#include <Wire.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#define RECEIVER_ADDRESS 8

// Variables to store sensor data
float humidity = 0.0;
float temperature = 0.0;
int rainValue = 0;
int ldrValue = 0;
int soilMoisture = 0;

ESP8266WebServer server(80);

// Function to handle root page request
void handleRootPage() {
  String html = "<html><body>";
  html += "Humidity (%): " + String(humidity) + "<br>";
  html += "Temperature (C): " + String(temperature) + "<br>";
  html += "Rain Drop: " + String(rainValue) + "<br>";
  html += "Day Light: " + String(ldrValue) + "<br>";
  html += "Soil Moisture: " + String(soilMoisture) + "<br>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(9600);

  Wire.begin(D1, D2); // Initialize I2C communication (sda=D3, scl=D4)
  
  // Connect to Wi-Fi
  WiFi.begin("JARVIS", "J97j(323");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Wi-Fi connected");
  Serial.println("IP address: " + WiFi.localIP().toString());

  // Set up the web server
  server.on("/", handleRootPage);
  server.begin();
  Serial.println(".");

  
  
}

void loop() {
  Wire.onReceive(receiveData);
  Wire.beginTransmission(RECEIVER_ADDRESS); // Request data from Arduino
  Wire.endTransmission();
  server.handleClient(); // Handle web server requests
  
}

void receiveData(int byteCount) {
  while (Wire.available()) {
    humidity = Wire.read();
    temperature = Wire.read();
    rainValue = Wire.read();
    ldrValue = Wire.read();
    soilMoisture = Wire.read();
    Serial.println("Wi-Fi connected");
  }
}
