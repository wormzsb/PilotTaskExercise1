// ListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "taskcontrol.h"
#include "ListDlg.h"
#include "MainFrm.h"
#include <direct.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListDlg dialog


CListDlg::CListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CListDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CListDlg)
	//}}AFX_DATA_INIT
}


void CListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CListDlg)
	DDX_Control(pDX, IDC_RESULTLIST, m_ResultList);
	DDX_Control(pDX, IDC_RESULTLIST2, m_ResultList2);
	DDX_Control(pDX, IDC_TAB1, m_TabCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CListDlg, CDialog)
	//{{AFX_MSG_MAP(CListDlg)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab1)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListDlg message handlers

void CListDlg::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int t = m_TabCtrl.GetCurSel();
	switch(t)
	{
	case 0:
		m_ResultList2.SetWindowPos(&wndBottom,10,10,200,200,SWP_HIDEWINDOW|SWP_NOMOVE|SWP_NOSIZE);
		m_ResultList.SetWindowPos(&wndBottom,10,10,200,200,SWP_SHOWWINDOW|SWP_NOMOVE|SWP_NOSIZE);
		break;
	case 1:
		m_ResultList.SetWindowPos(&wndBottom,10,10,200,200,SWP_HIDEWINDOW|SWP_NOMOVE|SWP_NOSIZE);
		m_ResultList2.SetWindowPos(&wndBottom,10,10,200,200,SWP_SHOWWINDOW|SWP_NOMOVE|SWP_NOSIZE);
		break;
	}
	*pResult = 0;	
}

void CListDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	RECT wnRect;
	if(m_TabCtrl.GetSafeHwnd()!=NULL)
	{
		m_TabCtrl.GetWindowRect(&wnRect);
		ScreenToClient(&wnRect);
		m_TabCtrl.MoveWindow(wnRect.left,wnRect.top,cx-20,cy-13);
	}
	if(m_ResultList.GetSafeHwnd()!=NULL)
	{
		m_ResultList.GetWindowRect(&wnRect);
		ScreenToClient(&wnRect);
		m_ResultList.MoveWindow(wnRect.left,wnRect.top,cx-50,cy-53);
	}
	if(m_ResultList2.GetSafeHwnd()!=NULL)
	{
		m_ResultList2.GetWindowRect(&wnRect);
		ScreenToClient(&wnRect);
		m_ResultList2.MoveWindow(wnRect.left,wnRect.top,cx-50,cy-53);
	}	
}

BOOL CListDlg::AddHeadT7(){
	m_ResultList.AddColumn(_T("测试序号"), 1, 80, LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("按键距离"), 1, 100, LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("偏差率"), 1, 120, LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("小球速度"), 1, 80, LVCFMT_RIGHT);
	return TRUE;
}


BOOL CListDlg::AddHeadT1()
{
    m_ResultList.AddColumn(_T("ID"),1,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Name"),2,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Sex"),3,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Session"),4,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("DistanceError"),5,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("AngleError"),6,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PracMode"),7,80,LVCFMT_RIGHT);
    m_ResultList.AddColumn(_T("ExperMode"),8,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Background"),9,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Track"),10,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Direction"),11,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("MoveMode"),12,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("SpeedMode"),13,80,LVCFMT_RIGHT);
    m_ResultList.AddColumn(_T("Pause"),14,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PauseNum"),15,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Speed"),16,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("InitSpeed"),17,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("SpeedMin"),18,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("SpeedMax"),19,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("AccelerationMin"),20,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("AccelerationMax"),21,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("AngleSpeedMin"),22,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("AngleSpeedMax"),23,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("RotateAngleMin"),24,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("RotateAngleMax"),25,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PracTime"),26,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("ExperTime"),27,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PracTimes"),28,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("ExperTimes"),29,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Pra_Test"),30,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Trial"),31,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PointNum"),32,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PointTime"),33,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("ObjPointX"),34,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("ObjPointY"),35,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PostPointX"),36,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PostPointY"),37,80,LVCFMT_RIGHT);

	m_ResultList.AddColumn(_T("ObjRotate"),38,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PostRotate"),39,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Distance"),40,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("RotateError"),41,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Hit"),42,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("ObjSpeedX"),43,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("ObjSpeedY"),44,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PostSpeedX"),45,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PostSpeedY"),46,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("ObjRotateSpeed"),47,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PostRotateSpeed"),48,80,LVCFMT_RIGHT);
	return TRUE;
}

BOOL CListDlg::AddHeadT2Trace()
{
    m_ResultList.AddColumn(_T("ID"),1,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Name"),2,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Sex"),3,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Session"),4,80,LVCFMT_RIGHT);

	m_ResultList.AddColumn(_T("DistanceError"),5,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PracMode"),6,80,LVCFMT_RIGHT);
    m_ResultList.AddColumn(_T("ExperMode"),7,80,LVCFMT_RIGHT);
    m_ResultList.AddColumn(_T("MainTask"),8,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("SubTask"),9,80,LVCFMT_RIGHT);

	m_ResultList.AddColumn(_T("Background"),10,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Direction"),11,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("InitSpeed"),12,80,LVCFMT_RIGHT);

	m_ResultList.AddColumn(_T("HoldTimeNum"),13,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("HoldTime1"),14,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("HoldTime2"),15,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("HoldTime3"),16,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("HoldTime4"),17,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("HoldTime5"),18,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("HoldTime6"),19,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("HoldTime7"),20,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("HoldTime8"),21,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("HoldTime9"),22,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("HoldTime10"),23,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("HoldTime11"),24,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("HoldTime12"),25,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PracTime"),26,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("ExperTime"),27,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PracTimes"),28,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("ExperTimes"),29,80,LVCFMT_RIGHT);

	m_ResultList.AddColumn(_T("Pra_Test"),30,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PointNum"),31,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PointTime"),32,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("ObjPointX"),33,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("ObjPointY"),34,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PostPointX"),35,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PostPointY"),36,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Distance"),37,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Hit"),38,80,LVCFMT_RIGHT);

	m_ResultList.AddColumn(_T("ObjSpeedX"),39,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("ObjSpeedY"),40,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PostSpeedX"),41,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PostSpeedY"),42,80,LVCFMT_RIGHT);
	return TRUE;
}

BOOL CListDlg::AddHeadT2Hold()
{
    m_ResultList2.AddColumn(_T("ID"),1,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("Name"),2,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("Sex"),3,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("Session"),4,80,LVCFMT_RIGHT);

	m_ResultList2.AddColumn(_T("DistanceError"),5,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("PracMode"),6,80,LVCFMT_RIGHT);
    m_ResultList2.AddColumn(_T("ExperMode"),7,80,LVCFMT_RIGHT);
    m_ResultList2.AddColumn(_T("MainTask"),8,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("SubTask"),9,80,LVCFMT_RIGHT);

	m_ResultList2.AddColumn(_T("Background"),10,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("Direction"),11,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("InitSpeed"),12,80,LVCFMT_RIGHT);

	m_ResultList2.AddColumn(_T("HoldTimeNum"),13,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("HoldTime1"),14,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("HoldTime2"),15,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("HoldTime3"),16,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("HoldTime4"),17,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("HoldTime5"),18,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("HoldTime6"),19,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("HoldTime7"),20,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("HoldTime8"),21,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("HoldTime9"),22,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("HoldTime10"),23,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("HoldTime11"),24,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("HoldTime12"),25,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("PracTime"),26,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("ExperTime"),27,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("PracTimes"),28,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("ExperTimes"),29,80,LVCFMT_RIGHT);

    m_ResultList2.AddColumn(_T("Pra_Test"),30,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("HoldNum"),31,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("HoldTime"),32,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("StartTime"),33,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("SureTime"),34,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("Test_RT"),35,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("HoldError"),36,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("Error_Ratio"),37,80,LVCFMT_RIGHT);
	return TRUE;
}

BOOL CListDlg::AddHeadT3Trace()
{
	m_ResultList.AddColumn(_T("ID"),1,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Name"),2,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Sex"),3,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Session"),4,80,LVCFMT_RIGHT);

	m_ResultList.AddColumn(_T("DistanceError"),5,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PracMode"),6,80,LVCFMT_RIGHT);
    m_ResultList.AddColumn(_T("ExperMode"),7,80,LVCFMT_RIGHT);
    m_ResultList.AddColumn(_T("MainTask"),8,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("SubTask"),9,80,LVCFMT_RIGHT);
	
	m_ResultList.AddColumn(_T("MainTaskMode"),10,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Background"),11,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("InitSpeed"),12,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("CodePairMode"),13,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("CodePairNum"),14,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("DisplayMode"),15,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("EventFrequency"),16,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PracTime"),17,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("ExperTime"),18,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PracTimes"),19,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("ExperTimes"),20,80,LVCFMT_RIGHT);

	m_ResultList.AddColumn(_T("Pra_Test"),21,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PointNum"),22,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PointTime"),23,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("ObjPointX"),24,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("ObjPointY"),25,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PostPointX"),26,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PostPointY"),27,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Distance"),28,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Hit"),29,80,LVCFMT_RIGHT);

	m_ResultList.AddColumn(_T("ObjSpeedX"),30,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("ObjSpeedY"),31,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PostSpeedX"),32,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PostSpeedY"),33,80,LVCFMT_RIGHT);
	return TRUE;
}

BOOL CListDlg::AddHeadT3Code()
{
	m_ResultList.AddColumn(_T("ID"),1,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Name"),2,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Sex"),3,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Session"),4,80,LVCFMT_RIGHT);

	m_ResultList.AddColumn(_T("PracMode"),5,80,LVCFMT_RIGHT);
    m_ResultList.AddColumn(_T("ExperMode"),6,80,LVCFMT_RIGHT);
    m_ResultList.AddColumn(_T("MainTask"),7,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("SubTask"),8,80,LVCFMT_RIGHT);

	m_ResultList.AddColumn(_T("MainTaskMode"),9,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Background"),10,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("InitSpeed"),11,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("EventMode"),12,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("CodePairMode"),13,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("CodePairNum"),14,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("DisplayMode"),15,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("EventFrequency"),16,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PracTime"),17,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("ExperTime"),18,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PracTimes"),19,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("ExperTimes"),20,80,LVCFMT_RIGHT);

	m_ResultList.AddColumn(_T("Shape1"),21,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Number1"),22,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Shape2"),23,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Number2"),24,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Shape3"),25,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Number3"),26,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Shape4"),27,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Number4"),28,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Shape5"),29,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Number5"),30,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Shape6"),31,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Number6"),32,80,LVCFMT_RIGHT);

	m_ResultList.AddColumn(_T("Pra_Test"),33,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("CodeNum"),34,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("CodeType"),35,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("StartTime"),36,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("SureTime"),37,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("ButtonNo"),38,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Code_RT"),39,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Code_ACC"),40,80,LVCFMT_RIGHT);
	return TRUE;
}

BOOL CListDlg::AddHeadT3Event()
{
	m_ResultList2.AddColumn(_T("ID"),1,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("Name"),2,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("Sex"),3,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("Session"),4,80,LVCFMT_RIGHT);

	m_ResultList2.AddColumn(_T("PracMode"),5,80,LVCFMT_RIGHT);
    m_ResultList2.AddColumn(_T("ExperMode"),6,80,LVCFMT_RIGHT);
    m_ResultList2.AddColumn(_T("MainTask"),7,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("SubTask"),8,80,LVCFMT_RIGHT);

	m_ResultList2.AddColumn(_T("MainTaskMode"),9,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("Background"),10,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("InitSpeed"),11,80,LVCFMT_RIGHT);
    m_ResultList2.AddColumn(_T("EventMode"),12,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("CodePairMode"),13,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("CodePairNum"),14,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("DisplayMode"),15,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("EventFrequency"),16,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("PracTime"),17,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("ExperTime"),18,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("PracTimes"),19,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("ExperTimes"),20,80,LVCFMT_RIGHT);

	m_ResultList2.AddColumn(_T("Pra_Test"),21,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("EventNum"),22,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("EventType"),23,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("StartTime"),24,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("SureTime"),25,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("Event_RT"),26,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("ButtonNo"),27,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("Event_Acc"),28,80,LVCFMT_RIGHT);
	return TRUE;
}

BOOL CListDlg::AddHeadT4()
{
    m_ResultList.AddColumn(_T("ID"),1,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Name"),2,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Sex"),3,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Session"),4,80,LVCFMT_RIGHT);

	m_ResultList.AddColumn(_T("PracMode"),5,80,LVCFMT_RIGHT);
    m_ResultList.AddColumn(_T("ExperMode"),6,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("TouchDirection"),7,80,LVCFMT_RIGHT);

	m_ResultList.AddColumn(_T("Pra_Test"),8,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("GroupNo"),9,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("TestNo"),10,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("TouchNo"),11,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Distance"),12,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("SizeDiff"),13,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("SureNo"),14,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("StartTime"),15,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("TouchTime"),16,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Touch_RT"),17,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Touch_Acc"),18,80,LVCFMT_RIGHT);
	return TRUE;
}

