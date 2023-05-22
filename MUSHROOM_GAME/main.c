#define _CRT_SECURE_NO_WARNINGS
#include "setting.h"
#include "create_map.h"

int main()
{
	system("mode con:cols=121 lines=32");
	system("MUSHROOM GAME");
	CreateMap();

	ConstInit();
	ScreenInit();
	Init();
	StageInit(stage_number);
			// �ʱ�ȭ


	/*===========����(q����)============*/
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



		Render();	//ȭ�� ���
		WaitRender(clock());
		PlayerDead();	//���� üũ
	}

	/*===========����============*/
	Release();
	ScreenRelease();	//����
	return 0;
}


