// SettingDlg7.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TaskControl.h"
#include "SettingDlg7.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "TaskControlDoc.h"

// CSettingDlg7 �Ի���

IMPLEMENT_DYNAMIC(CSettingDlg7, CDialog)

CSettingDlg7::CSettingDlg7(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingDlg7::IDD, pParent)
	, m_iStartPos(15)
	, m_bStartPosTop(true)
	, m_bStartPosBottom(true)
	, m_bStartPosLeft(true)
	, m_bStartPosRight(true)
{
	m_bPracCheck = TRUE;
	m_bExpCheck = TRUE;
	m_iSmallBallClrR = 0;
	m_iSmallBallClrG = 255;
	m_iSmallBallClrB = 0;
	m_iBkgndClrR = 48;
	m_iBkgndClrG = 48;
	m_iBkgndClrB = 48;
	m_iObstacleColorR = 255;
	m_iObstacleColorG = 0;
	m_iObstacleColorB = 0;
	m_iSpeedMode = 0;
	m_iSpeed1 = 50;
	m_iSpeed2 = 100;
	m_iSpeed3 = 150;
	//m_iSmallBallAcc = 10;
	//m_iStartPos = 0;
	m_iObstacleRadius = 50;
	m_iSmallBallRadius = 10;
	m_iBallCenterDis = 350;
	m_iPracTimes = 3;
	m_iExpTimes = 2;
	m_iInterval = 3;
	m_TaskName = _T("");
}

CSettingDlg7::~CSettingDlg7()
{
}

void CSettingDlg7::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_PRAC, m_bPracCheck);
	DDX_Check(pDX, IDC_CHECK_EXP, m_bExpCheck);
	DDX_Text(pDX, IDC_SMALL_BALL_CLR_R, m_iSmallBallClrR);
	DDX_Text(pDX, IDC_SMALL_BALL_CLR_G, m_iSmallBallClrG);
	DDX_Text(pDX, IDC_SMALL_BALL_CLR_B, m_iSmallBallClrB);
	DDX_Text(pDX, IDC_BKRND_CLR_R, m_iBkgndClrR);
	DDX_Text(pDX, IDC_BKRND_CLR_G, m_iBkgndClrG);
	DDX_Text(pDX, IDC_BKRND_CLR_B, m_iBkgndClrB);
	DDX_Text(pDX, IDC_BALL_CLR_R, m_iObstacleColorR);
	DDX_Text(pDX, IDC_BALL_CLR_G, m_iObstacleColorG);
	DDX_Text(pDX, IDC_BALL_CLR_B, m_iObstacleColorB);
	//DDX_Radio(pDX, IDC_SPEED_CONSTANT, m_iSpeedMode);
	DDX_Text(pDX,IDC_SPEED1, m_iSpeed1);
	DDX_Text(pDX, IDC_SPEED2, m_iSpeed2);
	DDX_Text(pDX, IDC_SPEED3, m_iSpeed3);
	//DDX_Text(pDX, IDC_BALL_ACC, m_iSmallBallAcc);

	DDX_Text(pDX, IDC_BALL_RADIUS, m_iObstacleRadius);
	DDX_Text(pDX, IDC_SMALL_BALL_RADIUS, m_iSmallBallRadius);
	DDX_Text(pDX, IDC_BALL_CENTER_DIS, m_iBallCenterDis);
	DDX_Text(pDX, IDC_PRAC_TIMES, m_iPracTimes);
	DDX_Text(pDX, IDC_EXP_TIMES, m_iExpTimes);
	DDX_Text(pDX, IDC_INTERVAL_TIME, m_iInterval);
	//DDX_Radio(pDX, IDC_LEFT, m_iStartPos);
	DDX_Check(pDX, IDC_LEFT, m_bStartPosLeft);
	DDX_Check(pDX, IDC_RIGHT, m_bStartPosRight);
	DDX_Check(pDX, IDC_TOP, m_bStartPosTop);
	DDX_Check(pDX, IDC_BOTTOM, m_bStartPosBottom);
}

BEGIN_MESSAGE_MAP(CSettingDlg7, CDialog)

	ON_BN_CLICKED(IDC_CHECK_PRAC, &CSettingDlg7::OnBnClickedCheckPrac)
	ON_BN_CLICKED(IDC_CHECK_EXP, &CSettingDlg7::OnBnClickedCheckExp)
	ON_BN_CLICKED(IDC_SPEED_CONSTANT, &CSettingDlg7::OnBnClickedSpeedConstant)
	//ON_BN_CLICKED(IDC_ACC, &CSettingDlg7::OnBnClickedAcc)
	ON_WM_CTLCOLOR()
