#include "setting.h"

const double fps = CLOCK / (double)1000;

int ConstInit()
{
	/* 캐릭터 생김새 */
	player.nLength = strlen(PLAYER_STR1);
	player.strPlayer1 = (char*)malloc(sizeof(char) * player.nLength);
	strcpy(player.strPlayer1, PLAYER_STR1);
	player.strPlayer2 = (char*)malloc(sizeof(char) * player.nLength);
	strcpy(player.strPlayer2, PLAYER_STR2);
	player.strPlayer3 = (char*)malloc(sizeof(char) * player.nLength);
	strcpy(player.strPlayer3, PLAYER_STR3);

	/* 인벤창 비우기 */
	inventory_count = 0;
	for (int i = 0; i < 10; i++)
	{
		inventory[i].use = FALSE;
		inventory[i].now_equip = FALSE;
		inventory[i].info = &item_C[0];
	}
	
	/* UI 초기 셋팅 */
	strcpy(ui.Player_Name, "님이름");
	ui.state = UI_INVENTORY_DEACTIVE;
	ui.Money = 0;
	ui.MyAtt = 10;
	ui.MyMaxHP = 100;
	ui.MyHP = 100;

	ui.position.x = 80;
	ui.position.y = 0;

	inventory[0].use = TRUE;
	inventory[0].info = &item_S[0];
	inventory[1].use = TRUE;
	inventory[1].info = &item_S[1];
	inventory[2].use = TRUE;
	inventory[2].info = &item_S[2];
	inventory[3].use = TRUE;
	inventory[3].info = &item_A[0];
	inventory[4].use = TRUE;
	inventory[4].info = &item_A[1];

	return 0;
}

int Init()
{
	second_all = 0;

	player.position.x = 2;
	player.position.y = 17;
	player.isReady = CANT_ATTACK;
	player.state = ALIVE;

	/* 적 타겟 초기화 */
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

void Render()
{
	ScreenClear();
	/*─────────────────────────────────────────────────────────────────────*/

	/* 각 맵마다 오브젝트, 맵 요소 */
	if (stage == TITLE) TitleSelect();
	if (stage == SHOP1) ShopSelect();
	if (stage == SHOP2) ShopSelect2();
	if (stage == END) TitleSelect();
	
	if (ui.state == UI_INVENTORY_ACTIVE) EquipmentItem();

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