#include "Node.h"

Node::Node() {
	this->parent = nullptr;
	this->state = nullptr;
	this->cost = NULL;
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