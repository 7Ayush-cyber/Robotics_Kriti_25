#include<Servo.h>


Servo ESC;
int speed;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ESC.attach(9);
  delay(1);
  ESC.write(10);
  delay(5000);
}


void loop() {
//   put your main code here, to run repeatedly:
  while(Serial.available() > 0)
  {
    speed = Serial.parseInt();
    Serial.println(speed);
    ESC.write(speed);//45 limit
  }
}
