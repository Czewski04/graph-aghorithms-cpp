//
// Created by wiktor on 11.05.2025.
//

#include "ShortestPathSolver.h"
#include "MinimumHeap.h"
#include <chrono>

// Algorytm Dijkstry dla macierzy sąsiedztwa
std::tuple<neighbour**, int*, double> ShortestPathSolver::dijkstrasAlgorithmForMatrix(int** adjacencyMatrix, int verticesNumber, int startVertex) {
    auto start = std::chrono::high_resolution_clock::now();

    int* distance = new int[verticesNumber];            // Tablica kosztów dojścia do każdego wierzchołka
    int* parent = new int[verticesNumber];              // Tablica rodziców danego wierzchołka w najkrótszej ścieżce
    auto** paths = new neighbour*[verticesNumber];      // Tablica ścierzek

    // Inicjalizacja tablic
    for (int i = 0; i < verticesNumber; ++i) {
        distance[i] = INT_MAX;
        parent[i] = -1;
        paths[i] = nullptr;
    }

    // Dodanie do kopca początkowego wierzchołka
    MinimumHeap heap(verticesNumber);
    distance[startVertex] = 0;
    heap.decreaseKey(startVertex, 0);

    // Pętla wykonująca się dopóki kolejka nie będzie pusta
    while (!heap.isEmpty()) {
        MinimumHeapNode minNode = heap.extractMin();    // Pobranie najlżejszego wierzchołka
        int u = minNode.vertex;

        for (int v = 0; v < verticesNumber; v++) {
            int weight = adjacencyMatrix[u][v];
            // Relaksacja
            if (weight > 0 && heap.isInHeap(v) && distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                parent[v] = u;
                heap.decreaseKey(v, distance[v]);
            }
        }
    }

    // Zbudowanie wyjściowej listy znalezionych ścieżek
    buildPathsList(verticesNumber, parent, paths);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start);

    return std::make_tuple(paths, distance, duration.count());
}

// Algorytm Dijkstry dla listy sąsiedztwa
std::tuple<neighbour **, int *, double> ShortestPathSolver::dijkstrasAlgorithmForList(neighbour **neighboursList, int verticesNumber, int startVertex) {
    auto start = std::chrono::high_resolution_clock::now();

    int* distance = new int[verticesNumber];            // Tablica kosztów dojścia do każdego wierzchołka
    int* parent = new int[verticesNumber];              // Tablica rodziców danego wierzchołka w najkrótszej ścieżce
    auto** paths = new neighbour*[verticesNumber];      // Tablica ścierzek

    // Inicjalizacja tablic
    for (int i = 0; i < verticesNumber; ++i) {
        distance[i] = INT_MAX;
        parent[i] = -1;
        paths[i] = nullptr;
    }

    // Dodanie do kopca początkowego wierzchołka
    MinimumHeap heap(verticesNumber);
    distance[startVertex] = 0;
    heap.decreaseKey(startVertex, 0);

    // Pętla wykonująca się dopóki kolejka nie będzie pusta
    while (!heap.isEmpty()) {
        MinimumHeapNode minNode = heap.extractMin();    // Pobranie najlżejszego wierzchołka
        int u = minNode.vertex;

        neighbour* current = neighboursList[u];
        while (current != nullptr) {
            int v = current -> vertex;
            int weight = current->weight;
            // Relaksacja
            if (weight > 0 && heap.isInHeap(v) && distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                parent[v] = u;
                heap.decreaseKey(v, distance[v]);
            }
            current = current->nextVertex;
        }
    }

    // Zbudowanie wyjściowej listy znalezionych ścieżek
    buildPathsList(verticesNumber, parent, paths);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start);

    return std::make_tuple(paths, distance, duration.count());
}

