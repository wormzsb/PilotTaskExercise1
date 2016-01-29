#pragma once

#pragma once

#include "resource.h"
#include "Datatype.h"
#include <direct.h>
#include <stdio.h>
#include <d3d9.h>
#include <string>
#include <d3dx9.h>
#include <time.h>   
#include "RandFcn.h" 
#include "Input.h"
#include "resource.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <thread>         // std::thread, std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
using namespace std;

#define WM_THREADSTOP (WM_USER+1)

namespace t8
{

	// define a data structure to hold our data ?optional
	extern struct MYDATA {
		int nTime;
		int nNumber;
	};

	extern int rtn;
	extern HINSTANCE gHinstance;
	extern float acce;//加速度
	extern int	iDirection;
	extern int g_nThreadExitCount;                      //当前运行的线程数
	extern DWORD dwInputThreadID;                       //瞄准器输入线程ID
	extern BOOL m_bCubeNum[4];                              //三维图形方块数标志

	extern BOOL m_bAcc;                                     //三维图形记忆正确性标志
	extern double alpha, omiga, v, a, b, r, Rx, Ry, fai, AngleSpeed, inc_v;
	extern double m_PostPointX, m_PostPointY;                //当前瞄准器坐标
	extern int JoyX, JoyY;                                   //当前操纵杆输入值  
	extern struct TaskSetting6   m_Setting;                 //任务6设置参数
	extern struct HardSetting   m_HardSetting;              //硬件设置参数
	extern struct PartInfo   m_PartInfo;                    //被试者信息
	extern short m_TrialType;                               //测试类型
	extern int m_TrialTime;                                 //测试时间
	extern int m_TrialTimes;                                //测试时间
	extern int iJoyMoveDirection;//手柄运动方向正向反向
	extern int x_resolution;			//屏幕分辨率
	extern int y_resolution;             //屏幕分辨率
	extern int rec_x_begin;
	extern int rec_y_begin;
	extern int rec_x_end;
	extern int rec_y_end;
	extern const float FontScale;             //字体随屏幕分辨率的放缩尺度

	extern const char Insturction11[];
	extern const char Insturction12[];
	extern const char Insturction13[];
	extern const char Insturction2[];
	extern const char Insturction3[];
	extern const char FeedBack[2][10];

	extern LPDIRECT3D9             g_pD3D;               //directx3d对象
	extern LPDIRECT3DDEVICE9       g_pd3dDevice;               //directx设备对象
	extern LPDIRECT3DTEXTURE9      g_pTextureInst;            //纹理对象
	extern LPDIRECT3DTEXTURE9      g_pTexture0;               //纹理对象
	extern LPDIRECT3DTEXTURE9      g_pTexture1;               //纹理对象
	extern LPDIRECT3DTEXTURE9      g_pTexture2;               //纹理对象
	extern LPDIRECT3DTEXTURE9      g_pTexture3[12];         //纹理对象
	extern LPDIRECT3DTEXTURE9      g_pTexture4;               //纹理对象
	extern LPD3DXSPRITE            g_pSprite;                 //精灵对象
	extern LPD3DXFONT              g_pFont;                  //字体对象
	extern LPD3DXFONT              g_pFont1;                  //字体对象
	extern LPD3DXFONT              g_pFont2;                  //字体对象
	extern LPDIRECT3DVERTEXBUFFER9      m_pVertexBuffer;

