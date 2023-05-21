#define _CRT_SECURE_NO_WARNINGS
#include "setting.h"
#include "create_map.h"

int main()
{
	system("mode con:cols=120 lines=32");
	system("MUSHROOM GAME");
	CreateMap();
	
	ScreenInit();
	StageInit(1);
	Init();		// 초기화


	/*===========시작(q종료)============*/
	while (1)
	{
		int nKey = GetKeyEvent();
		if (nKey == 'q')
			break;

		if (player.dead == FALSE)
		{
			PlayerCollide();
			PlayerMove();
			PlayerAttack();
			AttackTiming();
		}

		Render();	//화면 출력
		WaitRender(clock());
		Update();	//죽음 체크
	}

	/*===========종료============*/
	Release();
	ScreenRelease();	//해제
	return 0;
}


