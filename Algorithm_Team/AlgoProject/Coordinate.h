#include <iostream>
#include <cstdlib>

#ifndef COORDINATE_H
#define COORDINATE_H
class Coordinate {
public:
    int row;
    int col;
	
    Coordinate(int row, int col);
    int hashCode() const;
    bool equals(Coordinate *object);
};
#endif