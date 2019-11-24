#include <iostream>
#include <hash_set>
#include <cmath>
#include <vector>

using namespace std;

class Heuristics {
private:
	hash_set<Coordinate> goals;
	vector<vector<double>> cost(3, vector<double>(3, 0));
	// double cost[3][3];				// 박스 최대 개수가 3 개니까... 3x3 행렬로 만들 것임.
	HungarianAlgorithm h;			// 'e' : 유클리디안, 'm' : 맨하탄. 둘 중에 하나. 이 값에 따라 거리 계산 방법이 달라짐.
	char hChoice;

	// 맨하탄 거리 계산 공식
	int manhattan(Coordinate c1, Coordinate c2);
	// 유클리디언 거리 계산 공식
	double euclidean(Coordinate c1, Coordinate c2);
	// 위의 두 방법을 사용해서 거리 계산.
	double getDist(Coordinate obj, hash_set<Coordinate> sets, char method);

public:
	Heuristics(hash_set<Coordinate> goals, char hChoice);

	double calculate(State s, string method);

	double getHeuristic(State state);
};