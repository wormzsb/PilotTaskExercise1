
#include "stdafx.h"
#include "Task8.h"
#include <iostream>
using namespace std;

// ����ʱ���õ�������
LPDIRECT3DTEXTURE9 texCross = NULL, texRightF = NULL, texWrongF = NULL, texNoneF = NULL,
texRightJ = NULL, texWrongJ = NULL, texNoneJ = NULL;
LPDIRECT3DTEXTURE9      t8::texInst = NULL;            //�������


// ״̬����
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
	bool unCoincidence; // 0:�غ� 1�������غ�
	int btn;			//0���غ� 1�����غ� -1����ʱ
	bool isRight;		// 0: ���� 1����ȷ
	double responseTime;	// ��λ����
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
float t8::acce;//���ٶ�
int	t8::iDirection = 0;
int t8::g_nThreadExitCount = 0;                      //��ǰ���е��߳���
DWORD t8::dwInputThreadID = 0;                       //��׼�������߳�ID
BOOL t8::m_bCubeNum[4];                              //��άͼ�η�������־

BOOL t8::m_bAcc;                                     //��άͼ�μ�����ȷ�Ա�־
double t8::alpha, t8::omiga, t8::v, t8::a, t8::b, t8::r, t8::Rx, t8::Ry, t8::fai, t8::AngleSpeed, t8::inc_v;
double t8::m_PostPointX, t8::m_PostPointY;                //��ǰ��׼������
int t8::JoyX, t8::JoyY;                                   //��ǰ���ݸ�����ֵ  
struct TaskSetting8   t8::m_Setting;                 //����6���ò���
struct HardSetting   t8::m_HardSetting;              //Ӳ�����ò���
struct PartInfo   t8::m_PartInfo;                    //��������Ϣ
short t8::m_TrialType;                               //��������
int t8::m_TrialTime;                                 //����ʱ��
int t8::m_TrialTimes;                                //����ʱ��
int t8::iJoyMoveDirection;//�ֱ��˶�����������
int t8::x_resolution = 1024;			//��Ļ�ֱ���
int t8::y_resolution = 768;             //��Ļ�ֱ���
int t8::rec_x_begin;
int t8::rec_y_begin;
int t8::rec_x_end;
int t8::rec_y_end;
const float t8::FontScale = (float)(t8::x_resolution + t8::y_resolution) / 1400.0;             //��������Ļ�ֱ��ʵķ����߶�

const char t8::Insturction11[] = "    ��ӭ����˫������ά\
ͼ�μ����б�������ʹ�����ֿ��Ʋ��ݸ�׷����Ļ�ϵġ��͡���ͬʱ��ע��\
��Ļ������ֵ�ͼ��������Ҫ��ס��Щͼ����X�����Ļ�������Щ�ַ���\
��ʧ��Ȼ����Ļ���������γ���һϵ��ͼ����ÿ�γ���һ�������ж���Щͼ��\
�Ƿ�Ϊ���ס����Щͼ����";
const char t8::Insturction12[] = "    ��ӭ����˫��\
������б���ԣ���ʹ�����ֿ��Ʋ��ݸ�׷����Ļ�ϵġ��͡���ͬʱ��ע����\
Ļ������ֵ�ͼ��������Ҫ��ס��Щͼ����X�����Ļ�������Щ�ַ�����\
ʧ��Ȼ����Ļ���������γ���һϵ��ͼ����ÿ�γ���һ�������ж���Щͼ����\
��Ϊ���ס����Щͼ����";
const char t8::Insturction13[] = "���ס�����ͼ����\n�����ǡ�����ʼ���ԡ�";
const char t8::Insturction2[] = "��ϰ�������������������ʽʵ�顣";
const char t8::Insturction3[] = "��������ɣ��������������";
const char t8::FeedBack[2][10] = { "����","��ȷ" };

LPDIRECT3D9             t8::g_pD3D = NULL;               //directx3d����
LPDIRECT3DDEVICE9       t8::g_pd3dDevice = NULL;               //directx�豸����

