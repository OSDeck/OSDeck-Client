#include <SPI.h>

#ifndef ScreenObject_h
#define ScreenObject_h

struct ScreenObject {
    int globalId;
    int objType;
    int posX;
    int posY;
    const char* text;
    int textSize;
    int textColor;
    int sizeX;
    int sizeY;
    int color;
    int secondaryColor;
    const uint32_t* imageData;
    int value;
    bool touched;
    int ciclesSinceLastTouch;
};

#endif