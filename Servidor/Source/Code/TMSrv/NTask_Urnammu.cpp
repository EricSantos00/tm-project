#include "ProcessClientMessage.h"

void NTask_Urnammu(int a_iConn, int a_iTarget)
{
	if (!NPCBlock[Urnammu])
	{
		SendClientMsg(a_iConn, g_pMessageStringTable[_NN_NPCBLOCKED]);
		return;
	}

	if (pMob[a_iConn].Extra.ClassMaster != CELESTIALCS)
	{
		sprintf(temp, g_pMessageStringTable[_SN_NEEDCLASS], "Sub Celestial");
		SendClientMsg(a_iConn, temp);
		return;
	}
	if (pMob[a_iConn].MOB.Equip[11].sIndex < 1760 || pMob[a_iConn].MOB.Equip[11].sIndex > 1763)
	{
		sprintf(temp, g_pMessageStringTable[_SN_WANTEQUIPITEM], "o Sephirot da classe escolhida");
		SendClientMsg(a_iConn, temp);
		return;
	}
	if (pMob[a_iConn].Extra.Fame < 2000)
	{
		sprintf(temp, g_pMessageStringTable[_DN_NEEDFAME], 2000);
		SendClientMsg(a_iConn, temp);
		return;
	}

	pMob[a_iConn].Extra.Fame -= 2000;

	pMob[a_iConn].Extra.SaveCelestial[1].Class = pMob[a_iConn].MOB.Equip[11].sIndex - 1760;

	pMob[a_iConn].Extra.SaveCelestial[1].BaseScore.Str = BaseSIDCHM[pMob[a_iConn].MOB.Class][0];
	pMob[a_iConn].Extra.SaveCelestial[1].BaseScore.Int = BaseSIDCHM[pMob[a_iConn].MOB.Class][1];
	pMob[a_iConn].Extra.SaveCelestial[1].BaseScore.Dex = BaseSIDCHM[pMob[a_iConn].MOB.Class][2];
	pMob[a_iConn].Extra.SaveCelestial[1].BaseScore.Con = BaseSIDCHM[pMob[a_iConn].MOB.Class][3];

	memset(pMob[a_iConn].Extra.SaveCelestial[1].SkillBar1, 0, 4);
	memset(pMob[a_iConn].Extra.SaveCelestial[1].SkillBar2, 0, 16);

	int special = pMob[a_iConn].Extra.SaveCelestial[1].SpecialBonus;
	int specialreset = 55;

	for (int i = 0; i < 4; i++)
	{
		if (pMob[a_iConn].Extra.SaveCelestial[1].BaseScore.Special[i] <= 55)
		{
			special += pMob[a_iConn].Extra.SaveCelestial[1].BaseScore.Special[i];
			pMob[a_iConn].Extra.SaveCelestial[1].BaseScore.Special[i] = 0;
		}
		else
		{
			special += specialreset;
			pMob[a_iConn].Extra.SaveCelestial[1].BaseScore.Special[i] -= specialreset;
		}
	}

	pMob[a_iConn].Extra.SaveCelestial[1].SpecialBonus = special;

	pMob[a_iConn].Extra.SaveCelestial[1].LearnedSkill &= 0xFF000000;

	memset(&pMob[a_iConn].MOB.Equip[11], 0, sizeof(STRUCT_ITEM));

	SendItem(a_iConn, ITEM_PLACE_EQUIP, 11, &pMob[a_iConn].MOB.Equip[11]);

	SendClientMsg(a_iConn, g_pMessageStringTable[_NN_My_King_Bless1]);
	return;
}