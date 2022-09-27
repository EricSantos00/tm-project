#include "EventsEternal.h"
#include <Windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>
#include <string>
#include <io.h>
#include <errno.h>
#include "..\Basedef.h"
#include "..\CPSock.h"
#include "..\ItemEffect.h"
#include "Language.h"
#include "CItem.h"
#include "Server.h"
#include "GetFunc.h"
#include "SendFunc.h"
#include "ProcessClientMessage.h"

void fVemProEternal(int ClientID)
{
	char* item1 = "Buff Exp 6hrs";
	char* item2 = "Buff frango 6hrs";
	char* item3 = "Shire 3dias";
	STRUCT_ITEM Item;
	Item.sIndex = 3980;
	Item.stEffect[0].cEffect = 0;
	Item.stEffect[0].cValue = 0;
	Item.stEffect[1].cEffect = 0;
	Item.stEffect[1].cValue = 0;
	Item.stEffect[2].cEffect = 0;
	Item.stEffect[2].cValue = 0;
	
	PutItem(ClientID, &Item);

	int sAffect = GetEmptyAffect(ClientID, 30);
	
	pMob[ClientID].Affect[sAffect].Type = 30;
	pMob[ClientID].Affect[sAffect].Level = 2000;
	pMob[ClientID].Affect[sAffect].Value = 0;
	pMob[ClientID].Affect[sAffect].Time = AFFECT_1H * 6;
	
	pMob[ClientID].GetCurrentScore(ClientID);
	SendScore(ClientID);

	sAffect = GetEmptyAffect(ClientID, 39);

	if (sAffect == -1 || (pMob[ClientID].Affect[sAffect].Level != 2000 && pMob[ClientID].Affect[sAffect].Time == 39))
	{
		SendClientMsg(ClientID, g_pMessageStringTable[_NN_CantEatMore]);
		return;
	}

	if (pMob[ClientID].Affect[sAffect].Time >= 324000 / 4)
	{
		SendClientMsg(ClientID, g_pMessageStringTable[_NN_CantEatMore]);
		return;
	}

	pMob[ClientID].Affect[sAffect].Type = 39;
	pMob[ClientID].Affect[sAffect].Level = 2000;
	pMob[ClientID].Affect[sAffect].Value = 0;
	pMob[ClientID].Affect[sAffect].Time += AFFECT_1H * 6;

	if (pMob[ClientID].Affect[sAffect].Time >= 324000 / 4)
		pMob[ClientID].Affect[sAffect].Time = 324000 / 4;

	pMob[ClientID].GetCurrentScore(ClientID);
	SendScore(ClientID);

	char temp[256];
	sprintf(temp, "!Evento Novato, você recebeu! [%s],[%s],[%s]", item1,item2,item3);
	SendClientMsg(ClientID, temp);
}
