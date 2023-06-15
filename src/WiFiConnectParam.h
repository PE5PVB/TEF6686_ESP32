/*!
   @file WiFiConnectParam.h

   WiFi Connection Manager with Captive Portal

   Introduction

   This is the documentation for WiFiConnect for the Arduino platform.
   It is a WiFi connection manager for use with the popular ESP8266 and ESP32 chips.
   It contains a captive portal to allow easy connection and changing of WiFi netwoks
   via a web based interface and allows for additional user parameters.
   It can also display messages via a OLED screen see WiFiConnectOLED class.

   This is a heavily customised version from the original <a href="https://github.com/tzapu/WiFiManager">WiFiManager</a>
   developed by https://github.com/tzapu .

   Dependencies

   This library depends on <a href="https://github.com/esp8266/Arduino">
    ESP8266 Arduino Core</a> and <a href="https://github.com/espressif/arduino-esp32">ESP32 Arduino Core</a> being present on your system.
    Please make sure you have installed the latest version before using this library.

   
   Written by Stuart Blair.

   License

   GNU General Public License v3.0 licence, all text here must be included in any redistribution and you should receive a copy of the license file.

*/
#ifndef WIFI_CONNECT_PARAM
#define WIFI_CONNECT_PARAM

#ifndef WiFiConnect_MAX_PARAMS
#define WiFiConnect_MAX_PARAMS 10 ///< The maximum size of the param array and how many custom parameters we may have
#endif

#include <Arduino.h>
/**************************************************************************/
/*! 
    @brief  Class that stores a custom parameter
*/
/**************************************************************************/
class WiFiConnectParam {
  public:
    WiFiConnectParam(const char *custom);
    WiFiConnectParam(const char *id, const char *placeholder, const char *defaultValue, int length);
    WiFiConnectParam(const char *id, const char *placeholder, const char *defaultValue, int length, const char *custom);

    const char *getID();
    const char *getValue();
    const char *getPlaceholder();
    int         getValueLength();
    const char *getCustomHTML();
    void setValue(const char *newValue);
  private:
    const char *_id;
    const char *_placeholder;
    char       *_value;
    int         _length;
    const char *_customHTML;

    void init(const char *id, const char *placeholder, const char *defaultValue, int length, const char *custom);

    friend class WiFiConnect; ///< Declarion for WiFiConnect class

};
#endif
