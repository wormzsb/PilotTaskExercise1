#include "afxwin.h"
#if !defined(AFX_SETTINGDLG2_H__4DCD8289_A85C_4775_975C_E515603536BA__INCLUDED_)
#define AFX_SETTINGDLG2_H__4DCD8289_A85C_4775_975C_E515603536BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettingDlg2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg2 dialog

class CSettingDlg2 : public CDialog
{
// Construction
public:
	CSettingDlg2(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSettingDlg2)
	enum { IDD = IDD_SETTINGDLG2 };
	CComboBox	m_HoldTimeNumCom;
	CComboBox	m_Background;
	CString	m_PracTimes;
	int		m_Direction;
	CString	m_ExperTimes;
	BOOL	m_PracMode;
	BOOL	m_ExperMode;
	CString	m_InitSpeed;
	CString	m_HoldTime1;
	CString	m_HoldTime10;
	CString	m_HoldTime11;
	CString	m_HoldTime12;
	CString	m_HoldTime2;
	CString	m_HoldTime3;
	CString	m_HoldTime4;
	CString	m_HoldTime5;
	CString	m_HoldTime6;
	CString	m_HoldTime7;
	CString	m_HoldTime8;
	CString	m_HoldTime9;
	BOOL	m_MainTask;
	BOOL	m_SubTask;
	CString	m_PracTime;
	CString	m_ExperTime;
	CString	m_TaskName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingDlg2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	void Save(); 
	int m_DlgIdx;
protected:

	// Generated message map functions
	//{{AFX_MSG(CSettingDlg2)
	virtual BOOL OnInitDialog();
	afx_msg void OnExpermode();
	afx_msg void OnPracmode();
	afx_msg void OnSelchangeHoldtimenum();
	afx_msg void OnMaintask();
	afx_msg void OnSubtask();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	int m_iJoyMoveDirection;
	int m_iSubTaskInterval;
	BOOL m_bSpeedMode;
	float m_fSpeed;
	float m_fInitSpeed;
	float m_fSpeedMin;
	float m_fSpeedMax;
	float m_fAccMin;
	float m_fAccMax;
	CComboBox m_ccbTrack;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedSpeedmode0();
	afx_msg void OnBnClickedSpeedmode1();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGDLG2_H__4DCD8289_A85C_4775_975C_E515603536BA__INCLUDED_)
