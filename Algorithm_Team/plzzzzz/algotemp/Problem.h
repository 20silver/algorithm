#pragma once

#include "State.h"

#include <vector>
#include <set>
#include <string>

using namespace std;

class Problem
{
public:
	// Static Datas. ������ �ʴ� ���� ������, ó�� ������ �־����� State.
	set<Coordinate>* walls;
	set<Coordinate>* goals;
	State* initialState;

	// Dynamic Datas. �� �ܰ踶�� ���ϴ� State.
	State* currState;

	// ������
	Problem(set<Coordinate>& walls, State& state, set<Coordinate>& goals);

	bool goalTest(State& state);
	bool deadlockTest(State& state);
	vector<string>* actions(State& state);
	bool setContains(set<Coordinate>& argSet, int row, int col);
};