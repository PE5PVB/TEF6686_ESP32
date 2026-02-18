/*!
   @file WiFiConnectParam.cpp

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
#include "WiFiConnectParam.h"
/**************************************************************************/
/*!
    @brief  Class object initialiser
    @param    custom
              Custom HTML to be displayed in the access point for this item.
*/
/**************************************************************************/
WiFiConnectParam::WiFiConnectParam(const char *custom) {
  _id = NULL;
  _placeholder = NULL;
  _length = 0;
  _value = NULL;

  _customHTML = custom;
}
/**************************************************************************/
/*!
    @brief  Class object initialiser
    @param    id
              The unique ID for the html input box markup for this item
    @param    placeholder
              Text to be displayed as the input box placeholder for this item
    @param    defaultValue
              Default text to be displayed in the input box for this item
    @param    length
              The maximum input text length for this item
*/
/**************************************************************************/
WiFiConnectParam::WiFiConnectParam(const char *id, const char *placeholder, const char *defaultValue, int length) {
  init(id, placeholder, defaultValue, length, "");
}
/**************************************************************************/
/*!
    @brief  Class object initialiser
    @param    id
              The unique ID for the html input box markup for this item
    @param    placeholder
              Text to be displayed as the input box placeholder for this item
    @param    defaultValue
              Default text to be displayed in the input box for this item
    @param    length
              The maximum input text length for this item
    @param    custom
              Custom HTML to be displayed in the access point for this item.
*/
/**************************************************************************/
WiFiConnectParam::WiFiConnectParam(const char *id, const char *placeholder, const char *defaultValue, int length, const char *custom) {
  init(id, placeholder, defaultValue, length, custom);
}
/**************************************************************************/
/*!
    @brief  Initialiser method
    @param    id
              The unique ID for the html input box markup for this item
    @param    placeholder
              Text to be displayed as the input box placeholder for this item
    @param    defaultValue
              Default text to be displayed in the input box for this item
    @param    length
              The maximum input text length for this item
    @param    custom
              Custom HTML to be displayed in the access point for this item.
*/
/**************************************************************************/
void WiFiConnectParam::init(const char *id, const char *placeholder, const char *defaultValue, int length, const char *custom) {
  _id = id;
  _placeholder = placeholder;
  _length = length;
  setValue(defaultValue);

  _customHTML = custom;
}
/**************************************************************************/
/*!
    @brief  Method to change the current value of the item
    @param    newValue
              The new string value for the item
*/
/**************************************************************************/
void WiFiConnectParam::setValue(const char *newValue){
  if(_length>0){
  _value = new char[_length + 1];
  for (int i = 0; i < _length; i++) {
    _value[i] = 0;
  }
  if (newValue != NULL) {
    strncpy(_value, newValue, _length);
  }    
  }
}
/**************************************************************************/
/*!
    @brief  Function to get the current value of the item
    @return The current value
*/
/**************************************************************************/
const char* WiFiConnectParam::getValue() {
  return _value;
}
/**************************************************************************/
/*!
    @brief  Function to get the current id of the item
    @return The current id
*/
/**************************************************************************/
const char* WiFiConnectParam::getID() {
  return _id;
}
/**************************************************************************/
/*!
    @brief  Function to get the current placeholder text of the item
    @return The current placeholder text
*/
/**************************************************************************/
const char* WiFiConnectParam::getPlaceholder() {
  return _placeholder;
}
/**************************************************************************/
/*!
    @brief  Function to get the maximum length allowed for the value of the item
    @return The current maximum value length
*/
/**************************************************************************/
int WiFiConnectParam::getValueLength() {
  return _length;
}
/**************************************************************************/
/*!
    @brief  Function to get the current custom html markup of the item
    @return The current custom html markup
*/
/**************************************************************************/
const char* WiFiConnectParam::getCustomHTML() {
  return _customHTML;
}
