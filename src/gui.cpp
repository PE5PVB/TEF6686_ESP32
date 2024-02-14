#include "gui.h"
#include "language.h"
#include "constants.h"
#include <WiFi.h>
#include <Wire.h>
#include <EEPROM.h>
#include <cstring>


byte menuitem;
byte items[8] = {8, static_cast<byte>(dynamicspi ? 5 : 4), 7, 10, 9, 10, 10, 6};

void doTheme() {  // Use this to put your own colors in: http://www.barth-dev.de/online/rgb565-color-picker/
  switch (CurrentTheme) {
    case 0:  // Default PE5PVB theme
      PrimaryColor = Yellow;
      PrimaryColorSmooth = YellowSmooth;
      SecondaryColor = Skyblue;
      SecondaryColorSmooth = SkyblueSmooth;
      FrameColor = Blue;
      GreyoutColor = Darkgrey;
      BackgroundColor = Black;
      ActiveColor = White;
      ActiveColorSmooth = WhiteSmooth;
      FreqColor = Yellow;
      FreqColorSmooth = YellowSmooth;
      SignificantColor = Red;
      SignificantColorSmooth = RedSmooth;
      InsignificantColor = Green;
      InsignificantColorSmooth = GreenSmooth;
      StereoColor = Red;
      StereoColorSmooth = RedSmooth;
      RDSColor = Yellow;
      RDSColorSmooth = YellowSmooth;
      RDSDropoutColor = Teal;
      RDSDropoutColorSmooth = TealSmooth;
      BarSignificantColor = Red;
      BarInsignificantColor = Green;
      ModBarSignificantColor = Red;
      ModBarInsignificantColor = Green;
      BWAutoColor = Teal;
      BWAutoColorSmooth = TealSmooth;
      BatteryValueColor = Teal;
      BatteryValueColorSmooth = Black;
      break;
    case 1:  // Cyan theme
      PrimaryColor = Cyan;
      PrimaryColorSmooth = CyanSmooth;
      SecondaryColor = Teal;
      SecondaryColorSmooth = TealSmooth;
      FrameColor = CyanFrame;
      GreyoutColor = CyanGrey;
      BackgroundColor = Black;
      FreqColor = Cyan;
      FreqColorSmooth = CyanSmooth;
      ActiveColor = White;
      ActiveColorSmooth = WhiteSmooth;
      SignificantColor = Red;
      SignificantColorSmooth = RedSmooth;
      InsignificantColor = Green;
      InsignificantColorSmooth = GreenSmooth;
      StereoColor = Cyan;
      StereoColorSmooth = CyanSmooth;
      RDSColor = Cyan;
      RDSColorSmooth = CyanSmooth;
      RDSDropoutColor = CyanDark;
      RDSDropoutColorSmooth = CyanDarkSmooth;
      BarSignificantColor = Red;
      BarInsignificantColor = Cyan;
      ModBarSignificantColor = Red;
      ModBarInsignificantColor = Cyan;
      BWAutoColor = Teal;
      BWAutoColorSmooth = TealSmooth;
      BatteryValueColor = Teal;
      BatteryValueColorSmooth = TealSmooth;
      break;
    case 2:  // Crimson theme
      PrimaryColor = Crimson;
      PrimaryColorSmooth = CrimsonSmooth;
      SecondaryColor = Coral;
      SecondaryColorSmooth = CoralSmooth;
      FrameColor = CrimsonSmooth;
      GreyoutColor = PaleGrey;
      BackgroundColor = Black;
      FreqColor = Crimson;
      FreqColorSmooth = CrimsonSmooth;
      ActiveColor = White;
      ActiveColorSmooth = WhiteSmooth;
      SignificantColor = Green;
      SignificantColorSmooth = RedSmooth;
      InsignificantColor = Green;
      InsignificantColorSmooth = GreenSmooth;
      StereoColor = Crimson;
      StereoColorSmooth = Black;
      RDSColor = Crimson;
      RDSColorSmooth = Black;
      RDSDropoutColor = CrimsonDark;
      RDSDropoutColorSmooth = CrimsonDarkSmooth;
      BarSignificantColor = Yellow;
      BarInsignificantColor = Crimson;
      ModBarSignificantColor = Yellow;
      ModBarInsignificantColor = Crimson;
      BWAutoColor = Coral;
      BWAutoColorSmooth = CoralSmooth;
      BatteryValueColor = Watermelon;
      BatteryValueColorSmooth = WatermelonSmooth;
      break;
    case 3:  // Monochrome theme
      PrimaryColor = White;
      PrimaryColorSmooth = Black;
      SecondaryColor = PureGrey;
      SecondaryColorSmooth = Black;
      FrameColor = GreenGrey;
      GreyoutColor = PaleGrey;
      BackgroundColor = Black;
      FreqColor = White;
      FreqColorSmooth = Black;
      ActiveColor = White;
      ActiveColorSmooth = Black;
      SignificantColor = Red;
      SignificantColorSmooth = RedSmooth;
      InsignificantColor = Green;
      InsignificantColorSmooth = GreenSmooth;
      StereoColor = White;
      StereoColorSmooth = Black;
      RDSColor = White;
      RDSColorSmooth = Black;
      RDSDropoutColor = PureGrey;
      RDSDropoutColorSmooth = Black;
      BarSignificantColor = Red;
      BarInsignificantColor = Green;
      ModBarSignificantColor = Red;
      ModBarInsignificantColor = Green;
      BWAutoColor = PureGrey;
      BWAutoColorSmooth = Black;
      BatteryValueColor = White;
      BatteryValueColorSmooth = Black;
      break;
    case 4:  // Volcano theme
      PrimaryColor = Orange;
      PrimaryColorSmooth = OrangeSmooth;
      SecondaryColor = Tangerine;
      SecondaryColorSmooth = TangerineSmooth;
      FrameColor = GreenGrey;
      GreyoutColor = Maroon;
      BackgroundColor = Prussian;
      FreqColor = Orange;
      FreqColorSmooth = OrangeSmooth;
      ActiveColor = White;
      ActiveColorSmooth = WhiteSmooth;
      SignificantColor = Red;
      SignificantColorSmooth = RedSmooth;
      InsignificantColor = Green;
      InsignificantColorSmooth = GreenSmooth;
      StereoColor = Orange;
      StereoColorSmooth = CyanSmooth;
      RDSColor = Orange;
      RDSColorSmooth = OrangeSmooth;
      RDSDropoutColor = Dallas;
      RDSDropoutColorSmooth = DallasSmooth;
      BarSignificantColor = Red;
      BarInsignificantColor = Orange;
      ModBarSignificantColor = Red;
      ModBarInsignificantColor = Orange;
      BWAutoColor = Tangerine;
      BWAutoColorSmooth = TangerineSmooth;
      BatteryValueColor = Tangerine;
      BatteryValueColorSmooth = TangerineSmooth;
      break;
    case 5:  // Dendro theme
      PrimaryColor = Green;
      PrimaryColorSmooth = GreenDark;
      SecondaryColor = Cabbage;
      SecondaryColorSmooth = CabbageSmooth;
      FrameColor = GreenDark;
      GreyoutColor = PaleGrey;
      BackgroundColor = Black;
      FreqColor = Green;
      FreqColorSmooth = GreenDark;
      ActiveColor = White;
      ActiveColorSmooth = WhiteSmooth;
      SignificantColor = Red;
      SignificantColorSmooth = RedSmooth;
      InsignificantColor = Green;
      InsignificantColorSmooth = GreenSmooth;
      StereoColor = Green;
      StereoColorSmooth = GreenDark;
      RDSColor = Green;
      RDSColorSmooth = GreenDark;
      RDSDropoutColor = Laurel;
      RDSDropoutColorSmooth = LaurelSmooth;
      BarSignificantColor = Red;
      BarInsignificantColor = Green;
      ModBarSignificantColor = Red;
      ModBarInsignificantColor = Green;
      BWAutoColor = Cabbage;
      BWAutoColorSmooth = CabbageSmooth;
      BatteryValueColor = Cabbage;
      BatteryValueColorSmooth = CabbageSmooth;
      break;
    case 6:  // Sakura theme
      PrimaryColor = Sakura;
      PrimaryColorSmooth = SakuraSmooth;
      SecondaryColor = Cherry;
      SecondaryColorSmooth = CherrySmooth;
      FrameColor = Tyrian;
      GreyoutColor = Blackberry;
      BackgroundColor = Black;
      FreqColor = Sakura;
      FreqColorSmooth = SakuraSmooth;
      ActiveColor = White;
      ActiveColorSmooth = WhiteSmooth;
      SignificantColor = Red;
      SignificantColorSmooth = RedSmooth;
      InsignificantColor = Green;
      InsignificantColorSmooth = GreenSmooth;
      StereoColor = Sakura;
      StereoColorSmooth = SakuraSmooth;
      RDSColor = Sakura;
      RDSColorSmooth = SakuraSmooth;
      RDSDropoutColor = SakuraGrey;
      RDSDropoutColorSmooth = SakuraGreySmooth;
      BarSignificantColor = Black;
      BarSignificantColor = Red;
      BarInsignificantColor = Sakura;
      ModBarSignificantColor = Red;
      ModBarInsignificantColor = Sakura;
      BWAutoColor = Cherry;
      BWAutoColorSmooth = CherrySmooth;
      BatteryValueColor = Cherry;
      BatteryValueColorSmooth = CherrySmooth;
      break;
    case 7:  // Whiteout theme
      PrimaryColor = Black;
      PrimaryColorSmooth = White;
      SecondaryColor = Grey;
      SecondaryColorSmooth = White;
      FrameColor = Darkgrey;
      GreyoutColor = PureGrey;
      BackgroundColor = Honeydew;
      FreqColor = Black;
      FreqColorSmooth = White;
      ActiveColor = Black;
      ActiveColorSmooth = Honeydew;
      SignificantColor = Red;
      SignificantColorSmooth = Honeydew;
      InsignificantColor = Green;
      InsignificantColorSmooth = GreenSmooth;
      StereoColor = Black;
      StereoColorSmooth = Honeydew;
      RDSColor = Black;
      RDSColorSmooth = Honeydew;
      RDSDropoutColor = PureGrey;
      RDSDropoutColorSmooth = White;
      BarSignificantColor = Black;
      BarInsignificantColor = Green;
      ModBarSignificantColor = Black;
      ModBarInsignificantColor = Green;
      BWAutoColor = PureGrey;
      BWAutoColorSmooth = White;
      BatteryValueColor = Black;
      BatteryValueColorSmooth = White;
      break;
    case 8:  // Tangerine theme
      PrimaryColor = Tangerine;
      PrimaryColorSmooth = TangerineSmooth;
      SecondaryColor = Yolk;
      SecondaryColorSmooth = YolkSmooth;
      FrameColor = Chocolate;
      GreyoutColor = Spice;
      BackgroundColor = Black;
      FreqColor = Tangerine;
      FreqColorSmooth = IndigoSmooth;
      ActiveColor = White;
      ActiveColorSmooth = WhiteSmooth;
      SignificantColor = Red;
      SignificantColorSmooth = RedSmooth;
      InsignificantColor = Green;
      InsignificantColorSmooth = GreenSmooth;
      StereoColor = Tangerine;
      StereoColorSmooth = IndigoSmooth;
      RDSColor = Tangerine;
      RDSColorSmooth = IndigoSmooth;
      RDSDropoutColor = Copper;
      RDSDropoutColorSmooth = CopperSmooth;
      BarSignificantColor = Red;
      BarInsignificantColor = Green;
      ModBarSignificantColor = Red;
      ModBarInsignificantColor = Green;
      BWAutoColor = Yolk;
      BWAutoColorSmooth = YolkSmooth;
      BatteryValueColor = Yolk;
      BatteryValueColorSmooth = YolkSmooth;
      break;
    case 9:  // Ocean theme
      PrimaryColor = Ocean;
      PrimaryColorSmooth = OceanSmooth;
      SecondaryColor = Deepsky;
      SecondaryColorSmooth = DeepskySmooth;
      FrameColor = Navy;
      GreyoutColor = Cornblue;
      BackgroundColor = Black;
      FreqColor = Ocean;
      FreqColorSmooth = OceanSmooth;
      ActiveColor = White;
      ActiveColorSmooth = WhiteSmooth;
      SignificantColor = Red;
      SignificantColorSmooth = RedSmooth;
      InsignificantColor = Cyan;
      InsignificantColorSmooth = CyanSmooth;
      StereoColor = Ocean;
      StereoColorSmooth = OceanSmooth;
      RDSColor = Ocean;
      RDSColorSmooth = OceanSmooth;
      RDSDropoutColor = Cove;
      RDSDropoutColorSmooth = CoveSmooth;
      BarSignificantColor = Red;
      BarInsignificantColor = Ocean;
      ModBarSignificantColor = Red;
      ModBarInsignificantColor = Ocean;
      BWAutoColor = Deepsky;
      BWAutoColorSmooth = DeepskySmooth;
      BatteryValueColor = Deepsky;
      BatteryValueColorSmooth = DeepskySmooth;
      break;
    case 10:  // Indigo theme
      PrimaryColor = Indigo;
      PrimaryColorSmooth = IndigoSmooth;
      SecondaryColor = Violet;
      SecondaryColorSmooth = VioletSmooth;
      FrameColor = Electric;
      GreyoutColor = Meteorite;
      BackgroundColor = Black;
      FreqColor = Indigo;
      FreqColorSmooth = IndigoSmooth;
      ActiveColor = White;
      ActiveColorSmooth = WhiteSmooth;
      SignificantColor = Red;
      SignificantColorSmooth = RedSmooth;
      InsignificantColor = Green;
      InsignificantColorSmooth = GreenSmooth;
      StereoColor = Indigo;
      StereoColorSmooth = IndigoSmooth;
      RDSColor = Indigo;
      RDSColorSmooth = IndigoSmooth;
      RDSDropoutColor = Logan;
      RDSDropoutColorSmooth = LoganSmooth;
      BarSignificantColor = Red;
      BarInsignificantColor = Indigo;
      ModBarSignificantColor = Red;
      ModBarInsignificantColor = Indigo;
      BWAutoColor = Violet;
      BWAutoColorSmooth = VioletSmooth;
      BatteryValueColor = Violet;
      BatteryValueColorSmooth = VioletSmooth;
      break;

    case 11:  // Maroon
      PrimaryColor = Cherry;
      PrimaryColorSmooth = CherrySmooth;
      SecondaryColor = Crimson;
      SecondaryColorSmooth = CrimsonSmooth;
      FrameColor = Electric;
      GreyoutColor = CoralSmooth;
      BackgroundColor = MaroonSmooth;
      ActiveColor = White;
      ActiveColorSmooth = WhiteSmooth;
      FreqColor = Cherry;
      FreqColorSmooth = CherrySmooth;
      SignificantColor = Red;
      SignificantColorSmooth = RedSmooth;
      InsignificantColor = Violet;
      InsignificantColorSmooth = VioletSmooth;
      StereoColor = Cherry;
      StereoColorSmooth = CherrySmooth;
      RDSColor = Coral;
      RDSColorSmooth = CoralSmooth;
      RDSDropoutColor = Logan;
      RDSDropoutColorSmooth = LoganSmooth;
      BarSignificantColor = Yolk;
      BarInsignificantColor = Cherry;
      ModBarSignificantColor = Yolk;
      ModBarInsignificantColor = Cherry;
      BWAutoColor = Violet;
      BWAutoColorSmooth = VioletSmooth;
      BatteryValueColor = Purple;
      BatteryValueColorSmooth = PurpleSmooth;
      break;

    case 12:  // GoldBrite
      PrimaryColor = Yellow;
      PrimaryColorSmooth = YellowSmooth;
      SecondaryColor = Skyblue;
      SecondaryColorSmooth = SkyblueSmooth;
      FrameColor = Blue;
      GreyoutColor = Darkgrey;
      BackgroundColor = Black;
      ActiveColor = White;
      ActiveColorSmooth = WhiteSmooth;
      FreqColor = White;
      FreqColorSmooth = WhiteSmooth;
      SignificantColor = Red;
      SignificantColorSmooth = RedSmooth;
      InsignificantColor = Ocean;
      InsignificantColorSmooth = OceanSmooth;
      StereoColor = Red;
      StereoColorSmooth = RedSmooth;
      RDSColor = Yellow;
      RDSColorSmooth = YellowSmooth;
      RDSDropoutColor = Teal;
      RDSDropoutColorSmooth = TealSmooth;
      BarSignificantColor = Red;
      BarInsignificantColor = Ocean;
      ModBarSignificantColor = Red;
      ModBarInsignificantColor = Green;
      BWAutoColor = Teal;
      BWAutoColorSmooth = TealSmooth;
      BatteryValueColor = Teal;
      BatteryValueColorSmooth = Black;
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
  if (CurrentSkin == 0) {
    tft.fillScreen(BackgroundColor);
    tft.drawRect(0, 0, 320, 240, FrameColor);
    tft.drawLine(0, 30, 320, 30, FrameColor);
    tft.drawLine(0, 199, 320, 199, FrameColor);
    tft.drawLine(0, 218, 320, 218, FrameColor);
    tft.drawLine(53, 30, 53, 0, FrameColor);
    tft.drawLine(89, 30, 89, 0, FrameColor);
    tft.drawLine(120, 30, 120, 0, FrameColor);
    tft.drawLine(158, 30, 158, 0, FrameColor);
    tft.drawLine(248, 30, 248, 0, FrameColor);
    tftPrint(-1, "kHz", 203, 4, ActiveColor, ActiveColorSmooth, 28);
    tftPrint(0, myLanguage[language][93], 160, 222, ActiveColor, ActiveColorSmooth, 16);
    if (afpagenr == 1) {
      if (!radio.rds.hasAF) tftPrint(-1, myLanguage[language][87], 6, 48, PrimaryColor, PrimaryColorSmooth, 16);
    } else if (afpagenr == 2) {
      if (!radio.rds.hasEON) tftPrint(-1, myLanguage[language][88], 6, 48, PrimaryColor, PrimaryColorSmooth, 16);
    }
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
    afmethodBold = false;
    PIold = " ";
    PSold = " ";
    xPos = 0;
    for (byte i = 0; i < 20; i++) {
      mappedfreqold[i] = 0;
      mappedfreqold2[i] = 0;
      mappedfreqold3[i] = 0;
      eonpicodeold[i][0] = '\0';
      eonpsold[i] = "";
      eonptyold[i] = 254;
    }
    for (byte i = 0; i < 20; i++) std::memset(eonpicodeold[i], '\0', sizeof(eonpicodeold[i]));

    if (afpagenr == 1 && radio.rds.hasDABAF && radio.rds.dabaffreq != 0) tftPrint(1, "DAB: " + String(radio.rds.dabafchannel) + " (" + String(radio.rds.dabafeid) + ")", 166, 32, SecondaryColor, SecondaryColorSmooth, 16);
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
      tftPrint(0, String(myLanguage[language][84]) + " " + String(VERSION), 160, ITEM10 + 6, SecondaryColor, SecondaryColorSmooth, 16);
      break;

    case MAINSETTINGS:
      tftPrint(-1, myLanguage[language][108], 8, ITEM1 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][107], 8, ITEM2 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][75], 8, ITEM3 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][62], 8, ITEM4 + 6, ActiveColor, ActiveColorSmooth, 16);

      switch (hardwaremodel) {
        case BASE_ILI9341: tftPrint(1, myLanguage[language][109], 310, ITEM1 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
        case PORTABLE_ILI9341: tftPrint(1, myLanguage[language][110 ], 310, ITEM1 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
        case PORTABLE_TOUCH_ILI9341: tftPrint(1, myLanguage[language][111], 310, ITEM1 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
      }

      if (touchrotating) tftPrint(1, myLanguage[language][42], 310, ITEM2 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM2 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      if (tot != 0) tftPrint(1, String(tot), 270, ITEM3 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      if (tot != 0) tftPrint(1, myLanguage[language][80], 310, ITEM3 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM3 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      if (usesquelch) tftPrint(1, myLanguage[language][42], 310, ITEM4 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM4 + 6, PrimaryColor, PrimaryColorSmooth, 16);

      if (dynamicspi) {
        tftPrint(1, "MHz", 310, ITEM5 + 6, ActiveColor, ActiveColorSmooth, 16);
        tftPrint(-1, myLanguage[language][81], 8, ITEM5 + 6, ActiveColor, ActiveColorSmooth, 16);
        if (spispeed == SPI_SPEED_DEFAULT) tftPrint(1,  String(myLanguage[language][204]) + " " + String(SPI_FREQUENCY / 1000000, DEC), 270, ITEM5 + 6, PrimaryColor, PrimaryColorSmooth, 16);
        else tftPrint(1, String(spispeed * 10, DEC), 270, ITEM5 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      }
      break;

    case AUDIOSETTINGS:
      tftPrint(-1, myLanguage[language][20], 8, ITEM1 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][45], 8, ITEM2 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][67], 8, ITEM3 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][25], 8, ITEM4 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][26], 8, ITEM5 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][27], 8, ITEM6 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][199], 8, ITEM7 + 6, ActiveColor, ActiveColorSmooth, 16);

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
      if (fmdeemphasis != DEEMPHASIS_NONE) tftPrint(1, String((fmdeemphasis == DEEMPHASIS_50 ? FM_DEEMPHASIS_50 : FM_DEEMPHASIS_75), DEC), 270, ITEM7 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM7 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      if (fmdeemphasis != DEEMPHASIS_NONE) tftPrint(1, "μs", 310, ITEM7 + 6, ActiveColor, ActiveColorSmooth, 16);
      break;

    case DISPLAYSETTINGS:
      tftPrint(-1, myLanguage[language][39], 8, ITEM1 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][29], 8, ITEM2 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][63], 8, ITEM3 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][91], 8, ITEM4 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][74], 8, ITEM5 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][173], 8, ITEM6 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][98], 8, ITEM7 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][78], 8, ITEM8 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][77], 8, ITEM9 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][85], 8, ITEM10 + 6, ActiveColor, ActiveColorSmooth, 16);

      tftPrint(1, myLanguage[language][0], 310, ITEM1 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      tftPrint(1, "%", 310, ITEM2 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(1, String(ContrastSet, DEC), 270, ITEM2 + 6, PrimaryColor, PrimaryColorSmooth, 16);

      if (showmodulation) tftPrint(1, myLanguage[language][42], 310, ITEM3 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM3 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      if (screensaverset) tftPrint(1, myLanguage[language][92], 310, ITEM4 + 6, ActiveColor, ActiveColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM4 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      if (screensaverset) tftPrint(1, String(screensaverOptions[screensaverset], DEC), 270, ITEM4 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM4 + 6, PrimaryColor, PrimaryColorSmooth, 16);

      switch (poweroptions) {
        case LCD_OFF: tftPrint(1, myLanguage[language][76], 310, ITEM5 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
        case LCD_BRIGHTNESS_1_PERCENT: tftPrint(1, myLanguage[language][94], 310, ITEM5 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
        case LCD_BRIGHTNESS_A_QUARTER: tftPrint(1, myLanguage[language][95], 310, ITEM5 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
        case LCD_BRIGHTNESS_HALF: tftPrint(1, myLanguage[language][96], 310, ITEM5 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
      }

      switch (batteryoptions) {
        case BATTERY_NONE: tftPrint(1, myLanguage[language][30], 310, ITEM6 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
        case BATTERY_VALUE: tftPrint(1, myLanguage[language][174], 310, ITEM6 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
        case BATTERY_PERCENT: tftPrint(1, myLanguage[language][175], 310, ITEM6 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
      }

      tftPrint(1, unitString[unit], 310, ITEM7 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      tftPrint(1, Skin[CurrentSkin], 310, ITEM8 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      tftPrint(1, Theme[CurrentTheme], 310, ITEM9 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      tftPrint(1, FreqFont[freqfont], 310, ITEM10 + 6, PrimaryColor, PrimaryColorSmooth, 16);
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
      if (radio.underscore) tftPrint(1, myLanguage[language][42], 310, ITEM3 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM3 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      if (radio.rds.filter) tftPrint(1, myLanguage[language][42], 310, ITEM4 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM4 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      if (radio.rds.pierrors) tftPrint(1, myLanguage[language][42], 310, ITEM5 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM5 + 6, PrimaryColor, PrimaryColorSmooth, 16);

      switch (af) {
        case 0: tftPrint(1, myLanguage[language][30], 310, ITEM6 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
        case 1: tftPrint(1, String(myLanguage[language][42]) + " / REG " + String(myLanguage[language][42]), 310, ITEM6 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
        case 2: tftPrint(1, String(myLanguage[language][42]) + " / REG " + String(myLanguage[language][30]), 310, ITEM6 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
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
      tftPrint(-1, myLanguage[language][82], 8, ITEM10 + 6, ActiveColor, ActiveColorSmooth, 16);

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
      tftPrint(1, "kHz", 310, ITEM8 + 6, ActiveColor, ActiveColorSmooth, 16);

      switch (fmdefaultstepsize) {
        case 0: tftPrint(1, String(FREQ_FM_STEP_50K * 10, DEC), 270, ITEM8 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
        case 1: tftPrint(1, String(FREQ_FM_STEP_100K * 10, DEC), 270, ITEM8 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
        case 2: tftPrint(1, String(FREQ_FM_STEP_200K * 10, DEC), 270, ITEM8 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
      }

      switch (bandFM) {
        case FM_BAND_ALL: tftPrint(1, myLanguage[language][105] + String(",") + myLanguage[language][106], 310, ITEM9 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
        case FM_BAND_OIRT: tftPrint(1, myLanguage[language][106], 310, ITEM9 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
        case FM_BAND_FM: tftPrint(1, myLanguage[language][105], 310, ITEM9 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
        case FM_BAND_NONE: tftPrint(1, myLanguage[language][83], 310, ITEM9 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
      }
      tftPrint(1, String(fmscansens), 310, ITEM10 + 6, PrimaryColor, PrimaryColorSmooth, 16);
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
      tftPrint(-1, myLanguage[language][169], 8, ITEM9 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][82], 8, ITEM10 + 6, ActiveColor, ActiveColorSmooth, 16);

      if (softmuteam) tftPrint(1, myLanguage[language][42], 310, ITEM1 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM1 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      if (amnb != 0) tftPrint(1, "%", 310, ITEM2 + 6, ActiveColor, ActiveColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM2 + 6, ActiveColor, ActiveColorSmooth, 16);
      if (amnb != 0) tftPrint(1, String(amnb, DEC), 270, ITEM2 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM2 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      tftPrint(1, "dB", 310, ITEM3 + 6, ActiveColor, ActiveColorSmooth, 16);
      if (AMLevelOffset > 0) tftPrint(1, "+" + String(AMLevelOffset, DEC), 270, ITEM3 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, String(AMLevelOffset, DEC), 270, ITEM3 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      if (amrfagc != 0) tftPrint(1, "dB", 310, ITEM8 + 6, ActiveColor, ActiveColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM8 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      tftPrint(1, "kHz", 310, ITEM9 + 6, ActiveColor, ActiveColorSmooth, 16);

      switch (bandAM) {
        case AM_BAND_ALL: tftPrint(1, myLanguage[language][102] + String(",") + myLanguage[language][103] + String(",") + myLanguage[language][104], 310, ITEM4 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
        case AM_BAND_LW_MW: tftPrint(1, myLanguage[language][102] + String(",") + myLanguage[language][103], 310, ITEM4 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
        case AM_BAND_LW_SW: tftPrint(1, myLanguage[language][102] + String(",") + myLanguage[language][104], 310, ITEM4 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
        case AM_BAND_MW_SW: tftPrint(1, myLanguage[language][103] + String(",") + myLanguage[language][104], 310, ITEM4 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
        case AM_BAND_LW: tftPrint(1, myLanguage[language][102], 310, ITEM4 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
        case AM_BAND_MW: tftPrint(1, myLanguage[language][103], 310, ITEM4 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
        case AM_BAND_SW: tftPrint(1, myLanguage[language][104], 310, ITEM4 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
        case AM_BAND_NONE: tftPrint(1, myLanguage[language][83], 310, ITEM4 + 6, PrimaryColor, PrimaryColorSmooth, 16); break;
      }

      if (showSWMIBand) tftPrint(1, myLanguage[language][42], 310, ITEM5 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM5 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      if (amcodect != 0) tftPrint(1, "%", 310, ITEM6 + 6, ActiveColor, ActiveColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM6 + 6, ActiveColor, ActiveColorSmooth, 16);
      if (amcodect != 0) tftPrint(1, String(amcodect, DEC), 270, ITEM6 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM6 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      tftPrint(1, String(amcodectcount, DEC), 310, ITEM7 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      if (amrfagc != 0) tftPrint(1, String(amrfagc, DEC), 270, ITEM8 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      if (mwstepsize) tftPrint(1, "10", 270, ITEM9 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, "9", 270, ITEM9 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      tftPrint(1, String(amscansens), 310, ITEM10 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      break;

    case CONNECTIVITY:
      tftPrint(-1, myLanguage[language][50], 8, ITEM1 + 6, ActiveColor, ActiveColorSmooth, 16);
      if (wifi) tftPrint(-1, String(myLanguage[language][51]) + " IP: " + String(WiFi.localIP().toString()), 8, ITEM2 + 6, ActiveColor, ActiveColorSmooth, 16); else tftPrint(-1, myLanguage[language][51], 8, ITEM2 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][52], 8, ITEM3 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][58], 8, ITEM4 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][197], 8, ITEM5 + 6, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, myLanguage[language][205], 8, ITEM6 + 6, ActiveColor, ActiveColorSmooth, 16);

      if (USBmode) tftPrint(1, "RDS Spy", 310, ITEM1 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, "XDRGTK", 310, ITEM1 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      if (wifi) tftPrint(1, myLanguage[language][42], 310, ITEM2 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM2 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      tftPrint(1, ">", 310, ITEM3 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      if (wifi) tftPrint(1, String(WiFi.localIP()[0]) + "." + String(WiFi.localIP()[1]) + "." + String(WiFi.localIP()[2]) + "." + String(subnetclient, DEC), 310, ITEM4 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, "-", 310, ITEM4 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      tftPrint(1, String(stationlistid, DEC), 310, ITEM5 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      if (XDRGTKMuteScreen) tftPrint(1, myLanguage[language][42], 310, ITEM6 + 6, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(1, myLanguage[language][30], 310, ITEM6 + 6, PrimaryColor, PrimaryColorSmooth, 16);
      break;

  }
  analogWrite(SMETERPIN, 0);
}

void BuildAdvancedRDS() {
  afscreen = false;
  afpage = false;
  afpagenr = 1;
  advancedRDS = true;
  ScreensaverTimerSet(OFF);
  if (CurrentSkin == 0) {
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
    if (region == REGION_EU) tftPrint(-1, "PI", 216, 81, ActiveColor, ActiveColorSmooth, 16);
    if (region == REGION_US) {
      tftPrint(-1, "PI:", 216, 72, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, "ID:", 216, 89, ActiveColor, ActiveColorSmooth, 16);
    }
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

    tft.drawBitmap(122, 5, RDSLogo, 35, 22, GreyoutColor);
    tft.drawBitmap(92, 4, Speaker, 26, 22, GreyoutColor);

    if (!StereoToggle) {
      tft.drawSmoothCircle(71, 15, 10, SecondaryColor, SecondaryColorSmooth);
      tft.drawSmoothCircle(71, 15, 9, SecondaryColor, SecondaryColorSmooth);
    } else {
      tft.drawSmoothCircle(66, 15, 10, GreyoutColor, BackgroundColor);
      tft.drawSmoothCircle(66, 15, 9, GreyoutColor, BackgroundColor);
      tft.drawSmoothCircle(76, 15, 10, GreyoutColor, BackgroundColor);
      tft.drawSmoothCircle(76, 15, 9, GreyoutColor, BackgroundColor);
    }

    tftPrint(-1, "TP", 2, 51, GreyoutColor, BackgroundColor, 16);
    tftPrint(-1, "TA", 24, 51, GreyoutColor, BackgroundColor, 16);
    tftPrint(-1, "AF", 50, 51, GreyoutColor, BackgroundColor, 16);
    tftPrint(-1, "-B", 68, 51, GreyoutColor, BackgroundColor, 16);
    tftPrint(-1, "TMC", 88, 51, GreyoutColor, BackgroundColor, 16);
    tftPrint(-1, "RT+", 123, 51, GreyoutColor, BackgroundColor, 16);
    tftPrint(-1, "EON", 153, 51, GreyoutColor, BackgroundColor, 16);
    tftPrint(-1, "S", 185, 51, GreyoutColor, BackgroundColor, 16);
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
  ptynold = " ";
  PIold = " ";
  PSold = " ";
  stationIDold = " ";
  stationStateold = " ";
  MSold = 0;
  licold = 254;
  af_counterold = 254;
  TAold = false;
  TPold = false;
  hastmcold = false;
  dynamicPTYold = false;
  artheadold = false;
  compressedold = false;
  rdsstereoold = false;
  hasafold = false;
  haseonold = false;
  BWreset = true;
  pinstringold = "";
  hasrtplusold = false;
  afmethodBold = false;
  rds_clockold = "";
  dropout = false;
  rdsreset = true;
  ShowMemoryPos();
  xPos = 0;
  xPos2 = 0;
  xPos3 = 0;
  xPos4 = 0;
}

void BuildDisplay() {
  afscreen = false;
  advancedRDS = false;
  int bandColor;
  if (CurrentSkin == 0) {
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
    if (usesquelch) tftPrint(-1, "SQ:", 212, 145, ActiveColor, ActiveColorSmooth, 16);
    tftPrint(1, "C/N", 270, 163, ActiveColor, ActiveColorSmooth, 16);
    tftPrint(-1, "dB", 300, 163, ActiveColor, ActiveColorSmooth, 16);
    if (region == REGION_EU) tftPrint(-1, "PI:", 212, 193, ActiveColor, ActiveColorSmooth, 16);
    if (region == REGION_US) {
      tftPrint(-1, "PI:", 212, 184, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(-1, "ID:", 212, 201, ActiveColor, ActiveColorSmooth, 16);
    }
    tftPrint(-1, "PS:", 3, 193, ActiveColor, ActiveColorSmooth, 16);
    tftPrint(-1, "RT:", 3, 221, ActiveColor, ActiveColorSmooth, 16);
    tftPrint(-1, "PTY:", 3, 163, ActiveColor, ActiveColorSmooth, 16);

    tftPrint(0, "S", 7, 101, ActiveColor, ActiveColorSmooth, 16);
    tftPrint(-1, "1", 24, 115, ActiveColor, ActiveColorSmooth, 16);
    tftPrint(-1, "3", 48, 115, ActiveColor, ActiveColorSmooth, 16);
    tftPrint(-1, "5", 72, 115, ActiveColor, ActiveColorSmooth, 16);
    tftPrint(-1, "7", 96, 115, ActiveColor, ActiveColorSmooth, 16);
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

    tft.drawRoundRect(248, 56, 32, 20, 5, GreyoutColor);
    if (band > BAND_GAP) tftPrint(0, "iMS", 265, 59, GreyoutColor, BackgroundColor, 16);
    tft.drawRoundRect(286, 56, 32, 20, 5, GreyoutColor);
    if (band > BAND_GAP) tftPrint(0, "EQ", 303, 59, GreyoutColor, BackgroundColor, 16);

    tft.drawBitmap(122, 5, RDSLogo, 35, 22, GreyoutColor);
    tft.drawBitmap(92, 4, Speaker, 26, 22, GreyoutColor);

    if (!StereoToggle) {
      tft.drawSmoothCircle(71, 15, 10, SecondaryColor, SecondaryColorSmooth);
      tft.drawSmoothCircle(71, 15, 9, SecondaryColor, SecondaryColorSmooth);
    } else {
      tft.drawSmoothCircle(66, 15, 10, GreyoutColor, BackgroundColor);
      tft.drawSmoothCircle(66, 15, 9, GreyoutColor, BackgroundColor);
      tft.drawSmoothCircle(76, 15, 10, GreyoutColor, BackgroundColor);
      tft.drawSmoothCircle(76, 15, 9, GreyoutColor, BackgroundColor);
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
  PIold = " ";
  PSold = " ";
  stationIDold = " ";
  stationStateold = " ";
  BWreset = true;
  dropout = false;
  xPos = 0;
  if (band < BAND_GAP) tftPrint(-1, "MHz", 258, 76, ActiveColor, ActiveColorSmooth, 28); else tftPrint(-1, "kHz", 258, 76, ActiveColor, ActiveColorSmooth, 28);
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
            if (tot != 0) tftPrint(-1, myLanguage[language][80], 170, 118, BackgroundColor, BackgroundColor, 28);
            if (tot != 0) tftPrint(1, String(tot), 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            switch (tot) {
              case 0: tot = 15; break;
              case 15: tot = 30; break;
              case 30: tot = 60; break;
              case 60: tot = 90; break;
              default: tot = 0; break;
            }
            if (tot != 0) tftPrint(-1, myLanguage[language][80], 170, 118, ActiveColor, ActiveColorSmooth, 28);
            if (tot != 0) tftPrint(1, String(tot), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM4:
            if (usesquelch) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (usesquelch) usesquelch = false; else usesquelch = true;
            if (usesquelch) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM5:
            if (spispeed == SPI_SPEED_DEFAULT) tftPrint(1,  String(myLanguage[language][204]) + " " + String(SPI_FREQUENCY / 1000000, DEC), 155, 118, BackgroundColor, BackgroundColor, 28);
            else tftPrint(1, String(spispeed * 10, DEC), 155, 118, BackgroundColor, BackgroundColor, 28);

            spispeed++;
            if (spispeed > SPI_SPEED_COUNT - 1) spispeed = 0;

            if (spispeed == SPI_SPEED_DEFAULT) tftPrint(1,  String(myLanguage[language][204]) + " " + String(SPI_FREQUENCY / 1000000, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            else tftPrint(1, String(spispeed * 10, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);

            if (spispeed == SPI_SPEED_DEFAULT) tft.setSPISpeed(SPI_FREQUENCY / 1000000); else tft.setSPISpeed(spispeed * 10);
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
            if (StereoLevel != 0) tftPrint(-1, "dBμV", 170, 118, ActiveColor, ActiveColorSmooth, 28);
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
            if (HighCutOffset != 0) tftPrint(-1, "dBμV", 170, 118, ActiveColor, ActiveColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            if (HighCutOffset != 0) tftPrint(1, String(HighCutOffset, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            radio.setHighCutOffset(HighCutOffset);
            break;

          case ITEM7:
            tftPrint(0, myLanguage[language][199], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            if (fmdeemphasis != DEEMPHASIS_NONE) tftPrint(1, String((fmdeemphasis == DEEMPHASIS_50 ? FM_DEEMPHASIS_50 : FM_DEEMPHASIS_75), DEC), 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (fmnb != 0) tftPrint(-1, "μs", 170, 118, ActiveColor, ActiveColor, 28);
            if (fmdeemphasis != DEEMPHASIS_NONE) tftPrint(-1, "μs", 170, 118, BackgroundColor, BackgroundColor, 28);
            fmdeemphasis++;
            if (fmdeemphasis > DEEMPHASIS_COUNT - 1) fmdeemphasis = DEEMPHASIS_NONE;
            if (fmdeemphasis != DEEMPHASIS_NONE) tftPrint(1, String((fmdeemphasis == DEEMPHASIS_50 ? FM_DEEMPHASIS_50 : FM_DEEMPHASIS_75), DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            if (fmdeemphasis != DEEMPHASIS_NONE) tftPrint(-1, "μs", 170, 118, ActiveColor, PrimaryColorSmooth, 28);
            radio.setDeemphasis(fmdeemphasis);
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
            if (showmodulation) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (showmodulation) showmodulation = false; else showmodulation = true;
            if (showmodulation) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM4:
            if (screensaverset) tftPrint(-1, myLanguage[language][92], 170, 118, BackgroundColor, BackgroundColor, 28);
            if (!screensaverset) tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(1, String(screensaverOptions[screensaverset]), 155, 118, BackgroundColor, BackgroundColor, 28);
            screensaverset ++;
            if (screensaverset > sizeof(screensaverOptions) / sizeof(screensaverOptions[0]) - 1) screensaverset = 0;
            if (screensaverset) tftPrint(-1, myLanguage[language][92], 170, 118, ActiveColor, ActiveColorSmooth, 28);
            if (!screensaverset) tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(1, String(screensaverOptions[screensaverset]), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM5:
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

          case ITEM6:
            switch (batteryoptionsold) {
              case BATTERY_NONE: tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case BATTERY_VALUE: tftPrint(0, myLanguage[language][174], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case BATTERY_PERCENT: tftPrint(0, myLanguage[language][175], 155, 118, BackgroundColor, BackgroundColor, 28); break;
            }

            batteryoptions++;
            if (batteryoptions > RADIO_BATTERY_CNT - 1) batteryoptions = 0;

            switch (batteryoptions) {
              case BATTERY_NONE: tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case BATTERY_VALUE: tftPrint(0, myLanguage[language][174], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case BATTERY_PERCENT: tftPrint(0, myLanguage[language][175], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
            }
            batteryoptionsold = batteryoptions;
            break;

          case ITEM7:
            tftPrint(0, unitString[unit], 155, 118, BackgroundColor, BackgroundColor, 28);
            unit ++;
            if (unit > sizeof(unitString) / sizeof(unitString[0]) - 1) unit = 0;
            tftPrint(0, unitString[unit], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM8:
            tftPrint(0, Skin[CurrentSkin], 155, 118, BackgroundColor, BackgroundColor, 28);
            CurrentSkin ++;
            if (CurrentSkin > sizeof(Skin) / sizeof(Skin[0]) - 1) CurrentSkin = 0;
            tftPrint(0, Skin[CurrentSkin], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM9:
            CurrentTheme ++;
            if (CurrentTheme > sizeof(Theme) / sizeof(Theme[0]) - 1) CurrentTheme = 0;
            doTheme();
            tft.drawRoundRect(10, 30, 300, 170, 5, ActiveColor);
            tft.fillRoundRect(12, 32, 296, 166, 5, BackgroundColor);
            tftPrint(0, myLanguage[language][77], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            tftPrint(0, Theme[CurrentTheme], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM10:
            tftPrint(0, FreqFont[freqfont], 155, 118, BackgroundColor, BackgroundColor, 28);
            freqfont ++;
            if (freqfont > sizeof(FreqFont) / sizeof(FreqFont[0]) - 1) freqfont = 0;
            tftPrint(0, FreqFont[freqfont], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
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
            radio.rds.region = region;
            break;

          case ITEM3:
            if (radio.underscore) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (radio.underscore) radio.underscore = false; else radio.underscore = true;
            if (radio.underscore) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
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
              case 1: tftPrint(0, String(myLanguage[language][42]) + " / REG " + String(myLanguage[language][42]), 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case 2: tftPrint(0, String(myLanguage[language][42]) + " / REG " + String(myLanguage[language][30]), 155, 118, BackgroundColor, BackgroundColor, 28); break;
            }
            af++;
            if (af > 2) af = 0;

            switch (af) {
              case 0: tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case 1: tftPrint(0, String(myLanguage[language][42]) + " / REG " + String(myLanguage[language][42]), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case 2: tftPrint(0, String(myLanguage[language][42]) + " / REG " + String(myLanguage[language][30]), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
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
            if (fmnb != 0) tftPrint(-1, "%", 170, 118, ActiveColor, ActiveColorSmooth, 28);
            radio.setFMNoiseBlanker(fmnb);
            break;

          case ITEM8:
            switch (fmdefaultstepsize) {
              case 0: tftPrint(1, String(FREQ_FM_STEP_50K * 10, DEC), 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case 1: tftPrint(1, String(FREQ_FM_STEP_100K * 10, DEC), 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case 2: tftPrint(1, String(FREQ_FM_STEP_200K * 10, DEC), 155, 118, BackgroundColor, BackgroundColor, 28); break;
            }
            fmdefaultstepsize++;
            if (fmdefaultstepsize > 2) fmdefaultstepsize = 0;
            switch (fmdefaultstepsize) {
              case 0: tftPrint(1, String(FREQ_FM_STEP_50K * 10, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case 1: tftPrint(1, String(FREQ_FM_STEP_100K * 10, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case 2: tftPrint(1, String(FREQ_FM_STEP_200K * 10, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
            }
            break;

          case ITEM9:
            switch (bandFM) {
              case FM_BAND_ALL: tftPrint(0, myLanguage[language][105] + String(",") + myLanguage[language][106], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case FM_BAND_OIRT: tftPrint(0, myLanguage[language][106], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case FM_BAND_FM: tftPrint(0, myLanguage[language][105], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case FM_BAND_NONE: tftPrint(0, myLanguage[language][83], 155, 118, BackgroundColor, BackgroundColor, 28); break;
            }

            bandFM++;
            if (bandFM > FM_BAND_CNT - 1) bandFM = FM_BAND_ALL;

            switch (bandFM) {
              case FM_BAND_ALL: tftPrint(0, myLanguage[language][105] + String(",") + myLanguage[language][106], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case FM_BAND_OIRT: tftPrint(0, myLanguage[language][106], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case FM_BAND_FM: tftPrint(0, myLanguage[language][105], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case FM_BAND_NONE: tftPrint(0, myLanguage[language][83], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
            }
            break;

          case ITEM10:
            tftPrint(1, String(fmscansens), 155, 118, BackgroundColor, BackgroundColor, 28);
            fmscansens++;
            if (fmscansens > 15) fmscansens = 1;
            tftPrint(1, String(fmscansens), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
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
            if (amnb != 0) tftPrint(-1, "%", 170, 118, ActiveColor, ActiveColorSmooth, 28);
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
              case AM_BAND_NONE: tftPrint(0, myLanguage[language][83], 155, 118, BackgroundColor, BackgroundColor, 28); break;
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
              case AM_BAND_NONE: tftPrint(0, myLanguage[language][83], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
            }
            break;

          case ITEM5:
            if (showSWMIBand) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (showSWMIBand) showSWMIBand = false; else showSWMIBand = true;
            if (showSWMIBand) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM6:
            if (amcodect != 0) tftPrint(-1, "%", 170, 118, BackgroundColor, BackgroundColor, 28);
            if (amcodect != 0) tftPrint(1, String(amcodect, DEC), 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            amcodect++;
            if (amcodect > 150 || amcodect <= 50) {
              if (amcodect == 1) amcodect = 50; else amcodect = 0;
            }
            if (amcodect != 0) tftPrint(-1, "%", 170, 118, ActiveColor, ActiveColorSmooth, 28);
            if (amcodect != 0) tftPrint(1, String(amcodect, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
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
            if (amrfagc != 0) tftPrint(-1, "dB", 170, 118, ActiveColor, ActiveColorSmooth, 28);
            if (band > BAND_GAP) radio.setAMAttenuation(amrfagc);
            break;

          case ITEM9:
            if (mwstepsize) tftPrint (1, "10", 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint (1, "9", 155, 118, BackgroundColor, BackgroundColor, 28);
            if (mwstepsize) mwstepsize = false; else mwstepsize = true;
            if (mwstepsize) tftPrint (1, "10", 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint (1, "9", 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM10:
            tftPrint(1, String(amscansens), 155, 118, BackgroundColor, BackgroundColor, 28);
            amscansens++;
            if (amscansens > 15) amscansens = 1;
            tftPrint(1, String(amscansens), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
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

          case ITEM6:
            if (XDRGTKMuteScreen) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (XDRGTKMuteScreen) XDRGTKMuteScreen = false; else XDRGTKMuteScreen = true;
            if (XDRGTKMuteScreen) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
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
            if (tot != 0) tftPrint(-1, myLanguage[language][80], 170, 118, BackgroundColor, BackgroundColor, 28);
            if (tot != 0) tftPrint(1, String(tot), 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            switch (tot) {
              case 15: tot = 0; break;
              case 30: tot = 15; break;
              case 60: tot = 30; break;
              case 90: tot = 60; break;
              default: tot = 90; break;
            }
            if (tot != 0) tftPrint(-1, myLanguage[language][80], 170, 118, ActiveColor, ActiveColorSmooth, 28);
            if (tot != 0) tftPrint(1, String(tot), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM4:
            if (usesquelch) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (usesquelch) usesquelch = false; else usesquelch = true;
            if (usesquelch) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM5:
            if (spispeed == SPI_SPEED_DEFAULT) tftPrint(1,  String(myLanguage[language][204]) + " " + String(SPI_FREQUENCY / 1000000, DEC), 155, 118, BackgroundColor, BackgroundColor, 28);
            else tftPrint(1, String(spispeed * 10, DEC), 155, 118, BackgroundColor, BackgroundColor, 28);

            spispeed--;
            if (spispeed > SPI_SPEED_COUNT - 1) spispeed = SPI_SPEED_COUNT - 1;

            if (spispeed == SPI_SPEED_DEFAULT) tftPrint(1,  String(myLanguage[language][204]) + " " + String(SPI_FREQUENCY / 1000000, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            else tftPrint(1, String(spispeed * 10, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);

            if (spispeed == SPI_SPEED_DEFAULT) tft.setSPISpeed(SPI_FREQUENCY / 1000000); else tft.setSPISpeed(spispeed * 10);
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
            if (StereoLevel != 0) tftPrint(-1, "dBμV", 170, 118, ActiveColor, ActiveColorSmooth, 28);
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
            if (HighCutOffset != 0) tftPrint(1, String(HighCutOffset, DEC), 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            HighCutOffset --;
            if (HighCutOffset < 20 || HighCutOffset > 60) {
              if (HighCutOffset > 60) HighCutOffset = 60; else HighCutOffset = 0;
            }
            if (HighCutOffset != 0) tftPrint(-1, "dBμV", 170, 118, ActiveColor, ActiveColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            if (HighCutOffset != 0) tftPrint(1, String(HighCutOffset, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            radio.setHighCutOffset(HighCutOffset);
            break;

          case ITEM7:
            tftPrint(0, myLanguage[language][199], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            if (fmdeemphasis != DEEMPHASIS_NONE) tftPrint(1, String((fmdeemphasis == DEEMPHASIS_50 ? FM_DEEMPHASIS_50 : FM_DEEMPHASIS_75), DEC), 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (fmdeemphasis != DEEMPHASIS_NONE) tftPrint(-1, "μs", 170, 118, BackgroundColor, BackgroundColor, 28);
            fmdeemphasis--;
            if (fmdeemphasis > DEEMPHASIS_COUNT - 1) fmdeemphasis = DEEMPHASIS_COUNT - 1;
            if (fmdeemphasis != DEEMPHASIS_NONE) tftPrint(1, String((fmdeemphasis == DEEMPHASIS_50 ? FM_DEEMPHASIS_50 : FM_DEEMPHASIS_75), DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            if (fmdeemphasis != DEEMPHASIS_NONE) tftPrint(-1, "μs", 170, 118, ActiveColor, PrimaryColorSmooth, 28);
            radio.setDeemphasis(fmdeemphasis);
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
            if (showmodulation) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (showmodulation) showmodulation = false; else showmodulation = true;
            if (showmodulation) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM4:
            if (screensaverset) tftPrint(-1, myLanguage[language][92], 170, 118, BackgroundColor, BackgroundColor, 28);
            if (!screensaverset) tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(1, String(screensaverOptions[screensaverset]), 155, 118, BackgroundColor, BackgroundColor, 28);
            screensaverset --;
            if (screensaverset > sizeof(screensaverOptions) / sizeof(screensaverOptions[0]) - 1) screensaverset = sizeof(screensaverOptions) / sizeof(screensaverOptions[0]) - 1;
            if (screensaverset) tftPrint(-1, myLanguage[language][92], 170, 118, ActiveColor, ActiveColorSmooth, 28);
            if (!screensaverset) tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(1, String(screensaverOptions[screensaverset]), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM5:
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

          case ITEM6:
            switch (batteryoptionsold) {
              case BATTERY_NONE: tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case BATTERY_VALUE: tftPrint(0, myLanguage[language][174], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case BATTERY_PERCENT: tftPrint(0, myLanguage[language][175], 155, 118, BackgroundColor, BackgroundColor, 28); break;
            }

            batteryoptions--;
            if (batteryoptions > RADIO_BATTERY_CNT - 1) batteryoptions = RADIO_BATTERY_CNT - 1;

            switch (batteryoptions) {
              case BATTERY_NONE: tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case BATTERY_VALUE: tftPrint(0, myLanguage[language][174], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case BATTERY_PERCENT: tftPrint(0, myLanguage[language][175], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
            }
            batteryoptionsold = batteryoptions;
            break;

          case ITEM7:
            tftPrint(0, unitString[unit], 155, 118, BackgroundColor, BackgroundColor, 28);
            unit --;
            if (unit > sizeof(unitString) / sizeof(unitString[0]) - 1) unit = sizeof(unitString) / sizeof(unitString[0]) - 1;
            tftPrint(0, unitString[unit], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM8:
            tftPrint(0, Skin[CurrentSkin], 155, 118, BackgroundColor, BackgroundColor, 28);
            CurrentSkin --;
            if (CurrentSkin > sizeof(Skin) / sizeof(Skin[0]) - 1) CurrentSkin = sizeof(Skin) / sizeof(Skin[0]) - 1;
            tftPrint(0, Skin[CurrentSkin], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM9:
            CurrentTheme --;
            if (CurrentTheme > sizeof(Theme) / sizeof(Theme[0]) - 1) CurrentTheme = sizeof(Theme) / sizeof(Theme[0]) - 1;
            doTheme();
            tft.drawRoundRect(10, 30, 300, 170, 5, ActiveColor);
            tft.fillRoundRect(12, 32, 296, 166, 5, BackgroundColor);
            tftPrint(0, myLanguage[language][77], 155, 78, ActiveColor, ActiveColorSmooth, 28);
            tftPrint(0, Theme[CurrentTheme], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM10:
            tftPrint(0, FreqFont[freqfont], 155, 118, BackgroundColor, BackgroundColor, 28);
            freqfont --;
            if (freqfont > sizeof(FreqFont) / sizeof(FreqFont[0]) - 1) freqfont = sizeof(FreqFont) / sizeof(FreqFont[0]) - 1;
            tftPrint(0, FreqFont[freqfont], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
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
            radio.rds.region = region;
            break;

          case ITEM3:
            if (radio.underscore) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (radio.underscore) radio.underscore = false; else radio.underscore = true;
            if (radio.underscore) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
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
              case 1: tftPrint(0, String(myLanguage[language][42]) + " / REG " + String(myLanguage[language][42]), 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case 2: tftPrint(0, String(myLanguage[language][42]) + " / REG " + String(myLanguage[language][30]), 155, 118, BackgroundColor, BackgroundColor, 28); break;
            }
            af--;
            if (af > 2) af = 2;

            switch (af) {
              case 0: tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case 1: tftPrint(0, String(myLanguage[language][42]) + " / REG " + String(myLanguage[language][42]), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case 2: tftPrint(0, String(myLanguage[language][42]) + " / REG " + String(myLanguage[language][30]), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
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
            if (fmnb != 0) tftPrint(-1, "%", 170, 118, ActiveColor, ActiveColorSmooth, 28);
            radio.setFMNoiseBlanker(fmnb);
            break;

          case ITEM8:
            switch (fmdefaultstepsize) {
              case 0: tftPrint(1, String(FREQ_FM_STEP_50K * 10, DEC), 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case 1: tftPrint(1, String(FREQ_FM_STEP_100K * 10, DEC), 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case 2: tftPrint(1, String(FREQ_FM_STEP_200K * 10, DEC), 155, 118, BackgroundColor, BackgroundColor, 28); break;
            }
            fmdefaultstepsize--;
            if (fmdefaultstepsize > 2) fmdefaultstepsize = 2;
            switch (fmdefaultstepsize) {
              case 0: tftPrint(1, String(FREQ_FM_STEP_50K * 10, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case 1: tftPrint(1, String(FREQ_FM_STEP_100K * 10, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case 2: tftPrint(1, String(FREQ_FM_STEP_200K * 10, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
            }
            break;

          case ITEM9:
            switch (bandFM) {
              case FM_BAND_ALL: tftPrint(0, myLanguage[language][105] + String(",") + myLanguage[language][106], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case FM_BAND_OIRT: tftPrint(0, myLanguage[language][106], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case FM_BAND_FM: tftPrint(0, myLanguage[language][105], 155, 118, BackgroundColor, BackgroundColor, 28); break;
              case FM_BAND_NONE: tftPrint(0, myLanguage[language][83], 155, 118, BackgroundColor, BackgroundColor, 28); break;
            }

            bandFM--;
            if (bandFM > FM_BAND_CNT) bandFM = FM_BAND_NONE;

            switch (bandFM) {
              case FM_BAND_ALL: tftPrint(0, myLanguage[language][105] + String(",") + myLanguage[language][106], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case FM_BAND_OIRT: tftPrint(0, myLanguage[language][106], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case FM_BAND_FM: tftPrint(0, myLanguage[language][105], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case FM_BAND_NONE: tftPrint(0, myLanguage[language][83], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
            }
            break;

          case ITEM10:
            tftPrint(1, String(fmscansens), 155, 118, BackgroundColor, BackgroundColor, 28);
            fmscansens--;
            if (fmscansens == 0) fmscansens = 15;
            tftPrint(1, String(fmscansens), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
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
            if (amnb != 0) tftPrint(-1, "%", 170, 118, ActiveColor, ActiveColorSmooth, 28);
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
              case AM_BAND_NONE: tftPrint(0, myLanguage[language][83], 155, 118, BackgroundColor, BackgroundColor, 28); break;
            }

            bandAM--;
            if (bandAM > AM_BAND_CNT) bandAM = AM_BAND_NONE;

            switch (bandAM) {
              case AM_BAND_ALL: tftPrint(0, myLanguage[language][102] + String(",") + myLanguage[language][103] + String(",") + myLanguage[language][104], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case AM_BAND_LW_MW: tftPrint(0, myLanguage[language][102] + String(",") + myLanguage[language][103], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case AM_BAND_LW_SW: tftPrint(0, myLanguage[language][102] + String(",") + myLanguage[language][104], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case AM_BAND_MW_SW: tftPrint(0, myLanguage[language][103] + String(",") + myLanguage[language][104], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case AM_BAND_LW: tftPrint(0, myLanguage[language][102], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case AM_BAND_MW: tftPrint(0, myLanguage[language][103], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case AM_BAND_SW: tftPrint(0, myLanguage[language][104], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case AM_BAND_NONE: tftPrint(0, myLanguage[language][83], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
            }
            break;

          case ITEM5:
            if (showSWMIBand) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (showSWMIBand) showSWMIBand = false; else showSWMIBand = true;
            if (showSWMIBand) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM6:
            if (amcodect != 0) tftPrint(-1, "%", 170, 118, BackgroundColor, BackgroundColor, 28);
            if (amcodect != 0) tftPrint(1, String(amcodect, DEC), 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            amcodect--;
            if (amcodect < 50 || amcodect > 150) {
              if (amcodect > 150) amcodect = 150; else amcodect = 0;
            }
            if (amcodect != 0) tftPrint(-1, "%", 170, 118, ActiveColor, ActiveColorSmooth, 28);
            if (amcodect != 0) tftPrint(1, String(amcodect, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
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
            if (amrfagc != 0) tftPrint(-1, "dB", 170, 118, ActiveColor, ActiveColorSmooth, 28);
            if (band > BAND_GAP) radio.setAMAttenuation(amrfagc);
            break;

          case ITEM9:
            if (mwstepsize) tftPrint (1, "10", 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint (1, "9", 155, 118, BackgroundColor, BackgroundColor, 28);
            if (mwstepsize) mwstepsize = false; else mwstepsize = true;
            if (mwstepsize) tftPrint (1, "10", 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint (1, "9", 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM10:
            tftPrint(1, String(amscansens), 155, 118, BackgroundColor, BackgroundColor, 28);
            amscansens--;
            if (amscansens == 0) amscansens = 15;
            tftPrint(1, String(amscansens), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
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

          case ITEM6:
            if (XDRGTKMuteScreen) tftPrint(0, myLanguage[language][42], 155, 118, BackgroundColor, BackgroundColor, 28); else tftPrint(0, myLanguage[language][30], 155, 118, BackgroundColor, BackgroundColor, 28);
            if (XDRGTKMuteScreen) XDRGTKMuteScreen = false; else XDRGTKMuteScreen = true;
            if (XDRGTKMuteScreen) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
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
            tft.drawRoundRect(10, 6, 300, 230, 5, ActiveColor);
            tft.fillRoundRect(12, 8, 296, 226, 5, BackgroundColor);
            tftPrint(0, myLanguage[language][71], 155, 13, ActiveColor, ActiveColorSmooth, 28);
            tftPrint(0, myLanguage[language][72], 155, 63, ActiveColor, ActiveColorSmooth, 28);
            tftPrint(0, "PE5PVB", 155, 43, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(1, "ohmytime", 145, 93, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(1, "HyperDX", 145, 108, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(-1, "MCelliotG", 155, 93, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(-1, "andimik", 155, 108, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(1, "DXHR05", 145, 123, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(1, "NoobishSVK", 145, 138, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(-1, "yo2ldk", 155, 123, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(-1, "Justin_Peng(Portable)", 155, 138, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(1, "Overland DX", 145, 153, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(-1, "elektronik232", 155, 153, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(1, "KOTYA8", 145, 168, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(-1, "mrwish7", 155, 168, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(1, "lxsxl", 145, 183, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(-1, "leryfm", 155, 183, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(1, "marsel90-1", 145, 198, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(-1, "lawendel", 155, 198, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(0, "github.com/PE5PVB/TEF6686_ESP32", 155, 215, ActiveColor, ActiveColorSmooth, 16);
            break;
        }
        break;

      case MAINSETTINGS:
        switch (menuoption) {
          case ITEM1:
            Infoboxprint(myLanguage[language][108]);
            switch (hardwaremodel) {
              case BASE_ILI9341: tftPrint(0, myLanguage[language][109], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case PORTABLE_ILI9341: tftPrint(0, myLanguage[language][110], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case PORTABLE_TOUCH_ILI9341: tftPrint(0, myLanguage[language][111], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
            }
            hardwaremodelold = hardwaremodel;
            break;

          case ITEM2:
            Infoboxprint(myLanguage[language][68]);
            if (touchrotating) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM3:
            Infoboxprint(myLanguage[language][75]);
            if (tot != 0) tftPrint(-1, myLanguage[language][80], 170, 118, ActiveColor, ActiveColorSmooth, 28);
            if (tot != 0) tftPrint(1, String(tot), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM4:
            Infoboxprint(myLanguage[language][62]);
            if (usesquelch) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM5:
            Infoboxprint(myLanguage[language][81]);
            tftPrint(-1, "MHz", 170, 118, ActiveColor, ActiveColorSmooth, 28);
            if (spispeed == SPI_SPEED_DEFAULT) tftPrint(1,  String(myLanguage[language][204]) + " " + String(SPI_FREQUENCY / 1000000, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(1, String(spispeed * 10 , DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;
        }
        break;

      case AUDIOSETTINGS:
        switch (menuoption) {
          case ITEM1:
            Infoboxprint(myLanguage[language][10]);
            tftPrint(-1, "dB", 170, 118, ActiveColor, ActiveColorSmooth, 28);
            if (VolSet > 0) tftPrint(1, "+" + String(VolSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(1, String(VolSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM2:
            Infoboxprint(myLanguage[language][45]);
            if (edgebeep) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM3:
            Infoboxprint(myLanguage[language][67]);
            if (audiomode) tftPrint(0, "MPX", 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, "Stereo", 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM4:
            Infoboxprint(myLanguage[language][15]);
            if (StereoLevel != 0) tftPrint(-1, "dBμV", 170, 118, ActiveColor, ActiveColorSmooth, 28);
            if (StereoLevel != 0) tftPrint(1, String(StereoLevel, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM5:
            Infoboxprint(myLanguage[language][16]);
            if (HighCutLevel != 0) tftPrint(-1, "Hz", 170, 118, ActiveColor, ActiveColorSmooth, 28);
            if (HighCutLevel != 0) tftPrint(1, String(HighCutLevel * 100, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM6:
            Infoboxprint(myLanguage[language][17]);
            if (HighCutOffset != 0) tftPrint(-1, "dBμV", 170, 118, ActiveColor, ActiveColorSmooth, 28);
            if (HighCutOffset != 0) tftPrint(1, String(HighCutOffset, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM7:
            Infoboxprint(myLanguage[language][199]);
            if (fmdeemphasis != DEEMPHASIS_NONE) tftPrint(1, String((fmdeemphasis == DEEMPHASIS_50 ? FM_DEEMPHASIS_50 : FM_DEEMPHASIS_75), DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            if (fmdeemphasis != DEEMPHASIS_NONE) tftPrint(-1, "μs", 170, 118, ActiveColor, PrimaryColorSmooth, 28);
            break;
        }
        break;

      case DISPLAYSETTINGS:
        switch (menuoption) {
          case ITEM1:
            Infoboxprint(myLanguage[language][40]);
            tftPrint(0, myLanguage[language][0], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM2:
            Infoboxprint(myLanguage[language][19]);
            tftPrint(-1, "%", 170, 118, ActiveColor, ActiveColorSmooth, 28);
            tftPrint(1, String(ContrastSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM3:
            Infoboxprint(myLanguage[language][63]);
            if (showmodulation) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM4:
            Infoboxprint(myLanguage[language][91]);
            if (screensaverset) tftPrint(-1, myLanguage[language][92], 170, 118, ActiveColor, ActiveColorSmooth, 28);
            if (!screensaverset) tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(1, String(screensaverOptions[screensaverset], DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM5:
            Infoboxprint(myLanguage[language][74]);
            switch (poweroptions) {
              case LCD_OFF: tftPrint(0, myLanguage[language][76], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case LCD_BRIGHTNESS_1_PERCENT: tftPrint(0, myLanguage[language][94], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case LCD_BRIGHTNESS_A_QUARTER: tftPrint(0, myLanguage[language][95], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case LCD_BRIGHTNESS_HALF: tftPrint(0, myLanguage[language][96], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
            }
            poweroptionsold = poweroptions;
            break;

          case ITEM6:
            Infoboxprint(myLanguage[language][173]);
            switch (batteryoptions) {
              case BATTERY_NONE: tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case BATTERY_VALUE: tftPrint(0, myLanguage[language][174], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case BATTERY_PERCENT: tftPrint(0, myLanguage[language][175], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
            }
            batteryoptionsold = batteryoptions;
            break;

          case ITEM7:
            Infoboxprint(myLanguage[language][98]);
            tftPrint(0, unitString[unit], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM8:
            Infoboxprint(myLanguage[language][78]);
            tftPrint(0, Skin[CurrentSkin], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM9:
            Infoboxprint(myLanguage[language][77]);
            tftPrint(0, Theme[CurrentTheme], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM10:
            Infoboxprint(myLanguage[language][85]);
            tftPrint(0, FreqFont[freqfont], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;
        }
        break;

      case RDSSETTINGS:
        switch (menuoption) {
          case ITEM1:
            Infoboxprint(myLanguage[language][38]);
            switch (showrdserrors) {
              case 0: tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case 1: tftPrint(0, myLanguage[language][200], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case 2: tftPrint(0, myLanguage[language][201], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case 3: tftPrint(0, myLanguage[language][202], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
            }
            break;

          case ITEM2:
            Infoboxprint(myLanguage[language][46]);
            if (region == REGION_EU) tftPrint(0, myLanguage[language][47], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            if (region == REGION_US) tftPrint(0, myLanguage[language][48], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM3:
            Infoboxprint(myLanguage[language][49]);
            if (radio.underscore) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM4:
            Infoboxprint(myLanguage[language][60]);
            if (radio.rds.filter) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM5:
            Infoboxprint(myLanguage[language][61]);
            if (radio.rds.pierrors) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM6:
            Infoboxprint(myLanguage[language][99]);
            switch (af) {
              case 0: tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case 1: tftPrint(0, String(myLanguage[language][42]) + " / REG " + String(myLanguage[language][42]), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case 2: tftPrint(0, String(myLanguage[language][42]) + " / REG " + String(myLanguage[language][30]), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
            }
            break;

          case ITEM7:
            Infoboxprint(myLanguage[language][176]);
            if (radio.rds.rtbuffer) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM8:
            Infoboxprint(myLanguage[language][196]);
            if (radio.rds.sortaf) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM9:
            Infoboxprint(myLanguage[language][203]);
            if (radio.rds.fastps) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;
        }
        break;

      case FMSETTINGS:
        switch (menuoption) {
          case ITEM1:
            Infoboxprint(myLanguage[language][11]);
            tftPrint(-1, "MHz", 170, 118, ActiveColor, ActiveColorSmooth, 28);
            tftPrint(1, String(ConverterSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM2:
            Infoboxprint(myLanguage[language][12]);
            tftPrint(-1, "MHz", 170, 118, ActiveColor, ActiveColorSmooth, 28);
            tftPrint(1, String(LowEdgeSet / 10 + ConverterSet, DEC) + "." + String(LowEdgeSet % 10 + ConverterSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM3:
            Infoboxprint(myLanguage[language][13]);
            tftPrint(-1, "MHz", 170, 118, ActiveColor, ActiveColorSmooth, 28);
            tftPrint(1, String(HighEdgeSet / 10 + ConverterSet, DEC) + "." + String(HighEdgeSet % 10 + ConverterSet, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM4:
            Infoboxprint(myLanguage[language][14]);
            tftPrint(-1, "dB", 170, 118, ActiveColor, ActiveColorSmooth, 28);
            tftPrint(-1, "dBμV", 190, 165, ActiveColor, ActiveColorSmooth, 28);
            if (LevelOffset > 0) tftPrint(1, "+" + String(LevelOffset, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(1, String(LevelOffset, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            SStatusold = 2000;
            change = true;
            break;

          case ITEM5:
            Infoboxprint(myLanguage[language][18]);
            tftPrint(-1, "dBμV", 155, 118, ActiveColor, ActiveColorSmooth, 28);
            tftPrint(1, String(LowLevelSet, DEC), 145, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM6:
            Infoboxprint(myLanguage[language][43]);
            if (softmutefm) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM7:
            Infoboxprint(myLanguage[language][65]);
            if (fmnb != 0) tftPrint(-1, "%", 170, 118, ActiveColor, ActiveColorSmooth, 28);
            if (fmnb != 0) tftPrint(1, String(fmnb, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM8:
            tftPrint(-1, "kHz", 170, 118, ActiveColor, ActiveColorSmooth, 28);
            Infoboxprint(myLanguage[language][90]);
            switch (fmdefaultstepsize) {
              case 0: tftPrint(1, String(FREQ_FM_STEP_50K * 10, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case 1: tftPrint(1, String(FREQ_FM_STEP_100K * 10, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case 2: tftPrint(1, String(FREQ_FM_STEP_200K * 10, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
            }
            break;

          case ITEM9:
            Infoboxprint(myLanguage[language][100]);
            switch (bandFM) {
              case FM_BAND_ALL: tftPrint(0, myLanguage[language][105] + String(",") + myLanguage[language][106], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case FM_BAND_OIRT: tftPrint(0, myLanguage[language][106], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case FM_BAND_FM: tftPrint(0, myLanguage[language][105], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case FM_BAND_NONE: tftPrint(0, myLanguage[language][83], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
            }
            break;

          case ITEM10:
            Infoboxprint(myLanguage[language][82]);
            tftPrint (1, String(fmscansens), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;
        }
        break;

      case AMSETTINGS:
        switch (menuoption) {
          case ITEM1:
            Infoboxprint(myLanguage[language][44]);
            if (softmuteam) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM2:
            Infoboxprint(myLanguage[language][64]);
            if (amnb != 0) tftPrint(-1, "%", 170, 118, ActiveColor, ActiveColorSmooth, 28);
            if (amnb != 0) tftPrint(1, String(amnb, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM3:
            Infoboxprint(myLanguage[language][97]);
            tftPrint(-1, "dB", 170, 118, ActiveColor, ActiveColorSmooth, 28);
            if (AMLevelOffset > 0) tftPrint(1, "+" + String(AMLevelOffset, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(1, String(AMLevelOffset, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM4:
            Infoboxprint(myLanguage[language][101]);
            switch (bandAM) {
              case AM_BAND_ALL: tftPrint(0, myLanguage[language][102] + String(",") + myLanguage[language][103] + String(",") + myLanguage[language][104], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case AM_BAND_LW_MW: tftPrint(0, myLanguage[language][102] + String(",") + myLanguage[language][103], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case AM_BAND_LW_SW: tftPrint(0, myLanguage[language][102] + String(",") + myLanguage[language][104], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case AM_BAND_MW_SW: tftPrint(0, myLanguage[language][103] + String(",") + myLanguage[language][104], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case AM_BAND_LW: tftPrint(0, myLanguage[language][102], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case AM_BAND_MW: tftPrint(0, myLanguage[language][103], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case AM_BAND_SW: tftPrint(0, myLanguage[language][104], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
              case AM_BAND_NONE: tftPrint(0, myLanguage[language][83], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); break;
            }
            break;

          case ITEM5:
            Infoboxprint(myLanguage[language][59]);
            if (showSWMIBand) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM6:
            Infoboxprint(myLanguage[language][186]);
            if (amcodect != 0) tftPrint(-1, "%", 170, 118, ActiveColor, ActiveColorSmooth, 28);
            if (amcodect != 0) tftPrint(1, String(amcodect, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM7:
            Infoboxprint(myLanguage[language][188]);
            tftPrint(0, String(amcodectcount, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM8:
            Infoboxprint(myLanguage[language][198]);
            if (amrfagc != 0) tftPrint(-1, "dB", 170, 118, ActiveColor, ActiveColorSmooth, 28);
            if (amrfagc != 0) tftPrint(1, String(amrfagc, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM9:
            Infoboxprint(myLanguage[language][169]);
            tftPrint(-1, "kHz", 170, 118, ActiveColor, ActiveColorSmooth, 28);
            if (mwstepsize) tftPrint (1, "10", 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint (1, "9", 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM10:
            Infoboxprint(myLanguage[language][82]);
            tftPrint (1, String(amscansens), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;
        }
        break;

      case CONNECTIVITY:
        switch (menuoption) {
          case ITEM1:
            Infoboxprint(myLanguage[language][50]);
            if (USBmode) tftPrint(0, "RDS Spy", 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, "XDRGTK", 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM2:
            Infoboxprint(myLanguage[language][51]);
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
              Infoboxprint(myLanguage[language][58]);
              tftPrint(0, String(WiFi.localIP()[0]) + "." + String(WiFi.localIP()[1]) + "." + String(WiFi.localIP()[2]) + "." + String(subnetclient, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            } else {
              menuopen = false;
              BuildMenu();
            }
            break;

          case ITEM5:
            Infoboxprint(myLanguage[language][197]);
            tftPrint(0, String(stationlistid, DEC), 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;

          case ITEM6:
            Infoboxprint(myLanguage[language][205]);
            if (XDRGTKMuteScreen) tftPrint(0, myLanguage[language][42], 155, 118, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, myLanguage[language][30], 155, 118, PrimaryColor, PrimaryColorSmooth, 28);
            break;
        }
        break;
    }
  } else {
    if (menupage == CONNECTIVITY && menuoption == ITEM2) {
      tryWiFi();
      delay(2000);
    }
    if (menupage == DISPLAYSETTINGS && menuoption == ITEM5) {
      doTheme();
    }
    menuopen = false;
    BuildMenu();
  }
}

void Infoboxprint(const char* input) {
  int length = strlen(input);
  int newlineIndex = -1;

  for (int i = 0; i < length; i++) {
    if (input[i] == '\n') {
      newlineIndex = i;
      break;
    }
  }

  if (newlineIndex != -1) {
    char* line1 = (char*)malloc((newlineIndex + 1) * sizeof(char));
    strncpy(line1, input, newlineIndex);
    line1[newlineIndex] = '\0';

    char* line2 = (char*)malloc((length - newlineIndex) * sizeof(char));
    strcpy(line2, input + newlineIndex + 1);

    tftPrint(0, line1, 155, 48, ActiveColor, ActiveColorSmooth, 28);
    tftPrint(0, line2, 155, 78, ActiveColor, ActiveColorSmooth, 28);
    free(line1);
    free(line2);
  } else {
    tftPrint(0, input, 155, 78, ActiveColor, ActiveColorSmooth, 28);
  }
}