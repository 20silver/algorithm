#include "Coordinate.h"
#include "HungarianAlgorithm.h"
#include "State.h"

#include <iostream>
#include <set>
#include <cmath>
#include <vector>

using namespace std;

class Heuristics {
private:
	set<Coordinate> *goals;
	vector<vector<double>> cost(3, vector<double>(3, 0));
	HungarianAlgorithm *h;			// 'e' : 유클리디안, 'm' : 맨하탄. 둘 중에 하나. 이 값에 따라 거리 계산 방법이 달라짐.
	char hChoice;

	// 맨하탄 거리 계산 공식
	int manhattan(Coordinate *c1, Coordinate *c2);
	// 유클리디언 거리 계산 공식
	double euclidean(Coordinate *c1, Coordinate *c2);
	// 위의 두 방법을 사용해서 거리 계산.
	double getDist(const Coordinate *obj, set<Coordinate> *sets, string method);

public:
	Heuristics(set<Coordinate> *goals, char hChoice);

	double calculate(State *s, string method);

	double getHeuristic(State *state);
};