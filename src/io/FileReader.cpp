//
// Created by wiktor on 11.05.2025.
//

#include "FileReader.h"

#include <iostream>
#include <fstream>
#include <sstream>

std::string FileReader::askForFileName() {
    std::cout << "! The file should be in the same folder as the .exe file ! (for version running from exe)\n"
            "Please enter the file name: \n";
    std::string fileName;
    std::cin >> fileName;
    return fileName;
}

void FileReader::readFile(int **&adjacencyMatrix, neighbour **&neighboursList, int *&neighboursNumberList, int &verticesNumber, int &edgesNumber, int& startVertice, int& endVertice) {
    for (int i = 0; i < verticesNumber; i++) {
        delete[] neighboursList[i];
        delete[] adjacencyMatrix[i];
    }
    delete[] neighboursList;
    delete[] adjacencyMatrix;
    delete[] neighboursNumberList;

    std::ifstream file(askForFileName());
    if (!file) {
        std::cout << "File cannot be opened\n";
    }

    std::string line;
    getline(file, line);
    std::stringstream ss(line);
    ss >> edgesNumber >> verticesNumber >> startVertice >> endVertice;
    neighboursList = new neighbour*[verticesNumber];
    neighboursNumberList = new int [verticesNumber];
    adjacencyMatrix = new int*[verticesNumber];

    // Inicjalizacja macierzy i listy
    for (int i = 0; i < verticesNumber; i++) {
        adjacencyMatrix[i] = new int[verticesNumber];
        for (int j = 0; j < verticesNumber; j++) {
            adjacencyMatrix[i][j] = 0;
        }
        neighboursNumberList[i] = 0;
        neighboursList[i] = new neighbour[neighboursNumberList[i]];
    }

    for(int i=0; i<edgesNumber; i++){
        int vertex1, vertex2, weight;
        getline(file, line);
        std::stringstream ss(line);
        ss >> vertex1 >> vertex2 >> weight;

        // Umieszczenie wagi na krawędzi
        adjacencyMatrix[vertex1][vertex2] = weight;

        // Dodanie sąsiadów do listy sąsiedztwa poprzez alokację pamięci
        neighboursNumberList[vertex1] +=1;
        auto* newNeighboursList = new neighbour[neighboursNumberList[vertex1]];
        for (int j=0; j<neighboursNumberList[vertex1]-1; j++) {
            newNeighboursList[j] = neighboursList[vertex1][j];
        }
        delete[] neighboursList[vertex1];
        neighboursList[vertex1] = new neighbour[neighboursNumberList[vertex1]];
        for (int j=0; j<neighboursNumberList[vertex1]-1; j++) {
            neighboursList[vertex1][j] = newNeighboursList[j];
        }
        delete[] newNeighboursList;
        neighboursList[vertex1][neighboursNumberList[vertex1]-1].vertex = vertex2;
        neighboursList[vertex1][neighboursNumberList[vertex1]-1].weight = weight;

        if (startVertice < 0) {
            adjacencyMatrix[vertex2][vertex1] = weight;
            // Drugi wierzchołek bo krawędzie nieskierowane
            neighboursNumberList[vertex2] +=1;
            newNeighboursList = new neighbour[neighboursNumberList[vertex2]];
            for (int j=0; j<neighboursNumberList[vertex2]-1; j++) {
                newNeighboursList[j] = neighboursList[vertex2][j];
            }
            delete[] neighboursList[vertex2];
            neighboursList[vertex2] = new neighbour[neighboursNumberList[vertex2]];
            for (int j=0; j<neighboursNumberList[vertex2]-1; j++) {
                neighboursList[vertex2][j] = newNeighboursList[j];
            }
            delete[] newNeighboursList;
            neighboursList[vertex2][neighboursNumberList[vertex2]-1].vertex = vertex1;
            neighboursList[vertex2][neighboursNumberList[vertex2]-1].weight = weight;
        }
    }
}
