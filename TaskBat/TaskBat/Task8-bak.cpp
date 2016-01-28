// Task1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Task8.h"


FILE *t8::sfp;

HINSTANCE t8::gHinstance;//全局句柄

int t8::g_nThreadExitCount = 0;             //当前运行的线程数
DWORD t8::dwInputThreadID = 0;              //瞄准器输入线程ID      


int t8::rtn;
int t8::preKeyPress = -1; //记录上一次手柄按键
BOOL t8::bTimeOut = FALSE;
int t8::iShowState = t8::BALL_INTERVAL;;
char t8::szFeedBack[100];
int t8::iBallStartPos;
int t8::curStartPos;
const char t8::szSpeedMode[][100] = { "匀速","匀加速" };
BOOL t8::bBtnDown = TRUE;


BOOL t8::bShowSmallBall = TRUE;
int t8::iReactTime = 0;

BOOL t8::bBtnStatus = BTN_UP;//按键状态

int t8::JoyX, t8::JoyY, t8::JoyZ;                     //当前操纵杆输入值     

struct TaskSetting8  t8::m_Setting;        //任务1设置参数
struct PartInfo   t8::m_PartInfo;           //被试者信息

short t8::m_TrialType;						//测试类型
int t8::m_TrialTime;						//测试时间
int t8::m_TrialTimes = 1;						//测试次数
int t8::iTskCnt = 0;						//实验中或者练习的次数统计
int t8::iTotalTskCnt = 0;					//实验总试次

int t8::m_TrialGroups = 0;
int t8::x_resolution = 1024;			//屏幕分辨率
int t8::y_resolution = 768;             //屏幕分辨率
int t8::x_resolution1024 = 1024;
int t8::y_resolution768 = 768;
int t8::rec_x_begin = (t8::x_resolution - t8::x_resolution1024) / 2;
int t8::rec_y_begin = (t8::y_resolution - t8::y_resolution768) / 2;
int t8::rec_x_end = (t8::x_resolution + t8::x_resolution1024) / 2;
int t8::rec_y_end = (t8::y_resolution + t8::y_resolution768) / 2;

const float t8::FontScale = (float)(t8::x_resolution + t8::y_resolution) / 1400.0;    //字体随屏幕分辨率的放缩尺度

