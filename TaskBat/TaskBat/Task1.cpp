// Task1.cpp : Defines the entry point for the application.
//
#include "stdafx.h"
#include "Task1.h"
#include "Datatype.h"
#include <conio.h>
#include <iostream>
using namespace std;
FILE *t1::sfp;
CSky t1::sky;
int t1::rtn;//程序返回值
HINSTANCE t1::gHinstance;//全局句柄
int t1::g_nThreadExitCount = 0;             //当前运行的线程数
DWORD t1::dwInputThreadID = 0;              //瞄准器输入线程ID      
double t1::m_PostPointX, t1::m_PostPointY;       //当前瞄准器坐标
int t1::JoyX, t1::JoyY, t1::JoyZ;                     //当前操纵杆输入值     
int t1::post_fai0;                          //操纵杆旋钮初始角度
float t1::alpha, t1::omiga, t1::v, t1::a, t1::b, t1::r, t1::r1, t1::r2, t1::Rx, t1::Ry, t1::fai, t1::post_fai, t1::acce, t1::InitRotateAngle;
float t1::AngleSpeed, t1::RotateAngle;          //当前目标旋转角速度和旋转角度
struct TaskSetting1   t1::m_Setting;        //任务1设置参数
struct HardSetting   t1::m_HardSetting;     //硬件设置参数
struct PartInfo   t1::m_PartInfo;           //被试者信息
//const short PauseTime[2] = {2,3};
int *t1::m_PauseTimeStart;                  //暂停点时间起始点数组
int *t1::m_PauseTimeEnd;                    //暂停点时间结束点数组
short t1::m_PauseNo;                        //当前暂停点序号         
short t1::m_TrialType;						//测试类型
int t1::m_TrialTime;						//测试时间
int t1::m_TrialTimes;						//测试次数
int t1::iJoyMoveDirection;					//手柄移动方向（正负）
int t1::x_resolution = 1024;			//屏幕分辨率
int t1::y_resolution = 768;             //屏幕分辨率
int t1::rec_x_begin;
int t1::rec_y_begin;
int t1::rec_x_end;
int t1::rec_y_end;

const float t1::FontScale = (float)(t1::x_resolution + t1::y_resolution) / 1400.0;    //字体随屏幕分辨率的放缩尺度

const char t1::Insturction1[] = "    屏幕上的白色“⊥”是目标，黄色\
																																						“⊥”是追踪环。您的任务是：使用操纵杆来控制追踪环的运动，尽可能用追\
																																																																																																																					踪环套住目标。追踪环套住目标时，追踪环会变成红色。按X键开始任务。”双\
																																																																																																																																																																																																																																																																																				手追踪追踪任务的指导语为“屏幕上的白色“⊥”是目标，黄色“⊥”是追\
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																											踪环。您的任务是：使用操纵杆来控制追踪环的运动，尽可能用追踪环套住目\
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																										标。同时，使用旋钮控制追踪环的姿态，尽可能保持追踪环的姿态与目标一致。\
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																									追踪环套住目标时，追踪环会变成红色。按X键开始任务。";
const char t1::Insturction2[] = "休息一下，按任意键继续！";
const char t1::Insturction3[] = "练习结束，按任意键进入正式实验。";
const char t1::Insturction4[] = "该任务完成，按任意键继续！";

LPDIRECT3D9             t1::g_pD3D = NULL;		    //directx3d对象
LPDIRECT3DDEVICE9       t1::g_pd3dDevice = NULL;		    //directx设备对象
LPDIRECT3DTEXTURE9      t1::g_pTextureInst = NULL;	        //纹理对象
LPDIRECT3DTEXTURE9      t1::g_pTexture0 = NULL;	    	//纹理对象
LPDIRECT3DTEXTURE9      t1::g_pTexture1 = NULL;            //纹理对象
LPDIRECT3DTEXTURE9      t1::g_pTexture2 = NULL;            //纹理对象
LPD3DXSPRITE            t1::g_pSprite = NULL;              //精灵对象
LPD3DXFONT              t1::g_pFont = 0;               //字体对象
LPD3DXFONT              t1::g_pFont1 = 0;				//字体对象
LPDIRECT3DVERTEXBUFFER9      t1::m_pVertexBuffer = NULL;	//顶点对象

D3DXMATRIX t1::m_Transform;                                 //坐标变换矩阵
float t1::TimeInt;                                          //时间间隔
short t1::m_TrialNo;                                        //测试次数序号
BOOL t1::m_bDisplayReady;                                   //渲染设备就绪标志
BOOL t1::m_bObjPause;
short t1::m_Direction;

const double t1::m_MoveInt = 0.04;                          //采样间隔40ms
double t1::m_SampleInt;

UINT t1::m_PointNum;
UINT t1::m_MemNum;
BOOL *t1::m_bHit = NULL;                //存放击中状态的数组
SPOINT *t1::m_ObjPoint = NULL;			//存放目标坐标的数组					
SPOINT *t1::m_PostPoint = NULL;         //存放瞄准器坐标的数组
float *t1::m_ObjRotate = NULL;          //存放目标旋转角度的数组
float *t1::m_PostRotate = NULL;         //存放瞄准器旋转角度的数组
float *t1::m_Distance = NULL;			//存放目标和瞄准器距离的数组
float *t1::m_RotateError = NULL;        //存放目标和瞄准器角度误差的数组
float *t1::m_ObjSpeedX = NULL;          //存放目标速度的数组
float *t1::m_ObjSpeedY = NULL;          //存放目标速度的数组
float *t1::m_PostSpeedX = NULL;         //存放瞄准器速度的数组
float *t1::m_PostSpeedY = NULL;         //存放瞄准器速度的数组
float *t1::m_ObjRotateSpeed = NULL;     //存放目标旋转角速度的数组
float *t1::m_PostRotateSpeed = NULL;    //存放瞄准器旋转角速度的数组
//LONGLONG *m_PointTime = NULL;
unsigned long *t1::m_PointTime = NULL;  //存放采样时间的数组
RECT t1::strurect, t1::lerect, t1::rerect, t1::erect, t1::txtrect;

short t1::m_TestState;
char t1::m_file[220];
HWND t1::hWnd;
char t1::m_TesterName[40];
char t1::m_DataName[60];
char t1::m_TaskNumStr[100];
int t1::m_Condition;

