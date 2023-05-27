#pragma once
#include "all_include.h"
#include "item.h"
#include "shop.h"
#include "inventory.h"

typedef struct Inventory
{
	int use;
	Item* info;
}Inventory;

Inventory inventory[10];

void AddInventory();