#include "Problem.h"

Problem::Problem(set<Coordinate>& walls, State& state, set<Coordinate>& goals) {
	this->walls = &walls;
	this->goals = &goals;
	this->initialState = &state;
}


// 여기서 이항'<' 연산자 에러남...
// 모든 박스가 목적지에 도달했는지.. 게임 클리어 조건을 확인
bool Problem::goalTest(State& state) {
	set<Coordinate>::iterator boxIter;
	set<Coordinate>::iterator goalIter;
	set<Coordinate>* currBoxes = state.boxes;
	for (boxIter = currBoxes->begin(); boxIter != currBoxes->end(); boxIter++) {
		// 이 박스가 하나라도 골에 없으면 false 임...
		if (goals->find(*boxIter) == goals->end())
			return false;
	}
	return true;
}

bool Problem::deadlockTest(State& state) {
	set<Coordinate>::iterator boxIter;
	for (boxIter = state.boxes->begin(); boxIter != state.boxes->end(); boxIter++) {
		int row = (*boxIter).row;
		int col = (*boxIter).col;
		if (!setContains(*goals, row, col)) {
			if (setContains(*walls, row - 1, col) && setContains(*walls, row, col - 1))
				return true; // 상자의 top & left 가 벽으로 박힌 경우
			if (setContains(*walls, row - 1, col) && setContains(*walls, row, col + 1))
				return true; //top & right
			if (setContains(*walls, row + 1, col) && setContains(*walls, row, col - 1))
				return true; //bottom & left
			if (setContains(*walls, row + 1, col) && setContains(*walls, row, col + 1))
				return true; //bottom & right

			if (setContains(*walls, row - 1, col - 1) && setContains(*walls, row - 1, col) &&
				setContains(*walls, row - 1, col + 1) && setContains(*walls, row, col - 2) &&
				setContains(*walls, row, col + 2) && (!setContains(*goals, row, col - 1)) &&
				!setContains(*goals, row, col + 1))
				return true; //top & sides
			if (setContains(*walls, row + 1, col - 1) && setContains(*walls, row + 1, col) &&
				setContains(*walls, row + 1, col + 1) && setContains(*walls, row, col - 2) &&
				setContains(*walls, row, col + 2) && (!setContains(*goals, row, col - 1)) &&
				(!setContains(*goals, row, col + 1)))
				return true; //bottom & sides
			if (setContains(*walls, row - 1, col - 1) && setContains(*walls, row, col - 1) &&
				setContains(*walls, row + 1, col - 1) && setContains(*walls, row - 2, col) &&
				setContains(*walls, row + 2, col) && (!setContains(*goals, row - 1, col)) &&
				(!setContains(*goals, row + 1, col)))
				return true; //left & vertical
			if (setContains(*walls, row - 1, col + 1) && setContains(*walls, row, col + 1) &&
				setContains(*walls, row + 1, col + 1) && setContains(*walls, row - 2, col) &&
				setContains(*walls, row + 2, col) && (!setContains(*goals, row - 1, col)) &&
				(!setContains(*goals, row + 1, col)))
				return true; //right & top/bottom
		}
	}
	return false;
}


// 여기서도
vector<string>* Problem::actions(State& state) {
	vector<string>* actionList = new vector<string>();

	int row = state.player->row;
	int col = state.player->col;

	set<Coordinate>* currBoxes = state.boxes;

	Coordinate* newPlayer = new Coordinate(row - 1, col);
	Coordinate* newBox = new Coordinate(row - 2, col);
	// 플레이어가 이동할 곳이 벽이 아니면...
	if (walls->find(*newPlayer) == walls->end())
		// 플레이어가 이동할 곳에 박스가 있지만, 그 뒤에 박스가 또 있거나 벽이 있으면...
		if (currBoxes->find(*newPlayer) != currBoxes->end() && (currBoxes->find(*newBox) != currBoxes->end() || walls->find(*newBox) != currBoxes->end()));
		else
			actionList->push_back("u");

	newPlayer->set(row, col + 1);
	newBox->set(row, col + 2);
	if (walls->find(*newPlayer) == walls->end())
		// 플레이어가 이동할 곳에 박스가 있지만, 그 뒤에 박스가 또 있거나 벽이 있으면...
		if (currBoxes->find(*newPlayer) != currBoxes->end() && (currBoxes->find(*newBox) != currBoxes->end() || walls->find(*newBox) != currBoxes->end()));
		else
			actionList->push_back("r");


	newPlayer->set(row + 1, col);
	newBox->set(row + 2, col);
	if (walls->find(*newPlayer) == walls->end())
		// 플레이어가 이동할 곳에 박스가 있지만, 그 뒤에 박스가 또 있거나 벽이 있으면...
		if (currBoxes->find(*newPlayer) != currBoxes->end() && (currBoxes->find(*newBox) != currBoxes->end() || walls->find(*newBox) != currBoxes->end()));
		else
			actionList->push_back("d");

	newPlayer->set(row, col - 1);
	newBox->set(row, col - 2);
	if (walls->find(*newPlayer) == walls->end())
		// 플레이어가 이동할 곳에 박스가 있지만, 그 뒤에 박스가 또 있거나 벽이 있으면...
		if (currBoxes->find(*newPlayer) != currBoxes->end() && (currBoxes->find(*newBox) != currBoxes->end() || walls->find(*newBox) != currBoxes->end()));
		else
			actionList->push_back("l");

	return actionList;
}

// 여기서도 이항 '<' 연산자 에러..
bool Problem::setContains(set<Coordinate>& argSet, int row, int col) {
	set<Coordinate>::iterator coordIter;
	if (argSet.find(Coordinate(row, col)) != argSet.end())
		return true;
	return false;
}