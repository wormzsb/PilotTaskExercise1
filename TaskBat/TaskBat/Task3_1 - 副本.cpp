// Task3_1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Task3_1.h"
#include "..\..\all\Datatype.h"
#include <direct.h>
#include <stdio.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <time.h>   
#include "..\..\all\RandFcn.h" 
#include "..\..\all\Input.h"
#include "..\..\all\resource.h"
#define WM_THREADSTOP (WM_USER+1)
int rtn;
HINSTANCE gHinstance;

char szFeedBack[100];
// define a data structure to hold our data ?optional
struct MYDATA {
    int nTime;
    int nNumber;
};
int rangex;
int iPlaneCnt;
int	iHelicopterCnt;
BOOL m_bShowFeedback = FALSE;//显示反馈
float acce = 0;	//目标加速度
int iDirection = 0;  //顺逆时针
int g_nThreadExitCount = 0;                               //当前运行的线程数
DWORD dwInputThreadID = 0;                                //瞄准器输入线程ID 

double alpha,omiga,v,a,b,r,r1,r2,Rx,Ry,fai,AngleSpeed,inc_v;
double m_PostPointX,m_PostPointY;                         //当前瞄准器坐标
int JoyX,JoyY;                                            //当前操纵杆输入值  
struct TaskSetting3   m_Setting;                          //任务3设置参数
struct HardSetting   m_HardSetting;                       //硬件设置参数
struct PartInfo   m_PartInfo;                             //被试者信息
short m_TrialType;                                        //测试类型
int m_TrialTime;                                          //测试时间
int m_TrialTimes;                                         //测试次数
int iJoyMoveDirection;//手柄移动正向反向
int x_resolution=1024;			//屏幕分辨率
int y_resolution=768;             //屏幕分辨率
int rec_x_begin;
int rec_y_begin;
int rec_x_end;
int rec_y_end;
const float FontScale = (float)(x_resolution+y_resolution)/1400.0;       //字体随屏幕分辨率的放缩尺度

const char Insturction11[] = "    欢迎进入目标\
跟踪作业下的突发事件反应任务！在下面的测试中，你需要用右手操纵控制\
杆来完成目标跟踪任务。在跟踪的同时，你需要监测是否有飞机的图形出现，\
一旦出现，则用左手按键做出反应。";
const char Insturction12[] = "    欢迎进入目标跟踪作业下的突发事件反应任务！在下面的测试中，\
你需要用右手操纵控制杆来完成字符编码作业。屏幕正上方会显示编码规则，\
当屏幕中央出现图形的时候，你需要按照这个规则来按击相应字母。在进行编\
码的同时，你需要监测是否有飞机的图形出现，一旦出现，则用左手按键作\
出反应。";
const char Insturction13[] = "    欢迎进入目标跟踪作业下的突发事件反应任务！\
在下面的测试中，你需要用右手完成数字编\
码任务，同时监测是否有飞机的图形出现，则用左手按键作出反应，如果出\
现的是直升飞机的图形，则不需要按键。"; 
const char Insturction2[] = "练习结束，按任意键进入正式实验。";
const char Insturction3[] = "该任务完成，按任意键继续！";
const char FeedBack[2][10] = {"错误","正确"};

LPDIRECT3D9             g_pD3D       = NULL;             //directx3d对象
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL;             //directx设备对象
LPDIRECT3DTEXTURE9      g_pTextureInst  = NULL;          //纹理对象
LPDIRECT3DTEXTURE9      g_pTexture0  = NULL;             //纹理对象
LPDIRECT3DTEXTURE9      g_pTexture1  = NULL;             //纹理对象
LPDIRECT3DTEXTURE9      g_pTexture2  = NULL;             //纹理对象
LPDIRECT3DTEXTURE9      g_pTexture3[2]  = {NULL};        //纹理对象
LPD3DXSPRITE            g_pSprite  = NULL;               //精灵对象
LPD3DXFONT              g_pFont      = 0;                //字体对象
LPD3DXFONT              g_pFont1     = 0;                //字体对象
LPDIRECT3DVERTEXBUFFER9      m_pVertexBuffer  = NULL;    //顶点对象

D3DXMATRIX m_Transform;                                  //坐标变换矩阵
float TimeInt;                                           //时间间隔 
short m_EventNo;                                         //突发事件序号
short m_EventCount;                                      //突发事件总数
int m_RecordNo;                                          //突发事件记录序号
short m_EventKeyNum;                                     //突发事件按键数 
short m_SureDownNum;
BOOL m_bDisplayReady;                                    //渲染设备就绪标志
struct CUSTOMVERTEX
{
    FLOAT x, y, z, rhw; 
    DWORD color;
};
BOOL m_bEventStart;                                      //突发事件开始标志
BOOL m_bEventReactTime = FALSE;									//是否进入等待反应时间标志
int iPlanePos;
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

const double m_MoveInt = 0.04;                           //采样间隔40ms
double m_SampleInt;
BOOL m_bEventAcc;                                        //按键确认正确标志

UINT m_PointNum;
UINT m_MemNum, m_MemEvent;

short *m_EventType = NULL;                               //存放突发事件类型的数组
int *m_EventOrder = NULL;                                //存放突发事件类型序列的数组
int *m_EventInterval = NULL;                             //存放突发事件开始间隔的数组
unsigned long *m_EventStartTime = NULL;                  //存放突发事件开始时间的数组 
unsigned long *m_EventSureTime = NULL;                   //存放突发事件确认时间的数组
short *m_SureButtonNo = NULL;                            //存放突发事件确认键类型的数组
BOOL *m_bHit = NULL;                                     //存放击中状态的数组
SPOINT *m_ObjPoint = NULL;                               //存放目标坐标的数组
SPOINT *m_PostPoint = NULL;                              //存放瞄准器坐标的数组
float *m_Distance = NULL;                                //存放目标和瞄准器距离的数组
unsigned long *m_PointTime = NULL;                       //存放采样时间的数组
POINT *m_EventPoint = NULL;                              //存放突发事件显示坐标的数组
float *m_ObjSpeedX = NULL;                               //存放目标速度的数组
float *m_ObjSpeedY = NULL;                               //存放目标速度的数组
float *m_PostSpeedX = NULL;                              //存放瞄准器速度的数组
float *m_PostSpeedY = NULL;                              //存放瞄准器速度的数组
RECT strurect,lerect,rerect,erect,txtrect,coderect;
D3DRECT wcoderect;

short m_TestState;
char m_file1[220];
char m_file2[220];
HWND hWnd;
char m_TesterName[40];
char m_DataName[60];
char m_TaskNumStr[100];
int m_Condition;

//Timer
LARGE_INTEGER litmp; 
LONGLONG QPart0,QPart1,QPart2,QPart3,QPart4;
double dfMinus, dfFreq, dfTim, dfTotal, dfTotalPause, dfTotalEvent; 

