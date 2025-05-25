//
// Created by wiktor on 11.05.2025.
//

#include "MSTSolver.h"
#include "UnionFind.h"
#include "MinimumHeap.h"
#include <chrono>
#include <climits>

// Algorytm Prima dla macierzy sąsiedztwa
std::tuple<Edge *, int, int, double> MSTSolver::primsAlgorithmForMatrix(int **adjacencyMatrix, int verticesNumber) {
    auto start = std::chrono::high_resolution_clock::now();

    // Tablica reprezentująca rodziców w MST
    int* parent = new int[verticesNumber];

    // Tablica reprezentująca najmnijeszą znaną wagę krawędzi dla każdego wierzchołka
    int* key = new int[verticesNumber];

    // Tablica wynikowa krawędzi
    Edge* mstEdges = new Edge[verticesNumber - 1];

    int mstWeight = 0;
    int mstEdgeCount = 0;

    // Inicjalizacja kopca minimum dla wierzchołków
    MinimumHeap heap(verticesNumber);

    // Inicjalizacja rodziców i wag
    for (int v = 0; v < verticesNumber; v++) {
        key[v] = INT_MAX;
        parent[v] = -1;
    }

    // Wybór początkowego wierzchołka i aktualizacja pozycji na kopcu
    key[0] = 0;
    heap.decreaseKey(0, 0);

    while (!heap.isEmpty()) {
        // Wybranie najtańszego wierzchołka
        MinimumHeapNode minNode = heap.extractMin();
        int u = minNode.vertex;

        // Dodatnie krawędzi do MST (jeśli nie jest to piewrszy wierzchołek(ma rodzica))
        if (parent[u] != -1) {
            mstEdges[mstEdgeCount] = {parent[u], u, adjacencyMatrix[parent[u]][u]};
            mstEdgeCount++;
            mstWeight += adjacencyMatrix[parent[u]][u];
        }

        // Sprawdzenie sąsiadów wierzchołka
        for (int v = 0; v < verticesNumber; v++) {

            // Jeśli sąsiad nie jest jeszce w MST i waga krawędzi jest mniejsza niż aktualnie znana najmniejsza to następuje aktualizacja informacji
            if (adjacencyMatrix[u][v] > 0 && heap.isInHeap(v) && adjacencyMatrix[u][v] < key[v]) {
                key[v] = adjacencyMatrix[u][v];
                parent[v] = u;
                heap.decreaseKey(v, key[v]);
            }
        }
    }

    delete[] key;
    delete[] parent;

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start);
    return std::make_tuple(mstEdges, mstEdgeCount, mstWeight, duration.count());
}

// Algorytm Prima dla listy sąsiedztwa
std::tuple<Edge*, int, int, double> MSTSolver::primsAlgorithmForList(neighbour** neighboursList, int verticesNumber) {
    auto start = std::chrono::high_resolution_clock::now();

    // Tablica reprezentująca rodziców w MST
    int* parent = new int[verticesNumber];

    // Tablica reprezentująca najmnijeszą znaną wagę krawędzi dla każdego wierzchołka
    int* key = new int[verticesNumber];

    // Tablica wynikowa krawędzi
    Edge* mstEdges = new Edge[verticesNumber - 1];

    int mstWeight = 0;
    int mstEdgeCount = 0;

    // Inicjalizacja kopca minimum dla wierzchołków
    MinimumHeap heap(verticesNumber);

    // Inicjalizacja rodziców i wag
    for (int v = 0; v < verticesNumber; v++) {
        key[v] = INT_MAX;
        parent[v] = -1;
    }

    // Wybór początkowego wierzchołka i dodanie go do kopca
    key[0] = 0;
    heap.decreaseKey(0, 0);

    while (!heap.isEmpty()) {
        // Wybranie najtańszego wierzchołka
        MinimumHeapNode minNode = heap.extractMin();
        int u = minNode.vertex;

        // Dodatnie krawędzi do MST (jeśli nie jest to piewrszy(ma rodzica))
        if (parent[u] != -1) {
            mstEdges[mstEdgeCount] = {parent[u], u, key[u]};
            mstEdgeCount++;
            mstWeight += key[u];
        }

        // Sprawdzenie sąsiadów wierzchołka
        neighbour* current = neighboursList[u];
        while (current!=nullptr) {
            int v = current->vertex;
            int weight = current->weight;

            // Jeśli sąsiad nie jest jeszce w MST i waga krawędzi jest mniejsza niż aktualnie znana najmniejsza to następuje aktualizacja informacji
            if (heap.isInHeap(v) && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                heap.decreaseKey(v, key[v]);
            }
            current = current -> nextVertex;
        }
    }

    delete[] key;
    delete[] parent;

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start);

    return std::make_tuple(mstEdges, mstEdgeCount, mstWeight, duration.count());
}

