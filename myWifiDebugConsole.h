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
		char* messages[20];

	private:
		static int* ref;
		static void handleRoot();
		void testMemberFunction();
};

#endif
