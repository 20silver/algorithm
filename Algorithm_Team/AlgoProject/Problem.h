#ifndef PROBLEM_H
#define PROBLEM_H

#include "State.h"

#include <vector>
#include <set>
#include <vector>

using namespace std;


class Problem {
public:
    State *initialState;
    set<Coordinate> walls;
    set<Coordinate> goals;
    set<Coordinate, Coordinate> blocked;

    Problem(set<Coordinate> *walls, State *initialState, set<Coordinate> *goals);
    bool goalTest(State *state);
    bool deadlockTest(State *state);
    vector<string> actions(State *state);
    bool setContains(set<Coordinate> set, int row, int col);

};
#endif