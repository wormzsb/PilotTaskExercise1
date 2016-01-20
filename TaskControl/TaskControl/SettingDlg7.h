#pragma once
#include <math.h>


// CSettingDlg7 对话框

class CSettingDlg7 : public CDialog
{
	DECLARE_DYNAMIC(CSettingDlg7)

public:
	CSettingDlg7(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSettingDlg7();
	
	
	
	int m_DlgIdx;
// 对话框数据
	enum { IDD = IDD_SETTINGDLG7};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	
	BOOL m_bPracCheck;
	BOOL m_bExpCheck;
	int m_iSmallBallClrR;
	int m_iSmallBallClrG;
	int m_iSmallBallClrB;
	int m_iBkgndClrR;
	int m_iBkgndClrG;
	int m_iBkgndClrB;
	int m_iObstacleColorR;
	int m_iObstacleColorG;
	int m_iObstacleColorB;
	int m_iSpeedMode;
	int m_iSmallBallSpeed;
	int m_iSmallBallAcc;
	int m_iStartPos;
	int m_iObstacleRadius;
	int m_iSmallBallRadius;
	int m_iBallCenterDis;
	int m_iPracTimes;
	int m_iExpTimes;
	int m_iInterval;
	CString m_TaskName;

	BOOL m_bStartPosTop;
	BOOL m_bStartPosBottom;
	BOOL m_bStartPosLeft;
	BOOL m_bStartPosRight;

	void Save();
	afx_msg void OnBnClickedCheckPrac();
	afx_msg void OnBnClickedCheckExp();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedSpeedConstant();
	afx_msg void OnBnClickedAcc();
	//int m_iStartPos;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
//	afx_msg void OnBnClickedCheckPrac2();

	void setStartPos();

	afx_msg void OnBnClickedBallSpeed1();
	afx_msg void OnBnClickedBallSpeed2();
	afx_msg void OnBnClickedBallSpeed3();
};
