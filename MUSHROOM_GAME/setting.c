#include "setting.h"

const double fps = CLOCK / (double)1000;
static char string[100] = { 0 };

int ConstInit()
{
	
	inventory_count = 0;
	for (int i = 0; i < 10; i++)
	{
		inventory[i].use = FALSE;
		inventory[i].now_equip = FALSE;
		inventory[i].info = &item_C[0];
	}

	ui.Money = 0;
	ui.MyAtt = 10;
	ui.MyMaxHP = 100;
	ui.MyHP = 100;
	strcpy(ui.Player_Name, "호옹이");

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
	strcpy(ui.Enemy_HPbar, "□□□□□□□□□□");

	init_missile.x = 0;
	init_missile.y = 0;
	init_missile.speed = 0;
	init_missile.interval = 0;
	init_missile.extinct = FALSE;
	missile1.x = 82;
	missile1.y = 11;
	missile1.speed = 1.5;
	missile1.interval = RandomDouble(10, 30);
	missile1.extinct = FALSE;
	missile2.x = 82;
	missile2.y = 11;
	missile2.speed = 1.5;
	missile2.interval = RandomDouble(11, 30);
	missile2.extinct = FALSE;
	missile3.x = 82;
	missile3.y = 11;
	missile3.speed = 1.5;
	missile3.interval = RandomDouble(12, 30);
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
	case TITLE: // 타이틀
		map_pointer = map0;
		break;

	case TOWN:	// 마을
		map_pointer = map1;

		player.position.x = 2;
		player.position.y = 17;

		portal1.move_to_where = REGION1;
		portal2.move_to_where = SHOP1;
		portal3.move_to_where = SHOP2;
		portal4.move_to_where = END;

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
		strcpy(enemy1.name, "작은버섯");
		strcpy(enemy1.info, "간단하게 캘 수 있다");

		enemy2.att = 15;
		enemy2.hp = 150;
		enemy2.maxhp = 150;
		enemy2.dead = FALSE;
		enemy2.money = 150;
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
	/*─────────────────────────────────────────────────────────────────────*/

	/* 각 맵마다 오브젝트, 맵 요소 */
	if (stage == TITLE) TitleSelect();
	if (stage == SHOP1) ShopSelect();
	if (stage == END) TitleSelect();
	
	if (ui.state == TRUE) EquipmentItem();

	MapObject();

	if (stage != TITLE && stage != END)
	{
		/* 캐릭터 + 타이밍UI */
		PlayerControl();

		/* 맵 불러오기 (벽, 포탈, 적 등등) */
		MapInit(map_pointer);

		/* UI 상태창 셋팅 */
		TotalUI();
	}

	/*─────────────────────────────────────────────────────────────────────*/
	ScreenFlipping();
}

int WaitRender(clock_t OldTime)
{
	clock_t CurTime;	//clock_t 수행시간 측정
	while (1)
	{
		CurTime = clock();
		if (CurTime - OldTime > CLOCK)
		{
			if (second_all <= fps) second_all = 0;
			else second_all -= fps;

			if (player.state == DEAD) ui.respawn -= fps;

			if (stage == ROULETTE && shop.count_stop == FALSE)	// 룰렛
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


void Release()	//해제
{

}

int GetKeyEvent()
{
	if (_kbhit())	//_kbhit : 키보드가 눌렀음을 확인하는 함수
		return _getch();	//읽은 문자 반환

	return -1;
}

void MapInit(int(*map)[HEIGHT])
{
	for (int y = 0; y < WIDTH; y++)
		for (int x = 0; x < HEIGHT; x++)
		{
			if (map[y][x] == WALL) PrintScreen(x * 2, y, "■");
			if (map[y][x] == OBSTACLE) { SetColor(D_RED); PrintScreen(x * 2, y, "★"); SetColor(WHITE); }

			if (map[y][x] == PORTAL1)
			{
				portal1.position.x = x * 2;
				portal1.position.y = y;
				SetColor(BLUE); PrintScreen(x * 2, y, "▩"); SetColor(WHITE);
				if (player.collide.x == portal1.position.x && player.collide.y == portal1.position.y)
				{
					PortalCheck(portal1.move_to_where);
					Init();
					StageInit(stage);	// 닿으면 초기화
				}
			}
			if (map[y][x] == PORTAL2)
			{
				portal2.position.x = x * 2;
				portal2.position.y = y;
				SetColor(BLUE); PrintScreen(x * 2, y, "▩"); SetColor(WHITE);
				if (player.collide.x == portal2.position.x && player.collide.y == portal2.position.y)
				{
					PortalCheck(portal2.move_to_where);
					Init();
					StageInit(stage);	// 닿으면 초기화
				}
			}

			if (map[y][x] == PORTAL3)	// 잠깐 테스트용으로 돈먹게
			{
				portal3.position.x = x * 2;
				portal3.position.y = y;
				SetColor(BLUE); PrintScreen(x * 2, y, "▩"); SetColor(WHITE);
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
					StageInit(stage);	// 닿으면 초기화
				}
			}

			if (map[y][x] == ENEMY1)
			{
				SetColor(D_GREEN);
				if (enemy1.dead == FALSE)
				{
					enemy1.position.x = x * 2;
					enemy1.position.y = y;
					PrintScreen(enemy1.position.x, enemy1.position.y, "♣");
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
					PrintScreen(enemy2.position.x, enemy2.position.y, "♣");
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
		PrintScreen(9, 22, "경품 교환소");
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

		PrintScreen(36, 14, "얻은 무기는 마일리지로 교환 가능합니다.");
		PrintScreen(45, 15, "마일리지로 경품을 교환하세요!");

		if (shop.select == 1) PrintScreen(11, 21, "▶"); else PrintScreen(11, 21, "▷");
		PrintScreen(13, 21, "1회 뽑기 :  200원");

		if (shop.select == 2) PrintScreen(46, 21, "▶"); else PrintScreen(46, 21, "▷");
		PrintScreen(48, 21, "상점에서 나갑니다");

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
			PrintScreen(53, 14, "아이템 획득!!");
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

	/* 미사일 인터페이스 */
	PrintScreen(97, 10, "┏━━━━━┓ ");
	SetColor(YELLOW);
	if (player.isReady == NOW_ATTACKING) PrintScreen(100, 11, "☆");
	else PrintScreen(98, 11, "【☆】");
	SetColor(WHITE);
	PrintScreen(97, 12, "┗━━━━━┛ ");

	if (player.isReady == NOW_ATTACKING)
	{
		SetColor(YELLOW);
		if (missile1.extinct == FALSE) PrintScreen(missile1.x, missile1.y, "★");
		if (missile1.interval <= 0 && missile2.extinct == FALSE) PrintScreen(missile2.x, missile2.y, "★");
		if (missile2.interval <= 0 && missile3.extinct == FALSE) PrintScreen(missile3.x, missile3.y, "★");
		SetColor(WHITE);
	}
}



void TitleSelect()
{
	if (GetAsyncKeyState(VK_RETURN))
	{
		stage = 1;
		Init();
		StageInit(stage);
	}
}