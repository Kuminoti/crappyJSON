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

    for (int i = 0; i < size; i++) {
        std::cout << "closed" << this->JSarray.openFoundAt[i] << std::endl;
    }
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

    for (int i = 0; i < size; i++) {
        std::cout << "closed" << this->JSarray.closedFoundAt[i] << std::endl;
    }
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

    for (int i = 0; i < size; i++) {
        std::cout << "closed" << this->JSobject.closedFoundAt[i] << std::endl;
    }
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

    for (int i = 0; i < size; i++) {
        std::cout << "open" << this->JSobject.openFoundAt[i] << std::endl;
    }

    return openObjects;
}

std::string JSONReader::extractJSobject(std::string data) {
    int vectorSize = this->JSobject.closedFoundAt.size();
    int lastIndex = this->JSobject.closedFoundAt.size() - 1;
    std::string output;
    for (size_t i = 1; i < vectorSize; i++) {
        int lastPos = this->JSobject.closedFoundAt[lastIndex];
        int first = this->JSobject.openFoundAt[i];
        int last = lastPos - first;
        output = data.substr(first, last);

        this->obj.push_back(JsonObject::createObj(output));
        lastIndex--;
    }

    for (size_t i = 0; i < vectorSize - 1; i++) {
        std::cout << "\n\n\"your SubObjects" << this->obj[i].JSdata
                  << std::endl;
    }
    return output;
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
            std::cout << "jubARR" << std::endl;
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