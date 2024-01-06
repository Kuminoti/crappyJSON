#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#ifndef JSONDATATYPES_H
#define JSONDATATYPES_H

class JsonArray {
   private:
    std::string key;
    bool subArray;
    int numberOfElements;
    public:
    std::vector<int> openFoundAt;
    std::vector<int> closedFoundAt;

   public:
    std::string data;
    std::string getByIndex(int index);

    int getIndex(std::string data);

    JsonArray(){
        std::cout<<"lol";
    }
};

class JsonObject {
   public:
    std::string key;
    std::string JSdata;
    std::vector<int> openFoundAt;
    std::vector<int> closedFoundAt;
    JsonObject(){
        std::cout<<"LOL";
    }
    static JsonObject createObj(std::string data){
        return JsonObject(data);
    }
    JsonObject(std::string data){
        this->JSdata = data;
    }
    private:
    
};

#endif