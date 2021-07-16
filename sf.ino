#include "DHT.h"       
#define DHTTYPE DHT11   
#define dht_dpin 0
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

const int sensor_pin = A0;  /* Connect Soil moisture analog sensor pin to A0 of NodeMCU */
int relayInput = 2; // the input to the relay pin

char auth[] = "96185eb907904d209bddb196f0280051";
char ssid[] = "SARMAH's_5Ghz";
char pass[] = "Swandeep@1998";

BlynkTimer timer;

int LED=5;//D1
float t;
float h;
int moisture_soil;
int moisture_percentage;
DHT dht(dht_dpin, DHTTYPE); 


void temperature()
{
  Blynk.virtualWrite(V6, t);
}

void moisture()
{
  Blynk.virtualWrite(V2,moisture_soil);
}

void humidity()
{
  Blynk.virtualWrite(V5, h);
}

void setup() {
  Serial.begin(9600); /* Define baud rate for serial communication */
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  Serial.println("Humidity and temperature\n\n");
  timer.setInterval(1000L, temperature);
  timer.setInterval(1000L, humidity);
  pinMode(LED,OUTPUT);
  pinMode(relayInput, OUTPUT); // initialize pin as OUTPUT

}

void loop() {
  float moisture_percentage;

  moisture_percentage = ( 100.00 - ( (analogRead(sensor_pin)/1023.00) * 100.00 ));

  Serial.print("Soil Moisture(in Percentage) = ");
  Serial.print(moisture_percentage);
  moisture_soil=moisture_percentage;
  Serial.println("%");
  if(moisture_percentage>20)
  {
    digitalWrite(relayInput,LOW);
    digitalWrite(LED,LOW);
  }
  else
  {
    digitalWrite(relayInput,HIGH);
    digitalWrite(LED,HIGH);
  }
    
  h = dht.readHumidity();
  t = dht.readTemperature();         
  Serial.print("Current humidity = ");
  Serial.print(h);
  Serial.print("%  ");
  Serial.print("temperature = ");
  Serial.print(t); 
  Serial.println("C  ");
  delay(1000);

  Blynk.run();
  timer.run(); 
}
