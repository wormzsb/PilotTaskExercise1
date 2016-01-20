// SelectView.cpp : implementation file
//

#include "stdafx.h"
#include "taskcontrol.h"
#include "SelectView.h"
#include "TesterView.h"
#include "SettingDlg.h"
#include "MainFrm.h"
#include <direct.h>
#include "HardView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const CString m_TaskItem[] = {_T("任务1-目标跟踪能力测试"),
							   _T("任务2-操作力保持及时间知觉能力测试"),
							   _T("任务3-双任务模式突发事件反应时测试"),
							   _T("任务4-触点作业操作能力测试"),
							   _T("任务5-双任务模式图符记忆判别能力测试"),
							   _T("任务6-双任务模式三维图形记忆判别能力测试"),
							   _T("任务7-速度知觉能力测试")};
int m_CurItemNo;
/////////////////////////////////////////////////////////////////////////////
// CSelectView

IMPLEMENT_DYNCREATE(CSelectView, CFormView)

CSelectView::CSelectView()
	: CFormView(CSelectView::IDD)
{
	//{{AFX_DATA_INIT(CSelectView)
	//}}AFX_DATA_INIT
	m_bSetting = FALSE;
}

CSelectView::~CSelectView()
{
}

void CSelectView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectView)
	DDX_Control(pDX, IDC_LIST1, m_TaskList);
	DDX_Control(pDX, IDC_LIST2, m_SelectedList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectView, CFormView)
	//{{AFX_MSG_MAP(CSelectView)
	ON_BN_CLICKED(IDC_MOVEDOWN, OnMovedown)
	ON_BN_CLICKED(IDC_MOVEUP, OnMoveup)
	ON_BN_CLICKED(IDC_SELECT, OnSelect)
	ON_BN_CLICKED(IDC_REVERT, OnRevert)
	ON_BN_CLICKED(IDC_SETTING, OnSetting)
	ON_BN_CLICKED(IDC_VIEWSETTING, OnViewsetting)
	ON_BN_CLICKED(IDC_SAVEASSETTING, OnSaveassetting)
	ON_BN_CLICKED(IDC_MAKESURE, OnMakesure)
	ON_BN_CLICKED(IDC_SAVESETTING, OnSavesetting)
	//}}AFX_MSG_MAP
	ON_LBN_DBLCLK(IDC_LIST2, &CSelectView::OnDblclkList2)
	ON_BN_CLICKED(IDC_MAKESURE3, &CSelectView::OnLast)
	ON_BN_CLICKED(IDC_MAKESURE4, &CSelectView::OnNext)
	ON_BN_CLICKED(IDC_BUTTON1, &CSelectView::OnBnClickedButton1)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectView diagnostics

#ifdef _DEBUG
void CSelectView::AssertValid() const
{
	CFormView::AssertValid();
}

void CSelectView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CTaskControlDoc* CSelectView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTaskControlDoc)));
	return (CTaskControlDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSelectView message handlers

//下移所选的任务
void CSelectView::OnMovedown() 
{
	// TODO: Add your control notification handler code here
	int idx = m_SelectedList.GetCurSel();
	if(idx>-1)
	{
		int ItemNo;
		ItemNo = m_SelectedList.GetItemData(idx);
		//int taskidx = m_SelectedList.GetItemData(idx);
		CString selstr;
		m_SelectedList.GetText(idx,selstr);
		m_SelectedList.DeleteString(idx);

		//若是列表框最后一条消息 则不再需要插入
		if (idx < m_SelectedList.GetCount() - 1)
		{
			int newidx = m_SelectedList.InsertString(idx+1,selstr);
			m_SelectedList.SetItemData(newidx,ItemNo);
			m_SelectedList.SetCurSel(newidx);	
		}
		
	}	
	CButton* m_Button;
	m_Button = (CButton*)GetDlgItem(IDC_MAKESURE); 
    m_Button->EnableWindow(TRUE);
	m_bSetting = FALSE;
}

//上移所选的任务
void CSelectView::OnMoveup() 
{
	// TODO: Add your control notification handler code here
	int idx = m_SelectedList.GetCurSel();
	if(idx>-1)
	{
		int ItemNo;
		ItemNo = m_SelectedList.GetItemData(idx);
		//int taskidx = m_SelectedList.GetItemData(idx);
		CString selstr;
		m_SelectedList.GetText(idx,selstr);
		m_SelectedList.DeleteString(idx);
		int newidx = m_SelectedList.InsertString(idx-1,selstr);
		m_SelectedList.SetItemData(newidx,ItemNo);
		m_SelectedList.SetCurSel(newidx);
	}
	CButton* m_Button;
	m_Button = (CButton*)GetDlgItem(IDC_MAKESURE); 
    m_Button->EnableWindow(TRUE);
	m_bSetting = FALSE;
}

//选择任务
void CSelectView::OnSelect() 
{
	// TODO: Add your control notification handler code here
	CTaskControlDoc* pDoc = (CTaskControlDoc*)GetDocument();
	pDoc->m_TaskCount = m_SelectedList.GetCount();
	int idx = m_TaskList.GetCurSel();
	if(idx>-1)
	{
		int taskidx = m_TaskList.GetItemData(idx);
		pDoc->m_ItemData[m_CurItemNo].TaskIdx = taskidx;
		int i=0;
		while(pDoc->m_bUsedIdx[taskidx][i])
		{
			i++;
		}
		pDoc->m_ItemData[m_CurItemNo].TaskNo = i;
		pDoc->m_ItemData[m_CurItemNo].bSet = FALSE;
		pDoc->m_bUsedIdx[taskidx][i] = TRUE;
		CString selstr;
//		m_TaskList.DeleteString(idx);
		selstr.Format("%s  未设置",m_TaskItem[pDoc->m_ItemData[m_CurItemNo].TaskIdx]);
		int newidx = m_SelectedList.AddString(selstr);
		m_SelectedList.SetItemData(newidx,m_CurItemNo);
		m_SelectedList.SetCurSel(newidx);
//		m_TaskSig[taskidx] = 0;
		m_CurItemNo++;
	}	
	CButton* m_Button;
	m_Button = (CButton*)GetDlgItem(IDC_MAKESURE); 
    m_Button->EnableWindow(TRUE);
	m_bSetting = FALSE;
}

//取消所选的任务
void CSelectView::OnRevert() 
{
	// TODO: Add your control notification handler code here
	int idx = m_SelectedList.GetCurSel();
	if(idx>-1)
	{
		m_SelectedList.DeleteString(idx);
	}	
	CButton* m_Button;
	m_Button = (CButton*)GetDlgItem(IDC_MAKESURE); 
    m_Button->EnableWindow(TRUE);
}

void CSelectView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	int i;
	int idx = 0;
	for(i=0;i<7;i++)
	{
//		m_TaskSig[i] = 1;
		if (i != 3 && i != 4)
		{
			m_TaskList.InsertString(idx, m_TaskItem[i]);
			m_TaskList.SetItemData(idx, i);
			idx++;
		}
		m_TaskSet[i] = FALSE;
		
		
	}	
	m_CurItemNo = 0;
}