BOOL CListDlg::AddHeadT5Trace()
{
	m_ResultList.AddColumn(_T("ID"),1,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Name"),2,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Sex"),3,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Session"),4,80,LVCFMT_RIGHT);

	m_ResultList.AddColumn(_T("DistanceError"),5,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PracMode"),6,80,LVCFMT_RIGHT);
    m_ResultList.AddColumn(_T("ExperMode"),7,80,LVCFMT_RIGHT);
    m_ResultList.AddColumn(_T("MainTask"),8,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("SubTask"),9,80,LVCFMT_RIGHT);
	
	m_ResultList.AddColumn(_T("Background"),10,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("InitSpeed"),11,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("SignMemType"),12,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("SignMemMode"),13,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("SignMemNum"),14,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("SignShowMode"),15,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("SignShowTime"),16,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PracTime"),17,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("ExperTime"),18,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PracTimes"),19,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("ExperTimes"),20,80,LVCFMT_RIGHT);

	m_ResultList.AddColumn(_T("Pra_Test"),21,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PointNum"),22,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PointTime"),23,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("ObjPointX"),24,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("ObjPointY"),25,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PostPointX"),26,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PostPointY"),27,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Distance"),28,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Hit"),29,80,LVCFMT_RIGHT);

	m_ResultList.AddColumn(_T("ObjSpeedX"),30,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("ObjSpeedY"),31,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PostSpeedX"),32,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PostSpeedY"),33,80,LVCFMT_RIGHT);
	return TRUE;
}

BOOL CListDlg::AddHeadT5Sign()
{
	m_ResultList2.AddColumn(_T("ID"),1,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("Name"),2,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("Sex"),3,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("Session"),4,80,LVCFMT_RIGHT);

	m_ResultList2.AddColumn(_T("DistanceError"),5,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("PracMode"),6,80,LVCFMT_RIGHT);
    m_ResultList2.AddColumn(_T("ExperMode"),7,80,LVCFMT_RIGHT);
    m_ResultList2.AddColumn(_T("MainTask"),8,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("SubTask"),9,80,LVCFMT_RIGHT);

	m_ResultList2.AddColumn(_T("Background"),10,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("InitSpeed"),11,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("SignMemType"),12,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("SignMemMode"),13,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("SignMemNum"),14,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("SignShowMode"),15,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("SignShowTime"),16,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("PracTime"),17,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("ExperTime"),18,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("PracTimes"),19,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("ExperTimes"),20,80,LVCFMT_RIGHT);

	m_ResultList2.AddColumn(_T("Pra_Test"),21,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("GroupNo"),22,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("SignNo"),23,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("MemTime"),24,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("SignType"),25,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("SignName"),26,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("StartTime"),27,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("SureTime"),28,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("SureButton"),29,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("Sign_RT"),30,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("Sign_ACC"),31,80,LVCFMT_RIGHT);
	return TRUE;
}

