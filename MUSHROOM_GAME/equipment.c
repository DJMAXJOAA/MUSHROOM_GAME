#include "equipment.h"

which_weapon_use = 0;
now_equipment = 0;

void EquipmentNumber()
{
	/* 장착 선택중이 아닐때 */
	if (ui.state == UI_INVENTORY_DEACTIVE && second_all <= 0)
	{
		if (GetAsyncKeyState(0x30) & 0x8000) EquipmentState(0);
		else if (GetAsyncKeyState(0x31) & 0x8000) EquipmentState(1);
		else if (GetAsyncKeyState(0x32) & 0x8000) EquipmentState(2);
		else if (GetAsyncKeyState(0x33) & 0x8000) EquipmentState(3);
		else if (GetAsyncKeyState(0x34) & 0x8000) EquipmentState(4);
		else if (GetAsyncKeyState(0x35) & 0x8000) EquipmentState(5);
		else if (GetAsyncKeyState(0x36) & 0x8000) EquipmentState(6);
		else if (GetAsyncKeyState(0x37) & 0x8000) EquipmentState(7);
		else if (GetAsyncKeyState(0x38) & 0x8000) EquipmentState(8);
		else if (GetAsyncKeyState(0x39) & 0x8000) EquipmentState(9);
	}
}

void EquipmentState(int select_number)
{
	/* ~번 인벤창이 유효하고, 장착중이 아닐때 */
	if (inventory[select_number].use == TRUE && inventory[select_number].now_equip == FALSE)
	{
		which_weapon_use = select_number;
		ui.state = UI_INVENTORY_ACTIVE;
	}
	second_all = 0.2;
}

void EquipmentItem()
{
	/* Y 누르면 장착 */
	if (GetAsyncKeyState(0x59) & 0x8000)
	{
		ui.MyMaxHP = 100;
		ui.MyAtt = 10;		// 초기값으로
		for (int i = 0; i < 10; i++)
		{
			inventory[i].now_equip = FALSE;	// 모두 장착해제 
		}
		now_equipment = which_weapon_use;
		inventory[which_weapon_use].now_equip = TRUE;

		ui.MyMaxHP += inventory[which_weapon_use].info->hp;
		if (ui.MyHP > ui.MyMaxHP) ui.MyHP = ui.MyMaxHP; // 무기 꼈는데 체력 더 낮아지면 똑같아지게
		ui.MyAtt += inventory[which_weapon_use].info->att;
		
		ui.state = UI_EQUIPMENT;	// 장비창으로
	}

	/* else if S 누르면 판매 */
	else if (GetAsyncKeyState(0x53) & 0x8000)
	{
		inventory_count -= 1;
		ui.Money += inventory[which_weapon_use].info->sell_money;
		inventory[which_weapon_use].use = FALSE;

		ui.state = UI_INVENTORY_DEACTIVE;
	}

	/* else if N 누르면 취소 */
	else if (GetAsyncKeyState(0x4E) & 0x8000)
	{
		ui.state = UI_INVENTORY_DEACTIVE;
	}
}

void AbilityPlus()
{
	if (inventory[now_equipment].now_equip == TRUE)
	{
		ui.MyMaxHP += inventory[now_equipment].info->hp;
		ui.MyAtt += inventory[now_equipment].info->att;
	}
}