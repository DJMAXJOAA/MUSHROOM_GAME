#pragma once
#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include "UI.h"

#define CANT_ATTACK 0
#define CAN_ATTACK 1
#define NOW_ATTACKING 2

char PLAYER_STR1[] = "����";	// �÷��̾��� �����
char PLAYER_STR2[] = "���ࢺ";	// �÷��̾��� �����
char PLAYER_STR3[] = "����";	// �÷��̾��� �����

typedef struct Player
{
	Position position;
	char* strPlayer1;	// ĳ���͸� ������ ����(���� �Ҵ�)
	char* strPlayer2;
	char* strPlayer3;
	int isReady;
	int nLength;	    // ĳ������ ����
}Player;

Player player;
char* change;



void PlayerMove();
void CanAttack();

void PlayerMove()
{
	if (player.isReady == NOW_ATTACKING)
	{
		sprintf(player.strPlayer1, "����");
		sprintf(player.strPlayer2, "���ࢺ");
		sprintf(player.strPlayer3, "����");
	}
	else
	{
		if (GetAsyncKeyState(VK_LEFT) & 0x8000 && player.position.x > 0) { //����
			player.position.x--;
			player.position.x--;
			sprintf(player.strPlayer1, "����");
			sprintf(player.strPlayer2, "���ࢺ");
			sprintf(player.strPlayer3, "����");
		}

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && player.position.x < 75) { //������
			player.position.x++;
			player.position.x++;
			sprintf(player.strPlayer1, "����");
			sprintf(player.strPlayer2, "���ࢹ");
			sprintf(player.strPlayer3, "����");
		}

		if (GetAsyncKeyState(VK_UP) & 0x8000 && player.position.y > 0) { //��
			player.position.y--;
			sprintf(player.strPlayer1, "����");
			sprintf(player.strPlayer2, "���ࢺ");
			sprintf(player.strPlayer3, "����");
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000 && player.position.y < 37) { //�Ʒ�
			player.position.y++;
			sprintf(player.strPlayer1, "����");
			sprintf(player.strPlayer2, "���ࢺ");
			sprintf(player.strPlayer3, "����");
		}
	}

}

void CanAttack()
{
	int collide_x = player.position.x + 2;
	int collide_y = player.position.y + 1;

	if (player.isReady == CANT_ATTACK)
	{
		if (collide_x == enemy.position.x && collide_y == enemy.position.y) player.isReady = CAN_ATTACK;
	}
	if (player.isReady == CAN_ATTACK)
	{
		if (collide_x != enemy.position.x || collide_y != enemy.position.y) player.isReady = CANT_ATTACK;
	}
	if (player.isReady == CAN_ATTACK && GetAsyncKeyState(0x41) & 0x8000)
	{
		player.isReady = NOW_ATTACKING;
		ui.second = 3;
	}
	if (ui.second <= 0)
	{
		ui.second = 0;
		ui.timer = 0;
		player.isReady = CANT_ATTACK;
	}
	
}