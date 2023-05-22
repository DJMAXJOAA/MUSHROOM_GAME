#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define CLOCK 20	// 프레임당 밀리초
#define WORD_SPEED 30
#include "all_include.h"
#include "player.h"

const double fps = CLOCK / (double)1000;
static char string[100] = { 0 };

/* 초기화 관련 */
int ConstInit();					// 딱 처음 한번만 초기화(변하지 말아야 할것들)
int Init();						// 죽었을때 초기화(초기 설정, 변하지 않는 것들)
int StageInit(int stage_number);	// 맵별 초기화(맵별로 다름. 몇번맵?)

/* 실제 동작부 */
void Render();						// 화면 출력
void PlayerControl();			// 1. 플레이어 관련 함수
void TotalUI();					// 2. UI 관련 함수

/* 화면 관련 */
void WaitRender(clock_t OldTime);	// 화면 지연시간
void Release();						// 할당 해제(프로그램 종료)
int GetKeyEvent();					// 키 입력받기(인벤창, 종료, 리셋 등)

/* 맵 생성 관련 */
void MapInit(int(*map)[HEIGHT]);	// 맵 배열 생성(벽, 장애물, 포탈, NPC 등등 생성)
void MapObject();					// 맵 뒷배경 (사실상 씬)
void FilePrintStr(char *input_str, int x, int y);	// 파일 입출력

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
	player.dead = FALSE;
	player.shop = FALSE;

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
	missile1.interval = random(10, 30);
	missile1.extinct = FALSE;
	missile2.x = 82;
	missile2.y = 11;
	missile2.speed = 1.5;
	missile2.interval = random(11, 30);
	missile2.extinct = FALSE;
	missile3.x = 82;
	missile3.y = 11;
	missile3.speed = 1.5;
	missile3.interval = random(12, 30);
	missile3.extinct = FALSE;

	portal1.move_to_where = 1;
	portal2.move_to_where = 1;
	portal3.move_to_where = 1;
	portal4.move_to_where = 1;

	ui.EnemyAtt = 0;
	ui.EnemyHP = 0;
	ui.second = 0;
	InitNotice();

	return 0;
}

int StageInit(int stage_number)
{
	switch (stage_number)
	{
	case 1:	// 마을
		map_pointer = map1;

		player.shop = FALSE;
		player.position.x = 2;
		player.position.y = 17;


		portal1.move_to_where = 2;	// 던전으로
		portal2.move_to_where = 3;	// 상점으로
		portal3.move_to_where = 4;	// 상점2로
		portal4.move_to_where = 5;	// 쉼터로

		break;

	case 2:	// 던전
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

		portal1.move_to_where = 1;
		portal2.move_to_where = 6;
		break;

	case 3:	// 상점 (캐릭 이동불가, 커서)
		map_pointer = map3;

		shop.select = 1;

		break;
	}
	return 0;
}

void Render()
{
	ScreenClear();
	/*─────────────────────────────────────────────────────────────────────*/

	/* 뒷배경 오브젝트 */
	MapObject();

	/* 캐릭터 + 타이밍UI */
	PlayerControl();

	/* 맵 불러오기 */
	MapInit(map_pointer);

	/* UI 상태창 셋팅 */
	TotalUI();


	/*─────────────────────────────────────────────────────────────────────*/
	ScreenFlipping();
}

