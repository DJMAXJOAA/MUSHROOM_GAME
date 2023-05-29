#include "stage_setting.h"

int StageInit(int stage_number)
{
	switch (stage_number)
	{
	case TITLE: // Ÿ��Ʋ
		map_pointer = map0;
		break;

	case TOWN:	// ����
		enemy_target = &enemy;
		map_pointer = map1;

		player.position.x = 2;
		player.position.y = 17;

		portal1.move_to_where = REGION1;
		portal2.move_to_where = SHOP1;
		portal3.move_to_where = SHOP2;
		portal4.move_to_where = SHOP2;

		break;

	case REGION1:	// ����
		map_pointer = map2;

		player.position.x = 4;
		player.position.y = 14;

		enemy_target = &enemy;
		enemy1.att = 10;
		enemy1.hp = 100;
		enemy1.maxhp = 100;
		enemy1.dead = FALSE;
		enemy1.money = 100;
		strcpy(enemy1.name, "����");
		strcpy(enemy1.info, "�����ϰ� Ķ �� �ִ�");

		enemy2.att = 15;
		enemy2.hp = 500;
		enemy2.maxhp = 500;
		enemy2.dead = FALSE;
		enemy2.money = 1000;
		strcpy(enemy2.name, "�߰�����");
		strcpy(enemy2.info, "��¦ ĳ�� ���̴�");

		portal1.move_to_where = TOWN;
		portal2.move_to_where = END;
		break;

	case SHOP1:	// ���� (ĳ�� �̵��Ұ�, Ŀ��)
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
		PrintScreen(58, 22, "���� ���� �̱�");
		PrintScreen(9, 22, "���� ������ ����");
		SetColor(GRAY);
		FilePrintStr("house2.txt", 54, 23);
		FilePrintStr("house3.txt", 1, 23);
		SetColor(WHITE);

		FilePrintStr("road.txt", 1, 16);

		SetColor(GRAY);
		FilePrintStr("house.txt", 1, 1);
		SetColor(WHITE);

		PrintScreen(33, 9, "����");
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
				if (map2[y][x] == EMPTY) PrintScreen(x * 2, y, "��");
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
		PrintScreen(28, 10, "�ء� ���� ���� �̱� �ء�");
		PrintScreen(26, 11, "S��� ���⿡ ������ ������!!");
		SetColor(WHITE);

		PrintScreen(36, 14, "���� ����� �ٽ� �Ǹ��� �� �ֽ��ϴ�.");
		PrintScreen(38, 15, "S 500��, A 250��, B 100��, C 50��");

		if (shop.select == 1) PrintScreen(11, 21, "��"); else PrintScreen(11, 21, "��");
		PrintScreen(13, 21, "1ȸ �̱� :  200��");

		if (shop.select == 2) PrintScreen(46, 21, "��"); else PrintScreen(46, 21, "��");
		PrintScreen(48, 21, "�������� �����ϴ�");

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
		PrintScreen(28, 5, "�ء� ���� ������ ���� �ء�");
		SetColor(WHITE);

		PrintScreen(16, 8, "Ż���� ���ؼ���� �� �����۵��� �� �ʿ��Ұ̴ϴ�!");


		PrintScreen(14, 15, "��ȯ��");
		if (shop.select == 1) SetColor(YELLOW);
		FilePrintStr("scroll.txt", 8, 16);
		SetColor(WHITE);
		PrintScreen(8, 24, "���� : ");

		PrintScreen(39, 15, "����");
		if (shop.select == 2) SetColor(YELLOW);
		FilePrintStr("postion.txt", 38, 17);
		SetColor(WHITE);
		PrintScreen(34, 24, "���� : ");

		PrintScreen(60, 15, "��ź");
		if (shop.select == 3) SetColor(YELLOW);
		FilePrintStr("boom.txt", 58, 17);
		SetColor(WHITE);
		PrintScreen(54, 24, "���� : ");

		if (shop.select == 4) SetColor(YELLOW);
		PrintScreen(54, 28, "������");
		SetColor(WHITE);

		/*if (shop.select == 1) PrintScreen(11, 21, "��"); else PrintScreen(11, 21, "��");
		PrintScreen(13, 21, "1ȸ �̱� :  200��");

		if (shop.select == 2) PrintScreen(46, 21, "��"); else PrintScreen(46, 21, "��");
		PrintScreen(48, 21, "�������� �����ϴ�");*/
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
			sprintf(string, "%c��� ������ ȹ��!!", inventory[shop_result].info->rank);
			PrintScreen(53, 14, string);
			PrintScreen(53, 15, "�ٽ� �����ðڽ��ϱ�??");

			if (shop.select == 1) PrintScreen(51, 17, "��"); else PrintScreen(51, 17, "��");
			PrintScreen(53, 17, "�ٽ� �̱� :  200��");

			if (shop.select == 2) PrintScreen(51, 18, "��"); else PrintScreen(51, 18, "��");
			PrintScreen(53, 18, "�������� �����ϴ�.");
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
		PrintScreen(88, 27, "�÷��� ���ּż� �����մϴ�!!");
		PrintScreen(97, 28, "���ϰ��Ӱ��� ������");
		SetColor(WHITE);

	}
}