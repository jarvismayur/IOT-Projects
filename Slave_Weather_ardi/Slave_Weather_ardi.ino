#include <dht11.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

#define DHT11PIN 4

dht11 DHT11;

float humidity_1 = 0;
float temperature_1 = 0;
uint16_t rainValue = 0;
uint16_t ldrValue = 0;
uint16_t soilMoisture = 0;

SoftwareSerial swSerial(10, 11); // RX, TX (change pin numbers accordingly)

void setup()
{
  Serial.begin(9600);
  swSerial.begin(9600);
}

void loop()
{
  Serial.println();

  int chk = DHT11.read(DHT11PIN);
  int sensorValue = analogRead(A0);
  int sensorValue_2 = analogRead(A1);
  int sensorValue_3 = analogRead(A2);

  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, 2);

  Serial.print("Temperature  (C): ");
  Serial.println((float)DHT11.temperature, 2);

  Serial.print("Rain Drop : ");
  Serial.println(sensorValue);

  Serial.print("Day Light : ");
  Serial.println(sensorValue_2);

  Serial.print("Soil Moisture  : ");
  Serial.println(sensorValue_3);

  // Prepare data to be sent over SoftwareSerial in JSON format
  StaticJsonDocument<200> jsonDoc;
  jsonDoc["humidity"] = (float)DHT11.humidity;
  jsonDoc["temperature"] = (float)DHT11.temperature;
  jsonDoc["rainValue"] = (uint16_t)sensorValue;
  jsonDoc["ldrValue"] = (uint16_t)sensorValue_2;
  jsonDoc["soilMoisture"] = (uint16_t)sensorValue_3;

  String jsonString;
  serializeJson(jsonDoc, jsonString);

  // Send JSON data over SoftwareSerial
  swSerial.println(jsonString);
  delay(1000); // Adjust the delay as needed to control data transmission rate
}
