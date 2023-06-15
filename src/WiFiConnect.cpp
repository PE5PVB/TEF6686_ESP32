/*!
   @file WiFiConnect.cpp

   @mainpage WiFi Connection Manager with Captive Portal

   @section intro_sec Introduction

   This is the documentation for WiFiConnect for the Arduino platform <a href="https://github.com/smurf0969/WiFiConnect">https://github.com/smurf0969/WiFiConnect</a>.
   Further documentation can be found in the [Wiki](https://github.com/smurf0969/WiFiConnect/wiki) or in the project examples folder on GitHub.

   It is a WiFi connection manager for use with the popular ESP8266 and ESP32 chips.

   It contains a captive portal to allow easy connection and changing of WiFi netwoks
   via a web based interface and allows for additional user parameters.

   It can also display messages via a OLED screen see WiFiConnectOLED class.

   ![alt text](https://github.com/smurf0969/WiFiConnect/raw/master/extras/screenshots.png "Screenshots")

   This is a heavily customised version from the origional <a href="https://github.com/tzapu/WiFiManager">WiFiManager</a>
   developed by https://github.com/tzapu .

   @section dependencies Dependencies

   This library depends on <a href="https://github.com/esp8266/Arduino">
    ESP8266 Arduino Core</a> or <a href="https://github.com/espressif/arduino-esp32">ESP32 Arduino Core</a> depending on what chip you are using being present on your system.  
    Please make sure you have installed the latest version before using this library.  

    @section arduino_libraries Arduino Libraries

   - ArduinoJson 6.9.1 [https://github.com/bblanchon/ArduinoJson.git](https://github.com/bblanchon/ArduinoJson.git) or [https://blog.benoitblanchon.fr](https://blog.benoitblanchon.fr)
   - ESP8266 OLED SSD1306 ([Custom version](https://github.com/smurf0969/esp8266-oled-ssd1306/tree/Allow-overriding-default-font))    

   @section author Author

   Written by Stuart Blair.

   @section license License

   GNU General Public License v3.0 licence, all text here must be included in any redistribution and you should receive a copy of the license file.

*/
#include "WiFiConnect.h"

