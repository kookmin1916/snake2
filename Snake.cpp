#include "Snake.h"


Snake::Snake()
{
	Head = NULL;
	Direction = LEFT;
	GrowthCount = 0;
	PoisonCount = 0;
	GateCount = 0;
	MoveTic = false;
}

void Snake::DeleteMap(int Map[][MAX])
{
	Map[Head->y][Head->x] = BLANK;
	Node* temp = Head->Next;
	while (temp != NULL)
	{
		Map[temp->y][temp->x] = BLANK;
		temp = temp->Next;
	}
}

bool Snake::CheckNode(int x, int y)
{

	Node* temp = Head;
	while (temp != NULL)
	{
		if (temp->x == x && temp->y == y)
			return true;
		temp = temp->Next;
	}
	return false;
}

void Snake::GateCheck(int Map[][MAX], Gate gate[2])
{
	for (int i = 0; i < 2; i++)
	{
		if (gate[i].x == Head->x && gate[i].y == Head->y)
		{
			GateCount++;
			DIRECTION current_direction = Direction;
			const int dir[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
			for(int j = 0; j < 4; j++)
			{
				current_direction = NextDirection(current_direction, j);
				int next_y = gate[1 - i].y + dir[current_direction][0];
				int next_x = gate[1 - i].x + dir[current_direction][1];

				if(Map[next_y][next_x] != WALL && Map[next_y][next_x] != IMMUNE_WALL) {
					Head->y = next_y;
					Head->x = next_x;
					break;
				}
			}
			Direction = current_direction;
			break;
		}
	}
}


bool Snake::TailCheck(int x, int y)
{
	Node* temp = Head->Next;
	while (temp != NULL)
	{
		if (temp->x == x && temp->y == y)
			return true;
		temp = temp->Next;
	}
	return false;
}

bool Snake::Poison() 
{
	Node* temp = Head;
	while (temp->Next != NULL)
	{
		if (temp->Next->Next == NULL)
		{
			delete temp->Next;
			temp->Next = NULL;
			Level--;
			if (Level <= 2)
				return false;
			return true;
		}
		temp = temp->Next;
	}
}

void Snake::Growth()
{
	Node* temp = Head;
	while (temp->Next != NULL)
		temp = temp->Next;
	temp->Next = new Node;
	temp->Next->x = temp->LastX;
	temp->Next->y = temp->LastY;
	temp->Next->Next = NULL;
	Level++;
}

bool Snake::ItemCheck(int Map[MAX][MAX])
{
	switch (Map[Head->y][Head->x])
	{
	case GROWTH:
		Growth();
		GrowthCount++;
		break;
	case POISON:
		PoisonCount++;
		return Poison();
	}
	return true;
}

bool Snake::Move(int Map[][MAX], Gate gate[2])
{
	DeleteMap(Map);
	Head->LastX = Head->x;
	Head->LastY = Head->y;
	switch (Direction)
	{
	case LEFT:
		Head->x--;
		break;
	case RIGHT:
		Head->x++;
		break;
	case UP:
		Head->y--;
		break;
	case DOWN:
		Head->y++;
		break;
	}
	last_direction = Direction;
	
	if (TailCheck(Head->x, Head->y))
	{
		DeleteSnake(Head);
		return false;
	}
	GateCheck(Map, gate);
	if (Map[Head->y][Head->x] == WALL)
	{
		DeleteSnake(Head);
		return false;
	}
	MoveTail(Head);
	if(!ItemCheck(Map))
		return false;
	UpdateMap(Map);
	return true;
}

void Snake::MoveTail(Node* Node)
{
	if (Node->Next == NULL)
		return;
	Node->Next->LastX = Node->Next->x;
	Node->Next->LastY = Node->Next->y;
	Node->Next->x = Node->LastX;
	Node->Next->y = Node->LastY;
	MoveTail(Node->Next);
}

void Snake::DeleteSnake(Node* Node)
{
	if (Node == NULL)
		return;
	DeleteSnake(Node->Next);
	delete Node;
}

void Snake::SetSnake(int x, int y)
{
	Direction = LEFT;
	if (Head != NULL)
	{
		DeleteSnake(Head);
		Head = NULL;
	}
	Head = new Node;
	Head->x = x;
	Head->y = y;
	Head->Next = NULL;
	for (int i = 1; i <= 2; i++)
	{
		Node* add = new Node;
		add->x = Head->x + i;
		add->y = Head->y;
		add->Next = NULL;
		Node* temp = Head;
		while (temp->Next != NULL)
			temp = temp->Next;
		temp->Next = add;
	}
	OldClock = 0;
	Level = 3;
	GrowthCount = 0;
	PoisonCount = 0;
	GateCount = 0;
}

int Snake::Update(int Map[][MAX], Gate gate[2])
{
	if(++OldClock >= 500) {
		if(!Move(Map,gate))
			return -1;
		OldClock = 0;
		return 1;
	}
	return 0;
}

void Snake::Input()
{
	int ch = getch();
	
	switch (ch)
	{
	case KEY_LEFT:
		if (last_direction != RIGHT)
			Direction = LEFT;
		break;
	case KEY_RIGHT:
		if (last_direction != LEFT)
			Direction = RIGHT;
		break;
	case KEY_UP:
		if (last_direction != DOWN)
			Direction = UP;
		break;
	case KEY_DOWN:
		if (last_direction != UP)
			Direction = DOWN;
		break;
	}
}

void Snake::UpdateMap(int Map[][MAX])
{
	Map[Head->y][Head->x] = HEAD;
	Node* temp = Head->Next;
	while (temp != NULL)
	{
		Map[temp->y][temp->x] = TAIL;
		temp = temp->Next;
	}
}

Snake::~Snake()
{
	if (Head != NULL)
	{
		DeleteSnake(Head);
		Head = NULL;
	}
}

DIRECTION Snake::NextDirection(DIRECTION direction, int count) 
{
	const static DIRECTION next[4] = {RIGHT, UP, LEFT, DOWN};
	const static int dir_to_idx[4] = {2, 0, 1, 3};
	
	if(count == 0)
		return direction;
	if(count == 1)
		return next[(dir_to_idx[direction] + 3) % 4];
	if(count == 2)
		return next[(dir_to_idx[direction] + 1) % 4];
	return next[(dir_to_idx[direction] + 2) % 4];
}
