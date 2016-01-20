// TaskControlView.h : interface of the CTaskControlView class
//


#pragma once


class CTaskControlView : public CFormView
{
protected: // create from serialization only
	CTaskControlView();
	DECLARE_DYNCREATE(CTaskControlView)

public:
	enum{ IDD = IDD_TASKCONTROL_FORM };

// Attributes
public:
	CTaskControlDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CTaskControlView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

#ifndef _DEBUG  // debug version in TaskControlView.cpp
inline CTaskControlDoc* CTaskControlView::GetDocument() const
   { return reinterpret_cast<CTaskControlDoc*>(m_pDocument); }
#endif

