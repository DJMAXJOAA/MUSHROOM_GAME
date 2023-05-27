#include "setting.h"

const double fps = CLOCK / (double)1000;
static char string[100] = { 0 };

int ConstInit()
{

	ui.Money = 0;
	ui.MyAtt = 10;
	ui.MyMaxHP = 100;
	ui.MyHP = 100;
	strcpy(ui.Player_Name, "ȣ����");

	ui.position.x = 80;
	ui.position.y = 0;

	return 0;
}

int Init()
{
	second_all = 0;

	player.nLength = strlen(PLAYER_STR1);
	player.strPlayer1 = (char*)malloc(sizeof(char) * player.nLength);
	strcpy(player.strPlayer1, PLAYER_STR1);
	player.strPlayer2 = (char*)malloc(sizeof(char) * player.nLength);
	strcpy(player.strPlayer2, PLAYER_STR2);
	player.strPlayer3 = (char*)malloc(sizeof(char) * player.nLength);
	strcpy(player.strPlayer3, PLAYER_STR3);

	player.position.x = 2;
	player.position.y = 17;
	player.isReady = CANT_ATTACK;
	player.state = ALIVE;

	enemy.att = 0;
	enemy.maxhp = 0;
	enemy.hp = 0;
	enemy.dead = FALSE;
	enemy.money = 0;
	strcpy(enemy.name, "TARGET");
	strcpy(ui.Enemy_HPbar, "�����������");

	init_missile.x = 0;
	init_missile.y = 0;
	init_missile.speed = 0;
	init_missile.interval = 0;
	init_missile.extinct = FALSE;
	missile1.x = 82;
	missile1.y = 11;
	missile1.speed = 1.5;
	missile1.interval = random_double(10, 30);
	missile1.extinct = FALSE;
	missile2.x = 82;
	missile2.y = 11;
	missile2.speed = 1.5;
	missile2.interval = random_double(11, 30);
	missile2.extinct = FALSE;
	missile3.x = 82;
	missile3.y = 11;
	missile3.speed = 1.5;
	missile3.interval = random_double(12, 30);
	missile3.extinct = FALSE;

	ui.EnemyAtt = 0;
	ui.EnemyHP = 0;

	InitNotice();

	return 0;
}

