#include "stage_setting.h"

int StageInit(int stage_number)
{
	switch (stage_number)
	{
	case TITLE: // 타이틀
		map_pointer = map0;
		break;

	case TOWN:	// 마을
		enemy_target = &enemy;
		map_pointer = map1;

		player.position.x = 2;
		player.position.y = 17;

		portal1.move_to_where = REGION1;
		portal2.move_to_where = SHOP1;
		portal3.move_to_where = SHOP2;
		portal4.move_to_where = SHOP2;

		break;

	case REGION1:	// 던전
		map_pointer = map2;

		player.position.x = 4;
		player.position.y = 14;

		enemy_target = &enemy;
		enemy1.att = 10;
		enemy1.hp = 100;
		enemy1.maxhp = 100;
		enemy1.dead = FALSE;
		enemy1.money = 100;
		strcpy(enemy1.name, "구리");
		strcpy(enemy1.info, "간단하게 캘 수 있다");

		enemy2.att = 15;
		enemy2.hp = 500;
		enemy2.maxhp = 500;
		enemy2.dead = FALSE;
		enemy2.money = 1000;
		strcpy(enemy2.name, "중간버섯");
		strcpy(enemy2.info, "살짝 캐기 버겁다");

		portal1.move_to_where = TOWN;
		portal2.move_to_where = END;
		break;

	case SHOP1:	// 상점 (캐릭 이동불가, 커서)
		map_pointer = map3;

		shop.select = 1;
		shop.rank = 5;

		break;

	case SHOP2:
		map_pointer = map3;
		shop.select = 1;

		break;

	case ROULETTE:
		map_pointer = map3;

		break;

	case END:
		map_pointer = map0;
		break;
	}

	return 0;
}

