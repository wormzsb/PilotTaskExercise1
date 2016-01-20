// SettingDlg6.cpp : implementation file
//

#include "stdafx.h"
#include "TaskControl.h"
#include "SettingDlg6.h"
#include "MainFrm.h"
#include "TaskControlDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg6 dialog


CSettingDlg6::CSettingDlg6(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingDlg6::IDD, pParent)
	, m_iJoyMoveDirection(0)
	, m_iSubTaskInterval(0)
	, m_iPresentTime(0)
	, m_iReactTime(0)
	, m_iDirection(FALSE)
	, m_bSpeedMode(FALSE)
	, m_fInitSpeed(0)
	, m_fSpeedMin(0)
	, m_fSpeedMax(0)
	, m_fAccMin(0)
	, m_fAccMax(0)
{
	//{{AFX_DATA_INIT(CSettingDlg6)
	m_MemTaskMode = 0;
	m_PracMode = FALSE;
	m_ExperMode = FALSE;
	
	m_MainTask = FALSE;
	m_SubTask = FALSE;
	m_PracTimes = _T("");
	m_ExperTimes = _T("");
	m_ExperTime = _T("");
	m_PracTime = _T("");
	m_CubeNum1 = FALSE;
	m_CubeNum2 = FALSE;
	m_CubeNum3 = FALSE;
	m_CubeNum4 = FALSE;
	m_Prototype = -1;
	m_RefAxis = -1;
	m_TaskName = _T("");
	//}}AFX_DATA_INIT
}


void CSettingDlg6::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingDlg6)
	DDX_Control(pDX, IDC_BACKGROUND, m_Background);
	DDX_Radio(pDX, IDC_MEMTASKMODE0, m_MemTaskMode);
	DDX_Check(pDX, IDC_PRACMODE, m_PracMode);

	DDX_Text(pDX, IDC_INITSPEED, m_fSpeed);
	DDX_Check(pDX, IDC_MAINTASK, m_MainTask);
	DDX_Check(pDX, IDC_SUBTASK, m_SubTask);
	DDX_Text(pDX, IDC_PRACTIMES, m_PracTimes);
	//DDX_Text(pDX, IDC_EXPERTIMES, m_ExperTimes);
	//DDX_CBString(pDX, IDC_EXPERTIME, m_ExperTime);
	//DDX_CBString(pDX, IDC_PRACTIME, m_PracTime);
	DDX_Check(pDX, IDC_CUBENUM1, m_CubeNum1);
	DDX_Check(pDX, IDC_CUBENUM2, m_CubeNum2);
	DDX_Check(pDX, IDC_CUBENUM3, m_CubeNum3);
	DDX_Check(pDX, IDC_CUBENUM4, m_CubeNum4);
	DDX_Radio(pDX, IDC_PROTOTYPE1, m_Prototype);
	DDX_Radio(pDX, IDC_REFAXIS1, m_RefAxis);
	DDX_Text(pDX, IDC_TASKNAME, m_TaskName);
	//}}AFX_DATA_MAP
	DDX_Radio(pDX, IDC_JOY_MOVE_POS, m_iJoyMoveDirection);

	DDX_Text(pDX, IDC_SUBTASK_INTERVAL, m_iSubTaskInterval);
	DDX_Text(pDX, IDC_PRESENT_TIME, m_iPresentTime);
	DDX_Text(pDX, IDC_REACT_TIME, m_iReactTime);
	DDX_Radio(pDX, IDC_DIRECTION0, m_iDirection);
	DDX_Radio(pDX, IDC_SPEEDMODE0, m_bSpeedMode);
	DDX_Text(pDX, IDC_INITSPEED2, m_fInitSpeed);
	DDX_Text(pDX, IDC_SPEEDMIN, m_fSpeedMin);
	DDX_Text(pDX, IDC_SPEEDMAX4, m_fSpeedMax);
	DDX_Text(pDX, IDC_ACCELERATIONMIN, m_fAccMin);
	DDX_Text(pDX, IDC_ACCELERATIONMAX, m_fAccMax);
}


