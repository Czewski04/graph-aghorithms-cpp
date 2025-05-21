//
// Created by wiktor on 11.05.2025.
//

#ifndef MAXIMUMFLOWSOLVER_H
#define MAXIMUMFLOWSOLVER_H
#include <tuple>
#include "NeighbourStruct.h"

class MaximumFlowSolver {
public:
    static std::tuple<int, double> fordFulkersonAlgorithmForMatrix(int** adjacencyMatrix, int verticesNumber, int startVertex, int endVertex);
    static std::tuple<int, double> fordFulkersonAlgorithmForList(neighbour** neighboursList, int verticesNumber, int startVertex, int endVertex);

private:
    static bool dfsFindPathForMatrix(int** residualGraph, int verticesNumber, int source, int sink, int* parent, bool* visited);
    static bool dfsFindPathForList(neighbour** neighboursList, int verticesNumber, int source, int sink, int* parent, bool* visited);
    static void addNeighbourToList(neighbour*& neighbour, int vertex, int capacity);
};

#endif //MAXIMUMFLOWSOLVER_H
