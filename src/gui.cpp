#include "gui.h"
#include "constants.h"
#include <WiFi.h>
#include <Wire.h>
#include <EEPROM.h>
#include <cstring>

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
      ModBarSignificantColor = Crimson;
      ModBarInsignificantColor = Green;
      BWAutoColor = Teal;
      BWAutoColorSmooth = TealSmooth;
      BatteryValueColor = Teal;
      BatteryValueColorSmooth = Black;
      WifiColorLow = PrimaryColor;
      WifiColorHigh = SecondaryColor;
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
      BarSignificantColor = Purple;
      BarInsignificantColor = Skyblue;
      ModBarSignificantColor = Blue;
      ModBarInsignificantColor = Cyan;
      BWAutoColor = Teal;
      BWAutoColorSmooth = TealSmooth;
      BatteryValueColor = Teal;
      BatteryValueColorSmooth = TealSmooth;
      WifiColorLow = PrimaryColor;
      WifiColorHigh = SecondaryColor;
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
      SignificantColor = Red;
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
      ModBarSignificantColor = Orange;
      ModBarInsignificantColor = Coral;
      BWAutoColor = Coral;
      BWAutoColorSmooth = CoralSmooth;
      BatteryValueColor = Watermelon;
      BatteryValueColorSmooth = WatermelonSmooth;
      WifiColorLow = PrimaryColor;
      WifiColorHigh = SecondaryColor;
      break;
    case 3:  // Monochrome theme
      PrimaryColor = White;
      PrimaryColorSmooth = Black;
      SecondaryColor = Honeydew;
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
      BarSignificantColor = Honeydew;
      BarInsignificantColor = White;
      ModBarSignificantColor = Honeydew;
      ModBarInsignificantColor = White;
      BWAutoColor = PureGrey;
      BWAutoColorSmooth = Black;
      BatteryValueColor = White;
      BatteryValueColorSmooth = Black;
      WifiColorLow = PrimaryColor;
      WifiColorHigh = SecondaryColor;
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
      BarSignificantColor = Tangerine;
      BarInsignificantColor = Orange;
      ModBarSignificantColor = Tangerine;
      ModBarInsignificantColor = Yolk;
      BWAutoColor = Tangerine;
      BWAutoColorSmooth = TangerineSmooth;
      BatteryValueColor = Tangerine;
      BatteryValueColorSmooth = TangerineSmooth;
      WifiColorLow = PrimaryColor;
      WifiColorHigh = SecondaryColor;
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
      InsignificantColor = Teal;
      InsignificantColorSmooth = TealSmooth;
      StereoColor = Green;
      StereoColorSmooth = GreenDark;
      RDSColor = Green;
      RDSColorSmooth = GreenDark;
      RDSDropoutColor = Laurel;
      RDSDropoutColorSmooth = LaurelSmooth;
      BarSignificantColor = Green;
      BarInsignificantColor = Cabbage;
      ModBarSignificantColor = Green;
      ModBarInsignificantColor = Teal;
      BWAutoColor = Cabbage;
      BWAutoColorSmooth = CabbageSmooth;
      BatteryValueColor = Cabbage;
      BatteryValueColorSmooth = CabbageSmooth;
      WifiColorLow = PrimaryColor;
      WifiColorHigh = SecondaryColor;
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
      InsignificantColor = Pink;
      InsignificantColorSmooth = PinkSmooth;
      StereoColor = Sakura;
      StereoColorSmooth = SakuraSmooth;
      RDSColor = Sakura;
      RDSColorSmooth = SakuraSmooth;
      RDSDropoutColor = SakuraGrey;
      RDSDropoutColorSmooth = SakuraGreySmooth;
      BarSignificantColor = Violet;
      BarInsignificantColor = Sakura;
      ModBarSignificantColor = Cherry;
      ModBarInsignificantColor = Pink;
      BWAutoColor = Cherry;
      BWAutoColorSmooth = CherrySmooth;
      BatteryValueColor = Cherry;
      BatteryValueColorSmooth = CherrySmooth;
      WifiColorLow = PrimaryColor;
      WifiColorHigh = SecondaryColor;
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
      SignificantColorSmooth = RedSmooth;
      InsignificantColor = Green;
      InsignificantColorSmooth = GreenSmooth;
      StereoColor = Black;
      StereoColorSmooth = Honeydew;
      RDSColor = Black;
      RDSColorSmooth = Honeydew;
      RDSDropoutColor = PureGrey;
      RDSDropoutColorSmooth = White;
      BarSignificantColor = Black;
      BarInsignificantColor = Cabbage;
      ModBarSignificantColor = Black;
      ModBarInsignificantColor = Green;
      BWAutoColor = PureGrey;
      BWAutoColorSmooth = White;
      BatteryValueColor = Black;
      BatteryValueColorSmooth = White;
      WifiColorLow = PrimaryColor;
      WifiColorHigh = SecondaryColor;
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
      InsignificantColor = Orange;
      InsignificantColorSmooth = OrangeSmooth;
      StereoColor = Tangerine;
      StereoColorSmooth = IndigoSmooth;
      RDSColor = Tangerine;
      RDSColorSmooth = IndigoSmooth;
      RDSDropoutColor = Copper;
      RDSDropoutColorSmooth = CopperSmooth;
      BarSignificantColor = Yolk;
      BarInsignificantColor = Orange;
      ModBarSignificantColor = Yolk;
      ModBarInsignificantColor = Tangerine;
      BWAutoColor = Yolk;
      BWAutoColorSmooth = YolkSmooth;
      BatteryValueColor = Yolk;
      BatteryValueColorSmooth = YolkSmooth;
      WifiColorLow = PrimaryColor;
      WifiColorHigh = SecondaryColor;
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
      BarSignificantColor = Ocean;
      BarInsignificantColor = Cyan;
      ModBarSignificantColor = Ocean;
      ModBarInsignificantColor = Deepsky;
      BWAutoColor = Deepsky;
      BWAutoColorSmooth = DeepskySmooth;
      BatteryValueColor = Deepsky;
      BatteryValueColorSmooth = DeepskySmooth;
      WifiColorLow = PrimaryColor;
      WifiColorHigh = SecondaryColor;
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
      InsignificantColor = Purple;
      InsignificantColorSmooth = PurpleSmooth;
      StereoColor = Indigo;
      StereoColorSmooth = IndigoSmooth;
      RDSColor = Indigo;
      RDSColorSmooth = IndigoSmooth;
      RDSDropoutColor = Logan;
      RDSDropoutColorSmooth = LoganSmooth;
      BarSignificantColor = Indigo;
      BarInsignificantColor = Cherry;
      ModBarSignificantColor = Indigo;
      ModBarInsignificantColor = Violet;
      BWAutoColor = Violet;
      BWAutoColorSmooth = VioletSmooth;
      BatteryValueColor = Violet;
      BatteryValueColorSmooth = VioletSmooth;
      WifiColorLow = PrimaryColor;
      WifiColorHigh = SecondaryColor;
      break;

    case 11:  // Queer
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
      ModBarSignificantColor = Red;
      ModBarInsignificantColor = Purple;
      BWAutoColor = Violet;
      BWAutoColorSmooth = VioletSmooth;
      BatteryValueColor = Purple;
      BatteryValueColorSmooth = PurpleSmooth;
      WifiColorLow = PrimaryColor;
      WifiColorHigh = SecondaryColor;
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
      BarInsignificantColor = Green;
      ModBarSignificantColor = Cherry;
      ModBarInsignificantColor = Blue;
      BWAutoColor = Teal;
      BWAutoColorSmooth = TealSmooth;
      BatteryValueColor = Teal;
      BatteryValueColorSmooth = Black;
      WifiColorLow = PrimaryColor;
      WifiColorHigh = SecondaryColor;
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
      SignificantColor = Cherry;
      SignificantColorSmooth = CherrySmooth;
      InsignificantColor = Cyan;
      InsignificantColorSmooth = CyanSmooth;
      StereoColor = Cherry;
      StereoColorSmooth = CherrySmooth;
      RDSColor = Teal;
      RDSColorSmooth = TealSmooth;
      RDSDropoutColor = Logan;
      RDSDropoutColorSmooth = LoganSmooth;
      BarSignificantColor = Violet;
      BarInsignificantColor = Teal;
      ModBarSignificantColor = Purple;
      ModBarInsignificantColor = Pink;
      BWAutoColor = Violet;
      BWAutoColorSmooth = VioletSmooth;
      BatteryValueColor = Turquoise;
      BatteryValueColorSmooth = CyanDarkSmooth;
      WifiColorLow = Turquoise;
      WifiColorHigh = Pink;
      break;
  }
}

void BuildAFScreen() {
  if (!afscreen && RDSstatus) {
    tft.drawRoundRect(20, 30, 274, 170, 5, ActiveColor);
    tft.fillRoundRect(22, 32, 270, 166, 5, BackgroundColor);
    tftPrint(0, textUI(34), 155, 98, ActiveColor, ActiveColorSmooth, 28);
    radio.TestAFEON();
  }
  afscreen = true;
  advancedRDS = false;

  tft.fillScreen(BackgroundColor);
  tft.drawRect(0, 0, 320, 240, FrameColor);
  tft.drawLine(0, 30, 320, 30, FrameColor);
  tft.drawLine(0, 199, 320, 199, FrameColor);
  tft.drawLine(0, 218, 320, 218, FrameColor);
  tft.drawLine(30, 30, 30, 0, FrameColor);
  tft.drawLine(66, 30, 66, 0, FrameColor);
  tft.drawLine(105, 30, 105, 0, FrameColor);
  tft.drawLine(162, 30, 162, 0, FrameColor);
  tft.drawLine(248, 30, 248, 0, FrameColor);
  tftPrint(-1, "kHz", 205, 4, ActiveColor, ActiveColorSmooth, 28);
  tftPrint(0, textUI(33), 160, 222, ActiveColor, ActiveColorSmooth, 16);
  if (afpagenr == 1) {
    if (!radio.rds.hasAF) tftPrint(-1, textUI(87), 6, 48, PrimaryColor, PrimaryColorSmooth, 16);
  } else if (afpagenr == 2) {
    if (!radio.rds.hasEON) tftPrint(-1, textUI(88), 6, 48, PrimaryColor, PrimaryColorSmooth, 16);
  }
  RDSstatusold = !RDSstatusold;
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
  rds_clockold = "";
  dropout = false;
  rdsreset = true;
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
          FullLineSprite.drawString(removeNewline(textUI(177)), 152, 2);
          break;

        case MAINSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(108)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);

          switch (hardwaremodel) {
            case BASE_ILI9341: FullLineSprite.drawString(textUI(109), 298, 2); break;
            case PORTABLE_ILI9341: FullLineSprite.drawString(textUI(110), 298, 2); break;
            case PORTABLE_TOUCH_ILI9341: FullLineSprite.drawString(textUI(111), 298, 2); break;
          }
          break;

        case AUDIOSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(20)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString("dB", 298, 2);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((VolSet > 0 ? "+" : "") + String(VolSet, DEC), 258, 2);
          break;

        case DISPLAYSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(39)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(textUI(0), 298, 2);
          break;

        case RDSSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(38)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);

          switch (showrdserrors) {
            case 0: FullLineSprite.drawString(textUI(30), 298, 2); break;
            case 1: FullLineSprite.drawString(textUI(200), 298, 2); break;
            case 2: FullLineSprite.drawString(textUI(201), 298, 2); break;
          }
          break;

        case FMSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(21)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString("MHz", 298, 2);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(String(ConverterSet, DEC), 258, 2);
          break;

        case AMSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(44)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((softmuteam ? textUI(31) : textUI(30)), 298, 2);
          break;

        case CONNECTIVITY:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(5)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((USBmode ? "RDS Spy" : "XDRGTK"), 298, 2);
          break;

        case DXMODE:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(212)), 6, 2);
          break;

        case AUTOMEM:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(269)), 6, 2);
          break;
      }
      break;

    case 1:
      switch (menupage) {
        case INDEX:
          FullLineSprite.setTextDatum(TC_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(178)), 152, 2);
          break;

        case MAINSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(107)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((touchrotating ? textUI(31) : textUI(30)), 298, 2);
          break;

        case AUDIOSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(45)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((edgebeep ? textUI(31) : textUI(30)), 298, 2);
          break;

        case DISPLAYSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(29)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(String(ContrastSet, DEC), 258, 2);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString("%", 298, 2);
          break;

        case RDSSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(46)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          switch (radio.rds.region) {
            case 0: FullLineSprite.drawString(textUI(47), 298, 2); break;
            case 1: FullLineSprite.drawString(String(textUI(48)) + " DB", 298, 2); break;
            case 2: FullLineSprite.drawString(textUI(48), 298, 2); break;
            case 3: FullLineSprite.drawString(textUI(300), 298, 2); break;
          }
          break;

        case FMSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(22)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString("MHz", 298, 2);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(String(LowEdgeSet / 10 + ConverterSet, DEC) + "." + String(LowEdgeSet % 10 + ConverterSet, DEC), 258, 2);
          break;

        case AMSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(64)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          if (amnb != 0) FullLineSprite.drawString(String(amnb, DEC), 258, 2);
          if (amnb != 0) FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString((amnb != 0 ? "%" : textUI(30)), 298, 2);
          break;

        case CONNECTIVITY:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(51) + (wifi ? " IP: " + String(WiFi.localIP().toString()) : "")), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((wifi ? textUI(31) : textUI(30)), 298, 2);
          break;

        case DXMODE:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(209)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(String(scanstart + 1, DEC), 298, 2);
          break;

        case AUTOMEM:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(264)), 6, 2);

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
          FullLineSprite.drawString(removeNewline(textUI(179)), 152, 2);
          break;

        case MAINSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(75)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          if (tot != 0) FullLineSprite.drawString(String(tot), 258, 2);
          if (tot != 0) FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString((tot != 0 ? textUI(80) : textUI(30)), 298, 2);
          break;

        case AUDIOSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(67)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((audiomode ? "MPX" : "Stereo"), 298, 2);
          break;

        case DISPLAYSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(63)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((showmodulation ? textUI(31) : textUI(30)), 298, 2);
          break;

        case RDSSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(49)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          switch (radio.underscore) {
            case 0: FullLineSprite.drawString(textUI(30), 298, 2); break;
            case 1: FullLineSprite.drawString(textUI(50), 298, 2); break;
            case 2: FullLineSprite.drawString(textUI(31), 298, 2); break;
          }
          break;

        case FMSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(23)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString("MHz", 298, 2);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(String(HighEdgeSet / 10 + ConverterSet, DEC) + "." + String(HighEdgeSet % 10 + ConverterSet, DEC), 258, 2);
          break;

        case AMSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(97)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString("dB", 298, 2);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((AMLevelOffset > 0 ? "+" : "") + String(AMLevelOffset, DEC), 258, 2);
          break;

        case CONNECTIVITY:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(52)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(">", 298, 2);
          break;

        case DXMODE:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(210)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(String(scanstop + 1, DEC), 298, 2);
          break;

        case AUTOMEM:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(265)), 6, 2);

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
          FullLineSprite.drawString(removeNewline(textUI(180)), 152, 2);
          break;

        case MAINSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(62)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          if (autosquelch) FullLineSprite.drawString(textUI(86), 298, 2); else FullLineSprite.drawString((usesquelch ? textUI(31) : textUI(30)), 298, 2);
          break;

        case AUDIOSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(25)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          if (StereoLevel != 0) FullLineSprite.drawString(String(StereoLevel, DEC), 258, 2);
          if (StereoLevel != 0) FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString((StereoLevel != 0 ? "dBμV" : textUI(30)), 298, 2);
          break;

        case DISPLAYSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(91)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          if (screensaverset) FullLineSprite.drawString(String(screensaverOptions[screensaverset], DEC), 258, 2);
          if (screensaverset) FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString((screensaverset ? textUI(92) : textUI(30)), 298, 2);
          break;

        case RDSSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(60)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((radio.rds.filter ? textUI(31) : textUI(30)), 298, 2);
          break;

        case FMSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(24)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString("dB", 298, 2);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((LevelOffset > 0 ? "+" : "") + String(LevelOffset, DEC), 258, 2);
          break;

        case AMSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(59)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((showSWMIBand ? textUI(31) : textUI(30)), 298, 2);
          break;

        case CONNECTIVITY:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(58)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((wifi ? String(WiFi.localIP()[0]) + "." + String(WiFi.localIP()[1]) + "." + String(WiFi.localIP()[2]) + "." + String(subnetclient, DEC) : "-"), 298, 2);
          break;

        case DXMODE:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(211)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(92)), 298, 2);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((scanhold == 0 ? "0.5" : String(scanhold, DEC)), 258, 2);
          break;

        case AUTOMEM:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(266)), 6, 2);

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
          FullLineSprite.drawString(removeNewline(textUI(181)), 152, 2);
          break;

        case MAINSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(37)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString("dBµV", 298, 2);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(String(fmagc, DEC), 258, 2);
          break;

        case AUDIOSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(26)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(String(HighCutLevel * 100, DEC), 258, 2);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString("Hz", 298, 2);
          break;

        case DISPLAYSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(74)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);

          switch (poweroptions) {
            case LCD_OFF: FullLineSprite.drawString(textUI(76), 298, 2); break;
            case LCD_BRIGHTNESS_1_PERCENT: FullLineSprite.drawString(textUI(94), 298, 2); break;
            case LCD_BRIGHTNESS_A_QUARTER: FullLineSprite.drawString(textUI(95), 298, 2); break;
            case LCD_BRIGHTNESS_HALF: FullLineSprite.drawString(textUI(96), 298, 2); break;
          }
          break;

        case RDSSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(61)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((radio.rds.pierrors ? textUI(31) : textUI(30)), 298, 2);
          break;

        case FMSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(28)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString("dBμV", 298, 2);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(String(LowLevelSet, DEC), 258, 2);
          break;

        case AMSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(185)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          if (amcodect != 0) FullLineSprite.drawString(String(amcodect, DEC), 258, 2);
          if (amcodect != 0) FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString((amcodect != 0 ? "%" : textUI(30)), 298, 2);
          break;

        case CONNECTIVITY:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(271)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(String(stationlistid, DEC), 298, 2);
          break;

        case DXMODE:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(216)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((scanmem ? textUI(218) : textUI(217)), 298, 2);
          break;

        case AUTOMEM:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(267)), 6, 2);

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
          FullLineSprite.drawString(removeNewline(textUI(182)), 152, 2);
          break;

        case MAINSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(198)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString("dBµV", 298, 2);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(String(amagc, DEC), 258, 2);
          break;

        case AUDIOSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(27)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          if (HighCutOffset != 0) FullLineSprite.drawString(String(HighCutOffset, DEC), 258, 2);
          if (HighCutOffset != 0) FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString((HighCutOffset != 0 ? "dBμV" : textUI(30)), 298, 2);
          break;

        case DISPLAYSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(173)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);

          switch (batteryoptions) {
            case BATTERY_NONE: FullLineSprite.drawString(textUI(30), 298, 2); break;
            case BATTERY_VALUE: FullLineSprite.drawString(textUI(174), 298, 2); break;
            case BATTERY_PERCENT: FullLineSprite.drawString(textUI(175), 298, 2); break;
          }
          break;

        case RDSSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(99)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);

          switch (af) {
            case 0: FullLineSprite.drawString(textUI(30), 298, 2); break;
            case 1: FullLineSprite.drawString(String(textUI(31)) + " / REG " + String(textUI(31)), 298, 2); break;
            case 2: FullLineSprite.drawString(String(textUI(31)) + " / REG " + String(textUI(30)), 298, 2); break;
          }
          break;

        case FMSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(43)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((softmutefm ? textUI(31) : textUI(30)), 298, 2);
          break;

        case AMSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(187)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(String(amcodectcount, DEC), 298, 2);
          break;

        case CONNECTIVITY:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(205)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((XDRGTKMuteScreen ? textUI(31) : textUI(30)), 298, 2);
          break;

        case DXMODE:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(219)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          switch (scancancel) {
            case OFF: FullLineSprite.drawString(textUI(30), 298, 2); break;
            case CORRECTPI: FullLineSprite.drawString(textUI(220), 298, 2); break;
            case SIGNAL: FullLineSprite.drawString(textUI(221), 298, 2); break;
          }
          break;

        case AUTOMEM:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(268)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((mempionly ? textUI(31) : textUI(30)), 298, 2);
          break;
      }
      break;

    case 6:
      switch (menupage) {
        case INDEX:
          FullLineSprite.setTextDatum(TC_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(183)), 152, 2);
          break;

        case MAINSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(100)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);

          switch (bandFM) {
            case FM_BAND_ALL: FullLineSprite.drawString(textUI(105) + String(",") + textUI(106), 298, 2); break;
            case FM_BAND_OIRT: FullLineSprite.drawString(textUI(106), 298, 2); break;
            case FM_BAND_FM: FullLineSprite.drawString(textUI(105), 298, 2); break;
            case FM_BAND_NONE: FullLineSprite.drawString(textUI(83), 298, 2); break;
          }
          break;

        case AUDIOSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(199)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          if (fmdeemphasis != DEEMPHASIS_NONE) FullLineSprite.drawString(String((fmdeemphasis == DEEMPHASIS_50 ? FM_DEEMPHASIS_50 : FM_DEEMPHASIS_75), DEC), 258, 2);
          if (fmdeemphasis != DEEMPHASIS_NONE) FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(((fmdeemphasis != DEEMPHASIS_NONE) != 0 ? "μs" : textUI(30)), 298, 2);
          break;

        case DISPLAYSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(98)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(unitString[unit], 298, 2);
          break;

        case RDSSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(176)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((radio.rds.rtbuffer ? textUI(31) : textUI(30)), 298, 2);
          break;

        case FMSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(65)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          if (fmnb != 0) FullLineSprite.drawString(String(fmnb, DEC), 258, 2);
          if (fmnb != 0) FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString((fmnb != 0 ? "%" : textUI(30)), 298, 2);
          break;

        case AMSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(36)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          if (amgain != 0) FullLineSprite.drawString(String(amgain, DEC), 258, 2);
          if (amgain != 0) FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString((amgain != 0 ? "dB" : textUI(30)), 298, 2);
          break;

        case CONNECTIVITY:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(298)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((NTPoffset > -1 ? "+" : "") + String(NTPoffset, DEC), 298, 2);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString("GMT", 258, 2);
          break;

        case DXMODE:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(222)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((scanmute ? textUI(31) : textUI(30)), 298, 2);
          break;

        case AUTOMEM:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(278)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);

          switch (memdoublepi) {
            case MEMPI_OFF: FullLineSprite.drawString(textUI(30), 298, 2); break;
            case MEMPI_RANGE: FullLineSprite.drawString(textUI(279), 298, 2); break;
            default: FullLineSprite.drawString(textUI(280), 298, 2); break;
          }
          break;
      }
      break;

    case 7:
      switch (menupage) {
        case INDEX:
          FullLineSprite.setTextDatum(TC_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(213)), 152, 2);
          break;

        case MAINSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(101)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
