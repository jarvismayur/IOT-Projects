#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Declare the LCD object globally

void setup()
{
  Wire.begin(8); // Arduino is addressed as a slave with address 8
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  Serial.println("\nI2C Scanner");
  lcd.begin();  // Initialize the LCD object
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(4, 0);
  
  
  Serial.println("LED STARTED");
}

void loop()
{
  lcd.print("Hackster");// Your code logic here
}

void receiveEvent(int byteCount) {
  while (Wire.available()) {
    char receivedChar = Wire.read();
    Serial.print("Received: ");
    Serial.println(receivedChar);
    // Process the receivedChar as needed
  }
  
}
