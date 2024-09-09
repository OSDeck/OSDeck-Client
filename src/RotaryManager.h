#ifndef ROTARY_ENCODER_H
#define ROTARY_ENCODER_H

#include <Arduino.h>

class RotaryEncoder {
private:
    int id;           
    int clkPin;      
    int dtPin;       
    int swPin;        
    int lastCLKState;
    int counter;     

public:
    RotaryEncoder(int id, int clkPin, int dtPin, int swPin = -1);
    int checkRotation();
    bool isButtonPressed();
    int getId();
    int getCounter();
};

#endif 
