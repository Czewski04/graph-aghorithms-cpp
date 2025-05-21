//
// Created by wiktor on 11.05.2025.
//

#ifndef MAXIMUMFLOWSOLVER_H
#define MAXIMUMFLOWSOLVER_H
#include <tuple>
#include "../data_structures/NeighbourStruct.h"

class MaximumFlowSolver {
public:
    static std::tuple<int, double> fordFulkersonDfsAlgorithmForMatrix(int** adjacencyMatrix, int verticesNumber, int startVertex, int endVertex);
    static std::tuple<int, double> fordFulkersonDfsAlgorithmForList(neighbour** neighboursList, int verticesNumber, int startVertex, int endVertex);
    static std::tuple<int, double> fordFulkersonBfsAlgorithmForMatrix(int** adjacencyMatrix, int verticesNumber, int startVertex, int endVertex);
    static std::tuple<int, double> fordFulkersonBfsAlgorithmForList(neighbour** neighboursList, int verticesNumber, int startVertex, int endVertex);

private:
    static bool dfsFindPathForMatrix(int** residualGraph, int verticesNumber, int source, int sink, int* parent, bool* visited);
    static bool dfsFindPathForList(neighbour** residualGraph, int verticesNumber, int source, int sink, int* parent, bool* visited);
    static bool bfsFindPathForMatrix(int** residualGraph, int verticesNumber, int source, int sink, int* parent, bool* visited);
    static bool bfsFindPathForList(neighbour** residualGraph, int verticesNumber, int source, int sink, int* parent, bool* visited);
    static void addNeighbourToList(neighbour*& neighbour, int vertex, int capacity);
    static void deleteLinkedList(neighbour* mainNeighbour);
};

#endif //MAXIMUMFLOWSOLVER_H
