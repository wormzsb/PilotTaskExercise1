
#include "stdafx.h"
#include "Task8.h"
#include <iostream>
using namespace std;

// 反馈时候用到的纹理
LPDIRECT3DTEXTURE9 texCross = NULL, texRightF = NULL, texWrongF = NULL, texNoneF = NULL,
texRightJ = NULL, texWrongJ = NULL, texNoneJ = NULL;
LPDIRECT3DTEXTURE9      t8::texInst = NULL;            //纹理对象


// 状态控制
bool isCountdownStop = false;
int g_imgDisplayInd = -2;
int g_imgLastInd = -1000000;
bool isPressBtn = false;
bool isCoBtn = false;
double pauseTime;
int m_taskIndex;
int lastState = -1;
vector <string> LImgs, RImgs;

struct tagREC {
	bool mode; // 0: exercise; 1: formal
	int no;
	string leftImg;
	string rightImg;
	bool unCoincidence; // 0:重合 1：不能重合
	int btn;			//0：重合 1：不重合 -1：超时
	bool isRight;		// 0: 错误 1：正确
	double responseTime;	// 单位毫秒
};
typedef tagREC Rec;

vector<Rec>  recs;

LARGE_INTEGER freq;
LARGE_INTEGER begTime;
LARGE_INTEGER endTime;

bool bTimerExist = false;
thread timerThread;

string picDir = "./Pics/TaskR/";

int t8::rtn;
HINSTANCE t8::gHinstance;
float t8::acce;//加速度
int	t8::iDirection = 0;
int t8::g_nThreadExitCount = 0;                      //当前运行的线程数
DWORD t8::dwInputThreadID = 0;                       //瞄准器输入线程ID
BOOL t8::m_bCubeNum[4];                              //三维图形方块数标志

BOOL t8::m_bAcc;                                     //三维图形记忆正确性标志
double t8::alpha, t8::omiga, t8::v, t8::a, t8::b, t8::r, t8::Rx, t8::Ry, t8::fai, t8::AngleSpeed, t8::inc_v;
double t8::m_PostPointX, t8::m_PostPointY;                //当前瞄准器坐标
int t8::JoyX, t8::JoyY;                                   //当前操纵杆输入值  
struct TaskSetting8   t8::m_Setting;                 //任务6设置参数
struct HardSetting   t8::m_HardSetting;              //硬件设置参数
struct PartInfo   t8::m_PartInfo;                    //被试者信息
short t8::m_TrialType;                               //测试类型
int t8::m_TrialTime;                                 //测试时间
int t8::m_TrialTimes;                                //测试时间
int t8::iJoyMoveDirection;//手柄运动方向正向反向
int t8::x_resolution = 1024;			//屏幕分辨率
int t8::y_resolution = 768;             //屏幕分辨率
int t8::rec_x_begin;
int t8::rec_y_begin;
int t8::rec_x_end;
int t8::rec_y_end;
const float t8::FontScale = (float)(t8::x_resolution + t8::y_resolution) / 1400.0;             //字体随屏幕分辨率的放缩尺度

const char t8::Insturction11[] = "    欢迎进入双任务三维\
图形记忆判别任务！请使用右手控制操纵杆追踪屏幕上的“⊥”。同时请注意\
屏幕中央呈现的图符，你需要记住这些图符。X秒后，屏幕中央的这些字符会\
消失。然后屏幕中央面依次出现一系列图符，每次出现一个，请判断这些图符\
是否为你记住的那些图符。";
const char t8::Insturction12[] = "    欢迎进入双任\
务记忆判别测试！请使用右手控制操纵杆追踪屏幕上的“⊥”。同时请注意屏\
幕中央呈现的图符，你需要记住这些图符。X秒后，屏幕中央的这些字符会消\
失。然后屏幕中央面依次出现一系列图符，每次出现一个，请判断这些图符是\
否为你记住的那些图符。";
const char t8::Insturction13[] = "请记住上面的图符，\n按“是”键开始测试。";
const char t8::Insturction2[] = "练习结束，按任意键进入正式实验。";
const char t8::Insturction3[] = "该任务完成，按任意键继续！";
const char t8::FeedBack[2][10] = { "错误","正确" };

LPDIRECT3D9             t8::g_pD3D = NULL;               //directx3d对象
LPDIRECT3DDEVICE9       t8::g_pd3dDevice = NULL;               //directx设备对象

LPDIRECT3DTEXTURE9      t8::g_pTexture0 = NULL;               //纹理对象
LPDIRECT3DTEXTURE9      t8::g_pTexture1 = NULL;               //纹理对象
LPDIRECT3DTEXTURE9      t8::g_pTexture2 = NULL;               //纹理对象
LPDIRECT3DTEXTURE9      t8::g_pTexture3[12] = { NULL };         //纹理对象
LPDIRECT3DTEXTURE9      t8::g_pTexture4 = NULL;               //纹理对象

LPD3DXSPRITE            t8::g_pSprite = NULL;                 //精灵对象
LPD3DXFONT              t8::g_pFont = 0;                  //字体对象
LPD3DXFONT              t8::g_pFont1 = 0;                  //字体对象
LPD3DXFONT              t8::g_pFont2 = 0;                  //字体对象
LPDIRECT3DVERTEXBUFFER9      t8::m_pVertexBuffer = NULL;


LPDIRECT3DTEXTURE9 texLeft, texRight;

D3DXMATRIX t8::m_Transform;                          //坐标变换矩阵
float t8::TimeInt;
short t8::m_SignNo;                                  //三维图形记忆序号
short t8::m_SignOrderNo1, t8::m_SignOrderNo2;            //三维图形记忆系列序号
short t8::m_SignTrialNo;                             //三维图形记忆次数号
short t8::m_SignGroupNo;                             //三维图形记忆组号
short t8::m_SignCount;                               //三维图形记忆数目
BOOL t8::m_bShowMem;                                 //待记忆三维图形文件显示标志
BOOL t8::m_bLoadSign;                                //三维图形文件加载标志
BOOL t8::m_bDisplayReady;

