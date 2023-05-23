#define _CRT_SECURE_NO_WARNINGS
#include "setting.h"
#include "create_map.h"


int main()
{
	system("mode con:cols=121 lines=32");
	system("MUSHROOM GAME");
	CreateMap();
	
	ScreenInit();
	Init();
	StageInit(stage);
	ConstInit();		// 초기화
	

	/*===========시작(q종료)============*/
	while (1)
	{
		int nKey = GetKeyEvent();
		if (nKey == 'q' || nKey == 'Q') break;		// 강종
		if (nKey == 'r' || nKey == 'R') { Init(); StageInit(stage);} // 리셋
			
		Player_HPbar();
		Enemy_HPbar();
		if (player.state == ALIVE)
		{
			PlayerCollide();
			PlayerMove();
			PlayerAttack();
			AttackTiming();
		}
	
		Render();	//화면 출력
		PlayerDead();	//죽음 체크

		WaitRender(clock());
	}

	/*===========종료============*/
	Release();
	ScreenRelease();	//해제
	return 0;
}


