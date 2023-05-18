#pragma once
/* 아래 3개로 더블 버퍼링을 구현 */
void ScreenInit();
void ScreenFlipping();
void ScreenClear();

void ScreenRelease(); // 게임 종료시 메모리 초기화
void ScreenPrint(int x, int y, char* string);	// 스크린 사이즈
void SetColor(unsigned short color);	// 색 설정