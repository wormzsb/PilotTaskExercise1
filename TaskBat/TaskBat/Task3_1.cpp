// Task3_1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Task3_1.h"
#include <iostream>
using namespace std;

int t3::rtn;
HINSTANCE t3::gHinstance;

char t3::szFeedBack[100];

int t3::rangex;
int t3::iPlaneCnt;
int	t3::iHelicopterCnt;
BOOL t3::m_bShowFeedback = FALSE;//��ʾ����
float t3::acce = 0;	//Ŀ����ٶ�
int t3::iDirection = 0;  //˳��ʱ��
int t3::g_nThreadExitCount = 0;                               //��ǰ���е��߳���
DWORD t3::dwInputThreadID = 0;                                //��׼�������߳�ID 

double t3::alpha,t3::omiga,t3::v,t3::a,t3::b,t3::r,t3::r1,t3::r2,t3::Rx,t3::Ry,t3::fai,t3::AngleSpeed,t3::inc_v;
double t3::m_PostPointX,t3::m_PostPointY;                         //��ǰ��׼������
int t3::JoyX,t3::JoyY;                                            //��ǰ���ݸ�����ֵ  
struct TaskSetting3   t3::m_Setting;                          //����3���ò���
struct HardSetting   t3::m_HardSetting;                       //Ӳ�����ò���
struct PartInfo   t3::m_PartInfo;                             //��������Ϣ
short t3::m_TrialType;                                        //��������
int t3::m_TrialTime;                                          //����ʱ��
int t3::m_TrialTimes;                                         //���Դ���
int t3::iJoyMoveDirection;//�ֱ��ƶ�������
int t3::x_resolution=1024;			//��Ļ�ֱ���
int t3::y_resolution=768;             //��Ļ�ֱ���
int t3::rec_x_begin;
int t3::rec_y_begin;
int t3::rec_x_end;
int t3::rec_y_end;
const float t3::FontScale = (float)(t3::x_resolution+t3::y_resolution)/1400.0;       //��������Ļ�ֱ��ʵķ����߶�

const char t3::Insturction11[] = "    ��ӭ����Ŀ��\
������ҵ�µ�ͻ���¼���Ӧ����������Ĳ����У�����Ҫ�����ֲ��ݿ���\
�������Ŀ����������ڸ��ٵ�ͬʱ������Ҫ����Ƿ��зɻ���ͼ�γ��֣�\
һ�����֣��������ְ���������Ӧ��";
const char t3::Insturction12[] = "    ��ӭ����Ŀ�������ҵ�µ�ͻ���¼���Ӧ����������Ĳ����У�\
����Ҫ�����ֲ��ݿ��Ƹ�������ַ�������ҵ����Ļ���Ϸ�����ʾ�������\
����Ļ�������ͼ�ε�ʱ������Ҫ�������������������Ӧ��ĸ���ڽ��б�\
���ͬʱ������Ҫ����Ƿ��зɻ���ͼ�γ��֣�һ�����֣��������ְ�����\
����Ӧ��";
const char t3::Insturction13[] = "    ��ӭ����Ŀ�������ҵ�µ�ͻ���¼���Ӧ����\
������Ĳ����У�����Ҫ������������ֱ�\
������ͬʱ����Ƿ��зɻ���ͼ�γ��֣��������ְ���������Ӧ�������\
�ֵ���ֱ���ɻ���ͼ�Σ�����Ҫ������"; 
const char t3::Insturction2[] = "��ϰ�������������������ʽʵ�顣";
const char t3::Insturction3[] = "��������ɣ��������������";
const char t3::FeedBack[2][10] = {"����","��ȷ"};

