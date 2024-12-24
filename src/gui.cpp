#include "gui.h"
#include "language.h"
#include "constants.h"
#include "config.h"
#include <WiFi.h>
#include <Wire.h>
#include <EEPROM.h>
#include <cstring>

byte menuitem;
byte items[10] = {10, static_cast<byte>(dynamicspi ? 10 : 9), 7, 10, 10, 10, 9, 6, 9, 9};
extern mem presets[];
bool setWiFiConnectParam = false;

void doTheme() {  // Use this to put your own colors in: http://www.barth-dev.de/online/rgb565-color-picker/
  switch (CurrentTheme) {
    case 0:  // Default PE5PVB theme
      PrimaryColor = Yellow;
      PrimaryColorSmooth = YellowSmooth;
      SecondaryColor = Skyblue;
      SecondaryColorSmooth = SkyblueSmooth;
      FrameColor = Blue;
      GreyoutColor = BlackOlive;
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
      SecondaryColor = White;
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
      RDSDropoutColor = PaleGrey;
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
      SecondaryColor = Darkgrey;
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
      GreyoutColor = BlackOlive;
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

    case 13:  // Bubblegum
      PrimaryColor = Cyan;
      PrimaryColorSmooth = CyanSmooth;
      SecondaryColor = Cherry;
      SecondaryColorSmooth = CherrySmooth;
      FrameColor = Electric;
      GreyoutColor = Meteorite;
      BackgroundColor = EerieBlack;
      ActiveColor = White;
      ActiveColorSmooth = WhiteSmooth;
      FreqColor = Pink;
      FreqColorSmooth = PinkSmooth;
      SignificantColor = Purple;
      SignificantColorSmooth = PurpleSmooth;
      InsignificantColor = Cherry;
      InsignificantColorSmooth = CherrySmooth;
      StereoColor = Cherry;
      StereoColorSmooth = CherrySmooth;
      RDSColor = Teal;
      RDSColorSmooth = TealSmooth;
      RDSDropoutColor = Logan;
      RDSDropoutColorSmooth = LoganSmooth;
      BarSignificantColor = Coral;
      BarInsignificantColor = Teal;
      ModBarSignificantColor = Sakura;
      ModBarInsignificantColor = Skyblue;
      BWAutoColor = Violet;
      BWAutoColorSmooth = VioletSmooth;
      BatteryValueColor = Turquoise;
      BatteryValueColorSmooth = CyanDarkSmooth;
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
  xPos2 = 0;
  xPos3 = 0;
  xPos4 = 0;
  xPos5 = 0;
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

void ShowOneLine(byte position, byte item, bool selected) {
  switch (CurrentTheme) {
    case 7: FullLineSprite.pushImage (-8, -(position + 2), 320, 240, configurationbackground_wo); break;
    default: FullLineSprite.pushImage (-8, -(position + 2), 320, 240, configurationbackground); break;
  }

  if (selected) {
    switch (CurrentTheme) {
      case 7: FullLineSprite.pushImage(0, 0, 304, 19, selector_wo); break;
      default: FullLineSprite.pushImage(0, 0, 304, 19, selector); break;
    }
  }

  switch (item) {
    case 0:
      switch (menupage) {
        case INDEX:
          FullLineSprite.setTextDatum(TC_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][177]), 152, 2);
          break;

        case MAINSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][108]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);

          switch (hardwaremodel) {
            case BASE_ILI9341: FullLineSprite.drawString(myLanguage[language][109], 298, 2); break;
            case PORTABLE_ILI9341: FullLineSprite.drawString(myLanguage[language][110], 298, 2); break;
            case PORTABLE_TOUCH_ILI9341: FullLineSprite.drawString(myLanguage[language][111], 298, 2); break;
          }
          break;

        case AUDIOSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][20]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString("dB", 298, 2);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((VolSet > 0 ? "+" : "") + String(VolSet, DEC), 258, 2);
          break;

        case DISPLAYSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][39]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(myLanguage[language][0], 298, 2);
          break;

        case RDSSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][38]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);

          switch (showrdserrors) {
            case 0: FullLineSprite.drawString(myLanguage[language][30], 298, 2); break;
            case 1: FullLineSprite.drawString(myLanguage[language][200], 298, 2); break;
            case 2: FullLineSprite.drawString(myLanguage[language][201], 298, 2); break;
          }
          break;

        case FMSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][21]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString("MHz", 298, 2);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(String(ConverterSet, DEC), 258, 2);
          break;

        case AMSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][44]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((softmuteam ? myLanguage[language][42] : myLanguage[language][30]), 298, 2);
          break;

        case CONNECTIVITY:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][50]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((USBmode ? "RDS Spy" : "XDRGTK"), 298, 2);
          break;

        case DXMODE:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][212]), 6, 2);
          break;

        case AUTOMEM:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][269]), 6, 2);
          break;
      }
      break;

    case 1:
      switch (menupage) {
        case INDEX:
          FullLineSprite.setTextDatum(TC_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][178]), 152, 2);
          break;

        case MAINSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][107]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((touchrotating ? myLanguage[language][42] : myLanguage[language][30]), 298, 2);
          break;

        case AUDIOSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][45]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((edgebeep ? myLanguage[language][42] : myLanguage[language][30]), 298, 2);
          break;

        case DISPLAYSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][29]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(String(ContrastSet, DEC), 258, 2);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString("%", 298, 2);
          break;

        case RDSSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][46]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          if (region == REGION_EU) FullLineSprite.drawString(myLanguage[language][47], 298, 2);
          if (region == REGION_US) FullLineSprite.drawString(myLanguage[language][48], 298, 2);
          break;

        case FMSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][22]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString("MHz", 298, 2);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(String(LowEdgeSet / 10 + ConverterSet, DEC) + "." + String(LowEdgeSet % 10 + ConverterSet, DEC), 258, 2);
          break;

        case AMSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][64]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          if (amnb != 0) FullLineSprite.drawString(String(amnb, DEC), 258, 2);
          if (amnb != 0) FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString((amnb != 0 ? "%" : myLanguage[language][30]), 298, 2);
          break;

        case CONNECTIVITY:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][51] + (wifi ? " IP: " + String(WiFi.localIP().toString()) : "")), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((wifi ? myLanguage[language][42] : myLanguage[language][30]), 298, 2);
          break;

        case DXMODE:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][209]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(String(scanstart + 1, DEC), 298, 2);
          break;

        case AUTOMEM:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][264]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString("MHz", 298, 2);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(String(memstartfreq / 10 + ConverterSet, DEC) + "." + String(memstartfreq % 10 + ConverterSet, DEC), 258, 2);
          break;
      }
      break;

    case 2:
      switch (menupage) {
        case INDEX:
          FullLineSprite.setTextDatum(TC_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][179]), 152, 2);
          break;

        case MAINSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][75]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          if (tot != 0) FullLineSprite.drawString(String(tot), 258, 2);
          if (tot != 0) FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString((tot != 0 ? myLanguage[language][80] : myLanguage[language][30]), 298, 2);
          break;

        case AUDIOSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][67]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((audiomode ? "MPX" : "Stereo"), 298, 2);
          break;

        case DISPLAYSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][63]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((showmodulation ? myLanguage[language][42] : myLanguage[language][30]), 298, 2);
          break;

        case RDSSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][49]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((radio.underscore ? myLanguage[language][42] : myLanguage[language][30]), 298, 2);
          break;

        case FMSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][23]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString("MHz", 298, 2);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(String(HighEdgeSet / 10 + ConverterSet, DEC) + "." + String(HighEdgeSet % 10 + ConverterSet, DEC), 258, 2);
          break;

        case AMSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][97]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString("dB", 298, 2);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((AMLevelOffset > 0 ? "+" : "") + String(AMLevelOffset, DEC), 258, 2);
          break;

        case CONNECTIVITY:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][52]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(">", 298, 2);
          break;

        case DXMODE:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][210]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(String(scanstop + 1, DEC), 298, 2);
          break;

        case AUTOMEM:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][265]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString("MHz", 298, 2);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(String(memstopfreq / 10 + ConverterSet, DEC) + "." + String(memstopfreq % 10 + ConverterSet, DEC), 258, 2);
          break;
      }
      break;

    case 3:
      switch (menupage) {
        case INDEX:
          FullLineSprite.setTextDatum(TC_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][180]), 152, 2);
          break;

        case MAINSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][62]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          if (autosquelch) FullLineSprite.drawString(myLanguage[language][86], 298, 2); else FullLineSprite.drawString((usesquelch ? myLanguage[language][42] : myLanguage[language][30]), 298, 2);
          break;

        case AUDIOSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][25]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          if (StereoLevel != 0) FullLineSprite.drawString(String(StereoLevel, DEC), 258, 2);
          if (StereoLevel != 0) FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString((StereoLevel != 0 ? "dBμV" : myLanguage[language][30]), 298, 2);
          break;

        case DISPLAYSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][91]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          if (screensaverset) FullLineSprite.drawString(String(screensaverOptions[screensaverset], DEC), 258, 2);
          if (screensaverset) FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString((screensaverset ? myLanguage[language][92] : myLanguage[language][30]), 298, 2);
          break;

        case RDSSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][60]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((radio.rds.filter ? myLanguage[language][42] : myLanguage[language][30]), 298, 2);
          break;

        case FMSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][24]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString("dB", 298, 2);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((LevelOffset > 0 ? "+" : "") + String(LevelOffset, DEC), 258, 2);
          break;

        case AMSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][59]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((showSWMIBand ? myLanguage[language][42] : myLanguage[language][30]), 298, 2);
          break;

        case CONNECTIVITY:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][58]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((wifi ? String(WiFi.localIP()[0]) + "." + String(WiFi.localIP()[1]) + "." + String(WiFi.localIP()[2]) + "." + String(subnetclient, DEC) : "-"), 298, 2);
          break;

        case DXMODE:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][211]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][92]), 298, 2);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((scanhold == 0 ? "0.5" : String(scanhold, DEC)), 258, 2);
          break;

        case AUTOMEM:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][266]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(String(memstartpos + 1, DEC), 298, 2);
          break;
      }
      break;

    case 4:
      switch (menupage) {
        case INDEX:
          FullLineSprite.setTextDatum(TC_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][181]), 152, 2);
          break;

        case MAINSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][37]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString("dBµV", 298, 2);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(String(fmagc, DEC), 258, 2);
          break;

        case AUDIOSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][26]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(String(HighCutLevel * 100, DEC), 258, 2);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString("Hz", 298, 2);
          break;

        case DISPLAYSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][74]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);

          switch (poweroptions) {
            case LCD_OFF: FullLineSprite.drawString(myLanguage[language][76], 298, 2); break;
            case LCD_BRIGHTNESS_1_PERCENT: FullLineSprite.drawString(myLanguage[language][94], 298, 2); break;
            case LCD_BRIGHTNESS_A_QUARTER: FullLineSprite.drawString(myLanguage[language][95], 298, 2); break;
            case LCD_BRIGHTNESS_HALF: FullLineSprite.drawString(myLanguage[language][96], 298, 2); break;
          }
          break;

        case RDSSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][61]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((radio.rds.pierrors ? myLanguage[language][42] : myLanguage[language][30]), 298, 2);
          break;

        case FMSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][28]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString("dBμV", 298, 2);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(String(LowLevelSet, DEC), 258, 2);
          break;

        case AMSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][185]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          if (amcodect != 0) FullLineSprite.drawString(String(amcodect, DEC), 258, 2);
          if (amcodect != 0) FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString((amcodect != 0 ? "%" : myLanguage[language][30]), 298, 2);
          break;

        case CONNECTIVITY:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][271]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(String(stationlistid, DEC), 298, 2);
          break;

        case DXMODE:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][216]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((scanmem ? myLanguage[language][218] : myLanguage[language][217]), 298, 2);
          break;

        case AUTOMEM:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][267]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(String(memstoppos + 1, DEC), 298, 2);
          break;
      }
      break;

    case 5:
      switch (menupage) {
        case INDEX:
          FullLineSprite.setTextDatum(TC_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][182]), 152, 2);
          break;

        case MAINSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][198]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString("dBµV", 298, 2);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(String(amagc, DEC), 258, 2);
          break;

        case AUDIOSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][27]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          if (HighCutOffset != 0) FullLineSprite.drawString(String(HighCutOffset, DEC), 258, 2);
          if (HighCutOffset != 0) FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString((HighCutOffset != 0 ? "dBμV" : myLanguage[language][30]), 298, 2);
          break;

        case DISPLAYSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][173]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);

          switch (batteryoptions) {
            case BATTERY_NONE: FullLineSprite.drawString(myLanguage[language][30], 298, 2); break;
            case BATTERY_VALUE: FullLineSprite.drawString(myLanguage[language][174], 298, 2); break;
            case BATTERY_PERCENT: FullLineSprite.drawString(myLanguage[language][175], 298, 2); break;
          }
          break;

        case RDSSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][99]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);

          switch (af) {
            case 0: FullLineSprite.drawString(myLanguage[language][30], 298, 2); break;
            case 1: FullLineSprite.drawString(String(myLanguage[language][42]) + " / REG " + String(myLanguage[language][42]), 298, 2); break;
            case 2: FullLineSprite.drawString(String(myLanguage[language][42]) + " / REG " + String(myLanguage[language][30]), 298, 2); break;
          }
          break;

        case FMSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][43]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((softmutefm ? myLanguage[language][42] : myLanguage[language][30]), 298, 2);
          break;

        case AMSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][187]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(String(amcodectcount, DEC), 298, 2);
          break;

        case CONNECTIVITY:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][205]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((XDRGTKMuteScreen ? myLanguage[language][42] : myLanguage[language][30]), 298, 2);
          break;

        case DXMODE:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][219]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          switch (scancancel) {
            case OFF: FullLineSprite.drawString(myLanguage[language][30], 298, 2); break;
            case CORRECTPI: FullLineSprite.drawString(myLanguage[language][220], 298, 2); break;
            case SIGNAL: FullLineSprite.drawString(myLanguage[language][221], 298, 2); break;
          }
          break;

        case AUTOMEM:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][268]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((mempionly ? myLanguage[language][42] : myLanguage[language][30]), 298, 2);
          break;
      }
      break;

    case 6:
      switch (menupage) {
        case INDEX:
          FullLineSprite.setTextDatum(TC_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][183]), 152, 2);
          break;

        case MAINSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][100]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);

          switch (bandFM) {
            case FM_BAND_ALL: FullLineSprite.drawString(myLanguage[language][105] + String(",") + myLanguage[language][106], 298, 2); break;
            case FM_BAND_OIRT: FullLineSprite.drawString(myLanguage[language][106], 298, 2); break;
            case FM_BAND_FM: FullLineSprite.drawString(myLanguage[language][105], 298, 2); break;
            case FM_BAND_NONE: FullLineSprite.drawString(myLanguage[language][83], 298, 2); break;
          }
          break;

        case AUDIOSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][199]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          if (fmdeemphasis != DEEMPHASIS_NONE) FullLineSprite.drawString(String((fmdeemphasis == DEEMPHASIS_50 ? FM_DEEMPHASIS_50 : FM_DEEMPHASIS_75), DEC), 258, 2);
          if (fmdeemphasis != DEEMPHASIS_NONE) FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(((fmdeemphasis != DEEMPHASIS_NONE) != 0 ? "μs" : myLanguage[language][30]), 298, 2);
          break;

        case DISPLAYSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][98]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(unitString[unit], 298, 2);
          break;

        case RDSSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][176]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((radio.rds.rtbuffer ? myLanguage[language][42] : myLanguage[language][30]), 298, 2);
          break;

        case FMSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][65]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          if (fmnb != 0) FullLineSprite.drawString(String(fmnb, DEC), 258, 2);
          if (fmnb != 0) FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString((fmnb != 0 ? "%" : myLanguage[language][30]), 298, 2);
          break;

        case AMSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][36]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          if (amgain != 0) FullLineSprite.drawString(String(amgain, DEC), 258, 2);
          if (amgain != 0) FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString((amgain != 0 ? "dB" : myLanguage[language][30]), 298, 2);
          break;

        case DXMODE:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][222]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((scanmute ? myLanguage[language][42] : myLanguage[language][30]), 298, 2);
          break;

        case AUTOMEM:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][278]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);

          switch (memdoublepi) {
            case MEMPI_OFF: FullLineSprite.drawString(myLanguage[language][30], 298, 2); break;
            case MEMPI_RANGE: FullLineSprite.drawString(myLanguage[language][279], 298, 2); break;
            default: FullLineSprite.drawString(myLanguage[language][280], 298, 2); break;
          }
          break;
      }
      break;

    case 7:
      switch (menupage) {
        case INDEX:
          FullLineSprite.setTextDatum(TC_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][213]), 152, 2);
          break;

        case MAINSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][101]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
