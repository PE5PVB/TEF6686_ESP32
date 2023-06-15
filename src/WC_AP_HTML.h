/*!
 * @file WC_AP_HTML.h
 *
 * HTML snippets to build the Access Point portal and the Parameters Portal.
 *
 * Written by Stuart Blair
 *
 * GNU General Public License v3.0 licence, all text here must be included in any redistribution and you should receive a copy of the license file.
 *
 */
 
#ifndef WC_AP_HTML
#define WC_AP_HTML ///< Define to stop re-inclusion
/*! \def char AP_HTTP_HEAD[] PROGMEM
Start of HTML output
 */
const char AP_HTTP_HEAD[] PROGMEM            = "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/><title>{v}</title>";
/*! \def AP_HTTP_STYLE[] PROGMEM 
Style for our access point 
*/
const char AP_HTTP_STYLE[] PROGMEM           = "<style type=\"text/css\">h1 { font-weight: normal; } .msgbox { font-size:1.2rem; line-height: 1.8em; padding: 0.5em; background-color: #ddffff; border-left: 6px solid #ccc; margin-bottom:1em; } .c{text-align:center}div,input{padding:5px;font-size:1em}input{width:95%;margin-top:5px;margin-bottom:10px}body{text-align:center;font-family:verdana;}button{border:0;border-radius:.3rem;background-color:#1fa3ec;color:#fff;line-height:2.6rem;font-size:1.2rem;width:100%}.q{float:right;width:64px;text-align:right}.l{background:url(data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAMAAABEpIrGAAAALVBMVEX///8EBwfBwsLw8PAzNjaCg4NTVVUjJiZDRUUUFxdiZGSho6OSk5Pg4eFydHTCjaf3AAAAZElEQVQ4je2NSw7AIAhEBamKn97/uMXEGBvozkWb9C2Zx4xzWykBhFAeYp9gkLyZE0zIMno9n4g19hmdY39scwqVkOXaxph0ZCXQcqxSpgQpONa59wkRDOL93eAXvimwlbPbwwVAegLS1HGfZAAAAABJRU5ErkJggg==) no-repeat left center;background-size:1em;}.cfail,.cok{text-align:center; font-size:1.2rem; line-height: 2em; margin-top: 1em; padding: 0.7em; display:none;} .cfail{color: #FFFFFF;background-color: #ff8433;} .cok{ background-color: #6aff33;}</style>";
/** Scripts for our page */
const char AP_HTTP_SCRIPT[] PROGMEM          = "<script>function c(l){document.getElementById('s').value=l.innerText||l.textContent;document.getElementById('p').focus();}</script>";
/** End of the header section and beginning of the body */
const char AP_HTTP_HEAD_END[] PROGMEM        = "</head><body><div style='text-align:left;display:inline-block;min-width:260px;'>";
/** Start of our HTMl configuration Form */
const char AP_HTTP_PORTAL_OPTIONS[] PROGMEM  = "<div class=\"msgbox\">Connect this device to a WiFi network. Select the option to find a WiFi network.</div><form action=\"/wifi\" method=\"get\"><button>Configure WiFi (Auto Scan)</button></form><br/><form action=\"/0wifi\" method=\"get\"><button style=\"background-color:#bbbbbb;\">Configure WiFi (Manual)</button></form><!--<br/><form action=\"/i\" method=\"get\"><button>Info</button></form><br/></form>-->";
/** HTML snippet for wifi scanning */
const char AP_HTTP_ITEM[] PROGMEM            = "<div><a href='#p' onclick='c(this)'>{v}</a>&nbsp;<span class='q {i}'>{r}%</span></div>";
/** HTML form for saving wifi connection details */
const char AP_HTTP_FORM_START[] PROGMEM      ="<form method=\"post\" action=\"wifisave\"><label>Enter WiFi Name ('SSID'):</label><input id=\"s\" name=\"s\" length=32 placeholder=\"Example: Home_Network_2002\"><label>Enter WiFi Password:</label><input id=\"p\" name=\"p\" length=64 type=\"password\" placeholder=\"Password123\"><br/>";;
/** HTML snippet for our custom parameters */
const char AP_HTTP_FORM_PARAM[] PROGMEM      = "<br/><input id='{i}' name='{n}' maxlength={l} placeholder='{p}' value='{v}' {c}>";
/** The end of our HTML Form */
const char AP_HTTP_FORM_END[] PROGMEM        = "<br/><button type='submit'>Save and Connect</button></form>";
/** HTML snippet to recan for networks */
const char AP_HTTP_SCAN_LINK[] PROGMEM       = "<br/><div class=\"c\"><a href=\"/wifi\">Re-scan</a></div>";
/** HTML snippet for saved confirmation */
// https://stackoverflow.com/questions/20760635/why-does-setting-xmlhttprequest-responsetype-before-calling-open-throw
// https://esprima.org/demo/validate.html
// https://javascript-minifier.com/

/* Use JavaScript to ping the ESP periodically @ the AP IP address. 
 * If it comes back as an AP again then we know the connection to the WiFi didn't work. 
 * We wait about 30 seconds to determine this outcome. This isn't 100% foolproof, but should be good enough.
*/
/*
<script type="text/javascript">
function doPing() {        
		//if ( timeout_count > 20 ) {
        if ( attempt_count > 20 ) { // wait about a minute
			window.clearInterval(myPinger), document.getElementById("conn_ok").style.display = "block"
		}
		
        var o = new XMLHttpRequest;
        o.onload = function() {
            console.log(this.responseText), document.getElementById("conn_fail").style.display = "block", window.clearInterval(myPinger)
        }, o.ontimeout = function(o) {
            console.log("Timeout Counter is: " + timeout_count++)
        }, o.open("GET", "/foo"), o.timeout = 1000, o.send(null), console.log("Ping counter is: " + attempt_count++)
    }
	
    attempt_count = 0;
    timeout_count = 0;
    var myPinger = window.setInterval(doPing, 3000);

</script>
*/
const char AP_HTTP_SAVED[] PROGMEM           = "<div>Credentials Saved.<br />Attempting to connect to  WiFi network. Please wait.... <br /><script type=\"text/javascript\">function doPing(){attempt_count>20&&(window.clearInterval(myPinger),document.getElementById(\"conn_ok\").style.display=\"block\");var t=new XMLHttpRequest;t.onload=function(){console.log(this.responseText),document.getElementById(\"conn_fail\").style.display=\"block\",window.clearInterval(myPinger)},t.ontimeout=function(t){console.log(\"Timeout Counter is: \"+timeout_count++)},t.open(\"GET\",\"/foo\"),t.timeout=1e3,t.send(null),console.log(\"Ping counter is: \"+attempt_count++)}attempt_count=0,timeout_count=0;var myPinger=window.setInterval(doPing,3e3);</script><div class=\"cok\" id=\"conn_ok\">Connected to {ap} !<br />You may now close this window. </div><div class=\"cfail\" id=\"conn_fail\">Failed to connect to {ap}!<br /><a href=\"/\">Click here</a> to try again.</div></div>";
/** End of the HTML page */
const char AP_HTTP_END[] PROGMEM             = "</div></body></html>";
/** HTML snippet for our custom parameters portal form */
const char AP_HTTP_PORTAL_PARAM_OPTIONS[] PROGMEM  = "<form action=\"/params\" method=\"get\"><button>Configure Parameters</button></form><br/><form action=\"/i\" method=\"get\"><button>Info</button></form><br/>";
/** HTML snippet for our custom parameters save */
const char AP_HTTP_FORM_PARAM_START[] PROGMEM      ="<form method=\"get\" action=\"wifisave\">";

#endif