LPDIRECT3DTEXTURE9      t8::g_pTexture0 = NULL;               //�������
LPDIRECT3DTEXTURE9      t8::g_pTexture1 = NULL;               //�������
LPDIRECT3DTEXTURE9      t8::g_pTexture2 = NULL;               //�������
LPDIRECT3DTEXTURE9      t8::g_pTexture3[12] = { NULL };         //�������
LPDIRECT3DTEXTURE9      t8::g_pTexture4 = NULL;               //�������

LPD3DXSPRITE            t8::g_pSprite = NULL;                 //�������
LPD3DXFONT              t8::g_pFont = 0;                  //�������
LPD3DXFONT              t8::g_pFont1 = 0;                  //�������
LPD3DXFONT              t8::g_pFont2 = 0;                  //�������
LPDIRECT3DVERTEXBUFFER9      t8::m_pVertexBuffer = NULL;


LPDIRECT3DTEXTURE9 texLeft, texRight;

D3DXMATRIX t8::m_Transform;                          //����任����
float t8::TimeInt;
short t8::m_SignNo;                                  //��άͼ�μ������
short t8::m_SignOrderNo1, t8::m_SignOrderNo2;            //��άͼ�μ���ϵ�����
short t8::m_SignTrialNo;                             //��άͼ�μ��������
short t8::m_SignGroupNo;                             //��άͼ�μ������
short t8::m_SignCount;                               //��άͼ�μ�����Ŀ
BOOL t8::m_bShowMem;                                 //��������άͼ���ļ���ʾ��־
BOOL t8::m_bLoadSign;                                //��άͼ���ļ����ر�־
BOOL t8::m_bDisplayReady;

BOOL t8::m_bHideSign = FALSE;						  //�ڵȴ�ʱ��������άͼ��
BOOL t8::m_bRememStart;                               //��άͼ�μ��俪ʼ��־      
BOOL t8::m_bSignStart;                                //��άͼ����ʾ��־
short t8::m_SureDownNum;
int t8::m_SignType[12];                               //��άͼ������
int t8::m_SignOrder1[6];                              //��άͼ������
int t8::m_SignOrder2[6];                              //��άͼ������
unsigned long t8::m_SignStartTime[12];                //��άͼ�μ��俪ʼʱ��
unsigned long t8::m_SignSureTime[12];                 //��άͼ�μ���ȷ��ʱ��
char t8::m_LMemName[30];                              //��Ŵ�������άͼ�����Ƶ�����
char t8::m_RMemName[12][30];                          //��ż�����άͼ�����Ƶ�����
short t8::m_LMemAngle;                                //��Ŵ�������άͼ����ת�Ƕȵ�����
short t8::m_RMemAngle[12];                            //��ż�����άͼ����ת�Ƕȵ�����
short t8::m_MemAngleDiff[12];                         //���������άͼ����ת�ǶȲ������
short t8::m_NoSame[12];                               //�����άͼ����ͬ�Ե�����
short t8::m_SureButtonNo[12];                         //���ȷ�ϰ���������
short t8::m_ButtonDownNum;

int t8::m_CubeNum;

const double t8::m_MoveInt = 0.04;                    //�������40ms

