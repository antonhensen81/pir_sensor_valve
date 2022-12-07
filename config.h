// WIFI Settings
#define WIFI_ENABLED                           // comment this out to disable WiFi
const char* ssid       = "Your SSID here";     // WiFi SSID (network name)
const char* password   = "Your password here"; // Wifi Password
bool useStaticIp = false;                      // when set to false it will obtain an IP address via DHCP and ignore the settings below
                                               // when set to true it will use IP addresses defined below
  IPAddress local_IP(192, 168, 0, 200);
  IPAddress gateway(192, 168, 0, 1);
  IPAddress subnet(255, 255, 255, 0);
  IPAddress primaryDNS(8, 8, 8, 8);
  IPAddress secondaryDNS(8, 8, 4, 4);

// Display
#define DISPLAY_ENABLED                        // comment this out to disable display

// GPIO
int gpioPIR = 27;                              // GPIO port that the PIR sensor is attached to
int gpioPIRStatusLED = 26;                     // GPIO port of the status led that show the PIR sensor state
int gpioValve = 25;                            // GPIO port of the relais that controls the valve

// Initial settings (will be overwritten when using the web interface to change configuration. These values will not be used after doing so because the values are obtained by the data obtained using SPIFF)
int maximumValveOpenTimeInSeconds = 10;        // Keep valve opened for specified number of seconds
int disableValveAfterCloseInSeconds = 30;       // Keep valve closed for specified number of seconds
int openValveAfterInactivityInSeconds = 120;   // Open valve after specified number of seconds