int StageInit(int stage_number)
{
	switch (stage_number)
	{
	case TITLE: // Ÿ��Ʋ
		map_pointer = map0;
		break;

	case TOWN:	// ����
		map_pointer = map1;

		player.position.x = 2;
		player.position.y = 17;

		portal1.move_to_where = REGION1;
		portal2.move_to_where = SHOP1;
		portal3.move_to_where = SHOP2;
		portal4.move_to_where = END;

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
		strcpy(enemy1.name, "��������");
		strcpy(enemy1.info, "�����ϰ� Ķ �� �ִ�");

		enemy2.att = 15;
		enemy2.hp = 150;
		enemy2.maxhp = 150;
		enemy2.dead = FALSE;
		enemy2.money = 150;
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

void Render()
{
	ScreenClear();
	/*������������������������������������������������������������������������������������������������������������������������������������������*/

	/* �� �ʸ��� ������Ʈ, �� ��� */
	if (stage == TITLE) TitleSelect();
	if (stage == SHOP1) ShopSelect();
	if (stage == END) TitleSelect();

	MapObject();

	if (stage != TITLE && stage != END)
	{
		/* ĳ���� + Ÿ�̹�UI */
		PlayerControl();

		/* �� �ҷ����� (��, ��Ż, �� ���) */
		MapInit(map_pointer);

		/* UI ����â ���� */
		TotalUI();
	}

	/*������������������������������������������������������������������������������������������������������������������������������������������*/
	ScreenFlipping();
}

int WaitRender(clock_t OldTime)
{
	clock_t CurTime;	//clock_t ����ð� ����
	while (1)
	{
		CurTime = clock();
		if (CurTime - OldTime > CLOCK)
		{
			if (second_all <= fps) second_all = 0;
			else second_all -= fps;

			if (player.state == DEAD) ui.respawn -= fps;

			if (stage == ROULETTE && shop.count_stop == FALSE)	// �귿
			{
				shop.count--;
				if (shop.count <= 1)
				{
					if (shop.count_lange > 20)
					{
						shop.count_lange -= 1;
						shop.count = 2;
					}
					else if (shop.count_lange <= 20 && shop.count_lange > 8)
					{
						shop.count_lange -= 1;
						shop.count = 5;
					}
					else if (shop.count_lange <= 8)
					{
						shop.count_lange -= 1;
						shop.count = 10;
					}
				}
			}
			break;
		}

	}
	return 0;
}


void Release()	//����
{

}

int GetKeyEvent()
{
	if (_kbhit())	//_kbhit : Ű���尡 �������� Ȯ���ϴ� �Լ�
		return _getch();	//���� ���� ��ȯ

	return -1;
}

void MapInit(int(*map)[HEIGHT])
{
	for (int y = 0; y < WIDTH; y++)
		for (int x = 0; x < HEIGHT; x++)
		{
			if (map[y][x] == WALL) PrintScreen(x * 2, y, "��");
			if (map[y][x] == OBSTACLE) { SetColor(D_RED); PrintScreen(x * 2, y, "��"); SetColor(WHITE); }

			if (map[y][x] == PORTAL1)
			{
				portal1.position.x = x * 2;
				portal1.position.y = y;
				SetColor(BLUE); PrintScreen(x * 2, y, "��"); SetColor(WHITE);
				if (player.collide.x == portal1.position.x && player.collide.y == portal1.position.y)
				{
					PortalCheck(portal1.move_to_where);
					Init();
					StageInit(stage);	// ������ �ʱ�ȭ
				}
			}
			if (map[y][x] == PORTAL2)
			{
				portal2.position.x = x * 2;
				portal2.position.y = y;
				SetColor(BLUE); PrintScreen(x * 2, y, "��"); SetColor(WHITE);
				if (player.collide.x == portal2.position.x && player.collide.y == portal2.position.y)
				{
					PortalCheck(portal2.move_to_where);
					Init();
					StageInit(stage);	// ������ �ʱ�ȭ
				}
			}

			if (map[y][x] == PORTAL3)	// ��� �׽�Ʈ������ ���԰�
			{
				portal3.position.x = x * 2;
				portal3.position.y = y;
				SetColor(BLUE); PrintScreen(x * 2, y, "��"); SetColor(WHITE);
				if (player.collide.x == portal3.position.x && player.collide.y == portal3.position.y)
				{
					ui.Money += 10000;
				}
			}

			if (map[y][x] == PORTAL4)
			{
				portal4.position.x = x * 2;
				portal4.position.y = y;
				if (player.collide.x == portal4.position.x && player.collide.y == portal4.position.y)
				{
					PortalCheck(portal4.move_to_where);
					Init();
					StageInit(stage);	// ������ �ʱ�ȭ
				}
			}

			if (map[y][x] == ENEMY1)
			{
				SetColor(D_GREEN);
				if (enemy1.dead == FALSE)
				{
					enemy1.position.x = x * 2;
					enemy1.position.y = y;
					PrintScreen(enemy1.position.x, enemy1.position.y, "��");
					if (player.collide.x == enemy1.position.x && player.collide.y == enemy1.position.y) EnemyTargetChange(&enemy1);
				}
				SetColor(WHITE);
			}
			if (map[y][x] == ENEMY2)
			{
				SetColor(D_GREEN);
				if (enemy2.dead == FALSE)
				{
					enemy2.position.x = x * 2;
					enemy2.position.y = y;
					PrintScreen(enemy2.position.x, enemy2.position.y, "��");
					if (player.collide.x == enemy2.position.x && player.collide.y == enemy2.position.y) EnemyTargetChange(&enemy2);
				}
				SetColor(WHITE);
			}
		}
}


void MapObject()
{
	if (stage == TITLE)
	{
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
		PrintScreen(9, 22, "��ǰ ��ȯ��");
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

		PrintScreen(36, 14, "���� ����� ���ϸ����� ��ȯ �����մϴ�.");
		PrintScreen(45, 15, "���ϸ����� ��ǰ�� ��ȯ�ϼ���!");

		if (shop.select == 1) PrintScreen(11, 21, "��"); else PrintScreen(11, 21, "��");
		PrintScreen(13, 21, "1ȸ �̱� :  200��");

		if (shop.select == 2) PrintScreen(46, 21, "��"); else PrintScreen(46, 21, "��");
		PrintScreen(48, 21, "�������� �����ϴ�");

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
			PrintScreen(53, 14, "��� ������ ȹ��!!");
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

void PlayerControl()
{
	if (player.state == ALIVE)
	{
		if (player.isReady == NOW_ATTACKING) SetColor(D_GREEN);
		if (ObstacleCheck()) {
			SetColor(D_RED);
			ui.MyHP -= OBSTACLE_DAMAGE;
			notice.Danger = TRUE;
		}
		else notice.Danger = FALSE;
		PrintScreen(player.position.x, player.position.y, player.strPlayer1);
		PrintScreen(player.position.x, player.position.y + 1, player.strPlayer2);
		PrintScreen(player.position.x, player.position.y + 2, player.strPlayer3);
		SetColor(WHITE);
	}

	/* �̻��� �������̽� */
	PrintScreen(97, 10, "�������������� ");
	SetColor(YELLOW);
	if (player.isReady == NOW_ATTACKING) PrintScreen(100, 11, "��");
	else PrintScreen(98, 11, "���١�");
	SetColor(WHITE);
	PrintScreen(97, 12, "�������������� ");

	if (player.isReady == NOW_ATTACKING)
	{
		SetColor(YELLOW);
		if (missile1.extinct == FALSE) PrintScreen(missile1.x, missile1.y, "��");
		if (missile1.interval <= 0 && missile2.extinct == FALSE) PrintScreen(missile2.x, missile2.y, "��");
		if (missile2.interval <= 0 && missile3.extinct == FALSE) PrintScreen(missile3.x, missile3.y, "��");
		SetColor(WHITE);
	}
}

void TotalUI()
{
	for (int i = 0; i < WIDTH; i++)
	{
		PrintScreen(ui.position.x, ui.position.y + i, "��");
	}
	for (int i = 1; i < HEIGHT; i++)
	{
		PrintScreen(ui.position.x + i, 9, "��");
		PrintScreen(ui.position.x + i, 13, "��");
		PrintScreen(ui.position.x + i, 16, "��");
		PrintScreen(ui.position.x + i, 28, "��");
	}

	sprintf(string, "x : %d / y : %d", player.collide.x, player.collide.y);
	PrintScreen(83, 1, string);
	sprintf(string, "���� �� : %d", ui.Money);
	PrintScreen(83, 2, string);
	sprintf(string, "stage number : %d", stage);
	PrintScreen(83, 3, string);

	sprintf(string, "%s\t%s", ui.Player_Name, ui.Player_HPbar);
	PrintScreen(83, 4, string);
	sprintf(string, "HP:%.1lf / ATT:%.1lf\t", ui.MyHP, ui.MyAtt);
	PrintScreen(83, 5, string);
	sprintf(string, "%s\t%s", enemy_target->name, ui.Enemy_HPbar);
	PrintScreen(83, 6, string);
	sprintf(string, "HP:%.1lf / ATT:%.1lf\t", ui.EnemyHP, ui.EnemyAtt);
	PrintScreen(83, 7, string);

	if (player.state == DISAPPEAR)	// ���� �ȿ����� �������̽�
	{
		if (shop.select == 1 && ui.Money < 200)
		{
			PrintScreen(83, 14, "���� �����մϴ�!!");
		}
		else if (shop.rank == S)
		{
			PrintScreen(83, 14, "���S : 5%");
			PrintScreen(83, 15, "Ȯ���� Ư���� �ɷ��� �ֽ��ϴ�!");
		}
		else if (shop.rank == A)
		{
			PrintScreen(83, 14, "���A : 10%");
			PrintScreen(83, 15, "�ɱ� Ư���� �ɷ��� �ֽ��ϴ�.");
		}
		else if (shop.rank == B)
		{
			PrintScreen(83, 14, "���B : 35%");
			PrintScreen(83, 15, "C ���⺸�ٴ� ��¦ �����ϴ�.");
		}
		else if (shop.rank == C)
		{
			PrintScreen(83, 14, "���C : 50%");
			PrintScreen(83, 15, "������ ����� �����Դϴ�.");
		}
		else
		{
			PrintScreen(83, 14, "����Ű�� �̵�, ���ͷ� ����");
			PrintScreen(83, 15, "S 5%, A 15%, B 30% C 50%");
		}
	}
	else if (notice.Danger == TRUE)	// ��ֹ��� ��� ���� ��
	{
		PrintScreen(83, 14, "��ֹ��� ��� �־��. �����ϼ���!");
	}
	else if (notice.CollideEnemy == TRUE)	// ���� Ÿ����
	{
		PrintScreen(83, 14, enemy_target->name);
		PrintScreen(83, 15, enemy_target->info);
	}
	else if (notice.GetMoney == TRUE)	// ���� ��� ���� ����� ��
	{
		sprintf(string, "������ ĳ�� %d���� ������ϴ�!", notice.temp_money);
		PrintScreen(83, 14, string);
	}
	else if (notice.Critical >= 1)	// ��Ȯ�� Ÿ�ֿ̹� ���� ����
	{
		sprintf(string, "ũ��Ƽ��!! %d COMBO", notice.Critical);
		PrintScreen(83, 14, string);
		sprintf(string, "%.lf�������� �־����ϴ�!", ui.MyAtt * 1.5);
		PrintScreen(83, 15, string);
	}
	else if (notice.HitEnemy == TRUE)	// ���� ����
	{
		sprintf(string, "Ÿ�� ����! %.lf�������� �־����ϴ�!", ui.MyAtt);
		PrintScreen(83, 14, string);
	}
	else if (notice.Damaged == TRUE)	// Ÿ�̹��� �����缭 �������� �޾��� ��
	{
		sprintf(string, "���̰�! %.lf�������� �޾ҽ��ϴ� �̤�", enemy_target->att);
		PrintScreen(83, 14, string);
	}
	else
	{
		PrintScreen(83, 14, "AŰ  ���ݽ���");
		PrintScreen(83, 15, "Ÿ�̹� ���缭 FŰ ����(ũ��Ƽ�� x1.5)");
	}

	sprintf(string, "Ȯ�ο� ������ : %.2lf", second_all);
	PrintScreen(83, 17, string);
	sprintf(string, "�� ���� : %d", player.state);
	PrintScreen(83, 18, string);

	if (player.state == DEAD)
	{
		PrintScreen(83, 29, "����� �׾����ϴ�! �� ��Ȱ�մϴ�");
		sprintf(string, "���� ������ �ð� : %.1lf��", ui.respawn);
		PrintScreen(83, 30, string);
	}
	else if (ui.MyHP / ui.MyMaxHP <= 0.25)
	{
		PrintScreen(83, 29, "ü���� �����ϴ�.");
		PrintScreen(83, 30, "ü���� ȸ���ϼ���!!");
	}
}
