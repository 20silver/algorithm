#pragma once

#include "State.h"

#include <iostream>

using namespace std;


class Node {
public:
	Node* parent;
	State* state;
	int cost;
	string move;

	Node();
	Node(State* state, Node* parent, int cost, string move);
	bool operator==(const Node &n) const;
};