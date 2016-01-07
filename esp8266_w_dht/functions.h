//--------DO NOT EDIT--------------------//

#include <Arduino.h>
#define DEBUG 1

#define LED 13
String WEB_DOMN = "maker.ifttt.com";
String WEB_PORT = "80";
unsigned long old_time = 0;


SoftwareSerial mySerial(6, 7); // RX, TX

void initialize(void){
		// Set LED as an output pin
		pinMode (LED, OUTPUT) ;

		// Ensure the LED is off
		digitalWrite (LED, LOW) ;

		// Prepare mySerial Port
    if(DEBUG) Serial.begin(9600);
    if(DEBUG) Serial.println("Starting");

    mySerial.begin(9600) ;

		// Wait 6 seconds for things to stabilise
		delay (6000) ;
		if(DEBUG) Serial.println("Contacting ESP8266");

		// Attempt to contact the ESP8266
		// Do not continue if there is no response - just flash the LED once briefly and wait again
		mySerial.println ("AT") ;
		while (1)
		{
			if (mySerial.find("OK\r\n")) break ;
			else
			{
    
        
        if(DEBUG) Serial.println("unable to connect to ESP8266");
				digitalWrite (LED, HIGH) ;
				delay        (100)       ;
				digitalWrite (LED, LOW)  ;
			}
		}

			// Turn of local AT command echo
		  // Do not continue if there is no response - just flash the LED twice briefly and wait again
		  mySerial.println ("ATE0") ;
      if(DEBUG) Serial.println("Turning off echo");
		  while (1)
		  {
		    if (mySerial.find("OK\r\n")) break ;
		    else
		    {
          if(DEBUG) Serial.println("unable to turn off AT command echo");
		      digitalWrite (LED, HIGH) ;
		      delay        (100)       ;
		      digitalWrite (LED, LOW)  ;
		      delay        (100)       ;
		      digitalWrite (LED, HIGH) ;
		      delay        (100)       ;
		      digitalWrite (LED, LOW)  ;
		    }
		  }

		  // Set ESP8266 to Client Mode
		  // Do not continue if there is no response - just flash the LED thrice briefly and wait again
		  mySerial.println ("AT+CWMODE_DEF=1") ;
      if(DEBUG) Serial.println("Setting client mode");
		  while (1)
		  {
		    if (mySerial.find("OK\r\n")) break ;
		    else
		    {
          if(DEBUG) Serial.println("unable to set to client mode");
		      digitalWrite (LED, HIGH) ;
		      delay        (100)       ;
		      digitalWrite (LED, LOW)  ;
		      delay        (100)       ;
		      digitalWrite (LED, HIGH) ;
		      delay        (100)       ;
		      digitalWrite (LED, LOW)  ;
		      delay        (100)       ;
		      digitalWrite (LED, HIGH) ;
		      delay        (100)       ;
		      digitalWrite (LED, LOW)  ;
		    }
		  }

		  // Connect to specified Wi-Fi network
		  // Do not continue if there is no response - just flash the LED four times briefly and wait again
		  mySerial.println ("AT+CWJAP=\"" + WIFI_SSID + "\",\"" + WIFI_PASS + '"') ;
		  while (1)
		  {
		    if (mySerial.find("OK\r\n")) break ;
		    else
		    {
          if(DEBUG) Serial.println("unable to connect to Wi-Fi network");
		      digitalWrite (LED, HIGH) ;
		      delay        (100)       ;
		      digitalWrite (LED, LOW)  ;
		      delay        (100)       ;
		      digitalWrite (LED, HIGH) ;
		      delay        (100)       ;
		      digitalWrite (LED, LOW)  ;
		      delay        (100)       ;
		      digitalWrite (LED, HIGH) ;
		      delay        (100)       ;
		      digitalWrite (LED, LOW)  ;
		      delay        (100)       ;
		      digitalWrite (LED, HIGH) ;
		      delay        (100)       ;
		      digitalWrite (LED, LOW)  ;
		    }
		  }
}

void sendToIFTTT(double *values, int valuesLength){

  String data = "{";
  for(int i = 0; i < valuesLength; i++) {
     //if(!values[i]) continue;
     data += "\"value" + String(i+1) + "\":\"" + String(values[i]) +  "\"";
     if(i < valuesLength-1)
      data += ",";
  }
  data += "}";
 // String data = "{\"value1\":\"25.4\",\"value2\":\"85.6\"}";

  //Serial.println("Data: " + data + "\nValue:" + String(valuesLength));
  String request1 = "POST /trigger/" + IFTTT_EVENT_NAME + "/with/key/" + IFTTT_CHANNEL_KEY + " HTTP/1.1\r\n" ;
  String request2 = "Host: maker.ifttt.com\r\n" \
                      "User-Agent: ESP8266\r\n"   \
                      "Accept: */*\r\n"           ;
  String request3 = String("Content-Length: ") + data.length() + "\r\n" ;
  String request4 = "Content-Type: application/json\r\n" \
                    "Connection: close\r\n\r\n"          ;
  String request5 = data + "\r\n\r\n";

	// Open a TCP connection to a specified web domain / port
	mySerial.println ("AT+CIPSTART=\"TCP\",\"" + WEB_DOMN + "\"," + WEB_PORT) ;
 if(DEBUG) Serial.println("Opening tcp port");
	while (1)
	{
		if (mySerial.find("CONNECT\r\n\r\nOK\r\n")) break ;
	}
  if(DEBUG) Serial.println("Sent!");
	delay(100);

	mySerial.print   ("AT+CIPSEND=") ;
	mySerial.println (request1.length() + request2.length() + request3.length() + request4.length() + request5.length()) ;

	while (1)
	{
		if (mySerial.find("> ")) break;
	}

	mySerial.print (request1);
	mySerial.print (request2);
	mySerial.print (request3);
	mySerial.print (request4);
	mySerial.print (request5);
  if(DEBUG) Serial.println("Data Sent");
}



void readFromDHT(void){
  h = dht.readHumidity();
  t = dht.readTemperature();  // Read temperature as Celsius (the default)

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
}
