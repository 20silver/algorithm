#include "Coordinate.h"

Coordinate::Coordinate(int row, int col)
{
	this->row = row;
	this->col = col;
}


bool Coordinate::operator==(const Coordinate& coord) const {
	return (this->hashCode() == coord.hashCode());
}

Coordinate& Coordinate::operator=(Coordinate& coord) {
	this->row = coord.row;
	this->col = coord.col;
	return *this;
}

bool Coordinate::operator<(const Coordinate& coord) const {
	return (this->row < coord.row || (this->row == coord.row && this->col < coord.col));
}