WiFiConnect::WiFiConnect() {
  //_params = (WiFiConnectParam**)malloc(WiFiConnect_MAX_PARAMS * sizeof(WiFiConnectParam*));
  _apName[0]='\0';
  _apPassword[0]='\0';
}
/**************************************************************************/
/*!
    @brief  This function gets overridden by WiFiConnectOLED,
            please view its documentation.
*/
/**************************************************************************/
void  WiFiConnect::displayConnecting(int attempt, int totalAttempts) {
  /*dummy*/
}
/**************************************************************************/
/*!
    @brief  This function gets overridden by WiFiConnectOLED,
            please view its documentation.
*/
/**************************************************************************/
void  WiFiConnect::displayConnected() {
  /*dummy*/
}
/**************************************************************************/
/*!
    @brief  This function gets overridden by WiFiConnectOLED,
            please view its documentation.
*/
/**************************************************************************/
void  WiFiConnect::displayAP() {
  /*dummy*/
}
/**************************************************************************/
/*!
    @brief  This function gets overridden by WiFiConnectOLED,
            please view its documentation.
*/
/**************************************************************************/
void  WiFiConnect::displayParams() {
  /*dummy*/
}
/**************************************************************************/
/*!
    @brief  This function gets overridden by WiFiConnectOLED,
            please view its documentation.
*/
/**************************************************************************/
void WiFiConnect::displayManualReset() {
  /*dummy*/
}
/**************************************************************************/
/*!
    @brief  This function gets overridden by WiFiConnectOLED,
            please view its documentation.
*/
/**************************************************************************/
void WiFiConnect::displayTurnOFF(int ms) {
  /*dummy*/
}
/**************************************************************************/
/*!
    @brief  This function gets overridden by WiFiConnectOLED,
            please view its documentation.
*/
/**************************************************************************/
void WiFiConnect::displayLoop() {
  /*dummy*/
}
/**************************************************************************/
/*!
    @brief  This function gets overridden by WiFiConnectOLED,
            please view its documentation.
*/
/**************************************************************************/
void WiFiConnect::displayON() {
  /*dummy*/
}
/**************************************************************************/
/*!
    @brief  Sets the timeout for when the Access Point is idle.
    @param  mins
            The number of minutes to before exiting an idle access point.
*/
/**************************************************************************/
void WiFiConnect::setAPModeTimeoutMins(int mins) {
  if (mins > 0) {
    _apTimeoutMins = mins;
  }
}
/**************************************************************************/
/*!
    @brief  Sets the name for the Access Point, setting a default based on
            the ESP chip id if needed.
    @param  apName
            The new name for the access point.
*/
/**************************************************************************/
void WiFiConnect::setAPName(const char *apName) {
  if(strlen(apName)>32){return;}
  if (strlen(apName)==0||(apName == NULL)) {
    String ssid = "ESP_" + String(ESP_getChipId());
    //_apName = ssid.c_str();
    strcpy(_apName,ssid.c_str());

  } else if (apName != NULL &&  strlen(apName)>0) {
   // _apName = apName;
    strcpy(_apName,apName);
  }
}
/**************************************************************************/
/*!
    @brief  Gets the Access Point name or the default based on the
            ESP chip id if not already set.
    @return  The name to be given to the access point.
*/
/**************************************************************************/
const char* WiFiConnect::getAPName() {
  if ((_apName == NULL ) || strlen(_apName)==0) {
    setAPName(NULL);
  }
  return _apName;
}
/**************************************************************************/
/*!
    @brief  Adds a custom parameter to be displayed in the accesspoint and
            parameters portals.
            Custom parameters can be used to save information that you do
            not want to hard code i.e. IP address, Port number that can be
            saved to the file system.
    @param  p
            The custom parameter to add.
*/
/**************************************************************************/
void WiFiConnect::addParameter(WiFiConnectParam *p) {
  _params[_paramsCount] = p;
  _paramsCount++;
  DEBUG_WC("Adding parameter");
  DEBUG_WC(p->getID());
}
/**************************************************************************/
/*!
    @brief  Starts the custom Parameters Portal using default
            access point name and password.
    @return Returns wether WiFi is connected to a network
*/
/**************************************************************************/
boolean WiFiConnect::startParamsPortal() {
  return startParamsPortal(AP_NONE, _apName, _apPassword);
}
/**************************************************************************/
/*!
    @brief  Starts the custom Parameters Portal using default
            access point name and password, but allows for specifying how
            to continue.
    @param  apcontinue
            What should the access point do if there is still no connection.
            AP_NONE - continue running code,
            AP_LOOP - stay in an infinate loop,
            AP_RESET - Restart the ESP
			AP_WAIT  - Keep AP alive waiting for input			
   @return  Returns wether WiFi is connected to a network if
            AP_NONE is passed as a parameter
*/
/**************************************************************************/
boolean WiFiConnect::startParamsPortal(AP_Continue apcontinue) {
  return startParamsPortal(apcontinue, _apName, _apPassword);
}
/**************************************************************************/
/*!
    @brief  Starts the custom Parameters Portal.
    @param  apcontinue
            What should the access point do if there is still no connection.
            AP_NONE - continue running code,
            AP_LOOP - stay in an infinate loop,
            AP_RESET - Restart the ESP
			AP_WAIT  - Keep AP alive waiting for input			
    @param  apName
            The Name to use for the access point
    @param  apPassword
            The optional Password to protect the access point
   @return  Returns wether WiFi is connected to a network if
            AP_NONE is passed as a parameter
*/
/**************************************************************************/
boolean WiFiConnect::startParamsPortal(AP_Continue apcontinue, const char  *apName, const char  *apPassword) {

	// Wrapper
	return startConfigurationPortal(apcontinue, apName, apPassword, true);  
}
/**************************************************************************/
/*!
    @brief  Starts the Access Portal for setting SSID and Password for
            connecting to a network and any custom user parameters.
            Uses the default access point name and password.
   @return  Returns wether WiFi is connected to a network if
            AP_NONE is passed as a parameter
*/
/**************************************************************************/
boolean WiFiConnect::startConfigurationPortal() {
  return startConfigurationPortal(AP_NONE, _apName, _apPassword);
}
/**************************************************************************/
/*!
    @brief  Starts the Access Portal for setting SSID and Password for
            connecting to a network and any custom user parameters.
            Uses the default access point name and password, but
            allows for specifying how to continue if network not connected.
    @param  apcontinue
            What should the access point do if there is still no connection.
            AP_NONE - continue running code,
            AP_LOOP - stay in an infinate loop,
            AP_RESET - Restart the ESP
			AP_WAIT  - Keep AP alive waiting for input
    @return Returns wether WiFi is connected to a network if
            AP_NONE is passed as a parameter
*/
/**************************************************************************/
boolean WiFiConnect::startConfigurationPortal(AP_Continue apcontinue) {
  return startConfigurationPortal(apcontinue, _apName, _apPassword);
}
/**************************************************************************/
/*!
    @brief  Starts the Access Portal for setting SSID and Password for
            connecting to a network and any custom user parameters.
    @param  apcontinue
            What should the access point do if there is still no connection.
            AP_NONE - continue running code,
            AP_LOOP - stay in an infinate loop,
            AP_RESET - Restart the ESP, handy for sensors if you network
                       goes down, do they keep trying to connect.
			AP_WAIT  - Keep AP alive waiting for input					   
    @param  apName
            The Name to use for the access point
    @param  apPassword
            The optional Password to protect the access point
    @return Returns wether WiFi is connected to a network if
            AP_NONE is passed as a parameter
*/
/**************************************************************************/
boolean WiFiConnect::startConfigurationPortal(AP_Continue apcontinue, const char  *apName, const char  *apPassword, bool paramsMode) {

  if (paramsMode) {
	    DEBUG_WC(F("WiFi AP STA - Parameters Portal"));
  } else {
		DEBUG_WC(F("WiFi AP STA - Configuration Portal"));
  }
  _lastAPPage = millis();
  //  WiFi.mode(WIFI_AP);//Fix for scan bug when switching from STA to AP STA
  //  delay(1);
  //  WiFi.mode(WIFI_AP_STA);
  //  delay(1);
	
#ifdef ARDUINO_ARCH_ESP8266	
	WiFi.setSleepMode(WIFI_NONE_SLEEP);
#endif 

  delay(50);

  if (WiFi.status() != WL_CONNECTED) {
	  if (paramsMode) {
		   // Can't show the parameters portal if not connected to a WiFi network.
		   startConfigurationPortal(AP_WAIT, apName, apPassword, false);
	  } else {
      DEBUG_WC("startConfigurationPortal(): WiFi.mode(WIFI_AP)");
		  WiFi.mode(WIFI_AP);
	  }
  } else {
    WiFi.mode(WIFI_AP_STA); // start an access point on the same channel we're already connected to.
  }
  dnsServer.reset(new DNSServer());
#ifdef ESP8266
  server.reset(new ESP8266WebServer(80));
#else
  server.reset(new WebServer(80));
#endif
  setAPName(apName);
  DEBUG_WC(_apName);

  if (strlen(apPassword)>0){
    if (strlen(apPassword) < 8 || strlen(apPassword) > 63) {
      // fail passphrase to short or long!
      DEBUG_WC(F("Invalid AccessPoint password. Ignoring"));
      apPassword = NULL;
    }
    //_apPassword = apPassword;
    strcpy(_apPassword,apPassword);
    DEBUG_WC(_apPassword);
  }

  //optional soft ip config
  if (_ap_static_ip) {
    DEBUG_WC(F("Custom AP IP/GW/Subnet"));
    WiFi.softAPConfig(_ap_static_ip, _ap_static_gw, _ap_static_sn);
  }

  //if (_apPassword != NULL && _apPassword!="") {
  if(strlen(apPassword)>0){
    WiFi.softAP(_apName, _apPassword);//password option
  } else {
    WiFi.softAP(_apName);
    DEBUG_WC("startConfigurationPortal(): WiFi.softAP(_apName)");
  }

  delay(500); // Without delay I've seen the IP address blank
  DEBUG_WC(F("AP IP address: "));
  DEBUG_WC(WiFi.softAPIP());
  
  // Show on OLED depending on the mode
  if (!paramsMode) { displayAP(); } else {   displayParams(); }
  
  /* Setup the DNS server redirecting all the domains to the apIP */
  dnsServer->setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer->start(DNS_PORT, "*", WiFi.softAPIP());

  if (paramsMode)
  {
	  
	  server->on("/", std::bind(&WiFiConnect::handleParamRoot, 			this));
	  server->on("/param", std::bind(&WiFiConnect::handleParams, 		this));
	  server->on("/params", std::bind(&WiFiConnect::handleParams, 		this));
	  server->on("/wifisave", std::bind(&WiFiConnect::handleWifiSave, 	this));
	  server->on("/i", std::bind(&WiFiConnect::handleInfo, 				this));
	  //server->on("/r", std::bind(&WiFiConnect::handleReset, this)); // doesn't work - causes boot loop
	  //server->on("/generate_204", std::bind(&WiFiConnect::handle204, this));  //Android/Chrome OS captive portal check.
	  server->on("/fwlink", std::bind(&WiFiConnect::handleParamRoot, 	this));  //Microsoft captive portal. Maybe not needed. Might be handled by notFound handler.
	  server->on("/hotspot_detect.html", std::bind(&WiFiConnect::handleParamRoot, this));
	  
  } else  { // Config portal mode
	  
	  /* Setup web pages: root, wifi config pages, SO captive portal detectors and not found. */
	  server->on("/", 			std::bind(&WiFiConnect::handleRoot, this));
	  server->on("/wifi", 		std::bind(&WiFiConnect::handleWifi, this, true));   // Auto Scan of APs
	  server->on("/0wifi", 		std::bind(&WiFiConnect::handleWifi, this, false)); // Manual entry form only
	  server->on("/wifisave", 	std::bind(&WiFiConnect::handleWifiSave, this));
	  server->on("/i", 			std::bind(&WiFiConnect::handleInfo, this)); // Not of interest - commented out in static HTML
	  server->on("/r", 			std::bind(&WiFiConnect::handleReset, this));
	  //server->on("/generate_204", std::bind(&WiFiConnect::handle204, this));  //Android/Chrome OS captive portal check.
	  server->on("/fwlink", 	std::bind(&WiFiConnect::handleRoot, this));  //Microsoft captive portal. Maybe not needed. Might be handled by notFound handler.
	  server->on("/hotspot_detect.html", std::bind(&WiFiConnect::handleRoot, this));
	  
  } // config portal  

  	server->onNotFound 	   (std::bind(&WiFiConnect::handleNotFound, this));
    server->begin(); // Web server start
    DEBUG_WC(F("HTTP server started"));

  //notify we entered AP mode
  if ( _apcallback != NULL) {
    _apcallback(this);
  }
  
  if (apcontinue == AP_WAIT)
	  DEBUG_WC(F("AP to stay alive indefinitely waiting for configuration."));
		

  _lastAPPage = millis();
  _readyToConnect = false;	  
  while (true) {
	
	if (apcontinue != AP_WAIT)	// Stay here if the AP_LOOP enabled	
		if (millis() - (unsigned long int)_lastAPPage >= ( (unsigned int)_apTimeoutMins * 60 * 1000)) {
		  break;
		}
		
    dnsServer->processNextRequest();
    server->handleClient();
    if (_readyToConnect) {
      _readyToConnect = false;

      DEBUG_WC(F("startConfigurationPortal(): Calling: autoConnect(_ssid.c_str(), _password.c_str(), WIFI_AP_STA)"));	      

      if (autoConnect(_ssid.c_str(), _password.c_str(), WIFI_AP_STA)) {
		  
        DEBUG_WC(F("Connection was a success, so changing to WIFI_STA mode only."));		
        WiFi.mode(WIFI_STA);
        delay(500);
        //WiFi.reconnect();
        //delay(500);
        if (_savecallback != NULL) {
          _savecallback();
        }
        break; // we connected!
      }
      else
      {
        DEBUG_WC(F("Connection was a failure. We keep waiting."));		  
      }
    } // ready to connect
	
    yield();
  }
  
  //teardown??
  DEBUG_WC(F("Exiting AP (or AP Params) Mode"));
  server->close();
  server.reset();

  dnsServer.reset();
  boolean con = (WiFi.status() == WL_CONNECTED);
  if (!con) {
    switch (apcontinue) {
      case AP_WAIT:
        break;
      case AP_NONE:
        DEBUG_WC(F("No AP continue action"));
        break;
      case AP_LOOP:
        DEBUG_WC(F("AP to turn off and stay in loop lockup not being accessible."));
        displayManualReset();
        displayTurnOFF(5 * 60 * 100); //5mins
        WiFi.mode(WIFI_OFF);
        while (true) {
          displayLoop();
          delay(1000);
          yield();
        }
	
        break;
      case AP_RESTART:
       case AP_RESET:
        displayManualReset();
        DEBUG_WC(F("AP restart chip"));
        delay(1000);
#if defined(ESP8266)
        ESP.reset();
#else
        ESP.restart();
#endif
        delay(2000);
    }
    WiFi.mode(WIFI_STA);
  }
  return con;
}
/**************************************************************************/
/*!
    @brief  Tries to connect to the last connected WiFi network.
    @return Returns wether WiFi is connected

    @section example_startConfigurationPortal Example

    The return value can be used to automatically start the access point
    so you may change networks if required.

    @code
    if(!wificonnect.autoConnect()){
        //Start the access point
        wificonnect.startConfigurationPortal();
    }
    @endcode
*/
/**************************************************************************/
boolean WiFiConnect::autoConnect() {
  return autoConnect(NULL, NULL, WIFI_STA);
}
/**************************************************************************/
/*!
    @brief  Tries to connect to the specified WiFi network.
    @param ssidName
            The SSID of the netqork you want to connect to.
    @param ssidPassword
           The password for a secure network.
    @param WiFiMode
           The WiFi mode
    @return Returns wether WiFi is connected
*/
/**************************************************************************/
boolean WiFiConnect::autoConnect(char const *ssidName, char const *ssidPassword, WiFiMode_t acWiFiMode) {
/*
 #ifdef ESP32
    WiFi.persistent(false); // disable persistent for esp32 after esp_wifi_start or else saves wont work (from WiFiManager)
 #endif  
*/

  DEBUG_WC(F("Auto Connect"));
  WiFi.mode(acWiFiMode);
  DEBUG_WC("autoConnect():WiFi.mode(acWiFiMode)");
  if (WiFi.status() == WL_CONNECTED) {
    DEBUG_WC(F("Already Connected"));
	  DEBUG_WC(WiFi.localIP());
    return true;
  }
  if (_sta_static_ip) {
    DEBUG_WC(F("Custom STA IP/GW/Subnet"));
    WiFi.config(_sta_static_ip, _sta_static_gw, _sta_static_sn);
    DEBUG_WC(WiFi.localIP());
  }
  
 //fix for auto connect racing issue
 /*
  if (WiFi.status() == WL_CONNECTED && (WiFi.SSID() == String(ssidName))) {
    DEBUG_WC(F("Already connected. Bailing out."));
	  DEBUG_WC(WiFi.localIP());
	  return true;
    //return WL_CONNECTED;
  }
*/

  int c = 0;
  while (c < _retryAttempts) {
    displayConnecting(c + 1, _retryAttempts);
    long ms = millis();
    if (ssidName == NULL || strlen(ssidName)==0) {
    
    #ifdef ESP8266
        if (WiFi.SSID() == "")
        {
          DEBUG_WC(F("No ESP8266 WiFi SSID configuration stored. Bailing."));
          return false;
        }    
        DEBUG_WC(F("Stored SSID:")); DEBUG_WC(WiFi.SSID());        
    #endif

    #ifdef ESP32
      // WiFi.SSID() Always returns null on ESP32.... Arduino framework bug?
      // So use lower-level IDF function to pull persistent configuration.
      wifi_config_t conf;
      esp_wifi_get_config(WIFI_IF_STA, &conf);

      String stored_ssid = String(reinterpret_cast<const char*>(conf.sta.ssid));
      if (stored_ssid == "")
      {
        DEBUG_WC(F("No ESP32 WiFi SSID configuration stored. Bailing."));
        return false;
      }       

        DEBUG_WC(F("Stored SSID:")); DEBUG_WC(stored_ssid);              
    #endif

        
      WiFi.begin(); // persistence is on by default, so if this WiFi connection should happen automatically
      DEBUG_WC("autoConnect(): WiFi.begin()");

/*          
    #ifdef ESP32
                            //https://forum.arduino.cc/index.php?topic=652513.0
      int  wifi_retry = 0;   // COUNTER SOLVES ESP32-BUG WITH CERTAIN ROUTERS: CONNECTION ONLY ESTABLISHED EVERY SECOND TIME
    
      while (WiFi.waitForConnectResult() != WL_CONNECTED && wifi_retry < 3) {
          DEBUG_WC("WLAN Not yet connected on ESP32...retrying");
          WiFi.begin();
          delay(250);
          wifi_retry++;
      }

    #endif
*/

    } else {
      DEBUG_WC(F("Connecting with SSID & Password"));
      DEBUG_WC(ssidName);
      DEBUG_WC(ssidPassword);
      WiFi.begin(ssidName, ssidPassword);
      DEBUG_WC("autoConnect(): WiFi.begin(ssidName, ssidPassword)");
    }


    while (millis() - (unsigned long int)ms < ( (unsigned int)_connectionTimeoutSecs * 1000)) {
      int ws = WiFi.status();
      if (ws == WL_CONNECTED) {
        DEBUG_WC(F("WIFI_CONNECTED"));
        delay(500);//wait for ip to refresh
        DEBUG_WC(WiFi.localIP());
        displayConnected();
        return true;
      } else if (ws == WL_CONNECT_FAILED) {
        DEBUG_WC(F("WIFI_CONNECT_FAILED"));
        delay(500);
        //return false;
      } else {
        delay(200);
        yield();
      }
    }
    DEBUG_WC(statusToString(WiFi.status()));
    c++;
  } // attemps
  DEBUG_WC(statusToString(WiFi.status()));
  return false;
}
/**************************************************************************/
/*!
    @brief  Sets how many times we should try to connect to the WiFi network.
    @param  attempts
            How may attampts.
*/
/**************************************************************************/
void WiFiConnect::setRetryAttempts(int attempts) {
  if (attempts >= 1) {
    _retryAttempts = attempts;
  }
}
/**************************************************************************/
/*!
    @brief  Sets how long to wait for the connection before failing.
    @param  timeout
            How may seconds to wait for the connection to be made.
*/
/**************************************************************************/
void WiFiConnect::setConnectionTimeoutSecs(int timeout) {
  if (timeout >= 1) {
    _connectionTimeoutSecs = timeout;
  }
}
/**************************************************************************/
/*!
    @brief  A helper to clear the settings for the last connected network.
            Remember to comment out or remove and re-upload your code
            otherwise chip will constantly restart.
*/
/**************************************************************************/
void WiFiConnect::resetSettings() {
  DEBUG_WC(F("Clearing Settings for:"));
  DEBUG_WC(WiFi.SSID());
#if defined(ESP8266)
  WiFi.disconnect(true);
  delay(1000);
  ESP.reset();
#else
  WiFi.disconnect(true);//doesnt seem to work
  esp_wifi_restore();//doesnt seem to work
  WiFi.begin("0", "0"); //HACK
  delay(1000);
  ESP.restart();
#endif
  delay(2000);
}
/**************************************************************************/
/*!
    @brief  A helper function to return the string version of a
            wifi network state.
    @param  state
            The state that we want the string representation of.
    @return WiFi state as a string.
*/
/**************************************************************************/
const char* WiFiConnect::statusToString(int state) {
  switch (state) {
    case WL_CONNECTED:
      return "WL_CONNECTED";
    case WL_CONNECT_FAILED:
      return "WL_CONNECT_FAILED";
    case WL_CONNECTION_LOST:
      return "WL_CONNECTION_LOST";
    case WL_DISCONNECTED:
      return "WL_DISCONNECTED";
    case WL_SCAN_COMPLETED:
      return "WL_SCAN_COMPLETED";
    case WL_NO_SSID_AVAIL:
      return "WL_NO_SSID_AVAIL";
    case WL_IDLE_STATUS:
      return "WL_IDLE_STATUS";
    case WL_NO_SHIELD:
      return "WL_NO_SHIELD";
    default:
      return "UNKNOWN CODE";
  }
}
/**************************************************************************/
/*!
    @brief  Outputs debug messages
    @param  text
            The text to be outputted
*/
/**************************************************************************/
template <typename Generic>
void WiFiConnect::DEBUG_WC(Generic text) {
  if (_debug) {
    Serial.print("*WC: ");
    Serial.println(text);
  }
}
/**************************************************************************/
/*!
    @brief  Handles the web request for root in the Parameters Portal and
            sends back the html menu
*/
/**************************************************************************/
void WiFiConnect::handleParamRoot() {
  if (captivePortal()) { // If captive portal redirect instead of displaying the page.
    return;
  }
  _lastAPPage = millis();
  DEBUG_WC("Sending Root");
  String page = FPSTR(AP_HTTP_HEAD);
  page.replace("{v}", "Options");
  page += FPSTR(AP_HTTP_SCRIPT);
  page += FPSTR(AP_HTTP_STYLE);
  page += FPSTR(AP_HTTP_HEAD_END);
  page += String(F("<h1>"));
  page += _apName;
  page += String(F("</h1>"));
//  page += String(F("<h3>WiFiConnect</h3>"));
  page += FPSTR(AP_HTTP_PORTAL_PARAM_OPTIONS);
  page += FPSTR(AP_HTTP_END);

  server->sendHeader("Content-Length", String(page.length()));
  server->send(200, "text/html", page);

}
/**************************************************************************/
/*!
    @brief  Handles the web request for displaying custom parameters
            in the Parameters Portal and sends back the html
*/
/**************************************************************************/
void WiFiConnect::handleParams() {
  _lastAPPage = millis();
  DEBUG_WC(F("Sending Params"));

  String page = FPSTR(AP_HTTP_HEAD);
  page.replace("{v}", "Config Params");
  page += FPSTR(AP_HTTP_SCRIPT);
  page += FPSTR(AP_HTTP_STYLE);
  page += FPSTR(AP_HTTP_HEAD_END);
  page += FPSTR(AP_HTTP_FORM_PARAM_START);
  char parLength[4];
  // add the extra parameters to the form
  for (int i = 0; i < _paramsCount; i++) {
    if (_params[i] == NULL) {
      break;
    }

    String pitem = FPSTR(AP_HTTP_FORM_PARAM);
    if (_params[i]->getID() != NULL) {
      pitem.replace("{i}", _params[i]->getID());
      pitem.replace("{n}", _params[i]->getID());
      pitem.replace("{p}", _params[i]->getPlaceholder());
      snprintf(parLength, 4, "%d", _params[i]->getValueLength());
      pitem.replace("{l}", parLength);
      pitem.replace("{v}", _params[i]->getValue());
      pitem.replace("{c}", _params[i]->getCustomHTML());
    } else {
      pitem = _params[i]->getCustomHTML();
    }

    page += pitem;
  }
  if (_params[0] != NULL) {
    page += "<br/>";
  }

  page += FPSTR(AP_HTTP_FORM_END);

  page += FPSTR(AP_HTTP_END);

  server->sendHeader("Content-Length", String(page.length()));
  server->send(200, "text/html", page);
}
/**************************************************************************/
/*!
    @brief  Handles the web request for displaying the menu in the
            Access Point portal.
*/
/**************************************************************************/
void WiFiConnect::handleRoot() {
  if (captivePortal()) { // If captive portal redirect instead of displaying the page.
    return;
  }
  _lastAPPage = millis();
  DEBUG_WC("Sending Root");
  String page = FPSTR(AP_HTTP_HEAD);
  page.replace("{v}", "Options");
  page += FPSTR(AP_HTTP_SCRIPT);
  page += FPSTR(AP_HTTP_STYLE);
  page += FPSTR(AP_HTTP_HEAD_END);
  page += String(F("<h1>"));
  page += _apName;
  page += String(F("</h1>"));
  //page += String(F("<h3>WiFiConnect</h3>"));
  page += FPSTR(AP_HTTP_PORTAL_OPTIONS);
  page += FPSTR(AP_HTTP_END);

  server->sendHeader("Content-Length", String(page.length()));
  server->send(200, "text/html", page);


}