BOOL CListDlg::AddHeadT6Trace()
{
	m_ResultList.AddColumn(_T("ID"),1,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Name"),2,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Sex"),3,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Session"),4,80,LVCFMT_RIGHT);

	m_ResultList.AddColumn(_T("DistanceError"),5,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PracMode"),6,80,LVCFMT_RIGHT);
    m_ResultList.AddColumn(_T("ExperMode"),7,80,LVCFMT_RIGHT);
    m_ResultList.AddColumn(_T("MainTask"),8,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("SubTask"),9,80,LVCFMT_RIGHT);
	
	m_ResultList.AddColumn(_T("Background"),10,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("InitSpeed"),11,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("CubeNum1"),12,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("CubeNum2"),13,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("CubeNum3"),14,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("CubeNum4"),15,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Prototype"),16,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("RefAxis"),17,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("MemTaskMode"),18,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PracTime"),19,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("ExperTime"),20,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PracTimes"),21,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("ExperTimes"),22,80,LVCFMT_RIGHT);

	m_ResultList.AddColumn(_T("Pra_Test"),23,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PointNum"),24,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PointTime"),25,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("ObjPointX"),26,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("ObjPointY"),27,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PostPointX"),28,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PostPointY"),29,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Distance"),30,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("Hit"),31,80,LVCFMT_RIGHT);

	m_ResultList.AddColumn(_T("ObjSpeedX"),32,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("ObjSpeedY"),33,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PostSpeedX"),34,80,LVCFMT_RIGHT);
	m_ResultList.AddColumn(_T("PostSpeedY"),35,80,LVCFMT_RIGHT);
	return TRUE;
}

BOOL CListDlg::AddHeadT6Judge()
{
	m_ResultList2.AddColumn(_T("ID"),1,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("Name"),2,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("Sex"),3,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("Session"),4,80,LVCFMT_RIGHT);

	m_ResultList2.AddColumn(_T("DistanceError"),5,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("PracMode"),6,80,LVCFMT_RIGHT);
    m_ResultList2.AddColumn(_T("ExperMode"),7,80,LVCFMT_RIGHT);
    m_ResultList2.AddColumn(_T("MainTask"),8,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("SubTask"),9,80,LVCFMT_RIGHT);

	m_ResultList2.AddColumn(_T("Background"),10,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("InitSpeed"),11,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("CubeNum1"),12,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("CubeNum2"),13,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("CubeNum3"),14,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("CubeNum4"),15,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("Prototype"),16,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("RefAxis"),17,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("MemTaskMode"),18,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("PracTime"),19,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("ExperTime"),20,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("PracTimes"),21,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("ExperTimes"),22,80,LVCFMT_RIGHT);

	m_ResultList2.AddColumn(_T("Pra_Test"),23,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("GroupNo"),24,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("MemNo"),25,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("MemCubeNum"),26,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("LMemName"),27,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("RMemName"),28,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("LMemAngle"),29,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("RMemAngle"),30,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("MemAngleDiff"),31,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("Same"),32,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("StartTime"),33,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("SureTime"),34,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("SureButton"),35,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("Mem_RT"),36,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("Mem_ACC"),37,80,LVCFMT_RIGHT);
	return TRUE;
}

BOOL CListDlg::AddHeadT6Memory()
{
	m_ResultList2.AddColumn(_T("ID"),1,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("Name"),2,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("Sex"),3,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("Session"),4,80,LVCFMT_RIGHT);

	m_ResultList2.AddColumn(_T("DistanceError"),5,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("PracMode"),6,80,LVCFMT_RIGHT);
    m_ResultList2.AddColumn(_T("ExperMode"),7,80,LVCFMT_RIGHT);
    m_ResultList2.AddColumn(_T("MainTask"),8,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("SubTask"),9,80,LVCFMT_RIGHT);

	m_ResultList2.AddColumn(_T("Background"),10,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("InitSpeed"),11,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("CubeNum1"),12,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("CubeNum2"),13,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("CubeNum3"),14,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("CubeNum4"),15,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("Prototype"),16,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("RefAxis"),17,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("MemTaskMode"),18,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("PracTime"),19,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("ExperTime"),20,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("PracTimes"),21,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("ExperTimes"),22,80,LVCFMT_RIGHT);

	m_ResultList2.AddColumn(_T("Pra_Test"),23,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("GroupNo"),24,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("MemNo"),25,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("MemCubeNum"),26,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("LMemName"),27,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("RMemName"),28,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("LMemAngle"),29,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("RMemAngle"),30,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("MemAngleDiff"),31,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("Same"),32,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("StartTime"),33,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("SureTime"),34,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("SureButton"),35,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("Mem_RT"),36,80,LVCFMT_RIGHT);
	m_ResultList2.AddColumn(_T("Mem_ACC"),37,80,LVCFMT_RIGHT);
	return TRUE;
}


BOOL CListDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
    CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();

	int pos,pos1,pos2;

	pos = pDoc->m_FileName.ReverseFind('-');
	pDoc->m_TestTime = pDoc->m_FileName.Mid(pos+1,14);

	CString cs;
	TC_ITEM ti;
    m_ResultList.SetExtendedStyle(LVS_EX_HEADERDRAGDROP|LVS_EX_FULLROWSELECT
		|LVS_EX_GRIDLINES|LVS_EX_SUBITEMIMAGES);
    m_ResultList2.SetExtendedStyle(LVS_EX_HEADERDRAGDROP|LVS_EX_FULLROWSELECT
		|LVS_EX_GRIDLINES|LVS_EX_SUBITEMIMAGES);
	m_ResultList2.SetWindowPos(&wndBottom,10,10,200,200,SWP_HIDEWINDOW|SWP_NOMOVE|SWP_NOSIZE);
	m_ResultList.SetWindowPos(&wndBottom,10,10,200,200,SWP_SHOWWINDOW|SWP_NOMOVE|SWP_NOSIZE);

	int i;
	CString str;

	for(i=0;i<50;i++)
	{
		pDoc->m_StartPoint[i] = 0;
	}

	switch (pDoc->m_TaskNo)
	{
	case 1:
		if (m_TabCtrl.GetSafeHwnd())
		{
			cs = "目标追踪结果";
			ti.mask = TCIF_TEXT|TCIF_PARAM;
			ti.pszText = cs.LockBuffer();
//			ti.lParam = (long) pView;
			m_TabCtrl.InsertItem(m_TabCtrl.GetItemCount(), &ti);
			cs.UnlockBuffer();
		}

		m_ResultList.DeleteAllItems();            //删除列表中所有内容(行)
		while (m_ResultList.DeleteColumn(0));     //删除列表中所有列
		//向列表框中添加列
		if(pDoc->m_Setting1!=NULL)
		{
			delete []pDoc->m_Setting1;
			pDoc->m_Setting1 = NULL;
		}
		pDoc->m_Setting1 = new struct TaskSetting1[1];
        AddHeadT1();
		pDoc->MemClear();
        pDoc->m_bOpenFile1 = pDoc->ReadT1();
		break;
	case 2:
		if (m_TabCtrl.GetSafeHwnd())
		{
			cs = "目标追踪结果";
			ti.mask = TCIF_TEXT|TCIF_PARAM;
			ti.pszText = cs.LockBuffer();
//			ti.lParam = (long) pView;
			m_TabCtrl.InsertItem(m_TabCtrl.GetItemCount(), &ti);
			cs.UnlockBuffer();

			cs = "时间保持结果";
			ti.mask = TCIF_TEXT|TCIF_PARAM;
			ti.pszText = cs.LockBuffer();
//			ti.lParam = (long) pView;
			m_TabCtrl.InsertItem(m_TabCtrl.GetItemCount(), &ti);
			cs.UnlockBuffer();
		}
		m_ResultList.DeleteAllItems();            //删除列表中所有内容(行)
		while (m_ResultList.DeleteColumn(0));     //删除列表中所有列
		//向列表框中添加列
		if(pDoc->m_Setting2!=NULL)
		{
			delete []pDoc->m_Setting2;
			pDoc->m_Setting2 = NULL;
		}
		pDoc->m_Setting2 = new struct TaskSetting2[1];
        AddHeadT2Trace();

		m_ResultList2.DeleteAllItems();            //删除列表中所有内容(行)
		while (m_ResultList2.DeleteColumn(0));     //删除列表中所有列
		//向列表框中添加列
        AddHeadT2Hold();
		pos = pDoc->m_FileName.ReverseFind('\\');
        pos1 = pDoc->m_FileName.Find('-',pos+1);
		pos2 = pDoc->m_FileName.Find('-',pos1+1);
		pDoc->m_FileName1 = pDoc->m_FileName.Left(pos+1)+"T2-trace"+pDoc->m_FileName.Right(pDoc->m_FileName.GetLength()-pos2);
		pDoc->m_FileName2 = pDoc->m_FileName.Left(pos+1)+"T2-hold"+pDoc->m_FileName.Right(pDoc->m_FileName.GetLength()-pos2);
        pDoc->MemClear();
		pDoc->m_bOpenFile1 = pDoc->ReadT2Trace();
		pDoc->m_bOpenFile2 = pDoc->ReadT2Hold();
		break;
	case 3:
		if (m_TabCtrl.GetSafeHwnd())
		{
			if(pDoc->m_MainTaskMode == 0)
			{
				cs = "目标追踪结果";
			}
			else
			{
                cs = "编码测试结果";
			}
			ti.mask = TCIF_TEXT|TCIF_PARAM;
			ti.pszText = cs.LockBuffer();
//			ti.lParam = (long) pView;
			m_TabCtrl.InsertItem(m_TabCtrl.GetItemCount(), &ti);
			cs.UnlockBuffer();

			cs = "突发事件结果";
			ti.mask = TCIF_TEXT|TCIF_PARAM;
			ti.pszText = cs.LockBuffer();
//			ti.lParam = (long) pView;
			m_TabCtrl.InsertItem(m_TabCtrl.GetItemCount(), &ti);
			cs.UnlockBuffer();
		}
//		if(pDoc->m_MainTaskMode == 0)
//		{
//			m_ChartList.InsertString(0,"位移误差随时间变化的曲线");
//			m_ChartList.InsertString(1,"目标速度随时间变化的曲线");
//			m_ChartList.InsertString(2,"瞄准器速度随时间变化的曲线");
//			m_ChartList.SetCurSel(0);
//		}
		m_ResultList.DeleteAllItems();            //删除列表中所有内容(行)
		while (m_ResultList.DeleteColumn(0));     //删除列表中所有列
		//向列表框中添加列 
		if(pDoc->m_Setting3!=NULL)
		{
			delete []pDoc->m_Setting3;
			pDoc->m_Setting3 = NULL;
		}
		pDoc->m_Setting3 = new struct TaskSetting3[1];
		pos = pDoc->m_FileName.ReverseFind('\\');
        pos1 = pDoc->m_FileName.Find('-',pos+1);
		pos2 = pDoc->m_FileName.Find('-',pos1+1);	
		pDoc->MemClear();
		if(pDoc->m_MainTaskMode == 0)
		{
			AddHeadT3Trace();
			pDoc->m_FileName1 = pDoc->m_FileName.Left(pos+1)+"T3_1-trace"+pDoc->m_FileName.Right(pDoc->m_FileName.GetLength()-pos2);
	     	pDoc->m_FileName2 = pDoc->m_FileName.Left(pos+1)+"T3_1-event"+pDoc->m_FileName.Right(pDoc->m_FileName.GetLength()-pos2);
            pDoc->m_bOpenFile1 = pDoc->ReadT3Trace();
		}
		else
		{
            AddHeadT3Code();
			pDoc->m_FileName1 = pDoc->m_FileName.Left(pos+1)+"T3_2-code"+pDoc->m_FileName.Right(pDoc->m_FileName.GetLength()-pos2);
		    pDoc->m_FileName2 = pDoc->m_FileName.Left(pos+1)+"T3_2-event"+pDoc->m_FileName.Right(pDoc->m_FileName.GetLength()-pos2);
			pDoc->m_bOpenFile1 = pDoc->ReadT3Code();
		}
		m_ResultList2.DeleteAllItems();            //删除列表中所有内容(行)
		while (m_ResultList2.DeleteColumn(0));     //删除列表中所有列
		//向列表框中添加列
        AddHeadT3Event();
		pDoc->m_bOpenFile2 = pDoc->ReadT3Event();
		break;
	case 4:
		if (m_TabCtrl.GetSafeHwnd())
		{
			cs = "触点测试结果";
			ti.mask = TCIF_TEXT|TCIF_PARAM;
			ti.pszText = cs.LockBuffer();
//			ti.lParam = (long) pView;
			m_TabCtrl.InsertItem(m_TabCtrl.GetItemCount(), &ti);
			cs.UnlockBuffer();
		}
		m_ResultList.DeleteAllItems();            //删除列表中所有内容(行)
		while (m_ResultList.DeleteColumn(0));     //删除列表中所有列
		//向列表框中添加列
		if(pDoc->m_Setting4!=NULL)
		{
			delete []pDoc->m_Setting4;
			pDoc->m_Setting4 = NULL;
		}
		pDoc->m_Setting4 = new struct TaskSetting4[1];
        AddHeadT4();
		pDoc->MemClear();		
		pDoc->m_bOpenFile1 = pDoc->ReadT4();
		break;
	case 5:
		if (m_TabCtrl.GetSafeHwnd())
		{
			cs = "目标追踪结果";
			ti.mask = TCIF_TEXT|TCIF_PARAM;
			ti.pszText = cs.LockBuffer();
//			ti.lParam = (long) pView;
			m_TabCtrl.InsertItem(m_TabCtrl.GetItemCount(), &ti);
			cs.UnlockBuffer();

			cs = "图符记忆结果";
			ti.mask = TCIF_TEXT|TCIF_PARAM;
			ti.pszText = cs.LockBuffer();
//			ti.lParam = (long) pView;
			m_TabCtrl.InsertItem(m_TabCtrl.GetItemCount(), &ti);
			cs.UnlockBuffer();
		}
		m_ResultList.DeleteAllItems();            //删除列表中所有内容(行)
		while (m_ResultList.DeleteColumn(0));     //删除列表中所有列
		//向列表框中添加列
		if(pDoc->m_Setting5!=NULL)
		{
			delete []pDoc->m_Setting5;
			pDoc->m_Setting5 = NULL;
		}
		pDoc->m_Setting5 = new struct TaskSetting5[1];

        AddHeadT5Trace();

		m_ResultList2.DeleteAllItems();            //删除列表中所有内容(行)
		while (m_ResultList2.DeleteColumn(0));     //删除列表中所有列
		//向列表框中添加列
        AddHeadT5Sign();
		pos = pDoc->m_FileName.ReverseFind('\\');
        pos1 = pDoc->m_FileName.Find('-',pos+1);
		pos2 = pDoc->m_FileName.Find('-',pos1+1);
		pDoc->m_FileName1 = pDoc->m_FileName.Left(pos+1)+"T5-trace"+pDoc->m_FileName.Right(pDoc->m_FileName.GetLength()-pos2);
     	pDoc->m_FileName2 = pDoc->m_FileName.Left(pos+1)+"T5-sign"+pDoc->m_FileName.Right(pDoc->m_FileName.GetLength()-pos2);
		pDoc->MemClear();
		pDoc->m_bOpenFile1 = pDoc->ReadT5Trace();
		pDoc->m_bOpenFile2 = pDoc->ReadT5Sign();
		break;
	case 6:
		if (m_TabCtrl.GetSafeHwnd())
		{
			cs = "目标追踪结果";
			ti.mask = TCIF_TEXT|TCIF_PARAM;
			ti.pszText = cs.LockBuffer();
//			ti.lParam = (long) pView;
			m_TabCtrl.InsertItem(m_TabCtrl.GetItemCount(), &ti);
			cs.UnlockBuffer();

			if(pDoc->m_MemTaskMode == 0)
			{
				cs = "判别比较结果";
			}
			else
			{
                cs = "记忆判别结果";
			}
			ti.mask = TCIF_TEXT|TCIF_PARAM;
			ti.pszText = cs.LockBuffer();
//			ti.lParam = (long) pView;
			m_TabCtrl.InsertItem(m_TabCtrl.GetItemCount(), &ti);
			cs.UnlockBuffer();
		}
//		if(pDoc->m_Setting3.m_MainTaskMode == 0)
		{
//			m_ChartList.InsertString(0,"位移误差随时间变化的曲线");
//			m_ChartList.InsertString(1,"目标速度随时间变化的曲线");
//			m_ChartList.InsertString(2,"瞄准器速度随时间变化的曲线");
//			m_ChartList.SetCurSel(0);
		}
		m_ResultList.DeleteAllItems();            //删除列表中所有内容(行)
		while (m_ResultList.DeleteColumn(0));     //删除列表中所有列
		//向列表框中添加列
		if(pDoc->m_Setting6!=NULL)
		{
			delete []pDoc->m_Setting6;
			pDoc->m_Setting6 = NULL;
		}
		pDoc->m_Setting6 = new struct TaskSetting6[1];

		AddHeadT6Trace();

		m_ResultList2.DeleteAllItems();            //删除列表中所有内容(行)
		while (m_ResultList2.DeleteColumn(0));     //删除列表中所有列
		//向列表框中添加列
		pos = pDoc->m_FileName.ReverseFind('\\');
        pos1 = pDoc->m_FileName.Find('-',pos+1);
		pos2 = pDoc->m_FileName.Find('-',pos1+1);
 		pDoc->MemClear();
		if(pDoc->m_MemTaskMode == 0)
		{
		    AddHeadT6Judge();
			pDoc->m_FileName1 = pDoc->m_FileName.Left(pos+1)+"T6_1-trace"+pDoc->m_FileName.Right(pDoc->m_FileName.GetLength()-pos2);
     	    pDoc->m_FileName2 = pDoc->m_FileName.Left(pos+1)+"T6_1-judge"+pDoc->m_FileName.Right(pDoc->m_FileName.GetLength()-pos2);
            pDoc->m_bOpenFile1 = pDoc->ReadT6Trace();
			pDoc->m_bOpenFile2 = pDoc->ReadT6Judge();	
		}
		else
		{
            AddHeadT6Memory();
			pDoc->m_FileName1 = pDoc->m_FileName.Left(pos+1)+"T6_2-trace"+pDoc->m_FileName.Right(pDoc->m_FileName.GetLength()-pos2);
     	    pDoc->m_FileName2 = pDoc->m_FileName.Left(pos+1)+"T6_2-memory"+pDoc->m_FileName.Right(pDoc->m_FileName.GetLength()-pos2);
            pDoc->m_bOpenFile1 = pDoc->ReadT6Trace();
			pDoc->m_bOpenFile2 = pDoc->ReadT6Memory();
		}
		break;
	case 7:
		if (m_TabCtrl.GetSafeHwnd())
		{
			cs = "速度知觉结果";
			ti.mask = TCIF_TEXT | TCIF_PARAM;
			ti.pszText = cs.LockBuffer();
			//			ti.lParam = (long) pView;
			m_TabCtrl.InsertItem(m_TabCtrl.GetItemCount(), &ti);
			cs.UnlockBuffer();
		}

		m_ResultList.DeleteAllItems();            //删除列表中所有内容(行)
		while (m_ResultList.DeleteColumn(0));     //删除列表中所有列
												  //向列表框中添加列
		if (pDoc->m_Setting7 != NULL)
		{
			delete[]pDoc->m_Setting7;
			pDoc->m_Setting7 = NULL;
		}
		pDoc->m_Setting7 = new struct TaskSetting7[1];
		AddHeadT7();
		pDoc->MemClear();
		pDoc->m_bOpenFile1 = pDoc->ReadT7();
		break;
	}	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CString CListDlg::getCString(double x) {
	stringstream ss;
	ss << x;
	CString cstr(ss.str().c_str());
	return cstr;
}

CString CListDlg::getCString(int x) {
	stringstream ss;
	ss << x;
	CString cstr(ss.str().c_str());
	return cstr;
}


BOOL CListDlg::AddT7Item(int i) {
	CMainFrame*   pMain = (CMainFrame*)AfxGetMainWnd();
	CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();
	
	m_ResultList.AddItem(i, 0, getCString((pDoc->t7Recs[i]).no), -1);
	m_ResultList.AddItem(i, 1, getCString((pDoc->t7Recs[i]).buttonDistance), -1);
	m_ResultList.AddItem(i, 2, getCString((pDoc->t7Recs[i]).deviationRate) + CString("%"), -1);
	m_ResultList.AddItem(i, 3, getCString((pDoc->t7Recs[i]).smallBallSpeed), -1);
	return TRUE;
}

BOOL CListDlg::AddT1Item(int i)
{
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
    CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();

	CString str;
	m_ResultList.AddItem(i,0,pDoc->m_PartInfo.m_TesterNo,-1);
	m_ResultList.AddItem(i,1,pDoc->m_PartInfo.m_TesterName,-1);
	m_ResultList.AddItem(i,2,pDoc->m_PartInfo.m_TesterSex,-1);
	str.Format("%d",pDoc->m_PartInfo.m_Session);
	m_ResultList.AddItem(i,3,str,-1);

	str.Format("%.2f",pDoc->m_HardSetting.m_DistanceError);
	m_ResultList.AddItem(i,4,str,-1);
	str.Format("%.2f",pDoc->m_HardSetting.m_AngleError);
	m_ResultList.AddItem(i,5,str,-1);
	str.Format("%d",pDoc->m_Setting1[0].m_PracMode);
	m_ResultList.AddItem(i,6,str,-1);
	str.Format("%d",pDoc->m_Setting1[0].m_ExperMode);
	m_ResultList.AddItem(i,7,str,-1);

//	str.Format("%d",pDoc->m_Setting1.m_Background);
	m_ResultList.AddItem(i,8,m_BackgroundStr[pDoc->m_Setting1[0].m_Background],-1);
	m_ResultList.AddItem(i,9,m_TrackStr[pDoc->m_Setting1[0].m_Track],-1);
//	str.Format("%d",pDoc->m_Setting1.m_Direction);
	m_ResultList.AddItem(i,10,m_DirectionStr[pDoc->m_Setting1[0].m_Direction],-1);
//	str.Format("%d",pDoc->m_Setting1.m_MoveMode);
	m_ResultList.AddItem(i,11,m_MoveModeStr[pDoc->m_Setting1[0].m_MoveMode],-1);
//	str.Format("%d",pDoc->m_Setting1.m_SpeedMode);
	m_ResultList.AddItem(i,12,m_SpeedModeStr[pDoc->m_Setting1[0].m_SpeedMode],-1);

	str.Format("%d",pDoc->m_Setting1[0].m_Pause);
	m_ResultList.AddItem(i,13,str,-1);
	if(pDoc->m_Setting1[0].m_PauseNum<0)
	{
        str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_Setting1[0].m_PauseNum);	
	}
	m_ResultList.AddItem(i,14,str,-1);
	if(pDoc->m_Setting1[0].m_Speed<0)
	{
        str = "Disabled";
	}
	else
	{
		str.Format("%.2f",pDoc->m_Setting1[0].m_Speed);	
	}
	m_ResultList.AddItem(i,15,str,-1);
	if(pDoc->m_Setting1[0].m_InitSpeed<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%.2f",pDoc->m_Setting1[0].m_InitSpeed);    
	}
	m_ResultList.AddItem(i,16,str,-1);
	if(pDoc->m_Setting1[0].m_SpeedMin<0)
	{
		str = "Disabled";
	}
    else
	{
		str.Format("%.2f",pDoc->m_Setting1[0].m_SpeedMin);	
	}
	m_ResultList.AddItem(i,17,str,-1);
	if(pDoc->m_Setting1[0].m_SpeedMax<0)
	{
        str = "Disabled";
	}
	else
	{
	    str.Format("%.2f",pDoc->m_Setting1[0].m_SpeedMax);	
	}
	m_ResultList.AddItem(i,18,str,-1);
	if(pDoc->m_Setting1[0].m_AccelerationMin<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%.2f",pDoc->m_Setting1[0].m_AccelerationMin);
	}
	m_ResultList.AddItem(i,19,str,-1);
	if(pDoc->m_Setting1[0].m_AccelerationMax<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%.2f",pDoc->m_Setting1[0].m_AccelerationMax);
	}
	m_ResultList.AddItem(i,20,str,-1);
	if(pDoc->m_Setting1[0].m_AngleSpeedMin<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%.2f",pDoc->m_Setting1[0].m_AngleSpeedMin);
	}
	m_ResultList.AddItem(i,21,str,-1);
	if(pDoc->m_Setting1[0].m_AngleSpeedMax<0)
	{
		str = "Disabled";
	}
	else
	{
		str.Format("%.2f",pDoc->m_Setting1[0].m_AngleSpeedMax);
	}
	m_ResultList.AddItem(i,22,str,-1);
	if(pDoc->m_Setting1[0].m_RotateAngleMin<0)
	{
	    str = "Disabled";
	}
	else
	{
		str.Format("%.2f",pDoc->m_Setting1[0].m_RotateAngleMin);
	}
	m_ResultList.AddItem(i,23,str,-1);
	if(pDoc->m_Setting1[0].m_RotateAngleMax<0)
	{
		str = "Disabled";
	}
	else
	{
		str.Format("%.2f",pDoc->m_Setting1[0].m_RotateAngleMax);
	}
	m_ResultList.AddItem(i,24,str,-1);

	if(pDoc->m_Setting1[0].m_PracTime<0)
	{
	    str = "Disabled";
	}
	else
	{
		str.Format("%d",pDoc->m_Setting1[0].m_PracTime);
	}
	m_ResultList.AddItem(i,25,str,-1);
    if(pDoc->m_Setting1[0].m_ExperTime<0)
	{
	    str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_Setting1[0].m_ExperTime);
	}
	m_ResultList.AddItem(i,26,str,-1);
	if(pDoc->m_Setting1[0].m_PracTimes<0)
	{
	    str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_Setting1[0].m_PracTimes);
	}
	m_ResultList.AddItem(i,27,str,-1);
	if(pDoc->m_Setting1[0].m_ExperTimes<0)
	{
	    str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_Setting1[0].m_ExperTimes);
	}
	m_ResultList.AddItem(i,28,str,-1);

	str.Format("%d",pDoc->m_TrialType);
	m_ResultList.AddItem(i,29,str,-1);
	str.Format("%d",pDoc->m_TrialNo);
	m_ResultList.AddItem(i,30,str,-1);
	str.Format("%d",pDoc->m_PointNum);
	m_ResultList.AddItem(i,31,str,-1);
	str.Format("%u",pDoc->m_PointTime[i]);
	m_ResultList.AddItem(i,32,str,-1);
	str.Format("%d",pDoc->m_ObjPoint[i].x);
	m_ResultList.AddItem(i,33,str,-1);
	str.Format("%d",pDoc->m_ObjPoint[i].y);
	m_ResultList.AddItem(i,34,str,-1);
	str.Format("%d",pDoc->m_PostPoint[i].x);
	m_ResultList.AddItem(i,35,str,-1);
	str.Format("%d",pDoc->m_PostPoint[i].y);
	m_ResultList.AddItem(i,36,str,-1);
	str.Format("%.2f",pDoc->m_ObjRotate[i]);
	m_ResultList.AddItem(i,37,str,-1);
	str.Format("%.2f",pDoc->m_PostRotate[i]);
	m_ResultList.AddItem(i,38,str,-1);
	str.Format("%.2f",pDoc->m_Distance[i]);
	m_ResultList.AddItem(i,39,str,-1);
	str.Format("%.2f",pDoc->m_RotateError[i]);
	m_ResultList.AddItem(i,40,str,-1);
	str.Format("%d",pDoc->m_bHit[i]);
	m_ResultList.AddItem(i,41,str,-1);

	str.Format("%.2f",pDoc->m_ObjSpeedX[i]);
	m_ResultList.AddItem(i,42,str,-1);
	str.Format("%.2f",pDoc->m_ObjSpeedY[i]);
	m_ResultList.AddItem(i,43,str,-1);
	str.Format("%.2f",pDoc->m_PostSpeedX[i]);
	m_ResultList.AddItem(i,44,str,-1);
	str.Format("%.2f",pDoc->m_PostSpeedY[i]);
	m_ResultList.AddItem(i,45,str,-1);
	str.Format("%.2f",pDoc->m_ObjRotateSpeed[i]);
	m_ResultList.AddItem(i,46,str,-1);
	str.Format("%.2f",pDoc->m_PostRotateSpeed[i]);
	m_ResultList.AddItem(i,47,str,-1);
	return TRUE;
}


