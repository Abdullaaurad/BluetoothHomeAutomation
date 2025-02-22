#include <SoftwareSerial.h>

#define TRIG_PIN 2
#define ECHO_PIN A0
#define LDR_PIN A1
#define BUZZER_PIN 5
#define LED_PIN 6

SoftwareSerial BT(10, 11);  // HC-05 TX to D10, RX to D11

void setup() {
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    BT.begin(9600);  
    Serial.begin(9600);
    
    // Debugging message to confirm serial communication
    Serial.println("Bluetooth module initialized.");
}

void loop() {
    long duration;
    int distance;
    
    // Measure distance using Ultrasonic Sensor
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    
    duration = pulseIn(ECHO_PIN, HIGH);
    distance = duration * 0.034 / 2;
    
    // Read LDR value
    int lightLevel = analogRead(LDR_PIN);
    
    //Send sensor data to mobile via Bluetooth
    BT.print("Distance: "); BT.print(distance); BT.println(" cm");
    BT.print("Light Level: "); BT.println(lightLevel);

    // Print sensor data to Serial Monitor for debugging
    Serial.print("Distance: "); Serial.print(distance); Serial.println(" cm");
    Serial.print("Light Level: "); Serial.println(lightLevel);
    
    // Read Bluetooth commands from mobile app
    if (BT.available()) {
        char command = BT.read();
        Serial.print("Received command: "); Serial.println(command);

        if (command == '1') {  // Turn ON LED/Bulb
            digitalWrite(LED_PIN, HIGH);
            Serial.println("LED ON");
        } else if (command == '0') {  // Turn OFF LED/Bulb
            digitalWrite(LED_PIN, LOW);
            Serial.println("LED OFF");
        } else if (command == 'B') {  // Turn ON Buzzer
            digitalWrite(BUZZER_PIN, HIGH);
            Serial.println("Buzzer ON");
        } else if (command == 'b') {  // Turn OFF Buzzer
            digitalWrite(BUZZER_PIN, LOW);
            Serial.println("Buzzer OFF");
        }
    }
    
    delay(500);  // Delay to make the serial output more readable
}
