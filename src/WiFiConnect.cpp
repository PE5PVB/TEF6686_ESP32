/*!
   @file WiFiConnect.cpp

   @mainpage WiFi Connection Manager with Captive Portal

   @section intro_sec Introduction

   WiFi connection manager for ESP32 with captive portal for configuration.
   Based on WiFiConnect by Stuart Blair (https://github.com/smurf0969/WiFiConnect),
   derived from WiFiManager by tzapu (https://github.com/tzapu/WiFiManager).

   @section license License

   GNU General Public License v3.0
*/
#include "WiFiConnect.h"

#include "constants.h"

// ---- CSS for the captive portal ----

static const char TPL_STYLE[] PROGMEM =
  "<style>"
  "*{margin:0;padding:0;box-sizing:border-box}"
  "body{font-family:-apple-system,'Segoe UI',system-ui,sans-serif;background:#202228;color:#fff;min-height:100vh}"
  ".w{max-width:440px;margin:0 auto;padding:20px 16px}"
  ".logo{display:block;margin:0 auto 8px;max-width:160px;height:auto}"
  "h1{color:#5bd6ab;font-size:.92em;font-weight:600;text-transform:uppercase;letter-spacing:3px;"
    "text-align:center;padding-bottom:12px;margin-bottom:18px;border-bottom:1px solid rgba(91,214,171,.15)}"
  ".msg{background:rgba(46,80,73,.3);border:1px solid rgba(60,127,106,.2);border-radius:12px;"
    "padding:14px 18px;font-size:.88em;color:#a0a8b0;line-height:1.6;margin-bottom:20px;text-align:center}"
  ".cd{background:rgba(46,80,73,.12);border:1px solid rgba(60,127,106,.18);border-radius:14px;"
    "padding:16px;margin-bottom:14px}"
  ".cd h2{font-size:.7em;color:#4db691;text-transform:uppercase;letter-spacing:1.5px;"
    "margin-bottom:12px;font-weight:600;padding-left:10px;border-left:3px solid #4db691}"
  "button,input[type=submit]{display:block;width:100%;padding:14px;background:#4db691;"
    "color:#1a1c20;border:0;border-radius:12px;font-size:.92em;font-weight:600;"
    "font-family:inherit;text-transform:uppercase;letter-spacing:.5px;cursor:pointer;"
    "margin-bottom:8px;transition:background .2s}"
  "button:hover{background:#5bd6ab}"
  ".alt{background:0 0;color:#8090a0;border:1px solid rgba(60,127,106,.3);"
    "text-transform:none;font-weight:400;font-size:.82em;letter-spacing:0;padding:10px}"
  ".alt:hover{background:rgba(46,80,73,.2);color:#c0c8d0;border-color:#3c7f6a}"
  "label{display:block;font-size:.7em;color:#6a7280;text-transform:uppercase;"
    "letter-spacing:1px;margin:8px 0 4px;font-weight:500}"
  "input[type=text],input[type=password]{display:block;width:100%;padding:11px 14px;"
    "background:rgba(20,22,26,.5);border:1px solid rgba(60,127,106,.22);border-radius:10px;"
    "color:#e0e4e8;font-size:.9em;font-family:inherit;margin-bottom:10px;outline:0;"
    "transition:border .2s;-webkit-appearance:none}"
  "input[type=text]:focus,input[type=password]:focus{border-color:#5bd6ab}"
  "input::placeholder{color:#3a4250}"
  ".n{background:rgba(20,22,26,.35);border:1px solid rgba(60,127,106,.12);"
    "border-radius:10px;padding:10px 12px;margin-bottom:5px;cursor:pointer;"
    "display:flex;align-items:center;gap:10px;transition:border .2s}"
  ".n:hover{border-color:#3c7f6a}.n:active{border-color:#5bd6ab}"
  ".n span:first-child{color:#d0d4d8;flex:1;overflow:hidden;text-overflow:ellipsis;"
    "white-space:nowrap;font-size:.88em}"
  ".q{display:flex;align-items:center;gap:5px;font-size:.72em;color:#505868;"
    "font-family:ui-monospace,monospace;white-space:nowrap}"
  ".sig{display:flex;align-items:flex-end;gap:1px;height:12px}"
  ".sig i{display:block;width:3px;background:#1a2a24;border-radius:1px}"
  ".sig i:nth-child(1){height:3px}.sig i:nth-child(2){height:6px}"
  ".sig i:nth-child(3){height:9px}.sig i:nth-child(4){height:12px}"
  ".s1 i:nth-child(1){background:#f85149}"
  ".s2 i:nth-child(-n+2){background:#e8a838}"
  ".s3 i:nth-child(-n+3){background:#4db691}"
  ".s4 i{background:#5bd6ab}"
  ".lk{font-size:.55em;color:#505868;margin-left:1px}.lk::after{content:'\\1F512'}"
  ".ok,.fail{text-align:center;padding:18px;border-radius:14px;margin-top:16px;"
    "display:none;line-height:1.6}"
  ".ok{background:rgba(46,80,73,.3);border:1px solid rgba(60,127,106,.2);color:#5bd6ab}"
  ".fail{background:rgba(74,32,32,.3);border:1px solid rgba(106,48,48,.2);color:#f85149}"
  ".fail a{color:#f85149}"
  ".ld::after{content:'';display:inline-block;width:22px;height:22px;"
    "border:2px solid rgba(60,127,106,.2);border-top-color:#5bd6ab;"
    "border-radius:50%;animation:r .7s linear infinite}"
  "@keyframes r{to{transform:rotate(360deg)}}"
  ".ldw{text-align:center;padding:24px 0}"
  ".pt{color:#6a7280;font-size:.8em;margin:10px 0 2px;padding-top:8px;"
    "border-top:1px solid rgba(60,127,106,.1)}"
  ".pw{position:relative}"
  ".pw input{padding-right:44px}"
  ".pw button{position:absolute;right:3px;top:3px;width:36px;height:calc(100% - 16px);"
    "background:rgba(46,80,73,.3);border:0;border-radius:8px;padding:0;margin:0;"
    "color:#506070;cursor:pointer;display:flex;align-items:center;justify-content:center;"
    "text-transform:none;letter-spacing:0;font-size:.8em}"
  ".pw button:hover{color:#5bd6ab;background:rgba(46,80,73,.5)}"
  ".pw svg{width:16px;height:16px;fill:none;stroke:currentColor;stroke-width:1.5;"
    "stroke-linecap:round;stroke-linejoin:round}"
  ".hn{display:flex;align-items:center;gap:8px;font-size:.8em;color:#506070;"
    "margin:0 0 12px;cursor:pointer;font-weight:400;text-transform:none;letter-spacing:0}"
  ".hn input{width:auto;margin:0;accent-color:#4db691;-webkit-appearance:auto;appearance:auto}"
  "</style>";

