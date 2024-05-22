#ifndef TouchScreen_h
#define TouchScreen_h

#include <GSL1680.h>
#include "TouchData.h"

class TouchScreen {
  private:
    GSL1680* TS;
  public:
    TouchScreen(int INT, int WAKE);
    struct TouchData* readTouch();
    void test();
};

#endif