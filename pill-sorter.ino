#include <ArduinoJson.h> 
#include <Servo.h>

Servo myServo1;  // Servo for pill1 dispensing
Servo myServo2;  // Servo for pill2 (or another use)
const int buttonPin = 2;  // Button input pin
int buttonState = 0;
int lastButtonState = 0;
int currentAngle = 90;  // Default servo position

void setup() {
  myServo1.attach(9);  
  myServo2.attach(10); 
  myServo1.write(currentAngle);  
  myServo2.write(currentAngle);  
  pinMode(buttonPin, INPUT_PULLUP);  

  Serial.begin(9600);
  Serial.println("Arduino ready to receive data...");
}

void loop() {
  if (Serial.available() > 0) {
    String jsonData = Serial.readStringUntil('\n');  // Read JSON data
    Serial.println("Received JSON:");
    Serial.println(jsonData);

    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, jsonData);

    if (error) {
      Serial.println("Failed to parse JSON");
      return;
    }

    if (doc.size() > 0) {
      JsonObject pill1 = doc[0];  
      JsonArray days = pill1["days"];

      Serial.print("Pill1: ");
      Serial.println(pill1["pillName"].as<String>());

      if (days.size() > 0 && days[0].as<bool>()) {
        Serial.println("Monday: Take Pill - Moving Servo1");
        moveServo(myServo1);
        
        // Move Servo2 only if needed
        Serial.println("Moving Servo2 for additional process");
        moveServo(myServo2);
      } else {
        Serial.println("Monday: No pill required");
      }
    }
  }

  // Manual button press
  buttonState = digitalRead(buttonPin);
  if (buttonState == LOW && lastButtonState == HIGH) {
    delay(100);
    Serial.println("Manual button pressed - Moving Servo1");
    moveServo(myServo1);
  }

  lastButtonState = buttonState;
}

void moveServo(Servo &servo) {
  servo.write(180);
  delay(200);
  servo.write(90);
}
