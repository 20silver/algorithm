//
// Created by �̿��� on 30/11/2019.
//

#ifndef LEVEL_H
#define LEVEL_H


#include "State.h"
#include "Node.h"

#include <algorithm>
#include <string>

#include <cstdlib>
#include <deque>
#include <iostream>
#include <queue>

class Level {

public:
	State initialState;
	vector<Point> walls;
	vector<Point> goals;

	Level(State, vector<Point>, vector<Point>);
	
	string solve(string method);

	string bfsSolver();
	string aStarSolver();
	string dfsSolver();

	bool deadlockTest(State& state);
	bool setContains(vector<Point>& argset, const int& row, const int& col);
	vector<string> possibleActions(State& state);
	Node getChild(Node& n, string action);
	bool isSolved(State& state);

};




#endif //AL_ASTAR_LEVEL_H
