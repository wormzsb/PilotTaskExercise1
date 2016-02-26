// TaskControlDoc.h : interface of the CTaskControlDoc class
//


#pragma once
#include<vector>
#include<algorithm>
#include<fstream>
#include<sstream>
#include<string>
#include "TaskRec.h"
#include <afx.h>
using namespace std;

class CTaskControlDoc : public CDocument
{
protected: // create from serialization only
	CTaskControlDoc();
	DECLARE_DYNCREATE(CTaskControlDoc)

// Attributes
public:
	CString m_FileName;
	CString m_FileName1;
	CString m_FileName2;
    int m_TaskNo;

	int m_CodePairNum;
	int m_Character[6];
	int m_Shape[10];

    struct TaskSetting1  m_DefSetting1;
	struct TaskSetting2  m_DefSetting2;
	struct TaskSetting3  m_DefSetting3;
	struct TaskSetting4  m_DefSetting4;
	struct TaskSetting5  m_DefSetting5;
	struct TaskSetting6  m_DefSetting6;
	struct TaskSetting7  m_DefSetting7;
	struct TaskSetting8  m_DefSetting8;
    struct TaskSetting1  *m_Setting1;
	struct TaskSetting2  *m_Setting2;
	struct TaskSetting3  *m_Setting3;
	struct TaskSetting4  *m_Setting4;
	struct TaskSetting5  *m_Setting5;
	struct TaskSetting6  *m_Setting6;
	struct TaskSetting7  *m_Setting7;
	struct TaskSetting8  *m_Setting8;
	struct HardSetting   m_HardSetting;
	struct PartInfo      m_PartInfo;
	struct PartInfo      m_CurPartInfo;
	
	map<int, vector<string>> colHeads;		// 列头		

//	int m_ID;
//	char m_Name[10];
//	short m_Sex;
//	int m_Session;

	short m_TrialType; //测试类型
    short m_TrialNo;
	int m_TrialTime;   //测试时间
	int m_TrialTimes;  //测试次数

    UINT m_PointNum;
	short m_HoldNo;
    short m_CodeNo;
    int m_RecordNo;
	short m_TouchNo;

	UINT m_MemNum;
	//SPOINT *m_ObjPoint;
	//SPOINT *m_PostPoint;
	SPOINT m_ObjPoint;
	SPOINT m_PostPoint;
	float *m_ObjRotate;
	float *m_PostRotate;
	float *m_Distance;
	float *m_RotateError;
	float *m_ObjSpeedX;
	float *m_ObjSpeedY;
	float *m_ObjSpeed;
	float *m_PostSpeedX;
	float *m_PostSpeedY;
	float *m_PostSpeed;
	float *m_ObjRotateSpeed;
	float *m_PostRotateSpeed;
	unsigned long *m_PointTime;
    BOOL *m_bHit;
	float *m_ChartTime;

	SYSTEMTIME m_HoldStartTime;
	SYSTEMTIME m_HoldSureTime;
	int *m_HoldTime;
	long *m_TestRT;
	int *m_HoldError;
	float *m_ErrorRatio;

	short *m_EventType;
	unsigned long *m_EventStartTime;
	unsigned long *m_EventSureTime;
	short *m_SureButtonNo;
    unsigned long *m_EventRT;
	int *m_bEventAcc;

	short *m_CodeType;
	unsigned long *m_CodeStartTime;
	unsigned long *m_CodeSureTime;
    short *m_CodeButtonNo;
    long *m_CodeRT;
	int *m_bCodeAcc;

	short m_TouchGroupNo;
	int *m_TouchNoOrder;
	unsigned long *m_TouchStartTime;
	unsigned long *m_TouchSureTime;
    unsigned long *m_TouchRT;
	int *m_TouchAcc;
    int *m_TouchDistance;
	int *m_sizediff;
//	int m_MainTaskNo;

	short *m_SignMemNum;
	short m_SignGroupNo;
	short m_SignNo;
	unsigned long m_MemTime;
	short *m_SignType;
	char m_SignName[30];
	unsigned long *m_SignStartTime;
	unsigned long *m_SignSureTime;
	unsigned long *m_SignRT;
	int *m_SignAcc;