const char t8::Insturction1[] = "    屏幕上的白色“⊥”是目标，黄色\
“⊥”是追踪环。您的任务是：使用操纵杆来控制追踪环的运动，尽可能用追\
踪环套住目标。追踪环套住目标时，追踪环会变成红色。按X键开始任务。”双\
手追踪追踪任务的指导语为“屏幕上的白色“⊥”是目标，黄色“⊥”是追\
踪环。您的任务是：使用操纵杆来控制追踪环的运动，尽可能用追踪环套住目\
标。同时，使用旋钮控制追踪环的姿态，尽可能保持追踪环的姿态与目标一致。\
追踪环套住目标时，追踪环会变成红色。按X键开始任务。";
const char t8::Insturction2[] = "该任务完成，按任意键继续！";
const char t8::Insturction3[] = "练习结束，按任意键进入正式实验。";
const char t8::Insturction4[] = "该任务完成，按任意键继续！";
LPDIRECT3D9             t8::g_pD3D = NULL;		    //directx3d对象
LPDIRECT3DDEVICE9       t8::g_pd3dDevice = NULL;		    //directx设备对象
LPDIRECT3DTEXTURE9      t8::g_pTextureInst = NULL;	        //纹理对象
 LPDIRECT3DTEXTURE9      t8::g_1x15a = NULL;
 LPDIRECT3DTEXTURE9      t8::g_1x15b = NULL;
 LPDIRECT3DTEXTURE9      t8::g_1x75a = NULL;
 LPDIRECT3DTEXTURE9      t8::g_1x75b = NULL;
 LPDIRECT3DTEXTURE9      t8::g_1x135a = NULL;
 LPDIRECT3DTEXTURE9      t8::g_1x135b = NULL;
 LPDIRECT3DTEXTURE9      t8::g_1x195a = NULL;
 LPDIRECT3DTEXTURE9      t8::g_1x195b = NULL;
 LPDIRECT3DTEXTURE9      t8::g_1z15a = NULL;
 LPDIRECT3DTEXTURE9      t8::g_1z15b = NULL;
 LPDIRECT3DTEXTURE9      t8::g_1z75a = NULL;
 LPDIRECT3DTEXTURE9      t8::g_1z75b = NULL;
 LPDIRECT3DTEXTURE9      t8::g_1z135a = NULL;
 LPDIRECT3DTEXTURE9      t8::g_1z135b = NULL;
 LPDIRECT3DTEXTURE9      t8::g_1z195a = NULL;
 LPDIRECT3DTEXTURE9      t8::g_1z195b = NULL;
 LPDIRECT3DTEXTURE9      t8::g_8x15a = NULL;
 LPDIRECT3DTEXTURE9      t8::g_8x15b = NULL;
 LPDIRECT3DTEXTURE9      t8::g_8x75a = NULL;
 LPDIRECT3DTEXTURE9      t8::g_8x75b = NULL;
 LPDIRECT3DTEXTURE9      t8::g_8x135a = NULL;
 LPDIRECT3DTEXTURE9      t8::g_8x135b = NULL;
 LPDIRECT3DTEXTURE9      t8::g_8x195a = NULL;
 LPDIRECT3DTEXTURE9      t8::g_8x195b = NULL;
 LPDIRECT3DTEXTURE9      t8::g_8z15a = NULL;
 LPDIRECT3DTEXTURE9      t8::g_8z15b = NULL;
 LPDIRECT3DTEXTURE9      t8::g_8z75a = NULL;
 LPDIRECT3DTEXTURE9      t8::g_8z75b = NULL;
 LPDIRECT3DTEXTURE9      t8::g_8z135a = NULL;
 LPDIRECT3DTEXTURE9      t8::g_8z135b = NULL;
 LPDIRECT3DTEXTURE9      t8::g_8z195a = NULL;
 LPDIRECT3DTEXTURE9      t8::g_8z195b = NULL;
 LPDIRECT3DTEXTURE9      t8::g_9x15a = NULL;
 LPDIRECT3DTEXTURE9      t8::g_9x15b = NULL;
 LPDIRECT3DTEXTURE9      t8::g_9x75a = NULL;
 LPDIRECT3DTEXTURE9      t8::g_9x75b = NULL;
 LPDIRECT3DTEXTURE9      t8::g_9x135a = NULL;
 LPDIRECT3DTEXTURE9      t8::g_9x135b = NULL;
 LPDIRECT3DTEXTURE9      t8::g_9x195a = NULL;
 LPDIRECT3DTEXTURE9      t8::g_9x195b = NULL;
 LPDIRECT3DTEXTURE9      t8::g_9z15a = NULL;
 LPDIRECT3DTEXTURE9      t8::g_9z15b = NULL;
 LPDIRECT3DTEXTURE9      t8::g_9z75a = NULL;
 LPDIRECT3DTEXTURE9      t8::g_9z75b = NULL;
 LPDIRECT3DTEXTURE9      t8::g_9z135a = NULL;
 LPDIRECT3DTEXTURE9      t8::g_9z135b = NULL;
 LPDIRECT3DTEXTURE9      t8::g_9z195a = NULL;
 LPDIRECT3DTEXTURE9      t8::g_9z195b = NULL;
 LPDIRECT3DTEXTURE9      t8::g_cross = NULL;
 LPDIRECT3DTEXTURE9      t8::g_none_f = NULL;
 LPDIRECT3DTEXTURE9      t8::g_none_j = NULL;
 LPDIRECT3DTEXTURE9      t8::g_right_f = NULL;
 LPDIRECT3DTEXTURE9      t8::g_right_j = NULL;
 LPDIRECT3DTEXTURE9      t8::g_wrong_f = NULL;
 LPDIRECT3DTEXTURE9      t8::g_wrong_j = NULL;

LPD3DXSPRITE            t8::g_pSprite = NULL;              //精灵对象
LPD3DXFONT              t8::g_pFont = 0;               //字体对象
LPD3DXFONT              t8::g_pFont1 = 0;				//字体对象
LPDIRECT3DVERTEXBUFFER9      t8::m_pVertexBuffer = NULL;	//顶点对象

D3DXMATRIX t8::m_Transform;                                 //坐标变换矩阵
float t8::TimeInt;                                          //时间间隔
short t8::m_TrialNo;                                        //测试次数序号
BOOL t8::m_bDisplayReady;                                   //渲染设备就绪标志



															//const double dfTim = 0.05;                          //采样间隔50ms
