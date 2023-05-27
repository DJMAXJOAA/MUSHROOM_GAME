#include "UI.h"

UI* p_ui = &ui;

void InitNotice()
{
	notice.Critical = 0;
	notice.HitEnemy = FALSE;
	notice.Damaged = FALSE;
	notice.GetMoney = FALSE;
	notice.Danger = FALSE;
	notice.CollideEnemy = FALSE;
}


void Player_HPbar()
{
	if (ui.MyHP / ui.MyMaxHP > 0.9) strcpy(ui.Player_HPbar, "�����������");
	else if (ui.MyHP / ui.MyMaxHP > 0.8 && ui.MyHP / ui.MyMaxHP <= 0.9) strcpy(ui.Player_HPbar, "�����������");
	else if (ui.MyHP / ui.MyMaxHP > 0.7 && ui.MyHP / ui.MyMaxHP <= 0.8) strcpy(ui.Player_HPbar, "�����������");
	else if (ui.MyHP / ui.MyMaxHP > 0.6 && ui.MyHP / ui.MyMaxHP <= 0.7) strcpy(ui.Player_HPbar, "�����������");
	else if (ui.MyHP / ui.MyMaxHP > 0.5 && ui.MyHP / ui.MyMaxHP <= 0.6) strcpy(ui.Player_HPbar, "�����������");
	else if (ui.MyHP / ui.MyMaxHP > 0.4 && ui.MyHP / ui.MyMaxHP <= 0.5) strcpy(ui.Player_HPbar, "�����������");
	else if (ui.MyHP / ui.MyMaxHP > 0.3 && ui.MyHP / ui.MyMaxHP <= 0.4) strcpy(ui.Player_HPbar, "�����������");
	else if (ui.MyHP / ui.MyMaxHP > 0.2 && ui.MyHP / ui.MyMaxHP <= 0.3) strcpy(ui.Player_HPbar, "�����������");
	else if (ui.MyHP / ui.MyMaxHP > 0.1 && ui.MyHP / ui.MyMaxHP <= 0.2) strcpy(ui.Player_HPbar, "�����������");
	else if (ui.MyHP / ui.MyMaxHP > 0 && ui.MyHP / ui.MyMaxHP <= 0.1) strcpy(ui.Player_HPbar, "�����������");
	if (ui.MyHP / ui.MyMaxHP <= 0) strcpy(ui.Player_HPbar, "�����������");
}

void Enemy_HPbar()
{
	if (enemy_target->hp / enemy_target->maxhp > 0.9) strcpy(ui.Enemy_HPbar, "�����������");
	else if (enemy_target->hp / enemy_target->maxhp > 0.8 && enemy_target->hp / enemy_target->maxhp <= 0.9) strcpy(ui.Enemy_HPbar, "�����������");
	else if (enemy_target->hp / enemy_target->maxhp > 0.7 && enemy_target->hp / enemy_target->maxhp <= 0.8) strcpy(ui.Enemy_HPbar, "�����������");
	else if (enemy_target->hp / enemy_target->maxhp > 0.6 && enemy_target->hp / enemy_target->maxhp <= 0.7) strcpy(ui.Enemy_HPbar, "�����������");
	else if (enemy_target->hp / enemy_target->maxhp > 0.5 && enemy_target->hp / enemy_target->maxhp <= 0.6) strcpy(ui.Enemy_HPbar, "�����������");
	else if (enemy_target->hp / enemy_target->maxhp > 0.4 && enemy_target->hp / enemy_target->maxhp <= 0.5) strcpy(ui.Enemy_HPbar, "�����������");
	else if (enemy_target->hp / enemy_target->maxhp > 0.3 && enemy_target->hp / enemy_target->maxhp <= 0.4) strcpy(ui.Enemy_HPbar, "�����������");
	else if (enemy_target->hp / enemy_target->maxhp > 0.2 && enemy_target->hp / enemy_target->maxhp <= 0.3) strcpy(ui.Enemy_HPbar, "�����������");
	else if (enemy_target->hp / enemy_target->maxhp > 0.1 && enemy_target->hp / enemy_target->maxhp <= 0.2) strcpy(ui.Enemy_HPbar, "�����������");
	else if (enemy_target->hp / enemy_target->maxhp > 0 && enemy_target->hp / enemy_target->maxhp <= 0.1) strcpy(ui.Enemy_HPbar, "�����������");
	if (enemy_target->hp / enemy_target->maxhp <= 0) strcpy(ui.Enemy_HPbar, "�����������");
}


