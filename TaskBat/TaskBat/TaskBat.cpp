// TaskBat.cpp : Defines the entry point for the application.
//
#include "stdafx.h"

#include "TaskBat.h"

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

HWND myhWnd;

////��������Ϣ
//struct PartInfo
//{
//	char    m_TesterNo[20];
//	char    m_TesterName[20];
//	char    m_TesterSex[10];
//	short   m_TesterAge;
//	UINT    m_Session;
//};
const char* szTaskName[]={"[Task1(����1-Ŀ�������������)]\n","[Task2(����2-���������ּ�ʱ��֪����������)]\n","[Task3(����3-˫����ģʽͻ���¼���Ӧʱ����)]\n",
"[Task6(����6-˫����ģʽ��άͼ�μ����б���������)]\n","[Task7(����7-�ٶ�֪����������)]\n"};
const int iTaskIdx[]={1,2,3,6,7};

int findRight(const char* szTaskName)
{
	for(int i = 0; i < strlen(szTaskName); i++)
	{
		if (szTaskName[i] == ')')
			return i + 1;
	}
}




int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	int m_CurTaskCount = 0;
	char m_TaskExe[50][10];
	char m_TaskName[50][100];
	struct PartInfo      m_CurPartInfo;
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	int i, j;
	HANDLE hProcess;
	PROCESS_INFORMATION PI;
	STARTUPINFO SI;
	char m_file[500];
	FILE *sfp, *dfp;
	char m_BatFile[50];
	char TmpLine[100];
	char DTmpLine[100];
	BOOL bExeName;
	BOOL bTaskName;
	strcpy(m_BatFile, lpCmdLine);

	TCHAR szPath[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, szPath, MAX_PATH);

	int pos;
	for (i = 0; i < strlen(szPath); i++)
	{
		//��Ӧ�ó����ļ����зֳ���
		if (szPath[i] == 92)
			pos = i;
	}

	//�зֳ������� ���ڽ��������߱�� ���������� 
	TCHAR szFilename[100] = { 0 };
	strncpy(szFilename, szPath + pos + 1, strlen(szPath) - pos);
	int pos2;
	for (i = 0; i < strlen(szFilename); i++)
	{
		if (szFilename[i] == '-')
			pos = i;
		if (szFilename[i] == '.')
			pos2 = i;
	}


	strncpy(m_CurPartInfo.m_TesterNo, szFilename, pos);
	m_CurPartInfo.m_TesterNo[pos] = 0;
	strncpy(m_CurPartInfo.m_TesterName, szFilename + pos + 1, pos2 - pos - 1);
	m_CurPartInfo.m_TesterName[pos2 - pos - 1] = 0;

	TCHAR szSetPath[MAX_PATH] = { 0 };


	sprintf(szSetPath, "Settings\\%s-%s\\TaskSetting.set", m_CurPartInfo.m_TesterNo, m_CurPartInfo.m_TesterName);

	CopyFile(szSetPath, "Settings\\TaskSetting.set", FALSE);

	dfp = fopen("Settings\\TaskSetting.set", "r");
	if (dfp != NULL)
	{
		fgets(TmpLine, 100, dfp);
		fgets(TmpLine, 100, dfp);


		while (!feof(dfp))
		{
			//�зֳ�����������ת��ΪӦ�ó��������
			for (int i = 0; i < sizeof(szTaskName) / sizeof(char*); i++)
			{

				if (strcmp(szTaskName[i], TmpLine) == 0)
				{
					fgets(TmpLine, 100, dfp);

					sscanf(TmpLine, "TaskName\t%s\n", m_TaskName[m_CurTaskCount]);

					if (i != 2 && i != 3)
						sprintf(m_TaskExe[m_CurTaskCount], "Task%d", iTaskIdx[i]);

					//TASK3
					else if (i == 2)
						sprintf(m_TaskExe[m_CurTaskCount], "Task3_1");

					//TASK6 д������������Task6_1��Task6_2
					else if (i == 3)
					{
						fgets(TmpLine, 100, dfp);
						while (strstr(TmpLine, "MemTaskMode") == NULL)
							fgets(TmpLine, 100, dfp);
						int MemTaskMode;
						sscanf(TmpLine, "MemTaskMode\t%d", &MemTaskMode);

						if (MemTaskMode == 0)
							sprintf(m_TaskExe[m_CurTaskCount], "Task6_1");
						else
							sprintf(m_TaskExe[m_CurTaskCount], "Task6_2");

					}

					m_CurTaskCount++;
					break;

				}


			}

			fgets(TmpLine, 100, dfp);


		}

		fclose(dfp);
	}



	if (true)
	{
		HWND hWnd = NULL;
		exeTasks(hWnd, hInstance, m_CurTaskCount, m_TaskExe, m_TaskName, m_CurPartInfo);
	}
	else
	{
		DWORD exitCode;
		for (i = 0; i < m_CurTaskCount; i++)
		{
			memset(&SI, 0, sizeof(SI));
			SI.cb = sizeof(SI);
			sprintf_s(m_file, "%s.exe %s %s-%s-%d", m_TaskExe[i], m_TaskName[i], m_CurPartInfo.m_TesterNo, m_CurPartInfo.m_TesterName, 0);
			if (CreateProcess(NULL, m_file, NULL, NULL, TRUE, CREATE_NEW_PROCESS_GROUP | CREATE_DEFAULT_ERROR_MODE, NULL, NULL, &SI, &PI))
			{
				// Wait until child process exits.  


				HWND hWnd = FindWindow(_T("Shell_TrayWnd"), NULL);

				//����IDΪ0x1F5��Win + M����WM_HOTKEY��Ϣ
				SendMessage(hWnd, WM_HOTKEY, 0x1F5, 0);

				char szTaskExe[50] = { 0 };
				if (strcmp(m_TaskExe[i], "Task3_1") == 0)
					strcpy(szTaskExe, "Task3");

				else if (strcmp(m_TaskExe[i], "Task6_1") == 0 || strcmp(m_TaskExe[i], "Task6_2") == 0)
					strcpy(szTaskExe, "Task6");

				else
					strcpy(szTaskExe, m_TaskExe[i]);

				hWnd = FindWindow(NULL, szTaskExe);
				while (hWnd == NULL)
					hWnd = FindWindow(NULL, szTaskExe);

				SetActiveWindow(hWnd);
				SetForegroundWindow(hWnd);
				BringWindowToTop(hWnd);
				SetCursorPos(100, 200);//�ƶ���ĳ������
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//�������

				WaitForSingleObject(PI.hProcess, INFINITE);

				GetExitCodeProcess(PI.hProcess, &exitCode);


				CloseHandle(PI.hProcess);
				CloseHandle(PI.hThread);


				if (ID_CANCEL == exitCode)
					break;
			}

		}
	}
	

	return 0;

}


