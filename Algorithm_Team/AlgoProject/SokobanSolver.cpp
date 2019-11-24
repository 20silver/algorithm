#include "SokobanSolver.h"

// ���� �޾ƿ���.
int SokobanSolver::loadFile(string filename, char hChoice) {
	int numPlayer = 0;

	// ��, ��, �ڽ� ��ġ ������ hash_set ����.
	walls = new set<Coordinate>();
	goals = new set<Coordinate>();
	boxes = new set<Coordinate>();

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
			Coordinate coord = Coordinate(r, c);
			switch (obj) {
				// �ƹ��͵� ���� �� ������ ��.
			case '4':
				break;
				// �������� ��
			case '3':
				goals->insert(coord);
				break;
				// ������ ��
			case '2':
				boxes->insert(coord);
				break;
				// ���� ��
			case '1':
				walls->insert(coord);
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
