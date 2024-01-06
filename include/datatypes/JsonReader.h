#pragma once

#ifndef JSONREADER_H
#define JSONREADER_H
#include"jsondatatypes.h"

class JSONReader{

private:
    int SubObjects;
    JsonArray JSarray;
    JsonObject JSobject;
    std::vector<JsonObject> obj; 
    std::vector<JsonArray> arr;

    int findClosedObjects(std::string data);
    int findObjects(std::string data);
    int findArrays(std::string data);
    int findClosedArrays(std::string data);

public:
    JSONReader(std::string lol) {
        std::cout<<lol<<std::endl;
        
    }
    bool checkJson(std::string data);
    std::string extractJSobject(std::string data);
    std::string extractJSarray(std::string data);
};

#endif