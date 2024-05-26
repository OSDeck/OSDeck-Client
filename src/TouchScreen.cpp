#include "TouchScreen.h"

TouchScreen::TouchScreen(int INT, int WAKE) {
  TS = new GSL1680();
  TS->begin(WAKE, INT);
  data = new TouchData[1];
}

struct TouchData* TouchScreen::readTouch() {
  delete[] data;
  int touchpoints = TS->dataread();

  if(touchpoints == 0) {
    data = nullptr;
    return data;
  }

  data = new TouchData[touchpoints];

  for(int i = 0; i < touchpoints; i++) {
    data[i].fingerIndex = TS->readFingerID(i);
    data[i].posX = TS->readFingerX(i);
    data[i].posY = TS->readFingerY(i);
    data[i].touchPoints = touchpoints;
  }

  return data;
}
