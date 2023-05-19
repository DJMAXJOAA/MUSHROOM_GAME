#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#include "player.h"
#include "Screen.h"


void Init();						// �ʱ�ȭ(�ʱ� ����)
void Update();						// ������ ����
void Render();						// ȭ�� ���
void WaitRender(clock_t OldTime);	// ȭ�� �����ð�
void Release();						// �Ҵ� ����
int Timer(int SetTime, char string);
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
	ui.timer = 0;
	ui.second = 0;

	enemy.position.x = 60;
	enemy.position.y = 20;
	enemy.att = 10;
	enemy.hp = 30;
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

	ScreenPrint(player.position.x, player.position.y, player.strPlayer1);
	ScreenPrint(player.position.x, player.position.y+1, player.strPlayer2);
	ScreenPrint(player.position.x, player.position.y+2, player.strPlayer3);

	ScreenPrint(enemy.position.x, enemy.position.y, "��");

	sprintf(string, "���ΰ� �̵� ��ǥ : %d, %d", player.position.x, player.position.y);
	ScreenPrint(85, 1, string);

	sprintf(string, "���� ���ɻ��� : %d", player.isReady);
	ScreenPrint(85, 2, string);
	
	sprintf(string, "ü�� : %d", ui.MyHP);
	ScreenPrint(85, 4, string);

	sprintf(string, "���ݷ� : %d", ui.MyAtt);
	ScreenPrint(85, 5, string);

	if (player.isReady == NOW_ATTACKING) 
	{
		sprintf(string, "���� ä�� �ð� : %d��", ui.second);
		ScreenPrint(85, 6, string);
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
				ui.timer += 1;
				if (ui.timer > 33)
				{
					ui.second -= 1;
					ui.timer = 0;
				}
			}
			break;
		}		
	}
}

void Release()	//����
{

}

int Timer(int SetTime, char string)
{
	int EndTime = (unsigned)time(NULL);
	EndTime += 3;

	while (1)
	{
		int StartTime = (unsigned)time(NULL);
		sprintf("���� ä�� �ð� : %d��\n", EndTime - StartTime);
		ScreenPrint(85, 6, string);
		if (EndTime - StartTime == 0)
		{
			return 0;
		}
	}
}

int GetKeyEvent()
{
	if (_kbhit())	//_kbhit : Ű���尡 �������� Ȯ���ϴ� �Լ�
		return _getch();	//���� ���� ��ȯ

	return -1;
}
