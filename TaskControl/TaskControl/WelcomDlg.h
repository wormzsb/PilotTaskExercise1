#pragma once


// CWelcomDlg �Ի���

class CWelcomDlg : public CDialog
{
	DECLARE_DYNAMIC(CWelcomDlg)

public:
	CWelcomDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWelcomDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
