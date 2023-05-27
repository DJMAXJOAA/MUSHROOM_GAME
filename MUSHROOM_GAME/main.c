#define _CRT_SECURE_NO_WARNINGS
#include "setting.h"
//#include "create_map.h"

int main()
{
	system("mode con:cols=121 lines=32");	// 최대 가로길이, 세로길이
	/*CreateMap();*/		// 맵 제작시 보조적으로 사용했던 함수

	ScreenInit();		// 화면 초기화 : 버퍼 2개를 만들어서 더블버퍼링 준비

	Init();				// 초기화 : 처음에 한번, 죽었다 살아났을때
	StageInit(stage);	// 초기화 : 스테이지마다 초기화
	ConstInit();		// 초기화 : 딱 한번만 초기화 (HP bar)

	/*===========시작(q종료)============*/
	while (1)
	{
		int nKey = GetKeyEvent();
		if (nKey == 'q' || nKey == 'Q') break;		// Q키 강종
		if (nKey == 'r' || nKey == 'R') { Init(); StageInit(stage);} // R 맵 리셋

		/* 캐릭터 관련 함수들 */
		Player_HPbar();
		Enemy_HPbar();
		if (player.state == ALIVE)
		{
			PlayerCollide();
			PlayerMove();
			PlayerAttack();
			AttackTiming();
		}
	
		Render();		//화면 출력 (실제 main 함수)
		PlayerDead();	//죽음 체크

		WaitRender(clock());	// CLOCK초만큼 지나면, 화면을 플립해서 더블버퍼링 구현
	}

	/*===========종료============*/
	Release();
	ScreenRelease();	//해제
	return 0;
}


