/*!
   @file WiFiConnect.h

   This is the documentation for WiFiConnect for the Arduino platform.
   It is a WiFi connection manager for use with the popular ESP8266 and ESP32 chips.
   It contains a captive portal to allow easy connection and changing of WiFi netwoks
   via a web based interface and allows for additional user parameters.

   You can view the project at <a href="https://github.com/smurf0969/WiFiConnect">https://github.com/smurf0969/WiFiConnect</a>.
   Further information is also available in the project <a href="https://github.com/smurf0969/WiFiConnect/wiki">Wiki</a>.

   This is a heavily customised version from the origional <a href="https://github.com/tzapu/WiFiManager">WiFiManager</a>
   developed by https://github.com/tzapu .

   This library depends on <a href="https://github.com/esp8266/Arduino">
    ESP8266 Arduino Core</a> and <a href="https://github.com/espressif/arduino-esp32">ESP32 Arduino Core</a> being present on your system.
    Please make sure you have installed the latest version before using this library.

   Written by Stuart Blair.

   GNU General Public License v3.0 licence, all text here must be included in any redistribution and you should receive a copy of the license file.

*/
#ifndef WiFiConnect_h
#define WiFiConnect_h
#include <Arduino.h>
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#else
#include <WiFi.h>
#include <WebServer.h>
#endif
#include <DNSServer.h>
#include <memory>

#if defined(ESP8266)
extern "C" {
#include "user_interface.h"
}
#define ESP_getChipId()   (ESP.getChipId()) ///< Gets an ID from the chip
#else
#include <esp_wifi.h>
#define ESP_getChipId()   ((uint32_t)ESP.getEfuseMac())///< Gets an ID from the chip
#endif

#include "WC_AP_HTML.h"
#include "WiFiConnectParam.h"
/** Options for how a access point should continue if no WiFi connected */
enum AP_Continue {
  AP_NONE, ///< No action, continues to run code
  AP_LOOP, ///< Stalls execution with an infinate loop
  AP_RESTART, ///< Restarts the chip, allowing it to try to setup again. Handy for sensors when wifi is lost.
  AP_RESET, ///< Same as AP_RESTART
  AP_WAIT   // Keep the AP and webserver running, sit quietly and be patient.
};
/**************************************************************************/
/*!
    @brief  Class that helps to connect to WiFi networks, that also has
            captive portal web interface for configuration.
            This is the base class for WiFiConntectOLED which displays
            information on a OLED display.
*/
/**************************************************************************/
class WiFiConnect {
  public:
    /// Create WiFiConnect class
    WiFiConnect();

    boolean startConfigurationPortal();
    boolean startConfigurationPortal(AP_Continue apcontinue);
    boolean startConfigurationPortal(AP_Continue apcontinue, const char*  apName, const char*  apPassword = NULL, bool paramsMode = false);

    boolean startParamsPortal();
    boolean startParamsPortal(AP_Continue apcontinue);
    boolean startParamsPortal(AP_Continue apcontinue, const char*  apName, const char*  apPassword = NULL);

    void addParameter(WiFiConnectParam *p);

    void setAPName(const char*  apName);
    const char* getAPName();

    void resetSettings();

    boolean autoConnect();
    boolean autoConnect(const char*  ssidName, const char*  ssidPassword = NULL, WiFiMode_t acWiFiMode = WIFI_STA);


    //sets a custom ip /gateway /subnet configuration
    void          setAPStaticIPConfig(IPAddress ip, IPAddress gw, IPAddress sn);
    //sets config for a static IP
    void          setSTAStaticIPConfig(IPAddress ip, IPAddress gw, IPAddress sn);

    //called when AP mode and config portal is started
    void          setAPCallback( void (*func)(WiFiConnect*) );
    //called when settings have been changed and connection was successful
    void          setSaveConfigCallback( void (*func)(void) );

    void setDebug(boolean isDebug);

    void setRetryAttempts(int attempts);
    void setConnectionTimeoutSecs(int timeout);
    void setAPModeTimeoutMins(int mins);

