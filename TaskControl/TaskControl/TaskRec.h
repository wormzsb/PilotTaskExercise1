#pragma once
#include "Point2.h"
#include <map>
#include <string>
#include <sstream>
#include <vector>
using namespace std;
class TaskRec
{
public:
	int no;					// 测试序号
	
	// t7 
	double smallBallSpeed;	// 速度
	string smallBalldir;	// 运动方向
	LONGLONG moveBegTime;	// 运动开始时刻
	LONGLONG disappearTime;	// 消失时刻
	LONGLONG pressTime;		// 按键时刻
	//double biasRate;		// 偏差率(%)
	Point2 smallBallBegCo;	// 起始座标
	Point2 targetCo;		// 目标座标
	Point2 pressSmallBallCo;// 按键座标
	map <string, bool> flag;//自定义标志
	double visiblePeriod;			// 可见运动时间(毫秒)
	double obstacle2PressPeriod;	// 进入遮挡到按键的时间
	double totalPeriod;				// 实际时间
	double evaluateTime;			// 估计时间(毫秒)
	double deviationRate;			// 偏差率

	//t8 
	string leftImg;
	string rightImg;
	bool unCoincidence; // 0:重合 1：不能重合
	int btn;			//0：重合 1：不重合 -1：超时
	bool isRight;		// 0: 错误 1：正确
	double responseTime;	// 单位毫秒

public:
	TaskRec();
	~TaskRec();
	void setSmallBallDir(int curStartPos);
	bool isFlagExist(string s);
	void setFlag(string s, bool b);
	void setCo(Point2 &p, string str);
	string getCo(Point2 &p);
};

