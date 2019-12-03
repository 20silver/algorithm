#include <iostream>
#include <ncurses.h>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <unistd.h>

// 알고리즘 부분 
#include <vector>
#include "Point.h"
#include "State.h"
#include "Level.h"
#include "Node.h"

using namespace std;

struct Object {
	int xPos;
	int yPos;
	unsigned char zn;
	chtype ozn;
};

#define N 30
struct Object obj[N] = {};

int wbox = 0, lev = 5, step = 0, push = 0, goal = 19;
bool hasmap = false;
int mapdata[10][10];

void levList(int *h, int *w, int *array, int y, int x, int n) {
	if (!hasmap){
		char cstagenum = '0' + n; //stage num int to char
		char sstagenum[12] = {'s', 't', 'a', 'g', 'e', '/', cstagenum, '.', 't', 'x', 't', '\0'};
		ifstream stage(sstagenum);
		if(stage.fail())
		{
			printf("파일 없음");
		}
		stage >> *h >> *w;
		for (int i = 0; i < *h; i++) {
			for (int j = 0; j < *w; j++) {
				int n;
				stage >> n;
				mapdata[i][j] = n;
			}
		}
		stage.close();
	}
	*array = mapdata[y][x];
}

void pallete() { // 색 지정
	init_color(COLOR_BLACK, 0, 0, 0);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_CYAN, COLOR_BLACK);
	init_pair(6, COLOR_WHITE, COLOR_BLACK);
}

void Level_UI(int n) { // 숫자 - 스테이지 변환
	clear();

	vector<Point> walls, goals, boxes;
	Point player;
	Point tmp;

	mvprintw(1, 8, "< S O K O B A N > Level: %d", lev);
	mvprintw(2, 1, "Move- Arrow, Restart-R, Exit-Q, Auto Mode-A");
	mvprintw(3, 8, "Step: %d, Push: %d", step, push);
	int x = 0, y = 0, h = 1, w = 1, map;
	wbox = 0; goal = 19;

	for (y = 0; y < h; y++) {
		for (x = 0; x < w; x++) {
			levList(&h, &w, &map, y, x, n);
			switch(map) {
				case 0: mvaddch(y + 4, x + 10, '-' | COLOR_PAIR(4)); break; // 벽 내부
				case 1: mvaddch(y + 4, x + 10, '#' | COLOR_PAIR(1)); break; // 벽
				case 2: // 상자
					mvaddch(y + 4, x + 10, '-' | COLOR_PAIR(4));
					wbox += 1;
					obj[wbox].ozn = mvinch(y + 4, x + 10);
					obj[wbox].yPos = y + 4;
					obj[wbox].xPos = x + 10;
					obj[wbox].zn = '@';
					mvaddch(obj[wbox].yPos, obj[wbox].xPos, obj[wbox].zn | COLOR_PAIR(5));
					break;
				case 3: //목적지
					goal += 1;
					mvaddch(y + 4, x + 10, '-' | COLOR_PAIR(4));
					obj[goal].ozn = mvinch(y + 4, x + 10);
					obj[goal].yPos = y + 4;
					obj[goal].xPos = x + 10;
					obj[goal].zn = 'x';
					mvaddch(obj[goal].yPos, obj[goal].xPos, obj[goal].zn | COLOR_PAIR(3));
					break;
				case 4: mvaddch(y + 4, x + 10, '+' | COLOR_PAIR(6)); break; // 벽 외부
				case 5: // 플레이어
					mvaddch(y + 4, x + 10, '-' | COLOR_PAIR(4));
					obj[0].ozn = mvinch(y + 4, x + 10);
					obj[0].yPos = y + 4;
					obj[0].xPos = x + 10;
					obj[0].zn = 'P';
					mvaddch(obj[0].yPos, obj[0].xPos, obj[0].zn | COLOR_PAIR(2));
					break;
			}
		}
	}

	move(obj[0].yPos, obj[0].xPos);
}

void Step_Push(int step, int push) {
	mvprintw(3, 8, "Step: %d, Push: %d", step, push);
}

void stageClear() {
	clear();
	mvprintw(1, 3, "$$$$$$$$$$  $$            $$$$$$$$$     $$$$$      $$$$$$$ ");
	mvprintw(2, 3, "$$          $$            $$           $$    $$    $$     $$");
	mvprintw(3, 3, "$$          $$            $$          $$      $$   $$      $$ ");
	mvprintw(4, 3, "$$          $$            $$          $$      $$   $$    $$ ");
	mvprintw(5, 3, "$$          $$            $$$$$$$$$   $$$$$$$$$$   $$$$$$$ ");
	mvprintw(6, 3, "$$          $$            $$          $$      $$   $$    $$ ");
	mvprintw(7, 3, "$$          $$            $$          $$      $$   $$     $$ ");
	mvprintw(8, 3, "$$          $$            $$          $$      $$   $$      $$ ");
	mvprintw(9, 3, "$$$$$$$$$$  $$$$$$$$$$$$  $$$$$$$$$   $$      $$   $$       $$");
	mvprintw(10, 3, "Please Press 'q' to exit!");
}

