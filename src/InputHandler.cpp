#include "InputHandler.h"

const int CYCLESWITHOUTTOUCHFORCONFIRM = 5;

void InputHandler::handleTouch(TouchScreen* touch, Display* display, std::vector<ScreenObject>& objs, ComHandler& com) {
    struct TouchData* data = touch->readTouch();
    if(data != nullptr) {
        for(int i = 0; i < data->touchPoints; i++) {

            for (int j = 0; j < objs.size(); j++)
            {
                //check if interactable object
                if(objs[j].objType <= 3){
                    continue;
                }
                else if(objs[j].objType <= 8){//check if button
                    if (objs[j].posX < data[i].posX and objs[j].posX + objs[j].sizeX > data[i].posX and objs[j].posY < data[i].posY and objs[j].posY + objs[j].sizeY > data[i].posY)
                    {
                        if(!objs[j].touched){
                            objs[j].touched = true;
                            display->drawDisplayObject(objs[j]);
                        }

                        objs[j].ciclesSinceLastTouch = 0;
                    }  
                }
                else if(objs[j].objType == 9){//check if Slider Vertical
                    if (objs[j].posX - 20 < data[i].posX && objs[j].posX + 50 > data[i].posX &&
                        objs[j].posY - 10 < data[i].posY && objs[j].posY + objs[j].sizeY + 10 > data[i].posY)
                    {
                        if(!objs[j].touched){
                            objs[j].touched = true;
                        }

                        objs[j].value =  ((data[i].posY - objs[j].posY) * 100.0f) / objs[j].sizeY;

                        if(objs[j].value > 100){
                            objs[j].value = 100;
                        }

                        if(objs[j].value < 0){
                            objs[j].value = 0;
                        }

                         display->drawDisplayObject(objs[j]);

                        objs[j].ciclesSinceLastTouch = 0;
                    }
                }
                else if(objs[j].objType == 10){//check if Slider Horizontal
                    if (objs[j].posX - 10 < data[i].posX and objs[j].posX + objs[j].sizeX + 10 > data[i].posX and objs[j].posY - 20 < data[i].posY and objs[j].posY + 30 > data[i].posY)
                    {
                         if(!objs[j].touched){
                            objs[j].touched = true;
                        }

                        objs[j].value =  ((data[i].posX - objs[j].posX) * 100.0f) / objs[j].sizeX;

                        if(objs[j].value > 100){
                            objs[j].value = 100;
                        }

                        if(objs[j].value < 0){
                            objs[j].value = 0;
                        }

                         display->drawDisplayObject(objs[j]);

                        objs[j].ciclesSinceLastTouch = 0;
                    }
                }
                
                
            }
        }
    }
    for (int i = 0; i < objs.size(); i++)
    {  
        if (not objs[i].touched)
        {
            continue;
        }

         objs[i].ciclesSinceLastTouch++;

        if (objs[i].ciclesSinceLastTouch > CYCLESWITHOUTTOUCHFORCONFIRM)
        {
            objs[i].touched = false;
            display->drawDisplayObject(objs[i]);
            if (objs[i].objType < 9)
            {
                objs[i].value = 1;
            }
            
            com.sendEvent(objs[i]);
        }
        
        
    }

}

void InputHandler::handleRotary(std::vector<RotaryEncoder>& rotarys,ComHandler& com){

    for (int i = 0; i < rotarys.size(); i++)
    {
        int movement = rotarys[i].checkRotation();

        if(movement != 0){
            ScreenObject obj;
            obj.globalId = rotarys[i].getId();
            obj.value = movement;
            com.sendEvent(obj);
        }

        if(rotarys[i].isButtonPressed()){
            ScreenObject obj;
            obj.globalId = rotarys[i].getId();
            obj.value = 2;
            com.sendEvent(obj);
        }
    }

}