#include "TouchScreen.h"

TouchScreen::TouchScreen(int INT, int WAKE) {
  TS = new GSL1680();
  TS->begin(WAKE, INT);
}

struct TouchData* TouchScreen::readTouch() {
  if(TS->dataread() == 0) {
    return nullptr;
  }
  int touchpoints = TS->dataread();
  TouchData* data[touchpoints - 1];

  for(int i = 0; i < touchpoints; i++) {
    data[i]->fingerIndex = TS->readFingerID(i);
    data[i]->posX = TS->readFingerX(i);
    data[i]->posY = TS->readFingerY(i);
  }

  return *data;
}