BOOL t8::m_bHideSign = FALSE;						  //在等待时间隐藏三维图形
BOOL t8::m_bRememStart;                               //三维图形记忆开始标志      
BOOL t8::m_bSignStart;                                //三维图形显示标志
short t8::m_SureDownNum;
int t8::m_SignType[12];                               //三维图形类型
int t8::m_SignOrder1[6];                              //三维图形序列
int t8::m_SignOrder2[6];                              //三维图形序列
unsigned long t8::m_SignStartTime[12];                //三维图形记忆开始时间
unsigned long t8::m_SignSureTime[12];                 //三维图形记忆确认时间
char t8::m_LMemName[30];                              //存放待记忆三维图形名称的数组
char t8::m_RMemName[12][30];                          //存放记忆三维图形名称的数组
short t8::m_LMemAngle;                                //存放待记忆三维图形旋转角度的数组
short t8::m_RMemAngle[12];                            //存放记忆三维图形旋转角度的数组
short t8::m_MemAngleDiff[12];                         //存放两边三维图形旋转角度差的数组
short t8::m_NoSame[12];                               //存放三维图形相同性的数组
short t8::m_SureButtonNo[12];                         //存放确认按键的数组
short t8::m_ButtonDownNum;

int t8::m_CubeNum;

const double t8::m_MoveInt = 0.04;                    //采样间隔40ms

UINT t8::m_PointNum;
UINT t8::m_MemNum;
BOOL *t8::m_bHit = NULL;                               //存放击中状态的数组
SPOINT *t8::m_ObjPoint = NULL;                         //存放目标坐标的数组
SPOINT *t8::m_PostPoint = NULL;                        //存放瞄准器坐标的数组
float *t8::m_Distance = NULL;                          //存放目标和瞄准器距离的数组
unsigned long *t8::m_PointTime = NULL;                 //存放采样时间的数组
float *t8::m_ObjSpeedX = NULL;                         //存放目标速度的数组
float *t8::m_ObjSpeedY = NULL;                         //存放目标速度的数组
float *t8::m_PostSpeedX = NULL;                        //存放瞄准器速度的数组
float *t8::m_PostSpeedY = NULL;                        //存放瞄准器速度的数组
RECT t8::strurect, t8::lerect, t8::rerect, t8::erect, t8::txtrect, t8::coderect, t8::charrect[8];
D3DRECT t8::SignRect;

short t8::m_TestState;
char t8::m_file1[220];
char t8::szDataFile[220];
HWND t8::hWnd;
char t8::m_TesterName[40];
char t8::m_DataName[60];
char t8::m_TaskNumStr[100];

//Timer
LARGE_INTEGER t8::litmp;
LONGLONG t8::QPart1, t8::QPart2, t8::QPart3, t8::QPart4;
double t8::dfMinus, t8::dfFreq, t8::dfTim, t8::dfTotalPause, t8::dfTotalMove, t8::dfTotalSign;

bool t8::bShowTime = false;
int t8::countdown;




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
	char m_tasknostr[120];
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
			//Task6
			//		fscanf(fp,"[Task6]\n");
			//fscanf(fp,"TaskName\t%s\n",m_Setting.m_TaskName);
			//fscanf(fp, "PracMode\t%d\n", &m_Setting.m_bPracMode);
			fscanf(fp, "PresentTime\t%d\n", &m_Setting.m_iPresentTime);
			fscanf(fp, "FocusTime\t%d\n", &m_Setting.m_iFocusTime);
			fscanf(fp, "CountdownTime\t%d\n", &m_Setting.m_iCountdownTime);
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
VOID t8::SaveName()
{
	FILE *fp;
	char m_DataDir[60];
	char m_filename1[160];
	char m_filename2[160];
	char szTime[160];

	SYSTEMTIME CurTime;
	GetLocalTime(&CurTime);
	sprintf(szTime, "%d%02d%02d%02d%02d%02d",
		CurTime.wYear, CurTime.wMonth, CurTime.wDay, 
		CurTime.wHour, CurTime.wMinute, CurTime.wSecond);
	stringstream ss;
	if (strlen(m_DataName) == 0)
	{
	}
	else
	{
		ss << "T8-"
			<< m_taskIndex
			<< "-任务8-三维心理旋转测试-"
			<< m_PartInfo.m_TesterNo
			<< "-"
			<< m_PartInfo.m_TesterName
			<< "-"
			<< m_PartInfo.m_Session
			<< "-"
			<< szTime
			<< ".txt";
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
	//sprintf(m_file1, "%s\\%s", m_DataDir, m_filename1);
	sprintf(szDataFile, "%s\\%s", m_DataDir, ss.str());

	// 保存文件头
	ofstream out(szDataFile);
	if (!out.is_open()) 
		MessageBox(hWnd, "数据文件不能创建或打开", "错误", NULL);
	out << "序号\t左侧图片\t右侧图片\t能否重合\t按键情况\t是否正确\t反应时\n";
	out.close();
}



//************************************************
//*保存结果数据记录文件
//************************************************
VOID t8::SaveData()
{
	FILE *fp;
	int i;
	fp = fopen(szDataFile, "at");
	for (i = 0; i < recs.size(); i++)
	{
		fprintf(fp, "%d\t%s\t%s\t%d\t%d\t%d\t%.2f\t\n",
			recs[i].no, recs[i].leftImg, recs[i].rightImg, recs[i].unCoincidence, recs[i].btn, recs[i].isRight, recs[i].responseTime);
	}
	fclose(fp);
}


//************************************************
//*加载三维图形文件
//************************************************
HRESULT t8::LoadSignFile()
{
	
	return TRUE;
}

//************************************************
//*测试任务初始化
//************************************************
VOID t8::TestInit()
{

}

unsigned t8::addTex(LPDIRECT3DDEVICE9 & dev, string fileName, LPDIRECT3DTEXTURE9 &tex) {
	if (FAILED(D3DXCreateTextureFromFile(dev, fileName.c_str(), &tex)))
	{
		MessageBox(NULL, (fileName + "文件不存在").c_str(), "添加纹理", MB_OK);
		return E_FAIL;
	}
}

//************************************************
//*初始化DirectX 3D
//************************************************
HRESULT t8::InitD3D(HWND hWnd)
{
	m_TestState = STATE_DISPLAYINSTURCTION;
	m_bDisplayReady = TRUE;
	m_SignGroupNo = -1;
	m_SureDownNum = 0;
	m_CubeNum = 9;
	

	//材质大小
	//	SetRect( &rct, 0, 0, 128, 128 );
	SetRect(&strurect, x_resolution / 2 - 300 * FontScale, y_resolution / 2 + 100 * FontScale, x_resolution / 2 + 300 * FontScale, y_resolution / 2 + 140 * FontScale);
	SetRect(&erect, x_resolution / 2 - 300 * FontScale, y_resolution / 2 - 100 * FontScale, x_resolution / 2 + 300 * FontScale, y_resolution / 2 + 100 * FontScale);
	SetRect(&txtrect, 0, 0, x_resolution / 4, y_resolution / 8);
	SetRect(&coderect, x_resolution / 4, y_resolution / 8, x_resolution * 3 / 4, y_resolution / 4);
	SetRect(&lerect, x_resolution / 2 - 250 * FontScale, y_resolution / 2 - 50 * FontScale, x_resolution / 2 - 50 * FontScale, y_resolution / 2 + 100 * FontScale);
	SetRect(&rerect, x_resolution / 2 + 50 * FontScale, y_resolution / 2 - 50 * FontScale, x_resolution / 2 + 250 * FontScale, y_resolution / 2 + 100 * FontScale);
	SignRect.x1 = x_resolution / 2 - 128;
	SignRect.y1 = y_resolution / 2 - 128;
	SignRect.x2 = x_resolution / 2 + 128;
	SignRect.y2 = y_resolution / 2 + 128;


	//		SetRect( &charrect[i], x_resolution/3+x_resolution/12*i, y_resolution/3, x_resolution/3+x_resolution/12*(i+1), y_resolution/3+y_resolution/6);

	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		return E_FAIL;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;//FALSE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_COPY;//D3DSWAPEFFECT_DISCARD;
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
		MessageBox(NULL, "Could not find banana.bmp", "Textures.exe", MB_OK);
		return E_FAIL;
	}

	//加载纹理图片
	// 指导语
	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, (picDir+"ST_3D.jpg").c_str(), &texInst)))
	{
		MessageBox(NULL, "Could not find banana.bmp", "Textures.exe", MB_OK);
		return E_FAIL;		
	}
	
	addTex(g_pd3dDevice, "./Pics/TaskR/cross.jpg", texCross);
	addTex(g_pd3dDevice, picDir + "right_f.jpg", texRightF);	// 能重合 反应正确
	addTex(g_pd3dDevice, picDir + "wrong_f.jpg", texWrongF);	// 能重合 反应错误
	addTex(g_pd3dDevice, picDir + "none_f.jpg", texNoneF);		// 能重合 反应超时
	addTex(g_pd3dDevice, picDir + "right_j.jpg", texRightJ);	// 不能重合 反应正确
	addTex(g_pd3dDevice, picDir + "wrong_j.jpg", texWrongJ);	// 不能重合 反应错误
	addTex(g_pd3dDevice, picDir + "none_j.jpg", texNoneJ);		// 不能重合 反应超时


	LOGFONT lf;
	ZeroMemory(&lf, sizeof(LOGFONT));
	strcpy(lf.lfFaceName, "Times New Roman");
	lf.lfHeight = -16;
	if (FAILED(D3DXCreateFont(g_pd3dDevice, 30 * FontScale, 15 * FontScale, 20,
		0, 0, GB2312_CHARSET, 0, 0, 0, "宋体", &g_pFont)))
	{
		return E_FAIL;
	}
	if (FAILED(D3DXCreateFont(g_pd3dDevice, 40 * FontScale, 20 * FontScale, 20,
		0, 0, GB2312_CHARSET, 0, 0, 0, "宋体", &g_pFont1)))
	{
		return E_FAIL;
	}
	if (FAILED(D3DXCreateFont(g_pd3dDevice, 20 * FontScale, 10 * FontScale, 20,
		0, 0, GB2312_CHARSET, 0, 0, 0, "宋体", &g_pFont2)))
	{
		return E_FAIL;
	}
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	//    g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	g_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	TestInit();
	SaveName();
	return S_OK;
}