	short m_JudgeNo;
    int *m_CubeNum;
	short m_MemNo;
	char m_LMemName[30];
	char m_RMemName[30];
	short *m_Same;
	short *m_LMemAngle;
	short *m_RMemAngle;
	short *m_MemAngleDiff;

	int m_TaskCount;
	int m_CurTaskCount;
    short m_TaskOrder[50];
	short m_CurTaskOrder[50];
	CString m_TaskExe[50];
	CString m_TaskName[50];
	int m_TaskNum[MAX_TASK];
	struct ItemData
	{
		short TaskIdx;
		short TaskNo;
		BOOL bSet;
	}m_ItemData[50];
	int m_ItemOrder[50];
	BOOL m_bUsedIdx[MAX_TASK][50];
	int m_DocNum[MAX_TASK];
	CString m_CurSettingFile;

	int m_MainTaskMode;
	int m_MemTaskMode;

	int m_StartPoint[50];
	int m_ValidStart[50];
	int m_ExperStart1;
	int m_ExperStart2;

	CString m_TestTime;
	CString m_DataFileName;

	float m_DistanceTotal;
	float m_RotateErrorTotal;
	float m_DistanceAve;
	float m_RotateErrorAve;
	float m_DistanceSqt;
	float m_RotateErrorSqt;
	int m_HitCount;
	int m_HitTimeTotal;
	float m_HitTimeRate;
	int m_HoldErrorTotal[12];
	int m_HoldCountTotal[12];
	int m_TrueCode;
    int m_FalseCode;
	int m_TrueCount;
	int m_MissingCount;
	int m_CRCount;
	int m_FalseCount;
	int m_FailCount;//事件未发生按键数
	UINT m_CodeRTTotal;
	UINT m_RTTotal;
//	UINT m_NoRTTotal;
	float m_CodeRTAvg;
	float m_CodeRTSqr;
	float m_RTAvg;
//	float m_NoRTAvg;
	float m_RTSqr;
//	float m_NoRTSqr;
	float m_Acce;
	int m_TargetCount;
	int m_NoTargetCount;
	UINT m_TouchRTTotal[3][6];
    int m_TouchTotal;
	UINT m_SignRTTotal[5];
	int m_SignTotal[5];
    int m_SignTrueTotal[5];
    float m_SignRTAvg[5];
	float m_SignRTSqr[5];
	int m_SignTrue[5];
	int m_SignMissing[5];
	int m_SignCR[5];
	int m_SignFalse[5];

	BOOL m_bOpenFile1;
    BOOL m_bOpenFile2;

	BOOL bExist1;
	BOOL bExist2;

	BOOL bExitItem1;
	BOOL bExitItem2;

	BOOL bBatch;
	int m_TrialNum;

	// 任务2 
	vector<double> m_HoldTimeErrAve;
	vector<double> settingOrderHoldTimeErrRateAve;

	map<string, vector<TaskRec>> recs;

	//任务7的时间结果数据类型
	struct T7Time {
		SYSTEMTIME sTime, eTime; //开始结束时间
		int duration; //任务总时间
	};
	struct T7Time t7time;

	//任务8的结果数据类型
	struct T8Res {
		double CorrectRate=0;
		double AvgResTime=0;
		double TimeRate_Ratio=0;
		double SDrestime = 0;
		SYSTEMTIME sTime, eTime; //开始结束时间
		int duration; //任务总时间
	};
	struct T8Res t8res;
	
// Operations
public:
	void initAnalyseResult();
	void getTask2HoldError();
    void NewTester();
    void NewSetting();
	BOOL ReadDataFile();
	BOOL ReadT7();
	BOOL ReadT8();
	BOOL ReadT1();
	BOOL ReadT2Trace();
	BOOL ReadT2Hold();
    BOOL ReadT3Trace();
    BOOL ReadT3Code();
    BOOL ReadT3Event();
	BOOL ReadT4();
	BOOL ReadT5Trace();
    BOOL ReadT5Sign();
	BOOL ReadT6Trace();
	BOOL ReadT6Judge();
	BOOL ReadT6Memory();
	void MemClear();
	void DataAnalysis();
	double getAvgAbsDevRatio();
	double getSDAbsDveRatio();
	int getUnRspCnt();
	double getTotalTaskPeriod();
// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CTaskControlDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