// ---- JavaScript for the WiFi configuration page (AJAX scan, password toggle, hidden network) ----

static const char TPL_WIFI_JS[] PROGMEM =
  "function scan(){"
    "var nl=document.getElementById('nl');"
    "nl.innerHTML='<div class=\"ldw\"><span class=\"ld\"></span></div>';"
    "var x=new XMLHttpRequest;"
    "x.onload=function(){"
      "try{var d=JSON.parse(x.responseText);var h='';"
      "for(var i=0;i<d.n.length;i++){var n=d.n[i];"
        "var sl=n.r<26?'s1':n.r<51?'s2':n.r<76?'s3':'s4';"
        "h+='<div class=\"n\" onclick=\"sel(this)\"><span>'+esc(n.s)+'</span>'"
        "+'<span class=\"q\"><span class=\"sig '+sl+'\"><i></i><i></i><i></i><i></i></span>'"
        "+(n.e?'<span class=\"lk\"></span>':'')+'</span></div>';}"
      "nl.innerHTML=h||'<div class=\"msg\">'+T.nn+'</div>';"
      "}catch(e){nl.innerHTML='<div class=\"msg\">'+T.nn+'</div>';}};"
    "x.onerror=function(){nl.innerHTML='<div class=\"msg\">'+T.nn+'</div>';};"
    "x.open('GET','/scan');x.send();}"
  "function esc(s){var d=document.createElement('div');"
    "d.appendChild(document.createTextNode(s));return d.innerHTML;}"
  "function sel(el){"
    "var s=el.querySelector('span').textContent;"
    "document.getElementById('s').value=s;"
    "document.getElementById('hn').checked=false;"
    "document.getElementById('p').focus();}"
  "function togglePw(){"
    "var p=document.getElementById('p');"
    "p.type=p.type==='password'?'text':'password';}"
  "function toggleHn(){"
    "var c=document.getElementById('hn').checked;"
    "var s=document.getElementById('s');"
    "if(c){s.value='';s.focus();}}"
  "window.addEventListener('load',scan);";