// Algorytm Bellmana-Forda dla macierzy sąsiedztwa
std::tuple<neighbour**, int*, double> ShortestPathSolver::bellmanFordAlgorithmForMatrix(int** adjacencyMatrix, int verticesNumber, int startVertex) {
    auto start = std::chrono::high_resolution_clock::now();

    int* distance = new int[verticesNumber];            // Tablica kosztów dojścia do każdego wierzchołka
    int* parent = new int[verticesNumber];              // Tablica rodziców danego wierzchołka w najkrótszej ścieżce
    auto** paths = new neighbour*[verticesNumber];      // Tablica ścierzek

    // Inicjalizacja tablic
    for (int i = 0; i < verticesNumber; ++i) {
        distance[i] = INT_MAX;
        parent[i] = -1;
        paths[i] = nullptr;
    }

    // Aktualizacja wagi początkowego wierzchołka
    distance[startVertex] = 0;

    // Sprawdzenie wierzchołków V-1 razy
    for (int i = 1; i < verticesNumber; ++i) {
        for (int u = 0; u < verticesNumber; ++u) {
            for (int v = 0; v < verticesNumber; ++v) {
                int weight = adjacencyMatrix[u][v];
                // Relaksacja
                if (weight > 0 && distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
                    distance[v] = distance[u] + weight;
                    parent[v] = u;
                }
            }
        }
    }

    // Test ujemnego cyklu
    for (int u = 0; u < verticesNumber; ++u) {
        for (int v = 0; v < verticesNumber; ++v) {
            int weight = adjacencyMatrix[u][v];
            // Wykrywanie ujemnego cyklu
            if (weight > 0 && distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
                delete[] distance;
                delete[] parent;
                for (int i = 0; i < verticesNumber; ++i) {
                    delete[] paths[i];
                }
                delete[] paths;
                return std::make_tuple(nullptr, nullptr, -1.0);     // Zwrócenie błędu gdy wystąpi cykl ujemny
            }
        }
    }

    // Zbudowanie wyjściowej listy znalezionych ścieżek
    buildPathsList(verticesNumber, parent, paths);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start);

    return std::make_tuple(paths, distance, duration.count());
}

// Algorytm Bellmana-Forda dla listy sąsiedztwa
std::tuple<neighbour **, int *, double> ShortestPathSolver::bellmanFordAlgorithmForList(neighbour **neighboursList, int verticesNumber, int startVertex) {
    auto start = std::chrono::high_resolution_clock::now();

    int* distance = new int[verticesNumber];            // Tablica kosztów dojścia do każdego wierzchołka
    int* parent = new int[verticesNumber];              // Tablica rodziców danego wierzchołka w najkrótszej ścieżce
    auto** paths = new neighbour*[verticesNumber];      // Tablica ścierzek

    // Inicjalizacja tablic
    for (int i = 0; i < verticesNumber; ++i) {
        distance[i] = INT_MAX;
        parent[i] = -1;
        paths[i] = nullptr;
    }

    // Aktualizacja wagi początkowego wierzchołka
    distance[startVertex] = 0;

    // Sprawdzenie wierzchołków V-1 razy
    for (int i = 1; i < verticesNumber; ++i) {
        for (int u = 0; u < verticesNumber; ++u) {
            neighbour* current = neighboursList[u];
            while (current != nullptr) {
                int v = current->vertex;
                int weight = current->weight;
                // Relaksacja
                if (weight > 0 && distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
                    distance[v] = distance[u] + weight;
                    parent[v] = u;
                }
                current = current->nextVertex;
            }
        }
    }

    // Test ujemnego cyklu
    for (int i = 1; i < verticesNumber; ++i) {
        for (int u = 0; u < verticesNumber; ++u) {
            neighbour* current = neighboursList[u];
            while (current != nullptr) {
                int v = current->vertex;
                int weight = current->weight;
                // Wykrywanie ujemnego cyklu
                if (weight > 0 && distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
                    delete[] distance;
                    delete[] parent;
                    for (int i = 0; i < verticesNumber; ++i) {
                        delete[] paths[i];
                    }
                    delete[] paths;
                    return std::make_tuple(nullptr, nullptr, -1.0);     // Zwrócenie błędu gdy wystąpi cykl ujemny
                }
                current = current->nextVertex;
            }
        }
    }

    // Zbudowanie wyjściowej listy znalezionych ścieżek
    buildPathsList(verticesNumber, parent, paths);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start);

    return std::make_tuple(paths, distance, duration.count());
}

// Budowanie tablicy ścieżek dla każdego wierzchołka
void ShortestPathSolver::buildPathsList(int verticesNumber, int *parent, neighbour **paths) {
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
}