#include "afxwin.h"
#if !defined(AFX_SETTINGDLG3_H__563393C5_A01E_4A60_AC02_E0A35F8D3225__INCLUDED_)
#define AFX_SETTINGDLG3_H__563393C5_A01E_4A60_AC02_E0A35F8D3225__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettingDlg3.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg3 dialog

class CSettingDlg3 : public CDialog
{
// Construction
public:
	CSettingDlg3(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSettingDlg3)
	enum { IDD = IDD_SETTINGDLG3 };
	CComboBox	m_Background;
	int		m_CodePairMode;
	BOOL	m_PracMode;
	BOOL	m_ExperMode;
	float	m_fInitSpeed;
	int		m_EventMode;
	int		m_DisplayMode;
	BOOL	m_MainTask;
	BOOL	m_SubTask;
	CString	m_PracTime;
	CString	m_ExperTime;
	CString	m_ExperTimes;
	CString	m_PracTimes;
	CString	m_CodePairNum;
	int		m_MainTaskMode;
	int		m_EventFrequency;
	CString	m_TaskName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingDlg3)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	void Save(); 
	int m_DlgIdx;
protected:

	// Generated message map functions
	//{{AFX_MSG(CSettingDlg3)
	virtual BOOL OnInitDialog();
	afx_msg void OnPracmode();
	afx_msg void OnExpermode();
	afx_msg void OnMaintask();
	afx_msg void OnSubtask();
	afx_msg void OnCodepairmode0();
	afx_msg void OnCodepairmode1();
	afx_msg void OnMaintaskmode0();
	afx_msg void OnMaintaskmode1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	int m_iJoyMoveDirection;
	BOOL m_bLeftTop;
	BOOL m_bRightTop;
	BOOL m_bRightBottom;
	BOOL m_bLeftBottom;
	afx_msg void OnBnClickedDisplaymode1();
	BOOL m_bDirection;
	BOOL m_bSpeedMode;
	float m_fSpeed;
	float m_fSpeedMin;
	float m_fSpeedMax;
	float m_fAccMin;
	float m_fAccMax;
	CComboBox m_ccbTrack;
	int m_iPlane;
	int m_iHelicopter;
	afx_msg void OnEnChangePractime3();
	afx_msg void OnEnChangePractime4();
	int m_iExpTimes;
	int m_iPresentTime;
	int m_iReactTime;
	afx_msg void OnEnChangePractime5();
	int m_iInterMin;
	int m_iInterMax;
	afx_msg void OnEnChangeTaskname();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedSpeedmode0();
	afx_msg void OnBnClickedSpeedmode1();
//	afx_msg void OnBnHotItemChangeEventmode0(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedEventmode0();
	afx_msg void OnBnClickedEventmode1();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGDLG3_H__563393C5_A01E_4A60_AC02_E0A35F8D3225__INCLUDED_)