LPDIRECT3D9             t3::g_pD3D       = NULL;             //directx3d����
LPDIRECT3DDEVICE9       t3::g_pd3dDevice = NULL;             //directx�豸����
LPDIRECT3DTEXTURE9      t3::g_pTextureInst  = NULL;          //�������
LPDIRECT3DTEXTURE9      t3::g_pTexture0  = NULL;             //�������
LPDIRECT3DTEXTURE9      t3::g_pTexture1  = NULL;             //�������
LPDIRECT3DTEXTURE9      t3::g_pTexture2  = NULL;             //�������
LPDIRECT3DTEXTURE9      t3::g_pTexture3[2]  = {NULL};        //�������
LPD3DXSPRITE            t3::g_pSprite  = NULL;               //�������
LPD3DXFONT              t3::g_pFont      = 0;                //�������
LPD3DXFONT              t3::g_pFont1     = 0;                //�������
LPDIRECT3DVERTEXBUFFER9      t3::m_pVertexBuffer  = NULL;    //�������

D3DXMATRIX t3::m_Transform;                                  //����任����
float t3::TimeInt;                                           //ʱ���� 
short t3::m_EventNo;                                         //ͻ���¼����
short t3::m_EventCount;                                      //ͻ���¼�����
int t3::m_RecordNo;                                          //ͻ���¼���¼���
short t3::m_EventKeyNum;                                     //ͻ���¼������� 
short t3::m_SureDownNum;
BOOL t3::m_bDisplayReady;                                    //��Ⱦ�豸������־

BOOL t3::m_bEventStart;                                      //ͻ���¼���ʼ��־
BOOL t3::m_bEventReactTime = FALSE;									//�Ƿ����ȴ���Ӧʱ���־
int t3::iPlanePos;


const double t3::m_MoveInt = 0.04;                           //�������40ms
double t3::m_SampleInt;
BOOL t3::m_bEventAcc;                                        //����ȷ����ȷ��־

UINT t3::m_PointNum;
UINT t3::m_MemNum, t3::m_MemEvent;

short *t3::m_EventType = NULL;                               //���ͻ���¼����͵�����
int *t3::m_EventOrder = NULL;                                //���ͻ���¼��������е�����
int *t3::m_EventInterval = NULL;                             //���ͻ���¼���ʼ���������
unsigned long *t3::m_EventStartTime = NULL;                  //���ͻ���¼���ʼʱ������� 
unsigned long *t3::m_EventSureTime = NULL;                   //���ͻ���¼�ȷ��ʱ�������
short *t3::m_SureButtonNo = NULL;                            //���ͻ���¼�ȷ�ϼ����͵�����
BOOL *t3::m_bHit = NULL;                                     //��Ż���״̬������
SPOINT *t3::m_ObjPoint = NULL;                               //���Ŀ�����������
SPOINT *t3::m_PostPoint = NULL;                              //�����׼�����������
float *t3::m_Distance = NULL;                                //���Ŀ�����׼�����������
unsigned long *t3::m_PointTime = NULL;                       //��Ų���ʱ�������
POINT *t3::m_EventPoint = NULL;                              //���ͻ���¼���ʾ���������
float *t3::m_ObjSpeedX = NULL;                               //���Ŀ���ٶȵ�����
float *t3::m_ObjSpeedY = NULL;                               //���Ŀ���ٶȵ�����
float *t3::m_PostSpeedX = NULL;                              //�����׼���ٶȵ�����
float *t3::m_PostSpeedY = NULL;                              //�����׼���ٶȵ�����
RECT t3::strurect,t3::lerect,t3::rerect,t3::erect,t3::txtrect,t3::coderect;
D3DRECT t3::wcoderect;

short t3::m_TestState;
char t3::m_file1[220];
char t3::m_file2[220];
HWND t3::hWnd;
char t3::m_TesterName[40];
char t3::m_DataName[60];
char t3::m_TaskNumStr[100];
int t3::m_Condition;

//Timer
LARGE_INTEGER t3::litmp; 
LONGLONG t3::QPart0,t3::QPart1,t3::QPart2,t3::QPart3,t3::QPart4;
double t3::dfMinus, t3::dfFreq, t3::dfTim, t3::dfTotal, t3::dfTotalPause, t3::dfTotalEvent; 

