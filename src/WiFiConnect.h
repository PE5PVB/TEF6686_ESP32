/*!
   @file WiFiConnect.h

   WiFi Connection Manager with Captive Portal for ESP32.

   Provides WiFi auto-connect and a web-based configuration portal
   with support for custom user parameters.

   Based on WiFiConnect by Stuart Blair
   (https://github.com/smurf0969/WiFiConnect), itself derived from
   WiFiManager by tzapu (https://github.com/tzapu/WiFiManager).

   Simplified for ESP32-only use. Removed: ESP8266 support, OLED display,
   static IP configuration, debug output, params-only portal, and callbacks.

   GNU General Public License v3.0
*/
#ifndef WiFiConnect_h
#define WiFiConnect_h

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>
#include <esp_wifi.h>
#include <memory>

/// Maximum number of custom parameters
#define WiFiConnect_MAX_PARAMS 10

/// Gets a unique chip identifier from the ESP32 eFuse MAC
#define ESP_getChipId() ((uint32_t)ESP.getEfuseMac())

extern const char* textUI(uint16_t number);

class WiFiConnect;

/**************************************************************************/
/*!
    @brief  Stores a custom parameter for the configuration portal.
            Parameters can be plain HTML labels or input fields.
*/
/**************************************************************************/
class WiFiConnectParam {
public:
  /// Construct a custom HTML-only parameter (label, no input field)
  WiFiConnectParam(const char *custom);

  /// Construct an input field parameter
  WiFiConnectParam(const char *id, const char *placeholder, const char *defaultValue, int length);

  /// Destructor - frees the allocated value buffer
  ~WiFiConnectParam();

  const char *getID();
  const char *getValue();
  const char *getPlaceholder();
  int         getValueLength();
  const char *getCustomHTML();

private:
  const char *_id;
  const char *_placeholder;
  char       *_value;
  int         _length;
  const char *_customHTML;

  void init(const char *id, const char *placeholder, const char *defaultValue, int length, const char *custom);
  void setValue(const char *newValue);

  friend class WiFiConnect;
};

/**************************************************************************/
/*!
    @brief  WiFi connection manager with captive portal.
            Tries to connect to the last-known network, and if that fails,
            opens an access point with a web interface for configuration.
*/
/**************************************************************************/
class WiFiConnect {
public:
  WiFiConnect();

  /// Try to connect to the last-known WiFi network (3 retries, 10s timeout)
  boolean autoConnect();

  /// Add a custom parameter to the configuration portal
  void addParameter(WiFiConnectParam *p);

  /// Start the configuration portal access point (blocks until configured or cancelled)
  /// @param cancelPin  GPIO pin (active LOW) to cancel the portal, or -1 to disable
  boolean startConfigurationPortal(int8_t cancelPin = -1);

private:
  static const int RETRY_ATTEMPTS = 3;
  static const int CONNECTION_TIMEOUT_SECS = 10;
  static const byte DNS_PORT = 53;
  static const int MINIMUM_QUALITY = 8;

  int _paramsCount = 0;
  boolean _readyToConnect = false;
  String _ssid;
  String _password;

  WiFiConnectParam* _params[WiFiConnect_MAX_PARAMS];

  std::unique_ptr<DNSServer> dnsServer;
  std::unique_ptr<WebServer> server;

  char _apName[33];

  void setAPName();

  boolean autoConnect(const char *ssidName, const char *ssidPassword, WiFiMode_t acWiFiMode);

  void handleRoot();
  void handleWifi();
  void handleScan();
  void handleWifiSave();
  void handleLogo();
  void handleNotFound();

  boolean captivePortal();
  boolean isIp(String str);
  String  toStringIp(IPAddress ip);
  int     getRSSIasQuality(int RSSI);
};

#endif