//	ON_BN_CLICKED(IDC_CHECK_PRAC2, &CSettingDlg7::OnBnClickedCheckPrac2)
ON_BN_CLICKED(IDC_BALL_SPEED1, &CSettingDlg7::OnBnClickedBallSpeed1)
ON_BN_CLICKED(IDC_BALL_SPEED2, &CSettingDlg7::OnBnClickedBallSpeed2)
ON_BN_CLICKED(IDC_BALL_SPEED3, &CSettingDlg7::OnBnClickedBallSpeed3)
END_MESSAGE_MAP()


void CSettingDlg7::Save() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
    CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();
	
	//��ѡ����
	if (m_bPracCheck)
	{
		pDoc->m_Setting7[m_DlgIdx].m_PracMode = 1;
		pDoc->m_Setting7[m_DlgIdx].m_ExperMode = 0;
	}
	else
	{
		pDoc->m_Setting7[m_DlgIdx].m_PracMode = 0;
		pDoc->m_Setting7[m_DlgIdx].m_ExperMode = 1;
	}

	
	pDoc->m_Setting7[m_DlgIdx].m_iBallColorR = m_iSmallBallClrR;
	pDoc->m_Setting7[m_DlgIdx].m_iBallColorG = m_iSmallBallClrG;
	pDoc->m_Setting7[m_DlgIdx].m_iBallColorB = m_iSmallBallClrB;
	pDoc->m_Setting7[m_DlgIdx].m_iBckGrndColorR= m_iBkgndClrR;
	pDoc->m_Setting7[m_DlgIdx].m_iBckGrndColorG = m_iBkgndClrG;
	pDoc->m_Setting7[m_DlgIdx].m_iBckGrndColorB = m_iBkgndClrB;
	pDoc->m_Setting7[m_DlgIdx].m_iObstacleColorR = m_iObstacleColorR;
	pDoc->m_Setting7[m_DlgIdx].m_iObstacleColorG = m_iObstacleColorG;
	pDoc->m_Setting7[m_DlgIdx].m_iObstacleColorB = m_iObstacleColorB;
	pDoc->m_Setting7[m_DlgIdx].m_iSpeedMode = m_iSpeedMode;
	pDoc->m_Setting7[m_DlgIdx].m_iBallSpeed1 = m_iSpeed1;
	pDoc->m_Setting7[m_DlgIdx].m_iBallSpeed2 = m_iSpeed2;
	pDoc->m_Setting7[m_DlgIdx].m_iBallSpeed3 = m_iSpeed3;


	//pDoc->m_Setting7[m_DlgIdx].m_iBallSpeedAcc = m_iSmallBallAcc;
	//pDoc->m_Setting7[m_DlgIdx].m_iBallStartPos = m_iStartPos;
	pDoc->m_Setting7[m_DlgIdx].m_iObstacleRadius = m_iObstacleRadius;
	pDoc->m_Setting7[m_DlgIdx].m_iBallRadius = m_iSmallBallRadius;
	pDoc->m_Setting7[m_DlgIdx].m_iBallCenterDis = m_iBallCenterDis;
	pDoc->m_Setting7[m_DlgIdx].m_iIntervalTime = m_iInterval;
	printf(m_iBallCenterDis+"");


	if (m_bStartPosTop == TRUE) {
		pDoc->m_Setting7[m_DlgIdx].m_iTop = 1;
	}
	else {
		pDoc->m_Setting7[m_DlgIdx].m_iTop = 0;
	}

	if (m_bStartPosBottom == TRUE) {
		pDoc->m_Setting7[m_DlgIdx].m_iBottom = 1;
	}
	else {
		pDoc->m_Setting7[m_DlgIdx].m_iBottom = 0;
	}

	if (m_bStartPosLeft == TRUE) {
		pDoc->m_Setting7[m_DlgIdx].m_iLeft = 1;
	}
	else {
		pDoc->m_Setting7[m_DlgIdx].m_iLeft = 0;
	}

	if (m_bStartPosRight == TRUE) {
		pDoc->m_Setting7[m_DlgIdx].m_iRight = 1;
	}
	else {
		pDoc->m_Setting7[m_DlgIdx].m_iRight = 0;
	}
	
	pDoc->m_Setting7[m_DlgIdx].m_iPracTimes = m_iPracTimes;
	pDoc->m_Setting7[m_DlgIdx].m_iExpTimes = m_iPracTimes;

	// ��ʼλ��
	setStartPos();
}


void CSettingDlg7::setStartPos()
{
	UpdateData(TRUE);

	CMainFrame*   pMain = (CMainFrame*)AfxGetMainWnd();
	CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();

	pDoc->m_Setting7[m_DlgIdx].m_iBallStartPos = m_bStartPosTop * S_TOP;
	pDoc->m_Setting7[m_DlgIdx].m_iBallStartPos += m_bStartPosRight * S_RIGHT;
	pDoc->m_Setting7[m_DlgIdx].m_iBallStartPos += m_bStartPosBottom * S_BOTTOM;
	pDoc->m_Setting7[m_DlgIdx].m_iBallStartPos += m_bStartPosLeft * S_LEFT;
}