//************************************************
//*释放数组内存
//************************************************
VOID t8::CleanupMem()
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
	if (m_PointTime != NULL)
	{
		free(m_PointTime);
		m_PointTime = NULL;
	}
	if (m_Distance != NULL)
	{
		free(m_Distance);
		m_Distance = NULL;
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
}

//************************************************
//*释放DirectX对象
//************************************************
VOID t8::Cleanup()
{
	//释放字体对象
	int i;
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
	if (g_pFont2 != NULL)
	{
		g_pFont2->Release();
		g_pFont2 = NULL;
	}
	if (texInst != NULL)
	{
		texInst->Release();
		texInst = NULL;
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
	for (i = 0; i<12; i++)
	{
		if (g_pTexture3[i] != NULL)
		{
			g_pTexture3[i]->Release();
			g_pTexture3[i] = NULL;
		}
	}

	if (texLeft != NULL)
	{
		texLeft->Release();
		texLeft = NULL;
	}
	if (texRight != NULL)
	{
		texRight->Release();
		texRight = NULL;
	}

	if (texNoneF != NULL)
	{
		texNoneF->Release();
		texNoneF = NULL;
	}
	if (texNoneJ != NULL)
	{
		texNoneJ->Release();
		texNoneJ = NULL;
	}
	if (texRightF != NULL)
	{
		texRightF->Release();
		texRightF = NULL;
	}
	if (texRightJ != NULL)
	{
		texRightJ->Release();
		texRightJ = NULL;
	}
	if (texWrongF != NULL)
	{
		texWrongF->Release();
		texWrongF = NULL;
	}
	if (texWrongJ != NULL)
	{
		texWrongJ->Release();
		texWrongJ = NULL;
	}
	
	if (texCross != NULL)
	{
		texCross->Release();
		texCross = NULL;
	}
	//
	if (g_pTexture4 != NULL)
	{
		g_pTexture4->Release();
		g_pTexture4 = NULL;
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

}

void t8::getScale(double &sx, double &sy, 
	double w, double h,
	double tw, double th,
	int x_resolution, int y_resolution) {
	sx = (double)w / (double)tw;
	sy = (double)h / (double)th;
}

//在指定位置写文字
BOOL t8::drawText( string str, int tx, int ty, LPD3DXFONT &g_pFont) {
	
	RECT rect;
	rect.left = tx - 500;
	rect.top = ty;
	rect.right = tx + 500;
	rect.bottom = ty + 50;

	g_pFont->DrawText(NULL, str.c_str(), -1, &rect,
		DT_WORDBREAK | DT_NOCLIP | DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(255, 255, 255));
		
	return TRUE;
}

//在指定位置和缩放系数画纹理
BOOL t8::drawTex(double tx, double ty, LPD3DXSPRITE &g_pSprite, LPDIRECT3DTEXTURE9 &tex,
	double sx, double sy) {
	D3DXMATRIX mx;
	if (SUCCEEDED(g_pSprite->Begin(D3DXSPRITE_ALPHABLEND))) {
		// 左边
		D3DXMatrixTransformation2D(
			&mx,
			NULL,							// 缩放中心向量
			0.0,							// 缩放旋转角度
			&D3DXVECTOR2(sx, sy),			// 缩放向量
			&D3DXVECTOR2(0, 0),				// 旋转向量
			NULL,							// 旋转角度
			&D3DXVECTOR2(tx,ty)	// 平移向量
			);
		g_pSprite->SetTransform(&mx);
		g_pSprite->Draw(
			tex,
			NULL,							// 纹理源的ROI 
			&D3DXVECTOR3(0, 0, 0),			// 精灵中心 
			&D3DXVECTOR3(0, 0, 0),			// 精灵位置
			0xffffffff						// 修改颜色
			);
		g_pSprite->End();
		return TRUE;
	}
	return FALSE;
}

BOOL t8::drawTex(string mode, LPD3DXSPRITE &g_pSprite,
	LPDIRECT3DTEXTURE9 &tex,
	int x_resolution, int y_resolution) {
	/*int w, h;
	getTexSize(tex, w, h);
	double scale = getScale(x_resolution, y_resolution, w);
	double tx = x_resolution / 2 - scale*w / 2;
	double ty = (y_resolution - scale*h) / 2;
	if (!drawTex(tx, ty, g_pSprite, tex, scale))
		return FALSE;*/
	return drawTex(mode, g_pSprite, tex, tex, x_resolution, y_resolution);
	
}
// 按照模式画纹理
BOOL t8::drawTex(string mode, LPD3DXSPRITE &g_pSprite, 
	LPDIRECT3DTEXTURE9 &ltex, LPDIRECT3DTEXTURE9 &rtex,
	int x_resolution, int y_resolution) {
	
	int w, h;
	double tw, th;
	double tx, ty;
	double sx, sy;
	
	if (mode == "cross") {
		w = 360; h = 360;
		getTexSize(ltex,tw, th);
		getScale(sx, sy, w, h,tw,th, x_resolution, y_resolution);
		tx = (double)x_resolution / 2 - (double)w / 2;
		ty = ((double)y_resolution - h) / 2;
	}
	if (mode == "inst") {
		w = 762; h = 630;
		getTexSize(ltex, tw, th);
		getScale(sx, sy, w, h, tw, th, x_resolution, y_resolution);
		tx = (double)x_resolution / 2 - (double)w / 2;
		ty = ((double)y_resolution - h) / 2;
	}
	if (mode == "feedback") {
		w = 593; h = 82;
		getTexSize(ltex, tw, th);
		getScale(sx, sy, w, h, tw, th, x_resolution, y_resolution);
		tx = (double)x_resolution / 2 - (double)w / 2;
		ty = (double)y_resolution - (double) h ;
	}
	if (mode == "LR") {
		w = 600; h = 600;
		getTexSize(ltex, tw, th);
		getScale(sx, sy, w, h, tw, th, x_resolution, y_resolution);
	}

	
	//double scale = 1.;

	D3DXMATRIX mx;
	// 左右并列
	if (mode == "LR") {
		double tx, ty;
		tx = (double)x_resolution / 2 - w;
		ty = ((double)y_resolution - h) / 2;
		if (!drawTex(tx, ty, g_pSprite, ltex, sx, sy))
			return FALSE;
		tx = (double)x_resolution / 2;
		ty = ((double)y_resolution - h) / 2;
		if (!drawTex(tx, ty, g_pSprite, rtex, sx, sy))
			return FALSE;
	}
	//中间大图
	else if (mode == "cross" 
		|| mode == "feedback" 
		|| mode == "inst") {
		
		if (!drawTex(tx, ty, g_pSprite, ltex, sx, sy))
			return FALSE;
	}
	
	return TRUE;
}

//************************************************
//*渲染
//************************************************
VOID t8::Render()
{
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET,
		D3DCOLOR_XRGB(0, 0, 0), 0.0f, 0);
	// 绘制前景：
	D3DXMATRIX mx;
	//在后台缓冲区绘制图形
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		g_pd3dDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(CUSTOMVERTEX));
		g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
		//      g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
		switch (m_TestState)
		{
			//呈现指导语图片
		case STATE_DISPLAYINSTURCTION:
			//if (SUCCEEDED(g_pSprite->Begin(D3DXSPRITE_ALPHABLEND)))
			//{
				if (!drawTex("inst", g_pSprite, texInst, x_resolution, y_resolution))
					break;
				//D3DXMatrixTransformation2D(&mx, NULL, 0.0, &D3DXVECTOR2((float)1024 / (float)1024, (float)768 / (float)1024), &D3DXVECTOR2(0, 0), NULL, &D3DXVECTOR2(x_resolution / 2, y_resolution / 2));
				//g_pSprite->SetTransform(&mx);
				//g_pSprite->Draw(g_pTextureInst, NULL, &D3DXVECTOR3(512, 512, 0), &D3DXVECTOR3(0, 0, 0), 0xffffffff);
			//}
			//g_pSprite->End();
			break;
		//测试结束
		case STATE_OVER: {
			int sumRight = 0;
			double sumResTime = 0.;
			int cnt = recs.size() - 4;
			for (int i = 4; i < recs.size(); i++) {
				sumRight += (int)recs[i].isRight;
				sumResTime += recs[i].responseTime;
				
			}
			stringstream ss;
			ss.setf(ios::fixed);
			ss << "本次任务"
				<< "平均正确率为" << setprecision(2) << (double)sumRight / cnt * 100. << "%, "
				<< "平均反应时为" << setprecision(0) << sumResTime / cnt << "毫秒";
			int tx = x_resolution / 2;
			int ty = y_resolution  - 50;
			drawText(ss.str(), tx, ty, g_pFont);
			g_pFont1->DrawText(NULL, Insturction3, -1, &erect,
				DT_WORDBREAK | DT_NOCLIP | DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(255, 255, 255));
			break; 
		}
		case STATE_FOCUS_EXERCISE:
		case STATE_FOCUS_FORMAL: 
			// 绘制图片
			if (!drawTex("cross", g_pSprite, texCross, x_resolution, y_resolution))
				break;
			break;
		case STATE_BETWEEN_EXERCISE_AND_FORMAL: {
			// 绘制文字
			int tx = x_resolution / 2;
			int ty = y_resolution/2 - 50;
			stringstream ss;
			ss << "请按空格键进入正式任务" ;
			if (!drawText(ss.str(), tx, ty, g_pFont))
				break;
			break;
		}
		case STATE_DISPLAYFEEDBACK: 
		case STATE_DISPLAY_AND_COUNTDOWN_EXERCISE:
		case STATE_DISPLAY_AND_COUNTDOWN_FORMAL:
		case STATE_EXERCISE:
		case STATE_FORMAL: {
				// 绘制图片
				// 加载纹理
				if (LImgs.size() == 0 
					|| g_imgDisplayInd < 0 
					|| g_imgDisplayInd >= LImgs.size())
					break;
				if (g_imgLastInd != g_imgDisplayInd) {
					string lImg = picDir + LImgs[g_imgDisplayInd];
					string rImg = picDir + RImgs[g_imgDisplayInd];
					if (m_TestState == STATE_DISPLAYFEEDBACK) {
						lImg = picDir + LImgs[g_imgDisplayInd-1];
						rImg = picDir + LImgs[g_imgDisplayInd-1];
					}
					addTex(g_pd3dDevice, lImg.c_str(), texLeft);
					addTex(g_pd3dDevice, rImg.c_str(), texRight);
					g_imgLastInd = g_imgDisplayInd;
				}
				if (!drawTex("LR", g_pSprite, texLeft, texRight, x_resolution, y_resolution))
					break;
				
				if (bShowTime) {
					// 绘制文字
					int tx = x_resolution / 2;
					int ty = y_resolution - 50;
					stringstream ss;
					ss << "还剩" << countdown/1000 << "秒"/* << g_imgDisplayInd*/;
					if (!drawText(ss.str(), tx, ty, g_pFont))
						break;
				}

				// 下面是反馈时候显示反馈的图像
				if (m_TestState == STATE_DISPLAYFEEDBACK) {
					
					LPDIRECT3DTEXTURE9 texFeedBack = NULL;
					bool unCo = recs.rbegin()->unCoincidence;
					int iBtn = recs.rbegin()->btn;
					bool isRight = recs.rbegin()->isRight;

					if (!unCo && iBtn == -1)
						texFeedBack = texNoneF;			// 重合 & 超时
					if (!unCo  && iBtn != -1 && isRight)
						texFeedBack = texRightF;		// 重合 & 正确
					if (!unCo  && iBtn != -1 && !isRight)
						texFeedBack = texWrongF;		// 重合 & 错误
					if (unCo  && iBtn == -1)
						texFeedBack = texNoneJ;			// 不重合 & 超时
					if (unCo  && iBtn != -1 && isRight)
						texFeedBack = texRightJ;		// 不重合 & 正确
					if (unCo  && iBtn != -1 && !isRight)
						texFeedBack = texWrongJ;		// 不重合 & 错误

					if (!drawTex("feedback", g_pSprite, texFeedBack, x_resolution, y_resolution))
						break;
				}
				break;
			}
		}
		g_pd3dDevice->EndScene();
	}

	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

