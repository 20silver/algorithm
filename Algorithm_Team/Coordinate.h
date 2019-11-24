#ifndef COORDINATE_H
#define COORDINATE_H

class Coordinate(){
public:
    int row;
    int col;
    Coordinate(int row, int col);
    int hashCode();
    bool equals(Coordinate object);
};