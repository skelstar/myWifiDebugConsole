#ifndef myWifiDebugConsole_h
#define myWifiDebugConsole_h

#include <Arduino.h>
#include <ESP8266WebServer.h>

class myWifiDebugConsole
{
	public:
		myWifiDebugConsole();
		void init();
		void handleClient();

	private:
		static void handleRoot();
};

#endif
