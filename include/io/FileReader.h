//
// Created by wiktor on 11.05.2025.
//

#ifndef FILEREADER_H
#define FILEREADER_H
#include <string>

#include "NeighbourStruct.h"


class FileReader {
public:
    static std::string askForFileName();
    static void readFile(int**& adjacencyMatrix, neighbour**& neighboursList, int*& neighboursNumberList, int& verticesNumber, int& edgesNumber, int& startVertice, int& endVertice);
};

#endif //FILEREADER_H
