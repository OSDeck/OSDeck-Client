
#include "DataHandler.h"

DataHandler::DataHandler(ComHandler& comHandler) : comHandler(comHandler) {}

void DataHandler::sendRotationData(const String& id, float rotation) {
    StaticJsonDocument<200> doc;
    doc["id"] = id;
    JsonObject input = doc.createNestedObject("input");
    input["rotation"] = rotation;

    comHandler.sendData(doc);
}

void DataHandler::sendSlideData(const String& id, float slide) {
    StaticJsonDocument<200> doc;
    doc["id"] = id;
    JsonObject input = doc.createNestedObject("input");
    input["slide"] = slide;

    comHandler.sendData(doc);
}

void DataHandler::sendPositionData(const String& id, float x, float y) {
    StaticJsonDocument<200> doc;
    doc["id"] = id;
    JsonObject input = doc.createNestedObject("input");
    JsonObject position = input.createNestedObject("position");
    position["x"] = x;
    position["y"] = y;

    comHandler.sendData(doc);
}
