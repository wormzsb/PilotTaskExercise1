// TaskControlView.cpp : implementation of the CTaskControlView class
//

#include "stdafx.h"
#include "TaskControl.h"

#include "TaskControlDoc.h"
#include "TaskControlView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTaskControlView

IMPLEMENT_DYNCREATE(CTaskControlView, CFormView)

BEGIN_MESSAGE_MAP(CTaskControlView, CFormView)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

// CTaskControlView construction/destruction

CTaskControlView::CTaskControlView()
	: CFormView(CTaskControlView::IDD)
{
	// TODO: add construction code here

}

CTaskControlView::~CTaskControlView()
{
}

void CTaskControlView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CTaskControlView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	//cs.cx=500;
	//cs.cy=500;

	return CFormView::PreCreateWindow(cs);
}

void CTaskControlView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CTaskControlView diagnostics

#ifdef _DEBUG
void CTaskControlView::AssertValid() const
{
	CFormView::AssertValid();
}

void CTaskControlView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CTaskControlDoc* CTaskControlView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTaskControlDoc)));
	return (CTaskControlDoc*)m_pDocument;
}
#endif //_DEBUG


// CTaskControlView message handlers


HBRUSH CTaskControlView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_EDIT){
		pDC->SetBkColor(RGB(255,255,255));
	}
	return hbr;
}
