// TaskControlDoc.cpp : implementation of the CTaskControlDoc class
//

#include "stdafx.h"
#include "TaskControl.h"

#include "TaskControlDoc.h"
#include <math.h>
#include <direct.h>
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTaskControlDoc

IMPLEMENT_DYNCREATE(CTaskControlDoc, CDocument)

BEGIN_MESSAGE_MAP(CTaskControlDoc, CDocument)
END_MESSAGE_MAP()


// CTaskControlDoc construction/destruction

CTaskControlDoc::CTaskControlDoc()
{
	// TODO: add one-time construction code here
	int i;

	strcpy_s(m_DefSetting1.m_TaskName, 100,"任务1-目标跟踪能力测试");
	m_DefSetting1.m_PracMode = TRUE;
	m_DefSetting1.m_ExperMode = TRUE;
	m_DefSetting1.m_Track = TRACK_CIRCLE;
	m_DefSetting1.m_Direction = 0;
    m_DefSetting1.m_MoveMode = 0;
	m_DefSetting1.m_SpeedMode = 0;
	m_DefSetting1.m_InitAngle = 0;
	m_DefSetting1.m_Pause = 0;
	m_DefSetting1.m_PauseNum = 0;
	m_DefSetting1.m_Speed = 100.0;
	m_DefSetting1.m_InitSpeed = 50.0;
	m_DefSetting1.m_SpeedMin = 50.0;
	m_DefSetting1.m_SpeedMax = 150.0;
	m_DefSetting1.m_AccelerationMin = 2.0;
	m_DefSetting1.m_AccelerationMax = 5.0;
	m_DefSetting1.m_AngleSpeedMin = 0;
	m_DefSetting1.m_AngleSpeedMax = 0;
	m_DefSetting1.m_RotateAngleMin = 0;
	m_DefSetting1.m_RotateAngleMax = 0;
	m_DefSetting1.m_PracTime = 60;	
	m_DefSetting1.m_ExperTime = 60;	
	m_DefSetting1.m_PracTimes = 1;	
	m_DefSetting1.m_ExperTimes = 1;	
	m_DefSetting1.m_Background = BACKGROUND_GRAY;
	m_DefSetting1.m_iJoyMoveDirection = 0;

	strcpy_s(m_DefSetting2.m_TaskName, 100,"任务2-操作力保持及时间知觉能力测试");
	m_DefSetting2.m_PracMode = TRUE;
	m_DefSetting2.m_ExperMode = TRUE;
	m_DefSetting2.m_MainTask = TRUE;
	m_DefSetting2.m_SubTask = TRUE;
	m_DefSetting2.m_Direction = 0;
	m_DefSetting2.m_InitSpeed = 5;
	m_DefSetting2.m_HoldTimeNum = 4;
	m_DefSetting2.m_iJoyMoveDirection = 0;
	m_DefSetting2.m_MoveMode = 0;
	m_DefSetting2.m_SpeedMode = 0;
	m_DefSetting2.m_Speed = 100.;
	m_DefSetting2.m_InitSpeed = 50.;
	m_DefSetting2.m_SpeedMin = 50.;
	m_DefSetting2.m_SpeedMax = 150.;
	m_DefSetting2.m_AccelerationMin = 2.;
	m_DefSetting2.m_AccelerationMax = 5.;
	m_DefSetting2.m_iTrack = 0;
	for(i=0;i<12;i++)
	{
		m_DefSetting2.m_HoldTime[i] = 0;
	}
	m_DefSetting2.m_HoldTime[0] = 3.0;
	m_DefSetting2.m_HoldTime[1] = 6.0;
	m_DefSetting2.m_HoldTime[2] = 9.0;
	m_DefSetting2.m_HoldTime[3] = 12.0;
	m_DefSetting2.m_IntervalMode = 0;
	m_DefSetting2.m_PracTime = 60;	
	m_DefSetting2.m_ExperTime = 60;	
	m_DefSetting2.m_PracTimes = 1;
	m_DefSetting2.m_ExperTimes = 1;
	m_DefSetting2.m_Background = BACKGROUND_GRAY;
	m_DefSetting2.m_iSubTaskInterval = 2;

	strcpy_s(m_DefSetting3.m_TaskName,100, "任务3-双任务模式突发事件反应时测试");
	m_DefSetting3.m_PracMode = TRUE;
	m_DefSetting3.m_ExperMode = TRUE;
	m_DefSetting3.m_MainTask = TRUE;
	m_DefSetting3.m_SubTask = TRUE;
	m_DefSetting3.m_MainTaskMode = 0;
	m_DefSetting3.m_Background = BACKGROUND_GRAY;
	m_DefSetting3.m_InitSpeed = 5;
	m_DefSetting3.m_EventMode = 0;
	m_DefSetting3.m_CodePairMode = 0;
	m_DefSetting3.m_CodePairNum = 3;
	m_DefSetting3.m_DisplayMode = 0;
	m_DefSetting3.m_EventFrequency = 0;
	m_DefSetting3.m_PracTime = 60;	
	m_DefSetting3.m_ExperTime = 60;	
	m_DefSetting3.m_PracTimes = 1;
	m_DefSetting3.m_ExperTimes = 1;
	m_DefSetting3.m_iJoyMoveDirection = 0;
	m_DefSetting3.m_Direction = 0;
	m_DefSetting3.m_SpeedMode = 0;
	m_DefSetting3.m_Speed = 100;
	m_DefSetting3.m_InitSpeed = 50;
	m_DefSetting3.m_SpeedMin = 50;
	m_DefSetting3.m_SpeedMax = 150;
	m_DefSetting3.m_AccelerationMin = 2;
	m_DefSetting3.m_AccelerationMax = 5;
	m_DefSetting3.m_iTrack = 0;
	m_DefSetting3.m_iPlane = 1;
	m_DefSetting3.m_iHelicopter = 1;
	m_DefSetting3.m_iPresentTime = 2;
	m_DefSetting3.m_iIntervalMin = 4;
	m_DefSetting3.m_iIntervalMax = 8;
	m_DefSetting3.m_iReactTime = 2;
	m_DefSetting3.m_iPlanePos = 15; // 二进制的1111


	strcpy_s(m_DefSetting4.m_TaskName,100, "任务4-触点作业操作能力测试");
	m_DefSetting4.m_PracMode = TRUE;
	m_DefSetting4.m_ExperMode = TRUE;
	m_DefSetting4.m_Background = BACKGROUND_GRAY;
	m_DefSetting4.m_TouchOrder = 0;
	m_DefSetting4.m_PracTimes = 1;
	m_DefSetting4.m_ExperTimes = 1;

	strcpy_s(m_DefSetting5.m_TaskName,100, "任务5-双任务模式图符记忆判别能力测试");
	m_DefSetting5.m_PracMode = TRUE;
	m_DefSetting5.m_ExperMode = TRUE;
	m_DefSetting5.m_MainTask = TRUE;
	m_DefSetting5.m_SubTask = TRUE;
	m_DefSetting5.m_Background = BACKGROUND_GRAY;
	m_DefSetting5.m_InitSpeed = 5;
	m_DefSetting5.m_SignMemType = 0;
	m_DefSetting5.m_SignMemMode = 0;
	m_DefSetting5.m_SignMemNum = 4;
	m_DefSetting5.m_SignShowMode = 0;
	m_DefSetting5.m_SignShowTime = 2;
	m_DefSetting5.m_PracTime = 60;
	m_DefSetting5.m_ExperTime = 60;
	m_DefSetting5.m_PracTimes = 1;
	m_DefSetting5.m_ExperTimes = 1;

	strcpy_s(m_DefSetting6.m_TaskName,100, "任务6-双任务模式三维图形记忆判别能力测试");
	m_DefSetting6.m_PracMode = TRUE;
	m_DefSetting6.m_ExperMode = TRUE;
	m_DefSetting6.m_MainTask = TRUE;
	m_DefSetting6.m_SubTask = TRUE;
	m_DefSetting6.m_Background = BACKGROUND_GRAY;
	m_DefSetting6.m_InitSpeed = 0;
    m_DefSetting6.m_CubeNum1 = 1;
    m_DefSetting6.m_CubeNum2 = 0;
    m_DefSetting6.m_CubeNum3 = 0;
    m_DefSetting6.m_CubeNum4 = 0;
    m_DefSetting6.m_Prototype = 0;
    m_DefSetting6.m_RefAxis = 0;
	m_DefSetting6.m_MemTaskMode = 0;
	m_DefSetting6.m_PracTime = 60;
	m_DefSetting6.m_ExperTime = 60;
	m_DefSetting6.m_PracTimes = 1;
	m_DefSetting6.m_ExperTimes = 1;
	m_DefSetting6.m_iJoyMoveDirection = 0;
	m_DefSetting6.m_iPresentTime = 4;
	m_DefSetting6.m_iSubTaskInterval = 4;
	m_DefSetting6.m_iReactTime = 2;
	m_DefSetting6.m_Speed = 100;
	m_DefSetting6.m_InitSpeed = 50;
	m_DefSetting6.m_SpeedMin = 50;
	m_DefSetting6.m_SpeedMax = 150;
	m_DefSetting6.m_AccelerationMin = 2;
	m_DefSetting6.m_AccelerationMax = 5;
	m_DefSetting6.m_SpeedMode = 0;
	m_DefSetting6.m_Direction = 0;

	//strcpy_s(m_DefSetting7.m_TaskName,100, "任务7-速度知觉");
	strcpy_s(m_DefSetting7.m_TaskName,100, "任务7-速度知觉能力测试");
	m_DefSetting7.m_PracMode = TRUE;
	m_DefSetting7.m_ExperMode = TRUE;
	m_DefSetting7.m_iBallColorR = 255;
	m_DefSetting7.m_iBallColorG = 0;
	m_DefSetting7.m_iBallColorB = 0;
	m_DefSetting7.m_iBallRadius = 15;
	m_DefSetting7.m_iBallSpeed1 = 50;
	m_DefSetting7.m_iBallSpeed2 = 100;
	m_DefSetting7.m_iBallSpeed3 = 150;
	m_DefSetting7.m_iBallSpeedAcc = 10;
	m_DefSetting7.m_iBallStartPos = 15;
	m_DefSetting7.m_iTop = 1;
	m_DefSetting7.m_iBottom = 1;
	m_DefSetting7.m_iLeft = 1;
	m_DefSetting7.m_iRight = 1;
	m_DefSetting7.m_iBckGrndColorR = 0;
	m_DefSetting7.m_iBckGrndColorG = 0;
	m_DefSetting7.m_iBckGrndColorB = 0;
	m_DefSetting7.m_iExpTimes = 2;
	m_DefSetting7.m_iIntervalTime = 1;
	m_DefSetting7.m_iObstacleColorR = 80;
	m_DefSetting7.m_iObstacleColorG = 80;
	m_DefSetting7.m_iObstacleColorB = 80;
	m_DefSetting7.m_iObstacleRadius = 180;
	m_DefSetting7.m_iBallCenterDis = 330;
	m_DefSetting7.m_iPracTimes = 3;
	m_DefSetting7.m_iSpeedMode = 0;

	// Task 8 set default
	strcpy_s(m_DefSetting8.m_TaskName, 100, "任务8-三维心理旋转测试");
	m_DefSetting8.m_bPracMode = FALSE;
	m_DefSetting8.m_iFocusTime = 1;
	m_DefSetting8.m_iPrensentTime = 10;
	m_DefSetting8.m_iCountdownTime = 5;

	m_Setting1 = NULL;
	m_Setting2 = NULL;
	m_Setting3 = NULL;
	m_Setting4 = NULL;
	m_Setting5 = NULL;
	m_Setting6 = NULL;
	m_Setting7 = NULL;
	m_Setting8 = NULL;
	m_ReadSetting1 = NULL;
	m_ReadSetting2 = NULL;
	m_ReadSetting3 = NULL;
	m_ReadSetting4 = NULL;
	m_ReadSetting5 = NULL;
	m_ReadSetting6 = NULL;
	m_ReadSetting7 = NULL;
	m_ReadSetting8 = NULL;

	m_HardSetting.m_JoySpeedMax = 200;
	m_HardSetting.m_KnobSensitive = 1;
	m_HardSetting.m_AngleError = 10;
	m_HardSetting.m_DistanceError = 10;

	strcpy_s(m_PartInfo.m_TesterNo,20, "");
	strcpy_s(m_PartInfo.m_TesterName,20, "");
	strcpy_s(m_PartInfo.m_TesterSex, 10,"男");
	m_PartInfo.m_TesterAge = 0;
	m_PartInfo.m_Session = 0;
	m_CurPartInfo = m_PartInfo;

	//m_ObjPoint = NULL;
	//m_PostPoint = NULL;
	m_ObjRotate = NULL;
	m_PostRotate = NULL;
	//m_Distance = NULL;
	//m_RotateError = NULL;
	//m_ObjSpeedX = NULL;
	//m_ObjSpeedY = NULL;
	//m_ObjSpeed = NULL;
	//m_PostSpeedX = NULL;
	//m_PostSpeedY = NULL;
	//m_PostSpeed = NULL;
	m_ObjRotateSpeed = NULL;
	m_PostRotateSpeed = NULL;
	//m_PointTime = NULL;
    //m_bHit = NULL;
    //m_ChartTime=NULL;

	//m_HoldStartTime = NULL;
	//m_HoldSureTime = NULL;
	m_HoldTime = NULL;
	m_TestRT = NULL;
	m_HoldError = NULL;
	m_ErrorRatio = NULL;

	m_EventType = NULL;
	m_EventStartTime = NULL;
	m_EventSureTime = NULL;
	m_SureButtonNo = NULL;
    m_EventRT = NULL;
	m_bEventAcc = NULL;
	m_TrueCount = 0;
	m_MissingCount = 0;
	m_CRCount = 0;
	m_FalseCount = 0;
	m_FailCount = 0;

	m_CodeType = NULL;
	m_CodeStartTime = NULL;
	m_CodeSureTime = NULL;
    m_CodeButtonNo = NULL;
    m_CodeRT = NULL;
	m_bCodeAcc = NULL;

	m_TouchNoOrder = NULL;
	m_TouchStartTime = NULL;
	m_TouchSureTime = NULL;
    m_TouchRT = NULL;
	m_TouchAcc = NULL;
    m_TouchDistance = NULL;
	m_sizediff = NULL;

	m_SignMemNum = NULL;
	m_SignType = NULL;
	m_SignStartTime = NULL;
	m_SignSureTime = NULL;
	m_SignRT = NULL;
	m_SignAcc = NULL;

	m_CubeNum = NULL;
	m_Same = NULL;
	m_LMemAngle = NULL;
	m_RMemAngle = NULL;
	m_MemAngleDiff = NULL;

	m_TaskCount = 0;
	m_CurTaskCount = 0;
    for(i=0;i<MAX_TASK;i++)
	{
		for(int j=0;j<50;j++)
		{
			m_bUsedIdx[i][j] = FALSE;
		}
	}
	for(i=0;i<MAX_TASK;i++)
	{
		m_DocNum[i] = 0;
	}
}

CTaskControlDoc::~CTaskControlDoc()
{
}

BOOL CTaskControlDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CTaskControlDoc serialization

void CTaskControlDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CTaskControlDoc diagnostics

#ifdef _DEBUG
void CTaskControlDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTaskControlDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CTaskControlDoc commands
void CTaskControlDoc::NewTester()
{
	strcpy_s(m_PartInfo.m_TesterNo, 20, "");
	strcpy_s(m_PartInfo.m_TesterName, 20, "");
	strcpy_s(m_PartInfo.m_TesterSex,10, "男");
	m_PartInfo.m_TesterAge = 0;
	m_PartInfo.m_Session = 0;
}

void CTaskControlDoc::NewSetting()
{
	m_TaskCount = 0;
	if(m_ReadSetting1!=NULL)
	{
		delete []m_ReadSetting1;
		m_ReadSetting1 = NULL;
	}
	if(m_ReadSetting2!=NULL)
	{
		delete []m_ReadSetting2;
		m_ReadSetting2 = NULL;
	}
	if(m_ReadSetting3!=NULL)
	{
		delete []m_ReadSetting3;
		m_ReadSetting3 = NULL;
	}
	if(m_ReadSetting4!=NULL)
	{
		delete []m_ReadSetting4;
		m_ReadSetting4 = NULL;
	}
	if(m_ReadSetting5!=NULL)
	{
		delete []m_ReadSetting5;
		m_ReadSetting5 = NULL;
	}
	if(m_ReadSetting6!=NULL)
	{
		delete []m_ReadSetting6;
		m_ReadSetting6 = NULL;
	}

	if(m_ReadSetting7!=NULL)
	{
		delete []m_ReadSetting7;
		m_ReadSetting7 = NULL;
	}

	if (m_ReadSetting8 != NULL)
	{
		delete[]m_ReadSetting8;
		m_ReadSetting8 = NULL;
	}

	m_TaskCount = 0;
	int i;
    for(i=0;i<MAX_TASK;i++)
	{
		for(int j=0;j<50;j++)
		{
			m_bUsedIdx[i][j] = FALSE;
		}
	}
	for(i=0;i<MAX_TASK;i++)
	{
		m_DocNum[i] = 0;
	}


}

