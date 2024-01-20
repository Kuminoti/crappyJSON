#include "../include/datatypes/JsonReader.h"

int JSONReader::findArrays(std::string data) {
    int startPos = 0;
    int dataPos = 0;
    int arrays = 0;
    while ((dataPos = data.find("[", startPos)) != std::string::npos) {
        arrays++;
        this->JSarray.openFoundAt.push_back(dataPos);
        startPos = dataPos + 1;
    }
    int size = this->JSarray.openFoundAt.size();

    return arrays;
}

int JSONReader::findClosedArrays(std::string data) {
    int startPos = 0;
    int dataPos = 0;
    int arrays = 0;
    while ((dataPos = data.find("]", startPos)) != std::string::npos) {
        arrays++;
        this->JSarray.closedFoundAt.push_back(dataPos);
        startPos = dataPos + 1;
    }
    int size = this->JSarray.closedFoundAt.size();

    return arrays;
}

int JSONReader::findClosedObjects(std::string data) {
    int startPos = 0;
    int dataPos = 0;
    int closedObjects = 0;
    while ((dataPos = data.find("}", startPos)) != std::string::npos) {
        closedObjects++;
        this->JSobject.closedFoundAt.push_back(dataPos);
        startPos = dataPos + 1;
    }
    int size = this->JSobject.closedFoundAt.size();

    return closedObjects;
}

int JSONReader::findObjects(std::string data) {
    int startPos = 0;
    int dataPos = 0;
    int openObjects = 0;
    while ((dataPos = data.find("{", startPos)) != std::string::npos) {
        openObjects++;
        this->JSobject.openFoundAt.push_back(dataPos);
        startPos = dataPos + 1;
    }
    int size = this->JSobject.openFoundAt.size();

    return openObjects;
}



bool JSONReader::checkJson(std::string data) {
    bool OK = false;
    int openObj = this->findClosedObjects(data);
    int closedObj = this->findObjects(data);
    if (openObj == closedObj) {
        this->SubObjects = openObj;
        int openArr = this->findArrays(data);
        int closedArr = this->findClosedArrays(data);

        if (openArr == closedArr) {
            OK = true;
        } else {
            std::cerr << "ERROR []" << std::endl;
        }
    } else {
        OK = false;
        std::cout << "ERROR {}" << std::endl;
    }
    return OK;
}

void dotNotation(std::string key){
    std::string preDot;
    std::string afterDot;
    if(key.find(".") == std::string::npos){
    //Hier funktion einfügen um daten zu extrahieren.
    } else {

        size_t foundDot = key.find(".");
        preDot = key.substr(0, foundDot);
        afterDot = key.substr(foundDot + 1);

   }
}