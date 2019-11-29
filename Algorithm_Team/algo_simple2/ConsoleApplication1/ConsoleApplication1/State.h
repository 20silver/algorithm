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
	State() {};

	int hashCode() const;

	//getters
	set<Coordinate> getBoxes()
	{
		return *boxes;
	}

	Coordinate getPlayer()
	{
		return *player;
	}

	//setters
	void setBoxes(set<Coordinate> *aboxes)
	{
		this->boxes = aboxes;
	}

	void setPlayer(Coordinate *aplayer)
	{
		this->player = aplayer;
	}

    bool operator==(const State& other) const;
    bool operator<(const State& other) const;
};

