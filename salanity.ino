

#include <KNWRobot.h>
KNWRobot *myRobot;
const int ledGreen = 8;
const int ledRed = 9;
const int buttonPin = A12;
int buttonState;
const int maxVal= 660;
const int minVal= 300;
double adc = 0, previousState = 0;
double mean, resistMeasured, conductVal, salinity;
int turnOn = 1;


void setup() {
  // put your setup code here, to run once:
  myRobot = new KNWRobot;
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
 
  //Button configuration

  //Default value == 0
  
  
  buttonState = digitalRead(buttonPin);
    
  if(previousState == 1 && buttonState == 0 ){

    if(turnOn == 1){

      digitalWrite(ledGreen, HIGH);
      digitalWrite(ledRed, LOW);
  //Average 5 readings of the ACD for the conductivity sensor
  for(int i = 0; i < 5; i++){
    adc += myRobot->getConductivity();
    Serial.println(adc);
    }
  //  ---------------
   //Get Mean
  // ---------------
    mean = adc/5;
    myRobot->clearLine(1);
    Serial.print("mean: ");
    Serial.print(mean);
    Serial.println();
   // -----------------
    //get Resistance
   // -----------------
    resistMeasured = getResistance(mean);
  Serial.print("Resist Measured: ");
  Serial.print(resistMeasured);
  Serial.println();
 // -----------------------
    //Calculate Conductivity
  //  ---------------------
    conductVal = calConduct(resistMeasured);
  Serial.print("conductVal Measured: ");
  Serial.print(conductVal);
  Serial.println();
  //------------------------
      //translate Salinity
 // -----------------------
  salinity = translateSalinity(conductVal);
  Serial.print("Salinity Measured: ");
  Serial.print(salinity);
  Serial.println();
    turnOn = 0;
  }
  else{turnOn = 1;
      digitalWrite(ledRed,HIGH);
       digitalWrite(ledGreen, LOW);}  
  }
  previousState = buttonState;
}
double getResistance (double adc){
  double slope = (475.)/(1023.);
  Serial.println(slope);
  return (slope*adc) + 25.;
  }

double calConduct(double resist){
    double d = 0.8;
    double area = 9.;
    return  d/(area * resist) * 10; 
 }  

double translateSalinity(double conductivity){
  return 0.4665 * pow(conductivity,1.0878);  
  }
  
