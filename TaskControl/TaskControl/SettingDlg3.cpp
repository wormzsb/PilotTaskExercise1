// SettingDlg3.cpp : implementation file
//

#include "stdafx.h"
#include "TaskControl.h"
#include "SettingDlg3.h"
#include "MainFrm.h"
#include "TaskControlDoc.h"
//#include "..\..\all\Datatype.h"
//#include "..\..\all\Enum.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CSettingDlg3 dialog


CSettingDlg3::CSettingDlg3(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingDlg3::IDD, pParent)
	, m_iJoyMoveDirection(0)
	, m_bLeftTop(TRUE)
	, m_bRightTop(TRUE)
	, m_bRightBottom(TRUE)
	, m_bLeftBottom(TRUE)
	, m_bDirection(FALSE)
	, m_bSpeedMode(FALSE)
	, m_fSpeed(0)
	, m_fSpeedMin(0)
	, m_fSpeedMax(0)
	, m_fAccMin(0)
	, m_fAccMax(0)
	, m_iPlane(0)
	, m_iHelicopter(0)
	, m_iExpTimes(0)
	, m_iReactTime(0)
	, m_iInterMin(0)
	, m_iInterMax(0)
	, m_iPresentTime(0)
{
	//{{AFX_DATA_INIT(CSettingDlg3)
	m_CodePairMode = -1;
	m_PracMode = FALSE;
	m_ExperMode = FALSE;

	m_EventMode = -1;
	m_DisplayMode = -1;
	m_MainTask = FALSE;
	m_SubTask = FALSE;
	m_PracTime = _T("");
	m_ExperTime = _T("");
	m_ExperTimes = _T("");
	m_PracTimes = _T("");
	m_CodePairNum = _T("");
	m_MainTaskMode = -1;
	m_EventFrequency = 0;
	m_TaskName = _T("");
	//}}AFX_DATA_INIT
}


void CSettingDlg3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingDlg3)
	DDX_Control(pDX, IDC_BACKGROUND, m_Background);
	DDX_Check(pDX, IDC_PRACMODE, m_PracMode);
	DDX_Text(pDX, IDC_INITSPEED, m_fInitSpeed);
	DDX_Radio(pDX, IDC_EVENTMODE0, m_EventMode);
	DDX_Check(pDX, IDC_MAINTASK, m_MainTask);
	DDX_Check(pDX, IDC_SUBTASK, m_SubTask);	
	DDX_Text(pDX, IDC_TASKNAME, m_TaskName);
	//}}AFX_DATA_MAP
	DDX_Radio(pDX, IDC_JOY_MOVE_POS, m_iJoyMoveDirection);
	DDX_Check(pDX, IDC_LEFTTOP, m_bLeftTop);
	DDX_Check(pDX, IDC_IDC_RIGHTTOP, m_bRightTop);
	DDX_Check(pDX, IDC_RIGHTBOTTOM, m_bRightBottom);
	DDX_Check(pDX, IDC_LEFTBOTTOM, m_bLeftBottom);
	DDX_Radio(pDX, IDC_DIRECTION0, m_bDirection);
	DDX_Radio(pDX, IDC_SPEEDMODE0, m_bSpeedMode);
	DDX_Text(pDX, IDC_SPEED, m_fSpeed);
	DDX_Text(pDX, IDC_SPEEDMIN, m_fSpeedMin);
	DDX_Text(pDX, IDC_SPEEDMAX3, m_fSpeedMax);
	DDX_Text(pDX, IDC_ACCELERATIONMIN, m_fAccMin);
	DDX_Text(pDX, IDC_ACCELERATIONMAX, m_fAccMax);
	DDX_Control(pDX, IDC_TRACK, m_ccbTrack);
	DDX_Text(pDX, IDC_EVENTFREQUENCY2, m_iPlane);
	DDX_Text(pDX, IDC_EVENTFREQUENCY3, m_iHelicopter);
	DDX_Text(pDX, IDC_PRACTIME2, m_iExpTimes);
	DDX_Text(pDX, IDC_PRACTIME3, m_iPresentTime);
	DDX_Text(pDX, IDC_PRACTIME4, m_iReactTime);
	DDX_Text(pDX, IDC_INTER_MIN, m_iInterMin);
	DDX_Text(pDX, IDC_INTER_MAX, m_iInterMax);
}


