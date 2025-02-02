#include <ArduinoJson.h>  // Using ArduinoJson library from the Library Manager

void setup() {
  // Start the serial communication
  Serial.begin(9600);
  while (!Serial) { }

  Serial.println("Ready to receive data...");
}

void loop() {
  // Check if there's any data available to read
  if (Serial.available() > 0) {
    String jsonData = Serial.readString();  // Read the incoming data as a string
    Serial.println("Received JSON data:");
    Serial.println(jsonData);

    // Parse the JSON data
    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, jsonData);

    if (error) {
      Serial.println("Failed to parse JSON");
      return;
    }

    // Loop through each pill and its data
    JsonArray pillsArray = doc.as<JsonArray>();
    for (JsonObject pill : pillsArray) {
      String pillName = pill["pillName"];
      JsonArray days = pill["days"];

      Serial.print("Pill: ");
      Serial.println(pillName);

      // Loop through each day and print whether the checkbox is checked (true or false)
      for (int i = 0; i < days.size(); i++) {
        Serial.print("Day ");
        Serial.print(i + 1);  // Days 1 to 7
        Serial.print(": ");
        Serial.println(days[i].as<bool>() ? "Take" : "Do not take");
      }
    }
  }
}