// ---- WiFiConnectParam implementation ----

WiFiConnectParam::WiFiConnectParam(const char *custom) {
  _id = NULL;
  _placeholder = NULL;
  _length = 0;
  _value = NULL;
  _customHTML = custom;
}

WiFiConnectParam::WiFiConnectParam(const char *id, const char *placeholder, const char *defaultValue, int length) {
  init(id, placeholder, defaultValue, length, "");
}

void WiFiConnectParam::init(const char *id, const char *placeholder, const char *defaultValue, int length, const char *custom) {
  _id = id;
  _placeholder = placeholder;
  _length = length;
  _value = NULL;
  _customHTML = custom;
  setValue(defaultValue);
}

WiFiConnectParam::~WiFiConnectParam() {
  delete[] _value;
}

void WiFiConnectParam::setValue(const char *newValue) {
  if (_length > 0) {
    delete[] _value;
    _value = new char[_length + 1];
    memset(_value, 0, _length + 1);
    if (newValue != NULL) {
      strncpy(_value, newValue, _length);
    }
  }
}

const char* WiFiConnectParam::getValue() {
  return _value;
}

const char* WiFiConnectParam::getID() {
  return _id;
}

const char* WiFiConnectParam::getPlaceholder() {
  return _placeholder;
}

int WiFiConnectParam::getValueLength() {
  return _length;
}

const char* WiFiConnectParam::getCustomHTML() {
  return _customHTML;
}

// ---- WiFiConnect implementation ----

WiFiConnect::WiFiConnect() {
  _apName[0] = '\0';
}

void WiFiConnect::setAPName() {
  String ssid = "TEF_" + String(ESP_getChipId());
  strcpy(_apName, ssid.c_str());
}

void WiFiConnect::addParameter(WiFiConnectParam *p) {
  if (_paramsCount < WiFiConnect_MAX_PARAMS) {
    _params[_paramsCount] = p;
    _paramsCount++;
  }
}

boolean WiFiConnect::autoConnect() {
  return autoConnect(NULL, NULL, WIFI_STA);
}

boolean WiFiConnect::autoConnect(char const *ssidName, char const *ssidPassword, WiFiMode_t acWiFiMode) {
  WiFi.mode(acWiFiMode);

  if (WiFi.status() == WL_CONNECTED) {
    return true;
  }

  int c = 0;
  while (c < RETRY_ATTEMPTS) {
    long ms = millis();

    if (ssidName == NULL || strlen(ssidName) == 0) {
      wifi_config_t conf;
      esp_wifi_get_config(WIFI_IF_STA, &conf);
      String stored_ssid = String(reinterpret_cast<const char*>(conf.sta.ssid));
      if (stored_ssid == "") {
        return false;
      }
      WiFi.begin();
    } else {
      WiFi.begin(ssidName, ssidPassword);
    }

    while (millis() - (unsigned long)ms < ((unsigned int)CONNECTION_TIMEOUT_SECS * 1000)) {
      int ws = WiFi.status();
      if (ws == WL_CONNECTED) {
        delay(500);
        return true;
      } else if (ws == WL_CONNECT_FAILED) {
        delay(500);
      } else {
        delay(200);
        yield();
      }
    }
    c++;
  }
  return false;
}

