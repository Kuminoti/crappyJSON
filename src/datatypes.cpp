#include"../include/datatypes/jsondatatypes.h"

int JsonArray::numberOfElements(){
    int startPos = 0;
    int dataPos = 0;
    int elements = 0;
    while ((dataPos = this->JSdata.find(",", startPos)) != std::string::npos) {
        elements++;
        startPos = dataPos + 1;
    }
    return elements +1;
}