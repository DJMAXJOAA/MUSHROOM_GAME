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
	double respawn;
	char Player_HPbar[30];
	char Enemy_HPbar[30];
	int state;	// 장비창, 인벤창, 아이템사용창
}UI;

typedef struct Notice
{
	int Critical;
	int HitEnemy;
	int Damaged;
	int GetMoney;
	int temp_money;
	int Danger;
	int CollideEnemy;
}Notice;



UI ui;
UI* p_ui = &ui;
Notice notice;
Inventory inventory[10];

void InitNotice();	// ui 알림창 초기화
void Player_HPbar(); // 플레이어 체력바
void Enemy_HPbar(); // 몬스터 체력바
void ShopSelect();	// 상점 선택

void InitNotice()
{
	notice.Critical = 0;
	notice.HitEnemy = FALSE;
	notice.Damaged = FALSE;
	notice.GetMoney = FALSE;
	notice.Danger = FALSE;
	notice.CollideEnemy = FALSE;
}


void Player_HPbar()
{
	if (ui.MyHP / ui.MyMaxHP  > 0.9) strcpy(ui.Player_HPbar, "■■■■■■■■■■");
	else if (ui.MyHP / ui.MyMaxHP > 0.8 && ui.MyHP / ui.MyMaxHP <= 0.9) strcpy(ui.Player_HPbar, "■■■■■■■■■□");
	else if (ui.MyHP / ui.MyMaxHP > 0.7 && ui.MyHP / ui.MyMaxHP <= 0.8) strcpy(ui.Player_HPbar, "■■■■■■■■□□");
	else if (ui.MyHP / ui.MyMaxHP > 0.6 && ui.MyHP / ui.MyMaxHP <= 0.7) strcpy(ui.Player_HPbar, "■■■■■■■□□□");
	else if (ui.MyHP / ui.MyMaxHP > 0.5 && ui.MyHP / ui.MyMaxHP <= 0.6) strcpy(ui.Player_HPbar, "■■■■■■□□□□");
	else if (ui.MyHP / ui.MyMaxHP > 0.4 && ui.MyHP / ui.MyMaxHP <= 0.5) strcpy(ui.Player_HPbar, "■■■■■□□□□□");
	else if (ui.MyHP / ui.MyMaxHP > 0.3 && ui.MyHP / ui.MyMaxHP <= 0.4) strcpy(ui.Player_HPbar, "■■■■□□□□□□");
	else if (ui.MyHP / ui.MyMaxHP > 0.2 && ui.MyHP / ui.MyMaxHP <= 0.3) strcpy(ui.Player_HPbar, "■■■□□□□□□□");
	else if (ui.MyHP / ui.MyMaxHP > 0.1 && ui.MyHP / ui.MyMaxHP <= 0.2) strcpy(ui.Player_HPbar, "■■□□□□□□□□");
	else if (ui.MyHP / ui.MyMaxHP > 0 && ui.MyHP / ui.MyMaxHP <= 0.1) strcpy(ui.Player_HPbar, "■□□□□□□□□□");
	if (ui.MyHP / ui.MyMaxHP <= 0) strcpy(ui.Player_HPbar, "□□□□□□□□□□");
}

void Enemy_HPbar()
{
	if (enemy_target->hp / enemy_target->maxhp > 0.9) strcpy(ui.Enemy_HPbar, "■■■■■■■■■■");
	else if (enemy_target->hp / enemy_target->maxhp > 0.8 && enemy_target->hp / enemy_target->maxhp <= 0.9) strcpy(ui.Enemy_HPbar, "■■■■■■■■■□");
	else if (enemy_target->hp / enemy_target->maxhp > 0.7 && enemy_target->hp / enemy_target->maxhp <= 0.8) strcpy(ui.Enemy_HPbar, "■■■■■■■■□□");
	else if (enemy_target->hp / enemy_target->maxhp > 0.6 && enemy_target->hp / enemy_target->maxhp <= 0.7) strcpy(ui.Enemy_HPbar, "■■■■■■■□□□");
	else if (enemy_target->hp / enemy_target->maxhp > 0.5 && enemy_target->hp / enemy_target->maxhp <= 0.6) strcpy(ui.Enemy_HPbar, "■■■■■■□□□□");
	else if (enemy_target->hp / enemy_target->maxhp > 0.4 && enemy_target->hp / enemy_target->maxhp <= 0.5) strcpy(ui.Enemy_HPbar, "■■■■■□□□□□");
	else if (enemy_target->hp / enemy_target->maxhp > 0.3 && enemy_target->hp / enemy_target->maxhp <= 0.4) strcpy(ui.Enemy_HPbar, "■■■■□□□□□□");
	else if (enemy_target->hp / enemy_target->maxhp > 0.2 && enemy_target->hp / enemy_target->maxhp <= 0.3) strcpy(ui.Enemy_HPbar, "■■■□□□□□□□");
	else if (enemy_target->hp / enemy_target->maxhp > 0.1 && enemy_target->hp / enemy_target->maxhp <= 0.2) strcpy(ui.Enemy_HPbar, "■■□□□□□□□□");
	else if (enemy_target->hp / enemy_target->maxhp > 0 && enemy_target->hp / enemy_target->maxhp <= 0.1) strcpy(ui.Enemy_HPbar, "■□□□□□□□□□");
	if (enemy_target->hp / enemy_target->maxhp <= 0) strcpy(ui.Enemy_HPbar, "□□□□□□□□□□");
}

