void control_charge {
  if (mains_on) {
    charge_state = CHARGE;
  } else {
    charge_state = DISCHARGE;
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
