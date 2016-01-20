// SettingDlg2.cpp : implementation file
//

#include "stdafx.h"
#include "TaskControl.h"
#include "SettingDlg2.h"
#include "MainFrm.h"
#include "TaskControlDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//const char m_Edge[4][3][4] = {{"AB","AC","AD"},{"BA","BC","BD"},{"CA","CB","CD"},{"DA","DB","DC"}};
const short m_HoldTimeStatic[12] = {IDC_HOLDTIMESTATIC1, IDC_HOLDTIMESTATIC2, IDC_HOLDTIMESTATIC3, IDC_HOLDTIMESTATIC4, IDC_HOLDTIMESTATIC5, IDC_HOLDTIMESTATIC6,
	IDC_HOLDTIMESTATIC7, IDC_HOLDTIMESTATIC8, IDC_HOLDTIMESTATIC9, IDC_HOLDTIMESTATIC10, IDC_HOLDTIMESTATIC11, IDC_HOLDTIMESTATIC12};
const short m_HoldTime[12] = {IDC_HOLDTIME1, IDC_HOLDTIME2, IDC_HOLDTIME3, IDC_HOLDTIME4, IDC_HOLDTIME5, IDC_HOLDTIME6,
    IDC_HOLDTIME7,  IDC_HOLDTIME8,  IDC_HOLDTIME9, IDC_HOLDTIME10, IDC_HOLDTIME11, IDC_HOLDTIME12}; 
const short m_HoldTimeUnitStatic[12] = {IDC_HOLDTIMEUNITSTATIC1, IDC_HOLDTIMEUNITSTATIC2, IDC_HOLDTIMEUNITSTATIC3, IDC_HOLDTIMEUNITSTATIC4, IDC_HOLDTIMEUNITSTATIC5, IDC_HOLDTIMEUNITSTATIC6,
	IDC_HOLDTIMEUNITSTATIC7, IDC_HOLDTIMEUNITSTATIC8, IDC_HOLDTIMEUNITSTATIC9, IDC_HOLDTIMEUNITSTATIC10, IDC_HOLDTIMEUNITSTATIC11, IDC_HOLDTIMEUNITSTATIC12};
/////////////////////////////////////////////////////////////////////////////
// CSettingDlg2 dialog


CSettingDlg2::CSettingDlg2(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingDlg2::IDD, pParent)
	, m_iJoyMoveDirection(0)
	, m_iSubTaskInterval(0)
	, m_bSpeedMode(FALSE)
	, m_fSpeed(0)
	, m_fInitSpeed(0)
	, m_fSpeedMin(0)
	, m_fSpeedMax(0)
	, m_fAccMin(0)
	, m_fAccMax(0)
{
	//{{AFX_DATA_INIT(CSettingDlg2)
	m_PracTimes = _T("");
	m_Direction = -1;
	m_ExperTimes = _T("");
	m_PracMode = FALSE;
	m_ExperMode = FALSE;
	m_InitSpeed = _T("");
	m_HoldTime1 = _T("");
	m_HoldTime10 = _T("");
	m_HoldTime11 = _T("");
	m_HoldTime12 = _T("");
	m_HoldTime2 = _T("");
	m_HoldTime3 = _T("");
	m_HoldTime4 = _T("");
	m_HoldTime5 = _T("");
	m_HoldTime6 = _T("");
	m_HoldTime7 = _T("");
	m_HoldTime8 = _T("");
	m_HoldTime9 = _T("");
	m_MainTask = FALSE;
	m_SubTask = FALSE;
	m_PracTime = _T("");
	m_ExperTime = _T("");
	m_TaskName = _T("");
	//}}AFX_DATA_INIT
}


void CSettingDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingDlg2)
	DDX_Control(pDX, IDC_HOLDTIMENUM, m_HoldTimeNumCom);
	DDX_Control(pDX, IDC_BACKGROUND, m_Background);
	DDX_Text(pDX, IDC_PRACTIMES, m_PracTimes);
	DDX_Radio(pDX, IDC_DIRECTION0, m_Direction);
	DDX_Text(pDX, IDC_EXPERTIMES, m_ExperTimes);
	DDX_Check(pDX, IDC_PRACMODE, m_PracMode);
	DDX_Text(pDX, IDC_HOLDTIME1, m_HoldTime1);
	DDX_Text(pDX, IDC_HOLDTIME10, m_HoldTime10);
	DDX_Text(pDX, IDC_HOLDTIME11, m_HoldTime11);
	DDX_Text(pDX, IDC_HOLDTIME12, m_HoldTime12);
	DDX_Text(pDX, IDC_HOLDTIME2, m_HoldTime2);
	DDX_Text(pDX, IDC_HOLDTIME3, m_HoldTime3);
	DDX_Text(pDX, IDC_HOLDTIME4, m_HoldTime4);
	DDX_Text(pDX, IDC_HOLDTIME5, m_HoldTime5);
	DDX_Text(pDX, IDC_HOLDTIME6, m_HoldTime6);
	DDX_Text(pDX, IDC_HOLDTIME7, m_HoldTime7);
	DDX_Text(pDX, IDC_HOLDTIME8, m_HoldTime8);
	DDX_Text(pDX, IDC_HOLDTIME9, m_HoldTime9);
	DDX_Check(pDX, IDC_MAINTASK, m_MainTask);
	DDX_Check(pDX, IDC_SUBTASK, m_SubTask);

	DDX_Radio(pDX, IDC_JOY_MOVE_POS, m_iJoyMoveDirection);
	DDX_Text(pDX, IDC_EDIT1, m_iSubTaskInterval);
	DDX_Radio(pDX, IDC_SPEEDMODE0, m_bSpeedMode);
	DDX_Text(pDX, IDC_SPEED, m_fSpeed);
	DDX_Text(pDX, IDC_INITSPEED, m_fInitSpeed);
	DDX_Text(pDX, IDC_SPEEDMIN, m_fSpeedMin);
	DDX_Text(pDX, IDC_SPEEDMAX2, m_fSpeedMax);
	DDX_Text(pDX, IDC_ACCELERATIONMIN, m_fAccMin);
	DDX_Text(pDX, IDC_ACCELERATIONMAX, m_fAccMax);
	DDX_Control(pDX, IDC_TRACK, m_ccbTrack);
}


