// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "TaskControl.h"

#include "MainFrm.h"
#include "direct.h"
#include "TesterView.h"
#include "SelectView.h"
#include "HardView.h"
#include "SettingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern CTaskControlApp theApp;
struct MYDATA {
	CTaskControlDoc *pDoc;
};
MYDATA MyThreadData;
#define WM_UPDATEDATA WM_USER + 1999 //定义事件

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_HARD_ADJUST, OnHardAdjust)
	ON_COMMAND(ID_TESTER_NEW, OnTesterNew)
	ON_COMMAND(ID_TESTER_OPEN, OnTesterOpen)
	ON_COMMAND(ID_SETTING_NEW, OnSettingNew)
	ON_COMMAND(ID_SETTING_OPEN, OnSettingOpen)
	ON_COMMAND(ID_HARD_SETTING, OnHardSetting)
	ON_COMMAND(ID_DISPLAYRESULT, OnDisplayresult)
	ON_COMMAND(ID_QUIT, OnQuit)
	ON_COMMAND(ID_START, OnStart)
	ON_COMMAND(ID_SETTING_NOW, OnSettingNow)
	ON_COMMAND(ID_TESTER_NOW, OnTesterNow)
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(ID_BATCH, OnBatch)
	
	ON_MESSAGE(WM_CLOSEDLG,OnCloseDlg)
	ON_MESSAGE(WM_UPDATEDATA, OnUpdateData)   //让事件关联程序
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
/*	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);*/
	
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
    cs.cx=1600;
	cs.cy=1500;
    cs.style&=~FWS_ADDTOTITLE;
	
	return TRUE;
	
}


// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame message handlers
//新建被试者信息
void CMainFrame::OnTesterNew() 
{
	CTaskControlApp*   pApp =(CTaskControlApp*)AfxGetApp();
	// TODO: Add your command handler code here
	CTaskControlDoc* pDoc = (CTaskControlDoc*)GetActiveDocument();
	if (NULL == theApp.SwitchView(TESTER))
		return;

	((CTesterView*)pApp->g_pView[TESTER])->m_bSetting = FALSE;
	CWnd *pwnd=(CWnd *)theApp.m_pMainWnd;
	((CTesterView*)pApp->g_pView[TESTER])->CenterWindow(pwnd);
	//((CTesterView*)pApp->g_pView[TESTER])->SetWindowPos(pwnd,200,200,300,300,SWP_NOSIZE);
	pDoc->NewTester();
	pDoc->UpdateAllViews(NULL,1);		
}

//打开被试者信息
void CMainFrame::OnTesterOpen() 
{
	// TODO: Add your command handler code here
	CTaskControlDoc* pDoc = (CTaskControlDoc*)GetActiveDocument();
	CTaskControlApp*   pApp =(CTaskControlApp*)AfxGetApp();
	((CTesterView*)pApp->g_pView[TESTER])->m_bSetting = FALSE;
	CString m_FileName;

	char buf[1000];  
    int i=1000;  
 
	CFileDialog Dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"Part Info Files (*.txt)|*.txt||",this); 
	

	char lpBuffer[MAX_PATH];  
	strcpy(lpBuffer,g_szExePath);
	strcat(lpBuffer, "\\PartInfo\\");
	Dlg.m_ofn.lpstrInitialDir=lpBuffer;	
	if(Dlg.DoModal()==IDOK)
	{
		m_FileName = Dlg.GetPathName();
    	FILE *fp;
		fopen_s(&fp, m_FileName,"rt");
		
		if(fp!=NULL)
		{
			
			fscanf_s(fp,"编号\t%s\n",pDoc->m_PartInfo.m_TesterNo,20);
			fscanf_s(fp,"姓名\t%s\n",pDoc->m_PartInfo.m_TesterName,20);
			fscanf_s(fp,"性别\t%s\n",pDoc->m_PartInfo.m_TesterSex,10);
			fscanf_s(fp,"年龄\t%d\n",&pDoc->m_PartInfo.m_TesterAge);
			fscanf_s(fp,"第N次\t%d\n",&pDoc->m_PartInfo.m_Session);
			fclose(fp);
		}
		if (NULL == theApp.SwitchView(TESTER))
			return;
     	pDoc->UpdateAllViews(NULL,1);
	}
	
}

//新建任务设置
void CMainFrame::OnSettingNew() 
{
	// TODO: Add your command handler code here
	CTaskControlApp*   pApp =(CTaskControlApp*)AfxGetApp();
	CTaskControlDoc* pDoc = (CTaskControlDoc*)GetActiveDocument();
	if (NULL == theApp.SwitchView(SELECT))
			return;
	
	CWnd *pwnd=(CWnd *)theApp.m_pMainWnd;
	((CSelectView*)pApp->g_pView[SELECT])->CenterWindow(pwnd);
	pDoc->NewSetting();
	pDoc->UpdateAllViews(NULL,1);
}

//打开任务设置
void CMainFrame::OnSettingOpen() 
{
	// TODO: Add your command handler code here
	CTaskControlDoc* pDoc = (CTaskControlDoc*)GetActiveDocument();
//	CString m_FileName;
	CFileDialog Dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"Task Setting Files (*.set)|*.set||",this); 

//	CFileDialog Dlg(TRUE,"(*.set)|*.set","*.set",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"Task Setting Files (*.set)",this); 
    
	char lpBuffer[MAX_PATH];  
	strcpy(lpBuffer,g_szExePath);
	strcat(lpBuffer,"\\Settings\\");
	Dlg.m_ofn.lpstrInitialDir= lpBuffer;	
	if(Dlg.DoModal()==IDOK)
	{
		pDoc->NewSetting();
		pDoc->m_CurSettingFile = Dlg.GetPathName();
    	ReadSetting(pDoc->m_CurSettingFile);
		if (NULL == theApp.SwitchView(SELECT))
			return;
	    pDoc->UpdateAllViews(NULL,1);
	}
	SetCurrentDirectory(lpBuffer);		
}

