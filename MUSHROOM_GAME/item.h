#pragma once
#include "all_include.h"

enum item_rank
{
	C, B, A, S	// rank�迭 0~3 Ŭ���� ������
};

typedef struct Item
{
	char rank;
	double att;
	double hp;
}Item;

Item item_S[3];
Item item_A[3];
Item item_B[3];
Item item_C[3];

/*
C : ��0ü40 / ��10ü20 / ��20ü0
B : ��10ü40 / ��20ü20 / ��30ü0
A : ��15ü50 Ÿ�̹� �̻��� �ӵ��� ������ / ��30ü20 ũ��Ƽ�ð��ݷ�*1.75 / ��50ü0 ������
S : ��30ü60 ũ�� ������ ����(������ ũ��) / ��50ü20 ũ��Ƽ�ð��ݷ�*2 / ��100ü-20 ũ��Ƽ�ý� ü��ȸ�� 
*/