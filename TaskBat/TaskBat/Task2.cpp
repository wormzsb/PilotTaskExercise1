// Task2.cpp : Defines the entry point for the application.
//
#include "stdafx.h"
#include "Task2.h"
#include "Helper.h"

Helper t2::hp;

int t2::iDirection;
int t2::rtn;//���򷵻�ֵ
HINSTANCE t2::gHinstance;//ȫ�־��
float t2::acce = 0;  //Ŀ����ٶ�
int t2::g_nThreadExitCount = 0;             //��ǰ���е��߳���
DWORD t2::dwInputThreadID = 0;              //��׼�������߳�ID      
double t2::alpha, t2::omiga, t2::a, t2::b, 
t2::r, t2::Rx, t2::Ry, t2::fai, t2::AngleSpeed;
float t2::r1, t2::r2;
short t2::m_TrackState;
POINT t2::A, t2::C;
double t2::v;
double t2::m_PointX, t2::m_PointY;
double t2::m_PostPointX, t2::m_PostPointY;       //��ǰ��׼������
int t2::JoyX, t2::JoyY;                          //��ǰ���ݸ�����ֵ     
struct TaskSetting2   t2::m_Setting;        //����2���ò���
struct HardSetting   t2::m_HardSetting;     //Ӳ�����ò���
struct PartInfo   t2::m_PartInfo;           //��������Ϣ
short t2::m_TrialType;						//��������
int t2::m_TrialTime;						//����ʱ��
int t2::m_TrialTimes;						//���Դ���
int t2::iJoyMoveDirection;
//enum TRACE_STATE{AB,BD,DC,CA,AD,DB,BC,CD,DA,AC,CB,BA};               //Ŀ���˶��켣

int t2::x_resolution = 1024;            //��Ļ�ֱ���
int t2::y_resolution = 768;             //��Ļ�ֱ���
const float t2::FontScale = (float)(t2::x_resolution + t2::y_resolution) / 1400.0;    //��������Ļ�ֱ��ʵķ����߶�

const char t2::Insturction1[] = "    ��Ļ�ϵİ�ɫ���͡���Ŀ�꣬��ɫ���͡���׷�ٻ�����������\
�ǣ�ʹ�ò��ݸ�������׷�ٻ����˶�����������׷�ٻ���סĿ�ꡣ׷�ٻ���ס\
Ŀ��ʱ��׷�ٻ����ɺ�ɫ����E����ʼ����\n\
    ����׷�������ͬʱ����Ļ���Ͻǵķ����ڲ��ϳ��ָ��ֳ��ȵ�ʱ�䣬\
������ʱ�ź�ʱ�����֡���ʱ��ʼ��ʱ��������Ϊ��ȥ��ʱ������Ļ�ϳ���\
��ʱ�����ʱ�������ְ�E��ֹͣ��ʱ��";
const char t2::Insturction2[] = "��ϰ�������������������ʽʵ�顣";
const char t2::Insturction3[] = "���������,�������������";
char t2::m_TimeStr[10];                     //����ʱ����ʾ�ַ���
BOOL t2::bShowFeedBack = FALSE;
LPDIRECT3D9             t2::g_pD3D = NULL;             //directx3d����
LPDIRECT3DDEVICE9       t2::g_pd3dDevice = NULL;             //directx�豸����
LPDIRECT3DTEXTURE9      t2::g_pTextureInst = NULL;          //�������
LPDIRECT3DTEXTURE9      t2::g_pTexture0  = NULL;             //�������
LPDIRECT3DTEXTURE9      t2::g_pTexture1  = NULL;             //�������
LPDIRECT3DTEXTURE9      t2::g_pTexture2  = NULL;             //�������
LPDIRECT3DTEXTURE9      t2::g_pTexture3  = NULL;             //�������
LPD3DXSPRITE            t2::g_pSprite  = NULL;               //�������
LPD3DXFONT              t2::g_pFont      = 0;				 //�������
LPD3DXFONT              t2::g_pFont1     = 0;				 //�������
LPD3DXFONT              t2::g_pFontEng     = 0;				 //�������
LPDIRECT3DVERTEXBUFFER9      t2::m_pVertexBuffer = NULL;    //�������
D3DXMATRIX t2::m_Transform;                                  //����任����
float t2::TimeInt;										     //ʱ����
short t2::m_TrialCount;                                      //���Դ���
short t2::m_HoldNo;                                          //ʱ�䱣�����     
BOOL t2::m_bDisplayReady;								     //��Ⱦ�豸������־
short t2::m_SureDownNum;
POINT t2::m_IndicatorPoint;                                  //ʱ�䱣�ֿ�ʼָʾ������
BOOL t2::m_bHoldStart;                                       //ʱ�䱣�ֿ�ʼ��־
BOOL t2::m_bShowSign;                                        //ʱ�䱣�ֿ�ʼָʾ����ʾ��־
BOOL t2::m_bShowTime;

char t2::FeedBack[30];                                       //���ַ����ַ���

//#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

const double t2::m_MoveInt = 0.04;
double t2::m_SampleInt;                                      //�������40ms

