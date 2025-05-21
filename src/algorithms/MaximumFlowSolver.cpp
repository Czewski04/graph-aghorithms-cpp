//
// Created by wiktor on 11.05.2025.
//

#include "../../include/algorithms/MaximumFlowSolver.h"
#include <chrono>

bool MaximumFlowSolver::dfsFindPathForMatrix(int** residualGraph, int verticesNumber, int source, int sink, int* parent, bool* visited) {
    visited[source] = true;

    if (source == sink)
        return true;

    for (int v = 0; v < verticesNumber; ++v) {
        if (!visited[v] && residualGraph[source][v] > 0) {
            parent[v] = source;
            if (dfsFindPathForMatrix(residualGraph, verticesNumber, v, sink, parent, visited))
                return true;
        }
    }

    return false;
}

std::tuple<int, double> MaximumFlowSolver::fordFulkersonDfsAlgorithmForMatrix(int **adjacencyMatrix, int verticesNumber, int startVertex, int endVertex) {
    auto start = std::chrono::high_resolution_clock::now();

    // Tworzymy graf rezydualny jako kopię adjacencyMatrix
    int** residualGraph = new int*[verticesNumber];
    for (int i = 0; i < verticesNumber; i++) {
        residualGraph[i] = new int[verticesNumber];
        for (int j = 0; j < verticesNumber; j++) {
            residualGraph[i][j] = adjacencyMatrix[i][j];
        }
    }

    int* parent = new int[verticesNumber];
    bool* visited = new bool[verticesNumber];
    int maxFlow = 0;

    // Dopóki istnieje ścieżka z source do sink
    while (true) {
        for (int i = 0; i < verticesNumber; i++) {
            visited[i] = false;
            parent[i] = -1;
        }

        if (!dfsFindPathForMatrix(residualGraph, verticesNumber, startVertex, endVertex, parent, visited))
            break;

        // Znajdź minimalną przepustowość (bottleneck) na ścieżce
        int pathFlow = INT_MAX;
        for (int v = endVertex; v != startVertex; v = parent[v]) {
            int u = parent[v];
            if (residualGraph[u][v] < pathFlow)
                pathFlow = residualGraph[u][v];
        }

        // Aktualizuj graf rezydualny
        for (int v = endVertex; v != startVertex; v = parent[v]) {
            int u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }

    // Zwolnienie pamięci
    for (int i = 0; i < verticesNumber; ++i)
        delete[] residualGraph[i];
    delete[] residualGraph;
    delete[] parent;
    delete[] visited;

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start);

    return std::make_tuple(maxFlow, duration.count());
}

bool MaximumFlowSolver::dfsFindPathForList(neighbour** residualGraph, int verticesNumber, int source, int sink, int* parent, bool* visited) {
    visited[source] = true;

    if (source == sink)
        return true;

    neighbour* current = residualGraph[source];
    while (current != nullptr) {
        int v = current->vertex;
        int capacity = current->weight;
        if (!visited[v] && capacity>0) {
            parent[v] = source;
            if (dfsFindPathForList(residualGraph, verticesNumber, v, sink, parent, visited))
                return true;
        }
        current = current->nextVertex;
    }

    return false;
}

