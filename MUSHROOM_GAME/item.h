#pragma once
#include "all_include.h"

enum item_rank
{
	C, B, A, S	// rank�迭 0~3 Ŭ���� ������
};

enum ability	// �ɷ¾���, �̻��Ͻ��ο�, ũ��*1.75, ũ��*2.0, ũ��Ȯ��, �������ֱ�
{
	NONE, SLOW, CRIT_DMG1, CRIT_DMG2, CRIT_RANGE_UP, BURSERKR
};

typedef struct Item
{
	char rank;		// ��ũ
	char name[20];	// ��� �̸�
	double att;		// �߰����ݷ�
	double hp;		// �߰�ü��
	int sell_money;	// �ǸŰ���
	char data[100];	// ���� ������(���â)
	int ability;	// ���� Ư���ɷ�
}Item;

Item item_S[3];
Item item_A[3];
Item item_B[3];
Item item_C[3];