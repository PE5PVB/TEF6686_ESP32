#ifndef NTP_H
#define NTP_H

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <ESP32Time.h>
#include <TimeLib.h>

static const char ntpServerName[] = "0.pool.ntp.org";
static const int localPort = 8944;
const int NTP_PACKET_SIZE = 48; // NTP time is in the first 48 bytes of message

extern ESP32Time rtc;
extern WiFiClient RemoteClient;
extern WiFiUDP Udp;
extern bool wifi;

void sendNTPpacket(IPAddress &address);
void NTPupdate();
time_t getNtpTime();
#endif