void MapObject()
{
	if (stage == TITLE)
	{
		if (GetAsyncKeyState(VK_RETURN))
		{
			stage = 1;
			Init();
			StageInit(stage);
		}
		FilePrintStr("title_background.txt", 0, 0);

		SetColor(YELLOW);
		FilePrintStr("title1.txt", 12, 2);
		FilePrintStr("title2.txt", 12, 20);
		SetColor(WHITE);

		PrintScreen(47, 16, "Press enter to START!");
	}

	if (stage == TOWN)
	{
		PrintScreen(58, 22, "무기 랜덤 뽑기");
		PrintScreen(9, 22, "생존 아이템 상점");
		SetColor(GRAY);
		FilePrintStr("house2.txt", 54, 23);
		FilePrintStr("house3.txt", 1, 23);
		SetColor(WHITE);

		FilePrintStr("road.txt", 1, 16);

		SetColor(GRAY);
		FilePrintStr("house.txt", 1, 1);
		SetColor(WHITE);

		PrintScreen(33, 9, "쉼터");
		for (int i = 0; i < 7; i++)
		{
			PrintScreen(37, 21 + i, "|");
			PrintScreen(45, 21 + i, "|");
		}
		PrintScreen(46, 27, "--------");
	}


	if (stage == REGION1)
	{
		SetColor(D_GREEN);
		FilePrintStr("background.txt", 4, 9);
		FilePrintStr("background2.txt", 15, 5);
		SetColor(WHITE);

		for (int y = 0; y < WIDTH; y++)
		{
			for (int x = 0; x < HEIGHT; x++)
			{
				if (map2[y][x] == EMPTY) PrintScreen(x * 2, y, "　");
			}
		}
	}

	if (stage == SHOP1)
	{
		player.state = DISAPPEAR;
		SetColor(D_GRAY);
		FilePrintStr("background_pattern.txt", 1, 1);
		FilePrintStr("background_pattern.txt", 1, 16);
		SetColor(WHITE);

		FilePrintStr("shop_border.txt", 4, 8);

		SetColor(YELLOW);
		PrintScreen(28, 10, "※※ 무기 랜덤 뽑기 ※※");
		PrintScreen(26, 11, "S등급 무기에 도전해 보세요!!");
		SetColor(WHITE);

		PrintScreen(36, 14, "얻은 무기는 다시 판매할 수 있습니다.");
		PrintScreen(38, 15, "S 500원, A 250원, B 100원, C 50원");

		if (shop.select == 1) PrintScreen(11, 21, "▶"); else PrintScreen(11, 21, "▷");
		PrintScreen(13, 21, "1회 뽑기 :  200원");

		if (shop.select == 2) PrintScreen(46, 21, "▶"); else PrintScreen(46, 21, "▷");
		PrintScreen(48, 21, "상점에서 나갑니다");

	}

	if (stage == SHOP2)
	{
		player.state = DISAPPEAR;
		SetColor(D_GRAY);
		FilePrintStr("background_pattern.txt", 1, 1);
		FilePrintStr("background_pattern.txt", 1, 16);
		SetColor(WHITE);

		FilePrintStr("shop_border2.txt", 4, 3);

		SetColor(YELLOW);
		PrintScreen(28, 5, "※※ 생존 아이템 상점 ※※");
		SetColor(WHITE);

		PrintScreen(16, 8, "탈출을 위해서라면 이 아이템들은 꼭 필요할겁니다!");


		PrintScreen(14, 15, "귀환서");
		if (shop.select == 1) SetColor(YELLOW);
		FilePrintStr("scroll.txt", 8, 16);
		SetColor(WHITE);
		PrintScreen(8, 24, "개수 : ");

		PrintScreen(39, 15, "맥주");
		if (shop.select == 2) SetColor(YELLOW);
		FilePrintStr("postion.txt", 38, 17);
		SetColor(WHITE);
		PrintScreen(34, 24, "개수 : ");

		PrintScreen(60, 15, "폭탄");
		if (shop.select == 3) SetColor(YELLOW);
		FilePrintStr("boom.txt", 58, 17);
		SetColor(WHITE);
		PrintScreen(54, 24, "개수 : ");

		if (shop.select == 4) SetColor(YELLOW);
		PrintScreen(54, 28, "나가기");
		SetColor(WHITE);

		/*if (shop.select == 1) PrintScreen(11, 21, "▶"); else PrintScreen(11, 21, "▷");
		PrintScreen(13, 21, "1회 뽑기 :  200원");

		if (shop.select == 2) PrintScreen(46, 21, "▶"); else PrintScreen(46, 21, "▷");
		PrintScreen(48, 21, "상점에서 나갑니다");*/
	}

	if (stage == ROULETTE)
	{

		if (shop.rank == S)
		{
			SetColor(YELLOW);
			FilePrintStr("roulette_border.txt", 0, 0);
		}

		if (shop.count_stop == TRUE)
		{
			SetColor(YELLOW);
			FilePrintStr("roulette_box.txt", 6, 12);
			SetColor(WHITE);

			ShopSelect();
			sprintf(string, "%c등급 아이템 획득!!", inventory[shop_result].info->rank);
			PrintScreen(53, 14, string);
			PrintScreen(53, 15, "다시 뽑으시겠습니까??");

			if (shop.select == 1) PrintScreen(51, 17, "▶"); else PrintScreen(51, 17, "▷");
			PrintScreen(53, 17, "다시 뽑기 :  200원");

			if (shop.select == 2) PrintScreen(51, 18, "▶"); else PrintScreen(51, 18, "▷");
			PrintScreen(53, 18, "상점에서 나갑니다.");
		}

		RouletteFilePrint();
		RouletteMove();

		SetColor(WHITE);
	}

	if (stage == END)
	{
		SetColor(YELLOW);
		FilePrintStr("ending_background1.txt", 0, 5);
		FilePrintStr("ending_background2.txt", 10, 17);
		FilePrintStr("ending_background3.txt", 55, 17);
		PrintScreen(88, 27, "플레이 해주셔서 감사합니다!!");
		PrintScreen(97, 28, "인하게임개발 최형준");
		SetColor(WHITE);

	}
}