UINT t2::m_PointNum;
UINT t2::m_MemNum;
long *t2::m_HoldStartTime = NULL;                   //���ʱ�䱣�ֿ�ʼʱ�������
long *t2::m_HoldSureTime = NULL;                    //���ʱ�䱣��ȷ��ʱ������� 
int *t2::m_HoldTimeOrder = NULL;                             //���ʱ�䱣����ֵ������
float *t2::m_HoldTime = NULL;                                  //��ű���ʱ�������
BOOL *t2::m_bHit = NULL;                                     //��Ż���״̬������
SPOINT *t2::m_ObjPoint = NULL;                               //���Ŀ�����������
SPOINT *t2::m_PostPoint = NULL;                              //�����׼�����������
unsigned long *t2::m_PointTime = NULL;                       //��Ų���ʱ�������
float *t2::m_Distance = NULL;                                //���Ŀ�����׼�����������
float *t2::m_ObjSpeedX = NULL;                               //���Ŀ���ٶȵ�����
float *t2::m_ObjSpeedY = NULL;                               //���Ŀ���ٶȵ�����
float *t2::m_PostSpeedX = NULL;                              //�����׼���ٶȵ�����
float *t2::m_PostSpeedY = NULL;                              //�����׼���ٶȵ�����
RECT t2::strurect, t2::lerect, t2::rerect, t2::erect, t2::txtrect;

short t2::m_TestState;
char t2::m_file1[220];
char t2::m_file2[220];
HWND t2::hWnd;
char t2::m_TesterName[40];
char t2::m_DataName[60];
char t2::m_TaskNumStr[100];
int t2::m_Condition;

int t2::rec_x_begin;
int t2::rec_y_begin;
int t2::rec_x_end;
int t2::rec_y_end;

//Timer
LARGE_INTEGER t2::litmp;
LONGLONG t2::QPart1, t2::QPart2;
double t2::dfMinus, t2::dfFreq, t2::dfTim, t2::dfTotal, t2::dfTotalMove;

//************************************************
//*����Ŀ�����׼����ǰ���˶�״̬
//************************************************
VOID t2::MoveTrace()
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

	//��ǰ׷�ٻ�λ��
	//double JoyAlpha = 0;
	//JoyAlpha = atan(fabs((double)(JoyY - m_PostPointY) / (double)(JoyX - m_PostPointX)));//ҡ�˽Ƕ�
	//m_PostPointX = m_PostPointX + iJoyMoveDirection * cos(JoyAlpha) * m_PostSpeedX[m_PointNum - 1] * dfTim;
	//m_PostPointY = m_PostPointY + iJoyMoveDirection * sin(JoyAlpha) * m_PostSpeedY[m_PointNum - 1] * dfTim;
	//m_PostPoint[m_PointNum].x = m_PostPointX;
	//m_PostPoint[m_PointNum].y = m_PostPointY;
	
	//��ǰ׷�ٻ�λ��
	double JoyAlpha = 0;//ҡ�˽Ƕ�
	/*if (!(JoyX == 0 && JoyY == 0)) {
		double rJ = sqrt(JoyX * JoyX + JoyY * JoyY);
		double cosJ = (double)JoyX / rJ;
		double sinJ = (double)JoyY / rJ;
		m_PostPointX = m_PostPointX + cosJ * rJ  * dfTim;
		m_PostPointY = m_PostPointY + sinJ * rJ  * dfTim;
	}*/
	hp.updateAnalogNewPos(m_PostPointX, m_PostPointY, JoyX, JoyY, dfTim, iJoyMoveDirection);

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
	SetRect( &txtrect, m_ObjPoint[m_PointNum].x-128, m_ObjPoint[m_PointNum].y -44, m_ObjPoint[m_PointNum].x, m_ObjPoint[m_PointNum].y -44 );

}

