#include "RotaryManager.h"


RotaryEncoder::RotaryEncoder(int id, int clkPin, int dtPin, int swPin) : id(id), clkPin(clkPin), dtPin(dtPin), swPin(swPin), counter(0) {
    pinMode(clkPin, INPUT);
    pinMode(dtPin, INPUT);
    if (swPin != -1) {
        pinMode(swPin, INPUT_PULLUP); 
    }
    lastCLKState = digitalRead(clkPin);
}

int RotaryEncoder::checkRotation() {
    int currentCLKState = digitalRead(clkPin);
    int movement = 0;

 
    if (currentCLKState != lastCLKState) {
      
        if (digitalRead(dtPin) != currentCLKState) {
            counter++;  
            movement = 1;
        } else {
            counter--; 
            movement = -1;
        }
    }

    lastCLKState = currentCLKState;

    return movement;  
}


bool RotaryEncoder::isButtonPressed() {
    if (swPin != -1 && digitalRead(swPin) == LOW) {
        delay(200);  
        return true;
    }
    return false;
}


int RotaryEncoder::getId() {
    return id;
}


int RotaryEncoder::getCounter() {
    return counter;
}