BEGIN_MESSAGE_MAP(CSettingDlg3, CDialog)
	//{{AFX_MSG_MAP(CSettingDlg3)
	ON_BN_CLICKED(IDC_PRACMODE, OnPracmode)
	ON_BN_CLICKED(IDC_EXPERMODE, OnExpermode)
	ON_BN_CLICKED(IDC_MAINTASK, OnMaintask)
	ON_BN_CLICKED(IDC_SUBTASK, OnSubtask)
	ON_BN_CLICKED(IDC_CODEPAIRMODE0, OnCodepairmode0)
	ON_BN_CLICKED(IDC_CODEPAIRMODE1, OnCodepairmode1)
	ON_BN_CLICKED(IDC_MAINTASKMODE0, OnMaintaskmode0)
	ON_BN_CLICKED(IDC_MAINTASKMODE1, OnMaintaskmode1)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_DISPLAYMODE1, &CSettingDlg3::OnBnClickedDisplaymode1)

	ON_EN_CHANGE(IDC_TASKNAME, &CSettingDlg3::OnEnChangeTaskname)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_SPEEDMODE0, &CSettingDlg3::OnBnClickedSpeedmode0)
	ON_BN_CLICKED(IDC_SPEEDMODE1, &CSettingDlg3::OnBnClickedSpeedmode1)
