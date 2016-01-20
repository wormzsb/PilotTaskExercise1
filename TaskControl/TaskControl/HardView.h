#if !defined(AFX_HARDVIEW_H__1664F678_7933_4FDD_8A59_9FD226D9D37E__INCLUDED_)
#define AFX_HARDVIEW_H__1664F678_7933_4FDD_8A59_9FD226D9D37E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HardView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHardView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CHardView : public CFormView
{
public:
	CHardView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CHardView)

// Form Data
public:
	//{{AFX_DATA(CHardView)
	enum { IDD = IDD_HARDVIEW };
	CString	m_JoySpeedMax;
	CString	m_DistanceError;
	CString	m_AngleError;
	CString	m_KnobSensitive;
	bool	m_bSetting;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHardView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CHardView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CHardView)
	afx_msg void OnSave();
	afx_msg void OnSaveas();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CButton m_btnSave;
	afx_msg void OnEnChangeJoyspeedmax();
	afx_msg void OnEnChangeSensitive();
	afx_msg void OnEnChangeDistanceerror();
	afx_msg void OnEnChangeAngleerror();
	afx_msg void OnLast();
	afx_msg void OnBegain();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HARDVIEW_H__1664F678_7933_4FDD_8A59_9FD226D9D37E__INCLUDED_)
#include "afxwin.h"
