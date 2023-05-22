#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define CLOCK 20	// 프레임당 밀리초
#define WORD_SPEED 30
#include "all_include.h"
#include "Screen.h"
#include "player.h"

const double fps = CLOCK / (double)1000;
static char string[100] = { 0 };

enum
{
	BLACK, D_BLACK, D_GREEN, D_SKYBLUE, D_RED, D_VIOLET, D_YELLOW,
	GRAY, D_GRAY, BLUE, GREEN, SKYBLUE, RED, VIOLET, YELLOW, WHITE
};

/* 초기화 관련 */
void ConstInit();					// 딱 처음 한번만 초기화(변하지 말아야 할것들)
void Init();						// 죽었을때 초기화(초기 설정, 변하지 않는 것들)
void StageInit(int stage_number);	// 맵별 초기화(맵별로 다름. 몇번맵?)

/* 실제 동작부 */
void Render();						// 화면 출력
void PlayerControl();			// 1. 플레이어 관련 함수
void TotalUI();					// 2. UI 관련 함수
void PlayerDead();				// 죽었을때 살리고 초기화시킴

/* 화면 관련 */
void WaitRender(clock_t OldTime);	// 화면 지연시간
void Release();						// 할당 해제(프로그램 종료)
int GetKeyEvent();					// 키 입력받기(인벤창, 종료, 리셋 등)

/* 맵 생성 관련 */
void MapInit(int(*map)[HEIGHT]);	// 맵 배열 생성(벽, 장애물, 포탈, NPC 등등 생성)
void MapObject();					// 맵 뒷배경 (사실상 씬)
void FilePrintStr(char *input_str, int x, int y);	// 파일 입출력


void ConstInit()
{
	ui.Money = 0;
	ui.MyAtt = 10;
	ui.MyMaxHP = 100;
	ui.MyHP = 100;
	strcpy(ui.Player_Name, "호옹이");

	ui.position.x = 80;
	ui.position.y = 0;
}

void Init()
{
	player.nLength = strlen(PLAYER_STR1);
	player.strPlayer1 = (char*)malloc(sizeof(char) * player.nLength);
	strcpy(player.strPlayer1, PLAYER_STR1);
	player.strPlayer2 = (char*)malloc(sizeof(char) * player.nLength);
	strcpy(player.strPlayer2, PLAYER_STR2);
	player.strPlayer3 = (char*)malloc(sizeof(char) * player.nLength);
	strcpy(player.strPlayer3, PLAYER_STR3);


	player.isReady = CANT_ATTACK;
	player.dead = FALSE;
	player.shop = FALSE;
	ui.MyHP = ui.MyMaxHP;
	init_missile.x = 0;
	init_missile.y = 0;
	init_missile.speed = 0;
	init_missile.interval = 0;
	init_missile.extinct = FALSE;

	enemy.att = 0;
	enemy.maxhp = 0;
	enemy.hp = 0;
	enemy.dead = FALSE;
	enemy.money = 0;
	strcpy(enemy.name, "TARGET");
	strcpy(ui.Enemy_HPbar, "□□□□□□□□□□");

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

	
	
	ui.EnemyAtt = 0;
	ui.EnemyHP = 0;
	ui.second = 0;
	InitUI();
}

void StageInit(int stage_number)
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

		player.shop = TRUE;

		break;

	}
}