BOOL CListDlg::AddT2TraceItem(int i)
{
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
    CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();
	CString str;
	m_ResultList.AddItem(i,0,pDoc->m_PartInfo.m_TesterNo,-1);
	m_ResultList.AddItem(i,1,pDoc->m_PartInfo.m_TesterName,-1);
	m_ResultList.AddItem(i,2,pDoc->m_PartInfo.m_TesterSex,-1);
	str.Format("%d",pDoc->m_PartInfo.m_Session);
	m_ResultList.AddItem(i,3,str,-1);

	str.Format("%.2f",pDoc->m_HardSetting.m_DistanceError);
	m_ResultList.AddItem(i,4,str,-1);
	str.Format("%d",pDoc->m_Setting2[0].m_PracMode);
	m_ResultList.AddItem(i,5,str,-1);
	str.Format("%d",pDoc->m_Setting2[0].m_ExperMode);
	m_ResultList.AddItem(i,6,str,-1);
	str.Format("%d",pDoc->m_Setting2[0].m_MainTask);
	m_ResultList.AddItem(i,7,str,-1);
	str.Format("%d",pDoc->m_Setting2[0].m_SubTask);
	m_ResultList.AddItem(i,8,str,-1);

//	str.Format("%d",pDoc->m_Setting2.m_Background);
	m_ResultList.AddItem(i,9,m_BackgroundStr[pDoc->m_Setting2[0].m_Background],-1);
//	str.Format("%d",pDoc->m_Setting2.m_Direction);
	if(pDoc->m_Setting2[0].m_Direction<0)
	{
	    m_ResultList.AddItem(i,10,"Disabled",-1);
	}
	else
	{
	    m_ResultList.AddItem(i,10,m_DirectionStr[pDoc->m_Setting2[0].m_Direction],-1);
	}
	if(pDoc->m_Setting2[0].m_Direction<0)
	{
	    str = "Disabled";
	}
	else
	{
		str.Format("%.2f",pDoc->m_Setting2[0].m_InitSpeed);
	}
	m_ResultList.AddItem(i,11,str,-1);
    if(pDoc->m_Setting2[0].m_HoldTimeNum<0)
	{
	    str = "Disabled";
	}
	else
	{
		str.Format("%d",pDoc->m_Setting2[0].m_HoldTimeNum);
	}
	m_ResultList.AddItem(i,12,str,-1);
	if(pDoc->m_Setting2[0].m_HoldTime[0]<0)
	{
	    str = "Disabled";
	}
	else
	{
		str.Format("%.1f",pDoc->m_Setting2[0].m_HoldTime[0]);
	}
	m_ResultList.AddItem(i,13,str,-1);
	if(pDoc->m_Setting2[0].m_HoldTime[1]<0)
	{
	    str = "Disabled";
	}
	else
	{
		str.Format("%.1f",pDoc->m_Setting2[0].m_HoldTime[1]);
	}
	m_ResultList.AddItem(i,14,str,-1);
	if(pDoc->m_Setting2[0].m_HoldTime[2]<0)
	{
	    str = "Disabled";
	}
	else
	{
		str.Format("%.1f",pDoc->m_Setting2[0].m_HoldTime[2]);
	}
	m_ResultList.AddItem(i,15,str,-1);
	if(pDoc->m_Setting2[0].m_HoldTime[3]<0)
	{
	    str = "Disabled";
	}
	else
	{
		str.Format("%.1f",pDoc->m_Setting2[0].m_HoldTime[3]);
	}
	m_ResultList.AddItem(i,16,str,-1);
	if(pDoc->m_Setting2[0].m_HoldTime[4]<0)
	{
	    str = "Disabled";
	}
	else
	{
		str.Format("%.1f",pDoc->m_Setting2[0].m_HoldTime[4]);
	}
	m_ResultList.AddItem(i,17,str,-1);
	if(pDoc->m_Setting2[0].m_HoldTime[5]<0)
	{
	    str = "Disabled";
	}
	else
	{
		str.Format("%.1f",pDoc->m_Setting2[0].m_HoldTime[5]);
	}
	m_ResultList.AddItem(i,18,str,-1);
	if(pDoc->m_Setting2[0].m_HoldTime[6]<0)
	{
	    str = "Disabled";
	}
	else
	{
		str.Format("%.1f",pDoc->m_Setting2[0].m_HoldTime[6]);
	}
	m_ResultList.AddItem(i,19,str,-1);
	if(pDoc->m_Setting2[0].m_HoldTime[7]<0)
	{
	    str = "Disabled";
	}
	else
	{
		str.Format("%.1f",pDoc->m_Setting2[0].m_HoldTime[7]);
	}
	m_ResultList.AddItem(i,20,str,-1);
	if(pDoc->m_Setting2[0].m_HoldTime[8]<0)
	{
	    str = "Disabled";
	}
	else
	{
		str.Format("%.1f",pDoc->m_Setting2[0].m_HoldTime[8]);
	}
	m_ResultList.AddItem(i,21,str,-1);
	if(pDoc->m_Setting2[0].m_HoldTime[9]<0)
	{
	    str = "Disabled";
	}
	else
	{
		str.Format("%.1f",pDoc->m_Setting2[0].m_HoldTime[9]);
	}
	m_ResultList.AddItem(i,22,str,-1);
	if(pDoc->m_Setting2[0].m_HoldTime[10]<0)
	{
	    str = "Disabled";
	}
	else
	{
		str.Format("%.1f",pDoc->m_Setting2[0].m_HoldTime[10]);
	}
	m_ResultList.AddItem(i,23,str,-1);
	if(pDoc->m_Setting2[0].m_HoldTime[11]<0)
	{
	    str = "Disabled";
	}
	else
	{
		str.Format("%.1f",pDoc->m_Setting2[0].m_HoldTime[11]);
	}
	m_ResultList.AddItem(i,24,str,-1);
	if(pDoc->m_Setting2[0].m_PracTime<0)
	{
	    str = "Disabled";
	}
	else
	{
		str.Format("%d",pDoc->m_Setting2[0].m_PracTime);
	}
	m_ResultList.AddItem(i,25,str,-1);
	if(pDoc->m_Setting2[0].m_ExperTime<0)
	{
	    str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_Setting2[0].m_ExperTime);
	}
	m_ResultList.AddItem(i,26,str,-1);
	if(pDoc->m_Setting2[0].m_PracTimes<0)
	{
	    str = "Disabled";
	}
	else
	{
		str.Format("%d",pDoc->m_Setting2[0].m_PracTimes);
	}
	m_ResultList.AddItem(i,27,str,-1);
	if(pDoc->m_Setting2[0].m_ExperTimes<0)
	{
	    str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_Setting2[0].m_ExperTimes);
	}
	m_ResultList.AddItem(i,28,str,-1);
	        
    str.Format("%d",pDoc->m_TrialType);
	m_ResultList.AddItem(i,29,str,-1);
	str.Format("%d",pDoc->m_PointNum);
	m_ResultList.AddItem(i,30,str,-1);
	str.Format("%u",pDoc->m_PointTime[i]);
	m_ResultList.AddItem(i,31,str,-1);
	str.Format("%d",pDoc->m_ObjPoint[i].x);
	m_ResultList.AddItem(i,32,str,-1);
	str.Format("%d",pDoc->m_ObjPoint[i].y);
	m_ResultList.AddItem(i,33,str,-1);
	str.Format("%d",pDoc->m_PostPoint[i].x);
	m_ResultList.AddItem(i,34,str,-1);
	str.Format("%d",pDoc->m_PostPoint[i].y);
	m_ResultList.AddItem(i,35,str,-1);
	str.Format("%.2f",pDoc->m_Distance[i]);
	m_ResultList.AddItem(i,36,str,-1);
	str.Format("%d",pDoc->m_bHit[i]);
	m_ResultList.AddItem(i,37,str,-1);

	str.Format("%.2f",pDoc->m_ObjSpeedX[i]);
	m_ResultList.AddItem(i,38,str,-1);
	str.Format("%.2f",pDoc->m_ObjSpeedY[i]);
	m_ResultList.AddItem(i,39,str,-1);
	str.Format("%.2f",pDoc->m_PostSpeedX[i]);
	m_ResultList.AddItem(i,40,str,-1);
	str.Format("%.2f",pDoc->m_PostSpeedY[i]);
	m_ResultList.AddItem(i,41,str,-1);
	return TRUE;
}

