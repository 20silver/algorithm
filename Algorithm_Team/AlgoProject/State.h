#ifndef STATE_H
#define STATE_H

#include "Coordinate.h"

#include <set>


using namespace std;

class State{
public:
    set<Coordinate> *boxes;
    Coordinate *player;

    State(set<Coordinate> *boxes, Coordinate *player);
    int hashCode();
    bool equals(State *object);
};
#endif