/**************************************************************************/
/*!
    @brief  Handles the web request for entering the SSID and Password of
            the network you want to connect too.
            Optionally scans and shows available networks.
    @param  scan
            Whether to scan for networks or not.
*/
/**************************************************************************/
void WiFiConnect::handleWifi(boolean scan) {

  _lastAPPage = millis();
  DEBUG_WC(F("Sending WiFi"));

  String page = FPSTR(AP_HTTP_HEAD);
  page.replace("{v}", "Select WiFi");
  page += FPSTR(AP_HTTP_SCRIPT);
  page += FPSTR(AP_HTTP_STYLE);
  page += FPSTR(AP_HTTP_HEAD_END);

  if (scan) {
    int n = WiFi.scanNetworks();
    DEBUG_WC(F("Scan done"));
    if (n == 0) {
      DEBUG_WC(F("No networks found"));
      page += F("No networks found. Refresh to scan again.");
    } else {

      //sort networks
      int indices[n];
      for (int i = 0; i < n; i++) {
        indices[i] = i;
      }

      // RSSI SORT

      // old sort
      for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
          if (WiFi.RSSI(indices[j]) > WiFi.RSSI(indices[i])) {
            std::swap(indices[i], indices[j]);
          }
        }
      }

      /*std::sort(indices, indices + n, [](const int & a, const int & b) -> bool
        {
        return WiFi.RSSI(a) > WiFi.RSSI(b);
        });*/

      // remove duplicates ( must be RSSI sorted )
      if (_removeDuplicateAPs) {
        String cssid;
        for (int i = 0; i < n; i++) {
          if (indices[i] == -1) continue;
          cssid = WiFi.SSID(indices[i]);
          for (int j = i + 1; j < n; j++) {
            if (cssid == WiFi.SSID(indices[j])) {
              DEBUG_WC("DUP AP: " + WiFi.SSID(indices[j]));
              indices[j] = -1; // set dup aps to index -1
            }
          }
        }
      }

      //display networks in page
      for (int i = 0; i < n; i++) {
        if (indices[i] == -1) continue; // skip dups
        DEBUG_WC(WiFi.SSID(indices[i]));
        DEBUG_WC(WiFi.RSSI(indices[i]));
        int quality = getRSSIasQuality(WiFi.RSSI(indices[i]));

        if (_minimumQuality == -1 || _minimumQuality < quality) {
          String item = FPSTR(AP_HTTP_ITEM);
          String rssiQ;
          rssiQ += quality;
          item.replace("{v}", WiFi.SSID(indices[i]));
          item.replace("{r}", rssiQ);
#if defined(ESP8266)
          if (WiFi.encryptionType(indices[i]) != ENC_TYPE_NONE) {
#else
          if (WiFi.encryptionType(indices[i]) != WIFI_AUTH_OPEN) {
#endif
            item.replace("{i}", "l");
          } else {
            item.replace("{i}", "");
          }
          //DEBUG_WM(item);
          page += item;
          delay(0);
        } else {
          DEBUG_WC(F("Skipping due to quality"));
        }

      }
      page += "<br/>";
    }
  }

  page += FPSTR(AP_HTTP_FORM_START);
  char parLength[4];
  // add the extra parameters to the form
  for (int i = 0; i < _paramsCount; i++) {
    if (_params[i] == NULL) {
      break;
    }

    String pitem = FPSTR(AP_HTTP_FORM_PARAM);
    if (_params[i]->getID() != NULL) {
      pitem.replace("{i}", _params[i]->getID());
      pitem.replace("{n}", _params[i]->getID());
      pitem.replace("{p}", _params[i]->getPlaceholder());
      snprintf(parLength, 4, "%d", _params[i]->getValueLength());
      pitem.replace("{l}", parLength);
      pitem.replace("{v}", _params[i]->getValue());
      pitem.replace("{c}", _params[i]->getCustomHTML());
    } else {
      pitem = _params[i]->getCustomHTML();
    }

    page += pitem;
  }
  if (_params[0] != NULL) {
    page += "<br/>";
  }

  if (_sta_static_ip) {

    String item = FPSTR(AP_HTTP_FORM_PARAM);
    item.replace("{i}", "ip");
    item.replace("{n}", "ip");
    item.replace("{p}", "Static IP");
    item.replace("{l}", "15");
    item.replace("{v}", _sta_static_ip.toString());

    page += item;

    item = FPSTR(AP_HTTP_FORM_PARAM);
    item.replace("{i}", "gw");
    item.replace("{n}", "gw");
    item.replace("{p}", "Static Gateway");
    item.replace("{l}", "15");
    item.replace("{v}", _sta_static_gw.toString());

    page += item;

    item = FPSTR(AP_HTTP_FORM_PARAM);
    item.replace("{i}", "sn");
    item.replace("{n}", "sn");
    item.replace("{p}", "Subnet");
    item.replace("{l}", "15");
    item.replace("{v}", _sta_static_sn.toString());

    page += item;

    page += "<br/>";
  }

  page += FPSTR(AP_HTTP_FORM_END);
  page += FPSTR(AP_HTTP_SCAN_LINK);

  page += FPSTR(AP_HTTP_END);

  server->sendHeader("Content-Length", String(page.length()));
  server->send(200, "text/html", page);
}
void WiFiConnect::handleWifiSave() {
  _lastAPPage = millis();
  DEBUG_WC(F("Sending WiFi Save"));
  //SAVE/connect here
  if (_debug) {
    Serial.println(F("*WC Form Args"));
    for (int x = 0; x < server->args(); x++) {
      Serial.print(F("*WC "));
      Serial.print(server->argName(x));
      Serial.print(F("="));
      Serial.println(server->arg(x));
    }
  }
  _ssid = server->arg("s").c_str();
  _ssid.trim();
  DEBUG_WC(_ssid);
  _password = server->arg("p").c_str();
  _password.trim();
  DEBUG_WC(_password);
  //parameters
  for (int i = 0; i < _paramsCount; i++) {
    if (_params[i] == NULL) {
      break;
    }
    //read parameter
    String value = server->arg(_params[i]->getID()).c_str();
    //store it in array
    value.toCharArray(_params[i]->_value, _params[i]->_length);
    DEBUG_WC(F("Parameter"));
    DEBUG_WC(_params[i]->getID());
    DEBUG_WC(value);
  }

  if (server->arg("ip") != "") {
    DEBUG_WC(F("static ip"));
    DEBUG_WC(server->arg("ip"));
    //_sta_static_ip.fromString(server->arg("ip"));
    String ip = server->arg("ip");
    optionalIPFromString(&_sta_static_ip, ip.c_str());
  }
  if (server->arg("gw") != "") {
    DEBUG_WC(F("static gateway"));
    DEBUG_WC(server->arg("gw"));
    String gw = server->arg("gw");
    optionalIPFromString(&_sta_static_gw, gw.c_str());
  }
  if (server->arg("sn") != "") {
    DEBUG_WC(F("static netmask"));
    DEBUG_WC(server->arg("sn"));
    String sn = server->arg("sn");
    optionalIPFromString(&_sta_static_sn, sn.c_str());
  }

  String page = FPSTR(AP_HTTP_HEAD);
  page.replace("{v}", "Credentials Saved");
  page += FPSTR(AP_HTTP_SCRIPT);
  page += FPSTR(AP_HTTP_STYLE);
  page += FPSTR(AP_HTTP_HEAD_END);
  page += FPSTR(AP_HTTP_SAVED);
  page.replace("{ap}", _ssid);
  page += FPSTR(AP_HTTP_END);

  server->sendHeader("Content-Length", String(page.length()));
  server->send(200, "text/html", page);
  _readyToConnect = true;
}
/**************************************************************************/
/*!
    @brief  Handles the web request and shows basic information about the chip.
            TODO: ESP32 information still needs completing.
*/
/**************************************************************************/
void WiFiConnect::handleInfo() {
  _lastAPPage = millis();  DEBUG_WC(F("Sending Info"));

  String page = FPSTR(AP_HTTP_HEAD);
  page.replace("{v}", "Info");
  page += FPSTR(AP_HTTP_SCRIPT);
  page += FPSTR(AP_HTTP_STYLE);
  page += FPSTR(AP_HTTP_HEAD_END);
  page += F("<dl>");
  page += F("<dt>Chip ID</dt><dd>");
  page += ESP_getChipId();
  page += F("</dd>");
  page += F("<dt>Flash Chip ID</dt><dd>");
#if defined(ESP8266)
  page += ESP.getFlashChipId();
#else
  // TODO
  page += F("TODO");
#endif
  page += F("</dd>");
  page += F("<dt>IDE Flash Size</dt><dd>");
  page += ESP.getFlashChipSize();
  page += F(" bytes</dd>");
  page += F("<dt>Real Flash Size</dt><dd>");
#if defined(ESP8266)
  page += ESP.getFlashChipRealSize();
#else
  // TODO
  page += F("TODO");
#endif
  page += F(" bytes</dd>");
  page += F("<dt>Soft AP IP</dt><dd>");
  page += WiFi.softAPIP().toString();
  page += F("</dd>");
  page += F("<dt>Soft AP MAC</dt><dd>");
  page += WiFi.softAPmacAddress();
  page += F("</dd>");
  page += F("<dt>Station MAC</dt><dd>");
  page += WiFi.macAddress();
  page += F("</dd>");
  page += F("</dl>");
  page += FPSTR(AP_HTTP_END);

  server->sendHeader("Content-Length", String(page.length()));
  server->send(200, "text/html", page);

  DEBUG_WC(F("Sent info page"));
}
/**************************************************************************/
/*!
    @brief  Handles the reset web request and and restarts the chip.
            Does not clear settings.
*/
/**************************************************************************/
void WiFiConnect::handleReset() {
  _lastAPPage = millis();
  DEBUG_WC(F("Sending Reset"));

  String page = FPSTR(AP_HTTP_HEAD);
  page.replace("{v}", "Info");
  page += FPSTR(AP_HTTP_SCRIPT);
  page += FPSTR(AP_HTTP_STYLE);
  page += FPSTR(AP_HTTP_HEAD_END);
  page += F("Module will reset in a few seconds.");
  page += FPSTR(AP_HTTP_END);

  server->sendHeader("Content-Length", String(page.length()));
  server->send(200, "text/html", page);

  DEBUG_WC(F("Sent reset page"));
  delay(5000);
#if defined(ESP8266)
  ESP.reset(); // causes boot loop 
#else
  ESP.restart();
#endif
  delay(2000);

}
/**************************************************************************/
/*!
    @brief  Handles the 204 web request from Android devices
*/
/**************************************************************************/
void WiFiConnect::handle204() {
  _lastAPPage = millis();
  DEBUG_WC(F("Sending 204"));
  handleRoot();
}
/**************************************************************************/
/*!
    @brief  Handles any web requests that are not found.
*/
/**************************************************************************/
void WiFiConnect::handleNotFound() {
  if (captivePortal()) { // If captive portal redirect instead of displaying the error page.
    DEBUG_WC(F("Webserver called handleNotFound();"));  
    return;
  }
  _lastAPPage = millis();
  DEBUG_WC(F("Sending Not Found"));
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server->uri();
  message += "\nMethod: ";
  message += ( server->method() == HTTP_GET ) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server->args();
  message += "\n";

  for ( uint8_t i = 0; i < server->args(); i++ ) {
    message += " " + server->argName ( i ) + ": " + server->arg ( i ) + "\n";
  }
  server->sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server->sendHeader("Pragma", "no-cache");
  server->sendHeader("Expires", "-1");
  server->sendHeader("Content-Length", String(message.length()));
  server->send ( 404, "text/plain", message );
}

