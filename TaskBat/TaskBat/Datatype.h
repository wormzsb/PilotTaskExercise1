#pragma once
#include <dinput.h>

//����ʹ�ò��ݸ˻���� 0-���̣�1-���ݸ�
#define JOY 1

enum{BTN_DOWN, BTN_UP};
enum KEYMAP{KEY8,KEY6,KEY7,KEY4,KEY2,KEY5,KEY3,KEY1};
enum{LEFT, TOP,RIGHT,BOTTOM,RANDOM};
enum PLANE_POS{LEFT_TOP = 1,RIGHT_TOP = 2,RIGHT_BOTTOM = 4,LEFT_BOTTOM = 8};
enum{BALL_SPEED_CONSTANT, BALL_SPEED_ACC};

//�˶��켣����
enum TRACE_TYPE
{
	TRACK_CIRCLE,  //Բ��
	TRACK_ELLIPSE, //��Բ��
	TRACK_EIGHT    //������
};

//������ɫ
enum BACKGROUND_TYPE
{
	BACKGROUND_GRAY,  //����ɫ
	BACKGROUND_BLACK, //�ڻ�ɫ
	BACKGROUND_STAR   //��Խ�ǿ�
};

//�˶���ʽ
enum MOVE_MODE
{
	MODE_MOVE,       //ƽ��
	MODE_MOVEROATE   //ƽ��+��ת
};

const double PI = 3.1415927;

//����1����
struct TaskSetting1
{
	char    m_TaskName[100];
	BOOL    m_PracMode;
	BOOL    m_ExperMode;
	short	m_Track;
	short	m_Direction;
    short   m_MoveMode;
	short	m_SpeedMode;
	float   m_InitAngle;
	short	m_Pause;
	int	    m_PauseNum;
	float	m_Speed;
	float	m_InitSpeed;
	float	m_SpeedMin;
	float	m_SpeedMax;
	float   m_AccelerationMin;
	float   m_AccelerationMax;
	float	m_AngleSpeedMin;
	float	m_AngleSpeedMax;
	float	m_RotateAngleMin;
	float	m_RotateAngleMax;
	int	    m_PracTime;
	int	    m_ExperTime;
	int	    m_PracTimes;	
	int	    m_ExperTimes;
	short   m_Background;
	int		m_iJoyMoveDirection;
};

//����2����
struct TaskSetting2
{
	char    m_TaskName[100];
	BOOL    m_PracMode;
	BOOL    m_ExperMode;
	BOOL    m_MainTask;
	BOOL    m_SubTask;
	short	m_Direction;
	float	m_InitSpeed;
	short   m_HoldTimeNum;
	float	m_HoldTime[12];
	short   m_IntervalMode;
	int	    m_PracTime;
	int	    m_ExperTime;
    int     m_PracTimes;
	int     m_ExperTimes;
	short   m_Background;
	int		m_iJoyMoveDirection;
	int		m_iSubTaskInterval;
	short   m_MoveMode;
	short	m_SpeedMode;
	float	m_Speed;
	float	m_SpeedMin;
	float	m_SpeedMax;
	float   m_AccelerationMin;
	float   m_AccelerationMax;
	int		m_iTrack;
};

//����3����
struct TaskSetting3
{
	char    m_TaskName[100];
	BOOL    m_PracMode;
	BOOL    m_ExperMode;
	BOOL    m_MainTask;
	BOOL    m_SubTask;
	short	m_MainTaskMode;
	float	m_InitSpeed;
	short	m_EventMode;
	short	m_CodePairMode;
	int 	m_CodePairNum;
	short	m_DisplayMode;
	short	m_EventFrequency;
	int	    m_PracTime;
	int	    m_ExperTime;
	int 	m_PracTimes;
	int 	m_ExperTimes;
	short   m_Background;
	int		m_iJoyMoveDirection;
	int     m_iPlanePos;
	short	m_Direction;
	short	m_SpeedMode;
	float	m_Speed;
	float	m_SpeedMin;
	float	m_SpeedMax;
	float   m_AccelerationMin;
	float   m_AccelerationMax;
	int		m_iTrack;
	int		m_iPlane;
	int		m_iHelicopter;
	int		m_iPresentTime;
	int		m_iIntervalMin;
	int		m_iIntervalMax;
	int		m_iReactTime;
};

//����4����
struct TaskSetting4
{
	char    m_TaskName[100];
	BOOL    m_PracMode;
	BOOL    m_ExperMode;
	short   m_TouchOrder;
	int     m_PracTimes;
	int     m_ExperTimes;
	short   m_Background;
};

//����5����
struct TaskSetting5
{
	char    m_TaskName[100];
	BOOL    m_PracMode;
	BOOL    m_ExperMode;
	BOOL    m_MainTask;
	BOOL    m_SubTask;
	float	m_InitSpeed;
	short	m_SignMemType;
	short	m_SignMemMode;
	int 	m_SignMemNum;
	short	m_SignShowMode;
	float  	m_SignShowTime;
	int	    m_PracTime;
	int	    m_ExperTime;
	int 	m_PracTimes;
	int 	m_ExperTimes;
	short	m_Background;
	int		m_iJoyMoveDirection;
};

