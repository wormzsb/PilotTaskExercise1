#include "afxwin.h"
#if !defined(AFX_SETTINGDLG6_H__667AB463_B1AA_4A3D_9592_6862479ED36C__INCLUDED_)
#define AFX_SETTINGDLG6_H__667AB463_B1AA_4A3D_9592_6862479ED36C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettingDlg6.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg6 dialog

class CSettingDlg6 : public CDialog
{
// Construction
public:
	CSettingDlg6(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSettingDlg6)
	enum { IDD = IDD_SETTINGDLG6 };
	CComboBox	m_Background;
	int		m_MemTaskMode;
	BOOL	m_PracMode;
	BOOL	m_ExperMode;
	float	m_fSpeed;
	BOOL	m_MainTask;
	BOOL	m_SubTask;
	CString	m_PracTimes;
	CString	m_ExperTimes;
	CString	m_ExperTime;
	CString	m_PracTime;
	BOOL	m_CubeNum1;
	BOOL	m_CubeNum2;
	BOOL	m_CubeNum3;
	BOOL	m_CubeNum4;
	int		m_Prototype;
	int		m_RefAxis;
	CString	m_TaskName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingDlg6)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
    
// Implementation
public:
	void Save(); 
	int m_DlgIdx;
protected:

	// Generated message map functions
	//{{AFX_MSG(CSettingDlg6)
	virtual BOOL OnInitDialog();
	afx_msg void OnMaintask();
	afx_msg void OnSubtask();
	afx_msg void OnPracmode();
	afx_msg void OnExpermode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	int m_iJoyMoveDirection;

	afx_msg void OnBnClickedJoyMovePos();
	int m_iSubTaskInterval;
	int m_iPresentTime;
	int m_iReactTime;
	afx_msg void OnStnClickedRefaxisstatic();
	BOOL m_iDirection;
	BOOL m_bSpeedMode;
	float m_fInitSpeed;
	float m_fSpeedMin;
	float m_fSpeedMax;
	float m_fAccMin;
	float m_fAccMax;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedSpeedmode0();
	afx_msg void OnBnClickedSpeedmode1();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGDLG6_H__667AB463_B1AA_4A3D_9592_6862479ED36C__INCLUDED_)
