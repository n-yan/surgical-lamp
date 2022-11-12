


// obtain constants and create SOC discharge curve, calculate SOC
// voltage is obtained from voltage sensor
void disch_calc_soc(double a, double b, double c) {
  soc = (-b+sqrt(b^2-4*a*c))/(2*a);
}

// obtains soc estimation from charging equation
void charge_soc_estim_eq() {
  //previously not charging (state was discharging/init)
  if (prev_t == 0) {
    dod = 1 - soc;

  //currently discharging. iterates on dod to find soc.
  } else {
    unsigned long t = millis();
    double delta_t = (t - prev_t)/1000;
    double dod_delta = current*delta_t/cap;
    dod += dod_delta;
    soc = 1 - dod;
    prev_t = t;
  }
}

void find_soc() {
  switch(charge_state) {
    case INIT:
      // TODO: put in ryan code 
      dod = 0;
      prev_t = millis();
      break;
    case DISCHARGE:
      disch_calc_soc(a, b, c);
      dod = 0;
      prev_t = millis();
      break;
    case CHARGE:
      charge_soc_estim_eq();
      break;
  }
}
