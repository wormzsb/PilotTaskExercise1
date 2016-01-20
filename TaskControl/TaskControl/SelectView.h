#if !defined(AFX_SELECTVIEW_H__F924ECA5_A28A_42EC_8DD9_9863DA956A24__INCLUDED_)
#define AFX_SELECTVIEW_H__F924ECA5_A28A_42EC_8DD9_9863DA956A24__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectView.h : header file
//
#include "TaskControlDoc.h"
//#include <d3d9.h>
//#include <d3dx9.h>
/////////////////////////////////////////////////////////////////////////////
// CSelectView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CSelectView : public CFormView
{
public:
	CSelectView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSelectView)
//    LPDIRECT3D9 ppD3D; 
//	LPDIRECT3DDEVICE9 ppDevice;
// Form Data
public:
	//{{AFX_DATA(CSelectView)
	enum { IDD = IDD_SELECTVIEW };
	CListBox	m_TaskList;
	CListBox	m_SelectedList;
	bool		m_bSetting;
	//}}AFX_DATA

// Attributes
public:
	CTaskControlDoc* GetDocument();
//	short m_TaskSig[6];
//	CSettingDlg1 dlg0;
//	CSettingDlg2 dlg1;	
//	CSettingDlg3 dlg2;
//	CSettingDlg4 dlg3;
//	CSettingDlg5 dlg4;
//	CSettingDlg6 dlg5;
//	CString m_TaskExe[6];
//    short m_TaskOrder[6];
	BOOL m_TaskSet[50];
//	short m_TaskCount;
// Operations
public:
    void SaveSetting(CString FileName);
//	void render();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSelectView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CSelectView)
	afx_msg void OnMovedown();
	afx_msg void OnMoveup();
	afx_msg void OnSelect();
	afx_msg void OnRevert();
	afx_msg void OnSetting();
	afx_msg void OnViewsetting();
	afx_msg void OnSaveassetting();
	afx_msg void OnMakesure();
	afx_msg void OnSavesetting();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDblclkList2();
	afx_msg void OnLast();
	afx_msg void OnNext();
	afx_msg void OnBnClickedButton1();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

#ifndef _DEBUG  // debug version in SelectView.cpp
inline CTaskControlDoc* CSelectView::GetDocument()
   { return (CTaskControlDoc*)m_pDocument; }
#endif
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTVIEW_H__F924ECA5_A28A_42EC_8DD9_9863DA956A24__INCLUDED_)
