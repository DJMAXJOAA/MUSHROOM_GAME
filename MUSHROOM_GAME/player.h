#pragma once
#include "all_include.h"
#include "ui.h"

char PLAYER_STR1[];
char PLAYER_STR2[];
char PLAYER_STR3[];

enum
{
	ALIVE, DEAD, DISAPPEAR, INVENTORY
	// 0 살아있음, 1 죽음, 2 캐릭터 안보여야하는 상태(타이틀, 상점..), 3 인벤토리창(못움직임)
};

typedef struct Player
{
	Position position;
	Position_collide collide;
	char name[10];
	char* strPlayer1;	// 캐릭터를 포인터 설정(동적 할당)
	char* strPlayer2;
	char* strPlayer3;
	int isReady;
	int nLength;	    // 캐릭터의 길이
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

void PlayerMove();							// 캐릭터 움직임 (공격중일때 못움직임)
void PlayerCollide();						// 캐릭터와 타 오브젝트 충돌판정(중앙)
void PlayerDead();				// 죽었을때 살리고 초기화시킴
void EnemyTargetChange(EnemyDefault *p);	// 캐릭과 적과 닿으면 적으로 타겟 고정
void PlayerAttack();						// 캐릭터 공격
int WallCheck(int x, int y, int(*map)[HEIGHT]);	// 캐릭터 벽 판정 체크
int ObstacleCheck();						// 캐릭터 장애물 판정 체크
void PortalCheck(Portal* p);				// 캐릭터 포탈 판정 체크
void AttackTiming();						// 캐릭터 공격시 타이밍 미사일 이동관련
void MissileTargetChange(Missile* p);		// 판정선 근처에서 미사일의 참조를 바꿔준다
void MissileInit();							// 미사일 초기화
void AttackCoolDown();						// 공격 쿨타임

