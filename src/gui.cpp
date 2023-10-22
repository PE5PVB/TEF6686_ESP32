#include "gui.h"
#include "language.h"
#include "constants.h"
#include <WiFi.h>
#include <Wire.h>
#include <EEPROM.h>

byte menuitem;
byte items[8] = {8, 3, 6, 10, 9, 10, 8, 5};

void doTheme() {  // Use this to put your own colors in: http://www.barth-dev.de/online/rgb565-color-picker/
  switch (CurrentTheme) {
    case 0:  // Default PE5PVB theme
      PrimaryColor = TFT_YELLOW;
      PrimaryColorSmooth = 0x2120;
      SecondaryColor = TFT_SKYBLUE;
      SecondaryColorSmooth = 0x10E4;
      FrequencyColor = TFT_YELLOW;
      FrameColor = TFT_BLUE;
      GreyoutColor = 0x39A7;
      BackgroundColor = TFT_BLACK;
      ActiveColor = TFT_WHITE;
      ActiveColorSmooth = 0x18E3;
      SignificantColor = TFT_RED;
      SignificantColorSmooth = 0x2000;
      InsignificantColor = TFT_GREEN;
      InsignificantColorSmooth = 0x00C0;
      StereoColor = TFT_RED;
      StereoColorSmooth = 0x2000;
      RDSColor = TFT_YELLOW;
      RDSColorSmooth = 0x2120;
      BarSignificantColor = TFT_RED;
      BarInsignificantColor = TFT_GREEN;
      BWAutoColor = 0x07F7;
      BWAutoColorSmooth = 0x0144;
      BatteryValueColor = 0x07F7;
      BatteryValueColorSmooth = TFT_BLACK;
      CurrentThemeString = myLanguage[language][78];
      break;
    case 1:  // Cyan theme
      PrimaryColor = 0x0F3F;
      PrimaryColorSmooth = 0x0105;
      SecondaryColor = 0x5BAF;
      SecondaryColorSmooth = 0x29E8;
      FrequencyColor = 0x0F3F;
      FrameColor = 0x01e9;
      GreyoutColor = 0x2A08;
      BackgroundColor = TFT_BLACK;
      ActiveColor = TFT_WHITE;
      ActiveColorSmooth = 0x18E3;
      SignificantColor = TFT_RED;
      SignificantColorSmooth = 0x2000;
      InsignificantColor = TFT_GREEN;
      InsignificantColorSmooth = 0x00C0;
      StereoColor = 0x0F3F;
      StereoColorSmooth = 0x0105;
      RDSColor = 0x0F3F;
      RDSColorSmooth = 0x0105;
      BarSignificantColor = TFT_RED;
      BarInsignificantColor = 0x0F3F;
      BWAutoColor = 0x07F7;
      BWAutoColorSmooth = 0x0144;
      BatteryValueColor = 0x07F7;
      BatteryValueColorSmooth = 0x0144;
      CurrentThemeString = myLanguage[language][79];
      break;
    case 2:  // Crimson theme
      PrimaryColor = 0xF8C3;
      PrimaryColorSmooth = 0x3800;
      SecondaryColor = 0x6A08;
      SecondaryColorSmooth = 0x30E3;
      FrequencyColor = 0xF8C3;
      FrameColor = 0x3800;
      GreyoutColor = 0x4A69;
      BackgroundColor = TFT_BLACK;
      ActiveColor = TFT_WHITE;
      ActiveColorSmooth = 0x18E3;
      SignificantColor = TFT_RED;
      SignificantColorSmooth = 0x2000;
      InsignificantColor = TFT_GREEN;
      InsignificantColorSmooth = 0x00C0;
      StereoColor = 0xF8C3;
      StereoColorSmooth = TFT_BLACK;
      RDSColor = 0xF8C3;
      RDSColorSmooth = TFT_BLACK;
      BarSignificantColor = TFT_YELLOW;
      BarInsignificantColor = 0xF8C3;
      BWAutoColor = 0xFBEF;
      BWAutoColorSmooth = 0x4124;
      BatteryValueColor = 0xFA8D;
      BatteryValueColorSmooth = 0x3083;
      CurrentThemeString = myLanguage[language][80];
      break;
    case 3:  // Monochrome theme
      PrimaryColor = TFT_WHITE;
      PrimaryColorSmooth = TFT_BLACK;
      SecondaryColor = 0x7BCF;
      SecondaryColorSmooth = 0x1082;
      FrequencyColor = TFT_WHITE;
      FrameColor = 0x2965;
      GreyoutColor = 0x4A69;
      BackgroundColor = TFT_BLACK;
      ActiveColor = TFT_WHITE;
      ActiveColorSmooth = TFT_BLACK;
      SignificantColor = TFT_RED;
      SignificantColorSmooth = 0x2000;
      InsignificantColor = TFT_GREEN;
      InsignificantColorSmooth = 0x00C0;
      StereoColor = TFT_WHITE;
      StereoColorSmooth = TFT_BLACK;
      RDSColor = TFT_WHITE;
      RDSColorSmooth = TFT_BLACK;
      BarSignificantColor = TFT_RED;
      BarInsignificantColor = TFT_GREEN;
      BWAutoColor = 0x7BCF;
      BWAutoColorSmooth = 0x1082;
      BatteryValueColor = TFT_WHITE;
      BatteryValueColorSmooth = TFT_BLACK;
      CurrentThemeString = myLanguage[language][81];
      break;
    case 4:  // Volcano theme
      PrimaryColor = TFT_ORANGE;
      PrimaryColorSmooth = 0x2965;
      SecondaryColor = 0x6A86;
      SecondaryColorSmooth = 0x3123;
      FrequencyColor = TFT_ORANGE;
      FrameColor = 0x2965;
      GreyoutColor = 0x5140;
      BackgroundColor = 0x0806;
      ActiveColor = TFT_WHITE;
      ActiveColorSmooth = 0x18E3;
      SignificantColor = TFT_RED;
      SignificantColorSmooth = 0x2000;
      InsignificantColor = TFT_GREEN;
      InsignificantColorSmooth = 0x00C0;
      StereoColor = TFT_ORANGE;
      StereoColorSmooth = 0x0105;
      RDSColor = TFT_ORANGE;
      RDSColorSmooth = TFT_WHITE;
      BarSignificantColor = TFT_RED;
      BarInsignificantColor = TFT_ORANGE;
      BWAutoColor = 0xF980;
      BWAutoColorSmooth = 0x3080;
      BatteryValueColor = 0xF980;
      BatteryValueColorSmooth = 0x3080;
      CurrentThemeString = myLanguage[language][82];
      break;
    case 5:  // Dendro theme
      PrimaryColor = TFT_GREEN;
      PrimaryColorSmooth = 0x0200;
      SecondaryColor = 0x748E;
      SecondaryColorSmooth = 0x3206;
      FrequencyColor = TFT_GREEN;
      FrameColor = 0x0200;
      GreyoutColor = 0x4A69;
      BackgroundColor = TFT_BLACK;
      ActiveColor = TFT_WHITE;
      ActiveColorSmooth = 0x18E3;
      SignificantColor = TFT_RED;
      SignificantColorSmooth = 0x2000;
      InsignificantColor = TFT_GREEN;
      InsignificantColorSmooth = 0x00C0;
      StereoColor = TFT_GREEN;
      StereoColorSmooth = 0x0200;
      RDSColor = TFT_GREEN;
      RDSColorSmooth = 0x0200;
      BarSignificantColor = TFT_RED;
      BarInsignificantColor = TFT_GREEN;
      BWAutoColor = 0x07F6;
      BWAutoColorSmooth = 0x0184;
      BatteryValueColor = 0x07F6;
      BatteryValueColorSmooth = 0x0184;
      CurrentThemeString = myLanguage[language][83];
      break;
    case 6:  // Sakura theme
      PrimaryColor = 0xF3D5;
      PrimaryColorSmooth = 0x3008;
      SecondaryColor = 0x9B90;
      SecondaryColorSmooth = 0x3946;
      FrequencyColor = 0xF3D5;
      FrameColor = 0x3845;
      GreyoutColor = 0x38C5;
      BackgroundColor = TFT_BLACK;
      ActiveColor = TFT_WHITE;
      ActiveColorSmooth = 0x18E3;
      SignificantColor = TFT_RED;
      SignificantColorSmooth = 0x2000;
      InsignificantColor = TFT_GREEN;
      InsignificantColorSmooth = 0x00C0;
      StereoColor = 0xF3D5;
      StereoColorSmooth = 0x3008;
      RDSColor = 0xF3D5;
      RDSColorSmooth = 0x3008;
      BarSignificantColor = TFT_RED;
      BarInsignificantColor = 0xF3D5;
      BWAutoColor = 0xF00A;
      BWAutoColorSmooth = 0x2802;
      BatteryValueColor = 0xF00A;
      BatteryValueColorSmooth = 0x2802;
      CurrentThemeString = myLanguage[language][84];
      break;
    case 7:  // Whiteout theme
      PrimaryColor = TFT_BLACK;
      PrimaryColorSmooth = TFT_WHITE;
      SecondaryColor = 0x9492;
      SecondaryColorSmooth = TFT_WHITE;
      FrequencyColor = 0x18C3;
      FrameColor = 0x630C;
      GreyoutColor = 0x9492;
      BackgroundColor = 0xDFFC;
      ActiveColor = TFT_BLACK;
      ActiveColorSmooth = 0xDFFC;
      SignificantColor = TFT_BLACK;
      SignificantColorSmooth = 0xDFFC;
      InsignificantColor = TFT_GREEN;
      InsignificantColorSmooth = 0x0140;
      StereoColor = TFT_BLACK;
      StereoColorSmooth = 0xDFFC;
      RDSColor = TFT_BLACK;
      RDSColorSmooth = 0xDFFC;
      BarSignificantColor = TFT_BLACK;
      BarInsignificantColor = TFT_GREEN;
      BWAutoColor = 0x7BCF;
      BWAutoColorSmooth = TFT_WHITE;
      BatteryValueColor = TFT_BLACK;
      BatteryValueColorSmooth = TFT_WHITE;
      CurrentThemeString = myLanguage[language][85];
      break;
    case 8:  // Tangerine theme
      PrimaryColor = 0xF980;
      PrimaryColorSmooth = 0x3080;
      SecondaryColor = 0x9B8D;
      SecondaryColorSmooth = 0x5207;
      FrequencyColor = 0xF980;
      FrameColor = 0x38A1;
      GreyoutColor = 0x6247;
      BackgroundColor = TFT_BLACK;
      ActiveColor = TFT_WHITE;
      ActiveColorSmooth = 0x18E3;
      SignificantColor = TFT_RED;
      SignificantColorSmooth = 0x2000;
      InsignificantColor = TFT_GREEN;
      InsignificantColorSmooth = 0x00C0;
      StereoColor = 0xF980;
      StereoColorSmooth = 0x3080;
      RDSColor = 0xF980;
      RDSColorSmooth = 0x3080;
      BarSignificantColor = TFT_RED;
      BarInsignificantColor = TFT_GREEN;
      BWAutoColor = 0xED20;
      BWAutoColorSmooth = 0x3940;
      BatteryValueColor = 0xED20;
      BatteryValueColorSmooth = 0x3940;
      CurrentThemeString = myLanguage[language][170];
      break;
    case 9:  // Ocean theme
      PrimaryColor = 0x01FF;
      PrimaryColorSmooth = 0x0006;
      SecondaryColor = 0x73F4;
      SecondaryColorSmooth = 0x31A8;
      FrequencyColor = 0x01FF;
      FrameColor = 0x0010;
      GreyoutColor = 0x420C;
      BackgroundColor = TFT_BLACK;
      ActiveColor = TFT_WHITE;
      ActiveColorSmooth = 0x18E3;
      SignificantColor = TFT_RED;
      SignificantColorSmooth = 0x2000;
      InsignificantColor = TFT_GREEN;
      InsignificantColorSmooth = 0x00C0;
      StereoColor = 0x01FF;
      StereoColorSmooth = 0x0006;
      RDSColor = 0x01FF;
      RDSColorSmooth = 0x0006;
      BarSignificantColor = TFT_RED;
      BarInsignificantColor = 0x01FF;
      BWAutoColor = 0x051F;
      BWAutoColorSmooth = 0x0106;
      BatteryValueColor = 0x051F;
      BatteryValueColorSmooth = 0x0106;
      CurrentThemeString = myLanguage[language][171];
      break;
    case 10:  // Indigo theme
      PrimaryColor = 0x881F;
      PrimaryColorSmooth = 0x2007;
      SecondaryColor = 0x9C96;
      SecondaryColorSmooth = 0x41C8;
      FrequencyColor = 0x881F;
      FrameColor = 0x6016;
      GreyoutColor = 0x49AC;
      BackgroundColor = TFT_BLACK;
      ActiveColor = TFT_WHITE;
      ActiveColorSmooth = 0x18E3;
      SignificantColor = TFT_RED;
      SignificantColorSmooth = 0x2000;
      InsignificantColor = TFT_GREEN;
      InsignificantColorSmooth = 0x00C0;
      StereoColor = 0x881F;
      StereoColorSmooth = 0x2007;
      RDSColor = 0x881F;
      RDSColorSmooth = 0x2007;
      BarSignificantColor = TFT_RED;
      BarInsignificantColor = 0x881F;
      BWAutoColor = 0xD01F;
      BWAutoColorSmooth = 0x400A;
      BatteryValueColor = 0xD01F;
      BatteryValueColorSmooth = 0x400A;
      CurrentThemeString = myLanguage[language][172];
      break;
  }
}

