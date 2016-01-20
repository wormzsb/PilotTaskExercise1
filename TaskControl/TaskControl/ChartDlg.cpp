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

//绘制1条曲线
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

//绘制2条曲线
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

//绘制曲线
void CChartDlg::PlotChart()
{
	VARIANT var;
//    m_Chart.SetChartType();
	m_Chart.put_AllowSelections(FALSE);
	m_Chart.put_AllowDithering(FALSE);
    CVcPlot plot(m_Chart.get_Plot());
	CVcAxis Axis1(plot.get_Axis(VtChAxisIdY,var));
	CVcValueScale ValueScale(Axis1.get_ValueScale());
	ValueScale.put_Auto(TRUE);//不自动标注y轴刻度
//    m_Chart.GetPlot().GetAxis(1,var).GetValueScale().SetMaximum(m_ymax);//y轴最大刻度
//    m_Chart.GetPlot().GetAxis(1,var).GetValueScale().SetMinimum(m_ymin);//y轴最小刻度
    ValueScale.put_MajorDivision(5);//y轴刻度5等分
    ValueScale.put_MinorDivision(1);//每刻度一个刻度线
    CVcAxisTitle AxisTitle(Axis1.get_AxisTitle());
	switch(m_type)
	{
	case 0://位移误差随时间变化的曲线
		AxisTitle.put_Text("距离(像素)");			// Y轴名称
		break;
	case 1://角度误差随时间变化的曲线
		AxisTitle.put_Text("角度差(度)");			// Y轴名称
		break;
	case 2://目标、瞄准器速度随时间变化的曲线
		AxisTitle.put_Text("速度(像素/秒)");			// Y轴名称
		break;
	case 3://目标、瞄准器角速度随时间变化的曲线
		AxisTitle.put_Text("角速度(度/秒)");			// Y轴名称
		break;
	}
//	m_Chart.GetPlot().GetAxis(1,var).GetAxisTitle().SetText("距离(像素)");			// Y轴名称
//    m_Chart.SetRowCount(m_PointNum); //一屏显示10个采样时刻

	if(m_data2==NULL)
	{
		m_Chart.put_ShowLegend(FALSE);
		m_Chart.put_ColumnCount(1); //1条曲线
//		m_Chart.SetColumnCount(m_TrialNum); //1条曲线
	}
	else
	{
		m_Chart.put_ShowLegend(TRUE);
    	m_Chart.put_ColumnCount(2); //2条曲线
	}
    CVcSeriesCollection SeriesCollection(plot.get_SeriesCollection());
    CVcSeries Series1(SeriesCollection.get_Item(1));
    CVcPen Pen1(Series1.get_Pen());
	CVcColor Color(Pen1.get_VtColor());
	Color.Set(0, 0, 255);//线色
//    m_Chart.GetPlot().GetSeriesCollection().GetItem(1).SetLegendText("目标");//线色
//   m_Chart.GetPlot().GetSeriesCollection().GetItem(3).GetPen().GetVtColor().Set(0, 255, 0);
	Pen1.put_Width(30);//线宽
    if(m_data2!=NULL)
	{
		CVcSeries Series2(SeriesCollection.get_Item(2));
        CVcPen Pen(Series2.get_Pen());
        CVcColor Color(Pen.get_VtColor());
    	Color.Set(255, 0, 0);  
    	Pen.put_Width(30);
		Series1.put_LegendText("目标");//线色
		Series2.put_LegendText("瞄准器");//线色
	}
 //  m_Chart.GetPlot().GetSeriesCollection().GetItem(3).GetPen().SetWidth(2);
    m_Chart.put_RowCount(m_PointNum); //一屏显示10个采样时刻
	CVcAxis Axis0(plot.get_Axis(VtChAxisIdX,var));
	CVcCategoryScale CategoryScale(Axis0.get_CategoryScale());
    CategoryScale.put_Auto(FALSE);//不自动标注x轴刻度
    CategoryScale.put_DivisionsPerLabel(250);//每时刻一个标注
    CategoryScale.put_DivisionsPerTick(250);//每时刻一个刻度线
	plot.put_UniformAxis(FALSE);//每时刻一个刻度线
	CVcAxisTitle AxisTitle0(Axis0.get_AxisTitle());
    AxisTitle0.put_Text("时间(秒)");			// X轴名称
//   m_ScrLeft.SetScrollRange(0,45);
     //垂直滚动条可滚动范围(范围0－50, 每滚动1度,一屏显示5度)
//    m_ScrLeft.SetScrollPos(45-32);//垂直滚动条的当前位置
//    m_ScrBottom.SetScrollRange(0, 0);//水平滚动条的可滚动范围
//    m_ScrBottom.SetScrollPos(0);//水平滚动条的当前位置

//	float m_Data[2][1000];
    char s[10];
    UINT row = 1;
    //取数据进行显示
	//1条曲线
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
				//以t时刻做x轴的标注
				m_Chart.put_Column(1);
				sprintf_s(s, "%.2f", m_data1[i]);
				m_Chart.put_Data((LPCSTR)s);		
				row++;
			}
		}
	}
	//2条曲线
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
				//以t时刻做x轴的标注
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
		m_Chart.SetRowLabel((LPCTSTR)“");
		m_Chart.GetDataGrid().SetData(row, 1, 0, 1);
		//数据不足10个点, 对应的位置不显示
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
