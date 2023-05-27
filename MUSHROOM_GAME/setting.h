#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define CLOCK 20	// 프레임당 밀리초

#include "all_include.h"
#include "shop.h"

const double fps;
static char string[100];

/* 초기화 관련 */
int ConstInit();					// 딱 처음 한번만 초기화(변하지 말아야 할것들)
int Init();						// 죽었을때 초기화(초기 설정, 변하지 않는 것들)

int StageInit(int stage_number);	// 맵별 초기화(맵별로 다름. 몇번맵?)

/* 실제 동작부 */
void Render();						// 화면 출력

void MapObject();					// 맵 뒷배경 (사실상 씬)
void PlayerControl();			// 1. 플레이어 관련 함수
void MapInit(int(*map)[HEIGHT]);	// 맵 배열 생성(벽, 장애물, 포탈, NPC 등등 생성)
void TotalUI();					// 2. UI 관련 함수

/* 화면 관련 */
int WaitRender(clock_t OldTime);	// 화면 지연시간
void Release();						// 할당 해제(프로그램 종료)
int GetKeyEvent();					// 키 입력받기(인벤창, 종료, 리셋 등)

void TitleSelect();				// 타이틀 선택