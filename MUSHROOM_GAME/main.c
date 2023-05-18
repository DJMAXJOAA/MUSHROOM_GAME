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

void WaitRender(clock_t OldTime)
{
	clock_t CurTime;	//clock_t 수행시간 측정
	while (1)
	{
		CurTime = clock();
		if (CurTime - OldTime > 33)
			break;
	}
}

void Release()	//해제
{

}

int GetKeyEvent()
{
	if (_kbhit())	//_kbhit : 키보드가 눌렀음을 확인하는 함수
		return _getch();	//읽은 문자 반환

	return -1;
}

void KeyProcess(int key)
{
	switch (key)
	{
	case 'i':
		break;
	case 'j':
		break;
	}
}

int main()
{
	ScreenInit();
	Init();		// 초기화

	/* q : 종료 */
	while (1)
	{
		int nKey = GetKeyEvent();
		if (nKey == 'q')
			break;
		KeyProcess(nKey);

		Update();	//데이터 갱신

		Render();	//화면 출력
		WaitRender(clock());
	}
	Release();
	ScreenRelease();	//해제
	return 0;
}