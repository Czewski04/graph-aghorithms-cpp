//
// Created by wiktor on 11.05.2025.
//

#ifndef SHORTESTPATHSOLVER_H
#define SHORTESTPATHSOLVER_H
#include "NeighbourStruct.h"
#include <tuple>

class ShortestPathSolver {
public:
    static std::tuple<neighbour**, int*, double> dijkstrasAlgorithmForMatrix(int** adjacencyMatrix, int verticesNumber, int startVertex);
    static std::tuple<neighbour**, int*, double> dijkstrasAlgorithmForList(neighbour** neighboursList, int verticesNumber, int startVertex);
    static std::tuple<neighbour**, int*, double> bellmanFordAlgorithmForMatrix(int** adjacencyMatrix, int verticesNumber, int startVertex);

    static void buildPathsList(int verticesNumber, int *parent, neighbour **paths);

    static std::tuple<neighbour**, int*, double> bellmanFordAlgorithmForList(neighbour** neighboursList, int verticesNumber, int startVertex);
};



#endif //SHORTESTPATHSOLVER_H
