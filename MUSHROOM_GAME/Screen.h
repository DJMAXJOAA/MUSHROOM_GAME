#pragma once
#include "all_include.h"

/* 아래 3개로 더블 버퍼링을 구현 */
void ScreenInit();
void ScreenFlipping();
void ScreenClear();
void ScreenRelease(); // 게임 종료시 메모리 초기화
void ScreenPrint(int x, int y, char* string);	// 문자열 출력
extern void SetColor(unsigned short color);	// 색 설정

// static -> Screen.c 안에서만 사용 가능한 전역 변수 선언
static int g_nScreenIndex;
static HANDLE g_hScreen[2];
/* 시스템 접근 위한 핸들 설정(오브젝트 핸들)
함수로는 GetStdHandle(STD_OUTPUT_HANDLE)도 가능 */

void ScreenInit()
{
	CONSOLE_CURSOR_INFO cci;

	/* 화면에 버퍼 2개 생성 */
	g_hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	g_hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	/* 커서 숨기기 */
	cci.dwSize = 1;		// 커서 굵기 = 1
	cci.bVisible = FALSE;	// TRUE 보임, FALSE 안보임
	SetConsoleCursorInfo(g_hScreen[0], &cci);
	SetConsoleCursorInfo(g_hScreen[1], &cci);
}

void ScreenFlipping()
{
	SetConsoleActiveScreenBuffer(g_hScreen[g_nScreenIndex]);
	g_nScreenIndex = !g_nScreenIndex;
}

void ScreenClear()
{
	COORD Coor = { 0,0 };
	DWORD dw; // Double WORD 자료형 (= typedef unsigned long, 32비트:4바이트)
	FillConsoleOutputCharacter(g_hScreen[g_nScreenIndex], ' ', 120 * 40, Coor, &dw);
}

void ScreenRelease()
{
	CloseHandle(g_hScreen[0]);
	CloseHandle(g_hScreen[1]);
}

void ScreenPrint(double x, double y, char* string)
{
	DWORD dw;
	COORD CursorPosition = { x, y };
	SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
	WriteFile(g_hScreen[g_nScreenIndex], string, strlen(string), &dw, NULL);
}

extern void SetColor(unsigned short color) // 15가지 색상
{
	SetConsoleTextAttribute(g_hScreen[g_nScreenIndex], color);
}

