//
// Created by wiktor on 11.05.2025.
//

#ifndef NEIGHBOURSTRUCT_H
#define NEIGHBOURSTRUCT_H

struct neighbour {
    int vertex;
    int weight;
    neighbour* nextVertex;
    neighbour* reverseEdge;
};
#endif //NEIGHBOURSTRUCT_H
