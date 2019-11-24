#include "Heuristics.h"


Heuristics::Heuristics(hash_set<Coordinate> goals, char hChoice) {
	this->goals = goals;
	this->hChoice = hChoice;
	this->cost = new double[goals.size()][goals.size()];
	h = new HungarianAlgorithm(cost.size());
}


// 맨하탄 거리 계산 공식
int Heuristics::manhattan(Coordinate c1, Coordinate c2) {
	return abs(c1.row - c2.row) + abs(c1.col - c2.col);
}


// 유클리디안 거리 계산 공식
double Heuristics::euclidean(Coordinate c1, Coordinate c2) {
	return sqrt((double)((c1.row - c2.row) * (c1.row - c2.row) + (c1.col - c2.col) * (c1.col - c2.col)));
}




double Heuristics::calculate(State s, string method) {
	hash_set<Coordinate> boxes = s->boxes;			// 인자로 받은 state 에서 현재 박스들을 받아옴.
	Coordinate player = s->player;					// 인자로 받은 state 에서 현재 플레이어를 받아옴.

	double sum = 0;

	// 플레이어와 각 박스들의 거리들 중, 제일 작은 거리를 가져와서 sum 에 더함.
	double playerMin = getDist(player, boxes, method);
	sum += playerMin;

	// 각 박스 별로, 자신과 가장 가까운 Goal 과의 거리를 sum 에 더함.
	for (Coordinate b : boxes) {
		double boxMin = getDist(b, goals, method);
		sum += boxMin;
	}

	return sum;
}



double Heuristics::getDist(Coordinate obj, hash_set<Coordinate> sets, string method) {
	double minDist = 1000000;

	//For each coordinate in a set, calculate the distance according to given heuristic choice
	for (Coordinate c : sets) {
		double dist;
		//  맨하탄 공식으로 거리를 구한다면...
		if (method == "m")
			dist = manhattan(obj, c);
		// 아닐 경우엔 유클리디언 공식으로 구함.
		else
			dist = euclidean(obj, c);
		
		if (dist < minDist)
			minDist = dist;
	}

	return minDist;
}



double Heuristics::getHeuristic(State state) {

	if (hChoice == 'm')
		return calculate(state, "m");
	if (hChoice == 'e')
		return calculate(state, "e");

	int i = 0;
	for (Coordinate box : state.boxes) {
		int j = 0;
		double playerCost = manhattan(state.player, box);
		for (Coordinate goal : goals) {
			cost[i][j] = manhattan(box, goal);
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
