#pragma once
#include "all_include.h"

typedef struct Info	// ���� ����
{
	int money;			// ����
	int amount;			// ����
	double cooldown;	// ��� ��Ÿ��
}Info;

typedef struct Scroll	// 1 ��ȯ��
{
	Info info;
	double return_time;	// ��ȯ �ð�
}Scroll;

typedef struct Postion	// 2 ����
{
	Info info;
	double heal_value;	// ����
}Postion;

typedef struct Boom		// 3 ��ź
{
	Info info;
	int direction;		// ��ź ���� ����
	double boom_speed;	// ��ź �ӵ�
	double explosion_time	// ���� �����ð�
}Boom;

Scroll scroll;
Postion postion;
Boom boom;