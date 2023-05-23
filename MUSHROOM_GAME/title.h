#include "all_include.h"
#include "shop.h"

void TitleSelect();

void TitleSelect()
{
	if (GetAsyncKeyState(VK_RETURN))
	{
		stage = 1;
		Init();
		StageInit(stage);
	}
}