BEGIN_MESSAGE_MAP(CSettingDlg6, CDialog)
	//{{AFX_MSG_MAP(CSettingDlg6)
	ON_BN_CLICKED(IDC_MAINTASK, OnMaintask)
	ON_BN_CLICKED(IDC_SUBTASK, OnSubtask)
	ON_BN_CLICKED(IDC_PRACMODE, OnPracmode)
	ON_BN_CLICKED(IDC_EXPERMODE, OnExpermode)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_JOY_MOVE_POS, &CSettingDlg6::OnBnClickedJoyMovePos)
	ON_STN_CLICKED(IDC_REFAXISSTATIC, &CSettingDlg6::OnStnClickedRefaxisstatic)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_SPEEDMODE0, &CSettingDlg6::OnBnClickedSpeedmode0)
	ON_BN_CLICKED(IDC_SPEEDMODE1, &CSettingDlg6::OnBnClickedSpeedmode1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg6 message handlers

void CSettingDlg6::Save() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
    CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();
	pDoc->m_Setting6[m_DlgIdx].m_iJoyMoveDirection = m_iJoyMoveDirection;
	pDoc->m_Setting6[m_DlgIdx].m_InitSpeed = m_fInitSpeed;
	pDoc->m_Setting6[m_DlgIdx].m_Speed = m_fSpeed;
	pDoc->m_Setting6[m_DlgIdx].m_SpeedMin = m_fSpeedMin;
	pDoc->m_Setting6[m_DlgIdx].m_SpeedMax = m_fSpeedMax;
	pDoc->m_Setting6[m_DlgIdx]. m_AccelerationMin = m_fAccMin;
	pDoc->m_Setting6[m_DlgIdx]. m_AccelerationMax = m_fAccMax;
	pDoc->m_Setting6[m_DlgIdx].m_Direction = m_iDirection;
	pDoc->m_Setting6[m_DlgIdx].m_SpeedMode = m_bSpeedMode;

	strcpy_s(pDoc->m_Setting6[m_DlgIdx].m_TaskName,100, m_TaskName);

	//若有反馈
	if (m_PracMode)
	{
		pDoc->m_Setting6[m_DlgIdx].m_PracMode = 1;
		pDoc->m_Setting6[m_DlgIdx].m_ExperMode = 0;
	}
	else
	{
		pDoc->m_Setting6[m_DlgIdx].m_PracMode = 0;
		pDoc->m_Setting6[m_DlgIdx].m_ExperMode = 1;	
	}

	pDoc->m_Setting6[m_DlgIdx].m_PracTimes = atoi(m_PracTimes);
	pDoc->m_Setting6[m_DlgIdx].m_ExperTimes =  atoi(m_PracTimes);
  
	pDoc->m_Setting6[m_DlgIdx].m_iSubTaskInterval = m_iSubTaskInterval;
	pDoc->m_Setting6[m_DlgIdx].m_iPresentTime = m_iPresentTime;
	pDoc->m_Setting6[m_DlgIdx].m_iReactTime = m_iReactTime;

	pDoc->m_Setting6[m_DlgIdx].m_MainTask = m_MainTask;
    pDoc->m_Setting6[m_DlgIdx].m_SubTask = m_SubTask;
	pDoc->m_Setting6[m_DlgIdx].m_Background = m_Background.GetCurSel();

	pDoc->m_Setting6[m_DlgIdx].m_InitSpeed = m_fInitSpeed;

	if(pDoc->m_Setting6[m_DlgIdx].m_SubTask)
	{
		pDoc->m_Setting6[m_DlgIdx].m_CubeNum1 = m_CubeNum1;
		pDoc->m_Setting6[m_DlgIdx].m_CubeNum2 = m_CubeNum2;
		pDoc->m_Setting6[m_DlgIdx].m_CubeNum3 = m_CubeNum3;
		pDoc->m_Setting6[m_DlgIdx].m_CubeNum4 = m_CubeNum4;
		pDoc->m_Setting6[m_DlgIdx].m_Prototype = m_Prototype;
		pDoc->m_Setting6[m_DlgIdx].m_RefAxis = m_RefAxis;
		pDoc->m_Setting6[m_DlgIdx].m_MemTaskMode = m_MemTaskMode;
	}
	else
	{
		pDoc->m_Setting6[m_DlgIdx].m_CubeNum1 = -1;
		pDoc->m_Setting6[m_DlgIdx].m_CubeNum2 = -1;
		pDoc->m_Setting6[m_DlgIdx].m_CubeNum3 = -1;
		pDoc->m_Setting6[m_DlgIdx].m_CubeNum4 = -1;
		pDoc->m_Setting6[m_DlgIdx].m_Prototype = -1;
		pDoc->m_Setting6[m_DlgIdx].m_RefAxis = -1;
		pDoc->m_Setting6[m_DlgIdx].m_MemTaskMode = -1;
	}
	
	/*if(pDoc->m_Setting6[m_DlgIdx].m_MainTask&&pDoc->m_Setting6[m_DlgIdx].m_PracMode&&!pDoc->m_Setting6[m_DlgIdx].m_SubTask)
	{
		pDoc->m_Setting6[m_DlgIdx].m_PracTime = atoi(m_PracTime);
	}
	else
	{
    	pDoc->m_Setting6[m_DlgIdx].m_PracTime = -1;
	}
	if(pDoc->m_Setting6[m_DlgIdx].m_MainTask&&pDoc->m_Setting6[m_DlgIdx].m_ExperMode&&!pDoc->m_Setting6[m_DlgIdx].m_SubTask)
	{
		pDoc->m_Setting6[m_DlgIdx].m_ExperTime = atoi(m_ExperTime);
	}
    else
	{
		pDoc->m_Setting6[m_DlgIdx].m_ExperTime = -1;
	}
	if(pDoc->m_Setting6[m_DlgIdx].m_SubTask&&pDoc->m_Setting6[m_DlgIdx].m_PracMode)
	{
		pDoc->m_Setting6[m_DlgIdx].m_PracTimes = atoi(m_PracTimes);
		//pDoc->m_Setting6[m_DlgIdx].m_ExperTimes = atoi(m_ExperTimes);
	}
	else
	{
        pDoc->m_Setting6[m_DlgIdx].m_PracTimes = -1;
	}
	if(pDoc->m_Setting6[m_DlgIdx].m_SubTask&&pDoc->m_Setting6[m_DlgIdx].m_ExperMode)
	{
		pDoc->m_Setting6[m_DlgIdx].m_ExperTimes = atoi(m_ExperTimes);
	}*/
}

