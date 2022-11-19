/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

// include the library code:
#include <LiquidCrystal.h>


// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 4, d5 = 5, d6 = 6, d7 = 7, A = 8, B = 9 ;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  pinMode(A, INPUT);
  pinMode(B, INPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Battery Lvl 100%");
  lcd.setCursor(0, 1);
  lcd.print("A cal | B OFF");

  pinMode(0,OUTPUT);
  pinMode(1,OUTPUT);
  pinMode(2,OUTPUT);
  digitalWrite(0,LOW);
  digitalWrite(0,LOW);
  digitalWrite(0,LOW);
}

void loop() {
  if ( digitalRead(A) == HIGH) {
    // callibration sequence initiated
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Calibrate?");
    lcd.setCursor(0,1);
    lcd.print("A Yes| B No");
      if ( digitalRead(B) == HIGH) {
        // No calibration sequence, go back to main
        lcd.clear();
        lcd.print("Battery Lvl 100%");
        lcd.setCursor(0, 1);
        lcd.print("A cal | B OFF");
      }
  } else if ( digitalRead(B) == HIGH){
      lcd.clear();
      lcd.print("Battery Lvl 100%");
      lcd.setCursor(0, 1);
      lcd.print("A cal | B OFF");
    }
  
    
}
