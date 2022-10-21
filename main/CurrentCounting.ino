double iCoeff[2];  //I = (x-a)/b;
double SOC;
int CALIBRATE_PIN;
int BATTERY_VOLTAGE_PIN;
int I_SENS_PIN;


void loop() {
  if(digitalRead(CALIBRATE_PIN)) {
    //SAVE THIS TO EPROM
    SOC = calibrate();
  }
}

double calibrate() {
  double capacity = 0; // Ah
  double current = 0;  // A
  unsigned long prevTime;
  // 2. Deplete the remaining charge of the battery
  // Light ON
  while((double)analogRead(BATTERY_VOLTAGE_PIN)*15.0/1023.0 > 11.75) {
    //do nothing
  }
  // Light OFF
  // CHARGE ON
  
  while(//LED_FROM_CHARGER != FULL) {
    prevTime = millis();
    current = currentMeasure();
    capacity += current*(millis()-prevTime)*0.001/3600;
  }
  return capacity;
}

double currentMeasure() {
  double currentSum;
  unsigned long prevTime = millis();
  for(int i = 0; i < 10; i++) {
    if(millis() - prevTime > 50) {
      prevTime = millis();
      currentSum += analogRead(I_SENS_PIN) - iCoeff[0])/(iCoeff[1]);
    }
  }
  return currentSum/10.0;
}
