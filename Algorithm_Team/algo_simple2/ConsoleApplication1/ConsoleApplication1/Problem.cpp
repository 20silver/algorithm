#include "Problem.h"



Problem::Problem(State *initialState, set<Coordinate> *walls, set<Coordinate> *goals)
{
	this->initialState = initialState;
	this->walls = walls;
	this->goals = goals;
	this->currState = nullptr;
}
bool Problem::isSolved(State* state)
{
	// state�� box��� ���� Ŭ������ goal���� ���鼭 ��� ��ġ�ϸ� true
	set<Coordinate>::iterator it_goal, it_box;
	for (it_box = state->boxes->begin(); it_box != state->boxes->end(); it_box++)
	{
		it_goal = find(goals->begin(), goals->end(), *it_box);
		if (it_goal == goals->end())
			return false;
	}
	return true;
}

State* Problem::move(Coordinate* new_player)
{
	// move�� ��������.. �˻�
	// new_player��ġ�� wall�� �ִ���? 
	set<Coordinate>::iterator it_wall;
	//it_wall = find(walls->begin(), walls->end(), *new_player); // ? or just new_player
	it_wall = walls->find(*new_player);
	if (it_wall != walls->end())
		return nullptr;

	// new_player ��ġ�� box�� �ִ��� 
	set<Coordinate>::iterator it_box;
	//it_box = find(currState->boxes->begin(), currState->boxes->end(), *new_player);
	it_box = currState->boxes->find(*new_player);
	if (it_box != currState->boxes->end())
		return nullptr;

	// �÷��̾ �̵��� ������Ʈ �����
	State* new_state = new State(*currState->boxes, *new_player);
	return new_state;
}

State* Problem::push(Coordinate* new_player, int dir)
{
    // dir 1 = down, dir 2 = up, dir 3 = left, dir 4 = right
    // is there walls
    Coordinate *target_box;
    Coordinate *next_box;
    set<Coordinate>::iterator it;
    State *new_state = nullptr;
    set<Coordinate> new_boxes;


    switch(dir) {
        case 1:
            target_box = new Coordinate(new_player->row, new_player->col+1);
            next_box = new Coordinate(new_player->row, new_player->col+2);
            it= walls->find(*next_box);
            if(it != walls->end())
                return nullptr;

            // is there a box
            it = currState->boxes->find(*next_box);
            if(it != currState->boxes->end())
                return nullptr;

            // update currState
            it = currState->boxes->begin();
            while(it != currState->boxes->end())
            {
                if(*it == *target_box)
                    new_boxes.insert(*next_box);
                else new_boxes.insert(*it);
                it++;
            }
            new_state = new State(new_boxes, *target_box);
            currState = new_state;
            break;
        case 2:
            target_box = new Coordinate(new_player->row, new_player->col-1);
            next_box = new Coordinate(new_player->row, new_player->col-2);
            it= walls->find(*next_box);
            if(it != walls->end())
                return nullptr;

            // is there a box
            it = currState->boxes->find(*next_box);
            if(it != currState->boxes->end())
                return nullptr;

            // update currState
            it = currState->boxes->begin();
            while(it != currState->boxes->end())
            {
                if(*it == *target_box)
                    new_boxes.insert(*next_box);
                else new_boxes.insert(*it);
                it++;
            }
            new_state = new State(new_boxes, *target_box);
            currState = new_state;
            break;
        case 3 :
            target_box = new Coordinate(new_player->row-1, new_player->col);
            next_box = new Coordinate(new_player->row-2, new_player->col);
            it= walls->find(*next_box);
            if(it != walls->end())
                return nullptr;

            // is there a box
            it = currState->boxes->find(*next_box);
            if(it != currState->boxes->end())
                return nullptr;

            // update currState
            it = currState->boxes->begin();
            while(it != currState->boxes->end())
            {
                if(*it == *target_box)
                    new_boxes.insert(*next_box);
                else new_boxes.insert(*it);
                it++;
            }
            new_state = new State(new_boxes, *target_box);
            currState = new_state;
            break;
        case 4:
            target_box = new Coordinate(new_player->row+1, new_player->col);
            next_box = new Coordinate(new_player->row+2, new_player->col);
            it= walls->find(*next_box);
            if(it != walls->end())
                return nullptr;

            // is there a box
            it = currState->boxes->find(*next_box);
            if(it != currState->boxes->end())
                return nullptr;

            // update currState
            it = currState->boxes->begin();
            while(it != currState->boxes->end())
            {
                if(*it == *target_box)
                    new_boxes.insert(*next_box);
                else new_boxes.insert(*it);
                it++;
            }
            new_state = new State(new_boxes, *target_box);
            currState = new_state;
            break;
    };
    return new_state;

}
string Problem::bfsSolver()
{
    string result = "";
    set<State> visited;
    queue<tuple<State, string>> q;

    q.push(make_tuple(*initialState, ""));
    visited.insert(*initialState);

    tuple<int, int> dirs[] = {
            make_tuple(0, 1),
            make_tuple(0, -1),
            make_tuple(-1, 0),
            make_tuple(1, 0)
    };

    while(!q.empty())
    {
        State cur = get<0>(q.front());
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            Coordinate new_player(cur.player->row +get<0>(dirs[i]), cur.player->col +get<1>(dirs[i]));

            if(cur.boxes->find(new_player) != cur.boxes->end())
            {
                State* tmp = push(&new_player, i+1);
                if(tmp != nullptr && visited.find(*tmp) == visited.end())
                {
                    if(isSolved(tmp))
                        return result + to_string(i);
                    q.push(make_tuple(*tmp, result + to_string(i)));
                    visited.insert(*tmp);
                }
            }
            else
            {
                State* tmp = move(&new_player);
                if(tmp != nullptr && visited.find(*tmp) == visited.end())
                {
                    if(isSolved(tmp))
                        return result + to_string(i);
                    q.push(make_tuple(*tmp, result + to_string(i)));
                    visited.insert(*tmp);
                }
            }
        }
    }

    return "No solution";
}

// set contains? -> for deadlockTest