//设置所选的任务		
void CSelectView::OnSetting() 
{
	// TODO: Add your control notification handler code here
	CTaskControlDoc* pDoc = (CTaskControlDoc*)GetDocument();
	pDoc->m_TaskCount = m_SelectedList.GetCount();
	int i;
    for(i=0;i<7;i++)
	{
		pDoc->m_TaskNum[i] = 0;
	}
	for(i=0;i<pDoc->m_TaskCount;i++)
	{
		pDoc->m_ItemOrder[i] = m_SelectedList.GetItemData(i);
		pDoc->m_TaskOrder[i] = pDoc->m_ItemData[pDoc->m_ItemOrder[i]].TaskIdx;
//		pDoc->m_TaskNum[pDoc->m_TaskOrder[i]]++;
		int DocNo = pDoc->m_ItemData[pDoc->m_ItemOrder[i]].TaskNo;
		switch(pDoc->m_TaskOrder[i])
		{
        case 0:
			if(pDoc->m_Setting1==NULL)
			{
                pDoc->m_Setting1 = (struct TaskSetting1*)malloc((DocNo+1)*sizeof(struct TaskSetting1));
				pDoc->m_DocNum[pDoc->m_TaskOrder[i]] = DocNo+1;
			}
			else if(DocNo>(pDoc->m_DocNum[pDoc->m_TaskOrder[i]]-1))
			{
				pDoc->m_Setting1 = (struct TaskSetting1*)realloc(pDoc->m_Setting1, (DocNo+1)*sizeof(struct TaskSetting1));
			    pDoc->m_DocNum[pDoc->m_TaskOrder[i]] = DocNo+1;
			}
            if(!pDoc->m_ItemData[pDoc->m_ItemOrder[i]].bSet)
			{
				pDoc->m_Setting1[DocNo] = pDoc->m_DefSetting1;
			}
			break;
		case 1:
			if(pDoc->m_Setting2==NULL)
			{
                pDoc->m_Setting2 = (struct TaskSetting2*)malloc((DocNo+1)*sizeof(struct TaskSetting2));
				pDoc->m_DocNum[pDoc->m_TaskOrder[i]] = DocNo+1;
			}
			else if(DocNo>(pDoc->m_DocNum[pDoc->m_TaskOrder[i]]-1))
			{
				pDoc->m_Setting2 = (struct TaskSetting2*)realloc(pDoc->m_Setting2, (DocNo+1)*sizeof(struct TaskSetting2));
			    pDoc->m_DocNum[pDoc->m_TaskOrder[i]] = DocNo+1;
			}
            if(!pDoc->m_ItemData[pDoc->m_ItemOrder[i]].bSet)
			{
				pDoc->m_Setting2[DocNo] = pDoc->m_DefSetting2;
			}
			break;
		case 2:
			if(pDoc->m_Setting3==NULL)
			{
                pDoc->m_Setting3 = (struct TaskSetting3*)malloc((DocNo+1)*sizeof(struct TaskSetting3));
				pDoc->m_DocNum[pDoc->m_TaskOrder[i]] = DocNo+1;
			}
			else if(DocNo>(pDoc->m_DocNum[pDoc->m_TaskOrder[i]]-1))
			{
				pDoc->m_Setting3 = (struct TaskSetting3*)realloc(pDoc->m_Setting3, (DocNo+1)*sizeof(struct TaskSetting3));
			    pDoc->m_DocNum[pDoc->m_TaskOrder[i]] = DocNo+1;
			}
            if(!pDoc->m_ItemData[pDoc->m_ItemOrder[i]].bSet)
			{
				pDoc->m_Setting3[DocNo] = pDoc->m_DefSetting3;
			}
			break;
		case 3:
			if(pDoc->m_Setting4==NULL)
			{
                pDoc->m_Setting4 = (struct TaskSetting4*)malloc((DocNo+1)*sizeof(struct TaskSetting4));
				pDoc->m_DocNum[pDoc->m_TaskOrder[i]] = DocNo+1;
			}
			else if(DocNo>(pDoc->m_DocNum[pDoc->m_TaskOrder[i]]-1))
			{
				pDoc->m_Setting4 = (struct TaskSetting4*)realloc(pDoc->m_Setting4, (DocNo+1)*sizeof(struct TaskSetting4));
			    pDoc->m_DocNum[pDoc->m_TaskOrder[i]] = DocNo+1;
			}
            if(!pDoc->m_ItemData[pDoc->m_ItemOrder[i]].bSet)
			{
				pDoc->m_Setting4[DocNo] = pDoc->m_DefSetting4;
			}
			break;
		case 4:
			if(pDoc->m_Setting5==NULL)
			{
                pDoc->m_Setting5 = (struct TaskSetting5*)malloc((DocNo+1)*sizeof(struct TaskSetting5));
				pDoc->m_DocNum[pDoc->m_TaskOrder[i]] = DocNo+1;
			}
			else if(DocNo>(pDoc->m_DocNum[pDoc->m_TaskOrder[i]]-1))
			{
				pDoc->m_Setting5 = (struct TaskSetting5*)realloc(pDoc->m_Setting5, (DocNo+1)*sizeof(struct TaskSetting5));
			    pDoc->m_DocNum[pDoc->m_TaskOrder[i]] = DocNo+1;
			}
            if(!pDoc->m_ItemData[pDoc->m_ItemOrder[i]].bSet)
			{
				pDoc->m_Setting5[DocNo] = pDoc->m_DefSetting5;
			}
			break;
		case 5:
			if(pDoc->m_Setting6==NULL)
			{
                pDoc->m_Setting6 = (struct TaskSetting6*)malloc((DocNo+1)*sizeof(struct TaskSetting6));
				pDoc->m_DocNum[pDoc->m_TaskOrder[i]] = DocNo+1;
			}
			else if(DocNo>(pDoc->m_DocNum[pDoc->m_TaskOrder[i]]-1))
			{
				pDoc->m_Setting6 = (struct TaskSetting6*)realloc(pDoc->m_Setting6, (DocNo+1)*sizeof(struct TaskSetting6));
			    pDoc->m_DocNum[pDoc->m_TaskOrder[i]] = DocNo+1;
			}
            if(!pDoc->m_ItemData[pDoc->m_ItemOrder[i]].bSet)
			{
				pDoc->m_Setting6[DocNo] = pDoc->m_DefSetting6;
			}
			break;
		case 6:
			if(pDoc->m_Setting7==NULL)
			{
                pDoc->m_Setting7 = (struct TaskSetting7*)malloc((DocNo+1)*sizeof(struct TaskSetting7));
				pDoc->m_DocNum[pDoc->m_TaskOrder[i]] = DocNo+1;
			}
			else if(DocNo>(pDoc->m_DocNum[pDoc->m_TaskOrder[i]]-1))
			{
				pDoc->m_Setting7 = (struct TaskSetting7*)realloc(pDoc->m_Setting7, (DocNo+1)*sizeof(struct TaskSetting7));
			    pDoc->m_DocNum[pDoc->m_TaskOrder[i]] = DocNo+1;
			}
            if(!pDoc->m_ItemData[pDoc->m_ItemOrder[i]].bSet)
			{
				pDoc->m_Setting7[DocNo] = pDoc->m_DefSetting7;
			}
			break;
		}
	}  
	CSettingDlg dlg;
	int newidx;
//	BOOL bSet = FALSE;
	if(pDoc->m_TaskCount>0)
	{
		int idx = m_SelectedList.GetCurSel();
		if(idx<0)
		{
			idx = 0;
		}
		int ItemIdx;
		ItemIdx = m_SelectedList.GetItemData(idx);
		int taskidx = pDoc->m_ItemData[ItemIdx].TaskIdx;
		dlg.m_CurItem = idx;
		CString itemname;
		if(dlg.DoModal()==IDOK)
		{
			for(i=0;i<pDoc->m_TaskCount;i++)
			{
				ItemIdx = m_SelectedList.GetItemData(i);
                taskidx = pDoc->m_TaskOrder[i];
     			m_TaskSet[taskidx] = TRUE;
	    		m_SelectedList.DeleteString(i);
				switch(taskidx)
				{
				case 0:
					itemname = pDoc->m_Setting1[pDoc->m_ItemData[ItemIdx].TaskNo].m_TaskName;
					break;
				case 1:
					itemname = pDoc->m_Setting2[pDoc->m_ItemData[ItemIdx].TaskNo].m_TaskName;
					break;
				case 2:
					itemname = pDoc->m_Setting3[pDoc->m_ItemData[ItemIdx].TaskNo].m_TaskName;
					break;
				case 3:
					itemname = pDoc->m_Setting4[pDoc->m_ItemData[ItemIdx].TaskNo].m_TaskName;
					break;
				case 4:
					itemname = pDoc->m_Setting5[pDoc->m_ItemData[ItemIdx].TaskNo].m_TaskName;
					break;
				case 5:
					itemname = pDoc->m_Setting6[pDoc->m_ItemData[ItemIdx].TaskNo].m_TaskName;
					break;
				case 6:
					itemname = pDoc->m_Setting7[pDoc->m_ItemData[ItemIdx].TaskNo].m_TaskName;
					break;
				}
		        newidx = m_SelectedList.InsertString(i,itemname+"  已设置");
			    m_SelectedList.SetItemData(newidx,ItemIdx);
				pDoc->m_ItemData[pDoc->m_ItemOrder[i]].bSet = TRUE;
//		        m_SelectedList.SetCurSel(newidx);
			}
		}
		CButton* m_Button;
	    m_Button = (CButton*)GetDlgItem(IDC_MAKESURE); 
        m_Button->EnableWindow(TRUE);
		m_bSetting = FALSE;
	}	
}

