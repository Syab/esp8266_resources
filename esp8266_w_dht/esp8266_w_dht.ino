#include <SoftwareSerial.h>
#include "DHT.h"
#include "config.h"
#include "functions.h"

#define PUBLISH_INTERVAL 10*(1000)

void setup (void)
{
	initialize();
	Serial.println("DHTxx test!");
	dht.begin();
}

void loop (void)
{
  if(millis() - old_time > PUBLISH_INTERVAL){
		readFromDHT();
    
    double values[] = {t}; // Max 3 numbered items
    sendToIFTTT(values, sizeof(values)/sizeof(double));

    old_time = millis();
  }

  //PLACE ALL YOUR USER CODE HERE
}
