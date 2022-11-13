unsigned long previousConnectAttemptMillis = millis();
unsigned long previousTemperatureCheckMillis = millis();
unsigned long reconnectInterval = 8000;

void initializeWifi() {
  Serial.printf("Connecting to %s ", ssid);  
  WiFi.mode(WIFI_STA); // station mode: the ESP32 connects to an access point
  WiFi.begin(ssid, password);
}

void connectWifiWhenNeeded() {
  if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousConnectAttemptMillis >= reconnectInterval)) {
    Serial.print(millis());
    Serial.println("Reconnecting to WiFi...");
    WiFi.disconnect();
    WiFi.reconnect();
    previousConnectAttemptMillis = currentMillis;
  }  
}