//************************************************
//*计算目标和瞄准器当前的运动状态
//************************************************
VOID MoveTrace()
{
	m_PointNum++;
	if(m_PointNum>=m_MemNum)
	{
		m_MemNum+=1000;
		m_ObjPoint = (SPOINT*)realloc(m_ObjPoint,m_MemNum*sizeof(SPOINT));
     	m_PostPoint = (SPOINT*)realloc(m_PostPoint,m_MemNum*sizeof(SPOINT));		
		m_Distance = (float*)realloc(m_Distance,m_MemNum*sizeof(float));
		m_PointTime = (unsigned long*)realloc(m_PointTime,m_MemNum*sizeof(unsigned long));
	    m_bHit = (BOOL*)realloc(m_bHit,m_MemNum*sizeof(BOOL));
		m_ObjSpeedX = (float*)realloc(m_ObjSpeedX,m_MemNum*sizeof(float));
		m_ObjSpeedY = (float*)realloc(m_ObjSpeedY,m_MemNum*sizeof(float));
		m_PostSpeedX = (float*)realloc(m_PostSpeedX,m_MemNum*sizeof(float));
		m_PostSpeedY = (float*)realloc(m_PostSpeedY,m_MemNum*sizeof(float));
	
	}
	//m_PostSpeedX[m_PointNum] = JoyX;
   // m_PostSpeedY[m_PointNum] = JoyY;
	if (abs(JoyX )> 10)
		m_PostSpeedX[m_PointNum] = JoyX / abs(JoyX) * m_HardSetting.m_JoySpeedMax;
	else
		m_PostSpeedX[m_PointNum] = 0;

	if (abs(JoyY) > 10)
		m_PostSpeedY[m_PointNum] = JoyY / abs(JoyY) * m_HardSetting.m_JoySpeedMax;
	else
		m_PostSpeedY[m_PointNum] = 0;

	//当前点时间
	m_PointTime[m_PointNum] = m_PointTime[m_PointNum-1] + (int)(dfTim*1000);//QPart2/dfFreq*1000;

	//当前追踪环位置
    m_PostPointX = m_PostPointX + iJoyMoveDirection * m_PostSpeedX[m_PointNum-1] * dfTim;
    m_PostPointY = m_PostPointY + iJoyMoveDirection * m_PostSpeedY[m_PointNum-1] * dfTim;
	m_PostPoint[m_PointNum].x = m_PostPointX;
	m_PostPoint[m_PointNum].y = m_PostPointY;
	if(m_PostPoint[m_PointNum].x<0)
	{
		m_PostPointX = 0;
		m_PostPoint[m_PointNum].x = 0;
	}
	else if(m_PostPoint[m_PointNum].x>x_resolution)
	{
		m_PostPointX = x_resolution;
		m_PostPoint[m_PointNum].x = x_resolution;
	}
	if(m_PostPoint[m_PointNum].y<0)
	{
		m_PostPointY = 0;
		m_PostPoint[m_PointNum].y = 0;
	}
	else if(m_PostPoint[m_PointNum].y>y_resolution)
	{
		m_PostPointY = y_resolution;
		m_PostPoint[m_PointNum].y = y_resolution;
	}


	if(m_PostPointX<rec_x_begin)
	{
		m_PostPointX = rec_x_begin;
	}
	else if(m_PostPointX>rec_x_end)
	{
		m_PostPointX = rec_x_end;
	}
	if(m_PostPointY<rec_y_begin)
	{
		m_PostPointY = rec_y_begin;
	}
	else if(m_PostPointY>rec_y_end)
	{
		m_PostPointY = rec_y_end;
	}


	//平移
	alpha = alpha + (float)iDirection* (omiga * dfTim);
	switch(m_Setting.m_iTrack)
	{
	//圆形轨迹
	case 0:			
		if(alpha>2*PI)
		{
			alpha = alpha - 2*PI;
		}
		else if(alpha<0)
		{
			alpha = alpha + 2*PI;
		}
		m_ObjPoint[m_PointNum].x = a + r1 * cos(alpha);
		m_ObjPoint[m_PointNum].y = b - r1 * sin(alpha);   
		break;
	
	//八字形轨迹
	case 1:
		if(alpha>2*PI)
		{
			alpha = alpha - 2*PI;
		}
		else if(alpha<0)
		{
			alpha = alpha + 2*PI;
		}
		if((alpha<=PI/2.0)||(alpha>=PI*3.0/2.0))
		{
			m_ObjPoint[m_PointNum].x = a + r2 + r2 * cos(2*alpha);
			m_ObjPoint[m_PointNum].y = b - r2 * sin(2*alpha); 
		}
		else
		{
			m_ObjPoint[m_PointNum].x = a - r2 - r2 * cos(-2*alpha);
			m_ObjPoint[m_PointNum].y = b + r2 * sin(-2*alpha); 
		}	
		break;
	}

	//计算目标和瞄准器距离
	m_Distance[m_PointNum] = pow(pow((m_ObjPoint[m_PointNum].y-m_PostPoint[m_PointNum].y),2.0)+pow((m_ObjPoint[m_PointNum].x-m_PostPoint[m_PointNum].x),2.0),0.5);
  

	//计算击中状态
	if((m_Distance[m_PointNum]<m_HardSetting.m_DistanceError))
	{
		m_bHit[m_PointNum] = TRUE;
	}
	else
	{
        m_bHit[m_PointNum] = FALSE;
	}

	//计算当前目标速度
	//匀速
	if(m_Setting.m_SpeedMode == 1)
	{
		v = v + acce * dfTim;
		if(v>m_Setting.m_SpeedMax)
		{
			RandValueFloat(m_Setting.m_AccelerationMin, m_Setting.m_AccelerationMax, acce); 
			acce = -acce;
			v = v + acce * dfTim;
		}
		else if(v<=m_Setting.m_SpeedMin)
		{
			RandValueFloat(m_Setting.m_AccelerationMin, m_Setting.m_AccelerationMax, acce); 
			v = v + acce * dfTim;
		}

	}
	if(m_Setting.m_iTrack == 1)
	{
		
		omiga = pow(v*v/(pow(Rx*sin(alpha),(double)2.0)+pow(Ry*cos(alpha),(double)2.0)),(double)0.5);
	}
	else
	{
		omiga = v/r;
	}
	m_ObjSpeedX[m_PointNum] = -v * sin(alpha);
	m_ObjSpeedY[m_PointNum] = -v * cos(alpha);
}

