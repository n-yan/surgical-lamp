#include "LED_indicator.h"
#include "find_soc.h"
#include "control_charge.h"
#include "power_interrupts.h"
#include "sensors.h"

/*   ***STATE DECLARATIONS***   */
struct sys_states {       // USUAL STATE  // DESCRIPTION
  bool batt_fault;        // false        // true if battery has a fault
  bool main_cx;           // true         // true if mains is powering sys vs battery
  volatile bool main_on;  // true         // true if mains is on. volatile -> HW interrupt affects it
  bool batt_chgd;         // true         // true if battery is not fully discharged  
  bool sys_fault;         // false        // true if system/lamp has a fault
  bool calibrating;       // false        // true if battery is calibrating
  bool calibrated;        // true         // true if battery is calibrated
} states;


struct fault_states{
  bool no_fault;
  bool overheat;
  bool hydrogen;
  bool overcurrent;
  bool discharged;
} fault_state;


/*   ***PIN SETUP***   */
//UI
#define RED20 4
#define GREEN40 5
#define GREEN60 6
#define GREEN80 7
#define FAULT_LED 8

//sensor inputs
#define BATT_VOLT A0
#define BATT_CURR A1
#define BATT_TEMP A2
#define BATT_HYDR A3
#define LAMP_CURR A4

//hardware interrupts
#define MAINS_MONITOR 2 //able to use hw interrupt
//#define SYS_MONITOR 3 //able to use hw interrupt

//relays
#define POW_CONTROL 10
#define SYS_CUTOFF 11
#define BATT_CUTOFF 12
#define CH_CUTOFF 13

//charge_state constants
#define INIT 0
#define DISCHARGE 1
#define CHARGE 2

//SENSOR VARIABLE DECLARATIONS
// analogue -> int (need to be scaled)
int volt_raw, curr_raw, temp_raw, hydr_raw, lamp_curr_raw; 
double volt, curr, temp, hydr, lam_curr;
double over_curr, over_temp, over_hydr, min_volt, max_volt, max_charge_volt; //TODO: assign values 

//define dod and soc somehow. probably from find_soc > init
double soc, dod, cap;
unsigned long prev_t = 0;
int charge_state; //initialise charge_state

void setup() {
  //UI pins
  pinMode(RED20, OUTPUT);
  pinMode(GREEN40, OUTPUT);
  pinMode(GREEN60, OUTPUT);
  pinMode(GREEN80, OUTPUT);
  pinMode(FAULT_LED, OUTPUT);

  //sensor pins
  pinMode(BATT_VOLT, INPUT);
  pinMode(BATT_CURR, INPUT);
  pinMode(BATT_HYDR, INPUT);
  pinMode(BATT_TEMP, INPUT);
  pinMode(LAMP_CURR, INPUT);


  //interrupt pins
  pinMode(MAINS_MONITOR, INPUT);
  attachInterrupt(digitalPinToInterrupt(MAINS_MONITOR), mains_off, FALLING);
  attachInterrupt(digitalPinToInterrupt(MAINS_MONITOR), mains_on, RISING);

  //relay pins
  pinMode(POW_CONTROL, OUTPUT);
  pinMode(SYS_CUTOFF, OUTPUT);
  pinMode(BATT_CUTOFF, OUTPUT);
  pinMode(CH_CUTOFF, OUTPUT);
  

  //Initialising sequence - REWRITE WHOLE THING
  // power on autocutoff relay initially
  // update sensor values
  // check mains
  // set light off
  // set charge state to init
  
  digitalWrite(CUTOFF, HIGH); //WHAT DOES THIS MEAN??
  update_sensor_values();
  if (digitalRead(MAINS_MONITOR) == ON) {
    mains_on();
  } else {
    mains_off();
  }

  //REMOVE THIS - CONTROLLED BY EXT SWITCH
  digitalWrite(LIGHT_OUT, LOW);

  charge_state = INIT;
}

void loop() {

  //fault check. updates batt_fault and sys_fault states
  fault_check();

  // disconnects lamp if there is a lamp fault
  if (!states.sys_fault) {
    digitalWrite(SYS_CUTOFF, HIGH);
  } else {
    digitalWrite(SYS_CUTOFF, LOW);
  }
     
  if (!states.batt_fault) {
    //turn cutoff relay on (battery is connected)
    digitalWrite(BATT_CUTOFF, HIGH);

    //turn fault indicating LED off
    digitalWrite(FAULT_LED, LOW);

    //find soc
    find_soc();
    
    //control charging (updates relay CH_CUTOFF)
    control_charge();
  
    //update battery soh (if we get to it)

  } else {
    //what to do when there is a battery fault?
    //cutoff relay turned off (battery disconnected)
    digitalWrite(BATT_CUTOFF, LOW);

    //turn fault indicating LED on
    digitalWrite(FAULT_LED, HIGH);
  }
  
  //show battery soc through LEDs
  LED_indicator();

  //update sensor values
  update_sensor_values();
}
