#include "Problem.h"

Problem::Problem(set<Coordinate>& walls, State& state, set<Coordinate>& goals) {
	this->walls = &walls;
	this->goals = &goals;
	this->initialState = &state;
}


// ���⼭ ����'<' ������ ������...
// ��� �ڽ��� �������� �����ߴ���.. ���� Ŭ���� ������ Ȯ��
bool Problem::goalTest(State& state) {
	set<Coordinate>::iterator boxIter;
	set<Coordinate>::iterator goalIter;
	set<Coordinate>* currBoxes = state.boxes;
	for (boxIter = currBoxes->begin(); boxIter != currBoxes->end(); boxIter++) {
		// �� �ڽ��� �ϳ��� �� ������ false ��...
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
				return true; // ������ top & left �� ������ ���� ���
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


// ���⼭��
vector<string>* Problem::actions(State& state) {
	vector<string>* actionList = new vector<string>();

	int row = state.player->row;
	int col = state.player->col;

	set<Coordinate>* currBoxes = state.boxes;

	Coordinate* newPlayer = new Coordinate(row - 1, col);
	Coordinate* newBox = new Coordinate(row - 2, col);
	// �÷��̾ �̵��� ���� ���� �ƴϸ�...
	if (walls->find(*newPlayer) == walls->end())
		// �÷��̾ �̵��� ���� �ڽ��� ������, �� �ڿ� �ڽ��� �� �ְų� ���� ������...
		if (currBoxes->find(*newPlayer) != currBoxes->end() && (currBoxes->find(*newBox) != currBoxes->end() || walls->find(*newBox) != currBoxes->end()));
		else
			actionList->push_back("u");

	newPlayer->set(row, col + 1);
	newBox->set(row, col + 2);
	if (walls->find(*newPlayer) == walls->end())
		// �÷��̾ �̵��� ���� �ڽ��� ������, �� �ڿ� �ڽ��� �� �ְų� ���� ������...
		if (currBoxes->find(*newPlayer) != currBoxes->end() && (currBoxes->find(*newBox) != currBoxes->end() || walls->find(*newBox) != currBoxes->end()));
		else
			actionList->push_back("r");


	newPlayer->set(row + 1, col);
	newBox->set(row + 2, col);
	if (walls->find(*newPlayer) == walls->end())
		// �÷��̾ �̵��� ���� �ڽ��� ������, �� �ڿ� �ڽ��� �� �ְų� ���� ������...
		if (currBoxes->find(*newPlayer) != currBoxes->end() && (currBoxes->find(*newBox) != currBoxes->end() || walls->find(*newBox) != currBoxes->end()));
		else
			actionList->push_back("d");

	newPlayer->set(row, col - 1);
	newBox->set(row, col - 2);
	if (walls->find(*newPlayer) == walls->end())
		// �÷��̾ �̵��� ���� �ڽ��� ������, �� �ڿ� �ڽ��� �� �ְų� ���� ������...
		if (currBoxes->find(*newPlayer) != currBoxes->end() && (currBoxes->find(*newBox) != currBoxes->end() || walls->find(*newBox) != currBoxes->end()));
		else
			actionList->push_back("l");

	return actionList;
}

// ���⼭�� ���� '<' ������ ����..
bool Problem::setContains(set<Coordinate>& argSet, int row, int col) {
	set<Coordinate>::iterator coordIter;
	if (argSet.find(Coordinate(row, col)) != argSet.end())
		return true;
	return false;
}