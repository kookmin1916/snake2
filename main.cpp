#include "GameManager.h"
#include "Color.hpp"

int main()
{
    initscr();
    cbreak();
    noecho();
    scrollok(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
	srand(time(NULL));
	InitColor();

	GameManager GM;
	GM.GamePlay();
}