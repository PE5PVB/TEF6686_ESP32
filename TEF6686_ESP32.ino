#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include <WiFiClient.h>
#include <EEPROM.h>
#include <Wire.h>
#include <math.h>
#include <TFT_eSPI.h>               // https://github.com/Bodmer/TFT_eSPI
#include <TimeLib.h>                // https://github.com/PaulStoffregen/Time
#include <Hash.h>                   // https://github.com/bbx10/Hash_tng
#include "src/WiFiConnect.h"
#include "src/WiFiConnectParam.h"
#include "src/FONT16.h"
#include "src/FONT28.h"
#include "src/FONT48DEC.h"
#include "src/TEF6686.h"
#include "src/constants.h"
#include "src/language.h"

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
bool afpage;
bool afscreen;
bool aftest;
bool artheadold;
bool batterydetect = true;
bool BWreset;
bool change2;
bool cleanup;
bool compressedold;
bool direction;
bool dropout;
bool dynamicPTYold;
bool edgebeep;
bool errorAold;
bool errorBold;
bool errorCold;
bool errorDold;
bool fullsearchrds;
bool hasafold;
bool haseonold;
bool hasrtplusold;
bool hastmcold;
bool LowLevelInit;
bool memorystore;
bool menu;
bool menuopen;
bool nobattery;
bool power = true;
bool RDSSPYTCP;
bool RDSSPYUSB;
bool RDSstatus;
bool RDSstatusold;
bool rdsstereoold;
bool resetFontOnNextCall;
bool screenmute;
bool screensavertriggered = false;
bool seek;
bool setupmode;
bool showrdserrors;
bool showsquelch;
bool softmuteam;
bool softmutefm;
bool SQ;
bool Stereostatusold;
bool StereoToggle;
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
byte af_counterold;
byte afpagenr;
byte amnb;
byte audiomode;
byte band;
byte battery;
byte batteryold;
byte BWset;
byte colorinvert;
byte ContrastSet;
byte CurrentTheme;
byte displayflip;
byte ECCold;
byte EQset;
byte fmdefaultstepsize;
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
byte poweroptions;
byte poweroptionsold;
byte rdsblockold;
byte region;
byte regionold;
byte rotarymode;
byte screensaverOptions[5] = {0, 3, 10, 30, 60};
byte screensaverset;
byte showmodulation;
byte showSWMIBand = 1;
byte SNRold;
byte specialstepOIRT;
byte stepsize;
byte StereoLevel;
byte subnetclient;
byte TEF;
byte theme;
byte tunemode;
byte unit;
char buff[16];
char programTypePrevious[18];
char radioIdPrevious[6];
const uint8_t* currentFont = nullptr;
int ActiveColor;
int ActiveColorSmooth;
int AGC;
int AMLevelOffset;
int BackgroundColor;
int batupdatetimer;
int BWOld;
int bwupdatetimer;
int charWidth = tft.textWidth("AA");
int DeEmphasis;
int ForceMono;
int FrameColor;
int freqold;
int FrequencyColor;
int GreyoutColor;
int menuoption = 30;
int MStatusold;
int offsetupdatetimer;
int OStatusold;
int peakholdold;
int peakholdtimer;
int PrimaryColor;
int PrimaryColorSmooth;
int SignificantColor;
int SignificantColorSmooth;
int InsignificantColor;
int InsignificantColorSmooth;
int rotary;
int rssi;
int rssiold = 200;
int scanner_filter;
int SecondaryColor;
int SecondaryColorSmooth;
int snrupdatetimer;
int Sqstatusold;
int Squelch;
int Squelchold;
int SStatusold;
int Stereostatus;
int volume;
int XDRBWset;
int XDRBWsetold;
int xPos;
int xPos2;
int xPos3;
int xPos4;
int16_t OStatus;
int16_t SAvg;
int16_t SAvg2;
int16_t SStatus;
int8_t LevelOffset;
int8_t LowLevelSet;
int8_t VolSet;
IPAddress remoteip;
String afstringold;
String cryptedpassword;
String CurrentThemeString;
String ECColdtxt;
String eonpsold[11];
String eonstringold;
String LIColdString;
String pinstringold;
String PIold;
String programServicePrevious;
String PSold;
String ptynold = " ";
String PTYold;
String rds_clock;
String rds_clockold;
String RDSSPYRDS;
String RDSSPYRDSold;
String RTold;
String rtplusstringold;
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
uint8_t SNR;
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
unsigned int mappedfreqold[20];
unsigned int memory[EE_PRESETS_CNT];
unsigned int MWHighEdgeSet;
unsigned int MWLowEdgeSet;
unsigned int scanner_end;
unsigned int scanner_start;
unsigned int scanner_step;
unsigned int SWHighEdgeSet;
unsigned int SWLowEdgeSet;
unsigned long afticker;
unsigned long aftickerhold;
unsigned long aftimer;
unsigned long eonticker;
unsigned long eontickerhold;
unsigned long lowsignaltimer;
unsigned long peakholdmillis;
unsigned long rtplusticker;
unsigned long rtplustickerhold;
unsigned long rtticker;
unsigned long rttickerhold;

TEF6686 radio;
TFT_eSprite sprite = TFT_eSprite(&tft);
TFT_eSprite sprite2 = TFT_eSprite(&tft);
TFT_eSprite sprite3 = TFT_eSprite(&tft);
TFT_eSprite sprite4 = TFT_eSprite(&tft);
TFT_eSprite sprite5 = TFT_eSprite(&tft);
WiFiConnect wc;
WiFiServer Server(7373);
WiFiClient RemoteClient;
WiFiUDP Udp;
hw_timer_t *timScreensaver = NULL;
byte screensaver_IRQ = OFF;

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  setupmode = true;
  EEPROM.begin(EE_TOTAL_CNT);
  if (EEPROM.readByte(EE_BYTE_CHECKBYTE) != EE_CHECKBYTE_VALUE) DefaultSettings();

  frequency = EEPROM.readUInt(EE_UINT16_FREQUENCY_FM);
  VolSet = EEPROM.readInt(EE_BYTE_VOLSET);
  ConverterSet = EEPROM.readUInt(EE_UINT16_CONVERTERSET);
  LowEdgeSet = EEPROM.readUInt(EE_UINT16_FMLOWEDGESET);
  HighEdgeSet = EEPROM.readUInt(EE_UINT16_FMHIGHEDGESET);
  ContrastSet = EEPROM.readByte(EE_BYTE_CONTRASTSET);
  StereoLevel = EEPROM.readByte(EE_BYTE_STEREOLEVEL);
  HighCutLevel = EEPROM.readByte(EE_BYTE_HIGHCUTLEVEL);
  HighCutOffset = EEPROM.readByte(EE_BYTE_HIGHCUTOFFSET);
  LevelOffset = EEPROM.readByte(EE_BYTE_LEVELOFFSET);
  edgebeep = EEPROM.readByte(EE_BYTE_EDGEBEEP);
  softmuteam = EEPROM.readByte(EE_BYTE_SOFTMUTEAM);
  softmutefm = EEPROM.readByte(EE_BYTE_SOFTMUTEFM);
  frequency_AM = EEPROM.readUInt(EE_UINT16_FREQUENCY_AM);
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
  LowLevelSet = EEPROM.readInt(EE_BYTE_LOWLEVELSET);
  memorypos = EEPROM.readByte(EE_BYTE_MEMORYPOS);
  region = EEPROM.readByte(EE_BYTE_REGION);
  radio.rds.underscore = EEPROM.readByte(EE_BYTE_RDS_UNDERSCORE);
  USBmode = EEPROM.readByte(EE_BYTE_USBMODE);
  wifi = EEPROM.readByte(EE_BYTE_WIFI);
  subnetclient = EEPROM.readByte(EE_BYTE_SUBNETCLIENT);
  showSWMIBand = EEPROM.readByte(EE_BYTE_SHOWSWMIBAND);
  radio.rds.filter = EEPROM.readByte(EE_BYTE_RDS_FILTER);
  radio.rds.pierrors = EEPROM.readByte(EE_BYTE_RDS_PIERRORS);
  frequency_LW = EEPROM.readUInt(EE_UINT16_FREQUENCY_LW);
  frequency_MW = EEPROM.readUInt(EE_UINT16_FREQUENCY_MW);
  frequency_SW = EEPROM.readUInt(EE_UINT16_FREQUENCY_SW);
  XDRGTK_key = EEPROM.readString(EE_STRING_XDRGTK_KEY);
  showsquelch = EEPROM.readByte(EE_BYTE_SHOWSQUELCH);
  showmodulation = EEPROM.readByte(EE_BYTE_SHOWMODULATION);
  amnb = EEPROM.readByte(EE_BYTE_AM_NB);
  fmnb = EEPROM.readByte(EE_BYTE_FM_NB);
  audiomode = EEPROM.readByte(EE_BYTE_AUDIOMODE);
  specialstepOIRT = EEPROM.readByte(EE_BYTE_OIRT);
  LowEdgeOIRTSet = EEPROM.readUInt(EE_UINT16_LOWEDGEOIRTSET);
  HighEdgeOIRTSet = EEPROM.readUInt(EE_UINT16_HIGHEDGEOIRTSET);
  colorinvert = EEPROM.readByte(EE_BYTE_COLORINVERT);
  poweroptions = EEPROM.readByte(EE_BYTE_POWEROPTIONS);
  CurrentTheme = EEPROM.readByte(EE_BYTE_CURRENTTHEME);
  fmdefaultstepsize = EEPROM.readByte(EE_BYTE_FMDEFAULTSTEPSIZE);
  screensaverset = EEPROM.readByte(EE_BYTE_SCREENSAVERSET);
  AMLevelOffset = EEPROM.readInt(EE_INT16_AMLEVELOFFSET);
  unit = EEPROM.readByte(EE_BYTE_UNIT);
  af = EEPROM.readByte(EE_BYTE_AF);
  StereoToggle = EEPROM.readByte(EE_BYTE_STEREO);

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
    tftPrint(0, myLanguage[language][1], 155, 85, ActiveColor, ActiveColorSmooth, FONT28);
    tftPrint(0, myLanguage[language][2], 155, 115, ActiveColor, ActiveColorSmooth, FONT28);
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
    tftPrint(0, myLanguage[language][3], 155, 85, ActiveColor, ActiveColorSmooth, FONT28);
    tftPrint(0, myLanguage[language][2], 155, 115, ActiveColor, ActiveColorSmooth, FONT28);
    while (digitalRead(MODEBUTTON) == LOW) delay(50);
  }

  if (digitalRead(BANDBUTTON) == LOW) {
    analogWrite(SMETERPIN, 511);
    analogWrite(CONTRASTPIN, ContrastSet * 2 + 27);
    tftPrint(0, myLanguage[language][4], 155, 85, ActiveColor, ActiveColorSmooth, FONT28);
    tftPrint(0, myLanguage[language][5], 155, 115, ActiveColor, ActiveColorSmooth, FONT28);
    while (digitalRead(BANDBUTTON) == LOW) delay(50);
    analogWrite(SMETERPIN, 0);
  }

  if (digitalRead(ROTARY_BUTTON) == LOW && digitalRead(BWBUTTON) == HIGH) {
    analogWrite(CONTRASTPIN, ContrastSet * 2 + 27);
    if (optenc == 0) {
      optenc = 1;
      tftPrint(0, myLanguage[language][6], 155, 85, ActiveColor, ActiveColorSmooth, FONT28);
    } else {
      optenc = 0;
      tftPrint(0, myLanguage[language][7], 155, 85, ActiveColor, ActiveColorSmooth, FONT28);
    }
    EEPROM.writeByte(EE_BYTE_OPTENC, optenc);
    EEPROM.commit();
    tftPrint(0, myLanguage[language][2], 155, 115, ActiveColor, ActiveColorSmooth, FONT28);
    while (digitalRead(ROTARY_BUTTON) == LOW) delay(50);
  }

  if (digitalRead(ROTARY_BUTTON) == LOW && digitalRead(BWBUTTON) == LOW) {
    analogWrite(CONTRASTPIN, ContrastSet * 2 + 27);
    DefaultSettings();
    tftPrint(0, myLanguage[language][66], 155, 85, ActiveColor, ActiveColorSmooth, FONT28);
    tftPrint(0, myLanguage[language][2], 155, 115, ActiveColor, ActiveColorSmooth, FONT28);
    while (digitalRead(ROTARY_BUTTON) == LOW && digitalRead(BWBUTTON) == LOW) delay(50);
    ESP.restart();
  }

  tft.setSwapBytes(true);
  tft.fillScreen(BackgroundColor);
  tftPrint(0, myLanguage[language][8], 160, 3, PrimaryColor, PrimaryColorSmooth, FONT28);
  tftPrint(0, "Software " + String(VERSION), 160, 152, PrimaryColor, PrimaryColorSmooth, FONT16);

  tft.fillSmoothCircle(160, 90, 60, SignificantColor, SignificantColorSmooth);
  tft.fillSmoothCircle(160, 90, 52, BackgroundColor, SignificantColorSmooth);

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

  if (lowByte(device) == 14) {
    fullsearchrds = false;
    tft.fillRect(152, 230, 16, 6, PrimaryColor);
    tftPrint(0, "TEF6686 Lithio", 160, 172, ActiveColor, ActiveColorSmooth, FONT28);
  } else if (lowByte(device) == 1) {
    fullsearchrds = true;
    tft.fillRect(152, 230, 16, 6, PrimaryColor);
    tftPrint(0, "TEF6687 Lithio FMSI", 160, 172, ActiveColor, ActiveColorSmooth, FONT28);
  } else if (lowByte(device) == 9) {
    fullsearchrds = false;
    tft.fillRect(152, 230, 16, 6, PrimaryColor);
    tftPrint(0, "TEF6688 Lithio DR", 160, 172, ActiveColor, ActiveColorSmooth, FONT28);
  } else if (lowByte(device) == 3) {
    fullsearchrds = true;
    tft.fillRect(152, 230, 16, 6, PrimaryColor);
    tftPrint(0, "TEF6689 Lithio FMSI DR", 160, 172, ActiveColor, ActiveColorSmooth, FONT28);
  } else {
    tftPrint(0, myLanguage[language][9], 160, 172, SignificantColor, SignificantColorSmooth, FONT28);
    tft.fillRect(152, 230, 16, 6, TFT_RED);
    while (true);
    for (;;);
  }
  tftPrint(0, "Patch: v" + String(TEF), 160, 202, ActiveColor, ActiveColorSmooth, FONT28);

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
  if (!StereoToggle) radio.setMono(true);
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

  setupmode = false;
  sprite.createSprite(280, 19);
  sprite2.createSprite(172, 19);
  sprite3.createSprite(172, 19);
  sprite4.createSprite(172, 19);
  sprite5.createSprite(172, 19);
  sprite.setTextDatum(TL_DATUM);
  sprite2.setTextDatum(TL_DATUM);
  sprite3.setTextDatum(TL_DATUM);
  sprite4.setTextDatum(TL_DATUM);
  sprite5.setTextDatum(TL_DATUM);
  radio.tone(50, -5, 2000);

  if (screensaverset) {
    ScreensaverTimerInit();
    ScreensaverTimerSet(screensaverOptions[screensaverset]);
  }
}

