#ifndef InputHandler_h
#define InputHandler_h
#include <SPI.h>
#include <RA8875.h>
#include "ScreenObject.h"
#include <vector>
#include "TouchData.h"
#include "TouchScreen.h"
#include "Display.h"
#include "ComHandler.h"
#include "RotaryManager.h"

class ComHandler;

class InputHandler {
  private:

  public:
     static void handleTouch(TouchScreen* touch, Display* display, std::vector<ScreenObject>& objs, ComHandler& com);
     static void handleRotary(std::vector<RotaryEncoder>& rotarys,ComHandler& com);
    
};

#endif