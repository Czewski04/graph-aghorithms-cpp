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
    static std::tuple<Edge*, int, int, double> dijkstrasAlgorithmForMatrix(int** adjacencyMatrix, int verticesNumber);
    static std::tuple<Edge*, int, int, double> dijkstrasAlgorithmForList(neighbour** neighboursList, int* neighboursNumberList, int verticesNumber);
    static std::tuple<Edge*, int, int, double> bellmanFordAlgorithmForMatrix(int** adjacencyMatrix, int verticesNumber);
    static std::tuple<Edge*, int, int, double> bellmanFordAlgorithmForList(neighbour** neighboursList, int* neighboursNumberList, int verticesNumber);
};



#endif //SHORTESTPATHSOLVER_H
