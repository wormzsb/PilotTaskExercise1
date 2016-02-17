// SettingDlg1.cpp : implementation file
//

#include "stdafx.h"
#include "TaskControl.h"
#include "SettingDlg1.h"
#include "MainFrm.h"
#include "TaskControlDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg1 dialog


CSettingDlg1::CSettingDlg1(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingDlg1::IDD, pParent)
	
{
	//{{AFX_DATA_INIT(CSettingDlg1)
	m_PauseNum = 0;
	m_AngleSpeedMax = _T("");
	m_AngleSpeedMin = _T("");
	m_PracTimes = _T("");
	m_ExperTime = _T("");
	m_PracTime = _T("");
	m_MoveMode = -1;
	m_SpeedMode = -1;
	m_Direction = -1;
	m_AccelerationMax = _T("");
	m_AccelerationMin = _T("");
	m_InitSpeed = _T("");
	m_ExperTimes = _T("");
	m_SpeedMax = _T("");
	m_PracMode = FALSE;
	m_ExperMode = FALSE;
	m_Pause = 0;
	m_Speed = _T("");
	m_SpeedMin = _T("");
	m_RotateAngleMax = _T("");
	m_RotateAngleMin = _T("");
	m_TaskName = _T("");
	m_iJoyMoveDirection = 0;
	//}}AFX_DATA_INIT
}

CSettingDlg1::~CSettingDlg1()
{
}

void CSettingDlg1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingDlg1)
	DDX_Control(pDX, IDC_TRACK, m_Track);
	DDX_Control(pDX, IDC_BACKGROUND, m_Background);
	DDX_Text(pDX, IDC_PAUSENUM, m_PauseNum);
	DDX_Text(pDX, IDC_ANGLESPEEDMAX, m_AngleSpeedMax);
	DDX_Text(pDX, IDC_ANGLESPEEDMIN, m_AngleSpeedMin);
	DDX_Text(pDX, IDC_PRACTIMES, m_PracTimes);
	//DDX_Text(pDX, IDC_EXPERTIME, m_ExperTime);
	DDX_Text(pDX, IDC_PRACTIME, m_PracTime);
	DDX_Radio(pDX, IDC_MOVEMODE0, m_MoveMode);
	DDX_Radio(pDX, IDC_SPEEDMODE0, m_SpeedMode);
	DDX_Radio(pDX, IDC_DIRECTION0, m_Direction);
	DDX_Text(pDX, IDC_ACCELERATIONMAX, m_AccelerationMax);
	DDX_Text(pDX, IDC_ACCELERATIONMIN, m_AccelerationMin);
	DDX_Text(pDX, IDC_INITSPEED, m_InitSpeed);
	//DDX_Text(pDX, IDC_EXPERTIMES, m_ExperTimes);
	DDX_Text(pDX, IDC_SPEEDMAX, m_SpeedMax);
	//DDX_Check(pDX, IDC_PRACMODE, m_PracMode);
	//DDX_Check(pDX, IDC_EXPERMODE, m_ExperMode);
	DDX_Radio(pDX, IDC_PAUSE0, m_Pause);
	DDX_Text(pDX, IDC_SPEED, m_Speed);
	DDX_Text(pDX, IDC_SPEEDMIN, m_SpeedMin);
	DDX_Text(pDX, IDC_ROTATEANGLEMAX, m_RotateAngleMax);
	DDX_Text(pDX, IDC_ROTATEANGLEMIN, m_RotateAngleMin);
	DDX_Text(pDX, IDC_TASKNAME, m_TaskName);
	//}}AFX_DATA_MAP
	DDX_Radio(pDX, IDC_JOY_MOVE_POS, m_iJoyMoveDirection);
}


