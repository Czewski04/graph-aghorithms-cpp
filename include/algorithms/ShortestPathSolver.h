//
// Created by wiktor on 11.05.2025.
//

#ifndef SHORTESTPATHSOLVER_H
#define SHORTESTPATHSOLVER_H
#include <tuple>

#include "EdgeStruct.h"
#include "NeighbourStruct.h"


class ShortestPathSolver {
public:
    static std::tuple<neighbour**, int*, double> dijkstrasAlgorithmForMatrix(int** adjacencyMatrix, int verticesNumber, int startVertice);
    static std::tuple<neighbour**, int*, double> dijkstrasAlgorithmForList(neighbour** neighboursList, int verticesNumber, int startVertice);
    static std::tuple<neighbour**, int*, double> bellmanFordAlgorithmForMatrix(int** adjacencyMatrix, int verticesNumber, int startVertice);
    static std::tuple<neighbour**, int*, double> bellmanFordAlgorithmForList(neighbour** neighboursList, int verticesNumber, int startVertice);
};



#endif //SHORTESTPATHSOLVER_H
