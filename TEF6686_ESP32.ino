#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include <WiFiClient.h>
#include <EEPROM.h>
#include <Wire.h>
#include <math.h>
#include <ESP32Time.h>              // https://github.com/fbiego/ESP32Time
#include <TFT_eSPI.h>               // https://github.com/ohmytime/TFT_eSPI_DynamicSpeed (Modified version)
#include <Hash.h>                   // https://github.com/bbx10/Hash_tng
#include "src/WiFiConnect.h"
#include "src/WiFiConnectParam.h"
#include "src/FONT16.h"
#include "src/FONT16_CHS.h"
#include "src/FONT28.h"
#include "src/FONT28_CHS.h"
#include "src/FONT48DEC.h"
#include "src/FREQFONT.h"
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

// #define CHINA_PORTABLE      // uncomment for China Portable build (Simplified Chinese)
#define DYNAMIC_SPI_SPEED   // uncomment to enable dynamic SPI Speed https://github.com/ohmytime/TFT_eSPI_DynamicSpeed

#ifdef ARS
TFT_eSPI tft = TFT_eSPI(320, 240);
#else
TFT_eSPI tft = TFT_eSPI(240, 320);
#endif

#ifdef DYNAMIC_SPI_SPEED
bool dynamicspi = true;
#else
bool dynamicspi = false;
#endif

bool advancedRDS;
bool afmethodBold;
bool afpage;
bool afscreen;
bool aftest;
bool artheadold;
bool batterydetect = true;
bool beepresetstart;
bool beepresetstop;
bool BWreset;
bool BWtune;
bool change;
bool compressedold;
bool direction;
bool dropout;
bool dynamicPTYold;
bool edgebeep;
bool externaltune;
bool fullsearchrds;
bool hasafold;
bool hasCTold;
bool haseonold;
bool hasrtplusold;
bool hastmcold;
bool LowLevelInit;
bool memoryms[EE_PRESETS_CNT];
bool memorystore;
bool menu;
bool menuopen;
bool mwstepsize;
bool nobattery;
bool rdsflagreset;
bool rdsreset;
bool RDSSPYTCP;
bool RDSSPYUSB;
bool RDSstatus;
bool RDSstatusold;
bool rdsstereoold;
bool resetFontOnNextCall;
bool rtcset;
bool screenmute;
bool screensavertriggered = false;
bool seek;
bool setupmode;
byte showrdserrors;
bool usesquelch;
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
bool XDRGTKMuteScreen;
bool wifi;
bool wificonnected;
bool XDRGTKdata;
bool XDRGTKTCP;
bool XDRGTKUSB;
bool XDRMute;
byte af_counterold;
byte aid_counterold;
byte af;
byte afpagenr;
byte amnb;
byte amscansens;
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
byte BWsetAM;
byte BWsetFM;
byte charwidth = 8;
#ifdef CHINA_PORTABLE
byte hardwaremodel = PORTABLE_ILI9341;
#else
byte hardwaremodel = BASE_ILI9341;
#endif
byte hardwaremodelold;
byte ContrastSet;
byte CurrentSkin;
byte CurrentTheme;
byte displayflip;
byte ECCold;
byte eonptyold[20];
byte EQset;
byte fmscansens;
byte fmdefaultstepsize;
byte fmnb;
byte fmdeemphasis;
byte freqfont;
byte amcodect;
byte amcodectcount;
byte amrfagc;
byte freqoldcount;
byte HighCutLevel;
byte HighCutOffset;
byte iMSEQ;
byte iMSset;
byte language;
byte licold;
byte memoryband[EE_PRESETS_CNT];
byte memorybw[EE_PRESETS_CNT];
byte memorypos;
byte memoryposold;
byte memoryposstatus;
byte menupage;
byte MSold;
byte optenc;
byte poweroptions;
byte poweroptionsold;
byte rdsblockold;
byte rdsqualityold;
byte region;
byte rotarymode;
byte touchrotating;
byte screensaverOptions[5] = {0, 3, 10, 30, 60};
byte screensaverset;
byte showmodulation;
byte showSWMIBand;
byte submenu;
byte stationlistid;
byte nowToggleSWMIBand = 1;
byte stepsize;
byte StereoLevel;
byte subnetclient;
byte TEF;
byte tot;
byte tunemode;
byte unit;
byte spispeed;
byte spispeedold;
char buff[16];
char eonpicodeold[20][6];
char programTypePrevious[18];
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
int DeEmphasis;
int ForceMono;
int FrameColor;
int FreqColor;
int FreqColorSmooth;
int freqold;
int GreyoutColor;
int InsignificantColor;
int InsignificantColorSmooth;
int menuoption = ITEM1;
int ModBarInsignificantColor;
int ModBarSignificantColor;
int MStatusold;
int offsetupdatetimer;
int OStatusold;
int peakholdold;
int peakholdtimer;
int PrimaryColor;
int PrimaryColorSmooth;
int RDSColor;
int RDSColorSmooth;
int RDSDropoutColor;
int RDSDropoutColorSmooth;
int SignificantColor;
int SignificantColorSmooth;
int StereoColor;
int StereoColorSmooth;
int SquelchShow;
int rotary;
int rssi;
int rssiold = 200;
int scanner_filter;
int SecondaryColor;
int SecondaryColorSmooth;
int SNRupdatetimer;
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
int16_t SAvg3;
int16_t SStatus;
int8_t LevelOffset;
int8_t LowLevelSet;
int8_t CN;
int8_t CNold;
int8_t VolSet;
float batteryVold;
IPAddress remoteip;
String AIDString;
String cryptedpassword;
String ECColdtxt;
String eonpsold[20];
String LIColdString;
String pinstringold;
String PIold;
String PSold;
String ptynold = " ";
String PTYold;
String rds_clock;
String rds_clockold;
String RDSSPYRDS;
String RDSSPYRDSold;
String RTold;
String salt;
String saltkey = "                ";
String stationIDold;
String stationStateold;
String StereoStatusCommand;
String StereoStatusCommandold;
String SWMIBandstring = String();
String SWMIBandstringold = String();
String XDRGTK_key;
String XDRGTKRDS;
String XDRGTKRDSold;
uint16_t BW;
uint16_t MStatus;
uint16_t SWMIBandPos;
uint16_t SWMIBandPosold;
uint16_t USN;
uint16_t WAM;
uint8_t buff_pos;
unsigned int ConverterSet;
unsigned int freq_scan;
unsigned int frequency;
unsigned int frequency_OIRT;
unsigned int frequency_AM;
unsigned int frequency_LW;
unsigned int frequency_MIBand_11M;
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
unsigned int mappedfreqold2[20];
unsigned int mappedfreqold3[20];
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
unsigned long signalstatustimer;
unsigned long tottimer;
unsigned long tuningtimer;
unsigned long udptimer;

TEF6686 radio;
ESP32Time rtc(0);

TFT_eSprite RadiotextSprite = TFT_eSprite(&tft);
TFT_eSprite FrequencySprite = TFT_eSprite(&tft);
TFT_eSprite AdvRadiotextSprite = TFT_eSprite(&tft);
TFT_eSprite RDSSprite = TFT_eSprite(&tft);
TFT_eSprite SquelchSprite = TFT_eSprite(&tft);

