#ifndef HEURISTICS_H
#define HEURISTICS_H

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
	vector<vector<double>> cost;
	HungarianAlgorithm *h;			// 'e' : ��Ŭ�����, 'm' : ����ź. �� �߿� �ϳ�. �� ���� ���� �Ÿ� ��� ����� �޶���.
	char hChoice;

	// ����ź �Ÿ� ��� ����
	int manhattan(Coordinate *c1, Coordinate *c2);
	// ��Ŭ����� �Ÿ� ��� ����
	double euclidean(Coordinate *c1, Coordinate *c2);
	// ���� �� ����� ����ؼ� �Ÿ� ���.
	double getDist(Coordinate *obj, set<Coordinate> *sets, string method);

public:
	Heuristics(set<Coordinate> *goals, char hChoice);

	double calculate(State *s, string method);

	double getHeuristic(State *state);
};

#endif