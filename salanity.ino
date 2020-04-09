

#include <KNWRobot.h>
KNWRobot *myRobot;
const int ledGreen = 8;
const int ledRed = 9;
const int buttonPin = A12;
int buttonState;
double adc = 0, previousState = 0;
double mean, salinity;
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
   // -----------------Salinity---------
    display(translateSalinity(mean));
    turnOn = 0;
  }
  else{turnOn = 1;
      digitalWrite(ledRed,HIGH);
       digitalWrite(ledGreen, LOW);}  
  }
  previousState = buttonState;
  adc = 0;
}

void display(double percent){
   Serial.print("Salinity: ");  
   Serial.print((translateSalinity(mean)));
   Serial.println();  
  }
double translateSalinity(double adc){
  //Give back the percent of salinity
  return abs(26.44/(adc-326.61));
  }
  
