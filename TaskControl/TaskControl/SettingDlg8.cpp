// SettingDlg8.cpp : 实现文件
//

#include "stdafx.h"
#include "TaskControl.h"
#include "SettingDlg8.h"
#include "afxdialogex.h"
#include "MainFrm.h"


// CSettingDlg8 对话框

IMPLEMENT_DYNAMIC(CSettingDlg8, CDialog)

CSettingDlg8::CSettingDlg8(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_SETTINGDLG8, pParent)
{

}

CSettingDlg8::~CSettingDlg8()
{
}

void CSettingDlg8::DoDataExchange(CDataExchange* pDX)
{
	
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TASKNAME, m_szTaskName);
	//DDX_Check(pDX, IDC_PRACMODE, m_bPracMode);
	DDX_Text(pDX, IDC_PRESENT_TIME, m_iPrensentTime);
	DDX_Text(pDX, IDC_FOCUS_TIME, m_iFocusTime);
	DDX_Text(pDX, IDC_COUNTDOWN_TIME, m_iCountdownTime);

}


BEGIN_MESSAGE_MAP(CSettingDlg8, CDialog)
	ON_STN_CLICKED(IDC_CUBENUMSTATIC2, &CSettingDlg8::OnStnClickedCubenumstatic2)
END_MESSAGE_MAP()


// CSettingDlg8 消息处理程序


BOOL CSettingDlg8::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	// get doc ptr
	CMainFrame*   pMain = (CMainFrame*)AfxGetMainWnd();
	CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();
	
	// set default parameters
	m_szTaskName = pDoc->m_Setting8[m_DlgIdx].m_TaskName;
	//m_bPracMode = pDoc->m_Setting8[m_DlgIdx].m_bPracMode;
	m_iFocusTime = pDoc->m_Setting8[m_DlgIdx].m_iFocusTime;
	m_iPrensentTime = pDoc->m_Setting8[m_DlgIdx].m_iPrensentTime;
	m_iCountdownTime = pDoc->m_Setting8[m_DlgIdx].m_iCountdownTime;
	
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CSettingDlg8::Save() {
	UpdateData(TRUE);
	
	// Get pDoc ptr
	CMainFrame*   pMain = (CMainFrame*)AfxGetMainWnd();
	CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();
	
	// Save para to pDoc
	//pDoc->m_Setting8[m_DlgIdx].m_bPracMode = m_bPracMode;
	pDoc->m_Setting8[m_DlgIdx].m_iCountdownTime = m_iCountdownTime;
	pDoc->m_Setting8[m_DlgIdx].m_iFocusTime = m_iFocusTime;
	pDoc->m_Setting8[m_DlgIdx].m_iPrensentTime = m_iPrensentTime;
	strcpy_s(pDoc->m_Setting8[m_DlgIdx].m_TaskName, 100, m_szTaskName);
	

}


void CSettingDlg8::OnStnClickedCubenumstatic2()
{
	// TODO: 在此添加控件通知处理程序代码
}
