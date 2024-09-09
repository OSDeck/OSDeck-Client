#include <Arduino.h>
#include "ComHandler.h"
#include "Display.h"
#include "TouchScreen.h"
#include "TouchData.h"
#include "JsonParser.h"
#include "ScreenObject.h"
#include "InputHandler.h"
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


void setup() {
  display = new Display(DISPLAY_CS);
  touch = new TouchScreen(INT, WAKE);
      Serial.begin(9600);
    while (!Serial) {
        // Wait for Serial to initialize
    }

    
    
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
        Serial.println("Sucessfully extracted all");  
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

    InputHandler::handleTouch(touch,display,screenObjs,comHandler);
    

}

