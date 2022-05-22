## What does the code need to do: 
- Ryan discharge curve generation 
- Find, update soc 
- Check if mains is on (DIN1 voltage sensor)> if off switch relay (d01) 
- Update battery soh
- From din3 (temp) and ain3 (hydrogen sensor) 
- Turn on/off lights depending on switch (din2)
- Autocutoff?  
- Current sensor (for soc etc) (ain2) 
- Find charge state 

- Clean up code – segregate sections into different files? 
- Look at using interrrupts to integrate code after individual units are complete

## Done:
- LED indication


## PIN MAPPINGS
| Description | Overview pin | Arduino pin |
| ------------- | ------------- | -------------- |
| POW_CONTROL - controls where lamp pulls power | DO1 | 10 |
| RED20 – red LED (batt indicator)  | DO4 | 4 |
| GREEN40 – green LED (batt indicator)  | DO5 | 5 | 
| GREEN60 – green LED (batt indicator) | DO6  | 6 | 
| GREEN80 – green LED (batt indicator) | DO7  | 7 |
| FAULT_LED – yellow LED (batt indicator) | DO9(?) | 8 |
| BATT_VOLT - voltmeter (autocutoff) | AIN1 | A0 |
| BATT_CURR - current sensor (bidirectional) | AIN2 | A1 |
| BATT_TEMP - is actually analogue | DIN3 | A2 |
| BATT_HYDR - hydrogen sensor (monitors for battery fault) | AIN3 | A3 |
| MAINS_MONITOR - monitors mains voltage | DIN1 | 2 | <-- uses pin 2 for hardware interrupt
| LIGHT_SW - light switch input | DIN2 | 3 | <-- uses pin 3 for hardware interrupt
| LIGHT_OUT - controls lamp output | -- | 11 | 
| CUTOFF - controls cutoff relay | -- | 12 |


May add input and output pins for an extra relay (kill switch for battery)