//硬件校准
void CMainFrame::OnHardAdjust() 
{
	// TODO: Add your command handler code here
    WinExec("RunDLL32.exe Shell32.dll,Control_RunDLL joy.cpl,,1",SW_SHOWNORMAL); 
}

//硬件设置
void CMainFrame::OnHardSetting() 
{
	// TODO: Add your command handler code here
//	CJoySettingDlg dlg;
//	dlg.DoModal();
	CTaskControlApp*   pApp =(CTaskControlApp*)AfxGetApp();
	CWnd *pwnd=(CWnd *)theApp.m_pMainWnd;
	((CHardView*)pApp->g_pView[HARD])->CenterWindow(pwnd);
	if (NULL == theApp.SwitchView(HARD))
		return;			
  
//	SwitchToView(HARD);		
}

//单个数据处理
void CMainFrame::OnDisplayresult() 
{
	// TODO: Add your command handler code here
	int pos;
	CTaskControlDoc* pDoc = (CTaskControlDoc*)GetActiveDocument();
	CString m_FileName;
	CFileDialog Dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"Result Files (*.txt)|*.txt||",this); 

//	CFileDialog Dlg(TRUE,"(*.txt)|*.txt","*.txt",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"Result Files (*.txt)",this); 
    DWORD nBufferLength=256; 
	char lpBuffer[256];  
//	char lpSaveBuffer[256];

	GetCurrentDirectory(nBufferLength,lpBuffer);
//	sprintf(lpSaveBuffer,"%s\\PartInfo",lpBuffer);
	Dlg.m_ofn.lpstrInitialDir="Data";	
	if(Dlg.DoModal()==IDOK)
	{
		pDoc->bBatch = FALSE;
		SetCurrentDirectory(lpBuffer);	
        m_FileName = Dlg.GetPathName();
    	pos = m_FileName.ReverseFind('\\');
		if(m_FileName.Mid(pos+1,1)!="T")
		{
	    	MessageBox("数据文件格式有误！");
			return;
		}
		pDoc->m_FileName = m_FileName;	
		m_pWSDlg = new CResultDlg(this);
		m_pWSDlg->Create(); // displays the dialog window
	}
	SetCurrentDirectory(lpBuffer);		
}

LRESULT CMainFrame::OnCloseDlg(WPARAM wParam,LPARAM lParam)
{
	m_pWSDlg->DestroyWindow();
	return 0L;
}

