#pragma once
/* �Ʒ� 3���� ���� ���۸��� ���� */
void ScreenInit();
void ScreenFlipping();
void ScreenClear();

void ScreenRelease(); // ���� ����� �޸� �ʱ�ȭ
void ScreenPrint(int x, int y, char* string);	// ��ũ�� ������
void SetColor(unsigned short color);	// �� ����