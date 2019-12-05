//
// Created by �̿��� on 30/11/2019.
//

#ifndef NODE_H
#define NODE_H


#include "State.h"
#include <string>

class Node {
public:
	Node* parent;
	State where;
    float move;
    float h;
    float f() const { return move + h; }

	string past;

	Node() {};
	Node(State where, Node* parent, float move);
    float getDist(Point& goal);
    float getH(vector<Point>& goals);

	bool operator==(const Node& n) const;
    bool operator<(const Node& n) const;
};


#endif //AL_ASTAR_NODE_H
