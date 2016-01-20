// SettingDlg5.cpp : implementation file
//

#include "stdafx.h"
#include "TaskControl.h"
#include "SettingDlg5.h"
#include "MainFrm.h"
#include "TaskControlDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg5 dialog


CSettingDlg5::CSettingDlg5(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingDlg5::IDD, pParent)
	, m_iJoyMoveDirection(0)
{
	//{{AFX_DATA_INIT(CSettingDlg5)
	m_SignMemMode = -1;
	m_SignShowMode = -1;
	m_PracMode = FALSE;
	m_ExperMode = FALSE;
	m_InitSpeed = _T("");
	m_MainTask = FALSE;
	m_SubTask = FALSE;
	m_ExperTimes = _T("");
	m_PracTimes = _T("");
	m_SignMemNum = _T("");
	m_PracTime = _T("");
	m_ExperTime = _T("");
	m_SignShowTime = _T("");
	m_TaskName = _T("");
	//}}AFX_DATA_INIT
}


void CSettingDlg5::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingDlg5)
	DDX_Control(pDX, IDC_SIGNMEMTYPE, m_SignMemType);
	DDX_Control(pDX, IDC_BACKGROUND, m_Background);
	DDX_Radio(pDX, IDC_SIGNMEMMODE0, m_SignMemMode);
	DDX_Radio(pDX, IDC_SIGNSHOWMODE0, m_SignShowMode);
	DDX_Check(pDX, IDC_PRACMODE, m_PracMode);
	DDX_Check(pDX, IDC_EXPERMODE, m_ExperMode);
	DDX_CBString(pDX, IDC_INITSPEED, m_InitSpeed);
	DDX_Check(pDX, IDC_MAINTASK, m_MainTask);
	DDX_Check(pDX, IDC_SUBTASK, m_SubTask);
	DDX_CBString(pDX, IDC_EXPERTIMES, m_ExperTimes);
	DDX_CBString(pDX, IDC_PRACTIMES, m_PracTimes);
	DDX_CBString(pDX, IDC_SIGNMEMNUM, m_SignMemNum);
	DDX_CBString(pDX, IDC_PRACTIME, m_PracTime);
	DDX_CBString(pDX, IDC_EXPERTIME, m_ExperTime);
	DDX_CBString(pDX, IDC_SIGNSHOWTIME, m_SignShowTime);
	DDX_Text(pDX, IDC_TASKNAME, m_TaskName);
	//}}AFX_DATA_MAP
	DDX_Radio(pDX, IDC_JOY_MOVE_POS, m_iJoyMoveDirection);
}


BEGIN_MESSAGE_MAP(CSettingDlg5, CDialog)
	//{{AFX_MSG_MAP(CSettingDlg5)
	ON_BN_CLICKED(IDC_PRACMODE, OnPracmode)
	ON_BN_CLICKED(IDC_EXPERMODE, OnExpermode)
	ON_BN_CLICKED(IDC_MAINTASK, OnMaintask)
	ON_BN_CLICKED(IDC_SUBTASK, OnSubtask)
	ON_BN_CLICKED(IDC_SIGNMEMMODE0, OnSignmemmode0)
	ON_BN_CLICKED(IDC_SIGNMEMMODE1, OnSignmemmode1)
	ON_BN_CLICKED(IDC_SIGNSHOWMODE0, OnSignshowmode0)
	ON_BN_CLICKED(IDC_SIGNSHOWMODE1, OnSignshowmode1)
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg5 message handlers

