#include <Arduino.h>

//--------Settings that you need to change--------------------//
String WIFI_SSID = "xxxtypeSSIDxxx";
String WIFI_PASS = "xxxxtypePASSWORDxxx";

String IFTTT_EVENT_NAME = "dht";
String IFTTT_CHANNEL_KEY = "xxtypeKEYxx";


//----Everything needed for DHT 11-----//
#define DHTPIN 4        // what pin we're connected to

#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);
float h = 0;
// Read temperature as Celsius (the default)
float t = 0;
//----Everything needed for DHT 11-----//
