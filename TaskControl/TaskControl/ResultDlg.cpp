// ResultDlg.cpp : implementation file
//

#include "stdafx.h"
#include "taskcontrol.h"
#include "ResultDlg.h"
#include "MainFrm.h"
#include "TaskControlDoc.h"
#include "math.h"
#include <iostream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResultDlg dialog


CResultDlg::CResultDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CResultDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CResultDlg)
	//}}AFX_DATA_INIT
	cout << "on constructor" << endl;
	m_pMainFrm = NULL;
	iCurIdx = -1;
}

CResultDlg::CResultDlg(CFrameWnd* pMainFrm) // modeless constructor
{
	m_pMainFrm = pMainFrm;
	iCurIdx = -1;
}

BOOL CResultDlg::Create()
{
	//m_pMainFrm = (CFrameWnd*)AfxGetMainWnd();
	cout << "on create" << endl;
	return CDialog::Create(CResultDlg::IDD);
}

void CResultDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResultDlg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CResultDlg, CDialog)
	//{{AFX_MSG_MAP(CResultDlg)
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_COMMAND(ID_RESULT_LIST, OnResultList)
	ON_COMMAND(ID_ANALYSIS, OnAnalysis)
	ON_COMMAND(ID_CHART_DISTANCEERROR, OnChartDistanceerror)
	ON_COMMAND(ID_CHART_ANGLEERROR, OnChartAngleerror)
	ON_COMMAND(ID_CHART_OBJSPEED, OnChartObjspeed)
	ON_COMMAND(ID_CHART_OBJANGLESPEED, OnChartObjanglespeed)
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResultDlg message handlers

void CResultDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	cout << "on size" << endl;
	RECT wnRect;
	if(m_ListDlg.GetSafeHwnd()!=NULL)
	{
		m_ListDlg.GetWindowRect(&wnRect);
		ScreenToClient(&wnRect);
		m_ListDlg.MoveWindow(wnRect.left,wnRect.top,cx,cy);
	} 
	if(m_ChartDlg.GetSafeHwnd()!=NULL)
	{
		m_ChartDlg.GetWindowRect(&wnRect);
		ScreenToClient(&wnRect);
		m_ChartDlg.MoveWindow(wnRect.left,wnRect.top,cx,cy);
	} 
	if(m_AnalysisDlg.GetSafeHwnd()!=NULL)
	{
		m_AnalysisDlg.GetWindowRect(&wnRect);
		ScreenToClient(&wnRect);
		m_AnalysisDlg.MoveWindow(wnRect.left,wnRect.top,cx,cy);
	} 
}

void CResultDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	cout << "on close" << endl;
	if(m_pMainFrm!=NULL){
		m_pMainFrm->PostMessage(WM_CLOSEDLG,0);
	}			
	CDialog::OnClose();
}

