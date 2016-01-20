#if !defined(AFX_SETTINGDLG_H__858046F1_1092_4E93_8E06_F19E982E1C19__INCLUDED_)
#define AFX_SETTINGDLG_H__858046F1_1092_4E93_8E06_F19E982E1C19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettingDlg.h : header file
//

#include "SettingDlg1.h"
#include "SettingDlg2.h"
#include "SettingDlg3.h"
#include "SettingDlg4.h"
#include "SettingDlg5.h"
#include "SettingDlg6.h"
#include "SettingDlg7.h"
/////////////////////////////////////////////////////////////////////////////
// CSettingDlg dialog
class CSettingDlg : public CDialog
{
// Construction
public:
	CSettingDlg(CWnd* pParent = NULL);   // standard constructor
	void AddPages();
	CDialog* GetDialog(const int id);
	~CSettingDlg();
	void ClosePages();
	void SetCurDlg(const int id);
	int m_CurItem;
    int	m_MainTaskMode;
	int	m_MemTaskMode;
// Dialog Data
	//{{AFX_DATA(CSettingDlg)
	enum { IDD = IDD_SETTINGDLG };
	CTabCtrl	m_TabCtrl;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    CSettingDlg1 *m_SettingDlg1;
	CSettingDlg2 *m_SettingDlg2;
	CSettingDlg3 *m_SettingDlg3;
	CSettingDlg4 *m_SettingDlg4;
	CSettingDlg5 *m_SettingDlg5; 
	CSettingDlg6 *m_SettingDlg6; 
	CSettingDlg7 *m_SettingDlg7; 
	CPtrArray pPages;
	CWordArray csIds;
	int iCurIdx;
	// Generated message map functions
	//{{AFX_MSG(CSettingDlg)
	afx_msg void OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnApplication();
	virtual void OnOK();
	afx_msg void OnDefault();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGDLG_H__858046F1_1092_4E93_8E06_F19E982E1C19__INCLUDED_)
