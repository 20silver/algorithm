//
// Created by �̿��� on 30/11/2019.
//

#include "Level.h"
#include <set>
#include <list>


Level::Level(State state, vector<Point> goals, vector<Point> walls)
{
	this->initialState = state;
	this->goals = goals;
	this->walls = walls;

	cout << "=== init level ===" << endl;
	cout << "-- walls --" << endl;
	for (int i = 0; i < walls.size(); i++)
	{
		cout << walls[i].getRow() << ", " << walls[i].getCol() << endl;
	}
	cout << "-- boxes --" << endl;
	for (int i = 0; i < state.boxes.size(); i++)
	{
		cout << state.boxes[i].getRow() << ", " << state.boxes[i].getCol() << endl;
	}
}

string Level::solve(string method)
{
	string res;
	if (method == "bfs") res = bfsSolver();
	else if (method == "dfs") res = dfsSolver();
	else if (method == "astar") res = aStarSolver();
	return res;
}


vector<string> Level::possibleActions(State& state)
{
	vector<string> actionList;
	actionList.reserve(4);
	int row = state.player.row;
	int col = state.player.col;
	vector<Point> boxes = state.boxes;

	vector<Point>::iterator iter;
	vector<Point>::iterator iter1;
	vector<Point>::iterator iter2;
	vector<Point>::iterator iter3;

	Point newPlayer(row - 1, col);
	Point newBox(row - 2, col);

	iter = find(walls.begin(), walls.end(), newPlayer);
	iter1 = find(boxes.begin(), boxes.end(), newPlayer);
	iter2 = find(boxes.begin(), boxes.end(), newBox);
	iter3 = find(walls.begin(), walls.end(), newBox);

	if (iter == walls.end() && iter1 == boxes.end()) // �÷��̾ �� ���⿡ ���� �ڽ��� ����..
	{
		actionList.push_back("u"); //move
	}
	else if (iter1 != boxes.end()) // �ڽ��� �ִٸ�? Ǫ�� ��������
	{
		if (iter2 == boxes.end() && iter3 == walls.end())
		{
			actionList.push_back("U"); // push
		}
	}

	newPlayer.set(row, col + 1);
	newBox.set(row, col + 2);
	/*newPlayer = new Coordinate(row,col+1);
	newBox = new Coordinate(row, col+2);*/
	iter = find(walls.begin(), walls.end(), newPlayer);
	iter1 = find(boxes.begin(), boxes.end(), newPlayer);
	iter2 = find(boxes.begin(), boxes.end(), newBox);
	iter3 = find(walls.begin(), walls.end(), newBox);

	if (iter == walls.end() && iter1 == boxes.end()) // �÷��̾ �� ���⿡ ���̳� �ڽ��� ����..
	{
		actionList.push_back("r");
	}
	else if (iter1 != boxes.end()) // �ڽ��� �ִٸ�? Ǫ�� ��������
	{
		if (iter2 == boxes.end() && iter3 == walls.end())
		{
			actionList.push_back("R");
		}
	}

	newPlayer.set(row + 1, col);
	newBox.set(row + 2, col);

	iter = find(walls.begin(), walls.end(), newPlayer);
	iter1 = find(boxes.begin(), boxes.end(), newPlayer);
	iter2 = find(boxes.begin(), boxes.end(), newBox);
	iter3 = find(walls.begin(), walls.end(), newBox);
	if (iter == walls.end() && iter1 == boxes.end()) // �÷��̾ �� ���⿡ ���̳� �ڽ��� ����..
	{
		actionList.push_back("d");
	}
	else if (iter1 != boxes.end()) // �ڽ��� �ִٸ�? Ǫ�� ��������
	{
		if (iter2 == boxes.end() && iter3 == walls.end())
		{
			actionList.push_back("D");
		}
	}

	newPlayer.set(row, col - 1);
	newBox.set(row, col - 2);

	iter = find(walls.begin(), walls.end(), newPlayer);
	iter1 = find(boxes.begin(), boxes.end(), newPlayer);
	iter2 = find(boxes.begin(), boxes.end(), newBox);
	iter3 = find(walls.begin(), walls.end(), newBox);
	if (iter == walls.end() && iter1 == boxes.end()) // �÷��̾ �� ���⿡ ���̳� �ڽ��� ����..
	{
		actionList.push_back("l");
	}
	else if (iter1 != boxes.end()) // �ڽ��� �ִٸ�? Ǫ�� ��������
	{
		if (iter2 == boxes.end() && iter3 == walls.end())
		{
			actionList.push_back("L");
		}
	}
	return actionList;
}
string Level::bfsSolver()
{
	string res = "";
	Node node(initialState, NULL, 0);

	vector<string> actionList;
	vector<State> visited;

	deque<Node> q;
	q.push_back(node);

	vector<State>::iterator it_visited;
	deque<Node>::iterator it_q;

	int itrCount = 0;

	// visited�� �ֱ� ���� �ִ��� �˻��ϱ� 
	while (!q.empty())
	{
		cout << ++itrCount << endl;

		node = q.front();
		q.pop_front();
		visited.push_back(node.where);

		//	cout << "---curr node position" << node.where.player.getRow() << "," << node.where.player.getCol() << endl;

		actionList = possibleActions(node.where); //get possible action list of current state
		for (int i = 0; i < actionList.size(); i++)
		{
			//	cout << "can go to " << actionList[i] << endl;
			Node child = getChild(node, actionList[i]); // get child of current node

	///		cout << "past path of curr child : " << child.past << endl;

			it_visited = find(visited.begin(), visited.end(), child.where);
			it_q = find(q.begin(), q.end(), child);
			if (it_visited == visited.end() && it_q == q.end())
			{
				if (isSolved(child.where))
					return child.past;
				if (!deadlockTest(child.where))
					q.push_back(child);
			}
		}
	}

	res = "failed to solve";
	return res;
}

