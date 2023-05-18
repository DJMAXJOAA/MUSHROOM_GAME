#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>	//콘솔 입출력 제공 헤더파일

void Init()	//초기화
{

}

void Update() //데이터 갱신
{

}

void Render() //화면 출력
{
	ScreenClear();
	// 출력코드
	ScreenFlipping();
}

void Release()	//해제
{

}

int main()
{
	int nKey;
	clock_t CurTime, OldTime;	//clock_t 수행시간 측정

	ScreenInit();
	Init();	// 초기화

	/* ESC : 종료 */
	while (1)
	{
		if (_kbhit()) //_kbhit : 키보드가 눌렀음을 확인하는 함수
		{
			nKey = _getch();	//읽은 문자 반환
			if (nKey == 27) break;
			switch (nKey)
			{
			case 'j': break;
			case 'l': break;
			}
		}

		OldTime = clock();	//프로그램 시작 후 지난 틱 수 반환
		Update();	//데이터 갱신
		Render(); //화면 출력
		while (1)
		{
			CurTime = clock();
			if (CurTime - OldTime > 33) break;
		}

	}
	Release();
	ScreenRelease();	//해제
	return 0;
}