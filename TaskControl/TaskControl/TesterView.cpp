// TesterView.cpp : implementation file
//

#include "stdafx.h"
#include "taskcontrol.h"
#include "TesterView.h"
#include <direct.h>
#include "MainFrm.h"
#include "TaskControlDoc.h"
#include "SelectView.h"
#include "HardView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTesterView

IMPLEMENT_DYNCREATE(CTesterView, CFormView)

CTesterView::CTesterView()
	: CFormView(CTesterView::IDD)
	, m_oldpoint(0)
{
	//{{AFX_DATA_INIT(CTesterView)
	m_TesterNo = _T("");
	m_TesterName = _T("");
	m_TesterAge = 0;
	m_TesterSex = _T("");
	m_Session = 0;
	m_bSetting = FALSE;
	//}}AFX_DATA_INIT
}

CTesterView::~CTesterView()
{
}

void CTesterView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTesterView)
	DDX_Text(pDX, IDC_TESTERNO, m_TesterNo);
	DDX_Text(pDX, IDC_TESTERNAME, m_TesterName);
	DDX_Text(pDX, IDC_TESTERAGE, m_TesterAge);
	DDX_CBString(pDX, IDC_TESTERSEX, m_TesterSex);
	DDX_Text(pDX, IDC_SESSION, m_Session);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_MAKESURE, m_btnMakeSure);
}


BEGIN_MESSAGE_MAP(CTesterView, CFormView)
	//{{AFX_MSG_MAP(CTesterView)
	ON_BN_CLICKED(IDC_SAVEAS, OnSaveas)
	ON_BN_CLICKED(IDC_MAKESURE, OnMakesure)
	ON_EN_CHANGE(IDC_TESTERNO, OnChangeTesterno)
	ON_CBN_SELCHANGE(IDC_TESTERSEX, OnSelchangeTestersex)
	ON_EN_CHANGE(IDC_TESTERNAME, OnChangeTestername)
	ON_EN_CHANGE(IDC_TESTERAGE, OnChangeTesterage)
	ON_EN_CHANGE(IDC_SESSION, OnChangeSession)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_MAKESURE2, &CTesterView::OnNext)
	ON_BN_CLICKED(IDC_BUTTON1, &CTesterView::OnBnClickedButton1)
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTesterView diagnostics

#ifdef _DEBUG
void CTesterView::AssertValid() const
{
	CFormView::AssertValid();
}

void CTesterView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTesterView message handlers
//保存被试者信息
void CTesterView::OnSave() 
{
	SetCurrentDirectory(g_szExePath);
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_TesterNo=="")
	{
		MessageBox("请输入受试者编号！");
		return;
	}
	if(m_TesterName=="")
	{
		MessageBox("请输入受试者姓名！");
		return;
	}
	if(m_TesterAge<0)
	{
		MessageBox("请输入受试者年龄！");
		return;
	}
	if(m_Session<0)
	{
		MessageBox("请输入第N次！");
		return;
	}
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
    CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();

	sprintf_s(pDoc->m_PartInfo.m_TesterNo, m_TesterNo);
	sprintf_s(pDoc->m_PartInfo.m_TesterName, m_TesterName);
	sprintf_s(pDoc->m_PartInfo.m_TesterSex, m_TesterSex);
	pDoc->m_PartInfo.m_TesterAge = m_TesterAge;
	pDoc->m_PartInfo.m_Session = m_Session;

	_mkdir("PartInfo");
    DWORD nBufferLength=256; 
//	char lpBuffer[256];  
//	char lpSaveBuffer[256];  
	CString m_FileName;
//	GetCurrentDirectory(nBufferLength,lpBuffer);
//	sprintf(lpSaveBuffer,"%s\\PartInfo",lpBuffer);
    m_FileName.Format("PartInfo\\%s-%s.txt",m_TesterNo,m_TesterName);
//    m_FileName.Format("%s\\%s-%s.txt",lpSaveBuffer,m_TesterNo,m_TesterName);
	FILE *fp;
	fopen_s(&fp, m_FileName,"wt");
	if(fp!=NULL)
	{
        fprintf_s(fp,"编号\t%s\n",m_TesterNo);
		fprintf_s(fp,"姓名\t%s\n",m_TesterName);
        fprintf_s(fp,"性别\t%s\n",m_TesterSex);
		fprintf_s(fp,"年龄\t%d\n",m_TesterAge);
		fprintf_s(fp,"第N次\t%d\n",m_Session);
		fclose(fp);
	}	


	MessageBox("保存完毕！","提示");
}

