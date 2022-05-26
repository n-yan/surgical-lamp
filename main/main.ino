#include "LED_indicator.h"
#include "find_soc.h"
#include "control_charge.h"
#include "power_interrupts.h"
#include "sensors.h"

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
// these variables aren't really used but keep for now. re-evaluate if needed
volatile bool mains_on_state, lights_on_state;

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
double over_curr, over_temp, over_hydr, min_volt, max_volt, max_charge_volt; //TODO: assign values 

//define dod somehow. probably from find_soc > init
double soc, dod, cap;
unsigned long prev_t = 0;

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
  attachInterrupt(digitalPinToInterrupt(LIGHT_SW), lamp_toggle, RISING); //assuming push button. change if toggle switch

  pinMode(CUTOFF, OUTPUT);
  

  //Initialising sequence
  // power on autocutoff relay initially
  // update sensor values
  // check mains
  // set light off
  // set charge state to init
  
  digitalWrite(CUTOFF, HIGH);
  update_sensor_values();
  if (digitalRead(MAINS_MONITOR) == ON) {
    mains_on();
  } else {
    mains_off();
  }

  digitalWrite(LIGHT_OUT, LOW);

  charge_state = INIT;
}

void loop() {

  //fault check. if you find a better way to do this (i.e. w/an interrupt?) replace
  fault_check();
   
  if (fault_state.no_fault) {
    //turn cutoff relay on (battery is connected)
    digitalWrite(CUTOFF, HIGH);

    //turn fault indicating LED off
    digitalWrite(FAULT_LED, LOW);
  
    //find soc
    find_soc();
    
    //control charge state
    control_charge();
  
    //update battery soh (if we get to it)

  } else {
    //what to do when there is a battery fault?
    //cutoff relay turned off (battery disconnected)
    digitalWrite(CUTOFF, LOW);

    //turn fault indicating LED on
    digitalWrite(FAULT_LED, HIGH);
  }
  
  //show battery soc through LEDs
  LED_indicator();

  //update sensor values
  update_sensor_values();
}
