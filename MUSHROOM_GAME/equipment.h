#pragma once
#include "all_include.h"
#include "inventory.h"
#include "player.h"
#include "UI.h"

int which_weapon_use;	// ��� ��� ����?
int now_equipment;		// ���� �������� ���

void EquipmentNumber();
void EquipmentState(int select_number);
void EquipmentItem();
void AbilityPlus();