// HardView.cpp : implementation file
//

#include "stdafx.h"
#include "taskcontrol.h"
#include "HardView.h"
#include <direct.h>
#include "TesterView.h"
#include "MainFrm.h"
#include "TaskControlDoc.h"
#include "SelectView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHardView

IMPLEMENT_DYNCREATE(CHardView, CFormView)

CHardView::CHardView()
	: CFormView(CHardView::IDD)
{
	//{{AFX_DATA_INIT(CHardView)
	m_JoySpeedMax = _T("");
	m_DistanceError = _T("");
	m_AngleError = _T("");
	m_KnobSensitive = _T("");
	m_bSetting = FALSE;
	//}}AFX_DATA_INIT
}

CHardView::~CHardView()
{
}

void CHardView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHardView)
	DDX_Text(pDX, IDC_JOYSPEEDMAX, m_JoySpeedMax);
	DDX_Text(pDX, IDC_DISTANCEERROR, m_DistanceError);
	DDX_Text(pDX, IDC_ANGLEERROR, m_AngleError);
	DDX_Text(pDX, IDC_SENSITIVE, m_KnobSensitive);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_SAVE, m_btnSave);
}


BEGIN_MESSAGE_MAP(CHardView, CFormView)
	//{{AFX_MSG_MAP(CHardView)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_SAVEAS, OnSaveas)
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_JOYSPEEDMAX, &CHardView::OnEnChangeJoyspeedmax)
	ON_EN_CHANGE(IDC_SENSITIVE, &CHardView::OnEnChangeSensitive)
	ON_EN_CHANGE(IDC_DISTANCEERROR, &CHardView::OnEnChangeDistanceerror)
	ON_EN_CHANGE(IDC_ANGLEERROR, &CHardView::OnEnChangeAngleerror)
	ON_BN_CLICKED(IDC_SAVE2, &CHardView::OnLast)
	ON_BN_CLICKED(IDC_SAVE4, &CHardView::OnBegain)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHardView diagnostics

#ifdef _DEBUG
void CHardView::AssertValid() const
{
	CFormView::AssertValid();
}

void CHardView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHardView message handlers
//��������
void CHardView::OnSave() 
{
	SetCurrentDirectory(g_szExePath);
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_JoySpeedMax=="")
	{
		MessageBox("����������ٶȣ�");
		return;
	}
	if(m_KnobSensitive=="")
	{
		MessageBox("�����������ȣ�");
		return;
	}
	if(m_DistanceError=="")
	{
		MessageBox("�����������");
		return;
	}
	if(m_AngleError=="")
	{
		MessageBox("������Ƕ���");
		return;
	}
	CTaskControlApp*   pApp =(CTaskControlApp*)AfxGetApp();
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
    CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();


	pDoc->m_HardSetting.m_JoySpeedMax = atof(m_JoySpeedMax);
	pDoc->m_HardSetting.m_KnobSensitive = atof(m_KnobSensitive);
	pDoc->m_HardSetting.m_DistanceError = atof(m_DistanceError);
	pDoc->m_HardSetting.m_AngleError = atof(m_AngleError);

	SetCurrentDirectory(g_szExePath);
	_mkdir("Settings");
	FILE *fp;
	fopen_s(&fp,"Settings\\Hardware.ini","wt");
	if(fp!=NULL)
	{
		fprintf(fp,"JoySpeedMax\t%.2f\n",pDoc->m_HardSetting.m_JoySpeedMax);
		fprintf(fp,"KnobSensitive\t%.2f\n",pDoc->m_HardSetting.m_KnobSensitive);
		fprintf(fp,"DistanceError\t%.2f\n",pDoc->m_HardSetting.m_DistanceError);
		fprintf(fp,"AngleError\t%.2f\n",pDoc->m_HardSetting.m_AngleError);
		fclose(fp);
	}

	m_bSetting = TRUE;
	m_btnSave.EnableWindow(!m_bSetting);
	pApp->SaveExe(); 
}

//�������
void CHardView::OnSaveas() 
{
	SetCurrentDirectory(g_szExePath);
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_JoySpeedMax=="")
	{
		MessageBox("����������ٶȣ�");
		return;
	}
	if(m_KnobSensitive=="")
	{
		MessageBox("�����������ȣ�");
		return;
	}
	if(m_DistanceError=="")
	{
		MessageBox("�����������");
		return;
	}
	if(m_AngleError=="")
	{
		MessageBox("������Ƕ���");
		return;
	}
//	_mkdir("Settings");
	CString m_FileName;
	CFileDialog Dlg(FALSE,".ini","Hardware.ini",NULL,"Hardware Setting Files (*.ini)",this); 
    DWORD nBufferLength=256; 
	char lpBuffer[256];  
//	char lpSaveBuffer[256];
	GetCurrentDirectory(nBufferLength,lpBuffer);
