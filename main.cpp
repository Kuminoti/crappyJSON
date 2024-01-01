#include "include/json.h"

std::string input;

int main(int argc, char** argv) {
    Json json = Json::readFromFile("jsontest/test.json");
    std::cout << "\ndie Json daten\n " << json.getData() << std::endl;

    return 0;
}