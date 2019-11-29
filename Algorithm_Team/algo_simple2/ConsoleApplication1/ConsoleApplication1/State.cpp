#include "State.h"

State::State(set<Coordinate> boxes, Coordinate player)
{
	this->boxes = &boxes;
	this->player = &player;
}

int State::hashCode() const
{
	// ���� State�� ID�� ���� (boxes + player)
	int result = 17;
	set<Coordinate>::iterator it;
	// box���� �ߺ��Ǵ� ��ġ�� ���� hashing�Ѵ�
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

bool State::operator==(const State& other) const
{
	return this->hashCode() == other.hashCode();
}

bool State::operator<(const State& other) const
{
	return (this->hashCode() < other.hashCode());
}