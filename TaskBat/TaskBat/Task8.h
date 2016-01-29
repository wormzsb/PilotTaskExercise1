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
	extern float acce;//���ٶ�
	extern int	iDirection;
	extern int g_nThreadExitCount;                      //��ǰ���е��߳���
	extern DWORD dwInputThreadID;                       //��׼�������߳�ID
	extern BOOL m_bCubeNum[4];                              //��άͼ�η�������־

	extern BOOL m_bAcc;                                     //��άͼ�μ�����ȷ�Ա�־
	extern double alpha, omiga, v, a, b, r, Rx, Ry, fai, AngleSpeed, inc_v;
	extern double m_PostPointX, m_PostPointY;                //��ǰ��׼������
	extern int JoyX, JoyY;                                   //��ǰ���ݸ�����ֵ  
	extern struct TaskSetting6   m_Setting;                 //����6���ò���
	extern struct HardSetting   m_HardSetting;              //Ӳ�����ò���
	extern struct PartInfo   m_PartInfo;                    //��������Ϣ
	extern short m_TrialType;                               //��������
	extern int m_TrialTime;                                 //����ʱ��
	extern int m_TrialTimes;                                //����ʱ��
	extern int iJoyMoveDirection;//�ֱ��˶�����������
	extern int x_resolution;			//��Ļ�ֱ���
	extern int y_resolution;             //��Ļ�ֱ���
	extern int rec_x_begin;
	extern int rec_y_begin;
	extern int rec_x_end;
	extern int rec_y_end;
	extern const float FontScale;             //��������Ļ�ֱ��ʵķ����߶�

	extern const char Insturction11[];
	extern const char Insturction12[];
	extern const char Insturction13[];
	extern const char Insturction2[];
	extern const char Insturction3[];
	extern const char FeedBack[2][10];

	extern LPDIRECT3D9             g_pD3D;               //directx3d����
	extern LPDIRECT3DDEVICE9       g_pd3dDevice;               //directx�豸����
	extern LPDIRECT3DTEXTURE9      g_pTextureInst;            //�������
	extern LPDIRECT3DTEXTURE9      g_pTexture0;               //�������
	extern LPDIRECT3DTEXTURE9      g_pTexture1;               //�������
	extern LPDIRECT3DTEXTURE9      g_pTexture2;               //�������
	extern LPDIRECT3DTEXTURE9      g_pTexture3[12];         //�������
	extern LPDIRECT3DTEXTURE9      g_pTexture4;               //�������
	extern LPD3DXSPRITE            g_pSprite;                 //�������
	extern LPD3DXFONT              g_pFont;                  //�������
	extern LPD3DXFONT              g_pFont1;                  //�������
	extern LPD3DXFONT              g_pFont2;                  //�������
	extern LPDIRECT3DVERTEXBUFFER9      m_pVertexBuffer;

	extern D3DXMATRIX m_Transform;                          //����任����
	extern float TimeInt;
	extern short m_SignNo;                                  //��άͼ�μ������
	extern short m_SignOrderNo1, m_SignOrderNo2;            //��άͼ�μ���ϵ�����
	extern short m_SignTrialNo;                             //��άͼ�μ��������
	extern short m_SignGroupNo;                             //��άͼ�μ������
	extern short m_SignCount;                               //��άͼ�μ�����Ŀ
	extern BOOL m_bShowMem;                                 //��������άͼ���ļ���ʾ��־
	extern BOOL m_bLoadSign;                                //��άͼ���ļ����ر�־
	extern BOOL m_bDisplayReady;
	extern struct CUSTOMVERTEX
	{
		FLOAT x, y, z, rhw;
		DWORD color;
	};
	extern BOOL m_bHideSign;						  //�ڵȴ�ʱ��������άͼ��
	extern BOOL m_bRememStart;                               //��άͼ�μ��俪ʼ��־      
	extern BOOL m_bSignStart;                                //��άͼ����ʾ��־
	extern short m_SureDownNum;
	extern int m_SignType[12];                               //��άͼ������
	extern int m_SignOrder1[6];                              //��άͼ������
	extern int m_SignOrder2[6];                              //��άͼ������
	extern unsigned long m_SignStartTime[12];                //��άͼ�μ��俪ʼʱ��
	extern unsigned long m_SignSureTime[12];                 //��άͼ�μ���ȷ��ʱ��
	extern char m_LMemName[30];                              //��Ŵ�������άͼ�����Ƶ�����
	extern char m_RMemName[12][30];                          //��ż�����άͼ�����Ƶ�����
	extern short m_LMemAngle;                                //��Ŵ�������άͼ����ת�Ƕȵ�����
	extern short m_RMemAngle[12];                            //��ż�����άͼ����ת�Ƕȵ�����
	extern short m_MemAngleDiff[12];                         //���������άͼ����ת�ǶȲ������
	extern short m_NoSame[12];                               //�����άͼ����ͬ�Ե�����
	extern short m_SureButtonNo[12];                         //���ȷ�ϰ���������
	extern short m_ButtonDownNum;

	extern int m_CubeNum;
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

	extern const double m_MoveInt;                    //�������40ms

	extern UINT m_PointNum;
	extern UINT m_MemNum;
	extern BOOL *m_bHit;                               //��Ż���״̬������
	extern SPOINT *m_ObjPoint;                         //���Ŀ�����������
	extern SPOINT *m_PostPoint;                        //�����׼�����������
	extern float *m_Distance;                          //���Ŀ�����׼�����������
	extern unsigned long *m_PointTime;                 //��Ų���ʱ�������
	extern float *m_ObjSpeedX;                         //���Ŀ���ٶȵ�����
	extern float *m_ObjSpeedY;                         //���Ŀ���ٶȵ�����
	extern float *m_PostSpeedX;                        //�����׼���ٶȵ�����
	extern float *m_PostSpeedY;                        //�����׼���ٶȵ�����
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