//************************************************
//*读取当前任务设置
//************************************************
BOOL ReadSetting()
{
	FILE *fp;
	char m_PartFile[50];
	//读取被试者信息
	if(strlen(m_TesterName)>0)
	{
		sprintf(m_PartFile, "PartInfo\\%s.txt", m_TesterName);
		fp = fopen(m_PartFile,"rt");
		if(fp!=NULL)
		{
			fscanf(fp,"编号\t%s\n",m_PartInfo.m_TesterNo);
			fscanf(fp,"姓名\t%s\n",m_PartInfo.m_TesterName);
			fscanf(fp,"性别\t%s\n",m_PartInfo.m_TesterSex);
			fscanf(fp,"年龄\t%d\n",&m_PartInfo.m_TesterAge);
			fscanf(fp,"第N次\t%d\n",&m_PartInfo.m_Session);
			fclose(fp);
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
        strcpy(m_PartInfo.m_TesterNo,"unknown");
		strcpy(m_PartInfo.m_TesterName,"unknown");
		strcpy(m_PartInfo.m_TesterSex,"unknown");
		m_PartInfo.m_TesterAge = 0;
		m_PartInfo.m_Session = 1;
	}

	//读取硬件设置
    fp = fopen("Settings\\Hardware.ini","rt");
	if(fp!=NULL)
	{
		fscanf(fp,"JoySpeedMax\t%f\n",&m_HardSetting.m_JoySpeedMax);
		fscanf(fp,"KnobSensitive\t%f\n",&m_HardSetting.m_KnobSensitive);
		fscanf(fp,"DistanceError\t%f\n",&m_HardSetting.m_DistanceError);
		fscanf(fp,"AngleError\t%f\n",&m_HardSetting.m_AngleError);
		fclose(fp);
	}
	else
	{
		return FALSE;
	}

	//读取任务设置
    char m_tmp[500];
	char m_tasknostr[120];
	if(strlen(m_TaskNumStr)==0)
	{
        sprintf(m_tasknostr,"TaskName\t",m_TaskNumStr);
	}
	else
	{
		sprintf(m_tasknostr,"TaskName\t%s\n",m_TaskNumStr);
	}

	fp = fopen("Settings\\TaskSetting.set","rt");
	if(fp!=NULL)
	{
		do
		{
			fgets(m_tmp,500,fp);
		}
		while(strncmp(m_tmp,m_tasknostr,strlen(m_tasknostr))!=0&&(!feof(fp)));
		if(!feof(fp))
		{

			fscanf(fp,"PracMode\t%d\n",&m_Setting.m_PracMode);
			fscanf(fp,"ExperMode\t%d\n",&m_Setting.m_ExperMode);	
			fscanf(fp,"MainTask\t%d\n",&m_Setting.m_MainTask);
			fscanf(fp,"SubTask\t%d\n",&m_Setting.m_SubTask);	
			fscanf(fp,"MainTaskMode\t%d\n",&m_Setting.m_MainTaskMode);	
			fscanf(fp,"Background\t%d\n",&m_Setting.m_Background);
 			fscanf(fp,"InitSpeed\t%f\n",&m_Setting.m_InitSpeed);
			fscanf(fp,"EventMode\t%d\n",&m_Setting.m_EventMode);	
			fscanf(fp,"CodePairMode\t%d\n",&m_Setting.m_CodePairMode);	
			fscanf(fp,"CodePairNum\t%d\n",&m_Setting.m_CodePairNum);	
			fscanf(fp,"DisplayMode\t%d\n",&m_Setting.m_DisplayMode);	
			fscanf(fp,"EventFrequency\t%d\n",&m_Setting.m_EventFrequency);
			fscanf(fp,"PracTime\t%d\n",&m_Setting.m_PracTime);
			fscanf(fp,"ExperTime\t%d\n",&m_Setting.m_ExperTime);
			fscanf(fp,"PracTimes\t%d\n",&m_Setting.m_PracTimes);
			fscanf(fp,"ExperTimes\t%d\n",&m_Setting.m_ExperTimes);
			fscanf(fp,"JoyMoveDirection\t%d\n",&m_Setting.m_iJoyMoveDirection);
			fscanf(fp,"PlanePos\t%d\n",&m_Setting.m_iPlanePos);
			fscanf(fp,"Direction\t%d\n",&m_Setting.m_Direction);
			fscanf(fp,"SpeedMode\t%d\n",&m_Setting.m_SpeedMode);
			fscanf(fp,"Speed\t%f\n",&m_Setting.m_Speed);
			fscanf(fp,"SpeedMin\t%f\n",&m_Setting.m_SpeedMin);
			fscanf(fp,"SpeedMax\t%f\n",&m_Setting.m_SpeedMax);
			fscanf(fp,"AccelerationMin\t%f\n",&m_Setting. m_AccelerationMin);
			fscanf(fp,"AccelerationMax\t%f\n",&m_Setting. m_AccelerationMax);
			fscanf(fp,"Track\t%d\n",&m_Setting. m_iTrack);
			fscanf_s(fp,"Plane\t%d\n",&m_Setting. m_iPlane);
			fscanf_s(fp,"Helicopter\t%d\n",&m_Setting. m_iHelicopter);
			fscanf_s(fp,"PresentTime\t%d\n",&m_Setting.m_iPresentTime);
			fscanf_s(fp,"IntervalMin\t%d\n",&m_Setting.m_iIntervalMin);
			fscanf_s(fp,"IntervalMax\t%d\n",&m_Setting.m_iIntervalMax);
			fscanf_s(fp,"ReactTime\t%d\n",&m_Setting.m_iReactTime);
			fscanf(fp,"\n");

			fclose(fp);
		}
		else
		{
			fclose(fp);
            return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
	return TRUE;
}

//************************************************
//*创建结果数据记录文件
//************************************************
VOID SaveName()
{
	FILE *fp;
	char m_DataDir[60];
	char m_filename1[160];
	char m_filename2[160];

	SYSTEMTIME CurTime;
	GetLocalTime(&CurTime);
	if(strlen(m_DataName)==0)
	{
		sprintf(m_filename1, "T3_1-trace-%d%02d%02d%02d%02d%02d.txt", CurTime.wYear, CurTime.wMonth, CurTime.wDay, CurTime.wHour, CurTime.wMinute, CurTime.wSecond);
		sprintf(m_filename2, "T3_1-event-%d%02d%02d%02d%02d%02d.txt", CurTime.wYear, CurTime.wMonth, CurTime.wDay, CurTime.wHour, CurTime.wMinute, CurTime.wSecond);
	}
	else
	{
		sprintf(m_filename1, "T3_1-trace-%s-%s-%d%02d%02d%02d%02d%02d.txt", m_TaskNumStr, m_DataName, CurTime.wYear, CurTime.wMonth, CurTime.wDay, CurTime.wHour, CurTime.wMinute, CurTime.wSecond);
		sprintf(m_filename2, "T3_1-event-%s-%s-%d%02d%02d%02d%02d%02d.txt", m_TaskNumStr, m_DataName, CurTime.wYear, CurTime.wMonth, CurTime.wDay, CurTime.wHour, CurTime.wMinute, CurTime.wSecond);
	}
	
	if(strlen(m_TesterName)==0)
	{
		sprintf(m_DataDir,"Data");
	}
	else
	{
		sprintf(m_DataDir,"Data\\%s",m_TesterName);	 
	}
	_mkdir(m_DataDir);   
	sprintf(m_file1, "%s\\%s", m_DataDir, m_filename1);
	sprintf(m_file2, "%s\\%s", m_DataDir, m_filename2);

	if(m_Setting.m_MainTask == 1)
	{
		fp = fopen(m_file1,"at");
		fprintf(fp,"ID\tName\tSex\tSession\t"
			"DistanceError\tPracMode\tExperMode\tMainTask\tSubTask\t"
			"MainTaskMode\tBackground\tInitSpeed\tEventMode\tCodePairMode\tCodePairNum\tDisplayMode\tEventFrequency\tPracTime\tExperTime\tPracTimes\tExperTimes\t"
			"Pra_Test\tPointNum\tPointTime\tObjPointX\tObjPointY\tPostPointX\tPostPointY\tDistance\tHit\t"
		    "ObjSpeedX\tObjSpeedY\tPostSpeedX\tPostSpeedY\n");
		fclose(fp);
	}
	if(m_Setting.m_SubTask == 1)
	{
		fp = fopen(m_file2,"at");
		fprintf(fp,"ID\tName\tSex\tSession\t"
			"PracMode\tExperMode\tMainTask\tSubTask\t"
			"MainTaskMode\tBackground\tInitSpeed\tEventMode\tCodePairMode\tCodePairNum\tDisplayMode\tEventFrequency\tPracTime\tExperTime\tPracTimes\tExperTimes\t"
			"Pra_Test\tEventNum\tEventType\tStartTime\tSureTime\tEvent_RT\tButtonNo\tEvent_Acc\n");
		fclose(fp);
	}
}

//************************************************
//*保存结果数据记录文件
//************************************************
VOID SaveData()
{
	FILE *fp;
	BOOL m_bEventAcc;
	int i;

    //保存追踪数据
    if(m_Setting.m_MainTask == 1)
	{
		fp = fopen(m_file1,"at");
		for(i=0;i<m_PointNum;i++)
		{
			fprintf(fp,"%s\t%s\t%s\t%d\t"
				"%.2f\t%d\t%d\t%d\t%d\t"
				"%d\t%d\t%.2f\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t"
				"%d\t%d\t%u\t%d\t%d\t%d\t%d\t%.2f\t%d\t"
				"%.2f\t%.2f\t%.2f\t%.2f\n",
				m_PartInfo.m_TesterNo, m_PartInfo.m_TesterName, m_PartInfo.m_TesterSex, m_PartInfo.m_Session, 
				m_HardSetting.m_DistanceError, m_Setting.m_PracMode, m_Setting.m_ExperMode, m_Setting.m_MainTask, m_Setting.m_SubTask,
				m_Setting.m_MainTaskMode, m_Setting.m_Background, m_Setting.m_InitSpeed, m_Setting.m_EventMode, m_Setting.m_CodePairMode, m_Setting.m_CodePairNum, m_Setting.m_DisplayMode, m_Setting.m_EventFrequency, m_Setting.m_PracTime, m_Setting.m_ExperTime, m_Setting.m_PracTimes, m_Setting.m_ExperTimes, 
				m_TrialType, i+1, m_PointTime[i], m_ObjPoint[i].x, m_ObjPoint[i].y, m_PostPoint[i].x, m_PostPoint[i].y, m_Distance[i], m_bHit[i],
		        m_ObjSpeedX[i], m_ObjSpeedY[i], m_PostSpeedX[i], m_PostSpeedY[i]);
		}
		fclose(fp);
	}
	//保存突发事件数据
	if(m_Setting.m_SubTask == 1)
	{
		fp = fopen(m_file2,"at");
		for(i=0;i<m_RecordNo;i++)
		{
			if(m_Setting.m_EventMode == 0)
			{
				if(((m_EventType[i]==0)||(m_EventType[i]==1))&&(m_SureButtonNo[i]==0))
				{
					m_bEventAcc = TRUE;
				}
				else
				{
					m_bEventAcc = FALSE;
				}
			}
			else
			{
				m_bEventAcc = (m_EventType[i]==m_SureButtonNo[i]);
			}
			fprintf(fp,"%s\t%s\t%s\t%d\t"
				"%d\t%d\t%d\t%d\t"
				"%d\t%d\t%.2f\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t"
				"%d\t%d\t%d\t%u\t%u\t%u\t%d\t%d\n",
				m_PartInfo.m_TesterNo, m_PartInfo.m_TesterName, m_PartInfo.m_TesterSex, m_PartInfo.m_Session, 
				m_Setting.m_PracMode, m_Setting.m_ExperMode, m_Setting.m_MainTask, m_Setting.m_SubTask,
				m_Setting.m_MainTaskMode, m_Setting.m_Background, m_Setting.m_InitSpeed, m_Setting.m_EventMode, m_Setting.m_CodePairMode, m_Setting.m_CodePairNum, m_Setting.m_DisplayMode, m_Setting.m_EventFrequency, m_Setting.m_PracTime, m_Setting.m_ExperTime, m_Setting.m_PracTimes, m_Setting.m_ExperTimes, 
				m_TrialType, i+1,m_EventType[i], m_EventStartTime[i], m_EventSureTime[i],m_EventSureTime[i]-m_EventStartTime[i],m_SureButtonNo[i],m_bEventAcc);		
		} 
		fclose(fp);
	}
}

//************************************************
//*初始化DirectX 3D
//************************************************
HRESULT InitD3D( HWND hWnd )
{
	m_TestState = STATE_DISPLAYINSTURCTION;
    m_bDisplayReady = TRUE;
	m_SureDownNum = 0;
	if(m_Setting.m_PracMode == 1)
	{
		m_TrialType = TRIAL_PRACTICE;
	}
	else
	{
		m_TrialType = TRIAL_EXPERMENT;
	}

	if(m_Setting.m_iJoyMoveDirection == 0)
		iJoyMoveDirection = 1;
	else
		iJoyMoveDirection = -1;
	//材质大小
//	SetRect( &rct, 0, 0, 128, 128 );
    SetRect( &strurect, x_resolution/2-300*FontScale, y_resolution/2-180*FontScale, x_resolution/2+300*FontScale, y_resolution/2+20*FontScale );
    SetRect( &erect, x_resolution/2-300*FontScale, y_resolution/2-100*FontScale, x_resolution/2+300*FontScale, y_resolution/2+100*FontScale );
	SetRect( &txtrect, 0, 0, x_resolution/4, y_resolution/8 );
	SetRect( &coderect, x_resolution/4, y_resolution/8, x_resolution*3/4, y_resolution/4 );
    SetRect( &lerect, x_resolution/2-250*FontScale, y_resolution/2-50*FontScale, x_resolution/2-50*FontScale, y_resolution/2+100*FontScale );
	SetRect( &rerect, x_resolution/2+50*FontScale, y_resolution/2-50*FontScale, x_resolution/2+250*FontScale, y_resolution/2+100*FontScale );
    wcoderect.x1 = x_resolution/4;
	wcoderect.y1 = y_resolution/4;
	wcoderect.x2 = x_resolution*3/4;
	wcoderect.y2 = y_resolution*3/4;

	if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
	{
        return E_FAIL;
	}

    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof(d3dpp) );
    d3dpp.Windowed = TRUE;//FALSE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;//D3DSWAPEFFECT_COPY;//
 //   d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	D3DDISPLAYMODE d3ddm;
    if( FAILED( g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)) )
	{
		return E_FAIL;
	}

	d3dpp.BackBufferWidth = x_resolution;//d3ddm.Width;//
    d3dpp.BackBufferHeight = y_resolution;//d3ddm.Height;//
	d3dpp.BackBufferFormat = d3ddm.Format;

    if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &g_pd3dDevice ) ) )
    {
        return E_FAIL;
    }

    g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

    g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

	//创建精灵
    if( FAILED( D3DXCreateSprite( g_pd3dDevice, &g_pSprite )))
	{
		MessageBox(NULL, "Could not find banana.bmp", "Textures.exe", MB_OK);
		return E_FAIL;
	}

	//加载纹理图片
	if(m_Setting.m_MainTask&&m_Setting.m_SubTask)
	{
		if(m_Setting.m_EventMode == 0)
		{
			if( FAILED( D3DXCreateTextureFromFile( g_pd3dDevice, "Pics\\Inst\\DT_simpleRT_track.jpg", &g_pTextureInst ) ) )
			{
				MessageBox(NULL, "Could not find banana.bmp", "Textures.exe", MB_OK);
				return E_FAIL;
			}
		}
		else
		{
			if( FAILED( D3DXCreateTextureFromFile( g_pd3dDevice, "Pics\\Inst\\DT_selectiveRT_track.jpg", &g_pTextureInst ) ) )
			{
				MessageBox(NULL, "Could not find banana.bmp", "Textures.exe", MB_OK);
				return E_FAIL;
			}
		}
	}
	else if(m_Setting.m_MainTask)
	{
		if( FAILED( D3DXCreateTextureFromFile( g_pd3dDevice, "Pics\\Inst\\ST_tracking.jpg", &g_pTextureInst ) ) )
		{
			MessageBox(NULL, "Could not find banana.bmp", "Textures.exe", MB_OK);
			return E_FAIL;
		}
	}
	else
	{
		if(m_Setting.m_EventMode == 0)
		{
			if( FAILED( D3DXCreateTextureFromFile( g_pd3dDevice, "Pics\\Inst\\ST_simpleRT.jpg", &g_pTextureInst ) ) )
			{
				MessageBox(NULL, "Could not find banana.bmp", "Textures.exe", MB_OK);
				return E_FAIL;
			}
		}
		else
		{
			if( FAILED( D3DXCreateTextureFromFile( g_pd3dDevice, "Pics\\Inst\\ST_selectiveRT.jpg", &g_pTextureInst ) ) )
			{
				MessageBox(NULL, "Could not find banana.bmp", "Textures.exe", MB_OK);
				return E_FAIL;
			}
		}
	}

	if( FAILED( D3DXCreateTextureFromFile( g_pd3dDevice, "Pics\\Task3\\obj_white.bmp", &g_pTexture0 ) ) )
	{
		MessageBox(NULL, "Could not find banana.bmp", "Textures.exe", MB_OK);
		return E_FAIL;
	}
	if( FAILED( D3DXCreateTextureFromFile( g_pd3dDevice, "Pics\\Task3\\post_yellow.bmp", &g_pTexture1 ) ) )
	{
		MessageBox(NULL, "Could not find banana.bmp", "Textures.exe", MB_OK);
		return E_FAIL;
	}
	if( FAILED( D3DXCreateTextureFromFile( g_pd3dDevice, "Pics\\Task3\\post_red.bmp", &g_pTexture2 ) ) )
	{
		MessageBox(NULL, "Could not find banana.bmp", "Textures.exe", MB_OK);
		return E_FAIL;
	}
	if( FAILED( D3DXCreateTextureFromFile( g_pd3dDevice, "Pics\\Task3\\plane.png", &g_pTexture3[0] ) ) )
	{
		MessageBox(NULL, "Could not find banana.bmp", "Textures.exe", MB_OK);
		return E_FAIL;
	}
	if( FAILED( D3DXCreateTextureFromFile( g_pd3dDevice, "Pics\\Task3\\helicopter.png", &g_pTexture3[1] ) ) )
	{
		MessageBox(NULL, "Could not find banana.bmp", "Textures.exe", MB_OK);
		return E_FAIL;
	}

	LOGFONT lf;
	ZeroMemory(&lf,sizeof(LOGFONT));
	strcpy(lf.lfFaceName,"Times New Roman");
	lf.lfHeight = -16;
    if (FAILED(D3DXCreateFont(g_pd3dDevice,30*FontScale,15*FontScale,20,
		                      0,0,GB2312_CHARSET,0,0,0, "宋体", &g_pFont)))
	{
		  return E_FAIL;
	}
	if (FAILED(D3DXCreateFont(g_pd3dDevice,40*FontScale,20*FontScale,20,
		                      0,0,GB2312_CHARSET,0,0,0, "宋体", &g_pFont1)))
	{
		  return E_FAIL;
	}
    g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
