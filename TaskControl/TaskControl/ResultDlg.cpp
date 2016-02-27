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
		if(!addmenu.LoadMenu(IDR_MENU1)) //装入菜单资源。
		{
			MessageBox("菜单装入失败!","错误",MB_OK|MB_ICONERROR); 
			return FALSE;
		}
		bLoadMenu = TRUE;
		SetWindowText("数据分析—目标跟踪能力测试");
		break;
	case 2:
		if(!addmenu.LoadMenu(IDR_MENU2)) //装入菜单资源。
		{
			MessageBox("菜单装入失败!","错误",MB_OK|MB_ICONERROR); 
			return FALSE;
		}
		bLoadMenu = TRUE;
		SetWindowText("数据分析—操作力保持及时间知觉能力测试");
		break;
	case 3:
		pos = pDoc->m_FileName.ReverseFind('\\');
        pos1 = pDoc->m_FileName.Find('_',pos+1);
		pDoc->m_MainTaskMode = atoi(pDoc->m_FileName.Mid(pos1+1,1))-1;	
        if(pDoc->m_MainTaskMode==0)
		{
			if(!addmenu.LoadMenu(IDR_MENU2)) //装入菜单资源。
			{
				MessageBox("菜单装入失败!","错误",MB_OK|MB_ICONERROR); 
				return FALSE;
			}
			bLoadMenu = TRUE;
		}
		SetWindowText("数据分析—双任务模式突发事件反应时测试");
		break;
	case 4:
//		if(!addmenu.LoadMenu(IDR_MENU2)) //装入菜单资源。
//		{
//			MessageBox("菜单装入失败!","错误",MB_OK|MB_ICONERROR); 
//			return FALSE;
//		}
		SetWindowText("数据分析—触点作业操作能力测试");
		break;
	case 5:
		if(!addmenu.LoadMenu(IDR_MENU2)) //装入菜单资源。
		{
			MessageBox("菜单装入失败!","错误",MB_OK|MB_ICONERROR); 
			return FALSE;
		}
		bLoadMenu = TRUE;
		SetWindowText("数据分析—双任务模式图符记忆判别能力测试");
		break;
	case 6:
		pos = pDoc->m_FileName.ReverseFind('\\');
        pos1 = pDoc->m_FileName.Find('_',pos+1);
		pDoc->m_MemTaskMode = atoi(pDoc->m_FileName.Mid(pos1+1,1))-1;	
		if(!addmenu.LoadMenu(IDR_MENU2)) //装入菜单资源。
		{
			MessageBox("菜单装入失败!","错误",MB_OK|MB_ICONERROR); 
			return FALSE;
		}
		bLoadMenu = TRUE;
		SetWindowText("数据分析—双任务模式三维图形记忆判别能力测试");
		break;
	case 7:
		if (!addmenu.LoadMenu(IDR_MENU3)) //装入菜单资源。
		{
			MessageBox("菜单装入失败!", "错误", MB_OK | MB_ICONERROR);
			return FALSE;
		}
		bLoadMenu = TRUE;
		SetWindowText("数据分析—速度知觉任务测试");
		break;

	case 8:
		if (!addmenu.LoadMenu(IDR_MENU3)) //装入菜单资源。
		{
			MessageBox("菜单装入失败!", "错误", MB_OK | MB_ICONERROR);
			return FALSE;
		}
		bLoadMenu = TRUE;
		SetWindowText("数据分析—三维心理旋转测试");
		break;
	}
    if(bLoadMenu)
	{
		str="图示数据";
		pMenu=GetMenu(); 
		pMenu->GetSubMenu(0)->InsertMenu(1,MF_POPUP|MF_BYPOSITION|MF_STRING, 
		(UINT)addmenu.GetSubMenu(0)->m_hMenu,str); 

		pMenu->Detach(); //将窗口菜单与Cmenu对象分离。 
		addmenu.Detach();
		DrawMenuBar(); //重画菜单。 
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
		case 0://位移误差随时间变化的曲线
			m_ChartDlg.m_Chart.put_TitleText("位移误差随时间变化曲线");
        	m_ChartDlg.Plot(PlotNo, pDoc->m_PointNum-pDoc->m_ExperStart1,0,1000,pDoc->m_ChartTime,pDoc->m_Distance,pDoc->m_TrialNum,pDoc->m_StartPoint); // displays the dialog window
            break;
		case 1://角度误差随时间变化的曲线
			m_ChartDlg.m_Chart.put_TitleText("角度误差随时间变化曲线");
	    	m_ChartDlg.Plot(PlotNo, pDoc->m_PointNum-pDoc->m_ExperStart1,-180,180,pDoc->m_ChartTime,pDoc->m_RotateError,pDoc->m_TrialNum,pDoc->m_StartPoint); // displays the dialog window
			break;
		case 2://目标、瞄准器速度随时间变化的曲线
			m_ChartDlg.m_Chart.put_TitleText("目标和瞄准器速度随时间变化曲线");
			m_ChartDlg.Plot(PlotNo, pDoc->m_PointNum-pDoc->m_ExperStart1,-100,100,pDoc->m_ChartTime,pDoc->m_ObjSpeed,pDoc->m_PostSpeed,pDoc->m_TrialNum,pDoc->m_StartPoint); // displays the dialog window
			break;
		case 3://目标、瞄准器角速度随时间变化的曲线
			m_ChartDlg.m_Chart.put_TitleText("目标和瞄准器角速度随时间变化曲线");
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
		case 0://位移误差随时间变化的曲线
			m_ChartDlg.m_Chart.put_TitleText("位移误差随时间变化曲线");
			m_ChartDlg.Plot(PlotNo, pDoc->m_PointNum-pDoc->m_ExperStart1,0,1000,pDoc->m_ChartTime,pDoc->m_Distance,pDoc->m_TrialNum,pDoc->m_StartPoint); // displays the dialog window
            break;
		case 2://目标、瞄准器速度随时间变化的曲线
			/*m_ChartDlg.m_Chart.put_TitleText("目标和瞄准器速度随时间变化曲线");
			m_ChartDlg.Plot(PlotNo, pDoc->m_PointNum-pDoc->m_ExperStart1,-100,100,pDoc->m_ChartTime,pDoc->m_ObjSpeed,pDoc->m_PostSpeed,pDoc->m_TrialNum,pDoc->m_StartPoint); // displays the dialog window
			break;
		}
		break;
	case 7:
		break;
	}*/
	SetCurDlg(1);
}

//结果数据分析
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

//显示列表数据
void CResultDlg::OnResultList() 
{
	// TODO: Add your command handler code here
	cout << "on reslist" << endl;
	SetCurDlg(0);
}

//绘制目标和瞄准器距离
void CResultDlg::OnChartDistanceerror() 
{
	// TODO: Add your command handler code here
    DataChart(0);
}

//绘制目标和瞄准器角度误差
void CResultDlg::OnChartAngleerror() 
{
	// TODO: Add your command handler code here
	DataChart(1);	
}

//绘制目标速度
void CResultDlg::OnChartObjspeed() 
{
	// TODO: Add your command handler code here
	DataChart(2);	
}

//绘制目标角速度
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