void BuildAFScreen() {
  if (!afscreen && RDSstatus) {
    tft.drawRoundRect(20, 30, 274, 170, 5, ActiveColor);
    tft.fillRoundRect(22, 32, 270, 166, 5, BackgroundColor);
    tftPrint(0, myLanguage[language][34], 155, 98, ActiveColor, ActiveColorSmooth, 28);
    radio.TestAFEON();
  }
  afscreen = true;
  advancedRDS = false;
  if (theme == 0) {
    tft.fillScreen(BackgroundColor);
    tft.drawRect(0, 0, 320, 240, FrameColor);
    tft.drawLine(0, 30, 320, 30, FrameColor);
    tft.drawLine(0, 199, 320, 199, FrameColor);
    tft.drawLine(0, 218, 320, 218, FrameColor);
    tft.drawLine(168, 30, 168, 199, FrameColor);
    tft.drawLine(53, 30, 53, 0, FrameColor);
    tft.drawLine(89, 30, 89, 0, FrameColor);
    tft.drawLine(120, 30, 120, 0, FrameColor);
    tft.drawLine(158, 30, 158, 0, FrameColor);
    tft.drawLine(248, 30, 248, 0, FrameColor);
    tftPrint(-1, "kHz", 203, 4, ActiveColor, ActiveColorSmooth, 28);
    tftPrint(0, myLanguage[language][93], 160, 222, ActiveColor, ActiveColorSmooth, 16);
    tftPrint(-1, myLanguage[language][88], 184, 48, PrimaryColor, PrimaryColorSmooth, 16);
    tftPrint(-1, myLanguage[language][87], 6, 48, PrimaryColor, PrimaryColorSmooth, 16);
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
    batteryVold = 0;
    vPerold = 0;
    af_counterold = 254;
    strcpy(radioIdPrevious, "");
    programServicePrevious = "";
    afmethodBold = false;
    for (byte i = 0; i < 11; i++) eonpsold[i] = "";
  }
}