WiFiConnect wc;
WiFiServer Server(7373);
WiFiClient RemoteClient;
WiFiUDP Udp;
hw_timer_t *timScreensaver = NULL;
byte screensaver_IRQ = OFF;

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  gpio_set_drive_capability((gpio_num_t) 5, GPIO_DRIVE_CAP_0);
  gpio_set_drive_capability((gpio_num_t) 16, GPIO_DRIVE_CAP_0);
  gpio_set_drive_capability((gpio_num_t) 17, GPIO_DRIVE_CAP_0);
  gpio_set_drive_capability((gpio_num_t) 18, GPIO_DRIVE_CAP_0);
  gpio_set_drive_capability((gpio_num_t) 19, GPIO_DRIVE_CAP_0);
  gpio_set_drive_capability((gpio_num_t) 21, GPIO_DRIVE_CAP_0);
  gpio_set_drive_capability((gpio_num_t) 22, GPIO_DRIVE_CAP_0);
  gpio_set_drive_capability((gpio_num_t) 23, GPIO_DRIVE_CAP_0);
  setupmode = true;
  EEPROM.begin(EE_TOTAL_CNT);
  if (EEPROM.readByte(EE_BYTE_CHECKBYTE) != EE_CHECKBYTE_VALUE) DefaultSettings(hardwaremodel);

  frequency = EEPROM.readUInt(EE_UINT16_FREQUENCY_FM);
  frequency_OIRT = EEPROM.readUInt(EE_UINT16_FREQUENCY_OIRT);
  VolSet = EEPROM.readByte(EE_BYTE_VOLSET);
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
  LowLevelSet = EEPROM.readByte(EE_BYTE_LOWLEVELSET);
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
  usesquelch = EEPROM.readByte(EE_BYTE_USESQUELCH);
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
  if (af == 2) radio.rds.afreg = true; else radio.rds.afreg = false;
  StereoToggle = EEPROM.readByte(EE_BYTE_STEREO);
  batteryoptions = EEPROM.readByte(EE_BYTE_BATTERY_OPTIONS);
  amcodect = EEPROM.readByte(EE_BYTE_AM_CO_DECT);
  amcodectcount = EEPROM.readByte(EE_BYTE_AM_CO_DECT_COUNT);
  amrfagc = EEPROM.readByte(EE_BYTE_AM_RF_AGC);
  radio.rds.sortaf = EEPROM.readByte(EE_BYTE_SORTAF);
  stationlistid = EEPROM.readByte(EE_BYTE_STATIONLISTID);
  fmdeemphasis = EEPROM.readByte(EE_BYTE_FM_DEEMPHASIS);
  BWsetFM = EEPROM.readByte(EE_BYTE_BWSET_FM);
  BWsetAM = EEPROM.readByte(EE_BYTE_BWSET_AM);
  nowToggleSWMIBand = EEPROM.readByte(EE_BYTE_BANDAUTOSW);
  radio.rds.fastps = EEPROM.readByte(EE_BYTE_FASTPS);
  tot = EEPROM.readByte(EE_BYTE_TOT);
  mwstepsize = EEPROM.readByte(EE_BYTE_MWREGION);
  spispeed = EEPROM.readByte(EE_BYTE_SPISPEED);
  amscansens = EEPROM.readByte(EE_BYTE_AMSCANSENS);
  fmscansens = EEPROM.readByte(EE_BYTE_FMSCANSENS);
  freqfont = EEPROM.readByte(EE_BYTE_FREQFONT);
  CurrentSkin = EEPROM.readByte(EE_BYTE_SKIN);
  XDRGTKMuteScreen = EEPROM.readByte(EE_BYTE_XDRGTKMUTE);

  if (spispeed == SPI_SPEED_DEFAULT) tft.setSPISpeed(SPI_FREQUENCY / 1000000); else tft.setSPISpeed(spispeed * 10);
  LWLowEdgeSet = FREQ_LW_LOW_EDGE_MIN;
  LWHighEdgeSet = FREQ_LW_HIGH_EDGE_MAX;
  MWLowEdgeSet = mwstepsize == false ? FREQ_MW_LOW_EDGE_MIN_9K : FREQ_MW_LOW_EDGE_MIN_10K;
  MWHighEdgeSet = mwstepsize == false ? FREQ_MW_HIGH_EDGE_MAX_9K : FREQ_MW_HIGH_EDGE_MAX_10K;
  SWLowEdgeSet = FREQ_SW_LOW_EDGE_MIN;
  SWHighEdgeSet = FREQ_SW_HIGH_EDGE_MAX;
  if (LowEdgeOIRTSet < FREQ_FM_OIRT_START || LowEdgeOIRTSet > FREQ_FM_OIRT_END) LowEdgeOIRTSet = FREQ_FM_OIRT_START;
  if (HighEdgeOIRTSet < FREQ_FM_OIRT_START || HighEdgeOIRTSet > FREQ_FM_OIRT_END) HighEdgeOIRTSet = FREQ_FM_OIRT_END;

  LowEdgeOIRTSet = LowEdgeOIRTSet;
  HighEdgeOIRTSet = FREQ_FM_OIRT_END;

  for (int i = 0; i < EE_PRESETS_CNT; i++) memoryband[i] = EEPROM.readByte(i + EE_PRESETS_BAND_START);
  for (int i = 0; i < EE_PRESETS_CNT; i++) memory[i] = EEPROM.readUInt((i * 4) + EE_PRESETS_START);
  for (int i = 0; i < EE_PRESETS_CNT; i++) memorybw[i] = EEPROM.readByte(i + EE_PRESET_BW_START);
  for (int i = 0; i < EE_PRESETS_CNT; i++) memoryms[i] = EEPROM.readByte(i + EE_PRESET_MS_START);

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
      if (frequency % FREQ_OIRT_STEP_30K != 2) {
        Round30K(frequency_OIRT);
      }
      break;
  }

  if (IsStationEmpty()) memoryposstatus = MEM_DARK; else memoryposstatus = MEM_NORMAL;

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

  RadiotextSprite.createSprite(270, 19);
  FrequencySprite.createSprite(200, 50);
  AdvRadiotextSprite.createSprite(162, 19);
  RDSSprite.createSprite(172, 19);
  SquelchSprite.createSprite(47, 19);

  RadiotextSprite.setTextDatum(TL_DATUM);
  FrequencySprite.setTextDatum(TR_DATUM);
  AdvRadiotextSprite.setTextDatum(TL_DATUM);
  RDSSprite.setTextDatum(TL_DATUM);
  SquelchSprite.setTextDatum(TL_DATUM);
  switch (freqfont) {
    case 0: FrequencySprite.loadFont(FREQFONT0); break;
    case 1: FrequencySprite.loadFont(FREQFONT1); break;
    case 2: FrequencySprite.loadFont(FREQFONT2); break;
    case 3: FrequencySprite.loadFont(FREQFONT3); break;
    case 4: FrequencySprite.loadFont(FREQFONT4); break;
  }

  if (language == LANGUAGE_CHS) {
    RadiotextSprite.loadFont(FONT16_CHS);
    AdvRadiotextSprite.loadFont(FONT16_CHS);
    RDSSprite.loadFont(FONT16_CHS);
    SquelchSprite.loadFont(FONT16_CHS);
  } else {
    RadiotextSprite.loadFont(FONT16);
    AdvRadiotextSprite.loadFont(FONT16);
    RDSSprite.loadFont(FONT16);
    SquelchSprite.loadFont(FONT16);
  }

  if (digitalRead(BWBUTTON) == LOW && digitalRead(ROTARY_BUTTON) == HIGH) {
    if (rotarymode == 0) rotarymode = 1; else rotarymode = 0;
    EEPROM.writeByte(EE_BYTE_ROTARYMODE, rotarymode);
    EEPROM.commit();
    analogWrite(CONTRASTPIN, ContrastSet * 2 + 27);
    tftPrint(0, myLanguage[language][1], 155, 70, ActiveColor, ActiveColorSmooth, 28);
    tftPrint(0, myLanguage[language][2], 155, 130, ActiveColor, ActiveColorSmooth, 28);
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
    tftPrint(0, myLanguage[language][3], 155, 70, ActiveColor, ActiveColorSmooth, 28);
    tftPrint(0, myLanguage[language][2], 155, 130, ActiveColor, ActiveColorSmooth, 28);
    while (digitalRead(MODEBUTTON) == LOW) delay(50);
  }

  if (digitalRead(BANDBUTTON) == LOW) {
    analogWrite(SMETERPIN, 511);
    analogWrite(CONTRASTPIN, ContrastSet * 2 + 27);
    tftPrint(0, myLanguage[language][4], 155, 70, ActiveColor, ActiveColorSmooth, 28);
    tftPrint(0, myLanguage[language][5], 155, 130, ActiveColor, ActiveColorSmooth, 28);
    while (digitalRead(BANDBUTTON) == LOW) delay(50);
    analogWrite(SMETERPIN, 0);
  }

  if (digitalRead(ROTARY_BUTTON) == LOW && digitalRead(BWBUTTON) == HIGH) {
    analogWrite(CONTRASTPIN, ContrastSet * 2 + 27);
    if (optenc == 0) {
      optenc = 1;
      tftPrint(0, myLanguage[language][6], 155, 70, ActiveColor, ActiveColorSmooth, 28);
    } else {
      optenc = 0;
      tftPrint(0, myLanguage[language][7], 155, 70, ActiveColor, ActiveColorSmooth, 28);
    }
    EEPROM.writeByte(EE_BYTE_OPTENC, optenc);
    EEPROM.commit();
    tftPrint(0, myLanguage[language][2], 155, 130, ActiveColor, ActiveColorSmooth, 28);
    while (digitalRead(ROTARY_BUTTON) == LOW) delay(50);
  }

  if (digitalRead(ROTARY_BUTTON) == LOW && digitalRead(BWBUTTON) == LOW) {
    analogWrite(CONTRASTPIN, ContrastSet * 2 + 27);
    DefaultSettings(hardwaremodel);
    tftPrint(0, myLanguage[language][66], 155, 70, ActiveColor, ActiveColorSmooth, 28);
    tftPrint(0, myLanguage[language][2], 155, 130, ActiveColor, ActiveColorSmooth, 28);
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

  if (TEF != 102 && TEF != 205) SetTunerPatch();

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

  if (analogRead(BATTERY_PIN) < 200) batterydetect = false;

  if (wifi) {
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
  if (band > BAND_GAP) {
    radio.setAMCoChannel(amcodect, amcodectcount);
    radio.setAMAttenuation(amrfagc);
  }
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
  radio.setDeemphasis(fmdeemphasis);
  radio.rds.region = region;
  LowLevelInit = true;

  if (ConverterSet >= 200) {
    Wire.beginTransmission(0x12);
    Wire.write(ConverterSet >> 8);
    Wire.write(ConverterSet & (0xFF));
    Wire.endTransmission();
  }

  SelectBand();

  setupmode = false;
  if (edgebeep) radio.tone(50, -5, 2000);
  radio.I2Sin(false);
  if (!usesquelch) radio.setUnMute();
  if (screensaverset) {
    ScreensaverTimerInit();
    ScreensaverTimerSet(screensaverOptions[screensaverset]);
  }
  tottimer = millis();
}

void loop() {
  Communication();

  if (tot != 0) {
    unsigned long totprobe = tot * 60000;
    if (millis() >= tottimer + totprobe) deepSleep();
  }
  if (digitalRead(BANDBUTTON) == LOW ) BANDBUTTONPress();

  if (millis() >= tuningtimer + 200) {
    if (store) {
      detachInterrupt(digitalPinToInterrupt(ROTARY_PIN_A));
      detachInterrupt(digitalPinToInterrupt(ROTARY_PIN_B));
      StoreFrequency();
      store = false;
      attachInterrupt(digitalPinToInterrupt(ROTARY_PIN_A), read_encoder, CHANGE);
      attachInterrupt(digitalPinToInterrupt(ROTARY_PIN_B), read_encoder, CHANGE);
    }
    rdsflagreset = false;
  }

  if (!menu && !afscreen) {
    if (af != 0 && dropout && millis() >= aftimer + 1000) {
      aftimer = millis();
      frequency = radio.TestAF();
      if (freqold != frequency) {
        ShowFreq(0);
        dropout = true;
        if (radio.afmethodB) {
          afmethodBold = true;
          radio.clearRDS(fullsearchrds);
        }
        if (XDRGTKUSB || XDRGTKTCP) DataPrint("T" + String((frequency + ConverterSet * 100) * 10));
        store = true;
      }
    }

    if (band == BAND_FM && af != 0 && radio.rds.correctPI != 0) {
      if ((aftest && millis() >= aftimer + 3000) || ((USN > 250 || WAM > 250) && millis() >= aftimer + 1000)) {
        aftimer = millis();
        aftest = false;
        frequency = radio.TestAF();
        if (freqold != frequency) {
          ShowFreq(0);
          dropout = true;
          if (radio.afmethodB) {
            afmethodBold = true;
            radio.clearRDS(fullsearchrds);
          }
          if (XDRGTKUSB || XDRGTKTCP) DataPrint("T" + String((frequency + ConverterSet * 100) * 10));
          store = true;
        }
      }

      if (band == BAND_FM && millis() >= aftimer + 10000) {
        aftimer = millis();
        if (USN > 150 || WAM > 150) {
          frequency = radio.TestAF();
          if (freqold != frequency) {
            ShowFreq(0);
            dropout = true;
            if (radio.afmethodB) {
              afmethodBold = true;
              radio.clearRDS(fullsearchrds);
            }
            if (XDRGTKUSB || XDRGTKTCP) DataPrint("T" + String((frequency + ConverterSet * 100) * 10));
            store = true;
          }
        }
      }
    }
  }

  if (seek) Seek(direction);

  if ((SStatus / 10 > LowLevelSet) && !LowLevelInit && !menu && band < BAND_GAP) {
    if (!screenmute && !advancedRDS && !afscreen) {
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
            if (((segments + 1) % 6) == 0) tft.fillRect(16 + (2 * segments), 141, 2, 2, ModBarInsignificantColor);
          }
        }
      }
      if (region == REGION_EU) tftPrint(-1, "PI:", 212, 193, ActiveColor, ActiveColorSmooth, 16);
      if (region == REGION_US) {
        tftPrint(-1, "PI:", 212, 184, ActiveColor, ActiveColorSmooth, 16);
        tftPrint(-1, "ID:", 212, 201, ActiveColor, ActiveColorSmooth, 16);
      }
      tftPrint(-1, "PS:", 3, 193, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, "RT:", 3, 221, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, "PTY:", 3, 163, ActiveColor, ActiveColorSmooth, 16);
      if (!showmodulation) tft.drawLine(20, 143, 204, 143, GreyoutColor); else tft.drawLine(20, 143, 204, 143, TFT_DARKGREY);
    }
    LowLevelInit = true;
  }

  if ((SStatus / 10 <= LowLevelSet) && band < BAND_GAP) {
    if (LowLevelInit && !menu) {
      if (!screenmute && !afscreen && !advancedRDS) {
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
        if (region == REGION_EU) tftPrint(-1, "PI:", 212, 193, GreyoutColor, BackgroundColor, 16);
        if (region == REGION_US) {
          tftPrint(-1, "PI:", 212, 184, GreyoutColor, BackgroundColor, 16);
          tftPrint(-1, "ID:", 212, 201, GreyoutColor, BackgroundColor, 16);
        }
        tftPrint(-1, "PS:", 3, 193, GreyoutColor, BackgroundColor, 16);
        tftPrint(-1, "RT:", 3, 221, GreyoutColor, BackgroundColor, 16);
        tftPrint(-1, "PTY:", 3, 163, GreyoutColor, BackgroundColor, 16);
        tft.drawLine(20, 143, 204, 143, GreyoutColor);
        tft.drawBitmap(122, 5, RDSLogo, 35, 22, GreyoutColor);
      }
      LowLevelInit = false;
    }

    if (!menu && (screenmute || radio.rds.correctPI != 0)) readRds();
    if (millis() >= lowsignaltimer + 300) {
      lowsignaltimer = millis();
      if (af || (!screenmute || (screenmute && (XDRGTKTCP || XDRGTKUSB)))) {
        if (band < BAND_GAP) {
          radio.getStatus(SStatus, USN, WAM, OStatus, BW, MStatus, CN);
        } else {
          radio.getStatusAM(SStatus, USN, WAM, OStatus, BW, MStatus, CN);
        }
      }
      if (!menu) {
        doSquelch();
        GetData();
      }
    }

  } else {
    if (af || (!screenmute || (screenmute && (XDRGTKTCP || XDRGTKUSB)))) {
      if (band < BAND_GAP) {
        radio.getStatus(SStatus, USN, WAM, OStatus, BW, MStatus, CN);
      } else {
        radio.getStatusAM(SStatus, USN, WAM, OStatus, BW, MStatus, CN);
      }
    }
    if (!menu) {
      doSquelch();
      if (millis() >= tuningtimer + 200) readRds();
      GetData();
      if (!screenmute && !afscreen && !advancedRDS) ShowModLevel();
    }
  }

  if (menu && menuopen && menupage == FMSETTINGS && menuoption == ITEM4) {
    if (band < BAND_GAP) radio.getStatus(SStatus, USN, WAM, OStatus, BW, MStatus, CN); else radio.getStatusAM(SStatus, USN, WAM, OStatus, BW, MStatus, CN);
    if (millis() >= lowsignaltimer + 500 || change) {
      lowsignaltimer = millis();
      change = false;
      if (SStatus > SStatusold || SStatus < SStatusold) {
        if (SStatusold / 10 != SStatus / 10) tftReplace(1, String(SStatusold / 10), String(SStatus / 10), 140, 149, PrimaryColor, PrimaryColorSmooth, 48);
        tftReplace(1, "." + String(abs(SStatusold % 10)), "." + String(abs(SStatus % 10)), 160, 149, PrimaryColor, PrimaryColorSmooth, 28);
        SStatusold = SStatus;
      }
    }
  }

  if (rotary == -1) {
    tottimer = millis();
    if (screensavertriggered) {
      if (!touchrotating) {
        rotary = 0;
        WakeToSleep(REVERSE);
      } else {
        if (BWtune) doBWtuneUp(); else KeyUp();
      }
    } else {
      if (BWtune) doBWtuneUp(); else KeyUp();
      if (screensaverset && !menu && !screensavertriggered) ScreensaverTimerRestart();
    }
  }

  if (rotary == 1) {
    tottimer = millis();
    if (screensavertriggered) {
      if (!touchrotating) {
        rotary = 0;
        WakeToSleep(REVERSE);
      } else {
        if (BWtune) doBWtuneDown(); else KeyDown();
      }
    } else {
      if (BWtune) doBWtuneDown(); else KeyDown();
      if (screensaverset && !menu && !screensavertriggered) ScreensaverTimerRestart();
    }
  }

  if (digitalRead(ROTARY_BUTTON) == LOW) {
    tottimer = millis();
    if (screensavertriggered && !touchrotating) WakeToSleep(REVERSE);
    if (!afscreen) ButtonPress();
  }

  if (digitalRead(MODEBUTTON) == LOW) {
    tottimer = millis();
    if (screensavertriggered && !touchrotating) WakeToSleep(REVERSE);
    if (!screenmute) ModeButtonPress();
  }

  if (digitalRead(BWBUTTON) == HIGH && BWtune) BWtune = false;

  if (digitalRead(BWBUTTON) == LOW && !BWtune) {
    tottimer = millis();
    if (screensavertriggered && !touchrotating) WakeToSleep(REVERSE);
    if (!screenmute && !afscreen) BWButtonPress();
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
}

