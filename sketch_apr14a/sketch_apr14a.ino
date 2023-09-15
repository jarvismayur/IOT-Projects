#include <WiFi.h>
#include <FirebaseESP32.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <WiFiClientSecure.h>
#include <WiFiUdp.h>

#define RXPin 16 // RX pin of GPS module
#define TXPin 17 // TX pin of GPS module
#define SOS_PIN 23 // pin for SOS button

SoftwareSerial gpsSerial(RXPin, TXPin);
TinyGPSPlus gps;

const char* ssid = "Airtel_9730687488";
const char* password = "Mayur2123456";
const char* host = "your_firebase_host";
const char* auth = "your_firebase_auth_token";
const char* databaseURL = "your_firebase_database_url";

FirebaseData firebaseData;
FirebaseAuth firebaseAuth;

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);
  pinMode(SOS_PIN, INPUT_PULLUP);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
  Firebase.begin(databaseURL, auth);
}

void loop() {
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      if (gps.location.isValid()) {
        // GPS location is valid
        float latitude = gps.location.lat();
        float longitude = gps.location.lng();
        if (digitalRead(SOS_PIN) == LOW) {
          // SOS button is pressed
          sendSOS(latitude, longitude);
        }
      }
    }
  }
}

void sendSOS(float latitude, float longitude) {
  // send SOS message and location to Firebase database
  String sosMessage = "SOS! Help needed at https://maps.google.com/maps?q=" + String(latitude, 6) + "," + String(longitude, 6);
  Firebase.setString(firebaseData, "/sos", sosMessage);
  if (firebaseData.dataType() == "null") {
    Serial.println("Error sending SOS message to Firebase");
  } else {
    Serial.println("SOS message sent to Firebase");
  }
}
