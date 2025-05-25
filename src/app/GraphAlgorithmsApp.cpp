//
// Created by wiktor on 11.05.2025.
//

#include "GraphAlgorithmsApp.h"
#include "FileReader.h"
#include "MSTSolver.h"
#include "ShortestPathSolver.h"
#include "MaximumFlowSolver.h"
#include "GraphGenerator.h"
#include <iomanip>
#include <iostream>


[[noreturn]] void GraphAlgorithmsApp::runApp() {
    showMenu();
    switch (getUserChoice()) {
        case 1:
            while (true) {
                showMSTMenu();
                switch (getUserChoice()) {
                    case 1:
                        FileReader::readFile(adjacencyMatrix, neighboursList, verticesNumber, edgesNumber, startVertex, endVertex);
                        showAdjacencyMatrix();
                        showNeighboursList();
                        break;
                    case 2:
                        GraphGenerator::generateGraphForMST(adjacencyMatrix, neighboursList, verticesNumber, edgesNumber);
                        showAdjacencyMatrix();
                        showNeighboursList();
                    case 3:
                        showAdjacencyMatrix();
                        showNeighboursList();
                        break;
                    case 4:
                        std::tie(MSTEdgesList, MSTEdgesCount, MSTWeight, operationTime) = MSTSolver::primsAlgorithmForMatrix(adjacencyMatrix, verticesNumber);
                        std::cout<<"Matrix: \n";
                        showMSTResults();
                        std::tie(MSTEdgesList, MSTEdgesCount, MSTWeight, operationTime) = MSTSolver::primsAlgorithmForList(neighboursList, verticesNumber);
                        std::cout<<"List: \n";
                        showMSTResults();
                        break;
                    case 5:
                        std::tie(MSTEdgesList, MSTEdgesCount, MSTWeight, operationTime) = MSTSolver::kruskalsAlgorithmForMatrix(adjacencyMatrix, verticesNumber);
                        std::cout<<"Matrix: \n";
                        showMSTResults();
                        std::tie(MSTEdgesList, MSTEdgesCount, MSTWeight, operationTime) = MSTSolver::kruskalsAlgorithmForList(neighboursList, verticesNumber);
                        std::cout<<"List: \n";
                        showMSTResults();
                        break;
                    default: ;
                }
            }
            break;
        case 2:
            while (true) {
                showShortestPathMenu();
                switch (getUserChoice()) {
                    case 1:
                        FileReader::readFile(adjacencyMatrix, neighboursList, verticesNumber, edgesNumber, startVertex, endVertex);
                        showAdjacencyMatrix();
                        showNeighboursList();
                        break;
                    case 2:
                        GraphGenerator::generateGraphForShortestPathAndMaxFlow(adjacencyMatrix, neighboursList, verticesNumber, edgesNumber, startVertex, endVertex);
                        showAdjacencyMatrix();
                        showNeighboursList();
                    case 3:
                        showAdjacencyMatrix();
                        showNeighboursList();
                        break;
                    case 4:
                        std::tie(shortestPathsList, shortestPathsDistances, operationTime) = ShortestPathSolver::dijkstrasAlgorithmForMatrix(adjacencyMatrix, verticesNumber, startVertex);
                        std::cout<<"Matrix: \n";
                        showShortestPathsResult();
                        std::tie(shortestPathsList, shortestPathsDistances, operationTime) = ShortestPathSolver::dijkstrasAlgorithmForList(neighboursList, verticesNumber, startVertex);
                        std::cout<<"List: \n";
                        showShortestPathsResult();
                        break;
                    case 5:
                        std::tie(shortestPathsList, shortestPathsDistances, operationTime) = ShortestPathSolver::bellmanFordAlgorithmForMatrix(adjacencyMatrix, verticesNumber, startVertex);
                        std::cout<<"Matrix: \n";
                        showShortestPathsResult();
                        std::tie(shortestPathsList, shortestPathsDistances, operationTime) = ShortestPathSolver::bellmanFordAlgorithmForList(neighboursList, verticesNumber, startVertex);
                        std::cout<<"List: \n";
                        showShortestPathsResult();
                        break;
                    default: ;
                }
            }
            break;
        case 3:
            while (true) {
                showMaxFlowMenu();
                switch (getUserChoice()) {
                    case 1:
                        FileReader::readFile(adjacencyMatrix, neighboursList, verticesNumber, edgesNumber, startVertex, endVertex);
                        showAdjacencyMatrix();
                        showNeighboursList();
                        break;
                    case 2:
                        GraphGenerator::generateGraphForShortestPathAndMaxFlow(adjacencyMatrix, neighboursList, verticesNumber, edgesNumber, startVertex, endVertex);
                        showAdjacencyMatrix();
                        showNeighboursList();
                    case 3:
                        showAdjacencyMatrix();
                        showNeighboursList();
                        break;
                    case 4:
                        std::tie(maxFlow, operationTime) = MaximumFlowSolver::fordFulkersonDfsAlgorithmForMatrix(adjacencyMatrix, verticesNumber, startVertex, endVertex);
                        std::cout<<"Matrix: \n";
                        showMaxFlowResult();
                        std::tie(maxFlow, operationTime) = MaximumFlowSolver::fordFulkersonDfsAlgorithmForList(neighboursList, verticesNumber, startVertex, endVertex);
                        std::cout<<"List: \n";
                        showMaxFlowResult();
                        break;
                    case 5:
                        std::tie(maxFlow, operationTime) = MaximumFlowSolver::fordFulkersonBfsAlgorithmForMatrix(adjacencyMatrix, verticesNumber, startVertex, endVertex);
                        std::cout<<"Matrix: \n";
                        showMaxFlowResult();
                        std::tie(maxFlow, operationTime) = MaximumFlowSolver::fordFulkersonBfsAlgorithmForList(neighboursList, verticesNumber, startVertex, endVertex);
                        std::cout<<"List: \n";
                        showMaxFlowResult();
                        break;
                    default: ;
                }
            }
            break;
        default: ;
    }
}