#ifdef HAS_AIR_BAND
          switch (bandAM) {
            case AM_BAND_ALL: FullLineSprite.drawString(textUI(102) + String(",") + textUI(103) + String(",") + textUI(104) + String(",") + textUI(223), 298, 2); break;
            case AM_BAND_LW_MW_SW: FullLineSprite.drawString(textUI(102) + String(",") + textUI(103) + String(",") + textUI(104), 298, 2); break;
            case AM_BAND_LW_MW_AIR: FullLineSprite.drawString(textUI(102) + String(",") + textUI(103) + String(",") + textUI(223), 298, 2); break;
            case AM_BAND_LW_SW_AIR: FullLineSprite.drawString(textUI(102) + String(",") + textUI(104) + String(",") + textUI(223), 298, 2); break;
            case AM_BAND_MW_SW_AIR: FullLineSprite.drawString(textUI(103) + String(",") + textUI(104) + String(",") + textUI(223), 298, 2); break;
            case AM_BAND_LW_MW: FullLineSprite.drawString(textUI(102) + String(",") + textUI(103), 298, 2); break;
            case AM_BAND_LW_SW: FullLineSprite.drawString(textUI(102) + String(",") + textUI(104), 298, 2); break;
            case AM_BAND_LW_AIR: FullLineSprite.drawString(textUI(102) + String(",") + textUI(223), 298, 2); break;
            case AM_BAND_MW_SW: FullLineSprite.drawString(textUI(103) + String(",") + textUI(104), 298, 2); break;
            case AM_BAND_MW_AIR: FullLineSprite.drawString(textUI(103) + String(",") + textUI(223), 298, 2); break;
            case AM_BAND_SW_AIR: FullLineSprite.drawString(textUI(104) + String(",") + textUI(223), 298, 2); break;
            case AM_BAND_LW: FullLineSprite.drawString(textUI(102), 298, 2); break;
            case AM_BAND_MW: FullLineSprite.drawString(textUI(103), 298, 2); break;
            case AM_BAND_SW: FullLineSprite.drawString(textUI(104), 298, 2); break;
            case AM_BAND_AIR: FullLineSprite.drawString(textUI(223), 298, 2); break;
            case AM_BAND_NONE: FullLineSprite.drawString(textUI(83), 298, 2); break;
          }
          break;
#else
          switch (bandAM) {
            case AM_BAND_ALL: FullLineSprite.drawString(textUI(102) + String(",") + textUI(103) + String(",") + textUI(104), 298, 2); break;
            case AM_BAND_LW_MW: FullLineSprite.drawString(textUI(102) + String(",") + textUI(103), 298, 2); break;
            case AM_BAND_LW_SW: FullLineSprite.drawString(textUI(102) + String(",") + textUI(104), 298, 2); break;
            case AM_BAND_MW_SW: FullLineSprite.drawString(textUI(103) + String(",") + textUI(104), 298, 2); break;
            case AM_BAND_LW: FullLineSprite.drawString(textUI(102), 298, 2); break;
            case AM_BAND_MW: FullLineSprite.drawString(textUI(103), 298, 2); break;
            case AM_BAND_SW: FullLineSprite.drawString(textUI(104), 298, 2); break;
            case AM_BAND_NONE: FullLineSprite.drawString(textUI(83), 298, 2); break;
          }
          break;
#endif

        case DISPLAYSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(262)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((showclock ? textUI(31) : textUI(30)), 298, 2);
          break;

        case RDSSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(215)), 6, 2);
          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((radio.rds.sortaf ? textUI(31) : textUI(30)), 298, 2);
          break;

        case FMSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(90)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString("kHz", 300, 2);
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
          FullLineSprite.drawString(removeNewline(textUI(169)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((mwstepsize ? "10" : "9"), 258, 2);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString("kHz", 300, 2);
          break;

        case CONNECTIVITY:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(297)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((autoDST ? textUI(31) : textUI(30)), 298, 2);
          break;

        case DXMODE:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(296)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((autolog ? textUI(31) : textUI(30)), 298, 2);
          break;

        case AUTOMEM:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(82)), 6, 2);

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
          FullLineSprite.drawString(removeNewline(textUI(270)), 152, 2);
          break;

        case MAINSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(224)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          switch (longbandpress) {
            case STANDBY: FullLineSprite.drawString(textUI(225), 298, 2); break;
            case SCREENOFF: FullLineSprite.drawString(textUI(226), 298, 2); break;
            default: FullLineSprite.drawString(textUI(227), 298, 2); break;
          }
          break;

        case DISPLAYSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(77)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(Theme[CurrentTheme], 298, 2);
          break;

        case RDSSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(203)), 6, 2);
          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);

          switch (radio.rds.fastps) {
            case 0: FullLineSprite.drawString(textUI(30), 298, 2); break;
            case 1: FullLineSprite.drawString(textUI(260), 298, 2); break;
            case 2: FullLineSprite.drawString(textUI(261), 298, 2); break;
          }
          break;

        case FMSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(206)), 6, 2);
          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((fmsi ? textUI(31) : textUI(30)), 298, 2);
          break;

        case AMSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(82)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(String(amscansens), 298, 2);
          break;

        case CONNECTIVITY:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(93)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((clockampm ? "12" : "24"), 298, 2);
          break;

        case DXMODE:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(281)), 6, 2);
          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((scanholdonsignal ? textUI(31) : textUI(30)), 298, 2);
          break;

        case AUTOMEM:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(276)), 6, 2);
          break;
      }
      break;

    case 9:
      switch (menupage) {
        case INDEX:
          FullLineSprite.setTextDatum(TC_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(70)), 152, 2);
          break;

        case MAINSETTINGS:
          if (dynamicspi) {
            FullLineSprite.setTextDatum(TL_DATUM);
            FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            FullLineSprite.drawString(removeNewline(textUI(81)), 6, 2);

            FullLineSprite.setTextDatum(TR_DATUM);

            if (spispeed == 7) {
              FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
              FullLineSprite.drawString(textUI(86), 298, 2);
            } else {
              FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
              FullLineSprite.drawString("MHz", 298, 2);
              FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
              FullLineSprite.drawString((spispeed == SPI_SPEED_DEFAULT ? String(textUI(204)) + " " + String(SPI_FREQUENCY / 1000000, DEC) : String(spispeed * 10, DEC)), 258, 2);
            }
          }
          break;

        case DISPLAYSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(85)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(FreqFont[freqfont], 298, 2);
          break;

        case RDSSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(263)), 6, 2);
          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((showlongps ? textUI(31) : textUI(30)), 298, 2);
          break;

        case FMSETTINGS:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(82)), 6, 2);

          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString(String(fmscansens), 298, 2);
          break;


        case CONNECTIVITY:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(41)), 6, 2);

          char PICT[5];
          sprintf(PICT, "%04X", radio.rds.PICTlock);
          FullLineSprite.setTextDatum(TR_DATUM);
          FullLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          FullLineSprite.drawString((radio.rds.PICTlock == 0 ? textUI(30) : textUI(31)), 298, 2);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString((radio.rds.PICTlock != 0 ? String(PICT) : ""), 258, 2);
          break;

        case DXMODE:
          FullLineSprite.setTextDatum(TL_DATUM);
          FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          FullLineSprite.drawString(removeNewline(textUI(292)), 6, 2);
          break;
      }
      break;
  }
  FullLineSprite.pushSprite(8, 2 + position);
}