std::tuple<int, double> MaximumFlowSolver::fordFulkersonDfsAlgorithmForList(neighbour** neighboursList, int verticesNumber, int startVertex, int endVertex) {
    auto start = std::chrono::high_resolution_clock::now();

    // Inicjalizacja residualGraph jako tablicy wskaźników na listy sąsiedztwa
    neighbour** residualGraph = new neighbour*[verticesNumber];
    for (int i = 0; i < verticesNumber; ++i) {
        residualGraph[i] = nullptr; // Każda lista początkowo pusta
    }

    // Kopiowanie krawędzi z neighboursList do residualGraph
    // i dodawanie krawędzi wstecznych
    for (int u = 0; u < verticesNumber; ++u) {
        neighbour* currentOriginal = neighboursList[u]; // Iterujemy po oryginalnej liście sąsiedztwa
        while (currentOriginal != nullptr) {
            int v = currentOriginal->vertex;
            int capacity = currentOriginal->weight; // Waga w oryginalnym grafie to przepustowość

            // Dodaj krawędź w przód (u, v) do residualGraph
            addNeighbourToList(residualGraph[u], v, capacity);

            // Dodaj krawędź wsteczną (v, u) do residualGraph z przepustowością 0 (początkowo)
            // Jest to kluczowe dla możliwości "cofania" przepływu
            addNeighbourToList(residualGraph[v], u, 0);

            currentOriginal = currentOriginal->nextVertex;
        }
    }

    int* parent = new int[verticesNumber];
    bool* visited = new bool[verticesNumber];

    int maxFlow = 0;

    // Dopóki istnieje ścieżka z source do sink
    while (true) {
        for (int i = 0; i < verticesNumber; i++) {
            visited[i] = false;
            parent[i] = -1;
        }

        if (!dfsFindPathForList(residualGraph, verticesNumber, startVertex, endVertex, parent, visited))
            break;

        // Znajdź minimalną przepustowość (bottleneck) na ścieżce
        int pathFlow = INT_MAX;
        for (int v = endVertex; v != startVertex; v = parent[v]) {
            int u = parent[v];
            int currentEdgeCapacity = 0;
            neighbour* current = residualGraph[u];
            while (current != nullptr) {
                if (current->vertex == v) {
                    currentEdgeCapacity = current->weight;
                    break;
                }
                current = current->nextVertex;
            }
            if (currentEdgeCapacity < pathFlow)
                pathFlow = currentEdgeCapacity;
        }

        // Aktualizuj graf rezydualny
        for (int v = endVertex; v != startVertex; v = parent[v]) {
            int u = parent[v];
            int currentEdgeCapacity = 0;

            neighbour* current = residualGraph[u];
            while (current != nullptr) {
                if (current->vertex == v) {
                    currentEdgeCapacity = current->weight;
                    break;
                }
                current = current->nextVertex;
            }
            current = residualGraph[u];
            while (current != nullptr) {
                if (current->vertex == v) {
                    current->weight = currentEdgeCapacity-pathFlow;
                    break;
                }
                current = current->nextVertex;
            }

            current = residualGraph[v];
            while (current != nullptr) {
                if (current->vertex == u) {
                    currentEdgeCapacity = current->weight;
                    break;
                }
                current = current->nextVertex;
            }
            current = residualGraph[v];
            while (current != nullptr) {
                if (current->vertex == u) {
                    current->weight = currentEdgeCapacity+pathFlow;
                    break;
                }
                current = current->nextVertex;
            }
        }

        maxFlow += pathFlow;
    }

    // Zwolnienie pamięci
    for (int i = 0; i < verticesNumber; i++)
        deleteLinkedList(residualGraph[i]);
    delete[] residualGraph;
    delete[] parent;
    delete[] visited;

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start);

    return std::make_tuple(maxFlow, duration.count());
}

void MaximumFlowSolver::addNeighbourToList(neighbour*& mainVertex, int vertex, int capacity) {
    neighbour* newNeighbour = new neighbour;
    newNeighbour->vertex = vertex;
    newNeighbour->weight = capacity; // Waga tutaj to przepustowość rezydualna
    newNeighbour->nextVertex = nullptr;

    if (mainVertex == nullptr) {
        mainVertex = newNeighbour;
    } else {
        neighbour* current = mainVertex;
        while (current->nextVertex != nullptr) {
            current = current->nextVertex;
        }
        current->nextVertex = newNeighbour;
    }
}

std::tuple<int, double> MaximumFlowSolver::fordFulkersonBfsAlgorithmForMatrix(int** adjacencyMatrix, int verticesNumber, int startVertex, int endVertex) {
    auto start = std::chrono::high_resolution_clock::now();

    int** residualGraph = new int*[verticesNumber];
    for (int i = 0; i < verticesNumber; ++i) {
        residualGraph[i] = new int[verticesNumber];
        for (int j = 0; j < verticesNumber; ++j) {
            residualGraph[i][j] = adjacencyMatrix[i][j];
        }
    }

    int* parent = new int[verticesNumber];
    bool* visited = new bool[verticesNumber];
    int maxFlow = 0;

    while (true) {
        for (int i = 0; i < verticesNumber; i++) {
            visited[i] = false;
            parent[i] = -1;
        }

        if (!bfsFindPathForMatrix(residualGraph, verticesNumber, startVertex, endVertex, parent, visited))
            break;

        int pathFlow = INT_MAX;
        for (int v = endVertex; v != startVertex; v = parent[v]) {
            int u = parent[v];
            if (residualGraph[u][v] < pathFlow)
                pathFlow = residualGraph[u][v];
        }

        for (int v = endVertex; v != startVertex; v = parent[v]) {
            int u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }

    for (int i = 0; i < verticesNumber; ++i)
        delete[] residualGraph[i];
    delete[] residualGraph;
    delete[] parent;
    delete[] visited;

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start).count();

    return std::make_tuple(maxFlow, duration);
}

