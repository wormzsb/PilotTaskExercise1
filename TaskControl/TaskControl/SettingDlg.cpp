// SettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "taskcontrol.h"
#include "SettingDlg.h"
#include "MainFrm.h"
#include "TaskControlDoc.h"
#include <iostream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg dialog


CSettingDlg::CSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSettingDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	iCurIdx=-1;
	m_CurItem = 0;
	Initial = TRUE;
}


void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingDlg)
	DDX_Control(pDX, IDC_TAB1, m_TabCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialog)
	//{{AFX_MSG_MAP(CSettingDlg)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab1)
	ON_BN_CLICKED(IDC_APPLICATION, OnApplication)
	ON_BN_CLICKED(IDC_DEFAULT, OnDefault)
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg message handlers

void CSettingDlg::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	cout << "on OnSelchangeTab1" << endl;
	int t = m_TabCtrl.GetCurSel();
    SetCurDlg(t);
	*pResult = 0;
}

//添加选项卡
void CSettingDlg::AddPages()
{
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
    CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();

	int i;
	for(i=0;i<pDoc->m_TaskCount;i++)
	{
		switch(pDoc->m_TaskOrder[i])
		{
		case 0:
	    	m_SettingDlg1 = new CSettingDlg1();
			m_SettingDlg1->m_DlgIdx = pDoc->m_ItemData[pDoc->m_ItemOrder[i]].TaskNo;
			pPages.Add(m_SettingDlg1);
			csIds.Add(IDD_SETTINGDLG1);
			break;
		case 1:
	    	m_SettingDlg2 = new CSettingDlg2();
			m_SettingDlg2->m_DlgIdx = pDoc->m_ItemData[pDoc->m_ItemOrder[i]].TaskNo;
			pPages.Add(m_SettingDlg2);
			csIds.Add(IDD_SETTINGDLG2);
			break;
		case 2:
			if (Initial == TRUE)
				m_SettingDlg3 = new CSettingDlg3();
			m_SettingDlg3->m_DlgIdx = pDoc->m_ItemData[pDoc->m_ItemOrder[i]].TaskNo;
			pPages.Add(m_SettingDlg3);
			csIds.Add(IDD_SETTINGDLG3);
			break;
		case 3:
			m_SettingDlg4 = new CSettingDlg4();
			m_SettingDlg4->m_DlgIdx = pDoc->m_ItemData[pDoc->m_ItemOrder[i]].TaskNo;
			pPages.Add(m_SettingDlg4);
			csIds.Add(IDD_SETTINGDLG4);
			break;
		case 4:
	    	m_SettingDlg5 = new CSettingDlg5();
			m_SettingDlg5->m_DlgIdx = pDoc->m_ItemData[pDoc->m_ItemOrder[i]].TaskNo;
			pPages.Add(m_SettingDlg5);
			csIds.Add(IDD_SETTINGDLG5);
			break;
		case 5:
	    	m_SettingDlg6 = new CSettingDlg6();
			m_SettingDlg6->m_DlgIdx = pDoc->m_ItemData[pDoc->m_ItemOrder[i]].TaskNo;
			pPages.Add(m_SettingDlg6);
			csIds.Add(IDD_SETTINGDLG6);
			break;	
		case 6:
	    	m_SettingDlg7 = new CSettingDlg7();
			m_SettingDlg7->m_DlgIdx = pDoc->m_ItemData[pDoc->m_ItemOrder[i]].TaskNo;
			pPages.Add(m_SettingDlg7);
			csIds.Add(IDD_SETTINGDLG7);
			break;
		case 7:
			m_SettingDlg8 = new CSettingDlg8();
			m_SettingDlg8->m_DlgIdx = pDoc->m_ItemData[pDoc->m_ItemOrder[i]].TaskNo;
			pPages.Add(m_SettingDlg8);
			csIds.Add(IDD_SETTINGDLG8);
			break;
		}
	}  
	Initial = FALSE;
}

