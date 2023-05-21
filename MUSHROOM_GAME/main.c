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
	Init();		// �ʱ�ȭ


	/*===========����(q����)============*/
	while (1)
	{
		int nKey = GetKeyEvent();
		if (nKey == 'q')
			break;
		if (nKey == 'r')
		{
			Init();
			StageInit(1);
		}
			

		if (player.dead == FALSE)
		{
			PlayerCollide();
			PlayerMove();
			PlayerAttack();
			AttackTiming();
		}



		Render();	//ȭ�� ���
		WaitRender(clock());
		Update();	//���� üũ
	}

	/*===========����============*/
	Release();
	ScreenRelease();	//����
	return 0;
}


