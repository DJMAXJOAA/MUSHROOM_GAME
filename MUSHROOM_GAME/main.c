#include "setting.h"

int main()
{
	system("mode con:cols=120 lines=40");
	system("MUSHROOM GAME");
	ScreenInit();
	Init();		// 초기화


	/*===========시작(q종료)============*/
	while (1)
	{
		int nKey = GetKeyEvent();
		if (nKey == 'q')
			break;

		PlayerMove();
		CanAttack();
			

		Update();	//데이터 갱신

		Render();	//화면 출력
		WaitRender(clock());
	}

	/*===========종료============*/
	Release();
	ScreenRelease();	//해제
	return 0;
}


