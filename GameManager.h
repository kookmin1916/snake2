#pragma once

#include <ncurses.h>
#include "Color.hpp"
#include "Mecro.h"
#include "Snake.h"
#include "Gate.hpp"

using namespace std;

struct ITEM
{
	int x;
	int y;
	bool Growth;
};

struct Mission
{
	int MaxLevel;
	bool LevelCheck;
	int MaxGrowth;
	bool GrowthCheck;
	int MaxPoison;
	bool PoisonCheck;
	int MaxGate;
	bool GateCheck;
};

class GameManager
{
private:
	Mission mission[4];
	int Stage;
	Snake snake;
	int Map[MAX][MAX];
	int Map1[MAX][MAX];
	int Map2[MAX][MAX];
	int Map3[MAX][MAX];
	ITEM ItemList[3];
	int OldItemClock;
	int OldGateClock;
	Gate gate[2];

public:
	bool MissionCheck();
	void SetGate(int Map[MAX][MAX]);
	void Update(int Map[MAX][MAX]);
	void SetItem(int Map[MAX][MAX]);
	void MapDraw(int Map[MAX][MAX]);
	void DrawBlock(int color);
	void GamePlay();
	GameManager();
	~GameManager();
};
