//
// Created by wiktor on 13.05.2025.
//

#include "UnionFind.h"

UnionFind::UnionFind(int n) {
    size = n;               // liczba elementów w zbiorach (liczba wierzchołków)
    parent = new int[n];    // Tablica reprezentująca rodzica dla każdego wierzchołka
    rank = new int[n];      // Tablica reprezentująca głębokość drzewa reprezentującego zbiór

    // Utworzenie zbiorów jednoelementowych
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
        rank[i] = 0;
    }
}

UnionFind::~UnionFind() {
    delete[] parent;
    delete[] rank;
}

// Znalezienie korzenia drzewa, do którego należy dany wierzchołek poprzez rekurencję
int UnionFind::find(int v) {
    if (parent[v] != v) {
        parent[v] = find(parent[v]);
    }
    return parent[v];
}

// Złączenie zbiorów zawierających dane wierzchołki
void UnionFind::unionSets(int u, int v) {
    int rootU = find(u);
    int rootV = find(v);

    if (rootU == rootV)
        return;

    // Porównanie głębokości łączonych zbiorów i przypisanie płytszego do głębszego
    if (rank[rootU] < rank[rootV]) {
        parent[rootU] = rootV;
    } else if (rank[rootU] > rank[rootV]) {
        parent[rootV] = rootU;
    } else {
        parent[rootV] = rootU;
        rank[rootU]++;
    }
}