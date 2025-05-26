//
// Created by Wiktor on 25.05.2025.
//

#include <random>
#include <chrono>
#include <iostream>
#include "GraphGenerator.h"
#include "Utilities.h"

void GraphGenerator::generateGraphForMST(int **&adjacencyMatrix, neighbour **&neighboursList, int &verticesNumber, int &edgesNumber, int graphSize, int graphDensity) {
    for (int i = 0; i < verticesNumber; i++) {
        Utilities::deleteLinkedList(neighboursList[i]);
        delete[] adjacencyMatrix[i];
    }
    delete[] neighboursList;
    delete[] adjacencyMatrix;
    //int graphDensity = 0;
   // std::tie(verticesNumber, graphDensity) = askForGraphSize();
    verticesNumber = graphSize;
    bool nearlyFull = false;
    if(graphDensity == 99) {
        nearlyFull=true;
        graphDensity=100;
    }
    int maxEdgesCount = (int)(((double)verticesNumber * (verticesNumber-1)/2.0)*(graphDensity/100.0));
    edgesNumber = maxEdgesCount;

    // Inicjalizacja macierzy i listy
    neighboursList = new neighbour*[verticesNumber];
    adjacencyMatrix = new int*[verticesNumber];
    for (int i = 0; i < verticesNumber; i++) {
        adjacencyMatrix[i] = new int[verticesNumber];
        for (int j = 0; j < verticesNumber; j++) {
            adjacencyMatrix[i][j] = 0;
        }
        neighboursList[i] = nullptr;
    }

    std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> weightDistribution(1,100);
    for(int u=1; u<verticesNumber; u++){
        std::uniform_int_distribution<int> dist(0,u-1);
        int v = dist(gen);
        int w = weightDistribution(gen);
        adjacencyMatrix[u][v] = w;
        adjacencyMatrix[v][u] = w;
        Utilities::addVertexToNeighbourList(neighboursList, u, v, w);
        Utilities::addVertexToNeighbourList(neighboursList, v, u, w);
        maxEdgesCount--;
    }

    std::uniform_int_distribution<int> distVertex(0,verticesNumber-1);
    for(; maxEdgesCount>0; maxEdgesCount--){
        int u = distVertex(gen);
        int v = distVertex(gen);
        while(adjacencyMatrix[u][v]!=0 || u==v){
            u = distVertex(gen);
            v = distVertex(gen);
        }
        int w = weightDistribution(gen);
        adjacencyMatrix[u][v] = w;
        adjacencyMatrix[v][u] = w;
        Utilities::addVertexToNeighbourList(neighboursList, u, v, w);
        Utilities::addVertexToNeighbourList(neighboursList, v, u, w);
    }
    if(nearlyFull){
        int edgesToDelete = (int)(0.01 * edgesNumber);
        for(;edgesToDelete>0; edgesToDelete--){
            int u = distVertex(gen);
            int v = distVertex(gen);
            while(adjacencyMatrix[u][v]==0 || u==v){
                u = distVertex(gen);
                v = distVertex(gen);
            }
            adjacencyMatrix[u][v] = 0;
            adjacencyMatrix[v][u] = 0;
            removeNeighbourFromList(neighboursList[u], v);
            removeNeighbourFromList(neighboursList[v], u);
            edgesNumber--;
        }
    }
}

void GraphGenerator::removeNeighbourFromList(neighbour*& head, int targetVertex) {
    if (head == nullptr) return;

    // Jeśli pierwszy element to cel
    if (head->vertex == targetVertex) {
        neighbour* temp = head;
        head = head->nextVertex;
        delete temp;
        return;
    }

    // Szukanie dalej
    neighbour* current = head;
    while (current->nextVertex != nullptr && current->nextVertex->vertex != targetVertex) {
        current = current->nextVertex;
    }

    // Jeśli znaleziono i można usunąć
    if (current->nextVertex != nullptr) {
        neighbour* temp = current->nextVertex;
        current->nextVertex = current->nextVertex->nextVertex;
        delete temp;
    }
}


