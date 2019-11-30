//
// Created by ÀÌ¿¬°æ on 30/11/2019.
//

#ifndef LEVEL_H
#define LEVEL_H


#include "State.h"
#include "Node.h"

#include <algorithm>
#include <string>

class Level {

public:
	State initialState;
	vector<Point> walls;
	vector<Point> goals;

	Level(State, vector<Point>, vector<Point>);
	vector<string> possibleActions(State state);
	Node getChild(Node n, string action);
	bool isSolved(State state);

	string bfsSolver();
	string aStarSolver();
	string dfsSolver();

	double manhattan(Point c1, Point c2);
	bool deadlockTest(State state);
	bool setContains(vector<Point> argset, int row, int col);

};




#endif //AL_ASTAR_LEVEL_H
