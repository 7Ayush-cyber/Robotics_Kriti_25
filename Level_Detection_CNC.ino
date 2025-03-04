#define TRIG_PIN 30
#define ECHO_PIN 28
#define LED_33 26
#define LED_66 24
#define LED_FULL 22
#define NICHROME 32
#define X_STEP_PIN 2  // Pin for step signal (X-axis)
#define X_DIR_PIN 5   // Pin for direction signal (X-axis)
#define X_ENABLE_PIN 8 // Pin to enable/disable the motor
int dist = 5;
bool run = false;
void setup() {
  pinMode(X_STEP_PIN, OUTPUT);
  pinMode(X_DIR_PIN, OUTPUT);
  pinMode(X_ENABLE_PIN, OUTPUT); // Enable the motor (LOW to enable)
  digitalWrite(X_ENABLE_PIN, LOW); // Set direction of rotation
  digitalWrite(X_DIR_PIN, HIGH); // HIGH for one direction, LOW for the other
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_33, OUTPUT);
  pinMode(LED_66, OUTPUT);
  pinMode(LED_FULL, OUTPUT);
  pinMode(NICHROME, OUTPUT);
  Serial.begin(9600);
}
long getDistance() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    long duration = pulseIn(ECHO_PIN, HIGH);
    long distance = duration * 0.034 / 2;  // Convert to cm
    return distance;
}


void runStepper(int distance)
{
  for (int i = 0; i < distance * 200; i++) { // Assuming 200 steps per revolution
            digitalWrite(X_STEP_PIN, HIGH);
            delayMicroseconds(1000); // Adjust speed by changing the delay
            digitalWrite(X_STEP_PIN, LOW);
            delayMicroseconds(1000);
        }
}


void loop() {
    long distance = getDistance();


    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");


    // Turn on LEDs based on distance thresholds
    if(distance !=0){
      digitalWrite(LED_33, (distance <= 37) ? HIGH : LOW);
      digitalWrite(LED_66, (distance <= 29) ? HIGH : LOW);
      digitalWrite(LED_FULL, (distance <= 20) ? HIGH : LOW);
    }


    if ((distance < 20)&& (distance !=0)) {
        run = true;
        runStepper(dist);
        digitalWrite(NICHROME, HIGH);
        delay(10000);
        digitalWrite(X_DIR_PIN, !digitalRead(X_DIR_PIN));
        digitalWrite(NICHROME, LOW);
        runStepper(dist);
        digitalWrite(X_DIR_PIN, !digitalRead(X_DIR_PIN));
    }
}
