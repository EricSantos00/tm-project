#include "ProcessClientMessage.h"

void NTask_CapMercenario(int a_iConn, int a_iTarget, int confirm)
{
	if (pMob[a_iConn].Extra.QuestInfo.Mortal.TerraMistica != 0 || pMob[a_iConn].Extra.ClassMaster != MORTAL)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_Hurry_Helping_them]);
		return;
	}

	if (confirm == 0)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_Monster_Attaking_Us_Help]);
		return;
	}

	if (pMob[a_iConn].Leader)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_Party_Only]);
		return;
	}

	pMob[a_iConn].Extra.QuestInfo.Mortal.TerraMistica = 1;
	SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Get_Watching_Town_Mission]);

	sprintf(temp, "etc,mysticalland complete. name:%s", pMob[a_iConn].MOB.MobName);
	MyLog(LogType::Quests, temp, 0, 0, pUser[a_iConn].IP);
	return;
}

void NTask_CapExpor(int a_iConn, int a_iTarget)
{
	if (pMob[a_iConn].Extra.QuestInfo.Mortal.TerraMistica == 0)
	{
		BASE_GetLanguage(temp, _NN_Guard_This_Village);
		SendSay(a_iTarget, temp);
		return;
	}

	if (pMob[a_iConn].Extra.QuestInfo.Mortal.TerraMistica != 2)
	{
		BASE_GetLanguage(temp, _SN_All_Villagers_Thanks_Your, pMob[a_iConn].MOB.MobName);
		SendSay(a_iTarget, temp);
		return;
	}

	int _Level = pMob[a_iConn].MOB.CurrentScore.Level;
	int _ItemID = 551;
	int _ItemType = 1;

	if (_Level >= 50)
	{
		if (_Level >= 80)
		{
			_ItemID = rand() % 4 + 559;
			_ItemType = 0;
		}
		else
		{
			_ItemID = rand() % 4 + 555;
			_ItemType = 1;
		}
	}
	else
	{
		_ItemID = rand() % 4 + 551;
		_ItemType = 1;
	}

	STRUCT_ITEM Item;
	memset(&Item, 0, sizeof(STRUCT_ITEM));

	Item.sIndex = _ItemID;

	int _rd = rand() % 10;

	int bonustype = g_pBonusType[_rd];

	int bonusvalue1 = g_pBonusValue[_rd][_ItemType][0];
	int bonusvalue2 = g_pBonusValue[_rd][_ItemType][1];
	int fvalue = bonusvalue2 + 1 - bonusvalue1;
	int tvalue = rand() % fvalue + bonusvalue1;

	Item.stEffect[0].cEffect = 43;

	for (int z = 1; z <= 2; ++z)
	{
		int rd_ = rand() % 8;

		if (rd_)
		{
			switch (rd_)
			{
			case 1:
				Item.stEffect[z].cEffect = 2;
				Item.stEffect[z].cValue = rand() % 21 + 5;
				break;

			case 2:
				Item.stEffect[z].cEffect = 26;
				Item.stEffect[z].cValue = rand() % 11 + 5;
				break;

			case 3:
				Item.stEffect[z].cEffect = 5;
				Item.stEffect[z].cValue = rand() % 51 + 20;
				break;

			case 4:
				Item.stEffect[z].cEffect = 60;
				Item.stEffect[z].cValue = rand() % 7 + 2;
				break;

			case 5:
				Item.stEffect[z].cEffect = 7;
				Item.stEffect[z].cValue = rand() % 16 + 5;
				break;

			case 6:
				Item.stEffect[z].cEffect = 8;
				Item.stEffect[z].cValue = rand() % 16 + 5;
				break;

			case 7:
				Item.stEffect[z].cEffect = 9;
				Item.stEffect[z].cValue = rand() % 16 + 5;
				break;
			}
		}
		else
		{
			Item.stEffect[z].cEffect = 4;
			Item.stEffect[z].cValue = rand() % 41 + 20;
		}
	}

	PutItem(a_iConn, &Item);

	BASE_GetLanguage(temp, _NN_Give_You_Some_Reward);
	SendSay(a_iTarget, temp);

	pMob[a_iConn].Extra.QuestInfo.Mortal.TerraMistica = 3;
	SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Watching_Town_Awarded]);

	sprintf(temp, "etc,mystical_land complete %d-%d:%d:%d:%d:%d:%d name:%s conn:%d", Item.sIndex, Item.stEffect[0].cEffect, Item.stEffect[0].cValue, Item.stEffect[1].cEffect, Item.stEffect[1].cValue, Item.stEffect[2].cEffect, Item.stEffect[2].cValue, pMob[a_iConn].MOB.MobName, a_iConn);
	MyLog(LogType::Quests, temp, 0, 0, pUser[a_iConn].IP);
	return;
}