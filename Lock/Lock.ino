#define BLYNK_PRINT Serial
#define LED D4

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "OfHNfYExvcRWB886UnwwKWdWya7qcXcN";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "JARVIS";
char pass[] = "J97j(323";

Servo servo;

uint8_t BUTTON=D2;
bool door;
int pos;

BLYNK_WRITE(V3)
{
  int pinValue=param.asInt();
  if(pinValue==1)
  {
      for (pos = 0; pos <= 180; pos += 5) { 
        servo.write(pos);              
        delay(15);
      }
      digitalWrite(LED,HIGH);                                                           //INVERTED STATUS OF LED PINS:HIGH means LOW
      door=true;
      Blynk.email("temBharemayur@gmail.com","door_lock_unlock status","Door is closed");
  }
  else
  {
    for (pos = 180; pos >= 0; pos -= 5) { 
      servo.write(pos);              
      delay(15);
    }
    digitalWrite(LED,LOW);                                                          //LOW-->HIGH
    door=false;
    Blynk.email("temBharemayur@gmail.com","door_lock_unlock status","Door is open");
  }
}

void IntCallback()
{
  if(door==false)
  {
      for (pos = 0; pos <= 180; pos += 5) { 
        servo.write(pos);              
        delay(15);
      }
      digitalWrite(LED,HIGH);                                                           //INVERTED STATUS OF LED PINS:HIGH means LOW
      door=true;
  }
  else
  {
    return;
  }
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  servo.attach(15);     //15--->D8
  pinMode(LED,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON),IntCallback,RISING);
}

void loop()
{
  Blynk.run();
}
