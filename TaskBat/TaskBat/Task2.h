#pragma once

#include "resource.h"
#include "stdafx.h"
#include "Task2.h"
#include "Datatype.h"
#include <direct.h>
#include <stdio.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <time.h>   
#include "RandFcn.h" 
#include "Input.h"
#include "Helper.h"

#define WM_THREADSTOP (WM_USER+1)

#pragma comment(lib,"User32.lib")

namespace t2
{
	extern Helper hp;
	// define a data structure to hold our data ?optional
	extern struct MYDATA {
		int nTime;
		int nNumber;
	};

	extern int iDirection;
	extern int rtn;//���򷵻�ֵ
	extern HINSTANCE gHinstance;//ȫ�־��
	extern float acce;  //Ŀ����ٶ�
	extern int g_nThreadExitCount;             //��ǰ���е��߳���
	extern DWORD dwInputThreadID;              //��׼�������߳�ID      
	extern double alpha, omiga, a, b, r, Rx, Ry, fai, AngleSpeed;
	extern float r1, r2;
	extern short m_TrackState;
	extern POINT A, C;
	extern double v;
	extern double m_PointX, m_PointY;
	extern double m_PostPointX, m_PostPointY;       //��ǰ��׼������
	extern int JoyX, JoyY;                          //��ǰ���ݸ�����ֵ     
	extern struct TaskSetting2   m_Setting;        //����2���ò���
	extern struct HardSetting   m_HardSetting;     //Ӳ�����ò���
	extern struct PartInfo   m_PartInfo;           //��������Ϣ
	extern short m_TrialType;						//��������
	extern int m_TrialTime;						//����ʱ��
	extern int m_TrialTimes;						//���Դ���
	extern int iJoyMoveDirection;
	enum TRACE_STATE{ AB, BD, DC, CA, AD, DB, BC, CD, DA, AC, CB, BA };               //Ŀ���˶��켣

	extern int x_resolution;            //��Ļ�ֱ���
	extern int y_resolution;             //��Ļ�ֱ���
	extern const float FontScale;    //��������Ļ�ֱ��ʵķ����߶�

	extern const char Insturction1[];	
	
	extern const char Insturction2[];
	extern const char Insturction3[];
	extern char m_TimeStr[10];                     //����ʱ����ʾ�ַ���
	extern BOOL bShowFeedBack;
	extern LPDIRECT3D9             g_pD3D;             //directx3d����
	extern LPDIRECT3DDEVICE9       g_pd3dDevice;             //directx�豸����
	extern LPDIRECT3DTEXTURE9      g_pTextureInst;          //�������
	extern LPDIRECT3DTEXTURE9      g_pTexture0;             //�������
	extern LPDIRECT3DTEXTURE9      g_pTexture1;             //�������
	extern LPDIRECT3DTEXTURE9      g_pTexture2;             //�������
	extern LPDIRECT3DTEXTURE9      g_pTexture3;             //�������
	extern LPD3DXSPRITE            g_pSprite;               //�������
	extern LPD3DXFONT              g_pFont;				 //�������
	extern LPD3DXFONT              g_pFont1;				 //�������
	extern LPD3DXFONT              g_pFontEng;				 //�������
	extern LPDIRECT3DVERTEXBUFFER9      m_pVertexBuffer;    //�������
	extern D3DXMATRIX m_Transform;                                  //����任����
	extern float TimeInt;										     //ʱ����
	extern short m_TrialCount;                                      //���Դ���
	extern short m_HoldNo;                                          //ʱ�䱣�����     
	extern BOOL m_bDisplayReady;								     //��Ⱦ�豸������־
	extern short m_SureDownNum;
	extern struct CUSTOMVERTEX
	{
		FLOAT x, y, z, rhw;
		DWORD color;
	};
	extern POINT m_IndicatorPoint;                                  //ʱ�䱣�ֿ�ʼָʾ������
	extern BOOL m_bHoldStart;                                       //ʱ�䱣�ֿ�ʼ��־
	extern BOOL m_bShowSign;                                        //ʱ�䱣�ֿ�ʼָʾ����ʾ��־
	extern BOOL m_bShowTime;

	extern char FeedBack[30];                                       //���ַ����ַ���

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

	extern const double m_MoveInt;
	extern double m_SampleInt;                                      //�������40ms

	extern UINT m_PointNum;
	extern UINT m_MemNum;
	extern long *m_HoldStartTime;                   //���ʱ�䱣�ֿ�ʼʱ�������
	extern long *m_HoldSureTime;                    //���ʱ�䱣��ȷ��ʱ������� 
	extern int *m_HoldTimeOrder;                             //���ʱ�䱣����ֵ������
	extern float *m_HoldTime;                                  //��ű���ʱ�������
	extern BOOL *m_bHit;                                     //��Ż���״̬������
	extern SPOINT *m_ObjPoint;                               //���Ŀ�����������
	extern SPOINT *m_PostPoint;                              //�����׼�����������
	extern unsigned long *m_PointTime;                       //��Ų���ʱ�������
	extern float *m_Distance;                                //���Ŀ�����׼�����������
	extern float *m_ObjSpeedX;                               //���Ŀ���ٶȵ�����
	extern float *m_ObjSpeedY;                               //���Ŀ���ٶȵ�����
	extern float *m_PostSpeedX;                              //�����׼���ٶȵ�����
	extern float *m_PostSpeedY;                              //�����׼���ٶȵ�����
	extern RECT strurect, lerect, rerect, erect, txtrect;

	extern short m_TestState;
	extern char m_file1[220];
	extern char m_file2[220];
	extern HWND hWnd;
	extern char m_TesterName[40];
	extern char m_DataName[60];
	extern char m_TaskNumStr[100];
	extern int m_Condition;

	extern int rec_x_begin;
	extern int rec_y_begin;
	extern int rec_x_end;
	extern int rec_y_end;

	//Timer
	extern LARGE_INTEGER litmp;
	extern LONGLONG QPart1, QPart2;
	extern double dfMinus, dfFreq, dfTim, dfTotal, dfTotalMove;

	int APIENTRY _tWinMain(HINSTANCE &hInstance, HINSTANCE &hPrevInstance, LPTSTR &lpCmdLine, int &nCmdShow, HWND &_hWnd, std::string winClassName,  std::string winName);
	DWORD WINAPI InputThreadProcedure(LPVOID lpStartupParam);
	VOID UpdateState();
	LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	BOOL CALLBACK PauseMsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	VOID TestInit();
	VOID Render();
	VOID Cleanup();
	VOID CleanupMem();
	HRESULT InitD3D(HWND hWnd);
	VOID SaveData();
	VOID SaveName();
	BOOL ReadSetting();
	VOID MoveTrace();
	void hideLastWindow(bool &bUnClosedLastWin, std::string &winClassName, std::string &winName, HINSTANCE &hInstance);
}
