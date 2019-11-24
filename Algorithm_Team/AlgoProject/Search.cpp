#include "Search.h"
#include <string>

Search::Search(Heuristics *h)
{
    BFS = "Breadth-Frist Search";
    DFS = "Depth-First Search";
    UCS = "Uniform-Cost Search";
    ASTAR = "A* Search";
    GREEDY = "Greedy Search";

    this->h = h;
}

 /* Implementation for breath-first search using FIFO*/
string Search::bfs(Problem *p) 
{
    // long startTime = 
    int totalNode = 1;
    int redundant = 0;
	void* ptr = nullptr;
	string str = "";
    Node node(p->initialState, (Node *)ptr, 0, str); // //node with state=problem.INITIAL-STATE, PATH-COST = 0
    if(p->goalTest(node.state)) // if problem.GOAL-TEST(node.state) then return SOLUTION(node)
    return getSolution(BFS, &node, totalNode, 0, 0, 0);

    set<State*> explored;
    deque<Node> fringe;
    fringe.push_front(node);
    vector<string> actions;
    Node* child;

    while(!fringe.empty())
    {
        node = fringe.front(); // 맨 앞 노드 가져오기
        fringe.pop_front();
        explored.insert(node.state); // add node.STATE to explored
        actions = p->actions(node.state); // get actions -> ??
        for (int i = 0; i < actions.size(); i++)
        {
            child = getChild(p, &node, actions[i], false);
            if(child != nullptr && child->state != nullptr)
            {
                totalNode ++;
                // if child.STATE is not in explored or fringe, then
                auto it = find(fringe.begin(), fringe.end(), child);
                auto it_s = explored.find(child->state);
                if((it_s == explored.end()) && (it == fringe.end()) /*!explored.contains(child.state)*//* !fringe.contains(child) */) 
                {
                    string solution = getSolution(BFS, child, totalNode, redundant, fringe.size(), explored.size());
                    if(p->goalTest(child->state))
                        return solution;
                    if(!p->deadlockTest(child->state)) // check deadlock state
                        fringe.push_front(*child);
                }
                else redundant ++;
            }
        }
    }
    return getSolution(BFS, nullptr, totalNode, redundant, fringe.size(), explored.size());
} // end bfs

// bfs와 비슷하지만 queue대신 stack 사용 (LIFO)
string Search::dfs(Problem *p)
{
    int totalNode = 1;
    int redundant = 0;
    void* ptr = nullptr;
    string str = "";
    Node node(p->initialState, (Node *)ptr, 0, str);
    if(p->goalTest(node.state))
        return getSolution(DFS, &node, totalNode, 0, 0, 0);
    
    set<State*> explored;
    deque<Node> fringe;
    fringe.push_back(node); 
    while(!fringe.empty())
    {
        node = fringe.back(); // 첫 번째 노드 꺼내기
        fringe.pop_back();
        explored.insert(node.state);
        vector<string> actions = p->actions(node.state); // get actions
        for (int i = 0; i < actions.size(); i++)
        {
            Node* child = getChild(p, &node, actions[i], false);
            if(child != nullptr && child->state != nullptr)
            {
                totalNode++;
                // if child.STATE is not explored or fringe, then
                auto it = find(fringe.begin(), fringe.end(), child);
                auto it_s = explored.find(child->state);
                if((it_s == explored.end()) && (it == fringe.end()))
                {
                    string solution = getSolution(DFS, child, totalNode, redundant, fringe.size(), explored.size());
                    if(p->goalTest(child->state))
                        return solution;
                    if(!p->deadlockTest(child->state))
                        fringe.push_back(*child);
                }
                else redundant ++;
            }
        }
    }
    return getSolution(DFS, nullptr, totalNode, redundant, fringe.size(), explored.size());
} // end dfs

// TODO
// Implementation for uniform-cost search, greedy search, and A* search
// 위 메소드들은 모두 같은 코드를 쓰는데, 우선순위 큐를 sorting하는 코드만 달라진다
string Search::prioritySearch(Problem *p, char choice)
{
    string method = UCS;
    bool isUCS = true;
    int totalNode = 1;
    int redundant = 0;
} // end prioritySearch

// TODO : Comparators

//  최종 결과를 string으로 출력하는 함수
string Search::getSolution(string method, Node* n, int totalNode, int redundant, int fringeSize, int exploredSize)
{
    string result = "";
    int steps = 0;
    if(n == nullptr)
        result = "Failed to solve the puzzle";
    else 
        while(n->parent!= nullptr)
        {
            result = n->move + " " + result;
            n = n->parent;
            steps ++;
        }
    result = "Using " + method + ":\n" + result + "\n(total of " + to_string(steps) + " steps)" +
    "\na) Number of nodes generated: " + to_string(totalNode) +
    "\nb) Number of nodes containing states that were generated previously: " + to_string(redundant) +
    "\nc) Number of nodes on the fringe when termination occurs: " + to_string(fringeSize) +
    "\nd) Number of nodes on the explored list (if there is one) when termination occurs: " + to_string(exploredSize);

    return result;
} // end getSolution

// @return : action을 수행하고 난 후 n의 child, 여기서 action은 (l, r, u, d)
// if isUcs is true, add 1 to newCost whenever box is pushed
Node* Search::getChild(Problem* p, Node* n, string action, bool isUcs)
{
    set<Coordinate> boxes(n->state->boxes->begin(), n->state->boxes->end());
    int row = n->state->player->row;
    int col = n->state->player->col;
    int newCost = n->cost + 1;
    Coordinate *newPlayer = n->state->player;
    char choice = action[0];

    set<Coordinate>::iterator it;
    switch(choice) {
        case 'u' : // action : up
            // update player coordinate
            newPlayer = new Coordinate(row-1, col);
            // check if player is pushing a box
            it = find(boxes.begin(), boxes.end(), newPlayer);
            if(it != boxes.end())
            {
                Coordinate* newBox = new Coordinate(row-2, col);
                boxes.erase(*newPlayer);
                boxes.insert(*newBox);
                if(isUcs)
                    newCost++;
            }
        break;
        case 'd': // action : down
            //update player coordinate
            newPlayer = new Coordinate(row+1, col);
            //check if player is pushing a box
            it = find(boxes.begin(), boxes.end(), newPlayer);
            if (it != boxes.end()) {
                Coordinate* newBox = new Coordinate(row+2, col);
                //update box coordinate
                boxes.erase(*newPlayer);
                boxes.insert(*newBox);
                if (isUcs)
                    newCost++;
            }
        break;
        case 'l' : // action : left
            // update player coordinate
            newPlayer = new Coordinate(row, col-1);
            //check if player is pushing a box
            it = find(boxes.begin(), boxes.end(), newPlayer);
            if (it != boxes.end()) {
                Coordinate* newBox = new Coordinate(row, col-2);
                //update box coordinate
                boxes.erase(*newPlayer);
                boxes.insert(*newBox);
                if (isUcs)
                    newCost++;
            }
        break;
        case 'r': // action : right
            //update player coordinate
            newPlayer = new Coordinate(row, col+1);
            //check if player is pushing a box
            it = find(boxes.begin(), boxes.end(), newPlayer);
            if (it != boxes.end()) {
                Coordinate* newBox = new Coordinate(row, col+2);
                //update box coordinate
                boxes.erase(*newPlayer);
                boxes.insert(*newBox);
                if (isUcs)
                    newCost++;
            }
        break;
    }
    return new Node(new State(boxes, newPlayer), n, newCost, to_string(choice));
} // end getChild