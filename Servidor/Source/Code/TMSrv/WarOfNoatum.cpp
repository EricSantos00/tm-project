#include "WarOfNoatum.h"
#include "../Basedef.h"
void WarNoatum()
{
	time_t rawtime;
	tm* timeinfo;
	int minDefine = 5;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	int hourNotice = warsTimer[eNoatum].Hour;
	int minNotice;

	if (!warsTimer[eNoatum].Minute)
		minNotice = 60 - minDefine;
	
	if (warsTimer[eNoatum].Minute < 5)
	{
		hourNotice = warsTimer[eNoatum].Hour - 1;
		minNotice = (60 - minDefine) + warsTimer[eNoatum].Minute;
	}
	else
		minNotice = warsTimer[eNoatum].Minute - minDefine;

	if (CastleServer == 1 && (timeinfo->tm_hour == hourNotice 
		&& timeinfo->tm_min >= minNotice
		&& CastleState == 0 && !notWarNoatum 
		&& timeinfo->tm_min <= warsTimer[eNoatum].Minute))
	{
		int minRest = warsTimer[eNoatum].Minute - timeinfo->tm_min;
		sprintf(temp, g_pMessageStringTable[_DN_Castle_will_be_open], minRest);
		SendNotice(temp);
		CastleState = 1;
		notWarNoatum = TRUE;
		for (int j = 0; j < MAX_USER; j++)
		{
			if (pUser[j].Mode == USER_PLAY)
				SendClientSignalParm(j, ESCENE_FIELD, 940, CastleState);
		}
		return;
	}


	if (CastleState == 1 && (timeinfo->tm_hour == warsTimer[eNoatum].Hour && timeinfo->tm_min >= warsTimer[eNoatum].Minute))
	{
		ClearAreaGuild(1036, 1672, 1144, 1764, g_pGuildZone[4].ChargeGuild);

		ClearAreaTeleport(1129, 1705, 1129, 1709, 1057, 1742);
		ClearAreaTeleport(1116, 1705, 1116, 1709, 1057, 1742);
		ClearAreaTeleport(1094, 1688, 1094, 1692, 1057, 1742);
		ClearAreaTeleport(1087, 1609, 1087, 1713, 1057, 1742);
		ClearAreaTeleport(1050, 1690, 1050, 1690, 1057, 1742);
		ClearAreaTeleport(1046, 1690, 1047, 1691, 1057, 1742);
		ClearAreaTeleport(1124, 1708, 1124, 1708, 1057, 1742);

		SetCastleDoor(3);

		for (int i = 0; i < 3; ++i)
		{
			GenerateMob(i + TORRE_NOATUM1, 0, 0);
			LiveTower[i] = 1;
		}

		sprintf(temp, g_pMessageStringTable[_DN_Castle_opened]);
		SendNotice(temp);
		CastleState = 2;
		return;
	}

	int minFinish = warsTimer[eNoatum].Minute;
	int hourFinish = warsTimer[eNoatum].Hour + 1;
	
	if (hourFinish >= 24)
		hourFinish = 0;

	if (CastleState == 2 && (timeinfo->tm_hour == hourFinish && timeinfo->tm_min == (minFinish -minDefine)))
	{
		sprintf(temp, g_pMessageStringTable[_DN_Castle_will_be_closed], minDefine);
		SendNotice(temp);
		CastleState = 3;
	}

	if (CastleState == 3 && timeinfo->tm_hour == hourFinish && timeinfo->tm_min == minFinish)
	{
		sprintf(temp, g_pMessageStringTable[_DN_Castle_closed]);
		SendNotice(temp);
		FinishCastleWar();
	}

	
}

void FinishCastleWar()
{
	SetCastleDoor(1);

	ClearAreaGuild(1036, 1672, 1144, 1764, g_pGuildZone[4].ChargeGuild);

	CastleState = 0;

	pUser[playerAltar].CastleStatus = 0;

	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;

		SendClientSignal(i, _MSG_SendCastleState, CastleState);
	}

	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;

		SendClientSignalParm(i, ESCENE_FIELD, _MSG_SendCastleState, CastleState);
	}

	for (int i = MAX_USER; i < MAX_MOB; i++)
	{
		if (pMob[i].Mode == MOB_EMPTY)
			continue;

		if (pMob[i].MOB.Equip[0].sIndex == 219 ||
			strncmp(pMob[i].MOB.MobName, "Judith", NAME_LENGTH) == 0)
			DeleteMob(i, 2);
	}

	ClearArea(1036, 1672, 1144, 1764);

	CReadFiles::WriteGuild();
}

