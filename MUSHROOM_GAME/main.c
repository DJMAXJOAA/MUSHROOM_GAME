#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>	//�ܼ� ����� ���� �������

void Init()	//�ʱ�ȭ
{

}

void Update() //������ ����
{

}

void Render() //ȭ�� ���
{
	ScreenClear();
	// ����ڵ�
	ScreenFlipping();
}

void Release()	//����
{

}

int main()
{
	int nKey;
	clock_t CurTime, OldTime;	//clock_t ����ð� ����

	ScreenInit();
	Init();	// �ʱ�ȭ

	/* ESC : ���� */
	while (1)
	{
		if (_kbhit()) //_kbhit : Ű���尡 �������� Ȯ���ϴ� �Լ�
		{
			nKey = _getch();	//���� ���� ��ȯ
			if (nKey == 27) break;
			switch (nKey)
			{
			case 'j': break;
			case 'l': break;
			}
		}

		OldTime = clock();	//���α׷� ���� �� ���� ƽ �� ��ȯ
		Update();	//������ ����
		Render(); //ȭ�� ���
		while (1)
		{
			CurTime = clock();
			if (CurTime - OldTime > 33) break;
		}

	}
	Release();
	ScreenRelease();	//����
	return 0;
}