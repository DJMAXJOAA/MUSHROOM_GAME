#pragma once
#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <malloc.h>
#include <stralign.h>
#include "Screen.h"

/* ĳ���� ���� */
#define CANT_ATTACK 0
#define CAN_ATTACK 1
#define NOW_ATTACKING 2
#define ATTACK_COOLDOWN 0.1
#define RESPAWN_TIME 1

/* �ʰ��� */
#define WIDTH 32
#define HEIGHT 40

#define EMPTY 0
#define WALL 1
#define FOREST 2
#define CLEAR_WALL 3
#define OBSTACLE 9

#define NPC1 71
#define NPC2 72

#define PORTAL1 81
#define PORTAL2 82
#define PORTAL3 83
#define PORTAL4 84

#define ENEMY1 91
#define ENEMY2 92
#define ENEMY3 93
#define OBSTACLE_DAMAGE 1


enum map_name
{
	TITLE, TOWN, REGION1, SHOP1, SHOP2, ROULETTE, END = 99
};

enum color
{
	BLACK, D_BLACK, D_GREEN, D_SKYBLUE, D_RED, D_VIOLET, D_YELLOW,
	GRAY, D_GRAY, BLUE, GREEN, SKYBLUE, RED, VIOLET, YELLOW, WHITE
};

int stage = 0;	// ���� �� ����
double second = 0;			// Ŭ�� �ð� ��

double random_double(int range_min, int range_max);		//�����Լ� �������� �Ǽ�
int random(int range_min, int range_max);				//�����Լ� ��������
void PrintScreen(double x, double y, char* string);		// ���ڿ� ���
void SetColor(unsigned short color);					// �� ����
void FilePrintStr(char* input_str, int x, int y);		// �ؽ�Ʈ ���� �����ͼ� ȭ�� ����ϱ�


double random_double(int range_min, int range_max)
{
	srand((unsigned int)time(NULL));
	double random = rand() % (range_max - range_min + 1) + range_min;
	return random;
}

int random(int range_min, int range_max)
{
	srand((unsigned int)time(NULL));
	int random = rand() % (range_max - range_min + 1) + range_min;
	return random;
}

void PrintScreen(double x, double y, char* string)
{
	DWORD dw;
	COORD CursorPosition = { x, y };
	SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
	WriteFile(g_hScreen[g_nScreenIndex], string, strlen(string), &dw, NULL);
}


void SetColor(unsigned short color) // 15���� ����
{
	SetConsoleTextAttribute(g_hScreen[g_nScreenIndex], color);
}

void FilePrintStr(char* input_str, int x, int y)
{
	char str[200];
	FILE* fp = fopen(input_str, "rt");
	if (fp == NULL) return;
	int i = 0;
	while (1)
	{
		char* pstr = fgets(str, 200, fp);
		if (pstr == NULL)
		{
			break;
		}
		PrintScreen(x, y + i, str);
		i++;
	}
	fclose(fp);
}