// Algorytm Kruskala dla listy sąsiedztwa
std::tuple<Edge *, int, int, double> MSTSolver::kruskalsAlgorithmForList(neighbour **neighboursList, int verticesNumber) {
    auto start = std::chrono::high_resolution_clock::now();

    // Przygotowanie listy krawędzi
    Edge* edges;
    int edgeCount = extractEdgesFromNeighboursList(neighboursList, verticesNumber, edges);
    sortEdgesByWeight(edges, 0, edgeCount-1);

    // Inicjalizacja MST
    UnionFind unionFind(verticesNumber);
    Edge* mstEdges = new Edge[verticesNumber - 1];
    int mstWeight = 0;
    int mstEdgeCount = 0;

    // Algorytm Kruskala
    for (int i = 0; i < edgeCount && mstEdgeCount < verticesNumber - 1; ++i) {
        int u = edges[i].u;
        int v = edges[i].v;

        // Sprawdzenie czy wierzchołki należą do różnych zbiorów, jeśli tak to łączenie ich
        if (unionFind.find(u) != unionFind.find(v)) {
            mstEdges[mstEdgeCount] = edges[i];
            mstEdgeCount++;
            mstWeight += edges[i].weight;
            unionFind.unionSets(u, v);
        }
    }

    delete[] edges;

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start);
    return std::make_tuple(mstEdges, mstEdgeCount, mstWeight, duration.count());
}

// Algorym Kruskala dla macierzy sąsiedztwa
std::tuple<Edge *, int, int, double> MSTSolver::kruskalsAlgorithmForMatrix(int **adjacencyMatrix, int verticesNumber) {
    auto start = std::chrono::high_resolution_clock::now();

    // Przygotowanie listy krawędzi
    Edge* edges;
    int edgeCount = extractEdgesFromMatrix(adjacencyMatrix, verticesNumber, edges);
    sortEdgesByWeight(edges, 0, edgeCount-1);

    // Inicjalizacja MST
    UnionFind unionFind(verticesNumber);
    Edge* mstEdges = new Edge[verticesNumber - 1];
    int mstWeight = 0;
    int mstEdgeCount = 0;

    // Algorytm Kruskala
    for (int i = 0; i < edgeCount && mstEdgeCount < verticesNumber - 1; ++i) {
        int u = edges[i].u;
        int v = edges[i].v;

        // Sprawdzenie czy wierzchołki należą do różnych zbiorów, jeśli tak to łączenie ich
        if (unionFind.find(u) != unionFind.find(v)) {
            mstEdges[mstEdgeCount] = edges[i];
            mstEdgeCount++;
            mstWeight += edges[i].weight;
            unionFind.unionSets(u, v);
        }
    }

    delete[] edges;

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start);
    return std::make_tuple(mstEdges, mstEdgeCount, mstWeight, duration.count());
}

// Przekształcenie listy sąsiedztwa w listę krawędzi
int MSTSolver::extractEdgesFromNeighboursList(neighbour** neighboursList, int verticesNumber, Edge*& edgesOut
) {
    int estimatedEdges = 0;

    for (int u = 0; u < verticesNumber; u++) {
        neighbour* current = neighboursList[u];
        while (current!=nullptr) {
            int v = current -> vertex;
            if (u < v) {
                estimatedEdges++;
            }
            current = current -> nextVertex;
        }
    }


    //alokacja tablicy krawędzi
    edgesOut = new Edge[estimatedEdges];
    int edgeIndex = 0;


    for (int u = 0; u < verticesNumber; u++) {
        neighbour* current = neighboursList[u];
        while (current!=nullptr) {
            int v = current -> vertex;
            int w = current -> weight;
            if (u < v) {
                edgesOut[edgeIndex] = {u, v, w};
                edgeIndex++;
            }
            current = current -> nextVertex;
        }
    }

    return estimatedEdges;
}

// Przekształcenie macierzy sąsiedztwa w listę krawędzi
int MSTSolver::extractEdgesFromMatrix(int** adjacencyMatrix, int verticesNumber, Edge*& edgesOut) {
    int estimatedEdges = 0;

    // Zliczanie krawędzi tylko raz dla każdej pary (u, v)
    for (int u = 0; u < verticesNumber; u++) {
        for (int v = u + 1; v < verticesNumber; v++) {
            if (adjacencyMatrix[u][v] > 0) {
                estimatedEdges++;
            }
        }
    }

    //alokacja tablicy krawędzi
    edgesOut = new Edge[estimatedEdges];
    int edgeIndex = 0;

    //umieszczenie krawędzi na liście
    for (int u = 0; u < verticesNumber; u++) {
        for (int v = u + 1; v < verticesNumber; v++) {
            if (adjacencyMatrix[u][v] > 0) {
                edgesOut[edgeIndex] = {u, v, adjacencyMatrix[u][v]};
                edgeIndex++;
            }
        }
    }

    return estimatedEdges;
}

//funkcja sortująca listę krawędzi wg wagi krawędzi
void MSTSolver::sortEdgesByWeight(Edge* edges, int begin, int end) {
    if (begin >= end) return;

    Edge pivot = edges[((end - begin) / 2) + begin];    //wybór środkowego pivota
    swapEdges(edges, ((end-begin)/2)+begin, end);

    int left = begin;
    int right = end-1;

    while (left <= right) {
        while (left <= right && edges[left].weight < pivot.weight) {
            left++;
        }
        while (left <= right && edges[right].weight > pivot.weight) {
            right--;
        }
        if (left <= right) {
            swapEdges(edges, left, right);
            left++;
            right--;
        }
    }

    swapEdges(edges,left,end); // zamiana miejsc pivota

    sortEdgesByWeight(edges, begin, left-1); // lewa podtablica
    sortEdgesByWeight(edges, left+1, end); // prawa podtablica

}

void MSTSolver::swapEdges(Edge* edges, int i, int j) {
    Edge tmp = edges[i];
    edges[i] = edges[j];
    edges[j] = tmp;
}