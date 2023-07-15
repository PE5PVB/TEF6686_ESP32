#include <WiFiClient.h>
#include <EEPROM.h>
#include <Wire.h>
#include <math.h>
#include <TFT_eSPI.h>               // https://github.com/Bodmer/TFT_eSPI
#include <TimeLib.h>                // https://github.com/PaulStoffregen/Time
#include <Hash.h>                   // https://github.com/bbx10/Hash_tng
#include "src/WiFiConnect.h"
#include "src/WiFiConnectParam.h"
#include "src/font.h"
#include "src/TEF6686.h"
#include "src/constants.h"
#include "src/language.h"

#define GFXFF 1
#define FONT24 &Aura2ProRegular24pt7b
#define FONT14 &Aura2ProRegular14pt8b
#define FONT7  &Aura2ProRegular7pt8b

#define ROTARY_PIN_A    34
#define ROTARY_PIN_B    36
#define ROTARY_BUTTON   39
#define PIN_POT         35
#define BATTERY_PIN     13
#define BANDBUTTON       4
#define BWBUTTON        25
#define MODEBUTTON      26
#define CONTRASTPIN     2
#define STANDBYLED      19
#define SMETERPIN       27
//#define ARS       // uncomment for BGR type display (ARS version)

#ifdef ARS
#define VERSION         "v2.00ARS"
#include "ARS_Colors.h"
TFT_eSPI tft = TFT_eSPI(320, 240);
#else
#define VERSION         "v2.00"
TFT_eSPI tft = TFT_eSPI(240, 320);
#endif

bool advancedRDS;
bool af;
bool aftest;
bool afpage;
bool afscreen;
bool artheadold;
bool batterydetect = true;
bool BWreset;
bool change2;
bool compressedold;
bool rdsstereoold;
bool cleanup;
bool direction;
bool dropout;
bool dynamicPTYold;
bool edgebeep;
bool haseonold;
bool hasrtplusold;
bool hastmcold;
bool fullsearchrds;
bool hasafold;
bool LowLevelInit;
bool memorystore;
bool menu;
bool menuopen;
bool nobattery;
bool power = true;
bool errorAold;
bool errorBold;
bool errorCold;
bool errorDold;
bool RDSSPYTCP;
bool RDSSPYUSB;
bool RDSstatusold;
bool screenmute;
bool seek;
bool setupmode;
bool showrdserrors;
bool showsquelch;
bool softmuteam;
bool softmutefm;
bool SQ;
bool Stereostatusold;
bool StereoToggle = true;
bool store;
bool TAold;
bool TPold;
bool tuned;
bool USBmode = 1;
bool wifi;
bool wificonnected;
bool XDRGTKdata;
bool XDRGTKTCP;
bool XDRGTKUSB;
bool XDRMute;
bool screensavertriggered = false;
byte af_counterold;
byte afpagenr;
byte amnb;
byte audiomode;
byte band;
byte battery;
byte batteryold;
int batupdatetimer;
byte BWset;
byte colorinvert;
byte ContrastSet;
byte CurrentTheme;
byte displayflip;
byte ECCold;
byte EQset;
byte fmnb;
byte freqoldcount;
byte HighCutLevel;
byte HighCutOffset;
byte iMSEQ;
byte iMSset;
byte language;
byte licold;
byte memoryband[EE_PRESETS_CNT];
byte memorypos;
byte memoryposold;
byte menupage = 1;
byte menupagestotal = 4;
byte MSold;
byte optenc;
byte rdsblockold;
byte region;
byte regionold;
byte rotarymode;
byte showmodulation;
byte showSWMIBand = 1;
uint8_t SNR;
byte SNRold;
byte specialstepOIRT;
byte stepsize;
byte fmdefaultstepsize;
byte poweroptions;
byte screensaverset;
byte StereoLevel;
byte subnetclient;
byte TEF;
byte theme;
byte tunemode;
byte screensaverOptions[5] = {0, 3, 10, 30, 60};
byte unit;
char buff[16];
char programTypePrevious[18];
char radioIdPrevious[6];
int AGC;
int BWOld;
int bwupdatetimer;
int charWidth = tft.textWidth("AA");
int DeEmphasis;
int ForceMono;
int freqold;
int LevelOffset;
int AMLevelOffset;
int LowLevelSet;
int lowsignaltimer;
int menuoption = 30;
int MStatusold;
int offsetupdatetimer;
int OStatusold;
int peakholdold;
int peakholdtimer;
int rotary;
int rssi;
int rssiold = 200;
int scanner_filter;
int snrupdatetimer;
int Sqstatusold;
int Squelch;
int Squelchold;
int SStatusold;
int Stereostatus;
int VolSet;
int volume;
int XDRBWset;
int XDRBWsetold;
int xPos = 6;
int xPos2 = 6;
int xPos3 = 6;
int xPos4 = 6;
// Theme Engine Colors
int PrimaryColor;
int SecondaryColor;
int FrameColor;
int FrequencyColor;
int GreyoutColor;
int BackgroundColor;
int ActiveColor;
int OptimizerColor;
int RDSColor;
int StereoColor;
int16_t OStatus;
int16_t SAvg;
int16_t SAvg2;
int16_t SStatus;
IPAddress remoteip;
String cryptedpassword;
String CurrentThemeString;
String ECColdtxt;
String eonpsold[11];
String LIColdString;
String PIold;
String pinstringold;
String programServicePrevious;
String PSold;
String PTYold;
String ptynold = " ";
String rds_clock;
String rds_clockold;
String RDSSPYRDS;
String RDSSPYRDSold;
String RTold;
String salt;
String saltkey = "                ";
String SWMIBandstring = String();
String SWMIBandstringold = String();
String XDRGTK_key;
String XDRGTKRDS;
String XDRGTKRDSold;
uint16_t BW;
uint16_t MStatus;
uint16_t SWMIBandPos;
uint16_t SWMIBandPosold;  // Fix Me: Should store this parameter into flash, for use of restart.
uint16_t USN;
uint16_t WAM;
uint8_t buff_pos;
uint8_t RDSstatus;
unsigned int change;
unsigned int ConverterSet;
unsigned int freq_scan;
unsigned int frequency;
unsigned int frequency_AM;
unsigned int frequency_LW;
unsigned int frequency_MIBand_11M; // Surive before tuner restart
unsigned int frequency_MIBand_120M;
unsigned int frequency_MIBand_13M;
unsigned int frequency_MIBand_15M;
unsigned int frequency_MIBand_160M;
unsigned int frequency_MIBand_16M;
unsigned int frequency_MIBand_19M;
unsigned int frequency_MIBand_22M;
unsigned int frequency_MIBand_25M;
unsigned int frequency_MIBand_31M;
unsigned int frequency_MIBand_41M;
unsigned int frequency_MIBand_49M;
unsigned int frequency_MIBand_60M;
unsigned int frequency_MIBand_75M;
unsigned int frequency_MIBand_90M;
unsigned int frequency_MW;
unsigned int frequency_SW;
unsigned int frequencyold;
unsigned int HighEdgeOIRTSet;
unsigned int HighEdgeSet;
unsigned int LowEdgeOIRTSet;
unsigned int LowEdgeSet;
unsigned int LWHighEdgeSet;
unsigned int LWLowEdgeSet;
unsigned int mappedfreqold[10];
unsigned int memory[EE_PRESETS_CNT];
unsigned int MWHighEdgeSet;
unsigned int MWLowEdgeSet;
unsigned int scanner_end;
unsigned int scanner_start;
unsigned int scanner_step;
unsigned int SWHighEdgeSet;
unsigned int SWLowEdgeSet;
unsigned long peakholdmillis;
unsigned long afticker;
unsigned long aftickerhold;
unsigned long eonticker;
unsigned long eontickerhold;
unsigned long rtticker;
unsigned long rttickerhold;
unsigned long rtplusticker;
unsigned long rtplustickerhold;

unsigned long aftimer;

TEF6686 radio;
TFT_eSprite sprite = TFT_eSprite(&tft);
TFT_eSprite sprite2 = TFT_eSprite(&tft);
WiFiConnect wc;
WiFiServer Server(7373);
WiFiClient RemoteClient;
WiFiUDP Udp;
hw_timer_t *timScreensaver = NULL;
byte screensaver_IRQ = OFF;

void setup() {
  setupmode = true;
  EEPROM.begin(EE_TOTAL_CNT);
  if (EEPROM.readByte(EE_BYTE_CHECKBYTE) != EE_CHECKBYTE_VALUE) DefaultSettings();

  frequency = EEPROM.readUInt(EE_UINT_FREQUENCY_FM);
  VolSet = EEPROM.readInt(EE_INT_VOLSET);
  ConverterSet = EEPROM.readUInt(EE_UINT_CONVERTERSET);
  LowEdgeSet = EEPROM.readUInt(EE_UINT_FMLOWEDGESET);
  HighEdgeSet = EEPROM.readUInt(EE_UINT_FMHIGHEDGESET);
  ContrastSet = EEPROM.readByte(EE_BYTE_CONTRASTSET);
  StereoLevel = EEPROM.readByte(EE_BYTE_STEREOLEVEL);
  HighCutLevel = EEPROM.readByte(EE_BYTE_HIGHCUTLEVEL);
  HighCutOffset = EEPROM.readByte(EE_BYTE_HIGHCUTOFFSET);
  LevelOffset = EEPROM.readInt(EE_INT_LEVELOFFSET);
  edgebeep = EEPROM.readByte(EE_BYTE_EDGEBEEP);
  softmuteam = EEPROM.readByte(EE_BYTE_SOFTMUTEAM);
  softmutefm = EEPROM.readByte(EE_BYTE_SOFTMUTEFM);
  frequency_AM = EEPROM.readUInt(EE_UINT_FREQUENCY_AM);
  language = EEPROM.readByte(EE_BYTE_LANGUAGE);
  showrdserrors = EEPROM.readByte(EE_BYTE_SHOWRDSERRORS);
  TEF = EEPROM.readByte(EE_BYTE_TEF);
  displayflip = EEPROM.readByte(EE_BYTE_DISPLAYFLIP);
  rotarymode = EEPROM.readByte(EE_BYTE_ROTARYMODE);
  stepsize = EEPROM.readByte(EE_BYTE_STEPSIZE);
  tunemode = EEPROM.readByte(EE_BYTE_TUNEMODE);
  optenc = EEPROM.readByte(EE_BYTE_OPTENC);
  iMSset = EEPROM.readByte(EE_BYTE_IMSSET);
  EQset = EEPROM.readByte(EE_BYTE_EQSET);
  band = EEPROM.readByte(EE_BYTE_BAND);
  LowLevelSet = EEPROM.readInt(EE_INT_LOWLEVELSET);
  memorypos = EEPROM.readByte(EE_BYTE_MEMORYPOS);
  region = EEPROM.readByte(EE_BYTE_REGION);
  radio.rds.underscore = EEPROM.readByte(EE_BYTE_RDS_UNDERSCORE);
  USBmode = EEPROM.readByte(EE_BYTE_USBMODE);
  wifi = EEPROM.readByte(EE_BYTE_WIFI);
  subnetclient = EEPROM.readByte(EE_BYTE_SUBNETCLIENT);
  showSWMIBand = EEPROM.readByte(EE_BYTE_SHOWSWMIBAND);
  radio.rds.filter = EEPROM.readByte(EE_BYTE_RDS_FILTER);
  radio.rds.pierrors = EEPROM.readByte(EE_BYTE_RDS_PIERRORS);
  frequency_LW = EEPROM.readUInt(EE_UINT_FREQUENCY_LW);
  frequency_MW = EEPROM.readUInt(EE_UINT_FREQUENCY_MW);
  frequency_SW = EEPROM.readUInt(EE_UINT_FREQUENCY_SW);
  XDRGTK_key = EEPROM.readString(EE_STRING_XDRGTK_KEY);
  showsquelch = EEPROM.readByte(EE_BYTE_SHOWSQUELCH);
  showmodulation = EEPROM.readByte(EE_BYTE_SHOWMODULATION);
  amnb = EEPROM.readByte(EE_BYTE_AM_NB);
  fmnb = EEPROM.readByte(EE_BYTE_FM_NB);
  audiomode = EEPROM.readByte(EE_BYTE_AUDIOMODE);
  specialstepOIRT = EEPROM.readByte(EE_BYTE_OIRT);
  LowEdgeOIRTSet = EEPROM.readUInt(EE_UINT_LOWEDGEOIRTSET);
  HighEdgeOIRTSet = EEPROM.readUInt(EE_UINT_HIGHEDGEOIRTSET);
  colorinvert = EEPROM.readByte(EE_BYTE_COLORINVERT);
  poweroptions = EEPROM.readByte(EE_BYTE_POWEROPTIONS);
  CurrentTheme = EEPROM.readByte(EE_BYTE_CURRENTTHEME);
  fmdefaultstepsize = EEPROM.readByte(EE_BYTE_FMDEFAULTSTEPSIZE);
  screensaverset = EEPROM.readByte(EE_BYTE_SCREENSAVERSET);
  AMLevelOffset = EEPROM.readInt(EE_INT_AMLEVELOFFSET);
  unit = EEPROM.readByte(EE_BYTE_UNIT);
  af = EEPROM.readByte(EE_BYTE_AF);

  LWLowEdgeSet = FREQ_LW_LOW_EDGE_MIN;   // later will read from flash
  LWHighEdgeSet = FREQ_LW_HIGH_EDGE_MAX; // later will read from flash
  MWLowEdgeSet = region == 0 ? FREQ_MW_LOW_EDGE_MIN_9K : FREQ_MW_LOW_EDGE_MIN_10K;      // later will read from flash
  MWHighEdgeSet = region == 0 ? FREQ_MW_HIGH_EDGE_MAX_9K : FREQ_MW_HIGH_EDGE_MAX_10K;   // later will read from flash
  SWLowEdgeSet = FREQ_SW_LOW_EDGE_MIN;
  SWHighEdgeSet = FREQ_SW_HIGH_EDGE_MAX;

  for (int i = 0; i < EE_PRESETS_CNT; i++) memoryband[i] = EEPROM.readByte(i + EE_PRESETS_BAND_START);
  for (int i = 0; i < EE_PRESETS_CNT; i++) memory[i] = EEPROM.readUInt((i * 4) + EE_PRESETS_START);
  btStop();

  if (USBmode) Serial.begin(19200); else Serial.begin(115200);

  if (iMSset == 1 && EQset == 1) iMSEQ = 2;
  if (iMSset == 0 && EQset == 1) iMSEQ = 3;
  if (iMSset == 1 && EQset == 0) iMSEQ = 4;
  if (iMSset == 0 && EQset == 0) iMSEQ = 1;

  switch (band) {
    case BAND_LW:
      frequency_LW = frequency_AM;
      if (stepsize > 3) stepsize = 3;
      break;
    case BAND_MW:
      frequency_MW = frequency_AM;
      if (stepsize > 3) stepsize = 3;
      break;
    case BAND_SW: frequency_SW = frequency_AM; break;
    case BAND_FM:
      if (specialstepOIRT) {
        if (frequency >= (FREQ_FM_OIRT_START) && frequency <= (FREQ_FM_OIRT_END)) {
          if (frequency % 3 != 0) {
            Round30K(frequency);
          }
        }
      } else {
        if (frequency % 10 != 0) {
          if (fmdefaultstepsize == 1) Round100K(frequency); else Round50K(frequency);
        }
      }
      break;
    default: break;
  }

  tft.init();
  tft.invertDisplay(colorinvert);
  doTheme();
  if (displayflip == 0) {
#ifdef ARS
    tft.setRotation(0);
#else
    tft.setRotation(3);
#endif
  } else {
#ifdef ARS
    tft.setRotation(2);
#else
    tft.setRotation(1);
#endif
  }

  pinMode(MODEBUTTON, INPUT);
  pinMode(BWBUTTON, INPUT);
  pinMode(ROTARY_BUTTON, INPUT);
  pinMode(ROTARY_PIN_A, INPUT);
  pinMode(ROTARY_PIN_B, INPUT);
  attachInterrupt(digitalPinToInterrupt(ROTARY_PIN_A), read_encoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ROTARY_PIN_B), read_encoder, CHANGE);

  analogWrite(SMETERPIN, 0);

  if (digitalRead(BWBUTTON) == LOW && digitalRead(ROTARY_BUTTON) == HIGH) {
    if (rotarymode == 0) rotarymode = 1; else rotarymode = 0;
    EEPROM.writeByte(EE_BYTE_ROTARYMODE, rotarymode);
    EEPROM.commit();
    analogWrite(CONTRASTPIN, ContrastSet * 2 + 27);
    tft.setFreeFont(FONT14);
    tft.fillScreen(BackgroundColor);
    tft.setTextColor(ActiveColor);
    tft.drawCentreString(myLanguage[language][1], 155, 77, GFXFF);
    tft.drawCentreString(myLanguage[language][2], 150, 107, GFXFF);
    while (digitalRead(BWBUTTON) == LOW) delay(50);
  }

  if (digitalRead(MODEBUTTON) == LOW) {
    if (displayflip == 0) {
      displayflip = 1;
      tft.setRotation(1);
    } else {
      displayflip = 0;
      tft.setRotation(3);
    }
    EEPROM.writeByte(EE_BYTE_DISPLAYFLIP, displayflip);
    EEPROM.commit();
    analogWrite(CONTRASTPIN, ContrastSet * 2 + 27);
    tft.setFreeFont(FONT14);
    tft.fillScreen(BackgroundColor);
    tft.setTextColor(ActiveColor);
    tft.drawCentreString(myLanguage[language][3], 155, 77, GFXFF);
    tft.drawCentreString(myLanguage[language][2], 150, 107, GFXFF);
    while (digitalRead(MODEBUTTON) == LOW) delay(50);
  }

  if (digitalRead(BANDBUTTON) == LOW) {
    analogWrite(SMETERPIN, 511);
    analogWrite(CONTRASTPIN, ContrastSet * 2 + 27);
    tft.setFreeFont(FONT14);
    tft.fillScreen(BackgroundColor);
    tft.setTextColor(ActiveColor);
    tft.drawCentreString(myLanguage[language][4], 155, 77, GFXFF);
    tft.drawCentreString(myLanguage[language][5], 150, 107, GFXFF);
    while (digitalRead(BANDBUTTON) == LOW) delay(50);
    analogWrite(SMETERPIN, 0);
  }

  if (digitalRead(ROTARY_BUTTON) == LOW && digitalRead(BWBUTTON) == HIGH) {
    analogWrite(CONTRASTPIN, ContrastSet * 2 + 27);
    tft.setFreeFont(FONT14);
    tft.fillScreen(BackgroundColor);
    tft.setTextColor(ActiveColor);
    if (optenc == 0) {
      optenc = 1;
      tft.drawCentreString(myLanguage[language][6], 155, 77, GFXFF);
    } else {
      optenc = 0;
      tft.drawCentreString(myLanguage[language][7], 155, 77, GFXFF);
    }
    EEPROM.writeByte(EE_BYTE_OPTENC, optenc);
    EEPROM.commit();
    tft.drawCentreString(myLanguage[language][2], 150, 107, GFXFF);
    while (digitalRead(ROTARY_BUTTON) == LOW) delay(50);
  }

  if (digitalRead(ROTARY_BUTTON) == LOW && digitalRead(BWBUTTON) == LOW) {
    analogWrite(CONTRASTPIN, ContrastSet * 2 + 27);
    tft.setFreeFont(FONT14);
    tft.fillScreen(BackgroundColor);
    tft.setTextColor(ActiveColor);
    DefaultSettings();
    tft.drawCentreString(myLanguage[language][66], 155, 77, GFXFF);
    tft.drawCentreString(myLanguage[language][2], 150, 107, GFXFF);
    while (digitalRead(ROTARY_BUTTON) == LOW && digitalRead(BWBUTTON) == LOW) delay(50);
    ESP.restart();
  }

  tft.setSwapBytes(true);
  tft.fillScreen(BackgroundColor);
  tft.setTextColor(PrimaryColor);
  tft.setFreeFont(FONT14);
  tft.drawCentreString(myLanguage[language][8], 160, -5, GFXFF);
  tft.setFreeFont(FONT7);
  tft.setTextColor(PrimaryColor);
  tft.drawCentreString("Software " + String(VERSION), 160, 148, GFXFF);

  tft.fillCircle(160, 90, 60, TFT_RED);
  tft.fillCircle(160, 90, 52, BackgroundColor);

  tft.fillRect(120, 230, 16, 6, GreyoutColor);
  tft.fillRect(152, 230, 16, 6, GreyoutColor);
  tft.fillRect(184, 230, 16, 6, GreyoutColor);

  tft.drawBitmap(130, 80, TEFLogo, 59, 23, PrimaryColor);

  for (int x = 0; x <= ContrastSet; x++) {
    analogWrite(CONTRASTPIN, x * 2 + 27);
    delay(30);
  }

  TEF = EEPROM.readByte(EE_BYTE_TEF);

  if (TEF != 101 && TEF != 102 && TEF != 205) SetTunerPatch();

  radio.init(TEF);
  uint16_t device;
  uint16_t hw;
  uint16_t sw;

  radio.getIdentification(device, hw, sw);
  if (TEF != (highByte(hw) * 100 + highByte(sw))) SetTunerPatch();
  tft.fillRect(120, 230, 16, 6, PrimaryColor);

  radio.getIdentification(device, hw, sw);
  uint8_t version = highByte(hw) * 100 + highByte(sw);

  tft.setFreeFont(FONT14);
  tft.setTextColor(ActiveColor);

  if (lowByte(device) == 14) {
    fullsearchrds = false;
    tft.fillRect(152, 230, 16, 6, PrimaryColor);
    tft.drawCentreString("TEF6686 Lithio", 160, 160, GFXFF);
  } else if (lowByte(device) == 1) {
    fullsearchrds = true;
    tft.fillRect(152, 230, 16, 6, PrimaryColor);
    tft.drawCentreString("TEF6687 Lithio FMSI", 160, 160, GFXFF);
  } else if (lowByte(device) == 9) {
    fullsearchrds = false;
    tft.fillRect(152, 230, 16, 6, PrimaryColor);
    tft.drawCentreString("TEF6688 Lithio DR", 160, 160, GFXFF);
  } else if (lowByte(device) == 3) {
    fullsearchrds = true;
    tft.fillRect(152, 230, 16, 6, PrimaryColor);
    tft.drawCentreString("TEF6689 Lithio FMSI DR", 160, 160, GFXFF);
  } else {
    tft.setTextColor(TFT_RED);
    tft.drawCentreString(myLanguage[language][9], 160, 160, GFXFF);
    tft.fillRect(152, 230, 16, 6, TFT_RED);
    while (true);
    for (;;);
  }
  tft.drawCentreString("Patch: v" + String(TEF), 160, 190, GFXFF);

  if (wifi == true) {
    tryWiFi();
    tft.fillRect(184, 230, 16, 6, PrimaryColor);
    delay(2000);
  } else {
    Server.end();
    Udp.stop();
    tft.fillRect(184, 230, 16, 6, TFT_RED);
  }
  delay(1500);

  radio.setVolume(VolSet);
  radio.setOffset(LevelOffset);
  radio.setAMOffset(AMLevelOffset);
  radio.setStereoLevel(StereoLevel);
  radio.setHighCutLevel(HighCutLevel);
  radio.setHighCutOffset(HighCutOffset);
  radio.clearRDS(fullsearchrds);
  radio.setMute();
  radio.setSoftmuteFM(softmutefm);
  radio.setSoftmuteAM(softmuteam);
  radio.setAMNoiseBlanker(amnb);
  radio.setFMNoiseBlanker(fmnb);
  radio.setAudio(audiomode);
  if (region == 1) radio.setDeemphasis(2);
  radio.rds.region = region;
  LowLevelInit = true;

  if (ConverterSet >= 200) {
    Wire.beginTransmission(0x12);
    Wire.write(ConverterSet >> 8);
    Wire.write(ConverterSet & (0xFF));
    Wire.endTransmission();
  }

  if (analogRead(BATTERY_PIN) < 200) batterydetect = false;
  SelectBand();
  ShowSignalLevel();
  ShowBW();
  setupmode = false;
  sprite.createSprite(317, 16);
  sprite2.createSprite(172, 16);
  radio.tone(50, -5, 2000);

  if (screensaverset) {
    ScreensaverTimerInit();
    ScreensaverTimerSet(screensaverOptions[screensaverset]);
  }
}

void loop() {
  if (digitalRead(BANDBUTTON) == LOW && XDRGTKUSB == false && XDRGTKTCP == false) BANDBUTTONPress();

  if (power == true) {
    Communication();

    if (af) {
      if (aftest && millis() >= aftimer + 5000) {
        aftimer = millis();
        aftest = false;
        frequency = radio.TestAF();
        if (freqold != frequency) {
          ShowFreq(0);
          store = true;
        }
      }

      if (millis() >= aftimer + 10000) {
        aftimer = millis();
        if (USN > 150 || WAM > 150) {
          frequency = radio.TestAF();
          if (freqold != frequency) {
            ShowFreq(0);
            store = true;
          }
        }
      }
    }

    if (seek == true) Seek(direction);

    if ((SStatus / 10 > LowLevelSet) && LowLevelInit == false && menu == false && band == BAND_FM) {
      if (screenmute == false && !advancedRDS && !afscreen) {
        tft.setFreeFont(FONT7);
        tft.setTextColor(ActiveColor);
        if (showmodulation) {
          tft.drawString("10", 27, 146, GFXFF);
          tft.drawString("30", 57, 146, GFXFF);
          tft.drawString("50", 87, 146, GFXFF);
          tft.drawString("70", 117, 146, GFXFF);
          tft.drawString("100", 164, 146, GFXFF);
          tft.drawCentreString("M", 7, 132, GFXFF);
          for (byte segments = 0; segments < 94; segments++) {
            if (segments > 54) {
              if (((segments - 53) % 10) == 0) tft.fillRect(16 + (2 * segments), 147, 2, 3, TFT_RED);
            } else {
              if (((segments + 1) % 6) == 0) tft.fillRect(16 + (2 * segments), 147, 2, 3, TFT_GREEN);
            }
          }
        }
        if (region == 0) tft.drawString("PI:", 216, 191, GFXFF);
        if (region == 1) tft.drawString("ID:", 216, 191, GFXFF);
        tft.drawString("PS:", 6, 191, GFXFF);
        tft.drawString("PTY:", 6, 164, GFXFF);
        if (!showmodulation) tft.drawLine(20, 150, 200, 150, GreyoutColor); else tft.drawLine(20, 150, 200, 150, TFT_DARKGREY);
      }
      LowLevelInit = true;
    }

    if ((SStatus / 10 <= LowLevelSet) && band == BAND_FM) {
      if (LowLevelInit == true && menu == false) {
        if (screenmute == false && !afscreen && !advancedRDS) {
          tft.setFreeFont(FONT7);
          for (byte segments = 0; segments < 94; segments++) {
            if (segments > 54) {
              if (((segments - 53) % 10) == 0) tft.fillRect(16 + (2 * segments), 147, 2, 3, GreyoutColor);
            } else {
              if (((segments + 1) % 6) == 0) tft.fillRect(16 + (2 * segments), 147, 2, 3, GreyoutColor);
            }
          }
          tft.setTextColor(GreyoutColor);
          if (showmodulation) {
            tft.drawString("10", 27, 146, GFXFF);
            tft.drawString("30", 57, 146, GFXFF);
            tft.drawString("50", 87, 146, GFXFF);
            tft.drawString("70", 117, 146, GFXFF);
            tft.drawString("100", 164, 146, GFXFF);
            tft.drawCentreString("M", 7, 132, GFXFF);
            tft.fillRect(16, 139, 188, 8, GreyoutColor);
          }
          if (region == 0) tft.drawString("PI:", 216, 191, GFXFF);
          if (region == 1) tft.drawString("ID:", 216, 191, GFXFF);
          tft.drawString("PS:", 6, 191, GFXFF);
          tft.drawString("PTY:", 6, 164, GFXFF);
          tft.drawLine(20, 150, 200, 150, GreyoutColor);
          tft.drawBitmap(110, 5, RDSLogo, 67, 22, GreyoutColor);
        }
        LowLevelInit = false;
      }

      if (millis() >= lowsignaltimer + 300) {
        lowsignaltimer = millis();
        if (band == BAND_FM) radio.getStatus(SStatus, USN, WAM, OStatus, BW, MStatus, SNR); else radio.getStatusAM(SStatus, USN, WAM, OStatus, BW, MStatus, SNR);
        if (screenmute == true) readRds();
        if (menu == false) {
          doSquelch();
          GetData();
        }
      }

    } else {
      if (band == BAND_FM) radio.getStatus(SStatus, USN, WAM, OStatus, BW, MStatus, SNR); else radio.getStatusAM(SStatus, USN, WAM, OStatus, BW, MStatus, SNR);
      if (menu == false) {
        doSquelch();
        readRds();
        GetData();
        if (screenmute == false && afscreen == false && advancedRDS == false) ShowModLevel();
      }
    }

    if (menu == true && menuopen == true && menupage == 1 && menuoption == 110) {
      if (band == BAND_FM) radio.getStatus(SStatus, USN, WAM, OStatus, BW, MStatus, SNR); else radio.getStatusAM(SStatus, USN, WAM, OStatus, BW, MStatus, SNR);
      if (millis() >= lowsignaltimer + 500 || change2 == true) {
        lowsignaltimer = millis();
        change2 = false;
        if (SStatus > SStatusold || SStatus < SStatusold) {
          tft.setFreeFont(FONT24);
          tft.setTextColor(BackgroundColor);
          if (SStatus / 10 != SStatusold / 10) tft.drawRightString(String(SStatusold / 10), 150, 146, GFXFF);
          tft.setFreeFont(FONT14);
          tft.drawString("." + String(abs(SStatusold % 10)), 156, 137, GFXFF);
          tft.setFreeFont(FONT24);
          tft.setTextColor(PrimaryColor);
          tft.drawRightString(String(SStatus / 10), 150, 146, GFXFF);
          tft.setFreeFont(FONT14);
          tft.drawString("." + String(abs(SStatus % 10)), 156, 137, GFXFF);
          SStatusold = SStatus;
        }
      }
    }

    if (rotary == -1) {
      if (screensavertriggered) {
        rotary = 0;
        WakeToSleep(REVERSE);
      } else {
        KeyUp();
        if (screensaverset && !menu && !screensavertriggered) ScreensaverTimerRestart();
      }
    }
    if (rotary == 1) {
      if (screensavertriggered) {
        rotary = 0;
        WakeToSleep(REVERSE);
      } else {
        KeyDown();
        if (screensaverset && !menu && !screensavertriggered) ScreensaverTimerRestart();
      }
    }

    if (digitalRead(ROTARY_BUTTON) == LOW) if (!afscreen) ButtonPress();
    if (digitalRead(MODEBUTTON) == LOW && screenmute == false) ModeButtonPress();
    if (digitalRead(BWBUTTON) == LOW && screenmute == false) if (!afscreen) BWButtonPress();

    if (store == true) change++;

    if (change > 200 && store == true) {
      detachInterrupt(digitalPinToInterrupt(ROTARY_PIN_A));
      detachInterrupt(digitalPinToInterrupt(ROTARY_PIN_B));
      EEPROM.writeUInt(EE_UINT_FREQUENCY_FM, frequency);
      EEPROM.writeUInt(EE_UINT_FREQUENCY_AM, frequency_AM);
      EEPROM.writeByte(EE_BYTE_BAND, band);
      EEPROM.writeUInt(EE_UINT_FREQUENCY_LW, frequency_LW);
      EEPROM.writeUInt(EE_UINT_FREQUENCY_MW, frequency_MW);
      EEPROM.writeUInt(EE_UINT_FREQUENCY_SW, frequency_SW);
      EEPROM.commit();
      store = false;
      attachInterrupt(digitalPinToInterrupt(ROTARY_PIN_A), read_encoder, CHANGE);
      attachInterrupt(digitalPinToInterrupt(ROTARY_PIN_B), read_encoder, CHANGE);
    }

    if (screensaverset) {
      if (screensaver_IRQ)
      {
        screensaver_IRQ = OFF;
        if (!screensavertriggered && !advancedRDS && !menu) {
          WakeToSleep(true);
        }
      }
    }
  } else {
    if (rotary != 0) {
      rotary = 0;
      if (screensavertriggered) WakeToSleep(REVERSE);
    }
  }
}

