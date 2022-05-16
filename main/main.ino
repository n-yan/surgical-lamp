#include "LED_indicator.h"
#include "find_soc.h"
#include "control_charge.h"

//PIN SETUP
#define RED20 4
#define GREEN40 5
#define GREEN60 6
#define GREEN80 7
#define FAULT_LED 8

#define BATT_VOLT A0
#define BATT_CURR_CH A1
#define BATT_CURR_DIS A2
#define BATT_HYDR A3

//variables
double voltage, current;

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

  pinMode(BATT_VOLT, INPUT);
  pinMode(BATT_CURR_CH, INPUT);
  pinMode(BATT_CURR_DIS, INPUT);
  pinMode(BATT_HYDR, INPUT);

}

void loop() {
  //update sensor values
  voltage = analogRead(BATT_VOLT);
  current = analogRead(BATT_CURR_CH) - analogRead(BATT_CURR_DIS); // positive means batt charging, negative means batt discharging
  
  
  
  //find soc
  switch(ch_state) {
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
  //TODO: control charge state

  //update battery soh
  
  //show battery soc through LEDs
  LED_indicator(soc, RED20, GREEN40, GREEN60, GREEN80);
}
