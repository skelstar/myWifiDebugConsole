#ifndef myWifiDebugConsole_h
#define myWifiDebugConsole_h

#include <Arduino.h>
#include <ESP8266WebServer.h>

class myWifiDebugConsole
{
	public:
		myWifiDebugConsole(uint8_t refreshSeconds);
		void handleClient();
		void init();

	private:
		ESP8266WebServer _server;
		//void Wrapper_To_Handle_Root();
		static void handleRoot();
		uint8_t _refreshSeconds;
};

#endif