void GetData() {
  if (band == BAND_FM) ShowStereoStatus();
  if (screenmute == false) {
    if (band == BAND_FM) {
      if (advancedRDS && !afscreen) ShowAdvancedRDS();
      if (afscreen) ShowAFEON();
      if (!afscreen)
      {
        showPTY();
        doAF();
        showECC();
        showRadioText();
      }
      showPI();
      showPS();
    }
    ShowRSSI();
    ShowBattery();
    ShowOffset();
    if (!afscreen) ShowSignalLevel();
    ShowBW();
  }
}

void ShowPowerOptions(bool notglanceview) {
  uint16_t x, y;
  if (notglanceview) {
    x = 155;
    y = 110;
  } else {
    x = 305;
    y = 70;
  }

  switch (poweroptions) {
    case DEEP_SLEEP:
      if (notglanceview) tft.drawCentreString(myLanguage[language][75], x, y, GFXFF);
      else tft.drawRightString(myLanguage[language][75], x, y, GFXFF);
      break;
    case LCD_OFF:
      if (notglanceview) tft.drawCentreString(myLanguage[language][76], x, y, GFXFF);
      else tft.drawRightString(myLanguage[language][76], x, y, GFXFF);
      break;
    case LCD_BRIGHTNESS_1_PERCENT:
      if (notglanceview) tft.drawCentreString(myLanguage[language][94], x, y, GFXFF);
      else tft.drawRightString(myLanguage[language][94], x, y, GFXFF);
      break;
    case LCD_BRIGHTNESS_A_QUARTER:
      if (notglanceview) tft.drawCentreString(myLanguage[language][95], x, y, GFXFF);
      else tft.drawRightString(myLanguage[language][95], x, y, GFXFF);
      break;
    case LCD_BRIGHTNESS_HALF:
      if (notglanceview) tft.drawCentreString(myLanguage[language][96], x, y, GFXFF);
      else tft.drawRightString(myLanguage[language][96], x, y, GFXFF);
      break;
  }
}

void WakeToSleep(bool yes) {
  if (yes) {
    screensavertriggered = true;
    switch (poweroptions) {
      case DEEP_SLEEP:
        power = false;
        analogWrite(SMETERPIN, 0);
        MuteScreen(1);
        StoreFrequency();
        radio.power(1);
        break;
      case LCD_OFF:
        power = false;
        analogWrite(SMETERPIN, 0);
        MuteScreen(1);
        StoreFrequency();
        break;
      case LCD_BRIGHTNESS_1_PERCENT:
        analogWrite(SMETERPIN, 0);
        analogWrite(CONTRASTPIN, 1 * 2 + 27);
        break;
      case LCD_BRIGHTNESS_A_QUARTER:
        analogWrite(SMETERPIN, 0);
        analogWrite(CONTRASTPIN, MIN(ContrastSet, 25) * 2 + 27);
        break;
      case LCD_BRIGHTNESS_HALF:
        analogWrite(SMETERPIN, 0);
        analogWrite(CONTRASTPIN, MIN(ContrastSet, 50) * 2 + 27);
        break;
    }
  } else {
    switch (poweroptions) {
      case DEEP_SLEEP:
        ESP.restart();
        break;
      case LCD_OFF:
        power = true;
        pinMode (STANDBYLED, OUTPUT);
        digitalWrite(STANDBYLED, LOW);
        analogWrite(CONTRASTPIN, ContrastSet * 2 + 27);
        MuteScreen(0);
        screensavertriggered = false;
        screensaver_IRQ = OFF;
        ScreensaverTimerReopen();
        break;
      case LCD_BRIGHTNESS_1_PERCENT:
      case LCD_BRIGHTNESS_A_QUARTER:
      case LCD_BRIGHTNESS_HALF:
        pinMode (STANDBYLED, OUTPUT);
        digitalWrite(STANDBYLED, LOW);
        analogWrite(CONTRASTPIN, ContrastSet * 2 + 27);
        MuteScreen(0);
        screensavertriggered = false;
        screensaver_IRQ = OFF;
        ScreensaverTimerReopen();
        break;
    }
  }
}

void ScreensaverTimerInit() {
  timScreensaver = timerBegin(0, 80, true);
  timerAttachInterrupt(timScreensaver, ScreensaverInterrupt, true);
}

void ScreensaverTimerSet(byte value) {
  if (timScreensaver == NULL) {
    ScreensaverTimerInit();
    ScreensaverTimerSet(screensaverOptions[screensaverset]);
  }

  if (value == OFF) {
    if (screensaverset) timerStop(timScreensaver);
  } else {
    timerStop(timScreensaver);
    timerAlarmWrite(timScreensaver, value * TIMER_SCREENSAVER_BASE, true);
    timerStart(timScreensaver);
    timerAlarmEnable(timScreensaver);
  }
}

void ScreensaverTimerRestart() {
  if (timScreensaver == NULL) {
    ScreensaverTimerInit();
    ScreensaverTimerSet(screensaverOptions[screensaverset]);
  }
  timerRestart(timScreensaver);
}

void ScreensaverTimerReopen() {
  ScreensaverTimerSet(OFF);
  ScreensaverTimerSet(screensaverOptions[screensaverset]);
  ScreensaverTimerRestart();
}

void ScreensaverInterrupt()
{
  screensaver_IRQ = ON;
}

void BANDBUTTONPress() {
  if (!power) {
    if (screensavertriggered) WakeToSleep(REVERSE);
  } else {
    if (afscreen) {
      BuildAdvancedRDS();
    } else {
      unsigned long counterold = millis();
      unsigned long counter = millis();
      if (!menu && power) {
        while (digitalRead(BANDBUTTON) == LOW && counter - counterold <= 1000) counter = millis();

        if (counter - counterold < 1000) {
          if (screensavertriggered) {
            WakeToSleep(REVERSE);
            return;
          }

          if (advancedRDS) {
            BuildDisplay();
            ScreensaverTimerReopen();
          } else {
            if (tunemode != TUNE_MEM) {
              if (band == BAND_FM) {
                band = BAND_LW;
                if (stepsize > 3) stepsize = 3;
              }
              else if (band == BAND_LW) band = BAND_MW;
              else if (band == BAND_MW) band = BAND_SW;
              else if (band == BAND_SW) band = BAND_FM;
              StoreFrequency();
              SelectBand();
            }
            ScreensaverTimerRestart();
          }
        } else {
          if (screensavertriggered) {
            WakeToSleep(REVERSE);
            return;
          }

          if (band == BAND_FM) {
            if (advancedRDS && !seek) BuildAFScreen(); else BuildAdvancedRDS();
          } else {
            WakeToSleep(true);
          }
        }
      }
      while (digitalRead(BANDBUTTON) == LOW) delay(50);
      delay(100);
    }
  }
}

void StoreFrequency() {
  EEPROM.writeUInt(EE_UINT_FREQUENCY_FM, frequency);
  EEPROM.writeUInt(EE_UINT_FREQUENCY_AM, frequency_AM);
  EEPROM.writeByte(EE_BYTE_BAND, band);
  EEPROM.writeUInt(EE_UINT_FREQUENCY_LW, frequency_LW);
  EEPROM.writeUInt(EE_UINT_FREQUENCY_MW, frequency_MW);
  EEPROM.writeUInt(EE_UINT_FREQUENCY_SW, frequency_SW);
  EEPROM.commit();
}

void LimitAMFrequency() {
  switch (band) {
    case BAND_LW:
      frequency_AM = frequency_LW;
      if (frequency_AM > LWHighEdgeSet || frequency_AM < LWLowEdgeSet) {
        frequency_AM = LWLowEdgeSet;
      }
      break;
    case BAND_MW:
      frequency_AM = frequency_MW;
      if (frequency_AM > MWHighEdgeSet || frequency_AM < MWLowEdgeSet) {
        frequency_AM = MWLowEdgeSet; // take care of 9K/10K step
      }
      break;
    case BAND_SW:
      frequency_AM = frequency_SW;
      if (frequency_AM > SWHighEdgeSet || frequency_AM < SWLowEdgeSet) {
        frequency_AM = SWLowEdgeSet;
      }
      break;
  }
}

void DivdeSWMIBand() {
  if (frequency_AM >= FREQ_SW_160M_START && frequency_AM <= FREQ_SW_160M_END) {
    SWMIBandPos = SW_MI_BAND_160M;
    frequency_MIBand_160M = frequency_AM;
    SWMIBandstring = (String) "" + SWMIBandPos + " m";
  } else if (frequency_AM >= FREQ_SW_120M_START && frequency_AM <= FREQ_SW_120M_END) {
    SWMIBandPos = SW_MI_BAND_120M;
    frequency_MIBand_120M = frequency_AM;
    SWMIBandstring = (String) "" + SWMIBandPos + " m";
  } else if (frequency_AM >= FREQ_SW_90M_START && frequency_AM <= FREQ_SW_90M_END) {
    SWMIBandPos = SW_MI_BAND_90M;
    frequency_MIBand_90M = frequency_AM;
    SWMIBandstring = (String) "" + SWMIBandPos + " m";
  } else if (frequency_AM >= FREQ_SW_75M_START && frequency_AM <= FREQ_SW_75M_END) {
    SWMIBandPos = SW_MI_BAND_75M;
    frequency_MIBand_75M = frequency_AM;
    SWMIBandstring = (String) "" + SWMIBandPos + " m";
  } else if (frequency_AM >= FREQ_SW_60M_START && frequency_AM <= FREQ_SW_60M_END) {
    SWMIBandPos = SW_MI_BAND_60M;
    frequency_MIBand_60M = frequency_AM;
    SWMIBandstring = (String) "" + SWMIBandPos + " m";
  } else if (frequency_AM >= FREQ_SW_49M_START && frequency_AM <= FREQ_SW_49M_END) {
    SWMIBandPos = SW_MI_BAND_49M;
    frequency_MIBand_49M = frequency_AM;
    SWMIBandstring = (String) "" + SWMIBandPos + " m";
  } else if (frequency_AM >= FREQ_SW_41M_START && frequency_AM <= FREQ_SW_41M_END) {
    SWMIBandPos = SW_MI_BAND_41M;
    frequency_MIBand_41M = frequency_AM;
    SWMIBandstring = (String) "" + SWMIBandPos + " m";
  } else if (frequency_AM >= FREQ_SW_31M_START && frequency_AM <= FREQ_SW_31M_END) {
    SWMIBandPos = SW_MI_BAND_31M;
    frequency_MIBand_31M = frequency_AM;
    SWMIBandstring = (String) "" + SWMIBandPos + " m";
  } else if (frequency_AM >= FREQ_SW_25M_START && frequency_AM <= FREQ_SW_25M_END) {
    SWMIBandPos = SW_MI_BAND_25M;
    frequency_MIBand_25M = frequency_AM;
    SWMIBandstring = (String) "" + SWMIBandPos + " m";
  } else if (frequency_AM >= FREQ_SW_22M_START && frequency_AM <= FREQ_SW_22M_END) {
    SWMIBandPos = SW_MI_BAND_22M;
    frequency_MIBand_22M = frequency_AM;
    SWMIBandstring = (String) "" + SWMIBandPos + " m";
  } else if (frequency_AM >= FREQ_SW_19M_START && frequency_AM <= FREQ_SW_19M_END) {
    SWMIBandPos = SW_MI_BAND_19M;
    frequency_MIBand_19M = frequency_AM;
    SWMIBandstring = (String) "" + SWMIBandPos + " m";
  } else if (frequency_AM >= FREQ_SW_16M_START && frequency_AM <= FREQ_SW_16M_END) {
    SWMIBandPos = SW_MI_BAND_16M;
    frequency_MIBand_16M = frequency_AM;
    SWMIBandstring = (String) "" + SWMIBandPos + " m";
  } else if (frequency_AM >= FREQ_SW_15M_START && frequency_AM <= FREQ_SW_15M_END) {
    SWMIBandPos = SW_MI_BAND_15M;
    frequency_MIBand_15M = frequency_AM;
    SWMIBandstring = (String) "" + SWMIBandPos + " m";
  } else if (frequency_AM >= FREQ_SW_13M_START && frequency_AM <= FREQ_SW_13M_END) {
    SWMIBandPos = SW_MI_BAND_13M;
    frequency_MIBand_13M = frequency_AM;
    SWMIBandstring = (String) "" + SWMIBandPos + " m";
  } else if (frequency_AM >= FREQ_SW_11M_START && frequency_AM <= FREQ_SW_11M_END) {
    SWMIBandPos = SW_MI_BAND_11M;
    frequency_MIBand_11M = frequency_AM;
    SWMIBandstring = (String) "" + SWMIBandPos + " m";
  } else {
    if (SWMIBandPos > SW_MI_BAND_GAP) {
      SWMIBandPosold = SWMIBandPos;
      SWMIBandstringold = (String) "" + SWMIBandPosold + " m";
    }
    SWMIBandPos = SW_MI_BAND_GAP;
  }
}

void ToggleSWMIBand(bool plus) {
  switch (SWMIBandPosold) {
    case SW_MI_BAND_GAP:
      if (plus) {
        SWMIBandPos = SW_MI_BAND_160M;
        SWMIBandPosold = SWMIBandPos;
        frequency_AM = FREQ_SW_160M_START;
      } else {
        SWMIBandPos = SW_MI_BAND_11M;
        SWMIBandPosold = SWMIBandPos;
        frequency_AM = FREQ_SW_11M_END;
      }
      radio.SetFreqAM(frequency_AM);
      frequency_SW = frequency_AM;
      break;
    case SW_MI_BAND_11M:
      if (plus) {
        SWMIBandstringold = (String) "" + SWMIBandPosold + " m";
        SWMIBandPos = SW_MI_BAND_160M;
        SWMIBandPosold = SWMIBandPos;
        SWMIBandstring = (String) "" + SWMIBandPos + " m";
        frequency_AM = frequency_MIBand_160M == 0 ? FREQ_SW_160M_START : frequency_MIBand_160M;
      } else {
        SWMIBandstringold = (String) "" + SWMIBandPosold + " m";
        SWMIBandPos = SW_MI_BAND_13M;
        SWMIBandPosold = SWMIBandPos;
        SWMIBandstring = (String) "" + SWMIBandPos + " m";
        frequency_AM = frequency_MIBand_13M == 0 ? FREQ_SW_13M_END : frequency_MIBand_13M;
      }
      radio.SetFreqAM(frequency_AM);
      frequency_SW = frequency_AM;
      break;
    case SW_MI_BAND_13M:
      if (plus) {
        SWMIBandstringold = (String) "" + SWMIBandPosold + " m";
        SWMIBandPos = SW_MI_BAND_11M;
        SWMIBandPosold = SWMIBandPos;
        SWMIBandstring = (String) "" + SWMIBandPos + " m";
        frequency_AM = frequency_MIBand_11M == 0 ? FREQ_SW_11M_START : frequency_MIBand_11M;
      } else {
        SWMIBandstringold = (String) "" + SWMIBandPosold + " m";
        SWMIBandPos = SW_MI_BAND_15M;
        SWMIBandPosold = SWMIBandPos;
        SWMIBandstring = (String) "" + SWMIBandPos + " m";
        frequency_AM = frequency_MIBand_15M == 0 ? FREQ_SW_15M_END : frequency_MIBand_15M;
      }
      radio.SetFreqAM(frequency_AM);
      frequency_SW = frequency_AM;
      break;
    case SW_MI_BAND_15M:
      if (plus) {
        SWMIBandstringold = (String) "" + SWMIBandPosold + " m";
        SWMIBandPos = SW_MI_BAND_13M;
        SWMIBandPosold = SWMIBandPos;
        SWMIBandstring = (String) "" + SWMIBandPos + " m";
        frequency_AM = frequency_MIBand_13M == 0 ? FREQ_SW_13M_START : frequency_MIBand_13M;
      } else {
        SWMIBandstringold = (String) "" + SWMIBandPosold + " m";
        SWMIBandPos = SW_MI_BAND_16M;
        SWMIBandPosold = SWMIBandPos;
        SWMIBandstring = (String) "" + SWMIBandPos + " m";
        frequency_AM = frequency_MIBand_16M == 0 ? FREQ_SW_16M_END : frequency_MIBand_16M;
      }
      radio.SetFreqAM(frequency_AM);
      frequency_SW = frequency_AM;
      break;
    case SW_MI_BAND_16M:
      if (plus) {
        SWMIBandstringold = (String) "" + SWMIBandPosold + " m";
        SWMIBandPos = SW_MI_BAND_15M;
        SWMIBandPosold = SWMIBandPos;
        SWMIBandstring = (String) "" + SWMIBandPos + " m";
        frequency_AM = frequency_MIBand_15M == 0 ? FREQ_SW_15M_START : frequency_MIBand_15M;
      } else {
        SWMIBandstringold = (String) "" + SWMIBandPosold + " m";
        SWMIBandPos = SW_MI_BAND_19M;
        SWMIBandPosold = SWMIBandPos;
        SWMIBandstring = (String) "" + SWMIBandPos + " m";
        frequency_AM = frequency_MIBand_19M == 0 ? FREQ_SW_19M_END : frequency_MIBand_19M;
      }
      radio.SetFreqAM(frequency_AM);
      frequency_SW = frequency_AM;
      break;
    case SW_MI_BAND_19M:
      if (plus) {
        SWMIBandstringold = (String) "" + SWMIBandPosold + " m";
        SWMIBandPos = SW_MI_BAND_16M;
        SWMIBandPosold = SWMIBandPos;
        SWMIBandstring = (String) "" + SWMIBandPos + " m";
        frequency_AM = frequency_MIBand_16M == 0 ? FREQ_SW_16M_START : frequency_MIBand_16M;
      } else {
        SWMIBandstringold = (String) "" + SWMIBandPosold + " m";
        SWMIBandPos = SW_MI_BAND_22M;
        SWMIBandPosold = SWMIBandPos;
        SWMIBandstring = (String) "" + SWMIBandPos + " m";
        frequency_AM = frequency_MIBand_22M == 0 ? FREQ_SW_22M_END : frequency_MIBand_22M;
      }
      radio.SetFreqAM(frequency_AM);
      frequency_SW = frequency_AM;
      break;
    case SW_MI_BAND_22M:
      if (plus) {
        SWMIBandstringold = (String) "" + SWMIBandPosold + " m";
        SWMIBandPos = SW_MI_BAND_19M;
        SWMIBandPosold = SWMIBandPos;
        SWMIBandstring = (String) "" + SWMIBandPos + " m";
        frequency_AM = frequency_MIBand_19M == 0 ? FREQ_SW_19M_START : frequency_MIBand_19M;
      } else {
        SWMIBandstringold = (String) "" + SWMIBandPosold + " m";
        SWMIBandPos = SW_MI_BAND_25M;
        SWMIBandPosold = SWMIBandPos;
        SWMIBandstring = (String) "" + SWMIBandPos + " m";
        frequency_AM = frequency_MIBand_25M == 0 ? FREQ_SW_25M_END : frequency_MIBand_25M;
      }
      radio.SetFreqAM(frequency_AM);
      frequency_SW = frequency_AM;
      break;
    case SW_MI_BAND_25M:
      if (plus) {
        SWMIBandstringold = (String) "" + SWMIBandPosold + " m";
        SWMIBandPos = SW_MI_BAND_22M;
        SWMIBandPosold = SWMIBandPos;
        SWMIBandstring = (String) "" + SWMIBandPos + " m";
        frequency_AM = frequency_MIBand_22M == 0 ? FREQ_SW_22M_START : frequency_MIBand_22M;
      } else {
        SWMIBandstringold = (String) "" + SWMIBandPosold + " m";
        SWMIBandPos = SW_MI_BAND_31M;
        SWMIBandPosold = SWMIBandPos;
        SWMIBandstring = (String) "" + SWMIBandPos + " m";
        frequency_AM = frequency_MIBand_31M == 0 ? FREQ_SW_31M_END : frequency_MIBand_31M;
      }
      radio.SetFreqAM(frequency_AM);
      frequency_SW = frequency_AM;
      break;
    case SW_MI_BAND_31M:
      if (plus) {
        SWMIBandstringold = (String) "" + SWMIBandPosold + " m";
        SWMIBandPos = SW_MI_BAND_25M;
        SWMIBandPosold = SWMIBandPos;
        SWMIBandstring = (String) "" + SWMIBandPos + " m";
        frequency_AM = frequency_MIBand_25M == 0 ? FREQ_SW_25M_START : frequency_MIBand_25M;
      } else {
        SWMIBandstringold = (String) "" + SWMIBandPosold + " m";
        SWMIBandPos = SW_MI_BAND_41M;
        SWMIBandPosold = SWMIBandPos;
        SWMIBandstring = (String) "" + SWMIBandPos + " m";
        frequency_AM = frequency_MIBand_41M == 0 ? FREQ_SW_41M_END : frequency_MIBand_41M;
      }
      radio.SetFreqAM(frequency_AM);
      frequency_SW = frequency_AM;
      break;
    case SW_MI_BAND_41M:
      if (plus) {
        SWMIBandstringold = (String) "" + SWMIBandPosold + " m";
        SWMIBandPos = SW_MI_BAND_31M;
        SWMIBandPosold = SWMIBandPos;
        SWMIBandstring = (String) "" + SWMIBandPos + " m";
        frequency_AM = frequency_MIBand_31M == 0 ? FREQ_SW_31M_START : frequency_MIBand_31M;
      } else {
        SWMIBandstringold = (String) "" + SWMIBandPosold + " m";
        SWMIBandPos = SW_MI_BAND_49M;
        SWMIBandPosold = SWMIBandPos;
        SWMIBandstring = (String) "" + SWMIBandPos + " m";
        frequency_AM = frequency_MIBand_49M == 0 ? FREQ_SW_49M_END : frequency_MIBand_49M;
      }
      radio.SetFreqAM(frequency_AM);
      frequency_SW = frequency_AM;
      break;
    case SW_MI_BAND_49M:
      if (plus) {
        SWMIBandstringold = (String) "" + SWMIBandPosold + " m";
        SWMIBandPos = SW_MI_BAND_41M;
        SWMIBandPosold = SWMIBandPos;
        SWMIBandstring = (String) "" + SWMIBandPos + " m";
        frequency_AM = frequency_MIBand_41M == 0 ? FREQ_SW_41M_START : frequency_MIBand_41M;
      } else {
        SWMIBandstringold = (String) "" + SWMIBandPosold + " m";
        SWMIBandPos = SW_MI_BAND_60M;
        SWMIBandPosold = SWMIBandPos;
        SWMIBandstring = (String) "" + SWMIBandPos + " m";
        frequency_AM = frequency_MIBand_60M == 0 ? FREQ_SW_60M_END : frequency_MIBand_60M;
      }
      radio.SetFreqAM(frequency_AM);
      frequency_SW = frequency_AM;
      break;
    case SW_MI_BAND_60M:
      if (plus) {
        SWMIBandstringold = (String) "" + SWMIBandPosold + " m";
        SWMIBandPos = SW_MI_BAND_49M;
        SWMIBandPosold = SWMIBandPos;
        SWMIBandstring = (String) "" + SWMIBandPos + " m";
        frequency_AM = frequency_MIBand_49M == 0 ? FREQ_SW_49M_START : frequency_MIBand_49M;
      } else {
        SWMIBandstringold = (String) "" + SWMIBandPosold + " m";
        SWMIBandPos = SW_MI_BAND_75M;
        SWMIBandPosold = SWMIBandPos;
        SWMIBandstring = (String) "" + SWMIBandPos + " m";
        frequency_AM = frequency_MIBand_75M == 0 ? FREQ_SW_75M_END : frequency_MIBand_75M;
      }
      radio.SetFreqAM(frequency_AM);
      frequency_SW = frequency_AM;
      break;
    case SW_MI_BAND_75M:
      if (plus) {
        SWMIBandstringold = (String) "" + SWMIBandPosold + " m";
        SWMIBandPos = SW_MI_BAND_60M;
        SWMIBandPosold = SWMIBandPos;
        SWMIBandstring = (String) "" + SWMIBandPos + " m";
        frequency_AM = frequency_MIBand_60M == 0 ? FREQ_SW_60M_START : frequency_MIBand_60M;
      } else {
        SWMIBandstringold = (String) "" + SWMIBandPosold + " m";
        SWMIBandPos = SW_MI_BAND_90M;
        SWMIBandPosold = SWMIBandPos;
        SWMIBandstring = (String) "" + SWMIBandPos + " m";
        frequency_AM = frequency_MIBand_90M == 0 ? FREQ_SW_90M_END : frequency_MIBand_90M;
      }
      radio.SetFreqAM(frequency_AM);
      frequency_SW = frequency_AM;
      break;
    case SW_MI_BAND_90M:
      if (plus) {
        SWMIBandstringold = (String) "" + SWMIBandPosold + " m";
        SWMIBandPos = SW_MI_BAND_75M;
        SWMIBandPosold = SWMIBandPos;
        SWMIBandstring = (String) "" + SWMIBandPos + " m";
        frequency_AM = frequency_MIBand_75M == 0 ? FREQ_SW_75M_START : frequency_MIBand_75M;
      } else {
        SWMIBandstringold = (String) "" + SWMIBandPosold + " m";
        SWMIBandPos = SW_MI_BAND_120M;
        SWMIBandPosold = SWMIBandPos;
        SWMIBandstring = (String) "" + SWMIBandPos + " m";
        frequency_AM = frequency_MIBand_120M == 0 ? FREQ_SW_120M_END : frequency_MIBand_120M;
      }
      radio.SetFreqAM(frequency_AM);
      frequency_SW = frequency_AM;
      break;
    case SW_MI_BAND_120M:
      if (plus) {
        SWMIBandstringold = (String) "" + SWMIBandPosold + " m";
        SWMIBandPos = SW_MI_BAND_90M;
        SWMIBandPosold = SWMIBandPos;
        SWMIBandstring = (String) "" + SWMIBandPos + " m";
        frequency_AM = frequency_MIBand_90M == 0 ? FREQ_SW_90M_START : frequency_MIBand_90M;
      } else {
        SWMIBandstringold = (String) "" + SWMIBandPosold + " m";
        SWMIBandPos = SW_MI_BAND_160M;
        SWMIBandPosold = SWMIBandPos;
        SWMIBandstring = (String) "" + SWMIBandPos + " m";
        frequency_AM = frequency_MIBand_160M == 0 ? FREQ_SW_160M_END : frequency_MIBand_160M;
      }
      radio.SetFreqAM(frequency_AM);
      frequency_SW = frequency_AM;
      break;
    case SW_MI_BAND_160M:
      if (plus) {
        SWMIBandstringold = (String) "" + SWMIBandPosold + " m";
        SWMIBandPos = SW_MI_BAND_120M;
        SWMIBandPosold = SWMIBandPos;
        SWMIBandstring = (String) "" + SWMIBandPos + " m";
        frequency_AM = frequency_MIBand_120M == 0 ? FREQ_SW_120M_START : frequency_MIBand_120M;
      } else {
        SWMIBandstringold = (String) "" + SWMIBandPosold + " m";
        SWMIBandPos = SW_MI_BAND_11M;
        SWMIBandPosold = SWMIBandPos;
        SWMIBandstring = (String) "" + SWMIBandPos + " m";
        frequency_AM = frequency_MIBand_11M == 0 ? FREQ_SW_49M_END : frequency_MIBand_11M;
      }
      radio.SetFreqAM(frequency_AM);
      frequency_SW = frequency_AM;
      break;
  }
}

void SelectBand() {
  if (band != BAND_FM) {
    seek = false;
    if (tunemode == TUNE_AUTO) tunemode = TUNE_MAN;
    if (tunemode == TUNE_MI_BAND && band != BAND_SW) tunemode = TUNE_MAN;
    BWreset = true;
    BWset = 2;
    freqold = frequency_AM;
    LimitAMFrequency();
    radio.SetFreqAM(frequency_AM);
    doBW;
    radio.getStatusAM(SStatus, USN, WAM, OStatus, BW, MStatus, SNR);
    if (screenmute == false) radio.clearRDS(fullsearchrds); BuildDisplay();
    tft.setFreeFont(FONT7);
    if (region == 0) tft.drawString("PI:", 216, 191, GFXFF);
    if (region == 1) tft.drawString("ID:", 216, 191, GFXFF);
    tft.drawString("PS:", 6, 191, GFXFF);
    tft.drawString("PTY:", 6, 164, GFXFF);
    tft.drawBitmap(110, 5, RDSLogo, 67, 22, GreyoutColor);
    tft.drawRoundRect(249, 56, 30, 20, 5, GreyoutColor);
    tft.setTextColor(GreyoutColor);
    tft.drawCentreString("iMS", 264, 54, GFXFF);
    tft.drawRoundRect(287, 56, 30, 20, 5, GreyoutColor);
    tft.setTextColor(GreyoutColor);
    tft.drawCentreString("EQ", 302, 54, GFXFF);
  } else {
    LowLevelInit == false;
    BWreset = true;
    BWset = 0;
    if (tunemode == TUNE_MI_BAND) tunemode = TUNE_MAN;
    radio.power(0);
    delay(50);
    radio.SetFreq(frequency);
    freqold = frequency_AM;
    doBW;
    radio.getStatus(SStatus, USN, WAM, OStatus, BW, MStatus, SNR);
    if (screenmute == false) radio.clearRDS(fullsearchrds); BuildDisplay();
  }
}

void BWButtonPress() {
  if (menu == false) {
    seek = false;
    unsigned long counterold = millis();
    unsigned long counter = millis();
    while (digitalRead(BWBUTTON) == LOW && counter - counterold <= 1000) counter = millis();

    if (counter - counterold < 1000) {
      BWset++;
      doBW();
    } else {
      doStereoToggle();
    }
    if (screensaverset) {
      ScreensaverTimerRestart();
    }
  }

  while (digitalRead(BWBUTTON) == LOW) delay(50);
  delay(100);
}

void doStereoToggle() {
  if (StereoToggle == true) {
    if (screenmute == false) {
      tft.drawCircle(81, 15, 10, BackgroundColor);
      tft.drawCircle(81, 15, 9, BackgroundColor);
      tft.drawCircle(91, 15, 10, BackgroundColor);
      tft.drawCircle(91, 15, 9, BackgroundColor);
      tft.drawCircle(86, 15, 10, SecondaryColor);
      tft.drawCircle(86, 15, 9, SecondaryColor);
    }
    radio.setMono(true);
    StereoToggle = false;
  } else {
    if (screenmute == false) {
      tft.drawCircle(86, 15, 10, BackgroundColor);
      tft.drawCircle(86, 15, 9, BackgroundColor);
    }
    radio.setMono(false);
    Stereostatusold = false;
    StereoToggle = true;
  }
}

