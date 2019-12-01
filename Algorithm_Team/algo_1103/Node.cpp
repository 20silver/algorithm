//
// Created by �̿��� on 30/11/2019.
//

#include "Node.h"

Node::Node(State where, Node* parent, int move)
{
	this->where = where;
	this->parent = parent;
	this->move = move;
	past = " ";
}
double Node::getDist(Point goal)
{
	return abs(this->where.player.row - goal.row) + abs(this->where.player.col - goal.col);
}

bool Node::operator==(const Node& n) const
{
	return this->where == n.where ;
}
bool Node::operator<(const Node& n) const
{
    return this->f() < n.f();
}