void CSettingDlg7::OnBnClickedCheckPrac()
{
	UpdateData(TRUE);
	//((CEdit*)GetDlgItem(IDC_PRAC_TIMES))->SetReadOnly(!m_bPracCheck);
	
}


void CSettingDlg7::OnBnClickedCheckExp()
{
	
	UpdateData(TRUE);
	((CEdit*)GetDlgItem(IDC_EXP_TIMES))->SetReadOnly(!m_bExpCheck);
}


BOOL CSettingDlg7::OnInitDialog()
{
	
	CEdit*  pEdit=(CEdit*)GetDlgItem(IDC_EDIT3);
    pEdit->SetWindowText(_T("����7-�ٶ�֪����������")); 
	CDialog::OnInitDialog();
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
    CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();

	m_TaskName = pDoc->m_Setting7[m_DlgIdx].m_TaskName;

	
	m_bPracCheck = pDoc->m_Setting7[m_DlgIdx].m_PracMode;
	m_bExpCheck = pDoc->m_Setting7[m_DlgIdx].m_ExperMode;

	m_iSmallBallClrR = pDoc->m_Setting7[m_DlgIdx].m_iBallColorR;
	m_iSmallBallClrG = pDoc->m_Setting7[m_DlgIdx].m_iBallColorG;
	m_iSmallBallClrB = pDoc->m_Setting7[m_DlgIdx].m_iBallColorB;
	m_iBkgndClrR = pDoc->m_Setting7[m_DlgIdx].m_iBckGrndColorR;
	m_iBkgndClrG = pDoc->m_Setting7[m_DlgIdx].m_iBckGrndColorG;
	m_iBkgndClrB = pDoc->m_Setting7[m_DlgIdx].m_iBckGrndColorB;
	m_iObstacleColorR = pDoc->m_Setting7[m_DlgIdx].m_iObstacleColorR;
	m_iObstacleColorG = pDoc->m_Setting7[m_DlgIdx].m_iObstacleColorG;
	m_iObstacleColorB = pDoc->m_Setting7[m_DlgIdx].m_iObstacleColorB;
	m_iSpeedMode = pDoc->m_Setting7[m_DlgIdx].m_iSpeedMode;
	m_iSpeed1 = pDoc->m_Setting7[m_DlgIdx].m_iBallSpeed1;
	m_iSpeed2 = pDoc->m_Setting7[m_DlgIdx].m_iBallSpeed2;
	m_iSpeed3 = pDoc->m_Setting7[m_DlgIdx].m_iBallSpeed3;
	//m_iSmallBallAcc = pDoc->m_Setting7[m_DlgIdx].m_iBallSpeedAcc;
	m_iStartPos = pDoc->m_Setting7[m_DlgIdx].m_iBallStartPos;
	if (pDoc->m_Setting7[m_DlgIdx].m_iTop == 1) {
		m_bStartPosTop = TRUE;
	}
	else {
		m_bStartPosTop = FALSE;
	}

	if (pDoc->m_Setting7[m_DlgIdx].m_iBottom == 1) {
		m_bStartPosBottom = TRUE;
	}
	else {
		m_bStartPosBottom = FALSE;
	}

	if (pDoc->m_Setting7[m_DlgIdx].m_iLeft == 1) {
		m_bStartPosLeft = TRUE;
	}
	else {
		m_bStartPosLeft = FALSE;
	}

	if (pDoc->m_Setting7[m_DlgIdx].m_iRight == 1) {
		m_bStartPosRight = TRUE;
	}
	else {
		m_bStartPosRight = FALSE;
	}
	
	m_iObstacleRadius = pDoc->m_Setting7[m_DlgIdx].m_iObstacleRadius;
	m_iSmallBallRadius = pDoc->m_Setting7[m_DlgIdx].m_iBallRadius;
	m_iBallCenterDis = pDoc->m_Setting7[m_DlgIdx].m_iBallCenterDis;
	m_iPracTimes = pDoc->m_Setting7[m_DlgIdx].m_iPracTimes;
	m_iExpTimes = m_iPracTimes;
	m_iInterval = pDoc->m_Setting7[m_DlgIdx].m_iIntervalTime;

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control

}


void CSettingDlg7::OnBnClickedSpeedConstant()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	((CEdit*)GetDlgItem(IDC_BALL_ACC))->SetReadOnly(TRUE);
}


void CSettingDlg7::OnBnClickedAcc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	((CEdit*)GetDlgItem(IDC_BALL_ACC))->SetReadOnly(FALSE);
}


HBRUSH CSettingDlg7::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_EDIT){
		pDC->SetBkColor(RGB(255,255,255));
	}
	return hbr;
}




void CSettingDlg7::OnBnClickedBallSpeed1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CSettingDlg7::OnBnClickedBallSpeed2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CSettingDlg7::OnBnClickedBallSpeed3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

}