void CSettingDlg5::Save() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
    CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();

	strcpy_s(pDoc->m_Setting5[m_DlgIdx].m_TaskName,100, m_TaskName);
	pDoc->m_Setting5[m_DlgIdx].m_iJoyMoveDirection = m_iJoyMoveDirection;
    pDoc->m_Setting5[m_DlgIdx].m_PracMode = m_PracMode;
	pDoc->m_Setting5[m_DlgIdx].m_ExperMode = m_ExperMode;
	pDoc->m_Setting5[m_DlgIdx].m_MainTask = m_MainTask;
    pDoc->m_Setting5[m_DlgIdx].m_SubTask = m_SubTask;
	pDoc->m_Setting5[m_DlgIdx].m_Background = m_Background.GetCurSel();
	if(pDoc->m_Setting5[m_DlgIdx].m_MainTask)
	{
		pDoc->m_Setting5[m_DlgIdx].m_InitSpeed = atof(m_InitSpeed);
	}
	else
	{
        pDoc->m_Setting5[m_DlgIdx].m_InitSpeed = -1;
	}
	if(pDoc->m_Setting5[m_DlgIdx].m_SubTask)
	{
		pDoc->m_Setting5[m_DlgIdx].m_SignMemType = m_SignMemType.GetCurSel();
	    pDoc->m_Setting5[m_DlgIdx].m_SignMemMode = m_SignMemMode;
	}
	else
	{
		pDoc->m_Setting5[m_DlgIdx].m_SignMemType = -1;
	    pDoc->m_Setting5[m_DlgIdx].m_SignMemMode = -1;
	}
	if((!pDoc->m_Setting5[m_DlgIdx].m_SignMemMode)&&pDoc->m_Setting5[m_DlgIdx].m_SubTask)
	{
		pDoc->m_Setting5[m_DlgIdx].m_SignMemNum = atoi(m_SignMemNum);
	}
	else
	{
		pDoc->m_Setting5[m_DlgIdx].m_SignMemNum = -1;
	}
	if(pDoc->m_Setting5[m_DlgIdx].m_SubTask)
	{
		pDoc->m_Setting5[m_DlgIdx].m_SignShowMode = m_SignShowMode;
	}
	else
	{
		pDoc->m_Setting5[m_DlgIdx].m_SignShowMode = -1;
	}
	if(pDoc->m_Setting5[m_DlgIdx].m_SignShowMode&&pDoc->m_Setting5[m_DlgIdx].m_SubTask)
	{
		pDoc->m_Setting5[m_DlgIdx].m_SignShowTime = atof(m_SignShowTime);
	}
	else
	{
        pDoc->m_Setting5[m_DlgIdx].m_SignShowTime = -1;
	}
	if(pDoc->m_Setting5[m_DlgIdx].m_MainTask&&pDoc->m_Setting5[m_DlgIdx].m_PracMode&&!pDoc->m_Setting5[m_DlgIdx].m_SubTask)
	{
		pDoc->m_Setting5[m_DlgIdx].m_PracTime = atoi(m_PracTime);
	}
	else
	{
        pDoc->m_Setting5[m_DlgIdx].m_PracTime = -1;
	}
	if(pDoc->m_Setting5[m_DlgIdx].m_MainTask&&pDoc->m_Setting5[m_DlgIdx].m_ExperMode&&!pDoc->m_Setting5[m_DlgIdx].m_SubTask)
	{
		pDoc->m_Setting5[m_DlgIdx].m_ExperTime = atoi(m_ExperTime);
	}
	else
	{
        pDoc->m_Setting5[m_DlgIdx].m_ExperTime = -1;
	}
	if(pDoc->m_Setting5[m_DlgIdx].m_SubTask&&pDoc->m_Setting5[m_DlgIdx].m_PracMode)
	{
		pDoc->m_Setting5[m_DlgIdx].m_PracTimes = atoi(m_PracTimes);
	}
	else
	{
		pDoc->m_Setting5[m_DlgIdx].m_PracTimes = -1;
	}
	if(pDoc->m_Setting5[m_DlgIdx].m_SubTask&&pDoc->m_Setting5[m_DlgIdx].m_ExperMode)
	{
    	pDoc->m_Setting5[m_DlgIdx].m_ExperTimes = atoi(m_ExperTimes);
	}
	else
	{
    	pDoc->m_Setting5[m_DlgIdx].m_ExperTimes = -1;
	}
}

