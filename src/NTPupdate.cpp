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

// Retrieves the current time from an NTP server
time_t getNtpTime() {
  IPAddress ntpServerIP;
  byte packetBuffer[NTP_PACKET_SIZE];

  // Clear any previously received UDP packets
  while (Udp.parsePacket() > 0);

  // Resolve the NTP server's hostname to its IP address
  if (!WiFi.hostByName(ntpServerName, ntpServerIP)) {
    return 0; // Return 0 if hostname resolution fails
  }

  // Send an NTP request
  sendNTPpacket(ntpServerIP);

  // Wait for a response with a 1500ms timeout
  uint32_t startWait = millis();
  while (millis() - startWait < 1500) {
    if (Udp.parsePacket() >= NTP_PACKET_SIZE) { // Check if a valid packet is received
      Udp.read(packetBuffer, NTP_PACKET_SIZE);

      // Extract "seconds since 1900" from the packet (bytes 40-43)
      unsigned long secsSince1900 =
        ((unsigned long)packetBuffer[40] << 24) |
        ((unsigned long)packetBuffer[41] << 16) |
        ((unsigned long)packetBuffer[42] << 8)  |
        (unsigned long)packetBuffer[43];

      // Convert to UNIX epoch time (seconds since 1970)
      return secsSince1900 - 2208988800UL;
    }
  }

  // Return 0 if no valid response is received
  return 0;
}

// Updates the RTC with the time from an NTP server
void NTPupdate() {
  // Abort if Wi-Fi is not connected
  if (!wifi) {
    NTPupdated = false;
    return;
  }

  // Retrieve the current time from the NTP server
  time_t currentTime = getNtpTime();

  if (currentTime) {
    // Set the RTC if valid time is received
    rtc.setTime(currentTime);
    struct tm *t = localtime(&currentTime);
    rx8010_setTime(t);
    rtcset = true;
    NTPupdated = true;
    radio.rds.ctupdate = false;
  } else {
    // Indicate that the update failed
    NTPupdated = false;
    radio.rds.ctupdate = true;
  }
}