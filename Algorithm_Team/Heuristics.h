#include <iostream>
#include <hash_set>
#include <cmath>
#include <vector>

using namespace std;

class Heuristics {
private:
	hash_set<Coordinate> goals;
	vector<vector<double>> cost(3, vector<double>(3, 0));
	// double cost[3][3];				// �ڽ� �ִ� ������ 3 ���ϱ�... 3x3 ��ķ� ���� ����.
	HungarianAlgorithm h;			// 'e' : ��Ŭ�����, 'm' : ����ź. �� �߿� �ϳ�. �� ���� ���� �Ÿ� ��� ����� �޶���.
	char hChoice;

	// ����ź �Ÿ� ��� ����
	int manhattan(Coordinate c1, Coordinate c2);
	// ��Ŭ����� �Ÿ� ��� ����
	double euclidean(Coordinate c1, Coordinate c2);
	// ���� �� ����� ����ؼ� �Ÿ� ���.
	double getDist(Coordinate obj, hash_set<Coordinate> sets, char method);

public:
	Heuristics(hash_set<Coordinate> goals, char hChoice);

	double calculate(State s, string method);

	double getHeuristic(State state);
};