//	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_EVENTMODE0, &CSettingDlg3::OnBnHotItemChangeEventmode0)
	ON_BN_CLICKED(IDC_EVENTMODE0, &CSettingDlg3::OnBnClickedEventmode0)
	ON_BN_CLICKED(IDC_EVENTMODE1, &CSettingDlg3::OnBnClickedEventmode1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg3 message handlers

BOOL CSettingDlg3::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
    CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();
	m_bLeftTop =  pDoc->m_Setting3[m_DlgIdx].m_iPlanePos & LEFT_TOP ;
	m_bRightTop =  (pDoc->m_Setting3[m_DlgIdx].m_iPlanePos & RIGHT_TOP) >> 1;
	m_bLeftBottom =  (pDoc->m_Setting3[m_DlgIdx].m_iPlanePos & LEFT_BOTTOM) >> 3;
	m_bRightBottom =  (pDoc->m_Setting3[m_DlgIdx].m_iPlanePos & RIGHT_BOTTOM) >> 2;
	m_iPlane = pDoc->m_Setting3[m_DlgIdx].m_iPlane;
	m_iHelicopter = pDoc->m_Setting3[m_DlgIdx].m_iHelicopter;
	m_iJoyMoveDirection = pDoc->m_Setting3[m_DlgIdx].m_iJoyMoveDirection;
	m_bDirection = pDoc->m_Setting3[m_DlgIdx].m_Direction;
	m_bSpeedMode = pDoc->m_Setting3[m_DlgIdx].m_SpeedMode;
	m_fSpeed = pDoc->m_Setting3[m_DlgIdx].m_Speed;
	m_fInitSpeed = pDoc->m_Setting3[m_DlgIdx].m_InitSpeed;
	m_fSpeedMin = pDoc->m_Setting3[m_DlgIdx].m_SpeedMin;
	m_fSpeedMax = pDoc->m_Setting3[m_DlgIdx].m_SpeedMax;
	m_fAccMin = pDoc->m_Setting3[m_DlgIdx].m_AccelerationMin;
	m_fAccMax = pDoc->m_Setting3[m_DlgIdx].m_AccelerationMax;
	
	m_iPresentTime = pDoc->m_Setting3[m_DlgIdx].m_iPresentTime;
	m_iReactTime = pDoc->m_Setting3[m_DlgIdx].m_iReactTime;
	m_iInterMin = pDoc->m_Setting3[m_DlgIdx].m_iIntervalMin;
	m_iInterMax = pDoc->m_Setting3[m_DlgIdx].m_iIntervalMax; 
	m_iExpTimes = pDoc->m_Setting3[m_DlgIdx].m_ExperTimes;

	m_ccbTrack.AddString("圆形");
	m_ccbTrack.AddString("横8字形");
	m_ccbTrack.SetCurSel(pDoc->m_Setting3[m_DlgIdx].m_iTrack);

	m_TaskName = pDoc->m_Setting3[m_DlgIdx].m_TaskName;
	m_PracMode = pDoc->m_Setting3[m_DlgIdx].m_PracMode;
    m_ExperMode = pDoc->m_Setting3[m_DlgIdx].m_ExperMode;
	m_MainTask = pDoc->m_Setting3[m_DlgIdx].m_MainTask;
    m_SubTask = pDoc->m_Setting3[m_DlgIdx].m_SubTask;
	m_MainTaskMode = pDoc->m_Setting3[m_DlgIdx].m_MainTaskMode;
    
	m_Background.InsertString(0,"灰黑色");
	m_Background.InsertString(1,"蓝黑色");
    m_Background.SetCurSel(pDoc->m_Setting3[m_DlgIdx].m_Background);


	m_EventMode = pDoc->m_Setting3[m_DlgIdx].m_EventMode;
	m_CodePairMode = pDoc->m_Setting3[m_DlgIdx].m_CodePairMode;


 	m_DisplayMode = pDoc->m_Setting3[m_DlgIdx].m_DisplayMode;
	m_EventFrequency =  pDoc->m_Setting3[m_DlgIdx].m_EventFrequency;
	m_PracTime.Format("%d", pDoc->m_Setting3[m_DlgIdx].m_PracTime);
	m_ExperTime.Format("%d", pDoc->m_Setting3[m_DlgIdx].m_ExperTime);
    m_PracTimes.Format("%d", pDoc->m_Setting3[m_DlgIdx].m_PracTimes);
	m_ExperTimes.Format("%d", pDoc->m_Setting3[m_DlgIdx].m_ExperTimes);
	

	// 初始化速度设置的enable和disable
	GetDlgItem(IDC_SPEEDSTATIC)->EnableWindow(!pDoc->m_Setting3[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_SPEED)->EnableWindow(!pDoc->m_Setting3[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_SPEEDUNITSTATIC4)->EnableWindow(!pDoc->m_Setting3[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_INITSPEEDSTATIC3)->EnableWindow(pDoc->m_Setting3[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_INITSPEED)->EnableWindow(pDoc->m_Setting3[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_INITSPEEDUNITSTATIC)->EnableWindow(pDoc->m_Setting3[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_SPEEDMAXSTATIC)->EnableWindow(pDoc->m_Setting3[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_SPEEDMIN)->EnableWindow(pDoc->m_Setting3[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_SPEEDMIDSTATIC)->EnableWindow(pDoc->m_Setting3[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_SPEEDMAX3)->EnableWindow(pDoc->m_Setting3[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_SPEEDMAXUNITSTATIC)->EnableWindow(pDoc->m_Setting3[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_ACCELERATIONSTATIC)->EnableWindow(pDoc->m_Setting3[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_ACCELERATIONMIN)->EnableWindow(pDoc->m_Setting3[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_ACCELERATIONMIDSTATIC)->EnableWindow(pDoc->m_Setting3[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_ACCELERATIONMAX)->EnableWindow(pDoc->m_Setting3[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_ACCELERATIONUNITSTATIC2)->EnableWindow(pDoc->m_Setting3[m_DlgIdx].m_SpeedMode);

	// 简单任务 vs 选择任务
	GetDlgItem(IDC_EVENTFREQUENCY2)->EnableWindow(pDoc->m_Setting3[m_DlgIdx].m_EventMode);
	GetDlgItem(IDC_EVENTFREQUENCY3)->EnableWindow(pDoc->m_Setting3[m_DlgIdx].m_EventMode);

	UpdateData(FALSE);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSettingDlg3::Save() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
    CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();
	pDoc->m_Setting3[m_DlgIdx].m_iPlanePos = m_bLeftTop * LEFT_TOP;
	pDoc->m_Setting3[m_DlgIdx].m_iPlanePos += m_bRightTop * RIGHT_TOP ;
	pDoc->m_Setting3[m_DlgIdx].m_iPlanePos += m_bLeftBottom * LEFT_BOTTOM;
	pDoc->m_Setting3[m_DlgIdx].m_iPlanePos += m_bRightBottom * RIGHT_BOTTOM;
	pDoc->m_Setting3[m_DlgIdx].m_iPlane = m_iPlane;
	pDoc->m_Setting3[m_DlgIdx].m_iHelicopter = m_iHelicopter;

	pDoc->m_Setting3[m_DlgIdx].m_iJoyMoveDirection = m_iJoyMoveDirection ;
	strcpy_s(pDoc->m_Setting3[m_DlgIdx].m_TaskName,100, m_TaskName);

	pDoc->m_Setting3[m_DlgIdx].m_Direction = m_bDirection;
	pDoc->m_Setting3[m_DlgIdx].m_SpeedMode = m_bSpeedMode;
	pDoc->m_Setting3[m_DlgIdx].m_Speed = m_fSpeed;
	pDoc->m_Setting3[m_DlgIdx].m_InitSpeed = m_fInitSpeed;
	pDoc->m_Setting3[m_DlgIdx].m_SpeedMin = m_fSpeedMin;
	pDoc->m_Setting3[m_DlgIdx].m_SpeedMax = m_fSpeedMax;
	pDoc->m_Setting3[m_DlgIdx].m_AccelerationMin = m_fAccMin;
	pDoc->m_Setting3[m_DlgIdx].m_AccelerationMax = m_fAccMax;
	pDoc->m_Setting3[m_DlgIdx].m_ExperTimes =m_iExpTimes;
	pDoc->m_Setting3[m_DlgIdx].m_iPresentTime = m_iPresentTime; 
	pDoc->m_Setting3[m_DlgIdx].m_iReactTime = m_iReactTime;
	pDoc->m_Setting3[m_DlgIdx].m_iIntervalMin = m_iInterMin;
	pDoc->m_Setting3[m_DlgIdx].m_iIntervalMax = m_iInterMax; 
	

	pDoc->m_Setting3[m_DlgIdx].m_iTrack = m_ccbTrack.GetCurSel();


	//若需要显示反馈
	if (m_PracMode)
	{
		pDoc->m_Setting3[m_DlgIdx].m_PracMode = 1;
		pDoc->m_Setting3[m_DlgIdx].m_ExperMode = 0;
	}
	else
	{
		pDoc->m_Setting3[m_DlgIdx].m_PracMode = 0;
		pDoc->m_Setting3[m_DlgIdx].m_ExperMode = 1;
	}
 
	pDoc->m_Setting3[m_DlgIdx].m_PracTime = atoi(m_PracTime);
	pDoc->m_Setting3[m_DlgIdx].m_ExperTime = atoi(m_PracTime);
	pDoc->m_Setting3[m_DlgIdx].m_MainTask = m_MainTask;
    pDoc->m_Setting3[m_DlgIdx].m_SubTask = m_SubTask;
	if(pDoc->m_Setting3[m_DlgIdx].m_MainTask)
	{
		pDoc->m_Setting3[m_DlgIdx].m_MainTaskMode = m_MainTaskMode;
	}
	else
	{
        pDoc->m_Setting3[m_DlgIdx].m_MainTaskMode = -1;
	}
	pDoc->m_Setting3[m_DlgIdx].m_Background = m_Background.GetCurSel();



	
	pDoc->m_Setting3[m_DlgIdx].m_EventMode = m_EventMode;
	if(pDoc->m_Setting3[m_DlgIdx].m_MainTaskMode&&pDoc->m_Setting3[m_DlgIdx].m_MainTask)
	{
		pDoc->m_Setting3[m_DlgIdx].m_CodePairMode = m_CodePairMode;
	}
	else
	{
        pDoc->m_Setting3[m_DlgIdx].m_CodePairMode = -1;
	}
    if((!pDoc->m_Setting3[m_DlgIdx].m_CodePairMode)&&pDoc->m_Setting3[m_DlgIdx].m_MainTaskMode&&pDoc->m_Setting3[m_DlgIdx].m_MainTask)
	{
		pDoc->m_Setting3[m_DlgIdx].m_CodePairNum = atoi(m_CodePairNum);
	}
	else
	{
        pDoc->m_Setting3[m_DlgIdx].m_CodePairNum = -1;
	}
	if(pDoc->m_Setting3[m_DlgIdx].m_MainTaskMode&&pDoc->m_Setting3[m_DlgIdx].m_MainTask)
	{
		pDoc->m_Setting3[m_DlgIdx].m_DisplayMode = m_DisplayMode;
	}
	else
	{
        pDoc->m_Setting3[m_DlgIdx].m_DisplayMode = -1;
	}
	
	pDoc->m_Setting3[m_DlgIdx].m_EventFrequency = m_EventFrequency;
	
	
}

void CSettingDlg3::OnPracmode() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
}

void CSettingDlg3::OnExpermode() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetDlgItem(IDC_EXPERTIMESTATIC)->EnableWindow(m_MainTask&&m_ExperMode&&!m_SubTask);
	GetDlgItem(IDC_EXPERTIME)->EnableWindow(m_MainTask&&m_ExperMode&&!m_SubTask);
	GetDlgItem(IDC_EXPERTIMEUNITSTATIC)->EnableWindow(m_MainTask&&m_ExperMode&&!m_SubTask);
	GetDlgItem(IDC_EXPERTIMESSTATIC)->EnableWindow(m_SubTask&&m_ExperMode);
	GetDlgItem(IDC_EXPERTIMES)->EnableWindow(m_SubTask&&m_ExperMode);	
}

void CSettingDlg3::OnMaintask() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
}

void CSettingDlg3::OnSubtask() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);	
	GetDlgItem(IDC_SUBTASKSTATIC)->EnableWindow(m_SubTask);
	GetDlgItem(IDC_EVENTMODE0)->EnableWindow(m_SubTask);
	GetDlgItem(IDC_EVENTMODE1)->EnableWindow(m_SubTask);
    GetDlgItem(IDC_EVENTMODESTATIC)->EnableWindow(m_SubTask);
    GetDlgItem(IDC_EVENTFREQUENCYSTATIC)->EnableWindow(m_SubTask);
	GetDlgItem(IDC_EVENTFREQUENCY)->EnableWindow(m_SubTask);
	GetDlgItem(IDC_EVENTFREQUENCYUNIT)->EnableWindow(m_SubTask);
}

void CSettingDlg3::OnCodepairmode0() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetDlgItem(IDC_CODEPAIRNUM)->EnableWindow((!m_CodePairMode)&&m_MainTaskMode&&m_MainTask);	
}

void CSettingDlg3::OnCodepairmode1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetDlgItem(IDC_CODEPAIRNUM)->EnableWindow((!m_CodePairMode)&&m_MainTaskMode&&m_MainTask);	
	
}

void CSettingDlg3::OnMaintaskmode0() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetDlgItem(IDC_INITSPEEDSTATIC)->EnableWindow((!m_MainTaskMode)&&m_MainTask);
	GetDlgItem(IDC_INITSPEED)->EnableWindow((!m_MainTaskMode)&&m_MainTask);
	GetDlgItem(IDC_SPEEDUNITSTATIC)->EnableWindow((!m_MainTaskMode)&&m_MainTask);
	GetDlgItem(IDC_PRACTIMESTATIC)->EnableWindow((!m_MainTaskMode)&&m_MainTask&&m_PracMode);
	GetDlgItem(IDC_PRACTIME)->EnableWindow((!m_MainTaskMode)&&m_MainTask&&m_PracMode);
	GetDlgItem(IDC_PRACTIMEUNITSTATIC)->EnableWindow((!m_MainTaskMode)&&m_MainTask&&m_PracMode);
	GetDlgItem(IDC_EXPERTIMESTATIC)->EnableWindow((!m_MainTaskMode)&&m_MainTask&&m_ExperMode);
	GetDlgItem(IDC_EXPERTIME)->EnableWindow((!m_MainTaskMode)&&m_MainTask&&m_ExperMode);
	GetDlgItem(IDC_EXPERTIMEUNITSTATIC)->EnableWindow((!m_MainTaskMode)&&m_MainTask&&m_ExperMode);

	GetDlgItem(IDC_CODEPAIRMODESTATIC)->EnableWindow(m_MainTaskMode&&m_MainTask);
	GetDlgItem(IDC_CODEPAIRMODE0)->EnableWindow(m_MainTaskMode&&m_MainTask);
	GetDlgItem(IDC_CODEPAIRNUM)->EnableWindow((!m_CodePairMode)&&m_MainTaskMode&&m_MainTask);	
	GetDlgItem(IDC_CODEPAIRMODE1)->EnableWindow(m_MainTaskMode&&m_MainTask);
	GetDlgItem(IDC_DISPLAYMODESTATIC)->EnableWindow(m_MainTaskMode&&m_MainTask);
	GetDlgItem(IDC_DISPLAYMODE0)->EnableWindow(m_MainTaskMode&&m_MainTask);
	GetDlgItem(IDC_DISPLAYMODE1)->EnableWindow(m_MainTaskMode&&m_MainTask);	
	GetDlgItem(IDC_PRACTIMESSTATIC)->EnableWindow(m_MainTaskMode&&m_MainTask);
	GetDlgItem(IDC_PRACTIMES)->EnableWindow(m_MainTaskMode&&m_MainTask);
	GetDlgItem(IDC_EXPERTIMESSTATIC)->EnableWindow(m_MainTaskMode&&m_MainTask);
	GetDlgItem(IDC_EXPERTIMES)->EnableWindow(m_MainTaskMode&&m_MainTask);	
}

void CSettingDlg3::OnMaintaskmode1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetDlgItem(IDC_INITSPEEDSTATIC)->EnableWindow((!m_MainTaskMode)&&m_MainTask);
	GetDlgItem(IDC_INITSPEED)->EnableWindow((!m_MainTaskMode)&&m_MainTask);
	GetDlgItem(IDC_SPEEDUNITSTATIC)->EnableWindow((!m_MainTaskMode)&&m_MainTask);
	GetDlgItem(IDC_PRACTIMESTATIC)->EnableWindow((!m_MainTaskMode)&&m_MainTask&&m_PracMode);
	GetDlgItem(IDC_PRACTIME)->EnableWindow((!m_MainTaskMode)&&m_MainTask&&m_PracMode);
	GetDlgItem(IDC_PRACTIMEUNITSTATIC)->EnableWindow((!m_MainTaskMode)&&m_MainTask&&m_PracMode);
	GetDlgItem(IDC_EXPERTIMESTATIC)->EnableWindow((!m_MainTaskMode)&&m_MainTask&&m_ExperMode);
	GetDlgItem(IDC_EXPERTIME)->EnableWindow((!m_MainTaskMode)&&m_MainTask&&m_ExperMode);
    GetDlgItem(IDC_EXPERTIMEUNITSTATIC)->EnableWindow((!m_MainTaskMode)&&m_MainTask&&m_ExperMode);
	
	GetDlgItem(IDC_CODEPAIRMODESTATIC)->EnableWindow(m_MainTaskMode&&m_MainTask);
	GetDlgItem(IDC_CODEPAIRMODE0)->EnableWindow(m_MainTaskMode&&m_MainTask);
	GetDlgItem(IDC_CODEPAIRNUM)->EnableWindow((!m_CodePairMode)&&m_MainTaskMode&&m_MainTask);	
	GetDlgItem(IDC_CODEPAIRMODE1)->EnableWindow(m_MainTaskMode&&m_MainTask);
	GetDlgItem(IDC_DISPLAYMODESTATIC)->EnableWindow(m_MainTaskMode&&m_MainTask);
	GetDlgItem(IDC_DISPLAYMODE0)->EnableWindow(m_MainTaskMode&&m_MainTask);
	GetDlgItem(IDC_DISPLAYMODE1)->EnableWindow(m_MainTaskMode&&m_MainTask);		
	GetDlgItem(IDC_PRACTIMESSTATIC)->EnableWindow(m_MainTaskMode&&m_MainTask);
	GetDlgItem(IDC_PRACTIMES)->EnableWindow(m_MainTaskMode&&m_MainTask);
	GetDlgItem(IDC_EXPERTIMESSTATIC)->EnableWindow(m_MainTaskMode&&m_MainTask);
	GetDlgItem(IDC_EXPERTIMES)->EnableWindow(m_MainTaskMode&&m_MainTask);	
}


void CSettingDlg3::OnBnClickedDisplaymode1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CSettingDlg3::OnEnChangePractime3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。


	// TODO:  在此添加控件通知处理程序代码
}


void CSettingDlg3::OnEnChangePractime4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。



	// TODO:  在此添加控件通知处理程序代码
}


void CSettingDlg3::OnEnChangePractime5()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。



	// TODO:  在此添加控件通知处理程序代码
}


void CSettingDlg3::OnEnChangeTaskname()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。



	// TODO:  在此添加控件通知处理程序代码
}


HBRUSH CSettingDlg3::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_EDIT){
		pDC->SetBkColor(RGB(255,255,255));
	}
	return hbr;
}