void WaitRender(clock_t OldTime)
{
	clock_t CurTime;	//clock_t 수행시간 측정
	while (1)
	{
		CurTime = clock();
		if (CurTime - OldTime > CLOCK)
		{
			if (ui.second <= fps) ui.second = 0;
			else if (player.isReady == NOW_ATTACKING) ui.second -= fps;
			else if (player.shop == TRUE) ui.second -= fps;
			if (player.dead == TRUE) ui.respawn -= fps;
			break;
		}
	}
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

void MapInit(int(* map)[HEIGHT])
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
					StageInit(stage_number);	// 닿으면 초기화
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
					StageInit(stage_number);	// 닿으면 초기화
				}
			}

			if (map[y][x] == PORTAL3)
			{
				portal3.position.x = x * 2;
				portal3.position.y = y;
				if (player.collide.x == portal3.position.x && player.collide.y == portal3.position.y)
				{
					PortalCheck(portal3.move_to_where);
					Init();
					StageInit(stage_number);	// 닿으면 초기화
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
					StageInit(stage_number);	// 닿으면 초기화
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
	if (stage_number == 1)
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
			PrintScreen(37, 21+i, "|");
			PrintScreen(45, 21+i, "|");
		}
		PrintScreen(46, 27, "--------");
	}


	if (stage_number == 2)
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

	if (stage_number == 3)
	{
		player.shop = TRUE;
		SetColor(D_GRAY);
		FilePrintStr("background_pattern.txt", 1, 1);
		FilePrintStr("background_pattern.txt", 1, 16);
		SetColor(WHITE);

		FilePrintStr("shop_border.txt", 4, 2);
		
		SetColor(YELLOW);
		PrintScreen(28, 4, "※※ 무기 랜덤 뽑기 ※※");
		PrintScreen(26, 5, "S등급 무기에 도전해 보세요!!");
		SetColor(WHITE);
		
		PrintScreen(36, 8, "얻은 무기는 마일리지로 교환 가능합니다.");
		PrintScreen(45, 9, "마일리지로 경품을 교환하세요!");

		
		if (shop.select == 1) PrintScreen(11, 12, "▶"); else PrintScreen(11, 12, "▷");
		PrintScreen(13, 12, "1회 뽑기 :  200원");

		if (shop.select == 2) PrintScreen(46, 12, "▶"); else PrintScreen(46, 12, "▷");
		PrintScreen(48, 12, "5회 뽑기 : 1000원");

		if (shop.select == 3) PrintScreen(11, 15, "▶"); else PrintScreen(11, 15, "▷");
		PrintScreen(13, 15, "상점에서 나갑니다");

		if (shop.select == 4) SetColor(VIOLET); else SetColor(D_VIOLET);
		FilePrintStr("rankS.txt",7,18);
	
		if (shop.select == 5) SetColor(GREEN); else SetColor(D_GREEN);
		FilePrintStr("rankA.txt",42,18);
	
		if (shop.select == 6) SetColor(SKYBLUE); else SetColor(D_SKYBLUE);
		FilePrintStr("rankB.txt",7,24);
	
		if (shop.select == 7) SetColor(WHITE); else SetColor(GRAY);
		FilePrintStr("rankC.txt",42,24);
	}

}

void FilePrintStr(char *input_str, int x, int y)
{
	char str[100];
	FILE* fp = fopen(input_str, "rt");
	if (fp == NULL) return;
	int i = 0;
	while (1)
	{
		char* pstr = fgets(str, 100, fp);
		if (pstr == NULL)
		{
			break;
		}
		PrintScreen(x, y + i, str);
		i++;
	}
	fclose(fp);
}

void PlayerControl()
{
	if (player.dead == FALSE && player.shop == FALSE)
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
	for (int i = 0; i < WIDTH; i++) PrintScreen(ui.position.x, ui.position.y + i, "┃");
	for (int i = 1; i < HEIGHT; i++)
	{
		PrintScreen(ui.position.x + i, 9, "━");
		PrintScreen(ui.position.x + i, 13, "━");
		PrintScreen(ui.position.x + i, 16, "━");
	}

	sprintf(string, "x : %d / y : %d", player.collide.x, player.collide.y);
	PrintScreen(83, 1, string);
	sprintf(string, "보유 돈 : %d원", ui.Money);
	PrintScreen(83, 2, string);
	sprintf(string, "확인용 스테이지넘버: %d", stage_number);
	PrintScreen(83, 3, string);

	sprintf(string, "%s\t%s", ui.Player_Name, ui.Player_HPbar);
	PrintScreen(83, 4, string);
	sprintf(string, "HP:%.1lf / ATT:%.1lf\t", ui.MyHP, ui.MyAtt);
	PrintScreen(83, 5, string);
	sprintf(string, "%s\t%s", enemy_target->name, ui.Enemy_HPbar);
	PrintScreen(83, 6, string);
	sprintf(string, "HP:%.1lf / ATT:%.1lf\t", ui.EnemyHP, ui.EnemyAtt);
	PrintScreen(83, 7, string);

	if (player.shop == TRUE)	// 무기 상점 안에서의 인터페이스
	{
		if (shop.select == 4)
		{
			PrintScreen(83, 14, "등급S : 5%");
			PrintScreen(83, 15, "확실히 특별한 능력이 있습니다!");
		}
		else if (shop.select == 5)
		{
			PrintScreen(83, 14, "등급A : 15%");
			PrintScreen(83, 15, "쪼금 특별한 능력이 있습니다.");
		}
		else if (shop.select == 6)
		{
			PrintScreen(83, 14, "등급B : 30%");
			PrintScreen(83, 15, "C 무기보다는 살짝 좋습니다.");
		}
		else if (shop.select == 7)
		{
			PrintScreen(83, 14, "등급C : 50%");
			PrintScreen(83, 15, "지극히 평범한 무기입니다.");
		}
		else
		{
			PrintScreen(83, 14, "방향키로 이동, 엔터로 선택");
			PrintScreen(83, 15, "아래서 확률확인 가능");
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

	if (player.dead == TRUE)
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