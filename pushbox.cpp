/*
 * < 구현해야 할 목록 >
 * push 구현하기
 * 스테이지를 완료했을 때 다음 스테이지로 넘어가기
 * 벽이나 상자에 막혔을 때 step수 증가하지 않도록 하기
 * left = l, right = r, up = u, down = d를 string으로 입력받았을 때, 그 방향으로 움직이도록(자동화)
*/
#include <iostream>
#include <ncurses.h>
#include <fstream>
#include <stdlib.h>
#include <string>

using namespace std;

struct Object {
	int xPos;
	int yPos;
	unsigned char zn;
	chtype ozn;
};

#define N 10
struct Object obj[N] = {};

int wbox = 0, lev = 1, step = 0, push = 0;

void levList(int *h, int *w, int *array, int y, int x, int n) {
	// fstream으로 파일 불러오는 것으로 수정
	char cstagenum = '0' + n; //stage num int to char
	char sstagenum[12] = {'s', 't', 'a', 'g', 'e', '/', cstagenum, '.', 't', 'x', 't', '\0'};
	ifstream stage(sstagenum);
    if(stage.fail())
    {
        printf("파일 없음");
    }
    stage >> *h >> *w;
	int map0[*h][*w];
    for (int i = 0; i < *h; i++) {
        for (int j = 0; j < *w; j++) {
            int n;
            stage >> n;
            map0[i][j] = n;
        }
    }
    stage.close();
	*array = map0[y][x];
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

void Level(int n) { // 숫자 - 스테이지 변환
	clear();
	mvprintw(1, 8, "< S O K O B A N > Level: %d", lev);
	mvprintw(2, 1, "Move- Arrow, Restart-R, Exit-Q");
	mvprintw(3, 8, "Step: %d, Push: %d", step, push);
	int x = 0, y = 0, h = 1, w = 1, map;
	wbox = 0;

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
					mvaddch(y + 4, x + 10, '-' | COLOR_PAIR(4));
					obj[9].ozn = mvinch(y + 4, x + 10);
					obj[9].yPos = y + 4;
					obj[9].xPos = x + 10;
					obj[9].zn = 'x';
					mvaddch(obj[9].yPos, obj[9].xPos, obj[9].zn | COLOR_PAIR(3));
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

void Play(int input) {
	bool restart = FALSE;

	chtype up, lf, dw, rg, oup, olf, odw, org;
	up = (mvinch(obj[0].yPos - 1, obj[0].xPos) & A_CHARTEXT);
	lf = (mvinch(obj[0].yPos, obj[0].xPos - 1) & A_CHARTEXT);
	dw = (mvinch(obj[0].yPos + 1, obj[0].xPos) & A_CHARTEXT);
	rg = (mvinch(obj[0].yPos, obj[0].xPos + 1) & A_CHARTEXT);
	oup = (mvinch(obj[0].yPos - 2, obj[0].xPos) & A_CHARTEXT);
	olf = (mvinch(obj[0].yPos, obj[0].xPos - 2) & A_CHARTEXT);
	odw = (mvinch(obj[0].yPos + 2, obj[0].xPos) & A_CHARTEXT);
	org = (mvinch(obj[0].yPos, obj[0].xPos + 2) & A_CHARTEXT);

	for(int o = 0; o <= wbox; o++) { mvaddch(obj[o].yPos, obj[o].xPos, obj[o].ozn);}

	switch(input) { // 방향키 제어 // push 구현
		case KEY_UP:
			step++;
			if (up != 35) {
				if (up == 64 && (oup == 45 || oup == 120)) {
					obj[0].yPos -= 1;
					// 상자와 플레이어가 겹치지 않도록-----------
					for (int o = 1; o <= wbox; o++) {
						if ((obj[0].yPos == obj[o].yPos) && (obj[0].xPos == obj[o].xPos)) obj[o].yPos -= 1;
					}
					//-------------------------------------------
				} else if (up != 64) obj[0].yPos -= 1;
			}
			Step_Push(step, push);
			break;
		case KEY_DOWN:
			step++;
			if (dw != 35) {
				if (dw == 64 && (odw == 45 || odw == 120)) {
					obj[0].yPos += 1;
					for (int o = 1; o <= wbox; o++) {
						if ((obj[0].yPos == obj[o].yPos) && (obj[0].xPos == obj[o].xPos)){
							obj[o].yPos += 1;
						}
					}
				} else if (dw != 64) obj[0].yPos += 1;
			}
			Step_Push(step, push);
			break;
		case KEY_LEFT:
			step++;
			if (lf != 35) {
				if (lf == 64 && (olf == 45 || olf == 120)) {
					obj[0].xPos -= 1;
					for (int o = 1; o <= wbox; o++) {
						if ((obj[0].yPos == obj[o].yPos) &&  (obj[0].xPos == obj[o].xPos)) {
							obj[o].xPos -= 1;
						}
					}
				} else if (lf != 64) obj[0].xPos -= 1;
			}
			Step_Push(step, push);
			break;

		case KEY_RIGHT:
			step++;
			if (rg != 35) {
				if (rg == 64 && (org == 45 || org == 120)) {
					obj[0].xPos += 1;
					for (int o = 1; o <= wbox; o++) {
							if ((obj[0].yPos == obj[o].yPos) && (obj[0].xPos == obj[o].xPos)) {
								obj[o].xPos += 1;
							}
					}
				} else if (rg != 64) obj[0].xPos += 1;
			}
			Step_Push(step, push);
			break;

		case 'r':
		case 'R':
			restart = TRUE;
			step = 0; push = 0;
			Level(lev);
			break;
		default:
			break;
	}
	if (!restart) {
		for (int o = 0; o <= wbox; o++) {
			obj[o].ozn = mvinch(obj[o].yPos, obj[o].xPos);
			mvaddch(obj[o].yPos, obj[o].xPos, obj[o].zn | ((o == 0) ? COLOR_PAIR(2) : COLOR_PAIR(5)));
		}
		move(obj[0].yPos, obj[0].xPos);
	} else restart = FALSE;


}
/*	// 상자의 위치와 목적지의 위치가 모두 일치하는 경우 다음 레벨로 넘어감
int same = 1;
for (int o = 1; o <= wbox; o++) {
if ((obj[1].yPos == obj[o].yPos) && (obj[1].xPos == obj[o].xPos)) {
same++;
}// lev += 1; Level(lev);
}*/


int main() {
	int ch;
	initscr();
	keypad(stdscr, TRUE);

	if (!has_colors()) {
		endwin();
		printf("Error initializing colors.n");
		exit(1);
	}

	start_color();

	pallete();

	Level(lev);

	while ((ch = getch()) != 'q') {
		Play(ch);
	}
	endwin();

	return 0;
}
