#include "Node.h"

Node::Node() {
	this->parent = (Node*)nullptr;
	this->state = (State*)nullptr;
	this->cost = -1;
	this->move = "";
}

Node::Node(State* state, Node* parent, int cost, string move) {
	this->state = state;
	this->parent = parent;
	this->cost = cost;
	this->move = move;
}

bool Node::operator==(const Node &n) const {
	return (this->state == n.state && this->move == n.move);
}