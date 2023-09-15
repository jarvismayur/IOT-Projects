#include <LiquidCrystal.h>

// Define the ultrasonic sensor pins
const int trigPin = 2;
const int echoPin = 3;

// Define the LCD pins
const int rs = 12;
const int en = 9;
const int d4 = 2;
const int d5 = 3;
const int d6 = 4;
const int d7 = 5;

// Define the LCD object
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // Initialize the LCD
  lcd.begin(16, 2);

  // Set up the ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initialize the serial communication
  Serial.begin(9600);
}

void loop() {
  // Trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the echo duration
  long duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  float distance = duration * 0.034 / 2;

  // Display the distance on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.print(" cm");

  // Print the distance to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(1000);
}
