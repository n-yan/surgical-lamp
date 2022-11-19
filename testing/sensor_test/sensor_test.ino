struct fault_states{
  bool no_fault;
  bool overheat;
  bool hydrogen;
  bool overcurrent;
  bool discharged;
} fault_state;

//sensor inputs
//#define BATT_VOLT A1
#define BATT_CURR A0
/*
#define BATT_TEMP A2
#define BATT_HYDR A3
//#define LAMP_CURR A4

//hardware interrupts
#define MAINS_MONITOR 2 //able to use hw interrupt
*/
//SENSOR VARIABLE DECLARATIONS
// analogue -> int (need to be scaled)
int volt_raw, curr_raw, temp_raw, hydr_raw, lamp_curr_raw; 
double volt, curr, temp, hydr, lam_curr;
double over_curr, over_temp, over_hydr, min_volt, max_volt, max_charge_volt; //TODO: assign values 

void setup() {
  // put your setup code here, to run once:

  //sensor pins
  //pinMode(BATT_VOLT, INPUT);
  pinMode(BATT_CURR, INPUT);
  /*
  pinMode(BATT_HYDR, INPUT);
  pinMode(BATT_TEMP, INPUT);
  //pinMode(LAMP_CURR, INPUT);


  //interrupt pin
  pinMode(MAINS_MONITOR, INPUT);
*/
  //relay pins
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);

  digitalWrite(0, LOW);
  digitalWrite(1, LOW);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);

  Serial.begin(9600);
}

void loop() {

  /*
  volt_raw = analogRead(BATT_VOLT);
  Serial.print("Raw battery voltage: ");
  Serial.println(volt_raw);
  */

  
  curr_raw = analogRead(BATT_CURR);
  Serial.print("Raw battery current: ");
  Serial.println(curr_raw);

  /*
  Serial.print("Raw battery hydrogen: ");
  Serial.println(BATT_HYDR);

  Serial.print("Raw battery temperature: ");
  Serial.println(BATT_TEMP);

  //Serial.print("Raw lamp current: ");
  //Serial.println(LAMP_CURR);

  Serial.print("Mains connection: ");
  Serial.println(MAINS_MONITOR);

  */

}
