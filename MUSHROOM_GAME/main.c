#include "setting.h"
#include "create_map.h"

int main()
{
	system("mode con:cols=120 lines=32");
	system("MUSHROOM GAME");
	CreateMap();
	
	ScreenInit();
	Init();		// �ʱ�ȭ


	/*===========����(q����)============*/
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
		}

		Update();	//���� üũ

		Render();	//ȭ�� ���
		WaitRender(clock());
	}

	/*===========����============*/
	Release();
	ScreenRelease();	//����
	return 0;
}


