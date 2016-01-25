// AnalysisDlg.cpp : implementation file
//

#include "stdafx.h"
#include "taskcontrol.h"
#include "AnalysisDlg.h"
#include "math.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnalysisDlg dialog


CAnalysisDlg::CAnalysisDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAnalysisDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAnalysisDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAnalysisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAnalysisDlg)
	DDX_Control(pDX, IDC_RESULTLIST, m_ResultList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAnalysisDlg, CDialog)
	//{{AFX_MSG_MAP(CAnalysisDlg)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnalysisDlg message handlers

BOOL CAnalysisDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
//  DataAnalysis();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAnalysisDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	RECT wnRect;
	if(m_ResultList.GetSafeHwnd()!=NULL)
	{
		m_ResultList.GetWindowRect(&wnRect);
		ScreenToClient(&wnRect);
		m_ResultList.MoveWindow(wnRect.left,wnRect.top,cx-23,cy-20);
	}
}

//显示数据分析的结果
void CAnalysisDlg::DisplayResult()
{
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
    CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();

	int i,j;

	//设置列表控件属性
	CString cs;
    m_ResultList.SetExtendedStyle(LVS_EX_HEADERDRAGDROP|LVS_EX_FULLROWSELECT
		|LVS_EX_GRIDLINES|LVS_EX_SUBITEMIMAGES);
	m_ResultList.SetWindowPos(&wndBottom,10,10,220,220,SWP_SHOWWINDOW|SWP_NOMOVE|SWP_NOSIZE);

	CString str;

	//添加表头
	m_ResultList.DeleteAllItems();            //删除列表中所有内容(行)
    while (m_ResultList.DeleteColumn(0));     //删除列表中所有列
	m_ResultList.AddColumn(_T("指标"),1,300,LVCFMT_LEFT);
	m_ResultList.AddColumn(_T("指标值"),2,300,LVCFMT_LEFT);
	
	switch (pDoc->m_TaskNo)
	{
	//任务1
	case 1:
		m_ResultList.AddItem(0,0,"位移误差平均值(DistanceAve)",-1);
		m_ResultList.AddItem(1,0,"位移误差标准差(DistanceSqt)",-1);		
		m_ResultList.AddItem(2,0,"角度误差平均值(RotateErrorAve)",-1);
        m_ResultList.AddItem(3,0,"角度误差标准差(RotateErrorSqt)",-1);
		m_ResultList.AddItem(4,0,"击中总时间(HitTimeTotal)",-1);
		m_ResultList.AddItem(5,0,"击中时间比(HitTimeRate)",-1);	
		if(pDoc->m_bOpenFile1)
		{
			str.Format("%.2f",pDoc->m_DistanceAve);
			m_ResultList.AddItem(0,1,str,-1);
			str.Format("%.2f",pDoc->m_DistanceSqt);
			m_ResultList.AddItem(1,1,str,-1);
			str.Format("%.2f",pDoc->m_RotateErrorAve);
			m_ResultList.AddItem(2,1,str,-1);
			str.Format("%.2f",pDoc->m_RotateErrorSqt);
			m_ResultList.AddItem(3,1,str,-1);
			str.Format("%d",pDoc->m_HitTimeTotal);
			m_ResultList.AddItem(4,1,str,-1);
			str.Format("%.2f",pDoc->m_HitTimeRate);
			m_ResultList.AddItem(5,1,str,-1);
		}
		break;
	//任务2
	case 2:
		m_ResultList.AddItem(0,0,"位移误差平均值(DistanceAve)",-1);     
        m_ResultList.AddItem(1,0,"位移误差标准差(DistanceSqt)",-1);
		m_ResultList.AddItem(2,0,"击中总时间(HitTimeTotal)",-1);
		m_ResultList.AddItem(3,0,"击中时间比(HitTimeRate)",-1);	
		for(i=0;i<12;i++)
		{
			str.Format("保持时间%d误差率(HoldTimeRate%d)",i+1,i+1);
			m_ResultList.AddItem(i+4,0,str,-1);
		}
        if(pDoc->m_bOpenFile1)
		{
			str.Format("%.2f",pDoc->m_DistanceAve);
			m_ResultList.AddItem(0,1,str,-1);
			str.Format("%.2f",pDoc->m_DistanceSqt);
			m_ResultList.AddItem(1,1,str,-1);
			str.Format("%d",pDoc->m_HitTimeTotal);
			m_ResultList.AddItem(2,1,str,-1);
			str.Format("%.2f",pDoc->m_HitTimeRate);
			m_ResultList.AddItem(3,1,str,-1);
		}
		if(pDoc->m_bOpenFile2)
		{
			for(i=0;i<pDoc->m_Setting2[0].m_HoldTimeNum;i++)
			{
				//str.Format("%.2f", (float)pDoc->m_HoldErrorTotal[i] / (float)pDoc->m_HoldCountTotal[i]);
				str.Format("%.2f",pDoc->m_HoldTimeErrAve[i]);
				m_ResultList.AddItem(i+4,1,str,-1);
			}
			for (int i = pDoc->m_Setting2[0].m_HoldTimeNum; i < 12; i++)
			{
				str.Format("未设置");
				m_ResultList.AddItem(i + 4, 1, str, -1);
			}
		}
		break;
	//任务3
	case 3:
		if(pDoc->m_MainTaskMode == 0)//存在主任务
		{
			m_ResultList.AddItem(0,0,"位移误差平均值(DistanceAve)",-1);
			m_ResultList.AddItem(1,0,"位移误差标准差(DistanceSqt)",-1);
			m_ResultList.AddItem(2,0,"击中总时间(HitTimeTotal)",-1);
			m_ResultList.AddItem(3,0,"击中时间比(HitTimeRate)",-1);
			j=4;
		}
		else//废弃
		{
			m_ResultList.AddItem(0,0,"正确编码数(TrueCode)",-1);
			m_ResultList.AddItem(1,0,"错误编码数(FalseCode)",-1);
			m_ResultList.AddItem(2,0,"正确编码率(TrueCodeRate)",-1);
			m_ResultList.AddItem(3,0,"错误编码率(FalseCodeRate)",-1);
			m_ResultList.AddItem(4,0,"编码反应时平均值(CodeRTAvg)",-1);
			m_ResultList.AddItem(5,0,"编码反应时标准差(CodeRTSqr)",-1);
			j=6;
		}
		if(pDoc->m_Setting3[0].m_EventMode ==0)//简单任务
		{
			m_ResultList.AddItem(j,0,"击中数(HIT)",-1);
			m_ResultList.AddItem(j+1,0,"漏报数(MISS)",-1);
			m_ResultList.AddItem(j+2,0,"正确拒斥数(CR)",-1);
			m_ResultList.AddItem(j+3,0,"虚报数(FA)",-1);
			m_ResultList.AddItem(j+4,0,"突发事件反应时间平均值(RTAvg)",-1);
			m_ResultList.AddItem(j+5,0,"突发事件反应时间标准差(RTSqr)",-1);
		}
		else//选择任务
		{
			m_ResultList.AddItem(j,0,"击中数(HIT)",-1);
			m_ResultList.AddItem(j+1,0,"漏报数(MISS)",-1);
			m_ResultList.AddItem(j+2,0,"正确拒斥数(CR)",-1);
			m_ResultList.AddItem(j+3,0,"虚报数(FA)",-1);
			m_ResultList.AddItem(j+4,0,"靶事件反应时平均值(m_RTAvg)",-1);
			m_ResultList.AddItem(j+5,0,"靶事件反应时标准差(m_RTSqr)",-1);
		}

		if(pDoc->m_bOpenFile1)
		{
			if(pDoc->m_MainTaskMode == 0)//存在主任务
			{
				str.Format("%.2f",pDoc->m_DistanceAve);
				m_ResultList.AddItem(0,1,str,-1);
				str.Format("%.2f",pDoc->m_DistanceSqt);
				m_ResultList.AddItem(1,1,str,-1);
				str.Format("%d",pDoc->m_HitTimeTotal);
				m_ResultList.AddItem(2,1,str,-1);
				str.Format("%.2f",pDoc->m_HitTimeRate);
				m_ResultList.AddItem(3,1,str,-1);
				j=4;
			}
			else//废弃
			{
				str.Format("%d",pDoc->m_TrueCode);
				m_ResultList.AddItem(0,1,str,-1);
				str.Format("%d",pDoc->m_FalseCode);
				m_ResultList.AddItem(1,1,str,-1);
				str.Format("%.2f",(float)pDoc->m_TrueCode/(float)(pDoc->m_TrueCode+pDoc->m_FalseCode));
				m_ResultList.AddItem(2,1,str,-1);
				str.Format("%.2f",(float)pDoc->m_FalseCode/(float)(pDoc->m_TrueCode+pDoc->m_FalseCode));
				m_ResultList.AddItem(3,1,str,-1);
				str.Format("%.2f",pDoc->m_CodeRTAvg);
				m_ResultList.AddItem(4,1,str,-1);
				str.Format("%.2f",pDoc->m_CodeRTSqr);
				m_ResultList.AddItem(5,1,str,-1);
				j=6;
			}
		}
        if(pDoc->m_bOpenFile2)
		{
			if(pDoc->m_Setting3[0].m_EventMode ==0)//简单任务
			{
				str.Format("%d",pDoc->m_TrueCount);//击中数HIT
				m_ResultList.AddItem(j,1,str,-1);
				str.Format("%d",pDoc->m_MissingCount);//漏报数MISS
				m_ResultList.AddItem(j+1,1,str,-1);
//				str.Format("%d",pDoc->m_CRCount);//正确拒斥数CR：留空
				m_ResultList.AddItem(j+2,1,"",-1);
				//str.Format("%d",pDoc->m_FalseCount);//虚报数FA：留空
				m_ResultList.AddItem(j+3,1,"",-1);
				str.Format("%.2f",pDoc->m_RTAvg);//突发事件反映时间平均值RTAvg
				m_ResultList.AddItem(j+4,1,str,-1);
				str.Format("%.2f",pDoc->m_RTSqr);//突发事件反映时间标准差RTSqr
				m_ResultList.AddItem(j+5,1,str,-1);
			}
			else//选择任务
			{
				str.Format("%d",pDoc->m_TrueCount);//注释同简单任务
				m_ResultList.AddItem(j,1,str,-1);
				str.Format("%d",pDoc->m_MissingCount);
				m_ResultList.AddItem(j+1,1,str,-1);
				str.Format("%d",pDoc->m_CRCount);
				m_ResultList.AddItem(j+2,1,str,-1);
				str.Format("%d",pDoc->m_FalseCount);
				m_ResultList.AddItem(j+3,1,str,-1);
				str.Format("%.2f",pDoc->m_RTAvg);
				m_ResultList.AddItem(j+4,1,str,-1);
				str.Format("%.2f",pDoc->m_RTSqr);
				m_ResultList.AddItem(j+5,1,str,-1);
			}
		}
		break;
	//任务4
	case 4:
		for(i=0;i<3;i++)
		{
			for(j=0;j<6;j++)
			{
				str.Format("距离%d目标%d平均反应时间(RTAved%dt%d)",i+1,j+1,i+1,j+1);
				m_ResultList.AddItem(i*6+j,0,str,-1);
			}
		}
        if(pDoc->m_bOpenFile1)
		{
			for(i=0;i<3;i++)
			{
				for(j=0;j<6;j++)
				{
					str.Format("%.2f",(float)pDoc->m_TouchRTTotal[i][j]/(float)(pDoc->m_TouchTotal));
					m_ResultList.AddItem(i*6+j,1,str,-1);
				}
			}
		}
		break;
	//任务5
	case 5:
		m_ResultList.AddItem(0,0,"位移误差平均值(DistanceAve)",-1);
		m_ResultList.AddItem(1,0,"位移误差标准差(DistanceSqt)",-1);
		m_ResultList.AddItem(2,0,"击中总时间(HitTimeTotal)",-1);
		m_ResultList.AddItem(3,0,"击中时间比(HitTimeRate)",-1);
		for(i=0;i<5;i++)
		{
			str.Format("记忆数目%d反应时平均值(Num%dRTAvg)",i+4,i+4);
			m_ResultList.AddItem(4+i*6,0,str,-1);
			str.Format("记忆数目%d反应时标准差(Num%dRTSqr)",i+4,i+4);
			m_ResultList.AddItem(4+i*6+1,0,str,-1);
			str.Format("记忆数目%d击中数(Num%dHIT)",i+4,i+4);
			m_ResultList.AddItem(4+i*6+2,0,str,-1);
			str.Format("记忆数目%d漏报数(Num%dMISS)",i+4,i+4);
			m_ResultList.AddItem(4+i*6+3,0,str,-1);
			str.Format("记忆数目%d正确拒斥数(Num%dCR)",i+4,i+4);
			m_ResultList.AddItem(4+i*6+4,0,str,-1);
			str.Format("记忆数目%d虚报数(Num%dFA))",i+4,i+4);
			m_ResultList.AddItem(4+i*6+5,0,str,-1);
		}

		if(pDoc->m_bOpenFile1)
		{
			str.Format("%.2f",pDoc->m_DistanceAve);
			m_ResultList.AddItem(0,1,str,-1);
			str.Format("%.2f",pDoc->m_DistanceSqt);
			m_ResultList.AddItem(1,1,str,-1);
			str.Format("%d",pDoc->m_HitTimeTotal);
			m_ResultList.AddItem(2,1,str,-1);
			str.Format("%.2f",pDoc->m_HitTimeRate);
			m_ResultList.AddItem(3,1,str,-1);
		}
		if(pDoc->m_bOpenFile2)
		{
			for(i=0;i<5;i++)
			{
				if(pDoc->m_SignTotal[i]>0)
				{
					str.Format("%.2f",pDoc->m_SignRTAvg[i]);
					m_ResultList.AddItem(4+i*6,1,str,-1);
					str.Format("%.2f",pDoc->m_SignRTSqr[i]);
					m_ResultList.AddItem(4+i*6+1,1,str,-1);
					str.Format("%d",pDoc->m_SignTrue[i]);
					m_ResultList.AddItem(4+i*6+2,1,str,-1);
					str.Format("%d",pDoc->m_SignMissing[i]);
					m_ResultList.AddItem(4+i*6+3,1,str,-1);
					str.Format("%d",pDoc->m_SignCR[i]);
					m_ResultList.AddItem(4+i*6+4,1,str,-1);
					str.Format("%d",pDoc->m_SignFalse[i]);
					m_ResultList.AddItem(4+i*6+5,1,str,-1);
				}
			}
		}
		break;
	//任务6
	case 6:
        m_ResultList.AddItem(0,0,"位移误差平均值(DistanceAve)",-1);
		m_ResultList.AddItem(1,0,"位移误差标准差(DistanceSqt)",-1);
		m_ResultList.AddItem(2,0,"击中总时间(HitTimeTotal)",-1);
		m_ResultList.AddItem(3,0,"击中时间比(HitTimeRate)",-1);
		for(i=0;i<4;i++)
		{
            str.Format("方块数%d反应时间平均值(Cube%dRTAvg)",i+9,i+9);
			m_ResultList.AddItem(4+i*6,0,str,-1);
			str.Format("方块数%d反应时间标准差(Cube%dRTSqr)",i+9,i+9);
			m_ResultList.AddItem(4+i*6+1,0,str,-1);
			str.Format("方块数%d击中数(Cube%dHIT)",i+9,i+9);
			m_ResultList.AddItem(4+i*6+2,0,str,-1);
			str.Format("方块数%d漏报数(Cube%dMISS)",i+9,i+9);
			m_ResultList.AddItem(4+i*6+3,0,str,-1);
			str.Format("方块数%d正确拒斥数(Cube%dCR)",i+9,i+9);
			m_ResultList.AddItem(4+i*6+4,0,str,-1);
			str.Format("方块数%d虚报数(Cube%dFA))",i+9,i+9);
			m_ResultList.AddItem(4+i*6+5,0,str,-1);
		}

		if(pDoc->m_bOpenFile1)
		{
    		str.Format("%.2f",pDoc->m_DistanceAve);
			m_ResultList.AddItem(0,1,str,-1);
			str.Format("%.2f",pDoc->m_DistanceSqt);
			m_ResultList.AddItem(1,1,str,-1);
			str.Format("%d",pDoc->m_HitTimeTotal);
			m_ResultList.AddItem(2,1,str,-1);
			str.Format("%.2f",pDoc->m_HitTimeRate);
			m_ResultList.AddItem(3,1,str,-1);
		}
		if(pDoc->m_bOpenFile2)
		{
			for(i=0;i<4;i++)
			{
				if(pDoc->m_SignTotal[i]>0)
				{
					str.Format("%.2f",pDoc->m_SignRTAvg[i]);
					m_ResultList.AddItem(4+i*6,1,str,-1);
					str.Format("%.2f",pDoc->m_SignRTSqr[i]);
					m_ResultList.AddItem(4+i*6+1,1,str,-1);
					str.Format("%d",pDoc->m_SignTrue[i]);
					m_ResultList.AddItem(4+i*6+2,1,str,-1);
					str.Format("%d",pDoc->m_SignMissing[i]);
					m_ResultList.AddItem(4+i*6+3,1,str,-1);
					str.Format("%d",pDoc->m_SignCR[i]);
					m_ResultList.AddItem(4+i*6+4,1,str,-1);
					str.Format("%d",pDoc->m_SignFalse[i]);
					m_ResultList.AddItem(4+i*6+5,1,str,-1);
				}
			}
		}
		break;

		//任务7
	case 7:
		break;

	}	



}