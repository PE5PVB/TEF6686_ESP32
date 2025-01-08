#ifndef COMMS_H
#define COMMS_H

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <WiFiClient.h>
#include "TEF6686.h"
#include <WiFi.h>
#include <Hash.h>
#include "WiFiConnect.h"
#include "WiFiConnectParam.h"

extern bool advancedRDS;
extern bool afscreen;
extern bool aftest;
extern bool autosquelch;
extern bool BWreset;
extern bool Data_Accelerator;
extern bool direction;
extern bool externaltune;
extern bool fullsearchrds;
extern bool menu;
extern bool RDSSPYTCP;
extern bool RDSSPYUSB;
extern bool RDSstatus;
extern bool scandxmode;
extern bool screenmute;
extern bool seek;
extern bool setupmode;
extern bool softmuteam;
extern bool softmutefm;
extern bool SQ;
extern bool StereoToggle;
extern bool store;
extern bool usesquelch;
extern bool wifi;
extern bool wificonnected;
extern bool XDRGTKdata;
extern bool XDRGTKTCP;
extern bool XDRGTKUSB;
extern bool XDRGTKMuteScreen;
extern bool XDRScan;
extern bool XDRMute;
extern byte band;
extern byte BWset;
extern byte BWsetRecall;
extern byte EQset;
extern byte fmscansens;
extern byte iMSEQ;
extern byte iMSset;
extern byte language;
extern byte memorypos;
extern byte scanhold;
extern byte stepsize;
extern byte subnetclient;
extern byte TEF;
extern char buff[16];
extern int ActiveColor;
extern int ActiveColorSmooth;
extern int BackgroundColor;
extern int DeEmphasis;
extern int freqold;
extern int GreyoutColor;
extern int InsignificantColor;
extern int InsignificantColorSmooth;
extern int PrimaryColor;
extern int PrimaryColorSmooth;
extern int RDSColor;
extern int RDSColorSmooth;
extern int RDSDropoutColor;
extern int RDSDropoutColorSmooth;
extern int scanner_filter;
extern int SignificantColor;
extern int SignificantColorSmooth;
extern int Squelch;
extern int Squelchold;
extern int Stereostatus;
extern int XDRBWset;
extern int XDRBWsetold;
extern int16_t OStatus;
extern int16_t SStatus;
extern int8_t LowLevelSet;
extern int8_t VolSet;
extern IPAddress remoteip;
extern String cryptedpassword;
extern String salt;
extern String saltkey;
extern String StereoStatusCommand;
extern String StereoStatusCommandold;
extern String XDRGTK_key;
extern uint16_t BW;
extern uint16_t MStatus;
extern uint16_t USN;
extern uint16_t WAM;
extern uint8_t buff_pos;
extern int8_t CN;
extern unsigned int ConverterSet;
extern unsigned int freq_scan;
extern unsigned int frequency;
extern unsigned int frequency_OIRT;
extern unsigned int frequency_LW;
extern unsigned int frequency_AM;
extern unsigned int frequency_MW;
extern unsigned int frequency_SW;
extern unsigned int frequencyold;
extern unsigned int HighEdgeOIRTSet;
extern unsigned int LowEdgeOIRTSet;
extern unsigned int LWHighEdgeSet;
extern unsigned int LWLowEdgeSet;
extern unsigned int MWHighEdgeSet;
extern unsigned int MWLowEdgeSet;
extern unsigned int scanner_end;
extern unsigned int scanner_start;
extern unsigned int scanner_step;
extern unsigned int SWHighEdgeSet;
extern unsigned int SWLowEdgeSet;
extern unsigned long aftimer;
extern unsigned long signalstatustimer;

extern TFT_eSPI tft;
extern TEF6686 radio;
extern WiFiClient RemoteClient;
extern WiFiUDP Udp;
extern WiFiServer Server;
extern WiFiConnect wc;
extern WebServer webserver;

void Communication();
void XDRGTKRoutine();
void passwordcrypt();
void tryWiFi();

extern void DataPrint(String string);
extern void ShowFreq(int mode);
extern void SelectBand();
extern void doBW();
extern void BuildDisplay();
extern void BuildAdvancedRDS();
extern void ModeButtonPress();
extern void ScreensaverTimerReopen();
extern void Seek(bool mode);
extern void doStereoToggle();
extern void MuteScreen(bool setting);
extern void updateiMS();
extern void updateEQ();
extern void tftPrint(int8_t offset, const String & text, int16_t x, int16_t y, int color, int smoothcolor, uint8_t fontsize);
extern void showAutoSquelch(bool mode);
extern void ShowStepSize();
extern void startFMDXScan();
extern void cancelDXScan();
extern void printLogbookCSV();
#endif