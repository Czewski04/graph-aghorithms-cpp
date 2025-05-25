//
// Created by Wiktor on 25.05.2025.
//

#include <random>
#include <chrono>
#include <iostream>
#include "GraphGenerator.h"

void GraphGenerator::generateGraphForMST(int **&adjacencyMatrix, neighbour **&neighboursList, int &verticesNumber, int &edgesNumber) {
    int graphDensity = 0;
    std::tie(verticesNumber, graphDensity) = askForGraphSize();
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
        addVerticeToNeighbourList(neighboursList, u, v, w);
        addVerticeToNeighbourList(neighboursList, v, u, w);
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
        addVerticeToNeighbourList(neighboursList, u, v, w);
        addVerticeToNeighbourList(neighboursList, v, u, w);
    }
}

void GraphGenerator::addVerticeToNeighbourList(neighbour **&neighboursList, int u, int v, int w) {
    if (neighboursList[u] == nullptr) {
        neighboursList[u] = new neighbour;
        neighboursList[u]->vertex = v;
        neighboursList[u]->weight = w;
        neighboursList[u]->nextVertex = nullptr;

    }
    else {
        neighbour* current = neighboursList[u];
        while (current->nextVertex != nullptr) {
            current = current->nextVertex;
        }
        current->nextVertex = new neighbour;
        current->nextVertex->vertex = v;
        current->nextVertex->weight = w;
        current->nextVertex->nextVertex = nullptr;
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

void GraphGenerator::generateGraphForShortestPathAndMaxFlow(int **&adjacencyMatrix, neighbour **&neighboursList, int &verticesNumber, int &edgesNumber, int &startVertex, int &endVertex) {
    startVertex = 0;
    int graphDensity = 0;
    std::tie(verticesNumber, graphDensity) = askForGraphSize();
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
                addVerticeToNeighbourList(neighboursList, u, v, w);
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
        addVerticeToNeighbourList(neighboursList, u, v, w);
    }
    endVertex = vertexDistribution(gen);
}
