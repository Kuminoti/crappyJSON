#include"include/json.h"
#include"include/datatypes/JsonReader.h"

Json json = Json::readFromFile("jsontest/test.json");


JSONReader jsonreader("LOL");
bool lol = jsonreader.checkJson(json.getData());


int main(int argc, char** argv) {
    if(lol){
        std::string test = jsonreader.extractJSarray(json.getData());
        std::cout<<"das ist ein test:"<<test;
    }else{
        std::cout<<"OPFAA*2";
    }

    
    return 0;
}