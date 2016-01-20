#if !defined(AFX_RESULTDLG_H__7E6C5495_45B2_43C6_B3D1_8446BF9D8FD8__INCLUDED_)
#define AFX_RESULTDLG_H__7E6C5495_45B2_43C6_B3D1_8446BF9D8FD8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ResultDlg.h : header file
//
#include "ListDlg.h"
#include "ChartDlg.h"
#include "AnalysisDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CResultDlg dialog

class CResultDlg : public CDialog
{
// Construction
private:
	CFrameWnd* m_pMainFrm;
public:
	CResultDlg(CWnd* pParent = NULL);   // standard constructor
    BOOL Create();
	CResultDlg(CFrameWnd* pMainFrm);

	void AddPages();
	CDialog* GetDialog(const int id);
	~CResultDlg();
	void ClosePages();
	void SetCurDlg(const int id);
// Dialog Data
	//{{AFX_DATA(CResultDlg)
	enum { IDD = IDD_RESULTDLG };
	//}}AFX_DATA
    void DataChart(short PlotNo);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResultDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	CListDlg m_ListDlg;
	CChartDlg m_ChartDlg;
    CAnalysisDlg m_AnalysisDlg;

	CPtrArray pPages;
	CWordArray csIds;
	int iCurIdx;
	// Generated message map functions
	//{{AFX_MSG(CResultDlg)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnResultList();
	afx_msg void OnAnalysis();
	afx_msg void OnChartDistanceerror();
	afx_msg void OnChartAngleerror();
	afx_msg void OnChartObjspeed();
	afx_msg void OnChartObjanglespeed();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESULTDLG_H__7E6C5495_45B2_43C6_B3D1_8446BF9D8FD8__INCLUDED_)
