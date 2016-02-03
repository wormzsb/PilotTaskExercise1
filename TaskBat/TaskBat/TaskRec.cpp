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
		curSmallBallDir = "��ֱ����";
		break;
	case RIGHT:
		curSmallBallDir = "ˮƽ����";
		break;
	case BOTTOM:
		curSmallBallDir = "��ֱ����";
		break;
	case LEFT:
		curSmallBallDir = "ˮƽ����";
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




