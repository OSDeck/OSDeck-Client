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

void Display::drawText(int x, int y, int size, char* text, int color) {
  tft->setFontScale(size);
  tft->setTextColor(color);
  tft->setCursor(x, y);
  tft->print(text);
}

void Display::drawImage(uint32_t *imageData, int x, int y, int width) {
  
}