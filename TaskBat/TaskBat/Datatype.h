#pragma once
#include <dinput.h>

//定义使用操纵杆或键盘 0-键盘，1-操纵杆
#define JOY 1

enum{BTN_DOWN, BTN_UP};
enum KEYMAP{KEY8,KEY6,KEY7,KEY4,KEY2,KEY5,KEY3,KEY1};
enum{LEFT, TOP,RIGHT,BOTTOM,RANDOM};
enum PLANE_POS{LEFT_TOP = 1,RIGHT_TOP = 2,RIGHT_BOTTOM = 4,LEFT_BOTTOM = 8};
enum{BALL_SPEED_CONSTANT, BALL_SPEED_ACC};

//运动轨迹类型
enum TRACE_TYPE
{
	TRACK_CIRCLE,  //圆形
	TRACK_ELLIPSE, //椭圆形
	TRACK_EIGHT    //八字形
};

//背景颜色
enum BACKGROUND_TYPE
{
	BACKGROUND_GRAY,  //蓝灰色
	BACKGROUND_BLACK, //黑灰色
	BACKGROUND_STAR   //飞越星空
};

//运动方式
enum MOVE_MODE
{
	MODE_MOVE,       //平移
	MODE_MOVEROATE   //平移+旋转
};

const double PI = 3.1415927;

//任务1设置
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

//任务2设置
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

//任务3设置
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

//任务4设置
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

//任务5设置
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

//任务6设置
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

//任务7设置
struct TaskSetting7
{
	//目前用到的
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
	int m_iFocusTime;//注视时间
	int m_iPresentTime;//呈现时间
	int m_iCountdownTime;//倒数时间
};

//硬件设置
struct HardSetting
{
	float   m_JoySpeedMax;
	float   m_KnobSensitive;
	float   m_DistanceError;
	float   m_AngleError;
};

//被试者信息
struct PartInfo
{
	char    m_TesterNo[20];
	char    m_TesterName[20];
	char    m_TesterSex[10];
	short   m_TesterAge;
	UINT    m_Session;
};

//坐标点定义
typedef struct
{
	short x,y;
}SPOINT;

//定义操纵杆按键和硬件输入的对应关系
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
//定义键盘按键和硬件输入的对应关系
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

const short m_StartKey[8] = {KEY_YES,KEY_NO,KEY_A,KEY_B,KEY_C,KEY_D,KEY_E,KEY_F};    //开始任意键
const short m_CodeKey[6] = {KEY_A,KEY_B,KEY_C,KEY_D,KEY_E,KEY_F};                    //编码键
const short m_EventKey[2] = {KEY_YES,KEY_NO};                                        //Yes键、No键
const short m_TouchKey[12] = {TOUCH_A1,TOUCH_A2,TOUCH_A3,TOUCH_A4,TOUCH_A5,TOUCH_A6, 
    TOUCH_B1,TOUCH_B2,TOUCH_B3,TOUCH_B4,TOUCH_B5,TOUCH_B6};                          //触点键

//确认键类型
enum SUREDOWN_TYPE
{ 
    SUREDOWN_YES,       //YES
    SUREDOWN_NO
};

//触点键类型
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

//测试类型
enum TRIAL_TYPE
{ 
    TRIAL_PRACTICE,              //练习
    TRIAL_EXPERMENT              //正式
};

//测试执行状态
enum STATE_TYPE
{ 
    STATE_DISPLAYINSTURCTION,       //呈现指导语
	STATE_DISPLAYOBJ,               //呈现编码方式
    STATE_MOVINGOBJ,                //呈现编码
	STATE_ENTERNUMBER,              //输入数字
	STATE_DISPLAYFEEDBACK,          //呈现反馈
    STATE_DISPLAYNEXT,              //出现选项框
    STATE_DISPLAYOPTION,            //出现选项框
	STATE_OVER,                     //结束
	STATE_EXIT,                      //程序退出
	STATE_NEXT,                      //下一个任务
	
	// 任务8
	STATE_EXERCISE,						// 练习任务状态
	STATE_FORMAL,						// 正式任务状态
	STATE_FOCUS,						// 注视状态
	STATE_PAUSE,						// 暂停状态
	STATE_BETWEEN_EXERCISE_AND_FORMAL	// 练习和正式任务状态
};

//上述变量和文字的对应关系
const char	m_TrackStr[3][10] = {"圆形","椭圆形","八字形"};
const char	m_DirectionStr[2][10] = {"正向","反向"};
const char	m_MoveModeStr[2][10] = {"平移","平移+滚转"};
const char	m_SpeedModeStr[2][10] = {"匀速","变速"};
const char	m_BackgroundStr[3][10] = {"灰黑色","蓝黑色","飞越星空"};
const char	m_MainTaskModeStr[2][10] = {"目标跟踪","数字编码"};
const char	m_EventModeStr[2][12] = {"简单反应时","选择反应时"};
const char	m_CodePairModeStr[2][10] = {"固定数目","逐步增加"};
const char	m_TouchOrderStr[2][10] = {"垂直","水平"};
const char	m_DisplayModeStr[2][12] = {"确认后消失","一直呈现"};
const char	m_SignMemTypeStr[3][10] = {"字符","图标","图片"};
const char	m_SignMemModeStr[2][10] = {"固定数目","逐步增加"};
const char	m_SignShowModeStr[2][10] = {"按键确认","固定时长"};
const char	m_MemTaskModeStr[2][10] = {"判别比较","记忆判别"};
const char	m_RefAxisStr[3][10] = {"X轴","Y轴","Z轴"};
