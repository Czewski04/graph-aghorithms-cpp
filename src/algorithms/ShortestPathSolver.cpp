//
// Created by wiktor on 11.05.2025.
//

#include "../../include/algorithms/ShortestPathSolver.h"
#include "MinimumHeap.h"
#include <chrono>

std::tuple<neighbour**, int*, double> ShortestPathSolver::dijkstrasAlgorithmForMatrix(int** adjacencyMatrix, int verticesNumber, int startVertice) {
    auto start = std::chrono::high_resolution_clock::now();

    int* distance = new int[verticesNumber];            // Koszty dojścia do każdego wierzchołka
    int* parent = new int[verticesNumber];              // Rodzic danego wierzchołka w najkrótszej ścieżce
    auto** paths = new neighbour*[verticesNumber];      // Tablica list sąsiedztwa jako ścieżki

    for (int i = 0; i < verticesNumber; ++i) {
        distance[i] = INT_MAX;
        parent[i] = -1;
        paths[i] = nullptr;
    }

    MinimumHeap heap(verticesNumber);
    distance[startVertice] = 0;
    heap.decreaseKey(startVertice, 0);

    while (!heap.isEmpty()) {
        MinimumHeapNode minNode = heap.extractMin();
        int u = minNode.vertex;

        for (int v = 0; v < verticesNumber; v++) {
            int weight = adjacencyMatrix[u][v];
            if (weight > 0 && heap.isInHeap(v) && distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                parent[v] = u;
                heap.decreaseKey(v, distance[v]);
            }
        }
    }

    // Budowanie tablicy ścieżek dla każdego wierzchołka
    for (int v = 0; v < verticesNumber; v++) {
        for (int current = v; current != -1; current = parent[current]) {
            if (paths[v] == nullptr) {
                paths[v] = new neighbour;
                paths[v]->vertex = current;
                paths[v]->nextVertex = nullptr;
            }
            else {
                auto* newNeighbour = new neighbour;
                newNeighbour->vertex = current;
                newNeighbour->nextVertex = paths[v];
                paths[v] = newNeighbour;
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start);

    return std::make_tuple(paths, distance, duration.count());
}

std::tuple<neighbour **, int *, double> ShortestPathSolver::dijkstrasAlgorithmForList(neighbour **neighboursList, int verticesNumber, int startVertice) {
    auto start = std::chrono::high_resolution_clock::now();

    int* distance = new int[verticesNumber];            // Koszty dojścia do każdego wierzchołka
    int* parent = new int[verticesNumber];              // Rodzic danego wierzchołka w najkrótszej ścieżce
    auto** paths = new neighbour*[verticesNumber];      // Tablica list sąsiedztwa jako ścieżki

    for (int i = 0; i < verticesNumber; ++i) {
        distance[i] = INT_MAX;
        parent[i] = -1;
        paths[i] = nullptr;
    }

    MinimumHeap heap(verticesNumber);
    distance[startVertice] = 0;
    heap.decreaseKey(startVertice, 0);

    while (!heap.isEmpty()) {
        MinimumHeapNode minNode = heap.extractMin();
        int u = minNode.vertex;

        neighbour* current = neighboursList[u];
        while (current != nullptr) {
            int v = current -> vertex;
            int weight = current->weight;
            if (weight > 0 && heap.isInHeap(v) && distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                parent[v] = u;
                heap.decreaseKey(v, distance[v]);
            }
            current = current->nextVertex;
        }
    }

    // Budowanie tablicy ścieżek dla każdego wierzchołka
    for (int v = 0; v < verticesNumber; v++) {
        for (int current = v; current != -1; current = parent[current]) {
            if (paths[v] == nullptr) {
                paths[v] = new neighbour;
                paths[v]->vertex = current;
                paths[v]->nextVertex = nullptr;
            }
            else {
                auto* newNeighbour = new neighbour;
                newNeighbour->vertex = current;
                newNeighbour->nextVertex = paths[v];
                paths[v] = newNeighbour;
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start);

    return std::make_tuple(paths, distance, duration.count());
}