BOOL CSettingDlg6::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
    CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();
	m_iJoyMoveDirection = pDoc->m_Setting6[m_DlgIdx].m_iJoyMoveDirection;
	m_TaskName = pDoc->m_Setting6[m_DlgIdx].m_TaskName;
	m_PracMode = pDoc->m_Setting6[m_DlgIdx].m_PracMode;
    m_ExperMode = pDoc->m_Setting6[m_DlgIdx].m_ExperMode;
	m_MainTask = pDoc->m_Setting6[m_DlgIdx].m_MainTask;
    m_SubTask = pDoc->m_Setting6[m_DlgIdx].m_SubTask;
	m_iSubTaskInterval = pDoc->m_Setting6[m_DlgIdx].m_iSubTaskInterval;
	m_iPresentTime = pDoc->m_Setting6[m_DlgIdx].m_iPresentTime;
	m_iReactTime = pDoc->m_Setting6[m_DlgIdx].m_iReactTime;
	m_fInitSpeed = pDoc->m_Setting6[m_DlgIdx].m_InitSpeed;
	m_fSpeed = pDoc->m_Setting6[m_DlgIdx].m_Speed;
	m_fSpeedMin = pDoc->m_Setting6[m_DlgIdx].m_SpeedMin;
	m_fSpeedMax = pDoc->m_Setting6[m_DlgIdx].m_SpeedMax;
	m_fAccMin = pDoc->m_Setting6[m_DlgIdx]. m_AccelerationMin;
	m_fAccMax = pDoc->m_Setting6[m_DlgIdx]. m_AccelerationMax;

	m_Background.InsertString(0,"灰黑色");
	m_Background.InsertString(1,"蓝黑色");
    m_Background.SetCurSel(pDoc->m_Setting6[m_DlgIdx].m_Background);
	m_iDirection = pDoc->m_Setting6[m_DlgIdx].m_Direction;
	m_bSpeedMode = pDoc->m_Setting6[m_DlgIdx].m_SpeedMode;

	m_CubeNum1 = pDoc->m_Setting6[m_DlgIdx].m_CubeNum1;
    m_CubeNum2 = pDoc->m_Setting6[m_DlgIdx].m_CubeNum2;
    m_CubeNum3 = pDoc->m_Setting6[m_DlgIdx].m_CubeNum3;
    m_CubeNum4 = pDoc->m_Setting6[m_DlgIdx].m_CubeNum4;
    m_Prototype = pDoc->m_Setting6[m_DlgIdx].m_Prototype;
    m_RefAxis = pDoc->m_Setting6[m_DlgIdx].m_RefAxis;
	m_MemTaskMode = pDoc->m_Setting6[m_DlgIdx].m_MemTaskMode;
    m_PracTime.Format("%d", pDoc->m_Setting6[m_DlgIdx].m_PracTime);
	m_ExperTime.Format("%d", pDoc->m_Setting6[m_DlgIdx].m_ExperTime); 
    m_PracTimes.Format("%d", pDoc->m_Setting6[m_DlgIdx].m_PracTimes);
	m_ExperTimes.Format("%d", pDoc->m_Setting6[m_DlgIdx].m_ExperTimes); 

	/*GetDlgItem(IDC_MAINTASKSTATIC)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_MainTask);
	GetDlgItem(IDC_INITSPEEDSTATIC)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_MainTask);
	GetDlgItem(IDC_INITSPEED)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_MainTask);
	GetDlgItem(IDC_SPEEDUNITSTATIC)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_MainTask);
	GetDlgItem(IDC_PRACTIMESTATIC)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_MainTask&&pDoc->m_Setting6[m_DlgIdx].m_PracMode&&!pDoc->m_Setting6[m_DlgIdx].m_SubTask);
	GetDlgItem(IDC_PRACTIME)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_MainTask&&pDoc->m_Setting6[m_DlgIdx].m_PracMode&&!pDoc->m_Setting6[m_DlgIdx].m_SubTask);
	GetDlgItem(IDC_PRACTIMEUNITSTATIC)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_MainTask&&pDoc->m_Setting6[m_DlgIdx].m_PracMode&&!pDoc->m_Setting6[m_DlgIdx].m_SubTask);
	GetDlgItem(IDC_EXPERTIMESTATIC)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_MainTask&&pDoc->m_Setting6[m_DlgIdx].m_ExperMode&&!pDoc->m_Setting6[m_DlgIdx].m_SubTask);
	GetDlgItem(IDC_EXPERTIME)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_MainTask&&pDoc->m_Setting6[m_DlgIdx].m_ExperMode&&!pDoc->m_Setting6[m_DlgIdx].m_SubTask);
	GetDlgItem(IDC_EXPERTIMEUNITSTATIC)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_MainTask&&pDoc->m_Setting6[m_DlgIdx].m_ExperMode&&!pDoc->m_Setting6[m_DlgIdx].m_SubTask);

	GetDlgItem(IDC_SUBTASKSTATIC)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_SubTask);
    GetDlgItem(IDC_CUBENUMSTATIC)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_SubTask);
	GetDlgItem(IDC_CUBENUM1)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_SubTask);
	GetDlgItem(IDC_CUBENUM2)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_SubTask);
	GetDlgItem(IDC_CUBENUM3)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_SubTask);
	GetDlgItem(IDC_CUBENUM4)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_SubTask);
	GetDlgItem(IDC_PROTOTYPESTATIC)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_SubTask);
	GetDlgItem(IDC_PROTOTYPE1)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_SubTask);
	GetDlgItem(IDC_PROTOTYPE2)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_SubTask);
	GetDlgItem(IDC_PROTOTYPE3)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_SubTask);
	GetDlgItem(IDC_PROTOTYPE4)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_SubTask);
	GetDlgItem(IDC_REFAXISSTATIC)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_SubTask);
	GetDlgItem(IDC_REFAXIS1)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_SubTask);
	GetDlgItem(IDC_REFAXIS2)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_SubTask);
	GetDlgItem(IDC_REFAXIS3)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_SubTask);
	GetDlgItem(IDC_TASKMODESTATIC)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_SubTask);
	GetDlgItem(IDC_MEMTASKMODE0)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_SubTask);
	GetDlgItem(IDC_MEMTASKMODE1)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_SubTask);
	GetDlgItem(IDC_PRACTIMESSTATIC)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_SubTask&&pDoc->m_Setting6[m_DlgIdx].m_PracMode);
	GetDlgItem(IDC_PRACTIMES)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_SubTask&&pDoc->m_Setting6[m_DlgIdx].m_PracMode);
	GetDlgItem(IDC_EXPERTIMESSTATIC)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_SubTask&&pDoc->m_Setting6[m_DlgIdx].m_ExperMode);
	GetDlgItem(IDC_EXPERTIMES)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_SubTask&&pDoc->m_Setting6[m_DlgIdx].m_ExperMode);*/

	// 初始化速度设置的enable和disable
	GetDlgItem(IDC_INITSPEEDSTATIC)->EnableWindow(!pDoc->m_Setting6[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_INITSPEED)->EnableWindow(!pDoc->m_Setting6[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_SPEEDUNITSTATIC)->EnableWindow(!pDoc->m_Setting6[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_INITSPEEDSTATIC4)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_INITSPEED2)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_INITSPEEDUNITSTATIC2)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_SPEEDMAXSTATIC)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_SPEEDMIN)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_SPEEDMIDSTATIC)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_SPEEDMAX4)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_SPEEDMAXUNITSTATIC2)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_ACCELERATIONSTATIC)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_ACCELERATIONMIN)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_ACCELERATIONMIDSTATIC)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_ACCELERATIONMAX)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_ACCELERATIONUNITSTATIC2)->EnableWindow(pDoc->m_Setting6[m_DlgIdx].m_SpeedMode);


	UpdateData(FALSE);	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSettingDlg6::OnMaintask() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	/*GetDlgItem(IDC_MAINTASKSTATIC)->EnableWindow(m_MainTask);
	GetDlgItem(IDC_INITSPEEDSTATIC)->EnableWindow(m_MainTask);
	GetDlgItem(IDC_INITSPEED)->EnableWindow(m_MainTask);
	GetDlgItem(IDC_SPEEDUNITSTATIC)->EnableWindow(m_MainTask);
	GetDlgItem(IDC_PRACTIMESTATIC)->EnableWindow(m_MainTask&&m_PracMode&&!m_SubTask);
	GetDlgItem(IDC_PRACTIME)->EnableWindow(m_MainTask&&m_PracMode&&!m_SubTask);
	GetDlgItem(IDC_PRACTIMEUNITSTATIC)->EnableWindow(m_MainTask&&m_PracMode&&!m_SubTask);
	GetDlgItem(IDC_EXPERTIMESTATIC)->EnableWindow(m_MainTask&&m_ExperMode&&!m_SubTask);
	GetDlgItem(IDC_EXPERTIME)->EnableWindow(m_MainTask&&m_ExperMode&&!m_SubTask);
	GetDlgItem(IDC_EXPERTIMEUNITSTATIC)->EnableWindow(m_MainTask&&m_ExperMode&&!m_SubTask);*/
}

