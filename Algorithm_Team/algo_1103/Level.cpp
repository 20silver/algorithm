//
// Created by �̿��� on 30/11/2019.
//

#include "Level.h"

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
vector<string> Level::possibleActions(State state)
{
	vector<string> actionList;
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

	// visited�� �ֱ� ���� �ִ��� �˻��ϱ� 
	while (!q.empty())
	{
		node = q.front();
		q.pop_front();
		visited.push_back(node.where);

		cout << "---curr node position" << node.where.player.getRow() << "," << node.where.player.getCol() << endl;

		actionList = possibleActions(node.where); //get possible action list of current state
		for (int i = 0; i < actionList.size(); i++)
		{
			cout << "can go to " << actionList[i] << endl;
			Node child = getChild(node, actionList[i]); // get child of current node

			cout << "past path of curr child : " << child.past << endl;

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

bool Level::isSolved(State state)
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

// todo:
string Level::aStarSolver() {
	// �ϴ� �ڽ� �ϳ���..
	Point goal = goals[0];

	vector<Node> open;
	deque<Node> close;

	// start node
	Node start(initialState, nullptr, 0);
	start.h = 0;
	open.push_back(start);

	int tmpCount = 0;

	vector<string>actionList = possibleActions(initialState);
	deque<Node>::iterator it_close;
	vector<Node>::iterator it_open;

	while (!open.empty())
	{
		cout << "====ITERATION COUNT " << tmpCount << "======" << endl;
		//// open에서 가장 작은 비용 노드를 가져온 것이 curr가 됨..
		auto it = min_element(open.begin(), open.end());
		Node curr = *min_element(open.begin(), open.end());
		open.erase(it);

		if(isSolved(curr.where)) return curr.past;

		if(deadlockTest(curr.where)) continue;
		close.push_back(curr);

		vector<string>actionList = possibleActions(curr.where);
		cout << "current pos : " << curr.where.player.getRow() << ", " << curr.where.player.getCol() << endl;

		for (int i = 0; i < actionList.size(); i++)
		{
			Node child = getChild(curr, actionList[i]);
			cout << "child :" << child.past << endl;
			// �� ��Ͽ� �ִ��� �˻�
			child.move += 1;
			it_close = find(close.begin(), close.end(), child);
			it_open = find(open.begin(), open.end(), child);
			if (it_close == close.end() && it_open == open.end()) {
                child.h = child.getDist(goal); // �޸���ƽ ������
                cout << "child value check " << child.move << " " << child.h << endl;
                open.push_back(child);
            }
			if(it_close != close.end())
            {
                if((*it).move > child.move) (*it) = child;
            }
			//open.push_back(child);
		}

		tmpCount++;
	}
	return "No Solution";
}

bool Level::aStarCompare(const Node& n1, const Node& n2)
{
    return n1 < n2;
}

Node Level::getChild(Node n, string action)
{
	int row = n.where.player.getRow();
	int col = n.where.player.getCol();
	int curMove = n.move;

	Point newPlayer;
	Point newBox;
	vector<Point> boxes = n.where.boxes;

	vector<Point>::iterator it;
	bool hasChild = false;

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
			hasChild = true;
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
			hasChild = true;
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
			hasChild = true;
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
			hasChild = true;
		}
		break;
	}

	State new_state(boxes, newPlayer);
	Node res(new_state, &n, curMove + 1);
	res.past = n.past + action;
	return res;
}

double Level::manhattan(Point c1, Point c2)
{
	return abs(c1.row - c2.row) + abs(c1.col - c2.col);
}

bool Level::deadlockTest(State state) {
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

bool Level::setContains(vector<Point> argset, int row, int col) {
	Point temp(row, col);
	vector<Point>::iterator iter;
	iter = find(argset.begin(), argset.end(), temp);
	if (iter != argset.end())
		return true;
	return false;
}