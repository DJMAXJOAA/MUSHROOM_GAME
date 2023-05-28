#include "player.h"

char PLAYER_STR1[] = "　△　";
char PLAYER_STR2[] = "◁▣▷";
char PLAYER_STR3[] = "　▽　";		// 플레이어의 생김새

void PlayerMove()
{
	if (player.isReady == NOW_ATTACKING)
	{
		// 공격중 이동불가
	}
	else
	{
		if (GetAsyncKeyState(VK_LEFT) & 0x8000 && player.position.x > 0 &&
			WallCheck(-4, 1, map_pointer) && WallCheck(-4, 0, map_pointer) && WallCheck(-4, -1, map_pointer)) { //왼쪽
			player.position.x--;
			player.position.x--;
			sprintf(player.strPlayer1, "　△　");
			sprintf(player.strPlayer2, "◀▣▷");
			sprintf(player.strPlayer3, "　▽　");
		}

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && player.position.x < 75 &&
			WallCheck(4, 1, map_pointer) && WallCheck(4, 0, map_pointer) && WallCheck(4, -1, map_pointer)) { //오른쪽
			player.position.x++;
			player.position.x++;
			sprintf(player.strPlayer1, "　△　");
			sprintf(player.strPlayer2, "◁▣▶");
			sprintf(player.strPlayer3, "　▽　");
		}

		if (GetAsyncKeyState(VK_UP) & 0x8000 && player.position.y > 0 &&
			WallCheck(-2, -2, map_pointer) && WallCheck(0, -2, map_pointer) && WallCheck(2, -2, map_pointer)) { //위
			player.position.y--;
			sprintf(player.strPlayer1, "　▲　");
			sprintf(player.strPlayer2, "◁▣▷");
			sprintf(player.strPlayer3, "　▽　");
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000 && player.position.y < 35 &&
			WallCheck(-2, 2, map_pointer) && WallCheck(0, 2, map_pointer) && WallCheck(2, 2, map_pointer)) { //아래
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

void PlayerDead()
{
	if (ui.MyHP <= 0 && player.state == ALIVE)
	{
		ui.MyHP = 0;
		player.state = DEAD;
		ui.respawn += RESPAWN_TIME;
	}
	if (ui.respawn <= 0 && player.state == DEAD)
	{
		ui.MyHP = ui.MyMaxHP;
		SetColor(WHITE);
		stage = TOWN;
		Init();
		StageInit(stage);
	}
}

void EnemyTargetChange(EnemyDefault* p)
{
	enemy_target = p;
	if (enemy_target != enemy_target_new)	// 처음에만 적 정보 뜨게
	{
		enemy_target = p;
		enemy_target_new = p;
		InitNotice();
		notice.CollideEnemy = TRUE;
	}
	notice.GetMoney = FALSE;	// 돈 얼마 알림 끄기

}

void PlayerAttack()
{
	double temp = p_ui->MyAtt;
	if (enemy_target->dead == 0)	// ui창에 체력 공격력
	{
		p_ui->EnemyHP = enemy_target->hp;
		p_ui->EnemyAtt = enemy_target->att;
	}

	if (player.isReady == CANT_ATTACK)	// 적이랑 닿으면 공격 준비상태
	{
		if (player.collide.x == enemy_target->position.x || player.collide.y == enemy_target->position.y) player.isReady = CAN_ATTACK;
	}

	if (player.isReady == CAN_ATTACK)
	{
		MissileInit();
		MissileTargetChange(&init_missile);
		if (player.collide.x != enemy_target->position.x || player.collide.y != enemy_target->position.y) player.isReady = CANT_ATTACK;
	}

	if (player.isReady == CAN_ATTACK && GetAsyncKeyState(0x41) & 0x8000)
	{
		notice.CollideEnemy = FALSE;
		second_all = 0;
		player.isReady = NOW_ATTACKING;
	}

	if (player.isReady == NOW_ATTACKING && GetAsyncKeyState(0x46) & 0x8000 && second_all == 0)
	{
		if (missile->x >= 98 && missile->x <= 102)	// 공격 타이밍 맞으면
		{
			/* 정확히 정박 혹은 크리보정 아이템 착용시 */
			if (missile->x == 100 || inventory[now_equipment].info->ability == CRIT_RANGE_UP)
			{
				temp = p_ui->MyAtt;
				p_ui->MyAtt *= ui.CritDMG;
				notice.Damaged = FALSE;
				notice.HitEnemy = FALSE;
				notice.Critical += 1;
			}
			else
			{
				notice.Damaged = FALSE;
				notice.HitEnemy = TRUE;
				notice.Critical = 0;
			}

			if (p_ui->MyAtt >= enemy_target->hp)	// 1. 적이 내공격에 죽는피일때
			{
				notice.GetMoney = TRUE;		// 돈 얼마먹었는지 알림
				notice.temp_money = enemy_target->money;
				ui.Money += enemy_target->money;	// 돈먹고
				p_ui->MyAtt = temp;		// 크리티컬 데미지 초기화

				enemy_target->hp = 0;
				enemy_target->dead = TRUE;
				p_ui->EnemyHP = 0;
				p_ui->EnemyAtt = 0;
				enemy_target = &enemy;		// 적 죽이고 초기화
				strcpy(ui.Enemy_HPbar, "□□□□□□□□□□");

				MissileInit();

				notice.Damaged = FALSE;
				notice.HitEnemy = FALSE;
				notice.Critical = 0;

				player.isReady = CANT_ATTACK;
			}

			else	// 적이 공격해도 안죽음 : 적 피만 깎음
			{
				missile->extinct = TRUE;
				missile->x = 82;
				enemy_target->hp -= p_ui->MyAtt;
				p_ui->MyAtt = temp;		// 크리티컬 데미지 초기화
				second_all = ATTACK_COOLDOWN;
			}
		}
		else if (missile->x > 90)	// 공격 타이밍 안맞으면 : 내 피가 깎임
		{
			missile->x = 82;
			missile->extinct = TRUE;
			AttackCoolDown();
			notice.Damaged = TRUE;
			notice.HitEnemy = FALSE;
			notice.Critical = 0;
		}
	}
}


int WallCheck(int x, int y, int(*map)[HEIGHT])
{
	if (map[player.collide.y + y][(player.collide.x + x) / 2] == WALL || map[player.collide.y + y][(player.collide.x + x) / 2] == CLEAR_WALL)
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
	if (WallCheck(-2, -1, map_pointer) == 2) return 1;
	if (WallCheck(0, -1, map_pointer) == 2) return 1;
	if (WallCheck(2, -1, map_pointer) == 2) return 1;
	if (WallCheck(2, 0, map_pointer) == 2) return 1;
	if (WallCheck(2, 1, map_pointer) == 2) return 1;
	if (WallCheck(0, 1, map_pointer) == 2) return 1;
	if (WallCheck(-2, 1, map_pointer) == 2) return 1;
	if (WallCheck(-2, 0, map_pointer) == 2) return 1;
	if (WallCheck(0, 0, map_pointer) == 2) return 1;
	return 0;
}

void PortalCheck(Portal* p)
{
	stage = p;
}

void AttackTiming()
{
	if (missile1.x >= 90 && missile1.extinct == FALSE) MissileTargetChange(&missile1);
	if (missile2.x >= 90 && missile2.extinct == FALSE) MissileTargetChange(&missile2);
	if (missile3.x >= 90 && missile3.extinct == FALSE) MissileTargetChange(&missile3);

	if (player.isReady == NOW_ATTACKING)
	{
		missile1.interval--;
		if (missile1.x <= 118 && missile1.extinct == FALSE)
		{
			missile1.x += missile1.speed;
		}
	}
	if (missile1.x > 118)
	{
		missile1.x = 82;
		missile1.extinct = TRUE;
		AttackCoolDown();
		notice.Damaged = TRUE;
		notice.HitEnemy = FALSE;
		notice.Critical = 0;
	}

	if (missile1.interval <= 0)
	{
		missile2.interval--;
		if (missile2.x <= 118 && missile2.extinct == FALSE)
		{
			missile2.x += missile2.speed;

		}
	}
	if (missile2.x > 118 && missile1.extinct == TRUE)
	{
		missile2.x = 82;
		missile2.extinct = TRUE;
		AttackCoolDown();
		notice.Damaged = TRUE;
		notice.HitEnemy = FALSE;
		notice.Critical = 0;
	}

	if (missile2.interval <= 0)
	{
		missile3.interval--;
		if (missile3.x <= 118 && missile3.extinct == FALSE)
		{
			missile3.x += missile3.speed;
		}
	}
	if (missile3.x > 118 && missile2.extinct == TRUE)
	{
		AttackCoolDown();
		player.isReady = CAN_ATTACK;
		MissileInit();
		notice.Damaged = TRUE;
		notice.HitEnemy = FALSE;
		notice.Critical = 0;
	}
	if (missile3.extinct == TRUE)
	{
		player.isReady = CAN_ATTACK;
		MissileInit();
	}
}

void MissileTargetChange(Missile* p)
{
	missile = p;
}

void MissileInit()
{
	missile1.x = 82;
	missile2.x = 82;
	missile3.x = 82;
	missile1.extinct = FALSE;
	missile2.extinct = FALSE;
	missile3.extinct = FALSE;
	missile1.interval = RandomDouble(10, 30);
	missile2.interval = RandomDouble(10, 31);
	missile3.interval = RandomDouble(10, 32);
}

void AttackCoolDown()
{
	if (enemy_target->att >= ui.MyHP || inventory[now_equipment].info->ability == BURSERKR)
	{
		ui.MyHP = 0;
	}
	else
	{
		ui.MyHP -= enemy_target->att;
		second_all = ATTACK_COOLDOWN;
	}
}

void PlayerBuff()
{

	if (inventory[now_equipment].info->ability == SLOW) // 미사일슬로우
	{
		ui.CritDMG = 1.5;
		missile1.speed = 1;
		missile2.speed = 1;
		missile3.speed = 1;
	}
	else if (inventory[now_equipment].info->ability == CRIT_DMG1) // 크리*1.75
	{
		ui.CritDMG = 1.75;
		missile1.speed = 1.5;
		missile2.speed = 1.5;
		missile3.speed = 1.5;
	}
	else if (inventory[now_equipment].info->ability == CRIT_DMG2) // 크리*2.0
	{
		ui.CritDMG = 2.0;
		missile1.speed = 1.5;
		missile2.speed = 1.5;
		missile3.speed = 1.5;
	}
	else if (inventory[now_equipment].info->ability == CRIT_RANGE_UP) // 크리확정
	{
		ui.CritDMG = 1.5;
		missile1.speed = 1.5;
		missile2.speed = 1.5;
		missile3.speed = 1.5;
	}
	else if (inventory[now_equipment].info->ability == BURSERKR) // 맞으면주금
	{
		ui.CritDMG = 1.5;
		missile1.speed = 1.5;
		missile2.speed = 1.5;
		missile3.speed = 1.5;
	}
	else if (inventory[now_equipment].info->ability == NONE)	// 보통
	{
		ui.CritDMG = 1.5;
		missile1.speed = 1.5;
		missile2.speed = 1.5;
		missile3.speed = 1.5;
	}
}