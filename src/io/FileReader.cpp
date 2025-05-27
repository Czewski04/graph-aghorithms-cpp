//
// Created by wiktor on 11.05.2025.
//

#include "FileReader.h"
#include "Utilities.h"

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

void FileReader::readFile(int **&adjacencyMatrix, neighbour **&neighboursList, int &verticesNumber, int &edgesNumber, int& startVertex, int& endVertex) {
    // Sprzątanie
    for (int i = 0; i < verticesNumber; i++) {
        Utilities::deleteLinkedList(neighboursList[i]);
        delete[] adjacencyMatrix[i];
    }
    delete[] neighboursList;
    delete[] adjacencyMatrix;

    // Zapytanie o nazwę pliku
    std::ifstream file(askForFileName());
    if (!file) {
        std::cout << "File cannot be opened\n";
    }

    // Wczytanie pierwszej linii
    std::string line;
    getline(file, line);
    std::stringstream ss(line);
    ss >> edgesNumber >> verticesNumber >> startVertex >> endVertex;
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

    // Dodanie wszystkich wierzchołków
    for(int i=0; i<edgesNumber; i++){
        int vertex1, vertex2, weight;
        getline(file, line);
        std::stringstream ss(line);
        ss >> vertex1 >> vertex2 >> weight;

        // Umieszczenie wagi na krawędzi
        adjacencyMatrix[vertex1][vertex2] = weight;
        Utilities::addVertexToNeighbourList(neighboursList, vertex1, vertex2, weight);
        // Drugi wierzchołek, bo krawędzie nieskierowane
        if (startVertex < 0) {
            adjacencyMatrix[vertex2][vertex1] = weight;
            Utilities::addVertexToNeighbourList(neighboursList, vertex2, vertex1, weight);
        }
    }
}
