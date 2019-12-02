#include <iostream>
#include <fstream>
#include <vector>
#include "Point.h"
#include "State.h"
#include "Level.h"

using namespace std;

void loadFile()
{
	ifstream fin;
	fin.open("input.txt");
	int mapCount;
	fin >> mapCount;

	vector<Point> walls, goals, boxes;
	Point player;
	Point tmp;
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
					walls.push_back(tmp);
				}
				else if (c == 2) //box
				{
					tmp.setRow(i);
					tmp.setCol(j);
					boxes.push_back(tmp);
				}
				else if (c == 3) // goal
				{
					tmp.setRow(i);
					tmp.setCol(j);
					goals.push_back(tmp);
				}
				else if (c == 5) // player
				{
					player.setCol(j);
					player.setRow(i);
				}
			}
			cout << endl;
		}
	}

	State init_state(boxes, player);
	Level level(init_state, goals, walls);
	string res = level.bfsSolver();

	cout << "result : " << res << endl;
}

/*
int main() {
	loadFile();
	return 0;
}
*/