void ShowOneButton(byte position, byte item, bool selected) {
  switch (CurrentTheme) {
    case 7: PSSprite.pushImage (0, 0, 150, 32, touchselback_wo); break;
    default: PSSprite.pushImage (0, 0, 150, 32, touchselback); break;
  }

  switch (item) {
    case 0:
      switch (menupage) {
        case INDEX:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(177))), 75, 8);
          break;

        case MAINSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(108))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);

          switch (hardwaremodel) {
            case BASE_ILI9341: PSSprite.drawString(textUI(109), 75, 15); break;
            case PORTABLE_ILI9341: PSSprite.drawString(textUI(110), 75, 15); break;
            case PORTABLE_TOUCH_ILI9341: PSSprite.drawString(textUI(111), 75, 15); break;
          }
          break;

        case AUDIOSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(20))), 75, 1);

          PSSprite.setTextDatum(TL_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString("dB", 77, 15);
          PSSprite.setTextDatum(TR_DATUM);
          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString((VolSet > 0 ? "+" : "") + String(VolSet, DEC), 73, 15);
          break;

        case DISPLAYSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(39))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString(textUI(0), 75, 15);
          break;

        case RDSSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(38))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);

          switch (showrdserrors) {
            case 0: PSSprite.drawString(textUI(30), 75, 15); break;
            case 1: PSSprite.drawString(textUI(200), 75, 15); break;
            case 2: PSSprite.drawString(textUI(201), 75, 15); break;
          }
          break;

        case FMSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(21))), 75, 1);

          PSSprite.setTextDatum(TL_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString("MHz", 77, 15);
          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.setTextDatum(TR_DATUM);
          PSSprite.drawString(String(ConverterSet, DEC), 73, 15);
          break;

        case AMSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(44))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString((softmuteam ? textUI(31) : textUI(30)), 75, 15);
          break;

        case CONNECTIVITY:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(5))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString((USBmode ? "RDS Spy" : "XDRGTK"), 75, 15);
          break;

        case DXMODE:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(212))), 75, 8);
          break;

        case AUTOMEM:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(269))), 75, 8);
          break;
      }
      break;
    case 1:
      switch (menupage) {
        case INDEX:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(178))), 75, 8);
          break;

        case MAINSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(107))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString((touchrotating ? textUI(31) : textUI(30)), 75, 15);
          break;

        case AUDIOSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(45))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString((edgebeep ? textUI(31) : textUI(30)), 75, 15);
          break;

        case DISPLAYSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(29))), 75, 1);

          PSSprite.setTextDatum(TR_DATUM);
          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString(String(ContrastSet, DEC), 73, 15);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.setTextDatum(TL_DATUM);
          PSSprite.drawString("%", 77, 15);
          break;

        case RDSSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(46))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          switch (radio.rds.region) {
            case 0: PSSprite.drawString(textUI(47), 75, 15); break;
            case 1: PSSprite.drawString(String(textUI(48)) + " DB", 75, 15); break;
            case 2: PSSprite.drawString(textUI(48), 75, 15); break;
            case 3: PSSprite.drawString(textUI(300), 75, 15); break;
          }
          break;

        case FMSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(22))), 75, 1);

          PSSprite.setTextDatum(TL_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString("MHz", 77, 15);
          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.setTextDatum(TR_DATUM);
          PSSprite.drawString(String(LowEdgeSet / 10 + ConverterSet, DEC) + "." + String(LowEdgeSet % 10 + ConverterSet, DEC), 73, 15);
          break;

        case AMSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(64))), 75, 1);

          if (amnb == 0) {
            PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            PSSprite.drawString(textUI(30), 75, 15);
          } else {
            PSSprite.setTextDatum(TR_DATUM);
            PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            PSSprite.drawString(String(amnb, DEC), 73, 15);
            PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            PSSprite.setTextDatum(TL_DATUM);
            PSSprite.drawString("%", 77, 15);
          }
          break;

        case CONNECTIVITY:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(wifi ? " IP: " + String(WiFi.localIP().toString()) : textUI(51))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString((wifi ? textUI(31) : textUI(30)), 75, 15);
          break;

        case DXMODE:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(209))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString(String(scanstart + 1, DEC), 75, 15);
          break;

        case AUTOMEM:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(264))), 75, 1);

          PSSprite.setTextDatum(TL_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString("MHz", 77, 15);
          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.setTextDatum(TR_DATUM);
          PSSprite.drawString(String(memstartfreq / 10 + ConverterSet, DEC) + "." + String(memstartfreq % 10 + ConverterSet, DEC), 73, 15);
          break;
      }
      break;

    case 2:
      switch (menupage) {
        case INDEX:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(179))), 75, 8);
          break;

        case MAINSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(75))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          if (tot == 0) {
            PSSprite.drawString(textUI(30), 75, 15);
          } else {
            PSSprite.setTextDatum(TR_DATUM);
            PSSprite.drawString(String(tot), 73, 15);
            PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            PSSprite.setTextDatum(TL_DATUM);
            PSSprite.drawString(textUI(80), 77, 15);
          }
          break;

        case AUDIOSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(67))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString((audiomode ? "MPX" : "Stereo"), 75, 15);
          break;

        case DISPLAYSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(63))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString((showmodulation ? textUI(31) : textUI(30)), 75, 15);
          break;

        case RDSSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(49))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          switch (radio.underscore) {
            case 0: PSSprite.drawString(textUI(30), 75, 15); break;
            case 1: PSSprite.drawString(textUI(50), 75, 15); break;
            case 2: PSSprite.drawString(textUI(31), 75, 15); break;
          }
          break;

        case FMSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(23))), 75, 1);

          PSSprite.setTextDatum(TL_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString("MHz", 77, 15);
          PSSprite.setTextDatum(TR_DATUM);
          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString(String(HighEdgeSet / 10 + ConverterSet, DEC) + "." + String(HighEdgeSet % 10 + ConverterSet, DEC), 73, 15);
          break;

        case AMSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(97))), 75, 1);

          PSSprite.setTextDatum(TL_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString("dB", 77, 15);
          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.setTextDatum(TR_DATUM);
          PSSprite.drawString((AMLevelOffset > 0 ? "+" : "") + String(AMLevelOffset, DEC), 73, 15);
          break;

        case CONNECTIVITY:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(52))), 75, 8);

          break;

        case DXMODE:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(210))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString(String(scanstop + 1, DEC), 75, 15);
          break;

        case AUTOMEM:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(265))), 75, 1);

          PSSprite.setTextDatum(TL_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString("MHz", 77, 15);
          PSSprite.setTextDatum(TR_DATUM);
          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString(String(memstopfreq / 10 + ConverterSet, DEC) + "." + String(memstopfreq % 10 + ConverterSet, DEC), 73, 15);
          break;
      }
      break;

    case 3:
      switch (menupage) {
        case INDEX:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(180))), 75, 8);
          break;

        case MAINSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(62))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          if (autosquelch) PSSprite.drawString(textUI(86), 75, 15); else PSSprite.drawString((usesquelch ? textUI(31) : textUI(30)), 75, 15);
          break;

        case AUDIOSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(25))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          if (StereoLevel == 0) {
            PSSprite.drawString(textUI(30), 75, 15);
          } else {
            PSSprite.setTextDatum(TR_DATUM);
            PSSprite.drawString(String(StereoLevel, DEC), 73, 15);
            PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            PSSprite.setTextDatum(TL_DATUM);
            PSSprite.drawString("dBμV", 77, 15);
          }
          break;

        case DISPLAYSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(91))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          if (!screensaverset) {
            PSSprite.drawString(textUI(30), 75, 15);
          } else {
            PSSprite.setTextDatum(TR_DATUM);
            PSSprite.drawString(String(screensaverOptions[screensaverset], DEC), 73, 15);
            PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            PSSprite.setTextDatum(TL_DATUM);
            PSSprite.drawString(textUI(92), 77, 15);
          }
          break;

        case RDSSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(60))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString((radio.rds.filter ? textUI(31) : textUI(30)), 75, 15);
          break;

        case FMSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(24))), 75, 1);

          PSSprite.setTextDatum(TL_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString("dB", 77, 15);
          PSSprite.setTextDatum(TR_DATUM);
          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString((LevelOffset > 0 ? "+" : "") + String(LevelOffset, DEC), 73, 15);
          break;

        case AMSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(59))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString((showSWMIBand ? textUI(31) : textUI(30)), 75, 15);
          break;

        case CONNECTIVITY:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(58))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString((wifi ? String(WiFi.localIP()[0]) + "." + String(WiFi.localIP()[1]) + "." + String(WiFi.localIP()[2]) + "." + String(subnetclient, DEC) : "-"), 75, 15);
          break;

        case DXMODE:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(211))), 75, 1);

          PSSprite.setTextDatum(TL_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(removeNewline(textUI(92)), 77, 15);
          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.setTextDatum(TR_DATUM);
          PSSprite.drawString((scanhold == 0 ? "0.5" : String(scanhold, DEC)), 73, 15);
          break;

        case AUTOMEM:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(266))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString(String(memstartpos + 1, DEC), 75, 15);
          break;
      }
      break;

    case 4:
      switch (menupage) {
        case INDEX:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(181))), 75, 8);
          break;

        case MAINSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(37))), 75, 1);

          PSSprite.setTextDatum(TL_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString("dBµV", 77, 15);
          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.setTextDatum(TR_DATUM);
          PSSprite.drawString(String(fmagc, DEC), 73, 15);
          break;

        case AUDIOSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(26))), 75, 1);

          PSSprite.setTextDatum(TR_DATUM);
          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString(String(HighCutLevel * 100, DEC), 73, 15);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.setTextDatum(TL_DATUM);
          PSSprite.drawString("Hz", 77, 15);
          break;

        case DISPLAYSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(74))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);

          switch (poweroptions) {
            case LCD_OFF: PSSprite.drawString(textUI(76), 75, 15); break;
            case LCD_BRIGHTNESS_1_PERCENT: PSSprite.drawString(textUI(94), 75, 15); break;
            case LCD_BRIGHTNESS_A_QUARTER: PSSprite.drawString(textUI(95), 75, 15); break;
            case LCD_BRIGHTNESS_HALF: PSSprite.drawString(textUI(96), 75, 15); break;
          }
          break;

        case RDSSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(61))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString((radio.rds.pierrors ? textUI(31) : textUI(30)), 75, 15);
          break;

        case FMSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(28))), 75, 1);

          PSSprite.setTextDatum(TL_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString("dBμV", 77, 15);
          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.setTextDatum(TR_DATUM);
          PSSprite.drawString(String(LowLevelSet, DEC), 73, 15);
          break;

        case AMSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(185))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          if (amcodect == 0) {
            PSSprite.drawString(textUI(30), 75, 15);
          } else {
            PSSprite.setTextDatum(TR_DATUM);
            PSSprite.drawString(String(amcodect, DEC), 73, 15);
            PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            PSSprite.setTextDatum(TL_DATUM);
            PSSprite.drawString("%", 77, 15);
          }
          break;

        case CONNECTIVITY:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(271))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString(String(stationlistid, DEC), 75, 15);
          break;

        case DXMODE:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(216))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString((scanmem ? textUI(218) : textUI(217)), 75, 15);
          break;

        case AUTOMEM:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(267))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString(String(memstoppos + 1, DEC), 75, 15);
          break;
      }
      break;

    case 5:
      switch (menupage) {
        case INDEX:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(182))), 75, 8);
          break;

        case MAINSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(198))), 75, 1);

          PSSprite.setTextDatum(TL_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString("dBµV", 77, 15);
          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.setTextDatum(TR_DATUM);
          PSSprite.drawString(String(amagc, DEC), 73, 15);
          break;

        case AUDIOSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(27))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          if (HighCutOffset == 0) {
            PSSprite.drawString(textUI(30), 75, 15);
          } else {
            PSSprite.setTextDatum(TR_DATUM);
            PSSprite.drawString(String(HighCutOffset, DEC), 73, 15);
            PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            PSSprite.setTextDatum(TL_DATUM);
            PSSprite.drawString("dBμV", 77, 15);
          }
          break;

        case DISPLAYSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(173))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);

          switch (batteryoptions) {
            case BATTERY_NONE: PSSprite.drawString(textUI(30), 75, 15); break;
            case BATTERY_VALUE: PSSprite.drawString(textUI(174), 75, 15); break;
            case BATTERY_PERCENT: PSSprite.drawString(textUI(175), 75, 15); break;
          }
          break;

        case RDSSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(99))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);

          switch (af) {
            case 0: PSSprite.drawString(textUI(30), 75, 15); break;
            case 1: PSSprite.drawString(String(textUI(31)) + " / REG " + String(textUI(31)), 75, 15); break;
            case 2: PSSprite.drawString(String(textUI(31)) + " / REG " + String(textUI(30)), 75, 15); break;
          }
          break;

        case FMSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(43))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString((softmutefm ? textUI(31) : textUI(30)), 75, 15);
          break;

        case AMSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(187))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString(String(amcodectcount, DEC), 75, 15);
          break;

        case CONNECTIVITY:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(205))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString((XDRGTKMuteScreen ? textUI(31) : textUI(30)), 75, 15);
          break;

        case DXMODE:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(219))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          switch (scancancel) {
            case OFF: PSSprite.drawString(textUI(30), 75, 15); break;
            case CORRECTPI: PSSprite.drawString(textUI(220), 75, 15); break;
            case SIGNAL: PSSprite.drawString(textUI(221), 75, 15); break;
          }
          break;

        case AUTOMEM:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(268))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString((mempionly ? textUI(31) : textUI(30)), 75, 15);
          break;
      }
      break;

    case 6:
      switch (menupage) {
        case INDEX:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(183))), 75, 8);
          break;

        case MAINSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(100))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);

          switch (bandFM) {
            case FM_BAND_ALL: PSSprite.drawString(textUI(105) + String(",") + textUI(106), 75, 15); break;
            case FM_BAND_OIRT: PSSprite.drawString(textUI(106), 75, 15); break;
            case FM_BAND_FM: PSSprite.drawString(textUI(105), 75, 15); break;
            case FM_BAND_NONE: PSSprite.drawString(textUI(83), 75, 15); break;
          }
          break;

        case AUDIOSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(199))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          if (fmdeemphasis == DEEMPHASIS_NONE) {
            PSSprite.drawString(textUI(30), 75, 15);
          } else {
            PSSprite.setTextDatum(TR_DATUM);
            PSSprite.drawString(String((fmdeemphasis == DEEMPHASIS_50 ? FM_DEEMPHASIS_50 : FM_DEEMPHASIS_75), DEC), 73, 15);
            PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            PSSprite.setTextDatum(TL_DATUM);
            PSSprite.drawString("μs", 77, 15);
          }
          break;

        case DISPLAYSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(98))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString(unitString[unit], 75, 15);
          break;

        case RDSSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(176))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString((radio.rds.rtbuffer ? textUI(31) : textUI(30)), 75, 15);
          break;

        case FMSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(65))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          if (fmnb == 0) {
            PSSprite.drawString(textUI(30), 75, 15);
          } else {
            PSSprite.setTextDatum(TL_DATUM);
            PSSprite.drawString(String(fmnb, DEC), 73, 15);
            PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            PSSprite.setTextDatum(TR_DATUM);
            PSSprite.drawString("%", 77, 15);
          }
          break;

        case AMSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(36))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          if (amgain == 0) {
            PSSprite.drawString(textUI(30), 75, 15);
          } else {
            PSSprite.setTextDatum(TR_DATUM);
            PSSprite.drawString(String(amgain, DEC), 73, 15);
            PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            PSSprite.setTextDatum(TL_DATUM);
            PSSprite.drawString("dB", 77, 15);
          }
          break;

        case CONNECTIVITY:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(298))), 75, 1);

          PSSprite.setTextDatum(TL_DATUM);
          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString((NTPoffset > -1 ? "+" : "") + String(NTPoffset, DEC), 77, 15);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.setTextDatum(TR_DATUM);
          PSSprite.drawString("GMT", 73, 15);
          break;

        case DXMODE:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(222))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString((scanmute ? textUI(31) : textUI(30)), 75, 15);
          break;

        case AUTOMEM:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(278))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);

          switch (memdoublepi) {
            case MEMPI_OFF: PSSprite.drawString(textUI(30), 75, 15); break;
            case MEMPI_RANGE: PSSprite.drawString(textUI(279), 75, 15); break;
            default: PSSprite.drawString(textUI(280), 75, 15); break;
          }
          break;
      }
      break;

    case 7:
      switch (menupage) {
        case INDEX:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(213))), 75, 8);
          break;

        case MAINSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(101))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
#ifdef HAS_AIR_BAND
          switch (bandAM) {
            case AM_BAND_ALL: PSSprite.drawString(textUI(102) + String(",") + textUI(103) + String(",") + textUI(104) + String(",") + textUI(223), 75, 15); break;
            case AM_BAND_LW_MW_SW: PSSprite.drawString(textUI(102) + String(",") + textUI(103) + String(",") + textUI(104), 75, 15); break;
            case AM_BAND_LW_MW_AIR: PSSprite.drawString(textUI(102) + String(",") + textUI(103) + String(",") + textUI(223), 75, 15); break;
            case AM_BAND_LW_SW_AIR: PSSprite.drawString(textUI(102) + String(",") + textUI(104) + String(",") + textUI(223), 75, 15); break;
            case AM_BAND_MW_SW_AIR: PSSprite.drawString(textUI(103) + String(",") + textUI(104) + String(",") + textUI(223), 75, 15); break;
            case AM_BAND_LW_MW: PSSprite.drawString(textUI(102) + String(",") + textUI(103), 75, 15); break;
            case AM_BAND_LW_SW: PSSprite.drawString(textUI(102) + String(",") + textUI(104), 75, 15); break;
            case AM_BAND_LW_AIR: PSSprite.drawString(textUI(102) + String(",") + textUI(223), 75, 15); break;
            case AM_BAND_MW_SW: PSSprite.drawString(textUI(103) + String(",") + textUI(104), 75, 15); break;
            case AM_BAND_MW_AIR: PSSprite.drawString(textUI(103) + String(",") + textUI(223), 75, 15); break;
            case AM_BAND_SW_AIR: PSSprite.drawString(textUI(104) + String(",") + textUI(223), 75, 15); break;
            case AM_BAND_LW: PSSprite.drawString(textUI(102), 75, 15); break;
            case AM_BAND_MW: PSSprite.drawString(textUI(103), 75, 15); break;
            case AM_BAND_SW: PSSprite.drawString(textUI(104), 75, 15); break;
            case AM_BAND_AIR: PSSprite.drawString(textUI(223), 75, 15); break;
            case AM_BAND_NONE: PSSprite.drawString(textUI(83), 75, 15); break;
          }
          break;
