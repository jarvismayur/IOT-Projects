/*------ Arduino Line Follower Code----- */

/*-------defining Inputs------*/

#define LS  D5     // left sensor

#define RS  D6    // right sensor


/*-------defining Outputs------*/

#define LM1 D1       // left motor

#define LM2 D2      // left motor

#define RM1 D3      // right motor

#define RM2 D4      // right motor


void setup()

{

  pinMode(LS, INPUT);

  pinMode(RS, INPUT);

  pinMode(LM1, OUTPUT);

  pinMode(LM2, OUTPUT);

  pinMode(RM1, OUTPUT);

  pinMode(RM2, OUTPUT);

}


void loop()

{

  if(digitalRead(LS) && digitalRead(RS))     // Move Forward

  {

    digitalWrite(LM1, HIGH);

    digitalWrite(LM2, LOW);

    digitalWrite(RM1, HIGH);

    digitalWrite(RM2, LOW);

  }

  

  if(!(digitalRead(LS)) && digitalRead(RS))     // Turn right

  {

    digitalWrite(LM1, LOW);

    digitalWrite(LM2, LOW);

    digitalWrite(RM1, HIGH);

    digitalWrite(RM2, LOW);

  }

  

  if(digitalRead(LS) && !(digitalRead(RS)))     // turn left

  {

    digitalWrite(LM1, HIGH);

    digitalWrite(LM2, LOW);

    digitalWrite(RM1, LOW);

    digitalWrite(RM2, LOW);

  }

  

  if(!(digitalRead(LS)) && !(digitalRead(RS)))     // stop

  {

    digitalWrite(LM1, LOW);

    digitalWrite(LM2, LOW);

    digitalWrite(RM1, LOW);

    digitalWrite(RM2, LOW);

  }

}
