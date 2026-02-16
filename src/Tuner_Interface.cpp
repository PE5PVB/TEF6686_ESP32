#include "TEF6686.h"
#include "Tuner_Patch_Lithio_V102_p224.h"
#include "Tuner_Patch_Lithio_V205_p512.h"
#include <Wire.h>

#define TEF_I2C_ADDR 0x64

bool Data_Accelerator = false;

const unsigned char tuner_init_tab[] PROGMEM = {
  17, 0x20, 0x26, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xf8, 0x00, 0x00,
  9, 0x20, 0x36, 0x01, 0x00, 0x00, 0x01, 0x68, 0x01, 0x2C,
  7, 0x20, 0x37, 0x01, 0x00, 0x00, 0x0F, 0xA0,
  7, 0x20, 0x39, 0x01, 0x00, 0x01, 0x00, 0x01,
  7, 0x20, 0x3A, 0x01, 0x00, 0x01, 0x00, 0x01,
  11, 0x20, 0x3C, 0x01, 0x00, 0x3C, 0x00, 0x78, 0x00, 0x64, 0x00, 0xC8,
  11, 0x20, 0x46, 0x01, 0x01, 0xF4, 0x07, 0xD0, 0x00, 0xC8, 0x00, 0xC8,
  9, 0x20, 0x48, 0x01, 0x00, 0x00, 0x02, 0x58, 0x00, 0xF0,
  9, 0x20, 0x49, 0x01, 0x00, 0x00, 0x00, 0xA0, 0x00, 0x8C,
  9, 0x20, 0x4A, 0x01, 0x00, 0x00, 0x00, 0xA0, 0x00, 0x8C,
  7, 0x20, 0x4B, 0x01, 0x00, 0x00, 0x0F, 0xA0,
  7, 0x30, 0x15, 0x01, 0x00, 0x80, 0x00, 0x01,
  13, 0x30, 0x16, 0x01, 0x00, 0x21, 0x00, 0x02, 0x00, 0x10, 0x01, 0x00, 0x12, 0xc0,
  7, 0x30, 0x0d, 0x01, 0x00, 0x80, 0x00, 0xe0,
  0 // end marker
};

// Clock frequency data: 4 bytes frequency (big-endian Hz) + 2 bytes type
static const unsigned char clock_4000[]  PROGMEM = {0x00, 0x3D, 0x09, 0x00, 0x00, 0x00};
static const unsigned char clock_9216[]  PROGMEM = {0x00, 0x8C, 0xA0, 0x00, 0x00, 0x00};
static const unsigned char clock_12000[] PROGMEM = {0x00, 0xB7, 0x1B, 0x00, 0x00, 0x00};
static const unsigned char clock_55000[] PROGMEM = {0x03, 0x4E, 0x5A, 0xAE, 0x00, 0x01};

bool Tuner_WriteBuffer(unsigned char *buf, uint16_t len) {
  Wire.beginTransmission(TEF_I2C_ADDR);
  Wire.write(buf, len);
  uint8_t r = Wire.endTransmission();
  if (!Data_Accelerator) delay(2);
  return (r == 0);
}

bool Tuner_ReadBuffer(unsigned char *buf, uint16_t len) {
  Wire.requestFrom((uint8_t)TEF_I2C_ADDR, (uint8_t)len);
  if (Wire.available() == len) {
    for (uint16_t i = 0; i < len; i++) buf[i] = Wire.read();
    return true;
  }
  return false;
}

static void Tuner_Patch_Load(const unsigned char *pLutBytes, uint16_t size) {
  unsigned char buf[24 + 1];
  uint16_t i, len;
  buf[0] = 0x1b;

  while (size) {
    len = (size > 24) ? 24 : size;
    size -= len;

    for (i = 0; i < len; i++) buf[1 + i] = pgm_read_byte(&pLutBytes[i]);
    pLutBytes += len;

    if (!Tuner_WriteBuffer(buf, len + 1)) break;
  }
}

bool Tuner_Table_Write(const unsigned char *tab) {
  if (tab[1] == 0xff) {
    delay(tab[2]);
    return true;
  } else {
    return Tuner_WriteBuffer((unsigned char *)&tab[1], tab[0]);
  }
}

void Tuner_Reset(void) {
  Wire.beginTransmission(TEF_I2C_ADDR);
  Wire.write(0x1e);
  Wire.write(0x5a);
  Wire.write(0x01);
  Wire.write(0x5a);
  Wire.write(0x5a);
  Wire.endTransmission();
}

void Tuner_Patch(byte TEF) {
  Tuner_Reset();
  delay(100);
  Wire.beginTransmission(TEF_I2C_ADDR);
  Wire.write(0x1c);
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.endTransmission();
  delay(100);
  Wire.beginTransmission(TEF_I2C_ADDR);
  Wire.write(0x1c);
  Wire.write(0x00);
  Wire.write(0x74);
  Wire.endTransmission();
  switch (TEF) {
    case 102:
      Tuner_Patch_Load(pPatchBytes102, PatchSize102);
      break;

    case 205:
      Tuner_Patch_Load(pPatchBytes205, PatchSize205);
      break;
  }
  Wire.beginTransmission(TEF_I2C_ADDR);
  Wire.write(0x1c);
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.endTransmission();
  delay(100);
  Wire.beginTransmission(TEF_I2C_ADDR);
  Wire.write(0x1c);
  Wire.write(0x00);
  Wire.write(0x75);
  Wire.endTransmission();
  switch (TEF) {
    case 102:
      Tuner_Patch_Load(pLutBytes102, LutSize102);
      break;

    case 205:
      Tuner_Patch_Load(pLutBytes205, LutSize205);
      break;
  }
  Wire.beginTransmission(TEF_I2C_ADDR);
  Wire.write(0x1c);
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.endTransmission();
}

void Tuner_I2C_Init() {
  Wire.begin();
  Wire.setClock(400000);
  delay(5);
}

void Tuner_Init_Clock(byte xtal) {
  unsigned char activate[] = {0x14, 0x00, 0x01};
  Tuner_WriteBuffer(activate, 3);
  delay(50);

  const unsigned char *clockData;
  switch (xtal) {
    case 1: clockData = clock_9216;  break;
    case 2: clockData = clock_12000; break;
    case 3: clockData = clock_55000; break;
    default: clockData = clock_4000; break;
  }

  unsigned char clockCmd[9] = {0x40, 0x04, 0x01};
  memcpy_P(clockCmd + 3, clockData, 6);
  Tuner_WriteBuffer(clockCmd, 9);

  unsigned char enable[] = {0x40, 0x05, 0x01, 0x00, 0x01};
  Tuner_WriteBuffer(enable, 5);
  delay(100);
}

void Tuner_Init(const unsigned char *table) {
  const unsigned char *p = table;
  uint16_t i = 0;

  while (pgm_read_byte(p + i) != 0) {
    if (!Tuner_Table_Write(p + i)) break;
    i += pgm_read_byte(p + i) + 1;
  }
}
