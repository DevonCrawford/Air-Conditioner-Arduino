#include <LiquidCrystal.h>
#include<math.h>

// Initialize lcd library with numbers of interface pins
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

/* Initializing io pins on arduino */
int tempSensor1 = A0;
int tempSensor2 = A1;
int dDown = 2;
int dUp = 3;
int jcDown = 4;
int jcUp = 5;
int hubFan = A5;
int cjFans = A4;
int devFans = 6;

/* Declaring/Initializing variables */
double tmp1Data[8], tmp2Data[8];
double tmp1Avg = 0.0;
double tmp2Avg = 0.0;
double celsius1 = 0.0; 
double celsius2 = 0.0;
int i1 = 0;
int i2 = 0;
int setTemp1 = 0;
int setTemp2 = 0;

/* Declaring functions */
double getTemp (int sensor);
void printLCD (int celsius1, int setTemp1, int celsius2, int setTemp2);
int avgTemp(double *avg, int *i, double data[8], int celsius);

void setup() {
  Serial.begin(9600);

  /* Initialize io pins */
  pinMode(tempSensor1, INPUT);
  pinMode(tempSensor2, INPUT);
  pinMode(hubFan, OUTPUT);
  pinMode(devFans, OUTPUT);
  pinMode(cjFans, OUTPUT);

  /* Initialize LCD display */
  lcd.begin(16, 2);
  lcd.setCursor(15, 0);
  lcd.print("D");
  lcd.setCursor(14, 1);
  lcd.print("CJ");

  /* Set default room temperatures */
  setTemp1 = 20;
  setTemp2 = 20;
}

void loop() {
  /* Handles pushbutton presses
    changes temperature setting for Devon */
  if (digitalRead(dDown)) {
    setTemp1--;
  }
  if (digitalRead(dUp)) {
    setTemp1++;
  }

  /* Changes temperature setting for Justin and Cameron */
  if (digitalRead(jcDown)) {
    setTemp2--;
  }
  if (digitalRead(jcUp)) {
    setTemp2++;
  }

  /* Get temperature reading from both rooms */
  celsius1 = getTemp (tempSensor1);
  celsius2 = getTemp (tempSensor2);

  /* Calculate (tick) average temperatures for each sensor, removes noise */
  avgTemp(&tmp1Avg, &i1, tmp1Data, celsius1);
  avgTemp(&tmp2Avg, &i2, tmp2Data, celsius2); 

  /* Prints average temperatures to display */
  printLCD(tmp1Avg, setTemp1, tmp2Avg, setTemp2);

  /* If either room is too hot, turn on hub fan */
  if((tmp1Avg >= setTemp1) || (tmp2Avg >= setTemp2)) {
    analogWrite(hubFan, 1023);
  }
  else {
    analogWrite(hubFan, 0);
  }
  
  /* Turn on individual room fans based on room temperature */
  if(tmp1Avg >= setTemp1) {
     digitalWrite(devFans, HIGH);
  }
  else {
    digitalWrite(devFans, LOW);
  }
  if(tmp2Avg >= setTemp2) {
     analogWrite(cjFans, 1023);
  }
  else {
    analogWrite(cjFans, 0);
  }

  /* loop updates twice per second */
  delay(500);
}

/* Calculates average of 8 readings to filter out noise */
int avgTemp(double *avg, int *i, double data[8], double celsius) {
  if((*i) > 7) {
    *avg = 0.0;
    /* Takes the average of 8 temperature readings (over 4 seconds) */
    for(int j = 0; j < 8; j++) {
      (*avg) += data[j];
      Serial.println(data[j]);
    }
    *avg /= 8;
    *avg = round(*avg);
    *i = 0;
  }
  /* Difference from current reading and the average */
  double off1 = (*avg) - celsius;
  
  /* Record 8 temperature readings (ticks) determined time by loop */
  if(*avg == 0) {
    data[*i] = (double)celsius;
    (*i)++;
  }
  /* Discard innaccurate temperature reading from data */
  else if((off1 > -5) && (off1 < 5)) {
    data[*i] = (double)celsius;
    (*i)++;
  }
}

/* Less noisy analog read */
int advancedAnalogRead(int s) {
  analogRead(s); // dummy read to switch ADC to new sensor
  delay(10); // give the ADC time to settle
  return analogRead(s);
}

/* Get analog temperature reading, calculate to celsius */
double getTemp (int sensor) {
  double volts = ((double)advancedAnalogRead(sensor) / 1024) * 5000;
  double celsius = (volts - 500) / 10;
  return celsius;
}

/* Prints temperature data in specified layout on LCD display */
void printLCD (int celsius1, int setTemp1, int celsius2, int setTemp2) {
  lcd.setCursor(0, 0);
  lcd.print((int)celsius1);
  lcd.print("C");
  lcd.print(" Set [ ");
  lcd.print(setTemp1);
  lcd.print(" ]");

  lcd.setCursor(0, 1);
  lcd.print((int)celsius2);
  lcd.print("C");
  lcd.print(" Set [ ");
  lcd.print(setTemp2);
  lcd.print(" ]");
}



