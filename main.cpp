#include <Arduino.h>
#include "ComHandler.h"

ComHandler comHandler(115200);

// put function declarations here:
void processMessage();

void setup() {
}

void loop() {
  // Check for incoming messages and process them
  processMessage();
}

// Function to process incoming messages
void processMessage() {
  StaticJsonDocument<200> doc;

  // Check if data was received
  if (comHandler.receiveData(doc)) {
    // Convert received JSON to string
    String message;
    serializeJson(doc, message);

    // Append ":3" to the message
    message = ":3";

    // Create a new JSON document to send back
    StaticJsonDocument<200> responseDoc;
    responseDoc["message"] = message;

    // Send the modified message back
    comHandler.sendData(responseDoc);
  }
}