boolean WiFiConnect::startConfigurationPortal() {
  delay(50);

  if (WiFi.status() != WL_CONNECTED) {
    WiFi.mode(WIFI_AP);
  } else {
    WiFi.mode(WIFI_AP_STA);
  }

  dnsServer.reset(new DNSServer());
  server.reset(new WebServer(80));

  setAPName();
  WiFi.softAP(_apName);

  delay(500);

  /* Setup the DNS server redirecting all domains to the AP IP */
  dnsServer->setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer->start(DNS_PORT, "*", WiFi.softAPIP());

  /* Setup web pages: root, wifi config, scan API, logo, and not found */
  server->on("/",        std::bind(&WiFiConnect::handleRoot, this));
  server->on("/wifi",    std::bind(&WiFiConnect::handleWifi, this));
  server->on("/scan",    std::bind(&WiFiConnect::handleScan, this));
  server->on("/wifisave", std::bind(&WiFiConnect::handleWifiSave, this));
  server->on("/logo.png", std::bind(&WiFiConnect::handleLogo, this));

  /* Captive portal detection endpoints — redirect to root to trigger popup */
  server->on("/fwlink",              std::bind(&WiFiConnect::handleRoot, this));  // Windows
  server->on("/redirect",            std::bind(&WiFiConnect::handleRoot, this));  // Windows 10+
  server->on("/hotspot-detect.html", std::bind(&WiFiConnect::handleRoot, this));  // Apple iOS/macOS
  server->on("/library/test/success.html", std::bind(&WiFiConnect::handleRoot, this));  // Apple legacy
  server->on("/generate_204",        std::bind(&WiFiConnect::handleRoot, this));  // Android
  server->on("/gen_204",             std::bind(&WiFiConnect::handleRoot, this));  // Android alt
  server->on("/connecttest.txt",     std::bind(&WiFiConnect::handleRoot, this));  // Windows 11
  server->on("/ncsi.txt",            std::bind(&WiFiConnect::handleRoot, this));  // Windows NCSI

  server->onNotFound(std::bind(&WiFiConnect::handleNotFound, this));

  server->begin();

  _readyToConnect = false;
  while (true) {
    dnsServer->processNextRequest();
    server->handleClient();

    if (_readyToConnect) {
      _readyToConnect = false;

      if (autoConnect(_ssid.c_str(), _password.c_str(), WIFI_AP_STA)) {
        WiFi.mode(WIFI_STA);
        delay(500);
        break;
      }
    }
    yield();
  }

  server->close();
  server.reset();
  dnsServer.reset();

  return (WiFi.status() == WL_CONNECTED);
}

// ---- Page handlers ----

void WiFiConnect::handleRoot() {
  if (captivePortal()) return;

  String page = F("<!DOCTYPE html><html lang='en'><head>"
    "<meta charset='utf-8'>"
    "<meta name='viewport' content='width=device-width,initial-scale=1,user-scalable=no'>"
    "<title>");
  page += textUI(315);
  page += F("</title>");
  page += FPSTR(TPL_STYLE);
  page += F("</head><body><div class='w'>"
    "<img class='logo' src='/logo.png' alt='FMDX'><h1>");
  page += _apName;
  page += F("</h1><div class='msg'>");
  page += textUI(301);
  page += F("</div><form action='/wifi' method='get'><button>");
  page += textUI(302);
  page += F("</button></form></div></body></html>");

  server->sendHeader("Content-Length", String(page.length()));
  server->send(200, "text/html", page);
}

