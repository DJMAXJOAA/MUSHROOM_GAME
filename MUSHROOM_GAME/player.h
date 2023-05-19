#pragma once
#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include "UI.h"

#define CANT_ATTACK 0
#define CAN_ATTACK 1
#define NOW_ATTACKING 2
#define ATTACK_COOLDOWN 1

char PLAYER_STR1[] = "■▲■";		
char PLAYER_STR2[] = "◀□▶";
char PLAYER_STR3[] = "■▼■";		// 플레이어의 생김새

typedef struct Player
{
	Position position;
	char* strPlayer1;	// 캐릭터를 포인터 설정(동적 할당)
	char* strPlayer2;
	char* strPlayer3;
	int isReady;
	int nLength;	    // 캐릭터의 길이
}Player;

Player player;
char* change;

void PlayerMove();
void PlayerAttack();

void PlayerMove()
{
	if (player.isReady == NOW_ATTACKING)
	{ }
	else
	{
		if (GetAsyncKeyState(VK_LEFT) & 0x8000 && player.position.x > 0) { //왼쪽
			player.position.x--;
			player.position.x--;
			sprintf(player.strPlayer1, "■▲■");
			sprintf(player.strPlayer2, "◁□▶");
			sprintf(player.strPlayer3, "■▼■");
		}

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && player.position.x < 75) { //오른쪽
			player.position.x++;
			player.position.x++;
			sprintf(player.strPlayer1, "■▲■");
			sprintf(player.strPlayer2, "◀□▷");
			sprintf(player.strPlayer3, "■▼■");
		}

		if (GetAsyncKeyState(VK_UP) & 0x8000 && player.position.y > 0) { //위
			player.position.y--;
			sprintf(player.strPlayer1, "■△■");
			sprintf(player.strPlayer2, "◀□▶");
			sprintf(player.strPlayer3, "■▼■");
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000 && player.position.y < 37) { //아래
			player.position.y++;
			sprintf(player.strPlayer1, "■▲■");
			sprintf(player.strPlayer2, "◀□▶");
			sprintf(player.strPlayer3, "■▽■");
		}
	}

}

void PlayerAttack()
{
	int collide_x = player.position.x + 2;
	int collide_y = player.position.y + 1;

	if (player.isReady == CANT_ATTACK)
	{
		if (enemy.dead == FALSE && collide_x == enemy.position.x && collide_y == enemy.position.y)
		{
			player.isReady = CAN_ATTACK;
		}
	}
	if (player.isReady == CAN_ATTACK)
	{
		ui.EnemyHP = enemy.hp;
		ui.EnemyAtt = enemy.att;
		if (collide_x != enemy.position.x || collide_y != enemy.position.y) player.isReady = CANT_ATTACK;
	}
	if (player.isReady == CAN_ATTACK && GetAsyncKeyState(0x41) & 0x8000)
	{
		player.isReady = NOW_ATTACKING;
		ui.second = ATTACK_COOLDOWN;
	}
	if (player.isReady == NOW_ATTACKING && ui.second <= 0)
	{
		if (ui.MyAtt >= enemy.hp)
		{
			ui.MyHP -= enemy.att;
			enemy.hp = 0;
			ui.EnemyHP = 0;
			ui.EnemyAtt = 0;
			enemy.dead = TRUE;
			player.isReady = CANT_ATTACK;
		}
		else
		{
			ui.MyHP -= enemy.att;
			enemy.hp -= ui.MyAtt;
			player.isReady = CAN_ATTACK;
		}

		ui.second = 0;
		ui.timer = 0;
	}
}