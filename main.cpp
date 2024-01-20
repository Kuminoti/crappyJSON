#include"include/json.h"

 Json json = Json::readFromFile("jsontest/test.json");

std::string textInput;

int main(int argc, char** argv) {
    while (true){
    std::cout<<"Key wählen"<<std::endl;
    // std::cout<<json.getValue("schinken")<<std::endl;
    std::cin>>textInput;
    std::cout<<json.getValue(textInput)<<std::endl;
    }
    
    
    
    return 0;
}