//************************************************
//*����Ŀ�����׼����ǰ���˶�״̬
//************************************************
VOID t3::MoveTrace()
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

	//��ǰ��ʱ��
	m_PointTime[m_PointNum] = m_PointTime[m_PointNum-1] + (int)(dfTim*1000);//QPart2/dfFreq*1000;

	////��ǰ׷�ٻ�λ��
	//double JoyAlpha = 0;
	//JoyAlpha = atan(fabs((double)(JoyY - m_PostPointY) / (double)(JoyX - m_PostPointX)));//ҡ�˽Ƕ�
	//m_PostPointX = m_PostPointX + iJoyMoveDirection * cos(JoyAlpha) * m_PostSpeedX[m_PointNum - 1] * dfTim;
	//m_PostPointY = m_PostPointY + iJoyMoveDirection * sin(JoyAlpha) * m_PostSpeedY[m_PointNum - 1] * dfTim;
	//m_PostPoint[m_PointNum].x = m_PostPointX;
	//m_PostPoint[m_PointNum].y = m_PostPointY;
	
	//��ǰ׷�ٻ�λ��
	double JoyAlpha = 0;//ҡ�˽Ƕ�
	if (!(JoyX == 0 && JoyY == 0)) {
		double rJ = sqrt(JoyX * JoyX + JoyY * JoyY);
		double cosJ = (double)JoyX / rJ;
		double sinJ = (double)JoyY / rJ;
		m_PostPointX = m_PostPointX + cosJ * rJ  * dfTim;
		m_PostPointY = m_PostPointY + sinJ * rJ  * dfTim;
	}
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


	//ƽ��
	alpha = alpha + (float)iDirection* (omiga * dfTim);
	switch(m_Setting.m_iTrack)
	{
	//Բ�ι켣
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
	
	//�����ι켣
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

	//����Ŀ�����׼������
	m_Distance[m_PointNum] = pow(pow((m_ObjPoint[m_PointNum].y-m_PostPoint[m_PointNum].y),2.0)+pow((m_ObjPoint[m_PointNum].x-m_PostPoint[m_PointNum].x),2.0),0.5);
  

	//�������״̬
	if((m_Distance[m_PointNum]<m_HardSetting.m_DistanceError))
	{
		m_bHit[m_PointNum] = TRUE;
	}
	else
	{
        m_bHit[m_PointNum] = FALSE;
	}

	//���㵱ǰĿ���ٶ�
	//����
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
//*��ȡ��ǰ��������
//************************************************
BOOL t3::ReadSetting()
{
	FILE *fp;
	char m_PartFile[50];
	//��ȡ��������Ϣ
	if(strlen(m_TesterName)>0)
	{
		sprintf(m_PartFile, "PartInfo\\%s.txt", m_TesterName);
		fp = fopen(m_PartFile,"rt");
		if(fp!=NULL)
		{
			fscanf(fp,"���\t%s\n",m_PartInfo.m_TesterNo);
			fscanf(fp,"����\t%s\n",m_PartInfo.m_TesterName);
			fscanf(fp,"�Ա�\t%s\n",m_PartInfo.m_TesterSex);
			fscanf(fp,"����\t%d\n",&m_PartInfo.m_TesterAge);
			fscanf(fp,"��N��\t%d\n",&m_PartInfo.m_Session);
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

	//��ȡӲ������
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

	//��ȡ��������
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
//*����������ݼ�¼�ļ�
//************************************************
VOID t3::SaveName()
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
//*���������ݼ�¼�ļ�
//************************************************
VOID t3::SaveData()
{
	FILE *fp;
	BOOL m_bEventAcc;
	int i;

    //����׷������
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
	//����ͻ���¼�����
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
//*��ʼ��DirectX 3D
//************************************************
HRESULT t3::InitD3D(HWND hWnd)
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
	//���ʴ�С
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

	//��������
    if( FAILED( D3DXCreateSprite( g_pd3dDevice, &g_pSprite )))
	{
		MessageBox(NULL, "Could not find banana.bmp", "Textures.exe", MB_OK);
		return E_FAIL;
	}

	//��������ͼƬ
	if(m_Setting.m_MainTask&&m_Setting.m_SubTask)
	{
		if(m_Setting.m_EventMode == 0)
		{
			if (m_Setting.m_iJoyMoveDirection == 0) {
				if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, "Pics\\Inst\\DT_simpleRT_track.jpg", &g_pTextureInst)))
				{
					MessageBox(NULL, "Could not find banana.bmp", "Textures.exe", MB_OK);
					return E_FAIL;
				}
			}
			else {
				if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, "Pics\\Inst\\DT_simpleRT_track_a.jpg", &g_pTextureInst)))
				{
					MessageBox(NULL, "Could not find banana.bmp", "Textures.exe", MB_OK);
					return E_FAIL;
				}
			}
			
		}
		else
		{
			if (m_Setting.m_iJoyMoveDirection == 0) {
				if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, "Pics\\Inst\\DT_selectiveRT_track.jpg", &g_pTextureInst)))
				{
					MessageBox(NULL, "Could not find banana.bmp", "Textures.exe", MB_OK);
					return E_FAIL;
				}
			}
			else
			{
				if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, "Pics\\Inst\\DT_selectiveRT_track_a.jpg", &g_pTextureInst)))
				{
					MessageBox(NULL, "Could not find banana.bmp", "Textures.exe", MB_OK);
					return E_FAIL;
				}
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
		                      0,0,GB2312_CHARSET,0,0,0, "����", &g_pFont)))
	{
		  return E_FAIL;
	}
	if (FAILED(D3DXCreateFont(g_pd3dDevice,40*FontScale,20*FontScale,20,
		                      0,0,GB2312_CHARSET,0,0,0, "����", &g_pFont1)))
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
//*�ͷ������ڴ�
//************************************************
VOID t3::CleanupMem()
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
//*�ͷ�DirectX����
//************************************************
VOID t3::Cleanup()
{
	//�ͷ��������
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
//*��Ⱦ
//************************************************
VOID t3::Render()
{
	switch(m_TestState)
	{
    //����ָ������Ʊ���
	case STATE_DISPLAYINSTURCTION:
//		g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255,255,255), 0.0f, 0 );
//		break;
	//����ִ�й��̣����Ʊ���
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

	//�ں�̨����������ͼ��
	if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
    {
        g_pd3dDevice->SetStreamSource( 0, m_pVertexBuffer, 0, sizeof(CUSTOMVERTEX) );
        g_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX );
//      g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
    	switch(m_TestState)
		{
        //����ָ����ͼƬ
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
		//����ִ�й���
        case STATE_DISPLAYOBJ:  
		case STATE_MOVINGOBJ:     	
			if ( SUCCEEDED( g_pSprite->Begin(D3DXSPRITE_ALPHABLEND) ) )
			{
				//��ʾ׷��Ŀ�����׼��
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
				//��ʾͻ���¼�
				cout << "m_EventNo = " << m_EventNo
					<< ",   m_bEventStart = " << m_bEventStart
					<< ",   m_bEventReactTime = " << m_bEventReactTime
					<< ",   m_EventType = " << m_EventType[/*m_RecordNo*/m_EventNo]
					<<endl;
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
		//���ַ���
		case STATE_DISPLAYFEEDBACK:
		
			
			g_pFont1->DrawText(NULL, szFeedBack, -1, &erect,
				DT_WORDBREAK|DT_NOCLIP|DT_CENTER|DT_VCENTER, D3DCOLOR_XRGB(255,255,255));
			break;
		//����ѡ��
		case STATE_DISPLAYOPTION:  
            g_pFont->DrawText(NULL, Insturction2, -1, &erect,
				DT_WORDBREAK|DT_NOCLIP|DT_CENTER|DT_VCENTER, D3DCOLOR_XRGB(255,255,255));
			break;
		//���Խ���
		case STATE_OVER:
            g_pFont1->DrawText(NULL, Insturction3, -1, &erect,
			    DT_WORDBREAK|DT_NOCLIP|DT_CENTER|DT_VCENTER, D3DCOLOR_XRGB(255,255,255));
			break;
		}
        g_pd3dDevice->EndScene();
	}

    g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}
void t3::RandPlanePoint(int cnt, POINT* m_EventInterval)
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

void t3::RandEvent()
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
			//�ɻ������Ƿ����꣬������ֱ����
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
//*���������ʼ��
//************************************************
VOID t3::TestInit()
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

//��ͣ�Ի�����Ϣѭ��
BOOL CALLBACK t3::PauseMsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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
//*�ⲿ��Ϣ����
//************************************************
LRESULT WINAPI t3::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch( msg )
	{
	case WM_KEYUP:
		switch( wParam )
		{
			//�˳���
		case VK_ESCAPE:
			// User wants to leave fullscreen mode
			//ShowCursor(TRUE);
			ShowCursor(TRUE);
			rtn = DialogBox(gHinstance, MAKEINTRESOURCE(IDD_PAUSE), hWnd, PauseMsgProc);
			ShowCursor(FALSE);
			switch (rtn)
			{
			case ID_CONTINUE:
				//�����趨ʱ����QPart1
				QueryPerformanceCounter(&litmp);
				QPart1 = litmp.QuadPart;        		
				QPart2 = QPart1;
				//�������
				SetForegroundWindow(hWnd);
				//ShowCursor(FALSE);
				rtn = 0;
				break;
			case ID_NEXT:
				//����������;�˳� �򱣴浱ǰ����ʵ������
				if (m_TestState == STATE_MOVINGOBJ)
					SaveData();
				EndDialog(hWnd, rtn);
				PostThreadMessage(dwInputThreadID, WM_THREADSTOP, 0, 0); 	//�˳��߳�
				m_TestState = STATE_NEXT;
				break;
			case ID_CANCEL:
				//����������;�˳� �򱣴浱ǰ����ʵ������
				if (m_TestState == STATE_MOVINGOBJ)
					SaveData();
				EndDialog(hWnd,rtn);
				PostThreadMessage(dwInputThreadID, WM_THREADSTOP,0,0); 	//�˳��߳�
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
		//���������Ϣ
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
//*��������ִ�й���
//************************************************
VOID t3::UpdateState()
{
    switch(m_TestState)
	{
	//����ָ����
    case STATE_DISPLAYINSTURCTION:  
		break;
    //����Ŀ��
	case STATE_DISPLAYOBJ:	
		if(abs(JoyX)>30||abs(JoyY)>30)
		{
			if(QueryPerformanceFrequency(&litmp))
			{
				dfFreq = (double)litmp.QuadPart;// ��ü�������ʱ��Ƶ��
				m_SampleInt = m_MoveInt * dfFreq;
			}
		    QueryPerformanceCounter(&litmp);
			QPart0 = litmp.QuadPart;           // ��ó�ʼֵ
			QPart1 = QPart0;                   // ��ó�ʼֵ
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
	//��������ִ��
    case STATE_MOVINGOBJ:
		if(m_EventNo<m_Setting.m_ExperTimes)
        //if(dfTotal<m_TrialTime)
		{
			do
			{
				QueryPerformanceCounter(&litmp);
				QPart2 = litmp.QuadPart;         //�����ֵֹ
				dfMinus = (double)(QPart2-QPart1);
				//dfTim = dfMinus / dfFreq;        // ��ö�Ӧ��ʱ��ֵ����λΪ��		
			}while(dfMinus<m_SampleInt);
			dfTim = dfMinus / dfFreq;  // ��ö�Ӧ��ʱ��ֵ����λΪ��
			QPart1 = QPart2;           // ��ó�ʼֵ
			dfTotalEvent = dfTotalEvent + dfTim;
			dfTotal = dfTotal + dfTim;
			if(m_Setting.m_SubTask == 1 && !m_bShowFeedback)
			{
				if(m_EventNo<m_EventCount)
				{
					//ͻ���¼���ʼ
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
									sprintf(szFeedBack,"��Ӧ��ʱ");
									m_bShowFeedback = TRUE;
								}
								
								dfTotalEvent = 0;
							}
						
						}

						//��������
        				/*if(dfTotalEvent>=m_Setting.m_iPresentTime )
						{
							//sprintf(szFeedBack,"%s ��Ӧʱ��Ϊ%dms", FeedBack[m_bEventAcc],m_EventSureTime[m_RecordNo] - m_EventStartTime[m_RecordNo]);
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
									//�ɻ������Ƿ����꣬������ֱ����
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
			//���㵱ǰ�˶�״̬
			if(m_Setting.m_MainTask == 1)
			{
                MoveTrace();
			}

			
			//��ʾ����
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
			//��������
			SaveData();
			/*if((m_TrialType == TRIAL_PRACTICE)&&(m_Setting.m_ExperMode == 1))
			{
				//������ʽ����ѡ��
				m_TrialType = TRIAL_EXPERMENT;
				m_TestState = STATE_DISPLAYOPTION;
				CleanupMem();
			}
			else
			{*/
			//���Խ���
			QueryPerformanceCounter(&litmp);
			QPart1 = litmp.QuadPart;           // ��ó�ʼֵ
			TimeInt = 2;
			m_TestState = STATE_OVER;
			//}
		}
		break;
	//���ַ���
	case STATE_DISPLAYFEEDBACK:
		QueryPerformanceCounter(&litmp);
		QPart4 = litmp.QuadPart;         //�����ֵֹ
		dfMinus = (double)(QPart4-QPart3);
		dfTim = dfMinus / dfFreq;        // ��ö�Ӧ��ʱ��ֵ����λΪ��	
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
	//����ѡ���
    case STATE_DISPLAYOPTION:            
		break;
	//���Խ���
	case STATE_OVER: 
/*		QueryPerformanceCounter(&litmp);
		QPart2 = litmp.QuadPart;         //�����ֵֹ
		dfMinus = (double)(QPart2-QPart1);
		dfTim = dfMinus / dfFreq;        // ��ö�Ӧ��ʱ��ֵ����λΪ��	
		//2000ms
		if (dfTim >= TimeInt)
		{
            PostThreadMessage(dwInputThreadID, WM_THREADSTOP,0,0); 	
			m_TestState = STATE_EXIT;
		}*/	
		//SendMessage(hWnd, WM_DESTROY, 0, 0);

		break;
	//�����˳�
    case STATE_EXIT: 
		if (g_nThreadExitCount == 1)
		{
			SendMessage(hWnd, WM_CLOSE, 0, 0); // �رմ���
			SendMessage(hWnd, WM_DESTROY, 0, 0);
		}
		break;
	default:
		break;
	}
}

//************************************************
//*���ݸ������߳�
//************************************************
DWORD WINAPI t3::InputThreadProcedure(LPVOID lpStartupParam)
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
		//�����ⲿ��Ϣ
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
						//���ֿ�ʼѡ��ȴ����������ʼ����
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
								//��ͻ���¼�ʱ����ȷ��
								for(i=0; i<1 ;i++)
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
                                       //ȷ���˺����������룬�����޸�feedback��ֵ
										if(m_TrialType == TRIAL_PRACTICE && !m_bShowFeedback)
										{
											//��ϰ״̬���ַ���
											sprintf(szFeedBack,"%s ��Ӧʱ��Ϊ%dms", FeedBack[m_bEventAcc],m_EventSureTime[m_RecordNo] - m_EventStartTime[m_RecordNo]);
											QueryPerformanceCounter(&litmp);
											QPart3 = litmp.QuadPart;           // ��ó�ʼֵ
											TimeInt = 1;

											if (!m_Setting.m_MainTask)
												m_TestState = STATE_DISPLAYFEEDBACK;
											else
												m_bShowFeedback = TRUE;
											dfTotalEvent = 0;
										}
										else if(m_TrialType == TRIAL_EXPERMENT)
										{
											//��ʽ����״̬�����ַ���
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
	//									m_SureDownNum++;
										break;
									}
								}
							}
							else
							{
								//û��ͻ���¼�ʱ����ȷ��
								for(i=0; i<1 ;i++)
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
					//���Թ����л�ò��ݸ�����
	   				if(m_Setting.m_MainTask == 1)
					{
						JoyX = GetXAxis();//GetYAxis();//
						JoyY = GetYAxis();//-GetZAxis();
					}
					break;
				case STATE_OVER: 
					//���Խ������ȴ���������˳�
					if(m_SureDownNum == 0)
					{
						for(i=0;i<12;i++)
						{
							if(IsButtonDown(i))
							{
     	 						PostThreadMessage(dwInputThreadID, WM_THREADSTOP,0,0); 	
								m_TestState = STATE_NEXT;// STATE_EXIT --> STATE_NEXT
								//return 0;
							}
						}
					}
				    break;
				default:
					break;
				}
				//���㵱ǰ�����¼�����������ȷ���Ƿ����µļ�����
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
			//�Լ��̴�����ݸ�
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
//*������
//************************************************
int APIENTRY t3::_tWinMain(HINSTANCE &hInstance,
	HINSTANCE &hPrevInstance,
	LPTSTR    &lpCmdLine,
	int       &nCmdShow, HWND &_hWnd,
	std::string winClassName, std::string winName)
{
	// ��ʼ�������״̬
	bool bUnClosedLastWin = true;
	hWnd = _hWnd;
	gHinstance = hInstance;
	g_nThreadExitCount = 0;
	ShowCursor(FALSE);


	//��ô��ݵ������в������õ����������ֺ�������
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

    //��ȡ��������
	if(!ReadSetting())
	{
        MessageBox(hWnd,"���������ļ���ʽ����","��������", MB_OK);
		return 0;
	}

    //ע�ᴰ����
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

    //��������
    /*hWnd = CreateWindow( "ClassName", "Task1", 
                              WS_VISIBLE|WS_POPUP, 0, 0, 1024, 768,
                              NULL, NULL, hInstance, NULL );*/

	_hWnd = hWnd = CreateWindow(std::to_string(nCmdShow).c_str(), std::to_string(nCmdShow).c_str(),
    WS_VISIBLE|WS_POPUP, 0, 0, x_resolution, y_resolution,
    NULL, NULL, hInstance, NULL );
  
	//��ʾ������
	SetFocus(hWnd);
	//ShowCursor(FALSE);

    //��ʾ������
//	ShowWindow( hWnd, SW_HIDE );
//	UpdateWindow( hWnd );
    
	//����DirectX�豸
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
	//���ò��ݸ˱仯��Χ
	if (JoystickInit(hWnd, -m_JoySpeedMax, m_JoySpeedMax, 1))
	{
		JoystickUpdate();
	}
	else
	{
		MessageBox(hWnd,"������ݸ������Ƿ���ȷ��","��������", MB_OK);
		return 0;
	}  
	//�ر����뷨
	HKL hkl;
    hkl = LoadKeyboardLayout("00000804",KLF_ACTIVATE);  
	if(hkl != NULL)
	{
		ActivateKeyboardLayout(hkl,KLF_SETFORPROCESS);
	}
    //ShowCursor(FALSE);

	//�������ݸ������߳�
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
    srand((unsigned)time(NULL)); //��ʼ��������� 

	//��ʼ��Direct3D
    if( SUCCEEDED( InitD3D( hWnd ) ) )
    {	
		//������Ϣѭ��
		MSG msg;
		ZeroMemory( &msg, sizeof(msg) );
		while( msg.message!=WM_QUIT )
		{
			if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
			{
				//�����ⲿ��Ϣ
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
			else
			{
				//ִ�в��Թ���
				UpdateState();			    
				if( m_bDisplayReady )
				{
					//��Ⱦͼ��
					Render();  
					hideLastWindow(bUnClosedLastWin, winClassName, winName, hInstance);
				}
			}
			Sleep(1);
			// �����¡���һ�����񡱻��˳���ʱ����ֹ��Ϣѭ��
			if (m_TestState == STATE_NEXT
				|| m_TestState == STATE_EXIT)
			{
				Sleep(50);
				break;
			}
		}
    }
	ShowCursor(TRUE);
	CloseHandle(h);
	return rtn;
}

void t3::hideLastWindow(bool &bUnClosedLastWin, std::string &winClassName, std::string &winName, HINSTANCE &hInstance)
{
	if (bUnClosedLastWin)
	{
		bUnClosedLastWin = false;
		// ������һ������
		HWND tmpHw = FindWindow(winClassName.c_str(), winName.c_str());
		if (winClassName != "") // ����Ƿ��ǵ�һ������
		{
			ShowWindow(tmpHw, 0);
			UnregisterClass(winClassName.c_str(), hInstance);
		}
	}
}