#pragma once

#include "State.h"

#include <vector>
#include <set>

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
	bool move(Coordinate* new_player, Coordinate* new_box);
	bool push(State* state);

	// set contains? -> for deadlockTest
	
};

