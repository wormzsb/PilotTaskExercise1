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
	visiblePeriod = getPeriod(disappearTime, moveBegTime);
	return visiblePeriod;
}

double TaskRec::getObstacle2PressPeriod() {
	obstacle2PressPeriod = getPeriod(pressTime, disappearTime);
	return obstacle2PressPeriod;
}

double TaskRec::getTotalPeriod() {
	totalPeriod = getPeriod(pressTime, moveBegTime);
	return totalPeriod;
}

void TaskRec::setCo(Point2 &p, string str) {
	int indXS = str.find("X=")+2;
	int indXE = str.find(",");
	int indYS = str.find("Y=")+2;
	int indYE = str.find("}");
	
	if (indXS < 2 || indYS < 2)
		return;
	p.x = atof(str.substr(indXS, indXE - indXS).c_str());
	p.y = atof(str.substr(indYS, indYE - indYS).c_str());
}

string TaskRec::getCo(Point2 & p)
{
	stringstream ss;
	ss << "{X=" << p.x << ",Y=" << p.y << "}";
	return ss.str();
}