void TotalUI()
{
	char string[100];
	for (int i = 0; i < WIDTH; i++)
	{
		PrintScreen(ui.position.x, ui.position.y + i, "��");
	}
	for (int i = 1; i < HEIGHT; i++)
	{
		PrintScreen(ui.position.x + i, 9, "��");
		PrintScreen(ui.position.x + i, 13, "��");
		PrintScreen(ui.position.x + i, 16, "��");
		PrintScreen(ui.position.x + i, 28, "��");
	}

	sprintf(string, "x : %d / y : %d", player.collide.x, player.collide.y);
	PrintScreen(83, 1, string);
	sprintf(string, "���� �� : %d", ui.Money);
	PrintScreen(83, 2, string);
	sprintf(string, "stage number : %d", stage);
	PrintScreen(83, 3, string);

	sprintf(string, "%s\t%s", ui.Player_Name, ui.Player_HPbar);
	PrintScreen(83, 4, string);
	sprintf(string, "HP:%.1lf - MAXHP:%.1lf / ATT:%.1lf\t", ui.MyHP, ui.MyMaxHP, ui.MyAtt);
	PrintScreen(83, 5, string);
	sprintf(string, "%s\t%s", enemy_target->name, ui.Enemy_HPbar);
	PrintScreen(83, 6, string);
	sprintf(string, "HP:%.1lf / ATT:%.1lf\t", ui.EnemyHP, ui.EnemyAtt);
	PrintScreen(83, 7, string);

	if (player.state == DISAPPEAR)	// ���� �ȿ����� �������̽�
	{
		if (shop.select == 1 && ui.Money < 200)
		{
			PrintScreen(83, 14, "���� �����մϴ�!!");
		}
		else if (inventory_count == 10)
		{
			PrintScreen(83, 14, "�κ��丮�� ��á���ϴ�!");
			PrintScreen(83, 15, "�������� �Ǹ����ּ���.");
		}
		else if (shop.rank == S)
		{
			PrintScreen(83, 14, "���S : 5%");
			PrintScreen(83, 15, "Ȯ���� Ư���� �ɷ��� �ֽ��ϴ�!");
		}
		else if (shop.rank == A)
		{
			PrintScreen(83, 14, "���A : 10%");
			PrintScreen(83, 15, "�ɱ� Ư���� �ɷ��� �ֽ��ϴ�.");
		}
		else if (shop.rank == B)
		{
			PrintScreen(83, 14, "���B : 35%");
			PrintScreen(83, 15, "C ���⺸�ٴ� ��¦ �����ϴ�.");
		}
		else if (shop.rank == C)
		{
			PrintScreen(83, 14, "���C : 50%");
			PrintScreen(83, 15, "������ ����� �����Դϴ�.");
		}
		else
		{
			PrintScreen(83, 14, "����Ű�� �̵�, ���ͷ� ����");
			PrintScreen(83, 15, "S 5%, A 15%, B 30% C 50%");
		}
	}
	else if (ui.state == TRUE)	// �κ��丮â �����Ҷ�(�̰� ������ ��ֹ��� �ȵǰ� �����ϱ� ���߿�)
	{
		sprintf(string, "%d.%s ���� : �ǸŰ� %d��", which_weapon_use, inventory[which_weapon_use].info->name, inventory[which_weapon_use].info->sell_money);
		PrintScreen(83, 14, string);
		PrintScreen(83, 15, "Y ����, S �Ǹ�, N ���");
	}
	else if (notice.Danger == TRUE)	// ��ֹ��� ��� ���� ��
	{
		PrintScreen(83, 14, "��ֹ��� ��� �־��. �����ϼ���!");
	}
	else if (notice.CollideEnemy == TRUE)	// ���� Ÿ����
	{
		PrintScreen(83, 14, enemy_target->name);
		PrintScreen(83, 15, enemy_target->info);
	}
	else if (notice.GetMoney == TRUE)	// ���� ��� ���� ����� ��
	{
		sprintf(string, "������ ĳ�� %d���� ������ϴ�!", notice.temp_money);
		PrintScreen(83, 14, string);
	}
	else if (notice.Critical >= 1)	// ��Ȯ�� Ÿ�ֿ̹� ���� ����
	{
		sprintf(string, "ũ��Ƽ��!! %d COMBO", notice.Critical);
		PrintScreen(83, 14, string);
		sprintf(string, "%.lf�������� �־����ϴ�!", ui.MyAtt * 1.5);
		PrintScreen(83, 15, string);
	}
	else if (notice.HitEnemy == TRUE)	// ���� ����
	{
		sprintf(string, "Ÿ�� ����! %.lf�������� �־����ϴ�!", ui.MyAtt);
		PrintScreen(83, 14, string);
	}
	else if (notice.Damaged == TRUE)	// Ÿ�̹��� �����缭 �������� �޾��� ��
	{
		sprintf(string, "���̰�! %.lf�������� �޾ҽ��ϴ� �̤�", enemy_target->att);
		PrintScreen(83, 14, string);
	}
	else
	{
		PrintScreen(83, 14, "AŰ  ���ݽ���");
		PrintScreen(83, 15, "Ÿ�̹� ���缭 FŰ ����(ũ��Ƽ�� x1.5)");
	}
		
	for (int i = 0; i < 10; i++)
	{
		if (inventory[i].use == TRUE)
		{
			if (inventory[i].now_equip == TRUE) SetColor(YELLOW);	// �������̸� �����
			sprintf(string, "%d.%s %c : ATT+%.1lf HP+%.1lf", i, inventory[i].info->name, inventory[i].info->rank, inventory[i].info->att, inventory[i].info->hp);
			PrintScreen(83, 17 + i, string);
			SetColor(WHITE);
		}
	}

	if (player.state == DEAD)
	{
		PrintScreen(83, 29, "����� �׾����ϴ�! �� ��Ȱ�մϴ�");
		sprintf(string, "���� ������ �ð� : %.1lf��", ui.respawn);
		PrintScreen(83, 30, string);
	}
	else if (ui.MyHP / ui.MyMaxHP <= 0.25)
	{
		PrintScreen(83, 29, "ü���� �����ϴ�.");
		PrintScreen(83, 30, "ü���� ȸ���ϼ���!!");
	}
}