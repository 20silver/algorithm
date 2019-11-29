#include "Coordinate.h"
#include "State.h"
#include "Problem.h"

#include <iostream>
#include <fstream>
#include <set>


using namespace std;

void loadfile()
{
	ifstream fin;
	fin.open("input.txt");
	int mapCount;
	fin >> mapCount;

	set<Coordinate> walls, goals, boxes;
	Coordinate* player = nullptr;

	for (int idx = 0; idx < mapCount; idx++)
	{
		int h, w;
		fin >> h >> w;
		cout << "height : " << h << " width : " << w << endl;

		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				int c; fin >> c;
				cout << c << " ";
				Coordinate* tmp;
				if (c == 1) //walls
				{
					tmp = new Coordinate(i, j);
					walls.insert(*tmp);
				}
				else if (c == 2) //box
				{
					tmp = new Coordinate(i, j);
					boxes.insert(*tmp);
				}
				else if (c == 3)
				{
					tmp = new Coordinate(i, j);
					goals.insert(*tmp);
				}
				else if (c == 5) // player
				{
					player = new Coordinate(i, j);
					cout << i << endl;
				}
			}
		}
	}
	// create problem
	State init_state(boxes, *player); 
	Problem p(init_state, walls, goals);
	
	
	
	// create problem
//	Problem p(initial_state, &walls, &goals);
//	string res = p.bfsSolver();
//	cout << "result : " << res << endl;

}

int main(int c, char* v[])
{
	loadfile();
	return 0;

}
