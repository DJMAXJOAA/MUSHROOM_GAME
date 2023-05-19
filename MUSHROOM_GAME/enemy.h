#include <stdio.h>
#include <Windows.h>

typedef struct Position
{
	int x, y;	        //ÁÂÇ¥ ¼³Á¤
}Position;

typedef struct Enemy
{
	Position position;
	int hp;
	int att;
	int dead;
}Enemy;

Enemy enemy;

void EnemyDead();

void EnemyDead()
{

}