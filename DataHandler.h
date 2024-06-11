// DataHandler.h

#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <ArduinoJson.h>
#include "ComHandler.h"

class DataHandler {
public:
    DataHandler(ComHandler& comHandler);

    void sendRotationData(const String& id, float rotation);
    void sendSlideData(const String& id, float slide);
    void sendPositionData(const String& id, float x, float y);

private:
    ComHandler& comHandler;
};

#endif // DATAHANDLER_H
