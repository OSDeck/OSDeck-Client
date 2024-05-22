#include <Arduino.h>
#include "ComHandler.h"
#include "Display.h"
#include "TouchScreen.h"

#define DISPLAY_CS 10
#define INT 4
#define WAKE 5

ComHandler comHandler(115200);

// put function declarations here:
void processMessage();

Display* display = nullptr;
TouchScreen* touch = nullptr;

void setup() {
  display = new Display(DISPLAY_CS);
  touch = new TouchScreen(INT, WAKE);
}

void loop() {
  // Check for incoming messages and process them
  processMessage();

  if (digitalRead(INT) == HIGH) {
    TouchData* t = touch->readTouch();
    if(t != nullptr) {
      Serial.write(t[0].posX);
      Serial.write('\n');
    }
  }
}

// Function to process incoming messages
void processMessage() {
  StaticJsonDocument<200> doc;

  // Check if data was received
  if (comHandler.receiveData(doc)) {
    // Convert received JSON to string
    String message;
    serializeJson(doc, message);

    // Append ":3" to the message
    message = ":3";

    // Create a new JSON document to send back
    StaticJsonDocument<200> responseDoc;
    responseDoc["message"] = message;

    // Send the modified message back
    comHandler.sendData(responseDoc);
  }
}