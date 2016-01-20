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
		int nMask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM);//���б�������һ��
	//���б�������һ��
	BOOL AddItem(int nItem,int nSubItem,LPCTSTR strItem,int nImageIndex = -1);



public:
   BOOL   IsItem(int nItem) const;//��ѡ���Ƿ����
   BOOL   IsColumn(int nCol) const;//��ѡ���Ƿ����
   int    GetSelectedItem(int nStartItem = -1) const;//�õ���ѡ��
   BOOL   SelectItem(int nItem);//ѡ��ָ����
   BOOL   SelectAll();//ѡ��������
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
