#include "State.h"

State::State(set<Coordinate>* boxes, Coordinate* player)
{
	this->boxes = boxes;
	this->player = player;
}

int State::hashCode()
{
	// 현재 State의 ID를 만듬 (boxes + player)
	int result = 17;
	set<Coordinate>::iterator it;
	// box들을 중복되는 위치가 없게 hashing한다
	for (it = boxes->begin(); it != boxes->end(); it++)
		result = 37 * result + it->hashCode();

	// add player hashing
	result = 37 * result + player->hashCode();
	return result; 
}

bool State::equals(State* other)
{
	if (this->hashCode() == other->hashCode()) return true;
	return (this->boxes == other->boxes) && (this->player == other->player);
}