void ModeButtonPress() {
  if (advancedRDS) {
    BuildDisplay();
    ScreensaverTimerReopen();
  } else if (afscreen == true) {
    if (afpagenr == 1) afpagenr = 2; else if (afpagenr == 2) afpagenr = 1;
    if (afpagenr != 0) BuildAFScreen();
  } else {
    if (menu == false) {
      seek = false;
      unsigned long counterold = millis();
      unsigned long counter = millis();
      while (digitalRead(MODEBUTTON) == LOW && counter - counterold <= 1000) counter = millis();

      if (counter - counterold <= 1000) {
        doTuneMode();
        if (screensaverset) {
          ScreensaverTimerRestart();
        }
      } else {
        if (XDRGTKUSB == true || XDRGTKTCP == true) {
          ShowFreq(1);
          tft.setFreeFont(FONT14);
          tft.setTextColor(ActiveColor, BackgroundColor);
          tft.setCursor (70, 60);
          tft.drawString(myLanguage[language][86], 70, 60, GFXFF);
          delay(1000);
          tft.setTextColor(BackgroundColor);
          tft.drawString(myLanguage[language][86], 70, 60, GFXFF);
          ShowFreq(0);
        } else {
          if (menu == false) {
            BuildMenu();
            menu = true;
            ScreensaverTimerSet(OFF);
          }
        }
      }
    } else {
      OStatusold = 1000;
      Stereostatusold = false;
      SStatusold = 2000;
      BWOld = 0;
      radio.clearRDS(fullsearchrds);
      RDSstatus = 0;
      if (specialstepOIRT) {
        if (frequency >= (FREQ_FM_OIRT_START) && frequency <= (FREQ_FM_OIRT_END)) {
          if (frequency % 3 != 0) {
            Round30K(frequency);
            EEPROM.writeUInt(EE_UINT_FREQUENCY_FM, frequency);
          }
        } else {
          if (fmdefaultstepsize == 1) Round100K(frequency); else Round50K(frequency);
        }
      } else {
        if (frequency % 10 != 0) {
          if (fmdefaultstepsize == 1) Round100K(frequency); else Round50K(frequency);
          EEPROM.writeUInt(EE_UINT_FREQUENCY_FM, frequency);
        }
      }
      radio.clearRDS(fullsearchrds);
      BuildDisplay();
      ShowSignalLevel();
      ShowBW();
      menu = false;
      menuopen = false;
      LowLevelInit = true;
      EEPROM.writeInt(EE_INT_VOLSET, VolSet);
      EEPROM.writeUInt(EE_UINT_CONVERTERSET, ConverterSet);
      EEPROM.writeUInt(EE_UINT_FMLOWEDGESET, LowEdgeSet);
      EEPROM.writeUInt(EE_UINT_FMHIGHEDGESET, HighEdgeSet);
      EEPROM.writeByte(EE_BYTE_CONTRASTSET, ContrastSet);
      EEPROM.writeByte(EE_BYTE_STEREOLEVEL, StereoLevel);
      EEPROM.writeByte(EE_BYTE_HIGHCUTLEVEL, HighCutLevel);
      EEPROM.writeByte(EE_BYTE_HIGHCUTOFFSET, HighCutOffset);
      EEPROM.writeInt(EE_INT_LEVELOFFSET, LevelOffset);
      EEPROM.writeByte(EE_BYTE_EDGEBEEP, edgebeep);
      EEPROM.writeByte(EE_BYTE_SOFTMUTEAM, softmuteam);
      EEPROM.writeByte(EE_BYTE_SOFTMUTEFM, softmutefm);
      EEPROM.writeByte(EE_BYTE_LANGUAGE, language);
      EEPROM.writeByte(EE_BYTE_SHOWRDSERRORS, showrdserrors);
      EEPROM.writeInt(EE_INT_LOWLEVELSET, LowLevelSet);
      EEPROM.writeByte(EE_BYTE_REGION, region);
      EEPROM.writeByte(EE_BYTE_RDS_UNDERSCORE, radio.rds.underscore);
      EEPROM.writeByte(EE_BYTE_USBMODE, USBmode);
      EEPROM.writeByte(EE_BYTE_WIFI, wifi);
      EEPROM.writeByte(EE_BYTE_SUBNETCLIENT, subnetclient);
      EEPROM.writeByte(EE_BYTE_SHOWSWMIBAND, showSWMIBand);
      EEPROM.writeByte(EE_BYTE_RDS_FILTER, radio.rds.filter);
      EEPROM.writeByte(EE_BYTE_RDS_PIERRORS, radio.rds.pierrors);
      EEPROM.writeByte(EE_BYTE_SHOWSQUELCH, showsquelch);
      EEPROM.writeByte(EE_BYTE_SHOWMODULATION, showmodulation);
      EEPROM.writeByte(EE_BYTE_AM_NB, amnb);
      EEPROM.writeByte(EE_BYTE_FM_NB, fmnb);
      EEPROM.writeByte(EE_BYTE_AUDIOMODE, audiomode);
      EEPROM.writeByte(EE_BYTE_OIRT, specialstepOIRT);
      EEPROM.writeUInt(EE_UINT_LOWEDGEOIRTSET, LowEdgeOIRTSet);
      EEPROM.writeUInt(EE_UINT_HIGHEDGEOIRTSET, HighEdgeOIRTSet);
      EEPROM.writeByte(EE_BYTE_COLORINVERT, colorinvert);
      EEPROM.writeByte(EE_BYTE_POWEROPTIONS, poweroptions);
      EEPROM.writeByte(EE_BYTE_CURRENTTHEME, CurrentTheme);
      EEPROM.writeByte(EE_BYTE_FMDEFAULTSTEPSIZE, fmdefaultstepsize);
      EEPROM.writeByte(EE_BYTE_SCREENSAVERSET, screensaverset);
      EEPROM.writeInt(EE_INT_AMLEVELOFFSET, AMLevelOffset);
      EEPROM.writeByte(EE_BYTE_UNIT, unit);
      EEPROM.writeByte(EE_BYTE_AF, af);
      EEPROM.commit();
      Serial.end();
      if (wifi) remoteip = IPAddress (WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], subnetclient);
      if (USBmode) Serial.begin(19200); else Serial.begin(115200);
      ScreensaverTimerSet(screensaverOptions[screensaverset]);
      if (screensaverset) ScreensaverTimerRestart();
    }
  }
  while (digitalRead(MODEBUTTON) == LOW) delay(50);
  delay(100);
}

void ShowStepSize() {
  if (!advancedRDS) {
    tft.fillRect(224, 38, 15, 4, GreyoutColor);
    tft.fillRect(193, 38, 15, 4, GreyoutColor);
    if (band == BAND_FM) tft.fillRect(148, 38, 15, 4, GreyoutColor); else tft.fillRect(162, 38, 15, 4, GreyoutColor);
    if (band == BAND_FM) tft.fillRect(116, 38, 15, 4, GreyoutColor); else tft.fillRect(128, 38, 15, 4, GreyoutColor);
    if (stepsize == 1) tft.fillRect(224, 38, 15, 4, TFT_GREEN);
    if (stepsize == 2) tft.fillRect(193, 38, 15, 4, TFT_GREEN);
    if (stepsize == 3) {
      if (band == BAND_FM) tft.fillRect(148, 38, 15, 4, TFT_GREEN); else tft.fillRect(162, 38, 15, 4, TFT_GREEN);
    }
    if (stepsize == 4) {
      if (band == BAND_FM) tft.fillRect(116, 38, 15, 4, TFT_GREEN); else tft.fillRect(128, 38, 15, 4, TFT_GREEN);
    }
  }
}

void FindhighStopOIRT() {
  if (HighEdgeSet >= (FREQ_FM_OIRT_START / 10) && HighEdgeSet <= (FREQ_FM_OIRT_END / 10)) {
    HighEdgeOIRTSet = (HighEdgeSet * 10 - (HighEdgeSet * 10) % 3);
  } else {
    HighEdgeOIRTSet = 0;
  }
}

void FindlowStopOIRT() {
  if (LowEdgeSet >= (FREQ_FM_OIRT_START / 10) && LowEdgeSet <= (FREQ_FM_OIRT_END / 10)) {
    LowEdgeOIRTSet = (LowEdgeSet * 10 - (LowEdgeSet * 10) % 3);
  } else {
    LowEdgeOIRTSet = 0;
  }
}

void Round30K(unsigned int freq) {
  if (freq % 3 < 3) {
    frequency = (freq - freq % 3);
  }
}

void Round50K(unsigned int freq) {
  if (freq % 10 < 3) {
    frequency = (freq - freq % 10);
  }
  else if (freq % 10 > 2 && freq % 10 < 8) {
    frequency = (freq - (freq % 10 - 5));
  }
  else if (freq % 10 > 7) {
    frequency = (freq - (freq % 10) + 10);
  }
}

void Round100K(unsigned int freq) {
  if (freq % 10 < 5) {
    frequency = (freq - freq % 10);
  } else {
    frequency = (freq - (freq % 10) + 10);
  }
}

void Round5K(unsigned int freqAM) {
  if (freqAM % 10 < 3) {
    frequency_AM = (freqAM - freqAM % 10);
  }
  else if (freqAM % 10 > 2 && freqAM % 10 < 8) {
    frequency_AM = (freqAM - (freqAM % 10 - 5));
  }
  else if (freqAM % 10 > 7) {
    frequency_AM = (freqAM - (freqAM % 10) + 10);
  }
}

void RoundStep() {
  if (band == BAND_FM) {
    unsigned int freq = frequency;
    if (specialstepOIRT) {
      if (frequency >= FREQ_FM_OIRT_START && frequency <= FREQ_FM_OIRT_END) {
        Round30K(freq);
      } else {
        if (fmdefaultstepsize == 1) Round100K(freq); else Round50K(freq);
      }
    } else {
      if (fmdefaultstepsize == 1) Round100K(freq); else Round50K(freq);
    }
    radio.SetFreq(frequency);
  } else {
    if (band == BAND_MW) {
      unsigned int freq = frequency_AM / (region == 0 ? FREQ_MW_STEP_9K : FREQ_MW_STEP_10K);
      frequency_AM = freq * (region == 0 ? FREQ_MW_STEP_9K : FREQ_MW_STEP_10K);
      radio.SetFreqAM(frequency_AM);
    } else if (band == BAND_SW) {
      Round5K(frequency_AM);
      radio.SetFreqAM(frequency_AM);
    }
  }

  while (digitalRead(ROTARY_BUTTON) == LOW) delay(50);

  if (band == BAND_FM) EEPROM.writeUInt(EE_UINT_FREQUENCY_FM, frequency); else EEPROM.writeUInt(EE_UINT_FREQUENCY_AM, frequency_AM);
  EEPROM.commit();
}

void ButtonPress() {
  if (advancedRDS) BuildDisplay();
  if (menu == false) {
    if (tunemode == TUNE_MEM) {
      if (memorystore == false) {
        memorystore = true;
        ShowTuneMode();
      } else {
        memorystore = false;
        EEPROM.writeByte(memorypos + EE_PRESETS_BAND_START, band);
        if (band == BAND_FM) EEPROM.writeUInt((memorypos * 4) + EE_PRESETS_START, frequency); else EEPROM.writeUInt((memorypos * 4) + EE_PRESETS_START, frequency_AM);
        EEPROM.commit();
        memoryband[memorypos] = band;
        if (band == BAND_FM) memory[memorypos] = frequency; else memory[memorypos] = frequency_AM;
        ShowTuneMode();
      }
    } else {
      seek = false;
      unsigned long counterold = millis();
      unsigned long counter = millis();
      while (digitalRead(ROTARY_BUTTON) == LOW && counter - counterold <= 1000) counter = millis();

      if (counter - counterold < 1000) {
        if (tunemode == TUNE_MAN) {
          stepsize++;
          if (band == BAND_SW || band == BAND_FM) {
            if (stepsize > 4) stepsize = 0;
          }
          else {
            if (stepsize > 3) stepsize = 0;
          }

          if (screenmute == false) ShowStepSize();

          EEPROM.writeByte(EE_BYTE_STEPSIZE, stepsize);
          EEPROM.commit();
          if (stepsize == 0) {
            RoundStep();
            ShowFreq(0);
          }
        }
      } else {
        if (iMSEQ == 0) iMSEQ = 1;

        if (iMSEQ == 4) {
          iMSset = 0;
          EQset = 0;
          updateiMS();
          updateEQ();
          iMSEQ = 0;
        }
        if (iMSEQ == 3) {
          iMSset = 1;
          EQset = 0;
          updateiMS();
          updateEQ();
          iMSEQ = 4;
        }
        if (iMSEQ == 2) {
          iMSset = 0;
          EQset = 1;
          updateiMS();
          updateEQ();
          iMSEQ = 3;
        }
        if (iMSEQ == 1) {
          iMSset = 1;
          EQset = 1;
          updateiMS();
          updateEQ();
          iMSEQ = 2;
        }
        EEPROM.writeByte(EE_BYTE_IMSSET, iMSset);
        EEPROM.writeByte(EE_BYTE_EQSET, EQset);
        EEPROM.commit();
      }
    }
    if (screensaverset) {
      ScreensaverTimerRestart();
    }
  } else {
    if (menuopen == false) {
      menuopen = true;
      tft.drawRoundRect(20, 30, 274, 170, 5, ActiveColor);
      tft.fillRoundRect(22, 32, 270, 166, 5, BackgroundColor);
      tft.setFreeFont(FONT14);
      switch (menupage) {
        case 1:
          switch (menuoption) {
            case 30:
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawCentreString(myLanguage[language][10], 155, 70, GFXFF);
              tft.drawString("dB", 170, 110, GFXFF);
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              if (VolSet > 0) tft.drawRightString("+" + String(VolSet, DEC), 155, 110, GFXFF); else tft.drawRightString(String(VolSet, DEC), 155, 110, GFXFF);
              break;

            case 50:
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawCentreString(myLanguage[language][11], 155, 70, GFXFF);
              tft.drawString("MHz", 170, 110, GFXFF);
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);

              tft.drawRightString(String(ConverterSet, DEC), 155, 110, GFXFF);
              break;

            case 70:
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawCentreString(myLanguage[language][12], 155, 70, GFXFF);
              tft.drawString("MHz", 170, 110, GFXFF);
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawRightString(String(LowEdgeSet / 10 + ConverterSet, DEC) + "." + String(LowEdgeSet % 10 + ConverterSet, DEC), 155, 110, GFXFF);
              break;

            case 90:
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawCentreString(myLanguage[language][13], 155, 70, GFXFF);
              tft.drawString("MHz", 170, 110, GFXFF);
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawRightString(String(HighEdgeSet / 10 + ConverterSet, DEC) + "." + String(HighEdgeSet % 10 + ConverterSet, DEC), 155, 110, GFXFF);
              break;

            case 110:
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawCentreString(myLanguage[language][14], 155, 70, GFXFF);
              tft.drawString("dB", 170, 110, GFXFF);
              tft.drawString("dBμV", 190, 157, GFXFF);
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              if (LevelOffset > 0) tft.drawRightString("+" + String(LevelOffset, DEC), 155, 110, GFXFF); else tft.drawRightString(String(LevelOffset, DEC), 155, 110, GFXFF);
              SStatusold = 2000;
              change2 = true;
              break;

            case 130:
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawCentreString(myLanguage[language][15], 155, 70, GFXFF);
              if (StereoLevel != 0) tft.drawString("dBμV", 170, 110, GFXFF);
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              if (StereoLevel != 0) tft.drawRightString(String(StereoLevel, DEC), 155, 110, GFXFF); else tft.drawRightString(myLanguage[language][30], 155, 110, GFXFF);
              break;

            case 150:
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawCentreString(myLanguage[language][16], 155, 70, GFXFF);
              if (HighCutLevel != 0) tft.drawString("Hz", 170, 110, GFXFF);
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              if (HighCutLevel != 0) tft.drawRightString(String(HighCutLevel * 100, DEC), 155, 110, GFXFF); else tft.drawRightString(myLanguage[language][30], 155, 110, GFXFF);
              break;

            case 170:
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawCentreString(myLanguage[language][17], 155, 70, GFXFF);
              if (HighCutOffset != 0) tft.drawString("dBμV", 170, 110, GFXFF);
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              if (HighCutOffset != 0) tft.drawRightString(String(HighCutOffset, DEC), 155, 110, GFXFF); else tft.drawRightString(myLanguage[language][30], 155, 110, GFXFF);
              break;

            case 190:
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawCentreString(myLanguage[language][18], 155, 70, GFXFF);
              tft.drawString("dBμV", 155, 110, GFXFF);
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawRightString(String(LowLevelSet, DEC), 145, 110, GFXFF);
              break;

            case 210:
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawCentreString(myLanguage[language][19], 155, 70, GFXFF);
              tft.drawString("%", 170, 110, GFXFF);
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawRightString(String(ContrastSet, DEC), 155, 110, GFXFF);
              break;
          }
          break;

        case 2:
          switch (menuoption) {
            case 30:
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawCentreString(myLanguage[language][40], 155, 70, GFXFF);
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawCentreString(myLanguage[language][0], 155, 110, GFXFF);
              break;

            case 50:
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawCentreString(myLanguage[language][38], 155, 70, GFXFF);
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              if (showrdserrors) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
              break;

            case 70:
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawCentreString(myLanguage[language][43], 155, 70, GFXFF);
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              if (softmutefm) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
              break;

            case 90:
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawCentreString(myLanguage[language][44], 155, 70, GFXFF);
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              if (softmuteam) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
              break;

            case 110:
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawCentreString(myLanguage[language][45], 155, 70, GFXFF);
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              if (edgebeep) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
              break;

            case 130:
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawCentreString(myLanguage[language][46], 155, 70, GFXFF);
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              if (region == 0) tft.drawCentreString(myLanguage[language][47], 155, 110, GFXFF);
              if (region == 1) tft.drawCentreString(myLanguage[language][48], 155, 110, GFXFF);
              break;

            case 150:
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawCentreString(myLanguage[language][49], 155, 70, GFXFF);
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              if (radio.rds.underscore) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
              break;

            case 170:
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawCentreString(myLanguage[language][50], 155, 70, GFXFF);
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              if (USBmode) tft.drawCentreString("RDS Spy", 155, 110, GFXFF); else tft.drawCentreString("XDR-GTK", 155, 110, GFXFF);
              break;

            case 190:
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawCentreString(myLanguage[language][51], 155, 70, GFXFF);
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              if (wifi) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
              break;

            case 210:
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawCentreString(myLanguage[language][53], 155, 50, GFXFF);
              tft.drawCentreString("ESP_" + String(ESP_getChipId()), 155, 90, GFXFF);
              tft.drawCentreString(myLanguage[language][54], 155, 130, GFXFF);
              tft.setFreeFont(FONT7);
              tft.drawCentreString("http://192.168.4.1", 155, 170, GFXFF);
              char key [9];
              XDRGTK_key.toCharArray(key, 9);
              WiFiConnectParam XDRGTK_key_text("Set XDRGTK Password: (max 8 characters)");
              WiFiConnectParam XDRGTK_key_input("XDRGTK_key", "Password", key, 9);
              wc.addParameter(&XDRGTK_key_text);
              wc.addParameter(&XDRGTK_key_input);
              wc.startConfigurationPortal(AP_WAIT);
              XDRGTK_key = XDRGTK_key_input.getValue();
              EEPROM.writeString(EE_STRING_XDRGTK_KEY, XDRGTK_key);
              EEPROM.commit();
              tryWiFi();
              delay(2000);
              BuildMenu();
              break;
          }
          break;

        case 3:
          switch (menuoption) {
            case 30:
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawCentreString(myLanguage[language][58], 155, 70, GFXFF);
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawCentreString(String(WiFi.localIP()[0]) + "." + String(WiFi.localIP()[1]) + "." + String(WiFi.localIP()[2]) + "." + String(subnetclient, DEC), 155, 110, GFXFF);
              break;

            case 50:
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawCentreString(myLanguage[language][59], 155, 70, GFXFF);
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              if (showSWMIBand) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
              break;

            case 70:
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawCentreString(myLanguage[language][60], 155, 70, GFXFF);
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              if (radio.rds.filter) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
              break;

            case 90:
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawCentreString(myLanguage[language][61], 155, 70, GFXFF);
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              if (radio.rds.pierrors) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
              break;

            case 110:
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawCentreString(myLanguage[language][62], 155, 70, GFXFF);
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              if (showsquelch) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
              break;

            case 130:
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawCentreString(myLanguage[language][63], 155, 70, GFXFF);
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              if (showmodulation) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
              break;

            case 150:
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawCentreString(myLanguage[language][64], 155, 70, GFXFF);
              if (amnb != 0) tft.drawString("%", 170, 110, GFXFF);
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              if (amnb != 0) tft.drawRightString(String(amnb, DEC), 155, 110, GFXFF); else tft.drawRightString(myLanguage[language][30], 155, 110, GFXFF);
              break;

            case 170:
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawCentreString(myLanguage[language][65], 155, 70, GFXFF);
              if (fmnb != 0) tft.drawString("%", 170, 110, GFXFF);
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              if (fmnb != 0) tft.drawRightString(String(fmnb, DEC), 155, 110, GFXFF); else tft.drawRightString(myLanguage[language][30], 155, 110, GFXFF);
              break;

            case 190:
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawCentreString(myLanguage[language][67], 155, 70, GFXFF);
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              if (audiomode) tft.drawCentreString("MPX", 155, 110, GFXFF); else tft.drawCentreString("Stereo", 155, 110, GFXFF);
              break;

            case 210:
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawCentreString(myLanguage[language][68], 155, 70, GFXFF);
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              if (specialstepOIRT) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
              break;
          }
          break;

        case 4:
          switch (menuoption) {
            case 30:
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawCentreString(myLanguage[language][77], 155, 70, GFXFF);
              tft.setTextColor(PrimaryColor);
              tft.drawCentreString(CurrentThemeString, 155, 110, GFXFF);
              break;

            case 50:
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawCentreString(myLanguage[language][71], 155, 30, GFXFF);
              tft.drawCentreString(myLanguage[language][72], 155, 80, GFXFF);
              tft.setFreeFont(FONT7);
              tft.setTextColor(PrimaryColor);
              tft.drawCentreString("PE5PVB", 155, 60, GFXFF);
              tft.drawRightString("ohmytime", 145, 110, GFXFF);
              tft.drawRightString("HyperDX", 145, 125, GFXFF);
              tft.drawString("MCelliotG", 155, 110, GFXFF);
              tft.drawString("andimik", 155, 125, GFXFF);
              tft.drawRightString("DXHR05", 145, 140, GFXFF);
              tft.drawRightString("NoobishSVK", 145, 155, GFXFF);
              tft.drawString("yo2ldk", 155, 140, GFXFF);
              tft.drawString("Justin_Peng(Portable)", 155, 155, GFXFF);
              tft.setTextColor(ActiveColor);
              tft.drawCentreString("https://github.com/PE5PVB/TEF6686_ESP32", 155, 175, GFXFF);
              break;
            case 70:
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawCentreString(myLanguage[language][74], 155, 70, GFXFF);
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              ShowPowerOptions(true);
              break;
            case 90:
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawCentreString(myLanguage[language][90], 155, 70, GFXFF);
              tft.drawString("KHz", 170, 110, GFXFF);
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              if (fmdefaultstepsize) tft.drawRightString(String(FREQ_FM_STEP_100K * 10, DEC), 155, 110, GFXFF); else tft.drawRightString(String(FREQ_FM_STEP_50K * 10, DEC), 155, 110, GFXFF);
              break;
            case 110:
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawCentreString(myLanguage[language][91], 155, 70, GFXFF);
              if (screensaverset) tft.drawString(myLanguage[language][92], 170, 110, GFXFF);
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              if (!screensaverset) tft.drawRightString(myLanguage[language][30], 155, 110, GFXFF); else tft.drawRightString(String(screensaverOptions[screensaverset], DEC), 155, 110, GFXFF);
              break;
            case 130:
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawCentreString(myLanguage[language][97], 155, 70, GFXFF);
              tft.drawString("dB", 170, 110, GFXFF);
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              if (AMLevelOffset > 0) tft.drawRightString("+" + String(AMLevelOffset, DEC), 155, 110, GFXFF); else tft.drawRightString(String(AMLevelOffset, DEC), 155, 110, GFXFF);
              break;
            case 150:
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawCentreString(myLanguage[language][98], 155, 70, GFXFF);
              tft.setTextColor(PrimaryColor);
              tft.drawCentreString(unitString[unit], 155, 110, GFXFF);
              break;
            case 170:
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              tft.drawCentreString(myLanguage[language][99], 155, 70, GFXFF);
              if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
              if (af) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
              break;
          }
          break;
      }
    } else {
      if (menupage == 2 && menuoption == 190 && wifi == true) {
        tryWiFi();
        delay(2000);
      }
      menuopen = false;
      BuildMenu();
    }
  }
  while (digitalRead(ROTARY_BUTTON) == LOW) delay(50);
}

void KeyUp() {
  rotary = 0;
  if (!afscreen) {
    if (menu == false) {
      switch (tunemode) {
        case TUNE_MAN:
          TuneUp();
          break;

        case TUNE_AUTO:
          direction = true;
          seek = true;
          Seek(direction);
          break;

        case TUNE_MEM:
          memorypos++;
          if (memorypos > EE_PRESETS_CNT - 1) memorypos = 0;
          ShowMemoryPos();
          if (memorystore == false) DoMemoryPosTune();
          EEPROM.writeByte(EE_BYTE_MEMORYPOS, memorypos);
          EEPROM.commit();
          break;
        case TUNE_MI_BAND:
          if (showSWMIBand) {
            if (displayflip) {
              ToggleSWMIBand(false);
            } else {
              ToggleSWMIBand(true);
            }
          }
          break;
      }
        if (XDRGTKUSB == true || XDRGTKTCP == true) if (band == BAND_FM) DataPrint("T" + String(frequency * 10)); else DataPrint("T" + String(frequency_AM));
      radio.clearRDS(fullsearchrds);
      change = 0;
      ShowFreq(0);
      store = true;
    } else {
      if (menuopen == false) {
        tft.drawRoundRect(8, menuoption + 3, 302, 19, 5, BackgroundColor);
        menuoption += 20;
        if (menuoption > 210) {
          menupage++;
          if (menupage > menupagestotal) menupage = 1;
          menuoption = 30;
          BuildMenu();
        }
        tft.drawRoundRect(8, menuoption + 3, 302, 19, 5, ActiveColor);
      } else {
        switch (menupage) {
          case 1:
            switch (menuoption) {
              case 30:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                if (VolSet > 0) tft.drawRightString("+" + String(VolSet, DEC), 155, 110, GFXFF); else tft.drawRightString(String(VolSet, DEC), 155, 110, GFXFF);
                VolSet++;
                if (VolSet > 10) VolSet = 10;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (VolSet > 0) tft.drawRightString("+" + String(VolSet, DEC), 155, 110, GFXFF); else tft.drawRightString(String(VolSet, DEC), 155, 110, GFXFF);
                radio.setVolume(VolSet);
                break;

              case 50:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                tft.drawRightString(String(ConverterSet, DEC), 155, 110, GFXFF);
                ConverterSet++;
                  if (ConverterSet > 2400 || ConverterSet <= 200) if (ConverterSet == 1) ConverterSet = 200; else ConverterSet = 0;
                if (ConverterSet >= 200) {
                  Wire.beginTransmission(0x12);
                  Wire.write(ConverterSet >> 8);
                  Wire.write(ConverterSet & (0xFF));
                  Wire.endTransmission();
                }
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                tft.drawRightString(String(ConverterSet, DEC), 155, 110, GFXFF);
                break;

              case 70:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                tft.drawRightString(String(LowEdgeSet / 10 + ConverterSet, DEC) + "." + String(LowEdgeSet % 10 + ConverterSet, DEC), 155, 110, GFXFF);
                LowEdgeSet ++;
                if (LowEdgeSet > 1070) LowEdgeSet = 650;
                if (specialstepOIRT) {
                  FindlowStopOIRT();
                  FindhighStopOIRT();
                }
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                tft.drawRightString(String(LowEdgeSet / 10 + ConverterSet, DEC) + "." + String(LowEdgeSet % 10 + ConverterSet, DEC), 155, 110, GFXFF);
                break;

              case 90:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                tft.drawRightString(String(HighEdgeSet / 10 + ConverterSet, DEC) + "." + String(HighEdgeSet % 10 + ConverterSet, DEC), 155, 110, GFXFF);
                HighEdgeSet ++;
                if (HighEdgeSet > 1080) HighEdgeSet = 660;
                if (specialstepOIRT) {
                  FindlowStopOIRT();
                  FindhighStopOIRT();
                }
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                tft.drawRightString(String(HighEdgeSet / 10 + ConverterSet, DEC) + "." + String(HighEdgeSet % 10 + ConverterSet, DEC), 155, 110, GFXFF);
                break;

              case 110:
                tft.setFreeFont(FONT14);
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                if (LevelOffset > 0) tft.drawRightString("+" + String(LevelOffset, DEC), 155, 110, GFXFF); else tft.drawRightString(String(LevelOffset, DEC), 155, 110, GFXFF);
                LevelOffset++;
                if (LevelOffset > 15) LevelOffset = -25;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (LevelOffset > 0) tft.drawRightString("+" + String(LevelOffset, DEC), 155, 110, GFXFF); else tft.drawRightString(String(LevelOffset, DEC), 155, 110, GFXFF);
                radio.setOffset(LevelOffset);
                change2 = true;
                break;

              case 130:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                tft.drawRightString(String(StereoLevel, DEC), 155, 110, GFXFF);
                StereoLevel ++;
                  if (StereoLevel > 60 || StereoLevel <= 30) if (StereoLevel == 1) StereoLevel = 30; else StereoLevel = 0;
                tft.drawRightString(myLanguage[language][30], 155, 110, GFXFF);
                tft.drawString("dBμV", 170, 110, GFXFF);
                tft.setTextColor(ActiveColor);
                if (StereoLevel != 0) tft.drawString("dBμV", 170, 110, GFXFF);
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (StereoLevel != 0) tft.drawRightString(String(StereoLevel, DEC), 155, 110, GFXFF); else tft.drawRightString(myLanguage[language][30], 155, 110, GFXFF);
                radio.setStereoLevel(StereoLevel);
                break;

              case 150:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                tft.drawRightString(String(HighCutLevel * 100, DEC), 155, 110, GFXFF);
                HighCutLevel ++;
                if (HighCutLevel > 70) HighCutLevel = 15;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                tft.drawRightString(String(HighCutLevel * 100, DEC), 155, 110, GFXFF);
                radio.setHighCutLevel(HighCutLevel);
                break;

              case 170:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                tft.drawRightString(String(HighCutOffset, DEC), 155, 110, GFXFF);
                HighCutOffset ++;
                  if (HighCutOffset > 60 || HighCutOffset <= 20) if (HighCutOffset == 1) HighCutOffset = 20; else HighCutOffset = 0;
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                tft.drawRightString(myLanguage[language][30], 155, 110, GFXFF);
                tft.drawString("dBμV", 170, 110, GFXFF);
                tft.setTextColor(ActiveColor);
                if (HighCutOffset != 0) tft.drawString("dBμV", 170, 110, GFXFF);
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (HighCutOffset != 0) tft.drawRightString(String(HighCutOffset, DEC), 155, 110, GFXFF); else tft.drawRightString(myLanguage[language][30], 155, 110, GFXFF);
                radio.setHighCutOffset(HighCutOffset);
                break;

              case 190:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                tft.drawRightString(String(LowLevelSet, DEC), 145, 110, GFXFF);
                LowLevelSet++;
                if (LowLevelSet > 40) LowLevelSet = -10;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                tft.drawRightString(String(LowLevelSet, DEC), 145, 110, GFXFF);
                break;

              case 210:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                tft.drawRightString(String(ContrastSet, DEC), 155, 110, GFXFF);
                ContrastSet ++;
                if (ContrastSet > 100) ContrastSet = 1;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                tft.drawRightString(String(ContrastSet, DEC), 155, 110, GFXFF);
                analogWrite(CONTRASTPIN, ContrastSet * 2 + 27);
                break;
            }
            break;

          case 2:
            switch (menuoption) {
              case 30:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                tft.drawCentreString(myLanguage[language][0], 155, 110, GFXFF);
                language ++;
                if (language == (sizeof (myLanguage) / sizeof (myLanguage[0]))) language = 0;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                tft.drawCentreString(myLanguage[language][0], 155, 110, GFXFF);
                break;

              case 50:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                if (showrdserrors) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                if (showrdserrors) showrdserrors = false; else showrdserrors = true;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (showrdserrors) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                break;

              case 70:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                if (softmutefm) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                if (softmutefm) softmutefm = false; else softmutefm = true;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (softmutefm) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                radio.setSoftmuteFM(softmutefm);
                break;

              case 90:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                if (softmuteam) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                if (softmuteam) softmuteam = false; else softmuteam = true;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (softmuteam) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                radio.setSoftmuteAM(softmuteam);
                break;

              case 110:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                if (edgebeep) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                if (edgebeep) edgebeep = false; else edgebeep = true;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (edgebeep) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                break;

              case 130:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                if (region == 0) region = 1; else region = 0;
                if (regionold == 0) tft.drawCentreString(myLanguage[language][47], 155, 110, GFXFF);
                if (regionold == 1) tft.drawCentreString(myLanguage[language][48], 155, 110, GFXFF);
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (region == 0) tft.drawCentreString(myLanguage[language][47], 155, 110, GFXFF);
                if (region == 1) tft.drawCentreString(myLanguage[language][48], 155, 110, GFXFF);
                regionold = region;
                if (region == 0) radio.setDeemphasis(1);
                if (region == 1) radio.setDeemphasis(2);
                radio.rds.region = region;
                break;

              case 150:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                if (radio.rds.underscore) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                if (radio.rds.underscore) radio.rds.underscore = false; else radio.rds.underscore = true;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (radio.rds.underscore) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                break;

              case 170:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                if (USBmode) tft.drawCentreString("RDS Spy", 155, 110, GFXFF); else tft.drawCentreString("XDR-GTK", 155, 110, GFXFF);
                if (USBmode) USBmode = false; else USBmode = true;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (USBmode) tft.drawCentreString("RDS Spy", 155, 110, GFXFF); else tft.drawCentreString("XDR-GTK", 155, 110, GFXFF);
                break;

              case 190:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                if (wifi) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                if (wifi) wifi = false; else wifi = true;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (wifi) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                break;
            }
            break;

          case 3:
            switch (menuoption) {
              case 30:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                tft.drawCentreString(String(WiFi.localIP()[0]) + "." + String(WiFi.localIP()[1]) + "." + String(WiFi.localIP()[2]) + "." + String(subnetclient, DEC), 155, 110, GFXFF);
                subnetclient ++;
                if (subnetclient > 254) subnetclient = 1;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                tft.drawCentreString(String(WiFi.localIP()[0]) + "." + String(WiFi.localIP()[1]) + "." + String(WiFi.localIP()[2]) + "." + String(subnetclient, DEC), 155, 110, GFXFF);
                break;

              case 50:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                if (showSWMIBand) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                if (showSWMIBand) showSWMIBand = false; else showSWMIBand = true;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (showSWMIBand) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                break;

              case 70:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                if (radio.rds.filter) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                if (radio.rds.filter) radio.rds.filter = false; else radio.rds.filter = true;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (radio.rds.filter) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                break;

              case 90:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                if (radio.rds.pierrors) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                if (radio.rds.pierrors) radio.rds.pierrors = false; else radio.rds.pierrors = true;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (radio.rds.pierrors) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                break;

              case 110:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                if (showsquelch) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                if (showsquelch) showsquelch = false; else showsquelch = true;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (showsquelch) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                break;

              case 130:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                if (showmodulation) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                if (showmodulation) showmodulation = false; else showmodulation = true;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (showmodulation) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                break;

              case 150:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                tft.drawRightString(String(amnb, DEC), 155, 110, GFXFF);
                amnb ++;
                  if (amnb > 150 || amnb <= 50) if (amnb == 1) amnb = 50; else amnb = 0;
                tft.drawRightString(myLanguage[language][30], 155, 110, GFXFF);
                tft.drawString("%", 170, 110, GFXFF);
                tft.setTextColor(ActiveColor);
                if (amnb != 0) tft.drawString("%", 170, 110, GFXFF);
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (amnb != 0) tft.drawRightString(String(amnb, DEC), 155, 110, GFXFF); else tft.drawRightString(myLanguage[language][30], 155, 110, GFXFF);
                radio.setAMNoiseBlanker(amnb);
                break;

              case 170:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                tft.drawRightString(String(fmnb, DEC), 155, 110, GFXFF);
                fmnb ++;
                  if (fmnb > 150 || fmnb <= 50) if (fmnb == 1) fmnb = 50; else fmnb = 0;
                tft.drawRightString(myLanguage[language][30], 155, 110, GFXFF);
                tft.drawString("%", 170, 110, GFXFF);
                tft.setTextColor(ActiveColor);
                if (fmnb != 0) tft.drawString("%", 170, 110, GFXFF);
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (fmnb != 0) tft.drawRightString(String(fmnb, DEC), 155, 110, GFXFF); else tft.drawRightString(myLanguage[language][30], 155, 110, GFXFF);
                radio.setFMNoiseBlanker(fmnb);
                break;

              case 190:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                if (audiomode) tft.drawCentreString("MPX", 155, 110, GFXFF); else tft.drawCentreString("Stereo", 155, 110, GFXFF);
                if (audiomode) audiomode = false; else audiomode = true;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (audiomode) tft.drawCentreString("MPX", 155, 110, GFXFF); else tft.drawCentreString("Stereo", 155, 110, GFXFF);
                radio.setAudio(audiomode);
                break;
              case 210:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                if (specialstepOIRT) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                if (specialstepOIRT) {
                  specialstepOIRT = 0;
                } else {
                  specialstepOIRT = 1;
                  FindlowStopOIRT();
                  FindhighStopOIRT();
                }
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (specialstepOIRT) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                break;
            }
            break;
          case 4:
            switch (menuoption) {
              case 30:
                tft.setTextColor(TFT_BLACK);
                tft.drawCentreString(CurrentThemeString, 155, 110, GFXFF);
                CurrentTheme ++;
                if (CurrentTheme > 7) CurrentTheme = 0;
                doTheme();
                BuildMenu(); menu == false; menuopen = false; ButtonPress(); //Fast preview theme
                tft.setTextColor(PrimaryColor);
                tft.drawCentreString(CurrentThemeString, 155, 110, GFXFF);
                break;

              case 70:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                ShowPowerOptions(true);
                poweroptions++;
                if (poweroptions > RADIO_POWER_MODE_CNT - 1) poweroptions = 0;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                ShowPowerOptions(true);
                break;

              case 90:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                if (fmdefaultstepsize) tft.drawRightString(String(FREQ_FM_STEP_100K * 10, DEC), 155, 110, GFXFF); else tft.drawRightString(String(FREQ_FM_STEP_50K * 10, DEC), 155, 110, GFXFF);
                if (fmdefaultstepsize) fmdefaultstepsize = 0; else fmdefaultstepsize = 1;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (fmdefaultstepsize) tft.drawRightString(String(FREQ_FM_STEP_100K * 10, DEC), 155, 110, GFXFF); else tft.drawRightString(String(FREQ_FM_STEP_50K * 10, DEC), 155, 110, GFXFF);
                break;

              case 110:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                if (screensaverset) tft.drawString(myLanguage[language][92], 170, 110, GFXFF);
                if (!screensaverset) tft.drawRightString(myLanguage[language][30], 155, 110, GFXFF); else tft.drawRightString(String(screensaverOptions[screensaverset], DEC), 155, 110, GFXFF);
                screensaverset ++;
                if (screensaverset > sizeof(screensaverOptions) / sizeof(screensaverOptions[0]) - 1) screensaverset = 0;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (screensaverset) tft.drawString(myLanguage[language][92], 170, 110, GFXFF);
                if (!screensaverset) tft.drawRightString(myLanguage[language][30], 155, 110, GFXFF); else tft.drawRightString(String(screensaverOptions[screensaverset], DEC), 155, 110, GFXFF);
                break;

              case 130:
                tft.setFreeFont(FONT14);
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                if (AMLevelOffset > 0) tft.drawRightString("+" + String(AMLevelOffset, DEC), 155, 110, GFXFF); else tft.drawRightString(String(AMLevelOffset, DEC), 155, 110, GFXFF);
                AMLevelOffset++;
                if (AMLevelOffset > 15) AMLevelOffset = -50;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (AMLevelOffset > 0) tft.drawRightString("+" + String(AMLevelOffset, DEC), 155, 110, GFXFF); else tft.drawRightString(String(AMLevelOffset, DEC), 155, 110, GFXFF);
                radio.setAMOffset(AMLevelOffset);
                break;

              case 150:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                tft.drawCentreString(unitString[unit], 155, 110, GFXFF);
                unit ++;
                if (unit > 2) unit = 0;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(PrimaryColor);
                tft.drawCentreString(unitString[unit], 155, 110, GFXFF);
                break;

              case 170:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                if (af) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                if (af) af = false; else af = true;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (af) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                break;
            }
            break;
        }
      }
    }
  }
}

