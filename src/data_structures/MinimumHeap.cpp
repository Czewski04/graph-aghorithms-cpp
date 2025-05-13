//
// Created by wiktor on 13.05.2025.
//

#include "../../include/data_structures/MinimumHeap.h"

#include <climits>

MinimumHeap::MinimumHeap(int capacity) {
    // Ustawienie pojemności i początkowego rozmiaru kopca
    this->capacity = capacity;
    size = capacity;

    // Tablica kopca
    heapArray = new MinimumHeapNode[capacity];

    // Tablica reprezentująca pozycje wszystkich wierzchołków w kopcu pozwalająca znajdować je natychmiastowo
    position = new int[capacity];

    //  Inicjalizacja kopca
    for (int v = 0; v < capacity; ++v) {
        heapArray[v].vertex = v;
        heapArray[v].key = INT_MAX;
        position[v] = v;
    }
}

MinimumHeap::~MinimumHeap() {
    delete[] heapArray;
    delete[] position;
}

// Przypwracanie własności kopca
void MinimumHeap::heapifyDown(int index) {
    // Obliczenie indeksów dzieci
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    // Znajdowanie najmiejszego elementu z trójki (rodzic, dzieci)
    if (left < size && heapArray[left].key < heapArray[smallest].key)
        smallest = left;
    if (right < size && heapArray[right].key < heapArray[smallest].key)
        smallest = right;

    // Zamiana węzłów jeśli dzicko < od rodzica
    if (smallest != index) {
        swapNodes(smallest, index);
        heapifyDown(smallest);
    }
}
// Podniesienie elementu w górę kopca jeśli ma mniejszą wagę niż rodzic
void MinimumHeap::heapifyUp(int index) {
    while (index && heapArray[index].key < heapArray[(index - 1) / 2].key) {
        swapNodes(index, (index - 1) / 2);
        index = (index - 1) / 2;
    }
}

bool MinimumHeap::isEmpty() const {
    return size == 0;
}

bool MinimumHeap::isInHeap(int v) const {
    return position[v] < size;
}

// Obniżenie klucza wierzchołka v i przywrócenie struktury kopca
void MinimumHeap::decreaseKey(int v, int key) {
    int i = position[v];
    heapArray[i].key = key;
    heapifyUp(i);
}

// Wyciągnięcie najmiejeszego elementu z kopca
MinimumHeapNode MinimumHeap::extractMin() {
    if (size == 0)
        return {-1, -1};

    MinimumHeapNode root = heapArray[0];
    MinimumHeapNode lastNode = heapArray[size - 1];

    // Zamiana ostatniego elementu z pierwszym
    heapArray[0] = lastNode;
    position[root.vertex] = size - 1;
    position[lastNode.vertex] = 0;

    // Usunięcie ostatniego elementu poprzez redukcję rozmiaru i przywrócenie własności kopca
    size--;
    heapifyDown(0);

    return root;
}

// Funkcja zamieniająca miejscami dwa węzły w kopcu
void MinimumHeap::swapNodes(int i, int j) {
    MinimumHeapNode temp = heapArray[i];
    heapArray[i] = heapArray[j];
    heapArray[j] = temp;

    // Aktualizacja pozycji
    position[heapArray[i].vertex] = i;
    position[heapArray[j].vertex] = j;
}
