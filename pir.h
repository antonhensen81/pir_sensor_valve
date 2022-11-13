int previousSensorState;

void initializePir(){
  pinMode(gpioPIR, INPUT);
  pinMode(gpioPIRStatusLED, OUTPUT);
}

void updateStatusLed(bool sensorState) {
  if (sensorState != previousSensorState) {
    Serial.print("Sensor state changed to: ");
    Serial.println(sensorState);
    
    digitalWrite(gpioPIRStatusLED, sensorState);
    previousSensorState = sensorState;
  }
}

bool readPir(){
  bool sensorState = digitalRead(gpioPIR);
  updateStatusLed(sensorState);
  return sensorState;
}
