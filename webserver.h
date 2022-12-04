#ifdef WIFI_ENABLED

WebServer server(80);

String SendHTML(){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>Valve Control</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #3498db;}\n";
  ptr +=".button-on:active {background-color: #2980b9;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>Valve Controller</h1>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found\r\n");
}

void handle_state () {
  String ptr = "{\n";
  ptr += "  \"state\": ";
  ptr += state;
  ptr += "\n,  \"sensorState\": ";
  ptr += sensorState;
  ptr += "\n,  \"valveState\": ";
  ptr += valveState;
  ptr += "\n}\n"; 
  server.send(200, "text/html", ptr); 
}

void handle_OnConnect() {
  server.send(200, "text/html", SendHTML()); 
  server.onNotFound(handle_NotFound);
}

void initializeWebServer() {
  server.on("/", handle_OnConnect);  
  server.on("/state", handle_state);  
  server.begin();
}


void serveWebServerClient() {
  server.handleClient();
}  

#endif
