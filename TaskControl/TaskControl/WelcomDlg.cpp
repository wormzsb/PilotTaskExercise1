// WelcomDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TaskControl.h"
#include "WelcomDlg.h"
#include "afxdialogex.h"


// CWelcomDlg 对话框

IMPLEMENT_DYNAMIC(CWelcomDlg, CDialog)

CWelcomDlg::CWelcomDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWelcomDlg::IDD, pParent)
{

}

CWelcomDlg::~CWelcomDlg()
{
}

void CWelcomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWelcomDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CWelcomDlg 消息处理程序

void CALLBACK MessageBoxTimer(HWND hwnd,   
							  UINT uiMsg,   
							  UINT idEvent,   
							  DWORD dwTime)  
{
	KillTimer(hwnd,0);
	SendMessage(hwnd ,WM_CLOSE,NULL,NULL);
	

}
BOOL CWelcomDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetTimer(0, 3000,  MessageBoxTimer);
	return TRUE;
}


void CWelcomDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	
	HBITMAP hBitmap =  NULL;
	hBitmap =  (HBITMAP)::LoadImage(GetModuleHandle(NULL),"res\\背景.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	
	if (hBitmap == NULL)
		return;
	else
	
	{
		BITMAP bmp;
		GetObject(hBitmap, sizeof(BITMAP), &bmp);

		const int nWidth  = bmp.bmWidth; //width
		const int nHeight = bmp.bmHeight; //height

		int x_resolution = GetSystemMetrics(SM_CXSCREEN); 
		int y_resolution = GetSystemMetrics(SM_CYSCREEN); 
		SetWindowPos(NULL,(x_resolution - nWidth)/2,(y_resolution-nHeight)/2,nWidth,nHeight,SW_SHOW);

		HBITMAP OldBitmap; 
		CDC MemDC; 
		CDC*pDC =  GetDC();
		MemDC.CreateCompatibleDC(pDC); 
		OldBitmap=(HBITMAP)MemDC.SelectObject(hBitmap); 

	
		pDC->SetStretchBltMode(STRETCH_HALFTONE); 
		pDC->StretchBlt(0,0,nWidth,nHeight,&MemDC,0,0,nWidth,nHeight,SRCCOPY); 
	
		MemDC.SelectObject(OldBitmap);
		ReleaseDC(pDC);

	}

	
	

	
	
}


HBRUSH CWelcomDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_EDIT){
		pDC->SetBkColor(RGB(255,255,255));
	}
	return hbr;
}