int GraphAlgorithmsApp::getUserChoice() {
    int userChoice=0;
    std::cin >> userChoice;
    return userChoice;
}

void GraphAlgorithmsApp::showNeighboursList() {
    for (int i=0; i<verticesNumber; i++) {
        std::cout<<i<<". ";
        neighbour* current = neighboursList[i];
        while (current!=nullptr) {
            std::cout<<"("<<current -> vertex<<", "<<current -> weight<<") ";
            current = current -> nextVertex;
        }
        std::cout<<"\n";
    }
    std::cout<<"\n";
}

void GraphAlgorithmsApp::showAdjacencyMatrix() {
    std::cout << "   ";
    for (int i = 0; i < verticesNumber; ++i) {
        std::cout << std::setw(4) << i << " ";
    }
    std::cout << "\n";

    std::cout << "----";
    for (int i = 0; i < verticesNumber; ++i) {
        std::cout << "-----";
    }
    std::cout << "\n";

    for (int i = 0; i < verticesNumber; ++i) {
        std::cout << std::setw(2) << i << "|";
        for (int j = 0; j < verticesNumber; ++j) {
            std::cout << std::setw(4) << adjacencyMatrix[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void GraphAlgorithmsApp::showMenu() {
    std::cout<<"1. Minimum Spanning Tree Problem.\n"<<
        "2. Shortest Path Problem.\n"
        "3. Maximum Flow Problem.\n";
}

void GraphAlgorithmsApp::showMSTMenu() {
    std::cout<<"1. Read graph from file.\n"<<
        "2. Generate graph.\n"
        "3. Show graph.\n"
        "4. Prim's algorithm\n"
        "5. Kruskal's algorithm\n";
}

void GraphAlgorithmsApp::showShortestPathMenu() {
    std::cout<<"1. Read graph from file.\n"<<
        "2. Generate graph.\n"
        "3. Show graph.\n"
        "4. Dijkstra's algorithm\n"
        "5. Bellman-Ford algorithm\n";
}

void GraphAlgorithmsApp::showMaxFlowMenu() {
    std::cout<<"1. Read graph from file.\n"<<
        "2. Generate graph.\n"
        "3. Show graph.\n"
        "4. DFS Ford-Fulkerson algorithm\n"
        "5. BFS Ford-Fulkerson algorithm\n";
}

void GraphAlgorithmsApp::showMSTResults() {
    for (int i = 0; i < MSTEdgesCount; ++i) {
        std::cout<<MSTEdgesList[i].u<<" -- "<<MSTEdgesList[i].v<<"  |weight: "<<MSTEdgesList[i].weight<<"\n";
    }
    std::cout<<"Summary MST weight: "<<MSTWeight<<"\n";
    std::cout<<"Operation Time: "<<operationTime<<"\n";
    std::cout<<"\n\n";
}

void GraphAlgorithmsApp::showShortestPathsResult() {
    for (int i=0; i<verticesNumber; i++) {
        neighbour* current = shortestPathsList[i];
        while (current!=nullptr) {
            std::cout<<current -> vertex<<" -> ";
            current = current -> nextVertex;
        }
        std::cout<<"  total distance: "<<shortestPathsDistances[i];
        std::cout<<"\n";
    }
    std::cout<<"Operation Time: "<<operationTime<<"\n";
    std::cout<<"\n\n";
}

void GraphAlgorithmsApp::showMaxFlowResult() {
    std::cout<<"Maximum graph flow from "<<startVertex<<"to "<<endVertex<<": "<<maxFlow<<"\n";
    std::cout<<"Operation Time: "<<operationTime<<"\n";
    std::cout<<"\n\n";
}
