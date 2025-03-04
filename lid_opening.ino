#include<Servo.h>
Servo servo;
Servo ESC;
const int _USOutsideTrig = 7;
const int _USOutsideEcho = 8;
const int _SEROutsideSig = 9;
float time = 0;
const int maxTime = 15;
const int _ESCInsideSig = 4;
const int _ESCtrig = 2;
bool BLDCFan = false;
float _USOutsideDur, _USOutsideDist, _USInsideDur, _USInsideDist;
void setup() {
  servo.attach(_SEROutsideSig);//araching the servo
  servo.write(0);
  ESC.attach(_ESCInsideSig);//attaching the ESC for the BLDC
  delay(1);
  ESC.write(10);
  delay(5000);
  pinMode(_USOutsideTrig, OUTPUT);
  pinMode(_USOutsideEcho, INPUT);
  Serial.begin(9600);
}


void servoOpen() {
  time = 0.001;
  servo.write(90);
}

void servoClose() {
  time = 0;
  servo.write(0);
}


void loop() {
  digitalWrite(_USOutsideTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(_USOutsideTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(_USOutsideTrig, LOW);


  _USOutsideDur = pulseIn(_USOutsideEcho, HIGH);
  _USOutsideDist = (_USOutsideDur*.0345)/2;
  delay(100);
 
  if (digitalRead(_ESCtrig)){
    BLDCFan = true;
  }
  else{
    BLDCFan = false;
  }
  if (BLDCFan && (time==0)){
    ESC.write(80);
  }
  else{
    ESC.write(20);
  }
 
  if (_USOutsideDist < 10)
  {
    Serial.print("Opening Lid");
    servoOpen();
  }
  else if (time !=0 ){
    time += 0.5;
  }
  if (time >= maxTime){
    servoClose();
  }
}
