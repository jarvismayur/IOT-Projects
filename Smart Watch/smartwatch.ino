#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <SSD1306Wire.h>

// Initialize the BNO055 sensor
Adafruit_BNO055 bno = Adafruit_BNO055();

// WiFi credentials
const char* ssid = "YourSSID";
const char* password = "YourPassword";

// Server details
const char* serverIP = "your-server-ip";
const int serverPort = 80;
const String serverEndpoint = "/sensor_data";

// OLED Display
SSD1306Wire display(0x3c, SDA, SCL);

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA, SCL);
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  
  // Initialize the BNO055 sensor
  if (!bno.begin())
  {
    Serial.println("Could not find a valid BNO055 sensor, check wiring!");
    while (1);
  }
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  sensors_event_t event;
  bno.getEvent(&event);

  // Read sensor data
  float temperature = event.temperature;
  float orientationX = event.orientation.x;
  float orientationY = event.orientation.y;
  float orientationZ = event.orientation.z;
  
  // Create a JSON object to send data
  DynamicJsonDocument jsonDoc(200);
  jsonDoc["temperature"] = temperature;
  jsonDoc["orientation_x"] = orientationX;
  jsonDoc["orientation_y"] = orientationY;
  jsonDoc["orientation_z"] = orientationZ;

  // Serialize JSON to a string
  String jsonStr;
  serializeJson(jsonDoc, jsonStr);

  // Send data to the server
  sendSensorData(jsonStr);

  // Display sensor data on OLED
  display.clear();
  display.drawString(0, 0, "Temperature: " + String(temperature) + " C");
  display.drawString(0, 15, "Orientation X: " + String(orientationX));
  display.drawString(0, 30, "Orientation Y: " + String(orientationY));
  display.drawString(0, 45, "Orientation Z: " + String(orientationZ));
  display.display();

  delay(1000); // Adjust the delay as needed
}

void sendSensorData(String data) {
  HTTPClient http;
  http.begin(serverIP, serverPort, serverEndpoint);
  http.addHeader("Content-Type", "application/json");

  int httpCode = http.POST(data);

  if (httpCode > 0) {
    String payload = http.getString();
    Serial.println(httpCode);
    Serial.println(payload);
  } else {
    Serial.println("Error sending data");
  }

  http.end();
}
