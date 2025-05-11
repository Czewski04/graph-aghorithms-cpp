//
// Created by wiktor on 11.05.2025.
//

#include "GraphAlgorithmsApp.h"

#include <iomanip>
#include <iostream>

#include "FileReader.h"

[[noreturn]] void GraphAlgorithmsApp::runApp() {
    showMenu();
    switch (getUserChoice()) {
        case 1:
            while (true) {
                showMSTMenu();
                switch (getUserChoice()) {
                    case 1:
                        FileReader::readFile(adjacencyMatrix, neighboursList, neighboursNumberList, verticesNumber, edgesNumber);
                        break;
                    case 2:
                        ;
                    case 3:
                        showAdjacencyList();
                        showNeighboursList();
                        break;
                    default: ;
                }
            }
            break;
        case 2:
            showShortestPathMenu();
            break;
        case 3:
            showMaxFlowMenu();
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
        for (int j=0; j<neighboursNumberList[i]; j++) {
            std::cout<<"("<<neighboursList[i][j].vertex<<", "<<neighboursList[i][j].weight<<") ";
        }
        std::cout<<"\n";
    }
    std::cout<<"\n";
}

void GraphAlgorithmsApp::showAdjacencyList() {
    // Nagłówki kolumn
    std::cout << "   "; // Dwa spacje na wyrównanie z nagłówkami wierszy
    for (int i = 0; i < verticesNumber; ++i) {
        std::cout << std::setw(4) << i << " ";
    }
    std::cout << "\n";

    // Linia oddzielająca nagłówki od zawartości
    std::cout << "----";
    for (int i = 0; i < verticesNumber; ++i) {
        std::cout << "-----";
    }
    std::cout << "\n";

    // Zawartość macierzy z nagłówkami wierszy
    for (int i = 0; i < verticesNumber; ++i) {
        std::cout << std::setw(2) << i << "|"; // Nagłówek wiersza
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