std::tuple<int, int> GraphGenerator::askForGraphSize() {
    int size = 0, density = 0;
    std::cout<<"Enter the number of vertices in the graph: "<<"\n";
    std::cin>>size;
    while(density<20){
        std::cout<<"Enter the percentage of graph density: (should be: >=20%)"<<"\n";
        std::cin>>density;
    }
    return std::make_tuple(size, density);
}

void GraphGenerator::generateGraphForShortestPathAndMaxFlow(int **&adjacencyMatrix, neighbour **&neighboursList, int &verticesNumber, int &edgesNumber, int &startVertex, int &endVertex, int graphSize, int graphDensity) {
    for (int i = 0; i < verticesNumber; i++) {
        Utilities::deleteLinkedList(neighboursList[i]); // <--- TUTAJ ZMIANA: Użyj funkcji do zwalniania listy
        delete[] adjacencyMatrix[i];         // Poprawnie zwalnia wiersz macierzy
    }
    delete[] neighboursList; // Zwalnia tablicę wskaźników (pierwszy poziom alokacji)
    delete[] adjacencyMatrix; // Zwalnia tablicę wskaźników (pierwszy poziom alokacji)

    startVertex = 0;
    //int graphDensity = 0;
    verticesNumber = graphSize;
    //std::tie(verticesNumber, graphDensity) = askForGraphSize();
    bool nearlyFull = false;
    if(graphDensity == 99) {
        nearlyFull=true;
        graphDensity=100;
    }
    int maxEdgesCount = (int)((verticesNumber * (verticesNumber-1))*(graphDensity/100.0));
    edgesNumber = maxEdgesCount;
    bool* visited = new bool[verticesNumber];

    // Inicjalizacja macierzy i listy
    neighboursList = new neighbour*[verticesNumber];
    adjacencyMatrix = new int*[verticesNumber];
    for (int i = 0; i < verticesNumber; i++) {
        adjacencyMatrix[i] = new int[verticesNumber];
        for (int j = 0; j < verticesNumber; j++) {
            adjacencyMatrix[i][j] = 0;
        }
        neighboursList[i] = nullptr;
        visited[i] = false;
    }

    visited[0] = true;
    int mstVertices = 1;

    std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> weightDistribution(1,100);
    std::uniform_int_distribution<int> vertexDistribution(0, verticesNumber-1);

    while(mstVertices<verticesNumber){
        int u = vertexDistribution(gen);
        if(visited[u]){
            int v = vertexDistribution(gen);
            if(!visited[v]){
                int w = weightDistribution(gen);
                adjacencyMatrix[u][v] = w;
                Utilities::addVertexToNeighbourList(neighboursList, u, v, w);
                visited[v] = true;
                mstVertices++;
                maxEdgesCount--;
            }
        }
    }

    std::uniform_int_distribution<int> distVertex(0,verticesNumber-1);
    for(; maxEdgesCount>0; maxEdgesCount--){
        int u = distVertex(gen);
        int v = distVertex(gen);
        while(adjacencyMatrix[u][v]!=0 || u==v){
            u = distVertex(gen);
            v = distVertex(gen);
        }
        int w = weightDistribution(gen);
        adjacencyMatrix[u][v] = w;
        Utilities::addVertexToNeighbourList(neighboursList, u, v, w);
    }

    do {
        endVertex = vertexDistribution(gen);
    }while (endVertex == startVertex);
    if(nearlyFull){
        int edgesToDelete = (int)(0.01 * edgesNumber);
        for(;edgesToDelete>0; edgesToDelete--){
            int u = distVertex(gen);
            int v = distVertex(gen);
            while(adjacencyMatrix[u][v]==0 || u==v){
                u = distVertex(gen);
                v = distVertex(gen);
            }
            adjacencyMatrix[u][v] = 0;
            removeNeighbourFromList(neighboursList[u], v);
            edgesNumber--;
        }
    }
}
