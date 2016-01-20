// ChartDlg.cpp : implementation file
//

#include "stdafx.h"
#include "taskcontrol.h"
#include "ChartDlg.h"
#include "CVcPlot.h" 
#include "CVcAxis.h" 
#include "CVcValueScale.h" 
#include "CVcSeriesCollection.h" 
#include "CVcSeries.h" 
#include "CVcPen.h" 
#include "CVcColor.h" 
#include "CVcCategoryScale.h"
#include "CVcAxisTitle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChartDlg dialog


CChartDlg::CChartDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChartDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChartDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_PointNum = 0;
	m_ymin = 0;
	m_ymax = 0;
	m_pView = NULL;
	m_Time = NULL;
	m_data1 = NULL;
	m_data2 = NULL;
}

CChartDlg::CChartDlg(CView* pView) // modeless constructor
{
	m_pView = pView;
	m_Time = NULL;
	m_data1 = NULL;
	m_data2 = NULL;
}

//����1������
void CChartDlg::Plot(int type, UINT m, int min, int max, float *t, float *d, int trial, int *s)
{
	m_PointNum = m;
	m_Time = t;
	m_data1 = d;
	m_data2 = NULL;
	m_ymin = min;
	m_ymax = max;
	m_TrialNum = trial;
	m_StartPoint = s;
	m_type = type;
	PlotChart();
}

//����2������
void CChartDlg::Plot(int type, UINT m, int min, int max, float *t, float *d1, float *d2, int trial, int *s)
{
	m_PointNum = m;
    m_Time = t;
	m_data1 = d1;
	m_data2 = d2;
	m_ymin = min;
	m_ymax = max;
	m_TrialNum = trial;
	m_StartPoint = s;
	m_type = type;
	PlotChart();
}

void CChartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChartDlg)
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_MSCHART1, m_Chart);
}


BEGIN_MESSAGE_MAP(CChartDlg, CDialog)
	//{{AFX_MSG_MAP(CChartDlg)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChartDlg message handlers