BOOL CListDlg::AddT2HoldItem(int i)
{
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
    CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();
	CString str;
	m_ResultList2.AddItem(i,0,pDoc->m_PartInfo.m_TesterNo,-1);
	m_ResultList2.AddItem(i,1,pDoc->m_PartInfo.m_TesterName,-1);
	m_ResultList2.AddItem(i,2,pDoc->m_PartInfo.m_TesterSex,-1);
	str.Format("%d",pDoc->m_PartInfo.m_Session);
	m_ResultList2.AddItem(i,3,str,-1);

	str.Format("%.2f",pDoc->m_HardSetting.m_DistanceError);
	m_ResultList2.AddItem(i,4,str,-1);
	str.Format("%d",pDoc->m_Setting2[0].m_PracMode);
	m_ResultList2.AddItem(i,5,str,-1);
    str.Format("%d",pDoc->m_Setting2[0].m_ExperMode);
	m_ResultList2.AddItem(i,6,str,-1);
    str.Format("%d",pDoc->m_Setting2[0].m_MainTask);
	m_ResultList2.AddItem(i,7,str,-1);
    str.Format("%d",pDoc->m_Setting2[0].m_SubTask);
	m_ResultList2.AddItem(i,8,str,-1);

//	str.Format("%d",pDoc->m_Setting2.m_Background);
	m_ResultList2.AddItem(i,9,m_BackgroundStr[pDoc->m_Setting2[0].m_Background],-1);
//  str.Format("%d",pDoc->m_Setting2.m_Direction);
	if(pDoc->m_Setting2[0].m_Direction<0)
	{
	    m_ResultList2.AddItem(i,10,"Disabled",-1);
	}
	else
	{
    	m_ResultList2.AddItem(i,10,m_DirectionStr[pDoc->m_Setting2[0].m_Direction],-1);
	}
	if(pDoc->m_Setting2[0].m_InitSpeed<0)
	{
	    str = "Disabled";
	}
	else
	{
	    str.Format("%.2f",pDoc->m_Setting2[0].m_InitSpeed);
	}
	m_ResultList2.AddItem(i,11,str,-1);

	if(pDoc->m_Setting2[0].m_HoldTimeNum<0)
	{
	    str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_Setting2[0].m_HoldTimeNum);
	}
	m_ResultList2.AddItem(i,12,str,-1);
	if(pDoc->m_Setting2[0].m_HoldTime[0]<0)
	{
	    str = "Disabled";
	}
	else
	{
		str.Format("%.1f",pDoc->m_Setting2[0].m_HoldTime[0]);
	}
	m_ResultList2.AddItem(i,13,str,-1);
	if(pDoc->m_Setting2[0].m_HoldTime[1]<0)
	{
	    str = "Disabled";
	}
	else
	{
		str.Format("%.1f",pDoc->m_Setting2[0].m_HoldTime[1]);
	}
	m_ResultList2.AddItem(i,14,str,-1);
	if(pDoc->m_Setting2[0].m_HoldTime[2]<0)
	{
	    str = "Disabled";
	}
	else
	{
		str.Format("%.1f",pDoc->m_Setting2[0].m_HoldTime[2]);
	}
	m_ResultList2.AddItem(i,15,str,-1);
	if(pDoc->m_Setting2[0].m_HoldTime[3]<0)
	{
	    str = "Disabled";
	}
	else
	{
		str.Format("%.1f",pDoc->m_Setting2[0].m_HoldTime[3]);
	}
	m_ResultList2.AddItem(i,16,str,-1);
	if(pDoc->m_Setting2[0].m_HoldTime[4]<0)
	{
	    str = "Disabled";
	}
	else
	{
		str.Format("%.1f",pDoc->m_Setting2[0].m_HoldTime[4]);
	}
	m_ResultList2.AddItem(i,17,str,-1);
	if(pDoc->m_Setting2[0].m_HoldTime[5]<0)
	{
	    str = "Disabled";
	}
	else
	{
		str.Format("%.1f",pDoc->m_Setting2[0].m_HoldTime[5]);
	}
	m_ResultList2.AddItem(i,18,str,-1);
	if(pDoc->m_Setting2[0].m_HoldTime[6]<0)
	{
	    str = "Disabled";
	}
	else
	{
		str.Format("%.1f",pDoc->m_Setting2[0].m_HoldTime[6]);
	}
	m_ResultList2.AddItem(i,19,str,-1);
	if(pDoc->m_Setting2[0].m_HoldTime[7]<0)
	{
	    str = "Disabled";
	}
	else
	{
		str.Format("%.1f",pDoc->m_Setting2[0].m_HoldTime[7]);
	}
	m_ResultList2.AddItem(i,20,str,-1);
	if(pDoc->m_Setting2[0].m_HoldTime[8]<0)
	{
	    str = "Disabled";
	}
	else
	{
		str.Format("%.1f",pDoc->m_Setting2[0].m_HoldTime[8]);
	}
	m_ResultList2.AddItem(i,21,str,-1);
	if(pDoc->m_Setting2[0].m_HoldTime[9]<0)
	{
	    str = "Disabled";
	}
	else
	{
		str.Format("%.1f",pDoc->m_Setting2[0].m_HoldTime[9]);
	}
	m_ResultList2.AddItem(i,22,str,-1);
	if(pDoc->m_Setting2[0].m_HoldTime[10]<0)
	{
	    str = "Disabled";
	}
	else
	{
		str.Format("%.1f",pDoc->m_Setting2[0].m_HoldTime[10]);
	}
	m_ResultList2.AddItem(i,23,str,-1);
	if(pDoc->m_Setting2[0].m_HoldTime[11]<0)
	{
	    str = "Disabled";
	}
	else
	{
		str.Format("%.1f",pDoc->m_Setting2[0].m_HoldTime[11]);
	}
	m_ResultList2.AddItem(i,24,str,-1);
	if(pDoc->m_Setting2[0].m_PracTime<0)
	{
	    str = "Disabled";
	}
	else
	{
		str.Format("%d",pDoc->m_Setting2[0].m_PracTime);
	}
	m_ResultList2.AddItem(i,25,str,-1);
	if(pDoc->m_Setting2[0].m_ExperTime<0)
	{
	    str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_Setting2[0].m_ExperTime);
	}
	m_ResultList2.AddItem(i,26,str,-1);
	if(pDoc->m_Setting2[0].m_PracTimes<0)
	{
	    str = "Disabled";
	}
	else
	{
		str.Format("%d",pDoc->m_Setting2[0].m_PracTimes);
	}
	m_ResultList2.AddItem(i,27,str,-1);
	if(pDoc->m_Setting2[0].m_ExperTimes<0)
	{
	    str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_Setting2[0].m_ExperTimes);
	}
	m_ResultList2.AddItem(i,28,str,-1);

	str.Format("%d",pDoc->m_TrialType);
	m_ResultList2.AddItem(i,29,str,-1);
	str.Format("%d",pDoc->m_HoldNo);
	m_ResultList2.AddItem(i,30,str,-1);
	str.Format("%d",pDoc->m_HoldTime[i]);
	m_ResultList2.AddItem(i,31,str,-1);
	str.Format("%u",pDoc->m_HoldStartTime[i]);
	m_ResultList2.AddItem(i,32,str,-1);
	str.Format("%u",pDoc->m_HoldSureTime[i]);
	m_ResultList2.AddItem(i,33,str,-1);  
    str.Format("%u",pDoc->m_TestRT[i]);
	m_ResultList2.AddItem(i,34,str,-1);
	str.Format("%d",pDoc->m_HoldError[i]);
	m_ResultList2.AddItem(i,35,str,-1);
	str.Format("%.2f",pDoc->m_ErrorRatio[i]);
	m_ResultList2.AddItem(i,36,str,-1);
	return TRUE;
}

BOOL CListDlg::AddT3TraceItem(int i)
{
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
    CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();
	CString str;
	m_ResultList.AddItem(i,0,pDoc->m_PartInfo.m_TesterNo,-1);
	m_ResultList.AddItem(i,1,pDoc->m_PartInfo.m_TesterName,-1);
	m_ResultList.AddItem(i,2,pDoc->m_PartInfo.m_TesterSex,-1);
	str.Format("%d",pDoc->m_PartInfo.m_Session);
	m_ResultList.AddItem(i,3,str,-1);

	str.Format("%.2f",pDoc->m_HardSetting.m_DistanceError);
	m_ResultList.AddItem(i,4,str,-1);
	str.Format("%d",pDoc->m_Setting3[0].m_PracMode);
	m_ResultList.AddItem(i,5,str,-1);
	str.Format("%d",pDoc->m_Setting3[0].m_ExperMode);
	m_ResultList.AddItem(i,6,str,-1);
	str.Format("%d",pDoc->m_Setting3[0].m_MainTask);
	m_ResultList.AddItem(i,7,str,-1);
	str.Format("%d",pDoc->m_Setting3[0].m_SubTask);
	m_ResultList.AddItem(i,8,str,-1);

//	str.Format("%d",pDoc->m_Setting3.m_MainTaskMode);
	if(pDoc->m_Setting3[0].m_MainTaskMode<0)
	{
		m_ResultList.AddItem(i,9,"Disabled",-1);
	}
	else
	{
	    m_ResultList.AddItem(i,9,m_MainTaskModeStr[pDoc->m_Setting3[0].m_MainTaskMode],-1);
	}
//	str.Format("%d",pDoc->m_Setting3.m_Background);
	m_ResultList.AddItem(i,10,m_BackgroundStr[pDoc->m_Setting3[0].m_Background],-1);
	if(pDoc->m_Setting3[0].m_InitSpeed<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%.2f",pDoc->m_Setting3[0].m_InitSpeed);
	}
	m_ResultList.AddItem(i,11,str,-1);
//	str.Format("%d",pDoc->m_Setting3.m_CodePairMode);
    if(pDoc->m_Setting3[0].m_CodePairMode<0)
	{
		m_ResultList.AddItem(i,12,"Disabled",-1);
	}
	else
	{
	    m_ResultList.AddItem(i,12,m_CodePairModeStr[pDoc->m_Setting3[0].m_CodePairMode],-1);
	}
    if(pDoc->m_Setting3[0].m_CodePairNum<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_Setting3[0].m_CodePairNum);
	}
	m_ResultList.AddItem(i,13,str,-1);
//	str.Format("%d",pDoc->m_Setting3.m_DisplayMode);
    if(pDoc->m_Setting3[0].m_CodePairMode<0)
	{
		m_ResultList.AddItem(i,14,"Disabled",-1);
	}
	else
	{
		m_ResultList.AddItem(i,14,m_DisplayModeStr[pDoc->m_Setting3[0].m_DisplayMode],-1);
	}
	if(pDoc->m_Setting3[0].m_EventFrequency<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_Setting3[0].m_EventFrequency);
	}
	m_ResultList.AddItem(i,15,str,-1);
	if(pDoc->m_Setting3[0].m_PracTime<0)
	{
		str = "Disabled";
	}
	else
	{
		str.Format("%d",pDoc->m_Setting3[0].m_PracTime);
	}
	m_ResultList.AddItem(i,16,str,-1);
	if(pDoc->m_Setting3[0].m_ExperTime<0)
	{
		str = "Disabled";
	}
	else
	{
		str.Format("%d",pDoc->m_Setting3[0].m_ExperTime);
	}
	m_ResultList.AddItem(i,17,str,-1);
	if(pDoc->m_Setting3[0].m_PracTimes<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_Setting3[0].m_PracTimes);
	}
	m_ResultList.AddItem(i,18,str,-1);
	if(pDoc->m_Setting3[0].m_ExperTimes<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_Setting3[0].m_ExperTimes);
	}
	m_ResultList.AddItem(i,19,str,-1);
			
    str.Format("%d",pDoc->m_TrialType);
	m_ResultList.AddItem(i,20,str,-1);
    str.Format("%d",pDoc->m_PointNum);
	m_ResultList.AddItem(i,21,str,-1);
    str.Format("%u",pDoc->m_PointTime[i]);
	m_ResultList.AddItem(i,22,str,-1);
    str.Format("%d",pDoc->m_ObjPoint[i].x);
    m_ResultList.AddItem(i,23,str,-1);
	str.Format("%d",pDoc->m_ObjPoint[i].y);
	m_ResultList.AddItem(i,24,str,-1);
	str.Format("%d",pDoc->m_PostPoint[i].x);
	m_ResultList.AddItem(i,25,str,-1);
	str.Format("%d",pDoc->m_PostPoint[i].y);
	m_ResultList.AddItem(i,26,str,-1);
	str.Format("%.2f",pDoc->m_Distance[i]);
	m_ResultList.AddItem(i,27,str,-1);
	str.Format("%d",pDoc->m_bHit[i]);
	m_ResultList.AddItem(i,28,str,-1);

	str.Format("%.2f",pDoc->m_ObjSpeedX[i]);
	m_ResultList.AddItem(i,29,str,-1);
    str.Format("%.2f",pDoc->m_ObjSpeedY[i]);
	m_ResultList.AddItem(i,30,str,-1);
    str.Format("%.2f",pDoc->m_PostSpeedX[i]);
	m_ResultList.AddItem(i,31,str,-1);
    str.Format("%.2f",pDoc->m_PostSpeedY[i]);
	m_ResultList.AddItem(i,32,str,-1);
	return TRUE;
}

