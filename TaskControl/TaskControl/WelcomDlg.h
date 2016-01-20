#pragma once


// CWelcomDlg 对话框

class CWelcomDlg : public CDialog
{
	DECLARE_DYNAMIC(CWelcomDlg)

public:
	CWelcomDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWelcomDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
