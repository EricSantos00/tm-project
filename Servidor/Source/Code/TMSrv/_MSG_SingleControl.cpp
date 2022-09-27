#include "ProcessClientMessage.h"

void Exec_MSG_Quest(int a_iConn, char *pMsg)
{
	MSG_STANDARDPARM2 *m = (MSG_STANDARDPARM2*)pMsg;

	int npcIndex = m->Parm1;
	int confirm = m->Parm2;
	int client = m->ClientTick;

	if (npcIndex < MAX_USER || npcIndex >= MAX_MOB)
		return;

	int Merchant = pMob[npcIndex].MOB.Merchant;
	int npcGrade = pMob[npcIndex].MOB.BaseScore.Str;

	if (pUser[a_iConn].Trade.OpponentID)
	{
		RemoveTrade(pUser[a_iConn].Trade.OpponentID);
		RemoveTrade(a_iConn);
		return;
	}

	if (pUser[a_iConn].TradeMode)
	{
		SendClientMsg(a_iConn, g_pMessageStringTable[_NN_CantWhenAutoTrade]);
		return;
	}

	if (BASE_GetOnScreen(a_iConn, npcIndex) == FALSE)
		return;

	switch (Merchant)
	{
	case 74:
		NTask_Kibita(a_iConn, npcIndex); break;
	case 19:
		NTask_Skills(a_iConn, npcIndex, confirm); break;
	case 4:
		NTask_DragãoArmia(a_iConn, npcIndex); break;
	case 62:
		NTask_DragãoArzan(a_iConn, npcIndex); break;
	case 120:
		NTask_CarbuncleWind(a_iConn, npcIndex); break;
	case 10:
		NTask_CapMercenario(a_iConn, npcIndex, confirm); break;
	case 11:
		NTask_CapExpor(a_iConn, npcIndex); break;
	case 12:
		NTask_Jeffi(a_iConn, npcIndex); break;
	case 13:
		NTask_Shama(a_iConn, npcIndex); break;
	case 30:
		NTask_QuestLeakyZakum(a_iConn, npcIndex); break;
	case 8:
		NTask_QuestChefeTreina(a_iConn, npcIndex); break;
	case 78:
		NTask_BlackOracle(a_iConn, npcIndex); break;
	case 58:
		NTask_M_Montaria(a_iConn, npcIndex, confirm); break;
	case 14:
		NTask_King(a_iConn, npcIndex, confirm); break;
	case 15:
		NTask_King(a_iConn, npcIndex, confirm); break;
	case 26:
		NTask_KingdonBroker(a_iConn, npcIndex, confirm, client); break;
	case 68:
		NTask_GodGovernment(a_iConn, npcIndex); break;
	case 72:
		NTask_Uxmal(a_iConn, npcIndex); break;
	case 76:
		NTask_Urnammu(a_iConn, npcIndex); break;

	}

	if (Merchant == 100)
	{
		switch (npcGrade)
		{
		case 1:
			NTask_TrainingI(a_iConn, npcIndex); break;
		case 2:
			NTask_TrainingII(a_iConn, npcIndex); break;
		case 3:
			NTask_TrainingIII(a_iConn, npcIndex); break;
		case 11:
			NTask_QuestCapaVerde(a_iConn, npcIndex); break;
		case 13:
			NTask_LiderAprendiz(a_iConn, npcIndex); break;
		case 14:
			NTask_QuestGuardaReal(a_iConn, npcIndex); break;
		case 16:
		case 17:
		case 18:
		case 19:
			NTask_Perzens(a_iConn, npcIndex); break;
		case 21:
		case 22:
			NTask_Juli(a_iConn, npcIndex); break;
		case 33:
			NTask_QuestGuardaEventos(a_iConn, npcIndex); break;
		case 35:
			NTask_SacerdoteKruno(a_iConn, npcIndex); break;
		case 36:
			NTask_SacerdoteAmelia(a_iConn, npcIndex); break;
		
		}

	}

	if (Merchant == 42)
	{
		switch (npcGrade)
		{
			case 4:
				NTask_TrainingChief(a_iConn, npcIndex); break;
			case 5:
				NTask_QuestCoveiro(a_iConn, npcIndex); break;
			case 6:
				NTask_QuestJardineiro(a_iConn, npcIndex); break;
			case 7:
				NTask_QuestKaizen(a_iConn, npcIndex); break;
			case 8:
				NTask_QuestHidra(a_iConn, npcIndex); break;
			case 9:
				NTask_QuestElfos(a_iConn, npcIndex); break;
			case 10:
				NTask_QuestMolarGargula(a_iConn, npcIndex); break;
			case 12:
				NTask_MestreHaby(a_iConn, npcIndex, confirm); break;			
			case 37:
				NTask_SacerdoteJester(a_iConn, npcIndex); break;
			case 38:
				NTask_Sobrevivente(a_iConn, npcIndex); break;
			case 39:
				NTask_Forseti(a_iConn, npcIndex, confirm); break;
			case 40:
				NTask_GuardaHelgardh(a_iConn, npcIndex); break;
			case 41:
				NTask_Xamã(a_iConn, npcIndex, confirm); break;

			case 42:
			{
				DoTeleport(a_iConn, 2637 + rand() % 5 - 3, 2642 + rand() % 5 - 3);
				break;

			}

			case 43:
			case 44:
			case 45:
			case 46:
			case 47:
				NTask_EventTrade(a_iConn, npcIndex, npcGrade); break;
			

			
		}

	}
}