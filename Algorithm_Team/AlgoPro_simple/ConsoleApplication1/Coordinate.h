#pragma once

#include <cstdlib>

class Coordinate
{
public :
	int row;
	int col;

	Coordinate() {};
	Coordinate(int row, int col);
	int hashCode() const;
	bool equals(Coordinate);

};