BOOL CSettingDlg5::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
    CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();

	m_iJoyMoveDirection = pDoc->m_Setting5[m_DlgIdx].m_iJoyMoveDirection;
	m_TaskName = pDoc->m_Setting5[m_DlgIdx].m_TaskName;
	m_PracMode = pDoc->m_Setting5[m_DlgIdx].m_PracMode;
    m_ExperMode = pDoc->m_Setting5[m_DlgIdx].m_ExperMode;
	m_MainTask = pDoc->m_Setting5[m_DlgIdx].m_MainTask;
    m_SubTask = pDoc->m_Setting5[m_DlgIdx].m_SubTask;
	
	m_Background.InsertString(0,"»ÒºÚÉ«");
	m_Background.InsertString(1,"À¶ºÚÉ«");
    m_Background.SetCurSel(pDoc->m_Setting5[m_DlgIdx].m_Background);

	m_InitSpeed.Format("%.1f", pDoc->m_Setting5[m_DlgIdx].m_InitSpeed);

	m_SignMemType.InsertString(0,"×Ö·û");
	m_SignMemType.InsertString(1,"Í¼±ê");
	m_SignMemType.InsertString(2,"Í¼Æ¬");
    m_SignMemType.SetCurSel(pDoc->m_Setting5[m_DlgIdx].m_SignMemType);

	m_SignMemMode = pDoc->m_Setting5[m_DlgIdx].m_SignMemMode;
	CComboBox* m_SignMemNumCom = (CComboBox*)GetDlgItem(IDC_SIGNMEMNUM);
	m_SignMemNumCom->InsertString(0,"4");
	m_SignMemNumCom->InsertString(1,"5");
	m_SignMemNumCom->InsertString(2,"6");
	m_SignMemNumCom->InsertString(3,"7");
	m_SignMemNumCom->InsertString(4,"8");

	m_SignMemNum.Format("%d", pDoc->m_Setting5[m_DlgIdx].m_SignMemNum);
 	m_SignShowMode = pDoc->m_Setting5[m_DlgIdx].m_SignShowMode;
 	m_SignShowTime.Format("%.1f", pDoc->m_Setting5[m_DlgIdx].m_SignShowTime);
    m_PracTime.Format("%d", pDoc->m_Setting5[m_DlgIdx].m_PracTime);
	m_ExperTime.Format("%d", pDoc->m_Setting5[m_DlgIdx].m_ExperTime);
    m_PracTimes.Format("%d", pDoc->m_Setting5[m_DlgIdx].m_PracTimes);
	m_ExperTimes.Format("%d", pDoc->m_Setting5[m_DlgIdx].m_ExperTimes);

	GetDlgItem(IDC_MAINTASKSTATIC)->EnableWindow(pDoc->m_Setting5[m_DlgIdx].m_MainTask);
	GetDlgItem(IDC_INITSPEEDSTATIC)->EnableWindow(pDoc->m_Setting5[m_DlgIdx].m_MainTask);
	GetDlgItem(IDC_INITSPEED)->EnableWindow(pDoc->m_Setting5[m_DlgIdx].m_MainTask);
	GetDlgItem(IDC_SPEEDUNITSTATIC)->EnableWindow(pDoc->m_Setting5[m_DlgIdx].m_MainTask);
	GetDlgItem(IDC_PRACTIMESTATIC)->EnableWindow(pDoc->m_Setting5[m_DlgIdx].m_MainTask&&pDoc->m_Setting5[m_DlgIdx].m_PracMode&&!pDoc->m_Setting5[m_DlgIdx].m_SubTask);
	GetDlgItem(IDC_PRACTIME)->EnableWindow(pDoc->m_Setting5[m_DlgIdx].m_MainTask&&pDoc->m_Setting5[m_DlgIdx].m_PracMode&&!pDoc->m_Setting5[m_DlgIdx].m_SubTask);
	GetDlgItem(IDC_PRACTIMEUNITSTATIC)->EnableWindow(pDoc->m_Setting5[m_DlgIdx].m_MainTask&&pDoc->m_Setting5[m_DlgIdx].m_PracMode&&!pDoc->m_Setting5[m_DlgIdx].m_SubTask);
	GetDlgItem(IDC_EXPERTIMESTATIC)->EnableWindow(pDoc->m_Setting5[m_DlgIdx].m_MainTask&&pDoc->m_Setting5[m_DlgIdx].m_ExperMode&&!pDoc->m_Setting5[m_DlgIdx].m_SubTask);
	GetDlgItem(IDC_EXPERTIME)->EnableWindow(pDoc->m_Setting5[m_DlgIdx].m_MainTask&&pDoc->m_Setting5[m_DlgIdx].m_ExperMode&&!pDoc->m_Setting5[m_DlgIdx].m_SubTask);
    GetDlgItem(IDC_EXPERTIMEUNITSTATIC)->EnableWindow(pDoc->m_Setting5[m_DlgIdx].m_MainTask&&pDoc->m_Setting5[m_DlgIdx].m_ExperMode&&!pDoc->m_Setting5[m_DlgIdx].m_SubTask);
	
	GetDlgItem(IDC_SIGNMEMTYPESTATIC)->EnableWindow(pDoc->m_Setting5[m_DlgIdx].m_SubTask);
    GetDlgItem(IDC_SIGNMEMTYPE)->EnableWindow(pDoc->m_Setting5[m_DlgIdx].m_SubTask);
	GetDlgItem(IDC_SUBTASKSTATIC)->EnableWindow(pDoc->m_Setting5[m_DlgIdx].m_SubTask);
	GetDlgItem(IDC_SIGNMEMMODESTATIC)->EnableWindow(pDoc->m_Setting5[m_DlgIdx].m_SubTask);
	GetDlgItem(IDC_SIGNMEMMODE0)->EnableWindow(pDoc->m_Setting5[m_DlgIdx].m_SubTask);
	GetDlgItem(IDC_SIGNMEMNUM)->EnableWindow((!pDoc->m_Setting5[m_DlgIdx].m_SignMemMode)&&pDoc->m_Setting5[m_DlgIdx].m_SubTask);	
	GetDlgItem(IDC_SIGNMEMMODE1)->EnableWindow(pDoc->m_Setting5[m_DlgIdx].m_SubTask);
	GetDlgItem(IDC_SIGNSHOWMODESTATIC)->EnableWindow(pDoc->m_Setting5[m_DlgIdx].m_SubTask);
	GetDlgItem(IDC_SIGNSHOWMODE0)->EnableWindow(pDoc->m_Setting5[m_DlgIdx].m_SubTask);
	GetDlgItem(IDC_SIGNSHOWTIME)->EnableWindow(pDoc->m_Setting5[m_DlgIdx].m_SignShowMode&&pDoc->m_Setting5[m_DlgIdx].m_SubTask);	
	GetDlgItem(IDC_SIGNSHOWTIMEUNITSTATIC)->EnableWindow(pDoc->m_Setting5[m_DlgIdx].m_SignShowMode&&pDoc->m_Setting5[m_DlgIdx].m_SubTask);	
	GetDlgItem(IDC_SIGNSHOWMODE1)->EnableWindow(pDoc->m_Setting5[m_DlgIdx].m_SubTask);
	GetDlgItem(IDC_PRACTIMESSTATIC)->EnableWindow(pDoc->m_Setting5[m_DlgIdx].m_SubTask&&pDoc->m_Setting5[m_DlgIdx].m_PracMode);
	GetDlgItem(IDC_PRACTIMES)->EnableWindow(pDoc->m_Setting5[m_DlgIdx].m_SubTask&&pDoc->m_Setting5[m_DlgIdx].m_PracMode);
	GetDlgItem(IDC_EXPERTIMESSTATIC)->EnableWindow(pDoc->m_Setting5[m_DlgIdx].m_SubTask&&pDoc->m_Setting5[m_DlgIdx].m_ExperMode);
	GetDlgItem(IDC_EXPERTIMES)->EnableWindow(pDoc->m_Setting5[m_DlgIdx].m_SubTask&&pDoc->m_Setting5[m_DlgIdx].m_ExperMode);

	UpdateData(FALSE);	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSettingDlg5::OnPracmode() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetDlgItem(IDC_PRACTIMESTATIC)->EnableWindow(m_MainTask&&m_PracMode&&!m_SubTask);
	GetDlgItem(IDC_PRACTIME)->EnableWindow(m_MainTask&&m_PracMode&&!m_SubTask);
	GetDlgItem(IDC_PRACTIMEUNITSTATIC)->EnableWindow(m_MainTask&&m_PracMode&&!m_SubTask);
	GetDlgItem(IDC_PRACTIMESSTATIC)->EnableWindow(m_SubTask&&m_PracMode);
	GetDlgItem(IDC_PRACTIMES)->EnableWindow(m_SubTask&&m_PracMode);	
}

