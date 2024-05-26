#include <Arduino.h>
#include "ComHandler.h"
#include "Display.h"
#include "TouchScreen.h"
#include "TouchData.h"

#define DISPLAY_CS 10
#define INT 4
#define WAKE 5

ComHandler comHandler(9600);

// put function declarations here:
void processMessage();

Display* display = nullptr;
TouchScreen* touch = nullptr;

void setup() {
  display = new Display(DISPLAY_CS);
  touch = new TouchScreen(INT, WAKE);
  delay(1000);

  //display->drawRectangle(30, 30, 100, 100, RA8875_RED);
}

void loop() {
  // Check for incoming messages and process them
  //processMessage();

  if (digitalRead(INT) == HIGH) {
    struct TouchData* data = touch->readTouch();
    if(data != nullptr) {
      for(int i = 0; i < data[0].touchPoints; i++) {
        Serial.print("Finger: ");
        Serial.print(data[i].fingerIndex);
        Serial.print(" X: ");
        Serial.print(data[i].posX);
        Serial.print(" Y: ");
        Serial.print(data[i].posY);
        Serial.write("\n");
        }
    } else {
      Serial.println("No new Registry Entry");
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