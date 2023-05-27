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
	if (ui.MyHP / ui.MyMaxHP > 0.9) strcpy(ui.Player_HPbar, "■■■■■■■■■■");
	else if (ui.MyHP / ui.MyMaxHP > 0.8 && ui.MyHP / ui.MyMaxHP <= 0.9) strcpy(ui.Player_HPbar, "■■■■■■■■■□");
	else if (ui.MyHP / ui.MyMaxHP > 0.7 && ui.MyHP / ui.MyMaxHP <= 0.8) strcpy(ui.Player_HPbar, "■■■■■■■■□□");
	else if (ui.MyHP / ui.MyMaxHP > 0.6 && ui.MyHP / ui.MyMaxHP <= 0.7) strcpy(ui.Player_HPbar, "■■■■■■■□□□");
	else if (ui.MyHP / ui.MyMaxHP > 0.5 && ui.MyHP / ui.MyMaxHP <= 0.6) strcpy(ui.Player_HPbar, "■■■■■■□□□□");
	else if (ui.MyHP / ui.MyMaxHP > 0.4 && ui.MyHP / ui.MyMaxHP <= 0.5) strcpy(ui.Player_HPbar, "■■■■■□□□□□");
	else if (ui.MyHP / ui.MyMaxHP > 0.3 && ui.MyHP / ui.MyMaxHP <= 0.4) strcpy(ui.Player_HPbar, "■■■■□□□□□□");
	else if (ui.MyHP / ui.MyMaxHP > 0.2 && ui.MyHP / ui.MyMaxHP <= 0.3) strcpy(ui.Player_HPbar, "■■■□□□□□□□");
	else if (ui.MyHP / ui.MyMaxHP > 0.1 && ui.MyHP / ui.MyMaxHP <= 0.2) strcpy(ui.Player_HPbar, "■■□□□□□□□□");
	else if (ui.MyHP / ui.MyMaxHP > 0 && ui.MyHP / ui.MyMaxHP <= 0.1) strcpy(ui.Player_HPbar, "■□□□□□□□□□");
	if (ui.MyHP / ui.MyMaxHP <= 0) strcpy(ui.Player_HPbar, "□□□□□□□□□□");
}

void Enemy_HPbar()
{
	if (enemy_target->hp / enemy_target->maxhp > 0.9) strcpy(ui.Enemy_HPbar, "■■■■■■■■■■");
	else if (enemy_target->hp / enemy_target->maxhp > 0.8 && enemy_target->hp / enemy_target->maxhp <= 0.9) strcpy(ui.Enemy_HPbar, "■■■■■■■■■□");
	else if (enemy_target->hp / enemy_target->maxhp > 0.7 && enemy_target->hp / enemy_target->maxhp <= 0.8) strcpy(ui.Enemy_HPbar, "■■■■■■■■□□");
	else if (enemy_target->hp / enemy_target->maxhp > 0.6 && enemy_target->hp / enemy_target->maxhp <= 0.7) strcpy(ui.Enemy_HPbar, "■■■■■■■□□□");
	else if (enemy_target->hp / enemy_target->maxhp > 0.5 && enemy_target->hp / enemy_target->maxhp <= 0.6) strcpy(ui.Enemy_HPbar, "■■■■■■□□□□");
	else if (enemy_target->hp / enemy_target->maxhp > 0.4 && enemy_target->hp / enemy_target->maxhp <= 0.5) strcpy(ui.Enemy_HPbar, "■■■■■□□□□□");
	else if (enemy_target->hp / enemy_target->maxhp > 0.3 && enemy_target->hp / enemy_target->maxhp <= 0.4) strcpy(ui.Enemy_HPbar, "■■■■□□□□□□");
	else if (enemy_target->hp / enemy_target->maxhp > 0.2 && enemy_target->hp / enemy_target->maxhp <= 0.3) strcpy(ui.Enemy_HPbar, "■■■□□□□□□□");
	else if (enemy_target->hp / enemy_target->maxhp > 0.1 && enemy_target->hp / enemy_target->maxhp <= 0.2) strcpy(ui.Enemy_HPbar, "■■□□□□□□□□");
	else if (enemy_target->hp / enemy_target->maxhp > 0 && enemy_target->hp / enemy_target->maxhp <= 0.1) strcpy(ui.Enemy_HPbar, "■□□□□□□□□□");
	if (enemy_target->hp / enemy_target->maxhp <= 0) strcpy(ui.Enemy_HPbar, "□□□□□□□□□□");
}