void PlayerDead()
{
	if (ui.MyHP <= 0 && player.dead == FALSE)
	{
		ui.MyHP = 0;
		player.dead = TRUE;
		ui.respawn += RESPAWN_TIME;
	}
	if (ui.respawn <= 0 && player.dead == TRUE)
	{
		SetColor(WHITE);
		stage_number = 1;
		Init();
		StageInit(stage_number);
	}
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
			if (map[y][x] == WALL) ScreenPrint(x * 2, y, "■");
			if (map[y][x] == OBSTACLE) { SetColor(D_RED); ScreenPrint(x * 2, y, "★"); SetColor(WHITE); }

			if (map[y][x] == PORTAL1)
			{ 
				portal1.position.x = x * 2;
				portal1.position.y = y;
				SetColor(BLUE); ScreenPrint(x * 2, y, "▩"); SetColor(WHITE);
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
				SetColor(BLUE); ScreenPrint(x * 2, y, "▩"); SetColor(WHITE);
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
					ScreenPrint(enemy1.position.x, enemy1.position.y, "♣");
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
					ScreenPrint(enemy2.position.x, enemy2.position.y, "♣");
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
		ScreenPrint(58, 22, "무기 랜덤 뽑기");
		ScreenPrint(9, 22, "경품 교환소");
		SetColor(GRAY);
		FilePrintStr("house2.txt", 54, 23);
		FilePrintStr("house3.txt", 1, 23);
		SetColor(WHITE);

		FilePrintStr("road.txt", 1, 16);

		
		SetColor(GRAY);
		FilePrintStr("house.txt", 1, 1);
		SetColor(WHITE);

		ScreenPrint(33, 9, "쉼터");
		for (int i = 0; i < 7; i++)
		{
			ScreenPrint(37, 21+i, "|");
			ScreenPrint(45, 21+i, "|");
		}
		ScreenPrint(46, 27, "--------");
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
				if (map2[y][x] == EMPTY) ScreenPrint(x * 2, y, "　");
			}
		}
	}

	if (stage_number == 3)
	{
		SetColor(D_GRAY);
		FilePrintStr("background_pattern.txt", 1, 1);
		FilePrintStr("background_pattern.txt", 1, 16);
		SetColor(WHITE);

		FilePrintStr("shop_border.txt", 4, 2);
		
		SetColor(YELLOW);
		ScreenPrint(28, 4, "※※ 무기 랜덤 뽑기 ※※");
		ScreenPrint(26, 5, "S등급 무기에 도전해 보세요!!");
		SetColor(WHITE);
		
		ScreenPrint(38, 8, "5회 뽑기시 마일리지 1개 추가 지급");

		/*
		ScreenPrint(8, 11, "S랭크 : 공격력 30, 크리티컬 데미지 x1.5->2.0, 공격 판정 증가");
		ScreenPrint(8, 12, "A랭크 : 공격력 25, 크리티컬 데미지 x1.5->x1.75");
		ScreenPrint(8, 13, "B랭크 : 공격력 20");
		ScreenPrint(8, 14, "C랭크 : 공격력 10");
		*/

		ScreenPrint(13, 12, "1회 뽑기 :  200원");
		ScreenPrint(48, 12, "5회 뽑기 : 1000원");
		ScreenPrint(13, 15, "상점에서 나갑니다");

		SetColor(VIOLET);
		FilePrintStr("rankS.txt",7,18);
		SetColor(BLUE);
		FilePrintStr("rankA.txt",42,18);
		SetColor(SKYBLUE);
		FilePrintStr("rankB.txt",7,24);
		SetColor(WHITE);
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
		ScreenPrint(x, y + i, str);
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
			ui.Danger = TRUE;
		}
		else ui.Danger = FALSE;
		ScreenPrint(player.position.x, player.position.y, player.strPlayer1);
		ScreenPrint(player.position.x, player.position.y + 1, player.strPlayer2);
		ScreenPrint(player.position.x, player.position.y + 2, player.strPlayer3);
		SetColor(WHITE);
	}

	/* 미사일 인터페이스 */
	ScreenPrint(97, 10, "┏━━━━━┓ ");
	SetColor(YELLOW);
	if (player.isReady == NOW_ATTACKING) ScreenPrint(100, 11, "☆");
	else ScreenPrint(98, 11, "【☆】");
	SetColor(WHITE);
	ScreenPrint(97, 12, "┗━━━━━┛ ");

	if (player.isReady == NOW_ATTACKING)
	{
		SetColor(YELLOW);
		if (missile1.extinct == FALSE) ScreenPrint(missile1.x, missile1.y, "★");
		if (missile1.interval <= 0 && missile2.extinct == FALSE) ScreenPrint(missile2.x, missile2.y, "★");
		if (missile2.interval <= 0 && missile3.extinct == FALSE) ScreenPrint(missile3.x, missile3.y, "★");
		SetColor(WHITE);
	}
}

