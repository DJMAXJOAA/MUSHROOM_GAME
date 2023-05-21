#pragma once
#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <malloc.h>
#include <stralign.h>

double random(int range_min, int range_max)
{
	srand((unsigned int)time(NULL));
	double random = rand() % (range_max - range_min + 1) + range_min;
	return random;
}