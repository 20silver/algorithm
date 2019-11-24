#ifndef PROBLEM_H
#define PROBLEM_H

#include "State.h"


class Problem()
{
public:
    State initialState;
    HashSet<Coordinate> walls;
    HashSet<Coordinate> goals;
    HashMap<Coordinate, Coordinate> blocked;

    Problem(HashSet<Coordinate> walls, State initialState, HashSet<Coordinate> goals);
    bool goalTest(State state);
    bool deadlockTest(State state);
    vector<string> actions(State state);
    bool setContains(HashSet<Coordinate> set, int row, int col);

};