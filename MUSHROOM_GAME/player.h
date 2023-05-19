#pragma once
char PLAYER_STR[] = "<=O=>";	// 플레이어의 생김새

typedef struct Position
{
	int x, y;	//좌표 설정
}Position;

typedef struct
{
	Position position;
	char* strPlayer;	// 캐릭터를 포인터 설정(동적 할당)
	int nLength;	// 캐릭터의 길이
}Player;

Player player;