    boolean       captivePortal();

    //helpers
    const char* statusToString(int state);
    int           getRSSIasQuality(int RSSI);
    boolean       isIp(String str);
    String        toStringIp(IPAddress ip);
    virtual  void displayTurnOFF(int ms = 5000); ///< Virtual method overriden in WiFiConnectOLED
    virtual void displayLoop(); ///< Virtual method overriden in WiFiConnectOLED
    virtual void displayON(); ///< Virtual method overriden in WiFiConnectOLED
  protected:
    boolean _debug = false; ///< Flag to determine wheter to output mesages or not
    template <typename Generic>
    void    DEBUG_WC(Generic text);
    virtual   void displayConnecting(int attempt, int totalAttempts); ///< Virtual method overriden in WiFiConnectOLED
    virtual void displayConnected(); ///< Virtual method overriden in WiFiConnectOLED
    virtual void displayAP(); ///< Virtual method overriden in WiFiConnectOLED
    virtual void displayParams(); ///< Virtual method overriden in WiFiConnectOLED
    virtual void displayManualReset(); ///< Virtual method overriden in WiFiConnectOLED

  private:


    int _retryAttempts = 3; ///< Number of attempts when trying to connect to WiFi network
    int _connectionTimeoutSecs = 10; ///< How log to wait for the connection to succeed or fail
    int _apTimeoutMins = 3; ///< The amount of minutes of inactivity before the access point exits it routine
    // DNS server
    const byte    DNS_PORT = 53; ///< Standard DNS Port number

    long _lastAPPage = 0; ///< The last time a page was accessed in the portal. Used for the inactivity timeout.
    boolean _removeDuplicateAPs = true; ///< Flag to remove duplicate networks from scan results.
    int _minimumQuality = 8; ///< The minimum netqork quality to be included in scan results.
    int _paramsCount = 0; ///< The amount of custom parameters added via addParameter
    boolean _readyToConnect = false; ///< Flag used in access point to determine if it should try to connect to the network.
    String _ssid      = "                            "; ///< Tempory holder for the network ssid
    String _password  = "                            "; ///< Tempory holder for the network password

    WiFiConnectParam* _params[WiFiConnect_MAX_PARAMS]; ///< Array to hold custom parameters

    std::unique_ptr<DNSServer>        dnsServer; ///< DNS Server for captive portal to redirect to Access Point
#ifdef ESP8266
    std::unique_ptr<ESP8266WebServer> server; ///< Web server for serving access point pages
#else
    std::unique_ptr<WebServer>        server; ///< Web server for serving access point pages
#endif

     char _apName[33] ; ///< Holder for the access point name
     char _apPassword[65] ; ///< Holder for the access point password
    
    IPAddress     _ap_static_ip; ///< Variable for holding Static IP Address for the access point
    IPAddress     _ap_static_gw; ///< Variable for holding Static Gateway IP Address for the access point
    IPAddress     _ap_static_sn; ///< Variable for holding Static Subnet Mask IP Address for the access point
    IPAddress     _sta_static_ip; ///< Variable for holding Static IP Address for the network connection
    IPAddress     _sta_static_gw; ///< Variable for holding Static Gateway IP Address for the network connection
    IPAddress     _sta_static_sn; ///< Variable for holding Static Subnet Mask IP Address for the network connection

    void (*_apcallback)(WiFiConnect*) = NULL;
    void (*_savecallback)(void) = NULL;



    void handleRoot();
    void handleParamRoot();
    void handleParams();
    void handleWifi(boolean scan);
    void handleWifiSave();
    void handleInfo();
    void handleReset();
    void handle204();
    void handleNotFound();

    template <class T>
    auto optionalIPFromString(T *obj, const char *s) -> decltype(  obj->fromString(s)  ) {
      return  obj->fromString(s);
    }
    auto optionalIPFromString(...) -> bool {
      DEBUG_WC("NO fromString METHOD ON IPAddress, you need ESP8266 core 2.1.0 or newer for Custom IP configuration to work.");
      return false;
    }

};

#endif
