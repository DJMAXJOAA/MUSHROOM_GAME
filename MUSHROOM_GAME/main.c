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

void Release()	//����
{

}

int GetKeyEvent()
{
	if (_kbhit())	//_kbhit : Ű���尡 �������� Ȯ���ϴ� �Լ�
		return _getch();	//���� ���� ��ȯ

	return -1;
}

void KeyProcess(int key)
{
	switch (key)
	{
	case 'i':
		break;
	case 'j':
		break;
	}
}

int main()
{
	ScreenInit();
	Init();		// �ʱ�ȭ

	/* q : ���� */
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
	Release();
	ScreenRelease();	//����
	return 0;
}