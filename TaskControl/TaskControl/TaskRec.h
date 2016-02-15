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
	int no;					// �������
	
	// t7 
	double smallBallSpeed;	// �ٶ�
	string smallBalldir;	// �˶�����
	LONGLONG moveBegTime;	// �˶���ʼʱ��
	LONGLONG disappearTime;	// ��ʧʱ��
	LONGLONG pressTime;		// ����ʱ��
	//double biasRate;		// ƫ����(%)
	Point2 smallBallBegCo;	// ��ʼ����
	Point2 targetCo;		// Ŀ������
	Point2 pressSmallBallCo;// ��������
	map <string, bool> flag;//�Զ����־
	double visiblePeriod;			// �ɼ��˶�ʱ��(����)
	double obstacle2PressPeriod;	// �����ڵ���������ʱ��
	double totalPeriod;				// ʵ��ʱ��
	double evaluateTime;			// ����ʱ��(����)
	double deviationRate;			// ƫ����

	//t8 
	string leftImg;
	string rightImg;
	bool unCoincidence; // 0:�غ� 1�������غ�
	int btn;			//0���غ� 1�����غ� -1����ʱ
	bool isRight;		// 0: ���� 1����ȷ
	double responseTime;	// ��λ����

public:
	TaskRec();
	~TaskRec();
	void setSmallBallDir(int curStartPos);
	bool isFlagExist(string s);
	void setFlag(string s, bool b);
	void setCo(Point2 &p, string str);
	string getCo(Point2 &p);
};