//另存被试者信息
void CTesterView::OnSaveas() 
{
	SetCurrentDirectory(g_szExePath);
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_TesterNo=="")
	{
		MessageBox("请输入受试者编号！");
		return;
	}
	if(m_TesterName=="")
	{
		MessageBox("请输入受试者姓名！");
		return;
	}
	if(m_TesterAge<0)
	{
		MessageBox("请输入受试者年龄！");
		return;
	}
	if(m_Session<0)
	{
		MessageBox("请输入第N次！");
		return;
	}
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
    CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();

	sprintf_s(pDoc->m_PartInfo.m_TesterNo, m_TesterNo);
	sprintf_s(pDoc->m_PartInfo.m_TesterName, m_TesterName);
	sprintf_s(pDoc->m_PartInfo.m_TesterSex, m_TesterSex);
	pDoc->m_PartInfo.m_TesterAge = m_TesterAge;
	pDoc->m_PartInfo.m_Session = m_Session;

	_mkdir("PartInfo");
	CString m_FileName;
	m_FileName.Format("%s-%s.txt",m_TesterNo,m_TesterName);
	CFileDialog Dlg(FALSE,NULL,m_FileName,NULL,"Part Info Files (*.txt)",this); 
    DWORD nBufferLength=256; 
	char lpBuffer[256];  
//	char lpSaveBuffer[256];

	GetCurrentDirectory(nBufferLength,lpBuffer);
//	sprintf(lpSaveBuffer,"%s\\PartInfo",lpBuffer);
	CString dlgpath;
	dlgpath.Format("%s\\PartInfo",lpBuffer);
	Dlg.m_ofn.lpstrInitialDir=dlgpath.GetBuffer(dlgpath.GetLength());	
	if(Dlg.DoModal()==IDOK)
	{
		CString filepathall = Dlg.GetPathName();
		m_FileName.Format("%s",filepathall.GetBuffer(filepathall.GetLength()));
    	FILE *fp;
		fopen_s(&fp, m_FileName,"wt");
		if(fp!=NULL)
		{
			fprintf(fp,"编号\t%s\n",m_TesterNo);
			fprintf(fp,"姓名\t%s\n",m_TesterName);
			fprintf(fp,"性别\t%s\n",m_TesterSex);
			fprintf(fp,"年龄\t%d\n",m_TesterAge);
		    fprintf(fp,"第N次\t%d\n",m_Session);
			fclose(fp);
		}
		MessageBox("保存完毕！","提示");
	}
	SetCurrentDirectory(lpBuffer);
	
}

void CTesterView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
    CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();

	m_TesterNo = pDoc->m_PartInfo.m_TesterNo;
	m_TesterName = pDoc->m_PartInfo.m_TesterName;
	CComboBox* m_TesterSexCom;
	m_TesterSexCom = (CComboBox*)GetDlgItem(IDC_TESTERSEX);   
	m_TesterSexCom->ResetContent();
    m_TesterSexCom->InsertString(0,"男");
	m_TesterSexCom->InsertString(1,"女");
	m_TesterSexCom->SetCurSel(0);
	m_TesterSex = pDoc->m_PartInfo.m_TesterSex;
	m_TesterAge = pDoc->m_PartInfo.m_TesterAge;
	m_Session = pDoc->m_PartInfo.m_Session;
	UpdateData(FALSE);
	Resize();
}

void CTesterView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
    CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();

	
	m_TesterNo = pDoc->m_PartInfo.m_TesterNo;
	m_TesterName = pDoc->m_PartInfo.m_TesterName;
	CComboBox* m_TesterSexCom;
	m_TesterSexCom = (CComboBox*)GetDlgItem(IDC_TESTERSEX); 
	m_TesterSexCom->ResetContent();
	m_TesterSexCom->InsertString(0,"男");
	m_TesterSexCom->InsertString(1,"女");
	m_TesterSexCom->SetCurSel(0);
	m_TesterSex = pDoc->m_PartInfo.m_TesterSex;
	m_TesterAge = pDoc->m_PartInfo.m_TesterAge;
	m_Session = pDoc->m_PartInfo.m_Session;
	UpdateData(FALSE);	

	if (!m_bSetting)
	{
		CButton* m_Button;
		m_Button = (CButton*)GetDlgItem(IDC_MAKESURE); 
		m_Button->EnableWindow(TRUE);
	}

}