//Timer
LARGE_INTEGER t1::litmp;
LONGLONG t1::QPart1, t1::QPart2;
double t1::dfMinus, t1::dfFreq, t1::dfTim, t1::dfTotalPause, t1::dfTotalMove;
	


	
	//************************************************
	//*计算目标和瞄准器当前的运动状态
	//************************************************
	VOID t1::MoveTrace()
	{
		m_PointNum++;
		if (m_PointNum >= m_MemNum)
		{
			m_MemNum += 1000;
			m_ObjPoint = (SPOINT*)realloc(m_ObjPoint, m_MemNum*sizeof(SPOINT));
			m_PostPoint = (SPOINT*)realloc(m_PostPoint, m_MemNum*sizeof(SPOINT));
			m_ObjRotate = (float*)realloc(m_ObjRotate, m_MemNum*sizeof(float));
			m_PostRotate = (float*)realloc(m_PostRotate, m_MemNum*sizeof(float));
			m_Distance = (float*)realloc(m_Distance, m_MemNum*sizeof(float));
			m_RotateError = (float*)realloc(m_RotateError, m_MemNum*sizeof(float));
			m_PointTime = (unsigned long*)realloc(m_PointTime, m_MemNum*sizeof(unsigned long));
			m_bHit = (BOOL*)realloc(m_bHit, m_MemNum*sizeof(BOOL));
			m_ObjSpeedX = (float*)realloc(m_ObjSpeedX, m_MemNum*sizeof(float));
			m_ObjSpeedY = (float*)realloc(m_ObjSpeedY, m_MemNum*sizeof(float));
			m_PostSpeedX = (float*)realloc(m_PostSpeedX, m_MemNum*sizeof(float));
			m_PostSpeedY = (float*)realloc(m_PostSpeedY, m_MemNum*sizeof(float));
			m_ObjRotateSpeed = (float*)realloc(m_ObjRotateSpeed, m_MemNum*sizeof(float));
			m_PostRotateSpeed = (float*)realloc(m_PostRotateSpeed, m_MemNum*sizeof(float));
		}
		//m_PostSpeedX[m_PointNum] = JoyX;
		// m_PostSpeedY[m_PointNum] = JoyY;
		if (abs(JoyX)> 10)
			m_PostSpeedX[m_PointNum] = JoyX / abs(JoyX) * m_HardSetting.m_JoySpeedMax;
		else
			m_PostSpeedX[m_PointNum] = 0;

		if (abs(JoyY) > 10)
			m_PostSpeedY[m_PointNum] = JoyY / abs(JoyY) * m_HardSetting.m_JoySpeedMax;
		else
			m_PostSpeedY[m_PointNum] = 0;

		//当前点时间
		m_PointTime[m_PointNum] = m_PointTime[m_PointNum - 1] + (int)(dfTim * 1000);//QPart2/dfFreq*1000;

		//当前追踪环位置
		double JoyAlpha = 0;//摇杆角度
		//JoyAlpha = atan(fabs((double)(JoyY - m_PostPointY) / (double)(JoyX - m_PostPointX)));//摇杆角度
		if (!(JoyX == 0 && JoyY == 0)) {
			double rJ = sqrt(JoyX * JoyX + JoyY * JoyY);
			double cosJ = (double)JoyX / rJ;
			double sinJ = (double)JoyY / rJ;
			cout << "JoyX = " << JoyX;
			cout << ", JoyY = " << JoyY << endl;
			cout << "cosJ = " << cosJ;
			cout << ", sinJ = " << sinJ << endl;
			cout << " m_PostSpeedX[m_PointNum - 1] = " << m_PostSpeedX[m_PointNum - 1]
				<< ", m_PostSpeedY[m_PointNum - 1] = " << m_PostSpeedY[m_PointNum - 1]
				<< ", dfTim = " << dfTim << endl;
			cout << "old co " << m_PostPointX << ", " << m_PostPointY << endl;
			m_PostPointX = m_PostPointX + /*iJoyMoveDirection **/ cosJ * rJ  * dfTim;
			m_PostPointY = m_PostPointY + /*iJoyMoveDirection **/ sinJ * rJ  * dfTim;
			cout << "new co " << m_PostPointX << ", " << m_PostPointY << endl;
		}
		
		
		m_PostPoint[m_PointNum].x = m_PostPointX;
		m_PostPoint[m_PointNum].y = m_PostPointY;
		if (m_PostPoint[m_PointNum].x<0)
		{
			m_PostPointX = 0;
			m_PostPoint[m_PointNum].x = 0;
		}
		else if (m_PostPoint[m_PointNum].x>x_resolution)
		{
			m_PostPointX = x_resolution;
			m_PostPoint[m_PointNum].x = x_resolution;
		}
		if (m_PostPoint[m_PointNum].y<0)
		{
			m_PostPointY = 0;
			m_PostPoint[m_PointNum].y = 0;
		}
		else if (m_PostPoint[m_PointNum].y>y_resolution)
		{
			m_PostPointY = y_resolution;
			m_PostPoint[m_PointNum].y = y_resolution;
		}

		//	if(m_Setting.m_MoveMode == MODE_MOVEROATE)
	{
		m_PostRotate[m_PointNum] = post_fai;
		m_PostRotateSpeed[m_PointNum - 1] = (m_PostRotate[m_PointNum] - m_PostRotate[m_PointNum - 1]) / dfTim;


	}

		if (m_PostPointX<rec_x_begin)
		{
			m_PostPointX = rec_x_begin;
		}
		else if (m_PostPointX>rec_x_end)
		{
			m_PostPointX = rec_x_end;
		}
		if (m_PostPointY<rec_y_begin)
		{
			m_PostPointY = rec_y_begin;
		}
		else if (m_PostPointY>rec_y_end)
		{
			m_PostPointY = rec_y_end;
		}

		//计算暂停点
		if (m_Setting.m_Pause == 1)
		{
			if (!m_bObjPause)
			{
				if (dfTotalPause >= m_PauseTimeStart[m_PauseNo])
				{
					m_bObjPause = TRUE;
				}
			}
			else
			{
				if (dfTotalPause >= m_PauseTimeEnd[m_PauseNo])
				{
					m_bObjPause = FALSE;
					m_PauseNo++;
				}
			}
		}

		//目标非暂停
		if (!m_bObjPause)
		{
			//平移
			alpha = alpha + (float)m_Direction* (omiga * dfTim);
			switch (m_Setting.m_Track)
			{
				//圆形轨迹
			case TRACK_CIRCLE:
				if (alpha>2 * PI)
				{
					alpha = alpha - 2 * PI;
				}
				else if (alpha<0)
				{
					alpha = alpha + 2 * PI;
				}
				m_ObjPoint[m_PointNum].x = a + r1 * cos(alpha);
				m_ObjPoint[m_PointNum].y = b - r1 * sin(alpha);
				break;
				//椭圆形轨迹
			case TRACK_ELLIPSE:
				if (alpha>2 * PI)
				{
					alpha = alpha - 2 * PI;
				}
				else if (alpha<0)
				{
					alpha = alpha + 2 * PI;
				}
				m_ObjPoint[m_PointNum].x = a + Rx * cos(alpha);
				m_ObjPoint[m_PointNum].y = b - Ry * sin(alpha);
				break;
				//八字形轨迹
			case TRACK_EIGHT:
				if (alpha>2 * PI)
				{
					alpha = alpha - 2 * PI;
				}
				else if (alpha<0)
				{
					alpha = alpha + 2 * PI;
				}
				if ((alpha <= PI / 2.0) || (alpha >= PI*3.0 / 2.0))
				{
					m_ObjPoint[m_PointNum].x = a + r2 + r2 * cos(2 * alpha);
					m_ObjPoint[m_PointNum].y = b - r2 * sin(2 * alpha);
				}
				else
				{
					m_ObjPoint[m_PointNum].x = a - r2 - r2 * cos(-2 * alpha);
					m_ObjPoint[m_PointNum].y = b + r2 * sin(-2 * alpha);
				}
				break;
			}

			//目标旋转
			if (m_Setting.m_MoveMode == MODE_MOVEROATE)
			{
				fai = fai + AngleSpeed * dfTim;
				float NewRotateAngle;
				if (AngleSpeed<0)
				{
					if (fai<RotateAngle)
					{
						fai = RotateAngle;
						RandValueFloat(m_Setting.m_AngleSpeedMin, m_Setting.m_AngleSpeedMax, AngleSpeed);
						RandValueFloat(m_Setting.m_RotateAngleMin, m_Setting.m_RotateAngleMax, NewRotateAngle);
						printf("\nNewRotateAngle = %f\n", NewRotateAngle);
						getchar();
						RotateAngle = NewRotateAngle;
					}
				}
				else
				{
					if (fai>RotateAngle)
					{
						fai = RotateAngle;
						RandValueFloat(m_Setting.m_AngleSpeedMin, m_Setting.m_AngleSpeedMax, AngleSpeed);
						RandValueFloat(m_Setting.m_RotateAngleMin, m_Setting.m_RotateAngleMax, NewRotateAngle);
						printf("\nNewRotateAngle = %f\n", NewRotateAngle);
						getchar();
						AngleSpeed = -AngleSpeed;
						RotateAngle = -NewRotateAngle;
					}
				}
				m_ObjRotateSpeed[m_PointNum] = AngleSpeed;
			}
			else
			{
				m_ObjRotateSpeed[m_PointNum] = 0;
			}
		}
		//目标暂停
		else
		{
			m_ObjPoint[m_PointNum].x = m_ObjPoint[m_PointNum - 1].x;
			m_ObjPoint[m_PointNum].y = m_ObjPoint[m_PointNum - 1].y;
			m_ObjRotateSpeed[m_PointNum] = 0;
		}

		m_ObjRotate[m_PointNum] = fai;

		//计算目标和瞄准器距离
		m_Distance[m_PointNum] = pow(pow((m_ObjPoint[m_PointNum].y - m_PostPoint[m_PointNum].y), 2.0) + pow((m_ObjPoint[m_PointNum].x - m_PostPoint[m_PointNum].x), 2.0), 0.5);
		m_RotateError[m_PointNum] = m_PostRotate[m_PointNum] - m_ObjRotate[m_PointNum];

		//计算击中状态
		if ((m_Distance[m_PointNum]<m_HardSetting.m_DistanceError) && (fabs(m_RotateError[m_PointNum])<m_HardSetting.m_AngleError))
		{
			m_bHit[m_PointNum] = TRUE;
		}
		else
		{
			m_bHit[m_PointNum] = FALSE;
		}

		//计算当前目标速度
		if (!m_bObjPause)
		{
			//匀速
			if (m_Setting.m_SpeedMode == 0)
			{
				/*			//逐级加速
				if(m_Setting.m_Grade == 1)
				{
				if(dfTotalMove>=m_Setting.m_Interval)
				{
				v = v + inc_v;
				//					omiga = omiga + inc_omiga;
				dfTotalMove = 0;
				}
				}*/
			}
			//匀加速
			else
			{
				v = v + acce * dfTim;//m_MoveInt; 
				if (v>m_Setting.m_SpeedMax)
				{
					RandValueFloat(m_Setting.m_AccelerationMin, m_Setting.m_AccelerationMax, acce);
					acce = -acce;
					v = v + acce * dfTim;
				}
				else if (v <= m_Setting.m_SpeedMin)
				{
					RandValueFloat(m_Setting.m_AccelerationMin, m_Setting.m_AccelerationMax, acce);
					v = v + acce * dfTim;
				}
				//			omiga = omiga + a_omiga * dfTim; 
			}
			if (m_Setting.m_Track == TRACK_ELLIPSE)
			{
				//r = pow(pow(((float)m_ObjPoint[m_PointNum].y-b),2)+pow(((float)m_ObjPoint[m_PointNum].x-a),2),0.5);
				omiga = pow(v*v / (pow(Rx*sin(alpha), (float)2.0) + pow(Ry*cos(alpha), (float)2.0)), (float)0.5);
			}
			else
			{
				omiga = v / r;
			}
			m_ObjSpeedX[m_PointNum] = -v * sin(alpha);
			m_ObjSpeedY[m_PointNum] = -v * cos(alpha);
		}
		else
		{
			m_ObjSpeedX[m_PointNum] = 0;
			m_ObjSpeedY[m_PointNum] = 0;
		}
	}

	//************************************************
	//*读取当前任务设置
	//************************************************
	BOOL t1::ReadSetting()
	{
		FILE *fp;
		char m_PartFile[50];
		//读取被试者信息
		if (strlen(m_TesterName)>0)
		{
			sprintf(m_PartFile, "PartInfo\\%s.txt", m_TesterName);
			fp = fopen(m_PartFile, "rt");
			if (fp != NULL)
			{
				fscanf(fp, "编号\t%s\n", m_PartInfo.m_TesterNo);
				fscanf(fp, "姓名\t%s\n", m_PartInfo.m_TesterName);
				fscanf(fp, "性别\t%s\n", m_PartInfo.m_TesterSex);
				fscanf(fp, "年龄\t%d\n", &m_PartInfo.m_TesterAge);
				fscanf(fp, "第N次\t%d\n", &m_PartInfo.m_Session);
				fclose(fp);
			}
			else
			{
				return FALSE;
			}
		}
		else
		{
			strcpy(m_PartInfo.m_TesterNo, "unknown");
			strcpy(m_PartInfo.m_TesterName, "unknown");
			strcpy(m_PartInfo.m_TesterSex, "unknown");
			m_PartInfo.m_TesterAge = 0;
			m_PartInfo.m_Session = 1;
		}

		//读取硬件设置
		fp = fopen("Settings\\Hardware.ini", "rt");
		if (fp != NULL)
		{
			fscanf(fp, "JoySpeedMax\t%f\n", &m_HardSetting.m_JoySpeedMax);
			fscanf(fp, "KnobSensitive\t%f\n", &m_HardSetting.m_KnobSensitive);
			fscanf(fp, "DistanceError\t%f\n", &m_HardSetting.m_DistanceError);
			fscanf(fp, "AngleError\t%f\n", &m_HardSetting.m_AngleError);
			fclose(fp);
		}
		else
		{
			return FALSE;
		}

		//读取任务设置
		char m_tmp[500];
		char m_tasknostr[100];
		if (strlen(m_TaskNumStr) == 0)
		{
			sprintf(m_tasknostr, "TaskName\t", m_TaskNumStr);
		}
		else
		{
			sprintf(m_tasknostr, "TaskName\t%s\n", m_TaskNumStr);
		}
		fp = fopen("Settings\\TaskSetting.set", "rt");
		if (fp != NULL)
		{
			do
			{
				fgets(m_tmp, 500, fp);
			} while (strncmp(m_tmp, m_tasknostr, strlen(m_tasknostr)) != 0 && (!feof(fp)));
			if (!feof(fp))
			{
				//Task1
				//		fscanf(fp,"[Task1]\n");
				//fscanf(fp,"TaskName\t%s\n",m_Setting.m_TaskName);
				fscanf(fp, "PracMode\t%d\n", &m_Setting.m_PracMode);
				fscanf(fp, "ExperMode\t%d\n", &m_Setting.m_ExperMode);
				fscanf(fp, "Background\t%d\n", &m_Setting.m_Background);
				fscanf(fp, "Track\t%d\n", &m_Setting.m_Track);
				fscanf(fp, "Direction\t%d\n", &m_Setting.m_Direction);
				fscanf(fp, "MoveMode\t%d\n", &m_Setting.m_MoveMode);
				fscanf(fp, "SpeedMode\t%d\n", &m_Setting.m_SpeedMode);
				fscanf(fp, "Pause\t%d\n", &m_Setting.m_Pause);
				fscanf(fp, "PauseNum\t%d\n", &m_Setting.m_PauseNum);
				fscanf(fp, "Speed\t%f\n", &m_Setting.m_Speed);
				fscanf(fp, "InitSpeed\t%f\n", &m_Setting.m_InitSpeed);
				fscanf(fp, "SpeedMin\t%f\n", &m_Setting.m_SpeedMin);
				fscanf(fp, "SpeedMax\t%f\n", &m_Setting.m_SpeedMax);
				fscanf(fp, "AccelerationMin\t%f\n", &m_Setting.m_AccelerationMin);
				fscanf(fp, "AccelerationMax\t%f\n", &m_Setting.m_AccelerationMax);
				fscanf(fp, "AngleSpeedMin\t%f\n", &m_Setting.m_AngleSpeedMin);
				fscanf(fp, "AngleSpeedMax\t%f\n", &m_Setting.m_AngleSpeedMax);
				fscanf(fp, "RotateAngleMin\t%f\n", &m_Setting.m_RotateAngleMin);
				fscanf(fp, "RotateAngleMax\t%f\n", &m_Setting.m_RotateAngleMax);
				fscanf(fp, "PracTime\t%d\n", &m_Setting.m_PracTime);
				fscanf(fp, "ExperTime\t%d\n", &m_Setting.m_ExperTime);
				fscanf(fp, "PracTimes\t%d\n", &m_Setting.m_PracTimes);
				fscanf(fp, "ExperTimes\t%d\n", &m_Setting.m_ExperTimes);
				fscanf(fp, "JoyMoveDirection\t%d\n", &m_Setting.m_iJoyMoveDirection);


				fscanf(fp, "\n");

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
	VOID t1::SaveName()
	{
		FILE *fp;
		char m_DataDir[60];
		char m_filename[160];
		SYSTEMTIME CurTime;
		GetLocalTime(&CurTime);
		if (strlen(m_DataName) == 0)
		{
			sprintf(m_filename, "T1-%d%02d%02d%02d%02d%02d.txt", CurTime.wYear, CurTime.wMonth, CurTime.wDay, CurTime.wHour, CurTime.wMinute, CurTime.wSecond);
		}
		else
		{
			sprintf(m_filename, "T1-%s-%s-%d%02d%02d%02d%02d%02d.txt", m_TaskNumStr, m_DataName, CurTime.wYear, CurTime.wMonth, CurTime.wDay, CurTime.wHour, CurTime.wMinute, CurTime.wSecond);
		}
		if (strlen(m_TesterName) == 0)
		{
			sprintf(m_DataDir, "Data");
		}
		else
		{
			sprintf(m_DataDir, "Data\\%s", m_TesterName);
		}
		_mkdir(m_DataDir);
		sprintf(m_file, "%s\\%s", m_DataDir, m_filename);
		fp = fopen(m_file, "wt");
		fprintf(fp, "ID\tName\tSex\tSession\t"
			"DistanceError\tAngleError\tPracMode\tExperMode\t"
			"Background\tTrack\tDirection\tMoveMode\tSpeedMode\tPause\tPauseNum\tSpeed\tInitSpeed\t"
			"SpeedMin\tSpeedMax\tAccelerationMin\tAccelerationMax\tAngleSpeedMin\tAngleSpeedMax\tRotateAngleMin\tRotateAngleMax\tPracTime\tExperTime\tPracTimes\tExperTimes\t"
			"Pra_Test\tTrial\tPointNum\tPointTime\tObjPointX\tObjPointY\tPostPointX\tPostPointY\tObjRotate\tPostRotate\tDistance\tRotateError\tHit\t"
			"ObjSpeedX\tObjSpeedY\tPostSpeedX\tPostSpeedY\tObjRotateSpeed\tPostRotateSpeed\n");
		fclose(fp);
	}

	//************************************************
	//*保存结果数据记录文件
	//************************************************
	VOID t1::SaveData()
	{
		FILE *fp;
		int i;

		fp = fopen(t1::m_file, "at");
		if (m_PointNum>2)
		{
			m_PostRotateSpeed[m_PointNum - 1] = m_PostRotateSpeed[m_PointNum - 2];
		}
		for (i = 0; i<m_PointNum; i++)
		{
			fprintf(fp, "%s\t%s\t%s\t%d\t"
				"%.2f\t%.2f\t%d\t%d\t"
				"%d\t%d\t%d\t%d\t%d\t"
				"%d\t%d\t%.2f\t%.2f\t"
				"%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%d\t%d\t%d\t%d\t"
				"%d\t%d\t%d\t%u\t%d\t%d\t%d\t%d\t%.2f\t%.2f\t%.2f\t%.2f\t%d\t"
				"%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n",
				m_PartInfo.m_TesterNo, m_PartInfo.m_TesterName, m_PartInfo.m_TesterSex, m_PartInfo.m_Session,
				m_HardSetting.m_DistanceError, m_HardSetting.m_AngleError, m_Setting.m_PracMode, m_Setting.m_ExperMode,
				m_Setting.m_Background, m_Setting.m_Track, m_Setting.m_Direction, m_Setting.m_MoveMode, m_Setting.m_SpeedMode,
				m_Setting.m_Pause, m_Setting.m_PauseNum, m_Setting.m_Speed, m_Setting.m_InitSpeed,
				m_Setting.m_SpeedMin, m_Setting.m_SpeedMax, m_Setting.m_AccelerationMin, m_Setting.m_AccelerationMax, m_Setting.m_AngleSpeedMin, m_Setting.m_AngleSpeedMax, m_Setting.m_RotateAngleMin, m_Setting.m_RotateAngleMax, m_Setting.m_PracTime, m_Setting.m_ExperTime, m_Setting.m_PracTimes, m_Setting.m_ExperTimes,
				m_TrialType, m_TrialNo + 1, i + 1, m_PointTime[i], m_ObjPoint[i].x, m_ObjPoint[i].y, m_PostPoint[i].x, m_PostPoint[i].y, m_ObjRotate[i], m_PostRotate[i], m_Distance[i], m_RotateError[i], m_bHit[i],
				m_ObjSpeedX[i], m_ObjSpeedY[i], m_PostSpeedX[i], m_PostSpeedY[i], m_ObjRotateSpeed[i], m_PostRotateSpeed[i]);
		}
		fclose(fp);
	}

	//************************************************
	//*初始化DirectX 3D
	//************************************************
	HRESULT t1::InitD3D(HWND hWnd)
	{
		m_TestState = STATE_DISPLAYINSTURCTION;
		m_TrialNo = -1;
		m_bDisplayReady = TRUE;
		m_PointTime = NULL;

		if (m_Setting.m_iJoyMoveDirection == 0)
			iJoyMoveDirection = 1;
		else
			iJoyMoveDirection = -1;

		if (m_Setting.m_PracMode == 1)
		{
			m_TrialType = TRIAL_PRACTICE;
		}
		else
		{
			m_TrialType = TRIAL_EXPERMENT;
		}
		//材质大小
		//	SetRect( &rct, 0, 0, 128, 128 );
		SetRect(&strurect, x_resolution / 2 - 300 * FontScale, y_resolution / 2 - 180 * FontScale, x_resolution / 2 + 300 * FontScale, y_resolution / 2 + 20 * FontScale);
		SetRect(&erect, x_resolution / 2 - 300 * FontScale, y_resolution / 2 - 100 * FontScale, x_resolution / 2 + 300 * FontScale, y_resolution / 2 + 100 * FontScale);
		SetRect(&txtrect, x_resolution / 2 - 100 * FontScale + 5, y_resolution / 2 - 30 * FontScale + 1, x_resolution / 2 + 100 * FontScale - 5, y_resolution / 2 + 20 * FontScale - 1);
		SetRect(&lerect, x_resolution / 2 - 250 * FontScale, y_resolution / 2 - 50 * FontScale, x_resolution / 2 - 50 * FontScale, y_resolution / 2 + 100 * FontScale);
		SetRect(&rerect, x_resolution / 2 + 50 * FontScale, y_resolution / 2 - 50 * FontScale, x_resolution / 2 + 250 * FontScale, y_resolution / 2 + 100 * FontScale);

		if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		{
			return E_FAIL;
		}

		D3DPRESENT_PARAMETERS d3dpp;
		ZeroMemory(&d3dpp, sizeof(d3dpp));
		d3dpp.Windowed = TRUE;//FALSE;//
		d3dpp.SwapEffect = D3DSWAPEFFECT_FLIP;//D3DSWAPEFFECT_COPY;//D3DSWAPEFFECT_DISCARD;//
		//   d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

		D3DDISPLAYMODE d3ddm;
		if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
		{
			return E_FAIL;
		}

		d3dpp.BackBufferWidth = x_resolution;//d3ddm.Width;//
		d3dpp.BackBufferHeight = y_resolution;//d3ddm.Height;//
		d3dpp.BackBufferFormat = d3ddm.Format;

		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &g_pd3dDevice)))
		{
			return E_FAIL;
		}

		g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

		g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);


		//创建精灵
		if (FAILED(D3DXCreateSprite(g_pd3dDevice, &g_pSprite)))
		{
			MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
			return E_FAIL;
		}

		//加载纹理图片
		if (m_Setting.m_MoveMode == 0)
		{
			if (m_Setting.m_iJoyMoveDirection == 0) {
				if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\Inst\\ST_tracking.jpg"), &g_pTextureInst)))
				{
					MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
					return E_FAIL;
				}
			}
			else {
				if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\Inst\\ST_tracking_a.jpg"), &g_pTextureInst)))
				{
					MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
					return E_FAIL;
				}
			}
			
		}
		else
		{
			if (m_Setting.m_iJoyMoveDirection == 0) {
				if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\Inst\\DTtracking_and_rotate.jpg"), &g_pTextureInst)))
				{
					MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
					return E_FAIL;
				}
			}
			else {
				if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\Inst\\DTtracking_and_rotate_a.jpg"), &g_pTextureInst)))
				{
					MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
					return E_FAIL;
				}
			}

		}
		if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\Task1\\obj_white.bmp"), &g_pTexture0)))
		{
			MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
			return E_FAIL;
		}
		if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\Task1\\post_yellow.bmp"), &g_pTexture1)))
		{
			MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
			return E_FAIL;
		}
		if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\Task1\\post_red.bmp"), &g_pTexture2)))
		{
			MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
			return E_FAIL;
		}

		LOGFONT lf;
		ZeroMemory(&lf, sizeof(LOGFONT));
		lstrcpy(lf.lfFaceName, TEXT("Times New Roman"));
		lf.lfHeight = -16;
		if (FAILED(D3DXCreateFont(g_pd3dDevice, 30 * FontScale, 15 * FontScale, 20,
			0, 0, GB2312_CHARSET, 0, 0, 0, TEXT("宋体"), &g_pFont)))
		{
			return E_FAIL;
		}
		if (FAILED(D3DXCreateFont(g_pd3dDevice, 40 * FontScale, 20 * FontScale, 20,
			0, 0, GB2312_CHARSET, 0, 0, 0, TEXT("宋体"), &g_pFont1)))
		{
			return E_FAIL;
		}
		g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
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
	VOID t1::CleanupMem()
	{
		if (m_ObjPoint != NULL)
		{
			free(m_ObjPoint);
			m_ObjPoint = NULL;
		}
		if (m_PostPoint != NULL)
		{
			free(m_PostPoint);
			m_PostPoint = NULL;
		}
		if (m_ObjRotate != NULL)
		{
			free(m_ObjRotate);
			m_ObjRotate = NULL;
		}
		if (m_PostRotate != NULL)
		{
			free(m_PostRotate);
			m_PostRotate = NULL;
		}
		if (m_Distance != NULL)
		{
			free(m_Distance);
			m_Distance = NULL;
		}
		if (m_RotateError != NULL)
		{
			free(m_RotateError);
			m_RotateError = NULL;
		}
		if (m_PointTime != NULL)
		{
			free(m_PointTime);
			m_PointTime = NULL;
		}
		if (m_bHit != NULL)
		{
			free(m_bHit);
			m_bHit = NULL;
		}
		if (m_ObjSpeedX != NULL)
		{
			free(m_ObjSpeedX);
			m_ObjSpeedX = NULL;
		}
		if (m_ObjSpeedY != NULL)
		{
			free(m_ObjSpeedY);
			m_ObjSpeedY = NULL;
		}
		if (m_PostSpeedX != NULL)
		{
			free(m_PostSpeedX);
			m_PostSpeedX = NULL;
		}
		if (m_PostSpeedY != NULL)
		{
			free(m_PostSpeedY);
			m_PostSpeedY = NULL;
		}
		if (m_ObjRotateSpeed != NULL)
		{
			free(m_ObjRotateSpeed);
			m_ObjRotateSpeed = NULL;
		}
		if (m_PostRotateSpeed != NULL)
		{
			free(m_PostRotateSpeed);
			m_PostRotateSpeed = NULL;
		}
		if (m_PauseTimeStart != NULL)
		{
			free(m_PauseTimeStart);
			m_PauseTimeStart = NULL;
		}
		if (m_PauseTimeEnd != NULL)
		{
			free(m_PauseTimeEnd);
			m_PauseTimeEnd = NULL;
		}
	}

	//************************************************
	//*释放DirectX对象
	//************************************************
	VOID t1::Cleanup()
	{
		//释放字体对象
		if (g_pFont != NULL)
		{
			g_pFont->Release();
			g_pFont = NULL;
		}

		if (g_pFont1 != NULL)
		{
			g_pFont1->Release();
			g_pFont1 = NULL;
		}

		if (g_pTextureInst != NULL)
		{
			g_pTextureInst->Release();
			g_pTextureInst = NULL;
		}
		if (g_pTexture0 != NULL)
		{
			g_pTexture0->Release();
			g_pTexture0 = NULL;
		}
		if (g_pTexture1 != NULL)
		{
			g_pTexture1->Release();
			g_pTexture1 = NULL;
		}
		if (g_pTexture2 != NULL)
		{
			g_pTexture2->Release();
			g_pTexture2 = NULL;
		}
		if (g_pSprite != NULL)
		{
			g_pSprite->Release();
			g_pSprite = NULL;
		}

		if (m_pVertexBuffer != NULL)
		{
			m_pVertexBuffer->Release();
			m_pVertexBuffer = NULL;
		}

		if (g_pd3dDevice != NULL)
		{
			g_pd3dDevice->Release();
			g_pd3dDevice = NULL;
		}

		if (g_pD3D != NULL)
		{
			g_pD3D->Release();
			g_pD3D = NULL;
		}
		if (m_lpkDIDevice != NULL)
		{
			m_lpkDIDevice->Unacquire();
			m_lpkDIDevice->Release();
			m_lpkDIDevice = NULL;
		}

		if (m_lpkDInput != NULL)
		{
			m_lpkDInput->Release();
			m_lpkDInput = NULL;
		}
	}

	//************************************************
	//*渲染
	//************************************************
	VOID t1::Render()
	{
		switch (m_TestState)
		{
			//呈现指导语
		case STATE_DISPLAYINSTURCTION:
			//		g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255,255,255), 0.0f, 0 );
			//		break;
			//任务执行过程
		case STATE_DISPLAYOBJ:
		case STATE_MOVINGOBJ:
		case STATE_DISPLAYNEXT:
		case STATE_DISPLAYOPTION:
		case STATE_OVER:
			switch (m_Setting.m_Background)
			{
			case BACKGROUND_GRAY:
				g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(48, 48, 48), 0.0f, 0);
				break;
			case BACKGROUND_BLACK:
				g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(20, 20, 70), 0.0f, 0);
				break;
			case BACKGROUND_STAR:
				g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(48, 48, 48), 0.0f, 0);
				break;
			}
			break;
		}
		D3DXMATRIX mx;

		//在后台缓冲区绘制图形
		if (SUCCEEDED(g_pd3dDevice->BeginScene()))
		{
			g_pd3dDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(CUSTOMVERTEX));
			g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
			//      g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
			switch (m_TestState)
			{
				//呈现指导语
			case STATE_DISPLAYINSTURCTION:
				if (SUCCEEDED(g_pSprite->Begin(D3DXSPRITE_ALPHABLEND)))
				{
					D3DXMatrixTransformation2D(&mx, NULL, 0.0, &D3DXVECTOR2((float)1024 / (float)1024, (float)768 / (float)1024), &D3DXVECTOR2(0, 0), NULL, &D3DXVECTOR2(x_resolution / 2, y_resolution / 2));
					g_pSprite->SetTransform(&mx);
					g_pSprite->Draw(g_pTextureInst, NULL, &D3DXVECTOR3(512, 512, 0), &D3DXVECTOR3(0, 0, 0), 0xffffffff);
					//			    g_pFont->DrawText(NULL, Insturction1, -1, &erect,
					//				DT_WORDBREAK|DT_NOCLIP|DT_VCENTER, D3DCOLOR_XRGB(255,0,0));
				}
				g_pSprite->End();
				break;
				//呈现目标
			case STATE_DISPLAYOBJ:
			case STATE_MOVINGOBJ: {
				if (m_Setting.m_Background == BACKGROUND_STAR)
				{
					sky.NextFrame();
					sky.Show(g_pd3dDevice);
				}
				if (SUCCEEDED(g_pSprite->Begin(D3DXSPRITE_ALPHABLEND)))
				{
					D3DXMatrixTransformation2D(&mx, NULL, 0.0, &D3DXVECTOR2((float)128 / (float)128, (float)32 / (float)32), &D3DXVECTOR2(0, 0), post_fai*PI / 180.0, &D3DXVECTOR2(m_PostPoint[m_PointNum].x, m_PostPoint[m_PointNum].y));
					g_pSprite->SetTransform(&mx);
					if (m_bHit[m_PointNum])
					{
						g_pSprite->Draw(g_pTexture2, NULL, &D3DXVECTOR3(64, 20, 0), &D3DXVECTOR3(0, 0, 0), 0xffffffff);

					}
					else
					{
						g_pSprite->Draw(g_pTexture1, NULL, &D3DXVECTOR3(64, 20, 0), &D3DXVECTOR3(0, 0, 0), 0xffffffff);
					}
					D3DXMatrixTransformation2D(&mx, NULL, 0.0, &D3DXVECTOR2((float)64 / (float)64, (float)16 / (float)16), &D3DXVECTOR2(0, 0), fai*PI / 180.0, &D3DXVECTOR2(m_ObjPoint[m_PointNum].x, m_ObjPoint[m_PointNum].y));
					g_pSprite->SetTransform(&mx);
					g_pSprite->Draw(g_pTexture0, NULL, &D3DXVECTOR3(32, 12, 0), &D3DXVECTOR3(0, 0, 0), 0xffffffff);

				}
				g_pSprite->End();
				break;
			}
				//进行下次测试
			case STATE_DISPLAYNEXT:
				g_pFont->DrawText(NULL, Insturction2, -1, &erect,
					DT_WORDBREAK | DT_NOCLIP | DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(255, 255, 255));
				break;
				//测试选项
			case STATE_DISPLAYOPTION:
				g_pFont->DrawText(NULL, Insturction3, -1, &erect,
					DT_WORDBREAK | DT_NOCLIP | DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(255, 255, 255));
				break;
				//测试结束
			case STATE_OVER:
				g_pFont1->DrawText(NULL, Insturction4, -1, &erect,
					DT_WORDBREAK | DT_NOCLIP | DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(255, 255, 255));
				break;
			}
			g_pd3dDevice->EndScene();
		}

		g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
	}

	//************************************************
	//*测试任务初始化
	//************************************************
	VOID t1::TestInit()
	{
		

		if (m_TrialType == TRIAL_PRACTICE)
		{
			m_TrialTime = m_Setting.m_PracTime;
			m_TrialTimes = m_Setting.m_PracTimes;
		}
		else
		{
			m_TrialTime = m_Setting.m_ExperTime;
			m_TrialTimes = m_Setting.m_ExperTimes;
		}
		a = x_resolution / 2;
		b = y_resolution / 2;
		r1 = 300;
		r2 = 200;
		Rx = 400;
		Ry = 200;
		acce = m_Setting.m_AccelerationMin;
		//	inc_v = m_Setting.m_IncreaseValue;
		if (m_Setting.m_SpeedMode == 0)
		{
			v = m_Setting.m_Speed;
		}
		else
		{
			v = m_Setting.m_InitSpeed;
		}
		InitRotateAngle = 0.0;
		if (m_Setting.m_MoveMode)
		{
			RandValueFloat(m_Setting.m_AngleSpeedMin, m_Setting.m_AngleSpeedMax, AngleSpeed);
			RandValueFloat(-90.0, 90.0, RotateAngle);
			if (RotateAngle<0)
			{
				AngleSpeed = -AngleSpeed;
			}
		}
		else
		{
			RotateAngle = 0.0;
			AngleSpeed = 0.0;
		}
		fai = 0.0;
		post_fai = 0.0;
		m_PointNum = 0;
		m_MemNum = 1000;
		m_ObjPoint = (SPOINT*)malloc(m_MemNum*sizeof(POINT));
		m_PostPoint = (SPOINT*)malloc(m_MemNum*sizeof(POINT));
		m_ObjRotate = (float*)malloc(m_MemNum*sizeof(float));
		m_PostRotate = (float*)malloc(m_MemNum*sizeof(float));
		m_Distance = (float*)malloc(m_MemNum*sizeof(float));
		m_RotateError = (float*)malloc(m_MemNum*sizeof(float));
		m_PointTime = (unsigned long*)malloc(m_MemNum*sizeof(unsigned long));
		m_bHit = (BOOL*)malloc(m_MemNum*sizeof(BOOL));
		m_ObjSpeedX = (float*)malloc(m_MemNum*sizeof(float));
		m_ObjSpeedY = (float*)malloc(m_MemNum*sizeof(float));
		m_PostSpeedX = (float*)malloc(m_MemNum*sizeof(float));
		m_PostSpeedY = (float*)malloc(m_MemNum*sizeof(float));
		m_ObjRotateSpeed = (float*)malloc(m_MemNum*sizeof(float));
		m_PostRotateSpeed = (float*)malloc(m_MemNum*sizeof(float));
		if (m_Setting.m_Pause == 1)
		{
			m_PauseTimeStart = (int*)malloc(m_Setting.m_PauseNum*sizeof(int));
			m_PauseTimeEnd = (int*)malloc(m_Setting.m_PauseNum*sizeof(int));
		}
		m_ObjRotateSpeed[m_PointNum] = AngleSpeed;
		m_PostPointX = x_resolution / 2;
		m_PostPointY = y_resolution / 2;
		m_PostPoint[m_PointNum].x = m_PostPointX;
		m_PostPoint[m_PointNum].y = m_PostPointY;
		m_PostRotate[m_PointNum] = post_fai;
		m_ObjRotate[m_PointNum] = fai;
		m_RotateError[m_PointNum] = 0.0;
		switch (m_Setting.m_Track)
		{
		case TRACK_CIRCLE:
			alpha = m_Setting.m_InitAngle*PI / 180.0;
			m_ObjPoint[m_PointNum].x = a + r1 * cos(alpha);
			m_ObjPoint[m_PointNum].y = b - r1 * sin(alpha);
			r = r1;
			break;
		case TRACK_ELLIPSE:
			alpha = m_Setting.m_InitAngle*PI / 180.0;
			m_ObjPoint[m_PointNum].x = a + Rx * cos(alpha);
			m_ObjPoint[m_PointNum].y = b - Ry * sin(alpha);
			r = pow(pow((m_ObjPoint[m_PointNum].y - b), (float)2.0) + pow((m_ObjPoint[m_PointNum].x - a), (float)2.0), (float)0.5);
			break;
		case TRACK_EIGHT:
			alpha = 0;
			m_ObjPoint[m_PointNum].x = a + r2 + r2 * cos(2 * alpha);
			m_ObjPoint[m_PointNum].y = b - r2 * sin(2 * alpha);
			r = r2;
			break;
		}
		m_Distance[m_PointNum] = pow(pow((m_ObjPoint[m_PointNum].y - m_PostPoint[m_PointNum].y), 2.0) + pow((m_ObjPoint[m_PointNum].x - m_PostPoint[m_PointNum].x), 2.0), 0.5);
		if (m_Setting.m_Track == TRACK_ELLIPSE)
		{
			omiga = pow(v*v / (pow(Rx*sin(alpha), (float)2.0) + pow(Ry*cos(alpha), (float)2.0)), (float)0.5);
		}
		else
		{
			omiga = v / r;
		}
		m_ObjSpeedX[m_PointNum] = -v * sin(alpha);
		m_ObjSpeedY[m_PointNum] = -v * cos(alpha);
		JoyX = 0;
		JoyY = 0;
		m_bHit[m_PointNum] = FALSE;
		m_bObjPause = FALSE;
		m_PauseNo = 0;
		if (m_Setting.m_Pause == 1)
		{
			RandPausePoint(60, m_Setting.m_PauseNum, m_PauseTimeStart, m_PauseTimeEnd);
		}

		if (JoystickUpdate())
		{
			post_fai0 = GetZAxis();//GetXAxis();
		}
		if (m_Setting.m_Direction == 0)
		{
			m_Direction = 1;
		}
		else
		{
			m_Direction = -1;
		}
	}

	//暂停对话框消息循环
	BOOL CALLBACK t1::PauseMsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{

		int wmId = LOWORD(wParam);
		int wmEvent = HIWORD(wParam);
		switch (msg)
		{
		case WM_INITDIALOG:
			RECT rect;
			GetWindowRect(hWnd, &rect);
			SetWindowPos(hWnd, NULL, (x_resolution - rect.right) / 2, (y_resolution - rect.bottom) / 2, rect.right - rect.left, rect.bottom - rect.top, SWP_SHOWWINDOW);
			//ShowCursor(TRUE);
			break;

		case WM_COMMAND:
			switch (wmId)
			{
			case ID_CONTINUE:
			case ID_NEXT:
			case ID_CANCEL:
				EndDialog(hWnd, wmId);
				break;

			};

			break;

		}

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}


	//************************************************
	//*外部消息处理
	//************************************************
	LRESULT WINAPI t1::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_KEYUP:
			switch (wParam)
			{
				//退出键
			case VK_ESCAPE:
				// User wants to leave fullscreen mode
				//ShowCursor(TRUE);
				ShowCursor(TRUE);
				rtn = DialogBox(gHinstance, MAKEINTRESOURCE(IDD_PAUSE), hWnd, PauseMsgProc);
				ShowCursor(FALSE);

				//AllocConsole();
				//freopen("CONOUT$", "w", stdout);
				//printf("rtn的值为%d\n", rtn);
				//FreeConsole();
				switch (rtn)
				{
				case ID_CONTINUE:
					//TRACE("\n???\n");
					//重新设定时间间隔QPart1
					QueryPerformanceCounter(&litmp);
					QPart1 = litmp.QuadPart;
					QPart2 = QPart1;
					//激活父窗口
					SetForegroundWindow(hWnd);
					//ShowCursor(FALSE);
					rtn = 0;
					break;
				case ID_NEXT:
					//若在任务中途退出 则保存当前所有实验数据
					if (m_TestState == STATE_MOVINGOBJ)
						SaveData();
					EndDialog(hWnd, rtn);
					PostThreadMessage(dwInputThreadID, WM_THREADSTOP, 0, 0); 	//退出线程
					m_TestState = STATE_NEXT;
					break;
				case ID_CANCEL:
					//若在任务中途退出 则保存当前所有实验数据
					if (m_TestState == STATE_MOVINGOBJ)
						SaveData();
					EndDialog(hWnd, rtn);
					PostThreadMessage(dwInputThreadID, WM_THREADSTOP, 0, 0); 	//退出线程
					m_TestState = STATE_EXIT;
					//exit(0);
					break;
				}


			}
			return 0;
		case WM_KEYDOWN:
			switch (wParam)
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

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	//************************************************
	//*测试任务执行过程
	//************************************************
	VOID t1::UpdateState()
	{
		switch (m_TestState)
		{
			//呈现指导语
		case STATE_DISPLAYINSTURCTION:
			break;
			//呈现目标
		case STATE_DISPLAYOBJ:
			if (abs(JoyX)>20 || abs(JoyY)>20)
			{
				if (QueryPerformanceFrequency(&litmp))
				{
					dfFreq = (double)litmp.QuadPart;// 获得计数器的时钟频率
					m_SampleInt = m_MoveInt * dfFreq;
				}
				QueryPerformanceCounter(&litmp);
				QPart1 = litmp.QuadPart;           // 获得初始值
				dfTotalMove = 0;
				dfTotalPause = 0;
				m_PointTime[m_PointNum] = QPart1 / dfFreq * 1000;
				m_PostSpeedX[m_PointNum] = 0;
				m_PostSpeedY[m_PointNum] = 0;
				m_TestState = STATE_MOVINGOBJ;
			}
			break;
			//测试任务执行
		case STATE_MOVINGOBJ:
			if (dfTotalMove<m_TrialTime)//m_Setting.m_ExperTime)
			{
				//间隔40ms采样一次
				do
				{
					Sleep(1);
					QueryPerformanceCounter(&litmp);
					QPart2 = litmp.QuadPart;         //获得中止值
					dfMinus = (double)(QPart2 - QPart1);
					//dfTim = dfMinus / dfFreq;        // 获得对应的时间值，单位为秒	
				} while (dfMinus<m_SampleInt);
				dfTim = dfMinus / dfFreq;  // 获得对应的时间值，单位为秒
				QPart1 = QPart2;           // 获得初始值
				dfTotalMove = dfTotalMove + dfTim;
				//暂停点
				if (m_Setting.m_Pause == 1)
				{
					dfTotalPause = dfTotalPause + dfTim;
					if (dfTotalPause>60)
					{
						dfTotalPause = 0;
						m_PauseNo = 0;
						RandPausePoint(60, m_Setting.m_PauseNum, m_PauseTimeStart, m_PauseTimeEnd);
					}
				}
				//计算当前运动状态
				MoveTrace();
			}
			else
			{
				//保存数据
				SaveData();
				if (m_TrialNo >= m_TrialTimes - 1)
				{
					if ((m_TrialType == TRIAL_PRACTICE) && (m_Setting.m_ExperMode == 1))
					{
						//呈现正式测试选项
						m_TrialNo = -1;
						m_TrialType = TRIAL_EXPERMENT;
						m_TestState = STATE_DISPLAYOPTION;
						CleanupMem();
					}
					else
					{
						//测试结束
						QueryPerformanceCounter(&litmp);
						QPart1 = litmp.QuadPart;           // 获得初始值
						TimeInt = 2;
						m_TestState = STATE_OVER;
					}
				}
				else
				{
					//进行下一次测试
					CleanupMem();
					m_TestState = STATE_DISPLAYNEXT;
				}
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

				SendMessage(hWnd, WM_CLOSE, 0, 0); // 关闭窗口
				SendMessage(hWnd, WM_DESTROY, 0, 0);
			}
			break;
		case STATE_NEXT:
			break;
		default:
			break;
		}
	}

	//************************************************
	//*操纵杆输入线程
	//************************************************
	DWORD WINAPI t1::InputThreadProcedure(LPVOID lpStartupParam)
	{
		// get the data we passed to the thread. Note that we don't have to use this
		// at all if we don't want
		MYDATA* pMyData = (MYDATA*)lpStartupParam;

		// access some imaginary members of MYDATA, which you can define on
		// your own later
		pMyData->nTime = GetCurrentTime(); // imaginary function I created
		pMyData->nNumber = 5;


		// here's the thread's main loop ?kind of like the main loop in WinMain
		MSG msg;
		int i;
		for (;;)
		{
			//处理外部消息
			if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
			{
				GetMessage(&msg, NULL, 0, 0);

				if (msg.message == WM_THREADSTOP)
					break; // only way out of the for( ;; ) loop

				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				switch (m_TestState)
				{
				case STATE_DISPLAYINSTURCTION:
				case STATE_DISPLAYNEXT:
				case STATE_DISPLAYOPTION:
					//呈现开始选项，等待按任意键开始测试
					if (JoystickUpdate())
					{
						for (i = 0; i<8; i++)
						{
							if (IsButtonDown(KEY_YES))
							{
								m_TrialNo++;
								TestInit();
								m_TestState = STATE_DISPLAYOBJ;
								break;
							}
						}
					}
					break;
				case STATE_DISPLAYOBJ:
				case STATE_MOVINGOBJ:
					//测试过程中获得操纵杆输入
					if (JoystickUpdate())
					{
						
						JoyX = GetXAxis();//GetYAxis();//
						JoyY = GetYAxis();//-GetZAxis();//
						if (m_Setting.m_MoveMode == MODE_MOVEROATE)
						{
							JoyZ = GetZAxis();//GetXAxis();//
							//post_fai = (float)(JoyZ - post_fai0)*(3600.0) / m_HardSetting.m_KnobSensitive;//GetZAxis()*PI/400.0;
							

							post_fai = (float)(JoyZ - post_fai0/* - m_HardSetting.m_JoySpeedMax*/) / m_HardSetting.m_JoySpeedMax *(180.0) * 10. / m_HardSetting.m_KnobSensitive;
							
							//double JoyAlpha = 0;
							//JoyAlpha = atan(fabs((double)(JoyY) / (double)(JoyX)));//摇杆角度
							//post_fai = JoyAlpha * 180./PI *(10.0) / m_HardSetting.m_KnobSensitive;
							//cout << "JoyAlpha = " << JoyAlpha*180./PI << endl;
							//cout << "JoyZ = " << JoyZ << endl;
							//cout << "post_fai = " << post_fai << endl;
							//cout << "post_fai0 = " << post_fai0 << endl;

							while (post_fai<-180)
							{
								post_fai = post_fai + 360;
							}
							while (post_fai>180)
							{
								post_fai = post_fai - 360;
							}
						}
					}
					break;
				case STATE_OVER:
					//测试结束，等待按任意键退出
					if (JoystickUpdate())
					{
						for (i = 0; i<12; i++)
						{
							if (IsButtonDown(i))
							{
								PostThreadMessage(dwInputThreadID, WM_THREADSTOP, 0, 0);
								m_TestState = STATE_NEXT;// STATE_EXIT --> STATE_NEXT
							}
						}
					}
					break;
				default:
					break;
				}
				// do the task ?add in your own stuff here

				// yield to other threads, because we almost never get messages
				// (note that we may be yielding to WinMain too)
				//以键盘代替操纵杆
				if (JOY == 0)
				{
					if (IsButtonDown(DIK_ESCAPE))
					{
						PostThreadMessage(dwInputThreadID, WM_THREADSTOP, 0, 0);
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
	int APIENTRY t1::_tWinMain(HINSTANCE &hInstance,
		HINSTANCE &hPrevInstance,
		LPTSTR    &lpCmdLine,
		int       &nCmdShow, HWND &_hWnd,
		std::string winClassName, std::string winName)
	{
		// 打开控制台
		//if (!AllocConsole()) return 1;
		//freopen("CONOUT$", "w", stdout);
		
		// 初始化句柄和状态
		bool bUnClosedLastWin = true;
		hWnd = _hWnd;
		gHinstance = hInstance;
		ShowCursor(FALSE);
		//g_nThreadExitCount = 0;

		//获得传递的命令行参数，得到被试着名字和任务编号
		char *pdest;
		int result;
		int pos1;
		pdest = strrchr(lpCmdLine, ' ');
		pos1 = pdest - lpCmdLine;
		if (pos1>0)
		{
			strncpy(m_TaskNumStr, lpCmdLine, pos1);
		}
		else
		{
			strcpy(m_TaskNumStr, "");
		}
		pdest = strrchr(lpCmdLine, '-');
		result = pdest - lpCmdLine;
		if (result>0)
		{
			strncpy(m_TesterName, lpCmdLine + pos1 + 1, result - pos1 - 1);
		}
		else
		{
			strcpy(m_TesterName, "");
		}
		if (pos1>0)
		{
			strcpy(m_DataName, lpCmdLine + pos1 + 1);
		}
		else
		{
			strcpy(m_DataName, "");
		}
		//读取任务设置
		if (!ReadSetting())
		{
			MessageBox(hWnd, "任务设置文件格式错误！", "测试任务", MB_OK);
			return 0;
		}

		 
		//注册窗口类
		WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS, MsgProc, 0L, 0L,
			hInstance, NULL, NULL, NULL, NULL,
			std::to_string(nCmdShow).c_str(), NULL };
		RegisterClassEx(&wc);

		x_resolution = GetSystemMetrics(SM_CXSCREEN);
		y_resolution = GetSystemMetrics(SM_CYSCREEN);
		rec_x_begin = (x_resolution - 1024) / 2;
		rec_y_begin = (y_resolution - 768) / 2;
		rec_x_end = (x_resolution + 1024) / 2;
		rec_y_end = (y_resolution + 768) / 2;

		_hWnd = hWnd = CreateWindow(std::to_string(nCmdShow).c_str(), std::to_string(nCmdShow).c_str(),
			WS_VISIBLE | WS_POPUP, 0, 0, x_resolution, y_resolution,
			NULL, NULL, hInstance, NULL);

		//显示主窗口
		SetFocus(hWnd);
		

		//创建DirectX设备
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
			IID_IDirectInput8,
			(void**)&m_lpkDInput, NULL)))
		{
			return 0;
		}

		float m_JoySpeedMax;
		if (m_HardSetting.m_JoySpeedMax > 0)
		{
			m_JoySpeedMax = m_HardSetting.m_JoySpeedMax;
		}
		else
		{
			m_JoySpeedMax = 200;
		}
		
		//关闭输入法
		HKL hkl;
		hkl = LoadKeyboardLayout("00000804", KLF_ACTIVATE);
		if (hkl != NULL)
		{
			ActivateKeyboardLayout(hkl, KLF_SETFORPROCESS);
		}
		//ShowCursor(FALSE);
		//设置操纵杆变化范围
		if (JoystickInit(hWnd, -m_JoySpeedMax, m_JoySpeedMax, 1))
		{
			JoystickUpdate();
		}
		else
		{
			MessageBox(hWnd, "请检查操纵杆连接是否正确！", "测试任务", MB_OK);
			return 0;
		}

		// declare a variable of our data structure to pass to the ThreadProcedure
		MYDATA MyThreadData;
		MyThreadData.nTime = 7509843;
		MyThreadData.nNumber = 39;

		//创建操纵杆输入线程
		// declare a DWORD to hold our thread's new generated ID
		HANDLE h = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)InputThreadProcedure,
			(LPVOID)&MyThreadData, NULL, &dwInputThreadID);

		
		//	SetPriorityClass(h,NORMAL_PRIORITY_CLASS);
		//	SetThreadPriority(h,THREAD_PRIORITY_ABOVE_NORMAL);

		// actually create and start the thread now!
		// the thread will run until we send it our own WM_THREADSTOP message
		srand((unsigned)time(NULL)); //初始化随机种子

		//初始化Direct3D
		bool b_InitD3d =  SUCCEEDED(InitD3D(hWnd));
		if (b_InitD3d)
		{
			//进入消息循环
			MSG msg;
			ZeroMemory(&msg, sizeof(msg));
			while (msg.message != WM_QUIT)
			{
				if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
				{
					//处理外部消息
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else
				{
					//执行测试过程
					UpdateState();
					if (m_bDisplayReady)
					{
						//渲染图形
						Render();
						hideLastWindow(bUnClosedLastWin, winClassName, winName, hInstance);
					}
				}
				Sleep(1);

				// 当按下“下一个任务”或“退出”时，终止消息循环
				if (m_TestState == STATE_NEXT 
					|| m_TestState == STATE_EXIT)
				{
					break;
				}
			}
		}
		
		ShowCursor(TRUE);
		CloseHandle(h);
		return rtn;
	}

void t1::hideLastWindow(bool &bUnClosedLastWin, std::string &winClassName, std::string &winName, HINSTANCE &hInstance)
{
	if (bUnClosedLastWin)
	{
		bUnClosedLastWin = false;
		// 隐藏上一个窗口
		HWND tmpHw = FindWindow(winClassName.c_str(), winName.c_str());
		
		if (tmpHw) // 检查是否是第一个窗口
		{
			ShowWindow(tmpHw, 0);
			UnregisterClass(winClassName.c_str(), hInstance);
		}
	}
}