void CSettingDlg3::OnBnClickedSpeedmode0()
{
	// TODO: Add your control notification handler code here

	// 初始化速度设置的enable和disable
	UpdateData(TRUE);
	GetDlgItem(IDC_SPEEDSTATIC)->EnableWindow(!m_bSpeedMode);
	GetDlgItem(IDC_SPEED)->EnableWindow(!m_bSpeedMode);
	GetDlgItem(IDC_SPEEDUNITSTATIC4)->EnableWindow(!m_bSpeedMode);
	GetDlgItem(IDC_INITSPEEDSTATIC3)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_INITSPEED)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_INITSPEEDUNITSTATIC)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_SPEEDMAXSTATIC)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_SPEEDMIN)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_SPEEDMIDSTATIC)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_SPEEDMAX3)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_SPEEDMAXUNITSTATIC)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_ACCELERATIONSTATIC)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_ACCELERATIONMIN)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_ACCELERATIONMIDSTATIC)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_ACCELERATIONMAX)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_ACCELERATIONUNITSTATIC2)->EnableWindow(m_bSpeedMode);

}


void CSettingDlg3::OnBnClickedSpeedmode1()
{
	// TODO: Add your control notification handler code here
	// 初始化速度设置的enable和disable
	UpdateData(TRUE);
	GetDlgItem(IDC_SPEEDSTATIC)->EnableWindow(!m_bSpeedMode);
	GetDlgItem(IDC_SPEED)->EnableWindow(!m_bSpeedMode);
	GetDlgItem(IDC_SPEEDUNITSTATIC4)->EnableWindow(!m_bSpeedMode);
	GetDlgItem(IDC_INITSPEEDSTATIC3)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_INITSPEED)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_INITSPEEDUNITSTATIC)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_SPEEDMAXSTATIC)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_SPEEDMIN)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_SPEEDMIDSTATIC)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_SPEEDMAX3)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_SPEEDMAXUNITSTATIC)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_ACCELERATIONSTATIC)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_ACCELERATIONMIN)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_ACCELERATIONMIDSTATIC)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_ACCELERATIONMAX)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_ACCELERATIONUNITSTATIC2)->EnableWindow(m_bSpeedMode);

}


//void CSettingDlg3::OnBnHotItemChangeEventmode0(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	// This feature requires Internet Explorer 6 or greater.
//	// The symbol _WIN32_IE must be >= 0x0600.
//	LPNMBCHOTITEM pHotItem = reinterpret_cast<LPNMBCHOTITEM>(pNMHDR);
//	// TODO: Add your control notification handler code here
//	*pResult = 0;
//}


void CSettingDlg3::OnBnClickedEventmode0()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	// 简单任务 vs 选择任务
	GetDlgItem(IDC_EVENTFREQUENCY2)->EnableWindow(m_EventMode);
	GetDlgItem(IDC_EVENTFREQUENCY3)->EnableWindow(m_EventMode);
}


void CSettingDlg3::OnBnClickedEventmode1()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	// 简单任务 vs 选择任务
	GetDlgItem(IDC_EVENTFREQUENCY2)->EnableWindow(m_EventMode);
	GetDlgItem(IDC_EVENTFREQUENCY3)->EnableWindow(m_EventMode);
}
