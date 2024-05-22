#ifndef COM_HANDLER_H
#define COM_HANDLER_H

#include <Arduino.h>
#include <ArduinoJson.h>

class ComHandler {
public:
    ComHandler(unsigned long baudRate = 115200);
    void sendData(const JsonDocument& doc);
    bool receiveData(JsonDocument& doc);
};

#endif // COM_HANDLER_H
