#include "stdafx.h"
#include "math.h"
#include "CStar.h"



int Random(int max)
{
	return (int)((float)max/(float)RAND_MAX*rand());
}

