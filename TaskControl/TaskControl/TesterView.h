#if !defined(AFX_TESTERVIEW_H__6D55196E_11ED_48B0_B744_5DBF73570DC0__INCLUDED_)
#define AFX_TESTERVIEW_H__6D55196E_11ED_48B0_B744_5DBF73570DC0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TesterView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTesterView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CTesterView : public CFormView
{
public:
	CTesterView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CTesterView)

// Form Data
public:
	//{{AFX_DATA(CTesterView)
	enum { IDD = IDD_TESTERVIEW };
	CString	m_TesterNo;
	CString	m_TesterName;
	UINT	m_TesterAge;
	CString	m_TesterSex;
	UINT	m_Session;
	bool    m_bSetting;// «∑Ò±ª…Ë÷√
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTesterView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTesterView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CTesterView)
	afx_msg void OnSaveas();
	afx_msg void OnMakesure();
	afx_msg void OnChangeTesterno();
	afx_msg void OnSelchangeTestersex();
	afx_msg void OnChangeTestername();
	afx_msg void OnChangeTesterage();
	afx_msg void OnChangeSession();
	afx_msg void OnSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CButton m_btnMakeSure;
	afx_msg void OnNext();
	afx_msg void OnBnClickedButton1();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void Resize(void);
private:
	CPoint m_oldpoint;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTERVIEW_H__6D55196E_11ED_48B0_B744_5DBF73570DC0__INCLUDED_)
#include "afxwin.h"
#include "atltypes.h"
