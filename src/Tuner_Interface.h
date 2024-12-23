#ifndef TUNER_INTERFACE_H
#define TUNER_INTERFACE_H

void Tuner_I2C_Init();
void Tuner_Patch(byte TEF);
void Tuner_Init(const unsigned char *table);
bool Tuner_WriteBuffer(unsigned char *buf, uint16_t len);
bool Tuner_ReadBuffer(unsigned char *buf, uint16_t len);
bool Tuner_Table_Write(const unsigned char *tab);
void Tuner_Reset(void);
#endif