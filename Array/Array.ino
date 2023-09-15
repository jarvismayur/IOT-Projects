int s1=A0; //TCRT1
int s2=A1; //TCRT2
int s3=A2; //TCRT3
int s4=A3; //TCRT4
int s5=A4; //TCRT5
int near=A6; //IR sensor at the front to detect obstacles
int CLP=12; //limit switch int state1;
int state1;
int state2;
int state3;
int state4;
int state5;
int nearstate;
int CLPstate;
void setup(){
Serial.begin(9600);
  pinMode(s1,INPUT);
  pinMode(s2,INPUT);
  pinMode(s3,INPUT);
  pinMode(s4,INPUT);
  pinMode(s5,INPUT);
  pinMode(near,INPUT);
  pinMode(CLP,INPUT); }
void loop(){
  state1=digitalRead(s1); //TCRT1 status
  state2=digitalRead(s2); //TCRT2 status
  state3=digitalRead(s3); //TCRT3 status
  state4=digitalRead(s4); //TCRT4 status
  state5=digitalRead(s5); //TCRT5 status
  nearstate=analogRead(near); //IR sensor status
  CLPstate=digitalRead(CLP); //Limit switch status
  Serial.print("s1 =");
  Serial.println(state1); //Print TCRT1 status
  Serial.print("s2 =");
  Serial.println(state2); //Print TCRT2 status
  Serial.print("s3 =");
  Serial.println(state3); //Print TCRT3 status
  Serial.print("s4 =");
  Serial.println(state4); //Print TCRT4 status
  Serial.print("s5 =");
  Serial.println(state5); //Print TCRT5 status
  Serial.print("IR =");
  Serial.println(nearstate); //Print IR sensor status
  Serial.print("BMP =");
  Serial.println(CLPstate); //Print Limit switch status
  delay(2000);
}