string Level::dfsSolver()
{
	string res = "";
	Node node(initialState, NULL, 0);

	vector<string> actionList;
	vector<State> visited;

	deque<Node> s;

	vector<State>::iterator it_visited;
	deque<Node>::iterator it_s;

	s.push_back(node);
	while (!s.empty()) {
		node = s.back();
		s.pop_back();
		visited.push_back(node.where);
		actionList = possibleActions(node.where);
		for (int i = 0; i < actionList.size(); i++)
		{
			Node child = getChild(node, actionList[i]);
			it_visited = find(visited.begin(), visited.end(), child.where);
			it_s = find(s.begin(), s.end(), child);
			if (it_visited == visited.end() && it_s == s.end())
			{
				if (isSolved(child.where))
					return child.past;
				if (!deadlockTest(child.where))
					s.push_back(child);
			}
		}
	}

	return "fail to solve";
}

bool Level::isSolved(State& state)
{
	vector<Point>::iterator it_goal, it_box;
	for (it_box = state.boxes.begin(); it_box != state.boxes.end(); it_box++)
	{
		it_goal = find(goals.begin(), goals.end(), *it_box);
		if (it_goal == goals.end())
			return false;
	}
	return true;
}

void setPrint(list<Node> set, int min)
{
	cout << "set print" << endl;
	if (min > 0)
	{
		while (set.size() != 0)
		{
			if (set.front().f() == min)
			{
				cout << set.front().move << " " << set.front().h << endl;
				cout << set.front().past << endl;
			}
			set.erase(set.begin());
		}
		return;
	}
	list<Node>::iterator it = set.begin();
	while (set.size() != 0)
	{

		cout << set.front().move << " " << set.front().h << endl;
		cout << set.front().past << endl;

		set.erase(set.begin());

	}
}

// todo:
string Level::aStarSolver() {

	list<Node> open;
	set<Node> close;

	// start node
	Node curr(initialState, nullptr, 0.0f);
	Node child;

	curr.h = 0.0f;
	open.push_back(curr);

	int tmpCount = 0;

	vector<string>actionList;
	list<Node>::iterator it_open;
	list<Node>::reverse_iterator rit_open;
	set<Node>::iterator it_close;

	while (!open.empty())
	{
		tmpCount++;
		cout << "====ITERATION COUNT " << tmpCount << "======" << endl;

		//// open에서 가장 작은 비용 노드를 가져온 것이 curr가 됨..
		it_open = min_element(open.begin(), open.end());
		curr = *it_open;
		//		cout << "curr " << curr.h << curr.move << curr.f() << endl;
		//		setPrint(open, 0);
		open.erase(it_open);
		//	open.erase((++rit_open).base());

		if (isSolved(curr.where))
		{
			cout << "iter count : " << tmpCount << endl;
			cout << "open size : " << open.size() << endl;
			cout << "close size : " << close.size() << endl;
			return curr.past;
		}

		close.insert(curr);

		//		cout << "closed path : " << curr.past << endl;

		actionList = possibleActions(curr.where);
		//cout << "current pos : " << curr.where.player.getRow() << ", " << curr.where.player.getCol() << endl;

		for (const auto& i : actionList)
		{
			child = getChild(curr, i);
			//cout << "child :" << child.past << endl;
			if (deadlockTest(child.where)) continue;

			it_close = find(close.begin(), close.end(), child);
			if (it_close != close.end())
			{
				continue;
			}


			it_open = find(open.begin(), open.end(), child);

			child.h = child.getH(goals);

			if (it_open != open.end())
			{
				if (child.move < (*it_open).move) (*it_open) = child;
			}
			else
				open.push_back(child);
		}
	}

	return "No Solution";
}

