#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>	//�ܼ� ����� ���� �������
#include "Screen.h"	// ȭ�� â ���� ���

#include "main.h"
#include "Screen.h"
#include "player.h"

int main()
{
	system("mode con:cols=100 lines=40");
	ScreenInit();
	Init();		// �ʱ�ȭ


	/*===========����(q����)============*/
	while (1)
	{
		int nKey = GetKeyEvent();
		if (nKey == 'q')
			break;
		KeyProcess(nKey);

		Update();	//������ ����

		Render();	//ȭ�� ���
		WaitRender(clock());
	}

	/*===========����============*/
	Release();
	ScreenRelease();	//����
	return 0;
}


/*===========�ʱ�ȭ(�ʱ� ����)============*/
void Init()
{

	player.position.x = 0;
	player.position.y = 22;

	player.nLength = strlen(PLAYER_STR);

	player.strPlayer = (char*)malloc(sizeof(char) * player.nLength);
	strcpy(player.strPlayer, PLAYER_STR);
}

/*===========�����Ͱ���============*/
void Update()
{

}

/*===========ȭ�����, ȭ�鿡 ��Ÿ���� �͵�============*/
void Render()
{
	ScreenClear();
/*������������������������������������������������������������������������������������������������������������������������������������������*/

	char string[100] = { 0 };

	ScreenPrint(player.position.x, player.position.y, player.strPlayer);

	sprintf(string, "���ΰ� �̵� ��ǥ : %d, %d", player.position.x, player.position.y);
	ScreenPrint(0, 3, string);	// ��ǥ ǥ��â ���?

/*������������������������������������������������������������������������������������������������������������������������������������������*/
	ScreenFlipping();
}

/*===========ȭ�������ð� 33ms============*/
void WaitRender(clock_t OldTime)
{
	clock_t CurTime;	//clock_t ����ð� ����
	while (1)
	{
		CurTime = clock();
		if (CurTime - OldTime > 33)
			break;
	}
}

/*===========�Ҵ�����============*/
void Release()	//����
{

}

/*===========Ű�Է°���============*/
int GetKeyEvent()
{
	if (_kbhit())	//_kbhit : Ű���尡 �������� Ȯ���ϴ� �Լ�
		return _getch();	//���� ���� ��ȯ

	return -1;
}

/*===========ĳ���� �̵�============*/
void KeyProcess(int key)
{
	switch (key)
	{
	case 'a':
		if (player.position.x > 0)
		{
			player.position.x--;
		}
		break;
	case 'd':
		if (player.position.x < 100)
		{
			player.position.x++;
		}
		break;
	case 'w':
		if (player.position.y > 0)
		{
			player.position.y--;
		}
		break;
	case 's':
		if (player.position.y < 40)
		{
			player.position.y++;
		}
		break;
	}
}