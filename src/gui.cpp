#include "gui.h"
#include "language.h"
#include "constants.h"
#include "FONT16.h"
#include "FONT16_CHS.h"
#include "FONT28.h"
#include "FONT28_CHS.h"
#include <WiFi.h>
#include <Wire.h>
#include <EEPROM.h>

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
    tft.fillScreen(BackgroundColor);
    tft.drawRect(0, 0, 320, 240, FrameColor);
    tft.drawLine(0, 30, 320, 30, FrameColor);
    tft.drawLine(0, 199, 320, 199, FrameColor);
    tft.drawLine(0, 218, 320, 218, FrameColor);
    tft.drawLine(168, 30, 168, 199, FrameColor);
    tft.drawLine(108, 30, 108, 0, FrameColor);
    tft.drawLine(137, 30, 137, 0, FrameColor);
    tft.drawLine(175, 30, 175, 0, FrameColor);
    tft.drawLine(268, 30, 268, 0, FrameColor);
    tftPrint(-1, "kHz", 222, 4, ActiveColor, ActiveColorSmooth, FONT28);
    tftPrint(0, myLanguage[language][93], 160, 222, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, myLanguage[language][88], 184, 48, PrimaryColor, PrimaryColorSmooth, FONT16);
    tftPrint(-1, myLanguage[language][87], 6, 48, PrimaryColor, PrimaryColorSmooth, FONT16);
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