void t8::getTexSize(LPDIRECT3DTEXTURE9 texture, double &w, double &h) {
	D3DSURFACE_DESC surfaceDesc;
	int level = 0; //The level to get the width/height of (probably 0 if unsure)
	texture->GetLevelDesc(level, &surfaceDesc);
	w = (int)surfaceDesc.Width;
	h = (int)surfaceDesc.Height;
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
//*外部消息处理 主要是键盘按键处理
//************************************************
LRESULT WINAPI t8::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYUP:
		switch (wParam)
		{
			//退出键
		case VK_ESCAPE: {
			// User wants to leave fullscreen mode
			//ShowCursor(TRUE);

			//保存当前状态
			int originalState = m_TestState;
			isCountdownStop = true;

			// 进入暂停状态
			m_TestState = STATE_PAUSE;
			
			LARGE_INTEGER begContinue, endContinue;
			QueryPerformanceCounter(&begContinue);
			ShowCursor(TRUE);
			rtn = DialogBox(gHinstance, MAKEINTRESOURCE(IDD_PAUSE), hWnd, PauseMsgProc);
			ShowCursor(FALSE);
			switch (rtn)
			{
			case ID_CONTINUE: {
				//激活父窗口
				//g_imgDisplayInd--;
				
				//恢复状态
				QueryPerformanceCounter(&endContinue);
				isCountdownStop = false;
				
				// 计算暂停时间（任务开始(注视)x2+反馈）
				if (originalState == STATE_DISPLAY_AND_COUNTDOWN_FORMAL 
					|| originalState == STATE_DISPLAY_AND_COUNTDOWN_EXERCISE
					|| originalState == STATE_DISPLAYFEEDBACK
					|| originalState == STATE_FOCUS_EXERCISE
					|| originalState == STATE_FOCUS_FORMAL)
					pauseTime += (double)(endContinue.QuadPart - begContinue.QuadPart) 
						/ (double)freq.QuadPart * 1000.;
				
				lastState = m_TestState;
				m_TestState = originalState;

				SetForegroundWindow(hWnd);
				rtn = 0;
				break;
			}
			case ID_NEXT:
				//若在任务中途退出 则保存当前所有实验数据
				EndDialog(hWnd, rtn);
				m_TestState = STATE_NEXT;
				break;
			case ID_CANCEL:
				//若在任务中途退出 则保存当前所有实验数据
				EndDialog(hWnd, rtn);
				m_TestState = STATE_EXIT;
				break;
			}
			break;
		}
		case VK_SPACE:
			if (m_TestState == STATE_DISPLAYINSTURCTION) 
				m_TestState = STATE_FOCUS_EXERCISE;
			if (m_TestState == STATE_BETWEEN_EXERCISE_AND_FORMAL)
				m_TestState = STATE_FOCUS_FORMAL;
			break;
		case 'f':
		case 'F':
		case 'j':
		case 'J': {
				if (!(m_TestState == STATE_DISPLAY_AND_COUNTDOWN_FORMAL 
					|| m_TestState == STATE_DISPLAY_AND_COUNTDOWN_EXERCISE))
					break;

				// 中断倒计时
				isCountdownStop = true;

				// 结束计时
				//QueryPerformanceCounter(&endTime);
				
				// 按键处理
				isPressBtn = true; // 已按下
				if (wParam == 'f' || wParam == 'F')
					isCoBtn = 0;
				else if (wParam == 'j' || wParam == 'J')
					isCoBtn = 1;

				//addAndSaveRec(m_TestState); // 添加记录

				// 状态跳转
				if (m_TestState == STATE_DISPLAY_AND_COUNTDOWN_EXERCISE) {
					m_TestState = STATE_EXERCISE;	// 练习->反馈
				}
				if (m_TestState == STATE_DISPLAY_AND_COUNTDOWN_FORMAL) {
					m_TestState = STATE_FORMAL;		//
				}
				break;
			}
		}
		return 0;
	case WM_KEYDOWN:
		/*switch (wParam)
		{
		case : {
			break;
		}

		}*/
		if (m_TestState == STATE_OVER)
			m_TestState = STATE_NEXT;

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
VOID t8::UpdateState()
{
	
}

//************************************************
//*主程序
//************************************************
int APIENTRY t8::_tWinMain(HINSTANCE &hInstance,
	HINSTANCE &hPrevInstance,
	LPTSTR    &lpCmdLine,
	int       &nCmdShow, HWND &_hWnd,
	std::string winClassName, std::string winName)
{
	// 打开控制台
	//if (!AllocConsole()) return 1;
	//freopen("CONOUT$", "w", stdout);

	srand((unsigned)time(NULL)); //初始化随机种子 

	//// 测试
	//getFormalList(64);
	//saveImgList(LImgs, RImgs, "formal");
	//getExerciseList(LImgs, RImgs, 2);
	//saveImgList(LImgs, RImgs, "exrcise");
	
	// 初始化句柄和状态
	bool bUnClosedLastWin = true;
	hWnd = _hWnd;
	gHinstance = hInstance;
	g_nThreadExitCount = 0;
	m_taskIndex = nCmdShow;
	//ShowCursor(FALSE);

	//获得传递的命令行参数，得到被试着名字和任务编号
	//gHinstance = hInstance;
	char *pdest;
	int result;
	int pos1;
	pdest = strrchr(lpCmdLine, ' ');
	pos1 = pdest - lpCmdLine;
	if (pos1>0) strncpy(m_TaskNumStr, lpCmdLine, pos1);
	else strcpy(m_TaskNumStr, "");
	
	pdest = strrchr(lpCmdLine, '-');
	result = pdest - lpCmdLine;
	
	if (result>0) strncpy(m_TesterName, lpCmdLine + pos1 + 1, result - pos1 - 1);
	else strcpy(m_TesterName, "");
	if (pos1>0) strcpy(m_DataName, lpCmdLine + pos1 + 1);
	else strcpy(m_DataName, "");

	//读取任务设置
	if (!ReadSetting())
	{
		MessageBox(hWnd, "任务设置文件格式错误！", "测试任务", MB_OK);
		return 0;
	}
	timerThread = thread(stateControl, ref(m_TestState),
		m_Setting.m_iPresentTime, m_Setting.m_iCountdownTime, m_Setting.m_iFocusTime, ref(bShowTime));
	QueryPerformanceFrequency(&freq);
	
	m_bLoadSign = FALSE;
	//注册窗口类
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
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
	ShowCursor(FALSE);

	//关闭输入法
	HKL hkl;
	hkl = LoadKeyboardLayout("00000804", KLF_ACTIVATE);
	if (hkl != NULL)
	{
		ActivateKeyboardLayout(hkl, KLF_SETFORPROCESS);
	}

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
				saveRecs();
				break;
			}
		}
	}
	ShowCursor(TRUE);
	timerThread.join();
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

