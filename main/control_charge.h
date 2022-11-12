void control_charge() {
  if (states.main_on) {
    digitalWrite(CH_CUTOFF, HIGH);
  } else {
    digitalWrite(CH_CUTOFF, LOW);
  }
}

/*
 * deprecated code -> charging logic controlled by ots battery charger
// if SOC is max, tell charging circuit they should stop charging
double stop_charging(double soc, double cap) {
  double stop_charging = 0;
  if (soc >= cap) {
    stop_charging = 1;
  }
  return stop_charging;
}
*/
