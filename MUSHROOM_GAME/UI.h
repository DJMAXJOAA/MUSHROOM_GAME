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
	int state;	// ���â, �κ�â, �����ۻ��â
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

void InitNotice();	// ui �˸�â �ʱ�ȭ
void Player_HPbar(); // �÷��̾� ü�¹�
void Enemy_HPbar(); // ���� ü�¹�
void ShopSelect();	// ���� ����

