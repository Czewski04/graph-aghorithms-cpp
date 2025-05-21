//
// Created by wiktor on 11.05.2025.
//

#ifndef GRAPHALGORITHMSAPP_H
#define GRAPHALGORITHMSAPP_H
#include "EdgeStruct.h"
#include "NeighbourStruct.h"


class GraphAlgorithmsApp {
public:
        [[noreturn]]void runApp();
private:
        double lastOperationTime = 0;
        neighbour** neighboursList = nullptr;
        int** adjacencyMatrix = nullptr;
        int* neighboursNumberList = nullptr;
        int verticesNumber = 0;
        int edgesNumber = 0;
        int startVertice = -1;
        int endVertice = -1;

        double operationTime =0.0;
        int MSTWeight = 0;
        int MSTEdgesCount = 0;
        Edge* MSTEdgesList = nullptr;


        static int getUserChoice();
        void showNeighboursList();
        void showAdjacencyList();
        void showMSTResults();

        static void showMenu();
        static void showMSTMenu();
        static void showShortestPathMenu();
        static void showMaxFlowMenu();
};



#endif //GRAPHALGORITHMSAPP_H