void t8::test() {
	MessageBox(hWnd, "asdas","asdas",NULL);
}

// 单位：ms
void t8::timer(double &totalTime/*倒计时总时间，返回中断后的剩余时间*/, 
	int interval/*返回显示的间隔*/, 
	int &curTime/*当前时间，倒数显示*/, bool &isRtn/*是否返回*/, 
	bool &isShowTime/*是否显示时间*/, int countdownThreshold/*倒数计时阈值*/) {
	double residualTime = 0.;

	LARGE_INTEGER begt, endt, totalBegTime, totalEndTime;
	
	// 继续启动
	curTime = ceil(totalTime / 1000) * 1000;
	residualTime = 1000 - (curTime - totalTime);
	
	QueryPerformanceCounter(&begt);
	totalBegTime = begt;
	
	while (true) {
		// 判断退出
		if (totalTime <= 0
			|| (curTime <= 0 && residualTime <=0.+ 1e-6) 
			|| isRtn) {
			QueryPerformanceCounter(&totalEndTime);
			
			if (curTime <= 0 && residualTime <= 0. + 1e-6)
				totalTime = 0.;
			else {
				totalTime = totalTime -
					(double)(totalEndTime.QuadPart - totalBegTime.QuadPart)
					/ (double)freq.QuadPart * 1000.;
			}
			return;
		}
		// 判断是否显示时间
		if (curTime + residualTime < countdownThreshold)
			isShowTime = true;
		else
			isShowTime = false;

		QueryPerformanceCounter(&endt);
		// 判断是否已经耗尽残余时间
		if (residualTime > 1e-6) {
			double rsdTime = (double)(endt.QuadPart - totalBegTime.QuadPart)
				/ (double)freq.QuadPart * 1000.;
			if (rsdTime >= residualTime)
				residualTime = 0.;
		}
		//残余时间已经耗尽, 倒计时间隔处理
		else if (residualTime <= 1e-6) {
			double time1 = (double)(endt.QuadPart - begt.QuadPart)
				/ (double)freq.QuadPart *1000.;
			if (time1 >= interval) {
				QueryPerformanceCounter(&begt); // 新的间隔开始
				curTime -= interval;			// 当前时间减少
			}
		}
		
	}
	totalTime = 0;
}

