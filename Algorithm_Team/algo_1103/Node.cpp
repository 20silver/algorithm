//
// Created by �̿��� on 30/11/2019.
//

#include "Node.h"
#include <iostream>
#include <cmath>

Node::Node(State where, Node* parent, float move)
{
	this->where = where;
	this->parent = parent;
	this->move = move;
	past = "";
}
float Node::getDist(Point& goal) //manhattan distance..
{
	return abs(this->where.player.row - goal.row) + abs(this->where.player.col - goal.col);
}

int manhattan(Point p1, Point p2)
{
	return abs(p1.col - p2.col) + abs(p1.row - p2.row);
}
float euclidean(Point p1, Point p2)
{
	return sqrt((float)((p1.row - p2.row)*(p1.row - p2.row)+(p1.col - p2.col) * (p1.col - p2.col)));
}

float Node::getH(vector<Point>& goals)
{
	float sum = 0;
    float min = 1000000;
	int minIdx = 0;
    float dist = 0;

	// sum of player - boxes
	for (int i = 0; i < where.boxes.size(); i++)
	{
		dist = manhattan(where.player, where.boxes[i]);
		//sum += manhattan(where.player, where.boxes[i]);
		if (min > dist) min = dist;
	}
	sum += min;

	// sum of min distances of between boxes and goals
	// use greedy approach
	vector<bool> matched(goals.size(), false);

	for (int j = 0; j < where.boxes.size(); j++)
	{
		minIdx = 0;
		min = 1000000;

		for (int i = 0;i < goals.size(); i++)
		{
			if (matched[i]) continue;
			dist = manhattan(where.boxes[j], goals[i]);
			if (dist < min)
			{
				min = dist;
				minIdx = i;
			}
		}
		matched[minIdx] = true; // mark 
		sum += min;
	}
	//cout << "h : " << sum << endl;
	return sum;
}


bool Node::operator==(const Node& n) const
{
	return this->where == n.where;
}
bool Node::operator<(const Node& n) const
{
	return this->f() < n.f();
}
