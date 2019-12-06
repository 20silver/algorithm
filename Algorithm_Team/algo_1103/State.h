//
// Created by ÀÌ¿¬°æ on 30/11/2019.
//

#ifndef STATE_H
#define STATE_H

#include "Point.h"

#include <vector>

using namespace std;

class State {
public:
	vector<Point> boxes;
	Point player;
	bool hasData;

	State();
	State(vector<Point> boxes, Point player);
	int hashCode() const;

	bool operator==(const State& n) const;
	bool operator<(const State& n) const;
};


#endif
