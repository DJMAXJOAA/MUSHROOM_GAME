#pragma once
#include "all_include.h"
#include "enemy.h"

typedef struct UI
{
	Position position;
	int Money;
	char Player_Name[10];
	double MyHP;
	double MyMaxHP;
	double MyAtt;
	double EnemyHP;
	double EnemyAtt;
	double second;
	double respawn;
	char Player_HPbar[30];
	char Enemy_HPbar[30];
	int Critical;
	int HitEnemy;
	int Damaged;
	int Notice;
	int temp_money;
	int Danger;
	int CollideEnemy;
}UI;

typedef struct SHOP
{
	int select;

};

UI ui;
UI* p_ui = &ui;

void InitUI();	// ui �ʱ�ȭ

void InitUI()
{
	ui.CollideEnemy = FALSE;
	ui.Critical = 0;
	ui.HitEnemy = FALSE;
	ui.Damaged = FALSE;
	ui.Notice = FALSE;
	ui.Danger = FALSE;
}

void Player_HPbar()
{
	if (ui.MyHP / ui.MyMaxHP  > 0.9) strcpy(ui.Player_HPbar, "�����������");
	else if (ui.MyHP / ui.MyMaxHP > 0.8 && ui.MyHP / ui.MyMaxHP <= 0.9) strcpy(ui.Player_HPbar, "�����������");
	else if (ui.MyHP / ui.MyMaxHP > 0.7 && ui.MyHP / ui.MyMaxHP <= 0.8) strcpy(ui.Player_HPbar, "�����������");
	else if (ui.MyHP / ui.MyMaxHP > 0.6 && ui.MyHP / ui.MyMaxHP <= 0.7) strcpy(ui.Player_HPbar, "�����������");
	else if (ui.MyHP / ui.MyMaxHP > 0.5 && ui.MyHP / ui.MyMaxHP <= 0.6) strcpy(ui.Player_HPbar, "�����������");
	else if (ui.MyHP / ui.MyMaxHP > 0.4 && ui.MyHP / ui.MyMaxHP <= 0.5) strcpy(ui.Player_HPbar, "�����������");
	else if (ui.MyHP / ui.MyMaxHP > 0.3 && ui.MyHP / ui.MyMaxHP <= 0.4) strcpy(ui.Player_HPbar, "�����������");
	else if (ui.MyHP / ui.MyMaxHP > 0.2 && ui.MyHP / ui.MyMaxHP <= 0.3) strcpy(ui.Player_HPbar, "�����������");
	else if (ui.MyHP / ui.MyMaxHP > 0.1 && ui.MyHP / ui.MyMaxHP <= 0.2) strcpy(ui.Player_HPbar, "�����������");
	else if (ui.MyHP / ui.MyMaxHP > 0 && ui.MyHP / ui.MyMaxHP <= 0.1) strcpy(ui.Player_HPbar, "�����������");
	if (ui.MyHP / ui.MyMaxHP <= 0) strcpy(ui.Player_HPbar, "�����������");
}

void Enemy_HPbar()
{
	if (enemy_target->hp / enemy_target->maxhp > 0.9) strcpy(ui.Enemy_HPbar, "�����������");
	else if (enemy_target->hp / enemy_target->maxhp > 0.8 && enemy_target->hp / enemy_target->maxhp <= 0.9) strcpy(ui.Enemy_HPbar, "�����������");
	else if (enemy_target->hp / enemy_target->maxhp > 0.7 && enemy_target->hp / enemy_target->maxhp <= 0.8) strcpy(ui.Enemy_HPbar, "�����������");
	else if (enemy_target->hp / enemy_target->maxhp > 0.6 && enemy_target->hp / enemy_target->maxhp <= 0.7) strcpy(ui.Enemy_HPbar, "�����������");
	else if (enemy_target->hp / enemy_target->maxhp > 0.5 && enemy_target->hp / enemy_target->maxhp <= 0.6) strcpy(ui.Enemy_HPbar, "�����������");
	else if (enemy_target->hp / enemy_target->maxhp > 0.4 && enemy_target->hp / enemy_target->maxhp <= 0.5) strcpy(ui.Enemy_HPbar, "�����������");
	else if (enemy_target->hp / enemy_target->maxhp > 0.3 && enemy_target->hp / enemy_target->maxhp <= 0.4) strcpy(ui.Enemy_HPbar, "�����������");
	else if (enemy_target->hp / enemy_target->maxhp > 0.2 && enemy_target->hp / enemy_target->maxhp <= 0.3) strcpy(ui.Enemy_HPbar, "�����������");
	else if (enemy_target->hp / enemy_target->maxhp > 0.1 && enemy_target->hp / enemy_target->maxhp <= 0.2) strcpy(ui.Enemy_HPbar, "�����������");
	else if (enemy_target->hp / enemy_target->maxhp > 0 && enemy_target->hp / enemy_target->maxhp <= 0.1) strcpy(ui.Enemy_HPbar, "�����������");
	if (enemy_target->hp / enemy_target->maxhp <= 0) strcpy(ui.Enemy_HPbar, "�����������");
}