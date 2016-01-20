#pragma once
#include "Datatype.h"
#include "Input.h"
#include "resource.h"
#include "stdafx.h"
#include <direct.h>
#include <stdio.h> 
#include <d3d9.h>
#include <d3dx9.h>
#include <time.h>   
#include "RandFcn.h" 
#include "CSky.h"
#include <string>
//#include "..\..\all\resource.h"

#define WM_THREADSTOP (WM_USER+1)

#pragma comment(lib,"User32.lib")


namespace t1
{
	extern FILE *sfp;
	extern CSky sky;
	extern int rtn;//程序返回值
	extern HINSTANCE gHinstance;//全局句柄
	// define a data structure to hold our data ?optional
	extern struct MYDATA {
		int nTime;
		int nNumber;
	};
	extern int g_nThreadExitCount;// = 0;             //当前运行的线程数
	extern DWORD dwInputThreadID;// = 0;              //瞄准器输入线程ID      
	extern double m_PostPointX, m_PostPointY;       //当前瞄准器坐标
	extern int JoyX, JoyY, JoyZ;                     //当前操纵杆输入值     
	extern int post_fai0;                          //操纵杆旋钮初始角度
	extern float alpha, omiga, v, a, b, r, r1, r2, Rx, Ry, fai, post_fai, acce, InitRotateAngle;
	extern float AngleSpeed, RotateAngle;          //当前目标旋转角速度和旋转角度
	extern struct TaskSetting1   m_Setting;        //任务1设置参数
	extern struct HardSetting   m_HardSetting;     //硬件设置参数
	extern struct PartInfo   m_PartInfo;           //被试者信息
	//const short PauseTime[2] = {2,3};
	extern int *m_PauseTimeStart;                  //暂停点时间起始点数组
	extern int *m_PauseTimeEnd;                    //暂停点时间结束点数组
	extern short m_PauseNo;                        //当前暂停点序号         
	extern short m_TrialType;						//测试类型
	extern int m_TrialTime;						//测试时间
	extern int m_TrialTimes;						//测试次数
	extern int iJoyMoveDirection;					//手柄移动方向（正负）
	extern int x_resolution;// = 1024;			//屏幕分辨率
	extern int y_resolution;// = 768;             //屏幕分辨率
	extern int rec_x_begin;
	extern int rec_y_begin;
	extern int rec_x_end;
	extern int rec_y_end;

	extern const float FontScale;// = (float)(x_resolution + y_resolution) / 1400.0;    //字体随屏幕分辨率的放缩尺度

	extern const char Insturction1[];// = "    屏幕上的白色“⊥”是目标，黄色\
																								“⊥”是追踪环。您的任务是：使用操纵杆来控制追踪环的运动，尽可能用追\
																																																踪环套住目标。追踪环套住目标时，追踪环会变成红色。按X键开始任务。”双\
																																																																																手追踪追踪任务的指导语为“屏幕上的白色“⊥”是目标，黄色“⊥”是追\
																																																																																																																								踪环。您的任务是：使用操纵杆来控制追踪环的运动，尽可能用追踪环套住目\
																																																																																																																																																																								标。同时，使用旋钮控制追踪环的姿态，尽可能保持追踪环的姿态与目标一致。\
																																																																																																																																																																																																																																追踪环套住目标时，追踪环会变成红色。按X键开始任务。";
	extern const char Insturction2[];// = "休息一下，按任意键继续！";
	extern const char Insturction3[];// = "练习结束，按任意键进入正式实验。";
	extern const char Insturction4[];// = "该任务完成，按任意键继续！";

