#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#ifndef JSONDATATYPES_H
#define JSONDATATYPES_H

std::string testObject = "\"Key\":{\n \"LOL\":420}";

class JsonObject {
   private:
   protected:
    size_t nestings;
    size_t primitiv;
    size_t numObjs;
    size_t numArrays;

    std::vector<std::string> subObjects;
    std::vector<std::string> subArrays;

    int lenght;
    std::string value;
    std::string key;
    std::string content;
                      
    std::string findNestedValue(std::string objectPath) {
        size_t startPos = 1;
        size_t numberOfObjects = 0;
    }

   public:
};

class JsonArray {
   private:
   protected:
    std::vector<std::string> subObjects;
    std::vector<std::string> subArray;

    size_t nestings;
    size_t elements;
    size_t primitiv;
    size_t numObjs;
    size_t numArrays;

    int lenght;
    std::string content;

    std::string findIndex(std::string arrayPath, int index) {}

   public:
};

#endif