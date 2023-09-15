#define buzzer  1;
static const int irSensorPin = 2; // Replace with the actual pin number for the IR sensor
int SensorStatePrevious = LOW;
unsigned long minSensorDuration = 3000;
unsigned long minSensorDuration2 = 6000;
unsigned long SensorLongMillis;
bool SensorStateLongTime = false;
const int intervalSensor = 50;
unsigned long previousSensorMillis;
unsigned long SensorOutDuration;
unsigned long currentMillis;

const int motorEnableA = 9;
const int motorInput1 = 4;
const int motorInput2 = 3;

void setup() {
  Serial.begin(9600);
  pinMode(irSensorPin, INPUT); // Set IR sensor pin as input
  pinMode(buzzer, OUTPUT);
  pinMode(motorEnableA, OUTPUT);
  pinMode(motorInput1, OUTPUT);
  pinMode(motorInput2, OUTPUT);
  Serial.println("Press button");
}

void readSensorState() {
  if (currentMillis - previousSensorMillis > intervalSensor) {
    int irSensorState = digitalRead(irSensorPin); // Read IR sensor state

    if (irSensorState == LOW && SensorStatePrevious == HIGH && !SensorStateLongTime) {
      SensorLongMillis = currentMillis;
      SensorStatePrevious = LOW;
      Serial.println("IR Sensor activated");
    }

    SensorOutDuration = currentMillis - SensorLongMillis;

    if (irSensorState == LOW && !SensorStateLongTime && SensorOutDuration >= minSensorDuration) {
      SensorStateLongTime = true;
      digitalWrite(motorInput1, HIGH);
      digitalWrite(motorInput2, LOW);
      analogWrite(motorEnableA, 255);
      Serial.println("IR Sensor long activated - Starting Motor");
    }

    if (irSensorState == LOW && SensorStateLongTime && SensorOutDuration >= minSensorDuration2) {
      SensorStateLongTime = true;
      digitalWrite(buzzer, HIGH);
      delay(1000);
      Serial.println("IR Sensor long activated - Sounding Buzzer");
    }

    if (irSensorState == HIGH && SensorStatePrevious == LOW) {
      SensorStatePrevious = HIGH;
      SensorStateLongTime = false;
      digitalWrite(motorInput1, HIGH);
      digitalWrite(motorInput2, LOW);
      analogWrite(motorEnableA, 255);
      digitalWrite(buzzer, LOW);
      Serial.println("IR Sensor released - Stopping Motor and Buzzer");
    }

    if (irSensorState == LOW) { // When IR sensor does not provide output
      digitalWrite(motorInput1, LOW);
      digitalWrite(motorInput2, LOW);
      analogWrite(motorEnableA, 0);
      digitalWrite(buzzer, HIGH);
      Serial.println("IR Sensor not providing output - Starting Motor and Buzzer");
    }

    previousSensorMillis = currentMillis;
  }
}

void loop() {
  currentMillis = millis();
  readSensorState();
}