CDialog* CSettingDlg::GetDialog(const int id)
{
	ASSERT(id>=0&&id<pPages.GetSize());
	return (CDialog *)pPages.GetAt(id);
}


CSettingDlg::~CSettingDlg()
{

	ClosePages();
	for (int i = 0; i < pPages.GetSize(); i++)
		delete((CDialog *)pPages.GetAt(i));
	pPages.RemoveAll();
	csIds.RemoveAll();
}

void CSettingDlg::ClosePages()
{
	for(int t=0;t<pPages.GetSize();t++)
	{
		CDialog *pDlg=GetDialog(t);
		if(pDlg)
			pDlg->DestroyWindow();
	}
}

void CSettingDlg::SetCurDlg(const int id)
{
	if(iCurIdx>=0)
	{
		CDialog *pDlg1=GetDialog(iCurIdx);
		if(pDlg1)
			pDlg1->ShowWindow(SW_HIDE);
	}
	iCurIdx=id;
	CDialog *pDlg2=GetDialog(iCurIdx);
	if(pDlg2)
		pDlg2->ShowWindow(SW_SHOW);
}

BOOL CSettingDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
    CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();
	CString cs;
	TC_ITEM ti;

	int i;
	for(i=0;i<8;i++)
	{
	    pDoc->m_TaskNum[i] = 0;
	}
	if (m_TabCtrl.GetSafeHwnd())
	{
		for(i=0;i<pDoc->m_TaskCount;i++)
		{
			switch(pDoc->m_TaskOrder[i])
			{
			case 0:
				cs = "任务1";
				ti.mask = TCIF_TEXT|TCIF_PARAM;
				ti.pszText = cs.LockBuffer();
		//		ti.lParam = (long) pView;
				m_TabCtrl.InsertItem(m_TabCtrl.GetItemCount(), &ti);
				cs.UnlockBuffer();
				pDoc->m_TaskNum[0]++;
				break;
			case 1:
	    		cs = "任务2";
				ti.mask = TCIF_TEXT|TCIF_PARAM;
				ti.pszText = cs.LockBuffer();
		//		ti.lParam = (long) pView;
				m_TabCtrl.InsertItem(m_TabCtrl.GetItemCount(), &ti);
				cs.UnlockBuffer();
				pDoc->m_TaskNum[1]++;
				break;
			case 2:
	    		cs = "任务3";
				ti.mask = TCIF_TEXT|TCIF_PARAM;
				ti.pszText = cs.LockBuffer();
		//		ti.lParam = (long) pView;
				m_TabCtrl.InsertItem(m_TabCtrl.GetItemCount(), &ti);
				cs.UnlockBuffer();
				pDoc->m_TaskNum[2]++;
				break;
			case 3:
	    		cs = "任务4";
				ti.mask = TCIF_TEXT|TCIF_PARAM;
				ti.pszText = cs.LockBuffer();
		//		ti.lParam = (long) pView;
				m_TabCtrl.InsertItem(m_TabCtrl.GetItemCount(), &ti);
				cs.UnlockBuffer();
				pDoc->m_TaskNum[3]++;
				break;
			case 4:
	    		cs = "任务5";
				ti.mask = TCIF_TEXT|TCIF_PARAM;
				ti.pszText = cs.LockBuffer();
		//		ti.lParam = (long) pView;
				m_TabCtrl.InsertItem(m_TabCtrl.GetItemCount(), &ti);
				cs.UnlockBuffer();
				pDoc->m_TaskNum[4]++;
				break;
			case 5:
	    		cs = "任务6";
				ti.mask = TCIF_TEXT|TCIF_PARAM;
				ti.pszText = cs.LockBuffer();
		//		ti.lParam = (long) pView;
				m_TabCtrl.InsertItem(m_TabCtrl.GetItemCount(), &ti);
				cs.UnlockBuffer();
				pDoc->m_TaskNum[5]++;
				break;	
			case 6:
	    		cs = "任务7";
				ti.mask = TCIF_TEXT|TCIF_PARAM;
				ti.pszText = cs.LockBuffer();
		//		ti.lParam = (long) pView;
				m_TabCtrl.InsertItem(m_TabCtrl.GetItemCount(), &ti);
				cs.UnlockBuffer();
				pDoc->m_TaskNum[6]++;
				break;	
			case 7:
				cs = "任务8";
				ti.mask = TCIF_TEXT | TCIF_PARAM;
				ti.pszText = cs.LockBuffer();
				m_TabCtrl.InsertItem(m_TabCtrl.GetItemCount(), &ti);
				cs.UnlockBuffer();
				pDoc->m_TaskNum[7]++;
				break;

			}
		}  
	}
	// Add tab pages
	AddPages();

	if(pPages.GetSize()>0)
	{
		CRect rc;
		GetDlgItem(IDC_TAB1)->GetWindowRect(rc);
		ScreenToClient(rc);
		for(int t=0;t<pPages.GetSize();t++)
		{
			CDialog *pDlg=GetDialog(t);
			if(pDlg)
			{
				pDlg->Create(csIds.GetAt(t),this);
				//pDlg->SetWindowPos(NULL,rc.left+3,rc.top+21,rc.Width()-6,rc.Height()-23,SWP_NOZORDER);
				pDlg->CenterWindow();
			}
		}
//		SetCurDlg(0);
	}