double t8::m_SampleInt;

UINT t8::m_PointNum;
UINT t8::m_MemNum;

RECT t8::strurect, t8::lerect, t8::rerect, t8::erect, t8::txtrect;

short t8::m_TestState;
char t8::m_file[220];
char t8::m_file1[220];
HWND t8::hWnd;
char t8::m_TesterName[40];
char t8::m_DataName[60];
char t8::m_TaskNumStr[100];

//Timer
LARGE_INTEGER t8::litmp;
LONGLONG t8::QPart1, t8::QPart2, t8::QPart3;
double t8::dfMinus, t8::dfMinus1, t8::dfFreq, t8::dfTim, t8::dfdetTim, t8::dfInterval, t8::dfTotalMove;
BOOL t8::bXdown, t8::bZdown;



//************************************************
//*读取当前任务设置
//************************************************
BOOL t8::ReadSetting()
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

			fscanf(fp,"PointTime\t%d\n",&m_Setting.m_iPointTime);
			fscanf(fp, "ViewTime\t%d\n", &m_Setting.m_iViewTime);
			fscanf(fp, "LastTime\t%d\n", &m_Setting.m_iLastTime);

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
//*创建结果数据记录文件
//************************************************
VOID t8::SaveName()
{
	FILE *fp;
	char m_DataDir[60];
	char m_filename[160];
	SYSTEMTIME CurTime;
	GetLocalTime(&CurTime);
	if (strlen(m_DataName) == 0)
	{
		sprintf(m_filename, "t8-%d%02d%02d%02d%02d%02d.txt", CurTime.wYear, CurTime.wMonth, CurTime.wDay, CurTime.wHour, CurTime.wMinute, CurTime.wSecond);
	}
	else
	{
		sprintf(m_filename, "t8-%s-%s-%d%02d%02d%02d%02d%02d.txt", m_TaskNumStr, m_DataName, CurTime.wYear, CurTime.wMonth, CurTime.wDay, CurTime.wHour, CurTime.wMinute, CurTime.wSecond);
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

	//写入文件
	fp = fopen(m_file, "at");

	fprintf(fp, "序号\t左侧图片\t右侧图片\t能否重合\t按键情况\t是否正确\t反应时间\n");

	fclose(fp);




}

//************************************************
//*保存结果数据记录文件
//************************************************
VOID t8::SaveData()
{
	FILE* fp = fopen(m_file, "at");

	if (!bTimeOut) {

	}
	else {

	}

	fclose(fp);
}

//************************************************
//*初始化DirectX 3D
//************************************************
HRESULT t8::InitD3D(HWND hWnd)
{
	m_TestState = STATE_DISPLAYINSTURCTION;
	m_TrialNo = -1;

	//材质大小
	SetRect(&strurect, x_resolution / 2 - 300 * FontScale, y_resolution / 2 - 180 * FontScale, x_resolution / 2 + 300 * FontScale, y_resolution / 2 + 20 * FontScale);
	SetRect(&erect, x_resolution / 2 - 500 * FontScale, y_resolution / 2 - 100 * FontScale, x_resolution / 2 + 500 * FontScale + 50, y_resolution / 2 + 100 * FontScale);
	SetRect(&txtrect, x_resolution / 2 - 100 * FontScale - 50, y_resolution / 2 - 30 * FontScale - 200, x_resolution / 2 + 100 * FontScale + 50, y_resolution / 2 + 30 * FontScale - 200);
	SetRect(&lerect, x_resolution / 2 - 250 * FontScale, y_resolution / 2 - 50 * FontScale, x_resolution / 2 - 50 * FontScale, y_resolution / 2 + 100 * FontScale);
	SetRect(&rerect, x_resolution / 2 + 50 * FontScale, y_resolution / 2 - 50 * FontScale, x_resolution / 2 + 250 * FontScale, y_resolution / 2 + 100 * FontScale);

	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		return E_FAIL;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;//FALSE;//
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;//D3DSWAPEFFECT_FLIP;//D3DSWAPEFFECT_COPY;//

	D3DDISPLAYMODE d3ddm;
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	d3dpp.BackBufferWidth = x_resolution;//d3ddm.Width;//
	d3dpp.BackBufferHeight = y_resolution;//d3ddm.Height;//
	d3dpp.BackBufferFormat = d3ddm.Format;
	//	d3dpp.BackBufferCount =1;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice)))
	{
		return E_FAIL;
	}

	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);


	//创建精灵D3DXCreateSprite函数用来创建与一个特定D3D设备相关联的精灵对象。Sprite对象用于绘制二维图像到屏幕。
	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &g_pSprite)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\ST_3D.jpg"), &g_pTextureInst)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\1_x_15_a.jpg"), &g_1x15a)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\1_x_15_b.jpg"), &g_1x15b)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\1_x_75_a.jpg"), &g_1x75a)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}
	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\1_x_75_b.jpg"), &g_1x75b)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}
	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\1_x_135_a.jpg"), &g_1x135a)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\1_x_135_b.jpg"), &g_1x135b)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\1_x_195_a.jpg"), &g_1x195a)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\1_x_195_b.jpg"), &g_1x195b)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}
	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\1_z_15_a.jpg"), &g_1z15a)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\1_z_15_b.jpg"), &g_1z15b)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\1_z_75_a.jpg"), &g_1z75a)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}
	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\1_z_75_b.jpg"), &g_1z75b)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}
	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\1_z_135_a.jpg"), &g_1z135a)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\1_z_135_b.jpg"), &g_1z135b)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\1_z_195_a.jpg"), &g_1z195a)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\1_z_195_b.jpg"), &g_1z195b)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\8_x_15_a.jpg"), &g_8x15a)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\8_x_15_b.jpg"), &g_8x15b)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\8_x_75_a.jpg"), &g_8x75a)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}
	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\8_x_75_b.jpg"), &g_8x75b)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}
	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\8_x_135_a.jpg"), &g_8x135a)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\8_x_135_b.jpg"), &g_8x135b)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\8_x_195_a.jpg"), &g_8x195a)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\8_x_195_b.jpg"), &g_8x195b)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\8_z_15_a.jpg"), &g_8z15a)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\8_z_15_b.jpg"), &g_8z15b)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\8_z_75_a.jpg"), &g_8z75a)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}
	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\8_z_75_b.jpg"), &g_8z75b)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}
	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\8_z_135_a.jpg"), &g_8z135a)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\8_z_135_b.jpg"), &g_8z135b)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\8_z_195_a.jpg"), &g_8z195a)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\8_z_195_b.jpg"), &g_8z195b)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\9_x_15_a.jpg"), &g_9x15a)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\9_x_15_b.jpg"), &g_9x15b)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\9_x_75_a.jpg"), &g_9x75a)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}
	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\9_x_75_b.jpg"), &g_9x75b)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}
	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\9_x_135_a.jpg"), &g_9x135a)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\9_x_135_b.jpg"), &g_9x135b)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\9_x_195_a.jpg"), &g_9x195a)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\9_x_195_b.jpg"), &g_9x195b)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\9_z_15_a.jpg"), &g_9z15a)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\9_z_15_b.jpg"), &g_9z15b)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\9_z_75_a.jpg"), &g_9z75a)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}
	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\9_z_75_b.jpg"), &g_9z75b)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}
	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\9_z_135_a.jpg"), &g_9z135a)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\9_z_135_b.jpg"), &g_9z135b)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\9_z_195_a.jpg"), &g_9z195a)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\9_z_195_b.jpg"), &g_9z195b)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}


	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\cross.jpg"), &g_cross)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\none_f.jpg"), &g_none_f)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\none_j.jpg"), &g_none_j)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\right_f.jpg"), &g_right_f)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\right_j.jpg"), &g_right_j)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}
	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\wrong_f.jpg"), &g_wrong_f)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, TEXT("Pics\\TaskR\\wrong_j.jpg"), &g_wrong_j)))
	{
		MessageBox(NULL, TEXT("Could not find banana.bmp"), TEXT("Textures.exe"), MB_OK);
		return E_FAIL;
	}



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

	m_bDisplayReady = TRUE;
	SaveName();
	TestInit();
	return S_OK;
}

