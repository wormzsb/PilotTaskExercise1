#if !defined(AFX_DATALIST_H__CABDE6E9_D9AB_405B_AAEA_CD66047DA0A1__INCLUDED_)
#define AFX_DATALIST_H__CABDE6E9_D9AB_405B_AAEA_CD66047DA0A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDataList window

class CDataList : public CListCtrl
{
// Construction
public:
	CDataList();

// Attributes
public:

// Operations
public:
public:
	BOOL AddColumn(
		LPCTSTR strItem,int nItem,int nWidth,
		int nFmt = LVCFMT_CENTER,int nSubItem = -1,
		int nMask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM);//向列表框中添加一列
	//向列表框中添加一行
	BOOL AddItem(int nItem,int nSubItem,LPCTSTR strItem,int nImageIndex = -1);



public:
   BOOL   IsItem(int nItem) const;//所选行是否存在
   BOOL   IsColumn(int nCol) const;//所选列是否存在
   int    GetSelectedItem(int nStartItem = -1) const;//得到所选行
   BOOL   SelectItem(int nItem);//选择指定行
   BOOL   SelectAll();//选择所有行
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataList)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDataList();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDataList)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATALIST_H__CABDE6E9_D9AB_405B_AAEA_CD66047DA0A1__INCLUDED_)
