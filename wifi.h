unsigned long previousConnectAttemptMillis = millis();
unsigned long previousTemperatureCheckMillis = millis();
unsigned long reconnectInterval = 8000;

bool connectedState = false;
bool connectedOldState = false;

void initializeWifi() {
  Serial.print("Connecting to");
  Serial.println(ssid);

  if (useStaticIp) {
    // Configures static IP address
    if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
      Serial.println("STA Failed to configure");
    }    
  }
  
  WiFi.mode(WIFI_STA); // station mode: the ESP32 connects to an access point
  WiFi.begin(ssid, password);
}

void connectWifiWhenNeeded() {
  if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousConnectAttemptMillis >= reconnectInterval)) {
    //Serial.print(millis());
    //Serial.println("Reconnecting to WiFi...");
    connectedState= false;
    WiFi.disconnect();
    WiFi.reconnect();
    previousConnectAttemptMillis = currentMillis;
  } else
  {
    connectedState = true;
  }
  if (connectedState != connectedOldState)
  {
    Serial.print("Connection state changed to ");
    Serial.println(connectedState);
    if (connectedState){
      Serial.println(WiFi.localIP());
    }
    connectedOldState = connectedState;
  }
}
