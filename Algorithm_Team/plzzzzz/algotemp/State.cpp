#include "State.h"

State::State(set<Coordinate> boxes, Coordinate player)
{
	// 현재 State 의 박스 위치들을 담고 있는 Set
	this->boxes = &boxes;
	// 현재 Player 의 위치
	this->player = &player;
}

int State::hashCode()
{
	int result = 17;
	set<Coordinate>::iterator it;
	for (it = boxes->begin(); it != boxes->end(); it++)
		result = 37 * result + it->hashCode();

	// add player hashing
	result = 37 * result + player->hashCode();
	return result;
}

bool State::operator==(State& other)
{
	if (this->hashCode() == other.hashCode()) return true;
	return (this->boxes == other.boxes) && (this->player == other.player);
}