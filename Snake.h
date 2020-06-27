#pragma once

#include "Mecro.h"
#include "Gate.hpp"
#include <ncurses.h>

enum DIRECTION
{
	LEFT,
	RIGHT,
	UP,
	DOWN
};

struct Node
{
	int x;
	int y;
	int LastX;
	int LastY;
	Node* Next;
};

class Snake
{
private:
	Node* Head;
	DIRECTION Direction, last_direction;
	int OldClock;
	int Level;
	int GrowthCount;
	int PoisonCount;
	int GateCount;
	bool MoveTic;

public:
	bool TailCheck(int x, int y);
	void GateCheck(int Map[][MAX],Gate gate[2]);
	bool Poison();
	void Growth();
	bool ItemCheck(int Map[MAX][MAX]);
	bool CheckNode(int x, int y);
	void Input();
	void DeleteMap(int Map[][MAX]);
	void DeleteSnake(Node* Node);
	void SetSnake(int x, int y);
	int Update(int Map[][MAX],Gate gate[2]);
	void UpdateMap(int Map[][MAX]);
	bool Move(int Map[][MAX], Gate gate[2]);
	void MoveTail(Node* Node);
	DIRECTION NextDirection(DIRECTION direction, int count);

	int GetLevel() { return Level; }
	int GetGrowth() { return GrowthCount; }
	int GetPosion() { return PoisonCount; }
	int GetGate() { return GateCount; }

	Snake();
	~Snake();
};

