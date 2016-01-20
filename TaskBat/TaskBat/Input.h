#pragma once
#include <dinput.h>
#include "Datatype.h"
extern LPDIRECTINPUT8         m_lpkDInput;// = NULL;
extern LPDIRECTINPUTDEVICE8 m_lpkDIDevice;// = NULL;
extern DIJOYSTATE2          m_kDeviceData;

extern char m_strKeyState[256];

//short m_InputType = 0; 
static int rt = 0;
 /* Enumeration function */
BOOL CALLBACK EnumJoysticksCallback(
          const DIDEVICEINSTANCE *pdidInstance, VOID* pContext);

BOOL JoystickInit (HWND hWindow, int iMin, int iMax,
                            int iDeadZone);


 /* Update joystick status */
BOOL JoystickUpdate (void);

 /* Returns if a button is down */
BOOL IsButtonDown (int iButton);

 /* Returns if a button is up */
BOOL IsButtonUp (int iButton);

 /* Returns joystick horizontal axis */
int GetXAxis (void);
 
 /* Returns joystick vertical axis */
int GetYAxis (void);

 /* Returns joystick vertical axis */
int GetZAxis (void);

BOOL HasBtnDown(int preKeyPress);