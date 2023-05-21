#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "all_include.h"
#include "Screen.h"
#include "player.h"


enum
{
	BLACK, D_BLACK, D_GREEN, D_SKYBLUE, D_RED, D_VIOLET, D_YELLOW,
	GRAY, D_GRAY, BLUE, GREEN, SKYBLUE, RED, VIOLET, YELLOW, WHITE
};

int check = 0;

void Init();						// �ʱ�ȭ(�ʱ� ����)
void Update();						// ������ ����
void Render();						// ȭ�� ���
void WaitRender(clock_t OldTime);	// ȭ�� �����ð�
void Release();						// �Ҵ� ����
int GetKeyEvent();					// Ű �Է¹ޱ�

void Init()
{
	player.nLength = strlen(PLAYER_STR1);
	player.strPlayer1 = (char*)malloc(sizeof(char) * player.nLength);
	strcpy(player.strPlayer1, PLAYER_STR1);
	player.strPlayer2 = (char*)malloc(sizeof(char) * player.nLength);
	strcpy(player.strPlayer2, PLAYER_STR2);
	player.strPlayer3 = (char*)malloc(sizeof(char) * player.nLength);
	strcpy(player.strPlayer3, PLAYER_STR3);

	player.position.x = 4;
	player.position.y = 15;
	player.isReady = CANT_ATTACK;
	player.dead = FALSE;

	ui.position.x = 80;
	ui.position.y = 0;
	ui.Money = 0;
	ui.MyAtt = 10;
	ui.MyHP = 100;
	ui.EnemyAtt = 0;
	ui.EnemyHP = 0;
	ui.timer = 0;
	ui.second = 0;

	enemy1.att = 10;
	enemy1.hp = 30;
	enemy1.dead = FALSE;
	enemy1.money = 100;

	enemy2.att = 15;
	enemy2.hp = 25;
	enemy2.dead = FALSE;
	enemy2.money = 150;
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
	}
}

void Render()
{
	ScreenClear();
	/*������������������������������������������������������������������������������������������������������������������������������������������*/

	char string[100] = { 0 };

	for (int i = 0; i < WIDTH; i++) ScreenPrint(ui.position.x, ui.position.y + i, "��");
	for (int i = 1; i < HEIGHT; i++) { 
		ScreenPrint(ui.position.x + i, 9, "��"); 
		ScreenPrint(ui.position.x + i, 11, " "); 
		ScreenPrint(ui.position.x + i, 13, "��"); }

	if (player.dead == FALSE)
	{
		if (player.isReady == NOW_ATTACKING) SetColor(D_GREEN);
		if (ObstacleCheck()) {
			SetColor(D_RED);
			ui.MyHP -= OBSTACLE_DAMAGE;
		}
		ScreenPrint(player.position.x, player.position.y, player.strPlayer1);
		ScreenPrint(player.position.x, player.position.y + 1, player.strPlayer2);
		ScreenPrint(player.position.x, player.position.y + 2, player.strPlayer3);
		SetColor(WHITE);
	}

	for (int y = 0; y < WIDTH; y++)
		for (int x = 0; x < HEIGHT; x++)
		{
			if (map[y][x] == WALL) ScreenPrint(x * 2, y, "��");
			if (map[y][x] == PORTAL) { SetColor(BLUE); ScreenPrint(x * 2, y, "��"); SetColor(WHITE);}
			if (map[y][x] == OBSTACLE) { SetColor(D_RED); ScreenPrint(x * 2, y, "��"); SetColor(WHITE);	}
			if (map[y][x] == ENEMY1)
			{
				SetColor(D_GREEN);
				if (enemy1.dead == FALSE)
				{
					enemy1.position.x = x * 2;
					enemy1.position.y = y;
					ScreenPrint(enemy1.position.x, enemy1.position.y, "��");
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
					ScreenPrint(enemy2.position.x, enemy2.position.y, "��");
					if (player.collide.x == enemy2.position.x && player.collide.y == enemy2.position.y) EnemyTargetChange(&enemy2);	
				}
				SetColor(WHITE);
			}
		}

	sprintf(string, "�̵� ��ǥ : %d, %d", player.collide.x, player.collide.y);
	ScreenPrint(83, 1, string);
	sprintf(string, "���� ���� ���� : %d", player.isReady);
	ScreenPrint(83, 2, string);
	sprintf(string, "�� : %d", ui.Money);
	ScreenPrint(83, 3, string);

	sprintf(string, "�� ü�� : %d", ui.MyHP);
	ScreenPrint(83, 4, string);
	sprintf(string, "�� ���ݷ� : %d", ui.MyAtt);
	ScreenPrint(83, 5, string);
	sprintf(string, "�� ü�� : %d", ui.EnemyHP);
	ScreenPrint(83, 6, string);
	sprintf(string, "�� ���ݷ� : %d", ui.EnemyAtt);
	ScreenPrint(83, 7, string);

	if (player.isReady == NOW_ATTACKING)
	{
		sprintf(string, "���� ä�� �ð� : %.1lf��", ui.second);
		ScreenPrint(85, 11, string);
	}

	if (player.dead == TRUE)
	{
		sprintf(string, "����� �׾����ϴ�! �� ��Ȱ�մϴ�");
		ScreenPrint(83, 29, string);
		sprintf(string, "���� ������ �ð� : %.1lf��", ui.respawn);
		ScreenPrint(83, 30, string);
	}

	/*������������������������������������������������������������������������������������������������������������������������������������������*/
	ScreenFlipping();
}

void WaitRender(clock_t OldTime)
{
	clock_t CurTime;	//clock_t ����ð� ����
	while (1)
	{
		CurTime = clock();
		if (CurTime - OldTime > 33)
		{
			if (player.isReady == NOW_ATTACKING)
			{
				ui.second -= 0.03;
			}
			if (player.dead == TRUE)
			{
				ui.respawn -= 0.03;
			}
			break;
		}
	}
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