UINT t8::m_PointNum;
UINT t8::m_MemNum;
BOOL *t8::m_bHit = NULL;                               //��Ż���״̬������
SPOINT *t8::m_ObjPoint = NULL;                         //���Ŀ�����������
SPOINT *t8::m_PostPoint = NULL;                        //�����׼�����������
float *t8::m_Distance = NULL;                          //���Ŀ�����׼�����������
unsigned long *t8::m_PointTime = NULL;                 //��Ų���ʱ�������
float *t8::m_ObjSpeedX = NULL;                         //���Ŀ���ٶȵ�����
float *t8::m_ObjSpeedY = NULL;                         //���Ŀ���ٶȵ�����
float *t8::m_PostSpeedX = NULL;                        //�����׼���ٶȵ�����
float *t8::m_PostSpeedY = NULL;                        //�����׼���ٶȵ�����
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
//*��ȡ��ǰ��������
//************************************************
BOOL t8::ReadSetting()
{
	FILE *fp;
	char m_PartFile[50];
	//��ȡ��������Ϣ
	if (strlen(m_TesterName)>0)
	{
		sprintf(m_PartFile, "PartInfo\\%s.txt", m_TesterName);
		fp = fopen(m_PartFile, "rt");
		if (fp != NULL)
		{
			fscanf(fp, "���\t%s\n", m_PartInfo.m_TesterNo);
			fscanf(fp, "����\t%s\n", m_PartInfo.m_TesterName);
			fscanf(fp, "�Ա�\t%s\n", m_PartInfo.m_TesterSex);
			fscanf(fp, "����\t%d\n", &m_PartInfo.m_TesterAge);
			fscanf(fp, "��N��\t%d\n", &m_PartInfo.m_Session);
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

	//��ȡӲ������
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

	//��ȡ��������
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
//*����������ݼ�¼�ļ�
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
			<< "-����8-��ά������ת����-"
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

	// �����ļ�ͷ
	ofstream out(szDataFile);
	if (!out.is_open()) 
		MessageBox(hWnd, "�����ļ����ܴ������", "����", NULL);
	out << "���\t���ͼƬ\t�Ҳ�ͼƬ\t�ܷ��غ�\t�������\t�Ƿ���ȷ\t��Ӧʱ\n";
	out.close();
}



//************************************************
//*���������ݼ�¼�ļ�
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
//*������άͼ���ļ�
//************************************************
HRESULT t8::LoadSignFile()
{
	
	return TRUE;
}

//************************************************
//*���������ʼ��
//************************************************
VOID t8::TestInit()
{

}

unsigned t8::addTex(LPDIRECT3DDEVICE9 & dev, string fileName, LPDIRECT3DTEXTURE9 &tex) {
	if (FAILED(D3DXCreateTextureFromFile(dev, fileName.c_str(), &tex)))
	{
		MessageBox(NULL, (fileName + "�ļ�������").c_str(), "�������", MB_OK);
		return E_FAIL;
	}
}

//************************************************
//*��ʼ��DirectX 3D
//************************************************
HRESULT t8::InitD3D(HWND hWnd)
{
	m_TestState = STATE_DISPLAYINSTURCTION;
	m_bDisplayReady = TRUE;
	m_SignGroupNo = -1;
	m_SureDownNum = 0;
	m_CubeNum = 9;
	

	//���ʴ�С
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


	//��������
	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &g_pSprite)))
	{
		MessageBox(NULL, "Could not find banana.bmp", "Textures.exe", MB_OK);
		return E_FAIL;
	}

	//��������ͼƬ
	// ָ����
	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, (picDir+"ST_3D.jpg").c_str(), &texInst)))
	{
		MessageBox(NULL, "Could not find banana.bmp", "Textures.exe", MB_OK);
		return E_FAIL;		
	}
	
	addTex(g_pd3dDevice, "./Pics/TaskR/cross.jpg", texCross);
	addTex(g_pd3dDevice, picDir + "right_f.jpg", texRightF);	// ���غ� ��Ӧ��ȷ
	addTex(g_pd3dDevice, picDir + "wrong_f.jpg", texWrongF);	// ���غ� ��Ӧ����
	addTex(g_pd3dDevice, picDir + "none_f.jpg", texNoneF);		// ���غ� ��Ӧ��ʱ
	addTex(g_pd3dDevice, picDir + "right_j.jpg", texRightJ);	// �����غ� ��Ӧ��ȷ
	addTex(g_pd3dDevice, picDir + "wrong_j.jpg", texWrongJ);	// �����غ� ��Ӧ����
	addTex(g_pd3dDevice, picDir + "none_j.jpg", texNoneJ);		// �����غ� ��Ӧ��ʱ


	LOGFONT lf;
	ZeroMemory(&lf, sizeof(LOGFONT));
	strcpy(lf.lfFaceName, "Times New Roman");
	lf.lfHeight = -16;
	if (FAILED(D3DXCreateFont(g_pd3dDevice, 30 * FontScale, 15 * FontScale, 20,
		0, 0, GB2312_CHARSET, 0, 0, 0, "����", &g_pFont)))
	{
		return E_FAIL;
	}
	if (FAILED(D3DXCreateFont(g_pd3dDevice, 40 * FontScale, 20 * FontScale, 20,
		0, 0, GB2312_CHARSET, 0, 0, 0, "����", &g_pFont1)))
	{
		return E_FAIL;
	}
	if (FAILED(D3DXCreateFont(g_pd3dDevice, 20 * FontScale, 10 * FontScale, 20,
		0, 0, GB2312_CHARSET, 0, 0, 0, "����", &g_pFont2)))
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
//*�ͷ������ڴ�
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
//*�ͷ�DirectX����
//************************************************
VOID t8::Cleanup()
{
	//�ͷ��������
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

//��ָ��λ��д����
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

//��ָ��λ�ú�����ϵ��������
BOOL t8::drawTex(double tx, double ty, LPD3DXSPRITE &g_pSprite, LPDIRECT3DTEXTURE9 &tex,
	double sx, double sy) {
	D3DXMATRIX mx;
	if (SUCCEEDED(g_pSprite->Begin(D3DXSPRITE_ALPHABLEND))) {
		// ���
		D3DXMatrixTransformation2D(
			&mx,
			NULL,							// ������������
			0.0,							// ������ת�Ƕ�
			&D3DXVECTOR2(sx, sy),			// ��������
			&D3DXVECTOR2(0, 0),				// ��ת����
			NULL,							// ��ת�Ƕ�
			&D3DXVECTOR2(tx,ty)	// ƽ������
			);
		g_pSprite->SetTransform(&mx);
		g_pSprite->Draw(
			tex,
			NULL,							// ����Դ��ROI 
			&D3DXVECTOR3(0, 0, 0),			// �������� 
			&D3DXVECTOR3(0, 0, 0),			// ����λ��
			0xffffffff						// �޸���ɫ
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
// ����ģʽ������
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
	// ���Ҳ���
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
	//�м��ͼ
	else if (mode == "cross" 
		|| mode == "feedback" 
		|| mode == "inst") {
		
		if (!drawTex(tx, ty, g_pSprite, ltex, sx, sy))
			return FALSE;
	}
	
	return TRUE;
}

//************************************************
//*��Ⱦ
//************************************************
VOID t8::Render()
{
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET,
		D3DCOLOR_XRGB(0, 0, 0), 0.0f, 0);
	// ����ǰ����
	D3DXMATRIX mx;
	//�ں�̨����������ͼ��
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		g_pd3dDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(CUSTOMVERTEX));
		g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
		//      g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
		switch (m_TestState)
		{
			//����ָ����ͼƬ
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
		//���Խ���
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
			ss << "��������"
				<< "ƽ����ȷ��Ϊ" << setprecision(2) << (double)sumRight / cnt * 100. << "%, "
				<< "ƽ����ӦʱΪ" << setprecision(0) << sumResTime / cnt << "����";
			int tx = x_resolution / 2;
			int ty = y_resolution  - 50;
			drawText(ss.str(), tx, ty, g_pFont);
			g_pFont1->DrawText(NULL, Insturction3, -1, &erect,
				DT_WORDBREAK | DT_NOCLIP | DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(255, 255, 255));
			break; 
		}
		case STATE_FOCUS_EXERCISE:
		case STATE_FOCUS_FORMAL: 
			// ����ͼƬ
			if (!drawTex("cross", g_pSprite, texCross, x_resolution, y_resolution))
				break;
			break;
		case STATE_BETWEEN_EXERCISE_AND_FORMAL: {
			// ��������
			int tx = x_resolution / 2;
			int ty = y_resolution/2 - 50;
			stringstream ss;
			ss << "�밴�ո��������ʽ����" ;
			if (!drawText(ss.str(), tx, ty, g_pFont))
				break;
			break;
		}
		case STATE_DISPLAYFEEDBACK: 
		case STATE_DISPLAY_AND_COUNTDOWN_EXERCISE:
		case STATE_DISPLAY_AND_COUNTDOWN_FORMAL:
		case STATE_EXERCISE:
		case STATE_FORMAL: {
				// ����ͼƬ
				// ��������
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
					// ��������
					int tx = x_resolution / 2;
					int ty = y_resolution - 50;
					stringstream ss;
					ss << "��ʣ" << countdown/1000 << "��"/* << g_imgDisplayInd*/;
					if (!drawText(ss.str(), tx, ty, g_pFont))
						break;
				}

				// �����Ƿ���ʱ����ʾ������ͼ��
				if (m_TestState == STATE_DISPLAYFEEDBACK) {
					
					LPDIRECT3DTEXTURE9 texFeedBack = NULL;
					bool unCo = recs.rbegin()->unCoincidence;
					int iBtn = recs.rbegin()->btn;
					bool isRight = recs.rbegin()->isRight;

					if (!unCo && iBtn == -1)
						texFeedBack = texNoneF;			// �غ� & ��ʱ
					if (!unCo  && iBtn != -1 && isRight)
						texFeedBack = texRightF;		// �غ� & ��ȷ
					if (!unCo  && iBtn != -1 && !isRight)
						texFeedBack = texWrongF;		// �غ� & ����
					if (unCo  && iBtn == -1)
						texFeedBack = texNoneJ;			// ���غ� & ��ʱ
					if (unCo  && iBtn != -1 && isRight)
						texFeedBack = texRightJ;		// ���غ� & ��ȷ
					if (unCo  && iBtn != -1 && !isRight)
						texFeedBack = texWrongJ;		// ���غ� & ����

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

//��ͣ�Ի�����Ϣѭ��
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
//*�ⲿ��Ϣ���� ��Ҫ�Ǽ��̰�������
//************************************************
LRESULT WINAPI t8::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYUP:
		switch (wParam)
		{
			//�˳���
		case VK_ESCAPE: {
			// User wants to leave fullscreen mode
			//ShowCursor(TRUE);

			//���浱ǰ״̬
			int originalState = m_TestState;
			isCountdownStop = true;

			// ������ͣ״̬
			m_TestState = STATE_PAUSE;
			
			LARGE_INTEGER begContinue, endContinue;
			QueryPerformanceCounter(&begContinue);
			ShowCursor(TRUE);
			rtn = DialogBox(gHinstance, MAKEINTRESOURCE(IDD_PAUSE), hWnd, PauseMsgProc);
			ShowCursor(FALSE);
			switch (rtn)
			{
			case ID_CONTINUE: {
				//�������
				//g_imgDisplayInd--;
				
				//�ָ�״̬
				QueryPerformanceCounter(&endContinue);
				isCountdownStop = false;
				
				// ������ͣʱ�䣨����ʼ(ע��)x2+������
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
				//����������;�˳� �򱣴浱ǰ����ʵ������
				EndDialog(hWnd, rtn);
				m_TestState = STATE_NEXT;
				break;
			case ID_CANCEL:
				//����������;�˳� �򱣴浱ǰ����ʵ������
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

				// �жϵ���ʱ
				isCountdownStop = true;

				// ������ʱ
				//QueryPerformanceCounter(&endTime);
				
				// ��������
				isPressBtn = true; // �Ѱ���
				if (wParam == 'f' || wParam == 'F')
					isCoBtn = 0;
				else if (wParam == 'j' || wParam == 'J')
					isCoBtn = 1;

				//addAndSaveRec(m_TestState); // ��Ӽ�¼

				// ״̬��ת
				if (m_TestState == STATE_DISPLAY_AND_COUNTDOWN_EXERCISE) {
					m_TestState = STATE_EXERCISE;	// ��ϰ->����
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
		//���������Ϣ
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
//*��������ִ�й���
//************************************************
VOID t8::UpdateState()
{
	
}

//************************************************
//*������
//************************************************
int APIENTRY t8::_tWinMain(HINSTANCE &hInstance,
	HINSTANCE &hPrevInstance,
	LPTSTR    &lpCmdLine,
	int       &nCmdShow, HWND &_hWnd,
	std::string winClassName, std::string winName)
{
	// �򿪿���̨
	//if (!AllocConsole()) return 1;
	//freopen("CONOUT$", "w", stdout);

	srand((unsigned)time(NULL)); //��ʼ��������� 

	//// ����
	//getFormalList(64);
	//saveImgList(LImgs, RImgs, "formal");
	//getExerciseList(LImgs, RImgs, 2);
	//saveImgList(LImgs, RImgs, "exrcise");
	
	// ��ʼ�������״̬
	bool bUnClosedLastWin = true;
	hWnd = _hWnd;
	gHinstance = hInstance;
	g_nThreadExitCount = 0;
	m_taskIndex = nCmdShow;
	//ShowCursor(FALSE);

	//��ô��ݵ������в������õ����������ֺ�������
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

	//��ȡ��������
	if (!ReadSetting())
	{
		MessageBox(hWnd, "���������ļ���ʽ����", "��������", MB_OK);
		return 0;
	}
	timerThread = thread(stateControl, ref(m_TestState),
		m_Setting.m_iPresentTime, m_Setting.m_iCountdownTime, m_Setting.m_iFocusTime, ref(bShowTime));
	QueryPerformanceFrequency(&freq);
	
	m_bLoadSign = FALSE;
	//ע�ᴰ����
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

	//��ʾ������
	SetFocus(hWnd);
	ShowCursor(FALSE);

	//�ر����뷨
	HKL hkl;
	hkl = LoadKeyboardLayout("00000804", KLF_ACTIVATE);
	if (hkl != NULL)
	{
		ActivateKeyboardLayout(hkl, KLF_SETFORPROCESS);
	}

	//��ʼ��Direct3D
	if (SUCCEEDED(InitD3D(hWnd)))
	{

		//������Ϣѭ��
		MSG msg;
		ZeroMemory(&msg, sizeof(msg));
		while (msg.message != WM_QUIT)
		{
			if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
			{
				//�����ⲿ��Ϣ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				//ִ�в��Թ���
				if (m_bDisplayReady)
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
		// ������һ������
		HWND tmpHw = FindWindow(winClassName.c_str(), winName.c_str());
		if (winClassName != "") // ����Ƿ��ǵ�һ������
		{
			ShowWindow(tmpHw, 0);
			UnregisterClass(winClassName.c_str(), hInstance);
		}
	}
}

void t8::test() {
	MessageBox(hWnd, "asdas","asdas",NULL);
}

// ��λ��ms
void t8::timer(double &totalTime/*����ʱ��ʱ�䣬�����жϺ��ʣ��ʱ��*/, 
	int interval/*������ʾ�ļ��*/, 
	int &curTime/*��ǰʱ�䣬������ʾ*/, bool &isRtn/*�Ƿ񷵻�*/, 
	bool &isShowTime/*�Ƿ���ʾʱ��*/, int countdownThreshold/*������ʱ��ֵ*/) {
	double residualTime = 0.;

	LARGE_INTEGER begt, endt, totalBegTime, totalEndTime;
	
	// ��������
	curTime = ceil(totalTime / 1000) * 1000;
	residualTime = 1000 - (curTime - totalTime);
	
	QueryPerformanceCounter(&begt);
	totalBegTime = begt;
	
	while (true) {
		// �ж��˳�
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
		// �ж��Ƿ���ʾʱ��
		if (curTime + residualTime < countdownThreshold)
			isShowTime = true;
		else
			isShowTime = false;

		QueryPerformanceCounter(&endt);
		// �ж��Ƿ��Ѿ��ľ�����ʱ��
		if (residualTime > 1e-6) {
			double rsdTime = (double)(endt.QuadPart - totalBegTime.QuadPart)
				/ (double)freq.QuadPart * 1000.;
			if (rsdTime >= residualTime)
				residualTime = 0.;
		}
		//����ʱ���Ѿ��ľ�, ����ʱ�������
		else if (residualTime <= 1e-6) {
			double time1 = (double)(endt.QuadPart - begt.QuadPart)
				/ (double)freq.QuadPart *1000.;
			if (time1 >= interval) {
				QueryPerformanceCounter(&begt); // �µļ����ʼ
				curTime -= interval;			// ��ǰʱ�����
			}
		}
		
	}
	totalTime = 0;
}

// ״̬������
void t8::stateControl(short & state, int presentTime, int countdownTime, int foucusTime, bool &bShowTime) {
	double leftTime;
	while (true) {
		switch (state){
		// ʵ���������һ��task
		case STATE_NEXT:
		case STATE_EXIT:
			return;
		case STATE_OVER:
		case STATE_PAUSE:
			break;
		// ��ϰ����ע�ӵ�
		case STATE_FOCUS_EXERCISE:
			if (LImgs.empty()) getExerciseList(LImgs, RImgs, 2);// �������ͼƬ���
			//this_thread::sleep_for(std::chrono::seconds(foucusTime));
			// �ж��Ƿ��ʼ��ʱ��
			if (lastState == STATE_PAUSE)
				;
			else
				leftTime = foucusTime * 1000.;
			//leftTime = 1. * 1000.;
			isCountdownStop = false;
			bShowTime = false;
			timer(leftTime, 1000, countdown, isCountdownStop,
				bShowTime, 10000 * 1000);
			// �ж��Ƿ������˳�����ͣ״̬��
			if (isCountdownStop == true) {
				break;
			}
			leftTime = presentTime * 1000.;								// ��׼����Ҫ��ʾ��ʱ��
			isCountdownStop = false;
			// ��ʼչʾͼƬ
			if (g_imgDisplayInd == -2) g_imgDisplayInd = -1;
			g_imgDisplayInd++;
			isPressBtn = false;
			// ��ʱ��ʼ
			pauseTime = 0.;
			QueryPerformanceCounter(&begTime);
			lastState = STATE_FOCUS_EXERCISE;
			state = STATE_DISPLAY_AND_COUNTDOWN_EXERCISE;
			break;
		// ��ʽ����ע�ӵ�
		case STATE_FOCUS_FORMAL:
			if ( LImgs.empty()) getFormalList(64);				// �������ͼƬ���
			//this_thread::sleep_for(std::chrono::seconds(foucusTime));
			// �ж��Ƿ��ʼ��ʱ��
			if (lastState == STATE_PAUSE)
				;
			else
				leftTime = foucusTime * 1000.;
			isCountdownStop = false;
			bShowTime = false;
			timer(leftTime, 1000, countdown, isCountdownStop,
				bShowTime, countdownTime * 1000);
			// �ж��Ƿ������˳�����ͣ״̬��
			if (isCountdownStop == true) {
				break;
			}
			leftTime = presentTime * 1000.;								// ��׼����Ҫ��ʾ��ʱ��
			isCountdownStop = false;
			// ��ʼչʾͼƬ
			if (g_imgDisplayInd == -2) g_imgDisplayInd = -1;
			g_imgDisplayInd++;
			isPressBtn = false;
			// ��ʱ��ʼ
			pauseTime = 0.;
			QueryPerformanceCounter(&begTime);
			lastState = STATE_FOCUS_FORMAL;
			state = STATE_DISPLAY_AND_COUNTDOWN_FORMAL;
			break;
		// ��ϰ�������ʽ����֮��
		case STATE_BETWEEN_EXERCISE_AND_FORMAL:
			break;
		// ����
		case STATE_DISPLAYFEEDBACK:
			bShowTime = false;
			//this_thread::sleep_for(std::chrono::seconds(1));
			// �ж��Ƿ��ʼ��ʱ��
			if (lastState == STATE_PAUSE)
				;
			else
				leftTime = 3 * 1000.;
			isCountdownStop = false;
			bShowTime = false;
			timer(leftTime, 1000, countdown, isCountdownStop,
				bShowTime, -1);
			// �ж��Ƿ������˳�����ͣ״̬��
			if (isCountdownStop == true) {
				break;
			}
			// ��ʾ�����һ��ͼ�ķ����Ժ�������һ��״̬
			if (g_imgDisplayInd >= LImgs.size() - 1) {
				g_imgDisplayInd = -2;
				LImgs.clear();
				RImgs.clear();
				lastState = STATE_DISPLAYFEEDBACK;
				state = STATE_BETWEEN_EXERCISE_AND_FORMAL;
				break;
			}
			// һ����������¸�ע�ӵ�
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
			// ��ʱ������ 
			isCountdownStop = true;
			QueryPerformanceCounter(&endTime);
			// ͳ��
			addAndSaveRec(m_TestState);
			// ��ϰ������ʾ����
			if (g_imgDisplayInd <= LImgs.size() - 1) {
				state = STATE_DISPLAYFEEDBACK;	// Ӧ����ת������
				break;
			}
			
			// �ڵ���������֮��
			else if (g_imgDisplayInd < LImgs.size() - 1 && g_imgDisplayInd >= 0) {
				state = STATE_FOCUS_EXERCISE;
				break;
			}
			break;
		case STATE_FORMAL:
			// ��ʱ������ 
			isCountdownStop = true;
			QueryPerformanceCounter(&endTime);
			// ͳ��
			addAndSaveRec(m_TestState);
			// ��ʽ������ȫ������״̬ת��
			if (g_imgDisplayInd >= LImgs.size() - 1) {
				g_imgDisplayInd = -2;
				LImgs.clear();
				RImgs.clear();
				state = STATE_OVER;
				break;

			}
			// �ڵ���������֮��
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
	// ����ͼ�ܷ��غ�
	if (rec.leftImg[rec.leftImg.size() - 5] == rec.rightImg[rec.rightImg.size() - 5]) 
		rec.unCoincidence = 0;
	else
		rec.unCoincidence = 1;
	// �ж��Ƿ�ʱ
	rec.btn = (isPressBtn)? isCoBtn : -1;
	// �Ƿ񰴼���������ʱ��
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

// mode 0:�غ� 1:���غ�
void t8::getExerciseList(int mode, int n, vector<string> &LImg, vector<string> &RImg,
	vector<string> axis, vector<string> ab, vector<string> ang) {
	// ѡ��x�ỹ��z��		 1/2
	// ѡa�໹��b��			*1/2
	// ѡʲô�Ƕ�			*1/3

	//std::srand(unsigned(std::time(0)));
	for (int i = 0; i < n; i++)
	{
		// ѡ���
		int indAxis = getRandom(axis.size());
		int indAb = getRandom(ab.size());
		int indAng = getRandom(ang.size());
		stringstream ss;
		ss << "1_" << axis[indAxis] << "_15_" << ab[indAb] << ".jpg";
		LImg.push_back(ss.str());
		Sleep(getRandom(100));
		// ѡ�ұ�
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
	
	// ��ʼ��
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
	// һ��һ�������ַ���(8 or 9 -> x or z -> a or b), Ȼ�������ұߵ��������
	// ��������ò���
	append(LImgs, RImgs, ind, lstr, rstr, mode); 
}

void t8::saveImgList(vector<string> &LImgs, vector<string> &RImgs, string fileName) {
	ofstream out;
	out.open(string("./")+fileName+".csv");
	if (!out.is_open()) {
		MessageBox(hWnd, "û��formalimglist.csv", "û��formalimglist.csv", NULL);
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
		MessageBox(hWnd, "�����ļ����ܴ������", "����", NULL);
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