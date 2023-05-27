#pragma once
#include "all_include.h"
#include "item.h"
#include "shop.h"
#include "equipment.h"

typedef struct Inventory
{
	Item* info;		// ������ ���� ������
	int use;		// �κ��丮â �����?
	int now_equip;	// ������?
}Inventory;

int inventory_count;
Inventory inventory[10];

void AddInventory();