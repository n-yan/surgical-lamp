#include "LED_indicator.h"
#include "find_soc.h"
#include "control_charge.h"

//PIN SETUP
#define RED20 4
#define GREEN40 5
#define GREEN60 6
#define GREEN80 7
#define FAULT_LED 8

//CHARGE STATE
enum charge_state{
  INIT, 
  CHARGE, 
  DISCHARGE
} ch_state;

void setup() {
  pinMode(RED20, OUTPUT);
  pinMode(GREEN40, OUTPUT);
  pinMode(GREEN60, OUTPUT);
  pinMode(GREEN80, OUTPUT);
  pinMode(FAULT_LED, OUTPUT);

}

void loop() {
  //find soc
  switch(ch_state) {
    case DISCHARGE:
      soc = disch_calc_soc(voltage, a, b, c);
      break;
    case CHARGE:
      soc = charge_soc_estim_eq(dod_prev, current, delta_t, cap);
      break;
    case INIT:
      // TODO: put in ryan code 
      break;
  }

  //TODO: control charge state
  
  //show battery soc through LEDs
  LED_indicator(soc, RED20, GREEN40, GREEN60, GREEN80);
}
