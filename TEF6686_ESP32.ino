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
#include "src/FONT16_CHS.h"
#include "src/FONT28.h"
#include "src/FONT28_CHS.h"
#include "src/FONT48DEC.h"
#include "src/TEF6686.h"
#include "src/constants.h"
#include "src/language.h"
#include "src/gui.h"
#include "src/comms.h"
#include "src/rds.h"

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
// #define ARS                 // uncomment for BGR type display (ARS version)
// #define CHINA_PORTABLE      // uncomment for China Portable build (Simplified Chinese)

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
bool rdsreset;
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
byte bandAM;
byte bandFM;
byte bandforbidden;
byte battery;
byte batteryold;
byte batteryoptions;
byte batteryoptionsold;
byte BWset;
#ifdef CHINA_PORTABLE
byte hardwaremodel = PORTABLE_ILI9341;
#else
byte hardwaremodel = BASE_ILI9341;
#endif
byte hardwaremodelold;
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
byte menupagestotal = 5;
byte MSold;
byte optenc;
byte poweroptions;
byte poweroptionsold;
byte rdsblockold;
byte region;
byte regionold;
byte rotarymode;
byte touchrotating;
byte screensaverOptions[5] = {0, 3, 10, 30, 60};
byte screensaverset;
byte showmodulation;
byte showSWMIBand;
byte nowToggleSWMIBand = 0;
byte SNRold;
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
float vPerold;
int ActiveColor;
int ActiveColorSmooth;
int AGC;
int AMLevelOffset;
int BackgroundColor;
int BarSignificantColor;
int BarInsignificantColor;
int BatteryValueColor;
int BatteryValueColorSmooth;
int batupdatetimer;
int BWAutoColor;
int BWAutoColorSmooth;
int BWOld;
int bwupdatetimer;
int charWidth = tft.textWidth("AA");
int DeEmphasis;
int ForceMono;
int FrameColor;
int freqold;
int FrequencyColor;
int GreyoutColor;
int InsignificantColor;
int InsignificantColorSmooth;
int menuoption = 30;
int MStatusold;
int offsetupdatetimer;
int OStatusold;
int peakholdold;
int peakholdtimer;
int PrimaryColor;
int PrimaryColorSmooth;
int RDSColor;
int RDSColorSmooth;
int SignificantColor;
int SignificantColorSmooth;
int StereoColor;
int StereoColorSmooth;
int SquelchShow;
int SquelchShowold;
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
float batteryVold;
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
unsigned int frequency_OIRT;
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
  if (EEPROM.readByte(EE_BYTE_CHECKBYTE) != EE_CHECKBYTE_VALUE) DefaultSettings(hardwaremodel);

  frequency = EEPROM.readUInt(EE_UINT16_FREQUENCY_FM);
  frequency_OIRT = EEPROM.readUInt(EE_UINT16_FREQUENCY_OIRT);
  VolSet = EEPROM.readInt(EE_BYTE_VOLSET);
  ConverterSet = EEPROM.readUInt(EE_UINT16_CONVERTERSET);
  LowEdgeSet = EEPROM.readUInt(EE_UINT16_FMLOWEDGESET);
  HighEdgeSet = EEPROM.readUInt(EE_UINT16_FMHIGHEDGESET);
  ContrastSet = EEPROM.readByte(EE_BYTE_CONTRASTSET);
  StereoLevel = EEPROM.readByte(EE_BYTE_STEREOLEVEL);
  bandFM = EEPROM.readByte(EE_BYTE_BANDFM);
  bandAM = EEPROM.readByte(EE_BYTE_BANDAM);
  HighCutLevel = EEPROM.readByte(EE_BYTE_HIGHCUTLEVEL);
  HighCutOffset = EEPROM.readByte(EE_BYTE_HIGHCUTOFFSET);
  LevelOffset = EEPROM.readByte(EE_BYTE_LEVELOFFSET);
  radio.rds.rtbuffer = EEPROM.readByte(EE_BYTE_RTBUFFER);
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
  touchrotating = EEPROM.readByte(EE_BYTE_TOUCH_ROTATING);
  hardwaremodel = EEPROM.readByte(EE_BYTE_HARDWARE_MODEL);
  poweroptions = EEPROM.readByte(EE_BYTE_POWEROPTIONS);
  CurrentTheme = EEPROM.readByte(EE_BYTE_CURRENTTHEME);
  fmdefaultstepsize = EEPROM.readByte(EE_BYTE_FMDEFAULTSTEPSIZE);
  screensaverset = EEPROM.readByte(EE_BYTE_SCREENSAVERSET);
  AMLevelOffset = EEPROM.readInt(EE_INT16_AMLEVELOFFSET);
  unit = EEPROM.readByte(EE_BYTE_UNIT);
  af = EEPROM.readByte(EE_BYTE_AF);
  StereoToggle = EEPROM.readByte(EE_BYTE_STEREO);
  batteryoptions = EEPROM.readByte(EE_BYTE_BATTERY_OPTIONS);

  LWLowEdgeSet = FREQ_LW_LOW_EDGE_MIN;   // later will read from flash
  LWHighEdgeSet = FREQ_LW_HIGH_EDGE_MAX; // later will read from flash
  MWLowEdgeSet = region == 0 ? FREQ_MW_LOW_EDGE_MIN_9K : FREQ_MW_LOW_EDGE_MIN_10K;      // later will read from flash
  MWHighEdgeSet = region == 0 ? FREQ_MW_HIGH_EDGE_MAX_9K : FREQ_MW_HIGH_EDGE_MAX_10K;   // later will read from flash
  SWLowEdgeSet = FREQ_SW_LOW_EDGE_MIN;
  SWHighEdgeSet = FREQ_SW_HIGH_EDGE_MAX;
  if (LowEdgeOIRTSet < FREQ_FM_OIRT_START || LowEdgeOIRTSet > FREQ_FM_OIRT_END) LowEdgeOIRTSet = FREQ_FM_OIRT_START;
  if (HighEdgeOIRTSet < FREQ_FM_OIRT_START || HighEdgeOIRTSet > FREQ_FM_OIRT_END) HighEdgeOIRTSet = FREQ_FM_OIRT_END;

  LowEdgeOIRTSet = LowEdgeOIRTSet;
  HighEdgeOIRTSet = FREQ_FM_OIRT_END;

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
      if (frequency % 10 != 0) {
        if (fmdefaultstepsize == 1) Round100K(frequency); else Round50K(frequency);
      }
      break;
    case BAND_OIRT:
      if (frequency % FREQ_OIRT_STEP_30K != 0) {
        Round30K(frequency_OIRT);
      }
      break;
    default: break;
  }

  tft.init();
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

  tft.setSwapBytes(true);
  tft.fillScreen(BackgroundColor);

  if (digitalRead(BWBUTTON) == LOW && digitalRead(ROTARY_BUTTON) == HIGH) {
    if (rotarymode == 0) rotarymode = 1; else rotarymode = 0;
    EEPROM.writeByte(EE_BYTE_ROTARYMODE, rotarymode);
    EEPROM.commit();
    analogWrite(CONTRASTPIN, ContrastSet * 2 + 27);
    tftPrint(0, myLanguage[language][1], 155, 85, ActiveColor, ActiveColorSmooth, 28);
    tftPrint(0, myLanguage[language][2], 155, 115, ActiveColor, ActiveColorSmooth, 28);
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
    tftPrint(0, myLanguage[language][3], 155, 85, ActiveColor, ActiveColorSmooth, 28);
    tftPrint(0, myLanguage[language][2], 155, 115, ActiveColor, ActiveColorSmooth, 28);
    while (digitalRead(MODEBUTTON) == LOW) delay(50);
  }

  if (digitalRead(BANDBUTTON) == LOW) {
    analogWrite(SMETERPIN, 511);
    analogWrite(CONTRASTPIN, ContrastSet * 2 + 27);
    tftPrint(0, myLanguage[language][4], 155, 85, ActiveColor, ActiveColorSmooth, 28);
    tftPrint(0, myLanguage[language][5], 155, 115, ActiveColor, ActiveColorSmooth, 28);
    while (digitalRead(BANDBUTTON) == LOW) delay(50);
    analogWrite(SMETERPIN, 0);
  }

  if (digitalRead(ROTARY_BUTTON) == LOW && digitalRead(BWBUTTON) == HIGH) {
    analogWrite(CONTRASTPIN, ContrastSet * 2 + 27);
    if (optenc == 0) {
      optenc = 1;
      tftPrint(0, myLanguage[language][6], 155, 85, ActiveColor, ActiveColorSmooth, 28);
    } else {
      optenc = 0;
      tftPrint(0, myLanguage[language][7], 155, 85, ActiveColor, ActiveColorSmooth, 28);
    }
    EEPROM.writeByte(EE_BYTE_OPTENC, optenc);
    EEPROM.commit();
    tftPrint(0, myLanguage[language][2], 155, 115, ActiveColor, ActiveColorSmooth, 28);
    while (digitalRead(ROTARY_BUTTON) == LOW) delay(50);
  }

  if (digitalRead(ROTARY_BUTTON) == LOW && digitalRead(BWBUTTON) == LOW) {
    analogWrite(CONTRASTPIN, ContrastSet * 2 + 27);
    DefaultSettings(hardwaremodel);
    tftPrint(0, myLanguage[language][66], 155, 85, ActiveColor, ActiveColorSmooth, 28);
    tftPrint(0, myLanguage[language][2], 155, 115, ActiveColor, ActiveColorSmooth, 28);
    while (digitalRead(ROTARY_BUTTON) == LOW && digitalRead(BWBUTTON) == LOW) delay(50);
    ESP.restart();
  }

  tft.fillScreen(BackgroundColor);
  tftPrint(0, myLanguage[language][8], 160, 3, PrimaryColor, PrimaryColorSmooth, 28);
  tftPrint(0, "Software " + String(VERSION), 160, 152, PrimaryColor, PrimaryColorSmooth, 16);

  tft.fillSmoothCircle(160, 90, 60, PrimaryColor, PrimaryColorSmooth);
  tft.fillSmoothCircle(160, 90, 52, BackgroundColor, PrimaryColorSmooth);

  tft.fillRect(120, 230, 16, 6, GreyoutColor);
  tft.fillRect(152, 230, 16, 6, GreyoutColor);
  tft.fillRect(184, 230, 16, 6, GreyoutColor);

  tft.drawBitmap(130, 80, TEFLogo, 59, 23, ActiveColor);

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
    tftPrint(0, "TEF6686 Lithio", 160, 172, ActiveColor, ActiveColorSmooth, 28);
  } else if (lowByte(device) == 1) {
    fullsearchrds = true;
    tft.fillRect(152, 230, 16, 6, PrimaryColor);
    tftPrint(0, "TEF6687 Lithio FMSI", 160, 172, ActiveColor, ActiveColorSmooth, 28);
  } else if (lowByte(device) == 9) {
    fullsearchrds = false;
    tft.fillRect(152, 230, 16, 6, PrimaryColor);
    tftPrint(0, "TEF6688 Lithio DR", 160, 172, ActiveColor, ActiveColorSmooth, 28);
  } else if (lowByte(device) == 3) {
    fullsearchrds = true;
    tft.fillRect(152, 230, 16, 6, PrimaryColor);
    tftPrint(0, "TEF6689 Lithio FMSI DR", 160, 172, ActiveColor, ActiveColorSmooth, 28);
  } else {
    tftPrint(0, myLanguage[language][9], 160, 172, SignificantColor, SignificantColorSmooth, 28);
    tft.fillRect(152, 230, 16, 6, SignificantColor);
    while (true);
    for (;;);
  }
  tftPrint(0, "Patch: v" + String(TEF), 160, 202, ActiveColor, ActiveColorSmooth, 28);

  if (wifi == true) {
    tryWiFi();
    tft.fillRect(184, 230, 16, 6, PrimaryColor);
    delay(2000);
  } else {
    Server.end();
    Udp.stop();
    tft.fillRect(184, 230, 16, 6, SignificantColor);
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
  sprite.loadFont(FONT16);
  sprite2.loadFont(FONT16);
  sprite3.loadFont(FONT16);
  sprite4.loadFont(FONT16);
  sprite5.loadFont(FONT16);
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

    if (!menu && !afscreen) {

      if (af && dropout) {
        frequency = radio.TestAF();
        if (freqold != frequency) {
          ShowFreq(0);
          if (XDRGTKUSB == true || XDRGTKTCP == true) DataPrint("T" + String(frequency * 10));
          store = true;
        }
      }

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
    }

    if (seek == true) Seek(direction);

    if ((SStatus / 10 > LowLevelSet) && LowLevelInit == false && menu == false && band < BAND_GAP) {
      if (screenmute == false && !advancedRDS && !afscreen) {
        if (showmodulation) {
          tftPrint(-1, "10", 27, 144, ActiveColor, ActiveColorSmooth, 16);
          tftPrint(-1, "30", 57, 144, ActiveColor, ActiveColorSmooth, 16);
          tftPrint(-1, "50", 87, 144, ActiveColor, ActiveColorSmooth, 16);
          tftPrint(-1, "70", 117, 144, ActiveColor, ActiveColorSmooth, 16);
          tftPrint(-1, "100", 164, 144, ActiveColor, ActiveColorSmooth, 16);
          tftPrint(0, "M", 7, 128, ActiveColor, ActiveColorSmooth, 16);
          for (byte segments = 0; segments < 94; segments++) {
            if (segments > 54) {
              if (((segments - 53) % 10) == 0) tft.fillRect(16 + (2 * segments), 141, 2, 2, BarSignificantColor);
            } else {
              if (((segments + 1) % 6) == 0) tft.fillRect(16 + (2 * segments), 141, 2, 2, BarInsignificantColor);
            }
          }
        }
        if (region == 0) tftPrint(-1, "PI:", 212, 193, ActiveColor, ActiveColorSmooth, 16);
        if (region == 1) tftPrint(-1, "ID:", 212, 193, ActiveColor, ActiveColorSmooth, 16);
        tftPrint(-1, "PS:", 3, 193, ActiveColor, ActiveColorSmooth, 16);
        tftPrint(-1, "RT:", 3, 221, ActiveColor, ActiveColorSmooth, 16);
        tftPrint(-1, "PTY:", 3, 163, ActiveColor, ActiveColorSmooth, 16);
        if (!showmodulation) tft.drawLine(20, 143, 204, 143, GreyoutColor); else tft.drawLine(20, 143, 204, 143, TFT_DARKGREY);
      }
      LowLevelInit = true;
    }

    if ((SStatus / 10 <= LowLevelSet) && band < BAND_GAP) {
      if (LowLevelInit == true && menu == false) {
        if (screenmute == false && !afscreen && !advancedRDS) {
          for (byte segments = 0; segments < 94; segments++) {
            if (segments > 54) {
              if (((segments - 53) % 10) == 0) tft.fillRect(16 + (2 * segments), 141, 2, 2, GreyoutColor);
            } else {
              if (((segments + 1) % 6) == 0) tft.fillRect(16 + (2 * segments), 141, 2, 2, GreyoutColor);
            }
          }
          if (showmodulation) {
            tftPrint(-1, "10", 27, 144, GreyoutColor, BackgroundColor, 16);
            tftPrint(-1, "30", 57, 144, GreyoutColor, BackgroundColor, 16);
            tftPrint(-1, "50", 87, 144, GreyoutColor, BackgroundColor, 16);
            tftPrint(-1, "70", 117, 144, GreyoutColor, BackgroundColor, 16);
            tftPrint(-1, "100", 164, 144, GreyoutColor, BackgroundColor, 16);
            tftPrint(0, "M", 7, 128, GreyoutColor, BackgroundColor, 16);
            tft.fillRect(16, 133, 188, 6, GreyoutColor);
          }
          if (region == 0) tftPrint(-1, "PI:", 212, 193, GreyoutColor, BackgroundColor, 16);
          if (region == 1) tftPrint(-1, "ID:", 212, 193, GreyoutColor, BackgroundColor, 16);
          tftPrint(-1, "PS:", 3, 193, GreyoutColor, BackgroundColor, 16);
          tftPrint(-1, "RT:", 3, 221, GreyoutColor, BackgroundColor, 16);
          tftPrint(-1, "PTY:", 3, 163, GreyoutColor, BackgroundColor, 16);
          tft.drawLine(20, 143, 204, 143, GreyoutColor);
          tft.drawBitmap(122, 5, RDSLogo, 35, 22, GreyoutColor);
        }
        LowLevelInit = false;
      }

      if (millis() >= lowsignaltimer + 300) {
        lowsignaltimer = millis();
        if (band < BAND_GAP) radio.getStatus(SStatus, USN, WAM, OStatus, BW, MStatus, SNR); else radio.getStatusAM(SStatus, USN, WAM, OStatus, BW, MStatus, SNR);
        if (screenmute == true) readRds();
        if (menu == false) {
          doSquelch();
          GetData();
        }
      }

    } else {
      if (band < BAND_GAP) radio.getStatus(SStatus, USN, WAM, OStatus, BW, MStatus, SNR); else radio.getStatusAM(SStatus, USN, WAM, OStatus, BW, MStatus, SNR);
      if (menu == false) {
        doSquelch();
        readRds();
        GetData();
        if (screenmute == false && afscreen == false && advancedRDS == false) ShowModLevel();
      }
    }

    if (menu == true && menuopen == true && menupage == 1 && menuoption == 110) {
      if (band < BAND_GAP) radio.getStatus(SStatus, USN, WAM, OStatus, BW, MStatus, SNR); else radio.getStatusAM(SStatus, USN, WAM, OStatus, BW, MStatus, SNR);
      if (millis() >= lowsignaltimer + 500 || change2 == true) {
        lowsignaltimer = millis();
        change2 = false;
        if (SStatus > SStatusold || SStatus < SStatusold) {
          if (SStatusold / 10 != SStatus / 10) tftReplace(1, String(SStatusold / 10), String(SStatus / 10), 140, 149, PrimaryColor, PrimaryColorSmooth, 48);
          tftReplace(1, "." + String(abs(SStatusold % 10)), "." + String(abs(SStatus % 10)), 160, 149, PrimaryColor, PrimaryColorSmooth, 28);
          SStatusold = SStatus;
        }
      }
    }

    if (rotary == -1) {
      if (screensavertriggered) {
        if (!touchrotating) {
          rotary = 0;
          WakeToSleep(REVERSE);
        }
      } else {
        KeyUp();
        if (screensaverset && !menu && !screensavertriggered) ScreensaverTimerRestart();
      }
    }
    if (rotary == 1) {
      if (screensavertriggered) {
        if (!touchrotating) {
          rotary = 0;
          WakeToSleep(REVERSE);
        }
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
      EEPROM.writeUInt(EE_UINT16_FREQUENCY_OIRT, frequency_OIRT);
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
    if (rotary == -1) {
      if (!touchrotating) {
        rotary = 0;
        WakeToSleep(REVERSE);
      } else {
        KeyUp();
      }
    }

    if (rotary == 1) {
      if (!touchrotating) {
        rotary = 0;
        WakeToSleep(REVERSE);
      } else {
        KeyDown();
      }
    }
  }
}

void GetData() {
  if (band < BAND_GAP) ShowStereoStatus();
  if (screenmute == false) {
    if (band < BAND_GAP) {
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

void CheckBandForbiddenFM () {
  switch (band) {
    case BAND_FM:
      if (bandFM == FM_BAND_OIRT) bandforbidden = 1;
      else bandforbidden = 0;
      break;
    case BAND_OIRT:
      if (bandFM == FM_BAND_FM) bandforbidden = 1;
      else bandforbidden = 0;
      break;
  }
}

void doBandSelectionFM() {
  if (band > BAND_GAP) return;

  switch (bandFM) {
    case FM_BAND_ALL:
      break;
    case FM_BAND_OIRT:
      if (band == BAND_FM) {
        band = BAND_OIRT;
        if (frequency_OIRT > FREQ_FM_OIRT_END) {
          frequency_OIRT = FREQ_FM_OIRT_START;
          if (edgebeep) EdgeBeeper();
        }
        else if (frequency_OIRT < FREQ_FM_OIRT_START) {
          frequency_OIRT = FREQ_FM_OIRT_END;
          if (edgebeep) EdgeBeeper();
        }
        SelectBand();
      }
      break;
    case FM_BAND_FM:
      if (band == BAND_OIRT) {
        band = BAND_FM;
        if (frequency > HighEdgeSet * 10) {
          frequency = LowEdgeSet * 10;
          if (edgebeep) EdgeBeeper();
        } else if (frequency < LowEdgeSet * 10) {
          frequency = HighEdgeSet * 10;
          if (edgebeep) EdgeBeeper();
        }
        SelectBand();
      }
      break;
  }
}

void ShowBandSelectionFM(bool notglanceview, bool normaldisplay) {

  uint16_t bandFMx, bandFMy;
  int color, colorSmooth;

  if (notglanceview) {
    bandFMx = 155;
    bandFMy = 118;
  } else {
    bandFMx = 310;
    bandFMy = 196;
  }

  if (normaldisplay) {
    color = PrimaryColor;
    colorSmooth = PrimaryColorSmooth;
  } else {
    color = BackgroundColor;
    colorSmooth = BackgroundColor;
  }

  switch (bandFM) {
    case FM_BAND_ALL:
      if (notglanceview) tftPrint(0, myLanguage[language][105] + String(",") + myLanguage[language][106], bandFMx, bandFMy, color, colorSmooth, 28);
      else tftPrint(1, myLanguage[language][105] + String(",") + myLanguage[language][106], bandFMx, bandFMy, color, colorSmooth, 16);
      break;
    case FM_BAND_OIRT:
      if (notglanceview) tftPrint(0, myLanguage[language][106], bandFMx, bandFMy, color, colorSmooth, 28);
      else tftPrint(1, myLanguage[language][106], bandFMx, bandFMy, color, colorSmooth, 16);
      break;
    case FM_BAND_FM:
      if (notglanceview) tftPrint(0, myLanguage[language][105], bandFMx, bandFMy, color, colorSmooth, 28);
      else tftPrint(1, myLanguage[language][105], bandFMx, bandFMy, color, colorSmooth, 16);
      break;
  }
}

void CheckBandForbiddenAM () {
  switch (band) {
    case BAND_LW:
      if (bandAM == AM_BAND_MW_SW || bandAM == AM_BAND_MW || bandAM == AM_BAND_SW) bandforbidden = 1;
      else bandforbidden = 0;
      break;
    case BAND_MW:
      if (bandAM == AM_BAND_LW_SW || bandAM == AM_BAND_LW || bandAM == AM_BAND_SW) bandforbidden = 1;
      else bandforbidden = 0;
      break;
    case BAND_SW:
      if (bandAM == AM_BAND_LW_MW || bandAM == AM_BAND_LW || bandAM == AM_BAND_MW) bandforbidden = 1;
      else bandforbidden = 0;
      break;
  }
}

void doBandSelectionAM() {
  if (band < BAND_GAP) return;

  switch (bandAM) {
    case AM_BAND_ALL:
      break;
    case AM_BAND_LW_MW:
      if (band == BAND_SW) {
        band = BAND_LW;
        SelectBand();
      }
      break;
    case AM_BAND_LW_SW:
      if (band == BAND_MW) {
        band = BAND_LW;
        SelectBand();
      }
      break;
    case AM_BAND_MW_SW:
      if (band == BAND_LW) {
        band = BAND_MW;
        SelectBand();
      }
      break;
    case AM_BAND_LW:
      if (band != BAND_LW) {
        band = BAND_LW;
        SelectBand();
      }
      break;
    case AM_BAND_MW:
      if (band != BAND_MW) {
        band = BAND_MW;
        SelectBand();
      }
      break;
    case AM_BAND_SW:
      if (band != BAND_SW) {
        band = BAND_SW;
        SelectBand();
      }
      break;
  }
}

void ShowBandSelectionAM(bool notglanceview, bool normaldisplay) {

  uint16_t bandAMx, bandAMy;
  int color, colorSmooth;

  if (notglanceview) {
    bandAMx = 155;
    bandAMy = 118;
  } else {
    bandAMx = 310;
    bandAMy = 216;
  }

  if (normaldisplay) {
    color = PrimaryColor;
    colorSmooth = PrimaryColorSmooth;
  } else {
    color = BackgroundColor;
    colorSmooth = BackgroundColor;
  }

  switch (bandAM) {
    case AM_BAND_ALL:
      if (notglanceview) tftPrint(0, myLanguage[language][102] + String(",") + myLanguage[language][103] + String(",") + myLanguage[language][104], bandAMx, bandAMy, color, colorSmooth, 28);
      else tftPrint(1, myLanguage[language][102] + String(",") + myLanguage[language][103] + String(",") + myLanguage[language][104], bandAMx, bandAMy, color, colorSmooth, 16);
      break;
    case AM_BAND_LW_MW:
      if (notglanceview) tftPrint(0, myLanguage[language][102] + String(",") + myLanguage[language][103], bandAMx, bandAMy, color, colorSmooth, 28);
      else tftPrint(1, myLanguage[language][102] + String(",") + myLanguage[language][103], bandAMx, bandAMy, color, colorSmooth, 16);
      break;
    case AM_BAND_LW_SW:
      if (notglanceview) tftPrint(0, myLanguage[language][102] + String(",") + myLanguage[language][104], bandAMx, bandAMy, color, colorSmooth, 28);
      else tftPrint(1, myLanguage[language][102] + String(",") + myLanguage[language][104], bandAMx, bandAMy, color, colorSmooth, 16);
      break;
    case AM_BAND_MW_SW:
      if (notglanceview) tftPrint(0, myLanguage[language][103] + String(",") + myLanguage[language][104], bandAMx, bandAMy, color, colorSmooth, 28);
      else tftPrint(1, myLanguage[language][103] + String(",") + myLanguage[language][104], bandAMx, bandAMy, color, colorSmooth, 16);
      break;
    case AM_BAND_LW:
      if (notglanceview) tftPrint(0, myLanguage[language][102], bandAMx, bandAMy, color, colorSmooth, 28);
      else tftPrint(1, myLanguage[language][102], bandAMx, bandAMy, color, colorSmooth, 16);
      break;
    case AM_BAND_MW:
      if (notglanceview) tftPrint(0, myLanguage[language][103], bandAMx, bandAMy, color, colorSmooth, 28);
      else tftPrint(1, myLanguage[language][103], bandAMx, bandAMy, color, colorSmooth, 16);
      break;
    case AM_BAND_SW:
      if (notglanceview) tftPrint(0, myLanguage[language][104], bandAMx, bandAMy, color, colorSmooth, 28);
      else tftPrint(1, myLanguage[language][104], bandAMx, bandAMy, color, colorSmooth, 16);
      break;
  }
}

void ToggleBand(byte nowBand) {
  switch (nowBand) {
    case BAND_LW:
      if (bandAM == AM_BAND_LW_MW || bandAM == AM_BAND_ALL) band = BAND_MW;
      else if (bandAM == AM_BAND_LW_SW) band = BAND_SW;
      else if (bandAM == AM_BAND_LW) {
        if (bandFM == FM_BAND_FM) band = BAND_FM;
        else band = BAND_OIRT;
      }
      break;
    case BAND_MW:
      if (bandAM == AM_BAND_MW_SW || bandAM == AM_BAND_ALL) band = BAND_SW;
      else if (bandAM == AM_BAND_LW_MW || bandAM == AM_BAND_MW) {
        if (bandFM == FM_BAND_FM) band = BAND_FM;
        else band = BAND_OIRT;
      }
      break;
    case BAND_SW:
      if (bandFM == FM_BAND_FM) band = BAND_FM;
      else band = BAND_OIRT;
      break;
    case BAND_OIRT:
      if (bandFM == FM_BAND_ALL) band = BAND_FM;
      else if (bandFM == FM_BAND_OIRT) {
        if (bandAM == AM_BAND_ALL || bandAM == AM_BAND_LW_MW || bandAM == AM_BAND_LW_SW || bandAM == AM_BAND_LW) {
          band = BAND_LW;
          if (stepsize > 3) stepsize = 3;
        }
        else if (bandAM == AM_BAND_MW_SW || bandAM == AM_BAND_MW) band = BAND_MW;
        else if (bandAM == AM_BAND_SW) band = BAND_SW;
      } else if (bandFM == FM_BAND_FM) {
        if (bandAM == AM_BAND_ALL || bandAM == AM_BAND_LW_MW || bandAM == AM_BAND_LW_SW || bandAM == AM_BAND_LW) {
          band = BAND_LW;
          if (stepsize > 3) stepsize = 3;
        }
        else if (bandAM == AM_BAND_MW_SW || bandAM == AM_BAND_MW) band = BAND_MW;
        else if (bandAM == AM_BAND_SW) band = BAND_SW;
      }
      break;
    case BAND_FM:
      if (bandAM == AM_BAND_ALL || bandAM == AM_BAND_LW_MW || bandAM == AM_BAND_LW_SW || bandAM == AM_BAND_LW) {
        band = BAND_LW;
        if (stepsize > 3) stepsize = 3;
      }
      else if (bandAM == AM_BAND_MW_SW || bandAM == AM_BAND_MW) band = BAND_MW;
      else if (bandAM == AM_BAND_SW) band = BAND_SW;
      break;
  }
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
              ToggleBand(band);
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

          if (band < BAND_GAP) {
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
  EEPROM.writeUInt(EE_UINT16_FREQUENCY_OIRT, frequency_OIRT);
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

void ToggleSWMIBand(bool frequencyup) {
  switch (SWMIBandPosold) {
    case SW_MI_BAND_GAP:
      if (frequencyup) {
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
      if (frequencyup) {
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
      if (frequencyup) {
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
      if (frequencyup) {
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
      if (frequencyup) {
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
      if (frequencyup) {
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
      if (frequencyup) {
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
      if (frequencyup) {
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
      if (frequencyup) {
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
      if (frequencyup) {
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
      if (frequencyup) {
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
      if (frequencyup) {
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
      if (frequencyup) {
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
      if (frequencyup) {
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
      if (frequencyup) {
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
      if (frequencyup) {
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
  if (band > BAND_GAP) {
    seek = false;
    if (tunemode == TUNE_MI_BAND && band != BAND_SW) tunemode = TUNE_MAN;
    BWreset = true;
    BWset = 2;
    if (band == BAND_LW) freqold = frequency_LW;
    else if (band == BAND_MW) freqold = frequency_MW;
    else if (band == BAND_SW) freqold = frequency_SW;
    LimitAMFrequency();
    CheckBandForbiddenAM();
    radio.SetFreqAM(frequency_AM);
    doBW();
    radio.getStatusAM(SStatus, USN, WAM, OStatus, BW, MStatus, SNR);
    if (screenmute == false) radio.clearRDS(fullsearchrds); BuildDisplay();
    if (region == 0) tftPrint(-1, "PI:", 212, 193, GreyoutColor, BackgroundColor, 16);
    if (region == 1) tftPrint(-1, "ID:", 212, 193, GreyoutColor, BackgroundColor, 16);
    tftPrint(-1, "PS:", 3, 193, GreyoutColor, BackgroundColor, 16);
    tftPrint(-1, "RT:", 3, 221, GreyoutColor, BackgroundColor, 16);
    tftPrint(-1, "PTY:", 3, 163, GreyoutColor, BackgroundColor, 16);
    tft.drawBitmap(122, 5, RDSLogo, 35, 22, GreyoutColor);
    tft.drawRoundRect(248, 56, 32, 20, 5, GreyoutColor);
    tftPrint(0, "iMS", 265, 59, GreyoutColor, BackgroundColor, 16);
    tft.drawRoundRect(286, 56, 32, 20, 5, GreyoutColor);
    tftPrint(0, "EQ", 303, 59, GreyoutColor, BackgroundColor, 16);
  } else {
    LowLevelInit = false;
    BWreset = true;
    BWset = 0;
    if (tunemode == TUNE_MI_BAND) tunemode = TUNE_MAN;
    radio.power(0);
    delay(50);
    if (band == BAND_FM) radio.SetFreq(frequency);
    else if (band == BAND_OIRT) radio.SetFreq(frequency_OIRT);
    freqold = frequency_AM;
    CheckBandForbiddenFM();
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
      tft.drawSmoothCircle(66, 15, 10, BackgroundColor, BackgroundColor);
      tft.drawSmoothCircle(66, 15, 9, BackgroundColor, BackgroundColor);
      tft.drawSmoothCircle(76, 15, 10, BackgroundColor, BackgroundColor);
      tft.drawSmoothCircle(76, 15, 9, BackgroundColor, BackgroundColor);
      tft.drawSmoothCircle(71, 15, 10, SecondaryColor, SecondaryColorSmooth);
      tft.drawSmoothCircle(71, 15, 9, SecondaryColor, SecondaryColorSmooth);
    }
    radio.setMono(true);
    StereoToggle = false;
  } else {
    if (screenmute == false) {
      tft.drawSmoothCircle(71, 15, 10, BackgroundColor, BackgroundColor);
      tft.drawSmoothCircle(71, 15, 9, BackgroundColor, BackgroundColor);
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
          tftPrint(-1, myLanguage[language][86], 70, 68, ActiveColor, ActiveColorSmooth, 28);
          delay(1000);
          tftPrint(-1, myLanguage[language][86], 70, 68, BackgroundColor, BackgroundColor, 28);
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
      if (menuopen) {
        ButtonPress();
      } else {
        OStatusold = 1000;
        Stereostatusold = false;
        SStatusold = 2000;
        BWOld = 0;
        radio.clearRDS(fullsearchrds);
        RDSstatus = false;
        if (frequency % 10 != 0) {
          if (fmdefaultstepsize == 1) Round100K(frequency); else Round50K(frequency);
          EEPROM.writeUInt(EE_UINT16_FREQUENCY_FM, frequency);
        }
        radio.clearRDS(fullsearchrds);
        CheckBandForbiddenFM();
        CheckBandForbiddenAM();
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
        EEPROM.writeByte(EE_BYTE_BANDFM, bandFM);
        EEPROM.writeByte(EE_BYTE_BANDAM, bandAM);
        EEPROM.writeByte(EE_BYTE_HIGHCUTLEVEL, HighCutLevel);
        EEPROM.writeByte(EE_BYTE_HIGHCUTOFFSET, HighCutOffset);
        EEPROM.writeByte(EE_BYTE_LEVELOFFSET, LevelOffset);
        EEPROM.writeByte(EE_BYTE_RTBUFFER, radio.rds.rtbuffer);
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
        EEPROM.writeByte(EE_BYTE_TOUCH_ROTATING, touchrotating);
        EEPROM.writeUInt(EE_UINT16_LOWEDGEOIRTSET, LowEdgeOIRTSet);
        EEPROM.writeUInt(EE_UINT16_HIGHEDGEOIRTSET, HighEdgeOIRTSet);
        EEPROM.writeByte(EE_BYTE_HARDWARE_MODEL, hardwaremodel);
        EEPROM.writeByte(EE_BYTE_POWEROPTIONS, poweroptions);
        EEPROM.writeByte(EE_BYTE_CURRENTTHEME, CurrentTheme);
        EEPROM.writeByte(EE_BYTE_FMDEFAULTSTEPSIZE, fmdefaultstepsize);
        EEPROM.writeByte(EE_BYTE_SCREENSAVERSET, screensaverset);
        EEPROM.writeInt(EE_INT16_AMLEVELOFFSET, AMLevelOffset);
        EEPROM.writeByte(EE_BYTE_UNIT, unit);
        EEPROM.writeByte(EE_BYTE_AF, af);
        EEPROM.writeByte(EE_BYTE_STEREO, StereoToggle);
        EEPROM.writeByte(EE_BYTE_BATTERY_OPTIONS, batteryoptions);
        EEPROM.commit();
        Serial.end();
        if (wifi) remoteip = IPAddress (WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], subnetclient);
        if (USBmode) Serial.begin(19200); else Serial.begin(115200);
        doBandSelectionFM();
        doBandSelectionAM();
        ScreensaverTimerSet(screensaverOptions[screensaverset]);
        if (screensaverset) ScreensaverTimerRestart();
      }
    }
  }
  while (digitalRead(MODEBUTTON) == LOW) delay(50);
  delay(100);
}

void ShowStepSize() {
  if (!advancedRDS) {
    tft.fillRect(224, 38, 15, 4, GreyoutColor);
    tft.fillRect(193, 38, 15, 4, GreyoutColor);
    if (band < BAND_GAP) tft.fillRect(148, 38, 15, 4, GreyoutColor); else tft.fillRect(162, 38, 15, 4, GreyoutColor);
    if (band < BAND_GAP) tft.fillRect(116, 38, 15, 4, GreyoutColor); else if (band != BAND_LW) tft.fillRect(128, 38, 15, 4, GreyoutColor);
    if (stepsize == 1) tft.fillRect(224, 38, 15, 4, InsignificantColor);
    if (stepsize == 2) tft.fillRect(193, 38, 15, 4, InsignificantColor);
    if (stepsize == 3) {
      if (band < BAND_GAP) tft.fillRect(148, 38, 15, 4, InsignificantColor); else tft.fillRect(162, 38, 15, 4, InsignificantColor);
    }
    if (stepsize == 4) {
      if (band < BAND_GAP) tft.fillRect(116, 38, 15, 4, InsignificantColor); else tft.fillRect(128, 38, 15, 4, InsignificantColor);
    }
  }
}

void Round30K(unsigned int freq) {
  if (freq % FREQ_OIRT_STEP_30K < FREQ_OIRT_STEP_30K) {
    frequency_OIRT = (freq - freq % FREQ_OIRT_STEP_30K);
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
    if (fmdefaultstepsize == 1) Round100K(freq); else Round50K(freq);
    radio.SetFreq(frequency);
  } else if (band == BAND_OIRT) {
    Round30K(frequency_OIRT);
    radio.SetFreq(frequency_OIRT);
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

  if (band == BAND_FM) EEPROM.writeUInt(EE_UINT16_FREQUENCY_FM, frequency);
  else if (band == BAND_OIRT) EEPROM.writeUInt(EE_UINT16_FREQUENCY_OIRT, frequency_OIRT);
  else EEPROM.writeUInt(EE_UINT16_FREQUENCY_AM, frequency_AM);
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
          if (band == BAND_SW || band < BAND_GAP) {
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
        if (band < BAND_GAP) {
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
        } else {
          if (band == BAND_SW) {
            if (tunemode != TUNE_MEM) {
              nowToggleSWMIBand = !nowToggleSWMIBand;
              tunemode = TUNE_MEM;
              doTuneMode();
              ShowTuneMode();
            }
          }
        }
      }
    }
    if (screensaverset) {
      ScreensaverTimerRestart();
    }
  } else {
    DoMenu();
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
              ToggleSWMIBand(true);
            } else {
              ToggleSWMIBand(REVERSE);
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
      MenuUp();
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
              ToggleSWMIBand(REVERSE);
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
      MenuDown();
    }
  }
}

void ShowMemoryPos() {
  if (tunemode == TUNE_MEM) {
    if (advancedRDS) tftReplace(-1, String(memoryposold + 1), String(memorypos + 1), 215, 36, SecondaryColor, SecondaryColorSmooth, 16); else tftReplace(-1, String(memoryposold + 1), String(memorypos + 1), 50, 32, PrimaryColor, PrimaryColorSmooth, 16);
    memoryposold = memorypos;
  } else {
    if (advancedRDS) tftPrint(-1, String(memorypos + 1), 215, 36, BackgroundColor, BackgroundColor, 16); else tftPrint(-1, String(memorypos + 1), 50, 32, BackgroundColor, BackgroundColor, 16);
  }
}

void DoMemoryPosTune() {
  if (band != memoryband[memorypos]) {
    band = memoryband[memorypos];
    SelectBand();
  } else {
    band = memoryband[memorypos];
  }

  if (band == BAND_FM || band == BAND_OIRT) {
    frequency = memory[memorypos];
    radio.SetFreq(frequency);
  } else {
    frequency_AM = memory[memorypos];
    radio.SetFreqAM(frequency_AM);
  }
  ShowFreq(0);
}

void ShowFreq(int mode) {
  resetFontOnNextCall = true;
  tft.unloadFont();
  if (screenmute == false) {
    if (setupmode == false) {
      if (band != BAND_FM && band != BAND_OIRT) { // Fix Me :take care of 9K/10K Step
        if (freqold < 2000 && frequency_AM >= 2000 && stepsize == 0) if (frequency_AM != 27000 && freqold != 144) radio.SetFreqAM(2000);
        if (freqold >= 2000 && frequency_AM < 2000 && stepsize == 0) if (frequency_AM != 144 && freqold != 27000) radio.SetFreqAM(1998);
      }
    }

    if (screenmute == false) {
      detachInterrupt(digitalPinToInterrupt(ROTARY_PIN_A));
      detachInterrupt(digitalPinToInterrupt(ROTARY_PIN_B));
      if (band > BAND_GAP) {
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
        unsigned int freq;
        if (band == BAND_FM) freq = frequency + ConverterSet * 100;
        else if (band == BAND_OIRT) freq = frequency_OIRT + ConverterSet * 100;

        if (advancedRDS) {
          for (int i = 0; i < 33; i++) tft.fillCircle((6 * i) + 10, 133, 2, GreyoutColor);
          tftReplace(1, String(freqold / 100) + "." + (freqold % 100 < 10 ? "0" : "") + String(freqold % 100) + " MHz", String(freq / 100) + "." + (freq % 100 < 10 ? "0" : "") + String(freq % 100) + " MHz", 310, 35, PrimaryColor, PrimaryColorSmooth, 16);
          freqold = freq;
        } else if (afscreen) {
          tftReplace(1, String(freqold / 100) + "." + (freqold % 100 < 10 ? "0" : "") + String(freqold % 100) + " MHz", String(freq / 100) + "." + (freq % 100 < 10 ? "0" : "") + String(freq % 100), 290, 201, BWAutoColor, BWAutoColorSmooth, 16);
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
            if (band < BAND_GAP) {
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
    rdsreset = true;
    sprite.fillSprite(BackgroundColor);
    sprite2.fillSprite(BackgroundColor);
    if (advancedRDS) sprite2.pushSprite(35, 220); else if (!afscreen) sprite.pushSprite(38, 220);

    if (wifi) {
      String stationprint;
      stationprint = "from=TEF_tuner;RcvLevel=";
      stationprint += String(SStatus / 10);
      stationprint += ";bandwidth=-1;freq=";
      if (band > BAND_GAP) {
        stationprint += String(frequency_AM) + "000";
      } else {
        stationprint += String(band == BAND_FM ? frequency : frequency_OIRT) + "0000";
      }
      Udp.beginPacket(remoteip, 9030);
      Udp.print(stationprint);
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
          if (SNRold == 0) tftPrint(1, "--", 295, 163, BackgroundColor, BackgroundColor, 16); else tftPrint(1, String(SNRold), 295, 163, BackgroundColor, BackgroundColor, 16);
          if (tuned == true) {
            if (SNR == 0) tftPrint(1, "--", 295, 163, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, String(SNR), 295, 163, PrimaryColor, PrimaryColorSmooth, 16);
            SNRold = SNR;
          } else {
            tftPrint(1, "--", 295, 163, PrimaryColor, PrimaryColorSmooth, 16);
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
    if (unit == 2) SStatusprint = round((float(SStatus) / 10.0 - 10.0 * log10(75) - 90.0) * 10.0);

    if (SStatusprint > (SStatusold + 3) || SStatusprint < (SStatusold - 3)) {
      if (advancedRDS) {
        tftReplace(1, String(SStatusold / 10) + "." + String(abs(SStatusold % 10)), String(SStatusprint / 10) + "." + String(abs(SStatusprint % 10)), 273, 51, PrimaryColor, PrimaryColorSmooth, 16);
      } else {
        if (SStatusold / 10 != SStatusprint / 10) tftReplace(1, String(SStatusold / 10), String(SStatusprint / 10), 288, 105, PrimaryColor, PrimaryColorSmooth, 48);
        tftReplace(1, "." + String(abs(SStatusold % 10)), "." + String(abs(SStatusprint % 10)), 310, 105, PrimaryColor, PrimaryColorSmooth, 28);

        if (band < BAND_GAP) segments = (SStatus + 200) / 10; else segments = (SStatus + 200) / 10;

        tft.fillRect(16, 105, 2 * constrain(segments, 0, 54), 6, BarInsignificantColor);
        tft.fillRect(16 + 2 * 54, 105, 2 * (constrain(segments, 54, 94) - 54), 6, BarSignificantColor);
        tft.fillRect(16 + 2 * constrain(segments, 0, 94), 105, 2 * (94 - constrain(segments, 0, 94)), 6, GreyoutColor);
      }
      SStatusold = SStatusprint;
    }
  }
  if (wifi) {
    Udp.beginPacket(remoteip, 9030);
    Udp.print("from=TEF_tuner;RcvLevel=");
    Udp.print(String(SStatus / 10));
    Udp.endPacket();
  }
}

void ShowRDSLogo(bool RDSstatus) {
  if (screenmute == false) {
    if (RDSstatus != RDSstatusold) {
      if (RDSstatus) tft.drawBitmap(122, 5, RDSLogo, 35, 22, RDSColor); else tft.drawBitmap(122, 5, RDSLogo, 35, 22, GreyoutColor);
      RDSstatusold = RDSstatus;
    }
  }
}

void ShowStereoStatus() {
  if (StereoToggle == true) {
    if (band < BAND_GAP) Stereostatus = radio.getStereoStatus(); else Stereostatus = 0;
    if (Stereostatus != Stereostatusold) {
      if (Stereostatus == true && screenmute == false) {
        tft.drawSmoothCircle(66, 15, 10, StereoColor, StereoColorSmooth);
        tft.drawSmoothCircle(66, 15, 9, StereoColor, StereoColorSmooth);
        tft.drawSmoothCircle(76, 15, 10, StereoColor, StereoColorSmooth);
        tft.drawSmoothCircle(76, 15, 9, StereoColor, StereoColorSmooth);
      } else {
        if (screenmute == false) {
          tft.drawSmoothCircle(66, 15, 10, GreyoutColor, BackgroundColor);
          tft.drawSmoothCircle(66, 15, 9, GreyoutColor, BackgroundColor);
          tft.drawSmoothCircle(76, 15, 10, GreyoutColor, BackgroundColor);
          tft.drawSmoothCircle(76, 15, 9, GreyoutColor, BackgroundColor);
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

    if (band < BAND_GAP) {
      if (OStatus < -500) {
        tft.fillTriangle(3, 8, 3, 22, 11, 14, GreyoutColor);
        tft.fillTriangle(13, 8, 13, 22, 21, 14, GreyoutColor);
        tft.fillCircle(26, 15, 3, GreyoutColor);
        tft.fillTriangle(32, 14, 40, 8, 40, 22, GreyoutColor);
        tft.fillTriangle(42, 14, 50, 8, 50, 22, SignificantColor);
        tuned = false;
      } else if (OStatus < -250 && OStatus > -500) {
        tft.fillTriangle(3, 8, 3, 22, 11, 14, GreyoutColor);
        tft.fillTriangle(13, 8, 13, 22, 21, 14, GreyoutColor);
        tft.fillCircle(26, 15, 3, GreyoutColor);
        tft.fillTriangle(32, 14, 40, 8, 40, 22, SignificantColor);
        tft.fillTriangle(42, 14, 50, 8, 50, 22, GreyoutColor);
        tuned = false;
      } else if (USN < 250 && WAM < 250 && OStatus > -250 && OStatus < 250 && SQ == false) {
        tft.fillTriangle(3, 8, 3, 22, 11, 14, GreyoutColor);
        tft.fillTriangle(13, 8, 13, 22, 21, 14, GreyoutColor);
        tft.fillCircle(26, 15, 3, InsignificantColor);
        tft.fillTriangle(32, 14, 40, 8, 40, 22, GreyoutColor);
        tft.fillTriangle(42, 14, 50, 8, 50, 22, GreyoutColor);
        tuned = true;
      } else if (OStatus > 250 && OStatus < 500) {
        tft.fillTriangle(3, 8, 3, 22, 11, 14, GreyoutColor);
        tft.fillTriangle(13, 8, 13, 22, 21, 14, SignificantColor);
        tft.fillCircle(26, 15, 3, GreyoutColor);
        tft.fillTriangle(32, 14, 40, 8, 40, 22, GreyoutColor);
        tft.fillTriangle(42, 14, 50, 8, 50, 22, GreyoutColor);
        tuned = false;
      } else if (OStatus > 500) {
        tft.fillTriangle(3, 8, 3, 22, 11, 14, SignificantColor);
        tft.fillTriangle(13, 8, 13, 22, 21, 14, GreyoutColor);
        tft.fillCircle(26, 15, 3, GreyoutColor);
        tft.fillTriangle(32, 14, 40, 8, 40, 22, GreyoutColor);
        tft.fillTriangle(42, 14, 50, 8, 50, 22, GreyoutColor);
        tuned = false;
      } else {
        tft.fillTriangle(3, 8, 3, 22, 11, 14, GreyoutColor);
        tft.fillTriangle(13, 8, 13, 22, 21, 14, GreyoutColor);
        tft.fillCircle(26, 15, 3, GreyoutColor);
        tft.fillTriangle(32, 14, 40, 8, 40, 22, GreyoutColor);
        tft.fillTriangle(42, 14, 50, 8, 50, 22, GreyoutColor);
        tuned = false;
      }
    } else {
      if (OStatus <= -3) {
        tft.fillTriangle(3, 8, 3, 22, 11, 14, GreyoutColor);
        tft.fillTriangle(13, 8, 13, 22, 21, 14, GreyoutColor);
        tft.fillCircle(26, 15, 3, GreyoutColor);
        tft.fillTriangle(32, 14, 40, 8, 40, 22, GreyoutColor);
        tft.fillTriangle(42, 14, 50, 8, 50, 22, SignificantColor);
        tuned = false;
      } else if (OStatus < -2 && OStatus > -3) {
        tft.fillTriangle(3, 8, 3, 22, 11, 14, GreyoutColor);
        tft.fillTriangle(13, 8, 13, 22, 21, 14, GreyoutColor);
        tft.fillCircle(26, 15, 3, GreyoutColor);
        tft.fillTriangle(32, 14, 40, 8, 40, 22, SignificantColor);
        tft.fillTriangle(42, 14, 50, 8, 50, 22, GreyoutColor);
        tuned = false;
      } else if (OStatus > -2 && OStatus < 2 && SQ == false) {
        tft.fillTriangle(3, 8, 3, 22, 11, 14, GreyoutColor);
        tft.fillTriangle(13, 8, 13, 22, 21, 14, GreyoutColor);
        tft.fillCircle(26, 15, 3, InsignificantColor);
        tft.fillTriangle(32, 14, 40, 8, 40, 22, GreyoutColor);
        tft.fillTriangle(42, 14, 50, 8, 50, 22, GreyoutColor);
        tuned = true;
      } else if (OStatus > 2 && OStatus < 3) {
        tft.fillTriangle(3, 8, 3, 22, 11, 14, GreyoutColor);
        tft.fillTriangle(13, 8, 13, 22, 21, 14, SignificantColor);
        tft.fillCircle(26, 15, 3, GreyoutColor);
        tft.fillTriangle(32, 14, 40, 8, 40, 22, GreyoutColor);
        tft.fillTriangle(42, 14, 50, 8, 50, 22, GreyoutColor);
        tuned = false;
      } else if (OStatus >= 3) {
        tft.fillTriangle(3, 8, 3, 22, 11, 14, SignificantColor);
        tft.fillTriangle(13, 8, 13, 22, 21, 14, GreyoutColor);
        tft.fillCircle(26, 15, 3, GreyoutColor);
        tft.fillTriangle(32, 14, 40, 8, 40, 22, GreyoutColor);
        tft.fillTriangle(42, 14, 50, 8, 50, 22, GreyoutColor);
        tuned = false;
      } else {
        tft.fillTriangle(3, 8, 3, 22, 11, 14, GreyoutColor);
        tft.fillTriangle(13, 8, 13, 22, 21, 14, GreyoutColor);
        tft.fillCircle(26, 15, 3, GreyoutColor);
        tft.fillTriangle(32, 14, 40, 8, 40, 22, GreyoutColor);
        tft.fillTriangle(42, 14, 50, 8, 50, 22, GreyoutColor);
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
    if (BWset == 0) tftReplace(1, String (BWOld, DEC), String (BW, DEC), 201, 4, BWAutoColor, BWAutoColorSmooth, 28); else tftReplace(1, String (BWOld, DEC), String (BW, DEC), 201, 4, PrimaryColor, PrimaryColorSmooth, 28);
    BWOld = BW;
    BWreset = false;
    if (wifi) {
      Udp.beginPacket(remoteip, 9030);
      Udp.print("from=TEF_tuner;bandwidth=");
      Udp.print(String(BW * 1000));
      Udp.endPacket();
    }
  }
}

void ShowModLevel() {
  if (showmodulation) {
    int segments;

    if (seek || SQ) {
      MStatus = 0;
      MStatusold = 1;
    }
    segments = map(MStatus, 0, 120, 0, 94);

    if (segments > peakholdold) {
      peakholdold = segments;
      peakholdmillis = millis();
    }

    tft.fillRect(16, 133, 2 * constrain(segments, 0, 54), 6, BarInsignificantColor);
    tft.fillRect(16 + 2 * 54, 133, 2 * (constrain(segments, 54, 94) - 54), 6, BarSignificantColor);
    tft.fillRect(16 + 2 * constrain(segments, 0, 94), 133, 2 * (94 - constrain(segments, 0, 94)), 6, GreyoutColor);

    int peakHoldPosition = 16 + 2 * constrain(peakholdold, 0, 94);
    tft.fillRect(peakHoldPosition, 133, 2, 6, (MStatus > 80) ? BarSignificantColor : PrimaryColor);

    if (millis() - peakholdmillis >= 1000) {
      tft.fillRect(peakHoldPosition, 133, 2, 6, GreyoutColor);
      peakholdold = segments;
      peakholdmillis = millis();
    }
  }
}

void doSquelch() {
  if (XDRGTKUSB == false && XDRGTKTCP == false) {
    Squelch = analogRead(PIN_POT) / 4 - 100;
    if (unit == 0) SquelchShow = Squelch / 10;
    if (unit == 1) SquelchShow = ((Squelch * 100) + 10875) / 1000;
    if (unit == 2) SquelchShow = round((float(Squelch) / 10.0 - 10.0 * log10(75) - 90.0) * 10.0) / 10;

    if (Squelch > 920) Squelch = 920;
    if (showsquelch && !advancedRDS && !afscreen) {
      if (menu == false && (Squelch > Squelchold + 2 || Squelch < Squelchold - 2)) {
        if (Squelchold == -100) {
          if (Squelch != Squelchold) tftPrint(-1, myLanguage[language][33], 235, 145, BackgroundColor, BackgroundColor, 16);
        } else if (Squelchold == 920) {
          if (Squelch != Squelchold) tftPrint(-1, "ST", 235, 145, BackgroundColor, BackgroundColor, 16);
        } else {
          if (Squelch != Squelchold) tftPrint(-1, String(SquelchShowold), 235, 145, BackgroundColor, BackgroundColor, 16);
        }
        if (Squelch == -100) {
          if (Squelch != Squelchold) tftPrint(-1, myLanguage[language][33], 235, 145, PrimaryColor, PrimaryColorSmooth, 16);
        } else if (Squelch == 920) {
          tftPrint(-1, "ST", 235, 145, PrimaryColor, PrimaryColorSmooth, 16);
        } else {
          if (Squelch != Squelchold) tftPrint(-1, String(SquelchShow), 235, 145, PrimaryColor, PrimaryColorSmooth, 16);
        }
        SquelchShowold = SquelchShow;
      }
      Squelchold = Squelch;
    }
  }
  if ((XDRGTKUSB == true || XDRGTKTCP == true)) {
    if (XDRMute == false) {
      if (Squelch != -1) {
        if (Squelch < SStatus || Squelch == -100 || Squelch == 0) {
          if (!seek) radio.setUnMute();
          if (screenmute == false) tft.drawBitmap(92, 4, Speaker, 26, 22, GreyoutColor);
          SQ = false;
        } else {
          radio.setMute();
          if (screenmute == false) tft.drawBitmap(92, 4, Speaker, 26, 22, PrimaryColor);
          SQ = true;
        }
      } else {
        if (Stereostatus == true) {
          radio.setUnMute();
          if (screenmute == false) tft.drawBitmap(92, 4, Speaker, 26, 22, GreyoutColor);
          SQ = false;
        } else {
          radio.setMute();
          if (screenmute == false) tft.drawBitmap(92, 4, Speaker, 26, 22, PrimaryColor);
          SQ = true;
        }
      }
      if (screenmute == false && showsquelch == true && !advancedRDS && !afscreen) {
        if (Squelch != Squelchold) {
          if (Squelchold == -1) {
            if (Squelch != Squelchold) tftPrint(-1, "ST", 235, 145, BackgroundColor, BackgroundColor, 16);
          } else if (Squelchold == 0) {
            if (Squelch != Squelchold) tftPrint(-1, myLanguage[language][33], 235, 145, BackgroundColor, BackgroundColor, 16);
          } else {
            if (Squelch != Squelchold) tftPrint(-1, String(SquelchShowold), 235, 145, BackgroundColor, BackgroundColor, 16);
          }
          if (Squelch == -1) {
            if (Squelch != Squelchold) tftPrint(-1, "ST", 235, 145, PrimaryColor, PrimaryColorSmooth, 16);
          } else if (Squelch == 0) {
            if (Squelch != Squelchold) tftPrint(-1, myLanguage[language][33], 235, 145, PrimaryColor, PrimaryColorSmooth, 16);
          } else {
            if (Squelch != Squelchold) tftPrint(-1, String(SquelchShow), 235, 145, PrimaryColor, PrimaryColorSmooth, 16);
          }
          Squelchold = Squelch;
          SquelchShowold = SquelchShow;
        }
      }
    }
  } else {
    if (Squelch != 920) {
      if (Squelch < SStatus || Squelch == -100 || Squelch == 0) {
        if (!seek) radio.setUnMute();
        if (screenmute == false) tft.drawBitmap(92, 4, Speaker, 26, 22, GreyoutColor);
        SQ = false;
      } else {
        radio.setMute();
        if (screenmute == false) tft.drawBitmap(92, 4, Speaker, 26, 22, PrimaryColor);
        SQ = true;
      }
    } else {
      if (Stereostatus == true) {
        if (!seek) radio.setUnMute();
        if (screenmute == false) tft.drawBitmap(92, 4, Speaker, 26, 22, GreyoutColor);
        SQ = false;
      } else {
        radio.setMute();
        if (screenmute == false) tft.drawBitmap(92, 4, Speaker, 26, 22, PrimaryColor);
        SQ = true;
      }
    }
  }
}

void updateBW() {
  if (BWset == 0) {
    if (screenmute == false && advancedRDS == false && afscreen == false) {
      tft.drawRoundRect(248, 35, 71, 20, 5, ActiveColor);
      tftPrint(0, "AUTO BW", 283, 38, ActiveColor, ActiveColorSmooth, 16);
    }
    radio.setFMABandw();
  } else {
    if (screenmute == false && advancedRDS == false && afscreen == false) {
      tft.drawRoundRect(248, 35, 71, 20, 5, GreyoutColor);
      tftPrint(0, "AUTO BW", 283, 38, GreyoutColor, BackgroundColor, 16);
    }
  }
}

void updateiMS() {
  if (band < BAND_GAP) {
    if (iMSset == 0) {
      if (screenmute == false) {
        tft.drawRoundRect(248, 56, 32, 20, 5, ActiveColor);
        tftPrint(0, "iMS", 265, 59, ActiveColor, ActiveColorSmooth, 16);
      }
      radio.setiMS(1);
    } else {
      if (screenmute == false) {
        tft.drawRoundRect(248, 56, 32, 20, 5, GreyoutColor);
        tftPrint(0, "iMS", 265, 59, GreyoutColor, BackgroundColor, 16);
      }
      radio.setiMS(0);
    }
  }
}

void updateEQ() {
  if (band < BAND_GAP) {
    if (EQset == 0) {
      if (screenmute == false) {
        tft.drawRoundRect(286, 56, 32, 20, 5, ActiveColor);
        tftPrint(0, "EQ", 303, 59, ActiveColor, ActiveColorSmooth, 16);
      }
      radio.setEQ(1);
    } else {
      if (screenmute == false) {
        tft.drawRoundRect(286, 56, 32, 20, 5, GreyoutColor);
        tftPrint(0, "EQ", 303, 59, GreyoutColor, BackgroundColor, 16);
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
      tftReplace(-1, SWMIBandstringold, SWMIBandstring, 50, 51, SecondaryColor, SecondaryColorSmooth, 16);
      if (!SWMIBandstring.equals(SWMIBandstringold)) SWMIBandstringold = SWMIBandstring;
      break;

    case SW_MI_BAND_GAP:
      tftPrint(-1, SWMIBandstringold, 50, 51, BackgroundColor, BackgroundColor, 16);
      break;
  }
}

void doBW() {
  if (band < BAND_GAP) {
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
      if (band == BAND_SW) {
        if (showSWMIBand && nowToggleSWMIBand) tunemode = TUNE_MI_BAND;
        else tunemode = TUNE_AUTO;
      } else {
        tunemode = TUNE_AUTO;
      }
      if (stepsize != 0) {
        stepsize = 0;
        RoundStep();
        ShowStepSize();
      }
      break;
    case TUNE_MI_BAND:
    case TUNE_AUTO:
      tunemode = TUNE_MEM;
      break;

    case TUNE_MEM:
      if (!bandforbidden) tunemode = TUNE_MAN;
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
      if (band == BAND_SW && nowToggleSWMIBand) {
        tftPrint(0, "AUTO", 22, 60, BackgroundColor, BackgroundColor, 16);

        tft.drawRoundRect(1, 57, 42, 20, 5, GreyoutColor);
        tftPrint(0, "BAND", 22, 60, GreyoutColor, BackgroundColor, 16);
      } else {
        tftPrint(0, "BAND", 22, 60, BackgroundColor, BackgroundColor, 16);

        tft.drawRoundRect(1, 57, 42, 20, 5, GreyoutColor);
        tftPrint(0, "AUTO", 22, 60, GreyoutColor, BackgroundColor, 16);
      }

      tft.drawRoundRect(1, 35, 42, 20, 5, ActiveColor);
      tftPrint(0, "MAN", 22, 38, ActiveColor, ActiveColorSmooth, 16);

      tft.drawRoundRect(1, 79, 42, 20, 5, GreyoutColor);
      tftPrint(0, "MEM", 22, 82, GreyoutColor, BackgroundColor, 16);
      break;

    case TUNE_AUTO:
      tft.drawRoundRect(1, 57, 42, 20, 5, ActiveColor);
      tftPrint(0, "AUTO", 22, 60, ActiveColor, ActiveColorSmooth, 16);

      tft.drawRoundRect(1, 35, 42, 20, 5, GreyoutColor);
      tftPrint(0, "MAN", 22, 38, GreyoutColor, BackgroundColor, 16);

      tft.drawRoundRect(1, 79, 42, 20, 5, GreyoutColor);
      tftPrint(0, "MEM", 22, 82, GreyoutColor, BackgroundColor, 16);
      break;

    case TUNE_MEM:
      if (band == BAND_SW && nowToggleSWMIBand) {
        tftPrint(0, "AUTO", 22, 60, BackgroundColor, BackgroundColor, 16);

        tft.drawRoundRect(1, 57, 42, 20, 5, GreyoutColor);
        tftPrint(0, "BAND", 22, 60, GreyoutColor, BackgroundColor, 16);
      } else {
        tftPrint(0, "BAND", 22, 60, BackgroundColor, BackgroundColor, 16);

        tft.drawRoundRect(1, 57, 42, 20, 5, GreyoutColor);
        tftPrint(0, "AUTO", 22, 60, GreyoutColor, BackgroundColor, 16);
      }

      tft.drawRoundRect(1, 35, 42, 20, 5, GreyoutColor);
      tftPrint(0, "MAN", 22, 39, GreyoutColor, BackgroundColor, 16);

      if (memorystore == true) {
        tft.drawRoundRect(1, 79, 42, 20, 5, SignificantColor);
        tftPrint(0, "MEM", 22, 82, SignificantColor, SignificantColorSmooth, 16);
      } else {
        tft.drawRoundRect(1, 79, 42, 20, 5, ActiveColor);
        tftPrint(0, "MEM", 22, 82, ActiveColor, ActiveColorSmooth, 16);
      }
      break;

    case TUNE_MI_BAND:
      tft.drawRoundRect(1, 57, 42, 20, 5, ActiveColor);
      tft.setTextColor(ActiveColor);
      tftPrint(0, "BAND", 22, 60, ActiveColor, ActiveColorSmooth, 16);

      tft.drawRoundRect(1, 35, 42, 20, 5, GreyoutColor);
      tftPrint(0, "MAN", 22, 38, GreyoutColor, BackgroundColor, 16);

      tft.drawRoundRect(1, 79, 42, 20, 5, GreyoutColor);
      tftPrint(0, "MEM", 22, 82, GreyoutColor, BackgroundColor, 16);
      break;
  }
}

void ShowRSSI() {
  if (wifi) rssi = WiFi.RSSI(); else rssi = 0;
  if (rssiold != rssi) {
    rssiold = rssi;
    if (rssi == 0) {
      tft.drawBitmap(250, 4, WiFi4, 25, 25, GreyoutColor);
    } else if (rssi > -50 && rssi < 0) {
      tft.drawBitmap(250, 4, WiFi4, 25, 25, PrimaryColor);
    } else if (rssi > -60) {
      tft.drawBitmap(250, 4, WiFi4, 25, 25, GreyoutColor);
      tft.drawBitmap(250, 4, WiFi3, 25, 25, PrimaryColor);
    } else if (rssi > -70) {
      tft.drawBitmap(250, 4, WiFi4, 25, 25, GreyoutColor);
      tft.drawBitmap(250, 4, WiFi2, 25, 25, PrimaryColor);
    } else if (rssi < -70) {
      tft.drawBitmap(250, 4, WiFi4, 25, 25, GreyoutColor);
      tft.drawBitmap(250, 4, WiFi1, 25, 25, PrimaryColor);
    }
  }
}

void ShowBattery() {
  if (millis() >= batupdatetimer + TIMER_BAT_TIMER) {
    batupdatetimer = millis();
  } else {
    return;
  }

  uint16_t v = analogRead(BATTERY_PIN);

  battery = map(constrain(v, BAT_LEVEL_EMPTY, BAT_LEVEL_FULL), BAT_LEVEL_EMPTY, BAT_LEVEL_FULL, 0, BAT_LEVEL_STAGE);
  if (batteryold != battery) {
    if (batterydetect) {
      if (battery == 0) {
        tft.drawRect(277, 6, 37, 20, BarSignificantColor);
        tft.fillRect(313, 13, 4, 6, BarSignificantColor);
        tft.fillRect(279, 8, 33, 16, BackgroundColor);
        if (!batteryoptions == BATTERY_VALUE || !batteryoptions == BATTERY_PERCENT) {
          tft.fillRect(279, 24 - (battery * 4), 33, battery * 4, BarInsignificantColor);
        }
      } else {
        tft.drawRect(277, 6, 37, 20, ActiveColor);
        tft.fillRect(313, 13, 4, 6, ActiveColor);
        tft.fillRect(279, 8, 33, 16, BackgroundColor);
        if (!batteryoptions == BATTERY_VALUE || !batteryoptions == BATTERY_PERCENT) {
          tft.fillRect(279, 24 - (battery * 4), 33, battery * 4, BarInsignificantColor);
        }
      }
    } else {
      tft.drawRect(277, 6, 37, 20, GreyoutColor);
      tft.fillRect(313, 13, 4, 6, GreyoutColor);
      tft.fillRect(279, 8, 33, 16, BackgroundColor);
    }
    batteryold = battery;
  }

  if (!wifi && batterydetect) {
    float batteryV = ((float)v / 4095.0) * 2.0 * 3.3 * (1056 / 1000.0);
    batteryV = constrain(batteryV, 0.0, 5.0);
    if (round(batteryV * 100.0) != round(batteryVold * 100.0)) {
      if (batteryoptions == BATTERY_VALUE) {
        tftReplace(-1, String(batteryVold, 1) + "V", String(batteryV, 1) + "V", 279, 9, BatteryValueColor, BatteryValueColorSmooth, 16);
        batteryVold = batteryV;
      } else if (batteryoptions == BATTERY_PERCENT) {
        float vPer = 0.0;
        vPer = (batteryV - BATTERY_LOW_VALUE) / (BATTERY_FULL_VALUE - BATTERY_LOW_VALUE);
        vPer = constrain(vPer, 0.0, 1.0);
        vPer *= 100.0;
        Serial.println(vPer);
        tftReplace(-1, String(vPerold, 0) + "%", String(vPer, 0) + "%", 279, 9, BatteryValueColor, BatteryValueColorSmooth, 16);
        vPerold = vPer;
      }
    }
  }
}

void DataPrint(String string) {
  if (XDRGTKUSB) Serial.print(string);
  if (XDRGTKTCP) RemoteClient.print(string);
}

void TuneUp() {
  aftest = true;
  aftimer = millis();
  unsigned int temp = 0;
  if (stepsize == 0) {
    if (band > BAND_GAP) {
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
      if (band == BAND_OIRT) {
        temp = FREQ_OIRT_STEP_30K;
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
    if (frequency >= (HighEdgeSet * 10) + 1) {
      frequency = LowEdgeSet * 10;
      if (edgebeep) EdgeBeeper();
    }
    radio.SetFreq(frequency);
  } else if (band == BAND_OIRT) {
    frequency_OIRT += temp;
    if (frequency_OIRT > HighEdgeOIRTSet) {
      frequency_OIRT = LowEdgeOIRTSet;
      if (edgebeep) EdgeBeeper();
    }
    radio.SetFreq(frequency_OIRT);
  } else if (band == BAND_LW) {
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
    if (band > BAND_GAP) {
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
      if (band == BAND_OIRT) {
        temp = FREQ_OIRT_STEP_30K;
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
    if (frequency < LowEdgeSet * 10) {
      frequency = HighEdgeSet * 10;
      if (edgebeep) EdgeBeeper();
    }
    radio.SetFreq(frequency);
  } else if (band == BAND_OIRT) {
    frequency_OIRT -= temp;
    if (frequency_OIRT < LowEdgeOIRTSet) {
      frequency_OIRT = HighEdgeOIRTSet;
      if (edgebeep) EdgeBeeper();
    }
    radio.SetFreq(frequency_OIRT);
  } else if (band == BAND_LW) {
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
    if (screenmute == false) tft.drawBitmap(92, 4, Speaker, 26, 22, PrimaryColor);
  } else {
    radio.setUnMute();
    if (screenmute == false) tft.drawBitmap(92, 4, Speaker, 26, 22, GreyoutColor);
  }
}

void Seek(bool mode) {
  if (band < BAND_GAP) {
    radio.setMute();
    if (screenmute == false) tft.drawBitmap(92, 4, Speaker, 26, 22, PrimaryColor);
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
      if (screenmute == false) tft.drawBitmap(92, 4, Speaker, 26, 22, GreyoutColor);
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

    if (TEF == 0) tftPrint(0, myLanguage[language][35], 150, 78, ActiveColor, ActiveColorSmooth, 28); else tftPrint(0, myLanguage[language][36] + String(TEF), 150, 78, ActiveColor, ActiveColorSmooth, 28);
    tftPrint(0, myLanguage[language][37], 150, 108, ActiveColor, ActiveColorSmooth, 28);
    EEPROM.writeByte(EE_BYTE_TEF, TEF);
    EEPROM.commit();
    while (true);
    for (;;);
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

void DefaultSettings(byte userhardwaremodel) {
  EEPROM.writeByte(EE_BYTE_CHECKBYTE, EE_CHECKBYTE_VALUE);
  if (userhardwaremodel == BASE_ILI9341) EEPROM.writeUInt(EE_UINT16_FREQUENCY_FM, 10000); else EEPROM.writeUInt(EE_UINT16_FREQUENCY_FM, 8900);
  EEPROM.writeUInt(EE_UINT16_FREQUENCY_OIRT, FREQ_FM_OIRT_START);
  EEPROM.writeInt(EE_BYTE_VOLSET, 0);
  EEPROM.writeUInt(EE_UINT16_CONVERTERSET, 0);
  EEPROM.writeUInt(EE_UINT16_FMLOWEDGESET, 875);
  EEPROM.writeUInt(EE_UINT16_FMHIGHEDGESET, 1080);
  EEPROM.writeByte(EE_BYTE_CONTRASTSET, 50);
  EEPROM.writeByte(EE_BYTE_STEREOLEVEL, 0);
  if (userhardwaremodel == BASE_ILI9341) EEPROM.writeByte(EE_BYTE_BANDFM, FM_BAND_ALL); else EEPROM.writeByte(EE_BYTE_BANDFM, FM_BAND_FM);
  EEPROM.writeByte(EE_BYTE_BANDAM, AM_BAND_ALL);
  EEPROM.writeByte(EE_BYTE_HIGHCUTLEVEL, 70);
  EEPROM.writeByte(EE_BYTE_HIGHCUTOFFSET, 0);
  EEPROM.writeByte(EE_BYTE_LEVELOFFSET, 0);
  EEPROM.writeByte(EE_BYTE_RTBUFFER, 1);
  EEPROM.writeByte(EE_BYTE_EDGEBEEP, 0);
  EEPROM.writeByte(EE_BYTE_SOFTMUTEAM, 0);
  EEPROM.writeByte(EE_BYTE_SOFTMUTEFM, 0);
  EEPROM.writeUInt(EE_UINT16_FREQUENCY_AM, 828);
  if (userhardwaremodel == BASE_ILI9341) EEPROM.writeByte(EE_BYTE_LANGUAGE, 0); else EEPROM.writeByte(EE_BYTE_LANGUAGE, LANGUAGE_CHS);
  EEPROM.writeByte(EE_BYTE_SHOWRDSERRORS, 0);
  EEPROM.writeByte(EE_BYTE_TEF, 0);
  if (userhardwaremodel == BASE_ILI9341) EEPROM.writeByte(EE_BYTE_DISPLAYFLIP, 0); else EEPROM.writeByte(EE_BYTE_DISPLAYFLIP, 1);
  EEPROM.writeByte(EE_BYTE_ROTARYMODE, 0);
  EEPROM.writeByte(EE_BYTE_STEPSIZE, 0);
  EEPROM.writeByte(EE_BYTE_TUNEMODE, 0);
  EEPROM.writeByte(EE_BYTE_OPTENC, 0);
  EEPROM.writeByte(EE_BYTE_IMSSET, 1);
  EEPROM.writeByte(EE_BYTE_EQSET, 1);
  EEPROM.writeByte(EE_BYTE_BAND, BAND_FM);
  EEPROM.writeInt(EE_BYTE_LOWLEVELSET, -10);
  EEPROM.writeByte(EE_BYTE_MEMORYPOS, 0);
  EEPROM.writeByte(EE_BYTE_REGION, 0);
  EEPROM.writeByte(EE_BYTE_RDS_UNDERSCORE, 0);
  EEPROM.writeByte(EE_BYTE_USBMODE, 0);
  EEPROM.writeByte(EE_BYTE_WIFI, 0);
  EEPROM.writeByte(EE_BYTE_SUBNETCLIENT, 1);
  EEPROM.writeByte(EE_BYTE_SHOWSWMIBAND, 1);
  EEPROM.writeByte(EE_BYTE_RDS_FILTER, 0);
  EEPROM.writeByte(EE_BYTE_RDS_PIERRORS, 0);
  for (int i = 0; i < EE_PRESETS_CNT; i++) EEPROM.writeByte(i + EE_PRESETS_BAND_START, BAND_FM);
  for (int i = 0; i < EE_PRESETS_CNT; i++) EEPROM.writeUInt((i * 4) + EE_PRESETS_START, EE_PRESETS_FREQUENCY);
  if (userhardwaremodel == BASE_ILI9341) EEPROM.writeUInt(EE_UINT16_FREQUENCY_LW, 180); else EEPROM.writeUInt(EE_UINT16_FREQUENCY_LW, 164);
  if (userhardwaremodel == BASE_ILI9341) EEPROM.writeUInt(EE_UINT16_FREQUENCY_MW, 540); else EEPROM.writeUInt(EE_UINT16_FREQUENCY_MW, 639);
  if (userhardwaremodel == BASE_ILI9341) EEPROM.writeUInt(EE_UINT16_FREQUENCY_SW, 1800); else EEPROM.writeUInt(EE_UINT16_FREQUENCY_SW, 5000);
  EEPROM.writeString(EE_STRING_XDRGTK_KEY, "password");
  if (userhardwaremodel == BASE_ILI9341) EEPROM.writeByte(EE_BYTE_SHOWSQUELCH, 1); else EEPROM.writeByte(EE_BYTE_SHOWSQUELCH, 0);
  EEPROM.writeByte(EE_BYTE_SHOWMODULATION, 1);
  EEPROM.writeByte(EE_BYTE_AM_NB, 0);
  EEPROM.writeByte(EE_BYTE_FM_NB, 0);
  EEPROM.writeByte(EE_BYTE_AUDIOMODE, 0);
  if (userhardwaremodel == BASE_ILI9341) EEPROM.writeByte(EE_BYTE_TOUCH_ROTATING, 0); else EEPROM.writeByte(EE_BYTE_TOUCH_ROTATING, 1);
  EEPROM.writeUInt(EE_UINT16_LOWEDGEOIRTSET, 0);
  EEPROM.writeUInt(EE_UINT16_HIGHEDGEOIRTSET, 0);
  EEPROM.writeByte(EE_BYTE_HARDWARE_MODEL, userhardwaremodel);
  EEPROM.writeByte(EE_BYTE_POWEROPTIONS, 1);
  EEPROM.writeByte(EE_BYTE_CURRENTTHEME, 0);
  EEPROM.writeByte(EE_BYTE_FMDEFAULTSTEPSIZE, 1);
  EEPROM.writeByte(EE_BYTE_SCREENSAVERSET, 0);
  EEPROM.writeInt(EE_INT16_AMLEVELOFFSET, 0);
  EEPROM.writeByte(EE_BYTE_UNIT, 0);
  EEPROM.writeByte(EE_BYTE_AF, 0);
  EEPROM.writeByte(EE_BYTE_STEREO, 1);
  EEPROM.writeByte(EE_BYTE_BATTERY_OPTIONS, BATTERY_VALUE);
  EEPROM.commit();
}

void tftReplace(int8_t offset, const String & textold, const String & text, int16_t x, int16_t y, int color, int smoothcolor, uint8_t fontsize) {
  const uint8_t *selectedFont = nullptr;
  if (language == LANGUAGE_CHS) {
    if (fontsize == 16) selectedFont = FONT16_CHS;
    if (fontsize == 28) selectedFont = FONT28_CHS;
  } else {
    if (fontsize == 16) selectedFont = FONT16;
    if (fontsize == 28) selectedFont = FONT28;
  }
  if (fontsize == 48) selectedFont = FONT48;

  if (currentFont != selectedFont || resetFontOnNextCall) {
    if (currentFont != nullptr) tft.unloadFont();

    tft.loadFont(selectedFont);
    currentFont = selectedFont;
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

void tftPrint(int8_t offset, const String & text, int16_t x, int16_t y, int color, int smoothcolor, uint8_t fontsize) {
  const uint8_t *selectedFont = nullptr;
  if (language == LANGUAGE_CHS) {
    if (fontsize == 16) selectedFont = FONT16_CHS;
    if (fontsize == 28) selectedFont = FONT28_CHS;
  } else {
    if (fontsize == 16) selectedFont = FONT16;
    if (fontsize == 28) selectedFont = FONT28;
  }
  if (fontsize == 48) selectedFont = FONT48;

  if (currentFont != selectedFont || resetFontOnNextCall) {
    if (currentFont != nullptr) tft.unloadFont();
    tft.loadFont(selectedFont);
    currentFont = selectedFont;
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
