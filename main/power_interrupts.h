//turns mains off and switches to battery if there is no battery fault
void mains_off(){
  mains_on_state = false;
  //if there is no fault, switch to battery
  if (fault_state.no_fault) {
    digitalWrite(POW_CONTROL, LOW);
  }
  //if there is a fault, the system should already be turned off. (? check)
}

//turns mains on
void mains_on() {
  mains_on_state = true;
  digitalWrite(POW_CONTROL, HIGH);
}

//toggles lamp state
void lamp_toggle() {
  lights_on_state = !lights_on_state;
  if (lights_on_state) {
    digitalWrite(LIGHT_OUT, HIGH);
  } else {
    digitalWrite(LIGHT_OUT, LOW);
  }
  
}
