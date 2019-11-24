#include "Coordinate.h"
Coordinate::Coordinate() {

}
Coordinate::Coordinate(int row, int col){
    this->row = row;
    this->col = col;
}

int Coordinate::hashCode() {
    return row * 1000 + col;
}

bool Coordinate::equals(Coordinate object){
    if(object == NULL)
        return NULL;
    if(object == this)
        return true;
    if(typeid(this) != typeid(object))
        return false;
    Coordinate c = object;
    if(this->hashCode() == c.hashCode())
        return true;
    return((this->row == c.row) && (this->col == c.col));
}
