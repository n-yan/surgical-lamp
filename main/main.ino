#include "LED_indicator.h"
#include "find_soc.h"
#include "control_charge.h"
#include "power_interrupts.h"

//STATE DECLARATIONS
struct fault_states{
  bool no_fault;
  bool overheat;
  bool hydrogen;
  bool overcurrent;
  bool discharged;
} fault_state;

enum charge_states{
  INIT, 
  CHARGE, 
  DISCHARGE
} charge_state;

// set by digital interrupt pins -> HIGH/LOW -> convert to bool.
volatile bool mains_on, lights_on;

//PIN SETUP
#define POW_CONTROL 10
#define CUTOFF 12

#define RED20 4
#define GREEN40 5
#define GREEN60 6
#define GREEN80 7
#define FAULT_LED 8

//inputs
#define BATT_VOLT A0
#define BATT_CURR A1
#define BATT_TEMP A2
#define BATT_HYDR A3

#define MAINS_MONITOR 2 //able to use hw interrupt
#define LIGHT_SW 3 //able to use hw interrupt

#define LIGHT_OUT 11

//SENSOR VARIABLE DECLARATIONS
// analogue -> int (need to be scaled)
int volt_raw, curr_raw, temp_raw, hydr_raw; 
double volt, curr, temp, hydr;
double over_curr, over_temp, over_hydr, min_volt; //TODO: assign values 

double soc;

void setup() {
  pinMode(RED20, OUTPUT);
  pinMode(GREEN40, OUTPUT);
  pinMode(GREEN60, OUTPUT);
  pinMode(GREEN80, OUTPUT);
  pinMode(FAULT_LED, OUTPUT);

  pinMode(BATT_VOLT, INPUT);
  pinMode(BATT_CURR, INPUT);
  pinMode(BATT_HYDR, INPUT);
  pinMode(BATT_TEMP, INPUT);

  pinMode(POW_CONTROL, OUTPUT);
  pinMode(MAINS_MONITOR, INPUT);
  attachInterrupt(digitalPinToInterrupt(MAINS_MONITOR), mains_off, FALLING);
  attachInterrupt(digitalPinToInterrupt(MAINS_MONITOR), mains_on, RISING);

  pinMode(LIGHT_OUT, OUTPUT);
  pinMode(LIGHT_SW, INPUT);
  attachInterrupt(digitalPinToInterrupt(LIGHT_SW), lamp_toggle, CHANGE); //assuming toggle switch. change to RISING/FALLING if push button

  pinMode(CUTOFF, OUTPUT);
  

  //initialise

  //power on autocutoff relay initially
  //check mains
  //set light off
  //check faults
  
}

void loop() {
  //update sensor raw values
  volt_raw = analogRead(BATT_VOLT);
  curr_raw = analogRead(BATT_CURR); 
  temp_raw = analogRead(BATT_TEMP);
  hydr_raw = analogRead(BATT_HYDR);

  //scale sensor values. i.e. temp_raw -> temp (in degrees C)

  //fault check. if you find a better way to do this (i.e. w/an interrupt?) replace
  fault_check();
  
  if (fault_state.no_fault) {
  
    //update power/mains based on present state
    if (mains_on) {
      digitalWrite(POW_CONTROL, HIGH);
    }
  
    //find soc
    find_soc();
    
    //TODO: control charge state
  
    //update battery soh (if we get to it)

  } else {
    //what to do when there is a fault?
  }
  
  //show battery soc through LEDs
  LED_indicator();
}
