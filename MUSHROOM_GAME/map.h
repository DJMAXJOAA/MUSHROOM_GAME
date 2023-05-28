#pragma once
#include "all_include.h"

typedef struct Portal
{
	Position position;
	int move_to_where;
}Portal;

Portal portal1;
Portal portal2;
Portal portal3;
Portal portal4;

int map0[1][1];
int map1[WIDTH][HEIGHT];
int map2[WIDTH][HEIGHT];
int map3[WIDTH][HEIGHT];


int** map_pointer;