BEGIN_MESSAGE_MAP(CSettingDlg1, CDialog)
	//{{AFX_MSG_MAP(CSettingDlg1)
	ON_BN_CLICKED(IDC_PRACMODE, OnPracmode)
	ON_BN_CLICKED(IDC_EXPERMODE, OnExpermode)
	ON_BN_CLICKED(IDC_PAUSE0, OnPause0)
	ON_BN_CLICKED(IDC_PAUSE1, OnPause1)
	ON_BN_CLICKED(IDC_MOVEMODE0, OnMovemode0)
	ON_BN_CLICKED(IDC_MOVEMODE1, OnMovemode1)
	ON_BN_CLICKED(IDC_SPEEDMODE0, OnSpeedmode0)
	ON_BN_CLICKED(IDC_SPEEDMODE1, OnSpeedmode1)
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg1 message handlers

BOOL CSettingDlg1::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
    CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();

	m_TaskName = pDoc->m_Setting1[m_DlgIdx].m_TaskName;
	m_PracMode = pDoc->m_Setting1[m_DlgIdx].m_PracMode;
    m_ExperMode = pDoc->m_Setting1[m_DlgIdx].m_ExperMode;
    
	m_Background.InsertString(0,"灰黑色");
	m_Background.InsertString(1,"蓝黑色");
	m_Background.InsertString(2,"飞越星空");
    m_Background.SetCurSel(pDoc->m_Setting1[m_DlgIdx].m_Background);

    m_Track.InsertString(0,"圆形");
	m_Track.InsertString(1,"椭圆形");
	m_Track.InsertString(2,"横8字形");
	m_Track.SetCurSel(pDoc->m_Setting1[m_DlgIdx].m_Track);

	m_iJoyMoveDirection = pDoc->m_Setting1[m_DlgIdx].m_iJoyMoveDirection;
	m_Direction = pDoc->m_Setting1[m_DlgIdx].m_Direction;
    m_MoveMode = pDoc->m_Setting1[m_DlgIdx].m_MoveMode;
    m_SpeedMode = pDoc->m_Setting1[m_DlgIdx].m_SpeedMode;
    m_Pause = pDoc->m_Setting1[m_DlgIdx].m_Pause;
	m_PauseNum = pDoc->m_Setting1[m_DlgIdx].m_PauseNum;
	m_Speed.Format("%.1f", pDoc->m_Setting1[m_DlgIdx].m_Speed);
	m_InitSpeed.Format("%.1f", pDoc->m_Setting1[m_DlgIdx].m_InitSpeed);
	m_SpeedMin.Format("%.1f", pDoc->m_Setting1[m_DlgIdx].m_SpeedMin);
	m_SpeedMax.Format("%.1f", pDoc->m_Setting1[m_DlgIdx].m_SpeedMax);
	m_AccelerationMin.Format("%.1f", pDoc->m_Setting1[m_DlgIdx].m_AccelerationMin);
	m_AccelerationMax.Format("%.1f", pDoc->m_Setting1[m_DlgIdx].m_AccelerationMax);
	m_AngleSpeedMin.Format("%.1f", pDoc->m_Setting1[m_DlgIdx].m_AngleSpeedMin);
	m_AngleSpeedMax.Format("%.1f", pDoc->m_Setting1[m_DlgIdx].m_AngleSpeedMax);
	m_RotateAngleMin.Format("%.1f", pDoc->m_Setting1[m_DlgIdx].m_RotateAngleMin);
	m_RotateAngleMax.Format("%.1f", pDoc->m_Setting1[m_DlgIdx].m_RotateAngleMax);
	m_PracTime.Format("%d", pDoc->m_Setting1[m_DlgIdx].m_PracTime);
	m_ExperTime.Format("%d", pDoc->m_Setting1[m_DlgIdx].m_ExperTime);
    m_PracTimes.Format("%d", pDoc->m_Setting1[m_DlgIdx].m_PracTimes);
	m_ExperTimes.Format("%d", pDoc->m_Setting1[m_DlgIdx].m_ExperTimes);

	GetDlgItem(IDC_PRACTIMESTATIC)->EnableWindow(TRUE);
	//GetDlgItem(IDC_PRACTIME)->EnableWindow(pDoc->m_Setting1[m_DlgIdx].m_PracMode);
	GetDlgItem(IDC_PRACTIMEUNITSTATIC)->EnableWindow(TRUE);
	GetDlgItem(IDC_PRACTIMESSTATIC)->EnableWindow(TRUE);

	GetDlgItem(IDC_PRACTIME)->EnableWindow(TRUE);
	GetDlgItem(IDC_PRACTIMES)->EnableWindow(TRUE);
	//GetDlgItem(IDC_EXPERTIMESTATIC)->EnableWindow(pDoc->m_Setting1[m_DlgIdx].m_ExperMode);
	//GetDlgItem(IDC_EXPERTIME)->EnableWindow(pDoc->m_Setting1[m_DlgIdx].m_ExperMode);
	//GetDlgItem(IDC_EXPERTIMEUNITSTATIC)->EnableWindow(pDoc->m_Setting1[m_DlgIdx].m_PracMode);
	//GetDlgItem(IDC_EXPERTIMESSTATIC)->EnableWindow(pDoc->m_Setting1[m_DlgIdx].m_ExperMode);
	//GetDlgItem(IDC_EXPERTIMES)->EnableWindow(pDoc->m_Setting1[m_DlgIdx].m_ExperMode);

	GetDlgItem(IDC_PAUSENUMSTATIC)->EnableWindow(pDoc->m_Setting1[m_DlgIdx].m_Pause);
	GetDlgItem(IDC_PAUSENUM)->EnableWindow(pDoc->m_Setting1[m_DlgIdx].m_Pause);
	GetDlgItem(IDC_PAUSENUMUNIT)->EnableWindow(pDoc->m_Setting1[m_DlgIdx].m_Pause);

	GetDlgItem(IDC_ROTATESTATIC)->EnableWindow(pDoc->m_Setting1[m_DlgIdx].m_MoveMode);
	GetDlgItem(IDC_ANGLESPEEDSTATIC)->EnableWindow(pDoc->m_Setting1[m_DlgIdx].m_MoveMode);
	GetDlgItem(IDC_ANGLESPEEDMIN)->EnableWindow(pDoc->m_Setting1[m_DlgIdx].m_MoveMode);	
	GetDlgItem(IDC_ANGLESPEEDMIDSTATIC)->EnableWindow(pDoc->m_Setting1[m_DlgIdx].m_MoveMode);	
	GetDlgItem(IDC_ANGLESPEEDMAX)->EnableWindow(pDoc->m_Setting1[m_DlgIdx].m_MoveMode);
	GetDlgItem(IDC_ANGLESPEEDUNITSTATIC)->EnableWindow(pDoc->m_Setting1[m_DlgIdx].m_MoveMode);
	GetDlgItem(IDC_ROTATEANGLESTATIC)->EnableWindow(pDoc->m_Setting1[m_DlgIdx].m_MoveMode);
	GetDlgItem(IDC_ROTATEANGLEMIN)->EnableWindow(pDoc->m_Setting1[m_DlgIdx].m_MoveMode);	
	GetDlgItem(IDC_ROTATEANGLEMIDSTATIC)->EnableWindow(pDoc->m_Setting1[m_DlgIdx].m_MoveMode);	
	GetDlgItem(IDC_ROTATEANGLEMAX)->EnableWindow(pDoc->m_Setting1[m_DlgIdx].m_MoveMode);
	GetDlgItem(IDC_ROTATEANGLEUNITSTATIC)->EnableWindow(pDoc->m_Setting1[m_DlgIdx].m_MoveMode);

	GetDlgItem(IDC_SPEEDSTATIC)->EnableWindow(!pDoc->m_Setting1[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_SPEED)->EnableWindow(!pDoc->m_Setting1[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_SPEEDUNITSTATIC)->EnableWindow(!pDoc->m_Setting1[m_DlgIdx].m_SpeedMode);	
	GetDlgItem(IDC_INITSPEED)->EnableWindow(pDoc->m_Setting1[m_DlgIdx].m_SpeedMode);	
	GetDlgItem(IDC_INITSPEEDUNITSTATIC)->EnableWindow(pDoc->m_Setting1[m_DlgIdx].m_SpeedMode);	
	GetDlgItem(IDC_SPEEDMAXSTATIC)->EnableWindow(pDoc->m_Setting1[m_DlgIdx].m_SpeedMode);	
	GetDlgItem(IDC_SPEEDMIN)->EnableWindow(pDoc->m_Setting1[m_DlgIdx].m_SpeedMode);	
	GetDlgItem(IDC_SPEEDMIDSTATIC)->EnableWindow(pDoc->m_Setting1[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_SPEEDMAX)->EnableWindow(pDoc->m_Setting1[m_DlgIdx].m_SpeedMode);	
	GetDlgItem(IDC_SPEEDMAXUNITSTATIC)->EnableWindow(pDoc->m_Setting1[m_DlgIdx].m_SpeedMode);	
	GetDlgItem(IDC_ACCELERATIONSTATIC)->EnableWindow(pDoc->m_Setting1[m_DlgIdx].m_SpeedMode);	
	GetDlgItem(IDC_ACCELERATIONMIN)->EnableWindow(pDoc->m_Setting1[m_DlgIdx].m_SpeedMode);	
	GetDlgItem(IDC_ACCELERATIONMIDSTATIC)->EnableWindow(pDoc->m_Setting1[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_ACCELERATIONMAX)->EnableWindow(pDoc->m_Setting1[m_DlgIdx].m_SpeedMode);	
	GetDlgItem(IDC_ACCELERATIONUNITSTATIC)->EnableWindow(pDoc->m_Setting1[m_DlgIdx].m_SpeedMode);

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSettingDlg1::Save() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
    CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();

	strcpy_s(pDoc->m_Setting1[m_DlgIdx].m_TaskName, 100, m_TaskName);
	
	//显示反馈
	
	pDoc->m_Setting1[m_DlgIdx].m_PracMode = 0;
	pDoc->m_Setting1[m_DlgIdx].m_ExperMode = 1;
	pDoc->m_Setting1[m_DlgIdx].m_PracTimes = atoi(m_PracTimes);
	pDoc->m_Setting1[m_DlgIdx].m_ExperTimes = atoi(m_PracTimes);
	pDoc->m_Setting1[m_DlgIdx].m_PracTime = atoi(m_PracTime);
	pDoc->m_Setting1[m_DlgIdx].m_ExperTime = atoi(m_PracTime);
	
		
    pDoc->m_Setting1[m_DlgIdx].m_Background = m_Background.GetCurSel();
	pDoc->m_Setting1[m_DlgIdx].m_Track = m_Track.GetCurSel();
	pDoc->m_Setting1[m_DlgIdx].m_Direction = m_Direction;
    pDoc->m_Setting1[m_DlgIdx].m_MoveMode = m_MoveMode;
    pDoc->m_Setting1[m_DlgIdx].m_SpeedMode = m_SpeedMode;
    pDoc->m_Setting1[m_DlgIdx].m_Pause = m_Pause;
	pDoc->m_Setting1[m_DlgIdx].m_iJoyMoveDirection = m_iJoyMoveDirection;


	if(pDoc->m_Setting1[m_DlgIdx].m_Pause)
	{
		pDoc->m_Setting1[m_DlgIdx].m_PauseNum = m_PauseNum;
	}
	else
	{
        pDoc->m_Setting1[m_DlgIdx].m_PauseNum = 0;
	}
	if(!pDoc->m_Setting1[m_DlgIdx].m_SpeedMode)
	{
		pDoc->m_Setting1[m_DlgIdx].m_Speed = atof(m_Speed);
		pDoc->m_Setting1[m_DlgIdx].m_InitSpeed = -1;
		pDoc->m_Setting1[m_DlgIdx].m_SpeedMin = -1;
		pDoc->m_Setting1[m_DlgIdx].m_SpeedMax = -1;
		pDoc->m_Setting1[m_DlgIdx].m_AccelerationMin = -1;
    	pDoc->m_Setting1[m_DlgIdx].m_AccelerationMax = -1;
	}
	else
	{
		pDoc->m_Setting1[m_DlgIdx].m_Speed = -1;
		pDoc->m_Setting1[m_DlgIdx].m_InitSpeed = atof(m_InitSpeed);
		pDoc->m_Setting1[m_DlgIdx].m_SpeedMin = atof(m_SpeedMin);
		pDoc->m_Setting1[m_DlgIdx].m_SpeedMax = atof(m_SpeedMax);
		pDoc->m_Setting1[m_DlgIdx].m_AccelerationMin = atof(m_AccelerationMin);
    	pDoc->m_Setting1[m_DlgIdx].m_AccelerationMax = atof(m_AccelerationMax);
	}
	if(pDoc->m_Setting1[m_DlgIdx].m_MoveMode)
	{
		pDoc->m_Setting1[m_DlgIdx].m_AngleSpeedMin = atof(m_AngleSpeedMin);
		pDoc->m_Setting1[m_DlgIdx].m_AngleSpeedMax = atof(m_AngleSpeedMax);
		pDoc->m_Setting1[m_DlgIdx].m_RotateAngleMin = atof(m_RotateAngleMin);
		pDoc->m_Setting1[m_DlgIdx].m_RotateAngleMax = atof(m_RotateAngleMax);
	}
	else
	{
		pDoc->m_Setting1[m_DlgIdx].m_AngleSpeedMin = -1;
		pDoc->m_Setting1[m_DlgIdx].m_AngleSpeedMax = -1;
		pDoc->m_Setting1[m_DlgIdx].m_RotateAngleMin = -1;
		pDoc->m_Setting1[m_DlgIdx].m_RotateAngleMax = -1;
	}
	/*if(pDoc->m_Setting1[m_DlgIdx].m_PracMode)
	{
		pDoc->m_Setting1[m_DlgIdx].m_PracTime = atoi(m_PracTime);
		//pDoc->m_Setting1[m_DlgIdx].m_ExperTime = atoi(m_ExperTime);
	}
	else
	{
        pDoc->m_Setting1[m_DlgIdx].m_PracTime = -1;
	}
	if(pDoc->m_Setting1[m_DlgIdx].m_ExperMode)
	{
		pDoc->m_Setting1[m_DlgIdx].m_ExperTime = atoi(m_ExperTime);
	}
	else
	{
        pDoc->m_Setting1[m_DlgIdx].m_ExperTime = -1;
	}
	
	if(pDoc->m_Setting1[m_DlgIdx].m_PracMode)
	{
	    pDoc->m_Setting1[m_DlgIdx].m_PracTimes = atoi(m_PracTimes);
		//pDoc->m_Setting1[m_DlgIdx].m_ExperTimes = atoi(m_ExperTimes);
	}
	else
	{
	    pDoc->m_Setting1[m_DlgIdx].m_PracTimes = -1;
	}
	if(pDoc->m_Setting1[m_DlgIdx].m_ExperMode)
	{
		pDoc->m_Setting1[m_DlgIdx].m_ExperTimes = atoi(m_ExperTimes);
	}
	else
	{
		pDoc->m_Setting1[m_DlgIdx].m_ExperTimes = -1;
	}*/
}

void CSettingDlg1::OnPracmode() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetDlgItem(IDC_PRACTIMESTATIC)->EnableWindow(m_PracMode);
	GetDlgItem(IDC_PRACTIME)->EnableWindow(m_PracMode);
	GetDlgItem(IDC_PRACTIMEUNITSTATIC)->EnableWindow(m_PracMode);
	GetDlgItem(IDC_PRACTIMESSTATIC)->EnableWindow(m_PracMode);
	GetDlgItem(IDC_PRACTIMES)->EnableWindow(m_PracMode);
}

void CSettingDlg1::OnExpermode() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetDlgItem(IDC_EXPERTIMESTATIC)->EnableWindow(m_ExperMode);
	GetDlgItem(IDC_EXPERTIME)->EnableWindow(m_ExperMode);
	GetDlgItem(IDC_EXPERTIMEUNITSTATIC)->EnableWindow(m_ExperMode);
	GetDlgItem(IDC_EXPERTIMESSTATIC)->EnableWindow(m_ExperMode);
	GetDlgItem(IDC_EXPERTIMES)->EnableWindow(m_ExperMode);	
}

void CSettingDlg1::OnPause0() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetDlgItem(IDC_PAUSENUMSTATIC)->EnableWindow(m_Pause);
	GetDlgItem(IDC_PAUSENUM)->EnableWindow(m_Pause);
	GetDlgItem(IDC_PAUSENUMUNIT)->EnableWindow(m_Pause);
}

