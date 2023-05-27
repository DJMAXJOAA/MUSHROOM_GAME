#include "inventory.h"

Inventory inventory[10];

void AddInventory()
{
	inventory_count += 1;
	int temp = Random(0, 2);
	for (int i = 0; i < 10; i++)
	{
		if (inventory[i].use == FALSE)
		{
			if (shop.rank == S)
			{
				inventory[i].info = &item_S[temp];
				inventory[i].use = TRUE;
				break;
			}
			else if (shop.rank == A)
			{
				inventory[i].info = &item_A[temp];
				inventory[i].use = TRUE;
				break;
			}
			else if (shop.rank == B)
			{
				inventory[i].info = &item_B[temp];
				inventory[i].use = TRUE;
				break;
			}
			else
			{
				inventory[i].info = &item_C[temp];
				inventory[i].use = TRUE;
				break;
			}
		}
	}
}
