#include "Search.h"

string Search::bfs(Problem& p) {

	int totalNode = 1;
	int redundant = 0;

	Node* node = new Node(p.initialState, nullptr, 0, ""); //node with state=problem.INITIAL-STATE, PATH-COST = 0

	if (p.goalTest(*node->state)) //if problem.GOAL-TEST(node.state) then return SOLUTION(node)

		return getSolution(BFS, node, totalNode, 0, 0, 0);



	set<State>* explored = new set<State>(); //empty set

	deque<Node>* fringe = new deque<Node>();

	fringe->push_back(*node);

	vector<string>* actions;

	Node* child;

	while (!fringe->empty()) {

		// 첫번째 원소 가져오기
		node = &fringe->front();
		fringe->pop_front();

		//System.out.println("Player at ("+n.state.player.row+","+n.state.player.col+")");

		explored->insert(*node->state); //add node.STATE to explored

		actions = p.actions(*node->state); //get actions

		for (int i = 0; i < actions->size(); i++) { //for each action in problem.ACTIONS(node.STATE) do

			child = getChild(p, node, actions->at(i), false); //child <- CHILD-NODE(problem,node,action)

			if (child != nullptr && child->state != nullptr) {

				totalNode++;

				//if child.STATE is not in explored or fringe, then
				//child.state 가 explored 에 없고
				explored->find(*child->state) == explored->end();
				//fringe 에 child 도 없으면..
				deque<Node>::iterator fringeIter = find(fringe->begin(), fringe->end(), child);
				if ((explored->find(*child->state) == explored->end()) && (fringeIter == fringe->end())) {
					string solution = getSolution(BFS, child, totalNode, redundant, fringe->size(), explored->size());

					if (p.goalTest(*child->state))
						return solution;

					if (!p.deadlockTest(*child->state)) // check deadlock state
						fringe->push_back(*child);
				}
				else
					redundant++;

			}
		}
	}

	return getSolution(BFS, nullptr, totalNode, redundant, fringe->size(), explored->size());
}

string Search::getSolution(string method, Node* n, int totalNode, int redundant, int fringeSize, int exploredSize) {

	string result = "";

	int steps = 0;

	if (n == nullptr)
		result = "Failed to solve the puzzle";

	else
		while (n->parent != nullptr) {
			result = n->move + " " + result;
			n = n->parent;
			steps++;

		}

	result = "Using " + method + ":\n" + result + "\n(total of " + to_string(steps) + " steps)" +

		"\na) Number of nodes generated: " + to_string(totalNode) +

		"\nb) Number of nodes containing states that were generated previously: " + to_string(redundant) +

		"\nc) Number of nodes on the fringe when termination occurs: " + to_string(fringeSize) +

		"\nd) Number of nodes on the explored list (if there is one) when termination occurs: " + to_string(exploredSize);

	return result;

}


Node* Search::getChild(Problem& p, Node* n, string action, bool isUcs)
{
	set<Coordinate> boxes(n->state->boxes->begin(), n->state->boxes->end());
	int row = n->state->player->row;
	int col = n->state->player->col;
	int newCost = n->cost + 1;
	Coordinate* newPlayer = n->state->player;
	char choice = action[0];

	set<Coordinate>::iterator it;
	switch (choice) {
	case 'u': // action : up
	   // update player coordinate
		newPlayer = new Coordinate(row - 1, col);
		// check if player is pushing a box
		it = find(boxes.begin(), boxes.end(), newPlayer);
		if (it != boxes.end())
		{
			Coordinate* newBox = new Coordinate(row - 2, col);
			boxes.erase(*newPlayer);
			boxes.insert(*newBox);
			if (isUcs)
				newCost++;
		}
		break;
	case 'd': // action : down
	   //update player coordinate
		newPlayer = new Coordinate(row + 1, col);
		//check if player is pushing a box
		it = find(boxes.begin(), boxes.end(), newPlayer);
		if (it != boxes.end()) {
			Coordinate* newBox = new Coordinate(row + 2, col);
			//update box coordinate
			boxes.erase(*newPlayer);
			boxes.insert(*newBox);
			if (isUcs)
				newCost++;
		}
		break;
	case 'l': // action : left
	   // update player coordinate
		newPlayer = new Coordinate(row, col - 1);
		//check if player is pushing a box
		it = find(boxes.begin(), boxes.end(), newPlayer);
		if (it != boxes.end()) {
			Coordinate* newBox = new Coordinate(row, col - 2);
			//update box coordinate
			boxes.erase(*newPlayer);
			boxes.insert(*newBox);
			if (isUcs)
				newCost++;
		}
		break;
	case 'r': // action : right
	   //update player coordinate
		newPlayer = new Coordinate(row, col + 1);
		//check if player is pushing a box
		it = find(boxes.begin(), boxes.end(), newPlayer);
		if (it != boxes.end()) {
			Coordinate* newBox = new Coordinate(row, col + 2);
			//update box coordinate
			boxes.erase(*newPlayer);
			boxes.insert(*newBox);
			if (isUcs)
				newCost++;
		}
		break;
	}
	return new Node(new State(boxes, *newPlayer), n, newCost, to_string(choice));
} // end getChild