//
// Created by wiktor on 11.05.2025.
//

#ifndef MSTSOLVER_H
#define MSTSOLVER_H
#include "EdgeStruct.h"
#include "NeighbourStruct.h"
#include <tuple>

class MSTSolver {
public:
   static std::tuple<Edge*, int, int, double> primsAlgorithmForMatrix(int** adjacencyMatrix, int verticesNumber);
   static std::tuple<Edge*, int, int, double> primsAlgorithmForList(neighbour** neighboursList, int verticesNumber);
   static std::tuple<Edge*, int, int, double> kruskalsAlgorithmForMatrix(int** adjacencyMatrix, int verticesNumber);
   static std::tuple<Edge*, int, int, double> kruskalsAlgorithmForList(neighbour** neighboursList, int verticesNumber);

private:
   static int extractEdgesFromNeighboursList(neighbour** neighboursList, int verticesNumber, Edge*& edgesOut);
   static void sortEdgesByWeight(Edge* edges, int begin, int end);
   static int extractEdgesFromMatrix(int** adjacencyMatrix, int verticesNumber, Edge*& edgesOut);
   static void swapEdges(Edge* edges, int i, int j);
};

#endif //MSTSOLVER_H
