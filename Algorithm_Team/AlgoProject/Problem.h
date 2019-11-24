#include "State.h"

#include <vector>
#include <hash_map>
#include <set>
#include <vector>

using namespace std;

#ifndef PROBLEM_H
#define PROBLEM_H
class Problem {
public:
    State *initialState;
    set<Coordinate> walls;
    set<Coordinate> goals;
    set<Coordinate, Coordinate> blocked;

    Problem(set<Coordinate> walls, State *initialState, set<Coordinate> goals);
    bool goalTest(State *state);
    bool deadlockTest(State *state);
    vector<string> actions(State *state);
    bool setContains(set<Coordinate> set, int row, int col);

};
#endif