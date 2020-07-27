#include "pch.h"
#include "Basedef.h"
#include "TMGlobal.h"

HWND hWndMain;
char EncodeByte[4];
int g_nChannelWidth;
int g_nServerGroupNum;
char g_pServerList[MAX_SERVERGROUP][MAX_SERVERNUMBER][64];
int g_nSelServerWeather;
char g_pMessageStringTable[MAX_STRING][MAX_STRING_LENGTH];

float BASE_ScreenResize(float size)
{
	return (float)((float)g_pDevice->m_dwScreenWidth * (float)(size / 800.0f));
}

void BASE_InitModuleDir()
{
}

void BASE_InitializeHitRate()
{
}

void BASE_ApplyAttribute(char* pHeight, int size)
{
}

int BASE_ReadMessageBin()
{
	return 0;
}

void BASE_InitEffectString()
{
}

int BASE_InitializeBaseDef()
{
	return 1;
}

void BASE_ReadItemPrice()
{
}

void BASE_UnderBarToSpace(const char* szStr)
{
}

int BASE_GetHttpRequest(char* httpname, char* Request, int MaxBuffer)
{
	return 0;
}

int ReadItemicon()
{
	return 0;
}

void ReadItemName()
{
}

void ReadUIString()
{
	FILE* pFile = nullptr;
	fopen_s(&pFile, UIString_Path, "rt");

	if (pFile)
	{
		char str[128]{ 0 };
		while (fgets(str, sizeof str, pFile))
		{
			char part[64]{ 0 };
			int Index = 0;

			int ret = sscanf_s(str, "%d %s", &Index, part, 64);
			if (ret != 2)
				continue;

			strncpy_s(g_UIString[Index], part, sizeof part);
		}

		fclose(pFile);
	}
}

char ReadNameFiltraDataBase()
{
	return 1;
}

char ReadChatFiltraDataBase()
{
	return 1;
}

void EnableSysKey()
{
}

bool CheckOS()
{
	return false;
}

void DisableSysKey()
{
}

int IsClearString(char* str, int target)
{
	int len = strlen(str);
	for (int pos = 0; pos < len; ++pos)
	{
		if (str[pos] >= 0)
		{
			if (pos >= target)
				return 1;
		}
		else
		{
			if (pos == target)
				return 0;
			if (pos == target + 1)
				return 1;

			++pos;
		}
	}

	return 1;
}