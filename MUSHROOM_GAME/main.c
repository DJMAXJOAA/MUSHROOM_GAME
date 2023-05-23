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
	ConstInit();		// �ʱ�ȭ
	

	/*===========����(q����)============*/
	while (1)
	{
		int nKey = GetKeyEvent();
		if (nKey == 'q' || nKey == 'Q') break;		// ����
		if (nKey == 'r' || nKey == 'R') { Init(); StageInit(stage);} // ����
			
		Player_HPbar();
		Enemy_HPbar();
		if (player.state == ALIVE)
		{
			PlayerCollide();
			PlayerMove();
			PlayerAttack();
			AttackTiming();
		}
	
		Render();	//ȭ�� ���
		PlayerDead();	//���� üũ

		WaitRender(clock());
	}

	/*===========����============*/
	Release();
	ScreenRelease();	//����
	return 0;
}


