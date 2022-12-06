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
   // Initialize SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
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
    request->redirect("/");
  });
  server.onNotFound([](AsyncWebServerRequest *request){
    request->send(404, "text/plain", "The content you are looking for was not found.");
  });
 
  server.begin();
}

#endif
