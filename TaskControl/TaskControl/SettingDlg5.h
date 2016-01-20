#if !defined(AFX_SETTINGDLG5_H__EC1CF941_8DD7_4DC0_970F_512BB8029704__INCLUDED_)
#define AFX_SETTINGDLG5_H__EC1CF941_8DD7_4DC0_970F_512BB8029704__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettingDlg5.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg5 dialog

class CSettingDlg5 : public CDialog
{
// Construction
public:
	CSettingDlg5(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSettingDlg5)
	enum { IDD = IDD_SETTINGDLG5 };
	CComboBox	m_SignMemType;
	CComboBox	m_Background;
	int		m_SignMemMode;
	int		m_SignShowMode;
	BOOL	m_PracMode;
	BOOL	m_ExperMode;
	CString	m_InitSpeed;
	BOOL	m_MainTask;
	BOOL	m_SubTask;
	CString	m_ExperTimes;
	CString	m_PracTimes;
	CString	m_SignMemNum;
	CString	m_PracTime;
	CString	m_ExperTime;
	CString	m_SignShowTime;
	CString	m_TaskName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingDlg5)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	void Save(); 
	int m_DlgIdx;
protected:

	// Generated message map functions
	//{{AFX_MSG(CSettingDlg5)
	virtual BOOL OnInitDialog();
	afx_msg void OnPracmode();
	afx_msg void OnExpermode();
	afx_msg void OnMaintask();
	afx_msg void OnSubtask();
	afx_msg void OnSignmemmode0();
	afx_msg void OnSignmemmode1();
	afx_msg void OnSignshowmode0();
	afx_msg void OnSignshowmode1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	int m_iJoyMoveDirection;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGDLG5_H__EC1CF941_8DD7_4DC0_970F_512BB8029704__INCLUDED_)
