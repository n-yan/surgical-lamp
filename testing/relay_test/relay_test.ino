#include "../../main/power_interrupts.h"
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

//hardware interrupts
#define MAINS_MONITOR 2 //able to use hw interrupt

//relays
#define POW_CONTROL 10
#define SYS_CUTOFF 11
#define BATT_CUTOFF 12
#define CH_CUTOFF 13

//charge_state constants
#define INIT 0
#define DISCHARGE 1
#define CHARGE 2

void setup() {
  // put your setup code here, to run once:

  //interrupt pins
  pinMode(MAINS_MONITOR, INPUT);
  attachInterrupt(digitalPinToInterrupt(MAINS_MONITOR), mains_off, FALLING);
  attachInterrupt(digitalPinToInterrupt(MAINS_MONITOR), mains_on, RISING);

  //relay pins
  pinMode(POW_CONTROL, OUTPUT);
  pinMode(SYS_CUTOFF, OUTPUT);
  pinMode(BATT_CUTOFF, OUTPUT);
  pinMode(CH_CUTOFF, OUTPUT);

  //test as usual state
  //test if hardware interrupt functions by turning mains off/disconnecting pin 2
   states.batt_fault = false;
   states.main_cx = true;
   states.main_on = true;
   states.batt_chgd = true;
   states.sys_fault = false;
   states.calibrating = false;
   states.calibrated = true;
}

void loop() {
   
   relay_control();

  
}

void relay_control() {
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

    //control charging (updates relay CH_CUTOFF)
    control_charge();

  } else {
    //what to do when there is a battery fault?
    //cutoff relay turned off (battery disconnected)
    digitalWrite(BATT_CUTOFF, LOW);

    //turn fault indicating LED on
    digitalWrite(FAULT_LED, HIGH);
  }

}
}
