// Task1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Task8.h"
#include "..\..\all\Datatype.h"
#include <direct.h>
#include <stdio.h> 
#include <d3d9.h>
#include <d3dx9.h>
#include <time.h>   
#include "..\..\all\RandFcn.h" 
#include "..\..\all\Input.h"

FILE *sfp;



#define WM_THREADSTOP (WM_USER+1)
// define a data structure to hold our data ?optional
struct MYDATA {
    int nTime;
    int nNumber;
};
int g_nThreadExitCount = 0;             //当前运行的线程数
DWORD dwInputThreadID = 0;              //瞄准器输入线程ID      
struct Point
{
	double dX;
	double dY;
};

enum{BALL_INTERVAL, BALL_SHOW,BALL_OUT_SHOW};
int rtn;
int preKeyPress = -1; //记录上一次手柄按键
BOOL bTimeOut = FALSE;
int iShowState = BALL_INTERVAL;;
char szFeedBack[100];
int iBallStartPos; 	
const char szSpeedMode[][100]={"匀速","匀加速"};
BOOL bBtnDown = TRUE;
//当前小球坐标
Point stPntSmallBall;
//小球初始坐标
Point stPntSmallBallOrg;
const double dOrgDistance = 350;

BOOL bShowSmallBall = TRUE;
int iReactTime = 0;

double dBallSpeed = 0;//小球速度
BOOL bBtnStatus = BTN_UP;//按键状态

int JoyX,JoyY,JoyZ;                     //当前操纵杆输入值     

struct TaskSetting7  m_Setting;        //任务1设置参数
struct HardSetting   m_HardSetting;     //硬件设置参数
struct PartInfo   m_PartInfo;           //被试者信息
  
short m_TrialType;						//测试类型
int m_TrialTime;						//测试时间
int m_TrialTimes;						//测试次数
int iTskCnt = 0;						//实验中或者练习的次数统计
int iTotalTskCnt = 0;					//实验总试次

int m_TrialGroups = 0;
int x_resolution=1024;			//屏幕分辨率
int y_resolution=768;             //屏幕分辨率
int x_resolution1024 = 1024;
int y_resolution768 = 768;
int rec_x_begin = (x_resolution - x_resolution1024)/2;
int rec_y_begin = (y_resolution - y_resolution768)/2;
int rec_x_end = (x_resolution + x_resolution1024)/2;
int rec_y_end = (y_resolution + y_resolution768)/2;

const float FontScale = (float)(x_resolution+y_resolution)/1400.0;    //字体随屏幕分辨率的放缩尺度

const char Insturction1[] = "    屏幕上的白色“⊥”是目标，黄色\
“⊥”是追踪环。您的任务是：使用操纵杆来控制追踪环的运动，尽可能用追\
踪环套住目标。追踪环套住目标时，追踪环会变成红色。按X键开始任务。”双\
手追踪追踪任务的指导语为“屏幕上的白色“⊥”是目标，黄色“⊥”是追\
踪环。您的任务是：使用操纵杆来控制追踪环的运动，尽可能用追踪环套住目\
标。同时，使用旋钮控制追踪环的姿态，尽可能保持追踪环的姿态与目标一致。\
追踪环套住目标时，追踪环会变成红色。按X键开始任务。";
const char Insturction2[] = "该任务完成，按任意键继续！";
const char Insturction3[] = "练习结束，按任意键进入正式实验。";
const char Insturction4[] = "该任务完成，按任意键继续！";
LPDIRECT3D9             g_pD3D       = NULL;		    //directx3d对象
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL;		    //directx设备对象
LPDIRECT3DTEXTURE9      g_pTextureInst  = NULL;	        //纹理对象
LPDIRECT3DTEXTURE9      g_pTextureSmallBall  = NULL;	//小球纹理对象
LPDIRECT3DTEXTURE9      g_pTextureBall  = NULL;	    	//大球纹理对象

LPDIRECT3DTEXTURE9      g_pTextureCircle = NULL;
LPD3DXSPRITE            g_pSprite  = NULL;              //精灵对象
LPD3DXFONT              g_pFont      = 0;               //字体对象
LPD3DXFONT              g_pFont1     = 0;				//字体对象
LPDIRECT3DVERTEXBUFFER9      m_pVertexBuffer  = NULL;	//顶点对象

D3DXMATRIX m_Transform;                                 //坐标变换矩阵
float TimeInt;                                          //时间间隔
short m_TrialNo;                                        //测试次数序号
BOOL m_bDisplayReady;                                   //渲染设备就绪标志
                         
 
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

