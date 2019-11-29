#pragma once

#include <vector>
#include <set>
#include <list>
#include <string>
#include <deque>
#include <queue>

// #include "Heuristics.h"
#include "Problem.h"
#include "Node.h"
#include "State.h"

using namespace std;

class Search {
private:
	string BFS = "Breadth-First Search";
	// string DFS;
	// string UCS;
	// string ASTAR;
	// string GREEDY;

	// Heuristics* h; // �Ÿ�����ϴ� Ŭ����..

	string getSolution(string method, Node* n, int totalNode, int redundant, int fringeSize, int exploredSize);
	Node* getChild(Problem& p, Node* n, string action, bool isUcs);

public:
	// Search(Heuristics* h);
	string bfs(Problem& p);
	// string dfs(Problem* p);
	// string prioritySearch(Problem* p, char choice);
};