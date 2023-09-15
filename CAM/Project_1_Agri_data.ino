#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <dht11.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

#define MAX_DEVICES 4
#define CS_PIN 3
#define DHT11PIN 4
static const int RXPin = 6, TXPin = 5;
static const uint32_t GPSBaud = 9600;

dht11 DHT11;
Adafruit_BMP280 bmp;
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);
SoftwareSerial bluetoothSerial(10, 11);



void setup() {
  Serial.begin(9600);


  if (!bmp.begin(0x76)) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }
  ss.begin(GPSBaud);
}

void writeFloatToI2C(float value) {
  byte *bytePointer = (byte *)&value;
  for (int i = 0; i < sizeof(float); i++) {
    Wire.write(bytePointer[i]);
  }
}

float readFloatFromI2C() {
  float value;
  byte *bytePointer = (byte *)&value;
  for (int i = 0; i < sizeof(float); i++) {
    bytePointer[i] = Wire.read();
  }
  return value;
}



void loop() {
  int chk = DHT11.read(DHT11PIN);
  int sensorValue = analogRead(A0);
  int sensorValue_2 = analogRead(A1);
  int sensorValue_3 = analogRead(A2);

  float pressure = bmp.readPressure() / 100.0; // Convert Pa to hPa
  float altitude = bmp.readAltitude(1013.25); // Standard sea-level pressure


  
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

  Serial.print("Altitude  : ");
  Serial.println(altitude);

  Serial.print("Pressure  :");
  Serial.println(pressure);
  
  

  delay(100);
}
