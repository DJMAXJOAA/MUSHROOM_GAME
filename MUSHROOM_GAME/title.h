#include "all_include.h"
#include "shop.h"

void TitleSelect();
void Ending();

void TitleSelect()
{
	if (GetAsyncKeyState(VK_RETURN))
	{
		stage = 1;
		Init();
		StageInit(stage);
	}
}

void Ending()
{

}