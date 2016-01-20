#pragma once
#include "stdafx.h"
#include <dinput.h>
#include <direct.h>
#include <d3d9.h>
#include <d3dx9.h>

extern LPDIRECTINPUT8 m_lpkDI;// = NULL;
extern LPDIRECTINPUTDEVICE8   m_lpkDKB;// = NULL;
extern char buffer[256];
BOOL KeyboardInit (HWND hWindow, int iMin, int iMax, int iDeadZone);
BOOL KeyboardUpdate (void);
BOOL IsKeyDown (int iButton);
BOOL IsKeyUp (int iButton);
int GetXAxis (void);
int GetYAxis (void);
int GetZAxis (void);
