// Task6_1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Task6_1.h"

int t6_1::rtn;
HINSTANCE t6_1::gHinstance;
float t6_1::acce = 0; //目标的加速度
int t6_1::iDirection = 1;//目标运动方向
int t6_1::g_nThreadExitCount = 0;                      //当前运行的线程数
DWORD t6_1::dwInputThreadID = 0;                       //瞄准器输入线程ID
BOOL t6_1::m_bCubeNum[4];                              //三维图形方块数标志
int t6_1::iJoyMoveDirection;//手柄移动方向
BOOL t6_1::m_bAcc;                                     //三维图形记忆正确性标志
double t6_1::alpha, t6_1::omiga, t6_1::v, t6_1::a, t6_1::b, t6_1::r, t6_1::Rx, t6_1::Ry, t6_1::fai, t6_1::AngleSpeed, t6_1::inc_v;
double t6_1::m_PostPointX, t6_1::m_PostPointY;                //当前瞄准器坐标
int t6_1::JoyX, t6_1::JoyY;                                   //当前操纵杆输入值  
struct TaskSetting6   t6_1::m_Setting;                 //任务6设置参数
struct HardSetting   t6_1::m_HardSetting;              //硬件设置参数 
struct PartInfo  t6_1::m_PartInfo;                    //被试者信息
short t6_1::m_TrialType;                               //测试类型
int t6_1::m_TrialTime;                                 //测试时间
int t6_1::m_TrialTimes;                                //测试时间


int t6_1::x_resolution = 1024;			//屏幕分辨率
int t6_1::y_resolution = 768;             //屏幕分辨率
int t6_1::rec_x_begin;
int t6_1::rec_y_begin;
int t6_1::rec_x_end;
int t6_1::rec_y_end;
const float t6_1::FontScale = (float)(t6_1::x_resolution + t6_1::y_resolution) / 1400.0;            //字体随屏幕分辨率的放缩尺度

const char t6_1::Insturction11[] = "    欢迎进入双任务三维\
							 图形记忆判别任务！请使用右手控制操纵杆追踪屏幕上的“⊥”。同时请注意\
							 屏幕中央呈现的图符，你需要记住这些图符。X秒后，屏幕中央的这些字符会\
							 消失。然后屏幕中央面依次出现一系列图符，每次出现一个，请判断这些图符\
							 是否为你记住的那些图符。";
const char t6_1::Insturction12[] = "    欢迎进入双任\
							 务记忆判别测试！请使用右手控制操纵杆追踪屏幕上的“⊥”。同时请注意屏\
							 幕中央呈现的图符，你需要记住这些图符。X秒后，屏幕中央的这些字符会消\
							 失。然后屏幕中央面依次出现一系列图符，每次出现一个，请判断这些图符是\
							 否为你记住的那些图符。";
const char t6_1::Insturction13[] = "请记住上面的图符，\n按“是”键开始测试。";
const char t6_1::Insturction2[] = "练习结束，按任意键进入正式实验。";
const char t6_1::Insturction3[] = "该任务完成，按任意键继续！";
const char t6_1::FeedBack[2][10] = { "错误", "正确" };
char t6_1::m_CharStr[12];

LPDIRECT3D9             t6_1::g_pD3D       = NULL;                   //directx3d对象
LPDIRECT3DDEVICE9       t6_1::g_pd3dDevice = NULL;                   //directx设备对象
LPDIRECT3DTEXTURE9      t6_1::g_pTextureInst  = NULL;                //纹理对象
LPDIRECT3DTEXTURE9      t6_1::g_pTexture0  = NULL;                   //纹理对象
LPDIRECT3DTEXTURE9      t6_1::g_pTexture1  = NULL;                   //纹理对象
LPDIRECT3DTEXTURE9      t6_1::g_pTexture2  = NULL;                   //纹理对象
LPDIRECT3DTEXTURE9      t6_1::g_pTexture3  = NULL;                   //纹理对象
LPDIRECT3DTEXTURE9      t6_1::g_pTexture4  = NULL;                   //纹理对象
LPD3DXSPRITE            t6_1::g_pSprite  = NULL;                     //精灵对象
LPD3DXFONT              t6_1::g_pFont      = 0;                      //字体对象
LPD3DXFONT              t6_1::g_pFont1     = 0;                      //字体对象
LPD3DXFONT              t6_1::g_pFont2     = 0;                      //字体对象
LPDIRECT3DVERTEXBUFFER9      t6_1::m_pVertexBuffer = NULL;

D3DXMATRIX t6_1::m_Transform;                             //坐标变换矩阵
float t6_1::TimeInt;
short t6_1::m_SignNo;                                     //三维图形记忆序号
short t6_1::m_SignOrderNo1, t6_1::m_SignOrderNo2;               //三维图形记忆系列序号
short t6_1::m_SignTrialNo;                                //三维图形记忆次数号
short t6_1::m_SignGroupNo;                                //三维图形记忆组号
short t6_1::m_SignCount;                                  //三维图形记忆数目
BOOL t6_1::m_bLoadSign;                                   //三维图形文件加载标志
BOOL t6_1::m_bDisplayReady;                               //渲染设备就绪标志

BOOL t6_1::m_bHideSign = FALSE;									//在等待时间隐藏三维图形
BOOL t6_1::m_bRememStart;                                 //三维图形记忆开始标志                       
BOOL t6_1::m_bSignStart;                                  //三维图形显示标志
short t6_1::m_SureDownNum;
int t6_1::m_SignType[12];                                 //三维图形类型
int t6_1::m_SignOrderLeft[12];                            //左边三维图形类型
int t6_1::m_SignOrder1[6];                                //三维图形序列
int t6_1::m_SignOrder2[6];                                //三维图形序列
unsigned long *t6_1::m_SignStartTime = NULL;                //三维图形记忆开始时间
unsigned long *t6_1::m_SignSureTime = NULL;                 //三维图形记忆确认时间
char(*t6_1::m_LMemName)[30];                             //存放左边三维图形名称的数组
char(*t6_1::m_RMemName)[30];                             //存放右边三维图形名称的数组
short *t6_1::m_NoSame = NULL;                               //存放两边三维图形相同性的数组
short *t6_1::m_LMemAngle = NULL;                            //存放左边三维图形旋转角度的数组
short *t6_1::m_RMemAngle = NULL;                            //存放右边三维图形旋转角度的数组
short *t6_1::m_MemAngleDiff = NULL;                         //存放两边三维图形旋转角度差的数组
short *t6_1::m_SureButtonNo = NULL;
BOOL *t6_1::m_bHit = NULL;                                //存放击中状态的数组
int t6_1::m_CubeNum;


