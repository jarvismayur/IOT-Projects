#include <SPI.h>
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
SoftwareSerial bluetoothSerial(10, 11); // Use pins 10 (RX) and 11 (TX) for Bluetooth

void setup() {
  Serial.begin(9600);

  if (!bmp.begin(0x76)) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }
  ss.begin(GPSBaud);
  bluetoothSerial.begin(9600); // Initialize Bluetooth communication
}

void loop() {
  int chk = DHT11.read(DHT11PIN);
  int sensorValue = analogRead(A0);
  int sensorValue_2 = analogRead(A1);
  int sensorValue_3 = analogRead(A2);

  float pressure = bmp.readPressure() / 100.0;
  float altitude = bmp.readAltitude(1013.25);

  Serial.print("Humidity (%): "); 
  Serial.println((float)DHT11.humidity, 2);

  Serial.print(" Temperature (C): ");
  Serial.println((float)DHT11.temperature, 2);

  Serial.print(" Rain Drop: ");
  Serial.println(sensorValue);

  Serial.print(" Day Light: ");
  Serial.println(sensorValue_2);

  Serial.print(" Soil Moisture: ");
  Serial.println(sensorValue_3);

  Serial.print(" Altitude: ");
  Serial.println(altitude);

  Serial.print(" Pressure: ");
  Serial.println(pressure);

  // Transmit data via Bluetooth
  bluetoothSerial.print("Humidity: ");
  bluetoothSerial.print((float)DHT11.humidity, 2);
  bluetoothSerial.print(" Temperature: ");
  bluetoothSerial.print((float)DHT11.temperature, 2);
  bluetoothSerial.print(" Rain Drop: ");
  bluetoothSerial.print(sensorValue);
  bluetoothSerial.print(" Day Light: ");
  bluetoothSerial.print(sensorValue_2);
  bluetoothSerial.print(" Soil Moisture: ");
  bluetoothSerial.print(sensorValue_3);
  bluetoothSerial.print(" Altitude: ");
  bluetoothSerial.print(altitude);
  bluetoothSerial.print(" Pressure: ");
  bluetoothSerial.print(pressure);
  bluetoothSerial.print("\n");


  delay(3000);
}
