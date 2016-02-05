// Task6_1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Task6_1.h"

int t6_1::rtn;
HINSTANCE t6_1::gHinstance;
float t6_1::acce = 0; //Ŀ��ļ��ٶ�
int t6_1::iDirection = 1;//Ŀ���˶�����
int t6_1::g_nThreadExitCount = 0;                      //��ǰ���е��߳���
DWORD t6_1::dwInputThreadID = 0;                       //��׼�������߳�ID
BOOL t6_1::m_bCubeNum[4];                              //��άͼ�η�������־
int t6_1::iJoyMoveDirection;//�ֱ��ƶ�����
BOOL t6_1::m_bAcc;                                     //��άͼ�μ�����ȷ�Ա�־
double t6_1::alpha, t6_1::omiga, t6_1::v, t6_1::a, t6_1::b, t6_1::r, t6_1::Rx, t6_1::Ry, t6_1::fai, t6_1::AngleSpeed, t6_1::inc_v;
double t6_1::m_PostPointX, t6_1::m_PostPointY;                //��ǰ��׼������
int t6_1::JoyX, t6_1::JoyY;                                   //��ǰ���ݸ�����ֵ  
struct TaskSetting6   t6_1::m_Setting;                 //����6���ò���
struct HardSetting   t6_1::m_HardSetting;              //Ӳ�����ò��� 
struct PartInfo  t6_1::m_PartInfo;                    //��������Ϣ
short t6_1::m_TrialType;                               //��������
int t6_1::m_TrialTime;                                 //����ʱ��
int t6_1::m_TrialTimes;                                //����ʱ��


int t6_1::x_resolution = 1024;			//��Ļ�ֱ���
int t6_1::y_resolution = 768;             //��Ļ�ֱ���
int t6_1::rec_x_begin;
int t6_1::rec_y_begin;
int t6_1::rec_x_end;
int t6_1::rec_y_end;
const float t6_1::FontScale = (float)(t6_1::x_resolution + t6_1::y_resolution) / 1400.0;            //��������Ļ�ֱ��ʵķ����߶�

const char t6_1::Insturction11[] = "    ��ӭ����˫������ά\
							 ͼ�μ����б�������ʹ�����ֿ��Ʋ��ݸ�׷����Ļ�ϵġ��͡���ͬʱ��ע��\
							 ��Ļ������ֵ�ͼ��������Ҫ��ס��Щͼ����X�����Ļ�������Щ�ַ���\
							 ��ʧ��Ȼ����Ļ���������γ���һϵ��ͼ����ÿ�γ���һ�������ж���Щͼ��\
							 �Ƿ�Ϊ���ס����Щͼ����";
const char t6_1::Insturction12[] = "    ��ӭ����˫��\
							 ������б���ԣ���ʹ�����ֿ��Ʋ��ݸ�׷����Ļ�ϵġ��͡���ͬʱ��ע����\
							 Ļ������ֵ�ͼ��������Ҫ��ס��Щͼ����X�����Ļ�������Щ�ַ�����\
							 ʧ��Ȼ����Ļ���������γ���һϵ��ͼ����ÿ�γ���һ�������ж���Щͼ����\
							 ��Ϊ���ס����Щͼ����";
const char t6_1::Insturction13[] = "���ס�����ͼ����\n�����ǡ�����ʼ���ԡ�";
const char t6_1::Insturction2[] = "��ϰ�������������������ʽʵ�顣";
const char t6_1::Insturction3[] = "��������ɣ��������������";
const char t6_1::FeedBack[2][10] = { "����", "��ȷ" };
char t6_1::m_CharStr[12];

