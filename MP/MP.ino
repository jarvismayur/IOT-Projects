#include <Wire.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp; // Create BMP280 instance

void setup() {
  Serial.begin(9600);
  if (!bmp.begin(0x76)) { // 0x76 or 0x77 based on your sensor's address
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }
}

void loop() {
  float temperature = bmp.readTemperature();
  float pressure = bmp.readPressure() / 100.0; // Convert Pa to hPa
  float altitude = bmp.readAltitude(1013.25); // Standard sea-level pressure

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" hPa");

  Serial.print("Altitude: ");
  Serial.print(altitude);
  Serial.println(" meters");

  Serial.println();

  delay(1000);
}
