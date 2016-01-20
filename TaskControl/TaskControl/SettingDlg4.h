#if !defined(AFX_SETTINGDLG4_H__7DA2DF27_2CA6_467F_A9D0_E4610323146A__INCLUDED_)
#define AFX_SETTINGDLG4_H__7DA2DF27_2CA6_467F_A9D0_E4610323146A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettingDlg4.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg4 dialog

class CSettingDlg4 : public CDialog
{
// Construction
public:
	CSettingDlg4(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSettingDlg4)
	enum { IDD = IDD_SETTINGDLG4 };
	CComboBox	m_Background;
	int		m_TouchOrder;
	BOOL	m_PracMode;
	BOOL	m_ExperMode;
	CString	m_PracTimes;
	CString	m_ExperTimes;
	CString	m_TaskName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingDlg4)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	void Save(); 
	int m_DlgIdx;
protected:

	// Generated message map functions
	//{{AFX_MSG(CSettingDlg4)
	virtual BOOL OnInitDialog();
	afx_msg void OnPracmode();
	afx_msg void OnExpermode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGDLG4_H__7DA2DF27_2CA6_467F_A9D0_E4610323146A__INCLUDED_)
