#pragma once
#include "all_include.h"
#include "item.h"
#include "shop.h"
#include "equipment.h"

typedef struct Inventory
{
	Item* info;		// 아이템 정보 포인터
	int use;		// 인벤토리창 사용중?
	int now_equip;	// 장착중?
}Inventory;

int inventory_count;
Inventory inventory[10];

void AddInventory();