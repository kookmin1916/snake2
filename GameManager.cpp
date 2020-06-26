#include "GameManager.h"

GameManager::GameManager()
{
	Stage = 1;
	for (int y = 0; y < MAX; y++)
	{
		for (int x = 0; x < MAX; x++)
		{
			if (x == 0 || x == MAX - 1 || y == 0 || y == MAX - 1)
			{
				if ((x == 0 && y == 0) || (x == 0 && y == MAX - 1) || (x == MAX - 1 && y == 0) || (x == MAX - 1 && y == MAX - 1))
					Map[y][x] = IMMUNE_WALL;
				else
					Map[y][x] = WALL;
			}
			else
			{
				if (rand() % 100 == 0)
					Map[y][x] = WALL;
				else
					Map[y][x] = BLANK;
			}
		}
	}

	for (int y = 0; y < MAX; y++)
	{
		for (int x = 0; x < MAX; x++)
		{
			if (x == 0 || x == MAX - 1 || y == 0 || y == MAX - 1)
			{
				if ((x == 0 && y == 0) || (x == 0 && y == MAX - 1) || (x == MAX - 1 && y == 0) || (x == MAX - 1 && y == MAX - 1))
					Map1[y][x] = IMMUNE_WALL;
				else
					Map1[y][x] = WALL;
			}
			else
			{
				if (rand() %70 == 0)
					Map1[y][x] = WALL;
				else
					Map1[y][x] = BLANK;
			}
		}
	}

	for (int y = 0; y < MAX; y++)
	{
		for (int x = 0; x < MAX; x++)
		{
			if (x == 0 || x == MAX - 1 || y == 0 || y == MAX - 1)
			{
				if ((x == 0 && y == 0) || (x == 0 && y == MAX - 1) || (x == MAX - 1 && y == 0) || (x == MAX - 1 && y == MAX - 1))
					Map2[y][x] = IMMUNE_WALL;
				else
					Map2[y][x] = WALL;
			}
			else
			{
				if (rand() % 50 == 0)
					Map2[y][x] = WALL;
				else
					Map2[y][x] = BLANK;
			}
		}
	}

	for (int y = 0; y < MAX; y++)
	{
		for (int x = 0; x < MAX; x++)
		{
			if (x == 0 || x == MAX - 1 || y == 0 || y == MAX - 1)
			{
				if ((x == 0 && y == 0) || (x == 0 && y == MAX - 1) || (x == MAX - 1 && y == 0) || (x == MAX - 1 && y == MAX - 1))
					Map3[y][x] = IMMUNE_WALL;
				else
					Map3[y][x] = WALL;
			}
			else
			{
				if (rand() % 30 == 0)
					Map3[y][x] = WALL;
				else
					Map3[y][x] = BLANK;
			}
		}
	}
	mission[0].MaxLevel = 1;
	mission[0].LevelCheck = false;
	mission[0].MaxGrowth = 1;
	mission[0].GrowthCheck = false;
	mission[0].MaxPoison = 1;
	mission[0].PoisonCheck = false;
	mission[0].MaxGate = 1;
	mission[0].GateCheck = false;

	mission[1].MaxLevel = 16;
	mission[1].LevelCheck = false;
	mission[1].MaxGrowth = 15;
	mission[1].GrowthCheck = false;
	mission[1].MaxPoison = 11;
	mission[1].PoisonCheck = false;
	mission[1].MaxGate = 9;
	mission[1].GateCheck = false;

	mission[2].MaxLevel = 19;
	mission[2].LevelCheck = false;
	mission[2].MaxGrowth = 18;
	mission[2].GrowthCheck = false;
	mission[2].MaxPoison = 14;
	mission[2].PoisonCheck = false;
	mission[2].MaxGate = 12;
	mission[2].GateCheck = false;

	mission[3].MaxLevel = 22;
	mission[3].LevelCheck = false;
	mission[3].MaxGrowth = 21;
	mission[3].GrowthCheck = false;
	mission[3].MaxPoison = 16;
	mission[3].PoisonCheck = false;
	mission[3].MaxGate = 15;
	mission[3].GateCheck = false;

	for (int i = 0; i < 3; i++)
	{
		ItemList[i].x = -1;
		ItemList[i].y = -1;
	}
	for (int i = 0; i < 2; i++)
	{
		gate[i].x = -1;
		gate[i].y = -1;
	}
	OldItemClock = 0;
	OldGateClock = 0;
}

