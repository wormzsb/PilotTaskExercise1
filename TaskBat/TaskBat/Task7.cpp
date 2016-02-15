// Task1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Task7.h"
#include "TaskRec.h"

/*��¼����*/
TaskRec rec;
Helper t7::hp;

FILE *t7::sfp;

HINSTANCE t7::gHinstance;//ȫ�־��

int t7::g_nThreadExitCount = 0;             //��ǰ���е��߳���
DWORD t7::dwInputThreadID = 0;              //��׼�������߳�ID      


int t7::rtn;
int t7::preKeyPress = -1; //��¼��һ���ֱ�����
BOOL t7::bTimeOut = FALSE;
int t7::iShowState = t7::BALL_INTERVAL;;
char t7::szFeedBack[100];
int t7::iBallStartPos; 	
int t7::curStartPos;
const char t7::szSpeedMode[][100]={"����","�ȼ���"};
BOOL t7::bBtnDown = TRUE;
//��ǰС������
struct Point t7::stPntSmallBall;
//С���ʼ����
struct Point t7::stPntSmallBallOrg;
double t7::dOrgDistance = 350;// С�����Ļ���ģ������ڵ������ĵľ��룩

BOOL t7::bShowSmallBall = TRUE;
int t7::iReactTime = 0;

double t7::dBallSpeed = 0;//С���ٶ�
BOOL t7::bBtnStatus = BTN_UP;//����״̬

int t7::JoyX,t7::JoyY,t7::JoyZ;                     //��ǰ���ݸ�����ֵ     

struct TaskSetting7  t7::m_Setting;        //����1���ò���
struct HardSetting   t7::m_HardSetting;     //Ӳ�����ò���
struct PartInfo   t7::m_PartInfo;           //��������Ϣ
  
short t7::m_TrialType;						//��������
int t7::m_TrialTime;						//����ʱ��
int t7::m_TrialTimes = 1;						//���Դ���
int t7::iTskCnt = 0;						//ʵ���л�����ϰ�Ĵ���ͳ��
int t7::iTotalTskCnt = 0;					//ʵ�����Դ�

int t7::m_TrialGroups = 0;
int t7::x_resolution=1024;			//��Ļ�ֱ���
int t7::y_resolution=768;             //��Ļ�ֱ���
int t7::x_resolution1024 = 1024;
int t7::y_resolution768 = 768;
int t7::rec_x_begin = (t7::x_resolution - t7::x_resolution1024)/2;
int t7::rec_y_begin = (t7::y_resolution - t7::y_resolution768)/2;
int t7::rec_x_end = (t7::x_resolution + t7::x_resolution1024)/2;
int t7::rec_y_end = (t7::y_resolution + t7::y_resolution768)/2;

const float t7::FontScale = (float)(t7::x_resolution+t7::y_resolution)/1400.0;    //��������Ļ�ֱ��ʵķ����߶�

const char t7::Insturction1[] = "    ��Ļ�ϵİ�ɫ���͡���Ŀ�꣬��ɫ\
���͡���׷�ٻ������������ǣ�ʹ�ò��ݸ�������׷�ٻ����˶�����������׷\
�ٻ���סĿ�ꡣ׷�ٻ���סĿ��ʱ��׷�ٻ����ɺ�ɫ����X����ʼ���񡣡�˫\
��׷��׷�������ָ����Ϊ����Ļ�ϵİ�ɫ���͡���Ŀ�꣬��ɫ���͡���׷\
�ٻ������������ǣ�ʹ�ò��ݸ�������׷�ٻ����˶�����������׷�ٻ���סĿ\
�ꡣͬʱ��ʹ����ť����׷�ٻ�����̬�������ܱ���׷�ٻ�����̬��Ŀ��һ�¡�\
׷�ٻ���סĿ��ʱ��׷�ٻ����ɺ�ɫ����X����ʼ����";
const char t7::Insturction2[] = "��������ɣ��������������";
const char t7::Insturction3[] = "��ϰ�������������������ʽʵ�顣";
const char t7::Insturction4[] = "��������ɣ��������������";
LPDIRECT3D9             t7::g_pD3D       = NULL;		    //directx3d����
LPDIRECT3DDEVICE9       t7::g_pd3dDevice = NULL;		    //directx�豸����
LPDIRECT3DTEXTURE9      t7::g_pTextureInst  = NULL;	        //�������
LPDIRECT3DTEXTURE9      t7::g_pTextureSmallBall  = NULL;	//С���������
LPDIRECT3DTEXTURE9      t7::g_pTextureBall  = NULL;	    	//�����������

LPDIRECT3DTEXTURE9      t7::g_pTextureCircle = NULL;
LPD3DXSPRITE            t7::g_pSprite  = NULL;              //�������
LPD3DXFONT              t7::g_pFont      = 0;               //�������
LPD3DXFONT              t7::g_pFont1     = 0;				//�������
LPDIRECT3DVERTEXBUFFER9      t7::m_pVertexBuffer  = NULL;	//�������

D3DXMATRIX t7::m_Transform;                                 //����任����
float t7::TimeInt;                                          //ʱ����
short t7::m_TrialNo;                                        //���Դ������
BOOL t7::m_bDisplayReady;                                   //��Ⱦ�豸������־
                         
 

//const double dfTim = 0.05;                          //�������50ms
double t7::m_SampleInt;

UINT t7::m_PointNum;
UINT t7::m_MemNum;

RECT t7::strurect,t7::lerect,t7::rerect,t7::erect,t7::txtrect;

short t7::m_TestState;
char t7::m_file[220];
char t7::m_file1[220];
HWND t7::hWnd;
char t7::m_TesterName[40];
char t7::m_DataName[60];
char t7::m_TaskNumStr[100];

//Timer
LARGE_INTEGER t7::litmp; 
LONGLONG t7::QPart1,t7::QPart2,t7::QPart3;
double t7::dfMinus, t7::dfMinus1, t7::dfFreq, t7::dfTim, 
	t7::dfdetTim, t7::dfInterval, t7::dfTotalMove/*С���˶�ʱ���¼*/; 