void KeyDown() {
  rotary = 0;
  if (!afscreen) {
    if (menu == false) {
      switch (tunemode) {
        case TUNE_MAN:
          TuneDown();
          break;

        case TUNE_AUTO:
          direction = false;
          seek = true;
          Seek(direction);
          break;

        case TUNE_MEM:
          memorypos--;
          if (memorypos > EE_PRESETS_CNT - 1) memorypos = EE_PRESETS_CNT - 1;
          ShowMemoryPos();
          if (memorystore == false) DoMemoryPosTune();
          EEPROM.writeByte(EE_BYTE_MEMORYPOS, memorypos);
          EEPROM.commit();
          break;
        case TUNE_MI_BAND:
          if (showSWMIBand) {
            if (displayflip) {
              ToggleSWMIBand(true);
            } else {
              ToggleSWMIBand(false);
            }
          }
          break;
      }
        if (XDRGTKUSB == true || XDRGTKTCP == true) if (band == BAND_FM) DataPrint("T" + String(frequency * 10)); else DataPrint("T" + String(frequency_AM));
      radio.clearRDS(fullsearchrds);
      change = 0;
      ShowFreq(0);
      store = true;
    } else {
      if (menuopen == false) {
        tft.drawRoundRect(8, menuoption + 3, 302, 19, 5, BackgroundColor);
        menuoption -= 20;
        if (menuoption < 30) {
          menupage--;
          if (menupage == 0) menupage = menupagestotal;
          menuoption = 210;
          BuildMenu();
        }
        tft.drawRoundRect(8, menuoption + 3, 302, 19, 5, ActiveColor);
      } else {
        switch (menupage) {
          case 1:
            switch (menuoption) {
              case 30:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                if (VolSet > 0) tft.drawRightString("+" + String(VolSet, DEC), 155, 110, GFXFF); else tft.drawRightString(String(VolSet, DEC), 155, 110, GFXFF);
                VolSet--;
                if (VolSet < -10) VolSet = -10;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (VolSet > 0) tft.drawRightString("+" + String(VolSet, DEC), 155, 110, GFXFF); else tft.drawRightString(String(VolSet, DEC), 155, 110, GFXFF);
                radio.setVolume(VolSet);
                break;

              case 50:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                tft.drawRightString(String(ConverterSet, DEC), 155, 110, GFXFF);
                ConverterSet--;
                  if (ConverterSet < 200 || ConverterSet > 2400) if (ConverterSet > 2400) ConverterSet = 2400; else ConverterSet = 0;
                if (ConverterSet >= 200) {
                  Wire.beginTransmission(0x12);
                  Wire.write(ConverterSet >> 8);
                  Wire.write(ConverterSet & (0xFF));
                  Wire.endTransmission();
                }
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                tft.drawRightString(String(ConverterSet, DEC), 155, 110, GFXFF);
                break;

              case 70:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                tft.drawRightString(String(LowEdgeSet / 10 + ConverterSet, DEC) + "." + String(LowEdgeSet % 10 + ConverterSet, DEC), 155, 110, GFXFF);
                LowEdgeSet -= 10;
                if (LowEdgeSet < 650) LowEdgeSet = 1079;
                if (specialstepOIRT) {
                  FindlowStopOIRT();
                  FindhighStopOIRT();
                }
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                tft.drawRightString(String(LowEdgeSet / 10 + ConverterSet, DEC) + "." + String(LowEdgeSet % 10 + ConverterSet, DEC), 155, 110, GFXFF);
                break;

              case 90:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                tft.drawRightString(String(HighEdgeSet / 10 + ConverterSet, DEC) + "." + String(HighEdgeSet % 10 + ConverterSet, DEC), 155, 110, GFXFF);
                HighEdgeSet -= 10;
                if (HighEdgeSet < 660) HighEdgeSet = 1080;
                if (specialstepOIRT) {
                  FindlowStopOIRT();
                  FindhighStopOIRT();
                }
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                tft.drawRightString(String(HighEdgeSet / 10 + ConverterSet, DEC) + "." + String(HighEdgeSet % 10 + ConverterSet, DEC), 155, 110, GFXFF);
                break;

              case 110:
                tft.setFreeFont(FONT14);
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                if (LevelOffset > 0) tft.drawRightString("+" + String(LevelOffset, DEC), 155, 110, GFXFF); else tft.drawRightString(String(LevelOffset, DEC), 155, 110, GFXFF);
                LevelOffset--;
                if (LevelOffset < -25) LevelOffset = 15;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (LevelOffset > 0) tft.drawRightString("+" + String(LevelOffset, DEC), 155, 110, GFXFF); else tft.drawRightString(String(LevelOffset, DEC), 155, 110, GFXFF);
                radio.setOffset(LevelOffset);
                change2 = true;
                break;

              case 130:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                tft.drawRightString(String(StereoLevel, DEC), 155, 110, GFXFF);
                StereoLevel --;
                  if (StereoLevel < 30 || StereoLevel > 60) if (StereoLevel > 60) StereoLevel = 60; else StereoLevel = 0;
                tft.drawRightString(myLanguage[language][30], 155, 110, GFXFF);
                tft.drawString("dBμV", 170, 110, GFXFF);
                tft.setTextColor(ActiveColor);
                if (StereoLevel != 0) tft.drawString("dBμV", 170, 110, GFXFF);
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (StereoLevel != 0) tft.drawRightString(String(StereoLevel, DEC), 155, 110, GFXFF); else tft.drawRightString(myLanguage[language][30], 155, 110, GFXFF);
                radio.setStereoLevel(StereoLevel);
                break;

              case 150:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                tft.drawRightString(String(HighCutLevel * 100, DEC), 155, 110, GFXFF);
                HighCutLevel --;
                if (HighCutLevel < 15 || HighCutLevel > 70) HighCutLevel = 70;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                tft.drawRightString(String(HighCutLevel * 100, DEC), 155, 110, GFXFF);
                radio.setHighCutLevel(HighCutLevel);
                break;

              case 170:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                tft.drawRightString(String(HighCutOffset, DEC), 155, 110, GFXFF);
                HighCutOffset --;
                  if (HighCutOffset < 20 || HighCutOffset > 60) if (HighCutOffset > 60) HighCutOffset = 60; else HighCutOffset = 0;
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                tft.drawRightString(myLanguage[language][30], 155, 110, GFXFF);
                tft.drawString("dBμV", 170, 110, GFXFF);
                tft.setTextColor(ActiveColor);
                if (HighCutOffset != 0) tft.drawString("dBμV", 170, 110, GFXFF);
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (HighCutOffset != 0) tft.drawRightString(String(HighCutOffset, DEC), 155, 110, GFXFF); else tft.drawRightString(myLanguage[language][30], 155, 110, GFXFF);
                radio.setHighCutOffset(HighCutOffset);
                break;

              case 190:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                tft.drawRightString(String(LowLevelSet, DEC), 145, 110, GFXFF);
                LowLevelSet--;
                if (LowLevelSet < -10) LowLevelSet = 40;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                tft.drawRightString(String(LowLevelSet, DEC), 145, 110, GFXFF);
                break;


              case 210:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                tft.drawRightString(String(ContrastSet, DEC), 155, 110, GFXFF);
                ContrastSet --;
                if (ContrastSet < 1) ContrastSet = 100;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                tft.drawRightString(String(ContrastSet, DEC), 155, 110, GFXFF);
                analogWrite(CONTRASTPIN, ContrastSet * 2 + 27);
                break;
            }
            break;

          case 2:
            switch (menuoption) {
              case 30:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                tft.drawCentreString(myLanguage[language][0], 155, 110, GFXFF);
                language --;
                if (language > (sizeof (myLanguage) / sizeof (myLanguage[0]))) language = (sizeof (myLanguage) / sizeof (myLanguage[0])) - 1;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                tft.drawCentreString(myLanguage[language][0], 155, 110, GFXFF);
                break;

              case 50:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                if (showrdserrors) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                if (showrdserrors) showrdserrors = false; else showrdserrors = true;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (showrdserrors) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                break;

              case 70:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                if (softmutefm) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                if (softmutefm) softmutefm = false; else softmutefm = true;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (softmutefm) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                radio.setSoftmuteFM(softmutefm);
                break;

              case 90:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                if (softmuteam) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                if (softmuteam) softmuteam = false; else softmuteam = true;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (softmuteam) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                radio.setSoftmuteAM(softmuteam);
                break;

              case 110:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                if (edgebeep) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                if (edgebeep) edgebeep = false; else edgebeep = true;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (edgebeep) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                break;

              case 130:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                if (region == 0) region = 1; else region = 0;
                if (regionold == 0) tft.drawCentreString(myLanguage[language][47], 155, 110, GFXFF);
                if (regionold == 1) tft.drawCentreString(myLanguage[language][48], 155, 110, GFXFF);
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (region == 0) tft.drawCentreString(myLanguage[language][47], 155, 110, GFXFF);
                if (region == 1) tft.drawCentreString(myLanguage[language][48], 155, 110, GFXFF);
                regionold = region;
                if (region == 0) radio.setDeemphasis(1);
                if (region == 1) radio.setDeemphasis(2);
                radio.rds.region = region;
                break;

              case 150:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                if (radio.rds.underscore) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                if (radio.rds.underscore) radio.rds.underscore = false; else radio.rds.underscore = true;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (radio.rds.underscore) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                break;

              case 170:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                if (USBmode) tft.drawCentreString("RDS Spy", 155, 110, GFXFF); else tft.drawCentreString("XDR-GTK", 155, 110, GFXFF);
                if (USBmode) USBmode = false; else USBmode = true;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (USBmode) tft.drawCentreString("RDS Spy", 155, 110, GFXFF); else tft.drawCentreString("XDR-GTK", 155, 110, GFXFF);
                break;

              case 190:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                if (wifi) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                if (wifi) wifi = false; else wifi = true;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (wifi) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                break;
            }
            break;

          case 3:
            switch (menuoption) {
              case 30:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                tft.drawCentreString(String(WiFi.localIP()[0]) + "." + String(WiFi.localIP()[1]) + "." + String(WiFi.localIP()[2]) + "." + String(subnetclient, DEC), 155, 110, GFXFF);
                subnetclient --;
                if (subnetclient < 1) subnetclient = 254;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                tft.drawCentreString(String(WiFi.localIP()[0]) + "." + String(WiFi.localIP()[1]) + "." + String(WiFi.localIP()[2]) + "." + String(subnetclient, DEC), 155, 110, GFXFF);
                break;

              case 50:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                if (showSWMIBand) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                if (showSWMIBand) showSWMIBand = false; else showSWMIBand = true;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (showSWMIBand) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                break;

              case 70:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                if (radio.rds.filter) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                if (radio.rds.filter) radio.rds.filter = false; else radio.rds.filter = true;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (radio.rds.filter) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                break;

              case 90:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                if (radio.rds.pierrors) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                if (radio.rds.pierrors) radio.rds.pierrors = false; else radio.rds.pierrors = true;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (radio.rds.pierrors) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                break;

              case 110:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                if (showsquelch) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                if (showsquelch) showsquelch = false; else showsquelch = true;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (showsquelch) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                break;

              case 130:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                if (showmodulation) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                if (showmodulation) showmodulation = false; else showmodulation = true;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (showmodulation) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                break;

              case 150:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                tft.drawRightString(String(amnb, DEC), 155, 110, GFXFF);
                amnb --;
                  if (amnb > 150 || amnb <= 50) if (amnb > 150) amnb = 150; else amnb = 0;
                tft.drawRightString(myLanguage[language][30], 155, 110, GFXFF);
                tft.drawString("%", 170, 110, GFXFF);
                tft.setTextColor(ActiveColor);
                if (amnb != 0) tft.drawString("%", 170, 110, GFXFF);
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (amnb != 0) tft.drawRightString(String(amnb, DEC), 155, 110, GFXFF); else tft.drawRightString(myLanguage[language][30], 155, 110, GFXFF);
                radio.setAMNoiseBlanker(amnb);
                break;

              case 170:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                tft.drawRightString(String(fmnb, DEC), 155, 110, GFXFF);
                fmnb --;
                  if (fmnb > 150 || fmnb <= 50) if (fmnb > 150) fmnb = 150; else fmnb = 0;
                tft.drawRightString(myLanguage[language][30], 155, 110, GFXFF);
                tft.drawString("%", 170, 110, GFXFF);
                tft.setTextColor(ActiveColor);
                if (fmnb != 0) tft.drawString("%", 170, 110, GFXFF);
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (fmnb != 0) tft.drawRightString(String(fmnb, DEC), 155, 110, GFXFF); else tft.drawRightString(myLanguage[language][30], 155, 110, GFXFF);
                radio.setFMNoiseBlanker(fmnb);
                break;

              case 190:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                if (audiomode) tft.drawCentreString("MPX", 155, 110, GFXFF); else tft.drawCentreString("Stereo", 155, 110, GFXFF);
                if (audiomode) audiomode = false; else audiomode = true;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (audiomode) tft.drawCentreString("MPX", 155, 110, GFXFF); else tft.drawCentreString("Stereo", 155, 110, GFXFF);
                radio.setAudio(audiomode);
                break;
              case 210:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                if (specialstepOIRT) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                if (specialstepOIRT) {
                  specialstepOIRT = 0;
                } else {
                  specialstepOIRT = 1;
                  FindlowStopOIRT();
                  FindhighStopOIRT();
                }
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (specialstepOIRT) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                break;
            }
            break;
          case 4:
            switch (menuoption) {
              case 30:
                tft.setTextColor(BackgroundColor);
                tft.drawCentreString(CurrentThemeString, 155, 110, GFXFF);
                CurrentTheme --;
                if (CurrentTheme > 7) CurrentTheme = 7;
                doTheme();
                BuildMenu(); menu == false; menuopen = false; ButtonPress(); //Fast preview theme
                tft.setTextColor(PrimaryColor);
                tft.drawCentreString(CurrentThemeString, 155, 110, GFXFF);
                break;

              case 70:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                ShowPowerOptions(true);
                poweroptions--;
                if (poweroptions > RADIO_POWER_MODE_CNT - 1) poweroptions = RADIO_POWER_MODE_CNT - 1;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                ShowPowerOptions(true);
                break;

              case 90:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                if (fmdefaultstepsize) tft.drawRightString(String(FREQ_FM_STEP_100K * 10, DEC), 155, 110, GFXFF); else tft.drawRightString(String(FREQ_FM_STEP_50K * 10, DEC), 155, 110, GFXFF);
                if (fmdefaultstepsize) fmdefaultstepsize = 0; else fmdefaultstepsize = 1;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (fmdefaultstepsize) tft.drawRightString(String(FREQ_FM_STEP_100K * 10, DEC), 155, 110, GFXFF); else tft.drawRightString(String(FREQ_FM_STEP_50K * 10, DEC), 155, 110, GFXFF);
                break;

              case 110:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                if (screensaverset) tft.drawString(myLanguage[language][92], 170, 110, GFXFF);
                if (!screensaverset) tft.drawRightString(myLanguage[language][30], 155, 110, GFXFF); else tft.drawRightString(String(screensaverOptions[screensaverset], DEC), 155, 110, GFXFF);
                screensaverset --;
                if (screensaverset > sizeof(screensaverOptions) / sizeof(screensaverOptions[0]) - 1) screensaverset = sizeof(screensaverOptions) / sizeof(screensaverOptions[0]) - 1;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (screensaverset) tft.drawString(myLanguage[language][92], 170, 110, GFXFF);
                if (!screensaverset) tft.drawRightString(myLanguage[language][30], 155, 110, GFXFF); else tft.drawRightString(String(screensaverOptions[screensaverset], DEC), 155, 110, GFXFF);
                break;

              case 130:
                tft.setFreeFont(FONT14);
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                if (AMLevelOffset > 0) tft.drawRightString("+" + String(AMLevelOffset, DEC), 155, 110, GFXFF); else tft.drawRightString(String(AMLevelOffset, DEC), 155, 110, GFXFF);
                AMLevelOffset--;
                if (AMLevelOffset < -50) AMLevelOffset = 15;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (AMLevelOffset > 0) tft.drawRightString("+" + String(AMLevelOffset, DEC), 155, 110, GFXFF); else tft.drawRightString(String(AMLevelOffset, DEC), 155, 110, GFXFF);
                radio.setAMOffset(AMLevelOffset);
                break;

              case 150:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                tft.drawCentreString(unitString[unit], 155, 110, GFXFF);
                unit --;
                if (unit > 2) unit = 2;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(PrimaryColor);
                tft.drawCentreString(unitString[unit], 155, 110, GFXFF);
                break;

              case 170:
                if (CurrentTheme == 7) tft.setTextColor(TFT_WHITE); else tft.setTextColor(TFT_BLACK);
                if (af) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                if (af) af = false; else af = true;
                if (CurrentTheme == 7) tft.setTextColor(TFT_BLACK); else tft.setTextColor(TFT_WHITE);
                if (af) tft.drawCentreString(myLanguage[language][42], 155, 110, GFXFF); else tft.drawCentreString(myLanguage[language][30], 155, 110, GFXFF);
                break;
            }
            break;
        }
      }
    }
  }
}

void ShowMemoryPos() {
  if (tunemode == TUNE_MEM) {
    tft.setFreeFont(FONT7);
    tft.setTextColor(BackgroundColor);
    if (advancedRDS) tft.drawString(String(memoryposold + 1), 215, 30, GFXFF); else tft.drawString(String(memoryposold + 1), 80, 26, GFXFF);
    tft.setTextColor(SecondaryColor);
    if (advancedRDS)  tft.drawString(String(memorypos + 1), 215, 30, GFXFF); else tft.drawString(String(memorypos + 1), 80, 26, GFXFF);
    memoryposold = memorypos;
  } else {
    tft.setFreeFont(FONT7);
    tft.setTextColor(BackgroundColor);
    if (advancedRDS) tft.drawString(String(memorypos + 1), 215, 30, GFXFF); else tft.drawString(String(memorypos + 1), 80, 26, GFXFF);
  }
}

void DoMemoryPosTune() {
  if (band != memoryband[memorypos]) {
    band = memoryband[memorypos];
    SelectBand();
  } else {
    band = memoryband[memorypos];
  }

  if (band == BAND_FM) {
    frequency = memory[memorypos];
    radio.SetFreq(frequency);
  } else {
    frequency_AM = memory[memorypos];
    radio.SetFreqAM(frequency_AM);
  }
  ShowFreq(0);
}

void readRds() {
  radio.readRDS(showrdserrors);
  if (band == BAND_FM) {
    RDSstatus = radio.rds.hasRDS;
    ShowRDSLogo(RDSstatus);
    if (!afscreen) {
      if (RDSstatus == 0 && screenmute == false) {
        tft.setTextColor(SecondaryColor);
        tft.setFreeFont(FONT14);
        if (advancedRDS) tft.drawString(PIold, 244, 66, GFXFF); else tft.drawString(PIold, 244, 183, GFXFF);
        tft.setFreeFont(FONT14);
        if (advancedRDS) tft.drawString(PSold, 38, 66, GFXFF); else tft.drawString(PSold, 38, 183, GFXFF);
        tft.setFreeFont(FONT7);
        if (advancedRDS) tft.drawString(PTYold, 38, 105, GFXFF); else tft.drawString(PTYold, 38, 164, GFXFF);
        if (advancedRDS) tft.drawString(String(ptynold), 255, 105, GFXFF);
        tft.setTextColor(BackgroundColor);
        tft.setFreeFont(FONT7);
        if (!advancedRDS) tft.drawString(RTold, 1, 223, GFXFF);
        dropout = true;
      } else {
        if (dropout == true && PIold.length() != 0) {
          tft.setTextColor(PrimaryColor);
          tft.setFreeFont(FONT14);
          if (advancedRDS) tft.drawString(PIold, 244, 66, GFXFF); else tft.drawString(PIold, 244, 183, GFXFF);
          tft.setFreeFont(FONT14);
          if (advancedRDS) tft.drawString(PSold, 38, 66, GFXFF); else tft.drawString(PSold, 38, 183, GFXFF);
          tft.setFreeFont(FONT7);
          if (advancedRDS) tft.drawString(PTYold, 38, 105, GFXFF); else tft.drawString(PTYold, 38, 164, GFXFF);
          if (advancedRDS) tft.drawString(String(ptynold), 255, 105, GFXFF);
          dropout = false;
        }
      }
    }

    if ((RDSstatus == 1 && RDSSPYUSB == true) || (RDSstatus == 1 && RDSSPYTCP == true)) {
      RDSSPYRDS = "G:\r\n";
      if (radio.rds.rdsAerror) RDSSPYRDS += "----"; else RDSSPYRDS += String(((radio.rds.rdsA >> 8) >> 4) & 0xF, HEX) + String((radio.rds.rdsA >> 8) & 0xF, HEX) + String(((radio.rds.rdsA) >> 4) & 0xF, HEX) + String((radio.rds.rdsA) & 0xF, HEX);
      if (radio.rds.rdsBerror) RDSSPYRDS += "----"; else RDSSPYRDS += String(((radio.rds.rdsB >> 8) >> 4) & 0xF, HEX) + String((radio.rds.rdsB >> 8) & 0xF, HEX) + String(((radio.rds.rdsB) >> 4) & 0xF, HEX) + String((radio.rds.rdsB) & 0xF, HEX);
      if (radio.rds.rdsCerror) RDSSPYRDS += "----"; else RDSSPYRDS += String(((radio.rds.rdsC >> 8) >> 4) & 0xF, HEX) + String((radio.rds.rdsC >> 8) & 0xF, HEX) + String(((radio.rds.rdsC) >> 4) & 0xF, HEX) + String((radio.rds.rdsC) & 0xF, HEX);
      if (radio.rds.rdsDerror) RDSSPYRDS += "----"; else RDSSPYRDS += String(((radio.rds.rdsD >> 8) >> 4) & 0xF, HEX) + String((radio.rds.rdsD >> 8) & 0xF, HEX) + String(((radio.rds.rdsD) >> 4) & 0xF, HEX) + String((radio.rds.rdsD) & 0xF, HEX);
      RDSSPYRDS += "\r\n\r\n";

      if (RDSSPYRDS != RDSSPYRDSold) {
        if (RDSSPYUSB) Serial.print(RDSSPYRDS); else RemoteClient.print(RDSSPYRDS);
        RDSSPYRDSold = RDSSPYRDS;
      }
    }

    if ((RDSstatus == 1 && XDRGTKUSB == true) || (RDSstatus == 1 && XDRGTKTCP == true)) {
      DataPrint ("P");
      DataPrint (String(((radio.rds.rdsA >> 8) >> 4) & 0xF, HEX) + String((radio.rds.rdsA >> 8) & 0xF, HEX));
      DataPrint (String(((radio.rds.rdsA) >> 4) & 0xF, HEX) + String((radio.rds.rdsA) & 0xF, HEX));
      if (((radio.rds.rdsErr >> 14) & 0x02) > 2) DataPrint("?");
      if (((radio.rds.rdsErr >> 14) & 0x01) > 1) DataPrint("?");
      DataPrint ("\n");

      XDRGTKRDS = "R";
      XDRGTKRDS += String(((radio.rds.rdsB >> 8) >> 4) & 0xF, HEX) + String((radio.rds.rdsB >> 8) & 0xF, HEX);
      XDRGTKRDS += String(((radio.rds.rdsB) >> 4) & 0xF, HEX) + String((radio.rds.rdsB) & 0xF, HEX);
      XDRGTKRDS += String(((radio.rds.rdsC >> 8) >> 4) & 0xF, HEX) + String((radio.rds.rdsC >> 8) & 0xF, HEX);
      XDRGTKRDS += String(((radio.rds.rdsC) >> 4) & 0xF, HEX) + String((radio.rds.rdsC) & 0xF, HEX);
      XDRGTKRDS += String(((radio.rds.rdsD >> 8) >> 4) & 0xF, HEX) + String((radio.rds.rdsD >> 8) & 0xF, HEX);
      XDRGTKRDS += String(((radio.rds.rdsD) >> 4) & 0xF, HEX) + String((radio.rds.rdsD) & 0xF, HEX);

      byte erroutput;
      erroutput |= (highByte(radio.rds.rdsErr) & 0x04) >> 2;
      erroutput |= (highByte(radio.rds.rdsErr) & 0x02) << 2;
      erroutput |= (highByte(radio.rds.rdsErr) & 0x01) << 6;
      erroutput |= (highByte(radio.rds.rdsErr) & 0x08) >> 3;
      erroutput |= (highByte(radio.rds.rdsErr) & 0x10) >> 1;
      erroutput |= (highByte(radio.rds.rdsErr) & 0x40) << 1;
      erroutput |= (highByte(radio.rds.rdsErr) & 0x80) >> 7;
      erroutput |= (highByte(radio.rds.rdsErr) & 0x20) << 5;

      if (highByte(radio.rds.rdsErr) < 0x10) XDRGTKRDS += "0";
      XDRGTKRDS += String(erroutput, HEX);
      XDRGTKRDS += "\n";

      if (XDRGTKRDS != XDRGTKRDSold) {
        DataPrint(XDRGTKRDS);
        XDRGTKRDSold = XDRGTKRDS;
      }
    }
  }
}