//读取任务设置
void CMainFrame::ReadSetting(CString FileName) 
{
    CTaskControlDoc* pDoc = (CTaskControlDoc*)GetActiveDocument();
    
	FILE *fp;
    int i = 0;
	char m_str[100];
	CString str;
	fopen_s(&fp, FileName,"rt");
	if(fp!=NULL)
	{
		for(i=0;i<MAX_TASK;i++)
		{
			pDoc->m_TaskNum[i] = 0;
		}
		fscanf_s(fp,"[TaskOrder]\n");
		fscanf_s(fp,"%s\n",m_str,100);
		str.Format("%s", m_str);
		i=0;
		while(str.Left(4)==_T("Task"))
		{
			pDoc->m_TaskOrder[i] = atoi(str.Mid(4,5))-1;
			pDoc->m_TaskNum[pDoc->m_TaskOrder[i]]++;
			fscanf_s(fp,"%s\n",m_str,100);
		    str.Format("%s", m_str);
			i++;
		}
		pDoc->m_TaskCount = i;

        for(i=0;i<MAX_TASK;i++)
		{
			if(pDoc->m_TaskNum[i]>0)
			{
				switch(i)
				{
				case 0:
					pDoc->m_Setting1 = new struct TaskSetting1[pDoc->m_TaskNum[0]];
					pDoc->m_DocNum[i] = pDoc->m_TaskNum[i];
					break;
				case 1:
					pDoc->m_Setting2 = new struct TaskSetting2[pDoc->m_TaskNum[1]];
					pDoc->m_DocNum[i] = pDoc->m_TaskNum[i];
					break;
				case 2:
					pDoc->m_Setting3 = new struct TaskSetting3[pDoc->m_TaskNum[2]];
					pDoc->m_DocNum[i] = pDoc->m_TaskNum[i];
					break;
				case 3:
					pDoc->m_Setting4 = new struct TaskSetting4[pDoc->m_TaskNum[3]];
					pDoc->m_DocNum[i] = pDoc->m_TaskNum[i];
					break;
				case 4:
					pDoc->m_Setting5 = new struct TaskSetting5[pDoc->m_TaskNum[4]];
					pDoc->m_DocNum[i] = pDoc->m_TaskNum[i];
					break;
				case 5:
					pDoc->m_Setting6 = new struct TaskSetting6[pDoc->m_TaskNum[5]];
					pDoc->m_DocNum[i] = pDoc->m_TaskNum[i];
					break;
				case 6:
					pDoc->m_Setting7 = new struct TaskSetting7[pDoc->m_TaskNum[6]];
					pDoc->m_DocNum[i] = pDoc->m_TaskNum[i];
					break;
				case 7:
					pDoc->m_Setting8 = new struct TaskSetting8[pDoc->m_TaskNum[7]];
					pDoc->m_DocNum[i] = pDoc->m_TaskNum[i];
					break;
				}
			}
		}
		int TaskOrder;
		int i1=0;
		int i2=0;
		int i3=0;
		int i4=0;
		int i5=0;
		int i6=0;
		int i7 = 0;
		int i8 = 0;
		int idx;
		while(str.Left(5)==_T("[Task"))
		{
			TaskOrder = atoi(str.Mid(5,6))-1;
		    switch(TaskOrder)
			{
			case 0:
				//Task1
		//		fscanf(fp,"[Task1]\n");
				fscanf_s(fp,"TaskName\t%d-%s\n",&idx,pDoc->m_Setting1[i1].m_TaskName,100);
				fscanf_s(fp,"PracMode\t%d\n",&pDoc->m_Setting1[i1].m_PracMode);
				fscanf_s(fp,"ExperMode\t%d\n",&pDoc->m_Setting1[i1].m_ExperMode);
				fscanf_s(fp,"Background\t%d\n",&pDoc->m_Setting1[i1].m_Background);
				fscanf_s(fp,"Track\t%d\n",&pDoc->m_Setting1[i1].m_Track);
				fscanf_s(fp,"Direction\t%d\n",&pDoc->m_Setting1[i1].m_Direction);
				fscanf_s(fp,"MoveMode\t%d\n",&pDoc->m_Setting1[i1].m_MoveMode);
				fscanf_s(fp,"SpeedMode\t%d\n",&pDoc->m_Setting1[i1].m_SpeedMode);
				fscanf_s(fp,"Pause\t%d\n",&pDoc->m_Setting1[i1].m_Pause);
				fscanf_s(fp,"PauseNum\t%d\n",&pDoc->m_Setting1[i1].m_PauseNum);
				fscanf_s(fp,"Speed\t%f\n",&pDoc->m_Setting1[i1].m_Speed);
				fscanf_s(fp,"InitSpeed\t%f\n",&pDoc->m_Setting1[i1].m_InitSpeed);
				fscanf_s(fp,"SpeedMin\t%f\n",&pDoc->m_Setting1[i1].m_SpeedMin);
				fscanf_s(fp,"SpeedMax\t%f\n",&pDoc->m_Setting1[i1].m_SpeedMax);
				fscanf_s(fp,"AccelerationMin\t%f\n",&pDoc->m_Setting1[i1].m_AccelerationMin);
				fscanf_s(fp,"AccelerationMax\t%f\n",&pDoc->m_Setting1[i1].m_AccelerationMax);
				fscanf_s(fp,"AngleSpeedMin\t%f\n",&pDoc->m_Setting1[i1].m_AngleSpeedMin);
				fscanf_s(fp,"AngleSpeedMax\t%f\n",&pDoc->m_Setting1[i1].m_AngleSpeedMax);
				fscanf_s(fp,"RotateAngleMin\t%f\n",&pDoc->m_Setting1[i1].m_RotateAngleMin);
				fscanf_s(fp,"RotateAngleMax\t%f\n",&pDoc->m_Setting1[i1].m_RotateAngleMax);
				fscanf_s(fp,"PracTime\t%d\n",&pDoc->m_Setting1[i1].m_PracTime);
				fscanf_s(fp,"ExperTime\t%d\n",&pDoc->m_Setting1[i1].m_ExperTime);
				fscanf_s(fp,"PracTimes\t%d\n",&pDoc->m_Setting1[i1].m_PracTimes);
				fscanf_s(fp,"ExperTimes\t%d\n",&pDoc->m_Setting1[i1].m_ExperTimes);
				fscanf_s(fp,"JoyMoveDirection\t%d\n",&pDoc->m_Setting1[i1].m_iJoyMoveDirection);
				fscanf_s(fp,"\n");
				i1++;
				break;
			case 1:
				//Task2
		//		fscanf(fp,"[Task2]\n");
				fscanf_s(fp,"TaskName\t%d-%s\n",&idx, pDoc->m_Setting2[i2].m_TaskName,100);
				fscanf_s(fp,"PracMode\t%d\n",&pDoc->m_Setting2[i2].m_PracMode);
				fscanf_s(fp,"ExperMode\t%d\n",&pDoc->m_Setting2[i2].m_ExperMode);
				fscanf_s(fp,"MainTask\t%d\n",&pDoc->m_Setting2[i2].m_MainTask);
				fscanf_s(fp,"SubTask\t%d\n",&pDoc->m_Setting2[i2].m_SubTask);
				fscanf_s(fp,"Background\t%d\n",&pDoc->m_Setting2[i2].m_Background);
				fscanf_s(fp,"Direction\t%d\n",&pDoc->m_Setting2[i2].m_Direction);
				fscanf_s(fp,"InitSpeed\t%f\n",&pDoc->m_Setting2[i2].m_InitSpeed);
				fscanf_s(fp,"HoldTimeNum\t%d\n",&pDoc->m_Setting2[i2].m_HoldTimeNum);
				fscanf_s(fp,"HoldTime1\t%f\n",&pDoc->m_Setting2[i2].m_HoldTime[0]);
				fscanf_s(fp,"HoldTime2\t%f\n",&pDoc->m_Setting2[i2].m_HoldTime[1]);
				fscanf_s(fp,"HoldTime3\t%f\n",&pDoc->m_Setting2[i2].m_HoldTime[2]);
				fscanf_s(fp,"HoldTime4\t%f\n",&pDoc->m_Setting2[i2].m_HoldTime[3]);
				fscanf_s(fp,"HoldTime5\t%f\n",&pDoc->m_Setting2[i2].m_HoldTime[4]);
				fscanf_s(fp,"HoldTime6\t%f\n",&pDoc->m_Setting2[i2].m_HoldTime[5]);
				fscanf_s(fp,"HoldTime7\t%f\n",&pDoc->m_Setting2[i2].m_HoldTime[6]);
				fscanf_s(fp,"HoldTime8\t%f\n",&pDoc->m_Setting2[i2].m_HoldTime[7]);
				fscanf_s(fp,"HoldTime9\t%f\n",&pDoc->m_Setting2[i2].m_HoldTime[8]);
				fscanf_s(fp,"HoldTime10\t%f\n",&pDoc->m_Setting2[i2].m_HoldTime[9]);
				fscanf_s(fp,"HoldTime11\t%f\n",&pDoc->m_Setting2[i2].m_HoldTime[10]);
				fscanf_s(fp,"HoldTime12\t%f\n",&pDoc->m_Setting2[i2].m_HoldTime[11]);
				fscanf_s(fp,"PracTime\t%d\n",&pDoc->m_Setting2[i2].m_PracTime);
				fscanf_s(fp,"ExperTime\t%d\n",&pDoc->m_Setting2[i2].m_ExperTime);
				fscanf_s(fp,"PracTimes\t%d\n",&pDoc->m_Setting2[i2].m_PracTimes);
				fscanf_s(fp,"ExperTimes\t%d\n",&pDoc->m_Setting2[i2].m_ExperTimes);
				fscanf_s(fp,"JoyMoveDirection\t%d\n",&pDoc->m_Setting2[i2].m_iJoyMoveDirection);
				fscanf_s(fp,"SubTaskInterval\t%d\n",&pDoc->m_Setting2[i2].m_iSubTaskInterval);
				fscanf_s(fp,"SpeedMode\t%d\n",&pDoc->m_Setting2[i2].m_SpeedMode);
				fscanf_s(fp,"Speed\t%f\n",&pDoc->m_Setting2[i2].m_Speed);
				fscanf_s(fp,"SpeedMin\t%f\n",&pDoc->m_Setting2[i2].m_SpeedMin);
				fscanf_s(fp,"SpeedMax\t%f\n",&pDoc->m_Setting2[i2].m_SpeedMax);
				fscanf_s(fp,"AccelerationMin\t%f\n",&pDoc->m_Setting2[i2]. m_AccelerationMin);
				fscanf_s(fp,"AccelerationMax\t%f\n",&pDoc->m_Setting2[i2]. m_AccelerationMax);
				fscanf_s(fp,"Track\t%d\n",&pDoc->m_Setting2[i2]. m_iTrack);
				
				fscanf_s(fp,"\n");
				i2++;
				break;
			case 2:
				//Task3
		//		fscanf(fp,"[Task3]\n");
				fscanf_s(fp,"TaskName\t%d-%s\n",&idx,pDoc->m_Setting3[i3].m_TaskName,100);
				fscanf_s(fp,"PracMode\t%d\n",&pDoc->m_Setting3[i3].m_PracMode);
				fscanf_s(fp,"ExperMode\t%d\n",&pDoc->m_Setting3[i3].m_ExperMode);	
				fscanf_s(fp,"MainTask\t%d\n",&pDoc->m_Setting3[i3].m_MainTask);
				fscanf_s(fp,"SubTask\t%d\n",&pDoc->m_Setting3[i3].m_SubTask);	
				fscanf_s(fp,"MainTaskMode\t%d\n",&pDoc->m_Setting3[i3].m_MainTaskMode);	
				fscanf_s(fp,"Background\t%d\n",&pDoc->m_Setting3[i3].m_Background);
 				fscanf_s(fp,"InitSpeed\t%f\n",&pDoc->m_Setting3[i3].m_InitSpeed);
				fscanf_s(fp,"EventMode\t%d\n",&pDoc->m_Setting3[i3].m_EventMode);	
				fscanf_s(fp,"CodePairMode\t%d\n",&pDoc->m_Setting3[i3].m_CodePairMode);	
				fscanf_s(fp,"CodePairNum\t%d\n",&pDoc->m_Setting3[i3].m_CodePairNum);	
				fscanf_s(fp,"DisplayMode\t%d\n",&pDoc->m_Setting3[i3].m_DisplayMode);	
				fscanf_s(fp,"EventFrequency\t%d\n",&pDoc->m_Setting3[i3].m_EventFrequency);
				fscanf_s(fp,"PracTime\t%d\n",&pDoc->m_Setting3[i3].m_PracTime);
				fscanf_s(fp,"ExperTime\t%d\n",&pDoc->m_Setting3[i3].m_ExperTime);
				fscanf_s(fp,"PracTimes\t%d\n",&pDoc->m_Setting3[i3].m_PracTimes);
				fscanf_s(fp,"ExperTimes\t%d\n",&pDoc->m_Setting3[i3].m_ExperTimes);
				fscanf_s(fp,"JoyMoveDirection\t%d\n",&pDoc->m_Setting3[i3].m_iJoyMoveDirection);
				fscanf_s(fp,"PlanePos\t%d\n",&pDoc->m_Setting3[i3].m_iPlanePos);
				fscanf_s(fp,"Direction\t%d\n",&pDoc->m_Setting3[i3].m_Direction);
				fscanf_s(fp,"SpeedMode\t%d\n",&pDoc->m_Setting3[i3].m_SpeedMode);
				fscanf_s(fp,"Speed\t%f\n",&pDoc->m_Setting3[i3].m_Speed);
				fscanf_s(fp,"SpeedMin\t%f\n",&pDoc->m_Setting3[i3].m_SpeedMin);
				fscanf_s(fp,"SpeedMax\t%f\n",&pDoc->m_Setting3[i3].m_SpeedMax);
				fscanf_s(fp,"AccelerationMin\t%f\n",&pDoc->m_Setting3[i3]. m_AccelerationMin);
				fscanf_s(fp,"AccelerationMax\t%f\n",&pDoc->m_Setting3[i3]. m_AccelerationMax);
				fscanf_s(fp,"Track\t%d\n",&pDoc->m_Setting3[i3]. m_iTrack);
				fscanf_s(fp,"Plane\t%d\n",&pDoc->m_Setting3[i3].m_iPlane);
				fscanf_s(fp,"Helicopter\t%d\n",&pDoc->m_Setting3[i3].m_iHelicopter);
				fscanf_s(fp,"PresentTime\t%d\n",&pDoc->m_Setting3[i3].m_iPresentTime);
				fscanf_s(fp,"IntervalMin\t%d\n",&pDoc->m_Setting3[i3].m_iIntervalMin);
				fscanf_s(fp,"IntervalMax\t%d\n",&pDoc->m_Setting3[i3].m_iIntervalMax);
				fscanf_s(fp,"ReactTime\t%d\n",&pDoc->m_Setting3[i3].m_iReactTime);
				fscanf_s(fp,"\n");
				i3++;
				break;
			case 3:
				//Task4
		//		fscanf(fp,"[Task4]\n");
				fscanf_s(fp,"TaskName\t%d-%s\n",&idx,pDoc->m_Setting4[i4].m_TaskName,100);
				fscanf_s(fp,"PracMode\t%d\n",&pDoc->m_Setting4[i4].m_PracMode);
				fscanf_s(fp,"ExperMode\t%d\n",&pDoc->m_Setting4[i4].m_ExperMode);		
				fscanf_s(fp,"Background\t%d\n",&pDoc->m_Setting4[i4].m_Background);
				fscanf_s(fp,"TouchOrder\t%d\n",&pDoc->m_Setting4[i4].m_TouchOrder);	
				fscanf_s(fp,"PracTimes\t%d\n",&pDoc->m_Setting4[i4].m_PracTimes);
				fscanf_s(fp,"ExperTimes\t%d\n",&pDoc->m_Setting4[i4].m_ExperTimes);
				fscanf_s(fp,"\n");
				i4++;
				break;
			case 4:
				//Task5
		//		fscanf(fp,"[Task5]\n");
				fscanf_s(fp,"TaskName\t%d-%s\n",&idx,pDoc->m_Setting5[i5].m_TaskName,100);
				fscanf_s(fp,"PracMode\t%d\n",&pDoc->m_Setting5[i5].m_PracMode);
				fscanf_s(fp,"ExperMode\t%d\n",&pDoc->m_Setting5[i5].m_ExperMode);	
				fscanf_s(fp,"MainTask\t%d\n",&pDoc->m_Setting5[i5].m_MainTask);
				fscanf_s(fp,"SubTask\t%d\n",&pDoc->m_Setting5[i5].m_SubTask);
				fscanf_s(fp,"Background\t%d\n",&pDoc->m_Setting5[i5].m_Background);
 				fscanf_s(fp,"InitSpeed\t%f\n",&pDoc->m_Setting5[i5].m_InitSpeed);
				fscanf_s(fp,"SignMemType\t%d\n",&pDoc->m_Setting5[i5].m_SignMemType);
				fscanf_s(fp,"SignMemMode\t%hd\n",&pDoc->m_Setting5[i5].m_SignMemMode);	
				fscanf_s(fp,"SignMemNum\t%d\n",&pDoc->m_Setting5[i5].m_SignMemNum);	
				fscanf_s(fp,"SignShowMode\t%hd\n",&pDoc->m_Setting5[i5].m_SignShowMode);	
				fscanf_s(fp,"SignShowTime\t%f\n",&pDoc->m_Setting5[i5].m_SignShowTime);	
				fscanf_s(fp,"PracTime\t%d\n",&pDoc->m_Setting5[i5].m_PracTime);
				fscanf_s(fp,"ExperTime\t%d\n",&pDoc->m_Setting5[i5].m_ExperTime);
				fscanf_s(fp,"PracTimes\t%d\n",&pDoc->m_Setting5[i5].m_PracTimes);
				fscanf_s(fp,"ExperTimes\t%d\n",&pDoc->m_Setting5[i5].m_ExperTimes);
				fscanf_s(fp,"JoyMoveDirection\t%d\n",&pDoc->m_Setting5[i5].m_iJoyMoveDirection);
				fscanf_s(fp,"\n");
				i5++;
				break;
			case 5:
				//Task6
		//		fscanf(fp,"[Task6]\n");
				fscanf_s(fp,"TaskName\t%d-%s\n",&idx,pDoc->m_Setting6[i6].m_TaskName,100);
				fscanf_s(fp,"PracMode\t%d\n",&pDoc->m_Setting6[i6].m_PracMode);
				fscanf_s(fp,"ExperMode\t%d\n",&pDoc->m_Setting6[i6].m_ExperMode);	
				fscanf_s(fp,"MainTask\t%d\n",&pDoc->m_Setting6[i6].m_MainTask);
				fscanf_s(fp,"SubTask\t%d\n",&pDoc->m_Setting6[i6].m_SubTask);
				fscanf_s(fp,"Background\t%hd\n",&pDoc->m_Setting6[i6].m_Background);
 				fscanf_s(fp,"InitSpeed\t%f\n",&pDoc->m_Setting6[i6].m_InitSpeed);
				fscanf_s(fp,"CubeNum1\t%d\n",&pDoc->m_Setting6[i6].m_CubeNum1);
				fscanf_s(fp,"CubeNum2\t%d\n",&pDoc->m_Setting6[i6].m_CubeNum2);
				fscanf_s(fp,"CubeNum3\t%d\n",&pDoc->m_Setting6[i6].m_CubeNum3);
				fscanf_s(fp,"CubeNum4\t%d\n",&pDoc->m_Setting6[i6].m_CubeNum4);
				fscanf_s(fp,"Prototype\t%hd\n",&pDoc->m_Setting6[i6].m_Prototype);
				fscanf_s(fp,"RefAxis\t%hd\n",&pDoc->m_Setting6[i6].m_RefAxis);
				fscanf_s(fp,"MemTaskMode\t%hd\n",&pDoc->m_Setting6[i6].m_MemTaskMode);	
				fscanf_s(fp,"PracTime\t%d\n",&pDoc->m_Setting6[i6].m_PracTime);
				fscanf_s(fp,"ExperTime\t%d\n",&pDoc->m_Setting6[i6].m_ExperTime);
				fscanf_s(fp,"PracTimes\t%d\n",&pDoc->m_Setting6[i6].m_PracTimes);
				fscanf_s(fp,"ExperTimes\t%d\n",&pDoc->m_Setting6[i6].m_ExperTimes);
				fscanf_s(fp,"JoyMoveDirection\t%d\n",&pDoc->m_Setting6[i6].m_iJoyMoveDirection);
				fscanf_s(fp,"SubTaskInterval\t%d\n",&pDoc->m_Setting6[i6].m_iSubTaskInterval);
				fscanf_s(fp,"PresentTime\t%d\n",&pDoc->m_Setting6[i6].m_iPresentTime);
				fscanf_s(fp,"ReactTime\t%d\n",&pDoc->m_Setting6[i6].m_iReactTime);
				fscanf_s(fp,"Speed\t%f\n",&pDoc->m_Setting6[i6].m_Speed);
				fscanf_s(fp,"SpeedMin\t%f\n",&pDoc->m_Setting6[i6].m_SpeedMin);
				fscanf_s(fp,"SpeedMax\t%f\n",&pDoc->m_Setting6[i6].m_SpeedMax);
				fscanf_s(fp,"AccelerationMin\t%f\n",&pDoc->m_Setting6[i6].m_AccelerationMin);
				fscanf_s(fp,"AccelerationMax\t%f\n",&pDoc->m_Setting6[i6].m_AccelerationMax);
				fscanf_s(fp,"SpeedMode\t%d\n",&pDoc->m_Setting6[i6].m_SpeedMode);
				fscanf_s(fp,"Direction\t%d\n",&pDoc->m_Setting6[i6].m_Direction);

				fscanf_s(fp,"\n");
			    i6++;
				break;
			case 6:
				fscanf_s(fp,"TaskName\t%d-%s\n",&idx,pDoc->m_Setting7[i7].m_TaskName,100);
				fscanf_s(fp,"PracMode\t%d\n",&pDoc->m_Setting7[i7].m_PracMode);
				fscanf_s(fp,"ExperMode\t%d\n",&pDoc->m_Setting7[i7].m_ExperMode);
				fscanf_s(fp,"SpeedMode\t%d\n",&pDoc->m_Setting7[i7].m_iSpeedMode);
				fscanf_s(fp,"BallColorR\t%d\n",&pDoc->m_Setting7[i7].m_iBallColorR);
				fscanf_s(fp,"BallColorG\t%d\n",&pDoc->m_Setting7[i7].m_iBallColorG);
				fscanf_s(fp,"BallColorB\t%d\n",&pDoc->m_Setting7[i7].m_iBallColorB);
				fscanf_s(fp,"BallStartPos\t%d\n",&pDoc->m_Setting7[i7].m_iBallStartPos);
				fscanf_s(fp, "PosTop\t%d\n", &pDoc->m_Setting7[i7].m_iTop);
				fscanf_s(fp, "PosBottom\t%d\n", &pDoc->m_Setting7[i7].m_iBottom);
				fscanf_s(fp, "PosLeft\t%d\n", &pDoc->m_Setting7[i7].m_iLeft);
				fscanf_s(fp, "PosRight\t%d\n", &pDoc->m_Setting7[i7].m_iRight);
				fscanf_s(fp, "BallCenterDis\t%d\n", &pDoc->m_Setting7[i7].m_iBallCenterDis);
				fscanf_s(fp,"BallSpeed1\t%d\n",&pDoc->m_Setting7[i7].m_iBallSpeed1);
				fscanf_s(fp, "BallSpeed2\t%d\n", &pDoc->m_Setting7[i7].m_iBallSpeed2);
				fscanf_s(fp, "BallSpeed3\t%d\n", &pDoc->m_Setting7[i7].m_iBallSpeed3);
				fscanf_s(fp,"BallSpeedAcc\t%d\n",&pDoc->m_Setting7[i7].m_iBallSpeedAcc);
				fscanf_s(fp,"BallSpeedMax\t%d\n",&pDoc->m_Setting7[i7].m_iBallSpeedMax);

				fscanf_s(fp,"BallRadius\t%d\n",&pDoc->m_Setting7[i7].m_iBallRadius);
				fscanf_s(fp,"BckGrndColorR\t%d\n",&pDoc->m_Setting7[i7].m_iBckGrndColorR);
				fscanf_s(fp,"BckGrndColorG\t%d\n",&pDoc->m_Setting7[i7].m_iBckGrndColorG);
				fscanf_s(fp,"BckGrndColorB\t%d\n",&pDoc->m_Setting7[i7].m_iBckGrndColorB);
				fscanf_s(fp,"ObstacleColorR\t%d\n",&pDoc->m_Setting7[i7].m_iObstacleColorR);
				fscanf_s(fp,"ObstacleColorG\t%d\n",&pDoc->m_Setting7[i7].m_iObstacleColorG);
				fscanf_s(fp,"ObstacleColorB\t%d\n",&pDoc->m_Setting7[i7].m_iObstacleColorB);
				fscanf_s(fp,"ObstacleRadius\t%d\n",&pDoc->m_Setting7[i7].m_iObstacleRadius);
				fscanf_s(fp,"PracTimes\t%d\n",&pDoc->m_Setting7[i7].m_iPracTimes);
				fscanf_s(fp,"ExpTimes\t%d\n",&pDoc->m_Setting7[i7].m_iExpTimes);
				fscanf_s(fp,"IntervalTime\t%d\n",&pDoc->m_Setting7[i7].m_iIntervalTime);
	
				fscanf_s(fp,"\n");
			    i7++;
				break;
			case 7:
				fscanf_s(fp, "TaskName\t%d-%s\n", &idx, &pDoc->m_Setting8[i8].m_TaskName,100);
				//fscanf_s(fp, "PracMode\t%d\n", &pDoc->m_Setting8[i8].m_bPracMode);
				fscanf_s(fp, "PresentTime\t%d\n", &pDoc->m_Setting8[i8].m_iPrensentTime);
				fscanf_s(fp, "FocusTime\t%d\n", &pDoc->m_Setting8[i8].m_iFocusTime);
				fscanf_s(fp, "CountdownTime\t%d\n", &pDoc->m_Setting8[i8].m_iCountdownTime);
				fscanf_s(fp, "\n");
				i8++;
				break;

			}
			strcpy_s(m_str,100,"");
			fscanf_s(fp,"%s\n",m_str,100);
			str.Format("%s", m_str);
		}
//		fscanf(fp,"\n");
		fclose(fp);
	}
}