	extern LPDIRECT3D9             g_pD3D;// = NULL;		    //directx3d对象
	extern LPDIRECT3DDEVICE9       g_pd3dDevice;// = NULL;		    //directx设备对象
	extern LPDIRECT3DTEXTURE9      g_pTextureInst;// = NULL;	        //纹理对象
	extern LPDIRECT3DTEXTURE9      g_pTexture0;// = NULL;	    	//纹理对象
	extern LPDIRECT3DTEXTURE9      g_pTexture1;// = NULL;            //纹理对象
	extern LPDIRECT3DTEXTURE9      g_pTexture2;// = NULL;            //纹理对象
	extern LPD3DXSPRITE            g_pSprite;// = NULL;              //精灵对象
	extern LPD3DXFONT              g_pFont;// = 0;               //字体对象
	extern LPD3DXFONT              g_pFont1;// = 0;				//字体对象
	extern LPDIRECT3DVERTEXBUFFER9      m_pVertexBuffer;// = NULL;	//顶点对象

	extern D3DXMATRIX m_Transform;                                 //坐标变换矩阵
	extern float TimeInt;                                          //时间间隔
	extern short m_TrialNo;                                        //测试次数序号
	extern BOOL m_bDisplayReady;                                   //渲染设备就绪标志
	extern BOOL m_bObjPause;
	extern short m_Direction;                                      //目标运动方向

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

	extern const double m_MoveInt;// = 0.04;                          //采样间隔40ms
	extern double m_SampleInt;

	extern UINT m_PointNum;
	extern UINT m_MemNum;
	extern BOOL *m_bHit;// = NULL;                //存放击中状态的数组
	extern SPOINT *m_ObjPoint;// = NULL;			//存放目标坐标的数组					
	extern SPOINT *m_PostPoint;// = NULL;         //存放瞄准器坐标的数组
	extern float *m_ObjRotate;// = NULL;          //存放目标旋转角度的数组
	extern float *m_PostRotate;// = NULL;         //存放瞄准器旋转角度的数组
	extern float *m_Distance;// = NULL;			//存放目标和瞄准器距离的数组
	extern float *m_RotateError;// = NULL;        //存放目标和瞄准器角度误差的数组
	extern float *m_ObjSpeedX;// = NULL;          //存放目标速度的数组
	extern float *m_ObjSpeedY;// = NULL;          //存放目标速度的数组
	extern float *m_PostSpeedX;// = NULL;         //存放瞄准器速度的数组
	extern float *m_PostSpeedY;// = NULL;         //存放瞄准器速度的数组
	extern float *m_ObjRotateSpeed;// = NULL;     //存放目标旋转角速度的数组
	extern float *m_PostRotateSpeed;// = NULL;    //存放瞄准器旋转角速度的数组
	//LONGLONG *m_PointTime = NULL;
	extern unsigned long *m_PointTime;// = NULL;  //存放采样时间的数组
	extern RECT strurect, lerect, rerect, erect, txtrect;

	extern short m_TestState;
	extern char m_file[220];
	extern HWND hWnd;
	extern char m_TesterName[40];
	extern char m_DataName[60];
	extern char m_TaskNumStr[100];
	extern int m_Condition;

	//Timer
	extern LARGE_INTEGER litmp;
	extern LONGLONG QPart1, QPart2;
	extern double dfMinus, dfFreq, dfTim, dfTotalPause, dfTotalMove;
	VOID MoveTrace();
	BOOL ReadSetting();
	VOID SaveName();
	VOID SaveData();
	HRESULT InitD3D(HWND hWnd);
	VOID CleanupMem();
	VOID Cleanup();
	VOID Render();
	VOID TestInit();
	BOOL CALLBACK PauseMsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	VOID UpdateState();
	DWORD WINAPI InputThreadProcedure(LPVOID lpStartupParam);
	int APIENTRY _tWinMain(HINSTANCE &hInstance, HINSTANCE &hPrevInstance, LPTSTR &lpCmdLine, int &nCmdShow, HWND &_hWnd, std::string winClassName, std::string winName);
	void hideLastWindow(bool &bUnClosedLastWin, std::string &winClassName, std::string &winName, HINSTANCE &hInstance);
}