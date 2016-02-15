// TaskControl.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "TaskControl.h"
//#include "MainFrm.h"
#include "typeinfo"
#include "MainFrm.h"
#include "TaskControlDoc.h"
#include "TaskControlView.h"
#include "TesterView.h"
#include "SelectView.h"
#include "HardView.h"
#include "WelcomDlg.h"
#include "direct.h"
#include "TesterView.h"
//#include "MainFrm.h"
using namespace std;
//#include "vld.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define NUMVIEWS 4
// CTaskControlApp

BEGIN_MESSAGE_MAP(CTaskControlApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CTaskControlApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()

char g_szExePath[MAX_PATH];
// CTaskControlApp construction

CTaskControlApp::CTaskControlApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CTaskControlApp object

CTaskControlApp theApp;


// CTaskControlApp initialization
void CTaskControlApp::SaveExe()
{
	//ѭ������ ��ȫ��������� �ͽ��б���exe ����ʾ����
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
	CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();
	if (((CTesterView*)g_pView[TESTER])->m_bSetting && ((CSelectView*)g_pView[SELECT])->m_bSetting \
		&& ((CHardView*)g_pView[HARD])->m_bSetting)
	{
		//��ȡģ������Ŀ¼
		TCHAR szPath[MAX_PATH] = {0};
		GetModuleFileName(NULL, szPath, MAX_PATH);

		SetCurrentDirectory(g_szExePath);
		int i;
		int pos;
		for (i = 0; i < strlen(szPath); i++)
		{
			//��Ӧ�ó����ļ����зֳ���
			if (szPath[i] == 92)
				pos = i;
		}

		szPath[pos+1] = 0;
		TCHAR szSubPath[MAX_PATH] = {0};
		TCHAR szFilePath[MAX_PATH] = {0};
		TCHAR szBatPath[MAX_PATH] = {0};
		TCHAR szDirectPath[MAX_PATH]={0};
		TCHAR szSetPath[MAX_PATH]={0};
		strcpy(szSubPath,szPath);
		//����Taskbat�ĵ�ַ���������߱�ź�����ȷ����exe��·��
		sprintf(szFilePath,	"%s\\%s-%s.exe",g_szExePath,pDoc->m_CurPartInfo.m_TesterNo,pDoc->m_CurPartInfo.m_TesterName);
		sprintf(szBatPath,"%s\\Settings\\TaskBat.exe",g_szExePath);
	
		//���������������ļ���
		sprintf(szDirectPath,"%s\\Settings\\%s-%s", g_szExePath,pDoc->m_CurPartInfo.m_TesterNo,pDoc->m_CurPartInfo.m_TesterName);
	
		_mkdir(szDirectPath);
		strcat(szDirectPath,"\\TaskSetting.set");
		sprintf(szSetPath,"%s\\Settings\\TaskSetting.set",g_szExePath);
		//�ƶ�TaskSetiing.set�������������ļ���
		CopyFile(szBatPath,szFilePath,FALSE);
		CopyFile(szSetPath,szDirectPath,FALSE);


		//AfxMessageBox("ʵ�鷽��������");
		return;
	}
			

}
BOOL CTaskControlApp::InitInstance()
{
	CWelcomDlg dlg;
	dlg.DoModal();



	GetCurrentDirectory(MAX_PATH,g_szExePath);
	//_CrtSetBreakAlloc(1578);

	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
//		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	RegisterOcx("MSCHRT20.OCX");

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CTaskControlDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CTaskControlView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	

	// The one and only window has been initialized, so show and update it.
	g_pView[0] = ((CFrameWnd*)m_pMainWnd)->GetActiveView();
    g_pView[1] = (CView*) new CTesterView;
	g_pView[2] = (CView*) new CSelectView;
	g_pView[3] = (CView*) new CHardView;
    CDocument* pCurrentDoc = ((CFrameWnd*)m_pMainWnd)->GetActiveDocument();
    CCreateContext newContext;
    newContext.m_pNewViewClass = NULL;
    newContext.m_pNewDocTemplate = NULL;
	newContext.m_pLastView = NULL;
	newContext.m_pCurrentFrame = NULL;
	newContext.m_pCurrentDoc = pCurrentDoc;
	//��������ӵ�IDΪAFX_IDW_PANE_FIRST�����´�������ͼ�������ֵ
	UINT viewID[4];
	viewID[1] = AFX_IDW_PANE_FIRST+1;
	viewID[2] = AFX_IDW_PANE_FIRST+2;
	viewID[3] = AFX_IDW_PANE_FIRST+3;
	
	CRect rect(0, 0, 0, 0);

	m_pMainWnd->SetWindowText("��/��Э���Բ���ϵͳ");
	//m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();
	

	GetWindowRect(g_pView[0]->m_hWnd, &rect);

	CRect halfRect;
	halfRect.left = rect.left + rect.Width()/4;
	halfRect.right = halfRect.left + rect.Width();
	halfRect.top = rect.top + rect.Height()/4;
	halfRect.bottom = halfRect.top + rect.Height();

	// �����µ���ͼ����������ͼ��Ӧ�������ô��ڣ�ֱ��Ӧ�ó����˳���
	//Ӧ�ó�����Զ�ɾ���´�������ͼ


	g_pView[1]->Create(NULL, NULL,(AFX_WS_DEFAULT_VIEW & ~WS_VISIBLE),
	// AFX_WS_DEFAULT_VIEW����(WS_BORDER | WS_VISIBLE | WS_CHILD)
	halfRect, m_pMainWnd, viewID[1], &newContext);
	g_pView[1]->OnInitialUpdate();
    g_pView[2]->Create(NULL, NULL,(AFX_WS_DEFAULT_VIEW & ~WS_VISIBLE),
	// AFX_WS_DEFAULT_VIEW����(WS_BORDER | WS_VISIBLE | WS_CHILD)
	halfRect, m_pMainWnd, viewID[2], &newContext);
	g_pView[2]->OnInitialUpdate();
    g_pView[3]->Create(NULL, NULL,(AFX_WS_DEFAULT_VIEW & ~WS_VISIBLE),
	// AFX_WS_DEFAULT_VIEW����(WS_BORDER | WS_VISIBLE | WS_CHILD)
	halfRect, m_pMainWnd, viewID[3], &newContext);
	g_pView[3]->OnInitialUpdate();


	// call DragAcceptFiles only if there's a suffix
	//  In an SDI app, this should occur after ProcessShellCommand

	CTaskControlApp*   pApp =(CTaskControlApp*)AfxGetApp();
	// TODO: Add your command handler code here
	//CTaskControlDoc* pDoc = (CTaskControlDoc*)GetActiveDocument();
	if (NULL == theApp.SwitchView(TESTER))
		//return;

	((CTesterView*)pApp->g_pView[TESTER])->m_bSetting = FALSE;
	CWnd *pwnd=(CWnd *)theApp.m_pMainWnd;
	((CTesterView*)pApp->g_pView[TESTER])->CenterWindow(pwnd);
	//((CTesterView*)pApp->g_pView[TESTER])->SetWindowPos(pwnd,200,200,300,300,SWP_NOSIZE);
	//pDoc->NewTester();
	//pDoc->UpdateAllViews(NULL,1);		

	return TRUE;
}

CView* CTaskControlApp::SwitchView( UINT nIndex ) 
{ 
	int i;


    ASSERT( nIndex >=0 && nIndex < NUMVIEWS ); 
    CView* pNewView = g_pView[nIndex]; 
	CView* pActiveView =((CFrameWnd*) m_pMainWnd)->GetActiveView(); 
    if ( !pActiveView ) // ��ǰû�м������ͼ 
		return NULL; 
    if ( pNewView == pActiveView ) // ��ǰ��ͼ����Ҫ�л�����ͼ��ͬ 
		return pActiveView; 

	for (i = TESTER; i <= HARD; i++)
	{
		if (g_pView[i] == pActiveView)
		{
			switch(i)
			{
			case TESTER:
				if (!((CTesterView*)g_pView[i])->m_bSetting)
				{
					AfxMessageBox("�밴ȷ��֮�����뿪");
					return NULL;				
				}

				break;
			case SELECT:
				if (!((CSelectView*)g_pView[i])->m_bSetting)
				{
					AfxMessageBox("�밴ȷ��֮�����뿪");
					return NULL;
				}
	
				break;

			case HARD:
				if (!((CHardView*)g_pView[i])->m_bSetting)
				{
					AfxMessageBox("�밴ȷ��֮�����뿪");
					return NULL;
				}
					
				break;
			}
			
			break;
		}; 
	}
	//CRect rect;
	
    //������ͼ�Ĵ���ID��ʹRecalcLayout()���Թ��� 
    UINT temp = ::GetWindowLong(pActiveView->m_hWnd, GWL_ID); 
    ::SetWindowLong(pActiveView->m_hWnd, GWL_ID, ::GetWindowLong(pNewView->m_hWnd, GWL_ID)); 
    ::SetWindowLong(pNewView->m_hWnd, GWL_ID, temp); 
    //��ʾ�µ���ͼ������ǰһ����ͼ 
    pActiveView->ShowWindow(SW_HIDE); 
    pNewView->ShowWindow(SW_SHOW); 
    ((CFrameWnd*) m_pMainWnd)->SetActiveView(pNewView); 
	//GetWindowRect(g_pView[1]->m_hWnd, &rect);
	//((CFrameWnd*) m_pMainWnd)->RecalcLayout(); 
	

	//GetWindowRect(g_pView[1]->m_hWnd, &rect);
    pNewView->Invalidate(); 
    return pActiveView; 
} 

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

// App command to run the dialog
void CTaskControlApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CTaskControlApp message handlers

BOOL CTaskControlApp::RegisterOcx(LPCTSTR OcxFileName)
{
         LPCTSTR pszDllName = OcxFileName ;         //ActiveX�ؼ���·�����ļ���         
         HINSTANCE hLib = LoadLibrary(pszDllName); //װ��ActiveX�ؼ�
         if (hLib < (HINSTANCE)HINSTANCE_ERROR)
         {
                   return FALSE ;
         }
         FARPROC lpDllEntryPoint; 
         lpDllEntryPoint = GetProcAddress(hLib,_T("DllRegisterServer"));   //��ȡע�ắ��DllRegisterServer��ַ
         if(lpDllEntryPoint!=NULL)   //����ע�ắ��DllRegisterServer
         {
                  if(FAILED((*lpDllEntryPoint)()))
                   {
                            FreeLibrary(hLib);
                            return FALSE ;
                    }
                   return TRUE ;
         }
         else
                   return FALSE ;
}

BOOL CTaskControlApp::UnRegisterOcx(LPCTSTR OcxFileName)
{
         LPCTSTR pszDllName = OcxFileName ;         //ActiveX�ؼ���·�����ļ���         
         HINSTANCE hLib = LoadLibrary(pszDllName); //װ��ActiveX�ؼ�
         if (hLib < (HINSTANCE)HINSTANCE_ERROR)
         {
             return FALSE ;
         }
         FARPROC lpDllEntryPoint; 
         lpDllEntryPoint = GetProcAddress(hLib,_T("DllUnregisterServer"));        //��ȡע�ắ��DllUnregisterServer��ַ
         if(lpDllEntryPoint!=NULL)   //����ע�ắ��DllUnregisterServer
         {
             if(FAILED((*lpDllEntryPoint)()))
             {
                 FreeLibrary(hLib);
                 return FALSE ;
             }
             return TRUE ;
         }
         else
             return FALSE ;
}

HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if (nCtlColor == CTLCOLOR_EDIT){
		pDC->SetBkColor(RGB(255,255,255));
	}
	return hbr;
}


BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
