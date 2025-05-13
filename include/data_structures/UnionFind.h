//
// Created by wiktor on 13.05.2025.
//

#ifndef DISJOINTSET_H
#define DISJOINTSET_H



class UnionFind {
private:
    int* parent;
    int* rank;
    int size;

public:
    UnionFind(int n);
    ~UnionFind();

    int find(int v);
    void unionSets(int u, int v);
};



#endif //DISJOINTSET_H