//	sprintf(lpSaveBuffer,"%s\\PartInfo",lpBuffer);
	Dlg.m_ofn.lpstrInitialDir="Settings";	
	if(Dlg.DoModal()==IDOK)
	{
		m_FileName = Dlg.GetPathName();
    	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
		CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();

		pDoc->m_HardSetting.m_JoySpeedMax = atof(m_JoySpeedMax);
		pDoc->m_HardSetting.m_KnobSensitive = atof(m_KnobSensitive);
		pDoc->m_HardSetting.m_DistanceError = atof(m_DistanceError);
		pDoc->m_HardSetting.m_AngleError = atof(m_AngleError);

		FILE *fp;
		fopen_s(&fp, m_FileName,"wt");
		if(fp!=NULL)
		{
			fprintf(fp,"JoySpeedMax\t%.2f\n",pDoc->m_HardSetting.m_JoySpeedMax);
			fprintf(fp,"KnobSensitive\t%.2f\n",pDoc->m_HardSetting.m_KnobSensitive);
			fprintf(fp,"DistanceError\t%.2f\n",pDoc->m_HardSetting.m_DistanceError);
			fprintf(fp,"AngleError\t%.2f\n",pDoc->m_HardSetting.m_AngleError);
			fclose(fp);
		}	
	}
	SetCurrentDirectory(lpBuffer);		
}

void CHardView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
    CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();

	FILE *fp;
	fopen_s(&fp, "Settings\\Hardware.ini","rt");
	if(fp!=NULL)
	{
		fscanf_s(fp,"JoySpeedMax\t%f\n",&pDoc->m_HardSetting.m_JoySpeedMax);
		fscanf_s(fp,"KnobSensitive\t%f\n",&pDoc->m_HardSetting.m_KnobSensitive);
		fscanf_s(fp,"DistanceError\t%f\n",&pDoc->m_HardSetting.m_DistanceError);
		fscanf_s(fp,"AngleError\t%f\n",&pDoc->m_HardSetting.m_AngleError);
		fclose(fp);
	}
    
	m_JoySpeedMax.Format("%.2f", pDoc->m_HardSetting.m_JoySpeedMax);
	m_KnobSensitive.Format("%.2f", pDoc->m_HardSetting.m_KnobSensitive);
	m_DistanceError.Format("%.2f", pDoc->m_HardSetting.m_DistanceError);
	m_AngleError.Format("%.2f", pDoc->m_HardSetting.m_AngleError);

	m_btnSave.EnableWindow(!m_bSetting);
	

	UpdateData(FALSE);		
}


void CHardView::OnEnChangeJoyspeedmax()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CFormView::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	m_bSetting = FALSE;
	m_btnSave.EnableWindow(!m_bSetting);

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CHardView::OnEnChangeSensitive()
{
	m_bSetting = FALSE;
	m_btnSave.EnableWindow(!m_bSetting);
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CFormView::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�


	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CHardView::OnEnChangeDistanceerror()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CFormView::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	m_bSetting = FALSE;
	m_btnSave.EnableWindow(!m_bSetting);

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CHardView::OnEnChangeAngleerror()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CFormView::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	m_bSetting = FALSE;
	m_btnSave.EnableWindow(!m_bSetting);

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CHardView::OnLast()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		OnSave();
	CMainFrame *pWnd=(CMainFrame *)theApp.GetMainWnd();
	CTaskControlDoc* pDoc = (CTaskControlDoc*)pWnd->GetActiveDocument();
	/*if (NULL == theApp.SwitchView(SELECT))
			return;
	
	pDoc->NewSetting();
	pDoc->UpdateAllViews(NULL,1);*/
	if(pDoc->m_CurTaskCount<1)
	{
		MessageBox("û�����ã�����ϵͳĬ�ϵ����ã�");
	}
	pDoc->NewSetting();
	char m_FileName[30];
	strcpy_s(m_FileName, 30, "Settings\\TaskSetting.set");
   	pWnd->ReadSetting(m_FileName);
	if (NULL == theApp.SwitchView(SELECT))
		return;
    pDoc->UpdateAllViews(NULL,1);
}


void CHardView::OnBegain()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnSave();
    CMainFrame *pWnd=(CMainFrame *)theApp.GetMainWnd();
	CTaskControlDoc* pDoc = (CTaskControlDoc*)pWnd->GetActiveDocument();
	CTaskControlApp*   pApp =(CTaskControlApp*)AfxGetApp();

	CString str;
	if(strcmp(pDoc->m_CurPartInfo.m_TesterNo,"")==0)
	{
		str.Format("�����߱��û�����ã�");
		MessageBox(str);
		return;
	}
	if(strcmp(pDoc->m_CurPartInfo.m_TesterName,"")==0)
	{
		str.Format("����������û�����ã�");
		MessageBox(str);
		return;
	}

	//ѭ������ ��ȫ��������� �ͽ��б���exe ����ʾ����
	if (!(((CTesterView*)pApp->g_pView[TESTER])->m_bSetting && ((CSelectView*)pApp->g_pView[SELECT])->m_bSetting && \
		((CHardView*)pApp->g_pView[HARD])->m_bSetting))
	{
		MessageBox("��ȷ���û����ã��������ã�Ӳ�����ö���ȷ�����");
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


HBRUSH CHardView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_EDIT){
		pDC->SetBkColor(RGB(255,255,255));
	}
	return hbr;
}
