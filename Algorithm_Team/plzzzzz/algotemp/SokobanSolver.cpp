#include "SokobanSolver.h"

#include <fstream>
#include <vector>

void SokobanSolver::loadFile(string fileName) {
	col = 0;
	int numPlayer = 0;

	walls = new set<Coordinate>();
	goals = new set<Coordinate>();
	boxes = new set<Coordinate>();
	
	Coordinate *coord = new Coordinate();

	ifstream inStream;
	inStream.open("input.txt");

	int testCases;
	inStream >> testCases;

	for (int t = 0; t < testCases; t++) {
		int row; int col;
		inStream >> row >> col;

		cout << "row : " << row << " /// col : " << col << endl;

		for (int r = 0; r < row; r++){
			for (int c = 0; c < col; c++){
				int num; 
				inStream >> num;
				coord->set(r, c);
				// ���� ��
				if (num == 1) {
					walls->insert(*coord);
				}
				// �ڽ��� ��
				else if (num == 2) {
					boxes->insert(*coord);
				}
				// �������� ��
				else if (num == 3){
					goals->insert(*coord);
				}
				//�÷��̾��� ��
				else if (c == 5) {
					player->set(row, col);
				}
			}
		}
		State *initial_state = new State(*boxes, *player);
		prob = new Problem(*walls, *initial_state, *goals);

		// bfs �� �� ���ϱ�.
		string solution = solve('b');
	}
}