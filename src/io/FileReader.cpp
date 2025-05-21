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

void FileReader::readFile(int **&adjacencyMatrix, neighbour **&neighboursList, int &verticesNumber, int &edgesNumber, int& startVertice, int& endVertice) {
    for (int i = 0; i < verticesNumber; i++) {
        delete[] neighboursList[i];
        delete[] adjacencyMatrix[i];
    }
    delete[] neighboursList;
    delete[] adjacencyMatrix;

    std::ifstream file(askForFileName());
    if (!file) {
        std::cout << "File cannot be opened\n";
    }

    std::string line;
    getline(file, line);
    std::stringstream ss(line);
    ss >> edgesNumber >> verticesNumber >> startVertice >> endVertice;
    neighboursList = new neighbour*[verticesNumber];
    adjacencyMatrix = new int*[verticesNumber];

    // Inicjalizacja macierzy i listy
    for (int i = 0; i < verticesNumber; i++) {
        adjacencyMatrix[i] = new int[verticesNumber];
        for (int j = 0; j < verticesNumber; j++) {
            adjacencyMatrix[i][j] = 0;
        }
        neighboursList[i] = nullptr;
    }

    for(int i=0; i<edgesNumber; i++){
        int vertex1, vertex2, weight;
        getline(file, line);
        std::stringstream ss(line);
        ss >> vertex1 >> vertex2 >> weight;

        // Umieszczenie wagi na krawędzi
        adjacencyMatrix[vertex1][vertex2] = weight;

        if (neighboursList[vertex1] == nullptr) {
            neighboursList[vertex1] = new neighbour;
            neighboursList[vertex1]->vertex = vertex2;
            neighboursList[vertex1]->weight = weight;
            neighboursList[vertex1]->nextVertex = nullptr;

        }
        else {
            neighbour* current = neighboursList[vertex1];
            while (current->nextVertex != nullptr) {
                current = current->nextVertex;
            }
            current->nextVertex = new neighbour;
            current->nextVertex->vertex = vertex2;
            current->nextVertex->weight = weight;
            current->nextVertex->nextVertex = nullptr;
        }
        // Drugi wierzchołek bo krawędzie nieskierowane
        if (startVertice < 0) {
            adjacencyMatrix[vertex2][vertex1] = weight;
            if (neighboursList[vertex2] == nullptr) {
                neighboursList[vertex2] = new neighbour;
                neighboursList[vertex2]->vertex = vertex1;
                neighboursList[vertex2]->weight = weight;
                neighboursList[vertex2]->nextVertex = nullptr;
            }
            else {
                neighbour* current = neighboursList[vertex2];
                while (current->nextVertex != nullptr) {
                    current = current->nextVertex;
                }
                current->nextVertex = new neighbour;
                current->nextVertex->vertex = vertex1;
                current->nextVertex->weight = weight;
                current->nextVertex->nextVertex = nullptr;
            }
        }
    }
}