void nextStage() {
	bool flag;
	for (int o = 1; o<=wbox; o++){
		flag = false;
		for (int goal = 19; goal<=19+wbox; goal++){
			if ((obj[o].yPos == obj[goal].yPos) && (obj[o].xPos == obj[goal].xPos)){
				flag = true;
				break;
			}
		}
		if (!flag){
			return;
		}
	}
	step = 0; push = 0; lev += 1;
	if (lev == 6) {
	 	stageClear();
		return;
	}
	Level_UI(lev);
}

void Play(int input) {
	if (lev == 6){
		return;
	}
	bool restart = FALSE;
	int ymove = 0, xmove = 0;
	chtype up, lf, dw, rg, oup, olf, odw, org, way = 35, wayobj;
	up = (mvinch(obj[0].yPos - 1, obj[0].xPos) & A_CHARTEXT);
	lf = (mvinch(obj[0].yPos, obj[0].xPos - 1) & A_CHARTEXT);
	dw = (mvinch(obj[0].yPos + 1, obj[0].xPos) & A_CHARTEXT);
	rg = (mvinch(obj[0].yPos, obj[0].xPos + 1) & A_CHARTEXT);
	oup = (mvinch(obj[0].yPos - 2, obj[0].xPos) & A_CHARTEXT);
	olf = (mvinch(obj[0].yPos, obj[0].xPos - 2) & A_CHARTEXT);
	odw = (mvinch(obj[0].yPos + 2, obj[0].xPos) & A_CHARTEXT);
	org = (mvinch(obj[0].yPos, obj[0].xPos + 2) & A_CHARTEXT);

	for(int o = 0; o <= wbox; o++) { mvaddch(obj[o].yPos, obj[o].xPos, obj[o].ozn);}

	switch(input) { // 방향키 제어
		case 't':
		case 'T':
		case KEY_UP:
			ymove = -1;
			way = up;
			wayobj = oup;
			break;
		case 'c':
		case 'C':
		case KEY_DOWN:
			ymove = 1;
			way = dw;
			wayobj = odw;
			break;
		case 'k':
		case 'K':
		case KEY_LEFT:
			xmove = -1;
			way = lf;
			wayobj = olf;
			break;
		case 'q':
		case 'Q':
		case KEY_RIGHT:
			xmove = 1;
			way = rg;
			wayobj = org;
			break;
		case 'r':
		case 'R':
			restart = TRUE;
			step = 0; push = 0;
			Level_UI(lev);
			break;
		default:
			break;
	}
	if (way != 35) {
		step++;
		if (way == 64 && (wayobj == 45 || wayobj == 120)) {
			obj[0].xPos += xmove;
			obj[0].yPos += ymove;
			for (int o = 1; o <= wbox; o++) {
				if ((obj[0].yPos == obj[o].yPos) && (obj[0].xPos == obj[o].xPos)) {
					obj[o].xPos += xmove;
					obj[o].yPos += ymove;
					push++;
				}
			}
		} else if (way != 64){
			obj[0].xPos += xmove;
			obj[0].yPos += ymove;
		} else step--;
	}
	Step_Push(step, push);

	if (!restart) {
		for (int o = 0; o <= wbox; o++) {
			obj[o].ozn = mvinch(obj[o].yPos, obj[o].xPos);
			mvaddch(obj[o].yPos, obj[o].xPos, obj[o].zn | ((o == 0) ? COLOR_PAIR(2) : COLOR_PAIR(5)));
		}
		move(obj[0].yPos, obj[0].xPos);
		nextStage();
	} else restart = FALSE;
}



string loadFile(int stage)
{
	ifstream fin;
	switch (stage) {
	case 1:
		fin.open("stage/1.txt");
		break;
	case 2:
		fin.open("stage/2.txt");
		break;
	case 3:
		fin.open("stage/3.txt");
		break;
	case 4:
		fin.open("stage/4.txt");
		break;
	case 5:
		fin.open("stage/5.txt");
		break;
	}

	vector<Point> walls, goals, boxes;
	Point player;
	Point tmp;
	int h, w;
	fin >> h >> w;
//	cout << "height : " << h << " width : " << w << endl;

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			int c; fin >> c;
//			cout << c << " ";
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
	}
	State init_state(boxes, player);
	Level level(init_state, goals, walls);
	string res = level.bfsSolver();

//	cout << "result : " << res << endl;
	return res;
}





int main() {
	int ch;
	initscr();
	keypad(stdscr, TRUE);
	noecho();

	if (!has_colors()) {
		endwin();
		printf("Error initializing colors.n");
		exit(1);
	}

	start_color();

	pallete();

	Level_UI(lev);
	if (getch() != 'a'){
		while ((ch = getch()) != 'q') {
			Play(ch);
		}
	}
	// 여기가 알고리즘 자동으로 실행하는 부분...
	else {
		do{
			mvprintw(3, 25, "solving...");
			refresh();
			string inputstr = loadFile(lev);
			mvprintw(3, 25, "solved!   ");
			// string inputstr = "uUdlUdrrU";
			for (int i = 0; i<inputstr.length(); i++){
				int input = inputstr[i] - 1;
				Play(input);
				usleep(400000);
				refresh();
			}
		}while ((ch = getch()) != 'q');
	}
	
	endwin();

	return 0;
}
