#pragma once

#include <iostream>
#include <time.h>

using namespace std;

#ifdef __USE_MECRO_COLOR__

#include <Windows.h>
#include <conio.h>

#define col GetStdHandle(STD_OUTPUT_HANDLE) 
#define BLACK SetConsoleTextAttribute( col,0x0000 );
#define DARK_BLUE SetConsoleTextAttribute( col,0x0001 );
#define GREEN SetConsoleTextAttribute( col,0x0002 );
#define BLUE_GREEN SetConsoleTextAttribute( col,0x0003 );
#define BLOOD SetConsoleTextAttribute( col,0x0004 );
#define PUPPLE SetConsoleTextAttribute( col,0x0005 );
#define GOLD SetConsoleTextAttribute( col,0x0006 );
#define ORIGINAL SetConsoleTextAttribute( col,0x0007 );
#define GRAY SetConsoleTextAttribute( col,0x0008 );
#define BLUE SetConsoleTextAttribute( col,0x0009 );
#define HIGH_GREEN SetConsoleTextAttribute( col,0x000a );
#define SKY_BLUE SetConsoleTextAttribute( col,0x000b );
#define RED SetConsoleTextAttribute( col,0x000c );
#define PLUM SetConsoleTextAttribute( col,0x000d );
#define YELLOW SetConsoleTextAttribute( col,0x000e );

#endif

#define MAX 21
#define BLANK 0
#define WALL 1
#define HEAD 2
#define TAIL 3
#define GROWTH 4
#define POISON 5
#define IMMUNE_WALL 6
#define GATE 7
#define SPEED 300
#define CREATE_ITEM_TIME 5000
#define CREATE_GATE_TIME 20000
#define LEFT_KEY 75
#define RIGHT_KEY  77
#define UP_KEY  72
#define DOWN_KEY  80
