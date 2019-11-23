#include "SokobanSolver.h"

#include <iostream>
#include <string>

SokobanSolver solver;

using namespace std;

int main(int argc, char const *argv[])
{
    char solverChoice = '';
    char method = '';

    int numPayer = solver.loadFile("input.txt", solverChoice);
    if (numPayer != 1
    {
        cout << "Please have only 1 player in the puzzle" << endl;      
    }
    else
    {
        string answer = solver.solve(method);
        cout << answer << endl;
    }
    
    return 0;
}