#ifdef HAS_AIR_BAND
          switch (bandAM) {
            case AM_BAND_ALL: FullLineSprite.drawString(myLanguage[language][102] + String(",") + myLanguage[language][103] + String(",") + myLanguage[language][104] + String(",") + myLanguage[language][223], 298, 2); break;
            case AM_BAND_LW_MW_SW: FullLineSprite.drawString(myLanguage[language][102] + String(",") + myLanguage[language][103] + String(",") + myLanguage[language][104], 298, 2); break;
            case AM_BAND_LW_MW_AIR: FullLineSprite.drawString(myLanguage[language][102] + String(",") + myLanguage[language][103] + String(",") + myLanguage[language][223], 298, 2); break;
            case AM_BAND_LW_SW_AIR: FullLineSprite.drawString(myLanguage[language][102] + String(",") + myLanguage[language][104] + String(",") + myLanguage[language][223], 298, 2); break;
            case AM_BAND_MW_SW_AIR: FullLineSprite.drawString(myLanguage[language][103] + String(",") + myLanguage[language][104] + String(",") + myLanguage[language][223], 298, 2); break;
            case AM_BAND_LW_MW: FullLineSprite.drawString(myLanguage[language][102] + String(",") + myLanguage[language][103], 298, 2); break;
            case AM_BAND_LW_SW: FullLineSprite.drawString(myLanguage[language][102] + String(",") + myLanguage[language][104], 298, 2); break;
            case AM_BAND_LW_AIR: FullLineSprite.drawString(myLanguage[language][102] + String(",") + myLanguage[language][223], 298, 2); break;
            case AM_BAND_MW_SW: FullLineSprite.drawString(myLanguage[language][103] + String(",") + myLanguage[language][104], 298, 2); break;
            case AM_BAND_MW_AIR: FullLineSprite.drawString(myLanguage[language][103] + String(",") + myLanguage[language][223], 298, 2); break;
            case AM_BAND_SW_AIR: FullLineSprite.drawString(myLanguage[language][104] + String(",") + myLanguage[language][223], 298, 2); break;
            case AM_BAND_LW: FullLineSprite.drawString(myLanguage[language][102], 298, 2); break;
            case AM_BAND_MW: FullLineSprite.drawString(myLanguage[language][103], 298, 2); break;
            case AM_BAND_SW: FullLineSprite.drawString(myLanguage[language][104], 298, 2); break;
            case AM_BAND_AIR: FullLineSprite.drawString(myLanguage[language][223], 298, 2); break;
            case AM_BAND_NONE: FullLineSprite.drawString(myLanguage[language][83], 298, 2); break;
          }
          break;
#else
          switch (bandAM) {
            case AM_BAND_ALL: FullLineSprite.drawString(myLanguage[language][102] + String(",") + myLanguage[language][103] + String(",") + myLanguage[language][104], 298, 2); break;
            case AM_BAND_LW_MW: FullLineSprite.drawString(myLanguage[language][102] + String(",") + myLanguage[language][103], 298, 2); break;
            case AM_BAND_LW_SW: FullLineSprite.drawString(myLanguage[language][102] + String(",") + myLanguage[language][104], 298, 2); break;
            case AM_BAND_MW_SW: FullLineSprite.drawString(myLanguage[language][103] + String(",") + myLanguage[language][104], 298, 2); break;
            case AM_BAND_LW: FullLineSprite.drawString(myLanguage[language][102], 298, 2); break;
            case AM_BAND_MW: FullLineSprite.drawString(myLanguage[language][103], 298, 2); break;
            case AM_BAND_SW: FullLineSprite.drawString(myLanguage[language][104], 298, 2); break;
            case AM_BAND_NONE: FullLineSprite.drawString(myLanguage[language][83], 298, 2); break;
          }
          break;
#endif

        case DISPLAYSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][262]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((showclock ? myLanguage[language][42] : myLanguage[language][30]), 298, 2);
          break;

        case RDSSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][215]), 6, 2);
          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((radio.rds.sortaf ? myLanguage[language][42] : myLanguage[language][30]), 298, 2);
          break;

        case FMSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][90]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString("kHz", 298, 2);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);

          switch (fmdefaultstepsize) {
            case 0: FullLineSprite.drawString(String(FREQ_FM_STEP_50K * 10, DEC), 258, 2); break;
            case 1: FullLineSprite.drawString(String(FREQ_FM_STEP_100K * 10, DEC), 258, 2); break;
            case 2: FullLineSprite.drawString(String(FREQ_FM_STEP_200K * 10, DEC), 258, 2); break;
          }
          break;

        case AMSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][169]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((mwstepsize ? "10" : "9"), 258, 2);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString("kHz", 298, 2);
          break;

        case DXMODE:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][82]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(String(fmscansens), 298, 2);
          break;

        case AUTOMEM:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][82]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(String(fmscansens), 298, 2);
          break;
      }
      break;

    case 8:
      switch (menupage) {
        case INDEX:
          FullLineSprite.setTextDatum(TC_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][270]), 152, 2);
          break;

        case MAINSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][224]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          switch (longbandpress) {
            case STANDBY: FullLineSprite.drawString(myLanguage[language][225], 298, 2); break;
            case SCREENOFF: FullLineSprite.drawString(myLanguage[language][226], 298, 2); break;
            default: FullLineSprite.drawString(myLanguage[language][227], 298, 2); break;
          }
          break;

        case DISPLAYSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][77]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(Theme[CurrentTheme], 298, 2);
          break;

        case RDSSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][203]), 6, 2);
          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);

          switch (radio.rds.fastps) {
            case 0: FullLineSprite.drawString(myLanguage[language][30], 298, 2); break;
            case 1: FullLineSprite.drawString(myLanguage[language][260], 298, 2); break;
            case 2: FullLineSprite.drawString(myLanguage[language][261], 298, 2); break;
          }
          break;

        case FMSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][206]), 6, 2);
          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((fmsi ? myLanguage[language][42] : myLanguage[language][30]), 298, 2);
          break;

        case AMSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][82]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(String(amscansens), 298, 2);
          break;

        case DXMODE:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][281]), 6, 2);
          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((scanholdonsignal ? myLanguage[language][42] : myLanguage[language][30]), 298, 2);
          break;

        case AUTOMEM:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][276]), 6, 2);
          break;
      }
      break;

    case 9:
      switch (menupage) {
        case INDEX:
          FullLineSprite.setTextDatum(TC_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][70]), 152, 2);
          break;

        case MAINSETTINGS:
          if (dynamicspi) {
            FullLineSprite.setTextDatum(TL_DATUM);
            FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            FullLineSprite.drawString(removeNewline(myLanguage[language][81]), 6, 2);

            FullLineSprite.setTextDatum(TR_DATUM);

            if (spispeed == 7) {
              FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
              FullLineSprite.drawString(myLanguage[language][86], 298, 2);
            } else {
              FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
              FullLineSprite.drawString("MHz", 298, 2);
              FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
              FullLineSprite.drawString((spispeed == SPI_SPEED_DEFAULT ? String(myLanguage[language][204]) + " " + String(SPI_FREQUENCY / 1000000, DEC) : String(spispeed * 10, DEC)), 258, 2);
            }
          }
          break;

        case DISPLAYSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][85]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(FreqFont[freqfont], 298, 2);
          break;

        case RDSSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][263]), 6, 2);
          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((showlongps ? myLanguage[language][42] : myLanguage[language][30]), 298, 2);
          break;

        case FMSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(myLanguage[language][82]), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(String(fmscansens), 298, 2);
          break;
      }
      break;
  }
  FullLineSprite.pushSprite(8, 2 + position);
}

void BuildBWSelector() {
  switch (CurrentTheme) {
    case 7: tft.pushImage (0, 0, 320, 240, configurationbackground_wo); break;
    default: tft.pushImage (0, 0, 320, 240, configurationbackground); break;
  }
  tftPrint(0, myLanguage[language][285], 160, 6, PrimaryColor, PrimaryColorSmooth, 16);

  if (band < BAND_GAP) {
    for (int x = 0; x < 16; x++) {
      drawButton(BWButtonLabelsFM[x], x, (BWset == x + 1 ? true : false));
    }
    drawButton(BWButtonLabelsFM[16], 16, (BWset == 0 ? true : false));
    if (hardwaremodel == PORTABLE_TOUCH_ILI9341) drawButton("OK", 19, false);
  } else {
    for (int x = 0; x < 4; x++) {
      drawButton(BWButtonLabelsAM[x], x, (BWset == x + 1 ? true : false));
    }
    if (hardwaremodel == PORTABLE_TOUCH_ILI9341) drawButton("OK", 19, false);
  }
}

void BuildMenu() {
  advancedRDS = false;
  BWtune = false;

  switch (CurrentTheme) {
    case 7: tft.pushImage (0, 0, 320, 240, configurationbackground_wo); break;
    default: tft.pushImage (0, 0, 320, 240, configurationbackground); break;
  }

  if (!submenu) {
    tftPrint(0, myLanguage[language][41], 160, 6, PrimaryColor, PrimaryColorSmooth, 16);
  } else {
    tftPrint(-1, myLanguage[language][184], 8, 6, PrimaryColor, PrimaryColorSmooth, 16);
    tftPrint(1, myLanguage[language][189 + menupage - 1], 312, 6, ActiveColor, ActiveColorSmooth, 16);
  }

  ShowOneLine(ITEM1, 0, (menuoption == ITEM1 ? true : false));
  ShowOneLine(ITEM2, 1, (menuoption == ITEM2 ? true : false));
  ShowOneLine(ITEM3, 2, (menuoption == ITEM3 ? true : false));
  ShowOneLine(ITEM4, 3, (menuoption == ITEM4 ? true : false));
  ShowOneLine(ITEM5, 4, (menuoption == ITEM5 ? true : false));
  ShowOneLine(ITEM6, 5, (menuoption == ITEM6 ? true : false));
  ShowOneLine(ITEM7, 6, (menuoption == ITEM7 ? true : false));
  ShowOneLine(ITEM8, 7, (menuoption == ITEM8 ? true : false));
  ShowOneLine(ITEM9, 8, (menuoption == ITEM9 ? true : false));
  ShowOneLine(ITEM10, 9, (menuoption == ITEM10 ? true : false));

  analogWrite(SMETERPIN, 0);
}

void BuildAdvancedRDS() {
  afscreen = false;
  afpage = false;
  afpagenr = 1;
  advancedRDS = true;

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
    tft.drawCircle(71, 15, 10, SecondaryColor);
    tft.drawCircle(71, 15, 9, SecondaryColor);
  } else {
    tft.drawCircle(66, 15, 10, GreyoutColor);
    tft.drawCircle(66, 15, 9, GreyoutColor);
    tft.drawCircle(76, 15, 10, GreyoutColor);
    tft.drawCircle(76, 15, 9, GreyoutColor);
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
  xPos5 = 0;
}

void BuildDisplay() {
  afscreen = false;
  advancedRDS = false;
  BWtune = false;

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
  tft.drawLine(20, 114, 204, 114, Darkgrey);

  if (!showmodulation) tft.drawLine(20, 143, 204, 143, GreyoutColor); else tft.drawLine(20, 143, 204, 143, Darkgrey);
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
  if (usesquelch || autosquelch) tftPrint(-1, "SQ:", 212, 145, ActiveColor, ActiveColorSmooth, 16);
  tftPrint(1, "C/N", 270, 163, ActiveColor, ActiveColorSmooth, 16);
  tftPrint(-1, "dB", 300, 163, ActiveColor, ActiveColorSmooth, 16);

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

  tft.drawBitmap(122, 5, RDSLogo, 35, 22, GreyoutColor);
  tft.drawBitmap(92, 4, Speaker, 26, 22, GreyoutColor);

  if (!StereoToggle) {
    tft.drawCircle(71, 15, 10, SecondaryColor);
    tft.drawCircle(71, 15, 9, SecondaryColor);
  } else {
    tft.drawCircle(66, 15, 10, GreyoutColor);
    tft.drawCircle(66, 15, 9, GreyoutColor);
    tft.drawCircle(76, 15, 10, GreyoutColor);
    tft.drawCircle(76, 15, 9, GreyoutColor);
  }

  if (autosquelch) showAutoSquelch(1);

  RDSstatusold = false;
  Stereostatusold = false;
  LowLevelInit = true;
  updateBW();
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
  hasrtplusold = false;
  TAold = false;
  TPold = false;
  haseonold = false;
  MSold = 0;
  rds_clockold = "";
  strcpy(programTypePrevious, "");
  PIold = " ";
  PSold = " ";
  stationIDold = " ";
  stationStateold = " ";
  BWreset = true;
  dropout = false;
  xPos = 0;
  xPos2 = 0;
  xPos3 = 0;
  xPos4 = 0;
  xPos5 = 0;
}

