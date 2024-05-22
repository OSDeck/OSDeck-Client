#ifndef Display_h
#define Display_h

#include <SPI.h>
#include <RA8875.h>

class Display {
  private:
    RA8875* tft;
  public:
    Display(int cs);
    void clearDisplay();
    void drawRectangle(int x, int y, int width, int height, int color);
    void drawCircle(int x, int y, int radius, int color);
    void drawText(int x, int y, int size, char* text, int color);
    void drawImage(uint32_t imageData[150000], int x, int y);
};

#endif