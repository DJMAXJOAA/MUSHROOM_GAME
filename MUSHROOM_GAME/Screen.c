#include "Screen.h"

void ScreenInit()
{
	CONSOLE_CURSOR_INFO cci;

	/* ȭ�鿡 ���� 2�� ���� */
	g_hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	g_hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	/* Ŀ�� ����� */
	cci.dwSize = 1;		// Ŀ�� ���� = 1
	cci.bVisible = FALSE;	// TRUE ����, FALSE �Ⱥ���
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
	DWORD dw; // Double WORD �ڷ��� (= typedef unsigned long, 32��Ʈ:4����Ʈ)
	FillConsoleOutputCharacter(g_hScreen[g_nScreenIndex], ' ', 120 * 40, Coor, &dw);
}

void ScreenRelease()
{
	CloseHandle(g_hScreen[0]);
	CloseHandle(g_hScreen[1]);
}


