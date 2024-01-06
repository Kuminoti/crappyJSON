#pragma once

#ifndef JSON_H
#define JSON_H

#include"datatypes/jsonreader.h"





// Beginn der JSON-klasse

class Json {
   private:
    bool emptyJson;
    std::string Data;

   public:
    
    Json(std::string Data, bool emptyJson) {
        
      
            this->Data = Data;
            this->emptyJson = emptyJson;
            std::cout<<"new Json"<<std::endl;
            
        
    }

    std::string getData() { return this->Data; }

    void stringify() {}

    std::string getValue(std::string key) {
        std::string JsonValue;

        size_t keyStart = Data.find("\"" + key + "\"");
        if (keyStart == std::string::npos) {
            std::cerr << "Key not found: " << key << std::endl;
            // Schlüssel nicht gefunden, beende die Funktion
        }
        size_t keyEnd = keyStart + key.length() + 2;
        size_t valueStart = Data.find_first_not_of(" \t", keyEnd);
        size_t valueEnd = Data.find_first_of(",}", valueStart);
        if (valueEnd == std::string::npos) {
            std::cerr << "Error parsing JSON data." << std::endl;
            // Fehler beim Parsen der JSON-Daten, beende die Funktion
        }
        JsonValue = Data.substr(valueStart, valueEnd - valueStart);
        return JsonValue;
    }

    void changeData(std::string key, std::string value) {
        size_t keyStart = Data.find("\"" + key + "\"");
        if (keyStart == std::string::npos) {
            std::cerr << "Key not found: " << key << std::endl;
            return;  // Schlüssel nicht gefunden, beende die Funktion
        }
        size_t keyEnd = keyStart + key.length() +
                        2;  // 2 für die Anführungszeichen und den Doppelpunkt
        size_t valueStart = Data.find_first_not_of(" \t", keyEnd);

        size_t valueEnd = Data.find_first_of(",}", valueStart);
        if (valueEnd == std::string::npos) {
            std::cerr << "Error parsing JSON data." << std::endl;
            return;  // Fehler beim Parsen der JSON-Daten, beende die Funktion
        }
        this->Data.replace(valueStart, valueEnd - valueStart, value);
    }

    void addData(std::string KeyValue, std::string dataValue) {
        // check for arrays and objects
        bool object;
        bool array;

        array = dataValue.find("[") != std::string::npos;
        object = dataValue.find("{") != std::string::npos;

        // Add Data to your Json
        size_t lastBracePos = this->Data.rfind("}");

        if (lastBracePos != std::string::npos) {
            if (this->emptyJson) {
                if (array || object) {
                    this->Data.insert(lastBracePos - 1, "\"" + KeyValue + ":" +
                                                            dataValue + ",\n");

                } else if (!array && !object) {
                    this->Data.insert(
                        lastBracePos - 1,
                        "\"" + KeyValue + "\": " + dataValue + ",\n");
                }
                this->emptyJson = false;
            } else if (!this->emptyJson) {
                if (array || object) {
                    this->Data.insert(lastBracePos - 1, ",\"" + KeyValue + ":" +
                                                            dataValue + "\n");

                } else if (!array && !object) {
                    this->Data.insert(
                        lastBracePos - 1,
                        ",\"" + KeyValue + "\": " + dataValue + ",\n");
                }
            }
        } else {
            std::cerr << "ERROR";
        }
    }

    void saveFile(std::string src) {
        std::ofstream outputFile(src);
        if (outputFile.is_open()) {
            outputFile << this->Data;

            outputFile.close();

            std::cout << "Datei erfolgreich erstellt und Daten geschrieben."
                      << std::endl;
        } else {
            std::cerr << "Fehler beim Öffnen der Datei." << std::endl;
        }
    }

    void newFile(std::string src) {}

    static Json createEmptyJson() { return Json("{\n\n}", true); }

    static Json importStringData(std::string content) {
        return Json(content, false);
    }

    static Json readFromFile(std::string src) {
        std::ifstream inputFile(src);
        std::string fileContent;

        if (inputFile.is_open()) {
            std::string line;

            while (std::getline(inputFile, line)) {
                fileContent += line;  // Kein Zeilenumbruch hinzuf�gen
            }

            inputFile.close();
        } else {
            std::cerr << "Die Datei konnte nicht geöffnet werden." << std::endl;
        }
        return Json(fileContent, false);
    }
};

#endif