void BuildMenu() {
  advancedRDS = false;
  tft.fillScreen(BackgroundColor);
  tft.drawRect(0, 0, 320, 240, FrameColor);
  tft.drawLine(0, 23, 320, 23, FrameColor);
  tftPrint(-1, myLanguage[language][41], 4, 7, PrimaryColor, PrimaryColorSmooth, FONT16);
  tftPrint(1, String(menupage) + "/" + String(menupagestotal), 314, 7, ActiveColor, ActiveColorSmooth, FONT16);
  tft.drawRoundRect(3, menuoption + 3, 315, 21, 5, ActiveColor);
  switch (menupage) {
    case 1:
      tftPrint(1, "dB", 310, 36, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(1, "MHz", 310, 56, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(1, "MHz", 310, 76, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(1, "MHz", 310, 96, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(1, "dB", 310, 116, ActiveColor, ActiveColorSmooth, FONT16);
      if (StereoLevel != 0) tftPrint(1, "dBμV", 310, 136, ActiveColor, ActiveColorSmooth, FONT16);
      if (HighCutLevel != 0) tftPrint(1, "Hz", 310, 156, ActiveColor, ActiveColorSmooth, FONT16);
      if (HighCutOffset != 0) tftPrint(1, "dBμV", 310, 176, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(1, "dBμV", 310, 196, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(1, "%", 310, 216, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][20], 8, 36, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][21], 8, 56, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][22], 8, 76, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][23], 8, 96, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][24], 8, 116, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][25], 8, 136, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][26], 8, 156, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][27], 8, 176, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][28], 8, 196, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][29], 8, 216, ActiveColor, ActiveColorSmooth, FONT16);

      if (VolSet > 0) tftPrint(1, "+" + String(VolSet, DEC), 270, 36, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, String(VolSet, DEC), 270, 36, PrimaryColor, PrimaryColorSmooth, FONT16);
      tftPrint(1, String(ConverterSet, DEC), 270, 56, PrimaryColor, PrimaryColorSmooth, FONT16);
      tftPrint(1, String(LowEdgeSet / 10 + ConverterSet, DEC) + "." + String(LowEdgeSet % 10 + ConverterSet, DEC), 270, 76, PrimaryColor, PrimaryColorSmooth, FONT16);
      tftPrint(1, String(HighEdgeSet / 10 + ConverterSet, DEC) + "." + String(HighEdgeSet % 10 + ConverterSet, DEC), 270, 96, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (LevelOffset > 0) tftPrint(1, "+" + String(LevelOffset, DEC), 270, 116, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, String(LevelOffset, DEC), 270, 116, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (StereoLevel != 0) tftPrint(1, String(StereoLevel, DEC), 270, 136, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 310, 136, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (HighCutLevel != 0) tftPrint(1, String(HighCutLevel * 100, DEC), 270, 156, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 310, 156, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (HighCutOffset != 0) tftPrint(1, String(HighCutOffset, DEC), 270, 176, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 310, 176, PrimaryColor, PrimaryColorSmooth, FONT16);
      tftPrint(1, String(LowLevelSet, DEC), 270, 196, PrimaryColor, PrimaryColorSmooth, FONT16);
      tftPrint(1, String(ContrastSet, DEC), 270, 216, PrimaryColor, PrimaryColorSmooth, FONT16);
      break;

    case 2:
      tftPrint(-1, myLanguage[language][39], 8, 36, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][38], 8, 56, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][43], 8, 76, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][44], 8, 96, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][45], 8, 116, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][46], 8, 136, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][49], 8, 156, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][50], 8, 176, ActiveColor, ActiveColorSmooth, FONT16);
      if (wifi) tftPrint(-1, String(myLanguage[language][51]) + " IP: " + String(WiFi.localIP().toString()), 8, 196, ActiveColor, ActiveColorSmooth, FONT16); else tftPrint(-1, myLanguage[language][51], 8, 196, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][52], 8, 216, ActiveColor, ActiveColorSmooth, FONT16);

      tftPrint(1, myLanguage[language][0], 310, 36, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (showrdserrors) tftPrint(1, myLanguage[language][42], 310, 56, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 310, 56, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (softmutefm) tftPrint(1, myLanguage[language][42], 310, 76, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 310, 76, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (softmuteam) tftPrint(1, myLanguage[language][42], 310, 96, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 310, 96, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (edgebeep) tftPrint(1, myLanguage[language][42], 310, 116, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 310, 116, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (region == 0) tftPrint(1, myLanguage[language][47], 310, 136, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (region == 1) tftPrint(1, myLanguage[language][48], 310, 136, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (radio.rds.underscore) tftPrint(1, myLanguage[language][42], 310, 156, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 310, 156, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (USBmode) tftPrint(1, "RDS Spy", 310, 176, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, "XDRGTK", 310, 176, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (wifi) tftPrint(1, myLanguage[language][42], 310, 196, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 310, 196, PrimaryColor, PrimaryColorSmooth, FONT16);
      tftPrint(1, ">", 310, 216, PrimaryColor, PrimaryColorSmooth, FONT16);
      break;

    case 3:
      tftPrint(-1, myLanguage[language][58], 8, 36, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][59], 8, 56, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][60], 8, 76, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][61], 8, 96, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][62], 8, 116, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][63], 8, 136, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][64], 8, 156, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][65], 8, 176, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][67], 8, 196, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][68], 8, 216, ActiveColor, ActiveColorSmooth, FONT16);

      if (amnb != 0) tftPrint(1, "%", 310, 156, ActiveColor, ActiveColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 310, 156, ActiveColor, ActiveColorSmooth, FONT16);
      if (fmnb != 0) tftPrint(1, "%", 310, 176, ActiveColor, ActiveColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 310, 176, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(1, String(WiFi.localIP()[0]) + "." + String(WiFi.localIP()[1]) + "." + String(WiFi.localIP()[2]) + "." + String(subnetclient, DEC), 310, 36, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (showSWMIBand) tftPrint(1, myLanguage[language][42], 310, 56, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 310, 56, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (radio.rds.filter) tftPrint(1, myLanguage[language][42], 310, 76, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 310, 76, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (radio.rds.pierrors) tftPrint(1, myLanguage[language][42], 310, 96, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 310, 96, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (showsquelch) tftPrint(1, myLanguage[language][42], 310, 116, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 310, 116, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (showmodulation) tftPrint(1, myLanguage[language][42], 310, 136, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 310, 136, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (amnb != 0) tftPrint(1, String(amnb, DEC), 270, 156, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 310, 156, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (fmnb != 0) tftPrint(1, String(fmnb, DEC), 270, 176, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 310, 176, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (audiomode) tftPrint(1, "MPX", 310, 196, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, "Stereo", 310, 196, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (touchrotating) tftPrint(1, myLanguage[language][42], 310, 216, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 310, 216, PrimaryColor, PrimaryColorSmooth, FONT16);
      break;

    case 4:
      tftPrint(-1, myLanguage[language][77], 8, 36, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][70], 8, 56, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][74], 8, 76, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][90], 8, 96, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][91], 8, 116, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][97], 8, 136, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][98], 8, 156, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][99], 8, 176, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][100], 8, 196, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][101], 8, 216, ActiveColor, ActiveColorSmooth, FONT16);

      tftPrint(1, "KHz", 310, 96, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(1, "dB", 310, 136, ActiveColor, ActiveColorSmooth, FONT16);
      if (screensaverset) tftPrint(1, myLanguage[language][92], 310, 116, ActiveColor, ActiveColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 310, 116, PrimaryColor, PrimaryColorSmooth, FONT16);
      tftPrint(1, CurrentThemeString, 310, 36, PrimaryColor, PrimaryColorSmooth, FONT16);

      switch (poweroptions) {
        case DEEP_SLEEP: tftPrint(1, myLanguage[language][75], 310, 76, PrimaryColor, PrimaryColorSmooth, FONT16); break;
        case LCD_OFF: tftPrint(1, myLanguage[language][76], 310, 76, PrimaryColor, PrimaryColorSmooth, FONT16); break;
        case LCD_BRIGHTNESS_1_PERCENT: tftPrint(1, myLanguage[language][94], 310, 76, PrimaryColor, PrimaryColorSmooth, FONT16); break;
        case LCD_BRIGHTNESS_A_QUARTER: tftPrint(1, myLanguage[language][95], 310, 76, PrimaryColor, PrimaryColorSmooth, FONT16); break;
        case LCD_BRIGHTNESS_HALF: tftPrint(1, myLanguage[language][96], 310, 76, PrimaryColor, PrimaryColorSmooth, FONT16); break;
      }

      if (fmdefaultstepsize) tftPrint(1, String(FREQ_FM_STEP_100K * 10, DEC), 270, 96, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, String(FREQ_FM_STEP_50K * 10, DEC), 270, 96, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (screensaverset) tftPrint(1, String(screensaverOptions[screensaverset], DEC), 270, 116, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 310, 116, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (AMLevelOffset > 0) tftPrint(1, "+" + String(AMLevelOffset, DEC), 270, 136, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, String(AMLevelOffset, DEC), 270, 136, PrimaryColor, PrimaryColorSmooth, FONT16);
      if (af) tftPrint(1, myLanguage[language][42], 310, 176, PrimaryColor, PrimaryColorSmooth, FONT16); else tftPrint(1, myLanguage[language][30], 310, 176, PrimaryColor, PrimaryColorSmooth, FONT16);
      tftPrint(1, unitString[unit], 310, 156, PrimaryColor, PrimaryColorSmooth, FONT16);
      ShowBandSelectionFM(false, true);
      ShowBandSelectionAM(false, true);
      break;

    case 5:
      tftPrint(-1, myLanguage[language][108], 8, 36, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, myLanguage[language][173], 8, 56, ActiveColor, ActiveColorSmooth, FONT16);

      switch (hardwaremodel) {
        case BASE_ILI9341: tftPrint(1, myLanguage[language][109], 310, 36, PrimaryColor, PrimaryColorSmooth, FONT16); break;
        case PORTABLE_ILI9341: tftPrint(1, myLanguage[language][110 ], 310, 36, PrimaryColor, PrimaryColorSmooth, FONT16); break;
        case PORTABLE_TOUCH_ILI9341: tftPrint(1, myLanguage[language][111], 310, 36, PrimaryColor, PrimaryColorSmooth, FONT16); break;
      }
      switch (batteryoptions) {
        case BATTERY_NONE: tftPrint(1, myLanguage[language][30], 310, 56, PrimaryColor, PrimaryColorSmooth, FONT16); break;
        case BATTERY_VALUE: tftPrint(1, myLanguage[language][174], 310, 56, PrimaryColor, PrimaryColorSmooth, FONT16); break;
        case BATTERY_PERCENT: tftPrint(1, myLanguage[language][175], 310, 56, PrimaryColor, PrimaryColorSmooth, FONT16); break;
      }
      break;

  }
  analogWrite(SMETERPIN, 0);
}

void BuildAdvancedRDS() {
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
    tft.drawLine(64, 30, 64, 0, FrameColor);
    tft.drawLine(210, 30, 210, 240, FrameColor);
    tft.drawLine(108, 30, 108, 0, FrameColor);
    tft.drawLine(137, 30, 137, 0, FrameColor);
    tft.drawLine(175, 30, 175, 0, FrameColor);
    tft.drawLine(268, 30, 268, 0, FrameColor);
    tft.drawLine(0, 140, 210, 140, FrameColor);
    tft.drawLine(0, 166, 210, 166, FrameColor);
    tft.drawLine(0, 193, 210, 193, FrameColor);
    tft.drawLine(210, 191, 320, 191, FrameColor);
    tft.drawLine(0, 217, 210, 217, FrameColor);
    tft.drawRect(0, 0, 320, 240, FrameColor);

    tftPrint(-1, "ERRORS", 3, 34, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(1, unitString[unit], 310, 51, ActiveColor, ActiveColorSmooth, FONT16);
    if (region == 0) tftPrint(-1, "PI", 216, 81, ActiveColor, ActiveColorSmooth, FONT16);
    if (region == 1) tftPrint(-1, "ID", 216, 81, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "PS", 3, 81, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "PTY", 3, 109, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "RT+", 3, 147, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "AF", 3, 199, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "EON", 3, 174, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "RT", 3, 222, ActiveColor, ActiveColorSmooth, FONT16);

    tftPrint(-1, "A:", 66, 34, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "B:", 104, 34, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "C:", 142, 34, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "D:", 180, 34, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "ECC", 214, 193, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "LIC", 214, 208, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "PIN", 214, 223, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(1, "Dynamic PTY", 300, 130, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(1, "Artif. head", 300, 145, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(1, "Compressed", 300, 160, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(1, "Has stereo", 300, 175, ActiveColor, ActiveColorSmooth, FONT16);

    tft.fillCircle(86, 41, 5, SignificantColor);
    tft.fillCircle(124, 41, 5, SignificantColor);
    tft.fillCircle(162, 41, 5, SignificantColor);
    tft.fillCircle(200, 41, 5, SignificantColor);

    tft.fillCircle(310, 137, 5, SignificantColor);
    tft.fillCircle(310, 153, 5, SignificantColor);
    tft.fillCircle(310, 168, 5, SignificantColor);
    tft.fillCircle(310, 183, 5, SignificantColor);

    for (int i = 0; i < 33; i++) tft.fillCircle((6 * i) + 10, 133, 2, GreyoutColor);

    tftPrint(-1, "kHz", 222, 4, ActiveColor, ActiveColorSmooth, FONT28);

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
    tftPrint(-1, "TP", 3, 51, GreyoutColor, BackgroundColor, FONT16);
    tftPrint(-1, "TA", 25, 51, GreyoutColor, BackgroundColor, FONT16);
    tftPrint(-1, "AF", 47, 51, GreyoutColor, BackgroundColor, FONT16);
    tftPrint(-1, "CT", 69, 51, GreyoutColor, BackgroundColor, FONT16);
    tftPrint(-1, "TMC", 89, 51, GreyoutColor, BackgroundColor, FONT16);
    tftPrint(-1, "RT+", 122, 51, GreyoutColor, BackgroundColor, FONT16);
    tftPrint(-1, "EON", 150, 51, GreyoutColor, BackgroundColor, FONT16);
    tftPrint(-1, "M", 183, 51, GreyoutColor, BackgroundColor, FONT16);
    tftPrint(-1, "S", 199, 51, GreyoutColor, BackgroundColor, FONT16);
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
  int bandColor;
  if (theme == 0) {
    tft.fillScreen(BackgroundColor);
    tft.drawRect(0, 0, 320, 240, FrameColor);
    tft.drawLine(0, 30, 320, 30, FrameColor);
    tft.drawLine(0, 100, 320, 100, FrameColor);
    tft.drawLine(64, 30, 64, 0, FrameColor);
    tft.drawLine(210, 100, 210, 217, FrameColor);
    tft.drawLine(268, 30, 268, 0, FrameColor);
    tft.drawLine(0, 160, 210, 160, FrameColor);
    tft.drawLine(0, 180, 320, 180, FrameColor);
    tft.drawLine(0, 217, 320, 217, FrameColor);
    tft.drawLine(108, 30, 108, 0, FrameColor);
    tft.drawLine(137, 30, 137, 0, FrameColor);
    tft.drawLine(175, 30, 175, 0, FrameColor);
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
    if (showsquelch) tftPrint(-1, "SQ:", 212, 145, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(1, "C/N", 270, 163, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "dB", 300, 163, ActiveColor, ActiveColorSmooth, FONT16);
    if (region == 0) tftPrint(-1, "PI:", 216, 193, ActiveColor, ActiveColorSmooth, FONT16);
    if (region == 1) tftPrint(-1, "ID:", 216, 193, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "PS:", 6, 193, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "RT:", 6, 221, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "PTY:", 6, 163, ActiveColor, ActiveColorSmooth, FONT16);

    tftPrint(0, "S", 7, 103, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "1", 24, 115, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "3", 48, 115, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "5", 72, 115, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "7", 96, 115, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "9", 120, 115, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "+10", 134, 115, ActiveColor, ActiveColorSmooth, FONT16);
    tftPrint(-1, "+30", 174, 115, ActiveColor, ActiveColorSmooth, FONT16);

    if (!showmodulation) {
      tftPrint(0, "M", 7, 132, GreyoutColor, BackgroundColor, FONT16);
      tftPrint(-1, "10", 27, 144, GreyoutColor, BackgroundColor, FONT16);
      tftPrint(-1, "30", 57, 144, GreyoutColor, BackgroundColor, FONT16);
      tftPrint(-1, "50", 87, 144, GreyoutColor, BackgroundColor, FONT16);
      tftPrint(-1, "70", 117, 144, GreyoutColor, BackgroundColor, FONT16);
      tftPrint(-1, "100", 164, 144, GreyoutColor, BackgroundColor, FONT16);
    } else {
      tftPrint(0, "M", 7, 132, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, "10", 27, 144, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, "30", 57, 144, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, "50", 87, 144, ActiveColor, ActiveColorSmooth, FONT16);
      tftPrint(-1, "70", 117, 144, ActiveColor, BackgroundColor, FONT16);
      tftPrint(-1, "100", 164, 144, ActiveColor, ActiveColorSmooth, FONT16);
    }

    tftPrint(-1, "kHz", 222, 4, ActiveColor, ActiveColorSmooth, FONT28);
    tftPrint(-1, unitString[unit], 282, 145, ActiveColor, ActiveColorSmooth, FONT16);

    if (band < BAND_GAP) tftPrint(-1, "MHz", 258, 76, ActiveColor, ActiveColorSmooth, FONT28); else tftPrint(-1, "kHz", 258, 76, ActiveColor, ActiveColorSmooth, FONT28);

    tft.drawRoundRect(248, 56, 32, 20, 5, GreyoutColor);
    if (band > BAND_GAP) tftPrint(0, "iMS", 265, 59, GreyoutColor, BackgroundColor, FONT16);
    tft.drawRoundRect(286, 56, 32, 20, 5, GreyoutColor);
    if (band > BAND_GAP) tftPrint(0, "EQ", 303, 59, GreyoutColor, BackgroundColor, FONT16);

    tft.drawCircle(81, 15, 10, GreyoutColor);
    tft.drawCircle(81, 15, 9, GreyoutColor);
    tft.drawCircle(91, 15, 10, GreyoutColor);
    tft.drawCircle(91, 15, 9, GreyoutColor);
    tft.drawBitmap(139, 5, RDSLogo, 35, 22, GreyoutColor);
    if (StereoToggle == false) {
      tft.drawCircle(86, 15, 10, SecondaryColor);
      tft.drawCircle(86, 15, 9, SecondaryColor);
    }

    if (bandforbidden) bandColor = GreyoutColor; else bandColor = PrimaryColor;
    switch (band) {
      case BAND_LW: tftPrint(-1, myLanguage[language][102], 70, 32, bandColor, PrimaryColorSmooth, FONT16); break;
      case BAND_MW: tftPrint(-1, myLanguage[language][103], 70, 32, bandColor, PrimaryColorSmooth, FONT16); break;
      case BAND_SW: tftPrint(-1, myLanguage[language][104], 70, 32, bandColor, PrimaryColorSmooth, FONT16); break;
      case BAND_FM: tftPrint(-1, myLanguage[language][105], 70, 32, bandColor, PrimaryColorSmooth, FONT16); break;
      case BAND_OIRT: tftPrint(-1, myLanguage[language][106], 70, 32, bandColor, PrimaryColorSmooth, FONT16); break;
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
  if (band < BAND_GAP) tftPrint(-1, "MHz", 258, 76, ActiveColor, ActiveColorSmooth, FONT28); else tftPrint(-1, "kHz", 258, 76, ActiveColor, ActiveColorSmooth, FONT28);
}

void MenuUp() {
  if (menuopen == false) {
    tft.drawRoundRect(3, menuoption + 3, 315, 21, 5, BackgroundColor);
    if (hardwaremodel == BASE_ILI9341) {
      menuoption += 20;
      if (menuoption > 210) {
        menupage++;
        if (menupage > menupagestotal) menupage = 1;
        menuoption = 30;
        BuildMenu();
      }
    } else {
      menuoption -= 20;
      if (menuoption < 30) {
        menupage--;
        if (menupage == 0) menupage = menupagestotal;
        menuoption = 210;
        BuildMenu();
      }
    }
    tft.drawRoundRect(3, menuoption + 3, 315, 21, 5, ActiveColor);
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
            tftPrint(1, String(LowEdgeSet / 10 + ConverterSet, DEC) + "." + String(LowEdgeSet % 10 + ConverterSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
            break;

          case 90:
            tftPrint(1, String(HighEdgeSet / 10 + ConverterSet, DEC) + "." + String(HighEdgeSet % 10 + ConverterSet, DEC), 155, 118, BackgroundColor, BackgroundColor, FONT28);
            HighEdgeSet ++;
            if (HighEdgeSet > 1080) HighEdgeSet = 660;
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
            if (touchrotating) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, FONT28);
            if (touchrotating) touchrotating = 0; else touchrotating = 1;
            if (touchrotating) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
            break;
        }
        break;

      case 4:
        switch (menuoption) {
          case 30:
            CurrentTheme ++;
            if (CurrentTheme > 10) CurrentTheme = 0;
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

          case 190:
            ShowBandSelectionFM(true, REVERSE);
            bandFM++;
            if (bandFM > FM_BAND_CNT - 1) bandFM = FM_BAND_ALL;
            ShowBandSelectionFM(true, true);
            break;

          case 210:
            ShowBandSelectionAM(true, REVERSE);
            bandAM++;
            if (bandAM > AM_BAND_CNT - 1) bandAM = AM_BAND_ALL;
            ShowBandSelectionAM(true, true);
            break;

        }
        break;

      case 5:
        switch (menuoption) {
          case 30:
            switch (hardwaremodelold) {
              case BASE_ILI9341: tftPrint(0, myLanguage[language][109], 155, 118, BackgroundColor, BackgroundColor, FONT28); break;
              case PORTABLE_ILI9341: tftPrint(0, myLanguage[language][110], 155, 118, BackgroundColor, BackgroundColor, FONT28); break;
              case PORTABLE_TOUCH_ILI9341: tftPrint(0, myLanguage[language][111], 155, 118, BackgroundColor, BackgroundColor, FONT28); break;
            }

            hardwaremodel++;
            if (hardwaremodel > RADIO_HARDWARE_CNT - 1) hardwaremodel = 0;

            switch (hardwaremodel) {
              case BASE_ILI9341: tftPrint(0, myLanguage[language][109], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); break;
              case PORTABLE_ILI9341: tftPrint(0, myLanguage[language][110], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); break;
              case PORTABLE_TOUCH_ILI9341: tftPrint(0, myLanguage[language][111], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); break;
            }
            hardwaremodelold = hardwaremodel;
            break;

          case 50:
            switch (batteryoptionsold) {
              case BATTERY_NONE: tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, FONT28); break;
              case BATTERY_VALUE: tftPrint(0, myLanguage[language][174], 155, 118, BackgroundColor, BackgroundColor, FONT28); break;
              case BATTERY_PERCENT: tftPrint(0, myLanguage[language][175], 155, 118, BackgroundColor, BackgroundColor, FONT28); break;
            }

            batteryoptions++;
            if (batteryoptions > RADIO_BATTERY_CNT - 1) batteryoptions = 0;

            switch (batteryoptions) {
              case BATTERY_NONE: tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); break;
              case BATTERY_VALUE: tftPrint(0, myLanguage[language][174], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); break;
              case BATTERY_PERCENT: tftPrint(0, myLanguage[language][175], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); break;
            }
            batteryoptionsold = batteryoptions;
            break;
        }
        break;
    }
  }
}

void MenuDown() {
  if (menuopen == false) {
    tft.drawRoundRect(3, menuoption + 3, 315, 21, 5, BackgroundColor);
    if (hardwaremodel == BASE_ILI9341) {
      menuoption -= 20;
      if (menuoption < 30) {
        menupage--;
        if (menupage == 0) menupage = menupagestotal;
        menuoption = 210;
        BuildMenu();
      }
    } else {
      menuoption += 20;
      if (menuoption > 210) {
        menupage++;
        if (menupage > menupagestotal) menupage = 1;
        menuoption = 30;
        BuildMenu();
      }
    }
    tft.drawRoundRect(3, menuoption + 3, 315, 21, 5, ActiveColor);
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
            tftPrint(1, String(LowEdgeSet / 10 + ConverterSet, DEC) + "." + String(LowEdgeSet % 10 + ConverterSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
            break;

          case 90:
            tftPrint(1, String(HighEdgeSet / 10 + ConverterSet, DEC) + "." + String(HighEdgeSet % 10 + ConverterSet, DEC), 155, 118, BackgroundColor, BackgroundColor, FONT28);
            HighEdgeSet -= 10;
            if (HighEdgeSet < 660) HighEdgeSet = 1080;
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
            if (touchrotating) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, FONT28);
            if (touchrotating) touchrotating = 0; else touchrotating = 1;
            if (touchrotating) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
            break;
        }
        break;
      case 4:
        switch (menuoption) {
          case 30:
            CurrentTheme --;
            if (CurrentTheme > 10) CurrentTheme = 10;
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

          case 190:
            ShowBandSelectionFM(true, REVERSE);
            bandFM--;
            if (bandFM > FM_BAND_CNT) bandFM = FM_BAND_FM;
            ShowBandSelectionFM(true, true);
            break;

          case 210:
            ShowBandSelectionAM(true, REVERSE);
            bandAM--;
            if (bandAM > AM_BAND_CNT) bandAM = AM_BAND_SW;
            ShowBandSelectionAM(true, true);
            break;

        }
        break;

      case 5:
        switch (menuoption) {
          case 30:
            switch (hardwaremodelold) {
              case BASE_ILI9341: tftPrint(0, myLanguage[language][109], 155, 118, BackgroundColor, BackgroundColor, FONT28); break;
              case PORTABLE_ILI9341: tftPrint(0, myLanguage[language][110], 155, 118, BackgroundColor, BackgroundColor, FONT28); break;
              case PORTABLE_TOUCH_ILI9341: tftPrint(0, myLanguage[language][111], 155, 118, BackgroundColor, BackgroundColor, FONT28); break;
            }

            hardwaremodel--;
            if (hardwaremodel > RADIO_HARDWARE_CNT - 1) hardwaremodel = RADIO_HARDWARE_CNT - 1;

            switch (hardwaremodel) {
              case BASE_ILI9341: tftPrint(0, myLanguage[language][109], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); break;
              case PORTABLE_ILI9341: tftPrint(0, myLanguage[language][110], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); break;
              case PORTABLE_TOUCH_ILI9341: tftPrint(0, myLanguage[language][111], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); break;
            }
            hardwaremodelold = hardwaremodel;
            break;

          case 50:
            switch (batteryoptionsold) {
              case BATTERY_NONE: tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, FONT28); break;
              case BATTERY_VALUE: tftPrint(0, myLanguage[language][174], 155, 118, BackgroundColor, BackgroundColor, FONT28); break;
              case BATTERY_PERCENT: tftPrint(0, myLanguage[language][175], 155, 118, BackgroundColor, BackgroundColor, FONT28); break;
            }

            batteryoptions--;
            if (batteryoptions > RADIO_BATTERY_CNT - 1) batteryoptions = RADIO_BATTERY_CNT - 1;

            switch (batteryoptions) {
              case BATTERY_NONE: tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); break;
              case BATTERY_VALUE: tftPrint(0, myLanguage[language][174], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); break;
              case BATTERY_PERCENT: tftPrint(0, myLanguage[language][175], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); break;
            }
            batteryoptionsold = batteryoptions;
            break;
        }
        break;
    }
  }
}

void DoMenu() {
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
            tftPrint(0, myLanguage[language][107], 155, 78, ActiveColor, ActiveColorSmooth, FONT28);
            if (touchrotating) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28);
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
          case 190:
            tftPrint(0, myLanguage[language][100], 155, 78, ActiveColor, ActiveColorSmooth, FONT28);
            ShowBandSelectionFM(true, true);
            break;
          case 210:
            tftPrint(0, myLanguage[language][101], 155, 78, ActiveColor, ActiveColorSmooth, FONT28);
            ShowBandSelectionAM(true, true);
            break;
        }
        break;

      case 5:
        switch (menuoption) {
          case 30:
            tftPrint(0, myLanguage[language][108], 155, 78, ActiveColor, ActiveColorSmooth, FONT28);
            switch (hardwaremodel) {
              case BASE_ILI9341: tftPrint(0, myLanguage[language][109], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); break;
              case PORTABLE_ILI9341: tftPrint(0, myLanguage[language][110], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); break;
              case PORTABLE_TOUCH_ILI9341: tftPrint(0, myLanguage[language][111], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); break;
            }
            hardwaremodelold = hardwaremodel;
            break;

          case 50:
            tftPrint(0, myLanguage[language][173], 155, 78, ActiveColor, ActiveColorSmooth, FONT28);
            switch (batteryoptions) {
              case BATTERY_NONE: tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); break;
              case BATTERY_VALUE: tftPrint(0, myLanguage[language][174], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); break;
              case BATTERY_PERCENT: tftPrint(0, myLanguage[language][175], 155, 118, PrimaryColor, PrimaryColorSmooth, FONT28); break;
            }
            batteryoptionsold = batteryoptions;
            break;
        }
        break;

    }
  } else {
    if (menupage == 2 && menuoption == 190 && wifi == true) {
      tryWiFi();
      delay(2000);
    }
    if (menupage == 2 && menuoption == 30) {
      doTheme();
    }
    menuopen = false;
    BuildMenu();
  }
}