//************************************************
//*��ȡ��ǰ��������
//************************************************
BOOL t2::ReadSetting()
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
	char m_tasknostr[100];
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
			//Task2
	//		fscanf(fp,"[Task2]\n");
			fscanf(fp,"TaskName\t%s\n",m_Setting.m_TaskName);
			fscanf(fp,"PracMode\t%d\n",&m_Setting.m_PracMode);
			fscanf(fp,"ExperMode\t%d\n",&m_Setting.m_ExperMode);
			fscanf(fp,"MainTask\t%d\n",&m_Setting.m_MainTask);
			fscanf(fp,"SubTask\t%d\n",&m_Setting.m_SubTask);
			fscanf(fp,"Background\t%d\n",&m_Setting.m_Background);
			fscanf(fp,"Direction\t%d\n",&m_Setting.m_Direction);
			fscanf(fp,"InitSpeed\t%f\n",&m_Setting.m_InitSpeed);
			fscanf(fp,"HoldTimeNum\t%d\n",&m_Setting.m_HoldTimeNum);
			fscanf(fp,"HoldTime1\t%f\n",&m_Setting.m_HoldTime[0]);
			fscanf(fp,"HoldTime2\t%f\n",&m_Setting.m_HoldTime[1]);
			fscanf(fp,"HoldTime3\t%f\n",&m_Setting.m_HoldTime[2]);
			fscanf(fp,"HoldTime4\t%f\n",&m_Setting.m_HoldTime[3]);
			fscanf(fp,"HoldTime5\t%f\n",&m_Setting.m_HoldTime[4]);
			fscanf(fp,"HoldTime6\t%f\n",&m_Setting.m_HoldTime[5]);
			fscanf(fp,"HoldTime7\t%f\n",&m_Setting.m_HoldTime[6]);
			fscanf(fp,"HoldTime8\t%f\n",&m_Setting.m_HoldTime[7]);
			fscanf(fp,"HoldTime9\t%f\n",&m_Setting.m_HoldTime[8]);
			fscanf(fp,"HoldTime10\t%f\n",&m_Setting.m_HoldTime[9]);
			fscanf(fp,"HoldTime11\t%f\n",&m_Setting.m_HoldTime[10]);
			fscanf(fp,"HoldTime12\t%f\n",&m_Setting.m_HoldTime[11]);
			fscanf(fp,"PracTime\t%d\n",&m_Setting.m_PracTime);
			fscanf(fp,"ExperTime\t%d\n",&m_Setting.m_ExperTime);
			fscanf(fp,"PracTimes\t%d\n",&m_Setting.m_PracTimes);
			fscanf(fp,"ExperTimes\t%d\n",&m_Setting.m_ExperTimes);
			fscanf(fp,"JoyMoveDirection\t%d\n",&m_Setting.m_iJoyMoveDirection);
			fscanf(fp,"SubTaskInterval\t%d\n",&m_Setting.m_iSubTaskInterval);
			fscanf(fp,"SpeedMode\t%d\n",&m_Setting.m_SpeedMode);
			fscanf(fp,"Speed\t%f\n",&m_Setting.m_Speed);
			fscanf(fp,"SpeedMin\t%f\n",&m_Setting.m_SpeedMin);
			fscanf(fp,"SpeedMax\t%f\n",&m_Setting.m_SpeedMax);
			fscanf(fp,"AccelerationMin\t%f\n",&m_Setting.m_AccelerationMin);
			fscanf(fp,"AccelerationMax\t%f\n",&m_Setting.m_AccelerationMax);
			fscanf(fp,"Track\t%d\n",&m_Setting.m_iTrack);
		
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
VOID t2::SaveName()
{
	FILE *fp;
	char m_DataDir[160];
	char m_filename1[160];
	char m_filename2[160];

	SYSTEMTIME CurTime;
	GetLocalTime(&CurTime);
	if(strlen(m_DataName)==0)
	{
	    sprintf(m_filename1, "T2-trace-%d%02d%02d%02d%02d%02d.txt", CurTime.wYear, CurTime.wMonth, CurTime.wDay, CurTime.wHour, CurTime.wMinute, CurTime.wSecond);
		sprintf(m_filename2, "T2-hold-%d%02d%02d%02d%02d%02d.txt", CurTime.wYear, CurTime.wMonth, CurTime.wDay, CurTime.wHour, CurTime.wMinute, CurTime.wSecond);
	}
	else
	{
		sprintf(m_filename1, "T2-trace-%s-%s-%d%02d%02d%02d%02d%02d.txt", m_TaskNumStr, m_DataName, CurTime.wYear, CurTime.wMonth, CurTime.wDay, CurTime.wHour, CurTime.wMinute, CurTime.wSecond);
		sprintf(m_filename2, "T2-hold-%s-%s-%d%02d%02d%02d%02d%02d.txt", m_TaskNumStr, m_DataName, CurTime.wYear, CurTime.wMonth, CurTime.wDay, CurTime.wHour, CurTime.wMinute, CurTime.wSecond);
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
			"Background\tDirection\tInitSpeed\t"
			"HoldTimeNum\tHoldTime1\tHoldTime2\tHoldTime3\tHoldTime4\tHoldTime5\tHoldTime6\tHoldTime7\tHoldTime8\tHoldTime9\tHoldTime10\tHoldTime11\tHoldTime12\tPracTime\tExperTime\tPracTimes\tExperTimes\t"
			"Pra_Test\tPointNum\tPointTime\tObjPointX\tObjPointY\tPostPointX\tPostPointY\tDistance\tHit\t"
			"ObjSpeedX\tObjSpeedY\tPostSpeedX\tPostSpeedY\n");
		fclose(fp);
	}
    if(m_Setting.m_SubTask == 1)
	{
		fp = fopen(m_file2,"at");
		fprintf(fp,"ID\tName\tSex\tSession\t"
			"DistanceError\tPracMode\tExperMode\tMainTask\tSubTask\t"
			"Background\tDirection\tInitSpeed\t"
			"HoldTimeNum\tHoldTime1\tHoldTime2\tHoldTime3\tHoldTime4\tHoldTime5\tHoldTime6\tHoldTime7\tHoldTime8\tHoldTime9\tHoldTime10\tHoldTime11\tHoldTime12\tPracTime\tExperTime\tPracTimes\tExperTimes\t"
			"Pra_Test\tHoldNum\tHoldTime\tStartTime\tSureTime\tTest_RT\tHoldError\tError_Ratio\n");
		fclose(fp);
	}
}