void ShowAdvancedRDS() {
  if (radio.rds.rdsAerror != errorAold) {
    if (radio.rds.rdsAerror) tft.fillCircle(80, 41, 5, TFT_RED); else tft.fillCircle(80, 41, 5, TFT_GREEN);
    errorAold = radio.rds.rdsAerror;
  }

  if (radio.rds.rdsBerror != errorBold) {
    if (radio.rds.rdsBerror) tft.fillCircle(120, 41, 5, TFT_RED); else tft.fillCircle(120, 41, 5, TFT_GREEN);
    errorBold = radio.rds.rdsBerror;
  }

  if (radio.rds.rdsCerror != errorCold) {
    if (radio.rds.rdsCerror) tft.fillCircle(160, 41, 5, TFT_RED); else tft.fillCircle(160, 41, 5, TFT_GREEN);
    errorCold = radio.rds.rdsCerror;
  }

  if (radio.rds.rdsDerror != errorDold) {
    if (radio.rds.rdsDerror) tft.fillCircle(200, 41, 5, TFT_RED); else tft.fillCircle(200, 41, 5, TFT_GREEN);
    errorDold = radio.rds.rdsDerror;
  }

  if (radio.rds.hasDynamicPTY != dynamicPTYold) {
    if (radio.rds.hasDynamicPTY) tft.fillCircle(310, 139, 5, TFT_GREEN); else tft.fillCircle(310, 139, 5, TFT_RED);
    dynamicPTYold = radio.rds.hasDynamicPTY;
  }

  if (radio.rds.hasArtificialhead != artheadold) {
    if (radio.rds.hasArtificialhead) tft.fillCircle(310, 155, 5, TFT_GREEN); else tft.fillCircle(310, 155, 5, TFT_RED);
    artheadold = radio.rds.hasArtificialhead;
  }

  if (radio.rds.hasCompressed != compressedold) {
    if (radio.rds.hasCompressed) tft.fillCircle(310, 170, 5, TFT_GREEN); else tft.fillCircle(310, 170, 5, TFT_RED);
    compressedold = radio.rds.hasCompressed;
  }

  if (radio.rds.hasStereo != rdsstereoold) {
    if (radio.rds.hasStereo) tft.fillCircle(310, 185, 5, TFT_GREEN); else tft.fillCircle(310, 185, 5, TFT_RED);
    rdsstereoold = radio.rds.hasStereo;
  }

  if (ptynold != radio.rds.PTYN) {
    tft.setFreeFont(FONT7);
    tft.setTextColor(BackgroundColor);
    tft.drawString("N/A", 255, 105, GFXFF);
    tft.drawString(String(ptynold), 255, 105, GFXFF);
    tft.setTextColor(PrimaryColor);
    if (radio.rds.PTYN.length() > 0) tft.drawString(String(radio.rds.PTYN), 255, 105, GFXFF); else tft.drawString("N/A", 255, 105, GFXFF);
    ptynold = radio.rds.PTYN;
  }

  if (licold != radio.rds.LIC) {
    tft.setFreeFont(FONT7);
    tft.setTextColor(BackgroundColor);
    tft.drawString("N/A", 245, 205, GFXFF);
    tft.drawString(LIColdString, 245, 205, GFXFF);
    tft.setTextColor(PrimaryColor);
    if (radio.rds.LIC > 0 && radio.rds.LIC < 44) {
      if (radio.rds.hasLIC) tft.drawString(myLanguages[radio.rds.LIC], 245, 205, GFXFF); else tft.drawString("N/A", 245, 205, GFXFF);
      LIColdString = myLanguages[radio.rds.LIC];
    } else {
      byte lic;
      switch (radio.rds.LIC) {
        case 73: lic = 44; break;
        case 86: lic = 45; break;
        case 96: lic = 46; break;
        case 99: lic = 47; break;
        case 108: lic = 48; break;
        case 112: lic = 49; break;
        case 113: lic = 50; break;
        case 119: lic = 51; break;
        case 125: lic = 52; break;
        case 126: lic = 53; break;
        default: lic = 0; break;
      }
      if (radio.rds.hasLIC) tft.drawString(myLanguages[lic], 245, 205, GFXFF); else tft.drawString("N/A", 245, 205, GFXFF);
      LIColdString = myLanguages[lic];
    }
    licold = radio.rds.LIC;
  }

  String pinstring = String(radio.rds.pinDay) + " " + String(radio.rds.pinHour) + ":" + (radio.rds.pinMin < 10 ? "0" : "") + String(radio.rds.pinMin);
  if (pinstringold != pinstring) {
    tft.setFreeFont(FONT7);
    tft.setTextColor(BackgroundColor);
    tft.drawString("N/A", 245, 220, GFXFF);
    tft.drawString(pinstringold, 245, 220, GFXFF);
    tft.setTextColor(PrimaryColor);
    if (radio.rds.hasPIN) tft.drawString(pinstring, 245, 220, GFXFF); else tft.drawString("N/A", 245, 220, GFXFF);
    pinstringold = pinstring;
  }

  String afstring;
  if (radio.rds.hasAF) for (byte i = 0; i < radio.af_counter; i++) afstring += String(radio.af[i].frequency / 100) + "." + String((radio.af[i].frequency % 100) / 10) + (radio.af[i].filler ? "(f)" : "") + (i == radio.af_counter - 1 ? "          " : " | "); else afstring = myLanguage[language][87];
  if (hasafold != radio.rds.hasAF) {
    if (radio.rds.hasAF) tft.setTextColor(SecondaryColor); else tft.setTextColor(GreyoutColor);
    tft.drawString("AF",  42, 45, GFXFF);
    hasafold = radio.rds.hasAF;
  }
  if (millis() - afticker >= 500) {
    if (xPos2 == 6) {
      if (millis() - aftickerhold >= 2000) {
        xPos2 -= charWidth;
        aftickerhold = millis();
      }
    } else {
      xPos2 -= charWidth;
      aftickerhold = millis();
    }
    if (xPos2 < -tft.textWidth(afstring) + (charWidth * 14)) xPos2 = 6;
    sprite2.setFreeFont(FONT7);
    sprite2.setTextDatum(ML_DATUM);
    sprite2.fillSprite(BackgroundColor);
    sprite2.setTextColor(PrimaryColor);
    sprite2.drawString(afstring, xPos2, 4 , GFXFF);
    sprite2.pushSprite(35, 200);
    afticker = millis();
  }

  String eonstring;
  if (radio.rds.hasEON) for (byte i = 0; i < radio.eon_counter; i++) eonstring += String(radio.eon[i].picode) + (radio.eon[i].ps.length() > 0 ? String(": " + String(radio.eon[i].ps)) : "") + (radio.eon[i].mappedfreq > 0 ? String(" " + String(radio.eon[i].mappedfreq / 100) + "." + String((radio.eon[i].mappedfreq % 100) / 10))  : "") + (radio.eon[i].mappedfreq2 > 0 ? String(" / " + String(radio.eon[i].mappedfreq2 / 100) + "." + String((radio.eon[i].mappedfreq2 % 100) / 10))  : "") + (radio.eon[i].mappedfreq3 > 0 ? String(" /  " + String(radio.eon[i].mappedfreq3 / 100) + "." + String((radio.eon[i].mappedfreq3 % 100) / 10))  : "") + (i == radio.eon_counter - 1 ? "      " : " | "); else eonstring = myLanguage[language][88];
  if (haseonold != radio.rds.hasEON) {
    if (radio.rds.hasEON) tft.setTextColor(SecondaryColor); else tft.setTextColor(GreyoutColor);
    tft.drawString("EON",  148, 45, GFXFF);
    haseonold = radio.rds.hasEON;
  }
  if (millis() - eonticker >= 500) {
    if (xPos3 == 6) {
      if (millis() - eontickerhold >= 2000) {
        xPos3 -= charWidth;
        eontickerhold = millis();
      }
    } else {
      xPos3 -= charWidth;
      eontickerhold = millis();
    }
    if (xPos3 < -tft.textWidth(eonstring) + (charWidth * 14)) xPos3 = 6;
    sprite2.setFreeFont(FONT7);
    sprite2.setTextDatum(ML_DATUM);
    sprite2.fillSprite(BackgroundColor);
    sprite2.setTextColor(PrimaryColor);
    sprite2.drawString(eonstring, xPos3, 4, GFXFF);
    sprite2.pushSprite(35, 174);
    eonticker = millis();
  }

  String rtplusstring;
  if (radio.rds.hasRDSplus) rtplusstring = "1\) " + String(radio.rds.RTContent1) + " - 2\) " + String(radio.rds.RTContent2) + "         "; else rtplusstring = myLanguage[language][89];
  if (hasrtplusold != radio.rds.hasRDSplus) {
    if (radio.rds.hasRDSplus) tft.setTextColor(SecondaryColor); else tft.setTextColor(GreyoutColor);
    tft.drawString("RT+",  116, 45, GFXFF);
    hasrtplusold = radio.rds.hasRDSplus;
  }
  if (millis() - rtplusticker >= 350) {
    if (xPos3 == 6) {
      if (millis() - rtplustickerhold >= 2000) {
        xPos4 -= charWidth;
        rtplustickerhold = millis();
      }
    } else {
      xPos4 -= charWidth;
      rtplustickerhold = millis();
    }
    if (xPos4 < -tft.textWidth(rtplusstring) + (charWidth * 14)) xPos4 = 6;
    sprite2.setFreeFont(FONT7);
    sprite2.setTextDatum(ML_DATUM);
    sprite2.fillSprite(BackgroundColor);
    sprite2.setTextColor(PrimaryColor);
    sprite2.drawString(rtplusstring, xPos4, 4, GFXFF);
    sprite2.pushSprite(35, 149);
    rtplusticker = millis();
  }

  if (TPold != radio.rds.hasTP) {
    tft.setFreeFont(FONT7);
    if (radio.rds.hasTP == true) tft.setTextColor(SecondaryColor); else tft.setTextColor(GreyoutColor);
    tft.drawString("TP",  6, 45, GFXFF);
    TPold = radio.rds.hasTP;
  }

  if (TAold != radio.rds.hasTA) {
    tft.setFreeFont(FONT7);
    if (radio.rds.hasTA == true) tft.setTextColor(SecondaryColor); else tft.setTextColor(GreyoutColor);
    tft.drawString("TA",  24, 45, GFXFF);
    TAold = radio.rds.hasTA;
  }

  if (MSold != radio.rds.MS) {
    tft.setFreeFont(FONT7);
    switch (radio.rds.MS) {
      case 0:
        tft.setTextColor(GreyoutColor);
        tft.drawString("M",  185, 45, GFXFF);
        tft.drawString("S",  198, 45, GFXFF);
        break;

      case 1:
        tft.setTextColor(SecondaryColor);
        tft.drawString("M",  185, 45, GFXFF);
        tft.setTextColor(GreyoutColor);
        tft.drawString("S",  198, 45, GFXFF);
        break;

      case 2:
        tft.setTextColor(GreyoutColor);
        tft.drawString("M",  185, 45, GFXFF);
        tft.setTextColor(SecondaryColor);
        tft.drawString("S",  198, 45, GFXFF);
        break;
    }
    MSold = radio.rds.MS;
  }

  rds_clock = ((hour() < 10 ? "0" : "") + String(hour()) + ":" + (minute() < 10 ? "0" : "") + String(minute()));
  if (radio.rds.hasCT == true && rds_clock != rds_clockold) {
    tft.setFreeFont(FONT7);
    tft.setTextColor(BackgroundColor);
    tft.drawRightString(rds_clockold, 205, 105, GFXFF);
    if (radio.rds.hasCT == true) tft.setTextColor(SecondaryColor); else tft.setTextColor(GreyoutColor); tft.drawString("CT",  62, 45, GFXFF);
    tft.drawRightString(rds_clock, 205, 105, GFXFF);
    rds_clockold = rds_clock;
  }

  if (rdsblockold != radio.rdsblock) {
    if (rdsblockold < 33) tft.fillCircle((6 * rdsblockold) + 10, 136, 2, TFT_RED);
    if (radio.rdsblock < 33) tft.fillCircle((6 * radio.rdsblock) + 10, 136, 2, TFT_GREEN);
    rdsblockold = radio.rdsblock;
  }

  if (hastmcold != radio.rds.hasTMC) {
    if (radio.rds.hasTMC == true) tft.setTextColor(SecondaryColor); else tft.setTextColor(GreyoutColor);
    tft.drawString("TMC",  82, 45, GFXFF);
    hastmcold = radio.rds.hasTMC;
  }
}

void doAF() {
  if (radio.af_counter != af_counterold && radio.rds.hasAF == true) {
    if (wifi) {
      Udp.beginPacket(remoteip, 9030);
      Udp.print("AF=");

      for (byte af_scan = 0; af_scan < radio.af_counter; af_scan++) {
        if (wifi) {
          if ((radio.af[af_scan].frequency - 8750) / 10 < 0x10) {
            Udp.print("0");
          }
          Udp.print((radio.af[af_scan].frequency - 8750) / 10, HEX);
        }
      }
      af_counterold = radio.af_counter;

      for (int i = 0; i < 25 - radio.af_counter; i++) Udp.print("00");
      Udp.endPacket();
    }
  }
}

void showECC() {
  if (ECCold != radio.rds.ECC) {
    String ECC;
    if (radio.rds.picode[0] == '1') {
      if (radio.rds.ECC == 224) ECC = myCountries[0];
      if (radio.rds.ECC == 225) ECC = myCountries[1];
      if (radio.rds.ECC == 226) ECC = myCountries[2];
      if (radio.rds.ECC == 228) ECC = myCountries[3];
    } else if (radio.rds.picode[0] == '2') {
      if (radio.rds.ECC == 224) ECC = myCountries[4];
      if (radio.rds.ECC == 225) ECC = myCountries[5];
      if (radio.rds.ECC == 226) ECC = myCountries[6];
      if (radio.rds.ECC == 227) ECC = myCountries[7];
      if (radio.rds.ECC == 228) ECC = myCountries[8];
    } else if (radio.rds.picode[0] == '3') {
      if (radio.rds.ECC == 224) ECC = myCountries[9];
      if (radio.rds.ECC == 225) ECC = myCountries[10];
      if (radio.rds.ECC == 226) ECC = myCountries[11];
      if (radio.rds.ECC == 227) ECC = myCountries[12];
    } else if (radio.rds.picode[0] == '4') {
      if (radio.rds.ECC == 224) ECC = myCountries[13];
      if (radio.rds.ECC == 225) ECC = myCountries[14];
      if (radio.rds.ECC == 226) ECC = myCountries[15];
      if (radio.rds.ECC == 227) ECC = myCountries[16];
    } else if (radio.rds.picode[0] == '5') {
      if (radio.rds.ECC == 224) ECC = myCountries[17];
      if (radio.rds.ECC == 225) ECC = myCountries[18];
      if (radio.rds.ECC == 226) ECC = myCountries[19];
    } else if (radio.rds.picode[0] == '6') {
      if (radio.rds.ECC == 224) ECC = myCountries[20];
      if (radio.rds.ECC == 225) ECC = myCountries[21];
      if (radio.rds.ECC == 226) ECC = myCountries[22];
      if (radio.rds.ECC == 227) ECC = myCountries[23];
      if (radio.rds.ECC == 228) ECC = myCountries[24];
    } else if (radio.rds.picode[0] == '7') {
      if (radio.rds.ECC == 224) ECC = myCountries[25];
      if (radio.rds.ECC == 225) ECC = myCountries[26];
      if (radio.rds.ECC == 226) ECC = myCountries[27];
    } else if (radio.rds.picode[0] == '8') {
      if (radio.rds.ECC == 224) ECC = myCountries[28];
      if (radio.rds.ECC == 225) ECC = myCountries[29];
      if (radio.rds.ECC == 226) ECC = myCountries[30];
      if (radio.rds.ECC == 227) ECC = myCountries[31];
      if (radio.rds.ECC == 228) ECC = myCountries[32];
    } else if (radio.rds.picode[0] == '9') {
      if (radio.rds.ECC == 224) ECC = myCountries[33];
      if (radio.rds.ECC == 225) ECC = myCountries[34];
      if (radio.rds.ECC == 226) ECC = myCountries[35];
      if (radio.rds.ECC == 227) ECC = myCountries[36];
      if (radio.rds.ECC == 228) ECC = myCountries[37];
    } else if (radio.rds.picode[0] == 'A') {
      if (radio.rds.ECC == 224) ECC = myCountries[38];
      if (radio.rds.ECC == 225) ECC = myCountries[39];
      if (radio.rds.ECC == 226) ECC = myCountries[40];
      if (radio.rds.ECC == 227) ECC = myCountries[41];
    } else if (radio.rds.picode[0] == 'B') {
      if (radio.rds.ECC == 224) ECC = myCountries[42];
      if (radio.rds.ECC == 225) ECC = myCountries[43];
      if (radio.rds.ECC == 226) ECC = myCountries[44];
    } else if (radio.rds.picode[0] == 'C') {
      if (radio.rds.ECC == 224) ECC = myCountries[45];
      if (radio.rds.ECC == 225) ECC = myCountries[46];
      if (radio.rds.ECC == 226) ECC = myCountries[47];
      if (radio.rds.ECC == 227) ECC = myCountries[48];
    } else if (radio.rds.picode[0] == 'D') {
      if (radio.rds.ECC == 224) ECC = myCountries[0];
      if (radio.rds.ECC == 225) ECC = myCountries[49];
    } else if (radio.rds.picode[0] == 'E') {
      if (radio.rds.ECC == 224) ECC = myCountries[50];
      if (radio.rds.ECC == 225) ECC = myCountries[51];
      if (radio.rds.ECC == 226) ECC = myCountries[52];
      if (radio.rds.ECC == 227) ECC = myCountries[53];
    } else if (radio.rds.picode[0] == 'F') {
      if (radio.rds.ECC == 224) ECC = myCountries[54];
      if (radio.rds.ECC == 225) ECC = myCountries[55];
      if (radio.rds.ECC == 226) ECC = myCountries[56];
      if (radio.rds.ECC == 227) ECC = myCountries[57];
      if (radio.rds.ECC == 228) ECC = myCountries[58];
    } else {
      ECC = myLanguage[language][73];
    }
    if (advancedRDS) {
      tft.setFreeFont(FONT7);
      tft.setTextColor(BackgroundColor);
      tft.drawString("N/A", 245, 190, GFXFF);
      tft.drawString(ECColdtxt, 245, 190, GFXFF);
      tft.setTextColor(PrimaryColor);
      if (radio.rds.hasECC) tft.drawString(ECC, 245, 190, GFXFF); else tft.drawString("N/A", 245, 190, GFXFF);
      ECColdtxt = ECC;
    }

    if (wifi) {
      Udp.beginPacket(remoteip, 9030);
      Udp.print("ECC=");
      if (radio.rds.ECC < 0x10) Udp.print("0");
      Udp.print(radio.rds.ECC, HEX);
      Udp.endPacket();
    }
    ECCold = radio.rds.ECC;
  }
}

void showPI() {
  if (strcmp(radio.rds.picode, radioIdPrevious)) {
    tft.setFreeFont(FONT14);
    tft.setTextColor(BackgroundColor);
    if (advancedRDS) {
      tft.drawString(PIold, 244, 66, GFXFF);
      tft.setTextColor(PrimaryColor);
      tft.drawString(radio.rds.picode, 244, 66, GFXFF);
    } else if (afscreen) {
      tft.setFreeFont(FONT7);
      tft.drawString(PIold, 38, 30, GFXFF);
      tft.setTextColor(SecondaryColor);
      tft.drawString(radio.rds.picode, 38, 30, GFXFF);
    } else {
      tft.drawString(PIold, 244, 183, GFXFF);
      tft.setTextColor(PrimaryColor);
      tft.drawString(radio.rds.picode, 244, 183, GFXFF);
    }
    PIold = radio.rds.picode;
    if (wifi) {
      Udp.beginPacket(remoteip, 9030);
      Udp.print("from=TEF tuner;PI=" + String(radio.rds.picode, 4));
      Udp.endPacket();
    }
    strcpy(radioIdPrevious, radio.rds.picode);
  }
}

void showPTY() {
  if (strcmp(radio.rds.stationType, programTypePrevious)) {
    tft.setFreeFont(FONT7);
    tft.setTextColor(BackgroundColor);
    if (advancedRDS) tft.drawString(PTYold, 38, 105, GFXFF); else tft.drawString(PTYold, 38, 164, GFXFF);
    tft.setTextColor(PrimaryColor);
    if (advancedRDS) tft.drawString(radio.rds.stationType, 38, 105, GFXFF); else tft.drawString(radio.rds.stationType, 38, 164, GFXFF);
    PTYold = radio.rds.stationType;
    if (wifi) {
      Udp.beginPacket(remoteip, 9030);
      Udp.print("from=TEF tuner;PTY=");
      Udp.print(radio.rds.stationTypeCode, HEX);
      Udp.endPacket();
    }
    strcpy(programTypePrevious, radio.rds.stationType);
  }
}

void showPS() {
  if (radio.rds.stationName != programServicePrevious) {
    tft.setFreeFont(FONT14);
    tft.setTextColor(BackgroundColor);
    if (advancedRDS) {
      tft.drawString(PSold, 38, 66, GFXFF);
      tft.setTextColor(PrimaryColor);
      tft.drawString(radio.rds.stationName, 38, 66, GFXFF);
    } else if (afscreen) {
      tft.setFreeFont(FONT7);
      tft.drawString(PSold, 71, 30, GFXFF);
      tft.setTextColor(SecondaryColor);
      tft.drawString(radio.rds.stationName, 71, 30, GFXFF);
    } else {
      tft.drawString(PSold, 38, 183, GFXFF);
      tft.setTextColor(PrimaryColor);
      tft.drawString(radio.rds.stationName, 38, 183, GFXFF);
      tft.drawLine(0, 187, 320, 187, FrameColor);
      tft.drawLine(0, 218, 320, 218, FrameColor);
    }
    PSold = radio.rds.stationName;
    if (wifi) {
      Udp.beginPacket(remoteip, 9030);
      Udp.print("from=TEF tuner;PS=");
      char PShex[9];
      radio.rds.stationName.toCharArray(PShex, 9);
      for (int i = 0; i < 8; i++)
      {
        if (PShex[i] < 0x10) Udp.print("0");
        if (PShex[i] == 0x20) PShex[i] =  '_';
        Udp.print(PShex[i], HEX);
      }
      Udp.endPacket();
    }
    programServicePrevious = radio.rds.stationName;
  }
}

void showRadioText() {
  if (radio.rds.hasRT && RDSstatus) {
    if (millis() - rtticker >= 350) {
      if (xPos == 6) {
        if (millis() - rttickerhold >= 2000) {
          xPos -= charWidth;
          rttickerhold = millis();
        }
      } else {
        xPos -= charWidth;
        rttickerhold = millis();
      }

      if (advancedRDS) {
        if (xPos < -tft.textWidth(radio.rds.stationText + " " + radio.rds.stationText32) + (charWidth * 14)) xPos = 6;
        sprite2.setFreeFont(FONT7);
        sprite2.setTextDatum(ML_DATUM);
        sprite2.fillSprite(BackgroundColor);
        sprite2.setTextColor(PrimaryColor);
        sprite2.drawString(radio.rds.stationText + " " + radio.rds.stationText32, xPos, 4, GFXFF);
        sprite2.pushSprite(35, 222);
      } else {
        if (xPos < -tft.textWidth(radio.rds.stationText + " " + radio.rds.stationText32) + (charWidth * 24)) xPos = 6;
        sprite.setFreeFont(FONT7);
        sprite.setTextDatum(ML_DATUM);
        sprite.fillSprite(BackgroundColor);
        sprite.setTextColor(PrimaryColor);
        sprite.drawString(radio.rds.stationText + " " + radio.rds.stationText32, xPos, 4, GFXFF);
        sprite.pushSprite(1, 222);
      }
      rtticker = millis();
      RTold = radio.rds.stationText + " " + radio.rds.stationText32;
      cleanup = true;
    }
  } else if (cleanup == true) {
    sprite.fillSprite(BackgroundColor);
    sprite2.fillSprite(BackgroundColor);
    if (advancedRDS) sprite2.pushSprite(35, 222); else sprite.pushSprite(1, 222);
    cleanup = false;
  }

  if (wifi) {
    Udp.beginPacket(remoteip, 9030);
    Udp.print("from=TEF tuner;RT1=");
    char RThex[65];
    radio.rds.stationText.toCharArray(RThex, 65);
    for (int i = 0; i < 64; i++)
    {
      if (RThex[i] < 0x10) Udp.print("0");
      if (RThex[i] == ' ') RThex[i] =  '_';
      Udp.print(RThex[i], HEX);
    }
    Udp.endPacket();
  }
  tft.drawLine(0, 239, 320, 239, FrameColor);
}

void BuildMenu() {
  advancedRDS = false;
  tft.setFreeFont(FONT7);
  tft.fillScreen(BackgroundColor);
  tft.drawRect(0, 0, 320, 240, FrameColor);
  tft.drawLine(0, 23, 320, 23, FrameColor);
  tft.setTextColor(PrimaryColor);
  tft.drawString(myLanguage[language][41], 10, 1, GFXFF);
  tft.setTextColor(ActiveColor);
  tft.drawRightString(String(menupage) + "/" + String(menupagestotal), 305, 1, GFXFF);
  tft.drawRoundRect(8, menuoption + 3, 302, 19, 5, ActiveColor);
  tft.setTextColor(ActiveColor);
  switch (menupage) {
    case 1:
      tft.drawRightString("dB", 305, 30, GFXFF);
      tft.drawRightString("MHz", 305, 50, GFXFF);
      tft.drawRightString("MHz", 305, 70, GFXFF);
      tft.drawRightString("MHz", 305, 90, GFXFF);
      tft.drawRightString("dB", 305, 110, GFXFF);
      if (StereoLevel != 0) tft.drawRightString("dBμV", 305, 130, GFXFF);
      if (HighCutLevel != 0) tft.drawRightString("Hz", 305, 150, GFXFF);
      if (HighCutOffset != 0) tft.drawRightString("dBμV", 305, 170, GFXFF);
      tft.drawRightString("dBμV", 305, 190, GFXFF);
      tft.drawRightString("%", 305, 210, GFXFF);
      tft.drawString(myLanguage[language][20], 14, 30, GFXFF);
      tft.drawString(myLanguage[language][21], 14, 50, GFXFF);
      tft.drawString(myLanguage[language][22], 14, 70, GFXFF);
      tft.drawString(myLanguage[language][23], 14, 90, GFXFF);
      tft.drawString(myLanguage[language][24], 14, 110, GFXFF);
      tft.drawString(myLanguage[language][25], 14, 130, GFXFF);
      tft.drawString(myLanguage[language][26], 14, 150, GFXFF);
      tft.drawString(myLanguage[language][27], 14, 170, GFXFF);
      tft.drawString(myLanguage[language][28], 14, 190, GFXFF);
      tft.drawString(myLanguage[language][29], 14, 210, GFXFF);
      tft.setTextColor(PrimaryColor);
      if (VolSet > 0) tft.drawRightString("+" + String(VolSet, DEC), 265, 30, GFXFF); else tft.drawRightString(String(VolSet, DEC), 265, 30, GFXFF);
      tft.drawRightString(String(ConverterSet, DEC), 265, 50, GFXFF);
      tft.drawRightString(String(LowEdgeSet / 10 + ConverterSet, DEC) + "." + String(LowEdgeSet % 10 + ConverterSet, DEC), 265, 70, GFXFF);
      tft.drawRightString(String(HighEdgeSet / 10 + ConverterSet, DEC) + "." + String(HighEdgeSet % 10 + ConverterSet, DEC), 265, 90, GFXFF);
      if (LevelOffset > 0) tft.drawRightString("+" + String(LevelOffset, DEC), 265, 110, GFXFF); else tft.drawRightString(String(LevelOffset, DEC), 265, 110, GFXFF);
      if (StereoLevel != 0) tft.drawRightString(String(StereoLevel, DEC), 265, 130, GFXFF); else tft.drawRightString(myLanguage[language][30], 305, 130, GFXFF);
      if (HighCutLevel != 0) tft.drawRightString(String(HighCutLevel * 100, DEC), 265, 150, GFXFF); else tft.drawRightString(myLanguage[language][30], 265, 150, GFXFF);
      if (HighCutOffset != 0) tft.drawRightString(String(HighCutOffset, DEC), 265, 170, GFXFF); else tft.drawRightString(myLanguage[language][30], 305, 170, GFXFF);
      tft.drawRightString(String(LowLevelSet, DEC), 265, 190, GFXFF);
      tft.drawRightString(String(ContrastSet, DEC), 265, 210, GFXFF);
      break;

    case 2:
      tft.drawString(myLanguage[language][39], 14, 30, GFXFF);
      tft.drawString(myLanguage[language][38], 14, 50, GFXFF);
      tft.drawString(myLanguage[language][43], 14, 70, GFXFF);
      tft.drawString(myLanguage[language][44], 14, 90, GFXFF);
      tft.drawString(myLanguage[language][45], 14, 110, GFXFF);
      tft.drawString(myLanguage[language][46], 14, 130, GFXFF);
      tft.drawString(myLanguage[language][49], 14, 150, GFXFF);
      tft.drawString(myLanguage[language][50], 14, 170, GFXFF);
      if (wifi) tft.drawString(String(myLanguage[language][51]) + " IP: " + String(WiFi.localIP().toString()), 14, 190, GFXFF); else tft.drawString(myLanguage[language][51], 14, 190, GFXFF);
      tft.drawString(myLanguage[language][52], 14, 210, GFXFF);
      tft.setTextColor(PrimaryColor);
      tft.drawRightString(myLanguage[language][0], 305, 30, GFXFF);
      if (showrdserrors) tft.drawRightString(myLanguage[language][42], 305, 50, GFXFF); else tft.drawRightString(myLanguage[language][30], 305, 50, GFXFF);
      if (softmutefm) tft.drawRightString(myLanguage[language][42], 305, 70, GFXFF); else tft.drawRightString(myLanguage[language][30], 305, 70, GFXFF);
      if (softmuteam) tft.drawRightString(myLanguage[language][42], 305, 90, GFXFF); else tft.drawRightString(myLanguage[language][30], 305, 90, GFXFF);
      if (edgebeep) tft.drawRightString(myLanguage[language][42], 305, 110, GFXFF); else tft.drawRightString(myLanguage[language][30], 305, 110, GFXFF);
      if (region == 0) tft.drawRightString(myLanguage[language][47], 305, 130, GFXFF);
      if (region == 1) tft.drawRightString(myLanguage[language][48], 305, 130, GFXFF);
      if (radio.rds.underscore) tft.drawRightString(myLanguage[language][42], 305, 150, GFXFF); else tft.drawRightString(myLanguage[language][30], 305, 150, GFXFF);
      if (USBmode) tft.drawRightString("RDS Spy", 305, 170, GFXFF); else tft.drawRightString("XDR-GTK", 305, 170, GFXFF);
      if (wifi) tft.drawRightString(myLanguage[language][42], 305, 190, GFXFF); else tft.drawRightString(myLanguage[language][30], 305, 190, GFXFF);
      tft.drawRightString("→", 305, 210, GFXFF);
      break;

    case 3:
      tft.drawString(myLanguage[language][58], 14, 30, GFXFF);
      tft.drawString(myLanguage[language][59], 14, 50, GFXFF);
      tft.drawString(myLanguage[language][60], 14, 70, GFXFF);
      tft.drawString(myLanguage[language][61], 14, 90, GFXFF);
      tft.drawString(myLanguage[language][62], 14, 110, GFXFF);
      tft.drawString(myLanguage[language][63], 14, 130, GFXFF);
      tft.drawString(myLanguage[language][64], 14, 150, GFXFF);
      tft.drawString(myLanguage[language][65], 14, 170, GFXFF);
      tft.drawString(myLanguage[language][67], 14, 190, GFXFF);
      tft.drawString(myLanguage[language][68], 14, 210, GFXFF);
      if (amnb != 0) tft.drawRightString("%", 305, 150, GFXFF); else tft.drawRightString(myLanguage[language][30], 305, 150, GFXFF);
      if (fmnb != 0) tft.drawRightString("%", 305, 170, GFXFF); else tft.drawRightString(myLanguage[language][30], 305, 170, GFXFF);
      tft.setTextColor(PrimaryColor);
      tft.drawRightString(String(WiFi.localIP()[0]) + "." + String(WiFi.localIP()[1]) + "." + String(WiFi.localIP()[2]) + "." + String(subnetclient, DEC), 305, 30, GFXFF);
      if (showSWMIBand) tft.drawRightString(myLanguage[language][42], 305, 50, GFXFF); else tft.drawRightString(myLanguage[language][30], 305, 50, GFXFF);
      if (radio.rds.filter) tft.drawRightString(myLanguage[language][42], 305, 70, GFXFF); else tft.drawRightString(myLanguage[language][30], 305, 70, GFXFF);
      if (radio.rds.pierrors) tft.drawRightString(myLanguage[language][42], 305, 90, GFXFF); else tft.drawRightString(myLanguage[language][30], 305, 90, GFXFF);
      if (showsquelch) tft.drawRightString(myLanguage[language][42], 305, 110, GFXFF); else tft.drawRightString(myLanguage[language][30], 305, 110, GFXFF);
      if (showmodulation) tft.drawRightString(myLanguage[language][42], 305, 130, GFXFF); else tft.drawRightString(myLanguage[language][30], 305, 130, GFXFF);
      if (amnb != 0) tft.drawRightString(String(amnb, DEC), 265, 150, GFXFF); else tft.drawRightString(myLanguage[language][30], 305, 150, GFXFF);
      if (fmnb != 0) tft.drawRightString(String(fmnb, DEC), 265, 170, GFXFF); else tft.drawRightString(myLanguage[language][30], 305, 170, GFXFF);
      if (audiomode) tft.drawRightString("MPX", 305, 190, GFXFF); else tft.drawRightString("Stereo", 305, 190, GFXFF);
      if (specialstepOIRT) tft.drawRightString(myLanguage[language][42], 305, 210, GFXFF); else tft.drawRightString(myLanguage[language][30], 305, 210, GFXFF);
      break;
    case 4:
      tft.drawRightString("KHz", 305, 90, GFXFF);
      tft.drawRightString("dB", 305, 130, GFXFF);
      if (screensaverset) tft.drawRightString(myLanguage[language][92], 305, 110, GFXFF);
      tft.drawString(myLanguage[language][77], 14, 30, GFXFF);
      tft.drawString(myLanguage[language][70], 14, 50, GFXFF);
      tft.drawString(myLanguage[language][74], 14, 70, GFXFF);
      tft.drawString(myLanguage[language][90], 14, 90, GFXFF);
      tft.drawString(myLanguage[language][91], 14, 110, GFXFF);
      tft.drawString(myLanguage[language][97], 14, 130, GFXFF);
      tft.drawString(myLanguage[language][98], 14, 150, GFXFF);
      tft.drawString(myLanguage[language][99], 14, 170, GFXFF);
      tft.setTextColor(PrimaryColor);
      tft.drawRightString(CurrentThemeString, 305, 30, GFXFF);
      ShowPowerOptions(false);
      if (fmdefaultstepsize) tft.drawRightString(String(FREQ_FM_STEP_100K * 10, DEC), 265, 90, GFXFF); else tft.drawRightString(String(FREQ_FM_STEP_50K * 10, DEC), 265, 90, GFXFF);
      if (!screensaverset) tft.drawRightString(myLanguage[language][30], 305, 110, GFXFF); else tft.drawRightString(String(screensaverOptions[screensaverset], DEC), 265, 110, GFXFF);
      if (AMLevelOffset > 0) tft.drawRightString("+" + String(AMLevelOffset, DEC), 265, 130, GFXFF); else tft.drawRightString(String(AMLevelOffset, DEC), 265, 130, GFXFF);
      if (af) tft.drawRightString(myLanguage[language][42], 305, 170, GFXFF); else tft.drawRightString(myLanguage[language][30], 305, 170, GFXFF);
      tft.drawRightString(unitString[unit], 305, 150, GFXFF);
      break;
  }
  analogWrite(SMETERPIN, 0);
}

