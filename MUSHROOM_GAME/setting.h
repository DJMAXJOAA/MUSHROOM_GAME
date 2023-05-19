#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#include "Screen.h"
#include "player.h"


enum
{
	BLACK, D_BLACK, D_GREEN, D_SKYBLUE, D_RED, D_VIOLET, D_YELLOW, 
	GRAY, D_GRAY, BLUE, GREEN, SKYBLUE, RED, VIOLET, YELLOW, WHITE
};

void Init();						// �ʱ�ȭ(�ʱ� ����)
void Update();						// ������ ����
void Render();						// ȭ�� ���
void WaitRender(clock_t OldTime);	// ȭ�� �����ð�
void Release();						// �Ҵ� ����
int GetKeyEvent();					// Ű �Է¹ޱ�



void Init()
{
	player.position.x = 0;
	player.position.y = 22;
	player.isReady = 0;
	player.nLength = strlen(PLAYER_STR1);
	player.strPlayer1 = (char*)malloc(sizeof(char) * player.nLength);
	strcpy(player.strPlayer1, PLAYER_STR1);
	player.strPlayer2 = (char*)malloc(sizeof(char) * player.nLength);
	strcpy(player.strPlayer2, PLAYER_STR2);
	player.strPlayer3 = (char*)malloc(sizeof(char) * player.nLength);
	strcpy(player.strPlayer3, PLAYER_STR3);

	ui.position.x = 82;
	ui.position.y = 0;
	ui.MyAtt = 10;
	ui.MyHP = 100;
	ui.EnemyAtt = 0;
	ui.EnemyHP = 0;
	ui.timer = 0;
	ui.second = 0;

	enemy.position.x = 60;
	enemy.position.y = 20;
	enemy.att = 10;
	enemy.hp = 30;
	enemy.dead = FALSE;
}

void Update()
{

}

void Render()
{
	ScreenClear();
	/*������������������������������������������������������������������������������������������������������������������������������������������*/

	char string[100] = { 0 };

	for (int i = 0; i < 40; i++) ScreenPrint(ui.position.x, ui.position.y + i, "��");
	for (int i = 1; i < 38; i++) ScreenPrint(ui.position.x + i, 10, "��");

	if (player.isReady == NOW_ATTACKING) SetColor(D_RED);
	ScreenPrint(player.position.x, player.position.y, player.strPlayer1);
	ScreenPrint(player.position.x, player.position.y+1, player.strPlayer2);
	ScreenPrint(player.position.x, player.position.y+2, player.strPlayer3);

	SetColor(D_RED);
	if (enemy.dead == FALSE) ScreenPrint(enemy.position.x, enemy.position.y, "��");
	SetColor(WHITE);

	sprintf(string, "�̵� ��ǥ : %d, %d", player.position.x, player.position.y);
	ScreenPrint(85, 1, string);
	sprintf(string, "���� ���ɻ��� : %d", player.isReady);
	ScreenPrint(85, 2, string);
	
	sprintf(string, "�� ü�� : %d", ui.MyHP);
	ScreenPrint(85, 4, string);
	sprintf(string, "�� ���ݷ� : %d", ui.MyAtt);
	ScreenPrint(85, 5, string);
	sprintf(string, "�� ü�� : %d", ui.EnemyHP);
	ScreenPrint(85, 6, string);
	sprintf(string, "�� ���ݷ� : %d", ui.EnemyAtt);
	ScreenPrint(85, 7, string);

	if (player.isReady == NOW_ATTACKING) 
	{
		sprintf(string, "���� ä�� �ð� : %.1lf��", ui.second);
		ScreenPrint(85, 9, string);
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
