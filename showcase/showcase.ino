//hardware interrupt
#define MAINS_MONITOR 3 //able to use hw interrupt

//relays
#define POW_CONTROL 0
//following relays will be off
#define CH_CUTOFF 1
#define BATT_CUTOFF 2

#define BATT_VOLT A1

int volt_raw, volt_perc;
double volt;

#include <LiquidCrystal.h>
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 4, d5 = 5, d6 = 6, d7 = 7, A = 8, B = 9 ;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // put your setup code here, to run once:

  //interrupt pins
  pinMode(MAINS_MONITOR, INPUT);

  //HW interrupt does not seem to work - implememnt later
  /*
  attachInterrupt(digitalPinToInterrupt(MAINS_MONITOR), mains_off, FALLING);
  attachInterrupt(digitalPinToInterrupt(MAINS_MONITOR), mains_on, RISING);
  */
  
  //relay pins
  pinMode(POW_CONTROL, OUTPUT);
  pinMode(BATT_CUTOFF, OUTPUT);
  pinMode(CH_CUTOFF, OUTPUT);
  
  digitalWrite(CH_CUTOFF, LOW);
  digitalWrite(BATT_CUTOFF, HIGH);

  mains_on();

  //sensor
  pinMode(BATT_VOLT, INPUT);

  pinMode(A, INPUT);
  pinMode(B, INPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Battery Lvl 100%");
  lcd.setCursor(0, 1);
  lcd.print("A cal | B OFF");

}

void loop() {
  if (digitalRead(MAINS_MONITOR) == LOW) {
    digitalWrite(POW_CONTROL, HIGH);
  } else {
    digitalWrite(POW_CONTROL, LOW);
  }

  volt_raw = analogRead(BATT_VOLT);
  volt = volt_raw/815*12.94;
  volt_perc = 100*volt/13;

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
        lcd.print("Battery Lvl ");
        lcd.print(volt_perc);
        lcd.print("%");
        lcd.setCursor(0, 1);
        lcd.print("A cal | B OFF");
      }
  } else if ( digitalRead(B) == HIGH){
      lcd.clear();
      lcd.print("Battery Lvl ");
      lcd.print(volt_perc);
      lcd.print("%");
      lcd.setCursor(0, 1);
      lcd.print("A cal | B OFF");
  }
  
}

//turns mains off and switches to battery if there is no battery fault
void mains_off(){
  digitalWrite(POW_CONTROL, HIGH);
}

//turns mains on
void mains_on() {
  digitalWrite(POW_CONTROL, LOW);
}
