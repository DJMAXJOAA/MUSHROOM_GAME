#pragma once
#include "all_include.h"

enum item_rank
{
	C, B, A, S	// rank�迭 0~3 Ŭ���� ������
};

typedef struct Item
{
	char rank;		// ��ũ
	char name[20];	// ��� �̸�
	double att;		// �߰����ݷ�
	double hp;		// �߰�ü��
	int sell_money;	// �ǸŰ���
}Item;

Item item_S[3];
Item item_A[3];
Item item_B[3];
Item item_C[3];

/*
S 500�� : ��30ü70 ũ�� ������ ����(������ ũ��) / ��40ü40 ũ��Ƽ�ð��ݷ�*2 / ��100ü0 ����������
A 200�� : ��20ü50 Ÿ�̹� �̻��� �ӵ��� ������ / ��25ü20 ũ��Ƽ�ð��ݷ�*1.75 / ��40ü0 ���Ӿ���
B 100�� : ��5ü40 / ��15ü15 / ��20ü0
C 50�� : ��1ü40 / ��5ü20 / ��10ü0
*/