void CSettingDlg5::OnExpermode() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetDlgItem(IDC_EXPERTIMESTATIC)->EnableWindow(m_MainTask&&m_ExperMode&&!m_SubTask);
	GetDlgItem(IDC_EXPERTIME)->EnableWindow(m_MainTask&&m_ExperMode&&!m_SubTask);
	GetDlgItem(IDC_EXPERTIMEUNITSTATIC)->EnableWindow(m_MainTask&&m_ExperMode&&!m_SubTask);
	GetDlgItem(IDC_EXPERTIMESSTATIC)->EnableWindow(m_SubTask&&m_ExperMode);
	GetDlgItem(IDC_EXPERTIMES)->EnableWindow(m_SubTask&&m_ExperMode);	
}

void CSettingDlg5::OnMaintask() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetDlgItem(IDC_MAINTASKSTATIC)->EnableWindow(m_MainTask);
	GetDlgItem(IDC_INITSPEEDSTATIC)->EnableWindow(m_MainTask);
	GetDlgItem(IDC_INITSPEED)->EnableWindow(m_MainTask);
	GetDlgItem(IDC_SPEEDUNITSTATIC)->EnableWindow(m_MainTask);
	GetDlgItem(IDC_PRACTIMESTATIC)->EnableWindow(m_MainTask&&m_PracMode&&!m_SubTask);
	GetDlgItem(IDC_PRACTIME)->EnableWindow(m_MainTask&&m_PracMode&&!m_SubTask);
	GetDlgItem(IDC_PRACTIMEUNITSTATIC)->EnableWindow(m_MainTask&&m_PracMode&&!m_SubTask);
	GetDlgItem(IDC_EXPERTIMESTATIC)->EnableWindow(m_MainTask&&m_ExperMode&&!m_SubTask);
	GetDlgItem(IDC_EXPERTIME)->EnableWindow(m_MainTask&&m_ExperMode&&!m_SubTask);	
    GetDlgItem(IDC_EXPERTIMEUNITSTATIC)->EnableWindow(m_MainTask&&m_ExperMode&&!m_SubTask);
}

