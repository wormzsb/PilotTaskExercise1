#pragma once
#include "Point2.h"
#include <string>
#include "datatype.h"
#include <map>
#include <string>
using namespace std;
class TaskRec
{
public:
	LONGLONG freq;			// 计时频率
	int no;					// 测试序号
	double smallBallSpeed;	// 速度
	string smallBalldir;	// 运动方向
	LONGLONG moveBegTime;	// 运动开始时刻
	LONGLONG disappearTime;	// 消失时刻
	LONGLONG pressTime;		// 按键时刻
	//double biasRate;		// 偏差率(%)
	Point2 smallBallBegCo;	// 起始坐标
	Point2 targetCo;		// 目标坐标
	Point2 pressSmallBallCo;// 按键坐标
	map <string, bool> flag;//自定义标志
	// 以下读取记录时用：
	double visiblePeriod;			// 可见运动时间(毫秒)
	double obstacle2PressPeriod;	// 进入遮挡到按键的时间
	double totalPeriod;				// 实际时间
	double evaluateTime;			// 估计时间(毫秒)
	double deviationRate;			// 偏差率
public:
	TaskRec();
	~TaskRec();
	void setSmallBallDir(int curStartPos);
	bool isFlagExist(string s);
	void setFlag(string s, bool b);
	double getPeriod(LONGLONG t1, LONGLONG t2); // 单位毫秒
	double getVisiblePeriod();			// 可见运动时间(毫秒)
	double getObstacle2PressPeriod();	// 进入遮挡到按键的时间
	double getTotalPeriod();			// 实际时间
	void setCo(Point2 &p, string str);
};

