#include "Problem.h"



Problem::Problem(State *initialState, set<Coordinate> *walls, set<Coordinate> *goals)
{
	this->initialState = initialState;
	this->walls = walls;
	this->goals = goals;
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

bool Problem::move(Coordinate* new_player, Coordinate* new_box)
{
	// move�� ��������.. �˻�
	// new_player��ġ�� wall�� �ִ���? 
	set<Coordinate>::iterator it_wall;
	it_wall = find(walls->begin(), walls->end(), *new_player); // ? or just new_player
	if (it_wall != walls->end())
		return false;

	// new_player ��ġ�� box�� �ִ���?
	set<Coordinate>::iterator it_box;
	it_box = find(currState->boxes->begin(), currState->boxes->end(), *new_player);
	

}

bool push(State* state);

// set contains? -> for deadlockTest
