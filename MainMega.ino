#include<Servo.h>
#include <Arduino.h>

Servo servo;
Servo ESC;

bool isOpen = false;
bool escbool = false;
float time = 0;
const int maxTime = 7;

const int minlvl = 10;
const int sealLoop = 42;
const int pushLoop = 37;

//Part 3 Definition
int lidUltrasonicTrig = 22;
int lidUltrasonicEcho = 23;
int lvlUltrasonicTrig = 24;
int lvlUltrasonicEcho = 25;
int mq3Sensor = 26;
int mq4Sensor = 27;
int relayPin = 28;
int ESCsignal = 29;

int ESCpin = 30;
int lidServo = 53;
int sealingStepperStep = 2;
int sealingStepperDir = 5;
int sealingStepperEnable = 8;
int pushingStepperStep = 3;
int pushingStepperDir = 6;
int pushingStepperEnable = 9;

void servoOpen() {
  time = 0.001;
  Serial.println("Opening the Lid");
  if (!isOpen){
    servo.write(80); // to run continuous Servo Motor <90 pwm runs the motor Clockwise; 0 = max speed
    delay(450);// time delay enough to open the lid 70
    servo.write(90); // 90 pwm to stop the motor
    isOpen = true;
  }
}

void servoClose() {
  time = 0;
  servo.write(100);// >90 pwm to run the motor anticlockwise; 180 = max speed
  delay(450);
  servo.write(90);
  isOpen = false;
}

void runSensors(){
  int alc = digitalRead(mq3Sensor);
  int met = digitalRead(mq4Sensor);
  if (alc > 440){
    //light LED
  }
}

float getDist(int Trig,int Echo){
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  float dur = pulseIn(Echo, HIGH);
  float dist = (dur*0.0345) / 2;
  return dist;
}

void runStepper(int step, int distance)
{
  for (int i = 0; i < distance * 200; i++) { // 200 steps per revolution; Number of Revolutions to be calulated
            digitalWrite(step, HIGH);
            delayMicroseconds(1000); // Adjust speed by changing the delay
            digitalWrite(step, LOW);
            delayMicroseconds(1000);
        }
}

void nichrome(){
  Serial.println("Object detected within 20 cm! Turning on relay for 5 seconds.");
  digitalWrite(relayPin, LOW); // Active low signal 
  delay(5000);
  digitalWrite(relayPin, HIGH); // Turn off the relay after 5 seconds
}

void setup() {
  Serial.begin(9600);
  servo.attach(lidServo);//attaching the servo
  servo.write(90);
  pinMode(lidUltrasonicTrig, OUTPUT);
  pinMode(lidUltrasonicEcho, INPUT);
  pinMode(lvlUltrasonicTrig, OUTPUT);
  pinMode(lvlUltrasonicEcho, INPUT);
  pinMode(mq3Sensor, INPUT);
  pinMode(mq4Sensor, INPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH); // Turn off relay initially
  pinMode(sealingStepperStep, OUTPUT);
  pinMode(pushingStepperDir, OUTPUT);
  pinMode(sealingStepperEnable, OUTPUT);
  digitalWrite(sealingStepperEnable, LOW);
  digitalWrite(pushingStepperDir, LOW);
  pinMode(ESCsignal, INPUT);
  ESC.attach(ESCpin);
  delay(1);
  ESC.write(20);
  delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:
  float dist = getDist(lidUltrasonicTrig, lidUltrasonicEcho);
  
  if (dist < 10){
    runSensors();
    servoOpen();
  }
  else if (time !=0 ){
    time += 0.5;
  }
  if (time >= maxTime){
    servoClose();
  }
  float lvlDist = getDist(lvlUltrasonicTrig, lvlUltrasonicEcho);
  if ((lvlDist<22) && (!isOpen) && lvlDist>0){
    Serial.println(lvlDist);
    Serial.print("rine");
    runStepper(sealingStepperStep,sealLoop);
    digitalWrite(relayPin, LOW);
    delay(20000);
    digitalWrite(sealingStepperDir, !digitalRead(sealingStepperDir));
    digitalWrite(relayPin, HIGH);
    runStepper(sealingStepperStep, sealLoop);
    digitalWrite(sealingStepperDir, !digitalRead(sealingStepperDir));
    delay(10000);
    //run relay
    //push
    Serial.println("Running Lower Motor");
    runStepper(pushingStepperStep, pushLoop);
    delay(1000);
    digitalWrite(pushingStepperDir, !digitalRead(pushingStepperDir));
    runStepper(pushingStepperStep, pushLoop);
    digitalWrite(pushingStepperDir, !digitalRead(pushingStepperDir));
    delay(1000);
    Serial.print("RUNNING ESC");
    escbool = false;
  }
  else{
    //Serial.println("No object detected within 20 cm.");
    digitalWrite(relayPin, HIGH); // Turn off the relay
  }
  if (escbool)
  {
    Serial.print("RUNNING ESC");
    delay(7500);
    ESC.write(80);
    delay(6 * 1000);// run fan for 6 secs
    escbool = true;
  }
  else
  {
    ESC.write(20);
  }
}