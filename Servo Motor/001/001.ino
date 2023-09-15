#include <Servo.h>

const int trigPin = 2;    // Ultrasonic sensor trigger pin
const int echoPin = 3;    // Ultrasonic sensor echo pin
const int servoPin = 9;   // Servo motor control pin
const int openAngle = 180;  // Angle to open the dustbin
const int closeAngle = 0;   // Angle to close the dustbin

Servo servo;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  servo.attach(servoPin);
}

void loop() {
  // Measure the distance
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  // Open or close the dustbin based on the distance
  if (distance <= 10) {
    openDustbin();
  } else {
    closeDustbin();
  }

  delay(500);  // Delay between measurements
}

void openDustbin() {
  servo.write(openAngle);
  delay(1000);  // Delay to allow the servo to open completely
}

void closeDustbin() {
  servo.write(closeAngle);
  delay(1000);  // Delay to allow the servo to close completely
}
