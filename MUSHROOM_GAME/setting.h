#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define CLOCK 15	// 프레임당 밀리초
#include "all_include.h"
#include "Screen.h"
#include "player.h"

const double fps = CLOCK / (double)1000;
int stage_number = 1;

enum
{
	BLACK, D_BLACK, D_GREEN, D_SKYBLUE, D_RED, D_VIOLET, D_YELLOW,
	GRAY, D_GRAY, BLUE, GREEN, SKYBLUE, RED, VIOLET, YELLOW, WHITE
};

void Init();						// 초기화(초기 설정, 변하지 않는 것들)
void StageInit(int stage_number);	// 초기화(맵별로 다름. 몇번맵?)
void Update();						// 데이터 갱신
void Render();						// 화면 출력
void WaitRender(clock_t OldTime);	// 화면 지연시간
void Release();						// 할당 해제
int GetKeyEvent();					// 키 입력받기
void MapInit(int(*map)[HEIGHT]);	// 맵 그리기

void Init()
{
	player.nLength = strlen(PLAYER_STR1);
	player.strPlayer1 = (char*)malloc(sizeof(char) * player.nLength);
	strcpy(player.strPlayer1, PLAYER_STR1);
	player.strPlayer2 = (char*)malloc(sizeof(char) * player.nLength);
	strcpy(player.strPlayer2, PLAYER_STR2);
	player.strPlayer3 = (char*)malloc(sizeof(char) * player.nLength);
	strcpy(player.strPlayer3, PLAYER_STR3);

	player.position.x = 36;
	player.position.y = 14;
	player.isReady = CANT_ATTACK;
	player.dead = FALSE;

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

	ui.position.x = 81;
	ui.position.y = 0;
	ui.Money = 0;
	ui.MyAtt = 10;
	ui.MyHP = 100;
	ui.EnemyAtt = 0;
	ui.EnemyHP = 0;
	ui.second = 0;
	InitUI();
}

void StageInit(int stage_number)
{
	switch (stage_number)
	{
	case 1:
		map_pointer = map1;
		enemy_target = &enemy;
		enemy1.att = 10;
		enemy1.hp = 100;
		enemy1.dead = FALSE;
		enemy1.money = 100;
		strcpy(enemy1.name, "작은버섯");
		strcpy(enemy1.info, "간단하게 캘 수 있다");

		enemy2.att = 15;
		enemy2.hp = 150;
		enemy2.dead = FALSE;
		enemy2.money = 150;
		strcpy(enemy2.name, "중간버섯");
		strcpy(enemy2.info, "살짝 캐기 버겁다");
		break;

	case 2:
		map_pointer = map2;
		enemy_target = &enemy;
		enemy1.att = 10;
		enemy1.hp = 100;
		enemy1.dead = FALSE;
		enemy1.money = 100;
		strcpy(enemy1.name, "작은버섯");
		strcpy(enemy1.info, "간단하게 캘 수 있다");

		enemy2.att = 15;
		enemy2.hp = 150;
		enemy2.dead = FALSE;
		enemy2.money = 150;
		strcpy(enemy2.name, "중간버섯");
		strcpy(enemy2.info, "살짝 캐기 버겁다");
		break;
	}
}

void Update()
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
		Init();
		StageInit(1);
	}
}

void Render()
{
	ScreenClear();
	/*─────────────────────────────────────────────────────────────────────*/

	char string[100] = { 0 };

	

	if (player.dead == FALSE)
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

	/* 맵 불러오기 */
	MapInit(map_pointer);

	/* 미사일 인터페이스 */
	ScreenPrint(97, 10, "┏━━━━━┓ ");
	SetColor(YELLOW);
	ScreenPrint(100, 11, "☆"); // 100, 11 별 좌표
	SetColor(WHITE);
	ScreenPrint(97, 12, "┗━━━━━┛ ");

	if (player.isReady == NOW_ATTACKING)
	{
		SetColor(YELLOW);
		if (missile1.extinct == FALSE) ScreenPrint(missile1.x, missile1.y, "★");
		if(missile1.interval <= 0 && missile2.extinct == FALSE) ScreenPrint(missile2.x, missile2.y, "★");
		if(missile2.interval <= 0 && missile3.extinct == FALSE) ScreenPrint(missile3.x, missile3.y, "★");
		SetColor(WHITE);
	}

	



	/* UI 상태창 셋팅 */
	for (int i = 0; i < WIDTH; i++) ScreenPrint(ui.position.x, ui.position.y + i, "┃");
	for (int i = 1; i < HEIGHT; i++) {
		ScreenPrint(ui.position.x + i, 9, "━");
		ScreenPrint(ui.position.x + i, 13, "━");
		ScreenPrint(ui.position.x + i, 16, "━");
	}

	sprintf(string, "이동 좌표 : %d, %d", player.collide.x, player.collide.y);
	ScreenPrint(83, 1, string);
	sprintf(string, "보유 돈 : %d원", ui.Money);
	ScreenPrint(83, 2, string);
	sprintf(string, "확인용 : %d", ui.CollideEnemy);
	ScreenPrint(83, 3, string);

	sprintf(string, "내 체력\t%.1lf", ui.MyHP);
	ScreenPrint(83, 4, string);
	sprintf(string, "내 공격력\t%.1lf", ui.MyAtt);
	ScreenPrint(83, 5, string);
	sprintf(string, "적 체력\t%.1lf", ui.EnemyHP);
	ScreenPrint(83, 6, string);
	sprintf(string, "적 공격력\t%.1lf", ui.EnemyAtt);
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
		sprintf(string, "연속 %d번째 크리티컬!!", ui.Critical);
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
		ScreenPrint(83, 14, "버섯 위에서 A키  공격시작");
		ScreenPrint(83, 15, "타이밍 맞춰서 F키 공격(크리티컬 1.5x)");
	}


	if (player.dead == TRUE)
	{
		ScreenPrint(83, 29, "당신은 죽었습니다! 곧 부활합니다");
		sprintf(string, "남은 리스폰 시간 : %.1lf초", ui.respawn);
		ScreenPrint(83, 30, string);
	}

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
			if (map[y][x] == PORTAL) 
			{ 

				SetColor(BLUE); ScreenPrint(x * 2, y, "▩"); SetColor(WHITE);
				if (player.collide.x == enemy1.position.x && player.collide.y == enemy1.position.y) EnemyTargetChange(&enemy1);
			}
			if (map[y][x] == OBSTACLE) { SetColor(D_RED); ScreenPrint(x * 2, y, "★"); SetColor(WHITE); }
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