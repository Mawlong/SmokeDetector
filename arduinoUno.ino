
#include <SoftwareSerial.h>

//used to define serial ports for communication with UART device
//UART = universal asynchronous receiver transmitter  
SoftwareSerial s(5,6);

//defining pins for functions below
int redLED = 13;
int buzzer = 10;
int greenLED = 11;


void setup()
{
  //defining the baud rate for serial communication
  s.begin(9600);
  //to show output on serial monitor
  Serial.begin(9600);
  //defining the devices
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
}
 
void loop() 
{
  //initial setup
  digitalWrite(greenLED, HIGH);
  digitalWrite(redLED, LOW);
  digitalWrite(buzzer, LOW);
  //read analog value from MQ2 gas sensor
  int sensorValue = analogRead(A0);

  //write to the serial communication stream 
  s.write(sensorValue);
  //writing in serial monitor
  Serial.print("SMOKE VALUE: ");
  Serial.println(sensorValue);
  
  if(sensorValue>200)
  {
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, HIGH);
    digitalWrite(buzzer, HIGH);
    Serial.println("SMOKE DETECTED!");
    delay(5000);
  }
  delay(1000);
}
