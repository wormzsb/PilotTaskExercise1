#include "stdafx.h"

#include <stdio.h>
#include <dinput.h>
#include "Datatype.h"
#include "Input.h"

LPDIRECTINPUT8         m_lpkDInput = NULL;
LPDIRECTINPUTDEVICE8 m_lpkDIDevice = NULL;
DIJOYSTATE2          m_kDeviceData;

char m_strKeyState[256];

//short m_InputType = 0; 
//static int rt = 0;

 /* Enumeration function */
BOOL CALLBACK EnumJoysticksCallback(
          const DIDEVICEINSTANCE *pdidInstance, VOID* pContext)
{
    LPDIRECTINPUTDEVICE8 * lpkDevice = (LPDIRECTINPUTDEVICE8 *) pContext;
 
    /* Create joystick device */
    if (FAILED(m_lpkDInput->CreateDevice (
             pdidInstance->guidInstance, lpkDevice, NULL)) )
	{
        return DIENUM_CONTINUE;
	}
    else
	{
        return DIENUM_STOP;
	}
}

BOOL JoystickInit (HWND hWindow, int iMin, int iMax,
                            int iDeadZone)
{
	if(JOY)
	{
	    /* Find first available joystick */
		if (FAILED (m_lpkDInput->EnumDevices (
				 DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, &m_lpkDIDevice, 
				 DIEDFL_ATTACHEDONLY)) )
		{
			return FALSE;
		}
 
		/* Set joystick data format */
		if(m_lpkDIDevice == NULL)
		{
			return FALSE;
		}

		if (FAILED(m_lpkDIDevice->SetDataFormat (&c_dfDIJoystick2)))
		{
			return FALSE;
		}
 
	  /* Set joystick cooperative level */
		if (FAILED(m_lpkDIDevice->SetCooperativeLevel (hWindow, 
				DISCL_EXCLUSIVE | DISCL_FOREGROUND)))
		{
			return FALSE;
		}
 
	  /* Set joystick axis ranges */
		DIPROPRANGE kDIRange; 
 
		kDIRange.diph.dwSize       = sizeof(DIPROPRANGE); 
		kDIRange.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
		kDIRange.diph.dwHow        = 0; 
		kDIRange.diph.dwObj        = DIPH_DEVICE; 
		kDIRange.lMin              = iMin; 
		kDIRange.lMax              = iMax; 
 
		if (FAILED(m_lpkDIDevice->SetProperty (DIPROP_RANGE, &kDIRange.diph)))
		{
			return FALSE;
		}

	  /* Set joystick dead zone */
		DIPROPDWORD kDIDeadZone; 
 
		kDIDeadZone.diph.dwSize       = sizeof(DIPROPDWORD); 
		kDIDeadZone.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
		kDIDeadZone.diph.dwHow        = 0; 
		kDIDeadZone.diph.dwObj        = DIPH_DEVICE; 
		kDIDeadZone.dwData            = iDeadZone * 100; 
 
		if (FAILED (m_lpkDIDevice->SetProperty (DIPROP_DEADZONE,
											 &kDIDeadZone.diph)) )
		{
			return FALSE;
		}
 
	  /* Acquire joystick */
		HRESULT hRet = m_lpkDIDevice->Poll (); 
		if (FAILED (hRet)) 
		{
			hRet = m_lpkDIDevice->Acquire ();
  
			while (hRet == DIERR_INPUTLOST) 
			{
				hRet = m_lpkDIDevice->Acquire ();
			}
		}
		return TRUE;
	}
	else
	{
		if (FAILED(m_lpkDInput->CreateDevice (
			GUID_SysKeyboard, &m_lpkDIDevice, NULL)) )
		{
			return FALSE;
		}
		
		if (FAILED(m_lpkDIDevice->SetDataFormat (&c_dfDIKeyboard)))
		{
			return FALSE;
		}
 
		/* Set joystick cooperative level */
		if (FAILED(m_lpkDIDevice->SetCooperativeLevel (hWindow, 
				DISCL_EXCLUSIVE | DISCL_FOREGROUND)))
		{
			return FALSE;
		}

		/* Acquire joystick */
		HRESULT hRet = m_lpkDIDevice->Poll (); 
		if (FAILED (hRet)) 
		{
			hRet = m_lpkDIDevice->Acquire ();
  
			while (hRet == DIERR_INPUTLOST) 
			{
				hRet = m_lpkDIDevice->Acquire ();
			}
		}
		return TRUE;
	}
}

 /* Update joystick status */