	extern D3DXMATRIX m_Transform;                          //坐标变换矩阵
	extern float TimeInt;
	extern short m_SignNo;                                  //三维图形记忆序号
	extern short m_SignOrderNo1, m_SignOrderNo2;            //三维图形记忆系列序号
	extern short m_SignTrialNo;                             //三维图形记忆次数号
	extern short m_SignGroupNo;                             //三维图形记忆组号
	extern short m_SignCount;                               //三维图形记忆数目
	extern BOOL m_bShowMem;                                 //待记忆三维图形文件显示标志
	extern BOOL m_bLoadSign;                                //三维图形文件加载标志
	extern BOOL m_bDisplayReady;
	extern struct CUSTOMVERTEX
	{
		FLOAT x, y, z, rhw;
		DWORD color;
	};
	extern BOOL m_bHideSign;						  //在等待时间隐藏三维图形
	extern BOOL m_bRememStart;                               //三维图形记忆开始标志      
	extern BOOL m_bSignStart;                                //三维图形显示标志
	extern short m_SureDownNum;
	extern int m_SignType[12];                               //三维图形类型
	extern int m_SignOrder1[6];                              //三维图形序列
	extern int m_SignOrder2[6];                              //三维图形序列
	extern unsigned long m_SignStartTime[12];                //三维图形记忆开始时间
	extern unsigned long m_SignSureTime[12];                 //三维图形记忆确认时间
	extern char m_LMemName[30];                              //存放待记忆三维图形名称的数组
	extern char m_RMemName[12][30];                          //存放记忆三维图形名称的数组
	extern short m_LMemAngle;                                //存放待记忆三维图形旋转角度的数组
	extern short m_RMemAngle[12];                            //存放记忆三维图形旋转角度的数组
	extern short m_MemAngleDiff[12];                         //存放两边三维图形旋转角度差的数组
	extern short m_NoSame[12];                               //存放三维图形相同性的数组
	extern short m_SureButtonNo[12];                         //存放确认按键的数组
	extern short m_ButtonDownNum;

	extern int m_CubeNum;
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

	extern const double m_MoveInt;                    //采样间隔40ms

	extern UINT m_PointNum;
	extern UINT m_MemNum;
	extern BOOL *m_bHit;                               //存放击中状态的数组
	extern SPOINT *m_ObjPoint;                         //存放目标坐标的数组
	extern SPOINT *m_PostPoint;                        //存放瞄准器坐标的数组
	extern float *m_Distance;                          //存放目标和瞄准器距离的数组
	extern unsigned long *m_PointTime;                 //存放采样时间的数组
	extern float *m_ObjSpeedX;                         //存放目标速度的数组
	extern float *m_ObjSpeedY;                         //存放目标速度的数组
	extern float *m_PostSpeedX;                        //存放瞄准器速度的数组
	extern float *m_PostSpeedY;                        //存放瞄准器速度的数组
	extern RECT strurect, lerect, rerect, erect, txtrect, coderect, charrect[8];
	extern D3DRECT SignRect;

	extern short m_TestState;
	extern char m_file1[220];
	extern char m_file2[220];
	extern HWND hWnd;
	extern char m_TesterName[40];
	extern char m_DataName[60];
	extern char m_TaskNumStr[100];

	//Timer
	extern LARGE_INTEGER litmp;
	extern LONGLONG QPart1, QPart2, QPart3, QPart4;
	extern double dfMinus, dfFreq, dfTim, dfTotalPause, dfTotalMove, dfTotalSign;
	extern bool bShowTime;
	extern int countdown;
	VOID MoveTrace();

	BOOL ReadSetting();
	VOID SaveName();
	VOID SaveTraceData();
	VOID SaveMemoryData();
	HRESULT LoadSignFile();
	VOID TestInit();
	HRESULT InitD3D(HWND hWnd);
	VOID CleanupMem();
	VOID Cleanup();
	VOID Render();
	BOOL CALLBACK PauseMsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	VOID UpdateState();
	int APIENTRY _tWinMain(HINSTANCE &hInstance, HINSTANCE &hPrevInstance, LPTSTR &lpCmdLine, int &nCmdShow, HWND &_hWnd, std::string winClassName, std::string winName);
	void hideLastWindow(bool &bUnClosedLastWin, std::string &winClassName, std::string &winName, HINSTANCE &hInstance);
	void timer(short &state, int presentTime, int countdownTime, int foucusTime, bool &bShowTime);
	void getTexSize(LPDIRECT3DTEXTURE9 texture, int &w, int &h);
	BOOL drawText(string str, int tx, int ty, LPD3DXFONT &g_pFont);

}

