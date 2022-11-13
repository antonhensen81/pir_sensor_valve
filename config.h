const char* ssid       = "Your SSID here";     // WiFi SSID (network name)
const char* password   = "Your password here"; // Wifi Password
int gpioPIR = 27;                              // GPIO port that the PIR sensor is attached to
int gpioPIRStatusLED = 26;                     // GPIO port of the status led that show the PIR sensor state
int gpioValve = 25;                            // GPIO port of the relais that controls the valve
int maximumValveOpenTimeInSeconds = 10;        // Keep valve opened for specified number of seconds
int disableValveAfterCloseInSeconds = 30;      // Keep valve closed for specified number of seconds
int openValveAfterInactivityInSeconds = 120;   // Open valve after specified number of seconds