//    g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    g_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	SaveName();
    return S_OK;
}

//************************************************
//*释放数组内存
//************************************************
VOID CleanupMem()
{
	if(m_ObjPoint != NULL)
	{
		free(m_ObjPoint);
		m_ObjPoint = NULL;
	}
	if(m_PostPoint != NULL)
	{
		free(m_PostPoint);
		m_PostPoint = NULL;
	}
	if(m_Distance != NULL)
	{
		free(m_Distance);
		m_Distance = NULL;
	}
	if(m_PointTime != NULL)
	{
		free(m_PointTime);
		m_PointTime = NULL;
	}
	if(m_bHit != NULL)
	{
		free(m_bHit);
		m_bHit = NULL;
	}
	if(m_EventType != NULL)
	{
		free(m_EventType);
		m_EventType = NULL;
	}
	if(m_EventStartTime != NULL)
	{
		free(m_EventStartTime);
		m_EventStartTime = NULL;
	}
	if(m_EventSureTime != NULL)
	{
		free(m_EventSureTime);
		m_EventSureTime = NULL;
	}
	if(m_SureButtonNo != NULL)
	{
		free(m_SureButtonNo);
		m_SureButtonNo = NULL;
	}
	if(m_EventOrder != NULL)
	{
		free(m_EventOrder);
		m_EventOrder = NULL;
	}
	if(m_EventInterval != NULL)
	{
		free(m_EventInterval);
		m_EventInterval = NULL;
	}
	if(m_EventPoint != NULL)
	{
		free(m_EventPoint);
		m_EventPoint = NULL;
	}
	if(m_ObjSpeedX != NULL)
	{
		free(m_ObjSpeedX);
		m_ObjSpeedX = NULL;
	}
	if(m_ObjSpeedY != NULL)
	{
		free(m_ObjSpeedY);
		m_ObjSpeedY = NULL;
	}
	if(m_PostSpeedX != NULL)
	{
		free(m_PostSpeedX);
		m_PostSpeedX = NULL;
	}
	if(m_PostSpeedY != NULL)
	{
		free(m_PostSpeedY);
		m_PostSpeedY = NULL;
	}
}

//************************************************
//*释放DirectX对象
//************************************************
VOID Cleanup()
{
	//释放字体对象
	int i;
	if(g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}

  	if(g_pFont1 != NULL)
	{
		g_pFont1->Release();
		g_pFont1 = NULL;
	}
    if( g_pTextureInst!=NULL)
	{
		g_pTextureInst->Release();
		g_pTextureInst = NULL;
	}
	if( g_pTexture0!=NULL)
	{
		g_pTexture0->Release();
		g_pTexture0 = NULL;
	}
	if( g_pTexture1!=NULL)
	{
		g_pTexture1->Release();
		g_pTexture1 = NULL;
	}
	if( g_pTexture2!=NULL)
	{
		g_pTexture2->Release();
		g_pTexture2 = NULL;
	}
	for(i=0;i<2;i++)
	{
		if( g_pTexture3[i]!=NULL)
		{
			g_pTexture3[i]->Release();
			g_pTexture3[i] = NULL;
		}
	}
	if( g_pSprite!=NULL)
	{
		g_pSprite->Release();
		g_pSprite = NULL;
	}
	if(m_pVertexBuffer != NULL)
	{
		m_pVertexBuffer->Release();
		m_pVertexBuffer = NULL;
	}
    if( g_pd3dDevice != NULL ) 
	{
        g_pd3dDevice->Release();
		g_pd3dDevice = NULL;
	}

    if( g_pD3D != NULL )
	{
        g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//************************************************
//*渲染
//************************************************
VOID Render()
{
	switch(m_TestState)
	{
    //呈现指导语，绘制背景
	case STATE_DISPLAYINSTURCTION:
//		g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255,255,255), 0.0f, 0 );
//		break;
	//任务执行过程，绘制背景
	case STATE_DISPLAYOBJ:  
	case STATE_MOVINGOBJ: 
	case STATE_DISPLAYFEEDBACK:
	case STATE_DISPLAYOPTION:
	case STATE_OVER:
		switch(m_Setting.m_Background)
		{
		case BACKGROUND_GRAY:
			g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(48,48,48), 0.0f, 0 );
			break;
		case BACKGROUND_BLACK:
			g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(20,20,70), 0.0f, 0 );
			break;
		case BACKGROUND_STAR:
			g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,255), 0.0f, 0 );
			break;
		}
		break;
	}
	D3DXMATRIX mx;

	//在后台缓冲区绘制图形
	if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
    {
        g_pd3dDevice->SetStreamSource( 0, m_pVertexBuffer, 0, sizeof(CUSTOMVERTEX) );
        g_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX );
//      g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
    	switch(m_TestState)
		{
        //呈现指导语图片
		case STATE_DISPLAYINSTURCTION:
			if ( SUCCEEDED( g_pSprite->Begin(D3DXSPRITE_ALPHABLEND) ) )
			{
				D3DXMatrixTransformation2D(&mx, NULL, 0.0, &D3DXVECTOR2((float)1024/(float)1024,(float)768/(float)1024), &D3DXVECTOR2(0,0), NULL, &D3DXVECTOR2(x_resolution/2,y_resolution/2));
				g_pSprite->SetTransform(&mx);
			    g_pSprite->Draw(g_pTextureInst, NULL, &D3DXVECTOR3(512,512,0), &D3DXVECTOR3(0,0,0), 0xffffffff);
//			g_pFont->DrawText(NULL, Insturction11, -1, &erect,
//				DT_WORDBREAK|DT_NOCLIP|DT_VCENTER, D3DCOLOR_XRGB(255,0,0));
			}
			g_pSprite->End();
			break;
		//任务执行过程
        case STATE_DISPLAYOBJ:  
		case STATE_MOVINGOBJ:     	
			if ( SUCCEEDED( g_pSprite->Begin(D3DXSPRITE_ALPHABLEND) ) )
			{
				//显示追踪目标和瞄准器
                if(m_Setting.m_MainTask == 1)
				{
					D3DXMatrixTransformation2D(&mx, NULL, 0.0, &D3DXVECTOR2((float)128/(float)128,(float)32/(float)32), &D3DXVECTOR2(0,0), 0, &D3DXVECTOR2(m_PostPoint[m_PointNum].x,m_PostPoint[m_PointNum].y));
					g_pSprite->SetTransform(&mx);
					if(m_bHit[m_PointNum])
					{
						g_pSprite->Draw(g_pTexture2, NULL, &D3DXVECTOR3(64,20,0), &D3DXVECTOR3(0,0,0), 0xffffffff);
						
					}
					else
					{
						g_pSprite->Draw(g_pTexture1, NULL, &D3DXVECTOR3(64,20,0), &D3DXVECTOR3(0,0,0), 0xffffffff);
					}	
					D3DXMatrixTransformation2D(&mx, NULL, 0.0, &D3DXVECTOR2((float)64/(float)64,(float)16/(float)16), &D3DXVECTOR2(0,0), 0, &D3DXVECTOR2(m_ObjPoint[m_PointNum].x,m_ObjPoint[m_PointNum].y));
 					g_pSprite->SetTransform(&mx);
					g_pSprite->Draw(g_pTexture0, NULL, &D3DXVECTOR3(32,12,0), &D3DXVECTOR3(0,0,0), 0xffffffff);
				}
				//显示突发事件
                if(m_Setting.m_SubTask == 1)
				{
					if(m_bShowFeedback)
					{
						g_pFont1->DrawText(NULL, szFeedBack, -1, &erect,
						DT_WORDBREAK|DT_NOCLIP|DT_CENTER|DT_VCENTER, D3DCOLOR_XRGB(255,255,255));
					}
					else if(m_bEventStart && !m_bEventReactTime && m_RecordNo < m_Setting.m_ExperTimes)
					{
						D3DXMatrixTransformation2D(&mx, NULL, 0.0, &D3DXVECTOR2((float)128/(float)256,(float)128/(float)256), &D3DXVECTOR2(0,0), 0, &D3DXVECTOR2(m_EventPoint[m_EventNo].x,m_EventPoint[m_EventNo].y));
						g_pSprite->SetTransform(&mx);
						g_pSprite->Draw(g_pTexture3[m_EventType[m_RecordNo]], NULL, &D3DXVECTOR3(128,128,0), &D3DXVECTOR3(0,0,0), 0xffffffff);
					}
					
				}
			}
			g_pSprite->End();
		   	break; 
		//呈现反馈
		case STATE_DISPLAYFEEDBACK:
		
			
			g_pFont1->DrawText(NULL, szFeedBack, -1, &erect,
				DT_WORDBREAK|DT_NOCLIP|DT_CENTER|DT_VCENTER, D3DCOLOR_XRGB(255,255,255));
			break;
		//测试选项
		case STATE_DISPLAYOPTION:  
            g_pFont->DrawText(NULL, Insturction2, -1, &erect,
				DT_WORDBREAK|DT_NOCLIP|DT_CENTER|DT_VCENTER, D3DCOLOR_XRGB(255,255,255));
			break;
		//测试结束
		case STATE_OVER:
            g_pFont1->DrawText(NULL, Insturction3, -1, &erect,
			    DT_WORDBREAK|DT_NOCLIP|DT_CENTER|DT_VCENTER, D3DCOLOR_XRGB(255,255,255));
			break;
		}
        g_pd3dDevice->EndScene();
	}

    g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}
void RandPlanePoint(int cnt,POINT* m_EventInterval)
{
	
	int randPos;
	for (int i = 0; i < cnt; i++)
	{
		randPos = 1 << rand()%4;
		
		while(!(m_Setting.m_iPlanePos & randPos))
		{
			randPos = 1 << rand()%4;
		}

		switch (randPos)
		{
		case LEFT_TOP:
			m_EventPoint[i].x = rec_x_begin + 64;
			m_EventPoint[i].y = rec_y_begin + 64;
			break;
		case RIGHT_TOP:
			m_EventPoint[i].x = rec_x_end - 64;
			m_EventPoint[i].y = rec_y_begin + 64;
			break;
		case RIGHT_BOTTOM:
			m_EventPoint[i].x = rec_x_end - 64;
			m_EventPoint[i].y = rec_y_end - 64;
			break;
		case LEFT_BOTTOM:
			m_EventPoint[i].x = rec_x_begin + 64;
			m_EventPoint[i].y = rec_y_end - 64;
			break;

		}
	}
	


}