void MenuUp() {
  if (!menuopen) {
    ShowOneLine(menuoption, menuitem, false);

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

    ShowOneLine(menuoption, menuitem, true);
  } else {
    switch (CurrentTheme) {
      case 7: OneBigLineSprite.pushImage(-11, -88, 292, 170, popupbackground_wo); break;
      default: OneBigLineSprite.pushImage(-11, -88, 292, 170, popupbackground); break;
    }

    OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
    OneBigLineSprite.setTextDatum(TC_DATUM);

    switch (menupage) {
      case MAINSETTINGS:
        switch (menuoption) {
          case ITEM1:
            hardwaremodel++;
            if (hardwaremodel > RADIO_HARDWARE_CNT - 1) hardwaremodel = 0;

            switch (hardwaremodel) {
              case BASE_ILI9341: OneBigLineSprite.drawString(myLanguage[language][109], 135, 0); break;
              case PORTABLE_ILI9341: OneBigLineSprite.drawString(myLanguage[language][110], 135, 0); break;
              case PORTABLE_TOUCH_ILI9341: OneBigLineSprite.drawString(myLanguage[language][111], 135, 0); break;
            }

            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM2:
            if (touchrotating) touchrotating = 0; else touchrotating = 1;
            OneBigLineSprite.drawString((touchrotating ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM3:
            switch (tot) {
              case 0: tot = 15; break;
              case 15: tot = 30; break;
              case 30: tot = 60; break;
              case 60: tot = 90; break;
              default: tot = 0; break;
            }

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);

            if (tot != 0) {
              OneBigLineSprite.drawString(myLanguage[language][80], 150, 0);
              OneBigLineSprite.setTextDatum(TR_DATUM);
              OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
              OneBigLineSprite.drawString(String(tot), 135, 0);
            } else {
              OneBigLineSprite.setTextDatum(TC_DATUM);
              OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
              OneBigLineSprite.drawString(myLanguage[language][30], 135, 0);
            }

            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM4:
            if (autosquelch && !usesquelch) {
              usesquelch = true;
              autosquelch = false;
            } else if (usesquelch && !autosquelch) {
              usesquelch = false;
              autosquelch = false;
            } else {
              usesquelch = false;
              autosquelch = true;
            }

            if (autosquelch) OneBigLineSprite.drawString(myLanguage[language][86], 135, 0); else OneBigLineSprite.drawString((usesquelch ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM5:
            fmagc++;
            if (fmagc > 92) fmagc = 84;
            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("dBµV", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(fmagc), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            radio.setAGC(fmagc);
            break;

          case ITEM6:
            amagc++;
            if (amagc > 102) amagc = 94;
            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("dBµV", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(amagc), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            radio.setAMAGC(amagc);
            break;

          case ITEM7:
            bandFM++;
            if (bandFM > FM_BAND_CNT - 1) bandFM = FM_BAND_ALL;

            switch (bandFM) {
              case FM_BAND_ALL: OneBigLineSprite.drawString(myLanguage[language][105] + String(",") + myLanguage[language][106], 135, 0); break;
              case FM_BAND_OIRT: OneBigLineSprite.drawString(myLanguage[language][106], 135, 0); break;
              case FM_BAND_FM: OneBigLineSprite.drawString(myLanguage[language][105], 135, 0); break;
              case FM_BAND_NONE: OneBigLineSprite.drawString(myLanguage[language][83], 135, 0); break;
            }
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM8:
            bandAM++;
            if (bandAM > AM_BAND_CNT - 1) bandAM = AM_BAND_ALL;
#ifdef HAS_AIR_BAND
            switch (bandAM) {
              case AM_BAND_ALL: OneBigLineSprite.drawString(myLanguage[language][102] + String(",") + myLanguage[language][103] + String(",") + myLanguage[language][104] + String(",") + myLanguage[language][223], 135, 0); break;
              case AM_BAND_LW_MW_SW: OneBigLineSprite.drawString(myLanguage[language][102] + String(",") + myLanguage[language][103] + String(",") + myLanguage[language][104], 135, 0); break;
              case AM_BAND_LW_MW_AIR: OneBigLineSprite.drawString(myLanguage[language][102] + String(",") + myLanguage[language][103] + String(",") + myLanguage[language][223], 135, 0); break;
              case AM_BAND_LW_SW_AIR: OneBigLineSprite.drawString(myLanguage[language][102] + String(",") + myLanguage[language][104] + String(",") + myLanguage[language][223], 135, 0); break;
              case AM_BAND_MW_SW_AIR: OneBigLineSprite.drawString(myLanguage[language][103] + String(",") + myLanguage[language][104] + String(",") + myLanguage[language][223], 135, 0); break;
              case AM_BAND_LW_MW: OneBigLineSprite.drawString(myLanguage[language][102] + String(",") + myLanguage[language][103], 135, 0); break;
              case AM_BAND_LW_SW: OneBigLineSprite.drawString(myLanguage[language][102] + String(",") + myLanguage[language][104], 135, 0); break;
              case AM_BAND_LW_AIR: OneBigLineSprite.drawString(myLanguage[language][102] + String(",") + myLanguage[language][223], 135, 0); break;
              case AM_BAND_MW_SW: OneBigLineSprite.drawString(myLanguage[language][103] + String(",") + myLanguage[language][104], 135, 0); break;
              case AM_BAND_MW_AIR: OneBigLineSprite.drawString(myLanguage[language][103] + String(",") + myLanguage[language][223], 135, 0); break;
              case AM_BAND_SW_AIR: OneBigLineSprite.drawString(myLanguage[language][104] + String(",") + myLanguage[language][223], 135, 0); break;
              case AM_BAND_LW: OneBigLineSprite.drawString(myLanguage[language][102], 135, 0); break;
              case AM_BAND_MW: OneBigLineSprite.drawString(myLanguage[language][103], 135, 0); break;
              case AM_BAND_SW: OneBigLineSprite.drawString(myLanguage[language][104], 135, 0); break;
              case AM_BAND_AIR: OneBigLineSprite.drawString(myLanguage[language][223], 135, 0); break;
              case AM_BAND_NONE: OneBigLineSprite.drawString(myLanguage[language][83], 135, 0); break;
            }
#else
            switch (bandAM) {
              case AM_BAND_ALL: OneBigLineSprite.drawString(myLanguage[language][102] + String(",") + myLanguage[language][103] + String(",") + myLanguage[language][104], 135, 0); break;
              case AM_BAND_LW_MW: OneBigLineSprite.drawString(myLanguage[language][102] + String(",") + myLanguage[language][103], 135, 0); break;
              case AM_BAND_LW_SW: OneBigLineSprite.drawString(myLanguage[language][102] + String(",") + myLanguage[language][104], 135, 0); break;
              case AM_BAND_MW_SW: OneBigLineSprite.drawString(myLanguage[language][103] + String(",") + myLanguage[language][104], 135, 0); break;
              case AM_BAND_LW: OneBigLineSprite.drawString(myLanguage[language][102], 135, 0); break;
              case AM_BAND_MW: OneBigLineSprite.drawString(myLanguage[language][103], 135, 0); break;
              case AM_BAND_SW: OneBigLineSprite.drawString(myLanguage[language][104], 135, 0); break;
              case AM_BAND_NONE: OneBigLineSprite.drawString(myLanguage[language][83], 135, 0); break;
            }
#endif
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM9:
            longbandpress++;
            if (longbandpress > 2) longbandpress = 0;

            switch (longbandpress) {
              case STANDBY: OneBigLineSprite.drawString(myLanguage[language][225], 135, 0); break;
              case SCREENOFF: OneBigLineSprite.drawString(myLanguage[language][226], 135, 0); break;
              default: OneBigLineSprite.drawString(myLanguage[language][227], 135, 0); break;
            }
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM10:
            spispeed++;
            if (spispeed > SPI_SPEED_COUNT - 1) spispeed = 0;

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            if (spispeed != 7) {
              OneBigLineSprite.drawString("MHz", 175, 0);
              OneBigLineSprite.setTextDatum(TR_DATUM);
            } else {
              OneBigLineSprite.setTextDatum(TC_DATUM);
            }

            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            if (spispeed == 7) {
              OneBigLineSprite.drawString(myLanguage[language][86], 135, 0);
            } else {
              OneBigLineSprite.drawString((spispeed == SPI_SPEED_DEFAULT ? String(myLanguage[language][204]) + " " + String(SPI_FREQUENCY / 1000000, DEC) : String(spispeed * 10, DEC)), 160, 0);
            }
            OneBigLineSprite.pushSprite(24, 118);

            if (spispeed == SPI_SPEED_DEFAULT) {
              tft.setSPISpeed(SPI_FREQUENCY / 1000000);
            } else if (spispeed == 7) {
              setAutoSpeedSPI();
            } else {
              tft.setSPISpeed(spispeed * 10);
            }
            break;
        }
        break;

      case AUDIOSETTINGS:
        switch (menuoption) {
          case ITEM1:
            VolSet++;
            if (VolSet > 10) VolSet = 10;
            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("dB", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((VolSet > 0 ? "+" : "") + String(VolSet, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            radio.setVolume(VolSet);
            break;

          case ITEM2:
            edgebeep = !edgebeep;
            OneBigLineSprite.drawString((edgebeep ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM3:
            audiomode = !audiomode;

            OneBigLineSprite.drawString((audiomode ? "MPX" : "Stereo"), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            radio.setAudio(audiomode);
            break;

          case ITEM4:
            StereoLevel ++;
            if (StereoLevel > 60 || StereoLevel <= 30) {
              if (StereoLevel == 1) StereoLevel = 30; else StereoLevel = 0;
            }

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            if (StereoLevel != 0) OneBigLineSprite.drawString("dBµV", 155, 0);
            if (StereoLevel != 0) OneBigLineSprite.setTextDatum(TR_DATUM); else OneBigLineSprite.setTextDatum(TC_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((StereoLevel != 0 ? String(StereoLevel, DEC) : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            radio.setStereoLevel(StereoLevel);
            break;

          case ITEM5:
            tftPrint(1, String(HighCutLevel * 100, DEC), 155, 118, BackgroundColor, BackgroundColor, 28);

            HighCutLevel ++;
            if (HighCutLevel > 70) HighCutLevel = 15;

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("Hz", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(HighCutLevel * 100, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            radio.setHighCutLevel(HighCutLevel);
            break;

          case ITEM6:
            HighCutOffset ++;

            if (HighCutOffset > 60 || HighCutOffset <= 20) {
              if (HighCutOffset == 1) HighCutOffset = 20; else HighCutOffset = 0;
            }

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            if (HighCutOffset != 0) OneBigLineSprite.drawString("dBµV", 155, 0);
            if (HighCutOffset != 0) OneBigLineSprite.setTextDatum(TR_DATUM); else OneBigLineSprite.setTextDatum(TC_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((HighCutOffset != 0 ? String(HighCutOffset, DEC) : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            radio.setHighCutOffset(HighCutOffset);
            break;

          case ITEM7:
            fmdeemphasis++;
            if (fmdeemphasis > DEEMPHASIS_COUNT - 1) fmdeemphasis = DEEMPHASIS_NONE;

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            if (fmdeemphasis != DEEMPHASIS_NONE) OneBigLineSprite.drawString("μs", 155, 0);
            if (fmdeemphasis != DEEMPHASIS_NONE) OneBigLineSprite.setTextDatum(TR_DATUM); else OneBigLineSprite.setTextDatum(TC_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((fmdeemphasis != DEEMPHASIS_NONE ? (fmdeemphasis == DEEMPHASIS_50 ? String(FM_DEEMPHASIS_50, DEC) : String(FM_DEEMPHASIS_75, DEC)) : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            radio.setDeemphasis(fmdeemphasis);
            break;
        }
        break;

      case DISPLAYSETTINGS:
        switch (menuoption) {
          case ITEM1:
            language ++;
            if (language == (sizeof (myLanguage) / sizeof (myLanguage[0]))) language = 0;
            UpdateFonts(0);
            OneBigLineSprite.drawString(myLanguage[language][0], 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM2:
            ContrastSet ++;
            if (ContrastSet > 100) ContrastSet = 1;

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("%", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(ContrastSet, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            analogWrite(CONTRASTPIN, map(ContrastSet, 0, 100, 15, 255));
            break;

          case ITEM3:
            showmodulation = !showmodulation;

            OneBigLineSprite.drawString((showmodulation ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM4:
            screensaverset ++;
            if (screensaverset > sizeof(screensaverOptions) / sizeof(screensaverOptions[0]) - 1) screensaverset = 0;
            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            if (screensaverset) OneBigLineSprite.drawString(myLanguage[language][92], 155, 0);
            if (screensaverset) OneBigLineSprite.setTextDatum(TR_DATUM); else OneBigLineSprite.setTextDatum(TC_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((screensaverset ? String(screensaverOptions[screensaverset], DEC) : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM5:
            poweroptions++;
            if (poweroptions > RADIO_POWER_MODE_CNT - 1) poweroptions = 0;

            switch (poweroptions) {
              case LCD_OFF: OneBigLineSprite.drawString(myLanguage[language][76], 135, 0); break;
              case LCD_BRIGHTNESS_1_PERCENT: OneBigLineSprite.drawString(myLanguage[language][94], 135, 0); break;
              case LCD_BRIGHTNESS_A_QUARTER: OneBigLineSprite.drawString(myLanguage[language][95], 135, 0); break;
              case LCD_BRIGHTNESS_HALF: OneBigLineSprite.drawString(myLanguage[language][96], 135, 0); break;
            }

            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM6:
            batteryoptions++;
            if (batteryoptions > RADIO_BATTERY_CNT - 1) batteryoptions = 0;

            switch (batteryoptions) {
              case BATTERY_NONE: OneBigLineSprite.drawString(myLanguage[language][30], 135, 0); break;
              case BATTERY_VALUE: OneBigLineSprite.drawString(myLanguage[language][174], 135, 0); break;
              case BATTERY_PERCENT: OneBigLineSprite.drawString(myLanguage[language][175], 135, 0); break;
            }

            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM7:
            unit ++;
            if (unit > sizeof(unitString) / sizeof(unitString[0]) - 1) unit = 0;

            OneBigLineSprite.drawString(unitString[unit], 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM8:
            showclock = !showclock;

            OneBigLineSprite.drawString((showclock ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM9:
            CurrentTheme ++;
            if (CurrentTheme > sizeof(Theme) / sizeof(Theme[0]) - 1) CurrentTheme = 0;
            doTheme();
            OneBigLineSprite.fillSprite(BackgroundColor);
            tft.drawRoundRect(10, 30, 300, 170, 5, ActiveColor);
            tft.fillRoundRect(12, 32, 296, 166, 5, BackgroundColor);
            Infoboxprint(myLanguage[language][77]);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(Theme[CurrentTheme], 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            showMenuOpenTouchButtons();
            break;

          case ITEM10:
            freqfont ++;
            if (freqfont > sizeof(FreqFont) / sizeof(FreqFont[0]) - 1) freqfont = 0;

            OneBigLineSprite.drawString(FreqFont[freqfont], 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;
        }
        break;

      case RDSSETTINGS:
        switch (menuoption) {
          case ITEM1:
            showrdserrors++;
            if (showrdserrors > 2) showrdserrors = 0;

            switch (showrdserrors) {
              case 0: OneBigLineSprite.drawString(myLanguage[language][30], 135, 0); break;
              case 1: OneBigLineSprite.drawString(myLanguage[language][200], 135, 0); break;
              case 2: OneBigLineSprite.drawString(myLanguage[language][201], 135, 0); break;
            }
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM2:
            if (region == REGION_EU) region = REGION_US; else region = REGION_EU;
            if (region == REGION_EU) OneBigLineSprite.drawString(myLanguage[language][47], 135, 0);
            if (region == REGION_US) OneBigLineSprite.drawString(myLanguage[language][48], 135, 0);

            OneBigLineSprite.pushSprite(24, 118);
            radio.rds.region = region;
            break;

          case ITEM3:
            radio.underscore = !radio.underscore;

            OneBigLineSprite.drawString((radio.underscore ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM4:
            radio.rds.filter = !radio.rds.filter;

            OneBigLineSprite.drawString((radio.rds.filter ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM5:
            radio.rds.pierrors = !radio.rds.pierrors;

            OneBigLineSprite.drawString((radio.rds.pierrors ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM6:
            af++;
            if (af > 2) af = 0;

            switch (af) {
              case 0: OneBigLineSprite.drawString(myLanguage[language][30], 135, 0); break;
              case 1: OneBigLineSprite.drawString(String(myLanguage[language][42]) + " / REG " + String(myLanguage[language][42]), 135, 0); break;
              case 2: OneBigLineSprite.drawString(String(myLanguage[language][42]) + " / REG " + String(myLanguage[language][30]), 135, 0); break;
            }

            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM7:
            radio.rds.rtbuffer = !radio.rds.rtbuffer;

            OneBigLineSprite.drawString((radio.rds.rtbuffer ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM8:
            radio.rds.sortaf = !radio.rds.sortaf;

            OneBigLineSprite.drawString((radio.rds.sortaf ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM9:
            radio.rds.fastps++;
            if (radio.rds.fastps > 2) radio.rds.fastps = 0;

            switch (radio.rds.fastps) {
              case 0: OneBigLineSprite.drawString(myLanguage[language][30], 135, 0); break;
              case 1: OneBigLineSprite.drawString(myLanguage[language][260], 135, 0); break;
              case 2: OneBigLineSprite.drawString(myLanguage[language][261], 135, 0); break;
            }

            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM10:
            showlongps = !showlongps;

            OneBigLineSprite.drawString((showlongps ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;
        }
        break;

      case FMSETTINGS:
        switch (menuoption) {
          case ITEM1:
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

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("MHz", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(ConverterSet, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM2:
            LowEdgeSet ++;
            if (LowEdgeSet > 1070) (TEF == 205 ? LowEdgeSet = 640 : LowEdgeSet = 650);

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("MHz", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(LowEdgeSet / 10 + ConverterSet, DEC) + "." + String(LowEdgeSet % 10 + ConverterSet, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM3:
            HighEdgeSet ++;
            if (HighEdgeSet > 1080) HighEdgeSet = 660;

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("MHz", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(HighEdgeSet / 10 + ConverterSet, DEC) + "." + String(HighEdgeSet % 10 + ConverterSet, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM4:
            LevelOffset++;
            if (LevelOffset > 15) LevelOffset = -25;

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("dBμV", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((LevelOffset > 0 ? "+" : "") + String(LevelOffset, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            radio.setOffset(LevelOffset);
            change = true;
            break;

          case ITEM5:
            LowLevelSet++;
            if (LowLevelSet > 30) LowLevelSet = -15;

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("dBμV", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(LowLevelSet, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM6:
            softmutefm = !softmutefm;

            OneBigLineSprite.drawString((softmutefm ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            radio.setSoftmuteFM(softmutefm);
            break;

          case ITEM7:
            fmnb ++;
            if (fmnb > 150 || fmnb <= 50) {
              if (fmnb == 1) fmnb = 50; else fmnb = 0;
            }

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            if (fmnb != 0) OneBigLineSprite.drawString("%", 155, 0);
            if (fmnb != 0) OneBigLineSprite.setTextDatum(TR_DATUM); else OneBigLineSprite.setTextDatum(TC_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((fmnb != 0 ? String(fmnb, DEC) : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            radio.setFMNoiseBlanker(fmnb);
            break;

          case ITEM8:
            fmdefaultstepsize++;
            if (fmdefaultstepsize > 2) fmdefaultstepsize = 0;

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("kHz", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);

            switch (fmdefaultstepsize) {
              case 0: OneBigLineSprite.drawString(String(FREQ_FM_STEP_50K * 10, DEC), 135, 0); break;
              case 1: OneBigLineSprite.drawString(String(FREQ_FM_STEP_100K * 10, DEC), 135, 0); break;
              case 2: OneBigLineSprite.drawString(String(FREQ_FM_STEP_200K * 10, DEC), 135, 0); break;
            }
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM9:
            if (fullsearchrds) {
              fmsi = !fmsi;
              OneBigLineSprite.drawString((fmsi ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
              OneBigLineSprite.pushSprite(24, 118);
              if (fmsi) radio.setFMSI(2); else radio.setFMSI(1);
            }
            break;

          case ITEM10:
            fmscansens++;
            if (fmscansens > 30) fmscansens = 1;

            OneBigLineSprite.drawString(String(fmscansens), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;
        }
        break;

      case AMSETTINGS:
        switch (menuoption) {
          case ITEM1:
            softmuteam = !softmuteam;

            OneBigLineSprite.drawString((softmuteam ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            radio.setSoftmuteAM(softmuteam);
            break;

          case ITEM2:
            amnb ++;
            if (amnb > 150 || amnb <= 50) {
              if (amnb == 1) amnb = 50; else amnb = 0;
            }

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            if (amnb != 0) OneBigLineSprite.drawString("%", 155, 0);
            if (amnb != 0) OneBigLineSprite.setTextDatum(TR_DATUM); else OneBigLineSprite.setTextDatum(TC_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((amnb != 0 ? String(amnb, DEC) : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            radio.setAMNoiseBlanker(amnb);
            break;

          case ITEM3:
            AMLevelOffset++;
            if (AMLevelOffset > 15) AMLevelOffset = -50;

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("dB", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((AMLevelOffset > 0 ? "+" : "") + String(AMLevelOffset, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            radio.setAMOffset(AMLevelOffset);
            break;

          case ITEM4:
            showSWMIBand = !showSWMIBand;

            OneBigLineSprite.drawString((showSWMIBand ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM5:
            amcodect++;
            if (amcodect > 150 || amcodect <= 50) {
              if (amcodect == 1) amcodect = 50; else amcodect = 0;
            }

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            if (amcodect != 0) OneBigLineSprite.drawString("%", 155, 0);
            if (amcodect != 0) OneBigLineSprite.setTextDatum(TR_DATUM); else OneBigLineSprite.setTextDatum(TC_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((amcodect != 0 ? String(amcodect, DEC) : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            if (band > BAND_GAP) radio.setAMCoChannel(amcodect, amcodectcount);
            break;

          case ITEM6:
            amcodectcount++;
            if (amcodectcount > 15) amcodectcount = 1;

            OneBigLineSprite.drawString(String(amcodectcount, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            if (band > BAND_GAP) radio.setAMCoChannel(amcodect, amcodectcount);
            break;

          case ITEM7:
            amgain += 6;
            if (amgain > 36) amgain = 0;

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            if (amgain != 0) OneBigLineSprite.drawString("dB", 155, 0);
            if (amgain != 0) OneBigLineSprite.setTextDatum(TR_DATUM); else OneBigLineSprite.setTextDatum(TC_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((amgain != 0 ? String(amgain, DEC) : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            if (band > BAND_GAP) radio.setAMAttenuation(amgain);
            break;

          case ITEM8:
            mwstepsize = !mwstepsize;

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("kHz", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((mwstepsize ? "10" : "9"), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM9:
            amscansens++;
            if (amscansens > 30) amscansens = 1;

            OneBigLineSprite.drawString(String(amscansens, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;
        }
        break;

      case CONNECTIVITY:
        switch (menuoption) {
          case ITEM1:
            USBmode = !USBmode;

            OneBigLineSprite.drawString((USBmode ? "RDS Spy" : "XDRGTK"), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM2:
            wifi = !wifi;

            OneBigLineSprite.drawString((wifi ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM4:
            subnetclient ++;
            if (subnetclient > 254) subnetclient = 1;

            OneBigLineSprite.drawString(String(WiFi.localIP()[0]) + "." + String(WiFi.localIP()[1]) + "." + String(WiFi.localIP()[2]) + "." + String(subnetclient, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM5:
            stationlistid ++;
            if (stationlistid > 10) stationlistid = 1;

            OneBigLineSprite.drawString(String(stationlistid, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM6:
            XDRGTKMuteScreen = !XDRGTKMuteScreen;

            OneBigLineSprite.drawString((XDRGTKMuteScreen ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;
        }
        break;

      case DXMODE:
        switch (menuoption) {
          case ITEM2:
            scanstart++;
            if (scanstart >= scanstop) scanstart = 0;
            OneBigLineSprite.drawString(String(scanstart + 1, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM3:
            scanstop++;
            if (scanstop > EE_PRESETS_CNT - 1) scanstop = scanstart + 1;
            OneBigLineSprite.drawString(String(scanstop + 1, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM4:
            scanhold++;
            if (scanhold > 30) scanhold = 0;
            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString(myLanguage[language][92], 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((scanhold == 0 ? "0.5" : String(scanhold, DEC)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM5:
            scanmem = !scanmem;
            OneBigLineSprite.drawString((scanmem ? myLanguage[language][218] : myLanguage[language][217]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM6:
            scancancel++;
            if (scancancel > 2) scancancel = 0;
            switch (scancancel) {
              case OFF:  OneBigLineSprite.drawString(myLanguage[language][30], 135, 0); break;
              case CORRECTPI: OneBigLineSprite.drawString(myLanguage[language][220], 135, 0); break;
              case SIGNAL: OneBigLineSprite.drawString(myLanguage[language][221], 135, 0); break;
            }
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM7:
            scanmute = !scanmute;
            OneBigLineSprite.drawString((scanmute ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM8:
            fmscansens++;
            if (fmscansens > 30) fmscansens = 1;

            OneBigLineSprite.drawString(String(fmscansens), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM9:
            scanholdonsignal = !scanholdonsignal;

            OneBigLineSprite.drawString((scanholdonsignal ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;
        }
        break;

      case AUTOMEM:
        switch (menuoption) {
          case ITEM2:
            memstartfreq ++;
            if (memstartfreq > 1070) (TEF == 205 ? memstartfreq = 640 : memstartfreq = 650);

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("MHz", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(memstartfreq / 10 + ConverterSet, DEC) + "." + String(memstartfreq % 10 + ConverterSet, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM3:
            memstopfreq ++;
            if (memstopfreq > 1080) memstopfreq = 660;

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("MHz", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(memstopfreq / 10 + ConverterSet, DEC) + "." + String(memstopfreq % 10 + ConverterSet, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM4:
            memstartpos++;
            if (memstartpos >= memstoppos) memstartpos = 0;
            OneBigLineSprite.drawString(String(memstartpos + 1, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM5:
            memstoppos++;
            if (memstoppos > EE_PRESETS_CNT - 1) memstoppos = memstartpos + 1;
            OneBigLineSprite.drawString(String(memstoppos + 1, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM6:
            mempionly = !mempionly;

            OneBigLineSprite.drawString((mempionly ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM7:
            memdoublepi++;
            if (memdoublepi > 2) memdoublepi = 0;

            switch (memdoublepi) {
              case MEMPI_OFF: OneBigLineSprite.drawString(myLanguage[language][30], 135, 0); break;
              case MEMPI_RANGE: OneBigLineSprite.drawString(myLanguage[language][279], 135, 0); break;
              default: OneBigLineSprite.drawString(myLanguage[language][280], 135, 0); break;
            }
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM8:
            fmscansens++;
            if (fmscansens > 30) fmscansens = 1;

            OneBigLineSprite.drawString(String(fmscansens), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;
        }
        break;
    }
  }
}

void MenuDown() {
  if (!menuopen) {
    ShowOneLine(menuoption, menuitem, false);

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

    ShowOneLine(menuoption, menuitem, true);
  } else {
    switch (CurrentTheme) {
      case 7: OneBigLineSprite.pushImage(-11, -88, 292, 170, popupbackground_wo); break;
      default: OneBigLineSprite.pushImage(-11, -88, 292, 170, popupbackground); break;
    }

    OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
    OneBigLineSprite.setTextDatum(TC_DATUM);

    switch (menupage) {
      case MAINSETTINGS:
        switch (menuoption) {
          case ITEM1:
            hardwaremodel--;
            if (hardwaremodel > RADIO_HARDWARE_CNT - 1) hardwaremodel = RADIO_HARDWARE_CNT - 1;

            switch (hardwaremodel) {
              case BASE_ILI9341: OneBigLineSprite.drawString(myLanguage[language][109], 135, 0); break;
              case PORTABLE_ILI9341: OneBigLineSprite.drawString(myLanguage[language][110], 135, 0); break;
              case PORTABLE_TOUCH_ILI9341: OneBigLineSprite.drawString(myLanguage[language][111], 135, 0); break;
            }

            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM2:
            touchrotating = !touchrotating;

            OneBigLineSprite.drawString((touchrotating ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM3:
            switch (tot) {
              case 15: tot = 0; break;
              case 30: tot = 15; break;
              case 60: tot = 30; break;
              case 90: tot = 60; break;
              default: tot = 90; break;
            }

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);

            if (tot != 0) {
              OneBigLineSprite.drawString(myLanguage[language][80], 150, 0);
              OneBigLineSprite.setTextDatum(TR_DATUM);
              OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
              OneBigLineSprite.drawString(String(tot), 135, 0);
            } else {
              OneBigLineSprite.setTextDatum(TC_DATUM);
              OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
              OneBigLineSprite.drawString(myLanguage[language][30], 135, 0);
            }

            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM4:
            if (autosquelch && !usesquelch) {
              usesquelch = true;
              autosquelch = false;
            } else if (usesquelch && !autosquelch) {
              usesquelch = false;
              autosquelch = false;
            } else {
              usesquelch = false;
              autosquelch = true;
            }

            if (autosquelch) OneBigLineSprite.drawString(myLanguage[language][86], 135, 0); else OneBigLineSprite.drawString((usesquelch ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM5:
            fmagc--;
            if (fmagc < 84) fmagc = 92;
            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("dBµV", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(fmagc), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            radio.setAGC(fmagc);
            break;

          case ITEM6:
            amagc--;
            if (amagc < 94) amagc = 102;
            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("dBµV", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(amagc), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            radio.setAMAGC(amagc);
            break;

          case ITEM7:
            bandFM--;
            if (bandFM > FM_BAND_CNT) bandFM = FM_BAND_NONE;

            switch (bandFM) {
              case FM_BAND_ALL: OneBigLineSprite.drawString(myLanguage[language][105] + String(",") + myLanguage[language][106], 135, 0); break;
              case FM_BAND_OIRT: OneBigLineSprite.drawString(myLanguage[language][106], 135, 0); break;
              case FM_BAND_FM: OneBigLineSprite.drawString(myLanguage[language][105], 135, 0); break;
              case FM_BAND_NONE: OneBigLineSprite.drawString(myLanguage[language][83], 135, 0); break;
            }
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM8:
            bandAM--;
            if (bandAM > AM_BAND_CNT) bandAM = AM_BAND_NONE;

#ifdef HAS_AIR_BAND
            switch (bandAM) {
              case AM_BAND_ALL: OneBigLineSprite.drawString(myLanguage[language][102] + String(",") + myLanguage[language][103] + String(",") + myLanguage[language][104] + String(",") + myLanguage[language][223], 135, 0); break;
              case AM_BAND_LW_MW_SW: OneBigLineSprite.drawString(myLanguage[language][102] + String(",") + myLanguage[language][103] + String(",") + myLanguage[language][104], 135, 0); break;
              case AM_BAND_LW_MW_AIR: OneBigLineSprite.drawString(myLanguage[language][102] + String(",") + myLanguage[language][103] + String(",") + myLanguage[language][223], 135, 0); break;
              case AM_BAND_LW_SW_AIR: OneBigLineSprite.drawString(myLanguage[language][102] + String(",") + myLanguage[language][104] + String(",") + myLanguage[language][223], 135, 0); break;
              case AM_BAND_MW_SW_AIR: OneBigLineSprite.drawString(myLanguage[language][103] + String(",") + myLanguage[language][104] + String(",") + myLanguage[language][223], 135, 0); break;
              case AM_BAND_LW_MW: OneBigLineSprite.drawString(myLanguage[language][102] + String(",") + myLanguage[language][103], 135, 0); break;
              case AM_BAND_LW_SW: OneBigLineSprite.drawString(myLanguage[language][102] + String(",") + myLanguage[language][104], 135, 0); break;
              case AM_BAND_LW_AIR: OneBigLineSprite.drawString(myLanguage[language][102] + String(",") + myLanguage[language][223], 135, 0); break;
              case AM_BAND_MW_SW: OneBigLineSprite.drawString(myLanguage[language][103] + String(",") + myLanguage[language][104], 135, 0); break;
              case AM_BAND_MW_AIR: OneBigLineSprite.drawString(myLanguage[language][103] + String(",") + myLanguage[language][223], 135, 0); break;
              case AM_BAND_SW_AIR: OneBigLineSprite.drawString(myLanguage[language][104] + String(",") + myLanguage[language][223], 135, 0); break;
              case AM_BAND_LW: OneBigLineSprite.drawString(myLanguage[language][102], 135, 0); break;
              case AM_BAND_MW: OneBigLineSprite.drawString(myLanguage[language][103], 135, 0); break;
              case AM_BAND_SW: OneBigLineSprite.drawString(myLanguage[language][104], 135, 0); break;
              case AM_BAND_AIR: OneBigLineSprite.drawString(myLanguage[language][223], 135, 0); break;
              case AM_BAND_NONE: OneBigLineSprite.drawString(myLanguage[language][83], 135, 0); break;
            }
#else
            switch (bandAM) {
              case AM_BAND_ALL: OneBigLineSprite.drawString(myLanguage[language][102] + String(",") + myLanguage[language][103] + String(",") + myLanguage[language][104], 135, 0); break;
              case AM_BAND_LW_MW: OneBigLineSprite.drawString(myLanguage[language][102] + String(",") + myLanguage[language][103], 135, 0); break;
              case AM_BAND_LW_SW: OneBigLineSprite.drawString(myLanguage[language][102] + String(",") + myLanguage[language][104], 135, 0); break;
              case AM_BAND_MW_SW: OneBigLineSprite.drawString(myLanguage[language][103] + String(",") + myLanguage[language][104], 135, 0); break;
              case AM_BAND_LW: OneBigLineSprite.drawString(myLanguage[language][102], 135, 0); break;
              case AM_BAND_MW: OneBigLineSprite.drawString(myLanguage[language][103], 135, 0); break;
              case AM_BAND_SW: OneBigLineSprite.drawString(myLanguage[language][104], 135, 0); break;
              case AM_BAND_NONE: OneBigLineSprite.drawString(myLanguage[language][83], 135, 0); break;
            }
#endif

            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM9:
            longbandpress--;
            if (longbandpress > 2) longbandpress = 2;

            switch (longbandpress) {
              case STANDBY: OneBigLineSprite.drawString(myLanguage[language][225], 135, 0); break;
              case SCREENOFF: OneBigLineSprite.drawString(myLanguage[language][226], 135, 0); break;
              default: OneBigLineSprite.drawString(myLanguage[language][227], 135, 0); break;
            }
            OneBigLineSprite.pushSprite(24, 118);
            break;


          case ITEM10:
            spispeed--;
            if (spispeed > SPI_SPEED_COUNT - 1) spispeed = SPI_SPEED_COUNT - 1;
            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            if (spispeed != 7) {
              OneBigLineSprite.drawString("MHz", 175, 0);
              OneBigLineSprite.setTextDatum(TR_DATUM);
            } else {
              OneBigLineSprite.setTextDatum(TC_DATUM);
            }

            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            if (spispeed == 7) {
              OneBigLineSprite.drawString(myLanguage[language][86], 135, 0);
            } else {
              OneBigLineSprite.drawString((spispeed == SPI_SPEED_DEFAULT ? String(myLanguage[language][204]) + " " + String(SPI_FREQUENCY / 1000000, DEC) : String(spispeed * 10, DEC)), 160, 0);
            }
            OneBigLineSprite.pushSprite(24, 118);

            if (spispeed == SPI_SPEED_DEFAULT) {
              tft.setSPISpeed(SPI_FREQUENCY / 1000000);
            } else if (spispeed == 7) {
              setAutoSpeedSPI();
            } else {
              tft.setSPISpeed(spispeed * 10);
            }
            break;

        }
        break;

      case AUDIOSETTINGS:
        switch (menuoption) {
          case ITEM1:
            VolSet--;
            if (VolSet < -10) VolSet = -10;
            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("dB", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((VolSet > 0 ? "+" : "") + String(VolSet, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            radio.setVolume(VolSet);
            break;

          case ITEM2:
            edgebeep = !edgebeep;

            OneBigLineSprite.drawString((edgebeep ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM3:
            audiomode = !audiomode;

            OneBigLineSprite.drawString((audiomode ? "MPX" : "Stereo"), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            radio.setAudio(audiomode);
            break;

          case ITEM4:
            StereoLevel --;
            if (StereoLevel < 30 || StereoLevel > 60) {
              if (StereoLevel > 60) StereoLevel = 60; else StereoLevel = 0;
            }

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            if (StereoLevel != 0) OneBigLineSprite.drawString("dBµV", 155, 0);
            if (StereoLevel != 0) OneBigLineSprite.setTextDatum(TR_DATUM); else OneBigLineSprite.setTextDatum(TC_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((StereoLevel != 0 ? String(StereoLevel, DEC) : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            radio.setStereoLevel(StereoLevel);
            break;

          case ITEM5:
            HighCutLevel --;
            if (HighCutLevel < 15 || HighCutLevel > 70) HighCutLevel = 70;

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("Hz", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(HighCutLevel * 100, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            radio.setHighCutLevel(HighCutLevel);
            break;

          case ITEM6:
            HighCutOffset --;
            if (HighCutOffset < 20 || HighCutOffset > 60) {
              if (HighCutOffset > 60) HighCutOffset = 60; else HighCutOffset = 0;
            }

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            if (HighCutOffset != 0) OneBigLineSprite.drawString("dBµV", 155, 0);
            if (HighCutOffset != 0) OneBigLineSprite.setTextDatum(TR_DATUM); else OneBigLineSprite.setTextDatum(TC_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((HighCutOffset != 0 ? String(HighCutOffset, DEC) : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            radio.setHighCutOffset(HighCutOffset);
            break;

          case ITEM7:
            fmdeemphasis--;
            if (fmdeemphasis > DEEMPHASIS_COUNT - 1) fmdeemphasis = DEEMPHASIS_COUNT - 1;

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            if (fmdeemphasis != DEEMPHASIS_NONE) OneBigLineSprite.drawString("μs", 155, 0);
            if (fmdeemphasis != DEEMPHASIS_NONE) OneBigLineSprite.setTextDatum(TR_DATUM); else OneBigLineSprite.setTextDatum(TC_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((fmdeemphasis != DEEMPHASIS_NONE ? (fmdeemphasis == DEEMPHASIS_50 ? String(FM_DEEMPHASIS_50, DEC) : String(FM_DEEMPHASIS_75, DEC)) : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            radio.setDeemphasis(fmdeemphasis);
            break;
        }
        break;

      case DISPLAYSETTINGS:
        switch (menuoption) {
          case ITEM1:
            language --;
            if (language > (sizeof (myLanguage) / sizeof (myLanguage[0]))) language = (sizeof (myLanguage) / sizeof (myLanguage[0])) - 1;
            UpdateFonts(0);
            OneBigLineSprite.drawString(myLanguage[language][0], 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM2:
            ContrastSet --;
            if (ContrastSet < 1) ContrastSet = 100;

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("%", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(ContrastSet, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            analogWrite(CONTRASTPIN, map(ContrastSet, 0, 100, 15, 255));
            break;

          case ITEM3:
            showmodulation = !showmodulation;

            OneBigLineSprite.drawString((showmodulation ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM4:
            screensaverset --;
            if (screensaverset > sizeof(screensaverOptions) / sizeof(screensaverOptions[0]) - 1) screensaverset = sizeof(screensaverOptions) / sizeof(screensaverOptions[0]) - 1;

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            if (screensaverset) OneBigLineSprite.drawString(myLanguage[language][92], 155, 0);
            if (screensaverset) OneBigLineSprite.setTextDatum(TR_DATUM); else OneBigLineSprite.setTextDatum(TC_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((screensaverset ? String(screensaverOptions[screensaverset], DEC) : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM5:
            poweroptions--;
            if (poweroptions > RADIO_POWER_MODE_CNT - 1) poweroptions = RADIO_POWER_MODE_CNT - 1;

            switch (poweroptions) {
              case LCD_OFF: OneBigLineSprite.drawString(myLanguage[language][76], 135, 0); break;
              case LCD_BRIGHTNESS_1_PERCENT: OneBigLineSprite.drawString(myLanguage[language][94], 135, 0); break;
              case LCD_BRIGHTNESS_A_QUARTER: OneBigLineSprite.drawString(myLanguage[language][95], 135, 0); break;
              case LCD_BRIGHTNESS_HALF: OneBigLineSprite.drawString(myLanguage[language][96], 135, 0); break;
            }

            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM6:
            batteryoptions--;
            if (batteryoptions > RADIO_BATTERY_CNT - 1) batteryoptions = RADIO_BATTERY_CNT - 1;

            switch (batteryoptions) {
              case BATTERY_NONE: OneBigLineSprite.drawString(myLanguage[language][30], 135, 0); break;
              case BATTERY_VALUE: OneBigLineSprite.drawString(myLanguage[language][174], 135, 0); break;
              case BATTERY_PERCENT: OneBigLineSprite.drawString(myLanguage[language][175], 135, 0); break;
            }

            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM7:
            unit --;
            if (unit > sizeof(unitString) / sizeof(unitString[0]) - 1) unit = sizeof(unitString) / sizeof(unitString[0]) - 1;

            OneBigLineSprite.drawString(unitString[unit], 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM8:
            showclock = !showclock;

            OneBigLineSprite.drawString((showclock ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM9:
            CurrentTheme --;
            if (CurrentTheme > sizeof(Theme) / sizeof(Theme[0]) - 1) CurrentTheme = sizeof(Theme) / sizeof(Theme[0]) - 1;

            doTheme();
            OneBigLineSprite.fillSprite(BackgroundColor);
            tft.drawRoundRect(10, 30, 300, 170, 5, ActiveColor);
            tft.fillRoundRect(12, 32, 296, 166, 5, BackgroundColor);
            Infoboxprint(myLanguage[language][77]);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(Theme[CurrentTheme], 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            showMenuOpenTouchButtons();
            break;

          case ITEM10:
            freqfont --;
            if (freqfont > sizeof(FreqFont) / sizeof(FreqFont[0]) - 1) freqfont = sizeof(FreqFont) / sizeof(FreqFont[0]) - 1;

            OneBigLineSprite.drawString(FreqFont[freqfont], 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;
        }
        break;

      case RDSSETTINGS:
        switch (menuoption) {
          case ITEM1:
            showrdserrors--;
            if (showrdserrors > 2) showrdserrors = 2;

            switch (showrdserrors) {
              case 0: OneBigLineSprite.drawString(myLanguage[language][30], 135, 0); break;
              case 1: OneBigLineSprite.drawString(myLanguage[language][200], 135, 0); break;
              case 2: OneBigLineSprite.drawString(myLanguage[language][201], 135, 0); break;
            }
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM2:
            if (region == REGION_EU) region = REGION_US; else region = REGION_EU;
            if (region == REGION_EU) OneBigLineSprite.drawString(myLanguage[language][47], 135, 0);
            if (region == REGION_US) OneBigLineSprite.drawString(myLanguage[language][48], 135, 0);

            OneBigLineSprite.pushSprite(24, 118);
            radio.rds.region = region;
            break;

          case ITEM3:
            radio.underscore = !radio.underscore;

            OneBigLineSprite.drawString((radio.underscore ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM4:
            radio.rds.filter = !radio.rds.filter;

            OneBigLineSprite.drawString((radio.rds.filter ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM5:
            radio.rds.pierrors = !radio.rds.pierrors;

            OneBigLineSprite.drawString((radio.rds.pierrors ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM6:
            af--;
            if (af > 2) af = 2;

            switch (af) {
              case 0: OneBigLineSprite.drawString(myLanguage[language][30], 135, 0); break;
              case 1: OneBigLineSprite.drawString(String(myLanguage[language][42]) + " / REG " + String(myLanguage[language][42]), 135, 0); break;
              case 2: OneBigLineSprite.drawString(String(myLanguage[language][42]) + " / REG " + String(myLanguage[language][30]), 135, 0); break;
            }

            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM7:
            radio.rds.rtbuffer = !radio.rds.rtbuffer;

            OneBigLineSprite.drawString((radio.rds.rtbuffer ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM8:
            radio.rds.sortaf = !radio.rds.sortaf;

            OneBigLineSprite.drawString((radio.rds.sortaf ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM9:
            radio.rds.fastps--;
            if (radio.rds.fastps > 2) radio.rds.fastps = 2;

            switch (radio.rds.fastps) {
              case 0: OneBigLineSprite.drawString(myLanguage[language][30], 135, 0); break;
              case 1: OneBigLineSprite.drawString(myLanguage[language][260], 135, 0); break;
              case 2: OneBigLineSprite.drawString(myLanguage[language][261], 135, 0); break;
            }

            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM10:
            showlongps = !showlongps;

            OneBigLineSprite.drawString((showlongps ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;
        }
        break;

      case FMSETTINGS:
        switch (menuoption) {
          case ITEM1:
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

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("MHz", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(ConverterSet, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM2:
            LowEdgeSet -= 10;
            if ((TEF == 205 ? LowEdgeSet < 640 : LowEdgeSet < 650)) LowEdgeSet = 1079;

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("MHz", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(LowEdgeSet / 10 + ConverterSet, DEC) + "." + String(LowEdgeSet % 10 + ConverterSet, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM3:
            HighEdgeSet -= 10;
            if (HighEdgeSet < 660) HighEdgeSet = 1080;

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("MHz", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(HighEdgeSet / 10 + ConverterSet, DEC) + "." + String(HighEdgeSet % 10 + ConverterSet, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM4:
            LevelOffset--;
            if (LevelOffset < -25) LevelOffset = 15;

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("dBμV", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((LevelOffset > 0 ? "+" : "") + String(LevelOffset, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            radio.setOffset(LevelOffset);
            change = true;
            break;

          case ITEM5:
            LowLevelSet--;
            if (LowLevelSet < -15) LowLevelSet = 30;

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("dBμV", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(LowLevelSet, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM6:
            softmutefm = !softmutefm;

            OneBigLineSprite.drawString((softmutefm ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            radio.setSoftmuteFM(softmutefm);
            break;

          case ITEM7:
            fmnb --;
            if (fmnb > 150 || fmnb <= 50) {
              if (fmnb > 150) fmnb = 150; else fmnb = 0;
            }

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            if (fmnb != 0) OneBigLineSprite.drawString("%", 155, 0);
            if (fmnb != 0) OneBigLineSprite.setTextDatum(TR_DATUM); else OneBigLineSprite.setTextDatum(TC_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((fmnb != 0 ? String(fmnb, DEC) : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            radio.setFMNoiseBlanker(fmnb);
            break;

          case ITEM8:
            fmdefaultstepsize--;
            if (fmdefaultstepsize > 2) fmdefaultstepsize = 2;

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("kHz", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);

            switch (fmdefaultstepsize) {
              case 0: OneBigLineSprite.drawString(String(FREQ_FM_STEP_50K * 10, DEC), 135, 0); break;
              case 1: OneBigLineSprite.drawString(String(FREQ_FM_STEP_100K * 10, DEC), 135, 0); break;
              case 2: OneBigLineSprite.drawString(String(FREQ_FM_STEP_200K * 10, DEC), 135, 0); break;
            }
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM9:
            if (fullsearchrds) {
              fmsi = !fmsi;
              OneBigLineSprite.drawString((fmsi ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
              OneBigLineSprite.pushSprite(24, 118);
              if (fmsi) radio.setFMSI(2); else radio.setFMSI(1);
            }
            break;

          case ITEM10:
            fmscansens--;
            if (fmscansens == 0) fmscansens = 30;

            OneBigLineSprite.drawString(String(fmscansens), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;
        }
        break;

      case AMSETTINGS:
        switch (menuoption) {
          case ITEM1:
            softmuteam = !softmuteam;

            OneBigLineSprite.drawString((softmuteam ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            radio.setSoftmuteAM(softmuteam);
            break;

          case ITEM2:
            amnb --;
            if (amnb > 150 || amnb <= 50) {
              if (amnb > 150) amnb = 150; else amnb = 0;
            }

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            if (amnb != 0) OneBigLineSprite.drawString("%", 155, 0);
            if (amnb != 0) OneBigLineSprite.setTextDatum(TR_DATUM); else OneBigLineSprite.setTextDatum(TC_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((amnb != 0 ? String(amnb, DEC) : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            radio.setAMNoiseBlanker(amnb);
            break;

          case ITEM3:
            AMLevelOffset--;
            if (AMLevelOffset < -50) AMLevelOffset = 15;

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("dB", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((AMLevelOffset > 0 ? "+" : "") + String(AMLevelOffset, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            radio.setAMOffset(AMLevelOffset);
            break;

          case ITEM4:
            showSWMIBand = !showSWMIBand;

            OneBigLineSprite.drawString((showSWMIBand ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);

            break;

          case ITEM5:
            amcodect--;
            if (amcodect < 50 || amcodect > 150) {
              if (amcodect > 150) amcodect = 150; else amcodect = 0;
            }

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            if (amcodect != 0) OneBigLineSprite.drawString("%", 155, 0);
            if (amcodect != 0) OneBigLineSprite.setTextDatum(TR_DATUM); else OneBigLineSprite.setTextDatum(TC_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((amcodect != 0 ? String(amcodect, DEC) : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            if (band > BAND_GAP) radio.setAMCoChannel(amcodect, amcodectcount);
            break;

          case ITEM6:
            amcodectcount--;
            if (amcodectcount < 1) amcodectcount = 15;

            OneBigLineSprite.drawString(String(amcodectcount, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            if (band > BAND_GAP) radio.setAMCoChannel(amcodect, amcodectcount);
            break;

          case ITEM7:
            amgain -= 6;
            if (amgain > 36) amgain = 36;

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            if (amgain != 0) OneBigLineSprite.drawString("dB", 155, 0);
            if (amgain != 0) OneBigLineSprite.setTextDatum(TR_DATUM); else OneBigLineSprite.setTextDatum(TC_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((amgain != 0 ? String(amgain, DEC) : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            if (band > BAND_GAP) radio.setAMAttenuation(amgain);
            break;

          case ITEM8:
            mwstepsize = !mwstepsize;

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("kHz", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((mwstepsize ? "10" : "9"), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM9:
            amscansens--;
            if (amscansens == 0) amscansens = 30;

            OneBigLineSprite.drawString(String(amscansens, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;
        }
        break;

      case CONNECTIVITY:
        switch (menuoption) {
          case ITEM1:
            USBmode = !USBmode;

            OneBigLineSprite.drawString((USBmode ? "RDS Spy" : "XDRGTK"), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM2:
            wifi = !wifi;

            OneBigLineSprite.drawString((wifi ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM4:
            subnetclient --;
            if (subnetclient < 1) subnetclient = 254;

            OneBigLineSprite.drawString(String(WiFi.localIP()[0]) + "." + String(WiFi.localIP()[1]) + "." + String(WiFi.localIP()[2]) + "." + String(subnetclient, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM5:
            stationlistid --;
            if (stationlistid == 0) stationlistid = 10;

            OneBigLineSprite.drawString(String(stationlistid, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM6:
            XDRGTKMuteScreen = !XDRGTKMuteScreen;

            OneBigLineSprite.drawString((XDRGTKMuteScreen ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;
        }
        break;

      case DXMODE:
        switch (menuoption) {
          case ITEM2:
            scanstart--;
            if (scanstart >= scanstop) scanstart = scanstop - 1;
            OneBigLineSprite.drawString(String(scanstart + 1, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM3:
            scanstop--;
            if (scanstop <= scanstart) scanstop = EE_PRESETS_CNT - 1;
            OneBigLineSprite.drawString(String(scanstop + 1, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM4:
            scanhold--;
            if (scanhold > 30) scanhold = 30;
            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString(myLanguage[language][92], 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((scanhold == 0 ? "0.5" : String(scanhold, DEC)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM5:
            scanmem = !scanmem;
            OneBigLineSprite.drawString((scanmem ? myLanguage[language][218] : myLanguage[language][217]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM6:
            scancancel--;
            if (scancancel > 2) scancancel = 2;
            switch (scancancel) {
              case OFF:  OneBigLineSprite.drawString(myLanguage[language][30], 135, 0); break;
              case CORRECTPI: OneBigLineSprite.drawString(myLanguage[language][220], 135, 0); break;
              case SIGNAL: OneBigLineSprite.drawString(myLanguage[language][221], 135, 0); break;
            }
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM7:
            scanmute = !scanmute;
            OneBigLineSprite.drawString((scanmute ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM8:
            fmscansens--;
            if (fmscansens == 0) fmscansens = 30;

            OneBigLineSprite.drawString(String(fmscansens), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM9:
            scanholdonsignal = !scanholdonsignal;

            OneBigLineSprite.drawString((scanholdonsignal ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;
        }
        break;

      case AUTOMEM:
        switch (menuoption) {
          case ITEM2:
            memstartfreq -= 10;
            if ((TEF == 205 ? memstartfreq < 640 : memstartfreq < 650)) memstartfreq = 1079;

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("MHz", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(memstartfreq / 10 + ConverterSet, DEC) + "." + String(memstartfreq % 10 + ConverterSet, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM3:
            memstopfreq -= 10;
            if (memstopfreq < 660) memstopfreq = 1080;

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("MHz", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(memstopfreq / 10 + ConverterSet, DEC) + "." + String(memstopfreq % 10 + ConverterSet, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM4:
            memstartpos--;
            if (memstartpos >= memstoppos) memstartpos = scanstop - 1;
            OneBigLineSprite.drawString(String(memstartpos + 1, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM5:
            memstoppos--;
            if (memstoppos <= memstartpos) memstoppos = EE_PRESETS_CNT - 1;
            OneBigLineSprite.drawString(String(memstoppos + 1, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM6:
            mempionly = !mempionly;

            OneBigLineSprite.drawString((mempionly ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM7:
            memdoublepi--;
            if (memdoublepi > 2) memdoublepi = 2;

            switch (memdoublepi) {
              case MEMPI_OFF: OneBigLineSprite.drawString(myLanguage[language][30], 135, 0); break;
              case MEMPI_RANGE: OneBigLineSprite.drawString(myLanguage[language][279], 135, 0); break;
              default: OneBigLineSprite.drawString(myLanguage[language][280], 135, 0); break;
            }
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM8:
            fmscansens--;
            if (fmscansens == 0) fmscansens = 30;

            OneBigLineSprite.drawString(String(fmscansens), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;
        }
        break;
    }
  }
}

void showMenuOpenTouchButtons() {
  if (hardwaremodel == PORTABLE_TOUCH_ILI9341 && !((menupage == CONNECTIVITY && menuoption == ITEM3) || (menupage == AUTOMEM && (menuoption == ITEM1 || menuoption == ITEM9)) || (menupage == MAINSETTINGS && menuoption == ITEM1))) {
    tft.fillRoundRect(18, 154, 60, 40, 6, FrameColor);
    tft.drawRoundRect(18, 154, 60, 40, 6, ActiveColor);
    tft.fillRoundRect(240, 154, 60, 40, 6, FrameColor);
    tft.drawRoundRect(240, 154, 60, 40, 6, ActiveColor);
    tft.fillRoundRect(240, 36, 60, 40, 6, FrameColor);
    tft.drawRoundRect(240, 36, 60, 40, 6, ActiveColor);
    tft.fillTriangle(52, 160, 52, 188, 38, 174, ActiveColor);
    tft.fillTriangle(266, 160, 266, 188, 280, 174, ActiveColor);
    tftPrint(0, "OK", 270, 44, ActiveColor, ActiveColorSmooth, 28);
  }
}

void DoMenu() {
  if (!menuopen) {
    if (menupage != INDEX) {
      menuopen = true;
      switch (CurrentTheme) {
        case 7: tft.pushImage (13, 30, 292, 170, popupbackground_wo); break;
        default: tft.pushImage (13, 30, 292, 170, popupbackground); break;
      }
      showMenuOpenTouchButtons();
    }

    switch (CurrentTheme) {
      case 7: OneBigLineSprite.pushImage(-11, -88, 292, 170, popupbackground_wo); break;
      default: OneBigLineSprite.pushImage(-11, -88, 292, 170, popupbackground); break;
    }

    OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
    OneBigLineSprite.setTextDatum(TC_DATUM);

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
            menupage = DXMODE;
            menuoption = ITEM1;
            menuitem = 0;
            submenu = true;
            BuildMenu();
            break;

          case ITEM9:
            menupage = AUTOMEM;
            menuoption = ITEM1;
            menuitem = 0;
            submenu = true;
            BuildMenu();
            break;

          case ITEM10:
            menuopen = true;
            tft.drawRoundRect(10, 6, 300, 230, 5, ActiveColor);
            tft.fillRoundRect(12, 8, 296, 226, 5, BackgroundColor);
            tftPrint(0, myLanguage[language][71], 155, 13, ActiveColor, ActiveColorSmooth, 28);
            tftPrint(0, myLanguage[language][72], 155, 55, ActiveColor, ActiveColorSmooth, 28);
            tftPrint(0, "PE5PVB", 155, 38, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(1, "ohmytime", 145, 80, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(1, "HyperDX", 145, 95, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(-1, "MCelliotG", 155, 80, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(-1, "andimik", 155, 95, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(1, "DXHR05", 145, 110, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(1, "NoobishSVK", 145, 125, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(-1, "yo2ldk", 155, 110, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(-1, "Justin_Peng(Portable)", 155, 125, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(1, "Overland DX", 145, 140, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(-1, "elektronik232", 155, 140, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(1, "KOTYA8", 145, 155, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(-1, "mrwish7", 155, 155, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(1, "lxsxl", 145, 170, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(-1, "leryfm", 155, 170, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(1, "marsel90-1", 145, 185, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(-1, "lawendel", 155, 185, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(1, "KB8U", 145, 200, PrimaryColor, PrimaryColorSmooth, 16);
            tftPrint(0, "github.com/PE5PVB/TEF6686_ESP32", 155, 215, ActiveColor, ActiveColorSmooth, 16);
            break;
        }
        break;

      case MAINSETTINGS:
        switch (menuoption) {
          case ITEM1:
            Infoboxprint(myLanguage[language][108]);

            switch (hardwaremodel) {
              case BASE_ILI9341: OneBigLineSprite.drawString(myLanguage[language][109], 135, 0); break;
              case PORTABLE_ILI9341: OneBigLineSprite.drawString(myLanguage[language][110], 135, 0); break;
              case PORTABLE_TOUCH_ILI9341: OneBigLineSprite.drawString(myLanguage[language][111], 135, 0); break;
            }

            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM2:
            Infoboxprint(myLanguage[language][68]);

            OneBigLineSprite.drawString((touchrotating ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM3:
            Infoboxprint(myLanguage[language][75]);

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);

            if (tot != 0) {
              OneBigLineSprite.drawString(myLanguage[language][80], 150, 0);
              OneBigLineSprite.setTextDatum(TR_DATUM);
              OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
              OneBigLineSprite.drawString(String(tot), 135, 0);
            } else {
              OneBigLineSprite.setTextDatum(TC_DATUM);
              OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
              OneBigLineSprite.drawString(myLanguage[language][30], 135, 0);
            }

            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM4:
            Infoboxprint(myLanguage[language][62]);
            if (autosquelch) OneBigLineSprite.drawString(myLanguage[language][86], 135, 0); else OneBigLineSprite.drawString((usesquelch ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM5:
            Infoboxprint(myLanguage[language][37]);

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("dBµV", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(fmagc), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM6:
            Infoboxprint(myLanguage[language][198]);

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("dBµV", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(amagc), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM7:
            Infoboxprint(myLanguage[language][100]);

            switch (bandFM) {
              case FM_BAND_ALL: OneBigLineSprite.drawString(myLanguage[language][105] + String(",") + myLanguage[language][106], 135, 0); break;
              case FM_BAND_OIRT: OneBigLineSprite.drawString(myLanguage[language][106], 135, 0); break;
              case FM_BAND_FM: OneBigLineSprite.drawString(myLanguage[language][105], 135, 0); break;
              case FM_BAND_NONE: OneBigLineSprite.drawString(myLanguage[language][83], 135, 0); break;
            }
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM8:
            Infoboxprint(myLanguage[language][101]);

#ifdef HAS_AIR_BAND
            switch (bandAM) {
              case AM_BAND_ALL: OneBigLineSprite.drawString(myLanguage[language][102] + String(",") + myLanguage[language][103] + String(",") + myLanguage[language][104] + String(",") + myLanguage[language][223], 135, 0); break;
              case AM_BAND_LW_MW_SW: OneBigLineSprite.drawString(myLanguage[language][102] + String(",") + myLanguage[language][103] + String(",") + myLanguage[language][104], 135, 0); break;
              case AM_BAND_LW_MW_AIR: OneBigLineSprite.drawString(myLanguage[language][102] + String(",") + myLanguage[language][103] + String(",") + myLanguage[language][223], 135, 0); break;
              case AM_BAND_LW_SW_AIR: OneBigLineSprite.drawString(myLanguage[language][102] + String(",") + myLanguage[language][104] + String(",") + myLanguage[language][223], 135, 0); break;
              case AM_BAND_MW_SW_AIR: OneBigLineSprite.drawString(myLanguage[language][103] + String(",") + myLanguage[language][104] + String(",") + myLanguage[language][223], 135, 0); break;
              case AM_BAND_LW_MW: OneBigLineSprite.drawString(myLanguage[language][102] + String(",") + myLanguage[language][103], 135, 0); break;
              case AM_BAND_LW_SW: OneBigLineSprite.drawString(myLanguage[language][102] + String(",") + myLanguage[language][104], 135, 0); break;
              case AM_BAND_LW_AIR: OneBigLineSprite.drawString(myLanguage[language][102] + String(",") + myLanguage[language][223], 135, 0); break;
              case AM_BAND_MW_SW: OneBigLineSprite.drawString(myLanguage[language][103] + String(",") + myLanguage[language][104], 135, 0); break;
              case AM_BAND_MW_AIR: OneBigLineSprite.drawString(myLanguage[language][103] + String(",") + myLanguage[language][223], 135, 0); break;
              case AM_BAND_SW_AIR: OneBigLineSprite.drawString(myLanguage[language][104] + String(",") + myLanguage[language][223], 135, 0); break;
              case AM_BAND_LW: OneBigLineSprite.drawString(myLanguage[language][102], 135, 0); break;
              case AM_BAND_MW: OneBigLineSprite.drawString(myLanguage[language][103], 135, 0); break;
              case AM_BAND_SW: OneBigLineSprite.drawString(myLanguage[language][104], 135, 0); break;
              case AM_BAND_AIR: OneBigLineSprite.drawString(myLanguage[language][223], 135, 0); break;
              case AM_BAND_NONE: OneBigLineSprite.drawString(myLanguage[language][83], 135, 0); break;
            }
#else
            switch (bandAM) {
              case AM_BAND_ALL: OneBigLineSprite.drawString(myLanguage[language][102] + String(",") + myLanguage[language][103] + String(",") + myLanguage[language][104], 135, 0); break;
              case AM_BAND_LW_MW: OneBigLineSprite.drawString(myLanguage[language][102] + String(",") + myLanguage[language][103], 135, 0); break;
              case AM_BAND_LW_SW: OneBigLineSprite.drawString(myLanguage[language][102] + String(",") + myLanguage[language][104], 135, 0); break;
              case AM_BAND_MW_SW: OneBigLineSprite.drawString(myLanguage[language][103] + String(",") + myLanguage[language][104], 135, 0); break;
              case AM_BAND_LW: OneBigLineSprite.drawString(myLanguage[language][102], 135, 0); break;
              case AM_BAND_MW: OneBigLineSprite.drawString(myLanguage[language][103], 135, 0); break;
              case AM_BAND_SW: OneBigLineSprite.drawString(myLanguage[language][104], 135, 0); break;
              case AM_BAND_NONE: OneBigLineSprite.drawString(myLanguage[language][83], 135, 0); break;
            }
#endif
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM9:
            Infoboxprint(myLanguage[language][224]);

            switch (longbandpress) {
              case STANDBY: OneBigLineSprite.drawString(myLanguage[language][225], 135, 0); break;
              case SCREENOFF: OneBigLineSprite.drawString(myLanguage[language][226], 135, 0); break;
              default: OneBigLineSprite.drawString(myLanguage[language][227], 135, 0); break;
            }
            OneBigLineSprite.pushSprite(24, 118);
            break;


          case ITEM10:
            Infoboxprint(myLanguage[language][81]);

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            if (spispeed != 7) {
              OneBigLineSprite.drawString("MHz", 175, 0);
              OneBigLineSprite.setTextDatum(TR_DATUM);
            } else {
              OneBigLineSprite.setTextDatum(TC_DATUM);
            }
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            if (spispeed == 7) {
              OneBigLineSprite.drawString(myLanguage[language][86], 135, 0);
            } else {
              OneBigLineSprite.drawString((spispeed == SPI_SPEED_DEFAULT ? String(myLanguage[language][204]) + " " + String(SPI_FREQUENCY / 1000000, DEC) : String(spispeed * 10, DEC)), 160, 0);
            }
            OneBigLineSprite.pushSprite(24, 118);
            break;
        }
        break;

      case AUDIOSETTINGS:
        switch (menuoption) {
          case ITEM1:
            Infoboxprint(myLanguage[language][10]);

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("dB", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((VolSet > 0 ? "+" : "") + String(VolSet, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            radio.setVolume(VolSet);
            break;

          case ITEM2:
            Infoboxprint(myLanguage[language][45]);

            OneBigLineSprite.drawString((edgebeep ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM3:
            Infoboxprint(myLanguage[language][67]);

            OneBigLineSprite.drawString((audiomode ? "MPX" : "Stereo"), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM4:
            Infoboxprint(myLanguage[language][15]);

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            if (StereoLevel != 0) OneBigLineSprite.drawString("dBµV", 155, 0);
            if (StereoLevel != 0) OneBigLineSprite.setTextDatum(TR_DATUM); else OneBigLineSprite.setTextDatum(TC_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((StereoLevel != 0 ? String(StereoLevel, DEC) : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM5:
            Infoboxprint(myLanguage[language][16]);

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("Hz", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(HighCutLevel * 100, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM6:
            Infoboxprint(myLanguage[language][17]);

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            if (HighCutOffset != 0) OneBigLineSprite.drawString("dBµV", 155, 0);
            if (HighCutOffset != 0) OneBigLineSprite.setTextDatum(TR_DATUM); else OneBigLineSprite.setTextDatum(TC_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((HighCutOffset != 0 ? String(HighCutOffset, DEC) : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM7:
            Infoboxprint(myLanguage[language][199]);

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            if (fmdeemphasis != DEEMPHASIS_NONE) OneBigLineSprite.drawString("μs", 155, 0);
            if (fmdeemphasis != DEEMPHASIS_NONE) OneBigLineSprite.setTextDatum(TR_DATUM); else OneBigLineSprite.setTextDatum(TC_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((fmdeemphasis != DEEMPHASIS_NONE ? (fmdeemphasis == DEEMPHASIS_50 ? String(FM_DEEMPHASIS_50, DEC) : String(FM_DEEMPHASIS_75, DEC)) : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;
        }
        break;

      case DISPLAYSETTINGS:
        switch (menuoption) {
          case ITEM1:
            Infoboxprint(myLanguage[language][40]);

            OneBigLineSprite.drawString(myLanguage[language][0], 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM2:
            Infoboxprint(myLanguage[language][19]);

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("%", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(ContrastSet, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM3:
            Infoboxprint(myLanguage[language][63]);

            OneBigLineSprite.drawString((showmodulation ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM4:
            Infoboxprint(myLanguage[language][91]);

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            if (screensaverset) OneBigLineSprite.drawString(myLanguage[language][92], 155, 0);
            if (screensaverset) OneBigLineSprite.setTextDatum(TR_DATUM); else OneBigLineSprite.setTextDatum(TC_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((screensaverset ? String(screensaverOptions[screensaverset], DEC) : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM5:
            Infoboxprint(myLanguage[language][74]);

            switch (poweroptions) {
              case LCD_OFF: OneBigLineSprite.drawString(myLanguage[language][76], 135, 0); break;
              case LCD_BRIGHTNESS_1_PERCENT: OneBigLineSprite.drawString(myLanguage[language][94], 135, 0); break;
              case LCD_BRIGHTNESS_A_QUARTER: OneBigLineSprite.drawString(myLanguage[language][95], 135, 0); break;
              case LCD_BRIGHTNESS_HALF: OneBigLineSprite.drawString(myLanguage[language][96], 135, 0); break;
            }

            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM6:
            Infoboxprint(myLanguage[language][173]);

            switch (batteryoptions) {
              case BATTERY_NONE: OneBigLineSprite.drawString(myLanguage[language][30], 135, 0); break;
              case BATTERY_VALUE: OneBigLineSprite.drawString(myLanguage[language][174], 135, 0); break;
              case BATTERY_PERCENT: OneBigLineSprite.drawString(myLanguage[language][175], 135, 0); break;
            }

            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM7:
            Infoboxprint(myLanguage[language][98]);

            OneBigLineSprite.drawString(unitString[unit], 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM8:
            Infoboxprint(myLanguage[language][262]);

            OneBigLineSprite.drawString((showclock ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM9:
            Infoboxprint(myLanguage[language][77]);

            OneBigLineSprite.drawString(Theme[CurrentTheme], 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM10:
            Infoboxprint(myLanguage[language][85]);

            OneBigLineSprite.drawString(FreqFont[freqfont], 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;
        }
        break;

      case RDSSETTINGS:
        switch (menuoption) {
          case ITEM1:
            Infoboxprint(myLanguage[language][38]);

            switch (showrdserrors) {
              case 0: OneBigLineSprite.drawString(myLanguage[language][30], 135, 0); break;
              case 1: OneBigLineSprite.drawString(myLanguage[language][200], 135, 0); break;
              case 2: OneBigLineSprite.drawString(myLanguage[language][201], 135, 0); break;
            }
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM2:
            Infoboxprint(myLanguage[language][46]);

            if (region == REGION_EU) OneBigLineSprite.drawString(myLanguage[language][47], 135, 0);
            if (region == REGION_US) OneBigLineSprite.drawString(myLanguage[language][48], 135, 0);

            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM3:
            Infoboxprint(myLanguage[language][49]);

            OneBigLineSprite.drawString((radio.underscore ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM4:
            Infoboxprint(myLanguage[language][60]);

            OneBigLineSprite.drawString((radio.rds.filter ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM5:
            Infoboxprint(myLanguage[language][61]);

            OneBigLineSprite.drawString((radio.rds.pierrors ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM6:
            Infoboxprint(myLanguage[language][99]);

            switch (af) {
              case 0: OneBigLineSprite.drawString(myLanguage[language][30], 135, 0); break;
              case 1: OneBigLineSprite.drawString(String(myLanguage[language][42]) + " / REG " + String(myLanguage[language][42]), 135, 0); break;
              case 2: OneBigLineSprite.drawString(String(myLanguage[language][42]) + " / REG " + String(myLanguage[language][30]), 135, 0); break;
            }

            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM7:
            Infoboxprint(myLanguage[language][176]);

            OneBigLineSprite.drawString((radio.rds.rtbuffer ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM8:
            Infoboxprint(myLanguage[language][215]);

            OneBigLineSprite.drawString((radio.rds.sortaf ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM9:
            Infoboxprint(myLanguage[language][203]);

            switch (radio.rds.fastps) {
              case 0: OneBigLineSprite.drawString(myLanguage[language][30], 135, 0); break;
              case 1: OneBigLineSprite.drawString(myLanguage[language][260], 135, 0); break;
              case 2: OneBigLineSprite.drawString(myLanguage[language][261], 135, 0); break;
            }

            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM10:
            Infoboxprint(myLanguage[language][263]);

            OneBigLineSprite.drawString((showlongps ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;
        }
        break;

      case FMSETTINGS:
        switch (menuoption) {
          case ITEM1:
            Infoboxprint(myLanguage[language][11]);

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("MHz", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(ConverterSet, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM2:
            Infoboxprint(myLanguage[language][12]);

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("MHz", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(LowEdgeSet / 10 + ConverterSet, DEC) + "." + String(LowEdgeSet % 10 + ConverterSet, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM3:
            Infoboxprint(myLanguage[language][13]);

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("MHz", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(HighEdgeSet / 10 + ConverterSet, DEC) + "." + String(HighEdgeSet % 10 + ConverterSet, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM4:
            Infoboxprint(myLanguage[language][14]);

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("dB", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((LevelOffset > 0 ? "+" : "") + String(LevelOffset, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            tftPrint(-1, "dBμV", 179, 165, ActiveColor, ActiveColorSmooth, 28);
            SStatusold = 2000;
            change = true;
            break;

          case ITEM5:
            Infoboxprint(myLanguage[language][18]);

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("dBμV", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(LowLevelSet, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM6:
            Infoboxprint(myLanguage[language][43]);

            OneBigLineSprite.drawString((softmutefm ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM7:
            Infoboxprint(myLanguage[language][65]);

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            if (fmnb != 0) OneBigLineSprite.drawString("%", 155, 0);
            if (fmnb != 0) OneBigLineSprite.setTextDatum(TR_DATUM); else OneBigLineSprite.setTextDatum(TC_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((fmnb != 0 ? String(fmnb, DEC) : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM8:
            Infoboxprint(myLanguage[language][90]);

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("kHz", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);

            switch (fmdefaultstepsize) {
              case 0: OneBigLineSprite.drawString(String(FREQ_FM_STEP_50K * 10, DEC), 135, 0); break;
              case 1: OneBigLineSprite.drawString(String(FREQ_FM_STEP_100K * 10, DEC), 135, 0); break;
              case 2: OneBigLineSprite.drawString(String(FREQ_FM_STEP_200K * 10, DEC), 135, 0); break;
            }
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM9:
            if (fullsearchrds) {
              Infoboxprint(myLanguage[language][206]);

              OneBigLineSprite.drawString((fmsi ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            } else {
              Infoboxprint(myLanguage[language][207]);
            }
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM10:
            Infoboxprint(myLanguage[language][82]);

            OneBigLineSprite.drawString(String(fmscansens), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;
        }
        break;

      case AMSETTINGS:
        switch (menuoption) {
          case ITEM1:
            Infoboxprint(myLanguage[language][44]);

            OneBigLineSprite.drawString((softmuteam ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM2:
            Infoboxprint(myLanguage[language][64]);

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            if (amnb != 0) OneBigLineSprite.drawString("%", 155, 0);
            if (amnb != 0) OneBigLineSprite.setTextDatum(TR_DATUM); else OneBigLineSprite.setTextDatum(TC_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((amnb != 0 ? String(amnb, DEC) : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM3:
            Infoboxprint(myLanguage[language][97]);

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("dB", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((AMLevelOffset > 0 ? "+" : "") + String(AMLevelOffset, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM4:
            Infoboxprint(myLanguage[language][59]);

            OneBigLineSprite.drawString((showSWMIBand ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM5:
            Infoboxprint(myLanguage[language][186]);

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            if (amcodect != 0) OneBigLineSprite.drawString("%", 155, 0);
            if (amcodect != 0) OneBigLineSprite.setTextDatum(TR_DATUM); else OneBigLineSprite.setTextDatum(TC_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((amcodect != 0 ? String(amcodect, DEC) : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM6:
            Infoboxprint(myLanguage[language][188]);

            OneBigLineSprite.drawString(String(amcodectcount, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM7:
            Infoboxprint(myLanguage[language][36]);

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            if (amgain != 0) OneBigLineSprite.drawString("dB", 155, 0);
            if (amgain != 0) OneBigLineSprite.setTextDatum(TR_DATUM); else OneBigLineSprite.setTextDatum(TC_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((amgain != 0 ? String(amgain, DEC) : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM8:
            Infoboxprint(myLanguage[language][169]);

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("kHz", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((mwstepsize ? "10" : "9"), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM9:
            Infoboxprint(myLanguage[language][82]);

            OneBigLineSprite.drawString(String(amscansens, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;
        }
        break;

      case CONNECTIVITY:
        switch (menuoption) {
          case ITEM1:
            Infoboxprint(myLanguage[language][50]);

            OneBigLineSprite.drawString((USBmode ? "RDS Spy" : "XDRGTK"), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM2:
            Infoboxprint(myLanguage[language][51]);

            OneBigLineSprite.drawString((wifi ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM3: {
              tftPrint(0, myLanguage[language][53], 155, 58, ActiveColor, ActiveColorSmooth, 28);
              tftPrint(0, "ESP_" + String(ESP_getChipId()), 155, 98, PrimaryColor, PrimaryColorSmooth, 28);
              tftPrint(0, myLanguage[language][54], 155, 138, ActiveColor, ActiveColorSmooth, 28);
              tftPrint(0, "http://192.168.4.1", 155, 174, PrimaryColor, PrimaryColorSmooth, 16);
              char key [9];
              XDRGTK_key.toCharArray(key, 9);
              char rabbitearsuser [9];
              RabbitearsUser.toCharArray(rabbitearsuser, 9);
              char rabbitearspw [9];
              RabbitearsPassword.toCharArray(rabbitearspw, 9);
              UpdateFonts(1);
              WiFiConnectParam XDRGTK_key_text("Set XDRGTK Password: (max 8 characters)");
              WiFiConnectParam XDRGTK_key_input("XDRGTK_key", "Password", key, 9);
              WiFiConnectParam RabbitearsUser_text("Set rabbitears.info live bandscan user ID");
              WiFiConnectParam RabbitearsUser_input("RabbitearsUser", "ID", rabbitearsuser, 9);
              WiFiConnectParam RabbitearsPassword_text("Set rabbitears.info password");
              WiFiConnectParam RabbitearsPassword_input("RabbitearsPassword", "Password", rabbitearspw, 9);
              if (!setWiFiConnectParam) {
                wc.addParameter(&XDRGTK_key_text);
                wc.addParameter(&XDRGTK_key_input);
                wc.addParameter(&RabbitearsUser_text);
                wc.addParameter(&RabbitearsUser_input);
                wc.addParameter(&RabbitearsPassword_text);
                wc.addParameter(&RabbitearsPassword_input);
                setWiFiConnectParam = true;
              }
              wc.startConfigurationPortal(AP_WAIT);
              XDRGTK_key = XDRGTK_key_input.getValue();
              RabbitearsUser = RabbitearsUser_input.getValue();
              RabbitearsPassword = RabbitearsPassword_input.getValue();
              EEPROM.writeString(EE_STRING_XDRGTK_KEY, XDRGTK_key);
              EEPROM.writeString(EE_STRING_RABBITEARSUSER, RabbitearsUser);
              EEPROM.writeString(EE_STRING_RABBITEARSPASSWORD, RabbitearsPassword);
              EEPROM.commit();
              UpdateFonts(0);
              wifi = true;
              tryWiFi();
              delay(2000);
              menuopen = false;
              BuildMenu();
            } break;

          case ITEM4:
            if (wifi) {
              Infoboxprint(myLanguage[language][58]);

              OneBigLineSprite.drawString(String(WiFi.localIP()[0]) + "." + String(WiFi.localIP()[1]) + "." + String(WiFi.localIP()[2]) + "." + String(subnetclient, DEC), 135, 0);
              OneBigLineSprite.pushSprite(24, 118);
            } else {
              menuopen = false;
              BuildMenu();
            }
            break;

          case ITEM5:
            Infoboxprint(myLanguage[language][271]);

            OneBigLineSprite.drawString(String(stationlistid, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM6:
            Infoboxprint(myLanguage[language][205]);

            OneBigLineSprite.drawString((XDRGTKMuteScreen ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;
        }
        break;

      case DXMODE:
        switch (menuoption) {
          case ITEM1:
            if (presets[scanstart].band == BAND_FM && presets[scanstart].frequency == EE_PRESETS_FREQUENCY) {
              Infoboxprint(myLanguage[language][214]);
              OneBigLineSprite.pushSprite(24, 118);
            } else {
              startFMDXScan();
            }
            break;

          case ITEM2:
            Infoboxprint(myLanguage[language][209]);

            OneBigLineSprite.drawString(String(scanstart + 1), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM3:
            Infoboxprint(myLanguage[language][210]);

            OneBigLineSprite.drawString(String(scanstop + 1), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM4:
            Infoboxprint(myLanguage[language][211]);

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString(myLanguage[language][92], 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((scanhold == 0 ? "0.5" : String(scanhold, DEC)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM5:
            Infoboxprint(myLanguage[language][216]);

            OneBigLineSprite.drawString((scanmem ? myLanguage[language][218] : myLanguage[language][217]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM6:
            Infoboxprint(myLanguage[language][219]);

            switch (scancancel) {
              case OFF:  OneBigLineSprite.drawString(myLanguage[language][30], 135, 0); break;
              case CORRECTPI: OneBigLineSprite.drawString(myLanguage[language][220], 135, 0); break;
              case SIGNAL: OneBigLineSprite.drawString(myLanguage[language][221], 135, 0); break;
            }
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM7:
            Infoboxprint(myLanguage[language][222]);

            OneBigLineSprite.drawString((scanmute ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM8:
            Infoboxprint(myLanguage[language][82]);

            OneBigLineSprite.drawString(String(fmscansens), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM9:
            Infoboxprint(myLanguage[language][281]);

            OneBigLineSprite.drawString((scanholdonsignal ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;
        }
        break;

      case AUTOMEM:
        switch (menuoption) {
          case ITEM1:
            Infoboxprint(myLanguage[language][270]);
            switch (doAutoMemory(memstartfreq, memstopfreq, memstartpos, memstoppos, mempionly, memdoublepi)) {
              case 0:
                tftPrint(0, myLanguage[language][275], 160, 175, ActiveColor, ActiveColorSmooth, 16);
                break;

              case 1:
                tftPrint(0, myLanguage[language][273], 160, 175, ActiveColor, ActiveColorSmooth, 16);
                break;

              case 2:
                tftPrint(0, myLanguage[language][274], 160, 175, ActiveColor, ActiveColorSmooth, 16);
                break;
            }
            break;

          case ITEM2:
            Infoboxprint(myLanguage[language][264]);

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("MHz", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(memstartfreq / 10 + ConverterSet, DEC) + "." + String(memstartfreq % 10 + ConverterSet, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM3:
            Infoboxprint(myLanguage[language][265]);

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("MHz", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(memstopfreq / 10 + ConverterSet, DEC) + "." + String(memstopfreq % 10 + ConverterSet, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM4:
            Infoboxprint(myLanguage[language][266]);

            OneBigLineSprite.drawString(String(memstartpos + 1), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM5:
            Infoboxprint(myLanguage[language][267]);

            OneBigLineSprite.drawString(String(memstoppos + 1), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM6:
            Infoboxprint(myLanguage[language][268]);

            OneBigLineSprite.drawString((mempionly ? myLanguage[language][42] : myLanguage[language][30]), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM7:
            Infoboxprint(myLanguage[language][278]);

            switch (memdoublepi) {
              case MEMPI_OFF: OneBigLineSprite.drawString(myLanguage[language][30], 135, 0); break;
              case MEMPI_RANGE: OneBigLineSprite.drawString(myLanguage[language][279], 135, 0); break;
              default: OneBigLineSprite.drawString(myLanguage[language][280], 135, 0); break;
            }
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM8:
            Infoboxprint(myLanguage[language][82]);

            OneBigLineSprite.drawString(String(fmscansens), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM9:
            Infoboxprint(myLanguage[language][276]);

            ClearMemoryRange(memstartpos, memstoppos);
            OneBigLineSprite.drawString(myLanguage[language][216], 135, 0);
            OneBigLineSprite.pushSprite(24, 118);

            switch (CurrentTheme) {
              case 7: OneBigLineSprite.pushImage(-11, -118, 292, 170, popupbackground_wo); break;
              default: OneBigLineSprite.pushImage(-11, -118, 292, 170, popupbackground); break;
            }
            OneBigLineSprite.drawString(String(memstartpos + 1) + " - " + String(memstoppos + 1) + " " + String(myLanguage[language][277]), 135, 0);
            OneBigLineSprite.pushSprite(24, 148);
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
    if (scanstart >= scanstop) scanstart = scanstop - 1;
    if (scanstop <= scanstart) scanstop = scanstart + 1;

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

String removeNewline(String inputString) {
  String outputString = "";
  for (int i = 0; i < inputString.length(); i++) {
    if (inputString[i] == '\n') {
      outputString += ' ';
    } else {
      outputString += inputString[i];
    }
  }
  return outputString;
}

void drawButton(const char* text, byte button_number, bool active) {
  const int buttonWidth = 70;
  const int buttonHeight = 30;
  const int cornerRadius = 6;
  const int spacingX = 10;
  const int spacingY = 10;
  const int numColumns = 4;
  const int numRows = 5;

  const int startX = 6;
  const int startY = 35;

  if (button_number >= numColumns * numRows) return;

  int row = button_number / numColumns;
  int col = button_number % numColumns;

  int x = startX + col * (buttonWidth + spacingX);
  int y = startY + row * (buttonHeight + spacingY);

  tft.fillRoundRect(x, y, buttonWidth, buttonHeight, cornerRadius, (active ? InsignificantColor : FrameColor));
  tft.drawRoundRect(x, y, buttonWidth, buttonHeight, cornerRadius, ActiveColor);

  tftPrint(0, text, x + buttonWidth / 2, y + buttonHeight / 4, (active ? FrameColor : PrimaryColor), (active ? InsignificantColor : PrimaryColorSmooth), 16);
}