void TotalUI()
{
	char string[100];
	for (int i = 0; i < WIDTH; i++)
	{
		PrintScreen(ui.position.x, ui.position.y + i, "┃");
	}
	for (int i = 1; i < HEIGHT; i++)
	{
		PrintScreen(ui.position.x + i, 9, "━");
		PrintScreen(ui.position.x + i, 13, "━");
		PrintScreen(ui.position.x + i, 16, "━");
		PrintScreen(ui.position.x + i, 28, "…");
	}

	sprintf(string, "x : %d / y : %d", player.collide.x, player.collide.y);
	PrintScreen(83, 1, string);
	sprintf(string, "보유 돈 : %d", ui.Money);
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

	if (player.state == DISAPPEAR)	// 상점 안에서의 인터페이스
	{
		if (shop.select == 1 && ui.Money < 200)
		{
			PrintScreen(83, 14, "돈이 부족합니다!!");
		}
		else if (inventory_count == 10)
		{
			PrintScreen(83, 14, "인벤토리가 꽉찼습니다!");
			PrintScreen(83, 15, "아이템을 판매해주세요.");
		}
		else if (shop.rank == S)
		{
			PrintScreen(83, 14, "등급S : 5%");
			PrintScreen(83, 15, "확실히 특별한 능력이 있습니다!");
		}
		else if (shop.rank == A)
		{
			PrintScreen(83, 14, "등급A : 10%");
			PrintScreen(83, 15, "쪼금 특별한 능력이 있습니다.");
		}
		else if (shop.rank == B)
		{
			PrintScreen(83, 14, "등급B : 35%");
			PrintScreen(83, 15, "C 무기보다는 살짝 좋습니다.");
		}
		else if (shop.rank == C)
		{
			PrintScreen(83, 14, "등급C : 50%");
			PrintScreen(83, 15, "지극히 평범한 무기입니다.");
		}
		else
		{
			PrintScreen(83, 14, "방향키로 이동, 엔터로 선택");
			PrintScreen(83, 15, "S 5%, A 15%, B 30% C 50%");
		}
	}
	else if (ui.state == TRUE)	// 인벤토리창 수정할때(이거 전투나 장애물때 안되게 수정하기 나중에)
	{
		sprintf(string, "%d.%s 선택 : 판매가 %d원", which_weapon_use, inventory[which_weapon_use].info->name, inventory[which_weapon_use].info->sell_money);
		PrintScreen(83, 14, string);
		PrintScreen(83, 15, "Y 장착, S 판매, N 취소");
	}
	else if (notice.Danger == TRUE)	// 장애물에 닿고 있을 때
	{
		PrintScreen(83, 14, "장애물에 닿고 있어요. 조심하세요!");
	}
	else if (notice.CollideEnemy == TRUE)	// 적군 타게팅
	{
		PrintScreen(83, 14, enemy_target->name);
		PrintScreen(83, 15, enemy_target->info);
	}
	else if (notice.GetMoney == TRUE)	// 적을 잡고 돈을 얻었을 때
	{
		sprintf(string, "광물을 캐고 %d원을 얻었습니다!", notice.temp_money);
		PrintScreen(83, 14, string);
	}
	else if (notice.Critical >= 1)	// 정확한 타이밍에 공격 성공
	{
		sprintf(string, "크리티컬!! %d COMBO", notice.Critical);
		PrintScreen(83, 14, string);
		sprintf(string, "%.lf데미지를 주었습니다!", ui.MyAtt * 1.5);
		PrintScreen(83, 15, string);
	}
	else if (notice.HitEnemy == TRUE)	// 공격 성공
	{
		sprintf(string, "타격 성공! %.lf데미지를 주었습니다!", ui.MyAtt);
		PrintScreen(83, 14, string);
	}
	else if (notice.Damaged == TRUE)	// 타이밍을 못맞춰서 데미지를 받았을 때
	{
		sprintf(string, "아이고! %.lf데미지를 받았습니다 ㅜㅜ", enemy_target->att);
		PrintScreen(83, 14, string);
	}
	else
	{
		PrintScreen(83, 14, "A키  공격시작");
		PrintScreen(83, 15, "타이밍 맞춰서 F키 공격(크리티컬 x1.5)");
	}
		
	for (int i = 0; i < 10; i++)
	{
		if (inventory[i].use == TRUE)
		{
			if (inventory[i].now_equip == TRUE) SetColor(YELLOW);	// 장착중이면 노란색
			sprintf(string, "%d.%s %c : ATT+%.1lf HP+%.1lf", i, inventory[i].info->name, inventory[i].info->rank, inventory[i].info->att, inventory[i].info->hp);
			PrintScreen(83, 17 + i, string);
			SetColor(WHITE);
		}
	}

	if (player.state == DEAD)
	{
		PrintScreen(83, 29, "당신은 죽었습니다! 곧 부활합니다");
		sprintf(string, "남은 리스폰 시간 : %.1lf초", ui.respawn);
		PrintScreen(83, 30, string);
	}
	else if (ui.MyHP / ui.MyMaxHP <= 0.25)
	{
		PrintScreen(83, 29, "체력이 낮습니다.");
		PrintScreen(83, 30, "체력을 회복하세요!!");
	}
}