#ifndef RDS_H
#define RDS_H

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <WiFiClient.h>
#include "TEF6686.h"
#include <WiFi.h>

extern bool advancedRDS;
extern bool afpage;
extern bool afscreen;
extern bool aftest;
extern bool artheadold;
extern bool compressedold;
extern bool clearrds;
extern bool dropout;
extern bool dynamicPTYold;
extern bool errorAold;
extern bool errorBold;
extern bool errorCold;
extern bool errorDold;
extern bool hasafold;
extern bool haseonold;
extern bool hasrtplusold;
extern bool hastmcold;
extern bool rdsreset;
extern bool RDSSPYTCP;
extern bool RDSSPYUSB;
extern bool RDSstatus;
extern bool rdsstereoold;
extern bool screenmute;
extern bool setupmode;
extern byte showrdserrors;
extern bool TAold;
extern bool TPold;
extern bool wifi;
extern bool XDRGTKTCP;
extern bool XDRGTKUSB;
extern byte af_counterold;
extern byte afpagenr;
extern byte band;
extern byte ECCold;
extern byte language;
extern byte licold;
extern byte MSold;
extern byte rdsblockold;
extern byte stationlistid;
extern char programTypePrevious[18];
extern char radioIdPrevious[7];
extern int ActiveColor;
extern int ActiveColorSmooth;
extern int BackgroundColor;
extern int BWAutoColor;
extern int BWAutoColorSmooth;
extern int charWidth;
extern int GreyoutColor;
extern int InsignificantColor;
extern int InsignificantColorSmooth;
extern int PrimaryColor;
extern int PrimaryColorSmooth;
extern int SecondaryColor;
extern int SecondaryColorSmooth;
extern int SignificantColor;
extern int SignificantColorSmooth;
extern int xPos;
extern int xPos2;
extern int xPos3;
extern int xPos4;
extern IPAddress remoteip;
extern String afstringold;
extern String ECColdtxt;
extern String eonpsold[11];
extern String eonstringold;
extern String LIColdString;
extern String pinstringold;
extern String PIold;
extern String programServicePrevious;
extern String PSold;
extern String ptynold;
extern String PTYold;
extern String rds_clock;
extern String rds_clockold;
extern String RDSSPYRDS;
extern String RDSSPYRDSold;
extern String RTold;
extern String rtplusstringold;
extern String XDRGTKRDS;
extern String XDRGTKRDSold;
extern unsigned int mappedfreqold[20];
extern unsigned long afticker;
extern unsigned long aftickerhold;
extern unsigned long aftimer;
extern unsigned long eonticker;
extern unsigned long eontickerhold;
extern unsigned long rtplusticker;
extern unsigned long rtplustickerhold;
extern unsigned long rtticker;
extern unsigned long rttickerhold;

extern TFT_eSPI tft;
extern TEF6686 radio;
extern WiFiClient RemoteClient;
extern WiFiUDP Udp;
extern TFT_eSprite sprite;
extern TFT_eSprite sprite2;
extern TFT_eSprite sprite3;
extern TFT_eSprite sprite4;
extern TFT_eSprite sprite5;

void ShowAdvancedRDS();
void readRds();
void showECC();
void doAF();
void showPI();
void showPTY();
void showPS();
void showRadioText();
void ShowAFEON();

extern void ShowRDSLogo(bool RDSstatus);
extern void DataPrint(String string);
extern void tftPrint(int8_t offset, const String & text, int16_t x, int16_t y, int color, int smoothcolor, uint8_t fontsize);
extern void tftReplace(int8_t offset, const String & textold, const String & text, int16_t x, int16_t y, int color, int smoothcolor, uint8_t fontsize);

#endif