BOOL t7::bXdown,t7::bZdown;



//************************************************
//*��ȡ��ǰ��������
//************************************************
BOOL t7::ReadSetting()
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
	
			//fscanf(fp,"TaskName\t%s\n",m_Setting.m_TaskName);
			fscanf(fp,"PracMode\t%d\n",&m_Setting.m_PracMode);
			fscanf(fp,"ExperMode\t%d\n",&m_Setting.m_ExperMode);
			fscanf(fp,"SpeedMode\t%d\n",&m_Setting.m_iSpeedMode);
			fscanf(fp,"BallColorR\t%d\n",&m_Setting.m_iBallColorR);
			fscanf(fp,"BallColorG\t%d\n",&m_Setting.m_iBallColorG);
			fscanf(fp,"BallColorB\t%d\n",&m_Setting.m_iBallColorB);
			fscanf(fp,"BallStartPos\t%d\n",&m_Setting.m_iBallStartPos);
			fscanf(fp, "BallStartPos\t%d\n", &m_Setting.m_iBallStartPos);
			fscanf(fp, "PosTop\t%d\n", &m_Setting.m_iTop);
			fscanf(fp, "PosBottom\t%d\n", &m_Setting.m_iBottom);
			fscanf(fp, "PosLeft\t%d\n", &m_Setting.m_iLeft);
			fscanf(fp, "PosRight\t%d\n", &m_Setting.m_iRight);
			fscanf(fp, "BallCenterDis\t%d\n", &m_Setting.m_iBallCenterDis);
			//�޸����
			dOrgDistance = (double)m_Setting.m_iBallCenterDis;
			fscanf(fp,"BallSpeed1\t%d\n",&m_Setting.m_iBallSpeed1);
			fscanf(fp, "BallSpeed2\t%d\n", &m_Setting.m_iBallSpeed2);
			fscanf(fp, "BallSpeed3\t%d\n", &m_Setting.m_iBallSpeed3);
			fscanf(fp,"BallSpeedAcc\t%d\n",&m_Setting.m_iBallSpeedAcc);
			fscanf(fp,"BallSpeedMax\t%d\n",&m_Setting.m_iBallSpeedMax);

			fscanf(fp,"BallRadius\t%d\n",&m_Setting.m_iBallRadius);
			fscanf(fp,"BckGrndColorR\t%d\n",&m_Setting.m_iBckGrndColorR);
			fscanf(fp,"BckGrndColorG\t%d\n",&m_Setting.m_iBckGrndColorG);
			fscanf(fp,"BckGrndColorB\t%d\n",&m_Setting.m_iBckGrndColorB);
			fscanf(fp,"ObstacleColorR\t%d\n",&m_Setting.m_iObstacleColorR);
			fscanf(fp,"ObstacleColorG\t%d\n",&m_Setting.m_iObstacleColorG);
			fscanf(fp,"ObstacleColorB\t%d\n",&m_Setting.m_iObstacleColorB);
			fscanf(fp,"ObstacleRadius\t%d\n",&m_Setting.m_iObstacleRadius);
			fscanf(fp,"PracTimes\t%d\n",&m_Setting.m_iPracTimes);
			fscanf(fp,"ExpTimes\t%d\n",&m_Setting.m_iExpTimes);
			fscanf(fp,"IntervalTime\t%d\n",&m_Setting.m_iIntervalTime);

			//fscanf(fp,"\n");
		
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
VOID t7::SaveName()
{
	FILE *fp;
	char m_DataDir[60];
	char m_filename[160];
	SYSTEMTIME CurTime;
	GetLocalTime(&CurTime);
    if(strlen(m_DataName)==0)
	{
		sprintf(m_filename, "T7-%d%02d%02d%02d%02d%02d.txt", CurTime.wYear, CurTime.wMonth, CurTime.wDay, CurTime.wHour, CurTime.wMinute, CurTime.wSecond);
    }
	else
	{
		sprintf(m_filename, "T7-%s-%s-%d%02d%02d%02d%02d%02d.txt", m_TaskNumStr, m_DataName, CurTime.wYear, CurTime.wMonth, CurTime.wDay, CurTime.wHour, CurTime.wMinute, CurTime.wSecond);
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
	sprintf(m_file, "%s\\%s", m_DataDir, m_filename);

	//д���ļ� old code
	fp = fopen(m_file,"at");

	
	//fprintf(fp,"�ٶ�֪������\n");
	//fprintf(fp,"С����ɫR:%d G:%d B:%d\t",m_Setting.m_iBallColorR,m_Setting.m_iBallColorG,m_Setting.m_iBallColorB);
	//fprintf(fp,"�뾶:%d����\t%s%d\t",m_Setting.m_iBallRadius,szSpeedMode[BALL_SPEED_CONSTANT],m_Setting.m_iBallSpeed1);

	//if (BALL_SPEED_ACC == m_Setting.m_iSpeedMode)
	//	fprintf(fp,"���ٶ�:%f\t�ٶ�����:%f\t",m_Setting.m_iBallSpeedAcc,m_Setting.m_iBallSpeedMax);

	//fprintf(fp,"�ڵ�����ɫR:%d G:%d B:%d\t\n",m_Setting.m_iObstacleColorR,m_Setting.m_iObstacleColorG,m_Setting.m_iObstacleColorB);

	//fprintf(fp,"�������\t��������\tƫ����\tС���ٶ�\n");
	stringstream ss;
	ss
		<< "�������" << "\t"
		<< "�ٶ�" << "\t"
		<< "�˶�����" << "\t"
		<< "�˶���ʼʱ��" << "\t"
		<< "��ʧʱ��" << "\t"
		<< "����ʱ��" << "\t"
		<< "�ɼ��˶�ʱ��" << "\t"
		<< "�����ڵ�������ʱ��" << "\t"
		<< "ʵ��ʱ��(����)" << "\t"
		<< "����ʱ��(����)" << "\t"
		<< "ƫ����(%)" << "\t"
		<< "��ʼ����" << "\t"
		<< "Ŀ������" << "\t"
		<< "��������" << "\n";
	fprintf(fp,"%s",ss.str().c_str());
	fclose(fp);
	

	

}

//************************************************
//*���������ݼ�¼�ļ�
//************************************************
VOID t7::SaveData()
{
	FILE* fp = fopen(m_file,"at");
	double dNowDistance = sqrt(pow(stPntSmallBall.dX - stPntSmallBallOrg.dX, 2)
		+ pow(stPntSmallBall.dY - stPntSmallBallOrg.dY, 2));/*С���ƶ�����*/
	stringstream ss;

	// �������
	fprintf(fp,"%d\t", rec.no);

	// С���ٶ�
	fprintf(fp, "%d\t", (int)rec.smallBallSpeed);

	// ��ǰС����
	fprintf(fp, "%s\t", rec.smallBalldir.c_str());

	// С��ʼ�˶���ʱ��
	fprintf(fp, "%I64d\t", rec.moveBegTime);

	// С����ʧ��ʱ��
	fprintf(fp, "%I64d\t", rec.disappearTime);
	
	// ������ʱ��
	fprintf(fp, "%I64d\t", rec.pressTime);

	// �ɼ��˶�ʱ��
	fprintf(fp, "%.4lf\t", rec.getVisiblePeriod());
	
	// �����ڵ�������ʱ��
	double tmp = rec.getObstacle2PressPeriod();
	fprintf(fp, "%.4lf\t", tmp);

	// ʵ��ʱ��
	fprintf(fp, "%.2lf\t", rec.getTotalPeriod());

	// ����ʱ��
	fprintf(fp, "%.2lf\t",  rec.evaluateTime);

	// ƫ����
	if (!bTimeOut) {
		double ratio;
		ratio = (dNowDistance - dOrgDistance)
			/ (double)m_Setting.m_iObstacleRadius * 100.;
		if (ratio > 1e-6)
			fprintf(fp, "+" );
		fprintf(fp, "%.2lf\t", ratio);
	}
	else 
		fprintf(fp, "%d\t", -1);

	// ��ʼ����
	ss.str("");
	ss << "{X=" << (int)rec.smallBallBegCo.x
		<< ",Y=" << (int)rec.smallBallBegCo.y << "}";
	fprintf(fp, "%s\t", ss.str().c_str());

	// Ŀ������
	ss.str("");
	ss << "{X=" << (int)rec.targetCo.x
		<< ",Y=" << (int)rec.targetCo.y << "}";
	fprintf(fp, "%s\t", ss.str().c_str());

	// ��������
	ss.str("");
	ss << "{X=" << (int)rec.pressSmallBallCo.x
		<< ",Y=" << (int)rec.pressSmallBallCo.y << "}";
	fprintf(fp, "%s\n", ss.str().c_str());

	fclose(fp);
}

//************************************************
//*��ʼ��DirectX 3D
//************************************************
HRESULT t7::InitD3D( HWND hWnd )
{
	m_TestState = STATE_DISPLAYINSTURCTION;
	m_TrialNo = -1;

	if(m_Setting.m_PracMode == 1)
	{
		m_TrialType = TRIAL_PRACTICE;
		m_TrialTimes = m_Setting.m_iPracTimes;
		
	}
	else
	{
		m_TrialType = TRIAL_EXPERMENT;
		m_TrialTimes = m_Setting.m_iExpTimes;
	}
	//���ʴ�С
    SetRect( &strurect, x_resolution/2-300*FontScale, y_resolution/2-180*FontScale, x_resolution/2+300*FontScale, y_resolution/2+20*FontScale );
    SetRect( &erect, x_resolution/2-500*FontScale, y_resolution/2-100*FontScale, x_resolution/2+500*FontScale+50, y_resolution/2+100*FontScale );
	SetRect(&txtrect, x_resolution/2-100*FontScale-50, y_resolution/2-30*FontScale-200, x_resolution/2+100*FontScale+50, y_resolution/2+30*FontScale-200 );
    SetRect( &lerect, x_resolution/2-250*FontScale, y_resolution/2-50*FontScale, x_resolution/2-50*FontScale, y_resolution/2+100*FontScale );
	SetRect( &rerect, x_resolution/2+50*FontScale, y_resolution/2-50*FontScale, x_resolution/2+250*FontScale, y_resolution/2+100*FontScale );

	if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
	{
        return E_FAIL;
	}

    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof(d3dpp) );
    d3dpp.Windowed = TRUE;//FALSE;//
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;//D3DSWAPEFFECT_FLIP;//D3DSWAPEFFECT_COPY;//

	D3DDISPLAYMODE d3ddm;
    if( FAILED( g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)) )
	{
		return E_FAIL;
	}

	d3dpp.BackBufferWidth = x_resolution;//d3ddm.Width;//
    d3dpp.BackBufferHeight = y_resolution;//d3ddm.Height;//
	d3dpp.BackBufferFormat = d3ddm.Format;