void TotalUI()
{
	for (int i = 0; i < WIDTH; i++) ScreenPrint(ui.position.x, ui.position.y + i, "┃");
	for (int i = 1; i < HEIGHT; i++)
	{
		ScreenPrint(ui.position.x + i, 9, "━");
		ScreenPrint(ui.position.x + i, 13, "━");
		ScreenPrint(ui.position.x + i, 16, "━");
	}

	sprintf(string, "x : %d / y : %d", player.collide.x, player.collide.y);
	ScreenPrint(83, 1, string);
	sprintf(string, "보유 돈 : %d원", ui.Money);
	ScreenPrint(83, 2, string);

	sprintf(string, "%s\t%s", ui.Player_Name, ui.Player_HPbar);
	ScreenPrint(83, 4, string);
	sprintf(string, "HP:%.1lf / ATT:%.1lf\t", ui.MyHP, ui.MyAtt);
	ScreenPrint(83, 5, string);
	sprintf(string, "%s\t%s", enemy_target->name, ui.Enemy_HPbar);
	ScreenPrint(83, 6, string);
	sprintf(string, "HP:%.1lf / ATT:%.1lf\t", ui.EnemyHP, ui.EnemyAtt);
	ScreenPrint(83, 7, string);

	if (ui.Danger == TRUE)
	{
		ScreenPrint(83, 14, "장애물에 닿고 있어요. 조심하세요!");
	}
	else if (ui.CollideEnemy == TRUE)
	{
		ScreenPrint(83, 14, enemy_target->name);
		ScreenPrint(83, 15, enemy_target->info);
	}
	else if (ui.Notice == TRUE)
	{
		sprintf(string, "적을 잡고 %d원을 얻었습니다!", ui.temp_money);
		ScreenPrint(83, 14, string);
	}
	else if (ui.Critical >= 1)
	{
		sprintf(string, "크리티컬!! %d COMBO", ui.Critical);
		ScreenPrint(83, 14, string);
		sprintf(string, "%.lf데미지를 주었습니다!", ui.MyAtt * 1.5);
		ScreenPrint(83, 15, string);
	}
	else if (ui.HitEnemy == TRUE)
	{
		sprintf(string, "공격 성공! %.lf데미지를 주었습니다!", ui.MyAtt);
		ScreenPrint(83, 14, string);
	}
	else if (ui.Damaged == TRUE)
	{
		sprintf(string, "아이고! %.lf데미지를 받았습니다 ㅜㅜ", enemy_target->att);
		ScreenPrint(83, 14, string);
	}
	else
	{
		ScreenPrint(83, 14, "A키  공격시작");
		ScreenPrint(83, 15, "타이밍 맞춰서 F키 공격(크리티컬 x1.5)");
	}

	if (player.dead == TRUE)
	{
		ScreenPrint(83, 29, "당신은 죽었습니다! 곧 부활합니다");
		sprintf(string, "남은 리스폰 시간 : %.1lf초", ui.respawn);
		ScreenPrint(83, 30, string);
	}
	else if (ui.MyHP / ui.MyMaxHP <= 0.25)
	{
		ScreenPrint(83, 29, "체력이 낮습니다.");
		ScreenPrint(83, 30, "체력을 회복하세요!!");
	}
}

/*
 ____________________________
|  ___//\\___________//\\__  |
| |                        | |
| |   )xxxxx[;;;;;;;;;>    | |
| |________________________S_|
|____________________________|
*/

/*
 ____________________________
|  __/\_______/\_______/\__  |
| |                        | |
| |    []++++||=======>    | |
| |________________________A_|
|____________________________|
*/

/*
 ____________________________
|  ___________/\___________  |
| |                        | |
| |     =={==========-     | |
| |________________________B_|
|____________________________|
*/

/*
 ____________________________
|  ________________________  |
| |                        | |
| |      ====K-------      | |
| |________________________C_|
|____________________________|
*/