#define _CRT_SECURE_NO_WARNINGS
#include "setting.h"
//#include "create_map.h"

int main()
{
	system("mode con:cols=121 lines=32");	// �ִ� ���α���, ���α���
	/*CreateMap();*/		// �� ���۽� ���������� ����ߴ� �Լ�

	ScreenInit();		// ȭ�� �ʱ�ȭ : ���� 2���� ���� ������۸� �غ�

	Init();				// �ʱ�ȭ : ó���� �ѹ�, �׾��� ��Ƴ�����
	StageInit(stage);	// �ʱ�ȭ : ������������ �ʱ�ȭ
	ConstInit();		// �ʱ�ȭ : �� �ѹ��� �ʱ�ȭ (HP bar)

	/*===========����(q����)============*/
	while (1)
	{
		int nKey = GetKeyEvent();
		if (nKey == 'q' || nKey == 'Q') break;		// QŰ ����
		if (nKey == 'r' || nKey == 'R') { Init(); StageInit(stage);} // R �� ����

		/* ĳ���� ���� �Լ��� */
		Player_HPbar();
		Enemy_HPbar();
		if (player.state == ALIVE)
		{
			PlayerCollide();
			PlayerMove();
			PlayerAttack();
			AttackTiming();
		}
	
		Render();		//ȭ�� ��� (���� main �Լ�)
		PlayerDead();	//���� üũ

		WaitRender(clock());	// CLOCK�ʸ�ŭ ������, ȭ���� �ø��ؼ� ������۸� ����
	}

	/*===========����============*/
	Release();
	ScreenRelease();	//����
	return 0;
}


