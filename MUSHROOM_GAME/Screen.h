#pragma once
#include "all_include.h"

/* 아래 3개로 더블 버퍼링을 구현 */
void ScreenInit();		// 화면 초기화
void ScreenFlipping();	// 더블버퍼링, 2번화면과 1변화면 바꿔서 출력
void ScreenClear();		// 렌더링 화면을 빈 화면으로 바꿔준다
void ScreenRelease(); // 게임 종료시 메모리 초기화

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


