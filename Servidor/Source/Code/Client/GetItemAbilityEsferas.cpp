#include "main.h"

int g_pMountTempBonus[20][5] =
{
	// AttackAdd, MagicAdd, Evasion, Resistence, Speed

	{ 35, 7, 0, 0, 6 },//Shire 3D
	{ 350, 55, 10, 28, 6 },//Thoroughbred 3D
	{ 450, 55, 0, 0, 6 },//Klazedale 3D
	{ 35, 7, 0, 0, 6 },//Shire 15D
	{ 450, 72, 10, 28, 6 },//Thoroughbred 15D
	{ 450, 72, 0, 0, 6 },//Klazedale 15D
	{ 120, 45, 0, 0, 6 },//Shire 30D
	{ 450, 72, 10, 28, 6 },//Thoroughbred 30D
	{ 450, 72, 0, 0, 6 },//Klazedale 30D
	{ 325, 35, 16, 28, 6 },//Gulfaxi 30D
	{ 350, 45, 10, 4, 6 },//Tigre de Fogo
	{ 250, 25, 0, 31, 6 },//Dragão Vermelho
	{ 80, 15, 0, 31, 6 },//Dragão Menor
	{ 950, 145, 60, 20, 6 },//Dragão Akelo
	{ 950, 145, 60, 20, 6 },//Dragão Hekalo
};

INT32 HKD_GetItemAbility_Esferas(STRUCT_ITEM* item, INT32 effectId)
{

	if (item->sIndex >= 3980 && item->sIndex <= 3994)
	{
		int cd = item->sIndex - 3980;

		switch (effectId)
		{
		case EF_DAMAGE:
			return g_pMountTempBonus[cd][0];
		case EF_MAGIC:
			return g_pMountTempBonus[cd][1];
		case EF_PARRY:
			return g_pMountTempBonus[cd][2];
		case EF_RESISTALL:
			return g_pMountTempBonus[cd][3];
		default:
			break;
		}
	
	}
	/*
	if (item->sIndex == 3980 || item->sIndex == 3983 || item->sIndex == 3986)
	{
		switch (effectId)
		{
		case 2:
			return 35;

		case 60:
			return 7;
		}
	}
	else if (item->sIndex == 3981 || item->sIndex == 3984 || item->sIndex == 3987)
	{
		switch (effectId)
		{
		case 2:
			return 210;

		case 60:
			return 40;

		case 54:
			return 28;
		}
	}
	else if (item->sIndex == 3993 || item->sIndex == 3994)
	{
		switch (effectId)
		{
		case 2:
			return 750;
		case 60:
			return 125;
		case 54:
			return 20;
		}
	}
	else if (item->sIndex >= 3995 && item->sIndex <= 3996)
	{
		switch (effectId)
		{
		case 2:
			return 0;

		case 60:
			return 0;
		}
	}*/

	return 0;
}