void CSettingDlg1::OnPause1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetDlgItem(IDC_PAUSENUMSTATIC)->EnableWindow(m_Pause);
	GetDlgItem(IDC_PAUSENUM)->EnableWindow(m_Pause);
	GetDlgItem(IDC_PAUSENUMUNIT)->EnableWindow(m_Pause);	
}

void CSettingDlg1::OnMovemode0() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetDlgItem(IDC_ROTATESTATIC)->EnableWindow(m_MoveMode);
	GetDlgItem(IDC_ANGLESPEEDSTATIC)->EnableWindow(m_MoveMode);
	GetDlgItem(IDC_ANGLESPEEDMIN)->EnableWindow(m_MoveMode);	
	GetDlgItem(IDC_ANGLESPEEDMIDSTATIC)->EnableWindow(m_MoveMode);	
	GetDlgItem(IDC_ANGLESPEEDMAX)->EnableWindow(m_MoveMode);
	GetDlgItem(IDC_ANGLESPEEDUNITSTATIC)->EnableWindow(m_MoveMode);
	GetDlgItem(IDC_ROTATEANGLESTATIC)->EnableWindow(m_MoveMode);
	GetDlgItem(IDC_ROTATEANGLEMIN)->EnableWindow(m_MoveMode);	
	GetDlgItem(IDC_ROTATEANGLEMIDSTATIC)->EnableWindow(m_MoveMode);	
	GetDlgItem(IDC_ROTATEANGLEMAX)->EnableWindow(m_MoveMode);
	GetDlgItem(IDC_ROTATEANGLEUNITSTATIC)->EnableWindow(m_MoveMode);
}

