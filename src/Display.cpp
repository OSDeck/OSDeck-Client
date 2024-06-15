#include "Display.h"

Display::Display(int cs) {
  tft = new RA8875(cs);
  tft->begin(RA8875_800x480);
}

void Display::clearDisplay() {
  tft->clearScreen();
}

void Display::drawRectangle(int x, int y, int width, int height, int color) {
  tft->fillRect(x, y, width, height, color);
}

void Display::drawCircle(int x, int y, int radius, int color) {
  tft->fillCircle(x, y, radius, color);
}

void Display::drawText(int x, int y, int size, const char* text, int color) {
  tft->setFontScale(size);
  tft->setTextColor(color);
  tft->setCursor(x, y);
  tft->print(text);
}

void Display::drawImage(const uint32_t* imageData, int x, int y, int width, int size) {
  uint16_t pixels[width];

  for(int col = 0; col < size / width; col++) {
    for (int i = (width*col); i < width*(col+1);i++){
      pixels[i - (width*col)] = tft->Color24To565(imageData[i]);
    }
    tft->drawPixels(pixels,width,x,col+y);
  }
}
