#include "pch.h"
#include "Basedef.h"
#include "TMGlobal.h"
#include "TMLog.h"

HWND hWndMain;
char EncodeByte[4];
int g_nChannelWidth;
int g_nServerGroupNum;
char g_pServerList[MAX_SERVERGROUP][MAX_SERVERNUMBER][64];
int g_nSelServerWeather;
char g_pMessageStringTable[MAX_STRING][MAX_STRING_LENGTH];
STRUCT_ITEMLIST g_pItemList[6500];

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
int BASE_GetItemAbility(STRUCT_ITEM* item, char Type)
{
	return 0;
}
int BASE_DefineSkinMeshType(int nClass)
{
    switch (nClass)
    {
    case 1:
        return 0;
    case 2:
        return 1;
    case 4:
        return 0;
    case 8:
        return 1;
    case 16:
        return 20;
    case 17:
        return 21;
    case 18:
        return 22;
    case 19:
        return 23;
    case 20:
        return 24;
    case 21:
        return 2;
    case 22:
        return 25;
    case 23:
        return 26;
    case 24:
        return 27;
    case 25:
        return 2;
    case 26:
        return 3;
    case 27:
        return 28;
    case 28:
        return 29;
    case 29:
        return 6;
    case 30:
        return 4;
    case 31:
        return 32;
    case 32:
        return 7;
    case 33:
        return 8;
    case 34:
        return 0;
    case 35:
        return 29;
    case 36:
        return 0;
    case 37:
        return 1;
    case 38:
        return 1;
    case 39:
        return 0;
    case 40:
        return 0;
    case 41:
        return 69;
    case 42:
        return 30;
    case 43:
        return 31;
    case 44:
        return 33;
    case 45:
        return 23;
    case 46:
        return 11;
    case 47:
        return 35;
    case 48:
        return 34;
    case 49:
        return 36;
    case 50:
        return 37;
    case 51:
        return 38;
    case 52:
        return 39;
    case 53:
        return 40;
    case 54:
        return 9;
    case 55:
        return 10;
    case 56:
        return 41;
    case 57:
        return 12;
    case 58:
        return 42;
    case 59:
        return 43;
    case 60:
        return 0;
    case 61:
        return 1;
    case 62:
        return 5;
    case 63:
        return 0;
    case 64:
        return 44;
    case 66:
        return 45;
    case 67:
        return 46;
    case 68:
        return 47;
    case 69:
        return 48;
    case 70:
        return 53;
    case 71:
        return 54;
    case 72:
        return 55;
    case 73:
        return 56;
    case 74:
        return 57;
    }

    LOG_WRITELOG("Invalide Item Class\n");
    return 0;
}

float BASE_GetMountScale(int nSkinMeshType, int nMeshIndex)
{
    float fSize;

    fSize = 1.0f;
    if (nSkinMeshType == 28)
        fSize = 1.45f;
    else if (nSkinMeshType == 25 && nMeshIndex == 1)
        fSize = 1.4f;
    else if (nSkinMeshType == 20 && nMeshIndex == 7)
        fSize = 0.6f;
    else if (nSkinMeshType == 20 && !nMeshIndex)
        fSize = 1.3f;
    else if (nSkinMeshType == 29 && nMeshIndex == 4)
        fSize = 1.3f;

    return fSize;
}

