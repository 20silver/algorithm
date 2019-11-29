#include "Coordinate.h"

Coordinate::Coordinate(int row, int col)
{
	this->row = row;
	this->col = col;
}

int Coordinate::hashCode() const {
	return row * 1000 + col;
}

bool Coordinate::operator==(const Coordinate& other) const
{
	return (hashCode() == other.hashCode());
}

bool Coordinate::operator<(const Coordinate& other) const
{
	return (hashCode() < other.hashCode());
}

Coordinate& Coordinate::operator=(Coordinate& coord) {
	this->row = coord.row;
	this->col = coord.col;
	return *this;
}