BOOL CListDlg::AddT3CodeItem(int i)
{
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
    CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();
	CString str;
	m_ResultList.AddItem(i,0,pDoc->m_PartInfo.m_TesterNo,-1);
	m_ResultList.AddItem(i,1,pDoc->m_PartInfo.m_TesterName,-1);
	m_ResultList.AddItem(i,2,pDoc->m_PartInfo.m_TesterSex,-1);
    str.Format("%d",pDoc->m_PartInfo.m_Session);
	m_ResultList.AddItem(i,3,str,-1);

	str.Format("%d",pDoc->m_Setting3[0].m_PracMode);
	m_ResultList.AddItem(i,4,str,-1);
    str.Format("%d",pDoc->m_Setting3[0].m_ExperMode);
	m_ResultList.AddItem(i,5,str,-1);
    str.Format("%d",pDoc->m_Setting3[0].m_MainTask);
	m_ResultList.AddItem(i,6,str,-1);
    str.Format("%d",pDoc->m_Setting3[0].m_SubTask);
	m_ResultList.AddItem(i,7,str,-1);

//	str.Format("%d",pDoc->m_Setting3.m_MainTaskMode);
	if(pDoc->m_Setting3[0].m_MainTaskMode<0)
	{
		m_ResultList.AddItem(i,8,"Disabled",-1);
	}
	else
	{
        m_ResultList.AddItem(i,8,m_MainTaskModeStr[pDoc->m_Setting3[0].m_MainTaskMode],-1);
	}
//  str.Format("%d",pDoc->m_Setting3.m_Background);
	m_ResultList.AddItem(i,9,m_BackgroundStr[pDoc->m_Setting3[0].m_Background],-1);
	if(pDoc->m_Setting3[0].m_InitSpeed<0)
	{
		str = "Disabled";
	}
	else
	{
        str.Format("%.2f",pDoc->m_Setting3[0].m_InitSpeed);
	}
    m_ResultList.AddItem(i,10,str,-1); 
//  str.Format("%d",pDoc->m_Setting3.m_CodePairMode);
	if(pDoc->m_Setting3[0].m_EventMode<0)
	{
	    m_ResultList.AddItem(i,11,"Disabled",-1);
	}
	else
	{
        m_ResultList.AddItem(i,11,m_EventModeStr[pDoc->m_Setting3[0].m_EventMode],-1);
	}
	if(pDoc->m_Setting3[0].m_CodePairMode<0)
	{
		m_ResultList.AddItem(i,12,"Disabled",-1);
	}
	else
	{
	    m_ResultList.AddItem(i,12,m_CodePairModeStr[pDoc->m_Setting3[0].m_CodePairMode],-1);
	}
	if(pDoc->m_Setting3[0].m_CodePairNum<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_CodePairNum);
	}
	m_ResultList.AddItem(i,13,str,-1);
//	str.Format("%d",pDoc->m_Setting3.m_DisplayMode);
	if(pDoc->m_Setting3[0].m_DisplayMode<0)
	{
		m_ResultList.AddItem(i,14,"Disabled",-1);
	}
	else
	{
	    m_ResultList.AddItem(i,14,m_DisplayModeStr[pDoc->m_Setting3[0].m_DisplayMode],-1);
	}
	if(pDoc->m_Setting3[0].m_EventFrequency<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_Setting3[0].m_EventFrequency);
	}
	m_ResultList.AddItem(i,15,str,-1);
	if(pDoc->m_Setting3[0].m_PracTime<0)
	{
		str = "Disabled";
	}
	else
	{
		str.Format("%d",pDoc->m_Setting3[0].m_PracTime);
	}
	m_ResultList.AddItem(i,16,str,-1);
	if(pDoc->m_Setting3[0].m_ExperTime<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_Setting3[0].m_ExperTime);
	}
	m_ResultList.AddItem(i,17,str,-1);
	if(pDoc->m_Setting3[0].m_PracTimes<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_Setting3[0].m_PracTimes);
	}
	m_ResultList.AddItem(i,18,str,-1);
	if(pDoc->m_Setting3[0].m_ExperTimes<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_Setting3[0].m_ExperTimes);
	}
	m_ResultList.AddItem(i,19,str,-1);

	str.Format("%d",pDoc->m_Shape[0]);
	m_ResultList.AddItem(i,20,str,-1);
	str.Format("%d",pDoc->m_Character[0]);
	m_ResultList.AddItem(i,21,str,-1);
	str.Format("%d",pDoc->m_Shape[1]);
	m_ResultList.AddItem(i,22,str,-1);
	str.Format("%d",pDoc->m_Character[1]);
	m_ResultList.AddItem(i,23,str,-1);
	str.Format("%d",pDoc->m_Shape[2]);
	m_ResultList.AddItem(i,24,str,-1);
	str.Format("%d",pDoc->m_Character[2]);
	m_ResultList.AddItem(i,25,str,-1);
	str.Format("%d",pDoc->m_Shape[3]);
	m_ResultList.AddItem(i,26,str,-1);
	str.Format("%d",pDoc->m_Character[3]);
	m_ResultList.AddItem(i,27,str,-1);
	str.Format("%d",pDoc->m_Shape[4]);
	m_ResultList.AddItem(i,28,str,-1);
	str.Format("%d",pDoc->m_Character[4]);
	m_ResultList.AddItem(i,29,str,-1);
	str.Format("%d",pDoc->m_Shape[5]);
	m_ResultList.AddItem(i,30,str,-1);
	str.Format("%d",pDoc->m_Character[5]);
	m_ResultList.AddItem(i,31,str,-1);

	str.Format("%d",pDoc->m_TrialType);
	m_ResultList.AddItem(i,32,str,-1);
	str.Format("%d",pDoc->m_CodeNo);
	m_ResultList.AddItem(i,33,str,-1);
	str.Format("%d",pDoc->m_CodeType[i]);
	m_ResultList.AddItem(i,34,str,-1);
	str.Format("%u",pDoc->m_CodeStartTime[i]);
	m_ResultList.AddItem(i,35,str,-1);
	str.Format("%u",pDoc->m_CodeSureTime[i]);
	m_ResultList.AddItem(i,36,str,-1);
	str.Format("%d",pDoc->m_CodeButtonNo[i]);
	m_ResultList.AddItem(i,37,str,-1);
	str.Format("%u",pDoc->m_CodeRT[i]);
	m_ResultList.AddItem(i,38,str,-1);
	str.Format("%d",pDoc->m_bCodeAcc[i]);
	m_ResultList.AddItem(i,39,str,-1);
	return TRUE;
}

BOOL CListDlg::AddT3EventItem(int i)
{
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
    CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();
	CString str;
	m_ResultList2.AddItem(i,0,pDoc->m_PartInfo.m_TesterNo,-1);
	m_ResultList2.AddItem(i,1,pDoc->m_PartInfo.m_TesterName,-1);
	m_ResultList2.AddItem(i,2,pDoc->m_PartInfo.m_TesterSex,-1);
	str.Format("%d",pDoc->m_PartInfo.m_Session);
	m_ResultList2.AddItem(i,3,str,-1);

	str.Format("%d",pDoc->m_Setting3[0].m_PracMode);
	m_ResultList2.AddItem(i,4,str,-1);
	str.Format("%d",pDoc->m_Setting3[0].m_ExperMode);
	m_ResultList2.AddItem(i,5,str,-1);
	str.Format("%d",pDoc->m_Setting3[0].m_MainTask);
	m_ResultList2.AddItem(i,6,str,-1);
	str.Format("%d",pDoc->m_Setting3[0].m_SubTask);
	m_ResultList2.AddItem(i,7,str,-1);

//	str.Format("%d",pDoc->m_Setting3.m_MainTaskMode);
	if(pDoc->m_Setting3[0].m_MainTaskMode<0)
	{
		m_ResultList2.AddItem(i,8,"Disabled",-1);
	}
	else
	{
	    m_ResultList2.AddItem(i,8,m_MainTaskModeStr[pDoc->m_Setting3[0].m_MainTaskMode],-1);
	}
//	str.Format("%d",pDoc->m_Setting3.m_Background);
	m_ResultList2.AddItem(i,9,m_BackgroundStr[pDoc->m_Setting3[0].m_Background],-1);
	if(pDoc->m_Setting3[0].m_InitSpeed<0)
	{
		str = "Disabled";
	}
	else
	{
        str.Format("%.2f",pDoc->m_Setting3[0].m_InitSpeed);
	}
	m_ResultList2.AddItem(i,10,str,-1); 
//	str.Format("%d",pDoc->m_Setting3.m_EventMode);
	if(pDoc->m_Setting3[0].m_EventMode<0)
	{
		m_ResultList2.AddItem(i,11,"Disabled",-1);
	}
	else
	{
	    m_ResultList2.AddItem(i,11,m_EventModeStr[pDoc->m_Setting3[0].m_EventMode],-1);
	}
//  str.Format("%d",pDoc->m_Setting3.m_CodePairMode);
	if(pDoc->m_Setting3[0].m_CodePairMode<0)
	{
		m_ResultList2.AddItem(i,12,"Disabled",-1);
	}
	else
	{
	    m_ResultList2.AddItem(i,12,m_CodePairModeStr[pDoc->m_Setting3[0].m_CodePairMode],-1);
	}
	if(pDoc->m_Setting3[0].m_CodePairNum<0)
	{
		str = "Disabled";
	}
	else
	{
        str.Format("%d",pDoc->m_Setting3[0].m_CodePairNum);
	}
	m_ResultList2.AddItem(i,13,str,-1);
//  str.Format("%d",pDoc->m_Setting3.m_DisplayMode);
	if(pDoc->m_Setting3[0].m_DisplayMode<0)
	{
		m_ResultList2.AddItem(i,14,"Disabled",-1);
	}
	else
	{
	    m_ResultList2.AddItem(i,14,m_DisplayModeStr[pDoc->m_Setting3[0].m_DisplayMode],-1);
	}
	if(pDoc->m_Setting3[0].m_EventFrequency<0)
	{
		str = "Disabled";
	}
	else
	{
        str.Format("%d",pDoc->m_Setting3[0].m_EventFrequency);
	}
	m_ResultList2.AddItem(i,15,str,-1);
	if(pDoc->m_Setting3[0].m_PracTime<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_Setting3[0].m_PracTime);
	}
	m_ResultList2.AddItem(i,16,str,-1);
	if(pDoc->m_Setting3[0].m_ExperTime<0)
	{
		str = "Disabled";
	}
	else
	{
        str.Format("%d",pDoc->m_Setting3[0].m_ExperTime);
	}
	m_ResultList2.AddItem(i,17,str,-1);
	if(pDoc->m_Setting3[0].m_PracTimes<0)
	{
		str = "Disabled";
	}
	else
	{
        str.Format("%d",pDoc->m_Setting3[0].m_PracTimes);
	}
	m_ResultList2.AddItem(i,18,str,-1);
	if(pDoc->m_Setting3[0].m_ExperTimes<0)
	{
		str = "Disabled";
	}
	else
	{
        str.Format("%d",pDoc->m_Setting3[0].m_ExperTimes);
	}
    m_ResultList2.AddItem(i,19,str,-1);

	str.Format("%d",pDoc->m_TrialType);
	m_ResultList2.AddItem(i,20,str,-1);
	str.Format("%d",pDoc->m_RecordNo);
	m_ResultList2.AddItem(i,21,str,-1);
	str.Format("%d",pDoc->m_EventType[i]);
	m_ResultList2.AddItem(i,22,str,-1);
	str.Format("%u",pDoc->m_EventStartTime[i]);
	m_ResultList2.AddItem(i,23,str,-1);
    str.Format("%u",pDoc->m_EventSureTime[i]);
	m_ResultList2.AddItem(i,24,str,-1);
    str.Format("%u",pDoc->m_EventRT[i]);
	m_ResultList2.AddItem(i,25,str,-1);  
    str.Format("%d",pDoc->m_SureButtonNo[i]);
	m_ResultList2.AddItem(i,26,str,-1);
    str.Format("%d",pDoc->m_bEventAcc[i]);
	m_ResultList2.AddItem(i,27,str,-1);
    return TRUE;
}

BOOL CListDlg::AddT4Item(int i)
{
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
    CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();
	CString str;
	m_ResultList.AddItem(i,0,pDoc->m_PartInfo.m_TesterNo,-1);
	m_ResultList.AddItem(i,1,pDoc->m_PartInfo.m_TesterName,-1);
	m_ResultList.AddItem(i,2,pDoc->m_PartInfo.m_TesterSex,-1);
	str.Format("%d",pDoc->m_PartInfo.m_Session);
	m_ResultList.AddItem(i,3,str,-1);

	str.Format("%d",pDoc->m_Setting4[0].m_PracMode);
	m_ResultList.AddItem(i,4,str,-1);
    str.Format("%d",pDoc->m_Setting4[0].m_ExperMode);
	m_ResultList.AddItem(i,5,str,-1);
    m_ResultList.AddItem(i,6,m_TouchOrderStr[pDoc->m_Setting4[0].m_TouchOrder],-1);

	str.Format("%d",pDoc->m_TrialType);
	m_ResultList.AddItem(i,7,str,-1);
	str.Format("%d",pDoc->m_TouchGroupNo);
	m_ResultList.AddItem(i,8,str,-1);
	str.Format("%d",pDoc->m_TouchNo);
	m_ResultList.AddItem(i,9,str,-1);
	str.Format("%d",pDoc->m_TouchNoOrder[i]);
	m_ResultList.AddItem(i,10,str,-1);
	str.Format("%d",pDoc->m_TouchDistance[i]);
	m_ResultList.AddItem(i,11,str,-1);
	str.Format("%d",pDoc->m_sizediff[i]);
	m_ResultList.AddItem(i,12,str,-1);

	str.Format("%d",pDoc->m_SureButtonNo[i]);
	m_ResultList.AddItem(i,13,str,-1);
	str.Format("%u",pDoc->m_TouchStartTime[i]);
	m_ResultList.AddItem(i,14,str,-1);
	str.Format("%u",pDoc->m_TouchSureTime[i]);
	m_ResultList.AddItem(i,15,str,-1);
	str.Format("%u",pDoc->m_TouchRT[i]);
	m_ResultList.AddItem(i,16,str,-1);
	str.Format("%d",pDoc->m_TouchAcc[i]);
	m_ResultList.AddItem(i,17,str,-1);
	return TRUE;
}