void CSettingDlg1::OnMovemode1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetDlgItem(IDC_ROTATESTATIC)->EnableWindow(m_MoveMode);
	GetDlgItem(IDC_ANGLESPEEDSTATIC)->EnableWindow(m_MoveMode);
	GetDlgItem(IDC_ANGLESPEEDMIN)->EnableWindow(m_MoveMode);	
	GetDlgItem(IDC_ANGLESPEEDMIDSTATIC)->EnableWindow(m_MoveMode);	
	GetDlgItem(IDC_ANGLESPEEDMAX)->EnableWindow(m_MoveMode);	
	GetDlgItem(IDC_ANGLESPEEDUNITSTATIC)->EnableWindow(m_MoveMode);
	GetDlgItem(IDC_ROTATEANGLESTATIC)->EnableWindow(m_MoveMode);
	GetDlgItem(IDC_ROTATEANGLEMIN)->EnableWindow(m_MoveMode);	
	GetDlgItem(IDC_ROTATEANGLEMIDSTATIC)->EnableWindow(m_MoveMode);	
	GetDlgItem(IDC_ROTATEANGLEMAX)->EnableWindow(m_MoveMode);
	GetDlgItem(IDC_ROTATEANGLEUNITSTATIC)->EnableWindow(m_MoveMode);
}

