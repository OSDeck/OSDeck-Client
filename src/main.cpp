#include <Arduino.h>
#include "ComHandler.h"
#include "Display.h"
#include "TouchScreen.h"
#include "TouchData.h"
#include "JsonParser.h"
#include "ScreenObject.h"
#include "InputHandler.h"
#include "RotaryManager.h"
#include <vector>

#define DISPLAY_CS 10
#define WAKE 5
#define INT 6

ComHandler comHandler(9600);


// put function declarations here:
void processMessage();

Display* display = nullptr;
TouchScreen* touch = nullptr;

//list of all objects currently on screen
 std::vector<ScreenObject> screenObjs;

//list of all rotary encoders
std::vector<RotaryEncoder> rotaryEncders;



void setup() {
  display = new Display(DISPLAY_CS);
  touch = new TouchScreen(INT, WAKE);
      Serial.begin(9600);
    while (!Serial) {
        // Wait for Serial to initialize
    }

    rotaryEncders.push_back(RotaryEncoder(0,42,41,40));
    rotaryEncders.push_back(RotaryEncoder(1,38,37,36));
    rotaryEncders.push_back(RotaryEncoder(2,21,20,19));
    
}

void handleInstruction(const String& message) {

    if (message == "PC_HANDSHAKE") {
        Serial.println("ARDUINO_HANDSHAKE");
    }
           
    if (message == "START_LOAD") {
        screenObjs.clear();
        Serial.println("NEXT");
        while(comHandler.receiveAndProcessJson(screenObjs)){
            Serial.println("NEXT");    
        }
        display->clearDisplay();
        display->drawAllScreenObjects(screenObjs);
    }

}


void loop() {
    // Always check for instructions from the PC
    if (Serial.available()) {
        String message = Serial.readStringUntil('\n');
        handleInstruction(message);
    }

    InputHandler::handleRotary(rotaryEncders,comHandler);

    InputHandler::handleTouch(touch,display,screenObjs,comHandler);
    

}

