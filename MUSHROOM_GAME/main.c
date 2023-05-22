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
	StageInit(stage_number);
	ConstInit(); // 초기화


	/*===========시작(q종료)============*/
	while (1)
	{
		int nKey = GetKeyEvent();
		if (nKey == 'q' || nKey == 'Q')
			break;
		if (nKey == 'r' || nKey == 'R')
		{
			Init();
			StageInit(stage_number);
		}
			
		Player_HPbar();
		Enemy_HPbar();
		if (player.dead == FALSE && player.shop == FALSE)
		{
			PlayerCollide();
			PlayerMove();
			PlayerAttack();
			AttackTiming();
		}
		if (player.shop == TRUE) ShopSelect();
	

		Render();	//화면 출력
		WaitRender(clock());
		PlayerDead();	//죽음 체크
	}

	/*===========종료============*/
	Release();
	ScreenRelease();	//해제
	return 0;
}


