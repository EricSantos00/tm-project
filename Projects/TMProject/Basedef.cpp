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

int BASE_GetSum(char* p, int size)
{
	int sum = 0;
	for (int i = 0; i < size; ++i)
	{
		int mod = i % 7;
		if (!(i % 7))
			sum += p[i] / 2;
		if (mod == 1)
			sum += p[i] ^ 0xFF;
		if (mod == 2)
			sum += 3 * p[i];
		if (mod == 3)
			sum += 2 * p[i];
		if (mod == 4)
			sum -= p[i] / 7;
		if (mod == 5)
			sum -= p[i];
		else
			sum += p[i] / 3;
	}

	return sum;
}

int BASE_ReadMessageBin()
{
	memset(g_pMessageStringTable, 0, sizeof g_pMessageStringTable);

	int size = 256000;
	FILE* pFile = nullptr;
	fopen_s(&pFile, Strdef_Path, "rb");

	int checksum = 0;	
	if (pFile)
	{
		fread(g_pMessageStringTable, size, 1u, pFile);
		fread(&checksum, 4, 1, pFile);
		fclose(pFile);
	}

	if (checksum != BASE_GetSum((char*)g_pMessageStringTable, size))
		return 0;

	for (int i = 0; i < 2000; ++i)
		for (int k = 0; k < 128; ++k)
			g_pMessageStringTable[i][k] ^= 0x5A;

	return 1;
}

void BASE_InitEffectString()
{
}

int BASE_InitializeBaseDef()
{
	BASE_InitializeServerList();

	return 1;
}

void BASE_ReadItemPrice()
{
}

void BASE_UnderBarToSpace(char* szStr)
{
	while (*szStr)
	{
		if (*szStr == '_')
			*szStr = ' ';

		++szStr;
	}
}

int BASE_GetHttpRequest(char* httpname, char* Request, int MaxBuffer)
{
	return 0;
}

int BASE_GetWeekNumber()
{
	time_t now;
	time(&now);

	unsigned int week = 86400;
	return (int)(now / week - 3);

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

int IsClearString2(char* str, int nTarget)
{
	if (!str)
		return 1;

	char* pNextRightChar = CharNext(&str[nTarget]);
	int nLen = pNextRightChar - &str[nTarget];
	int nLen2 = pNextRightChar - CharPrev(str, pNextRightChar);

	if (nLen == 1 && nLen2 == 2)
		return 0;

	if (nLen != 2 || nLen2 != 1)
		return 1;

	return 0;
}

int BASE_InitializeServerList()
{
	FILE* fpBin = nullptr;
	fopen_s(&fpBin, "./serverlist.bin", "rb");

	if (fpBin)
	{
		char szList[65] = { "¤¡¤¤¤§¤©¤±¤²¤µ¤·¤¸¤º¤»¤¼¤½¤¾¤¿¤Á¤Ã¤Å¤Ç¤Ë¤Ì¤Ð¤Ñ¤Ó¤¿¤Ä¤Ó¤Ç¤Ì°¡³ª´Ù"};

		memset(&g_pServerList, 0, sizeof g_pServerList);
		fread(g_pServerList, 0x6E, 0x40u, fpBin);
		fclose(fpBin);

		for (int k = 0; k < MAX_SERVERGROUP; k++)
			for (int j = 0; j < MAX_SERVERNUMBER; j++)
				for (int i = 0; i < 64; i++)
					g_pServerList[k][j][i] -= szList[63 - i];
		return 1;
	}

	return 0;
}