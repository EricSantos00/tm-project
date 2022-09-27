#include "AccountBuff.h"

void LoadBuff(int conn)
{
	int sAffect = GetEmptyAffect(conn, SAUDE_TYPE);

	if (sAffect != -1)
	{
		if (!AccountSaveBuff[0])
		{
			pMob[conn].Affect[sAffect].Type = 0;
			pMob[conn].Affect[sAffect].Level = 0;
			pMob[conn].Affect[sAffect].Value = 0;
		}
		else
		{
			pMob[conn].Affect[sAffect].Type = SAUDE_TYPE;
			pMob[conn].Affect[sAffect].Level = 1;
			pMob[conn].Affect[sAffect].Value = 0;
		}
		
		pMob[conn].Affect[sAffect].Time = AccountSaveBuff[0];
		pMob[conn].GetCurrentScore(conn);
		SendScore(conn);
	}

	sAffect = GetEmptyAffect(conn, SEPHIRA_TYPE);

	if (sAffect != -1)
	{
		if (!AccountSaveBuff[1])
		{
			pMob[conn].Affect[sAffect].Type = 0;
			pMob[conn].Affect[sAffect].Level = 0;
			pMob[conn].Affect[sAffect].Value = 0;
		}
		else
		{
			pMob[conn].Affect[sAffect].Type = SEPHIRA_TYPE;
			pMob[conn].Affect[sAffect].Level = 0;
			pMob[conn].Affect[sAffect].Value = 1;
		}
		
		pMob[conn].Affect[sAffect].Time = AccountSaveBuff[1];
		pMob[conn].GetCurrentScore(conn);
		SendScore(conn);
	}

	sAffect = GetEmptyAffect(conn, BOXEXP_TYPE);

	if (sAffect != -1)
	{
		if (!AccountSaveBuff[2])
		{
			pMob[conn].Affect[sAffect].Type = 0;
			pMob[conn].Affect[sAffect].Level = 0;
			pMob[conn].Affect[sAffect].Value = 0;
		}
		else
		{
			pMob[conn].Affect[sAffect].Type = BOXEXP_TYPE;
			pMob[conn].Affect[sAffect].Level = 2000;
			pMob[conn].Affect[sAffect].Value = 0;
		}
		
		pMob[conn].Affect[sAffect].Time = AccountSaveBuff[2];
		pMob[conn].GetCurrentScore(conn);
		SendScore(conn);
	}

	sAffect = GetEmptyAffect(conn, PVM_TYPE);

	if (sAffect != -1)
	{
		if (!AccountSaveBuff[3])
		{
			pMob[conn].Affect[sAffect].Type = 0;
			pMob[conn].Affect[sAffect].Level = 0;
			pMob[conn].Affect[sAffect].Value = 0;
		}
		else
		{
			pMob[conn].Affect[sAffect].Type = PVM_TYPE;
			pMob[conn].Affect[sAffect].Level = 2000;
			pMob[conn].Affect[sAffect].Value = 0;
		}
		
		pMob[conn].Affect[sAffect].Time = AccountSaveBuff[3];
		pMob[conn].GetCurrentScore(conn);
		SendScore(conn);
	}

}

void SaveBuff(int conn)
{
	AccountSaveBuff[0] = 0;
	AccountSaveBuff[1] = 0;
	AccountSaveBuff[2] = 0;
	AccountSaveBuff[3] = 0;
	for (int i = 0; i < MAX_AFFECT; i++)
	{
		if (pMob[conn].Affect[i].Type == SAUDE_TYPE && pMob[conn].Affect[i].Level == 1)//Saude
			AccountSaveBuff[0] = pMob[conn].Affect[i].Time;

		if (pMob[conn].Affect[i].Type == SEPHIRA_TYPE && pMob[conn].Affect[i].Value == 1)//Sephira
			AccountSaveBuff[1] = pMob[conn].Affect[i].Time;

		if (pMob[conn].Affect[i].Type == BOXEXP_TYPE && pMob[conn].Affect[i].Level == 2000)//BoxExp
			AccountSaveBuff[2] = pMob[conn].Affect[i].Time;

		if (pMob[conn].Affect[i].Type == PVM_TYPE && pMob[conn].Affect[i].Level == 2000)//PVM/Frango assado
			AccountSaveBuff[3] = pMob[conn].Affect[i].Time;

	}
}
