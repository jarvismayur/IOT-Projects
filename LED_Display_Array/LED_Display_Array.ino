#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,3);
SoftwareSerial mySerial (6,5);   //(RX, TX);

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 3
int i = 0;
String val = "No Data";
String oldval;
String newval = "No Data";


MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);


void setup(){
  
  // put your setup code here, to run once:
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  // put your setup 
  lcd.begin(16,2);
  mySerial.begin(9600);
  Serial.begin(9600);
  lcd.setCursor(0, 0);
  lcd.print("Wireless Notice");
  lcd.setCursor(0, 1);
  lcd.print("     Board     ");
  //delay(3000);
  lcd.clear();
  lcd.print("Welcome!");
  myDisplay.begin();
  myDisplay.setIntensity(2);
  myDisplay.displayClear();
  myDisplay.displayScroll(" Smart Agriculture Management System  by Kids World School Students  ", PA_CENTER, PA_SCROLL_LEFT, 100);
}

  
void loop(){
    if(myDisplay.displayAnimate()){
      myDisplay.displayReset();
    }
  val = mySerial.readString();
  val.trim();
  Serial.println(val);
  if(val != oldval)
  {
    newval = val;
  }
  lcd.clear();
  lcd.setCursor(i, 0);
  lcd.print(newval);
  i++;
  if(i >= 15)
  {
    i = 0;
  }
  val = oldval;
  }
