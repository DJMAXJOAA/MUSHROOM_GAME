#pragma once
char PLAYER_STR[] = "<=O=>";	// �÷��̾��� �����

typedef struct Position
{
	int x, y;	//��ǥ ����
}Position;

typedef struct
{
	Position position;
	char* strPlayer;	// ĳ���͸� ������ ����(���� �Ҵ�)
	int nLength;	// ĳ������ ����
}Player;

Player player;