void CSettingDlg6::OnSubtask() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);	
	GetDlgItem(IDC_SUBTASKSTATIC)->EnableWindow(m_SubTask);
    GetDlgItem(IDC_CUBENUMSTATIC)->EnableWindow(m_SubTask);
	GetDlgItem(IDC_CUBENUM1)->EnableWindow(m_SubTask);
	GetDlgItem(IDC_CUBENUM2)->EnableWindow(m_SubTask);
	GetDlgItem(IDC_CUBENUM3)->EnableWindow(m_SubTask);
	GetDlgItem(IDC_CUBENUM4)->EnableWindow(m_SubTask);
	GetDlgItem(IDC_PROTOTYPESTATIC)->EnableWindow(m_SubTask);
	GetDlgItem(IDC_PROTOTYPE1)->EnableWindow(m_SubTask);
	GetDlgItem(IDC_PROTOTYPE2)->EnableWindow(m_SubTask);
	GetDlgItem(IDC_PROTOTYPE3)->EnableWindow(m_SubTask);
	GetDlgItem(IDC_PROTOTYPE4)->EnableWindow(m_SubTask);
	GetDlgItem(IDC_REFAXISSTATIC)->EnableWindow(m_SubTask);
	GetDlgItem(IDC_REFAXIS1)->EnableWindow(m_SubTask);
	GetDlgItem(IDC_REFAXIS2)->EnableWindow(m_SubTask);
	GetDlgItem(IDC_REFAXIS3)->EnableWindow(m_SubTask);
	GetDlgItem(IDC_TASKMODESTATIC)->EnableWindow(m_SubTask);
	GetDlgItem(IDC_MEMTASKMODE0)->EnableWindow(m_SubTask);
	GetDlgItem(IDC_MEMTASKMODE1)->EnableWindow(m_SubTask);
	GetDlgItem(IDC_PRACTIMESSTATIC)->EnableWindow(m_SubTask&&m_PracMode);
	GetDlgItem(IDC_PRACTIMES)->EnableWindow(m_SubTask&&m_PracMode);
	GetDlgItem(IDC_EXPERTIMESSTATIC)->EnableWindow(m_SubTask&&m_ExperMode);
	GetDlgItem(IDC_EXPERTIMES)->EnableWindow(m_SubTask&&m_ExperMode);
	GetDlgItem(IDC_PRACTIMESTATIC)->EnableWindow(m_MainTask&&m_PracMode&&!m_SubTask);
	GetDlgItem(IDC_PRACTIME)->EnableWindow(m_MainTask&&m_PracMode&&!m_SubTask);
	GetDlgItem(IDC_PRACTIMEUNITSTATIC)->EnableWindow(m_MainTask&&m_PracMode&&!m_SubTask);
	GetDlgItem(IDC_EXPERTIMESTATIC)->EnableWindow(m_MainTask&&m_ExperMode&&!m_SubTask);
	GetDlgItem(IDC_EXPERTIME)->EnableWindow(m_MainTask&&m_ExperMode&&!m_SubTask);
	GetDlgItem(IDC_EXPERTIMEUNITSTATIC)->EnableWindow(m_MainTask&&m_ExperMode&&!m_SubTask);
}

