#include <iostream>
#include <cstdlib>
#include "Coordinate.h"

using namespace std;

Coordinate::Coordinate(int row, int col){
    this->row = row;
    this->col = col;
}

int Coordinate::hashCode() {
    return row*1000 + col;
}

bool Coordinate::equals(Coordinate object){
    if(object == null)
        return null;
    if(object == this)
        return true;
    if(typeid(this) != typeid(object))
        return false;
    Cooordinate c = object;
    if(this->hashCode() == c->hashCode())
        return true;
    return((this->row == c->row) && (this->col == c->col));
}
