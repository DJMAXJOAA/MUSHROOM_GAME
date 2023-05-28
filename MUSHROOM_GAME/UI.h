#pragma once
#include "all_include.h"
#include "enemy.h"
#include "player.h"
#include "shop.h"
#include "inventory.h"

enum UI_STATE // 0:���â 1:�κ�â 2:�κ�����â(�����Ǹŵ�), 3: �����ۻ��â
{
	UI_EQUIPMENT, UI_INVENTORY_DEACTIVE, UI_INVENTORY_ACTIVE, UI_USEITEM
};

typedef struct UI
{
	Position position;
	int Money;
	char Player_Name[10];
	double MyHP;
	double MyMaxHP;
	double MyAtt;
	double CritDMG;
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

UI ui;
UI* p_ui;
Notice notice;

void InitNotice();	// ui �˸�â �ʱ�ȭ
void Player_HPbar(); // �÷��̾� ü�¹�
void Enemy_HPbar(); // ���� ü�¹�
void ShopSelect();	// ���� ����
void TotalUI();		// ���� UI
void UISelect();	// UI �κ�â, ���â, �����â ����