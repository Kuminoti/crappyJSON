#pragma once

#include "jsondatatypes.h"

#ifndef JSONREADER_H
#define JSONREADER_H







// class JsonReader {
//    public:

    

//         int findSymbols (std::string Content, char* symbol){
//         int foundSymbols = 0;
//         int startPos = 0;
//         int dataPos;
//         while ((dataPos = Content.find(symbol, startPos)) !=
//                std::string::npos) {
//             if (symbol == "{") {
//                 foundSymbols++;
//                 this->dataTypes.Objects.openFoundAt.push_back(dataPos);
//                 startPos = dataPos + 1;
//             } else if (symbol == "}") {
//                 foundSymbols++;
//                 this->dataTypes.Objects.closedFoundAt.push_back(dataPos);
//                 startPos = dataPos + 1;
//             } else if (symbol == "[") {
//                 foundSymbols++;
//                 this->dataTypes.arrays.closedFoundAt.push_back(dataPos);
//                 startPos = dataPos + 1;
//             } else if (symbol == "]") {
//                 foundSymbols++;
//                 dataTypes.arrays.closedFoundAt.push_back(dataPos);
//                 startPos = dataPos + 1;
//             }
//         }

//         return foundSymbols;
//     }
//     int openBraces;
//     int closedBraces;
//     int openSqare;
//     int closedSquare;
//     int anfz;  // ""

//     std::string leftOver;

//     std::vector<JsonObject> ObjectsVec;
//     std::vector<JsonPrimitivs> PrimitivsVec;
//     std::vector<JsonArray> ArraysVec;

//     void extractArray(JsonArray array) {}

//     void extractJSONObject(std::string object) {
//         int lastBrace = this->dataTypes.Objects.closedFoundAt.size() -1;
//         std::vector<int> subObjPosOpen = this->dataTypes.Objects.openFoundAt;
//         std::string foundObject;
//         for (size_t i = 0; i < lastBrace; i++){
//             foundObject = object.substr(subObjPosOpen[i],lastBrace);
//             JsonObject newobject(object);
//             this->ObjectsVec.push_back(newobject);
//             lastBrace--;
//         }
        

        
//     }

//    public:
//     DataTypes dataTypes;

//     void extractData(std::string Content) {
//         this->openBraces = findSymbols(Content, "{");
//         this->closedBraces = findSymbols(Content, "}");
//         if(openBraces == closedBraces){
//             extractJSONObject(Content);
//         }

//         this->openSqare = findSymbols(Content, "[");
//         this->closedSquare = findSymbols(Content, "]");
//         this->anfz = findSymbols(Content, "\"");
        

        
//     }
// };



/*
Json constructor -> extractData -> extractObjects
*/
#endif