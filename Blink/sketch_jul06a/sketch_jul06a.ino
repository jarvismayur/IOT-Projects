// Ultrasonic sensor pins
const int trigPin = 2;
const int echoPin = 3;

// Motor control pins
const int leftMotorPin1 = 4;
const int leftMotorPin2 = 5;
const int rightMotorPin1 = 6;
const int rightMotorPin2 = 7;

// Distance threshold for obstacle detection (in centimeters)
const int obstacleThreshold = 20;

// Motor speed variables
const int baseSpeed = 180; // Adjust this value to control the overall speed
int leftMotorSpeed = baseSpeed;
int rightMotorSpeed = baseSpeed;

void setup() {
  // Initialize ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initialize motor control pins
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);

  // Set initial motor direction (forward)
  digitalWrite(leftMotorPin1, HIGH);
  digitalWrite(leftMotorPin2, LOW);
  digitalWrite(rightMotorPin1, HIGH);
  digitalWrite(rightMotorPin2, LOW);

  // Start serial communication
  Serial.begin(9600);
}

void loop() {
  // Perform obstacle detection
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

  // Check if obstacle is detected
  if (distance <= obstacleThreshold) {
    // Obstacle detected, avoid it
    avoidObstacle();
  } else {
    // No obstacle detected, move forward
    moveForward();
  }

  // Print the distance to the obstacle
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}

void moveForward() {
  // Set motor speeds to move forward
  analogWrite(leftMotorPin1, leftMotorSpeed);
  analogWrite(leftMotorPin2, LOW);
  analogWrite(rightMotorPin1, rightMotorSpeed);
  analogWrite(rightMotorPin2, LOW);
}

void avoidObstacle() {
  // Stop the robot
  analogWrite(leftMotorPin1, 0);
  analogWrite(leftMotorPin2, 0);
  analogWrite(rightMotorPin1, 0);
  analogWrite(rightMotorPin2, 0);

  // Reverse for a short duration
  analogWrite(leftMotorPin1, 0);
  analogWrite(leftMotorPin2, baseSpeed);
  analogWrite(rightMotorPin1, 0);
  analogWrite(rightMotorPin2, baseSpeed);
  delay(500);

  // Turn right for a short duration
  analogWrite(leftMotorPin1, leftMotorSpeed);
  analogWrite(leftMotorPin2, LOW);
  analogWrite(rightMotorPin1, 0);
  analogWrite(rightMotorPin2, baseSpeed);
  delay(500);

  // Resume moving forward
  moveForward();
}
