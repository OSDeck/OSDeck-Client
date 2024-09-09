#ifndef JsonParser_h
#define JsonParser_h

#include <ArduinoJson.h>
#include "TouchData.h"
#include "Arduino.h"
#include <vector>
#include"ScreenObject.h"
#include "mbedtls/base64.h"

class JsonParser {
    private:
    public:
        JsonParser();
        JsonDocument parseTouchData(struct TouchData* touchData[]);
        static void parseAndAddScreenObject(String& jsonString, std::vector<ScreenObject>& screenObjects);
        static StaticJsonDocument<200> EventJson(ScreenObject obj);
};
         

#endif