void CSelectView::OnViewsetting() 
{
	// TODO: Add your control notification handler code here
	CTaskControlDoc* pDoc = (CTaskControlDoc*)GetDocument();
	CSettingDlg dlg;
	int idx = m_SelectedList.GetCurSel();
	BOOL bSet = FALSE;
	if(idx>-1)
	{
        int ItemIdx = m_SelectedList.GetItemData(idx);
		int taskidx = pDoc->m_ItemData[ItemIdx].TaskIdx;
		if(!m_TaskSet[taskidx])
		{
			MessageBox("任务参数没有设置！");
			return;
		}
		dlg.m_CurItem = idx;
        dlg.DoModal();
	}		
}

//保存任务设置
void CSelectView::OnSavesetting() 
{
	// TODO: Add your control notification handler code here
	CTaskControlDoc* pDoc = (CTaskControlDoc*)GetDocument();

//	_mkdir("Settings");
//	CString m_FileName;
//	m_FileName = "Settings\\TaskSetting.set";
	SaveSetting(pDoc->m_CurSettingFile);
	MessageBox("保存完毕！","提示");
}

//另存任务设置
void CSelectView::OnSaveassetting() 
{
	// TODO: Add your control notification handler code here
	SetCurrentDirectory(g_szExePath);

	CString m_FileName;
	CFileDialog Dlg(FALSE,NULL,"*.set",NULL,"Task Setting Files (*.set)",this); 
   
    DWORD nBufferLength=256; 
	char lpBuffer[256];  
//	char lpSaveBuffer[256];
	GetCurrentDirectory(nBufferLength,lpBuffer);
//	sprintf(lpSaveBuffer,"%s\\PartInfo",lpBuffer);
	CString dlgpath;
	dlgpath.Format("%s\\Settings",lpBuffer);
	Dlg.m_ofn.lpstrInitialDir=dlgpath.GetBuffer(dlgpath.GetLength());	
	if(Dlg.DoModal()==IDOK)
	{
		m_FileName = Dlg.GetPathName();	
        SaveSetting(m_FileName);
		MessageBox("保存完毕！","提示");
	}
	SetCurrentDirectory(lpBuffer);
}