void CSettingDlg1::OnSpeedmode0() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetDlgItem(IDC_SPEEDSTATIC)->EnableWindow(!m_SpeedMode);
	GetDlgItem(IDC_SPEED)->EnableWindow(!m_SpeedMode);
	GetDlgItem(IDC_SPEEDUNITSTATIC)->EnableWindow(!m_SpeedMode);	
	GetDlgItem(IDC_INITSPEED)->EnableWindow(m_SpeedMode);	
	GetDlgItem(IDC_INITSPEEDUNITSTATIC)->EnableWindow(m_SpeedMode);	
	GetDlgItem(IDC_SPEEDMAXSTATIC)->EnableWindow(m_SpeedMode);
	GetDlgItem(IDC_SPEEDMIN)->EnableWindow(m_SpeedMode);	
	GetDlgItem(IDC_SPEEDMIDSTATIC)->EnableWindow(m_SpeedMode);
	GetDlgItem(IDC_SPEEDMAX)->EnableWindow(m_SpeedMode);	
	GetDlgItem(IDC_SPEEDMAXUNITSTATIC)->EnableWindow(m_SpeedMode);	
	GetDlgItem(IDC_ACCELERATIONSTATIC)->EnableWindow(m_SpeedMode);	
	GetDlgItem(IDC_ACCELERATIONMIN)->EnableWindow(m_SpeedMode);	
	GetDlgItem(IDC_ACCELERATIONMIDSTATIC)->EnableWindow(m_SpeedMode);
	GetDlgItem(IDC_ACCELERATIONMAX)->EnableWindow(m_SpeedMode);
	GetDlgItem(IDC_ACCELERATIONUNITSTATIC)->EnableWindow(m_SpeedMode);
}

