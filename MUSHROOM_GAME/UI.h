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
	int Critical;
	int HitEnemy;
	int Damaged;
	int Notice;
	int temp_money;
	int Danger;
}UI;

UI ui;
UI* p_ui = &ui;

void InitUI();	// ui �ʱ�ȭ

void InitUI()
{
	ui.Critical = 0;
	ui.HitEnemy = FALSE;
	ui.Damaged = FALSE;
	ui.Notice = FALSE;
	ui.Danger = FALSE;
}