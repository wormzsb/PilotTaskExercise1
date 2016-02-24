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
	extern int rtn;//程序返回值
	extern HINSTANCE gHinstance;//全局句柄
	extern float acce;  //目标加速度
	extern int g_nThreadExitCount;             //当前运行的线程数
	extern DWORD dwInputThreadID;              //瞄准器输入线程ID      
	extern double alpha, omiga, a, b, r, Rx, Ry, fai, AngleSpeed;
	extern float r1, r2;
	extern short m_TrackState;
	extern POINT A, C;
	extern double v;
	extern double m_PointX, m_PointY;
	extern double m_PostPointX, m_PostPointY;       //当前瞄准器坐标
	extern int JoyX, JoyY;                          //当前操纵杆输入值     
	extern struct TaskSetting2   m_Setting;        //任务2设置参数
	extern struct HardSetting   m_HardSetting;     //硬件设置参数
	extern struct PartInfo   m_PartInfo;           //被试者信息
	extern short m_TrialType;						//测试类型
	extern int m_TrialTime;						//测试时间
	extern int m_TrialTimes;						//测试次数
	extern int iJoyMoveDirection;
	enum TRACE_STATE{ AB, BD, DC, CA, AD, DB, BC, CD, DA, AC, CB, BA };               //目标运动轨迹

	extern int x_resolution;            //屏幕分辨率
	extern int y_resolution;             //屏幕分辨率
	extern const float FontScale;    //字体随屏幕分辨率的放缩尺度

	extern const char Insturction1[];	
	
	extern const char Insturction2[];
	extern const char Insturction3[];
	extern char m_TimeStr[10];                     //保持时间显示字符串
	extern BOOL bShowFeedBack;
	extern LPDIRECT3D9             g_pD3D;             //directx3d对象
	extern LPDIRECT3DDEVICE9       g_pd3dDevice;             //directx设备对象
	extern LPDIRECT3DTEXTURE9      g_pTextureInst;          //纹理对象
	extern LPDIRECT3DTEXTURE9      g_pTexture0;             //纹理对象
	extern LPDIRECT3DTEXTURE9      g_pTexture1;             //纹理对象
	extern LPDIRECT3DTEXTURE9      g_pTexture2;             //纹理对象
	extern LPDIRECT3DTEXTURE9      g_pTexture3;             //纹理对象
	extern LPD3DXSPRITE            g_pSprite;               //精灵对象
	extern LPD3DXFONT              g_pFont;				 //字体对象
	extern LPD3DXFONT              g_pFont1;				 //字体对象
	extern LPD3DXFONT              g_pFontEng;				 //字体对象
	extern LPDIRECT3DVERTEXBUFFER9      m_pVertexBuffer;    //顶点对象
	extern D3DXMATRIX m_Transform;                                  //坐标变换矩阵
	extern float TimeInt;										     //时间间隔
	extern short m_TrialCount;                                      //测试次数
	extern short m_HoldNo;                                          //时间保持序号     
	extern BOOL m_bDisplayReady;								     //渲染设备就绪标志
	extern short m_SureDownNum;
	extern struct CUSTOMVERTEX
	{
		FLOAT x, y, z, rhw;
		DWORD color;
	};
	extern POINT m_IndicatorPoint;                                  //时间保持开始指示器坐标
	extern BOOL m_bHoldStart;                                       //时间保持开始标志
	extern BOOL m_bShowSign;                                        //时间保持开始指示器显示标志
	extern BOOL m_bShowTime;

	extern char FeedBack[30];                                       //呈现反馈字符串

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

	extern const double m_MoveInt;
	extern double m_SampleInt;                                      //采样间隔40ms

	extern UINT m_PointNum;
	extern UINT m_MemNum;
	extern long *m_HoldStartTime;                   //存放时间保持开始时间的数组
	extern long *m_HoldSureTime;                    //存放时间保持确认时间的数组 
	extern int *m_HoldTimeOrder;                             //存放时间保持数值的数组
	extern float *m_HoldTime;                                  //存放保持时间的数组
	extern BOOL *m_bHit;                                     //存放击中状态的数组
	extern SPOINT *m_ObjPoint;                               //存放目标坐标的数组
	extern SPOINT *m_PostPoint;                              //存放瞄准器坐标的数组
	extern unsigned long *m_PointTime;                       //存放采样时间的数组
	extern float *m_Distance;                                //存放目标和瞄准器距离的数组
	extern float *m_ObjSpeedX;                               //存放目标速度的数组
	extern float *m_ObjSpeedY;                               //存放目标速度的数组
	extern float *m_PostSpeedX;                              //存放瞄准器速度的数组
	extern float *m_PostSpeedY;                              //存放瞄准器速度的数组
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
