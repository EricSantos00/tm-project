
#include "ProcessClientMessage.h"

void Exec_MSG_PutoutSeal(int conn, char *pMsg)
{
	MSG_PutoutSeal *m = (MSG_PutoutSeal*)pMsg;

	if (pUser[conn].Mode != USER_PLAY)
	{
		SendHpMode(conn);
		return;
	}

	if (pUser[conn].Trade.OpponentID)
	{
		RemoveTrade(conn);
		return;
	}

	if (pMob[conn].MOB.CurrentScore.Hp == 0)
	{
		SendHpMode(conn);
		AddCrackError(conn, 1, 15);

		if (m->SourType == ITEM_PLACE_CARRY)
			SendItem(conn, m->SourType, m->SourPos, &pMob[conn].MOB.Carry[m->SourPos]);

		else if (m->SourType == ITEM_PLACE_CARGO)
			SendItem(conn, m->SourType, m->SourPos, &pUser[conn].Cargo[m->SourPos]);

		else
			SendItem(conn, m->SourType, m->SourPos, &pMob[conn].MOB.Equip[m->SourPos]);

		return;
	}

	if (m->GridX >= MAX_GRIDX || m->GridY >= MAX_GRIDY)
	{
		CrackLog(conn, " Drop grid, out of range");
		return;
	}

	STRUCT_ITEM *item = GetItemPointer(&pMob[conn].MOB, pUser[conn].Cargo, m->SourType, m->SourPos);

	if (item == NULL)
	{
		sprintf(temp, "err,use item fail source %d %d", m->SourType, m->SourPos);
		Log(temp, "-system", 0);
		return;
	}

	if(item->sIndex != 3443)
	{
		CrackLog(conn, "outseal no 3443");
		return;
	}

	if(item->stEffect[0].cEffect == 0)
	{
		CrackLog(conn, "outseal no effect");
		return;
	}

	m->MobName[NAME_LENGTH - 1] = 0;
	m->MobName[NAME_LENGTH - 2] = 0;

	if (BASE_CheckValidString(m->MobName) == 0)
	{
		SendItem(conn, m->SourType, m->SourPos, item);
		return;
	}
	CharLogOut(conn);

	MSG_DBOutCapsule sm_outc;
	memset(&sm_outc, 0, sizeof(MSG_DBOutCapsule));

	sm_outc.Size = sizeof(MSG_DBOutCapsule);
	sm_outc.Type = _MSG_DBOutCapsule;
	sm_outc.ID = conn;

	sm_outc.Slot = pUser[conn].Slot;
	sm_outc.SourType = m->SourType;
	sm_outc.SourPos = m->SourPos;
	sm_outc.DestType = m->DestType;
	sm_outc.DestPos = m->DestPos;
	sm_outc.GridX = m->GridX;
	sm_outc.GridY = m->GridY;
	sm_outc.WarpID = m->WarpID;

	strncpy(sm_outc.MobName, m->MobName, 12);

	sprintf(temp, "etc,outcapsule srctype:%d srcslot:%d name:%s", m->SourType, m->SourPos, m->MobName);
	Log(temp, pMob[conn].MOB.MobName, pUser[conn].IP);

	DBServerSocket.SendOneMessage((char*)&sm_outc, sizeof(MSG_DBOutCapsule));
}