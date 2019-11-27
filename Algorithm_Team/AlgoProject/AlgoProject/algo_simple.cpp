// source from https://rosettacode.org/wiki/Sokoban#Set-based_Version
// works with c++11

// levels are stored as a character array where
//		space is an empty square
//		# is a wall
//		@ is the player
//		$ is a box
//		. is a goal
//		+ is the player on a goal
//		* is a box on a goal

// In solution, lower cases are move, upper cases are push

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <regex> // 정규표현식 라이브러리
#include <tuple>
#include <set>
#include <array>

using namespace std;

class Board
{
public :
	vector<vector<char>> sData, dData;
	int px, py; // position of player
	
	Board(string b)
	{
		regex pattern("([^\\n]+)\\n?");
		sregex_iterator end, iter(b.begin(), b.end(), pattern); // 들어온 인풋스트링 b에서 pattern찾기

		int w = 0;
		vector<string> data;
		for (; iter != end; ++iter)
		{
			data.push_back((*iter)[1]);
			w = max(w, (*iter)[1].length());
		}

		for (int v = 0; v < data.size(); ++v)
		{
			vector<char> sTemp, dTemp;
			for (int u = 0; u < w; ++u)
			{
				if (u > data[v].size())
				{
					sTemp.push_back(' ');
					dTemp.push_back(' ');
				}
				else
				{
					char s = ' ', d = ' ', c = data[v][u];

					if (c == '#')
						s = '#';
					else if (c == '.' || c == '*' || c == '+')
						s = '.';

					if (c == '@' || c == '+')
					{
						d = '@';
						px = u;
						py = v;
					}
					else if (c == '$' || c == '*')
						d = '*';

					sTemp.push_back(s);
					dTemp.push_back(d);
				}
			}
			sData.push_back(sTemp);
			dData.push_back(dTemp);
		}
	}

	bool move(int x, int y, int dx, int dy, vector<vector<char>>& data)
	{
		if (sData[y + dy][x + dx] == '#' || data[y + dy][x + dx] == ' ')
			return false;

		data[y][x] = ' ';
		data[y + dy][x + dx] = '@';
		return true;
	}

	bool push(int x, int y, int dx, int dy, vector<vector<char>>& data)
	{
		if (sData[y + 2 + dy][x + 2 + dx] == '#' || sData[y + 2 + dy][x + 2 + dx] == ' ')
			return false;

		data[x][y] = ' ';
		data[y + dy][x + dx] = '@';
		data[y + 2 + dy][x + 2 + dx] = '*';

		return true;
	}

	bool isSolved(const vector<vector<char>>& data)
	{
		for (int v = 0; v < data.size(); v++)
			for (int u = 0; u < data[v].size(); u++)
				if ((sData[v][u] == '.') ^ (data[v][u] == '*'))
					return false;
		return true;
	}

	// using bfs
	string solve()
	{
		set <vector<vector<char>>> visited;
		queue<tuple<vector<vector<char>>, string, int, int>> open;

		open.push(make_tuple(dData, "", px, py));
		visited.insert(dData);

		array<tuple<int, int, char, char>, 4> dirs;
		dirs[0] = make_tuple( 0, -1, 'u', 'U');
		dirs[1] = make_tuple( 1,  0, 'r', 'R');
		dirs[2] = make_tuple( 0,  1, 'd', 'D');
		dirs[3] = make_tuple(-1,  0, 'l', 'L');

		while (open.size() > 0)
		{
			// get front element of queue for bfs
			vector<vector<char>> tmp, cur = get<0>(open.front());
			string cSol = get<1>(open.front());
			int x = get<2>(open.front());
			int y = get<3>(open.front());
			open.pop();

			for (int i = 0; i < 4; i++)
			{
				tmp = cur;
				int dx = get<0>(dirs[i]);
				int dy = get<1>(dirs[i]);

				if (tmp[y + dy][x + dx] == '*') // * is a box on a goal
				{
					if (push(x, y, dx, dy, tmp) && (visited.find(tmp) == visited.end())) // 푸쉬에 성공했고, tmp가 방문하지 않은 경우
					{
						if (isSolved(tmp))
							return cSol + get<3>(dirs[i]);
						open.push(make_tuple(tmp, cSol + get<3>(dirs[i]), x + dx, y + dy));
						visited.insert(tmp);
					}
				}
				else if (move(x, y, dx, dy, tmp) && (visited.find(tmp) == visited.end()))
				{
					if (isSolved(tmp))
						return cSol + get<2>(dirs[i]);
					open.push(make_tuple(tmp, cSol + get<2>(dirs[i]), x + dx, y + dy));
					visited.insert(tmp);
				}
			}
		}
		return "No solution";
	}
};