//
// Created by �̿��� on 30/11/2019.
//

#include "Point.h"

Point::Point()
{
	row = -1;
	col = -1;
}
Point::Point(int row, int col)
{
	this->row = row;
	this->col = col;
}
int Point::hashCode() const
{
	return row * 1000 + col;
}
bool Point::operator==(const Point& other) const
{
	return this->hashCode() == other.hashCode();
}