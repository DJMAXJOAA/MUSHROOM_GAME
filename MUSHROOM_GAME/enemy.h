#include <stdio.h>
#include <Windows.h>

typedef struct Position
{
	int x, y;	        //��ǥ ����
}Position;

typedef struct Enemy
{
	Position position;
	int hp;
	int att;
}Enemy;

Enemy enemy;