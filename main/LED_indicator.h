// LED level indicates the battery level
// 3 green LED, 1 red LED
void LED_indicator() {
  // assume all states have an initial state of 0
  if (SOC > 0.8) {
    digitalWrite(GREEN40, HIGH);
    digitalWrite(GREEN60, HIGH);
    digitalWrite(GREEN80, HIGH);
    digitalWrite(RED20, LOW);
  
  } else if (SOC > 0.6) {
    digitalWrite(GREEN60,HIGH);
    digitalWrite(GREEN40, HIGH);
    digitalWrite(RED20, LOW);
    digitalWrite(GREEN80, LOW); 
      
  } else if (SOC > 0.4) {
    digitalWrite(GREEN40, HIGH);
    digitalWrite(RED20, LOW);
    digitalWrite(GREEN60, LOW);
    digitalWrite(GREEN80, LOW);
    
  } else if (SOC > 0.2) {
    digitalWrite(RED20, HIGH);
    digitalWrite(GREEN40, LOW);
    digitalWrite(GREEN60, LOW);
    digitalWrite(GREEN80, LOW);
    
  } else {
    //TODO: better solution. don't want delay here (for consistent
    // delta t/loop time, for current calculation in charge soc est.)
    digitalWrite(GREEN40, LOW);
    digitalWrite(GREEN60, LOW);
    digitalWrite(GREEN80, LOW);
    digitalWrite(RED20, HIGH);
    delay(200);
    digitalWrite(RED20, LOW);
    delay(200);
  }
}
