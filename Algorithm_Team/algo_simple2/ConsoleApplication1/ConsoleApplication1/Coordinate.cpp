#include "Coordinate.h"

Coordinate::Coordinate(int row, int col)
{
	this->row = row;
	this->col = col;
}

int Coordinate::hashCode() const {
	return row * 1000 + col;
}

bool Coordinate::equals(Coordinate c)
{
	return ((this->row == c.row) && (this->col == c.col));
}

bool Coordinate::operator==(const Coordinate& other) const
{
	return (hashCode() == other.hashCode());
}

bool Coordinate::operator<(const Coordinate& other) const
{
	return (hashCode() < other.hashCode());
}
