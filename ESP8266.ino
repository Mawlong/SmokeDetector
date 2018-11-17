#include <SoftwareSerial.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//auth token sent by blynk servers
char auth[] = "46f62e19db7e4297b75c9d84d168c06e";
//WiFi SSID and password
char ssid[] = "Leon";
char pass[] = "1212alexa";

//Blynk library routines Blynk Timer inherits SimpleTimer Library
//a well known and widely used library to time multiple events on hardware. 
BlynkTimer timer;

//Defining ports fro Serial Communication
SoftwareSerial s(D6,D5);

int data;

void detectSmoke()
{
  //Write to the stream
   s.write("0");
  //if serial communication is available (Boolean) 
  if (s.available()>0)
  {
    //reading data sent via serial communication from Arduino
    data=s.read();
    
    Serial.println(data);
    
    if(data > 200)
    {
      //Write a value of 1 to Virtual pin 1
      // This inturn sends a HTTP PUT request to IFTTT servers
      Blynk.virtualWrite(V1,1);
      
      Serial.println("SMOKE!");
      delay(5000);
    }
  }
}

void setup() 
{
  // to define Baud rate between UART devices
  s.begin(9600);

  //to print values on Serial Monitor
  Serial.begin(9600);
  
  //to start connection for transmission of data to Blynk Servers
  Blynk.begin(auth, ssid, pass);
  
  //call function detectSmoke() after 1 second
  timer.setInterval(1000L, detectSmoke);
}
 
void loop() 
{
  //to start blynk services
  Blynk.run();
  //to start timer Routine
  timer.run();
}