void CMainFrame::OnQuit() 
{
	// TODO: Add your command handler code here
	if ( MessageBox("确实要退出系统吗？","提示信息",MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON2)==IDYES )
	{
		CFrameWnd::OnClose();
	}	
}

//开始实验
void CMainFrame::OnStart() 
{
	// TODO: Add your command handler code here
    CTaskControlDoc* pDoc = (CTaskControlDoc*)GetActiveDocument();
	CTaskControlApp*   pApp =(CTaskControlApp*)AfxGetApp();

	CString str;
	if(strcmp(pDoc->m_CurPartInfo.m_TesterNo,"")==0)
	{
		str.Format("被试者编号没有设置！");
		MessageBox(str);
		return;
	}
	if(strcmp(pDoc->m_CurPartInfo.m_TesterName,"")==0)
	{
		str.Format("被试者姓名没有设置！");
		MessageBox(str);
		return;
	}

	//循环遍历 若全部设置完毕 就进行保存exe 并提示保存
	if (!(((CTesterView*)pApp->g_pView[TESTER])->m_bSetting && ((CSelectView*)pApp->g_pView[SELECT])->m_bSetting && \
		((CHardView*)pApp->g_pView[HARD])->m_bSetting))
	{
		MessageBox("请确保用户设置，任务设置，硬件设置都已确认完毕");
		return; 
	}
	



    PROCESS_INFORMATION PI;
    STARTUPINFO SI;
	char m_file[300];

	SetCurrentDirectory(g_szExePath);
	memset(&SI, 0, sizeof(SI));
	SI.cb = sizeof(SI);
	sprintf_s(m_file, "%s-%s.exe", pDoc->m_CurPartInfo.m_TesterNo,pDoc->m_CurPartInfo.m_TesterName);
	CreateProcess(NULL,m_file,NULL,NULL,FALSE,0,NULL,NULL,&SI,&PI) ;  
	//CreateProcess(NULL,m_file,NULL,NULL,TRUE,CREATE_NEW_PROCESS_GROUP|CREATE_DEFAULT_ERROR_MODE,NULL,NULL,&SI,&PI);
	WaitForSingleObject(PI.hProcess,INFINITE);

}