//����6����
struct TaskSetting6
{
	char    m_TaskName[100];
	BOOL    m_PracMode;
	BOOL    m_ExperMode;
	BOOL    m_MainTask;
	BOOL    m_SubTask;
	float	m_InitSpeed;
	short	m_MemTaskMode;
	BOOL    m_CubeNum1;
    BOOL    m_CubeNum2;
    BOOL    m_CubeNum3;
    BOOL    m_CubeNum4;
    short	m_Prototype;
    short	m_RefAxis;
	int 	m_PracTime;
	int	    m_ExperTime;
	int 	m_PracTimes;
	int 	m_ExperTimes;
	short	m_Background;
	int		m_iJoyMoveDirection;
	int		m_iSubTaskInterval;
	int		m_iPresentTime;
	int		m_iReactTime;
	float	m_Speed;
	float	m_SpeedMin;
	float	m_SpeedMax;
	float   m_AccelerationMin;
	float   m_AccelerationMax;
	int		m_SpeedMode;
	int		m_Direction;
			

};

//����7����
struct TaskSetting7
{
	//Ŀǰ�õ���
	char    m_TaskName[200];

	BOOL    m_PracMode;
	BOOL    m_ExperMode;
	int		m_iSpeedMode;
	int		m_iBallColorR;
	int		m_iBallColorG;
	int		m_iBallColorB;
	int		m_iBallStartPos;
	int		m_iBallSpeed1;
	int		m_iBallSpeed2;
	int		m_iBallSpeed3;
	int		m_iTop;
	int		m_iBottom;
	int		m_iLeft;
	int		m_iRight;
	int		m_iBallSpeedAcc;
	int		m_iBallSpeedMax;
	int		m_iBallRadius;
	int     m_iBallCenterDis;
	int     m_iBckGrndColorR;
	int     m_iBckGrndColorG;
	int     m_iBckGrndColorB;
	int     m_iObstacleColorR;
	int     m_iObstacleColorG;
	int     m_iObstacleColorB;
	int     m_iObstacleRadius;
	int		m_iPracTimes;
	int		m_iExpTimes;
	int		m_iIntervalTime;


	
};

//task8
struct TaskSetting8 {
	bool m_bPracMode;
	int m_iFocusTime;//ע��ʱ��
	int m_iPresentTime;//����ʱ��
	int m_iCountdownTime;//����ʱ��
};

//Ӳ������
struct HardSetting
{
	float   m_JoySpeedMax;
	float   m_KnobSensitive;
	float   m_DistanceError;
	float   m_AngleError;
};

//��������Ϣ
struct PartInfo
{
	char    m_TesterNo[20];
	char    m_TesterName[20];
	char    m_TesterSex[10];
	short   m_TesterAge;
	UINT    m_Session;
};

//����㶨��
typedef struct
{
	short x,y;
}SPOINT;

//������ݸ˰�����Ӳ������Ķ�Ӧ��ϵ
#if JOY
const short KEY_YES = 7;//15;
const short KEY_NO = 5;//22;
const short KEY_A = 5;//1;
const short KEY_B = 3;//14;
const short KEY_C = 1;//0;
const short KEY_D = 4;//8;
const short KEY_E = 2;//21;
const short KEY_F = 0;//7;
const short TOUCH_A1 = 13;//10;//2;
const short TOUCH_A2 = 12;//3;//9;
const short TOUCH_A3 = 11;//23;//16;
const short TOUCH_A4 = 10;//16;//23;
const short TOUCH_A5 = 9;//9;//3;
const short TOUCH_A6 = 8;//2;//10;
const short TOUCH_B1 = 14;//17;//5;//
const short TOUCH_B2 = 15;//6;//18;
const short TOUCH_B3 = 16;//4;//11;
const short TOUCH_B4 = 17;//11;//4;
const short TOUCH_B5 = 18;//18;//6;//
const short TOUCH_B6 = 19;//5;//17;
#else 
//������̰�����Ӳ������Ķ�Ӧ��ϵ
const short KEY_YES = DIK_A;
const short KEY_NO = DIK_S;
const short KEY_A = DIK_1;
const short KEY_B = DIK_2;
const short KEY_C = DIK_3;
const short KEY_D = DIK_Q;
const short KEY_E = DIK_W;
const short KEY_F = DIK_E;
const short TOUCH_A1 = DIK_1;//2;
const short TOUCH_A2 = DIK_2;//9;
const short TOUCH_A3 = DIK_3;//16;
const short TOUCH_A4 = DIK_4;//23;
const short TOUCH_A5 = DIK_5;//3;
const short TOUCH_A6 = DIK_6;//10;
const short TOUCH_B1 = DIK_Q;//5;//
const short TOUCH_B2 = DIK_W;//18;
const short TOUCH_B3 = DIK_E;//11;
const short TOUCH_B4 = DIK_R;//4;
const short TOUCH_B5 = DIK_T;//6;//
const short TOUCH_B6 = DIK_Y;//17;
#endif

