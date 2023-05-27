#pragma once
#include "all_include.h"

enum item_rank
{
	C, B, A, S	// rank배열 0~3 클수록 높은거
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
C : 공0체40 / 공10체20 / 공20체0
B : 공10체40 / 공20체20 / 공30체0
A : 공15체50 타이밍 미사일 속도가 느려짐 / 공30체20 크리티컬공격력*1.75 / 공50체0 걍없음
S : 공30체60 크리 판정선 증가(무조건 크리) / 공50체20 크리티컬공격력*2 / 공100체-20 크리티컬시 체력회복 
*/