//	d3dpp.BackBufferCount =1;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

    if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &g_pd3dDevice ) ) )
    {
        return E_FAIL;
    }

    g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

    g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );


	//��������D3DXCreateSprite��������������һ���ض�D3D�豸������ľ������Sprite�������ڻ��ƶ�άͼ����Ļ��
    if( FAILED( D3DXCreateSprite( g_pd3dDevice, &g_pSprite )))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}

	
	if( FAILED( D3DXCreateTextureFromFile( g_pd3dDevice, TEXT("Pics\\Inst\\Speed_Sensor.jpg"), &g_pTextureInst ) ) )
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}
	
	if( FAILED( D3DXCreateTextureFromFile( g_pd3dDevice, TEXT("Pics\\Task8\\Ball.png"), &g_pTextureSmallBall) ) )
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}
	
	if( FAILED( D3DXCreateTextureFromFile( g_pd3dDevice, TEXT("Pics\\Task8\\Ball.png"), &g_pTextureBall) ) )
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}
	if( FAILED( D3DXCreateTextureFromFile( g_pd3dDevice, TEXT("Pics\\Task8\\CircleCenter.png"), &g_pTextureCircle) ) )
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}

	
	if (FAILED(D3DXCreateFont(g_pd3dDevice,30*FontScale,15*FontScale,20,
		0,0,GB2312_CHARSET,0,0,0, TEXT("����"), &g_pFont)))
	{
		return E_FAIL;
	}
	if (FAILED(D3DXCreateFont(g_pd3dDevice,40*FontScale,20*FontScale,20,
		0,0,GB2312_CHARSET,0,0,0, TEXT("����"), &g_pFont1)))
	{
		return E_FAIL;
	}
 
	m_bDisplayReady = TRUE;
	SaveName();
	TestInit();
    return S_OK;
}

