#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <myWifiDebugConsole.h>

static ESP8266WebServer _server(80);

char* messages[20];

myWifiDebugConsole::myWifiDebugConsole()
{
}

void myWifiDebugConsole::init() 
{
    _server.on("/", handleRoot(5));
    _server.begin();
}

void myWifiDebugConsole::handleRoot(int test) 
{
    char temp[600];
    int sec = millis() / 1000;
    int min = sec / 60;
    int hr = min / 60;

    strcat(temp, "<html>");
  	strcat(temp, "<head>");
    strcat(temp, "<meta http-equiv='refresh' content='1'/>");
    strcat(temp, "<title>ESP8266 Debug Demo</title>");
  	strcat(temp, "</head>");
  	strcat(temp, "<body>");
    strcat(temp, "<h1>Hello from ESP8266!</h1>");
    for (int i=0; i<20; i++) {
    	strcat(temp, messages[i]);
    }
  	strcat(temp, "</body>");
	strcat(temp, "</html>");
	puts(temp);

//     snprintf(temp, 600,
// "<html>\
//   <head>\
//     <meta http-equiv='refresh' content='1'/>\
//     <title>ESP8266 Debug Demo</title>\
//   </head>\
//   <body>\
//     <h1>Hello from ESP8266!</h1>\
//     <p>
//     <p>Timestamp: %02d:%02d:%02d</p>\
//   </body>\
// </html>",
//         hr, 
//         min % 60, 
//         sec % 60
//     );
	_server.send(200, "text/html", temp);
}

void myWifiDebugConsole::handleClient()
{
	_server.handleClient();
}
