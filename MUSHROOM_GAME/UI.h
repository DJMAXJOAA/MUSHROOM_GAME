#pragma once
#include <stdio.h>
#include <Windows.h>
#include "enemy.h"

typedef struct UI
{
	Position position;
	int MyHP;
	int MyAtt;
	int EnemyHP;
	int EnemyAtt;
	int timer;
	int second;
}UI;

UI ui;