// Config
#include "config.h"

// State
unsigned long currentMillis = millis();

// 0 : Idle. Valve idle (free to operate)
// 1 : Open. Valve opened (not free to operate)
// 2 : Closed. Valve disabled (not free to operate)
int state = 0;

bool sensorState = LOW;
bool valveState = LOW;
int timeCount = 0;


// Dependencies
#include "valve.h"
#include "pir.h"

#ifdef WIFI_ENABLED
  #include <WiFi.h>
  #include <WebServer.h>
  #include "ESPAsyncWebServer.h"
  #include "AsyncJson.h"
  #include "ArduinoJson.h"
  #include "SPIFFS.h"
  #include "ota.h"
  #include "wifi.h"
  #include "server.h"
#endif

#ifdef DISPLAY_ENABLED
  #include "display.h"
#endif

void setup(void) {
  // Serial
  Serial.begin(115200);

  #ifdef WIFI_ENABLED
    initializeWifi();
    initializeWebServer();
  #endif
  initializePir();
  initializeValve();
  #ifdef DISPLAY_ENABLED
    initializeDisplay();
  #endif
}
   
void updateLoop() {  
  readPir();
  updateValve();
  #ifdef DISPLAY_ENABLED
    updateDisplay(); 
  #endif
  delay(1000);
}

void loop() {
  currentMillis = millis();
  #ifdef WIFI_ENABLED 
    connectWifiWhenNeeded();
    handleOTA();
  #endif
  updateLoop();
}
