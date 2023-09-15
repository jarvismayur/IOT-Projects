#include <dht11.h>
#include <Wire.h>
#define DHT11PIN 4

dht11 DHT11;

void setup()
{
  Serial.begin(9600);
  Wire.begin(); // Initialize I2C communication as the master
}

void loop()
{
  Serial.println();

  int chk = DHT11.read(DHT11PIN);
  int sensorValue = analogRead(A0);
  int sensorValue_2 = analogRead(A1);
  int sensorValue_3 = analogRead(A1);

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

  // Prepare data to be sent over I2C
  float humidity = (float)DHT11.humidity;
  float temperature = (float)DHT11.temperature;
  uint16_t rainValue = (uint16_t)sensorValue;
  uint16_t ldrValue = (uint16_t)sensorValue_2;
  uint16_t soilMoisture = (uint16_t)sensorValue_3;

  // Send sensor data to NodeMCU (receiver) with address 8
  Wire.beginTransmission(8); // NodeMCU address for the receiver
  Wire.write((byte*)&humidity, sizeof(humidity));
  Wire.write((byte*)&temperature, sizeof(temperature));
  Wire.write((byte*)&rainValue, sizeof(rainValue));
  Wire.write((byte*)&ldrValue, sizeof(ldrValue));
  Wire.write((byte*)&soilMoisture, sizeof(soilMoisture));
  Wire.endTransmission();

  delay(2000);
}