BOOL CListDlg::AddT5TraceItem(int i)
{
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
    CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();
	CString str;
	m_ResultList.AddItem(i,0,pDoc->m_PartInfo.m_TesterNo,-1);
	m_ResultList.AddItem(i,1,pDoc->m_PartInfo.m_TesterName,-1);
	m_ResultList.AddItem(i,2,pDoc->m_PartInfo.m_TesterSex,-1);
	str.Format("%d",pDoc->m_PartInfo.m_Session);
	m_ResultList.AddItem(i,3,str,-1);

	str.Format("%.2f",pDoc->m_HardSetting.m_DistanceError);
	m_ResultList.AddItem(i,4,str,-1);
	str.Format("%d",pDoc->m_Setting5[0].m_PracMode);
	m_ResultList.AddItem(i,5,str,-1);
	str.Format("%d",pDoc->m_Setting5[0].m_ExperMode);
	m_ResultList.AddItem(i,6,str,-1);
	str.Format("%d",pDoc->m_Setting5[0].m_MainTask);
	m_ResultList.AddItem(i,7,str,-1);
	str.Format("%d",pDoc->m_Setting5[0].m_SubTask);
	m_ResultList.AddItem(i,8,str,-1);

//	str.Format("%d",pDoc->m_Setting5.m_Background);
	m_ResultList.AddItem(i,9,m_BackgroundStr[pDoc->m_Setting5[0].m_Background],-1);
	if(pDoc->m_Setting5[0].m_InitSpeed<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%.2f",pDoc->m_Setting5[0].m_InitSpeed);
	}
	m_ResultList.AddItem(i,10,str,-1);
//	str.Format("%d",pDoc->m_Setting5.m_SignMemType);
	if(pDoc->m_Setting5[0].m_SignMemType<0)
	{
		m_ResultList.AddItem(i,11,"Disabled",-1);
	}
	else
	{
	    m_ResultList.AddItem(i,11,m_SignMemTypeStr[pDoc->m_Setting5[0].m_SignMemType],-1);
	}
//	str.Format("%d",pDoc->m_Setting5.m_SignMemMode);
	if(pDoc->m_Setting5[0].m_SignMemMode<0)
	{
		m_ResultList.AddItem(i,12,"Disabled",-1);
	}
	else
	{
	    m_ResultList.AddItem(i,12,m_SignMemModeStr[pDoc->m_Setting5[0].m_SignMemMode],-1);
	}
	if(pDoc->m_Setting5[0].m_SignMemNum<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_Setting5[0].m_SignMemNum);
	}
	m_ResultList.AddItem(i,13,str,-1);
//	str.Format("%d",pDoc->m_Setting5.m_SignShowMode);
	if(pDoc->m_Setting5[0].m_SignShowMode<0)
	{
		m_ResultList.AddItem(i,14,"Disabled",-1);
	}
	else
	{
	    m_ResultList.AddItem(i,14,m_SignShowModeStr[pDoc->m_Setting5[0].m_SignShowMode],-1);
	}
    if(pDoc->m_Setting5[0].m_SignShowTime<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%.1f",pDoc->m_Setting5[0].m_SignShowTime);
	}
	m_ResultList.AddItem(i,15,str,-1);
	if(pDoc->m_Setting5[0].m_PracTime<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_Setting5[0].m_PracTime);
	}
	m_ResultList.AddItem(i,16,str,-1);
	if(pDoc->m_Setting5[0].m_ExperTime<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_Setting5[0].m_ExperTime);
	}
	m_ResultList.AddItem(i,17,str,-1);
	if(pDoc->m_Setting5[0].m_PracTimes<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_Setting5[0].m_PracTimes);
	}
	m_ResultList.AddItem(i,18,str,-1);
	if(pDoc->m_Setting5[0].m_ExperTimes<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_Setting5[0].m_ExperTimes);
	}
	m_ResultList.AddItem(i,19,str,-1);
			
    str.Format("%d",pDoc->m_TrialType);
	m_ResultList.AddItem(i,20,str,-1);
	str.Format("%d",pDoc->m_PointNum);
	m_ResultList.AddItem(i,21,str,-1);
	str.Format("%u",pDoc->m_PointTime[i]);
	m_ResultList.AddItem(i,22,str,-1);
	str.Format("%d",pDoc->m_ObjPoint[i].x);
	m_ResultList.AddItem(i,23,str,-1);
	str.Format("%d",pDoc->m_ObjPoint[i].y);
	m_ResultList.AddItem(i,24,str,-1);
	str.Format("%d",pDoc->m_PostPoint[i].x);
	m_ResultList.AddItem(i,25,str,-1);
	str.Format("%d",pDoc->m_PostPoint[i].y);
	m_ResultList.AddItem(i,26,str,-1);
	str.Format("%.2f",pDoc->m_Distance[i]);
	m_ResultList.AddItem(i,27,str,-1);
	str.Format("%d",pDoc->m_bHit[i]);
	m_ResultList.AddItem(i,28,str,-1);

	str.Format("%.2f",pDoc->m_ObjSpeedX[i]);
	m_ResultList.AddItem(i,29,str,-1);
	str.Format("%.2f",pDoc->m_ObjSpeedY[i]);
	m_ResultList.AddItem(i,30,str,-1);
	str.Format("%.2f",pDoc->m_PostSpeedX[i]);
	m_ResultList.AddItem(i,31,str,-1);
	str.Format("%.2f",pDoc->m_PostSpeedY[i]);
	m_ResultList.AddItem(i,32,str,-1);
	return TRUE;
}

BOOL CListDlg::AddT5SignItem(int i)
{
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
    CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();
	CString str;
	m_ResultList2.AddItem(i,0,pDoc->m_PartInfo.m_TesterNo,-1);
	m_ResultList2.AddItem(i,1,pDoc->m_PartInfo.m_TesterName,-1);
	m_ResultList2.AddItem(i,2,pDoc->m_PartInfo.m_TesterSex,-1);
	str.Format("%d",pDoc->m_PartInfo.m_Session);
	m_ResultList2.AddItem(i,3,str,-1);

	str.Format("%.2f",pDoc->m_HardSetting.m_DistanceError);
	m_ResultList2.AddItem(i,4,str,-1);
	str.Format("%d",pDoc->m_Setting5[0].m_PracMode);
	m_ResultList2.AddItem(i,5,str,-1);
	str.Format("%d",pDoc->m_Setting5[0].m_ExperMode);
	m_ResultList2.AddItem(i,6,str,-1);
	str.Format("%d",pDoc->m_Setting5[0].m_MainTask);
	m_ResultList2.AddItem(i,7,str,-1);
	str.Format("%d",pDoc->m_Setting5[0].m_SubTask);
	m_ResultList2.AddItem(i,8,str,-1);

//	str.Format("%d",pDoc->m_Setting5.m_Background);
	m_ResultList2.AddItem(i,9,m_BackgroundStr[pDoc->m_Setting5[0].m_Background],-1);
	if(pDoc->m_Setting5[0].m_InitSpeed<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%.2f",pDoc->m_Setting5[0].m_InitSpeed);
	}
	m_ResultList2.AddItem(i,10,str,-1);
//	str.Format("%d",pDoc->m_Setting5.m_SignMemType);
	if(pDoc->m_Setting5[0].m_SignMemType<0)
	{
		m_ResultList.AddItem(i,11,"Disabled",-1);
	}
	else
	{
	    m_ResultList2.AddItem(i,11,m_SignMemTypeStr[pDoc->m_Setting5[0].m_SignMemType],-1);
	}
//	str.Format("%d",pDoc->m_Setting5.m_SignMemMode);
	if(pDoc->m_Setting5[0].m_SignMemMode<0)
	{
		m_ResultList.AddItem(i,12,"Disabled",-1);
	}
	else
	{
	    m_ResultList2.AddItem(i,12,m_SignMemModeStr[pDoc->m_Setting5[0].m_SignMemMode],-1);
	}
	if(pDoc->m_Setting5[0].m_SignMemNum<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_SignMemNum);
	}
	m_ResultList2.AddItem(i,13,str,-1);
//	str.Format("%d",pDoc->m_Setting5.m_SignShowMode);
	if(pDoc->m_Setting5[0].m_SignShowMode<0)
	{
		m_ResultList.AddItem(i,14,"Disabled",-1);
	}
	else
	{
	    m_ResultList2.AddItem(i,14,m_SignShowModeStr[pDoc->m_Setting5[0].m_SignShowMode],-1);
	}
    if(pDoc->m_Setting5[0].m_SignShowTime<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%.1f",pDoc->m_Setting5[0].m_SignShowTime);
	}
	m_ResultList2.AddItem(i,15,str,-1);
	if(pDoc->m_Setting5[0].m_PracTime<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_Setting5[0].m_PracTime);
	}
	m_ResultList2.AddItem(i,16,str,-1);
	if(pDoc->m_Setting5[0].m_ExperTime<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_Setting5[0].m_ExperTime);
	}
	m_ResultList2.AddItem(i,17,str,-1);
	if(pDoc->m_Setting5[0].m_PracTimes<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_Setting5[0].m_PracTimes);
	}
	m_ResultList2.AddItem(i,18,str,-1);
	if(pDoc->m_Setting5[0].m_ExperTimes<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_Setting5[0].m_ExperTimes);
	}
	m_ResultList2.AddItem(i,19,str,-1);
			
    str.Format("%d",pDoc->m_TrialType);
	m_ResultList2.AddItem(i,20,str,-1);
	str.Format("%d",pDoc->m_SignGroupNo);
	m_ResultList2.AddItem(i,21,str,-1);
	str.Format("%d",pDoc->m_SignNo);
	m_ResultList2.AddItem(i,22,str,-1);
	str.Format("%d",pDoc->m_MemTime);
	m_ResultList2.AddItem(i,23,str,-1);
	str.Format("%d",pDoc->m_SignType[i]);
	m_ResultList2.AddItem(i,24,str,-1);
    m_ResultList2.AddItem(i,25,pDoc->m_SignName,-1);
	str.Format("%u",pDoc->m_SignStartTime[i]);
	m_ResultList2.AddItem(i,26,str,-1);
	str.Format("%u",pDoc->m_SignSureTime[i]);
	m_ResultList2.AddItem(i,27,str,-1);
	str.Format("%d",pDoc->m_SureButtonNo[i]);
	m_ResultList2.AddItem(i,28,str,-1);
	str.Format("%u",pDoc->m_SignRT[i]);
	m_ResultList2.AddItem(i,29,str,-1);
	str.Format("%d",pDoc->m_SignAcc[i]);
	m_ResultList2.AddItem(i,30,str,-1);
	return TRUE;
}

BOOL CListDlg::AddT6TraceItem(int i)
{
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
    CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();
	CString str;
	m_ResultList.AddItem(i,0,pDoc->m_PartInfo.m_TesterNo,-1);
	m_ResultList.AddItem(i,1,pDoc->m_PartInfo.m_TesterName,-1);
	m_ResultList.AddItem(i,2,pDoc->m_PartInfo.m_TesterSex,-1);
	str.Format("%d",pDoc->m_PartInfo.m_Session);
	m_ResultList.AddItem(i,3,str,-1);

	str.Format("%.2f",pDoc->m_HardSetting.m_DistanceError);
	m_ResultList.AddItem(i,4,str,-1);
	str.Format("%d",pDoc->m_Setting6[0].m_PracMode);
	m_ResultList.AddItem(i,5,str,-1);
	str.Format("%d",pDoc->m_Setting6[0].m_ExperMode);
	m_ResultList.AddItem(i,6,str,-1);
	str.Format("%d",pDoc->m_Setting6[0].m_MainTask);
	m_ResultList.AddItem(i,7,str,-1);
	str.Format("%d",pDoc->m_Setting6[0].m_SubTask);
	m_ResultList.AddItem(i,8,str,-1);

//	str.Format("%d",pDoc->m_Setting6.m_Background);
	m_ResultList.AddItem(i,9,m_BackgroundStr[pDoc->m_Setting6[0].m_Background],-1);
	if(pDoc->m_Setting6[0].m_InitSpeed<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%.2f",pDoc->m_Setting6[0].m_InitSpeed);
	}
	m_ResultList.AddItem(i,10,str,-1);
	if(pDoc->m_Setting6[0].m_CubeNum1<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_Setting6[0].m_CubeNum1);
	}
	m_ResultList.AddItem(i,11,str,-1);
	if(pDoc->m_Setting6[0].m_CubeNum2<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_Setting6[0].m_CubeNum2);
	}
	m_ResultList.AddItem(i,12,str,-1);
	if(pDoc->m_Setting6[0].m_CubeNum3<0)
	{
		str = "Disabled";
	}
	else
	{
    	str.Format("%d",pDoc->m_Setting6[0].m_CubeNum3);
	}
	m_ResultList.AddItem(i,13,str,-1);
	if(pDoc->m_Setting6[0].m_CubeNum4<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_Setting6[0].m_CubeNum4);
	}
	m_ResultList.AddItem(i,14,str,-1);
	if(pDoc->m_Setting6[0].m_Prototype<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_Setting6[0].m_Prototype+1);
	}
	m_ResultList.AddItem(i,15,str,-1);