Node Level::getChild(Node& n, string action)
{
	int row = n.where.player.getRow();
	int col = n.where.player.getCol();
	float move = n.move + 1.0f;

	Point newPlayer;
	Point newBox;
	vector<Point> boxes = n.where.boxes;

	vector<Point>::iterator it;

	char dir = action[0];
	switch (dir)
	{
	case 'U':
	case 'u':
		newPlayer.set(row - 1, col);
		// �÷��̾ �ڽ��� �а� ����?
		it = find(boxes.begin(), boxes.end(), newPlayer);
		if (it != boxes.end())
		{
			Point newBox(row - 2, col);
			boxes.erase(it);
			boxes.push_back(newBox);
		}
		break;
	case 'D':
	case 'd':
		newPlayer.set(row + 1, col);
		// �÷��̾ �ڽ��� �а� ����?
		it = find(boxes.begin(), boxes.end(), newPlayer);
		if (it != boxes.end())
		{
			Point newBox(row + 2, col);
			boxes.erase(it);
			boxes.push_back(newBox);
		}
		break;
	case 'L':
	case 'l':
		newPlayer.set(row, col - 1);
		// �÷��̾ �ڽ��� �а� ����?
		it = find(boxes.begin(), boxes.end(), newPlayer);
		if (it != boxes.end())
		{
			Point newBox(row, col - 2);
			boxes.erase(it);
			boxes.push_back(newBox);
		}
		break;
	case 'R':
	case 'r':
		newPlayer.set(row, col + 1);
		// �÷��̾ �ڽ��� �а� ����?
		it = find(boxes.begin(), boxes.end(), newPlayer);
		if (it != boxes.end())
		{
			Point newBox(row, col + 2);
			boxes.erase(it);
			boxes.push_back(newBox);
		}
		break;
	}

	State new_state(boxes, newPlayer);
	Node res(new_state, &n, move);
	res.past = n.past + action;
	return res;
}


bool Level::deadlockTest(State& state) {
	vector<Point>::iterator it;
	for (it = state.boxes.begin(); it != state.boxes.end(); it++) {
		int row = (*it).row;
		int col = (*it).col;
		if (!setContains(goals, row, col)) {
			if (setContains(walls, row - 1, col) && setContains(walls, row, col - 1))
				return true; //top & left
			if (setContains(walls, row - 1, col) && setContains(walls, row, col + 1))
				return true; //top & right
			if (setContains(walls, row + 1, col) && setContains(walls, row, col - 1))
				return true; //bottom & left
			if (setContains(walls, row + 1, col) && setContains(walls, row, col + 1))
				return true; //bottom & right

			if (setContains(walls, row - 1, col - 1) && setContains(walls, row - 1, col) &&
				setContains(walls, row - 1, col + 1) && setContains(walls, row, col - 2) &&
				setContains(walls, row, col + 2) && (!setContains(goals, row, col - 1)) &&
				!setContains(goals, row, col + 1))
				return true; //top & sides
			if (setContains(walls, row + 1, col - 1) && setContains(walls, row + 1, col) &&
				setContains(walls, row + 1, col + 1) && setContains(walls, row, col - 2) &&
				setContains(walls, row, col + 2) && (!setContains(goals, row, col - 1)) &&
				(!setContains(goals, row, col + 1)))
				return true; //bottom & sides
			if (setContains(walls, row - 1, col - 1) && setContains(walls, row, col - 1) &&
				setContains(walls, row + 1, col - 1) && setContains(walls, row - 2, col) &&
				setContains(walls, row + 2, col) && (!setContains(goals, row - 1, col)) &&
				(!setContains(goals, row + 1, col)))
				return true; //left & vertical
			if (setContains(walls, row - 1, col + 1) && setContains(walls, row, col + 1) &&
				setContains(walls, row + 1, col + 1) && setContains(walls, row - 2, col) &&
				setContains(walls, row + 2, col) && (!setContains(goals, row - 1, col)) &&
				(!setContains(goals, row + 1, col)))
				return true; //right & top/bottom
		}
	}
	return false;
}

bool Level::setContains(vector<Point>& argset, const int& row, const int& col) {
	Point temp(row, col);
	vector<Point>::iterator iter;
	iter = find(argset.begin(), argset.end(), temp);
	if (iter != argset.end())
		return true;
	return false;
}