//************************************************
//*释放数组内存
//************************************************
VOID t8::CleanupMem()
{

}

//************************************************
//*释放DirectX对象
//************************************************
VOID t8::Cleanup()
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
VOID t8::Render()
{
	switch (m_TestState)
	{
		//呈现指导语
	case STATE_DISPLAYINSTURCTION:
		//		g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255,255,255), 0.0f, 0 );
		//		break;
		//任务执行过程
		t8::preKeyPress = -1;
	case STATE_DISPLAYOBJ:
	case STATE_MOVINGOBJ:
	case STATE_DISPLAYNEXT:
	case STATE_DISPLAYOPTION:
	case STATE_OVER:

		g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 0.0f, 0);


		break;
	}
	D3DXMATRIX mx;

	//在后台缓冲区绘制图形
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		//g_pd3dDevice->SetStreamSource( 0, m_pVertexBuffer, 0, sizeof(CUSTOMVERTEX) );
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

			}
			g_pSprite->End();
			break;
			//呈现目标
		case STATE_DISPLAYOBJ:
		case STATE_MOVINGOBJ:

			g_pSprite->End();
			break;
			//进行下次测试
		case STATE_DISPLAYFEEDBACK:
			g_pFont->DrawText(NULL, szFeedBack, -1, &txtrect,
				DT_WORDBREAK | DT_NOCLIP | DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(255, 255, 255));


			g_pSprite->End();

			break;
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
VOID t8::TestInit()
{

	//Cleanup();
	//CleanupMem();

	//t8::preKeyPress = -1; //记录上一次手柄按键
	//t8::iShowState = t8::BALL_INTERVAL;;
	//t8::bBtnDown = TRUE;
	//t8::bShowSmallBall = TRUE;
	//t8::dBallSpeed = 0;//小球速度
	//t8::bBtnStatus = BTN_UP;//按键状态
	//t8::iTotalTskCnt = 0;					//实验总试次


	//g_nThreadExitCount = 0;

	dfTotalMove = 0;


}

