// TaskControl.h : main header file for the TaskControl application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
enum eView {TESTER = 1,SELECT=2,HARD=3};

// CTaskControlApp:
// See TaskControl.cpp for the implementation of this class
//

class CTaskControlApp : public CWinApp
{
public:
	CTaskControlApp();
    CView *g_pView[4];
    BOOL RegisterOcx(LPCTSTR OcxFileName);
	BOOL UnRegisterOcx(LPCTSTR OcxFileName);

// Overrides
public:
	virtual BOOL InitInstance();
    CView* SwitchView( UINT nIndex ); 
	void SaveExe();
// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTaskControlApp theApp;