//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TASKBAT));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_TASKBAT);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   //ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   myhWnd = hWnd;

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void destroyWinClass(HINSTANCE hInstance)
{
	//ע��������
	UnregisterClass("ClassName", hInstance);
}

// ִ�������б��е�����
void exeTasks(HWND &hWnd, HINSTANCE &hInstance,
	const int &m_CurTaskCount, char m_TaskExe[][10], char m_TaskName[][100], PartInfo &m_CurPartInfo)
{
	std::string curWinClassName = "";
	std::string lastWinClassName = "";
	std::string lastWinName = "";
	int x_resolution, y_resolution, rec_x_begin, rec_y_begin, rec_x_end, rec_y_end;
	char cmdPara[500];
	int b_IsExit;
	for (size_t i = 0; i < m_CurTaskCount; i++)
	{
		b_IsExit = STATE_DISPLAYINSTURCTION;
		sprintf_s(cmdPara, "%s %s-%s-%d", m_TaskName[i], m_CurPartInfo.m_TesterNo, m_CurPartInfo.m_TesterName, 0);
		std::string task = m_TaskExe[i];
		//if (true) continue;
		if (task == "Task1")
		{
			//curWinClassName = "ClassName1";
			HINSTANCE hPrevInstance = NULL;
			LPTSTR    lpCmdLine = cmdPara;
			int nCmdShow = i;
			t1::_tWinMain(hInstance, hPrevInstance, 
				lpCmdLine, nCmdShow, hWnd, lastWinClassName, lastWinName);
			lastWinClassName = std::to_string(nCmdShow).c_str();
			lastWinName = std::to_string(nCmdShow).c_str();
			b_IsExit = t1::m_TestState;
			if (b_IsExit == STATE_EXIT)
				break;
		}
		else if (task == "Task2")
		{
			//curWinClassName = "ClassName2";
			HINSTANCE hPrevInstance = NULL;
			LPTSTR    lpCmdLine = cmdPara;
			int nCmdShow = i;
			t2::_tWinMain(hInstance, hPrevInstance,
				lpCmdLine, nCmdShow, hWnd, lastWinClassName, lastWinName);
			lastWinClassName = std::to_string(nCmdShow).c_str();
			lastWinName = std::to_string(nCmdShow).c_str();
			b_IsExit = t2::m_TestState;
			if (b_IsExit == STATE_EXIT)
				break;
		}
		else if (task == "Task3_1")
		{
			//curWinClassName = "ClassName3";
			HINSTANCE hPrevInstance = NULL;
			LPTSTR    lpCmdLine = cmdPara;
			int nCmdShow = i;
			t3::_tWinMain(hInstance, hPrevInstance,
				lpCmdLine, nCmdShow, hWnd, lastWinClassName, lastWinName);
			lastWinClassName = std::to_string(nCmdShow).c_str();
			lastWinName = std::to_string(nCmdShow).c_str();
			b_IsExit = t3::m_TestState;
			if (b_IsExit == STATE_EXIT)
				break;
		}
		else if (task == "Task6_1")
		{
			//curWinClassName = "ClassName6_1";
			HINSTANCE hPrevInstance = NULL;
			LPTSTR    lpCmdLine = cmdPara;
			int nCmdShow = i;
			t6_1::_tWinMain(hInstance, hPrevInstance,
				lpCmdLine, nCmdShow, hWnd, lastWinClassName, lastWinName);
			lastWinClassName = std::to_string(nCmdShow).c_str();
			lastWinName = std::to_string(nCmdShow).c_str();
			b_IsExit = t6_1::m_TestState;
			if (b_IsExit == STATE_EXIT)
				break;
		}
		else if (task == "Task6_2")
		{
			//curWinClassName = "ClassName6_2";
			HINSTANCE hPrevInstance = NULL;
			LPTSTR    lpCmdLine = cmdPara;
			int nCmdShow = i;
			t6_2::_tWinMain(hInstance, hPrevInstance,
				lpCmdLine, nCmdShow, hWnd, lastWinClassName, lastWinName);
			lastWinClassName = std::to_string(nCmdShow).c_str();
			lastWinName = std::to_string(nCmdShow).c_str();
			b_IsExit = t6_2::m_TestState;
			if (b_IsExit == STATE_EXIT)
				break;
		}
		else if (task == "Task7")
		{
			//curWinClassName = "ClassName7";
			HINSTANCE hPrevInstance = NULL;
			LPTSTR    lpCmdLine = cmdPara;
			int nCmdShow = i;
			t7::_tWinMain(hInstance, hPrevInstance,
				lpCmdLine, nCmdShow, hWnd, lastWinClassName, lastWinName);
			lastWinClassName = std::to_string(nCmdShow).c_str();
			lastWinName = std::to_string(nCmdShow).c_str();
			b_IsExit = t7::m_TestState;
			if (b_IsExit == STATE_EXIT)
				break;
		}
		else
		{
			MessageBox(myhWnd, "����", "û�д������񣡵���˳�", MB_OK);
			exit(1);
		}

		if (b_IsExit != STATE_EXIT)
		{
			Sleep(500);
		}
		
	}
	if (b_IsExit == STATE_EXIT)
	{
		MessageBox(myhWnd, "�����������!", "����Э��ʵ��", MB_OK);
	}
	
}