void BuildMenu() {
  advancedRDS = false;
  tft.fillScreen(BackgroundColor);
  tft.drawRect(0, 0, 320, 240, FrameColor);
  tft.drawLine(0, 23, 320, 23, FrameColor);
  if (!submenu) {
    tftPrint(0, myLanguage[language][41], 160, 7, PrimaryColor, PrimaryColorSmooth, 16);
  } else {
    tftPrint(-1, myLanguage[language][184], 4, 7, PrimaryColor, PrimaryColorSmooth, 16);
    tftPrint(1, myLanguage[language][189 + menupage - 1], 318, 7, ActiveColor, ActiveColorSmooth, 16);
  }
  tft.drawRoundRect(3, menuoption + 3, 315, 21, 5, ActiveColor);
  switch (menupage) {
    case INDEX:
      tftPrint(0, myLanguage[language][177], 160, ITEM1 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(0, myLanguage[language][178], 160, ITEM2 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(0, myLanguage[language][179], 160, ITEM3 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(0, myLanguage[language][180], 160, ITEM4 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(0, myLanguage[language][181], 160, ITEM5 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(0, myLanguage[language][182], 160, ITEM6 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(0, myLanguage[language][183], 160, ITEM7 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(0, myLanguage[language][70], 160, ITEM8 + 6, ActiveColor, ActiveColorSmooth, 16);
      break;

    case MAINSETTINGS:
      tftPrint(-1, myLanguage[language][108], 8, ITEM1 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][68], 8, ITEM2 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][206], 8, ITEM3 + 6, ActiveColor, ActiveColorSmooth, 16);

      tftPrint(1, "Mhz", 310, ITEM3 + 6, ActiveColor, ActiveColorSmooth, 16); 

      switch (hardwaremodel) {
        case BASE_ILI9341: tftPrint(1, myLanguage[language][109], 310, ITEM1 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
        case PORTABLE_ILI9341: tftPrint(1, myLanguage[language][110 ], 310, ITEM1 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
        case PORTABLE_TOUCH_ILI9341: tftPrint(1, myLanguage[language][111], 310, ITEM1 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
      }

      if (spispeed == SPI_SPEED_DEFAULT) tftPrint(1,  myLanguage[language][78] + String(SPI_FREQUENCY / 1000000, DEC), 270, ITEM3 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      else tftPrint(1, String(spispeed * 10 ,DEC), 270, ITEM3 + 6, PrimaryColor, PrimaryColorSmooth, 16);

      if (touchrotating) tftPrint(1, myLanguage[language][42], 310, ITEM2 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM2 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      break;

    case AUDIOSETTINGS:
      tftPrint(-1, myLanguage[language][20], 8, ITEM1 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][45], 8, ITEM2 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][67], 8, ITEM3 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][25], 8, ITEM4 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][26], 8, ITEM5 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][27], 8, ITEM6 + 6, ActiveColor, ActiveColorSmooth, 16);

      tftPrint(1, "dB", 310, ITEM1 + 6, ActiveColor, ActiveColorSmooth, 16);
      if (VolSet > 0) tftPrint(1, "+" + String(VolSet, DEC), 270, ITEM1 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, String(VolSet, DEC), 270, ITEM1 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      if (edgebeep) tftPrint(1, myLanguage[language][42], 310, ITEM2 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM2 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      if (audiomode) tftPrint(1, "MPX", 310, ITEM3 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, "Stereo", 310, ITEM3 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      if (StereoLevel != 0) tftPrint(1, "dBμV", 310, ITEM4 + 6, ActiveColor, ActiveColorSmooth, 16);
      if (StereoLevel != 0) tftPrint(1, String(StereoLevel, DEC), 270, ITEM4 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM4 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      if (HighCutLevel != 0) tftPrint(1, "Hz", 310, ITEM5 + 6, ActiveColor, ActiveColorSmooth, 16);
      if (HighCutLevel != 0) tftPrint(1, String(HighCutLevel * 100, DEC), 270, ITEM5 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM5 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      if (HighCutOffset != 0) tftPrint(1, "dBμV", 310, ITEM6 + 6, ActiveColor, ActiveColorSmooth, 16);
      if (HighCutOffset != 0) tftPrint(1, String(HighCutOffset, DEC), 270, ITEM6 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM6 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      break;

    case DISPLAYSETTINGS:
      tftPrint(-1, myLanguage[language][39], 8, ITEM1 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][29], 8, ITEM2 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][62], 8, ITEM3 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][63], 8, ITEM4 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][77], 8, ITEM5 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][91], 8, ITEM6 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][74], 8, ITEM7 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][173], 8, ITEM8 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][98], 8, ITEM9 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][75], 8, ITEM10 + 6, ActiveColor, ActiveColorSmooth, 16);

      tftPrint(1, myLanguage[language][0], 310, ITEM1 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      tftPrint(1, "%", 310, ITEM2 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(1, String(ContrastSet, DEC), 270, ITEM2 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      if (showsquelch) tftPrint(1, myLanguage[language][42], 310, ITEM3 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM3 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      if (showmodulation) tftPrint(1, myLanguage[language][42], 310, ITEM4 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM4 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      tftPrint(1, CurrentThemeString, 310, ITEM5 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      if (screensaverset) tftPrint(1, myLanguage[language][92], 310, ITEM6 + 6, ActiveColor, ActiveColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM6 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      if (screensaverset) tftPrint(1, String(screensaverOptions[screensaverset], DEC), 270, ITEM6 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM6 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      if (tot != 0) tftPrint(1, myLanguage[language][205], 310, ITEM10 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM10 + 6, PrimaryColor, PrimaryColorSmooth, 16);

      switch (poweroptions) {
        case LCD_OFF: tftPrint(1, myLanguage[language][76], 310, ITEM7 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
        case LCD_BRIGHTNESS_1_PERCENT: tftPrint(1, myLanguage[language][94], 310, ITEM7 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
        case LCD_BRIGHTNESS_A_QUARTER: tftPrint(1, myLanguage[language][95], 310, ITEM7 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
        case LCD_BRIGHTNESS_HALF: tftPrint(1, myLanguage[language][96], 310, ITEM7 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
      }

      switch (batteryoptions) {
        case BATTERY_NONE: tftPrint(1, myLanguage[language][30], 310, ITEM8 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
        case BATTERY_VALUE: tftPrint(1, myLanguage[language][174], 310, ITEM8 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
		case BATTERY_VALUE2: tftPrint(1, myLanguage[language][207], 310, ITEM8 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
        case BATTERY_PERCENT: tftPrint(1, myLanguage[language][175], 310, ITEM8 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
      }

      tftPrint(1, unitString[unit], 310, ITEM9 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      if (tot != 0) tftPrint(1, String(tot), 270, ITEM10 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      break;

    case RDSSETTINGS:
      tftPrint(-1, myLanguage[language][38], 8, ITEM1 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][46], 8, ITEM2 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][49], 8, ITEM3 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][60], 8, ITEM4 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][61], 8, ITEM5 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][99], 8, ITEM6 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][176], 8, ITEM7 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][196], 8, ITEM8 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][203], 8, ITEM9 + 6, ActiveColor, ActiveColorSmooth, 16);

      switch (showrdserrors) {
        case 0: tftPrint(1, myLanguage[language][30], 310, ITEM1 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
        case 1: tftPrint(1, myLanguage[language][200], 310, ITEM1 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
        case 2: tftPrint(1, myLanguage[language][201], 310, ITEM1 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
        case 3: tftPrint(1, myLanguage[language][202], 310, ITEM1 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
      }

      if (region == REGION_EU) tftPrint(1, myLanguage[language][47], 310, ITEM2 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      if (region == REGION_US) tftPrint(1, myLanguage[language][48], 310, ITEM2 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      if (radio.rds.underscore) tftPrint(1, myLanguage[language][42], 310, ITEM3 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM3 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      if (radio.rds.filter) tftPrint(1, myLanguage[language][42], 310, ITEM4 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM4 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      if (radio.rds.pierrors) tftPrint(1, myLanguage[language][42], 310, ITEM5 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM5 + 6, PrimaryColor, PrimaryColorSmooth, 16);

      switch (af) {
        case 0: tftPrint(1, myLanguage[language][30], 310, ITEM6 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
        case 1: tftPrint(1, myLanguage[language][42], 310, ITEM6 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
        case 2: tftPrint(1, "AF REG", 310, ITEM6 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
      }

      if (radio.rds.rtbuffer) tftPrint(1, myLanguage[language][42], 310, ITEM7 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM7 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      if (radio.rds.sortaf) tftPrint(1, myLanguage[language][42], 310, ITEM8 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM8 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      if (radio.rds.fastps) tftPrint(1, myLanguage[language][42], 310, ITEM9 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM9 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      break;

    case FMSETTINGS:
      tftPrint(-1, myLanguage[language][21], 8, ITEM1 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][22], 8, ITEM2 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][23], 8, ITEM3 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][24], 8, ITEM4 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][28], 8, ITEM5 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][43], 8, ITEM6 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][65], 8, ITEM7 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][90], 8, ITEM8 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][100], 8, ITEM9 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][199], 8, ITEM10 + 6, ActiveColor, ActiveColorSmooth, 16);

      tftPrint(1, "MHz", 310, ITEM1 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(1, String(ConverterSet, DEC), 270, ITEM1 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      tftPrint(1, "MHz", 310, ITEM2 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(1, String(LowEdgeSet / 10 + ConverterSet, DEC) + "." + String(LowEdgeSet % 10 + ConverterSet, DEC), 270, ITEM2 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      tftPrint(1, "MHz", 310, ITEM3 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(1, String(HighEdgeSet / 10 + ConverterSet, DEC) + "." + String(HighEdgeSet % 10 + ConverterSet, DEC), 270, ITEM3 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      tftPrint(1, "dB", 310, ITEM4 + 6, ActiveColor, ActiveColorSmooth, 16);
      if (LevelOffset > 0) tftPrint(1, "+" + String(LevelOffset, DEC), 270, ITEM4 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, String(LevelOffset, DEC), 270, ITEM4 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      tftPrint(1, "dBμV", 310, ITEM5 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(1, String(LowLevelSet, DEC), 270, ITEM5 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      if (softmutefm) tftPrint(1, myLanguage[language][42], 310, ITEM6 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM6 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      if (fmnb != 0) tftPrint(1, "%", 310, ITEM7 + 6, ActiveColor, ActiveColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM7 + 6, ActiveColor, ActiveColorSmooth, 16);
      if (fmnb != 0) tftPrint(1, String(fmnb, DEC), 270, ITEM7 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM7 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      tftPrint(1, "KHz", 310, ITEM8 + 6, ActiveColor, ActiveColorSmooth, 16);
      if (fmdefaultstepsize) tftPrint(1, String(FREQ_FM_STEP_100K * 10, DEC), 270, ITEM8 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, String(FREQ_FM_STEP_50K * 10, DEC), 270, ITEM8 + 6, PrimaryColor, PrimaryColorSmooth, 16);

      switch (bandFM) {
        case FM_BAND_ALL: tftPrint(1, myLanguage[language][105] + String(",") + myLanguage[language][106], 310, ITEM9 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
        case FM_BAND_OIRT: tftPrint(1, myLanguage[language][106], 310, ITEM9 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
        case FM_BAND_FM: tftPrint(1, myLanguage[language][105], 310, ITEM9 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
      }
      if (fmdeemphasis != DEEMPHASIS_NONE) tftPrint(1, String((fmdeemphasis == DEEMPHASIS_50 ? FM_DEEMPHASIS_50 : FM_DEEMPHASIS_75), DEC), 270, ITEM10 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM10 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      if (fmdeemphasis != DEEMPHASIS_NONE) tftPrint(1, "μs", 310, ITEM10 + 6, ActiveColor, ActiveColorSmooth, 16);
      break;

    case AMSETTINGS:
      tftPrint(-1, myLanguage[language][44], 8, ITEM1 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][64], 8, ITEM2 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][97], 8, ITEM3 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][101], 8, ITEM4 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][59], 8, ITEM5 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][185], 8, ITEM6 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][187], 8, ITEM7 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][198], 8, ITEM8 + 6, ActiveColor, ActiveColorSmooth, 16);


      if (softmuteam) tftPrint(1, myLanguage[language][42], 310, ITEM1 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM1 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      if (amnb != 0) tftPrint(1, "%", 310, ITEM2 + 6, ActiveColor, ActiveColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM2 + 6, ActiveColor, ActiveColorSmooth, 16);
      if (amnb != 0) tftPrint(1, String(amnb, DEC), 270, ITEM2 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM2 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      tftPrint(1, "dB", 310, ITEM3 + 6, ActiveColor, ActiveColorSmooth, 16);
      if (AMLevelOffset > 0) tftPrint(1, "+" + String(AMLevelOffset, DEC), 270, ITEM3 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, String(AMLevelOffset, DEC), 270, ITEM3 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      if (amrfagc != 0) tftPrint(1, "dB", 310, ITEM8 + 6, ActiveColor, ActiveColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM8 + 6, PrimaryColor, PrimaryColorSmooth, 16);

      switch (bandAM) {
        case AM_BAND_ALL: tftPrint(1, myLanguage[language][102] + String(",") + myLanguage[language][103] + String(",") + myLanguage[language][104], 310, ITEM4 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
        case AM_BAND_LW_MW: tftPrint(1, myLanguage[language][102] + String(",") + myLanguage[language][103], 310, ITEM4 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
        case AM_BAND_LW_SW: tftPrint(1, myLanguage[language][102] + String(",") + myLanguage[language][104], 310, ITEM4 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
        case AM_BAND_MW_SW: tftPrint(1, myLanguage[language][103] + String(",") + myLanguage[language][104], 310, ITEM4 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
        case AM_BAND_LW: tftPrint(1, myLanguage[language][102], 310, ITEM4 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
        case AM_BAND_MW: tftPrint(1, myLanguage[language][103], 310, ITEM4 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
        case AM_BAND_SW: tftPrint(1, myLanguage[language][104], 310, ITEM4 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
      }

      if (showSWMIBand) tftPrint(1, myLanguage[language][42], 310, ITEM5 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM5 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      if (amcodect != 0) tftPrint(1, "%", 310, ITEM6 + 6, ActiveColor, ActiveColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM6 + 6, ActiveColor, ActiveColorSmooth, 16);
      if (amcodect != 0) tftPrint(1, String(amcodect, DEC), 270, ITEM6 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM6 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      tftPrint(1, String(amcodectcount, DEC), 310, ITEM7 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      if (amrfagc != 0) tftPrint(1, String(amrfagc, DEC), 270, ITEM8 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      break;

    case CONNECTIVITY:
      tftPrint(-1, myLanguage[language][50], 8, ITEM1 + 6, ActiveColor, ActiveColorSmooth, 16);
      if (wifi) tftPrint(-1, String(myLanguage[language][51]) + " IP: " + String(WiFi.localIP().toString()), 8, ITEM2 + 6, ActiveColor, ActiveColorSmooth, 16); else tftPrint(-1, myLanguage[language][51], 8, ITEM2 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][52], 8, ITEM3 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][58], 8, ITEM4 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][197], 8, ITEM5 + 6, ActiveColor, ActiveColorSmooth, 16);

      if (USBmode) tftPrint(1, "RDS Spy", 310, ITEM1 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, "XDRGTK", 310, ITEM1 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      if (wifi) tftPrint(1, myLanguage[language][42], 310, ITEM2 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM2 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      tftPrint(1, ">", 310, ITEM3 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      if (wifi) tftPrint(1, String(WiFi.localIP()[0]) + "." + String(WiFi.localIP()[1]) + "." + String(WiFi.localIP()[2]) + "." + String(subnetclient, DEC), 310, ITEM4 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, "-", 310, ITEM4 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      tftPrint(1, String(stationlistid, DEC), 310, ITEM5 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      break;

  }
  analogWrite(SMETERPIN, 0);
}

void BuildAdvancedRDS() {
  rdsreset = true;
  afscreen = false;
  afpage = false;
  afpagenr = 0;
  advancedRDS = true;
  ScreensaverTimerSet(OFF);
  if (theme == 0) {
    tft.fillScreen(BackgroundColor);
    tft.drawRect(0, 0, 320, 240, FrameColor);
    tft.drawLine(0, 30, 320, 30, FrameColor);
    tft.drawLine(0, 68, 320, 68, FrameColor);
    tft.drawLine(0, 104, 320, 104, FrameColor);
    tft.drawLine(0, 126, 320, 126, FrameColor);
    tft.drawLine(120, 30, 120, 0, FrameColor);
    tft.drawLine(210, 30, 210, 240, FrameColor);
    tft.drawLine(53, 30, 53, 0, FrameColor);
    tft.drawLine(89, 30, 89, 0, FrameColor);
    tft.drawLine(120, 30, 120, 0, FrameColor);
    tft.drawLine(158, 30, 158, 0, FrameColor);
    tft.drawLine(248, 30, 248, 0, FrameColor);
    tft.drawLine(0, 140, 210, 140, FrameColor);
    tft.drawLine(0, 166, 210, 166, FrameColor);
    tft.drawLine(0, 193, 210, 193, FrameColor);
    tft.drawLine(210, 191, 320, 191, FrameColor);
    tft.drawLine(0, 217, 210, 217, FrameColor);
    tft.drawRect(0, 0, 320, 240, FrameColor);

    tftPrint(-1, "ERRORS", 3, 34, ActiveColor, ActiveColorSmooth, 16);
    tftPrint(1, "MHz", 310, 35, ActiveColor, ActiveColorSmooth, 16);
    tftPrint(1, unitString[unit], 310, 51, ActiveColor, ActiveColorSmooth, 16);
    if (region == REGION_EU) tftPrint(-1, "PI", ITEM10 + 6, 81, ActiveColor, ActiveColorSmooth, 16);
    if (region == REGION_US) tftPrint(-1, "ID", ITEM10 + 6, 81, ActiveColor, ActiveColorSmooth, 16);
    tftPrint(-1, "PS", 3, 81, ActiveColor, ActiveColorSmooth, 16);
    tftPrint(-1, "PTY", 3, 109, ActiveColor, ActiveColorSmooth, 16);
    tftPrint(-1, "RT+", 3, 147, ActiveColor, ActiveColorSmooth, 16);
    tftPrint(-1, "AF", 3, 199, ActiveColor, ActiveColorSmooth, 16);
    tftPrint(-1, "EON", 3, 174, ActiveColor, ActiveColorSmooth, 16);
    tftPrint(-1, "RT", 3, 222, ActiveColor, ActiveColorSmooth, 16);

    tftPrint(-1, "A:", 66, 34, ActiveColor, ActiveColorSmooth, 16);
    tftPrint(-1, "B:", 104, 34, ActiveColor, ActiveColorSmooth, 16);
    tftPrint(-1, "C:", 142, 34, ActiveColor, ActiveColorSmooth, 16);
    tftPrint(-1, "D:", 180, 34, ActiveColor, ActiveColorSmooth, 16);
    tftPrint(-1, "ECC", 214, 193, ActiveColor, ActiveColorSmooth, 16);
    tftPrint(-1, "LIC", 214, 208, ActiveColor, ActiveColorSmooth, 16);
    tftPrint(-1, "PIN", 214, 223, ActiveColor, ActiveColorSmooth, 16);
    tftPrint(1, "Dynamic PTY", 300, 130, ActiveColor, ActiveColorSmooth, 16);
    tftPrint(1, "Artif. head", 300, 145, ActiveColor, ActiveColorSmooth, 16);
    tftPrint(1, "Compressed", 300, 160, ActiveColor, ActiveColorSmooth, 16);
    tftPrint(1, "Has stereo", 300, 175, ActiveColor, ActiveColorSmooth, 16);

    tft.fillCircle(86, 41, 5, SignificantColor);
    tft.fillCircle(124, 41, 5, SignificantColor);
    tft.fillCircle(162, 41, 5, SignificantColor);
    tft.fillCircle(200, 41, 5, SignificantColor);

    tft.fillCircle(310, 137, 5, SignificantColor);
    tft.fillCircle(310, 153, 5, SignificantColor);
    tft.fillCircle(310, 168, 5, SignificantColor);
    tft.fillCircle(310, 183, 5, SignificantColor);

    for (int i = 0; i < 33; i++) tft.fillCircle((6 * i) + 10, 133, 2, GreyoutColor);

    tftPrint(-1, "kHz", 203, 4, ActiveColor, ActiveColorSmooth, 28);

    tft.drawCircle(66, 15, 10, GreyoutColor);
    tft.drawCircle(66, 15, 9, GreyoutColor);
    tft.drawCircle(76, 15, 10, GreyoutColor);
    tft.drawCircle(76, 15, 9, GreyoutColor);
    tft.drawBitmap(122, 5, RDSLogo, 35, 22, GreyoutColor);

    if (!StereoToggle) {
      tft.drawCircle(71, 15, 10, SecondaryColor);
      tft.drawCircle(71, 15, 9, SecondaryColor);
    }

    tftPrint(-1, "TP", 2, 51, GreyoutColor, BackgroundColor, 16);
    tftPrint(-1, "TA", 25, 51, GreyoutColor, BackgroundColor, 16);
    tftPrint(-1, "AF", 52, 51, GreyoutColor, BackgroundColor, 16);
    tftPrint(-1, "-B", 70, 51, GreyoutColor, BackgroundColor, 16);
    tftPrint(-1, "TMC", 90, 51, GreyoutColor, BackgroundColor, 16);
    tftPrint(-1, "RT+", 127, 51, GreyoutColor, BackgroundColor, 16);
    tftPrint(-1, "EON", 155, 51, GreyoutColor, BackgroundColor, 16);
    tftPrint(-1, "S", 188, 51, GreyoutColor, BackgroundColor, 16);
    tftPrint(-1, "M", 196, 51, GreyoutColor, BackgroundColor, 16);
  }

  RDSstatusold = false;
  ShowFreq(0);
  Stereostatusold = false;
  SStatusold = 2000;
  SStatus = 100;
  rssiold = 2000;
  rdsblockold = 33;
  batteryold = 6;
  batteryVold = 0;
  vPerold = 0;
  ECCold = 253;
  strcpy(programTypePrevious, "");
  strcpy(radioIdPrevious, "");
  programServicePrevious = "";
  ptynold = " ";
  MSold = 0;
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
  hasrtplusold = false;
  eonstringold = "";
  afstringold = "";
  rtplusstringold = "";
  afmethodBold = false;
  rds_clockold = "";
  ShowMemoryPos();
}

void BuildDisplay() {
  afscreen = false;
  advancedRDS = false;
  int bandColor;
  if (theme == 0) {
    tft.fillScreen(BackgroundColor);
    tft.drawRect(0, 0, 320, 240, FrameColor);
    tft.drawLine(0, 30, 320, 30, FrameColor);
    tft.drawLine(0, 100, 320, 100, FrameColor);
    tft.drawLine(120, 30, 120, 0, FrameColor);
    tft.drawLine(210, 100, 210, 217, FrameColor);
    tft.drawLine(248, 30, 248, 0, FrameColor);
    tft.drawLine(0, 160, 210, 160, FrameColor);
    tft.drawLine(0, 180, 320, 180, FrameColor);
    tft.drawLine(0, 217, 320, 217, FrameColor);
    tft.drawLine(53, 30, 53, 0, FrameColor);
    tft.drawLine(89, 30, 89, 0, FrameColor);
    tft.drawLine(158, 30, 158, 0, FrameColor);
    tft.drawLine(20, 114, 204, 114, TFT_DARKGREY);
    if (!showmodulation) tft.drawLine(20, 143, 204, 143, GreyoutColor); else tft.drawLine(20, 143, 204, 143, TFT_DARKGREY);
    for (byte segments = 0; segments < 94; segments++) {
      if (segments > 54) {
        if (((segments - 53) % 10) == 0) {
          tft.fillRect(16 + (2 * segments), 112, 2, 2, BarSignificantColor);
          if (!showmodulation) tft.fillRect(16 + (2 * segments), 141, 2, 2, GreyoutColor); else tft.fillRect(16 + (2 * segments), 141, 2, 2, BarSignificantColor);
        }
      } else {
        if (((segments + 1) % 6) == 0) {
          tft.fillRect(16 + (2 * segments), 112, 2, 2, BarInsignificantColor);
          if (!showmodulation) tft.fillRect(16 + (2 * segments), 141, 2, 2, GreyoutColor); else tft.fillRect(16 + (2 * segments), 141, 2, 2, BarInsignificantColor);
        }
      }
    }
    if (showsquelch) tftPrint(-1, "SQ:", 212, 145, ActiveColor, ActiveColorSmooth, 16);
    tftPrint(1, "C/N", 270, 163, ActiveColor, ActiveColorSmooth, 16);
    tftPrint(-1, "dB", 300, 163, ActiveColor, ActiveColorSmooth, 16);
    if (region == REGION_EU) tftPrint(-1, "PI:", 212, 193, ActiveColor, ActiveColorSmooth, 16);
    if (region == REGION_US) tftPrint(-1, "ID:", 212, 193, ActiveColor, ActiveColorSmooth, 16);
    tftPrint(-1, "PS:", 3, 193, ActiveColor, ActiveColorSmooth, 16);
    tftPrint(-1, "RT:", 3, 221, ActiveColor, ActiveColorSmooth, 16);
    tftPrint(-1, "PTY:", 3, 163, ActiveColor, ActiveColorSmooth, 16);

    tftPrint(0, "S", 7, 101, ActiveColor, ActiveColorSmooth, 16);
    tftPrint(-1, "1", 24, 115, ActiveColor, ActiveColorSmooth, 16);
    tftPrint(-1, "3", 48, 115, ActiveColor, ActiveColorSmooth, 16);
    tftPrint(-1, "5", 72, 115, ActiveColor, ActiveColorSmooth, 16);
    tftPrint(-1, "7", ITEM4 + 6, 115, ActiveColor, ActiveColorSmooth, 16);
    tftPrint(-1, "9", 120, 115, ActiveColor, ActiveColorSmooth, 16);
    tftPrint(-1, "+10", 134, 115, ActiveColor, ActiveColorSmooth, 16);
    tftPrint(-1, "+30", 174, 115, ActiveColor, ActiveColorSmooth, 16);

    if (!showmodulation) {
      tftPrint(0, "M", 7, 128, GreyoutColor, BackgroundColor, 16);
      tftPrint(-1, "10", 27, 144, GreyoutColor, BackgroundColor, 16);
      tftPrint(-1, "30", 57, 144, GreyoutColor, BackgroundColor, 16);
      tftPrint(-1, "50", 87, 144, GreyoutColor, BackgroundColor, 16);
      tftPrint(-1, "70", 117, 144, GreyoutColor, BackgroundColor, 16);
      tftPrint(-1, "100", 164, 144, GreyoutColor, BackgroundColor, 16);
    } else {
      tftPrint(0, "M", 7, 128, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, "10", 27, 144, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, "30", 57, 144, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, "50", 87, 144, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, "70", 117, 144, ActiveColor, BackgroundColor, 16);
      tftPrint(-1, "100", 164, 144, ActiveColor, ActiveColorSmooth, 16);
    }

    tftPrint(-1, "kHz", 203, 4, ActiveColor, ActiveColorSmooth, 28);
    tftPrint(-1, unitString[unit], 282, 145, ActiveColor, ActiveColorSmooth, 16);

    if (band < BAND_GAP) tftPrint(-1, "MHz", 258, ITEM3 + 6, ActiveColor, ActiveColorSmooth, 28); else tftPrint(-1, "kHz", 258, ITEM3 + 6, ActiveColor, ActiveColorSmooth, 28);

    tft.drawRoundRect(248, ITEM2 + 6, 32, 20, 5, GreyoutColor);
    if (band > BAND_GAP) tftPrint(0, "iMS", 265, 59, GreyoutColor, BackgroundColor, 16);
    tft.drawRoundRect(286, ITEM2 + 6, 32, 20, 5, GreyoutColor);
    if (band > BAND_GAP) tftPrint(0, "EQ", 303, 59, GreyoutColor, BackgroundColor, 16);

    tft.drawCircle(66, 15, 10, GreyoutColor);
    tft.drawCircle(66, 15, 9, GreyoutColor);
    tft.drawCircle(76, 15, 10, GreyoutColor);
    tft.drawCircle(76, 15, 9, GreyoutColor);
    tft.drawBitmap(122, 5, RDSLogo, 35, 22, GreyoutColor);
    if (!StereoToggle) {
      tft.drawCircle(71, 15, 10, SecondaryColor);
      tft.drawCircle(71, 15, 9, SecondaryColor);
    }

    if (bandforbidden) bandColor = GreyoutColor; else bandColor = PrimaryColor;
    switch (band) {
      case BAND_LW: tftPrint(-1, myLanguage[language][102], 70, 32, bandColor, PrimaryColorSmooth, 16); break;
      case BAND_MW: tftPrint(-1, myLanguage[language][103], 70, 32, bandColor, PrimaryColorSmooth, 16); break;
      case BAND_SW: tftPrint(-1, myLanguage[language][104], 70, 32, bandColor, PrimaryColorSmooth, 16); break;
      case BAND_FM: tftPrint(-1, myLanguage[language][105], 70, 32, bandColor, PrimaryColorSmooth, 16); break;
      case BAND_OIRT: tftPrint(-1, myLanguage[language][106], 70, 32, bandColor, PrimaryColorSmooth, 16); break;
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
  CNold = 254;
  af_counterold = 254;
  batteryold = 6;
  batteryVold = 0;
  vPerold = 0;
  rds_clockold = "";
  strcpy(programTypePrevious, "");
  strcpy(radioIdPrevious, "");
  programServicePrevious = "";
  BWreset = true;
  if (band < BAND_GAP) tftPrint(-1, "MHz", 258, ITEM3 + 6, ActiveColor, ActiveColorSmooth, 28); else tftPrint(-1, "kHz", 258, ITEM3 + 6, ActiveColor, ActiveColorSmooth, 28);
}

void MenuUp() {
  if (!menuopen) {
    tft.drawRoundRect(3, menuoption + 3, 315, 21, 5, BackgroundColor);
    if (hardwaremodel == BASE_ILI9341) {
      menuoption += ITEM_GAP;
      menuitem++;
      if (menuitem > items[menupage] - 1) {
        menuitem = 0;
        menuoption = ITEM1;
      }
    } else {
      menuoption -= ITEM_GAP;
      menuitem--;
      if (menuitem > 10) {
        menuoption = ITEM10;
        menuitem = 9;
        while (menuitem > items[menupage] - 1) {
          menuoption -= ITEM_GAP;
          menuitem --;
        }
      }
    }
    tft.drawRoundRect(3, menuoption + 3, 315, 21, 5, ActiveColor);
  } else {
    switch (menupage) {
      case MAINSETTINGS:
        switch (menuoption) {
          case ITEM1:
            switch (hardwaremodelold) {
              case BASE_ILI9341: tftPrint(0, myLanguage[language][109], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case PORTABLE_ILI9341: tftPrint(0, myLanguage[language][110], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case PORTABLE_TOUCH_ILI9341: tftPrint(0, myLanguage[language][111], 155, 118, BackgroundColor, BackgroundColor, 28); break;
            }

            hardwaremodel++;
            if (hardwaremodel > RADIO_HARDWARE_CNT - 1) hardwaremodel = 0;

            switch (hardwaremodel) {
              case BASE_ILI9341: tftPrint(0, myLanguage[language][109], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case PORTABLE_ILI9341: tftPrint(0, myLanguage[language][110], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case PORTABLE_TOUCH_ILI9341: tftPrint(0, myLanguage[language][111], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
            }
            hardwaremodelold = hardwaremodel;
            break;

          case ITEM2:
            if (touchrotating) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (touchrotating) touchrotating = 0; else touchrotating = 1;
            if (touchrotating) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM3:
            if (spispeed == SPI_SPEED_DEFAULT) tftPrint(0,  myLanguage[language][78] + String(SPI_FREQUENCY / 1000000, DEC) + " Mhz", 155, 118, BackgroundColor, BackgroundColor, 28);
            else tftPrint(0, String(spispeed * 10 ,DEC) + " Mhz", 155, 118, BackgroundColor, BackgroundColor, 28);

            spispeed++;
            if (spispeed > SPI_SPEED_COUNT - 1) spispeed = 0;

            if (spispeed == SPI_SPEED_DEFAULT) tftPrint(0,  myLanguage[language][78] + String(SPI_FREQUENCY / 1000000, DEC) + " Mhz", 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            else tftPrint(0, String(spispeed * 10 ,DEC) + " Mhz", 155, 118, PrimaryColor, PrimaryColorSmooth, 28);

            if (spispeed == SPI_SPEED_DEFAULT) SPI.setFrequency(SPI_FREQUENCY); else SPI.setFrequency(spispeed * 1000000);
            spispeedold = spispeed;
            break;
        }
        break;

      case AUDIOSETTINGS:
        switch (menuoption) {
          case ITEM1:
            if (VolSet > 0) tftPrint(1, "+" + String(VolSet, DEC), 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(1, String(VolSet, DEC), 155, 118, BackgroundColor, BackgroundColor, 28);
            VolSet++;
            if (VolSet > 10) VolSet = 10;
            if (VolSet > 0) tftPrint(1, "+" + String(VolSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(1, String(VolSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            radio.setVolume(VolSet);
            break;

          case ITEM2:
            if (edgebeep) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (edgebeep) edgebeep = false; else edgebeep = true;
            if (edgebeep) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM3:
            if (audiomode) tftPrint(0, "MPX", 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, "Stereo", 155, 118, BackgroundColor, BackgroundColor, 28);
            if (audiomode) audiomode = false; else audiomode = true;
            if (audiomode) tftPrint(0, "MPX", 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, "Stereo", 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            radio.setAudio(audiomode);
            break;

          case ITEM4:
            if (StereoLevel != 0) tftPrint(1, String(StereoLevel, DEC), 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (StereoLevel != 0) tftPrint(-1, "dBμV", 170, 118, BackgroundColor, BackgroundColor, 28);
            StereoLevel ++;
            if (StereoLevel > 60 || StereoLevel <= 30) {
              if (StereoLevel == 1) StereoLevel = 30; else StereoLevel = 0;
            }
            if (StereoLevel != 0) tftPrint(-1, "dBμV", 170, 118, PrimaryColor, PrimaryColorSmooth, 28);
            if (StereoLevel != 0) tftPrint(1, String(StereoLevel, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            radio.setStereoLevel(StereoLevel);
            break;

          case ITEM5:
            tftPrint(1, String(HighCutLevel * 100, DEC), 155, 118, BackgroundColor, BackgroundColor, 28);
            HighCutLevel ++;
            if (HighCutLevel > 70) HighCutLevel = 15;
            tftPrint(1, String(HighCutLevel * 100, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            radio.setHighCutLevel(HighCutLevel);
            break;

          case ITEM6:
            if (HighCutOffset != 0) tftPrint(-1, "dBμV", 170, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (HighCutOffset != 0) tftPrint(1, String(HighCutOffset, DEC), 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            HighCutOffset ++;
            if (HighCutOffset > 60 || HighCutOffset <= 20) {
              if (HighCutOffset == 1) HighCutOffset = 20; else HighCutOffset = 0;
            }
            if (HighCutOffset != 0) tftPrint(-1, "dBμV", 170, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            if (HighCutOffset != 0) tftPrint(1, String(HighCutOffset, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            radio.setHighCutOffset(HighCutOffset);
            break;
        }
        break;

      case DISPLAYSETTINGS:
        switch (menuoption) {
          case ITEM1:
            tftPrint(0, myLanguage[language][0], 155, 118, BackgroundColor, BackgroundColor, 28);
            language ++;
            if (language == (sizeof (myLanguage) / sizeof (myLanguage[0]))) language = 0;
            tftPrint(0, myLanguage[language][0], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM2:
            tftPrint(1, String(ContrastSet, DEC), 155, 118, BackgroundColor, BackgroundColor, 28);
            ContrastSet ++;
            if (ContrastSet > 100) ContrastSet = 1;
            tftPrint(1, String(ContrastSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            analogWrite(CONTRASTPIN, ContrastSet * 2 + 27);
            break;

          case ITEM3:
            if (showsquelch) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (showsquelch) showsquelch = false; else showsquelch = true;
            if (showsquelch) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM4:
            if (showmodulation) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (showmodulation) showmodulation = false; else showmodulation = true;
            if (showmodulation) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM5:
            CurrentTheme ++;
            if (CurrentTheme > 10) CurrentTheme = 0;
            doTheme();
            tft.drawRoundRect(10, 30, 300, 170, 5, ActiveColor);
            tft.fillRoundRect(12, 32, 296, 166, 5, BackgroundColor);
            tftPrint(0, myLanguage[language][77], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            tftPrint(0, CurrentThemeString, 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM6:
            if (screensaverset) tftPrint(-1, myLanguage[language][92], 170, 118, BackgroundColor, BackgroundColor, 28);
            if (!screensaverset) tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(1, String(screensaverOptions[screensaverset]), 155, 118, BackgroundColor, BackgroundColor, 28);
            screensaverset ++;
            if (screensaverset > sizeof(screensaverOptions) / sizeof(screensaverOptions[0]) - 1) screensaverset = 0;
            if (screensaverset) tftPrint(-1, myLanguage[language][92], 170, 118, PrimaryColor, PrimaryColorSmooth, 28);
            if (!screensaverset) tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(1, String(screensaverOptions[screensaverset]), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM7:
            switch (poweroptionsold) {
              case LCD_OFF: tftPrint(0, myLanguage[language][76], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case LCD_BRIGHTNESS_1_PERCENT: tftPrint(0, myLanguage[language][94], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case LCD_BRIGHTNESS_A_QUARTER: tftPrint(0, myLanguage[language][95], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case LCD_BRIGHTNESS_HALF: tftPrint(0, myLanguage[language][96], 155, 118, BackgroundColor, BackgroundColor, 28); break;
            }

            poweroptions++;
            if (poweroptions > RADIO_POWER_MODE_CNT - 1) poweroptions = 0;

            switch (poweroptions) {
              case LCD_OFF: tftPrint(0, myLanguage[language][76], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case LCD_BRIGHTNESS_1_PERCENT: tftPrint(0, myLanguage[language][94], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case LCD_BRIGHTNESS_A_QUARTER: tftPrint(0, myLanguage[language][95], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case LCD_BRIGHTNESS_HALF: tftPrint(0, myLanguage[language][96], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
            }
            poweroptionsold = poweroptions;
            break;

          case ITEM8:
            switch (batteryoptionsold) {
              case BATTERY_NONE: tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case BATTERY_VALUE: tftPrint(0, myLanguage[language][174], 155, 118, BackgroundColor, BackgroundColor, 28); break;
			  case BATTERY_VALUE2: tftPrint(0, myLanguage[language][207], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case BATTERY_PERCENT: tftPrint(0, myLanguage[language][175], 155, 118, BackgroundColor, BackgroundColor, 28); break;
            }

            batteryoptions++;
            if (batteryoptions > RADIO_BATTERY_CNT - 1) batteryoptions = 0;

            switch (batteryoptions) {
              case BATTERY_NONE: tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case BATTERY_VALUE: tftPrint(0, myLanguage[language][174], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
			  case BATTERY_VALUE2: tftPrint(0, myLanguage[language][207], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case BATTERY_PERCENT: tftPrint(0, myLanguage[language][175], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
            }
            batteryoptionsold = batteryoptions;
            break;

          case ITEM9:
            tftPrint(0, String(unitString[unit]), 155, 118, BackgroundColor, BackgroundColor, 28);
            unit ++;
            if (unit > 2) unit = 0;
            tftPrint(0, String(unitString[unit]), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM10:
            if (tot != 0) tftPrint(0, String(tot) + " " + myLanguage[language][205], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            switch (tot) {
              case 0: tot = 15; break;
              case 15: tot = 30; break;
              case 30: tot = 60; break;
              case 60: tot = 90; break;
              default: tot = 0; break;
            }
            if (tot != 0) tftPrint(0, String(tot) + " " + myLanguage[language][205], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;
        }
        break;

      case RDSSETTINGS:
        switch (menuoption) {
          case ITEM1:
            switch (showrdserrors) {
              case 0: tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case 1: tftPrint(0, myLanguage[language][200], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case 2: tftPrint(0, myLanguage[language][201], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case 3: tftPrint(0, myLanguage[language][202], 155, 118, BackgroundColor, BackgroundColor, 28); break;
            }
            showrdserrors++;
            if (showrdserrors > 3) showrdserrors = 0;

            switch (showrdserrors) {
              case 0: tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case 1: tftPrint(0, myLanguage[language][200], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case 2: tftPrint(0, myLanguage[language][201], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case 3: tftPrint(0, myLanguage[language][202], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
            }
            break;

          case ITEM2:
            if (region == REGION_EU) tftPrint(0, myLanguage[language][47], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (region == REGION_US) tftPrint(0, myLanguage[language][48], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (region == REGION_EU) region = REGION_US; else region = REGION_EU;
            if (region == REGION_EU) tftPrint(0, myLanguage[language][47], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            if (region == REGION_US) tftPrint(0, myLanguage[language][48], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            regionold = region;
            if (region == REGION_EU) {
              fmdeemphasis = DEEMPHASIS_50;
              radio.setDeemphasis(fmdeemphasis);
            }
            if (region == REGION_US) {
              fmdeemphasis = DEEMPHASIS_75;
              radio.setDeemphasis(fmdeemphasis);
            }
            radio.rds.region = region;
            break;

          case ITEM3:
            if (radio.rds.underscore) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (radio.rds.underscore) radio.rds.underscore = false; else radio.rds.underscore = true;
            if (radio.rds.underscore) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM4:
            if (radio.rds.filter) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (radio.rds.filter) radio.rds.filter = false; else radio.rds.filter = true;
            if (radio.rds.filter) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM5:
            if (radio.rds.pierrors) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (radio.rds.pierrors) radio.rds.pierrors = false; else radio.rds.pierrors = true;
            if (radio.rds.pierrors) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM6:
            switch (af) {
              case 0: tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case 1: tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case 2: tftPrint(0, "AF REG", 155, 118, BackgroundColor, BackgroundColor, 28); break;
            }
            af++;
            if (af > 2) af = 0;

            switch (af) {
              case 0: tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case 1: tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case 2: tftPrint(0, "AF REG", 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
            }
            break;

          case ITEM7:
            if (radio.rds.rtbuffer) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (radio.rds.rtbuffer) radio.rds.rtbuffer = false; else radio.rds.rtbuffer = true;
            if (radio.rds.rtbuffer) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM8:
            if (radio.rds.sortaf) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (radio.rds.sortaf) radio.rds.sortaf = false; else radio.rds.sortaf = true;
            if (radio.rds.sortaf) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM9:
            if (radio.rds.fastps) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (radio.rds.fastps) radio.rds.fastps = false; else radio.rds.fastps = true;
            if (radio.rds.fastps) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;
        }
        break;

      case FMSETTINGS:
        switch (menuoption) {
          case ITEM1:
            tftPrint(1, String(ConverterSet, DEC), 155, 118, BackgroundColor, BackgroundColor, 28);
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
            tftPrint(1, String(ConverterSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM2:
            tftPrint(1, String(LowEdgeSet / 10 + ConverterSet, DEC) + "." + String(LowEdgeSet % 10 + ConverterSet, DEC), 155, 118, BackgroundColor, BackgroundColor, 28);
            LowEdgeSet ++;
            if (LowEdgeSet > 1070) LowEdgeSet = 650;
            tftPrint(1, String(LowEdgeSet / 10 + ConverterSet, DEC) + "." + String(LowEdgeSet % 10 + ConverterSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM3:
            tftPrint(1, String(HighEdgeSet / 10 + ConverterSet, DEC) + "." + String(HighEdgeSet % 10 + ConverterSet, DEC), 155, 118, BackgroundColor, BackgroundColor, 28);
            HighEdgeSet ++;
            if (HighEdgeSet > 1080) HighEdgeSet = 660;
            tftPrint(1, String(HighEdgeSet / 10 + ConverterSet, DEC) + "." + String(HighEdgeSet % 10 + ConverterSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM4:
            if (LevelOffset > 0) tftPrint(1, "+" + String(LevelOffset, DEC), 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(1, String(LevelOffset, DEC), 155, 118, BackgroundColor, BackgroundColor, 28);
            LevelOffset++;
            if (LevelOffset > 15) LevelOffset = -25;
            if (LevelOffset > 0) tftPrint(1, "+" + String(LevelOffset, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(1, String(LevelOffset, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            radio.setOffset(LevelOffset);
            change = true;
            break;

          case ITEM5:
            tftPrint(1, String(LowLevelSet, DEC), 145, 118, BackgroundColor, BackgroundColor, 28);
            LowLevelSet++;
            if (LowLevelSet > 30) LowLevelSet = -15;
            tftPrint(1, String(LowLevelSet, DEC), 145, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM6:
            if (softmutefm) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (softmutefm) softmutefm = false; else softmutefm = true;
            if (softmutefm) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            radio.setSoftmuteFM(softmutefm);
            break;

          case ITEM7:
            if (fmnb != 0) tftPrint(1, String(fmnb, DEC), 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (fmnb != 0) tftPrint(-1, "%", 170, 118, BackgroundColor, BackgroundColor, 28);
            fmnb ++;
            if (fmnb > 150 || fmnb <= 50) {
              if (fmnb == 1) fmnb = 50; else fmnb = 0;
            }
            if (fmnb != 0) tftPrint(1, String(fmnb, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            if (fmnb != 0) tftPrint(-1, "%", 170, 118, PrimaryColor, PrimaryColorSmooth, 28);
            radio.setFMNoiseBlanker(fmnb);
            break;

          case ITEM8:
            if (fmdefaultstepsize) tftPrint(1, String(FREQ_FM_STEP_100K * 10, DEC), 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(1, String(FREQ_FM_STEP_50K * 10, DEC), 155, 118, BackgroundColor, BackgroundColor, 28);
            if (fmdefaultstepsize) fmdefaultstepsize = 0; else fmdefaultstepsize = 1;
            if (fmdefaultstepsize) tftPrint(1, String(FREQ_FM_STEP_100K * 10, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(1, String(FREQ_FM_STEP_50K * 10, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM9:
            switch (bandFM) {
              case FM_BAND_ALL: tftPrint(0, myLanguage[language][105] + String(",") + myLanguage[language][106], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case FM_BAND_OIRT: tftPrint(0, myLanguage[language][106], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case FM_BAND_FM: tftPrint(0, myLanguage[language][105], 155, 118, BackgroundColor, BackgroundColor, 28); break;
            }

            bandFM++;
            if (bandFM > FM_BAND_CNT - 1) bandFM = FM_BAND_ALL;

            switch (bandFM) {
              case FM_BAND_ALL: tftPrint(0, myLanguage[language][105] + String(",") + myLanguage[language][106], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case FM_BAND_OIRT: tftPrint(0, myLanguage[language][106], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case FM_BAND_FM: tftPrint(0, myLanguage[language][105], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
            }
            break;

          case ITEM10:
            tftPrint(0, myLanguage[language][199], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            if (fmdeemphasis != DEEMPHASIS_NONE) tftPrint(1, String((fmdeemphasis == DEEMPHASIS_50 ? FM_DEEMPHASIS_50 : FM_DEEMPHASIS_75), DEC), 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(1, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (fmnb != 0) tftPrint(-1, "μs", 170, 118, ActiveColor, ActiveColor, 28);
            if (fmdeemphasis != DEEMPHASIS_NONE) tftPrint(-1, "μs", 170, 118, BackgroundColor, BackgroundColor, 28);
            fmdeemphasis++;
            if (fmdeemphasis > DEEMPHASIS_COUNT - 1) fmdeemphasis = DEEMPHASIS_NONE;
            if (fmdeemphasis != DEEMPHASIS_NONE) tftPrint(1, String((fmdeemphasis == DEEMPHASIS_50 ? FM_DEEMPHASIS_50 : FM_DEEMPHASIS_75), DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(1, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            if (fmdeemphasis != DEEMPHASIS_NONE) tftPrint(-1, "μs", 170, 118, ActiveColor, PrimaryColorSmooth, 28);
            radio.setDeemphasis(fmdeemphasis);
            break;

        }
        break;

      case AMSETTINGS:
        switch (menuoption) {
          case ITEM1:
            if (softmuteam) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (softmuteam) softmuteam = false; else softmuteam = true;
            if (softmuteam) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            radio.setSoftmuteAM(softmuteam);
            break;

          case ITEM2:
            if (amnb != 0) tftPrint(1, String(amnb, DEC), 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (amnb != 0) tftPrint(-1, "%", 170, 118, BackgroundColor, BackgroundColor, 28);
            amnb ++;
            if (amnb > 150 || amnb <= 50) {
              if (amnb == 1) amnb = 50; else amnb = 0;
            }
            if (amnb != 0) tftPrint(1, String(amnb, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            if (amnb != 0) tftPrint(-1, "%", 170, 118, PrimaryColor, PrimaryColorSmooth, 28);
            radio.setAMNoiseBlanker(amnb);
            break;

          case ITEM3:
            if (AMLevelOffset > 0) tftPrint(1, "+" + String(AMLevelOffset, DEC), 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(1, String(AMLevelOffset, DEC), 155, 118, BackgroundColor, BackgroundColor, 28);
            AMLevelOffset++;
            if (AMLevelOffset > 15) AMLevelOffset = -50;
            if (AMLevelOffset > 0) tftPrint(1, "+" + String(AMLevelOffset, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(1, String(AMLevelOffset, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            radio.setAMOffset(AMLevelOffset);
            break;

          case ITEM4:
            switch (bandAM) {
              case AM_BAND_ALL: tftPrint(0, myLanguage[language][102] + String(",") + myLanguage[language][103] + String(",") + myLanguage[language][104], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case AM_BAND_LW_MW: tftPrint(0, myLanguage[language][102] + String(",") + myLanguage[language][103], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case AM_BAND_LW_SW: tftPrint(0, myLanguage[language][102] + String(",") + myLanguage[language][104], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case AM_BAND_MW_SW: tftPrint(0, myLanguage[language][103] + String(",") + myLanguage[language][104], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case AM_BAND_LW: tftPrint(0, myLanguage[language][102], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case AM_BAND_MW: tftPrint(0, myLanguage[language][103], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case AM_BAND_SW: tftPrint(0, myLanguage[language][104], 155, 118, BackgroundColor, BackgroundColor, 28); break;
            }

            bandAM++;
            if (bandAM > AM_BAND_CNT - 1) bandAM = AM_BAND_ALL;

            switch (bandAM) {
              case AM_BAND_ALL: tftPrint(0, myLanguage[language][102] + String(",") + myLanguage[language][103] + String(",") + myLanguage[language][104], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case AM_BAND_LW_MW: tftPrint(0, myLanguage[language][102] + String(",") + myLanguage[language][103], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case AM_BAND_LW_SW: tftPrint(0, myLanguage[language][102] + String(",") + myLanguage[language][104], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case AM_BAND_MW_SW: tftPrint(0, myLanguage[language][103] + String(",") + myLanguage[language][104], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case AM_BAND_LW: tftPrint(0, myLanguage[language][102], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case AM_BAND_MW: tftPrint(0, myLanguage[language][103], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case AM_BAND_SW: tftPrint(0, myLanguage[language][104], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
            }
            break;

          case ITEM5:
            if (showSWMIBand) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (showSWMIBand) showSWMIBand = false; else showSWMIBand = true;
            if (showSWMIBand) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM6:
            if (amcodect != 0) tftPrint(0, String(amcodect, DEC) + " %", 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            amcodect++;
            if (amcodect > 150 || amcodect <= 50) {
              if (amcodect == 1) amcodect = 50; else amcodect = 0;
            }
            if (amcodect != 0) tftPrint(0, String(amcodect, DEC) + " %", 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            if (band > BAND_GAP) radio.setAMCoChannel(amcodect, amcodectcount);
            break;

          case ITEM7:
            tftPrint(0, String(amcodectcount, DEC), 155, 118, BackgroundColor, BackgroundColor, 28);
            amcodectcount++;
            if (amcodectcount > 15) amcodectcount = 1;
            tftPrint(0, String(amcodectcount, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            if (band > BAND_GAP) radio.setAMCoChannel(amcodect, amcodectcount);
            break;

          case ITEM8:
            if (amrfagc != 0) tftPrint(1, String(amrfagc, DEC), 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (amrfagc != 0) tftPrint(-1, "dB", 170, 118, BackgroundColor, BackgroundColor, 28);
            amrfagc += 6;
            if (amrfagc > 36) amrfagc = 0;
            if (amrfagc != 0) tftPrint(1, String(amrfagc, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            if (amrfagc != 0) tftPrint(-1, "dB", 170, 118, PrimaryColor, PrimaryColorSmooth, 28);
            if (band > BAND_GAP) radio.setAMAttenuation(amrfagc);
            break;

        }
        break;

      case CONNECTIVITY:
        switch (menuoption) {
          case ITEM1:
            if (USBmode) tftPrint(0, "RDS Spy", 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, "XDRGTK", 155, 118, BackgroundColor, BackgroundColor, 28);
            if (USBmode) USBmode = false; else USBmode = true;
            if (USBmode) tftPrint(0, "RDS Spy", 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, "XDRGTK", 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM2:
            if (wifi) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (wifi) wifi = false; else wifi = true;
            if (wifi) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM4:
            tftPrint(0, String(WiFi.localIP()[0]) + "." + String(WiFi.localIP()[1]) + "." + String(WiFi.localIP()[2]) + "." + String(subnetclient, DEC), 155, 118, BackgroundColor, BackgroundColor, 28);
            subnetclient ++;
            if (subnetclient > 254) subnetclient = 1;
            tftPrint(0, String(WiFi.localIP()[0]) + "." + String(WiFi.localIP()[1]) + "." + String(WiFi.localIP()[2]) + "." + String(subnetclient, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM5:
            tftPrint(0, String(stationlistid, DEC), 155, 118, BackgroundColor, BackgroundColor, 28);
            stationlistid ++;
            if (stationlistid > 10) stationlistid = 1;
            tftPrint(0, String(stationlistid, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;
        }
        break;
    }
  }
}

void MenuDown() {
  if (!menuopen) {
    tft.drawRoundRect(3, menuoption + 3, 315, 21, 5, BackgroundColor);
    if (hardwaremodel == BASE_ILI9341) {
      menuoption -= ITEM_GAP;
      menuitem--;
      if (menuitem > 10) {
        menuoption = ITEM10;
        menuitem = 9;
        while (menuitem > items[menupage] - 1) {
          menuoption -= ITEM_GAP;
          menuitem --;
        }
      }
    } else {
      menuoption += ITEM_GAP;
      menuitem++;
      if (menuitem > items[menupage] - 1) {
        menuitem = 0;
        menuoption = ITEM1;
      }
    }
    tft.drawRoundRect(3, menuoption + 3, 315, 21, 5, ActiveColor);
  } else {
    switch (menupage) {
      case MAINSETTINGS:
        switch (menuoption) {
          case ITEM1:
            switch (hardwaremodelold) {
              case BASE_ILI9341: tftPrint(0, myLanguage[language][109], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case PORTABLE_ILI9341: tftPrint(0, myLanguage[language][110], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case PORTABLE_TOUCH_ILI9341: tftPrint(0, myLanguage[language][111], 155, 118, BackgroundColor, BackgroundColor, 28); break;
            }

            hardwaremodel--;
            if (hardwaremodel > RADIO_HARDWARE_CNT - 1) hardwaremodel = RADIO_HARDWARE_CNT - 1;

            switch (hardwaremodel) {
              case BASE_ILI9341: tftPrint(0, myLanguage[language][109], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case PORTABLE_ILI9341: tftPrint(0, myLanguage[language][110], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case PORTABLE_TOUCH_ILI9341: tftPrint(0, myLanguage[language][111], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
            }
            hardwaremodelold = hardwaremodel;
            break;

          case ITEM2:
            if (touchrotating) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (touchrotating) touchrotating = 0; else touchrotating = 1;
            if (touchrotating) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;
          case ITEM3:
            if (spispeed == SPI_SPEED_DEFAULT) tftPrint(0,  myLanguage[language][78] + String(SPI_FREQUENCY / 1000000, DEC) + " Mhz", 155, 118, BackgroundColor, BackgroundColor, 28);
            else tftPrint(0, String(spispeed * 10 ,DEC) + " Mhz", 155, 118, BackgroundColor, BackgroundColor, 28);

            spispeed--;
            if (spispeed > SPI_SPEED_COUNT - 1) spispeed = SPI_SPEED_COUNT - 1;

            if (spispeed == SPI_SPEED_DEFAULT) tftPrint(0,  myLanguage[language][78] + String(SPI_FREQUENCY / 1000000, DEC) + " Mhz", 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            else tftPrint(0, String(spispeed * 10 ,DEC) + " Mhz", 155, 118, PrimaryColor, PrimaryColorSmooth, 28);

            if (spispeed == SPI_SPEED_DEFAULT) SPI.setFrequency(SPI_FREQUENCY); else SPI.setFrequency(spispeed * 1000000);
            spispeedold = spispeed;
            break;

        }
        break;

      case AUDIOSETTINGS:
        switch (menuoption) {
          case ITEM1:
            if (VolSet > 0) tftPrint(1, "+" + String(VolSet, DEC), 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(1, String(VolSet, DEC), 155, 118, BackgroundColor, BackgroundColor, 28);
            VolSet--;
            if (VolSet < -10) VolSet = -10;
            if (VolSet > 10) VolSet = 10;
            if (VolSet > 0) tftPrint(1, "+" + String(VolSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(1, String(VolSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            radio.setVolume(VolSet);
            break;

          case ITEM2:
            if (edgebeep) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (edgebeep) edgebeep = false; else edgebeep = true;
            if (edgebeep) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM3:
            if (audiomode) tftPrint(0, "MPX", 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, "Stereo", 155, 118, BackgroundColor, BackgroundColor, 28);
            if (audiomode) audiomode = false; else audiomode = true;
            if (audiomode) tftPrint(0, "MPX", 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, "Stereo", 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            radio.setAudio(audiomode);
            break;

          case ITEM4:
            if (StereoLevel != 0) tftPrint(1, String(StereoLevel, DEC), 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (StereoLevel != 0) tftPrint(-1, "dBμV", 170, 118, BackgroundColor, BackgroundColor, 28);
            StereoLevel --;
            if (StereoLevel < 30 || StereoLevel > 60) {
              if (StereoLevel > 60) StereoLevel = 60; else StereoLevel = 0;
            }
            if (StereoLevel != 0) tftPrint(-1, "dBμV", 170, 118, PrimaryColor, PrimaryColorSmooth, 28);
            if (StereoLevel != 0) tftPrint(1, String(StereoLevel, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            radio.setStereoLevel(StereoLevel);
            break;

          case ITEM5:
            tftPrint(1, String(HighCutLevel * 100, DEC), 155, 118, BackgroundColor, BackgroundColor, 28);
            HighCutLevel --;
            if (HighCutLevel < 15 || HighCutLevel > 70) HighCutLevel = 70;
            tftPrint(1, String(HighCutLevel * 100, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            radio.setHighCutLevel(HighCutLevel);
            break;

          case ITEM6:
            if (HighCutOffset != 0) tftPrint(-1, "dBμV", 170, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (HighCutOffset != 0) tftPrint(1, String(HighCutOffset, DEC), 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(1, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            HighCutOffset --;
            if (HighCutOffset < 20 || HighCutOffset > 60) {
              if (HighCutOffset > 60) HighCutOffset = 60; else HighCutOffset = 0;
            }
            if (HighCutOffset != 0) tftPrint(-1, "dBμV", 170, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            if (HighCutOffset != 0) tftPrint(1, String(HighCutOffset, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            radio.setHighCutOffset(HighCutOffset);
            break;
        }
        break;

      case DISPLAYSETTINGS:
        switch (menuoption) {
          case ITEM1:
            tftPrint(0, myLanguage[language][0], 155, 118, BackgroundColor, BackgroundColor, 28);
            language --;
            if (language > (sizeof (myLanguage) / sizeof (myLanguage[0]))) language = (sizeof (myLanguage) / sizeof (myLanguage[0])) - 1;
            tftPrint(0, myLanguage[language][0], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM2:
            tftPrint(1, String(ContrastSet, DEC), 155, 118, BackgroundColor, BackgroundColor, 28);
            ContrastSet --;
            if (ContrastSet < 1) ContrastSet = 100;
            tftPrint(1, String(ContrastSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            analogWrite(CONTRASTPIN, ContrastSet * 2 + 27);
            break;

          case ITEM3:
            if (showsquelch) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (showsquelch) showsquelch = false; else showsquelch = true;
            if (showsquelch) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM4:
            if (showmodulation) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (showmodulation) showmodulation = false; else showmodulation = true;
            if (showmodulation) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM5:
            CurrentTheme --;
            if (CurrentTheme > 10) CurrentTheme = 10;
            doTheme();
            tft.drawRoundRect(10, 30, 300, 170, 5, ActiveColor);
            tft.fillRoundRect(12, 32, 296, 166, 5, BackgroundColor);
            tftPrint(0, myLanguage[language][77], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            tftPrint(0, CurrentThemeString, 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM6:
            if (screensaverset) tftPrint(-1, myLanguage[language][92], 170, 118, BackgroundColor, BackgroundColor, 28);
            if (!screensaverset) tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(1, String(screensaverOptions[screensaverset]), 155, 118, BackgroundColor, BackgroundColor, 28);
            screensaverset --;
            if (screensaverset > sizeof(screensaverOptions) / sizeof(screensaverOptions[0]) - 1) screensaverset = sizeof(screensaverOptions) / sizeof(screensaverOptions[0]) - 1;
            if (screensaverset) tftPrint(-1, myLanguage[language][92], 170, 118, PrimaryColor, PrimaryColorSmooth, 28);
            if (!screensaverset) tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(1, String(screensaverOptions[screensaverset]), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM7:
            switch (poweroptionsold) {
              case LCD_OFF: tftPrint(0, myLanguage[language][76], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case LCD_BRIGHTNESS_1_PERCENT: tftPrint(0, myLanguage[language][94], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case LCD_BRIGHTNESS_A_QUARTER: tftPrint(0, myLanguage[language][95], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case LCD_BRIGHTNESS_HALF: tftPrint(0, myLanguage[language][96], 155, 118, BackgroundColor, BackgroundColor, 28); break;
            }

            poweroptions--;
            if (poweroptions > RADIO_POWER_MODE_CNT - 1) poweroptions = RADIO_POWER_MODE_CNT - 1;

            switch (poweroptions) {
              case LCD_OFF: tftPrint(0, myLanguage[language][76], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case LCD_BRIGHTNESS_1_PERCENT: tftPrint(0, myLanguage[language][94], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case LCD_BRIGHTNESS_A_QUARTER: tftPrint(0, myLanguage[language][95], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case LCD_BRIGHTNESS_HALF: tftPrint(0, myLanguage[language][96], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
            }
            poweroptionsold = poweroptions;
            break;

          case ITEM8:
            switch (batteryoptionsold) {
              case BATTERY_NONE: tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case BATTERY_VALUE: tftPrint(0, myLanguage[language][174], 155, 118, BackgroundColor, BackgroundColor, 28); break;
			  case BATTERY_VALUE2: tftPrint(0, myLanguage[language][207], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case BATTERY_PERCENT: tftPrint(0, myLanguage[language][175], 155, 118, BackgroundColor, BackgroundColor, 28); break;
            }

            batteryoptions--;
            if (batteryoptions > RADIO_BATTERY_CNT - 1) batteryoptions = RADIO_BATTERY_CNT - 1;

            switch (batteryoptions) {
              case BATTERY_NONE: tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case BATTERY_VALUE: tftPrint(0, myLanguage[language][174], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
			  case BATTERY_VALUE2: tftPrint(0, myLanguage[language][207], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case BATTERY_PERCENT: tftPrint(0, myLanguage[language][175], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
            }
            batteryoptionsold = batteryoptions;
            break;

          case ITEM9:
            tftPrint(0, String(unitString[unit]), 155, 118, BackgroundColor, BackgroundColor, 28);
            unit --;
            if (unit > 2) unit = 2;
            tftPrint(0, String(unitString[unit]), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM10:
            if (tot != 0) tftPrint(0, String(tot) + " " + myLanguage[language][205], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            switch (tot) {
              case 15: tot = 0; break;
              case 30: tot = 15; break;
              case 60: tot = 30; break;
              case 90: tot = 60; break;
              default: tot = 90; break;
            }
            if (tot != 0) tftPrint(0, String(tot) + " " + myLanguage[language][205], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;
        }
        break;

      case RDSSETTINGS:
        switch (menuoption) {
          case ITEM1:
            switch (showrdserrors) {
              case 0: tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case 1: tftPrint(0, myLanguage[language][200], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case 2: tftPrint(0, myLanguage[language][201], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case 3: tftPrint(0, myLanguage[language][202], 155, 118, BackgroundColor, BackgroundColor, 28); break;
            }
            showrdserrors--;
            if (showrdserrors > 3) showrdserrors = 3;

            switch (showrdserrors) {
              case 0: tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case 1: tftPrint(0, myLanguage[language][200], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case 2: tftPrint(0, myLanguage[language][201], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case 3: tftPrint(0, myLanguage[language][202], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
            }
            break;

          case ITEM2:
            if (region == REGION_EU) tftPrint(0, myLanguage[language][47], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (region == REGION_US) tftPrint(0, myLanguage[language][48], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (region == REGION_EU) region = REGION_US; else region = REGION_EU;
            if (region == REGION_EU) tftPrint(0, myLanguage[language][47], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            if (region == REGION_US) tftPrint(0, myLanguage[language][48], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            regionold = region;
            if (region == REGION_EU) {
              fmdeemphasis = DEEMPHASIS_50;
              radio.setDeemphasis(fmdeemphasis);
            }
            if (region == REGION_US) {
              fmdeemphasis = DEEMPHASIS_75;
              radio.setDeemphasis(fmdeemphasis);
            }
            radio.rds.region = region;
            break;

          case ITEM3:
            if (radio.rds.underscore) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (radio.rds.underscore) radio.rds.underscore = false; else radio.rds.underscore = true;
            if (radio.rds.underscore) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM4:
            if (radio.rds.filter) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (radio.rds.filter) radio.rds.filter = false; else radio.rds.filter = true;
            if (radio.rds.filter) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM5:
            if (radio.rds.pierrors) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (radio.rds.pierrors) radio.rds.pierrors = false; else radio.rds.pierrors = true;
            if (radio.rds.pierrors) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM6:
            switch (af) {
              case 0: tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case 1: tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case 2: tftPrint(0, "AF REG", 155, 118, BackgroundColor, BackgroundColor, 28); break;
            }
            af--;
            if (af > 2) af = 2;

            switch (af) {
              case 0: tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case 1: tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case 2: tftPrint(0, "AF REG", 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
            }
            break;

          case ITEM7:
            if (radio.rds.rtbuffer) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (radio.rds.rtbuffer) radio.rds.rtbuffer = false; else radio.rds.rtbuffer = true;
            if (radio.rds.rtbuffer) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM8:
            if (radio.rds.sortaf) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (radio.rds.sortaf) radio.rds.sortaf = false; else radio.rds.sortaf = true;
            if (radio.rds.sortaf) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM9:
            if (radio.rds.fastps) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (radio.rds.fastps) radio.rds.fastps = false; else radio.rds.fastps = true;
            if (radio.rds.fastps) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;
        }
        break;

      case FMSETTINGS:
        switch (menuoption) {
          case ITEM1:
            tftPrint(1, String(ConverterSet, DEC), 155, 118, BackgroundColor, BackgroundColor, 28);
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
            tftPrint(1, String(ConverterSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM2:
            tftPrint(1, String(LowEdgeSet / 10 + ConverterSet, DEC) + "." + String(LowEdgeSet % 10 + ConverterSet, DEC), 155, 118, BackgroundColor, BackgroundColor, 28);
            LowEdgeSet -= 10;
            if (LowEdgeSet < 650) LowEdgeSet = 1079;
            tftPrint(1, String(LowEdgeSet / 10 + ConverterSet, DEC) + "." + String(LowEdgeSet % 10 + ConverterSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM3:
            tftPrint(1, String(HighEdgeSet / 10 + ConverterSet, DEC) + "." + String(HighEdgeSet % 10 + ConverterSet, DEC), 155, 118, BackgroundColor, BackgroundColor, 28);
            HighEdgeSet -= 10;
            if (HighEdgeSet < 660) HighEdgeSet = 1080;
            tftPrint(1, String(HighEdgeSet / 10 + ConverterSet, DEC) + "." + String(HighEdgeSet % 10 + ConverterSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM4:
            if (LevelOffset > 0) tftPrint(1, "+" + String(LevelOffset, DEC), 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(1, String(LevelOffset, DEC), 155, 118, BackgroundColor, BackgroundColor, 28);
            LevelOffset--;
            if (LevelOffset < -25) LevelOffset = 15;
            if (LevelOffset > 0) tftPrint(1, "+" + String(LevelOffset, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(1, String(LevelOffset, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);                radio.setOffset(LevelOffset);
            change = true;
            break;

          case ITEM5:
            tftPrint(1, String(LowLevelSet, DEC), 145, 118, BackgroundColor, BackgroundColor, 28);
            LowLevelSet--;
            if (LowLevelSet < -15) LowLevelSet = 30;
            tftPrint(1, String(LowLevelSet, DEC), 145, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM6:
            if (softmutefm) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (softmutefm) softmutefm = false; else softmutefm = true;
            if (softmutefm) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            radio.setSoftmuteFM(softmutefm);
            break;

          case ITEM7:
            if (fmnb != 0) tftPrint(1, String(fmnb, DEC), 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (fmnb != 0) tftPrint(-1, "%", 170, 118, BackgroundColor, BackgroundColor, 28);
            fmnb --;
            if (fmnb > 150 || fmnb <= 50) {
              if (fmnb > 150) fmnb = 150; else fmnb = 0;
            }
            if (fmnb != 0) tftPrint(1, String(fmnb, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            if (fmnb != 0) tftPrint(-1, "%", 170, 118, PrimaryColor, PrimaryColorSmooth, 28);
            radio.setFMNoiseBlanker(fmnb);
            break;

          case ITEM8:
            if (fmdefaultstepsize) tftPrint(1, String(FREQ_FM_STEP_100K * 10, DEC), 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(1, String(FREQ_FM_STEP_50K * 10, DEC), 155, 118, BackgroundColor, BackgroundColor, 28);
            if (fmdefaultstepsize) fmdefaultstepsize = 0; else fmdefaultstepsize = 1;
            if (fmdefaultstepsize) tftPrint(1, String(FREQ_FM_STEP_100K * 10, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(1, String(FREQ_FM_STEP_50K * 10, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM9:
            switch (bandFM) {
              case FM_BAND_ALL: tftPrint(0, myLanguage[language][105] + String(",") + myLanguage[language][106], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case FM_BAND_OIRT: tftPrint(0, myLanguage[language][106], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case FM_BAND_FM: tftPrint(0, myLanguage[language][105], 155, 118, BackgroundColor, BackgroundColor, 28); break;
            }

            bandFM--;
            if (bandFM > FM_BAND_CNT) bandFM = FM_BAND_FM;

            switch (bandFM) {
              case FM_BAND_ALL: tftPrint(0, myLanguage[language][105] + String(",") + myLanguage[language][106], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case FM_BAND_OIRT: tftPrint(0, myLanguage[language][106], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case FM_BAND_FM: tftPrint(0, myLanguage[language][105], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
            }
            break;

          case ITEM10:
            tftPrint(0, myLanguage[language][199], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            if (fmdeemphasis != DEEMPHASIS_NONE) tftPrint(1, String((fmdeemphasis == DEEMPHASIS_50 ? FM_DEEMPHASIS_50 : FM_DEEMPHASIS_75), DEC), 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(1, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (fmdeemphasis != DEEMPHASIS_NONE) tftPrint(-1, "μs", 170, 118, BackgroundColor, BackgroundColor, 28);
            fmdeemphasis--;
            if (fmdeemphasis > DEEMPHASIS_COUNT - 1) fmdeemphasis = DEEMPHASIS_COUNT - 1;
            if (fmdeemphasis != DEEMPHASIS_NONE) tftPrint(1, String((fmdeemphasis == DEEMPHASIS_50 ? FM_DEEMPHASIS_50 : FM_DEEMPHASIS_75), DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(1, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            if (fmdeemphasis != DEEMPHASIS_NONE) tftPrint(-1, "μs", 170, 118, ActiveColor, PrimaryColorSmooth, 28);
            radio.setDeemphasis(fmdeemphasis);
            break;

        }
        break;

      case AMSETTINGS:
        switch (menuoption) {
          case ITEM1:
            if (softmuteam) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (softmuteam) softmuteam = false; else softmuteam = true;
            if (softmuteam) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            radio.setSoftmuteAM(softmuteam);
            break;

          case ITEM2:
            if (amnb != 0) tftPrint(1, String(amnb, DEC), 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (amnb != 0) tftPrint(-1, "%", 170, 118, BackgroundColor, BackgroundColor, 28);
            amnb --;
            if (amnb > 150 || amnb <= 50) {
              if (amnb > 150) amnb = 150; else amnb = 0;
            }
            if (amnb != 0) tftPrint(1, String(amnb, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            if (amnb != 0) tftPrint(-1, "%", 170, 118, PrimaryColor, PrimaryColorSmooth, 28);
            radio.setAMNoiseBlanker(amnb);
            break;

          case ITEM3:
            if (AMLevelOffset > 0) tftPrint(1, "+" + String(AMLevelOffset, DEC), 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(1, String(AMLevelOffset, DEC), 155, 118, BackgroundColor, BackgroundColor, 28);
            AMLevelOffset--;
            if (AMLevelOffset < -50) AMLevelOffset = 15;
            if (AMLevelOffset > 0) tftPrint(1, "+" + String(AMLevelOffset, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(1, String(AMLevelOffset, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            radio.setAMOffset(AMLevelOffset);
            break;

          case ITEM4:
            switch (bandAM) {
              case AM_BAND_ALL: tftPrint(0, myLanguage[language][102] + String(",") + myLanguage[language][103] + String(",") + myLanguage[language][104], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case AM_BAND_LW_MW: tftPrint(0, myLanguage[language][102] + String(",") + myLanguage[language][103], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case AM_BAND_LW_SW: tftPrint(0, myLanguage[language][102] + String(",") + myLanguage[language][104], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case AM_BAND_MW_SW: tftPrint(0, myLanguage[language][103] + String(",") + myLanguage[language][104], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case AM_BAND_LW: tftPrint(0, myLanguage[language][102], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case AM_BAND_MW: tftPrint(0, myLanguage[language][103], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case AM_BAND_SW: tftPrint(0, myLanguage[language][104], 155, 118, BackgroundColor, BackgroundColor, 28); break;
            }

            bandAM--;
            if (bandAM > AM_BAND_CNT) bandAM = AM_BAND_SW;

            switch (bandAM) {
              case AM_BAND_ALL: tftPrint(0, myLanguage[language][102] + String(",") + myLanguage[language][103] + String(",") + myLanguage[language][104], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case AM_BAND_LW_MW: tftPrint(0, myLanguage[language][102] + String(",") + myLanguage[language][103], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case AM_BAND_LW_SW: tftPrint(0, myLanguage[language][102] + String(",") + myLanguage[language][104], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case AM_BAND_MW_SW: tftPrint(0, myLanguage[language][103] + String(",") + myLanguage[language][104], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case AM_BAND_LW: tftPrint(0, myLanguage[language][102], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case AM_BAND_MW: tftPrint(0, myLanguage[language][103], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case AM_BAND_SW: tftPrint(0, myLanguage[language][104], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
            }
            break;

          case ITEM5:
            if (showSWMIBand) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (showSWMIBand) showSWMIBand = false; else showSWMIBand = true;
            if (showSWMIBand) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM6:
            if (amcodect != 0) tftPrint(0, String(amcodect, DEC) + " %", 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            amcodect--;
            if (amcodect < 50 || amcodect > 150) {
              if (amcodect > 150) amcodect = 150; else amcodect = 0;
            }
            if (amcodect != 0) tftPrint(0, String(amcodect, DEC) + " %", 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            if (band > BAND_GAP) radio.setAMCoChannel(amcodect, amcodectcount);
            break;

          case ITEM7:
            tftPrint(0, String(amcodectcount, DEC), 155, 118, BackgroundColor, BackgroundColor, 28);
            amcodectcount--;
            if (amcodectcount < 1) amcodectcount = 15;
            tftPrint(0, String(amcodectcount, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            if (band > BAND_GAP) radio.setAMCoChannel(amcodect, amcodectcount);
            break;

          case ITEM8:
            if (amrfagc != 0) tftPrint(1, String(amrfagc, DEC), 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (amrfagc != 0) tftPrint(-1, "dB", 170, 118, BackgroundColor, BackgroundColor, 28);
            amrfagc -= 6;
            if (amrfagc > 36) amrfagc = 36;
            if (amrfagc != 0) tftPrint(1, String(amrfagc, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            if (amrfagc != 0) tftPrint(-1, "dB", 170, 118, PrimaryColor, PrimaryColorSmooth, 28);
            if (band > BAND_GAP) radio.setAMAttenuation(amrfagc);
            break;

        }
        break;

      case CONNECTIVITY:
        switch (menuoption) {
          case ITEM1:
            if (USBmode) tftPrint(0, "RDS Spy", 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, "XDRGTK", 155, 118, BackgroundColor, BackgroundColor, 28);
            if (USBmode) USBmode = false; else USBmode = true;
            if (USBmode) tftPrint(0, "RDS Spy", 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, "XDRGTK", 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM2:
            if (wifi) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (wifi) wifi = false; else wifi = true;
            if (wifi) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM4:
            tftPrint(0, String(WiFi.localIP()[0]) + "." + String(WiFi.localIP()[1]) + "." + String(WiFi.localIP()[2]) + "." + String(subnetclient, DEC), 155, 118, BackgroundColor, BackgroundColor, 28);
            subnetclient --;
            if (subnetclient < 1) subnetclient = 254;
            tftPrint(0, String(WiFi.localIP()[0]) + "." + String(WiFi.localIP()[1]) + "." + String(WiFi.localIP()[2]) + "." + String(subnetclient, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM5:
            tftPrint(0, String(stationlistid, DEC), 155, 118, BackgroundColor, BackgroundColor, 28);
            stationlistid --;
            if (stationlistid == 0) stationlistid = 10;
            tftPrint(0, String(stationlistid, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;
        }
        break;
    }
  }
}

void DoMenu() {
  if (!menuopen) {
    if (menupage != INDEX) {
      menuopen = true;
      tft.drawRoundRect(10, 30, 300, 170, 5, ActiveColor);
      tft.fillRoundRect(12, 32, 296, 166, 5, BackgroundColor);
    }

    switch (menupage) {
      case INDEX:
        switch (menuoption) {
          case ITEM1:
            menupage = MAINSETTINGS;
            menuoption = ITEM1;
            menuitem = 0;
            submenu = true;
            BuildMenu();
            break;

          case ITEM2:
            menupage = AUDIOSETTINGS;
            menuoption = ITEM1;
            menuitem = 0;
            submenu = true;
            BuildMenu();
            break;

          case ITEM3:
            menupage = DISPLAYSETTINGS;
            menuoption = ITEM1;
            menuitem = 0;
            submenu = true;
            BuildMenu();
            break;

          case ITEM4:
            menupage = RDSSETTINGS;
            menuoption = ITEM1;
            menuitem = 0;
            submenu = true;
            BuildMenu();
            break;

          case ITEM5:
            menupage = FMSETTINGS;
            menuoption = ITEM1;
            menuitem = 0;
            submenu = true;
            BuildMenu();
            break;

          case ITEM6:
            menupage = AMSETTINGS;
            menuoption = ITEM1;
            menuitem = 0;
            submenu = true;
            BuildMenu();
            break;

          case ITEM7:
            menupage = CONNECTIVITY;
            menuoption = ITEM1;
            menuitem = 0;
            submenu = true;
            BuildMenu();
            break;

          case ITEM8:
            menuopen = true;
            tft.drawRoundRect(10, 10, 300, 220, 5, ActiveColor);
            tft.fillRoundRect(12, 12, 296, 216, 5, BackgroundColor);
            tftPrint(0, myLanguage[language][71], 155, 18, ActiveColor, ActiveColorSmooth, 28);
            tftPrint(0, myLanguage[language][72], 155, 68, ActiveColor, ActiveColorSmooth, 28);
            tftPrint(0, "PE5PVB", 155, 48, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(1, "ohmytime", 145, 98, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(1, "HyperDX", 145, 113, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(-1, "MCelliotG", 155, 98, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(-1, "andimik", 155, 113, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(1, "DXHR05", 145, 128, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(1, "NoobishSVK", 145, 143, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(-1, "yo2ldk", 155, 128, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(-1, "Justin_Peng(Portable)", 155, 143, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(1, "Overland DX", 145, 158, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(-1, "elektronik232", 155, 158, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(1, "KOTYA8", 145, 173, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(-1, "mrwish7", 155, 173, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(1, "lxsxl", 145, 188, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(0, "github.com/PE5PVB/TEF6686_ESP32", 155, 208, ActiveColor, ActiveColorSmooth, 16);
            break;
        }
        break;

      case MAINSETTINGS:
        switch (menuoption) {
          case ITEM1:
            tftPrint(0, myLanguage[language][108], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            switch (hardwaremodel) {
              case BASE_ILI9341: tftPrint(0, myLanguage[language][109], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case PORTABLE_ILI9341: tftPrint(0, myLanguage[language][110], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case PORTABLE_TOUCH_ILI9341: tftPrint(0, myLanguage[language][111], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
            }
            hardwaremodelold = hardwaremodel;
            break;

          case ITEM2:
            tftPrint(0, myLanguage[language][107], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            if (touchrotating) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM3:
            tftPrint(0, myLanguage[language][206], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            if (spispeed == SPI_SPEED_DEFAULT) tftPrint(0,  myLanguage[language][78] + String(SPI_FREQUENCY / 1000000, DEC) + " Mhz", 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            else tftPrint(0, String(spispeed * 10 ,DEC) + " Mhz", 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

        }
        break;

      case AUDIOSETTINGS:
        switch (menuoption) {
          case ITEM1:
            tftPrint(0, myLanguage[language][10], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            tftPrint(-1, "dB", 170, 118, ActiveColor, ActiveColorSmooth, 28);
            if (VolSet > 0) tftPrint(1, "+" + String(VolSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(1, String(VolSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM2:
            tftPrint(0, myLanguage[language][45], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            if (edgebeep) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM3:
            tftPrint(0, myLanguage[language][67], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            if (audiomode) tftPrint(0, "MPX", 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, "Stereo", 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM4:
            tftPrint(0, myLanguage[language][15], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            if (StereoLevel != 0) tftPrint(-1, "dBμV", 170, 118, ActiveColor, ActiveColorSmooth, 28);
            if (StereoLevel != 0) tftPrint(1, String(StereoLevel, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM5:
            tftPrint(0, myLanguage[language][16], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            if (HighCutLevel != 0) tftPrint(-1, "Hz", 170, 118, ActiveColor, ActiveColorSmooth, 28);
            if (HighCutLevel != 0) tftPrint(1, String(HighCutLevel * 100, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM6:
            tftPrint(0, myLanguage[language][17], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            if (HighCutOffset != 0) tftPrint(-1, "dBμV", 170, 118, ActiveColor, ActiveColorSmooth, 28);
            if (HighCutOffset != 0) tftPrint(1, String(HighCutOffset, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;
        }
        break;

      case DISPLAYSETTINGS:
        switch (menuoption) {
          case ITEM1:
            tftPrint(0, myLanguage[language][40], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            tftPrint(0, myLanguage[language][0], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM2:
            tftPrint(0, myLanguage[language][19], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            tftPrint(-1, "%", 170, 118, ActiveColor, ActiveColorSmooth, 28);
            tftPrint(1, String(ContrastSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM3:
            tftPrint(0, myLanguage[language][62], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            if (showsquelch) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM4:
            tftPrint(0, myLanguage[language][63], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            if (showmodulation) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM5:
            tftPrint(0, myLanguage[language][77], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            tftPrint(0, CurrentThemeString, 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM6:
            tftPrint(0, myLanguage[language][91], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            if (screensaverset) tftPrint(-1, myLanguage[language][92], 170, 118, PrimaryColor, PrimaryColorSmooth, 28);
            if (!screensaverset) tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(1, String(screensaverOptions[screensaverset], DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM7:
            tftPrint(0, myLanguage[language][74], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            switch (poweroptions) {
              case LCD_OFF: tftPrint(0, myLanguage[language][76], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case LCD_BRIGHTNESS_1_PERCENT: tftPrint(0, myLanguage[language][94], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case LCD_BRIGHTNESS_A_QUARTER: tftPrint(0, myLanguage[language][95], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case LCD_BRIGHTNESS_HALF: tftPrint(0, myLanguage[language][96], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
            }
            poweroptionsold = poweroptions;
            break;

          case ITEM8:
            tftPrint(0, myLanguage[language][173], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            switch (batteryoptions) {
              case BATTERY_NONE: tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case BATTERY_VALUE: tftPrint(0, myLanguage[language][174], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
			  case BATTERY_VALUE2: tftPrint(0, myLanguage[language][207], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case BATTERY_PERCENT: tftPrint(0, myLanguage[language][175], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
            }
            batteryoptionsold = batteryoptions;
            break;

          case ITEM9:
            tftPrint(0, myLanguage[language][98], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            tftPrint(0, unitString[unit], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM10:
            tftPrint(0, myLanguage[language][75], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            if (tot != 0) tftPrint(0, String(tot) + " " + myLanguage[language][205], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;
        }
        break;

      case RDSSETTINGS:
        switch (menuoption) {
          case ITEM1:
            tftPrint(0, myLanguage[language][38], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            switch (showrdserrors) {
              case 0: tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case 1: tftPrint(0, myLanguage[language][200], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case 2: tftPrint(0, myLanguage[language][201], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case 3: tftPrint(0, myLanguage[language][202], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
            }
            break;

          case ITEM2:
            tftPrint(0, myLanguage[language][46], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            if (region == REGION_EU) tftPrint(0, myLanguage[language][47], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            if (region == REGION_US) tftPrint(0, myLanguage[language][48], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM3:
            tftPrint(0, myLanguage[language][49], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            if (radio.rds.underscore) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM4:
            tftPrint(0, myLanguage[language][60], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            if (radio.rds.filter) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM5:
            tftPrint(0, myLanguage[language][61], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            if (radio.rds.pierrors) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM6:
            tftPrint(0, myLanguage[language][99], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            switch (af) {
              case 0: tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case 1: tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case 2: tftPrint(0, "AF REG", 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
            }
            break;

          case ITEM7:
            tftPrint(0, myLanguage[language][176], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            if (radio.rds.rtbuffer) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM8:
            tftPrint(0, myLanguage[language][196], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            if (radio.rds.sortaf) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM9:
            tftPrint(0, myLanguage[language][203], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            if (radio.rds.fastps) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;
        }
        break;

      case FMSETTINGS:
        switch (menuoption) {
          case ITEM1:
            tftPrint(0, myLanguage[language][11], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            tftPrint(-1, "MHz", 170, 118, ActiveColor, ActiveColorSmooth, 28);
            tftPrint(1, String(ConverterSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM2:
            tftPrint(0, myLanguage[language][12], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            tftPrint(-1, "MHz", 170, 118, ActiveColor, ActiveColorSmooth, 28);
            tftPrint(1, String(LowEdgeSet / 10 + ConverterSet, DEC) + "." + String(LowEdgeSet % 10 + ConverterSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM3:
            tftPrint(0, myLanguage[language][13], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            tftPrint(-1, "MHz", 170, 118, ActiveColor, ActiveColorSmooth, 28);
            tftPrint(1, String(HighEdgeSet / 10 + ConverterSet, DEC) + "." + String(HighEdgeSet % 10 + ConverterSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM4:
            tftPrint(0, myLanguage[language][14], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            tftPrint(-1, "dB", 170, 118, ActiveColor, ActiveColorSmooth, 28);
            tftPrint(-1, "dBμV", 190, 165, ActiveColor, ActiveColorSmooth, 28);
            if (LevelOffset > 0) tftPrint(1, "+" + String(LevelOffset, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(1, String(LevelOffset, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            SStatusold = 2000;
            change = true;
            break;

          case ITEM5:
            tftPrint(0, myLanguage[language][18], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            tftPrint(-1, "dBμV", 155, 118, ActiveColor, ActiveColorSmooth, 28);
            tftPrint(1, String(LowLevelSet, DEC), 145, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM6:
            tftPrint(0, myLanguage[language][43], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            if (softmutefm) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM7:
            tftPrint(0, myLanguage[language][65], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            if (fmnb != 0) tftPrint(-1, "%", 170, 118, PrimaryColor, PrimaryColorSmooth, 28);
            if (fmnb != 0) tftPrint(1, String(fmnb, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM8:
            tftPrint(-1, "KHz", 170, 118, ActiveColor, ActiveColorSmooth, 28);
            tftPrint(0, myLanguage[language][90], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            if (fmdefaultstepsize) tftPrint(1, String(FREQ_FM_STEP_100K * 10, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(1, String(FREQ_FM_STEP_50K * 10, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM9:
            tftPrint(0, myLanguage[language][100], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            switch (bandFM) {
              case FM_BAND_ALL: tftPrint(0, myLanguage[language][105] + String(",") + myLanguage[language][106], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case FM_BAND_OIRT: tftPrint(0, myLanguage[language][106], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case FM_BAND_FM: tftPrint(0, myLanguage[language][105], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
            }
            break;

          case ITEM10:
            tftPrint(0, myLanguage[language][199], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            if (fmdeemphasis != DEEMPHASIS_NONE) tftPrint(1, String((fmdeemphasis == DEEMPHASIS_50 ? FM_DEEMPHASIS_50 : FM_DEEMPHASIS_75), DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(1, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            if (fmdeemphasis != DEEMPHASIS_NONE) tftPrint(-1, "μs", 170, 118, ActiveColor, PrimaryColorSmooth, 28);
            break;

        }
        break;

      case AMSETTINGS:
        switch (menuoption) {
          case ITEM1:
            tftPrint(0, myLanguage[language][44], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            if (softmuteam) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM2:
            tftPrint(0, myLanguage[language][64], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            if (amnb != 0) tftPrint(-1, "%", 170, 118, PrimaryColor, PrimaryColorSmooth, 28);
            if (amnb != 0) tftPrint(1, String(amnb, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM3:
            tftPrint(0, myLanguage[language][97], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            tftPrint(-1, "dB", 170, 118, ActiveColor, ActiveColorSmooth, 28);
            if (AMLevelOffset > 0) tftPrint(1, "+" + String(AMLevelOffset, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(1, String(AMLevelOffset, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM4:
            tftPrint(0, myLanguage[language][101], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            switch (bandAM) {
              case AM_BAND_ALL: tftPrint(0, myLanguage[language][102] + String(",") + myLanguage[language][103] + String(",") + myLanguage[language][104], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case AM_BAND_LW_MW: tftPrint(0, myLanguage[language][102] + String(",") + myLanguage[language][103], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case AM_BAND_LW_SW: tftPrint(0, myLanguage[language][102] + String(",") + myLanguage[language][104], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case AM_BAND_MW_SW: tftPrint(0, myLanguage[language][103] + String(",") + myLanguage[language][104], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case AM_BAND_LW: tftPrint(0, myLanguage[language][102], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case AM_BAND_MW: tftPrint(0, myLanguage[language][103], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case AM_BAND_SW: tftPrint(0, myLanguage[language][104], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
            }
            break;

          case ITEM5:
            tftPrint(0, myLanguage[language][59], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            if (showSWMIBand) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM6:
            tftPrint(0, myLanguage[language][186], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            if (amcodect != 0) tftPrint(0, String(amcodect, DEC) + " %", 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM7:
            tftPrint(0, myLanguage[language][188], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            tftPrint(0, String(amcodectcount, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM8:
            tftPrint(0, myLanguage[language][198], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            if (amrfagc != 0) tftPrint(-1, "dB", 170, 118, PrimaryColor, PrimaryColorSmooth, 28);
            if (amrfagc != 0) tftPrint(1, String(amrfagc, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

        }
        break;

      case CONNECTIVITY:
        switch (menuoption) {
          case ITEM1:
            tftPrint(0, myLanguage[language][50], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            if (USBmode) tftPrint(0, "RDS Spy", 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, "XDRGTK", 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM2:
            tftPrint(0, myLanguage[language][51], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            if (wifi) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM3: {
              tftPrint(0, myLanguage[language][53], 155, 58, ActiveColor, ActiveColorSmooth, 28);
              tftPrint(0, "ESP_" + String(ESP_getChipId()), 155, 98, PrimaryColor, PrimaryColorSmooth, 28);
              tftPrint(0, myLanguage[language][54], 155, 138, ActiveColor, ActiveColorSmooth, 28);
              tftPrint(0, "http://192.168.4.1", 155, 174, PrimaryColor, PrimaryColorSmooth, 16);
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
              wifi = true;
              tryWiFi();
              delay(2000);
              menuopen = false;
              BuildMenu();
            } break;

          case ITEM4:
            if (wifi) {
              tftPrint(0, myLanguage[language][58], 155, 78, ActiveColor, ActiveColorSmooth, 28);
              tftPrint(0, String(WiFi.localIP()[0]) + "." + String(WiFi.localIP()[1]) + "." + String(WiFi.localIP()[2]) + "." + String(subnetclient, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            } else {
              menuopen = false;
              BuildMenu();
            }
            break;

          case ITEM5:
            tftPrint(0, myLanguage[language][197], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            tftPrint(0, String(stationlistid, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;
        }
        break;
    }
  } else {
    if (menupage == CONNECTIVITY && menuoption == ITEM2) {
      tryWiFi();
      if (wifi) delay(2000);
    }
    if (menupage == DISPLAYSETTINGS && menuoption == ITEM5) {
      doTheme();
    }
    menuopen = false;
    BuildMenu();
  }
}