const double t6_1::m_MoveInt = 0.04;                      //采样间隔40ms

UINT t6_1::m_PointNum;
UINT t6_1::m_MemNum;
SPOINT *t6_1::m_ObjPoint = NULL;                          //存放目标坐标的数组
SPOINT *t6_1::m_PostPoint = NULL;                         //存放瞄准器坐标的数组
float *t6_1::m_Distance = NULL;                           //存放目标和瞄准器距离的数组
unsigned long *t6_1::m_PointTime = NULL;                  //存放采样时间的数组
float *t6_1::m_ObjSpeedX = NULL;                          //存放目标速度的数组
float *t6_1::m_ObjSpeedY = NULL;                          //存放目标速度的数组
float *t6_1::m_PostSpeedX = NULL;                         //存放瞄准器速度的数组
float *t6_1::m_PostSpeedY = NULL;                         //存放瞄准器速度的数组
RECT t6_1::strurect, t6_1::lerect, t6_1::rerect, t6_1::erect, t6_1::txtrect, t6_1::coderect, t6_1::charrect[8];
D3DRECT t6_1::SignRect;

short t6_1::m_TestState;
char t6_1::m_file1[220];
char t6_1::m_file2[220];
HWND t6_1::hWnd;
char t6_1::m_TesterName[40];
char t6_1::m_DataName[60];
char t6_1::m_TaskNumStr[100];

//Timer
LARGE_INTEGER t6_1::litmp;
LONGLONG t6_1::QPart1, t6_1::QPart2, t6_1::QPart3, t6_1::QPart4;
double t6_1::dfMinus, t6_1::dfFreq, t6_1::dfTim, t6_1::dfTotalPause, t6_1::dfTotalMove, t6_1::dfTotalSign;

//************************************************
//*计算目标和瞄准器当前的运动状态
//************************************************
VOID t6_1::MoveTrace()
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
	if (abs(JoyX )> 10)
		m_PostSpeedX[m_PointNum] = JoyX / abs(JoyX) * m_HardSetting.m_JoySpeedMax;
	else
		m_PostSpeedX[m_PointNum] = 0;

	if (abs(JoyY) > 10)
		m_PostSpeedY[m_PointNum] = JoyY / abs(JoyY) * m_HardSetting.m_JoySpeedMax;
	else
		m_PostSpeedY[m_PointNum] = 0;

	//当前点时间
	m_PointTime[m_PointNum] = m_PointTime[m_PointNum-1] + (int)(dfTim*1000);// QPart2/dfFreq*1000;


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


	//当前追踪环位置
	double JoyAlpha = 0;
	JoyAlpha = atan(fabs((double)(JoyY - m_PostPointY) / (double)(JoyX - m_PostPointX)));//摇杆角度
	m_PostPointX = m_PostPointX + iJoyMoveDirection * cos(JoyAlpha) * m_PostSpeedX[m_PointNum - 1] * dfTim;
	m_PostPointY = m_PostPointY + iJoyMoveDirection * sin(JoyAlpha) * m_PostSpeedY[m_PointNum - 1] * dfTim;
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

	//当前目标角度
	alpha = alpha + (float)iDirection* (omiga * dfTim);
	omiga = v/r;
	if(alpha>2*PI)
	{
		alpha = alpha - 2*PI;
	}
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



	//当前目标位置
	m_ObjPoint[m_PointNum].x = a + r * cos(alpha);
	m_ObjPoint[m_PointNum].y = b - r * sin(alpha);   

	m_Distance[m_PointNum] = pow(pow((m_ObjPoint[m_PointNum].y-m_PostPoint[m_PointNum].y),2.0)+pow((m_ObjPoint[m_PointNum].x-m_PostPoint[m_PointNum].x),2.0),0.5);
	//追踪环和目标接近程度
	if(m_Distance[m_PointNum]<m_HardSetting.m_DistanceError)
	{
		m_bHit[m_PointNum] = TRUE;
	}
	else
	{
		m_bHit[m_PointNum] = FALSE;
	}
	//计算当前目标速度
	m_ObjSpeedX[m_PointNum] = -v * sin(alpha);
	m_ObjSpeedY[m_PointNum] = -v * cos(alpha);


}

