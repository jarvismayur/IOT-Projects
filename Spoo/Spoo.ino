#include <Wire.h>

#include <MPU6050.h>

#include <Servo.h>   

Servo servo1;

Servo servo2;          


MPU6050 sensor ;

int16_t ax, ay, az ;
int16_t gx, gy, gz ;

void setup ( )

{ 

servo1.attach (3);

servo2.attach (5);

servo1.write(90);

servo2.write(90);

Wire.begin ( );

Serial.begin  (9600); 

Serial.println  ( "Initializing the sensor" ); 

sensor.initialize ( ); 

Serial.println (sensor.testConnection ( ) ? "Successfully Connected" : "Connection failed"); 

delay (1000); 

Serial.println ( "Taking Values from the sensor" );

delay (1000);

}




void loop ( ) 

{ 

sensor.getMotion6 (&ax, &ay, &az, &gx, &gy, &gz);

ax = map (ax, -17000, 17000, 0, 180) ;

ay = map (ay, -17000, 17000, 0, 180) ;


servo1.write(ax);
Serial.print(ax);

servo2.write(ay); 
Serial.println(ay);

delay(1);

}
