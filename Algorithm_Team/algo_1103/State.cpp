//
// Created by �̿��� on 30/11/2019.
//

#include "State.h"

State::State()
{
	hasData = false;
}

State::State(vector<Point> boxes, Point player)
{
	this->boxes = boxes;
	this->player = player;

	hasData = true;
}

int State::hashCode() const
{
	int result = 17;
	for (int i = 0; i < boxes.size(); i++)
		result = 37 * result + boxes[i].hashCode();

	result = 37 * result + player.hashCode();
	return result;
}

bool State::operator==(const State& n) const
{
	//return this->boxes == n.boxes && this->player == n.player;
	//return this->hashCode() == n.hashCode();

	if (this->hashCode() == n.hashCode()) return true;
	if ((this->boxes == n.boxes) && (this->player == n.player)) return true;
	return false;
}
