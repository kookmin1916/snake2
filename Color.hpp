#pragma once

#include <ncurses.h>

enum Color {
    WHITE = 1,
    CYAN,
    BLUE,
    RED,
    YELLOW,
    MAGENTA,
    GREEN,
    BLACK,
};

static void InitColor()
{
    initscr();
    start_color();
    
    init_pair(Color::WHITE, COLOR_BLACK, COLOR_WHITE);
    init_pair(Color::CYAN, COLOR_BLACK, COLOR_CYAN);
    init_pair(Color::BLUE, COLOR_BLACK, COLOR_BLUE);
    init_pair(Color::RED, COLOR_BLACK, COLOR_RED);
    init_pair(Color::YELLOW, COLOR_BLACK, COLOR_YELLOW);
    init_pair(Color::MAGENTA, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(Color::GREEN, COLOR_BLACK, COLOR_GREEN);
    init_pair(Color::BLACK, COLOR_WHITE, COLOR_BLACK);

    attron(COLOR_PAIR(Color::WHITE));
    wbkgd(stdscr, COLOR_PAIR(Color::WHITE));
    attroff(COLOR_PAIR(Color::WHITE));
}
