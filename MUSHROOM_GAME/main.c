#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>	//콘솔 입출력 제공 헤더파일
#include "Screen.h"	// 화면 창 관련 헤더

#include "main.h"
#include "Screen.h"
#include "player.h"

int main()
{
	system("mode con:cols=100 lines=40");
	ScreenInit();
	Init();		// 초기화


	/*===========시작(q종료)============*/
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

	/*===========종료============*/
	Release();
	ScreenRelease();	//해제
	return 0;
}


/*===========초기화(초기 설정)============*/
void Init()
{

	player.position.x = 0;
	player.position.y = 22;

	player.nLength = strlen(PLAYER_STR);

	player.strPlayer = (char*)malloc(sizeof(char) * player.nLength);
	strcpy(player.strPlayer, PLAYER_STR);
}

/*===========데이터갱신============*/
void Update()
{

}

/*===========화면출력, 화면에 나타나는 것들============*/
void Render()
{
	ScreenClear();
/*─────────────────────────────────────────────────────────────────────*/

	char string[100] = { 0 };

	ScreenPrint(player.position.x, player.position.y, player.strPlayer);

	sprintf(string, "주인공 이동 좌표 : %d, %d", player.position.x, player.position.y);
	ScreenPrint(0, 3, string);	// 좌표 표시창 어디에?

/*─────────────────────────────────────────────────────────────────────*/
	ScreenFlipping();
}

/*===========화면지연시간 33ms============*/
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

/*===========할당해제============*/
void Release()	//해제
{

}

/*===========키입력감지============*/
int GetKeyEvent()
{
	if (_kbhit())	//_kbhit : 키보드가 눌렀음을 확인하는 함수
		return _getch();	//읽은 문자 반환

	return -1;
}

/*===========캐릭터 이동============*/
void KeyProcess(int key)
{
	switch (key)
	{
	case 'a':
		if (player.position.x > 0)
		{
			player.position.x--;
		}
		break;
	case 'd':
		if (player.position.x < 100)
		{
			player.position.x++;
		}
		break;
	case 'w':
		if (player.position.y > 0)
		{
			player.position.y--;
		}
		break;
	case 's':
		if (player.position.y < 40)
		{
			player.position.y++;
		}
		break;
	}
}