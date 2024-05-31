#ifndef JsonParser_h
#define JsonParser_h

#include <ArduinoJson.h>
#include "TouchData.h"

class JsonParser {
    private:
    public:
        JsonParser();
        JsonDocument parseTouchData(struct TouchData* touchData[]);
};

#endif