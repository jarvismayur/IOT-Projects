#include <dht11.h>
#include <ESP8266WiFi.h>

#define DHT11PIN 4
#define WIFI_SSID "JARVIS"
#define WIFI_PASSWORD "J97j(323"

dht11 DHT11;

void setup()
{
  Serial.begin(9600);

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected to Wi-Fi!");
}

void loop()
{
  Serial.println();

  int chk = DHT11.read(DHT11PIN);
  int sensorValue = analogRead(A0);
//  int sensorValue_2 = analogRead(A1);
//  int sensorValue_3 = analogRead(A2);

  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, 2);

  Serial.print("Temperature (C): ");
  Serial.println((float)DHT11.temperature, 2);

  Serial.print("Rain Drop: ");
  Serial.println(sensorValue);

  Serial.print("Day Light: ");
  Serial.println(sensorValue_2);

  Serial.print("Soil Moisture: ");
  Serial.println(sensorValue_3);

  // Send sensor data to Thingspeak
  sendDataToThingspeak(DHT11.humidity, DHT11.temperature, sensorValue, sensorValue_2, sensorValue_3);

  delay(2000);
}

void sendDataToThingspeak(float humidity, float temperature, int rainDrop, int dayLight, int soilMoisture)
{
  WiFiClient client;
  const char *host = "api.thingspeak.com";
  const int httpPort = 80;
  String data = "api_key=https://thingesp.siddhesh.me/api/v1/user/tembharemayur/project/TestMayur/endpoint?token=i5S0lZ43&field1=" + String(humidity) +
                "&field2=" + String(temperature) +
                "&field3=" + String(rainDrop) +
                "&field4=" + String(dayLight) +
                "&field5=" + String(soilMoisture);

  if (!client.connect(host, httpPort))
  {
    Serial.println("Connection to Thingspeak failed!");
    return;
  }

  // POST data to Thingspeak
  client.print("POST /update HTTP/1.1\r\n");
  client.print("Host: " + String(host) + "\r\n");
  client.print("Connection: close\r\n");
  client.print("Content-Type: application/x-www-form-urlencoded\r\n");
  client.print("Content-Length: ");
  client.print(data.length());
  client.print("\r\n\r\n");
  client.print(data);

  unsigned long timeout = millis();
  while (client.available() == 0)
  {
    if (millis() - timeout > 5000)
    {
      Serial.println("Client Timeout !");
      client.stop();
      return;
    }
  }

  while (client.available())
  {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println("Data sent to Thingspeak successfully!");
  client.stop();
}
