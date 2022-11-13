#include <WiFi.h>
unsigned long currentMillis = millis();

// Config
#include "config.h"

// Dependencies
#include "display.h"
#include "ota.h"
#include "valve.h"
#include "pir.h"
#include "wifi.h"

int timeCount = 0;

void setup(void) {
  // Serial
  Serial.begin(115200);

  initializeWifi();
  initializePir();
  initializeValve();
  initializeDisplay();
}
   
void updateLoop() {  
  bool sensorState = readPir();
  int valveState = updateValve(sensorState, timeCount);
  updateDisplay(valveState, sensorState, timeCount); 
  
  delay(100);
}

void loop() {
  currentMillis = millis();
  connectWifiWhenNeeded();
  handleOTA();
  updateLoop();
}
