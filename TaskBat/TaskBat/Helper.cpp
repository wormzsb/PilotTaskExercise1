#include "stdafx.h"
#include "Helper.h"


Helper::Helper()
{
}


Helper::~Helper()
{
}

double Helper::getDis(Point p1, Point p2) {
	double dx = p1.dX - p2.dX;
	double dy = p1.dY - p2.dY;
	return sqrt(dx * dx + dy * dy);
}