void CSettingDlg1::OnSpeedmode1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetDlgItem(IDC_SPEEDSTATIC)->EnableWindow(!m_SpeedMode);
	GetDlgItem(IDC_SPEED)->EnableWindow(!m_SpeedMode);
	GetDlgItem(IDC_SPEEDUNITSTATIC)->EnableWindow(!m_SpeedMode);	
	GetDlgItem(IDC_INITSPEED)->EnableWindow(m_SpeedMode);	
	GetDlgItem(IDC_INITSPEEDUNITSTATIC)->EnableWindow(m_SpeedMode);	
	GetDlgItem(IDC_SPEEDMAXSTATIC)->EnableWindow(m_SpeedMode);
	GetDlgItem(IDC_SPEEDMIN)->EnableWindow(m_SpeedMode);
	GetDlgItem(IDC_SPEEDMIDSTATIC)->EnableWindow(m_SpeedMode);
	GetDlgItem(IDC_SPEEDMAX)->EnableWindow(m_SpeedMode);	
	GetDlgItem(IDC_SPEEDMAXUNITSTATIC)->EnableWindow(m_SpeedMode);	
	GetDlgItem(IDC_ACCELERATIONSTATIC)->EnableWindow(m_SpeedMode);	
	GetDlgItem(IDC_ACCELERATIONMIN)->EnableWindow(m_SpeedMode);	
	GetDlgItem(IDC_ACCELERATIONMIDSTATIC)->EnableWindow(m_SpeedMode);
	GetDlgItem(IDC_ACCELERATIONMAX)->EnableWindow(m_SpeedMode);
	GetDlgItem(IDC_ACCELERATIONUNITSTATIC)->EnableWindow(m_SpeedMode);
}


HBRUSH CSettingDlg1::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_EDIT){
		pDC->SetBkColor(RGB(255,255,255));
	}
/*	if (nCtlColor == CTLCOLOR_EDIT){
		if (pWnd == this->GetDlgItem(IDC_BACKGROUND)
			|| pWnd == this->GetDlgItem(IDC_TRACK)) {
				return hbr;
		}
		else{
			pDC->SetBkColor(RGB(255,255,255));
			CRect rect;
			pWnd->GetClientRect(&rect);
			rect.InflateRect(1,1,1,1);
			CBrush brush(RGB(0,0,255));
			pDC->FrameRect(rect,&brush);
		}
	}*/
	return hbr;
}


void CSettingDlg1::OnPaint()
{
	CPaintDC dc(this); // device context for painting
		// TODO: 在此处添加消息处理程序代码
		// 不为绘图消息调用 CDialog::OnPaint()
}