void MuteScreen(bool setting) {
  if (!setting && screenmute) {
    screenmute = false;
    setupmode = true;
    tft.writecommand(0x11);
    analogWrite(CONTRASTPIN, ContrastSet * 2 + 27);
    radio.clearRDS(fullsearchrds);
    BuildDisplay();
    setupmode = false;
  } else if (setting && !screenmute) {
    screenmute = true;
    analogWrite(CONTRASTPIN, 0);
    tft.writecommand(0x10);
  }
}

void ShowAFEON() {
  tft.setTextColor(PrimaryColor);

  if (radio.rds.hasAF) {
    if (hasafold == false) {
      tft.setTextColor(BackgroundColor);
      tft.drawString(myLanguage[language][87], 6, 48, GFXFF);
      tft.setTextColor(PrimaryColor);
      hasafold = true;
    }

    if (radio.af_counter > 33) {
      if (!afpage) {
        afpage = true;
        afpagenr = 1;
      }
    } else {
      afpagenr = 0;
    }

    if (af_counterold != radio.af_counter) {
      Serial.println(radio.af_counter);
      tft.fillRect(2, 53, 177, 165, BackgroundColor);
      for (byte i = 0; i < radio.af_counter; i++) {
        byte x = i - (afpagenr == 2 ? 33 : 0);
        tft.drawRightString((radio.af[i].filler ? "(f) " : "") + String(radio.af[i].frequency / 100) + "." + String((radio.af[i].frequency % 100) / 10),  56 + (x > 10 ? 60 : 0) + (x > 21 ? 60 : 0), 48 + (15 * x) - (x > 10 ? 165 : 0) - (x > 21 ? 165 : 0), GFXFF);
        if (i == 32  + (afpagenr == 2 ? 33 : 0)) i = 254;
      }

      if (radio.af_counter > 11 + (afpagenr == 2 ? 33 : 0)) tft.drawLine(65, 54, 65, 210, SecondaryColor);
      if (radio.af_counter > 22 + (afpagenr == 2 ? 33 : 0)) tft.drawLine(125, 54, 125, 210, SecondaryColor);
      tft.setTextColor(SecondaryColor);
      if (afpage == true) tft.drawRightString(String(afpagenr) + "/2", 315, 218, GFXFF);
    }
    af_counterold = radio.af_counter;
  }

  if (radio.rds.hasEON) {
    if (haseonold == false) {
      tft.setTextColor(BackgroundColor);
      tft.drawString(myLanguage[language][88], 184, 48, GFXFF);
      tft.setTextColor(PrimaryColor);
    }
    haseonold = true;
    for (byte i = 0; i < radio.eon_counter; i++) {
      tft.drawString(String(radio.eon[i].picode), 184, 48 + (15 * i), GFXFF);
      if (radio.eon[i].ps.length() > 0) {
        tft.setTextColor(ActiveColor);
        tft.drawString("PS :", 218, 30, GFXFF);
        tft.setTextColor(PrimaryColor);
        if (radio.eon[i].ps != eonpsold[i]) {
          tft.setTextColor(BackgroundColor);
          tft.drawString(String(eonpsold[i]), 218, 48 + (15 * i), GFXFF);
          eonpsold[i] = radio.eon[i].ps;
        }
        tft.drawString(String(radio.eon[i].ps), 218, 48 + (15 * i), GFXFF);
      }

      if (radio.eon[i].mappedfreq > 0) {
        tft.setTextColor(ActiveColor);
        tft.drawRightString("FREQ:", 316, 30, GFXFF);
        tft.setTextColor(PrimaryColor);
        if (radio.eon[i].mappedfreq != mappedfreqold[i]) {
          tft.setTextColor(BackgroundColor);
          tft.drawRightString(String(mappedfreqold[i] / 100) + "." + String((mappedfreqold[i] % 100) / 10), 316, 48 + (15 * i), GFXFF);
          tft.setTextColor(PrimaryColor);
        }
        tft.drawRightString(String(radio.eon[i].mappedfreq / 100) + "." + String((radio.eon[i].mappedfreq % 100) / 10), 316, 48 + (15 * i), GFXFF);
        mappedfreqold[i] = radio.eon[i].mappedfreq;
      }
      if (i == 10) i = 254;
    }
  }
}

void BuildAFScreen() {
  afscreen = true;
  advancedRDS = false;
  if (theme == 0) {
    tft.invertDisplay(colorinvert);
    tft.fillScreen(BackgroundColor);
    tft.drawRect(0, 0, 320, 240, FrameColor);
    tft.drawLine(0, 30, 320, 30, FrameColor);
    tft.drawLine(0, 218, 320, 218, FrameColor);
    tft.drawLine(180, 30, 180, 218, FrameColor);
    tft.setTextColor(ActiveColor);
    tft.setFreeFont(FONT14);
    tft.drawString("kHz", 225, -5, GFXFF);
    tft.setTextColor(ActiveColor);
    tft.setFreeFont(FONT7);
    tft.drawString("AF : ", 4, 30, GFXFF);
    tft.drawString("PI : ", 184, 30, GFXFF);
    tft.drawCentreString(myLanguage[language][93], 160, 218, GFXFF);
    tft.setTextColor(PrimaryColor);
    tft.drawString(myLanguage[language][88], 184, 48, GFXFF);
    tft.drawString(myLanguage[language][87], 6, 48, GFXFF);

    tft.drawRoundRect(35, 32, 138, 20, 5, ActiveColor);

    for (byte i = 0; i < 11; i++) mappedfreqold[i] = 0;
    RDSstatusold = false;
    ShowFreq(0);
    Stereostatusold = false;
    haseonold = false;
    hasafold = false;
    BWreset = true;
    SStatusold = 2000;
    rssiold = 2000;
    batteryold = 6;
    af_counterold = 254;
    strcpy(radioIdPrevious, "0");
    programServicePrevious = "0";
    for (byte i = 0; i < 11; i++) eonpsold[i] = "";
  }
}

void BuildAdvancedRDS() {
  afscreen = false;
  afpage = false;
  afpagenr = 0;
  advancedRDS = true;
  ScreensaverTimerSet(OFF);
  if (theme == 0) {
    tft.invertDisplay(colorinvert);
    tft.fillScreen(BackgroundColor);
    tft.drawRect(0, 0, 320, 240, FrameColor);
    tft.drawLine(0, 30, 320, 30, FrameColor);
    tft.drawLine(0, 70, 320, 70, FrameColor);
    tft.drawLine(0, 103, 320, 103, FrameColor);
    tft.drawLine(0, 128, 320, 128, FrameColor);
    tft.drawLine(64, 30, 64, 0, FrameColor);
    tft.drawLine(210, 30, 210, 240, FrameColor);
    tft.drawLine(268, 30, 268, 0, FrameColor);
    tft.drawLine(108, 30, 108, 0, FrameColor);
    tft.drawLine(174, 30, 174, 0, FrameColor);
    tft.drawLine(0, 143, 210, 143, FrameColor);
    tft.drawLine(0, 168, 210, 168, FrameColor);
    tft.drawLine(0, 193, 320, 193, FrameColor);
    tft.drawLine(0, 218, 210, 218, FrameColor);
    tft.drawRect(0, 0, 320, 240, FrameColor);

    tft.setTextColor(ActiveColor);
    tft.setFreeFont(FONT7);
    tft.drawString("ERRORS : ", 6, 30, GFXFF);
    tft.drawRightString(unitString[unit],  310, 45, GFXFF);
    if (region == 0) tft.drawString("PI : ", 216, 76, GFXFF);
    if (region == 1) tft.drawString("ID : ", 216, 76, GFXFF);
    tft.drawString("PS : ", 6, 76, GFXFF);
    tft.drawString("PTY : ", 6, 105, GFXFF);
    tft.drawString("RT + : ", 6, 146, GFXFF);
    tft.drawString("EON : ", 6, 171, GFXFF);
    tft.drawString("AF : ", 6, 196, GFXFF);
    tft.drawString("RT : ", 6, 218, GFXFF);
    tft.drawString("PTYN : ", 216, 105, GFXFF);
    tft.drawString("A : ", 60, 30, GFXFF);
    tft.drawString("B : ", 100, 30, GFXFF);
    tft.drawString("C : ", 140, 30, GFXFF);
    tft.drawString("D : ", 180, 30, GFXFF);
    tft.drawString("ECC : ", 216, 190, GFXFF);
    tft.drawString("LIC : ", 216, 205, GFXFF);
    tft.drawString("PIN : ", 216, 220, GFXFF);
    tft.drawRightString("Dynamic PTY", 300, 128, GFXFF);
    tft.drawRightString("Artificial Head", 300, 143, GFXFF);
    tft.drawRightString("Compressed", 300, 158, GFXFF);
    tft.drawRightString("Has Stereo", 300, 173, GFXFF);

    tft.fillCircle(80, 41, 5, TFT_RED);
    tft.fillCircle(120, 41, 5, TFT_RED);
    tft.fillCircle(160, 41, 5, TFT_RED);
    tft.fillCircle(200, 41, 5, TFT_RED);

    tft.fillCircle(310, 139, 5, TFT_RED);
    tft.fillCircle(310, 155, 5, TFT_RED);
    tft.fillCircle(310, 170, 5, TFT_RED);
    tft.fillCircle(310, 185, 5, TFT_RED);

    for (int i; i < 33; i++) tft.fillCircle((6 * i) + 10, 136, 2, GreyoutColor);

    tft.setTextColor(ActiveColor);
    tft.setFreeFont(FONT14);
    tft.drawString("kHz", 225, -5, GFXFF);

    tft.drawCircle(81, 15, 10, GreyoutColor);
    tft.drawCircle(81, 15, 9, GreyoutColor);
    tft.drawCircle(91, 15, 10, GreyoutColor);
    tft.drawCircle(91, 15, 9, GreyoutColor);
    tft.drawBitmap(110, 5, RDSLogo, 67, 22, GreyoutColor);

    if (StereoToggle == false) {
      tft.drawCircle(86, 15, 10, PrimaryColor);
      tft.drawCircle(86, 15, 9, PrimaryColor);
    }

    tft.setFreeFont(FONT7);
    tft.setTextColor(SecondaryColor);
    if (radio.rds.hasCT) tft.drawRightString(rds_clockold, 205, 105, GFXFF);
    tft.setTextColor(GreyoutColor);
    tft.drawString("TP",  6, 45, GFXFF);
    tft.drawString("TA",  24, 45, GFXFF);
    tft.drawString("AF",  42, 45, GFXFF);
    tft.drawString("CT",  62, 45, GFXFF);
    tft.drawString("TMC",  82, 45, GFXFF);
    tft.drawString("RT + ",  116, 45, GFXFF);
    tft.drawString("EON",  148, 45, GFXFF);
    tft.drawString("M",  185, 45, GFXFF);
    tft.drawString("S",  198, 45, GFXFF);
  }

  RDSstatusold = false;
  ShowFreq(0);
  Stereostatusold = false;
  SStatusold = 2000;
  SStatus = 100;
  rssiold = 2000;
  rdsblockold = 33;
  batteryold = 6;

  strcpy(programTypePrevious, "0");
  strcpy(radioIdPrevious, "0");
  programServicePrevious = "0";
  ptynold = " ";
  MSold = 0;
  ECCold = 254;
  licold = 254;
  af_counterold = 254;
  TAold = false;
  TPold = false;
  hastmcold = false;
  errorAold = true;
  errorBold = true;
  errorCold = true;
  errorDold = true;
  dynamicPTYold = false;
  artheadold = false;
  compressedold = false;
  rdsstereoold = false;
  hasafold = false;
  haseonold = false;
  BWreset = true;
  pinstringold = "";
  ShowMemoryPos();
}

void BuildDisplay() {
  afscreen = false;
  advancedRDS = false;
  if (theme == 0) {
    tft.invertDisplay(colorinvert);
    tft.fillScreen(BackgroundColor);
    tft.drawRect(0, 0, 320, 240, FrameColor);
    tft.drawLine(0, 30, 320, 30, FrameColor);
    tft.drawLine(0, 100, 320, 100, FrameColor);
    tft.drawLine(64, 30, 64, 0, FrameColor);
    tft.drawLine(210, 100, 210, 218, FrameColor);
    tft.drawLine(268, 30, 268, 0, FrameColor);
    tft.drawLine(0, 165, 210, 165, FrameColor);
    tft.drawLine(0, 187, 320, 187, FrameColor);
    tft.drawLine(0, 218, 320, 218, FrameColor);
    tft.drawLine(108, 30, 108, 0, FrameColor);
    tft.drawLine(174, 30, 174, 0, FrameColor);
    tft.drawLine(20, 120, 200, 120, TFT_DARKGREY);
    if (!showmodulation) tft.drawLine(20, 150, 200, 150, GreyoutColor); else tft.drawLine(20, 150, 200, 150, TFT_DARKGREY);
    for (byte segments = 0; segments < 94; segments++) {
      if (segments > 54) {
        if (((segments - 53) % 10) == 0) {
          tft.fillRect(16 + (2 * segments), 117, 2, 3, TFT_RED);
          if (!showmodulation) tft.fillRect(16 + (2 * segments), 147, 2, 3, GreyoutColor); else tft.fillRect(16 + (2 * segments), 147, 2, 3, TFT_RED);
        }
      } else {
        if (((segments + 1) % 6) == 0) {
          tft.fillRect(16 + (2 * segments), 117, 2, 3, TFT_GREEN);
          if (!showmodulation) tft.fillRect(16 + (2 * segments), 147, 2, 3, GreyoutColor); else tft.fillRect(16 + (2 * segments), 147, 2, 3, TFT_GREEN);
        }
      }
    }
    tft.setTextColor(ActiveColor);
    tft.setFreeFont(FONT7);
    if (showsquelch) tft.drawString("SQ: ", 216, 150, GFXFF);
    tft.drawString("S/N", 250, 164, GFXFF);
    tft.drawString("dB",  300, 164, GFXFF);
    tft.drawCentreString("S", 7, 101, GFXFF);
    if (region == 0) tft.drawString("PI: ", 216, 191, GFXFF);
    if (region == 1) tft.drawString("ID: ", 216, 191, GFXFF);
    tft.drawString("PS: ", 6, 191, GFXFF);
    tft.drawString("PTY: ", 6, 164, GFXFF);
    tft.drawString("1", 24, 116, GFXFF);
    tft.drawString("3", 48, 116, GFXFF);
    tft.drawString("5", 72, 116, GFXFF);
    tft.drawString("7", 96, 116, GFXFF);
    tft.drawString("9", 120, 116, GFXFF);
    tft.drawString(" + 10", 134, 116, GFXFF);
    tft.drawString(" + 30", 174, 116, GFXFF);
    if (!showmodulation) tft.setTextColor(GreyoutColor);
    tft.drawCentreString("M", 7, 132, GFXFF);
    tft.drawString("10", 27, 146, GFXFF);
    tft.drawString("30", 57, 146, GFXFF);
    tft.drawString("50", 87, 146, GFXFF);
    tft.drawString("70", 117, 146, GFXFF);
    tft.drawString("100", 164, 146, GFXFF);
    tft.setTextColor(ActiveColor);
    tft.setFreeFont(FONT14);
    tft.drawString("kHz", 225, -5, GFXFF);
    tft.setTextColor(ActiveColor);
    if (band == BAND_FM) tft.drawString("MHz", 258, 67, GFXFF); else tft.drawString("kHz", 258, 67, GFXFF);

    tft.drawRoundRect(249, 56, 30, 20, 5, GreyoutColor);
    tft.drawRoundRect(287, 56, 30, 20, 5, GreyoutColor);
    tft.drawCircle(81, 15, 10, GreyoutColor);
    tft.drawCircle(81, 15, 9, GreyoutColor);
    tft.drawCircle(91, 15, 10, GreyoutColor);
    tft.drawCircle(91, 15, 9, GreyoutColor);
    tft.drawBitmap(110, 5, RDSLogo, 67, 22, GreyoutColor);
    if (StereoToggle == false) {
      tft.drawCircle(86, 15, 10, PrimaryColor);
      tft.drawCircle(86, 15, 9, PrimaryColor);
    }
    tft.setTextColor(SecondaryColor);
    tft.setFreeFont(FONT7);
    if (band == BAND_LW) tft.drawString("LW", 50, 26, GFXFF);
    else if (band == BAND_MW) tft.drawString("MW", 50, 26, GFXFF);
    else if (band == BAND_SW) tft.drawString("SW", 50, 26, GFXFF);
    else tft.drawString("FM", 50, 26, GFXFF);
  }


  // WORKING ON THIS!
  /*
    if (theme == 1) {
    tft.setFreeFont(FONT7);
    tft.fillScreen(BackgroundColor);
    tft.fillRect(12, 105, 2, 50, TFT_RED);
    tft.fillRect(305, 105, 2, 50, TFT_RED);
    tft.fillRect(0, 208, 50, 2, TFT_RED);
    tft.fillRect(270, 208, 50, 2, TFT_RED);
    tft.fillRect(12, 18, 293, 2, TFT_RED);
    tft.fillRect(30, 220, 98, 6, TFT_RED);
    tft.fillRect(204, 220, 98, 6, TFT_RED);

    tft.fillRect(44, 138, 2, 14, ActiveColor);
    tft.fillRect(70, 138, 2, 14, ActiveColor);
    tft.fillRect(96, 38, 20, 4, TFT_DARKGREY);
    tft.fillRect(129, 38, 20, 4, TFT_DARKGREY);
    tft.fillRect(173, 38, 20, 4, TFT_DARKGREY);
    tft.fillRect(207, 38, 20, 4, TFT_DARKGREY);

    tft.setFreeFont(GUI2_FONT12);
    tft.setTextColor(ActiveColor);
    tft.drawString("PI : ", 26, 102, GFXFF);

    tft.setFreeFont(GUI2_FONT12);
    tft.setTextColor(PrimaryColor);
    tft.drawString("232F", 56, 102, GFXFF);

    tft.setFreeFont(GUI2_FONT12);
    tft.setTextColor(PrimaryColor);
    tft.drawRightString("36.2", 250, 102, GFXFF);

    tft.setFreeFont(GUI2_FONT12);
    tft.setTextColor(ActiveColor);
    tft.drawRightString("dBf", 294, 102, GFXFF);

    tft.setTextColor(ActiveColor);
    tft.setFreeFont(GUI2_FONT7);
    tft.drawRightString("dB S / N", 294, 132, GFXFF);

    tft.setFreeFont(GUI2_FONT7);
    tft.setTextColor(PrimaryColor);
    tft.drawRightString("20", 244, 132, GFXFF);

    tft.setTextColor(PrimaryColor);
    tft.setFreeFont(GUI2_FONT12);
    tft.drawCentreString("R - ZURNAL", 160, 156, GFXFF);

    tft.setTextColor(TFT_DARKGREY);
    tft.setFreeFont(GUI2_FONT7);
    tft.drawCentreString("Zelena vlna - volejte bezplatne 800 500 553 !", 160, 180, GFXFF);

    tft.setFreeFont(GUI2_FONT7);
    tft.setTextColor(TFT_DARKGREY);
    tft.drawCentreString("Information", 160, 140, GFXFF);

    tft.setTextColor(PrimaryColor);
    tft.setFreeFont(GUI2_FONT7);
    tft.drawRightString("TP", 40, 132, GFXFF);

    tft.setTextColor(TFT_DARKGREY);
    tft.setFreeFont(GUI2_FONT7);
    tft.drawCentreString("TA", 57, 132, GFXFF);

    tft.setTextColor(TFT_DARKGREY);
    tft.setFreeFont(GUI2_FONT7);
    tft.drawString("AF", 76, 132, GFXFF);

    tft.setTextColor(ActiveColor);
    tft.setFreeFont(GUI2_FONT12);
    tft.drawString("kHz", 162, 92, GFXFF);

    tft.setTextColor(PrimaryColor);
    tft.setFreeFont(GUI2_FONT12);
    tft.drawRightString("236", 158, 92, GFXFF);

    tft.setTextColor(PrimaryColor);
    tft.setFreeFont(FONTDEC);
    tft.drawCentreString("88.50", 160, 49, GFXFF);

    tft.setFreeFont(GUI2_FONT7);
    tft.setTextColor(TFT_DARKGREY);
    tft.drawCentreString("MANUAL", 160, 16, GFXFF);

    tft.setFreeFont(GUI2_FONT7);
    tft.setTextColor(ActiveColor);
    tft.drawCentreString("21 : 35", 160, -4, GFXFF);

    tft.setFreeFont(GUI2_FONT7);
    tft.setTextColor(ActiveColor);
    tft.drawString("89 % ", 243, -4, GFXFF);

    tft.setFreeFont(GUI2_FONT12);
    tft.setTextColor(PrimaryColor);
    tft.drawString("S", 14, 204, GFXFF);
    tft.drawString("M", 182, 204, GFXFF);

    tft.setFreeFont(GUI2_FONT7);
    tft.setTextColor(TFT_DARKGREY);
    tft.drawString("1 3 5 7 9  + 10  + 30", 30, 220, GFXFF);
    tft.drawString("20 50 70 100 120", 204, 220, GFXFF);

    for (;;);
    }
  */
  RDSstatusold = false;
  Stereostatusold = false;
  ShowFreq(0);
  ShowTuneMode();
  updateBW();
  ShowStepSize();
  ShowMemoryPos();
  updateiMS();
  updateEQ();
  Squelchold = -2;
  SStatusold = 2000;
  SStatus = 100;
  rssiold = 2000;
  SNRold = 254;
  af_counterold = 254;
  batteryold = 6;
  strcpy(programTypePrevious, "0");
  strcpy(radioIdPrevious, "0");
  programServicePrevious = "0";
  BWreset = true;
}

void ShowFreq(int mode) {
  if (screenmute == false) {
    if (setupmode == false) {
      if (band == 1) { // Fix Me :take care of 9K/10K Step
        if (freqold < 2000 && frequency_AM >= 2000 && stepsize == 0) if (frequency_AM != 27000 && freqold != 144) radio.SetFreqAM(2000);
        if (freqold >= 2000 && frequency_AM < 2000 && stepsize == 0) if (frequency_AM != 144 && freqold != 27000) radio.SetFreqAM(1998);
      }
    }

    if (screenmute == false) {
      detachInterrupt(digitalPinToInterrupt(ROTARY_PIN_A));
      detachInterrupt(digitalPinToInterrupt(ROTARY_PIN_B));
      if (band != BAND_FM ) {
        unsigned int freq = frequency_AM;
        String count = String(freq, DEC);
        if (setupmode == false && count.length() != freqoldcount || mode != 0) {
          tft.setTextColor(BackgroundColor);
          tft.drawRightString(String(freqold), 248, 45, 7);
        }
        tft.setTextColor(PrimaryColor, BackgroundColor);
        tft.drawRightString(String(freq), 248, 45, 7);
        freqold = freq;
        freqoldcount = count.length();

        if (band == BAND_SW && showSWMIBand) {
          DivdeSWMIBand();
          updateSWMIBand();
        }

      } else {
        unsigned int freq = frequency + ConverterSet * 100;
        if (advancedRDS) {
          for (int i; i < 33; i++) tft.fillCircle((6 * i) + 10, 136, 2, GreyoutColor);
          tft.setFreeFont(FONT7);
          tft.setTextColor(BackgroundColor);
          tft.drawRightString(String(freqold / 100) + "." + (freqold % 100 < 10 ? "0" : "") + String(freqold % 100) + " MHz",  310, 30, GFXFF);
          tft.setTextColor(PrimaryColor);
          tft.drawRightString(String(freq / 100) + "." + (freq % 100 < 10 ? "0" : "") + String(freq % 100) + " MHz",  310, 30, GFXFF);
          freqold = freq;
        } else if (afscreen) {
          tft.setFreeFont(FONT7);
          tft.setTextColor(BackgroundColor);
          tft.drawRightString(String(freqold / 100) + "." + (freqold % 100 < 10 ? "0" : "") + String(freqold % 100),  170, 30, GFXFF);
          tft.setTextColor(SecondaryColor);
          tft.drawRightString(String(freq / 100) + "." + (freq % 100 < 10 ? "0" : "") + String(freq % 100),  170, 30, GFXFF);
          freqold = freq;
        } else {
          String count = String(freq / 100, DEC);
          if (setupmode == false && count.length() != freqoldcount || mode != 0) {
            tft.setTextColor(BackgroundColor);
            if (freqoldcount <= 2) tft.setCursor (108, 45);
            if (freqoldcount == 3) tft.setCursor (76, 45);
            if (freqoldcount >= 4) tft.setCursor (44, 45);
            tft.setTextFont(7);
            tft.print(freqold / 100);
            if (band == BAND_FM) {
              tft.print(".");
              if (freqold % 100 < 10) tft.print("0");
              tft.print(freqold % 100);
            }
          }

          tft.setTextColor(PrimaryColor, BackgroundColor);
          if (mode == 0) {
            if (count.length() <= 2) tft.setCursor (108, 45);
            if (count.length() == 3) tft.setCursor (76, 45);
            if (count.length() >= 4) tft.setCursor (44, 45);
            tft.setTextFont(7);
            tft.print(freq / 100);
            tft.print(".");
            if (freq % 100 < 10) tft.print("0");
            tft.print(freq % 100);
            freqold = freq;
            freqoldcount = count.length();
          } else if (mode == 1) {
            tft.setTextColor(BackgroundColor);
            if (freqoldcount <= 2) tft.setCursor (98, 45);
            if (freqoldcount == 3) tft.setCursor (71, 45);
            if (freqoldcount == 4) tft.setCursor (44, 45);
            tft.setTextFont(1);
            tft.print(freqold / 100);
            tft.print(".");
            if (freqold % 100 < 10) tft.print("0");
            tft.print(freqold % 100);
          }
        }
      }
      attachInterrupt(digitalPinToInterrupt(ROTARY_PIN_A), read_encoder, CHANGE);
      attachInterrupt(digitalPinToInterrupt(ROTARY_PIN_B), read_encoder, CHANGE);
    }
    strcpy(programTypePrevious, "0");
    strcpy(radioIdPrevious, "0");
    programServicePrevious = "0";

    if (wifi) {
      Udp.beginPacket(remoteip, 9030);
      Udp.print("from = TEF tuner; freq = ");
      if (band != BAND_FM) Udp.print(String(frequency_AM) + "000; ClearRDS = 1"); else Udp.print(String(frequency) + "0000; ClearRDS = 1");
      Udp.endPacket();
    }
  }
}