BOOL CChartDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//��������
void CChartDlg::PlotChart()
{
	VARIANT var;
//    m_Chart.SetChartType();
	m_Chart.put_AllowSelections(FALSE);
	m_Chart.put_AllowDithering(FALSE);
    CVcPlot plot(m_Chart.get_Plot());
	CVcAxis Axis1(plot.get_Axis(VtChAxisIdY,var));
	CVcValueScale ValueScale(Axis1.get_ValueScale());
	ValueScale.put_Auto(TRUE);//���Զ���עy��̶�
//    m_Chart.GetPlot().GetAxis(1,var).GetValueScale().SetMaximum(m_ymax);//y�����̶�
//    m_Chart.GetPlot().GetAxis(1,var).GetValueScale().SetMinimum(m_ymin);//y����С�̶�
    ValueScale.put_MajorDivision(5);//y��̶�5�ȷ�
    ValueScale.put_MinorDivision(1);//ÿ�̶�һ���̶���
    CVcAxisTitle AxisTitle(Axis1.get_AxisTitle());
	switch(m_type)
	{
	case 0://λ�������ʱ��仯������
		AxisTitle.put_Text("����(����)");			// Y������
		break;
	case 1://�Ƕ������ʱ��仯������
		AxisTitle.put_Text("�ǶȲ�(��)");			// Y������
		break;
	case 2://Ŀ�ꡢ��׼���ٶ���ʱ��仯������
		AxisTitle.put_Text("�ٶ�(����/��)");			// Y������
		break;
	case 3://Ŀ�ꡢ��׼�����ٶ���ʱ��仯������
		AxisTitle.put_Text("���ٶ�(��/��)");			// Y������
		break;
	}
//	m_Chart.GetPlot().GetAxis(1,var).GetAxisTitle().SetText("����(����)");			// Y������
//    m_Chart.SetRowCount(m_PointNum); //һ����ʾ10������ʱ��

	if(m_data2==NULL)
	{
		m_Chart.put_ShowLegend(FALSE);
		m_Chart.put_ColumnCount(1); //1������
//		m_Chart.SetColumnCount(m_TrialNum); //1������
	}
	else
	{
		m_Chart.put_ShowLegend(TRUE);
    	m_Chart.put_ColumnCount(2); //2������
	}
    CVcSeriesCollection SeriesCollection(plot.get_SeriesCollection());
    CVcSeries Series1(SeriesCollection.get_Item(1));
    CVcPen Pen1(Series1.get_Pen());
	CVcColor Color(Pen1.get_VtColor());
	Color.Set(0, 0, 255);//��ɫ
//    m_Chart.GetPlot().GetSeriesCollection().GetItem(1).SetLegendText("Ŀ��");//��ɫ
//   m_Chart.GetPlot().GetSeriesCollection().GetItem(3).GetPen().GetVtColor().Set(0, 255, 0);
	Pen1.put_Width(30);//�߿�
    if(m_data2!=NULL)
	{
		CVcSeries Series2(SeriesCollection.get_Item(2));
        CVcPen Pen(Series2.get_Pen());
        CVcColor Color(Pen.get_VtColor());
    	Color.Set(255, 0, 0);  
    	Pen.put_Width(30);
		Series1.put_LegendText("Ŀ��");//��ɫ
		Series2.put_LegendText("��׼��");//��ɫ
	}
 //  m_Chart.GetPlot().GetSeriesCollection().GetItem(3).GetPen().SetWidth(2);
    m_Chart.put_RowCount(m_PointNum); //һ����ʾ10������ʱ��
	CVcAxis Axis0(plot.get_Axis(VtChAxisIdX,var));
	CVcCategoryScale CategoryScale(Axis0.get_CategoryScale());
    CategoryScale.put_Auto(FALSE);//���Զ���עx��̶�
    CategoryScale.put_DivisionsPerLabel(250);//ÿʱ��һ����ע
    CategoryScale.put_DivisionsPerTick(250);//ÿʱ��һ���̶���
	plot.put_UniformAxis(FALSE);//ÿʱ��һ���̶���
	CVcAxisTitle AxisTitle0(Axis0.get_AxisTitle());
    AxisTitle0.put_Text("ʱ��(��)");			// X������
//   m_ScrLeft.SetScrollRange(0,45);
     //��ֱ�������ɹ�����Χ(��Χ0��50, ÿ����1��,һ����ʾ5��)
//    m_ScrLeft.SetScrollPos(45-32);//��ֱ�������ĵ�ǰλ��
//    m_ScrBottom.SetScrollRange(0, 0);//ˮƽ�������Ŀɹ�����Χ
//    m_ScrBottom.SetScrollPos(0);//ˮƽ�������ĵ�ǰλ��

//	float m_Data[2][1000];
    char s[10];
    UINT row = 1;
    //ȡ���ݽ�����ʾ
	//1������
    if(m_data2==NULL)
	{
		int j = 0;
		int l = 0;
		int i;
   		for(j=0;j<m_TrialNum;j++)
		{
		//	row = row+(row-1)%250;
			for(i=m_StartPoint[j];i<m_StartPoint[j+1];i++)
			{
				m_Chart.put_Row(row);
				sprintf_s(s, "%d", (int)m_Time[i]);
				m_Chart.put_RowLabel(s);
				//m_Chart.SetData((LPCSTR)s);
				//��tʱ����x��ı�ע
				m_Chart.put_Column(1);
				sprintf_s(s, "%.2f", m_data1[i]);
				m_Chart.put_Data((LPCSTR)s);		
				row++;
			}
		}
	}
	//2������
	else
	{
		int j = 0;
		int l = 0;
		int i;
		for(j=0;j<m_TrialNum;j++)
		{
			for(i=m_StartPoint[j];i<m_StartPoint[j+1];i++)
			{
				m_Chart.put_Row(row);
				sprintf_s(s, "%d", (int)m_Time[i]);
				m_Chart.put_RowLabel(s);
				//��tʱ����x��ı�ע
				m_Chart.put_Column(1);
				sprintf_s(s, "%.2f", m_data1[i]);
				m_Chart.put_Data((LPCSTR)s);
				m_Chart.put_Column(2);
				sprintf_s(s, "%.2f", m_data2[i]);
				m_Chart.put_Data((LPCSTR)s);
				row++;
			}
		}
	}
/*    while ((row <= 10))
	{
		m_Chart.SetRow(row);
		m_Chart.SetRowLabel((LPCTSTR)��");
		m_Chart.GetDataGrid().SetData(row, 1, 0, 1);
		//���ݲ���10����, ��Ӧ��λ�ò���ʾ
		m_Chart.GetDataGrid().SetData(row, 2, 0, 1);
		m_Chart.GetDataGrid().SetData(row, 3, 0, 1);
		row++;
    }*/
    m_Chart.Refresh();
    m_Chart.EditCopy();
}

void CChartDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	RECT wnRect;
	if(m_Chart.GetSafeHwnd()!=NULL)
	{
		m_Chart.GetWindowRect(&wnRect);
		ScreenToClient(&wnRect);
		m_Chart.MoveWindow(wnRect.left,wnRect.top,cx-20,cy-13);
	}		
}


HBRUSH CChartDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_EDIT){
		pDC->SetBkColor(RGB(255,255,255));
	}
	return hbr;
}
