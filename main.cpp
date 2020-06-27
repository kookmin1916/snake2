#include <cstdlib>
#include <ctime>
#include "GameManager.h"
#include "Color.hpp"

using namespace std;

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