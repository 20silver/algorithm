#include "State.h"

State::State(set<Coordinate> boxes, Coordinate player)
{
	// ���� State �� �ڽ� ��ġ���� ��� �ִ� Set
	this->boxes = &boxes;
	// ���� Player �� ��ġ
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