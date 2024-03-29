#include "shop.h"

int shop_result = 0;

void ShopSelect()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		if (shop.select == 1)
		{
			if (ui.Money < 200)
			{
				//돈이 부족합니다! 알림창 출력
			}
			else if (inventory_count == 10)
			{
				//인벤창 꽉찼습니다! 알림창 출력
			}
			else
			{
				ui.Money -= 200;
				RouletteInit();
				stage = ROULETTE;
			}
		}

		if (shop.select == 2)
		{
			player.state = ALIVE;
			stage = TOWN;
			shop.cheat == FALSE;
			Init();
			StageInit(stage);
		}
	}
	if (GetAsyncKeyState(0x50) & 0x8000)	// p키 S확정
	{
		shop.cheat = TRUE;
		RouletteInit();
		stage = ROULETTE;
	}

	if (stage == SHOP1)
	{
		if (GetAsyncKeyState(VK_LEFT) & 0x8000 && second_all <= 0)
		{
			if (shop.select == 2) shop.select = 1;
			second_all = 0.1;
		}

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && second_all <= 0)
		{
			if (shop.select == 1) shop.select = 2;
			second_all = 0.1;
		}
	}
	else if (stage == ROULETTE)
	{
		if (GetAsyncKeyState(VK_UP) & 0x8000 && second_all <= 0)
		{
			if (shop.select == 2) shop.select = 1;
			second_all = 0.1;
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000 && second_all <= 0)
		{
			if (shop.select == 1) shop.select = 2;
			second_all = 0.1;
		}
	}
}

void ShopSelect2()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000 && second_all <= 0)
	{
		if (shop.select == 2) shop.select = 1;
		else if (shop.select == 3) shop.select = 2;
		second_all = 0.1;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && second_all <= 0)
	{
		if (shop.select == 1) shop.select = 2;
		else if (shop.select == 2) shop.select = 3;
		second_all = 0.1;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000 && second_all <= 0)
	{
		if (shop.select == 4) shop.select = 3;
		second_all = 0.1;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000 && second_all <= 0)
	{
		shop.select = 4;
		second_all = 0.1;
	}
}

void RouletteMove()
{
	if (shop.count_lange <= 6)	// 인벤토리에 추가, 알림 출력
	{
		shop.count_lange = SHOP_COUNT_LANGE;
		shop.count = 0;
		shop.count_stop = TRUE;

		if (shop.arr[2] >= 0 && shop.arr[2] < 5)
		{
			shop.rank = S;
		}
		else if (shop.arr[2] >= 5 && shop.arr[2] < 20)
		{
			shop.rank = A;
		}
		else if (shop.arr[2] >= 20 && shop.arr[2] < 50)
		{
			shop.rank = B;
		}
		else shop.rank = C;
		AddInventory();
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
	shop.count_lange = SHOP_COUNT_LANGE;
	shop.count = 10;
	shop.count_stop = FALSE;
	shop.rank = 5;

	if (shop.cheat == TRUE)
	{
		for (int i = 0; i < shop.count_lange; i++)
		{
			shop.arr[i] = 1;
		}
	}
	else
	{
		for (int i = 0; i < shop.count_lange; i++)
		{
			shop.arr[i] = Random(i, 100 - i) - i;
		}
	}
}

void RouletteFilePrint()
{
	for (int i = 0; i < 5; i++)
	{
		if (shop.arr[i] >= 0 && shop.arr[i] < 5)
		{
			SetColor(VIOLET);
			FilePrintStr("rankS.txt", 12, 25 - (i * 6));
		}
		else if (shop.arr[i] >= 5 && shop.arr[i] < 20)
		{
			SetColor(GREEN);
			FilePrintStr("rankA.txt", 12, 25 - (i * 6));
		}
		else if (shop.arr[i] >= 20 && shop.arr[i] < 50)
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