//************************************************
//*读取当前任务设置
//************************************************
BOOL t6_1::ReadSetting()
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
			//Task6
			//		fscanf(fp,"[Task6]\n");
			//fscanf(fp,"TaskName\t%s\n",m_Setting.m_TaskName);
			fscanf(fp,"PracMode\t%d\n",&m_Setting.m_PracMode);
			fscanf(fp,"ExperMode\t%d\n",&m_Setting.m_ExperMode);	
			fscanf(fp,"MainTask\t%d\n",&m_Setting.m_MainTask);
			fscanf(fp,"SubTask\t%d\n",&m_Setting.m_SubTask);
			fscanf(fp,"Background\t%d\n",&m_Setting.m_Background);
			fscanf(fp,"InitSpeed\t%f\n",&m_Setting.m_InitSpeed);
			fscanf(fp,"CubeNum1\t%d\n",&m_Setting.m_CubeNum1);
			fscanf(fp,"CubeNum2\t%d\n",&m_Setting.m_CubeNum2);
			fscanf(fp,"CubeNum3\t%d\n",&m_Setting.m_CubeNum3);
			fscanf(fp,"CubeNum4\t%d\n",&m_Setting.m_CubeNum4);
			fscanf(fp,"Prototype\t%d\n",&m_Setting.m_Prototype);
			fscanf(fp,"RefAxis\t%d\n",&m_Setting.m_RefAxis);
			fscanf(fp,"MemTaskMode\t%d\n",&m_Setting.m_MemTaskMode);	
			fscanf(fp,"PracTime\t%d\n",&m_Setting.m_PracTime);
			fscanf(fp,"ExperTime\t%d\n",&m_Setting.m_ExperTime);
			fscanf(fp,"PracTimes\t%d\n",&m_Setting.m_PracTimes);
			fscanf(fp,"ExperTimes\t%d\n",&m_Setting.m_ExperTimes);
			fscanf(fp,"JoyMoveDirection\t%d\n",&m_Setting.m_iJoyMoveDirection);
			fscanf(fp,"SubTaskInterval\t%d\n",&m_Setting.m_iSubTaskInterval);
			fscanf(fp,"PresentTime\t%d\n",&m_Setting.m_iPresentTime);
			fscanf(fp,"ReactTime\t%d\n",&m_Setting.m_iReactTime);
			fscanf(fp,"Speed\t%f\n",&m_Setting.m_Speed);
			fscanf(fp,"SpeedMin\t%f\n",&m_Setting.m_SpeedMin);
			fscanf(fp,"SpeedMax\t%f\n",&m_Setting.m_SpeedMax);
			fscanf(fp,"AccelerationMin\t%f\n",&m_Setting.m_AccelerationMin);
			fscanf(fp,"AccelerationMax\t%f\n",&m_Setting.m_AccelerationMax);
			fscanf(fp,"SpeedMode\t%d\n",&m_Setting.m_SpeedMode);
			fscanf(fp,"Direction\t%d\n",&m_Setting.m_Direction);
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
VOID t6_1::SaveName()
{
	FILE *fp;
	char m_DataDir[60];
	char m_filename1[160];
	char m_filename2[160];


	SYSTEMTIME CurTime;
	GetLocalTime(&CurTime);
	if(strlen(m_DataName)==0)
	{
		sprintf(m_filename1, "T6_1-trace-%d%02d%02d%02d%02d%02d.txt", CurTime.wYear, CurTime.wMonth, CurTime.wDay, CurTime.wHour, CurTime.wMinute, CurTime.wSecond);
		sprintf(m_filename2, "T6_1-judge-%d%02d%02d%02d%02d%02d.txt", CurTime.wYear, CurTime.wMonth, CurTime.wDay, CurTime.wHour, CurTime.wMinute, CurTime.wSecond);
	}
	else
	{
		sprintf(m_filename1, "T6_1-trace-%s-%s-%d%02d%02d%02d%02d%02d.txt", m_TaskNumStr, m_DataName, CurTime.wYear, CurTime.wMonth, CurTime.wDay, CurTime.wHour, CurTime.wMinute, CurTime.wSecond);
		sprintf(m_filename2, "T6_1-judge-%s-%s-%d%02d%02d%02d%02d%02d.txt", m_TaskNumStr, m_DataName, CurTime.wYear, CurTime.wMonth, CurTime.wDay, CurTime.wHour, CurTime.wMinute, CurTime.wSecond);
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
			"Background\tInitSpeed\tCubeNum1\tCubeNum2\tCubeNum3\tCubeNum4\tPrototype\tRefAxis\tMemTaskMode\tPracTime\tExperTime\tPracTimes\tExperTimes\t"
			"Pra_Test\tPointNum\tPointTime\tObjPointX\tObjPointY\tPostPointX\tPostPointY\tDistance\tHit\t"
			"ObjSpeedX\tObjSpeedY\tPostSpeedX\tPostSpeedY\n");
		fclose(fp);
	}
	if(m_Setting.m_SubTask == 1)
	{
		fp = fopen(m_file2,"at");
		fprintf(fp,"ID\tName\tSex\tSession\t"
			"DistanceError\tPracMode\tExperMode\tMainTask\tSubTask\t"
			"Background\tInitSpeed\tCubeNum1\tCubeNum2\tCubeNum3\tCubeNum4\tPrototype\tRefAxis\tMemTaskMode\tPracTime\tExperTime\tPracTimes\tExperTimes\t"
			"Pra_Test\tGroupNo\tMemNo\tMemCubeNum\tLMemName\tRMemName\tLMemAngle\tRMemAngle\tMemAngleDiff\tSame\tStartTime\tSureTime\tSureButton\tMem_RT\tMem_Acc\n");
		fclose(fp);
	}
}

//************************************************
//*保存追踪结果数据记录文件
//************************************************
VOID t6_1::SaveTraceData()
{
	FILE *fp;
	int i;

	if(m_Setting.m_MainTask == 1)
	{
		fp = fopen(m_file1,"at");
		for(i=0;i<m_PointNum;i++)
		{
			fprintf(fp,"%s\t%s\t%s\t%d\t"
				"%.2f\t%d\t%d\t%d\t%d\t"
				"%d\t%.2f\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t"
				"%d\t%d\t%u\t%d\t%d\t%d\t%d\t%.2f\t%d\t"
				"%.2f\t%.2f\t%.2f\t%.2f\n",
				m_PartInfo.m_TesterNo, m_PartInfo.m_TesterName, m_PartInfo.m_TesterSex, m_PartInfo.m_Session, 
				m_HardSetting.m_DistanceError, m_Setting.m_PracMode, m_Setting.m_ExperMode, m_Setting.m_MainTask, m_Setting.m_SubTask,
				m_Setting.m_Background, m_Setting.m_InitSpeed, m_Setting.m_CubeNum1, m_Setting.m_CubeNum2, m_Setting.m_CubeNum3, m_Setting.m_CubeNum4, m_Setting.m_Prototype, m_Setting.m_RefAxis, m_Setting.m_MemTaskMode, m_Setting.m_PracTime, m_Setting.m_ExperTime, m_Setting.m_PracTimes, m_Setting.m_ExperTimes, 
				m_TrialType, i+1, m_PointTime[i], m_ObjPoint[i].x, m_ObjPoint[i].y, m_PostPoint[i].x, m_PostPoint[i].y, m_Distance[i], m_bHit[i],
				m_ObjSpeedX[i], m_ObjSpeedY[i], m_PostSpeedX[i], m_PostSpeedY[i]);
		}
		fclose(fp);
	}
}

//************************************************
//*保存记忆结果数据记录文件
//************************************************
VOID t6_1::SaveJudgeData()
{
	FILE *fp;
	int i;

	fp = fopen(m_file2,"at");
	for(i=0;i<m_SignNo;i++)
	{
		fprintf(fp,"%s\t%s\t%s\t%d\t"
			"%.2f\t%d\t%d\t%d\t%d\t"
			"%d\t%.2f\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t"
			"%d\t%d\t%d\t%d\t%s\t%s\t%d\t%d\t%d\t%d\t%u\t%u\t%d\t%u\t%d\n",
			m_PartInfo.m_TesterNo, m_PartInfo.m_TesterName, m_PartInfo.m_TesterSex, m_PartInfo.m_Session, 
			m_HardSetting.m_DistanceError, m_Setting.m_PracMode, m_Setting.m_ExperMode, m_Setting.m_MainTask, m_Setting.m_SubTask,
			m_Setting.m_Background, m_Setting.m_InitSpeed, m_Setting.m_CubeNum1, m_Setting.m_CubeNum2, m_Setting.m_CubeNum3, m_Setting.m_CubeNum4, m_Setting.m_Prototype, m_Setting.m_RefAxis, m_Setting.m_MemTaskMode, m_Setting.m_PracTime, m_Setting.m_ExperTime, m_Setting.m_PracTimes, m_Setting.m_ExperTimes, 
			m_TrialType, m_SignTrialNo+1, i+1, m_CubeNum, m_LMemName[i], m_RMemName[i], m_LMemAngle[i], m_RMemAngle[i], m_MemAngleDiff[i], !m_NoSame[i], m_SignStartTime[i], m_SignSureTime[i], m_SureButtonNo[i], m_SignSureTime[i]-m_SignStartTime[i], m_NoSame[i]==m_SureButtonNo[i]);		
	}
	fclose(fp);
}