//	HWND hWndTab = (HWND)SendMessage(PSM_GETTABCONTROL);
//	m_TabCtrl.SubclassDlgItem(IDC_TAB1, this);

	m_TabCtrl.SetCurSel(m_CurItem);// 
	NMHDR nmhdr;   
	nmhdr.code = TCN_SELCHANGE; 
	nmhdr.hwndFrom = m_TabCtrl.GetSafeHwnd(); 
	nmhdr.idFrom = IDC_TAB1; 
	SendMessage(WM_NOTIFY,(WPARAM)m_TabCtrl.GetSafeHwnd(),(LPARAM)&nmhdr);
	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// on confirm btn
void CSettingDlg::OnApplication() 
{
	// TODO: Add your control notification handler code here
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
    CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();
	
	for(int t=0;t<pPages.GetSize();t++)
	{
		switch(pDoc->m_TaskOrder[t])
		{
		case 0:
			m_SettingDlg1=(CSettingDlg1*)GetDialog(t);
			m_SettingDlg1->Save();
			break;
		case 1:
	    	m_SettingDlg2=(CSettingDlg2*)GetDialog(t);
			m_SettingDlg2->Save();
			break;
	    case 2:
	    	m_SettingDlg3=(CSettingDlg3*)GetDialog(t);
			m_SettingDlg3->Save();
			break;
		case 3:
	    	m_SettingDlg4=(CSettingDlg4*)GetDialog(t);
			m_SettingDlg4->Save();
			break;
		case 4:
	    	m_SettingDlg5=(CSettingDlg5*)GetDialog(t);
			m_SettingDlg5->Save();
			break;
		case 5:
	    	m_SettingDlg6=(CSettingDlg6*)GetDialog(t);
			m_SettingDlg6->Save();
			break;	
		case 6:
			m_SettingDlg7=(CSettingDlg7*)GetDialog(t);
			m_SettingDlg7->Save();
			break;	
		case 7:
			m_SettingDlg8 = (CSettingDlg8*)GetDialog(t);
			m_SettingDlg8->Save();
		}
	}
}

//保存任务设置
void CSettingDlg::OnOK() 
{
	// TODO: Add extra validation here
	OnApplication();
	CDialog::OnOK();
}

void CSettingDlg::OnDefault() 
{
	// TODO: Add your control notification handler code here
	
}


HBRUSH CSettingDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_EDIT){
		pDC->SetBkColor(RGB(255,255,255));
	}
	return hbr;
}