void CSelectView::SaveSetting(CString FileName) 
{
	SetCurrentDirectory(g_szExePath);
	// TODO: Add extra validation here
	CTaskControlDoc* pDoc = (CTaskControlDoc*)GetDocument();

	CString str;
	int i;
	pDoc->m_TaskCount = m_SelectedList.GetCount();

	for(i=0;i<pDoc->m_TaskCount;i++)
	{
		int ItemIdx = m_SelectedList.GetItemData(i);
		pDoc->m_TaskOrder[i] = pDoc->m_ItemData[ItemIdx].TaskIdx;
		if(!m_TaskSet[pDoc->m_TaskOrder[i]])
		{
		    str.Format("任务%d没有设置！",pDoc->m_TaskOrder[i]+1);
		    MessageBox(str);
		    return;
		}
	} 
	FILE *fp;
	fopen_s(&fp, FileName,"wt");
	if(fp!=NULL)
	{
		fprintf(fp,"[TaskOrder]\n");
		for(i=0;i<pDoc->m_TaskCount;i++)
		{
			int ItemIdx = m_SelectedList.GetItemData(i);
			pDoc->m_TaskOrder[i] = pDoc->m_ItemData[ItemIdx].TaskIdx;
			fprintf(fp,"Task%d\n",pDoc->m_TaskOrder[i]+1);
		}  
		fprintf(fp,"\n");
		for(i=0;i<pDoc->m_TaskCount;i++)
		{
			int ItemIdx = m_SelectedList.GetItemData(i);
			pDoc->m_TaskOrder[i] = pDoc->m_ItemData[ItemIdx].TaskIdx;
			int DocNo = pDoc->m_ItemData[ItemIdx].TaskNo;
			switch(pDoc->m_TaskOrder[i])
			{
			case 0:
				//Task1
				fprintf(fp,"[Task1(%s)]\n",pDoc->m_Setting1[DocNo].m_TaskName);
				fprintf(fp,"TaskName\t%d-%s\n",i,pDoc->m_Setting1[DocNo].m_TaskName);
				fprintf(fp,"PracMode\t%d\n",pDoc->m_Setting1[DocNo].m_PracMode);
				fprintf(fp,"ExperMode\t%d\n",pDoc->m_Setting1[DocNo].m_ExperMode);
				fprintf(fp,"Background\t%d\n",pDoc->m_Setting1[DocNo].m_Background);
				fprintf(fp,"Track\t%d\n",pDoc->m_Setting1[DocNo].m_Track);
				fprintf(fp,"Direction\t%d\n",pDoc->m_Setting1[DocNo].m_Direction);
				fprintf(fp,"MoveMode\t%d\n",pDoc->m_Setting1[DocNo].m_MoveMode);
				fprintf(fp,"SpeedMode\t%d\n",pDoc->m_Setting1[DocNo].m_SpeedMode);
				fprintf(fp,"Pause\t%d\n",pDoc->m_Setting1[DocNo].m_Pause);
				fprintf(fp,"PauseNum\t%d\n",pDoc->m_Setting1[DocNo].m_PauseNum);
				fprintf(fp,"Speed\t%.2f\n",pDoc->m_Setting1[DocNo].m_Speed);
				fprintf(fp,"InitSpeed\t%.2f\n",pDoc->m_Setting1[DocNo].m_InitSpeed);
				fprintf(fp,"SpeedMin\t%.2f\n",pDoc->m_Setting1[DocNo].m_SpeedMin);
				fprintf(fp,"SpeedMax\t%.2f\n",pDoc->m_Setting1[DocNo].m_SpeedMax);
				fprintf(fp,"AccelerationMin\t%.2f\n",pDoc->m_Setting1[DocNo].m_AccelerationMin);
				fprintf(fp,"AccelerationMax\t%.2f\n",pDoc->m_Setting1[DocNo].m_AccelerationMax);
				fprintf(fp,"AngleSpeedMin\t%.2f\n",pDoc->m_Setting1[DocNo].m_AngleSpeedMin);
				fprintf(fp,"AngleSpeedMax\t%.2f\n",pDoc->m_Setting1[DocNo].m_AngleSpeedMax);
				fprintf(fp,"RotateAngleMin\t%.2f\n",pDoc->m_Setting1[DocNo].m_RotateAngleMin);
				fprintf(fp,"RotateAngleMax\t%.2f\n",pDoc->m_Setting1[DocNo].m_RotateAngleMax);
				fprintf(fp,"PracTime\t%d\n",pDoc->m_Setting1[DocNo].m_PracTime);
				fprintf(fp,"ExperTime\t%d\n",pDoc->m_Setting1[DocNo].m_ExperTime);
				fprintf(fp,"PracTimes\t%d\n",pDoc->m_Setting1[DocNo].m_PracTimes);
				fprintf(fp,"ExperTimes\t%d\n",pDoc->m_Setting1[DocNo].m_ExperTimes);
				fprintf(fp,"JoyMoveDirection\t%d\n",pDoc->m_Setting1[DocNo].m_iJoyMoveDirection);
				fprintf(fp,"\n");
				break;
			case 1:
	    		//Task2
				fprintf(fp,"[Task2(%s)]\n",pDoc->m_Setting2[DocNo].m_TaskName);
				fprintf(fp,"TaskName\t%d-%s\n",i,pDoc->m_Setting2[DocNo].m_TaskName);
				fprintf(fp,"PracMode\t%d\n",pDoc->m_Setting2[DocNo].m_PracMode);
				fprintf(fp,"ExperMode\t%d\n",pDoc->m_Setting2[DocNo].m_ExperMode);
				fprintf(fp,"MainTask\t%d\n",pDoc->m_Setting2[DocNo].m_MainTask);
				fprintf(fp,"SubTask\t%d\n",pDoc->m_Setting2[DocNo].m_SubTask);
				fprintf(fp,"Background\t%d\n",pDoc->m_Setting2[DocNo].m_Background);
				fprintf(fp,"Direction\t%d\n",pDoc->m_Setting2[DocNo].m_Direction);
				fprintf(fp,"InitSpeed\t%.2f\n",pDoc->m_Setting2[DocNo].m_InitSpeed);
				fprintf(fp,"HoldTimeNum\t%d\n",pDoc->m_Setting2[DocNo].m_HoldTimeNum);
				fprintf(fp,"HoldTime1\t%.1f\n",pDoc->m_Setting2[DocNo].m_HoldTime[0]);
				fprintf(fp,"HoldTime2\t%.1f\n",pDoc->m_Setting2[DocNo].m_HoldTime[1]);
				fprintf(fp,"HoldTime3\t%.1f\n",pDoc->m_Setting2[DocNo].m_HoldTime[2]);
				fprintf(fp,"HoldTime4\t%.1f\n",pDoc->m_Setting2[DocNo].m_HoldTime[3]);
				fprintf(fp,"HoldTime5\t%.1f\n",pDoc->m_Setting2[DocNo].m_HoldTime[4]);
				fprintf(fp,"HoldTime6\t%.1f\n",pDoc->m_Setting2[DocNo].m_HoldTime[5]);
				fprintf(fp,"HoldTime7\t%.1f\n",pDoc->m_Setting2[DocNo].m_HoldTime[6]);
				fprintf(fp,"HoldTime8\t%.1f\n",pDoc->m_Setting2[DocNo].m_HoldTime[7]);
				fprintf(fp,"HoldTime9\t%.1f\n",pDoc->m_Setting2[DocNo].m_HoldTime[8]);
				fprintf(fp,"HoldTime10\t%.1f\n",pDoc->m_Setting2[DocNo].m_HoldTime[9]);
				fprintf(fp,"HoldTime11\t%.1f\n",pDoc->m_Setting2[DocNo].m_HoldTime[10]);
				fprintf(fp,"HoldTime12\t%.1f\n",pDoc->m_Setting2[DocNo].m_HoldTime[11]);
				fprintf(fp,"PracTime\t%d\n",pDoc->m_Setting2[DocNo].m_PracTime);
				fprintf(fp,"ExperTime\t%d\n",pDoc->m_Setting2[DocNo].m_ExperTime);
				fprintf(fp,"PracTimes\t%d\n",pDoc->m_Setting2[DocNo].m_PracTimes);
				fprintf(fp,"ExperTimes\t%d\n",pDoc->m_Setting2[DocNo].m_ExperTimes);
				fprintf(fp,"JoyMoveDirection\t%d\n",pDoc->m_Setting2[DocNo].m_iJoyMoveDirection);
				fprintf(fp,"SubTaskInterval\t%d\n",pDoc->m_Setting2[DocNo].m_iSubTaskInterval);
				fprintf(fp,"SpeedMode\t%d\n",pDoc->m_Setting2[DocNo].m_SpeedMode);
				fprintf(fp,"Speed\t%f\n",pDoc->m_Setting2[DocNo].m_Speed);
				fprintf(fp,"SpeedMin\t%f\n",pDoc->m_Setting2[DocNo].m_SpeedMin);
				fprintf(fp,"SpeedMax\t%f\n",pDoc->m_Setting2[DocNo].m_SpeedMax);
				fprintf(fp,"AccelerationMin\t%f\n",pDoc->m_Setting2[DocNo]. m_AccelerationMin);
				fprintf(fp,"AccelerationMax\t%f\n",pDoc->m_Setting2[DocNo]. m_AccelerationMax);
				fprintf(fp,"Track\t%d\n",pDoc->m_Setting2[DocNo]. m_iTrack);
				fprintf(fp,"\n");
				break;
			case 2:
				//Task3
				fprintf(fp,"[Task3(%s)]\n",pDoc->m_Setting3[DocNo].m_TaskName);
				fprintf(fp,"TaskName\t%d-%s\n",i,pDoc->m_Setting3[DocNo].m_TaskName);
				fprintf(fp,"PracMode\t%d\n",pDoc->m_Setting3[DocNo].m_PracMode);
				fprintf(fp,"ExperMode\t%d\n",pDoc->m_Setting3[DocNo].m_ExperMode);	
				fprintf(fp,"MainTask\t%d\n",pDoc->m_Setting3[DocNo].m_MainTask);
				fprintf(fp,"SubTask\t%d\n",pDoc->m_Setting3[DocNo].m_SubTask);	
				fprintf(fp,"MainTaskMode\t%d\n",pDoc->m_Setting3[DocNo].m_MainTaskMode);	
				fprintf(fp,"Background\t%d\n",pDoc->m_Setting3[DocNo].m_Background);
 				fprintf(fp,"InitSpeed\t%.2f\n",pDoc->m_Setting3[DocNo].m_InitSpeed);
				fprintf(fp,"EventMode\t%d\n",pDoc->m_Setting3[DocNo].m_EventMode);	
				fprintf(fp,"CodePairMode\t%d\n",pDoc->m_Setting3[DocNo].m_CodePairMode);	
				fprintf(fp,"CodePairNum\t%d\n",pDoc->m_Setting3[DocNo].m_CodePairNum);	
				fprintf(fp,"DisplayMode\t%d\n",pDoc->m_Setting3[DocNo].m_DisplayMode);	
				fprintf(fp,"EventFrequency\t%d\n",pDoc->m_Setting3[DocNo].m_EventFrequency);
				fprintf(fp,"PracTime\t%d\n",pDoc->m_Setting3[DocNo].m_PracTime);
				fprintf(fp,"ExperTime\t%d\n",pDoc->m_Setting3[DocNo].m_ExperTime);
				fprintf(fp,"PracTimes\t%d\n",pDoc->m_Setting3[DocNo].m_PracTimes);
				fprintf(fp,"ExperTimes\t%d\n",pDoc->m_Setting3[DocNo].m_ExperTimes);
				fprintf(fp,"JoyMoveDirection\t%d\n",pDoc->m_Setting3[DocNo].m_iJoyMoveDirection);
				fprintf(fp,"PlanePos\t%d\n",pDoc->m_Setting3[DocNo].m_iPlanePos);
				fprintf(fp,"Direction\t%d\n",pDoc->m_Setting3[DocNo].m_Direction);
				fprintf(fp,"SpeedMode\t%d\n",pDoc->m_Setting3[DocNo].m_SpeedMode);
				fprintf(fp,"Speed\t%f\n",pDoc->m_Setting3[DocNo].m_Speed);
				fprintf(fp,"SpeedMin\t%f\n",pDoc->m_Setting3[DocNo].m_SpeedMin);
				fprintf(fp,"SpeedMax\t%f\n",pDoc->m_Setting3[DocNo].m_SpeedMax);
				fprintf(fp,"AccelerationMin\t%f\n",pDoc->m_Setting3[DocNo]. m_AccelerationMin);
				fprintf(fp,"AccelerationMax\t%f\n",pDoc->m_Setting3[DocNo]. m_AccelerationMax);
				fprintf(fp,"Track\t%d\n",pDoc->m_Setting3[DocNo].m_iTrack);
				fprintf(fp,"Plane\t%d\n",pDoc->m_Setting3[DocNo].m_iPlane);
				fprintf(fp,"Helicopter\t%d\n",pDoc->m_Setting3[DocNo].m_iHelicopter);
				fprintf(fp,"PresentTime\t%d\n",pDoc->m_Setting3[DocNo].m_iPresentTime);
				fprintf(fp,"IntervalMin\t%d\n",pDoc->m_Setting3[DocNo].m_iIntervalMin);
				fprintf(fp,"IntervalMax\t%d\n",pDoc->m_Setting3[DocNo].m_iIntervalMax);
				fprintf(fp,"ReactTime\t%d\n",pDoc->m_Setting3[DocNo].m_iReactTime);
				fprintf(fp,"\n");
				break;
			case 3:
				//Task4
				fprintf(fp,"[Task4(%s)]\n",pDoc->m_Setting4[DocNo].m_TaskName);
				fprintf(fp,"TaskName\t%d-%s\n",i,pDoc->m_Setting4[DocNo].m_TaskName);
				fprintf(fp,"PracMode\t%d\n",pDoc->m_Setting4[DocNo].m_PracMode);
				fprintf(fp,"ExperMode\t%d\n",pDoc->m_Setting4[DocNo].m_ExperMode);		
				fprintf(fp,"Background\t%d\n",pDoc->m_Setting4[DocNo].m_Background);
				fprintf(fp,"TouchOrder\t%d\n",pDoc->m_Setting4[DocNo].m_TouchOrder);	
				fprintf(fp,"PracTimes\t%d\n",pDoc->m_Setting4[DocNo].m_PracTimes);
				fprintf(fp,"ExperTimes\t%d\n",pDoc->m_Setting4[DocNo].m_ExperTimes);
				fprintf(fp,"\n");
				break;
			case 4:
				//Task5
				fprintf(fp,"[Task5(%s)]\n",pDoc->m_Setting5[DocNo].m_TaskName);
				fprintf(fp,"TaskName\t%d-%s\n",i,pDoc->m_Setting5[DocNo].m_TaskName);
				fprintf(fp,"PracMode\t%d\n",pDoc->m_Setting5[DocNo].m_PracMode);
				fprintf(fp,"ExperMode\t%d\n",pDoc->m_Setting5[DocNo].m_ExperMode);	
				fprintf(fp,"MainTask\t%d\n",pDoc->m_Setting5[DocNo].m_MainTask);
				fprintf(fp,"SubTask\t%d\n",pDoc->m_Setting5[DocNo].m_SubTask);
				fprintf(fp,"Background\t%d\n",pDoc->m_Setting5[DocNo].m_Background);
 				fprintf(fp,"InitSpeed\t%.2f\n",pDoc->m_Setting5[DocNo].m_InitSpeed);
				fprintf(fp,"SignMemType\t%d\n",pDoc->m_Setting5[DocNo].m_SignMemType);
				fprintf(fp,"SignMemMode\t%d\n",pDoc->m_Setting5[DocNo].m_SignMemMode);	
				fprintf(fp,"SignMemNum\t%d\n",pDoc->m_Setting5[DocNo].m_SignMemNum);	
				fprintf(fp,"SignShowMode\t%d\n",pDoc->m_Setting5[DocNo].m_SignShowMode);	
				fprintf(fp,"SignShowTime\t%.1f\n",pDoc->m_Setting5[DocNo].m_SignShowTime);	
				fprintf(fp,"PracTime\t%d\n",pDoc->m_Setting5[DocNo].m_PracTime);
				fprintf(fp,"ExperTime\t%d\n",pDoc->m_Setting5[DocNo].m_ExperTime);
				fprintf(fp,"PracTimes\t%d\n",pDoc->m_Setting5[DocNo].m_PracTimes);
				fprintf(fp,"ExperTimes\t%d\n",pDoc->m_Setting5[DocNo].m_ExperTimes);
				fprintf(fp,"JoyMoveDirection\t%d\n",pDoc->m_Setting5[DocNo].m_iJoyMoveDirection);
				fprintf(fp,"\n");
				break;
			case 5:
				//Task6
				fprintf(fp,"[Task6(%s)]\n",pDoc->m_Setting6[DocNo].m_TaskName);
				fprintf(fp,"TaskName\t%d-%s\n",i,pDoc->m_Setting6[DocNo].m_TaskName);
				fprintf(fp,"PracMode\t%d\n",pDoc->m_Setting6[DocNo].m_PracMode);
				fprintf(fp,"ExperMode\t%d\n",pDoc->m_Setting6[DocNo].m_ExperMode);	
				fprintf(fp,"MainTask\t%d\n",pDoc->m_Setting6[DocNo].m_MainTask);
				fprintf(fp,"SubTask\t%d\n",pDoc->m_Setting6[DocNo].m_SubTask);
				fprintf(fp,"Background\t%d\n",pDoc->m_Setting6[DocNo].m_Background);
 				fprintf(fp,"InitSpeed\t%f\n",pDoc->m_Setting6[DocNo].m_InitSpeed);
				fprintf(fp,"CubeNum1\t%d\n",pDoc->m_Setting6[DocNo].m_CubeNum1);
				fprintf(fp,"CubeNum2\t%d\n",pDoc->m_Setting6[DocNo].m_CubeNum2);
				fprintf(fp,"CubeNum3\t%d\n",pDoc->m_Setting6[DocNo].m_CubeNum3);
				fprintf(fp,"CubeNum4\t%d\n",pDoc->m_Setting6[DocNo].m_CubeNum4);
				fprintf(fp,"Prototype\t%d\n",pDoc->m_Setting6[DocNo].m_Prototype);
				fprintf(fp,"RefAxis\t%d\n",pDoc->m_Setting6[DocNo].m_RefAxis);
				fprintf(fp,"MemTaskMode\t%d\n",pDoc->m_Setting6[DocNo].m_MemTaskMode);	
				fprintf(fp,"PracTime\t%d\n",pDoc->m_Setting6[DocNo].m_PracTime);
				fprintf(fp,"ExperTime\t%d\n",pDoc->m_Setting6[DocNo].m_ExperTime);
				fprintf(fp,"PracTimes\t%d\n",pDoc->m_Setting6[DocNo].m_PracTimes);
				fprintf(fp,"ExperTimes\t%d\n",pDoc->m_Setting6[DocNo].m_ExperTimes);
				fprintf(fp,"JoyMoveDirection\t%d\n",pDoc->m_Setting6[DocNo].m_iJoyMoveDirection);
				fprintf(fp,"SubTaskInterval\t%d\n",pDoc->m_Setting6[DocNo].m_iSubTaskInterval);
				fprintf(fp,"PresentTime\t%d\n",pDoc->m_Setting6[DocNo].m_iPresentTime);
				fprintf(fp,"ReactTime\t%d\n",pDoc->m_Setting6[DocNo].m_iReactTime);
				fprintf(fp,"Speed\t%f\n",pDoc->m_Setting6[DocNo].m_Speed);
				fprintf(fp,"SpeedMin\t%f\n",pDoc->m_Setting6[DocNo].m_SpeedMin);
				fprintf(fp,"SpeedMax\t%f\n",pDoc->m_Setting6[DocNo].m_SpeedMax);
				fprintf(fp,"AccelerationMin\t%f\n",pDoc->m_Setting6[DocNo].m_AccelerationMin);
				fprintf(fp,"AccelerationMax\t%f\n",pDoc->m_Setting6[DocNo].m_AccelerationMax);
				fprintf(fp,"SpeedMode\t%d\n",pDoc->m_Setting6[DocNo].m_SpeedMode);
				fprintf(fp,"Direction\t%d\n",pDoc->m_Setting6[DocNo].m_Direction);
	

				fprintf(fp,"\n");
				break;
			case 6:
				fprintf(fp,"[Task7(%s)]\n",pDoc->m_Setting7[DocNo].m_TaskName);
				fprintf(fp,"TaskName\t%d-%s\n",i,pDoc->m_Setting7[DocNo].m_TaskName);
				fprintf(fp,"PracMode\t%d\n",pDoc->m_Setting7[DocNo].m_PracMode);
				fprintf(fp,"ExperMode\t%d\n",pDoc->m_Setting7[DocNo].m_ExperMode);
				fprintf(fp,"SpeedMode\t%d\n",pDoc->m_Setting7[DocNo].m_iSpeedMode);
				fprintf(fp,"BallColorR\t%d\n",pDoc->m_Setting7[DocNo].m_iBallColorR);
				fprintf(fp,"BallColorG\t%d\n",pDoc->m_Setting7[DocNo].m_iBallColorG);
				fprintf(fp,"BallColorB\t%d\n",pDoc->m_Setting7[DocNo].m_iBallColorB);
				fprintf(fp,"BallStartPos\t%d\n",pDoc->m_Setting7[DocNo].m_iBallStartPos);
				fprintf(fp,"BallSpeed\t%d\n",pDoc->m_Setting7[DocNo].m_iBallSpeed);
				fprintf(fp,"BallSpeedAcc\t%d\n",pDoc->m_Setting7[DocNo].m_iBallSpeedAcc);
				fprintf(fp,"BallSpeedMax\t%d\n",pDoc->m_Setting7[DocNo].m_iBallSpeedMax);

				fprintf(fp,"BallRadius\t%d\n",pDoc->m_Setting7[DocNo].m_iBallRadius);
				fprintf(fp,"BckGrndColorR\t%d\n",pDoc->m_Setting7[DocNo].m_iBckGrndColorR);
				fprintf(fp,"BckGrndColorG\t%d\n",pDoc->m_Setting7[DocNo].m_iBckGrndColorG);
				fprintf(fp,"BckGrndColorB\t%d\n",pDoc->m_Setting7[DocNo].m_iBckGrndColorB);
				fprintf(fp,"ObstacleColorR\t%d\n",pDoc->m_Setting7[DocNo].m_iObstacleColorR);
				fprintf(fp,"ObstacleColorG\t%d\n",pDoc->m_Setting7[DocNo].m_iObstacleColorG);
				fprintf(fp,"ObstacleColorB\t%d\n",pDoc->m_Setting7[DocNo].m_iObstacleColorB);
				fprintf(fp,"ObstacleRadius\t%d\n",pDoc->m_Setting7[DocNo].m_iObstacleRadius);
				fprintf(fp,"PracTimes\t%d\n",pDoc->m_Setting7[DocNo].m_iPracTimes);
				fprintf(fp,"ExpTimes\t%d\n",pDoc->m_Setting7[DocNo].m_iExpTimes);
				fprintf(fp,"IntervalTime\t%d\n",pDoc->m_Setting7[DocNo].m_iIntervalTime);
				//fprintf(fp, "\n");
				break;
			}
		}  
		fclose(fp);
	}
}
void CSelectView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
    CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();
	
	m_CurItemNo = 0;
	int i;
	for(i=0;i<7;i++)
	{
//		m_TaskSig[i] = 1;
		m_TaskSet[i] = 0;
	}
	m_SelectedList.ResetContent();

	for(i=0;i<pDoc->m_TaskCount;i++)
	{
		int taskidx = pDoc->m_TaskOrder[i];
		pDoc->m_ItemData[m_CurItemNo].TaskIdx = taskidx;
		int j=0;
		while(pDoc->m_bUsedIdx[taskidx][j])
		{
			j++;
		}
		pDoc->m_ItemData[m_CurItemNo].TaskNo = j;
		pDoc->m_ItemData[m_CurItemNo].bSet = TRUE;
		pDoc->m_bUsedIdx[taskidx][j] = TRUE;
		CString str;
		switch(taskidx)
		{
		case 0:
            str.Format("%s  已设置",pDoc->m_Setting1[pDoc->m_ItemData[m_CurItemNo].TaskNo].m_TaskName);
			break;
		case 1:
			str.Format("%s  已设置",pDoc->m_Setting2[pDoc->m_ItemData[m_CurItemNo].TaskNo].m_TaskName);
			break;
		case 2:
			str.Format("%s  已设置",pDoc->m_Setting3[pDoc->m_ItemData[m_CurItemNo].TaskNo].m_TaskName);
			break;
		case 3:
			str.Format("%s  已设置",pDoc->m_Setting4[pDoc->m_ItemData[m_CurItemNo].TaskNo].m_TaskName);
			break;
		case 4:
			str.Format("%s  已设置",pDoc->m_Setting5[pDoc->m_ItemData[m_CurItemNo].TaskNo].m_TaskName);
			break;
		case 5:
			str.Format("%s  已设置",pDoc->m_Setting6[pDoc->m_ItemData[m_CurItemNo].TaskNo].m_TaskName);
			break;	
		case 6:
			str.Format("%s  已设置",pDoc->m_Setting7[pDoc->m_ItemData[m_CurItemNo].TaskNo].m_TaskName);
			break;		

		}
        int newidx = m_SelectedList.AddString(str);
		m_SelectedList.SetItemData(newidx,m_CurItemNo);
		m_SelectedList.SetCurSel(newidx);
//		m_TaskSig[taskidx] = 0;
		m_CurItemNo++;
		m_SelectedList.SetCurSel(newidx);
//		m_TaskSig[pDoc->m_TaskOrder[i]] = 0;
		m_TaskSet[pDoc->m_TaskOrder[i]] = 1;
	}
	m_TaskList.ResetContent();

	int idx = 0;
	for(i=0;i<7;i++)
	{
		if (i != 3 && i != 4)
		{
			m_TaskList.InsertString(idx, m_TaskItem[i]);
			m_TaskList.SetItemData(idx, i);
			idx++;
		}
		
		

	}
	UpdateData(FALSE);	


	if(!m_bSetting)
	{
		CButton* m_Button;
		m_Button = (CButton*)GetDlgItem(IDC_MAKESURE); 
		m_Button->EnableWindow(TRUE);
	}
	
}