int t8::GetKeyZAxis(void)
{
	if (bZdown)
	{
		bZdown = FALSE;
		return -1000;
	}
	else if (bXdown)
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
LRESULT WINAPI t8::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch (msg)
	{
	case WM_KEYUP:
		switch (wParam)
		{
			//退出键
		case VK_ESCAPE:
			// User wants to leave fullscreen mode
			/*
			PostThreadMessage(dwInputThreadID, WM_THREADSTOP,0,0);
			m_TestState = STATE_EXIT;
			break;
			*/
			//ShowCursor(TRUE);
			ShowCursor(TRUE);
			rtn = DialogBox(gHinstance, MAKEINTRESOURCE(IDD_PAUSE), hWnd, t8::PauseMsgProc);
			ShowCursor(FALSE);
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
				Sleep(10);
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

	case WM_DESTROY:
		CleanupMem();
		Cleanup();
		PostQuitMessage(0);
		m_bDisplayReady = FALSE;
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void t8::GoToFeedBack()
{
	
	if (!bTimeOut)
	{

	}
	else
		sprintf(szFeedBack, "反应超时！");

	bTimeOut = FALSE;
	m_TestState = STATE_DISPLAYFEEDBACK;
	QueryPerformanceCounter(&litmp);
	QPart1 = litmp.QuadPart;         //获得中止值
}
void t8::TaskOver()
{
	iTotalTskCnt++;
	iTskCnt++;
	SaveData();


	if (iTskCnt == m_TrialTimes)
	{


		if (m_TrialType == TRIAL_PRACTICE)
		{

			GoToFeedBack();

		}
		else
		{

			m_TestState = STATE_OVER;

		}

	}
	else
	{
		if (m_TrialType == TRIAL_PRACTICE)
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
VOID t8::UpdateState()
{
	switch (m_TestState)
	{
		//呈现指导语
	case STATE_DISPLAYINSTURCTION:
		break;
		//呈现目标
	case STATE_DISPLAYOBJ:


		if (QueryPerformanceFrequency(&litmp))
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





		
		
		bShowSmallBall = TRUE;
		m_TestState = STATE_MOVINGOBJ;
		iShowState = BALL_INTERVAL;
		break;
		//测试任务执行
	case STATE_MOVINGOBJ:
	{
		//间隔50ms采样一次
		do
		{
			Sleep(1);
			QueryPerformanceCounter(&litmp);
			QPart2 = litmp.QuadPart;         //获得中止值
			dfMinus = (double)(QPart2 - QPart1);
		} while (dfMinus < m_SampleInt);//dfTim);//			
		dfTim = dfMinus / dfFreq;  // 获得对应的时间值，单位为秒
		QPart1 = QPart2;           // 获得初始值



		if (iShowState != BALL_INTERVAL)
		{
			
		}



		switch (iShowState)
		{
		case BALL_INTERVAL:

			break;

		case BALL_SHOW:

			//这里注意 stPntSmallBall只是图片的坐标
			dfTotalMove = dfTotalMove + dfTim;

			//超时设置

			if (1==1)
			{
				bTimeOut = TRUE;
				dfTotalMove = 0;
				TaskOver();
			}


			break;


		}


		break;
	}
	case STATE_DISPLAYFEEDBACK:
		QueryPerformanceCounter(&litmp);
		QPart2 = litmp.QuadPart;         //获得中止值
		dfMinus = (double)(QPart2 - QPart1);
		dfTim = dfMinus / dfFreq;        // 获得对应的时间值，单位为秒	
		QPart1 = QPart2;
		dfTotalMove = dfTotalMove + dfTim;

		if (dfTotalMove > 3)
		{
			dfTotalMove = 0;

			if (iTskCnt == 64)
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
			SendMessage(hWnd, WM_CLOSE, 0, 0); // 关闭窗口
			SendMessage(hWnd, WM_DESTROY, 0, 0);
		}
		break;
	default:
		break;
	}
}



//************************************************
//*主程序
//************************************************
int APIENTRY t8::_tWinMain(HINSTANCE &hInstance, HINSTANCE &hPrevInstance, LPTSTR &lpCmdLine, int &nCmdShow, HWND &_hWnd, std::string winClassName, std::string winName)
{
	// TODO: Place code here.
	//获得传递的命令行参数，得到被试着名字和任务编号
	//任务7-速度知觉 1-1-0
	t8::rtn = 0;
	t8::preKeyPress = -1; //记录上一次手柄按键
	t8::bTimeOut = FALSE;
	t8::iShowState = t8::BALL_INTERVAL;
	t8::bShowSmallBall = TRUE;
	t8::iReactTime = 0;
	t8::bBtnStatus = BTN_UP;//按键状态
	t8::iTskCnt = 0;						//实验中或者练习的次数统计
	t8::iTotalTskCnt = 0;					//实验总试次
	t8::bBtnDown = TRUE;
	g_nThreadExitCount = 0;             //当前运行的线程数
	dwInputThreadID = 0;              //瞄准器输入线程ID 
	preKeyPress = -1; //记录上一次手柄按键
	t8::m_TrialGroups = 0;
	m_TestState = STATE_DISPLAYINSTURCTION;
	// 任务次数初始化
	iTskCnt = 0;

	// 初始化句柄和状态
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

	int nFullWidth = GetSystemMetrics(SM_CXSCREEN);
	int nFullHeight = GetSystemMetrics(SM_CYSCREEN);

	//创建窗口
	_hWnd = hWnd = CreateWindow(std::to_string(nCmdShow).c_str(), std::to_string(nCmdShow).c_str(),
		WS_VISIBLE | WS_POPUP, 0, 0, nFullWidth, nFullHeight,
		NULL, NULL, wc.hInstance, NULL);

	//显示主窗口
	SetFocus(hWnd);
	//ShowCursor(FALSE);

	x_resolution = nFullWidth;
	y_resolution = nFullHeight;

	if (m_lpkDInput)
	{
		m_lpkDInput->Release();
	}
	if (m_lpkDIDevice)
	{
		m_lpkDIDevice->Release();

	}
	//创建DirectX设备
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&m_lpkDInput, NULL)))
	{
		return 0;
	}


	//关闭输入法
	HKL hkl;
	hkl = LoadKeyboardLayout("00000804", KLF_ACTIVATE);
	if (hkl != NULL)
	{
		ActivateKeyboardLayout(hkl, KLF_SETFORPROCESS);
	}
	//ShowCursor(FALSE);    

	m_bDisplayReady = FALSE;
	// declare a variable of our data structure to pass to the ThreadProcedure
	MYDATA MyThreadData;
	MyThreadData.nTime = 7509843;
	MyThreadData.nNumber = 39;

	srand((unsigned)time(NULL)); //初始化随机种子 

								 //初始化Direct3D
	if (SUCCEEDED(InitD3D(hWnd)))
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



	return rtn;
}

void t8::hideLastWindow(bool &bUnClosedLastWin, std::string &winClassName, std::string &winName, HINSTANCE &hInstance)
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

//暂停对话框消息循环
BOOL CALLBACK t8::PauseMsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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