void SetCastleDoor(int state)
{
	for (int i = 0; i < 4; i++)
	{
		int DoorId = i + 36;

		if (pItem[DoorId].ITEM.sIndex <= 0 || pItem[DoorId].ITEM.sIndex >= MAX_ITEMLIST)
			continue;

		if (pItem[DoorId].State == state)
			continue;

		int height = 0;

		UpdateItem(DoorId, state, &height);

		if (state == STATE_OPEN)
		{
			MSG_UpdateItem sm;
			memset(&sm, 0, sizeof(MSG_UpdateItem));

			sm.ID = ESCENE_FIELD;
			sm.Type = _MSG_UpdateItem;
			sm.ItemID = DoorId + 10000;
			sm.Size = sizeof(MSG_UpdateItem);
			//		sm.Height = height;
			sm.State = pItem[DoorId].State;

			GridMulticast(pItem[DoorId].PosX, pItem[DoorId].PosY, (MSG_STANDARD*)&sm, 0);
		}
		else
		{
			int keyid = BASE_GetItemAbility(&pItem[DoorId].ITEM, EF_KEYID);

			if (keyid == 15)
				CreateMob("GATE", pItem[DoorId].PosX, pItem[DoorId].PosY, "npc", 0);

			MSG_CreateItem sm;
			memset(&sm, 0, sizeof(MSG_CreateItem));

			GetCreateItem(DoorId, &sm);

			GridMulticast(pItem[DoorId].PosX, pItem[DoorId].PosY, (MSG_STANDARD*)&sm, 0);
		}
		pItem[DoorId].Delay = 0;
	}
}

void MasterCastle(int conn)
{
	if (conn > 0 && conn < MAX_USER && pMob[conn].MOB.CurrentScore.Hp > 0)
	{

		int Guild = pMob[conn].MOB.Guild;
		if (CastleState <= 1 || pMob[conn].TargetX != 1046 || pMob[conn].TargetY != 1690 || Guild <= 0 || pMob[conn].MOB.GuildLevel < 6 || Guild == g_pGuildZone[4].ChargeGuild)
		{
			pUser[conn].CastleStatus = 0;

			if (playerAltar == conn)
				playerAltar = 0;
		
			else
				SendClientSignalParm(conn, ESCENE_FIELD, _MSG_StartTime, 
					pUser[playerAltar].CastleStatus);
	
			//if ((pMob[conn].TargetX >= 1042 && pMob[conn].TargetX <= 1095) &&(pMob[conn].TargetY >= 1679 && pMob[conn].TargetY <= 1701))
			
		
		}

		else
		{
			int Citys = 0;

			for (int i = 0; i < ValidGuild; i++)
			{
				if (g_pGuildZone[i].ChargeGuild == pMob[conn].MOB.Guild && i != 4)
					Citys++;
			}

			if (Citys != 0)
			{
				if (pUser[conn].CastleStatus == 0)
				{
					playerAltar = conn;
					//countAltarDec = 180; //3min
					sprintf(temp, g_pMessageStringTable[_SN_S_is_charging_castle], pMob[conn].MOB.MobName);
					SendNotice(temp);
					
				}
				MSG_STANDARDPARM sm;
				memset(&sm, 0, sizeof(MSG_STANDARDPARM));

				sm.Type = _MSG_SendCastleState2;
				sm.Size = sizeof(MSG_STANDARDPARM);
				sm.ID = conn;
				sm.Parm = 1;

				GridMulticast(pMob[conn].TargetX, pMob[conn].TargetY, (MSG_STANDARD*)&sm, 0);
				
				//countAltarDec -= pUser[conn].CastleStatus;
				//Contador Altar de Thor
				SendClientSignalParm(conn, ESCENE_FIELD, _MSG_StartTime, pUser[conn].CastleStatus++);
				//pUser[conn].CastleStatus++;
				if (pUser[conn].CastleStatus > 180)//Dominou o Altar
				{
					sprintf(temp, g_pMessageStringTable[_SN_S_charge_castle], pMob[conn].MOB.MobName);
					SendNotice(temp);

					g_pGuildZone[4].ChargeGuild = Guild;
					g_pGuildZone[4].Clan = pMob[conn].MOB.Clan;

					FinishCastleWar();

					for (int i = 0; i < MAX_USER; i++)
						ClearCrown(i);
				}

			}
		}
	}
}
