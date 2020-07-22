#include "pch.h"
#include "Basedef.h"
#include "TMGlobal.h"

HWND hWndMain;
char EncodeByte[4];

float BASE_ScreenResize(float size)
{
	return (float)((float)g_pDevice->m_dwScreenWidth * (float)(size / 800.0f));
}
