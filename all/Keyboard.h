#pragma once
#include <dinput.h>

extren LPDIRECTINPUT8         m_lpkDI;// = NULL;
extren LPDIRECTINPUTDEVICE8   m_lpkDKB;// = NULL;
extren char buffer[256];
BOOL KeyboardInit (HWND hWindow, int iMin, int iMax, int iDeadZone);
BOOL KeyboardUpdate (void);
BOOL IsKeyDown (int iButton);
BOOL IsKeyUp (int iButton);
int GetXAxis (void);
int GetYAxis (void);
int GetZAxis (void);
