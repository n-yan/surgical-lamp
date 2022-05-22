// Establishing Variables
int curTempAvg[10];
int pastTempAvg[15]; //Celsius
bool hydrogen = false; 
bool tempIncreasing = false;

unsigned long prev10s;
unsigned long prevMin;
unsigned long lampOnTime;


int voltStep = 14000;   // mV
int currents[201];      // mA
int times[201];         // s
double SOCs[100];
int effectiveCapacity;  // mAh

double coefficients[3]; //V = ax^2 + bx + c where x is SOC 

//Temperature
// avg from 35-25min,25-18min,18-12min,12-7min,7-3min,3-1min,1min-30s,temp now
void setup() {
// Define Battery Characteristics
  /* Process: 
    1. Max charge the battery at 14V 3A, move on when temp increases concavely or if hydrogen is present

    2. Power the lamp - measuring current and the time at set voltage margins
    3. Calculate effective capacity of the battery and the coefficients which determine its discharge curve. Save in EPROM
  */

  /* Pseudocode
    // set ins and outs
    Digital 1 set to output (charge)
    Digital 2 set to input (hydrogen)
    Analogue 1 set to inout (temperature)

    Digital One ON

    // Record Temp while dtemp^2/d^2time < 0
    while (tempNotRising and noHydrogenPresent) {
      if (millis()-prev10s > 6000) {
        for (int i = 9; i>=1; i--) {
          curTemp[i] = curTempAvg[i-1]
        }
        curTemp[0] = tempNow;
        hydrogen = Digital In pin 2
      }

      if (millis()-prevMin > 60000) {
        for (int i = 14; i >=1 ; i--) {
          prevTempAvg[i] = prevTempAvg[i-1]
        }
        prevTempAvg[0] = sum(curTemps);

         //See if the temp has an ascending curve
        take the first point:
        c = prevTempAvg[0]

        take the last equaton for heavier weighting:
        t[14] = 14^2a + 14b + c; therefore b = (t[14]-14^2a-c)/14

        take the sum of all the other errors
        for(int i = 1; i <= 13; i++) {
          sumTemps = sumTemps + prevTempAvg[i];
        }

        and use simultaneous eqns work to determine coefficient of a
        a = (sumTemps-((17/2)*c)-((91/14)*prevTempAvg[14])/(-455)
      
        if (a>3/255) {
          tempIncreasing = true;
        }
      }    

      //Step 2:
      Digital 1 OFF

      Lamp ON
      lampOnTime = millis();
      //Replace this
      delay(600000);
      int counter = 0;
      while (voltStep > VoltageBattery) {
        voltStep = voltStep - 10;
        counter++;
      }

      while (voltStep >= 12000) {
        if (voltStep > voltageBattery) {
          times[((14000-voltStep)/10)-counter] = millis()-lampOnTime;
          current[((14000-voltStep)/10)-counter] = curDraw (which is AnalogueIn2)
          voltStep = voltStep - 10;
        }
      }

      Lamp ON via Mains

      // Step 3: Calculate Battery Deets
      effectiveCapacity = current[0]*time[0];
      for (int i = 1; i < (201-counter); i++) {
        effectiveCapacity = effectiveCapacity + (times[i]-times[i-1])*currents[i];
      }

      // SOCs for each voltage step
      SOC[0] = 100;
      for (int i = 1 ; i < (201-counter); i++) {
        SOC[i] = (effectiveCapacity - ((times[i]-times[i-1])*currents[i]))/effectiveCapacity;
      }

      // Least squares approach to second order model for the discharge curve
      //Calculate Sums
      double sumsX = 0;
      double sumsX2 = 0;
      double sumsX3 = 0;
      double sumsX4 = 0;
      double sumsY = 0;
      double sumsXY = 0;
      double sumsX2y = 0;
      int n = (201-counter)

      for (int i = 0; i < (201-counter); i++) {
        sumsX = sumsX + SOC[i];
        sumsX2 = sumsX2 + SOC[i]^2;
        sumsX3 = sumsX3 + SOC[i]^3;
        sumsX4 = sumsX4 + SOC[i]^4;
        sumsY = sumsY + (14-(0.01*(counter+i)));
        sumsXY = sumsXY + SOC[i]*(14-(0.01*(counter+i)));
        sumsX2y = sumsX2Y + (SOC[i]^2)*(14-(0.01*(counter+i)));
      }
      
      // x is SOC, y is voltages
      Det = 
      sumsX4*(n*sumx^2 - (sumx)^2) - sumx^3*(n*sumx^3 - (sumx^2*sumx)) + sumx^2*(sumx^3*sumx - (sumx^2)^2)

      A = sum(X^2y)*(n*sumx2-(sumX)^2) - sum(x^3)*(n*sum(xy)-(sumX*sumY)) + sumx^2*(sumx*sumxy - (sumx^2*sumy))/DET

      B = sumx^4*(n*sumxy - sumxsumy) - sum(x^2y)*(n*sumx^3 - sumx^2*sumx) + sumx^2*(sumx^3*sumy - sumx^2*sumxy)/DET

      C = sumx^4*(sumx^2*sumy - sumxy*sumx) - sumx^3*(sumx^3*sumy - sumxy*sumx^2) + sumx^2y*(sumx^3*sumx - (sumx^2)^2)/ DET

      
    }
*/

}

void loop() {
  // put your main code here, to run repeatedly:

}
