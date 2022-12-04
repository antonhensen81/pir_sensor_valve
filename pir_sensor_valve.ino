// Config
#include "config.h"

// State
unsigned long currentMillis = millis();

// 0 is valve idle (free to operate)
// 1 is valve opened (not free to operate)
// 2 is valve disabled (not free to operate)
int state = 0;

bool sensorState = LOW;
bool valveState = LOW;
int timeCount = 0;


// Dependencies
#include "valve.h"
#include "pir.h"

#ifdef WIFI_ENABLED
  #include <WiFi.h>
  #include "ota.h"
  #include "wifi.h"
  #include <WebServer.h>
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
  updateValve(sensorState, timeCount);
  #ifdef DISPLAY_ENABLED
    updateDisplay(); 
  #endif
  #ifdef WIFI_ENABLED
    serveWebServerClient();
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
