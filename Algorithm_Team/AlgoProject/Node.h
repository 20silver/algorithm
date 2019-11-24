#include "State.h"

#include <iostream>

using namespace std;

#ifndef NODE_H
#define NODE_H
class Node {
public:
	Node parent;
	State state;
	int cost;
	string move;


	Node(State state, Node parent, int cost, string move);
	bool equals(Node n);
};
#endif