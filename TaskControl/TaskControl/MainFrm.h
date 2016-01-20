// MainFrm.h : interface of the CMainFrame class
//


#pragma once

#include "ResultDlg.h"
#include "ProcessDlg.h"

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
    CResultDlg *m_pWSDlg;
	CProcessDlg *pDlg;
// Operations
public:
    void OnThread(CTaskControlDoc* pDoc);
// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
    void ReadSetting(CString FileName); 
	virtual ~CMainFrame();
	
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnHardAdjust();
	afx_msg void OnTesterNew();
	afx_msg void OnTesterOpen();
	afx_msg void OnSettingNew();
	afx_msg void OnSettingOpen();
	afx_msg void OnHardSetting();
	afx_msg void OnDisplayresult();
	afx_msg void OnQuit();
	afx_msg void OnStart();
	afx_msg void OnSettingNow();
	afx_msg void OnTesterNow();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnBatch();

	afx_msg LRESULT OnCloseDlg(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnUpdateData(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
	
};


