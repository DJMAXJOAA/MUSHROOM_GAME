#pragma once
#include "all_include.h"

/* 아래 3개로 더블 버퍼링을 구현 */
void ScreenInit();		// 화면 초기화
void ScreenFlipping();	// 더블버퍼링, 2번화면과 1변화면 바꿔서 출력
void ScreenClear();		// 렌더링 화면을 빈 화면으로 바꿔준다
void ScreenRelease(); // 게임 종료시 메모리 초기화

static int g_nScreenIndex;
static HANDLE g_hScreen[2];
/* 시스템 접근 위한 핸들 설정(오브젝트 핸들)
함수로는 GetStdHandle(STD_OUTPUT_HANDLE)도 가능 */