#else
          switch (bandAM) {
            case AM_BAND_ALL: PSSprite.drawString(textUI(102) + String(",") + textUI(103) + String(",") + textUI(104), 75, 15); break;
            case AM_BAND_LW_MW: PSSprite.drawString(textUI(102) + String(",") + textUI(103), 75, 15); break;
            case AM_BAND_LW_SW: PSSprite.drawString(textUI(102) + String(",") + textUI(104), 75, 15); break;
            case AM_BAND_MW_SW: PSSprite.drawString(textUI(103) + String(",") + textUI(104), 75, 15); break;
            case AM_BAND_LW: PSSprite.drawString(textUI(102), 75, 15); break;
            case AM_BAND_MW: PSSprite.drawString(textUI(103), 75, 15); break;
            case AM_BAND_SW: PSSprite.drawString(textUI(104), 75, 15); break;
            case AM_BAND_NONE: PSSprite.drawString(textUI(83), 75, 15); break;
          }
          break;
#endif

        case DISPLAYSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(262))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString((showclock ? textUI(31) : textUI(30)), 75, 15);
          break;

        case RDSSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(215))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString((radio.rds.sortaf ? textUI(31) : textUI(30)), 75, 15);
          break;

        case FMSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(90))), 75, 1);

          PSSprite.setTextDatum(TL_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString("kHz", 77, 15);
          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.setTextDatum(TR_DATUM);

          switch (fmdefaultstepsize) {
            case 0: PSSprite.drawString(String(FREQ_FM_STEP_50K * 10, DEC), 73, 15); break;
            case 1: PSSprite.drawString(String(FREQ_FM_STEP_100K * 10, DEC), 73, 15); break;
            case 2: PSSprite.drawString(String(FREQ_FM_STEP_200K * 10, DEC), 73, 15); break;
          }
          break;

        case AMSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(169))), 75, 1);

          PSSprite.setTextDatum(TR_DATUM);
          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString((mwstepsize ? "10" : "9"), 73, 15);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.setTextDatum(TL_DATUM);
          PSSprite.drawString("kHz", 77, 15);
          break;

        case CONNECTIVITY:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(297))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString((autoDST ? textUI(31) : textUI(30)), 75, 15);
          break;

        case DXMODE:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(296))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString((autolog ? textUI(31) : textUI(30)), 75, 15);
          break;

        case AUTOMEM:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(82))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString(String(fmscansens), 75, 15);
          break;
      }
      break;

    case 8:
      switch (menupage) {
        case INDEX:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(270))), 75, 8);
          break;

        case MAINSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(224))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          switch (longbandpress) {
            case STANDBY: PSSprite.drawString(textUI(225), 75, 15); break;
            case SCREENOFF: PSSprite.drawString(textUI(226), 75, 15); break;
            default: PSSprite.drawString(textUI(227), 75, 15); break;
          }
          break;

        case DISPLAYSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(77))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString(Theme[CurrentTheme], 75, 15);
          break;

        case RDSSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(203))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);

          switch (radio.rds.fastps) {
            case 0: PSSprite.drawString(textUI(30), 75, 15); break;
            case 1: PSSprite.drawString(textUI(260), 75, 15); break;
            case 2: PSSprite.drawString(textUI(261), 75, 15); break;
          }
          break;

        case FMSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(206))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString((fmsi ? textUI(31) : textUI(30)), 75, 15);
          break;

        case AMSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(82))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString(String(amscansens), 75, 15);
          break;

        case CONNECTIVITY:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(93))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString((clockampm ? "12" : "24"), 75, 15);
          break;

        case DXMODE:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(281))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString((scanholdonsignal ? textUI(31) : textUI(30)), 75, 15);
          break;

        case AUTOMEM:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(276))), 75, 8);
          break;
      }
      break;

    case 9:
      switch (menupage) {
        case INDEX:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(70))), 75, 8);
          break;

        case MAINSETTINGS:
          if (dynamicspi) {
            PSSprite.setTextDatum(TC_DATUM);
            PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            PSSprite.drawString(shortLine(removeNewline(textUI(81))), 75, 1);

            if (spispeed == 7) {
              PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
              PSSprite.drawString(textUI(86), 75, 15);
            } else {
              PSSprite.setTextDatum(TL_DATUM);
              PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
              PSSprite.drawString("MHz", 77, 15);
              PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
              PSSprite.setTextDatum(TR_DATUM);
              PSSprite.drawString((spispeed == SPI_SPEED_DEFAULT ? String(textUI(204)) + " " + String(SPI_FREQUENCY / 1000000, DEC) : String(spispeed * 10, DEC)), 73, 15);
            }
          }
          break;

        case DISPLAYSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(85))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString(FreqFont[freqfont], 75, 15);
          break;

        case RDSSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(263))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString((showlongps ? textUI(31) : textUI(30)), 75, 15);
          break;

        case FMSETTINGS:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(82))), 75, 1);

          PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
          PSSprite.drawString(String(fmscansens), 75, 15);
          break;

        case CONNECTIVITY:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(41))), 75, 1);


          if (radio.rds.PICTlock == 0) {
            PSSprite.setTextDatum(TC_DATUM);
            PSSprite.drawString(textUI(30), 75, 15);
          } else {
            char PICT[5];
            sprintf(PICT, "%04X", radio.rds.PICTlock);

            PSSprite.setTextDatum(TL_DATUM);
            PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            PSSprite.drawString(textUI(31), 77, 15);
            PSSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            PSSprite.setTextDatum(TR_DATUM);
            PSSprite.drawString(String(PICT), 73, 15);
          }
          break;


        case DXMODE:
          PSSprite.setTextDatum(TC_DATUM);
          PSSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
          PSSprite.drawString(shortLine(removeNewline(textUI(292))), 75, 8);
          break;
      }
      break;
  }
  PSSprite.pushSprite((position > ITEM5 ? 163 : 8), (position * 2) - 22 - (position > ITEM5 ? 200 : 0));
  if (selected) {
    tft.drawRect((position > ITEM5 ? 163 : 8),
                 (position * 2) - 22 - (position > ITEM5 ? 200 : 0), 150, 32, PrimaryColor);
    tft.drawRect((position > ITEM5 ? 164 : 9),
                 (position * 2) - 21 - (position > ITEM5 ? 200 : 0), 148, 30, PrimaryColor);
  }
}

void BuildBWSelector() {
  BWsettemp = BWset;
  switch (CurrentTheme) {
    case 7: tft.pushImage (0, 0, 320, 240, configurationbackground_wo); break;
    default: tft.pushImage (0, 0, 320, 240, configurationbackground); break;
  }
  tftPrint(0, textUI(285), 160, 6, PrimaryColor, PrimaryColorSmooth, 16);
  showBWSelector();
}

