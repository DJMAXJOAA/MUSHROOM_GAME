#pragma once
#include "all_include.h"

/* �Ʒ� 3���� ���� ���۸��� ���� */
void ScreenInit();		// ȭ�� �ʱ�ȭ
void ScreenFlipping();	// ������۸�, 2��ȭ��� 1��ȭ�� �ٲ㼭 ���
void ScreenClear();		// ������ ȭ���� �� ȭ������ �ٲ��ش�
void ScreenRelease(); // ���� ����� �޸� �ʱ�ȭ

static int g_nScreenIndex;
static HANDLE g_hScreen[2];
/* �ý��� ���� ���� �ڵ� ����(������Ʈ �ڵ�)
�Լ��δ� GetStdHandle(STD_OUTPUT_HANDLE)�� ���� */

