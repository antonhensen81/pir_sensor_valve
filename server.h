#ifdef WIFI_ENABLED

AsyncWebServer server (80);
String rootPage = "";

int getParameter(AsyncWebServerRequest *request, String name){
  int result = -1;
  String message;
  if (request->hasParam(name, true)) {
    message = request->getParam(name, true)->value();
    result = message.toInt();
  } 
  return result;
}

void initializeWebServer() {  
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false);
  });
  server.on("/live", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/live.html", String(), false);
  });
  server.on("/state", HTTP_GET, [](AsyncWebServerRequest *request) {
      AsyncResponseStream *response = request->beginResponseStream("application/json");
      DynamicJsonDocument json(1024);
      json["state"] = state;
      json["sensorState"] = sensorState;
      json["valveState"] = valveState;
      serializeJson(json, *response);
      request->send(response);
  });  
  server.on("/settings", HTTP_GET, [](AsyncWebServerRequest *request) {
      AsyncResponseStream *response = request->beginResponseStream("application/json");
      DynamicJsonDocument json(1024);
      json["maximumValveOpenTimeInSeconds"] = maximumValveOpenTimeInSeconds;
      json["disableValveAfterCloseInSeconds"] = disableValveAfterCloseInSeconds;
      json["openValveAfterInactivityInSeconds"] = openValveAfterInactivityInSeconds;
      serializeJson(json, *response);
      request->send(response);
  });

  server.on("/updateSettings", HTTP_POST, [](AsyncWebServerRequest *request) {
    maximumValveOpenTimeInSeconds = getParameter(request, "maximumValveOpenTimeInSeconds");
    disableValveAfterCloseInSeconds = getParameter(request, "disableValveAfterCloseInSeconds");
    openValveAfterInactivityInSeconds = getParameter(request, "openValveAfterInactivityInSeconds");

    char json_string[1024];
    DynamicJsonDocument json(1024);
    json["maximumValveOpenTimeInSeconds"] = maximumValveOpenTimeInSeconds;
    json["disableValveAfterCloseInSeconds"] = disableValveAfterCloseInSeconds;
    json["openValveAfterInactivityInSeconds"] = openValveAfterInactivityInSeconds;
    serializeJson(json, json_string);
    
    File file = SPIFFS.open("/settings", FILE_WRITE);

    Serial.print("JSON:");
    Serial.println(json_string);
    
    if(file.println(json_string)) {
      request->redirect("/");
    }else {
      request->send(404, "text/plain", "Failed to update settings");
    }
//    ESP.restart();
  });
  server.onNotFound([](AsyncWebServerRequest *request){
    request->send(404, "text/plain", "The content you are looking for was not found.");
  });
 
  server.begin();
}

#endif
