// if SOC is max, tell charging circuit they should stop charging
double stop_charging(double soc, double cap) {
  double stop_charging = 0;
  if (soc >= cap) {
    stop_charging = 1;
  }
  return stop_charging;
}
