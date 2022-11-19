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

void setup() {
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

  //update sensor values
  update_sensor_values();

}

/**** RELAY CONTROL ****/
void control_charge() {
  if (states.main_on) {
    digitalWrite(CH_CUTOFF, HIGH);
  } else {
    digitalWrite(CH_CUTOFF, LOW);
  }
}

//turns mains off and switches to battery if there is no battery fault
void mains_off(){
  states.main_on = false;
  //if there is no fault, switch to battery
  if (fault_state.no_fault) {
    digitalWrite(POW_CONTROL, HIGH);
  }
  //if there is a fault, the system should already be turned off. (? check)
}

//turns mains on
void mains_on() {
  states.main_on = true;
  digitalWrite(POW_CONTROL, LOW);
}

/**** SENSOR FUNCTIONS ****/
void fault_check() {
  if (curr > over_curr) {
    fault_state.overcurrent = true;
    Serial.begin(9600);
    Serial.print("Fault: overcurrent. Current is ");
    Serial.print(curr);
    Serial.println(); 
    Serial.end();
  } else {
    fault_state.overcurrent = false;
  }

  if (hydr > over_hydr) {
    fault_state.hydrogen = true;
    Serial.begin(9600);
    Serial.print("Fault: hydrogen detected, battery is overcharged. Amount detected is ");
    Serial.print(hydr);
    Serial.println(); 
    Serial.end();
  } else {
    fault_state.hydrogen = false;
  }

  if (temp > over_temp) {
    fault_state.overheat = true;
    Serial.begin(9600);
    Serial.print("Fault: overheating battery. Temperature is ");
    Serial.print(temp);
    Serial.println(); 
    Serial.end();
  } else {
    fault_state.overheat = false;
  }

  if (volt < min_volt || volt > max_volt) {
    fault-state.discharged = true;
    Serial.begin(9600);
    Serial.print("Fault: battery voltage out of safe operating range. Current voltage is ");
    Serial.print(volt);
    Serial.println(); 
    Serial.end();
  } else {
    fault_state.discharged = false;
  }

  fault_state.no_fault = !(fault_state.overheat & fault_state.hydrogen & fault_state.overcurrent);
  states.batt_fault = fault_state.no_fault;

  // lamp overcurrent check
  if (lamp_curr > over_curr) {
    states.sys_fault = true;
  } else {
    states.sys_fault = false;
  }
}

void update_sensor_values() {
  //update sensor raw values
  volt_raw = analogRead(BATT_VOLT);
  curr_raw = analogRead(BATT_CURR); 
  temp_raw = analogRead(BATT_TEMP);
  hydr_raw = analogRead(BATT_HYDR);
  lamp_curr_raw = analogRead(LAMP_CURR);

  //scale sensor values. i.e. temp_raw -> temp (in degrees C). depends on datasheet/testing
  //arduino adc has a resolution of 10 bits. i.e. 1024 steps from 0-5V

  //voltage <- voltage divider. scale according to resistors
  
  //curr sensor range -37.5A to 37.5A <- change if sensor changes
  curr = curr_raw * 75 * 5/1024 - 75; 

  //temp sensor is thermistor. 

  //hydr sensor <- conductivity rises with increase in combustible gas -> voltage over load resistor rises
  //how to scale????????????????????
  
}
