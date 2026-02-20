#include "NTPupdate.h"
#include "rtc_rx8010.h"

// Sends an NTP request packet to the specified server address
void sendNTPpacket(IPAddress &address) {
  byte packetBuffer[NTP_PACKET_SIZE] = {0}; // Initialize buffer with zeros

  // Set NTP packet header fields as per NTP protocol
  packetBuffer[0] = 0b11100011; // LI, Version, Mode
  packetBuffer[2] = 6;          // Polling interval
  packetBuffer[3] = 0xEC;       // Peer clock precision

  // Root Delay & Root Dispersion fields
  packetBuffer[12] = 49;
  packetBuffer[13] = 0x4E;
  packetBuffer[14] = 49;
  packetBuffer[15] = 52;

  // Send the NTP request to port 123 (NTP standard port)
  Udp.beginPacket(address, 123);
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}

// ---- Non-blocking NTP state machine ----

static uint8_t       _ntpState   = 0;  // 0=idle, 1=waiting for reply
static unsigned long _ntpSendMs  = 0;
static const unsigned long NTP_TIMEOUT_MS = 1500;

// Starts an NTP request (non-blocking). Call ntpPoll() in loop to process the reply.
void NTPupdate() {
  if (!wifi || WiFi.status() != WL_CONNECTED) {
    NTPupdated = false;
    return;
  }

  IPAddress ntpServerIP;

  // Clear any previously received UDP packets
  while (Udp.parsePacket() > 0);

  // Resolve the NTP server's hostname to its IP address
  if (!WiFi.hostByName(ntpServerName, ntpServerIP)) {
    NTPupdated = false;
    radio.rds.ctupdate = true;
    return;
  }

  // Send an NTP request and enter waiting state
  sendNTPpacket(ntpServerIP);
  _ntpState  = 1;
  _ntpSendMs = millis();
}

// Poll for NTP response (called from loop). Returns immediately if idle.
void ntpPoll() {
  if (_ntpState != 1) return;

  byte packetBuffer[NTP_PACKET_SIZE];

  if (Udp.parsePacket() >= NTP_PACKET_SIZE) {
    Udp.read(packetBuffer, NTP_PACKET_SIZE);

    // Extract "seconds since 1900" from the packet (bytes 40-43)
    unsigned long secsSince1900 =
      ((unsigned long)packetBuffer[40] << 24) |
      ((unsigned long)packetBuffer[41] << 16) |
      ((unsigned long)packetBuffer[42] << 8)  |
      (unsigned long)packetBuffer[43];

    // Convert to UNIX epoch time (seconds since 1970)
    time_t currentTime = secsSince1900 - 2208988800UL;

    rtc.setTime(currentTime);
    struct tm *t = localtime(&currentTime);
    rx8010_setTime(t);
    rtcset = true;
    NTPupdated = true;
    radio.rds.ctupdate = false;
    _ntpState = 0;
    return;
  }

  // Timeout
  if (millis() - _ntpSendMs >= NTP_TIMEOUT_MS) {
    NTPupdated = false;
    radio.rds.ctupdate = true;
    _ntpState = 0;
  }
}
