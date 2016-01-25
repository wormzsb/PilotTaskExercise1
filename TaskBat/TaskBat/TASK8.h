#pragma once

#include "resource.h"
#include "Datatype.h"
#include <direct.h>
#include <string> 
#include <stdio.h> 
#include <d3d9.h>
#include <d3dx9.h>
#include <time.h>   
#include "RandFcn.h" 
#include "Input.h"
#include "..\..\all\Enum.h"
#include <vector>
#define WM_THREADSTOP (WM_USER+1)

namespace t8
{

	extern FILE *sfp;
	extern HINSTANCE gHinstance;//ȫ�־��

								// define a data structure to hold our data ?optional
	extern struct MYDATA {
		int nTime;
		int nNumber;
	};
	extern int g_nThreadExitCount;             //��ǰ���е��߳���
	extern DWORD dwInputThreadID;              //��׼�������߳�ID      
	extern struct Point
	{
		double dX;
		double dY;
	};
	extern double dfMinus, dfMinus1, dfFreq, dfTim, dfdetTim, dfInterval, dfTotalMove;
	extern enum { BALL_INTERVAL, BALL_SHOW, BALL_OUT_SHOW };
	extern int rtn;
	extern int preKeyPress; //��¼��һ���ֱ�����
	extern BOOL bTimeOut;
	extern int iShowState;
	extern char szFeedBack[100];
	extern int iBallStartPos;
	extern int curStartPos;
	extern const char szSpeedMode[][100];
	extern BOOL bBtnDown;
	extern BOOL bShowSmallBall;
	extern int iReactTime;

	extern BOOL bBtnStatus;//����״̬

	extern int JoyX, JoyY, JoyZ;                     //��ǰ���ݸ�����ֵ     

	extern struct TaskSetting8  m_Setting;        //����1���ò���
	extern struct PartInfo   m_PartInfo;           //��������Ϣ

	extern short m_TrialType;						//��������
	extern int m_TrialTime;						//����ʱ��
	extern int m_TrialTimes;						//���Դ���
	extern int iTskCnt;						//ʵ���л�����ϰ�Ĵ���ͳ��
	extern int iTotalTskCnt;					//ʵ�����Դ�

	extern int m_TrialGroups;
	extern int x_resolution;			//��Ļ�ֱ���
	extern int y_resolution;             //��Ļ�ֱ���
	extern int x_resolution1024;
	extern int y_resolution768;
	extern int rec_x_begin;
	extern int rec_y_begin;
	extern int rec_x_end;
	extern int rec_y_end;

	extern const float FontScale;    //��������Ļ�ֱ��ʵķ����߶�

	extern const char Insturction1[];
	extern const char Insturction2[];
	extern const char Insturction3[];
	extern const char Insturction4[];
	extern LPDIRECT3D9             g_pD3D;		    //directx3d����
	extern LPDIRECT3DDEVICE9       g_pd3dDevice;		    //directx�豸����
	extern LPDIRECT3DTEXTURE9      g_pTextureInst;	        //�������
	extern LPDIRECT3DTEXTURE9      g_1x15a;
	extern LPDIRECT3DTEXTURE9      g_1x15b;
	extern LPDIRECT3DTEXTURE9      g_1x75a;
	extern LPDIRECT3DTEXTURE9      g_1x75b;
	extern LPDIRECT3DTEXTURE9      g_1x135a;
	extern LPDIRECT3DTEXTURE9      g_1x135b;
	extern LPDIRECT3DTEXTURE9      g_1x195a;
	extern LPDIRECT3DTEXTURE9      g_1x195b;
	extern LPDIRECT3DTEXTURE9      g_1z15a;
	extern LPDIRECT3DTEXTURE9      g_1z15b;
	extern LPDIRECT3DTEXTURE9      g_1z75a;
	extern LPDIRECT3DTEXTURE9      g_1z75b;
	extern LPDIRECT3DTEXTURE9      g_1z135a;
	extern LPDIRECT3DTEXTURE9      g_1z135b;
	extern LPDIRECT3DTEXTURE9      g_1z195a;
	extern LPDIRECT3DTEXTURE9      g_1z195b;
	extern LPDIRECT3DTEXTURE9      g_8x15a;
	extern LPDIRECT3DTEXTURE9      g_8x15b;
	extern LPDIRECT3DTEXTURE9      g_8x75a;
	extern LPDIRECT3DTEXTURE9      g_8x75b;
	extern LPDIRECT3DTEXTURE9      g_8x135a;
	extern LPDIRECT3DTEXTURE9      g_8x135b;
	extern LPDIRECT3DTEXTURE9      g_8x195a;
	extern LPDIRECT3DTEXTURE9      g_8x195b;
	extern LPDIRECT3DTEXTURE9      g_8z15a;
	extern LPDIRECT3DTEXTURE9      g_8z15b;
	extern LPDIRECT3DTEXTURE9      g_8z75a;
	extern LPDIRECT3DTEXTURE9      g_8z75b;
	extern LPDIRECT3DTEXTURE9      g_8z135a;
	extern LPDIRECT3DTEXTURE9      g_8z135b;
	extern LPDIRECT3DTEXTURE9      g_8z195a;
	extern LPDIRECT3DTEXTURE9      g_8z195b;
	extern LPDIRECT3DTEXTURE9      g_9x15a;
	extern LPDIRECT3DTEXTURE9      g_9x15b;
	extern LPDIRECT3DTEXTURE9      g_9x75a;
	extern LPDIRECT3DTEXTURE9      g_9x75b;
	extern LPDIRECT3DTEXTURE9      g_9x135a;
	extern LPDIRECT3DTEXTURE9      g_9x135b;
	extern LPDIRECT3DTEXTURE9      g_9x195a;
	extern LPDIRECT3DTEXTURE9      g_9x195b;
	extern LPDIRECT3DTEXTURE9      g_9z15a;
	extern LPDIRECT3DTEXTURE9      g_9z15b;
	extern LPDIRECT3DTEXTURE9      g_9z75a;
	extern LPDIRECT3DTEXTURE9      g_9z75b;
	extern LPDIRECT3DTEXTURE9      g_9z135a;
	extern LPDIRECT3DTEXTURE9      g_9z135b;
	extern LPDIRECT3DTEXTURE9      g_9z195a;
	extern LPDIRECT3DTEXTURE9      g_9z195b;
	extern LPDIRECT3DTEXTURE9      g_cross;
	extern LPDIRECT3DTEXTURE9      g_none_f;
	extern LPDIRECT3DTEXTURE9      g_none_j;
	extern LPDIRECT3DTEXTURE9      g_right_f;
	extern LPDIRECT3DTEXTURE9      g_right_j;
	extern LPDIRECT3DTEXTURE9      g_wrong_f;
	extern LPDIRECT3DTEXTURE9      g_wrong_j;

	extern LPD3DXSPRITE            g_pSprite;              //�������
	extern LPD3DXFONT              g_pFont;               //�������
	extern LPD3DXFONT              g_pFont1;				//�������
	extern LPDIRECT3DVERTEXBUFFER9      m_pVertexBuffer;	//�������

	extern D3DXMATRIX m_Transform;                                 //����任����
	extern float TimeInt;                                          //ʱ����
	extern short m_TrialNo;                                        //���Դ������
	extern BOOL m_bDisplayReady;                                   //��Ⱦ�豸������־


#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

	extern double m_SampleInt;

	extern UINT m_PointNum;
	extern UINT m_MemNum;

	extern RECT strurect, lerect, rerect, erect, txtrect;

	extern short m_TestState;
	extern char m_file[220];
	extern char m_file1[220];
	extern HWND hWnd;
	extern char m_TesterName[40];
	extern char m_DataName[60];
	extern char m_TaskNumStr[100];

	//Timer
	extern LARGE_INTEGER litmp;
	extern LONGLONG QPart1, QPart2, QPart3;
	extern BOOL bXdown, bZdown;
	BOOL ReadSetting();
	VOID SaveName();
	VOID SaveData();
	HRESULT InitD3D(HWND hWnd);
	VOID CleanupMem();
	VOID Cleanup();
	VOID Render();
	VOID TestInit();
	int GetKeyZAxis(void);
	LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void GoToFeedBack();
	void TaskOver();
	VOID UpdateState();
	int APIENTRY _tWinMain(HINSTANCE &hInstance, HINSTANCE &hPrevInstance, LPTSTR &lpCmdLine, int &nCmdShow, HWND &_hWnd, std::string winClassName, std::string winName);
	void hideLastWindow(bool &bUnClosedLastWin, std::string &winClassName, std::string &winName, HINSTANCE &hInstance);
	BOOL CALLBACK PauseMsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
}