void CSettingDlg6::OnPracmode() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	/*GetDlgItem(IDC_PRACTIMESTATIC)->EnableWindow(m_MainTask&&m_PracMode&&!m_SubTask);
	GetDlgItem(IDC_PRACTIME)->EnableWindow(m_MainTask&&m_PracMode&&!m_SubTask);
	GetDlgItem(IDC_PRACTIMEUNITSTATIC)->EnableWindow(m_MainTask&&m_PracMode&&!m_SubTask);
	GetDlgItem(IDC_PRACTIMESSTATIC)->EnableWindow(m_SubTask&&m_PracMode);
	GetDlgItem(IDC_PRACTIMES)->EnableWindow(m_SubTask&&m_PracMode);*/
}

void CSettingDlg6::OnExpermode() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetDlgItem(IDC_EXPERTIMESTATIC)->EnableWindow(m_MainTask&&m_ExperMode&&!m_SubTask);
	GetDlgItem(IDC_EXPERTIME)->EnableWindow(m_MainTask&&m_ExperMode&&!m_SubTask);
	GetDlgItem(IDC_EXPERTIMEUNITSTATIC)->EnableWindow(m_MainTask&&m_ExperMode&&!m_SubTask);
	GetDlgItem(IDC_EXPERTIMESSTATIC)->EnableWindow(m_SubTask&&m_ExperMode);
	GetDlgItem(IDC_EXPERTIMES)->EnableWindow(m_SubTask&&m_ExperMode);
}


