#include <Servo.h>

// Define constants for ultrasonic sensor pins
const int trigPin = 9;  // Trigger pin
const int echoPin = 10; // Echo pin

// Create a Servo object
Servo servoMotor;

void setup() {
  // Initialize the serial communication
  Serial.begin(9600);

  // Attach the servo to pin 3
  servoMotor.attach(3);

  // Initialize the ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Variables to hold the duration and distance
  long duration;
  int distance;

  // Clear the trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send a pulse to the trigger pin
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the pulse duration on the echo pin
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  distance = duration / 58;

  // Print the distance to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Check if an object is within a certain range (adjust the value as needed)
  if (distance < 30) {
    // If an object is detected within 30cm, rotate the servo by 90 degrees
    servoMotor.write(90);
    delay(1000); // Delay to allow the servo to reach the position
    servoMotor.write(0); // Return the servo to the initial position (0 degrees)
  }

  delay(100); // Add a small delay for stability
}
