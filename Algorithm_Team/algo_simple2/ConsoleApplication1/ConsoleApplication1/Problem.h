#pragma once

#include "State.h"

#include <vector>
#include <set>
#include <string>
#include <queue>
#include <tuple>

using namespace std;

class Problem
{
public:
	// static datas
	set<Coordinate>* walls;
	set<Coordinate>* goals;

	// dynamic datas
    State* initialState;

	State* currState;

	Problem(State*, set<Coordinate>*, set<Coordinate>*);
	bool isSolved(State* state);
	bool deadlockTest(State* state);
    State* move(Coordinate* new_player);
    State* push(Coordinate* new_player, int dir);
	string bfsSolver();

	// set contains? -> for deadlockTest
	
};

