#pragma once
#include "all_include.h"
#include "UI.h"


#define CANT_ATTACK 0
#define CAN_ATTACK 1
#define NOW_ATTACKING 2
#define ATTACK_COOLDOWN 0.5
#define RESPAWN_TIME 1

char PLAYER_STR1[] = "　△　";		
char PLAYER_STR2[] = "◁▣▷";
char PLAYER_STR3[] = "　▽　";		// 플레이어의 생김새

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

typedef struct Missile
{
	float x;
	float y;
	float speed;
	int interval;
	int extinct;
}Missile;

Player player;
Missile missile1;
Missile missile2;
Missile missile3;

void PlayerMove();
void PlayerCollide();
void EnemyTargetChange(EnemyDefault *p);
void PlayerAttack();
int WallCheck(int x, int y);
int ObstacleCheck();
void AttackTiming();

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
			sprintf(player.strPlayer1, "　△　");
			sprintf(player.strPlayer2, "◀▣▷");
			sprintf(player.strPlayer3, "　▽　");
		}

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && player.position.x < 75 &&
			WallCheck(4, 1) && WallCheck(4, 0) && WallCheck(4, -1)) { //오른쪽
			player.position.x++;
			player.position.x++;
			sprintf(player.strPlayer1, "　△　");
			sprintf(player.strPlayer2, "◁▣▶");
			sprintf(player.strPlayer3, "　▽　");
		}

		if (GetAsyncKeyState(VK_UP) & 0x8000 && player.position.y > 0 &&
			WallCheck(-2, -2) && WallCheck(0, -2) && WallCheck(2, -2)) { //위
			player.position.y--;
			sprintf(player.strPlayer1, "　▲　");
			sprintf(player.strPlayer2, "◁▣▷");
			sprintf(player.strPlayer3, "　▽　");
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000 && player.position.y < 35 &&
			WallCheck(-2, 2) && WallCheck(0, 2) && WallCheck(2, 2)) { //아래
			player.position.y++;
			sprintf(player.strPlayer1, "　△　");
			sprintf(player.strPlayer2, "◁▣▷");
			sprintf(player.strPlayer3, "　▼　");
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
		ui.second = 0;
	}

	if (player.isReady == NOW_ATTACKING && ui.second <= 0)
	{
		ui.second = 0;
	}
	if (player.isReady == NOW_ATTACKING && GetAsyncKeyState(0x46) & 0x8000 && ui.second == 0)
	{
		if (missile1.x >= 97 && missile1.x <= 103)
		{
			enemy_target->hp -= ui.MyAtt;
			missile1.extinct == TRUE;
			ui.second = ATTACK_COOLDOWN;
		}
		else
		{
			ui.MyHP -= enemy_target->att;
			missile1.extinct == TRUE;
			ui.second = ATTACK_COOLDOWN;
		}
	}

	if (player.isReady == NOW_ATTACKING && missile3.extinct == TRUE)
	{
		if (p_ui->MyAtt >= enemy_target->hp)
		{
			ui.Money += enemy_target->money;
			p_ui->MyHP -= enemy_target->att;
			enemy_target->hp = 0;
			enemy_target->dead = TRUE;
			p_ui->EnemyHP = 0;
			p_ui->EnemyAtt = 0;
			enemy_target = &enemy;

			missile1.extinct = FALSE;
			missile2.extinct = FALSE;
			missile3.extinct = FALSE;
			missile1.interval = 20;
			missile2.interval = 10;
			missile3.interval = 20;

			player.isReady = CANT_ATTACK;	
		}
		else
		{
			p_ui->MyHP -= enemy_target->att;
			enemy_target->hp -= p_ui->MyAtt;

			missile1.extinct = FALSE;
			missile2.extinct = FALSE;
			missile3.extinct = FALSE;
			missile1.interval = 20;
			missile2.interval = 10;
			missile3.interval = 20;
			
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

void AttackTiming()
{
	if (player.isReady == NOW_ATTACKING && missile1.x <= 118 && missile1.extinct == FALSE)
	{
		missile1.x += missile1.speed;
		missile1.interval--;
	}
	else if(missile1.x > 118 && missile1.extinct == TRUE)
	{
		missile1.x = 82;
		missile1.extinct = TRUE;
	}

	if (missile1.interval <= 0 && missile2.x <= 118 && missile2.extinct == FALSE)
	{
		missile2.x += missile2.speed;
		missile2.interval--;
	}
	else if (missile2.x > 118 && missile2.extinct == TRUE)
	{
		missile2.x = 82;
		missile2.extinct = TRUE;
	}

	if (missile2.interval <= 0 && missile3.x <= 118 && missile3.extinct == FALSE)
	{
		missile3.x += missile3.speed;
		missile3.interval--;
	}
	else if (missile3.x > 118 && missile3.extinct == TRUE)
	{
		missile3.x = 82;
		missile3.extinct = TRUE;
	}
}