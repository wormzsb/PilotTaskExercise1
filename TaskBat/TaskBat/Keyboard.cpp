#include <dinput.h>
#include "Keyboard.h"
#include "stdafx.h"
#include <direct.h>
#include <d3d9.h>
#include <d3dx9.h>
LPDIRECTINPUT8 m_lpkDI=NULL;
LPDIRECTINPUTDEVICE8 m_lpkDKB=NULL;
char buffer[256];

BOOL KeyboardInit (HWND hWindow, int iMin, int iMax,
                            int iDeadZone)
{
    if (FAILED(m_lpkDI->CreateDevice (
        pdidInstance->guidInstance, m_lpkDKB, NULL)) )
	{
        return DIENUM_CONTINUE;
	}
    else
	{
        return DIENUM_STOP;
	}

    if (FAILED(m_lpkDKB->SetDataFormat (&c_dfDIKeyboard)))
	{
        return FALSE;
	}
 
    /* Acquire joystick */
    HRESULT hRet = m_lpkDKB->Poll (); 
    if (FAILED (hRet)) 
	{
        hRet = m_lpkDKB->Acquire ();
  
        while (hRet == DIERR_INPUTLOST) 
		{
            hRet = m_lpkDKB->Acquire ();
		}
	}
    return TRUE;
}

 /* Update Keyboard status */
BOOL KeyboardUpdate (void)
{
  /* Poll the Keyboard */
    if (FAILED (m_lpkDKB->Poll ()) )  
	{
   /* Acquire Keyboard */
        HRESULT hRet = m_lpkDKB->Acquire ();

        if ((FAILED (hRet)) && (hRet == DIERR_INPUTLOST))
		{
            m_lpkDKB->Acquire ();
		}
        else
		{
            return FALSE;
		}
	}
 
    /* Get device data */
    if (FAILED (m_lpkDIDevice->GetDeviceState (sizeof (DIJOYSTATE2),
                                            &m_kDeviceData)) )
	{
        return FALSE;
	}
    return TRUE; 
}

 /* Returns if a button is down */
BOOL IsKeyDown (int iButton)
{
    /* Check if button is pressed */
	if(iButton == 5)
	{
		if (m_kDeviceData.rgdwPOV[0] == JOY_POVRIGHT)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else if(iButton == 6)
	{
		if (m_kDeviceData.rgdwPOV[0] == JOY_POVFORWARD)
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
		if (m_kDeviceData.rgbButtons [iButton] & (1<<7))
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
BOOL IsKeyUp (int iButton)
{
  /* Check if button isn't pressed */
	if(iButton == 5)
	{
		if (m_kDeviceData.rgdwPOV[0] == JOY_POVRIGHT)
		{
			return FALSE;
		}
		else
		{
			return TRUE;
		}
	}
	else if(iButton == 6)
	{
		if (m_kDeviceData.rgdwPOV[0] == JOY_POVFORWARD)
		{
			return FALSE;
		}
		else
		{
			return TRUE;
		}
	}
    if (m_kDeviceData.rgbButtons [iButton] & (1<<7))
	{
        return FALSE;
	}
	else
	{
		return TRUE;
	}
}

 /* Returns joystick horizontal axis */
int GetXAxis (void)
{
    return m_kDeviceData.lX;
}
 
 /* Returns joystick vertical axis */
int GetYAxis (void)
{
    return m_kDeviceData.lY;
}

 /* Returns joystick vertical axis */
int GetZAxis (void)
{
    return m_kDeviceData.lRz;
}