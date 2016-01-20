#pragma once
#include <string>
#include "resource.h"
#include "Datatype.h"
#include <string>
#include "stdafx.h"
#include "TaskBat.h"
#include <stdio.h> 
#include <direct.h>
#include <atlstr.h>
#include "Task1.h"
#include "Task2.h"
#include "Task3_1.h"
#include "Task6_1.h"
#include "Task6_2.h"
#include "Task7.h"

#define MAX_LOADSTRING 100

void exeTasks(HWND &hWnd, HINSTANCE &hInstance, const int &m_CurTaskCount, char m_TaskExe[][10], char m_TaskName[][100], PartInfo &m_CurPartInfo);
