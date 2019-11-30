//
// Created by ÀÌ¿¬°æ on 30/11/2019.
//

#ifndef NODE_H
#define NODE_H


#include "State.h"
#include <string>

class Node {
public:
	Node* parent;
	int move;
	State where;
	int h;
	int f() { return move + h; }

	string past;

	Node(State where, Node* parent, int move);
	double getDist(Point goal);

	bool operator==(const Node& n) const;
};


#endif //AL_ASTAR_NODE_H