LPDIRECT3D9             t6_1::g_pD3D       = NULL;                   //directx3d����
LPDIRECT3DDEVICE9       t6_1::g_pd3dDevice = NULL;                   //directx�豸����
LPDIRECT3DTEXTURE9      t6_1::g_pTextureInst  = NULL;                //�������
LPDIRECT3DTEXTURE9      t6_1::g_pTexture0  = NULL;                   //�������
LPDIRECT3DTEXTURE9      t6_1::g_pTexture1  = NULL;                   //�������
LPDIRECT3DTEXTURE9      t6_1::g_pTexture2  = NULL;                   //�������
LPDIRECT3DTEXTURE9      t6_1::g_pTexture3  = NULL;                   //�������
LPDIRECT3DTEXTURE9      t6_1::g_pTexture4  = NULL;                   //�������
LPD3DXSPRITE            t6_1::g_pSprite  = NULL;                     //�������
LPD3DXFONT              t6_1::g_pFont      = 0;                      //�������
LPD3DXFONT              t6_1::g_pFont1     = 0;                      //�������
LPD3DXFONT              t6_1::g_pFont2     = 0;                      //�������
LPDIRECT3DVERTEXBUFFER9      t6_1::m_pVertexBuffer = NULL;

D3DXMATRIX t6_1::m_Transform;                             //����任����
float t6_1::TimeInt;
short t6_1::m_SignNo;                                     //��άͼ�μ������
short t6_1::m_SignOrderNo1, t6_1::m_SignOrderNo2;               //��άͼ�μ���ϵ�����
short t6_1::m_SignTrialNo;                                //��άͼ�μ��������
short t6_1::m_SignGroupNo;                                //��άͼ�μ������
short t6_1::m_SignCount;                                  //��άͼ�μ�����Ŀ
BOOL t6_1::m_bLoadSign;                                   //��άͼ���ļ����ر�־
BOOL t6_1::m_bDisplayReady;                               //��Ⱦ�豸������־

BOOL t6_1::m_bHideSign = FALSE;									//�ڵȴ�ʱ��������άͼ��
BOOL t6_1::m_bRememStart;                                 //��άͼ�μ��俪ʼ��־                       
BOOL t6_1::m_bSignStart;                                  //��άͼ����ʾ��־
short t6_1::m_SureDownNum;
int t6_1::m_SignType[12];                                 //��άͼ������
int t6_1::m_SignOrderLeft[12];                            //�����άͼ������
int t6_1::m_SignOrder1[6];                                //��άͼ������
int t6_1::m_SignOrder2[6];                                //��άͼ������
unsigned long *t6_1::m_SignStartTime = NULL;                //��άͼ�μ��俪ʼʱ��
unsigned long *t6_1::m_SignSureTime = NULL;                 //��άͼ�μ���ȷ��ʱ��
char(*t6_1::m_LMemName)[30];                             //��������άͼ�����Ƶ�����
char(*t6_1::m_RMemName)[30];                             //����ұ���άͼ�����Ƶ�����
short *t6_1::m_NoSame = NULL;                               //���������άͼ����ͬ�Ե�����
short *t6_1::m_LMemAngle = NULL;                            //��������άͼ����ת�Ƕȵ�����
short *t6_1::m_RMemAngle = NULL;                            //����ұ���άͼ����ת�Ƕȵ�����
short *t6_1::m_MemAngleDiff = NULL;                         //���������άͼ����ת�ǶȲ������
short *t6_1::m_SureButtonNo = NULL;
BOOL *t6_1::m_bHit = NULL;                                //��Ż���״̬������
int t6_1::m_CubeNum;


const double t6_1::m_MoveInt = 0.04;                      //�������40ms

UINT t6_1::m_PointNum;
UINT t6_1::m_MemNum;
SPOINT *t6_1::m_ObjPoint = NULL;                          //���Ŀ�����������
SPOINT *t6_1::m_PostPoint = NULL;                         //�����׼�����������
float *t6_1::m_Distance = NULL;                           //���Ŀ�����׼�����������
unsigned long *t6_1::m_PointTime = NULL;                  //��Ų���ʱ�������
float *t6_1::m_ObjSpeedX = NULL;                          //���Ŀ���ٶȵ�����
float *t6_1::m_ObjSpeedY = NULL;                          //���Ŀ���ٶȵ�����
float *t6_1::m_PostSpeedX = NULL;                         //�����׼���ٶȵ�����
float *t6_1::m_PostSpeedY = NULL;                         //�����׼���ٶȵ�����
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
//*����Ŀ�����׼����ǰ���˶�״̬
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

	//��ǰ��ʱ��
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


	//��ǰ׷�ٻ�λ��
	double JoyAlpha = 0;
	JoyAlpha = atan(fabs((double)(JoyY - m_PostPointY) / (double)(JoyX - m_PostPointX)));//ҡ�˽Ƕ�
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

	//��ǰĿ��Ƕ�
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



	//��ǰĿ��λ��
	m_ObjPoint[m_PointNum].x = a + r * cos(alpha);
	m_ObjPoint[m_PointNum].y = b - r * sin(alpha);   

	m_Distance[m_PointNum] = pow(pow((m_ObjPoint[m_PointNum].y-m_PostPoint[m_PointNum].y),2.0)+pow((m_ObjPoint[m_PointNum].x-m_PostPoint[m_PointNum].x),2.0),0.5);
	//׷�ٻ���Ŀ��ӽ��̶�
	if(m_Distance[m_PointNum]<m_HardSetting.m_DistanceError)
	{
		m_bHit[m_PointNum] = TRUE;
	}
	else
	{
		m_bHit[m_PointNum] = FALSE;
	}
	//���㵱ǰĿ���ٶ�
	m_ObjSpeedX[m_PointNum] = -v * sin(alpha);
	m_ObjSpeedY[m_PointNum] = -v * cos(alpha);


}

