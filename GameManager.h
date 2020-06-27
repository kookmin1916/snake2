#pragma once

#include <ncurses.h>
#include <cstdlib>
#include <vector>
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
	Snake snake;
	Gate gate[2];
	ITEM ItemList[3];
	
	int Stage;
	int Map[4][MAX][MAX];
	vector<pair<int, int> > wall_list[4];
	
	int OldItemClock;
	int OldGateClock;

public:
	bool MissionCheck();
	void SetGate(int Map[MAX][MAX]);
	void Update(int Map[MAX][MAX]);
	void SetItem(int Map[MAX][MAX]);
	void DrawMap(int Map[MAX][MAX]);
	void DrawBlock(int color);
	void GamePlay();

	GameManager();
	~GameManager();
};
