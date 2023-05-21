#pragma once
#include "all_include.h"
#include "UI.h"


#define CANT_ATTACK 0
#define CAN_ATTACK 1
#define NOW_ATTACKING 2
#define ATTACK_COOLDOWN 0.5
#define RESPAWN_TIME 3

char PLAYER_STR1[] = "□△□";		
char PLAYER_STR2[] = "◁▣▷";
char PLAYER_STR3[] = "□▽□";		// 플레이어의 생김새

typedef struct Player
{
	Position position;
	Position_collide collide;
	char* strPlayer1;	// 캐릭터를 포인터 설정(동적 할당)
	char* strPlayer2;
	char* strPlayer3;
	int isReady;
	int nLength;	    // 캐릭터의 길이
	int dead;
}Player;

Player player;
char* change;

void PlayerMove();
void PlayerCollide();
void EnemyTargetChange(EnemyDefault *p);
void PlayerAttack();
int WallCheck(int x, int y);
int ObstacleCheck();

void PlayerMove()
{
	if (player.isReady == NOW_ATTACKING)
	{ }
	else
	{
		if (GetAsyncKeyState(VK_LEFT) & 0x8000 && player.position.x > 0 && 
			WallCheck(-4, 1) && WallCheck(-4, 0) && WallCheck(-4, -1)) { //왼쪽
			player.position.x--;
			player.position.x--;
			sprintf(player.strPlayer1, "□△□");
			sprintf(player.strPlayer2, "◀▣▷");
			sprintf(player.strPlayer3, "□▽□");
		}

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && player.position.x < 75 &&
			WallCheck(4, 1) && WallCheck(4, 0) && WallCheck(4, -1)) { //오른쪽
			player.position.x++;
			player.position.x++;
			sprintf(player.strPlayer1, "□△□");
			sprintf(player.strPlayer2, "◁▣▶");
			sprintf(player.strPlayer3, "□▽□");
		}

		if (GetAsyncKeyState(VK_UP) & 0x8000 && player.position.y > 0 &&
			WallCheck(-2, -2) && WallCheck(0, -2) && WallCheck(2, -2)) { //위
			player.position.y--;
			sprintf(player.strPlayer1, "□▲□");
			sprintf(player.strPlayer2, "◁▣▷");
			sprintf(player.strPlayer3, "□▽□");
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000 && player.position.y < 35 &&
			WallCheck(-2, 2) && WallCheck(0, 2) && WallCheck(2, 2)) { //아래
			player.position.y++;
			sprintf(player.strPlayer1, "□△□");
			sprintf(player.strPlayer2, "◁▣▷");
			sprintf(player.strPlayer3, "□▼□");
		}
	}

}

void PlayerCollide()
{
	player.collide.x = player.position.x + 2;
	player.collide.y = player.position.y + 1;
}

void EnemyTargetChange(EnemyDefault *p)
{
	enemy_target = p;
}

void PlayerAttack()
{
	if (enemy_target->dead == 0)
	{
		p_ui->EnemyHP = enemy_target->hp;
		p_ui->EnemyAtt = enemy_target->att;
	}
	if (player.isReady == CANT_ATTACK)
	{
		if (player.collide.x == enemy_target->position.x || player.collide.y == enemy_target->position.y) player.isReady = CAN_ATTACK;
	}
	if (player.isReady == CAN_ATTACK)
	{
		if (player.collide.x != enemy_target->position.x || player.collide.y != enemy_target->position.y) player.isReady = CANT_ATTACK;
	}
	if (player.isReady == CAN_ATTACK && GetAsyncKeyState(0x41) & 0x8000)
	{
		player.isReady = NOW_ATTACKING;
		ui.second = ATTACK_COOLDOWN;
	}
	if (player.isReady == NOW_ATTACKING && p_ui->second <= 0)
	{
		if (p_ui->MyAtt >= enemy_target->hp)
		{
			ui.Money += enemy_target->money;
			p_ui->MyHP -= enemy_target->att;
			enemy_target->hp = 0;
			enemy_target->dead = TRUE;
			p_ui->EnemyHP = 0;
			p_ui->EnemyAtt = 0;
			player.isReady = CANT_ATTACK;
		}
		else
		{
			p_ui->MyHP -= enemy_target->att;
			enemy_target->hp -= p_ui->MyAtt;
			
			player.isReady = CAN_ATTACK;
		}
		ui.second = 0;
		ui.timer = 0;
	}
}

int WallCheck(int x, int y)
{
	if (map[player.collide.y + y][(player.collide.x + x) / 2] == WALL)
	{
		return 0;
	}
	if (map[player.collide.y + y][(player.collide.x + x) / 2] == OBSTACLE)
	{
		return 2;
	}
	return 1;
}

int ObstacleCheck()
{
	if (WallCheck(-2, -1) == 2) return 1;
	if (WallCheck(0, -1) == 2) return 1;
	if (WallCheck(2, -1) == 2) return 1;
	if (WallCheck(2, 0) == 2) return 1;
	if (WallCheck(2, 1) == 2) return 1;
	if (WallCheck(0, 1) == 2) return 1;
	if (WallCheck(-2, 1) == 2) return 1;
	if (WallCheck(-2, 0) == 2) return 1;
	if (WallCheck(0, 0) == 2) return 1;
	return 0;
}