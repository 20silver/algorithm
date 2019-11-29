#include "State.h"

#include <iostream>

State::State(set<Coordinate> boxes, Coordinate player)
{
	this->boxes = &boxes;
	this->player = &player;
	cout << "state : " << this->boxes->size() << " " << this->player->col << endl;
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


bool State::operator==(const State& other) const
{
	return this->hashCode() == other.hashCode();
}

bool State::operator<(const State& other) const
{
	return (this->hashCode() < other.hashCode());
}