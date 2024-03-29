#include "all_include.h"
#include "Screen.h"

double second_all = 0;	// 클락 시간 초
int stage  = 0;			// 시작 맵 설정
char string[100] = { 0 };

double RandomDouble(int range_min, int range_max)
{
	srand((unsigned int)time(NULL));
	double random = rand() % (range_max - range_min + 1) + range_min;
	return random;
}

int Random(int range_min, int range_max)
{
	srand((unsigned int)time(NULL));
	int random = rand() % (range_max - range_min + 1) + range_min;
	return random;
}

void PrintScreen(int x, int y, char* string)
{
	DWORD dw;
	COORD CursorPosition = { x, y };
	SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
	WriteFile(g_hScreen[g_nScreenIndex], string, strlen(string), &dw, NULL);
}


void SetColor(unsigned short color) // 15가지 색상
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

int GetKeyEvent()
{
	if (_kbhit())	//_kbhit : 키보드가 눌렀음을 확인하는 함수
		return _getch();	//읽은 문자 반환

	return -1;
}