void GameManager::MapDraw(int Map[MAX][MAX])
{
	clear();
	for (int y = 0; y < MAX; y++)
	{
		for (int x = 0; x < MAX; x++)
		{
			int color = 0;
			if (Map[y][x] == BLANK)
				color = Color::WHITE;
			if (Map[y][x] == WALL)
				color = Color::MAGENTA;
			else if (Map[y][x] == HEAD)
				color = Color::YELLOW;
			else if (Map[y][x] == TAIL)
				color = Color::BLUE;
			else if (Map[y][x] == GROWTH)
				color = Color::GREEN;
			else if (Map[y][x] == POISON)
				color = Color::RED;
			else if (Map[y][x] == IMMUNE_WALL)
				color = Color::BLACK;
			else if(Map[y][x] == GATE)
				color = Color::CYAN;

			DrawBlock(color);
		}
		if (y == 0)
			printw("\tScore Board  %d Stage", Stage);
		else if (y == 1)
			printw("\tB : %d/%d",snake.GetLevel(), mission[Stage - 1].MaxLevel);
		else if (y == 2)
			printw("\t+ : %d", snake.GetGrowth());
		else if (y == 3)
			printw("\t- : %d", snake.GetPosion());
		else if (y == 4)
			printw("\tG : %d", snake.GetGate());
		else if (y == 7)
			printw("\t Mission");
		else if (y == 8)
			printw("\tB : %d (%c)", mission[Stage - 1].MaxLevel, mission[Stage - 1].LevelCheck ? 'v' : ' ');
		else if (y == 9)
			printw("\t+ : %d (%c)", mission[Stage - 1].MaxGrowth, mission[Stage - 1].GrowthCheck ? 'v' : ' ');
		else if (y == 10)
			printw("\t- : %d (%c)", mission[Stage - 1].MaxPoison, mission[Stage - 1].PoisonCheck ? 'v' : ' ');
		else if (y == 11)
			printw("\tG : %d (%c)", mission[Stage - 1].MaxGate, mission[Stage - 1].GateCheck ? 'v' : ' ');
		printw("\n");
	}
}

void GameManager::Update(int Map[MAX][MAX])
{
	if (++OldItemClock >= CREATE_ITEM_TIME)
	{
		SetItem(Map);
		OldItemClock = 0;
	}
	if (++OldGateClock >= CREATE_GATE_TIME)
	{
		SetGate(Map);
		OldGateClock = 0;
	}
}

void GameManager::SetGate(int Map[MAX][MAX])
{
	for (int i = 0; i < 2; i++)
	{
		if (gate[i].x != -1 && gate[i].y != -1)
			Map[gate[i].y][gate[i].x] = WALL;
		if (i == 0)
		{
			gate[i].x = rand() % 2 == 2 ? 0 : MAX - 1;
			gate[i].y = rand() % (MAX - 2) + 1;
		}
		else
		{
			gate[i].x = rand() % (MAX - 2) + 1;
			gate[i].y = rand() % 2 == 2 ? 0 : MAX - 1;
		}
		Map[gate[i].y][gate[i].x] = GATE;
	}
}

void GameManager::SetItem(int Map[MAX][MAX])
{
	for (int i = 0; i < 3; i++)
	{
		if (ItemList[i].x != -1 && ItemList[i].y != -1)
			Map[ItemList[i].y][ItemList[i].x] = BLANK;
		ItemList[i].x = rand() % (MAX - 2) + 1;
		ItemList[i].y = rand() % (MAX - 2) + 1;
		if (snake.CheckNode(ItemList[i].x, ItemList[i].x))
		{
			i--;
			continue;
		}
		ItemList[i].Growth = rand() % 2 == 0 ? true : false;
		if (ItemList[i].Growth)
			Map[ItemList[i].y][ItemList[i].x] = GROWTH;
		else
			Map[ItemList[i].y][ItemList[i].x] = POISON;
	}
}


bool GameManager::MissionCheck()
{
	if (mission[Stage - 1].MaxLevel <= snake.GetLevel())
		mission[Stage - 1].LevelCheck = true;
	if (mission[Stage - 1].MaxGrowth <= snake.GetGrowth())
		mission[Stage - 1].GrowthCheck = true;
	if (mission[Stage - 1].MaxPoison <= snake.GetPosion())
		mission[Stage - 1].PoisonCheck = true;
	if (mission[Stage - 1].MaxGate <= snake.GetGate())
		mission[Stage - 1].GateCheck = true;
	if (mission[Stage - 1].GateCheck && mission[Stage - 1].GrowthCheck && mission[Stage - 1].LevelCheck && mission[Stage - 1].PoisonCheck)
		return true;
	return false;
}

void GameManager::DrawBlock(int color)
{
	attron(COLOR_PAIR(color));
	printw("  ");
	attroff(COLOR_PAIR(color));
}

void GameManager::GamePlay()
{
	snake.SetSnake(MAX / 2 - 2, MAX / 2);
	snake.UpdateMap(Map);
	while (true)
	{
		snake.Input();
		bool Check;
		if (Stage == 1)
		{
			Update(Map);
			Check = snake.Update(Map, gate);
		}
		else if (Stage == 2)
		{
			Update(Map1);
			Check = snake.Update(Map1, gate);
		}
		else if (Stage == 3)
		{
			Update(Map2);
			Check = snake.Update(Map2, gate);
		}
		else
		{
			Update(Map3);
			Check = snake.Update(Map3, gate);
		}
		if (Check)
		{
			if (MissionCheck())
			{
				Stage++;
				if (Stage > 4)
					return;
				else
				{
					for (int y = 0; y < MAX; y++)
					{
						for (int x = 0; x < MAX; x++)
						{
							if (Map[y][x] == HEAD || Map[y][x] == TAIL)
								Map[y][x] = BLANK;
						}
					}
					snake.SetSnake(MAX / 2 - 2, MAX / 2);
					snake.UpdateMap(Map);
					OldItemClock = 0;
					OldGateClock = 0;
					Map[gate[0].y][gate[0].x] = WALL;
					Map[gate[1].y][gate[1].x] = WALL;
				}
			}
			if (Stage == 1)
				MapDraw(Map);
			else if (Stage == 2)
				MapDraw(Map1);
			else if (Stage == 3)
				MapDraw(Map2);
			else
				MapDraw(Map3);
		}
		napms(1);
	}
}

GameManager::~GameManager()
{

}