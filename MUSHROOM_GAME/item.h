#pragma once
#include "all_include.h"

enum item_rank
{
	C, B, A, S	// rank배열 0~3 클수록 높은거
};

typedef struct Item
{
	char rank;		// 랭크
	char name[20];	// 장비 이름
	double att;		// 추가공격력
	double hp;		// 추가체력
	int sell_money;	// 판매가격
}Item;

Item item_S[3];
Item item_A[3];
Item item_B[3];
Item item_C[3];

/*
S 500원 : 공30체70 크리 판정선 증가(무조건 크리) / 공40체40 크리티컬공격력*2 / 공100체0 맞으면죽음
A 200원 : 공20체50 타이밍 미사일 속도가 느려짐 / 공25체20 크리티컬공격력*1.75 / 공40체0 걍머없음
B 100원 : 공5체40 / 공15체15 / 공20체0
C 50원 : 공1체40 / 공5체20 / 공10체0
*/