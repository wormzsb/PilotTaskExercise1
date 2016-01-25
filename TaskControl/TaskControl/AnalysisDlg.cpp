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

//��ʾ���ݷ����Ľ��
void CAnalysisDlg::DisplayResult()
{
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
    CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();

	int i,j;

	//�����б�ؼ�����
	CString cs;
    m_ResultList.SetExtendedStyle(LVS_EX_HEADERDRAGDROP|LVS_EX_FULLROWSELECT
		|LVS_EX_GRIDLINES|LVS_EX_SUBITEMIMAGES);
	m_ResultList.SetWindowPos(&wndBottom,10,10,220,220,SWP_SHOWWINDOW|SWP_NOMOVE|SWP_NOSIZE);

	CString str;

	//��ӱ�ͷ
	m_ResultList.DeleteAllItems();            //ɾ���б�����������(��)
    while (m_ResultList.DeleteColumn(0));     //ɾ���б���������
	m_ResultList.AddColumn(_T("ָ��"),1,300,LVCFMT_LEFT);
	m_ResultList.AddColumn(_T("ָ��ֵ"),2,300,LVCFMT_LEFT);
	
	switch (pDoc->m_TaskNo)
	{
	//����1
	case 1:
		m_ResultList.AddItem(0,0,"λ�����ƽ��ֵ(DistanceAve)",-1);
		m_ResultList.AddItem(1,0,"λ������׼��(DistanceSqt)",-1);		
		m_ResultList.AddItem(2,0,"�Ƕ����ƽ��ֵ(RotateErrorAve)",-1);
        m_ResultList.AddItem(3,0,"�Ƕ�����׼��(RotateErrorSqt)",-1);
		m_ResultList.AddItem(4,0,"������ʱ��(HitTimeTotal)",-1);
		m_ResultList.AddItem(5,0,"����ʱ���(HitTimeRate)",-1);	
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
	//����2
	case 2:
		m_ResultList.AddItem(0,0,"λ�����ƽ��ֵ(DistanceAve)",-1);     
        m_ResultList.AddItem(1,0,"λ������׼��(DistanceSqt)",-1);
		m_ResultList.AddItem(2,0,"������ʱ��(HitTimeTotal)",-1);
		m_ResultList.AddItem(3,0,"����ʱ���(HitTimeRate)",-1);	
		for(i=0;i<12;i++)
		{
			str.Format("����ʱ��%d�����(HoldTimeRate%d)",i+1,i+1);
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
				str.Format("δ����");
				m_ResultList.AddItem(i + 4, 1, str, -1);
			}
		}
		break;
	//����3
	case 3:
		if(pDoc->m_MainTaskMode == 0)//����������
		{
			m_ResultList.AddItem(0,0,"λ�����ƽ��ֵ(DistanceAve)",-1);
			m_ResultList.AddItem(1,0,"λ������׼��(DistanceSqt)",-1);
			m_ResultList.AddItem(2,0,"������ʱ��(HitTimeTotal)",-1);
			m_ResultList.AddItem(3,0,"����ʱ���(HitTimeRate)",-1);
			j=4;
		}
		else//����
		{
			m_ResultList.AddItem(0,0,"��ȷ������(TrueCode)",-1);
			m_ResultList.AddItem(1,0,"���������(FalseCode)",-1);
			m_ResultList.AddItem(2,0,"��ȷ������(TrueCodeRate)",-1);
			m_ResultList.AddItem(3,0,"���������(FalseCodeRate)",-1);
			m_ResultList.AddItem(4,0,"���뷴Ӧʱƽ��ֵ(CodeRTAvg)",-1);
			m_ResultList.AddItem(5,0,"���뷴Ӧʱ��׼��(CodeRTSqr)",-1);
			j=6;
		}
		if(pDoc->m_Setting3[0].m_EventMode ==0)//������
		{
			m_ResultList.AddItem(j,0,"������(HIT)",-1);
			m_ResultList.AddItem(j+1,0,"©����(MISS)",-1);
			m_ResultList.AddItem(j+2,0,"��ȷ�ܳ���(CR)",-1);
			m_ResultList.AddItem(j+3,0,"�鱨��(FA)",-1);
			m_ResultList.AddItem(j+4,0,"ͻ���¼���Ӧʱ��ƽ��ֵ(RTAvg)",-1);
			m_ResultList.AddItem(j+5,0,"ͻ���¼���Ӧʱ���׼��(RTSqr)",-1);
		}
		else//ѡ������
		{
			m_ResultList.AddItem(j,0,"������(HIT)",-1);
			m_ResultList.AddItem(j+1,0,"©����(MISS)",-1);
			m_ResultList.AddItem(j+2,0,"��ȷ�ܳ���(CR)",-1);
			m_ResultList.AddItem(j+3,0,"�鱨��(FA)",-1);
			m_ResultList.AddItem(j+4,0,"���¼���Ӧʱƽ��ֵ(m_RTAvg)",-1);
			m_ResultList.AddItem(j+5,0,"���¼���Ӧʱ��׼��(m_RTSqr)",-1);
		}

		if(pDoc->m_bOpenFile1)
		{
			if(pDoc->m_MainTaskMode == 0)//����������
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
			else//����
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
			if(pDoc->m_Setting3[0].m_EventMode ==0)//������
			{
				str.Format("%d",pDoc->m_TrueCount);//������HIT
				m_ResultList.AddItem(j,1,str,-1);
				str.Format("%d",pDoc->m_MissingCount);//©����MISS
				m_ResultList.AddItem(j+1,1,str,-1);
//				str.Format("%d",pDoc->m_CRCount);//��ȷ�ܳ���CR������
				m_ResultList.AddItem(j+2,1,"",-1);
				//str.Format("%d",pDoc->m_FalseCount);//�鱨��FA������
				m_ResultList.AddItem(j+3,1,"",-1);
				str.Format("%.2f",pDoc->m_RTAvg);//ͻ���¼���ӳʱ��ƽ��ֵRTAvg
				m_ResultList.AddItem(j+4,1,str,-1);
				str.Format("%.2f",pDoc->m_RTSqr);//ͻ���¼���ӳʱ���׼��RTSqr
				m_ResultList.AddItem(j+5,1,str,-1);
			}
			else//ѡ������
			{
				str.Format("%d",pDoc->m_TrueCount);//ע��ͬ������
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
	//����4
	case 4:
		for(i=0;i<3;i++)
		{
			for(j=0;j<6;j++)
			{
				str.Format("����%dĿ��%dƽ����Ӧʱ��(RTAved%dt%d)",i+1,j+1,i+1,j+1);
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
	//����5
	case 5:
		m_ResultList.AddItem(0,0,"λ�����ƽ��ֵ(DistanceAve)",-1);
		m_ResultList.AddItem(1,0,"λ������׼��(DistanceSqt)",-1);
		m_ResultList.AddItem(2,0,"������ʱ��(HitTimeTotal)",-1);
		m_ResultList.AddItem(3,0,"����ʱ���(HitTimeRate)",-1);
		for(i=0;i<5;i++)
		{
			str.Format("������Ŀ%d��Ӧʱƽ��ֵ(Num%dRTAvg)",i+4,i+4);
			m_ResultList.AddItem(4+i*6,0,str,-1);
			str.Format("������Ŀ%d��Ӧʱ��׼��(Num%dRTSqr)",i+4,i+4);
			m_ResultList.AddItem(4+i*6+1,0,str,-1);
			str.Format("������Ŀ%d������(Num%dHIT)",i+4,i+4);
			m_ResultList.AddItem(4+i*6+2,0,str,-1);
			str.Format("������Ŀ%d©����(Num%dMISS)",i+4,i+4);
			m_ResultList.AddItem(4+i*6+3,0,str,-1);
			str.Format("������Ŀ%d��ȷ�ܳ���(Num%dCR)",i+4,i+4);
			m_ResultList.AddItem(4+i*6+4,0,str,-1);
			str.Format("������Ŀ%d�鱨��(Num%dFA))",i+4,i+4);
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
	//����6
	case 6:
        m_ResultList.AddItem(0,0,"λ�����ƽ��ֵ(DistanceAve)",-1);
		m_ResultList.AddItem(1,0,"λ������׼��(DistanceSqt)",-1);
		m_ResultList.AddItem(2,0,"������ʱ��(HitTimeTotal)",-1);
		m_ResultList.AddItem(3,0,"����ʱ���(HitTimeRate)",-1);
		for(i=0;i<4;i++)
		{
            str.Format("������%d��Ӧʱ��ƽ��ֵ(Cube%dRTAvg)",i+9,i+9);
			m_ResultList.AddItem(4+i*6,0,str,-1);
			str.Format("������%d��Ӧʱ���׼��(Cube%dRTSqr)",i+9,i+9);
			m_ResultList.AddItem(4+i*6+1,0,str,-1);
			str.Format("������%d������(Cube%dHIT)",i+9,i+9);
			m_ResultList.AddItem(4+i*6+2,0,str,-1);
			str.Format("������%d©����(Cube%dMISS)",i+9,i+9);
			m_ResultList.AddItem(4+i*6+3,0,str,-1);
			str.Format("������%d��ȷ�ܳ���(Cube%dCR)",i+9,i+9);
			m_ResultList.AddItem(4+i*6+4,0,str,-1);
			str.Format("������%d�鱨��(Cube%dFA))",i+9,i+9);
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

		//����7
	case 7:
		break;

	}	



}