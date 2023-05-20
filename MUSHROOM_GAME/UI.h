#pragma once
#include <stdio.h>
#include <Windows.h>
#include "enemy.h"

typedef struct UI
{
	Position position;
	int Money;
	int MyHP;
	int MyAtt;
	int EnemyHP;
	int EnemyAtt;
	int timer;
	float second;
}UI;

UI ui;
UI* p_ui = &ui;