#pragma once

#include "State.h"

#include <vector>
#include <set>
#include <string>

using namespace std;

class Problem
{
public:
	// Static Datas. 변하지 않는 벽과 목적지, 처음 문제로 주어지는 State.
	set<Coordinate>* walls;
	set<Coordinate>* goals;
	State* initialState;

	// Dynamic Datas. 매 단계마다 변하는 State.
	State* currState;

	// 생성자
	Problem(set<Coordinate>& walls, State& state, set<Coordinate>& goals);

	bool goalTest(State& state);
	bool deadlockTest(State& state);
	vector<string>* actions(State& state);
	bool setContains(set<Coordinate>& argSet, int row, int col);
};