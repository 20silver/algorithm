#ifndef SOKOBANSOLVER_H
#define SOKOBANSOLVER_H

#include "Coordinate.h"
#include "Problem.h"
#include "Heuristics.h"
#include "Search.h"

#include <set>
#include <iostream>
#include <fstream>



using namespace std;

class SokobanSolver {
private:
	set<Coordinate> *walls;
	set<Coordinate> *goals;
	set<Coordinate> *boxes;

	Coordinate *player;
	Problem *prob;
	Heuristics *h;

	int row;
	int col;

public :
	SokobanSolver() {}

	
	// ���� �޾ƿ���.
	int loadFile(string filename, char hChoice);



	// ���⼭���ʹ� �׳� ��� ���Ͽ� ����...

	string solve(char method) {
		Search *s = new Search(h);
		switch (method) {
			case 'b':
				return s->bfs(prob);
			case 'd':
				return s->dfs(prob);
			case 'u':
				return s->prioritySearch(prob, 'u');
			case 'a':
				return s->prioritySearch(prob, 'a');
			case 'g':
				return s->prioritySearch(prob, 'g');
			default:
				return "Invalid method, please choose a valid search method.";
		}
	}

	int getRow() {
		return row;
	}

	int getCol() {
		return col;
	}

	set<Coordinate>* getWalls() {
		return walls;
	}

	set<Coordinate>* getBoxes() {
		return boxes;
	}

	set<Coordinate>* getGoals() {
		return goals;
	}

	Coordinate* getPlayer() {
		return player;
	}
};
#endif