//************************************************
//*��ȡ��ǰ��������
//************************************************
BOOL t6_1::ReadSetting()
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
//*����������ݼ�¼�ļ�
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
//*����׷�ٽ�����ݼ�¼�ļ�
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
//*������������ݼ�¼�ļ�
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
//*������άͼ���ļ�
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
		sprintf(m_SignName1,"Pics\\Task6\\��άͼ��\\%s.jpg",m_LMemName[m_SignNo]);
		sprintf(m_RMemName[m_SignNo],"M%d_%d_%s%04d",m_CubeNum, m_Setting.m_Prototype+1, axis[m_Setting.m_RefAxis],(m_SignOrderLeft[m_SignNo]+m_SignOrder1[m_SignOrderNo1])%12*5);
		sprintf(m_SignName2,"Pics\\Task6\\��άͼ��\\%s.jpg",m_RMemName[m_SignNo]);
		m_NoSame[m_SignNo] = 0;
		m_LMemAngle[m_SignNo] = m_SignOrderLeft[m_SignNo]*30;
		m_RMemAngle[m_SignNo] = (m_SignOrderLeft[m_SignNo]+m_SignOrder1[m_SignOrderNo1])%12*30;
		m_MemAngleDiff[m_SignNo] = m_SignOrder1[m_SignOrderNo1]*30;
		m_SignOrderNo1++;
	}
	else
	{
		sprintf(m_LMemName[m_SignNo],"M%d_%d_%s%04d",m_CubeNum, m_Setting.m_Prototype+1, axis[m_Setting.m_RefAxis],m_SignOrderLeft[m_SignNo]*5);
		sprintf(m_SignName1,"Pics\\Task6\\��άͼ��\\%s.jpg",m_LMemName[m_SignNo]);
		sprintf(m_RMemName[m_SignNo],"M%d_%d_mir_%s%04d",m_CubeNum, m_Setting.m_Prototype+1, axis[m_Setting.m_RefAxis],(m_SignOrderLeft[m_SignNo]+m_SignOrder2[m_SignOrderNo2])%12*5);
		sprintf(m_SignName2,"Pics\\Task6\\��άͼ��\\%s.jpg",m_RMemName[m_SignNo]);
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
//*��ʼ��DirectX 3D
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
	//���ʴ�С
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

	//��������
	if( FAILED( D3DXCreateSprite( g_pd3dDevice, &g_pSprite )))
	{
		MessageBox(NULL, "Could not find banana.bmp", "Textures.exe", MB_OK);
		return E_FAIL;
	}

	//��������ͼƬ
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
		0,0,GB2312_CHARSET,0,0,0, "����", &g_pFont)))
	{
		return E_FAIL;
	}
	if (FAILED(D3DXCreateFont(g_pd3dDevice,40*FontScale,20*FontScale,20,
		0,0,GB2312_CHARSET,0,0,0, "����", &g_pFont1)))
	{
		return E_FAIL;
	}
	if (FAILED(D3DXCreateFont(g_pd3dDevice,20*FontScale,10*FontScale,20,
		0,0,GB2312_CHARSET,0,0,0, "����", &g_pFont2)))
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
//*�ͷ������ڴ�
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
//*�ͷ�DirectX����
//************************************************
VOID t6_1::Cleanup()
{
	delete []m_LMemName;
	m_LMemName = NULL;
	delete []m_RMemName;
	m_RMemName = NULL;
	//�ͷ��������
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
//*��Ⱦ
//************************************************
VOID t6_1::Render()
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
					//������άͼ��
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
			}
			g_pSprite->End();
			
			break; 
			//���ַ���
		//case STATE_DISPLAYFEEDBACK:
			//g_pFont1->DrawText(NULL, FeedBack[m_bAcc], -1, &erect,
			//	DT_WORDBREAK|DT_NOCLIP|DT_CENTER|DT_VCENTER, D3DCOLOR_XRGB(255,0,0));
			//break;
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

