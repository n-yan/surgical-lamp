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