void RandEvent()
{
	int i;

	for (i = 0; i < m_Setting.m_ExperTimes; i++)
	{
		if(m_Setting.m_EventMode == 0)
		{
			m_EventType[i] = 0;
		}
		else
		{
			//飞机数量是否用完，用完用直升机
			if (iPlaneCnt == 0)
				break;
			else if (iHelicopterCnt == 0)
				break;
			else
			{
				if(rand()<RAND_MAX/2)
				{
					m_EventType[i] = 0;
					iPlaneCnt--;
				}
				else 
				{
					m_EventType[i] = 1;
					iHelicopterCnt--;

				}						
			}
		}
	
	}


	for (i=i;i < m_Setting.m_ExperTimes; i++)
	{
		if (iPlaneCnt == 0)
			m_EventType[i] = 1;
		else
			m_EventType[i] = 0;
	}
		

}
//************************************************
//*测试任务初始化
//************************************************
VOID TestInit()
{
	rangex =  m_Setting.m_iIntervalMin + rand()%(m_Setting.m_iIntervalMax - m_Setting.m_iIntervalMin + 1);

	if (m_Setting.m_Direction == 0)
		iDirection = 1;
	else
		iDirection = -1;
	
	if (m_Setting.m_SpeedMode == 0)
		v = m_Setting.m_Speed;
	else
	{
		v = m_Setting.m_InitSpeed;
		if(v>m_Setting.m_SpeedMax)
		{
			RandValueFloat(m_Setting.m_AccelerationMin, m_Setting.m_AccelerationMax, acce); 
			acce = -acce;
			v = v + acce * dfTim;
		}
		else if(v<=m_Setting.m_SpeedMin)
		{
			RandValueFloat(m_Setting.m_AccelerationMin, m_Setting.m_AccelerationMax, acce); 
			v = v + acce * dfTim;
		}
		else
			RandValueFloat(m_Setting.m_AccelerationMin, m_Setting.m_AccelerationMax, acce); 
	}

	if(m_Setting.m_MainTask == 1)
	{
		if(m_TrialType == TRIAL_PRACTICE)
		{
			m_TrialTime = m_Setting.m_PracTime;
		}
		else
		{
			m_TrialTime = m_Setting.m_ExperTime;
		}
		a = x_resolution/2;
		b = y_resolution/2;
		r1 = 300;
		r2 = 200;
		Rx = 400;
		Ry = 200;
		alpha = atan(Rx/Ry);
		Rx = 400;
		Ry = 200;
		fai = 0.0;
		
		m_PointNum = 0;
		m_MemNum = 1000;
		m_ObjPoint = (SPOINT*)malloc(m_MemNum*sizeof(SPOINT));
		m_PostPoint = (SPOINT*)malloc(m_MemNum*sizeof(SPOINT));
		m_Distance = (float*)malloc(m_MemNum*sizeof(float));
		m_PointTime = (unsigned long*)malloc(m_MemNum*sizeof(unsigned long)); 
		m_bHit = (BOOL*)malloc(m_MemNum*sizeof(BOOL));
		m_ObjSpeedX = (float*)malloc(m_MemNum*sizeof(float));
		m_ObjSpeedY = (float*)malloc(m_MemNum*sizeof(float));
		m_PostSpeedX = (float*)malloc(m_MemNum*sizeof(float));
		m_PostSpeedY = (float*)malloc(m_MemNum*sizeof(float));
		m_PostPointX = x_resolution/2;
		m_PostPointY = y_resolution/2;
		m_PostPoint[m_PointNum].x = m_PostPointX;
		m_PostPoint[m_PointNum].y = m_PostPointY;
		alpha = 0;
		m_ObjPoint[m_PointNum].x = a + r * cos(alpha);
		m_ObjPoint[m_PointNum].y = b - r * sin(alpha);  
		m_Distance[m_PointNum] = pow(pow((m_ObjPoint[m_PointNum].y-m_PostPoint[m_PointNum].y),2.0)+pow((m_ObjPoint[m_PointNum].x-m_PostPoint[m_PointNum].x),2.0),0.5);
	    m_bHit[m_PointNum] = FALSE;	
		m_ObjSpeedX[m_PointNum] = -v * sin(alpha);
		m_ObjSpeedY[m_PointNum] = -v * cos(alpha);
		JoyX = 0;
		JoyY = 0;
	}
	if(m_Setting.m_SubTask == 1)
	{
		if(m_Setting.m_MainTask == 0)
		{
			if(m_TrialType == TRIAL_PRACTICE)
			{
				m_TrialTime = m_Setting.m_PracTime;
			}
			else
			{
				m_TrialTime = m_Setting.m_ExperTime;
			}
		}
	    m_MemEvent = 100;
		m_EventType = (short*)malloc(m_MemEvent*sizeof(short));
		m_EventStartTime = (unsigned long*)malloc(m_MemEvent*sizeof(unsigned long));
		m_EventSureTime = (unsigned long*)malloc(m_MemEvent*sizeof(unsigned long));
		m_SureButtonNo = (short*)malloc(m_MemEvent*sizeof(short));
		m_EventCount = m_Setting.m_ExperTimes;
	
		if(m_EventCount>0)
		{
			if (m_Setting.m_iPlane == 0 && m_Setting.m_iHelicopter == 0)
				iPlaneCnt = iHelicopterCnt = 1;
			else
			{
				iPlaneCnt  = 1.0 * m_Setting.m_ExperTimes* (m_Setting.m_iPlane) / (m_Setting.m_iPlane + m_Setting.m_iHelicopter);
				iHelicopterCnt= m_Setting.m_ExperTimes - iPlaneCnt;
			}
		

			m_EventOrder = (int*)malloc(m_EventCount*sizeof(int));
			m_EventInterval = (int*)malloc(m_EventCount*sizeof(int));
			m_EventPoint = (POINT*)malloc(m_EventCount*sizeof(POINT));
			//RandEventOrder(m_TrialTime,m_EventCount,m_EventInterval);
			RandEvent();
			RandOrder(m_EventCount,m_EventOrder);
	    	//RandPoint(x_resolution/2-256, y_resolution/2-256, m_EventCount, m_EventPoint);
			RandPlanePoint(m_EventCount, m_EventPoint);

		}
		
		if(m_Setting.m_EventMode == 0)
		{
			m_EventKeyNum = 1;		
		}
		else
		{
			m_EventKeyNum = 2;
		}
		m_EventNo = 0;
    	m_RecordNo = 0;
        if(m_Setting.m_MainTask == 0)
		{
			JoyX = 100;
			JoyY = 100;
		}
	}

	if (m_Setting.m_MainTask == 1)
	{
		switch(m_Setting.m_iTrack)
		{
			case 0:
				alpha = 0;
				m_ObjPoint[m_PointNum].x = a + r1 * cos(alpha);
				m_ObjPoint[m_PointNum].y = b - r1 * sin(alpha);   
				r = r1;
			
	
				break;
	
			case 1:
 				alpha = 0;
				m_ObjPoint[m_PointNum].x = a + r2 + r2 * cos(2*alpha);
				m_ObjPoint[m_PointNum].y = b - r2 * sin(2*alpha); 
				r = r2;
				break;
		}
	
	}
	

	omiga = v/r;
}

//暂停对话框消息循环
BOOL CALLBACK PauseMsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	int wmId = LOWORD(wParam); 
	int wmEvent = HIWORD(wParam); 
	switch( msg )
	{
	case WM_INITDIALOG:
		RECT rect;	
		GetWindowRect(hWnd, &rect);
		SetWindowPos(hWnd, NULL, (x_resolution - rect.right) / 2, (y_resolution - rect.bottom) / 2, rect.right - rect.left, rect.bottom - rect.top,SWP_SHOWWINDOW);
		ShowCursor(TRUE); 
		break;

	case WM_COMMAND:
		switch (wmId) 
		{
		case ID_CONTINUE:
		case ID_NEXT:
		case ID_CANCEL:
			EndDialog(hWnd,wmId);
			break;

		};

		break;

	}

	return DefWindowProc( hWnd, msg, wParam, lParam );
}


//************************************************
//*外部消息处理
//************************************************
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
	{
	case WM_KEYUP:
		switch( wParam )
		{
			//退出键
		case VK_ESCAPE:
			// User wants to leave fullscreen mode
			rtn = DialogBox(gHinstance,MAKEINTRESOURCE(IDD_PAUSE),hWnd,PauseMsgProc);
			switch(rtn)
			{
			case ID_CONTINUE:
				//重新设定时间间隔QPart1
				QueryPerformanceCounter(&litmp);
				QPart1 = litmp.QuadPart;        		
				QPart2 = QPart1;
				//激活父窗口
				SetForegroundWindow(hWnd);
				ShowCursor(FALSE);
				rtn = 0;
				break;
			case ID_NEXT:
			case ID_CANCEL:
				//若在任务中途退出 则保存当前所有实验数据
				if (m_TestState == STATE_MOVINGOBJ)
					SaveData();
				EndDialog(hWnd,rtn);
				PostThreadMessage(dwInputThreadID, WM_THREADSTOP,0,0); 	//退出线程
				m_TestState = STATE_EXIT;
				break;
			}


		}
		return 0;
	case WM_KEYDOWN:
		switch( wParam )
		{
		
		}
		return 0;
		//程序结束消息
	case WM_DESTROY:
		CleanupMem();
		Cleanup();
		//PostQuitMessage( 0 );
		
		PostQuitMessage(rtn);
		m_bDisplayReady = FALSE;
		return 0;
	}

	return DefWindowProc( hWnd, msg, wParam, lParam );
}

