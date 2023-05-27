#pragma once
#include "all_include.h"
#include "ui.h"

char PLAYER_STR1[];
char PLAYER_STR2[];
char PLAYER_STR3[];

enum
{
	ALIVE, DEAD, DISAPPEAR, INVENTORY
	// 0 �������, 1 ����, 2 ĳ���� �Ⱥ������ϴ� ����(Ÿ��Ʋ, ����..), 3 �κ��丮â(��������)
};

typedef struct Player
{
	Position position;
	Position_collide collide;
	char name[10];
	char* strPlayer1;	// ĳ���͸� ������ ����(���� �Ҵ�)
	char* strPlayer2;
	char* strPlayer3;
	int isReady;
	int nLength;	    // ĳ������ ����
	int state;
}Player;

typedef struct Missile
{
	double x;
	double y;
	double speed;
	int interval;
	int extinct;
}Missile;

Player player;

Missile* missile;
Missile init_missile;
Missile missile1;
Missile missile2;
Missile missile3;

void PlayerMove();							// ĳ���� ������ (�������϶� ��������)
void PlayerCollide();						// ĳ���Ϳ� Ÿ ������Ʈ �浹����(�߾�)
void PlayerDead();				// �׾����� �츮�� �ʱ�ȭ��Ŵ
void EnemyTargetChange(EnemyDefault *p);	// ĳ���� ���� ������ ������ Ÿ�� ����
void PlayerAttack();						// ĳ���� ����
int WallCheck(int x, int y, int(*map)[HEIGHT]);	// ĳ���� �� ���� üũ
int ObstacleCheck();						// ĳ���� ��ֹ� ���� üũ
void PortalCheck(Portal* p);				// ĳ���� ��Ż ���� üũ
void AttackTiming();						// ĳ���� ���ݽ� Ÿ�̹� �̻��� �̵�����
void MissileTargetChange(Missile* p);		// ������ ��ó���� �̻����� ������ �ٲ��ش�
void MissileInit();							// �̻��� �ʱ�ȭ
void AttackCoolDown();						// ���� ��Ÿ��

