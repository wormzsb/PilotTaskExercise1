#if !defined(AFX_SETTINGDLG1_H__098B2D07_C6EF_4BCB_8A34_94AE36E1689B__INCLUDED_)
#define AFX_SETTINGDLG1_H__098B2D07_C6EF_4BCB_8A34_94AE36E1689B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettingDlg1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg1 dialog

class CSettingDlg1 : public CDialog
{
// Construction
public:
	CSettingDlg1(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSettingDlg1();
// Dialog Data
	//{{AFX_DATA(CSettingDlg1)
	enum { IDD = IDD_SETTINGDLG1 };
	CComboBox	m_Track;
	CComboBox	m_Background;
	UINT	m_PauseNum;
	CString	m_AngleSpeedMax;
	CString	m_AngleSpeedMin;
	CString	m_PracTimes;
	CString	m_ExperTime;
	CString	m_PracTime;
	int		m_MoveMode;
	int		m_SpeedMode;
	int		m_Direction;
	CString	m_AccelerationMax;
	CString	m_AccelerationMin;
	CString	m_InitSpeed;
	CString	m_ExperTimes;
	CString	m_SpeedMax;
	BOOL	m_PracMode;
	BOOL	m_ExperMode;
	int		m_Pause;
	CString	m_Speed;
	CString	m_SpeedMin;
	CString	m_RotateAngleMax;
	CString	m_RotateAngleMin;
	CString	m_TaskName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingDlg1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	void Save(); 
	int m_DlgIdx;
protected:

	// Generated message map functions
	//{{AFX_MSG(CSettingDlg1)
	virtual BOOL OnInitDialog();
	afx_msg void OnPracmode();
	afx_msg void OnExpermode();
	afx_msg void OnPause0();
	afx_msg void OnPause1();
	afx_msg void OnMovemode0();
	afx_msg void OnMovemode1();
	afx_msg void OnSpeedmode0();
	afx_msg void OnSpeedmode1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	int m_iJoyMoveDirection;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGDLG1_H__098B2D07_C6EF_4BCB_8A34_94AE36E1689B__INCLUDED_)
