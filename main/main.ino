#include "LED_indicator.h"
#include "find_soc.h"
#include "control_charge.h"
#include "power_interrupts.h"

//STATE DECLARATIONS
bool mains_on, lights_on;

struct fault_states{
  bool no_fault;
  bool overheat;
  bool hydrogen;
  bool overcurrent;
} fault_state;

enum charge_states{
  INIT, 
  CHARGE, 
  DISCHARGE
} charge_state;

//PIN SETUP
#define POW_CONTROL 10

#define RED20 4
#define GREEN40 5
#define GREEN60 6
#define GREEN80 7
#define FAULT_LED 8

#define BATT_VOLT A0
#define BATT_CURR_CH A1
#define BATT_CURR_DIS A2
#define BATT_HYDR A3

#define MAINS_MONITOR 2 //able to use hw interrupt
#define LIGHT_SW 3 //able to use hw interrupt
#define BATT_TEMP 9

//SENSOR VARIABLE DECLARATIONS
double voltage, current;

void setup() {
  pinMode(POW_CONTROL, OUTPUT);
  
  pinMode(RED20, OUTPUT);
  pinMode(GREEN40, OUTPUT);
  pinMode(GREEN60, OUTPUT);
  pinMode(GREEN80, OUTPUT);
  pinMode(FAULT_LED, OUTPUT);

  pinMode(BATT_VOLT, INPUT);
  pinMode(BATT_CURR_CH, INPUT);
  pinMode(BATT_CURR_DIS, INPUT);
  pinMode(BATT_HYDR, INPUT);

  pinMode(MAINS_MONITOR, INPUT);
  attachInterrupt(digitalPinToInterrupt(MAINS_MONITOR), mains_off, FALLING);
  attachInterrupt(digitalPinToInterrupt(MAINS_MONITOR), mains_on, RISING);
  
  pinMode(LIGHT_SW, INPUT);
  attachInterrupt(digitalPinToInterrupt(LIGHT_SW), lamp_toggle, CHANGE); //assuming toggle switch. change to RISING/FALLING if push button
  
  pinMode(BATT_TEMP, INPUT);

  //initialise

  //check mains
  //set light off
  //check faults
  
}

void loop() {
  //update sensor values
  voltage = analogRead(BATT_VOLT);
  current = analogRead(BATT_CURR_CH) - analogRead(BATT_CURR_DIS); // positive means batt charging, negative means batt discharging
  
  //find soc
  find_soc();
  
  //TODO: control charge state

  //update battery soh
  
  //show battery soc through LEDs
  LED_indicator();
}
