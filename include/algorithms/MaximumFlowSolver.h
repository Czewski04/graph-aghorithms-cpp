//
// Created by wiktor on 11.05.2025.
//

#ifndef MAXIMUMFLOWSOLVER_H
#define MAXIMUMFLOWSOLVER_H
#include <tuple>
#include "NeighbourStruct.h"

class MaximumFlowSolver {
public:
    static std::tuple<int, double, int**> fordFulkersonDfsAlgorithmForMatrix(int** adjacencyMatrix, int verticesNumber, int startVertex, int endVertex);
    static std::tuple<int, double, neighbour**> fordFulkersonDfsAlgorithmForList(neighbour** neighboursList, int verticesNumber, int startVertex, int endVertex);
    static std::tuple<int, double, int**> fordFulkersonBfsAlgorithmForMatrix(int** adjacencyMatrix, int verticesNumber, int startVertex, int endVertex);
    static std::tuple<int, double, neighbour**> fordFulkersonBfsAlgorithmForList(neighbour** neighboursList, int verticesNumber, int startVertex, int endVertex);

private:
    static bool dfsFindPathForMatrix(int** residualGraph, int verticesNumber, int source, int sink, int* parent, bool* visited);
    static bool dfsFindPathForList(neighbour** residualGraph, int verticesNumber, int source, int sink, int* parent, bool* visited, neighbour** pathEdges);
    static bool bfsFindPathForMatrix(int** residualGraph, int verticesNumber, int source, int sink, int* parent, bool* visited);
    static bool bfsFindPathForList(neighbour** residualGraph, int verticesNumber, int source, int sink, int* parent, bool* visited, neighbour** pathEdges);
    static void addResidualEdge(neighbour*& headU, neighbour*& headV, int u, int v, int capacity, neighbour* originalEdgeLink);
};

#endif //MAXIMUMFLOWSOLVER_H
