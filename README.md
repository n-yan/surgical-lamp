## TODO:
- sensor raw readings -> readable information (from datasheets or testing)
  - test hydr and temp sensor
  - get voltage divider info for voltage
- Solve arduino power-up/boot-up time issue (flash Optiboot onto arduino for no-delay boot)
  - investigate further -> Optiboot v4.4 vs newest
  - bring in 2 arduinos (one of them to use as ISP)
- Consider system states and triage them.
  - Also, try figure out what state transitions require special considerations

## Lower priority TODO: 
- LCD UI
- Ryan discharge curve generation
- Update battery soh 
- Battery initial setup for a separate modular system (??)

## Done:
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

## STATES
- RELAY (AUTOCUTOFF) ON/OFF // BATTERY FAULT/NO FAULT
- RELAY (MAINS/BATTERY) ON/OFF 
- MAINS ON/OFF
- BATTERY CHARGED/DISCHARGED
- LIGHT ON/OFF
- CALIBRATING/NOT CALIBRATING
- CALIBRATED/NOT CALIBRATED

## PIN MAPPINGS
The red/green/fault LED pin mappings will be replaced with LCD pins (6).  

Digital pins utilised: 11/14  

Analog pins utilised: 4/6  

Note analog pins can be used as digital pins if needed.

| Description | Overview pin | Arduino pin |
| ------------- | ------------- | -------------- |
| RED20 – red LED (batt indicator)  **output** | DO4 | 4 |
| GREEN40 – green LED (batt indicator) **output** | DO5 | 5 | 
| GREEN60 – green LED (batt indicator)  **output** | DO6  | 6 | 
| GREEN80 – green LED (batt indicator) **output** | DO7  | 7 |
| FAULT_LED – yellow LED (batt indicator) **output** | DO9(?) | 8 |
| -- | -- | -- |
| BATT_VOLT - voltmeter (autocutoff) **input** | AIN1 | A0 |
| BATT_CURR - current sensor (bidirectional) **input** | AIN2 | A1 |
| BATT_TEMP - is actually analogue **input** | DIN3 | A2 |
| BATT_HYDR - hydrogen sensor (monitors for battery fault) **input** | AIN3 | A3 |
| -- | -- | -- |
| MAINS_MONITOR - monitors mains voltage **input** | DIN1 | 2 | <-- uses pin 2 for hardware interrupt
| LIGHT_SW - light switch **input** | DIN2 | 3 | <-- uses pin 3 for hardware interrupt
| LIGHT_OUT - controls lamp **output** | -- | 11 | 
| POW_CONTROL - controls where lamp pulls power **output** | DO1 | 10 |
| CUTOFF - controls battery cutoff relay **output** | -- | 12 |
