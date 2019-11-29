#pragma once

#include <cstdlib>

class Coordinate
{
public :
	int row;
	int col;

	Coordinate(int row, int col);
	int hashCode() const;
	bool equals(Coordinate);

    bool operator==(const Coordinate& other) const;
    bool operator<(const Coordinate& other) const;

};

