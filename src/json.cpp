#include "json.h"


Json::Json(std::string Data, bool emptyJson) : process() {
    if (process.checkJson(Data)) {
        this->Data = Data;
        this->emptyJson = emptyJson;
        std::cout << "new Json" << std::endl;
    } else {
        std::cout << "OBAOPFA";
    }
}

std::string Json::getData() { return this->Data; }

void Json::changeData(std::string key, std::string value) {
    size_t keyStart = Data.find("\"" + key + "\":");
    if (keyStart == std::string::npos) {
        std::cerr << "Key not found: " << key << std::endl;
        return;  // Schlüssel nicht gefunden, beende die Funktion
    }
    size_t keyEnd = keyStart + key.length() +
                    3;  // 2 für die Anführungszeichen und den Doppelpunkt
    size_t valueStart = Data.find_first_not_of(" \t", keyEnd);

    size_t valueEnd = Data.find_first_of(",}", valueStart);
    if (valueEnd == std::string::npos) {
        std::cerr << "Error parsing JSON data." << std::endl;
        return;  // Fehler beim Parsen der JSON-Daten, beende die Funktion
    }
    this->Data.replace(valueStart, valueEnd - valueStart, value);
}

void Json::addData(std::string KeyValue, std::string dataValue) {
    bool object;
    bool array;

    array = dataValue.find("[") != std::string::npos;
    object = dataValue.find("{") != std::string::npos;

    // Add Data to your Json
    size_t lastBracePos = this->Data.rfind("}");

    if (lastBracePos != std::string::npos) {
        if (this->emptyJson) {
            if (array || object) {
                this->Data.insert(lastBracePos - 1,
                                  "\"" + KeyValue + ":" + dataValue + ",\n");

            } else if (!array && !object) {
                this->Data.insert(lastBracePos - 1,
                                  "\"" + KeyValue + "\": " + dataValue + ",\n");
            }
            this->emptyJson = false;
        } else if (!this->emptyJson) {
            if (array || object) {
                this->Data.insert(lastBracePos - 1,
                                  ",\"" + KeyValue + ":" + dataValue + "\n");

            } else if (!array && !object) {
                this->Data.insert(lastBracePos - 1, ",\"" + KeyValue + "\": " +
                                                        dataValue + ",\n");
            }
        }
    } else {
        std::cerr << "ERROR";
    }
}

std::string Json::getValue(std::string key) {
    std::string JsonValue;

    size_t keyStart = Data.find("\"" + key + "\"");
    if (keyStart == std::string::npos) {
        std::cerr << "Key not found: " << key << std::endl;
        return JsonValue; 
    }

    size_t keyEnd = keyStart + key.length() + 3;

    size_t valueStart = Data.find_first_not_of(" \t", keyEnd);
    size_t valueEnd = Data.find_first_of(",}", valueStart);

    if (valueEnd == std::string::npos) {
        std::cerr << "Error parsing JSON data." << std::endl;
        return JsonValue; // Rückgabe eines leeren Werts im Fehlerfall
    }

    JsonValue = Data.substr(valueStart, valueEnd - valueStart);

    // Überprüfen, ob der Wert ein Objekt ist (von geschweiften Klammern umschlossen)
    if (JsonValue.find("{") != std::string::npos) {
        std::cout << "FOUND OBJECT\n";

        int braceCount = 0;
        size_t currentIndex = valueStart;
        size_t dataSize = Data.size();

        // Finden der schließenden geschweiften Klammer für das verschachtelte Objekt
        while (currentIndex < dataSize) {
            if (Data[currentIndex] == '{') {
                braceCount++;
            } else if (Data[currentIndex] == '}') {
                braceCount--;
                if (braceCount == 0) {
                    break;  // Schließende Klammer für das verschachtelte Objekt gefunden
                }
            }
            currentIndex++;
        }

        if (braceCount == 0) {
            JsonValue = Data.substr(valueStart, currentIndex - valueStart + 1);
            
        }
    }

    return JsonValue;
}
