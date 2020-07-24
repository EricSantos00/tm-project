#include "pch.h"
#include "Basedef.h"
#include "TMGlobal.h"
#include "ItemEffect.h"
#include "ObjectManager.h"
#include "TMCamera.h"
#include "TMLog.h"
#include <WinInet.h>

HWND hWndMain;
char EncodeByte[4];

unsigned char g_pAttribute[1024][1024];
int g_pGroundMask[MAX_GROUNDMASK][4][6][6];

STRUCT_ITEMLIST g_pItemList[MAX_ITEMLIST];

STRUCT_SPELL g_pSpell[MAX_SKILLINDEX];

STRUCT_INITITEM g_pInitItem[MAX_INITITEM];
int g_dwInitItem;

int g_pHitRate[1024] = { 0, };

char g_pMessageStringTable[MAX_STRDEF][MAX_MSGSTRING];

char g_pServerList[MAX_SERVERGROUP][MAX_SERVERNUMBER][64];

/* Functions */

int BASE_InitializeBaseDef()
{
    //memset(g_pTotoList, 0, 0x1E00u);
    //memset(ChargedGuildList, 0, 0xC8u);
    //memset(KhepraGuildList, 0, 0x28u);

    BASE_InitializeServerList();

    if (!BASE_ReadSkillBin())
        return FALSE;

    if (!BASE_ReadItemList())
        return FALSE;

    if (!BASE_ReadInitItem())
        return FALSE;

    //memset(g_pClientGuildName, 0, sizeof(g_pClientGuildName));

    BASE_InitialItemRePrice();

    BASE_InitializeAttribute();

    return TRUE;
}

