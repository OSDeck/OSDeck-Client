#include "ComHandler.h"

// Konstruktor
ComHandler::ComHandler(unsigned long baudRate) {
    Serial.begin(baudRate);
    while (!Serial) continue;
}

// Methode zum Senden von Daten
void ComHandler::sendData(const JsonDocument& doc) {
    serializeJson(doc, Serial);
    Serial.println();
}

// Methode zum Empfangen von Daten
bool ComHandler::receiveData(JsonDocument& doc) {
    if (Serial.available()) {
        String data = Serial.readStringUntil('\n');
        
        DeserializationError error = deserializeJson(doc, data);
        if (error) {
            Serial.print("deserializeJson() failed: ");
            Serial.println(error.c_str());
            return false;
        }
        return true;
    }
    return false;
}