int BASE_GetRoute(int x, int y, int* targetx, int* targety, char* Route, int distance, char* pHeight, int MH)
{
    int lastx = x;
    int lasty = y;
    int tx = *targetx;
    int ty = *targety;
    memset(Route, 0, 24);

    for (int i = 0; i < distance && i < 23; ++i)
    {
        if (x - g_HeightPosX < 1 || y - g_HeightPosY < 1 || x - g_HeightPosX > g_HeightWidth - 2 || y - g_HeightPosY > g_HeightHeight - 2)
        {
            Route[i] = 0;
            break;
        }

        int cul = pHeight[x + g_HeightWidth * (y - g_HeightPosY) - g_HeightPosX];
        int n = pHeight[x + g_HeightWidth * (y - g_HeightPosY - 1) - g_HeightPosX];
        int ne = pHeight[x + g_HeightWidth * (y - g_HeightPosY - 1) - g_HeightPosX + 1];
        int e = pHeight[x + g_HeightWidth * (y - g_HeightPosY) - g_HeightPosX + 1];
        int se = pHeight[x + g_HeightWidth * (y - g_HeightPosY + 1) - g_HeightPosX + 1];
        int s = pHeight[x + g_HeightWidth * (y - g_HeightPosY + 1) - g_HeightPosX];
        int sw = pHeight[x + g_HeightWidth * (y - g_HeightPosY + 1) - g_HeightPosX - 1];
        int w = pHeight[x + g_HeightWidth * (y - g_HeightPosY) - g_HeightPosX - 1];
        int nw = pHeight[x + g_HeightWidth * (y - g_HeightPosY - 1) - g_HeightPosX - 1];

        if (tx == x && ty > y && s < MH + cul && s > cul - MH)
        {
            Route[i] = '8';
            ++y;
        }
        else if (tx == x && ty < y && n < MH + cul && n > cul - MH)
        {
            Route[i] = '2';
            --y;
        }
        else if (tx > x
            && ty < y
            && ne < MH + cul
            && ne > cul - MH
            && (n < MH + cul && n > cul - MH || e < MH + cul && e > cul - MH))
        {
            Route[i] = '3';
            ++x;
            --y;
        }
        else if (tx > x && ty == y && e < MH + cul && e > cul - MH)
        {
            Route[i] = '6';
            ++x;
        }
        else if (tx > x
            && ty > y
            && se < MH + cul
            && se > cul - MH
            && (s < MH + cul && s > cul - MH || e < MH + cul && e > cul - MH))
        {
            Route[i] = '9';
            ++x;
            ++y;
        }
        else if (tx < x
            && ty > y
            && sw < MH + cul
            && sw > cul - MH
            && (s < MH + cul && s > cul - MH || w < MH + cul && w > cul - MH))
        {
            Route[i] = '7';
            --x;
            ++y;
        }
        else if (tx < x && ty == y && w < MH + cul && w > cul - MH)
        {
            Route[i] = '4';
            --x;
        }
        else if (tx < x
            && ty < y
            && nw < MH + cul
            && nw > cul - MH
            && (n < MH + cul && n > cul - MH || w < MH + cul && w > cul - MH))
        {
            Route[i] = '1';
            --x;
            --y;
        }
        else if (tx > x && ty < y && e < MH + cul && e > cul - MH)
        {
            Route[i] = '6';
            ++x;
        }
        else if (tx > x && ty < y && n < MH + cul && n > cul - MH)
        {
            Route[i] = '2';
            --y;
        }
        else if (tx > x && ty > y && e < MH + cul && e > cul - MH)
        {
            Route[i] = '6';
            ++x;
        }
        else if (tx > x && ty > y && s < MH + cul && s > cul - MH)
        {
            Route[i] = '8';
            ++y;
        }
        else if (tx < x && ty > y && w < MH + cul && w > cul - MH)
        {
            Route[i] = '4';
            --x;
        }
        else if (tx < x && ty > y && s < MH + cul && s > cul - MH)
        {
            Route[i] = '8';
            ++y;
        }
        else if (tx < x && ty < y && w < MH + cul && w > cul - MH)
        {
            Route[i] = '4';
            --x;
        }
        else if (tx < x && ty < y && n < MH + cul && n > cul - MH)
        {
            Route[i] = '2';
            --y;
        }
        else if (tx == x + 1 || ty == y + 1 || tx == x - 1 || ty == y - 1)
        {
            Route[i] = 0;
            break;
        }
        if (tx == x
            && ty > y
            && se < MH + cul
            && se > cul - MH
            && (s < MH + cul && s > cul - MH || e < MH + cul && e > cul - MH))
        {
            Route[i] = '9';
            ++x;
            ++y;
        }
        else if (tx == x
            && ty > y
            && sw < MH + cul
            && sw > cul - MH
            && (s < MH + cul && s > cul - MH || w < MH + cul && w > cul - MH))
        {
            Route[i] = '7';
            --x;
            ++y;
        }
        else if (tx == x
            && ty < y
            && ne < MH + cul
            && ne > cul - MH
            && (n < MH + cul && n > cul - MH || e < MH + cul && e > cul - MH))
        {
            Route[i] = '3';
            ++x;
            --y;
        }
        else if (tx == x
            && ty < y
            && nw < MH + cul
            && nw > cul - MH
            && (n < MH + cul && n > cul - MH || w < MH + cul && w > cul - MH))
        {
            Route[i] = '1';
            --x;
            --y;
        }
        else if (tx < x
            && ty == y
            && sw < MH + cul
            && sw > cul - MH
            && (s < MH + cul && s > cul - MH || w < MH + cul && w > cul - MH))
        {
            Route[i] = '7';
            --x;
            ++y;
        }
        else if (tx < x
            && ty == y
            && nw < MH + cul
            && nw > cul - MH
            && (n < MH + cul && n > cul - MH || w < MH + cul && w > cul - MH))
        {
            Route[i] = '1';
            --x;
            --y;
        }
        else if (tx > x
            && ty == y
            && se < MH + cul
            && se > cul - MH
            && (s < MH + cul && s > cul - MH || e < MH + cul && e > cul - MH))
        {
            Route[i] = '9';
            ++x;
            ++y;
        }
        else if (tx <= x
            || ty != y
            || ne >= MH + cul
            || ne <= cul - MH
            || (n >= MH + cul || n <= cul - MH) && (e >= MH + cul || e <= cul - MH))
        {
            Route[i] = 0;
            break;
        }

        Route[i] = '3';
        ++x;
        --y;
    }

    if (lastx == x && lasty == y)
        return 0;

    *targetx = x;
    *targety = y;
    return lastx != x || lasty != y;
}

int BASE_GetDistance(int x1, int y1, int x2, int y2)
{
    int dy;
    int dx;
    if (x1 <= x2)
        dx = x2 - x1;
    else
        dx = x1 - x2;
    if (y1 <= y2)
        dy = y2 - y1;
    else
        dy = y1 - y2;
    if (dx <= 6 && dy <= 6)
        return g_pDistanceTable[dy][dx];
    if (dx <= dy)
        return dy + 1;

    return dx + 1;
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