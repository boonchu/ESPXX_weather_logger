const char* ssid     = "INSERT SSID Wifi";
const char* password = "INSERT Wifi password";

const char* host = "api.thingspeak.com";

// my channel (public mode)
// https://thingspeak.com/channels/409552
const char* THINGSPEAK_API_KEY = "Register THINGSPEAK and get read API key";

// DHT Settings
#define DHTPIN D6     // what digital pin we're connected to. If you are not using NodeMCU change D6 to real pin


// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

const boolean IS_METRIC = true;

// Update every 60 seconds = 1 minutes. Min with Thingspeak is ~20 seconds
const int UPDATE_INTERVAL_SECONDS = 50;
