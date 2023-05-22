#pragma once
#include "all_include.h"

typedef struct
{
	char rank;
	double att;
	double hp;
	double critical_damage;
	double judge_plus;
}Item;

Item item_s[3];
Item item_a[3];
Item item_b[3];
Item item_c[3];

/*
S : ��30ü60 ũ�� ������ ����(������ ũ��) / ��50ü20 ũ��Ƽ�ð��ݷ�*2 / ��100ü-50 ũ��Ƽ�ý� ü��ȸ�� 
A : ��15ü50 Ÿ�̹� �̻��� �ӵ��� ������ / ��30ü20 ũ��Ƽ�ð��ݷ�*1.75 / ��50ü0 ������
B : ��10ü40 / ��20ü20 / ��30ü0
C : ��0ü40 / ��10ü20 / ��20ü0
*/