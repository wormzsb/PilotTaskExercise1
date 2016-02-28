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

void Helper::updateAnalogNewPos(double &x, double &y, int JoyX, int JoyY, double dfTim, int dir) {
	if (!(JoyX == 0 && JoyY == 0)) {
		double rJ = sqrt(JoyX * JoyX + JoyY * JoyY);
		double cosJ = (double)JoyX / rJ;
		double sinJ = (double)JoyY / rJ;
		x += cosJ * rJ  * dfTim * dir;
		y += sinJ * rJ  * dfTim * dir;
	}
}

void Helper::getAnologSpeed(float &sx, float &sy, int JoyX, int JoyY, double dfTim, int dir) {
	if (!(JoyX == 0 && JoyY == 0)) {
		double rJ = sqrt(JoyX * JoyX + JoyY * JoyY);
		double cosJ = (double)JoyX / rJ;
		double sinJ = (double)JoyY / rJ;
		sx = cosJ * rJ  * dfTim * dir;
		sy = sinJ * rJ  * dfTim * dir;
	}
	else {
		sx = sy = 0;
	}
}