void ShowSignalLevel() {
  if (screenmute == false) {
    if (millis() >= snrupdatetimer + TIMER_SNR_TIMER) {
      snrupdatetimer = millis();
      if (!advancedRDS) {
        if (SNR > (SNRold + 1) || SNR < (SNRold - 1)) {
          tft.setFreeFont(FONT7);
          tft.setTextColor(BackgroundColor);
          if (SNRold == 0) tft.drawRightString("--", 294, 164, GFXFF); else tft.drawRightString(String(SNRold), 294, 164, GFXFF);
          tft.setTextColor(PrimaryColor, BackgroundColor);
          if (tuned == true) {
            if (SNR == 0) tft.drawRightString("--", 294, 164, GFXFF); else tft.drawRightString(String(SNR), 294, 164, GFXFF);
            SNRold = SNR;
          } else {
            tft.drawRightString("--", 294, 164, GFXFF);
            SNRold = 0;
          }
        }
      }
    }
    SAvg = (((SAvg * 9) + 5) / 10) + SStatus;
    SAvg2 = (((SAvg2 * 9) + 5) / 10) + SNR;

    float sval = 0;
    int16_t smeter = 0;
    int16_t segments;

    if (SStatus > 0) {
      if (SStatus < 1000) {
        sval = 51 * ((pow(10, (((float)SStatus) / 1000))) - 1);
        smeter = int16_t(sval);
      } else {
        smeter = 511;
      }
    }

    smeter = int16_t(sval);
    SStatus = SAvg / 10;
    SNR = SAvg2 / 10;

    if (menu == false) analogWrite(SMETERPIN, smeter);

    int SStatusprint;
    if (unit == 0) SStatusprint = SStatus;
    if (unit == 1) SStatusprint = ((SStatus * 100) + 10875) / 100;
    if (unit == 2) SStatusprint = ((float(SStatus / 10) - 10 * log10(75) - 90) * 10);

    if (SStatusprint > (SStatusold + 3) || SStatusprint < (SStatusold - 3)) {
      if (advancedRDS) {
        tft.setFreeFont(FONT7);
        tft.setTextColor(BackgroundColor);
        tft.drawRightString(String(SStatusold / 10) + "." + String(abs(SStatusold % 10)),  274, 45, GFXFF);
        tft.setTextColor(PrimaryColor);
        tft.drawRightString(String(SStatusprint / 10) + "." + String(abs(SStatusprint % 10)),  274, 45, GFXFF);
        SStatusold = SStatusprint;
      } else {
        tft.setFreeFont(FONT24);
        tft.setTextColor(BackgroundColor);
        if (SStatusold / 10 != SStatusprint / 10) tft.drawRightString(String(SStatusold / 10), 290, 106, GFXFF);
        tft.setFreeFont(FONT14);
        tft.drawString("." + String(abs(SStatusold % 10)), 296, 97, GFXFF);
        tft.setFreeFont(FONT24);
        tft.setTextColor(PrimaryColor);
        tft.drawRightString(String(SStatusprint / 10), 290, 106, GFXFF);
        tft.setFreeFont(FONT14);
        tft.drawString("." + String(abs(SStatusprint % 10)), 296, 97, GFXFF);

        if (band == BAND_FM) segments = (SStatus + 200) / 10; else segments = (SStatus + 200) / 10;

        tft.fillRect(16, 109, 2 * constrain(segments, 0, 54), 8, TFT_GREEN);
        tft.fillRect(16 + 2 * 54, 109, 2 * (constrain(segments, 54, 94) - 54), 8, TFT_RED);
        tft.fillRect(16 + 2 * constrain(segments, 0, 94), 109, 2 * (94 - constrain(segments, 0, 94)), 8, GreyoutColor);

        SStatusold = SStatusprint;
        tft.setTextColor(ActiveColor);
        tft.setFreeFont(FONT7);
        tft.drawString(unitString[unit], 282, 144, GFXFF);
      }
      if (wifi) {
        Udp.beginPacket(remoteip, 9030);
        Udp.print("from = TEF tuner; RcvLevel = ");
        Udp.print(SStatus / 10);
        Udp.endPacket();
      }
    }
  }
}

void ShowRDSLogo(bool RDSstatus) {
  if (screenmute == false) {
    if (RDSstatus != RDSstatusold) {
      if (RDSstatus == true) tft.drawBitmap(110, 5, RDSLogo, 67, 22, RDSColor); else tft.drawBitmap(110, 5, RDSLogo, 67, 22, GreyoutColor);
      RDSstatusold = RDSstatus;
    }
  }
}

void ShowStereoStatus() {
  if (StereoToggle == true) {
    if (band == BAND_FM) Stereostatus = radio.getStereoStatus(); else Stereostatus = 0;
    if (Stereostatus != Stereostatusold) {
      if (Stereostatus == true && screenmute == false) {
        tft.drawCircle(81, 15, 10, StereoColor);
        tft.drawCircle(81, 15, 9, StereoColor);
        tft.drawCircle(91, 15, 10, StereoColor);
        tft.drawCircle(91, 15, 9, StereoColor);
      } else {
        if (screenmute == false) {
          tft.drawCircle(81, 15, 10, GreyoutColor);
          tft.drawCircle(81, 15, 9, GreyoutColor);
          tft.drawCircle(91, 15, 10, GreyoutColor);
          tft.drawCircle(91, 15, 9, GreyoutColor);
        }
      }
      Stereostatusold = Stereostatus;
    }
  }
}

void ShowOffset() {
  if (OStatus != OStatusold) {
    if (millis() >= offsetupdatetimer + TIMER_OFFSET_TIMER) {
      offsetupdatetimer = millis();
    } else {
      return;
    }

    if (band == BAND_FM) {
      if (OStatus < -500) {
        tft.fillTriangle(6, 8, 6, 22, 14, 14, GreyoutColor);
        tft.fillTriangle(18, 8, 18, 22, 26, 14, GreyoutColor);
        tft.fillCircle(32, 15, 3, GreyoutColor);
        tft.fillTriangle(38, 14, 46, 8, 46, 22, GreyoutColor);
        tft.fillTriangle(50, 14, 58, 8, 58, 22, TFT_RED);
        tuned = false;
      } else if (OStatus < -250 && OStatus > -500) {
        tft.fillTriangle(6, 8, 6, 22, 14, 14, GreyoutColor);
        tft.fillTriangle(18, 8, 18, 22, 26, 14, GreyoutColor);
        tft.fillCircle(32, 15, 3, GreyoutColor);
        tft.fillTriangle(38, 14, 46, 8, 46, 22, TFT_RED);
        tft.fillTriangle(50, 14, 58, 8, 58, 22, GreyoutColor);
        tuned = false;
      } else if (USN < 250 && WAM < 250 && OStatus > -250 && OStatus < 250 && SQ == false) {
        tft.fillTriangle(6, 8, 6, 22, 14, 14, GreyoutColor);
        tft.fillTriangle(18, 8, 18, 22, 26, 14, GreyoutColor);
        tft.fillCircle(32, 15, 3, TFT_GREEN);
        tft.fillTriangle(38, 14, 46, 8, 46, 22, GreyoutColor);
        tft.fillTriangle(50, 14, 58, 8, 58, 22, GreyoutColor);
        tuned = true;
      } else if (OStatus > 250 && OStatus < 500) {
        tft.fillTriangle(6, 8, 6, 22, 14, 14, GreyoutColor);
        tft.fillTriangle(18, 8, 18, 22, 26, 14, TFT_RED);
        tft.fillCircle(32, 15, 3, GreyoutColor);
        tft.fillTriangle(38, 14, 46, 8, 46, 22, GreyoutColor);
        tft.fillTriangle(50, 14, 58, 8, 58, 22, GreyoutColor);
        tuned = false;
      } else if (OStatus > 500) {
        tft.fillTriangle(6, 8, 6, 22, 14, 14, TFT_RED);
        tft.fillTriangle(18, 8, 18, 22, 26, 14, GreyoutColor);
        tft.fillCircle(32, 15, 3, GreyoutColor);
        tft.fillTriangle(38, 14, 46, 8, 46, 22, GreyoutColor);
        tft.fillTriangle(50, 14, 58, 8, 58, 22, GreyoutColor);
        tuned = false;
      } else {
        tft.fillTriangle(6, 8, 6, 22, 14, 14, GreyoutColor);
        tft.fillTriangle(18, 8, 18, 22, 26, 14, GreyoutColor);
        tft.fillCircle(32, 15, 3, GreyoutColor);
        tft.fillTriangle(38, 14, 46, 8, 46, 22, GreyoutColor);
        tft.fillTriangle(50, 14, 58, 8, 58, 22, GreyoutColor);
        tuned = false;
      }
    } else {
      if (OStatus <= -3) {
        tft.fillTriangle(6, 8, 6, 22, 14, 14, GreyoutColor);
        tft.fillTriangle(18, 8, 18, 22, 26, 14, GreyoutColor);
        tft.fillCircle(32, 15, 3, GreyoutColor);
        tft.fillTriangle(38, 14, 46, 8, 46, 22, GreyoutColor);
        tft.fillTriangle(50, 14, 58, 8, 58, 22, TFT_RED);
        tuned = false;
      } else if (OStatus < -2 && OStatus > -3) {
        tft.fillTriangle(6, 8, 6, 22, 14, 14, GreyoutColor);
        tft.fillTriangle(18, 8, 18, 22, 26, 14, GreyoutColor);
        tft.fillCircle(32, 15, 3, GreyoutColor);
        tft.fillTriangle(38, 14, 46, 8, 46, 22, TFT_RED);
        tft.fillTriangle(50, 14, 58, 8, 58, 22, GreyoutColor);
        tuned = false;
      } else if (OStatus > -2 && OStatus < 2 && SQ == false) {
        tft.fillTriangle(6, 8, 6, 22, 14, 14, GreyoutColor);
        tft.fillTriangle(18, 8, 18, 22, 26, 14, GreyoutColor);
        tft.fillCircle(32, 15, 3, TFT_GREEN);
        tft.fillTriangle(38, 14, 46, 8, 46, 22, GreyoutColor);
        tft.fillTriangle(50, 14, 58, 8, 58, 22, GreyoutColor);
        tuned = true;
      } else if (OStatus > 2 && OStatus < 3) {
        tft.fillTriangle(6, 8, 6, 22, 14, 14, GreyoutColor);
        tft.fillTriangle(18, 8, 18, 22, 26, 14, TFT_RED);
        tft.fillCircle(32, 15, 3, GreyoutColor);
        tft.fillTriangle(38, 14, 46, 8, 46, 22, GreyoutColor);
        tft.fillTriangle(50, 14, 58, 8, 58, 22, GreyoutColor);
        tuned = false;
      } else if (OStatus >= 3) {
        tft.fillTriangle(6, 8, 6, 22, 14, 14, TFT_RED);
        tft.fillTriangle(18, 8, 18, 22, 26, 14, GreyoutColor);
        tft.fillCircle(32, 15, 3, GreyoutColor);
        tft.fillTriangle(38, 14, 46, 8, 46, 22, GreyoutColor);
        tft.fillTriangle(50, 14, 58, 8, 58, 22, GreyoutColor);
        tuned = false;
      } else {
        tft.fillTriangle(6, 8, 6, 22, 14, 14, GreyoutColor);
        tft.fillTriangle(18, 8, 18, 22, 26, 14, GreyoutColor);
        tft.fillCircle(32, 15, 3, GreyoutColor);
        tft.fillTriangle(38, 14, 46, 8, 46, 22, GreyoutColor);
        tft.fillTriangle(50, 14, 58, 8, 58, 22, GreyoutColor);
        tuned = false;
      }
    }
    OStatusold = OStatus;
  }
}

void ShowBW() {
  if (millis() >= bwupdatetimer + TIMER_BW_TIMER) {
    bwupdatetimer = millis();
  } else {
    return;
  }

  if (BW != BWOld || BWreset == true) {
    tft.setFreeFont(FONT14);
    tft.setTextColor(BackgroundColor);
    tft.drawRightString(String (BWOld, DEC), 218, -4, GFXFF);
    if (BWset == 0) tft.setTextColor(SecondaryColor); else tft.setTextColor(PrimaryColor);
    tft.drawRightString(String (BW, DEC), 218, -4, GFXFF);
    BWOld = BW;
    BWreset = false;
    if (wifi) {
      Udp.beginPacket(remoteip, 9030);
      Udp.print("from = TEF tuner; Bandwidth = ");
      Udp.print(BW * 1000);
      Udp.endPacket();
    }
  }
}

void ShowModLevel() {
  if (showmodulation) {
    int segments;
    int color;
    int hold = 0;

    if (SQ != false) {
      MStatus = 0;
      MStatusold = 1;
    }
    segments = map(MStatus, 0, 120, 0, 94);

    if (segments > peakholdold) {
      peakholdold = segments;
      peakholdmillis = millis();
    }

    tft.fillRect(16, 139, 2 * constrain(segments, 0, 54), 8, TFT_GREEN);
    tft.fillRect(16 + 2 * 54, 139, 2 * (constrain(segments, 54, 94) - 54), 8, TFT_RED);
    tft.fillRect(16 + 2 * constrain(segments, 0, 94), 139, 2 * (94 - constrain(segments, 0, 94)), 8, GreyoutColor);

    int peakHoldPosition = 16 + 2 * constrain(peakholdold, 0, 94);
    tft.fillRect(peakHoldPosition, 139, 2, 8, (MStatus > 80) ? TFT_RED : PrimaryColor);

    if (millis() - peakholdmillis >= 1000) {
      tft.fillRect(peakHoldPosition, 139, 2, 8, GreyoutColor);
      peakholdold = segments;
      peakholdmillis = millis();
    }



    /*
        if (MStatus != MStatusold || MStatus < 10) {
          for (segments = 0; segments < 13; segments++) {
            color = TFT_GREEN;
            if (segments > 8) color = TFT_ORANGE;
            if (segments > 9) color = TFT_RED;
            if (MStatus > (segments + 1) * 10) {
              hold = segments;
              tft.fillRect(20 + segments * 14, 139, 12, 8, color);
            } else {
              if (segments != peakholdold) tft.fillRect(20 + segments * 14, 139, 12, 8, GreyoutColor);
            }
          }

          if (peakholdold < hold) peakholdold = hold;

          if (peakholdmillis > peakholdtimer + 3000) {
            peakholdtimer += 3000;
            peakholdold = hold;
          }
          peakholdmillis = millis();
          MStatusold = MStatus;
        }
    */
  }
}

void doSquelch() {
  tft.setFreeFont(FONT7);
  if (XDRGTKUSB == false && XDRGTKTCP == false) {
    Squelch = analogRead(PIN_POT) / 4 - 100;
    if (Squelch > 920) Squelch = 920;
    if (showsquelch && !advancedRDS && !afscreen) {
      if (seek == false && menu == false && Squelch != Squelchold) {
        tft.setTextColor(BackgroundColor);
        if (Squelchold == -100) {
          tft.drawCentreString(myLanguage[language][33], 224, 164, GFXFF);
        } else if (Squelchold == 920) {
          tft.drawCentreString("ST", 224, 164, GFXFF);
        } else {
          tft.drawCentreString(String(Squelchold / 10), 224, 164, GFXFF);
        }
        tft.setTextColor(ActiveColor);
        if (Squelch == -100) {
          tft.drawCentreString(myLanguage[language][33], 224, 164, GFXFF);
        } else if (Squelch == 920) {
          tft.drawCentreString("ST", 224, 164, GFXFF);
        } else {
          tft.drawCentreString(String(Squelch / 10), 224, 164, GFXFF);
        }
      }
      Squelchold = Squelch;
    }
  }
  if (seek == false && (XDRGTKUSB == true || XDRGTKTCP == true)) {
    if (XDRMute == false) {
      if (Squelch != -1) {
        if (Squelch < SStatus || Squelch == -100 || Squelch == 0) {
          radio.setUnMute();
          SQ = false;
        } else {
          radio.setMute();
          SQ = true;
        }
      } else {
        if (Stereostatus == true) {
          radio.setUnMute();
          SQ = false;
        } else {
          radio.setMute();
          SQ = true;
        }
      }
      if (screenmute == false && showsquelch == true && !advancedRDS && !afscreen) {
        if (Squelch != Squelchold) {
          tft.setTextColor(BackgroundColor);
          if (Squelchold == -1) {
            tft.drawCentreString("ST", 224, 164, GFXFF);
          } else if (Squelchold == 0) {
            tft.drawCentreString(myLanguage[language][33], 224, 164, GFXFF);
          } else {
            tft.drawCentreString(String(Squelchold / 10), 224, 164, GFXFF);
          }
          tft.setTextColor(ActiveColor);
          if (Squelch == -1) {
            tft.drawCentreString("ST", 224, 164, GFXFF);
          } else if (Squelch == 0) {
            tft.drawCentreString(myLanguage[language][33], 224, 164, GFXFF);
          } else {
            tft.drawCentreString(String(Squelch / 10), 224, 164, GFXFF);
          }
          Squelchold = Squelch;
        }
      }
    }
  } else {
    if (seek == false && Squelch != 920) {
      if (Squelch < SStatus || Squelch == -100 || Squelch == 0) {
        radio.setUnMute();
        SQ = false;
      } else {
        radio.setMute();
        SQ = true;
      }
    } else {
      if (seek == false && Stereostatus == true) {
        radio.setUnMute();
        SQ = false;
      } else {
        radio.setMute();
        SQ = true;
      }
    }
  }
}

void updateBW() {
  tft.setFreeFont(FONT7);
  if (BWset == 0) {
    if (screenmute == false && advancedRDS == false && afscreen == false) {
      tft.drawRoundRect(249, 35, 68, 20, 5, ActiveColor);
      tft.setTextColor(ActiveColor);
    }
    radio.setFMABandw();
  } else {
    if (screenmute == false && advancedRDS == false && afscreen == false) {
      tft.drawRoundRect(249, 35, 68, 20, 5, GreyoutColor);
      tft.setTextColor(GreyoutColor);
    }
  }
  if (screenmute == false && advancedRDS == false && afscreen == false) tft.drawCentreString("AUTO BW", 282, 33, GFXFF);
}

void updateiMS() {
  tft.setFreeFont(FONT7);
  if (band == BAND_FM) {
    if (iMSset == 0) {
      if (screenmute == false) {
        tft.drawRoundRect(249, 56, 30, 20, 5, ActiveColor);
        tft.setTextColor(ActiveColor);
      }
      radio.setiMS(1);
    } else {
      if (screenmute == false) {
        tft.drawRoundRect(249, 56, 30, 20, 5, GreyoutColor);
        tft.setTextColor(GreyoutColor);
      }
      radio.setiMS(0);
    }
  } else {
    tft.setTextColor(GreyoutColor);
  }
  tft.drawCentreString("iMS", 264, 54, GFXFF);
}

void updateEQ() {
  tft.setFreeFont(FONT7);
  if (band == BAND_FM) {
    if (EQset == 0) {
      if (screenmute == false) {
        tft.drawRoundRect(287, 56, 30, 20, 5, ActiveColor);
        tft.setTextColor(ActiveColor);
      }
      radio.setEQ(1);
    } else {
      if (screenmute == false) {
        tft.drawRoundRect(287, 56, 30, 20, 5, GreyoutColor);
        tft.setTextColor(GreyoutColor);
      }
      radio.setEQ(0);
    }
  } else {
    tft.setTextColor(GreyoutColor);
  }
  tft.drawCentreString("EQ", 302, 54, GFXFF);
}

void updateSWMIBand() {
  switch (SWMIBandPos) {
    case SW_MI_BAND_11M:
    case SW_MI_BAND_13M:
    case SW_MI_BAND_15M:
    case SW_MI_BAND_16M:
    case SW_MI_BAND_19M:
    case SW_MI_BAND_22M:
    case SW_MI_BAND_25M:
    case SW_MI_BAND_31M:
    case SW_MI_BAND_41M:
    case SW_MI_BAND_49M:
    case SW_MI_BAND_60M:
    case SW_MI_BAND_75M:
    case SW_MI_BAND_90M:
    case SW_MI_BAND_120M:
    case SW_MI_BAND_160M:
      tft.setTextColor(BackgroundColor);
      tft.drawString(SWMIBandstringold, 50, 45, GFXFF);

      tft.setTextColor(PrimaryColor, BackgroundColor);
      tft.drawString(SWMIBandstring, 50, 45, GFXFF);
      break;
    case SW_MI_BAND_GAP:

      tft.setTextColor(BackgroundColor);
      tft.drawString(SWMIBandstringold, 50, 45, GFXFF);

      break;
  }
}

void doBW() {
  if (band == BAND_FM) {
    if (BWset > 16) BWset = 0;

    switch (BWset) {
      case 1:
        radio.setFMBandw(56);
        break;

      case 2:
        radio.setFMBandw(64);
        break;

      case 3:
        radio.setFMBandw(72);
        break;

      case 4:
        radio.setFMBandw(84);
        break;

      case 5:
        radio.setFMBandw(97);
        break;

      case 6:
        radio.setFMBandw(114);
        break;

      case 7:
        radio.setFMBandw(133);
        break;

      case 8:
        radio.setFMBandw(151);
        break;

      case 9:
        radio.setFMBandw(168);
        break;

      case 10:
        radio.setFMBandw(184);
        break;

      case 11:
        radio.setFMBandw(200);
        break;

      case 12:
        radio.setFMBandw(217);
        break;

      case 13:
        radio.setFMBandw(236);
        break;

      case 14:
        radio.setFMBandw(254);
        break;

      case 15:
        radio.setFMBandw(287);
        break;

      case 16:
        radio.setFMBandw(311);
        break;
    }
  } else {
    if (BWset > 4) BWset = 1;

    switch (BWset) {
      case 1:
        radio.setAMBandw(3);
        break;

      case 2:
        radio.setAMBandw(4);
        break;

      case 3:
        radio.setAMBandw(6);
        break;

      case 4:
        radio.setAMBandw(8);
        break;
    }
  }
  updateBW();
  BWreset = true;
}

void doTuneMode() {
  switch (tunemode) {
    case TUNE_MAN:
      if (band == BAND_FM) {
        tunemode = TUNE_AUTO;
        if (stepsize != 0) {
          stepsize = 0;
          RoundStep();
          ShowStepSize();
        }
      } else if (band == BAND_SW && showSWMIBand) {
        tunemode = TUNE_MI_BAND;
      } else {
        tunemode = TUNE_MEM;
      }
      break;
    case TUNE_MI_BAND:
    case TUNE_AUTO:
      tunemode = TUNE_MEM;
      break;

    case TUNE_MEM:
      tunemode = TUNE_MAN;
      break;
  }
  ShowTuneMode();
  ShowMemoryPos();
  ShowFreq(0);
  EEPROM.writeByte(EE_BYTE_TUNEMODE, tunemode);
  EEPROM.commit();
}

void ShowTuneMode() {
  tft.setFreeFont(FONT7);
  switch (tunemode) {
    case TUNE_MAN:
      if (band == BAND_SW) {
        tft.drawRoundRect(3, 57, 40, 20, 5, GreyoutColor);
        tft.setTextColor(GreyoutColor);
        tft.drawCentreString("BAND", 22, 55, GFXFF);
      } else {
        tft.drawRoundRect(3, 57, 40, 20, 5, GreyoutColor);
        tft.setTextColor(GreyoutColor);
        tft.drawCentreString("AUTO", 22, 55, GFXFF);
      }

      tft.drawRoundRect(3, 35, 40, 20, 5, ActiveColor);
      tft.setTextColor(ActiveColor);
      tft.drawCentreString("MAN", 22, 33, GFXFF);

      tft.drawRoundRect(3, 79, 40, 20, 5, GreyoutColor);
      tft.setTextColor(GreyoutColor);
      tft.drawCentreString("MEM", 22, 77, GFXFF);
      break;

    case TUNE_AUTO:
      tft.drawRoundRect(3, 57, 40, 20, 5, ActiveColor);
      tft.setTextColor(ActiveColor);
      tft.drawCentreString("AUTO", 22, 55, GFXFF);

      tft.drawRoundRect(3, 35, 40, 20, 5, GreyoutColor);
      tft.setTextColor(GreyoutColor);
      tft.drawCentreString("MAN", 22, 33, GFXFF);

      tft.drawRoundRect(3, 79, 40, 20, 5, GreyoutColor);
      tft.setTextColor(GreyoutColor);
      tft.drawCentreString("MEM", 22, 77, GFXFF);
      break;

    case TUNE_MEM:
      if (band == BAND_SW) {
        tft.drawRoundRect(3, 57, 40, 20, 5, GreyoutColor);
        tft.setTextColor(GreyoutColor);
        tft.drawCentreString("BAND", 22, 55, GFXFF);
      } else {
        tft.drawRoundRect(3, 57, 40, 20, 5, GreyoutColor);
        tft.setTextColor(GreyoutColor);
        tft.drawCentreString("AUTO", 22, 55, GFXFF);
      }

      tft.drawRoundRect(3, 35, 40, 20, 5, GreyoutColor);
      tft.setTextColor(GreyoutColor);
      tft.drawCentreString("MAN", 22, 33, GFXFF);

      if (memorystore == true) {
        tft.drawRoundRect(3, 79, 40, 20, 5, TFT_RED);
        tft.setTextColor(TFT_RED);
      } else {
        tft.drawRoundRect(3, 79, 40, 20, 5, ActiveColor);
        tft.setTextColor(ActiveColor);
      }
      tft.drawCentreString("MEM", 22, 77, GFXFF);
      break;
    case TUNE_MI_BAND:
      tft.drawRoundRect(3, 57, 40, 20, 5, ActiveColor);
      tft.setTextColor(ActiveColor);
      tft.drawCentreString("BAND", 22, 55, GFXFF);

      tft.drawRoundRect(3, 35, 40, 20, 5, GreyoutColor);
      tft.setTextColor(GreyoutColor);
      tft.drawCentreString("MAN", 22, 33, GFXFF);

      tft.drawRoundRect(3, 79, 40, 20, 5, GreyoutColor);
      tft.setTextColor(GreyoutColor);
      tft.drawCentreString("MEM", 22, 77, GFXFF);
      break;
  }
}

void ShowRSSI() {
  if (wifi) rssi = WiFi.RSSI(); else rssi = 0;
  if (rssiold != rssi) {
    rssiold = rssi;
    if (rssi == 0) {
      tft.drawBitmap(272, 4, WiFi4, 25, 25, GreyoutColor);
    } else if (rssi > -50 && rssi < 0) {
      tft.drawBitmap(272, 4, WiFi4, 25, 25, PrimaryColor);
    } else if (rssi > -60) {
      tft.drawBitmap(272, 4, WiFi4, 25, 25, GreyoutColor);
      tft.drawBitmap(272, 4, WiFi3, 25, 25, PrimaryColor);
    } else if (rssi > -70) {
      tft.drawBitmap(272, 4, WiFi4, 25, 25, GreyoutColor);
      tft.drawBitmap(272, 4, WiFi2, 25, 25, PrimaryColor);
    } else if (rssi < -70) {
      tft.drawBitmap(272, 4, WiFi4, 25, 25, GreyoutColor);
      tft.drawBitmap(272, 4, WiFi1, 25, 25, PrimaryColor);
    }
  }
}

void ShowBattery() {
  if (millis() >= batupdatetimer + TIMER_BAT_TIMER) {
    batupdatetimer = millis();
  } else {
    return;
  }

  battery = map(constrain(analogRead(BATTERY_PIN), BAT_LEVEL_EMPTY, BAT_LEVEL_FULL), BAT_LEVEL_EMPTY, BAT_LEVEL_FULL, 0, BAT_LEVEL_STAGE);
  if (batteryold != battery) {
    if (batterydetect) {
      if (battery == 0) {
        tft.drawRect(300, 8, 12, 20, TFT_RED);
        tft.fillRect(303, 4, 6, 4, TFT_RED);
        tft.fillRect(302, 10, 8, 16, BackgroundColor);
        tft.fillRect(302, 26 - (battery * 4), 8, battery * 4, TFT_GREEN);
      } else {
        tft.drawRect(300, 8, 12, 20, ActiveColor);
        tft.fillRect(303, 4, 6, 4, ActiveColor);
        tft.fillRect(302, 10, 8, 16, BackgroundColor);
        tft.fillRect(302, 26 - (battery * 4), 8, battery * 4, TFT_GREEN);
      }
    } else {
      tft.drawRect(300, 8, 12, 20, GreyoutColor);
      tft.fillRect(303, 4, 6, 4, GreyoutColor);
      tft.fillRect(302, 10, 8, 16, BackgroundColor);
    }
    batteryold = battery;
  }
}

void Communication() {
  if (menu == false) {
    if (wifi) {
      int packetSize = Udp.parsePacket();
      if (packetSize) {
        char packetBuffer[packetSize];
        Udp.read(packetBuffer, packetSize);
        Udp.endPacket();
        String packet = String(packetBuffer);
        if (packetBuffer == "from = StationList; freq = ?; bandwidth = ? ") {
          ShowFreq(0);
          Udp.beginPacket(remoteip, 9030);
          Udp.print("from = TEF tuner; Bandwidth = ");
          Udp.print(BW * 1000);
          Udp.endPacket();
        } else {
          int symPos = packet.indexOf("freq = ");
          String stlfreq = packet.substring(symPos + 5, packetSize);
          if ((stlfreq.toInt()) / 10000 > 6500 && (stlfreq.toInt()) / 10000 < 10800) {
            if (band != BAND_FM) {
              band = BAND_FM;
              SelectBand();
            }
            frequency = (stlfreq.toInt()) / 10000;
            radio.SetFreq(frequency);
          }

          // To Do: AM
          //          if ((stlfreq.toInt()) / 1000 > 144 && (stlfreq.toInt()) / 1000 < 27000) {
          //            if (band != 5) {
          //              band = 5;
          //            SelectBand();
          //            }
          //            frequency5 = (stlfreq.toInt()) / 1000;
          //            radio.SetFreqAM(frequency5);
          //          }
          radio.clearRDS(fullsearchrds);
          ShowFreq(0);
          store = true;
        }
      }
    }

    if (Server.hasClient())
    {
      if (RemoteClient.connected())
      {
        Server.available().stop();
      } else {
        wificonnected = true;
        RemoteClient = Server.available();
        passwordcrypt();
        RemoteClient.print(saltkey + "\n");
      }
    } else {
      if (Server.hasClient()) Server.available().stop();
    }

    if (wificonnected == true && !RemoteClient.connected()) {
      wificonnected = false;
      RDSSPYTCP = false;
      XDRGTKTCP = false;
    }


    if (XDRGTKTCP == false && wificonnected == true && RemoteClient.available()) {
      String data_str = RemoteClient.readStringUntil('\n');
      int data = data_str.toInt();
      if (data_str.length() > 30 && data_str.equals(cryptedpassword))
      {
        radio.setFMABandw();
        if (band != BAND_FM) {
          band = BAND_FM;
          SelectBand();
        }
        XDRGTKTCP = true;
        RemoteClient.print("o1, 0\n");
        store = true;
      } else if (RDSSPYTCP == false && XDRGTKTCP == false && data_str.length() < 5 && data_str == ("*R ? F"))
      {
        RDSSPYTCP = true;
      } else if (RDSSPYTCP == true) {
        int symPos = data_str.indexOf("*F");
        if (symPos >= 5) {
          String freq = data_str.substring(0, symPos);
          freq = freq.substring(0, freq.length() - 1);
          frequency = freq.toInt();
          radio.SetFreq(frequency);
          radio.clearRDS(fullsearchrds);
          if (band != BAND_FM) {
            band = BAND_FM;
            SelectBand();
          }
          ShowFreq(0);
          store = true;
        }
      } else {
        RemoteClient.print("a0\n");
      }
    }

    if (XDRGTKUSB == false && Serial.available())
    {
      String data_str = Serial.readStringUntil('\n');
      int data = data_str.toInt();
      if (data_str.length() > 1 && data_str == ("*D * R ? F")) RDSSPYUSB = true;
      int symPos = data_str.indexOf("*F");
      if (symPos >= 5) {
        String freq = data_str.substring(0, symPos);
        freq = freq.substring(0, freq.length() - 1);
        frequency = freq.toInt();
        radio.SetFreq(frequency);
        if (band != BAND_FM) {
          band = BAND_FM;
          BWreset = true;
          BWset = 0;
          radio.power(0);
          delay(50);
          radio.SetFreq(frequency);
          radio.clearRDS(fullsearchrds);
          freqold = frequency_AM;
          doBW;
          radio.getStatus(SStatus, USN, WAM, OStatus, BW, MStatus, SNR);
          if (screenmute == false) radio.clearRDS(fullsearchrds); BuildDisplay();
        }
        ShowFreq(0);
        store = true;
      }
      if (data_str.charAt(0) == 'x') {
        radio.setFMABandw();
        if (band != BAND_FM) {
          band = BAND_FM;
          SelectBand();
        }
        Serial.print("OK\nT" + String(frequency * 10) + "\n");
        XDRGTKUSB = true;
        if (menu == true) ModeButtonPress();
        if (Squelch != Squelchold) {
          if (screenmute == false) {
            tft.setFreeFont(FONT7);
            tft.setTextColor(BackgroundColor);
            if (Squelchold == -100) tft.drawCentreString(myLanguage[language][33], 224, 164, GFXFF); else if (Squelchold > 920) tft.drawCentreString("ST", 224, 164, GFXFF); else tft.drawCentreString(String(Squelchold / 10), 224, 164, GFXFF);
          }
        }
      }
    }
    if (XDRGTKUSB || XDRGTKTCP) XDRGTKRoutine();
  }
}


