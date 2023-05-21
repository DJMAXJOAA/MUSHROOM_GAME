#pragma once
#include "all_include.h"
#include "enemy.h"

typedef struct UI
{
	Position position;
	int Money;
	double MyHP;
	double MyAtt;
	double EnemyHP;
	double EnemyAtt;
	double second;
	double respawn;
	int critical;
}UI;

UI ui;
UI* p_ui = &ui;