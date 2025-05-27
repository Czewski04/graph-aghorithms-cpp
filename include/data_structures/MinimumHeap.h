//
// Created by wiktor on 13.05.2025.
//

#ifndef MINIMUMHEAP_H
#define MINIMUMHEAP_H
#include "MinimumHeapNode.h"


class MinimumHeap {
private:
    MinimumHeapNode* heapArray;
    int* position;
    int size;
    int capacity;

    void heapifyDown(int index);
    void heapifyUp(int index);
    void swapNodes(int i, int j);

public:
    explicit MinimumHeap(int capacity);
    ~MinimumHeap();

    bool isEmpty() const;
    bool isInHeap(int v) const;
    void decreaseKey(int v, int key);
    MinimumHeapNode extractMin();
};



#endif //MINIMUMHEAP_H
