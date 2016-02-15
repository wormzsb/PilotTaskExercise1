#pragma once
#include "Point2.h"
#include <string>
#include "Datatype.h"
#include <map>
#include <string>
using namespace std;
class TaskRec
{
public:
	LONGLONG freq;			// ��ʱƵ��
	int no;					// �������
	double smallBallSpeed;	// �ٶ�
	string smallBalldir;	// �˶�����
	LONGLONG moveBegTime;	// �˶���ʼʱ��
	LONGLONG disappearTime;	// ��ʧʱ��
	LONGLONG pressTime;		// ����ʱ��
	double evaluateTime;	// ����ʱ��(����)
	double biasRate;		// ƫ����(%)
	Point2 smallBallBegCo;	// ��ʼ����
	Point2 targetCo;		// Ŀ������
	Point2 pressSmallBallCo;// ��������
	map <string, bool> flag;//�Զ����־
public:
	TaskRec();
	~TaskRec();
	void setSmallBallDir(int curStartPos);
	bool isFlagExist(string s);
	void setFlag(string s, bool b);
	double getPeriod(LONGLONG t1, LONGLONG t2); // ��λ����
	double getVisiblePeriod();			// �ɼ��˶�ʱ��(����)
	double getObstacle2PressPeriod();	// �����ڵ���������ʱ��
	double getTotalPeriod();			// ʵ��ʱ��
};