//************************************************
//*测试任务执行过程
//************************************************
VOID UpdateState()
{
    switch(m_TestState)
	{
	//呈现指导语
    case STATE_DISPLAYINSTURCTION:  
		break;
    //呈现目标
	case STATE_DISPLAYOBJ:	
		if(abs(JoyX)>30||abs(JoyY)>30)
		{
			if(QueryPerformanceFrequency(&litmp))
			{
				dfFreq = (double)litmp.QuadPart;// 获得计数器的时钟频率
				m_SampleInt = m_MoveInt * dfFreq;
			}
		    QueryPerformanceCounter(&litmp);
			QPart0 = litmp.QuadPart;           // 获得初始值
			QPart1 = QPart0;                   // 获得初始值
			dfTotalEvent = 0;
			dfTotal = 0;
			if(m_Setting.m_MainTask == 1)
			{
				m_PointTime[m_PointNum] = QPart1/dfFreq*1000;
				m_PostSpeedX[m_PointNum] = 0;
	            m_PostSpeedY[m_PointNum] = 0;
			}
            m_TestState = STATE_MOVINGOBJ;
		}
		break;
	//测试任务执行
    case STATE_MOVINGOBJ:
		if(m_EventNo<m_Setting.m_ExperTimes)
        //if(dfTotal<m_TrialTime)
		{
			do
			{
				QueryPerformanceCounter(&litmp);
				QPart2 = litmp.QuadPart;         //获得中止值
				dfMinus = (double)(QPart2-QPart1);
				//dfTim = dfMinus / dfFreq;        // 获得对应的时间值，单位为秒		
			}while(dfMinus<m_SampleInt);
			dfTim = dfMinus / dfFreq;  // 获得对应的时间值，单位为秒
			QPart1 = QPart2;           // 获得初始值
			dfTotalEvent = dfTotalEvent + dfTim;
			dfTotal = dfTotal + dfTim;
			if(m_Setting.m_SubTask == 1 && !m_bShowFeedback)
			{
				if(m_EventNo<m_EventCount)
				{
					//突发事件开始
					if(m_bEventStart)
					{

						if (!m_bEventReactTime)
						{
							if(dfTotalEvent>=m_Setting.m_iPresentTime)
							{
								m_bEventReactTime = TRUE;
								dfTotalEvent = 0;
							}
							
						}
						else
						{
							if (dfTotalEvent >= m_Setting.m_iReactTime)
							{	

								if (m_Setting.m_PracMode == 0)
								{
									m_bEventStart = FALSE;
									dfTotalEvent = 0;
									m_EventSureTime[m_RecordNo] = 0;
									m_SureButtonNo[m_RecordNo] = -1;
									m_EventNo++;
									m_RecordNo++;
									if(m_RecordNo>=m_MemEvent)
									{
										m_MemEvent+=100;
										m_EventType = (short*)realloc(m_EventType,m_MemEvent*sizeof(short));
										m_EventStartTime = (unsigned long*)realloc(m_EventStartTime,m_MemEvent*sizeof(unsigned long));
										m_EventSureTime = (unsigned long*)realloc(m_EventSureTime,m_MemEvent*sizeof(unsigned long));
										m_SureButtonNo = (short*)realloc(m_SureButtonNo,m_MemEvent*sizeof(short));
									}
								
									
								}
								else
								{
									sprintf(szFeedBack,"反应超时");
									m_bShowFeedback = TRUE;
								}
								
								dfTotalEvent = 0;
							}
						
						}

						//持续两秒
        				/*if(dfTotalEvent>=m_Setting.m_iPresentTime )
						{
							//sprintf(szFeedBack,"%s 反应时间为%dms", FeedBack[m_bEventAcc],m_EventSureTime[m_RecordNo] - m_EventStartTime[m_RecordNo]);
							//rangex =  m_Setting.m_iIntervalMin + rand()%(m_Setting.m_iIntervalMax - m_Setting.m_iIntervalMin + 1);
							m_bEventStart = FALSE;
							dfTotalEvent = 0;
							m_EventSureTime[m_RecordNo] = 0;
							m_SureButtonNo[m_RecordNo] = -1;
							m_EventNo++;
							m_RecordNo++;
							if(m_RecordNo>=m_MemEvent)
							{
								m_MemEvent+=100;
								m_EventType = (short*)realloc(m_EventType,m_MemEvent*sizeof(short));
								m_EventStartTime = (unsigned long*)realloc(m_EventStartTime,m_MemEvent*sizeof(unsigned long));
								m_EventSureTime = (unsigned long*)realloc(m_EventSureTime,m_MemEvent*sizeof(unsigned long));
								m_SureButtonNo = (short*)realloc(m_SureButtonNo,m_MemEvent*sizeof(short));
							}
		//					RandValue(4,9,m_EventInterval);
						}

						if (dfTotalEvent >= m_Setting.m_iReactTime)
						{	
								dfTotalEvent = 0;
								m_bEventStart = TRUE;
								m_bEventReactTime = FALSE;
								m_EventStartTime[m_RecordNo] = QPart2/dfFreq*1000;

								if(m_Setting.m_EventMode == 0)
								{
									m_EventType[m_RecordNo] = 0;
								}
								else
								{
									//飞机数量是否用完，用完用直升机
									if (iPlaneCnt == 0)
										m_EventType[m_RecordNo] = 1;
									else if (iHelicopterCnt == 0)
										m_EventType[m_RecordNo] = 0;
									else
									{
										if(rand()<RAND_MAX/2)
										{
											m_EventType[m_RecordNo] = 0;
											iPlaneCnt--;
										}
										else 
										{
											m_EventType[m_RecordNo] = 1;
											iHelicopterCnt--;

										}						
									}
								}
									
						}*/
					}
					else if (dfTotalEvent >= rangex)
					{
						dfTotalEvent = 0;
						m_bEventStart = TRUE;
						m_bEventReactTime = FALSE;
						m_EventStartTime[m_RecordNo] = QPart2/dfFreq*1000;
						

					}
				}
			}
			//计算当前运动状态
			if(m_Setting.m_MainTask == 1)
			{
                MoveTrace();
			}

			
			//显示反馈
			if (m_bShowFeedback)
			{
				if (dfTotalEvent >= 2)
				{
					m_bShowFeedback = FALSE;
					m_bEventStart = FALSE;
					dfTotalEvent = 0;
					m_EventNo++;
					m_RecordNo++;
					if(m_RecordNo>=m_MemEvent)
					{
						m_MemEvent+=100;
						m_EventType = (short*)realloc(m_EventType,m_MemEvent*sizeof(short));
						m_EventStartTime = (unsigned long*)realloc(m_EventStartTime,m_MemEvent*sizeof(unsigned long));
						m_EventSureTime = (unsigned long*)realloc(m_EventSureTime,m_MemEvent*sizeof(unsigned long));
						m_SureButtonNo = (short*)realloc(m_SureButtonNo,m_MemEvent*sizeof(short));
					}
				}	
					
			}

		}
		else
		{
			//保存数据
			SaveData();
			/*if((m_TrialType == TRIAL_PRACTICE)&&(m_Setting.m_ExperMode == 1))
			{
				//呈现正式测试选项
				m_TrialType = TRIAL_EXPERMENT;
				m_TestState = STATE_DISPLAYOPTION;
				CleanupMem();
			}
			else
			{*/
			//测试结束
			QueryPerformanceCounter(&litmp);
			QPart1 = litmp.QuadPart;           // 获得初始值
			TimeInt = 2;
			m_TestState = STATE_OVER;
			//}
		}
		break;
	//呈现反馈
	case STATE_DISPLAYFEEDBACK:
		QueryPerformanceCounter(&litmp);
		QPart4 = litmp.QuadPart;         //获得中止值
		dfMinus = (double)(QPart4-QPart3);
		dfTim = dfMinus / dfFreq;        // 获得对应的时间值，单位为秒	
		//2000ms
		if (dfTim >= TimeInt)
		{
			m_bEventStart = FALSE;
			dfTotalEvent = 0;
			m_EventNo++;
			m_RecordNo++;
			if(m_RecordNo>=m_MemEvent)
			{
				m_MemEvent+=100;
				m_EventType = (short*)realloc(m_EventType,m_MemEvent*sizeof(short));
				m_EventStartTime = (unsigned long*)realloc(m_EventStartTime,m_MemEvent*sizeof(unsigned long));
				m_EventSureTime = (unsigned long*)realloc(m_EventSureTime,m_MemEvent*sizeof(unsigned long));
			    m_SureButtonNo = (short*)realloc(m_SureButtonNo,m_MemEvent*sizeof(short));
			}
			m_TestState = STATE_MOVINGOBJ;
		}	
		break;
	//出现选项框
    case STATE_DISPLAYOPTION:            
		break;
	//测试结束
	case STATE_OVER: 
/*		QueryPerformanceCounter(&litmp);
		QPart2 = litmp.QuadPart;         //获得中止值
		dfMinus = (double)(QPart2-QPart1);
		dfTim = dfMinus / dfFreq;        // 获得对应的时间值，单位为秒	
		//2000ms
		if (dfTim >= TimeInt)
		{
            PostThreadMessage(dwInputThreadID, WM_THREADSTOP,0,0); 	
			m_TestState = STATE_EXIT;
		}*/	
		break;
	//程序退出
    case STATE_EXIT: 
		if (g_nThreadExitCount == 1)
		{
		    SendMessage(hWnd,WM_DESTROY,0,0);
		}
		break;
	default:
		break;
	}
}