const short m_StartKey[8] = {KEY_YES,KEY_NO,KEY_A,KEY_B,KEY_C,KEY_D,KEY_E,KEY_F};    //��ʼ�����
const short m_CodeKey[6] = {KEY_A,KEY_B,KEY_C,KEY_D,KEY_E,KEY_F};                    //�����
const short m_EventKey[2] = {KEY_YES,KEY_NO};                                        //Yes����No��
const short m_TouchKey[12] = {TOUCH_A1,TOUCH_A2,TOUCH_A3,TOUCH_A4,TOUCH_A5,TOUCH_A6, 
    TOUCH_B1,TOUCH_B2,TOUCH_B3,TOUCH_B4,TOUCH_B5,TOUCH_B6};                          //�����

//ȷ�ϼ�����
enum SUREDOWN_TYPE
{ 
    SUREDOWN_YES,       //YES
    SUREDOWN_NO
};

//���������
enum TOUCHDOWN_TYPE
{ 
    TOUCHDOWN_A1,       //YES
    TOUCHDOWN_A2,
	TOUCHDOWN_A3,
	TOUCHDOWN_A4,
	TOUCHDOWN_A5,
	TOUCHDOWN_A6,
	TOUCHDOWN_B1,
	TOUCHDOWN_B2,
	TOUCHDOWN_B3,
	TOUCHDOWN_B4,
	TOUCHDOWN_B5,
	TOUCHDOWN_B6
};

const short m_SureDownType[2] = {SUREDOWN_YES,SUREDOWN_NO};
const short m_TouchDownType[12] = {TOUCHDOWN_A1,TOUCHDOWN_A2,TOUCHDOWN_A3,TOUCHDOWN_A4,TOUCHDOWN_A5,TOUCHDOWN_A6,
	TOUCHDOWN_B1,TOUCHDOWN_B2,TOUCHDOWN_B3,TOUCHDOWN_B4,TOUCHDOWN_B5,TOUCHDOWN_B6};

//��������
enum TRIAL_TYPE
{ 
    TRIAL_PRACTICE,              //��ϰ
    TRIAL_EXPERMENT              //��ʽ
};

//����ִ��״̬
enum STATE_TYPE
{ 
    STATE_DISPLAYINSTURCTION,       //����ָ����
	STATE_DISPLAYOBJ,               //���ֱ��뷽ʽ
    STATE_MOVINGOBJ,                //���ֱ���
	STATE_ENTERNUMBER,              //��������
	STATE_DISPLAYFEEDBACK,          //���ַ���
    STATE_DISPLAYNEXT,              //����ѡ���
    STATE_DISPLAYOPTION,            //����ѡ���
	STATE_OVER,                     //����
	STATE_EXIT,                      //�����˳�
	STATE_NEXT,                      //��һ������
	
	// ����8
	STATE_EXERCISE,						// ��ϰ����״̬
	STATE_FORMAL,						// ��ʽ����״̬
	STATE_FOCUS,						// ע��״̬
	STATE_PAUSE,						// ��ͣ״̬
	STATE_BETWEEN_EXERCISE_AND_FORMAL	// ��ϰ����ʽ����״̬
};

//�������������ֵĶ�Ӧ��ϵ
const char	m_TrackStr[3][10] = {"Բ��","��Բ��","������"};
const char	m_DirectionStr[2][10] = {"����","����"};
const char	m_MoveModeStr[2][10] = {"ƽ��","ƽ��+��ת"};
const char	m_SpeedModeStr[2][10] = {"����","����"};
const char	m_BackgroundStr[3][10] = {"�Һ�ɫ","����ɫ","��Խ�ǿ�"};
const char	m_MainTaskModeStr[2][10] = {"Ŀ�����","���ֱ���"};
const char	m_EventModeStr[2][12] = {"�򵥷�Ӧʱ","ѡ��Ӧʱ"};
const char	m_CodePairModeStr[2][10] = {"�̶���Ŀ","������"};
const char	m_TouchOrderStr[2][10] = {"��ֱ","ˮƽ"};
const char	m_DisplayModeStr[2][12] = {"ȷ�Ϻ���ʧ","һֱ����"};
const char	m_SignMemTypeStr[3][10] = {"�ַ�","ͼ��","ͼƬ"};
const char	m_SignMemModeStr[2][10] = {"�̶���Ŀ","������"};
const char	m_SignShowModeStr[2][10] = {"����ȷ��","�̶�ʱ��"};
const char	m_MemTaskModeStr[2][10] = {"�б�Ƚ�","�����б�"};
const char	m_RefAxisStr[3][10] = {"X��","Y��","Z��"};
