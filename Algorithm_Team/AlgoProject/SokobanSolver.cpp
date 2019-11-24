#include "SokobanSolver.h"

// 문제 받아오기.
int SokobanSolver::loadFile(string filename, char hChoice) {
	int numPlayer = 0;

	// 벽, 골, 박스 위치 저장할 hash_set 생성.
	walls = new hash_set<Coordinate>();
	goals = new hash_set<Coordinate>();
	boxes = new hash_set<Coordinate>();

	// Input 파일 읽어오고...
	ifstream inStream;
	inStream.open("input.txt");
	// 게임 맵은 8x8 이니까 한 번에 8 자씩만 읽어오면 된다.
	char* line;
	row = 8;
	col = 8;
	for (int r = 0; r < row; r++) {
		inStream.getline(line, 8);
		// row 하나 읽기
		for (int c = 0; c < col; c++) {
			char obj = line[c];
			switch (obj) {
				// 아무것도 없는 빈 공간일 때.
			case '4':
				break;
				// 목적지일 때
			case '3':
				goals.insert(new Coordinate(r, c));
				break;
				// 상자일 때
			case '2':
				boxes.insert(new Coordinate(r, c));
				break;
				// 벽일 때
			case '1':
				walls.insert(new Coordinate(r, c));
				break;
				// 벽 안쪽의 캐릭터가 움직일 수 있는 공간일 때
			case '0':
				break;
				// 캐릭터일 때
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
