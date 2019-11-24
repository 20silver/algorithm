#include "Coordinate.h"

#include <set>

using namespace std;

#ifndef STATE_H
#define STATE_H
class State{
public:
    set<Coordinate> boxes;
    Coordinate player;

    State(set<Coordinate> boxes, Coordinate player);
    int hashCode();
    bool equals(State object);
};
#endif