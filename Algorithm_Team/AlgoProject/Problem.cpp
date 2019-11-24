#include "Problem.h"

Problem::Problem(set<Coordinate> walls, State *initialState, set<Coordinate> goals){
    this->initialState = initialState;
    this->walls = walls;
    this->goals = goals;
}

bool Problem::goalTest(State *state){
	set<int>::iterator iter;
    for(Coordinate box : state->boxes){
		iter = goals.find(box);
        if(iter == goals.end())
            return false;
    }
    return true;
}

bool Problem::deadlockTest(State *state){
    for(Coordinate box : state.boxes){
        int row = box.row;
        int col = box.col;
        if (!setContains(goals, row, col)) {
            if (setContains(walls, row-1, col)&&setContains(walls, row, col-1))
                return true; //top & left
            if (setContains(walls, row-1, col)&&setContains(walls, row, col+1))
                return true; //top & right
            if (setContains(walls, row+1, col)&&setContains(walls, row, col-1))
                return true; //bottom & left
            if (setContains(walls, row+1, col)&&setContains(walls, row, col+1))
                return true; //bottom & right

            if (setContains(walls, row-1, col-1)&&setContains(walls, row-1, col)&&
                    setContains(walls, row-1, col+1)&&setContains(walls, row, col-2)&&
                    setContains(walls, row, col+2)&&(!setContains(goals, row, col-1))&&
                            !setContains(goals, row, col+1))
                return true; //top & sides
            if (setContains(walls, row+1, col-1)&&setContains(walls, row+1, col)&&
                    setContains(walls, row+1, col+1)&&setContains(walls, row, col-2)&&
                    setContains(walls, row, col+2)&&(!setContains(goals, row, col-1))&&
                            (!setContains(goals, row, col+1)))
                return true; //bottom & sides
            if (setContains(walls, row-1, col-1)&&setContains(walls, row, col-1)&&
                    setContains(walls, row+1, col-1)&&setContains(walls, row-2, col)&&
                    setContains(walls, row+2, col)&&(!setContains(goals, row-1, col))&&
                            (!setContains(goals, row+1, col)))
                return true; //left & vertical
            if (setContains(walls, row-1, col+1)&&setContains(walls, row, col+1)&&
                    setContains(walls, row+1, col+1)&&setContains(walls, row-2, col)&&
                    setContains(walls, row+2, col)&&(!setContains(goals, row-1, col))&&
                            (!setContains(goals, row+1, col)))
                return true; //right & top/bottom
        }
    }
    return false; 
}

vector<string> Problem::actions(State *state){
    vector<string> actionList();
    int row = state.player.row;
    int col = state.player.col;
    HashSet<Coordinate> boxes = state->boxes;
	set<int>::iterator iter;
	set<int>::iterator iter1;
	set<int>::iterator iter2;
	set<int>::iterator iter3;

    Coordinate newPlayer(row-1,col);
    Coordinate newBox(row-2, col);
	iter = walls.find(newPlayer)
	if (iter == walls.end()) {
		iter1 = boxes.find(newPlayer);
		iter2 = boxes.find(newBox);
		iter3 = walls.find(newBox);
		if (iter1 != boxes.end() && (iter2 != boxes.end() || iter3 != walls.end())
			;
		else
			actionList.push_back("u");
	}
    newPlayer = new Coordinate(row,col+1);
    newBox = new Coordinate(row, col+2);
	iter = walls.find(newPlayer);
	if (iter == walls.end()) {
		iter1 = boxes.find(newPlayer);
		iter2 = boxes.find(newBox);
		iter3 = walls.find(newBox);
		if (iter1 != boxes.end() && iter2 != boxes.end() || iter3 != walls.end())
			;
		else
			actionList.push_back("r");
	}
    newPlayer = new Coordinate(row+1,col);
    newBox = new Coordinate(row+2, col);
	iter = walls.find(newPlayer);
	if (iter == walls.end()) {
		iter1 = boxes.find(newPlayer);
		iter2 = boxes.find(newBox);
		iter3 = walls.find(newBox);
		if (iter1 != boxes.end() && iter2 != boxes.end() || iter3 != walls.end()))
			;
		else
			actionList.push_back("d");
	}
    newPlayer = new Coordinate(row,col-1);
    newBox = new Coordinate(row, col-2);
	iter = walls.find(newPlayer);
	if (iter == walls.end()) {
		iter1 = boxes.find(newPlayer);
		iter2 = boxes.find(newBox);
		iter3 = walls.find(newBox);
		if (iter1 != boxes.end() && iter2 != boxes.end() || iter3 != walls.end()))
			;
		else
			actionList.push_back("l");
	}
    return actionList;
}

bool Problem::setContains(set<Coordinate> set, int row, int col){
    temp = new Coordinate(row, col)
	set<int>::iterator iter;
	iter = set.find(temp);
    if(iter != set.end())
        return true;
    return false;
}