void WiFiConnect::handleWifi() {
  String page = F("<!DOCTYPE html><html lang='en'><head>"
    "<meta charset='utf-8'>"
    "<meta name='viewport' content='width=device-width,initial-scale=1,user-scalable=no'>"
    "<title>");
  page += textUI(316);
  page += F("</title>");
  page += FPSTR(TPL_STYLE);
  page += F("</head><body><div class='w'>"
    "<img class='logo' src='/logo.png' alt='FMDX'><h1>");
  page += _apName;
  page += F("</h1>");

  // ---- Networks card ----
  page += F("<div class='cd'><h2>");
  page += textUI(302);
  page += F("</h2><div id='nl'><div class='ldw'><span class='ld'></span></div></div>"
    "<button class='alt' onclick='scan()'>");
  page += textUI(309);
  page += F("</button></div>");

  // ---- Connection form card ----
  page += F("<div class='cd'><h2>");
  page += textUI(308);
  page += F("</h2><form method='post' action='wifisave'>");

  // Hidden network toggle
  page += F("<label class='hn'><input type='checkbox' id='hn' onchange='toggleHn()'> ");
  page += textUI(303);
  page += F("</label>");

  // SSID field
  page += F("<label>");
  page += textUI(304);
  page += F("</label><input type='text' id='s' name='s' maxlength='32' placeholder='");
  page += textUI(305);
  page += F("'>");

  // Password field with SVG eye toggle
  page += F("<label>");
  page += textUI(306);
  page += F("</label><div class='pw'><input type='password' id='p' name='p' maxlength='64' placeholder='");
  page += textUI(307);
  page += F("'><button type='button' onclick='togglePw()'>"
    "<svg viewBox='0 0 24 24'><path d='M1 12s4-8 11-8 11 8 11 8-4 8-11 8-11-8-11-8z'/>"
    "<circle cx='12' cy='12' r='3'/></svg></button></div>");

  // Custom parameters
  for (int i = 0; i < _paramsCount; i++) {
    if (_params[i] == NULL) break;

    if (_params[i]->getID() != NULL) {
      char parLength[4];
      snprintf(parLength, 4, "%d", _params[i]->getValueLength());
      page += F("<input type='text' id='");
      page += _params[i]->getID();
      page += F("' name='");
      page += _params[i]->getID();
      page += F("' maxlength=");
      page += parLength;
      page += F(" placeholder='");
      page += _params[i]->getPlaceholder();
      page += F("' value='");
      page += _params[i]->getValue();
      page += F("' ");
      page += _params[i]->getCustomHTML();
      page += F(">");
    } else {
      page += F("<p class='pt'>");
      page += _params[i]->getCustomHTML();
      page += F("</p>");
    }
  }

  // Submit button
  page += F("<button type='submit'>");
  page += textUI(308);
  page += F("</button></form></div>");

  // JavaScript: inject translated text, then functions
  String nnText = textUI(317);
  nnText.replace("'", "\\'");
  page += F("<script>var T={nn:'");
  page += nnText;
  page += F("'};");
  page += FPSTR(TPL_WIFI_JS);
  page += F("</script></div></body></html>");

  server->sendHeader("Content-Length", String(page.length()));
  server->send(200, "text/html", page);
}

void WiFiConnect::handleScan() {
  int n = WiFi.scanNetworks();

  String json = F("{\"n\":[");

  if (n > 0) {
    // Sort by RSSI
    int indices[n];
    for (int i = 0; i < n; i++) indices[i] = i;
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        if (WiFi.RSSI(indices[j]) > WiFi.RSSI(indices[i])) {
          std::swap(indices[i], indices[j]);
        }
      }
    }

    // Remove duplicates (must be RSSI sorted)
    for (int i = 0; i < n; i++) {
      if (indices[i] == -1) continue;
      String cssid = WiFi.SSID(indices[i]);
      for (int j = i + 1; j < n; j++) {
        if (cssid == WiFi.SSID(indices[j])) indices[j] = -1;
      }
    }

    bool first = true;
    for (int i = 0; i < n; i++) {
      if (indices[i] == -1) continue;
      int quality = getRSSIasQuality(WiFi.RSSI(indices[i]));
      if (quality < MINIMUM_QUALITY) continue;

      if (!first) json += ',';
      first = false;

      // Escape SSID for JSON
      String ssid = WiFi.SSID(indices[i]);
      ssid.replace("\\", "\\\\");
      ssid.replace("\"", "\\\"");

      json += F("{\"s\":\"");
      json += ssid;
      json += F("\",\"r\":");
      json += String(quality);
      json += F(",\"e\":");
      json += (WiFi.encryptionType(indices[i]) != WIFI_AUTH_OPEN) ? '1' : '0';
      json += '}';
    }
  }

  json += F("]}");
  server->send(200, "application/json", json);
}

