#pragma once

#define SHOP_COUNT_LANGE 100

#include "all_include.h"
#include "player.h"

typedef struct SHOP
{
	int select;
	int count;
	int count_lange;
	int count_stop;
	int rank;
	int arr[100];
	int cheat;
}SHOP;

SHOP shop;
SHOP* pshop;

void ShopSelect();
void RouletteInit();
void RouletteMove();
void RouletteFilePrint();