//当前任务设置
void CMainFrame::OnSettingNow() 
{
	// TODO: Add your command handler code here
	CTaskControlDoc* pDoc = (CTaskControlDoc*)GetActiveDocument();
	if(pDoc->m_CurTaskCount<1)
	{
		MessageBox("没有设置，采用系统默认的设置！");
	}
	pDoc->NewSetting();
	char m_FileName[30];
	strcpy_s(m_FileName, 30, "Settings\\TaskSetting.set");
   	ReadSetting(m_FileName);
	if (NULL == theApp.SwitchView(SELECT))
		return;
    pDoc->UpdateAllViews(NULL,1);
}

//当前被试者信息
void CMainFrame::OnTesterNow() 
{
	// TODO: Add your command handler code here
	CTaskControlDoc* pDoc = (CTaskControlDoc*)GetActiveDocument();
	if(strcmp(pDoc->m_CurPartInfo.m_TesterNo,"")==0)
	{
		MessageBox("没有设置，采用系统默认的设置！");
	}

	if (NULL == theApp.SwitchView(TESTER))
		return;

	pDoc->m_PartInfo = pDoc->m_CurPartInfo;
   	pDoc->UpdateAllViews(NULL,1);
}

/*void CMainFrame::OnFullScreen()
{
	GetWindowPlacement(&m_OldWndPlacement);
	CRect WindowRect;
	GetWindowRect(&WindowRect);
	CRect ClientRect;
	RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, reposQuery, &ClientRect);
	ClientToScreen(&ClientRect);
	//获取屏幕的分辨率
	int nFullWidth=GetSystemMetrics(SM_CXSCREEN);
	int nFullHeight=GetSystemMetrics(SM_CYSCREEN);
	//将除控制条外的客户区全屏显示到从(0,0)到(nFullWidth, nFullHeight)区
	//域, 将(0,0)和(nFullWidth, nFullHeight)两个点外扩充原窗口和除控制条之外的 客
	//户区位置间的差值, 就得到全屏显示的窗口位置
	m_FullScreenRect.left=WindowRect.left-ClientRect.left;
	m_FullScreenRect.top=WindowRect.top-ClientRect.top;
	m_FullScreenRect.right=WindowRect.right-ClientRect.right+nFullWidth;
	m_FullScreenRect.bottom=WindowRect.bottom-ClientRect.bottom+nFullHeight;
	m_bFullScreen=TRUE; //设置全屏显示标志为 TRUE
	//进入全屏显示状态
	WINDOWPLACEMENT wndpl;
	wndpl.length=sizeof(WINDOWPLACEMENT);
	wndpl.flags=0;
	wndpl.showCmd=SW_SHOWNORMAL;
	wndpl.rcNormalPosition=m_FullScreenRect;
	SetWindowPlacement(&wndpl);
}*/


void CMainFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// TODO: Add your message handler code here and/or call default
/*    if(m_bFullScreen)
	{
		lpMMI->ptMaxSize.x=m_FullScreenRect.Width();
        lpMMI->ptMaxSize.y=m_FullScreenRect.Height();
		lpMMI->ptMaxPosition.x=m_FullScreenRect.Width();
		lpMMI->ptMaxPosition.y=m_FullScreenRect.Height();
		//最大的Track尺寸也要改变
		lpMMI->ptMaxTrackSize.x=m_FullScreenRect.Width();
		lpMMI->ptMaxTrackSize.y=m_FullScreenRect.Height();
	}*/
	CFrameWnd::OnGetMinMaxInfo(lpMMI);
}

UINT MyThread(LPVOID pParam)//注意返回类型为UINT
{
	MYDATA* pInfo=(MYDATA*)pParam;
	CMainFrame* pMain =(CMainFrame*)theApp.m_pMainWnd;
	pMain->OnThread(pInfo->pDoc);
	CString m_FileName;
	return 0;
}

//数据批处理
void CMainFrame::OnBatch() 
{
	// TODO: Add your command handler code here
	CTaskControlDoc* pDoc = (CTaskControlDoc*)GetActiveDocument();
	HANDLE m_pMyThread;
	DWORD ThreadID;
	MyThreadData.pDoc = pDoc;
    m_pMyThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)MyThread,&MyThreadData,0,&ThreadID);
}

