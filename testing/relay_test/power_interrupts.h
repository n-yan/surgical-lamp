extern struct sys_states states;
extern struct fault_state;
//turns mains off and switches to battery if there is no battery fault
void mains_off(){
  states.main_on = false;
  //if there is no fault, switch to battery
  if (fault_state.no_fault) {
    digitalWrite(POW_CONTROL, HIGH);
  }
  //if there is a fault, the system should already be turned off. (? check)
}

//turns mains on
void mains_on() {
  states.main_on = true;
  digitalWrite(POW_CONTROL, LOW);
}
