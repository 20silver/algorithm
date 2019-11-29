#include "SokobanSolver.h"

#include <cstdlib>

using namespace std;

int main() {
	cout << "너 실행은 되냐 ㅅㅂ아" << endl;
	SokobanSolver* solver = new SokobanSolver();
	solver->loadFile("input.txt");

	return 0;
}