//hardware interrupt
#define MAINS_MONITOR 3 //able to use hw interrupt

//relays
#define POW_CONTROL 0
//following relays will be off
#define CH_CUTOFF 1
#define BATT_CUTOFF 2


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

}

void loop() {
  if (digitalRead(MAINS_MONITOR) == LOW) {
    digitalWrite(POW_CONTROL, HIGH);
  } else {
    digitalWrite(POW_CONTROL, LOW);
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