// 状态控制器
void t8::stateControl(short & state, int presentTime, int countdownTime, int foucusTime, bool &bShowTime) {
	double leftTime;
	while (true) {
		switch (state){
		// 实验结束或下一个task
		case STATE_NEXT:
		case STATE_EXIT:
			return;
		case STATE_OVER:
		case STATE_PAUSE:
			break;
		// 练习任务注视点
		case STATE_FOCUS_EXERCISE:
			if (LImgs.empty()) getExerciseList(LImgs, RImgs, 2);// 产生随机图片组合
			//this_thread::sleep_for(std::chrono::seconds(foucusTime));
			// 判断是否初始化时间
			if (lastState == STATE_PAUSE)
				;
			else
				leftTime = foucusTime * 1000.;
			//leftTime = 1. * 1000.;
			isCountdownStop = false;
			bShowTime = false;
			timer(leftTime, 1000, countdown, isCountdownStop,
				bShowTime, 10000 * 1000);
			// 判断是否立刻退出（暂停状态）
			if (isCountdownStop == true) {
				break;
			}
			leftTime = presentTime * 1000.;								// 先准备好要显示的时间
			isCountdownStop = false;
			// 开始展示图片
			if (g_imgDisplayInd == -2) g_imgDisplayInd = -1;
			g_imgDisplayInd++;
			isPressBtn = false;
			// 计时开始
			pauseTime = 0.;
			QueryPerformanceCounter(&begTime);
			lastState = STATE_FOCUS_EXERCISE;
			state = STATE_DISPLAY_AND_COUNTDOWN_EXERCISE;
			break;
		// 正式任务注视点
		case STATE_FOCUS_FORMAL:
			if ( LImgs.empty()) getFormalList(64);				// 产生随机图片组合
			//this_thread::sleep_for(std::chrono::seconds(foucusTime));
			// 判断是否初始化时间
			if (lastState == STATE_PAUSE)
				;
			else
				leftTime = foucusTime * 1000.;
			isCountdownStop = false;
			bShowTime = false;
			timer(leftTime, 1000, countdown, isCountdownStop,
				bShowTime, countdownTime * 1000);
			// 判断是否立刻退出（暂停状态）
			if (isCountdownStop == true) {
				break;
			}
			leftTime = presentTime * 1000.;								// 先准备好要显示的时间
			isCountdownStop = false;
			// 开始展示图片
			if (g_imgDisplayInd == -2) g_imgDisplayInd = -1;
			g_imgDisplayInd++;
			isPressBtn = false;
			// 计时开始
			pauseTime = 0.;
			QueryPerformanceCounter(&begTime);
			lastState = STATE_FOCUS_FORMAL;
			state = STATE_DISPLAY_AND_COUNTDOWN_FORMAL;
			break;
		// 练习任务和正式任务之间
		case STATE_BETWEEN_EXERCISE_AND_FORMAL:
			break;
		// 反馈
		case STATE_DISPLAYFEEDBACK:
			bShowTime = false;
			//this_thread::sleep_for(std::chrono::seconds(1));
			// 判断是否初始化时间
			if (lastState == STATE_PAUSE)
				;
			else
				leftTime = 3 * 1000.;
			isCountdownStop = false;
			bShowTime = false;
			timer(leftTime, 1000, countdown, isCountdownStop,
				bShowTime, -1);
			// 判断是否立刻退出（暂停状态）
			if (isCountdownStop == true) {
				break;
			}
			// 显示完最后一张图的反馈以后跳到下一个状态
			if (g_imgDisplayInd >= LImgs.size() - 1) {
				g_imgDisplayInd = -2;
				LImgs.clear();
				RImgs.clear();
				lastState = STATE_DISPLAYFEEDBACK;
				state = STATE_BETWEEN_EXERCISE_AND_FORMAL;
				break;
			}
			// 一般情况跳到下个注视点
			lastState = STATE_DISPLAYFEEDBACK;
			state = STATE_FOCUS_EXERCISE;
			break;
		case STATE_DISPLAY_AND_COUNTDOWN_FORMAL:
		case STATE_DISPLAY_AND_COUNTDOWN_EXERCISE: {
			
			timer(leftTime, 1000, countdown, isCountdownStop, 
				bShowTime, countdownTime*1000);
			if (isCountdownStop == true) {
				break;
			}
			if (state == STATE_DISPLAY_AND_COUNTDOWN_EXERCISE)
				state = STATE_EXERCISE;
			else
				state = STATE_FORMAL;
			break;
		}
		case STATE_EXERCISE:
			// 计时结束， 
			isCountdownStop = true;
			QueryPerformanceCounter(&endTime);
			// 统计
			addAndSaveRec(m_TestState);
			// 练习任务显示反馈
			if (g_imgDisplayInd <= LImgs.size() - 1) {
				state = STATE_DISPLAYFEEDBACK;	// 应该先转到反馈
				break;
			}
			
			// 在单次任务中之间
			else if (g_imgDisplayInd < LImgs.size() - 1 && g_imgDisplayInd >= 0) {
				state = STATE_FOCUS_EXERCISE;
				break;
			}
			break;
		case STATE_FORMAL:
			// 计时结束， 
			isCountdownStop = true;
			QueryPerformanceCounter(&endTime);
			// 统计
			addAndSaveRec(m_TestState);
			// 正式任务完全结束，状态转移
			if (g_imgDisplayInd >= LImgs.size() - 1) {
				g_imgDisplayInd = -2;
				LImgs.clear();
				RImgs.clear();
				state = STATE_OVER;
				break;

			}
			// 在单次任务中之间
			else if (g_imgDisplayInd < LImgs.size() - 1 && g_imgDisplayInd >= 0) {
				state =  STATE_FOCUS_FORMAL;
				break;
			}
			break;
		default:
			break;
		}


	}
	
}

