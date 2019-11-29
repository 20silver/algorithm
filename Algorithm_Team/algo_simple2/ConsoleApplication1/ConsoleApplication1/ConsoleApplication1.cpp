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
	Coordinate player(-1, -1);
	Coordinate tmp(-1, -1);

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
				if (c == 1) //walls
				{
					tmp.setRow(i);
					tmp.setCol(j);
					walls.insert(tmp);
				}
				else if (c == 2) //box
				{
					tmp.setRow(i);
					tmp.setCol(j);
					boxes.insert(tmp);
				}
				else if (c == 3)
				{
					tmp.setRow(i);
					tmp.setCol(j);
					goals.insert(tmp);
				}
				else if (c == 5) // player
				{
					player.setCol(j);
					player.setRow(i);
					cout << i << endl;
				}
			}
		}
	}
	// create problem
	cout << "before : " << boxes.size() << player.col << endl;
	State init_state(boxes, player);

	cout << "init_state |  player pos : " << init_state.player.getCol() << " boxes size : " << init_state.boxes.size() <<
		" goals size : " << goals.size() << " walls size: " << walls.size() <<endl;

	Problem p(init_state, walls, goals);
	string res = p.bfsSolver();
	cout << "result : " << res << endl;
	
	
	
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
