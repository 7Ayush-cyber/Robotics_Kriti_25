const int MQ3_PIN = A0;  // MQ3 sensor connected to A0
const int MQ4_PIN = A1;  // MQ4 sensor connected to A1

void setup() {
    Serial.begin(9600);  // Start Serial communication at 9600 baud rate
}


void loop() {
    int mq3_value = analogRead(MQ3_PIN);  // Read MQ3 sensor value
    int mq4_value = analogRead(MQ4_PIN);  // Read MQ4 sensor value


    Serial.print("MQ3 Alcohol Sensor Value: ");
    Serial.print(mq3_value);
    Serial.print("  |  ");


    Serial.print("MQ4 Methane Sensor Value: ");
    Serial.println(mq4_value);


    delay(1000);  // Wait for 1 second before reading again
}
