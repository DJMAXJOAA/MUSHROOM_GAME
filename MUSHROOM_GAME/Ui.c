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

	/*sprintf(string, "x : %d / y : %d", player.collide.x, player.collide.y);
	PrintScreen(83, 1, string);*/
	sprintf(string, "���� �� : %d", ui.Money);
	PrintScreen(83, 1, string);
	/*sprintf(string, "stage number : %d", stage);
	PrintScreen(83, 3, string);*/

	sprintf(string, "%s", ui.Player_Name);
	PrintScreen(83, 3, string);
	sprintf(string, "%s", ui.Player_HPbar);
	PrintScreen(98, 3, string);
	sprintf(string, "HP:%.1lf / %.1lf", ui.MyHP, ui.MyMaxHP);
	PrintScreen(83, 4, string);
	sprintf(string, "::: ATT:%.1lf", ui.MyAtt);
	PrintScreen(105, 4, string);

	sprintf(string, "%s", enemy_target->name);
	PrintScreen(83, 6, string);
	sprintf(string, "%s", ui.Enemy_HPbar);
	PrintScreen(98, 6, string);
	sprintf(string, "HP:%.1lf / %.1lf", enemy_target->hp, enemy_target->maxhp);
	PrintScreen(83, 7, string);
	sprintf(string, "::: ATT:%.1lf", ui.EnemyAtt);
	PrintScreen(105, 7, string);

	/* �˸� UI */
		/* ����â */
	if (player.state == DISAPPEAR)	
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
		else if (C <= shop.rank && shop.rank <= S)
		{
			sprintf(string, "���%c : %s ", inventory[shop_result].info->rank, inventory[shop_result].info->name);
			PrintScreen(83, 14, string);
			sprintf(string, "%s ",inventory[shop_result].info->data);
			PrintScreen(83, 15, string);
		}
		else
		{
			PrintScreen(83, 14, "����Ű�� �̵�, ���ͷ� ����");
			PrintScreen(83, 15, "S 5%, A 15%, B 30% C 50%");
		}
	}

		/* ���� �˸� UI �κ��丮â �����Ҷ�
		(�̰� ������ ��ֹ��� �ȵǰ� �����ϱ� ���߿�) */
	else if (ui.state == UI_INVENTORY_ACTIVE)	
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
		sprintf(string, "%.lf�������� �־����ϴ�!", ui.MyAtt * ui.CritDMG);
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
		PrintScreen(83, 14, "AŰ�� ���ݽ��� �� FŰ ����(3��)");
		PrintScreen(83, 15, "I �κ��丮 0~9��Ű ����, E ���â");
	}
		
	/* ���â, �κ�â, �����â */
		/* �κ�â, �κ�����â */
	if (ui.state == UI_INVENTORY_DEACTIVE || ui.state == UI_INVENTORY_ACTIVE || stage == ROULETTE) // �귿â �κ�����
	{
		PrintScreen(83, 17, "INVENTORY");
		for (int i = 0; i < 10; i++)
		{
			if (inventory[i].use == TRUE)
			{
				if (inventory[i].now_equip == TRUE) SetColor(YELLOW);	// �������̸� �����
				sprintf(string, "%d.%s %c : ATT+%.1lf HP+%.1lf", i, inventory[i].info->name, inventory[i].info->rank, inventory[i].info->att, inventory[i].info->hp);
				PrintScreen(83, 18 + i, string);
				SetColor(WHITE);
			}
		}
	}
	/* ���â */
	else if (ui.state == UI_EQUIPMENT)
	{
		PrintScreen(83, 17, "EQUIPMENT");
		SetColor(WHITE);
		FilePrintStr("rankX.txt", 86, 18);
		PrintScreen(83, 25, "���� ����X");
		for (int i = 0; i < 10; i++)
		{
			if (inventory[i].now_equip == TRUE)
			{
				if (inventory[i].info->rank == 'S')
				{
					SetColor(VIOLET);
					FilePrintStr("rankS.txt", 86, 18);
				}
				else if (inventory[i].info->rank == 'A')
				{
					SetColor(GREEN);
					FilePrintStr("rankA.txt", 86, 18);
				}
				else if (inventory[i].info->rank == 'B')
				{
					SetColor(SKYBLUE);
					FilePrintStr("rankB.txt", 86, 18);
				}
				else if (inventory[i].info->rank == 'C')
				{
					SetColor(WHITE);
					FilePrintStr("rankC.txt", 86, 18);
				}
				SetColor(WHITE);
				sprintf(string, "%c RANK %s", inventory[i].info->rank, inventory[i].info->name);
				PrintScreen(83, 25, string);
				sprintf(string, "ATT+%.1lf HP+%.1lf", inventory[i].info->att, inventory[i].info->hp);
				PrintScreen(83, 26, string);
				sprintf(string, "%s ", inventory[i].info->data);
				PrintScreen(83, 27, string);
				break;
			}
		}
	}

	/* ��� ���� */
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

void UISelect()
{
	if (GetAsyncKeyState(0x45) & 0x8000)	// EŰ : Equipment ���â
	{
		ui.state = UI_EQUIPMENT;
		second_all = 0.2;
	}
	else if (GetAsyncKeyState(0x49) & 0x8000)	// IŰ : Equipment ���â
	{
		ui.state = UI_INVENTORY_DEACTIVE;
		second_all = 0.2;
	}

	if (ui.state == UI_INVENTORY_DEACTIVE) EquipmentNumber();
	else if (ui.state == UI_INVENTORY_ACTIVE) EquipmentItem();
}