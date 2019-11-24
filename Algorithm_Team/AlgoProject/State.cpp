#include "State.h"

#include <iostream>
#include <cstdlib>
#include <set>

using namespace std;

  
State::State(set<Coordinate> *boxes, Coordinate *player){
    this->boxes = boxes;
    this->player = player;
}

int State::hashCode() {
    int result = 17;
	set<Coordinate>::iterator it;
	for (it = boxes->begin(); it != boxes->end(); it++) {
        result = 37 * result + it->hashCode();
    }
    result = 37 * result + player->hashCode();
    return result;
}

bool State::equals(State *object){
    /* 
	if(object == NULL)
        return false;
    if(object == this)
        return true;
	*/
    if(typeid(this) != typeid(object))
        return false;
	State *s = object;
    if (this->hashCode() == s->hashCode())
        return true;
    if ((this->boxes == s->boxes) && (this->player == s->player))
        return true;

    return false;

}
