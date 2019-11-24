#include "Node.h"

Node::Node(State state, Node parent, int cost, string move) {
	this-state = state;
	this->parent = parent;
	this->cost = cost;
	this->move = move;
}


bool Node::equals(Node n) {
	return (this->state == n.state);
}