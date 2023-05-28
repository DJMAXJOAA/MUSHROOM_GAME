#pragma once
#include "all_include.h"

enum item_rank
{
	C, B, A, S	// rank배열 0~3 클수록 높은거
};

enum ability	// 능력없음, 미사일슬로우, 크리*1.75, 크리*2.0, 크리확정, 맞으면주금
{
	NONE, SLOW, CRIT_DMG1, CRIT_DMG2, CRIT_RANGE_UP, BURSERKR
};

typedef struct Item
{
	char rank;		// 랭크
	char name[20];	// 장비 이름
	double att;		// 추가공격력
	double hp;		// 추가체력
	int sell_money;	// 판매가격
	char data[100];	// 무기 상세정보(장비창)
	int ability;	// 무기 특수능력
}Item;

Item item_S[3];
Item item_A[3];
Item item_B[3];
Item item_C[3];