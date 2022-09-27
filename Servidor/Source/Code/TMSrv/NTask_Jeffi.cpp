#include "ProcessClientMessage.h"

void NTask_Jeffi(int a_iConn, int a_iTarget)
{
	if (!NPCBlock[Jeffi])
	{
		SendClientMsg(a_iConn, g_pMessageStringTable[_NN_NPCBLOCKED]);
		return;
	}

	if (pMob[a_iConn].MOB.Equip[13].sIndex == 447 || pMob[a_iConn].MOB.Equip[13].sIndex == 692)
	{
		int price = 0;
		if (pMob[a_iConn].MOB.Equip[13].sIndex == 447)
			price = 1000000;

		else
		{
			if (pMob[a_iConn].MOB.Equip[13].sIndex != 692)
				return;

			price = 5000000;
		}

		if (pMob[a_iConn].MOB.Coin >= price)
		{
			if (price == 1000000)
			{
				pMob[a_iConn].MOB.Coin -= 1000000;
				pMob[a_iConn].MOB.Equip[13].sIndex = rand() % 3 + 448;
			}
			else
			{
				pMob[a_iConn].MOB.Coin -= 5000000;
				pMob[a_iConn].MOB.Equip[13].sIndex = rand() % 3 + 693;
			}

			SendItem(a_iConn, ITEM_PLACE_EQUIP, 13, &pMob[a_iConn].MOB.Equip[13]);
			SendEtc(a_iConn);
			SendSay(a_iTarget, g_pMessageStringTable[_NN_Processing_Complete]);
			SetAffect(a_iConn, 44, 20, 20);
			SendScore(a_iConn);

			sprintf(temp, "etc,jeffi make reset50-100 name:%s level:%d", pMob[a_iConn].MOB.MobName, pMob[a_iConn].MOB.BaseScore.Level);
			MyLog(LogType::Quests, temp, 0, 0, pUser[a_iConn].IP);
		}
		else
		{
			if (price == 1000000)
				SendSay(a_iTarget, g_pMessageStringTable[_NN_Need_1000000_Gold]);
			else
				SendSay(a_iTarget, g_pMessageStringTable[_NN_Need_5000000_Gold]);
		}
	}
	else
	{
		int Ori = 0;
		int Lac = 0;
		short PacOri = 0;
		short PacLac = 0;

		for (int i = 0; i < pMob[a_iConn].MaxCarry; i++)
		{
			if (pMob[a_iConn].MOB.Carry[i].sIndex == 419)
				Ori += pMob[a_iConn].MOB.Carry[i].stEffect[0].cEffect == 61 ? pMob[a_iConn].MOB.Carry[i].stEffect[0].cValue : 1;

			if (pMob[a_iConn].MOB.Carry[i].sIndex == 420)
				Lac += pMob[a_iConn].MOB.Carry[i].stEffect[0].cEffect == 61 ? pMob[a_iConn].MOB.Carry[i].stEffect[0].cValue : 1;
		}

		int SlotId = -1;

		for (int i = 0; i < pMob[a_iConn].MaxCarry; i++)
		{
			if (pMob[a_iConn].MOB.Carry[i].sIndex == 0)
			{
				SlotId = i;

				break;
			}
		}

		if (pMob[a_iConn].MOB.Coin >= 1000000)
		{
			STRUCT_ITEM Poeira;
			memset(&Poeira, 0, sizeof(STRUCT_ITEM));

			bool Flag = false;

			if (SlotId != -1)
			{
				if (Ori >= 10)
				{
					while (Ori >= 10)
					{
						PacOri++;
						RemoveItem(a_iConn, 419, 10);
						Ori -= 10;
					}

					Flag = true;

					Poeira.sIndex = 412;
					Poeira.stEffect[0].cEffect = 61;
					Poeira.stEffect[0].cValue = PacOri;
					PutItem(a_iConn, &Poeira);
				}

				else if (Lac >= 10)
				{
					while (Lac >= 10)
					{
						PacLac++;
						RemoveItem(a_iConn, 420, 10);
						Lac -= 10;
					}

					Flag = true;

					Poeira.sIndex = 413;
					Poeira.stEffect[0].cEffect = 61;
					Poeira.stEffect[0].cValue = PacLac;
					PutItem(a_iConn, &Poeira);
				}
			}

			else
			{
				SendClientMsg(a_iConn, g_pMessageStringTable[_NN_You_Have_No_Space_To_Trade]);
				return;
			}

			if (Flag)
			{
				SetAffect(a_iConn, 44, 20, 20);
				SendScore(a_iConn);
				SendCarry(a_iConn);
				SendEtc(a_iConn);

				SendSay(a_iTarget, g_pMessageStringTable[_NN_Processing_Complete]);

				pMob[a_iConn].MOB.Coin -= 1000000;

				sprintf(temp, "etc,jeffi make lac_ori name:%s level:%d", pMob[a_iConn].MOB.MobName, pMob[a_iConn].MOB.BaseScore.Level);
				MyLog(LogType::Quests, temp, 0, 0, pUser[a_iConn].IP);
			}
			else
				SendSay(a_iTarget, g_pMessageStringTable[_NN_Need_10_Particle]);

		}
		else
			SendSay(a_iTarget, g_pMessageStringTable[_NN_Need_1000000_Gold]);
	}
	return;
}