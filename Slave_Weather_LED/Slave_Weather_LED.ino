#include <dht11.h>
#include <SoftwareSerial.h>
#include <LedControl.h>
#include <ArduinoJson.h>

#define DHT11PIN 4

dht11 DHT11;

float humidity_1 = 0;
float temperature_1 = 0;
uint16_t rainValue = 0;
uint16_t ldrValue = 0;
uint16_t soilMoisture = 0;

SoftwareSerial swSerial(10, 11); // RX, TX (change pin numbers accordingly)

// Define the connections to the MAX7219 module
const int MAX7219_DIN = 9;  // Data in pin
const int MAX7219_CLK = 8;  // Clock pin
const int MAX7219_CS = 7;   // Chip select pin
const int NUM_DEVICES = 2; // Number of MAX7219 modules (1 if you're using only one)

LedControl lc = LedControl(MAX7219_DIN, MAX7219_CLK, MAX7219_CS, NUM_DEVICES);

void setup()
{
  Serial.begin(9600);
  swSerial.begin(9600);

  // Initialize the LED matrix
  lc.shutdown(0, false); // Wake up the MAX7219
  lc.setIntensity(0, 8); // Set the brightness (0-15)
  lc.clearDisplay(0);    // Clear the display
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

  // Display the data on the LED matrix
  displayDataOnMatrix(jsonDoc);

  delay(1000); // Adjust the delay as needed to control data transmission rate
}

void displayDataOnMatrix(JsonDocument &data)
{
  // Clear the display before showing new data
  lc.clearDisplay(0);

  // Example: Display humidity value in binary format on the LED matrix
  int humidityValue = data["humidity"];
  for (int row = 0; row < 8; row++)
  {
    lc.setRow(0, row, (humidityValue >> row) & 0x01);
  }
}
