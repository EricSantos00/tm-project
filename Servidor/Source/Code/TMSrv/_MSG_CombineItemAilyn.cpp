#include "ProcessClientMessage.h"

void Exec_MSG_CombineItemAilyn(int conn, char *pMsg)
{
	MSG_CombineItem *m = (MSG_CombineItem*)pMsg;

	for (int i = 0; i < MAX_COMBINE; i++)
	{
		if (m->Item[i].sIndex == 0)
			continue;

		int invPos = m->InvenPos[i];

		if (invPos < 0 || invPos >= pMob[conn].MaxCarry)
		{
			RemoveTrade(conn);
			return;
		}

		if (memcmp(&pMob[conn].MOB.Carry[invPos], &m->Item[i], sizeof(STRUCT_ITEM)))
		{
			MyLog(LogType::Combines, "err,msg_CombineAilyn - item remove or changed.", pUser[conn].AccountName, 0, pUser[conn].IP);
			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
			return;
		}
	}

	if (pMob[conn].MOB.Coin < 50000000)
	{
		sprintf(temp, g_pMessageStringTable[_DN_D_Cost], 50000000);
		SendClientMsg(conn, temp);
		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
		return;
	}

	int combine = GetMatchCombineAilyn(m->Item);

	if (combine == 0)
	{
		SendClientMsg(conn, g_pMessageStringTable[_NN_Wrong_Combination]);
		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
		return;
	}

	for (int i = 2; i < MAX_COMBINE; i++)
	{
		if (m->Item[i].sIndex == 0)
			continue;

		memset(&pMob[conn].MOB.Carry[m->InvenPos[i]], 0, sizeof(STRUCT_ITEM));
		SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[i], &pMob[conn].MOB.Carry[m->InvenPos[i]]);
	}

	for (int i = 0; i < MAX_COMBINE; i++)
	{
		if (m->Item[i].sIndex)
		{
			char itemlog[2048];

			BASE_GetItemCode(&m->Item[i], itemlog);

			strcat(temp, itemlog);
		}
	}

	srand(time(NULL) / 5 * (rand() % 500) * 5);

	int _rand = rand() % 115;
	if (_rand >= 100)
		_rand -= 15;

	int zrand = rand() % 115;
	if (zrand >= 100)
		zrand -= 15;

	int ipos1 = 0;
	int ipos2 = 0;

	if (_rand <= combine || LOCALSERVER)
	{
		ipos1 = m->InvenPos[0];
		ipos2 = m->InvenPos[1];

		for (int i = 0; i < 3; i++)
		{
			if (m->Item[0].stEffect[i].cEffect == m->Item->stEffect[i].cEffect) // se o add for igual
			{
				if (m->Item[0].stEffect[i].cValue < m->Item[1].stEffect[i].cValue) // porem o valor for menor
				{
					if (zrand <= 89)
					{
						pMob[conn].MOB.Carry[ipos1].stEffect[0].cEffect = pMob[conn].MOB.Carry[ipos1].stEffect[0].cEffect;
						pMob[conn].MOB.Carry[ipos1].stEffect[0].cValue = pMob[conn].MOB.Carry[ipos1].stEffect[0].cValue;
						pMob[conn].MOB.Carry[ipos1].stEffect[1].cEffect = pMob[conn].MOB.Carry[ipos1].stEffect[1].cEffect;
						pMob[conn].MOB.Carry[ipos1].stEffect[1].cValue = pMob[conn].MOB.Carry[ipos1].stEffect[1].cValue;
						pMob[conn].MOB.Carry[ipos1].stEffect[2].cEffect = pMob[conn].MOB.Carry[ipos1].stEffect[2].cEffect;
						pMob[conn].MOB.Carry[ipos1].stEffect[2].cValue = pMob[conn].MOB.Carry[ipos1].stEffect[2].cValue;
					}

					else if (zrand >= 90 && zrand <= 100)
					{
						pMob[conn].MOB.Carry[ipos1].stEffect[0].cEffect = pMob[conn].MOB.Carry[ipos2].stEffect[0].cEffect;
						pMob[conn].MOB.Carry[ipos1].stEffect[0].cValue = pMob[conn].MOB.Carry[ipos2].stEffect[0].cValue;
						pMob[conn].MOB.Carry[ipos1].stEffect[1].cEffect = pMob[conn].MOB.Carry[ipos2].stEffect[1].cEffect;
						pMob[conn].MOB.Carry[ipos1].stEffect[1].cValue = pMob[conn].MOB.Carry[ipos2].stEffect[1].cValue;
						pMob[conn].MOB.Carry[ipos1].stEffect[2].cEffect = pMob[conn].MOB.Carry[ipos2].stEffect[2].cEffect;
						pMob[conn].MOB.Carry[ipos1].stEffect[2].cValue = pMob[conn].MOB.Carry[ipos2].stEffect[2].cValue;
					}

					break;
				}

				else
				{
					if (m->Item[1].stEffect[i].cValue < m->Item[0].stEffect[i].cValue) // porem o valor for menor
					{
						if (zrand <= 89)
						{
							pMob[conn].MOB.Carry[ipos1].stEffect[0].cEffect = pMob[conn].MOB.Carry[ipos2].stEffect[0].cEffect;
							pMob[conn].MOB.Carry[ipos1].stEffect[0].cValue = pMob[conn].MOB.Carry[ipos2].stEffect[0].cValue;
							pMob[conn].MOB.Carry[ipos1].stEffect[1].cEffect = pMob[conn].MOB.Carry[ipos2].stEffect[1].cEffect;
							pMob[conn].MOB.Carry[ipos1].stEffect[1].cValue = pMob[conn].MOB.Carry[ipos2].stEffect[1].cValue;
							pMob[conn].MOB.Carry[ipos1].stEffect[2].cEffect = pMob[conn].MOB.Carry[ipos2].stEffect[2].cEffect;
							pMob[conn].MOB.Carry[ipos1].stEffect[2].cValue = pMob[conn].MOB.Carry[ipos2].stEffect[2].cValue;
						}

						else if (zrand >= 90 && zrand <= 100)
						{
							pMob[conn].MOB.Carry[ipos1].stEffect[0].cEffect = pMob[conn].MOB.Carry[ipos1].stEffect[0].cEffect;
							pMob[conn].MOB.Carry[ipos1].stEffect[0].cValue = pMob[conn].MOB.Carry[ipos1].stEffect[0].cValue;
							pMob[conn].MOB.Carry[ipos1].stEffect[1].cEffect = pMob[conn].MOB.Carry[ipos1].stEffect[1].cEffect;
							pMob[conn].MOB.Carry[ipos1].stEffect[1].cValue = pMob[conn].MOB.Carry[ipos1].stEffect[1].cValue;
							pMob[conn].MOB.Carry[ipos1].stEffect[2].cEffect = pMob[conn].MOB.Carry[ipos1].stEffect[2].cEffect;
							pMob[conn].MOB.Carry[ipos1].stEffect[2].cValue = pMob[conn].MOB.Carry[ipos1].stEffect[2].cValue;
						}

						break;
					}
				}
			}

			if (m->Item[0].stEffect[0].cEffect == m->Item[1].stEffect[0].cEffect) // Verifica se os status do item 1 e igual ao item 2
			{
				if (m->Item[0].stEffect[0].cValue == m->Item[1].stEffect[0].cValue) // verifica e os valores do item 1 e igual ao item 2
				{
					if (m->Item[0].stEffect[1].cEffect == m->Item[1].stEffect[1].cEffect)
					{
						if (m->Item[0].stEffect[1].cValue == m->Item[1].stEffect[1].cValue)
						{
							if (m->Item[0].stEffect[2].cEffect == m->Item[1].stEffect[2].cEffect)
							{
								if (m->Item[0].stEffect[2].cValue == m->Item[1].stEffect[2].cValue)
								{
									pMob[conn].MOB.Carry[ipos1].stEffect[0].cEffect = pMob[conn].MOB.Carry[ipos2].stEffect[0].cEffect;
									pMob[conn].MOB.Carry[ipos1].stEffect[0].cValue = pMob[conn].MOB.Carry[ipos2].stEffect[0].cValue;
									pMob[conn].MOB.Carry[ipos1].stEffect[1].cEffect = pMob[conn].MOB.Carry[ipos2].stEffect[1].cEffect;
									pMob[conn].MOB.Carry[ipos1].stEffect[1].cValue = pMob[conn].MOB.Carry[ipos2].stEffect[1].cValue;
									pMob[conn].MOB.Carry[ipos1].stEffect[2].cEffect = pMob[conn].MOB.Carry[ipos2].stEffect[2].cEffect;
									pMob[conn].MOB.Carry[ipos1].stEffect[2].cValue = pMob[conn].MOB.Carry[ipos2].stEffect[2].cValue;
								} // tanto faz o id que vai pegar ambos adds serão iguais
							}
						}
					}
				}
			}

			if (m->Item[0].stEffect[i].cEffect != m->Item[1].stEffect[i].cEffect) // se o adicional for diferente, entra aqui
			{
				int randd = rand() % 100; // gera um rand de 100 numeros

				if (randd <= 50) // se o numero randomico for menor que 50 vai pegar os adds do primeiro item
				{
					pMob[conn].MOB.Carry[ipos1].stEffect[0].cEffect = pMob[conn].MOB.Carry[ipos1].stEffect[0].cEffect;
					pMob[conn].MOB.Carry[ipos1].stEffect[0].cValue = pMob[conn].MOB.Carry[ipos1].stEffect[0].cValue;
					pMob[conn].MOB.Carry[ipos1].stEffect[1].cEffect = pMob[conn].MOB.Carry[ipos1].stEffect[1].cEffect;
					pMob[conn].MOB.Carry[ipos1].stEffect[1].cValue = pMob[conn].MOB.Carry[ipos1].stEffect[1].cValue;
					pMob[conn].MOB.Carry[ipos1].stEffect[2].cEffect = pMob[conn].MOB.Carry[ipos1].stEffect[2].cEffect;
					pMob[conn].MOB.Carry[ipos1].stEffect[2].cValue = pMob[conn].MOB.Carry[ipos1].stEffect[2].cValue;

					break;
				}

				else // se for maior, vai pegar os do segundo add
				{
					pMob[conn].MOB.Carry[ipos1].stEffect[0].cEffect = pMob[conn].MOB.Carry[ipos2].stEffect[0].cEffect;
					pMob[conn].MOB.Carry[ipos1].stEffect[0].cValue = pMob[conn].MOB.Carry[ipos2].stEffect[0].cValue;
					pMob[conn].MOB.Carry[ipos1].stEffect[1].cEffect = pMob[conn].MOB.Carry[ipos2].stEffect[1].cEffect;
					pMob[conn].MOB.Carry[ipos1].stEffect[1].cValue = pMob[conn].MOB.Carry[ipos2].stEffect[1].cValue;
					pMob[conn].MOB.Carry[ipos1].stEffect[2].cEffect = pMob[conn].MOB.Carry[ipos2].stEffect[2].cEffect;
					pMob[conn].MOB.Carry[ipos1].stEffect[2].cValue = pMob[conn].MOB.Carry[ipos2].stEffect[2].cValue;

					break;
				}
			}
		}

		SendClientMsg(conn, g_pMessageStringTable[_NN_Processing_Complete]);

		BASE_SetItemSanc(&pMob[conn].MOB.Carry[ipos1], 10, m->Item[3].sIndex - 2441);

		memset(&pMob[conn].MOB.Carry[ipos2], 0, sizeof(STRUCT_ITEM));
		SendItem(conn, ITEM_PLACE_CARRY, ipos2, &pMob[conn].MOB.Carry[ipos2]);

		pMob[conn].MOB.Coin -= 50000000;
		SendEtc(conn);

		SendClientMsg(conn, g_pMessageStringTable[_NN_Processing_Complete]);

		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);

		sprintf(temp, "Ailyn: [%s] combinou com sucesso para [+10] o item [%s]", pMob[conn].MOB.MobName, g_pItemList[m->Item->sIndex].Name);
		SendNotice(temp);

		char tt[512];

		sprintf(temp, "%s ", pUser[conn].AccountName);
		BASE_GetItemCode(&pMob[conn].MOB.Carry[ipos1], tt);
		strcat(temp, tt);

		MyLog(LogType::Combines, "*** Combine ailyn sucess ***", pUser[conn].AccountName, 0, pUser[conn].IP);
		SendItem(conn, ITEM_PLACE_CARRY, ipos1, &pMob[conn].MOB.Carry[ipos1]);

		int TargetVillage = BASE_GetVillage(pMob[conn].TargetX, pMob[conn].TargetY);

		if (TargetVillage >= 0 && TargetVillage < 5)
		{
			if (GuildImpostoID[TargetVillage] >= MAX_USER && GuildImpostoID[TargetVillage] < MAX_MOB && pMob[GuildImpostoID[TargetVillage]].Mode != USER_EMPTY && pMob[GuildImpostoID[TargetVillage]].MOB.Guild == g_pGuildZone[TargetVillage].ChargeGuild)
			{
				if (pMob[GuildImpostoID[TargetVillage]].MOB.Exp < 200000000000)
					pMob[GuildImpostoID[TargetVillage]].MOB.Exp += 50000000 / 10;
			}
		}

		return;
	}
	else
	{
		sprintf(temp, "%s", g_pMessageStringTable[_NN_CombineFailed]);
		SendClientMsg(conn, temp);

		pMob[conn].MOB.Coin -= 50000000;
		SendEtc(conn);

		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 2);

		sprintf(temp, "Ailyn: [%s] falhou na combinação para [+10] do item [%s]", pMob[conn].MOB.MobName, g_pItemList[m->Item->sIndex].Name);
		SendNotice(temp);
		MyLog(LogType::Combines, "*** Combine ailyn fail ***", pUser[conn].AccountName, 0, pUser[conn].IP);

		return;
	}
}