BOOL CResultDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here	
	cout << "on initdialog" << endl;
	CString cs;
    int pos,pos1;
	CMenu *pMenu;
	CMenu addmenu;
    CTaskControlDoc* pDoc;
	CView *pView;
    pView = (CView*)m_pMainFrm->GetActiveView();	
	pDoc = (CTaskControlDoc*)pView->GetDocument();	
	pos = pDoc->m_FileName.ReverseFind('\\');
	pDoc->m_TaskNo = atoi(pDoc->m_FileName.Mid(pos+2,1));
	BOOL bLoadMenu = FALSE;

	CString str;
	switch (pDoc->m_TaskNo)
	{
	case 1:
		if(!addmenu.LoadMenu(IDR_MENU1)) //װ��˵���Դ��
		{
			MessageBox("�˵�װ��ʧ��!","����",MB_OK|MB_ICONERROR); 
			return FALSE;
		}
		bLoadMenu = TRUE;
		SetWindowText("���ݷ�����Ŀ�������������");
		break;
	case 2:
		if(!addmenu.LoadMenu(IDR_MENU2)) //װ��˵���Դ��
		{
			MessageBox("�˵�װ��ʧ��!","����",MB_OK|MB_ICONERROR); 
			return FALSE;
		}
		bLoadMenu = TRUE;
		SetWindowText("���ݷ��������������ּ�ʱ��֪����������");
		break;
	case 3:
		pos = pDoc->m_FileName.ReverseFind('\\');
        pos1 = pDoc->m_FileName.Find('_',pos+1);
		pDoc->m_MainTaskMode = atoi(pDoc->m_FileName.Mid(pos1+1,1))-1;	
        if(pDoc->m_MainTaskMode==0)
		{
			if(!addmenu.LoadMenu(IDR_MENU2)) //װ��˵���Դ��
			{
				MessageBox("�˵�װ��ʧ��!","����",MB_OK|MB_ICONERROR); 
				return FALSE;
			}
			bLoadMenu = TRUE;
		}
		SetWindowText("���ݷ�����˫����ģʽͻ���¼���Ӧʱ����");
		break;
	case 4:
//		if(!addmenu.LoadMenu(IDR_MENU2)) //װ��˵���Դ��
//		{
//			MessageBox("�˵�װ��ʧ��!","����",MB_OK|MB_ICONERROR); 
//			return FALSE;
//		}
		SetWindowText("���ݷ�����������ҵ������������");
		break;
	case 5:
		if(!addmenu.LoadMenu(IDR_MENU2)) //װ��˵���Դ��
		{
			MessageBox("�˵�װ��ʧ��!","����",MB_OK|MB_ICONERROR); 
			return FALSE;
		}
		bLoadMenu = TRUE;
		SetWindowText("���ݷ�����˫����ģʽͼ�������б���������");
		break;
	case 6:
		pos = pDoc->m_FileName.ReverseFind('\\');
        pos1 = pDoc->m_FileName.Find('_',pos+1);
		pDoc->m_MemTaskMode = atoi(pDoc->m_FileName.Mid(pos1+1,1))-1;	
		if(!addmenu.LoadMenu(IDR_MENU2)) //װ��˵���Դ��
		{
			MessageBox("�˵�װ��ʧ��!","����",MB_OK|MB_ICONERROR); 
			return FALSE;
		}
		bLoadMenu = TRUE;
		SetWindowText("���ݷ�����˫����ģʽ��άͼ�μ����б���������");
		break;
	case 7:
		if (!addmenu.LoadMenu(IDR_MENU3)) //װ��˵���Դ��
		{
			MessageBox("�˵�װ��ʧ��!", "����", MB_OK | MB_ICONERROR);
			return FALSE;
		}
		bLoadMenu = TRUE;
		SetWindowText("���ݷ������ٶ�֪���������");
		break;

	case 8:
		if (!addmenu.LoadMenu(IDR_MENU3)) //װ��˵���Դ��
		{
			MessageBox("�˵�װ��ʧ��!", "����", MB_OK | MB_ICONERROR);
			return FALSE;
		}
		bLoadMenu = TRUE;
		SetWindowText("���ݷ�������ά������ת����");
		break;
	}
    if(bLoadMenu)
	{
		str="ͼʾ����";
		pMenu=GetMenu(); 
		pMenu->GetSubMenu(0)->InsertMenu(1,MF_POPUP|MF_BYPOSITION|MF_STRING, 
		(UINT)addmenu.GetSubMenu(0)->m_hMenu,str); 

		pMenu->Detach(); //�����ڲ˵���Cmenu������롣 
		addmenu.Detach();
		DrawMenuBar(); //�ػ��˵��� 
	}
	
	AddPages();
	if(pPages.GetSize()>0)
	{
		CRect rc;
		GetWindowRect(rc);
		ScreenToClient(rc);
		for(int t=0;t<pPages.GetSize();t++)
		{
			CDialog *pDlg=GetDialog(t);
			if(pDlg)
			{
				pDlg->Create(csIds.GetAt(t),this);
				pDlg->SetWindowPos(NULL,rc.left,rc.top+33,rc.Width()-5,rc.Height()-43,SWP_NOZORDER);
			}
		}
		SetCurDlg(0);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CResultDlg::AddPages()
{
	cout << "on addpage" << endl;
	cout << "on m_ListDlg" << endl;
	pPages.Add(&m_ListDlg);
	csIds.Add(IDD_LISTDLG);
	
	cout << "on m_ChartDlg" << endl;
	pPages.Add(&m_ChartDlg);
	csIds.Add(IDD_CHARTDLG);

	cout << "on m_AnalysisDlg" << endl;
	pPages.Add(&m_AnalysisDlg);
	csIds.Add(IDD_ANALYSISDLG);
}

CDialog* CResultDlg::GetDialog(const int id)
{
	cout << "on GetDialog" << endl;
	cout << "page id " << id<< endl;
	cout << "page size " << pPages.GetSize() << endl;
	ASSERT(id>=0&&id<pPages.GetSize());
	return (CDialog *)pPages.GetAt(id);
}

CResultDlg::~CResultDlg()
{
	cout << "on destructor" << endl;
	ClosePages();
	pPages.RemoveAll();
	csIds.RemoveAll();
}

void CResultDlg::ClosePages()
{
	cout << "on closepage" << endl;
	for(int t=0;t<pPages.GetSize();t++)
	{
		CDialog *pDlg=GetDialog(t);
		if(pDlg)
			pDlg->DestroyWindow();
	}
}

void CResultDlg::SetCurDlg(const int id)
{
	cout << "on setcurdlg" << endl;
	cout << "iCurIdx " << iCurIdx << endl;
	cout << "id " << id << endl;
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

void CResultDlg::DataChart(short PlotNo) 
{
	// TODO: Add your control notification handler code here
//	CMainFrame* m_pParent;
//	m_pParent = (CMainFrame*) m_pMainFrm;
//	m_pParent->m_pChartDlg = new CChartDlg(this);

	cout << "on datachart" << endl;
	CTaskControlDoc* pDoc;
	CView *pView;
    pView = (CView*)m_pMainFrm->GetActiveView();	
	pDoc = (CTaskControlDoc*)pView->GetDocument();	
    int i;

	/*switch(pDoc->m_TaskNo)
	{
	case 1:
		switch(PlotNo)
		{
		case 0://λ�������ʱ��仯������
			m_ChartDlg.m_Chart.put_TitleText("λ�������ʱ��仯����");
        	m_ChartDlg.Plot(PlotNo, pDoc->m_PointNum-pDoc->m_ExperStart1,0,1000,pDoc->m_ChartTime,pDoc->m_Distance,pDoc->m_TrialNum,pDoc->m_StartPoint); // displays the dialog window
            break;
		case 1://�Ƕ������ʱ��仯������
			m_ChartDlg.m_Chart.put_TitleText("�Ƕ������ʱ��仯����");
	    	m_ChartDlg.Plot(PlotNo, pDoc->m_PointNum-pDoc->m_ExperStart1,-180,180,pDoc->m_ChartTime,pDoc->m_RotateError,pDoc->m_TrialNum,pDoc->m_StartPoint); // displays the dialog window
			break;
		case 2://Ŀ�ꡢ��׼���ٶ���ʱ��仯������
			m_ChartDlg.m_Chart.put_TitleText("Ŀ�����׼���ٶ���ʱ��仯����");
			m_ChartDlg.Plot(PlotNo, pDoc->m_PointNum-pDoc->m_ExperStart1,-100,100,pDoc->m_ChartTime,pDoc->m_ObjSpeed,pDoc->m_PostSpeed,pDoc->m_TrialNum,pDoc->m_StartPoint); // displays the dialog window
			break;
		case 3://Ŀ�ꡢ��׼�����ٶ���ʱ��仯������
			m_ChartDlg.m_Chart.put_TitleText("Ŀ�����׼�����ٶ���ʱ��仯����");
			m_ChartDlg.Plot(PlotNo, pDoc->m_PointNum-pDoc->m_ExperStart1,-100,100,pDoc->m_ChartTime,pDoc->m_ObjRotateSpeed,pDoc->m_PostRotateSpeed,pDoc->m_TrialNum,pDoc->m_StartPoint); // displays the dialog window
			break;
		}
		break;
	case 2:
	case 3:
	case 5:
	case 6:
		/*switch(PlotNo)
		{
		case 0://λ�������ʱ��仯������
			m_ChartDlg.m_Chart.put_TitleText("λ�������ʱ��仯����");
			m_ChartDlg.Plot(PlotNo, pDoc->m_PointNum-pDoc->m_ExperStart1,0,1000,pDoc->m_ChartTime,pDoc->m_Distance,pDoc->m_TrialNum,pDoc->m_StartPoint); // displays the dialog window
            break;
		case 2://Ŀ�ꡢ��׼���ٶ���ʱ��仯������
			/*m_ChartDlg.m_Chart.put_TitleText("Ŀ�����׼���ٶ���ʱ��仯����");
			m_ChartDlg.Plot(PlotNo, pDoc->m_PointNum-pDoc->m_ExperStart1,-100,100,pDoc->m_ChartTime,pDoc->m_ObjSpeed,pDoc->m_PostSpeed,pDoc->m_TrialNum,pDoc->m_StartPoint); // displays the dialog window
			break;
		}
		break;
	case 7:
		break;
	}*/
	SetCurDlg(1);
}

//������ݷ���
void CResultDlg::OnAnalysis() 
{
	// TODO: Add your control notification handler code here
	cout << "on analysis" << endl;
	CTaskControlDoc* pDoc;
	CView *pView;
    pView = (CView*)m_pMainFrm->GetActiveView();	
	pDoc = (CTaskControlDoc*)pView->GetDocument();	

	pDoc->DataAnalysis();
	m_AnalysisDlg.DisplayResult();
	SetCurDlg(2);
}

//��ʾ�б�����
void CResultDlg::OnResultList() 
{
	// TODO: Add your command handler code here
	cout << "on reslist" << endl;
	SetCurDlg(0);
}

//����Ŀ�����׼������
void CResultDlg::OnChartDistanceerror() 
{
	// TODO: Add your command handler code here
    DataChart(0);
}

//����Ŀ�����׼���Ƕ����
void CResultDlg::OnChartAngleerror() 
{
	// TODO: Add your command handler code here
	DataChart(1);	
}

//����Ŀ���ٶ�
void CResultDlg::OnChartObjspeed() 
{
	// TODO: Add your command handler code here
	DataChart(2);	
}

//����Ŀ����ٶ�
void CResultDlg::OnChartObjanglespeed() 
{
	// TODO: Add your command handler code here
	DataChart(3);	
}


HBRUSH CResultDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	cout << "on ctlcolor" << endl;
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_EDIT){
		pDC->SetBkColor(RGB(255,255,255));
	}
	return hbr;
}
