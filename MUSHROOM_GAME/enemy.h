#include "all_include.h"
#include "map.h"

typedef struct
{
	Position position;
	double maxhp;
	double hp;
	double att;
	double dead;
	double money;
	char HPbar[10];
	char name[40];
	char info[40];
}EnemyDefault;

EnemyDefault enemy;
EnemyDefault enemy1;
EnemyDefault enemy2;

EnemyDefault* enemy_target;
EnemyDefault* enemy_target_new;
