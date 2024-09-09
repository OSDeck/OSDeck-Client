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

void Display::drawTextAutoCenter(int x, int y, int size, const char* text, int color) {
  tft->setFontScale(size);
  tft->setTextColor(color);
  tft->setCursor(x, y,true);
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

    void Display::drawButton(int x, int y, int width,int height, int color,int secondaryColor, bool pressed){
        drawRectangle(x, y, width, height, color);

        double innerSizefactorX = 0.1 * width;
        double innerSizefactorY = 0.1 * height;

        if (pressed)
        {
          innerSizefactorX *= 2;
          innerSizefactorY *= 2;
        }

        drawRectangle(x + innerSizefactorX,y + innerSizefactorY, width - 2*innerSizefactorX, height - 2*innerSizefactorY, secondaryColor);

    }
    void Display::drawButtonCircle(int x, int y, int radius, int color,int secondaryColor, bool pressed){
        drawCircle(x + radius, y + radius, radius , color);

        double innerSizefactorRadius = 0.1 * radius;

        if (pressed)
        {
          innerSizefactorRadius *= 2;
        }

        drawCircle(x + radius,y + radius, radius - 2*innerSizefactorRadius, secondaryColor);

    }
    void Display::drawButtonCircleWithText(int x, int y, int radius ,int textSize,int color,int secondaryColor,int textColor, const char* text, bool pressed){
        drawCircle(x + radius, y + radius, radius , color);

        double innerSizefactorRadius = 0.1 * radius;

        if (pressed)
        {
          innerSizefactorRadius *= 2;
        }

        drawCircle(x + radius,y + radius, radius -  2*innerSizefactorRadius, secondaryColor);
        drawTextAutoCenter(x + radius,y+radius,textSize,text,textColor);

    }


    void Display::drawButtonWithText(int x, int y, int with, int height ,int textSize,int color,int secondaryColor,int textColor, const char* text, bool pressed){
        drawRectangle(x, y, with, height, color);

        double innerSizefactorX = 0.1 * with;
        double innerSizefactorY = 0.1 * height;
        if (pressed)
        {
          innerSizefactorX *= 2;
          innerSizefactorY *= 2;
        }

        drawRectangle(x + innerSizefactorX,y + innerSizefactorY, with - 2*innerSizefactorX, height - 2*innerSizefactorY, 0x4208);

        drawTextAutoCenter(x + with/2,y+height/2,textSize,text,textColor);
    }
    void Display::drawButtonWithImage(int x, int y, int size ,int color, const uint32_t* imageData, bool pressed){
      drawRectangle(x, y, size, size, color);

      double innerSizefactor = 0.1 * size;

      if (pressed)
      {
        innerSizefactor *= 2;
      }

      drawImage(imageData,x + innerSizefactor,y + innerSizefactor, size - 2*innerSizefactor, size - 2*innerSizefactor);
 
    }
    void Display::drawSliderHorizontal(int x, int y, int size, int color,int secondColor, int value){
      double heightSled = 20;
      double widthSled = 20;

      double actualSledDistance = size-widthSled;


      drawRectangle(x, y, size , heightSled, secondColor);


      drawRectangle(x+ actualSledDistance/ 100 * value, y , widthSled , heightSled, color);
    }
    void Display::drawSliderVertical(int x, int y, int size, int color,int secondColor, int value){
      double heightSled = 20;
      double widthSled = 20;

      double actualSledDistance = size-widthSled;
      
      drawRectangle(x, y, heightSled, size, secondColor);

      drawRectangle(x, y + actualSledDistance/ 100 * value, widthSled , heightSled, color);
    }


    void Display::drawDisplayObject(ScreenObject obj){
      switch (obj.objType)
      {
      case 0: //text
        drawText(obj.posX,obj.posY,obj.sizeX,obj.text,obj.color);
        break;
      
      case 1:// rectangle
        drawRectangle(obj.posX,obj.posY,obj.sizeX,obj.sizeY,obj.color);
        break;

      case 2: //circle
        drawCircle(obj.posX,obj.posY,obj.sizeX,obj.color);
        break;

      case 3: //image
        drawImage(obj.imageData,obj.posX,obj.posY,obj.sizeX,obj.sizeY);
        break;

      case 4: //button Rectnangle
          drawButton(obj.posX,obj.posY,obj.sizeX,obj.sizeY,obj.color,obj.secondaryColor,obj.touched);
        break;

      case 5: //button Rectangle with Image
          drawButtonWithImage(obj.posX,obj.posY,obj.sizeX,obj.color,obj.imageData,obj.touched);
        break;

      case 6: //button Rectangle with Text
        drawButtonWithText(obj.posX,obj.posY,obj.sizeX,obj.sizeY,obj.textSize,obj.color,obj.secondaryColor,obj.textColor,obj.text,obj.touched);
        break;
      
      case 7://button Circle
          drawButtonCircle(obj.posX,obj.posY,obj.sizeX,obj.color,obj.secondaryColor,obj.touched);
        break;

      case 8: //button Circle with Text
          drawButtonCircleWithText(obj.posX,obj.posY,obj.sizeX,obj.textSize,obj.color,obj.secondaryColor,obj.textColor,obj.text,obj.touched);
        break;

      case 9: //slider Vertical
        drawSliderVertical(obj.posX,obj.posY,obj.sizeX,obj.color,obj.secondaryColor,obj.value);
        break;

      case 10: //slider Horizontal
        drawSliderHorizontal(obj.posX,obj.posY,obj.sizeX,obj.color,obj.secondaryColor,obj.value);
        break;
      
      default:
        break;
      }
    }

  void Display::drawAllScreenObjects(std::vector<ScreenObject> objs){
    for (int i = 0; i < objs.size(); i++)
    {
        drawDisplayObject(objs[i]);
    }
}


