#include "setting.h"

int main()
{
	system("mode con:cols=120 lines=40");
	system("MUSHROOM GAME");
	ScreenInit();
	Init();		// �ʱ�ȭ


	/*===========����(q����)============*/
	while (1)
	{
		int nKey = GetKeyEvent();
		if (nKey == 'q')
			break;

		PlayerMove();
		CanAttack();
			

		Update();	//������ ����

		Render();	//ȭ�� ���
		WaitRender(clock());
	}

	/*===========����============*/
	Release();
	ScreenRelease();	//����
	return 0;
}


