//
// Created by wiktor on 11.05.2025.
//

#include "MaximumFlowSolver.h"
#include "Utilities.h"
#include <chrono>
#include <iostream>

// Algorytm DFS dla macierzy sąsiedztwa
bool MaximumFlowSolver::dfsFindPathForMatrix(int** residualGraph, int verticesNumber, int source, int sink, int* parent, bool* visited) {
    // Dodanie wierzchołka do odwiedzonych
    visited[source] = true;

    // Weryfikacja czy algorytm dotarł do końca ścieżki
    if (source == sink)
        return true;

    // Przejście po wszystkich sąsiadach danego wierzchołka
    for (int v = 0; v < verticesNumber; v++) {
        if (!visited[v] && residualGraph[source][v] > 0) {
            parent[v] = source;
            // Rekurencyjne wywołanie DFS
            if (dfsFindPathForMatrix(residualGraph, verticesNumber, v, sink, parent, visited))
                return true;
        }
    }

    return false;
}

// Algorytm Forda-Fulkersona DFS dla macierzy sąsiedztwa
std::tuple<int, double, int**> MaximumFlowSolver::fordFulkersonDfsAlgorithmForMatrix(int **adjacencyMatrix, int verticesNumber, int startVertex, int endVertex) {
    auto start = std::chrono::high_resolution_clock::now();

    // Utworzenie grafu rezydualnego
    int** residualGraph = new int*[verticesNumber];
    for (int i = 0; i < verticesNumber; i++) {
        residualGraph[i] = new int[verticesNumber];
        for (int j = 0; j < verticesNumber; j++) {
            residualGraph[i][j] = adjacencyMatrix[i][j];
        }
    }

    int* parent = new int[verticesNumber];      // Tablica rodziców obrazująca ścieżkę
    bool* visited = new bool[verticesNumber];   // Tablica odwiedzonych wierzchołków
    int maxFlow = 0;                            // Maksymalny przepływ

    // Pętla wykonująca się, dopóki istnieje ścieżka z wierzchołka początkowego do końcowego
    while (true) {
        // Wyczyszczenie tablicy odwiedzonych wierzchołków i rodziców przed każdą iteracją
        for (int i = 0; i < verticesNumber; i++) {
            visited[i] = false;
            parent[i] = -1;
        }

        // Warunek sprawdzający, czy istnieje ścieżka
        if (!dfsFindPathForMatrix(residualGraph, verticesNumber, startVertex, endVertex, parent, visited))
            break;

        // Znajdowanie minimalnej przepustowości na ścieżce
        int pathFlow = INT_MAX;
        for (int v = endVertex; v != startVertex; v = parent[v]) {
            int u = parent[v];
            if (residualGraph[u][v] < pathFlow)
                pathFlow = residualGraph[u][v];
        }

        // Aktualizacja grafu rezydualnego
        for (int v = endVertex; v != startVertex; v = parent[v]) {
            int u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }

        // Dodanie przepływu do maksymalnego
        maxFlow += pathFlow;
    }

    // Zwolnienie pamięci po wszystkich operacjach
    delete[] parent;
    delete[] visited;

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start);

    return std::make_tuple(maxFlow, duration.count(), residualGraph);
}

// Algorytm DFS dla listy sąsiedztwa
bool MaximumFlowSolver::dfsFindPathForList(neighbour** residualGraph, int verticesNumber, int source, int sink, int* parent, bool* visited, neighbour** pathEdges) {
    // Dodanie wierzchołka do odwiedzonych
    visited[source] = true;

    // Weryfikacja czy algorytm dotarł do końca ścieżki
    if (source == sink)
        return true;

    // Przejście po wszystkich sąsiadach danego wierzchołka
    neighbour* current = residualGraph[source];
    while (current != nullptr) {
        int v = current->vertex;
        int capacity = current->weight;
        if (!visited[v] && capacity>0) {
            parent[v] = source;
            pathEdges[v] = current;     //  zapamiętanie wierzchołka na ścieżce
            // Rekurencyjne wywołanie DFS
            if (dfsFindPathForList(residualGraph, verticesNumber, v, sink, parent, visited, pathEdges))
                return true;
        }
        current = current->nextVertex;
    }

    return false;
}

