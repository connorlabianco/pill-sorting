#include <ArduinoJson.h>
#include <Servo.h>

Servo servo1; // Pill1
Servo servo2; // Pill2
Servo servo3; // Pill3
Servo newServo; // Rotating Plate

const int servo1Pin = 10;
const int servo2Pin = 9;
const int servo3Pin = 8; 
const int newServoPin = 7; // Set correct pin for the rotating plate servo

const int buttonPin = 6; // Start button pin
int currentDay = 0; // Track the current day
int newServoAngle = 0; // Track the angle of the rotating plate

bool pill1Days[7], pill2Days[7], pill3Days[7];

void setup() {
    Serial.begin(9600);

    servo1.attach(servo1Pin);
    servo2.attach(servo2Pin);
    servo3.attach(servo3Pin);
    newServo.attach(newServoPin);

    pinMode(buttonPin, INPUT_PULLUP); // Using internal pull-up

    resetServos();
    Serial.println("Setup complete. Waiting for data...");
}

void loop() {
    if (Serial.available() > 0) {
        String jsonString = Serial.readStringUntil('\n'); // Read JSON string
        Serial.println("Raw JSON Received: " + jsonString); // Log raw JSON
        processJson(jsonString);
        currentDay = 0; // Reset to the first day when new data arrives
        newServoAngle = 0; // Reset plate position
        newServo.write(newServoAngle); // Move to initial position
    }

    // Check if button is pressed to move to the next day
    if (digitalRead(buttonPin) == LOW) {
        delay(200); // Debounce delay
        executeServoMovements(); // Execute for the current day

        // **Wait 5 seconds before rotating the plate**
        Serial.println("Waiting 5 seconds before rotating plate...");
        delay(5000); 

        // Move the rotating plate servo by 180/7 degrees
        newServoAngle += 180 / 7;
        if (newServoAngle > 180) {
            newServoAngle = 0; // Reset to Monday if exceeding Sunday
        }
        newServo.write(newServoAngle);
        Serial.print("Rotating plate moved to ");
        Serial.print(newServoAngle);
        Serial.println(" degrees.");

        currentDay++; // Move to the next day
        
        if (currentDay >= 7) {
            Serial.println("All days completed. Resetting...");
            currentDay = 0; // Restart week cycle
            newServoAngle = 0; // Reset plate position
            newServo.write(newServoAngle);
        }

        while (digitalRead(buttonPin) == LOW); // Wait for button release
    }
}

void processJson(String jsonString) {
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, jsonString);

    if (error) {
        Serial.println("JSON Parse Failed");
        return;
    }

    Serial.println("JSON Parsed Successfully:");
    for (int i = 0; i < 7; i++) {
        pill1Days[i] = doc["pill1"][i];
        pill2Days[i] = doc["pill2"][i];
        pill3Days[i] = doc["pill3"][i];
    }
}

void executeServoMovements() {
    Serial.print("Day ");
    Serial.print(currentDay);
    Serial.println(": Executing Servo Movements...");

    if (pill1Days[currentDay]) {
        Serial.println("Moving Servo1 (Pill1)");
        servo1.write(0);
        delay(50); // Hold position
        servo1.write(90);
    }
    if (pill2Days[currentDay]) {
        Serial.println("Moving Servo2 (Pill2)");
        servo2.write(0);
        delay(45);
        servo2.write(90);
    }
    if (pill3Days[currentDay]) {
        Serial.println("Moving Servo3 (Pill3)");
        servo3.write(10);
        delay(66);
        servo3.write(100);
    }
    
    Serial.println("Servo Movements Complete for Today.");
}

void resetServos() {
    servo1.write(90);
    servo2.write(90);
    servo3.write(100);
    newServo.write(0); // Reset plate position to start (Monday)
    Serial.println("Servos Reset to 90°, Plate Reset to 0°");
}
