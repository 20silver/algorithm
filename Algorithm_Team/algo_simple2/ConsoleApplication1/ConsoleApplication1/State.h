#pragma once

#include "Coordinate.h"

#include <set>

using namespace std;

class State
{
public:
	set <Coordinate>* boxes;
	Coordinate* player;

	State(set<Coordinate> boxes, Coordinate player);
	int hashCode() const;
	bool equals(State*);

    bool operator==(const State& other) const;
    bool operator<(const State& other) const;
};

