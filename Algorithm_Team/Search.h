/* https://github.com/jameshong92/sokoban-solver/blob/master/src/Search.java*/

#include <vector>
#include <set>
#include <list>
#include <string>
#include <deque>

#include "Heuristics.h"
#include "Problem.h"
#include "Node.h"
#include "State.h"

using namespace std;

class Search {
    private :
        string BFS;
        string DFS;
        string UCS;
        string ASTAR;
        string GREEDY;

        Heuristics *h; // 거리계산하는 클래스..

        string getSolution(string method, Node n, int totalNode, int redundant, int fringeSize, int exploredSize);
        Node getChild(Problem p, Node n, string action, bool isUcs);

    public :
        Search(Heuristics h);
        string bfs(Problem p);
        string dfs(Problem p);
        string prioritySearch(Problem p, char choice);
};