void CSettingDlg6::OnBnClickedJoyMovePos()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CSettingDlg6::OnStnClickedRefaxisstatic()
{
	// TODO: 在此添加控件通知处理程序代码
}


HBRUSH CSettingDlg6::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_EDIT){
		pDC->SetBkColor(RGB(255,255,255));
	}
	return hbr;
}


void CSettingDlg6::OnBnClickedSpeedmode0()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	// 初始化速度设置的enable和disable
	GetDlgItem(IDC_INITSPEEDSTATIC)->EnableWindow(!m_bSpeedMode);
	GetDlgItem(IDC_INITSPEED)->EnableWindow(!m_bSpeedMode);
	GetDlgItem(IDC_SPEEDUNITSTATIC)->EnableWindow(!m_bSpeedMode);
	GetDlgItem(IDC_INITSPEEDSTATIC4)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_INITSPEED2)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_INITSPEEDUNITSTATIC2)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_SPEEDMAXSTATIC)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_SPEEDMIN)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_SPEEDMIDSTATIC)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_SPEEDMAX4)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_SPEEDMAXUNITSTATIC2)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_ACCELERATIONSTATIC)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_ACCELERATIONMIN)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_ACCELERATIONMIDSTATIC)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_ACCELERATIONMAX)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_ACCELERATIONUNITSTATIC2)->EnableWindow(m_bSpeedMode);

}


void CSettingDlg6::OnBnClickedSpeedmode1()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	// 初始化速度设置的enable和disable
	GetDlgItem(IDC_INITSPEEDSTATIC)->EnableWindow(!m_bSpeedMode);
	GetDlgItem(IDC_INITSPEED)->EnableWindow(!m_bSpeedMode);
	GetDlgItem(IDC_SPEEDUNITSTATIC)->EnableWindow(!m_bSpeedMode);
	GetDlgItem(IDC_INITSPEEDSTATIC4)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_INITSPEED2)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_INITSPEEDUNITSTATIC2)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_SPEEDMAXSTATIC)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_SPEEDMIN)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_SPEEDMIDSTATIC)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_SPEEDMAX4)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_SPEEDMAXUNITSTATIC2)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_ACCELERATIONSTATIC)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_ACCELERATIONMIN)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_ACCELERATIONMIDSTATIC)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_ACCELERATIONMAX)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_ACCELERATIONUNITSTATIC2)->EnableWindow(m_bSpeedMode);

}
