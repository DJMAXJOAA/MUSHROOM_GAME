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
S : 공30체60 크리 판정선 증가(무조건 크리) / 공50체20 크리티컬공격력*2 / 공100체-50 크리티컬시 체력회복 
A : 공15체50 타이밍 미사일 속도가 느려짐 / 공30체20 크리티컬공격력*1.75 / 공50체0 걍없음
B : 공10체40 / 공20체20 / 공30체0
C : 공0체40 / 공10체20 / 공20체0
*/