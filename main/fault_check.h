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
    Serial.print("Fault: hydrogen detected. Amount detected is ");
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

  if (volt < min_volt) {
    fault-state.discharged = true;
    Serial.begin(9600);
    Serial.print("Fault: discharged battery. Current voltage is ");
    Serial.print(volt);
    Serial.println(); 
    Serial.end();
  } else {
    fault_state.discharged = false;
  }

  fault_state.no_fault = !(fault_state.overheat & fault_state.hydrogen & fault_state.overcurrent);
}