//************************************************
//*�ͷ������ڴ�
//************************************************
VOID t7::CleanupMem()
{
	
}

//************************************************
//*�ͷ�DirectX����
//************************************************
VOID t7::Cleanup()
{
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

	if( g_pTextureInst!=NULL)
	{
		g_pTextureInst->Release();
		g_pTextureInst = NULL;
	}
	if( g_pTextureSmallBall!=NULL)
	{
		g_pTextureSmallBall->Release();
		g_pTextureSmallBall = NULL;
	}
	if( g_pTextureBall!=NULL)
	{
		g_pTextureBall->Release();
		g_pTextureBall = NULL;
	}
	
	if( g_pSprite!=NULL)
	{
		g_pSprite->Release();
		g_pSprite = NULL;
	}

	if( m_pVertexBuffer!=NULL)
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
	if (m_lpkDIDevice != NULL)
	{
        m_lpkDIDevice->Unacquire ();
        m_lpkDIDevice->Release ();
        m_lpkDIDevice = NULL;
	}

	if (m_lpkDInput != NULL)
	{
	    m_lpkDInput->Release ();
	    m_lpkDInput = NULL;
	}
}

//************************************************
//*��Ⱦ
//************************************************
VOID t7::Render()
{
	switch(m_TestState)
	{
    //����ָ����
	case STATE_DISPLAYINSTURCTION:
//		g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255,255,255), 0.0f, 0 );
//		break;
	//����ִ�й���
		t7::preKeyPress = -1;
	case STATE_DISPLAYOBJ:  
	case STATE_MOVINGOBJ: 
	case STATE_DISPLAYNEXT:
	case STATE_DISPLAYOPTION:
	case STATE_OVER:
		
		g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(m_Setting.m_iBckGrndColorR,m_Setting.m_iBckGrndColorG,m_Setting.m_iBckGrndColorB), 0.0f, 0 );
	
		
		break;
	}
	D3DXMATRIX mx;

	//�ں�̨����������ͼ��
	if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
    {	
        //g_pd3dDevice->SetStreamSource( 0, m_pVertexBuffer, 0, sizeof(CUSTOMVERTEX) );
        g_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX );
//      g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
    	switch(m_TestState)
		{
        //����ָ����
		case STATE_DISPLAYINSTURCTION:
			if ( SUCCEEDED( g_pSprite->Begin(D3DXSPRITE_ALPHABLEND) ) )
			{
				D3DXMatrixTransformation2D(&mx, NULL, 0.0, &D3DXVECTOR2((float)1024/(float)1024,(float)768/(float)1024), &D3DXVECTOR2(0,0), NULL, &D3DXVECTOR2(x_resolution/2,y_resolution/2));
				g_pSprite->SetTransform(&mx);
			    g_pSprite->Draw(g_pTextureInst, NULL, &D3DXVECTOR3(512,512,0), &D3DXVECTOR3(0,0,0), 0xffffffff);
			
			}
			g_pSprite->End();
			break;
		//����Ŀ��
        case STATE_DISPLAYOBJ:  
		case STATE_MOVINGOBJ:  
		
			if ( SUCCEEDED( g_pSprite->Begin(D3DXSPRITE_ALPHABLEND) ) )
			{
				if (iShowState != BALL_INTERVAL)
				{
					//ֱ��/768 = ���ų߶�
					D3DXMatrixTransformation2D(&mx, NULL, 0.0, &D3DXVECTOR2(2.0 * m_Setting.m_iBallRadius/1024.,2.0 * m_Setting.m_iBallRadius/1024.), &D3DXVECTOR2(0,0), 0, &D3DXVECTOR2(stPntSmallBall.dX, stPntSmallBall.dY));
					g_pSprite->SetTransform(&mx);
					g_pSprite->Draw(g_pTextureSmallBall, NULL, &D3DXVECTOR3(512,512,0), &D3DXVECTOR3(0,0,0), D3DCOLOR_XRGB(m_Setting.m_iBallColorR,m_Setting.m_iBallColorG,m_Setting.m_iBallColorB));

				
					//ֱ��/768 = ���ų߶�
					//D3DXMatrixTransformation2D(&mx, NULL, 0.0, &D3DXVECTOR2(1.,1.), NULL, 0, &D3DXVECTOR2(x_resolution / 2, y_resolution / 2));
					D3DXMatrixTransformation2D(&mx, NULL, 0.0, &D3DXVECTOR2(2.0 * m_Setting.m_iObstacleRadius / 1024.,2.0 * m_Setting.m_iObstacleRadius / 1024.), NULL, 0, &D3DXVECTOR2(x_resolution / 2, y_resolution / 2));
					g_pSprite->SetTransform(&mx);
					g_pSprite->Draw(g_pTextureBall, NULL,  &D3DXVECTOR3(512,512,0), &D3DXVECTOR3(0,0,0), D3DCOLOR_XRGB(m_Setting.m_iObstacleColorR,m_Setting.m_iObstacleColorG,m_Setting.m_iObstacleColorB));

					//D3DXMatrixTransformation2D(&mx, NULL, 0.0, &D3DXVECTOR2(1.,1.), &D3DXVECTOR2(0, 0), 0, &D3DXVECTOR2(x_resolution / 2, y_resolution / 2));
					D3DXMatrixTransformation2D(&mx, NULL, 0.0, &D3DXVECTOR2(2.0 * m_Setting.m_iBallRadius / 1024.,2.0 * m_Setting.m_iBallRadius / 1024.), &D3DXVECTOR2(0, 0), 0, &D3DXVECTOR2(x_resolution / 2, y_resolution / 2));
					g_pSprite->SetTransform(&mx);
					g_pSprite->Draw(g_pTextureCircle, NULL, &D3DXVECTOR3(512,512,0), &D3DXVECTOR3(0,0,0), D3DCOLOR_XRGB(m_Setting.m_iBallColorR,m_Setting.m_iBallColorG,m_Setting.m_iBallColorB));

				}
		
				

			}
			g_pSprite->End();
			break;
		//�����´β���
		case STATE_DISPLAYFEEDBACK:
			g_pFont->DrawText(NULL, szFeedBack, -1, &txtrect,
				DT_WORDBREAK|DT_NOCLIP|DT_CENTER|DT_VCENTER, D3DCOLOR_XRGB(255,255,255));

			if ( SUCCEEDED( g_pSprite->Begin(D3DXSPRITE_ALPHABLEND) ) )
			{
				//ֱ��/768 = ���ų߶�
				D3DXMatrixTransformation2D(&mx, NULL, 0.0, &D3DXVECTOR2(2.0 * m_Setting.m_iBallRadius/1024.,2.0 * m_Setting.m_iBallRadius/1024.), &D3DXVECTOR2(0,0), 0, &D3DXVECTOR2(stPntSmallBall.dX, stPntSmallBall.dY));
				g_pSprite->SetTransform(&mx);
				g_pSprite->Draw(g_pTextureSmallBall, NULL, &D3DXVECTOR3(512,512,0), &D3DXVECTOR3(0,0,0), D3DCOLOR_XRGB(m_Setting.m_iBallColorR,m_Setting.m_iBallColorG,m_Setting.m_iBallColorB));
			}

			
			g_pSprite->End();
			
			break;
		case STATE_DISPLAYNEXT:  
            g_pFont->DrawText(NULL, Insturction2, -1, &erect,
				DT_WORDBREAK|DT_NOCLIP|DT_CENTER|DT_VCENTER, D3DCOLOR_XRGB(255,255,255));
			break;
		//����ѡ��
		case STATE_DISPLAYOPTION:  
            g_pFont->DrawText(NULL, Insturction3, -1, &erect,
				DT_WORDBREAK|DT_NOCLIP|DT_CENTER|DT_VCENTER, D3DCOLOR_XRGB(255,255,255));
			break;
		//���Խ���
		case STATE_OVER:
            g_pFont1->DrawText(NULL, Insturction4, -1, &erect,
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
VOID t7::TestInit()
{
	
	//Cleanup();
	//CleanupMem();

	//t7::preKeyPress = -1; //��¼��һ���ֱ�����
	//t7::iShowState = t7::BALL_INTERVAL;;
	//t7::bBtnDown = TRUE;
	//t7::bShowSmallBall = TRUE;
	//t7::dBallSpeed = 0;//С���ٶ�
	//t7::bBtnStatus = BTN_UP;//����״̬
	//t7::iTotalTskCnt = 0;					//ʵ�����Դ�


	//g_nThreadExitCount = 0;
	
	dfTotalMove = 0;
	
	dBallSpeed = (double)m_Setting.m_iBallSpeed1;
	
}

int t7::GetKeyZAxis (void)
{
	if(bZdown) 
	{
		bZdown = FALSE;
		return -1000;
	}
	else if(bXdown) 
	{
		bXdown = FALSE;
		return 1000;
	}
	else
	{
        return 0;
	}
}


//************************************************
//*�ⲿ��Ϣ����
//************************************************
LRESULT WINAPI t7::MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{

	switch( msg )
    {
	    case WM_KEYUP:
		    switch( wParam )
            {
			//�˳���
		    case VK_ESCAPE:
		 		// User wants to leave fullscreen mode
				/*
				PostThreadMessage(dwInputThreadID, WM_THREADSTOP,0,0); 	
			    m_TestState = STATE_EXIT;
				break;
				*/
				//ShowCursor(TRUE);
				ShowCursor(TRUE);
				rtn = DialogBox(gHinstance, MAKEINTRESOURCE(IDD_PAUSE), hWnd, t7::PauseMsgProc);
				ShowCursor(FALSE);
				switch (rtn)
				{
				case ID_CONTINUE:
					//TRACE("\n???\n");
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
					Sleep(10);
					m_TestState = STATE_NEXT;
					break;
				case ID_CANCEL:
					//����������;�˳� �򱣴浱ǰ����ʵ������
					if (m_TestState == STATE_MOVINGOBJ)
						SaveData();
					EndDialog(hWnd, rtn);
					PostThreadMessage(dwInputThreadID, WM_THREADSTOP, 0, 0); 	//�˳��߳�
					m_TestState = STATE_EXIT;
					//exit(0);
					break;
				}
			}
			return 0;

        case WM_DESTROY:
			CleanupMem();
            Cleanup();
            PostQuitMessage( 0 );
			m_bDisplayReady = FALSE;
            return 0;
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}

void t7::GoToFeedBack()
{
	/*С��ǰ�ƶ��ľ���*/
	double dNowDistance = sqrt(pow(stPntSmallBall.dX - stPntSmallBallOrg.dX, 2)+pow(stPntSmallBall.dY - stPntSmallBallOrg.dY, 2));
	/*ƫ����*/
	//double rs = (dNowDistance - dOrgDistance)/dOrgDistance * 100;
	double rs = (dNowDistance - dOrgDistance)
		/ (double)m_Setting.m_iObstacleRadius * 100.;
	//double rs = (dNowDistance - dOrgDistance)/fabs(dNowDistance - dOrgDistance) *  sqrt(pow(stPntSmallBall.dX - x_resolution / 2, 2)+pow(stPntSmallBall.dY - y_resolution / 2, 2))/dOrgDistance * 100;

	if (!bTimeOut)
	{
		
		sprintf(szFeedBack, "ƫ����%.2f%%\n",rs);
	
	}
	else
		sprintf(szFeedBack, "��Ӧ��ʱ��");
	
	bTimeOut = FALSE;
	m_TestState = STATE_DISPLAYFEEDBACK;
	QueryPerformanceCounter(&litmp);
	QPart1 = litmp.QuadPart;         //�����ֵֹ
}
void t7::TaskOver()
{
	iTotalTskCnt++;
	iTskCnt++;
	SaveData();


	if(iTskCnt ==  m_TrialTimes)
	{
		

		if(m_TrialType == TRIAL_PRACTICE)
		{
			
			GoToFeedBack();

		}
		else
		{

			m_TestState =  STATE_OVER;

		}

	}
	else
	{
		if(m_TrialType == TRIAL_PRACTICE)
		{
			GoToFeedBack();
		}
		else
			m_TestState = STATE_DISPLAYOBJ;

	}

	TestInit();

}

// ����С��ĳ�ʼλ��
void t7::setSmallBallOriPos(struct Point &stPntSmallBallOrg, int &curStartPos, int startPos)
{
	bool bStartPosTop, bStartPosRight, bStartPosBottom, bStartPosLeft;
	bStartPosTop = (startPos & S_TOP) >> (unsigned)log2((double)S_TOP);
	bStartPosRight = (startPos & S_RIGHT) >> (unsigned)log2((double)S_RIGHT);
	bStartPosBottom = (startPos & S_BOTTOM) >> (unsigned)log2((double)S_BOTTOM);
	bStartPosLeft = (startPos & S_LEFT) >> (unsigned)log2((double)S_LEFT);

	std::vector<int> vec;
	if (bStartPosTop) vec.push_back(TOP);
	if (bStartPosRight) vec.push_back(RIGHT);
	if (bStartPosBottom) vec.push_back(BOTTOM);
	if (bStartPosLeft) vec.push_back(LEFT);

	srand((unsigned)time(NULL));
	int ind = rand() % vec.size();
	curStartPos = vec[ind];


	//��������ٶ�
	std::vector<int> speeds;
	speeds.push_back(m_Setting.m_iBallSpeed1);
	speeds.push_back(m_Setting.m_iBallSpeed2);
	speeds.push_back(m_Setting.m_iBallSpeed3);

	srand((unsigned)time(NULL));
	int ind2 = rand() % speeds.size();
	dBallSpeed = speeds[ind2];

	switch (/*iBallStartPos*/curStartPos)
	{
	case TOP:
		stPntSmallBallOrg.dX = x_resolution / 2;
		stPntSmallBallOrg.dY = y_resolution / 2 - dOrgDistance;//�����ĵľ��룺350pixles
		break;
	case RIGHT:
		stPntSmallBallOrg.dX = x_resolution / 2 + dOrgDistance;
		stPntSmallBallOrg.dY = y_resolution / 2;
		break;
	case BOTTOM:
		stPntSmallBallOrg.dX = x_resolution / 2;
		stPntSmallBallOrg.dY = y_resolution / 2 + dOrgDistance;//�����ĵľ��룺350pixles
		break;
	case LEFT:
		stPntSmallBallOrg.dX = x_resolution / 2 - dOrgDistance;
		stPntSmallBallOrg.dY = y_resolution / 2;
		break;


	}
}


//************************************************
//*��������ִ�й���
//************************************************
VOID t7::UpdateState()
{
    switch(m_TestState)
	{
	//����ָ����
    case STATE_DISPLAYINSTURCTION:       
        break;
	//����Ŀ�꣨Ӧ���ǳ�ʼ�������ã�
	case STATE_DISPLAYOBJ:
		
		
		if(QueryPerformanceFrequency(&litmp))
		{
			dfFreq = (double)litmp.QuadPart;// ��ü�������ʱ��Ƶ��
			m_SampleInt = 0.04 * dfFreq;
		}
	    QueryPerformanceCounter(&litmp);
		QPart1 = litmp.QuadPart;           // ��ó�ʼֵ
		dfTim = 0;
		dfTotalMove = 0;
		dfInterval = 0;
		QPart3 = QPart1;
		QPart2 = QPart1;

		// ����С��ĳ�ʼλ��
		setSmallBallOriPos(stPntSmallBallOrg, curStartPos, m_Setting.m_iBallStartPos);
		/*if(RANDOM == m_Setting.m_iBallStartPos)
			iBallStartPos = rand() % 4;
		else
			iBallStartPos =  m_Setting.m_iBallStartPos; 

		switch (iBallStartPos)
		{
		case TOP:
			stPntSmallBallOrg.dX = x_resolution / 2;
			stPntSmallBallOrg.dY = y_resolution / 2 - 350;//�������350pixles
			break;
		case RIGHT:
			stPntSmallBallOrg.dX = x_resolution / 2 + 350;
			stPntSmallBallOrg.dY = y_resolution / 2;
			break;
		case BOTTOM:
			stPntSmallBallOrg.dX = x_resolution / 2;
			stPntSmallBallOrg.dY = y_resolution / 2 + 350;//�������350pixles
			break;
		case LEFT:
			stPntSmallBallOrg.dX = x_resolution / 2 - 350;
			stPntSmallBallOrg.dY = y_resolution / 2;
			break;


		}*/
		stPntSmallBall = stPntSmallBallOrg;
		
		rec.smallBallBegCo = Point2(stPntSmallBallOrg.dX, stPntSmallBallOrg.dY);
		rec.targetCo = Point2(x_resolution / 2, y_resolution / 2);
		
		bShowSmallBall = TRUE;
		m_TestState = STATE_MOVINGOBJ;
		iShowState = BALL_INTERVAL;
		
		rec.freq = dfFreq;
		rec.no = iTotalTskCnt + 1;
		rec.smallBallSpeed = dBallSpeed;
		rec.setSmallBallDir(curStartPos);
		rec.moveBegTime = QPart1;
		rec.evaluateTime = (double)m_Setting.m_iObstacleRadius
			/ (double)dBallSpeed;
		rec.flag.clear();
		break;
	//��������ִ�У�Ӧ����С���˶��Ĺ��̣�
    case STATE_MOVINGOBJ:
	{
		//���50ms����һ��
		do
		{
			Sleep(1);
			QueryPerformanceCounter(&litmp);
			QPart2 = litmp.QuadPart;         //�����ֵֹ
			dfMinus = (double)(QPart2 - QPart1);
		} while (dfMinus < m_SampleInt);//dfTim);//			
		dfTim = dfMinus / dfFreq;  // ��ö�Ӧ��ʱ��ֵ����λΪ��
		QPart1 = QPart2;           // ��ó�ʼֵ

		// С���ƶ�
		if (iShowState != BALL_INTERVAL)
		{
			// ����С����˶�����
			//setSmallBallDirection();
			switch (/*iBallStartPos*/curStartPos)
			{
			case TOP:
				stPntSmallBall.dY += dBallSpeed*dfTim;
				break;
			case BOTTOM:
				stPntSmallBall.dY -= dBallSpeed*dfTim;
				break;
			case RIGHT:
				stPntSmallBall.dX -= dBallSpeed*dfTim;
				break;
			case LEFT:
				stPntSmallBall.dX += dBallSpeed*dfTim;
				break;

			}

		//	if (BALL_SPEED_ACC == m_Setting.m_iSpeedMode)
		//		dBallSpeed += 1.0*m_Setting.m_iBallSpeedAcc*dfTim;
		}

		/*�ж�С���Ƿ�����ڵ���*/
		if (hp.getDis(stPntSmallBall, stPntSmallBallOrg) 
			+ m_Setting.m_iObstacleRadius >= dOrgDistance 
			&& !rec.isFlagExist("disappearTime")/*��֤��һ�θ�ֵ*/) {
			LARGE_INTEGER tmp;
			QueryPerformanceCounter(&tmp);
			rec.disappearTime = tmp.QuadPart;
			rec.setFlag("disappearTime", true);
		}

		/*״̬��ת*/
		switch (iShowState)
		{
			// Ӧ���ǵ���С����֮��ļ��
		case BALL_INTERVAL:
			dfInterval += dfTim;

			// �ж�ʱ�����Ƿ����
			if (dfInterval > m_Setting.m_iIntervalTime)
			{
				dfInterval = 0;
				iShowState = BALL_SHOW;
			}

			break;

		case BALL_SHOW:

			//����ע�� stPntSmallBallֻ��ͼƬ������
			dfTotalMove = dfTotalMove + dfTim;

			//��ʱ���� ���վ�����㡰��ʱ�� ����һ��С����
			if (abs(stPntSmallBall.dX - stPntSmallBallOrg.dX + stPntSmallBall.dY - stPntSmallBallOrg.dY) > dOrgDistance +m_Setting.m_iObstacleRadius)
			{
				bTimeOut = TRUE;
				dfTotalMove = 0;
				TaskOver();
			}


			break;


		}


		break;
	}
	case STATE_DISPLAYFEEDBACK:   /*�����ǿ�ѡ��*/  
		QueryPerformanceCounter(&litmp);
		QPart2 = litmp.QuadPart;         //�����ֵֹ
		dfMinus = (double)(QPart2-QPart1);
		dfTim = dfMinus / dfFreq;        // ��ö�Ӧ��ʱ��ֵ����λΪ��	
		QPart1 = QPart2;
		dfTotalMove = dfTotalMove + dfTim;

		if (dfTotalMove > 1)// ��ʾ����3��
		{	
			dfTotalMove = 0;

			if (iTskCnt ==   m_Setting.m_iPracTimes*(m_Setting.m_iTop + m_Setting.m_iBottom + m_Setting.m_iLeft + m_Setting.m_iRight) * 3)
			{
				//������ʽ����ѡ��
				/*m_TrialType = TRIAL_EXPERMENT;
				m_TrialTimes = m_Setting.m_iExpTimes;
				m_TestState = STATE_DISPLAYOPTION;
				iTskCnt = 0;*/
				m_TestState = STATE_OVER;
				
			}
			else
				m_TestState = STATE_DISPLAYOBJ;
		}
		break;

	//����ѡ���
    case STATE_DISPLAYOPTION:            
		break;
	//���Խ���
	case STATE_OVER: 

		break;
    //�����˳�
    case STATE_EXIT: 
		if (g_nThreadExitCount == 1)
		{
			SendMessage(hWnd, WM_CLOSE, 0, 0); // �رմ���
		    SendMessage(hWnd,WM_DESTROY,0,0);
		}
		break;
	default:
		break;
	}
}

//************************************************
//*���ݸ������߳�
//************************************************
DWORD WINAPI t7::InputThreadProcedure(LPVOID lpStartupParam)
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
			if (JoystickUpdate() /*|| m_TestState == STATE_DISPLAYINSTURCTION*/)
			{
				if (!bBtnDown /*|| m_TestState == STATE_DISPLAYINSTURCTION*/)
				{
					/*��ͬ״̬��Ӧ����*/
					switch(m_TestState)
					{
						case STATE_DISPLAYINSTURCTION:
							//���ֿ�ʼѡ��ȴ����������ʼ����
								for (i = 0; i < 12; i++)
								{
									if (IsButtonDown(KEY_YES))
									{
										preKeyPress = KEY1;
										bBtnDown = TRUE;
										TestInit();
										m_TestState = STATE_DISPLAYOBJ;

									}
									break;
								}
							break;
							
							//�����Ϣѡ��
						case STATE_DISPLAYNEXT:
					
							for(i=0;i<8;i++)
							{

								if(IsButtonDown(m_StartKey[i]))
								{
									preKeyPress = i;
									bBtnDown = TRUE;
									iShowState = BALL_INTERVAL;
									m_TestState = STATE_DISPLAYOBJ;
									break;
								}
							}
						

					

							break;

						
						case STATE_DISPLAYOPTION:
							
								for (i = 0; i < 8; i++)
								{

									if (IsButtonDown(m_StartKey[i]))
									{
										preKeyPress = i;
										bBtnDown = TRUE;
										m_TrialType = TRIAL_EXPERMENT;
										TestInit();
										iShowState = BALL_INTERVAL;
										m_TestState = STATE_DISPLAYOBJ;
										break;
									}
								}
							
								
							
						
							break;	
						case STATE_DISPLAYOBJ:
						case STATE_MOVINGOBJ:
							
								
							if (IsButtonDown(KEY_YES) && BALL_INTERVAL != iShowState)
							{
								/*�ж�С���Ƿ�����ڵ���*/
								if (abs(stPntSmallBall.dX - stPntSmallBallOrg.dX + stPntSmallBall.dY - stPntSmallBallOrg.dY)
										> abs(dOrgDistance - m_Setting.m_iObstacleRadius)) {
									/*��ȡ����ʱ��*/
									if (!rec.isFlagExist("pressTime")) {
										LARGE_INTEGER tmp;
										QueryPerformanceCounter(&tmp);
										rec.pressTime = tmp.QuadPart;
										rec.pressSmallBallCo = Point2(stPntSmallBall.dX, stPntSmallBall.dY);
										rec.setFlag("pressTime",true);
									}
									
									preKeyPress = KEY_YES;
									iReactTime = dfTotalMove;
									bBtnDown = TRUE;
									TaskOver();
								}
		
							}
							

							break;
						case STATE_OVER: 
						case STATE_NEXT:
							//���Խ������ȴ���������˳�
					
							for(i=0;i<12;i++)
							{
								if(IsButtonDown(i))
								{
									preKeyPress = i;
									bBtnDown = TRUE;
									PostThreadMessage(dwInputThreadID, WM_THREADSTOP,0,0); 	
									m_TestState = STATE_NEXT;// STATE_EXIT --> STATE_NEXT
								}
							}
					
					
							break;
						default:
							break;
					}
				}

				else
				{
					bBtnDown = HasBtnDown(preKeyPress);
					if(m_TestState == STATE_DISPLAYINSTURCTION)
					{
						bBtnDown = FALSE;
					}
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
int APIENTRY t7::_tWinMain(HINSTANCE &hInstance, HINSTANCE &hPrevInstance, LPTSTR &lpCmdLine, int &nCmdShow, HWND &_hWnd, std::string winClassName, std::string winName)
{
 	// TODO: Place code here.
	//��ô��ݵ������в������õ����������ֺ�������
	//����7-�ٶ�֪�� 1-1-0
	t7::rtn = 0;
	t7::preKeyPress = -1; //��¼��һ���ֱ�����
	t7::bTimeOut = FALSE;
	t7::iShowState = t7::BALL_INTERVAL;
	t7::bShowSmallBall = TRUE;
	t7::iReactTime = 0;
	t7::dBallSpeed = 0;//С���ٶ�
	t7::bBtnStatus = BTN_UP;//����״̬
	t7::iTskCnt = 0;						//ʵ���л�����ϰ�Ĵ���ͳ��
	t7::iTotalTskCnt = 0;					//ʵ�����Դ�
	t7::bBtnDown = TRUE;
	g_nThreadExitCount = 0;             //��ǰ���е��߳���
	dwInputThreadID = 0;              //��׼�������߳�ID 
	preKeyPress = -1; //��¼��һ���ֱ�����
	t7::m_TrialGroups = 0;
	m_TestState = STATE_DISPLAYINSTURCTION;
	// ���������ʼ��
	iTskCnt = 0;

	// ��ʼ�������״̬
	bool bUnClosedLastWin = true;
	hWnd = _hWnd;
	gHinstance = hInstance;
	g_nThreadExitCount = 0;
	ShowCursor(FALSE);

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
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_VREDRAW|CS_HREDRAW|CS_DBLCLKS, MsgProc, 0L, 0L, 
                      hInstance, NULL, NULL, NULL, NULL,
					  std::to_string(nCmdShow).c_str(), NULL };
    RegisterClassEx( &wc );

	int nFullWidth=GetSystemMetrics(SM_CXSCREEN); 
	int nFullHeight=GetSystemMetrics(SM_CYSCREEN); 

    //��������
	_hWnd = hWnd = CreateWindow(std::to_string(nCmdShow).c_str(), std::to_string(nCmdShow).c_str(),
                              WS_VISIBLE|WS_POPUP, 0, 0, nFullWidth, nFullHeight,
                              NULL, NULL, wc.hInstance, NULL );

	//��ʾ������
	SetFocus(hWnd);
	//ShowCursor(FALSE);

	x_resolution =  nFullWidth;
	y_resolution =  nFullHeight;

	if (m_lpkDInput)
	{
	m_lpkDInput->Release();
	}
	if (m_lpkDIDevice)
	{
	m_lpkDIDevice->Release();

	}
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
		t7::preKeyPress = -1;
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

	m_bDisplayReady = FALSE;
	// declare a variable of our data structure to pass to the ThreadProcedure
	MYDATA MyThreadData;
    MyThreadData.nTime = 7509843;
	MyThreadData.nNumber = 39;

	//�������ݸ������߳�
	// declare a DWORD to hold our thread's new generated ID
	HANDLE h = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE) InputThreadProcedure,
	(LPVOID) &MyThreadData, NULL, &dwInputThreadID);

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

void t7::hideLastWindow(bool &bUnClosedLastWin, std::string &winClassName, std::string &winName, HINSTANCE &hInstance)
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

//��ͣ�Ի�����Ϣѭ��
BOOL CALLBACK t7::PauseMsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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
