#include <TFT_eSPI.h> 
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

// state to decide if we should render on the display
bool shouldUpdateDisplay = true;
bool lastConnectionStatus = true;
int previousValveState = 0;
int stateSensorPrevious = 0;
int previousTimeCount = 0;

void initializeDisplay() {
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
}

#ifdef WIFI_ENABLED
String getIpAddressString() {
  if (WiFi.status() != WL_CONNECTED) {
    //Serial.print(".");
    if (lastConnectionStatus == true){
      lastConnectionStatus = false;
      shouldUpdateDisplay = true;
    }
    return "Connecting";
  }
  else {    
    if (lastConnectionStatus == false){
      lastConnectionStatus = true;
      shouldUpdateDisplay = true;
    }
    return WiFi.localIP().toString();
  }  
}
#endif

void updateDisplay() {  
  if (previousValveState != valveState ){
    shouldUpdateDisplay = true;
  }

  if (stateSensorPrevious != sensorState){
    shouldUpdateDisplay = true;
  }

  if (previousTimeCount != timeCount){
    shouldUpdateDisplay = true;
  }
  
  if (shouldUpdateDisplay){
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(1);

    #ifdef WIFI_ENABLED
      String ipAddress = getIpAddressString();    
      tft.setTextDatum(MC_DATUM); // middle center
      tft.drawString(ipAddress, 120, 35, 4);
    #endif

    tft.setTextDatum(ML_DATUM ); // middle left    
    tft.drawString("valve:",10, 65,4);
    switch (valveState)
    {
      case 0:
        tft.drawString("idle", 100, 65, 4);
        break;      
      case 1:
        tft.drawString("opened", 100, 65, 4);
        break;      
      case 2:
        tft.drawString("closed", 100, 65, 4);
        break;      
    }

    tft.drawString("sensor:",10, 85,4);
    if (sensorState){
      tft.drawString("trigger", 100, 85, 4);
    }
    else {
      tft.drawString("idle", 100, 85, 4);
    }

    tft.drawString("time:",10, 105,4);
    tft.drawNumber(timeCount, 100, 105,4);
    
    previousValveState = valveState;
    stateSensorPrevious = sensorState;
    previousTimeCount = timeCount;
    
    shouldUpdateDisplay = false;    
  }   
}
