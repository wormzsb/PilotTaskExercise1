#pragma once
#include "Datatype.h"
#include <algorithm>
using namespace std;
class Helper
{
public:
	Helper();
	~Helper();

	static double getDis(Point p1, Point p2);
	void updateAnalogNewPos(double &x, double &y, int JoyX, int JoyY, double dfTim, int dir);
	void getAnologSpeed(float & sx, float & sy, int JoyX, int JoyY, double dfTim, int dir);
};

