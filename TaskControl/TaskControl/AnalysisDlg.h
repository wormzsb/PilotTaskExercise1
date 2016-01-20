#if !defined(AFX_ANALYSISDLG_H__B205DBCA_E77B_4DAD_91F1_20C05D425D58__INCLUDED_)
#define AFX_ANALYSISDLG_H__B205DBCA_E77B_4DAD_91F1_20C05D425D58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AnalysisDlg.h : header file
//
#include "DataList.h"
/////////////////////////////////////////////////////////////////////////////
// CAnalysisDlg dialog

class CAnalysisDlg : public CDialog
{
// Construction
public:
	CAnalysisDlg(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CAnalysisDlg)
	enum { IDD = IDD_ANALYSISDLG };
	CDataList	m_ResultList;
	//}}AFX_DATA
    void DisplayResult();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnalysisDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAnalysisDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANALYSISDLG_H__B205DBCA_E77B_4DAD_91F1_20C05D425D58__INCLUDED_)
