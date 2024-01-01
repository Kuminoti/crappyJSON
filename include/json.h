#pragma once

#ifndef JSON_H
#define JSON_H

// #include"jsondatatypes.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class JSONanalyser {
   private:
    std::vector<std::string> subObject;
    std::vector<std::string> Objectkey;

    std::vector<std::string> subArray;
    std::vector<std::string> Arraykey;

    void analyseNesting(std::string dataPath) {}

    bool extractJSONArray(std::string txt) {
        size_t startPos = 1;
        size_t nestings = 0;
        size_t sqBraceOpen;
        size_t sqBraceClose;
        bool valid = false;

        while ((sqBraceOpen = txt.find("[", startPos)) != std::string::npos) {
            nestings++;
            startPos = sqBraceOpen + 1;

            if ((sqBraceClose = txt.find("]", sqBraceOpen))) {
                nestings--;
                std::string nestedArray =
                    txt.substr(sqBraceOpen, sqBraceClose - sqBraceOpen + 1);
                subArray.push_back(nestedArray);
                size_t startPosKey = txt.rfind("\"", sqBraceOpen);
                if (startPosKey != std::string::npos) {
                    size_t endPosKey = txt.rfind("\"", startPosKey - 1);
                    if (endPosKey != std::string::npos) {
                        std::string ArrayKey = txt.substr(
                            endPosKey + 1, startPosKey - endPosKey - 1);
                        std::cout << "Key: " << ArrayKey << "\nvalue"
                                  << nestedArray << std::endl;
                        Arraykey.push_back(ArrayKey);
                    }
                }
            }
        }
        if (nestings == 0) {
            valid = true;
            return true;
        } else if (nestings > 0) {
            std::cerr << "Error: Missing ]" << std::endl;
            valid = false;
        } else if (nestings < 0) {
            std::cerr << "Error: Missing [" << std::endl;
            valid = false;
        }
        return valid;
    }

    bool extractJSONObject(std::string txt) {
        size_t nestings = 0;
        size_t startPos = 1;
        size_t openBracePos;
        size_t closeBracePos;

        bool valid = false;

        while ((openBracePos = txt.find("{", startPos)) != std::string::npos) {
            nestings++;
            startPos = openBracePos + 1;

            if ((closeBracePos = txt.find("}", openBracePos)) !=
                std::string::npos) {
                std::string nestedObject = txt.substr(
                    openBracePos, closeBracePos - openBracePos + nestings);
                nestings--;
                subObject.push_back(nestedObject);
                size_t startPosKey = txt.rfind("\"", openBracePos);
                if (startPosKey != std::string::npos) {
                    size_t endPosKey = txt.rfind("\"", startPosKey - 1);
                    if (endPosKey != std::string::npos) {
                        std::string objectKey = txt.substr(
                            endPosKey + 1, startPosKey - endPosKey - 1);
                        std::cout << "Key: " << objectKey << "\nvalue"
                                  << nestedObject << std::endl;
                        Objectkey.push_back(objectKey);
                    }
                }
            }
        }
        if (nestings == 0) {
            valid = true;
        } else if (nestings > 0) {
            std::cerr << "Error: Missing }" << std::endl;
            valid = false;
        } else if (nestings < 0) {
            std::cerr << "Error: Missing {" << std::endl;
            valid = false;
        }
        return valid;
    }

   public:
    bool analyseJSON(std::string data) {
        bool objects = extractJSONObject(data);
        bool arrays = extractJSONArray(data);
        if (objects && arrays) {
            return true;
        } else {
            std::cerr << "Error invalid json" << std::endl;
            return false;
        }
    }

    void getInfo(std::string info) {}
};

// Beginn der JSON-klasse

class Json {
   private:
    bool emptyJson;
    std::string Data;

   public:
    JSONanalyser process;

    Json(std::string Data, bool emptyJson) {
        this->process = JSONanalyser();
        bool valid = this->process.analyseJSON(Data);
        if (valid) {
            this->Data = Data;
            this->emptyJson = emptyJson;
            std::cout << "new JSON" << std::endl;
        } else {
            std::cout << "NOOB";
        }
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