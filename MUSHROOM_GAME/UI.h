#pragma once
#include "all_include.h"
#include "enemy.h"

typedef struct UI
{
	Position position;
	int Money;
	int MyHP;
	int MyAtt;
	int EnemyHP;
	int EnemyAtt;
	double second;
	double respawn;
}UI;

UI ui;
UI* p_ui = &ui;