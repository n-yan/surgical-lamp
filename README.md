## TODO:
- Write testing code
  - Write code testing physical functions
    - relay switching at desired logic changes
    - sensor behaviour as expected
    - combine above two
    - SoC tracking works
    - initialisation test
    - full integrated test
  - Convert current code to function? (headache)
  - Write black box tests validating logic - not in Arduino (headache)
- Consider system states and triage them. > sort of done? for normal states
  - Also, try figure out what state transitions require special considerations
  - Start rewriting the code
    - rewrite initialising sequence
    - update finding soc
    - add more logic
    - change to LCD from LED UI
- Integrate LCD UI
  - Update pin mappings, i.e. change LED digital output opins to LCD

- sensor raw readings -> readable information (from datasheets or testing)
  - test hydr and temp sensor
  - get voltage divider info for voltage
- Solve arduino power-up/boot-up time issue (flash Optiboot onto arduino for no-delay boot)
  - investigate further -> Optiboot v4.4 vs newest
  - bring in 2 arduinos (one of them to use as ISP)

## Lower priority TODO: 
- LCD UI
- Ryan discharge curve generation
- Update battery soh 
- Battery initial setup for a separate modular system (??)

## Done:
- Thermistor and hydrogen sensor how to implement
- remove 2nd hw interrupt
- updated fault check and control charge
- update power interrupt
- update pin mappings
- create system boolean states
- LED indication
- Look at using interrrupts to integrate code after individual units are complete
- Clean up code – segregate sections into different files? 
- From din3 (temp) and ain3 (hydrogen sensor) 
- Finish light_toggle fn
- Turn on/off lights depending on switch (din2)
- Check if mains is on (DIN1 voltage sensor)> if off switch relay (d01) 
- Current sensor (for soc etc) (ain2) 
- Autocutoff? 
- Finish SOC updating (convert to using global vars)
- Find/control charge state (no longer complicated due to OTS charger)

## SYSTEM BOOLEAN STATES
| State name | Usual state | Description |
| ------------- | ------------- | -------------- |
| batt_fault | false | true if battery has a fault |
| main_cx | true | true if mains is powering sys vs battery |
| main_on | true | true if mains is on |
| batt_chgd | true | true if battery is not fully discharged |
| sys_fault | false | true if system/lamp has a fault |
| calibrating | false | true if battery is calibrating |
| calibrated | true | true if battery is calibrated |

## PIN MAPPINGS
The red/green/fault LED pin mappings will be replaced with LCD pins (6).  

Digital pins utilised: 11/14  

Analog pins utilised: 5/6  

Note analog pins can be used as digital pins if needed.

| Description | Overview pin | Arduino pin |
| ------------- | ------------- | -------------- |
| RED20 – red LED (batt indicator)  **output** | DO4 | 4 |
| GREEN40 – green LED (batt indicator) **output** | DO5 | 5 | 
| GREEN60 – green LED (batt indicator)  **output** | DO6  | 6 | 
| GREEN80 – green LED (batt indicator) **output** | DO7  | 7 |
| FAULT_LED – yellow LED (batt indicator) **output** | DO9(?) | 8 |
| -- | -- | -- |
| BATT_VOLT - voltmeter (autocutoff) **input** | AIN2 | A0 |
| BATT_CURR - current sensor (bidirectional) **input** | AIN1 | A1 |
| BATT_TEMP - is actually analogue **input** | DIN3 | A2 |
| BATT_HYDR - hydrogen sensor (monitors for battery fault) **input** | AIN3 | A3 |
| LAMP_CURR - current sensor **input** | AIN4 | A4 |
| -- | -- | -- |
| MAINS_MONITOR - monitors mains voltage **input** | DIN1 | 2 | <-- uses pin 2 for hardware interrupt
| ? **input** | ? | 3 | <-- uses pin 3 for hardware interrupt
| -- | -- | -- |
| POW_CONTROL - controls where lamp pulls power **output** | D01/relay L | 10 |
| SYS_CUTOFF - controls system/lamp cutoff relay **output** | relay M | 11 | 
| BATT_CUTOFF - controls battery cutoff relay **output** | relay B | 12 |
| CH_CUTOFF - controls if battery is charging from mains **output** | relay C | 13 | 