BOOL JoystickUpdate (void)
{
  /* Poll the joystick */
    if (FAILED (m_lpkDIDevice->Poll ()) )  
	{
   /* Acquire joystick */
        HRESULT hRet = m_lpkDIDevice->Acquire ();

        if ((FAILED (hRet)) && (hRet == DIERR_INPUTLOST))
		{
            m_lpkDIDevice->Acquire ();
		}
        else
		{
            return FALSE;
		}
	}
 
    if(JOY)
	{
		/* Get device data */
		if (FAILED (m_lpkDIDevice->GetDeviceState (sizeof (DIJOYSTATE2),
												&m_kDeviceData)) )
		{
			return FALSE;
		}
	}
	else
	{
		if (FAILED (m_lpkDIDevice->GetDeviceState (sizeof (m_strKeyState),
												&m_strKeyState)) )
		{
			return FALSE;
		}
	}
    return TRUE; 
}

 /* Returns if a button is down */
BOOL IsButtonDown (int iButton)
{
    if(JOY)
	{
		/* Check if button is pressed */
		if (m_kDeviceData.rgbButtons [iButton] & (1<<7))
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		if(m_strKeyState[iButton] & 0x80) 
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
}

 /* Returns if a button is up */
BOOL IsButtonUp (int iButton)
{
	if(JOY)
	{
		/* Check if button isn't pressed */
		if (m_kDeviceData.rgbButtons [iButton] & (1<<7))
		{
			return FALSE;
		}
		else
		{
			return TRUE;
		}
	}
	else
	{
		if(m_strKeyState[iButton] & 0x80) 
		{
			return FALSE;
		}
		else
		{
			return TRUE;
		}
	}
}

 /* Returns joystick horizontal axis */
int GetXAxis (void)
{
	if(JOY)
	{
		//printf("\n m_kDeviceData.lX = %d\n", m_kDeviceData.lX);
		return m_kDeviceData.lX;
	}
    else
	{
		if(m_strKeyState[DIK_LEFTARROW] & 0x80) 
		{
			rt = -600;
			return rt;
		}
		else if(m_strKeyState[DIK_RIGHTARROW] & 0x80) 
		{
			rt = 600;
			return rt;
		}
		else
		{
			return 0;
		}
	}
}
 
 /* Returns joystick vertical axis */
int GetYAxis (void)
{
	if(JOY)
	{
        return m_kDeviceData.lY;
	}
    else
	{
		if(m_strKeyState[DIK_UPARROW] & 0x80) 
		{
			return -600;
		}
		else if(m_strKeyState[DIK_DOWNARROW] & 0x80) 
		{
			return 600;
		}
		else
		{
            return 0;
		}
	}
}

 /* Returns joystick vertical axis */
int GetZAxis (void)
{
	if(JOY)
	{
        return m_kDeviceData.lRz;
	}
	else
	{
        if(m_strKeyState[DIK_Z] & 0x80) 
		{
			return -100;
		}
		else if(m_strKeyState[DIK_X] & 0x80) 
		{
			return 100;
		}
		else
		{
            return 0;
		}
	}
}

BOOL HasBtnDown(int preKeyPress)
{
	if (preKeyPress == -1)
		return FALSE;

	//若上一个键没有弹起则重新不做任何事
	if(IsButtonDown(preKeyPress))
	{
		return TRUE;
	}
	

	return FALSE;
}