bool MaximumFlowSolver::bfsFindPathForMatrix(int** residualGraph, int verticesNumber, int source, int sink, int* parent, bool* visited) {
    int* queue = new int[verticesNumber];
    int front = 0, back = 0;

    queue[back++] = source;
    visited[source] = true;
    parent[source] = -1;

    while (front < back) {
        int u = queue[front++];

        for (int v = 0; v < verticesNumber; ++v) {
            if (!visited[v] && residualGraph[u][v] > 0) {
                queue[back++] = v;
                parent[v] = u;
                visited[v] = true;
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

std::tuple<int, double> MaximumFlowSolver::fordFulkersonBfsAlgorithmForList(neighbour **neighboursList, int verticesNumber, int startVertex, int endVertex) {
    auto start = std::chrono::high_resolution_clock::now();

    // Inicjalizacja residualGraph jako tablicy wskaźników na listy sąsiedztwa
    neighbour** residualGraph = new neighbour*[verticesNumber];
    for (int i = 0; i < verticesNumber; ++i) {
        residualGraph[i] = nullptr; // Każda lista początkowo pusta
    }

    // Kopiowanie krawędzi z neighboursList do residualGraph
    // i dodawanie krawędzi wstecznych
    for (int u = 0; u < verticesNumber; ++u) {
        neighbour* currentOriginal = neighboursList[u]; // Iterujemy po oryginalnej liście sąsiedztwa
        while (currentOriginal != nullptr) {
            int v = currentOriginal->vertex;
            int capacity = currentOriginal->weight; // Waga w oryginalnym grafie to przepustowość
            // Dodaj krawędź w przód (u, v) do residualGraph
            addNeighbourToList(residualGraph[u], v, capacity);
            // Dodaj krawędź wsteczną (v, u) do residualGraph z przepustowością 0 (początkowo)
            // Jest to kluczowe dla możliwości "cofania" przepływu
            addNeighbourToList(residualGraph[v], u, 0);
            currentOriginal = currentOriginal->nextVertex;
        }
    }

    int* parent = new int[verticesNumber];
    bool* visited = new bool[verticesNumber];
    int maxFlow = 0;

    // Dopóki istnieje ścieżka z source do sink
    while (true) {
        for (int i = 0; i < verticesNumber; i++) {
            visited[i] = false;
            parent[i] = -1;
        }

        if (!dfsFindPathForList(residualGraph, verticesNumber, startVertex, endVertex, parent, visited))
            break;

        // Znajdź minimalną przepustowość (bottleneck) na ścieżce
        int pathFlow = INT_MAX;
        for (int v = endVertex; v != startVertex; v = parent[v]) {
            int u = parent[v];
            int currentEdgeCapacity = 0;
            neighbour* current = residualGraph[u];
            while (current != nullptr) {
                if (current->vertex == v) {
                    currentEdgeCapacity = current->weight;
                    break;
                }
                current = current->nextVertex;
            }
            if (currentEdgeCapacity < pathFlow)
                pathFlow = currentEdgeCapacity;
        }

        // Aktualizuj graf rezydualny
        for (int v = endVertex; v != startVertex; v = parent[v]) {
            int u = parent[v];
            int currentEdgeCapacity = 0;

            neighbour* current = residualGraph[u];
            while (current != nullptr) {
                if (current->vertex == v) {
                    currentEdgeCapacity = current->weight;
                    break;
                }
                current = current->nextVertex;
            }
            current = residualGraph[u];
            while (current != nullptr) {
                if (current->vertex == v) {
                    current->weight = currentEdgeCapacity-pathFlow;
                    break;
                }
                current = current->nextVertex;
            }

            current = residualGraph[v];
            while (current != nullptr) {
                if (current->vertex == u) {
                    currentEdgeCapacity = current->weight;
                    break;
                }
                current = current->nextVertex;
            }
            current = residualGraph[v];
            while (current != nullptr) {
                if (current->vertex == u) {
                    current->weight = currentEdgeCapacity+pathFlow;
                    break;
                }
                current = current->nextVertex;
            }
        }

        maxFlow += pathFlow;
    }

    // Zwolnienie pamięci
    for (int i = 0; i < verticesNumber; i++)
        deleteLinkedList(residualGraph[i]);
    delete[] residualGraph;
    delete[] parent;
    delete[] visited;

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start);

    return std::make_tuple(maxFlow, duration.count());
}

bool MaximumFlowSolver::bfsFindPathForList(neighbour **residualGraph, int verticesNumber, int source, int sink, int *parent, bool *visited) {
    int* queue = new int[verticesNumber];
    int front = 0, back = 0;

    queue[back++] = source;
    visited[source] = true;
    parent[source] = -1;

    while (front < back) {
        int u = queue[front++];

        neighbour* current = residualGraph[u];
        while (current != nullptr) {
            int v = current->vertex;
            int capacity = current->weight;
            if (!visited[v] && capacity > 0) {
                queue[back++] = v;
                parent[v] = u;
                visited[v] = true;
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

// Funkcja pomocnicza do zwalniania pamięci listy sąsiedztwa
void MaximumFlowSolver::deleteLinkedList(neighbour* mainNeighbour) {
    neighbour* current = mainNeighbour;
    while (current != nullptr) {
        neighbour* next = current->nextVertex; // Zapisz wskaźnik na następny element
        delete current; // Usuń bieżący element
        current = next; // Przejdź do następnego
    }
}