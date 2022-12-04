int previousSensorState;

void initializePir(){
  pinMode(gpioPIR, INPUT);
  pinMode(gpioPIRStatusLED, OUTPUT);
}

void updateStatusLed(bool sensorState) {
  if (sensorState != previousSensorState) {
//    Serial.print("sensor:");
//    Serial.println(sensorState);
    
    digitalWrite(gpioPIRStatusLED, sensorState);
    previousSensorState = sensorState;
  }
}

void readPir() {
  sensorState = digitalRead(gpioPIR); 
  updateStatusLed(sensorState);  
}
