unsigned long lastStateChange = millis();

// 0 is valve idle (free to operate)
// 1 is valve opened (not free to operate)
// 2 is valve disabled (not free to operate)
int valveState = 0;

void initializeValve() {
  pinMode(gpioValve, OUTPUT);
}

void openValveIfTriggered(bool sensorState){
  if (sensorState) {
    Serial.println("Opening valve because of sensor trigger");
    digitalWrite(gpioValve, HIGH);
    valveState = 1;
    lastStateChange = millis();
  }
}

void openValveIfIdleForTooLong(){
  if (millis() - lastStateChange > openValveAfterInactivityInSeconds * 1000) {
    Serial.println("Opening valve because of long inactivity");
    digitalWrite(gpioValve, HIGH);
    valveState = 1;
    lastStateChange = millis();
  }
}

void closeValveAfterTimeOut() {
  if (millis() - lastStateChange > maximumValveOpenTimeInSeconds * 1000) {
    Serial.println("Closing valve");
    digitalWrite(gpioValve, LOW);
    valveState = 2;
    lastStateChange = millis();
  }  
}

void disableValveUntilTimeOut(){
  if (millis() - lastStateChange > disableValveAfterCloseInSeconds * 1000) {
    Serial.println("Setting idle mode");
    valveState = 0;
    lastStateChange = millis();
  }    
}

int updateValve(bool sensorState, int &timeCount){
  switch (valveState){
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
  timeCount = (millis() - lastStateChange) / 1000;
  return valveState;
}
