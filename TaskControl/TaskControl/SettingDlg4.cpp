// SettingDlg4.cpp : implementation file
//

#include "stdafx.h"
#include "TaskControl.h"
#include "SettingDlg4.h"
#include "MainFrm.h"
#include "TaskControlDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg4 dialog


CSettingDlg4::CSettingDlg4(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingDlg4::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSettingDlg4)
	m_TouchOrder = 0;
	m_PracMode = FALSE;
	m_ExperMode = FALSE;
	m_PracTimes = _T("");
	m_ExperTimes = _T("");
	m_TaskName = _T("");
	//}}AFX_DATA_INIT
}


void CSettingDlg4::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingDlg4)
	DDX_Control(pDX, IDC_BACKGROUND, m_Background);
	DDX_Radio(pDX, IDC_TOUCHORDER0, m_TouchOrder);
	DDX_Check(pDX, IDC_PRACMODE, m_PracMode);
	DDX_Check(pDX, IDC_EXPERMODE, m_ExperMode);
	DDX_CBString(pDX, IDC_PRACTIMES, m_PracTimes);
	DDX_CBString(pDX, IDC_EXPERTIMES, m_ExperTimes);
	DDX_Text(pDX, IDC_TASKNAME, m_TaskName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSettingDlg4, CDialog)
	//{{AFX_MSG_MAP(CSettingDlg4)
	ON_BN_CLICKED(IDC_PRACMODE, OnPracmode)
	ON_BN_CLICKED(IDC_EXPERMODE, OnExpermode)
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg4 message handlers

BOOL CSettingDlg4::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
    CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();

	m_TaskName = pDoc->m_Setting4[m_DlgIdx].m_TaskName;
	m_PracMode = pDoc->m_Setting4[m_DlgIdx].m_PracMode;
    m_ExperMode = pDoc->m_Setting4[m_DlgIdx].m_ExperMode;
    
	m_Background.InsertString(0,"灰黑色");
	m_Background.InsertString(1,"蓝黑色");
    m_Background.SetCurSel(pDoc->m_Setting4[m_DlgIdx].m_Background);

	m_TouchOrder = pDoc->m_Setting4[m_DlgIdx].m_TouchOrder;
    m_PracTimes.Format("%d", pDoc->m_Setting4[m_DlgIdx].m_PracTimes);
	m_ExperTimes.Format("%d", pDoc->m_Setting4[m_DlgIdx].m_ExperTimes);

	GetDlgItem(IDC_PRACTIMESSTATIC)->EnableWindow(pDoc->m_Setting4[m_DlgIdx].m_PracMode);
	GetDlgItem(IDC_PRACTIMES)->EnableWindow(pDoc->m_Setting4[m_DlgIdx].m_PracMode);
	GetDlgItem(IDC_EXPERTIMESSTATIC)->EnableWindow(pDoc->m_Setting4[m_DlgIdx].m_ExperMode);
	GetDlgItem(IDC_EXPERTIMES)->EnableWindow(pDoc->m_Setting4[m_DlgIdx].m_ExperMode);

	UpdateData(FALSE);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSettingDlg4::Save() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
    CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();

	strcpy_s(pDoc->m_Setting4[m_DlgIdx].m_TaskName, 100,m_TaskName);
    pDoc->m_Setting4[m_DlgIdx].m_PracMode = m_PracMode;
	pDoc->m_Setting4[m_DlgIdx].m_ExperMode = m_ExperMode;
	pDoc->m_Setting4[m_DlgIdx].m_Background = m_Background.GetCurSel();
	pDoc->m_Setting4[m_DlgIdx].m_TouchOrder = m_TouchOrder;
	pDoc->m_Setting4[m_DlgIdx].m_PracTimes = atoi(m_PracTimes);
	pDoc->m_Setting4[m_DlgIdx].m_ExperTimes = atoi(m_ExperTimes);	
}

void CSettingDlg4::OnPracmode() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetDlgItem(IDC_PRACTIMESSTATIC)->EnableWindow(m_PracMode);
	GetDlgItem(IDC_PRACTIMES)->EnableWindow(m_PracMode);			
}

void CSettingDlg4::OnExpermode() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetDlgItem(IDC_EXPERTIMESSTATIC)->EnableWindow(m_ExperMode);
	GetDlgItem(IDC_EXPERTIMES)->EnableWindow(m_ExperMode);	
}


HBRUSH CSettingDlg4::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_EDIT){
		pDC->SetBkColor(RGB(255,255,255));
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
