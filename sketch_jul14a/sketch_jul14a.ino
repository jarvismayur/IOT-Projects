#include <Servo.h>

const int pirPin = 2;        // PIR sensor pin
const int servo1Pin = 6;     // First servo motor pin
const int servo2Pin = 4;     // Second servo motor pin
const int ledPin = 5;        // LED pin

Servo servo1;
Servo servo2;

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);

  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  
  // Initialize the servos to a closed position
  servo1.write(180);
  servo2.write(180);
}

void loop() {
  int pirValue = digitalRead(pirPin);
  
  if (pirValue == HIGH) {
    openDoor();
  } else {
    closeDoor();
  }
}

void openDoor() {
  digitalWrite(ledPin, HIGH);    // Turn on the LED
  
  // Rotate the servo motors to open the door
  servo1.write(0);
  servo2.write(180);
  
  delay(5000);                   // Wait for the door to open
  
  digitalWrite(ledPin, LOW);     // Turn off the LED
}

void closeDoor() {
  // Rotate the servo motors to close the door
  servo1.write(0);
  servo2.write(180);
  
  delay(2000);                   // Wait for the door to close
}
