const int SENSOR_PIN = 4;  // Pin connected to the output (middle) wire of the PIR sensor
const int LED_PIN = 13;    // Pin connected to control the LED

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  Serial.println("PIR Motion Sensor with LED");

  pinMode(SENSOR_PIN, INPUT);   // Set sensor pin as input
  pinMode(LED_PIN, OUTPUT);     // Set LED pin as output
}

void loop() {
  int motion = digitalRead(SENSOR_PIN);  // Read sensor pin and store the value in "motion"

  if (motion == HIGH) {  // If motion is detected (sensor reads HIGH)
    Serial.println("Motion detected");
    digitalWrite(LED_PIN, HIGH);  // Turn the LED ON
  } else {
    Serial.println("No motion detected");
    digitalWrite(LED_PIN, LOW);   // Turn the LED OFF
  }

  delay(500);  // Delay to avoid rapid toggling of the LED
}