void t8::addAndSaveRec(int state) {
	Rec rec;
	double responseTime = (double)(endTime.QuadPart - begTime.QuadPart) 
		/ (double)freq.QuadPart * 1000. - pauseTime;
	rec.no = g_imgDisplayInd + 1;
	rec.leftImg = LImgs[g_imgDisplayInd];
	rec.rightImg = RImgs[g_imgDisplayInd];
	// 两张图能否重合
	if (rec.leftImg[rec.leftImg.size() - 5] == rec.rightImg[rec.rightImg.size() - 5]) 
		rec.unCoincidence = 0;
	else
		rec.unCoincidence = 1;
	// 判断是否超时
	rec.btn = (isPressBtn)? isCoBtn : -1;
	// 是否按键（不按则超时）
	if (isPressBtn) {
		if (rec.unCoincidence == rec.btn)
			rec.isRight = true;
		else
			rec.isRight = false;
		rec.responseTime = responseTime;
	}
	else	{
		rec.isRight = false;
		rec.responseTime = -1.;
	}

	recs.push_back(rec);
	
}

void t8::shuffleVector(vector<string> &v) {
	//std::srand(unsigned(std::time(0)));
	random_shuffle(v.begin(), v.end());
}

void t8::shuffleVector(vector<int> &v) {
	//std::srand(unsigned(std::time(0)));
	random_shuffle(v.begin(), v.end());
}
int t8::getRandom(int end) {
	//std::srand(unsigned(std::time(0)));
	return rand() % end;
}