void CMainFrame::OnThread(CTaskControlDoc* pDoc) 
{
	CString m_FileName;
//	CFileDialog Dlg(TRUE,"(*.txt)|*.txt","*.txt",OFN_ALLOWMULTISELECT|OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"Result Files (*.txt)",this); 

	CFileDialog Dlg(TRUE,NULL,NULL,OFN_ALLOWMULTISELECT|OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"Result Files (*.txt)|*.txt||",this); 
    DWORD nBufferLength=256; 
	char lpBuffer[256];  
//	char lpSaveBuffer[256];

	GetCurrentDirectory(nBufferLength,lpBuffer);
//	sprintf(lpSaveBuffer,"%s\\PartInfo",lpBuffer);
	Dlg.m_ofn.lpstrInitialDir="Data";
	CString str;
	Dlg.m_ofn.lpstrFile=str.GetBuffer(20000);
	Dlg.m_ofn.nMaxFile =20000;
	str.ReleaseBuffer(); 
	if(Dlg.DoModal()==IDOK)
	{
		pDoc->bBatch = TRUE;
		SetCurrentDirectory(lpBuffer);		
		POSITION selpos;
		selpos=Dlg.GetStartPosition();
		int i=0;
		while(selpos!=NULL)
		{
		    m_FileName=Dlg.GetNextPathName(selpos);		
			i++;
		}
		SendMessage(WM_UPDATEDATA, i, 0);//向主线程发送消息更新进度条
		selpos=Dlg.GetStartPosition();
		int pos;
		i=0;
		while(selpos!=NULL)
		{
			m_FileName=Dlg.GetNextPathName(selpos);				
			//m_FileName = Dlg.GetPathName();
    		pos = m_FileName.ReverseFind('\\');
			if(m_FileName.Mid(pos+1,1)!="T")
			{
	   			MessageBox("数据文件格式有误！");
				return;
			}
			pDoc->m_FileName = m_FileName;	

			if(pDoc->ReadDataFile())
			{
				pDoc->DataAnalysis();
			}
			i++;
			SendMessage(WM_UPDATEDATA, i, 1);//向主线程发送消息更新进度条
		}
//		AfxMessageBox("数据批处理完毕！");
		SendMessage(WM_UPDATEDATA, i, 2);//向主线程发送消息更新进度条
	}
}

LRESULT CMainFrame::OnUpdateData(WPARAM wParam, LPARAM lParam)
{
	switch((int)lParam)
	{
	case 0:
		pDlg = new CProcessDlg; 
		pDlg->Create();
		pDlg->SetWindowPos(&wndTopMost,300,300,NULL,NULL,SWP_NOSIZE);
		pDlg->GetDlgItem(IDC_OK)->EnableWindow(FALSE);
		pDlg->m_Progress.SetRange(0,(int)wParam);
		break;
	case 1:
	    pDlg->m_Progress.SetPos((int)wParam);
		break;
	case 2:
		pDlg->GetDlgItem(IDC_TEXT)->SetWindowText("数据批处理完毕！");
		pDlg->GetDlgItem(IDC_OK)->EnableWindow(TRUE);
//		pDlg->DestroyWindow();
		break;
	}
    return 0;
}


