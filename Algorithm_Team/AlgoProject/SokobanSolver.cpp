#include "SokobanSolver.h"

// ���� �޾ƿ���.
int SokobanSolver::loadFile(string filename, char hChoice) {
	int numPlayer = 0;

	// ��, ��, �ڽ� ��ġ ������ hash_set ����.
	walls = new hash_set<Coordinate>();
	goals = new hash_set<Coordinate>();
	boxes = new hash_set<Coordinate>();

	// Input ���� �о����...
	ifstream inStream;
	inStream.open("input.txt");
	// ���� ���� 8x8 �̴ϱ� �� ���� 8 �ھ��� �о���� �ȴ�.
	char* line;
	row = 8;
	col = 8;
	for (int r = 0; r < row; r++) {
		inStream.getline(line, 8);
		// row �ϳ� �б�
		for (int c = 0; c < col; c++) {
			char obj = line[c];
			switch (obj) {
				// �ƹ��͵� ���� �� ������ ��.
			case '4':
				break;
				// �������� ��
			case '3':
				goals.insert(new Coordinate(r, c));
				break;
				// ������ ��
			case '2':
				boxes.insert(new Coordinate(r, c));
				break;
				// ���� ��
			case '1':
				walls.insert(new Coordinate(r, c));
				break;
				// �� ������ ĳ���Ͱ� ������ �� �ִ� ������ ��
			case '0':
				break;
				// ĳ������ ��
			case '+':
				player = new Coordinate(r, c);
				numPlayer++;
				break;

			}
		}
	}

	prob = new Problem(walls, new State(boxes, player), goals);
	h = new Heuristics(goals, hChoice);

	return numPlayer;
}
