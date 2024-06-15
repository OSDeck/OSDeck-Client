#include <Arduino.h>
#include "ComHandler.h"
#include "Display.h"
#include "TouchScreen.h"
#include "TouchData.h"
#include "JsonParser.h"

#define DISPLAY_CS 10
#define WAKE 5
#define INT 6

ComHandler comHandler(9600);

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
  //processMessage();

  if (digitalRead(INT) == HIGH) {
    struct TouchData* data = touch->readTouch();
    if(data != nullptr) {
    } else {
      Serial.println("No new Registry Entry");
    }
  }
}