//	str.Format("%d",pDoc->m_Setting6.m_RefAxis);
	if(pDoc->m_Setting6[0].m_RefAxis<0)
	{
		m_ResultList.AddItem(i,16,"Disabled",-1);
	}
	else
	{
	    m_ResultList.AddItem(i,16,m_RefAxisStr[pDoc->m_Setting6[0].m_RefAxis],-1);
	}
	if(pDoc->m_Setting6[0].m_MemTaskMode<0)
	{
		m_ResultList.AddItem(i,17,"Disabled",-1);
	}
	else
	{
	    m_ResultList2.AddItem(i,17,m_MemTaskModeStr[pDoc->m_Setting6[0].m_MemTaskMode],-1);
	}
	if(pDoc->m_Setting6[0].m_PracTime<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_Setting6[0].m_PracTime);
	}
	m_ResultList.AddItem(i,18,str,-1);
	if(pDoc->m_Setting6[0].m_ExperTime<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_Setting6[0].m_ExperTime);
	}
	m_ResultList.AddItem(i,19,str,-1);
    if(pDoc->m_Setting6[0].m_PracTimes<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_Setting6[0].m_PracTimes);
	}
	m_ResultList.AddItem(i,20,str,-1);
    if(pDoc->m_Setting6[0].m_ExperTimes<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_Setting6[0].m_ExperTimes);
	}
	m_ResultList.AddItem(i,21,str,-1);
			
    str.Format("%d",pDoc->m_TrialType);
	m_ResultList.AddItem(i,22,str,-1);
	str.Format("%d",pDoc->m_PointNum);
	m_ResultList.AddItem(i,23,str,-1);
	str.Format("%u",pDoc->m_PointTime[i]);
	m_ResultList.AddItem(i,24,str,-1);
	str.Format("%d",pDoc->m_ObjPoint[i].x);
	m_ResultList.AddItem(i,25,str,-1);
	str.Format("%d",pDoc->m_ObjPoint[i].y);
	m_ResultList.AddItem(i,26,str,-1);
	str.Format("%d",pDoc->m_PostPoint[i].x);
	m_ResultList.AddItem(i,27,str,-1);
	str.Format("%d",pDoc->m_PostPoint[i].y);
	m_ResultList.AddItem(i,28,str,-1);
	str.Format("%.2f",pDoc->m_Distance[i]);
	m_ResultList.AddItem(i,29,str,-1);
	str.Format("%d",pDoc->m_bHit[i]);
	m_ResultList.AddItem(i,30,str,-1);

	str.Format("%.2f",pDoc->m_ObjSpeedX[i]);
	m_ResultList.AddItem(i,31,str,-1);
	str.Format("%.2f",pDoc->m_ObjSpeedY[i]);
	m_ResultList.AddItem(i,32,str,-1);
	str.Format("%.2f",pDoc->m_PostSpeedX[i]);
	m_ResultList.AddItem(i,33,str,-1);
	str.Format("%.2f",pDoc->m_PostSpeedY[i]);
	m_ResultList.AddItem(i,34,str,-1);
	return TRUE;
}

BOOL CListDlg::AddT6JudgeItem(int i)
{
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
    CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();
	CString str;
	m_ResultList2.AddItem(i,0,pDoc->m_PartInfo.m_TesterNo,-1);
	m_ResultList2.AddItem(i,1,pDoc->m_PartInfo.m_TesterName,-1);
	m_ResultList2.AddItem(i,2,pDoc->m_PartInfo.m_TesterSex,-1);
	str.Format("%d",pDoc->m_PartInfo.m_Session);
	m_ResultList2.AddItem(i,3,str,-1);

	str.Format("%.2f",pDoc->m_HardSetting.m_DistanceError);
	m_ResultList2.AddItem(i,4,str,-1);
	str.Format("%d",pDoc->m_Setting6[0].m_PracMode);
	m_ResultList2.AddItem(i,5,str,-1);
	str.Format("%d",pDoc->m_Setting6[0].m_ExperMode);
	m_ResultList2.AddItem(i,6,str,-1);
	str.Format("%d",pDoc->m_Setting6[0].m_MainTask);
	m_ResultList2.AddItem(i,7,str,-1);
	str.Format("%d",pDoc->m_Setting6[0].m_SubTask);
	m_ResultList2.AddItem(i,8,str,-1);

//	str.Format("%d",pDoc->m_Setting6.m_Background);
	m_ResultList2.AddItem(i,9,m_BackgroundStr[pDoc->m_Setting6[0].m_Background],-1);
	if(pDoc->m_Setting6[0].m_InitSpeed<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%.2f",pDoc->m_Setting6[0].m_InitSpeed);
	}
	m_ResultList2.AddItem(i,10,str,-1);
	if(pDoc->m_Setting6[0].m_CubeNum1<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_Setting6[0].m_CubeNum1);
	}
	m_ResultList2.AddItem(i,11,str,-1);
	if(pDoc->m_Setting6[0].m_CubeNum2<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_Setting6[0].m_CubeNum2);
	}
	m_ResultList2.AddItem(i,12,str,-1);
	if(pDoc->m_Setting6[0].m_CubeNum3<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_Setting6[0].m_CubeNum3);
	}
	m_ResultList2.AddItem(i,13,str,-1);
	if(pDoc->m_Setting6[0].m_CubeNum4<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_Setting6[0].m_CubeNum4);
	}
	m_ResultList2.AddItem(i,14,str,-1);
	if(pDoc->m_Setting6[0].m_Prototype<0)
	{
		str = "Disabled";
	}
	else
	{
    	str.Format("%d",pDoc->m_Setting6[0].m_Prototype+1);
	}
	m_ResultList2.AddItem(i,15,str,-1);
//	str.Format("%d",pDoc->m_Setting6.m_RefAxis);
	if(pDoc->m_Setting6[0].m_RefAxis<0)
	{
		m_ResultList2.AddItem(i,16,"Disabled",-1);
	}
	else
	{
	    m_ResultList2.AddItem(i,16,m_RefAxisStr[pDoc->m_Setting6[0].m_RefAxis],-1);
	}
	if(pDoc->m_Setting6[0].m_MemTaskMode<0)
	{
		m_ResultList2.AddItem(i,17,"Disabled",-1);
	}
	else
	{
	    m_ResultList2.AddItem(i,17,m_MemTaskModeStr[pDoc->m_Setting6[0].m_MemTaskMode],-1);
	}
	if(pDoc->m_Setting6[0].m_PracTime<0)
	{
		str = "Disabled";
	}
	else
	{
    	str.Format("%d",pDoc->m_Setting6[0].m_PracTime);
	}
	m_ResultList2.AddItem(i,18,str,-1);
	if(pDoc->m_Setting6[0].m_ExperTime<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_Setting6[0].m_ExperTime);
	}
	m_ResultList2.AddItem(i,19,str,-1);
	if(pDoc->m_Setting6[0].m_PracTimes<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_Setting6[0].m_PracTimes);
	}
	m_ResultList2.AddItem(i,20,str,-1);
	if(pDoc->m_Setting6[0].m_ExperTimes<0)
	{
		str = "Disabled";
	}
	else
	{
	    str.Format("%d",pDoc->m_Setting6[0].m_ExperTimes);
	}
	m_ResultList2.AddItem(i,21,str,-1);
			
    str.Format("%d",pDoc->m_TrialType);
	m_ResultList2.AddItem(i,22,str,-1);
	str.Format("%d",pDoc->m_SignGroupNo);
	m_ResultList2.AddItem(i,23,str,-1);
	str.Format("%d",pDoc->m_MemNo);
	m_ResultList2.AddItem(i,24,str,-1);
	str.Format("%d",pDoc->m_CubeNum[i]);
	m_ResultList2.AddItem(i,25,str,-1);
	m_ResultList2.AddItem(i,26,pDoc->m_LMemName,-1);
	m_ResultList2.AddItem(i,27,pDoc->m_RMemName,-1);
	str.Format("%d",pDoc->m_LMemAngle[i]);
	m_ResultList2.AddItem(i,28,str,-1);
	str.Format("%d",pDoc->m_RMemAngle[i]);
	m_ResultList2.AddItem(i,29,str,-1);
	str.Format("%d",pDoc->m_MemAngleDiff[i]);
	m_ResultList2.AddItem(i,30,str,-1);
	str.Format("%d",pDoc->m_Same[i]);
	m_ResultList2.AddItem(i,31,str,-1);
	str.Format("%u",pDoc->m_SignStartTime[i]);
	m_ResultList2.AddItem(i,32,str,-1);
	str.Format("%u",pDoc->m_SignSureTime[i]);
	m_ResultList2.AddItem(i,33,str,-1);
	str.Format("%d",pDoc->m_SureButtonNo[i]);
	m_ResultList2.AddItem(i,34,str,-1);
	str.Format("%u",pDoc->m_SignRT[i]);
	m_ResultList2.AddItem(i,35,str,-1);
	str.Format("%d",pDoc->m_SignAcc[i]);
	m_ResultList2.AddItem(i,36,str,-1);
	return TRUE;
}

BOOL CListDlg::AddT6MemoryItem(int i)
{
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
    CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();
	CString str;
	m_ResultList2.AddItem(i,0,pDoc->m_PartInfo.m_TesterNo,-1);
			m_ResultList2.AddItem(i,1,pDoc->m_PartInfo.m_TesterName,-1);
			m_ResultList2.AddItem(i,2,pDoc->m_PartInfo.m_TesterSex,-1);
	        str.Format("%d",pDoc->m_PartInfo.m_Session);
			m_ResultList2.AddItem(i,3,str,-1);

			str.Format("%.2f",pDoc->m_HardSetting.m_DistanceError);
			m_ResultList2.AddItem(i,4,str,-1);
			str.Format("%d",pDoc->m_Setting6[0].m_PracMode);
			m_ResultList2.AddItem(i,5,str,-1);
	        str.Format("%d",pDoc->m_Setting6[0].m_ExperMode);
			m_ResultList2.AddItem(i,6,str,-1);
		    str.Format("%d",pDoc->m_Setting6[0].m_MainTask);
			m_ResultList2.AddItem(i,7,str,-1);
	        str.Format("%d",pDoc->m_Setting6[0].m_SubTask);
			m_ResultList2.AddItem(i,8,str,-1);

//	        str.Format("%d",pDoc->m_Setting6.m_Background);
			m_ResultList2.AddItem(i,9,m_BackgroundStr[pDoc->m_Setting6[0].m_Background],-1);
	        str.Format("%.2f",pDoc->m_Setting6[0].m_InitSpeed);
			m_ResultList2.AddItem(i,10,str,-1);
			str.Format("%d",pDoc->m_Setting6[0].m_CubeNum1);
			m_ResultList2.AddItem(i,11,str,-1);
			str.Format("%d",pDoc->m_Setting6[0].m_CubeNum2);
			m_ResultList2.AddItem(i,12,str,-1);
			str.Format("%d",pDoc->m_Setting6[0].m_CubeNum3);
			m_ResultList2.AddItem(i,13,str,-1);
			str.Format("%d",pDoc->m_Setting6[0].m_CubeNum4);
			m_ResultList2.AddItem(i,14,str,-1);
	        str.Format("%d",pDoc->m_Setting6[0].m_Prototype+1);
			m_ResultList.AddItem(i,15,str,-1);
//	        str.Format("%d",pDoc->m_Setting6.m_RefAxis);
			m_ResultList2.AddItem(i,16,m_RefAxisStr[pDoc->m_Setting6[0].m_RefAxis],-1);
			m_ResultList2.AddItem(i,17,m_MemTaskModeStr[pDoc->m_Setting6[0].m_MemTaskMode],-1);
	        str.Format("%d",pDoc->m_Setting6[0].m_PracTime);
			m_ResultList2.AddItem(i,18,str,-1);
			str.Format("%d",pDoc->m_Setting6[0].m_ExperTime);
			m_ResultList2.AddItem(i,19,str,-1);
	        str.Format("%d",pDoc->m_Setting6[0].m_PracTimes);
			m_ResultList2.AddItem(i,20,str,-1);
	        str.Format("%d",pDoc->m_Setting6[0].m_ExperTimes);
			m_ResultList2.AddItem(i,21,str,-1);
			
            str.Format("%d",pDoc->m_TrialType);
			m_ResultList2.AddItem(i,22,str,-1);
	        str.Format("%d",pDoc->m_SignGroupNo);
			m_ResultList2.AddItem(i,23,str,-1);
	        str.Format("%d",pDoc->m_MemNo);
			m_ResultList2.AddItem(i,24,str,-1);
	        str.Format("%d",pDoc->m_CubeNum[i]);
			m_ResultList2.AddItem(i,25,str,-1);
			m_ResultList2.AddItem(i,26,pDoc->m_LMemName,-1);
			m_ResultList2.AddItem(i,27,pDoc->m_RMemName,-1);
	        str.Format("%d",pDoc->m_LMemAngle[i]);
			m_ResultList2.AddItem(i,28,str,-1);
	        str.Format("%d",pDoc->m_RMemAngle[i]);
			m_ResultList2.AddItem(i,29,str,-1);
		    str.Format("%d",pDoc->m_MemAngleDiff[i]);
			m_ResultList2.AddItem(i,30,str,-1);
			str.Format("%d",pDoc->m_Same[i]);
			m_ResultList2.AddItem(i,31,str,-1);
	        str.Format("%u",pDoc->m_SignStartTime[i]);
			m_ResultList2.AddItem(i,32,str,-1);
	        str.Format("%u",pDoc->m_SignSureTime[i]);
			m_ResultList2.AddItem(i,33,str,-1);
	        str.Format("%d",pDoc->m_SureButtonNo[i]);
			m_ResultList2.AddItem(i,34,str,-1);
	        str.Format("%u",pDoc->m_SignRT[i]);
			m_ResultList2.AddItem(i,35,str,-1);
	        str.Format("%d",pDoc->m_SignAcc[i]);
			m_ResultList2.AddItem(i,36,str,-1);
		return TRUE;
}



HBRUSH CListDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_EDIT){
		pDC->SetBkColor(RGB(255,255,255));
	}
	return hbr;
}
