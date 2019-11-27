#include "Coordinate.h"
#include "State.h"

#include <iostream>
#include <fstream>

// levels are stored as a character array where
//		space is an empty square
//		# is a wall
//		@ is the player
//		$ is a box
//		. is a goal
//		+ is the player on a goal
//		* is a box on a goal

// In solution, lower cases are move, upper cases are push


using namespace std;

void loadfile()
{
	cout << "load file" << endl;
	ifstream fin;
	fin.open("input.txt");
	int mapCount;
	fin >> mapCount;

	for (int i = 0; i < mapCount; i++)
	{
		int h, w;
		fin >> h >> w;
		cout << h << " " << w;

		
	}

}

int main()
{
	loadfile();

}
