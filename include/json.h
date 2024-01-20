#pragma once

#ifndef JSON_H
#define JSON_H

#define version "0.1.0"

#include "datatypes/jsonreader.h"

// Beginn der JSON-klasse

class Json {
   private:
    bool emptyJson;
    std::string Data;
    JSONReader process;

   public:
    Json(std::string Data, bool emptyJson);
    std::string getData();

    std::string getValue(std::string key);

    void changeData(std::string key, std::string value);

    void addData(std::string KeyValue, std::string dataValue);

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