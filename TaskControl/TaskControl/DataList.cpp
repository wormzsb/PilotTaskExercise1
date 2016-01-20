// DataList.cpp : implementation file
//

#include "stdafx.h"
//#include "MMMD.h"
#include "DataList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataList

CDataList::CDataList()
{
}

CDataList::~CDataList()
{
}

// ��ѡ���Ƿ����
BOOL CDataList::IsItem(int nItem) const
{
   return GetItemCount() > nItem;
}

//���б���������
BOOL CDataList::AddColumn(LPCTSTR strItem,int nItem,int nWidth,int nFmt,int nSubItem,int nMask)
{
	LV_COLUMN lvc;
	lvc.mask = nMask;
	lvc.fmt = nFmt;
	lvc.pszText = (LPTSTR) strItem;
//	lvc.cx = GetStringWidth(lvc.pszText) + 65;
	lvc.cx = nWidth;
	if(nMask & LVCF_SUBITEM){
		if(nSubItem != -1)
			lvc.iSubItem = nSubItem;
		else
			lvc.iSubItem = nItem;
	}
	return InsertColumn(nItem,&lvc);
}

//���б���������
BOOL CDataList::AddItem(int nItem,int nSubItem,LPCTSTR strItem,int nImageIndex)
{
	LV_ITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = nItem;
	lvItem.iSubItem = nSubItem;
	lvItem.pszText = (LPTSTR) strItem;
//	lvItem.Height=20;
	if(nImageIndex != -1){
		lvItem.mask |= LVIF_IMAGE;
		lvItem.iImage |= LVIF_IMAGE;
	}
	if(nSubItem == 0)
		return InsertItem(&lvItem);
	return SetItem(&lvItem);
}

// ��ѡ���Ƿ����
BOOL CDataList::IsColumn(int nCol) const
{
   LV_COLUMN lvc;
   memset(&lvc, 0, sizeof(lvc));
   lvc.mask = LVCF_WIDTH;
   return GetColumn(nCol, &lvc);
}

// ������ѡ��
int CDataList::GetSelectedItem(int nStartItem /* = -1 */ ) const
{
   return GetNextItem(nStartItem, LVNI_SELECTED);
}

// ѡ��ָ������
BOOL CDataList::SelectItem(int nItem) 
{
   return SetItemState(nItem, LVIS_SELECTED, LVIS_SELECTED);
}

// ѡ���б���е�������
BOOL CDataList::SelectAll()
{
   BOOL bReturn(TRUE);

   for (int nItem = 0; IsItem(nItem); nItem++) 
      if (! SetItemState(nItem, LVIS_SELECTED, LVIS_SELECTED)) {
         bReturn = FALSE;
         break;
      }

   return bReturn;
}
BEGIN_MESSAGE_MAP(CDataList, CListCtrl)
	//{{AFX_MSG_MAP(CDataList)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataList message handlers