//************************************************
//*���������ݼ�¼�ļ�
//************************************************
VOID t2::SaveData()
{
	FILE *fp;
	int i;

    long m_TestRT;
	int m_HoldError;
	double m_ErrorRatio;
	//����׷������
	if(m_Setting.m_MainTask == 1)
	{
		fp = fopen(m_file1,"at");
		for(i=0;i<m_PointNum;i++)
		{
			fprintf(fp,"%s\t%s\t%s\t%d\t"
				"%.2f\t%d\t%d\t%d\t%d\t"
				"%d\t%d\t%.2f\t"
				"%d\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%d\t%d\t%d\t%d\t"
				"%d\t%d\t%u\t%d\t%d\t%d\t%d\t%.2f\t%d\t"
				"%.2f\t%.2f\t%.2f\t%.2f\n",
				m_PartInfo.m_TesterNo, m_PartInfo.m_TesterName, m_PartInfo.m_TesterSex, m_PartInfo.m_Session, 
				m_HardSetting.m_DistanceError, m_Setting.m_PracMode, m_Setting.m_ExperMode, m_Setting.m_MainTask, m_Setting.m_SubTask,
				m_Setting.m_Background, m_Setting.m_Direction, m_Setting.m_InitSpeed, 
				m_Setting.m_HoldTimeNum, m_Setting.m_HoldTime[0], m_Setting.m_HoldTime[1], m_Setting.m_HoldTime[2], m_Setting.m_HoldTime[3], m_Setting.m_HoldTime[4], m_Setting.m_HoldTime[5], m_Setting.m_HoldTime[6], m_Setting.m_HoldTime[7], m_Setting.m_HoldTime[8], m_Setting.m_HoldTime[9], m_Setting.m_HoldTime[10], m_Setting.m_HoldTime[11], m_Setting.m_PracTime, m_Setting.m_ExperTime, m_Setting.m_PracTimes, m_Setting.m_ExperTimes,
				m_TrialType, i+1, m_PointTime[i], m_ObjPoint[i].x, m_ObjPoint[i].y, m_PostPoint[i].x, m_PostPoint[i].y, m_Distance[i], m_bHit[i],
				m_ObjSpeedX[i], m_ObjSpeedY[i], m_PostSpeedX[i], m_PostSpeedY[i]);		
		}
		fclose(fp);
	}
	//����ʱ�䱣������
	if(m_Setting.m_SubTask == 1)
	{
		fp = fopen(m_file2,"at");
		for(i=0;i<m_HoldNo;i++)
		{
			if (m_HoldSureTime[i] == -1)
			{
				m_TestRT = -1;
				m_HoldError = -1;
				m_ErrorRatio = -1;
			}
			else
			{
				m_TestRT = m_HoldSureTime[i] - m_HoldStartTime[i];
				m_HoldError = m_TestRT - m_HoldTime[i]*1000;
				m_ErrorRatio = (double)(m_HoldError) / (double)(m_HoldTime[i] * 1000.0);
			}
			
			fprintf(fp,"%s\t%s\t%s\t%d\t"
				"%.2f\t%d\t%d\t%d\t%d\t"
				"%d\t%d\t%.2f\t"
				"%d\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%d\t%d\t%d\t%d\t"
				"%d\t%d\t%d\t%d\t%d\t%d\t%d\t%.2lf\n",
				m_PartInfo.m_TesterNo, m_PartInfo.m_TesterName, m_PartInfo.m_TesterSex, m_PartInfo.m_Session, 
				m_HardSetting.m_DistanceError, m_Setting.m_PracMode, m_Setting.m_ExperMode, m_Setting.m_MainTask, m_Setting.m_SubTask,
				m_Setting.m_Background, m_Setting.m_Direction, m_Setting.m_InitSpeed, 
				m_Setting.m_HoldTimeNum, m_Setting.m_HoldTime[0], m_Setting.m_HoldTime[1], m_Setting.m_HoldTime[2], m_Setting.m_HoldTime[3], m_Setting.m_HoldTime[4], m_Setting.m_HoldTime[5], m_Setting.m_HoldTime[6], m_Setting.m_HoldTime[7], m_Setting.m_HoldTime[8], m_Setting.m_HoldTime[9], m_Setting.m_HoldTime[10], m_Setting.m_HoldTime[11], m_Setting.m_PracTime, m_Setting.m_ExperTime, m_Setting.m_PracTimes, m_Setting.m_ExperTimes,
				m_TrialType, i+1,int(m_HoldTime[i]*1000), m_HoldStartTime[i], m_HoldSureTime[i], m_TestRT, m_HoldError, m_ErrorRatio);
		}
		fclose(fp);
	}
}

//************************************************
//*��ʼ��DirectX 3D
//************************************************
HRESULT t2::InitD3D( HWND hWnd )
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

	if (m_Setting.m_iJoyMoveDirection == 0)
		iJoyMoveDirection = 1;
	else
		iJoyMoveDirection = -1;


	//���ʴ�С