//************************************************
//*加载三维图形文件
//************************************************
HRESULT t6_1::LoadSignFile()
{  
	char axis[3][2] = {"X","Y","Z"};
	if( g_pTexture3!=NULL)
	{
		g_pTexture3->Release();
		g_pTexture3 = NULL;
	}
	if( g_pTexture4!=NULL)
	{
		g_pTexture4->Release();
		g_pTexture4 = NULL;
	}

	char m_SignName1[80];
	char m_SignName2[80];

	if(m_SignType[m_SignNo]<m_SignCount/2)
	{
		sprintf(m_LMemName[m_SignNo],"M%d_%d_%s%04d",m_CubeNum, m_Setting.m_Prototype+1, axis[m_Setting.m_RefAxis],m_SignOrderLeft[m_SignNo]*5);
		sprintf(m_SignName1,"Pics\\Task6\\三维图形\\%s.jpg",m_LMemName[m_SignNo]);
		sprintf(m_RMemName[m_SignNo],"M%d_%d_%s%04d",m_CubeNum, m_Setting.m_Prototype+1, axis[m_Setting.m_RefAxis],(m_SignOrderLeft[m_SignNo]+m_SignOrder1[m_SignOrderNo1])%12*5);
		sprintf(m_SignName2,"Pics\\Task6\\三维图形\\%s.jpg",m_RMemName[m_SignNo]);
		m_NoSame[m_SignNo] = 0;
		m_LMemAngle[m_SignNo] = m_SignOrderLeft[m_SignNo]*30;
		m_RMemAngle[m_SignNo] = (m_SignOrderLeft[m_SignNo]+m_SignOrder1[m_SignOrderNo1])%12*30;
		m_MemAngleDiff[m_SignNo] = m_SignOrder1[m_SignOrderNo1]*30;
		m_SignOrderNo1++;
	}
	else
	{
		sprintf(m_LMemName[m_SignNo],"M%d_%d_%s%04d",m_CubeNum, m_Setting.m_Prototype+1, axis[m_Setting.m_RefAxis],m_SignOrderLeft[m_SignNo]*5);
		sprintf(m_SignName1,"Pics\\Task6\\三维图形\\%s.jpg",m_LMemName[m_SignNo]);
		sprintf(m_RMemName[m_SignNo],"M%d_%d_mir_%s%04d",m_CubeNum, m_Setting.m_Prototype+1, axis[m_Setting.m_RefAxis],(m_SignOrderLeft[m_SignNo]+m_SignOrder2[m_SignOrderNo2])%12*5);
		sprintf(m_SignName2,"Pics\\Task6\\三维图形\\%s.jpg",m_RMemName[m_SignNo]);
		m_NoSame[m_SignNo] = 1;
		m_LMemAngle[m_SignNo] = m_SignOrderLeft[m_SignNo]*30;
		m_RMemAngle[m_SignNo] = (m_SignOrderLeft[m_SignNo]+m_SignOrder2[m_SignOrderNo2])%12*30;
		m_MemAngleDiff[m_SignNo] = m_SignOrder2[m_SignOrderNo2]*30;
		m_SignOrderNo2++;
	}
	if( FAILED( D3DXCreateTextureFromFile( g_pd3dDevice, m_SignName1, &g_pTexture3 ) ) )
	{
		MessageBox(NULL, m_SignName1, "Textures.exe", MB_OK);
	}

	if(m_Setting.m_MainTask == 1)
	{
		if(JoystickUpdate())
		{
			JoyX = GetXAxis();//GetYAxis();//
			JoyY = GetYAxis();//-GetZAxis();//
		}
	}
	if( FAILED( D3DXCreateTextureFromFile( g_pd3dDevice, m_SignName2, &g_pTexture4 ) ) )
	{
		MessageBox(NULL, m_SignName2, "Textures.exe", MB_OK);
	}
	if(m_Setting.m_MainTask == 1)
	{
		if(JoystickUpdate())
		{
			JoyX = GetXAxis();//GetYAxis();//
			JoyY = GetYAxis();//-GetZAxis();//
		}
	}
	return TRUE;
}

