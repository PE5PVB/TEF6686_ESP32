#ifndef LOGBOOK_H
#define LOGBOOK_H

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h>
#include "TEF6686.h"

extern bool autoDST;
extern bool clockampm;
extern bool NTPupdated;
extern bool rtcset;
extern bool scandxmode;
extern byte band;
extern byte chipmodel;
extern byte language;
extern byte scanhold;
extern byte unit;
extern int16_t SStatus;
extern int8_t NTPoffset;
extern unsigned int ConverterSet;
extern unsigned int frequency;
extern unsigned int frequency_OIRT;
extern unsigned int logcounter;
extern IPAddress remoteip;

extern TEF6686 radio;
extern WebServer webserver;
extern WiFiUDP Udp;

void handleRoot();
void handleDownloadCSV();
bool handleCreateNewLogbook();
byte addRowToCSV();
String getCurrentDateTime(bool inUTC);
bool isDST(time_t t);
void handleLogo();
void printLogbookCSV();
void sendUDPlog();
IPAddress makeBroadcastAddress(IPAddress ip);
#endif