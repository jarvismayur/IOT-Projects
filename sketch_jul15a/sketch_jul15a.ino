#include <dht11.h>
#define DHT11PIN 4

dht11 DHT11;

void  setup()
{
  Serial.begin(9600);
 
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
  
  delay(2000);

}
