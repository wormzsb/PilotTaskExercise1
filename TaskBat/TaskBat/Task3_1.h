#pragma once

#include "resource.h"
#include "Datatype.h"
#include <direct.h>
#include <stdio.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <time.h>   
#include <string>   
#include "RandFcn.h" 
#include "Input.h"
#include "resource.h"
#include "Helper.h"
#define WM_THREADSTOP (WM_USER+1)

namespace t3
{
	extern Helper hp;
	extern int rtn; 
	extern HINSTANCE gHinstance; 
	extern char szFeedBack[100]; 
	// define a data structure to hold our data ?optional
	extern struct MYDATA {
		int nTime; 
		int nNumber;
	};
	extern int rangex; 
	extern int iPlaneCnt; 
	extern int	iHelicopterCnt; 
	extern BOOL m_bShowFeedback;//��ʾ����
	extern float acce;	//Ŀ����ٶ�
	extern int iDirection;   //˳��ʱ��
	extern int g_nThreadExitCount;                               //��ǰ���е��߳���
	extern DWORD dwInputThreadID;                                 //��׼�������߳�ID 

	extern double alpha, omiga, v, a, b, r, r1, r2, Rx, Ry, fai, AngleSpeed, inc_v;
	extern double m_PostPointX, m_PostPointY;                           //��ǰ��׼������
	extern int JoyX, JoyY;                                              //��ǰ���ݸ�����ֵ  
	extern struct TaskSetting3   m_Setting;                            //����3���ò���
	extern struct HardSetting   m_HardSetting;                         //Ӳ�����ò���
	extern struct PartInfo   m_PartInfo;                               //��������Ϣ
	extern short m_TrialType;                                          //��������
	extern int m_TrialTime;                                            //����ʱ��
	extern int m_TrialTimes;                                           //���Դ���
	extern int iJoyMoveDirection;  //�ֱ��ƶ�������
	extern int x_resolution;  			//��Ļ�ֱ���
	extern int y_resolution;               //��Ļ�ֱ���
	extern int rec_x_begin;
	extern int rec_y_begin;
	extern int rec_x_end;
	extern int rec_y_end;
	extern const float FontScale;         //��������Ļ�ֱ��ʵķ����߶�

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
	extern LPDIRECT3DTEXTURE9      g_pTexture3[2];          //�������
	extern LPD3DXSPRITE            g_pSprite;                 //�������
	extern LPD3DXFONT              g_pFont;                  //�������
	extern LPD3DXFONT              g_pFont1;                  //�������
	extern LPDIRECT3DVERTEXBUFFER9      m_pVertexBuffer;      //�������

	extern D3DXMATRIX m_Transform;                                    //����任����
	extern float TimeInt;                                             //ʱ���� 
	extern short m_EventNo;                                           //ͻ���¼����
	extern short m_EventCount;                                        //ͻ���¼�����
	extern int m_RecordNo;                                            //ͻ���¼���¼���
	extern short m_EventKeyNum;                                       //ͻ���¼������� 
	extern short m_SureDownNum;
	extern BOOL m_bDisplayReady;                                      //��Ⱦ�豸������־
	extern struct CUSTOMVERTEX
	{
		FLOAT x, y, z, rhw;   
		DWORD color;   
	};  
	extern BOOL m_bEventStart;                                        //ͻ���¼���ʼ��־
	extern BOOL m_bEventReactTime;  									//�Ƿ����ȴ���Ӧʱ���־
	extern int iPlanePos;
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

	extern const double m_MoveInt;                             //�������40ms
	extern double m_SampleInt;
	extern BOOL m_bEventAcc;                                          //����ȷ����ȷ��־

	extern UINT m_PointNum;
	extern UINT m_MemNum, m_MemEvent;

	extern short *m_EventType;                                 //���ͻ���¼����͵�����
	extern int *m_EventOrder;                                  //���ͻ���¼��������е�����
	extern int *m_EventInterval;                               //���ͻ���¼���ʼ���������
	extern unsigned long *m_EventStartTime;                    //���ͻ���¼���ʼʱ������� 
	extern unsigned long *m_EventSureTime;                     //���ͻ���¼�ȷ��ʱ�������
	extern short *m_SureButtonNo;                              //���ͻ���¼�ȷ�ϼ����͵�����
	extern BOOL *m_bHit;                                       //��Ż���״̬������
	extern SPOINT *m_ObjPoint;                                 //���Ŀ�����������
	extern SPOINT *m_PostPoint;                                //�����׼�����������
	extern float *m_Distance;                                  //���Ŀ�����׼�����������
	extern unsigned long *m_PointTime;                         //��Ų���ʱ�������
	extern POINT *m_EventPoint;                                //���ͻ���¼���ʾ���������
	extern float *m_ObjSpeedX;                                 //���Ŀ���ٶȵ�����
	extern float *m_ObjSpeedY;                                 //���Ŀ���ٶȵ�����
	extern float *m_PostSpeedX;                                //�����׼���ٶȵ�����
	extern float *m_PostSpeedY;                                //�����׼���ٶȵ�����
	extern RECT strurect, lerect, rerect, erect, txtrect, coderect;
	extern D3DRECT wcoderect;

	extern short m_TestState;
	extern char m_file1[220];
	extern char m_file2[220];
	extern HWND hWnd;
	extern char m_TesterName[40];
	extern char m_DataName[60];
	extern char m_TaskNumStr[100];
	extern int m_Condition;

	//Timer
	extern LARGE_INTEGER litmp;
	extern LONGLONG QPart0, QPart1, QPart2, QPart3, QPart4;
	extern double dfMinus, dfFreq, dfTim, dfTotal, dfTotalPause, dfTotalEvent;
	VOID MoveTrace();
	BOOL ReadSetting();
	VOID SaveName();
	VOID SaveData();
	HRESULT InitD3D(HWND hWnd);
	VOID CleanupMem();
	VOID Cleanup();
	VOID Render();
	void RandPlanePoint(int cnt, POINT* m_EventInterval);
	void RandEvent();
	VOID TestInit();
	BOOL CALLBACK PauseMsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	VOID UpdateState();
	DWORD WINAPI InputThreadProcedure(LPVOID lpStartupParam);
	int APIENTRY _tWinMain(HINSTANCE &hInstance, HINSTANCE &hPrevInstance, LPTSTR &lpCmdLine, int &nCmdShow, HWND &_hWnd, std::string winClassName, std::string winName);
	void hideLastWindow(bool &bUnClosedLastWin, std::string &winClassName, std::string &winName, HINSTANCE &hInstance);
}