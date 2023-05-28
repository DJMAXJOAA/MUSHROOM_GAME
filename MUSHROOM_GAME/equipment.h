#pragma once
#include "all_include.h"
#include "inventory.h"
#include "player.h"
#include "UI.h"

int which_weapon_use;	// 몇번 장비 선택?
int now_equipment;		// 지금 착용중인 장비

void EquipmentNumber();
void EquipmentState(int select_number);
void EquipmentItem();
void AbilityPlus();