//	SetRect( &rct, 0, 0, 128, 128 );
    SetRect( &strurect, x_resolution/2-300*FontScale, y_resolution/2-180*FontScale, x_resolution/2+300*FontScale, y_resolution/2+20*FontScale );
    SetRect( &erect, x_resolution/2-300*FontScale, y_resolution/2-100*FontScale, x_resolution/2+300*FontScale, y_resolution/2+100*FontScale );
	//SetRect( &txtrect, 0, 0, x_resolution/4, y_resolution/8 );
    SetRect( &lerect, x_resolution/2-250*FontScale, y_resolution/2-50*FontScale, x_resolution/2-50*FontScale, y_resolution/2+100*FontScale );
	SetRect( &rerect, x_resolution/2+50*FontScale, y_resolution/2-50*FontScale, x_resolution/2+250*FontScale, y_resolution/2+100*FontScale );
    
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


	//��������
    if( FAILED( D3DXCreateSprite( g_pd3dDevice, &g_pSprite )))
	{
		MessageBox(NULL, "Could not find banana.bmp", "Textures.exe", MB_OK);
		return E_FAIL;
	}

	//��������ͼƬ
	if(m_Setting.m_MainTask&&m_Setting.m_SubTask)
	{
		if (m_Setting.m_iJoyMoveDirection == 0) {
			if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, "Pics\\Inst\\DT_timing_track.jpg", &g_pTextureInst)))
			{
				MessageBox(NULL, "Could not find banana.bmp", "Textures.exe", MB_OK);
				return E_FAIL;
			}
		}
		else
		{
			if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, "Pics\\Inst\\DT_timing_track_a.jpg", &g_pTextureInst)))
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
		if( FAILED( D3DXCreateTextureFromFile( g_pd3dDevice, "Pics\\Inst\\ST_timing.jpg", &g_pTextureInst ) ) )
		{
			MessageBox(NULL, "Could not find banana.bmp", "Textures.exe", MB_OK);
			return E_FAIL;
		}
	}

	if( FAILED( D3DXCreateTextureFromFile( g_pd3dDevice, "Pics\\Task2\\obj_white.bmp", &g_pTexture0 ) ) )
	{
		MessageBox(NULL, "Could not find banana.bmp", "Textures.exe", MB_OK);
		return E_FAIL;
	}
	if( FAILED( D3DXCreateTextureFromFile( g_pd3dDevice, "Pics\\Task2\\post_yellow.bmp", &g_pTexture1 ) ) )
	{
		MessageBox(NULL, "Could not find banana.bmp", "Textures.exe", MB_OK);
		return E_FAIL;
	}
    if( FAILED( D3DXCreateTextureFromFile( g_pd3dDevice, "Pics\\Task2\\post_red.bmp", &g_pTexture2 ) ) )
	{
		MessageBox(NULL, "Could not find banana.bmp", "Textures.exe", MB_OK);
		return E_FAIL;
	}
    if( FAILED( D3DXCreateTextureFromFile( g_pd3dDevice, "Pics\\Task2\\indicator_green.bmp", &g_pTexture3 ) ) )
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
    if (FAILED(D3DXCreateFont(g_pd3dDevice,30*FontScale,12*FontScale,20,
		                      0,0,GB2312_CHARSET,0,0,0, "����", &g_pFontEng)))
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

	// Initialize and configure DirectSound
    SaveName();
    return S_OK;
}

