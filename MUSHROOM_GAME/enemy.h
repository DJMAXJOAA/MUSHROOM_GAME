#include "all_include.h"
#include "map.h"

typedef struct
{
	Position position;
	double hp;
	double att;
	double dead;
	double money;
}EnemyDefault;

EnemyDefault enemy;
EnemyDefault enemy1;
EnemyDefault enemy2;

EnemyDefault* enemy_target = &enemy;

