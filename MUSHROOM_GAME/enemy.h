#include "all_include.h"
#include "map.h"

typedef struct
{
	Position position;
	int hp;
	int att;
	int dead;
	int money;
}EnemyDefault;

EnemyDefault enemy;
EnemyDefault enemy1;
EnemyDefault enemy2;

EnemyDefault* enemy_target = &enemy;