#if !defined(AFX_LISTDLG_H__8BECEF6C_EE37_44D4_BACA_994C5D58D51E__INCLUDED_)
#define AFX_LISTDLG_H__8BECEF6C_EE37_44D4_BACA_994C5D58D51E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListDlg.h : header file
//
#include "DataList.h"
#include "TaskControlDoc.h"
/////////////////////////////////////////////////////////////////////////////
// CListDlg dialog

class CListDlg : public CDialog
{
// Construction
public:
	CListDlg(CWnd* pParent = NULL);   // standard constructor
    UINT m_MemNum;

// Dialog Data
	//{{AFX_DATA(CListDlg)
	enum { IDD = IDD_LISTDLG };
	CDataList	m_ResultList;
	CDataList	m_ResultList2;
	CTabCtrl	m_TabCtrl;
	//}}AFX_DATA
	BOOL AddHeadT1();
	BOOL AddHeadT2Trace();
	BOOL AddHeadT2Hold();
    BOOL AddHeadT3Trace();
    BOOL AddHeadT3Code();
    BOOL AddHeadT3Event();
	BOOL AddHeadT4();
	BOOL AddHeadT5Trace();
    BOOL AddHeadT5Sign();
	BOOL AddHeadT6Trace();
	BOOL AddHeadT6Judge();
	BOOL AddHeadT6Memory();

	BOOL AddHead();



	BOOL AddT1Item(int i);
	BOOL AddT2TraceItem(int i);
	BOOL AddT2HoldItem(int i);
    BOOL AddT3TraceItem(int i);
    BOOL AddT3CodeItem(int i);
    BOOL AddT3EventItem(int i);
	BOOL AddT4Item(int i);
	BOOL AddT5TraceItem(int i);
    BOOL AddT5SignItem(int i);
	BOOL AddT6TraceItem(int i);
	BOOL AddT6JudgeItem(int i);
	BOOL AddT6MemoryItem(int i);
	BOOL AddT7Item(int i);

	BOOL AddT8Item(int row);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CListDlg)
	afx_msg void OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	CString getCString(double x);
	CString getCString(int x);
	CString getCString(LONGLONG x);
	CString getCString(string x);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTDLG_H__8BECEF6C_EE37_44D4_BACA_994C5D58D51E__INCLUDED_)