//设置为当前任务设置
void CSelectView::OnMakesure() 
{
	// TODO: Add your control notification handler code here
	CMainFrame*   pMain   =(CMainFrame*)AfxGetMainWnd();
    CTaskControlDoc* pDoc = (CTaskControlDoc*)pMain->GetActiveDocument();
	CTaskControlApp*   pApp =(CTaskControlApp*)AfxGetApp();

	CString str;
	int i;
	pDoc->m_CurTaskCount = m_SelectedList.GetCount();
	for(i=0;i<pDoc->m_CurTaskCount;i++)
	{
		int ItemIdx = m_SelectedList.GetItemData(i);
		pDoc->m_CurTaskOrder[i] = pDoc->m_ItemData[ItemIdx].TaskIdx;
    	if(!m_TaskSet[pDoc->m_CurTaskOrder[i]])
		{
			str.Format("任务%d没有设置！",pDoc->m_CurTaskOrder[i]+1);
			MessageBox(str);
			return;
		}
		switch(pDoc->m_CurTaskOrder[i])
		{
		case 0:
			pDoc->m_TaskName[i] = pDoc->m_Setting1[pDoc->m_ItemData[ItemIdx].TaskNo].m_TaskName;
            pDoc->m_TaskExe[i] = _T("Task1");
			break;
		case 1:
			pDoc->m_TaskName[i] = pDoc->m_Setting2[pDoc->m_ItemData[ItemIdx].TaskNo].m_TaskName;
            pDoc->m_TaskExe[i] = _T("Task2");
			break;
		case 2:
			pDoc->m_TaskName[i] = pDoc->m_Setting3[pDoc->m_ItemData[ItemIdx].TaskNo].m_TaskName;
            if(pDoc->m_Setting3[pDoc->m_ItemData[ItemIdx].TaskNo].m_MainTask)
			{
				if(pDoc->m_Setting3[pDoc->m_ItemData[ItemIdx].TaskNo].m_MainTaskMode == 0)
				{
					pDoc->m_TaskExe[i] = "Task3_1";
				}
				else
				{
					pDoc->m_TaskExe[i] = "Task3_2";
				}
			}
			else
			{
                pDoc->m_TaskExe[i] = "Task3_1";
			}
			break;
		case 3:
			pDoc->m_TaskName[i] = pDoc->m_Setting4[pDoc->m_ItemData[ItemIdx].TaskNo].m_TaskName;
            pDoc->m_TaskExe[i] = _T("Task4");
			break;
		case 4:
			pDoc->m_TaskName[i] = pDoc->m_Setting5[pDoc->m_ItemData[ItemIdx].TaskNo].m_TaskName;
            pDoc->m_TaskExe[i] = _T("Task5");
			break;
		case 5:
			pDoc->m_TaskName[i] = pDoc->m_Setting6[pDoc->m_ItemData[ItemIdx].TaskNo].m_TaskName;
            if(pDoc->m_Setting6[pDoc->m_ItemData[ItemIdx].TaskNo].m_MemTaskMode == 0)
			{
				pDoc->m_TaskExe[i] = "Task6_1";
			}
			else
			{
				pDoc->m_TaskExe[i] = "Task6_2";
			}
			break;
		case 6:
			pDoc->m_TaskName[i] = pDoc->m_Setting7[pDoc->m_ItemData[ItemIdx].TaskNo].m_TaskName;
            pDoc->m_TaskExe[i] = _T("Task7");
			break;
		}
	}	
	//SetCurrentDirectory(g_szExePath);
	_mkdir("Settings");
	CString m_FileName;
	m_FileName = "Settings\\TaskSetting.set";
	SaveSetting(m_FileName);
	m_bSetting = TRUE;

//	for(i=0;i<6;i++)
//	{
//    	pDoc->m_CurTaskExe[i] = pDoc->m_TaskExe[i];
//	}
	CButton* m_Button;
	m_Button = (CButton*)GetDlgItem(IDC_MAKESURE); 
    m_Button->EnableWindow(FALSE);
	

	//循环遍历 若全部设置完毕 就进行保存exe 并提示保存
	pApp->SaveExe(); 
}


