#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);
const int switchPin = 6;
int switchState = 0;
int prevSwitchState = 0;
double voltageReading = 0;
double storedCapacity = 0;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  pinMode(switchPin,INPUT);
  pinMode(A0, INPUT);

  while(digitalRead(switchPin) == 0) {
    lcd.clear();
    voltageReading = (double)(analogRead(A0)*(50/2.58))/(1024/5)+(25);
    lcd.print("Set Capacity");
    lcd.setCursor(0,1);
    lcd.print(voltageReading);
    lcd.print("Ah");
    delay(100);
  }
  storedCapacity = voltageReading;
}

void loop() {
  
  // Display the current battery capacity
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Battery Capacity");
  lcd.setCursor(0,1);
  lcd.print(storedCapacity);
  lcd.print("Ah");
  delay(100);
  //Change the battery capacity
  switchState = digitalRead(switchPin);
  if((switchState == 1) && (prevSwitchState == 0)) {
    prevSwitchState = switchState;
    while ((switchState != 1) && (prevSwitchState == 0)) {
      voltageReading = (double)(analogRead(A0)*(50/2.58))/(1024/5)+(25);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Battery Capacity");
      lcd.setCursor(0,1);
      lcd.print(voltageReading);
      lcd.print("Ah");
      lcd.clear();
      delay(100);
      prevSwitchState = switchState;
      switchState = digitalRead(switchPin);
    }
    storedCapacity = voltageReading;
  }
}
