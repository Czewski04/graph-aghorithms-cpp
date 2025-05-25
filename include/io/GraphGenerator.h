//
// Created by Wiktor on 25.05.2025.
//

#ifndef GRAPHGENERATOR_H
#define GRAPHGENERATOR_H

#include <tuple>
#include "NeighbourStruct.h"

class GraphGenerator {
public:
    static void generateGraphForMST(int**& adjacencyMatrix, neighbour**& neighboursList, int& verticesNumber, int& edgesNumber);
    static void generateGraphForShortestPathAndMaxFlow(int**& adjacencyMatrix, neighbour**& neighboursList, int& verticesNumber, int& edgesNumber, int& startVertex, int& endVertex);
private:
    static std::tuple<int, int> askForGraphSize();
    static void addVerticeToNeighbourList(neighbour **&neighboursList, int u, int v, int w);
};

#endif //GRAPHGENERATOR_H