void loop() {
  if (digitalRead(BANDBUTTON) == LOW ) BANDBUTTONPress();

  if (power == true) {
    Communication();

    if (band == BAND_FM && af && radio.rds.correctPI != 0) {
      if ((aftest && millis() >= aftimer + 3000) || ((USN > 250 || WAM > 250) && millis() >= aftimer + 1000)) {
        aftimer = millis();
        aftest = false;
        frequency = radio.TestAF();
        if (freqold != frequency) {
          ShowFreq(0);
          if (XDRGTKUSB == true || XDRGTKTCP == true) DataPrint("T" + String(frequency * 10));
          store = true;
        }
      }

      if (band == BAND_FM && millis() >= aftimer + 10000) {
        aftimer = millis();
        if (USN > 150 || WAM > 150) {
          frequency = radio.TestAF();
          if (freqold != frequency) {
            ShowFreq(0);
            if (XDRGTKUSB == true || XDRGTKTCP == true) DataPrint("T" + String(frequency * 10));
            store = true;
          }
        }
      }
    }

    if (seek == true) Seek(direction);

    if ((SStatus / 10 > LowLevelSet) && LowLevelInit == false && menu == false && band == BAND_FM) {
      if (screenmute == false && !advancedRDS && !afscreen) {
        if (showmodulation) {
          tftPrint(-1, "10", 27, 148, ActiveColor, ActiveColorSmooth, FONT16);
          tftPrint(-1, "30", 57, 148, ActiveColor, ActiveColorSmooth, FONT16);
          tftPrint(-1, "50", 87, 148, ActiveColor, ActiveColorSmooth, FONT16);
          tftPrint(-1, "70", 117, 148, ActiveColor, ActiveColorSmooth, FONT16);
          tftPrint(-1, "100", 164, 148, ActiveColor, ActiveColorSmooth, FONT16);
          tftPrint(0, "M", 7, 134, ActiveColor, ActiveColorSmooth, FONT16);
          for (byte segments = 0; segments < 94; segments++) {
            if (segments > 54) {
              if (((segments - 53) % 10) == 0) tft.fillRect(16 + (2 * segments), 143, 2, 3, TFT_RED);
            } else {
              if (((segments + 1) % 6) == 0) tft.fillRect(16 + (2 * segments), 143, 2, 3, TFT_GREEN);
            }
          }
        }
        if (region == 0) tftPrint(-1, "PI:", 216, 197, ActiveColor, ActiveColorSmooth, FONT16);
        if (region == 1) tftPrint(-1, "ID:", 216, 197, ActiveColor, ActiveColorSmooth, FONT16);
        tftPrint(-1, "PS:", 6, 197, ActiveColor, ActiveColorSmooth, FONT16);
        tftPrint(-1, "RT:", 6, 222, ActiveColor, ActiveColorSmooth, FONT16);
        tftPrint(-1, "PTY:", 6, 170, ActiveColor, ActiveColorSmooth, FONT16);
        if (!showmodulation) tft.drawLine(20, 146, 204, 146, GreyoutColor); else tft.drawLine(20, 146, 204, 146, TFT_DARKGREY);
      }
      LowLevelInit = true;
    }

    if ((SStatus / 10 <= LowLevelSet) && band == BAND_FM) {
      if (LowLevelInit == true && menu == false) {
        if (screenmute == false && !afscreen && !advancedRDS) {
          for (byte segments = 0; segments < 94; segments++) {
            if (segments > 54) {
              if (((segments - 53) % 10) == 0) tft.fillRect(16 + (2 * segments), 143, 2, 3, GreyoutColor);
            } else {
              if (((segments + 1) % 6) == 0) tft.fillRect(16 + (2 * segments), 143, 2, 3, GreyoutColor);
            }
          }
          if (showmodulation) {
            tftPrint(-1, "10", 27, 148, GreyoutColor, BackgroundColor, FONT16);
            tftPrint(-1, "30", 57, 148, GreyoutColor, BackgroundColor, FONT16);
            tftPrint(-1, "50", 87, 148, GreyoutColor, BackgroundColor, FONT16);
            tftPrint(-1, "70", 117, 148, GreyoutColor, BackgroundColor, FONT16);
            tftPrint(-1, "100", 164, 148, GreyoutColor, BackgroundColor, FONT16);
            tftPrint(0, "M", 7, 134, GreyoutColor, BackgroundColor, FONT16);
            tft.fillRect(16, 135, 188, 8, GreyoutColor);
          }
          if (region == 0) tftPrint(-1, "PI:", 216, 197, GreyoutColor, BackgroundColor, FONT16);
          if (region == 1) tftPrint(-1, "ID:", 216, 197, GreyoutColor, BackgroundColor, FONT16);
          tftPrint(-1, "PS:", 6, 197, GreyoutColor, BackgroundColor, FONT16);
          tftPrint(-1, "RT:", 6, 222, GreyoutColor, BackgroundColor, FONT16);
          tftPrint(-1, "PTY:", 6, 170, GreyoutColor, BackgroundColor, FONT16);
          tft.drawLine(20, 146, 204, 146, GreyoutColor);
          tft.drawBitmap(139, 5, RDSLogo, 35, 22, GreyoutColor);
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
          if (SStatusold / 10 != SStatus / 10) tftReplace(1, String(SStatusold / 10), String(SStatus / 10), 140, 149, PrimaryColor, PrimaryColorSmooth, FONT48);
          tftReplace(1, "." + String(abs(SStatusold % 10)), "." + String(abs(SStatus % 10)), 160, 149, PrimaryColor, PrimaryColorSmooth, FONT28);
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
      EEPROM.writeUInt(EE_UINT16_FREQUENCY_FM, frequency);
      EEPROM.writeUInt(EE_UINT16_FREQUENCY_AM, frequency_AM);
      EEPROM.writeByte(EE_BYTE_BAND, band);
      EEPROM.writeUInt(EE_UINT16_FREQUENCY_LW, frequency_LW);
      EEPROM.writeUInt(EE_UINT16_FREQUENCY_MW, frequency_MW);
      EEPROM.writeUInt(EE_UINT16_FREQUENCY_SW, frequency_SW);
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
  EEPROM.writeUInt(EE_UINT16_FREQUENCY_FM, frequency);
  EEPROM.writeUInt(EE_UINT16_FREQUENCY_AM, frequency_AM);
  EEPROM.writeByte(EE_BYTE_BAND, band);
  EEPROM.writeUInt(EE_UINT16_FREQUENCY_LW, frequency_LW);
  EEPROM.writeUInt(EE_UINT16_FREQUENCY_MW, frequency_MW);
  EEPROM.writeUInt(EE_UINT16_FREQUENCY_SW, frequency_SW);
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
    doBW();
    radio.getStatusAM(SStatus, USN, WAM, OStatus, BW, MStatus, SNR);
    if (screenmute == false) radio.clearRDS(fullsearchrds); BuildDisplay();
    if (region == 0) tftPrint(-1, "PI:", 216, 197, GreyoutColor, BackgroundColor, FONT16);
    if (region == 1) tftPrint(-1, "ID:", 216, 195, GreyoutColor, BackgroundColor, FONT16);
    tftPrint(-1, "PS:", 6, 197, GreyoutColor, BackgroundColor, FONT16);
    tftPrint(-1, "RT:", 6, 222, GreyoutColor, BackgroundColor, FONT16);
    tftPrint(-1, "PTY:", 6, 170, GreyoutColor, BackgroundColor, FONT16);
    tft.drawBitmap(139, 5, RDSLogo, 35, 22, GreyoutColor);
    tft.drawRoundRect(248, 56, 32, 20, 5, GreyoutColor);
    tftPrint(0, "iMS", 265, 59, GreyoutColor, BackgroundColor, FONT16);
    tft.drawRoundRect(286, 56, 32, 20, 5, GreyoutColor);
    tftPrint(0, "EQ", 303, 59, GreyoutColor, BackgroundColor, FONT16);
  } else {
    LowLevelInit = false;
    BWreset = true;
    BWset = 0;
    if (tunemode == TUNE_MI_BAND) tunemode = TUNE_MAN;
    radio.power(0);
    delay(50);
    radio.SetFreq(frequency);
    freqold = frequency_AM;
    doBW();
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
      tft.drawSmoothCircle(81, 15, 10, BackgroundColor, BackgroundColor);
      tft.drawSmoothCircle(81, 15, 9, BackgroundColor, BackgroundColor);
      tft.drawSmoothCircle(91, 15, 10, BackgroundColor, BackgroundColor);
      tft.drawSmoothCircle(91, 15, 9, BackgroundColor, BackgroundColor);
      tft.drawSmoothCircle(86, 15, 10, SecondaryColor, SecondaryColorSmooth);
      tft.drawSmoothCircle(86, 15, 9, SecondaryColor, SecondaryColorSmooth);
    }
    radio.setMono(true);
    StereoToggle = false;
  } else {
    if (screenmute == false) {
      tft.drawSmoothCircle(86, 15, 10, BackgroundColor, BackgroundColor);
      tft.drawSmoothCircle(86, 15, 9, BackgroundColor, BackgroundColor);
    }
    radio.setMono(false);
    Stereostatusold = false;
    StereoToggle = true;
  }
  EEPROM.writeByte(EE_BYTE_STEREO, StereoToggle);
  EEPROM.commit();
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
          tftPrint(-1, myLanguage[language][86], 70, 68, ActiveColor, ActiveColorSmooth, FONT28);
          delay(1000);
          tftPrint(-1, myLanguage[language][86], 70, 68, BackgroundColor, BackgroundColor, FONT28);
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
      RDSstatus = false;
      if (specialstepOIRT) {
        if (frequency >= (FREQ_FM_OIRT_START) && frequency <= (FREQ_FM_OIRT_END)) {
          if (frequency % 3 != 0) {
            Round30K(frequency);
            EEPROM.writeUInt(EE_UINT16_FREQUENCY_FM, frequency);
          }
        } else {
          if (fmdefaultstepsize == 1) Round100K(frequency); else Round50K(frequency);
        }
      } else {
        if (frequency % 10 != 0) {
          if (fmdefaultstepsize == 1) Round100K(frequency); else Round50K(frequency);
          EEPROM.writeUInt(EE_UINT16_FREQUENCY_FM, frequency);
        }
      }
      radio.clearRDS(fullsearchrds);
      BuildDisplay();
      ShowSignalLevel();
      ShowBW();
      menu = false;
      menuopen = false;
      LowLevelInit = true;
      EEPROM.writeInt(EE_BYTE_VOLSET, VolSet);
      EEPROM.writeUInt(EE_UINT16_CONVERTERSET, ConverterSet);
      EEPROM.writeUInt(EE_UINT16_FMLOWEDGESET, LowEdgeSet);
      EEPROM.writeUInt(EE_UINT16_FMHIGHEDGESET, HighEdgeSet);
      EEPROM.writeByte(EE_BYTE_CONTRASTSET, ContrastSet);
      EEPROM.writeByte(EE_BYTE_STEREOLEVEL, StereoLevel);
      EEPROM.writeByte(EE_BYTE_HIGHCUTLEVEL, HighCutLevel);
      EEPROM.writeByte(EE_BYTE_HIGHCUTOFFSET, HighCutOffset);
      EEPROM.writeInt(EE_BYTE_LEVELOFFSET, LevelOffset);
      EEPROM.writeByte(EE_BYTE_EDGEBEEP, edgebeep);
      EEPROM.writeByte(EE_BYTE_SOFTMUTEAM, softmuteam);
      EEPROM.writeByte(EE_BYTE_SOFTMUTEFM, softmutefm);
      EEPROM.writeByte(EE_BYTE_LANGUAGE, language);
      EEPROM.writeByte(EE_BYTE_SHOWRDSERRORS, showrdserrors);
      EEPROM.writeInt(EE_BYTE_LOWLEVELSET, LowLevelSet);
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
      EEPROM.writeUInt(EE_UINT16_LOWEDGEOIRTSET, LowEdgeOIRTSet);
      EEPROM.writeUInt(EE_UINT16_HIGHEDGEOIRTSET, HighEdgeOIRTSet);
      EEPROM.writeByte(EE_BYTE_COLORINVERT, colorinvert);
      EEPROM.writeByte(EE_BYTE_POWEROPTIONS, poweroptions);
      EEPROM.writeByte(EE_BYTE_CURRENTTHEME, CurrentTheme);
      EEPROM.writeByte(EE_BYTE_FMDEFAULTSTEPSIZE, fmdefaultstepsize);
      EEPROM.writeByte(EE_BYTE_SCREENSAVERSET, screensaverset);
      EEPROM.writeInt(EE_INT16_AMLEVELOFFSET, AMLevelOffset);
      EEPROM.writeByte(EE_BYTE_UNIT, unit);
      EEPROM.writeByte(EE_BYTE_AF, af);
      EEPROM.writeByte(EE_BYTE_STEREO, StereoToggle);
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

  if (band == BAND_FM) EEPROM.writeUInt(EE_UINT16_FREQUENCY_FM, frequency); else EEPROM.writeUInt(EE_UINT16_FREQUENCY_AM, frequency_AM);
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
      tft.drawRoundRect(10, 30, 300, 170, 5, ActiveColor);
      tft.fillRoundRect(12, 32, 296, 166, 5, BackgroundColor);
      switch (menupage) {
        case 1:
          switch (menuoption) {
            case 30:
              tftPrint(0, myLanguage[language][10], 155, 78, ActiveColor, ActiveColorSmooth, FONT28);
              tftPrint(-1, "dB", 170, 118, ActiveColor, ActiveColorSmooth, FONT28);
              if (VolSet > 0) tftPrint(1, "+" + String(VolSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(1, String(VolSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
              break;

            case 50:
              tftPrint(0, myLanguage[language][11], 155, 78, ActiveColor, ActiveColorSmooth, FONT28);
              tftPrint(-1, "MHz", 170, 118, ActiveColor, ActiveColorSmooth, FONT28);
              tftPrint(1, String(ConverterSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
              break;

            case 70:
              tftPrint(0, myLanguage[language][12], 155, 78, ActiveColor, ActiveColorSmooth, FONT28);
              tftPrint(-1, "MHz", 170, 118, ActiveColor, ActiveColorSmooth, FONT28);
              tftPrint(1, String(LowEdgeSet / 10 + ConverterSet, DEC) + "." + String(LowEdgeSet % 10 + ConverterSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
              break;

            case 90:
              tftPrint(0, myLanguage[language][13], 155, 78, ActiveColor, ActiveColorSmooth, FONT28);
              tftPrint(-1, "MHz", 170, 118, ActiveColor, ActiveColorSmooth, FONT28);
              tftPrint(1, String(HighEdgeSet / 10 + ConverterSet, DEC) + "." + String(HighEdgeSet % 10 + ConverterSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
              break;

            case 110:
              tftPrint(0, myLanguage[language][14], 155, 78, ActiveColor, ActiveColorSmooth, FONT28);
              tftPrint(-1, "dB", 170, 118, ActiveColor, ActiveColorSmooth, FONT28);
              tftPrint(-1, "dBμV", 190, 165, ActiveColor, ActiveColorSmooth, FONT28);
              if (LevelOffset > 0) tftPrint(1, "+" + String(LevelOffset, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(1, String(LevelOffset, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
              SStatusold = 2000;
              change2 = true;
              break;

            case 130:
              tftPrint(0, myLanguage[language][15], 155, 78, ActiveColor, ActiveColorSmooth, FONT28);
              if (StereoLevel != 0) tftPrint(-1, "dBμV", 170, 118, ActiveColor, ActiveColorSmooth, FONT28);
              if (StereoLevel != 0) tftPrint(1, String(StereoLevel, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(1, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
              break;

            case 150:
              tftPrint(0, myLanguage[language][16], 155, 78, ActiveColor, ActiveColorSmooth, FONT28);
              if (HighCutLevel != 0) tftPrint(-1, "Hz", 170, 118, ActiveColor, ActiveColorSmooth, FONT28);
              if (HighCutLevel != 0) tftPrint(1, String(HighCutLevel * 100, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(1, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
              break;

            case 170:
              tftPrint(0, myLanguage[language][17], 155, 78, ActiveColor, ActiveColorSmooth, FONT28);
              if (HighCutOffset != 0) tftPrint(-1, "dBμV", 170, 118, ActiveColor, ActiveColorSmooth, FONT28);
              if (HighCutOffset != 0) tftPrint(1, String(HighCutOffset, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(1, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
              break;

            case 190:
              tftPrint(0, myLanguage[language][18], 155, 78, ActiveColor, ActiveColorSmooth, FONT28);
              tftPrint(-1, "dBμV", 155, 118, ActiveColor, ActiveColorSmooth, FONT28);
              tftPrint(1, String(LowLevelSet, DEC), 145, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
              break;

            case 210:
              tftPrint(0, myLanguage[language][19], 155, 78, ActiveColor, ActiveColorSmooth, FONT28);
              tftPrint(-1, "%", 170, 118, ActiveColor, ActiveColorSmooth, FONT28);
              tftPrint(1, String(ContrastSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
              break;
          }
          break;

        case 2:
          switch (menuoption) {
            case 30:
              tftPrint(0, myLanguage[language][40], 155, 78, ActiveColor, ActiveColorSmooth, FONT28);
              tftPrint(0, myLanguage[language][0], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
              break;

            case 50:
              tftPrint(0, myLanguage[language][38], 155, 78, ActiveColor, ActiveColorSmooth, FONT28);
              if (showrdserrors) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
              break;

            case 70:
              tftPrint(0, myLanguage[language][43], 155, 78, ActiveColor, ActiveColorSmooth, FONT28);
              if (softmutefm) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
              break;

            case 90:
              tftPrint(0, myLanguage[language][44], 155, 78, ActiveColor, ActiveColorSmooth, FONT28);
              if (softmuteam) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
              break;

            case 110:
              tftPrint(0, myLanguage[language][45], 155, 78, ActiveColor, ActiveColorSmooth, FONT28);
              if (edgebeep) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
              break;

            case 130:
              tftPrint(0, myLanguage[language][46], 155, 78, ActiveColor, ActiveColorSmooth, FONT28);
              if (region == 0) tftPrint(0, myLanguage[language][47], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
              if (region == 1) tftPrint(0, myLanguage[language][48], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
              break;

            case 150:
              tftPrint(0, myLanguage[language][49], 155, 78, ActiveColor, ActiveColorSmooth, FONT28);
              if (radio.rds.underscore) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
              break;

            case 170:
              tftPrint(0, myLanguage[language][50], 155, 78, ActiveColor, ActiveColorSmooth, FONT28);
              if (USBmode) tftPrint(0, "RDS Spy", 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, "XDRGTK", 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
              break;

            case 190:
              tftPrint(0, myLanguage[language][51], 155, 78, ActiveColor, ActiveColorSmooth, FONT28);
              if (wifi) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
              break;

            case 210:
              tftPrint(0, myLanguage[language][53], 155, 58, ActiveColor, ActiveColorSmooth, FONT28);
              tftPrint(0, "ESP_" + String(ESP_getChipId()), 155, 98, PrimaryColor, PrimaryColorSmooth, FONT28);
              tftPrint(0, myLanguage[language][54], 155, 138, ActiveColor, ActiveColorSmooth, FONT28);
              tftPrint(0, "http://192.168.4.1", 155, 174, PrimaryColor, PrimaryColorSmooth, FONT16);
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
              tftPrint(0, myLanguage[language][58], 155, 78, ActiveColor, ActiveColorSmooth, FONT28);
              tftPrint(0, String(WiFi.localIP()[0]) + "." + String(WiFi.localIP()[1]) + "." + String(WiFi.localIP()[2]) + "." + String(subnetclient, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
              break;

            case 50:
              tftPrint(0, myLanguage[language][59], 155, 78, ActiveColor, ActiveColorSmooth, FONT28);
              if (showSWMIBand) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
              break;

            case 70:
              tftPrint(0, myLanguage[language][60], 155, 78, ActiveColor, ActiveColorSmooth, FONT28);
              if (radio.rds.filter) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
              break;

            case 90:
              tftPrint(0, myLanguage[language][61], 155, 78, ActiveColor, ActiveColorSmooth, FONT28);
              if (radio.rds.pierrors) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
              break;

            case 110:
              tftPrint(0, myLanguage[language][62], 155, 78, ActiveColor, ActiveColorSmooth, FONT28);
              if (showsquelch) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
              break;

            case 130:
              tftPrint(0, myLanguage[language][63], 155, 78, ActiveColor, ActiveColorSmooth, FONT28);
              if (showmodulation) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
              break;

            case 150:
              tftPrint(0, myLanguage[language][64], 155, 78, ActiveColor, ActiveColorSmooth, FONT28);
              if (amnb != 0) tftPrint(-1, "%", 170, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
              if (amnb != 0) tftPrint(1, String(amnb, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(1, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
              break;

            case 170:
              tftPrint(0, myLanguage[language][65], 155, 78, ActiveColor, ActiveColorSmooth, FONT28);
              if (fmnb != 0) tftPrint(-1, "%", 170, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
              if (fmnb != 0) tftPrint(1, String(fmnb, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(1, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
              break;

            case 190:
              tftPrint(0, myLanguage[language][67], 155, 78, ActiveColor, ActiveColorSmooth, FONT28);
              if (audiomode) tftPrint(0, "MPX", 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, "Stereo", 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
              break;

            case 210:
              tftPrint(0, myLanguage[language][68], 155, 78, ActiveColor, ActiveColorSmooth, FONT28);
              if (specialstepOIRT) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
              break;
          }
          break;

        case 4:
          switch (menuoption) {
            case 30:
              tftPrint(0, myLanguage[language][77], 155, 78, ActiveColor, ActiveColorSmooth, FONT28);
              tftPrint(0, CurrentThemeString, 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
              break;

            case 50:
              tftPrint(0, myLanguage[language][71], 155, 38, ActiveColor, ActiveColorSmooth, FONT28);
              tftPrint(0, myLanguage[language][72], 155, 88, ActiveColor, ActiveColorSmooth, FONT28);
              tftPrint(0, "PE5PVB", 155, 68, PrimaryColor, PrimaryColorSmooth, FONT16);
              tftPrint(1, "ohmytime", 145, 118, PrimaryColor, PrimaryColorSmooth, FONT16);
              tftPrint(1, "HyperDX", 145, 133, PrimaryColor, PrimaryColorSmooth, FONT16);
              tftPrint(-1, "MCelliotG", 155, 118, PrimaryColor, PrimaryColorSmooth, FONT16);
              tftPrint(-1, "andimik", 155, 133, PrimaryColor, PrimaryColorSmooth, FONT16);
              tftPrint(1, "DXHR05", 145, 148, PrimaryColor, PrimaryColorSmooth, FONT16);
              tftPrint(1, "NoobishSVK", 145, 163, PrimaryColor, PrimaryColorSmooth, FONT16);
              tftPrint(-1, "yo2ldk", 155, 148, PrimaryColor, PrimaryColorSmooth, FONT16);
              tftPrint(-1, "Justin_Peng(Portable)", 155, 163, PrimaryColor, PrimaryColorSmooth, FONT16);
              tftPrint(0, "github.com/PE5PVB/TEF6686_ESP32", 155, 183, ActiveColor, ActiveColorSmooth, FONT16);
              break;

            case 70:
              tftPrint(0, myLanguage[language][74], 155, 78, ActiveColor, ActiveColorSmooth, FONT28);
              switch (poweroptions) {
                case DEEP_SLEEP: tftPrint(0, myLanguage[language][75], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); break;
                case LCD_OFF: tftPrint(0, myLanguage[language][76], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); break;
                case LCD_BRIGHTNESS_1_PERCENT: tftPrint(0, myLanguage[language][94], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); break;
                case LCD_BRIGHTNESS_A_QUARTER: tftPrint(0, myLanguage[language][95], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); break;
                case LCD_BRIGHTNESS_HALF: tftPrint(0, myLanguage[language][96], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); break;
              }
              poweroptionsold = poweroptions;
              break;

            case 90:
              tftPrint(-1, "KHz", 170, 118, ActiveColor, ActiveColorSmooth, FONT28);
              tftPrint(0, myLanguage[language][90], 155, 78, ActiveColor, ActiveColorSmooth, FONT28);
              if (fmdefaultstepsize) tftPrint(1, String(FREQ_FM_STEP_100K * 10, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(1, String(FREQ_FM_STEP_50K * 10, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
              break;

            case 110:
              tftPrint(0, myLanguage[language][91], 155, 78, ActiveColor, ActiveColorSmooth, FONT28);
              if (screensaverset) tftPrint(-1, myLanguage[language][92], 170, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
              if (!screensaverset) tftPrint(1, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(1, String(screensaverOptions[screensaverset], DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
              break;

            case 130:
              tftPrint(0, myLanguage[language][97], 155, 78, ActiveColor, ActiveColorSmooth, FONT28);
              tftPrint(-1, "dB", 170, 118, ActiveColor, ActiveColorSmooth, FONT28);
              if (AMLevelOffset > 0) tftPrint(1, "+" + String(AMLevelOffset, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(1, String(AMLevelOffset, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
              break;

            case 150:
              tftPrint(0, myLanguage[language][98], 155, 78, ActiveColor, ActiveColorSmooth, FONT28);
              tftPrint(0, unitString[unit], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
              break;

            case 170:
              tftPrint(0, myLanguage[language][99], 155, 78, ActiveColor, ActiveColorSmooth, FONT28);
              if (af) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
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
      if (XDRGTKUSB == true || XDRGTKTCP == true) {
        if (band == BAND_FM) DataPrint("T" + String(frequency * 10)); else DataPrint("T" + String(frequency_AM));
      }
      radio.clearRDS(fullsearchrds);
      change = 0;
      ShowFreq(0);
      store = true;
    } else {
      if (menuopen == false) {
        tft.drawRoundRect(8, menuoption + 3, 302, 21, 5, BackgroundColor);
        menuoption += 20;
        if (menuoption > 210) {
          menupage++;
          if (menupage > menupagestotal) menupage = 1;
          menuoption = 30;
          BuildMenu();
        }
        tft.drawRoundRect(8, menuoption + 3, 302, 21, 5, ActiveColor);
      } else {
        switch (menupage) {
          case 1:
            switch (menuoption) {
              case 30:
                if (VolSet > 0) tftPrint(1, "+" + String(VolSet, DEC), 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(1, String(VolSet, DEC), 155, 118, BackgroundColor, BackgroundColor, FONT28);
                VolSet++;
                if (VolSet > 10) VolSet = 10;
                if (VolSet > 0) tftPrint(1, "+" + String(VolSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(1, String(VolSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                radio.setVolume(VolSet);
                break;

              case 50:
                tftPrint(1, String(ConverterSet, DEC), 155, 118, BackgroundColor, BackgroundColor, FONT28);
                ConverterSet++;
                if (ConverterSet > 2400 || ConverterSet <= 200) {
                  if (ConverterSet == 1) ConverterSet = 200; else ConverterSet = 0;
                }
                if (ConverterSet >= 200) {
                  Wire.beginTransmission(0x12);
                  Wire.write(ConverterSet >> 8);
                  Wire.write(ConverterSet & (0xFF));
                  Wire.endTransmission();
                }
                tftPrint(1, String(ConverterSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                break;

              case 70:
                tftPrint(1, String(LowEdgeSet / 10 + ConverterSet, DEC) + "." + String(LowEdgeSet % 10 + ConverterSet, DEC), 155, 118, BackgroundColor, BackgroundColor, FONT28);
                LowEdgeSet ++;
                if (LowEdgeSet > 1070) LowEdgeSet = 650;
                if (specialstepOIRT) {
                  FindlowStopOIRT();
                  FindhighStopOIRT();
                }
                tftPrint(1, String(LowEdgeSet / 10 + ConverterSet, DEC) + "." + String(LowEdgeSet % 10 + ConverterSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                break;

              case 90:
                tftPrint(1, String(HighEdgeSet / 10 + ConverterSet, DEC) + "." + String(HighEdgeSet % 10 + ConverterSet, DEC), 155, 118, BackgroundColor, BackgroundColor, FONT28);
                HighEdgeSet ++;
                if (HighEdgeSet > 1080) HighEdgeSet = 660;
                if (specialstepOIRT) {
                  FindlowStopOIRT();
                  FindhighStopOIRT();
                }
                tftPrint(1, String(HighEdgeSet / 10 + ConverterSet, DEC) + "." + String(HighEdgeSet % 10 + ConverterSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                break;

              case 110:
                if (LevelOffset > 0) tftPrint(1, "+" + String(LevelOffset, DEC), 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(1, String(LevelOffset, DEC), 155, 118, BackgroundColor, BackgroundColor, FONT28);
                LevelOffset++;
                if (LevelOffset > 15) LevelOffset = -25;
                if (LevelOffset > 0) tftPrint(1, "+" + String(LevelOffset, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(1, String(LevelOffset, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                radio.setOffset(LevelOffset);
                change2 = true;
                break;

              case 130:
                if (StereoLevel != 0) tftPrint(1, String(StereoLevel, DEC), 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(1, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (StereoLevel != 0) tftPrint(-1, "dBμV", 170, 118, BackgroundColor, BackgroundColor, FONT28);
                StereoLevel ++;
                if (StereoLevel > 60 || StereoLevel <= 30) {
                  if (StereoLevel == 1) StereoLevel = 30; else StereoLevel = 0;
                }
                if (StereoLevel != 0) tftPrint(-1, "dBμV", 170, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                if (StereoLevel != 0) tftPrint(1, String(StereoLevel, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(1, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                radio.setStereoLevel(StereoLevel);
                break;

              case 150:
                tftPrint(1, String(HighCutLevel * 100, DEC), 155, 118, BackgroundColor, BackgroundColor, FONT28);
                HighCutLevel ++;
                if (HighCutLevel > 70) HighCutLevel = 15;
                tftPrint(1, String(HighCutLevel * 100, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                radio.setHighCutLevel(HighCutLevel);
                break;

              case 170:
                if (HighCutOffset != 0) tftPrint(-1, "dBμV", 170, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(1, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (HighCutOffset != 0) tftPrint(1, String(HighCutOffset, DEC), 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(1, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, FONT28);
                HighCutOffset ++;
                if (HighCutOffset > 60 || HighCutOffset <= 20) {
                  if (HighCutOffset == 1) HighCutOffset = 20; else HighCutOffset = 0;
                }
                if (HighCutOffset != 0) tftPrint(-1, "dBμV", 170, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(1, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                if (HighCutOffset != 0) tftPrint(1, String(HighCutOffset, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(1, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                radio.setHighCutOffset(HighCutOffset);
                break;

              case 190:
                tftPrint(1, String(LowLevelSet, DEC), 145, 118, BackgroundColor, BackgroundColor, FONT28);
                LowLevelSet++;
                if (LowLevelSet > 30) LowLevelSet = -15;
                tftPrint(1, String(LowLevelSet, DEC), 145, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                break;

              case 210:
                tftPrint(1, String(ContrastSet, DEC), 155, 118, BackgroundColor, BackgroundColor, FONT28);
                ContrastSet ++;
                if (ContrastSet > 100) ContrastSet = 1;
                tftPrint(1, String(ContrastSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                analogWrite(CONTRASTPIN, ContrastSet * 2 + 27);
                break;
            }
            break;

          case 2:
            switch (menuoption) {
              case 30:
                tftPrint(0, myLanguage[language][0], 155, 118, BackgroundColor, BackgroundColor, FONT28);
                language ++;
                if (language == (sizeof (myLanguage) / sizeof (myLanguage[0]))) language = 0;
                tftPrint(0, myLanguage[language][0], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                break;

              case 50:
                if (showrdserrors) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (showrdserrors) showrdserrors = false; else showrdserrors = true;
                if (showrdserrors) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                break;

              case 70:
                if (softmutefm) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (softmutefm) softmutefm = false; else softmutefm = true;
                if (softmutefm) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                radio.setSoftmuteFM(softmutefm);
                break;

              case 90:
                if (softmuteam) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (softmuteam) softmuteam = false; else softmuteam = true;
                if (softmuteam) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                radio.setSoftmuteAM(softmuteam);
                break;

              case 110:
                if (edgebeep) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (edgebeep) edgebeep = false; else edgebeep = true;
                if (edgebeep) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                break;

              case 130:
                if (region == 0) tftPrint(0, myLanguage[language][47], 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (region == 1) tftPrint(0, myLanguage[language][48], 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (region == 0) region = 1; else region = 0;
                if (region == 0) tftPrint(0, myLanguage[language][47], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                if (region == 1) tftPrint(0, myLanguage[language][48], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                regionold = region;
                if (region == 0) radio.setDeemphasis(1);
                if (region == 1) radio.setDeemphasis(2);
                radio.rds.region = region;
                break;

              case 150:
                if (radio.rds.underscore) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (radio.rds.underscore) radio.rds.underscore = false; else radio.rds.underscore = true;
                if (radio.rds.underscore) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                break;

              case 170:
                if (USBmode) tftPrint(0, "RDS Spy", 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(0, "XDRGTK", 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (USBmode) USBmode = false; else USBmode = true;
                if (USBmode) tftPrint(0, "RDS Spy", 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, "XDRGTK", 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                break;

              case 190:
                if (wifi) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (wifi) wifi = false; else wifi = true;
                if (wifi) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                break;
            }
            break;

          case 3:
            switch (menuoption) {
              case 30:
                tftPrint(0, String(WiFi.localIP()[0]) + "." + String(WiFi.localIP()[1]) + "." + String(WiFi.localIP()[2]) + "." + String(subnetclient, DEC), 155, 118, BackgroundColor, BackgroundColor, FONT28);
                subnetclient ++;
                if (subnetclient > 254) subnetclient = 1;
                tftPrint(0, String(WiFi.localIP()[0]) + "." + String(WiFi.localIP()[1]) + "." + String(WiFi.localIP()[2]) + "." + String(subnetclient, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                break;

              case 50:
                if (showSWMIBand) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (showSWMIBand) showSWMIBand = false; else showSWMIBand = true;
                if (showSWMIBand) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                break;

              case 70:
                if (radio.rds.filter) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (radio.rds.filter) radio.rds.filter = false; else radio.rds.filter = true;
                if (radio.rds.filter) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                break;

              case 90:
                if (radio.rds.pierrors) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (radio.rds.pierrors) radio.rds.pierrors = false; else radio.rds.pierrors = true;
                if (radio.rds.pierrors) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                break;

              case 110:
                if (showsquelch) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (showsquelch) showsquelch = false; else showsquelch = true;
                if (showsquelch) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                break;

              case 130:
                if (showmodulation) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (showmodulation) showmodulation = false; else showmodulation = true;
                if (showmodulation) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                break;

              case 150:
                if (amnb != 0) tftPrint(1, String(amnb, DEC), 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(1, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (amnb != 0) tftPrint(-1, "%", 170, 118, BackgroundColor, BackgroundColor, FONT28);
                amnb ++;
                if (amnb > 150 || amnb <= 50) {
                  if (amnb == 1) amnb = 50; else amnb = 0;
                }
                if (amnb != 0) tftPrint(1, String(amnb, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(1, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                if (amnb != 0) tftPrint(-1, "%", 170, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                radio.setAMNoiseBlanker(amnb);
                break;

              case 170:
                if (fmnb != 0) tftPrint(1, String(fmnb, DEC), 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(1, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (fmnb != 0) tftPrint(-1, "%", 170, 118, BackgroundColor, BackgroundColor, FONT28);
                fmnb ++;
                if (fmnb > 150 || fmnb <= 50) {
                  if (fmnb == 1) fmnb = 50; else fmnb = 0;
                }
                if (fmnb != 0) tftPrint(1, String(fmnb, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(1, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                if (fmnb != 0) tftPrint(-1, "%", 170, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                radio.setFMNoiseBlanker(fmnb);
                break;

              case 190:
                if (audiomode) tftPrint(0, "MPX", 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(0, "Stereo", 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (audiomode) audiomode = false; else audiomode = true;
                if (audiomode) tftPrint(0, "MPX", 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, "Stereo", 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                radio.setAudio(audiomode);
                break;

              case 210:
                if (specialstepOIRT) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (specialstepOIRT) {
                  specialstepOIRT = 0;
                } else {
                  specialstepOIRT = 1;
                  FindlowStopOIRT();
                  FindhighStopOIRT();
                }
                if (specialstepOIRT) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                break;
            }
            break;

          case 4:
            switch (menuoption) {
              case 30:
                CurrentTheme ++;
                if (CurrentTheme > 7) CurrentTheme = 0;
                doTheme();
                tft.drawRoundRect(10, 30, 300, 170, 5, ActiveColor);
                tft.fillRoundRect(12, 32, 296, 166, 5, BackgroundColor);
                tftPrint(0, myLanguage[language][77], 155, 78, ActiveColor, ActiveColorSmooth, FONT28);
                tftPrint(0, CurrentThemeString, 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                break;

              case 70:
                switch (poweroptionsold) {
                  case DEEP_SLEEP: tftPrint(0, myLanguage[language][75], 155, 118, BackgroundColor, BackgroundColor, FONT28); break;
                  case LCD_OFF: tftPrint(0, myLanguage[language][76], 155, 118, BackgroundColor, BackgroundColor, FONT28); break;
                  case LCD_BRIGHTNESS_1_PERCENT: tftPrint(0, myLanguage[language][94], 155, 118, BackgroundColor, BackgroundColor, FONT28); break;
                  case LCD_BRIGHTNESS_A_QUARTER: tftPrint(0, myLanguage[language][95], 155, 118, BackgroundColor, BackgroundColor, FONT28); break;
                  case LCD_BRIGHTNESS_HALF: tftPrint(0, myLanguage[language][96], 155, 118, BackgroundColor, BackgroundColor, FONT28); break;
                }

                poweroptions++;
                if (poweroptions > RADIO_POWER_MODE_CNT - 1) poweroptions = 0;

                switch (poweroptions) {
                  case DEEP_SLEEP: tftPrint(0, myLanguage[language][75], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); break;
                  case LCD_OFF: tftPrint(0, myLanguage[language][76], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); break;
                  case LCD_BRIGHTNESS_1_PERCENT: tftPrint(0, myLanguage[language][94], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); break;
                  case LCD_BRIGHTNESS_A_QUARTER: tftPrint(0, myLanguage[language][95], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); break;
                  case LCD_BRIGHTNESS_HALF: tftPrint(0, myLanguage[language][96], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); break;
                }
                poweroptionsold = poweroptions;
                break;

              case 90:
                if (fmdefaultstepsize) tftPrint(1, String(FREQ_FM_STEP_100K * 10, DEC), 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(1, String(FREQ_FM_STEP_50K * 10, DEC), 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (fmdefaultstepsize) fmdefaultstepsize = 0; else fmdefaultstepsize = 1;
                if (fmdefaultstepsize) tftPrint(1, String(FREQ_FM_STEP_100K * 10, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(1, String(FREQ_FM_STEP_50K * 10, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                break;

              case 110:
                if (screensaverset) tftPrint(-1, myLanguage[language][92], 170, 118, BackgroundColor, BackgroundColor, FONT28);
                if (!screensaverset) tftPrint(1, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(1, String(screensaverOptions[screensaverset]), 155, 118, BackgroundColor, BackgroundColor, FONT28);
                screensaverset ++;
                if (screensaverset > sizeof(screensaverOptions) / sizeof(screensaverOptions[0]) - 1) screensaverset = 0;
                if (screensaverset) tftPrint(-1, myLanguage[language][92], 170, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                if (!screensaverset) tftPrint(1, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(1, String(screensaverOptions[screensaverset]), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                break;

              case 130:
                if (AMLevelOffset > 0) tftPrint(1, "+" + String(AMLevelOffset, DEC), 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(1, String(AMLevelOffset, DEC), 155, 118, BackgroundColor, BackgroundColor, FONT28);
                AMLevelOffset++;
                if (AMLevelOffset > 15) AMLevelOffset = -50;
                if (AMLevelOffset > 0) tftPrint(1, "+" + String(AMLevelOffset, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(1, String(AMLevelOffset, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                radio.setAMOffset(AMLevelOffset);
                break;

              case 150:
                tftPrint(0, String(unitString[unit]), 155, 118, BackgroundColor, BackgroundColor, FONT28);
                unit ++;
                if (unit > 2) unit = 0;
                tftPrint(0, String(unitString[unit]), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                break;

              case 170:
                if (af) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (af) af = false; else af = true;
                if (af) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
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
      if (XDRGTKUSB == true || XDRGTKTCP == true) {
        if (band == BAND_FM) DataPrint("T" + String(frequency * 10)); else DataPrint("T" + String(frequency_AM));
      }
      radio.clearRDS(fullsearchrds);
      change = 0;
      ShowFreq(0);
      store = true;
    } else {
      if (menuopen == false) {
        tft.drawRoundRect(8, menuoption + 3, 302, 21, 5, BackgroundColor);
        menuoption -= 20;
        if (menuoption < 30) {
          menupage--;
          if (menupage == 0) menupage = menupagestotal;
          menuoption = 210;
          BuildMenu();
        }
        tft.drawRoundRect(8, menuoption + 3, 302, 21, 5, ActiveColor);
      } else {
        switch (menupage) {
          case 1:
            switch (menuoption) {
              case 30:
                if (VolSet > 0) tftPrint(1, "+" + String(VolSet, DEC), 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(1, String(VolSet, DEC), 155, 118, BackgroundColor, BackgroundColor, FONT28);
                VolSet--;
                if (VolSet < -10) VolSet = -10;
                if (VolSet > 10) VolSet = 10;
                if (VolSet > 0) tftPrint(1, "+" + String(VolSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(1, String(VolSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                radio.setVolume(VolSet);
                break;

              case 50:
                tftPrint(1, String(ConverterSet, DEC), 155, 118, BackgroundColor, BackgroundColor, FONT28);
                ConverterSet--;
                if (ConverterSet < 200 || ConverterSet > 2400) {
                  if (ConverterSet > 2400) ConverterSet = 2400; else ConverterSet = 0;
                }
                if (ConverterSet >= 200) {
                  Wire.beginTransmission(0x12);
                  Wire.write(ConverterSet >> 8);
                  Wire.write(ConverterSet & (0xFF));
                  Wire.endTransmission();
                }
                tftPrint(1, String(ConverterSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                break;

              case 70:
                tftPrint(1, String(LowEdgeSet / 10 + ConverterSet, DEC) + "." + String(LowEdgeSet % 10 + ConverterSet, DEC), 155, 118, BackgroundColor, BackgroundColor, FONT28);
                LowEdgeSet -= 10;
                if (LowEdgeSet < 650) LowEdgeSet = 1079;
                if (specialstepOIRT) {
                  FindlowStopOIRT();
                  FindhighStopOIRT();
                }
                tftPrint(1, String(LowEdgeSet / 10 + ConverterSet, DEC) + "." + String(LowEdgeSet % 10 + ConverterSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                break;

              case 90:
                tftPrint(1, String(HighEdgeSet / 10 + ConverterSet, DEC) + "." + String(HighEdgeSet % 10 + ConverterSet, DEC), 155, 118, BackgroundColor, BackgroundColor, FONT28);
                HighEdgeSet -= 10;
                if (HighEdgeSet < 660) HighEdgeSet = 1080;
                if (specialstepOIRT) {
                  FindlowStopOIRT();
                  FindhighStopOIRT();
                }
                tftPrint(1, String(HighEdgeSet / 10 + ConverterSet, DEC) + "." + String(HighEdgeSet % 10 + ConverterSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);                break;

              case 110:
                if (LevelOffset > 0) tftPrint(1, "+" + String(LevelOffset, DEC), 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(1, String(LevelOffset, DEC), 155, 118, BackgroundColor, BackgroundColor, FONT28);
                LevelOffset--;
                if (LevelOffset < -25) LevelOffset = 15;
                if (LevelOffset > 0) tftPrint(1, "+" + String(LevelOffset, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(1, String(LevelOffset, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);                radio.setOffset(LevelOffset);
                change2 = true;
                break;

              case 130:
                if (StereoLevel != 0) tftPrint(1, String(StereoLevel, DEC), 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(1, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (StereoLevel != 0) tftPrint(-1, "dBμV", 170, 118, BackgroundColor, BackgroundColor, FONT28);
                StereoLevel --;
                if (StereoLevel < 30 || StereoLevel > 60) {
                  if (StereoLevel > 60) StereoLevel = 60; else StereoLevel = 0;
                }
                if (StereoLevel != 0) tftPrint(-1, "dBμV", 170, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                if (StereoLevel != 0) tftPrint(1, String(StereoLevel, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(1, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                radio.setStereoLevel(StereoLevel);
                break;

              case 150:
                tftPrint(1, String(HighCutLevel * 100, DEC), 155, 118, BackgroundColor, BackgroundColor, FONT28);
                HighCutLevel --;
                if (HighCutLevel < 15 || HighCutLevel > 70) HighCutLevel = 70;
                tftPrint(1, String(HighCutLevel * 100, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                radio.setHighCutLevel(HighCutLevel);
                break;

              case 170:
                if (HighCutOffset != 0) tftPrint(-1, "dBμV", 170, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(1, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (HighCutOffset != 0) tftPrint(1, String(HighCutOffset, DEC), 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(1, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, FONT28);
                HighCutOffset --;
                if (HighCutOffset < 20 || HighCutOffset > 60) {
                  if (HighCutOffset > 60) HighCutOffset = 60; else HighCutOffset = 0;
                }
                if (HighCutOffset != 0) tftPrint(-1, "dBμV", 170, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(1, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                if (HighCutOffset != 0) tftPrint(1, String(HighCutOffset, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(1, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                radio.setHighCutOffset(HighCutOffset);
                break;

              case 190:
                tftPrint(1, String(LowLevelSet, DEC), 145, 118, BackgroundColor, BackgroundColor, FONT28);
                LowLevelSet--;
                if (LowLevelSet < -15) LowLevelSet = 30;
                tftPrint(1, String(LowLevelSet, DEC), 145, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                break;


              case 210:
                tftPrint(1, String(ContrastSet, DEC), 155, 118, BackgroundColor, BackgroundColor, FONT28);
                ContrastSet --;
                if (ContrastSet < 1) ContrastSet = 100;
                tftPrint(1, String(ContrastSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                analogWrite(CONTRASTPIN, ContrastSet * 2 + 27);
                break;
            }
            break;

          case 2:
            switch (menuoption) {
              case 30:
                tftPrint(0, myLanguage[language][0], 155, 118, BackgroundColor, BackgroundColor, FONT28);
                language --;
                if (language > (sizeof (myLanguage) / sizeof (myLanguage[0]))) language = (sizeof (myLanguage) / sizeof (myLanguage[0])) - 1;
                tftPrint(0, myLanguage[language][0], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                break;

              case 50:
                if (showrdserrors) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (showrdserrors) showrdserrors = false; else showrdserrors = true;
                if (showrdserrors) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                break;

              case 70:
                if (softmutefm) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (softmutefm) softmutefm = false; else softmutefm = true;
                if (softmutefm) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                radio.setSoftmuteFM(softmutefm);
                break;

              case 90:
                if (softmuteam) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (softmuteam) softmuteam = false; else softmuteam = true;
                if (softmuteam) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                radio.setSoftmuteAM(softmuteam);
                break;

              case 110:
                if (edgebeep) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (edgebeep) edgebeep = false; else edgebeep = true;
                if (edgebeep) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                break;

              case 130:
                if (region == 0) tftPrint(0, myLanguage[language][47], 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (region == 1) tftPrint(0, myLanguage[language][48], 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (region == 0) region = 1; else region = 0;
                if (region == 0) tftPrint(0, myLanguage[language][47], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                if (region == 1) tftPrint(0, myLanguage[language][48], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                regionold = region;
                if (region == 0) radio.setDeemphasis(1);
                if (region == 1) radio.setDeemphasis(2);
                radio.rds.region = region;
                break;

              case 150:
                if (radio.rds.underscore) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (radio.rds.underscore) radio.rds.underscore = false; else radio.rds.underscore = true;
                if (radio.rds.underscore) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                break;

              case 170:
                if (USBmode) tftPrint(0, "RDS Spy", 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(0, "XDRGTK", 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (USBmode) USBmode = false; else USBmode = true;
                if (USBmode) tftPrint(0, "RDS Spy", 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, "XDRGTK", 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                break;

              case 190:
                if (wifi) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (wifi) wifi = false; else wifi = true;
                if (wifi) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                break;
            }
            break;

          case 3:
            switch (menuoption) {
              case 30:
                tftPrint(0, String(WiFi.localIP()[0]) + "." + String(WiFi.localIP()[1]) + "." + String(WiFi.localIP()[2]) + "." + String(subnetclient, DEC), 155, 118, BackgroundColor, BackgroundColor, FONT28);
                subnetclient --;
                if (subnetclient < 1) subnetclient = 254;
                tftPrint(0, String(WiFi.localIP()[0]) + "." + String(WiFi.localIP()[1]) + "." + String(WiFi.localIP()[2]) + "." + String(subnetclient, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                break;

              case 50:
                if (showSWMIBand) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (showSWMIBand) showSWMIBand = false; else showSWMIBand = true;
                if (showSWMIBand) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                break;

              case 70:
                if (radio.rds.filter) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (radio.rds.filter) radio.rds.filter = false; else radio.rds.filter = true;
                if (radio.rds.filter) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                break;

              case 90:
                if (radio.rds.pierrors) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (radio.rds.pierrors) radio.rds.pierrors = false; else radio.rds.pierrors = true;
                if (radio.rds.pierrors) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                break;

              case 110:
                if (showsquelch) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (showsquelch) showsquelch = false; else showsquelch = true;
                if (showsquelch) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                break;

              case 130:
                if (showmodulation) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (showmodulation) showmodulation = false; else showmodulation = true;
                if (showmodulation) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                break;

              case 150:
                if (amnb != 0) tftPrint(1, String(amnb, DEC), 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(1, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (amnb != 0) tftPrint(-1, "%", 170, 118, BackgroundColor, BackgroundColor, FONT28);
                amnb --;
                if (amnb > 150 || amnb <= 50) {
                  if (amnb > 150) amnb = 150; else amnb = 0;
                }
                if (amnb != 0) tftPrint(1, String(amnb, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(1, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                if (amnb != 0) tftPrint(-1, "%", 170, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                radio.setAMNoiseBlanker(amnb);
                break;

              case 170:
                if (fmnb != 0) tftPrint(1, String(fmnb, DEC), 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(1, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (fmnb != 0) tftPrint(-1, "%", 170, 118, BackgroundColor, BackgroundColor, FONT28);
                fmnb --;
                if (fmnb > 150 || fmnb <= 50) {
                  if (fmnb > 150) fmnb = 150; else fmnb = 0;
                }
                if (fmnb != 0) tftPrint(1, String(fmnb, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(1, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                if (fmnb != 0) tftPrint(-1, "%", 170, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                radio.setFMNoiseBlanker(fmnb);
                break;

              case 190:
                if (audiomode) tftPrint(0, "MPX", 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(0, "Stereo", 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (audiomode) audiomode = false; else audiomode = true;
                if (audiomode) tftPrint(0, "MPX", 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, "Stereo", 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                radio.setAudio(audiomode);
                break;
              case 210:
                if (specialstepOIRT) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (specialstepOIRT) {
                  specialstepOIRT = 0;
                } else {
                  specialstepOIRT = 1;
                  FindlowStopOIRT();
                  FindhighStopOIRT();
                }
                if (specialstepOIRT) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                break;
            }
            break;
          case 4:
            switch (menuoption) {
              case 30:
                CurrentTheme --;
                if (CurrentTheme > 7) CurrentTheme = 7;
                doTheme();
                tft.drawRoundRect(10, 30, 300, 170, 5, ActiveColor);
                tft.fillRoundRect(12, 32, 296, 166, 5, BackgroundColor);
                tftPrint(0, myLanguage[language][77], 155, 78, ActiveColor, ActiveColorSmooth, FONT28);
                tftPrint(0, CurrentThemeString, 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                break;

              case 70:
                switch (poweroptionsold) {
                  case DEEP_SLEEP: tftPrint(0, myLanguage[language][75], 155, 118, BackgroundColor, BackgroundColor, FONT28); break;
                  case LCD_OFF: tftPrint(0, myLanguage[language][76], 155, 118, BackgroundColor, BackgroundColor, FONT28); break;
                  case LCD_BRIGHTNESS_1_PERCENT: tftPrint(0, myLanguage[language][94], 155, 118, BackgroundColor, BackgroundColor, FONT28); break;
                  case LCD_BRIGHTNESS_A_QUARTER: tftPrint(0, myLanguage[language][95], 155, 118, BackgroundColor, BackgroundColor, FONT28); break;
                  case LCD_BRIGHTNESS_HALF: tftPrint(0, myLanguage[language][96], 155, 118, BackgroundColor, BackgroundColor, FONT28); break;
                }

                poweroptions--;
                if (poweroptions > RADIO_POWER_MODE_CNT - 1) poweroptions = RADIO_POWER_MODE_CNT - 1;

                switch (poweroptions) {
                  case DEEP_SLEEP: tftPrint(0, myLanguage[language][75], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); break;
                  case LCD_OFF: tftPrint(0, myLanguage[language][76], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); break;
                  case LCD_BRIGHTNESS_1_PERCENT: tftPrint(0, myLanguage[language][94], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); break;
                  case LCD_BRIGHTNESS_A_QUARTER: tftPrint(0, myLanguage[language][95], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); break;
                  case LCD_BRIGHTNESS_HALF: tftPrint(0, myLanguage[language][96], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); break;
                }
                poweroptionsold = poweroptions;
                break;

              case 90:
                if (fmdefaultstepsize) tftPrint(1, String(FREQ_FM_STEP_100K * 10, DEC), 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(1, String(FREQ_FM_STEP_50K * 10, DEC), 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (fmdefaultstepsize) fmdefaultstepsize = 0; else fmdefaultstepsize = 1;
                if (fmdefaultstepsize) tftPrint(1, String(FREQ_FM_STEP_100K * 10, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(1, String(FREQ_FM_STEP_50K * 10, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                break;

              case 110:
                if (screensaverset) tftPrint(-1, myLanguage[language][92], 170, 118, BackgroundColor, BackgroundColor, FONT28);
                if (!screensaverset) tftPrint(1, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(1, String(screensaverOptions[screensaverset]), 155, 118, BackgroundColor, BackgroundColor, FONT28);
                screensaverset --;
                if (screensaverset > sizeof(screensaverOptions) / sizeof(screensaverOptions[0]) - 1) screensaverset = sizeof(screensaverOptions) / sizeof(screensaverOptions[0]) - 1;
                if (screensaverset) tftPrint(-1, myLanguage[language][92], 170, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                if (!screensaverset) tftPrint(1, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(1, String(screensaverOptions[screensaverset]), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                break;

              case 130:
                if (AMLevelOffset > 0) tftPrint(1, "+" + String(AMLevelOffset, DEC), 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(1, String(AMLevelOffset, DEC), 155, 118, BackgroundColor, BackgroundColor, FONT28);
                AMLevelOffset--;
                if (AMLevelOffset < -50) AMLevelOffset = 15;
                if (AMLevelOffset > 0) tftPrint(1, "+" + String(AMLevelOffset, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(1, String(AMLevelOffset, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                radio.setAMOffset(AMLevelOffset);
                break;

              case 150:
                tftPrint(0, String(unitString[unit]), 155, 118, BackgroundColor, BackgroundColor, FONT28);
                unit --;
                if (unit > 2) unit = 2;
                tftPrint(0, String(unitString[unit]), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
                break;

              case 170:
                if (af) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, FONT28);
                if (af) af = false; else af = true;
                if (af) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
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
    if (advancedRDS) tftReplace(-1, String(memoryposold + 1), String(memorypos + 1), 215, 36, SecondaryColor, SecondaryColorSmooth, FONT16); else tftReplace(-1, String(memoryposold + 1), String(memorypos + 1), 80, 32, SecondaryColor, SecondaryColorSmooth, FONT16);
    memoryposold = memorypos;
  } else {
    if (advancedRDS) tftPrint(-1, String(memorypos + 1), 215, 36, BackgroundColor, BackgroundColor, FONT16); else tftPrint(-1, String(memorypos + 1), 80, 32, BackgroundColor, BackgroundColor, FONT16);
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
      if (!RDSstatus && !screenmute) {
        if (advancedRDS) tftPrint(-1, PIold, 244, 75, SecondaryColor, SecondaryColorSmooth, FONT28); else tftPrint(-1, PIold, 244, 190, SecondaryColor, SecondaryColorSmooth, FONT28);
        if (advancedRDS) tftPrint(-1, PSold, 38, 75, SecondaryColor, SecondaryColorSmooth, FONT28); else tftPrint(-1, PSold, 38, 190, SecondaryColor, SecondaryColorSmooth, FONT28);
        if (advancedRDS) tftPrint(-1, PTYold, 38, 109, SecondaryColor, SecondaryColorSmooth, FONT16); else tftPrint(-1, PTYold, 38, 170, SecondaryColor, SecondaryColorSmooth, FONT16);
        if (!advancedRDS) {
          sprite.fillSprite(BackgroundColor);
          sprite.pushSprite(38, 220);
        } else {
          tftPrint(-1, "PTYN N/A", 216, 109, BackgroundColor, BackgroundColor, FONT16);
          tftPrint(-1, String(ptynold), 216, 109, BackgroundColor, BackgroundColor, FONT16);
        }
        dropout = true;
        aftest = true;
        aftimer = millis();
      } else {
        if (dropout == true && PIold.length() != 0) {
          if (advancedRDS) tftPrint(-1, PIold, 244, 75, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(-1, PIold, 244, 190, PrimaryColor, PrimaryColorSmooth, FONT28);
          if (advancedRDS) tftPrint(-1, PSold, 38, 75, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(-1, PSold, 38, 190, PrimaryColor, PrimaryColorSmooth, FONT28);
          if (advancedRDS) tftPrint(-1, PTYold, 38, 109, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(-1, PTYold, 38, 170, PrimaryColor, PrimaryColorSmooth, FONT16);
          if (advancedRDS) {
            tftPrint(-1, "PTYN N/A", 216, 109, BackgroundColor, BackgroundColor, FONT16);
            tftPrint(-1, String(ptynold), 216, 109, BackgroundColor, BackgroundColor, FONT16);
          }
          dropout = false;
        }
      }
    }

    if ((RDSstatus && RDSSPYUSB) || (RDSstatus && RDSSPYTCP)) {
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

    if ((RDSstatus && XDRGTKUSB) || (RDSstatus && XDRGTKTCP)) {
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

      uint8_t erroutput = 0;
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
    if (radio.rds.rdsAerror) tft.fillCircle(86, 41, 5, TFT_RED); else tft.fillCircle(86, 41, 5, TFT_GREEN);
    errorAold = radio.rds.rdsAerror;
  }

  if (radio.rds.rdsBerror != errorBold) {
    if (radio.rds.rdsBerror) tft.fillCircle(124, 41, 5, TFT_RED); else tft.fillCircle(124, 41, 5, TFT_GREEN);
    errorBold = radio.rds.rdsBerror;
  }

  if (radio.rds.rdsCerror != errorCold) {
    if (radio.rds.rdsCerror) tft.fillCircle(162, 41, 5, TFT_RED); else tft.fillCircle(162, 41, 5, TFT_GREEN);
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
    tftPrint(-1, "PTYN N/A", 216, 109, BackgroundColor, BackgroundColor, FONT16);
    tftPrint(-1, String(ptynold), 216, 109, BackgroundColor, BackgroundColor, FONT16);
    if (radio.rds.PTYN.length() > 0) tftPrint(-1, String(ptynold), 216, 109, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(-1, "PTYN N/A", 216, 109, PrimaryColor, PrimaryColorSmooth, FONT16);
    ptynold = radio.rds.PTYN;
  }

  if (licold != radio.rds.LIC) {
    tftPrint(-1, "N/A", 242, 209, BackgroundColor, BackgroundColor, FONT16);
    tftPrint(-1, LIColdString, 242, 209, BackgroundColor, BackgroundColor, FONT16);

    if (radio.rds.LIC > 0 && radio.rds.LIC < 44) {
      if (radio.rds.hasLIC) tftPrint(-1, myLanguages[radio.rds.LIC], 242, 209, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(-1, "N/A", 242, 209, PrimaryColor, PrimaryColorSmooth, FONT16);
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
      if (radio.rds.hasLIC) tftPrint(-1, myLanguages[lic], 242, 209, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(-1, "N/A", 242, 209, PrimaryColor, PrimaryColorSmooth, FONT16);
      LIColdString = myLanguages[lic];
    }
    licold = radio.rds.LIC;
  }

  String pinstring = String(radio.rds.pinDay) + " " + String(radio.rds.pinHour) + ":" + (radio.rds.pinMin < 10 ? "0" : "") + String(radio.rds.pinMin);
  if (pinstringold != pinstring) {
    tftPrint(-1, "N/A", 242, 224, BackgroundColor, BackgroundColor, FONT16);
    tftPrint(-1, pinstringold, 242, 224, BackgroundColor, BackgroundColor, FONT16);

    if (radio.rds.hasPIN) tftPrint(-1, pinstring, 242, 224, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(-1, "N/A", 242, 224, PrimaryColor, PrimaryColorSmooth, FONT16);
    pinstringold = pinstring;
  }

  String afstring;
  if (radio.rds.hasAF) for (byte i = 0; i < radio.af_counter; i++) afstring += String(radio.af[i].frequency / 100) + "." + String((radio.af[i].frequency % 100) / 10) + (radio.af[i].filler ? "(f)" : "") + (i == radio.af_counter - 1 ? " " : " | "); else afstring = myLanguage[language][87];
  if (hasafold != radio.rds.hasAF) {
    if (radio.rds.hasAF) tftPrint(-1, "AF", 50, 51, SecondaryColor, SecondaryColorSmooth, FONT16); else tftPrint(-1, "AF", 50, 51, GreyoutColor, BackgroundColor, FONT16);
    hasafold = radio.rds.hasAF;
  }

  if (afstring.length() < 20) {
    if (afstringold != afstring) {
      xPos2 = 0;
      sprite5.fillSprite(BackgroundColor);
      sprite5.loadFont(FONT16);
      sprite5.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
      sprite5.drawString(afstring, xPos2, 2);
      sprite5.pushSprite(35, 198);
    }
  } else {
    if (millis() - afticker >= 50) {
      if (xPos2 == 0) {
        if (millis() - aftickerhold >= 2000) {
          xPos2 --;
          aftickerhold = millis();
        }
      } else {
        xPos2 --;
        aftickerhold = millis();
      }
      if (xPos2 < -tft.textWidth(afstring) + (charWidth * 16)) xPos2 = 0;
      sprite5.fillSprite(BackgroundColor);
      sprite5.loadFont(FONT16);
      sprite5.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
      sprite5.drawString(afstring, xPos2, 2);
      sprite5.pushSprite(35, 198);
      afticker = millis();
    }
  }
  afstringold = afstring;

  String eonstring;
  if (radio.rds.hasEON) for (byte i = 0; i < radio.eon_counter; i++) eonstring += String(radio.eon[i].picode) + (radio.eon[i].ps.length() > 0 ? String(": " + String(radio.eon[i].ps)) : "") + (radio.eon[i].mappedfreq > 0 ? String(" " + String(radio.eon[i].mappedfreq / 100) + "." + String((radio.eon[i].mappedfreq % 100) / 10))  : "") + (radio.eon[i].mappedfreq2 > 0 ? String(" / " + String(radio.eon[i].mappedfreq2 / 100) + "." + String((radio.eon[i].mappedfreq2 % 100) / 10))  : "") + (radio.eon[i].mappedfreq3 > 0 ? String(" /  " + String(radio.eon[i].mappedfreq3 / 100) + "." + String((radio.eon[i].mappedfreq3 % 100) / 10))  : "") + (i == radio.eon_counter - 1 ? " " : " | "); else eonstring = myLanguage[language][88];
  if (haseonold != radio.rds.hasEON) {
    if (radio.rds.hasEON) tftPrint(-1, "EON", 153, 51, SecondaryColor, SecondaryColorSmooth, FONT16); else tftPrint(-1, "EON", 153, 51, GreyoutColor, BackgroundColor, FONT16);
    haseonold = radio.rds.hasEON;
  }
  if (eonstring.length() < 20) {
    if (eonstringold != eonstring) {
      xPos3 = 0;
      sprite3.fillSprite(BackgroundColor);
      sprite3.loadFont(FONT16);
      sprite3.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
      sprite3.drawString(eonstring, xPos3, 2);
      sprite3.pushSprite(35, 174);
    }
  } else {
    if (millis() - eonticker >= 50) {
      if (xPos3 == 0) {
        if (millis() - eontickerhold >= 2000) {
          xPos3 --;
          eontickerhold = millis();
        }
      } else {
        xPos3 --;
        eontickerhold = millis();
      }
      if (xPos3 < -tft.textWidth(eonstring) + (charWidth * 16)) xPos3 = 0;
      sprite3.fillSprite(BackgroundColor);
      sprite3.loadFont(FONT16);
      sprite3.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
      sprite3.drawString(eonstring, xPos3, 2);
      sprite3.pushSprite(35, 174);
      eonticker = millis();
    }
  }
  eonstringold = eonstring;

  String rtplusstring;
  if (radio.rds.hasRDSplus) rtplusstring = "1) " + String(radio.rds.RTContent1) + " - 2) " + String(radio.rds.RTContent2) + "         "; else rtplusstring = myLanguage[language][89];
  if (hasrtplusold != radio.rds.hasRDSplus) {
    if (radio.rds.hasRDSplus) tftPrint(-1, "RT+", 124, 51, SecondaryColor, SecondaryColorSmooth, FONT16); else tftPrint(-1, "RT+", 124, 51, GreyoutColor, BackgroundColor, FONT16);
    hasrtplusold = radio.rds.hasRDSplus;
  }
  if (rtplusstring.length() < 20) {
    if (rtplusstringold != rtplusstring) {
      xPos4 = 0;
      sprite4.fillSprite(BackgroundColor);
      sprite4.loadFont(FONT16);
      sprite4.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
      sprite4.drawString(rtplusstring, xPos4, 2);
      sprite4.pushSprite(35, 149);
    }
  } else {
    if (millis() - rtplusticker >= 50) {
      if (xPos4 == 0) {
        if (millis() - rtplustickerhold >= 2000) {
          xPos4 --;
          rtplustickerhold = millis();
        }
      } else {
        xPos4 --;
        rtplustickerhold = millis();
      }
      if (xPos4 < -tft.textWidth(rtplusstring) + (charWidth * 16)) xPos4 = 0;
      sprite4.fillSprite(BackgroundColor);
      sprite4.loadFont(FONT16);
      sprite4.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
      sprite4.drawString(rtplusstring, xPos4, 2);
      sprite4.pushSprite(35, 149);
      rtplusticker = millis();
    }
  }
  rtplusstringold = rtplusstring;

  if (TPold != radio.rds.hasTP) {
    if (radio.rds.hasTP == true) tftPrint(-1, "TP", 6, 51, SecondaryColor, SecondaryColorSmooth, FONT16); else tftPrint(-1, "TP", 6, 51, GreyoutColor, BackgroundColor, FONT16);
    TPold = radio.rds.hasTP;
  }

  if (TAold != radio.rds.hasTA) {
    if (radio.rds.hasTA == true) tftPrint(-1, "TA", 28, 51, SecondaryColor, SecondaryColorSmooth, FONT16); else tftPrint(-1, "TA", 28, 51, GreyoutColor, BackgroundColor, FONT16);
    TAold = radio.rds.hasTA;
  }

  if (MSold != radio.rds.MS) {
    switch (radio.rds.MS) {
      case 0:
        tftPrint(-1, "M", 185, 51, GreyoutColor, BackgroundColor, FONT16);
        tftPrint(-1, "S", 198, 51, GreyoutColor, BackgroundColor, FONT16);
        break;

      case 1:
        tftPrint(-1, "M", 185, 51, SecondaryColor, SecondaryColorSmooth, FONT16);
        tftPrint(-1, "S", 198, 51, GreyoutColor, BackgroundColor, FONT16);
        break;

      case 2:
        tftPrint(-1, "M", 185, 51, GreyoutColor, BackgroundColor, FONT16);
        tftPrint(-1, "S", 198, 51, SecondaryColor, SecondaryColorSmooth, FONT16);
        break;
    }
    MSold = radio.rds.MS;
  }

  rds_clock = ((hour() < 10 ? "0" : "") + String(hour()) + ":" + (minute() < 10 ? "0" : "") + String(minute()));
  if (rds_clock != rds_clockold) {
    if (radio.rds.hasCT) {
      tftReplace(1, rds_clockold, rds_clock, 205, 109, SecondaryColor, SecondaryColorSmooth, FONT16);
      tftPrint(-1, "CT", 72, 51, SecondaryColor, SecondaryColorSmooth, FONT16);
    } else {
      tftPrint(1, rds_clock, 205, 109, BackgroundColor, BackgroundColor, FONT16);
      tftPrint(-1, "CT", 72, 51, GreyoutColor, BackgroundColor, FONT16);
    }
    rds_clockold = rds_clock;
  }

  if (rdsblockold != radio.rdsblock) {
    if (rdsblockold < 33) tft.fillCircle((6 * rdsblockold) + 10, 136, 2, TFT_RED);
    if (radio.rdsblock < 33) tft.fillCircle((6 * radio.rdsblock) + 10, 136, 2, TFT_GREEN);
    rdsblockold = radio.rdsblock;
  }

  if (hastmcold != radio.rds.hasTMC) {
    if (radio.rds.hasTMC == true) tftPrint(-1, "TMC", 90, 51, SecondaryColor, SecondaryColorSmooth, FONT16); else tftPrint(-1, "TMC", 90, 51, GreyoutColor, BackgroundColor, FONT16);
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
      tftPrint(-1, "N/A", 242, 194, BackgroundColor, BackgroundColor, FONT16);
      tftPrint(-1, ECColdtxt, 242, 194, BackgroundColor, BackgroundColor, FONT16);
      if (radio.rds.hasECC) tftPrint(-1, ECC, 242, 194, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(-1, "N/A", 242, 194, PrimaryColor, PrimaryColorSmooth, FONT16);
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
    if (advancedRDS) {
      tftReplace(-1, PIold, radio.rds.picode, 244, 75, PrimaryColor, PrimaryColorSmooth, FONT28);
    } else if (afscreen) {
      tftReplace(-1, PIold, radio.rds.picode, 30, 201, SecondaryColor, SecondaryColorSmooth, FONT16);
    } else {
      tftReplace(-1, PIold, radio.rds.picode, 244, 190, PrimaryColor, PrimaryColorSmooth, FONT28);
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
    if (advancedRDS) tftReplace(-1, PTYold, radio.rds.stationType, 38, 109, PrimaryColor, PrimaryColorSmooth, FONT16); else tftReplace(-1, PTYold, radio.rds.stationType, 38, 170, PrimaryColor, PrimaryColorSmooth, FONT16);
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
    if (advancedRDS) {
      tftReplace(-1, PSold, radio.rds.stationName, 38, 75, PrimaryColor, PrimaryColorSmooth, FONT28);
    } else if (afscreen) {
      tftReplace(0, PSold, radio.rds.stationName, 160, 201, SecondaryColor, SecondaryColorSmooth, FONT16);
    } else {
      tftReplace(-1, PSold, radio.rds.stationName, 38, 190, PrimaryColor, PrimaryColorSmooth, FONT28);
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
    if (advancedRDS && radio.rds.stationText.length() < 20) {
      xPos = 0;
      sprite2.fillSprite(BackgroundColor);
      sprite2.loadFont(FONT16);
      sprite2.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
      sprite2.drawString(radio.rds.stationText + " " + radio.rds.stationText32, xPos, 2);
      sprite2.pushSprite(35, 220);
    } else if (!advancedRDS && radio.rds.stationText.length() < 29) {
      if (RTold != radio.rds.stationText + " " + radio.rds.stationText32) {
        xPos = 0;
        sprite.fillSprite(BackgroundColor);
        sprite.loadFont(FONT16);
        sprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
        sprite.drawString(radio.rds.stationText + " " + radio.rds.stationText32, xPos, 2);
        sprite.pushSprite(38, 220);
      }
    } else {
      if (millis() - rtticker >= 50) {
        if (xPos == 0) {
          if (millis() - rttickerhold >= 2000) {
            xPos --;
            rttickerhold = millis();
          }
        } else {
          xPos --;
          rttickerhold = millis();
        }
        if (advancedRDS) {
          if (xPos < -tft.textWidth(radio.rds.stationText + " " + radio.rds.stationText32) + (charWidth * 16)) xPos = 0;
          sprite2.fillSprite(BackgroundColor);
          sprite2.loadFont(FONT16);
          sprite2.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          sprite2.drawString(radio.rds.stationText + " " + radio.rds.stationText32, xPos, 2);
          sprite2.pushSprite(35, 220);
        } else {
          if (xPos < -tft.textWidth(radio.rds.stationText + " " + radio.rds.stationText32) + (charWidth * 26)) xPos = 0;
          sprite.fillSprite(BackgroundColor);
          sprite.loadFont(FONT16);
          sprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          sprite.drawString(radio.rds.stationText + " " + radio.rds.stationText32, xPos, 2);
          sprite.pushSprite(38, 220);
        }
        rtticker = millis();
        cleanup = true;
      }
    }
  } else if (cleanup == true) {
    sprite.fillSprite(BackgroundColor);
    sprite2.fillSprite(BackgroundColor);
    if (advancedRDS) sprite2.pushSprite(35, 220); else sprite.pushSprite(38, 220);
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
  RTold = radio.rds.stationText + " " + radio.rds.stationText32;
}

void BuildMenu() {
  advancedRDS = false;
  tft.fillScreen(BackgroundColor);
  tft.drawRect(0, 0, 320, 240, FrameColor);
  tft.drawLine(0, 23, 320, 23, FrameColor);
  tftPrint(-1, myLanguage[language][41], 10, 7, PrimaryColor, PrimaryColorSmooth, FONT16);
  tftPrint(1, String(menupage) + "/" + String(menupagestotal), 305, 7, ActiveColor, ActiveColorSmooth, FONT16);
  tft.drawRoundRect(8, menuoption + 3, 302, 21, 5, ActiveColor);
  switch (menupage) {
    case 1:
      tftPrint(1, "dB", 305, 36, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(1, "MHz", 305, 56, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(1, "MHz", 305, 76, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(1, "MHz", 305, 96, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(1, "dB", 305, 116, ActiveColor, ActiveColorSmooth, FONT16);
      if (StereoLevel != 0) tftPrint(1, "dBμV", 305, 136, ActiveColor, ActiveColorSmooth, FONT16);
      if (HighCutLevel != 0) tftPrint(1, "Hz", 305, 156, ActiveColor, ActiveColorSmooth, FONT16);
      if (HighCutOffset != 0) tftPrint(1, "dBμV", 305, 176, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(1, "dBμV", 305, 196, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(1, "%", 305, 216, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][20], 14, 36, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][21], 14, 56, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][22], 14, 76, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][23], 14, 96, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][24], 14, 116, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][25], 14, 136, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][26], 14, 156, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][27], 14, 176, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][28], 14, 196, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][29], 14, 216, ActiveColor, ActiveColorSmooth, FONT16);

      if (VolSet > 0) tftPrint(1, "+" + String(VolSet, DEC), 265, 36, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, String(VolSet, DEC), 265, 36, PrimaryColor, PrimaryColorSmooth, FONT16);
      tftPrint(1, String(ConverterSet, DEC), 265, 56, PrimaryColor, PrimaryColorSmooth, FONT16);
      tftPrint(1, String(LowEdgeSet / 10 + ConverterSet, DEC) + "." + String(LowEdgeSet % 10 + ConverterSet, DEC), 265, 76, PrimaryColor, PrimaryColorSmooth, FONT16);
      tftPrint(1, String(HighEdgeSet / 10 + ConverterSet, DEC) + "." + String(HighEdgeSet % 10 + ConverterSet, DEC), 265, 96, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (LevelOffset > 0) tftPrint(1, "+" + String(LevelOffset, DEC), 265, 116, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, String(LevelOffset, DEC), 265, 116, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (StereoLevel != 0) tftPrint(1, String(StereoLevel, DEC), 265, 136, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 265, 136, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (HighCutLevel != 0) tftPrint(1, String(HighCutLevel * 100, DEC), 265, 156, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 265, 156, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (HighCutOffset != 0) tftPrint(1, String(HighCutOffset, DEC), 265, 176, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 265, 176, PrimaryColor, PrimaryColorSmooth, FONT16);
      tftPrint(1, String(LowLevelSet, DEC), 265, 196, PrimaryColor, PrimaryColorSmooth, FONT16);
      tftPrint(1, String(ContrastSet, DEC), 265, 216, PrimaryColor, PrimaryColorSmooth, FONT16);
      break;

    case 2:
      tftPrint(-1, myLanguage[language][39], 14, 36, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][38], 14, 56, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][43], 14, 76, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][44], 14, 96, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][45], 14, 116, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][46], 14, 136, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][49], 14, 156, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][50], 14, 176, ActiveColor, ActiveColorSmooth, FONT16);
      if (wifi) tftPrint(-1, String(myLanguage[language][51]) + " IP: " + String(WiFi.localIP().toString()), 14, 196, ActiveColor, ActiveColorSmooth, FONT16); else tftPrint(-1, myLanguage[language][51], 14, 196, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][52], 14, 216, ActiveColor, ActiveColorSmooth, FONT16);

      tftPrint(1, myLanguage[language][0], 305, 36, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (showrdserrors) tftPrint(1, myLanguage[language][42], 305, 56, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 305, 56, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (softmutefm) tftPrint(1, myLanguage[language][42], 305, 76, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 305, 76, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (softmuteam) tftPrint(1, myLanguage[language][42], 305, 96, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 305, 96, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (edgebeep) tftPrint(1, myLanguage[language][42], 305, 116, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 305, 116, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (region == 0) tftPrint(1, myLanguage[language][47], 305, 136, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (region == 1) tftPrint(1, myLanguage[language][48], 305, 136, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (radio.rds.underscore) tftPrint(1, myLanguage[language][42], 305, 156, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 305, 156, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (USBmode) tftPrint(1, "RDS Spy", 305, 176, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, "XDRGTK", 305, 176, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (wifi) tftPrint(1, myLanguage[language][42], 305, 196, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 305, 196, PrimaryColor, PrimaryColorSmooth, FONT16);
      tftPrint(1, ">", 305, 216, PrimaryColor, PrimaryColorSmooth, FONT16);
      break;

    case 3:
      tftPrint(-1, myLanguage[language][58], 14, 36, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][59], 14, 56, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][60], 14, 76, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][61], 14, 96, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][62], 14, 116, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][63], 14, 136, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][64], 14, 156, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][65], 14, 176, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][67], 14, 196, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][68], 14, 216, ActiveColor, ActiveColorSmooth, FONT16);

      if (amnb != 0) tftPrint(1, "%", 305, 156, ActiveColor, ActiveColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 305, 156, ActiveColor, ActiveColorSmooth, FONT16);
      if (fmnb != 0) tftPrint(1, "%", 305, 176, ActiveColor, ActiveColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 305, 176, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(1, String(WiFi.localIP()[0]) + "." + String(WiFi.localIP()[1]) + "." + String(WiFi.localIP()[2]) + "." + String(subnetclient, DEC), 305, 36, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (showSWMIBand) tftPrint(1, myLanguage[language][42], 305, 56, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 305, 56, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (radio.rds.filter) tftPrint(1, myLanguage[language][42], 305, 76, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 305, 76, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (radio.rds.pierrors) tftPrint(1, myLanguage[language][42], 305, 96, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 305, 96, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (showsquelch) tftPrint(1, myLanguage[language][42], 305, 116, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 305, 116, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (showmodulation) tftPrint(1, myLanguage[language][42], 305, 136, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 305, 136, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (amnb != 0) tftPrint(1, String(amnb, DEC), 265, 156, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 305, 156, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (fmnb != 0) tftPrint(1, String(fmnb, DEC), 265, 176, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 305, 176, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (audiomode) tftPrint(1, "MPX", 305, 196, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, "Stereo", 305, 196, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (specialstepOIRT) tftPrint(1, myLanguage[language][42], 305, 216, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 305, 216, PrimaryColor, PrimaryColorSmooth, FONT16);
      break;

    case 4:
      tftPrint(-1, myLanguage[language][77], 14, 36, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][70], 14, 56, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][74], 14, 76, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][90], 14, 96, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][91], 14, 116, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][97], 14, 136, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][98], 14, 156, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][99], 14, 176, ActiveColor, ActiveColorSmooth, FONT16);

      tftPrint(1, "KHz", 305, 96, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(1, "dB", 305, 136, ActiveColor, ActiveColorSmooth, FONT16);
      if (screensaverset) tftPrint(1, myLanguage[language][92], 305, 116, ActiveColor, ActiveColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 305, 116, PrimaryColor, PrimaryColorSmooth, FONT16);
      tftPrint(1, CurrentThemeString, 305, 36, PrimaryColor, PrimaryColorSmooth, FONT16);

      switch (poweroptions) {
        case DEEP_SLEEP: tftPrint(1, myLanguage[language][75], 305, 76, PrimaryColor, PrimaryColorSmooth, FONT16); break;
        case LCD_OFF: tftPrint(1, myLanguage[language][76], 305, 76, PrimaryColor, PrimaryColorSmooth, FONT16); break;
        case LCD_BRIGHTNESS_1_PERCENT: tftPrint(1, myLanguage[language][94], 305, 76, PrimaryColor, PrimaryColorSmooth, FONT16); break;
        case LCD_BRIGHTNESS_A_QUARTER: tftPrint(1, myLanguage[language][95], 305, 76, PrimaryColor, PrimaryColorSmooth, FONT16); break;
        case LCD_BRIGHTNESS_HALF: tftPrint(1, myLanguage[language][96], 305, 76, PrimaryColor, PrimaryColorSmooth, FONT16); break;
      }

      if (fmdefaultstepsize) tftPrint(1, String(FREQ_FM_STEP_100K * 10, DEC), 265, 96, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, String(FREQ_FM_STEP_50K * 10, DEC), 265, 96, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (screensaverset) tftPrint(1, String(screensaverOptions[screensaverset], DEC), 265, 116, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 305, 116, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (AMLevelOffset > 0) tftPrint(1, "+" + String(AMLevelOffset, DEC), 265, 136, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, String(AMLevelOffset, DEC), 265, 136, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (af) tftPrint(1, myLanguage[language][42], 305, 176, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 305, 176, PrimaryColor, PrimaryColorSmooth, FONT16);
      tftPrint(1, unitString[unit], 305, 156, PrimaryColor, PrimaryColorSmooth, FONT16);
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
  if (radio.rds.hasAF) {
    if (hasafold == false) {
      tftPrint(-1, myLanguage[language][87], 6, 54, BackgroundColor, BackgroundColor, FONT16);
      hasafold = true;
    }

    if (radio.af_counter > 30) {
      if (!afpage) {
        afpage = true;
        afpagenr = 1;
      }
    } else {
      afpagenr = 0;
    }

    if (af_counterold != radio.af_counter) {
      tft.fillRect(2, 48, 166, 150, BackgroundColor);
      for (byte i = 0; i < radio.af_counter; i++) {
        byte x = i - (afpagenr == 2 ? 30 : 0);
        if (radio.af[i].checked) {
          tftPrint(1, (radio.af[i].filler ? "f " : "") + String(radio.af[i].frequency / 100) + "." + String((radio.af[i].frequency % 100) / 10), 50 + (x > 9 ? 54 : 0) + (x > 19 ? 54 : 0), 48 + (15 * x) - (x > 9 ? 150 : 0) - (x > 19 ? 150 : 0), InsignificantColor, InsignificantColorSmooth, FONT16);
        } else if (!radio.af[i].afvalid) {
          tftPrint(1, (radio.af[i].filler ? "f " : "") + String(radio.af[i].frequency / 100) + "." + String((radio.af[i].frequency % 100) / 10), 50 + (x > 9 ? 54 : 0) + (x > 19 ? 54 : 0), 48 + (15 * x) - (x > 9 ? 150 : 0) - (x > 19 ? 150 : 0), SignificantColor, SignificantColorSmooth, FONT16);
        } else {
          tftPrint(1, (radio.af[i].filler ? "f " : "") + String(radio.af[i].frequency / 100) + "." + String((radio.af[i].frequency % 100) / 10), 50 + (x > 9 ? 54 : 0) + (x > 19 ? 54 : 0), 48 + (15 * x) - (x > 9 ? 150 : 0) - (x > 19 ? 150 : 0), PrimaryColor, PrimaryColorSmooth, FONT16);
        }
        if (i == 29  + (afpagenr == 2 ? 30 : 0)) i = 254;
      }

      if (radio.af_counter > 10 + (afpagenr == 2 ? 30 : 0)) tft.drawLine(59, 54, 59, 191, SecondaryColor);
      if (radio.af_counter > 20 + (afpagenr == 2 ? 30 : 0)) tft.drawLine(113, 54, 113, 191, SecondaryColor);
      if (afpage == true) tftPrint(1, String(afpagenr) + "/2", 315, 222, SecondaryColor, SecondaryColorSmooth, FONT16);
    }
    af_counterold = radio.af_counter;
  }

  if (radio.rds.hasEON) {
    if (haseonold == false) {
      tftPrint(-1, myLanguage[language][88], 184, 54, BackgroundColor, BackgroundColor, FONT16);
    }
    haseonold = true;
    for (byte i = 0; i < radio.eon_counter; i++) {
      tftPrint(-1, String(radio.eon[i].picode), 170, 48 + (15 * i), PrimaryColor, PrimaryColorSmooth, FONT16);
      if (radio.eon[i].ps.length() > 0) {
        tftPrint(-1, "PS:", 210, 32, ActiveColor, ActiveColorSmooth, FONT16);
        if (radio.eon[i].ps != eonpsold[i]) {
          tftPrint(-1, String(eonpsold[i]), 210, 48 + (15 * i), BackgroundColor, BackgroundColor, FONT16);
          eonpsold[i] = radio.eon[i].ps;
        }
        tftPrint(-1, String(radio.eon[i].ps), 210, 48 + (15 * i), SecondaryColor, SecondaryColorSmooth, FONT16);
      }

      if (radio.eon[i].mappedfreq > 0) {
        tftPrint(1, "FREQ:", 316, 32, ActiveColor, ActiveColorSmooth, FONT16);
        if (radio.eon[i].mappedfreq != mappedfreqold[i]) {
          tftPrint(1, String(mappedfreqold[i] / 100) + "." + String((mappedfreqold[i] % 100) / 10), 316, 48 + (15 * i), BackgroundColor, BackgroundColor, FONT16);
        }
        tftPrint(1, String(radio.eon[i].mappedfreq / 100) + "." + String((radio.eon[i].mappedfreq % 100) / 10), 316, 48 + (15 * i), PrimaryColor, PrimaryColorSmooth, FONT16);
        mappedfreqold[i] = radio.eon[i].mappedfreq;
      }
      if (i == 10) i = 254;
    }
  }
}

void BuildAFScreen() {
  if (!afscreen && RDSstatus) {
    tft.drawRoundRect(20, 30, 274, 170, 5, ActiveColor);
    tft.fillRoundRect(22, 32, 270, 166, 5, BackgroundColor);
    tftPrint(0, myLanguage[language][34], 155, 98, ActiveColor, ActiveColorSmooth, FONT28);
    radio.TestAFEON();
  }
  afscreen = true;
  advancedRDS = false;
  if (theme == 0) {
    tft.invertDisplay(colorinvert);
    tft.fillScreen(BackgroundColor);
    tft.drawRect(0, 0, 320, 240, FrameColor);
    tft.drawLine(0, 30, 320, 30, FrameColor);
    tft.drawLine(0, 199, 320, 199, FrameColor);
    tft.drawLine(0, 218, 320, 218, FrameColor);
    tft.drawLine(168, 30, 168, 199, FrameColor);
    tft.drawLine(108, 30, 108, 0, FrameColor);
    tft.drawLine(137, 30, 137, 0, FrameColor);
    tft.drawLine(174, 30, 174, 0, FrameColor);
    tft.drawLine(268, 30, 268, 0, FrameColor);
    tftPrint(-1, "kHz", 220, 4, ActiveColor, ActiveColorSmooth, FONT28);
    tftPrint(-1, "AF:", 4, 32, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "PI:", 170, 32, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(0, myLanguage[language][93], 160, 222, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, myLanguage[language][88], 184, 54, PrimaryColor, PrimaryColorSmooth, FONT16);
    tftPrint(-1, myLanguage[language][87], 6, 54, PrimaryColor, PrimaryColorSmooth, FONT16);

    for (byte i = 0; i < 20; i++) mappedfreqold[i] = 0;
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
    tft.drawLine(108, 30, 108, 0, FrameColor);
    tft.drawLine(137, 30, 137, 0, FrameColor);
    tft.drawLine(174, 30, 174, 0, FrameColor);
    tft.drawLine(268, 30, 268, 0, FrameColor);
    tft.drawLine(0, 143, 210, 143, FrameColor);
    tft.drawLine(0, 168, 210, 168, FrameColor);
    tft.drawLine(0, 193, 320, 193, FrameColor);
    tft.drawLine(0, 218, 210, 218, FrameColor);
    tft.drawRect(0, 0, 320, 240, FrameColor);

    tftPrint(-1, "ERRORS", 3, 34, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(1, unitString[unit], 310, 51, ActiveColor, ActiveColorSmooth, FONT16);
    if (region == 0) tftPrint(-1, "PI", 216, 82, ActiveColor, ActiveColorSmooth, FONT16);
    if (region == 1) tftPrint(-1, "ID", 216, 82, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "PS", 3, 82, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "PTY", 3, 109, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "RT+", 3, 150, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "AF", 3, 200, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "EON", 3, 175, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "RT", 3, 222, ActiveColor, ActiveColorSmooth, FONT16);

    tftPrint(-1, "A:", 66, 34, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "B:", 104, 34, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "C:", 142, 34, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "D:", 180, 34, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "ECC", 214, 194, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "LIC", 214, 209, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "PIN", 214, 224, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(1, "Dyn. PTY", 300, 132, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(1, "Art. head", 300, 147, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(1, "Compressed", 300, 162, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(1, "Has stereo", 300, 177, ActiveColor, ActiveColorSmooth, FONT16);

    tft.fillCircle(86, 41, 5, TFT_RED);
    tft.fillCircle(124, 41, 5, TFT_RED);
    tft.fillCircle(162, 41, 5, TFT_RED);
    tft.fillCircle(200, 41, 5, TFT_RED);

    tft.fillCircle(310, 139, 5, TFT_RED);
    tft.fillCircle(310, 155, 5, TFT_RED);
    tft.fillCircle(310, 170, 5, TFT_RED);
    tft.fillCircle(310, 185, 5, TFT_RED);

    for (int i = 0; i < 33; i++) tft.fillCircle((6 * i) + 10, 136, 2, GreyoutColor);

    tftPrint(-1, "kHz", 220, 4, ActiveColor, ActiveColorSmooth, FONT28);

    tft.drawCircle(81, 15, 10, GreyoutColor);
    tft.drawCircle(81, 15, 9, GreyoutColor);
    tft.drawCircle(91, 15, 10, GreyoutColor);
    tft.drawCircle(91, 15, 9, GreyoutColor);
    tft.drawBitmap(139, 5, RDSLogo, 35, 22, GreyoutColor);

    if (StereoToggle == false) {
      tft.drawCircle(86, 15, 10, SecondaryColor);
      tft.drawCircle(86, 15, 9, SecondaryColor);
    }

    if (radio.rds.hasCT) tftPrint(1, rds_clockold, 205, 109, SecondaryColor, SecondaryColorSmooth, FONT16);
    tftPrint(-1, "TP", 6, 51, GreyoutColor, BackgroundColor, FONT16);
    tftPrint(-1, "TA", 28, 51, GreyoutColor, BackgroundColor, FONT16);
    tftPrint(-1, "AF", 50, 51, GreyoutColor, BackgroundColor, FONT16);
    tftPrint(-1, "CT", 72, 51, GreyoutColor, BackgroundColor, FONT16);
    tftPrint(-1, "TMC", 90, 51, GreyoutColor, BackgroundColor, FONT16);
    tftPrint(-1, "RT+", 124, 51, GreyoutColor, BackgroundColor, FONT16);
    tftPrint(-1, "EON", 153, 51, GreyoutColor, BackgroundColor, FONT16);
    tftPrint(-1, "M", 185, 51, GreyoutColor, BackgroundColor, FONT16);
    tftPrint(-1, "S", 198, 51, GreyoutColor, BackgroundColor, FONT16);
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
    tft.drawLine(137, 30, 137, 0, FrameColor);
    tft.drawLine(174, 30, 174, 0, FrameColor);
    tft.drawLine(20, 116, 204, 116, TFT_DARKGREY);
    if (!showmodulation) tft.drawLine(20, 146, 204, 146, GreyoutColor); else tft.drawLine(20, 146, 204, 146, TFT_DARKGREY);
    for (byte segments = 0; segments < 94; segments++) {
      if (segments > 54) {
        if (((segments - 53) % 10) == 0) {
          tft.fillRect(16 + (2 * segments), 114, 2, 3, TFT_RED);
          if (!showmodulation) tft.fillRect(16 + (2 * segments), 143, 2, 3, GreyoutColor); else tft.fillRect(16 + (2 * segments), 143, 2, 3, TFT_RED);
        }
      } else {
        if (((segments + 1) % 6) == 0) {
          tft.fillRect(16 + (2 * segments), 114, 2, 3, TFT_GREEN);
          if (!showmodulation) tft.fillRect(16 + (2 * segments), 143, 2, 3, GreyoutColor); else tft.fillRect(16 + (2 * segments), 143, 2, 3, TFT_GREEN);
        }
      }
    }
    if (showsquelch) tftPrint(0, "SQ:", 224, 150, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "S/N", 246, 170, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "dB", 300, 170, ActiveColor, ActiveColorSmooth, FONT16);
    if (region == 0) tftPrint(-1, "PI:", 216, 197, ActiveColor, ActiveColorSmooth, FONT16);
    if (region == 1) tftPrint(-1, "ID:", 216, 197, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "PS:", 6, 197, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "RT:", 6, 222, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "PTY:", 6, 170, ActiveColor, ActiveColorSmooth, FONT16);

    tftPrint(0, "S", 7, 103, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "1", 24, 118, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "3", 48, 118, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "5", 72, 118, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "7", 96, 118, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "9", 120, 118, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "+10", 134, 118, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "+30", 174, 118, ActiveColor, ActiveColorSmooth, FONT16);

    if (!showmodulation) {
      tftPrint(0, "M", 7, 134, GreyoutColor, BackgroundColor, FONT16);
      tftPrint(-1, "10", 27, 148, GreyoutColor, BackgroundColor, FONT16);
      tftPrint(-1, "30", 57, 148, GreyoutColor, BackgroundColor, FONT16);
      tftPrint(-1, "50", 87, 148, GreyoutColor, BackgroundColor, FONT16);
      tftPrint(-1, "70", 117, 148, GreyoutColor, BackgroundColor, FONT16);
      tftPrint(-1, "100", 164, 148, GreyoutColor, BackgroundColor, FONT16);
    } else {
      tftPrint(0, "M", 7, 134, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, "10", 27, 148, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, "30", 57, 148, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, "50", 87, 148, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, "70", 117, 148, ActiveColor, BackgroundColor, FONT16);
      tftPrint(-1, "100", 164, 148, ActiveColor, ActiveColorSmooth, FONT16);
    }

    tftPrint(-1, "kHz", 220, 4, ActiveColor, ActiveColorSmooth, FONT28);
    tftPrint(-1, unitString[unit], 282, 150, ActiveColor, ActiveColorSmooth, FONT16);

    if (band == BAND_FM) tftPrint(-1, "MHz", 258, 76, ActiveColor, ActiveColorSmooth, FONT28); else tftPrint(-1, "kHz", 258, 76, ActiveColor, ActiveColorSmooth, FONT28);

    tft.drawRoundRect(249, 56, 30, 20, 5, GreyoutColor);
    tft.drawRoundRect(287, 56, 30, 20, 5, GreyoutColor);
    tft.drawCircle(81, 15, 10, GreyoutColor);
    tft.drawCircle(81, 15, 9, GreyoutColor);
    tft.drawCircle(91, 15, 10, GreyoutColor);
    tft.drawCircle(91, 15, 9, GreyoutColor);
    tft.drawBitmap(139, 5, RDSLogo, 35, 22, GreyoutColor);
    if (StereoToggle == false) {
      tft.drawCircle(86, 15, 10, SecondaryColor);
      tft.drawCircle(86, 15, 9, SecondaryColor);
    }

    switch (band) {
      case BAND_LW: tftPrint(-1, "LW", 50, 32, SecondaryColor, SecondaryColorSmooth, FONT16); break;
      case BAND_MW: tftPrint(-1, "MW", 50, 32, SecondaryColor, SecondaryColorSmooth, FONT16); break;
      case BAND_SW: tftPrint(-1, "SW", 50, 32, SecondaryColor, SecondaryColorSmooth, FONT16); break;
      case BAND_FM: tftPrint(-1, "FM", 50, 32, SecondaryColor, SecondaryColorSmooth, FONT16); break;
    }
  }
  RDSstatusold = false;
  Stereostatusold = false;
  LowLevelInit = true;
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
  resetFontOnNextCall = true;
  tft.unloadFont();
  if (screenmute == false) {
    if (setupmode == false) {
      if (band != BAND_FM) { // Fix Me :take care of 9K/10K Step
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
        if ((setupmode == false && count.length() != freqoldcount) || mode != 0) {
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
          for (int i = 0; i < 33; i++) tft.fillCircle((6 * i) + 10, 136, 2, GreyoutColor);
          tftReplace(1, String(freqold / 100) + "." + (freqold % 100 < 10 ? "0" : "") + String(freqold % 100) + " MHz", String(freq / 100) + "." + (freq % 100 < 10 ? "0" : "") + String(freq % 100) + " MHz", 310, 36, PrimaryColor, PrimaryColorSmooth, FONT16);
          freqold = freq;
        } else if (afscreen) {
          tftReplace(1, String(freqold / 100) + "." + (freqold % 100 < 10 ? "0" : "") + String(freqold % 100) + " MHz", String(freq / 100) + "." + (freq % 100 < 10 ? "0" : "") + String(freq % 100), 290, 201, SecondaryColor, SecondaryColorSmooth, FONT16);
          freqold = freq;
        } else {
          String count = String(freq / 100, DEC);
          if ((setupmode == false && count.length() != freqoldcount) || mode != 0) {
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
    rtplusstringold = "";
    eonstringold = "";
    afstringold = "";
    rds_clockold = "";

    if (wifi) {
      Udp.beginPacket(remoteip, 9030);
      Udp.print("from=TEF tuner;freq=");
      if (band != BAND_FM) Udp.print(String(frequency_AM) + "000;ClearRDS=1"); else Udp.print(String(frequency) + "0000;ClearRDS=1");
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
          if (SNRold == 0) tftPrint(1, "--", 294, 170, BackgroundColor, BackgroundColor, FONT16); else tftPrint(1, String(SNRold), 294, 170, BackgroundColor, BackgroundColor, FONT16);
          if (tuned == true) {
            if (SNR == 0) tftPrint(1, "--", 294, 170, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, String(SNR), 294, 170, PrimaryColor, PrimaryColorSmooth, FONT16);
            SNRold = SNR;
          } else {
            tftPrint(1, "--", 294, 170, PrimaryColor, PrimaryColorSmooth, FONT16);
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

    int SStatusprint = 0;
    if (unit == 0) SStatusprint = SStatus;
    if (unit == 1) SStatusprint = ((SStatus * 100) + 10875) / 100;
    if (unit == 2) SStatusprint = ((float(SStatus / 10) - 10 * log10(75) - 90) * 10);

    if (SStatusprint > (SStatusold + 3) || SStatusprint < (SStatusold - 3)) {
      if (advancedRDS) {
        tftReplace(1, String(SStatusold / 10) + "." + String(abs(SStatusold % 10)), String(SStatusprint / 10) + "." + String(abs(SStatusprint % 10)), 274, 51, PrimaryColor, PrimaryColorSmooth, FONT16);
      } else {
        if (SStatusold / 10 != SStatusprint / 10) tftReplace(1, String(SStatusold / 10), String(SStatusprint / 10), 288, 110, PrimaryColor, PrimaryColorSmooth, FONT48);
        tftReplace(1, "." + String(abs(SStatusold % 10)), "." + String(abs(SStatusprint % 10)), 310, 105, PrimaryColor, PrimaryColorSmooth, FONT28);

        if (band == BAND_FM) segments = (SStatus + 200) / 10; else segments = (SStatus + 200) / 10;

        tft.fillRect(16, 105, 2 * constrain(segments, 0, 54), 8, TFT_GREEN);
        tft.fillRect(16 + 2 * 54, 105, 2 * (constrain(segments, 54, 94) - 54), 8, TFT_RED);
        tft.fillRect(16 + 2 * constrain(segments, 0, 94), 105, 2 * (94 - constrain(segments, 0, 94)), 8, GreyoutColor);
      }
      SStatusold = SStatusprint;

      if (wifi) {
        Udp.beginPacket(remoteip, 9030);
        Udp.print("from=TEF tuner;RcvLevel=");
        Udp.print(SStatus / 10);
        Udp.endPacket();
      }
    }
  }
}

void ShowRDSLogo(bool RDSstatus) {
  if (screenmute == false) {
    if (RDSstatus != RDSstatusold) {
      if (RDSstatus) tft.drawBitmap(139, 5, RDSLogo, 35, 22, InsignificantColor); else tft.drawBitmap(139, 5, RDSLogo, 35, 22, GreyoutColor);
      RDSstatusold = RDSstatus;
    }
  }
}

void ShowStereoStatus() {
  if (StereoToggle == true) {
    if (band == BAND_FM) Stereostatus = radio.getStereoStatus(); else Stereostatus = 0;
    if (Stereostatus != Stereostatusold) {
      if (Stereostatus == true && screenmute == false) {
        tft.drawSmoothCircle(81, 15, 10, SignificantColor, SignificantColorSmooth);
        tft.drawSmoothCircle(81, 15, 9, SignificantColor, SignificantColorSmooth);
        tft.drawSmoothCircle(91, 15, 10, SignificantColor, SignificantColorSmooth);
        tft.drawSmoothCircle(91, 15, 9, SignificantColor, SignificantColorSmooth);
      } else {
        if (screenmute == false) {
          tft.drawSmoothCircle(81, 15, 10, GreyoutColor, BackgroundColor);
          tft.drawSmoothCircle(81, 15, 9, GreyoutColor, BackgroundColor);
          tft.drawSmoothCircle(91, 15, 10, GreyoutColor, BackgroundColor);
          tft.drawSmoothCircle(91, 15, 9, GreyoutColor, BackgroundColor);
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
    if (BWset == 0) tftReplace(1, String (BWOld, DEC), String (BW, DEC), 218, 4, SecondaryColor, SecondaryColorSmooth, FONT28); else tftReplace(1, String (BWOld, DEC), String (BW, DEC), 218, 4, PrimaryColor, PrimaryColorSmooth, FONT28);
    BWOld = BW;
    BWreset = false;
    if (wifi) {
      Udp.beginPacket(remoteip, 9030);
      Udp.print("from=TEF tuner;Bandwidth=");
      Udp.print(BW * 1000);
      Udp.endPacket();
    }
  }
}

void ShowModLevel() {
  if (showmodulation) {
    int segments;

    if (SQ != false) {
      MStatus = 0;
      MStatusold = 1;
    }
    segments = map(MStatus, 0, 120, 0, 94);

    if (segments > peakholdold) {
      peakholdold = segments;
      peakholdmillis = millis();
    }

    tft.fillRect(16, 135, 2 * constrain(segments, 0, 54), 8, TFT_GREEN);
    tft.fillRect(16 + 2 * 54, 135, 2 * (constrain(segments, 54, 94) - 54), 8, TFT_RED);
    tft.fillRect(16 + 2 * constrain(segments, 0, 94), 135, 2 * (94 - constrain(segments, 0, 94)), 8, GreyoutColor);

    int peakHoldPosition = 16 + 2 * constrain(peakholdold, 0, 94);
    tft.fillRect(peakHoldPosition, 135, 2, 8, (MStatus > 80) ? TFT_RED : PrimaryColor);

    if (millis() - peakholdmillis >= 1000) {
      tft.fillRect(peakHoldPosition, 135, 2, 8, GreyoutColor);
      peakholdold = segments;
      peakholdmillis = millis();
    }
  }
}

void doSquelch() {
  if (XDRGTKUSB == false && XDRGTKTCP == false) {
    Squelch = analogRead(PIN_POT) / 4 - 100;
    if (Squelch > 920) Squelch = 920;
    if (showsquelch && !advancedRDS && !afscreen) {
      if (seek == false && menu == false && Squelch != Squelchold) {
        if (Squelchold == -100) {
          if (Squelch != Squelchold) tftPrint(0, myLanguage[language][33], 224, 170, BackgroundColor, BackgroundColor, FONT16);
        } else if (Squelchold == 920) {
          if (Squelch != Squelchold) tftPrint(0, "ST", 224, 170, BackgroundColor, BackgroundColor, FONT16);
        } else {
          if (Squelch != Squelchold) tftPrint(0, String(Squelchold / 10), 224, 170, BackgroundColor, BackgroundColor, FONT16);
        }
        if (Squelch == -100) {
          if (Squelch != Squelchold) tftPrint(0, myLanguage[language][33], 224, 170, PrimaryColor, PrimaryColorSmooth, FONT16);
        } else if (Squelch == 920) {
          tftPrint(0, "ST", 224, 170, PrimaryColor, PrimaryColorSmooth, FONT16);
        } else {
          if (Squelch != Squelchold) tftPrint(0, String(Squelch / 10), 224, 170, PrimaryColor, PrimaryColorSmooth, FONT16);
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
          if (screenmute == false) tft.drawBitmap(110, 5, Speaker, 26, 22, GreyoutColor);
          SQ = false;
        } else {
          radio.setMute();
          if (screenmute == false) tft.drawBitmap(110, 5, Speaker, 26, 22, PrimaryColor);
          SQ = true;
        }
      } else {
        if (Stereostatus == true) {
          radio.setUnMute();
          if (screenmute == false) tft.drawBitmap(110, 5, Speaker, 26, 22, GreyoutColor);
          SQ = false;
        } else {
          radio.setMute();
          if (screenmute == false) tft.drawBitmap(110, 5, Speaker, 26, 22, PrimaryColor);
          SQ = true;
        }
      }
      if (screenmute == false && showsquelch == true && !advancedRDS && !afscreen) {
        if (Squelch != Squelchold) {
          if (Squelchold == -1) {
            if (Squelch != Squelchold) tftPrint(0, "ST", 224, 170, BackgroundColor, BackgroundColor, FONT16);
          } else if (Squelchold == 0) {
            if (Squelch != Squelchold) tftPrint(0, myLanguage[language][33], 224, 170, BackgroundColor, BackgroundColor, FONT16);
          } else {
            if (Squelch != Squelchold) tftPrint(0, String(Squelchold / 10), 224, 170, BackgroundColor, BackgroundColor, FONT16);
          }
          if (Squelch == -1) {
            if (Squelch != Squelchold) tftPrint(0, "ST", 224, 170, PrimaryColor, PrimaryColorSmooth, FONT16);
          } else if (Squelch == 0) {
            if (Squelch != Squelchold) tftPrint(0, myLanguage[language][33], 224, 170, PrimaryColor, PrimaryColorSmooth, FONT16);
          } else {
            if (Squelch != Squelchold) tftPrint(0, String(Squelch / 10), 224, 170, PrimaryColor, PrimaryColorSmooth, FONT16);
          }
          Squelchold = Squelch;
        }
      }
    }
  } else {
    if (seek == false && Squelch != 920) {
      if (Squelch < SStatus || Squelch == -100 || Squelch == 0) {
        radio.setUnMute();
        if (screenmute == false) tft.drawBitmap(110, 5, Speaker, 26, 22, GreyoutColor);
        SQ = false;
      } else {
        radio.setMute();
        if (screenmute == false) tft.drawBitmap(110, 5, Speaker, 26, 22, PrimaryColor);
        SQ = true;
      }
    } else {
      if (seek == false && Stereostatus == true) {
        radio.setUnMute();
        if (screenmute == false) tft.drawBitmap(110, 5, Speaker, 26, 22, GreyoutColor);
        SQ = false;
      } else {
        radio.setMute();
        if (screenmute == false) tft.drawBitmap(110, 5, Speaker, 26, 22, PrimaryColor);
        SQ = true;
      }
    }
  }
}

void updateBW() {
  if (BWset == 0) {
    if (screenmute == false && advancedRDS == false && afscreen == false) {
      tft.drawRoundRect(248, 35, 70, 20, 5, ActiveColor);
      tftPrint(0, "AUTO BW", 283, 38, ActiveColor, ActiveColorSmooth, FONT16);
    }
    radio.setFMABandw();
  } else {
    if (screenmute == false && advancedRDS == false && afscreen == false) {
      tft.drawRoundRect(247, 35, 70, 20, 5, GreyoutColor);
      tftPrint(0, "AUTO BW", 282, 38, GreyoutColor, BackgroundColor, FONT16);
    }
  }
}

void updateiMS() {
  if (band == BAND_FM) {
    if (iMSset == 0) {
      if (screenmute == false) {
        tft.drawRoundRect(248, 56, 32, 20, 5, ActiveColor);
        tftPrint(0, "iMS", 265, 59, ActiveColor, ActiveColorSmooth, FONT16);
      }
      radio.setiMS(1);
    } else {
      if (screenmute == false) {
        tft.drawRoundRect(248, 56, 32, 20, 5, GreyoutColor);
        tftPrint(0, "iMS", 265, 59, GreyoutColor, BackgroundColor, FONT16);
      }
      radio.setiMS(0);
    }
  }
}

void updateEQ() {
  if (band == BAND_FM) {
    if (EQset == 0) {
      if (screenmute == false) {
        tft.drawRoundRect(286, 56, 32, 20, 5, ActiveColor);
        tftPrint(0, "EQ", 303, 59, ActiveColor, ActiveColorSmooth, FONT16);
      }
      radio.setEQ(1);
    } else {
      if (screenmute == false) {
        tft.drawRoundRect(286, 56, 32, 20, 5, GreyoutColor);
        tftPrint(0, "EQ", 303, 59, GreyoutColor, BackgroundColor, FONT16);
      }
      radio.setEQ(0);
    }
  }
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
      tftReplace(-1, SWMIBandstringold, SWMIBandstring, 50, 51, PrimaryColor, PrimaryColorSmooth, FONT16);
      break;

    case SW_MI_BAND_GAP:
      tftPrint(-1, SWMIBandstringold, 50, 51, BackgroundColor, BackgroundColor, FONT16);
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
  switch (tunemode) {
    case TUNE_MAN:
      if (band == BAND_SW) {
        tft.drawRoundRect(1, 57, 42, 20, 5, GreyoutColor);
        tftPrint(0, "BAND", 22, 60, GreyoutColor, BackgroundColor, FONT16);
      } else {
        tft.drawRoundRect(1, 57, 42, 20, 5, GreyoutColor);
        tftPrint(0, "AUTO", 22, 60, GreyoutColor, BackgroundColor, FONT16);
      }

      tft.drawRoundRect(1, 35, 42, 20, 5, ActiveColor);
      tftPrint(0, "MAN", 22, 38, ActiveColor, ActiveColorSmooth, FONT16);

      tft.drawRoundRect(1, 79, 42, 20, 5, GreyoutColor);
      tftPrint(0, "MEM", 22, 82, GreyoutColor, BackgroundColor, FONT16);
      break;

    case TUNE_AUTO:
      tft.drawRoundRect(1, 57, 42, 20, 5, ActiveColor);
      tftPrint(0, "AUTO", 22, 60, ActiveColor, ActiveColorSmooth, FONT16);

      tft.drawRoundRect(1, 35, 42, 20, 5, GreyoutColor);
      tftPrint(0, "MAN", 22, 38, GreyoutColor, BackgroundColor, FONT16);

      tft.drawRoundRect(1, 79, 42, 20, 5, GreyoutColor);
      tftPrint(0, "MEM", 22, 82, GreyoutColor, BackgroundColor, FONT16);
      break;

    case TUNE_MEM:
      if (band == BAND_SW) {
        tft.drawRoundRect(1, 57, 42, 20, 5, GreyoutColor);
        tftPrint(0, "BAND", 22, 60, GreyoutColor, BackgroundColor, FONT16);
      } else {
        tft.drawRoundRect(1, 57, 42, 20, 5, GreyoutColor);
        tftPrint(0, "AUTO", 22, 60, GreyoutColor, BackgroundColor, FONT16);
      }

      tft.drawRoundRect(1, 35, 42, 20, 5, GreyoutColor);
      tftPrint(0, "MAN", 22, 39, GreyoutColor, BackgroundColor, FONT16);

      if (memorystore == true) {
        tft.drawRoundRect(1, 79, 42, 20, 5, TFT_RED);
        tftPrint(0, "MEM", 22, 82, SignificantColor, SignificantColorSmooth, FONT16);
      } else {
        tft.drawRoundRect(1, 79, 42, 20, 5, ActiveColor);
        tftPrint(0, "MEM", 22, 82, ActiveColor, ActiveColorSmooth, FONT16);
      }
      break;

    case TUNE_MI_BAND:
      tft.drawRoundRect(1, 57, 42, 20, 5, ActiveColor);
      tft.setTextColor(ActiveColor);
      tftPrint(0, "BAND", 22, 60, ActiveColor, ActiveColorSmooth, FONT16);

      tft.drawRoundRect(1, 35, 42, 20, 5, GreyoutColor);
      tftPrint(0, "MAN", 22, 38, GreyoutColor, BackgroundColor, FONT16);

      tft.drawRoundRect(1, 79, 42, 20, 5, GreyoutColor);
      tftPrint(0, "MEM", 22, 82, GreyoutColor, BackgroundColor, FONT16);
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
        if (strcmp(packetBuffer, "from=StationList;freq=?;bandwidth=?") == 0) {
          ShowFreq(0);
          Udp.beginPacket(remoteip, 9030);
          Udp.print("from=TEF tuner;Bandwidth=");
          Udp.print(BW * 1000);
          Udp.endPacket();
        } else {
          int symPos = packet.indexOf("freq=");
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
      if (data_str.length() > 30 && data_str.equals(cryptedpassword))
      {
        radio.setFMABandw();
        if (band != BAND_FM) {
          band = BAND_FM;
          SelectBand();
        }
        XDRGTKTCP = true;
        RemoteClient.print("o1,0\n");
        store = true;
      } else if (RDSSPYTCP == false && XDRGTKTCP == false && data_str.length() < 5 && data_str == ("*D*R?F"))
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
      if (data_str.length() > 1 && data_str == ("*D*R?F")) RDSSPYUSB = true;
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
          doBW();
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
            if (Squelchold == -100) {
              tftPrint(0, myLanguage[language][33], 224, 170, BackgroundColor, BackgroundColor, FONT16);
            } else if (Squelchold > 920) {
              tftPrint(0, "ST", 224, 170, BackgroundColor, BackgroundColor, FONT16);
            } else {
              tftPrint(0, String(Squelchold / 10), 224, 170, BackgroundColor, BackgroundColor, FONT16);
            }
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
          LowLevelSet = EEPROM.readInt(EE_BYTE_LOWLEVELSET);
          softmuteam = EEPROM.readByte(EE_BYTE_SOFTMUTEAM);
          softmutefm = EEPROM.readByte(EE_BYTE_SOFTMUTEFM);
          radio.setSoftmuteFM(softmutefm);
          radio.setSoftmuteAM(softmuteam);
          DataPrint("G00\n");
        }
        if (offsetg == 10) {
          MuteScreen(1);
          LowLevelSet = EEPROM.readInt(EE_BYTE_LOWLEVELSET);
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
          RDSstatus = false;
        }
        store = true;
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
        RDSstatus = false;
        store = true;
        aftest = true;
        aftimer = millis();
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
            tft.drawRoundRect(10, 30, 300, 170, 5, ActiveColor);
            tft.fillRoundRect(12, 32, 296, 166, 5, BackgroundColor);
            tftPrint(0, myLanguage[language][34], 160, 100, ActiveColor, ActiveColorSmooth, FONT28);
          }
          frequencyold = frequency;
          for (freq_scan = scanner_start; freq_scan <= scanner_end; freq_scan += scanner_step) {
            DataPrint(String(freq_scan * 10, DEC));
            DataPrint(" = ");
            if (band == BAND_FM) radio.getStatus(SStatus, USN, WAM, OStatus, BW, MStatus, SNR); else  radio.getStatusAM(SStatus, USN, WAM, OStatus, BW, MStatus, SNR);
            DataPrint(String((radio.CheckSignal(freq_scan) / 10) + 10, DEC));
            DataPrint(", ");
          }
          DataPrint("\n");
          radio.SetFreq(frequencyold);
          BuildDisplay();
          radio.setFMABandw();
          BWset = 0;
        }
        break;

      case 'Y':
        VolSet = atoi(buff + 1);
        if (VolSet == 0) {
          radio.setMute();
          if (screenmute == false) tft.drawBitmap(110, 5, Speaker, 26, 22, PrimaryColor);
          XDRMute = true;
          SQ = true;
        } else {
          radio.setUnMute();
          if (screenmute == false) tft.drawBitmap(110, 5, Speaker, 26, 22, GreyoutColor);
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
        if (screenmute == false) tft.drawBitmap(110, 5, Speaker, 26, 22, GreyoutColor);
        VolSet = EEPROM.readInt(EE_BYTE_VOLSET);
        LowLevelSet = EEPROM.readInt(EE_BYTE_LOWLEVELSET);
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
  unsigned int temp = 0;
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
  if (RDSSPYUSB == true) Serial.print("G:\r\nRESET-------\r\n\r\n");
  if (RDSSPYTCP == true) RemoteClient.print("G:\r\nRESET-------\r\n\r\n");
}

void TuneDown() {
  aftest = true;
  aftimer = millis();
  unsigned int temp = 0;
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
  if (RDSSPYUSB == true) Serial.print("G:\r\nRESET-------\r\n\r\n");
  if (RDSSPYTCP == true) RemoteClient.print("G:\r\nRESET-------\r\n\r\n");
}

void EdgeBeeper() {
  bool x = radio.mute;
  radio.tone(50, -5, 2000);
  if (x) {
    radio.setMute();
    if (screenmute == false) tft.drawBitmap(110, 5, Speaker, 26, 22, PrimaryColor);
  } else {
    radio.setUnMute();
    if (screenmute == false) tft.drawBitmap(110, 5, Speaker, 26, 22, GreyoutColor);
  }
}

void Seek(bool mode) {
  if (band == BAND_FM) {
    radio.setMute();
    if (screenmute == false) tft.drawBitmap(110, 5, Speaker, 26, 22, PrimaryColor);
    if (mode == false) TuneDown(); else TuneUp();
    delay(50);
    ShowFreq(0);
    if (XDRGTKUSB == true || XDRGTKTCP == true) {
      if (band == BAND_FM) DataPrint("T" + String(frequency * 10) + "\n"); else DataPrint("T" + String(frequency_AM) + "\n");
    }
    radio.getStatus(SStatus, USN, WAM, OStatus, BW, MStatus, SNR);

    if ((USN < 200) && (WAM < 230) && (OStatus < 80 && OStatus > -80) && (Squelch < SStatus || Squelch == 920)) {
      seek = false;
      radio.setUnMute();
      if (screenmute == false) tft.drawBitmap(110, 5, Speaker, 26, 22, GreyoutColor);
      store = true;
    } else {
      seek = true;
      if (RDSSPYUSB == true) Serial.print("G:\r\nRESET-------\r\n\r\n");
      if (RDSSPYTCP == true) RemoteClient.print("G:\r\nRESET-------\r\n\r\n");
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
    analogWrite(CONTRASTPIN, ContrastSet * 2 + 27);

    if (TEF == 0) tftPrint(0, myLanguage[language][35], 150, 78, ActiveColor, ActiveColorSmooth, FONT28); else tftPrint(0, myLanguage[language][36] + String(TEF), 150, 78, ActiveColor, ActiveColorSmooth, FONT28);
    tftPrint(0, myLanguage[language][37], 150, 108, ActiveColor, ActiveColorSmooth, FONT28);
    EEPROM.writeByte(EE_BYTE_TEF, TEF);
    EEPROM.commit();
    while (true);
    for (;;);
  }
}

void doTheme() {  // Use this to put your own colors in: http://www.barth-dev.de/online/rgb565-color-picker/
  switch (CurrentTheme) {
    case 0:  // Default PE5PVB theme
      PrimaryColor = 0xFFE0;
      PrimaryColorSmooth = 0x10A0;
      SecondaryColor = 0x867D;
      SecondaryColorSmooth = 0x53F1;
      FrequencyColor = TFT_YELLOW;
      FrameColor = TFT_BLUE;
      GreyoutColor = 0x38E7;
      BackgroundColor = TFT_BLACK;
      ActiveColor = 0xFFFF;
      ActiveColorSmooth = 0x39E7;
      SignificantColor = 0xF800;
      SignificantColorSmooth = 0x7C00;
      InsignificantColor = 0x07E0;
      InsignificantColorSmooth = 0x0140;
      CurrentThemeString = myLanguage[language][78];
      break;
    case 1:  // Cyan theme
      PrimaryColor = 0x0F3F;
      PrimaryColorSmooth = 0x0000;
      SecondaryColor = 0xFFFF;
      SecondaryColorSmooth = 0x0000;
      FrequencyColor = 0x0F3F;
      FrameColor = 0x0248;
      GreyoutColor = 0x4A69;
      BackgroundColor = 0x0000;
      ActiveColor = 0xFFFF;
      ActiveColorSmooth = 0x0000;
      SignificantColor = 0xF800;
      SignificantColorSmooth = 0x0000;
      InsignificantColor = 0x07E0;
      InsignificantColorSmooth = 0x0140;
      CurrentThemeString = myLanguage[language][79];
      break;
    case 2:  // Crimson theme
      PrimaryColor = 0xF8C3;
      PrimaryColorSmooth = 0x0000;
      SecondaryColor = 0xFFFF;
      SecondaryColorSmooth = 0x0000;
      FrequencyColor = 0xF8C3;
      FrameColor = 0x3800;
      GreyoutColor = 0x4A69;
      BackgroundColor = 0x0000;
      ActiveColor = 0xFFFF;
      ActiveColorSmooth = 0x0000;
      SignificantColor = 0xF8C3;
      SignificantColorSmooth = 0x0000;
      InsignificantColor = 0x07E0;
      InsignificantColorSmooth = 0x0140;
      CurrentThemeString = myLanguage[language][80];
      break;
    case 3:  // Monochrome theme
      PrimaryColor = 0xFFFF;
      PrimaryColorSmooth = 0x0000;
      SecondaryColor = 0xFFFF;
      SecondaryColorSmooth = 0x0000;
      FrequencyColor = 0xFFFF;
      FrameColor = 0x2965;
      GreyoutColor = 0x4A69;
      BackgroundColor = 0x0000;
      ActiveColor = 0xFFFF;
      ActiveColorSmooth = 0x0000;
      SignificantColor = 0xFFFF;
      SignificantColorSmooth = 0xFFFF;
      InsignificantColor = 0xFFFF;
      InsignificantColorSmooth = 0xFFFF;
      CurrentThemeString = myLanguage[language][81];
      break;
    case 4:  // Volcano theme
      PrimaryColor = 0xFC00;
      PrimaryColorSmooth = 0xFFFF;
      SecondaryColor = 0xFFFF;
      SecondaryColorSmooth = 0xFFFF;
      FrequencyColor = 0xFC00;
      FrameColor = 0x2965;
      GreyoutColor = 0x5140;
      BackgroundColor = 0x0806;
      ActiveColor = 0xFFFF;
      ActiveColorSmooth = 0x0000;
      SignificantColor = 0xFFFF;
      SignificantColorSmooth = 0x0806;
      InsignificantColor = 0x07E0;
      InsignificantColorSmooth = 0x0140;
      CurrentThemeString = myLanguage[language][82];
      break;
    case 5:  // Dendro theme
      PrimaryColor = TFT_GREEN;
      PrimaryColorSmooth = 0x0000;
      SecondaryColor = TFT_GREEN;
      SecondaryColorSmooth = 0x0000;
      FrequencyColor = TFT_GREEN;
      FrameColor = 0x0200;
      GreyoutColor = 0x4A69;
      BackgroundColor = 0x0000;
      ActiveColor = 0xFFFF;
      ActiveColorSmooth = 0x0000;
      SignificantColor = PrimaryColor;
      SignificantColorSmooth = 0x0000;
      InsignificantColor = 0x07E0;
      InsignificantColorSmooth = 0x0140;
      CurrentThemeString = myLanguage[language][83];
      break;
    case 6:  // Sakura theme
      PrimaryColor = 0xF3D5;
      PrimaryColorSmooth = 0x0000;
      SecondaryColor = 0xF3D5;
      SecondaryColorSmooth = 0x0000;
      FrequencyColor = 0xF3D5;
      FrameColor = 0x3845;
      GreyoutColor = 0x4A69;
      BackgroundColor = 0x0000;
      ActiveColor = 0xFFFF;
      ActiveColorSmooth = 0x0000;
      SignificantColor = 0xFFFF;
      SignificantColorSmooth = 0x0000;
      InsignificantColor = 0x07E0;
      InsignificantColorSmooth = 0x0140;
      CurrentThemeString = myLanguage[language][84];
      break;
    case 7:  // Whiteout theme
      PrimaryColor = 0x0000;
      PrimaryColorSmooth = 0xDFFC;
      SecondaryColor = 0x0000;
      SecondaryColorSmooth = 0xDFFC;
      FrequencyColor = 0x18C3;
      FrameColor = 0x630C;
      GreyoutColor = 0x9492;
      BackgroundColor = 0xDFFC;
      ActiveColor = 0x0000;
      ActiveColorSmooth = 0xDFFC;
      SignificantColor = 0x0000;
      SignificantColorSmooth = 0xDFFC;
      InsignificantColor = 0x07E0;
      InsignificantColorSmooth = 0x0140;
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
  if (!setupmode) {
    tft.drawRoundRect(1, 60, 319, 140, 5, ActiveColor);
    tft.fillRoundRect(3, 62, 315, 136, 5, BackgroundColor);
    tftPrint(0, myLanguage[language][55], 155, 88, ActiveColor, ActiveColorSmooth, FONT28);
  }
  if (wc.autoConnect()) {
    Server.begin();
    Udp.begin(9031);
    remoteip = IPAddress (WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], subnetclient);
    if (!setupmode) tftPrint(0, myLanguage[language][57], 155, 128, InsignificantColor, InsignificantColorSmooth, FONT28);
    wifi = true;
  } else {
    if (!setupmode) tftPrint(0, myLanguage[language][56], 155, 128, SignificantColor, SignificantColorSmooth, FONT28);
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
  EEPROM.writeUInt(EE_UINT16_FREQUENCY_FM, 10000);
  EEPROM.writeInt(EE_BYTE_VOLSET, 0);
  EEPROM.writeUInt(EE_UINT16_CONVERTERSET, 0);
  EEPROM.writeUInt(EE_UINT16_FMLOWEDGESET, 875);
  EEPROM.writeUInt(EE_UINT16_FMHIGHEDGESET, 1080);
  EEPROM.writeByte(EE_BYTE_CONTRASTSET, 50);
  EEPROM.writeByte(EE_BYTE_STEREOLEVEL, 0);
  EEPROM.writeByte(EE_BYTE_HIGHCUTLEVEL, 70);
  EEPROM.writeByte(EE_BYTE_HIGHCUTOFFSET, 0);
  EEPROM.writeInt(EE_BYTE_LEVELOFFSET, 0);
  EEPROM.writeByte(EE_BYTE_EDGEBEEP, 0);
  EEPROM.writeByte(EE_BYTE_SOFTMUTEAM, 0);
  EEPROM.writeByte(EE_BYTE_SOFTMUTEFM, 0);
  EEPROM.writeUInt(EE_UINT16_FREQUENCY_AM, 828);
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
  EEPROM.writeInt(EE_BYTE_LOWLEVELSET, -10);
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
  EEPROM.writeUInt(EE_UINT16_FREQUENCY_LW, 180);
  EEPROM.writeUInt(EE_UINT16_FREQUENCY_MW, 540);
  EEPROM.writeUInt(EE_UINT16_FREQUENCY_SW, 1800);
  EEPROM.writeString(EE_STRING_XDRGTK_KEY, "password");
  EEPROM.writeByte(EE_BYTE_SHOWSQUELCH, 1);
  EEPROM.writeByte(EE_BYTE_SHOWMODULATION, 1);
  EEPROM.writeByte(EE_BYTE_AM_NB, 0);
  EEPROM.writeByte(EE_BYTE_FM_NB, 0);
  EEPROM.writeByte(EE_BYTE_AUDIOMODE, 0);
  EEPROM.writeByte(EE_BYTE_OIRT, 0);
  EEPROM.writeUInt(EE_UINT16_LOWEDGEOIRTSET, 0);
  EEPROM.writeUInt(EE_UINT16_HIGHEDGEOIRTSET, 0);
  EEPROM.writeByte(EE_BYTE_COLORINVERT, 0);
  EEPROM.writeByte(EE_BYTE_POWEROPTIONS, 0);
  EEPROM.writeByte(EE_BYTE_CURRENTTHEME, 0);
  EEPROM.writeByte(EE_BYTE_FMDEFAULTSTEPSIZE, 0);
  EEPROM.writeByte(EE_BYTE_SCREENSAVERSET, 0);
  EEPROM.writeInt(EE_INT16_AMLEVELOFFSET, 0);
  EEPROM.writeByte(EE_BYTE_UNIT, 0);
  EEPROM.writeByte(EE_BYTE_AF, 0);
  EEPROM.writeByte(EE_BYTE_STEREO, 1);
  EEPROM.commit();
}

void tftPrint(int8_t offset, const String & text, int16_t x, int16_t y, int color, int smoothcolor, const uint8_t* font) {
  if (currentFont != font || resetFontOnNextCall) {
    if (currentFont != nullptr) tft.unloadFont();
    tft.loadFont(font);
    currentFont = font;
    resetFontOnNextCall = false;
  }

  tft.setTextColor(color, smoothcolor, false);

  switch (offset) {
    case -1: tft.setTextDatum(TL_DATUM); break;
    case 0: tft.setTextDatum(TC_DATUM); break;
    case 1: tft.setTextDatum(TR_DATUM); break;
  }

  tft.drawString(text, x, y, 1);
}

void tftReplace(int8_t offset, const String & textold, const String & text, int16_t x, int16_t y, int color, int smoothcolor, const uint8_t* font) {
  if (currentFont != font || resetFontOnNextCall) {
    if (currentFont != nullptr) tft.unloadFont();

    tft.loadFont(font);
    currentFont = font;
    resetFontOnNextCall = false;
  }

  tft.setTextColor(BackgroundColor, BackgroundColor, false);

  switch (offset) {
    case -1: tft.setTextDatum(TL_DATUM); break;
    case 0: tft.setTextDatum(TC_DATUM); break;
    case 1: tft.setTextDatum(TR_DATUM); break;
  }

  tft.drawString(textold, x, y);
  tft.setTextColor(color, smoothcolor, false);

  switch (offset) {
    case -1: tft.setTextDatum(TL_DATUM); break;
    case 0: tft.setTextDatum(TC_DATUM); break;
    case 1: tft.setTextDatum(TR_DATUM); break;
  }

  tft.drawString(text, x, y);
}
