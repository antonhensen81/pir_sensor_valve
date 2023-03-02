unsigned long lastStateChange = millis();
bool triggeredByTimeOut = false;

void initializeValve() {
  pinMode(gpioValve, OUTPUT);
}

void openValveIfTriggered(bool sensorState){
  if (sensorState) {
    Serial.println("Opening valve because of sensor trigger");
    digitalWrite(gpioValve, HIGH);
    valveState = HIGH;
    state = 1;
    lastStateChange = millis();
  }
}

void openValveIfIdleForTooLong(){
  if (millis() - lastStateChange > openValveAfterInactivityInSeconds * 1000) {
    Serial.println("Opening valve because of long inactivity");
    digitalWrite(gpioValve, HIGH);
    state = 1;
    triggeredByTimeOut = true;
    valveState = HIGH;
    lastStateChange = millis();
  }
}

void closeValveAfterTimeOut() {
  if (millis() - lastStateChange > maximumValveOpenTimeInSeconds * 1000) {
    Serial.println("Closing valve");
    digitalWrite(gpioValve, LOW);
    valveState = LOW;
    state = 2;
    lastStateChange = millis();
  }  
}

void disableValveUntilTimeOut(){
  if (millis() - lastStateChange > disableValveAfterCloseInSeconds * 1000) {
    Serial.println("Setting idle mode");
    state = 0;
    
    if (triggeredByTimeOut && resetAfterInactivity){
      triggeredByTimeOut = false;
      Serial.println("RESET!!!");
      ESP.restart();
      esp_restart();
    }
    
    lastStateChange = millis();
  }    
}

void updateValve(){
  switch (state){
    case 0:
      openValveIfTriggered(sensorState);
      openValveIfIdleForTooLong();
      break;
    case 1:
      closeValveAfterTimeOut();
      break;
    case 2:
      disableValveUntilTimeOut();
      break;
  }
  Serial.print("state:");
  Serial.println(state); 
  
  timeCount = (millis() - lastStateChange) / 1000;
}