float BASE_ScreenResize(float size)
{
    return (float)((float)g_pDevice->m_dwScreenWidth * (float)(size / 800.0f));
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
void BASE_ReadItemPrice()
{
    FILE* fp = NULL;

    int itemprice[MAX_ITEMPRICE][2] = { 0, };

    char stemp[126] = { 0, };

    int len = sizeof(itemprice) / sizeof(int);
    memset((char*)itemprice, 0, len);
    fopen_s(&fp, "ItemPrice.bin", "rb");

    if (fp)
    {
        fread(itemprice, len, 1, fp);
        fclose(fp);
    }

    for (int k = 0; k < MAX_ITEMPRICE && itemprice[k][0]; ++k)
    {
        auto idx = itemprice[k][0];
        
        auto bufprice = g_pItemList[idx].nPrice;
        
        g_pItemList[idx].nPrice = itemprice[k][1];

        sprintf(
            stemp,
            "set item price index [%d] set%d before %d to %d",
            idx,
            itemprice[k][1],
            bufprice,
            g_pItemList[idx].nPrice);

        //Log(stemp, "-system", 0);
    }
}

void BASE_UnderBarToSpace(const char* szStr)
{
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

char BASE_GetAttr(int nX, int nY)
{
	return g_pAttribute[nY / 4 % 1024][nX / 4 % 1024];
}

float BASE_GetMountScale(int nSkinMeshType, int nMeshIndex)
{
    if (nSkinMeshType == 28)
        return 1.45f;
    else if (nSkinMeshType == 25 || nMeshIndex == 1)
        return 1.4f;
    else if (nSkinMeshType == 20 || nMeshIndex == 7)
        return 0.60000002f;
    else if (nSkinMeshType == 29 || nMeshIndex == 4)
        return 1.3f;
    else
		return 1.0f;
}

int BASE_GetColorCount(unsigned int dwColor)
{
	if (dwColor == 0xFFAAAAFF)
		return 1;
	if (dwColor == 0xFF99EE99)
		return 2;
	if (dwColor == 0xFFFFFFAA)
		return 3;
	if (dwColor == 0xFFFFAA00)
		return 4;

	return 0;
}

int BASE_UpdateItem2(int maskidx, int CurrentState, int NextState, int xx, int yy, char* pHeight, int rotate, int height)
{
    int xp;
    int yp;
    int y;
    int x;

    if (maskidx < 10 && maskidx >= 0)
    {
        for (y = 0; y <= 5; ++y)
        {
            for (x = 0; x <= 5; ++x)
            {
                xp = xx + x - 2;
                yp = yy + y - 2;
                if (xp - g_HeightPosX < 1
                    || yp - g_HeightPosY < 1
                    || xp - g_HeightPosX > g_HeightWidth - 2
                    || yp - g_HeightPosY > g_HeightHeight - 2)
                {
                    break;
                }

                //Entendi nada aqui
                auto val = g_pGroundMask[maskidx][rotate][y][x];

                int valPos = xp + g_HeightWidth * (yp - g_HeightPosY) - g_HeightPosX;

                if (strlen(pHeight) < valPos)
                    return FALSE;

                if (val)
                    pHeight[xp + g_HeightWidth * (yp - g_HeightPosY) - g_HeightPosX] = height;
            }
        }
        
        return TRUE;
    }

    return FALSE;
}

int BASE_CanEquip(STRUCT_ITEM* item, STRUCT_SCORE* score, int Pos, int Class, STRUCT_ITEM* pBaseEquip, int OriginalFace, int cktrans)
{
    int idx = item->sIndex;
 
    if (idx <= 0 || idx >= MAX_ITEMLIST)
        return FALSE;

    int nUnique = g_pItemList[idx].nUnique;

    if (Pos == EQUIP_MANTUA)
        return FALSE;

    int grade = g_pItemList[idx].nGrade;

    if (Pos != -1)
    {
        int tpos = BASE_GetItemAbility(item, EF_POS);

        if (!((tpos >> Pos) & 1))
            return FALSE;
        if (Pos == EQUIP_LEFT || Pos == EQUIP_RIGHT)
        {
            int OtherPos = Pos == EQUIP_LEFT ? EQUIP_RIGHT : EQUIP_LEFT;
            int OtherIdx = pBaseEquip[OtherPos].sIndex;
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
                    else
                    {
                        if (nUnique2 != 46)
                            return FALSE;
                        if (tpos != 128)
                            return FALSE;
                    }
                }
            }
        }
    }

    if (Class >= 22 && Class <= 25 || Class == 32)
        Class = OriginalFace;

    int trans = Class % 10;

    if (Pos == EQUIP_HELM
        && trans > 5
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

    //What could be this?
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

        int v20 = BASE_GetItemAbility(item, EF_POS);
        if (v20 != 64 && v20 != 128 && v20 != 192)
            return FALSE;
    }
    if (nUnique % 10 >= 9 && nUnique < 40 && trans < 6)
        return FALSE;

    int lvl = BASE_GetItemAbility(item, EF_LEVEL);
    int str = BASE_GetItemAbility(item, EF_REQ_STR);
    int spt = BASE_GetItemAbility(item, EF_REQ_INT);
    int agi = BASE_GetItemAbility(item, EF_REQ_DEX);
    int con = BASE_GetItemAbility(item, EF_REQ_CON);

    int v9 = BASE_GetItemAbility(item, EF_WTYPE);

    int weapontype = v9 % 10;
    int modweapon = v9 % 10;

    int v10 = (v9 % 10) / 10;

    if (Pos == EQUIP_RIGHT && weapontype)
    {
        int rate = 100;
        if (v10 || modweapon <= 1)
        {
            if (v10 == 6 && modweapon > 1)
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

//Need to review this function
int BASE_GetRoute(int x, int y, int* targetx, int* targety, char* Route, int distance, char* pHeight, int MH)
{
    int lastx = x;
    int lasty = y;
    int tx = *targetx;
    int ty = *targety;
    memset(Route, 0, 24);

    for (int i = 0; i < distance && i < 23; ++i)
    {
        if (x - g_HeightPosX < 1
            || y - g_HeightPosY < 1
            || x - g_HeightPosX > g_HeightWidth - 2
            || y - g_HeightPosY > g_HeightHeight - 2)
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
        if (tx != x || ty <= y || s >= MH + cul || s <= cul - MH)
        {
            if (tx != x || ty >= y || n >= MH + cul || n <= cul - MH)
            {
                if (tx <= x
                    || ty >= y
                    || ne >= MH + cul
                    || ne <= cul - MH
                    || (n >= MH + cul || n <= cul - MH) && (e >= MH + cul || e <= cul - MH))
                {
                    if (tx <= x || ty != y || e >= MH + cul || e <= cul - MH)
                    {
                        if (tx <= x
                            || ty <= y
                            || se >= MH + cul
                            || se <= cul - MH
                            || (s >= MH + cul || s <= cul - MH) && (e >= MH + cul || e <= cul - MH))
                        {
                            if (tx >= x
                                || ty <= y
                                || sw >= MH + cul
                                || sw <= cul - MH
                                || (s >= MH + cul || s <= cul - MH) && (w >= MH + cul || w <= cul - MH))
                            {
                                if (tx >= x || ty != y || w >= MH + cul || w <= cul - MH)
                                {
                                    if (tx >= x
                                        || ty >= y
                                        || nw >= MH + cul
                                        || nw <= cul - MH
                                        || (n >= MH + cul || n <= cul - MH) && (w >= MH + cul || w <= cul - MH))
                                    {
                                        if (tx <= x || ty >= y || e >= MH + cul || e <= cul - MH)
                                        {
                                            if (tx <= x || ty >= y || n >= MH + cul || n <= cul - MH)
                                            {
                                                if (tx <= x || ty <= y || e >= MH + cul || e <= cul - MH)
                                                {
                                                    if (tx <= x || ty <= y || s >= MH + cul || s <= cul - MH)
                                                    {
                                                        if (tx >= x || ty <= y || w >= MH + cul || w <= cul - MH)
                                                        {
                                                            if (tx >= x || ty <= y || s >= MH + cul || s <= cul - MH)
                                                            {
                                                                if (tx >= x || ty >= y || w >= MH + cul || w <= cul - MH)
                                                                {
                                                                    if (tx >= x || ty >= y || n >= MH + cul || n <= cul - MH)
                                                                    {
                                                                        if (tx == x + 1 || ty == y + 1 || tx == x - 1 || ty == y - 1)
                                                                        {
                                                                            Route[i] = 0;
                                                                            break;
                                                                        }
                                                                        if (tx != x
                                                                            || ty <= y
                                                                            || se >= MH + cul
                                                                            || se <= cul - MH
                                                                            || (s >= MH + cul || s <= cul - MH) && (e >= MH + cul || e <= cul - MH))
                                                                        {
                                                                            if (tx != x
                                                                                || ty <= y
                                                                                || sw >= MH + cul
                                                                                || sw <= cul - MH
                                                                                || (s >= MH + cul || s <= cul - MH) && (w >= MH + cul || w <= cul - MH))
                                                                            {
                                                                                if (tx != x
                                                                                    || ty >= y
                                                                                    || ne >= MH + cul
                                                                                    || ne <= cul - MH
                                                                                    || (n >= MH + cul || n <= cul - MH) && (e >= MH + cul || e <= cul - MH))
                                                                                {
                                                                                    if (tx != x
                                                                                        || ty >= y
                                                                                        || nw >= MH + cul
                                                                                        || nw <= cul - MH
                                                                                        || (n >= MH + cul || n <= cul - MH) && (w >= MH + cul || w <= cul - MH))
                                                                                    {
                                                                                        if (tx >= x
                                                                                            || ty != y
                                                                                            || sw >= MH + cul
                                                                                            || sw <= cul - MH
                                                                                            || (s >= MH + cul || s <= cul - MH) && (w >= MH + cul || w <= cul - MH))
                                                                                        {
                                                                                            if (tx >= x
                                                                                                || ty != y
                                                                                                || nw >= MH + cul
                                                                                                || nw <= cul - MH
                                                                                                || (n >= MH + cul || n <= cul - MH) && (w >= MH + cul || w <= cul - MH))
                                                                                            {
                                                                                                if (tx <= x
                                                                                                    || ty != y
                                                                                                    || se >= MH + cul
                                                                                                    || se <= cul - MH
                                                                                                    || (s >= MH + cul || s <= cul - MH)
                                                                                                    && (e >= MH + cul || e <= cul - MH))
                                                                                                {
                                                                                                    if (tx <= x
                                                                                                        || ty != y
                                                                                                        || ne >= MH + cul
                                                                                                        || ne <= cul - MH
                                                                                                        || (n >= MH + cul || n <= cul - MH)
                                                                                                        && (e >= MH + cul || e <= cul - MH))
                                                                                                    {
                                                                                                        Route[i] = 0;
                                                                                                        break;
                                                                                                    }
                                                                                                    Route[i] = 51;
                                                                                                    ++x;
                                                                                                    --y;
                                                                                                }
                                                                                                else
                                                                                                {
                                                                                                    Route[i] = 57;
                                                                                                    ++x;
                                                                                                    ++y;
                                                                                                }
                                                                                            }
                                                                                            else
                                                                                            {
                                                                                                Route[i] = 49;
                                                                                                --x;
                                                                                                --y;
                                                                                            }
                                                                                        }
                                                                                        else
                                                                                        {
                                                                                            Route[i] = 55;
                                                                                            --x;
                                                                                            ++y;
                                                                                        }
                                                                                    }
                                                                                    else
                                                                                    {
                                                                                        Route[i] = 49;
                                                                                        --x;
                                                                                        --y;
                                                                                    }
                                                                                }
                                                                                else
                                                                                {
                                                                                    Route[i] = 51;
                                                                                    ++x;
                                                                                    --y;
                                                                                }
                                                                            }
                                                                            else
                                                                            {
                                                                                Route[i] = 55;
                                                                                --x;
                                                                                ++y;
                                                                            }
                                                                        }
                                                                        else
                                                                        {
                                                                            Route[i] = 57;
                                                                            ++x;
                                                                            ++y;
                                                                        }
                                                                    }
                                                                    else
                                                                    {
                                                                        Route[i] = 50;
                                                                        --y;
                                                                    }
                                                                }
                                                                else
                                                                {
                                                                    Route[i] = 52;
                                                                    --x;
                                                                }
                                                            }
                                                            else
                                                            {
                                                                Route[i] = 56;
                                                                ++y;
                                                            }
                                                        }
                                                        else
                                                        {
                                                            Route[i] = 52;
                                                            --x;
                                                        }
                                                    }
                                                    else
                                                    {
                                                        Route[i] = 56;
                                                        ++y;
                                                    }
                                                }
                                                else
                                                {
                                                    Route[i] = 54;
                                                    ++x;
                                                }
                                            }
                                            else
                                            {
                                                Route[i] = 50;
                                                --y;
                                            }
                                        }
                                        else
                                        {
                                            Route[i] = 54;
                                            ++x;
                                        }
                                    }
                                    else
                                    {
                                        Route[i] = 49;
                                        --x;
                                        --y;
                                    }
                                }
                                else
                                {
                                    Route[i] = 52;
                                    --x;
                                }
                            }
                            else
                            {
                                Route[i] = 55;
                                --x;
                                ++y;
                            }
                        }
                        else
                        {
                            Route[i] = 57;
                            ++x;
                            ++y;
                        }
                    }
                    else
                    {
                        Route[i] = 54;
                        ++x;
                    }
                }
                else
                {
                    Route[i] = 51;
                    ++x;
                    --y;
                }
            }
            else
            {
                Route[i] = 50;
                --y;
            }
        }
        else
        {
            Route[i] = 56;
            ++y;
        }
    }

    if (lastx != x || lasty != y)
    {
        *targetx = x;
        *targety = y;
        return lastx != x || lasty != y;
    }

    return FALSE;
}

int BASE_GetItemAbilityNosanc(STRUCT_ITEM* item, char Type)
{
    int value = 0;
    int idx = item->sIndex;

    if (idx <= 0 || idx > MAX_ITEMLIST)
        return 0;
    if (idx >= 3200 && idx <= 3300)
        return 0;

    int nUnique = g_pItemList[idx].nUnique;

    if ((Type == EF_DAMAGEADD || Type == EF_MAGICADD) && (nUnique < 41 || nUnique > 50))
        return 0;

    if (Type == EF_CRITICAL && (item->stEffect[1].cEffect == 71 || item->stEffect[2].cEffect == 71))
        Type = EF_CRITICAL2;

    if (Type == EF_DAMAGE && g_pItemList[idx].nPos == 32 && (item->stEffect[1].cEffect == 73 || item->stEffect[2].cEffect == 73))
        Type = EF_DAMAGE2;

    if (Type == EF_MPADD && (item->stEffect[1].cEffect == 70 || item->stEffect[2].cEffect == 70))
        Type = EF_MPADD2;

    if (Type == EF_HPADD && (item->stEffect[1].cEffect == 69 || item->stEffect[2].cEffect == 69))
        Type = EF_HPADD2;

    if (Type == EF_ACADD && (item->stEffect[1].cEffect == 72 || item->stEffect[2].cEffect == 72))
        Type = EF_ACADD2;

    if (Type == EF_LEVEL)
        value = g_pItemList[idx].nReqLvl;

    if (Type == EF_REQ_STR)
        value = g_pItemList[idx].nReqStr;
    if (Type == EF_REQ_INT)
        value = g_pItemList[idx].nReqInt;
    if (Type == EF_REQ_DEX)
        value = g_pItemList[idx].nReqDex;
    if (Type == EF_REQ_CON)
        value = g_pItemList[idx].nReqCon;
    if (Type == EF_POS)
        value = g_pItemList[idx].nPos;

    if (Type != 78)
    {
        for (int i = 0; i < MAX_ITEMEFFECT; ++i)
        {
            if (g_pItemList[idx].stEffect[i].sValue == Type)
            {
                int tvalue = g_pItemList[idx].stEffect[i].sEffect;

                if (Type == EF_ATTSPEED && tvalue == 1)
                    tvalue = 10;

                value = tvalue;
            }
        }
    }

    int result = 0;

    if (item->sIndex < 2330 || item->sIndex >= 2390)
    {
        if (item->sIndex < 3980 || item->sIndex >= 4000)
        {
            int value = 0;
            for (int j = 0; j < MAX_STITEM_EFFECTS; ++j) {
                if (item->stEffect[j].cEffect == Type)
                {
                    int v5 = item->stEffect[j].cValue;

                    if (Type == EF_ATTSPEED && v5 == 1)
                        v5 = 10;

                    value = v5;
                }
            }

            result = value;
        }
        else
        {
            int mountId = item->sIndex - 3980;

            switch (Type)
            {
            case EF_DAMAGE:
                result = g_pMountTempBonus[mountId][0];
                break;
            case EF_MAGIC:
                result = g_pMountTempBonus[mountId][1];
                break;

            case EF_PARRY:
                result = g_pMountTempBonus[mountId][2];
                break;

            case EF_RESISTALL:
                result = g_pMountTempBonus[mountId][3];
                break;

            default:
                result = value;
                break;
            }
        }
    }
    else
    {
        if (Type == EF_MOUNTHP)
            return item->stEffect[0].sValue;
        if (Type == EF_MOUNTSANC)
            return item->stEffect[1].cEffect;
        if (Type == EF_MOUNTLIFE)
            return item->stEffect[1].cValue;
        if (Type == EF_MOUNTFEED)
            return item->stEffect[2].cEffect;
        if (Type == EF_MOUNTKILL)
            return item->stEffect[2].cValue;

        int lv = item->stEffect[1].cEffect;
        int cd = item->sIndex - 2360;

        if (Type == EF_DAMAGE)
            return g_pMountBonus[cd][0] * ((lv + 20) / 100);
        else if (Type == EF_MAGIC)
            return g_pMountBonus[cd][1] * ((lv + 15) / 100);
        else if (Type == EF_PARRY)
            return g_pMountBonus[cd][2];
        else if (Type == EF_RESISTALL)
            result = g_pMountBonus[cd][3];
        else
            result = value;
    }
    return result;
}

int BASE_GetMeshIndex(short sIndex)
{
    STRUCT_ITEM item;
    BASE_ClearItem(&item);

    item.sIndex = sIndex;

    int nPos = BASE_GetItemAbility(&item, EF_POS);
    int nClassType = BASE_GetItemAbility(&item, EF_CLASS);
    int nClassIndex = 0;

    if (g_pItemList[sIndex].nIndexMesh >= 40
        && g_pItemList[sIndex].nIndexMesh < 50
        && (nPos & 4 || nPos & 8 || nPos & 0x10 || nPos & 0x20))
    {
        if (g_pItemList[sIndex].nIndexMesh == 40)
            return FALSE;
        else
        {
            switch (nClassType)
            {
            case 1:
                nClassIndex = 0;
                break;
            case 4:
                nClassIndex = 1;
                break;
            case 2:
                nClassIndex = 2;
                break;
            case 8:
                nClassIndex = 3;
                break;
            }
            if (nPos & 4)
            {
                nPos = 0;
            }
            else if (nPos & 8)
            {
                nPos = 1;
            }
            else if (nPos & 0x10)
            {
                nPos = 2;
            }
            else if (nPos & 0x20)
            {
                nPos = 3;
            }
            return nPos + 4 * (g_pItemList[sIndex].nIndexMesh + nClassIndex - 41) + 1401;
        }
    }
    else
    {
        switch (nClassType)
        {
        case 1:
            nClassIndex = 0;
            break;
        case 2:
            nClassIndex = 200;
            break;
        case 4:
            nClassIndex = 20;
            break;
        case 8:
            nClassIndex = 220;
            break;
        }

        if (nClassType > 8)
            return g_pItemList[sIndex].nIndexMesh;
        else if (nPos & 2)
            return g_pItemList[sIndex].nIndexMesh + nClassIndex + 1001;
        else if (nPos & 4)
            return g_pItemList[sIndex].nIndexMesh + nClassIndex + 1041;
        else if (nPos & 8)
            return g_pItemList[sIndex].nIndexMesh + nClassIndex + 1081;
        else if (nPos & 0x10)
            return g_pItemList[sIndex].nIndexMesh + nClassIndex + 1121;
        else if (nPos & 0x20)
            return g_pItemList[sIndex].nIndexMesh + nClassIndex + 1161;
        else
            return g_pItemList[sIndex].nIndexMesh;
    }

    return FALSE;
}

int BASE_GetItemSancSuccess(STRUCT_ITEM* item)
{
    if (item->sIndex < 2330 || item->sIndex >= 2390)
    {
        if (item->sIndex < 3200 || item->sIndex >= 3300)
        {
            if (item->sIndex < 3980 || item->sIndex >= 4000)
            {
                int sanc = 0;
                if (item->stEffect[0].cEffect != EF_SANC && item->stEffect[1].cEffect != EF_SANC && item->stEffect[2].cEffect != EF_SANC)
                {
                    if (item->stEffect[0].cEffect >= EF_STARTCOL && item->stEffect[0].cEffect <= EF_MAXCOL)
                        sanc = item->stEffect[0].cValue;
                    else if(item->stEffect[1].cEffect >= EF_STARTCOL && item->stEffect[1].cEffect <= EF_MAXCOL)
                        sanc = item->stEffect[1].cValue;
                    else if (item->stEffect[2].cEffect >= EF_STARTCOL && item->stEffect[2].cEffect <= EF_MAXCOL)
                        sanc = item->stEffect[2].cValue;
                }
                else if (item->stEffect[0].cEffect == EF_SANC)
                    sanc = item->stEffect[0].cValue;
                else if (item->stEffect[1].cEffect == EF_SANC)
                    sanc = item->stEffect[1].cValue;
                else
                    sanc = item->stEffect[2].cValue;

                if (sanc <= 210)
                    return sanc / 10;
                else
                    return 0;
            }
        }
    }

    return 0;
}

int BASE_GetHttpRequest(char* httpname, char* Request, int MaxBuffer)
{
    HINTERNET hHttpFile;
    unsigned int dwBytesRead;
    void* hSession;

    dwBytesRead = 0;
    hSession = InternetOpenA("MS", 0, 0, 0, 0);
    if (hSession)
    {
        hHttpFile = InternetOpenUrlA(hSession, httpname, 0, 0, 0x4000000u, 0);

        if (hHttpFile)
        {
            InternetReadFile(hHttpFile, Request, MaxBuffer, (LPDWORD)&dwBytesRead);
            InternetCloseHandle(hHttpFile);
            if (dwBytesRead >= 0x400)
                dwBytesRead = 1023;
            Request[dwBytesRead] = 0;
            InternetCloseHandle(hSession);
            
            return TRUE;
        }
        else
        {
            GetLastError();
            InternetCloseHandle(hSession);
            
            return FALSE;
        }
    }

    return FALSE;
}

int BASE_GetManaSpent(int SkillNumber, int SaveMana, int Special)
{
    return g_pSpell[SkillNumber].ManaSpent * (Special / 2 + 100) / 100 * (100 - SaveMana) / 100;
}

int BASE_GetItemAmount(STRUCT_ITEM* item)
{
    if (item->stEffect[0].cEffect == EF_AMOUNT || item->stEffect[1].cEffect == EF_AMOUNT || item->stEffect[2].cEffect == EF_AMOUNT)
    {
        if (item->stEffect[0].cEffect == EF_AMOUNT)
            return item->stEffect[0].cValue;
        else if (item->stEffect[1].cEffect == EF_AMOUNT)
            return item->stEffect[1].cValue;
        else if (item->stEffect[2].cEffect == EF_AMOUNT)
            return item->stEffect[2].cValue;
    }

    return 0;
}

int BASE_GetSkillDamage(int skillnum, STRUCT_MOB* mob, int weather, int weapondamage, int OriginalFace)
{
    int instanceindex = g_pSpell[skillnum].InstanceType;

    int level = mob->CurrentScore.Level;
    if (level < 0)
        level = 0;
    if (level >= 400)
        level = 400;

    int special = mob->CurrentScore.Special[skillnum % 24 / 8 + 1];
    int base = g_pSpell[skillnum].InstanceValue;
    int affectbase = g_pSpell[skillnum].AffectType;
    int skillclass = skillnum / 8 % 3;
    int dam = 0;

    if (instanceindex)
    {
        if (instanceindex < 1 || instanceindex > 5)
        {
            if (instanceindex == 6)
            {
                dam = base + 3 * special / 2;
                if (skillnum == 29 && mob->LearnedSkill[0] & 128)
                    dam = 120 * dam / 100;
            }
            else if (instanceindex == 11)
            {
                dam = g_pSpell[skillnum].ForceDamage;
            }
            else
            {
                dam = 2 * mob->Magic;
            }
        }
        else
        {
            int skind = skillnum / 8;
            int trans = 0;
            if (OriginalFace % 10 > 5)
                trans = 1;
            if (trans)
            {
                if (skillnum == 97)
                {
                    dam = base + 15 * level;
                }
                else if (mob->Class || skind != 1)
                {
                    if (mob->Class || skind == 1)
                    {
                        switch (mob->Class)
                        {
                        case 1:
                            dam = mob->CurrentScore.Int / 30 + mob->CurrentScore.Int / 3 + level + base + 2 * special;
                            break;
                        case 2:
                            dam = mob->CurrentScore.Int / 30 + mob->CurrentScore.Int / 3 + level + base + 2 * special;
                            break;
                        case 3:
                            if (skillnum == 79)
                                dam = mob->CurrentScore.Damage;
                            else
                                dam = 3 * weapondamage + 3 * mob->CurrentScore.Str + level / 2 + special + base;
                            break;
                        }
                    }
                    else
                    {
                        dam = weapondamage + mob->CurrentScore.Int / 4 + level + special + base + mob->CurrentScore.Int / 40;
                    }
                }
                else
                {
                    dam = 3 * weapondamage + 3 * mob->CurrentScore.Str + level + special + base;
                }
            }
            else if (skillnum == 97)
            {
                dam = base + 15 * level;
            }
            else if (mob->Class || skind != 1)
            {
                if (mob->Class || skind == 1)
                {
                    switch (mob->Class)
                    {
                    case 1:
                        dam = mob->CurrentScore.Int / 30 + mob->CurrentScore.Int / 3 + level / 2 + special + base;
                        break;
                    case 2:
                        dam = mob->CurrentScore.Int / 30 + mob->CurrentScore.Int / 3 + level / 2 + special + base;
                        break;
                    case 3:
                        if (skillnum == 79)
                            dam = mob->CurrentScore.Damage;
                        else
                            dam = 3 * weapondamage + 3 * mob->CurrentScore.Str + level / 2 + special + base;
                        break;
                    }
                }
                else
                {
                    dam = weapondamage + mob->CurrentScore.Int / 4 + level / 2 + special + base + mob->CurrentScore.Int / 40;
                }
            }
            else
            {
                dam = 3 * weapondamage + 3 * mob->CurrentScore.Str + level / 2 + special + base;
            }
            if (weather == 1)
            {
                if (instanceindex == 2)
                    dam = 90 * dam / 100;
                if (instanceindex == 5)
                    dam = 130 * dam / 100;
            }
            else if (weather == 2 && instanceindex == 3)
            {
                dam = 120 * dam / 100;
            }
            if (skillnum != 97)
            {
                if (skillnum == 79)
                    return dam;
                if ((mob->Class || skind != 1) && mob->Class != 3)
                {
                    dam = 5 * (dam * (4 * mob->Magic + 100) / 100);
                }
                else
                {
                    dam = 5 * dam / 4;
                }
            }
            if ((1 << (8 * skillclass + 7)) & mob->LearnedSkill[0])
            {
                switch (mob->Class)
                {
                case 0:
                    if (skillclass)
                    {
                        if (skillclass == 1)
                        {
                            dam = 120 * dam / 100;
                        }
                        else if (skillclass == 2)
                        {
                            dam = 115 * dam / 100;
                        }
                    }
                    else
                    {
                        dam = 115 * dam / 100;
                    }
                    break;
                case 1:
                    if (skillclass)
                    {
                        if (skillclass == 1)
                        {
                            dam = 115 * dam / 100;
                        }
                        else if (skillclass == 2)
                        {
                            dam = 115 * dam / 100;
                        }
                    }
                    else
                    {
                        dam = 110 * dam / 100;
                    }
                    break;
                case 2:
                    if (!skillclass)
                        dam = 110 * dam / 100;
                    break;
                case 3:
                    if (skillclass)
                    {
                        if (skillclass == 1)
                        {
                            dam = 110 * dam / 100;
                        }
                        else if (skillclass == 2)
                        {
                            dam = 120 * dam / 100;
                        }
                    }
                    else
                    {
                        dam = 110 * dam / 100;
                    }
                    break;
                default:
                    return dam;
                }
            }
        }
    }
    else
    {
        switch (skillnum)
        {
        case 11:
            dam = affectbase + special / 10;
            break;
        case 13:
            dam = affectbase + 3 * special;
            break;
        case 41:
            dam = special / 25 + 2;
            break;
        case 43:
            dam = affectbase + special / 3 + 15;
            break;
        case 44:
            dam = 5 * (special / 3 + 15);
            break;
        case 45:
            dam = affectbase + special / 10;
            break;
        }
    }
    return dam;
}

/*int BASE_IsInView(TMVector3 vec, float fRadius)
{
    D3DXVECTOR3 vTemp;
    D3DXVECTOR3 vPosTransformed;
    D3DXVECTOR3 vecPos[9];

    if (g_pObjectManager->m_pCamera->m_fVerticalAngle < -0.39269909f)
    {
        int bVisible = 0;

        vTemp = D3DXVECTOR3();
        vPosTransformed = D3DXVECTOR3();

        for (int i = 0; i < 9; ++i)
        {
            vecPos[i].x = vec.x;
            vecPos[i].y = vec.y;
            vecPos[i].z = vec.z;
        }

        vecPos[1].x = vecPos[1].x - fRadius;
        vecPos[2].x = vecPos[2].x + fRadius;
        vecPos[3].z = vecPos[3].z - fRadius;
        vecPos[4].z = vecPos[4].z + fRadius;
        vecPos[5].x = vecPos[5].x - fRadius;
        vecPos[5].z = vecPos[5].z - fRadius;
        vecPos[6].x = vecPos[6].x - fRadius;
        vecPos[6].z = vecPos[6].z + fRadius;
        vecPos[7].x = vecPos[7].x + fRadius;
        vecPos[7].z = vecPos[7].z - fRadius;
        vecPos[8].x = vecPos[8].x + fRadius;
        vecPos[8].z = vecPos[8].z + fRadius;

        for (int ia = 0; ia < 9; ++ia)
        {

            D3DXVec3TransformCoord(&vTemp, &vecPos[ia], &g_pDevice->m_matView);
            D3DXVec3TransformCoord(&vPosTransformed, &vTemp, &g_pDevice->m_matProj);

            if (vPosTransformed.z >= -0.0099999998f && vPosTransformed.z < 1.0)
            {
                auto vPosInX = floor((float)((float)(vPosTransformed.x + 1.0f) * (double)(g_pDevice->m_dwScreenWidth - g_pDevice->m_nWidthShift)) / 2.0f);
                auto vPosInY = floor((float)((float)(vPosTransformed.y + 1.0f) * (double)(g_pDevice->m_dwScreenHeight - g_pDevice->m_nHeightShift)) / 2.0f);

                if (vPosInX > -30
                    && vPosInX < (signed int)(g_pDevice->m_dwScreenWidth - g_pDevice->m_nWidthShift + 30)
                    && vPosInY > -30
                    && vPosInY < (signed int)(g_pDevice->m_dwScreenHeight - g_pDevice->m_nHeightShift + 30))
                {
                    bVisible = 1;
                    break;
                }
            }
        }
        return bVisible;
    }
    else
        return TRUE; //??
}
*/
int BASE_IsInLowZone(int nX, int nY)
{
    int nX4 = nX / 4;
    int nY4 = nY / 4;
 
    if (nY / 4 < 1024 && nX4 < 1024 && nY4 >= 0 && nX4 >= 0)
    {
        return ((g_pAttribute[nY4][nX4]) & 128) != 0;
    }
    else
    {
        LOG_WRITELOG("\nWrong Position [X:%d Y:%d]\n");
        MessageBoxA(g_pApp->m_hWnd, "Wrong Character Information.", "Error", MB_OK);
        PostMessageA(g_pApp->m_hWnd, 16, 0, 0);

        return FALSE;
    }
}

int BASE_Get3DTo2DPos(float fX, float fY, float fZ, int* pX, int* pY)
{
    return TRUE;
}

unsigned int BASE_GetItemColor(STRUCT_ITEM* pItem)
{
    if (pItem)
    {
        int dwColor = 0xFF99EE99;
        int nMaxValue = 0;
        int dwMaxParm = 0;

        for (int i = 0; i < 49; ++i)
        {
            int parm = dwEFParam[i];

            //Gambiarra KKK?
            if (parm == 45)
                parm = 69;
            if (parm == 46)
                parm = 70;

            int nPos = BASE_GetItemAbility(pItem, EF_POS);

            int nValue2 = 0;
            int nValue3 = 0;
            int nColor = 0;

            if (parm != 42 && parm != 53 && (nPos != 32 || parm != 2))
            {
                nValue2 = BASE_GetBonusItemAbility(pItem, parm);
                nValue3 = BASE_GetBonusItemAbilityNosanc(pItem, parm);
                nColor = BASE_GetOptionColor(nPos, (unsigned short)parm, nValue3);
            }
            else
            {
                nValue2 = BASE_GetItemAbility(pItem, parm);
                nValue3 = BASE_GetItemAbilityNosanc(pItem, parm);
                nColor = BASE_GetOptionColor(nPos, (unsigned short)parm, nValue3);
            }

            int dwTempColor = nColor;

            if (dwMaxParm && (unsigned short)dwMaxParm == (unsigned short)parm)
            {
                nMaxValue += nValue3;
                dwColor = BASE_GetOptionColor(nPos, (unsigned short)parm, nValue2);
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
    else
        return 0xFFAAAAFF;
}

int BASE_ReadItemName(char* filename)
{
    FILE* fpBin = NULL;
    FILE* fp = NULL;

    char temp2[256] = { 0, };
    char temp1[256] = { 0, };
    char str[1024] = { 0, };
    char Name[256] = { 0, };
    char temp[256] = { 0, };
    char ReName[256] = { 0, };

    sprintf(temp, "%s", filename);
    fopen_s(&fp, temp, "rb");

    if (!fp)
    {
        sprintf(temp, "../../TMSRV/Run/%s", filename);
        fopen_s(&fp, temp, "rb");
    }

    if (fp)
    {
        fopen_s(&fpBin, "Itemname.bin", "wb");

        if (fpBin)
        {
            while (1)
            {
                int Index = -1;

                memset(Name, 0, 256);
                memset(ReName, 0, 256);

                if (!fgets(str, 1024, fp))
                    break;

                for (int i = 0; i < 1024; ++i)
                {
                    if (str[i] == 44)
                        str[i] = 32;

                    if (!str[i])
                        break;
                }

                temp1[0] = 0;
                temp2[0] = 0;

                sscanf(str, "%d %s %s", &Index, Name, ReName);

                if (Index != -1)
                {
                    if (Index < MAX_ITEMLIST)
                    {
                        int len = strlen(Name);

                        if (len > 0 && len < 63)
                        {
                            int len2 = strlen(ReName);
                            if (len2 > 0 && len2 < 63)
                            {
                                ReName[63] = 0;
                                ReName[62] = 0;

                                strcpy(g_pItemList[Index].Name, ReName);

                                fwrite(&Index, 4, 1, fpBin);

                                for (int nTemp = 0; nTemp < 62; ++nTemp)
                                    ReName[nTemp] += nTemp;

                                fwrite(ReName, 64, 1, fpBin);
                            }
                            else
                            {
                                //Log("too long Item Name", "system", 0);
                            }
                        }
                        else
                        {
                            //Log("too long Item Name", "system", 0);
                        }
                    }
                    else
                    {
                        MessageBoxA(0, str, "check MAX_ITEMLIST", 0);
                    }
                }
            }

            fclose(fpBin);
            fclose(fp);

            return TRUE;
        }
    }

    return FALSE;
}

void BASE_InitialItemRePrice()
{
    //?????? WTF THIS FUCKING FUNCTION
    g_pItemList[412].nPrice = 4000000;
    g_pItemList[413].nPrice = 8000000;
    g_pItemList[419].nPrice = 400000;
    g_pItemList[420].nPrice = 800000;
}

void BASE_SetItemAmount(STRUCT_ITEM* item, int amount)
{
    if (item->sIndex == 419
        || item->sIndex == 420
        || item->sIndex == 412
        || item->sIndex == 413
        || item->sIndex >= 2390 && item->sIndex <= 2418)
    {
        if (item->stEffect[0].cEffect == EF_UNIQUE)
        {
            item->stEffect[0].cEffect = 0;
            item->stEffect[0].cValue = 0;
        }
        if (item->stEffect[1].cEffect == EF_UNIQUE)
        {
            item->stEffect[1].cEffect = 0;
            item->stEffect[1].cValue = 0;
        }
        if (item->stEffect[2].cEffect == EF_UNIQUE)
        {
            item->stEffect[2].cEffect = 0;
            item->stEffect[2].cValue = 0;
        }
    }
    if (item->stEffect[0].cEffect != EF_AMOUNT && item->stEffect[1].cEffect != EF_AMOUNT && item->stEffect[2].cEffect != EF_AMOUNT)
    {
        if (!item->stEffect[0].cEffect || !item->stEffect[1].cEffect || !item->stEffect[2].cEffect)
        {
            if (item->stEffect[0].cEffect)
            {
                if (item->stEffect[1].cEffect)
                {
                    item->stEffect[2].cEffect = EF_AMOUNT;
                    item->stEffect[2].cValue = amount;
                }
                else
                {
                    item->stEffect[1].cEffect = EF_AMOUNT;
                    item->stEffect[1].cValue = amount;
                }
            }
            else
            {
                item->stEffect[0].cEffect = EF_AMOUNT;
                item->stEffect[0].cValue = amount;
            }
        }
    }
    else if (item->stEffect[0].cEffect == EF_AMOUNT)
    {
        item->stEffect[0].cValue = amount;
    }
    else if (item->stEffect[1].cEffect == EF_AMOUNT)
    {
        item->stEffect[1].cValue = amount;
    }
    else
    {
        item->stEffect[2].cValue = amount;
    }
}

void BASE_WriteItemList(int nItemList)
{
    FILE* fp = NULL;
    FILE* fpCSum = NULL;

    int size = sizeof(g_pItemList);
    char* temp = (char*)&g_pItemList;

    for (int i = 0; i < size; ++i)
        temp[i] ^= 0x5A;

    if (!nItemList)
    {
        fopen_s(&fp, ".\\ItemList.bin", "wb");

        if (!fp)
        {
            MessageBoxA(NULL, "Can't generate ItemList.bin file", "ERROR", MB_OK);
            return;
        }

        fwrite(temp, size, 1, fp);
    }

    int sum = BASE_GetSum2((char*)&g_pItemList, size);

    int nRand = rand();

    if (!nItemList)
    {
        fwrite(&nRand, 4, 1, fp);
        fclose(fp);
    }

    fpCSum = NULL;
    if (nItemList)
        fopen_s(&fpCSum, "..\\ItemCSum.h", "a+");
    else
        fopen_s(&fpCSum, "..\\ItemCSum.h", "wt");

    if (fpCSum)
    {
        if (nItemList)
            fprintf(fpCSum, "#define ITEM_CHECKSUM2 %d\n", sum);
        else
            fprintf(fpCSum, "#define ITEM_CHECKSUM %d\n", sum);

        fclose(fpCSum);
    }
}

int BASE_GetSubGuild(int item)
{
    int ret = 0;

    if (item >= 3 && item <= 8)
        ret = item % 3 + 1;

    return ret;
}

void BASE_InitMission()
{
    FILE* fp = NULL;

    fopen_s(&fp, "Missionitems.bin", "rb");

    if (fp)
    {
        //Need to create the g_sMission, maybe use the STRUCT_MISSION
        //fread(&g_sMission, sizeof(g_sMission), 1, fp);
        fclose(fp);
    }
}

int BASE_CanEquip_RecvRes(STRUCT_REQ* req, STRUCT_ITEM* item, STRUCT_SCORE* score, int Pos, int Class, STRUCT_ITEM* pBaseEquip, int OriginalFace)
{
    if (!req)
        return FALSE;

    req->Class = 0;
    req->Level = 0;
    req->Str = 0;
    req->Int = 0;
    req->Dex = 0;
    req->Con = 0;

    int idx = item->sIndex;

    if (idx <= 0 || idx >= MAX_ITEMLIST)
        return FALSE;

    int nUnique = g_pItemList[idx].nUnique;

    if (Pos == EQUIP_MANTUA)
        return FALSE;

    int grade = g_pItemList[idx].nGrade;

    if (Pos != -1)
    {
        int itemPos = BASE_GetItemAbility(item, EF_POS);

        if (!((itemPos >> Pos) & 1))
            return FALSE;

        if (Pos == EQUIP_LEFT || Pos == EQUIP_RIGHT)
        {
            int OtherPos = Pos == EQUIP_LEFT ? EQUIP_RIGHT : EQUIP_LEFT;
            int OtherIdx = pBaseEquip[OtherPos].sIndex;

            if (OtherIdx > 0 && OtherIdx < MAX_ITEMLIST)
            {
                int nUnique2 = g_pItemList[OtherIdx].nUnique;
                int otherpos = BASE_GetItemAbility(&pBaseEquip[OtherPos], EF_POS);

                if (itemPos == 64 || otherpos == 64)
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
                        if (itemPos != 128)
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

    int trans = Class % 10;

    if (Pos != EQUIP_HELM || item->sIndex == 747 || trans <= 5)
    {
        if (mount != 19 && mount != 20 || trans > 5)
        {
            req->Class = 1;

            int transitem = BASE_GetItemAbility(item, EF_TRANS);
            if (transitem == 1)
            {
                if (trans < 6)
                    req->Class = 0;
            }
            else if (transitem == 2 && trans >= 6)
            {
                req->Class = 0;
            }

            int cls = (BASE_GetItemAbility(item, EF_CLASS) >> Class / 10) & 1;
            int tpos = BASE_GetItemAbility(item, EF_POS);

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

            int lvl = BASE_GetItemAbility(item, EF_LEVEL);
            int str = BASE_GetItemAbility(item, EF_REQ_STR);
            int spt = BASE_GetItemAbility(item, EF_REQ_INT);
            int agi = BASE_GetItemAbility(item, EF_REQ_DEX);
            int con = BASE_GetItemAbility(item, EF_REQ_CON);
            int WeaponType = BASE_GetItemAbility(item, EF_WTYPE);
            int modweapon = WeaponType % 10;
            int divweapon = (WeaponType % 10) / 10;

            if (Pos == EQUIP_RIGHT && WeaponType % 10)
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

            return TRUE;
        }
    }

    return FALSE;
}

int BASE_GetItemColorEffect(STRUCT_ITEM* item)
{
    int effect = 0;

    if (item->stEffect[0].cEffect != EF_SANC && item->stEffect[1].cEffect != EF_SANC && item->stEffect[2].cEffect != EF_SANC)
    {
        if (item->stEffect[0].cEffect >= EF_STARTCOL && item->stEffect[0].cEffect <= EF_MAXCOL)
            effect = item->stEffect[0].cEffect;
        else if (item->stEffect[1].cEffect >= EF_STARTCOL && item->stEffect[1].cEffect <= EF_MAXCOL)
            effect = item->stEffect[1].cEffect;
        else if (item->stEffect[2].cEffect >= EF_STARTCOL && item->stEffect[2].cEffect <= EF_MAXCOL)
            effect = item->stEffect[2].cEffect;
    }
    else if (item->stEffect[0].cEffect == EF_SANC)
        effect = item->stEffect[0].cEffect;
    else if (item->stEffect[1].cEffect == EF_SANC)
        effect = item->stEffect[1].cEffect;
    else if (item->stEffect[2].cEffect == EF_SANC)
        effect = item->stEffect[2].cEffect;

    return effect;
}

int BASE_CheckValidString(char* name)
{
    int sLength = strlen(name);

    if (sLength >= 4 && sLength < 16)
    {
        for (int j = 0; j < sLength; ++j)
        {
            auto x = name[j];
            if (x >= 0)
            {
                if ((x < 97 || x > 122) && (x < 65 || x > 90) && (x < 48 || x > 57) && x != 45)
                    return FALSE;
            }
            else if (!name[++j])
            {
                return FALSE;
            }
        }

        return TRUE;
    }

    return FALSE;
}

int BASE_GetSum2(char* p, int size)
{
    int sum = 0;

    for (int i = 0; i < size; ++i)
    {
        int mod = i % 9;

        if (!(i % 9))
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

void BASE_InitEffectString()
{
}

unsigned int BASE_GetItemTenColor(STRUCT_ITEM* pItem)
{
    if (BASE_GetItemSanc(pItem) > 9)
    {
        auto sanc = 0;

        if (!(pItem->stEffect[0].cEffect == EF_SANC || (pItem->stEffect[0].cEffect >= EF_STARTCOL && pItem->stEffect[0].cEffect <= EF_MAXCOL)))
        {
            if (!((pItem->stEffect[1].cEffect == EF_SANC
                || (pItem->stEffect[1].cEffect >= EF_STARTCOL && pItem->stEffect[1].cEffect <= EF_MAXCOL))))
            {
                if (!((pItem->stEffect[2].cEffect == EF_SANC
                    || (pItem->stEffect[2].cEffect >= EF_STARTCOL && pItem->stEffect[2].cEffect <= EF_MAXCOL))))
                {
                    if ((pItem->stEffect[0].cEffect == EF_SANC || (pItem->stEffect[0].cEffect >= EF_STARTCOL && pItem->stEffect[0].cEffect <= EF_MAXCOL)))
                    {
                        sanc = pItem->stEffect[0].cValue;
                    }
                    else
                    {
                        if (pItem->stEffect[1].cEffect == EF_SANC
                            || (pItem->stEffect[1].cEffect < EF_STARTCOL || pItem->stEffect[1].cEffect > EF_MAXCOL))
                            sanc = pItem->stEffect[1].cValue;
                        else
                            sanc = pItem->stEffect[2].cValue;
                    }
                }
            }
        }


        return (sanc - 230) % 4 + 5;
    }

    return FALSE;
}

int BASE_ReadTOTOList(char* szFileName)
{
    return FALSE;
}

void BASE_UnderBarToSpace(char* szStr)
{
    char* pNext = NULL;

    int nStrLen = strlen(szStr);
    pNext = strchr(szStr, 95);

    do
    {
        if (!pNext)
            break;

        *pNext = 32;
        pNext = strchr(pNext, 95);

        --nStrLen;
    } while (nStrLen >= 0);
}

void BASE_SortTradeItem(STRUCT_ITEM* Item, int Type)
{
}

int BASE_GetVillage(int x, int y)
{
    //Need to build this and put in the properly place
    const int g_pVillage[5][2] = { 0, };

    for (int i = 0; i < 5; ++i)
    {
        if (x >= g_pVillage[i][0]
            && x <= g_pVillage[i][0]
            && y >= g_pVillage[i][1]
            && y <= g_pVillage[i][1])
        {
            return i;
        }
    }

    return 5;
}

int BASE_GetItemAbility(STRUCT_ITEM* item, char Type)
{
    int value = 0;

    int idx = item->sIndex;

    if (idx <= 0 || idx > MAX_ITEMLIST) //MAX_ITEMLIST
        return 0;

    int nUnique = g_pItemList[idx].nUnique;
    int nPos = g_pItemList[idx].nPos;

    if ((Type == EF_DAMAGEADD || Type == EF_MAGICADD) && (nUnique < 41 || nUnique > 50))
        return 0;

    if (Type == EF_CRITICAL && (item->stEffect[1].cEffect == 71 || item->stEffect[2].cEffect == 71))
        Type = EF_CRITICAL2;

    if (Type == EF_DAMAGE && g_pItemList[idx].nPos == 32 && (item->stEffect[1].cEffect == 73 || item->stEffect[2].cEffect == 73))
        Type = EF_DAMAGE2;

    if (Type == EF_MPADD && (item->stEffect[1].cEffect == 70 || item->stEffect[2].cEffect == 70))
        Type = EF_MPADD2;

    if (Type == EF_HPADD && (item->stEffect[1].cEffect == 69 || item->stEffect[2].cEffect == 69))
        Type = EF_HPADD2;

    if (Type == EF_ACADD && (item->stEffect[1].cEffect == 72 || item->stEffect[2].cEffect == 72))
        Type = EF_ACADD2;

    if (Type == EF_LEVEL)
        value = g_pItemList[idx].nReqLvl;

    if (Type == EF_REQ_STR)
        value = g_pItemList[idx].nReqStr;
    if (Type == EF_REQ_INT)
        value = g_pItemList[idx].nReqInt;
    if (Type == EF_REQ_DEX)
        value = g_pItemList[idx].nReqDex;
    if (Type == EF_REQ_CON)
        value = g_pItemList[idx].nReqCon;
    if (Type == EF_POS)
        value = g_pItemList[idx].nPos;

    if (Type != EF_INCUBATE)
    {
        for (int i = 0; i < 12; ++i)
        {
            if (g_pItemList[idx].stEffect[i].sValue == Type
                || (g_pItemList[idx].stEffect[i].sValue == EF_HPADD && Type == EF_HPADD2))
            {
                int tvalue = g_pItemList[idx].stEffect[i].sEffect;

                if (Type == EF_ATTSPEED && tvalue == 1)
                    tvalue = 10;

                value += tvalue;
            }
        }
    }

    if (item->sIndex < 2330 || item->sIndex >= 2390)
    {
        if (item->sIndex < 3980 || item->sIndex >= 4000)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (item->stEffect[j].cEffect == Type)
                {
                    int v6 = item->stEffect[j].cValue;

                    if (Type == EF_ATTSPEED && v6 == 1)
                        v6 = 10;

                    value += v6;
                }
            }

            int sanc = BASE_GetItemSanc(item);

            if (item->sIndex <= 40)
                sanc = 0;

            if (sanc >= 9 && nPos & 0xF00)
                ++sanc;

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
                if (sanc > 10) {
                    if (sanc >= 11) {
                        int UpSanc = sanc - 10;

                        if (sanc == 11) {
                            UpSanc = 220;
                        }
                        else
                        {
                            switch (UpSanc) {
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
                        }

                        return UpSanc * 10 * value / 100 / 10;
                    }
                }
                else {
                    return value * (sanc + 10) / 10;
                }
            }

            if (Type == EF_RUNSPEED)
            {
                if (value >= 3)
                    value = 2;

                if (value > 0 && sanc >= 9)
                    ++value;
            }

            if (Type == EF_HWORDGUILD || Type == EF_LWORDGUILD)
                return value;
            if (Type == EF_REGENMP || Type == EF_REGENHP)
                return (value * sanc);
            if (Type == EF_GRID && (value < 0 || value > 7))
                return 0;
        }
        else
        {
            int mountId = item->sIndex - 3980;

            switch (Type) {
            case EF_DAMAGE:
                return g_pMountTempBonus[mountId][0];
                break;
            case EF_MAGIC:
                return g_pMountTempBonus[mountId][1];
                break;
            case EF_PARRY:
                return g_pMountTempBonus[mountId][2];
                break;
            case EF_RESISTALL:
                return g_pMountTempBonus[mountId][3];
                break;
            default:
                return value;
                break;
            }
        }
    }
    else
    {
        if (Type == EF_MOUNTHP)
            return item->stEffect[0].sValue;
        if (Type == EF_MOUNTSANC)
            return item->stEffect[1].cEffect;
        if (Type == EF_MOUNTLIFE)
            return item->stEffect[1].cValue;
        if (Type == EF_MOUNTFEED)
            return item->stEffect[2].cEffect;
        if (Type == EF_MOUNTKILL)
            return item->stEffect[2].cValue;

        int lv = item->stEffect[1].cEffect;
        int cd = item->sIndex - 2360;

        if (Type == EF_DAMAGE)
            return g_pMountBonus[cd][0] * ((lv + 20) / 100);
        else if (Type == EF_MAGIC)
            return g_pMountBonus[cd][1] * ((lv + 15) / 100);
        else if (Type == EF_PARRY)
            return g_pMountBonus[cd][2];
        else if (Type == EF_RESISTALL)
            return g_pMountBonus[cd][3];
        else
            return value;
    }

    return 0;
}

int BASE_InitializeClientGuildName(int group, int nFile)
{
    return FALSE;
}

int BASE_GetMobAbility(STRUCT_MOB* mob, char Type)
{
    int nUnique[16] = { 0, };

    int value = 0;

    if (Type == EF_RANGE)
    {
        int valuea = BASE_GetMaxAbility(mob, Type);
        if (valuea < 2 && mob->Class == 3)
        {
            if (mob->LearnedSkill[0] & 0x80000)
                valuea = 2;
        }

        return valuea;
    }
    else
    {
        memset(nUnique, 0, sizeof(nUnique));

        for (int i = 0; i < MAX_EQUIPMENT; ++i)
        {
            if (mob->Equip[i].sIndex || i == EQUIP_RIGHT)
            {
                if (i >= EQUIP_HELM && i <= EQUIP_BOOTS)
                    nUnique[i] = g_pItemList[mob->Equip[i].sIndex].nUnique;

                if ((Type != EF_DAMAGE || i != EQUIP_LEFT) && (Type != EF_MAGIC || i != EQUIP_RIGHT))
                {
                    if (i != EQUIP_RIGHT || Type != 2)
                    {
                        value += BASE_GetItemAbility(&mob->Equip[i], Type);
                    }
                    else
                    {
                        int ldam = BASE_GetItemAbility(&mob->Equip[6], EF_DAMAGE2) + BASE_GetItemAbility(&mob->Equip[6], Type);
                        int rdam = BASE_GetItemAbility(&mob->Equip[7], EF_DAMAGE2) + BASE_GetItemAbility(&mob->Equip[7], Type);
                        int lidx = mob->Equip[6].sIndex;
                        int ridx = mob->Equip[7].sIndex;

                        int ltype = 0;
                        if (lidx > 0 && lidx < MAX_ITEMLIST)
                            ltype = g_pItemList[lidx].nPos;

                        int rtype = 0;
                        if (ridx > 0 && ridx < MAX_ITEMLIST)
                            rtype = g_pItemList[ridx].nPos;

                        if (ltype && rtype)
                        {
                            int multi = 0;

                            if (ltype != 47 || rtype != 45)
                            {
                                if (ltype == rtype)
                                    multi = 50;
                                else
                                    multi = 30;
                                if (!mob->Class && mob->LearnedSkill[0] & 0x200)
                                    multi += 15;
                                if (mob->Class == 3 && mob->LearnedSkill[0] & 0x400)
                                    multi += 10;
                                if (ldam <= rdam)
                                    value += multi * ldam / 100 + rdam;
                                else
                                    value += multi * rdam / 100 + ldam;
                            }
                            else
                            {
                                value += ldam;
                            }
                        }
                        else if (ldam <= rdam)
                        {
                            value += rdam;
                        }
                        else
                        {
                            value += ldam;
                        }
                    }
                }
            }
        }

        if (value < 0)
            value = 0;

        return value;
    }

    return 0;
}

bool BASE_CheckNameValid(char* name)
{
    return true;
}

char* BASE_TransCurse(char* sz)
{
    return (char*)E_NOTIMPL;
}

int BASE_InitializeAttribute()
{
    int tsum = 0;

    int sum = 0;

    FILE* fp = NULL;

    char FileName[256] = { 0, };

    strcpy(FileName, "./Env/AttributeMap.dat");

    fopen_s(&fp, FileName, "rb");

    if (!fp)
        fopen_s(&fp, "../../TMSRV/Run/AttributeMap.dat", "rb");

    if (fp)
    {
        fread(&g_pAttribute, 1024, 1024, fp);
        fread(&tsum, 4, 1, fp);
        fclose(fp);

        sum = BASE_GetSum((char*)&g_pAttribute, sizeof(g_pAttribute));

        return (sum == tsum);
    }
    else
    {
        MessageBoxA(0, "There is no file", "Attributemap.dat", 0);
        return FALSE;
    }
}

void BASE_InitializeEffectName()
{
}

int BASE_ReadInitItem()
{
    FILE* fp = NULL;

    char szFileName[256];
    char szPathName[256];

    memset(szPathName, 0, 256);
    memset(szFileName, 0, 256);

    GetModuleFileNameA(0, szPathName, 256);

    int v0 = strlen(szPathName);
    for (int nIndex = v0 - 1; nIndex > 0; --nIndex)
    {
        if (szPathName[nIndex] == 92)
        {
            sprintf(szFileName, "%s", &szPathName[nIndex + 1]);
            break;
        }
    }

    fopen_s(&fp, szFileName, "rb");

    if (!fp)
        fopen_s(&fp, "WYD.EXE", "rb"); //??

    if (fp)
    {
        fseek(fp, MAX_INITITEM, 2);
        fread((void*)&g_pInitItem, MAX_INITITEM, 1, fp);
        fclose(fp);

        for (int i = 0; i < MAX_INITITEM; ++i)
            g_pInitItem[i].sIndex = 0;

        for (int ia = 0; ia < MAX_INITITEM; ++ia)
        {
            if (g_pInitItem[ia].sIndex <= 0)
            {
                g_dwInitItem = ia;
                break;
            }
        }
        
        return TRUE;
    }
    else
    {
        MessageBoxA(NULL, "Can't read inititem", "ERROR", MB_OK);
        return 0;
    }
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

bool BASE_CheckChatValid(char* Chat)
{
    return true;
}

int BASE_ReadItemList()
{
    FILE* fp = NULL;
    char buff[256];

    int size = sizeof(g_pItemList);
    char* temp = (char*)&g_pItemList;
    int tsum = 0;

    fopen_s(&fp, ".\\ItemList.bin", "rb");

    if (!fp)
    {
        MessageBoxA(0, "Can't read ItemList.bin", "ERROR", 0);
        return 0;
    }

    fread(temp, size, 1, fp);
    fread(&tsum, 4, 1, fp);
    fclose(fp);

    BASE_GetSum2((char*)&g_pItemList, size);

    if (tsum != ITEMLIST_CHECKSUM)
        return 0;

    for (int i = 0; i < size; ++i)
        temp[i] ^= 0x5Au;

    auto Handle = _open(".\\ExtraItem.bin", 0x8000, 0);

    if (Handle != -1)
    {
        while (_read(Handle, buff, 142) >= 142)
        {
            int idx = *(WORD*)buff;
            if (buff > 0 && idx < MAX_ITEMLIST)
                memcpy(&g_pItemList[idx], &buff[2], 140);
        }

        _close(Handle);

        for (int j = 0; j < size; ++j)
            temp[j] ^= 0x5Au;

        tsum = BASE_GetSum2((char*)&g_pItemList, size);

        if (tsum != ITEMLIST_CHECKSUM)
            return 0;

        for (int j = 0; j < size; ++j)
            temp[j] ^= 0x5Au;
    }
    return 1;
}

int BASE_GetItemSanc(STRUCT_ITEM* item)
{
    if (item->sIndex < 2330 || item->sIndex >= 2390)
    {
        if (item->sIndex < 3200 || item->sIndex >= 3300)
        {
            if (item->sIndex < 3980 || item->sIndex >= 4000)
            {
                auto sanc = 0;
                if (item->stEffect[0].cEffect != EF_SANC && item->stEffect[1].cEffect != EF_SANC && item->stEffect[2].cEffect != EF_SANC)
                {
                    if (item->stEffect[0].cEffect >= EF_STARTCOL && item->stEffect[0].cEffect <= EF_MAXCOL)
                        sanc = item->stEffect[0].cValue;
                    else if(item->stEffect[1].cEffect >= EF_STARTCOL && item->stEffect[1].cEffect <= EF_MAXCOL)
                        sanc = item->stEffect[1].cValue;
                    else if (item->stEffect[2].cEffect >= EF_STARTCOL && item->stEffect[2].cEffect <= EF_MAXCOL)
                        sanc = item->stEffect[2].cValue;
                }
                else if (item->stEffect[0].cEffect == EF_SANC)
                    sanc = item->stEffect[0].cValue;
                else if (item->stEffect[1].cEffect == EF_SANC)
                    sanc = item->stEffect[1].cValue;
                else if (item->stEffect[2].cEffect == EF_SANC)
                    sanc = item->stEffect[2].cValue;

                if (item->sIndex != 786 && item->sIndex != 1936 && item->sIndex != 1937)
                {
                    auto isanc = sanc;

                    if (sanc < 230)
                        isanc = sanc % 10;
                    else
                        isanc = sanc - 220;
                    if (isanc >= 10 && isanc <= 35)
                        isanc = (isanc - 10) / 4 + 10;

                    return isanc;
                }

                return sanc;
            }
        }
    }

    return 0;
}

int BASE_CheckBit(char* byte, int pos)
{
    return ((1 << pos % 8) & byte[pos / 8]) != 0;
}

void BASE_SetBit(char* byte, int pos)
{
    byte[pos / 8] |= 1 << pos % 8;
}

void BASE_ResetBit(char* byte, int pos)
{
    byte[pos / 8] &= ~(1 << pos % 8);
}

int BASE_GetBonusItemAbilityNosanc(STRUCT_ITEM* item, char Type)
{
    if (item->sIndex < 2330 || item->sIndex >= 2390)
    {
        if (item->sIndex < 3980 || item->sIndex >= 4000)
        {
            int value = 0;
            int idx = item->sIndex;
            if (idx > 0 && idx <= 6500)
            {
                if (idx < 3200 || idx > 3300)
                {
                    for (int i = 0; i < MAX_STITEM_EFFECTS; ++i)
                    {
                        if (item->stEffect[i].cEffect == Type)
                        {
                            int tvalue = item->stEffect[i].cValue;

                            if (Type == EF_ATTSPEED && tvalue == 1)
                                tvalue = 10;

                            value += tvalue;
                        }
                    }

                    return value;
                }
            }
        }
    }

    return 0;
}

void BASE_InitializeHitRate()
{
    memset(&g_pHitRate, 0, sizeof(g_pHitRate));

    int Jump = 512;
    int Start = 0;
    int Quad = 0;
    do
    {
        for (int i = 0; i < 1024; i += Jump)
        {
            if (!g_pHitRate[i])
            {
                if (Quad)
                {
                    if (Quad == 1)
                    {
                        g_pHitRate[i] = 512 - Start;
                    }
                    else if (Quad == 2)
                    {
                        g_pHitRate[i] = Start + 512;
                    }
                    else
                    {
                        g_pHitRate[i] = 1024 - Start;
                    }
                }
                else
                {
                    g_pHitRate[i] = Start;
                }

                if (g_pHitRate[i] > 999)
                    g_pHitRate[i] = 999;

                if (++Quad >= 4)
                    Quad = 0;

                if (!Quad)
                    ++Start;
            }
        }
        Jump /= 2;
    } while (Jump);

    g_pHitRate[0] = 512;
}

int BASE_ReadSkillBin()
{
    FILE* fp = NULL;

    int size = sizeof(g_pSpell);
    int tsum = 0;
    fopen_s(&fp, "SkillData.bin", "rb");

    if (fp)
    {
        fread(g_pSpell, size, 1, fp);
        fread(&tsum, 4, 1, fp);
        fclose(fp);
        BASE_GetSum2((char*)&g_pSpell, size);
        if (tsum == SKILLDATA_CHECKSUM)
        {
            for (int i = 0; i < size; ++i)
                *(char*)&g_pSpell[i] ^= 0x5Au;

            return TRUE;
        }
    }
    else
    {
        MessageBoxA(NULL, "Can't read SkillData.bin", "ERROR", MB_OK);
        return FALSE;
    }
}

int BASE_ReadMessageBin()
{
    int result = FALSE;

    FILE* fp = NULL;
    int size = sizeof(g_pMessageStringTable);

    memset(&g_pMessageStringTable, 0, size);
    int tsum = 0;

    fopen_s(&fp, "UI/strdef.bin", "rb");
    if (fp)
    {
        fread(&g_pMessageStringTable, size, 1, fp);
        fread(&tsum, 4, 1, fp);
        fclose(fp);
    }

    int sum = BASE_GetSum((char*)&g_pMessageStringTable, size);
    if (sum == tsum)
    {
        for (int i = 0; i < size; ++i)
            *(char*)&g_pMessageStringTable[i] ^= 0x5Au;

        result = TRUE;
    }
    else
    {
        result = FALSE;
    }
    return result;
}

int BASE_GetSpeed(STRUCT_SCORE* score)
{
    int Run = score->AttackRun & 0xF;

    if (Run < 1)
        Run = 1;
    if (Run > 7)
        Run = 7;

    return Run;
}

void BASE_GetHitPosition2(int sx, int sy, int* tx, int* ty, char* pHeight, int MH)
{
    int v10 = FALSE;
    int dy = FALSE;

    if ((sx != *tx || sy != *ty) && sx && sy && *tx && *ty)
    {
        if (sx <= *tx)
            v10 = *tx - sx;
        else
            v10 = sx - *tx;
        if (sy <= *ty)
            dy = *ty - sy;
        else
            dy = sy - *ty;

        int This = pHeight[sx + g_HeightWidth * (sy - g_HeightPosY) - g_HeightPosX];

        if (v10 <= dy)
        {
            int dira = 0;

            if (sy >= *ty)
                dira = -1;
            else
                dira = 1;

            int v17 = dy;

            for (int y = sy; y - dira != *ty; y += dira)
            {
                if (y == sy)
                {
                    if (--v17 < 0)
                        return;
                }
                else
                {
                    int v7 = 1000 * (*tx - sx) / (*ty - sy);
                    int xp = (1000 * sx - sy * v7 + y * v7) / 1000;
                    int Lasta = This;

                    if (y - g_HeightPosY < 0 || y - g_HeightPosY >= 256 || xp - g_HeightPosX < 0 || xp - g_HeightPosX >= 256)
                    {
                        *tx = 0;
                        *ty = 0;
                        return;
                    }

                    This = pHeight[xp + g_HeightWidth * (y - g_HeightPosY) - g_HeightPosX];
                    if (y == sy)
                    {
                        --v17;
                    }
                    else
                    {
                        if (This > MH + Lasta || This < Lasta - MH)
                        {
                            *tx = 0;
                            *ty = 0;
                            return;
                        }
                        if (--v17 < 0)
                            return;
                    }
                }
            }
        }
        else
        {
            int dir = 0;

            if (sx >= *tx)
                dir = -1;
            else
                dir = 1;

            int leng = v10;

            for (int x = sx; x - dir != *tx; x += dir)
            {
                if (x == sx)
                {
                    if (--leng < 0)
                        return;
                }
                else
                {
                    int Last = This;
                    int a = 1000 * (*ty - sy) / (*tx - sx);
                    This = pHeight[x + g_HeightWidth * ((1000 * sy - sx * a + x * a) / 1000 - g_HeightPosY) - g_HeightPosX];
                    if (This > MH + Last || This < Last - MH)
                    {
                        *tx = 0;
                        *ty = 0;
                        return;
                    }
                    if (--leng < 0)
                        return;
                }
            }
        }
    }
}

int BASE_CheckQuestBit(char quest, int index)
{
    return ((1 << index) & quest) != 0;
}

unsigned int BASE_GetOptionColor(int nPos, unsigned int dwParam, int nValue)
{
    return 0;
}

int BASE_GetMaxAbility(STRUCT_MOB* mob, char Type)
{
    int value = 0;
    for (int i = 0; i < MAX_EQUIPMENT; ++i)
    {
        if (mob->Equip[i].sIndex)
        {
            int tvalue = BASE_GetItemAbility(&mob->Equip[i], Type);
            if (value < tvalue)
                value = tvalue;
        }
    }
    return value;
}

void BASE_InitializeMathTable()
{
    //there's nothin here...
    return;
}

int BASE_InitializeServerList()
{
    FILE* fpBin = NULL;
    char szList[65];

    fopen_s(&fpBin, "./serverlist.bin", "rb");
    if (fpBin)
    {
        memcpy(szList, "¤¡¤¤¤§¤©¤±¤²¤µ¤·¤¸¤º¤»¤¼¤½¤¾¤¿¤Á¤äŤǤˤ̤ФѤӤ¿¤ĤӤǤ̰¡³ª´٢", sizeof(szList));
        memset(g_pServerList, 0, sizeof(g_pServerList));
        fread(g_pServerList, 110, 64, fpBin);
        fclose(fpBin);
        for (int k = 0; k < 10; ++k)
        {
            for (int j = 0; j < 11; ++j)
            {
                for (int i = 0; i < 64; ++i)
                    g_pServerList[k][j][i] -= szList[63 - i];
            }
        }
    }
    return TRUE;
}

void BASE_GetHitPosition(int sx, int sy, int* tx, int* ty, char* pHeight, int MH)
{
    int dira = 0, dir = 0;

    if ((sx != *tx || sy != *ty) && sx && sy && *tx && *ty)
    {
        int dx = sx <= *tx ? *tx - sx : sx - *tx;
        int dy = sy <= *ty ? *ty - sy : sy - *ty;
        int dis = BASE_GetDistance(sx, sy, *tx, *ty);
        if (dis > 1)
        {
            if (dis <= 30)
            {
                if (dx <= dy)
                {
                    if (*ty != sy)
                    {
                        int aa = 1000 * (*tx - sx) / (*ty - sy);
                        int ba = 1000 * sx - sy * aa;
                        if (sy >= *ty)
                            dira = -1;
                        else
                            dira = 1;
                        int sya = dira + sy;
                        if (dx == dy)
                            *tx;
                        int Thisa = pHeight[(ba + sya * aa) / 1000 + g_HeightWidth * (sya - g_HeightPosY) - g_HeightPosX];
                        if (Thisa == 127)
                        {
                            *tx = 0;
                            *ty = 0;
                        }
                        else
                        {
                            int v14 = dy;
                            for (int y = sya; y != *ty; y += dira)
                            {
                                if (y == sya)
                                {
                                    if (--v14 < 1)
                                        return;
                                }
                                else
                                {
                                    int xp = (ba + y * aa) / 1000;
                                    int Lasta = Thisa;
                                    Thisa = pHeight[xp + g_HeightWidth * (y - g_HeightPosY) - g_HeightPosX];
                                    if (Thisa == 127)
                                    {
                                        *tx = 0;
                                        *ty = 0;
                                        return;
                                    }
                                    if (Thisa > MH + Lasta || Thisa < Lasta - MH)
                                    {
                                        *tx = xp;
                                        *ty = y;
                                        return;
                                    }
                                    if (--v14 < 1)
                                        return;
                                }
                            }
                        }
                    }
                }
                else if (*tx != sx)
                {
                    int a = 1000 * (*ty - sy) / (*tx - sx);
                    int b = 1000 * sy - sx * a;
                    if (sx >= *tx)
                        dir = -1;
                    else
                        dir = 1;
                    int sxa = dir + sx;
                    int This = pHeight[sxa + g_HeightWidth * ((b + sxa * a) / 1000 - g_HeightPosY) - g_HeightPosX];
                    if (This == 127)
                    {
                        *tx = 0;
                        *ty = 0;
                    }
                    else
                    {
                        int leng = dx;
                        for (int x = sxa; x != *tx; x += dir)
                        {
                            if (x == sxa)
                            {
                                if (--leng < 1)
                                    return;
                            }
                            else
                            {
                                int Last = This;
                                This = pHeight[x + g_HeightWidth * ((b + x * a) / 1000 - g_HeightPosY) - g_HeightPosX];
                                if (This == 127)
                                {
                                    *tx = 0;
                                    *ty = 0;
                                    return;
                                }
                                if (This > MH + Last || This < Last - MH)
                                {
                                    *tx = x;
                                    *ty = (b + x * a) / 1000;
                                    return;
                                }
                                if (--leng < 1)
                                    return;
                            }
                        }
                    }
                }
            }
            else
            {
                *tx = 0;
                *ty = 0;
            }
        }
    }
}

int BASE_CanCarry(STRUCT_ITEM* Carry, int pos)
{
    if (pos >= 30)
    {
        if (pos / 15 != 2 || Carry[60].sIndex == 3467)
            return (pos / 15 != 3 || Carry[61].sIndex == 3467);
        else
            return FALSE;
    }

    return TRUE;
}

int BASE_DefineSkinMeshType(int nClass)
{
    int nSkinMeshType = 0;

    switch (nClass)
    {
    case 1:
        nSkinMeshType = 0;
        break;
    case 2:
        nSkinMeshType = 1;
        break;
    case 4:
        nSkinMeshType = 0;
        break;
    case 8:
        nSkinMeshType = 1;
        break;
    case 16:
        nSkinMeshType = 20;
        break;
    case 17:
        nSkinMeshType = 21;
        break;
    case 18:
        nSkinMeshType = 22;
        break;
    case 19:
        nSkinMeshType = 23;
        break;
    case 20:
        nSkinMeshType = 24;
        break;
    case 21:
        nSkinMeshType = 2;
        break;
    case 22:
        nSkinMeshType = 25;
        break;
    case 23:
        nSkinMeshType = 26;
        break;
    case 24:
        nSkinMeshType = 27;
        break;
    case 25:
        nSkinMeshType = 2;
        break;
    case 26:
        nSkinMeshType = 3;
        break;
    case 27:
        nSkinMeshType = 28;
        break;
    case 28:
        nSkinMeshType = 29;
        break;
    case 29:
        nSkinMeshType = 6;
        break;
    case 30:
        nSkinMeshType = 4;
        break;
    case 31:
        nSkinMeshType = 32;
        break;
    case 32:
        nSkinMeshType = 7;
        break;
    case 33:
        nSkinMeshType = 8;
        break;
    case 34:
        nSkinMeshType = 0;
        break;
    case 35:
        nSkinMeshType = 29;
        break;
    case 36:
        nSkinMeshType = 0;
        break;
    case 37:
        nSkinMeshType = 1;
        break;
    case 38:
        nSkinMeshType = 1;
        break;
    case 39:
        nSkinMeshType = 0;
        break;
    case 40:
        nSkinMeshType = 0;
        break;
    case 41:
        nSkinMeshType = 69;
        break;
    case 42:
        nSkinMeshType = 30;
        break;
    case 43:
        nSkinMeshType = 31;
        break;
    case 44:
        nSkinMeshType = 33;
        break;
    case 45:
        nSkinMeshType = 23;
        break;
    case 46:
        nSkinMeshType = 11;
        break;
    case 47:
        nSkinMeshType = 35;
        break;
    case 48:
        nSkinMeshType = 34;
        break;
    case 49:
        nSkinMeshType = 36;
        break;
    case 50:
        nSkinMeshType = 37;
        break;
    case 51:
        nSkinMeshType = 38;
        break;
    case 52:
        nSkinMeshType = 39;
        break;
    case 53:
        nSkinMeshType = 40;
        break;
    case 54:
        nSkinMeshType = 9;
        break;
    case 55:
        nSkinMeshType = 10;
        break;
    case 56:
        nSkinMeshType = 41;
        break;
    case 57:
        nSkinMeshType = 12;
        break;
    case 58:
        nSkinMeshType = 42;
        break;
    case 59:
        nSkinMeshType = 43;
        break;
    case 60:
        nSkinMeshType = 0;
        break;
    case 61:
        nSkinMeshType = 1;
        break;
    case 62:
        nSkinMeshType = 5;
        break;
    case 63:
        nSkinMeshType = 0;
        break;
    case 64:
        nSkinMeshType = 44;
        break;
    case 66:
        nSkinMeshType = 45;
        break;
    case 67:
        nSkinMeshType = 46;
        break;
    case 68:
        nSkinMeshType = 47;
        break;
    case 69:
        nSkinMeshType = 48;
        break;
    case 70:
        nSkinMeshType = 53;
        break;
    case 71:
        nSkinMeshType = 54;
        break;
    case 72:
        nSkinMeshType = 55;
        break;
    case 73:
        nSkinMeshType = 56;
        break;
    case 74:
        nSkinMeshType = 57;
        break;
    default:
        nSkinMeshType = 0;
        LOG_WRITELOG("Invalide Item Class\n");
        break;
    }
    return nSkinMeshType;
}

int BASE_GetWeekNumber()
{
    return FALSE;
}

int BASE_GetDistance(int x1, int y1, int x2, int y2)
{
    int result = FALSE;
    int dy;
    int dist = 0;

    if (x1 <= x2)
        dist = x2 - x1;
    else
        dist = x1 - x2;

    if (y1 <= y2)
        dy = y2 - y1;
    else
        dy = y1 - y2;
    if (dist > 6 || dy > 6)
    {
        if (dist <= dy)
            result = dy + 1;
        else
            result = dist + 1;
    }
    else
    {
        return g_pDistanceTable[dy][dist];
    }

    return result;
}

int BASE_GetCheckFace(int face)
{
    int faceKind = 0;
    if (face % 10 > 5)
        faceKind = 1;
    return faceKind;
}

int BASE_GetStaticItemAbility(STRUCT_ITEM* item, char Type)
{
    return 0;
}

int BASE_GetBonusItemAbility(STRUCT_ITEM* item, char Type)
{
    if (item->sIndex < 2330 || item->sIndex >= 2390)
    {
        if (item->sIndex < 3980 || item->sIndex >= 4000)
        {
            int value = 0;
            int idx = item->sIndex;

            if (idx > 0 && idx <= MAX_ITEMLIST) //MAX_ITEMLIST
            {
                if (idx < 3200 || idx > 3300)
                {
                    int nPos = g_pItemList[idx].nPos;
                    for (int i = 0; i < MAX_STITEM_EFFECTS; ++i)
                    {
                        if (item->stEffect[i].cEffect == Type)
                        {
                            int tvalue = item->stEffect[i].cValue;
                            if (Type == EF_ATTSPEED && tvalue == 1)
                                tvalue = 10;

                            value += tvalue;
                        }
                    }

                    int sanc = BASE_GetItemSanc(item);
                    if (sanc >= 9 && nPos & 0xF00)
                        ++sanc;
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
                        && Type != EF_PREVBONUS)
                    {
                        if (sanc > 10)
                        {
                            if (sanc >= 11)
                            {
                                int UpSanc = sanc - 10;
                                if (sanc == 11)
                                {
                                    UpSanc = 220;
                                }
                                else
                                {
                                    switch (UpSanc)
                                    {
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
                                }
                                value = UpSanc * 10 * value / 100 / 10;
                            }
                        }
                        else
                        {
                            value = value * (sanc + 10) / 10;
                        }
                    }

                    return value;
                }
            }
        }
    }

    return 0;
}

int BASE_GetDoubleCritical(STRUCT_MOB* mob, unsigned short* sProgress, unsigned short* cProgress, char* bDoubleCritical)
{
    *bDoubleCritical = 0;

    if (!cProgress)
        return 0;

    if (*cProgress >= 1024)
        *cProgress %= 1024;

    if (sProgress && *sProgress >= 1024)
        *sProgress %= 1024;

    int hitValue = 100 * ((mob->CurrentScore.AttackRun >> 4) - 5);
    int critValue = 4 * mob->Critical;

    if (sProgress && cProgress && *cProgress != *sProgress)
    {
        if (*sProgress > * cProgress)
            *cProgress = *sProgress;
        if (*sProgress < *cProgress)
        {
            if (*sProgress + 5 < *cProgress)
            {
                *cProgress = *sProgress;
                return 0;
            }
            *sProgress = *cProgress;
        }
    }

    auto tProgress = *cProgress;

    int value = g_pHitRate[tProgress];
    
    for (int i = 0; i < 2; ++i)
    {
        int bit = 0;
        if (!i && value < hitValue)
            bit = 1;
        if (i == 1 && 1000 - value < critValue)
            bit = 1;

        *bDoubleCritical |= bit << i;
    }

    if (sProgress)
        ++* sProgress;

    ++* cProgress;

    return 1;
}

void BASE_InitModuleDir()
{
    char String[256] = { 0, };

    GetModuleFileNameA(0, String, 256);
    int len = strlen(String);
    for (int i = len - 1; i > 0; --i)
    {
        if (String[i] == 92)
        {
            if (i >= 256)
            {
                //error
            }

            String[i] = 0;
            break;
        }
    }

    SetCurrentDirectoryA(String);
}

void BASE_ClearItem(STRUCT_ITEM* item)
{
    memset(&item, 0, sizeof(STRUCT_ITEM));
}

void BASE_ClearMob(STRUCT_MOB* mob)
{
    memset(mob->MobName, 0, 16);
    mob->HomeTownX = 2112;
    mob->HomeTownY = 2112;
    mob->ShortSkill[0] = -1;
    mob->ShortSkill[1] = -1;
    mob->ShortSkill[2] = -1;
    mob->ShortSkill[3] = -1;
}

int BASE_GetMobCheckSum(STRUCT_MOB* mob)
{
    int sum = 0;

    memset(&mob->BaseScore, 0, sizeof(STRUCT_SCORE));

    for (int i = 0; i < MAX_EQUIPMENT; ++i)
        sum += i * mob->Equip[i].sIndex;

    for (int ia = 0; ia < MAX_CARRY; ++ia)
        sum += ia * mob->Carry[ia].sIndex;
    
    for (int ib = 0; ib < MAX_CARRY; ++ib)
        sum += ib * mob->Carry[ib].sIndex;
    
    return sum;
}

void BASE_InitializeMobname(char* file)
{
}

void BASE_InitializeMessage(char* file)
{
    FILE* fp = NULL;
    char str[512] = { 0, };
    char part1[256] = { 0, };

    memset(&g_pMessageStringTable, 0, sizeof(g_pMessageStringTable));
    fopen_s(&fp, file, "rt");
    if (fp)
    {
        memset(str, 0, 512);
        memset(part1, 0, 256);

        char* cont = { 0, };

        while (1)
        {
            memset(str, 0, 512);
            memset(part1, 0, 256);

            cont = 0;
            int Index = -1;

            if (!fgets(str, 512, fp))
                break;

            sscanf(str, "%d %s", &Index, part1);

            if (Index > 0 && Index <= MAX_STRDEF) //MAX_MESSAGE
            {
                int TabPos = 0;

                for (int i = 0; i < 256; ++i)
                {
                    if (str[i] == 9)
                    {
                        TabPos = i;
                        break;
                    }
                }

                if (TabPos)
                {
                    cont = &str[TabPos + 1];
                    for (int i = 0; i < 128; ++i)
                    {
                        if (cont[i] == 9 || cont[i] == 10 || !cont[i])
                        {
                            cont[i] = 0;
                            break;
                        }
                    }

                    int len = strlen(cont);

                    if (len <= 0 || len >= 126)
                    {
                        char dst[128] = { 0, };
                        sprintf(dst, "Empty or Long String-%s", str);
                        //Log(&dst, "-system", 0);
                        cont[127] = 0;
                        cont[126] = 0;
                    }

                    strcpy(g_pMessageStringTable[Index], cont);
                }
                else
                {
                    char stemp[128] = { 0, };

                    sprintf(stemp, "Can't parse String-%s", str);

                    //Log(stemp, "-system", 0);
                }
            }
        }

        fclose(fp);
    }
}

void BASE_WriteMessageBin()
{
    int size = sizeof(g_pMessageStringTable);
    char temp[MAX_STRDEF][MAX_MSGSTRING] = { 0, };

    memcpy(temp, g_pMessageStringTable, sizeof(g_pMessageStringTable));

    for (int i = 0; i < size; ++i)
        *(char*)temp[i] ^= 0x5A;

    FILE* fp = NULL;

    fopen_s(&fp, "UI/strdef.bin", "wb");

    if (fp)
    {
        fwrite(&g_pMessageStringTable, 1, sizeof(g_pMessageStringTable), fp);
        int sum = BASE_GetSum((char*)&g_pMessageStringTable, size);
        fwrite(&sum, 4, 1, fp);
        fclose(fp);
    }
}

void BASE_InitializeItemList()
{
    char extraitem[128];

    //memset(g_pItemList, 0, sizeof(g_pItemList));
    /*
    if (BASE_ReadItemListFile((char*)"itemlist.csv", 0))
    {
        strcpy(extraitem, "extraitem.csv");
        BASE_ReadItemListFile(extraitem, 1);
        BASE_ReadItemName((char*)"itemname.csv");
        BASE_InitialItemRePrice();
    }
    else
    {
        MessageBoxA(0, "There is no file", "itemlist.csv", 0);
    }*/
}

void BASE_InitializeInitItem()
{
    FILE* fp;
    char str[1024];
    char _Buffer[1024];

    fp = fopen("./InitItem.csv", "rb");
    if (!fp)
        fp = fopen("../../TMSRV/Run/InitItem.csv", "rb");
    if (fp)
    {
        if (fgets(str, 1023, fp))
        {
            g_dwInitItem = 0;
            while (fgets(_Buffer, 1024, fp))
            {
                for (int i = 0; i < 1024; ++i)
                {
                    if (_Buffer[i] == 44)
                        _Buffer[i] = 32;
                    if (!_Buffer[i])
                        break;
                }

                int Index = -1;
                int PosX = 0;
                int PosY = 0;
                int Rotate = 0;

                sscanf(_Buffer, "%d %d %d %d", &Index, &PosX, &PosY, &Rotate);

                if (Index != -1)
                {
                    g_pInitItem[g_dwInitItem].PosX = PosX;
                    g_pInitItem[g_dwInitItem].PosX = PosY;
                    g_pInitItem[g_dwInitItem].sIndex = Index;
                    g_pInitItem[g_dwInitItem].Rotate = Rotate;

                    g_dwInitItem++;
                }
            }

            fclose(fp);
        }
    }
    else
    {
        MessageBoxA(0, "There is no file", "InitItem.csv", 0);
    }
}

int BASE_InitializeLotto()
{
    return 0;
}

void BASE_SpaceToUnderBar(char* szStr)
{
    for (int i = 0; ; ++i)
    {
        int len = strlen(szStr);

        if (i >= len)
            break;

        if (szStr[i] == 32)
            szStr[i] = 95;
    }
}

char BASE_CheckEngNum(char* szStr)
{
    int len = strlen(szStr);
    szStr[15] = 0;
    szStr[14] = 0;

    for (int j = 0; j < len; ++j)
    {
        auto x = szStr[j];

        auto v4 = x >= 97 && x <= 122 || x >= 65 && x <= 90;

        if (!v4)
        {
            auto v3 = x < 48 || x > 57 ? 0 : 1;

            if (!v3 && x != 45 && x != 91 && x != 93 && x != 123 && x != 125 && x != 40 && x != 41)
                return FALSE;
        }
    }

    return TRUE;
}

bool BASE_CheckHangul(unsigned short word)
{
    return word >= 176
        && word <= 201
        && word >= 161
        && word <= 255;
}

void BASE_InitializeSkill()
{

    FILE* fp;

    STRUCT_SPELL temp;

    int Act2[6];
    int Act1[6];

    char str[1024];

    char skilldata2[256];
    char skilldata1[256];

    fp = fopen("./SkillData.csv", "rb");
    if (!fp)
        fp = fopen("../../TMSRV/Run/SkillData.csv", "rb");

    if (fp)
    {
        memset(g_pSpell, 0, sizeof(g_pSpell));

        if (fgets(str, 1024, fp))
        {
            while (fgets(str, 1024, fp))
            {
                for (int i = 0; i < 1024; ++i)
                {
                    if (str[i] == 44)
                        str[i] = 32;
                    if (!str[i])
                        break;
                }
                memset((char*)&temp, 0, sizeof(STRUCT_SPELL));

                int Index = -1;

                sscanf(
                    str,
                    "%d %d %d %d %d %d %d %d %d %d %d %d %d %s %s %d %d %d %d %d %d %d %d",
                    &Index,
                    &temp,
                    &temp.TargetType,
                    &temp.ManaSpent,
                    &temp.Delay,
                    &temp.Range,
                    &temp.InstanceType,
                    &temp.InstanceValue,
                    &temp.TickType,
                    &temp.TickValue,
                    &temp.AffectType,
                    &temp.AffectValue,
                    &temp.AffectTime,
                    skilldata1,
                    skilldata2,
                    &temp.InstanceAttribute,
                    &temp.TickAttribute,
                    &temp.Aggressive,
                    &temp.MaxTarget,
                    &temp.bParty,
                    &temp.AffectResist,
                    &temp.Passive,
                    &temp.ForceDamage);

                if (Index >= 0 && Index < 248)
                {
                    temp.AffectTime /= 4;
                    memset((char*)Act1, 0, 0x18u);
                    memset((char*)Act2, 0, 0x18u);
                    memset(temp.Act1, 0, 8u);
                    memset(temp.Act2, 0, 8u);
                    sscanf(skilldata1, "%d.%d.%d.%d.%d.%d", Act1, &Act1[1], &Act1[2], &Act1[3], &Act1[4], &Act1[5]);
                    sscanf(skilldata2, "%d.%d.%d.%d.%d.%d", Act2, &Act2[1], &Act2[2], &Act2[3], &Act2[4], &Act2[5]);
                    for (int i = 0; i < 6; ++i)
                    {
                        temp.Act1[i] = Act1[i];
                        temp.Act2[i] = Act2[i];
                    }

                    memcpy(&g_pSpell[Index], &temp, sizeof(STRUCT_SPELL));
                }
            }
            fclose(fp);
        }
    }
    else
    {
        MessageBoxA(NULL, "There is no file", "SkillData.csv", MB_OK);
    }
}

int BASE_CheckPacket(MSG_STANDARD* m)
{
    return TRUE;
}

void BASE_WriteSkillBin()
{
    FILE* fpCSum;
    FILE* fp;

    int size = sizeof(g_pSpell);
    char* temp = (char*)&g_pSpell;

    for (int i = 0; i < size; ++i)
        temp[i] ^= 0x5A;

    fopen_s(&fp, "SkillData.bin", "wb");

    if (fp)
    {
        fwrite(g_pSpell, sizeof(STRUCT_SPELL), 248, fp); //MAX_SPELL
        int sum = BASE_GetSum2((char*)g_pSpell, size);
        int nRand = rand();
        fwrite(&nRand, 4, 1, fp);
        fclose(fp);

        fopen_s(&fpCSum, "..\\SkillCSum.h", "wt");
        if (fpCSum)
        {
            fprintf(fpCSum, "#define SKILL_CHECKSUM %d", sum);
            fclose(fp);
        }
    }
}

void BASE_WriteInitItem()
{
    FILE* fp = NULL;

    for (int i = 0; i < MAX_INITITEM; ++i)
    {
        g_pInitItem[i].PosX = 0;
        g_pInitItem[i].PosY = 0;
        g_pInitItem[i].sIndex = 0;
        g_pInitItem[i].Rotate = 0;
    }

    fp = fopen("InitItem.bin", "wb");
    if (fp)
    {
        fwrite(g_pInitItem, sizeof(g_pInitItem), 1, fp);
        fclose(fp);

    }
    else
    {
        MessageBoxA(NULL, "Can't write inititem.bin", "ERROR", MB_OK);
    }
}

int BASE_ReadGameRoomIP()
{
    return 0;
}

int BASE_ReadBlockIP()
{
    return 0;
}

int BASE_CanTrade(STRUCT_ITEM* Dest, STRUCT_ITEM* Carry, char* MyTrade, STRUCT_ITEM* OpponentTrade)
{
    STRUCT_ITEM OpponentTemp[15] = { 0, };

    memcpy(OpponentTemp, OpponentTrade, sizeof(OpponentTemp));
    memcpy(Dest, Carry, sizeof(STRUCT_ITEM)); //default was 0x200u wtf

    for (int i = 0; i < MAX_ITEMTRADE; ++i)
    {
        int pos = MyTrade[i];

        if (pos != -1)
            BASE_ClearItem(&Dest[pos]);
    }

    BASE_SortTradeItem(OpponentTemp, 33);

    for (int ia = 0; ia < MAX_ITEMTRADE; ++ia)
    {
        if (OpponentTemp[ia].sIndex)
        {
            int j = 0;

            for (j = 0; j < MAX_CARRY - 4; ++j) //why here is ++j and not j++?
            {
                if (!Dest[j].sIndex && BASE_CanCarry(Dest, j))
                {
                    //idk why ji did this...
                    Dest[j].sIndex = OpponentTemp[ia].sIndex;
                    Dest[j].stEffect[1].cEffect = OpponentTemp[ia].stEffect[1].cEffect;
                    break;
                }
            }

            if (j == MAX_CARRY - 4)
                return FALSE;
        }
    }
    return TRUE;
}

int BASE_CanCargo(STRUCT_ITEM* item, STRUCT_ITEM* cargo, int DestX, int DestY)
{
    char CargoGrid[14][9] = { 0, };
    char SourGrid[4][2] = { 0, };
    char TempGrid[4][2] = { 0, };

    auto grid = BASE_GetItemAbility(item, 33);

    memcpy(&SourGrid, &g_pItemGrid[grid], sizeof(STRUCT_ITEM));
    memset((char*)CargoGrid, 0, sizeof(CargoGrid));

    for (int i = 0; i < 128; ++i)
    {
        if (cargo[i].sIndex)
        {
            int itemGrid = BASE_GetItemAbility(&cargo[i], EF_GRID);

            memcpy(&TempGrid, &g_pItemGrid[itemGrid], sizeof(STRUCT_ITEM));
            int tx = i % 9;
            int ty = i / 9;

            for (int yy = 0; yy < 4; ++yy)
            {
                for (int xx = 0; xx < 2; ++xx)
                {
                    if (TempGrid[yy][xx] == 1 && ty + yy >= 0 && tx + xx >= 0 && ty + yy < 14 && tx + xx < 9)
                    {
                        //wtf
                        CargoGrid[ty][9 * yy + tx + xx] = 1;
                    }
                }
            }
        }
    }

    for (int j = 0; j < 4; ++j)
    {
        for (int k = 0; k < 2; ++k)
        {
            if (SourGrid[j][k] == 1)
            {
                if (DestY + j < 0 || DestX + k < 0 || DestY + j >= 14 || DestX + k >= 9)
                    return 0;
                if (CargoGrid[DestY][9 * j + DestX + k] == 1)
                    return 0;
            }
        }
    }
    return TRUE;
}

void BASE_GetDestByAction(unsigned short* x, unsigned short* y, MSG_Action* mv)
{
    *x = mv->PosX;
    *y = mv->PosY;
    for (int i = 0; i < MAX_ROUTE && mv->Route[i]; ++i)
    {
        if (mv->Route[i] == 54)
            ++* x;
        if (mv->Route[i] == 52)
            --* x;
        if (mv->Route[i] == 56)
            --* y;
        if (mv->Route[i] == 50)
            ++* y;
        if (mv->Route[i] == 57)
        {
            ++* x;
            --* y;
        }
        if (mv->Route[i] == 51)
        {
            ++* x;
            ++* y;
        }
        if (mv->Route[i] == 55)
        {
            --* x;
            --* y;
        }
        if (mv->Route[i] == 49)
        {
            --* x;
            ++* y;
        }
    }
}

int BASE_GetHitRate(STRUCT_SCORE* att, STRUCT_SCORE* def)
{
    int rate = 0;

    if (def->Dex && def->Level)
    {
        if (att->Dex >= 0 && def->Dex >= 0 && att->Level >= 0 && def->Level >= 0)
        {
            rate = 100 * (def->Level + att->Level) / def->Level * (60 * att->Dex / (def->Dex / 2 + att->Dex)) / 100;
            if (rate >= 95)
                rate = 95;
            if (rate < 40)
                rate = 40;
        }
        else
        {
            rate = 0;
        }
    }
    else
    {
        rate = 95;
    }
    return rate;
}

int BASE_GetDamageRate(STRUCT_SCORE* att, int Skill)
{
    int rate = 0;

    rate = att->Special[Skill];
    if (rate >= 200)
        rate = 200;
    if (rate < 0)
        rate = 0;

    return rate;
}

void BASE_GetCurrentScore(STRUCT_MOB* MOB, STRUCT_AFFECT* Affect, STRUCT_EXT1* Ext1, STRUCT_EXT2* Ext2, int OriginalFace, int TargetX, int TargetY, int* AnotherSkill, int soultype, int* BuffState)
{
}

int BASE_UpdateItem(int maskidx, int CurrentState, int NextState, int xx, int yy, char* pHeight, int rotate, int* height)
{
    *height = 0;
    auto delta = 0;

    if (maskidx < 10 && maskidx >= 0)
    {
        if (CurrentState == 1 && (NextState == 3 || NextState == 2))
            delta = 1;
        if (NextState == 1 && (CurrentState == 3 || CurrentState == 2))
            delta = -1;
        if (delta)
        {
            for (auto y = 0; y <= 5; ++y)
            {
                for (auto x = 0; x <= 5; ++x)
                {
                    auto val = g_pGroundMask[maskidx][rotate][y][x];

                    if (val)
                    {
                        auto vala = delta * val;
                        auto xp = xx + x - 2;
                        auto yp = yy + y - 2;
                        if (xp - g_HeightPosX < 1
                            || yp - g_HeightPosY < 1
                            || xp - g_HeightPosX > g_HeightWidth - 2
                            || yp - g_HeightPosY > g_HeightHeight - 2)
                        {
                            break;
                        }

                        auto Last = vala + pHeight[xp + g_HeightWidth * (yp - g_HeightPosY) - g_HeightPosX];

                        if (Last > 127)
                            Last = 127;
                        if (Last < -128)
                            Last = -128;

                        if (g_pGroundMask[maskidx][rotate][y][x])
                            *height = Last;

                        pHeight[xp + g_HeightWidth * (yp - g_HeightPosY) - g_HeightPosX] = Last;
                    }
                }
            }
            return TRUE;
        }
    }

    return FALSE;
}

int BASE_GetDamage(int dam, int ac, int combat)
{
    int combata = combat / 2;
    if (combata > 7)
        combata = 7;

    int tdam = (rand() % (12 - combata) + combata + 99) * (dam - ac / 2) / 100;
    if (tdam >= -50)
    {
        if (tdam < -50 || tdam >= 0)
        {
            if (tdam >= 0 && tdam <= 50)
                tdam = 5 * tdam / 4 + 7;
        }
        else
        {
            tdam = (tdam + 50) / 7;
        }
    }
    else
    {
        tdam = 0;
    }
    if (tdam <= 0)
        tdam = 1;
    return tdam;
}

int BASE_GetGuild(int x, int y)
{
    return 5; //default value is 5
}

int BASE_GetGuild(STRUCT_ITEM* item)
{
    int hword = 0;
    int lword = 0;

    if (item->stEffect[0].cEffect == EF_HWORDGUILD || item->stEffect[1].cEffect == EF_HWORDGUILD || item->stEffect[2].cEffect == EF_HWORDGUILD)
    {
        if (item->stEffect[0].cEffect == EF_HWORDGUILD)
            hword = item->stEffect[0].cValue;
        else if (item->stEffect[1].cEffect == EF_HWORDGUILD)
            hword = item->stEffect[1].cValue;
        else if (item->stEffect[2].cEffect == EF_HWORDGUILD)
            hword = item->stEffect[2].cValue;
    }

    if (item->stEffect[0].cEffect == EF_LWORDGUILD || item->stEffect[1].cEffect == EF_LWORDGUILD || item->stEffect[2].cEffect == EF_LWORDGUILD)
    {
        if (item->stEffect[0].cEffect == EF_LWORDGUILD)
            lword = item->stEffect[0].cValue;
        else if (item->stEffect[1].cEffect == EF_LWORDGUILD)
            lword = item->stEffect[1].cValue;
        else if (item->stEffect[2].cEffect == EF_LWORDGUILD)
            lword = item->stEffect[2].cValue;
    }

    return lword + (hword << 8);
}

int BASE_GetArena(int x, int y)
{
    for (int i = 0; i < 5; ++i)
    {
        if (x >= g_pGuildZone[i].ax1 && x <= g_pGuildZone[i].ax2 && y >= g_pGuildZone[i].ay1 && y <= g_pGuildZone[i].ay2)
            return i;
    }

    return 5;
}

void BASE_GetClientGuildName(int ServerGroup, unsigned short usGuild, char* szGuildName, int Sub)
{

}

int BASE_GetAccuracyRate(STRUCT_SCORE* att)
{
    int ret = att->Dex / 2 + 50;
    if (ret > 100)
        ret = 100;
    return ret;
}

void BASE_GetFirstKey(char* source, char* dest)
{
    if ((*source < 65 || *source > 90) && (*source < 97 || *source > 122))
    {
        if (*source >= 0)
        {
            strcpy(dest, "etc");
        }
        else
        {
            auto Point = 94 * (*source - 176) + source[1] - 161;

            if (Point >= 0 && Point < 2350)
            {
                /* KOREAN LETTERS
                for (int a = 0; a < 18 && Point >= (signed int)(&KorIndex)[a]; ++a)
                    if (a < 0 || a > 17)
                    {
                        strcpy(dest, "etc");
                    }
                    else
                    {
                        *dest = (char)(&KorFirst)[2 * a];
                        dest[1] = byte_85D011[2 * a];
                        dest[2] = 0;
                    }

                */
            }
            else
            {
                strcpy(dest, "etc");
            }
        }
    }
    else
    {
        *dest = *source;
        dest[1] = 0;
    }
}

void BASE_GetKorFirst(int temp, int* a)
{
    *a = ((temp >> 10) & 0x1F) - 1;
}

int BASE_GetItemSancEffect(STRUCT_ITEM* item)
{
    if (item->sIndex < 2330 || item->sIndex >= 2390)
    {
        if (item->sIndex < 3200 || item->sIndex >= 3300)
        {
            if (item->sIndex < 3980 || item->sIndex >= 4000)
            {
                auto sanc = 0;
                if (item->stEffect[0].cEffect != EF_SANC && item->stEffect[1].cEffect != EF_SANC && item->stEffect[2].cEffect != EF_SANC)
                {
                    if (item->stEffect[0].cEffect >= EF_STARTCOL && item->stEffect[0].cEffect <= EF_MAXCOL)
                        sanc = item->stEffect[0].cValue;
                    else if(item->stEffect[1].cEffect >= EF_STARTCOL && item->stEffect[1].cEffect <= EF_MAXCOL)
                        sanc = item->stEffect[1].cValue;
                    else if (item->stEffect[2].cEffect >= EF_STARTCOL && item->stEffect[2].cEffect <= EF_MAXCOL)
                        sanc = item->stEffect[2].cValue;
                }
                else if (item->stEffect[0].cEffect == EF_SANC)
                    sanc = item->stEffect[0].cValue;
                else if (item->stEffect[1].cEffect == EF_SANC)
                    sanc = item->stEffect[1].cValue;
                else if (item->stEffect[2].cEffect == EF_SANC)
                    sanc = item->stEffect[2].cValue;

                auto isanc = 0;

                if (sanc < 230)
                    isanc = sanc % 10;
                else
                    isanc = sanc - 220;

                return isanc;
            }
        }
    }

    return 0;
}

void BASE_SetColorArmor(STRUCT_ITEM* item, int color)
{
    if (color < EF_MAXCOL && color > EF_STARTCOL || color == EF_SANC)
    {
        if (item->stEffect[0].cEffect != EF_SANC && item->stEffect[1].cEffect != EF_SANC && item->stEffect[2].cEffect != EF_SANC)
        {
            if (item->stEffect[0].cEffect >= EF_STARTCOL && item->stEffect[0].cEffect <= EF_MAXCOL)
                item->stEffect[0].cEffect = color;
            else if(item->stEffect[1].cEffect >= EF_STARTCOL && item->stEffect[1].cEffect <= EF_MAXCOL)
                item->stEffect[1].cEffect = color;
            else if (item->stEffect[2].cEffect >= EF_STARTCOL && item->stEffect[2].cEffect <= EF_MAXCOL)
                item->stEffect[2].cEffect = color;
        }
        else if (item->stEffect[0].cEffect == EF_SANC)
            item->stEffect[0].cEffect = color;
        else if (item->stEffect[1].cEffect == EF_SANC)
            item->stEffect[1].cEffect = color;
        else if (item->stEffect[2].cEffect == EF_SANC)
            item->stEffect[2].cEffect = color;
    }
}

void BASE_SetQuestBit(char* quest, int index)
{
    *quest |= 1 << index;
}

void BASE_CleanQuestBit(char* quest, int index)
{
    *quest &= ~(1 << index);
}

int BASE_GetSuccessRate(STRUCT_ITEM* item, int OriLacto)
{
    int rate = 0;

    if (item->sIndex < 2330 || item->sIndex >= 2390)
    {
        if (item->sIndex < 3980 || item->sIndex >= 4000)
        {
            if (OriLacto && OriLacto != 1)
                return 0;
            else
            {
                int sanc = BASE_GetItemSanc(item) % 12;
                int succ = BASE_GetItemSancSuccess(item);
                int level = BASE_GetItemAbility(item, EF_REFLEVEL);

                if (level)
                {
                    if (OriLacto)
                        rate = g_pSancRate[level - 1][sanc]; //Check this
                    else
                        rate = g_pSancRate[level - 1][sanc]; //Check this

                    return rate + succ; //Check this
                }
                else if (item->sIndex < 2300 || item->sIndex >= 2330)
                    return 0;
            }
        }
    }

    return 0;
}

int BASE_GetGrowthRate(STRUCT_ITEM* item)
{
    int result = 0;

    if (item->sIndex >= 2360 || item->sIndex < 2390)
        result = g_pSancRate[2][item->stEffect[1].cEffect / 10];
    else
        result = 0;
    return result;
}

int BASE_SetItemSanc(STRUCT_ITEM* dest, int sanc, int success)
{
    if (sanc < 0)
        sanc = 0;
    if (sanc > 33)
        return 0;
    if (success < 0)
        success = 0;
    if (success > 20)
        success = 20;

    auto mod = 0;
    auto sc = 0;
    if (sanc > 9)
    {
        mod = sanc - 9;
        sanc = 9;
    }
    if (mod > 0)
        sc = mod - 27;
    else
        sc = sanc + 10 * success;

    if (dest->stEffect[0].cEffect == EF_SANC)
        dest->stEffect[0].cValue = sc;
    else if (dest->stEffect[1].cEffect == EF_SANC)
        dest->stEffect[1].cValue = sc;
    else if (dest->stEffect[2].cEffect == EF_SANC)
        dest->stEffect[2].cValue = sc;
    else
    {
        if (dest->stEffect[0].cEffect >= EF_STARTCOL && dest->stEffect[0].cEffect <= EF_MAXCOL)
            dest->stEffect[0].cValue = sc;
        else if(dest->stEffect[1].cEffect >= EF_STARTCOL && dest->stEffect[1].cEffect <= EF_MAXCOL)
            dest->stEffect[1].cValue = sc;
        else if (dest->stEffect[2].cEffect >= EF_STARTCOL && dest->stEffect[2].cEffect <= EF_MAXCOL)
            dest->stEffect[2].cValue = sc;
        else
        {
            if (dest->stEffect[0].cEffect)
            {
                if (dest->stEffect[1].cEffect)
                {
                    if (dest->stEffect[2].cEffect)
                        return FALSE;

                    dest->stEffect[2].cEffect = EF_SANC;
                    dest->stEffect[2].cValue = sc;
                }
                else
                {
                    dest->stEffect[1].cEffect = EF_SANC;
                    dest->stEffect[1].cValue = sc;
                }
            }
            else
            {
                dest->stEffect[0].cEffect = EF_SANC;
                dest->stEffect[0].cValue = sc;
            }
        }
    }

    return TRUE;
}

int BASE_SumItemAmount(STRUCT_ITEM* sour, STRUCT_ITEM* dest)
{
    //Need to implement
    if (sour->sIndex == dest->sIndex)
    {
        return TRUE; //TRUE means that the item can get amounted
    }
}

void BASE_GetLanguage(char* str, int idx)
{
    if (idx >= 0 && idx < 2000)
        sprintf(str, g_pMessageStringTable[idx]);
    else
        strcpy(str, "[UNHANDLED]");
}

void BASE_GetLanguage(char* str, int idx, char* parm1)
{
    if (idx >= 0 && idx < 2000)
        sprintf(str, g_pMessageStringTable[idx], parm1);
    else
        strcpy(str, "[UNHANDLED]");
}

void BASE_GetLanguage(char* str, int idx, char* parm1, char* parm2)
{
    if (idx >= 0 && idx < 2000)
        sprintf(str, g_pMessageStringTable[idx], parm1, parm2);
    else
        strcpy(str, "[UNHANDLED]");
}

void BASE_GetLanguage(char* str, int idx, int parm1)
{
    if (idx >= 0 && idx < 2000)
        sprintf(str, g_pMessageStringTable[idx], parm1);
    else
        strcpy(str, "[UNHANDLED]");
}

void BASE_GetLanguage(char* str, int idx, int parm1, int parm2)
{
    if (idx >= 0 && idx < 2000)
        sprintf(str, g_pMessageStringTable[idx], parm1, parm2);
    else
        strcpy(str, "[UNHANDLED]");
}

void BASE_GetLanguage(char* str, int idx, char* parm1, int parm2)
{
    if (idx >= 0 && idx < 2000)
        sprintf(str, g_pMessageStringTable[idx], parm1, parm2);
    else
        strcpy(str, "[UNHANDLED]");
}

void BASE_GetLanguage(char* str, int idx, int parm1, char* parm2)
{
    if (idx >= 0 && idx < 2000)
        sprintf(str, g_pMessageStringTable[idx], parm1, parm2);
    else
        strcpy(str, "[UNHANDLED]");
}

void BASE_GetItemCode(STRUCT_ITEM* item, char* str)
{
    int iidx = item->sIndex;
    sprintf(
        str,
        " %4.4x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x",
        iidx,
        item->stEffect[0].cEffect,
        item->stEffect[0].cValue,
        item->stEffect[1].cEffect,
        item->stEffect[1].cValue,
        item->stEffect[2].cEffect,
        item->stEffect[2].cValue);
}

int BASE_GetEnglish(char* name)
{
    return FALSE;
}

int BASE_GetBonusSkillPoint(STRUCT_MOB* mob, int face)
{
    int result = FALSE;

    auto cls = mob->Class;
    auto spellperlevel = 0;
    auto mod = 0;

    if (BASE_GetCheckFace(face) == 1)
    {
        if (mob->LearnedSkill[0] & 0x40000000)
        {
            spellperlevel = 1600;
            if (mob->CurrentScore.Level > 199)
                spellperlevel = 3 * (mob->CurrentScore.Level - 199) + 1600;
        }
        else
        {
            auto spellperlevela = 4 * mob->CurrentScore.Level;
            auto bonus = BASE_GetItemAbility(mob->Equip, 86);
            if (bonus > 56)
                bonus = 56;

            auto spellperlevel = spellperlevela + 3 * bonus;

            if (mob->CurrentScore.Level >= 355)
                spellperlevel -= 2 * mob->CurrentScore.Level - 708;
        }
    }
    else
    {
        spellperlevel = 3 * mob->CurrentScore.Level;
        mod = mob->CurrentScore.Level - 199;
        if (mob->CurrentScore.Level > 354)
            mod -= mob->CurrentScore.Level - 354;
        if (mod > 0)
            spellperlevel += mod;
    }
    if (mob->Quest & 1)
        spellperlevel += 9;

    if (cls >= CLASS_KNIGHT && cls <= CLASS_HUNTER)
    {
        auto spelluse = 0;
        auto skillbit = 1;
        for (int j = 0; j < 24; ++j)
        {
            if (skillbit & mob->LearnedSkill[0])
                spelluse += g_pSpell[j + 24 * cls].ManaSpent;

            skillbit *= 2;
        }
        for (int ja = 24; ja < 32; ++ja)
        {
            if (skillbit & mob->LearnedSkill[0])
                spelluse += g_pSpell[96 - (ja + 72)].ManaSpent; //Not sure

            skillbit *= 2;
        }

        if (spellperlevel == spelluse)
        {
            return TRUE;
        }
        else
        {
            mob->SkillBonus = spellperlevel - spelluse;
            return FALSE;
        }
    }

    return FALSE;
}

int BASE_GetBonusScorePoint(STRUCT_MOB* mob, int face, STRUCT_EXT2* ext2)
{
    return FALSE;
}

int BASE_GetBonusSpecialPoint(STRUCT_MOB* mob, int face)
{
    int left;
    int bonus;

    auto totaluse = mob->BaseScore.Special[3]
        + mob->BaseScore.Special[2]
        + mob->BaseScore.Special[1]
        + mob->BaseScore.Special[0];
    auto leveluse = 2 * mob->BaseScore.Level;

    if (BASE_GetCheckFace(face) == 1)
    {
        if (mob->LearnedSkill[0] & 0x40000000)
        {
            leveluse = 855;

            if (mob->BaseScore.Level >= 199)
                leveluse = 2 * (mob->BaseScore.Level - 199) + 855;
        }
        else
        {
            left = mob->BaseScore.Level - 199;

            if (left > 0)
                leveluse += left;

            bonus = BASE_GetItemAbility(mob->Equip, 86);

            if (bonus > 56)
                bonus = 56;

            leveluse += 2 * bonus;

            if (mob->BaseScore.Level >= 355)
                leveluse -= 2 * mob->BaseScore.Level - 708;
        }
    }

    if (leveluse > totaluse)
        mob->SpecialBonus = leveluse - totaluse;

    return TRUE;
}

int BASE_GetHpMp(STRUCT_MOB* mob, int face)
{
    return TRUE; //????
}

int BASE_GetAC(STRUCT_MOB* mob, int face)
{
    if (BASE_GetCheckFace(face))
        mob->BaseScore.Ac = 2 * mob->BaseScore.Level + 4;
    else
        mob->BaseScore.Ac = mob->BaseScore.Level + 4;
    return TRUE;
}

int BASE_NeedLog(STRUCT_ITEM* item, int money)
{
    return TRUE;
}

void BASE_ReadLimitTime()
{
    FILE* fp = NULL;

    fp = fopen("../../LimitTime.txt", "rt");
    if (fp)
    {
        //g_nLimitWarningTime = 0;
        //g_nLimitTime = 0;
        //g_nResetLimitTime = 0;
        //fscanf(fp, "%d\n", &g_nLimitWarningTime);
        //fscanf(fp, "%d\n", &g_nLimitTime);
        //fscanf(fp, "%d\n", &g_nResetLimitTime);
        fclose(fp);
    }
}

void BASE_GetItemFromString(STRUCT_ITEM* item, char* str)
{
    int ia[7];
    char itemtemp[256];

    memset(itemtemp, 0, 256);
    strcpy(itemtemp, str);

    BASE_UnderBarToSpace(itemtemp);

    memset(&item, 0, sizeof(STRUCT_ITEM));
    memset(&ia, 0, 28);

    sscanf(itemtemp, "%d %d %d %d %d %d %d", ia, &ia[1], &ia[2], &ia[3], &ia[4], &ia[5], &ia[6]);

    item->sIndex = ia[0];
    item->stEffect[0].cEffect = ia[1];
    item->stEffect[0].cValue = ia[2];
    item->stEffect[1].cEffect = ia[3];
    item->stEffect[1].cValue = ia[4];
    item->stEffect[2].cEffect = ia[5];
    item->stEffect[2].cValue = ia[6];
}


int BASE_GetClan(int mantle)
{
    int clan = 4;

    const int whiteMantles[] = { 548, 549, 573, 3193, 3196, 3199, 573 };
    int size_white = sizeof(whiteMantles) / sizeof(int);

    for (int i = 0; i < size_white; i++)
    {
        if (mantle == whiteMantles[i])
        {
            clan = 6;
            break;
        }
    }

    const int blueMantles[] = { 544, 546, 1769, 1770, 1771, 3192, 3195, 3198, 1770 };
    int size_blue = sizeof(blueMantles) / sizeof(int);

    for (int i = 0; i < size_blue; i++)
    {
        if (mantle == blueMantles[i])
        {
            clan = 8;
            break;
        }
    }

    const int redMantles[] = { 543, 544, 1766, 1767, 1768, 3191, 3194, 3197, 1767 };
    int size_red = sizeof(redMantles) / sizeof(int);

    for (int i = 0; i < size_red; i++)
    {
        if (mantle == redMantles[i])
        {
            clan = 7;
            break;
        }
    }

    return clan;
}

int BASE_GetMandleLev(int mantle)
{
    return FALSE;
}

int BASE_OnlyUseEngString(char* str)
{
    for (int j = 0; j < strlen(str); ++j)
    {
        auto x = str[j];
        if (x >= 0)
        {
            if ((x < 97 || x > 122) && (x < 65 || x > 90) && (x < 48 || x > 57) && x != 45 && x != 64)
                str[j] = 32;
        }
        else
        {
            str[j] = 32;
        }
    }
    return TRUE;
}

int BOOL_CanRepurchase(STRUCT_REPURCHASEITEM* pRepurchase)
{
    auto iOldOrder = 0;
    for (int i = 0; i < 10; ++i)
    {
        if (!pRepurchase[i].Order)
            return i;
        if (pRepurchase[iOldOrder].Order > pRepurchase[i].Order)
            iOldOrder = i;
    }
    return iOldOrder;
}

void CreateUserPassDir()
{

}

void ConvertScore(STRUCT_SCORE* newScore, STRUCT_SCORE_OLD* oldScore)
{
    newScore->Level = oldScore->Level;
    newScore->Ac = oldScore->Ac;
    newScore->Damage = oldScore->Damage;
    newScore->Reserved = oldScore->Reserved;
    newScore->AttackRun = oldScore->AttackRun;
    newScore->MaxHp = oldScore->MaxHp;
    newScore->MaxMp = oldScore->MaxMp;
    newScore->Hp = oldScore->Hp;
    newScore->Mp = oldScore->Mp;
    newScore->Str = oldScore->Str;
    newScore->Int = oldScore->Int;
    newScore->Dex = oldScore->Dex;
    newScore->Con = oldScore->Con;

    for (int i = 0; i < 4; ++i)
        newScore->Special[i] = oldScore->Special[i];
}

void ConvertMob(STRUCT_MOB* newMob, STRUCT_MOB_OLD* oldMob)
{
    strcpy(newMob->MobName, oldMob->MobName);
    newMob->Clan = oldMob->Clan;
    newMob->Merchant = oldMob->Merchant;
    newMob->Guild = oldMob->Guild;
    newMob->Class = oldMob->Class;
    newMob->Rsv = oldMob->Rsv;
    newMob->Quest = oldMob->Quest;
    newMob->Coin = oldMob->Coin;
    newMob->Exp = oldMob->Exp;
    newMob->HomeTownX = oldMob->HomeTownX;
    newMob->HomeTownY = oldMob->HomeTownY;
    ConvertScore(&newMob->BaseScore, &oldMob->BaseScore);
    ConvertScore(&newMob->CurrentScore, &oldMob->CurrentScore);

    for (int cEquip = 0; cEquip < MAX_EQUIPMENT; ++cEquip)
        memcpy(&newMob->Equip[cEquip], &oldMob->Equip[cEquip], 8);

    for (int cCarry = 0; cCarry < MAX_CARRY; ++cCarry)
        memcpy(&newMob->Carry[cCarry], &oldMob->Carry[cCarry], 8);

    newMob->Carry[63].stEffect[0].cValue = 0;
    newMob->Carry[63].stEffect[1].cValue = 0;
    newMob->Carry[63].stEffect[2].sValue = 0;

    newMob->LearnedSkill[0] = oldMob->LearnedSkill;
    newMob->LearnedSkill[1] = 0;
    newMob->ScoreBonus = oldMob->ScoreBonus;
    newMob->SpecialBonus = oldMob->SpecialBonus;
    newMob->SkillBonus = oldMob->SkillBonus;
    newMob->Critical = oldMob->Critical;
    newMob->SaveMana = oldMob->SaveMana;
    memcpy(newMob->ShortSkill, oldMob->ShortSkill, 8);
    memcpy(newMob->Resist, oldMob->Resist, 4);
}

void ConvertExt(STRUCT_EXT1* newExt, STRUCT_EXT1_OLD* oldExt)
{
    memcpy(newExt, oldExt, 32);

    for (int i = 0; i < 16; ++i)
        memcpy(&newExt->Affect[i].Type, &oldExt->Affect[i].Type, 8);
}

char BASE_GetAttribute(int x, int y)
{
    char result;

    if (x >= 0 && x <= 4096 && y >= 0 && x <= 4096)
        result = g_pAttribute[y / 4 & 0x3FF][x / 4 & 0x3FF];
    else
        result = 0;
    return result;
}

int BASE_EnCode16Str(char* dest)
{
    char szTemp[32];

    memset(szTemp, 0, 32);

    if (strlen(dest) >= 4 && strlen(dest) <= 16)
    {
        for (int i = 0; i < strlen(dest); ++i)
        {
            if (dest[i] < 48 || dest[i] > 57)
            {
                if (dest[i] < 65 || dest[i] > 90)
                {
                    if (dest[i] < 97 || dest[i] > 122)
                        return FALSE;

                    auto v5 = dest[i] - 97;
                    szTemp[2 * i] = v5 - v5 / 2 + 97;
                    szTemp[2 * i + 1] = v5 - (v5 - v5 / 2) + 97;
                }
                else
                {
                    auto v4 = dest[i] - 65;
                    szTemp[2 * i] = v4 - v4 / 2 + 65;
                    szTemp[2 * i + 1] = v4 - (v4 - v4 / 2) + 65;
                }
            }
            else
            {
                auto nTemp1 = dest[i] - 48;
                szTemp[2 * i] = nTemp1 - nTemp1 / 2 + 48;
                szTemp[2 * i + 1] = nTemp1 - (nTemp1 - nTemp1 / 2) + 48;
            }
        }

        auto nTemp2 = szTemp[3];
        szTemp[3] = szTemp[6];
        szTemp[6] = nTemp2;
        
        auto v7 = szTemp[7];
        szTemp[7] = szTemp[0];
        szTemp[0] = v7;

        memcpy(dest, szTemp, 2 * strlen(dest));

        return TRUE;
    }

    return FALSE;
}

int BASE_DeCode16Str(char* dest)
{
    char szTemp[16];

    memset(szTemp, 0, 16);

    int count = strlen(dest);

    if (count >= 8 && count <= 32)
    {
        auto nTemp2 = *dest;
        *dest = dest[7];
        dest[7] = nTemp2;
        
        auto v4 = dest[3];
        dest[3] = dest[6];
        dest[6] = v4;

        for (int i = 0; i < count; i += 2)
        {
            if (dest[i] < 48 || dest[i] > 57)
            {
                if (dest[i] < 65 || dest[i] > 90)
                {
                    if (dest[i] < 97 || dest[i] > 122)
                        return FALSE;

                    szTemp[i / 2] = dest[i] + dest[i + 1] - 97;
                }
                else
                {
                    szTemp[i / 2] = dest[i] + dest[i + 1] - 65;
                }
            }
            else
            {
                szTemp[i / 2] = dest[i] + dest[i + 1] - 48;
            }
        }

        memset(dest, 0, 32);
        memcpy(dest, szTemp, count);

        return TRUE;
    }

    return FALSE;
}

char get_hexa(char num)
{
    char result;

    if (num < 0 || num > 9)
    {
        if (num < 10 || num > 15)
            result = 48;
        else
            result = num + 55;
    }
    else
    {
        result = num + 48;
    }
    return result;
}

void SwapChar(char* pOriginal, char cBad, char cGood)
{
    for (int i = 0; pOriginal[i]; ++i)
    {
        if (pOriginal[i] == cBad)
            pOriginal[i] = cGood;
    }
}

int IntFromHex(char* pChars)
{
    int Hi = *pChars;

    if (Hi < 48 || Hi > 57)
    {
        if (Hi < 97 || Hi > 102)
        {
            if (Hi >= 65 && Hi <= 70)
                Hi -= 55;
        }
        else
        {
            Hi -= 87;
        }
    }
    else
    {
        Hi -= 48;
    }

    int Lo = pChars[1];
    if (Lo < 48 || Lo > 57)
    {
        if (Lo < 97 || Lo > 102)
        {
            if (Lo >= 65 && Lo <= 70)
                Lo -= 55;
        }
        else
        {
            Lo -= 87;
        }
    }
    else
    {
        Lo -= 48;
    }
    return Lo + 16 * Hi;
}

void BASE_URLEncode(char* ret_buf, int ret_len, const char* src_buf, int src_len)
{
    int i = 0;
    for (int j = 0; i < ret_len && j < src_len; ++j)
    {
        if (src_buf[j] == 32)
        {
            ret_buf[i] = 43;
        }
        else if (src_buf[j] != 45 && src_buf[j] != 64 && src_buf[j] != 42 && src_buf[j] != 95 && src_buf[j] != 46)
        {
            if (isalnum(src_buf[j]))
            {
                ret_buf[i] = src_buf[j];
            }
            else
            {
                ret_buf[i] = 37;
                
                auto v4 = i + 1;
                ret_buf[v4] = get_hexa((src_buf[j] >> 4) & 0xF);
                i = v4 + 1;
                ret_buf[i] = get_hexa(src_buf[j] & 0xF);
            }
        }
        else
        {
            ret_buf[i] = src_buf[j];
        }
        ++i;
    }
}

void BASE_URLDecode(char* pEncoded)
{
    char* pDecoded;

    SwapChar(pEncoded, 43, 32);
    pDecoded = pEncoded;
    while (*pEncoded)
    {
        if (*pEncoded == 37)
        {
            if (isxdigit(*++pEncoded))
            {
                if (isxdigit(pEncoded[1]))
                {
                    *pDecoded++ = IntFromHex(pEncoded);
                    pEncoded += 2;
                }
            }
        }
        else
        {
            *pDecoded++ = *pEncoded++;
        }
    }
    *pDecoded = 0;
}

BOOL IsBuffSkill(int nSkillIndex)
{
    return g_pSpell[nSkillIndex].Passive == 0;
}

BOOL IsPassiveSkill(int nSkillIndex)
{
    if (nSkillIndex < 5400)
    {
        if (nSkillIndex >= 5000)
            nSkillIndex -= 5000;
    }
    else
    {
        nSkillIndex -= 5200;
    }
    return g_pSpell[nSkillIndex].Passive == 1;
}

int IsSkill(int nSkillIndex)
{
    if (nSkillIndex < 5000 || nSkillIndex > 5104)
        return (nSkillIndex >= 5400 && nSkillIndex <= 5447);

    return TRUE;
}

int GetSkillIndex(int nSkillIndex)
{
    if (nSkillIndex < 5400)
    {
        if (nSkillIndex >= 5000)
            nSkillIndex -= 5000;
    }
    else
    {
        nSkillIndex -= 5200;
    }

    return nSkillIndex;
}

void DownLoadGuilds()
{
    HINTERNET Session;
    HINTERNET hHttpFile;
    _iobuf* fpGuildTemp;
    unsigned int dwBytesRead;
    char szData[1024];

    dwBytesRead = 0;
    Session = InternetOpenA("MS", 0, 0, 0, 0);
    fpGuildTemp = fopen("Guilds.txt", "wt");
    hHttpFile = InternetOpenUrlA(Session, (LPCSTR)&g_pMessageStringTable[199], 0, 0, 0x4000000u, 0);
    if (hHttpFile && fpGuildTemp)
    {
        memset(szData, 0, 1024);
        InternetReadFile(hHttpFile, szData, 1024, (LPDWORD)&dwBytesRead);
        fwrite(szData, 1, dwBytesRead, fpGuildTemp);

        while (dwBytesRead)
        {
            memset(szData, 0, 1024);
            InternetReadFile(hHttpFile, szData, 1024, (LPDWORD)&dwBytesRead);
            fwrite(szData, 1u, dwBytesRead, fpGuildTemp);
        }
        InternetCloseHandle(hHttpFile);
        fclose(fpGuildTemp);
        //CurrentClientGuild = -1;
        //g_nUpdateGuildName = 2;
        //endthread();
    }
    GetLastError();
}

int IsValidClassSkill(int nSkillIndex)
{
    int kind = 0;

    if (nSkillIndex < 0 || nSkillIndex >= 96)
    {
        if (nSkillIndex >= 96
            && nSkillIndex <= 103
            && !((1 << (nSkillIndex - 72)) & g_pObjectManager->m_stMobData.LearnedSkill[0]))
        {
            return FALSE;
        }
    }
    else
    {
        if (nSkillIndex / 24 != g_pObjectManager->m_stMobData.Class)
            return FALSE;
        if (!((1 << nSkillIndex % 24) & g_pObjectManager->m_stMobData.LearnedSkill[0]))
            return FALSE;
        kind = nSkillIndex % 24 / 8 + 1;
        if (kind <= 0 || kind > 3)
            return FALSE;
    }

    return TRUE;
}

int IsValidSkill(int nSkillIndex)
{
    int result = FALSE;

    if (nSkillIndex < 0 || nSkillIndex >= 104)
    {
        if (nSkillIndex == 205 && g_pObjectManager->m_stMobData.LearnedSkill[1] & 0x20)
        {
            result = 1;
        }
        else if (nSkillIndex == 233 && g_pObjectManager->m_stMobData.LearnedSkill[1] & 0x200)
        {
            result = 1;
        }
        else if (nSkillIndex == 238 && g_pObjectManager->m_stMobData.LearnedSkill[1] & 4)
        {
            result = 1;
        }
        else if (nSkillIndex < 200 || nSkillIndex >= 247)
        {
            result = 0;
        }
        else if (nSkillIndex != 205 && nSkillIndex != 233 && nSkillIndex != 238)
        {
            result = ((1 << 4 * ((nSkillIndex - 200) / 4)) & g_pObjectManager->m_stMobData.LearnedSkill[1]) != 0;
        }
        else
        {
            result = 0;
        }
    }
    else
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
        result = 1;
    }
    return result;
}

char CheckGuildName(char* GuildName, bool bSubguild)
{
    char result;

    if (!bSubguild)
    {
        for (int i = 0; i < strlen(GuildName); ++i)
        {
            if (GuildName[i] == 32)
                return FALSE;
            if (GuildName[i] == 95)
                return FALSE;
        }
    }
    if (strlen(GuildName) >= 2)
    {
        for (int ia = 1; ia < strlen(GuildName); ++ia)
        {
            if (GuildName[ia] == -95 && GuildName[ia - 1] == -95)
                return FALSE;
        }
        
        return TRUE;
    }

    return TRUE;
}

void spaceout(char* str1, char* str2)
{
    int isspace = 1;

    if (strlen(str1) >= 1)
    {
        for (int cnt = 0; str1[cnt] && cnt < 100; ++cnt)
            str2[cnt] = str1[cnt];

        while (isspace)
        {
            isspace = 0;
            for (int cnta = 0; str2[cnta] && cnta < 100; ++cnta)
            {
                if (str2[cnta] == 32)
                {
                    for (int in_cnt = cnta; str2[in_cnt] && in_cnt < 100; ++in_cnt)
                        str2[in_cnt] = str2[in_cnt + 1];
                }
            }
            for (int cntb = 0; str2[cntb] && cntb < 100; ++cntb)
            {
                if (str2[cntb] == 32)
                    isspace = 1;
            }
        }
    }
}

int GetDistance(int x1, int y1, int x2, int y2)
{
    int dy = 0;
    int dx = 0;

    if (x1 <= x2)
        dx = x2 - x1;
    else
        dx = x1 - x2;
    if (y1 <= y2)
        dy = y2 - y1;
    else
        dy = y1 - y2;

    if (dx <= dy)
        return dy + 1;
    else
        return dx + 1;
}

int GetTimeNumber(_SYSTEMTIME* pTime)
{
    return pTime->wMinute
        + (60 * pTime->wHour)
        + (1440 * pTime->wDay)
        + (43200 * pTime->wMonth)
        + (518400 * pTime->wYear);
}

void SetMinimapPos()
{
    return;
}

void Guildmark_Download(void* pArg)
{
}

int IsChannelWarZone()
{
    return FALSE;
}

int BASE_CheckEngString(char* str)
{
    int len = strlen(str);
    for (int j = 0; j < len; ++j)
    {
        auto x = str[j];
        if (x >= 0)
        {
            if ((x < 97 || x > 122) && (x < 65 || x > 90) && (x < 48 || x > 57) && x != 45)
                return 0;
        }
        else
        {
            str[j] = 32;
        }
    }
    return 1;
}

unsigned int BASE_GetCandidateList(HIMC* hIMC, unsigned int dwIndex, tagCANDIDATELIST* lpCand, unsigned int dwBufLen, unsigned int* lpdwListCount)
{
    auto bytes = ImmGetCandidateListA((HIMC)&hIMC, dwIndex, lpCand, dwBufLen);

    if (bytes)
    {
        return bytes;
    }

    return FALSE;
}