#include "Heuristics.h"


Heuristics::Heuristics(set<Coordinate> *goals, char hChoice) {
	this->goals = goals;
	this->hChoice = hChoice;
	this->cost = new double[3][3];
	h = new HungarianAlgorithm(9);			// ���� cost.size() ���µ�.. �ִ� 3x3 = 9 �ϱ� 9�� �൵ ������ ������..? �� ��
}


// ����ź �Ÿ� ��� ����
int Heuristics::manhattan(Coordinate *c1, Coordinate *c2) {
	return abs(c1->row - c2->row) + abs(c1->col - c2->col);
}


// ��Ŭ����� �Ÿ� ��� ����
double Heuristics::euclidean(Coordinate *c1, Coordinate *c2) {
	return sqrt((double)((c1->row - c2->row) * (c1->row - c2->row) + (c1->col - c2->col) * (c1->col - c2->col)));
}




double Heuristics::calculate(State *s, string method) {
	set<Coordinate>* boxes = s->boxes;			// ���ڷ� ���� state ���� ���� �ڽ����� �޾ƿ�.
	Coordinate* player = s->player;					// ���ڷ� ���� state ���� ���� �÷��̾ �޾ƿ�.

	double sum = 0;

	// �÷��̾�� �� �ڽ����� �Ÿ��� ��, ���� ���� �Ÿ��� �����ͼ� sum �� ����.
	double playerMin = getDist(player, boxes, method);
	sum += playerMin;

	// �� �ڽ� ����, �ڽŰ� ���� ����� Goal ���� �Ÿ��� sum �� ����.
	set<Coordinate>::iterator it;
	for (it = boxes->begin(); it != boxes->end(); it++) {
		double boxMin = getDist(*it, goals, method);
		sum += boxMin;
	}

	return sum;
}



double Heuristics::getDist(const Coordinate *obj, set<Coordinate> *sets, string method) {
	double minDist = 1000000;

	set<Coordinate>::iterator it;
	for (it = sets->begin(); it != sets->end(); it++) {
		double dist;
		//  ����ź �������� �Ÿ��� ���Ѵٸ�...
		if (method == "m")
			dist = manhattan(obj, it);
		// �ƴ� ��쿣 ��Ŭ����� �������� ����.
		else
			dist = euclidean(obj, it);
		
		if (dist < minDist)
			minDist = dist;
	}

	return minDist;
}



double Heuristics::getHeuristic(State *state) {

	if (hChoice == 'm')
		return calculate(state, "m");
	if (hChoice == 'e')
		return calculate(state, "e");

	int i = 0;
	set<Coordinate>::iterator it;
	for (it = state->boxes->begin(); it != state->boxes->end(); it++) {
		int j = 0;
		double playerCost = manhattan(state->player, it);
		for (auto goal : goals) {
			cost[i][j] = manhattan(it, goal);
			cost[i][j] += playerCost;
			j++;
		}
		i++;
	}

	// HungarianAlgorithm Ŭ�������� excute �Լ� ����...
	vector<int> result = h.execute(cost);
	double max_ = 0;
	for (int k = 0; k < goals.size(); k++) {
		int goalCol = result[k];
		if (goalCol > -1)
			max_ += cost[k][goalCol];
	}
	if (hChoice == 'h')
		return max_;

	return max(max(calculate(state, "m"), calculate(state, "e")), max_);
}