void showBWSelector() {
  if (band < BAND_GAP) {
    for (int x = 0; x < 17; x++) drawButton(BWButtonLabelsFM[x], x, (BWset == x + 1 || (BWset == 0 && x == 16) ? true : false), false);
    drawButton(BWButtonLabelsFM[17], 17, (!iMSset ? true : false), false);
    drawButton(BWButtonLabelsFM[18], 18, (!EQset ? true : false), false);
    drawButton("OK", 19, false, false);
  } else {
    for (int x = 0; x < 4; x++) {
      drawButton(BWButtonLabelsAM[x], x, (BWset == x + 1 ? true : false), false);
    }
    drawButton("OK", 19, false, false);
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
    tftPrint(0, textUI(32), 160, 6, PrimaryColor, PrimaryColorSmooth, 16);
  } else {
    tftPrint(-1, textUI(184), (hardwaremodel == PORTABLE_TOUCH_ILI9341 ? 20 : 8), 6, PrimaryColor, PrimaryColorSmooth, 16);
    tftPrint(1, textUI(189 + menupage - 1), 312, 6, ActiveColor, ActiveColorSmooth, 16);
  }

  if (hardwaremodel == PORTABLE_TOUCH_ILI9341) {
    tft.fillRoundRect(4, 4, 15, 20, 3, FrameColor);
    tft.drawRoundRect(4, 4, 15, 20, 3, ActiveColor);
    tft.fillTriangle(12, 8, 8, 14, 12, 20, (CurrentTheme == 7 ? White : ActiveColor));

    if (items[menupage] > 0) ShowOneButton(ITEM1, 0, false);
    if (items[menupage] > 1) ShowOneButton(ITEM2, 1, false);
    if (items[menupage] > 2) ShowOneButton(ITEM3, 2, false);
    if (items[menupage] > 3) ShowOneButton(ITEM4, 3, false);
    if (items[menupage] > 4) ShowOneButton(ITEM5, 4, false);
    if (items[menupage] > 5) ShowOneButton(ITEM6, 5, false);
    if (items[menupage] > 6) ShowOneButton(ITEM7, 6, false);
    if (items[menupage] > 7) ShowOneButton(ITEM8, 7, false);
    if (items[menupage] > 8) ShowOneButton(ITEM9, 8, false);
    if (items[menupage] > 9) ShowOneButton(ITEM10, 9, false);
  } else {
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
  }

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
  tft.drawLine(0, 140, 210, 140, FrameColor);
  tft.drawLine(0, 166, 210, 166, FrameColor);
  tft.drawLine(0, 193, 210, 193, FrameColor);
  tft.drawLine(0, 217, 210, 217, FrameColor);
  tft.drawLine(30, 30, 30, 0, FrameColor);
  tft.drawLine(66, 30, 66, 0, FrameColor);
  tft.drawLine(105, 30, 105, 0, FrameColor);
  tft.drawLine(105, 30, 105, 0, FrameColor);
  tft.drawLine(162, 30, 162, 0, FrameColor);
  tft.drawLine(210, 30, 210, 240, FrameColor);
  tft.drawLine(210, 191, 320, 191, FrameColor);
  tft.drawLine(248, 30, 248, 0, FrameColor);

  tftPrint(-1, "ERRORS", 3, 34, ActiveColor, ActiveColorSmooth, 16);
  tftPrint(1, "MHz", 310, 35, ActiveColor, ActiveColorSmooth, 16);
  tftPrint(1, unitString[unit], 310, 51, ActiveColor, ActiveColorSmooth, 16);
  if (radio.rds.region == 0) {
    tftPrint(-1, "PI", 216, 81, ActiveColor, ActiveColorSmooth, 16);
  } else {
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
  tftPrint(1, "Artificial head", 300, 145, ActiveColor, ActiveColorSmooth, 16);
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

  tftPrint(-1, "kHz", 205, 4, ActiveColor, ActiveColorSmooth, 28);

  tft.drawBitmap(68, 5, RDSLogo, 35, 22, GreyoutColor);
  tft.drawBitmap(249, 4, Speaker, 28, 24, GreyoutColor);

  if (!StereoToggle) {
    tft.drawBitmap(38, 5, Mono, 22, 22, SecondaryColor);
  } else {
    tft.drawBitmap(32, 5, Stereo, 32, 22, GreyoutColor);
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

  RDSstatusold = !RDSstatusold;
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
  tft.drawLine(0, 160, 195, 160, FrameColor);
  tft.drawLine(0, 180, 320, 180, FrameColor);
  tft.drawLine(0, 217, 320, 217, FrameColor);
  tft.drawLine(16, 114, 189, 114, ActiveColor);
  tft.drawLine(30, 30, 30, 0, FrameColor);
  tft.drawLine(66, 30, 66, 0, FrameColor);
  tft.drawLine(105, 30, 105, 0, FrameColor);
  tft.drawLine(162, 30, 162, 0, FrameColor);
  tft.drawLine(195, 100, 195, 180, FrameColor);
  tft.drawLine(195, 144, 320, 144, FrameColor);
  tft.drawLine(210, 180, 210, 217, FrameColor);
  tft.drawLine(257, 144, 257, 180, FrameColor);
  tft.drawLine(248, 30, 248, 0, FrameColor);

  if (!showmodulation) tft.drawLine(16, 143, 189, 143, GreyoutColor); else tft.drawLine(16, 143, 189, 143, ActiveColor);

  for (byte segments = 0; segments < 93; segments++) {
    if (segments > 54) {
      if (((segments - 53) % 10) == 0) {
        tft.fillRect(22 + (2 * segments), 112, 2, 2, BarSignificantColor);
        if (!showmodulation) tft.fillRect(22 + (2 * segments), 141, 2, 2, GreyoutColor); else tft.fillRect(22 + (2 * segments), 141, 2, 2, BarSignificantColor);
      }
    } else {
      if (((segments + 1) % 6) == 0) {
        tft.fillRect(22 + (2 * segments), 112, 2, 2, BarInsignificantColor);
        if (!showmodulation) tft.fillRect(22 + (2 * segments), 141, 2, 2, GreyoutColor); else tft.fillRect(22 + (2 * segments), 141, 2, 2, BarInsignificantColor);
      }
    }
  }

  if (usesquelch || autosquelch) tftPrint(-1, "SQ:", 197, 147, ActiveColor, ActiveColorSmooth, 16);
  tftPrint(-1, "US:", 259, 147, ActiveColor, ActiveColorSmooth, 16);
  tftPrint(-1, "MP:", 259, 165, ActiveColor, ActiveColorSmooth, 16);
  tftPrint(-1, "CN:", 197, 165, ActiveColor, ActiveColorSmooth, 16);
  tftPrint(1, "dB", 255, 165, ActiveColor, ActiveColorSmooth, 16);
  tftPrint(1, "%", 316, 165, ActiveColor, ActiveColorSmooth, 16);
  tftPrint(1, "%", 316, 147, ActiveColor, ActiveColorSmooth, 16);

  tftPrint(0, "S", 7, 101, ActiveColor, ActiveColorSmooth, 16);
  tftPrint(-1, "1", 21, 115, ActiveColor, ActiveColorSmooth, 16);
  tftPrint(-1, "3", 41, 115, ActiveColor, ActiveColorSmooth, 16);
  tftPrint(-1, "5", 61, 115, ActiveColor, ActiveColorSmooth, 16);
  tftPrint(-1, "7", 81, 115, ActiveColor, ActiveColorSmooth, 16);
  tftPrint(-1, "9", 101, 115, ActiveColor, ActiveColorSmooth, 16);
  tftPrint(-1, "+10", 127, 115, ActiveColor, ActiveColorSmooth, 16);
  tftPrint(-1, "+30", 160, 115, ActiveColor, ActiveColorSmooth, 16);

  if (!showmodulation) {
    tftPrint(0, "A", 7, 128, GreyoutColor, BackgroundColor, 16);
    tftPrint(-1, "10", 24, 144, GreyoutColor, BackgroundColor, 16);
    tftPrint(-1, "30", 54, 144, GreyoutColor, BackgroundColor, 16);
    tftPrint(-1, "50", 84, 144, GreyoutColor, BackgroundColor, 16);
    tftPrint(-1, "70", 114, 144, GreyoutColor, BackgroundColor, 16);
    tftPrint(-1, "100", 160, 144, GreyoutColor, BackgroundColor, 16);
  } else {
    tftPrint(0, "A", 7, 128, ActiveColor, ActiveColorSmooth, 16);
    tftPrint(-1, "10", 24, 144, ActiveColor, ActiveColorSmooth, 16);
    tftPrint(-1, "30", 54, 144, ActiveColor, ActiveColorSmooth, 16);
    tftPrint(-1, "50", 84, 144, ActiveColor, ActiveColorSmooth, 16);
    tftPrint(-1, "70", 114, 144, ActiveColor, BackgroundColor, 16);
    tftPrint(-1, "100", 160, 144, ActiveColor, ActiveColorSmooth, 16);
  }

  tftPrint(1, "kHz", 246, 4, ActiveColor, ActiveColorSmooth, 28);
  tftPrint(1, unitString[unit], 316, 128, ActiveColor, ActiveColorSmooth, 16);

  tft.drawBitmap(68, 5, RDSLogo, 35, 22, GreyoutColor);
  tft.drawBitmap(249, 4, Speaker, 28, 24, GreyoutColor);

  if (!StereoToggle) {
    tft.drawBitmap(38, 5, Mono, 22, 22, SecondaryColor);
  } else {
    tft.drawBitmap(32, 5, Stereo, 32, 22, GreyoutColor);
  }

  if (autosquelch) showAutoSquelch(1);

  RDSstatusold = !RDSstatusold;
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
  MPold = 99;
  USold = 99;
}

void MenuUpDown(bool dir) {
  if (!menuopen) {
    if (hardwaremodel == PORTABLE_TOUCH_ILI9341) ShowOneButton(menuoption, menuitem, false); else ShowOneLine(menuoption, menuitem, false);

    if (hardwaremodel == BASE_ILI9341) {
      if (dir) {
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
    } else {
      if (dir) {
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
    }

    if (hardwaremodel == PORTABLE_TOUCH_ILI9341) ShowOneButton(menuoption, menuitem, true); else ShowOneLine(menuoption, menuitem, true);
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
            if (dir) {
              hardwaremodel++;
              if (hardwaremodel > RADIO_HARDWARE_CNT - 1) hardwaremodel = 0;
            } else {
              hardwaremodel--;
              if (hardwaremodel > RADIO_HARDWARE_CNT - 1) hardwaremodel = RADIO_HARDWARE_CNT - 1;
            }

            switch (hardwaremodel) {
              case BASE_ILI9341: OneBigLineSprite.drawString(textUI(109), 135, 0); break;
              case PORTABLE_ILI9341: OneBigLineSprite.drawString(textUI(110), 135, 0); break;
              case PORTABLE_TOUCH_ILI9341: OneBigLineSprite.drawString(textUI(111), 135, 0); break;
            }

            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM2:
            touchrotating = !touchrotating;
            OneBigLineSprite.drawString((touchrotating ? textUI(31) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM3:
            if (dir) {
              switch (tot) {
                case 0: tot = 15; break;
                case 15: tot = 30; break;
                case 30: tot = 60; break;
                case 60: tot = 90; break;
                default: tot = 0; break;
              }
            } else {
              switch (tot) {
                case 15: tot = 0; break;
                case 30: tot = 15; break;
                case 60: tot = 30; break;
                case 90: tot = 60; break;
                default: tot = 90; break;
              }
            }

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);

            if (tot != 0) {
              OneBigLineSprite.drawString(textUI(80), 150, 0);
              OneBigLineSprite.setTextDatum(TR_DATUM);
              OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
              OneBigLineSprite.drawString(String(tot), 135, 0);
            } else {
              OneBigLineSprite.setTextDatum(TC_DATUM);
              OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
              OneBigLineSprite.drawString(textUI(30), 135, 0);
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

            if (autosquelch) OneBigLineSprite.drawString(textUI(86), 135, 0); else OneBigLineSprite.drawString((usesquelch ? textUI(31) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM5:
            if (dir) {
              fmagc++;
              if (fmagc > 92) fmagc = 84;
            } else {
              fmagc--;
              if (fmagc < 84) fmagc = 92;
            }
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
            if (dir) {
              amagc++;
              if (amagc > 102) amagc = 94;
            } else {
              amagc--;
              if (amagc < 94) amagc = 102;
            }
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
            if (dir) {
              bandFM++;
              if (bandFM > FM_BAND_CNT - 1) bandFM = FM_BAND_ALL;
            } else {
              bandFM--;
              if (bandFM > FM_BAND_CNT) bandFM = FM_BAND_NONE;
            }

            switch (bandFM) {
              case FM_BAND_ALL: OneBigLineSprite.drawString(textUI(105) + String(",") + textUI(106), 135, 0); break;
              case FM_BAND_OIRT: OneBigLineSprite.drawString(textUI(106), 135, 0); break;
              case FM_BAND_FM: OneBigLineSprite.drawString(textUI(105), 135, 0); break;
              case FM_BAND_NONE: OneBigLineSprite.drawString(textUI(83), 135, 0); break;
            }
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM8:
            if (dir) {
              bandAM++;
              if (bandAM > AM_BAND_CNT - 1) bandAM = AM_BAND_ALL;
            } else {
              bandAM--;
              if (bandAM > AM_BAND_CNT) bandAM = AM_BAND_NONE;
            }

#ifdef HAS_AIR_BAND
            switch (bandAM) {
              case AM_BAND_ALL: OneBigLineSprite.drawString(textUI(102) + String(",") + textUI(103) + String(",") + textUI(104) + String(",") + textUI(223), 135, 0); break;
              case AM_BAND_LW_MW_SW: OneBigLineSprite.drawString(textUI(102) + String(",") + textUI(103) + String(",") + textUI(104), 135, 0); break;
              case AM_BAND_LW_MW_AIR: OneBigLineSprite.drawString(textUI(102) + String(",") + textUI(103) + String(",") + textUI(223), 135, 0); break;
              case AM_BAND_LW_SW_AIR: OneBigLineSprite.drawString(textUI(102) + String(",") + textUI(104) + String(",") + textUI(223), 135, 0); break;
              case AM_BAND_MW_SW_AIR: OneBigLineSprite.drawString(textUI(103) + String(",") + textUI(104) + String(",") + textUI(223), 135, 0); break;
              case AM_BAND_LW_MW: OneBigLineSprite.drawString(textUI(102) + String(",") + textUI(103), 135, 0); break;
              case AM_BAND_LW_SW: OneBigLineSprite.drawString(textUI(102) + String(",") + textUI(104), 135, 0); break;
              case AM_BAND_LW_AIR: OneBigLineSprite.drawString(textUI(102) + String(",") + textUI(223), 135, 0); break;
              case AM_BAND_MW_SW: OneBigLineSprite.drawString(textUI(103) + String(",") + textUI(104), 135, 0); break;
              case AM_BAND_MW_AIR: OneBigLineSprite.drawString(textUI(103) + String(",") + textUI(223), 135, 0); break;
              case AM_BAND_SW_AIR: OneBigLineSprite.drawString(textUI(104) + String(",") + textUI(223), 135, 0); break;
              case AM_BAND_LW: OneBigLineSprite.drawString(textUI(102), 135, 0); break;
              case AM_BAND_MW: OneBigLineSprite.drawString(textUI(103), 135, 0); break;
              case AM_BAND_SW: OneBigLineSprite.drawString(textUI(104), 135, 0); break;
              case AM_BAND_AIR: OneBigLineSprite.drawString(textUI(223), 135, 0); break;
              case AM_BAND_NONE: OneBigLineSprite.drawString(textUI(83), 135, 0); break;
            }
#else
            switch (bandAM) {
              case AM_BAND_ALL: OneBigLineSprite.drawString(textUI(102) + String(",") + textUI(103) + String(",") + textUI(104), 135, 0); break;
              case AM_BAND_LW_MW: OneBigLineSprite.drawString(textUI(102) + String(",") + textUI(103), 135, 0); break;
              case AM_BAND_LW_SW: OneBigLineSprite.drawString(textUI(102) + String(",") + textUI(104), 135, 0); break;
              case AM_BAND_MW_SW: OneBigLineSprite.drawString(textUI(103) + String(",") + textUI(104), 135, 0); break;
              case AM_BAND_LW: OneBigLineSprite.drawString(textUI(102), 135, 0); break;
              case AM_BAND_MW: OneBigLineSprite.drawString(textUI(103), 135, 0); break;
              case AM_BAND_SW: OneBigLineSprite.drawString(textUI(104), 135, 0); break;
              case AM_BAND_NONE: OneBigLineSprite.drawString(textUI(83), 135, 0); break;
            }
#endif
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM9:
            if (dir) {
              longbandpress++;
              if (longbandpress > 2) longbandpress = 0;
            } else {
              longbandpress--;
              if (longbandpress > 2) longbandpress = 2;
            }

            switch (longbandpress) {
              case STANDBY: OneBigLineSprite.drawString(textUI(225), 135, 0); break;
              case SCREENOFF: OneBigLineSprite.drawString(textUI(226), 135, 0); break;
              default: OneBigLineSprite.drawString(textUI(227), 135, 0); break;
            }
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM10:
            if (dir) {
              spispeed++;
              if (spispeed > SPI_SPEED_COUNT - 1) spispeed = 0;
            } else {
              spispeed--;
              if (spispeed > SPI_SPEED_COUNT - 1) spispeed = SPI_SPEED_COUNT - 1;
            }

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
              OneBigLineSprite.drawString(textUI(86), 135, 0);
            } else {
              OneBigLineSprite.drawString((spispeed == SPI_SPEED_DEFAULT ? String(textUI(204)) + " " + String(SPI_FREQUENCY / 1000000, DEC) : String(spispeed * 10, DEC)), 160, 0);
            }
            OneBigLineSprite.pushSprite(24, 118);
#ifdef DYNAMIC_SPI_SPEED
            if (spispeed == SPI_SPEED_DEFAULT) {
              tft.setSPISpeed(SPI_FREQUENCY / 1000000);
            } else if (spispeed == 7) {
              setAutoSpeedSPI();
            } else {
              tft.setSPISpeed(spispeed * 10);
            }
#endif
            break;
        }
        break;

      case AUDIOSETTINGS:
        switch (menuoption) {
          case ITEM1:
            if (dir) {
              VolSet++;
              if (VolSet > 10) VolSet = 10;
            } else {
              VolSet--;
              if (VolSet < -10) VolSet = -10;
            }

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
            OneBigLineSprite.drawString((edgebeep ? textUI(31) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM3:
            audiomode = !audiomode;

            OneBigLineSprite.drawString((audiomode ? "MPX" : "Stereo"), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            radio.setAudio(audiomode);
            break;

          case ITEM4:
            if (dir) {
              StereoLevel ++;
              if (StereoLevel > 60 || StereoLevel <= 30) {
                if (StereoLevel == 1) StereoLevel = 30; else StereoLevel = 0;
              }
            } else {
              StereoLevel --;
              if (StereoLevel < 30 || StereoLevel > 60) {
                if (StereoLevel > 60) StereoLevel = 60; else StereoLevel = 0;
              }
            }

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            if (StereoLevel != 0) OneBigLineSprite.drawString("dBµV", 155, 0);
            if (StereoLevel != 0) OneBigLineSprite.setTextDatum(TR_DATUM); else OneBigLineSprite.setTextDatum(TC_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((StereoLevel != 0 ? String(StereoLevel, DEC) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            radio.setStereoLevel(StereoLevel);
            break;

          case ITEM5:
            if (dir) {
              HighCutLevel ++;
              if (HighCutLevel > 70) HighCutLevel = 15;
            } else {
              HighCutLevel --;
              if (HighCutLevel < 15 || HighCutLevel > 70) HighCutLevel = 70;
            }

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
            if (dir) {
              HighCutOffset ++;

              if (HighCutOffset > 60 || HighCutOffset <= 20) {
                if (HighCutOffset == 1) HighCutOffset = 20; else HighCutOffset = 0;
              }
            } else {
              HighCutOffset --;
              if (HighCutOffset < 20 || HighCutOffset > 60) {
                if (HighCutOffset > 60) HighCutOffset = 60; else HighCutOffset = 0;
              }
            }

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            if (HighCutOffset != 0) OneBigLineSprite.drawString("dBµV", 155, 0);
            if (HighCutOffset != 0) OneBigLineSprite.setTextDatum(TR_DATUM); else OneBigLineSprite.setTextDatum(TC_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((HighCutOffset != 0 ? String(HighCutOffset, DEC) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            radio.setHighCutOffset(HighCutOffset);
            break;

          case ITEM7:
            if (dir) {
              fmdeemphasis++;
              if (fmdeemphasis > DEEMPHASIS_COUNT - 1) fmdeemphasis = DEEMPHASIS_NONE;
            } else {
              fmdeemphasis--;
              if (fmdeemphasis > DEEMPHASIS_COUNT - 1) fmdeemphasis = DEEMPHASIS_COUNT - 1;
            }

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            if (fmdeemphasis != DEEMPHASIS_NONE) OneBigLineSprite.drawString("μs", 155, 0);
            if (fmdeemphasis != DEEMPHASIS_NONE) OneBigLineSprite.setTextDatum(TR_DATUM); else OneBigLineSprite.setTextDatum(TC_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((fmdeemphasis != DEEMPHASIS_NONE ? (fmdeemphasis == DEEMPHASIS_50 ? String(FM_DEEMPHASIS_50, DEC) : String(FM_DEEMPHASIS_75, DEC)) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            radio.setDeemphasis(fmdeemphasis);
            break;
        }
        break;

      case DISPLAYSETTINGS:
        switch (menuoption) {
          case ITEM1:
            if (dir) {
              language ++;
              if (language == language_totalnumber) language = 0;
            } else {
              language --;
              if (language > language_totalnumber) language = language_totalnumber - 1;
            }

            UpdateFonts(0);
            OneBigLineSprite.drawString(textUI(0), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM2:
            if (dir) {
              ContrastSet ++;
              if (ContrastSet > 100) ContrastSet = 1;
            } else {
              ContrastSet --;
              if (ContrastSet < 1) ContrastSet = 100;
            }

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

            OneBigLineSprite.drawString((showmodulation ? textUI(31) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM4:
            if (dir) {
              screensaverset ++;
              if (screensaverset > sizeof(screensaverOptions) / sizeof(screensaverOptions[0]) - 1) screensaverset = 0;
            } else {
              screensaverset --;
              if (screensaverset > sizeof(screensaverOptions) / sizeof(screensaverOptions[0]) - 1) screensaverset = sizeof(screensaverOptions) / sizeof(screensaverOptions[0]) - 1;
            }

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            if (screensaverset) OneBigLineSprite.drawString(textUI(92), 155, 0);
            if (screensaverset) OneBigLineSprite.setTextDatum(TR_DATUM); else OneBigLineSprite.setTextDatum(TC_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((screensaverset ? String(screensaverOptions[screensaverset], DEC) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM5:
            if (dir) {
              poweroptions++;
              if (poweroptions > RADIO_POWER_MODE_CNT - 1) poweroptions = 0;
            } else {
              poweroptions--;
              if (poweroptions > RADIO_POWER_MODE_CNT - 1) poweroptions = RADIO_POWER_MODE_CNT - 1;
            }

            switch (poweroptions) {
              case LCD_OFF: OneBigLineSprite.drawString(textUI(76), 135, 0); break;
              case LCD_BRIGHTNESS_1_PERCENT: OneBigLineSprite.drawString(textUI(94), 135, 0); break;
              case LCD_BRIGHTNESS_A_QUARTER: OneBigLineSprite.drawString(textUI(95), 135, 0); break;
              case LCD_BRIGHTNESS_HALF: OneBigLineSprite.drawString(textUI(96), 135, 0); break;
            }

            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM6:
            if (dir) {
              batteryoptions++;
              if (batteryoptions > RADIO_BATTERY_CNT - 1) batteryoptions = 0;
            } else {
              batteryoptions--;
              if (batteryoptions > RADIO_BATTERY_CNT - 1) batteryoptions = RADIO_BATTERY_CNT - 1;
            }

            switch (batteryoptions) {
              case BATTERY_NONE: OneBigLineSprite.drawString(textUI(30), 135, 0); break;
              case BATTERY_VALUE: OneBigLineSprite.drawString(textUI(174), 135, 0); break;
              case BATTERY_PERCENT: OneBigLineSprite.drawString(textUI(175), 135, 0); break;
            }

            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM7:
            if (dir) {
              unit ++;
              if (unit > sizeof(unitString) / sizeof(unitString[0]) - 1) unit = 0;
            } else {
              unit --;
              if (unit > sizeof(unitString) / sizeof(unitString[0]) - 1) unit = sizeof(unitString) / sizeof(unitString[0]) - 1;
            }

            OneBigLineSprite.drawString(unitString[unit], 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM8:
            showclock = !showclock;

            OneBigLineSprite.drawString((showclock ? textUI(31) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM9:
            if (dir) {
              CurrentTheme ++;
              if (CurrentTheme > sizeof(Theme) / sizeof(Theme[0]) - 1) CurrentTheme = 0;
            } else {
              CurrentTheme --;
              if (CurrentTheme > sizeof(Theme) / sizeof(Theme[0]) - 1) CurrentTheme = sizeof(Theme) / sizeof(Theme[0]) - 1;
            }

            doTheme();
            switch (CurrentTheme) {
              case 7:
                OneBigLineSprite.pushImage(-11, -88, 292, 170, popupbackground_wo);
                tft.pushImage (13, 30, 292, 170, popupbackground_wo);
                break;
              default:
                OneBigLineSprite.pushImage(-11, -88, 292, 170, popupbackground);
                tft.pushImage (13, 30, 292, 170, popupbackground);
                break;
            }

            showMenuOpenTouchButtons();
            tft.drawRoundRect(10, 30, 300, 170, 5, ActiveColor);
            Infoboxprint(textUI(77));
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(Theme[CurrentTheme], 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            showMenuOpenTouchButtons();
            break;

          case ITEM10:
            if (dir) {
              freqfont ++;
              if (freqfont > sizeof(FreqFont) / sizeof(FreqFont[0]) - 1) freqfont = 0;
            } else {
              freqfont --;
              if (freqfont > sizeof(FreqFont) / sizeof(FreqFont[0]) - 1) freqfont = sizeof(FreqFont) / sizeof(FreqFont[0]) - 1;
            }

            OneBigLineSprite.drawString(FreqFont[freqfont], 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;
        }
        break;

      case RDSSETTINGS:
        switch (menuoption) {
          case ITEM1:
            if (dir) {
              showrdserrors++;
              if (showrdserrors > 2) showrdserrors = 0;
            } else {
              showrdserrors--;
              if (showrdserrors > 2) showrdserrors = 2;
            }

            switch (showrdserrors) {
              case 0: OneBigLineSprite.drawString(textUI(30), 135, 0); break;
              case 1: OneBigLineSprite.drawString(textUI(200), 135, 0); break;
              case 2: OneBigLineSprite.drawString(textUI(201), 135, 0); break;
            }
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM2:
            if (dir) {
              radio.rds.region++;
              if (radio.rds.region > 3) radio.rds.region = 0;
            } else {
              radio.rds.region--;
              if (radio.rds.region > 3) radio.rds.region = 3;
            }

            switch (radio.rds.region) {
              case 0: OneBigLineSprite.drawString(textUI(47), 135, 0); break;
              case 1: OneBigLineSprite.drawString(String(textUI(48)) + " DB", 135, 0); break;
              case 2: OneBigLineSprite.drawString(textUI(48), 135, 0); break;
              case 3: OneBigLineSprite.drawString(textUI(300), 135, 0); break;
            }
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM3:
            if (dir) {
              radio.underscore++;
              if (radio.underscore > 2) radio.underscore = 0;
            } else {
              radio.underscore--;
              if (radio.underscore > 2) radio.underscore = 2;
            }

            switch (radio.underscore) {
              case 0: OneBigLineSprite.drawString(textUI(30), 135, 0); break;
              case 1: OneBigLineSprite.drawString(textUI(50), 135, 0); break;
              case 2: OneBigLineSprite.drawString(textUI(31), 135, 0); break;
            }
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM4:
            radio.rds.filter = !radio.rds.filter;

            OneBigLineSprite.drawString((radio.rds.filter ? textUI(31) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM5:
            radio.rds.pierrors = !radio.rds.pierrors;

            OneBigLineSprite.drawString((radio.rds.pierrors ? textUI(31) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM6:
            if (dir) {
              af++;
              if (af > 2) af = 0;
            } else {
              af--;
              if (af > 2) af = 2;
            }

            switch (af) {
              case 0: OneBigLineSprite.drawString(textUI(30), 135, 0); break;
              case 1: OneBigLineSprite.drawString(String(textUI(31)) + " / REG " + String(textUI(31)), 135, 0); break;
              case 2: OneBigLineSprite.drawString(String(textUI(31)) + " / REG " + String(textUI(30)), 135, 0); break;
            }

            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM7:
            radio.rds.rtbuffer = !radio.rds.rtbuffer;

            OneBigLineSprite.drawString((radio.rds.rtbuffer ? textUI(31) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM8:
            radio.rds.sortaf = !radio.rds.sortaf;

            OneBigLineSprite.drawString((radio.rds.sortaf ? textUI(31) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM9:
            if (dir) {
              radio.rds.fastps++;
              if (radio.rds.fastps > 2) radio.rds.fastps = 0;
            } else {
              radio.rds.fastps--;
              if (radio.rds.fastps > 2) radio.rds.fastps = 2;
            }

            switch (radio.rds.fastps) {
              case 0: OneBigLineSprite.drawString(textUI(30), 135, 0); break;
              case 1: OneBigLineSprite.drawString(textUI(260), 135, 0); break;
              case 2: OneBigLineSprite.drawString(textUI(261), 135, 0); break;
            }

            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM10:
            showlongps = !showlongps;

            OneBigLineSprite.drawString((showlongps ? textUI(31) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;
        }
        break;

      case FMSETTINGS:
        switch (menuoption) {
          case ITEM1:
            if (dir) {
              ConverterSet++;
              if (ConverterSet > 2400 || ConverterSet <= 200) {
                if (ConverterSet == 1) ConverterSet = 200; else ConverterSet = 0;
              }
            } else {
              ConverterSet--;
              if (ConverterSet < 200 || ConverterSet > 2400) {
                if (ConverterSet > 2400) ConverterSet = 2400; else ConverterSet = 0;
              }
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
            if (dir) {
              LowEdgeSet ++;
              if (LowEdgeSet > 1070) (TEF == 205 ? LowEdgeSet = 640 : LowEdgeSet = 650);
            } else {
              LowEdgeSet -= 10;
              if ((TEF == 205 ? LowEdgeSet < 640 : LowEdgeSet < 650)) LowEdgeSet = 1079;
            }

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("MHz", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(LowEdgeSet / 10 + ConverterSet, DEC) + "." + String(LowEdgeSet % 10 + ConverterSet, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM3:
            if (dir) {
              HighEdgeSet ++;
              if (HighEdgeSet > 1080) HighEdgeSet = 660;
            } else {
              HighEdgeSet -= 10;
              if (HighEdgeSet < 660) HighEdgeSet = 1080;
            }

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("MHz", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(HighEdgeSet / 10 + ConverterSet, DEC) + "." + String(HighEdgeSet % 10 + ConverterSet, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM4:
            if (dir) {
              LevelOffset++;
              if (LevelOffset > 15) LevelOffset = -25;
            } else {
              LevelOffset--;
              if (LevelOffset < -25) LevelOffset = 15;
            }

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("dB", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((LevelOffset > 0 ? "+" : "") + String(LevelOffset, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            radio.setOffset(LevelOffset);
            change = true;
            break;

          case ITEM5:
            if (dir) {
              LowLevelSet++;
              if (LowLevelSet > 30) LowLevelSet = -15;
            } else {
              LowLevelSet--;
              if (LowLevelSet < -15) LowLevelSet = 30;
            }

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

            OneBigLineSprite.drawString((softmutefm ? textUI(31) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            radio.setSoftmuteFM(softmutefm);
            break;

          case ITEM7:
            if (dir) {
              fmnb ++;
              if (fmnb > 150 || fmnb <= 50) {
                if (fmnb == 1) fmnb = 50; else fmnb = 0;
              }
            } else {
              fmnb --;
              if (fmnb > 150 || fmnb <= 50) {
                if (fmnb > 150) fmnb = 150; else fmnb = 0;
              }
            }

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            if (fmnb != 0) OneBigLineSprite.drawString("%", 155, 0);
            if (fmnb != 0) OneBigLineSprite.setTextDatum(TR_DATUM); else OneBigLineSprite.setTextDatum(TC_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((fmnb != 0 ? String(fmnb, DEC) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            radio.setFMNoiseBlanker(fmnb);
            break;

          case ITEM8:
            if (dir) {
              fmdefaultstepsize++;
              if (fmdefaultstepsize > 2) fmdefaultstepsize = 0;
            } else {
              fmdefaultstepsize--;
              if (fmdefaultstepsize > 2) fmdefaultstepsize = 2;
            }

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
              OneBigLineSprite.drawString((fmsi ? textUI(31) : textUI(30)), 135, 0);
              OneBigLineSprite.pushSprite(24, 118);
              if (fmsi) radio.setFMSI(2); else radio.setFMSI(1);
            }
            break;

          case ITEM10:
            if (dir) {
              fmscansens++;
              if (fmscansens > 30) fmscansens = 1;
            } else {
              fmscansens--;
              if (fmscansens == 0) fmscansens = 30;
            }

            OneBigLineSprite.drawString(String(fmscansens), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;
        }
        break;

      case AMSETTINGS:
        switch (menuoption) {
          case ITEM1:
            softmuteam = !softmuteam;

            OneBigLineSprite.drawString((softmuteam ? textUI(31) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            radio.setSoftmuteAM(softmuteam);
            break;

          case ITEM2:
            if (dir) {
              amnb ++;
              if (amnb > 150 || amnb <= 50) {
                if (amnb == 1) amnb = 50; else amnb = 0;
              }
            } else {
              amnb --;
              if (amnb > 150 || amnb <= 50) {
                if (amnb > 150) amnb = 150; else amnb = 0;
              }
            }

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            if (amnb != 0) OneBigLineSprite.drawString("%", 155, 0);
            if (amnb != 0) OneBigLineSprite.setTextDatum(TR_DATUM); else OneBigLineSprite.setTextDatum(TC_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((amnb != 0 ? String(amnb, DEC) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            radio.setAMNoiseBlanker(amnb);
            break;

          case ITEM3:
            if (dir) {
              AMLevelOffset++;
              if (AMLevelOffset > 15) AMLevelOffset = -50;
            } else {
              AMLevelOffset--;
              if (AMLevelOffset < -50) AMLevelOffset = 15;
            }

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

            OneBigLineSprite.drawString((showSWMIBand ? textUI(31) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM5:
            if (dir) {
              amcodect++;
              if (amcodect > 150 || amcodect <= 50) {
                if (amcodect == 1) amcodect = 50; else amcodect = 0;
              }
            } else {
              amcodect--;
              if (amcodect < 50 || amcodect > 150) {
                if (amcodect > 150) amcodect = 150; else amcodect = 0;
              }
            }

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            if (amcodect != 0) OneBigLineSprite.drawString("%", 155, 0);
            if (amcodect != 0) OneBigLineSprite.setTextDatum(TR_DATUM); else OneBigLineSprite.setTextDatum(TC_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((amcodect != 0 ? String(amcodect, DEC) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            if (band > BAND_GAP) radio.setAMCoChannel(amcodect, amcodectcount);
            break;

          case ITEM6:
            if (dir) {
              amcodectcount++;
              if (amcodectcount > 15) amcodectcount = 1;
            } else {
              amcodectcount--;
              if (amcodectcount < 1) amcodectcount = 15;
            }

            OneBigLineSprite.drawString(String(amcodectcount, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            if (band > BAND_GAP) radio.setAMCoChannel(amcodect, amcodectcount);
            break;

          case ITEM7:
            if (dir) {
              amgain += 6;
              if (amgain > 36) amgain = 0;
            } else {
              amgain -= 6;
              if (amgain > 36) amgain = 36;
            }

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            if (amgain != 0) OneBigLineSprite.drawString("dB", 155, 0);
            if (amgain != 0) OneBigLineSprite.setTextDatum(TR_DATUM); else OneBigLineSprite.setTextDatum(TC_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((amgain != 0 ? String(amgain, DEC) : textUI(30)), 135, 0);
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
            if (dir) {
              amscansens++;
              if (amscansens > 30) amscansens = 1;
            } else {
              amscansens--;
              if (amscansens == 0) amscansens = 30;
            }

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

            OneBigLineSprite.drawString((wifi ? textUI(31) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM4:
            if (dir) {
              subnetclient ++;
              if (subnetclient > 254) subnetclient = 1;
            } else {
              subnetclient --;
              if (subnetclient < 1) subnetclient = 254;
            }

            OneBigLineSprite.drawString(String(WiFi.localIP()[0]) + "." + String(WiFi.localIP()[1]) + "." + String(WiFi.localIP()[2]) + "." + String(subnetclient, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM5:
            if (dir) {
              stationlistid ++;
              if (stationlistid > 10) stationlistid = 1;
            } else {
              stationlistid --;
              if (stationlistid == 0) stationlistid = 10;
            }

            OneBigLineSprite.drawString(String(stationlistid, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM6:
            XDRGTKMuteScreen = !XDRGTKMuteScreen;

            OneBigLineSprite.drawString((XDRGTKMuteScreen ? textUI(31) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM7:
            if (dir) {
              NTPoffset++;
              if (NTPoffset > 12) NTPoffset = -12;
            } else {
              NTPoffset--;
              if (NTPoffset < -12) NTPoffset = 12;
            }

            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("GMT", 135, 0);
            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((NTPoffset > -1 ? "+" : "") + String(NTPoffset), 155, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM8:
            autoDST = !autoDST;

            OneBigLineSprite.drawString((autoDST ? textUI(31) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM9:
            clockampm = !clockampm;

            OneBigLineSprite.drawString((clockampm ? "12" : "24"), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM10:
            char PICT[5];
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);

            if (radio.rds.PICTlock != 0) {
              OneBigLineSprite.setTextDatum(TC_DATUM);
              OneBigLineSprite.drawString(textUI(30), 135, 0);
              radio.rds.PICTlock = 0;
            } else {
              if (radio.rds.correctPI != 0) {
                radio.rds.PICTlock = radio.rds.correctPI;
                sprintf(PICT, "%04X", radio.rds.PICTlock);
                OneBigLineSprite.setTextDatum(TR_DATUM);
                OneBigLineSprite.drawString(textUI(31), 135, 0);
                OneBigLineSprite.setTextDatum(TL_DATUM);
                OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
                OneBigLineSprite.drawString(String(PICT), 155, 0);
              } else {
                OneBigLineSprite.setTextDatum(TC_DATUM);
                OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
                OneBigLineSprite.drawString(textUI(42), 135, 0);
              }
            }
            OneBigLineSprite.pushSprite(24, 118);
            break;
        }
        break;

      case DXMODE:
        switch (menuoption) {
          case ITEM2:
            if (dir) {
              scanstart++;
              if (scanstart >= scanstop) scanstart = 0;
            } else {
              scanstart--;
              if (scanstart >= scanstop) scanstart = scanstop - 1;
            }

            OneBigLineSprite.drawString(String(scanstart + 1, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM3:
            if (dir) {
              scanstop++;
              if (scanstop > EE_PRESETS_CNT - 1) scanstop = scanstart + 1;
            } else {
              scanstop--;
              if (scanstop <= scanstart) scanstop = EE_PRESETS_CNT - 1;
            }

            OneBigLineSprite.drawString(String(scanstop + 1, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM4:
            if (dir) {
              scanhold++;
              if (scanhold > 30) scanhold = 0;
            } else {
              scanhold--;
              if (scanhold > 30) scanhold = 30;
            }

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString(textUI(92), 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((scanhold == 0 ? "0.5" : String(scanhold, DEC)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM5:
            scanmem = !scanmem;
            OneBigLineSprite.drawString((scanmem ? textUI(218) : textUI(217)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM6:
            if (dir) {
              scancancel++;
              if (scancancel > 2) scancancel = 0;
            } else {
              scancancel--;
              if (scancancel > 2) scancancel = 2;
            }

            switch (scancancel) {
              case OFF:  OneBigLineSprite.drawString(textUI(30), 135, 0); break;
              case CORRECTPI: OneBigLineSprite.drawString(textUI(220), 135, 0); break;
              case SIGNAL: OneBigLineSprite.drawString(textUI(221), 135, 0); break;
            }
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM7:
            scanmute = !scanmute;

            OneBigLineSprite.drawString((scanmute ? textUI(31) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM8:
            autolog = !autolog;

            OneBigLineSprite.drawString((autolog ? textUI(31) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM9:
            scanholdonsignal = !scanholdonsignal;

            OneBigLineSprite.drawString((scanholdonsignal ? textUI(31) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;
        }
        break;

      case AUTOMEM:
        switch (menuoption) {
          case ITEM2:
            if (dir) {
              memstartfreq ++;
              if (memstartfreq > 1070) (TEF == 205 ? memstartfreq = 640 : memstartfreq = 650);
            } else {
              memstartfreq -= 10;
              if ((TEF == 205 ? memstartfreq < 640 : memstartfreq < 650)) memstartfreq = 1079;
            }

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("MHz", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(memstartfreq / 10 + ConverterSet, DEC) + "." + String(memstartfreq % 10 + ConverterSet, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM3:
            if (dir) {
              memstopfreq ++;
              if (memstopfreq > 1080) memstopfreq = 660;
            } else {
              memstopfreq -= 10;
              if (memstopfreq < 660) memstopfreq = 1080;
            }

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("MHz", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(memstopfreq / 10 + ConverterSet, DEC) + "." + String(memstopfreq % 10 + ConverterSet, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM4:
            if (dir) {
              memstartpos++;
              if (memstartpos >= memstoppos) memstartpos = 0;
            } else {
              memstartpos--;
              if (memstartpos >= memstoppos) memstartpos = scanstop - 1;
            }

            OneBigLineSprite.drawString(String(memstartpos + 1, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM5:
            if (dir) {
              memstoppos++;
              if (memstoppos > EE_PRESETS_CNT - 1) memstoppos = memstartpos + 1;
            } else {
              memstoppos--;
              if (memstoppos <= memstartpos) memstoppos = EE_PRESETS_CNT - 1;
            }

            OneBigLineSprite.drawString(String(memstoppos + 1, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM6:
            mempionly = !mempionly;

            OneBigLineSprite.drawString((mempionly ? textUI(31) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM7:
            if (dir) {
              memdoublepi++;
              if (memdoublepi > 2) memdoublepi = 0;
            } else {
              memdoublepi--;
              if (memdoublepi > 2) memdoublepi = 2;
            }

            switch (memdoublepi) {
              case MEMPI_OFF: OneBigLineSprite.drawString(textUI(30), 135, 0); break;
              case MEMPI_RANGE: OneBigLineSprite.drawString(textUI(279), 135, 0); break;
              default: OneBigLineSprite.drawString(textUI(280), 135, 0); break;
            }
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM8:
            if (dir) {
              fmscansens++;
              if (fmscansens > 30) fmscansens = 1;
            } else {
              fmscansens--;
              if (fmscansens == 0) fmscansens = 30;
            }

            OneBigLineSprite.drawString(String(fmscansens), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;
        }
        break;
    }
  }
}

void showMenuOpenTouchButtons() {
  if (hardwaremodel == PORTABLE_TOUCH_ILI9341 && !((menupage == CONNECTIVITY && menuoption == ITEM3) || (menupage == AUTOMEM && (menuoption == ITEM1 || menuoption == ITEM9)) || (menupage == MAINSETTINGS && menuoption == ITEM1) || (menupage == DXMODE && menuoption == ITEM10))) {
    tft.fillRoundRect(18, 154, 60, 40, 6, FrameColor);
    tft.drawRoundRect(18, 154, 60, 40, 6, ActiveColor);
    tft.fillRoundRect(240, 154, 60, 40, 6, FrameColor);
    tft.drawRoundRect(240, 154, 60, 40, 6, ActiveColor);
    tft.fillTriangle(52, 160, 52, 188, 38, 174, (CurrentTheme == 7 ? White : ActiveColor));
    tft.fillTriangle(266, 160, 266, 188, 280, 174, (CurrentTheme == 7 ? White : ActiveColor));
    if (!submenu && menuoption == ITEM9) {
      tft.fillRoundRect(240, 36, 60, 40, 6, FrameColor);
      tft.drawRoundRect(240, 36, 60, 40, 6, ActiveColor);
      tftPrint(0, "OK", 270, 44, (CurrentTheme == 7 ? White : ActiveColor), ActiveColorSmooth, 28);
    } else {
      tft.fillRoundRect(130, 154, 60, 40, 6, FrameColor);
      tft.drawRoundRect(130, 154, 60, 40, 6, ActiveColor);
      tftPrint(0, "OK", 160, 162, (CurrentTheme == 7 ? White : ActiveColor), ActiveColorSmooth, 28);
    }
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

      if (menupage == CONNECTIVITY && menuoption == ITEM3) {
        switch (CurrentTheme) {
          case 7: tft.pushImage (0, 0, 320, 240, configurationbackground_wo); break;
          default: tft.pushImage (0, 0, 320, 240, configurationbackground); break;
        }
        tftPrint(0, textUI(189 + menupage - 1), 160, 6, ActiveColor, ActiveColorSmooth, 16);
      }
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
            tftPrint(0, textUI(71), 155, 13, ActiveColor, ActiveColorSmooth, 28);
            tftPrint(0, textUI(72), 155, 55, ActiveColor, ActiveColorSmooth, 28);
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
            if (hardwaremodel == PORTABLE_TOUCH_ILI9341) {
              tft.fillRoundRect(240, 36, 60, 40, 6, FrameColor);
              tft.drawRoundRect(240, 36, 60, 40, 6, ActiveColor);
              tftPrint(0, "OK", 270, 44, (CurrentTheme == 7 ? White : ActiveColor), ActiveColorSmooth, 28);
            }
            break;
        }
        break;

      case MAINSETTINGS:
        switch (menuoption) {
          case ITEM1:
            Infoboxprint(textUI(108));

            switch (hardwaremodel) {
              case BASE_ILI9341: OneBigLineSprite.drawString(textUI(109), 135, 0); break;
              case PORTABLE_ILI9341: OneBigLineSprite.drawString(textUI(110), 135, 0); break;
              case PORTABLE_TOUCH_ILI9341: OneBigLineSprite.drawString(textUI(111), 135, 0); break;
            }

            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM2:
            Infoboxprint(textUI(68));

            OneBigLineSprite.drawString((touchrotating ? textUI(31) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM3:
            Infoboxprint(textUI(75));

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);

            if (tot != 0) {
              OneBigLineSprite.drawString(textUI(80), 150, 0);
              OneBigLineSprite.setTextDatum(TR_DATUM);
              OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
              OneBigLineSprite.drawString(String(tot), 135, 0);
            } else {
              OneBigLineSprite.setTextDatum(TC_DATUM);
              OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
              OneBigLineSprite.drawString(textUI(30), 135, 0);
            }

            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM4:
            Infoboxprint(textUI(62));
            if (autosquelch) OneBigLineSprite.drawString(textUI(86), 135, 0); else OneBigLineSprite.drawString((usesquelch ? textUI(31) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM5:
            Infoboxprint(textUI(37));

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("dBµV", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(fmagc), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM6:
            Infoboxprint(textUI(198));

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("dBµV", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(amagc), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM7:
            Infoboxprint(textUI(100));

            switch (bandFM) {
              case FM_BAND_ALL: OneBigLineSprite.drawString(textUI(105) + String(",") + textUI(106), 135, 0); break;
              case FM_BAND_OIRT: OneBigLineSprite.drawString(textUI(106), 135, 0); break;
              case FM_BAND_FM: OneBigLineSprite.drawString(textUI(105), 135, 0); break;
              case FM_BAND_NONE: OneBigLineSprite.drawString(textUI(83), 135, 0); break;
            }
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM8:
            Infoboxprint(textUI(101));

#ifdef HAS_AIR_BAND
            switch (bandAM) {
              case AM_BAND_ALL: OneBigLineSprite.drawString(textUI(102) + String(",") + textUI(103) + String(",") + textUI(104) + String(",") + textUI(223), 135, 0); break;
              case AM_BAND_LW_MW_SW: OneBigLineSprite.drawString(textUI(102) + String(",") + textUI(103) + String(",") + textUI(104), 135, 0); break;
              case AM_BAND_LW_MW_AIR: OneBigLineSprite.drawString(textUI(102) + String(",") + textUI(103) + String(",") + textUI(223), 135, 0); break;
              case AM_BAND_LW_SW_AIR: OneBigLineSprite.drawString(textUI(102) + String(",") + textUI(104) + String(",") + textUI(223), 135, 0); break;
              case AM_BAND_MW_SW_AIR: OneBigLineSprite.drawString(textUI(103) + String(",") + textUI(104) + String(",") + textUI(223), 135, 0); break;
              case AM_BAND_LW_MW: OneBigLineSprite.drawString(textUI(102) + String(",") + textUI(103), 135, 0); break;
              case AM_BAND_LW_SW: OneBigLineSprite.drawString(textUI(102) + String(",") + textUI(104), 135, 0); break;
              case AM_BAND_LW_AIR: OneBigLineSprite.drawString(textUI(102) + String(",") + textUI(223), 135, 0); break;
              case AM_BAND_MW_SW: OneBigLineSprite.drawString(textUI(103) + String(",") + textUI(104), 135, 0); break;
              case AM_BAND_MW_AIR: OneBigLineSprite.drawString(textUI(103) + String(",") + textUI(223), 135, 0); break;
              case AM_BAND_SW_AIR: OneBigLineSprite.drawString(textUI(104) + String(",") + textUI(223), 135, 0); break;
              case AM_BAND_LW: OneBigLineSprite.drawString(textUI(102), 135, 0); break;
              case AM_BAND_MW: OneBigLineSprite.drawString(textUI(103), 135, 0); break;
              case AM_BAND_SW: OneBigLineSprite.drawString(textUI(104), 135, 0); break;
              case AM_BAND_AIR: OneBigLineSprite.drawString(textUI(223), 135, 0); break;
              case AM_BAND_NONE: OneBigLineSprite.drawString(textUI(83), 135, 0); break;
            }
#else
            switch (bandAM) {
              case AM_BAND_ALL: OneBigLineSprite.drawString(textUI(102) + String(",") + textUI(103) + String(",") + textUI(104), 135, 0); break;
              case AM_BAND_LW_MW: OneBigLineSprite.drawString(textUI(102) + String(",") + textUI(103), 135, 0); break;
              case AM_BAND_LW_SW: OneBigLineSprite.drawString(textUI(102) + String(",") + textUI(104), 135, 0); break;
              case AM_BAND_MW_SW: OneBigLineSprite.drawString(textUI(103) + String(",") + textUI(104), 135, 0); break;
              case AM_BAND_LW: OneBigLineSprite.drawString(textUI(102), 135, 0); break;
              case AM_BAND_MW: OneBigLineSprite.drawString(textUI(103), 135, 0); break;
              case AM_BAND_SW: OneBigLineSprite.drawString(textUI(104), 135, 0); break;
              case AM_BAND_NONE: OneBigLineSprite.drawString(textUI(83), 135, 0); break;
            }
#endif
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM9:
            Infoboxprint(textUI(224));

            switch (longbandpress) {
              case STANDBY: OneBigLineSprite.drawString(textUI(225), 135, 0); break;
              case SCREENOFF: OneBigLineSprite.drawString(textUI(226), 135, 0); break;
              default: OneBigLineSprite.drawString(textUI(227), 135, 0); break;
            }
            OneBigLineSprite.pushSprite(24, 118);
            break;


          case ITEM10:
            Infoboxprint(textUI(81));

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
              OneBigLineSprite.drawString(textUI(86), 135, 0);
            } else {
              OneBigLineSprite.drawString((spispeed == SPI_SPEED_DEFAULT ? String(textUI(204)) + " " + String(SPI_FREQUENCY / 1000000, DEC) : String(spispeed * 10, DEC)), 160, 0);
            }
            OneBigLineSprite.pushSprite(24, 118);
            break;
        }
        break;

      case AUDIOSETTINGS:
        switch (menuoption) {
          case ITEM1:
            Infoboxprint(textUI(10));

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
            Infoboxprint(textUI(45));

            OneBigLineSprite.drawString((edgebeep ? textUI(31) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM3:
            Infoboxprint(textUI(67));

            OneBigLineSprite.drawString((audiomode ? "MPX" : "Stereo"), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM4:
            Infoboxprint(textUI(15));

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            if (StereoLevel != 0) OneBigLineSprite.drawString("dBµV", 155, 0);
            if (StereoLevel != 0) OneBigLineSprite.setTextDatum(TR_DATUM); else OneBigLineSprite.setTextDatum(TC_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((StereoLevel != 0 ? String(StereoLevel, DEC) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM5:
            Infoboxprint(textUI(16));

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("Hz", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(HighCutLevel * 100, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM6:
            Infoboxprint(textUI(17));

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            if (HighCutOffset != 0) OneBigLineSprite.drawString("dBµV", 155, 0);
            if (HighCutOffset != 0) OneBigLineSprite.setTextDatum(TR_DATUM); else OneBigLineSprite.setTextDatum(TC_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((HighCutOffset != 0 ? String(HighCutOffset, DEC) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM7:
            Infoboxprint(textUI(199));

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            if (fmdeemphasis != DEEMPHASIS_NONE) OneBigLineSprite.drawString("μs", 155, 0);
            if (fmdeemphasis != DEEMPHASIS_NONE) OneBigLineSprite.setTextDatum(TR_DATUM); else OneBigLineSprite.setTextDatum(TC_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((fmdeemphasis != DEEMPHASIS_NONE ? (fmdeemphasis == DEEMPHASIS_50 ? String(FM_DEEMPHASIS_50, DEC) : String(FM_DEEMPHASIS_75, DEC)) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;
        }
        break;

      case DISPLAYSETTINGS:
        switch (menuoption) {
          case ITEM1:
            Infoboxprint(textUI(40));

            OneBigLineSprite.drawString(textUI(0), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM2:
            Infoboxprint(textUI(19));

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("%", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(ContrastSet, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM3:
            Infoboxprint(textUI(63));

            OneBigLineSprite.drawString((showmodulation ? textUI(31) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM4:
            Infoboxprint(textUI(91));

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            if (screensaverset) OneBigLineSprite.drawString(textUI(92), 155, 0);
            if (screensaverset) OneBigLineSprite.setTextDatum(TR_DATUM); else OneBigLineSprite.setTextDatum(TC_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((screensaverset ? String(screensaverOptions[screensaverset], DEC) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM5:
            Infoboxprint(textUI(74));

            switch (poweroptions) {
              case LCD_OFF: OneBigLineSprite.drawString(textUI(76), 135, 0); break;
              case LCD_BRIGHTNESS_1_PERCENT: OneBigLineSprite.drawString(textUI(94), 135, 0); break;
              case LCD_BRIGHTNESS_A_QUARTER: OneBigLineSprite.drawString(textUI(95), 135, 0); break;
              case LCD_BRIGHTNESS_HALF: OneBigLineSprite.drawString(textUI(96), 135, 0); break;
            }

            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM6:
            Infoboxprint(textUI(173));

            switch (batteryoptions) {
              case BATTERY_NONE: OneBigLineSprite.drawString(textUI(30), 135, 0); break;
              case BATTERY_VALUE: OneBigLineSprite.drawString(textUI(174), 135, 0); break;
              case BATTERY_PERCENT: OneBigLineSprite.drawString(textUI(175), 135, 0); break;
            }

            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM7:
            Infoboxprint(textUI(98));

            OneBigLineSprite.drawString(unitString[unit], 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM8:
            Infoboxprint(textUI(262));

            OneBigLineSprite.drawString((showclock ? textUI(31) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM9:
            Infoboxprint(textUI(77));

            OneBigLineSprite.drawString(Theme[CurrentTheme], 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM10:
            Infoboxprint(textUI(85));

            OneBigLineSprite.drawString(FreqFont[freqfont], 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;
        }
        break;

      case RDSSETTINGS:
        switch (menuoption) {
          case ITEM1:
            Infoboxprint(textUI(38));

            switch (showrdserrors) {
              case 0: OneBigLineSprite.drawString(textUI(30), 135, 0); break;
              case 1: OneBigLineSprite.drawString(textUI(200), 135, 0); break;
              case 2: OneBigLineSprite.drawString(textUI(201), 135, 0); break;
            }
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM2:
            Infoboxprint(textUI(46));

            switch (radio.rds.region) {
              case 0: OneBigLineSprite.drawString(textUI(47), 135, 0); break;
              case 1: OneBigLineSprite.drawString(String(textUI(48)) + " DB", 135, 0); break;
              case 2: OneBigLineSprite.drawString(textUI(48), 135, 0); break;
              case 3: OneBigLineSprite.drawString(textUI(300), 135, 0); break;
            }
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM3:
            Infoboxprint(textUI(49));

            switch (radio.underscore) {
              case 0: OneBigLineSprite.drawString(textUI(30), 135, 0); break;
              case 1: OneBigLineSprite.drawString(textUI(50), 135, 0); break;
              case 2: OneBigLineSprite.drawString(textUI(31), 135, 0); break;
            }
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM4:
            Infoboxprint(textUI(60));

            OneBigLineSprite.drawString((radio.rds.filter ? textUI(31) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM5:
            Infoboxprint(textUI(61));

            OneBigLineSprite.drawString((radio.rds.pierrors ? textUI(31) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM6:
            Infoboxprint(textUI(99));

            switch (af) {
              case 0: OneBigLineSprite.drawString(textUI(30), 135, 0); break;
              case 1: OneBigLineSprite.drawString(String(textUI(31)) + " / REG " + String(textUI(31)), 135, 0); break;
              case 2: OneBigLineSprite.drawString(String(textUI(31)) + " / REG " + String(textUI(30)), 135, 0); break;
            }

            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM7:
            Infoboxprint(textUI(176));

            OneBigLineSprite.drawString((radio.rds.rtbuffer ? textUI(31) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM8:
            Infoboxprint(textUI(215));

            OneBigLineSprite.drawString((radio.rds.sortaf ? textUI(31) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM9:
            Infoboxprint(textUI(203));

            switch (radio.rds.fastps) {
              case 0: OneBigLineSprite.drawString(textUI(30), 135, 0); break;
              case 1: OneBigLineSprite.drawString(textUI(260), 135, 0); break;
              case 2: OneBigLineSprite.drawString(textUI(261), 135, 0); break;
            }

            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM10:
            Infoboxprint(textUI(263));

            OneBigLineSprite.drawString((showlongps ? textUI(31) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;
        }
        break;

      case FMSETTINGS:
        switch (menuoption) {
          case ITEM1:
            Infoboxprint(textUI(11));

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("MHz", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(ConverterSet, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM2:
            Infoboxprint(textUI(12));

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("MHz", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(LowEdgeSet / 10 + ConverterSet, DEC) + "." + String(LowEdgeSet % 10 + ConverterSet, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM3:
            Infoboxprint(textUI(13));

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("MHz", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(HighEdgeSet / 10 + ConverterSet, DEC) + "." + String(HighEdgeSet % 10 + ConverterSet, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM4:
            Infoboxprint(textUI(14));

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("dB", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((LevelOffset > 0 ? "+" : "") + String(LevelOffset, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM5:
            Infoboxprint(textUI(18));

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("dBμV", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(LowLevelSet, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM6:
            Infoboxprint(textUI(43));

            OneBigLineSprite.drawString((softmutefm ? textUI(31) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM7:
            Infoboxprint(textUI(65));

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            if (fmnb != 0) OneBigLineSprite.drawString("%", 155, 0);
            if (fmnb != 0) OneBigLineSprite.setTextDatum(TR_DATUM); else OneBigLineSprite.setTextDatum(TC_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((fmnb != 0 ? String(fmnb, DEC) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM8:
            Infoboxprint(textUI(90));

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
              Infoboxprint(textUI(206));

              OneBigLineSprite.drawString((fmsi ? textUI(31) : textUI(30)), 135, 0);
            } else {
              Infoboxprint(textUI(207));
            }
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM10:
            Infoboxprint(textUI(82));

            OneBigLineSprite.drawString(String(fmscansens), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;
        }
        break;

      case AMSETTINGS:
        switch (menuoption) {
          case ITEM1:
            Infoboxprint(textUI(44));

            OneBigLineSprite.drawString((softmuteam ? textUI(31) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM2:
            Infoboxprint(textUI(64));

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            if (amnb != 0) OneBigLineSprite.drawString("%", 155, 0);
            if (amnb != 0) OneBigLineSprite.setTextDatum(TR_DATUM); else OneBigLineSprite.setTextDatum(TC_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((amnb != 0 ? String(amnb, DEC) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM3:
            Infoboxprint(textUI(97));

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("dB", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((AMLevelOffset > 0 ? "+" : "") + String(AMLevelOffset, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM4:
            Infoboxprint(textUI(59));

            OneBigLineSprite.drawString((showSWMIBand ? textUI(31) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM5:
            Infoboxprint(textUI(186));

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            if (amcodect != 0) OneBigLineSprite.drawString("%", 155, 0);
            if (amcodect != 0) OneBigLineSprite.setTextDatum(TR_DATUM); else OneBigLineSprite.setTextDatum(TC_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((amcodect != 0 ? String(amcodect, DEC) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM6:
            Infoboxprint(textUI(188));

            OneBigLineSprite.drawString(String(amcodectcount, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM7:
            Infoboxprint(textUI(36));

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            if (amgain != 0) OneBigLineSprite.drawString("dB", 155, 0);
            if (amgain != 0) OneBigLineSprite.setTextDatum(TR_DATUM); else OneBigLineSprite.setTextDatum(TC_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((amgain != 0 ? String(amgain, DEC) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM8:
            Infoboxprint(textUI(169));

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("kHz", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((mwstepsize ? "10" : "9"), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM9:
            Infoboxprint(textUI(82));

            OneBigLineSprite.drawString(String(amscansens, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;
        }
        break;

      case CONNECTIVITY:
        switch (menuoption) {
          case ITEM1:
            Infoboxprint(textUI(5));

            OneBigLineSprite.drawString((USBmode ? "RDS Spy" : "XDRGTK"), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM2:
            Infoboxprint(textUI(51));

            OneBigLineSprite.drawString((wifi ? textUI(31) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM3: {
              tftPrint(0, textUI(53), 155, 58, ActiveColor, ActiveColorSmooth, 28);
              tftPrint(0, "ESP_" + String(ESP_getChipId()), 155, 98, PrimaryColor, PrimaryColorSmooth, 28);
              tftPrint(0, textUI(54), 155, 138, ActiveColor, ActiveColorSmooth, 28);
              tftPrint(0, "http://192.168.4.1", 155, 174, PrimaryColor, PrimaryColorSmooth, 16);
              char key [9];
              XDRGTK_key.toCharArray(key, 9);
              char rabbitearsuser [9];
              RabbitearsUser.toCharArray(rabbitearsuser, 9);
              char rabbitearspw [9];
              RabbitearsPassword.toCharArray(rabbitearspw, 9);
              UpdateFonts(1);
              if (wifi) {
                wifi = false;
                tryWiFi();
              }
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
              Infoboxprint(textUI(58));

              OneBigLineSprite.drawString(String(WiFi.localIP()[0]) + "." + String(WiFi.localIP()[1]) + "." + String(WiFi.localIP()[2]) + "." + String(subnetclient, DEC), 135, 0);
              OneBigLineSprite.pushSprite(24, 118);
            } else {
              menuopen = false;
              BuildMenu();
            }
            break;

          case ITEM5:
            Infoboxprint(textUI(271));

            OneBigLineSprite.drawString(String(stationlistid, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM6:
            Infoboxprint(textUI(205));

            OneBigLineSprite.drawString((XDRGTKMuteScreen ? textUI(31) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM7:
            Infoboxprint(textUI(298));

            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("GMT", 135, 0);
            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((NTPoffset > -1 ? "+" : "") + String(NTPoffset), 155, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM8:
            Infoboxprint(textUI(297));

            OneBigLineSprite.drawString((autoDST ? textUI(31) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM9:
            Infoboxprint(textUI(93));

            OneBigLineSprite.drawString((clockampm ? "12" : "24"), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM10:
            Infoboxprint(textUI(41));

            char PICT[5];
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);

            if (radio.rds.PICTlock == 0) {
              OneBigLineSprite.setTextDatum(TC_DATUM);
              OneBigLineSprite.drawString(textUI(30), 135, 0);
            } else {
              sprintf(PICT, "%04X", radio.rds.PICTlock);
              OneBigLineSprite.setTextDatum(TR_DATUM);
              OneBigLineSprite.drawString(textUI(31), 135, 0);
              OneBigLineSprite.setTextDatum(TL_DATUM);
              OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
              OneBigLineSprite.drawString(String(PICT), 155, 0);
            }
            OneBigLineSprite.pushSprite(24, 118);
        }
        break;

      case DXMODE:
        switch (menuoption) {
          case ITEM1:
            if (presets[scanstart].band == BAND_FM && presets[scanstart].frequency == EE_PRESETS_FREQUENCY && scanmem) {
              Infoboxprint(textUI(214));
              OneBigLineSprite.pushSprite(24, 118);
            } else {
              startFMDXScan();
            }
            break;

          case ITEM2:
            Infoboxprint(textUI(209));

            OneBigLineSprite.drawString(String(scanstart + 1), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM3:
            Infoboxprint(textUI(210));

            OneBigLineSprite.drawString(String(scanstop + 1), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM4:
            Infoboxprint(textUI(211));

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString(textUI(92), 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString((scanhold == 0 ? "0.5" : String(scanhold, DEC)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM5:
            Infoboxprint(textUI(216));

            OneBigLineSprite.drawString((scanmem ? textUI(218) : textUI(217)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM6:
            Infoboxprint(textUI(219));

            switch (scancancel) {
              case OFF:  OneBigLineSprite.drawString(textUI(30), 135, 0); break;
              case CORRECTPI: OneBigLineSprite.drawString(textUI(220), 135, 0); break;
              case SIGNAL: OneBigLineSprite.drawString(textUI(221), 135, 0); break;
            }
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM7:
            Infoboxprint(textUI(222));

            OneBigLineSprite.drawString((scanmute ? textUI(31) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM8:
            Infoboxprint(textUI(296));

            OneBigLineSprite.drawString((autolog ? textUI(31) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM9:
            Infoboxprint(textUI(281));

            OneBigLineSprite.drawString((scanholdonsignal ? textUI(31) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM10:
            Infoboxprint(textUI(292));
            if (handleCreateNewLogbook()) OneBigLineSprite.drawString(textUI(293), 135, 0); else OneBigLineSprite.drawString(textUI(294), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);

            if (hardwaremodel == PORTABLE_TOUCH_ILI9341) {
              tft.fillRoundRect(130, 154, 60, 40, 6, FrameColor);
              tft.drawRoundRect(130, 154, 60, 40, 6, ActiveColor);
              tftPrint(0, "OK", 160, 162, (CurrentTheme == 7 ? White : ActiveColor), ActiveColorSmooth, 28);
            }
            break;
        }
        break;

      case AUTOMEM:
        switch (menuoption) {
          case ITEM1:
            Infoboxprint(textUI(270));
            switch (doAutoMemory(memstartfreq, memstopfreq, memstartpos, memstoppos, mempionly, memdoublepi)) {
              case 0:
                tftPrint(0, textUI(275), 160, 175, ActiveColor, ActiveColorSmooth, 16);
                break;

              case 1:
                tftPrint(0, textUI(273), 160, 175, ActiveColor, ActiveColorSmooth, 16);
                break;

              case 2:
                tftPrint(0, textUI(274), 160, 175, ActiveColor, ActiveColorSmooth, 16);
                break;
            }
            if (hardwaremodel == PORTABLE_TOUCH_ILI9341) {
              tft.fillRoundRect(240, 36, 60, 40, 6, FrameColor);
              tft.drawRoundRect(240, 36, 60, 40, 6, ActiveColor);
              tftPrint(0, "OK", 270, 44, (CurrentTheme == 7 ? White : ActiveColor), ActiveColorSmooth, 28);
            }
            break;

          case ITEM2:
            Infoboxprint(textUI(264));

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("MHz", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(memstartfreq / 10 + ConverterSet, DEC) + "." + String(memstartfreq % 10 + ConverterSet, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM3:
            Infoboxprint(textUI(265));

            OneBigLineSprite.setTextDatum(TL_DATUM);
            OneBigLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
            OneBigLineSprite.drawString("MHz", 155, 0);
            OneBigLineSprite.setTextDatum(TR_DATUM);
            OneBigLineSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
            OneBigLineSprite.drawString(String(memstopfreq / 10 + ConverterSet, DEC) + "." + String(memstopfreq % 10 + ConverterSet, DEC), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM4:
            Infoboxprint(textUI(266));

            OneBigLineSprite.drawString(String(memstartpos + 1), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM5:
            Infoboxprint(textUI(267));

            OneBigLineSprite.drawString(String(memstoppos + 1), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM6:
            Infoboxprint(textUI(268));

            OneBigLineSprite.drawString((mempionly ? textUI(31) : textUI(30)), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM7:
            Infoboxprint(textUI(278));

            switch (memdoublepi) {
              case MEMPI_OFF: OneBigLineSprite.drawString(textUI(30), 135, 0); break;
              case MEMPI_RANGE: OneBigLineSprite.drawString(textUI(279), 135, 0); break;
              default: OneBigLineSprite.drawString(textUI(280), 135, 0); break;
            }
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM8:
            Infoboxprint(textUI(82));

            OneBigLineSprite.drawString(String(fmscansens), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);
            break;

          case ITEM9:
            Infoboxprint(textUI(276));

            ClearMemoryRange(memstartpos, memstoppos);
            OneBigLineSprite.drawString(textUI(216), 135, 0);
            OneBigLineSprite.pushSprite(24, 118);

            switch (CurrentTheme) {
              case 7: OneBigLineSprite.pushImage(-11, -118, 292, 170, popupbackground_wo); break;
              default: OneBigLineSprite.pushImage(-11, -118, 292, 170, popupbackground); break;
            }
            OneBigLineSprite.drawString(String(memstartpos + 1) + " - " + String(memstoppos + 1) + " " + String(textUI(277)), 135, 0);
            OneBigLineSprite.pushSprite(24, 148);
            if (hardwaremodel == PORTABLE_TOUCH_ILI9341) {
              tft.fillRoundRect(240, 36, 60, 40, 6, FrameColor);
              tft.drawRoundRect(240, 36, 60, 40, 6, ActiveColor);
              tftPrint(0, "OK", 270, 44, (CurrentTheme == 7 ? White : ActiveColor), ActiveColorSmooth, 28);
            }
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
    if (menu) {
      tftPrint(0, line1, 155, 48, ActiveColor, ActiveColorSmooth, 28);
      tftPrint(0, line2, 155, 78, ActiveColor, ActiveColorSmooth, 28);
    } else if (setupmode) {
      tftPrint(0, line1, 155, 40, ActiveColor, ActiveColorSmooth, 28);
      tftPrint(0, line2, 155, 70, ActiveColor, ActiveColorSmooth, 28);
    } else {
      FrequencySprite.drawString(line1, 100, 5);
      FrequencySprite.drawString(line2, 100, 25);
    }
    free(line1);
    free(line2);
  } else {
    if (menu) {
      tftPrint(0, input, 155, 78, ActiveColor, ActiveColorSmooth, 28);
    } else if (setupmode) {
      tftPrint(0, input, 155, 70, ActiveColor, ActiveColorSmooth, 28);
    } else {
      FrequencySprite.drawString(input, 100, 15);
    }
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

void drawButton(const char* text, byte button_number, bool active, bool selected) {
  const int buttonWidth = 70;
  const int buttonHeight = 30;
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

  // Draw the selection outline
  if (selected) {
    tft.drawRect(x - 2, y - 2, buttonWidth + 4, buttonHeight + 4, PrimaryColor);
    tft.drawRect(x - 1, y - 1, buttonWidth + 2, buttonHeight + 2, PrimaryColor);
  } else {
    tft.drawRect(x - 2, y - 2, buttonWidth + 4, buttonHeight + 4, BackgroundColor);
    tft.drawRect(x - 1, y - 1, buttonWidth + 2, buttonHeight + 2, BackgroundColor);
  }


  // Draw the button fill
  tft.pushImage (x, y, 70, 30, (CurrentTheme == 7 ? bwselector_wo : bwselector));


  // Draw the small line at the bottom (narrower, centered, and 3px up)
  int lineHeight = 4;                         // Height of the bottom line
  int lineWidth = (buttonWidth / 2) - 6;      // Half the button width, minus 6px
  int lineX = x + (buttonWidth - lineWidth) / 2; // Center the line horizontally
  int lineY = y + buttonHeight - lineHeight - 3; // Move the line 3px up
  if (button_number != 19) tft.fillRect(lineX, lineY, lineWidth, lineHeight, (active ? InsignificantColor : GreyoutColor));

  // Draw the button text
  tftPrint(0, text, x + buttonWidth / 2, y + (buttonHeight / 4) - 2, ActiveColor, ActiveColorSmooth, 16);
}

String shortLine(String text) {
  String tempText = text;

  if (PSSprite.textWidth(tempText + "...") > 155) { // Include "..." in width check
    while (PSSprite.textWidth(tempText + "...") > 155 && tempText.length() > 0) {
      // Safely remove the last UTF-8 character
      int lastCharIndex = tempText.length() - 1;
      while (lastCharIndex > 0 && (tempText[lastCharIndex] & 0xC0) == 0x80) {
        lastCharIndex--; // Skip over continuation bytes
      }
      tempText = tempText.substring(0, lastCharIndex); // Remove last character
    }
    text = tempText + "..."; // Add "..." to the truncated text
  }
  return text;
}