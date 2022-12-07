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

#include "SPIFFS.h"

#ifdef WIFI_ENABLED
  #include <WiFi.h>
  #include <WebServer.h>
  #include "ESPAsyncWebServer.h"
  #include "AsyncJson.h"
  #include "ArduinoJson.h"
  #include "ota.h"
  #include "wifi.h"
  #include "server.h"
#endif

#ifdef DISPLAY_ENABLED
  #include "display.h"
#endif


void readSettings()
{
   // Initialize SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  // Read settings from SPIFFS

  File file = SPIFFS.open("/settings", FILE_READ);
  if (file) {
    String json = file.readString();

    Serial.print(" json: ");
    Serial.println(json);
    
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, json);
    String maximumValveOpenTimeInSecondsConfig = doc["maximumValveOpenTimeInSeconds"];
    String disableValveAfterCloseInSecConfig = doc["disableValveAfterCloseInSeconds"];
    String openValveAfterInactivityInSeConfig = doc["openValveAfterInactivityInSeconds"];


    Serial.print(" maximumValveOpenTimeInSecondsConfig : ");
    Serial.println(maximumValveOpenTimeInSecondsConfig);
    Serial.print(" disableValveAfterCloseInSecConfig : ");
    Serial.println(disableValveAfterCloseInSecConfig);
    Serial.print(" openValveAfterInactivityInSeConfig : ");
    Serial.println(openValveAfterInactivityInSeConfig);
    
    maximumValveOpenTimeInSeconds = maximumValveOpenTimeInSecondsConfig.toInt();
    disableValveAfterCloseInSeconds = disableValveAfterCloseInSecConfig.toInt();
    openValveAfterInactivityInSeconds = openValveAfterInactivityInSeConfig.toInt();

    Serial.print(" maximumValveOpenTimeInSeconds : ");
    Serial.println(maximumValveOpenTimeInSeconds);
    Serial.print(" disableValveAfterCloseInSeconds : ");
    Serial.println(disableValveAfterCloseInSeconds);
    Serial.print(" openValveAfterInactivityInSeconds : ");
    Serial.println(openValveAfterInactivityInSeconds);
    
  } else
  {
    Serial.println("No settings found using SPIFFS");
  }
  file.close();    
}

void setup(void) {
  // Serial
  Serial.begin(115200);
  readSettings();

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
