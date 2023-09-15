# include <Servo.h>
#include <MPU6050_tockn.h> 
#include <Wire.h>

MPU6050 mpu6050(Wire);
int X,Y,Z;
int OX,OY,OZ;
int error, diff, sum, ovr, ovr2, prev;
Servo myservo[2];
int pos = 0;
int g;
int g1 = 0;
int g2 = 0;
int g3 = 0;
int g4 = 0;
int g5 = 0;

int f;
int f1 = 0;
int f2 = 0;
int f3 = 0;
int f4 = 0;
int f5 = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  mpu6050.begin();
  //Serial.println("STRTM");
  // mpu6050.calcGyroOffsets(true);
  mpu6050.update();
  OX = mpu6050.getAngleX();
   OY = mpu6050.getAngleY();
  // OZ = mpu6050.getAngleZ();



  if(OX < 0){
    OX = OX *(-1);}
  else{
    OX = ((OX-OX)-OX)+10;}

  if(OY < 0){
    OY = (OY *(-1));}
  else{
    OY = ((OY-OY)-OY)+10;}

  if(OZ < 0){
    OZ = OZ *(-1);}
  else{
    OZ = (OZ-OZ)-OZ;}
  myservo[0].attach(3);
  myservo[1].attach(5);

  delay(10);
}

void loop() {
  mpu6050.update();
  g5 = g4;
  g4 = g3;
  g3 = g2;
  g2 = g1;
  g1 = OX + mpu6050.getAngleX();
  g = (g1 + g2 + g3 + g4 + g5)/5;
  // X = OX + mpu6050.getAngleX();
  f5 = f4;
  f4 = f3;
  f3 = f2;
  f2 = f1;
  f1 = OY + mpu6050.getAngleY();
  f = (f1 + f2 + f3 + f4 + f5)/5;
  
  // Y = OY + mpu6050.getAngleY();
  // Z = OZ + mpu6050.getAngleZ();
  
  // error = 0 - Y;
  // diff = error - prev;
  ovr = 90 - (f);
  ovr2 = 90 + (g);
  myservo[0].write(ovr);
  myservo[1].write(ovr2);
  delay(10);

}
