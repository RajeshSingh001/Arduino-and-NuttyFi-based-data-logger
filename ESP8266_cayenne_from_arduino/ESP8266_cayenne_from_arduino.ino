// This example shows how to connect to Cayenne using an ESP8266 and send/receive sample data.
// Make sure you install the ESP8266 Board Package via the Arduino IDE Board Manager and select the correct ESP8266 board before compiling. 

//#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(D7,D8,false,256);
// WiFi network info.
char ssid[] = "ESPServer_RAJ";
char wifiPassword[] = "RAJ@12345";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "fac81bb0-7283-11e7-85a3-9540e9f7b5aa";
char password[] = "3745eb389f4e035711428158f7cdc1adc0475946";
char clientID[] = "386b86f0-7284-11e7-b0bc-87cd67a1f8c7";

int TEMP,HUM,PRESS,ALT;
void setup()
{
  pinMode(D0, OUTPUT);
	Serial.begin(9600);
	Cayenne.begin(username, password, clientID, ssid, wifiPassword);
}

void loop()
{
	Cayenne.loop();
  SerialDATA(); 
  Cayenne.virtualWrite(0, TEMP);
  Cayenne.virtualWrite(1, HUM);
  Cayenne.virtualWrite(2, PRESS);
  Cayenne.virtualWrite(3, ALT);
  delay(500);
}

//Default function for processing actuator commands from the Cayenne Dashboard.
//You can also use functions for specific channels, e.g CAYENNE_IN(1) for channel 1 commands.
CAYENNE_IN_DEFAULT()
{
	//CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());
  CAYENNE_LOG("CAYENNE_IN_(1)(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());
  //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");

   int i = getValue.asInt();
   if(i>=45)
   {
   digitalWrite(D0,HIGH);
   }
   else
   {
   digitalWrite(D0,LOW); 
   }
  
}
   

void SerialDATA()
{
if (mySerial.available()<1)  return;
 char STRING_SERIAL=mySerial.read();
  if(STRING_SERIAL!='\r')                 return;
  TEMP =mySerial.parseInt();
  HUM=mySerial.parseInt();
  PRESS=mySerial.parseInt();
  ALT=mySerial.parseInt();
} 


/*
#define CAYENNE_DEBUG         // Uncomment to show debug messages
#define CAYENNE_PRINT Serial  // Comment this out to disable prints and save space

#include "CayenneDefines.h"
#include "BlynkSimpleEsp8266.h"
#include "CayenneWiFiClient.h"

// Cayenne authentication token. This should be obtained from the Cayenne Dashboard.
char token[] = "<your_token>";
// Your network name and password.
char ssid[] = "<your_ssid>";
char password[] = "<your_pwd>";

void setup()
{
  // initialize digital pin 2 as an output.
  pinMode(2, OUTPUT);
  Serial.begin(9600);
  Cayenne.begin(token, ssid, password);
}

void loop()
{
  Cayenne.run();
}

// This function will be called every time a Dashboard widget writes a value to Virtual Pin 2.
CAYENNE_IN(V2)
{
  CAYENNE_LOG("Got a value: %s", getValue.asStr());
  int i = getValue.asInt();
 
  if (i == 0)
  {
    digitalWrite(2, LOW);
  }
  else
  {
    digitalWrite(2, HIGH);
  } 
}*/