BOOL CTaskControlDoc::ReadDataFile() 
{
	int pos,pos1,pos2;
	CString cs;
	int i;
	CString str;

	for(i=0;i<50;i++)
	{
		m_StartPoint[i] = 0;
	}

	pos = m_FileName.ReverseFind('\\');
	m_TaskNo = atoi(m_FileName.Mid(pos+2,1));

	pos1 = m_FileName.ReverseFind('-');
	m_TestTime = m_FileName.Mid(pos1+1,14);
	pos1 = m_FileName.ReverseFind('.');
	m_DataFileName = m_FileName.Mid(pos+1,pos1-pos-1);
	switch (m_TaskNo)
	{
	case 1:
		if(m_ReadSetting1!=NULL)
		{
			delete []m_ReadSetting1;
			m_ReadSetting1 = NULL;
		}
		m_ReadSetting1 = new struct TaskSetting1[1];
		MemClear();
        m_bOpenFile1 = ReadT1();
		break;
	case 2:
		if(m_ReadSetting2!=NULL)
		{
			delete []m_ReadSetting2;
			m_ReadSetting2 = NULL;
		}
		m_ReadSetting2 = new struct TaskSetting2[1];
		pos = m_FileName.ReverseFind('\\');
        pos1 = m_FileName.Find('-',pos+1);
		pos2 = m_FileName.Find('-',pos1+1);
		m_FileName1 = m_FileName.Left(pos+1)+"T2-trace"+m_FileName.Right(m_FileName.GetLength()-pos2);
		m_FileName2 = m_FileName.Left(pos+1)+"T2-hold"+m_FileName.Right(m_FileName.GetLength()-pos2);
        MemClear();
		m_bOpenFile1 = ReadT2Trace();
		m_bOpenFile2 = ReadT2Hold();
		break;
	case 3:
		pos = m_FileName.ReverseFind('\\');
        pos1 = m_FileName.Find('_',pos+1);
		m_MainTaskMode = atoi(m_FileName.Mid(pos1+1,1))-1;	
		if(m_ReadSetting3!=NULL)
		{
			delete []m_ReadSetting3;
			m_ReadSetting3 = NULL;
		}
		m_ReadSetting3 = new struct TaskSetting3[1];
		pos = m_FileName.ReverseFind('\\');
        pos1 = m_FileName.Find('-',pos+1);
		pos2 = m_FileName.Find('-',pos1+1);	
		MemClear();
		if(m_MainTaskMode == 0)
		{
			m_FileName1 = m_FileName.Left(pos+1)+"T3_1-trace"+m_FileName.Right(m_FileName.GetLength()-pos2);
	     	m_FileName2 = m_FileName.Left(pos+1)+"T3_1-event"+m_FileName.Right(m_FileName.GetLength()-pos2);
            m_bOpenFile1 = ReadT3Trace();
		}
		else
		{
			m_FileName1 = m_FileName.Left(pos+1)+"T3_2-code"+m_FileName.Right(m_FileName.GetLength()-pos2);
		    m_FileName2 = m_FileName.Left(pos+1)+"T3_2-event"+m_FileName.Right(m_FileName.GetLength()-pos2);
			m_bOpenFile1 = ReadT3Code();
		}
		m_bOpenFile2 = ReadT3Event();
		break;
	case 4:
		if(m_ReadSetting4!=NULL)
		{
			delete []m_ReadSetting4;
			m_ReadSetting4 = NULL;
		}
		m_ReadSetting4 = new struct TaskSetting4[1];
		MemClear();		
		m_bOpenFile1 = ReadT4();
		break;
	case 5:
		if(m_ReadSetting5!=NULL)
		{
			delete []m_ReadSetting5;
			m_ReadSetting5 = NULL;
		}
		m_ReadSetting5 = new struct TaskSetting5[1];
		pos = m_FileName.ReverseFind('\\');
        pos1 = m_FileName.Find('-',pos+1);
		pos2 = m_FileName.Find('-',pos1+1);
		m_FileName1 = m_FileName.Left(pos+1)+"T5-trace"+m_FileName.Right(m_FileName.GetLength()-pos2);
     	m_FileName2 = m_FileName.Left(pos+1)+"T5-sign"+m_FileName.Right(m_FileName.GetLength()-pos2);
		MemClear();
		m_bOpenFile1 = ReadT5Trace();
		m_bOpenFile2 = ReadT5Sign();
		break;
	case 6:
		pos = m_FileName.ReverseFind('\\');
        pos1 = m_FileName.Find('_',pos+1);
		m_MemTaskMode = atoi(m_FileName.Mid(pos1+1,1))-1;	
		if(m_ReadSetting6!=NULL)
		{
			delete []m_ReadSetting6;
			m_ReadSetting6 = NULL;
		}
		m_ReadSetting6 = new struct TaskSetting6[1];
		pos = m_FileName.ReverseFind('\\');
        pos1 = m_FileName.Find('-',pos+1);
		pos2 = m_FileName.Find('-',pos1+1);
 		MemClear();
		if(m_MemTaskMode == 0)
		{
			m_FileName1 = m_FileName.Left(pos+1)+"T6_1-trace"+m_FileName.Right(m_FileName.GetLength()-pos2);
     	    m_FileName2 = m_FileName.Left(pos+1)+"T6_1-judge"+m_FileName.Right(m_FileName.GetLength()-pos2);
            m_bOpenFile1 = ReadT6Trace();
			m_bOpenFile2 = ReadT6Judge();	
		}
		else
		{
			m_FileName1 = m_FileName.Left(pos+1)+"T6_2-trace"+m_FileName.Right(m_FileName.GetLength()-pos2);
     	    m_FileName2 = m_FileName.Left(pos+1)+"T6_2-memory"+m_FileName.Right(m_FileName.GetLength()-pos2);
            m_bOpenFile1 = ReadT6Trace();
			m_bOpenFile2 = ReadT6Memory();
		}
		break;
	case 7:
		// xxx

		if (m_ReadSetting7 != NULL)
		{
			delete[]m_ReadSetting7;
			m_ReadSetting7 = NULL;
		}
		m_ReadSetting7 = new struct TaskSetting7[1];
		MemClear();
		break;

	case 8:
		// xxx

		if (m_ReadSetting8 != NULL)
		{
			delete[]m_ReadSetting8;
			m_ReadSetting8 = NULL;
		}
		m_ReadSetting8 = new struct TaskSetting8[1];
		MemClear();
		m_bOpenFile1 = ReadT8();
		break;
	}	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CTaskControlDoc::ReadT7() {
	CMainFrame*   pMain = (CMainFrame*)AfxGetMainWnd();
	m_TrialType = -1;
	m_ExperStart1 = -1;
	bExitItem1 = FALSE;
	FILE *fp;
	int j = 0;
	//	FILE *fp1;
	CString str;
	char tmp[1000];

	CString m_SaveName;
	//	char filestr[50];
	//	int len;
	_mkdir("Result");
	_mkdir("Result\\Task7");
	m_SaveName = "Result\\Task7\\task7_tracking_result.txt";
	
	// 这部分看起来没什么用
	fopen_s(&fp, m_SaveName, "r");
	{
		if (fp != NULL)
		{
			fgets(tmp, 1000, fp);
			while (!feof(fp))
			{
				fgets(tmp, 1000, fp);
				if (strncmp(tmp, m_DataFileName, m_DataFileName.GetLength()) == 0)
				{
					if (bBatch)
					{
						fclose(fp);
						return FALSE;
					}
					else
					{
						bExitItem1 = TRUE;
					}
				}
			}
			bExist1 = TRUE;
			fclose(fp);
		}
		else
		{
			bExist1 = FALSE;
		}
	}

	// get list dialog pointer
	CResultDlg *m_pWSDlg;
	if (!bBatch)
	{
		m_pWSDlg = (CResultDlg *)pMain->m_pWSDlg;
	}

	// 读取Data数据
	//fopen_s(&fp, m_FileName, "rt");
	ifstream fin;
	fin.open((CT2A(m_FileName)));
	if (fin.is_open()==0) {
		AfxMessageBox("文件没有正确打开");
		return TRUE;
	}
	
	string t;
	int n=0;
	while (getline(fin, t)) n++;//计算行数
	fin.close();

	fin.open((CT2A(m_FileName)));
	if (fin.is_open() == 0) {
		AfxMessageBox("文件没有正确打开");
		return TRUE;
	}

	char sz[1000];
	// read head(1 row)
	fin.getline(sz, 1000);
	//TRACE("\nsz = %s\n", sz);
	
	recs["t7"] = vector<TaskRec>();

	int i = 0;
	while (fin.peek() != EOF) {
		TRACE("\n i = %d \n", i);
		string str;
		TaskRec rec;
		fin >> rec.no;
		if (fin.fail()) break;
		fin >> rec.smallBallSpeed >> rec.smallBalldir
			>> rec.moveBegTime >> rec.disappearTime >> rec.pressTime
			>> rec.visiblePeriod >> rec.obstacle2PressPeriod 
			>> rec.totalPeriod >> rec.evaluateTime 
			>> rec.deviationRate;
		fin >> str; rec.setCo(rec.smallBallBegCo, str);
		fin >> str; rec.setCo(rec.targetCo, str);
		fin >> str; rec.setCo(rec.pressSmallBallCo, str);
		if (i == n - 2)
		{
			char t2;
			fin >> t7time.sTime.wHour >> t2 >> t7time.sTime.wMinute >> t2 >> t7time.sTime.wSecond
				>> t7time.eTime.wHour >> t2 >> t7time.eTime.wMinute >> t2 >> t7time.eTime.wSecond
				>> t7time.duration;
		}
		recs["t7"].push_back(rec);
		
		// add to list dialog
		m_pWSDlg->m_ListDlg.AddT7Item(i, n);

		i++;
	}
	return TRUE;
}

BOOL CTaskControlDoc::ReadT8()
{
	CMainFrame*   pMain = (CMainFrame*)AfxGetMainWnd();
	// get list dialog pointer
	CResultDlg *m_pWSDlg;
	if (!bBatch)
	{
		m_pWSDlg = (CResultDlg *)pMain->m_pWSDlg;
	}
	// 读取Data数据
	//fopen_s(&fp, m_FileName, "rt");
	ifstream fin;
	fin.open((CT2A(m_FileName)));
	if (fin.is_open() == 0) {
		AfxMessageBox("文件没有正确打开");
		return TRUE;
	}
	char sz[1000];
	// read head(1 row)
	fin.getline(sz, 1000);
	recs["t8"] = vector<TaskRec>();
	int i = 0;
	while (fin.peek() != EOF) {
		TRACE("\n i = %d \n", i);
		string str;
		TaskRec rec;
		char t;
		if (i == 0)
		{
			fin >> rec.no;
			if (fin.fail()) break;
			fin >> rec.leftImg >> rec.rightImg >> rec.unCoincidence
				>> rec.btn >> rec.isRight >> rec.responseTime
				>> t8res.sTime.wHour >> t >> t8res.sTime.wMinute >> t >> t8res.sTime.wSecond
				>> t8res.eTime.wHour >> t >> t8res.eTime.wMinute >> t >> t8res.eTime.wSecond >> t8res.duration;
		}//第一行记录任务用时信息
		else
		{
			fin >> rec.no;
			if (fin.fail()) break;
			fin >> rec.leftImg >> rec.rightImg >> rec.unCoincidence
				>> rec.btn >> rec.isRight >> rec.responseTime;
		}
		recs["t8"].push_back(rec);

		// add to list dialog
		m_pWSDlg->m_ListDlg.AddT8Item(i);

		i++;
	}

	return FALSE;
}


BOOL CTaskControlDoc::ReadT1()
{
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
    m_TrialType = -1;
    m_ExperStart1 = -1;
	bExitItem1 = FALSE;
	FILE *fp;
	int j = 0;
//	FILE *fp1;
	CString str;
	char tmp[1000];

    CString m_SaveName;
//	char filestr[50];
//	int len;
	_mkdir("Result");
	_mkdir("Result\\Task1");
	m_SaveName = "Result\\Task1\\task1_tracking_result.txt";
//	sprintf(filestr,"%s\t%s",m_TestTime,m_PartInfo.m_TesterNo);
//	len = strlen(filestr);
	fopen_s(&fp, m_SaveName,"r");
	{
		if(fp!=NULL)
		{
			fgets(tmp,1000,fp);	
			while(!feof(fp))
			{
				fgets(tmp,1000,fp);	
				if(strncmp(tmp,m_DataFileName,m_DataFileName.GetLength()) == 0)
				{
					if(bBatch)
					{
						fclose(fp);
						return FALSE;
					}
					else
					{
	                    bExitItem1 = TRUE;
					}
				}
			}
			bExist1 = TRUE;
			fclose(fp);
		}
		else
		{
			bExist1 = FALSE;
		}
	}

	CResultDlg *m_pWSDlg;
	if (!bBatch)
	{
		m_pWSDlg = (CResultDlg *)pMain->m_pWSDlg;
	}

	fopen_s(&fp, m_FileName,"rt");
	int i = 0;
	if(fp!=NULL)
	{
		/*m_MemNum = 2000;

		//m_ObjPoint = (SPOINT*)malloc(m_MemNum*sizeof(POINT));
		//m_PostPoint = (SPOINT*)malloc(m_MemNum*sizeof(POINT));
		m_ObjRotate = (float*)malloc(m_MemNum*sizeof(float));
		m_PostRotate = (float*)malloc(m_MemNum*sizeof(float));
		m_Distance = (float*)malloc(m_MemNum*sizeof(float));
		m_RotateError = (float*)malloc(m_MemNum*sizeof(float));
		m_PointTime = (unsigned long*)malloc(m_MemNum*sizeof(unsigned long));
		m_bHit = (BOOL*)malloc(m_MemNum*sizeof(BOOL));
		m_ObjSpeedX = (float*)malloc(m_MemNum*sizeof(float));
		m_ObjSpeedY = (float*)malloc(m_MemNum*sizeof(float));
		m_PostSpeedX = (float*)malloc(m_MemNum*sizeof(float));
		m_PostSpeedY = (float*)malloc(m_MemNum*sizeof(float));
		m_ObjRotateSpeed = (float*)malloc(m_MemNum*sizeof(float));
		m_PostRotateSpeed = (float*)malloc(m_MemNum*sizeof(float));
		m_ChartTime = (float*)malloc(m_MemNum*sizeof(float));
		m_ObjSpeed = (float*)malloc(m_MemNum*sizeof(float));
		m_PostSpeed = (float*)malloc(m_MemNum*sizeof(float));*/
//		fprintf(fp,"ID\tName\tSex\tSession\t"
//			"DistanceError\tAngleError\tPracMode\tExperMode\t"
//			"Background\tTrack\tDirection\tMoveMode\tSpeedMode\tPause\tPauseNum\tInitSpeed\t"
//			"SpeedMin\tSpeedMax\tAccelerationMin\tAccelerationMax\tAngleSpeedMin\tAngleSpeedMax\tRotateAngleMin\tRotateAngleMax\tPracTime\tExperTime\tPracTimes\tExperTimes\t"
//			"Pra_Test\tTrial\tPointNum\tPointTime\tObjPointX\tObjPointY\tPostPointX\tPostPointY\tObjRotate\tPostRotate\tDistance\tRotateError\tHit\t"
//			"ObjSpeedX\tObjSpeedY\tPostSpeedX\tPostSpeedY\tObjRotateSpeed\tPostRotateSpeed\n");
		fgets(tmp,1000,fp);
		//fscanf(fp,"%s\n",tmp);

		try{
			while(!feof(fp))
			{
	//			fp1 = fp;
				/*if(i>=m_MemNum)
				{
					m_MemNum+=1000;
					//m_ObjPoint = (SPOINT*)realloc(m_ObjPoint,m_MemNum*sizeof(SPOINT));
     				//m_PostPoint = (SPOINT*)realloc(m_PostPoint,m_MemNum*sizeof(SPOINT));
					m_ObjRotate = (float*)realloc(m_ObjRotate,m_MemNum*sizeof(float));
     				m_PostRotate = (float*)realloc(m_PostRotate,m_MemNum*sizeof(float));
					m_Distance = (float*)realloc(m_Distance,m_MemNum*sizeof(float));
     				m_RotateError = (float*)realloc(m_RotateError,m_MemNum*sizeof(float));
					m_PointTime = (unsigned long*)realloc(m_PointTime,m_MemNum*sizeof(unsigned long));
					m_bHit = (BOOL*)realloc(m_bHit,m_MemNum*sizeof(BOOL));
					m_ObjSpeedX = (float*)realloc(m_ObjSpeedX,m_MemNum*sizeof(float));
					m_ObjSpeedY = (float*)realloc(m_ObjSpeedY,m_MemNum*sizeof(float));
					m_PostSpeedX = (float*)realloc(m_PostSpeedX,m_MemNum*sizeof(float));
					m_PostSpeedY = (float*)realloc(m_PostSpeedY,m_MemNum*sizeof(float));
					m_ObjRotateSpeed = (float*)realloc(m_ObjRotateSpeed,m_MemNum*sizeof(float));
					m_PostRotateSpeed = (float*)realloc(m_PostRotateSpeed,m_MemNum*sizeof(float));
					m_ChartTime = (float*)realloc(m_ChartTime,m_MemNum*sizeof(float));
					m_ObjSpeed = (float*)realloc(m_ObjSpeed,m_MemNum*sizeof(float));
	            	m_PostSpeed = (float*)realloc(m_PostSpeed,m_MemNum*sizeof(float));
				}*/
				float m_Distance_t;
				float m_RotateError_t;
				float m_ObjSpeedX_t;
				float m_ObjSpeedY_t;
				float m_PostSpeedX_t;
				float m_PostSpeedY_t;
				unsigned long m_PointTime_t;
				BOOL m_bHit_t;
				fscanf_s(fp,"%s\t%s\t%s\t%d\t"
					"%f\t%f\t%d\t%d\t"
					"%d\t%d\t%d\t%d\t%d\t"
					"%d\t%d\t%f\t%f\t"
					"%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%d\t%d\t%d\t%d\t"
					"%d\t%d\t%d\t%u\t%d\t%d\t%d\t%d\t%f\t%f\t%f\t%f\t%d\t"
					"%f\t%f\t%f\t%f\t%f\t%f\n",
					m_PartInfo.m_TesterNo,20, m_PartInfo.m_TesterName,20, m_PartInfo.m_TesterSex,10, &m_PartInfo.m_Session, 
					&m_HardSetting.m_DistanceError, &m_HardSetting.m_AngleError, &m_ReadSetting1[0].m_PracMode, &m_ReadSetting1[0].m_ExperMode,
					&m_ReadSetting1[0].m_Background, &m_ReadSetting1[0].m_Track, &m_ReadSetting1[0].m_Direction, &m_ReadSetting1[0].m_MoveMode, &m_ReadSetting1[0].m_SpeedMode,
					&m_ReadSetting1[0].m_Pause, &m_ReadSetting1[0].m_PauseNum, &m_ReadSetting1[0].m_Speed, &m_ReadSetting1[0].m_InitSpeed,
					&m_ReadSetting1[0].m_SpeedMin, &m_ReadSetting1[0].m_SpeedMax, &m_ReadSetting1[0].m_AccelerationMin, &m_ReadSetting1[0].m_AccelerationMax, &m_ReadSetting1[0].m_AngleSpeedMin, &m_ReadSetting1[0].m_AngleSpeedMax, &m_ReadSetting1[0].m_RotateAngleMin, &m_ReadSetting1[0].m_RotateAngleMax, &m_ReadSetting1[0].m_PracTime, &m_ReadSetting1[0].m_ExperTime, &m_ReadSetting1[0].m_PracTimes, &m_ReadSetting1[0].m_ExperTimes,
					&m_TrialType, &m_TrialNo, &m_PointNum, &m_PointTime_t, &m_ObjPoint.x, &m_ObjPoint.y, &m_PostPoint.x, &m_PostPoint.y, &m_ObjRotate, &m_PostRotate, &m_Distance_t, &m_RotateError_t, &m_bHit_t,
					&m_ObjSpeedX_t, &m_ObjSpeedY_t, &m_PostSpeedX_t, &m_PostSpeedY_t, &m_ObjRotateSpeed, &m_PostRotateSpeed);
				m_Distance.push_back(m_Distance_t);
				m_RotateError.push_back(m_RotateError_t);
				m_ObjSpeedX.push_back(m_ObjSpeedX_t);
				m_ObjSpeedY.push_back(m_ObjSpeedY_t);
				m_PostSpeedX.push_back(m_PostSpeedX_t);
				m_PostSpeedY.push_back(m_PostSpeedY_t);
				m_PointTime.push_back(m_PointTime_t);
				m_bHit.push_back(m_bHit_t);
	//			if(fp == fp1)
	//			{
	//				MessageBox("文件格式有误！");	
	//				return FALSE;
	//			}
                m_ObjSpeed.push_back(pow(pow((double)m_ObjSpeedX[i],2.0)+pow((double)m_ObjSpeedY[i],2.0),0.5));
				m_PostSpeed.push_back(pow(pow((double)m_PostSpeedX[i],2.0)+pow((double)m_PostSpeedY[i],2.0),0.5));
				if(m_TrialType==0)
				{ 
					m_ExperStart1 = i;
				}
				if(m_TrialType==1&&m_PointNum==1)
				{ 
					m_StartPoint[j] = i;
					j++;
				} 
				if(m_TrialType==1)
				{
					m_ChartTime.push_back((float)(m_PointTime[i] - m_PointTime[m_StartPoint[j-1]])/1000.0);
				}
				if (!bBatch)
				{
					if(m_TrialType==0||m_TrialType==1)
					{
						m_pWSDlg->m_ListDlg.AddT1Item(i);
					}
				}
				i++;
			}
			m_ExperStart1 = m_ExperStart1+1;
			m_PointNum = i;	
			fclose(fp);
			if(m_ExperStart1>=m_PointNum-1)
			{
				return FALSE;
			}
			if(m_TrialType!=0&&m_TrialType!=1)
			{
				return FALSE;
			}
			m_StartPoint[m_ReadSetting1[0].m_ExperTimes] = m_PointNum;
			m_TrialNum = m_ReadSetting1[0].m_ExperTimes;
		}
		catch(...)
		{
			AfxMessageBox("数据文件格式错误！");
			return FALSE;
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CTaskControlDoc::ReadT2Trace()
{
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
	m_TrialType = -1;
    m_ExperStart1 = -1;
	bExitItem1 = FALSE;
	FILE *fp;
	FILE *fp1;
	CString str;
	int j = 0;
	char tmp[1000];
	int i;

    CString m_SaveName;
	char filestr[50];
	int len;
	_mkdir("Result");
	_mkdir("Result\\Task2");
	m_SaveName = "Result\\Task2\\task2_tracking_result.txt";
	sprintf_s(filestr,50,"%s\t%s",m_TestTime,m_PartInfo.m_TesterNo);
	len = strlen(filestr);
	fopen_s(&fp, m_SaveName,"r");
	{
		if(fp!=NULL)
		{
			fgets(tmp,1000,fp);	
			while(!feof(fp))
			{
				fgets(tmp,1000,fp);	
				if(strncmp(tmp,filestr,len) == 0)
				{
					if(bBatch)
					{
						fclose(fp);
						return FALSE;
					}
					else
					{
	                    bExitItem1 = TRUE;
					}
				}
			}
			bExist1 = TRUE;
			fclose(fp);
		}
		else
		{
			bExist1 = FALSE;
		}
	}

	CResultDlg *m_pWSDlg;
	if (!bBatch)
	{
		m_pWSDlg = (CResultDlg *)pMain->m_pWSDlg;
	}

	fopen_s(&fp, m_FileName1,"rt");
	i = 0;
	if(fp!=NULL)
	{
		/*m_MemNum = 1000;
		//m_ObjPoint = (SPOINT*)malloc(m_MemNum*sizeof(POINT));
		//m_PostPoint = (SPOINT*)malloc(m_MemNum*sizeof(POINT));
		m_Distance = (float*)malloc(m_MemNum*sizeof(float));
		m_PointTime = (unsigned long*)malloc(m_MemNum*sizeof(unsigned long));
		m_bHit = (BOOL*)malloc(m_MemNum*sizeof(BOOL));
		m_ObjSpeedX = (float*)malloc(m_MemNum*sizeof(float));
		m_ObjSpeedY = (float*)malloc(m_MemNum*sizeof(float));
		m_PostSpeedX = (float*)malloc(m_MemNum*sizeof(float));
		m_PostSpeedY = (float*)malloc(m_MemNum*sizeof(float));
		m_ChartTime = (float*)malloc(m_MemNum*sizeof(float));
		m_ObjSpeed = (float*)malloc(m_MemNum*sizeof(float));
		m_PostSpeed = (float*)malloc(m_MemNum*sizeof(float));*/
		//m_StartPoint = (int*)malloc(m_MemNum*sizeof(int));
		//m_ValidStart = (int*)malloc(m_MemNum*sizeof(int));
//		fprintf(fp,"ID\tName\tSex\tSession\t"
//			"DistanceError\tPracMode\tExperMode\tMainTask\tSubTask\t"
//			"Background\tDirection\tInitSpeed\t"
//			"HoldTimeNum\tHoldTime1\tHoldTime2\tHoldTime3\tHoldTime4\tHoldTime5\tHoldTime6\tHoldTime7\tHoldTime8\tHoldTime9\tHoldTime10\tHoldTime11\tHoldTime12\tPracTime\tExperTime\tPracTimes\tExperTimes\t"
//			"Pra_Test\tPointNum\tPointTime\tObjPointX\tObjPointY\tPostPointX\tPostPointY\tDistance\tHit\t"
//			"ObjSpeedX\tObjSpeedY\tPostSpeedX\tPostSpeedY\n");
        
		fgets(tmp,1000,fp);
		try
		{
			while(!feof(fp))
			{
				fp1 = fp;
				/*if(i>=m_MemNum)
				{
					m_MemNum+=1000;
					//m_ObjPoint = (SPOINT*)realloc(m_ObjPoint,m_MemNum*sizeof(SPOINT));
     				//m_PostPoint = (SPOINT*)realloc(m_PostPoint,m_MemNum*sizeof(SPOINT));
					m_Distance = (float*)realloc(m_Distance,m_MemNum*sizeof(float));
					m_PointTime = (unsigned long*)realloc(m_PointTime,m_MemNum*sizeof(unsigned long));
					m_bHit = (BOOL*)realloc(m_bHit,m_MemNum*sizeof(BOOL));
					m_ObjSpeedX = (float*)realloc(m_ObjSpeedX,m_MemNum*sizeof(float));
					m_ObjSpeedY = (float*)realloc(m_ObjSpeedY,m_MemNum*sizeof(float));
					m_PostSpeedX = (float*)realloc(m_PostSpeedX,m_MemNum*sizeof(float));
					m_PostSpeedY = (float*)realloc(m_PostSpeedY,m_MemNum*sizeof(float));
					m_ChartTime = (float*)realloc(m_ChartTime,m_MemNum*sizeof(float));
					m_ObjSpeed = (float*)realloc(m_ObjSpeed,m_MemNum*sizeof(float));
	           		m_PostSpeed = (float*)realloc(m_PostSpeed,m_MemNum*sizeof(float));
					//m_StartPoint = (int*)realloc(m_StartPoint, m_MemNum*sizeof(int));
					//m_ValidStart = (int*)realloc(m_ValidStart, m_MemNum*sizeof(int));
				}*/
				float m_Distance_t;
				float m_RotateError_t;
				float m_ObjSpeedX_t;
				float m_ObjSpeedY_t;
				float m_PostSpeedX_t;
				float m_PostSpeedY_t;
				unsigned long m_PointTime_t;
				BOOL m_bHit_t;
				fscanf_s(fp,"%s\t%s\t%s\t%d\t"
					"%f\t%d\t%d\t%d\t%d\t"
					"%d\t%d\t%f\t"
					"%d\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%d\t%d\t%d\t%d\t"
					"%d\t%d\t%u\t%d\t%d\t%d\t%d\t%f\t%d\t"
					"%f\t%f\t%f\t%f\n",
					m_PartInfo.m_TesterNo,20, m_PartInfo.m_TesterName,20, m_PartInfo.m_TesterSex,10, &m_PartInfo.m_Session, 
					&m_HardSetting.m_DistanceError, &m_ReadSetting2[0].m_PracMode, &m_ReadSetting2[0].m_ExperMode, &m_ReadSetting2[0].m_MainTask, &m_ReadSetting2[0].m_SubTask,
					&m_ReadSetting2[0].m_Background, &m_ReadSetting2[0].m_Direction, &m_ReadSetting2[0].m_InitSpeed, 
					&m_ReadSetting2[0].m_HoldTimeNum, &m_ReadSetting2[0].m_HoldTime[0], &m_ReadSetting2[0].m_HoldTime[1], &m_ReadSetting2[0].m_HoldTime[2], &m_ReadSetting2[0].m_HoldTime[3], &m_ReadSetting2[0].m_HoldTime[4], &m_ReadSetting2[0].m_HoldTime[5], &m_ReadSetting2[0].m_HoldTime[6], &m_ReadSetting2[0].m_HoldTime[7], &m_ReadSetting2[0].m_HoldTime[8], &m_ReadSetting2[0].m_HoldTime[9], &m_ReadSetting2[0].m_HoldTime[10], &m_ReadSetting2[0].m_HoldTime[11], &m_ReadSetting2[0].m_PracTime, &m_ReadSetting2[0].m_ExperTime, &m_ReadSetting2[0].m_PracTimes, &m_ReadSetting2[0].m_ExperTimes,
					&m_TrialType, /*&m_TrialNo,*/ &m_PointNum, &m_PointTime_t, &m_ObjPoint.x, &m_ObjPoint.y, &m_PostPoint.x, &m_PostPoint.y, &m_Distance_t, &m_bHit_t,
					&m_ObjSpeedX_t, &m_ObjSpeedY_t, &m_PostSpeedX_t, &m_PostSpeedY_t);
				m_Distance.push_back(m_Distance_t);
				m_RotateError.push_back(m_RotateError_t);
				m_ObjSpeedX.push_back(m_ObjSpeedX_t);
				m_ObjSpeedY.push_back(m_ObjSpeedY_t);
				m_PostSpeedX.push_back(m_PostSpeedX_t);
				m_PostSpeedY.push_back(m_PostSpeedY_t);
				m_PointTime.push_back(m_PointTime_t);
				m_bHit.push_back(m_bHit_t);
				m_ObjSpeed.push_back(pow(pow((double)m_ObjSpeedX[i], 2.0) + pow((double)m_ObjSpeedY[i], 2.0), 0.5));
				m_PostSpeed.push_back(pow(pow((double)m_PostSpeedX[i], 2.0) + pow((double)m_PostSpeedY[i], 2.0), 0.5));
	//			if(fp == fp1)
	//			{
	//				MessageBox("文件格式有误！");
	//				return FALSE;
	//			}
				if(m_TrialType==0)
				{ 
					m_ExperStart1 = i;
				}
				if(m_TrialType==1&&m_PointNum==1)
				{ 
					m_StartPoint[j] = i;
					j++;
				} 
				if(m_TrialType==1)
				{
					m_ChartTime.push_back((float)(m_PointTime[i] - m_PointTime[m_StartPoint[j - 1]]) / 1000.0);
				}
				if (!bBatch)
				{
					if(m_TrialType==0||m_TrialType==1)
					{
						m_pWSDlg->m_ListDlg.AddT2TraceItem(i);
					}
				}
				i++;
			}
			m_ExperStart1 = m_ExperStart1+1;
			m_PointNum = i;
			
			fclose(fp);
			if(m_ExperStart1>m_PointNum)
			{
				return FALSE;
			}
			if(m_TrialType!=0&&m_TrialType!=1)
			{
				return FALSE;
			}
			m_StartPoint[1] = m_PointNum;
			m_TrialNum = 1;
		}
		catch(...)
		{
			AfxMessageBox("数据文件格式错误！");
			return FALSE;
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CTaskControlDoc::ReadT2Hold()
{
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
	bExitItem2 = FALSE;
	m_TrialType = -1;
    m_ExperStart2 = -1;
	FILE *fp;
	FILE *fp1;
	CString str;
	char tmp[1000];
	int i;

    CString m_SaveName;
	char filestr[50];
	int len;
	_mkdir("Result");
	_mkdir("Result\\Task2");
	m_SaveName = "Result\\Task2\\task2_hold_result.txt";
	sprintf_s(filestr,50,"%s\t%s",m_TestTime,m_PartInfo.m_TesterNo);
	len = strlen(filestr);
	fopen_s(&fp, m_SaveName,"r");
	{
		if(fp!=NULL)
		{
			fgets(tmp,1000,fp);	
			while(!feof(fp))
			{
				fgets(tmp,1000,fp);	
				if(strncmp(tmp,filestr,len) == 0)
				{
					if(bBatch)
					{
						fclose(fp);
						return FALSE;
					}
					else
					{
	                    bExitItem2 = TRUE;
					}
				}
			}
			bExist2 = TRUE;
			fclose(fp);
		}
		else
		{
			bExist2 = FALSE;
		}
	}

	CResultDlg *m_pWSDlg;
	if (!bBatch)
	{
		m_pWSDlg = (CResultDlg *)pMain->m_pWSDlg;
	}

	ifstream fin;
	fin.open((CT2A(m_FileName2)));
	if (fin.is_open() == 0) {
		AfxMessageBox("文件没有正确打开");
		return TRUE;
	}

	m_MemNum = 100;
//	m_HoldStartTime = (SYSTEMTIME)malloc(m_MemNum*sizeof(SYSTEMTIME));
//	m_HoldSureTime = (SYSTEMTIME)malloc(m_MemNum*sizeof(SYSTEMTIME));
	m_HoldTime = (int*)malloc(m_MemNum*sizeof(int));
	m_TestRT = (long*)malloc(m_MemNum*sizeof(long));
	m_HoldError = (int*)malloc(m_MemNum*sizeof(int));
	m_ErrorRatio = (float*)malloc(m_MemNum*sizeof(float));

	i = 0;
	char sz[1000];
	// read head(1 row)
	fin.getline(sz, 1000);
	while (!fin.eof()) {
		char t;
		if (i >= m_MemNum)
		{
			m_MemNum += 10;
//			m_HoldStartTime = (SYSTEMTIME)realloc(m_HoldStartTime, m_MemNum*sizeof(SYSTEMTIME));
//			m_HoldSureTime = (SYSTEMTIME)realloc(m_HoldSureTime, m_MemNum*sizeof(SYSTEMTIME));
			m_HoldTime = (int*)realloc(m_HoldTime, m_MemNum*sizeof(int));
			m_TestRT = (long*)realloc(m_TestRT, m_MemNum*sizeof(long));
			m_HoldError = (int*)realloc(m_HoldError, m_MemNum*sizeof(int));
			m_ErrorRatio = (float*)realloc(m_ErrorRatio, m_MemNum*sizeof(float));
		}

		fin >> m_PartInfo.m_TesterNo;
		if (fin.fail()) break;
		fin >> m_PartInfo.m_TesterName
			>> m_PartInfo.m_TesterSex
			>> m_PartInfo.m_Session
			>> m_HardSetting.m_DistanceError
			>> m_ReadSetting2[0].m_PracMode
			>> m_ReadSetting2[0].m_ExperMode
			>> m_ReadSetting2[0].m_MainTask
			>> m_ReadSetting2[0].m_SubTask
			>> m_ReadSetting2[0].m_Background
			>> m_ReadSetting2[0].m_Direction
			>> m_ReadSetting2[0].m_InitSpeed
			>> m_ReadSetting2[0].m_HoldTimeNum
			>> m_ReadSetting2[0].m_HoldTime[0]
			>> m_ReadSetting2[0].m_HoldTime[1]
			>> m_ReadSetting2[0].m_HoldTime[2]
			>> m_ReadSetting2[0].m_HoldTime[3]
			>> m_ReadSetting2[0].m_HoldTime[4]
			>> m_ReadSetting2[0].m_HoldTime[5]
			>> m_ReadSetting2[0].m_HoldTime[6]
			>> m_ReadSetting2[0].m_HoldTime[7]
			>> m_ReadSetting2[0].m_HoldTime[8]
			>> m_ReadSetting2[0].m_HoldTime[9]
			>> m_ReadSetting2[0].m_HoldTime[10]
			>> m_ReadSetting2[0].m_HoldTime[11]
			>> m_ReadSetting2[0].m_PracTime
			>> m_ReadSetting2[0].m_ExperTime
			>> m_ReadSetting2[0].m_PracTimes
			>> m_ReadSetting2[0].m_ExperTimes
			>> m_TrialType
			>> m_HoldNo
			>> m_HoldTime[i]
			>> m_HoldStartTime.wHour >> t
			>> m_HoldStartTime.wMinute >> t
			>> m_HoldStartTime.wSecond
			>> m_HoldSureTime.wHour >> t
			>> m_HoldSureTime.wMinute >> t
			>> m_HoldSureTime.wSecond
			>> m_TestRT[i]
			>> m_HoldError[i]
			>> m_ErrorRatio[i];
			if (m_TrialType == 0)
			{
				m_ExperStart2 = i;
			}
			if (!bBatch)
				if (m_TrialType == 0 || m_TrialType == 1)
				{
					m_pWSDlg->m_ListDlg.AddT2HoldItem(i);
				}

		i++;
	}

    /*fopen_s(&fp, m_FileName2,"rt");
	i = 0;
	if(fp!=NULL)
	{
		m_MemNum = 100;
		//m_HoldStartTime = (long*)malloc(m_MemNum*sizeof(long));
		//m_HoldSureTime = (long*)malloc(m_MemNum*sizeof(long));
		m_HoldTime = (int*)malloc(m_MemNum*sizeof(int));
		m_TestRT = (long*)malloc(m_MemNum*sizeof(long));
		m_HoldError = (int*)malloc(m_MemNum*sizeof(int));
        m_ErrorRatio = (float*)malloc(m_MemNum*sizeof(float));

//		fprintf(fp,"ID\tName\tSex\tSession\t"
//			"DistanceError\tPracMode\tExperMode\tMainTask\tSubTask\t"
//			"Background\tDirection\tInitSpeed\t"
//			"HoldTimeNum\tHoldTime1\tHoldTime2\tHoldTime3\tHoldTime4\tHoldTime5\tHoldTime6\tHoldTime7\tHoldTime8\tHoldTime9\tHoldTime10\tHoldTime11\tHoldTime12\tPracTime\tExperTime\tPracTimes\tExperTimes\t"
//			"Pra_Test\tHoldNum\tHoldTime\tStartTime\tSureTime\tTest_RT\tHoldError\tError_Ratio\n");
        fgets(tmp,1000,fp);
		try{
			while(!feof(fp))
			{
				fp1 = fp;
				char t;
				if(i>=m_MemNum)
				{
					m_MemNum+=100;
					m_HoldStartTime = (char*)realloc(m_HoldStartTime,m_MemNum*sizeof(char));
					m_HoldSureTime = (char*)realloc(m_HoldSureTime,m_MemNum*sizeof(char));
					m_HoldTime = (int*)realloc(m_HoldTime,m_MemNum*sizeof(int));
					m_TestRT = (long*)realloc(m_TestRT,m_MemNum*sizeof(long));
					m_HoldError = (int*)realloc(m_HoldError,m_MemNum*sizeof(int));
					m_ErrorRatio = (float*)realloc(m_ErrorRatio,m_MemNum*sizeof(float));
				}

				fscanf_s(fp,"%s\t%s\t%s\t%d\t"
					"%f\t%d\t%d\t%d\t%d\t"
					"%d\t%d\t%f\t"
					"%d\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%d\t%d\t%d\t%d\t"
					"%d\t%d\t%d\t%s\t%s\t%d\t%d\t%f\n",
					m_PartInfo.m_TesterNo,20, m_PartInfo.m_TesterName,20, m_PartInfo.m_TesterSex,10, &m_PartInfo.m_Session, 
					&m_HardSetting.m_DistanceError, &m_ReadSetting2[0].m_PracMode, &m_ReadSetting2[0].m_ExperMode, &m_ReadSetting2[0].m_MainTask, &m_ReadSetting2[0].m_SubTask,
					&m_ReadSetting2[0].m_Background, &m_ReadSetting2[0].m_Direction, &m_ReadSetting2[0].m_InitSpeed, 
					&m_ReadSetting2[0].m_HoldTimeNum, &m_ReadSetting2[0].m_HoldTime[0], &m_ReadSetting2[0].m_HoldTime[1], &m_ReadSetting2[0].m_HoldTime[2], &m_ReadSetting2[0].m_HoldTime[3], &m_ReadSetting2[0].m_HoldTime[4], &m_ReadSetting2[0].m_HoldTime[5], &m_ReadSetting2[0].m_HoldTime[6], &m_ReadSetting2[0].m_HoldTime[7], &m_ReadSetting2[0].m_HoldTime[8], &m_ReadSetting2[0].m_HoldTime[9], &m_ReadSetting2[0].m_HoldTime[10], &m_ReadSetting2[0].m_HoldTime[11], &m_ReadSetting2[0].m_PracTime, &m_ReadSetting2[0].m_ExperTime, &m_ReadSetting2[0].m_PracTimes, &m_ReadSetting2[0].m_ExperTimes,
					&m_TrialType, &m_HoldNo, &m_HoldTime[i], &m_HoldStartTime, &m_HoldSureTime, &m_TestRT[i], &m_HoldError[i], &m_ErrorRatio[i]);
				if(m_TrialType==0)
				{ 
					m_ExperStart2 = i;
				}
				if (!bBatch)
				{
					if(m_TrialType==0||m_TrialType==1)
					{
						 m_pWSDlg->m_ListDlg.AddT2HoldItem(i);
					}
				}
	//			if(fp == fp1)
	//			{
	//				MessageBox("文件格式有误！");
	//				return FALSE;
	//			}
				i++;
			}
			m_ExperStart2 = m_ExperStart2+1;
			m_HoldNo = i;
			fclose(fp);
			if(m_ExperStart2>m_HoldNo)
			{
				return FALSE;
			}
			if(m_TrialType!=0&&m_TrialType!=1)
			{
				return FALSE;
			}
		}
		catch(...)
		{
			AfxMessageBox("数据文件格式错误！");
			return FALSE;
		}
		return TRUE;
	}*/
	return TRUE;
}

BOOL CTaskControlDoc::ReadT3Trace()
{
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
	m_TrialType = -1;
    m_ExperStart1 = -1;
	bExitItem1 = FALSE;
	FILE *fp;
	FILE *fp1;
	CString str;
	int j = 0;
	char tmp[1000];
	int i;

    CString m_SaveName;
	char filestr[50];
	int len;
	_mkdir("Result");
	_mkdir("Result\\Task3");
	m_SaveName = "Result\\Task3\\task3_tracking_result.txt";
	sprintf_s(filestr,50,"%s\t%s",m_TestTime,m_PartInfo.m_TesterNo);
	len = strlen(filestr);
	fopen_s(&fp, m_SaveName,"r");
	{
		if(fp!=NULL)
		{
			fgets(tmp,1000,fp);	
			while(!feof(fp))
			{
				fgets(tmp,1000,fp);	
				if(strncmp(tmp,filestr,len) == 0)
				{
					if(bBatch)
					{
						fclose(fp);
						return FALSE;
					}
					else
					{
	                    bExitItem1 = TRUE;
					}
				}
			}
			bExist1 = TRUE;
			fclose(fp);
		}
		else
		{
			bExist1 = FALSE;
		}
	}

	CResultDlg *m_pWSDlg;
	if (!bBatch)
	{
		m_pWSDlg = (CResultDlg *)pMain->m_pWSDlg;
	}

	fopen_s(&fp, m_FileName1,"rt");
	i = 0;
	if(fp!=NULL)
	{
		/*m_MemNum = 1000;
		//m_ObjPoint = (SPOINT*)malloc(m_MemNum*sizeof(POINT));
		//m_PostPoint = (SPOINT*)malloc(m_MemNum*sizeof(POINT));
		m_Distance = (float*)malloc(m_MemNum*sizeof(float));
		m_PointTime = (unsigned long*)malloc(m_MemNum*sizeof(unsigned long));
		m_bHit = (BOOL*)malloc(m_MemNum*sizeof(BOOL));
		m_ObjSpeedX = (float*)malloc(m_MemNum*sizeof(float));
		m_ObjSpeedY = (float*)malloc(m_MemNum*sizeof(float));
		m_PostSpeedX = (float*)malloc(m_MemNum*sizeof(float));
		m_PostSpeedY = (float*)malloc(m_MemNum*sizeof(float));
		m_ChartTime = (float*)malloc(m_MemNum*sizeof(float));
		m_ObjSpeed = (float*)malloc(m_MemNum*sizeof(float));
		m_PostSpeed = (float*)malloc(m_MemNum*sizeof(float));*/
//		fprintf(fp,"ID\tName\tSex\tSession\t"
//			"DistanceError\tPracMode\tExperMode\tMainTask\tSubTask\t"
//			"MainTaskMode\tBackground\tInitSpeed\tEventMode\tCodePairMode\tCodePairNum\tDisplayMode\tPracTime\tExperTime\tPracTimes\tExperTimes\t"
//			"Pra_Test\tPointNum\tPointTime\tObjPointX\tObjPointY\tPostPointX\tPostPointY\tDistance\tHit\t"
//		    "ObjSpeedX\tObjSpeedY\tPostSpeedX\tPostSpeedY\n");
        fgets(tmp,1000,fp);
		try{
			while(!feof(fp))
			{
				fp1 = fp;
				/*if(i>=m_MemNum)
				{
					m_MemNum+=1000;
					//m_ObjPoint = (SPOINT*)realloc(m_ObjPoint,m_MemNum*sizeof(SPOINT));
     				//m_PostPoint = (SPOINT*)realloc(m_PostPoint,m_MemNum*sizeof(SPOINT));
					m_Distance = (float*)realloc(m_Distance,m_MemNum*sizeof(float));
					m_PointTime = (unsigned long*)realloc(m_PointTime,m_MemNum*sizeof(unsigned long));
					m_bHit = (BOOL*)realloc(m_bHit,m_MemNum*sizeof(BOOL));
					m_ObjSpeedX = (float*)realloc(m_ObjSpeedX,m_MemNum*sizeof(float));
					m_ObjSpeedY = (float*)realloc(m_ObjSpeedY,m_MemNum*sizeof(float));
					m_PostSpeedX = (float*)realloc(m_PostSpeedX,m_MemNum*sizeof(float));
					m_PostSpeedY = (float*)realloc(m_PostSpeedY,m_MemNum*sizeof(float));
					m_ChartTime = (float*)realloc(m_ChartTime,m_MemNum*sizeof(float));
					m_ObjSpeed = (float*)realloc(m_ObjSpeed,m_MemNum*sizeof(float));
	           		m_PostSpeed = (float*)realloc(m_PostSpeed,m_MemNum*sizeof(float));
				}*/
				float m_Distance_t;
				float m_RotateError_t;
				float m_ObjSpeedX_t;
				float m_ObjSpeedY_t;
				float m_PostSpeedX_t;
				float m_PostSpeedY_t;
				unsigned long m_PointTime_t;
				BOOL m_bHit_t;
				fscanf_s(fp,"%s\t%s\t%s\t%d\t"
					"%f\t%d\t%d\t%d\t%d\t"
					"%d\t%d\t%f\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t"
					"%d\t%d\t%u\t%d\t%d\t%d\t%d\t%f\t%d\t"
					"%f\t%f\t%f\t%f\n",
					m_PartInfo.m_TesterNo,20, m_PartInfo.m_TesterName,20, m_PartInfo.m_TesterSex,10, &m_PartInfo.m_Session, 
					&m_HardSetting.m_DistanceError, &m_ReadSetting3[0].m_PracMode, &m_ReadSetting3[0].m_ExperMode, &m_ReadSetting3[0].m_MainTask, &m_ReadSetting3[0].m_SubTask,
					&m_ReadSetting3[0].m_MainTaskMode, &m_ReadSetting3[0].m_Background, &m_ReadSetting3[0].m_InitSpeed, &m_ReadSetting3[0].m_EventMode, &m_ReadSetting3[0].m_CodePairMode, &m_ReadSetting3[0].m_CodePairNum, &m_ReadSetting3[0].m_DisplayMode, &m_ReadSetting3[0].m_EventFrequency, &m_ReadSetting3[0].m_PracTime, &m_ReadSetting3[0].m_ExperTime, &m_ReadSetting3[0].m_PracTimes, &m_ReadSetting3[0].m_ExperTimes, 
					&m_TrialType, /*&m_TrialNo,*/ &m_PointNum, &m_PointTime_t, &m_ObjPoint.x, &m_ObjPoint.y, &m_PostPoint.x, &m_PostPoint.y, &m_Distance_t, &m_bHit_t,
					&m_ObjSpeedX_t, &m_ObjSpeedY_t, &m_PostSpeedX_t, &m_PostSpeedY_t);
				m_Distance.push_back(m_Distance_t);
				m_RotateError.push_back(m_RotateError_t);
				m_ObjSpeedX.push_back(m_ObjSpeedX_t);
				m_ObjSpeedY.push_back(m_ObjSpeedY_t);
				m_PostSpeedX.push_back(m_PostSpeedX_t);
				m_PostSpeedY.push_back(m_PostSpeedY_t);
				m_PointTime.push_back(m_PointTime_t);
				m_bHit.push_back(m_bHit_t);
				m_ObjSpeed.push_back(pow(pow((double)m_ObjSpeedX[i], 2.0) + pow((double)m_ObjSpeedY[i], 2.0), 0.5));
				m_PostSpeed.push_back(pow(pow((double)m_PostSpeedX[i], 2.0) + pow((double)m_PostSpeedY[i], 2.0), 0.5));
	//			if(fp == fp1)
	//			{
	//				MessageBox("文件格式有误！");
	//				return FALSE;
	//			}
				if(m_TrialType==0)
				{ 
					m_ExperStart1 = i;
				}
				if(m_TrialType==1&&m_PointNum==1)
				{ 
					m_StartPoint[j] = i;
					j++;
				} 
				if(m_TrialType==1)
				{
					m_ChartTime.push_back((float)(m_PointTime[i] - m_PointTime[m_StartPoint[j - 1]]) / 1000.0);
				}
				if (!bBatch)
				{
					if(m_TrialType==0||m_TrialType==1)
					{
						m_pWSDlg->m_ListDlg.AddT3TraceItem(i);
					}
				}
				i++;
			}
			
			m_ExperStart1 = m_ExperStart1+1;
			m_PointNum = i;		
			fclose(fp);
			if (m_ExperStart1 > m_PointNum)
				//if(m_ExperStart1>=m_PointNum-1)
			{
				return FALSE;
			}
			if(m_TrialType!=0&&m_TrialType!=1)
			{
				return FALSE;
			}
			m_StartPoint[1] = m_PointNum;
			m_TrialNum = 1;
		}
		catch(...)
		{
			AfxMessageBox("数据文件格式错误！");
			return FALSE;
		}
		return TRUE;
	}
	return FALSE;
}
//已经废弃不用了
BOOL CTaskControlDoc::ReadT3Code()
{
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
	m_TrialType = -1;
    m_ExperStart1 = -1;
	bExitItem1 = FALSE;
    FILE *fp;
	FILE *fp1;
	CString str;
	char tmp[1000];
	int i;

    CString m_SaveName;
	char filestr[50];
	int len;
	_mkdir("Result");
	_mkdir("Result\\Task3");
	m_SaveName = "Result\\Task3\\task3_coding_result.txt";
	sprintf_s(filestr,50,"%s\t%s",m_TestTime,m_PartInfo.m_TesterNo);
	len = strlen(filestr);
	fopen_s(&fp, m_SaveName,"r");
	{
		if(fp!=NULL)
		{
			fgets(tmp,1000,fp);	
			while(!feof(fp))
			{
				fgets(tmp,1000,fp);	
				if(strncmp(tmp,filestr,len) == 0)
				{
					if(bBatch)
					{
						fclose(fp);
						return FALSE;
					}
					else
					{
	                    bExitItem1 = TRUE;
					}
				}
			}
			bExist1 = TRUE;
			fclose(fp);
		}
		else
		{
			bExist1 = FALSE;
		}
	}

	CResultDlg *m_pWSDlg;
	if (!bBatch)
	{
		m_pWSDlg = (CResultDlg *)pMain->m_pWSDlg;
	}

    fopen_s(&fp, m_FileName1,"rt");
	i = 0;
	if(fp!=NULL)
	{
		m_MemNum = 100;
		m_CodeType = (short*)malloc(m_MemNum*sizeof(short));
		m_CodeStartTime = (unsigned long*)malloc(m_MemNum*sizeof(unsigned long));
		m_CodeSureTime = (unsigned long*)malloc(m_MemNum*sizeof(unsigned long));
		m_CodeButtonNo = (short*)malloc(m_MemNum*sizeof(short));
		m_CodeRT = (long*)malloc(m_MemNum*sizeof(long));
        m_bCodeAcc = (int*)malloc(m_MemNum*sizeof(int));
		
//		fprintf(fp,"ID\tName\tSex\tSession\t"
//			"PracMode\tExperMode\tMainTask\tSubTask\t"
//			"MainTaskMode\tBackground\tInitSpeed\tEventMode\tCodePairMode\tCodePairNum\tDisplayMode\tPracTime\tExperTime\tPracTimes\tExperTimes\t"
//			"Shape1\tNumber1\tShape2\tNumber2\tShape3\tNumber3\tShape4\tNumber4\tShape5\tNumber5\tShape6\tNumber6\t"
//			"Pra_Test\tCodeNum\tCodeType\tStartTime\tSureTime\tCode_RT\tButtonNo\tCode_ACC\n");
        fgets(tmp,1000,fp);

		try
		{
    		while(!feof(fp))
			{
				fp1 = fp;
				if(i>=m_MemNum)
				{
					m_MemNum+=100;
					m_CodeType = (short*)realloc(m_CodeType,m_MemNum*sizeof(short));
					m_CodeStartTime = (unsigned long*)realloc(m_CodeStartTime,m_MemNum*sizeof(unsigned long));
					m_CodeSureTime = (unsigned long*)realloc(m_CodeSureTime,m_MemNum*sizeof(unsigned long));
					m_CodeButtonNo = (short*)realloc(m_CodeButtonNo,m_MemNum*sizeof(short));
					m_CodeRT = (long*)realloc(m_CodeRT,m_MemNum*sizeof(long));
					m_bCodeAcc = (int*)realloc(m_bCodeAcc,m_MemNum*sizeof(int));
				}
				fscanf_s(fp,"%s\t%s\t%s\t%d\t"
					"%d\t%d\t%d\t%d\t"
					"%d\t%d\t%f\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t"
					"%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t"
					"%d\t%d\t%d\t%u\t%u\t%d\t%d\t%d\n",
					m_PartInfo.m_TesterNo,20, m_PartInfo.m_TesterName,20, m_PartInfo.m_TesterSex,10, &m_PartInfo.m_Session, 
					&m_ReadSetting3[0].m_PracMode, &m_ReadSetting3[0].m_ExperMode, &m_ReadSetting3[0].m_MainTask, &m_ReadSetting3[0].m_SubTask,
					&m_ReadSetting3[0].m_MainTaskMode, &m_ReadSetting3[0].m_Background, &m_ReadSetting3[0].m_InitSpeed, &m_ReadSetting3[0].m_EventMode, &m_ReadSetting3[0].m_CodePairMode, &m_CodePairNum, &m_ReadSetting3[0].m_DisplayMode, &m_ReadSetting3[0].m_EventFrequency, &m_ReadSetting3[0].m_PracTime, &m_ReadSetting3[0].m_ExperTime, &m_ReadSetting3[0].m_PracTimes, &m_ReadSetting3[0].m_ExperTimes, 
					&m_Shape[0], &m_Character[0],&m_Shape[1],&m_Character[1],&m_Shape[2],&m_Character[2],&m_Shape[3],&m_Character[3],&m_Shape[4],&m_Character[4],&m_Shape[5],&m_Character[5],
					&m_TrialType, &m_CodeNo, &m_CodeType[i], &m_CodeStartTime[i], &m_CodeSureTime[i], &m_CodeRT[i], &m_CodeButtonNo[i], &m_bCodeAcc[i]);		
				for(int j=0;j<m_CodePairNum;j++)
				{
					if(m_Shape[j]==m_CodeType[i])
					{
						m_bCodeAcc[i] = (m_Character[j]==m_CodeButtonNo[i]);
					}
				}
				
				if(m_TrialType==0)
				{ 
					m_ExperStart1 = i;
				}
	//			if(fp == fp1)
	//			{
	//				MessageBox("文件格式有误！");
	//				return FALSE;
	//			}
				if (!bBatch)
				{
					if(m_TrialType==0||m_TrialType==1)
					{
						m_pWSDlg->m_ListDlg.AddT3CodeItem(i);
					}
				}
				i++;
			}
			m_ExperStart1 = m_ExperStart1+1;
			m_CodeNo = i;
			fclose(fp);
			if (m_ExperStart1 > m_CodeNo)
				//if(m_ExperStart1>=m_CodeNo-1)
			{
				return FALSE;
			}
			if(m_TrialType!=0&&m_TrialType!=1)
			{
				return FALSE;
			}
		}
		catch(...)
		{
			AfxMessageBox("数据文件格式错误！");
			return FALSE;
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CTaskControlDoc::ReadT3Event()
{
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
	m_TrialType = -1;
    m_ExperStart2 = -1;
	bExitItem2 = FALSE;
    FILE *fp;
	FILE *fp1;
	CString str;
	char tmp[1000];
	int i;

    CString m_SaveName;
	char filestr[50];
	int len;
	_mkdir("Result");
	_mkdir("Result\\Task3");
	m_SaveName = "Result\\Task3\\task3_event_result.txt";
	sprintf_s(filestr,50,"%s\t%s",m_TestTime,m_PartInfo.m_TesterNo);
	len = strlen(filestr);
	fopen_s(&fp, m_SaveName,"r");
	{
		if(fp!=NULL)
		{
			fgets(tmp,1000,fp);	
			while(!feof(fp))
			{
				fgets(tmp,1000,fp);	
				if(strncmp(tmp,filestr,len) == 0)
				{
					if(bBatch)
					{
						fclose(fp);
						return FALSE;
					}
					else
					{
	                    bExitItem2 = TRUE;
					}
				}
			}
			bExist2 = TRUE;
			fclose(fp);
		}
		else
		{
			bExist2 = FALSE;
		}
	}

	CResultDlg *m_pWSDlg;
	if (!bBatch)
	{
		m_pWSDlg = (CResultDlg *)pMain->m_pWSDlg;
	}

    fopen_s(&fp, m_FileName2,"rt");
	i = 0;
	if(fp!=NULL)
	{
		m_MemNum = 100;
		m_EventType = (short*)malloc(m_MemNum*sizeof(short));
		m_EventStartTime = (unsigned long*)malloc(m_MemNum*sizeof(unsigned long));
		m_EventSureTime = (unsigned long*)malloc(m_MemNum*sizeof(unsigned long));
		m_SureButtonNo = (short*)malloc(m_MemNum*sizeof(short));
        m_EventRT = (long*)malloc(m_MemNum*sizeof(long));
		m_bEventAcc = (int*)malloc(m_MemNum*sizeof(int));
//		fprintf(fp,"ID\tName\tSex\tSession\t"
//			"PracMode\tExperMode\tMainTask\tSubTask\t"
//			"MainTaskMode\tBackground\tInitSpeed\tEventMode\tCodePairMode\tCodePairNum\tDisplayMode\tPracTime\tExperTime\tPracTimes\tExperTimes\t"
//			"Pra_Test\tEventNum\tEventType\tStartTime\tSureTime\tEvent_RT\tButtonNo\tEvent_Acc\n");
        fgets(tmp,1000,fp);
		try
		{
			while(!feof(fp))
			{
				fp1 = fp;
				if(i>=m_MemNum)
				{
					m_MemNum+=100;
					m_EventType = (short*)realloc(m_EventType,m_MemNum*sizeof(short));
					m_EventStartTime = (unsigned long*)realloc(m_EventStartTime,m_MemNum*sizeof(unsigned long));
					m_EventSureTime = (unsigned long*)realloc(m_EventSureTime,m_MemNum*sizeof(unsigned long));
					m_SureButtonNo = (short*)realloc(m_SureButtonNo,m_MemNum*sizeof(short));
					m_EventRT = (long*)realloc(m_EventRT,m_MemNum*sizeof(long));
					m_bEventAcc = (int*)realloc(m_bEventAcc,m_MemNum*sizeof(int));
				}

				fscanf_s(fp,"%s\t%s\t%s\t%d\t"
					"%d\t%d\t%d\t%d\t"
					"%d\t%d\t%f\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t"
					"%d\t%d\t%d\t%d:%d:%d\t%d:%d:%d\t%d\t%d\t%d\n",
					m_PartInfo.m_TesterNo,20, m_PartInfo.m_TesterName,20, m_PartInfo.m_TesterSex, 10,&m_PartInfo.m_Session, 
					&m_ReadSetting3[0].m_PracMode, &m_ReadSetting3[0].m_ExperMode, &m_ReadSetting3[0].m_MainTask, &m_ReadSetting3[0].m_SubTask,
					&m_ReadSetting3[0].m_MainTaskMode, &m_ReadSetting3[0].m_Background, &m_ReadSetting3[0].m_InitSpeed, &m_ReadSetting3[0].m_EventMode, &m_ReadSetting3[0].m_CodePairMode, &m_ReadSetting3[0].m_CodePairNum, &m_ReadSetting3[0].m_DisplayMode, &m_ReadSetting3[0].m_EventFrequency, &m_ReadSetting3[0].m_PracTime, &m_ReadSetting3[0].m_ExperTime, &m_ReadSetting3[0].m_PracTimes, &m_ReadSetting3[0].m_ExperTimes, 
					&m_TrialType, &m_RecordNo, &m_EventType[i], &m_HoldStartTime.wHour, &m_HoldStartTime.wMinute, &m_HoldStartTime.wSecond, &m_HoldSureTime.wHour, &m_HoldSureTime.wMinute, &m_HoldSureTime.wSecond, &m_EventRT[i],&m_SureButtonNo[i],&m_bEventAcc[i]);
				if(m_TrialType==0)
				{ 
					m_ExperStart2 = i;
				}

	//			if(fp == fp1)
	//			{
	//				MessageBox("文件格式有误！");
	//				return FALSE;
	//			}
				if (!bBatch)
				{
					if(m_TrialType==0||m_TrialType==1)
					{
			    		m_pWSDlg->m_ListDlg.AddT3EventItem(i);
					}
				}
				i++;
			}
			m_ExperStart2 = m_ExperStart2+1;
			m_RecordNo = i;
			fclose(fp);
			if (m_ExperStart2 > m_RecordNo)
				//if(m_ExperStart2>=m_RecordNo-1)
			{
				return FALSE;
			}
			if(m_TrialType!=0&&m_TrialType!=1)
			{
				return FALSE;
			}
		}
		catch(...)
		{
			AfxMessageBox("数据文件格式错误！");
			return FALSE;
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CTaskControlDoc::ReadT4()
{
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
	m_TrialType = -1;
	m_ExperStart1 = -1;
	bExitItem1 = FALSE;
	FILE *fp;
	FILE *fp1;
	CString str;
	char tmp[1000];

    CString m_SaveName;
	char filestr[50];
	int len;
	_mkdir("Result");
	_mkdir("Result\\Task4");
	m_SaveName = "Result\\Task4\\task4_touch_result.txt";
	sprintf_s(filestr,50,"%s\t%s",m_TestTime,m_PartInfo.m_TesterNo);
	len = strlen(filestr);
	fopen_s(&fp, m_SaveName,"r");
	{
		if(fp!=NULL)
		{
			fgets(tmp,1000,fp);	
			while(!feof(fp))
			{
				fgets(tmp,1000,fp);	
				if(strncmp(tmp,filestr,len) == 0)
				{
					if(bBatch)
					{
						fclose(fp);
						return FALSE;
					}
					else
					{
	                    bExitItem1 = TRUE;
					}
				}
			}
			bExist1 = TRUE;
			fclose(fp);
		}
		else
		{
			bExist1 = FALSE;
		}
	}

	CResultDlg *m_pWSDlg;
	if (!bBatch)
	{
		m_pWSDlg = (CResultDlg *)pMain->m_pWSDlg;
	}

	fopen_s(&fp, m_FileName,"rt");
	int i = 0;

	if(fp!=NULL)
	{
		m_MemNum = 100;
		m_TouchNoOrder = (int*)malloc(m_MemNum*sizeof(int));
		m_TouchStartTime = (unsigned long*)malloc(m_MemNum*sizeof(unsigned long));
		m_TouchSureTime = (unsigned long*)malloc(m_MemNum*sizeof(unsigned long));
		m_TouchRT = (unsigned long*)malloc(m_MemNum*sizeof(unsigned long));
		m_TouchAcc = (int*)malloc(m_MemNum*sizeof(int));
		m_TouchDistance = (int*)malloc(m_MemNum*sizeof(int));
		m_sizediff = (int*)malloc(m_MemNum*sizeof(int));
        m_SureButtonNo = (short*)malloc(m_MemNum*sizeof(short));
				
//		fprintf(fp,"ID\tName\tSex\tSession\t"
//			"PracMode\tExperMode\t"
//			"Pra_Test\tGroupNo\tTestNo\tTouchNo\tDistance\tSizeDiff\t"
//			"SureNo\tStartTime\tTouchTime\tTouch_RT\tTouch_Acc\n");
        fgets(tmp,1000,fp);
		try{
			while(!feof(fp))
			{
				fp1 = fp;
				if(i>=m_MemNum)
				{
					m_MemNum+=100;
					m_TouchNoOrder = (int*)realloc(m_TouchNoOrder, m_MemNum*sizeof(int));
					m_TouchStartTime = (unsigned long*)realloc(m_TouchStartTime, m_MemNum*sizeof(unsigned long));
					m_TouchSureTime = (unsigned long*)realloc(m_TouchSureTime, m_MemNum*sizeof(unsigned long));
					m_TouchRT = (unsigned long*)realloc(m_TouchRT, m_MemNum*sizeof(unsigned long));
					m_TouchAcc = (int*)realloc(m_TouchAcc, m_MemNum*sizeof(int));
					m_TouchDistance = (int*)realloc(m_TouchDistance, m_MemNum*sizeof(int));
					m_sizediff = (int*)realloc(m_sizediff, m_MemNum*sizeof(int));
					m_SureButtonNo = (short*)realloc(m_SureButtonNo,m_MemNum*sizeof(short));
				}
				fscanf_s(fp,"%s\t%s\t%s\t%d\t"
					"%d\t%d\t%d\t"
					"%d\t%d\t%d\t%d\t%d\t%d\t"
					"%d\t%u\t%u\t%u\t%d\n",
					m_PartInfo.m_TesterNo,20, m_PartInfo.m_TesterName,20, m_PartInfo.m_TesterSex, 10,&m_PartInfo.m_Session,
					&m_ReadSetting4[0].m_PracMode, &m_ReadSetting4[0].m_ExperMode, &m_ReadSetting4[0].m_TouchOrder,
					&m_TrialType,&m_TouchGroupNo,&m_TouchNo,&m_TouchNoOrder[i],&m_TouchDistance[i],&m_sizediff[i],
					&m_SureButtonNo[i],&m_TouchStartTime[i],&m_TouchSureTime[i],&m_TouchRT[i],&m_TouchAcc[i]);		
				if(m_TrialType==0)
				{ 
					m_ExperStart1 = i;
				}
	//			if(fp == fp1)
	//			{
	//				MessageBox("文件格式有误！");
	//				return FALSE;
	//			}
				if (!bBatch)
				{
					if(m_TrialType==0||m_TrialType==1)
					{
			    		m_pWSDlg->m_ListDlg.AddT4Item(i);
					}
				}
				i++;
			}
			m_ExperStart1 = m_ExperStart1+1;
			m_TouchNo = i;
			fclose(fp);
			if(m_ExperStart1>=m_TouchNo-1)
			{
				return FALSE;
			}
			if(m_TrialType!=0&&m_TrialType!=1)
			{
				return FALSE;
			}
		}
		catch(...)
		{
			AfxMessageBox("数据文件格式错误！");
			return FALSE;
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CTaskControlDoc::ReadT5Trace()
{
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
	m_TrialType = -1;
	m_ExperStart1 = -1;
	bExitItem1 = FALSE;
	FILE *fp;
	FILE *fp1;
	CString str;
	int j = 0;
	char tmp[1000];
	int i;

    CString m_SaveName;
	char filestr[50];
	int len;
	_mkdir("Result");
	_mkdir("Result\\Task5");
	m_SaveName = "Result\\Task5\\task5_tracking_result.txt";
	sprintf_s(filestr,50,"%s\t%s",m_TestTime,m_PartInfo.m_TesterNo);
	len = strlen(filestr);
	fopen_s(&fp, m_SaveName,"r");
	{
		if(fp!=NULL)
		{
			fgets(tmp,1000,fp);	
			while(!feof(fp))
			{
				fgets(tmp,1000,fp);	
				if(strncmp(tmp,filestr,len) == 0)
				{
					if(bBatch)
					{
						fclose(fp);
						return FALSE;
					}
					else
					{
	                    bExitItem1 = TRUE;
					}
				}
			}
			bExist1 = TRUE;
			fclose(fp);
		}
		else
		{
			bExist1 = FALSE;
		}
	}

	CResultDlg *m_pWSDlg;
	if (!bBatch)
	{
		m_pWSDlg = (CResultDlg *)pMain->m_pWSDlg;

	}

	fopen_s(&fp, m_FileName1,"rt");
	i = 0;
	if(fp!=NULL)
	{
		/*m_MemNum = 1000;
		//m_ObjPoint = (SPOINT*)malloc(m_MemNum*sizeof(POINT));
		//m_PostPoint = (SPOINT*)malloc(m_MemNum*sizeof(POINT));
		m_Distance = (float*)malloc(m_MemNum*sizeof(float));
		m_PointTime = (unsigned long*)malloc(m_MemNum*sizeof(unsigned long));
		m_bHit = (BOOL*)malloc(m_MemNum*sizeof(BOOL));
		m_ObjSpeedX = (float*)malloc(m_MemNum*sizeof(float));
		m_ObjSpeedY = (float*)malloc(m_MemNum*sizeof(float));
		m_PostSpeedX = (float*)malloc(m_MemNum*sizeof(float));
		m_PostSpeedY = (float*)malloc(m_MemNum*sizeof(float));
		m_ChartTime = (float*)malloc(m_MemNum*sizeof(float));
		m_ObjSpeed = (float*)malloc(m_MemNum*sizeof(float));
		m_PostSpeed = (float*)malloc(m_MemNum*sizeof(float));*/
//		fprintf(fp,"ID\tName\tSex\tSession\t"
//			"DistanceError\tPracMode\tExperMode\tMainTask\tSubTask\t"
//			"Background\tInitSpeed\tSignMemType\tSignMemMode\tSignMemNum\tSignShowMode\tSignShowTime\tPracTime\tExperTime\tPracTimes\tExperTimes\t"
//			"Pra_Test\tPointNum\tPointTime\tObjPointX\tObjPointY\tPostPointX\tPostPointY\tDistance\tHit\t"
//		    "ObjSpeedX\tObjSpeedY\tPostSpeedX\tPostSpeedY\n");
        fgets(tmp,1000,fp);
		try{
			while(!feof(fp))
			{
				fp1 = fp;
				/*if(i>=m_MemNum)
				{
					m_MemNum+=1000;
					//m_ObjPoint = (SPOINT*)realloc(m_ObjPoint,m_MemNum*sizeof(SPOINT));
     				//m_PostPoint = (SPOINT*)realloc(m_PostPoint,m_MemNum*sizeof(SPOINT));
					m_Distance = (float*)realloc(m_Distance,m_MemNum*sizeof(float));
					m_PointTime = (unsigned long*)realloc(m_PointTime,m_MemNum*sizeof(unsigned long));
					m_bHit = (BOOL*)realloc(m_bHit,m_MemNum*sizeof(BOOL));
					m_ObjSpeedX = (float*)realloc(m_ObjSpeedX,m_MemNum*sizeof(float));
					m_ObjSpeedY = (float*)realloc(m_ObjSpeedY,m_MemNum*sizeof(float));
					m_PostSpeedX = (float*)realloc(m_PostSpeedX,m_MemNum*sizeof(float));
					m_PostSpeedY = (float*)realloc(m_PostSpeedY,m_MemNum*sizeof(float));
					m_ChartTime = (float*)realloc(m_ChartTime,m_MemNum*sizeof(float));
					m_ObjSpeed = (float*)realloc(m_ObjSpeed,m_MemNum*sizeof(float));
	           		m_PostSpeed = (float*)realloc(m_PostSpeed,m_MemNum*sizeof(float));
				}*/
				float m_Distance_t;
				float m_RotateError_t;
				float m_ObjSpeedX_t;
				float m_ObjSpeedY_t;
				float m_PostSpeedX_t;
				float m_PostSpeedY_t;
				unsigned long m_PointTime_t;
				BOOL m_bHit_t;
				fscanf_s(fp,"%s\t%s\t%s\t%d\t"
					"%f\t%d\t%d\t%d\t%d\t"
					"%d\t%f\t%d\t%d\t%d\t%d\t%f\t%d\t%d\t%d\t%d\t"
					"%d\t%d\t%u\t%d\t%d\t%d\t%d\t%f\t%d\t"
					"%f\t%f\t%f\t%f\n",
					m_PartInfo.m_TesterNo,20, m_PartInfo.m_TesterName,20, m_PartInfo.m_TesterSex, 10,&m_PartInfo.m_Session, 
					&m_HardSetting.m_DistanceError, &m_ReadSetting5[0].m_PracMode, &m_ReadSetting5[0].m_ExperMode, &m_ReadSetting5[0].m_MainTask, &m_ReadSetting5[0].m_SubTask,
					&m_ReadSetting5[0].m_Background, &m_ReadSetting5[0].m_InitSpeed, &m_ReadSetting5[0].m_SignMemType, &m_ReadSetting5[0].m_SignMemMode, &m_SignMemNum, &m_ReadSetting5[0].m_SignShowMode, &m_ReadSetting5[0].m_SignShowTime, &m_ReadSetting5[0].m_PracTime, &m_ReadSetting5[0].m_ExperTime, &m_ReadSetting5[0].m_PracTimes, &m_ReadSetting5[0].m_ExperTimes,
					&m_TrialType, /*&m_TrialNo,*/ &m_PointNum, &m_PointTime_t, &m_ObjPoint.x, &m_ObjPoint.y, &m_PostPoint.x, &m_PostPoint.y, &m_Distance_t, &m_bHit_t,
					&m_ObjSpeedX_t, &m_ObjSpeedY_t, &m_PostSpeedX_t, &m_PostSpeedY_t);
				m_Distance.push_back(m_Distance_t);
				m_RotateError.push_back(m_RotateError_t);
				m_ObjSpeedX.push_back(m_ObjSpeedX_t);
				m_ObjSpeedY.push_back(m_ObjSpeedY_t);
				m_PostSpeedX.push_back(m_PostSpeedX_t);
				m_PostSpeedY.push_back(m_PostSpeedY_t);
				m_PointTime.push_back(m_PointTime_t);
				m_bHit.push_back(m_bHit_t);
				m_ObjSpeed.push_back(pow(pow((double)m_ObjSpeedX[i], 2.0) + pow((double)m_ObjSpeedY[i], 2.0), 0.5));
				m_PostSpeed.push_back(pow(pow((double)m_PostSpeedX[i], 2.0) + pow((double)m_PostSpeedY[i], 2.0), 0.5));
	//			if(fp == fp1)
	//			{
	//				MessageBox("文件格式有误！");
	//				return FALSE;
	//			}
				if(m_TrialType==0)
				{ 
					m_ExperStart1 = i;
				}
				if(m_TrialType==1&&m_PointNum==1)
				{ 
					m_StartPoint[j] = i;
					j++;
				} 
				if(m_TrialType==1)
				{
					m_ChartTime.push_back((float)(m_PointTime[i] - m_PointTime[m_StartPoint[j - 1]]) / 1000.0);
				}
				if (!bBatch)
				{
					if(m_TrialType==0||m_TrialType==1)
					{
			    		m_pWSDlg->m_ListDlg.AddT5TraceItem(i);
					}
				}
				i++;
			}
			
			m_ExperStart1 = m_ExperStart1+1;
			m_PointNum = i;
			fclose(fp);

			if(m_ExperStart2>=m_PointNum-1)
			{
				return FALSE;
			}
			if(m_TrialType!=0&&m_TrialType!=1)
			{
				return FALSE;
			}	
			m_StartPoint[1] = m_PointNum;
			m_TrialNum = 1;
		}
		catch(...)
		{
			AfxMessageBox("数据文件格式错误！");
			return FALSE;
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CTaskControlDoc::ReadT5Sign()
{
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
	m_TrialType = -1;
    m_ExperStart2 = -1;
	bExitItem2 = FALSE;
	FILE *fp;
	FILE *fp1;
	CString str;
	char tmp[1000];
	int i;

    CString m_SaveName;
	char filestr[50];
	int len;
	_mkdir("Result");
	_mkdir("Result\\Task5");
	m_SaveName = "Result\\Task5\\task5_sign_result.txt";
	sprintf_s(filestr,50,"%s\t%s",m_TestTime,m_PartInfo.m_TesterNo);
	len = strlen(filestr);
	fopen_s(&fp, m_SaveName,"r");
	{
		if(fp!=NULL)
		{
			fgets(tmp,1000,fp);	
			while(!feof(fp))
			{
				fgets(tmp,1000,fp);	
				if(strncmp(tmp,filestr,len) == 0)
				{
					if(bBatch)
					{
						fclose(fp);
						return FALSE;
					}
					else
					{
	                    bExitItem2 = TRUE;
					}
				}
			}
			bExist2 = TRUE;
			fclose(fp);
		}
		else
		{
			bExist2 = FALSE;
		}
	}

	CResultDlg *m_pWSDlg;
	if (!bBatch)
	{
		m_pWSDlg = (CResultDlg *)pMain->m_pWSDlg;
	}

    fopen_s(&fp, m_FileName2,"rt");
	i = 0;
	if(fp!=NULL)
	{
		m_MemNum = 100;
		m_SignType = (short*)malloc(m_MemNum*sizeof(short));
		m_SignMemNum = (short*)malloc(m_MemNum*sizeof(short));
		m_SignStartTime = (unsigned long*)malloc(m_MemNum*sizeof(unsigned long));
		m_SignSureTime = (unsigned long*)malloc(m_MemNum*sizeof(unsigned long));
		m_SureButtonNo = (short*)malloc(m_MemNum*sizeof(short));
		m_SignRT = (unsigned long*)malloc(m_MemNum*sizeof(unsigned long));
		m_SignAcc = (int*)malloc(m_MemNum*sizeof(int));
//		fprintf(fp,"ID\tName\tSex\tSession\t"
//			"DistanceError\tPracMode\tExperMode\tMainTask\tSubTask\t"
//			"Background\tInitSpeed\tSignMemType\tSignMemMode\tSignMemNum\tSignShowMode\tSignShowTime\tPracTime\tExperTime\tPracTimes\tExperTimes\t"
//			"Pra_Test\tGroupNo\tSignNo\tMemTime\tSignType\tSignName\tStartTime\tSureTime\tSureButton\tSign_RT\tSign_Acc\n");
        fgets(tmp,1000,fp);
		try{
			while(!feof(fp))
			{
				fp1 = fp;
				if(i>=m_MemNum)
				{
					m_MemNum+=100;
					m_SignType = (short*)realloc(m_SignType,m_MemNum*sizeof(short));
					m_SignMemNum = (short*)realloc(m_SignMemNum,m_MemNum*sizeof(short));
					m_SignStartTime = (unsigned long*)realloc(m_SignStartTime,m_MemNum*sizeof(unsigned long));
					m_SignSureTime = (unsigned long*)realloc(m_SignSureTime,m_MemNum*sizeof(unsigned long));
					m_SureButtonNo = (short*)realloc(m_SureButtonNo,m_MemNum*sizeof(short));
					m_SignRT = (unsigned long*)realloc(m_SignRT,m_MemNum*sizeof(unsigned long));
					m_SignAcc = (int*)realloc(m_SignAcc,m_MemNum*sizeof(int));
				}

				fscanf_s(fp,"%s\t%s\t%s\t%d\t"
					"%f\t%d\t%d\t%d\t%d\t"
					"%d\t%f\t%d\t%d\t%d\t%d\t%f\t%d\t%d\t%d\t%d\t"
					"%d\t%d\t%d\t%u\t%d\t%s\t%u\t%u\t%d\t%u\t%d\n",
					m_PartInfo.m_TesterNo,20, m_PartInfo.m_TesterName,20, m_PartInfo.m_TesterSex,10, &m_PartInfo.m_Session, 
					&m_HardSetting.m_DistanceError, &m_ReadSetting5[0].m_PracMode, &m_ReadSetting5[0].m_ExperMode, &m_ReadSetting5[0].m_MainTask, &m_ReadSetting5[0].m_SubTask,
					&m_ReadSetting5[0].m_Background, &m_ReadSetting5[0].m_InitSpeed, &m_ReadSetting5[0].m_SignMemType, &m_ReadSetting5[0].m_SignMemMode, &m_SignMemNum[i], &m_ReadSetting5[0].m_SignShowMode, &m_ReadSetting5[0].m_SignShowTime, &m_ReadSetting5[0].m_PracTime, &m_ReadSetting5[0].m_ExperTime, &m_ReadSetting5[0].m_PracTimes, &m_ReadSetting5[0].m_ExperTimes,
					&m_TrialType, &m_SignGroupNo, &m_SignNo, &m_MemTime, &m_SignType[i], m_SignName,30, &m_SignStartTime[i], &m_SignSureTime[i], &m_SureButtonNo[i], &m_SignRT[i], &m_SignAcc[i]);		
				if(m_TrialType==0)
				{ 
					m_ExperStart2 = i;
				}
	//			if(fp == fp1)
	//			{
	//				MessageBox("文件格式有误！");
	//				return FALSE;
	//			}
				if (!bBatch)
				{
					if(m_TrialType==0||m_TrialType==1)
					{
			    		m_pWSDlg->m_ListDlg.AddT5SignItem(i);
					}
				}
				i++;
			}
			m_ExperStart2 = m_ExperStart2+1;
			m_RecordNo = i;
			fclose(fp);
			if(m_ExperStart2>=m_RecordNo-1)
			{
				return FALSE;
			}
			if(m_TrialType!=0&&m_TrialType!=1)
			{
				return FALSE;
			}
		}
		catch(...)
		{
			AfxMessageBox("数据文件格式错误！");
			return FALSE;
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CTaskControlDoc::ReadT6Trace()
{
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
	m_TrialType = -1;
	bExitItem1 = FALSE;
    m_ExperStart1 = -1;
	FILE *fp;
	FILE *fp1;
	CString str;
	int j = 0;
    char tmp[1000];
	int i;

    CString m_SaveName;
	char filestr[50];
	int len;
	_mkdir("Result");
	_mkdir("Result\\Task6");
	m_SaveName = "Result\\Task6\\task6_tracking_result.txt";
	sprintf_s(filestr,50,"%s\t%s",m_TestTime,m_PartInfo.m_TesterNo);
	len = strlen(filestr);
	fopen_s(&fp, m_SaveName,"r");
	{
		if(fp!=NULL)
		{
			fgets(tmp,1000,fp);	
			while(!feof(fp))
			{
				fgets(tmp,1000,fp);	
				if(strncmp(tmp,filestr,len) == 0)
				{
					if(bBatch)
					{
						fclose(fp);
						return FALSE;
					}
					else
					{
	                    bExitItem1 = TRUE;
					}
				}
			}
			bExist1 = TRUE;
			fclose(fp);
		}
		else
		{
			bExist1 = FALSE;
		}
	}

	CResultDlg *m_pWSDlg;
	if (!bBatch)
	{
		m_pWSDlg = (CResultDlg *)pMain->m_pWSDlg;
	}

	fopen_s(&fp, m_FileName1,"rt");
	i = 0;
	if(fp!=NULL)
	{
		/*m_MemNum = 1000;
		//m_ObjPoint = (SPOINT*)malloc(m_MemNum*sizeof(POINT));
		//m_PostPoint = (SPOINT*)malloc(m_MemNum*sizeof(POINT));
		m_Distance = (float*)malloc(m_MemNum*sizeof(float));
		m_PointTime = (unsigned long*)malloc(m_MemNum*sizeof(unsigned long));
		m_bHit = (BOOL*)malloc(m_MemNum*sizeof(BOOL));
		m_ObjSpeedX = (float*)malloc(m_MemNum*sizeof(float));
		m_ObjSpeedY = (float*)malloc(m_MemNum*sizeof(float));
		m_PostSpeedX = (float*)malloc(m_MemNum*sizeof(float));
		m_PostSpeedY = (float*)malloc(m_MemNum*sizeof(float));
		m_ChartTime = (float*)malloc(m_MemNum*sizeof(float));
		m_ObjSpeed = (float*)malloc(m_MemNum*sizeof(float));
		m_PostSpeed = (float*)malloc(m_MemNum*sizeof(float));*/
        fgets(tmp,1000,fp);
//        fscanf(fp,"ID\tName\tSex\tSession\t"
//			"DistanceError\tPracMode\tExperMode\tMainTask\tSubTask\t"
//			"Background\tInitSpeed\tCubeNum1\tCubeNum2\tCubeNum3\tCubeNum4\tPrototype\tRefAxis\tMemTaskMode\tPracTime\tExperTime\tPracTimes\tExperTimes\t"
//			"Pra_Test\tPointNum\tPointTime\tObjPointX\tObjPointY\tPostPointX\tPostPointY\tDistance\tHit\t"
//		    "ObjSpeedX\tObjSpeedY\tPostSpeedX\tPostSpeedY\n");
		try{
 			while(!feof(fp))
			{
				fp1 = fp;
				/*if(i>=m_MemNum)
				{
					m_MemNum+=1000;
					//m_ObjPoint = (SPOINT*)realloc(m_ObjPoint,m_MemNum*sizeof(SPOINT));
     				//m_PostPoint = (SPOINT*)realloc(m_PostPoint,m_MemNum*sizeof(SPOINT));
					m_Distance = (float*)realloc(m_Distance,m_MemNum*sizeof(float));
					m_PointTime = (unsigned long*)realloc(m_PointTime,m_MemNum*sizeof(unsigned long));
					m_bHit = (BOOL*)realloc(m_bHit,m_MemNum*sizeof(BOOL));
					m_ObjSpeedX = (float*)realloc(m_ObjSpeedX,m_MemNum*sizeof(float));
					m_ObjSpeedY = (float*)realloc(m_ObjSpeedY,m_MemNum*sizeof(float));
					m_PostSpeedX = (float*)realloc(m_PostSpeedX,m_MemNum*sizeof(float));
					m_PostSpeedY = (float*)realloc(m_PostSpeedY,m_MemNum*sizeof(float));
					m_ChartTime = (float*)realloc(m_ChartTime,m_MemNum*sizeof(float));
					m_ObjSpeed = (float*)realloc(m_ObjSpeed,m_MemNum*sizeof(float));
					m_PostSpeed = (float*)realloc(m_PostSpeed,m_MemNum*sizeof(float));
				}*/
				float m_Distance_t;
				float m_RotateError_t;
				float m_ObjSpeedX_t;
				float m_ObjSpeedY_t;
				float m_PostSpeedX_t;
				float m_PostSpeedY_t;
				unsigned long m_PointTime_t;
				BOOL m_bHit_t;
				fscanf_s(fp,"%s\t%s\t%s\t%d\t"
					"%f\t%d\t%d\t%d\t%d\t"
					"%d\t%f\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t"
					"%d\t%d\t%u\t%d\t%d\t%d\t%d\t%f\t%d\t"
					"%f\t%f\t%f\t%f\n",
					m_PartInfo.m_TesterNo,20, m_PartInfo.m_TesterName, 20,m_PartInfo.m_TesterSex,10, &m_PartInfo.m_Session, 
					&m_HardSetting.m_DistanceError, &m_ReadSetting6[0].m_PracMode, &m_ReadSetting6[0].m_ExperMode, &m_ReadSetting6[0].m_MainTask, &m_ReadSetting6[0].m_SubTask,
					&m_ReadSetting6[0].m_Background, &m_ReadSetting6[0].m_InitSpeed, &m_ReadSetting6[0].m_CubeNum1, &m_ReadSetting6[0].m_CubeNum2, &m_ReadSetting6[0].m_CubeNum3, &m_ReadSetting6[0].m_CubeNum4, &m_ReadSetting6[0].m_Prototype, &m_ReadSetting6[0].m_RefAxis, &m_ReadSetting6[0].m_MemTaskMode, &m_ReadSetting6[0].m_PracTime, &m_ReadSetting6[0].m_ExperTime, &m_ReadSetting6[0].m_PracTimes, &m_ReadSetting6[0].m_ExperTimes, 
					&m_TrialType, /*&m_TrialNo,*/ &m_PointNum, &m_PointTime_t, &m_ObjPoint.x, &m_ObjPoint.y, &m_PostPoint.x, &m_PostPoint.y, &m_Distance_t, &m_bHit_t,
					&m_ObjSpeedX_t, &m_ObjSpeedY_t, &m_PostSpeedX_t, &m_PostSpeedY_t);
				m_Distance.push_back(m_Distance_t);
				m_RotateError.push_back(m_RotateError_t);
				m_ObjSpeedX.push_back(m_ObjSpeedX_t);
				m_ObjSpeedY.push_back(m_ObjSpeedY_t);
				m_PostSpeedX.push_back(m_PostSpeedX_t);
				m_PostSpeedY.push_back(m_PostSpeedY_t);
				m_PointTime.push_back(m_PointTime_t);
				m_bHit.push_back(m_bHit_t);
				m_ObjSpeed.push_back(pow(pow((double)m_ObjSpeedX[i], 2.0) + pow((double)m_ObjSpeedY[i], 2.0), 0.5));
				m_PostSpeed.push_back(pow(pow((double)m_PostSpeedX[i], 2.0) + pow((double)m_PostSpeedY[i], 2.0), 0.5));
	//			if(fp == fp1)
	//			{
	//				MessageBox("文件格式有误！");
	//				return FALSE;
	//			}
				if(m_TrialType==0)
				{ 
					m_ExperStart1 = i;
				}
				if(m_TrialType==1&&m_PointNum==1)
				{ 
					m_StartPoint[j] = i;
					j++;
				} 
				if(m_TrialType==1)
				{
					m_ChartTime.push_back((float)(m_PointTime[i] - m_PointTime[m_StartPoint[j-1]])/1000.0);
				}
				if (!bBatch)
				{
					if(m_TrialType==0||m_TrialType==1)
					{
						m_pWSDlg->m_ListDlg.AddT6TraceItem(i);
					}
				}
				i++;
			}
			fclose(fp);		
			m_ExperStart1 = m_ExperStart1+1;
			m_PointNum = i;
			if(m_TrialType!=0&&m_TrialType!=1)
			{
				return FALSE;
			}
			if(m_ExperStart1>m_PointNum)
			//if(m_ExperStart1>=m_PointNum-1)
			{
				return FALSE;
			}
			m_StartPoint[1] = m_PointNum;	
			m_TrialNum = 1;
		}
		catch(...)
		{
			AfxMessageBox("数据文件格式错误！");
			return FALSE;
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CTaskControlDoc::ReadT6Judge()
{
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
	m_TrialType = -1;
	m_ExperStart2 = -1;
	bExitItem2 = FALSE;
	FILE *fp;
	FILE *fp1;
	CString str;
	char tmp[1000];
	int i;

    CString m_SaveName;
	char filestr[50];
	int len;
	_mkdir("Result");
	_mkdir("Result\\Task6");
	m_SaveName = "Result\\Task6\\task6_judge_result.txt";
	sprintf_s(filestr,50,"%s\t%s",m_TestTime,m_PartInfo.m_TesterNo);
	len = strlen(filestr);
	fopen_s(&fp, m_SaveName,"r");
	{
		if(fp!=NULL)
		{
			fgets(tmp,1000,fp);	
			while(!feof(fp))
			{
				fgets(tmp,1000,fp);	
				if(strncmp(tmp,filestr,len) == 0)
				{
					if(bBatch)
					{
						fclose(fp);
						return FALSE;
					}
					else
					{
	                    bExitItem2 = TRUE;
					}
				}
			}
			bExist2 = TRUE;
			fclose(fp);
		}
		else
		{
			bExist2 = FALSE;
		}
	}

	CResultDlg *m_pWSDlg;
	if (!bBatch)
	{
	    m_pWSDlg = (CResultDlg *)pMain->m_pWSDlg;
	}

    fopen_s(&fp, m_FileName2,"rt");
	i = 0;
	if(fp!=NULL)
	{
		m_MemNum = 100;
		m_CubeNum = (int*)malloc(m_MemNum*sizeof(int));
//		pDoc->m_LMemName = (char*)malloc(m_MemNum*sizeof(char));
//		pDoc->m_RMemName = (char*)malloc(m_MemNum*sizeof(char));
		m_LMemAngle = (short*)malloc(m_MemNum*sizeof(short));
		m_RMemAngle = (short*)malloc(m_MemNum*sizeof(short));
		m_MemAngleDiff = (short*)malloc(m_MemNum*sizeof(short));
		m_Same = (short*)malloc(m_MemNum*sizeof(short));
		m_SignStartTime = (unsigned long*)malloc(m_MemNum*sizeof(unsigned long));
		m_SignSureTime = (unsigned long*)malloc(m_MemNum*sizeof(unsigned long));
		m_SureButtonNo = (short*)malloc(m_MemNum*sizeof(short));
		m_SignRT = (unsigned long*)malloc(m_MemNum*sizeof(unsigned long));
		m_SignAcc = (int*)malloc(m_MemNum*sizeof(int));

//		fprintf(fp,"ID\tName\tSex\tSession\t"
//			"DistanceError\tPracMode\tExperMode\tMainTask\tSubTask\t"
//			"Background\tInitSpeed\tCubeNum1\tCubeNum2\tCubeNum3\tCubeNum4\tPrototype\tRefAxis\tMemTaskMode\tPracTime\tExperTime\tPracTimes\tExperTimes\t"
//			"Pra_Test\tGroupNo\tMemNo\tMemCubeNum\tLMemName\tRMemName\tLMemAngle\tRMemAngle\tMemAngleDiff\tSame\tStartTime\tSureTime\tSureButton\tMem_RT\tMem_Acc\n");

        fgets(tmp,1000,fp);
		try{
			while(!feof(fp))
			{
				fp1 = fp;
				if(i>=m_MemNum)
				{
					m_MemNum+=100;
					m_CubeNum = (int*)realloc(m_CubeNum,m_MemNum*sizeof(int));
	//				pDoc->m_LMemName[30] = (char*)realloc(pDoc->m_LMemName,m_MemNum*sizeof(char));
	//				pDoc->m_RMemName[30] = (char*)realloc(pDoc->m_RMemName,m_MemNum*sizeof(char));
					m_LMemAngle = (short*)realloc(m_LMemAngle,m_MemNum*sizeof(short));
					m_RMemAngle = (short*)realloc(m_RMemAngle,m_MemNum*sizeof(short));
					m_MemAngleDiff = (short*)realloc(m_MemAngleDiff,m_MemNum*sizeof(short));
					m_Same = (short*)realloc(m_Same,m_MemNum*sizeof(short));
					m_SignStartTime = (unsigned long*)realloc(m_SignStartTime,m_MemNum*sizeof(unsigned long));
					m_SignSureTime = (unsigned long*)realloc(m_SignSureTime,m_MemNum*sizeof(unsigned long));
					m_SureButtonNo = (short*)realloc(m_SureButtonNo,m_MemNum*sizeof(short));
					m_SignRT = (unsigned long*)realloc(m_SignRT,m_MemNum*sizeof(unsigned long));
					m_SignAcc = (int*)realloc(m_SignAcc,m_MemNum*sizeof(int));
				}

				fscanf_s(fp,"%s\t%s\t%s\t%d\t"
					"%f\t%d\t%d\t%d\t%d\t"
					"%d\t%f\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t"
					"%d\t%d\t%d\t%d\t%s\t%s\t%d\t%d\t%d\t%d\t%u\t%u\t%d\t%u\t%d\n",
					m_PartInfo.m_TesterNo,20, m_PartInfo.m_TesterName,20, m_PartInfo.m_TesterSex,10, &m_PartInfo.m_Session, 
					&m_HardSetting.m_DistanceError, &m_ReadSetting6[0].m_PracMode, &m_ReadSetting6[0].m_ExperMode, &m_ReadSetting6[0].m_MainTask, &m_ReadSetting6[0].m_SubTask,
					&m_ReadSetting6[0].m_Background, &m_ReadSetting6[0].m_InitSpeed, &m_ReadSetting6[0].m_CubeNum1, &m_ReadSetting6[0].m_CubeNum2, &m_ReadSetting6[0].m_CubeNum3, &m_ReadSetting6[0].m_CubeNum4, &m_ReadSetting6[0].m_Prototype, &m_ReadSetting6[0].m_RefAxis, &m_ReadSetting6[0].m_MemTaskMode, &m_ReadSetting6[0].m_PracTime, &m_ReadSetting6[0].m_ExperTime, &m_ReadSetting6[0].m_PracTimes, &m_ReadSetting6[0].m_ExperTimes, 
					&m_TrialType, &m_SignGroupNo, &m_MemNo, &m_CubeNum[i], m_LMemName,30, m_RMemName,30, &m_LMemAngle[i], &m_RMemAngle[i], &m_MemAngleDiff[i], &m_Same[i], &m_SignStartTime[i], &m_SignSureTime[i], &m_SureButtonNo[i], &m_SignRT[i], &m_SignAcc[i]);		
				if(m_TrialType==0)
				{ 
					m_ExperStart2 = i;
				}
	//			if(fp == fp1)
	//			{
	//				MessageBox("文件格式有误！");
	//				return FALSE;
	//			}
				if (!bBatch)
				{
					if(m_TrialType==0||m_TrialType==1)
					{
			    		m_pWSDlg->m_ListDlg.AddT6JudgeItem(i);
					}
				}
    			i++;
			}
			m_ExperStart2 = m_ExperStart2+1;
			m_RecordNo = i;
			fclose(fp);	
			if (m_ExperStart2 > m_RecordNo)
			//if (m_ExperStart2 >= m_RecordNo - 1)
			{
				return FALSE;
			}
			if(m_TrialType!=0&&m_TrialType!=1)
			{
				return FALSE;
			}
		}
		catch(...)
		{
			AfxMessageBox("数据文件格式错误！");
			return FALSE;
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CTaskControlDoc::ReadT6Memory()
{
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
	m_TrialType = -1;
    m_ExperStart2 = -1;
	bExitItem2 = FALSE;
	FILE *fp;
	FILE *fp1;
	CString str;
	char tmp[1000];
	int i;

    CString m_SaveName;
	char filestr[50];
	int len;
	_mkdir("Result");
	_mkdir("Result\\Task6");
	m_SaveName = "Result\\Task6\\task6_memory_result.txt";
	sprintf_s(filestr,50,"%s\t%s",m_TestTime,m_PartInfo.m_TesterNo);
	len = strlen(filestr);
	fopen_s(&fp, m_SaveName,"r");
	{
		if(fp!=NULL)
		{
			fgets(tmp,1000,fp);	
			while(!feof(fp))
			{
				fgets(tmp,1000,fp);	
				if(strncmp(tmp,filestr,len) == 0)
				{
					if(bBatch)
					{
						fclose(fp);
						return FALSE;
					}
					else
					{
	                    bExitItem2 = TRUE;
					}
				}
			}
			bExist2 = TRUE;
			fclose(fp);
		}
		else
		{
			bExist2 = FALSE;
		}
	}

	CResultDlg *m_pWSDlg;
	if (!bBatch)
	{
    	m_pWSDlg = (CResultDlg *)pMain->m_pWSDlg;
	}

    fopen_s(&fp, m_FileName2,"rt");
	i = 0;
	if(fp!=NULL)
	{
		m_MemNum = 100;
		m_CubeNum = (int*)malloc(m_MemNum*sizeof(int));
//		pDoc->m_LMemName[30] = (char*)malloc(m_MemNum*sizeof(char));
//		pDoc->m_RMemName[30] = (char*)malloc(m_MemNum*sizeof(char));
		m_LMemAngle = (short*)malloc(m_MemNum*sizeof(short));
		m_RMemAngle = (short*)malloc(m_MemNum*sizeof(short));
		m_MemAngleDiff = (short*)malloc(m_MemNum*sizeof(short));
		m_Same = (short*)malloc(m_MemNum*sizeof(short));
		m_SignStartTime = (unsigned long*)malloc(m_MemNum*sizeof(unsigned long));
		m_SignSureTime = (unsigned long*)malloc(m_MemNum*sizeof(unsigned long));
		m_SureButtonNo = (short*)malloc(m_MemNum*sizeof(short));
		m_SignRT = (unsigned long*)malloc(m_MemNum*sizeof(unsigned long));
		m_SignAcc = (int*)malloc(m_MemNum*sizeof(int));

//		fprintf(fp,"ID\tName\tSex\tSession\t"
//			"DistanceError\tPracMode\tExperMode\tMainTask\tSubTask\t"
//			"Background\tInitSpeed\tCubeNum1\tCubeNum2\tCubeNum3\tCubeNum4\tPrototype\tRefAxis\tMemTaskMode\tPracTime\tExperTime\tPracTimes\tExperTimes\t"
//			"Pra_Test\tGroupNo\tMemNo\tMemCubeNum\tLMemName\tRMemName\tLMemAngle\tRMemAngle\tMemAngleDiff\tSame\tStartTime\tSureTime\tSureButton\tMem_RT\tMem_Acc\n");
        fgets(tmp,1000,fp);

		try
		{
			while(!feof(fp))
			{
				fp1 = fp;
				if(i>=m_MemNum)
				{
					m_MemNum+=100;
					m_CubeNum = (int*)realloc(m_CubeNum,m_MemNum*sizeof(int));
	//				pDoc->m_LMemName[30] = (char*)realloc(pDoc->m_LMemName,m_MemNum*sizeof(char));
	//				pDoc->m_RMemName[30] = (char*)realloc(pDoc->m_RMemName,m_MemNum*sizeof(char));
					m_LMemAngle = (short*)realloc(m_LMemAngle,m_MemNum*sizeof(short));
					m_RMemAngle = (short*)realloc(m_RMemAngle,m_MemNum*sizeof(short));
					m_MemAngleDiff = (short*)realloc(m_MemAngleDiff,m_MemNum*sizeof(short));
					m_Same = (short*)realloc(m_Same,m_MemNum*sizeof(short));
					m_SignStartTime = (unsigned long*)realloc(m_SignStartTime,m_MemNum*sizeof(unsigned long));
					m_SignSureTime = (unsigned long*)realloc(m_SignSureTime,m_MemNum*sizeof(unsigned long));
					m_SureButtonNo = (short*)realloc(m_SureButtonNo,m_MemNum*sizeof(short));
					m_SignRT = (unsigned long*)realloc(m_SignRT,m_MemNum*sizeof(unsigned long));
					m_SignAcc = (int*)realloc(m_SignAcc,m_MemNum*sizeof(int));
				}

				fscanf_s(fp,"%s\t%s\t%s\t%d\t"
					"%f\t%d\t%d\t%d\t%d\t"
					"%d\t%f\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t"
					"%d\t%d\t%d\t%d\t%s\t%s\t%d\t%d\t%d\t%d\t%u\t%u\t%d\t%u\t%d\n",
					m_PartInfo.m_TesterNo,20, m_PartInfo.m_TesterName,20, m_PartInfo.m_TesterSex,10, &m_PartInfo.m_Session, 
					&m_HardSetting.m_DistanceError, &m_ReadSetting6[0].m_PracMode, &m_ReadSetting6[0].m_ExperMode, &m_ReadSetting6[0].m_MainTask, &m_ReadSetting6[0].m_SubTask,
					&m_ReadSetting6[0].m_Background, &m_ReadSetting6[0].m_InitSpeed, &m_ReadSetting6[0].m_CubeNum1, &m_ReadSetting6[0].m_CubeNum2, &m_ReadSetting6[0].m_CubeNum3, &m_ReadSetting6[0].m_CubeNum4, &m_ReadSetting6[0].m_Prototype, &m_ReadSetting6[0].m_RefAxis, &m_ReadSetting6[0].m_MemTaskMode, &m_ReadSetting6[0].m_PracTime, &m_ReadSetting6[0].m_ExperTime, &m_ReadSetting6[0].m_PracTimes, &m_ReadSetting6[0].m_ExperTimes, 
					&m_TrialType, &m_SignGroupNo, &m_MemNo, &m_CubeNum[i], m_LMemName,30, m_RMemName,30, &m_LMemAngle[i], &m_RMemAngle[i], &m_MemAngleDiff[i], &m_Same[i], &m_SignStartTime[i], &m_SignSureTime[i], &m_SureButtonNo[i], &m_SignRT[i], &m_SignAcc[i]);		
				if(m_TrialType==0)
				{ 
					m_ExperStart2 = i;
				}
	//			if(fp == fp1)
	//			{
	//				MessageBox("文件格式有误！");
	//				return FALSE;
	//			}
				
				if (!bBatch)
				{
					if(m_TrialType==0||m_TrialType==1)
					{
						m_pWSDlg->m_ListDlg.AddT6MemoryItem(i);
					}
				}
				i++;
			}
			m_ExperStart2 = m_ExperStart2+1;
			m_RecordNo = i;
			fclose(fp);
			//if(m_ExperStart2>=m_RecordNo-1)
			if(m_ExperStart2>m_RecordNo)
			{
				return FALSE;
			}
			if(m_TrialType!=0&&m_TrialType!=1)
			{
				return FALSE;
			}
		}
		catch(...)
		{
			AfxMessageBox("数据文件格式错误！");
			return FALSE;
		}
		return TRUE;
	}
	return FALSE;
}

void CTaskControlDoc::MemClear()
{
	/*if(m_ObjPoint!=NULL)
	{
		delete []m_ObjPoint;
		m_ObjPoint = NULL;
	}
	if(m_PostPoint!=NULL)
	{
		delete []m_PostPoint;
		m_PostPoint = NULL;
	}*/
	/*if(m_ObjRotate!=NULL)
	{
		delete []m_ObjRotate;
		m_ObjRotate = NULL;
	}
	if(m_PostRotate!=NULL)
	{
		delete []m_PostRotate;
		m_PostRotate = NULL;
	}
	if(m_Distance!=NULL)
	{
		delete []m_Distance;
		m_Distance = NULL;
	}
	if(m_RotateError!=NULL)
	{
		delete []m_RotateError;
		m_RotateError = NULL;
	}
	if(m_ObjSpeedX!=NULL)
	{
		delete []m_ObjSpeedX;
		m_ObjSpeedX = NULL;
	}
	if(m_ObjSpeedY!=NULL)
	{
		delete []m_ObjSpeedY;
		m_ObjSpeedY = NULL;
	}
	if(m_ObjSpeed!=NULL)
	{
		delete []m_ObjSpeed;
		m_ObjSpeed = NULL;
	}
	if(m_PostSpeedX!=NULL)
	{
		delete []m_PostSpeedX;
		m_PostSpeedX = NULL;
	}
	if(m_PostSpeedY!=NULL)
	{
		delete []m_PostSpeedY;
		m_PostSpeedY = NULL;
	}
	if(m_PostSpeed!=NULL)
	{
		delete []m_PostSpeed;
		m_PostSpeed = NULL;
	}
	if(m_ObjRotateSpeed!=NULL)
	{
		delete []m_ObjRotateSpeed;
		m_ObjRotateSpeed = NULL;
	}

	if(m_PostRotateSpeed!=NULL)
	{
		delete []m_PostRotateSpeed;
		m_PostRotateSpeed = NULL;
	}
	if(m_PointTime!=NULL)
	{
		delete []m_PointTime;
		m_PointTime = NULL;
	}
	if(m_bHit!=NULL)
	{
		delete []m_bHit;
		m_bHit = NULL;
	}
	if(m_ChartTime!=NULL)
	{
		delete []m_ChartTime;
		m_ChartTime = NULL;
	}*/

	/*if(m_HoldStartTime!=NULL)
	{
		delete []m_HoldStartTime;
		m_HoldStartTime = NULL;
	}
	if(m_HoldSureTime!=NULL)
	{
		delete []m_HoldSureTime;
		m_HoldSureTime = NULL;
	}*/
	if(m_HoldTime!=NULL)
	{
		delete []m_HoldTime;
		m_HoldTime = NULL;
	}
	if(m_TestRT!=NULL)
	{
		delete []m_TestRT;
		m_TestRT = NULL;
	}
	if(m_HoldError!=NULL)
	{
		delete []m_HoldError;
		m_HoldError = NULL;
	}
	if(m_ErrorRatio!=NULL)
	{
		delete []m_ErrorRatio;
		m_ErrorRatio = NULL;
	}

	if(m_EventType!=NULL)
	{
		delete []m_EventType;
		m_EventType = NULL;
	}
	if(m_EventStartTime!=NULL)
	{
		delete []m_EventStartTime;
		m_EventStartTime = NULL;
	}
	if(m_EventSureTime!=NULL)
	{
		delete []m_EventSureTime;
		m_EventSureTime = NULL;
	}
	if(m_SureButtonNo!=NULL)
	{
		delete []m_SureButtonNo;
		m_SureButtonNo = NULL;
	}
	if(m_EventRT!=NULL)
	{
		delete []m_EventRT;
		m_EventRT = NULL;
	}
	if(m_bEventAcc!=NULL)
	{
		delete []m_bEventAcc;
		m_bEventAcc = NULL;
	}

	if(m_CodeType!=NULL)
	{
		delete []m_CodeType;
		m_CodeType = NULL;
	}
	if(m_CodeStartTime!=NULL)
	{
		delete []m_CodeStartTime;
		m_CodeStartTime = NULL;
	}
	if(m_CodeSureTime!=NULL)
	{
		delete []m_CodeSureTime;
		m_CodeSureTime = NULL;
	}
	if(m_CodeButtonNo!=NULL)
	{
		delete []m_CodeButtonNo;
		m_CodeButtonNo = NULL;
	}
	if(m_CodeRT!=NULL)
	{
		delete []m_CodeRT;
		m_CodeRT = NULL;
	}
	if(m_bCodeAcc!=NULL)
	{
		delete []m_bCodeAcc;
		m_bCodeAcc = NULL;
	}

	if(m_TouchNoOrder!=NULL)
	{
		delete []m_TouchNoOrder;
		m_TouchNoOrder = NULL;
	}
	if(m_TouchStartTime!=NULL)
	{
		delete []m_TouchStartTime;
		m_TouchStartTime = NULL;
	}
	if(m_TouchSureTime!=NULL)
	{
		delete []m_TouchSureTime;
		m_TouchSureTime = NULL;
	}
	if(m_TouchRT!=NULL)
	{
		delete []m_TouchRT;
		m_TouchRT = NULL;
	}
	if(m_TouchAcc!=NULL)
	{
		delete []m_TouchAcc;
		m_TouchAcc = NULL;
	}
	if(m_TouchDistance!=NULL)
	{
		delete []m_TouchDistance;
		m_TouchDistance = NULL;
	}
	if(m_sizediff!=NULL)
	{
		delete []m_sizediff;
		m_sizediff = NULL;
	}

	if(m_SignType!=NULL)
	{
		delete []m_SignType;
		m_SignType = NULL;
	}
	if(m_SignStartTime!=NULL)
	{
		delete []m_SignStartTime;
		m_SignStartTime = NULL;
	}
	if(m_SignSureTime!=NULL)
	{
		delete []m_SignSureTime;
		m_SignSureTime = NULL;
	}
	if(m_SignRT!=NULL)
	{
		delete []m_SignRT;
		m_SignRT = NULL;
	}
	if(m_SignAcc!=NULL)
	{
		delete []m_SignAcc;
		m_SignAcc = NULL;
	}

	if(m_CubeNum!=NULL)
	{
		delete []m_CubeNum;
		m_CubeNum = NULL;
	}
	if(m_Same!=NULL)
	{
		delete []m_Same;
		m_Same = NULL;
	}
	if(m_LMemAngle!=NULL)
	{
		delete []m_LMemAngle;
		m_LMemAngle = NULL;
	}
	if(m_RMemAngle!=NULL)
	{
		delete []m_RMemAngle;
		m_RMemAngle = NULL;
	}
	if(m_MemAngleDiff!=NULL)
	{
		delete []m_MemAngleDiff;
		m_MemAngleDiff = NULL;
	}

	if(m_SignMemNum!=NULL)
	{
		delete []m_SignMemNum;
		m_SignMemNum = NULL;
	}
}

void CTaskControlDoc::initAnalyseResult()
{
	//初始化分析结果
	m_DistanceTotal = 0;
	m_RotateErrorTotal = 0;
	m_DistanceAve = 0;
	m_RotateErrorAve = 0;
	m_DistanceSqt = 0;
	m_RotateErrorSqt = 0;
	m_HitCount = 0;
	m_HitTimeTotal = 0;
	m_HitTimeRate = 0;
	m_TrueCount = 0;
	m_MissingCount = 0;
	m_CRCount = 0;
	m_FalseCount = 0;
	m_CodeRTTotal = 0;
	m_RTTotal = 0;
	m_CodeRTAvg = 0;
	m_CodeRTSqr = 0;
	m_RTAvg = 0;
	m_RTSqr = 0;
	m_Acce = 0;
	m_TargetCount = 0;
	m_NoTargetCount = 0;
	m_HoldTimeErrAve.clear();
	settingOrderHoldTimeErrRateAve.clear();
	//t7res = {0, 0., 0., 0};
}


void CTaskControlDoc::getTask2HoldError()
{
	//m_HoldError
}

// 数据分析函数
// 前人的所有的task的分析都在这里TT
void CTaskControlDoc::DataAnalysis()
{
	int i,j;
	FILE *fp;

    CString m_SaveName;
	int m_PointTotal = 0;
	UINT m_TimeTotal = 0;
    int TouchNo;

	//初始化分析结果
	initAnalyseResult();


	CString cs;
	CString str;

	switch (m_TaskNo)
	{
	case 1:
		if(m_bOpenFile1)
		{
			m_TrialNum = m_ReadSetting1[0].m_ExperTimes;
			for(j=0;j<m_TrialNum;j++)
			{
				m_ValidStart[j] = m_StartPoint[j] + 125; //从第125个开始计算
				for(i=m_ValidStart[j];i<m_StartPoint[j+1];i++)
				{
					m_DistanceTotal += m_Distance[i];
					m_RotateErrorTotal += fabs(m_RotateError[i]);
					if(m_bHit[i])
					{
						m_HitCount++;
					}
					m_PointTotal++;
				}
				m_TimeTotal+=(m_PointTime[m_StartPoint[j+1]-1]-m_PointTime[m_ValidStart[j]]);
			}
			m_DistanceAve = m_DistanceTotal/(float)m_PointTotal;
			m_RotateErrorAve = m_RotateErrorTotal/(float)m_PointTotal;
			m_HitTimeTotal = m_HitCount*40;	//采样时间是40ms
			m_HitTimeRate = (float)m_HitTimeTotal/(float)m_TimeTotal;
			m_DistanceTotal = 0;
			m_RotateErrorTotal = 0;
			for(j=0;j<m_TrialNum;j++)
			{
				for(i=m_ValidStart[j];i<m_StartPoint[j+1];i++)
				{
					m_DistanceTotal += pow((m_Distance[i]-m_DistanceAve),2);
				    m_RotateErrorTotal += pow((fabs(m_RotateError[i])-m_RotateErrorAve),2);
				}
			}
			m_DistanceSqt = pow((double)m_DistanceTotal/(double)(m_PointTotal-1),0.5);
			m_RotateErrorSqt = pow((double)m_RotateErrorTotal/(double)(m_PointTotal-1),0.5);
	//		pos = pDoc->m_FileName.ReverseFind('\\');
	//	    pos1 = pDoc->m_FileName.ReverseFind('-');
			if(!bExitItem1)
			{
				_mkdir("Result");
				_mkdir("Result\\Task1");
				m_SaveName = "Result\\Task1\\task1_tracking_result.txt";
				fopen_s(&fp, m_SaveName,"at");
				if(fp!=NULL)
				{
					if(!bExist1)
					{
						fprintf(fp,"FileName\tID\tName\tSex\tSession\t"
							"DistanceError\tAngleError\tPracMode\tExperMode\t"
							"Background\tTrack\tDirection\tMoveMode\tSpeedMode\tPause\tPauseNum\tInitSpeed\t"
							"SpeedMin\tSpeedMax\tAccelerationMin\tAccelerationMax\tAngleSpeedMin\tAngleSpeedMax\tRotateAngleMin\tRotateAngleMax\tPracTime\tExperTime\tPracTimes\tExperTimes\t"
							"DistanceAve\tDistanceSqt\tRotateErrorAve\tRotateErrorSqt\tHitTimeTotal\tHitTimeRate\n");
					}
    				fprintf(fp,"%s\t%s\t%s\t%s\t%d\t"
						"%.2f\t%.2f\t%d\t%d\t"
						"%d\t%d\t%d\t%d\t%d\t"
						"%d\t%d\t%.2f\t"
						"%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%d\t%d\t%d\t%d\t"
						"%.2f\t%.2f\t%.2f\t%.2f\t%d\t%.2f\n",
						m_DataFileName, m_PartInfo.m_TesterNo, m_PartInfo.m_TesterName, m_PartInfo.m_TesterSex, m_PartInfo.m_Session, 
						m_HardSetting.m_DistanceError, m_HardSetting.m_AngleError, m_ReadSetting1[0].m_PracMode, m_ReadSetting1[0].m_ExperMode,
						m_ReadSetting1[0].m_Background, m_ReadSetting1[0].m_Track, m_ReadSetting1[0].m_Direction, m_ReadSetting1[0].m_MoveMode, m_ReadSetting1[0].m_SpeedMode,
						m_ReadSetting1[0].m_Pause, m_ReadSetting1[0].m_PauseNum, m_ReadSetting1[0].m_InitSpeed,
						m_ReadSetting1[0].m_SpeedMin, m_ReadSetting1[0].m_SpeedMax, m_ReadSetting1[0].m_AccelerationMin, m_ReadSetting1[0].m_AccelerationMax, m_ReadSetting1[0].m_AngleSpeedMin, m_ReadSetting1[0].m_AngleSpeedMax, m_ReadSetting1[0].m_RotateAngleMin, m_ReadSetting1[0].m_RotateAngleMax, m_ReadSetting1[0].m_PracTime, m_ReadSetting1[0].m_ExperTime, m_ReadSetting1[0].m_PracTimes, m_ReadSetting1[0].m_ExperTimes,
						m_DistanceAve, m_DistanceSqt, m_RotateErrorAve, m_RotateErrorSqt, m_HitTimeTotal, m_HitTimeRate);
					fclose(fp);
				}
			}
		}
		break;
	// 任务二
	// 1: tracking; 2: holding
	case 2:
		if(m_bOpenFile1)
		{
			m_TrialNum = 1;//为什么是1，先保留着吧
            for(j=0;j<m_TrialNum;j++)
			{
				m_ValidStart[j] = m_StartPoint[j] + 125;
				for(i=m_ValidStart[j];i<m_StartPoint[j+1];i++)
				{
					m_DistanceTotal += m_Distance[i];
					if(m_bHit[i])
					{
						m_HitCount++;
					}
					m_PointTotal++;
				}
				m_TimeTotal+=(m_PointTime[m_StartPoint[j+1]-1]-m_PointTime[m_ValidStart[j]]);
			}
			m_DistanceAve = m_DistanceTotal/(float)m_PointTotal;//平均误差距离
			m_HitTimeTotal = m_HitCount*40;
			m_HitTimeRate = (float)m_HitTimeTotal/(float)m_TimeTotal;
			m_DistanceTotal = 0;
			for(j=0;j<m_TrialNum;j++)
			{
				for(i=m_ValidStart[j];i<m_StartPoint[j+1];i++)
				{
					m_DistanceTotal += pow((m_Distance[i]-m_DistanceAve),2);
				}
			}
			m_DistanceSqt = pow((double)m_DistanceTotal/(double)(m_PointTotal-1),0.5);//误差距离标准差
		}



		if(m_bOpenFile2)
		{
			/*for(i=0;i<12;i++)
			{
				m_HoldErrorTotal[i] = 0;
				m_HoldCountTotal[i] = 0;
			}*/
			//for(i=m_ExperStart2;i<m_HoldNo;i++)
			//{
				/*for(j=0;j<12;j++)
				{
					if((float)m_HoldTime[i]/1000.0==m_ReadSetting2[0].m_HoldTime[j])
					{
						m_HoldErrorTotal[j] += m_HoldError[i];
						m_HoldCountTotal[j]++;
						continue;
					}
				}*/
			//}
	//		pos = pDoc->m_FileName.ReverseFind('\\');
	//	    pos1 = pDoc->m_FileName.ReverseFind('-');

			// ------------------------------------------------------
			// pDoc->m_HoldTime[i]: is the real hold time order
			// pDoc->m_ReadSetting2[0].m_HoldTime[i] is the setting hold time 
			// which should be the expected order in Analysis dialog 
			// ------------------------------------------------------

			vector<int> uniqueHoldTimeVec;

			for (int i = 0; i < m_HoldNo; i++)//放入误差率绝对值
				m_HoldTimeErrAve.push_back(fabs(m_ErrorRatio[i]));
			for (int i = 0; i < m_HoldNo; i++)//查找不同的holdtime
				{
					if (uniqueHoldTimeVec.empty()) uniqueHoldTimeVec.push_back(m_HoldTime[i]);
					else if (find(uniqueHoldTimeVec.begin(), uniqueHoldTimeVec.end(), m_HoldTime[i]) == uniqueHoldTimeVec.end())
						uniqueHoldTimeVec.push_back(m_HoldTime[i]);
				}
			for (int i = 0; i < uniqueHoldTimeVec.size(); i++)
			{
				int count = 0;
				double err = 0.;
				vector<int> ind;
				for (int j = 0; j < m_HoldNo; j++)//查找相同的holdtime，用他们的err的绝对值的均值代替
				if (m_ErrorRatio[j] != -1)
					{
						if (uniqueHoldTimeVec[i] == m_HoldTime[j])
						{
							count++;
							err += fabs(m_HoldTimeErrAve[j]);
							ind.push_back(j);
						}
					}
				err /= count;
				for (int j = 0; j < ind.size(); j++) // 写到相同的holdtime的holdTimeError中
				{
					m_HoldTimeErrAve[ind[j]] = err;
				}
			}
			// Sort in setting hold time order
			for (int i = 0; i < m_ReadSetting2[0].m_HoldTimeNum; i++) {
				settingOrderHoldTimeErrRateAve.push_back(-1);
				for (int j = 0; j < m_HoldNo; j++) {
					if ((m_ReadSetting2[0].m_HoldTime[i]*1000 == m_HoldTime[j])&&(m_ErrorRatio[j] != -1)) {
						settingOrderHoldTimeErrRateAve[i] = m_HoldTimeErrAve[j];
						break;
					}
				}
			}
		}
		if(m_bOpenFile1)
		{
			if(!bExitItem1)
			{
				_mkdir("Result");
				_mkdir("Result\\Task2");
				m_SaveName = "Result\\Task2\\task2_tracking_result.txt";
				fopen_s(&fp, m_SaveName,"at");
				if(fp!=NULL)
				{
					if(!bExist1)
					{
						fprintf_s(fp,"FileName\tID\tName\tSex\tSession\t"
							"DistanceError\tPracMode\tExperMode\tMainTask\tSubTask\t"
							"Background\tDirection\tInitSpeed\t"
							"HoldTimeNum\tHoldTime1\tHoldTime2\tHoldTime3\tHoldTime4\tHoldTime5\tHoldTime6\tHoldTime7\tHoldTime8\tHoldTime9\tHoldTime10\tHoldTime11\tHoldTime12\tPracTime\tExperTime\tPracTimes\tExperTimes\t"
							"DistanceAve\tDistanceSqt\tHitTimeTotal\tHitTimeRate\n");
					}
					fprintf(fp,"%s\t%s\t%s\t%s\t%d\t"
						"%.2f\t%d\t%d\t%d\t%d\t"
						"%d\t%d\t%.2f\t"
						"%d\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%d\t%d\t%d\t%d\t"
						"%.2f\t%.2f\t%d\t%.2f\n",
						m_DataFileName, m_PartInfo.m_TesterNo, m_PartInfo.m_TesterName, m_PartInfo.m_TesterSex, m_PartInfo.m_Session, 
						m_HardSetting.m_DistanceError, m_ReadSetting2[0].m_PracMode, m_ReadSetting2[0].m_ExperMode, m_ReadSetting2[0].m_MainTask, m_ReadSetting2[0].m_SubTask,
						m_ReadSetting2[0].m_Background, m_ReadSetting2[0].m_Direction, m_ReadSetting2[0].m_InitSpeed, 
						m_ReadSetting2[0].m_HoldTimeNum, m_ReadSetting2[0].m_HoldTime[0], m_ReadSetting2[0].m_HoldTime[1], m_ReadSetting2[0].m_HoldTime[2], m_ReadSetting2[0].m_HoldTime[3], m_ReadSetting2[0].m_HoldTime[4], m_ReadSetting2[0].m_HoldTime[5], m_ReadSetting2[0].m_HoldTime[6], m_ReadSetting2[0].m_HoldTime[7], m_ReadSetting2[0].m_HoldTime[8], m_ReadSetting2[0].m_HoldTime[9], m_ReadSetting2[0].m_HoldTime[10], m_ReadSetting2[0].m_HoldTime[11], m_ReadSetting2[0].m_PracTime, m_ReadSetting2[0].m_ExperTime, m_ReadSetting2[0].m_PracTimes, m_ReadSetting2[0].m_ExperTimes,
						m_DistanceAve, m_DistanceSqt, m_HitTimeTotal, m_HitTimeRate);
					fclose(fp);
				}
			}
		}

		if(m_bOpenFile2)
		{
			if(!bExitItem2)
			{
				_mkdir("Result");
				_mkdir("Result\\Task2");
				m_SaveName = "Result\\Task2\\task2_hold_result.txt";
				fopen_s(&fp, m_SaveName,"at");
				if(fp!=NULL)
				{
					if(!bExist2)
					{
						fprintf_s(fp,"FileName\tID\tName\tSex\tSession\t"
							"DistanceError\tPracMode\tExperMode\tMainTask\tSubTask\t"
							"Background\tDirection\tInitSpeed\t"
							"HoldTimeNum\tHoldTime1\tHoldTime2\tHoldTime3\tHoldTime4\tHoldTime5\tHoldTime6\tHoldTime7\tHoldTime8\tHoldTime9\tHoldTime10\tHoldTime11\tHoldTime12\tPracTime\tExperTime\tPracTimes\tExperTimes\t"
							"HoldTimeRate1\tHoldTimeRate2\tHoldTimeRate3\tHoldTimeRate4\tHoldTimeRate5\tHoldTimeRate6\tHoldTimeRate7\tHoldTimeRate8\tHoldTimeRate9\tHoldTimeRate10\tHoldTimeRate11\tHoldTimeRate12\n");
					}
					fprintf(fp,"%s\t%s\t%s\t%s\t%d\t"
						"%.2f\t%d\t%d\t%d\t%d\t"
						"%d\t%d\t%.2f\t"
						"%d\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%d\t%d\t%d\t%d\t",
						m_DataFileName, m_PartInfo.m_TesterNo, m_PartInfo.m_TesterName, m_PartInfo.m_TesterSex, m_PartInfo.m_Session, 
						m_HardSetting.m_DistanceError, m_ReadSetting2[0].m_PracMode, m_ReadSetting2[0].m_ExperMode, m_ReadSetting2[0].m_MainTask, m_ReadSetting2[0].m_SubTask,
						m_ReadSetting2[0].m_Background, m_ReadSetting2[0].m_Direction, m_ReadSetting2[0].m_InitSpeed, 
						m_ReadSetting2[0].m_HoldTimeNum, m_ReadSetting2[0].m_HoldTime[0], m_ReadSetting2[0].m_HoldTime[1], m_ReadSetting2[0].m_HoldTime[2], m_ReadSetting2[0].m_HoldTime[3], m_ReadSetting2[0].m_HoldTime[4], m_ReadSetting2[0].m_HoldTime[5], m_ReadSetting2[0].m_HoldTime[6], m_ReadSetting2[0].m_HoldTime[7], m_ReadSetting2[0].m_HoldTime[8], m_ReadSetting2[0].m_HoldTime[9], m_ReadSetting2[0].m_HoldTime[10], m_ReadSetting2[0].m_HoldTime[11], m_ReadSetting2[0].m_PracTime, m_ReadSetting2[0].m_ExperTime, m_ReadSetting2[0].m_PracTimes, m_ReadSetting2[0].m_ExperTimes);
					for(i=0;i<m_ReadSetting2[0].m_HoldTimeNum;i++)
					{	
						//fprintf(fp, "%.2f\t", (float)m_HoldErrorTotal[i] / (float)m_HoldCountTotal[i]);//错了
						fprintf(fp,"%.2f\t", settingOrderHoldTimeErrRateAve[i]);
					}
					for(i=m_ReadSetting2[0].m_HoldTimeNum;i<12;i++)
					{
						fprintf(fp,"%s\t","");
					}
					fprintf(fp,"\n");
					fclose(fp);
				}
			}
		}
		break;
	// 任务3
	case 3:
		if (m_bOpenFile1)//trace文件
		{
			if (m_MainTaskMode == 0)//主任务存在；怎么实际意思和这个变量名是相反的？
			{
				m_TrialNum = 1;
				for (j = 0; j < m_TrialNum; j++)
				{
					//i = 0;
					//do
					//{
					//	i++;
					//}while((m_PointTime[i]-m_PointTime[m_StartPoint[j]])<=5000);
					m_ValidStart[j] = m_StartPoint[j] + 125;
					for (i = m_ValidStart[j]; i < m_StartPoint[j + 1]; i++)
					{
						m_DistanceTotal += m_Distance[i];
						if (m_bHit[i])
						{
							m_HitCount++;
						}
						m_PointTotal++;
					}
					m_TimeTotal += (m_PointTime[m_StartPoint[j + 1] - 1] - m_PointTime[m_ValidStart[j]]);
				}
				m_DistanceAve = m_DistanceTotal / (float)m_PointTotal;
				m_HitTimeTotal = m_HitCount * 40;
				m_HitTimeRate = (float)m_HitTimeTotal / (float)m_TimeTotal;
				m_DistanceTotal = 0;
				for (j = 0; j < m_TrialNum; j++)
				{
					for (i = m_ValidStart[j]; i < m_StartPoint[j + 1]; i++)
					{
						m_DistanceTotal += pow((m_Distance[i] - m_DistanceAve), 2);
					}
				}
				m_DistanceSqt = pow((double)m_DistanceTotal / (double)(m_PointTotal - 1), 0.5);
			}
			else//没有主任务--这部分已经被废弃了，被event部分取代
			{
				m_TrueCode = 0;
				m_FalseCode = 0;
				m_CodeRTTotal = 0;
				for (i = m_ExperStart1; i < m_CodeNo; i++)
				{
					if (m_bCodeAcc[i] == 1)
					{
						m_TrueCode++;
						m_CodeRTTotal += m_CodeRT[i];
					}
					else
					{
						m_FalseCode++;
					}
				}
				m_CodeRTAvg = (float)m_CodeRTTotal / (float)(m_TrueCode);
				m_CodeRTTotal = 0;
				for (i = m_ExperStart1; i < m_CodeNo; i++)
				{
					if (m_bCodeAcc[i] > 0)
					{
						m_CodeRTTotal += pow((m_CodeRT[i] - m_CodeRTAvg), 2);
					}
				}
				m_CodeRTSqr = pow((double)m_CodeRTTotal / (double)(m_TrueCode - 1), 0.5);
			}
		}
		if (m_bOpenFile2)//Event
		{
			if (m_ReadSetting3[0].m_EventMode == 0)// eventMode==0 简单模式
			{
				//初始化统计变量
				m_TrueCount = 0;
				m_MissingCount = 0;
				m_CRCount = 0;
				m_FalseCount = 0;
				m_FailCount = 0;
				m_RTTotal = 0; //靶事件反应总时

				for (i =/*m_ExperStart2*/0; i < m_RecordNo; i++)//遍历所有记录
				{
					if (m_EventType[i] == 0 && m_SureButtonNo[i] == 0) //统计击中数
						m_TrueCount++;
					if (m_EventType[i] == 0 && m_SureButtonNo[i] == -1) // 统计漏报数
						m_MissingCount++;
					//if (m_EventType[i] == 1 && m_SureButtonNo[i] == 1) //统计正确拒斥数
					//	m_CRCount++;
					//if (m_EventType[i] == 1 && m_SureButtonNo[i] == 0) //统计虚报数
					//	m_FalseCount++;
					if (m_EventType[i] == 2) //统计未触发事件时错误按键数
						m_FailCount++;
					if (m_EventType[i] == 0	&& m_SureButtonNo[i] ==0 ) //统计靶事件反应时
						m_RTTotal += m_EventRT[i];
				}
				//---old code---//
				/*for(i=m_ExperStart2;i<m_RecordNo;i++)
				{
				if(m_bEventAcc[i] == 1)
				{
				m_TrueCount++;
				m_RTTotal += m_EventRT[i];
				}
				else if(m_bEventAcc[i] == 0)
				{
				m_FalseCount++;
				}
				else
				{
				m_MissingCount++;
				}
				}*/
				m_RTAvg = (double)m_RTTotal / (double)m_TrueCount;
				//m_RTTotal = 0;
				double sumRT = 0.;
				for (i = 0; i < m_RecordNo; i++)
				{
					if (m_bEventAcc[i] == 1)
					{
						sumRT += pow((m_EventRT[i] - m_RTAvg), 2);
					}
				}
				if (m_TrueCount > 1)
					m_RTSqr = pow((double)sumRT / (double)(m_TrueCount - 1), 0.5);
				else
					m_RTSqr = 0.;

			}
			else //选择模式
			{
				//初始化统计变量
				m_TrueCount = 0;
				m_MissingCount = 0;
				m_CRCount = 0;
				m_FalseCount = 0;
				m_FailCount = 0;
				m_RTTotal = 0; //靶事件反应总时

				for (i =/*m_ExperStart2*/0; i < m_RecordNo; i++)//遍历所有记录
				{
					if (m_EventType[i] == 0 && m_SureButtonNo[i] == 0) //统计击中数
						m_TrueCount++;
					if (m_EventType[i] == 0 && m_SureButtonNo[i] == 1) // 统计漏报数
						m_MissingCount++;
					if (m_EventType[i] == 1 && m_SureButtonNo[i] == 1) //统计正确拒斥数
						m_CRCount++;
					if (m_EventType[i] == 1 && m_SureButtonNo[i] == 0) //统计虚报数
						m_FalseCount++;
					if (m_EventType[i] == 2) //统计未触发事件时错误按键数
						m_FailCount++;
					if (m_bEventAcc[i] == 1) //统计靶事件反应时
						m_RTTotal += m_EventRT[i];

					//旧代码
					//					if(m_EventType[i] == 1)
					//					{
					//						if(m_bEventAcc[i] == 1)
					//						{
					//							m_TrueCount++;
					//							m_RTTotal += m_EventRT[i];
					//						}
					//						else
					//						{
					//							m_MissingCount++;
					//						}
					////						m_TargetCount++;
					//					}
					//					else
					//					{
					//						if(m_bEventAcc[i] == 1)
					//						{
					//							m_CRCount++;
					//							m_RTTotal += m_EventRT[i];
					//						}
					//						else
					//						{
					//							m_FalseCount++;
					//						}
					////						m_NoTargetCount++;
					//					}	
				}
				m_RTAvg = (float)m_RTTotal / (float)(m_TrueCount+m_CRCount);//靶事件反应时平均值
																				//				m_NoRTAvg = (float)m_NoRTTotal/(float)(m_CRCount);
				m_RTTotal = 0;
				double sumRT = 0.;
				//				m_NoRTTotal = 0;
				for (i =/*m_ExperStart2*/0; i < m_RecordNo; i++)
				{
					if (m_bEventAcc[i] == 1)
					{
						//						if(m_EventType[i] == 1)
						//						{
						sumRT += pow((m_EventRT[i] - m_RTAvg), 2);
						//						}
						//						else
						//						{
						//							m_NoRTTotal += pow((m_EventRT[i]-m_NoRTAvg),2);
						//						}
					}
				}
				//m_RTSqr = pow((double)m_RTTotal/(double)(m_TrueCount+m_CRCount-1),0.5);//靶事件反应时标准差
				//				m_NoRTSqr = pow((float)m_NoRTTotal/(float)(m_CRCount-1),0.5);
				if (m_TrueCount + m_CRCount > 1)
					m_RTSqr = pow((double)sumRT / (double)(m_TrueCount + m_CRCount - 1), 0.5);
				else
					m_RTSqr = 0.;
			}
		}

		//		pos = pDoc->m_FileName.ReverseFind('\\');
		//		pos1 = pDoc->m_FileName.ReverseFind('-');
		if (m_bOpenFile1)//记录track部分的统计结果
		{
			if (!bExitItem1)
			{
				if (m_MainTaskMode == 0)
				{
					_mkdir("Result");
					_mkdir("Result\\Task3");
					m_SaveName = "Result\\Task3\\task3_tracking_result.txt";
					fopen_s(&fp, m_SaveName, "at");
					if (fp != NULL)
					{
						if (!bExist1)
						{
							fprintf(fp, "FileName\tID\tName\tSex\tSession\t"
								"DistanceError\tPracMode\tExperMode\tMainTask\tSubTask\t"
								"MainTaskMode\tBackground\tInitSpeed\tEventMode\tCodePairMode\tCodePairNum\tDisplayMode\tEventFrequency\tPracTime\tExperTime\tPracTimes\tExperTimes\t"
								"DistanceAve\tDistanceSqt\tHitTimeTotal\tHitTimeRate\n");
						}
						fprintf(fp, "%s\t%s\t%s\t%s\t%d\t"
							"%.2f\t%d\t%d\t%d\t%d\t"
							"%d\t%d\t%.2f\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t"
							"%.2f\t%.2f\t%.2f\t%.2f\n",
							m_DataFileName, m_PartInfo.m_TesterNo, m_PartInfo.m_TesterName, m_PartInfo.m_TesterSex, m_PartInfo.m_Session,
							m_HardSetting.m_DistanceError, m_ReadSetting3[0].m_PracMode, m_ReadSetting3[0].m_ExperMode, m_ReadSetting3[0].m_MainTask, m_ReadSetting3[0].m_SubTask,
							m_ReadSetting3[0].m_MainTaskMode, m_ReadSetting3[0].m_Background, m_ReadSetting3[0].m_InitSpeed, m_ReadSetting3[0].m_EventMode, m_ReadSetting3[0].m_CodePairMode, m_ReadSetting3[0].m_CodePairNum, m_ReadSetting3[0].m_DisplayMode, m_ReadSetting3[0].m_EventFrequency, m_ReadSetting3[0].m_PracTime, m_ReadSetting3[0].m_ExperTime, m_ReadSetting3[0].m_PracTimes, m_ReadSetting3[0].m_ExperTimes,
							m_DistanceAve, m_DistanceSqt, m_HitTimeTotal, m_HitTimeRate);
						fclose(fp);
					}
				}
				else//这部分已经被废弃了，被event部分取代
				{
					_mkdir("Result");
					_mkdir("Result\\Task3");
					m_SaveName = "Result\\Task3\\task3_coding_result.txt";
					fopen_s(&fp, m_SaveName, "at");
					if (fp != NULL)
					{
						if (!bExist1)
						{
							fprintf(fp, "FileName\tID\tName\tSex\tSession\t"
								"PracMode\tExperMode\tMainTask\tSubTask\t"
								"MainTaskMode\tBackground\tInitSpeed\tEventMode\tCodePairMode\tCodePairNum\tDisplayMode\tEventFrequency\tPracTime\tExperTime\tPracTimes\tExperTimes\t"
								"Shape1\tNumber1\tShape2\tNumber2\tShape3\tNumber3\tShape4\tNumber4\tShape5\tNumber5\tShape6\tNumber6\t"
								"TrueCode\tFalseCode\tTrueCodeRate\tFalseCodeRate\tCodeRTAvg\tCodeRTSqr\n");
						}
						fprintf(fp, "%s\t%s\t%s\t%s\t%d\t"
							"%d\t%d\t%d\t%d\t"
							"%d\t%d\t%.2f\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t"
							"%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t"
							"%d\t%d\t%.2f\t%.2f\t%.2f\t%.2f\n",
							m_DataFileName, m_PartInfo.m_TesterNo, m_PartInfo.m_TesterName, m_PartInfo.m_TesterSex, m_PartInfo.m_Session,
							m_ReadSetting3[0].m_PracMode, m_ReadSetting3[0].m_ExperMode, m_ReadSetting3[0].m_MainTask, m_ReadSetting3[0].m_SubTask,
							m_ReadSetting3[0].m_MainTaskMode, m_ReadSetting3[0].m_Background, m_ReadSetting3[0].m_InitSpeed, m_ReadSetting3[0].m_EventMode, m_ReadSetting3[0].m_CodePairMode, m_CodePairNum, m_ReadSetting3[0].m_DisplayMode, m_ReadSetting3[0].m_EventFrequency, m_ReadSetting3[0].m_PracTime, m_ReadSetting3[0].m_ExperTime, m_ReadSetting3[0].m_PracTimes, m_ReadSetting3[0].m_ExperTimes,
							m_Shape[0], m_Character[0], m_Shape[1], m_Character[1], m_Shape[2], m_Character[2], m_Shape[3], m_Character[3], m_Shape[4], m_Character[4], m_Shape[5], m_Character[5],
							m_TrueCode, m_FalseCode, (float)m_TrueCode / (float)(m_TrueCode + m_FalseCode), (float)m_FalseCode / (float)(m_TrueCode + m_FalseCode), m_CodeRTAvg, m_CodeRTSqr);
						fclose(fp);
					}
				}
			}
		}

		if (m_bOpenFile2)
		{
			if (!bExitItem2)
			{
				if (m_ReadSetting3[0].m_EventMode == 0)//简单任务
				{
					_mkdir("Result");
					_mkdir("Result\\Task3");
					m_SaveName = "Result\\Task3\\task3_samrt_result.txt";
					fopen_s(&fp, m_SaveName, "at");
					if (fp != NULL)
					{
						if (!bExist2)
						{
							fprintf(fp, "FileName\tID\tName\tSex\tSession\t"
								"PracMode\tExperMode\tMainTask\tSubTask\t"
								"MainTaskMode\tBackground\tInitSpeed\tEventMode\tCodePairMode\tCodePairNum\tDisplayMode\tEventFrequency\tPracTime\tExperTime\tPracTimes\tExperTimes\t"
								"HIT\tMISS\tCR\tFA\tFail\tRTTimeAvg\tRTTimeSqr\n");
						}
						fprintf(fp, "%s\t%s\t%s\t%s\t%d\t"
							"%d\t%d\t%d\t%d\t"
							"%d\t%d\t%.2f\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t"
							"%d\t%d\t%d\t%d\t%.2f\t%.2f\n",
							m_DataFileName, m_PartInfo.m_TesterNo, m_PartInfo.m_TesterName, m_PartInfo.m_TesterSex, m_PartInfo.m_Session,
							m_ReadSetting3[0].m_PracMode, m_ReadSetting3[0].m_ExperMode, m_ReadSetting3[0].m_MainTask, m_ReadSetting3[0].m_SubTask,
							m_ReadSetting3[0].m_MainTaskMode, m_ReadSetting3[0].m_Background, m_ReadSetting3[0].m_InitSpeed, m_ReadSetting3[0].m_EventMode, m_ReadSetting3[0].m_CodePairMode, m_ReadSetting3[0].m_CodePairNum, m_ReadSetting3[0].m_DisplayMode, m_ReadSetting3[0].m_EventFrequency, m_ReadSetting3[0].m_PracTime, m_ReadSetting3[0].m_ExperTime, m_ReadSetting3[0].m_PracTimes, m_ReadSetting3[0].m_ExperTimes,
							m_TrueCount, m_MissingCount, m_FalseCount, m_FailCount, m_RTAvg, m_RTSqr);
						fclose(fp);
					}
				}
				else//选择任务
				{
					_mkdir("Result");
					_mkdir("Result\\Task3");
					m_SaveName = "Result\\Task3\\task3_selrt_result.txt";
					fopen_s(&fp, m_SaveName, "at");
					if (fp != NULL)
					{
						if (!bExist2)
						{
							fprintf(fp, "FileName\tID\tName\tSex\tSession\t"
								"PracMode\tExperMode\tMainTask\tSubTask\t"
								"MainTaskMode\tBackground\tInitSpeed\tEventMode\tCodePairMode\tCodePairNum\tDisplayMode\tEventFrequency\tPracTime\tExperTime\tPracTimes\tExperTimes\t"
								"HIT\tMISS\tCR\tFA\tFail\tm_RTTotalAvg\tm_RTTotalSqr\n");
						}
						fprintf(fp, "%s\t%s\t%s\t%s\t%d\t"
							"%d\t%d\t%d\t%d\t"
							"%d\t%d\t%.2f\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t"
							"%d\t%d\t%d\t%d\t%d\t%.2f\t%.2f\n",
							m_DataFileName, m_PartInfo.m_TesterNo, m_PartInfo.m_TesterName, m_PartInfo.m_TesterSex, m_PartInfo.m_Session,
							m_ReadSetting3[0].m_PracMode, m_ReadSetting3[0].m_ExperMode, m_ReadSetting3[0].m_MainTask, m_ReadSetting3[0].m_SubTask,
							m_ReadSetting3[0].m_MainTaskMode, m_ReadSetting3[0].m_Background, m_ReadSetting3[0].m_InitSpeed, m_ReadSetting3[0].m_EventMode, m_ReadSetting3[0].m_CodePairMode, m_ReadSetting3[0].m_CodePairNum, m_ReadSetting3[0].m_DisplayMode, m_ReadSetting3[0].m_EventFrequency, m_ReadSetting3[0].m_PracTime, m_ReadSetting3[0].m_ExperTime, m_ReadSetting3[0].m_PracTimes, m_ReadSetting3[0].m_ExperTimes,
							m_TrueCount, m_MissingCount, m_CRCount, m_FalseCount, m_FailCount, m_RTAvg, m_RTSqr);
						fclose(fp);
					}
				}
			}
		}
		break;
	case 4:
		if(m_bOpenFile1)
		{
			m_TouchTotal = 0;
			for(i=0;i<3;i++)
			{
				for(j=0;j<6;j++)
				{
					m_TouchRTTotal[i][j] = 0;
				}
			}
			for(i=m_ExperStart1;i<m_TouchNo;i++)
			{
				if(m_TouchNoOrder[i]>6)
				{
					TouchNo = m_TouchNoOrder[i]-6;
				}
				else
				{
                    TouchNo = m_TouchNoOrder[i];
				}
				if(m_TouchAcc[i]==1)
				{
					m_TouchRTTotal[m_TouchDistance[i]-1][TouchNo-1] += m_TouchRT[i];
					m_TouchTotal++;
				}
			}
			m_TouchTotal = m_TouchTotal/18;
//			pos = m_FileName.ReverseFind('\\');
//			pos1 = m_FileName.ReverseFind('-');
			if(!bExitItem1)
			{
				_mkdir("Result");
				_mkdir("Result\\Task4");
				m_SaveName = "Result\\Task4\\task4_touch_result.txt";
				fopen_s(&fp, m_SaveName,"at");
				if(fp!=NULL)
				{
					if(!bExist1)
					{
						fprintf(fp,"FileName\tID\tName\tSex\tSession\t"
							"PracMode\tExperMode\tTouchDirection\t"
							"RTAved1t1\tRTAved1t2\tRTAved1t3\tRTAved1t4\tRTAved1t5\tRTAved1t6\t"
							"RTAved2t1\tRTAved2t2\tRTAved2t3\tRTAved2t4\tRTAved2t5\tRTAved2t6\t"
							"RTAved3t1\tRTAved3t2\tRTAved3t3\tRTAved3t4\tRTAved3t5\tRTAved3t6\n");
					}
					fprintf(fp,"%s\t%s\t%s\t%s\t%d\t"
						"%d\t%d\t%d\t"
						"%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t"
						"%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t"
						"%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n",
						m_DataFileName, m_PartInfo.m_TesterNo, m_PartInfo.m_TesterName, m_PartInfo.m_TesterSex, m_PartInfo.m_Session,
						m_ReadSetting4[0].m_PracMode, m_ReadSetting4[0].m_ExperMode, m_ReadSetting4[0].m_TouchOrder,
						(float)m_TouchRTTotal[0][0]/(float)m_TouchTotal,(float)m_TouchRTTotal[0][1]/(float)m_TouchTotal,(float)m_TouchRTTotal[0][2]/(float)m_TouchTotal,(float)m_TouchRTTotal[0][3]/(float)m_TouchTotal,(float)m_TouchRTTotal[0][4]/(float)m_TouchTotal,(float)m_TouchRTTotal[0][5]/(float)m_TouchTotal,
						(float)m_TouchRTTotal[1][0]/(float)m_TouchTotal,(float)m_TouchRTTotal[1][1]/(float)m_TouchTotal,(float)m_TouchRTTotal[1][2]/(float)m_TouchTotal,(float)m_TouchRTTotal[1][3]/(float)m_TouchTotal,(float)m_TouchRTTotal[1][4]/(float)m_TouchTotal,(float)m_TouchRTTotal[1][5]/(float)m_TouchTotal,
						(float)m_TouchRTTotal[2][0]/(float)m_TouchTotal,(float)m_TouchRTTotal[2][1]/(float)m_TouchTotal,(float)m_TouchRTTotal[2][2]/(float)m_TouchTotal,(float)m_TouchRTTotal[2][3]/(float)m_TouchTotal,(float)m_TouchRTTotal[2][4]/(float)m_TouchTotal,(float)m_TouchRTTotal[2][5]/(float)m_TouchTotal);
					fclose(fp);
				}
			}
		}
		break;
	case 5:
		if(m_bOpenFile1)
		{
			m_TrialNum = 1;
            for(j=0;j<m_TrialNum;j++)
			{
				//i = 0;
				//do
				//{
				//	i++;
				//}while((m_PointTime[i]-m_PointTime[m_StartPoint[j]])<=5000);
				m_ValidStart[j] = m_StartPoint[j] + 125;
				for(i=m_ValidStart[j];i<m_StartPoint[j+1];i++)
				{
					m_DistanceTotal += m_Distance[i];
					if(m_bHit[i])
					{
						m_HitCount++;
					}
					m_PointTotal++;
				}
				m_TimeTotal+=(m_PointTime[m_StartPoint[j+1]-1]-m_PointTime[m_ValidStart[j]]);
			}
			m_DistanceAve = m_DistanceTotal/(float)m_PointTotal;
			m_HitTimeTotal = m_HitCount*40;
			m_HitTimeRate = (float)m_HitTimeTotal/(float)m_TimeTotal;
			m_DistanceTotal = 0;
			for(j=0;j<m_TrialNum;j++)
			{
				for(i=m_ValidStart[j];i<m_StartPoint[j+1];i++)
				{
					m_DistanceTotal += pow((m_Distance[i]-m_DistanceAve),2);
				}
			}
			m_DistanceSqt = pow((double)m_DistanceTotal/(double)(m_PointTotal-1),0.5);
		}

        if(m_bOpenFile2)
		{		
			for(i=0;i<5;i++)
			{
				m_SignRTTotal[i] = 0;
				m_SignTotal[i] = 0;
				m_SignTrueTotal[i] = 0;
				m_SignRTAvg[i] = 0;
				m_SignRTSqr[i] = 0;
				m_SignTrue[i] = 0;
				m_SignMissing[i] = 0;
				m_SignCR[i] = 0;
				m_SignFalse[i] = 0;
			}
			for(i=m_ExperStart2;i<m_RecordNo;i++)
			{
				if(m_SignType[i] == 0)//是
				{
					if(m_SignAcc[i] == 1)
					{
						m_SignTrue[m_SignMemNum[i]-4]++;
						m_SignRTTotal[m_SignMemNum[i]-4] += m_SignRT[i];
					}
					else
					{
						m_SignMissing[m_SignMemNum[i]-4]++;
//						m_MissingCount++;
					}
//					m_TargetCount++;
				}
				else//不是
				{
					if(m_SignAcc[i] == 1)
					{
						m_SignCR[m_SignMemNum[i]-4]++;
						m_SignRTTotal[m_SignMemNum[i]-4] += m_SignRT[i];
					}
					else
					{
						m_SignFalse[m_SignMemNum[i]-4]++;
					}
//					m_NoTargetCount++;
				}
/*				if(m_SignAcc[i]==1)
				{
					m_SignRTTotal[m_SignMemNum[i]-4] += m_SignRT[i];
					m_SignTrueTotal[m_SignMemNum[i]-4]++;
				}*/
				m_SignTotal[m_SignMemNum[i]-4]++;
			}
			for(i=0;i<5;i++)
			{
				m_SignTrueTotal[i] = m_SignTrue[i]+m_SignCR[i];
				if(m_SignTrueTotal[i]>0)
				{
					m_SignRTAvg[i] = (float)m_SignRTTotal[i]/(float)(m_SignTrueTotal[i]);	
				}
				m_SignRTTotal[i] = 0;
//				m_SignTrueRate[i] = (float)m_SignTrueTotal[i]/(float)m_SignTotal[i];
			}
			for(i=m_ExperStart2;i<m_RecordNo;i++)
			{
				if(m_SignAcc[i]==1)
				{
					m_SignRTTotal[m_SignMemNum[i]-4] += pow((m_SignRT[i]-m_SignRTAvg[m_SignMemNum[i]-4]),2);
				}
			}
			for(i=0;i<5;i++)
			{
				if(m_SignTrueTotal[i]>0)
				{
					m_SignRTSqr[i] = pow((double)m_SignRTTotal[i]/(double)(m_SignTrueTotal[i]-1),0.5);
				}
			}
		}
 		
//		pos = pDoc->m_FileName.ReverseFind('\\');
//	    pos1 = pDoc->m_FileName.ReverseFind('-');
		if(m_bOpenFile1)
		{
			if(!bExitItem1)
			{
				_mkdir("Result");
				_mkdir("Result\\Task5");
				m_SaveName = "Result\\Task5\\task5_tracking_result.txt";
				fopen_s(&fp, m_SaveName,"at");
				if(fp!=NULL)
				{
					if(!bExist1)
					{
						fprintf(fp,"FileName\tID\tName\tSex\tSession\t"
							"DistanceError\tPracMode\tExperMode\tMainTask\tSubTask\t"
							"Background\tInitSpeed\tSignMemType\tSignMemMode\tSignShowMode\tSignShowTime\tPracTime\tExperTime\tPracTimes\tExperTimes\t"
							"DistanceAve\tDistanceSqt\tHitTimeTotal\tHitTimeRate\n");
					}
					fprintf(fp,"%s\t%s\t%s\t%s\t%d\t"
						"%.2f\t%d\t%d\t%d\t%d\t"
						"%d\t%.2f\t%d\t%d\t%d\t%.1f\t%d\t%d\t%d\t%d\t"
						"%.2f\t%.2f\t%.2f\t%.2f\n",
						m_DataFileName, m_PartInfo.m_TesterNo, m_PartInfo.m_TesterName, m_PartInfo.m_TesterSex, m_PartInfo.m_Session, 
						m_HardSetting.m_DistanceError, m_ReadSetting5[0].m_PracMode, m_ReadSetting5[0].m_ExperMode, m_ReadSetting5[0].m_MainTask, m_ReadSetting5[0].m_SubTask,
						m_ReadSetting5[0].m_Background, m_ReadSetting5[0].m_InitSpeed, m_ReadSetting5[0].m_SignMemType, m_ReadSetting5[0].m_SignMemMode, m_ReadSetting5[0].m_SignShowMode, m_ReadSetting5[0].m_SignShowTime, m_ReadSetting5[0].m_PracTime, m_ReadSetting5[0].m_ExperTime, m_ReadSetting5[0].m_PracTimes, m_ReadSetting5[0].m_ExperTimes,
						m_DistanceAve, m_DistanceSqt, m_HitTimeTotal, m_HitTimeRate);
					fclose(fp);
				}
			}
		}

		if(m_bOpenFile2)
		{
			if(!bExitItem2)
			{
				_mkdir("Result");
				_mkdir("Result\\Task5");
				m_SaveName = "Result\\Task5\\task5_sign_result.txt";
				fopen_s(&fp, m_SaveName,"at");
				if(fp!=NULL)
				{
					if(!bExist2)
					{
						fprintf(fp,"FileName\tID\tName\tSex\tSession\t"
							"DistanceError\tPracMode\tExperMode\tMainTask\tSubTask\t"
							"Background\tInitSpeed\tSignMemType\tSignMemMode\tSignShowMode\tSignShowTime\tPracTime\tExperTime\tPracTimes\tExperTimes\t"
							"RTTimeAvg4\tRTTimeSqr4\tHIT4\tMISS4\tCR4\tFA4\tRTTimeAvg5\tRTTimeSqr5\tHIT5\tMISS5\tCR5\tFA5\tRTTimeAvg6\tRTTimeSqr6\tHIT6\tMISS6\tCR6\tFA6\t"
							"RTTimeAvg7\tRTTimeSqr7\tHIT7\tMISS7\tCR7\tFA7\tRTTimeAvg8\tRTTimeSqr8\tHIT8\tMISS8\tCR8\tFA8\n");
					}
					fprintf(fp,"%s\t%s\t%s\t%s\t%d\t"
						"%.2f\t%d\t%d\t%d\t%d\t"
						"%d\t%.2f\t%d\t%d\t%d\t%.1f\t%d\t%d\t%d\t%d\t",
						m_DataFileName, m_PartInfo.m_TesterNo, m_PartInfo.m_TesterName, m_PartInfo.m_TesterSex, m_PartInfo.m_Session, 
						m_HardSetting.m_DistanceError, m_ReadSetting5[0].m_PracMode, m_ReadSetting5[0].m_ExperMode, m_ReadSetting5[0].m_MainTask, m_ReadSetting5[0].m_SubTask,
						m_ReadSetting5[0].m_Background, m_ReadSetting5[0].m_InitSpeed, m_ReadSetting5[0].m_SignMemType, m_ReadSetting5[0].m_SignMemMode, m_ReadSetting5[0].m_SignShowMode, m_ReadSetting5[0].m_SignShowTime, m_ReadSetting5[0].m_PracTime, m_ReadSetting5[0].m_ExperTime, m_ReadSetting5[0].m_PracTimes, m_ReadSetting5[0].m_ExperTimes);
					for(i=0;i<5;i++)
					{
						if(m_SignTotal[i]>0)
						{
							fprintf(fp,"%.2f\t%.2f\t%d\t%d\t%d\t%d\t",m_SignRTAvg[i],m_SignRTSqr[i],m_SignTrue[i],m_SignMissing[i],m_SignCR[i],m_SignFalse[i]);
						}
						else
						{
							fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t","","","","","","");
						}
					}
					fprintf(fp,"\n");
					fclose(fp);
				}
			}
		}
		break;
	case 6:
		if(m_bOpenFile1)
		{
			m_TrialNum = 1;
            for(j=0;j<m_TrialNum;j++)
			{
				//i = 0;
				//do
				//{
				//	i++;
				//}while((m_PointTime[i]-m_PointTime[m_StartPoint[j]])<=5000);
				m_ValidStart[j] = m_StartPoint[j] + 125;
				for(i=m_ValidStart[j];i<m_StartPoint[j+1];i++)
				{
					m_DistanceTotal += m_Distance[i];
					if(m_bHit[i])
					{
						m_HitCount++;
					}
					m_PointTotal++;
				}
				m_TimeTotal+=(m_PointTime[m_StartPoint[j+1]-1]-m_PointTime[m_ValidStart[j]]);
			}
			m_DistanceAve = m_DistanceTotal/(float)m_PointTotal;
			m_HitTimeTotal = m_HitCount*40;
			m_HitTimeRate = (float)m_HitTimeTotal/(float)m_TimeTotal;
			m_DistanceTotal = 0;
			for(j=0;j<m_TrialNum;j++)
			{
				for(i=m_ValidStart[j];i<m_StartPoint[j+1];i++)
				{
					m_DistanceTotal += pow((m_Distance[i]-m_DistanceAve),2);
				}
			}
			m_DistanceSqt = pow((double)m_DistanceTotal/(double)(m_PointTotal-1),0.5);
		}

        if(m_bOpenFile2)
		{
			for(i=0;i<4;i++)
			{
				m_SignRTTotal[i] = 0;
				m_SignTotal[i] = 0;
				m_SignTrueTotal[i] = 0;
				m_SignRTAvg[i] = 0;
				m_SignRTSqr[i] = 0;
				m_SignTrue[i] = 0;
				m_SignMissing[i] = 0;
				m_SignCR[i] = 0;
				m_SignFalse[i] = 0;
			}
			for(i=/*m_ExperStart2*/0;i<m_RecordNo;i++)
			{
				if(m_Same[i] == 1)//相同
				{
					if(m_SignAcc[i] == 1)
					{
						m_SignTrue[m_CubeNum[i]-9]++;
						m_SignRTTotal[m_CubeNum[i]-9] += m_SignRT[i];
					}
					else
					{
						m_SignMissing[m_CubeNum[i]-9]++;
//						m_MissingCount++;
					}
//					m_TargetCount++;
				}
				else//不同
				{
					if(m_SignAcc[i] == 1)
					{
						m_SignCR[m_CubeNum[i]-9]++;
						m_SignRTTotal[m_CubeNum[i]-9] += m_SignRT[i];
					}
					else
					{
						m_SignFalse[m_CubeNum[i]-9]++;
					}
//					m_NoTargetCount++;
				}
/*				if(m_SignAcc[i]==1)
				{
					m_SignRTTotal[m_CubeNum[i]-9] += m_SignRT[i];
					m_SignTrueTotal[m_CubeNum[i]-9]++;
				}*/
				m_SignTotal[m_CubeNum[i]-9]++;
			}
			for(i=0;i<4;i++)
			{
				m_SignTrueTotal[i] = m_SignTrue[i]+m_SignCR[i];
				if(m_SignTrueTotal[i]>0)
				{
					m_SignRTAvg[i] = (float)m_SignRTTotal[i]/(float)(m_SignTrueTotal[i]);	
				}
				m_SignRTTotal[i] = 0;
//				m_SignTrueRate[i] = (float)m_SignTrueTotal[i]/(float)m_SignTotal[i];
			}
			for(i=/*m_ExperStart2*/0;i<m_RecordNo;i++)
			{
				if(m_SignAcc[i]==1)
				{
					m_SignRTTotal[m_CubeNum[i]-9] += pow((m_SignRT[i]-m_SignRTAvg[m_CubeNum[i]-9]),2);
				}
			}
			for(i=0;i<4;i++)
			{
				if(m_SignTrueTotal[i]>0)
				{
					if (m_SignTrueTotal[i] > 1)
						m_SignRTSqr[i] = pow((double)m_SignRTTotal[i] / (double)(m_SignTrueTotal[i] - 1), 0.5);
					else
						m_SignRTSqr[i] = 0.;
				}
			}
		}
//		pos = pDoc->m_FileName.ReverseFind('\\');
//	    pos1 = pDoc->m_FileName.ReverseFind('-');
		if(m_bOpenFile1)
		{
			if(!bExitItem1)
			{
				_mkdir("Result");
				_mkdir("Result\\Task6");
				m_SaveName = "Result\\Task6\\task6_tracking_result.txt";
				fopen_s(&fp, m_SaveName,"at");
				if(fp!=NULL)
				{
					if(!bExist1)
					{
						fprintf(fp,"FileName\tID\tName\tSex\tSession\t"
							"DistanceError\tPracMode\tExperMode\tMainTask\tSubTask\t"
							"Background\tInitSpeed\tCubeNum1\tCubeNum2\tCubeNum3\tCubeNum4\tPrototype\tRefAxis\tMemTaskMode\tPracTime\tExperTime\tPracTimes\tExperTimes\t"
							"DistanceAve\tDistanceSqt\tHitTimeTotal\tHitTimeRate\n");
					}
					fprintf(fp,"%s\t%s\t%s\t%s\t%d\t"
						"%.2f\t%d\t%d\t%d\t%d\t"
						"%d\t%.2f\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t"
						"%.2f\t%.2f\t%.2f\t%.2f\n",
						m_DataFileName, m_PartInfo.m_TesterNo, m_PartInfo.m_TesterName, m_PartInfo.m_TesterSex, m_PartInfo.m_Session, 
						m_HardSetting.m_DistanceError, m_ReadSetting6[0].m_PracMode, m_ReadSetting6[0].m_ExperMode, m_ReadSetting6[0].m_MainTask, m_ReadSetting6[0].m_SubTask,
						m_ReadSetting6[0].m_Background, m_ReadSetting6[0].m_InitSpeed, m_ReadSetting6[0].m_CubeNum1, m_ReadSetting6[0].m_CubeNum2, m_ReadSetting6[0].m_CubeNum3, m_ReadSetting6[0].m_CubeNum4, m_ReadSetting6[0].m_Prototype, m_ReadSetting6[0].m_RefAxis, m_ReadSetting6[0].m_MemTaskMode, m_ReadSetting6[0].m_PracTime, m_ReadSetting6[0].m_ExperTime, m_ReadSetting6[0].m_PracTimes, m_ReadSetting6[0].m_ExperTimes, 
						m_DistanceAve, m_DistanceSqt, m_HitTimeTotal, m_HitTimeRate);
					fclose(fp);
				}
			}
		}
        if(m_bOpenFile2)
		{
			if(!bExitItem2)
			{
				_mkdir("Result");
				_mkdir("Result\\Task6");
				if(m_MemTaskMode == 0)
				{
					m_SaveName = "Result\\Task6\\task6_judge_result.txt";
					fopen_s(&fp, m_SaveName,"at");
					if(fp!=NULL)
					{
						if(!bExist2)
						{
							fprintf(fp,"FileName\tID\tName\tSex\tSession\t"
								"DistanceError\tPracMode\tExperMode\tMainTask\tSubTask\t"
								"Background\tInitSpeed\tCubeNum1\tCubeNum2\tCubeNum3\tCubeNum4\tPrototype\tRefAxis\tMemTaskMode\tPracTime\tExperTime\tPracTimes\tExperTimes\t"
								"RTTimeAvg9\tRTTimeSqr9\tHIT9\tMISS9\tCR9\tFA9\tRTTimeAvg10\tRTTimeSqr10\tHIT10\tMISS10\tCR10\tFA10\t"
								"RTTimeAvg11\tRTTimeSqr11\tHIT11\tMISS11\tCR11\tFA11\tRTTimeAvg12\tRTTimeSqr12\tHIT12\tMISS12\tCR12\tFA12\n");
						}

						fprintf(fp,"%s\t%s\t%s\t%s\t%d\t"
							"%.2f\t%d\t%d\t%d\t%d\t"
							"%d\t%.2f\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t",
							m_DataFileName, m_PartInfo.m_TesterNo, m_PartInfo.m_TesterName, m_PartInfo.m_TesterSex, m_PartInfo.m_Session, 
							m_HardSetting.m_DistanceError, m_ReadSetting6[0].m_PracMode, m_ReadSetting6[0].m_ExperMode, m_ReadSetting6[0].m_MainTask, m_ReadSetting6[0].m_SubTask,
							m_ReadSetting6[0].m_Background, m_ReadSetting6[0].m_InitSpeed, m_ReadSetting6[0].m_CubeNum1, m_ReadSetting6[0].m_CubeNum2, m_ReadSetting6[0].m_CubeNum3, m_ReadSetting6[0].m_CubeNum4, m_ReadSetting6[0].m_Prototype, m_ReadSetting6[0].m_RefAxis, m_ReadSetting6[0].m_MemTaskMode, m_ReadSetting6[0].m_PracTime, m_ReadSetting6[0].m_ExperTime, m_ReadSetting6[0].m_PracTimes, m_ReadSetting6[0].m_ExperTimes);	
						for(i=0;i<4;i++)
						{
							if(m_SignTotal[i]>0)
							{
								fprintf(fp,"%.2f\t%.2f\t%d\t%d\t%d\t%d\t",m_SignRTAvg[i],m_SignRTSqr[i],m_SignTrue[i],m_SignMissing[i],m_SignCR[i],m_SignFalse[i]);
							}
							else
							{
								fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t","","","","","","");
							}
						}
						fprintf(fp,"\n");
						fclose(fp);
					}
				}
				else
				{
					m_SaveName = "Result\\Task6\\task6_memory_result.txt";
					fopen_s(&fp, m_SaveName,"at");
					if(fp!=NULL)
					{
						if(!bExist2)
						{
							fprintf(fp,"FileName\tID\tName\tSex\tSession\t"
								"DistanceError\tPracMode\tExperMode\tMainTask\tSubTask\t"
								"Background\tInitSpeed\tCubeNum1\tCubeNum2\tCubeNum3\tCubeNum4\tPrototype\tRefAxis\tMemTaskMode\tPracTime\tExperTime\tPracTimes\tExperTimes\t"
								"RTTimeAvg9\tRTTimeSqr9\tHIT9\tMISS9\tCR9\tFA9\tRTTimeAvg10\tRTTimeSqr10\tHIT10\tMISS10\tCR10\tFA10\t"
								"RTTimeAvg11\tRTTimeSqr11\tHIT11\tMISS11\tCR11\tFA11\tRTTimeAvg12\tRTTimeSqr12\tHIT12\tMISS12\tCR12\tFA12\n");
						}
						fprintf(fp,"%s\t%s\t%s\t%s\t%d\t"
							"%.2f\t%d\t%d\t%d\t%d\t"
							"%d\t%.2f\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t",
							m_DataFileName, m_PartInfo.m_TesterNo, m_PartInfo.m_TesterName, m_PartInfo.m_TesterSex, m_PartInfo.m_Session, 
							m_HardSetting.m_DistanceError, m_ReadSetting6[0].m_PracMode, m_ReadSetting6[0].m_ExperMode, m_ReadSetting6[0].m_MainTask, m_ReadSetting6[0].m_SubTask,
							m_ReadSetting6[0].m_Background, m_ReadSetting6[0].m_InitSpeed, m_ReadSetting6[0].m_CubeNum1, m_ReadSetting6[0].m_CubeNum2, m_ReadSetting6[0].m_CubeNum3, m_ReadSetting6[0].m_CubeNum4, m_ReadSetting6[0].m_Prototype, m_ReadSetting6[0].m_RefAxis, m_ReadSetting6[0].m_MemTaskMode, m_ReadSetting6[0].m_PracTime, m_ReadSetting6[0].m_ExperTime, m_ReadSetting6[0].m_PracTimes, m_ReadSetting6[0].m_ExperTimes);
						for(i=0;i<4;i++)
						{
							if(m_SignTotal[i]>0)
							{
								fprintf(fp,"%.2f\t%.2f\t%d\t%d\t%d\t%d\t",m_SignRTAvg[i],m_SignRTSqr[i],m_SignTrue[i],m_SignMissing[i],m_SignCR[i],m_SignFalse[i]);
							}
							else
							{
								fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t","","","","","","");
							}
						}
						fprintf(fp,"\n");
						fclose(fp);
					}
				}
			}
		}
		break;
	case 7: {
		//_mkdir("Result");
		//_mkdir("Result\\Task6");
		//m_SaveName = "Result\\Task6\\task6_tracking_result.txt";
		////fopen_s(&fp, m_SaveName, "at");
		//ofstream fout(m_SaveName, ios::app);
		//if (!fout.is_open()) break;
		break;
	}
	case 8://task8
		double CRCount=0;
		double ResTime=0;
		for (int i = 4; i < recs["t8"].size(); i++)
		{
			if (recs["t8"][i].isRight == 1) {
				CRCount++;
				ResTime += recs["t8"][i].responseTime;
			}
		}
		t8res.CorrectRate = CRCount / (recs["t8"].size()-4);
		t8res.AvgResTime = ResTime / /*(recs["t8"].size()-4)*/CRCount;
		t8res.TimeRate_Ratio = t8res.AvgResTime / t8res.CorrectRate;

		double avg = 0.0;
		for (int i = 4; i < recs["t8"].size(); i++) {
			if (recs["t8"][i].isRight == 1) 
				avg += fabs(recs["t8"][i].responseTime);
		}
		avg /= CRCount;
		double absSum = 0.;
		for (int i = 4; i < recs["t8"].size(); i++) {
			if (recs["t8"][i].isRight == 1)
				absSum += pow(fabs(recs["t8"][i].responseTime) - avg, 2);
		}
		if (CRCount > 2)
			t8res.SDrestime = sqrt(absSum / (/*recs["t8"].size() - 5*/CRCount-1));
		else
			t8res.SDrestime = 0;

		_mkdir("Result");
		_mkdir("Result\\Task8");
		m_SaveName = "Result\\Task8\\task8_result.txt";
		fopen_s(&fp, m_SaveName, "at");
		if (fp != NULL)
		{
			fprintf(fp, 
				"CorrectRate\tAvgResponseTime\tAvgResponseTime\\CorrectRate\SDResponseTime\n");
			fprintf(fp, 
				"%.3lf\t%.0lf\t%.0lf\%.0lf\t",
				t8res.CorrectRate, t8res.AvgResTime, t8res.TimeRate_Ratio, t8res.SDrestime);
			fprintf(fp, "\n");
			fclose(fp);

		}
		break;

	}		
}

double CTaskControlDoc::getAvgAbsDevRatio() {
	double avg = 0.0;
	int count=0;
	for (int i = 0; i < recs["t7"].size(); i++) {
		if (recs["t7"][i].deviationRate != -1)
		{
			avg += fabs(recs["t7"][i].deviationRate);
			count++;
		}
		
	}
	return avg / (double)count;
}

double CTaskControlDoc::getSDAbsDveRatio() {
	double absAvg = getAvgAbsDevRatio();
	double absSum = 0.;
	int count=0;
	for (int i = 0; i < recs["t7"].size(); i++) {
		if (recs["t7"][i].deviationRate != -1)
		{
			absSum += pow(fabs(recs["t7"][i].deviationRate) - absAvg, 2);
			count++;
		}
	}
		if (count >= 2)
		return sqrt(absSum / (count - 1));
	else
		return 0.;
}

int CTaskControlDoc::getUnRspCnt() {
	int cnt = 0;
	for (int i = 0; i < recs["t7"].size(); i++) {
		if (recs["t7"][i].deviationRate >= -1 - 1e-6
			&& recs["t7"][i].deviationRate <= -1 + 1e-6) {
			cnt++;
		}
	}
	return cnt;
}

double CTaskControlDoc::getTotalTaskPeriod() {
	double sum = 0.;
	for (int i = 0; i < recs["t7"].size(); i++) {
		sum += recs["t7"][i].totalPeriod;
	}
	return sum;
}