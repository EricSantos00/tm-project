
#include "ProcessClientMessage.h"

void Exec_MSG_DropItem(int conn, char *pMsg)
{
	MSG_DropItem *m = (MSG_DropItem*)pMsg;

	if (pMob[conn].MOB.CurrentScore.Hp <= 0 || pUser[conn].Mode != USER_PLAY)
	{
		AddCrackError(conn, 1, 14);
		SendHpMode(conn);
		return;
	}

	if (pUser[conn].Trade.OpponentID)
	{
		RemoveTrade(pUser[conn].Trade.OpponentID);
		RemoveTrade(conn);
		return;
	}
 
	if (pUser[conn].TradeMode)
	{
		SendClientMsg(conn, g_pMessageStringTable[_NN_CantWhenAutoTrade]);
		return;
	}

	if (pUser[conn].IsBlocked)
	{
		RemoveTrade(pUser[conn].Trade.OpponentID);
		SendClientMsg(conn, "Sua conta está com o bloqueio ativo para essa operação.");
		RemoveTrade(conn);
		return;
	}

	if (m->GridX >= MAX_GRIDX || m->GridY >= MAX_GRIDY)
	{
		sprintf(temp, "err,wrong drop pos %d %d", m->GridX, m->GridY);
		Log(temp, pUser[conn].AccountName, pUser[conn].IP);
		return;
	}

	if (isDropItem == 0)
		return SendClientMsg(conn, "Não é possivel dropar itens no chão, jogue-o na lixeira da mochila.");;

	int gridx = m->GridX;
	int gridy = m->GridY;

	int titem = GetEmptyItemGrid(&gridx, &gridy);

	m->GridX = gridx;
	m->GridY = gridy;

	if (titem == 0)
	{
		SendClientMsg(conn, g_pMessageStringTable[_NN_Cant_Drop_Here]);
		return;
	}

	if (m->SourType == ITEM_PLACE_EQUIP)
	{
		Log("err,dropitem - sourtype", pUser[conn].AccountName, pUser[conn].IP);
		return;
	}

	if (m->SourType)
	{
		if (m->SourType == ITEM_PLACE_CARRY)
		{
			if (m->SourPos < 0 || m->SourPos >= pMob[conn].MaxCarry)
			{
				Log("err,dropitem - carry equip", pUser[conn].AccountName, pUser[conn].IP);
				return;
			}
		}
		else
		{
			if (m->SourType != ITEM_PLACE_CARGO)
			{
				Log("err,dropitem - sourtype", pUser[conn].AccountName, pUser[conn].IP);
				return;
			}
			if (m->SourPos < 0 || m->SourPos >= MAX_CARGO)
			{
				Log("err,dropitem - sourpos cargo", pUser[conn].AccountName, pUser[conn].IP);
				return;
			}
		}
	}

	STRUCT_ITEM *SrcItem = GetItemPointer(&pMob[conn].MOB, pUser[conn].Cargo, m->SourType, m->SourPos);
	STRUCT_ITEM *BackupItem = GetItemPointer(&pMob[conn].MOB, pUser[conn].Cargo, m->SourType, m->SourPos);


	if (SrcItem == NULL || BackupItem == NULL)
		return;

	if (SrcItem->sIndex <= 0 || SrcItem->sIndex >= MAX_ITEMLIST)
		return;

	if (SrcItem->sIndex != 508 && SrcItem->sIndex != 509 && SrcItem->sIndex != 522
		&& (SrcItem->sIndex < 526 || SrcItem->sIndex > 537) && SrcItem->sIndex != 446 && SrcItem->sIndex != 747 && SrcItem->sIndex != 3993 && SrcItem->sIndex != 3994)
	{
		int drop = CreateItem(m->GridX, m->GridY, SrcItem, m->Rotate, 1);

		if (drop <= 0 || drop >= MAX_ITEM)
		{
			SendClientMsg(conn, "Can't create object(item)");
			return;
		}

		char tmplog[2048];
		BASE_GetItemCode(SrcItem, tmplog);
		sprintf(temp, "dropitem, %s", tmplog);
		MyLog(LogType::Itens, pUser[conn].AccountName, temp, 0, pUser[conn].IP);

		memset(SrcItem, 0, sizeof(STRUCT_ITEM));
							 
		MSG_CNFDropItem sm_ditem;
		memset(&sm_ditem, 0, sizeof(MSG_CNFDropItem));

		sm_ditem.Type = _MSG_CNFDropItem;
		sm_ditem.Size = sizeof(MSG_CNFDropItem);

		sm_ditem.SourType = m->SourType;
		sm_ditem.SourPos = m->SourPos;
		sm_ditem.Rotate = m->Rotate;
		sm_ditem.GridX = m->GridX;
		sm_ditem.GridY = m->GridY;

		pUser[conn].cSock.SendOneMessage((char*)&sm_ditem, sizeof(MSG_CNFDropItem));
	}
	else
	{
		SendClientMsg(conn, g_pMessageStringTable[_NN_Guild_Medal_Cant_Be_Droped]);
		return;
	}
}