/**************************************************************************/
/*!
    @brief  Redirect to captive portal if we get a request for another domain.
            Return true in that case so the page handler do not try to
            handle the request again.
    @return True if we have redirected to our portal, else false and contimue
            to handle request
*/
/**************************************************************************/
boolean WiFiConnect::captivePortal() {
	DEBUG_WC(server->hostHeader());
	
  if (!isIp(server->hostHeader()) ) {
    _lastAPPage = millis();
    DEBUG_WC(F("Request redirected to captive portal"));
    String msg = "redirect\n";
    server->sendHeader("Location", String("http://") + toStringIp(server->client().localIP()), true);
    server->sendHeader("Content-Length", String(msg.length()));
    server->send ( 302, "text/plain", msg); // Empty content inhibits Content-length header so we have to close the socket ourselves.
    //server->client().stop(); // Stop is needed because we sent no content length

    return true;
  }
  return false;
}

/**************************************************************************/
/*!
    @brief  Sets the function to be called when we enter Access Point
            for configuration.
            Gets passed a the WiFiConnect for additional usage within function.
    @param  func
            The function to be called.

*/
/**************************************************************************/
void WiFiConnect::setAPCallback( void (*func)(WiFiConnect* myWiFiConnect) ) {
  _apcallback = func;
}
/**************************************************************************/
/*!
    @brief  Sets the function to be called when we need to save the
            custom parameters/configuration.
    @param  func
            The function to be called.
            This function should be short running and ideally just set.
            a flag for processing else where.
*/
/**************************************************************************/
void WiFiConnect::setSaveConfigCallback( void (*func)(void) ) {
  _savecallback = func;
}
/**************************************************************************/
/*!
    @brief  Function to convert RSSI into a usable range 0-100 so we can
            use it to exclude poor networks.
    @param  RSSI
            The quality/signal strength of the WiFi network.
    @return Value in the range of 0-100 to network indicate quality.

*/
/**************************************************************************/
int WiFiConnect::getRSSIasQuality(int RSSI) {
  int quality = 0;

  if (RSSI <= -100) {
    quality = 0;
  } else if (RSSI >= -50) {
    quality = 100;
  } else {
    quality = 2 * (RSSI + 100);
  }
  return quality;
}
/**************************************************************************/
/*!
    @brief  Function to check if a given string is an IP Address.
    @param  str
            The string to process.
    @return True if inputted string is an IP Address.

*/
/**************************************************************************/
boolean WiFiConnect::isIp(String str) {
  for (unsigned int i = 0; i < str.length(); i++) {
    int c = str.charAt(i);
    if (c != '.' && (c < '0' || c > '9')) {
      return false;
    }
  }
  return true;
}
/**************************************************************************/
/*!
    @brief  Function to return a IPAddress as a string representation.
    @param  ip
            The IPAddress to process.
    @return String version of the IPAddress

*/
/**************************************************************************/
String WiFiConnect::toStringIp(IPAddress ip) {
  String res = "";
  for (int i = 0; i < 3; i++) {
    res += String((ip >> (8 * i)) & 0xFF) + ".";
  }
  res += String(((ip >> 8 * 3)) & 0xFF);
  return res;
}
/**************************************************************************/
/*!
    @brief  Used to turn on or off messages to the serial port/monitor.
    @param  isDebug
            Set to true to enable messages.
*/
/**************************************************************************/
void WiFiConnect::setDebug(boolean isDebug) {
  _debug = isDebug;
}

/**************************************************************************/
/*!
    @brief  Used to set a static ip/gateway and subnet mask for the access point.
            IP and DNS Gateway are normally the same for a captive portal.
    @param  ip
            The IP address that you want to access the portal through.
    @param  gw
            The gateway address for the DNS server, usually the same as IP for
            captive portal.
    @param  sn
            The subnet mask for the access point, usually 255.255.255.0
*/
/**************************************************************************/
void          WiFiConnect::setAPStaticIPConfig(IPAddress ip, IPAddress gw, IPAddress sn) {
  _ap_static_ip = ip;
  _ap_static_gw = gw;
  _ap_static_sn = sn;
}
/**************************************************************************/
/*!
    @brief  Used to set a static ip/gateway and subnet mask for the local
            network.
    @param  ip
            The IP address that you want to use on the network.
    @param  gw
            The gateway address for the DNS server or network router.
    @param  sn
            The subnet mask for the access point, usually 255.255.255.0
            for local networks.
*/
/**************************************************************************/
void          WiFiConnect::setSTAStaticIPConfig(IPAddress ip, IPAddress gw, IPAddress sn) {
  _sta_static_ip = ip;
  _sta_static_gw = gw;
  _sta_static_sn = sn;
}
