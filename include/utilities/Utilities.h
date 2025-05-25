//
// Created by Wiktor on 25.05.2025.
//

#ifndef UTILITIES_H
#define UTILITIES_H


#include "NeighbourStruct.h"

class Utilities {
public:
    static void deleteLinkedList(neighbour* head);
    static void addVertexToNeighbourList(neighbour**& neighboursList, int u, int v, int w);
};


#endif //UTILITIES_H
