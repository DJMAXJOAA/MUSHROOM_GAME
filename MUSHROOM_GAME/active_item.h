#pragma once
#include "all_include.h"

typedef struct Info	// 공통 정보
{
	int money;			// 가격
	int amount;			// 수량
	double cooldown;	// 사용 쿨타임
}Info;

typedef struct Scroll	// 1 귀환서
{
	Info info;
	double return_time;	// 귀환 시간
}Scroll;

typedef struct Postion	// 2 포션
{
	Info info;
	double heal_value;	// 힐량
}Postion;

typedef struct Boom		// 3 폭탄
{
	Info info;
	int direction;		// 폭탄 진행 방향
	double boom_speed;	// 폭탄 속도
	double explosion_time	// 폭발 남은시간
}Boom;

Scroll scroll;
Postion postion;
Boom boom;