#include "GameManager.h"

GameManager::GameManager()
{
	Stage = 1;
	for (int y = 0; y < MAX; y++)
	{
		for (int x = 0; x < MAX; x++)
		{
			for(int i = 0; i < 4; i++)
			{
				if (x == 0 || x == MAX - 1 || y == 0 || y == MAX - 1) {
					if ((x == 0 && y == 0) || (x == 0 && y == MAX - 1) || (x == MAX - 1 && y == 0) || (x == MAX - 1 && y == MAX - 1))
						Map[i][y][x] = IMMUNE_WALL;
					else
						Map[i][y][x] = WALL;
				}
				else 
					Map[i][y][x] = BLANK;
			}
		}
	}

	for(int i = 0; i < 4; i++)
	{
		for(int x = 10 - 1; x <= 10 + 1; x++)
		{
			Map[i][10 - 4][x] = Map[i][10 + 4][x] = WALL;
			wall_list[i].push_back(make_pair(10 - 4, x));
			wall_list[i].push_back(make_pair(10 + 4, x));
		}
	}

	for(int i = 1; i < 4; i++)
	{
		Map[i][10 - 4][10 - 3] = Map[i][10 - 4][10 + 3] = WALL;
		Map[i][10 + 4][10 - 3] = Map[i][10 + 4][10 + 3] = WALL;
		wall_list[i].push_back(make_pair(10 - 4, 10 - 3));
		wall_list[i].push_back(make_pair(10 + 4, 10 + 3));
		wall_list[i].push_back(make_pair(10 - 4, 10 + 3));
		wall_list[i].push_back(make_pair(10 + 4, 10 - 3));
	}

	for(int i = 2; i < 4; i++)
	{
		Map[i][10 - 1][10 - 5] = Map[i][10 - 1][10 + 5] = WALL;
		Map[i][10 + 1][10 - 5] = Map[i][10 + 1][10 + 5] = WALL;
		wall_list[i].push_back(make_pair(10 - 1, 10 - 5));
		wall_list[i].push_back(make_pair(10 + 1, 10 + 5));
		wall_list[i].push_back(make_pair(10 - 1, 10 + 5));
		wall_list[i].push_back(make_pair(10 + 1, 10 - 5));
	}

	for(int i = 3; i < 4; i++)
	{
		Map[i][10 - 7][10 - 7] = Map[i][10 - 7][10 + 7] = WALL;
		Map[i][10 + 7][10 - 7] = Map[i][10 + 7][10 + 7] = WALL;
		wall_list[i].push_back(make_pair(10 - 7, 10 - 7));
		wall_list[i].push_back(make_pair(10 + 7, 10 + 7));
		wall_list[i].push_back(make_pair(10 - 7, 10 + 7));
		wall_list[i].push_back(make_pair(10 + 7, 10 - 7));
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

void GameManager::DrawMap(int Map[MAX][MAX])
{
	clear();
	for (int y = 0; y < MAX; y++)
	{
		for (int x = 0; x < MAX; x++)
		{
			int color = Color::WHITE;
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
			printw("    Score Board  %d Stage", Stage);
		else if (y == 1)
			printw("    B : %d/%d",snake.GetLevel(), mission[Stage - 1].MaxLevel);
		else if (y == 2)
			printw("    + : %d", snake.GetGrowth());
		else if (y == 3)
			printw("    - : %d", snake.GetPosion());
		else if (y == 4)
			printw("    G : %d", snake.GetGate());
		else if (y == 7)
			printw("     Mission");
		else if (y == 8)
			printw("    B : %d (%c)", mission[Stage - 1].MaxLevel, mission[Stage - 1].LevelCheck ? 'v' : ' ');
		else if (y == 9)
			printw("    + : %d (%c)", mission[Stage - 1].MaxGrowth, mission[Stage - 1].GrowthCheck ? 'v' : ' ');
		else if (y == 10)
			printw("    - : %d (%c)", mission[Stage - 1].MaxPoison, mission[Stage - 1].PoisonCheck ? 'v' : ' ');
		else if (y == 11)
			printw("    G : %d (%c)", mission[Stage - 1].MaxGate, mission[Stage - 1].GateCheck ? 'v' : ' ');
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
	int last_r = -1;
	for (int i = 0; i < 2; i++)
	{
		int last_y = gate[i].y;
		int last_x = gate[i].x;
		
		if(rand() % 3 != 0) {
			do 
			{
				if (rand() % 2 == 0) {
					gate[i].x = rand() % 2 == 2 ? 0 : MAX - 1;
					gate[i].y = rand() % (MAX - 2) + 1;
				}
				else {
					gate[i].x = rand() % (MAX - 2) + 1;
					gate[i].y = rand() % 2 == 2 ? 0 : MAX - 1;
				}
			}
			while(i == 1 && gate[0].y == gate[1].y && gate[0].x == gate[1].x);
		}
		else {
			int r;
			do 
			{
				r = rand() % wall_list[Stage - 1].size();
			}
			while(r == last_r);
			
			gate[i].y = wall_list[Stage - 1][r].first;
			gate[i].x = wall_list[Stage - 1][r].second;
			last_r = r;
		}

		if (last_y != -1 && last_x != -1)
			Map[last_y][last_x] = WALL;
		Map[gate[i].y][gate[i].x] = GATE;
	}
}

void GameManager::SetItem(int Map[MAX][MAX])
{
	for (int i = 0; i < 3; i++)
	{
		if (ItemList[i].x != -1 && ItemList[i].y != -1)
			Map[ItemList[i].y][ItemList[i].x] = BLANK;

		do
		{
			ItemList[i].x = rand() % (MAX - 2) + 1;
			ItemList[i].y = rand() % (MAX - 2) + 1;
		}
		while(snake.CheckNode(ItemList[i].x, ItemList[i].y)
			|| Map[ItemList[i].y][ItemList[i].x] != BLANK);
		
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
	snake.UpdateMap(Map[0]);
	while (true)
	{
		snake.Input();
		int check;
		int (&current_map)[MAX][MAX] = Map[Stage - 1];

		Update(current_map);
		check = snake.Update(current_map, gate);
		if(check == -1)
			break;

		if (check)
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
							if (current_map[y][x] == HEAD || current_map[y][x] == TAIL)
								current_map[y][x] = BLANK;
						}
					}
					snake.SetSnake(MAX / 2 - 2, MAX / 2);
					snake.UpdateMap(current_map);
					OldItemClock = 0;
					OldGateClock = 0;
					current_map[gate[0].y][gate[0].x] = WALL;
					current_map[gate[1].y][gate[1].x] = WALL;
				}
			}
			DrawMap(current_map);
		}
		napms(1);
	}
}

GameManager::~GameManager()
{

}