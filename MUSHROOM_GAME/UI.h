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


typedef struct
{
	int Critial;

}Inventory;

UI ui;
UI* p_ui;
Notice notice;
Inventory inventory[10];

void InitNotice();	// ui 알림창 초기화
void Player_HPbar(); // 플레이어 체력바
void Enemy_HPbar(); // 몬스터 체력바
void ShopSelect();	// 상점 선택