void GetData() {
  if (!afscreen) {
    showCT();
    ShowSignalLevel();
  }

  if (band < BAND_GAP && !menu) {
    if (advancedRDS && !afscreen && !screenmute) ShowAdvancedRDS();
    if (afscreen && !screenmute) ShowAFEON();
    if (!afscreen) {
      ShowErrors();
      showPTY();
      showECC();
      showRadioText();
      if (millis() >= tuningtimer + 200) doAF();
    }
    showPI();
    showPS();
  }

  if (!screenmute) {
    ShowRSSI();
    ShowOffset();
    ShowStereoStatus();
    ShowBW();
    updateCodetect();
    if (millis() >= tuningtimer + 200) ShowBattery();
  }
}

void WakeToSleep(bool yes) {
  if (yes) {
    screensavertriggered = true;
    switch (poweroptions) {
      case LCD_OFF:
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
      case LCD_OFF:
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
      if (bandFM == FM_BAND_OIRT) bandforbidden = 1; else bandforbidden = 0;
      break;
    case BAND_OIRT:
      if (bandFM == FM_BAND_FM) bandforbidden = 1; else bandforbidden = 0;
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
        } else if (frequency_OIRT < FREQ_FM_OIRT_START) {
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
    case FM_BAND_NONE:
      ToggleBand(band);
      SelectBand();
      break;
  }
}

void CheckBandForbiddenAM () {
  switch (band) {
    case BAND_LW:
      if (bandAM == AM_BAND_MW_SW || bandAM == AM_BAND_MW || bandAM == AM_BAND_SW) bandforbidden = 1; else bandforbidden = 0;
      break;
    case BAND_MW:
      if (bandAM == AM_BAND_LW_SW || bandAM == AM_BAND_LW || bandAM == AM_BAND_SW) bandforbidden = 1; else bandforbidden = 0;
      break;
    case BAND_SW:
      if (bandAM == AM_BAND_LW_MW || bandAM == AM_BAND_LW || bandAM == AM_BAND_MW) bandforbidden = 1; else bandforbidden = 0;
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
    case AM_BAND_NONE:
      ToggleBand(band);
      SelectBand();
      break;
  }
}

void AMjumptoFM() {
  if (bandFM != FM_BAND_NONE) {
    if (bandFM == FM_BAND_FM) band = BAND_FM; else band = BAND_OIRT;
  } else {
    // do nothing
  }
}

void FMjumptoAM() {
  if (bandAM == AM_BAND_ALL || bandAM == AM_BAND_LW_MW || bandAM == AM_BAND_LW_SW || bandAM == AM_BAND_LW) {
    band = BAND_LW;
    if (stepsize > 3) stepsize = 3;
  } else if (bandAM == AM_BAND_MW_SW || bandAM == AM_BAND_MW) {
    band = BAND_MW;
  } else if (bandAM == AM_BAND_SW) {
    band = BAND_SW;
  }
}

void ToggleBand(byte nowBand) {
  switch (nowBand) {
    case BAND_LW:
      if (bandAM == AM_BAND_LW_MW || bandAM == AM_BAND_ALL) {
        band = BAND_MW;
      } else if (bandAM == AM_BAND_LW_SW) {
        band = BAND_SW;
      } else if (bandAM == AM_BAND_LW || bandAM == AM_BAND_NONE) {
        AMjumptoFM();
      }
      break;
    case BAND_MW:
      if (bandAM == AM_BAND_MW_SW || bandAM == AM_BAND_ALL) {
        band = BAND_SW;
      } else if (bandAM == AM_BAND_LW_MW) {
        if (bandFM != FM_BAND_NONE) {
          if (bandFM == FM_BAND_FM) band = BAND_FM; else band = BAND_OIRT;
        } else {
          band = BAND_LW;
        }
      } else if (bandAM == AM_BAND_MW || bandAM == AM_BAND_NONE) {
        AMjumptoFM();
      }
      break;
    case BAND_SW:
      if (bandFM != FM_BAND_NONE) {
        if (bandFM == FM_BAND_FM) band = BAND_FM; else band = BAND_OIRT;
      } else {
        if (bandAM == AM_BAND_LW_SW || bandAM == AM_BAND_ALL) {
          band = BAND_LW;
        } else if (bandAM == AM_BAND_MW_SW) {
          band = BAND_MW;
        } else if (bandAM == AM_BAND_SW || bandAM == AM_BAND_NONE) {
          AMjumptoFM();
        }
      }
      break;
    case BAND_OIRT:
      if (bandFM == FM_BAND_ALL || bandFM == FM_BAND_FM) {
        band = BAND_FM;
      } else if (bandFM == FM_BAND_OIRT) {
        if (bandAM != AM_BAND_NONE) {
          FMjumptoAM();
        } else {
          // do nothing
        }
      }
      break;
    case BAND_FM:
      if (bandAM != AM_BAND_NONE) {
        FMjumptoAM();
      } else {
        if (bandFM == FM_BAND_OIRT || bandFM == FM_BAND_ALL) {
          band = BAND_OIRT;
        } else if (bandFM == FM_BAND_FM) {
          // do nothing
        }
      }
      break;
  }
}

void BANDBUTTONPress() {
  if (!usesquelch) radio.setUnMute();
  if (afscreen) {
    BuildAdvancedRDS();
  } else {
    unsigned long counterold = millis();
    unsigned long counter = millis();
    if (!menu) {
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
            if (XDRGTKUSB || XDRGTKTCP) {
              if (band == BAND_FM) DataPrint("M0\nT" + String(frequency * 10)); else if (band == BAND_OIRT) DataPrint("M0\nT" + String(frequency_OIRT * 10)); else DataPrint("M1\nT" + String(frequency_AM));
            }
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
        frequency_AM = MWLowEdgeSet;
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
    if (!screenmute) tft.drawBitmap(92, 4, Speaker, 26, 22, GreyoutColor);
    if (tunemode == TUNE_MI_BAND && band != BAND_SW) tunemode = TUNE_MAN;
    BWreset = true;
    BWset = BWsetAM;
    switch (band) {
      case BAND_LW: freqold = frequency_LW; frequency_AM = frequency_LW; break;
      case BAND_MW: freqold = frequency_MW; frequency_AM = frequency_MW; break;
      case BAND_SW: freqold = frequency_SW; frequency_AM = frequency_SW; break;
    }
    LimitAMFrequency();
    if (!externaltune) CheckBandForbiddenAM();
    radio.SetFreqAM(frequency_AM);
    radio.setAMAttenuation(amrfagc);
    radio.setAMCoChannel(amcodect, amcodectcount);
    doBW();
    if (!screenmute) {
      BuildDisplay();
      if (region == REGION_EU) tftPrint(-1, "PI:", 212, 193, GreyoutColor, BackgroundColor, 16);
      if (region == REGION_US) {
        tftPrint(-1, "PI:", 212, 184, GreyoutColor, BackgroundColor, 16);
        tftPrint(-1, "ID:", 212, 201, GreyoutColor, BackgroundColor, 16);
      }

      tftPrint(-1, "PS:", 3, 193, GreyoutColor, BackgroundColor, 16);
      tftPrint(-1, "RT:", 3, 221, GreyoutColor, BackgroundColor, 16);
      tftPrint(-1, "PTY:", 3, 163, GreyoutColor, BackgroundColor, 16);
      tft.drawBitmap(122, 5, RDSLogo, 35, 22, GreyoutColor);
      tft.drawRoundRect(248, 56, 32, 20, 5, GreyoutColor);
      tftPrint(0, "iMS", 265, 59, GreyoutColor, BackgroundColor, 16);
      tft.drawRoundRect(286, 56, 32, 20, 5, GreyoutColor);
      tftPrint(0, "EQ", 303, 59, GreyoutColor, BackgroundColor, 16);
    }
  } else {
    if (tunemode == TUNE_MI_BAND) tunemode = TUNE_MAN;
    radio.power(0);
    delay(50);
    if (band == BAND_FM) radio.SetFreq(frequency);
    if (band == BAND_OIRT) radio.SetFreq(frequency_OIRT);
    PIold = "";
    PSold = "";
    PTYold = "";
    RTold = "";
    BWreset = true;
    BWset = BWsetFM;
    radio.clearRDS(fullsearchrds);
    freqold = frequency_AM;
    if (!externaltune) CheckBandForbiddenFM();
    doBW();
    if (!screenmute) BuildDisplay();
  }
}

void BWButtonPress() {
  if (!usesquelch) radio.setUnMute();
  if (!menu) {
    seek = false;
    if (!screenmute) tft.drawBitmap(92, 4, Speaker, 26, 22, GreyoutColor);
    unsigned long counterold = millis();
    unsigned long counter = millis();
    while (digitalRead(BWBUTTON) == LOW && counter - counterold <= 1000) counter = millis();

    if (counter - counterold < 1000) {
      if (band == BAND_FM || band == BAND_OIRT) {
        doStereoToggle();
      } else {
        BWset++;
        doBW();
        BWtune = true;
      }
    } else {
      BWset++;
      doBW();
      BWtune = true;
    }
    if (screensaverset) {
      ScreensaverTimerRestart();
    }
    delay(100);
  }
}

void doStereoToggle() {
  if (StereoToggle) {
    if (!screenmute) {
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
    if (!screenmute) {
      tft.drawSmoothCircle(71, 15, 10, BackgroundColor, BackgroundColor);
      tft.drawSmoothCircle(71, 15, 9, BackgroundColor, BackgroundColor);
      tft.drawSmoothCircle(66, 15, 10, GreyoutColor, BackgroundColor);
      tft.drawSmoothCircle(66, 15, 9, GreyoutColor, BackgroundColor);
      tft.drawSmoothCircle(76, 15, 10, GreyoutColor, BackgroundColor);
      tft.drawSmoothCircle(76, 15, 9, GreyoutColor, BackgroundColor);
    }
    radio.setMono(false);
    Stereostatusold = false;
    StereoToggle = true;
  }
  EEPROM.writeByte(EE_BYTE_STEREO, StereoToggle);
  EEPROM.commit();
}

void ModeButtonPress() {
  if (!usesquelch) radio.setUnMute();
  if (advancedRDS) {
    BuildDisplay();
    ScreensaverTimerReopen();
  } else if (afscreen) {
    if (afpagenr == 1) afpagenr = 2; else if (afpagenr == 2 && afpage) afpagenr = 3; else afpagenr = 1;
    BuildAFScreen();
  } else {
    if (!menu) {
      seek = false;
      if (!screenmute) tft.drawBitmap(92, 4, Speaker, 26, 22, GreyoutColor);
      memorystore = false;
      unsigned long counterold = millis();
      unsigned long counter = millis();
      while (digitalRead(MODEBUTTON) == LOW && counter - counterold <= 1000) counter = millis();

      if (counter - counterold <= 1000) {
        doTuneMode();
        if (screensaverset) {
          ScreensaverTimerRestart();
        }
      } else {
        if (XDRGTKUSB || XDRGTKTCP) {
          ShowFreq(1);
          tftPrint(-1, myLanguage[language][86], 70, 68, ActiveColor, ActiveColorSmooth, 28);
          delay(1000);
          tftPrint(-1, myLanguage[language][86], 70, 68, BackgroundColor, BackgroundColor, 28);
          ShowFreq(0);
        } else {
          if (!menu) {
            menuoption = ITEM1;
            menupage = INDEX;
            menuitem = 0;
            BuildMenu();
            menu = true;
            ScreensaverTimerSet(OFF);
          }
        }
      }
    } else {
      if (menuopen && !submenu) {
        ButtonPress();
      } else if (!submenu) {
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
        menu = false;
        menuopen = false;
        LowLevelInit = true;
        EEPROM.writeByte(EE_BYTE_VOLSET, VolSet);
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
        EEPROM.writeByte(EE_BYTE_LOWLEVELSET, LowLevelSet);
        EEPROM.writeByte(EE_BYTE_REGION, region);
        EEPROM.writeByte(EE_BYTE_RDS_UNDERSCORE, radio.rds.underscore);
        EEPROM.writeByte(EE_BYTE_USBMODE, USBmode);
        EEPROM.writeByte(EE_BYTE_WIFI, wifi);
        EEPROM.writeByte(EE_BYTE_SUBNETCLIENT, subnetclient);
        EEPROM.writeByte(EE_BYTE_SHOWSWMIBAND, showSWMIBand);
        EEPROM.writeByte(EE_BYTE_RDS_FILTER, radio.rds.filter);
        EEPROM.writeByte(EE_BYTE_RDS_PIERRORS, radio.rds.pierrors);
        EEPROM.writeByte(EE_BYTE_USESQUELCH, usesquelch);
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
        EEPROM.writeByte(EE_BYTE_AM_CO_DECT, amcodect);
        EEPROM.writeByte(EE_BYTE_AM_CO_DECT_COUNT, amcodectcount);
        EEPROM.writeByte(EE_BYTE_AM_RF_AGC, amrfagc);
        EEPROM.writeByte(EE_BYTE_SORTAF, radio.rds.sortaf);
        EEPROM.writeByte(EE_BYTE_STATIONLISTID, stationlistid);
        EEPROM.writeByte(EE_BYTE_FM_DEEMPHASIS, fmdeemphasis);
        EEPROM.writeByte(EE_BYTE_FASTPS, radio.rds.fastps);
        EEPROM.writeByte(EE_BYTE_TOT, tot);
        EEPROM.writeByte(EE_BYTE_MWREGION, mwstepsize);
        EEPROM.writeByte(EE_BYTE_SPISPEED, spispeed);
        EEPROM.writeByte(EE_BYTE_AMSCANSENS, amscansens);
        EEPROM.writeByte(EE_BYTE_FMSCANSENS, fmscansens);
        EEPROM.writeByte(EE_BYTE_FREQFONT, freqfont);
        EEPROM.writeByte(EE_BYTE_SKIN, CurrentSkin);
        EEPROM.writeByte(EE_BYTE_XDRGTKMUTE, XDRGTKMuteScreen);
        EEPROM.commit();
        if (af == 2) radio.rds.afreg = true; else radio.rds.afreg = false;
        if (!usesquelch) radio.setUnMute();
        Serial.end();
        if (wifi) remoteip = IPAddress (WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], subnetclient);
        if (USBmode) Serial.begin(19200); else Serial.begin(115200);
        RadiotextSprite.unloadFont();
        AdvRadiotextSprite.unloadFont();
        RDSSprite.unloadFont();
        SquelchSprite.unloadFont();
        FrequencySprite.unloadFont();
        if (language == LANGUAGE_CHS) {
          RadiotextSprite.loadFont(FONT16_CHS);
          AdvRadiotextSprite.loadFont(FONT16_CHS);
          RDSSprite.loadFont(FONT16_CHS);
          SquelchSprite.loadFont(FONT16_CHS);
        } else {
          RadiotextSprite.loadFont(FONT16);
          AdvRadiotextSprite.loadFont(FONT16);
          RDSSprite.loadFont(FONT16);
          SquelchSprite.loadFont(FONT16);
        }
        switch (freqfont) {
          case 0: FrequencySprite.loadFont(FREQFONT0); break;
          case 1: FrequencySprite.loadFont(FREQFONT1); break;
          case 2: FrequencySprite.loadFont(FREQFONT2); break;
          case 3: FrequencySprite.loadFont(FREQFONT3); break;
          case 4: FrequencySprite.loadFont(FREQFONT4); break;
        }

        BuildDisplay();
        ShowSignalLevel();
        ShowBW();
        MWLowEdgeSet = mwstepsize == false ? FREQ_MW_LOW_EDGE_MIN_9K : FREQ_MW_LOW_EDGE_MIN_10K;
        MWHighEdgeSet = mwstepsize == false ? FREQ_MW_HIGH_EDGE_MAX_9K : FREQ_MW_HIGH_EDGE_MAX_10K;
        doBandSelectionFM();
        doBandSelectionAM();
        ScreensaverTimerSet(screensaverOptions[screensaverset]);
        if (screensaverset) ScreensaverTimerRestart();
      } else {
        if (submenu) {
          if (menuopen) {
            if (menupage == CONNECTIVITY && menuoption == ITEM2 && wifi) {
              tryWiFi();
              delay(2000);
            }
            if (menupage == DISPLAYSETTINGS && menuoption == ITEM5) {
              doTheme();
            }
            menuopen = false;
          }
          submenu = false;
          menuoption = ITEM1;
          menupage = INDEX;
          menuitem = 0;
          BuildMenu();
        }
      }
    }
  }
  while (digitalRead(MODEBUTTON) == LOW) delay(50);
  delay(100);
}

void ShowStepSize() {
  if (!advancedRDS) {
    tft.fillRect(191, 38, 15, 4, GreyoutColor);
    tft.fillRect(222, 38, 15, 4, GreyoutColor);
    if (band < BAND_GAP) tft.fillRect(113, 38, 15, 4, GreyoutColor); else if (band != BAND_LW && band != BAND_MW) tft.fillRect(129, 38, 15, 4, GreyoutColor);
    if (band < BAND_GAP) tft.fillRect(144, 38, 15, 4, GreyoutColor); else tft.fillRect(159, 38, 15, 4, GreyoutColor);
    if (stepsize == 1) tft.fillRect(222, 38, 15, 4, InsignificantColor);
    if (stepsize == 2) tft.fillRect(191, 38, 15, 4, InsignificantColor);
    if (stepsize == 3) {
      if (band < BAND_GAP) tft.fillRect(144, 38, 15, 4, InsignificantColor); else tft.fillRect(159, 38, 15, 4, InsignificantColor);
    }
    if (stepsize == 4) {
      if (band < BAND_GAP) tft.fillRect(113, 38, 15, 4, InsignificantColor); else tft.fillRect(129, 38, 15, 4, InsignificantColor);
    }
  }
}

void Round30K(unsigned int freq) {
  if (freq % FREQ_OIRT_STEP_30K == 1) {
    frequency_OIRT = (freq + 1);
  } else if (freq % FREQ_OIRT_STEP_30K == 0) {
    frequency_OIRT = (freq - 1);
  }
}

void Round50K(unsigned int freq) {
  if (freq % 10 < 3) {
    frequency = (freq - freq % 10);
  } else if (freq % 10 > 2 && freq % 10 < 8) {
    frequency = (freq - (freq % 10 - 5));
  } else if (freq % 10 > 7) {
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

void Round200K(unsigned int freq) {
  frequency = (freq / 10) * 10;

  if (freq % 10 >= 5) frequency += 10;
  if ((frequency / 100) % 2 == 0) frequency += 10;
  if (frequency > 10800) frequency = 10790;
  if (frequency % 20 == 0 && (frequency / 10) % 2 == 0) frequency -= 10;
}

void Round5K(unsigned int freqAM) {
  if (freqAM % 10 < 3) {
    frequency_AM = (freqAM - freqAM % 10);
  } else if (freqAM % 10 > 2 && freqAM % 10 < 8) {
    frequency_AM = (freqAM - (freqAM % 10 - 5));
  } else if (freqAM % 10 > 7) {
    frequency_AM = (freqAM - (freqAM % 10) + 10);
  }
}

void RoundStep() {
  if (band == BAND_FM) {
    unsigned int freq = frequency;
    switch (fmdefaultstepsize) {
      case 0: Round50K(freq); break;
      case 1: Round100K(freq); break;
      case 2: Round200K(freq); break;
    }
    radio.SetFreq(frequency);
  } else if (band == BAND_OIRT) {
    Round30K(frequency_OIRT);
    radio.SetFreq(frequency_OIRT);
  } else {
    if (band == BAND_MW) {
      unsigned int freq = frequency_AM / (mwstepsize == false ? FREQ_MW_STEP_9K : FREQ_MW_STEP_10K);
      frequency_AM = freq * (mwstepsize == false ? FREQ_MW_STEP_9K : FREQ_MW_STEP_10K);
      radio.SetFreqAM(frequency_AM);
    } else if (band == BAND_SW) {
      Round5K(frequency_AM);
      radio.SetFreqAM(frequency_AM);
    }
  }

  while (digitalRead(ROTARY_BUTTON) == LOW) delay(50);

  if (band == BAND_FM) {
    EEPROM.writeUInt(EE_UINT16_FREQUENCY_FM, frequency);
  } else if (band == BAND_OIRT) {
    EEPROM.writeUInt(EE_UINT16_FREQUENCY_OIRT, frequency_OIRT);
  } else {
    EEPROM.writeUInt(EE_UINT16_FREQUENCY_AM, frequency_AM);
  }
  EEPROM.commit();
}

void ButtonPress() {
  if (!usesquelch) radio.setUnMute();
  if (advancedRDS) BuildDisplay();
  if (!menu) {
    if (tunemode == TUNE_MEM) {
      if (!memorystore) {
        memorystore = true;
        if (!IsStationEmpty()) memoryposstatus = MEM_EXIST;
        else memoryposstatus = MEM_NORMAL;
        ShowMemoryPos();

        ShowTuneMode();
      } else {
        memorystore = false;
        EEPROM.writeByte(memorypos + EE_PRESETS_BAND_START, band);
        EEPROM.writeByte(memorypos + EE_PRESET_BW_START, BWset);
        EEPROM.writeByte(memorypos + EE_PRESET_MS_START, StereoToggle);
        if (band == BAND_FM) {
          EEPROM.writeUInt((memorypos * 4) + EE_PRESETS_START, frequency);
        } else if (band == BAND_OIRT) {
          EEPROM.writeUInt((memorypos * 4) + EE_PRESETS_START, frequency_OIRT);
        } else if (band == BAND_LW) {
          EEPROM.writeUInt((memorypos * 4) + EE_PRESETS_START, frequency_LW);
        } else if (band == BAND_MW) {
          EEPROM.writeUInt((memorypos * 4) + EE_PRESETS_START, frequency_MW);
        } else {
          EEPROM.writeUInt((memorypos * 4) + EE_PRESETS_START, frequency_SW);
        }
        EEPROM.commit();
        memoryband[memorypos] = band;
        memorybw[memorypos] = BWset;
        memoryms[memorypos] = StereoToggle;
        if (band == BAND_FM) {
          memory[memorypos] = frequency;
        } else if (band == BAND_OIRT) {
          memory[memorypos] = frequency_OIRT;
        } else if (band == BAND_LW) {
          memory[memorypos] = frequency_LW;
        } else if (band == BAND_MW) {
          memory[memorypos] = frequency_MW;
        } else {
          memory[memorypos] = frequency_SW;
        }
        ShowTuneMode();
        if (memoryposstatus == MEM_DARK || memoryposstatus == MEM_EXIST) {
          memoryposstatus = MEM_NORMAL;
          ShowMemoryPos();
        }
      }
    } else {
      seek = false;
      if (!screenmute) tft.drawBitmap(92, 4, Speaker, 26, 22, GreyoutColor);
      unsigned long counterold = millis();
      unsigned long counter = millis();
      while (digitalRead(ROTARY_BUTTON) == LOW && counter - counterold <= 1000) counter = millis();

      if (counter - counterold < 1000) {
        if (tunemode == TUNE_MAN) {
          stepsize++;
          if (band == BAND_SW || band < BAND_GAP) {
            if (stepsize > 4) stepsize = 0;
          } else {
            if (stepsize > 3) stepsize = 0;
          }

          if (!screenmute) ShowStepSize();

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
          if (XDRGTKUSB || XDRGTKTCP) DataPrint("G" + String(!EQset) + String(!iMSset) + "\n");
        } else {
          if (band == BAND_SW && tunemode != TUNE_MEM) {
            nowToggleSWMIBand = !nowToggleSWMIBand;
            tunemode = TUNE_MAN;
            EEPROM.writeByte(EE_BYTE_BANDAUTOSW, nowToggleSWMIBand);
            EEPROM.commit();
            if (!screenmute) {
              tftPrint(0, "AUTO", 22, 60, BackgroundColor, BackgroundColor, 16);
              tftPrint(0, "BAND", 22, 60, BackgroundColor, BackgroundColor, 16);
            }
            doTuneMode();
            ShowTuneMode();
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
    if (!menu) {
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
          if (!memorystore) {
            DoMemoryPosTune();
          } else {
            if (!IsStationEmpty()) memoryposstatus = MEM_EXIST;
            else memoryposstatus = MEM_NORMAL;
          }
          ShowMemoryPos();
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
      if (XDRGTKUSB || XDRGTKTCP) {
        if (band == BAND_FM) DataPrint("M0\nT" + String(frequency * 10)); else if (band == BAND_OIRT) DataPrint("M0\nT" + String(frequency_OIRT * 10)); else DataPrint("M1\nT" + String(frequency_AM));
      }
      if (!memorystore) {
        radio.clearRDS(fullsearchrds);
        ShowFreq(0);
        store = true;
      }
    } else {
      MenuUp();
    }
  }
}

void KeyDown() {
  rotary = 0;
  if (!afscreen) {
    if (!menu) {
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
          if (!memorystore) {
            DoMemoryPosTune();
          } else {
            if (!IsStationEmpty()) memoryposstatus = MEM_EXIST;
            else memoryposstatus = MEM_NORMAL;
          }
          ShowMemoryPos();
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
      if (XDRGTKUSB || XDRGTKTCP) {
        if (band == BAND_FM) DataPrint("M0\nT" + String(frequency * 10)); else if (band == BAND_OIRT) DataPrint("M0\nT" + String(frequency_OIRT * 10)); else DataPrint("M1\nT" + String(frequency_AM));
      }
      if (!memorystore) {
        radio.clearRDS(fullsearchrds);
        ShowFreq(0);
        store = true;
      }
    } else {
      MenuDown();
    }
  }
}

bool IsStationEmpty() {
  if (memoryband[memorypos] == BAND_FM && memory[memorypos] == EE_PRESETS_FREQUENCY) {
    return true;
  }
  return false;
}

void ShowMemoryPos() {
  if (tunemode == TUNE_MEM) {
    int memposcolor = 0;
    int memposcolorsmooth = 0;
    switch (memoryposstatus) {
      case MEM_DARK:
        memposcolor = InsignificantColor;
        memposcolorsmooth = InsignificantColorSmooth;
        break;

      case MEM_NORMAL:
        memposcolor = PrimaryColor;
        memposcolorsmooth = PrimaryColorSmooth;
        break;

      case MEM_EXIST:
        memposcolor = SignificantColor;
        memposcolorsmooth = SignificantColorSmooth;
        break;
    }
    if (advancedRDS) tftReplace(-1, String(memoryposold + 1), String(memorypos + 1), 215, 36, SecondaryColor, SecondaryColorSmooth, 16); else tftReplace(-1, String(memoryposold + 1), String(memorypos + 1), 50, 32, memposcolor, memposcolorsmooth, 16);
    memoryposold = memorypos;
  } else {
    if (advancedRDS) tftPrint(-1, String(memorypos + 1), 215, 36, BackgroundColor, BackgroundColor, 16); else tftPrint(-1, String(memorypos + 1), 50, 32, BackgroundColor, BackgroundColor, 16);
  }
}

void DoMemoryPosTune() {
  // Process empty stations
  if (IsStationEmpty()) {
    memoryposstatus = MEM_DARK;
    return;
  } else {
    memoryposstatus = MEM_NORMAL;
  }

  if (band != memoryband[memorypos]) {
    band = memoryband[memorypos];
    SelectBand();
  } else {
    band = memoryband[memorypos];
  }

  if (band == BAND_FM) {
    frequency = memory[memorypos];
    radio.SetFreq(frequency);
  } else if (band == BAND_OIRT) {
    frequency_OIRT = memory[memorypos];
    radio.SetFreq(frequency_OIRT);
  } else if (band == BAND_LW) {
    frequency_LW = memory[memorypos];
    radio.SetFreqAM(frequency_LW);
  } else if (band == BAND_MW) {
    frequency_MW = memory[memorypos];
    radio.SetFreqAM(frequency_MW);
  } else if (band == BAND_SW) {
    frequency_SW = memory[memorypos];
    radio.SetFreqAM(frequency_SW);
  }
  ShowFreq(0);

  if (band == BAND_FM || band == BAND_OIRT) {
    StereoToggle = memoryms[memorypos];
    if (!StereoToggle) {
      Stereostatusold = false;
      tft.drawSmoothCircle(66, 15, 10, BackgroundColor, BackgroundColor);
      tft.drawSmoothCircle(66, 15, 9, BackgroundColor, BackgroundColor);
      tft.drawSmoothCircle(76, 15, 10, BackgroundColor, BackgroundColor);
      tft.drawSmoothCircle(76, 15, 9, BackgroundColor, BackgroundColor);
      tft.drawSmoothCircle(71, 15, 10, SecondaryColor, SecondaryColorSmooth);
      tft.drawSmoothCircle(71, 15, 9, SecondaryColor, SecondaryColorSmooth);
    } else {
      Stereostatusold = false;
      tft.drawSmoothCircle(71, 15, 10, BackgroundColor, BackgroundColor);
      tft.drawSmoothCircle(71, 15, 9, BackgroundColor, BackgroundColor);
      tft.drawSmoothCircle(66, 15, 10, GreyoutColor, BackgroundColor);
      tft.drawSmoothCircle(66, 15, 9, GreyoutColor, BackgroundColor);
      tft.drawSmoothCircle(76, 15, 10, GreyoutColor, BackgroundColor);
      tft.drawSmoothCircle(76, 15, 9, GreyoutColor, BackgroundColor);
    }
  }

  BWset = memorybw[memorypos];
  doBW();
  BWtune = true;

}

void ShowFreq(int mode) {
  if (!setupmode) {
    if (band != BAND_FM && band != BAND_OIRT) {
      if (freqold < 2000 && frequency_AM >= 2000 && stepsize == 0) if (frequency_AM != 27000 && freqold != 144) radio.SetFreqAM(2000);
      if (freqold >= 2000 && frequency_AM < 2000 && stepsize == 0) if (frequency_AM != 144 && freqold != 27000) radio.SetFreqAM(1998);
    }
  }

  detachInterrupt(digitalPinToInterrupt(ROTARY_PIN_A));
  detachInterrupt(digitalPinToInterrupt(ROTARY_PIN_B));

  if (band > BAND_GAP) {
    switch (band) {
      case BAND_LW: frequency_AM = frequency_LW; break;
      case BAND_MW: frequency_AM = frequency_MW; break;
      case BAND_SW: frequency_AM = frequency_SW; break;
    }

    if (!screenmute) {
      FrequencySprite.fillSprite(BackgroundColor);
      FrequencySprite.setTextColor(FreqColor, FreqColorSmooth, false);
      FrequencySprite.drawString(String(frequency_AM) + " ", 218, -6);
      FrequencySprite.setTextColor(SecondaryColor, SecondaryColorSmooth, false);
      FrequencySprite.setTextDatum(TL_DATUM);
      FrequencySprite.loadFont(FONT16);
    }

    if (band == BAND_SW && showSWMIBand) {
      DivdeSWMIBand();
      updateSWMIBand();
    }

    if (!screenmute) {
      FrequencySprite.pushSprite(46, 46);
      FrequencySprite.setTextDatum(TR_DATUM);

      switch (freqfont) {
        case 0: FrequencySprite.loadFont(FREQFONT0); break;
        case 1: FrequencySprite.loadFont(FREQFONT1); break;
        case 2: FrequencySprite.loadFont(FREQFONT2); break;
        case 3: FrequencySprite.loadFont(FREQFONT3); break;
        case 4: FrequencySprite.loadFont(FREQFONT4); break;
      }
    }

    freqold = frequency_AM;
  } else {
    unsigned int freq = 0;
    if (band == BAND_FM) freq = frequency + ConverterSet * 100;
    if (band == BAND_OIRT) freq = frequency_OIRT;

    if (!screenmute) {
      if (advancedRDS) {
        for (int i = 0; i < 33; i++) tft.fillCircle((6 * i) + 10, 133, 2, GreyoutColor);
        tftReplace(1, String(freqold / 100) + "." + (freqold % 100 < 10 ? "0" : "") + String(freqold % 100), String(freq / 100) + "." + (freq % 100 < 10 ? "0" : "") + String(freq % 100), 273, 35, PrimaryColor, PrimaryColorSmooth, 16);
        freqold = freq;
      } else if (afscreen) {
        tftReplace(1, String(freqold / 100) + "." + (freqold % 100 < 10 ? "0" : "") + String(freqold % 100) + " MHz", String(freq / 100) + "." + (freq % 100 < 10 ? "0" : "") + String(freq % 100), 290, 201, BWAutoColor, BWAutoColorSmooth, 16);
        freqold = freq;
      } else {
        if (mode == 0) {
          FrequencySprite.fillSprite(BackgroundColor);
          FrequencySprite.setTextColor(FreqColor, FreqColorSmooth, false);
          FrequencySprite.drawString(String(freq / 100) + "." + (freq % 100 < 10 ? "0" : "") + String(freq % 100) + " ", 218, -6);
          FrequencySprite.pushSprite(46, 46);
          freqold = freq;
        } else if (mode == 1) {
          FrequencySprite.fillSprite(BackgroundColor);
          FrequencySprite.pushSprite(46, 46);
        }
      }
    }
  }
  attachInterrupt(digitalPinToInterrupt(ROTARY_PIN_A), read_encoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ROTARY_PIN_B), read_encoder, CHANGE);

  rdsreset = true;
  licold = 254;
  ECCold = 253;
  afmethodBold = false;
  aid_counterold = 0;
  dropout = false;

  if (wifi) {
    Udp.beginPacket(remoteip, 9030);
    if (band == BAND_FM) {
      Udp.print("from=TEF_tuner " + String(stationlistid, DEC) + ";freq=" + String(frequency) + "0000");
    } else if (band == BAND_OIRT) {
      Udp.print("from=TEF_tuner " + String(stationlistid, DEC) + ";freq=" + String(frequency_OIRT) + "0000");
    } else {
      Udp.print("from=TEF_tuner " + String(stationlistid, DEC) + ";freq=" + String(frequency_AM) + "000");
    }
    Udp.endPacket();
  }
  tuningtimer = millis();

  if (!rdsflagreset && !screenmute && !afscreen) {
    ShowRDSLogo(false);
    RadiotextSprite.fillSprite(BackgroundColor);
    AdvRadiotextSprite.fillSprite(BackgroundColor);
    if (!advancedRDS) {
      tft.fillCircle(314, 223, 2, GreyoutColor);
      tft.fillCircle(314, 234, 2, GreyoutColor);
      RadiotextSprite.pushSprite(38, 220);
    } else {
      tft.fillCircle(203, 223, 2, GreyoutColor);
      tft.fillCircle(203, 234, 2, GreyoutColor);
      AdvRadiotextSprite.pushSprite(35, 220);
    }
    rdsflagreset = true;
  }
}

void ShowSignalLevel() {
  if (!screenmute) {
    if (millis() >= SNRupdatetimer + TIMER_SNR_TIMER) {
      SNRupdatetimer = millis();
      if (!advancedRDS) {
        if (CN > (CNold + 1) || CN < (CNold - 1)) {
          if (CNold == 0) tftPrint(1, "--", 295, 163, BackgroundColor, BackgroundColor, 16); else tftPrint(1, String(CNold), 295, 163, BackgroundColor, BackgroundColor, 16);
          if (tuned) {
            if (CN == 0) tftPrint(1, "--", 295, 163, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, String(CN), 295, 163, PrimaryColor, PrimaryColorSmooth, 16);
            CNold = CN;
          } else {
            tftPrint(1, "--", 295, 163, PrimaryColor, PrimaryColorSmooth, 16);
            CNold = 0;
          }
        }
      }
    }
    SAvg = (((SAvg * 9) + 5) / 10) + SStatus;
    SAvg2 = (((SAvg2 * 9) + 5) / 10) + CN;

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
    CN = SAvg2 / 10;

    if (!menu) analogWrite(SMETERPIN, smeter);

    int SStatusprint = 0;
    if (unit == 0) SStatusprint = SStatus;
    if (unit == 1) SStatusprint = ((SStatus * 100) + 10875) / 100;
    if (unit == 2) SStatusprint = round((float(SStatus) / 10.0 - 10.0 * log10(75) - 90.0) * 10.0);

    if (SStatusprint > (SStatusold + 3) || SStatusprint < (SStatusold - 3)) {
      if (advancedRDS) {
        tftReplace(1, String(SStatusold / 10) + "." + String(abs(SStatusold % 10)), String(SStatusprint / 10) + "." + String(abs(SStatusprint % 10)), 273, 51, PrimaryColor, PrimaryColorSmooth, 16);
      } else {
        if (SStatusold / 10 != SStatusprint / 10) tftReplace(1, String(SStatusold / 10), String(SStatusprint / 10), 288, 105, FreqColor, FreqColorSmooth, 48);
        tftReplace(1, "." + String(abs(SStatusold % 10)), "." + String(abs(SStatusprint % 10)), 310, 105, FreqColor, FreqColorSmooth, 28);

        if (band < BAND_GAP) segments = (SStatus + 200) / 10; else segments = (SStatus + 200) / 10;

        tft.fillRect(16, 105, 2 * constrain(segments, 0, 54), 6, BarInsignificantColor);
        tft.fillRect(16 + 2 * 54, 105, 2 * (constrain(segments, 54, 94) - 54), 6, BarSignificantColor);
        tft.fillRect(16 + 2 * constrain(segments, 0, 94), 105, 2 * (94 - constrain(segments, 0, 94)), 6, GreyoutColor);
      }
      SStatusold = SStatusprint;
    }
  }
  if (wifi && millis() >= udptimer + 2000) {
    udptimer = millis();
    Udp.beginPacket(remoteip, 9030);
    Udp.print("from=TEF_tuner " + String(stationlistid, DEC) + ";RcvLevel=" + String(SStatus / 10));
    Udp.endPacket();
  }
}

void ShowRDSLogo(bool RDSstatus) {
  if (!screenmute) {
    if (RDSstatus != RDSstatusold) {
      if (RDSstatus) tft.drawBitmap(122, 5, RDSLogo, 35, 22, RDSColor); else tft.drawBitmap(122, 5, RDSLogo, 35, 22, GreyoutColor);
      RDSstatusold = RDSstatus;
    }
  }
}

void ShowStereoStatus() {
  if (StereoToggle) {
    if (band < BAND_GAP) Stereostatus = radio.getStereoStatus(); else Stereostatus = false;
    if (Stereostatus != Stereostatusold) {
      if (Stereostatus && !screenmute) {
        tft.drawSmoothCircle(66, 15, 10, StereoColor, StereoColorSmooth);
        tft.drawSmoothCircle(66, 15, 9, StereoColor, StereoColorSmooth);
        tft.drawSmoothCircle(76, 15, 10, StereoColor, StereoColorSmooth);
        tft.drawSmoothCircle(76, 15, 9, StereoColor, StereoColorSmooth);
      } else {
        if (!screenmute) {
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
      } else if (USN < 250 && WAM < 250 && OStatus > -250 && OStatus < 250 && !SQ) {
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
      } else if (OStatus > -2 && OStatus < 2 && !SQ) {
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
  if (!BWtune && millis() >= bwupdatetimer + TIMER_BW_TIMER) {
    bwupdatetimer = millis();
  } else {
    if (!BWtune) return;
  }

  if (BW != BWOld || BWreset) {
    if (BWset == 0) tftReplace(1, String (BWOld, DEC), String (BW, DEC), 201, 4, BWAutoColor, BWAutoColorSmooth, 28); else tftReplace(1, String (BWOld, DEC), String (BW, DEC), 201, 4, PrimaryColor, PrimaryColorSmooth, 28);
    BWOld = BW;
    BWreset = false;
    if (wifi) {
      Udp.beginPacket(remoteip, 9030);
      Udp.print("from=TEF_tuner " + String(stationlistid, DEC) + ";bandwidth=" + String(BW * 1000));
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

    tft.fillRect(16, 133, 2 * constrain(segments, 0, 54), 6, ModBarInsignificantColor);
    tft.fillRect(16 + 2 * 54, 133, 2 * (constrain(segments, 54, 94) - 54), 6, ModBarSignificantColor);
    tft.fillRect(16 + 2 * constrain(segments, 0, 94), 133, 2 * (94 - constrain(segments, 0, 94)), 6, GreyoutColor);

    int peakHoldPosition = 16 + 2 * constrain(peakholdold, 0, 94);
    tft.fillRect(peakHoldPosition, 133, 2, 6, (MStatus > 80) ? ModBarSignificantColor : PrimaryColor);

    if (millis() - peakholdmillis >= 1000) {
      tft.fillRect(peakHoldPosition, 133, 2, 6, GreyoutColor);
      peakholdold = segments;
      peakholdmillis = millis();
    }
  }
}

void doSquelch() {
  if (!XDRGTKUSB && !XDRGTKTCP && usesquelch) Squelch = analogRead(PIN_POT) / 4 - 100;
  if (unit == 0) SquelchShow = Squelch / 10;
  if (unit == 1) SquelchShow = ((Squelch * 100) + 10875) / 1000;
  if (unit == 2) SquelchShow = round((float(Squelch) / 10.0 - 10.0 * log10(75) - 90.0) * 10.0) / 10;
  if (Squelch > 920) Squelch = 920;

  if (!XDRGTKUSB && !XDRGTKTCP && usesquelch) {
    if (!screenmute && usesquelch && !advancedRDS && !afscreen) {
      if (!menu && (Squelch > Squelchold + 2 || Squelch < Squelchold - 2)) {
        SquelchSprite.fillSprite(BackgroundColor);
        SquelchSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);

        if (Squelch == -100) {
          SquelchSprite.drawString(String(myLanguage[language][33]), 0, 0);
        } else if (Squelch == 920) {
          SquelchSprite.drawString("ST", 0, 0);
        } else {
          SquelchSprite.drawString(String(SquelchShow), 0, 0);
        }
        if (Squelch != Squelchold) SquelchSprite.pushSprite(235, 145);
      }
      Squelchold = Squelch;
    }
  }

  if ((XDRGTKUSB || XDRGTKTCP)) {
    if (!XDRMute) {
      if (Squelch != -1) {
        if (Squelch < SStatus || Squelch == -100 || Squelch == 0) {
          if (!seek) radio.setUnMute();
          if (!screenmute && !seek) tft.drawBitmap(92, 4, Speaker, 26, 22, GreyoutColor);
          SQ = false;
        } else {
          radio.setMute();
          if (!screenmute && !seek) tft.drawBitmap(92, 4, Speaker, 26, 22, PrimaryColor);
          SQ = true;
        }
      } else {
        if (Stereostatus) {
          radio.setUnMute();
          if (!screenmute && !seek) tft.drawBitmap(92, 4, Speaker, 26, 22, GreyoutColor);
          SQ = false;
        } else {
          radio.setMute();
          if (!screenmute && !seek) tft.drawBitmap(92, 4, Speaker, 26, 22, PrimaryColor);
          SQ = true;
        }
      }
      if (!screenmute && usesquelch && !advancedRDS && !afscreen) {
        if (Squelch != Squelchold) {
          SquelchSprite.fillSprite(BackgroundColor);
          SquelchSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);

          if (Squelch == -1) {
            SquelchSprite.drawString("ST", 0, 0);
          } else if (Squelch == 0) {
            SquelchSprite.drawString(String(myLanguage[language][33]), 0, 0);
          } else {
            SquelchSprite.drawString(String(SquelchShow), 0, 0);
          }
          if (Squelch != Squelchold) SquelchSprite.pushSprite(235, 145);
          Squelchold = Squelch;
        }
      }
    }
  } else if (usesquelch) {
    if (Squelch != 920) {
      if (Squelch < SStatus || Squelch == -100 || Squelch == 0) {
        if (!seek) radio.setUnMute();
        if (!screenmute && !seek) tft.drawBitmap(92, 4, Speaker, 26, 22, GreyoutColor);
        SQ = false;
      } else {
        radio.setMute();
        if (!screenmute && !seek) tft.drawBitmap(92, 4, Speaker, 26, 22, PrimaryColor);
        SQ = true;
      }
    } else {
      if (Stereostatus) {
        if (!seek) radio.setUnMute();
        if (!screenmute && !seek) tft.drawBitmap(92, 4, Speaker, 26, 22, GreyoutColor);
        SQ = false;
      } else {
        radio.setMute();
        if (!screenmute && !seek) tft.drawBitmap(92, 4, Speaker, 26, 22, PrimaryColor);
        SQ = true;
      }
    }
  }
}

void updateBW() {
  if (BWset == 0) {
    if (!screenmute && !advancedRDS && !afscreen) {
      tft.drawRoundRect(248, 35, 71, 20, 5, ActiveColor);
      tftPrint(0, "AUTO BW", 283, 38, ActiveColor, ActiveColorSmooth, 16);
    }
    radio.setFMABandw();
  } else {
    if (!screenmute && !advancedRDS && !afscreen) {
      tft.drawRoundRect(248, 35, 71, 20, 5, GreyoutColor);
      tftPrint(0, "AUTO BW", 283, 38, GreyoutColor, BackgroundColor, 16);
    }
  }
}

void updateiMS() {
  if (band < BAND_GAP) {
    if (iMSset == 0) {
      if (!screenmute && !advancedRDS && !afscreen) {
        tft.drawRoundRect(248, 56, 32, 20, 5, ActiveColor);
        tftPrint(0, "iMS", 265, 59, ActiveColor, ActiveColorSmooth, 16);
      }
      radio.setiMS(1);
    } else {
      if (!screenmute && !advancedRDS && !afscreen) {
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
      if (!screenmute && !advancedRDS && !afscreen) {
        tft.drawRoundRect(286, 56, 32, 20, 5, ActiveColor);
        tftPrint(0, "EQ", 303, 59, ActiveColor, ActiveColorSmooth, 16);
      }
      radio.setEQ(1);
    } else {
      if (!screenmute && !advancedRDS && !afscreen) {
        tft.drawRoundRect(286, 56, 32, 20, 5, GreyoutColor);
        tftPrint(0, "EQ", 303, 59, GreyoutColor, BackgroundColor, 16);
      }
      radio.setEQ(0);
    }
  }
}

void updateCodetect() {
  if (band > BAND_GAP) {
    if (WAM) tftPrint(-1, "co", 50, 61, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(-1, "co", 50, 61, BackgroundColor, BackgroundColor, 16);
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
      FrequencySprite.drawString(SWMIBandstring + " ", 0, 0);
      beepresetstart = true;
      if (edgebeep && beepresetstop) {
        EdgeBeeper();
        beepresetstop = false;
      }
      break;

    case SW_MI_BAND_GAP:
      beepresetstop = true;
      if (edgebeep && beepresetstart) {
        EdgeBeeper();
        beepresetstart = false;
      }
      break;
  }
}

void doBW() {
  if (band < BAND_GAP) {
    if (BWset > 16) BWset = 0;

    switch (BWset) {
      case 1: radio.setFMBandw(56); break;
      case 2: radio.setFMBandw(64); break;
      case 3: radio.setFMBandw(72); break;
      case 4: radio.setFMBandw(84); break;
      case 5: radio.setFMBandw(97); break;
      case 6: radio.setFMBandw(114); break;
      case 7: radio.setFMBandw(133); break;
      case 8: radio.setFMBandw(151); break;
      case 9: radio.setFMBandw(168); break;
      case 10: radio.setFMBandw(184); break;
      case 11: radio.setFMBandw(200); break;
      case 12: radio.setFMBandw(217); break;
      case 13: radio.setFMBandw(236); break;
      case 14: radio.setFMBandw(254); break;
      case 15: radio.setFMBandw(287); break;
      case 16: radio.setFMBandw(311); break;
    }
    BWsetFM = BWset;
    EEPROM.writeByte(EE_BYTE_BWSET_FM, BWsetFM);
  } else {
    if (BWset > 4) BWset = 1;

    switch (BWset) {
      case 1: radio.setAMBandw(3); break;
      case 2: radio.setAMBandw(4); break;
      case 3: radio.setAMBandw(6); break;
      case 4: radio.setAMBandw(8); break;
    }
    BWsetAM = BWset;
    EEPROM.writeByte(EE_BYTE_BWSET_AM, BWsetAM);
  }
  updateBW();
  BWreset = true;
  EEPROM.commit();
}

void doBWtuneDown() {
  rotary = 0;
  BWset--;
  if (band < BAND_GAP) {
    if (BWset > 16) BWset = 16;
  } else {
    if (BWset == 0) BWset = 4;
  }
  doBW();
  ShowBW();
}

void doBWtuneUp() {
  rotary = 0;
  BWset++;
  if (band < BAND_GAP) {
    if (BWset > 16) BWset = 0;
  } else {
    if (BWset > 4) BWset = 1;
  }
  doBW();
  ShowBW();
}

void doTuneMode() {
  switch (tunemode) {
    case TUNE_MAN:
      if (band == BAND_SW) {
        if (showSWMIBand && nowToggleSWMIBand) {
          tunemode = TUNE_MI_BAND;
        } else {
          tunemode = TUNE_AUTO;
        }
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
  if (!screenmute) {
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

        if (memorystore) {
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

  uint16_t v = 0;
  if (!wifi) v = analogRead(BATTERY_PIN);
  battery = map(constrain(v, BAT_LEVEL_EMPTY, BAT_LEVEL_FULL), BAT_LEVEL_EMPTY, BAT_LEVEL_FULL, 0, BAT_LEVEL_STAGE);

  if (batteryold != battery) {
    if (!wifi && batterydetect) {
      if (battery == 0) {
        tft.drawRoundRect(277, 6, 37, 20, 2, BarSignificantColor);
        tft.fillRoundRect(313, 13, 4, 6, 2, BarSignificantColor);
      } else {
        tft.drawRoundRect(277, 6, 37, 20, 2, ActiveColor);
        tft.fillRoundRect(313, 13, 4, 6, 2, ActiveColor);
      }
      if (batteryoptions != BATTERY_VALUE && batteryoptions != BATTERY_PERCENT && battery != 0) {
        tft.fillRoundRect(279, 8, (battery * 8) , 16, 2, BarInsignificantColor);
      } else {
        tft.fillRoundRect(279, 8, 33, 16, 2, BackgroundColor);
      }
    } else {
      tft.drawRoundRect(277, 6, 37, 20, 2, GreyoutColor);
      tft.fillRoundRect(313, 13, 4, 6, 2, GreyoutColor);
      tft.fillRoundRect(279, 8, 33, 16, 2, BackgroundColor);
    }
    batteryold = battery;
    batteryVold = 0;
    vPerold = 0;
  }

  if (!wifi && batterydetect) {
    float batteryV = constrain((((float)v / 4095.0) * 3.3 * (1100 / 1000.0) * 2.0), 0.0, 5.0);
    float vPer = constrain((batteryV - BATTERY_LOW_VALUE) / (BATTERY_FULL_VALUE - BATTERY_LOW_VALUE), 0.0, 0.99) * 100;

    if (abs(batteryV - batteryVold) > 0.05 && batteryoptions == BATTERY_VALUE) {
      tftReplace(-1, String(batteryVold, 1) + "V", String(batteryV, 1) + "V", 279, 9, BatteryValueColor, BatteryValueColorSmooth, 16);
      batteryVold = batteryV;
    } else if (int(vPer) != int(vPerold) && batteryoptions == BATTERY_PERCENT && abs(vPer - vPerold) > 0.5) {
      tftReplace(-1, String(vPerold, 0) + "%", String(vPer, 0) + "%", 279, 9, BatteryValueColor, BatteryValueColorSmooth, 16);
      vPerold = vPer;
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
      if (frequency_AM < MWHighEdgeSet && frequency_AM > MWLowEdgeSet) {
        if (!mwstepsize) {
          temp = FREQ_MW_STEP_9K;
          frequency_AM = (frequency_AM / FREQ_MW_STEP_9K) * FREQ_MW_STEP_9K;
        } else if (mwstepsize) {
          temp = FREQ_MW_STEP_10K;
          frequency_AM = (frequency_AM / FREQ_MW_STEP_10K) * FREQ_MW_STEP_10K;
        }
      } else if (frequency_AM < MWLowEdgeSet) {
        temp = FREQ_MW_STEP_9K;
        frequency_AM = (frequency_AM / FREQ_MW_STEP_9K) * FREQ_MW_STEP_9K;
      } else {
        temp = FREQ_SW_STEP_5K;
        frequency_AM = (frequency_AM / FREQ_SW_STEP_5K) * FREQ_SW_STEP_5K;
      }
    } else {
      if (band == BAND_OIRT) {
        temp = FREQ_OIRT_STEP_30K;
      } else {
        switch (fmdefaultstepsize) {
          case 0: temp = FREQ_FM_STEP_50K; break;
          case 1: temp = FREQ_FM_STEP_100K; break;
          case 2: temp = FREQ_FM_STEP_200K; break;
        }
      }
    }
  }
  if (stepsize == 1) temp = 1;
  if (stepsize == 2) temp = 10;
  if (stepsize == 3) temp = 100;
  if (stepsize == 4) temp = 1000;

  if (band == BAND_FM) {
    frequency += temp;
    if (fmdefaultstepsize == 2 && stepsize == 0 && frequency == 8795) frequency = 8790;
    if (frequency >= (HighEdgeSet * 10) + 1) {
      frequency = LowEdgeSet * 10;
      if (fmdefaultstepsize == 2 && stepsize == 0 && frequency == 8750) frequency = 8775;
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
  if (RDSSPYUSB) Serial.print("G:\r\nRESET-------\r\n\r\n");
  if (RDSSPYTCP) RemoteClient.print("G:\r\nRESET-------\r\n\r\n");
}

void TuneDown() {
  aftest = true;
  aftimer = millis();
  unsigned int temp = 0;
  if (stepsize == 0) {
    if (band > BAND_GAP) {
      if (frequency_AM < MWHighEdgeSet && frequency_AM > MWLowEdgeSet) {
        if (!mwstepsize) {
          temp = FREQ_MW_STEP_9K;
          frequency_AM = (frequency_AM / FREQ_MW_STEP_9K) * FREQ_MW_STEP_9K;
        } else if (mwstepsize) {
          temp = FREQ_MW_STEP_10K;
          frequency_AM = (frequency_AM / FREQ_MW_STEP_10K) * FREQ_MW_STEP_10K;
        }
      } else if (frequency_AM < MWLowEdgeSet) {
        temp = FREQ_MW_STEP_9K;
        frequency_AM = (frequency_AM / FREQ_MW_STEP_9K) * FREQ_MW_STEP_9K;
      } else {
        temp = FREQ_SW_STEP_5K;
        frequency_AM = (frequency_AM / FREQ_SW_STEP_5K) * FREQ_SW_STEP_5K;
      }
    } else {
      if (band == BAND_OIRT) {
        temp = FREQ_OIRT_STEP_30K;
      } else {
        switch (fmdefaultstepsize) {
          case 0: temp = FREQ_FM_STEP_50K; break;
          case 1: temp = FREQ_FM_STEP_100K; break;
          case 2: temp = FREQ_FM_STEP_200K; break;
        }
      }
    }
  }
  if (stepsize == 1) temp = 1;
  if (stepsize == 2) temp = 10;
  if (stepsize == 3) temp = 100;
  if (stepsize == 4) temp = 1000;

  if (band == BAND_FM) {
    frequency -= temp;
    if (fmdefaultstepsize == 2 && stepsize == 0 && frequency == 8770) frequency = 8775;
    if (fmdefaultstepsize == 2 && stepsize == 0 && frequency == 8755) frequency = 10790;

    if (frequency < LowEdgeSet * 10) {
      frequency = HighEdgeSet * 10;
      if (fmdefaultstepsize == 2 && stepsize == 0 && frequency == 10800) frequency = 10790;
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
  if (RDSSPYUSB) Serial.print("G:\r\nRESET-------\r\n\r\n");
  if (RDSSPYTCP) RemoteClient.print("G:\r\nRESET-------\r\n\r\n");
}

void EdgeBeeper() {
  radio.tone(50, -5, 2000);
  if (radio.mute) {
    radio.setMute();
    if (!screenmute) tft.drawBitmap(92, 4, Speaker, 26, 22, PrimaryColor);
  } else {
    radio.setUnMute();
    if (!screenmute) tft.drawBitmap(92, 4, Speaker, 26, 22, GreyoutColor);
  }
}

void Seek(bool mode) {
  radio.setMute();
  if (!screenmute) tft.drawBitmap(92, 4, Speaker, 26, 22, PrimaryColor);
  if (!mode) TuneDown(); else TuneUp();
  delay(50);
  ShowFreq(0);
  if (XDRGTKUSB || XDRGTKTCP) {
    if (band == BAND_FM) DataPrint("M0\nT" + String(frequency * 10)); else if (band == BAND_OIRT) DataPrint("M0\nT" + String(frequency_OIRT * 10)); else DataPrint("M1\nT" + String(frequency_AM));
  }

  if (band < BAND_GAP) {
    radio.getStatus(SStatus, USN, WAM, OStatus, BW, MStatus, CN);
    if ((USN < fmscansens * 30) && (WAM < 230) && (OStatus < 80 && OStatus > -80) && (Squelch < SStatus || Squelch == 920)) {
      seek = false;
      radio.setUnMute();
      if (!screenmute) tft.drawBitmap(92, 4, Speaker, 26, 22, GreyoutColor);
      store = true;
    } else {
      seek = true;
      if (RDSSPYUSB) Serial.print("G:\r\nRESET-------\r\n\r\n");
      if (RDSSPYTCP) RemoteClient.print("G:\r\nRESET-------\r\n\r\n");
    }
  } else {
    radio.getStatusAM(SStatus, USN, WAM, OStatus, BW, MStatus, CN);
    if ((USN < amscansens * 30) && (OStatus < 2 && OStatus > -2) && (Squelch < SStatus || Squelch == 920)) {
      seek = false;
      radio.setUnMute();
      if (!screenmute) tft.drawBitmap(92, 4, Speaker, 26, 22, GreyoutColor);
      store = true;
    } else {
      seek = true;
    }
  }
}

void SetTunerPatch() {
  if (TEF != 102 && TEF != 205) {
    radio.init(102);
    uint16_t device;
    uint16_t hw;
    uint16_t sw;
    radio.getIdentification(device, hw, sw);
    TEF = highByte(hw) * 100 + highByte(sw);
    tft.fillScreen(BackgroundColor);
    analogWrite(CONTRASTPIN, ContrastSet * 2 + 27);

    if (TEF == 0) {
      tftPrint(0, myLanguage[language][35], 150, 78, ActiveColor, ActiveColorSmooth, 28);
      for (;;);
    }
    EEPROM.writeByte(EE_BYTE_TEF, TEF);
    EEPROM.commit();
    Tuner_Reset();
    ESP.restart();
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
      if (rotarymode) rotary = -1; else rotary = 1;
      encval = 0;
    } else if (encval < -2) {
      if (rotarymode) rotary = 1; else rotary = -1;
      encval = 0;
    }
  } else {
    if (encval > 3) {
      if (rotarymode) rotary = -1; else rotary = 1;
      encval = 0;
    } else if (encval < -3) {
      if (rotarymode) rotary = 1; else rotary = -1;
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
  EEPROM.writeByte(EE_BYTE_VOLSET, 0);
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
  EEPROM.writeByte(EE_BYTE_SHOWRDSERRORS, 1);
  EEPROM.writeByte(EE_BYTE_TEF, 0);
  if (userhardwaremodel == BASE_ILI9341) EEPROM.writeByte(EE_BYTE_DISPLAYFLIP, 0); else EEPROM.writeByte(EE_BYTE_DISPLAYFLIP, 1);
  EEPROM.writeByte(EE_BYTE_ROTARYMODE, 0);
  EEPROM.writeByte(EE_BYTE_STEPSIZE, 0);
  EEPROM.writeByte(EE_BYTE_TUNEMODE, 0);
  EEPROM.writeByte(EE_BYTE_OPTENC, 0);
  EEPROM.writeByte(EE_BYTE_IMSSET, 1);
  EEPROM.writeByte(EE_BYTE_EQSET, 1);
  EEPROM.writeByte(EE_BYTE_BAND, BAND_FM);
  EEPROM.writeByte(EE_BYTE_LOWLEVELSET, -15);
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
  for (int i = 0; i < EE_PRESETS_CNT; i++) EEPROM.writeByte(i + EE_PRESET_BW_START, 0);
  for (int i = 0; i < EE_PRESETS_CNT; i++) EEPROM.writeByte(i + EE_PRESET_MS_START, 1);
  if (userhardwaremodel == BASE_ILI9341) EEPROM.writeUInt(EE_UINT16_FREQUENCY_LW, 180); else EEPROM.writeUInt(EE_UINT16_FREQUENCY_LW, 164);
  if (userhardwaremodel == BASE_ILI9341) EEPROM.writeUInt(EE_UINT16_FREQUENCY_MW, 540); else EEPROM.writeUInt(EE_UINT16_FREQUENCY_MW, 639);
  if (userhardwaremodel == BASE_ILI9341) EEPROM.writeUInt(EE_UINT16_FREQUENCY_SW, 1800); else EEPROM.writeUInt(EE_UINT16_FREQUENCY_SW, 5000);
  EEPROM.writeString(EE_STRING_XDRGTK_KEY, "password");
  if (userhardwaremodel == BASE_ILI9341) EEPROM.writeByte(EE_BYTE_USESQUELCH, 1); else EEPROM.writeByte(EE_BYTE_USESQUELCH, 0);
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
  EEPROM.writeByte(EE_BYTE_AM_CO_DECT, 100);
  EEPROM.writeByte(EE_BYTE_AM_CO_DECT_COUNT, 3);
  EEPROM.writeByte(EE_BYTE_AM_RF_AGC, 0);
  EEPROM.writeByte(EE_BYTE_SORTAF, 1);
  EEPROM.writeByte(EE_BYTE_STATIONLISTID, 1);
  EEPROM.writeByte(EE_BYTE_FM_DEEMPHASIS, DEEMPHASIS_50);
  EEPROM.writeByte(EE_BYTE_BWSET_FM, 0);
  EEPROM.writeByte(EE_BYTE_BWSET_AM, 2);
  EEPROM.writeByte(EE_BYTE_BANDAUTOSW, 0);
  EEPROM.writeByte(EE_BYTE_FASTPS, 1);
  EEPROM.writeByte(EE_BYTE_TOT, 0);
  EEPROM.writeByte(EE_BYTE_MWREGION, 0);
  EEPROM.writeByte(EE_BYTE_SPISPEED, 0);
  EEPROM.writeByte(EE_BYTE_AMSCANSENS, 4);
  EEPROM.writeByte(EE_BYTE_FMSCANSENS, 4);
  EEPROM.writeByte(EE_BYTE_FREQFONT, 3);
  EEPROM.writeByte(EE_BYTE_SKIN, 0);
  EEPROM.writeByte(EE_BYTE_XDRGTKMUTE, 0);
  EEPROM.commit();
}

void tftReplace(int8_t offset, const String &textold, const String &text, int16_t x, int16_t y, int color, int smoothcolor, uint8_t fontsize) {
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

  String modifiedText = text;
  modifiedText.replace("\n", " ");

  tft.drawString(modifiedText, x, y);
}

void tftPrint(int8_t offset, const String &text, int16_t x, int16_t y, int color, int smoothcolor, uint8_t fontsize) {
  const uint8_t *selectedFont = nullptr;
  if (language == LANGUAGE_CHS) {
    if (fontsize == 16) selectedFont = FONT16_CHS;
    if (fontsize == 28) selectedFont = FONT28_CHS;
  } else {
    if (fontsize == 16) selectedFont = FONT16;
    if (fontsize == 28) selectedFont = FONT28;
  }
  if (fontsize == 48) selectedFont = FONT48;
  if (fontsize == 52) {
    switch (freqfont) {
      case 0: selectedFont = FREQFONT0; break;
      case 1: selectedFont = FREQFONT1; break;
      case 2: selectedFont = FREQFONT2; break;
      case 3: selectedFont = FREQFONT3; break;
      case 4: selectedFont = FREQFONT4; break;
    }
  }

  if (currentFont != selectedFont || resetFontOnNextCall) {
    if (currentFont != nullptr) tft.unloadFont();
    tft.loadFont(selectedFont);
    currentFont = selectedFont;
    resetFontOnNextCall = false;
  }

  tft.setTextColor(color, smoothcolor, (fontsize == 52 ? true : false));

  switch (offset) {
    case -1: tft.setTextDatum(TL_DATUM); break;
    case 0: tft.setTextDatum(TC_DATUM); break;
    case 1: tft.setTextDatum(TR_DATUM); break;
  }

  String modifiedText = text;
  modifiedText.replace("\n", " ");

  tft.drawString(modifiedText, x, y, 1);
}

void deepSleep() {
  analogWrite(SMETERPIN, 0);
  MuteScreen(1);
  StoreFrequency();
  radio.power(1);
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_34, LOW);
  esp_deep_sleep_start();
}