// Algorytm Forda-Fulkersona DFS dla listy sąsiedztwa
std::tuple<int, double, neighbour**> MaximumFlowSolver::fordFulkersonDfsAlgorithmForList(neighbour** neighboursList, int verticesNumber, int startVertex, int endVertex) {
    auto start = std::chrono::high_resolution_clock::now();

    // Utworzenie grafu rezydualnego
    auto** residualGraph = new neighbour*[verticesNumber];
    for (int i = 0; i < verticesNumber; i++)
        residualGraph[i] = nullptr;

    // Dodanie krawędzi rezydualnych
    for (int u = 0; u < verticesNumber; u++) {
        neighbour* currentOriginal = neighboursList[u];
        while (currentOriginal != nullptr) {
            int v = currentOriginal->vertex;
            int capacity = currentOriginal->weight;
            addResidualEdge(residualGraph[u], residualGraph[v], u, v, capacity);
            currentOriginal = currentOriginal->nextVertex;
        }
    }
    int* parent = new int[verticesNumber];              // Tablica rodziców obrazująca ścieżkę
    bool* visited = new bool[verticesNumber];           // Tablica odwiedzonych wierzchołków
    auto** pathEdges = new neighbour*[verticesNumber];  // Tablica wskaźników zapamiętująca wskaźniki na wierzchołki na ścieżce
    int maxFlow = 0;                                    // Maksymalny przepływ

    // Pętla wykonująca się, dopóki istnieje ścieżka z wierzchołka początkowego do końcowego
    while (true) {
        // Wyczyszczenie tablicy odwiedzonych wierzchołków i rodziców przed każdą iteracją
        for (int i = 0; i < verticesNumber; i++) {
            visited[i] = false;
            parent[i] = -1;
            pathEdges[i] = nullptr;
        }
        // Warunek sprawdzający, czy istnieje ścieżka
        if (!dfsFindPathForList(residualGraph, verticesNumber, startVertex, endVertex, parent, visited, pathEdges))
            break;

        // Znajdowanie minimalnej przepustowości na ścieżce
        int pathFlow = INT_MAX;
        for (int v = endVertex; v != startVertex; v = parent[v]) {
            if (pathEdges[v]->weight < pathFlow)
                pathFlow = pathEdges[v]->weight;
        }

        // Aktualizacja grafu rezydualnego
        for (int v = endVertex; v != startVertex; v = parent[v]) {
            neighbour* edge = pathEdges[v];
            edge->weight -= pathFlow;
            edge->reverseEdge->weight += pathFlow;
        }

        // Dodanie przepływu do maksymalnego
        maxFlow += pathFlow;
    }

    delete[] parent;
    delete[] visited;
    delete[] pathEdges;

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start);

    return std::make_tuple(maxFlow, duration.count(), residualGraph);
}

// Algorytm BFS dla macierzy sąsiedztwa
bool MaximumFlowSolver::bfsFindPathForMatrix(int** residualGraph, int verticesNumber, int source, int sink, int* parent, bool* visited) {
    // Utworzenie kolejki FIFO na wierzchołki
    int* queue = new int[verticesNumber];
    int front = 0, back = 0;

    // Dodanie wierzchołka początkowego do kolejki i oznaczenie jako odwiedzony
    queue[back] = source;
    back++;
    visited[source] = true;
    parent[source] = -1;

    // Pętla wykonująca się, dopóki kolejka nie jest pusta
    while (front < back) {
        int u = queue[front]; // Pobranie wierzchołka z kolejki
        front++;

        // Sprawdzenie wszystkich sąsiadów wierzchołka
        for (int v = 0; v < verticesNumber; v++) {
            // Jeżeli sąsiad jest nieodwiedzony dodajemy go do kolejki
            if (!visited[v] && residualGraph[u][v] > 0) {
                queue[back] = v;
                back++;
                parent[v] = u;
                visited[v] = true;
                // Weryfikacja czy algorytm dotarł do końca ścieżki
                if (v == sink) {
                    delete[] queue;
                    return true;
                }
            }
        }
    }

    delete[] queue;
    return false;
}

// Algorytm Forda-Fulkersona BFS dla macierzy sąsiedztwa
std::tuple<int, double, int**> MaximumFlowSolver::fordFulkersonBfsAlgorithmForMatrix(int** adjacencyMatrix, int verticesNumber, int startVertex, int endVertex) {
    auto start = std::chrono::high_resolution_clock::now();

    // Utworzenie grafu rezydualnego
    int** residualGraph = new int*[verticesNumber];
    for (int i = 0; i < verticesNumber; ++i) {
        residualGraph[i] = new int[verticesNumber];
        for (int j = 0; j < verticesNumber; ++j) {
            residualGraph[i][j] = adjacencyMatrix[i][j];
        }
    }

    int* parent = new int[verticesNumber];      // Tablica rodziców obrazująca ścieżkę
    bool* visited = new bool[verticesNumber];   // Tablica odwiedzonych wierzchołków
    int maxFlow = 0;                            // Maksymalny przepływ

    // Pętla wykonująca się, dopóki istnieje ścieżka z wierzchołka początkowego do końcowego
    while (true) {

        // Wyczyszczenie tablicy odwiedzonych wierzchołków i rodziców przed każdą iteracją
        for (int i = 0; i < verticesNumber; i++) {
            visited[i] = false;
            parent[i] = -1;
        }

        // Warunek sprawdzający, czy istnieje ścieżka
        if (!bfsFindPathForMatrix(residualGraph, verticesNumber, startVertex, endVertex, parent, visited))
            break;

        // Znajdowanie minimalnej przepustowości na ścieżce
        int pathFlow = INT_MAX;
        for (int v = endVertex; v != startVertex; v = parent[v]) {
            int u = parent[v];
            if (residualGraph[u][v] < pathFlow)
                pathFlow = residualGraph[u][v];
        }

        // Aktualizacja grafu rezydualnego
        for (int v = endVertex; v != startVertex; v = parent[v]) {
            int u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }

        // Dodanie przepływu do maksymalnego
        maxFlow += pathFlow;
    }

    delete[] parent;
    delete[] visited;

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start).count();

    return std::make_tuple(maxFlow, duration, residualGraph);
}