// mode 0:重合 1:不重合
void t8::getExerciseList(int mode, int n, vector<string> &LImg, vector<string> &RImg,
	vector<string> axis, vector<string> ab, vector<string> ang) {
	// 选绕x轴还是z轴		 1/2
	// 选a类还是b类			*1/2
	// 选什么角度			*1/3

	//std::srand(unsigned(std::time(0)));
	for (int i = 0; i < n; i++)
	{
		// 选左边
		int indAxis = getRandom(axis.size());
		int indAb = getRandom(ab.size());
		int indAng = getRandom(ang.size());
		stringstream ss;
		ss << "1_" << axis[indAxis] << "_15_" << ab[indAb] << ".jpg";
		LImg.push_back(ss.str());
		Sleep(getRandom(100));
		// 选右边
		string newab = ab[indAb];
		if (mode == 1)  newab = ab[(indAb + 1) % ab.size()];
		ss.str("");
		ss << "1_" << axis[indAxis] << "_"<< ang[indAng] <<"_" << newab << ".jpg";
		RImg.push_back(ss.str());
		Sleep(getRandom(100));

	}

}

void t8::getExerciseList(vector<string> &LImgs, vector<string> &RImgs, int n) {
	
	LImgs.clear();
	RImgs.clear();
	
	// 初始化
	vector<string> axis = { "x","z"};
	vector<string> ab = { "a","b" };
	vector<string> ang = { "75","135","195" };
	
	getExerciseList(0, n, LImgs, RImgs, axis, ab, ang);
	getExerciseList(1, n, LImgs, RImgs, axis, ab, ang);
}


void t8::append(vector<string> &LImgs, vector<string> &RImgs, 
	vector<int> ind, vector<string> lstr, vector<string> rstr, vector<string> mode) {
	string a = lstr[0];
	string b = rstr[0];
	//std::srand(unsigned(std::time(0)));
	if (mode[0] == "89")
	{
		vector<int> indOdd, indEven;
		vector<string> str2 = {a,b};
		shuffleVector(str2);
		for (int i = 0; i < ind.size(); i++)
		{
			if (i % 2) {
				LImgs.push_back(str2[0]);
				RImgs.push_back("");
				indOdd.push_back(i);
			}
			else {
				LImgs.push_back(str2[1]);
				RImgs.push_back("");
				indEven.push_back(i);
			}
		}

		cout << "89" << endl;
		for (int i = 0; i < indOdd.size(); i++){
			cout << "L: " << LImgs[indOdd[i]] << endl;
		}
		lstr.erase(lstr.begin());
		rstr.erase(rstr.begin());
		mode.erase(mode.begin());
		append(LImgs, RImgs, indOdd, lstr, rstr, mode);
		append(LImgs, RImgs, indEven, lstr, rstr, mode);
	}
	else if (mode[0] == "half") {
		shuffleVector(ind);
		for (int i = 0; i < ind.size(); i++) {
			if (i < ind.size() / 2) 
				LImgs[ind[i]] += lstr[0];
			else
				LImgs[ind[i]] += rstr[0];
		}
		
		vector<int> ind1(ind.begin(), ind.begin() + ind.size() / 2);
		vector<int> ind2(ind.begin() + ind.size() / 2, ind.end());

		cout << "half" << endl;
		for (int i = 0; i < ind1.size(); i++) {
			cout << "L: " << LImgs[ind1[i]] << ", R: " << RImgs[ind1[i]] << endl;
		}

		
		if (lstr[0] != rstr[0]) {
			lstr.erase(lstr.begin());
			rstr.erase(rstr.begin());
			mode.erase(mode.begin());
			append(LImgs, RImgs, ind1, lstr, rstr, mode);
			append(LImgs, RImgs, ind2, lstr, rstr, mode);
		}
		else {
			lstr.erase(lstr.begin());
			rstr.erase(rstr.begin());
			mode.erase(mode.begin());
			append(LImgs, RImgs, ind, lstr, rstr, mode);
		}
	}
	else if (mode[0] == "right")
	{
		for (int i = 0; i < ind.size(); i++){
			RImgs[ind[i]] = LImgs[ind[0]].substr(0, 3);
		}
		vector<string> angAb = {	"_15_a.jpg", "_75_a.jpg", "_135_a.jpg", "_195_a.jpg",
								"_15_b.jpg", "_75_b.jpg", "_135_b.jpg", "_195_b.jpg"};
		
		shuffleVector(angAb);
		for (int i = 0; i < angAb.size(); i++) {
			RImgs[ind[i]] += angAb[i];
		}
		cout << "right" << endl;
		for (int i = 0; i < ind.size(); i++) {
			cout << "L: " << LImgs[ind[i]] << ", R: " << RImgs[ind[i]] << endl;
		}
	}

}

void t8::getFormalList(int n) {
	
	LImgs.clear();
	RImgs.clear();

	vector<string> lstr = { "8", "_x", "_15", "_a.jpg" , "right"};
	vector<string> rstr = { "9", "_z", "_15", "_b.jpg" , "right" };
	vector<string> mode = { "89", "half", "half", "half", "right"};
	vector<int> ind(n);
	for (int i = 0; i < n; i++)
	{
		ind[i] = i;
	}
	// 一层一层的添加字符串(8 or 9 -> x or z -> a or b), 然后生成右边的随机序列
	// 函数名起得不好
	append(LImgs, RImgs, ind, lstr, rstr, mode); 
}

void t8::saveImgList(vector<string> &LImgs, vector<string> &RImgs, string fileName) {
	ofstream out;
	out.open(string("./")+fileName+".csv");
	if (!out.is_open()) {
		MessageBox(hWnd, "没打开formalimglist.csv", "没打开formalimglist.csv", NULL);
		exit(0);
	}
	for (int i = 0; i < LImgs.size(); i++)
	{
		out << LImgs[i] << "," << RImgs[i] << endl;
	}
}

void t8::saveRecs() {
	ofstream out;
	out.open(szDataFile, ios::app);
	if (!out.is_open())
		MessageBox(hWnd, "数据文件不能创建或打开", "错误", NULL);
	for (int i = 0; i < recs.size(); i++)
	{
		out << recs[i].no << "\t"
			<< recs[i].leftImg << "\t"
			<< recs[i].rightImg << "\t"
			<< recs[i].unCoincidence << "\t"
			<< recs[i].btn << "\t"
			<< recs[i].isRight << "\t"
			<< recs[i].responseTime << "\n";
	}
}