//设为当前被试者信息
void CTesterView::OnMakesure() 
{
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_TesterNo=="")
	{
		MessageBox("请输入受试者编号！");
		return;
	}
	if(m_TesterName=="")
	{
		MessageBox("请输入受试者姓名！");
		return;
	}
	if(m_TesterAge<0)
	{
		MessageBox("请输入受试者年龄！");
		return;
	}
	if(m_Session<0)
	{
		MessageBox("请输入第N次！");
		return;
	}
	CTaskControlApp*   pApp =(CTaskControlApp*)AfxGetApp();
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
    CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();

	sprintf_s(pDoc->m_PartInfo.m_TesterNo, m_TesterNo);
	sprintf_s(pDoc->m_PartInfo.m_TesterName, m_TesterName);
	sprintf_s(pDoc->m_PartInfo.m_TesterSex, m_TesterSex);
	pDoc->m_PartInfo.m_TesterAge = m_TesterAge;
	pDoc->m_PartInfo.m_Session = m_Session;

	_mkdir("PartInfo");
    DWORD nBufferLength=256; 
//	char lpBuffer[256];  
//	char lpSaveBuffer[256];  
	CString m_FileName;
//	GetCurrentDirectory(nBufferLength,lpBuffer);
//	sprintf(lpSaveBuffer,"%s\\PartInfo",lpBuffer);
    m_FileName.Format("PartInfo\\%s-%s.txt",m_TesterNo,m_TesterName);
//    m_FileName.Format("%s\\%s-%s.txt",lpSaveBuffer,m_TesterNo,m_TesterName);
	FILE *fp;
	fopen_s(&fp, m_FileName,"wt");
	if(fp!=NULL)
	{
        fprintf_s(fp,"编号\t%s\n",m_TesterNo);
		fprintf_s(fp,"姓名\t%s\n",m_TesterName);
        fprintf_s(fp,"性别\t%s\n",m_TesterSex);
		fprintf_s(fp,"年龄\t%d\n",m_TesterAge);
		fprintf_s(fp,"第N次\t%d\n",m_Session);
		fclose(fp);
	}	
//	SetCurrentDirectory(lpBuffer);	

	sprintf_s(pDoc->m_CurPartInfo.m_TesterNo, m_TesterNo);
	sprintf_s(pDoc->m_CurPartInfo.m_TesterName, m_TesterName);
	sprintf_s(pDoc->m_CurPartInfo.m_TesterSex, m_TesterSex);
	pDoc->m_CurPartInfo.m_TesterAge = m_TesterAge;	
	pDoc->m_CurPartInfo.m_Session = m_Session;
	CButton* m_Button;
	m_Button = (CButton*)GetDlgItem(IDC_MAKESURE); 
    m_Button->EnableWindow(FALSE);
	m_bSetting = TRUE;

	pApp->SaveExe(); 
			

		
}

void CTesterView::OnChangeTesterno() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
    CButton* m_Button;
	m_Button = (CButton*)GetDlgItem(IDC_MAKESURE); 
    m_Button->EnableWindow(TRUE);	
}

void CTesterView::OnSelchangeTestersex() 
{
	// TODO: Add your control notification handler code here
    CButton* m_Button;
	m_Button = (CButton*)GetDlgItem(IDC_MAKESURE); 
    m_Button->EnableWindow(TRUE);	
}

void CTesterView::OnChangeTestername() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
    CButton* m_Button;
	m_Button = (CButton*)GetDlgItem(IDC_MAKESURE); 
    m_Button->EnableWindow(TRUE);	
}

void CTesterView::OnChangeTesterage() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
    CButton* m_Button;
	m_Button = (CButton*)GetDlgItem(IDC_MAKESURE); 
    m_Button->EnableWindow(TRUE);	
}

void CTesterView::OnChangeSession() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
    CButton* m_Button;
	m_Button = (CButton*)GetDlgItem(IDC_MAKESURE); 
    m_Button->EnableWindow(TRUE);
}


void CTesterView::OnNext()
{
	// TODO: 在此添加控件通知处理程序代码
	OnMakesure() ;
	CMainFrame *pWnd=(CMainFrame *)theApp.GetMainWnd();
	CTaskControlApp*   pApp =(CTaskControlApp*)AfxGetApp();
	CWnd *pwnd=(CWnd *)theApp.m_pMainWnd;
	((CSelectView*)pApp->g_pView[SELECT])->CenterWindow(pwnd);
	CTaskControlDoc* pDoc = (CTaskControlDoc*)pWnd->GetActiveDocument();
	if (NULL == theApp.SwitchView(SELECT))
			return;
	
	pDoc->NewSetting();
	pDoc->UpdateAllViews(NULL,1);
}


void CTesterView::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame* active = (CMainFrame *)theApp.GetMainWnd();
	if (active) {
		active->PostMessage(WM_COMMAND,ID_TESTER_OPEN);
	}
}


HBRUSH CTesterView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_EDIT){
		pDC->SetBkColor(RGB(255,255,255));
	}
	return hbr;
}


void CTesterView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
}


void CTesterView::Resize(void)
{

}
