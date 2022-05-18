void mains_off(){
  mains_on = false;
  //if there is no fault, switch to battery
  if (fault_state.no_fault) {
    digitalWrite(POW_CONTROL, HIGH);
  }
  //if there is a fault, the system should already be turned off. (? check)
}

void mains_on() {
  mains_on = true;
  if (fault_state.no_fault) {
    digitalWrite(FAULT_LED, LOW);
  } else {
    digitalWrite(FAULT_LED, HIGH);
  }
}

void lamp_toggle() {
  
}
