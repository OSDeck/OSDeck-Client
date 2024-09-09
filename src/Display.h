#ifndef Display_h
#define Display_h

#include <SPI.h>
#include <RA8875.h>
#include "ScreenObject.h"
#include <vector>

class Display {
  private:
    RA8875* tft;
  public:
    Display(int cs);
    void clearDisplay();
    void drawRectangle(int x, int y, int width, int height, int color);
    void drawCircle(int x, int y, int radius, int color);
    void drawText(int x, int y, int size, const char* text, int color);
    void drawTextAutoCenter(int x, int y, int size, const char* text, int color);
    void drawImage(const uint32_t* imageData, int x, int y, int width, int size);
    void drawButton(int x, int y, int width,int height, int color,int secondaryColor, bool pressed);
    void drawButtonWithText(int x, int y, int with, int height ,int textSize,int color,int secondaryColor,int textColor, const char* text, bool pressed = false);
    void drawButtonWithImage(int x, int y, int size ,int color, const uint32_t* imageData, bool pressed);
    void drawSliderHorizontal(int x, int y, int size, int color,int secondColor, int value = 0);
    void drawSliderVertical(int x, int y, int size, int color,int secondColor, int value = 0);
    void drawDisplayObject(ScreenObject obj);
    void drawAllScreenObjects(std::vector<ScreenObject> objs);

};

#endif