//************************************************
//*操纵杆输入线程
//************************************************
DWORD WINAPI InputThreadProcedure(LPVOID lpStartupParam)
{
    // get the data we passed to the thread. Note that we don't have to use this
    // at all if we don't want
    MYDATA* pMyData = (MYDATA*) lpStartupParam;

    // access some imaginary members of MYDATA, which you can define on
    // your own later
    pMyData->nTime = GetCurrentTime(); // imaginary function I created
    pMyData->nNumber = 5;

    // here's the thread's main loop ?kind of like the main loop in WinMain
    MSG msg;
    int i;
    for( ;; )
	{
		//处理外部消息
        if( PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
            GetMessage(&msg, NULL, 0, 0);

            if( msg.message == WM_THREADSTOP )
            break; // only way out of the for( ;; ) loop

            TranslateMessage(&msg);
            DispatchMessage(&msg);
		}
        else
		{	
			if(JoystickUpdate())
			{
				switch(m_TestState)
				{
				case STATE_DISPLAYINSTURCTION:
				case STATE_DISPLAYOPTION:  
					if(m_SureDownNum == 0)
					{
						//呈现开始选项，等待按任意键开始测试
						for(i=0;i<8;i++)
						{
							if(IsButtonDown(KEY_YES))
							{
	//							m_SureDownNum++;
		//						m_EventNo++;
								TestInit();
								m_TestState = STATE_DISPLAYOBJ;
								break;
							}
						}
					}
					break;
				case STATE_DISPLAYOBJ:
				case STATE_MOVINGOBJ:	
					if(m_Setting.m_SubTask == 1)
					{
						if(m_SureDownNum == 0)
						{
							if(m_bEventStart)
							{
								//有突发事件时按键确认
								for(i=0;i<m_EventKeyNum;i++)
								{
									
									if(IsButtonDown(m_EventKey[i]))
									{	
										
										rangex =  m_Setting.m_iIntervalMin + rand()%(m_Setting.m_iIntervalMax - m_Setting.m_iIntervalMin + 1);
										m_EventSureTime[m_RecordNo] = QPart2/dfFreq*1000;
										m_SureButtonNo[m_RecordNo] = m_SureDownType[i];
										if(m_Setting.m_EventMode == 0)
										{
											if(m_SureButtonNo[m_RecordNo]==0)
											{
												m_bEventAcc = TRUE;
											}
											else
											{
												m_bEventAcc = FALSE;
											}
										}
										else
										{
											m_bEventAcc = (m_EventType[m_RecordNo]==m_SureButtonNo[m_RecordNo]);
										}
                                       //确保此函数不被重入，以免修改feedback的值
										if(m_TrialType == TRIAL_PRACTICE && !m_bShowFeedback)
										{
											//练习状态呈现反馈
											sprintf(szFeedBack,"%s 反应时间为%dms", FeedBack[m_bEventAcc],m_EventSureTime[m_RecordNo] - m_EventStartTime[m_RecordNo]);
											QueryPerformanceCounter(&litmp);
											QPart3 = litmp.QuadPart;           // 获得初始值
											TimeInt = 1;

											if (!m_Setting.m_MainTask)
												m_TestState = STATE_DISPLAYFEEDBACK;
											else
												m_bShowFeedback = TRUE;
											dfTotalEvent = 0;
										}
										else if(m_TrialType == TRIAL_EXPERMENT)
										{
											//正式测试状态不呈现反馈
											m_bEventStart = FALSE;
											dfTotalEvent = 0;
											m_EventNo++;
											m_RecordNo++;
											if(m_RecordNo>=m_MemEvent)
											{
												m_MemEvent+=100;
												m_EventType = (short*)realloc(m_EventType,m_MemEvent*sizeof(short));
												m_EventStartTime = (unsigned long*)realloc(m_EventStartTime,m_MemEvent*sizeof(unsigned long));
												m_EventSureTime = (unsigned long*)realloc(m_EventSureTime,m_MemEvent*sizeof(unsigned long));
												m_SureButtonNo = (short*)realloc(m_SureButtonNo,m_MemEvent*sizeof(short));
											}
										}
//										m_SureDownNum++;
										break;
									}
								}
							}
							else
							{
								//没有突发事件时按键确认
								for(i=0;i<m_EventKeyNum;i++)
								{
									if(IsButtonDown(m_EventKey[i]))
									{
										m_EventType[m_RecordNo] = 2;
										m_EventStartTime[m_RecordNo]  = 0;
										m_EventSureTime[m_RecordNo] = QPart2/dfFreq*1000;
										m_SureButtonNo[m_RecordNo] = m_SureDownType[i];
										m_RecordNo++;
										if(m_RecordNo>=m_MemEvent)
										{
											m_MemEvent+=100;
											m_EventType = (short*)realloc(m_EventType,m_MemEvent*sizeof(short));
											m_EventStartTime = (unsigned long*)realloc(m_EventStartTime,m_MemEvent*sizeof(unsigned long));
											m_EventSureTime = (unsigned long*)realloc(m_EventSureTime,m_MemEvent*sizeof(unsigned long));
											m_SureButtonNo = (short*)realloc(m_SureButtonNo,m_MemEvent*sizeof(short));
										}
//										m_SureDownNum++;
										break;
									}
								}
							}
						}
					}
					//测试过程中获得操纵杆输入
	   				if(m_Setting.m_MainTask == 1)
					{
						JoyX = GetXAxis();//GetYAxis();//
						JoyY = GetYAxis();//-GetZAxis();
					}
					break;
				case STATE_OVER: 
					//测试结束，等待按任意键退出
					if(m_SureDownNum == 0)
					{
						for(i=0;i<12;i++)
						{
							if(IsButtonDown(i))
							{
     	 						PostThreadMessage(dwInputThreadID, WM_THREADSTOP,0,0); 	
    							m_TestState = STATE_EXIT;
							}
						}
					}
				    break;
				default:
					break;
				}
				//计算当前被按下键的数量，以确定是否有新的键按下
				m_SureDownNum = 0;
				{
					for(i=0;i<8;i++)
					{
						if(IsButtonDown(m_StartKey[i]))
						{
							m_SureDownNum++;
						}
					}
				}
			}
            // do the task ?add in your own stuff here

            // yield to other threads, because we almost never get messages
            // (note that we may be yielding to WinMain too)
			//以键盘代替操纵杆
			if(JOY == 0)
			{
				if(IsButtonDown(DIK_ESCAPE))
				{
					PostThreadMessage(dwInputThreadID, WM_THREADSTOP,0,0); 	
					m_TestState = STATE_EXIT;
				}
			}    
		}
		Sleep(1);
	}
    g_nThreadExitCount++;
	return 0;
}

//************************************************
//*主程序
//************************************************
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	//获得传递的命令行参数，得到被试着名字和任务编号
	char *pdest;
    int result;
	int pos1;
	pdest = strrchr(lpCmdLine, ' ');
	pos1 = pdest - lpCmdLine;
	if(pos1>0)
	{
		strncpy(m_TaskNumStr, lpCmdLine, pos1);
	}
	else
	{
		strcpy(m_TaskNumStr, "");
	}
	pdest = strrchr(lpCmdLine, '-');
	result = pdest - lpCmdLine;
	if(result>0)
	{
		strncpy(m_TesterName, lpCmdLine+pos1+1, result-pos1-1);
	}
	else
	{
		strcpy(m_TesterName,"");
	}
	if(pos1>0)
	{
		strcpy(m_DataName, lpCmdLine+pos1+1);
	}
	else
	{
        strcpy(m_DataName, "");
	}

    //读取任务设置
	if(!ReadSetting())
	{
        MessageBox(hWnd,"任务设置文件格式错误！","测试任务", MB_OK);
		return 0;
	}

    //注册窗口类
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L, 
                      GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
                      "ClassName", NULL };
    RegisterClassEx( &wc );
	x_resolution=GetSystemMetrics(SM_CXSCREEN); 
	y_resolution=GetSystemMetrics(SM_CYSCREEN); 
	rec_x_begin = (x_resolution - 1024)/2;
	rec_y_begin = (y_resolution - 768)/2;
	rec_x_end = (x_resolution + 1024)/2;
	rec_y_end = (y_resolution + 768)/2;

    //创建窗口
    /*hWnd = CreateWindow( "ClassName", "Task1", 
                              WS_VISIBLE|WS_POPUP, 0, 0, 1024, 768,
                              NULL, NULL, hInstance, NULL );*/

	hWnd = CreateWindow( "ClassName", "Task3", 
    WS_VISIBLE|WS_POPUP, 0, 0, x_resolution, y_resolution,
    NULL, NULL, hInstance, NULL );
  
    //显示主窗口
//	ShowWindow( hWnd, SW_HIDE );
//	UpdateWindow( hWnd );
    
	//创建DirectX设备
    if (FAILED (DirectInput8Create (hInstance, DIRECTINPUT_VERSION, 
        IID_IDirectInput8, 
        (void**) &m_lpkDInput, NULL)))
	{
         return 0;
	}
	float m_JoySpeedMax;
	if(m_HardSetting.m_JoySpeedMax>0)
	{
		m_JoySpeedMax = m_HardSetting.m_JoySpeedMax;
	}
	else
	{
        m_JoySpeedMax = 200;
	}
	//设置操纵杆变化范围
	if (JoystickInit(hWnd, -m_JoySpeedMax, m_JoySpeedMax, 1))
	{
		JoystickUpdate();
	}
	else
	{
		MessageBox(hWnd,"请检查操纵杆连接是否正确！","测试任务", MB_OK);
		return 0;
	}  
	//关闭输入法
	HKL hkl;
    hkl = LoadKeyboardLayout("00000804",KLF_ACTIVATE);  
	if(hkl != NULL)
	{
		ActivateKeyboardLayout(hkl,KLF_SETFORPROCESS);
	}
    ShowCursor(FALSE);

	//创建操纵杆输入线程
	// declare a variable of our data structure to pass to the ThreadProcedure
	MYDATA MyThreadData;
	MyThreadData.nTime = 7509843;
	MyThreadData.nNumber = 39;

	// declare a DWORD to hold our thread's new generated ID

	// actually create and start the thread now!
	// the thread will run until we send it our own WM_THREADSTOP message
	HANDLE h = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE) InputThreadProcedure,
	    (LPVOID) &MyThreadData, NULL, &dwInputThreadID);
//	SetPriorityClass(h,NORMAL_PRIORITY_CLASS);
//	SetThreadPriority(h,THREAD_PRIORITY_ABOVE_NORMAL);
    srand((unsigned)time(NULL)); //初始化随机种子 

	//初始化Direct3D
    if( SUCCEEDED( InitD3D( hWnd ) ) )
    {	
		//进入消息循环
		MSG msg;
		ZeroMemory( &msg, sizeof(msg) );
		while( msg.message!=WM_QUIT )
		{
			if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
			{
				//处理外部消息
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
			else
			{
				//执行测试过程
				UpdateState();			    
				if( m_bDisplayReady )
				{
					//渲染图形
					Render();  
				}
			}
			Sleep(1);
		}
    }
    //注销窗口类
    UnregisterClass( "ClassName", wc.hInstance );
	return rtn;
}