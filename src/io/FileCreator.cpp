//
// Created by Wiktor on 25.05.2025.
//

#include "FileCreator.h"
#include <filesystem>
#include <iostream>
#include <fstream>


void FileCreator::generateFile(int**& adjacencyMatrix, int& verticesNumber, int& edgesNumber){
    std::ofstream file;
    std::string filename = "grafik.txt";

    file.open(filename, std::ios::app);

    if (!file.is_open()) {
        throw std::runtime_error("Nie można otworzyć pliku: " + filename);
    }

    file << verticesNumber <<" "<< edgesNumber<<"\n";

    for(int u=0; u<verticesNumber; u++){
        for(int v=0; v<verticesNumber; v++){
            if(adjacencyMatrix[u][v]!=0) file << u <<" "<< v <<" "<< adjacencyMatrix[u][v]<<"\n";
        }
    }

    file << "\n";

    file.close();
}