void CSettingDlg5::OnSubtask() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetDlgItem(IDC_SIGNMEMTYPESTATIC)->EnableWindow(m_SubTask);
    GetDlgItem(IDC_SIGNMEMTYPE)->EnableWindow(m_SubTask);
	GetDlgItem(IDC_SUBTASKSTATIC)->EnableWindow(m_SubTask);
	GetDlgItem(IDC_SIGNMEMMODESTATIC)->EnableWindow(m_SubTask);
	GetDlgItem(IDC_SIGNMEMMODE0)->EnableWindow(m_SubTask);
	GetDlgItem(IDC_SIGNMEMNUM)->EnableWindow((!m_SignMemMode)&&m_SubTask);	
	GetDlgItem(IDC_SIGNMEMMODE1)->EnableWindow(m_SubTask);
	GetDlgItem(IDC_SIGNSHOWMODESTATIC)->EnableWindow(m_SubTask);
	GetDlgItem(IDC_SIGNSHOWMODE0)->EnableWindow(m_SubTask);
	GetDlgItem(IDC_SIGNSHOWTIME)->EnableWindow(m_SignShowMode&&m_SubTask);	
	GetDlgItem(IDC_SIGNSHOWTIMEUNITSTATIC)->EnableWindow(m_SignShowMode&&m_SubTask);	
	GetDlgItem(IDC_SIGNSHOWMODE1)->EnableWindow(m_SubTask);
	GetDlgItem(IDC_PRACTIMESSTATIC)->EnableWindow(m_SubTask&&m_PracMode);
	GetDlgItem(IDC_PRACTIMES)->EnableWindow(m_SubTask&&m_PracMode);
	GetDlgItem(IDC_EXPERTIMESSTATIC)->EnableWindow(m_SubTask&&m_ExperMode);
	GetDlgItem(IDC_EXPERTIMES)->EnableWindow(m_SubTask&&m_ExperMode);
	GetDlgItem(IDC_PRACTIMESTATIC)->EnableWindow(m_MainTask&&m_PracMode&&!m_SubTask);
	GetDlgItem(IDC_PRACTIME)->EnableWindow(m_MainTask&&m_PracMode&&!m_SubTask);
	GetDlgItem(IDC_PRACTIMEUNITSTATIC)->EnableWindow(m_MainTask&&m_PracMode&&!m_SubTask);
	GetDlgItem(IDC_EXPERTIMESTATIC)->EnableWindow(m_MainTask&&m_ExperMode)&&!m_SubTask;
	GetDlgItem(IDC_EXPERTIME)->EnableWindow(m_MainTask&&m_ExperMode&&!m_SubTask);	
    GetDlgItem(IDC_EXPERTIMEUNITSTATIC)->EnableWindow(m_MainTask&&m_ExperMode&&!m_SubTask);

}

void CSettingDlg5::OnSignmemmode0() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetDlgItem(IDC_SIGNMEMNUM)->EnableWindow((!m_SignMemMode)&&m_SubTask);	
}

void CSettingDlg5::OnSignmemmode1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetDlgItem(IDC_SIGNMEMNUM)->EnableWindow((!m_SignMemMode)&&m_SubTask);	
}

void CSettingDlg5::OnSignshowmode0() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetDlgItem(IDC_SIGNSHOWTIME)->EnableWindow(m_SignShowMode&&m_SubTask);	
    GetDlgItem(IDC_SIGNSHOWTIMEUNITSTATIC)->EnableWindow(m_SignShowMode&&m_SubTask);	
}

void CSettingDlg5::OnSignshowmode1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetDlgItem(IDC_SIGNSHOWTIME)->EnableWindow(m_SignShowMode&&m_SubTask);	
    GetDlgItem(IDC_SIGNSHOWTIMEUNITSTATIC)->EnableWindow(m_SignShowMode&&m_SubTask);		
}


HBRUSH CSettingDlg5::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_EDIT){
		pDC->SetBkColor(RGB(255,255,255));
	}
	return hbr;
}
