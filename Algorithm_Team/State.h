#ifndef STATE_H
#define STATE_H
#include "Coordinate.h"
class State{
public:
    HashSet<Coordinate> boxes;
    Coordinate player;

    State(HashSet<Coordinate> boxes, Coordinate player);
    int hashcode();
    bool equals(State object);
};