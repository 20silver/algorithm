#include "Coordinate.h"

Coordinate::Coordinate(int row, int col){
    this->row = row;
    this->col = col;
}

int Coordinate::hashCode() const {
    return row * 1000 + col;
}

bool Coordinate::equals(Coordinate *object){
    if(this->hashCode() == object->hashCode())
        return true;
    return((this->row == object->row) && (this->col == object->col));
}
