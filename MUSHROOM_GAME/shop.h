#include "all_include.h"
#include "player.h"

typedef struct SHOP
{
	int select;
	int count;
	int count_lange;
	int count_stop;
	int arr[100];
}SHOP;

SHOP shop;
SHOP *pshop;

void ShopSelect();
void RouletteInit();
void RouletteMove();
void RouletteFilePrint();
void RouletteStart();

void ShopSelect()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		if (shop.select == 1)
		{
			RouletteInit();
			stage = ROULETTE;
		}

		if (shop.select == 2)
		{
			player.state = ALIVE;
			stage = TOWN;
			Init();
			StageInit(stage);
		}
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000 && second <= 0)
	{
		if (shop.select == 2) shop.select = 1;
		second = 0.1;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && second <= 0)
	{
		if (shop.select == 1) shop.select = 2;
		second = 0.1;
	}
}

void RouletteMove()
{
	if (shop.count_lange <= 6)
	{
		shop.count_lange = 100;
		shop.count = 0;
		shop.count_stop = TRUE;
	}
	if (shop.count == 2)
	{
		for (int i = 0; i < shop.count_lange; i++)
		{
			shop.arr[i] = shop.arr[i + 1];
		}
	}
}

void RouletteInit()
{
	shop.count_lange = 100;
	shop.count = 10;
	shop.count_stop = FALSE;
	for (int i = 0; i < shop.count_lange; i++)
	{
		shop.arr[i] = random(i, 100 - i) - i;
	}
}

void RouletteFilePrint()
{
	for (int i = 0; i < 5; i ++) 
	{
		if (shop.arr[i] >= 0 && shop.arr[i] < 5)
		{
			SetColor(VIOLET);
			FilePrintStr("rankS.txt", 12, 25 - (i * 6));
		}
		else if (shop.arr[i] >= 5 && shop.arr[i] < 15)
		{
			SetColor(GREEN);
			FilePrintStr("rankA.txt", 12, 25 - (i * 6));
		}
		else if (shop.arr[i] >= 15 && shop.arr[i] < 50)
		{
			SetColor(SKYBLUE);
			FilePrintStr("rankB.txt", 12, 25 - (i * 6));
		}
		else
		{
			SetColor(WHITE);
			FilePrintStr("rankC.txt", 12, 25 - (i * 6));
		}
	}
	SetColor(WHITE);
}

void RouletteStart()
{
	if (ui.Money < 200)
	{
		//돈이 부족합니다! 알림창 출력
	}
	else if (inventory->size >= 11)
	{
		// 인벤토리 꽉찼습니다! 알림창 출력
	}
}