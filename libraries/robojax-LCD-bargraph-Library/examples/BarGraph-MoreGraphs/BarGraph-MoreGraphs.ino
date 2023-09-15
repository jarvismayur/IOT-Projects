/*
 * This Arduino sketch displays multiple bargraphs on LCD1602-I2C
 * Original library was taken from https://playground.arduino.cc/Code/LcdBarGraph/
 * Modified by Ahmad Shamshiri on May 25, 2019 at 19:43 in Ajax, Ontario, Canada
 * Visit http://robojax.com/learn/arduino for other Arduino codes
 * Watch video instruction for this code:
 * 
 * Robojax Arduino Course on Udemy where  you get Schematic Diagram of this sketch 
 * and many other robotics related lectures and codes. Purchase the course here: http://bit.ly/rj-udemy
 * 

 * This code is "AS IS" without warranty or liability. Free to be used as long as you keep this note intact.* 
 * This code has been download from Robojax.com
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LcdBarGraphRobojax.h>

byte lcdNumCols = 16; // -- number of columns in the LCD
byte lcdLine = 2; // -- number of line in the LCD

byte sensorPin = 0; // -- value for this example

LiquidCrystal_I2C lcd(0x3f,lcdNumCols,lcdLine); //0x3f is address for I2C
                  // to get I2C address, run I2C Scanner. 
                  //Link is provided (in same page as this code) at http://robojax.com/learn/arduino
LcdBarGraphRobojax lbg(&lcd, lcdNumCols, 0, 0);  // -- creating a 4 char wide bargaph in the end of second column (column 1)

// -- creating a 4 chars wide bars
LcdBarGraphRobojax lbg0(&lcd, 4, 0, 0); // -- First line at column 0
LcdBarGraphRobojax lbg1(&lcd, 4, 5, 0); // -- First line at column 5
LcdBarGraphRobojax lbg2(&lcd, 4, 10, 0); // -- First line at column 10
LcdBarGraphRobojax lbg3(&lcd, 4, 0, 1); // -- Second line at column 0
LcdBarGraphRobojax lbg4(&lcd, 4, 5, 1);  // -- Second line at column 5
LcdBarGraphRobojax lbg5(&lcd, 4, 10, 1); // -- Second line at column 0

byte i0 = 0;
byte i1 = 0;
byte i2 = 0;
byte i3 = 0;
byte i4 = 0;
byte i5 = 0;

void setup(){
  // -- initializing the LCD
  lcd.begin();
  lcd.clear();
  // -- do some delay: some time I've got broken visualization
  delay(100);
}

void loop()
{
  // -- draw bar graph from the analog value readed
  lbg0.drawValue( i0, 255);
  lbg1.drawValue( i1, 255);
  lbg2.drawValue( i2, 255);
  lbg3.drawValue( i3, 255);
  lbg4.drawValue( i4, 255);
  lbg5.drawValue( i5, 255);
  // -- do some delay: frequent draw may cause broken visualization
  delay(100);
  
  i0 += 5;
  i1 += 7;
  i2 += 9;
  i3 += 11;
  i4 += 13;
  i5 += 15;
}