// Algorytm BFS dla listy sąsiedztwa
bool MaximumFlowSolver::bfsFindPathForList(neighbour **residualGraph, int verticesNumber, int source, int sink, int *parent, bool *visited, neighbour** pathEdges) {
    // Utworzenie kolejki FIFO na wierzchołki
    int* queue = new int[verticesNumber];
    int front = 0, back = 0;

    // Dodanie wierzchołka początkowego do kolejki i oznaczenie jako odwiedzony
    queue[back] = source;
    back++;
    visited[source] = true;
    parent[source] = -1;;

    // Pętla wykonująca się, dopóki kolejka nie jest pusta
    while (front < back) {
        int u = queue[front]; // Pobranie wierzchołka z kolejki
        front++;

        // Sprawdzenie wszystkich sąsiadów wierzchołka
        neighbour* current = residualGraph[u];
        while (current != nullptr) {
            int v = current->vertex;
            int capacity = current->weight;
            // Jeżeli sąsiad jest nieodwiedzony dodajemy go do kolejki
            if (!visited[v] && capacity > 0) {
                queue[back] = v;
                back++;
                parent[v] = u;
                visited[v] = true;;
                pathEdges[v] = current;
                // Weryfikacja czy algorytm dotarł do końca ścieżki
                if (v == sink) {
                    delete[] queue;
                    return true;
                }
            }
            current = current->nextVertex;
        }
    }

    delete[] queue;
    return false;
}

// Algorytm Forda-Fulkersona BFS dla listy sąsiedztwa
std::tuple<int, double, neighbour**> MaximumFlowSolver::fordFulkersonBfsAlgorithmForList(neighbour **neighboursList, int verticesNumber, int startVertex, int endVertex) {
    auto start = std::chrono::high_resolution_clock::now();

    // Utworzenie grafu rezydualnego
    auto** residualGraph = new neighbour*[verticesNumber];
    for (int i = 0; i < verticesNumber; i++)
        residualGraph[i] = nullptr;

    // Dodanie krawędzi rezydualnych
    for (int u = 0; u < verticesNumber; u++) {
        neighbour* currentOriginal = neighboursList[u];
        while (currentOriginal != nullptr) {
            int v = currentOriginal->vertex;
            int capacity = currentOriginal->weight;
            addResidualEdge(residualGraph[u], residualGraph[v], u, v, capacity);
            currentOriginal = currentOriginal->nextVertex;
        }
    }

    int* parent = new int[verticesNumber];              // Tablica rodziców obrazująca ścieżkę
    bool* visited = new bool[verticesNumber];           // Tablica odwiedzonych wierzchołków
    auto** pathEdges = new neighbour*[verticesNumber];  // Tablica wskaźników zapamiętująca wskaźniki na wierzchołki na ścieżce
    int maxFlow = 0;                                    // Maksymalny przepływ

    // Pętla wykonująca się, dopóki istnieje ścieżka z wierzchołka początkowego do końcowego
    while (true) {
        // Wyczyszczenie tablicy odwiedzonych wierzchołków i rodziców przed każdą iteracją
        for (int i = 0; i < verticesNumber; i++) {
            visited[i] = false;
            parent[i] = -1;
            pathEdges[i] = nullptr;
        }

        // Warunek sprawdzający, czy istnieje ścieżka
        if (!bfsFindPathForList(residualGraph, verticesNumber, startVertex, endVertex, parent, visited, pathEdges))
            break;

        // Znajdowanie minimalnej przepustowości na ścieżce
        int pathFlow = INT_MAX;
        for (int v = endVertex; v != startVertex; v = parent[v]) {
            neighbour* edge = pathEdges[v];
            if (edge->weight < pathFlow)
                pathFlow = edge->weight;
        }

        // Aktualizacja grafu rezydualnego
        for (int v = endVertex; v != startVertex; v = parent[v]) {
            neighbour* edge = pathEdges[v];
            edge->weight -= pathFlow;
            edge->reverseEdge->weight += pathFlow;
            int u = parent[v];
        }

        // Dodanie przepływu do maksymalnego
        maxFlow += pathFlow;
    }

    delete[] parent;
    delete[] visited;
    delete[] pathEdges;

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start);

    return std::make_tuple(maxFlow, duration.count(), residualGraph);
}

// Metoda dodająca krawędzie do grafu rezydualnego
void MaximumFlowSolver::addResidualEdge(neighbour*& headU, neighbour*& headV, int u, int v, int capacity) {
    // Utworzenie krawędzi rezydualnych w obie strony
    auto* forward = new neighbour{v, capacity, headU, nullptr};
    auto* backward = new neighbour{u, 0, headV, nullptr};

    // Łączenie krawędzi
    forward->reverseEdge = backward;
    backward->reverseEdge = forward;

    // Dodanie do listy
    headU = forward;
    headV = backward;
}