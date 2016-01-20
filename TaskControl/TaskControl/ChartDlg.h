#if !defined(AFX_CHARTDLG_H__ED96C035_5A74_4414_8D01_869878803488__INCLUDED_)
#define AFX_CHARTDLG_H__ED96C035_5A74_4414_8D01_869878803488__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChartDlg.h : header file
//

#include "mschart1.h"
/////////////////////////////////////////////////////////////////////////////
// CChartDlg dialog

class CChartDlg : public CDialog
{
// Construction
private:
	CView* m_pView;
public:
	CChartDlg(CWnd* pParent = NULL);   // standard constructor
    void Plot(int type, UINT m, int min, int max, float *t, float *d, int trial, int *s); 
	void Plot(int type, UINT m, int min, int max, float *t, float *d1, float *d2, int trial, int *s);
	void PlotChart();
	CChartDlg(CView* pView);

	UINT m_PointNum; 
	float *m_Time;
	float *m_data1;
	float *m_data2;
	int m_ymin;
	int m_ymax;
	int *m_StartPoint;
	int m_TrialNum;
	int m_type;
// Dialog Data
	//{{AFX_DATA(CChartDlg)
	enum { IDD = IDD_CHARTDLG };

	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChartDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChartDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CMschart1 m_Chart;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHARTDLG_H__ED96C035_5A74_4414_8D01_869878803488__INCLUDED_)