//const double dfTim = 0.05;                          //采样间隔50ms
double m_SampleInt;

UINT m_PointNum;
UINT m_MemNum;

RECT strurect,lerect,rerect,erect,txtrect;

short m_TestState;
char m_file[220];
char m_file1[220];
HWND hWnd;
char m_TesterName[40];
char m_DataName[60];
char m_TaskNumStr[100];

//Timer
LARGE_INTEGER litmp; 
LONGLONG QPart1,QPart2,QPart3;
double dfMinus, dfMinus1, dfFreq, dfTim, dfdetTim, dfInterval, dfTotalMove; 
BOOL bXdown,bZdown;


void TestInit();
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
			fscanf(fp,"BallSpeed\t%d\n",&m_Setting.m_iBallSpeed);
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

	//写入文件
	fp = fopen(m_file,"at");

	
	fprintf(fp,"速度知觉测试\n");
	fprintf(fp,"小球颜色R:%d G:%d B:%d\t",m_Setting.m_iBallColorR,m_Setting.m_iBallColorG,m_Setting.m_iBallColorB);
	fprintf(fp,"半径:%d像素\t%s%d\t",m_Setting.m_iBallRadius,szSpeedMode[BALL_SPEED_CONSTANT],m_Setting.m_iBallSpeed);

	if (BALL_SPEED_ACC == m_Setting.m_iSpeedMode)
		fprintf(fp,"加速度:%f\t速度上限:%f\t",m_Setting.m_iBallSpeedAcc,m_Setting.m_iBallSpeedMax);

	fprintf(fp,"遮挡物颜色R:%d G:%d B:%d\t\n",m_Setting.m_iObstacleColorR,m_Setting.m_iObstacleColorG,m_Setting.m_iObstacleColorB);

	fprintf(fp,"任务序号\t偏差率\n");
	
	fclose(fp);
	

	

}

//************************************************
//*保存结果数据记录文件
//************************************************
VOID SaveData()
{
	FILE* fp = fopen(m_file,"at");
	double dNowDistance = sqrt(pow(stPntSmallBall.dX - stPntSmallBallOrg.dX, 2)+pow(stPntSmallBall.dY - stPntSmallBallOrg.dY, 2));
	fprintf(fp,"%d\t",iTotalTskCnt);

	if (!bTimeOut)
		fprintf(fp,"%.4lf%%\n",(dNowDistance - dOrgDistance)/dOrgDistance * 100);
	fclose(fp);
}

//************************************************
//*初始化DirectX 3D
//************************************************
HRESULT InitD3D( HWND hWnd )
{
	m_TestState = STATE_DISPLAYINSTURCTION;
	m_TrialNo = -1;

	if(m_Setting.m_PracMode == 1)
	{
		m_TrialType = TRIAL_PRACTICE;
		m_TrialTimes =  m_Setting.m_iPracTimes;
		
		
	}
	else
	{
		m_TrialType = TRIAL_EXPERMENT;
		m_TrialTimes = m_Setting.m_iExpTimes;
	}
	//材质大小
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


	//创建精灵D3DXCreateSprite函数用来创建与一个特定D3D设备相关联的精灵对象。Sprite对象用于绘制二维图像到屏幕。
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
		0,0,GB2312_CHARSET,0,0,0, TEXT("宋体"), &g_pFont)))
	{
		return E_FAIL;
	}
	if (FAILED(D3DXCreateFont(g_pd3dDevice,40*FontScale,20*FontScale,20,
		0,0,GB2312_CHARSET,0,0,0, TEXT("宋体"), &g_pFont1)))
	{
		return E_FAIL;
	}
 
	m_bDisplayReady = TRUE;
	SaveName();
	TestInit();
    return S_OK;
}

//************************************************
//*释放数组内存
//************************************************
VOID CleanupMem()
{
	
}

//************************************************
//*释放DirectX对象
//************************************************
VOID Cleanup()
{
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
//*渲染
//************************************************
VOID Render()
{
	switch(m_TestState)
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
		
		g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(m_Setting.m_iBckGrndColorR,m_Setting.m_iBckGrndColorG,m_Setting.m_iBckGrndColorB), 0.0f, 0 );
	
		
		break;
	}
	D3DXMATRIX mx;

	//在后台缓冲区绘制图形
	if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
    {	
        //g_pd3dDevice->SetStreamSource( 0, m_pVertexBuffer, 0, sizeof(CUSTOMVERTEX) );
        g_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX );
//      g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
    	switch(m_TestState)
		{
        //呈现指导语
		case STATE_DISPLAYINSTURCTION:
			if ( SUCCEEDED( g_pSprite->Begin(D3DXSPRITE_ALPHABLEND) ) )
			{
				D3DXMatrixTransformation2D(&mx, NULL, 0.0, &D3DXVECTOR2((float)1024/(float)1024,(float)768/(float)1024), &D3DXVECTOR2(0,0), NULL, &D3DXVECTOR2(x_resolution/2,y_resolution/2));
				g_pSprite->SetTransform(&mx);
			    g_pSprite->Draw(g_pTextureInst, NULL, &D3DXVECTOR3(512,512,0), &D3DXVECTOR3(0,0,0), 0xffffffff);
			
			}
			g_pSprite->End();
			break;
		//呈现目标
        case STATE_DISPLAYOBJ:  
		case STATE_MOVINGOBJ:  
		
			if ( SUCCEEDED( g_pSprite->Begin(D3DXSPRITE_ALPHABLEND) ) )
			{
				if (iShowState != BALL_INTERVAL)
				{
					//直径/768 = 缩放尺度
					D3DXMatrixTransformation2D(&mx, NULL, 0.0, &D3DXVECTOR2(2.0 * m_Setting.m_iBallRadius/768,2.0 * m_Setting.m_iBallRadius/768), &D3DXVECTOR2(0,0), 0, &D3DXVECTOR2(stPntSmallBall.dX, stPntSmallBall.dY));
					g_pSprite->SetTransform(&mx);
					g_pSprite->Draw(g_pTextureSmallBall, NULL, &D3DXVECTOR3(512,512,0), &D3DXVECTOR3(0,0,0), D3DCOLOR_XRGB(m_Setting.m_iBallColorR,m_Setting.m_iBallColorG,m_Setting.m_iBallColorB));

				
					//直径/768 = 缩放尺度
					D3DXMatrixTransformation2D(&mx,NULL, 0.0, &D3DXVECTOR2(2.0 * m_Setting.m_iObstacleRadius/768,2.0 * m_Setting.m_iObstacleRadius/768), NULL, 0, &D3DXVECTOR2(x_resolution/2,y_resolution/2));
					g_pSprite->SetTransform(&mx);
					g_pSprite->Draw(g_pTextureBall, NULL,  &D3DXVECTOR3(512,512,0), &D3DXVECTOR3(0,0,0), D3DCOLOR_XRGB(m_Setting.m_iObstacleColorR,m_Setting.m_iObstacleColorG,m_Setting.m_iObstacleColorB));

					D3DXMatrixTransformation2D(&mx, NULL, 0.0, &D3DXVECTOR2(2.0 * m_Setting.m_iBallRadius/768,2.0 * m_Setting.m_iBallRadius/768), &D3DXVECTOR2(0,0), 0, &D3DXVECTOR2(x_resolution/2,y_resolution/2));
					g_pSprite->SetTransform(&mx);
					g_pSprite->Draw(g_pTextureCircle, NULL, &D3DXVECTOR3(512,512,0), &D3DXVECTOR3(0,0,0), D3DCOLOR_XRGB(m_Setting.m_iBallColorR,m_Setting.m_iBallColorG,m_Setting.m_iBallColorB));

				}
		
				

			}
			g_pSprite->End();
			break;
		//进行下次测试
		case STATE_DISPLAYFEEDBACK:
			g_pFont->DrawText(NULL, szFeedBack, -1, &txtrect,
				DT_WORDBREAK|DT_NOCLIP|DT_CENTER|DT_VCENTER, D3DCOLOR_XRGB(255,255,255));

			if ( SUCCEEDED( g_pSprite->Begin(D3DXSPRITE_ALPHABLEND) ) )
			{
				//直径/768 = 缩放尺度
				D3DXMatrixTransformation2D(&mx, NULL, 0.0, &D3DXVECTOR2(2.0 * m_Setting.m_iBallRadius/768,2.0 * m_Setting.m_iBallRadius/768), &D3DXVECTOR2(0,0), 0, &D3DXVECTOR2(stPntSmallBall.dX, stPntSmallBall.dY));
				g_pSprite->SetTransform(&mx);
				g_pSprite->Draw(g_pTextureSmallBall, NULL, &D3DXVECTOR3(512,512,0), &D3DXVECTOR3(0,0,0), D3DCOLOR_XRGB(m_Setting.m_iBallColorR,m_Setting.m_iBallColorG,m_Setting.m_iBallColorB));
			}

			
			g_pSprite->End();
			
			break;
		case STATE_DISPLAYNEXT:  
            g_pFont->DrawText(NULL, Insturction2, -1, &erect,
				DT_WORDBREAK|DT_NOCLIP|DT_CENTER|DT_VCENTER, D3DCOLOR_XRGB(255,255,255));
			break;
		//测试选项
		case STATE_DISPLAYOPTION:  
            g_pFont->DrawText(NULL, Insturction3, -1, &erect,
				DT_WORDBREAK|DT_NOCLIP|DT_CENTER|DT_VCENTER, D3DCOLOR_XRGB(255,255,255));
			break;
		//测试结束
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
//*测试任务初始化
//************************************************
VOID TestInit()
{
	
	
	dfTotalMove = 0;
	
	dBallSpeed = (double)m_Setting.m_iBallSpeed;
	
	
}

int GetKeyZAxis (void)
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
				PostThreadMessage(dwInputThreadID, WM_THREADSTOP,0,0); 	
			    m_TestState = STATE_EXIT;
				break;
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

void GoToFeedBack()
{
	double dNowDistance = sqrt(pow(stPntSmallBall.dX - stPntSmallBallOrg.dX, 2)+pow(stPntSmallBall.dY - stPntSmallBallOrg.dY, 2));
	double rs = (dNowDistance - dOrgDistance)/dOrgDistance * 100;
	//double rs = (dNowDistance - dOrgDistance)/fabs(dNowDistance - dOrgDistance) *  sqrt(pow(stPntSmallBall.dX - x_resolution / 2, 2)+pow(stPntSmallBall.dY - y_resolution / 2, 2))/dOrgDistance * 100;

	if (!bTimeOut)
	{
		sprintf(szFeedBack, "偏差率%.2f%%\n",rs);
	
	}
	else
		sprintf(szFeedBack, "反应超时！");
	
	bTimeOut = FALSE;
	m_TestState = STATE_DISPLAYFEEDBACK;
	QueryPerformanceCounter(&litmp);
	QPart1 = litmp.QuadPart;         //获得中止值
}
void TaskOver()
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
		
		
		if(QueryPerformanceFrequency(&litmp))
		{
			dfFreq = (double)litmp.QuadPart;// 获得计数器的时钟频率
			m_SampleInt = 0.04 * dfFreq;
		}
	    QueryPerformanceCounter(&litmp);
		QPart1 = litmp.QuadPart;           // 获得初始值
		dfTim = 0;
		dfTotalMove = 0;
		dfInterval = 0;
		QPart3 = QPart1;
		QPart2 = QPart1;


       

		srand((unsigned)time(NULL));

		
		if(RANDOM == m_Setting.m_iBallStartPos)
			iBallStartPos = rand() % 4;
		else
			iBallStartPos =  m_Setting.m_iBallStartPos; 

		switch (iBallStartPos)
		{
		case TOP:
			stPntSmallBallOrg.dX = x_resolution / 2;
			stPntSmallBallOrg.dY = y_resolution / 2 - 350;//两者相据350pixles
			break;
		case RIGHT:
			stPntSmallBallOrg.dX = x_resolution / 2 + 350;
			stPntSmallBallOrg.dY = y_resolution / 2;
			break;
		case BOTTOM:
			stPntSmallBallOrg.dX = x_resolution / 2;
			stPntSmallBallOrg.dY = y_resolution / 2 + 350;//两者相据350pixles
			break;
		case LEFT:
			stPntSmallBallOrg.dX = x_resolution / 2 - 350;
			stPntSmallBallOrg.dY = y_resolution / 2;
			break;


		}
		stPntSmallBall = stPntSmallBallOrg;
		bShowSmallBall = TRUE;
		m_TestState = STATE_MOVINGOBJ;
		iShowState = BALL_INTERVAL;
		break;
	//测试任务执行
    case STATE_MOVINGOBJ:
		
			//间隔50ms采样一次
			do
			{
				Sleep(1);
				QueryPerformanceCounter(&litmp);
				QPart2 = litmp.QuadPart;         //获得中止值
				dfMinus = (double)(QPart2-QPart1);
			}while(dfMinus<m_SampleInt);//dfTim);//			
			dfTim = dfMinus / dfFreq;  // 获得对应的时间值，单位为秒
			QPart1 = QPart2;           // 获得初始值
			
		
		
			if (iShowState != BALL_INTERVAL)
			{
				switch (iBallStartPos)
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
					stPntSmallBall.dX  += dBallSpeed*dfTim;
					break;

				}

				if (BALL_SPEED_ACC == m_Setting.m_iSpeedMode)
					dBallSpeed += 1.0*m_Setting.m_iBallSpeedAcc*dfTim;
			}
		


			switch (iShowState)
			{
				case BALL_INTERVAL:
					dfInterval += dfTim;
					
					if (dfInterval > m_Setting.m_iIntervalTime)
					{
						dfInterval = 0;
						iShowState = BALL_SHOW;
					}
					
					break;

				case BALL_SHOW:

					//这里注意 stPntSmallBall只是图片的坐标
					dfTotalMove = dfTotalMove + dfTim;

					if (dfTotalMove >= 15)
					{
						bTimeOut = TRUE;
						dfTotalMove = 0;
						TaskOver();
					}

					
					break;


			}


		break;

	case STATE_DISPLAYFEEDBACK:     
		QueryPerformanceCounter(&litmp);
		QPart2 = litmp.QuadPart;         //获得中止值
		dfMinus = (double)(QPart2-QPart1);
		dfTim = dfMinus / dfFreq;        // 获得对应的时间值，单位为秒	
		QPart1 = QPart2;
		dfTotalMove = dfTotalMove + dfTim;

		if (dfTotalMove > 3)
		{	
			dfTotalMove = 0;

			if (iTskCnt ==   m_Setting.m_iPracTimes)
			{
				//呈现正式测试选项
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

	//出现选项框
    case STATE_DISPLAYOPTION:            
		break;
	//测试结束
	case STATE_OVER: 

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
				if (!bBtnDown)
				{
					
					switch(m_TestState)
					{
						case STATE_DISPLAYINSTURCTION:
							//呈现开始选项，等待按任意键开始测试
							if(IsButtonDown(KEY_YES))
							{	
								preKeyPress = KEY1;
								bBtnDown = TRUE;
								m_TestState = STATE_DISPLAYOBJ;

							}
							break;
							//组间休息选项
						case STATE_DISPLAYNEXT:
					
							for(i=0;i<8;i++)
							{

								if(IsButtonDown(m_StartKey[i]))
								{
									preKeyPress = i;
									bBtnDown = TRUE;
									iShowState = BALL_INTERVAL;
									m_TestState = STATE_DISPLAYOBJ;
								}
							}
						

					

							break;

						
						case STATE_DISPLAYOPTION:
								for(i=0;i<8;i++)
								{

									if(IsButtonDown(m_StartKey[i]))
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
						
							if(IsButtonDown(KEY_YES)  && BALL_INTERVAL != iShowState)
							{
								preKeyPress = KEY_YES;
								iReactTime = dfTotalMove;
								bBtnDown = TRUE;
								TaskOver();
							}



							break;
						case STATE_OVER: 
							//测试结束，等待按任意键退出
					
							for(i=0;i<12;i++)
							{
								if(IsButtonDown(i))
								{
									preKeyPress = i;
									bBtnDown = TRUE;
									PostThreadMessage(dwInputThreadID, WM_THREADSTOP,0,0); 	
									m_TestState = STATE_EXIT;
								}
							}
					
					
							break;
						default:
							break;
					}
				}

				else
					bBtnDown = HasBtnDown(preKeyPress);
			}


		}
		
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
 	// TODO: Place code here.
	//获得传递的命令行参数，得到被试着名字和任务编号
	//任务7-速度知觉 1-1-0

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
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_VREDRAW|CS_HREDRAW|CS_DBLCLKS, MsgProc, 0L, 0L, 
                      hInstance, NULL, NULL, NULL, NULL,
                      "ClassName", NULL };
    RegisterClassEx( &wc );

	int nFullWidth=GetSystemMetrics(SM_CXSCREEN); 
	int nFullHeight=GetSystemMetrics(SM_CYSCREEN); 

    //创建窗口
    hWnd = CreateWindow( "ClassName", "Task7", 
                              WS_VISIBLE|WS_POPUP, 0, 0, nFullWidth, nFullHeight,
                              NULL, NULL, hInstance, NULL );

	x_resolution =  nFullWidth;
	y_resolution =  nFullHeight;


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

	m_bDisplayReady = FALSE;
	// declare a variable of our data structure to pass to the ThreadProcedure
	MYDATA MyThreadData;
    MyThreadData.nTime = 7509843;
	MyThreadData.nNumber = 39;

	//创建操纵杆输入线程
	// declare a DWORD to hold our thread's new generated ID
	HANDLE h = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE) InputThreadProcedure,
	(LPVOID) &MyThreadData, NULL, &dwInputThreadID);

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
					Render();
					
				}
		
			}
			
		}
	}
	//注销窗口类
    UnregisterClass( "ClassName", hInstance );
	return rtn;
}