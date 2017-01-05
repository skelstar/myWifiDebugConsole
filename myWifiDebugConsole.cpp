#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <myWifiDebugConsole.h>

static ESP8266WebServer _server(80);

myWifiDebugConsole::myWifiDebugConsole()
{
}

void myWifiDebugConsole::init() 
{
    _server.on("/", handleRoot);
    _server.begin();
}

void myWifiDebugConsole::handleRoot() 
{
    char temp[600];
    int sec = millis() / 1000;
    int min = sec / 60;
    int hr = min / 60;

    snprintf(temp, 600,
"<html>\
  <head>\
    <meta http-equiv='refresh' content='1'/>\
    <title>ESP8266 Debug Demo</title>\
  </head>\
  <body>\
    <h1>Hello from ESP8266!</h1>\
    <p>Timestamp: %02d:%02d:%02d</p>\
  </body>\
</html>",
        hr, 
        min % 60, 
        sec % 60
    );
	_server.send(200, "text/html", temp);
}

void myWifiDebugConsole::handleClient()
{
	_server.handleClient();
}
