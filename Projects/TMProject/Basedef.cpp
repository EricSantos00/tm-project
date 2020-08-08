#include "pch.h"
#include "Basedef.h"
#include "TMGlobal.h"
#include "TMLog.h"
#include "ItemEffect.h"

HWND hWndMain;
char EncodeByte[4];
int g_nChannelWidth;
int g_nServerGroupNum;
char g_pServerList[MAX_SERVERGROUP][MAX_SERVERNUMBER][64];
int g_nSelServerWeather;
char g_pMessageStringTable[MAX_STRING][MAX_STRING_LENGTH];
STRUCT_ITEMLIST g_pItemList[6500];
STRUCT_SPELL g_pSpell[248];
STRUCT_INITITEM g_pInitItem[100];
int g_itemicon[6500];

STRUCT_GUILDZONE g_pGuildZone[MAX_GUILDZONE] =
{
    {0, 0, 2088, 2148, 2086, 2093, 2052, 2052, 2171, 2163, 197, 213, 238, 230, 205, 220, 228, 220, 5, 0}, // Armia
    {0, 0, 2531, 1700, 2494, 1707, 2432, 1672, 2675, 1767, 197, 149, 238, 166, 205, 157, 228, 157, 5, 0}, // Azran
    {0, 0, 2460, 1976, 2453, 2000, 2448, 1966, 2476, 2024, 141, 213, 182, 230, 146, 220, 173, 220, 5, 0}, // Erion
    {0, 0, 3614, 3124, 3652, 3122, 3605, 3090, 3690, 3260, 141, 149, 182, 166, 146, 157, 173, 157, 5, 0}, // Nippleheim
    {0, 0, 1066, 1760, 1050, 1706, 1036, 1700, 1072, 1760, 4000, 4000, 4010, 4010, 4005, 4005, 4005, 4005, 5, 0} // Noatum
};

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

int BASE_InitializeAttribute()
{
    char FileName[256]{};
    strcpy(FileName, "./Env/AttributeMap.dat");

    FILE* fp = nullptr;
    fopen_s(&fp, FileName, "rb");
    if (fp == nullptr)
        fopen_s(&fp, "../../TMSRV/Run/AttributeMap.dat", "rb");

    if (fp == nullptr)
    {
        MessageBox(0, "There is no file", "Attributemap.dat", MB_OK);
        return 0;
    }

    fread(g_pAttribute, 1024, 1024, fp);
    int tsum = 0;
    fread(&tsum, 4, 1, fp);
    fclose(fp);

    int sum = BASE_GetSum((char*)g_pAttribute, sizeof(g_pAttribute));

    return sum == tsum;
}

void BASE_ApplyAttribute(char* pHeight, int size)
{
    int endx = size + g_HeightPosX;
    int endy = size + g_HeightPosY;

    for (int y = g_HeightPosY; y < endy; ++y)
    {
        for (int x = g_HeightPosX; x < endx; ++x)
        {
            if (g_pAttribute[(y >> 2) & 0x3FF][(x >> 2) & 0x3FF] & 2)
                pHeight[x + g_HeightWidth * (y - g_HeightPosY) - g_HeightPosX] = 127;
        }
    }
}