void DataPrint(String string) {
  if (XDRGTKUSB) Serial.print(string);
  if (XDRGTKTCP) RemoteClient.print(string);
}

void XDRGTKRoutine() {
  if (XDRGTKUSB) {
    if (Serial.available())
    {
      buff[buff_pos] = Serial.read();
      if (buff[buff_pos] != '\n' && buff_pos != 16 - 1)
      {
        buff_pos++;
      } else {
        buff[buff_pos] = 0;
        buff_pos = 0;
        XDRGTKdata = true;
      }
    }
  }

  if (XDRGTKTCP) {
    if (RemoteClient.available() > 0) {
      buff[buff_pos] = RemoteClient.read();
      if (buff[buff_pos] != '\n' && buff_pos != 16 - 1)
      {
        buff_pos++;
      } else {
        buff[buff_pos] = 0;
        buff_pos = 0;
        XDRGTKdata = true;
      }
    }
  }

  if (XDRGTKdata) {
    switch (buff[0])
    {
      case 'A':
        int AGC;
        AGC = atol(buff + 1);
        DataPrint("A" + String(AGC) + "\n");
        radio.setAGC(AGC);
        break;

      case 'C':
        byte scanmethod;
        scanmethod = atol(buff + 1);
        if (scanmethod == 1) {
          DataPrint("C1\n");
          direction = false;
          Seek(direction);
          ShowFreq(0);
        }
        if (scanmethod == 2) {
          DataPrint("C2\n");
          direction = true;
          Seek(direction);
          ShowFreq(0);
        }
        DataPrint("C0\n");
        break;

      case 'N':
        doStereoToggle();
        break;

      case 'D':
        DeEmphasis = atol(buff + 1);
        DataPrint("D" + String(DeEmphasis) + "\n");
        radio.setDeemphasis(DeEmphasis);
        break;

      case 'F':
        XDRBWset = atol(buff + 1);
        DataPrint("F" + String(XDRBWset) + "\n");
        if (XDRBWset < 0) {
          XDRBWsetold = XDRBWset;
          BWset = 0;
        } else if (XDRBWset < 16) {
          BWset = XDRBWset + 1;
          XDRBWsetold = XDRBWset;
        } else {
          XDRBWset = XDRBWsetold;
        }
        doBW();
        break;

      case 'G':
        byte offsetg;
        offsetg = atol(buff + 1);
        if (offsetg == 0) {
          MuteScreen(0);
          LowLevelSet = EEPROM.readInt(EE_INT_LOWLEVELSET);
          softmuteam = EEPROM.readByte(EE_BYTE_SOFTMUTEAM);
          softmutefm = EEPROM.readByte(EE_BYTE_SOFTMUTEFM);
          radio.setSoftmuteFM(softmutefm);
          radio.setSoftmuteAM(softmuteam);
          DataPrint("G00\n");
        }
        if (offsetg == 10) {
          MuteScreen(1);
          LowLevelSet = EEPROM.readInt(EE_INT_LOWLEVELSET);
          softmuteam = EEPROM.readByte(EE_BYTE_SOFTMUTEAM);
          softmutefm = EEPROM.readByte(EE_BYTE_SOFTMUTEFM);
          radio.setSoftmuteFM(softmutefm);
          radio.setSoftmuteAM(softmuteam);
          DataPrint("G10\n");
        }
        if (offsetg == 1) {
          MuteScreen(0);
          radio.setSoftmuteFM(1);
          radio.setSoftmuteAM(1);
          DataPrint("G01\n");
        }
        if (offsetg == 11) {
          MuteScreen(1);
          radio.setSoftmuteFM(1);
          radio.setSoftmuteAM(1);
          DataPrint("G11\n");
        }
        break;

      case 'M':
        byte XDRband;
        XDRband = atol(buff + 1);
        if (XDRband == 0) DataPrint("M0\n"); else DataPrint("M1\n");
        if (XDRband == 1) {
          if (frequency_AM >= LWLowEdgeSet && frequency_AM <= LWHighEdgeSet) {
            if (band != BAND_LW) {
              band = BAND_LW;
              SelectBand();
            }
          }
          if (frequency_AM >= MWLowEdgeSet && frequency_AM <= MWHighEdgeSet) {
            if (band != BAND_MW) {
              band = BAND_MW;
              SelectBand();
            }
          }
          if (frequency_AM >= SWLowEdgeSet && frequency_AM <= SWHighEdgeSet) {
            if (band != BAND_SW) {
              band = BAND_SW;
              SelectBand();
            }
          }
          radio.SetFreqAM(frequency_AM);
          DataPrint("M1\n");
          DataPrint("T" + String(frequency_AM) + "\n");
        } else {
          if (band != BAND_FM) {
            band = BAND_FM;
            SelectBand();
          }
          DataPrint("M0\n");
          DataPrint("T" + String(frequency * 10) + "\n");
          radio.SetFreq(frequency);
          radio.clearRDS(fullsearchrds);
          RDSstatus = 0;
        }
        store == true;
        break;

      case 'T':
        unsigned int freqtemp;
        freqtemp = atoi(buff + 1);
        if (seek == true) seek = false;
        if (freqtemp >= LWLowEdgeSet && freqtemp <= LWHighEdgeSet) {
          frequency_AM = freqtemp;
          if (band != BAND_LW) {
            band = BAND_LW;
            SelectBand();
          }
          radio.SetFreqAM(frequency_AM);
          DataPrint("M1\n");
        }
        if (freqtemp >= MWLowEdgeSet && freqtemp <= MWHighEdgeSet) {
          frequency_AM = freqtemp;
          if (band != BAND_MW) {
            band = BAND_MW;
            SelectBand();
          }
          radio.SetFreqAM(frequency_AM);
          DataPrint("M1\n");
        }
        if (freqtemp >= SWLowEdgeSet && freqtemp <= SWHighEdgeSet) {
          frequency_AM = freqtemp;
          if (band != BAND_SW) {
            band = BAND_SW;
            SelectBand();
          }
          radio.SetFreqAM(frequency_AM);
          DataPrint("M1\n");
        }
        if (freqtemp >= FREQ_FM_START && freqtemp <= FREQ_FM_END) {
          frequency = freqtemp / 10;
          if (band != BAND_FM) {
            band = BAND_FM;
            SelectBand();
          }
          radio.SetFreq(frequency);
          DataPrint("M0\n");
        }
        if (band == BAND_FM) DataPrint("T" + String(frequency * 10) + "\n"); else DataPrint("T" + String(frequency_AM) + "\n");
        ShowFreq(0);
        radio.clearRDS(fullsearchrds);
        RDSstatus = 0;
        store == true;
        break;

      case 'Q':
        Squelch = atoi(buff + 1);
        if (Squelch == -1) {
          DataPrint("Q - 1\n");
        } else {
          Squelch *= 10;
          DataPrint("Q\n");
          DataPrint(String(Squelch / 10));
        }
        break;

      case 'S':
        if (buff[1] == 'a') {
          scanner_start = (atol(buff + 2) + 5) / 10;
        } else if (buff[1] == 'b') {
          scanner_end = (atol(buff + 2) + 5) / 10;
        } else if (buff[1] == 'c') {
          scanner_step = (atol(buff + 2) + 5) / 10;
        } else if (buff[1] == 'f') {
          scanner_filter = atol(buff + 2);
        } else if (scanner_start > 0 && scanner_end > 0 && scanner_step > 0 && scanner_filter >= 0) {
          frequencyold = frequency;
          radio.SetFreq(scanner_start);
          DataPrint("U");
          if (scanner_filter < 0) {
            BWset = 0;
          } else if (scanner_filter == 0) {
            BWset = 1;
          } else if (scanner_filter == 26) {
            BWset = 2;
          } else if (scanner_filter == 1) {
            BWset = 3;
          } else if (scanner_filter == 28) {
            BWset = 4;
          } else if (scanner_filter == 29) {
            BWset = 5;
          } else if (scanner_filter == 3) {
            BWset = 6;
          } else if (scanner_filter == 4) {
            BWset = 7;
          } else if (scanner_filter == 5) {
            BWset = 8;
          } else if (scanner_filter == 7) {
            BWset = 9;
          } else if (scanner_filter == 8) {
            BWset = 10;
          } else if (scanner_filter == 9) {
            BWset = 11;
          } else if (scanner_filter == 10) {
            BWset = 12;
          } else if (scanner_filter == 11) {
            BWset = 13;
          } else if (scanner_filter == 12) {
            BWset = 14;
          } else if (scanner_filter == 13) {
            BWset = 15;
          } else if (scanner_filter == 15) {
            BWset = 16;
          }
          doBW();
          if (screenmute == false) {
            ShowFreq(1);
            tft.setTextColor(ActiveColor, BackgroundColor);
            tft.setCursor (90, 60);
            tft.setFreeFont(FONT14);
            tft.drawCentreString(myLanguage[language][34], 140, 60, GFXFF);
          }
          frequencyold = frequency;
          for (freq_scan = scanner_start; freq_scan <= scanner_end; freq_scan += scanner_step) {
            radio.SetFreq(freq_scan);
            DataPrint(String(freq_scan * 10, DEC));
            DataPrint(" = ");
            delay(10);
            if (band == BAND_FM) radio.getStatus(SStatus, USN, WAM, OStatus, BW, MStatus, SNR); else  radio.getStatusAM(SStatus, USN, WAM, OStatus, BW, MStatus, SNR);
            DataPrint(String((SStatus / 10) + 10, DEC));
            DataPrint(", ");
          }
          DataPrint("\n");
          if (screenmute == false) {
            tft.setTextColor(BackgroundColor);
            tft.drawCentreString(myLanguage[language][34], 140, 60, GFXFF);
          }
          radio.SetFreq(frequencyold);
          ShowFreq(0);
          radio.setFMABandw();
          BWset = 0;
        }
        break;

      case 'Y':
        VolSet = atoi(buff + 1);
        if (VolSet == 0) {
          radio.setMute();
          XDRMute = true;
          SQ = true;
        } else {
          radio.setUnMute();
          radio.setVolume((VolSet - 40) / 10);
          XDRMute = false;
        }
        DataPrint("Y" + String(VolSet) + "\n");
        VolSet /= 10;
        break;

      case 'x':
        DataPrint("OK\nT" + String(frequency * 10) + "\n");
        break;

      case 'X':
        XDRGTKTCP = false;
        XDRGTKUSB = false;
        store = true;
        XDRMute = false;
        radio.setUnMute();
        VolSet = EEPROM.readInt(EE_INT_VOLSET);
        LowLevelSet = EEPROM.readInt(EE_INT_LOWLEVELSET);
        softmuteam = EEPROM.readByte(EE_BYTE_SOFTMUTEAM);
        softmutefm = EEPROM.readByte(EE_BYTE_SOFTMUTEFM);
        radio.setVolume(VolSet);
        radio.setSoftmuteFM(softmutefm);
        radio.setSoftmuteAM(softmuteam);
        if (screenmute) MuteScreen(0);
        break;

      case 'Z':
        byte iMSEQX;
        iMSEQX = atol(buff + 1);
        switch (iMSEQX) {
          case 0:
            iMSset = 1;
            EQset = 1;
            iMSEQ = 2;
            break;

          case 1:
            iMSset = 0;
            EQset = 1;
            iMSEQ = 3;
            break;

          case 2:
            iMSset = 1;
            EQset = 0;
            iMSEQ = 4;
            break;

          case 3:
            iMSset = 0;
            EQset = 0;
            iMSEQ = 1;
            break;
        }
        updateiMS();
        updateEQ();
        DataPrint("Z" + String(iMSEQX) + "\n");
        break;
    }
    XDRGTKdata = false;
  }

  if (band != BAND_FM) {
    DataPrint("Sm");
  } else {
    if (StereoToggle == false) {
      DataPrint("SS");
    } else if (Stereostatus == true) {
      DataPrint("Ss");
    } else {
      DataPrint("Sm");
    }
  }
  DataPrint(String(((SStatus * 100) + 10875) / 1000) + "." + String(((SStatus * 100) + 10875) / 100 % 10) + ", " + String(WAM / 10) + ", " + String(SNR) + "\n");
}

void TuneUp() {
  aftest = true;
  aftimer = millis();
  unsigned int temp;
  if (stepsize == 0) {
    if (band != BAND_FM) {
      if (frequency_AM < MWHighEdgeSet) {
        if (region == 0) {
          temp = FREQ_MW_STEP_9K;
          frequency_AM = (frequency_AM / FREQ_MW_STEP_9K) * FREQ_MW_STEP_9K;
        } else if (region == 1) {
          temp = FREQ_MW_STEP_10K;
          frequency_AM = (frequency_AM / FREQ_MW_STEP_10K) * FREQ_MW_STEP_10K;
        }
      } else {
        temp = FREQ_SW_STEP_5K;
        frequency_AM = (frequency_AM / FREQ_SW_STEP_5K) * FREQ_SW_STEP_5K;
      }
    } else {
      if (frequency >= (FREQ_FM_OIRT_START) && frequency <= (FREQ_FM_OIRT_END - FREQ_FM_STEP_30K)) {
        if (specialstepOIRT) {
          temp = FREQ_FM_STEP_30K;
        } else {
          if (fmdefaultstepsize == 1) temp = FREQ_FM_STEP_100K; else temp = FREQ_FM_STEP_50K;
        }
      } else {
        if (fmdefaultstepsize == 1) temp = FREQ_FM_STEP_100K; else temp = FREQ_FM_STEP_50K;
      }
    }
  }
  if (stepsize == 1) temp = 1;
  if (stepsize == 2) temp = 10;
  if (stepsize == 3) temp = 100;
  if (stepsize == 4) temp = 1000;

  if (band == BAND_FM) {
    frequency += temp;
    if (specialstepOIRT) {
      if (frequency >= (HighEdgeOIRTSet == 0 ? ((HighEdgeSet * 10) + 1) : (HighEdgeOIRTSet + 1))) {
        frequency = (LowEdgeOIRTSet == 0 ? (LowEdgeSet * 10) : LowEdgeOIRTSet);
        if (edgebeep) EdgeBeeper();
      }
    } else {
      if (frequency >= (HighEdgeSet * 10) + 1) {
        frequency = LowEdgeSet * 10;
        if (edgebeep) EdgeBeeper();
      }
    }
    radio.SetFreq(frequency);
  }

  if (band == BAND_LW) {
    frequency_AM += temp;
    if (frequency_AM > LWHighEdgeSet) {
      frequency_AM = LWLowEdgeSet;
      if (edgebeep) EdgeBeeper();
    }
    radio.SetFreqAM(frequency_AM);
    frequency_LW = frequency_AM;
  } else if (band == BAND_MW) {
    frequency_AM += temp;
    if (frequency_AM > MWHighEdgeSet) {
      frequency_AM = MWLowEdgeSet;
      if (edgebeep) EdgeBeeper();
    }
    radio.SetFreqAM(frequency_AM);
    frequency_MW = frequency_AM;
  } else if (band == BAND_SW) {
    frequency_AM += temp;
    if (frequency_AM > SWHighEdgeSet) {
      frequency_AM = SWLowEdgeSet;
      if (edgebeep) EdgeBeeper();
    }
    radio.SetFreqAM(frequency_AM);
    frequency_SW = frequency_AM;
  }
  radio.clearRDS(fullsearchrds);
  if (RDSSPYUSB == true) Serial.print("G : \r\nRESET------ -\r\n\r\n");
  if (RDSSPYTCP == true) RemoteClient.print("G : \r\nRESET------ -\r\n\r\n");
}

void TuneDown() {
  aftest = true;
  aftimer = millis();
  unsigned int temp;
  if (stepsize == 0) {
    if (band != BAND_FM) {
      if (frequency_AM <= MWHighEdgeSet) {
        if (frequency_AM == 2000) { // Fix Me :take care of 9K/10K Step
          frequency_AM = 1998;
          temp = 0;
        } else {
          temp = region == 0 ? FREQ_MW_STEP_9K : FREQ_MW_STEP_10K;
          frequency_AM = (frequency_AM / temp) * temp;
        }
      } else {
        temp = FREQ_SW_STEP_5K;
        frequency_AM = (frequency_AM / temp) * temp;
      }
    } else {
      if (frequency >= (FREQ_FM_OIRT_START + FREQ_FM_STEP_30K) && frequency <= (FREQ_FM_OIRT_END)) {
        if (specialstepOIRT) {
          temp = FREQ_FM_STEP_30K;
        } else {
          if (fmdefaultstepsize == 1) temp = FREQ_FM_STEP_100K; else temp = FREQ_FM_STEP_50K;
        }
      } else {
        if (fmdefaultstepsize == 1) temp = FREQ_FM_STEP_100K; else temp = FREQ_FM_STEP_50K;
      }
    }
  }
  if (stepsize == 1) temp = 1;
  if (stepsize == 2) temp = 10;
  if (stepsize == 3) temp = 100;
  if (stepsize == 4) temp = 1000;

  if (band == BAND_FM) {
    frequency -= temp;
    if (specialstepOIRT) {
      if (frequency < (LowEdgeOIRTSet == 0 ? (LowEdgeSet * 10) : LowEdgeOIRTSet) ) {
        frequency = (HighEdgeOIRTSet == 0 ? (HighEdgeSet * 10) : HighEdgeOIRTSet);
        if (edgebeep) EdgeBeeper();
      }
    } else {
      if (frequency < LowEdgeSet * 10) {
        frequency = HighEdgeSet * 10;
        if (edgebeep) EdgeBeeper();
      }
    }
    radio.SetFreq(frequency);
  }

  if (band == BAND_LW) {
    frequency_AM -= temp;
    if (frequency_AM < LWLowEdgeSet) {
      frequency_AM = LWHighEdgeSet;
      if (edgebeep) EdgeBeeper();
    }
    radio.SetFreqAM(frequency_AM);
    frequency_LW = frequency_AM;
  } else if (band == BAND_MW) {
    frequency_AM -= temp;
    if (frequency_AM < MWLowEdgeSet) {
      frequency_AM = MWHighEdgeSet;
      if (edgebeep) EdgeBeeper();
    }
    radio.SetFreqAM(frequency_AM);
    frequency_MW = frequency_AM;
  } else if (band == BAND_SW) {
    frequency_AM -= temp;
    if (frequency_AM < SWLowEdgeSet) {
      frequency_AM = SWHighEdgeSet;
      if (edgebeep) EdgeBeeper();
    }
    radio.SetFreqAM(frequency_AM);
    frequency_SW = frequency_AM;
  }
  radio.clearRDS(fullsearchrds);
  if (RDSSPYUSB == true) Serial.print("G : \r\nRESET------ -\r\n\r\n");
  if (RDSSPYTCP == true) RemoteClient.print("G : \r\nRESET------ -\r\n\r\n");
}

void EdgeBeeper() {
  bool x = radio.mute;
  radio.tone(50, -5, 2000);
  if (x) radio.setMute(); else radio.setUnMute();
}

void Seek(bool mode) {
  if (band == BAND_FM) {
    radio.setMute();
    if (mode == false) TuneDown(); else TuneUp();
    delay(50);
    ShowFreq(0);
      if (XDRGTKUSB == true || XDRGTKTCP == true) if (band == BAND_FM) DataPrint("T" + String(frequency * 10) + "\n"); else DataPrint("T" + String(frequency_AM) + "\n");
    radio.getStatus(SStatus, USN, WAM, OStatus, BW, MStatus, SNR);

    if ((USN < 200) && (WAM < 230) && (OStatus < 80 && OStatus > -80) && (Squelch < SStatus || Squelch == 920)) {
      seek = false;
      radio.setUnMute();
      store = true;
    } else {
      seek = true;
      if (RDSSPYUSB == true) Serial.print("G : \r\nRESET------ -\r\n\r\n");
      if (RDSSPYTCP == true) RemoteClient.print("G : \r\nRESET------ -\r\n\r\n");
    }
  }
}

void SetTunerPatch() {
  if (TEF != 101 && TEF != 102 && TEF != 205) {
    radio.init(102);
    uint16_t device;
    uint16_t hw;
    uint16_t sw;
    radio.getIdentification(device, hw, sw);
    TEF = highByte(hw) * 100 + highByte(sw);
    tft.fillScreen(BackgroundColor);
    tft.setTextColor(ActiveColor);
    tft.setFreeFont(FONT14);
    analogWrite(CONTRASTPIN, ContrastSet * 2 + 27);

    if (TEF == 0) tft.drawCentreString(myLanguage[language][35], 150, 70, GFXFF); else tft.drawCentreString(String(myLanguage[language][36]) + String(TEF), 150, 70, GFXFF);
    tft.drawCentreString(myLanguage[language][37], 150, 100, GFXFF);
    EEPROM.writeByte(EE_BYTE_TEF, TEF);
    EEPROM.commit();
    while (true);
    for (;;);
  }
}

void doTheme() {  // Use this to put your own colors in: http://www.barth-dev.de/online/rgb565-color-picker/
  switch (CurrentTheme) {
    case 0:  // Default PE5PVB theme
      PrimaryColor = TFT_YELLOW;
      SecondaryColor = TFT_SKYBLUE;
      FrequencyColor = TFT_YELLOW;
      FrameColor = TFT_BLUE;
      GreyoutColor = 0x38E7;
      BackgroundColor = TFT_BLACK;
      ActiveColor = TFT_WHITE;
      OptimizerColor = 1;
      StereoColor = TFT_RED;
      RDSColor = TFT_SKYBLUE;
      CurrentThemeString = myLanguage[language][78];
      break;
    case 1:  // Cyan theme
      PrimaryColor = 0x0F3F;
      SecondaryColor = 0x0F3F;
      FrequencyColor = 0x0F3F;
      FrameColor = 0x0248;
      GreyoutColor = 0x4A69;
      BackgroundColor = 0x0000;
      ActiveColor = 0xFFFF;
      OptimizerColor = 1;
      StereoColor = 0xF3F;
      RDSColor = 0xFFFF;
      CurrentThemeString = myLanguage[language][79];
      break;
    case 2:  // Crimson theme
      PrimaryColor = 0xF8C3;
      SecondaryColor = 0xF8C3;
      FrequencyColor = 0xF8C3;
      FrameColor = 0x3800;
      GreyoutColor = 0x4A69;
      BackgroundColor = 0x0000;
      ActiveColor = 0xFFFF;
      OptimizerColor = 1;
      StereoColor = 0xF8C3;
      RDSColor = 0xFFFF;
      CurrentThemeString = myLanguage[language][80];
      break;
    case 3:  // Monochrome theme
      PrimaryColor = 0xFFFF;
      SecondaryColor = 0xFFFF;
      FrequencyColor = 0xFFFF;
      FrameColor = 0x2965;
      GreyoutColor = 0x4A69;
      BackgroundColor = 0x0000;
      ActiveColor = 0xFFFF;
      OptimizerColor = 1;
      StereoColor = 0xFFFF;
      RDSColor = 0xFFFF;
      CurrentThemeString = myLanguage[language][81];
      break;
    case 4:  // Volcano theme
      PrimaryColor = 0xFC00;
      SecondaryColor = 0xFC00;
      FrequencyColor = 0xFC00;
      FrameColor = 0x2965;
      GreyoutColor = 0x5140;
      BackgroundColor = 0x0806;
      ActiveColor = 0xFFFF;
      OptimizerColor = 1;
      StereoColor = 0xFC00;
      RDSColor = 0xFFFF;
      CurrentThemeString = myLanguage[language][82];
      break;
    case 5:  // Dendro theme
      PrimaryColor = TFT_GREEN;
      SecondaryColor = TFT_GREEN;
      FrequencyColor = TFT_GREEN;
      FrameColor = 0x0200;
      GreyoutColor = 0x4A69;
      BackgroundColor = 0x0000;
      ActiveColor = 0xFFFF;
      OptimizerColor = 1;
      StereoColor = TFT_GREEN;
      RDSColor = PrimaryColor;
      CurrentThemeString = myLanguage[language][83];
      break;
    case 6:  // Sakura theme
      PrimaryColor = 0xF3D5;
      SecondaryColor = 0xF3D5;
      FrequencyColor = 0xF3D5;
      FrameColor = 0x3845;
      GreyoutColor = 0x4A69;
      BackgroundColor = 0x0000;
      ActiveColor = 0xFFFF;
      OptimizerColor = 1;
      StereoColor = 0xF3D5;
      RDSColor = ActiveColor;
      CurrentThemeString = myLanguage[language][84];
      break;
    case 7:  // Whiteout theme
      PrimaryColor = 0x0000;
      SecondaryColor = 0x0000;
      FrequencyColor = 0x18C3;
      FrameColor = 0x630C;
      GreyoutColor = 0x9492;
      BackgroundColor = 0xDFFC;
      ActiveColor = 0x0000;
      OptimizerColor = 0xFFDF;
      StereoColor = 0x0000;
      RDSColor = 0x0000;
      CurrentThemeString = myLanguage[language][85];
      break;
  }
}

void read_encoder() {
  static uint8_t old_AB = 3;
  static int8_t encval = 0;
  static const int8_t enc_states[]  = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};

  old_AB <<= 2;

  if (digitalRead(ROTARY_PIN_A)) old_AB |= 0x02;
  if (digitalRead(ROTARY_PIN_B)) old_AB |= 0x01;
  encval += enc_states[( old_AB & 0x0f )];

  if (optenc == 1) {
    if (encval > 2) {
      if (rotarymode == true) rotary = -1; else rotary = 1;
      encval = 0;
    } else if (encval < -2) {
      if (rotarymode == true) rotary = 1; else rotary = -1;
      encval = 0;
    }
  } else {
    if (encval > 3) {
      if (rotarymode == true) rotary = -1; else rotary = 1;
      encval = 0;
    } else if (encval < -3) {
      if (rotarymode == true) rotary = 1; else rotary = -1;
      encval = 0;
    }
  }
}

void tryWiFi() {
  if (!setupmode) tft.drawRoundRect(1, 60, 319, 140, 5, ActiveColor);
  if (!setupmode) tft.fillRoundRect(3, 62, 315, 136, 5, BackgroundColor);
  if (!setupmode) tft.setFreeFont(FONT14);
  if (!setupmode) tft.setTextColor(ActiveColor);
  if (!setupmode) tft.drawCentreString(myLanguage[language][55], 155, 80, GFXFF);
  if (wc.autoConnect()) {
    Server.begin();
    Udp.begin(9031);
    remoteip = IPAddress (WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], subnetclient);
    if (!setupmode) tft.setTextColor(TFT_GREEN);
    if (!setupmode) tft.drawCentreString(myLanguage[language][57], 155, 120, GFXFF);
    wifi = true;
  } else {
    Server.end();
    Udp.stop();
    if (!setupmode) tft.setTextColor(TFT_RED);
    if (!setupmode) tft.drawCentreString(myLanguage[language][56], 155, 120, GFXFF);
    wifi = false;
    XDRGTKTCP = false;
    RDSSPYTCP = false;
  }
}

void passwordcrypt() {
  int generated = 0;
  while (generated < 16)
  {
    byte randomValue = random(0, 26);
    char letter = randomValue + 'a';
    if (randomValue > 26) letter = (randomValue - 26);
    saltkey.setCharAt(generated, letter);
    generated ++;
  }
  salt = saltkey + XDRGTK_key;
  cryptedpassword = String(sha1(salt));
}

void DefaultSettings() {
  EEPROM.writeByte(EE_BYTE_CHECKBYTE, EE_CHECKBYTE_VALUE);
  EEPROM.writeUInt(EE_UINT_FREQUENCY_FM, 10000);
  EEPROM.writeInt(EE_INT_VOLSET, 0);
  EEPROM.writeUInt(EE_UINT_CONVERTERSET, 0);
  EEPROM.writeUInt(EE_UINT_FMLOWEDGESET, 875);
  EEPROM.writeUInt(EE_UINT_FMHIGHEDGESET, 1080);
  EEPROM.writeByte(EE_BYTE_CONTRASTSET, 50);
  EEPROM.writeByte(EE_BYTE_STEREOLEVEL, 0);
  EEPROM.writeByte(EE_BYTE_HIGHCUTLEVEL, 70);
  EEPROM.writeByte(EE_BYTE_HIGHCUTOFFSET, 0);
  EEPROM.writeInt(EE_INT_LEVELOFFSET, 0);
  EEPROM.writeByte(EE_BYTE_EDGEBEEP, 0);
  EEPROM.writeByte(EE_BYTE_SOFTMUTEAM, 0);
  EEPROM.writeByte(EE_BYTE_SOFTMUTEFM, 0);
  EEPROM.writeUInt(EE_UINT_FREQUENCY_AM, 828);
  EEPROM.writeByte(EE_BYTE_LANGUAGE, 0);
  EEPROM.writeByte(EE_BYTE_SHOWRDSERRORS, 1);
  EEPROM.writeByte(EE_BYTE_TEF, 0);
  EEPROM.writeByte(EE_BYTE_DISPLAYFLIP, 0);
  EEPROM.writeByte(EE_BYTE_ROTARYMODE, 0);
  EEPROM.writeByte(EE_BYTE_STEPSIZE, 0);
  EEPROM.writeByte(EE_BYTE_TUNEMODE, 0);
  EEPROM.writeByte(EE_BYTE_OPTENC, 0);
  EEPROM.writeByte(EE_BYTE_IMSSET, 1);
  EEPROM.writeByte(EE_BYTE_EQSET, 1);
  EEPROM.writeByte(EE_BYTE_BAND, 0);
  EEPROM.writeInt(EE_INT_LOWLEVELSET, -10);
  EEPROM.writeByte(EE_BYTE_MEMORYPOS, 0);
  EEPROM.writeByte(EE_BYTE_REGION, 0);
  EEPROM.writeByte(EE_BYTE_RDS_UNDERSCORE, 0);
  EEPROM.writeByte(EE_BYTE_USBMODE, 0);
  EEPROM.writeByte(EE_BYTE_WIFI, 0);
  EEPROM.writeByte(EE_BYTE_SUBNETCLIENT, 1);
  EEPROM.writeByte(EE_BYTE_SHOWSWMIBAND, 1);
  EEPROM.writeByte(EE_BYTE_RDS_FILTER, 1);
  EEPROM.writeByte(EE_BYTE_RDS_PIERRORS, 0);
  for (int i = 0; i < EE_PRESETS_CNT; i++) EEPROM.writeByte(i + EE_PRESETS_BAND_START, BAND_FM);
  for (int i = 0; i < EE_PRESETS_CNT; i++) EEPROM.writeUInt((i * 4) + EE_PRESETS_START, EE_PRESETS_FREQUENCY);
  EEPROM.writeUInt(EE_UINT_FREQUENCY_LW, 180);
  EEPROM.writeUInt(EE_UINT_FREQUENCY_MW, 540);
  EEPROM.writeUInt(EE_UINT_FREQUENCY_SW, 1800);
  EEPROM.writeString(EE_STRING_XDRGTK_KEY, "password");
  EEPROM.writeByte(EE_BYTE_SHOWSQUELCH, 1);
  EEPROM.writeByte(EE_BYTE_SHOWMODULATION, 1);
  EEPROM.writeByte(EE_BYTE_AM_NB, 0);
  EEPROM.writeByte(EE_BYTE_FM_NB, 0);
  EEPROM.writeByte(EE_BYTE_AUDIOMODE, 0);
  EEPROM.writeByte(EE_BYTE_OIRT, 0);
  EEPROM.writeUInt(EE_UINT_LOWEDGEOIRTSET, 0);
  EEPROM.writeUInt(EE_UINT_HIGHEDGEOIRTSET, 0);
  EEPROM.writeByte(EE_BYTE_COLORINVERT, 0);
  EEPROM.writeByte(EE_BYTE_POWEROPTIONS, 0);
  EEPROM.writeByte(EE_BYTE_CURRENTTHEME, 0);
  EEPROM.writeByte(EE_BYTE_FMDEFAULTSTEPSIZE, 0);
  EEPROM.writeByte(EE_BYTE_SCREENSAVERSET, 0);
  EEPROM.writeInt(EE_INT_AMLEVELOFFSET, 0);
  EEPROM.writeByte(EE_BYTE_UNIT, 0);
  EEPROM.writeByte(EE_BYTE_AF, 0);
  EEPROM.commit();
}