//************************************************
//*初始化DirectX 3D
//************************************************
HRESULT t6_1::InitD3D(HWND hWnd)
{
	m_TestState = STATE_DISPLAYINSTURCTION;
	m_bDisplayReady = TRUE;
	m_SignGroupNo = -1;
	m_SureDownNum = 0;
	m_CubeNum = 9;
	if(m_Setting.m_PracMode == 1)
	{
		m_TrialType = TRIAL_PRACTICE;
	}
	else
	{
		m_TrialType = TRIAL_EXPERMENT;
	}

	if (m_Setting.m_iJoyMoveDirection == 0)
		iJoyMoveDirection = 1;
	else
		iJoyMoveDirection = -1;
	//材质大小
	//	SetRect( &rct, 0, 0, 128, 128 );
	SetRect( &strurect, x_resolution/2-300*FontScale, y_resolution/2+100*FontScale, x_resolution/2+300*FontScale, y_resolution/2+140*FontScale );
	SetRect( &erect, x_resolution/2-300*FontScale, y_resolution/2-100*FontScale, x_resolution/2+300*FontScale, y_resolution/2+100*FontScale );
	SetRect( &txtrect, 0, 0, x_resolution/4, y_resolution/8 );
	SetRect( &coderect, x_resolution/4, y_resolution/8, x_resolution*3/4, y_resolution/4 );
	SetRect( &lerect, x_resolution/2-250*FontScale, y_resolution/2-50*FontScale, x_resolution/2-50*FontScale, y_resolution/2+100*FontScale );
	SetRect( &rerect, x_resolution/2+50*FontScale, y_resolution/2-50*FontScale, x_resolution/2+250*FontScale, y_resolution/2+100*FontScale );
	SignRect.x1 = x_resolution/2-256;
	SignRect.y1 = y_resolution/2-128;
	SignRect.x2 = x_resolution/2+256;
	SignRect.y2 = y_resolution/2+128;

	//		SetRect( &charrect[i], x_resolution/3+x_resolution/12*i, y_resolution/3, x_resolution/3+x_resolution/12*(i+1), y_resolution/3+y_resolution/6);

	if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
	{
		return E_FAIL;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.Windowed = TRUE;//FALSE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_COPY;//D3DSWAPEFFECT_DISCARD;
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
		if( FAILED( D3DXCreateTextureFromFile( g_pd3dDevice, "Pics\\Inst\\DT_3Dcompare_track.jpg", &g_pTextureInst ) ) )
		{
			MessageBox(NULL, "Could not find banana.bmp", "Textures.exe", MB_OK);
			return E_FAIL;
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
		if( FAILED( D3DXCreateTextureFromFile( g_pd3dDevice, "Pics\\Inst\\ST_3Dcompare.jpg", &g_pTextureInst ) ) )
		{
			MessageBox(NULL, "Could not find banana.bmp", "Textures.exe", MB_OK);
			return E_FAIL;
		}
	}

	if( FAILED( D3DXCreateTextureFromFile( g_pd3dDevice, "Pics\\Task6\\obj_white.bmp", &g_pTexture0 ) ) )
	{
		MessageBox(NULL, "Could not find banana.bmp", "Textures.exe", MB_OK);
		return E_FAIL;
	}
	if( FAILED( D3DXCreateTextureFromFile( g_pd3dDevice, "Pics\\Task6\\post_yellow.bmp", &g_pTexture1 ) ) )
	{
		MessageBox(NULL, "Could not find banana.bmp", "Textures.exe", MB_OK);
		return E_FAIL;
	}
	if( FAILED( D3DXCreateTextureFromFile( g_pd3dDevice, "Pics\\Task6\\post_red.bmp", &g_pTexture2 ) ) )
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
	if (FAILED(D3DXCreateFont(g_pd3dDevice,20*FontScale,10*FontScale,20,
		0,0,GB2312_CHARSET,0,0,0, "宋体", &g_pFont2)))
	{
		return E_FAIL;
	}
	g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	//    g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	g_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	SaveName();
	m_LMemName=new char[12][30];
	m_RMemName=new char[12][30];
	return S_OK;
}

//************************************************
//*释放数组内存
//************************************************
VOID t6_1::CleanupMem()
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
	if(m_PointTime != NULL)
	{
		free(m_PointTime);
		m_PointTime = NULL;
	}
	if(m_Distance != NULL)
	{
		free(m_Distance);
		m_Distance = NULL;
	}
	if(m_bHit != NULL)
	{
		free(m_bHit);
		m_bHit = NULL;
	}
	if(m_SignStartTime != NULL)
	{
		free(m_SignStartTime);
		m_SignStartTime = NULL;
	}
	if(m_SignSureTime != NULL)
	{
		free(m_SignSureTime);
		m_SignSureTime = NULL;
	}
	if(m_SureButtonNo != NULL)
	{
		free(m_SureButtonNo);
		m_SureButtonNo = NULL;
	}
	if(m_NoSame != NULL)
	{
		free(m_NoSame);
		m_NoSame = NULL;
	}
	if(m_LMemAngle != NULL)
	{
		free(m_LMemAngle);
		m_LMemAngle = NULL;
	}
	if(m_RMemAngle != NULL)
	{
		free(m_RMemAngle);
		m_RMemAngle = NULL;
	}
	if(m_MemAngleDiff != NULL)
	{
		free(m_MemAngleDiff);
		m_MemAngleDiff = NULL;
	}
	//	delete []m_LMemName;
	//	m_LMemName = NULL;
	//	delete []m_RMemName;
	//	m_RMemName = NULL;
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
VOID t6_1::Cleanup()
{
	delete []m_LMemName;
	m_LMemName = NULL;
	delete []m_RMemName;
	m_RMemName = NULL;
	//释放字体对象
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
	if(g_pFont2 != NULL)
	{
		g_pFont2->Release();
		g_pFont2 = NULL;
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
	if( g_pTexture3!=NULL)
	{
		g_pTexture3->Release();
		g_pTexture3 = NULL;
	}
	if( g_pTexture4!=NULL)
	{
		g_pTexture4->Release();
		g_pTexture4 = NULL;
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
VOID t6_1::Render()
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
		if(m_Setting.m_SubTask)
		{
			//g_pd3dDevice->Clear( 1, &SignRect, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255,255,255), 0.0f, 0 );
		}
		break;
	case STATE_DISPLAYNEXT:
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
				//	    		g_pFont->DrawText(NULL, Insturction11, -1, &erect,
				//			    DT_WORDBREAK|DT_NOCLIP|DT_VCENTER, D3DCOLOR_XRGB(255,0,0));
			}
			g_pSprite->End();
			break;
		case STATE_DISPLAYOBJ:  
		case STATE_MOVINGOBJ: 
		case STATE_DISPLAYNEXT:
	    case STATE_DISPLAYFEEDBACK:
			//			char t[10];
			//			sprintf(t,"%d",m_SignNo);
			//						    g_pFont2->DrawText(NULL, t, -1, &strurect,
			//				    DT_WORDBREAK|DT_NOCLIP|DT_CENTER|DT_VCENTER, D3DCOLOR_XRGB(255,0,0));

			if ( SUCCEEDED( g_pSprite->Begin(D3DXSPRITE_ALPHABLEND) ) )
			{
				

				if (m_TestState == STATE_DISPLAYFEEDBACK)
					g_pFont1->DrawText(NULL, FeedBack[m_bAcc], -1, &erect,
						DT_WORDBREAK|DT_NOCLIP|DT_CENTER|DT_VCENTER, D3DCOLOR_XRGB(255,0,0));
				else
				{
					//呈现三维图形
					if(m_Setting.m_SubTask == 1)
					{
						if(m_bSignStart && !m_bHideSign)
						{
							D3DXMatrixTransformation2D(&mx, NULL, 0.0, &D3DXVECTOR2((float)256/(float)256,(float)256/(float)256), &D3DXVECTOR2(0,0), 0, &D3DXVECTOR2(x_resolution/2-128,y_resolution/2));
							g_pSprite->SetTransform(&mx);
							g_pSprite->Draw(g_pTexture3, NULL, &D3DXVECTOR3(128,128,0), &D3DXVECTOR3(0,0,0), 0xffffffff);
							D3DXMatrixTransformation2D(&mx, NULL, 0.0, &D3DXVECTOR2((float)256/(float)256,(float)256/(float)256), &D3DXVECTOR2(0,0), 0, &D3DXVECTOR2(x_resolution/2+128,y_resolution/2));
							g_pSprite->SetTransform(&mx);
							g_pSprite->Draw(g_pTexture4, NULL, &D3DXVECTOR3(128,128,0), &D3DXVECTOR3(0,0,0), 0xffffffff);
						}
					}
				
				}
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
			}
			g_pSprite->End();
			
			break; 
			//呈现反馈
		//case STATE_DISPLAYFEEDBACK:
			//g_pFont1->DrawText(NULL, FeedBack[m_bAcc], -1, &erect,
			//	DT_WORDBREAK|DT_NOCLIP|DT_CENTER|DT_VCENTER, D3DCOLOR_XRGB(255,0,0));
			//break;
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

//************************************************
//*测试任务初始化
//************************************************
VOID t6_1::TestInit()
{
	

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
		a = x_resolution / 2;
		b = y_resolution / 2;
		r = 300;//350;
		Rx = 400;
		Ry = 200;
		//v = m_Setting.m_InitSpeed;
		fai = 0.0;
		omiga = v/r;
		m_PointNum = 0;
		m_MemNum = 1000;
		m_ObjPoint = (SPOINT*)malloc(m_MemNum*sizeof(POINT));
		m_PostPoint = (SPOINT*)malloc(m_MemNum*sizeof(POINT));
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
		
		m_TrialTimes = m_Setting.m_ExperTimes;
		m_SignCount = 12;
		m_bCubeNum[0] = m_Setting.m_CubeNum1;
		m_bCubeNum[1] = m_Setting.m_CubeNum2;
		m_bCubeNum[2] = m_Setting.m_CubeNum3;
		m_bCubeNum[3] = m_Setting.m_CubeNum4;
		
		m_SignNo = 0;
		m_SignTrialNo = 0;
		m_SignOrderNo1 = 0;
		m_SignOrderNo2 = 0;
		m_bRememStart = FALSE;
		//		m_bShowMem = FALSE;
		m_bSignStart = FALSE;
		m_SignStartTime = (unsigned long*)malloc(m_SignCount*sizeof(unsigned long));
		m_SignSureTime = (unsigned long*)malloc(m_SignCount*sizeof(unsigned long));
		//		m_MemAcc = (short*)malloc(m_TrialTimes*sizeof(short));
		m_SureButtonNo = (short*)malloc(m_SignCount*sizeof(short));
		m_NoSame = (short*)malloc(m_SignCount*sizeof(short));
		m_LMemAngle = (short*)malloc(m_SignCount*sizeof(short));
		m_RMemAngle = (short*)malloc(m_SignCount*sizeof(short));
		m_MemAngleDiff = (short*)malloc(m_SignCount*sizeof(short));
		RandOrder(m_SignCount,m_SignType);
		RandOrder1(12,m_SignCount/2,m_SignOrderLeft);
		RandOrder1(6,m_SignCount/2,m_SignOrder1);
		RandOrder1(6,m_SignCount/2,m_SignOrder2);
		m_bLoadSign = FALSE;
		//	RandPoint(x_resolution/2-128, y_resolution/2-128, 12, m_EventPoint);
		if(m_Setting.m_MainTask == 0)
		{
			JoyX = 100;
			JoyY = 100;
		}
	}
}

//暂停对话框消息循环
BOOL CALLBACK t6_1::PauseMsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	int wmId = LOWORD(wParam); 
	int wmEvent = HIWORD(wParam); 
	switch( msg )
	{
	case WM_INITDIALOG:
		RECT rect;	
		GetWindowRect(hWnd, &rect);
		SetWindowPos(hWnd, NULL, (x_resolution - rect.right) / 2, (y_resolution - rect.bottom) / 2, rect.right - rect.left, rect.bottom - rect.top,SWP_SHOWWINDOW);
		//ShowCursor(TRUE); 
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
LRESULT WINAPI t6_1::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch( msg )
	{
	case WM_KEYUP:
		switch( wParam )
		{
			//退出键
		case VK_ESCAPE:
			// User wants to leave fullscreen mode
			//ShowCursor(TRUE);
			ShowCursor(TRUE);
			rtn = DialogBox(gHinstance, MAKEINTRESOURCE(IDD_PAUSE), hWnd, PauseMsgProc);
			ShowCursor(FALSE);
			switch (rtn)
			{
			case ID_CONTINUE:
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
				{
					SaveTraceData();
					SaveJudgeData();
				}
				EndDialog(hWnd, rtn);
				PostThreadMessage(dwInputThreadID, WM_THREADSTOP, 0, 0); 	//退出线程
				m_TestState = STATE_NEXT;
				break;
			case ID_CANCEL:
				//若在任务中途退出 则保存当前所有实验数据
				if (m_TestState == STATE_MOVINGOBJ)
				{
					SaveTraceData();
					SaveJudgeData();
				}
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
VOID t6_1::UpdateState()
{
	switch(m_TestState)
	{
		//呈现指导语
	case STATE_DISPLAYINSTURCTION:       
		break;
		//呈现目标
	case STATE_DISPLAYOBJ:	
		if(abs(JoyX)>30||abs(JoyY)>30)
			//		if(m_bRememStart)
		{
			if(QueryPerformanceFrequency(&litmp))
			{
				dfFreq = (double)litmp.QuadPart;// 获得计数器的时钟频率
			}
			QueryPerformanceCounter(&litmp);
			QPart1 = litmp.QuadPart;           // 获得初始值
			dfTotalSign = 0;
			dfTotalMove = 0;
			if(m_Setting.m_MainTask == 1)
			{
				m_PointTime[m_PointNum] = QPart1/dfFreq*1000;
				m_PostSpeedX[m_PointNum] = 0;
				m_PostSpeedY[m_PointNum] = 0;
			}
			if(!m_bLoadSign)
			{
				if(LoadSignFile())
				{
					m_bLoadSign = TRUE;
				}
			}
			m_TestState = STATE_MOVINGOBJ;
		}
		break;
		//测试任务执行
	case STATE_MOVINGOBJ:
	case STATE_DISPLAYFEEDBACK:
		if(m_Setting.m_SubTask == 1)
		{
			if(m_SignTrialNo<1)
			{	
				//if(m_SignNo<m_SignCount)//m_TrialTimes)//m_Setting.m_ExperTimes)
				if(m_SignNo<m_TrialTimes)//m_TrialTimes)//m_Setting.m_ExperTimes)
				{
					//加载图形文件
					if(!m_bLoadSign)
					{
						if(LoadSignFile())
						{
							m_bLoadSign = TRUE;
						}
					}
					//采样时间40ms
					do
					{
						QueryPerformanceCounter(&litmp);
						QPart2 = litmp.QuadPart;         //获得中止值
						dfMinus = (double)(QPart2-QPart1);
						dfTim = dfMinus / dfFreq;        // 获得对应的时间值，单位为秒		
					}while(dfTim<m_MoveInt);
					QPart1 = QPart2;           // 获得初始值
					dfTotalSign = dfTotalSign + dfTim;
					dfTotalMove = dfTotalMove + dfTim;
					//显示比较记忆图形
					if(!m_bRememStart)
					{
						
						if(dfTotalSign>=2)
						{
							m_bRememStart = TRUE;
							dfTotalSign = 0;
						}
					}
					else//if(m_bRememStart)
					{
						if(!m_bSignStart)
						{
							//任务间隔
							if(dfTotalSign>= m_Setting.m_iSubTaskInterval)
							{	
								m_bSignStart = TRUE;
								m_SignStartTime[m_SignNo] = QPart2/dfFreq*1000;
								dfTotalSign = 0;
							}
						}
						else
						{
							//超时选项，呈现时间
							if (!m_bHideSign)
							{
								if(dfTotalSign >= m_Setting.m_iPresentTime)
								{
									dfTotalSign = 0;
									m_bHideSign = TRUE;
								}
									
							}
							else
							{
								//取消等待时间
								//if(dfTotalSign >= m_Setting.m_iReactTime)
								if(dfTotalSign >= 0)
								{
								
									m_SignSureTime[m_SignNo] = 0;
									m_SureButtonNo[m_SignNo] = -1;
									m_bSignStart = FALSE;
									dfTotalSign = 0;
									m_SignNo++;
									if(m_SignNo<m_SignCount)
									{
										m_bLoadSign = FALSE;
									}
									if(!m_bLoadSign)
									{
										if(LoadSignFile())
										{
											m_bLoadSign = TRUE;
										}
									}
									
									m_bHideSign = FALSE;
								}
							
							}
							
						}
					}
					//计算当前运动状态
					if(m_Setting.m_MainTask == 1)
					{
						MoveTrace();
					}
				}
				else
				{
					m_SignTrialNo++;
					if(m_SignTrialNo<m_TrialTimes)
					{
						//保存数据
						SaveJudgeData();
						m_SignNo = 0;
						m_SignOrderNo1 = 0;
						m_SignOrderNo2 = 0;
						RandOrder(m_SignCount,m_SignType);
						RandOrder1(12,m_SignCount/2,m_SignOrderLeft);
						RandOrder1(6,m_SignCount/2,m_SignOrder1);
						RandOrder1(6,m_SignCount/2,m_SignOrder2);
						m_bLoadSign = FALSE;
						//加载图形文件
						if(!m_bLoadSign)
						{
							if(LoadSignFile())
							{
								m_bLoadSign = TRUE;
							}
						}
					}
				}
			}
			else
			{	
				//如果全部方块数目已进行完
				if(m_SignGroupNo>=3)
				{
					//保存数据
					if(m_Setting.m_MainTask == 1)
					{
						SaveTraceData();
					}
					SaveJudgeData();
					if((m_TrialType == TRIAL_PRACTICE)&&(m_Setting.m_ExperMode == 1))
					{
						//呈现正式测试选项
						m_SignTrialNo = 0;
						m_CubeNum = 9;
						m_SignGroupNo = -1;
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
				//如果全部方块数目没有进行完
				else
				{
					//保存数据
					SaveJudgeData();
					//进行下一个方块数目
					m_SignNo = 0;
					m_SignTrialNo = 0;
					m_SignOrderNo1 = 0;
					m_SignOrderNo2 = 0;
					RandOrder(m_SignCount,m_SignType);
					RandOrder1(12,m_SignCount/2,m_SignOrderLeft);
					RandOrder1(6,m_SignCount/2,m_SignOrder1);
					RandOrder1(6,m_SignCount/2,m_SignOrder2);
					//					m_bRememStart = FALSE;
					//					m_bShowMem = FALSE;
					m_bSignStart = FALSE;
					//					RandOrder(10,m_SignOrder);
					m_SignGroupNo++;
					m_CubeNum++;
					while((!m_bCubeNum[m_SignGroupNo])&&(m_SignGroupNo<4))
					{
						m_SignGroupNo++;
						m_CubeNum++;
					}
					//如果没有要进行的方块数
					if(m_SignGroupNo>3)
					{
						//保存数据
						if(m_Setting.m_MainTask == 1)
						{
							SaveTraceData();
						}
						if((m_TrialType == TRIAL_PRACTICE)&&(m_Setting.m_ExperMode == 1))
						{
							//呈现正式测试选项
							m_CubeNum = 9;
							m_SignGroupNo = -1;
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
						//加载图形文件
						m_bLoadSign = FALSE;
						if(!m_bLoadSign)
						{
							if(LoadSignFile())
							{
								m_bLoadSign = TRUE;
							}
						}
					}
				}
			}
		}
		else
		{
			


			//仅进行追踪任务
			if(dfTotalMove<m_TrialTime)
			{
				do
				{
					QueryPerformanceCounter(&litmp);
					QPart2 = litmp.QuadPart;         //获得中止值
					dfMinus = (double)(QPart2-QPart1);
					dfTim = dfMinus / dfFreq;        // 获得对应的时间值，单位为秒		
				}while(dfTim<m_MoveInt);
				QPart1 = QPart2;           // 获得初始值
				dfTotalMove = dfTotalMove + dfTim;
				MoveTrace();
			}
			else
			{
				//保存数据
				SaveTraceData();			
				if((m_TrialType == TRIAL_PRACTICE)&&(m_Setting.m_ExperMode == 1))
				{
					//呈现正式测试选项
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
		}

		if (m_TestState == STATE_DISPLAYFEEDBACK)
		{
			QueryPerformanceCounter(&litmp);
			QPart4 = litmp.QuadPart;         //获得中止值
			dfMinus = (double)(QPart4-QPart3);
			dfTim = dfMinus / dfFreq;        // 获得对应的时间值，单位为秒	
			//2000ms
		
			if (dfTim >= TimeInt)
			{
				m_bSignStart = FALSE;
				dfTotalSign = 0;
				//		m_ButtonDownNum++;
				m_SignNo++;
				if((m_SignTrialNo<m_TrialTimes-1)||(m_SignNo<m_SignCount))
				{
					m_bLoadSign = FALSE;
				}
				m_TestState = STATE_MOVINGOBJ;
			}	
		}
		
		

		break;
		//呈现反馈
	/*case STATE_DISPLAYFEEDBACK:
		QueryPerformanceCounter(&litmp);
		QPart4 = litmp.QuadPart;         //获得中止值
		dfMinus = (double)(QPart4-QPart3);
		dfTim = dfMinus / dfFreq;        // 获得对应的时间值，单位为秒	
		//2000ms
		
		if (dfTim >= TimeInt)
		{
			m_bSignStart = FALSE;
			dfTotalSign = 0;
			//		m_ButtonDownNum++;
			m_SignNo++;
			if((m_SignTrialNo<m_TrialTimes-1)||(m_SignNo<m_SignCount))
			{
				m_bLoadSign = FALSE;
			}
			m_TestState = STATE_MOVINGOBJ;
		}	
		break;*/
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
	default:
		break;
	}
}

//************************************************
//*操纵杆输入线程
//************************************************
DWORD WINAPI t6_1::InputThreadProcedure(LPVOID lpStartupParam)
{
	// get the data we passed to the thread. Note that we don't have to use this
	// at all if we don't want
	MYDATA* pMyData = (MYDATA*) lpStartupParam;

	// access some imaginary members of MYDATA, which you can define on
	// your own later
	pMyData->nTime = GetCurrentTime(); // imaginary function I created
	pMyData->nNumber = 5;

	// here's the thread's main loop ?kind of like the main loop in WinMain
	int i;
	MSG msg;

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
					//呈现开始选项，等待按任意键开始测试
					if(m_SureDownNum== 0)
					{
						for(i=0;i<8;i++)
						{
							if(IsButtonDown(KEY_YES))
							{
								TestInit();
								//								m_ButtonDownNum++;
								m_SignGroupNo++;
								while((!m_bCubeNum[m_SignGroupNo])&&(m_SignGroupNo<4))
								{
									m_SignGroupNo++;
									m_CubeNum++;
								}
								if(m_SignGroupNo>3)
								{
									m_SignNo = m_SignCount;
								}
								m_TestState = STATE_DISPLAYOBJ;
								break;
							}
						}
					}
					break;
				case STATE_DISPLAYOBJ:
					if(m_Setting.m_MainTask == 1)
					{
						JoyX = GetXAxis();//GetYAxis();//
						JoyY = GetYAxis();//-GetZAxis();//
						//						if(JoyX||JoyY)
						//						{
						//							m_bRememStart = TRUE;
						//						}
					}
					else//if(m_Setting.m_SubTask == 1)
					{ 
						if(!m_bRememStart)
						{
							m_bRememStart = TRUE;
						}
					}	
					break;
				case STATE_DISPLAYFEEDBACK:
					if(m_Setting.m_MainTask == 1)
					{
						JoyX = GetXAxis();//GetYAxis();//
						JoyY = GetYAxis();//-GetZAxis();//
					
					}
					break;
				case STATE_MOVINGOBJ:
				//case STATE_DISPLAYFEEDBACK:
					if(m_Setting.m_SubTask == 1)
					{ 
						if(m_bSignStart)
						{
							//有比较记忆图形时按键确认
							if(m_SureDownNum == 0)
							{
								for(i=0;i<2;i++)
								{
									if(IsButtonDown(m_EventKey[i]))
									{
										m_SignSureTime[m_SignNo] = QPart2/dfFreq*1000;
										m_SureButtonNo[m_SignNo] = m_SureDownType[i];
										m_bAcc = (m_NoSame[m_SignNo]==m_SureButtonNo[m_SignNo]);
										if(m_TrialType == TRIAL_PRACTICE)
										{
											QueryPerformanceCounter(&litmp);
											QPart3 = litmp.QuadPart;           // 获得初始值
											TimeInt = 1;
											m_TestState = STATE_DISPLAYFEEDBACK;
										}
										else
										{
											m_bSignStart = FALSE;
											dfTotalSign = 0;
											//										m_ButtonDownNum++;
											m_SignNo++;
											if((m_SignTrialNo<m_TrialTimes-1)||(m_SignNo<m_SignCount))
											{
												m_bLoadSign = FALSE;
											}
										}
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
						JoyY = GetYAxis();//-GetZAxis();//
					}
					break;
				case STATE_DISPLAYNEXT:
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
								m_TestState = STATE_NEXT;// STATE_EXIT --> STATE_NEXT
							}
						}
					}
					break;
				default:
					break;
				}
				//计算当前被按下键的数量，以确定是否有新的键按下
				m_SureDownNum = 0;
				for(i=0;i<2;i++)
				{
					if(IsButtonDown(m_EventKey[i]))
					{
						m_SureDownNum++;
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
int APIENTRY t6_1::_tWinMain(HINSTANCE &hInstance, HINSTANCE &hPrevInstance, LPTSTR &lpCmdLine, int &nCmdShow, HWND &_hWnd, std::string winClassName, std::string winName)
{
	// 初始化句柄和状态
	bool bUnClosedLastWin = true;
	hWnd = _hWnd;
	gHinstance = hInstance;
	g_nThreadExitCount = 0;
	ShowCursor(FALSE);


	//获得传递的命令行参数，得到被试着名字和任务编号
	//gHinstance = hInstance;
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
	
	m_bLoadSign = FALSE;
	//注册窗口类
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L, 
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		std::to_string(nCmdShow).c_str(), NULL };
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

	_hWnd = hWnd = CreateWindow(std::to_string(nCmdShow).c_str(), std::to_string(nCmdShow).c_str(),
		WS_VISIBLE|WS_POPUP, 0, 0, x_resolution, y_resolution,
		NULL, NULL, hInstance, NULL );
	//显示主窗口
	//	ShowWindow( hWnd, SW_HIDE );
	//	UpdateWindow( hWnd );

	//显示主窗口
	SetFocus(hWnd);
	//ShowCursor(FALSE);

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
	//ShowCursor(FALSE);

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

void t6_1::hideLastWindow(bool &bUnClosedLastWin, std::string &winClassName, std::string &winName, HINSTANCE &hInstance)
{
	if (bUnClosedLastWin)
	{
		bUnClosedLastWin = false;
		// 隐藏上一个窗口
		HWND tmpHw = FindWindow(winClassName.c_str(), winName.c_str());
		if (winClassName != "") // 检查是否是第一个窗口
		{
			ShowWindow(tmpHw, 0);
			UnregisterClass(winClassName.c_str(), hInstance);
		}
	}
}