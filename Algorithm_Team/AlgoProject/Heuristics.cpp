#include "Heuristics.h"


Heuristics::Heuristics(set<Coordinate> *goals, char hChoice) {
	this->goals = goals;
	this->hChoice = hChoice;
	this->cost = new double[3][3];
	h = new HungarianAlgorithm(9);			// 원래 cost.size() 들어가는데.. 최대 3x3 = 9 니까 9로 줘도 괜찮지 않을까..? ㅎ ㅎ
}


// 맨하탄 거리 계산 공식
int Heuristics::manhattan(Coordinate *c1, Coordinate *c2) {
	return abs(c1->row - c2->row) + abs(c1->col - c2->col);
}


// 유클리디안 거리 계산 공식
double Heuristics::euclidean(Coordinate *c1, Coordinate *c2) {
	return sqrt((double)((c1->row - c2->row) * (c1->row - c2->row) + (c1->col - c2->col) * (c1->col - c2->col)));
}




double Heuristics::calculate(State *s, string method) {
	set<Coordinate>* boxes = s->boxes;			// 인자로 받은 state 에서 현재 박스들을 받아옴.
	Coordinate* player = s->player;					// 인자로 받은 state 에서 현재 플레이어를 받아옴.

	double sum = 0;

	// 플레이어와 각 박스들의 거리들 중, 제일 작은 거리를 가져와서 sum 에 더함.
	double playerMin = getDist(player, boxes, method);
	sum += playerMin;

	// 각 박스 별로, 자신과 가장 가까운 Goal 과의 거리를 sum 에 더함.
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
		//  맨하탄 공식으로 거리를 구한다면...
		if (method == "m")
			dist = manhattan(obj, it);
		// 아닐 경우엔 유클리디언 공식으로 구함.
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

	// HungarianAlgorithm 클래스에서 excute 함수 실행...
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
