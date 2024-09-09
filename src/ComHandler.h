#ifndef COM_HANDLER_H
#define COM_HANDLER_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <InputHandler.h>
#include <vector>
#include "ScreenObject.h"
#include "JsonParser.h"

class ComHandler {
public:
    bool Connect();
    ComHandler(unsigned long baudRate = 115200);
    void sendData(const JsonDocument& doc);
    bool receiveData(JsonDocument& doc);
    bool receiveAndProcessJson(std::vector<ScreenObject>& screenObjects);
    void sendEvent(ScreenObject obj);
};

#endif // COM_HANDLER_H
