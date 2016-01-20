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
	extern int rtn;//���򷵻�ֵ
	extern HINSTANCE gHinstance;//ȫ�־��
	// define a data structure to hold our data ?optional
	extern struct MYDATA {
		int nTime;
		int nNumber;
	};
	extern int g_nThreadExitCount;// = 0;             //��ǰ���е��߳���
	extern DWORD dwInputThreadID;// = 0;              //��׼�������߳�ID      
	extern double m_PostPointX, m_PostPointY;       //��ǰ��׼������
	extern int JoyX, JoyY, JoyZ;                     //��ǰ���ݸ�����ֵ     
	extern int post_fai0;                          //���ݸ���ť��ʼ�Ƕ�
	extern float alpha, omiga, v, a, b, r, r1, r2, Rx, Ry, fai, post_fai, acce, InitRotateAngle;
	extern float AngleSpeed, RotateAngle;          //��ǰĿ����ת���ٶȺ���ת�Ƕ�
	extern struct TaskSetting1   m_Setting;        //����1���ò���
	extern struct HardSetting   m_HardSetting;     //Ӳ�����ò���
	extern struct PartInfo   m_PartInfo;           //��������Ϣ
	//const short PauseTime[2] = {2,3};
	extern int *m_PauseTimeStart;                  //��ͣ��ʱ����ʼ������
	extern int *m_PauseTimeEnd;                    //��ͣ��ʱ�����������
	extern short m_PauseNo;                        //��ǰ��ͣ�����         
	extern short m_TrialType;						//��������
	extern int m_TrialTime;						//����ʱ��
	extern int m_TrialTimes;						//���Դ���
	extern int iJoyMoveDirection;					//�ֱ��ƶ�����������
	extern int x_resolution;// = 1024;			//��Ļ�ֱ���
	extern int y_resolution;// = 768;             //��Ļ�ֱ���
	extern int rec_x_begin;
	extern int rec_y_begin;
	extern int rec_x_end;
	extern int rec_y_end;

	extern const float FontScale;// = (float)(x_resolution + y_resolution) / 1400.0;    //��������Ļ�ֱ��ʵķ����߶�

	extern const char Insturction1[];// = "    ��Ļ�ϵİ�ɫ���͡���Ŀ�꣬��ɫ\
																								���͡���׷�ٻ������������ǣ�ʹ�ò��ݸ�������׷�ٻ����˶�����������׷\
																																																�ٻ���סĿ�ꡣ׷�ٻ���סĿ��ʱ��׷�ٻ����ɺ�ɫ����X����ʼ���񡣡�˫\
																																																																																��׷��׷�������ָ����Ϊ����Ļ�ϵİ�ɫ���͡���Ŀ�꣬��ɫ���͡���׷\
																																																																																																																								�ٻ������������ǣ�ʹ�ò��ݸ�������׷�ٻ����˶�����������׷�ٻ���סĿ\
																																																																																																																																																																								�ꡣͬʱ��ʹ����ť����׷�ٻ�����̬�������ܱ���׷�ٻ�����̬��Ŀ��һ�¡�\
																																																																																																																																																																																																																																׷�ٻ���סĿ��ʱ��׷�ٻ����ɺ�ɫ����X����ʼ����";
	extern const char Insturction2[];// = "��Ϣһ�£��������������";
	extern const char Insturction3[];// = "��ϰ�������������������ʽʵ�顣";
	extern const char Insturction4[];// = "��������ɣ��������������";

	extern LPDIRECT3D9             g_pD3D;// = NULL;		    //directx3d����
	extern LPDIRECT3DDEVICE9       g_pd3dDevice;// = NULL;		    //directx�豸����
	extern LPDIRECT3DTEXTURE9      g_pTextureInst;// = NULL;	        //�������
	extern LPDIRECT3DTEXTURE9      g_pTexture0;// = NULL;	    	//�������
	extern LPDIRECT3DTEXTURE9      g_pTexture1;// = NULL;            //�������
	extern LPDIRECT3DTEXTURE9      g_pTexture2;// = NULL;            //�������
	extern LPD3DXSPRITE            g_pSprite;// = NULL;              //�������
	extern LPD3DXFONT              g_pFont;// = 0;               //�������
	extern LPD3DXFONT              g_pFont1;// = 0;				//�������
	extern LPDIRECT3DVERTEXBUFFER9      m_pVertexBuffer;// = NULL;	//�������

	extern D3DXMATRIX m_Transform;                                 //����任����
	extern float TimeInt;                                          //ʱ����
	extern short m_TrialNo;                                        //���Դ������
	extern BOOL m_bDisplayReady;                                   //��Ⱦ�豸������־
	extern BOOL m_bObjPause;
	extern short m_Direction;                                      //Ŀ���˶�����

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

	extern const double m_MoveInt;// = 0.04;                          //�������40ms
	extern double m_SampleInt;

	extern UINT m_PointNum;
	extern UINT m_MemNum;
	extern BOOL *m_bHit;// = NULL;                //��Ż���״̬������
	extern SPOINT *m_ObjPoint;// = NULL;			//���Ŀ�����������					
	extern SPOINT *m_PostPoint;// = NULL;         //�����׼�����������
	extern float *m_ObjRotate;// = NULL;          //���Ŀ����ת�Ƕȵ�����
	extern float *m_PostRotate;// = NULL;         //�����׼����ת�Ƕȵ�����
	extern float *m_Distance;// = NULL;			//���Ŀ�����׼�����������
	extern float *m_RotateError;// = NULL;        //���Ŀ�����׼���Ƕ���������
	extern float *m_ObjSpeedX;// = NULL;          //���Ŀ���ٶȵ�����
	extern float *m_ObjSpeedY;// = NULL;          //���Ŀ���ٶȵ�����
	extern float *m_PostSpeedX;// = NULL;         //�����׼���ٶȵ�����
	extern float *m_PostSpeedY;// = NULL;         //�����׼���ٶȵ�����
	extern float *m_ObjRotateSpeed;// = NULL;     //���Ŀ����ת���ٶȵ�����
	extern float *m_PostRotateSpeed;// = NULL;    //�����׼����ת���ٶȵ�����
	//LONGLONG *m_PointTime = NULL;
	extern unsigned long *m_PointTime;// = NULL;  //��Ų���ʱ�������
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