void WiFiConnect::handleWifiSave() {
  _ssid = server->arg("s").c_str();
  _ssid.trim();
  _password = server->arg("p").c_str();
  _password.trim();

  // Read custom parameters from form
  for (int i = 0; i < _paramsCount; i++) {
    if (_params[i] == NULL || _params[i]->getID() == NULL) continue;
    String value = server->arg(_params[i]->getID()).c_str();
    value.toCharArray(_params[i]->_value, _params[i]->_length);
  }

  String page = F("<!DOCTYPE html><html lang='en'><head>"
    "<meta charset='utf-8'>"
    "<meta name='viewport' content='width=device-width,initial-scale=1,user-scalable=no'>"
    "<title>");
  page += textUI(318);
  page += F("</title>");
  page += FPSTR(TPL_STYLE);
  page += F("</head><body><div class='w'>"
    "<img class='logo' src='/logo.png' alt='FMDX'><h1>");
  page += _apName;
  page += F("</h1><div class='cd'>");

  // Connecting spinner
  page += F("<div id='sp' style='text-align:center;padding:20px 0'>"
    "<div class='ld'></div>"
    "<p style='margin-top:14px;color:#ddd'>");
  page += textUI(310);
  page += F(" <strong style='color:#5bd6ab'>");
  page += _ssid;
  page += F("</strong> ...</p></div>");

  // Polling script: polls /foo every 3s; if AP responds → fail, if 20 timeouts → success
  page += F("<script>"
    "var a=0,t=setInterval(function(){"
    "if(a>20){clearInterval(t);document.getElementById('sp').style.display='none';"
    "document.getElementById('ok').style.display='block';return}"
    "var x=new XMLHttpRequest;"
    "x.onload=function(){clearInterval(t);document.getElementById('sp').style.display='none';"
    "document.getElementById('fl').style.display='block'};"
    "x.ontimeout=function(){};"
    "x.open('GET','/foo');x.timeout=1e3;x.send(null);a++},3e3);"
    "</script>");

  // Success message
  page += F("<div class='ok' id='ok'>");
  page += textUI(311);
  page += F(" <strong>");
  page += _ssid;
  page += F("</strong>!<br>");
  page += textUI(312);
  page += F("</div>");

  // Failure message
  page += F("<div class='fail' id='fl'>");
  page += textUI(313);
  page += F(" <strong>");
  page += _ssid;
  page += F("</strong>.<br><a href='/'>");
  page += textUI(314);
  page += F("</a></div>");

  page += F("</div></div></body></html>");

  server->sendHeader("Content-Length", String(page.length()));
  server->send(200, "text/html", page);
  _readyToConnect = true;
}

void WiFiConnect::handleLogo() {
  server->send_P(200, "image/png", (const char*)logo_png, sizeof(logo_png));
}

void WiFiConnect::handleNotFound() {
  if (captivePortal()) {
    return;
  }

  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server->uri();
  message += "\nMethod: ";
  message += (server->method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server->args();
  message += "\n";

  for (uint8_t i = 0; i < server->args(); i++) {
    message += " " + server->argName(i) + ": " + server->arg(i) + "\n";
  }

  server->sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server->sendHeader("Pragma", "no-cache");
  server->sendHeader("Expires", "-1");
  server->sendHeader("Content-Length", String(message.length()));
  server->send(404, "text/plain", message);
}

boolean WiFiConnect::captivePortal() {
  if (!isIp(server->hostHeader())) {
    String msg = "redirect\n";
    server->sendHeader("Location", String("http://") + toStringIp(server->client().localIP()), true);
    server->sendHeader("Content-Length", String(msg.length()));
    server->send(302, "text/plain", msg);
    return true;
  }
  return false;
}

boolean WiFiConnect::isIp(String str) {
  for (unsigned int i = 0; i < str.length(); i++) {
    int c = str.charAt(i);
    if (c != '.' && (c < '0' || c > '9')) {
      return false;
    }
  }
  return true;
}

String WiFiConnect::toStringIp(IPAddress ip) {
  String res = "";
  for (int i = 0; i < 3; i++) {
    res += String((ip >> (8 * i)) & 0xFF) + ".";
  }
  res += String(((ip >> 8 * 3)) & 0xFF);
  return res;
}

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
