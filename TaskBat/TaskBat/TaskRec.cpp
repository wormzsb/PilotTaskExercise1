#include "stdafx.h"
#include "TaskRec.h"


TaskRec::TaskRec()
{
}


TaskRec::~TaskRec()
{
}

void TaskRec::setSmallBallDir(int curStartPos) {
	string &curSmallBallDir = this->smallBalldir;
	switch (curStartPos) {
	case TOP:
		curSmallBallDir = "竖直向下";
		break;
	case RIGHT:
		curSmallBallDir = "水平向左";
		break;
	case BOTTOM:
		curSmallBallDir = "竖直向上";
		break;
	case LEFT:
		curSmallBallDir = "水平向右";
		break;
	}
}


bool TaskRec::isFlagExist(string s) {
	map<string, bool>::iterator it = flag.find(s);
	if (it == flag.end())
		return false;
	else
		return true;
}

void TaskRec::setFlag(string s, bool b) {
	flag[s] = b;
}

double TaskRec::getPeriod(LONGLONG t1, LONGLONG t2) {
	return fabs((double)(t1 - t2))
		/ (double)freq * 1000.;
}

double TaskRec::getVisiblePeriod() {
	return getPeriod(disappearTime, moveBegTime);
}

double TaskRec::getObstacle2PressPeriod() {
	return getPeriod(pressTime, disappearTime);
}

double TaskRec::getTotalPeriod() {
	return getPeriod(pressTime, moveBegTime);
}




