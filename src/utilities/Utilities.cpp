//
// Created by Wiktor on 25.05.2025.
//

#include "Utilities.h"


void Utilities::deleteLinkedList(neighbour *head) {
    neighbour* current = head;
    while (current != nullptr) {
        neighbour* next = current->nextVertex; // Zapisz wskaźnik na następny element
        delete current; // Usuń bieżący element
        current = next; // Przejdź do następnego
    }
}

void Utilities::addVertexToNeighbourList(neighbour **&neighboursList, int u, int v, int w) {
    if (neighboursList[u] == nullptr) {
        neighboursList[u] = new neighbour;
        neighboursList[u]->vertex = v;
        neighboursList[u]->weight = w;
        neighboursList[u]->nextVertex = nullptr;

    }
    else {
        neighbour* current = neighboursList[u];
        while (current->nextVertex != nullptr) {
            current = current->nextVertex;
        }
        current->nextVertex = new neighbour;
        current->nextVertex->vertex = v;
        current->nextVertex->weight = w;
        current->nextVertex->nextVertex = nullptr;
    }
}