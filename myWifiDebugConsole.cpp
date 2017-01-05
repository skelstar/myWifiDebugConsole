#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <myWifiDebugConsole.h>

ESP8266WebServer _server (80);
uint8_t _refreshSeconds;

myWifiDebugConsole::myWifiDebugConsole(uint8_t refreshSeconds)
{
	_refreshSeconds = refreshSeconds;
}


// void myWifiDebugConsole::Wrapper_To_Handle_Root() {
// 	handleRoot();
// }

void myWifiDebugConsole::init() 
{
	char temp[400];
    int sec = millis() / 1000;
    int min = sec / 60;
    int hr = min / 60;

	snprintf ( temp, 400,

"<html>\
  <head>\
    <meta http-equiv='refresh' content='5'/>\
    <title>ESP8266 Debug Demo</title>\
    <style>\
      body { font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
    <h1>Hello from ESP8266!</h1>\
    <p>Timestamp: %02d:%02d:%02d</p>\
  </body>\
</html>",
		//_refreshSeconds,
        hr, 
        min % 60, 
        sec % 60
    );


    //_server.on ( "/", handleRoot );
    _server.on( "/", [&]() 
	{
		_server.send ( 200, "text/plain", "temp");
    });
    //_server.on ( "/inline", []() {
    //        _server.send ( 200, "text/plain", "this works as well" );
    //    });
    //server.onNotFound ( handleNotFound );
    _server.begin();
}

void myWifiDebugConsole::handleRoot() {
/*
    char temp[400];
    int sec = millis() / 1000;
    int min = sec / 60;
    int hr = min / 60;

    snprintf ( temp, 400,

"<html>\
  <head>\
    <meta http-equiv='refresh' content='5'/>\
    <title>ESP8266 Debug Demo</title>\
    <style>\
      body { font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
    <h1>Hello from ESP8266!</h1>\
    <p>Timestamp: %02d:%02d:%02d</p>\
    <img src=\"/test.svg\" />\
  </body>\
</html>",
		//_refreshSeconds,
        hr, 
        min % 60, 
        sec % 60
    );
    _server.send ( 200, "text/html", temp );*/
}

void myWifiDebugConsole::handleClient()
{
	_server.handleClient();
}