//************************************************
//*�ͷ������ڴ�
//************************************************
VOID t2::CleanupMem()
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
	if(m_HoldStartTime != NULL)
	{
		free(m_HoldStartTime);
		m_HoldStartTime = NULL;
	}
	if(m_HoldSureTime != NULL)
	{
		free(m_HoldSureTime);
		m_HoldSureTime = NULL;
	}
	if(m_HoldTimeOrder != NULL)
	{
		free(m_HoldTimeOrder);
		m_HoldTimeOrder = NULL;
	}
	if(m_HoldTime != NULL)
	{
		free(m_HoldTime);
		m_HoldTime = NULL;
	}
	if(m_bHit != NULL)
	{
		free(m_bHit);
		m_bHit = NULL;
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
VOID t2::Cleanup()
{
	//�ͷ��������
	if(g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}
	if(g_pFontEng != NULL)
	{
		g_pFontEng->Release();
		g_pFontEng = NULL;
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
	if( g_pTexture3!=NULL)
	{
		g_pTexture3->Release();
		g_pTexture3 = NULL;
	}
	if( g_pSprite!=NULL)
	{
		g_pSprite->Release();
		g_pSprite = NULL;
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
VOID t2::Render()
{
	switch(m_TestState)
	{
    //����ָ����
	case STATE_DISPLAYINSTURCTION:
//		g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255,255,255), 0.0f, 0 );
//		break;
	//����ִ�й���
	case STATE_DISPLAYOBJ:  
	case STATE_DISPLAYFEEDBACK:
	case STATE_MOVINGOBJ: 
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
    	switch(m_TestState)
		{
        //����ָ����
		case STATE_DISPLAYINSTURCTION:
			if ( SUCCEEDED( g_pSprite->Begin(D3DXSPRITE_ALPHABLEND) ) )
			{
				D3DXMatrixTransformation2D(&mx, NULL, 0.0, &D3DXVECTOR2((float)1024/(float)1024,(float)768/(float)1024), &D3DXVECTOR2(0,0), NULL, &D3DXVECTOR2(x_resolution/2,y_resolution/2));
				g_pSprite->SetTransform(&mx);
			    g_pSprite->Draw(g_pTextureInst, NULL, &D3DXVECTOR3(512,512,0), &D3DXVECTOR3(0,0,0), 0xffffffff);
//			g_pFont->DrawText(NULL, Insturction1, -1, &erect,
//				DT_WORDBREAK|DT_NOCLIP|DT_VCENTER, D3DCOLOR_XRGB(255,0,0));
			}
			g_pSprite->End();
			break;

		//����ִ�й���
        case STATE_DISPLAYOBJ:  
		case STATE_MOVINGOBJ: {
			
			double JoyAlpha = 0;
			JoyAlpha = atan(fabs((double)(JoyY - m_PostPointY) / (double)(JoyX - m_PostPointX)));//ҡ�˽Ƕ�
			
			if (SUCCEEDED(g_pSprite->Begin(D3DXSPRITE_ALPHABLEND)))
			{
				if (m_Setting.m_MainTask == 1)
				{
					D3DXMatrixTransformation2D(&mx, NULL, 0.0, &D3DXVECTOR2((float)128 / (float)128, (float)32 / (float)32), &D3DXVECTOR2(0, 0), 0, &D3DXVECTOR2(m_PostPoint[m_PointNum].x, m_PostPoint[m_PointNum].y));
					g_pSprite->SetTransform(&mx);
					if (m_bHit[m_PointNum])
					{
						g_pSprite->Draw(g_pTexture2, NULL, &D3DXVECTOR3(64, 20, 0), &D3DXVECTOR3(0, 0, 0), 0xffffffff);

					}
					else
					{
						g_pSprite->Draw(g_pTexture1, NULL, &D3DXVECTOR3(64, 20, 0), &D3DXVECTOR3(0, 0, 0), 0xffffffff);
					}
				}
				D3DXMatrixTransformation2D(&mx, NULL, 0.0, &D3DXVECTOR2((float)64 / (float)64, (float)16 / (float)16), &D3DXVECTOR2(0, 0), 0, &D3DXVECTOR2(m_ObjPoint[m_PointNum].x, m_ObjPoint[m_PointNum].y));
				g_pSprite->SetTransform(&mx);
				g_pSprite->Draw(g_pTexture0, NULL, &D3DXVECTOR3(32, 12, 0), &D3DXVECTOR3(0, 0, 0), 0xffffffff);
				if (m_bShowSign)
				{
					D3DXMatrixTransformation2D(&mx, NULL, 0.0, &D3DXVECTOR2((float)32 / (float)32, (float)32 / (float)32), &D3DXVECTOR2(0, 0), 0, &D3DXVECTOR2(m_ObjPoint[m_PointNum].x + 32, m_ObjPoint[m_PointNum].y - 28));
					g_pSprite->SetTransform(&mx);
					g_pSprite->Draw(g_pTexture3, NULL, &D3DXVECTOR3(16, 16, 0), &D3DXVECTOR3(0, 0, 0), 0xffffffff);
				}
			}
			g_pSprite->End();
			if (m_Setting.m_SubTask == 1)
			{
				if (bShowFeedBack)
				{
					g_pFontEng->DrawText(NULL, FeedBack, -1, &txtrect,
						DT_WORDBREAK | DT_NOCLIP | DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(255, 255, 255));
				}
				else if (m_bShowTime)
				{
					g_pFontEng->DrawText(NULL, m_TimeStr, -1, &txtrect,
						DT_WORDBREAK | DT_NOCLIP | DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(255, 255, 255));
				}
			}


			break;
		}
		//���ַ���
		case STATE_DISPLAYFEEDBACK:
			g_pFont1->DrawText(NULL, FeedBack, -1, &erect,
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

//************************************************
//*���������ʼ��
//************************************************
VOID t2::TestInit()
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
		//v = m_Setting.m_InitSpeed;
		m_TrackState = AB;
		A.x = a-Rx;
		A.y = b-Ry;
		C.x = a+Rx;
		C.y = b+Ry;	
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
		m_PointX = A.x;
		m_PointY = A.y;
		//m_ObjPoint[m_PointNum].x = m_PointX;
		//m_ObjPoint[m_PointNum].y = m_PointY; 
		m_Distance[m_PointNum] = pow(pow((m_ObjPoint[m_PointNum].y-m_PostPoint[m_PointNum].y),2.0)+pow((m_ObjPoint[m_PointNum].x-m_PostPoint[m_PointNum].x),2.0),0.5);
		m_ObjSpeedX[m_PointNum] = v;
		m_ObjSpeedY[m_PointNum] = 0;
		
		m_bHit[m_PointNum] = FALSE;
		JoyX = 0;
		JoyY = 0;
	}
	if(m_Setting.m_SubTask == 1)
	{
		if(m_TrialType == TRIAL_PRACTICE)
		{
			m_TrialTimes = m_Setting.m_PracTimes;
		}
		else
		{
			m_TrialTimes = m_Setting.m_ExperTimes;
		}
		if(m_Setting.m_MainTask != 1)
		{
			a = x_resolution / 2;
			b = y_resolution / 2;
			r1 = 300;
			r2 = 200;
			Rx = 400;
			Ry = 200;

			m_PointX = a+r1;
			m_PointY = b;
			m_PointNum = 0;
			m_MemNum = 1;
			m_ObjPoint = (SPOINT*)malloc(m_MemNum*sizeof(SPOINT));
			m_ObjPoint[m_PointNum].x = m_PointX;
			m_ObjPoint[m_PointNum].y = m_PointY; 
			SetRect( &txtrect, m_PointX-128, m_PointY-44, m_PointX, m_PointY-44 );
		    m_IndicatorPoint.x = m_PointX+32;
	        m_IndicatorPoint.y = m_PointY-28;
			JoyX = 100;
		    JoyY = 100;
		}
		m_bHoldStart = FALSE;
		m_bShowSign = FALSE;
		m_bShowTime = FALSE;
		m_TrialCount = m_TrialTimes * m_Setting.m_HoldTimeNum;
		m_HoldStartTime = (long*)malloc(m_TrialCount*sizeof(long));
		m_HoldSureTime = (long*)malloc(m_TrialCount*sizeof(long));
		m_HoldTimeOrder = (int*)malloc(m_TrialCount*sizeof(int));
		m_HoldTime = (float*)malloc(m_TrialCount*sizeof(float));
		RandOrder(m_TrialCount,m_HoldTimeOrder);
		m_HoldNo = 0;
	}

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

//��ͣ�Ի�����Ϣѭ��
BOOL CALLBACK t2::PauseMsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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
LRESULT WINAPI t2::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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
VOID t2::UpdateState()
{
    switch(m_TestState)
	{
	//����ָ����
    case STATE_DISPLAYINSTURCTION:       
        break;
	//����Ŀ��
	case STATE_DISPLAYOBJ:
		if(abs(JoyX)>20||abs(JoyY)>20)
		{
			if(QueryPerformanceFrequency(&litmp))
			{
				dfFreq = (double)litmp.QuadPart;// ��ü�������ʱ��Ƶ��
				m_SampleInt = m_MoveInt * dfFreq;
			}
		    QueryPerformanceCounter(&litmp);
			QPart1 = litmp.QuadPart;           // ��ó�ʼֵ
			dfTotal = 0;
			dfTotalMove = 0;
			if(m_Setting.m_MainTask == 1)
			{
				m_PointTime[m_PointNum] = QPart1/dfFreq*1000;
				m_PostSpeedX[m_PointNum] = JoyX;
				m_PostSpeedY[m_PointNum] = JoyY;
			}
            m_TestState = STATE_MOVINGOBJ;
		}
		break;
	//��������ִ��
    case STATE_MOVINGOBJ:
		if(m_Setting.m_SubTask == 1)
		{
			if(m_HoldNo<m_TrialCount)
			{
				//���40ms����һ��
				do
				{
					QueryPerformanceCounter(&litmp);
					QPart2 = litmp.QuadPart;         //�����ֵֹ
					dfMinus = (double)(QPart2-QPart1);
					//dfTim = dfMinus / dfFreq;        // ��ö�Ӧ��ʱ��ֵ����λΪ��		
				}while(dfMinus<m_SampleInt);
				dfTim = dfMinus / dfFreq;  // ��ö�Ӧ��ʱ��ֵ����λΪ��
				QPart1 = QPart2;           // ��ó�ʼֵ
				dfTotal = dfTotal + dfTim;

			
				//����ʱ�䱣�ֿ�ʼָʾ��
				if(m_bShowSign)
				{
        			if(dfTotal>=0.2)
					{
						m_bShowSign = FALSE;
					}
				}
				//ʱ�䱣�ֿ�ʼ
				if(!m_bHoldStart)
				{
					if(!m_bShowTime)
					{
						if(dfTotal>=1)
						{   
							m_HoldTime[m_HoldNo] = m_Setting.m_HoldTime[m_HoldTimeOrder[m_HoldNo]%m_Setting.m_HoldTimeNum];
							sprintf(m_TimeStr,"%.1fs",m_HoldTime[m_HoldNo]);
							m_bShowTime = TRUE;
							dfTotal = 0;
						}
					}
					if(dfTotal>=2)//(float)m_Setting.m_Interval*0.001)
					{
						m_bHoldStart = TRUE;
						//m_HoldStartTime[m_HoldNo] = QPart2/dfFreq*1000;
						m_HoldStartTime[m_HoldNo] = 0;
						m_bShowSign = TRUE;
						dfTotal = 0;
					}
				}
				//���㵱ǰ�˶�״̬
				if(m_Setting.m_MainTask == 1)
				{
				    MoveTrace();
				}

				//���㳬ʱ
				if (dfTotal >= (2 * m_HoldTime[m_HoldNo] + 5))
				{
					m_HoldSureTime[m_HoldNo] = -1;
					sprintf(FeedBack, "��Ӧ��ʱ");
					if (m_TrialType == TRIAL_PRACTICE)
					{
						bShowFeedBack = TRUE;
						dfTotal = 0;
					}
					else
					{
						m_bHoldStart = FALSE;
						m_bShowTime = FALSE;
						m_bShowSign = FALSE;
						dfTotal = 0;
						m_HoldNo++;
					}

				}

				//��ʾ����
				if (bShowFeedBack)
				{
					if (dfTotal >= 2)
					{
						bShowFeedBack = FALSE;
						m_bHoldStart = FALSE;
						m_bShowTime = FALSE;
						dfTotal = 0;
						m_HoldNo++;
					}
					
					
				}
			}
			else
			{
				//��������
				SaveData();
				if((m_TrialType == TRIAL_PRACTICE)&&(m_Setting.m_ExperMode == 1))
				{
					//������ʽ����ѡ��
					m_TrialType = TRIAL_EXPERMENT;
					m_TestState = STATE_DISPLAYOPTION;
					CleanupMem();
				}
				else
				{
					//���Խ���
					QueryPerformanceCounter(&litmp);
					QPart1 = litmp.QuadPart;           // ��ó�ʼֵ
					TimeInt = 2;
					m_TestState = STATE_OVER;
				}
			}
		}
		else
		{
			//������׷������
			if(dfTotalMove<m_TrialTime)
			{
				//���40ms����һ��
				do
				{
					QueryPerformanceCounter(&litmp);
					QPart2 = litmp.QuadPart;         //�����ֵֹ
					dfMinus = (double)(QPart2-QPart1);
					dfTim = dfMinus / dfFreq;        // ��ö�Ӧ��ʱ��ֵ����λΪ��		
				}while(dfTim<m_MoveInt);
				QPart1 = QPart2;           // ��ó�ʼֵ
				dfTotalMove = dfTotalMove + dfTim;
				//���㵱ǰ�˶�״̬
				MoveTrace();
			}
			else
			{
				//��������
				SaveData();			
				if((m_TrialType == TRIAL_PRACTICE)&&(m_Setting.m_ExperMode == 1))
				{
					//������ʽ����ѡ��
    				m_TrialType = TRIAL_EXPERMENT;
				    m_TestState = STATE_DISPLAYOPTION;
					CleanupMem();
				}
				else
				{	
					//���Խ���
					QueryPerformanceCounter(&litmp);
					QPart1 = litmp.QuadPart;           // ��ó�ʼֵ
					TimeInt = 2;
					m_TestState = STATE_OVER;
				}
			}
		}
		break;
	//���ַ���
	case STATE_DISPLAYFEEDBACK:
		QueryPerformanceCounter(&litmp);
		QPart2 = litmp.QuadPart;         //�����ֵֹ
		dfMinus = (double)(QPart2-QPart1);
		dfTim = dfMinus / dfFreq;        // ��ö�Ӧ��ʱ��ֵ����λΪ��	
		//2000ms
		if (dfTim >= TimeInt)
		{
			m_bHoldStart = FALSE;
			m_bShowTime = FALSE;
			dfTotal = 0;
			m_HoldNo++;
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
DWORD WINAPI t2::InputThreadProcedure(LPVOID lpStartupParam)
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
					//���ֿ�ʼѡ��ȴ���ȷ������ʼ����
					if(m_SureDownNum == 0)
					{
//					if(JoystickUpdate())
//					if(m_SureDownNum == 0)
//					{
						for(i=0;i<8;i++)
						{
							if(IsButtonDown(KEY_YES))
							{
//								m_SureDownNum++;
								if(m_TrialType == TRIAL_EXPERMENT)
								{
									
								}
		//						m_HoldNo++;
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
						if(m_bHoldStart)
						{
							if(m_SureDownNum == 0)
							{
								//ʱ�䱣�ְ�YES��ȷ��
								if(IsButtonDown(KEY_YES) && !bShowFeedBack)
								{
	//								m_SureDownNum++;
									//m_HoldSureTime[m_HoldNo] = QPart2/dfFreq*1000;
									m_HoldSureTime[m_HoldNo] = dfTotal*1000;
									sprintf(FeedBack,"֪��ʱ��%dms",m_HoldSureTime[m_HoldNo] - m_HoldStartTime[m_HoldNo]);
									if(m_TrialType == TRIAL_PRACTICE)
									{
										//��ϰ״̬���ַ���
										QueryPerformanceCounter(&litmp);
										QPart1 = litmp.QuadPart;           // ��ó�ʼֵ
										TimeInt = 1;
										dfTotal = 0;
										bShowFeedBack = TRUE;
										dfTotal = 0;
										
									}
									else
									{
										
										//��ʽ����״̬�����ַ���
										m_bHoldStart = FALSE;
										m_bShowTime = FALSE;
										m_bShowSign = FALSE;
										dfTotal = 0;
										m_HoldNo++;
									}
								}
							}
						}
					}
					//���Թ����л�ò��ݸ�����
					if(m_Setting.m_MainTask == 1)
					{
						JoyX = GetXAxis();//GetYAxis();//
						JoyY = GetYAxis();//-GetZAxis();//
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
					for(i=0;i<12;i++)
					{
						if(IsButtonDown(i))
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
int APIENTRY t2::_tWinMain(HINSTANCE &hInstance,
	HINSTANCE &hPrevInstance,
	LPTSTR    &lpCmdLine,
	int       &nCmdShow, HWND &_hWnd,
	std::string winClassName, std::string winName)
{
	// ��ʼ�������״̬
	bool bUnClosedLastWin = true;
	t2::hWnd = _hWnd;
	g_nThreadExitCount = 0;
	gHinstance = hInstance;
	ShowCursor(FALSE);

	//��ô��ݵ������в������õ����������ֺ�������
	char *pdest;
    int result;
	int pos1;
	//gHinstance =  hInstance;
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
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, t2::MsgProc, 0L, 0L, 
                      hInstance, NULL, NULL, NULL, NULL,
					  std::to_string(nCmdShow).c_str(), NULL };
    RegisterClassEx( &wc );

	x_resolution=GetSystemMetrics(SM_CXSCREEN); 
	y_resolution=GetSystemMetrics(SM_CYSCREEN); 
	rec_x_begin = (x_resolution - 1024)/2;
	rec_y_begin = (y_resolution - 768)/2;
	rec_x_end = (x_resolution + 1024)/2;
	rec_y_end = (y_resolution + 768)/2;

	//SendMessage(_hWnd, WM_CLOSE, 0, 0); // �رմ���
	//SendMessage(hWnd, WM_DESTROY, 0, 0);
	

	//��������
	_hWnd = t2::hWnd = CreateWindow(std::to_string(nCmdShow).c_str(), std::to_string(nCmdShow).c_str(),
		WS_VISIBLE | WS_POPUP, 0, 0, x_resolution, y_resolution,
		NULL, NULL, wc.hInstance, NULL);
	
	
	//��ʾ������
	SetFocus(hWnd);
	//ShowCursor(FALSE);
	

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
		//msg.hwnd = hWnd;
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
				break;
			}
		}
    }
		ShowCursor(TRUE);
		
		CloseHandle(h);
		
		return rtn;
}

void t2::hideLastWindow(bool &bUnClosedLastWin, std::string &winClassName, std::string &winName, HINSTANCE &hInstance)
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
