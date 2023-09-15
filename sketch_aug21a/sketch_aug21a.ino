#include <Wire.h>
#include <Servo.h>
#include <MPU6050.h>

MPU6050 mpu;
Servo servo1;
Servo servo2;

int gyroThreshold = 10;

void setup() {
  Wire.begin();
  servo1.attach(9);
  servo2.attach(10);
  
  mpu.initialize();
  
  Serial.begin(9600);
}

void loop() {
  int16_t gyroY = mpu.getRotationY();
  
  if (abs(gyroY) > gyroThreshold) {
    int servo1Position = map(gyroY, -90, 90, 0, 180);
    int servo2Position = map(gyroY, -90, 90, 180, 0);
    
    servo1.write(servo1Position);
    servo2.write(servo2Position);
    
    Serial.print("Gyro Y: ");
    Serial.print(gyroY);
    Serial.print(" Servo1: ");
    Serial.print(servo1Position);
    Serial.print(" Servo2: ");
    Serial.println(servo2Position);
  }
  
  delay(100);
}
