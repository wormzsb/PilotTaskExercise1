#include "afxwin.h"
#pragma once


// CSettingDlg8 对话框

class CSettingDlg8 : public CDialog
{
	DECLARE_DYNAMIC(CSettingDlg8)

public:
	CSettingDlg8(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSettingDlg8();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETTINGDLG8 };
#endif

	// setting var
	BOOL m_bPracMode;				// 0:exercise; 1: formal
	int m_iPrensentTime;			// defualt: 10s
	int m_iFocusTime;			// default: 2s
	int m_iCountdownTime;		// default: 5s

	// UI var
	CString m_szTaskName;
	int m_DlgIdx; // tab index in setting dialog

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnStnClickedCubenumstatic2();
	void Save();
};
