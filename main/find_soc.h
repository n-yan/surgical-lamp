// obtain constants and create SOC discharge curve, calculate SOC
// voltage is obtained from voltage sensor
double disch_calc_soc(double voltage, double a, double b, double c) {
  double soc = (-b+sqrt(b^2-4*a*c))/(2*a);
  return soc;
}

// obtains soc estimation from charging equation
double charge_soc_estim_eq(double dod_prev, double current, int delta_t, double cap) {
  double dod_delta = current*delta_t/cap;
  double dod = dod_prev + dod_delta;
  double soc = 1 - dod;
  
  return soc;
}

void find_soc() {
  switch(charge_state) {
    case INIT:
      // TODO: put in ryan code 
      break;
    case DISCHARGE:
      soc = disch_calc_soc(voltage, a, b, c);
      break;
    case CHARGE:
      soc = charge_soc_estim_eq(dod_prev, current, delta_t, cap); //define delta_t
      break;
  }
}