//��ͣ�Ի�����Ϣѭ��
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
//*�ⲿ��Ϣ����
//************************************************
LRESULT WINAPI t6_1::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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
				{
					SaveTraceData();
					SaveJudgeData();
				}
				EndDialog(hWnd, rtn);
				PostThreadMessage(dwInputThreadID, WM_THREADSTOP, 0, 0); 	//�˳��߳�
				m_TestState = STATE_NEXT;
				break;
			case ID_CANCEL:
				//����������;�˳� �򱣴浱ǰ����ʵ������
				if (m_TestState == STATE_MOVINGOBJ)
				{
					SaveTraceData();
					SaveJudgeData();
				}
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
VOID t6_1::UpdateState()
{
	switch(m_TestState)
	{
		//����ָ����
	case STATE_DISPLAYINSTURCTION:       
		break;
		//����Ŀ��
	case STATE_DISPLAYOBJ:	
		if(abs(JoyX)>30||abs(JoyY)>30)
			//		if(m_bRememStart)
		{
			if(QueryPerformanceFrequency(&litmp))
			{
				dfFreq = (double)litmp.QuadPart;// ��ü�������ʱ��Ƶ��
			}
			QueryPerformanceCounter(&litmp);
			QPart1 = litmp.QuadPart;           // ��ó�ʼֵ
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
		//��������ִ��
	case STATE_MOVINGOBJ:
	case STATE_DISPLAYFEEDBACK:
		if(m_Setting.m_SubTask == 1)
		{
			if(m_SignTrialNo<1)
			{	
				//if(m_SignNo<m_SignCount)//m_TrialTimes)//m_Setting.m_ExperTimes)
				if(m_SignNo<m_TrialTimes)//m_TrialTimes)//m_Setting.m_ExperTimes)
				{
					//����ͼ���ļ�
					if(!m_bLoadSign)
					{
						if(LoadSignFile())
						{
							m_bLoadSign = TRUE;
						}
					}
					//����ʱ��40ms
					do
					{
						QueryPerformanceCounter(&litmp);
						QPart2 = litmp.QuadPart;         //�����ֵֹ
						dfMinus = (double)(QPart2-QPart1);
						dfTim = dfMinus / dfFreq;        // ��ö�Ӧ��ʱ��ֵ����λΪ��		
					}while(dfTim<m_MoveInt);
					QPart1 = QPart2;           // ��ó�ʼֵ
					dfTotalSign = dfTotalSign + dfTim;
					dfTotalMove = dfTotalMove + dfTim;
					//��ʾ�Ƚϼ���ͼ��
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
							//������
							if(dfTotalSign>= m_Setting.m_iSubTaskInterval)
							{	
								m_bSignStart = TRUE;
								m_SignStartTime[m_SignNo] = QPart2/dfFreq*1000;
								dfTotalSign = 0;
							}
						}
						else
						{
							//��ʱѡ�����ʱ��
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
								//ȡ���ȴ�ʱ��
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
					//���㵱ǰ�˶�״̬
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
						//��������
						SaveJudgeData();
						m_SignNo = 0;
						m_SignOrderNo1 = 0;
						m_SignOrderNo2 = 0;
						RandOrder(m_SignCount,m_SignType);
						RandOrder1(12,m_SignCount/2,m_SignOrderLeft);
						RandOrder1(6,m_SignCount/2,m_SignOrder1);
						RandOrder1(6,m_SignCount/2,m_SignOrder2);
						m_bLoadSign = FALSE;
						//����ͼ���ļ�
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
				//���ȫ��������Ŀ�ѽ�����
				if(m_SignGroupNo>=3)
				{
					//��������
					if(m_Setting.m_MainTask == 1)
					{
						SaveTraceData();
					}
					SaveJudgeData();
					if((m_TrialType == TRIAL_PRACTICE)&&(m_Setting.m_ExperMode == 1))
					{
						//������ʽ����ѡ��
						m_SignTrialNo = 0;
						m_CubeNum = 9;
						m_SignGroupNo = -1;
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
				//���ȫ��������Ŀû�н�����
				else
				{
					//��������
					SaveJudgeData();
					//������һ��������Ŀ
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
					//���û��Ҫ���еķ�����
					if(m_SignGroupNo>3)
					{
						//��������
						if(m_Setting.m_MainTask == 1)
						{
							SaveTraceData();
						}
						if((m_TrialType == TRIAL_PRACTICE)&&(m_Setting.m_ExperMode == 1))
						{
							//������ʽ����ѡ��
							m_CubeNum = 9;
							m_SignGroupNo = -1;
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
					else
					{
						//����ͼ���ļ�
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
			


			//������׷������
			if(dfTotalMove<m_TrialTime)
			{
				do
				{
					QueryPerformanceCounter(&litmp);
					QPart2 = litmp.QuadPart;         //�����ֵֹ
					dfMinus = (double)(QPart2-QPart1);
					dfTim = dfMinus / dfFreq;        // ��ö�Ӧ��ʱ��ֵ����λΪ��		
				}while(dfTim<m_MoveInt);
				QPart1 = QPart2;           // ��ó�ʼֵ
				dfTotalMove = dfTotalMove + dfTim;
				MoveTrace();
			}
			else
			{
				//��������
				SaveTraceData();			
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

		if (m_TestState == STATE_DISPLAYFEEDBACK)
		{
			QueryPerformanceCounter(&litmp);
			QPart4 = litmp.QuadPart;         //�����ֵֹ
			dfMinus = (double)(QPart4-QPart3);
			dfTim = dfMinus / dfFreq;        // ��ö�Ӧ��ʱ��ֵ����λΪ��	
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
		//���ַ���
	/*case STATE_DISPLAYFEEDBACK:
		QueryPerformanceCounter(&litmp);
		QPart4 = litmp.QuadPart;         //�����ֵֹ
		dfMinus = (double)(QPart4-QPart3);
		dfTim = dfMinus / dfFreq;        // ��ö�Ӧ��ʱ��ֵ����λΪ��	
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
					//���ֿ�ʼѡ��ȴ����������ʼ����
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
							//�бȽϼ���ͼ��ʱ����ȷ��
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
											QPart3 = litmp.QuadPart;           // ��ó�ʼֵ
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
					//���Թ����л�ò��ݸ�����
					if(m_Setting.m_MainTask == 1)
					{
						JoyX = GetXAxis();//GetYAxis();//
						JoyY = GetYAxis();//-GetZAxis();//
					}
					break;
				case STATE_DISPLAYNEXT:
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
int APIENTRY t6_1::_tWinMain(HINSTANCE &hInstance, HINSTANCE &hPrevInstance, LPTSTR &lpCmdLine, int &nCmdShow, HWND &_hWnd, std::string winClassName, std::string winName)
{
	// ��ʼ�������״̬
	bool bUnClosedLastWin = true;
	hWnd = _hWnd;
	gHinstance = hInstance;
	g_nThreadExitCount = 0;
	ShowCursor(FALSE);


	//��ô��ݵ������в������õ����������ֺ�������
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

	//��ȡ��������
	if(!ReadSetting())
	{
		MessageBox(hWnd,"���������ļ���ʽ����","��������", MB_OK);
		return 0;
	}
	
	m_bLoadSign = FALSE;
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
	//	ShowWindow( hWnd, SW_HIDE );
	//	UpdateWindow( hWnd );

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

void t6_1::hideLastWindow(bool &bUnClosedLastWin, std::string &winClassName, std::string &winName, HINSTANCE &hInstance)
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