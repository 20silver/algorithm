#include <hash_set>
#include <iostream>
#include <fStream>

#ifndef SOKOBANSOLVER_H
#define SOKOBANSOLVER_H

using namespace std;

class SokobanSolver {
private:
	hash_set<Coordinate> walls;
	hash_set<Coordinate> goals;
	hash_set<Coordinate> boxes;

	Coordinate player;
	Problem prob;
	Heuristics h;

	int row;
	int col;

public :
	SokobanSolver() {}

	
	// ���� �޾ƿ���.
	int loadFile(string filename, char hChoice);



	// ���⼭���ʹ� �׳� ��� ���Ͽ� ����...

	string solve(char method) {
		Search s = new Search(h);
		switch (method) {
			case 'b':
				return s.bfs(prob);
			case 'd':
				return s.dfs(prob);
			case 'u':
				return s.prioritySearch(prob, 'u');
			case 'a':
				return s.prioritySearch(prob, 'a');
			case 'g':
				return s.prioritySearch(prob, 'g');
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

	hash_set<Coordinate> getWalls() {
		return walls;
	}

	hash_set<Coordinate> getBoxes() {
		return boxes;
	}

	hash_set<Coordinate> getGoals() {
		return goals;
	}

	Coordinate getPlayer() {
		return player;
	}
};
#endif