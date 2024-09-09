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

// Method to establish connection (handshake)
bool ComHandler::Connect() {
    const String handshakeRequest = "PC_HANDSHAKE";
    const String handshakeResponse = "ARDUINO_HANDSHAKE";

    // Wait for handshake from PC
    while (true) {
        if (Serial.available()) {
            String incomingMessage = Serial.readStringUntil('\n');
            if (incomingMessage == handshakeRequest) {
                Serial.println(handshakeResponse);  // Send acknowledgment
                return true;
            }
        }
    }
}

// Function to receive and process JSON data
bool ComHandler::receiveAndProcessJson(std::vector<ScreenObject>& screenObjects) {
    unsigned long startTime = millis();
    const unsigned long timeout = 1000;  // 1-second timeout

    while (millis() - startTime < timeout) {
        if (Serial.available()) {
            String jsonString = Serial.readStringUntil('\n');
            if (jsonString == "END") {
                return false;
            }
            JsonParser::parseAndAddScreenObject(jsonString, screenObjects);
            return true;
        }
    }

    return true; 
}

void ComHandler::sendEvent(ScreenObject obj){
    Serial.println("EVENT");
    sendData(JsonParser::EventJson(obj));
}