int BASE_ReadItemList()
{
    FILE* fp = nullptr;

    fopen_s(&fp, ".\\ItemList.bin", "rb");

    if (!fp)
    {
        MessageBoxA(0, "Can't read ItemList.bin", "ERROR", 0);
        return 0;
    }

    int size = sizeof(g_pItemList);

    char* temp = (char*)g_pItemList;

    int tsum{};

    fread(g_pItemList, size, 1u, fp);
    fread(&tsum, 4u, 1u, fp);
    fclose(fp);

    int sum = BASE_GetSum2((char*)g_pItemList, size); // Not being used...

#if !defined _DEBUG
    if (tsum != 0x1343B16)
        return 0;
#endif

    for (int i = 0; i < size; ++i)
        temp[i] ^= 0x5A;

    int Handle = _open(".\\ExtraItem.bin", _O_RDONLY | _O_BINARY, 0);

    if (Handle != -1)
    {
        char buff[256]{};

        while (_read(Handle, buff, sizeof(STRUCT_ITEMLIST) + 2) >= sizeof(STRUCT_ITEMLIST) + 2)
        {
            short idx = *(short*)buff;

            if (buff > 0 && idx < MAX_ITEMLIST)
                memcpy(&g_pItemList[idx], &buff[2], sizeof(STRUCT_ITEMLIST));
        }

        _close(Handle);

        for (int j = 0; j < size; ++j)
            temp[j] ^= 0x5A;

        sum = BASE_GetSum2((char*)g_pItemList, size); // Not being used...

#if !defined _DEBUG
        if (tsum != 0x1343B16)
            return 0;
#endif
        for (int j = 0; j < size; ++j)
            temp[j] ^= 0x5A;
    }
    return 1;
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

int BASE_GetSum2(char* p, int size)
{
    int sum = 0;

    for (int i = 0; i < size; ++i)
    {
        int mod = i % 9;
        if (mod == 0)
            sum += 2 * p[i];
        if (mod == 1)
            sum += p[i] ^ 0xFF;
        if (mod == 2)
            sum += p[i] / 3;
        if (mod == 3)
            sum += 2 * p[i];
        if (mod == 4)
            sum -= p[i] ^ 0x5A;
        if (mod == 5)
            sum -= p[i];
        else
            sum += p[i] / 5;
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
    int ret = 0;
	ret = BASE_InitializeServerList() & 1;
    ret = BASE_ReadItemList() & ret;
    ret = BASE_InitializeAttribute() & ret;

	return ret;
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

int BASE_GetItemSanc(STRUCT_ITEM* item)
{
    if (item->sIndex >= 2330 && item->sIndex < 2390)
        return 0;

    if (item->sIndex >= 3200 && item->sIndex < 3300)
        return 0;

    if (item->sIndex >= 3980 && item->sIndex < 4000)
        return 0;

    int sanc{};

    if (item->stEffect[0].cEffect != EF_SANC && item->stEffect[1].cEffect != EF_SANC && item->stEffect[2].cEffect != EF_SANC)
    {
        if (item->stEffect[0].cEffect >= 115 && item->stEffect[0].cEffect <= 126)
            sanc = item->stEffect[0].cValue;

        else if (item->stEffect[1].cEffect >= 115 && item->stEffect[1].cEffect <= 126)
            sanc = item->stEffect[1].cValue;

        else if (item->stEffect[2].cEffect >= 115 && item->stEffect[2].cEffect <= 126)
            sanc = item->stEffect[2].cValue;
    }
    else if (item->stEffect[0].cEffect == EF_SANC)
        sanc = item->stEffect[0].cValue;

    else if (item->stEffect[1].cEffect == EF_SANC)
        sanc = item->stEffect[1].cValue;

    else
        sanc = item->stEffect[2].cValue;

    if (item->sIndex != 786 && item->sIndex != 1936 && item->sIndex != 1937)
    {
        if (sanc < 230)
            sanc %= 10;
        else
            sanc -= 220;

        if (sanc >= 10 && sanc <= 35)
            sanc = (sanc - 10) / 4 + 10;
    }

    return sanc;
}

int BASE_GetItemAbility(STRUCT_ITEM* item, char Type)
{
    int value = 0;
    int idx = item->sIndex;

    if (idx <= 0 || idx > MAX_ITEMLIST)
        return 0;

    int nUnique = g_pItemList[idx].nUnique;
    int nPos = g_pItemList[idx].nPos;

    if ((Type == EF_DAMAGEADD || Type == EF_MAGICADD) && (nUnique < 41 || nUnique > 50))
        return 0;

    if (Type == EF_CRITICAL && (item->stEffect[1].cEffect == EF_CRITICAL2 || item->stEffect[2].cEffect == EF_CRITICAL2))
        Type = EF_CRITICAL2;

    if (Type == EF_DAMAGE && nPos == 32 && (item->stEffect[1].cEffect == EF_DAMAGE2 || item->stEffect[2].cEffect == EF_DAMAGE2))
        Type = EF_DAMAGE2;

    if (Type == EF_MPADD && (item->stEffect[1].cEffect == EF_MPADD2 || item->stEffect[2].cEffect == EF_MPADD2))
        Type = EF_MPADD2;

    if (Type == EF_HPADD && (item->stEffect[1].cEffect == EF_HPADD2 || item->stEffect[2].cEffect == EF_HPADD2))
        Type = EF_HPADD2;

    if (Type == EF_ACADD && (item->stEffect[1].cEffect == EF_ACADD2 || item->stEffect[2].cEffect == EF_ACADD2))
        Type = EF_ACADD2;

    if (Type == EF_LEVEL)
        value = g_pItemList[idx].nReqLvl;

    if (Type == EF_REQ_STR)
        value += g_pItemList[idx].nReqStr;

    if (Type == EF_REQ_INT)
        value += g_pItemList[idx].nReqInt;

    if (Type == EF_REQ_DEX)
        value += g_pItemList[idx].nReqDex;

    if (Type == EF_REQ_CON)
        value += g_pItemList[idx].nReqCon;

    if (Type == EF_POS)
        value += g_pItemList[idx].nPos;

    if (Type != EF_INCUBATE)
    {
        for (int i = 0; i < 12; ++i)
        {
            if (g_pItemList[idx].stEffect[i].sEffect == Type ||
                g_pItemList[idx].stEffect[i].sEffect == EF_HPADD && Type == EF_HPADD2)
            {
                int tvalue = g_pItemList[idx].stEffect[i].sValue;

                if (Type == EF_ATTSPEED && tvalue == 1)
                    tvalue = 10;

                value += tvalue;
            }
        }
    }

    if (item->sIndex >= 2330 && item->sIndex < 2390)
    {
        switch (Type)
        {
        case EF_MOUNTHP:
            return item->stEffect[0].sValue;
        case EF_MOUNTSANC:
            return item->stEffect[1].cEffect;
        case EF_MOUNTLIFE:
            return item->stEffect[1].cValue;
        case EF_MOUNTFEED:
            return item->stEffect[2].cEffect;
        case EF_MOUNTKILL:
            return item->stEffect[2].cValue;
        }

        if (item->sIndex < 2362 || item->sIndex >= 2390 || item->stEffect[0].sValue <= 0)
            return value;

        int lv = item->stEffect[1].cEffect;
        int cd = item->sIndex - 2360;

        switch (Type)
        {
        case EF_DAMAGE:
            value = g_pMountBonus[cd][0] * (lv + 20) / 100;
            break;
        case EF_MAGIC:
            value = g_pMountBonus[cd][1] * (lv + 15) / 100;
            break;
        case EF_PARRY:
            value = g_pMountBonus[cd][2];
            break;
        case EF_RESISTALL:
            value = g_pMountBonus[cd][3];
            break;
        default:
            break;
        }
    }
    else if (item->sIndex >= 3980 && item->sIndex < 4000)
    {
        int cd = item->sIndex - 3980;

        switch (Type)
        {
        case EF_DAMAGE:
            value = g_pMountBonus2[cd][0];
            break;
        case EF_MAGIC:
            value = g_pMountBonus2[cd][1];
            break;
        case EF_PARRY:
            value = g_pMountBonus2[cd][2];
            break;
        case EF_RESISTALL:
            value = g_pMountBonus2[cd][3];
            break;
        default:
            break;
        }
    }
    else
    {
        for (int j = 0; j < 3; ++j)
        {
            if (item->stEffect[j].cEffect == Type)
            {
                int tvalue = item->stEffect[j].cValue;

                if (Type == EF_ATTSPEED && tvalue == 1)
                    tvalue = 10;

                value += tvalue;
            }
        }

        int sanc = BASE_GetItemSanc(item);

        if (item->sIndex <= 40)
            sanc = 0;

        if (sanc >= 9 && nPos & 0xF00)
            sanc++;

        if (sanc
            && Type != EF_GRID
            && Type != EF_CLASS
            && Type != EF_POS
            && Type != EF_WTYPE
            && Type != EF_RANGE
            && Type != EF_LEVEL
            && Type != EF_REQ_STR
            && Type != EF_REQ_INT
            && Type != EF_REQ_DEX
            && Type != EF_REQ_CON
            && Type != EF_VOLATILE
            && Type != EF_INCUBATE
            && Type != EF_INCUDELAY
            && Type != EF_PREVBONUS
            && Type != EF_TRANS
            && Type != EF_REFLEVEL
            && Type != EF_GAMEROOM
            && Type != EF_REGENMP
            && Type != EF_REGENHP
            && Type != EF_FAME)
        {
            if (sanc > 10)
            {
                int UpSanc = sanc - 10;

                switch (UpSanc)
                {
                case 1:
                    UpSanc = 220;
                    break;
                case 2:
                    UpSanc = 250;
                    break;
                case 3:
                    UpSanc = 280;
                    break;
                case 4:
                    UpSanc = 320;
                    break;
                case 5:
                    UpSanc = 370;
                    break;
                case 6:
                    UpSanc = 400;
                    break;
                }

                value = UpSanc * 10 * value / 100 / 10;
            }
            else
            {
                value = value * (sanc + 10) / 10;
            }
        }

        if (Type == EF_RUNSPEED)
        {
            if (value >= 3)
                value = 2;

            if (value > 0 && sanc >= 9)
                value++;
        }

       /* if (Type == EF_HWORDGUILD || Type == EF_LWORDGUILD)
            value = value;*/

        if (Type == EF_REGENMP || Type == EF_REGENHP)
            value *= sanc;

        if (Type == EF_GRID && (value < 0 || value > 7))
            value = 0;
    }

	return value;
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

    LOG_WRITELOG("Invalide Item Class %d\n", nClass);
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
        if (tx == x && ty == y)
        {
            Route[i] = 0;
            break;
        }
        if (tx == x && ty > y && s < MH + cul && s > cul - MH)
        {
            Route[i] = 56;
            ++y;
        }
        else if (tx == x && ty < y && n < MH + cul && n > cul - MH)
        {
            Route[i] = 50;
            --y;
        }
        else if (tx > x
            && ty < y
            && ne < MH + cul
            && ne > cul - MH
            && (n < MH + cul && n > cul - MH || e < MH + cul && e > cul - MH))
        {
            Route[i] = 51;
            ++x;
            --y;
        }
        else if (tx > x && ty == y && e < MH + cul && e > cul - MH)
        {
            Route[i] = 54;
            ++x;
        }
        else if (tx > x
            && ty > y
            && se < MH + cul
            && se > cul - MH
            && (s < MH + cul && s > cul - MH || e < MH + cul && e > cul - MH))
        {
            Route[i] = 57;
            ++x;
            ++y;
        }
        else if (tx < x
            && ty > y
            && sw < MH + cul
            && sw > cul - MH
            && (s < MH + cul && s > cul - MH || w < MH + cul && w > cul - MH))
        {
            Route[i] = 55;
            --x;
            ++y;
        }
        else if (tx < x && ty == y && w < MH + cul && w > cul - MH)
        {
            Route[i] = 52;
            --x;
        }
        else if (tx < x
            && ty < y
            && nw < MH + cul
            && nw > cul - MH
            && (n < MH + cul && n > cul - MH || w < MH + cul && w > cul - MH))
        {
            Route[i] = 49;
            --x;
            --y;
        }
        else if (tx > x && ty < y && e < MH + cul && e > cul - MH)
        {
            Route[i] = 54;
            ++x;
        }
        else if (tx > x && ty < y && n < MH + cul && n > cul - MH)
        {
            Route[i] = 50;
            --y;
        }
        else if (tx > x && ty > y && e < MH + cul && e > cul - MH)
        {
            Route[i] = 54;
            ++x;
        }
        else if (tx > x && ty > y && s < MH + cul && s > cul - MH)
        {
            Route[i] = 56;
            ++y;
        }
        else if (tx < x && ty > y && w < MH + cul && w > cul - MH)
        {
            Route[i] = 52;
            --x;
        }
        else if (tx < x && ty > y && s < MH + cul && s > cul - MH)
        {
            Route[i] = 56;
            ++y;
        }
        else if (tx < x && ty < y && w < MH + cul && w > cul - MH)
        {
            Route[i] = 52;
            --x;
        }
        else if (tx < x && ty < y && n < MH + cul && n > cul - MH)
        {
            Route[i] = 50;
            --y;
        }
        else
        {
            if (tx == x + 1 || ty == y + 1 || tx == x - 1 || ty == y - 1)
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
                Route[i] = 57;
                ++x;
                ++y;
            }
            else if (tx == x
                && ty > y
                && sw < MH + cul
                && sw > cul - MH
                && (s < MH + cul && s > cul - MH || w < MH + cul && w > cul - MH))
            {
                Route[i] = 55;
                --x;
                ++y;
            }
            else if (tx == x
                && ty < y
                && ne < MH + cul
                && ne > cul - MH
                && (n < MH + cul && n > cul - MH || e < MH + cul && e > cul - MH))
            {
                Route[i] = 51;
                ++x;
                --y;
            }
            else if (tx == x
                && ty < y
                && nw < MH + cul
                && nw > cul - MH
                && (n < MH + cul && n > cul - MH || w < MH + cul && w > cul - MH))
            {
                Route[i] = 49;
                --x;
                --y;
            }
            else if (tx < x
                && ty == y
                && sw < MH + cul
                && sw > cul - MH
                && (s < MH + cul && s > cul - MH || w < MH + cul && w > cul - MH))
            {
                Route[i] = 55;
                --x;
                ++y;
            }
            else if (tx < x
                && ty == y
                && nw < MH + cul
                && nw > cul - MH
                && (n < MH + cul && n > cul - MH || w < MH + cul && w > cul - MH))
            {
                Route[i] = 49;
                --x;
                --y;
            }
            else if (tx > x
                && ty == y
                && se < MH + cul
                && se > cul - MH
                && (s < MH + cul && s > cul - MH || e < MH + cul && e > cul - MH))
            {
                Route[i] = 57;
                ++x;
                ++y;
            }
            else
            {
                if (tx <= x
                    || ty != y
                    || ne >= MH + cul
                    || ne <= cul - MH
                    || (n >= MH + cul || n <= cul - MH) && (e >= MH + cul || e <= cul - MH))
                {
                    Route[i] = 0;
                    break;
                }
                Route[i] = 51;
                ++x;
                --y;
            }
        }
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

int BASE_GetSpeed(STRUCT_SCORE* score)
{
    int Run;

    Run = score->AttackRun & 0xF;
    if (Run < 1)
        Run = 1;
    if (Run > 7)
        Run = 7;

    return Run;
}

int ReadItemicon()
{
    FILE* fpBin = nullptr;
    fopen_s(&fpBin, "./itemicon.bin", "rb");
    if (fpBin)
    {
        fread(g_itemicon, sizeof(g_itemicon), 1u, fpBin);
        fclose(fpBin);
    }

    return 1;
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

int IsSkill(int nSkillIndex)
{
    if (nSkillIndex >= 5000 && nSkillIndex <= 5104)
        return 1;
    if (nSkillIndex >= 5400 && nSkillIndex <= 5447)
        return 1;

    return 0;
}

int GetSkillIndex(int nSkillIndex)
{
    if (nSkillIndex >= 5400)
        nSkillIndex -= 5200;
    else if (nSkillIndex >= 5000)
        nSkillIndex -= 5000;

    return nSkillIndex;
}

int IsValidSkill(int nSkillIndex)
{
    if (nSkillIndex >= 0 && nSkillIndex < 104)
    {
        if (nSkillIndex >= 96)
        {
            if (!((1 << (nSkillIndex - 72)) & g_pObjectManager->m_stMobData.LearnedSkill[0]))
                return 0;
        }
        else if (!((1 << nSkillIndex % 24) & g_pObjectManager->m_stMobData.LearnedSkill[0]))
        {
            return 0;
        }
        return 1;
    }
    else if (nSkillIndex == 205 && g_pObjectManager->m_stMobData.LearnedSkill[1] & 0x20)
    {
        return 1;
    }
    else if (nSkillIndex == 233 && g_pObjectManager->m_stMobData.LearnedSkill[1] & 0x200)
    {
        return 1;
    }
    else if (nSkillIndex == 238 && g_pObjectManager->m_stMobData.LearnedSkill[1] & 4)
    {
        return 1;
    }
    else if (nSkillIndex < 200 || nSkillIndex >= 247)
    {
        return 0;
    }
    else if (nSkillIndex == 205 || nSkillIndex == 233 || nSkillIndex == 238)
    {
        return 0;
    }
    else
    {
        return ((1 << 4 * ((nSkillIndex - 200) / 4)) & g_pObjectManager->m_stMobData.LearnedSkill[1]) != 0;
    }

    return 0;
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

int BASE_GetVillage(int x, int y)
{
    for (int i = 0; i < 5; ++i)
    {
        if (x >= g_pGuildZone[i].vx1 && g_pGuildZone[i].vx2 && g_pGuildZone[i].vy1 && g_pGuildZone[i].vy2)
            return i;
    }

    return MAX_GUILDZONE;
}

int BASE_GetSubGuild(int item)
{
    int ret = 0;
    if (item >= 3 && item <= 8)
        ret = item % 3 + 1;

    return ret;
	
}

unsigned int BASE_GetItemTenColor(STRUCT_ITEM* pItem)
{
    if (BASE_GetItemSanc(pItem) <= 9)
        return 0;

    unsigned char sanc{};

    if (pItem->stEffect[0].cEffect == EF_SANC || (pItem->stEffect[0].cEffect >= 115 && pItem->stEffect[0].cEffect <= 126))
        sanc = pItem->stEffect[0].cValue;

    else if (pItem->stEffect[1].cEffect == EF_SANC || (pItem->stEffect[1].cEffect >= 115 && pItem->stEffect[1].cEffect <= 126))
        sanc = pItem->stEffect[1].cValue;

    else if (pItem->stEffect[2].cEffect == EF_SANC || (pItem->stEffect[2].cEffect >= 115 && pItem->stEffect[2].cEffect <= 126))
        sanc = pItem->stEffect[2].cValue;

    return (sanc - 230) % 4 + 5;
}

int BASE_GetItemColorEffect(STRUCT_ITEM* item)
{
    int effect{};

    if (item->stEffect[0].cEffect != EF_SANC && item->stEffect[1].cEffect != EF_SANC && item->stEffect[2].cEffect != EF_SANC)
    {
        if (item->stEffect[0].cEffect >= 115 && item->stEffect[0].cEffect <= 126)
            effect = item->stEffect[0].cEffect;

        else if (item->stEffect[1].cEffect >= 115 && item->stEffect[1].cEffect <= 126)
            effect = item->stEffect[1].cEffect;

        else if (item->stEffect[2].cEffect >= 115 && item->stEffect[2].cEffect <= 126)
            effect = item->stEffect[2].cEffect;
    }
    else if (item->stEffect[0].cEffect == EF_SANC)
        effect = item->stEffect[0].cEffect;

    else if (item->stEffect[1].cEffect == EF_SANC)
        effect = item->stEffect[1].cEffect;

    else
        effect = item->stEffect[2].cEffect;

    return effect;
}

char BASE_CheckValidString(char* name)
{
    int size = strlen(name);
    if (size < 4 || size >= 16)
        return 0;

    for (int j = 0; j < size; ++j)
    {
        char x = name[j];
        if (x < 0)
        {
            if (!name[++j])
                return 0;
        }
        else if ((x < 'a' || x > 'z') && (x < 'A' || x > 'Z') && (x < '0' || x > '9') && x != '-')
            return 0;
    }

    return 1;
}

char* BASE_TransCurse(char* sz)
{
    if (sz == nullptr)
        return 0;
    
    bool bFind = false;
    do
    {
        bFind = false;
        for (size_t i = 0; i < g_pCurseList.dnum; ++i)
        {
            if (strlen(g_pCurseList.pCurseList[i].szOriginal) == 0)
                return sz;

            char* szDest = strstr(sz, g_pCurseList.pCurseList[i].szOriginal);
            if (szDest == nullptr)
                continue;

            int nOriLen = strlen(g_pCurseList.pCurseList[i].szOriginal);
            if (!IsClearString2(sz, szDest - sz))
                continue;

            char szNext[128]{};
            memcpy(szNext, sz, szDest - sz);
            strcat(szNext, g_pCurseList.pCurseList[i].szTrans);
            strcat(szNext, &szDest[nOriLen]);
            sprintf(sz, szNext);
            bFind = true;
            break;
        }
    } while (bFind == true);
    return sz;
}

char BASE_GetAttribute(int x, int y)
{
    if (x >= 0 && x <= 4096 && y >= 0 && x <= 4096)
        return g_pAttribute[y / 4 & 1023][x / 4 & 1023];
   
    return 0;
}

char BASE_GetAttr(int nX, int nY)
{
    return g_pAttribute[nY / 4 % 1024][nX / 4 % 1024];
}

int BASE_ReadTOTOList(char* szFileName)
{
    return 0;
}

int BASE_GetStaticItemAbility(STRUCT_ITEM* item, char Type)
{
    int value = 0;
    int idx = item->sIndex;

    if (idx <= 0 || idx > MAX_ITEMLIST)
        return value;

    int nPos = g_pItemList[idx].nPos;

    if (Type == EF_LEVEL && idx >= 2330 && idx < 2360)
        value = item->stEffect[1].cEffect - 1;
    else if (Type == EF_LEVEL)
        value += g_pItemList[idx].nReqLvl;

    if (Type == EF_REQ_STR)
        value += g_pItemList[idx].nReqStr;

    if (Type == EF_REQ_INT)
        value += g_pItemList[idx].nReqInt;

    if (Type == EF_REQ_DEX)
        value += g_pItemList[idx].nReqDex;

    if (Type == EF_REQ_CON)
        value += g_pItemList[idx].nReqCon;

    if (Type == EF_POS)
        value += g_pItemList[idx].nPos;

    if (Type != EF_INCUBATE)
    {
        for (int i = 0; i < 12; i++)
        {
            if (g_pItemList[idx].stEffect[i].sEffect != Type)
                continue;

            int tvalue = g_pItemList[idx].stEffect[i].sValue;

            if (Type == EF_ATTSPEED && tvalue == 1)
                tvalue = 10;

            value += tvalue;
        }
    }

    if (Type == EF_RESIST1 || Type == EF_RESIST2 || Type == EF_RESIST3 || Type == EF_RESIST4)
    {
        for (int i = 0; i < 12; i++)
        {
            if (g_pItemList[idx].stEffect[i].sEffect == EF_RESISTALL)
                value += g_pItemList[idx].stEffect[i].sValue;
        }

        for (int i = 0; i < 3; i++)
        {
            if (item->stEffect[i].cEffect == EF_RESISTALL)
                value += item->stEffect[i].cValue;
        }
    }
    if (idx >= 2330 && idx < 2390)
    {
        if (Type == EF_MOUNTHP)
            return item->stEffect[0].sValue;

        else if (Type == EF_MOUNTSANC)
            return item->stEffect[1].cEffect;

        else if (Type == EF_MOUNTLIFE)
            return item->stEffect[1].cValue;

        else if (Type == EF_MOUNTFEED)
            return item->stEffect[2].cEffect;

        else if (Type == EF_MOUNTKILL)
            return item->stEffect[2].cValue;

        if (idx < 2362 || idx >= 2390 || item->stEffect[0].sValue <= 0)
            return value;

        int lv = item->stEffect[1].cEffect;
        int cd = item->sIndex - 2360;

        if (Type == EF_DAMAGE)
            return g_pMountBonus[cd][0] * (lv + 20) / 100;

        else if (Type == EF_MAGIC)
            return g_pMountBonus[cd][1] * (lv + 15) / 100;

        else if (Type == EF_PARRY)
            return g_pMountBonus[cd][2];

        else if (Type == EF_RESIST1 || Type == EF_RESIST2 || Type == EF_RESIST3 || Type == EF_RESIST4)
            return g_pMountBonus[cd][3];
        else
            return value;
    }

    if (idx >= 3980 && idx <= 3994)
    {

        if (Type == EF_DAMAGE)
            return g_pMountBonus2[idx - 3980][0];

        else if (Type == EF_MAGIC)
            return g_pMountBonus2[idx - 3980][1];

        else if (Type == EF_PARRY)
            return g_pMountBonus2[idx - 3980][2];

        else if (Type == EF_RESIST1 || Type == EF_RESIST2 || Type == EF_RESIST3 || Type == EF_RESIST4)
            return g_pMountBonus2[idx - 3980][3];
        else
            return value;
    }

    int sanc = BASE_GetItemSanc(item);

    if (sanc == 9 && (nPos & 0xF00) != 0)
        sanc = 10;

    if (Type != EF_GRID && Type != EF_CLASS && Type != EF_POS && Type != EF_WTYPE && Type != EF_RANGE && Type != EF_LEVEL &&
        Type != EF_REQ_STR && Type != EF_REQ_INT && Type != EF_REQ_DEX && Type != EF_REQ_CON && Type != EF_INCUBATE && Type != EF_INCUDELAY)
    {
        value *= sanc + 10;
        value /= 10;
    }

    if (Type == EF_RUNSPEED)
    {
        if (value >= 3)
            value = 2;

        if (value > 0 && sanc == 9)
            value++;
    }

    if (Type == EF_HWORDGUILD || Type == EF_LWORDGUILD)
    {
        unsigned char v = value;

        value = v;
    }

    return value;
}

int BASE_IsInLowZone(int nX, int nY)
{
    int nX4 = nX / 4;
    int nY4 = nY / 4;
    if (nY / 4 < 1024 && nX4 < 1024 && nY4 >= 0 && nX4 >= 0)
        return g_pAttribute[nY4][nX4] < 0;

    LOG_WRITELOG("\nWrong Position [X:%d Y:%d]\n");
    MessageBox(g_pApp->m_hWnd, "Wrong Character Information.", "Error", MB_SYSTEMMODAL);
    PostMessage(g_pApp->m_hWnd, 16, 0, 0);
    return 0;
}

int BASE_GetItemAmount(STRUCT_ITEM* item)
{
    return 0;
}

int BASE_CanCarry(STRUCT_ITEM* Carry, int pos)
{
    return 0;
}

int BASE_CanTrade(STRUCT_ITEM* Dest, STRUCT_ITEM* Carry, char* MyTrade, STRUCT_ITEM* OpponentTrade)
{
    return 0;
}

int BASE_CanCargo(STRUCT_ITEM* item, STRUCT_ITEM* cargo, int DestX, int DestY)
{
    return 0;
}

int BASE_CanEquip(STRUCT_ITEM* item, STRUCT_SCORE* score, int Pos, int Class, STRUCT_ITEM* pBaseEquip, int OriginalFace, int cktrans)
{
    int idx = item->sIndex;
    if (idx <= 0 || idx >= 6500)
        return FALSE;

    int nUnique = g_pItemList[idx].nUnique;
    if (Pos == 15)
        return FALSE;

    if (Pos != -1)
    {
        int tpos = BASE_GetItemAbility(item, EF_POS);
        int pos = (tpos >> Pos) & 1;

        if (pos == 0)
            return FALSE;

        if (Pos == 6 || Pos == 7)
        {
            int OtherPos = (Pos == 6) ? 7 : 6;
            int	OtherIdx = pBaseEquip[OtherPos].sIndex;

            if (OtherIdx > 0 && OtherIdx < MAX_ITEMLIST)
            {
                int nUnique2 = g_pItemList[OtherIdx].nUnique;
                int otherpos = BASE_GetItemAbility(&pBaseEquip[OtherPos], EF_POS);

                if (tpos == 64 || otherpos == 64)
                {
                    if (nUnique == 46)
                    {
                        if (otherpos != 128)
                            return FALSE;
                    }
                    else if (nUnique2 == 46)
                    {
                        if (tpos != 128)
                            return FALSE;
                    }
                    else
                        return FALSE;
                }
            }
        }
    }

    if (Class >= 22 && Class <= 25 || Class == 32)
        Class = OriginalFace;

    int trans = Class % 10;

    if (Pos == 1 && trans > 5
        && item->sIndex != 747
        && item->sIndex != 3500
        && item->sIndex != 3507
        && item->sIndex != 3501
        && item->sIndex != 3502
        && item->sIndex != 3303
        && item->sIndex != 3507)
    {
        return FALSE;
    }

    int transitem = BASE_GetItemAbility(item, EF_TRANS);
    switch (transitem)
    {
    case 1:
        if (trans < 6)
            return FALSE;
        break;
    case 2:
        if (trans >= 6)
            return FALSE;
        break;
    case 3:
        if (trans < 6)
            return FALSE;
        if (cktrans != 1)
            return FALSE;
        break;
    }

    if (!((BASE_GetItemAbility(item, EF_CLASS) >> Class / 10) & 1))
    {
        if (trans <= 5)
            return FALSE;

        int pos = BASE_GetItemAbility(item, EF_POS);
        if (pos != 64 && pos != 128 && pos != 192)
            return FALSE;
    }
    if (nUnique % 10 >= 9 && nUnique < 40 && trans < 6)
        return FALSE;

    int lvl = BASE_GetItemAbility(item, EF_LEVEL);
    int str = BASE_GetItemAbility(item, EF_REQ_STR);
    int spt = BASE_GetItemAbility(item, EF_REQ_INT);
    int agi = BASE_GetItemAbility(item, EF_REQ_DEX);
    int con = BASE_GetItemAbility(item, EF_REQ_CON);

    int wtype = BASE_GetItemAbility(item, EF_WTYPE);

    int weapontype = wtype % 10;
    int modweapon = wtype % 10;

    int divweapon = wtype % 10 / 10;
    if (Pos == 7 && weapontype)
    {
        int rate = 100;
        if (divweapon || modweapon <= 1)
        {
            if (divweapon == 6 && modweapon > 1)
                rate = 150;
        }
        else
        {
            rate = 130;
        }
        lvl = rate * lvl / 100;
        str = rate * str / 100;
        spt = rate * spt / 100;
        agi = rate * agi / 100;
        con = rate * con / 100;
    }

    if (trans < 5)
    {
        if (lvl > score->Level)
            return FALSE;
        if (str > score->Str)
            return FALSE;
        if (spt > score->Int)
            return FALSE;
        if (agi > score->Dex)
            return FALSE;
        if (con > score->Con)
            return FALSE;
    }

    return TRUE;
}

unsigned int BASE_GetItemColor(STRUCT_ITEM* item)
{
    if (!item)
        return 0xFF99EE99;

    unsigned int dwColor = 0xFFAAAAFF;
    int nMaxValue = 0;
    unsigned int dwMaxParm = 0;

    for (int i = 0; i < 49; ++i)
    {
        auto parm = dwEFParam[i];
        if (parm == 45)
            parm = 69;
        if (parm == 46)
            parm = 70;

        int nPos = BASE_GetItemAbility(item, 17);
        int nValue2 = 0;
        int nValue3 = 0;
        unsigned int dwTempColor = 0;
        if (parm == 42 || parm == 53 || nPos == 32 && parm == 2)
        {
            nValue2 = BASE_GetItemAbility(item, parm);
            nValue3 = BASE_GetItemAbilityNosanc(item, parm);
            dwTempColor = BASE_GetOptionColor(nPos, parm, nValue3);
        }
        else
        {
            nValue2 = BASE_GetBonusItemAbility(item, parm);
            nValue3 = BASE_GetBonusItemAbilityNosanc(item, parm);
            dwTempColor = BASE_GetOptionColor(nPos, parm, nValue3);
        }

        if (dwMaxParm && (unsigned __int8)dwMaxParm == parm)
        {
            nMaxValue += nValue3;
            dwColor = BASE_GetOptionColor(nPos, parm, nValue2);
        }
        else if (nValue3)
        {
            if (BASE_GetColorCount(dwColor) < BASE_GetColorCount(dwTempColor))
            {
                nMaxValue = nValue3;
                dwMaxParm = parm;
                dwColor = dwTempColor;
            }
        }
    }

    return dwColor;
}

int BASE_GetColorCount(unsigned int dwColor)
{
    unsigned int nCount = 0;
    if (dwColor == 0xFFAAAAFF)
        nCount = 1;
    if (dwColor == 0xFF99EE99)
        nCount = 2;
    if (dwColor == 0xFFFFFFAA)
        nCount = 3;
    if (dwColor == 0xFFFFAA00)
        nCount = 4;

    return nCount;
}

int BASE_GetManaSpent(int SkillNumber, int SaveMana, int Special)
{
    return 0;
}

int BASE_GetSkillDamage(int dam, int ac, int combat)
{
    return 0;
}

int BASE_GetSkillDamage(int skillnum, STRUCT_MOB* mob, int weather, int weapondamage, int OriginalFace)
{
    return 0;
}

int BASE_CanEquip_RecvRes(STRUCT_REQ* req, STRUCT_ITEM* item, STRUCT_SCORE* score, int Pos, int Class, STRUCT_ITEM* pBaseEquip, int OriginalFace)
{
    if (!req)
        return 0;
    req->Class = 0;
    req->Level = 0;
    req->Str = 0;
    req->Int = 0;
    req->Dex = 0;
    req->Con = 0;
    int idx = item->sIndex;

    if (idx <= 0 || idx >= 6500)
        return 0;
    int nUnique = g_pItemList[idx].nUnique;
    if (Pos == 15)
        return 0;
    int grade = g_pItemList[idx].nGrade;

    if (Pos != -1)
    {
        int nPos = BASE_GetItemAbility(item, 17);
        if (!((nPos >> Pos) & 1))
            return 0;

        if (Pos == 6 || Pos == 7)
        {
            int OtherPos = Pos == 6 ? 7 : 6;
            int OtherIdx = pBaseEquip[OtherPos].sIndex;

            if (OtherIdx > 0 && OtherIdx < 6500)
            {
                int nUnique2 = g_pItemList[OtherIdx].nUnique;
                int otherpos = BASE_GetItemAbility(&pBaseEquip[OtherPos], 17);
                if (nPos == 64 || otherpos == 64)
                {
                    if (nUnique == 46)
                    {
                        if (otherpos != 128)
                            return 0;
                    }
                    else
                    {
                        if (nUnique2 != 46)
                            return 0;
                        if (nPos != 128)
                            return 0;
                    }
                }
            }
        }
    }

    if (Class >= 22 && Class <= 25 || Class == 32)
        Class = OriginalFace;
    int mount = 0;
    if (idx >= 2300 && idx < 2390)
        mount = (idx - 2300) % 30;
    int  trans = Class % 10;
    if (Pos == 1 && item->sIndex != 747 && trans > 5)
        return 0;
    if ((mount == 19 || mount == 20) && trans <= 5)
        return 0;
    req->Class = 1;
    int transitem = BASE_GetItemAbility(item, 112);

    if (transitem == 1)
    {
        if (trans < 6)
            req->Class = 0;
    }
    else if (transitem == 2 && trans >= 6)
    {
        req->Class = 0;
    }

    int cls = (BASE_GetItemAbility(item, 18) >> Class / 10) & 1;
    int tpos = BASE_GetItemAbility(item, 17);
    if (!cls)
    {
        if (trans > 5)
        {
            if (tpos != 64 && tpos != 128 && tpos != 192)
                req->Class = 0;
        }
        else
        {
            req->Class = 0;
        }
    }
    if (Class <= 31 && Class % 10 != 1 && tpos == 2)
        req->Class = 0;
    if (nUnique % 10 >= 9 && nUnique < 40 && trans < 6)
        req->Class = 0;

    int lvl = BASE_GetItemAbility(item, 1);
    int str = BASE_GetItemAbility(item, 22);
    int spt = BASE_GetItemAbility(item, 23);
    int agi = BASE_GetItemAbility(item, 24);
    int con = BASE_GetItemAbility(item, 25);
    int wtype = BASE_GetItemAbility(item, 21);
    int modweapon = wtype % 10;
    int divweapon = wtype % 10 / 10;
    if (Pos == 7 && modweapon)
    {
        int rate = 100;
        if (divweapon || modweapon <= 1)
        {
            if (divweapon == 6 && modweapon > 1)
                rate = 150;
        }
        else
        {
            rate = 130;
        }
        lvl = rate * lvl / 100;
        str = rate * str / 100;
        spt = rate * spt / 100;
        agi = rate * agi / 100;
        con = rate * con / 100;
    }

    if (score->Level >= lvl)
        req->Level = 1;
    if (score->Str >= str)
        req->Str = 1;
    if (score->Int >= spt)
        req->Int = 1;
    if (score->Dex >= agi)
        req->Dex = 1;
    if (score->Con >= con)
        req->Con = 1;

    return 1;
}

int BASE_GetBonusItemAbilityNosanc(STRUCT_ITEM* item, char Type)
{
    if (item->sIndex >= 2330 && item->sIndex < 2390)
        return FALSE;

    int value = 0;

    int idx = item->sIndex;

    if (idx <= 0 || idx > MAX_ITEMLIST)
        return value;

    for (int i = 0; i < 3; i++)
    {
        if (item->stEffect[i].cEffect != Type)
            continue;

        int tvalue = item->stEffect[i].cValue;

        if (Type == EF_ATTSPEED && tvalue == 1)
            tvalue = 10;

        value += tvalue;
    }

    if (Type == EF_RESIST1 || Type == EF_RESIST2 || Type == EF_RESIST3 || Type == EF_RESIST4)
    {
        for (int i = 0; i < 12; i++)
        {
            if (g_pItemList[idx].stEffect[i].sEffect == EF_RESISTALL)
                value += g_pItemList[idx].stEffect[i].sValue;
        }

        for (int i = 0; i < 3; i++)
        {
            if (item->stEffect[i].cEffect == EF_RESISTALL)
                value += item->stEffect[i].cValue;
        }
    }

    return value;
}

int BASE_GetBonusItemAbility(STRUCT_ITEM* item, char Type)
{
    if (item->sIndex >= 2330 && item->sIndex < 2390)
        return FALSE;

    int value = 0;

    int idx = item->sIndex;

    if (idx <= 0 || idx > MAX_ITEMLIST)
        return value;

    int nPos = g_pItemList[idx].nPos;

    for (int i = 0; i < 3; i++)
    {
        if (item->stEffect[i].cEffect != Type)
            continue;

        int tvalue = item->stEffect[i].cValue;

        if (Type == EF_ATTSPEED && tvalue == 1)
            tvalue = 10;

        value += tvalue;
    }

    if (Type == EF_RESIST1 || Type == EF_RESIST2 || Type == EF_RESIST3 || Type == EF_RESIST4)
    {
        for (int i = 0; i < 12; i++)
        {
            if (g_pItemList[idx].stEffect[i].sEffect == EF_RESISTALL)
                value += g_pItemList[idx].stEffect[i].sValue;
        }

        for (int i = 0; i < 3; i++)
        {
            if (item->stEffect[i].cEffect == EF_RESISTALL)
                value += item->stEffect[i].cValue;
        }
    }

    int sanc = BASE_GetItemSanc(item);

    if (sanc == 9 && (nPos & 0xF00) != 0)
        sanc = 10;

    if (sanc == 0)
        return value;

    if (Type != EF_GRID && Type != EF_CLASS && Type != EF_POS && Type != EF_WTYPE && Type != EF_RANGE && Type != EF_LEVEL && Type != EF_REQ_STR && Type != EF_REQ_INT && Type != EF_REQ_DEX && Type != EF_REQ_CON && Type != EF_VOLATILE && Type != EF_INCUBATE && Type != EF_INCUDELAY)
    {
        value *= sanc + 10;
        value /= 10;
    }

    return value;
}

int BASE_GetItemAbilityNosanc(STRUCT_ITEM* item, char type)
{
    // _8
    int itemId = item->sIndex;
    // _4
    int value = 0;

    if (itemId < 0 || itemId >= MAX_ITEMLIST)
        return value;

    int nUnique = g_pItemList[itemId].nUnique;
    int nPos = g_pItemList[itemId].nPos;

    if (type == EF_DAMAGEADD || type == EF_MAGICADD)
    {
        if (nUnique < 41 || nUnique > 50)
            return value;
    }

    if (type == EF_CRITICAL)
    {
        if (item->stEffect[1].cEffect == EF_CRITICAL2 || item->stEffect[2].cEffect == EF_CRITICAL2)
            type = EF_CRITICAL2;
    }

    if (type == EF_DAMAGE && nPos == 32)
    {
        if (item->stEffect[1].cEffect == EF_DAMAGE2 || item->stEffect[2].cEffect == EF_DAMAGE2)
            type = EF_DAMAGE2;
    }

    if (type == EF_MPADD)
    {
        if (item->stEffect[1].cEffect == EF_MPADD2 || item->stEffect[2].cEffect == EF_MPADD2)
            type = EF_MPADD2;
    }

    if (type == EF_HPADD)
    {
        if (item->stEffect[1].cEffect == EF_HPADD2 || item->stEffect[2].cEffect == EF_HPADD2)
            type = EF_HPADD2;
    }

    if (type == EF_ACADD)
    {
        if (item->stEffect[1].cEffect == EF_ACADD2 || item->stEffect[2].cEffect == EF_ACADD2)
            type = EF_ACADD2;
    }

    if (type == EF_LEVEL)
        value += g_pItemList[itemId].nReqLvl;

    if (type == EF_REQ_STR)
        value += g_pItemList[itemId].nReqStr;

    if (type == EF_REQ_INT)
        value += g_pItemList[itemId].nReqInt;

    if (type == EF_REQ_DEX)
        value += g_pItemList[itemId].nReqDex;

    if (type == EF_REQ_CON)
        value += g_pItemList[itemId].nReqCon;

    if (type == EF_POS)
        value += g_pItemList[itemId].nPos;

    if (type != EF_INCUBATE)
    {
        for (int i = 0; i < 12; i++)
        {
            if (g_pItemList[itemId].stEffect[i].sEffect != type)
                continue;

            if (g_pItemList[itemId].stEffect[i].sEffect == EF_HPADD || g_pItemList[itemId].stEffect[i].sEffect == EF_HPADD2)
                continue;

            int tvalue = g_pItemList[itemId].stEffect[i].sValue;

            if (itemId == EF_ATTSPEED && tvalue == 1)
                tvalue = 10;

            value += tvalue;
        }
    }

    if (itemId >= 2330 && itemId < 2390)
    {
        if (type == EF_MOUNTHP)
            return item->stEffect[0].sValue;

        else if (type == EF_MOUNTSANC)
            return item->stEffect[1].cEffect;

        else if (type == EF_MOUNTLIFE)
            return item->stEffect[1].cValue;

        else if (type == EF_MOUNTFEED)
            return item->stEffect[2].cEffect;

        else if (type == EF_MOUNTKILL)
            return item->stEffect[2].cValue;

        if (itemId < 2362 || itemId >= 2390 || item->stEffect[0].sValue <= 0)
            return value;

        int lv = item->stEffect[1].cEffect;
        int cd = item->sIndex - 2360;

        if (type == EF_DAMAGE)
            return g_pMountBonus[cd][0] * (lv + 20) / 100;

        else if (type == EF_MAGIC)
            return g_pMountBonus[cd][1] * (lv + 15) / 100;

        else if (type == EF_PARRY)
            return g_pMountBonus[cd][2];

        else if (type == EF_RESIST1 || type == EF_RESIST2 || type == EF_RESIST3 || type == EF_RESIST4)
            return g_pMountBonus[cd][3];
        else
            return value;
    }

    if (itemId >= 3980 && itemId <= 3994)
    {

        if (type == EF_DAMAGE)
            return g_pMountBonus2[itemId - 3980][0];

        else if (type == EF_MAGIC)
            return g_pMountBonus2[itemId - 3980][1];

        else if (type == EF_PARRY)
            return g_pMountBonus2[itemId - 3980][2];

        else if (type == EF_RESIST1 || type == EF_RESIST2 || type == EF_RESIST3 || type == EF_RESIST4)
            return g_pMountBonus2[itemId - 3980][3];
        else
            return value;
    }

    for (int i = 0; i < 3; i++)
    {
        if (item->stEffect[i].cEffect == type)
        {
            int total = item->stEffect[i].cValue;
            if (type == EF_ATTSPEED && total == 1)
                total = 10;

            value += total;
        }
    }

    return value;
}

unsigned int BASE_GetOptionColor(int nPos, unsigned int dwParam, int nValue)
{
    if (nPos >= 64)
    {
        if (nPos != 64 && nPos != 128 && nPos != 192)
        {
            return 0xFF99EE99;
        }
        else if (dwParam == 2 || dwParam == 73 || dwParam == 67)
        {
            if (nValue < 45)
            {
                return 0xFF99EE99;
            }
            else if (nValue < 45 || nValue > 54)
            {
                return 0xFFFFAA00;
            }
            else
            {
                return 0xFFFFFFAA;
            }
        }
        else if (dwParam == 60 || dwParam == 68)
        {
            if (nValue < 20)
            {
                return 0xFF99EE99;
            }
            else if (nValue < 20 || nValue > 24)
            {
                return 0xFFFFAA00;
            }
            else
            {
                return 0xFFFFFFAA;
            }
        }
        else if (dwParam == 26)
        {
            if (nValue < 21)
            {
                return 0xFF99EE99;
            }
            else if (nValue < 21 || nValue > 24)
            {
                return 0xFFFFAA00;
            }
            else
            {
                return 0xFFFFFFAA;
            }
        }
        else if (dwParam == 74)
        {
            if (nValue < 21)
            {
                return 0xFF99EE99;
            }
            else if (nValue < 21 || nValue > 24)
            {
                return 0xFFFFAA00;
            }
            else
            {
                return 0xFFFFFFAA;
            }
        }
        else
        {
            return 0xFF99EE99;
        }
    }
    else if (dwParam == 60 || dwParam == 68)
    {
        if (nPos == 2)
        {
            if (nValue < 12)
            {
                return 0xFF99EE99;
            }
            else if (nValue < 12 || nValue > 14)
            {
                return 0xFFFFAA00;
            }
            else
            {
                return 0xFFFFFFAA;
            }
        }
        else if (nValue >= 6)
        {
            if (nValue == 6)
                return 0xFFFFFFAA;
            else
                return 0xFFFFAA00;
        }
        else
        {
            return 0xFF99EE99;
        }
    }
    else if (dwParam == 42 || dwParam == 71)
    {
        if (nValue < 50)
        {
            return 0xFF99EE99;
        }
        else if (nValue < 50 || nValue >= 60)
        {
            return 0xFFFFAA00;
        }
        else
        {
            return 0xFFFFFFAA;
        }
    }
    else if (dwParam == 26)
    {
        if (nValue < 12)
        {
            return 0xFF99EE99;
        }
        else if (nValue == 12)
        {
            return 0xFFFFFFAA;
        }
        else
        {
            return 0xFFFFAA00;
        }
    }
    else if (dwParam == 74)
    {
        if (nValue < 12)
        {
            return 0xFF99EE99;
        }
        else if (nValue == 12)
        {
            return 0xFFFFFFAA;
        }
        else
        {
            return 0xFFFFAA00;
        }
    }
    else if (dwParam == 3 || dwParam == 53 || dwParam == 72)
    {
        if (nPos == 16)
        {
            if (nValue < 30)
            {
                return 0xFF99EE99;
            }
            else if (nValue == 30)
            {
                return 0xFFFFFFAA;
            }
            else
            {
                return 0xFFFFAA00;
            }
        }
        else if (nValue < 15)
        {
            return 0xFF99EE99;
        }
        else if (nValue == 15)
        {
            return 0xFFFFFFAA;
        }
        else
        {
            return 0xFFFFAA00;
        }
    }
    else if (dwParam == 2 || dwParam == 73 || dwParam == 67)
    {
        if (nPos == 32)
        {
            if (nValue < 24)
            {
                return 0xFF99EE99;
            }
            else if (nValue < 24 || nValue > 30)
            {
                return 0xFFFFAA00;
            }
            else
            {
                return 0xFFFFFFAA;
            }
        }
        else if (nValue < 18)
        {
            return 0xFF99EE99;
        }
        else if (nValue == 18)
        {
            return 0xFFFFFFAA;
        }
        else
        {
            return 0xFFFFAA00;
        }
    }
    else if (dwParam == 4 || dwParam == 45 || dwParam == 69)
    {
        if (nValue < 40)
        {
            return 0xFF99EE99;
        }
        else if (nValue == 40)
        {
            return 0xFFFFFFAA;
        }
        else
        {
            return 0xFFFFAA00;
        }
    }
    else
    {
        return 0xFF99EE99;
    }

    return 0;
}

void BASE_SetItemAmount(STRUCT_ITEM* item, int amount)
{
}

int BASE_GetMobAbility(STRUCT_MOB* mob, char Type)
{
    return 0;
}

int IsPassiveSkill(int nSkillIndex)
{
    if (nSkillIndex >= 5400)
    {
        nSkillIndex -= 5200;
    }
    else if (nSkillIndex >= 5000)
    {
        nSkillIndex -= 5000;
    }

    return g_pSpell[nSkillIndex].Passive == 1;
}

bool BASE_HasSancAdd(STRUCT_ITEM* item)
{
    for (auto i : item->stEffect)
    {
        if (i.cEffect == 43 || (i.cEffect >= 155 && i.cEffect <= 126))
            return true;
    }
  
    return false;
}

bool BASE_HasSancAdd(STRUCT_BONUSEFFECT effect)
{
    if (effect.cEffect == 43 || (effect.cEffect >= 155 && effect.cEffect <= 126))
        return true;

    return false;
}

int BASE_GetItemSancSuccess(STRUCT_ITEM* item)
{
    return 0;
}