void CSelectView::OnDblclkList2()
{
	// TODO: 在此添加控件通知处理程序代码
	OnSetting();
}


void CSelectView::OnLast()
{
	// TODO: 在此添加控件通知处理程序代码
		OnMakesure() ;
	CMainFrame *pWnd=(CMainFrame *)theApp.GetMainWnd();
	CTaskControlDoc* pDoc = (CTaskControlDoc*)pWnd->GetActiveDocument();
	if(strcmp(pDoc->m_CurPartInfo.m_TesterNo,"")==0)
	{
		MessageBox("没有设置，采用系统默认的设置！");
	}

	if (NULL == theApp.SwitchView(TESTER))
		return;

	pDoc->m_PartInfo = pDoc->m_CurPartInfo;
   	pDoc->UpdateAllViews(NULL,1);
}


void CSelectView::OnNext()
{
	// TODO: 在此添加控件通知处理程序代码
   OnMakesure();
	CTaskControlApp*   pApp =(CTaskControlApp*)AfxGetApp();
	CWnd *pwnd=(CWnd *)theApp.m_pMainWnd;
	((CHardView*)pApp->g_pView[HARD])->CenterWindow(pwnd);
	if (NULL == theApp.SwitchView(HARD))
     return;	
}


void CSelectView::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame* active = (CMainFrame *)theApp.GetMainWnd();
	if (active) {
		active->PostMessage(WM_COMMAND,ID_SETTING_OPEN);
	}
}


HBRUSH CSelectView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_EDIT){
		pDC->SetBkColor(RGB(255,255,255));
	}
	return hbr;
}