BEGIN_MESSAGE_MAP(CSettingDlg2, CDialog)
	//{{AFX_MSG_MAP(CSettingDlg2)
	ON_BN_CLICKED(IDC_EXPERMODE, OnExpermode)
	ON_BN_CLICKED(IDC_PRACMODE, OnPracmode)
	ON_CBN_SELCHANGE(IDC_HOLDTIMENUM, OnSelchangeHoldtimenum)
	ON_BN_CLICKED(IDC_MAINTASK, OnMaintask)
	ON_BN_CLICKED(IDC_SUBTASK, OnSubtask)
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_SPEEDMODE0, &CSettingDlg2::OnBnClickedSpeedmode0)
	ON_BN_CLICKED(IDC_SPEEDMODE1, &CSettingDlg2::OnBnClickedSpeedmode1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg2 message handlers

BOOL CSettingDlg2::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	int i;
	char str[4];
	CEdit*  pEdit=(CEdit*)GetDlgItem(IDC_EDIT2);
    pEdit->SetWindowText(_T("任务2-操作力保持及时间知觉能力测试")); 
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
    CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();
	m_ccbTrack.AddString("圆形");
	m_ccbTrack.AddString("8字形");
	m_ccbTrack.SetCurSel( pDoc->m_Setting2[m_DlgIdx].m_iTrack);
	m_TaskName = pDoc->m_Setting2[m_DlgIdx].m_TaskName;
	m_PracMode = pDoc->m_Setting2[m_DlgIdx].m_PracMode;
    m_ExperMode = pDoc->m_Setting2[m_DlgIdx].m_ExperMode;
	m_MainTask = pDoc->m_Setting2[m_DlgIdx].m_MainTask;
    m_SubTask = pDoc->m_Setting2[m_DlgIdx].m_SubTask;
	m_iJoyMoveDirection = pDoc->m_Setting2[m_DlgIdx].m_iJoyMoveDirection;
	m_iSubTaskInterval = pDoc->m_Setting2[m_DlgIdx].m_iSubTaskInterval;
	
	m_bSpeedMode = pDoc->m_Setting2[m_DlgIdx].m_SpeedMode;
	m_fSpeed = pDoc->m_Setting2[m_DlgIdx].m_Speed;
	m_fSpeedMin = pDoc->m_Setting2[m_DlgIdx].m_SpeedMin;
	m_fSpeedMax = pDoc->m_Setting2[m_DlgIdx].m_SpeedMax;
	m_fAccMin = pDoc->m_Setting2[m_DlgIdx].m_AccelerationMin;
	m_fAccMax = pDoc->m_Setting2[m_DlgIdx].m_AccelerationMax;
	m_fInitSpeed = pDoc->m_Setting2[m_DlgIdx].m_InitSpeed;
	m_HoldTimeNumCom.ResetContent();
	m_HoldTimeNumCom.InitStorage(20, 20*4*sizeof(char));
	for(i=0;i<12;i++)
	{
		sprintf_s(str,"%d",i+1);
        m_HoldTimeNumCom.AddString(str);
	

	}
	m_HoldTimeNumCom.SetCurSel(pDoc->m_Setting2[m_DlgIdx].m_HoldTimeNum-1);


	m_Background.InsertString(0,"灰黑色");
	m_Background.InsertString(1,"蓝黑色");
    m_Background.SetCurSel(pDoc->m_Setting2[m_DlgIdx].m_Background);

	m_Direction = pDoc->m_Setting2[m_DlgIdx].m_Direction;
	m_InitSpeed.Format("%.1f", pDoc->m_Setting2[m_DlgIdx].m_InitSpeed);
	m_HoldTime1.Format("%.1f", pDoc->m_Setting2[m_DlgIdx].m_HoldTime[0]);
	m_HoldTime2.Format("%.1f", pDoc->m_Setting2[m_DlgIdx].m_HoldTime[1]);
	m_HoldTime3.Format("%.1f", pDoc->m_Setting2[m_DlgIdx].m_HoldTime[2]);
	m_HoldTime4.Format("%.1f", pDoc->m_Setting2[m_DlgIdx].m_HoldTime[3]);
	m_HoldTime5.Format("%.1f", pDoc->m_Setting2[m_DlgIdx].m_HoldTime[4]);
	m_HoldTime6.Format("%.1f", pDoc->m_Setting2[m_DlgIdx].m_HoldTime[5]);
	m_HoldTime7.Format("%.1f", pDoc->m_Setting2[m_DlgIdx].m_HoldTime[6]);
	m_HoldTime8.Format("%.1f", pDoc->m_Setting2[m_DlgIdx].m_HoldTime[7]);
	m_HoldTime9.Format("%.1f", pDoc->m_Setting2[m_DlgIdx].m_HoldTime[8]);
	m_HoldTime10.Format("%.1f", pDoc->m_Setting2[m_DlgIdx].m_HoldTime[9]);
	m_HoldTime11.Format("%.1f", pDoc->m_Setting2[m_DlgIdx].m_HoldTime[10]);
	m_HoldTime12.Format("%.1f", pDoc->m_Setting2[m_DlgIdx].m_HoldTime[11]);
	m_PracTime.Format("%d", pDoc->m_Setting2[m_DlgIdx].m_PracTime);
	m_ExperTime.Format("%d", pDoc->m_Setting2[m_DlgIdx].m_ExperTime);
    m_PracTimes.Format("%d", pDoc->m_Setting2[m_DlgIdx].m_PracTimes);
	m_ExperTimes.Format("%d", pDoc->m_Setting2[m_DlgIdx].m_ExperTimes);



	GetDlgItem(IDC_SUBTASKSTATIC)->EnableWindow(pDoc->m_Setting2[m_DlgIdx].m_SubTask);
	GetDlgItem(IDC_HOLDTIMENUMSTATIC)->EnableWindow(pDoc->m_Setting2[m_DlgIdx].m_SubTask);
	GetDlgItem(IDC_HOLDTIMENUM)->EnableWindow(pDoc->m_Setting2[m_DlgIdx].m_SubTask);
	
	
	for(i=0;i<pDoc->m_Setting2[m_DlgIdx].m_HoldTimeNum;i++)
	{
        GetDlgItem(m_HoldTimeStatic[i])->EnableWindow(pDoc->m_Setting2[m_DlgIdx].m_SubTask&&TRUE);
	    GetDlgItem(m_HoldTime[i])->EnableWindow(pDoc->m_Setting2[m_DlgIdx].m_SubTask&&TRUE);	
		GetDlgItem(m_HoldTimeUnitStatic[i])->EnableWindow(pDoc->m_Setting2[m_DlgIdx].m_SubTask&&TRUE);	
	}
	for(i=pDoc->m_Setting2[m_DlgIdx].m_HoldTimeNum;i<12;i++)
	{
        GetDlgItem(m_HoldTimeStatic[i])->EnableWindow(pDoc->m_Setting2[m_DlgIdx].m_SubTask&&FALSE);
	    GetDlgItem(m_HoldTime[i])->EnableWindow(pDoc->m_Setting2[m_DlgIdx].m_SubTask&&FALSE);	
		GetDlgItem(m_HoldTimeUnitStatic[i])->EnableWindow(pDoc->m_Setting2[m_DlgIdx].m_SubTask&&FALSE);	
	}
	
	
	GetDlgItem(IDC_PRACTIMES)->EnableWindow(TRUE);

	// 初始化速度设置的enable和disable
	GetDlgItem(IDC_SPEEDSTATIC)->EnableWindow(!pDoc->m_Setting2[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_SPEED)->EnableWindow(!pDoc->m_Setting2[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_SPEEDUNITSTATIC)->EnableWindow(!pDoc->m_Setting2[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_INITSPEEDSTATIC2)->EnableWindow(pDoc->m_Setting2[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_INITSPEED)->EnableWindow(pDoc->m_Setting2[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_INITSPEEDUNITSTATIC)->EnableWindow(pDoc->m_Setting2[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_SPEEDMAXSTATIC)->EnableWindow(pDoc->m_Setting2[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_SPEEDMIN)->EnableWindow(pDoc->m_Setting2[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_SPEEDMIDSTATIC)->EnableWindow(pDoc->m_Setting2[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_SPEEDMAX2)->EnableWindow(pDoc->m_Setting2[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_SPEEDMAXUNITSTATIC)->EnableWindow(pDoc->m_Setting2[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_ACCELERATIONSTATIC)->EnableWindow(pDoc->m_Setting2[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_ACCELERATIONMIN)->EnableWindow(pDoc->m_Setting2[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_ACCELERATIONMIDSTATIC)->EnableWindow(pDoc->m_Setting2[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_ACCELERATIONMAX)->EnableWindow(pDoc->m_Setting2[m_DlgIdx].m_SpeedMode);
	GetDlgItem(IDC_ACCELERATIONUNITSTATIC)->EnableWindow(pDoc->m_Setting2[m_DlgIdx].m_SpeedMode);


	UpdateData(FALSE);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSettingDlg2::Save() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
    CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();

	strcpy_s(pDoc->m_Setting2[m_DlgIdx].m_TaskName,100, m_TaskName);

	//若有反馈
	if (m_PracMode)
	{
		  pDoc->m_Setting2[m_DlgIdx].m_PracMode = 1;
		  pDoc->m_Setting2[m_DlgIdx].m_ExperMode = 0;
	}
	else
	{
		  pDoc->m_Setting2[m_DlgIdx].m_PracMode = 0;
		  pDoc->m_Setting2[m_DlgIdx].m_ExperMode = 1;
	}
	pDoc->m_Setting2[m_DlgIdx]. m_iTrack = m_ccbTrack.GetCurSel();
	pDoc->m_Setting2[m_DlgIdx].m_ExperTime = atoi(m_PracTime);
	pDoc->m_Setting2[m_DlgIdx].m_PracTime = atoi(m_PracTime);
	pDoc->m_Setting2[m_DlgIdx].m_ExperTimes =  atoi(m_PracTimes);
    pDoc->m_Setting2[m_DlgIdx].m_PracTimes =  atoi(m_PracTimes);
    pDoc->m_Setting2[m_DlgIdx].m_MainTask = m_MainTask;
	pDoc->m_Setting2[m_DlgIdx].m_SubTask = m_SubTask;
	pDoc->m_Setting2[m_DlgIdx].m_Background = m_Background.GetCurSel();
	pDoc->m_Setting2[m_DlgIdx].m_iJoyMoveDirection = m_iJoyMoveDirection;
	pDoc->m_Setting2[m_DlgIdx].m_Direction = m_Direction;
	pDoc->m_Setting2[m_DlgIdx].m_InitSpeed = atof(m_InitSpeed);
	pDoc->m_Setting2[m_DlgIdx].m_iSubTaskInterval = m_iSubTaskInterval;
	pDoc->m_Setting2[m_DlgIdx].m_SpeedMode = m_bSpeedMode;
	pDoc->m_Setting2[m_DlgIdx].m_Speed = m_fSpeed;
	pDoc->m_Setting2[m_DlgIdx].m_SpeedMin = m_fSpeedMin;
	pDoc->m_Setting2[m_DlgIdx].m_SpeedMax = m_fSpeedMax;;
	pDoc->m_Setting2[m_DlgIdx].m_AccelerationMin = m_fAccMin;
	pDoc->m_Setting2[m_DlgIdx].m_AccelerationMax = m_fAccMax;;
	pDoc->m_Setting2[m_DlgIdx].m_InitSpeed = m_fInitSpeed;
	if(pDoc->m_Setting2[m_DlgIdx].m_SubTask)
	{
		pDoc->m_Setting2[m_DlgIdx].m_HoldTimeNum = m_HoldTimeNumCom.GetCurSel()+1;
	}
	else
	{
        pDoc->m_Setting2[m_DlgIdx].m_HoldTimeNum = -1;
	}
	if(pDoc->m_Setting2[m_DlgIdx].m_HoldTimeNum>0)
	{
		pDoc->m_Setting2[m_DlgIdx].m_HoldTime[0] = atof(m_HoldTime1);
	}
	else
	{
		pDoc->m_Setting2[m_DlgIdx].m_HoldTime[0] = -1;
	}
	if(pDoc->m_Setting2[m_DlgIdx].m_HoldTimeNum>1)
	{
		pDoc->m_Setting2[m_DlgIdx].m_HoldTime[1] = atof(m_HoldTime2);
	}
	else
	{
		pDoc->m_Setting2[m_DlgIdx].m_HoldTime[1] = -1;
	}
	if(pDoc->m_Setting2[m_DlgIdx].m_HoldTimeNum>2)
	{
		pDoc->m_Setting2[m_DlgIdx].m_HoldTime[2] = atof(m_HoldTime3);
	}
	else
	{
		pDoc->m_Setting2[m_DlgIdx].m_HoldTime[2] = -1;
	}
	if(pDoc->m_Setting2[m_DlgIdx].m_HoldTimeNum>3)
	{
		pDoc->m_Setting2[m_DlgIdx].m_HoldTime[3] = atof(m_HoldTime4);
	}
	else
	{
		pDoc->m_Setting2[m_DlgIdx].m_HoldTime[3] = -1;
	}
	if(pDoc->m_Setting2[m_DlgIdx].m_HoldTimeNum>4)
	{
		pDoc->m_Setting2[m_DlgIdx].m_HoldTime[4] = atof(m_HoldTime5);
	}
	else
	{
		pDoc->m_Setting2[m_DlgIdx].m_HoldTime[4] = -1;
	}
	if(pDoc->m_Setting2[m_DlgIdx].m_HoldTimeNum>5)
	{
		pDoc->m_Setting2[m_DlgIdx].m_HoldTime[5] = atof(m_HoldTime6);
	}
	else
	{
		pDoc->m_Setting2[m_DlgIdx].m_HoldTime[5] = -1;
	}
	if(pDoc->m_Setting2[m_DlgIdx].m_HoldTimeNum>6)
	{
		pDoc->m_Setting2[m_DlgIdx].m_HoldTime[6] = atof(m_HoldTime7);
	}
	else
	{
		pDoc->m_Setting2[m_DlgIdx].m_HoldTime[6] = -1;
	}
	if(pDoc->m_Setting2[m_DlgIdx].m_HoldTimeNum>7)
	{
		pDoc->m_Setting2[m_DlgIdx].m_HoldTime[7] = atof(m_HoldTime8);
	}
	else
	{
		pDoc->m_Setting2[m_DlgIdx].m_HoldTime[7] = -1;
	}
	if(pDoc->m_Setting2[m_DlgIdx].m_HoldTimeNum>8)
	{
		pDoc->m_Setting2[m_DlgIdx].m_HoldTime[8] = atof(m_HoldTime9);
	}
	else
	{
		pDoc->m_Setting2[m_DlgIdx].m_HoldTime[8] = -1;
	}
	if(pDoc->m_Setting2[m_DlgIdx].m_HoldTimeNum>9)
	{
		pDoc->m_Setting2[m_DlgIdx].m_HoldTime[9] = atof(m_HoldTime10);
	}
	else
	{
		pDoc->m_Setting2[m_DlgIdx].m_HoldTime[9] = -1;
	}
	if(pDoc->m_Setting2[m_DlgIdx].m_HoldTimeNum>10)
	{
		pDoc->m_Setting2[m_DlgIdx].m_HoldTime[10] = atof(m_HoldTime11);
	}
	else
	{
		pDoc->m_Setting2[m_DlgIdx].m_HoldTime[10] = -1;
	}
		if(pDoc->m_Setting2[m_DlgIdx].m_HoldTimeNum>11)
	{
		pDoc->m_Setting2[m_DlgIdx].m_HoldTime[11] = atof(m_HoldTime12);
	}
	else
	{
		pDoc->m_Setting2[m_DlgIdx].m_HoldTime[11] = -1;
	}

}

void CSettingDlg2::OnPracmode() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

}

void CSettingDlg2::OnExpermode() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetDlgItem(IDC_EXPERTIMESSTATIC)->EnableWindow(m_ExperMode);
	GetDlgItem(IDC_EXPERTIMES)->EnableWindow(m_ExperMode);
	GetDlgItem(IDC_EXPERTIMESTATIC)->EnableWindow(m_ExperMode);
	GetDlgItem(IDC_EXPERTIME)->EnableWindow(m_ExperMode);
	GetDlgItem(IDC_EXPERTIMEUNITSTATIC)->EnableWindow(m_ExperMode);

}


void CSettingDlg2::OnSelchangeHoldtimenum() 
{
	// TODO: Add your control notification handler code here
    CComboBox* m_HoldTimeCom;
	m_HoldTimeCom = (CComboBox*)GetDlgItem(IDC_HOLDTIMENUM);    
	short holdtimenum = m_HoldTimeCom->GetCurSel()+1;
	int i;
	for(i=0;i<holdtimenum;i++)
	{
        GetDlgItem(m_HoldTimeStatic[i])->EnableWindow(TRUE);
	    GetDlgItem(m_HoldTime[i])->EnableWindow(TRUE);	
		GetDlgItem(m_HoldTimeUnitStatic[i])->EnableWindow(TRUE);	
	}
	for(i=holdtimenum;i<12;i++)
	{
        GetDlgItem(m_HoldTimeStatic[i])->EnableWindow(FALSE);
	    GetDlgItem(m_HoldTime[i])->EnableWindow(FALSE);	
		GetDlgItem(m_HoldTimeUnitStatic[i])->EnableWindow(FALSE);	
	}
}

void CSettingDlg2::OnMaintask() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	/*GetDlgItem(IDC_MAINTASKSTATIC)->EnableWindow(m_MainTask);
	GetDlgItem(IDC_DIRECTIONSTATIC)->EnableWindow(m_MainTask);
	GetDlgItem(IDC_DIRECTION0)->EnableWindow(m_MainTask);
	GetDlgItem(IDC_DIRECTION1)->EnableWindow(m_MainTask);
	GetDlgItem(IDC_INITSPEEDSTATIC)->EnableWindow(m_MainTask);
	GetDlgItem(IDC_INITSPEED)->EnableWindow(m_MainTask);
	GetDlgItem(IDC_INITSPEEDUNIT)->EnableWindow(m_MainTask);
	GetDlgItem(IDC_PRACTIMESTATIC)->EnableWindow(m_MainTask&&m_PracMode&&!m_SubTask);
	GetDlgItem(IDC_PRACTIME)->EnableWindow(m_MainTask);

	GetDlgItem(IDC_PRACTIMEUNITSTATIC)->EnableWindow(m_MainTask&&m_PracMode&&!m_SubTask);	
	GetDlgItem(IDC_EXPERTIMESTATIC)->EnableWindow(m_MainTask&&m_ExperMode&&!m_SubTask);
	GetDlgItem(IDC_EXPERTIME)->EnableWindow(m_MainTask&&m_ExperMode&&!m_SubTask);
	GetDlgItem(IDC_EXPERTIMEUNITSTATIC)->EnableWindow(m_MainTask&&m_ExperMode&&!m_SubTask);*/
}

void CSettingDlg2::OnSubtask() 
{
	// TODO: Add your control notification handler code here
    int i;
	UpdateData(TRUE);
    CComboBox* m_HoldTimeCom;
	m_HoldTimeCom = (CComboBox*)GetDlgItem(IDC_HOLDTIMENUM);    
	short holdtimenum = m_HoldTimeCom->GetCurSel()+1;

	GetDlgItem(IDC_SUBTASKSTATIC)->EnableWindow(m_SubTask);
	GetDlgItem(IDC_HOLDTIMENUMSTATIC)->EnableWindow(m_SubTask);
	GetDlgItem(IDC_HOLDTIMENUM)->EnableWindow(m_SubTask);
	for(i=0;i<holdtimenum;i++)
	{
        GetDlgItem(m_HoldTimeStatic[i])->EnableWindow(m_SubTask&&TRUE);
	    GetDlgItem(m_HoldTime[i])->EnableWindow(m_SubTask&&TRUE);	
		GetDlgItem(m_HoldTimeUnitStatic[i])->EnableWindow(m_SubTask&&TRUE);	
	}
	for(i=holdtimenum;i<12;i++)
	{
        GetDlgItem(m_HoldTimeStatic[i])->EnableWindow(m_SubTask&&FALSE);
	    GetDlgItem(m_HoldTime[i])->EnableWindow(m_SubTask&&FALSE);	
		GetDlgItem(m_HoldTimeUnitStatic[i])->EnableWindow(m_SubTask&&FALSE);	
	}
	/*GetDlgItem(IDC_PRACTIMESSTATIC)->EnableWindow(m_SubTask);
	GetDlgItem(IDC_PRACTIMES)->EnableWindow(m_SubTask);
	GetDlgItem(IDC_EXPERTIMESSTATIC)->EnableWindow(m_SubTask);
	GetDlgItem(IDC_EXPERTIMES)->EnableWindow(m_SubTask);	
	GetDlgItem(IDC_PRACTIMESTATIC)->EnableWindow(m_MainTask&&m_PracMode&&!m_SubTask);
	GetDlgItem(IDC_PRACTIME)->EnableWindow(m_MainTask&&m_PracMode&&!m_SubTask);
	GetDlgItem(IDC_PRACTIMEUNITSTATIC)->EnableWindow(m_MainTask&&m_PracMode&&!m_SubTask);	
	GetDlgItem(IDC_EXPERTIMESTATIC)->EnableWindow(m_MainTask&&m_ExperMode&&!m_SubTask);
	GetDlgItem(IDC_EXPERTIME)->EnableWindow(m_MainTask&&m_ExperMode&&!m_SubTask);
	GetDlgItem(IDC_EXPERTIMEUNITSTATIC)->EnableWindow(m_MainTask&&m_ExperMode&&!m_SubTask);*/
}


HBRUSH CSettingDlg2::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_EDIT){
		pDC->SetBkColor(RGB(255,255,255));
	}
	return hbr;
}


void CSettingDlg2::OnBnClickedSpeedmode0()
{
	// TODO: Add your control notification handler code here
	// 初始化速度设置的enable和disable
	UpdateData(TRUE);
	GetDlgItem(IDC_SPEEDSTATIC)->EnableWindow(!m_bSpeedMode);
	GetDlgItem(IDC_SPEED)->EnableWindow(!m_bSpeedMode);
	GetDlgItem(IDC_SPEEDUNITSTATIC)->EnableWindow(!m_bSpeedMode);
	GetDlgItem(IDC_INITSPEEDSTATIC2)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_INITSPEED)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_INITSPEEDUNITSTATIC)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_SPEEDMAXSTATIC)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_SPEEDMIN)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_SPEEDMIDSTATIC)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_SPEEDMAX2)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_SPEEDMAXUNITSTATIC)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_ACCELERATIONSTATIC)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_ACCELERATIONMIN)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_ACCELERATIONMIDSTATIC)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_ACCELERATIONMAX)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_ACCELERATIONUNITSTATIC)->EnableWindow(m_bSpeedMode);


}


void CSettingDlg2::OnBnClickedSpeedmode1()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetDlgItem(IDC_SPEEDSTATIC)->EnableWindow(!m_bSpeedMode);
	GetDlgItem(IDC_SPEED)->EnableWindow(!m_bSpeedMode);
	GetDlgItem(IDC_SPEEDUNITSTATIC)->EnableWindow(!m_bSpeedMode);
	GetDlgItem(IDC_INITSPEEDSTATIC2)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_INITSPEED)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_INITSPEEDUNITSTATIC)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_SPEEDMAXSTATIC)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_SPEEDMIN)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_SPEEDMIDSTATIC)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_SPEEDMAX2)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_SPEEDMAXUNITSTATIC)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_ACCELERATIONSTATIC)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_ACCELERATIONMIN)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_ACCELERATIONMIDSTATIC)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_ACCELERATIONMAX)->EnableWindow(m_bSpeedMode);
	GetDlgItem(IDC_ACCELERATIONUNITSTATIC)->EnableWindow(m_bSpeedMode);

}
