#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define CLOCK 15	// 프레임당 밀리초

#include "all_include.h"
#include "title.h"

const double fps = CLOCK / (double)1000;
static char string[100] = { 0 };

/* 초기화 관련 */
int ConstInit();					// 딱 처음 한번만 초기화(변하지 말아야 할것들)
int Init();						// 죽었을때 초기화(초기 설정, 변하지 않는 것들)

int StageInit(int stage_number);	// 맵별 초기화(맵별로 다름. 몇번맵?)

/* 실제 동작부 */
void Render();						// 화면 출력

void MapObject();					// 맵 뒷배경 (사실상 씬)
void PlayerControl();			// 1. 플레이어 관련 함수
void MapInit(int(*map)[HEIGHT]);	// 맵 배열 생성(벽, 장애물, 포탈, NPC 등등 생성)
void TotalUI();					// 2. UI 관련 함수

/* 화면 관련 */
int WaitRender(clock_t OldTime);	// 화면 지연시간
void Release();						// 할당 해제(프로그램 종료)
int GetKeyEvent();					// 키 입력받기(인벤창, 종료, 리셋 등)


int ConstInit()
{
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
	second = 0;

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
			if (second <= fps) second = 0;
			else second -= fps;

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
			PrintScreen(53, 14, "등급 아이템 획득!!");
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

void TotalUI()
{
	for (int i = 0; i < WIDTH; i++)
	{
		PrintScreen(ui.position.x, ui.position.y + i, "┃");
	}
	for (int i = 1; i < HEIGHT; i++)
	{
		PrintScreen(ui.position.x + i, 9, "━");
		PrintScreen(ui.position.x + i, 13, "━");
		PrintScreen(ui.position.x + i, 16, "━");
		PrintScreen(ui.position.x + i, 28, "…");
	}

	sprintf(string, "x : %d / y : %d", player.collide.x, player.collide.y);
	PrintScreen(83, 1, string);
	sprintf(string, "보유 돈 : %d", ui.Money);
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

	if (player.state == DISAPPEAR)	// 상점 안에서의 인터페이스
	{
		if (shop.select == 1 && ui.Money < 200)
		{
			PrintScreen(83, 14, "돈이 부족합니다!!");
		}
		else if (shop.rank == S)
		{
			PrintScreen(83, 14, "등급S : 5%");
			PrintScreen(83, 15, "확실히 특별한 능력이 있습니다!");
		}
		else if (shop.rank == A)
		{
			PrintScreen(83, 14, "등급A : 10%");
			PrintScreen(83, 15, "쪼금 특별한 능력이 있습니다.");
		}
		else if (shop.rank == B)
		{
			PrintScreen(83, 14, "등급B : 35%");
			PrintScreen(83, 15, "C 무기보다는 살짝 좋습니다.");
		}
		else if (shop.rank == C)
		{
			PrintScreen(83, 14, "등급C : 50%");
			PrintScreen(83, 15, "지극히 평범한 무기입니다.");
		}
		else
		{
			PrintScreen(83, 14, "방향키로 이동, 엔터로 선택");
			PrintScreen(83, 15, "S 5%, A 15%, B 30% C 50%");
		}
	}
	else if (notice.Danger == TRUE)	// 장애물에 닿고 있을 때
	{
		PrintScreen(83, 14, "장애물에 닿고 있어요. 조심하세요!");
	}
	else if (notice.CollideEnemy == TRUE)	// 적군 타게팅
	{
		PrintScreen(83, 14, enemy_target->name);
		PrintScreen(83, 15, enemy_target->info);
	}
	else if (notice.GetMoney == TRUE)	// 적을 잡고 돈을 얻었을 때
	{
		sprintf(string, "광물을 캐고 %d원을 얻었습니다!", notice.temp_money);
		PrintScreen(83, 14, string);
	}
	else if (notice.Critical >= 1)	// 정확한 타이밍에 공격 성공
	{
		sprintf(string, "크리티컬!! %d COMBO", notice.Critical);
		PrintScreen(83, 14, string);
		sprintf(string, "%.lf데미지를 주었습니다!", ui.MyAtt * 1.5);
		PrintScreen(83, 15, string);
	}
	else if (notice.HitEnemy == TRUE)	// 공격 성공
	{
		sprintf(string, "타격 성공! %.lf데미지를 주었습니다!", ui.MyAtt);
		PrintScreen(83, 14, string);
	}
	else if (notice.Damaged == TRUE)	// 타이밍을 못맞춰서 데미지를 받았을 때
	{
		sprintf(string, "아이고! %.lf데미지를 받았습니다 ㅜㅜ", enemy_target->att);
		PrintScreen(83, 14, string);
	}
	else
	{
		PrintScreen(83, 14, "A키  공격시작");
		PrintScreen(83, 15, "타이밍 맞춰서 F키 공격(크리티컬 x1.5)");
	}

	sprintf(string, "확인용 남은초 : %.2lf", second);
	PrintScreen(83, 17, string);
	sprintf(string, "내 상태 : %d", player.state);
	PrintScreen(83, 18, string);

	if (player.state == DEAD)
	{
		PrintScreen(83, 29, "당신은 죽었습니다! 곧 부활합니다");
		sprintf(string, "남은 리스폰 시간 : %.1lf초", ui.respawn);
		PrintScreen(83, 30, string);
	}
	else if (ui.MyHP / ui.MyMaxHP <= 0.25)
	{
		PrintScreen(83, 29, "체력이 낮습니다.");
		PrintScreen(83, 30, "체력을 회복하세요!!");
	}
}
