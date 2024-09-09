#include "JsonParser.h"



JsonDocument JsonParser::parseTouchData(struct TouchData* touchData[]) {
    JsonDocument doc;
    //doc[""]

}

void JsonParser::parseAndAddScreenObject(String& jsonString, std::vector<ScreenObject>& screenObjects) {
    // Trim the input string to remove any unwanted whitespace
    jsonString.trim();

    // Create a DynamicJsonDocument for the outer JSON
    DynamicJsonDocument outerDoc(2048);
    DeserializationError error = deserializeJson(outerDoc, jsonString);

    // Check for errors in deserialization
    if (error) {
        Serial.print("Outer deserializeJson() failed: ");
        Serial.println(error.c_str());
        Serial.println(jsonString);
        return;
    }

    // Extract the inner JSON string from the "config" field
    String innerJsonString = outerDoc["config"].as<String>();

    // Create a new DynamicJsonDocument for the inner JSON
    DynamicJsonDocument innerDoc(2048);
    error = deserializeJson(innerDoc, innerJsonString);

    // Check for errors in deserialization of the inner JSON
    if (error) {
        Serial.print("Inner deserializeJson() failed: ");
        Serial.println(error.c_str());
        Serial.println(innerJsonString);
        return;
    }

    // Extract values from the inner JSON document and populate the ScreenObject
    ScreenObject screenObj;
    screenObj.globalId = innerDoc["globalId"];
    screenObj.objType = innerDoc["objType"];
    screenObj.posX = innerDoc["Position"]["x"];
    screenObj.posY = innerDoc["Position"]["y"];
    screenObj.sizeX = innerDoc["Properties"]["SizeX"];

    if (innerDoc["Properties"].containsKey("SizeY")) {
        screenObj.sizeY = innerDoc["Properties"]["SizeY"];
    } else {
        screenObj.sizeY = innerDoc["Properties"]["SizeX"];
    }

    if (innerDoc["Properties"].containsKey("Color")) {
        screenObj.color = innerDoc["Properties"]["Color"];
    } else {
        screenObj.color = -1;
    }
    screenObj.value = 0;  // Default value
    screenObj.touched = false;  // Default value
    screenObj.ciclesSinceLastTouch = 0;  // Default value

    // Optional fields
    if (innerDoc["Properties"].containsKey("Text")) {
        screenObj.text = innerDoc["Properties"]["Text"].as<const char*>();
    } else {
        screenObj.text = nullptr;
    }

    if (innerDoc["Properties"].containsKey("TextSize")) {
        screenObj.textSize = innerDoc["Properties"]["TextSize"];
    } else {
        screenObj.textSize = -1;  // Default value
    }

    if (innerDoc["Properties"].containsKey("TextColor")) {
        screenObj.textColor = innerDoc["Properties"]["TextColor"];
    } else {
        screenObj.textColor = -1;  // Default value
    }

    if (innerDoc["Properties"].containsKey("SecondaryColor")) {
        screenObj.secondaryColor = innerDoc["Properties"]["SecondaryColor"];
    } else {
        screenObj.secondaryColor = -1;  // Default value
    }

if (innerDoc["Properties"].containsKey("Image")) {
    String base64Image = innerDoc["Properties"]["Image"];
    size_t decodedLength = 0;

    // Allocate buffer for the decoded data (worst case size for base64 is 3/4 of the original size)
    size_t imageDataLength = (base64Image.length() * 3) / 4;
    uint8_t* byteData = (uint8_t*)malloc(imageDataLength);

    // Decode the base64 string
    int ret = mbedtls_base64_decode(byteData, imageDataLength, &decodedLength, (const unsigned char*)base64Image.c_str(), base64Image.length());

    if (ret == 0) {
        // Convert byte array to uint32_t array if needed
        int numPixels = decodedLength / sizeof(uint32_t);
        screenObj.imageData = new uint32_t[numPixels];
        memcpy(screenObj.imageData, byteData, decodedLength);
    } else {
        Serial.println("Base64 decoding failed");
        screenObj.imageData = nullptr;
    }

    // Clean up
    free(byteData);
} else {
    screenObj.imageData = nullptr;
}


    // Add the new ScreenObject to the list
    screenObjects.push_back(screenObj);
}


StaticJsonDocument<200> JsonParser::EventJson(ScreenObject obj){
 // Create a JSON document
    StaticJsonDocument<200> doc;

    // Add the id field, convert globalId to a string
    doc["id"] = String(obj.globalId);

    // Create the input object
    JsonObject input = doc.createNestedObject("input");

    // Add the value field
    input["value"] = obj.value;

    // Convert the JSON document to a string and return it
    return doc;
}