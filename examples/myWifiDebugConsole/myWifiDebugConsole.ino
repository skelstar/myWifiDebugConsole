#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <EventManager.h>
#include <myPushButton.h>
#include <myWifiDebugConsole.h>


const char* ssid = "LeilaNet2";
const char* password = "ec1122%f*&";

void listener_Button(int eventCode, int eventParam);

myPushButton button(5, true, 2000, 1, listener_Button);

#define DEBUG_BUFFER_SIZE   20
char* debugMessage[DEBUG_BUFFER_SIZE];
int debugMsgIndex = 0;

myWifiDebugConsole console;

void listener_Button(int eventCode, int eventParam) {
    
    switch (eventParam) {
        
        case button.EV_BUTTON_PRESSED:     
            Serial.println("EV_BUTTON_PRESSED");
            addDebugMessage("EV_BUTTON_PRESSED");
            break;          
        
        case button.EV_HELD_FOR_LONG_ENOUGH:
            Serial.println("EV_HELD_FOR_LONG_ENOUGH");
            addDebugMessage("EV_HELD_FOR_LONG_ENOUGH");
            break;
        
        case button.EV_RELEASED:
            Serial.println("EV_RELEASED");
            addDebugMessage("EV_RELEASED");
            break;
    }
}

void addDebugMessage(char* message) {
    
    if (debugMsgIndex == DEBUG_BUFFER_SIZE)
        return;

    debugMessage[debugMsgIndex++] = message;
}

void setup() {

    Serial.begin(9600);
    delay(200);
    Serial.println("Booting");

    setupOTA("DebugConsoleTest");

    Serial.println(WiFi.localIP());

    console.init();

    Serial.println("HTTP server started");
}

void loop() {

	button.serviceEvents();

    ArduinoOTA.handle();

    console.handleClient();
}


void setupOTA(char* host) {
    
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("Connection Failed! Rebooting...");
        delay(5000);
        ESP.restart();
    }
    
    ArduinoOTA.setHostname(host);
    ArduinoOTA.onStart([]() {
        Serial.println("OTA Start");
    });
    ArduinoOTA.onEnd([]() {
        Serial.println("\nOTA End");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });
    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
        else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

    ArduinoOTA.begin();
}
