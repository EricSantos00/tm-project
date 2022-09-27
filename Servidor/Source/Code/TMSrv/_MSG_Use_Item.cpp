#include "ProcessClientMessage.h"
#include <iostream>
#include <windows.h>
#include <windowsx.h>
#include <string>
#include <sstream>
#include "Quiz.h"
#include "ItensEntradaQuest.h"
#include "Contratos.h"
#include "Events.h"
#include "BoxPremium.h"
#include "../ConfigIni.h"
#include "GuildHall.h"
#include "TitleSystem.h"

using namespace ConfigIni;

void Exec_MSG_UseItem(int a_iConn, char *pMsg)
{
	MSG_UseItem *m = (MSG_UseItem*)pMsg;

	if (pUser[a_iConn].Mode != USER_PLAY)
	{
		SendHpMode(a_iConn);
		return;
	}

	if (pUser[a_iConn].Trade.OpponentID)
	{
		RemoveTrade(pUser[a_iConn].Trade.OpponentID);
		RemoveTrade(a_iConn);
		return;
	}

	if (pUser[a_iConn].TradeMode)
	{
		RemoveTrade(a_iConn);
		return;
	}

	if (pUser[a_iConn].IsBlocked)
	{
		SendClientMsg(a_iConn, "Sua conta está com o bloqueio ativo para essa operação.");
		return;
	}

	if (pMob[a_iConn].MOB.CurrentScore.Hp == 0)
	{
		SendHpMode(a_iConn);
		AddCrackError(a_iConn, 1, 15);

		if (m->SourType == ITEM_PLACE_CARRY)
			SendItem(a_iConn, m->SourType, m->SourPos, &pMob[a_iConn].MOB.Carry[m->SourPos]);

		else if (m->SourType == ITEM_PLACE_CARGO)
			SendItem(a_iConn, m->SourType, m->SourPos, &pUser[a_iConn].Cargo[m->SourPos]);

		else
			SendItem(a_iConn, m->SourType, m->SourPos, &pMob[a_iConn].MOB.Equip[m->SourPos]);
		return;
	}

	if (m->GridX >= MAX_GRIDX || m->GridY >= MAX_GRIDY)
	{
		CrackLog(a_iConn, " Drop grid, out of range");
		return;
	}

	STRUCT_ITEM *item = GetItemPointer(&pMob[a_iConn].MOB, pUser[a_iConn].Cargo, m->SourType, m->SourPos);

	if (item == NULL)
	{
		sprintf(temp, "err,use item fail source %d %d", m->SourType, m->SourPos);
		MyLog(LogType::Itens, "-system", temp, 0, pUser[a_iConn].IP);
		return;
	}

	int Vol = BASE_GetItemAbility(item, EF_VOLATILE);
	int amount = BASE_GetItemAmount(item);

#pragma region >> Pot HP / MP
	if (Vol == 1)
	{

		if (pMob[a_iConn].CheckSpellState[CH_SPEEL_CANCELATION])
		{
			if (amount > 1)
				BASE_SetItemAmount(item, amount - 1);
			else
				memset(item, 0, sizeof(STRUCT_ITEM));

			return;
		}

		int Hp = BASE_GetItemAbility(item, EF_HP);

		if (pUser[a_iConn].PotionTime != 0)
		{
			int isTime = GetTickCount() - pUser[a_iConn].PotionTime;

			if (isTime < PotionDelay)
			{
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				return;
			}
		}
		pUser[a_iConn].PotionTime = GetTickCount();

		if (Hp && pMob[a_iConn].MOB.CurrentScore.Hp > 0)
		{
			int CurHP = pUser[a_iConn].HP + Hp;

			if (CurHP > 2000) CurHP = 2000;

			pUser[a_iConn].HP = CurHP;
		}

		int Mp = BASE_GetItemAbility(item, EF_MP);

		if (pMob[a_iConn].MOB.CurrentScore.Hp > 0 && Mp && pMob[a_iConn].MOB.CurrentScore.Mp >= 0)
		{
			int CurMP = pUser[a_iConn].MP + Mp;

			if (CurMP > _Max_Potion_MPCasting_) CurMP = _Max_Potion_MPCasting_;

			pUser[a_iConn].MP = CurMP;
		}

		pUser[a_iConn].Unk_2688 = 1;
		//SendSetHpMp(a_iConn);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		return;
	}

#pragma endregion
#pragma region >> Poeira de Lactolerium / Oriharucon
	if (Vol == 4 || Vol == 5)
	{
		STRUCT_ITEM *dest = GetItemPointer(&pMob[a_iConn].MOB, pUser[a_iConn].Cargo, m->DestType, m->DestPos);

		if (dest == NULL)
		{
			sprintf(temp, "err,use item fail dest %d %d", m->DestType, m->DestPos);
			MyLog(LogType::Itens, "-system", temp, 0, pUser[a_iConn].IP);
			return;
		}

		//Capa Celestial
		if (dest->sIndex > 3196 && dest->sIndex < 3199)
		{
			SendClientMsg(a_iConn, "Esete item não pode ser refinado dessa forma!!");
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int Egg = 0;
		//ovos de montaria
		if (dest->sIndex >= 2300 && dest->sIndex < 2330)
			Egg = 1;

		if (m->DestType == ITEM_PLACE_CARRY && m->DestPos < pMob[a_iConn].MaxCarry)
		{
			if (dest == NULL)
			{
				SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Only_To_Equips]);
				MyLog(LogType::Itens, "use item fail - dest", 0, 0, pUser[a_iConn].IP);
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				return;
			}

			int dstVolatile = BASE_GetItemAbility(dest, EF_VOLATILE);

			if (dstVolatile)
			{
				SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Only_To_Equips]);
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				return;
			}


			int isSanc = BASE_GetItemAbility(dest, EF_NOSANC);

			if (isSanc)
			{
				SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Refine_More]);
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				return;
			}

			int sanc = BASE_GetItemSanc(dest);
			int itemtype = 0;

			if (dest->sIndex >= 1234 && dest->sIndex <= 1237 || dest->sIndex >= 1369 && dest->sIndex <= 1372 || dest->sIndex >= 1519 && dest->sIndex <= 1522 || dest->sIndex >= 1669 && dest->sIndex <= 1672 || dest->sIndex >= 1901 && dest->sIndex <= 1910 || dest->sIndex == 1714)
				itemtype = 5;

			if (sanc > 5 && Vol == 4)
			{
				SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Refine_More]);
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				return;
			}
			/*
			if(pUser[a_iConn].UseItemTime != 0)
			{
			int isTime = GetTickCount() - pUser[a_iConn].UseItemTime;

			if(isTime < 1000)
			{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			SendClientMsg(a_iConn, "Você deve esperar 1 segundo.");
			return;
			}
			}
			pUser[a_iConn].UseItemTime = GetTickCount();
			*/

#pragma region >> Refinar item Selado no inventário
			if (itemtype == 5)
			{
				if (sanc >= 9)
				{
					SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Refine_More]);
					SendItem(a_iConn, m->SourType, m->SourPos, item);
					return;
				}

				if (sanc >= 6 && Vol == 4)
				{
					SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Refine_More]);
					SendItem(a_iConn, m->SourType, m->SourPos, item);
					return;
				}

				if (sanc == 0)
				{
					if (dest->stEffect[0].cEffect && dest->stEffect[0].cEffect != 43 && (dest->stEffect[0].cEffect && dest->stEffect[0].cEffect < 116 || dest->stEffect[0].cEffect && dest->stEffect[0].cEffect > 125))
					{
						if (dest->stEffect[1].cEffect && dest->stEffect[1].cEffect != 43 && (dest->stEffect[1].cEffect && dest->stEffect[1].cEffect < 116 || dest->stEffect[1].cEffect && dest->stEffect[1].cEffect > 125))
						{
							if (dest->stEffect[2].cEffect && dest->stEffect[2].cEffect != 43 && (dest->stEffect[2].cEffect && dest->stEffect[2].cEffect < 116 || dest->stEffect[2].cEffect && dest->stEffect[2].cEffect > 125))
							{
								SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Refine_More]);
								SendItem(a_iConn, m->SourType, m->SourPos, item);
								return;
							}
							dest->stEffect[2].cEffect = 43;
							dest->stEffect[2].cValue = 0;
						}
						else
						{
							dest->stEffect[1].cEffect = 43;
							dest->stEffect[1].cValue = 0;
						}
					}
					else
					{
						dest->stEffect[0].cEffect = 43;
						dest->stEffect[0].cValue = 0;
					}
				}

				int _rd = rand() % 115;

				if (_rd > 100)
					_rd -= 15;

				int ref = sanc;

				int _chance = g_pCelestialRate[ref];

				if (_rd <= _chance)
				{
					sprintf(temp, "%s", g_pMessageStringTable[_NN_Refine_Success]);
					SendClientMsg(a_iConn, temp);

					BASE_SetItemSanc(dest, ref + 1, 0);

					pMob[a_iConn].GetCurrentScore(a_iConn);

					SendScore(a_iConn);
					sprintf(temp, "useitem,refine success %d+%d - (%d,%d,%d)", dest->sIndex, sanc, item->stEffect[0].cEffect, item->stEffect[1].cEffect, item->stEffect[2].cEffect);
					MyLog(LogType::Itens, temp, pMob[a_iConn].MOB.MobName, 0, pUser[a_iConn].IP);


					if (amount > 1)
						BASE_SetItemAmount(item, amount - 1);

					else
						memset(item, 0, sizeof(STRUCT_ITEM));


					SendItem(a_iConn, m->DestType, m->DestPos, dest);
					SendEmotion(a_iConn, 14, 3);
				}

				else
				{
					sprintf(temp, "%s", g_pMessageStringTable[_NN_Fail_To_Refine]);

					SendClientMsg(a_iConn, temp);
					sprintf(temp, "useitem,refine fail %d+%d - (%d,%d,%d)", dest->sIndex, sanc, item->stEffect[0].cEffect, item->stEffect[1].cEffect, item->stEffect[2].cEffect);
					MyLog(LogType::Itens, temp, pMob[a_iConn].MOB.MobName, 0, pUser[a_iConn].IP);

					if (amount > 1)
						BASE_SetItemAmount(item, amount - 1);

					else
						memset(item, 0, sizeof(STRUCT_ITEM));


					BASE_ClearItem(dest);
					SendItem(a_iConn, m->DestType, m->DestPos, dest);

					int sFace = pMob[a_iConn].MOB.Equip[0].sIndex / 10;

					if (sFace)
						SendEmotion(a_iConn, 15, 0);

					else
						SendEmotion(a_iConn, 20, 0);
				}

				return;
			}
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Only_To_Equips]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
#pragma endregion
		}

		if (m->DestType == ITEM_PLACE_EQUIP && m->DestPos == 0 || m->DestType || m->DestPos > 11 && m->DestPos < 15 && dest->sIndex != 753 && dest->sIndex != 769 && dest->sIndex != 1726 && dest->sIndex != 3397 && dest->sIndex != 3398 && dest->sIndex != 3399
			&& dest->sIndex != 3400 && dest->sIndex != 3401 && dest->sIndex != 3402 && dest->sIndex != 3403 && dest->sIndex != 3404 && dest->sIndex != 3405 && dest->sIndex != 3406 && !Egg)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Only_To_Equips]);

			MyLog(LogType::Itens, "err,use item fail - dest", pMob[a_iConn].MOB.MobName, 0, pUser[a_iConn].IP);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (dest == NULL)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Only_To_Equips]);
			MyLog(LogType::Itens, "err,use item fail - dest", pMob[a_iConn].MOB.MobName, 0, pUser[a_iConn].IP);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int dstVolatile = BASE_GetItemAbility(dest, EF_VOLATILE);

		if (dstVolatile)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Only_To_Equips]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int isSanc = BASE_GetItemAbility(dest, EF_NOSANC);

		if (isSanc)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Refine_More]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int sanc = BASE_GetItemSanc(dest);
		int itemtype = BASE_GetItemAbility(dest, EF_MOBTYPE);

		if (sanc >= 6 && Vol == 4)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Refine_More]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}
#pragma region >> Block PL Tinturas
		if (dest->sIndex >= 3397 && dest->sIndex <= 3406 && Vol == 5)
		{
			if (sanc >= 0)
			{
				SendClientMsg(a_iConn, "Refine com Poeira de Oriharucon.");
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				return;
			}
		}
#pragma endregion
#pragma region >> Refinar item celestial / HC
		if (itemtype == 3)
		{
			if (sanc >= REF_15)
			{
				SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Refine_More]);
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				return;
			}

			if (sanc >= 6 && Vol == 4)
			{
				SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Refine_More]);
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				return;
			}

			if (sanc == 0)
			{
				if (dest->stEffect[0].cEffect && dest->stEffect[0].cEffect != 43 && (dest->stEffect[0].cEffect && dest->stEffect[0].cEffect < 116 || dest->stEffect[0].cEffect && dest->stEffect[0].cEffect > 125))
				{
					if (dest->stEffect[1].cEffect && dest->stEffect[1].cEffect != 43 && (dest->stEffect[1].cEffect && dest->stEffect[1].cEffect < 116 || dest->stEffect[1].cEffect && dest->stEffect[1].cEffect > 125))
					{
						if (dest->stEffect[2].cEffect && dest->stEffect[2].cEffect != 43 && (dest->stEffect[2].cEffect && dest->stEffect[2].cEffect < 116 || dest->stEffect[2].cEffect && dest->stEffect[2].cEffect > 125))
						{
							SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Refine_More]);
							SendItem(a_iConn, m->SourType, m->SourPos, item);
							return;
						}
						dest->stEffect[2].cEffect = 43;
						dest->stEffect[2].cValue = 0;
					}
					else
					{
						dest->stEffect[1].cEffect = 43;
						dest->stEffect[1].cValue = 0;
					}
				}
				else
				{
					dest->stEffect[0].cEffect = 43;
					dest->stEffect[0].cValue = 0;
				}
			}

			int _rd = rand() % 115;

			if (_rd > 100)
				_rd -= 15;

			int ref = sanc;

			if (ref == REF_10)
				ref = 10;

			else if (ref == REF_11)
				ref = 11;

			else if (ref == REF_12)
				ref = 12;

			else if (ref == REF_13)
				ref = 13;

			else if (ref == REF_14)
				ref = 14;

			else if (ref == REF_15)
				ref = 15;

			int _chance = g_pCelestialRate[ref];

			if (_rd <= _chance)
			{
				sprintf(temp, "%s", g_pMessageStringTable[_NN_Refine_Success]);
				SendClientMsg(a_iConn, temp);


				BASE_SetItemSanc(dest, ref + 1, 0);

				pMob[a_iConn].GetCurrentScore(a_iConn);

				SendScore(a_iConn);
				sprintf(temp, "useitem,refine success %d+%d - (%d,%d,%d)", dest->sIndex, sanc, item->stEffect[0].cEffect, item->stEffect[1].cEffect, item->stEffect[2].cEffect);
				MyLog(LogType::Itens, temp, pMob[a_iConn].MOB.MobName, 0, pUser[a_iConn].IP);

				//SendNotice(g_pMessageStringTable[_SS_Combin_12Succ]);

				if (amount > 1)
					BASE_SetItemAmount(item, amount - 1);

				else
					memset(item, 0, sizeof(STRUCT_ITEM));


				SendItem(a_iConn, m->DestType, m->DestPos, dest);
				SendEmotion(a_iConn, 14, 3);
			}

			else
			{
				sprintf(temp, "%s", g_pMessageStringTable[_NN_Fail_To_Refine]);

				SendClientMsg(a_iConn, temp);
				sprintf(temp, "useitem,refine fail %d+%d - (%d,%d,%d)", dest->sIndex, sanc, item->stEffect[0].cEffect, item->stEffect[1].cEffect, item->stEffect[2].cEffect);
				MyLog(LogType::Itens, temp, pMob[a_iConn].MOB.MobName, 0, pUser[a_iConn].IP);


				if (amount > 1)
					BASE_SetItemAmount(item, amount - 1);

				else
					memset(item, 0, sizeof(STRUCT_ITEM));


				BASE_SetItemSanc(dest, 0, 0);
				SendItem(a_iConn, m->DestType, m->DestPos, dest);

				int sFace = pMob[a_iConn].MOB.Equip[0].sIndex / 10;

				if (sFace)
					SendEmotion(a_iConn, 15, 0);

				else
					SendEmotion(a_iConn, 20, 0);
			}

			return;
		}
#pragma endregion
#pragma region >> Pedras Arch
		if (dest->sIndex >= 1752 && dest->sIndex <= 1759)
		{
			int _rd = rand() % 115;

			if (_rd > 100)
				_rd -= 15;

			int NextPedra = 1744;
			int RateSucess = 0;

			if (dest->sIndex == 1752)//Orc Tropper
			{
				if (_rd < 56)
					NextPedra = 1744;//Inteligencia

				else if (_rd < 80)
					NextPedra = 1745;//Sabedoria

				else if (_rd < 90)
					NextPedra = 1746;//Misericórdia

				else if (_rd < 93)
					NextPedra = 1747;//Abismo

				RateSucess = 93;
			}

			else if (dest->sIndex == 1753)//Esqueleto
			{
				if (_rd < 21)
					NextPedra = 1744;//Inteligencia

				else if (_rd < 76)
					NextPedra = 1745;//Sabedoria

				else if (_rd < 86)
					NextPedra = 1746;//Misericórdia

				else if (_rd < 90)
					NextPedra = 1747;//Abismo

				RateSucess = 90;
			}

			else if (dest->sIndex == 1754)//Dragão Lich
			{
				if (_rd < 3)
					NextPedra = 1744;//Inteligencia

				else if (_rd < 21)
					NextPedra = 1745;//Sabedoria

				else if (_rd < 76)
					NextPedra = 1746;//Misericórdia

				else if (_rd < 85)
					NextPedra = 1747;//Abismo

				RateSucess = 85;
			}

			else if (dest->sIndex == 1755)//DemonLord
			{
				if (_rd < 3)
					NextPedra = 1744;//Inteligencia

				else if (_rd < 10)
					NextPedra = 1745;//Sabedoria

				else if (_rd < 25)
					NextPedra = 1746;//Misericórdia

				else if (_rd < 80)
					NextPedra = 1747;//Abismo

				RateSucess = 80;
			}

			else if (dest->sIndex == 1756)//Manticora
			{
				if (_rd < 50)
					NextPedra = 1748;//Beleza

				else if (_rd < 62)
					NextPedra = 1749;//Vitória

				else if (_rd < 68)
					NextPedra = 1750;//Originalidade

				else if (_rd < 70)
					NextPedra = 1751;//Reino

				RateSucess = 70;
			}

			else if (dest->sIndex == 1757)//Gargula de fogo
			{
				if (_rd < 9)
					NextPedra = 1748;//Beleza

				else if (_rd < 59)
					NextPedra = 1749;//Vitória

				else if (_rd < 63)
					NextPedra = 1750;//Originalidade

				else if (_rd < 65)
					NextPedra = 1751;//Reino

				RateSucess = 65;
			}

			else if (dest->sIndex == 1758)//Lugefer
			{
				if (_rd < 2)
					NextPedra = 1748;//Beleza

				else if (_rd < 8)
					NextPedra = 1749;//Vitória

				else if (_rd < 58)
					NextPedra = 1750;//Originalidade

				else if (_rd < 62)
					NextPedra = 1751;//Reino

				RateSucess = 62;
			}

			else if (dest->sIndex == 1759)//DemonLord
			{
				if (_rd < 2)
					NextPedra = 1748;//Beleza

				else if (_rd < 5)
					NextPedra = 1749;//Vitória

				else if (_rd < 10)
					NextPedra = 1750;//Originalidade

				else if (_rd < 60)
					NextPedra = 1751;//Reino

				RateSucess = 60;
			}

			if (_rd <= RateSucess)
			{
				sprintf(temp, "%s", g_pMessageStringTable[_NN_Refine_Success]);
				SendClientMsg(a_iConn, temp);

				dest->sIndex = NextPedra;

				pMob[a_iConn].GetCurrentScore(a_iConn);

				SendScore(a_iConn);
				sprintf(temp, "useitem,refine success %d+%d - (%d,%d,%d)", dest->sIndex, sanc, item->stEffect[0].cEffect, item->stEffect[1].cEffect, item->stEffect[2].cEffect);
				MyLog(LogType::Itens, temp, pMob[a_iConn].MOB.MobName, 0, pUser[a_iConn].IP);


				if (amount > 1)
					BASE_SetItemAmount(item, amount - 1);

				else
					memset(item, 0, sizeof(STRUCT_ITEM));


				SendItem(a_iConn, m->DestType, m->DestPos, dest);
				SendEmotion(a_iConn, 14, 3);
			}

			else
			{
				sprintf(temp, "%s", g_pMessageStringTable[_NN_Fail_To_Refine]);

				SendClientMsg(a_iConn, temp);
				sprintf(temp, "useitem,refine fail %d+%d - (%d,%d,%d)", dest->sIndex, sanc, item->stEffect[0].cEffect, item->stEffect[1].cEffect, item->stEffect[2].cEffect);
				MyLog(LogType::Itens, temp, pMob[a_iConn].MOB.MobName, 0, pUser[a_iConn].IP);

				if (amount > 1)
					BASE_SetItemAmount(item, amount - 1);

				else
					memset(item, 0, sizeof(STRUCT_ITEM));


				BASE_SetItemSanc(dest, 0, 0);
				SendItem(a_iConn, m->DestType, m->DestPos, dest);

				int sFace = pMob[a_iConn].MOB.Equip[0].sIndex / 10;

				if (sFace)
					SendEmotion(a_iConn, 15, 0);

				else
					SendEmotion(a_iConn, 20, 0);
			}

			return;
		}
#pragma endregion
#pragma region >> Tinturas
		if (dest->sIndex >= 3397 && dest->sIndex <= 3406 && Vol == 4)
		{
			int _rd = rand() % 115;

			if (_rd > 100)
				_rd -= 15;

			int RateSucess = 0;

			if (dest->sIndex == 3397) // Tintura Azul
			{
				if (_rd < 90)
					dest->sIndex = 3407;

				RateSucess = 100;
			}
			else if (dest->sIndex == 3398) // Tintura Vermelho
			{
				if (_rd < 90)
					dest->sIndex = 3408;
				RateSucess = 100;
			}
			else if (dest->sIndex == 3399) // Tintura Verde
			{
				if (_rd < 90)
					dest->sIndex = 3409;
				RateSucess = 100;
			}
			else if (dest->sIndex == 3400) // Tintura Prateado
			{
				if (_rd < 90)
					dest->sIndex = 3410;
				RateSucess = 100;
			}
			else if (dest->sIndex == 3401) // Tintura Preto
			{
				if (_rd < 90)
					dest->sIndex = 3411;
				RateSucess = 100;
			}
			else if (dest->sIndex == 3402) // Tintura Roxo
			{
				if (_rd < 90)
					dest->sIndex = 3412;
				RateSucess = 100;
			}
			else if (dest->sIndex == 3403) // Tintura Marrom
			{
				if (_rd < 90)
					dest->sIndex = 3413;
				RateSucess = 100;
			}
			else if (dest->sIndex == 3404) // Tintura Rosa
			{
				if (_rd < 90)
					dest->sIndex = 3414;
				RateSucess = 100;
			}
			else if (dest->sIndex == 3405) // Tintura Amrelo
			{
				if (_rd < 90)
					dest->sIndex = 3415;
				RateSucess = 100;
			}
			else if (dest->sIndex == 3406) // Tintura Azul Claro
			{
				if (_rd < 90)
					dest->sIndex = 3416;
				RateSucess = 100;
			}

			if (_rd <= RateSucess)
			{
				sprintf(temp, "%s", g_pMessageStringTable[_NN_Refine_Success]);
				SendClientMsg(a_iConn, temp);

				pMob[a_iConn].GetCurrentScore(a_iConn);
				SendScore(a_iConn);


				if (amount > 1)
					BASE_SetItemAmount(item, amount - 1);

				else
					memset(item, 0, sizeof(STRUCT_ITEM));

				SendItem(a_iConn, m->DestType, m->DestPos, dest);
				SendEmotion(a_iConn, 14, 3);
			}

			else
			{
				sprintf(temp, "%s", g_pMessageStringTable[_NN_Fail_To_Refine]);
				SendClientMsg(a_iConn, temp);

				if (amount > 1)
					BASE_SetItemAmount(item, amount - 1);

				else
					memset(item, 0, sizeof(STRUCT_ITEM));


				BASE_SetItemSanc(dest, 0, 0);
				SendItem(a_iConn, m->DestType, m->DestPos, dest);

				int sFace = pMob[a_iConn].MOB.Equip[0].sIndex / 10;

				if (sFace)
					SendEmotion(a_iConn, 15, 0);

				else
					SendEmotion(a_iConn, 20, 0);
			}

			return;
		}
#pragma endregion
#pragma region >> Refinar brincos +10+
		if (sanc >= 9 && sanc <= REF_14 && Vol == 5 && m->DestPos == 8 && g_pItemList[dest->sIndex].nPos == 256)
		{
			int RateSucess = 15;
			int _rand = rand() % 100;

			if (item->sIndex == 4141)
				RateSucess = 100;

			int ref = sanc;

			switch (ref)
			{
			case 9:
				ref = 9;
				break;
			case REF_10:
				ref = 10;
				break;
			case REF_11:
			case REF_12:
			case REF_13:
			case REF_14:
			case REF_15:
				SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Refine_More]);
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				return;
			default:
				break;
			}

			/*
			if (ref == 9)
				ref = 9;

			else if (ref == REF_10)
				ref = 10;

			else if (ref == REF_11)
				ref = 11;

			else if (ref == REF_12)
				ref = 12;

			else if (ref == REF_13)
				ref = 13;

			else if (ref == REF_14)
				ref = 14;

			else if (ref == REF_15)
				ref = 15;*/

			int _chance = RateSucess;

			if (_rand <= _chance)
			{
				sprintf(temp, "%s", g_pMessageStringTable[_NN_Refine_Success]);
				SendClientMsg(a_iConn, temp);


				BASE_SetItemSanc(dest, ref + 1, 0);

				pMob[a_iConn].GetCurrentScore(a_iConn);

				SendScore(a_iConn);
				sprintf(temp, "useitem,refine success %d+%d - (%d,%d,%d)", dest->sIndex, sanc, dest->stEffect[0].cEffect, dest->stEffect[1].cEffect, dest->stEffect[2].cEffect);
				MyLog(LogType::Itens, temp, pMob[a_iConn].MOB.MobName, 0, pUser[a_iConn].IP);

				if (amount > 1)
					BASE_SetItemAmount(item, amount - 1);

				else
					memset(item, 0, sizeof(STRUCT_ITEM));


				SendItem(a_iConn, m->DestType, m->DestPos, dest);
				SendEmotion(a_iConn, 14, 3);
			}

			else
			{
				sprintf(temp, "%s", g_pMessageStringTable[_NN_Fail_To_Refine]);

				SendClientMsg(a_iConn, temp);
				sprintf(temp, "useitem,refine fail %d+%d - (%d,%d,%d)", dest->sIndex, sanc, dest->stEffect[0].cEffect, dest->stEffect[1].cEffect, dest->stEffect[2].cEffect);
				MyLog(LogType::Itens, temp, pMob[a_iConn].MOB.MobName, 0, pUser[a_iConn].IP);


				if (amount > 1)
					BASE_SetItemAmount(item, amount - 1);

				else
					memset(item, 0, sizeof(STRUCT_ITEM));


				BASE_ClearItem(dest);
				SendItem(a_iConn, m->DestType, m->DestPos, dest);

				int sFace = pMob[a_iConn].MOB.Equip[0].sIndex / 10;

				if (sFace)
					SendEmotion(a_iConn, 15, 0);

				else
					SendEmotion(a_iConn, 20, 0);
			}
			return;
		}
#pragma endregion

		if (sanc == 9 || sanc >= REF_11 || sanc < 0 || sanc >= 9 && dest->sIndex == 769)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Refine_More]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int sancsucess = BASE_GetItemSancSuccess(dest);

		if (sanc < 0)
			sanc = 0;

		if (sanc == 0)
		{
			if (dest->stEffect[0].cEffect && dest->stEffect[0].cEffect != 43 && (dest->stEffect[0].cEffect && dest->stEffect[0].cEffect < 116 || dest->stEffect[0].cEffect && dest->stEffect[0].cEffect > 125))
			{
				if (dest->stEffect[1].cEffect && dest->stEffect[1].cEffect != 43 && (dest->stEffect[1].cEffect && dest->stEffect[1].cEffect < 116 || dest->stEffect[1].cEffect && dest->stEffect[1].cEffect > 125))
				{
					if (dest->stEffect[2].cEffect && dest->stEffect[2].cEffect != 43 && (dest->stEffect[2].cEffect && dest->stEffect[2].cEffect < 116 || dest->stEffect[2].cEffect && dest->stEffect[2].cEffect > 125))
					{
						SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Refine_More]);
						SendItem(a_iConn, m->SourType, m->SourPos, item);
						return;
					}
					dest->stEffect[2].cEffect = 43;
					dest->stEffect[2].cValue = 0;
				}
				else
				{
					dest->stEffect[1].cEffect = 43;
					dest->stEffect[1].cValue = 0;
				}
			}
			else
			{
				dest->stEffect[0].cEffect = 43;
				dest->stEffect[0].cValue = 0;
			}
		}

		if (dest->sIndex >= 2300 && dest->sIndex < 2330 && pMob[a_iConn].MOB.BaseScore.Level < 999 && BASE_GetBonusItemAbility(dest, EF_INCUDELAY) > 0)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Incu_Wait_More]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int OriLacto = Vol - 4;
		int RateSucess = item->sIndex != 4141 ? BASE_GetSuccessRate(dest, OriLacto) : BASE_GetSuccessRate(dest, 2);
		int _rand = rand() % 100;

		/*if (item->sIndex == 413)
		{
			if (sanc == 7)
				RateSucess = 20;

			else if (sanc == 8)
				RateSucess = 10;

			else if (sanc == 9)
				RateSucess = 5;

		}*/

		int ItemGrade = BASE_GetItemAbility(dest, EF_ITEMLEVEL);

		RateSucess += pMob[a_iConn].g_pFairyContent[2];

		if (_rand <= RateSucess && RateSucess)
		{
			if (sanc == REF_10)
				BASE_SetItemSanc(dest, 11, BASE_GetItemGem(dest));

			else
			{
				if (ItemGrade >= 1 && ItemGrade <= 5)
				{
					ItemGrade--;
					sanc += g_pSancGrade[OriLacto][ItemGrade];


					if (sanc >= 6 && Vol == 4)
						sanc = 6;

					else if (sanc > 9)
						sanc = 9;
				}
				else
					sanc++;


				sancsucess = 0;

				BASE_SetItemSanc(dest, sanc, 0);
			}

			pMob[a_iConn].GetCurrentScore(a_iConn);
			SendScore(a_iConn);

			sprintf(temp, "useitem,refine success %d+%d - (%d,%d,%d)", dest->sIndex, sanc, dest->stEffect[0].cEffect, dest->stEffect[1].cEffect, dest->stEffect[2].cEffect);
			MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);

			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Refine_Success]);

			/*if (sanc == 7)
			{
				sprintf(temp, "[%s] obteve sucesso ao refinar o item [%s] para +7. ", pMob[a_iConn].MOB.MobName, g_pItemList[dest->sIndex].Name);
				SendNotice(temp);
				pMob[a_iConn].GetCurrentScore(0);
				SendScore(a_iConn);
			}*/

			switch (sanc)
			{
			//case 7:
			//case 8:
			case 9:
			case REF_11:
				sprintf(temp, "[%s] obteve sucesso ao refinar o item [%s] para [+%d]. ", pMob[a_iConn].MOB.MobName, g_pItemList[dest->sIndex].Name, sanc);
				SendNotice(temp);
				pMob[a_iConn].GetCurrentScore(0);
				SendScore(a_iConn);
				break;
			default:
				break;
			}

			if (dest->sIndex >= 2300 && dest->sIndex < 2330)
			{
				dest->stEffect[2].cEffect = 84;

				int incurand = rand() & 0x80000003;

				if (incurand < 0)
					incurand = ((incurand - 1) | 0xFC) + 1;

				dest->stEffect[2].cValue = incurand + 6;

				int incubate = BASE_GetBonusItemAbility(dest, EF_INCUBATE);

				STRUCT_ITEM *Mount = &pMob[a_iConn].MOB.Equip[14];

				if (sanc >= incubate)
				{
					dest->sIndex += 30;

					dest->stEffect[0].sValue = 20000;
					dest->stEffect[1].cEffect = 1;
					dest->stEffect[1].cValue = rand() % 20 + 10;
					dest->stEffect[2].cEffect = 30;
					dest->stEffect[2].cValue = 1;

					SendClientMsg(a_iConn, g_pMessageStringTable[_NN_INCUBATED]);
					MountProcess(a_iConn, Mount); // Correção para quando terminar de incubar aparecer a cria

					SendItem(a_iConn, m->DestType, m->DestPos, dest);
				}
			}
			SendItem(a_iConn, m->DestType, m->DestPos, dest);
			SendEmotion(a_iConn, 14, 3);

			if (amount > 1)
				BASE_SetItemAmount(item, amount - 1);

			else
				memset(item, 0, sizeof(STRUCT_ITEM));
		}

		else
		{

			if (amount > 1)
				BASE_SetItemAmount(item, amount - 1);

			else
				memset(item, 0, sizeof(STRUCT_ITEM));

			//static const int uncontinue[] = { 8, 9, 10, 11, 12, 13, 14, 15, 16 };
			//for (int i = 0; i < 10; i++)
			//{
			//	if (sanc == 6 /*&& BASE_GetItemAbility(dest, EF_ITEMLEVEL) >= 4 */ && m->DestPos != uncontinue[i]
			//		&& dest->sIndex != 3502)
			//	{
			//		int randoly = rand() % 100 + 1;

			//		if (randoly < 20)
			//		{
			//			BASE_ClearItem(dest);
			//			sprintf(temp, "Refinação falhou, seu item foi destruído. ");
			//			SendNotice(temp);
			//			pMob[a_iConn].GetCurrentScore(0);
			//			SendScore(a_iConn);
			//		}

			//		else if (randoly < 40)
			//		{
			//			SendClientMsg(a_iConn, "Refinação falhou, a refinação do item foi diminuida.");
			//			pMob[a_iConn].GetCurrentScore(0);
			//			BASE_SetItemSanc(dest, 5, 0);
			//			SendScore(a_iConn);
			//		}

			//		else
			//		{
			//			sprintf(temp, "%s", g_pMessageStringTable[_NN_Fail_To_Refine]);
			//			SendClientMsg(a_iConn, temp);
			//		}

			//		SendItem(a_iConn, m->DestType, m->DestPos, dest);
			//		return;
			//	}
			//}

			if (rand() % 4 <= 2)
			{
				if (OriLacto == 1)
					++sancsucess;

				else if (sanc <= 5 && !OriLacto)
					++sancsucess;
			}
			if (dest->sIndex >= 2300 && dest->sIndex < 2330)
			{
				dest->stEffect[2].cEffect = 84;

				int incu = rand() & 0x80000003;
				if (incu < 0)
					incu = ((incu - 1) | 0xFC) + 1;

				dest->stEffect[2].cValue = incu;
			}

			if (sanc != REF_10)
				BASE_SetItemSanc(dest, sanc, sancsucess);

			SendItem(a_iConn, m->DestType, m->DestPos, dest);

			int sFace = pMob[a_iConn].MOB.Equip[0].sIndex / 10;

			if (sFace)
				SendEmotion(a_iConn, 15, 0);

			else
				SendEmotion(a_iConn, 20, 0);

			sprintf(temp, "%s", g_pMessageStringTable[_NN_Fail_To_Refine]);

			SendClientMsg(a_iConn, temp);
			sprintf(temp, "useitem,refine fail %d+%d - (%d,%d,%d)", dest->sIndex, sanc, dest->stEffect[0].cEffect, dest->stEffect[1].cEffect, dest->stEffect[2].cEffect);
			MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);
		}

		return;
	}

#pragma endregion
#pragma region >> Pilula do Poder Mágico
	if (Vol == 6)
	{
		if (pMob[a_iConn].Extra.QuestInfo.Mortal.PilulaOrc)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		pMob[a_iConn].MOB.SkillBonus += 9;
		pMob[a_iConn].Extra.QuestInfo.Mortal.PilulaOrc = 1;
		SendEmotion(a_iConn, 14, 3);
		SendEtc(a_iConn);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);
		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		sprintf(temp, "useitem, Pilula do Poder Mágico quest complete.");
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);
		return;
	}
#pragma endregion
#pragma region >> Olho Crescente
	if (Vol == 8)
	{
		if (pMob[a_iConn].Extra.ClassMaster != MORTAL)
			return;

		pMob[a_iConn].MOB.Exp += 2500;

		sprintf(temp, g_pMessageStringTable[_NS_GETEXP], 2500);
		SendClientMsg(a_iConn, temp);

		SendEmotion(a_iConn, 14, 3);

		if (pMob[a_iConn].CheckGetLevel() == 4)
		{
			SetCircletSubGod(a_iConn);
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Level_Up]);
			SendScore(a_iConn);
			TitleNotification(a_iConn, pMob[a_iConn].MOB.CurrentScore.Level);

			if (pMob[a_iConn].Extra.ClassMaster == MORTAL)
				DoItemLevel(a_iConn);
		}

		SendEtc(a_iConn);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		sprintf(temp, "useitem,olho_crescente level:%d exp recebida:2500", pMob[a_iConn].MOB.BaseScore.Level);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);
		return;
	}
#pragma endregion
#pragma region >> Spinner/Beril/Tectita/Adamantita
	if (Vol == 9)
	{
		STRUCT_ITEM *dest = GetItemPointer(&pMob[a_iConn].MOB, pUser[a_iConn].Cargo, m->DestType, m->DestPos);

		if (dest == NULL)
		{
			sprintf(temp, "err,use item fail dest %d %d", m->DestType, m->DestPos);
			MyLog(LogType::Itens, "-system", temp, 0, pUser[a_iConn].IP);
			return;
		}

		int sourIndex = item->sIndex;
		int destIndex = dest->sIndex;
		int Type = sourIndex - 575;

		if (sourIndex - 575 >= 0 && Type < 4)
		{
			int UniqueType = -1;
			int nUnique = g_pItemList[destIndex].nUnique;

			if (nUnique == 5 || nUnique == 14 || nUnique == 24 || nUnique == 34)
				UniqueType = 0;

			if (nUnique == 6 || nUnique == 15 || nUnique == 25 || nUnique == 35)
				UniqueType = 1;

			if (nUnique == 7 || nUnique == 16 || nUnique == 26 || nUnique == 36)
				UniqueType = 2;

			if (nUnique == 8 || nUnique == 17 || nUnique == 27 || nUnique == 37)
				UniqueType = 3;

			if (nUnique == 10 || nUnique == 20 || nUnique == 30 || nUnique == 40)
				UniqueType = 3;

			if (nUnique == -1)
			{
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				SendClientMsg(a_iConn, g_pMessageStringTable[Type + _NN_Only_Level1_Armor]);
			}
			else
			{
				if (UniqueType == Type)
				{
					int Grade = g_pItemList[destIndex].Grade;

					if (Grade > 0 && Grade < 4)
					{
						int _rand = rand() % 100;
						int chance = 50;
						if (_rand <= 50)
						{
							int Extra = g_pItemList[destIndex].Extra;

							dest->sIndex = Extra;

							SendItem(a_iConn, m->DestType, m->DestPos, dest);

							if (amount > 1)
								BASE_SetItemAmount(item, amount - 1);

							else
								memset(item, 0, sizeof(STRUCT_ITEM));

							SendScore(a_iConn);
							SendEmotion(a_iConn, 14, 0);

							sprintf(temp, "useitem,regendary success %d - (%d,%d,%d)", dest->sIndex,
								item->stEffect[0].cEffect, item->stEffect[1].cEffect, item->stEffect[2].cEffect);

							MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);

							sprintf(temp, "%s(%d/%d)", g_pMessageStringTable[_NN_Refine_Success], _rand, chance);

							SendClientMsg(a_iConn, temp);
						}
						else
						{
							if (pMob[a_iConn].MOB.Equip[0].sIndex / 10)
								SendEmotion(a_iConn, 15, 0);

							else
								SendEmotion(a_iConn, 20, 0);

							sprintf(temp, "useitem,regendary fail %d - (%d,%d,%d)",
								dest->sIndex, item->stEffect[0].cEffect, item->stEffect[1].cEffect, item->stEffect[2].cEffect);

							MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);

							sprintf(temp, "%s(%d/%d)", g_pMessageStringTable[_NN_Fail_To_Refine], _rand, chance);
							SendClientMsg(a_iConn, temp);

							if (amount > 1)
								BASE_SetItemAmount(item, amount - 1);

							else
								memset(item, 0, sizeof(STRUCT_ITEM));
						}
					}
					else
					{
						SendItem(a_iConn, m->SourType, m->SourPos, item);
						SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Refine_More]);
					}
				}
				else
				{
					SendItem(a_iConn, m->SourType, m->SourPos, item);
					SendClientMsg(a_iConn, g_pMessageStringTable[Type + _NN_Only_Level1_Armor]);
				}
			}
		}
		else
			SendItem(a_iConn, m->SourType, m->SourPos, item);
		return;
	}
#pragma endregion
#pragma region >> Pergaminho do Retorno
	if (Vol == 11)
	{
		DoRecall(a_iConn);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		MyLog(LogType::Itens, "%s useitem,recall", pMob[a_iConn].MOB.MobName, 0, pUser[a_iConn].IP);
		return;
	}
#pragma endregion
#pragma region >> Pergaminho do Portal
	if (Vol == 13)
	{
		if ((pMob[a_iConn].MOB.SPX / 128) == 9 && (pMob[a_iConn].MOB.SPY / 128) == 1 || (pMob[a_iConn].MOB.SPX / 128) == 8 && (pMob[a_iConn].MOB.SPY / 128) == 2)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Use_That_Here]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		unsigned char map_att = GetAttribute(pMob[a_iConn].TargetX, pMob[a_iConn].TargetY);

		if (map_att & 4 && pMob[a_iConn].MOB.CurrentScore.Level < 1000)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Use_That_Here]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		DoTeleport(a_iConn, pMob[a_iConn].MOB.SPX, pMob[a_iConn].MOB.SPY);

		sprintf(temp, "useitem,teleport portal scrool %d %d", pMob[a_iConn].TargetX, pMob[a_iConn].TargetY);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		return;
	}
#pragma endregion
#pragma region >> Pedidos de caça
	if (Vol == 195)
	{
		std::vector<short> nItens = {3432,3433,3434,3435,3436,3437};
		int itemValido = FALSE;
		for (size_t i = 0; i < 6; i++)
		{
			if (item->sIndex == nItens[i])
			{
				itemValido = TRUE;
			}
		}
		if (!itemValido)
		{
			return;
		}
		//if (item->sIndex < 3432 || item->sIndex > 3437)
		//	return;


		if (m->WarpID <= 0 || m->WarpID > 10)
			return;

		DoTeleport(a_iConn, HuntingScrolls[item->sIndex - 3432][m->WarpID - 1][0], HuntingScrolls[item->sIndex - 3432][m->WarpID - 1][1]);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		sprintf(temp, "useitem,huntingscrolls itemindex:%d warpid:%d tx:%d ty:%d", item->sIndex, m->WarpID, HuntingScrolls[item->sIndex - 3432][m->WarpID - 1][0], HuntingScrolls[item->sIndex - 3432][m->WarpID - 1][1]);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);
		return;
	}
#pragma endregion

#pragma region >> Entrada do Território
	if (Vol == 188)
	{
		if (pMob[a_iConn].QuizError >= MAX_QUIZ_ERROR)
		{
			sprintf(temp, "Errou [%d] de [%d] tentativas", pMob[a_iConn].QuizError, MAX_QUIZ_ERROR);
			SendMsgExp(a_iConn, temp, TNColor::CornBlueName, false);
			SendClientMsg(a_iConn, "Digite o Comando /ResetLan para tentar novamente");
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}
		int territorio = item->sIndex - 4111;

	
				//N
			if (territorio == 0 && pMob[a_iConn].Extra.ClassMaster != MORTAL)
			{
				SendClientMsg(a_iConn, "Somente para Mortais.");
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				return;
			}
			
				//M
			if (territorio == 1 && pMob[a_iConn].Extra.ClassMaster != ARCH)
			{
				SendClientMsg(a_iConn, "Somente para Archs.");
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				return;
			}
			
				//A
			if (territorio == 2 && pMob[a_iConn].Extra.ClassMaster != CELESTIAL)
			{
				SendClientMsg(a_iConn, "Somente para Celestiais.");
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				return;
			}
		
		
			quizTerritory(a_iConn, item->sIndex, territorio);
		
		sprintf(temp, "useitem,territorio ticket used %d", territorio);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		return;
	}
#pragma endregion

#pragma >> Moedas Eternal Points
	if (Vol == 189)
	{
		int idItem = item->sIndex - 3016;
		int TotalEp = 0;
		switch (idItem)
		{
		case 0://Moeda de Bronze 1.Ep
			TotalEp = 1;
			break;
		case 1://Moeda de Prata 5.Ep
			TotalEp = 5;
			break;
		case 2://Moeda de Ouro 10.Ep
			TotalEp = 10;
			break;
		case 3://Moeda de Ouro 20.Ep
			TotalEp = 20;
			break;
		default:
			break;
		}
		int DonateAtual = pUser[a_iConn].Donate;
		if (TotalEp > 0)
		{
			DonateAtual += TotalEp;
			if (DonateAtual > MAX_DONATE)
			{
				sprintf(temp, "Limite máximo de Epoints atingido");
				SendMsgExp(a_iConn, temp, TNColor::CornBlueName, false);
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				return;
			}
			
				pUser[a_iConn].Donate += TotalEp;
				sprintf(temp, "Você recebeu [%d] de [%s]", TotalEp, "EPoints");
				SendMsgExp(a_iConn, temp, TNColor::GreenYellow, false);

				memset(item, 0, sizeof(STRUCT_ITEM));
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				return;
			
		}
	}
#pragma endregion
#pragma region Pergaminho da Água N
	if (Vol >= 131 && Vol <= 140)
	{
		int TargetX = pMob[a_iConn].TargetX;
		int TargetY = pMob[a_iConn].TargetY;

		int inside = 0;


		for (int i = 0; i < 10; i++)
		{
			if (TargetX >= WaterScrollPosition[0][i][0] - 12 && TargetY >= WaterScrollPosition[0][i][1] - 12
				&& TargetX <= WaterScrollPosition[0][i][0] + 12 && TargetY <= WaterScrollPosition[0][i][1] + 12 && i >= 9)
			{
				inside = 1;
				break;
			}

			if (TargetX >= WaterScrollPosition[0][i][0] - 8 && TargetY >= WaterScrollPosition[0][i][1] - 8
				&& TargetX <= WaterScrollPosition[0][i][0] + 8 && TargetY <= WaterScrollPosition[0][i][1] + 8)
			{
				inside = 1;
				break;
			}
		}

		if (((TargetX / 4) != 491 || (TargetY / 4) != 443 || Vol == 139) && inside == 0)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Use_That_Here]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].Leader != -1 && pMob[a_iConn].Leader)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Party_Leader_Only]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		char UserName[128];

		int Sala = Vol - 131;
		int UserArea = Sala <= 7 ? GetUserInArea(WaterScrollPosition[0][Vol - 131][0] - 8, WaterScrollPosition[0][Vol - 131][1] - 8, WaterScrollPosition[0][Vol - 131][0] + 8, WaterScrollPosition[0][Vol - 131][1] + 8, UserName) : GetUserInArea(WaterScrollPosition[0][Vol - 131][0] - 12, WaterScrollPosition[0][Vol - 131][1] - 12, WaterScrollPosition[0][Vol - 131][0] + 12, WaterScrollPosition[0][Vol - 131][1] + 12, UserName);

		if (UserArea >= 1)
		{
			sprintf(temp, g_pMessageStringTable[_NN_Someone_is_on_quest], UserName, UserArea - 1);

			SendClientMsg(a_iConn, temp);
			SendItem(a_iConn, m->SourType, m->SourPos, item);

			return;
		}

		WaterClear1[0][Vol - 131] = Sala <= 7 ? 30 : 15;

		DoTeleport(a_iConn, WaterScrollPosition[0][Vol - 131][0], WaterScrollPosition[0][Vol - 131][1]);
		SendClientSignalParm(a_iConn, ESCENE_FIELD, _MSG_StartTime, WaterClear1[0][Vol - 131] * 2);

		for (int i = 0; i < MAX_PARTY; i++)
		{
			int partyconn = pMob[a_iConn].PartyList[i];

			if (partyconn > 0 && partyconn < MAX_USER && partyconn != a_iConn && pUser[partyconn].Mode == USER_PLAY)
			{
				if (pMob[partyconn].Extra.ClassMaster == ARCH) continue;

				DoTeleport(partyconn, WaterScrollPosition[0][Vol - 131][0], WaterScrollPosition[0][Vol - 131][1]);
				SendClientSignalParm(partyconn, ESCENE_FIELD, _MSG_StartTime, WaterClear1[0][Vol - 131] * 2);
			}
		}

		if (Sala <= 7)
		{
			GenerateMob(Sala + WATER_N_INITIAL, 0, 0);
			GenerateMob(Sala + WATER_N_INITIAL, 0, 0);
			//RebuildGenerator();
		}
		else if (Sala == 9)
		{
			int _rand = rand() % 10;

			if (_rand < 4)
				GenerateMob(WATER_N_INITIAL + 8, 0, 0);

			else if (_rand < 5)
				GenerateMob(WATER_N_INITIAL + 9, 0, 0);

			else if (_rand < 6)
				GenerateMob(WATER_N_INITIAL + 10, 0, 0);

			else
				GenerateMob(WATER_N_INITIAL + 11, 0, 0);
		}

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		return;
	}
#pragma endregion
#pragma region Pergaminho da Água M
	if (Vol >= 21 && Vol <= 30)
	{
		int TargetX = pMob[a_iConn].TargetX;
		int TargetY = pMob[a_iConn].TargetY;

		int inside = 0;

		for (int i = 0; i < 10; i++)
		{
			if (TargetX >= WaterScrollPosition[1][i][0] - 12 && TargetY >= WaterScrollPosition[1][i][1] - 12
				&& TargetX <= WaterScrollPosition[1][i][0] + 12 && TargetY <= WaterScrollPosition[1][i][1] + 12 && i >= 9)
			{
				inside = 1;
				break;
			}

			if (TargetX >= WaterScrollPosition[1][i][0] - 8 && TargetY >= WaterScrollPosition[1][i][1] - 8
				&& TargetX <= WaterScrollPosition[1][i][0] + 8 && TargetY <= WaterScrollPosition[1][i][1] + 8)
			{
				inside = 1;
				break;
			}
		}

		if (((TargetX / 4) != 491 || (TargetY / 4) != 443 || Vol == 29) && inside == 0)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Use_That_Here]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].Leader != -1 && pMob[a_iConn].Leader)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Party_Leader_Only]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		char UserName[128];

		int Sala = Vol - 21;
		int UserArea = Sala <= 7 ? GetUserInArea(WaterScrollPosition[1][Vol - 21][0] - 8, WaterScrollPosition[1][Vol - 21][1] - 8, WaterScrollPosition[1][Vol - 21][0] + 8, WaterScrollPosition[1][Vol - 21][1] + 8, UserName) : GetUserInArea(WaterScrollPosition[1][Vol - 21][0] - 12, WaterScrollPosition[1][Vol - 21][1] - 12, WaterScrollPosition[1][Vol - 21][0] + 12, WaterScrollPosition[1][Vol - 21][1] + 12, UserName);

		if (UserArea >= 1)
		{
			sprintf(temp, g_pMessageStringTable[_NN_Someone_is_on_quest], UserName, UserArea - 1);

			SendClientMsg(a_iConn, temp);
			SendItem(a_iConn, m->SourType, m->SourPos, item);

			return;
		}

		WaterClear1[1][Vol - 21] = Sala <= 7 ? 30 : 15;

		DoTeleport(a_iConn, WaterScrollPosition[1][Vol - 21][0], WaterScrollPosition[1][Vol - 21][1]);
		SendClientSignalParm(a_iConn, ESCENE_FIELD, _MSG_StartTime, WaterClear1[1][Vol - 21] * 2);

		for (int i = 0; i < MAX_PARTY; i++)
		{
			int partyconn = pMob[a_iConn].PartyList[i];

			if (partyconn > 0 && partyconn < MAX_USER && partyconn != a_iConn && pUser[partyconn].Mode == USER_PLAY)
			{
				DoTeleport(partyconn, WaterScrollPosition[1][Vol - 21][0], WaterScrollPosition[1][Vol - 21][1]);
				SendClientSignalParm(partyconn, ESCENE_FIELD, _MSG_StartTime, WaterClear1[1][Vol - 21] * 2);
			}
		}

		if (Sala <= 7)
		{
			GenerateMob(Sala + WATER_M_INITIAL, 0, 0);
			GenerateMob(Sala + WATER_M_INITIAL, 0, 0);
			RebuildGenerator();
		}
		else if (Sala == 9)
		{
			int _rand = rand() % 10;

			if (_rand < 4)
				GenerateMob(WATER_M_INITIAL + 8, 0, 0);

			else if (_rand < 5)
				GenerateMob(WATER_M_INITIAL + 9, 0, 0);

			else if (_rand < 6)
				GenerateMob(WATER_M_INITIAL + 10, 0, 0);

			else
				GenerateMob(WATER_M_INITIAL + 11, 0, 0);
		}

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		return;
	}
#pragma endregion
#pragma region Pergaminho da Água A
	if (Vol >= 161 && Vol <= 170)
	{
		int TargetX = pMob[a_iConn].TargetX;
		int TargetY = pMob[a_iConn].TargetY;

		int inside = 0;

		for (int i = 0; i < 10; i++)
		{
			if (TargetX >= WaterScrollPosition[2][i][0] - 12 && TargetY >= WaterScrollPosition[2][i][1] - 12
				&& TargetX <= WaterScrollPosition[2][i][0] + 12 && TargetY <= WaterScrollPosition[2][i][1] + 12 && i >= 9)
			{
				inside = 1;
				break;
			}

			if (TargetX >= WaterScrollPosition[2][i][0] - 8 && TargetY >= WaterScrollPosition[2][i][1] - 8
				&& TargetX <= WaterScrollPosition[2][i][0] + 8 && TargetY <= WaterScrollPosition[2][i][1] + 8)
			{
				inside = 1;
				break;
			}
		}

		if (((TargetX / 4) != 491 || (TargetY / 4) != 443 || Vol == 169) && inside == 0)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Use_That_Here]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].Leader != -1 && pMob[a_iConn].Leader)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Party_Leader_Only]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		char UserName[128];

		int Sala = Vol - 161;
		int UserArea = Sala <= 7 ? GetUserInArea(WaterScrollPosition[2][Vol - 161][0] - 8, WaterScrollPosition[2][Vol - 161][1] - 8, WaterScrollPosition[2][Vol - 161][0] + 8, WaterScrollPosition[2][Vol - 161][1] + 8, UserName) : GetUserInArea(WaterScrollPosition[2][Vol - 161][0] - 12, WaterScrollPosition[2][Vol - 161][1] - 12, WaterScrollPosition[2][Vol - 161][0] + 12, WaterScrollPosition[2][Vol - 161][1] + 12, UserName);

		if (UserArea >= 1)
		{
			sprintf(temp, g_pMessageStringTable[_NN_Someone_is_on_quest], UserName, UserArea - 1);

			SendClientMsg(a_iConn, temp);
			SendItem(a_iConn, m->SourType, m->SourPos, item);

			return;
		}

		WaterClear1[2][Vol - 161] = Sala <= 7 ? 30 : 15;

		DoTeleport(a_iConn, WaterScrollPosition[2][Vol - 161][0], WaterScrollPosition[2][Vol - 161][1]);
		SendClientSignalParm(a_iConn, ESCENE_FIELD, _MSG_StartTime, WaterClear1[2][Vol - 161] * 2);

		for (int i = 0; i < MAX_PARTY; i++)
		{
			int partyconn = pMob[a_iConn].PartyList[i];

			if (partyconn > 0 && partyconn < MAX_USER && partyconn != a_iConn && pUser[partyconn].Mode == USER_PLAY)
			{
				DoTeleport(partyconn, WaterScrollPosition[2][Vol - 161][0], WaterScrollPosition[2][Vol - 161][1]);
				SendClientSignalParm(partyconn, ESCENE_FIELD, _MSG_StartTime, WaterClear1[2][Vol - 161] * 2);
			}
		}

		if (Sala <= 7)
		{
			GenerateMob(Sala + WATER_A_INITIAL, 0, 0);
			GenerateMob(Sala + WATER_A_INITIAL, 0, 0);
			//RebuildGenerator();
		}
		else if (Sala == 9)
		{
			int _rand = rand() % 10;

			if (_rand < 4)
				GenerateMob(WATER_A_INITIAL + 8, 0, 0);

			else if (_rand < 5)
				GenerateMob(WATER_A_INITIAL + 9, 0, 0);

			else if (_rand < 6)
				GenerateMob(WATER_A_INITIAL + 10, 0, 0);

			else
				GenerateMob(WATER_A_INITIAL + 11, 0, 0);
		}

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		return;
	}
#pragma endregion
#pragma region Pesadelo N
	if (Vol == 173)
	{
		int TargetX = pMob[a_iConn].TargetX;
		int TargetY = pMob[a_iConn].TargetY;

		if ((TargetX / 128) != 19 || (TargetY / 128) != 15)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Use_That_Here]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].Leader != -1 && pMob[a_iConn].Leader)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Party_Leader_Only]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}
		if ((pMob[a_iConn].Extra.ClassMaster == CELESTIAL || pMob[a_iConn].Extra.ClassMaster == CELESTIALCS || pMob[a_iConn].Extra.ClassMaster == SCELESTIAL) && pMob[a_iConn].MOB.CurrentScore.Level >= 180)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);

			return;
		}

		struct tm when;
		time_t now;
		time(&now);
		when = *localtime(&now);

		if (when.tm_min >= 4 && when.tm_min <= 19 || when.tm_min >= 24 && when.tm_min <= 39
			|| when.tm_min >= 44 && when.tm_min <= 59)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);

			return;
		}

		int isParty = item->sIndex == 3324 ? 1 : 0;

		if (isParty == 0)
			goto lbl_n_noparty;

		if (PartyPesa[0] >= maxNightmare)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Night_Limited]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);

			return;
		}
		PartyPesa[0]++;

	lbl_n_noparty:
		int NigthTime = 240;

		if (when.tm_min >= 20 && when.tm_min <= 23)
			NigthTime -= ((when.tm_min - 20) * 60) + when.tm_sec;

		else if (when.tm_min >= 40 && when.tm_min <= 43)
			NigthTime -= ((when.tm_min - 40) * 60) + when.tm_sec;

		else if (when.tm_min >= 0 && when.tm_min <= 3)
			NigthTime -= (when.tm_min * 60) + when.tm_sec;


		DoTeleport(a_iConn, PesaNPosStandard[0][0], PesaNPosStandard[0][1]);
		SendClientSignalParm(a_iConn, ESCENE_FIELD, _MSG_StartTime, NigthTime);

		for (int i = 0; i < MAX_PARTY && isParty == 1; i++)
		{
			int partyconn = pMob[a_iConn].PartyList[i];

			if ((pMob[partyconn].Extra.ClassMaster == CELESTIAL || pMob[partyconn].Extra.ClassMaster == CELESTIALCS || pMob[partyconn].Extra.ClassMaster == SCELESTIAL) && pMob[partyconn].MOB.CurrentScore.Level >= 180)
				continue;

			if (partyconn > 0 && partyconn < MAX_USER && partyconn != a_iConn && pUser[partyconn].Mode == USER_PLAY)
			{
				DoTeleport(partyconn, PesaNPosStandard[i][0], PesaNPosStandard[i][1]);
				SendClientSignalParm(partyconn, ESCENE_FIELD, _MSG_StartTime, NigthTime);
			}
		}

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		return;
	}
#pragma endregion
#pragma region Pesadelo M
	if (Vol == 174)
	{
		int TargetX = pMob[a_iConn].TargetX;
		int TargetY = pMob[a_iConn].TargetY;

		if ((TargetX / 128) != 16 || (TargetY / 128) != 16)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Use_That_Here]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].Leader != -1 && pMob[a_iConn].Leader)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Party_Leader_Only]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}
		if ((pMob[a_iConn].Extra.ClassMaster == CELESTIAL || pMob[a_iConn].Extra.ClassMaster == CELESTIALCS || pMob[a_iConn].Extra.ClassMaster == SCELESTIAL) && pMob[a_iConn].MOB.CurrentScore.Level >= 180)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);

			return;
		}

		struct tm when;
		time_t now;
		time(&now);
		when = *localtime(&now);

		if (when.tm_min >= 0 && when.tm_min <= 4 || when.tm_min >= 9 && when.tm_min <= 24
			|| when.tm_min >= 29 && when.tm_min <= 44 || when.tm_min >= 49 && when.tm_min <= 59)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);

			return;
		}
		int isParty = item->sIndex == 3325 ? 1 : 0;

		if (isParty == 0)
			goto lbl_m_noparty;

		if (PartyPesa[1] >= maxNightmare)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Night_Limited]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);

			return;
		}
		PartyPesa[1]++;

	lbl_m_noparty:
		int NigthTime = 240;

		if (when.tm_min >= 5 && when.tm_min <= 8)
			NigthTime -= ((when.tm_min - 5) * 60) + when.tm_sec;

		else if (when.tm_min >= 25 && when.tm_min <= 28)
			NigthTime -= ((when.tm_min - 25) * 60) + when.tm_sec;

		else if (when.tm_min >= 45 && when.tm_min <= 48)
			NigthTime -= ((when.tm_min - 45) * 60) + when.tm_sec;

		if ((pMob[a_iConn].MOB.SPX / 128) == 8 && (pMob[a_iConn].MOB.SPY / 128) == 2)
			DoTeleport(a_iConn, pMob[a_iConn].MOB.SPX, pMob[a_iConn].MOB.SPY);
		else
			DoTeleport(a_iConn, PesaMPosStandard[0][0], PesaMPosStandard[0][1]);

		SendClientSignalParm(a_iConn, ESCENE_FIELD, _MSG_StartTime, NigthTime);

		for (int i = 0; i < MAX_PARTY && isParty == 1; i++)
		{
			int partyconn = pMob[a_iConn].PartyList[i];

			if ((pMob[partyconn].Extra.ClassMaster == CELESTIAL || pMob[partyconn].Extra.ClassMaster == CELESTIALCS || pMob[partyconn].Extra.ClassMaster == SCELESTIAL) && pMob[partyconn].MOB.CurrentScore.Level >= 180)
				continue;

			if (partyconn > 0 && partyconn < MAX_USER && partyconn != a_iConn && pUser[partyconn].Mode == USER_PLAY)
			{
				if ((pMob[partyconn].MOB.SPX / 128) == 8 && (pMob[partyconn].MOB.SPY / 128) == 2)
					DoTeleport(partyconn, pMob[partyconn].MOB.SPX, pMob[partyconn].MOB.SPY);
				else
					DoTeleport(partyconn, PesaMPosStandard[i][0], PesaMPosStandard[i][1]);

				SendClientSignalParm(partyconn, ESCENE_FIELD, _MSG_StartTime, NigthTime);
			}
		}

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		return;
	}
#pragma endregion
#pragma region >> Pesadelo A
	if (Vol == 175)
	{
		int TargetX = pMob[a_iConn].TargetX;
		int TargetY = pMob[a_iConn].TargetY;


		if ((TargetX / 128) != 19 || (TargetY / 128) != 13)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Use_That_Here]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if ((pMob[a_iConn].Extra.ClassMaster == CELESTIAL || pMob[a_iConn].Extra.ClassMaster == CELESTIALCS || 
			pMob[a_iConn].Extra.ClassMaster == SCELESTIAL) && pMob[a_iConn].Extra.NT < 1)
		{
			SendClientMsg(a_iConn, "Você não possui NT suficiente para realizar essa quest!!");
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].Leader != -1 && pMob[a_iConn].Leader)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Party_Leader_Only]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int isParty = item->sIndex == 3326 ? 1 : 0;

		if (isParty == 0)
			goto lbl_a_noparty;

		if ((pMob[a_iConn].Extra.ClassMaster == CELESTIAL || pMob[a_iConn].Extra.ClassMaster == CELESTIALCS || pMob[a_iConn].Extra.ClassMaster == SCELESTIAL) && pMob[a_iConn].MOB.CurrentScore.Level >= 180)
		{
			SendClientMsg(a_iConn, "Classes Celestiais somente Lv. 179 menos");
			SendItem(a_iConn, m->SourType, m->SourPos, item);

			return;
		}

		struct tm when;
		time_t now;
		time(&now);
		when = *localtime(&now);

		if (when.tm_min >= 0 && when.tm_min <= 9 || when.tm_min >= 14 && when.tm_min <= 29
			|| when.tm_min >= 34 && when.tm_min <= 49 || when.tm_min >= 54 && when.tm_min <= 60)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);

			return;
		}

		if ((pMob[a_iConn].Extra.ClassMaster == CELESTIAL || pMob[a_iConn].Extra.ClassMaster == SCELESTIAL || pMob[a_iConn].Extra.ClassMaster == CELESTIALCS) && pMob[a_iConn].Extra.NT <= 0)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);

			return;
		}

		if (PartyPesa[2] >= maxNightmare)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Night_Limited]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);

			return;
		}
		PartyPesa[2]++;

	lbl_a_noparty:
		int NigthTime = 240;

		if (when.tm_min >= 10 && when.tm_min <= 13)
			NigthTime -= ((when.tm_min - 10) * 60) + when.tm_sec;

		else if (when.tm_min >= 30 && when.tm_min <= 33)
			NigthTime -= ((when.tm_min - 30) * 60) + when.tm_sec;

		else if (when.tm_min >= 50 && when.tm_min <= 53)
			NigthTime -= ((when.tm_min - 50) * 60) + when.tm_sec;


		if ((pMob[a_iConn].Extra.ClassMaster == CELESTIAL || pMob[a_iConn].Extra.ClassMaster == SCELESTIAL || pMob[a_iConn].Extra.ClassMaster == CELESTIALCS))
			pMob[a_iConn].Extra.NT--;

		if ((pMob[a_iConn].MOB.SPX / 128) == 9 && (pMob[a_iConn].MOB.SPY / 128) == 1)
			DoTeleport(a_iConn, pMob[a_iConn].MOB.SPX + rand() % 1, pMob[a_iConn].MOB.SPY + rand() % 1);

		else
			DoTeleport(a_iConn, PesaAPosStandard[0][0] + rand() % 1, PesaAPosStandard[0][1] + rand() % 1);

		SendClientSignalParm(a_iConn, ESCENE_FIELD, _MSG_StartTime, NigthTime);

		for (int i = 0; i < MAX_PARTY && isParty == 1; i++)
		{
			int partyconn = pMob[a_iConn].PartyList[i];

			if ((pMob[partyconn].Extra.ClassMaster >= CELESTIAL) && pMob[partyconn].MOB.CurrentScore.Level >= 180)
				continue;

			if (partyconn > 0 && partyconn < MAX_USER && partyconn != a_iConn && pUser[partyconn].Mode == USER_PLAY)
			{
				if ((pMob[partyconn].Extra.ClassMaster >= CELESTIAL))
				{
					if (pMob[partyconn].Extra.NT <= 0)
						continue;

					pMob[partyconn].Extra.NT--;
				}

				if ((pMob[partyconn].MOB.SPX / 128) == 9 && (pMob[partyconn].MOB.SPY / 128) == 1)
					DoTeleport(partyconn, pMob[partyconn].MOB.SPX + rand() % 1, pMob[partyconn].MOB.SPY + rand() % 1);
				else
					DoTeleport(partyconn, PesaAPosStandard[i][0] + rand() % 1, PesaAPosStandard[i][1] + rand() % 1);

				SendClientSignalParm(partyconn, ESCENE_FIELD, _MSG_StartTime, NigthTime);
			}
		}
		sprintf(temp, "useitem,nightmare A ticket used party:%d", isParty);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		return;
	}
#pragma endregion
#pragma region >> Gema Estelar
	if (Vol == 12)
	{
		unsigned char map_att = GetAttribute(pMob[a_iConn].TargetX, pMob[a_iConn].TargetY);
		int Arena = BASE_GetArena(pMob[a_iConn].TargetX, pMob[a_iConn].TargetY);
		int Village = BASE_GetVillage(pMob[a_iConn].TargetX, pMob[a_iConn].TargetY);

		if ((pMob[a_iConn].TargetX / 128) == 9 && (pMob[a_iConn].TargetY / 128) == 1) goto CanSave;

		if ((pMob[a_iConn].TargetX / 128) == 8 && (pMob[a_iConn].TargetY / 128) == 2) goto CanSave;

		if ((pMob[a_iConn].TargetX / 512) == 6 && ((pMob[a_iConn].TargetY / 512) == 2 || (pMob[a_iConn].TargetY / 512) == 3))
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Use_That_Here]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].TargetX >= 3570 && pMob[a_iConn].TargetY >= 3446 && pMob[a_iConn].TargetX <= 3965 && pMob[a_iConn].TargetY <= 3711)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Use_That_Here]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].TargetX >= 1302 && pMob[a_iConn].TargetY >= 1483 && pMob[a_iConn].TargetX <= 1381 && pMob[a_iConn].TargetY <= 1516)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Use_That_Here]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].TargetX >= 2379 && pMob[a_iConn].TargetY >= 2076 && pMob[a_iConn].TargetX <= 2426 && pMob[a_iConn].TargetY <= 2133)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Use_That_Here]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}
		if (pMob[a_iConn].TargetX >= 2228 && pMob[a_iConn].TargetY >= 1700 && pMob[a_iConn].TargetX <= 2257 && pMob[a_iConn].TargetY <= 1728)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Use_That_Here]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].TargetX >= 459 && pMob[a_iConn].TargetY >= 3887 && pMob[a_iConn].TargetX <= 497 && pMob[a_iConn].TargetY <= 3916)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Use_That_Here]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].TargetX >= 658 && pMob[a_iConn].TargetY >= 3728 && pMob[a_iConn].TargetX <= 703 && pMob[a_iConn].TargetY <= 3762)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Use_That_Here]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].TargetX >= 1312 && pMob[a_iConn].TargetY >= 4027 && pMob[a_iConn].TargetX <= 1348 && pMob[a_iConn].TargetY <= 4055)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Use_That_Here]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].TargetX >= 793 && pMob[a_iConn].TargetY >= 4046 && pMob[a_iConn].TargetX <= 827 && pMob[a_iConn].TargetY <= 4080)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Use_That_Here]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (map_att & 4 && pMob[a_iConn].MOB.CurrentScore.Level < 1000)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Use_That_Here]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (Arena < MAX_GUILDZONE || Village < MAX_GUILDZONE || (pMob[a_iConn].TargetX / 512) == 4 && (pMob[a_iConn].TargetY / 512) == 7)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Use_That_Here]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}
	CanSave:
		int sFace = pMob[a_iConn].MOB.Equip[0].sIndex / 10;

		if (sFace == 0)
			SendEmotion(a_iConn, 23, 0);

		else if (sFace == 1)
			SendEmotion(a_iConn, 15, 0);

		else if (sFace == 2)
			SendEmotion(a_iConn, 15, 0);

		else if (sFace == 3)
			SendEmotion(a_iConn, 15, 0);


		pMob[a_iConn].MOB.SPX = pMob[a_iConn].TargetX;
		pMob[a_iConn].MOB.SPY = pMob[a_iConn].TargetY;

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Set_Warp]);
		return;
	}
#pragma endregion
#pragma region >> Gema de Diamante
	if (Vol == 180)
	{
		STRUCT_ITEM *dest = GetItemPointer(&pMob[a_iConn].MOB, pUser[a_iConn].Cargo, m->DestType, m->DestPos);

		if (dest == NULL)
		{
			sprintf(temp, "err,use item fail dest %d %d", m->DestType, m->DestPos);
			MyLog(LogType::Itens, "-system", temp, 0, pUser[a_iConn].IP);
			return;
		}

		if (m->DestType || m->DestPos >= 8 && m->DestPos < 16 || m->DestType == ITEM_PLACE_EQUIP && m->DestPos == 0)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Only_To_Equips]);
			MyLog(LogType::Itens, "err,use item fail - dest", pMob[a_iConn].MOB.MobName, 0, pUser[a_iConn].IP);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int sanc = BASE_GetItemSanc(dest);
		int ItemId = dest->sIndex;

		if (sanc < REF_10 && g_pItemList[ItemId].Grade < 5)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (g_pItemList[ItemId].Grade == 6)
			ItemId -= 1;

		else if (g_pItemList[ItemId].Grade == 7)
			ItemId -= 2;

		else if (g_pItemList[ItemId].Grade == 8)
			ItemId -= 3;

		dest->sIndex = ItemId;

		if (sanc == REF_10)
			BASE_SetItemSanc(dest, 10, 0);

		else if (sanc == REF_11)
			BASE_SetItemSanc(dest, 11, 0);

		else if (sanc == REF_12)
			BASE_SetItemSanc(dest, 12, 0);

		else if (sanc == REF_13)
			BASE_SetItemSanc(dest, 13, 0);

		else if (sanc == REF_14)
			BASE_SetItemSanc(dest, 14, 0);

		else if (sanc == REF_15)
			BASE_SetItemSanc(dest, 15, 0);

		pMob[a_iConn].GetCurrentScore(a_iConn);

		SendScore(a_iConn);
		sprintf(temp, "useitem,change jewel success %d+%d - (%d,%d,%d)", dest->sIndex, sanc, item->stEffect[0].cEffect, item->stEffect[1].cEffect, item->stEffect[2].cEffect);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);


		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		SendItem(a_iConn, m->DestType, m->DestPos, dest);
		SendEmotion(a_iConn, 14, 3);

		return;
	}
#pragma endregion
#pragma region >> Gema de Esmeralda
	if (Vol == 181)
	{
		STRUCT_ITEM *dest = GetItemPointer(&pMob[a_iConn].MOB, pUser[a_iConn].Cargo, m->DestType, m->DestPos);

		if (dest == NULL)
		{
			sprintf(temp, "err,use item fail dest %d %d", m->DestType, m->DestPos);
			MyLog(LogType::Itens, "-system", temp, 0, pUser[a_iConn].IP);
			return;
		}

		if (m->DestType || m->DestPos >= 8 && m->DestPos < 16 || m->DestType == ITEM_PLACE_EQUIP && m->DestPos == 0)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Only_To_Equips]);
			MyLog(LogType::Itens, "err,use item fail - dest", pMob[a_iConn].MOB.MobName, 0, pUser[a_iConn].IP);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int sanc = BASE_GetItemSanc(dest);
		int ItemId = dest->sIndex;

		if (sanc < REF_10 && g_pItemList[ItemId].Grade < 5)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (g_pItemList[ItemId].Grade == 5)
			ItemId += 1;

		else if (g_pItemList[ItemId].Grade == 7)
			ItemId -= 1;

		else if (g_pItemList[ItemId].Grade == 8)
			ItemId -= 2;

		dest->sIndex = ItemId;

		if (sanc == REF_10)
			BASE_SetItemSanc(dest, 10, 1);

		else if (sanc == REF_11)
			BASE_SetItemSanc(dest, 11, 1);

		else if (sanc == REF_12)
			BASE_SetItemSanc(dest, 12, 1);

		else if (sanc == REF_13)
			BASE_SetItemSanc(dest, 13, 1);

		else if (sanc == REF_14)
			BASE_SetItemSanc(dest, 14, 1);

		else if (sanc == REF_15)
			BASE_SetItemSanc(dest, 15, 1);

		pMob[a_iConn].GetCurrentScore(a_iConn);

		SendScore(a_iConn);
		sprintf(temp, "useitem,change jewel success %d+%d - (%d,%d,%d)", dest->sIndex, sanc, item->stEffect[0].cEffect, item->stEffect[1].cEffect, item->stEffect[2].cEffect);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		SendItem(a_iConn, m->DestType, m->DestPos, dest);
		SendEmotion(a_iConn, 14, 3);

		return;
	}
#pragma endregion
#pragma region >> Gema de Coral
	if (Vol == 182)
	{
		STRUCT_ITEM *dest = GetItemPointer(&pMob[a_iConn].MOB, pUser[a_iConn].Cargo, m->DestType, m->DestPos);

		if (dest == NULL)
		{
			sprintf(temp, "err,use item fail dest %d %d", m->DestType, m->DestPos);
			MyLog(LogType::Itens, "-system", temp, 0, pUser[a_iConn].IP);
			return;
		}

		if (m->DestType || m->DestPos >= 8 && m->DestPos < 16 || m->DestType == ITEM_PLACE_EQUIP && m->DestPos == 0)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Only_To_Equips]);
			MyLog(LogType::Itens, "err,use item fail - dest", pMob[a_iConn].MOB.MobName, 0, pUser[a_iConn].IP);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int sanc = BASE_GetItemSanc(dest);
		int ItemId = dest->sIndex;

		if (sanc < REF_10 && g_pItemList[ItemId].Grade < 5)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (g_pItemList[ItemId].Grade == 5)
			ItemId += 2;

		else if (g_pItemList[ItemId].Grade == 6)
			ItemId += 1;

		else if (g_pItemList[ItemId].Grade == 8)
			ItemId -= 1;

		dest->sIndex = ItemId;

		if (sanc == REF_10)
			BASE_SetItemSanc(dest, 10, 2);

		else if (sanc == REF_11)
			BASE_SetItemSanc(dest, 11, 2);

		else if (sanc == REF_12)
			BASE_SetItemSanc(dest, 12, 2);

		else if (sanc == REF_13)
			BASE_SetItemSanc(dest, 13, 2);

		else if (sanc == REF_14)
			BASE_SetItemSanc(dest, 14, 2);

		else if (sanc == REF_15)
			BASE_SetItemSanc(dest, 15, 2);

		pMob[a_iConn].GetCurrentScore(a_iConn);

		SendScore(a_iConn);
		sprintf(temp, "useitem,change jewel success %d+%d - (%d,%d,%d)", dest->sIndex, sanc, item->stEffect[0].cEffect, item->stEffect[1].cEffect, item->stEffect[2].cEffect);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		SendItem(a_iConn, m->DestType, m->DestPos, dest);
		SendEmotion(a_iConn, 14, 3);

		return;
	}
#pragma endregion
#pragma region >> Gema de Garnet
	if (Vol == 183)
	{
		STRUCT_ITEM *dest = GetItemPointer(&pMob[a_iConn].MOB, pUser[a_iConn].Cargo, m->DestType, m->DestPos);

		if (dest == NULL)
		{
			sprintf(temp, "err,use item fail dest %d %d", m->DestType, m->DestPos);
			MyLog(LogType::Itens, "-system", temp, 0, pUser[a_iConn].IP);
			return;
		}

		if (m->DestType || m->DestPos >= 8 && m->DestPos < 16 || m->DestType == ITEM_PLACE_EQUIP && m->DestPos == 0)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Only_To_Equips]);
			MyLog(LogType::Itens, "err,use item fail - dest", pMob[a_iConn].MOB.MobName, 0, pUser[a_iConn].IP);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int sanc = BASE_GetItemSanc(dest);
		int ItemId = dest->sIndex;

		if (sanc < REF_10 && g_pItemList[ItemId].Grade < 5)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (g_pItemList[ItemId].Grade == 5)
			ItemId += 3;

		else if (g_pItemList[ItemId].Grade == 6)
			ItemId += 2;

		else if (g_pItemList[ItemId].Grade == 7)
			ItemId += 1;

		dest->sIndex = ItemId;

		if (sanc == REF_10)
			BASE_SetItemSanc(dest, 10, 3);

		else if (sanc == REF_11)
			BASE_SetItemSanc(dest, 11, 3);

		else if (sanc == REF_12)
			BASE_SetItemSanc(dest, 12, 3);

		else if (sanc == REF_13)
			BASE_SetItemSanc(dest, 13, 3);

		else if (sanc == REF_14)
			BASE_SetItemSanc(dest, 14, 3);

		else if (sanc == REF_15)
			BASE_SetItemSanc(dest, 15, 3);

		pMob[a_iConn].GetCurrentScore(a_iConn);

		SendScore(a_iConn);
		sprintf(temp, "useitem,change jewel success %d+%d - (%d,%d,%d)", dest->sIndex, sanc, item->stEffect[0].cEffect, item->stEffect[1].cEffect, item->stEffect[2].cEffect);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		SendItem(a_iConn, m->DestType, m->DestPos, dest);
		SendEmotion(a_iConn, 14, 3);

		return;
	}
#pragma endregion
#pragma region >> Selo das Almas
	if (Vol == 206)
	{
		if (item->stEffect[0].cEffect == 0)
		{//Selo Vazio
			if (pMob[a_iConn].Extra.ClassMaster != SCELESTIAL)
			{
				SendClientMsg(a_iConn, g_pMessageStringTable[_NN_GOD2CHARONLY_]);
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				return;
			}

			if (amount > 1)
				BASE_SetItemAmount(item, amount - 1);

			else
				memset(item, 0, sizeof(STRUCT_ITEM));

			CharLogOut(a_iConn);

			MSG_STANDARDPARM sm_sa;
			memset(&sm_sa, 0, sizeof(MSG_STANDARDPARM));

			sm_sa.Size = sizeof(MSG_STANDARDPARM);
			sm_sa.Type = _MSG_DBPutInCapsule;
			sm_sa.ID = a_iConn;

			sm_sa.Parm = pUser[a_iConn].Slot;

			DBServerSocket.SendOneMessage((char*)&sm_sa, sizeof(MSG_STANDARDPARM));
		}

		return;
	}
#pragma endregion
#pragma region >> Rações
	if (Vol == 15)
	{
		if (m->DestType || m->DestPos != 14)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		STRUCT_ITEM *dest = &pMob[a_iConn].MOB.Equip[14];

		if (dest->sIndex < 2330 || dest->sIndex >= 2390)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int mount = (dest->sIndex - 2330) % 30;

		if (mount >= 6 && mount <= 15)
			mount = 6;

		if (mount == 19)
			mount = 7;

		if (mount == 20)
			mount = 8;

		if (mount == 21 || mount == 22 || mount == 23)
			mount = 9;

		if (mount == 24 || mount == 25 || mount == 26)
			mount = 10;

		if (mount == 27)
			mount = 11;

		if (mount == 28)
			mount = 12;

		if (mount == 29)
			mount = 19;

		int racid = item->sIndex >= 3367 ? item->sIndex - 3367 : item->sIndex - 2420;

		int racao = racid % 30;

		if (mount == racao)
		{
			if (dest->stEffect[0].sValue > 0)
			{
				if ((pMob[a_iConn].MOB.Equip[14].stEffect[0].sValue + 5000) > 30000)
					pMob[a_iConn].MOB.Equip[14].stEffect[0].sValue = 30000;
				else
					pMob[a_iConn].MOB.Equip[14].stEffect[0].sValue += 5000;


				int _racao = dest->stEffect[2].cEffect + 2;

				if (_racao > 100)
					_racao = 100;

				dest->stEffect[2].cEffect = _racao;

				SendItem(a_iConn, ITEM_PLACE_EQUIP, 14, &pMob[a_iConn].MOB.Equip[14]);

				STRUCT_ITEM *Mount = &pMob[a_iConn].MOB.Equip[14];

				if (dest->sIndex >= 2330 && dest->sIndex < 2360)
					MountProcess(a_iConn, dest);

				if (dest->sIndex >= 2360 && dest->sIndex < 2390)
					ProcessAdultMount(a_iConn, 0);

				if (amount > 1)
					BASE_SetItemAmount(item, amount - 1);

				else
					memset(item, 0, sizeof(STRUCT_ITEM));

				MountProcess(a_iConn, Mount);
				SendClientSignalParm(a_iConn, ESCENE_FIELD, _MSG_SoundEffect, 270);
				SendItem(a_iConn, m->DestType, m->DestPos, dest);
			}
			else
				SendItem(a_iConn, m->SourType, m->SourPos, item);
		}
		else
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Mount_Not_Match]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
		}

		sprintf(temp, "useitem,ração mount: %d", mount);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);
		return;
	}
#pragma endregion
#pragma region >> Âmagos
	if (Vol == 16)
	{
		char temp2[4096];
		if (m->DestType || m->DestPos != 14)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		STRUCT_ITEM *dest = &pMob[a_iConn].MOB.Equip[14];

		if (dest->sIndex < 2330 || dest->sIndex >= 2390 || dest->stEffect[0].sValue <= 0)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int mountIndex = (dest->sIndex - 2330) % 30;
		int amgIndex = (item->sIndex - 2390) % 30;

		//if (mountIndex == 28)//Sleipnir
		//	mountIndex = 21;

		//if (mountIndex == 27)//Svadilfire
		//	mountIndex = 10;

		if (mountIndex != amgIndex)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Mount_Not_Match]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		dest->stEffect[0].sValue = 20000;
		dest->stEffect[2].cEffect = 100;
		int level = dest->stEffect[1].cEffect;

		if (level >= 120 && dest->sIndex >= 2360 && dest->sIndex < 2390)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Upgrade_More]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			ProcessAdultMount(a_iConn, 0);
			return;
		}
		//montarias
		if (dest->sIndex >= 2360 && dest->sIndex < 2390)
		{
			int rate = BASE_GetGrowthRate(dest);
			int _rand = rand() % 101;

			if (_rand > rate) // Refinação falhou
			{
				int rand2 = rand() % 100;

				if (rand2 < 20 && dest->stEffect[1].cEffect < 70)
				{
					dest->stEffect[1].cEffect--;
				}

				if (dest->stEffect[1].cEffect >= 70 && dest->stEffect[1].cEffect % 2 != 0)
				{
					if (rand2 < 50)
					{
						dest->stEffect[1].cEffect--;
					}
				}

				if (pMob[a_iConn].MOB.Equip[0].sIndex / 10)
					SendEmotion(a_iConn, 15, 0);
				else
					SendEmotion(a_iConn, 20, 0);

				if (amount > 1)
					BASE_SetItemAmount(item, amount - 1);

				else
					memset(item, 0, 8);

				sprintf(temp, "%s", g_pMessageStringTable[_NN_Fail_To_Refine]);
				SendClientMsg(a_iConn, temp);

				SendItem(a_iConn, m->DestType, m->DestPos, dest);

				ProcessAdultMount(a_iConn, 0);
				return;
			}
			
				sprintf(temp, "%s", g_pMessageStringTable[_NN_Refine_Success]);
				printf(temp, "useitem,mount refine success %d+%d (%d,%d,%d)", dest->sIndex, dest->stEffect[1].cValue,
					item->stEffect[0].cEffect, item->stEffect[1].cEffect, item->stEffect[2].cEffect);

				SendEmotion(a_iConn, 14, 3);

			MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);
		}
		int levelUP = 1;

		if (LOCALSERVER)
			levelUP = 10;

		level = levelUP + level;
		dest->stEffect[1].cEffect = level;
		dest->stEffect[2].cValue = 1;

		STRUCT_ITEM *Mount = &pMob[a_iConn].MOB.Equip[14];

		if (level >= 25 && dest->sIndex == 2330
			|| level >= 50 && dest->sIndex == 2331
			|| level >= 100 && dest->sIndex >= 2332 && dest->sIndex < 2360)
		{
			dest->sIndex += 30;

			dest->stEffect[1].cValue += rand() % 14 + 1; // Variar entre quantas vitalidades pode subir 1 ~ 14
			dest->stEffect[1].cEffect = 0;
			dest->stEffect[2].cValue = 0;

			if (dest->stEffect[1].cValue >= 60) // Verificação para saber se a vitalidade é maior que 60
				dest->stEffect[1].cValue = 60; // iguala a vitalidade a 60 para não bugar
		
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Mount_Growth]);
			ProcessAdultMount(a_iConn, 0);
			RemoveParty(a_iConn);
			SendEquip(a_iConn, a_iConn);
		}

		if (dest->sIndex >= 2330 && dest->sIndex < 2360)
			MountProcess(a_iConn, &pMob[a_iConn].MOB.Equip[14]);
		

		if (dest->sIndex >= 2360 && dest->sIndex < 2390)
			ProcessAdultMount(a_iConn, 0);

		SendItem(a_iConn, m->DestType, m->DestPos, dest);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		sprintf(temp, "Sua montaria subiu para lv. [%d]", level);
		SendMsgExp(a_iConn, temp, TNColor::Blue, false);

		return;
	}
#pragma endregion
#pragma region >> Acelerador de Nascimento
	if (item->sIndex == 3438)
	{
		STRUCT_ITEM *dest = GetItemPointer(&pMob[a_iConn].MOB, pUser[a_iConn].Cargo, m->DestType, m->DestPos);

		if (dest == NULL)
		{
			sprintf(temp, "Erro, uso do item falhou dest %d %d", m->DestType, m->DestPos);
			MyLog(LogType::Itens, "-system", temp, 0, pUser[a_iConn].IP);
			return;
		}

		if (m->DestType || m->DestPos != 14)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Mount_Not_Match]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].MOB.Equip[14].sIndex >= 2330 && pMob[a_iConn].MOB.Equip[14].sIndex <= 2390 ||
			pMob[a_iConn].MOB.Equip[14].sIndex >= 3980 && pMob[a_iConn].MOB.Equip[14].sIndex <= 3994)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			SendClientMsg(a_iConn, "Aplicável somente para ovos de montarias.");
			return;
		}

		dest->sIndex += 30;
		dest->stEffect[0].sValue = 20000;
		dest->stEffect[1].cEffect = 1;
		dest->stEffect[1].cValue = dest->stEffect[1].cValue + rand() % 20;
		dest->stEffect[2].cEffect = 30;
		dest->stEffect[2].cValue = 1;
		MountProcess(a_iConn, &pMob[a_iConn].MOB.Equip[14]);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, 8);
		SendItem(a_iConn, m->DestType, m->DestPos, dest);
		SendClientMsg(a_iConn, "Processo concluido com sucesso.");
		return;
	}
#pragma endregion
#pragma region >> Retornar Cavalo
	if (item->sIndex == 3453)
	{
		int mountIndex = pMob[a_iConn].MOB.Equip[14].sIndex;

		if (mountIndex < 2330 || mountIndex >= 2390)
		{
			SendClientMsg(a_iConn, "Sua montaria não está ferida.");
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].MOB.Equip[14].stEffect[0].sValue > 0)
		{
			SendClientMsg(a_iConn, "Sua montaria não está ferida.");
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int price = g_pItemList[mountIndex].Price;

		if (pMob[a_iConn].MOB.Coin < price)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Not_Enough_Money]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (price < 0 || price > 2000000000)
			return;

		pMob[a_iConn].MOB.Coin -= price;

		int vit = BASE_GetItemAbility(&pMob[a_iConn].MOB.Equip[14], 79);

		vit -= rand() % 3;

		if (vit > 0)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cured]);
			pMob[a_iConn].MOB.Equip[14].stEffect[1].cValue = vit;
			pMob[a_iConn].MOB.Equip[14].stEffect[0].sValue = 20;
			pMob[a_iConn].MOB.Equip[14].stEffect[2].cEffect = 5;
		}
		else
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cure_failed]);
			memset(&pMob[a_iConn].MOB.Equip[14], 0, sizeof(STRUCT_ITEM));
		}

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, 8);

		pMob[a_iConn].GetCurrentScore(a_iConn);
		SendItem(a_iConn, ITEM_PLACE_EQUIP, 14, &pMob[a_iConn].MOB.Equip[14]);
		MountProcess(a_iConn, &pMob[a_iConn].MOB.Equip[14]);
		SendEtc(a_iConn);

		sprintf(temp, "etc,mount ressurect index:%d vit:%d - %d", pMob[a_iConn].MOB.Equip[14].sIndex, vit, pMob[a_iConn].MOB.Equip[14].stEffect[1].cEffect);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);
		return;
	}
#pragma endregion
#pragma region >> Catalizadores
	if (Vol == 94)
	{
		STRUCT_ITEM *dest = GetItemPointer(&pMob[a_iConn].MOB, pUser[a_iConn].Cargo, m->DestType, m->DestPos);

		if (dest == NULL)
		{
			sprintf(temp, "Erro, uso do item falhou dest %d %d", m->DestType, m->DestPos);
			MyLog(LogType::Itens, "-system", temp, 0, pUser[a_iConn].IP);
			return;
		}

		if (m->DestType || m->DestPos != 14)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Mount_Not_Match]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}


		int mount = (dest->sIndex);
		int cat = item->sIndex - 3344;

		// Kapel
		if (mount >= 2333 && mount <= 2335) //Dente de Sabre, Dragão Menor, Urso
			mount = 0;

		// Acuban
		if (mount >= 2336 && mount <= 2338 || mount >= 2341 && mount <= 2343 || mount >= 2357 && mount <= 2358) // Cavalo Leve N e B, Cavalo Fantasma N e B, Cavalo S/Sela N e B, Svaldfire e Spleinir
			mount = 1;

		// Mencar
		if (mount == 2339 || mount == 2340 || mount >= 2344 && mount <= 2345) //  Andaluz N e B, Equipe N e B
			mount = 2;

		// Birago
		if (mount >= 2346 && mount <= 2348) //Dragão, Fenri das Sombras, Fenri
			mount = 3;

		// Yus
		if (mount >= 2351 && mount <= 2353) //Pegasus, Unisus
			mount = 4;

		// Makav
		if (mount >= 2354 && mount <= 2356) // Grifo, Hipo-Grifo, Grifo Sangrento
			mount = 5;

		// Alperath
		if (mount >= 2349 && mount <= 2350) //Dragão Vermelho, Tigre de Fogo
			mount = 6;

		if (mount != cat)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Mount_Not_Match]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		dest->sIndex += 30;

		int life = dest->stEffect[1].cValue;
		dest->stEffect[1].cValue = life + rand() % 20 + 1;
		dest->stEffect[1].cEffect = 0;
		dest->stEffect[2].cValue = 0;

		SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Mount_Growth]);
		MountProcess(a_iConn, &pMob[a_iConn].MOB.Equip[14]);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		SendItem(a_iConn, m->DestType, m->DestPos, dest);

		int sFace = pMob[a_iConn].MOB.Equip[0].sIndex / 10;

		if (sFace)
			SendEmotion(a_iConn, 15, 0);
		else
			SendEmotion(a_iConn, 20, 0);

		SendItem(a_iConn, m->DestType, m->DestPos, dest);

		RemoveParty(a_iConn);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		return;
	}
#pragma endregion	
#pragma region >> Restauradores
	if (Vol == 93)
	{
		STRUCT_ITEM *dest = GetItemPointer(&pMob[a_iConn].MOB, pUser[a_iConn].Cargo, m->DestType, m->DestPos);

		if (dest == NULL)
		{
			sprintf(temp, "Erro, uso do item falhou dest %d %d", m->DestType, m->DestPos);
			MyLog(LogType::Itens, "-system", temp, 0, pUser[a_iConn].IP);
			return;
		}

		if (m->DestType || m->DestPos != 14)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Mount_Not_Match]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int mount = (dest->sIndex);
		int res = item->sIndex - 3351;

		// Kapel
		if (mount >= 2363 && mount <= 2365) //Dente de Sabre, Dragão Menor, Urso
			mount = 0;

		// Acuban
		if (mount >= 2366 && mount <= 2368 || mount >= 2371 && mount <= 2373 || mount >= 2387 && mount <= 2388) // Cavalo Leve N e B, Cavalo Fantasma N e B, Cavalo S/Sela N e B, Svaldfire e Spleinir
			mount = 1;

		// Mencar
		if (mount == 2369 || mount == 2370 || mount >= 2374 && mount <= 2375) //  Andaluz N e B, Equipe N e B
			mount = 2;

		// Birago
		if (mount >= 2376 && mount <= 2378) //Dragão, Fenri das Sombras, Fenri
			mount = 3;

		// Yus
		if (mount >= 2381 && mount <= 2383) //Pegasus, Unisus
			mount = 4;

		// Makavcataliza
		if (mount >= 2384 && mount <= 2386) // Grifo, Hipo-Grifo, Grifo Sangrento
			mount = 5;

		// Alperath
		if (mount >= 2379 && mount <= 2380) //Dragão Vermelho, Tigre de Fogo
			mount = 6;

		if (mount != res)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Mount_Not_Match]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (dest->stEffect[1].cValue == 60 || dest->stEffect[0].sValue <= 0)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			SendClientMsg(a_iConn, "Vitalidade da montaria está no máximo.");
			return;
		}

		dest->stEffect[1].cValue += rand() % 2 + 1;
		SendClientMsg(a_iConn, "Upgrade +");
		SendEmotion(a_iConn, 14, 3);

		int sFace = pMob[a_iConn].MOB.Equip[0].sIndex / 10;

		if (sFace)
			SendEmotion(a_iConn, 15, 0);
		else
			SendEmotion(a_iConn, 20, 0);

		SendItem(a_iConn, m->DestType, m->DestPos, dest);


		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		return;
	}
#pragma endregion
#pragma region >> Divina 7 15 30 Dias
	if (item->sIndex >= 3379 && item->sIndex <= 3381)
	{
		time(&pMob[a_iConn].Extra.DivineEnd);

		int val = 0;

		if (item->sIndex == 3379)//7DD
		{
			val = 60 * 60 * 24 * 8;
			pMob[a_iConn].Extra.DivineEnd += val;
		}
		else  if (item->sIndex == 3380)//15D
		{
			val = 60 * 60 * 24 * 16;
			pMob[a_iConn].Extra.DivineEnd += val;
		}

		else if (item->sIndex == 3381)//30D
		{
			val = 60 * 60 * 24 * 31;
			pMob[a_iConn].Extra.DivineEnd += val;
		}

		int divina = GetEmptyAffect(a_iConn, 34);

		if (divina == -1 || pMob[a_iConn].Affect[divina].Type == 34)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_CantEatMore]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int AffectIndex = 34;
		int Level = 1;

		pMob[a_iConn].Affect[divina].Type = AffectIndex;
		pMob[a_iConn].Affect[divina].Level = Level;
		pMob[a_iConn].Affect[divina].Value = 2;
		pMob[a_iConn].Affect[divina].Time = 2000000000;

		BASE_GetHpMp(&pMob[a_iConn].MOB, &pMob[a_iConn].Extra);
		pMob[a_iConn].GetCurrentScore(a_iConn);
		SendScore(a_iConn);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);
		else
		{
			memset(item, 0, sizeof(STRUCT_ITEM));
		}

		MSG_STANDARDPARM4 divineCast;
		memset(&divineCast, 0, sizeof(MSG_STANDARDPARM4));

		divineCast.Size = sizeof(MSG_STANDARDPARM4);
		divineCast.Type = _S_SSP_REQ_DIVINE_END_;
		divineCast.ID = a_iConn;

		divineCast.Parm1 = val;
		divineCast.Parm2 = pUser[a_iConn].Slot;
		divineCast.Parm3 = AffectIndex; // AffectIndex
		divineCast.Parm4 = Level; // Value

		DBServerSocket.SendOneMessage((char*)&divineCast, sizeof(MSG_STANDARDPARM4));

		sprintf(temp, "useitem,item divine type: %d", Vol - 64);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);
		return;
	}
#pragma endregion
#pragma region >> Poção Vigor & Saúde
	if (Vol == 58)
	{
		int sAffect = GetEmptyAffect(a_iConn, 35);

		if (sAffect == -1 || pMob[a_iConn].Affect[sAffect].Type == 35)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_CantEatMore]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}
		if (item->sIndex == 3313) // Vigor 1 hora
		{
			pMob[a_iConn].Affect[sAffect].Type = 35;
			pMob[a_iConn].Affect[sAffect].Level = 2;
			pMob[a_iConn].Affect[sAffect].Value = 0;
			pMob[a_iConn].Affect[sAffect].Time = AFFECT_1H;

			BASE_GetHpMp(&pMob[a_iConn].MOB, &pMob[a_iConn].Extra);
			pMob[a_iConn].GetCurrentScore(a_iConn);
			SendScore(a_iConn);

			if (amount > 1)
				BASE_SetItemAmount(item, amount - 1);

			else
				memset(item, 0, sizeof(STRUCT_ITEM));

			return;
		}
		else if (item->sIndex == 3364) // 7 Dias
		{
			pMob[a_iConn].Affect[sAffect].Type = 35;
			pMob[a_iConn].Affect[sAffect].Level = 1;
			pMob[a_iConn].Affect[sAffect].Value = 0;
			pMob[a_iConn].Affect[sAffect].Time = AFFECT_1D * 7;

			BASE_GetHpMp(&pMob[a_iConn].MOB, &pMob[a_iConn].Extra);
			pMob[a_iConn].GetCurrentScore(a_iConn);

			SendScore(a_iConn);

			if (amount > 1)
				BASE_SetItemAmount(item, amount - 1);

			else
				memset(item, 0, sizeof(STRUCT_ITEM));

			return;
		}
		else if (item->sIndex == 3365) // 15 Dias
		{
			pMob[a_iConn].Affect[sAffect].Type = 35;
			pMob[a_iConn].Affect[sAffect].Level = 1;
			pMob[a_iConn].Affect[sAffect].Value = 0;
			pMob[a_iConn].Affect[sAffect].Time = AFFECT_1D * 15;

			BASE_GetHpMp(&pMob[a_iConn].MOB, &pMob[a_iConn].Extra);
			pMob[a_iConn].GetCurrentScore(a_iConn);

			SendScore(a_iConn);


			if (amount > 1)
				BASE_SetItemAmount(item, amount - 1);

			else
				memset(item, 0, sizeof(STRUCT_ITEM));

			return;
		}
		else if (item->sIndex == 3366) // 30 Dias
		{
			pMob[a_iConn].Affect[sAffect].Type = 35;
			pMob[a_iConn].Affect[sAffect].Level = 1;
			pMob[a_iConn].Affect[sAffect].Value = 0;
			pMob[a_iConn].Affect[sAffect].Time = AFFECT_1D * 30;

			BASE_GetHpMp(&pMob[a_iConn].MOB, &pMob[a_iConn].Extra);
			pMob[a_iConn].GetCurrentScore(a_iConn);

			SendScore(a_iConn);

			if (amount > 1)
				BASE_SetItemAmount(item, amount - 1);

			else
				memset(item, 0, sizeof(STRUCT_ITEM));
			return;
		}

		sprintf(temp, "useitem,item vigor type: %d", item->sIndex);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);
	}
#pragma endregion

#pragma region >> Marmita 24h 3d 7d
	if (Vol == 60)
	{
		int sAffect = GetEmptyAffect(a_iConn, MOUNT_PROTECT_TYPE);
		unsigned int newTime = 0;

		if (sAffect == -1)
		{
			SendClientMsg(a_iConn, "Limite máximo de buffs atingido..");
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}
		switch (item->sIndex)
		{
			case 3214:
				newTime = AFFECT_1D;
				break;
			case 3215:
				newTime = AFFECT_1D * 3;
				break;
			case 3216:
				newTime = AFFECT_1D * 7;
				break;
			default:
				break;
		}

		if (pMob[a_iConn].Affect[sAffect].Type == MOUNT_PROTECT_TYPE)
		{
			unsigned int sumTime = pMob[a_iConn].Affect[sAffect].Time + newTime;
			if (sumTime > MAX_TIME_MARMITA)
			{
				SendClientMsg(a_iConn, "Limite de acumulo de tempo do buff é de 15 dias..");
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				return;
			}
			newTime = sumTime;
		}
		
			pMob[a_iConn].Affect[sAffect].Type = MOUNT_PROTECT_TYPE;
			pMob[a_iConn].Affect[sAffect].Level = 1;
			pMob[a_iConn].Affect[sAffect].Value = 0;
			pMob[a_iConn].Affect[sAffect].Time = newTime;

		
			pMob[a_iConn].GetCurrentScore(a_iConn);
			SendScore(a_iConn);

			if (amount > 1)
				BASE_SetItemAmount(item, amount - 1);

			else
				memset(item, 0, sizeof(STRUCT_ITEM));

			return;
		
		
		sprintf(temp, "useitem,item marmita type: %d", item->sIndex);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);
	}
#pragma endregion

#pragma region >> Poção Kappa
	if (Vol == 10 || Vol == 55 || Vol == 200 || Vol == 201 || Vol == 56 || Vol == 52 || Vol == 53 || Vol == 57 || Vol == 202)
	{
		int value = 0;

		int tempo = 80;

		//Kappa
		if (item->sIndex == 787)
			value = 1;

		//Combatente
		else if (item->sIndex == 1764)
			value = 2;

		//Mental
		else if (item->sIndex == 1765)
			value = 3;

		//Mental 60m
		else if (item->sIndex == 3312)
		{
			tempo = AFFECT_1H;
			value = 3;
		}
		//Combatente 60m
		else if (item->sIndex == 3311)
		{
			tempo = AFFECT_1H;
			value = 2;
		}

		//Kappa 30m
		else if (item->sIndex == 3310)
		{
			tempo = AFFECT_1H / 2;
			value = 1;
		}

		//Mental 20h
		else if (item->sIndex == 3321)
		{
			tempo = AFFECT_1H * 20;
			value = 3;
		}

		//Combatente 20h
		else if (item->sIndex == 3320)
		{
			tempo = AFFECT_1H * 20;
			value = 2;
		}

		//Kappa 20h
		else if (item->sIndex == 3319)
		{
			tempo = AFFECT_1H * 20;
			value = 1;
		}
		//Sephira 7d
		else if (item->sIndex == 3361)
		{
			tempo = AFFECT_1D * 7;
			value = 1;
		}

		//Sephira 15d
		else if (item->sIndex == 3362)
		{
			tempo = AFFECT_1D * 15;
			value = 1;
		}

		//Sephira 30d
		else if (item->sIndex == 3363)
		{
			tempo = AFFECT_1D * 30;
			value = 1;
		}

		int EmptyAffect = -1;

		for (int i = 0; i < MAX_AFFECT; i++)
		{
			if (pMob[a_iConn].Affect[i].Type == 4 && pMob[a_iConn].Affect[i].Value == value)
			{
				EmptyAffect = i;
				break;
			}
		}

		if (EmptyAffect >= 0)
		{
			SendClientMsg(a_iConn, "Você já possui um buff desse tipo ativo.");
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		for (int i = 0; i < MAX_AFFECT && EmptyAffect == -1; i++)
		{
			if (pMob[a_iConn].Affect[i].Type == 0)
			{
				EmptyAffect = i;
				break;
			}
		}

		if (EmptyAffect != -1)
		{
			pMob[a_iConn].Affect[EmptyAffect].Type = 4;
			pMob[a_iConn].Affect[EmptyAffect].Level = 0;
			pMob[a_iConn].Affect[EmptyAffect].Value = value;
			pMob[a_iConn].Affect[EmptyAffect].Time = tempo;

			pMob[a_iConn].GetCurrentScore(a_iConn);
			SendScore(a_iConn);
		}


		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		sprintf(temp, "useitem,poção_kappa affectslot:%d value:%d time:%d", EmptyAffect, value, tempo);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);
		return;
	}
#pragma endregion
#pragma region >> Elixir Qetsiyah
	if (item->sIndex == 5548)
	{
		int sAffect = GetEmptyAffect(a_iConn, 51);

		if (sAffect == -1 || pMob[a_iConn].Affect[sAffect].Type == 51)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_CantEatMore]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		pMob[a_iConn].Affect[sAffect].Type = 51;
		pMob[a_iConn].Affect[sAffect].Level = 2;
		pMob[a_iConn].Affect[sAffect].Value = 0;
		pMob[a_iConn].Affect[sAffect].Time = AFFECT_1D;

		pMob[a_iConn].GetCurrentScore(a_iConn);
		SendScore(a_iConn);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		sprintf(temp, "useitem,item revigorante type: %d", item->sIndex);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);
		return;
	}
#pragma endregion
#pragma region >> Remédio da Coragem
	if (item->sIndex == 4046 || item->sIndex == 646)
	{
		int sAffect = GetEmptyAffect(a_iConn, 30);

		if (sAffect == -1 || pMob[a_iConn].Affect[sAffect].Type == 30 && pMob[a_iConn].Affect[sAffect].Value != 500)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_CantEatMore]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		pMob[a_iConn].Affect[sAffect].Type = 30;
		pMob[a_iConn].Affect[sAffect].Value = 1;
		pMob[a_iConn].Affect[sAffect].Level = 500;
		pMob[a_iConn].Affect[sAffect].Time = 100;

		if (pMob[a_iConn].Affect[sAffect].Time >= 324000)
			pMob[a_iConn].Affect[sAffect].Time = 324000;

		pMob[a_iConn].GetCurrentScore(a_iConn);
		SendScore(a_iConn);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		sprintf(temp, "useitem,remedio_da_coragem dam:500");
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);
		return;
	}
#pragma endregion
#pragma region >> Elixir da Coragem
	if (Vol == 230 && (item->sIndex == 647 || item->sIndex == 3378))
	{
		int sAffect = GetEmptyAffect(a_iConn, 30);

		if (sAffect == -1 || pMob[a_iConn].Affect[sAffect].Type == 30 && pMob[a_iConn].Affect[sAffect].Value != 2000)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_CantEatMore]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		pMob[a_iConn].Affect[sAffect].Type = 30;
		pMob[a_iConn].Affect[sAffect].Value = 1;
		pMob[a_iConn].Affect[sAffect].Level = 2000;
		pMob[a_iConn].Affect[sAffect].Time = item->sIndex != 3378 ? AFFECT_1H : AFFECT_1D * 30;

		if (pMob[a_iConn].Affect[sAffect].Time >= 324000)
			pMob[a_iConn].Affect[sAffect].Time = 324000;

		pMob[a_iConn].GetCurrentScore(a_iConn);
		SendScore(a_iConn);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		sprintf(temp, "useitem,elixir_da_coragem dam:2000");
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);
		return;
	}
#pragma endregion
#pragma region >> Frango Assado
	if (Vol == 63 || Vol == 64)
	{
		int sAffect = GetEmptyAffect(a_iConn, 30);

		if (sAffect == -1 || (pMob[a_iConn].Affect[sAffect].Level != 2000 && pMob[a_iConn].Affect[sAffect].Time == 30))
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_CantEatMore]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		pMob[a_iConn].Affect[sAffect].Type = 30;
		pMob[a_iConn].Affect[sAffect].Level = 2000;
		pMob[a_iConn].Affect[sAffect].Value = 0;
		pMob[a_iConn].Affect[sAffect].Time = AFFECT_1H * 4;

		if (pMob[a_iConn].Affect[sAffect].Time >= 324000)
			pMob[a_iConn].Affect[sAffect].Time = 324000;

		pMob[a_iConn].GetCurrentScore(a_iConn);
		SendScore(a_iConn);

		sprintf(temp, "useitem,item frango time %d", pMob[a_iConn].Affect[sAffect].Time);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		return;
	}
#pragma endregion
#pragma region >> Baú Exp
	if (item->sIndex == 4140 || item->sIndex == 4144)
	{
		int sAffect = GetEmptyAffect(a_iConn, 39);

		if (sAffect == -1 || (pMob[a_iConn].Affect[sAffect].Level != 2000 && pMob[a_iConn].Affect[sAffect].Time == 39))
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_CantEatMore]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].Affect[sAffect].Time >= 324000 / 4)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_CantEatMore]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		pMob[a_iConn].Affect[sAffect].Type = 39;
		pMob[a_iConn].Affect[sAffect].Level = 2000;
		pMob[a_iConn].Affect[sAffect].Value = 0;
		pMob[a_iConn].Affect[sAffect].Time += AFFECT_1H * 2;

		if (pMob[a_iConn].Affect[sAffect].Time >= 324000 / 4)
			pMob[a_iConn].Affect[sAffect].Time = 324000 / 4;

		pMob[a_iConn].GetCurrentScore(a_iConn);
		SendScore(a_iConn);

		sprintf(temp, "useitem,item bau exp time %d", pMob[a_iConn].Affect[sAffect].Time);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		return;
	}
#pragma endregion
#pragma region >> Jóias PvP
	if (Vol == 242)
	{
		int sAffect = GetEmptyAffect(a_iConn, 8);

		int joia = 0;

		if (item->sIndex == 3200)
			joia = 0;//Jóia_da_Sagacidade Lv1

		else if (item->sIndex == 3201)
			joia = 1;//Jóia_da_Resistência LV2

		else if (item->sIndex == 3202)
			joia = 2;//Jóia_da_Revelação Lv3

		else if (item->sIndex == 3204)
			joia = 3;//Jóia_da_Absorção Lv4

		else if (item->sIndex == 3205)
			joia = 4;//Jóia_da_Proteção Lv5

		else if (item->sIndex == 3206)
			joia = 5;//Jóia_do_Poder Lv6

		else if (item->sIndex == 3208)
			joia = 6;//Jóia_da_Precisão Lv7

		else if (item->sIndex == 3209)
			joia = 7;//Jóia_da_Magia Lv8

		if (sAffect == -1)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_CantEatMore]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].Affect[sAffect].Type != 8)
		{
			pMob[a_iConn].Affect[sAffect].Type = 8;
			pMob[a_iConn].Affect[sAffect].Level = 1 << joia;
			pMob[a_iConn].Affect[sAffect].Value = 0;
		}

		else if ((pMob[a_iConn].Affect[sAffect].Level & (1 << joia)) == 0)
			pMob[a_iConn].Affect[sAffect].Level |= 1 << joia;

		pMob[a_iConn].Affect[sAffect].Time = AFFECT_1H;
		pMob[a_iConn].GetCurrentScore(a_iConn);
		SendScore(a_iConn);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		sprintf(temp, "useitem,joia_pvp joia:%d", item->sIndex);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);
		return;
	}
#pragma region >> Armazenagem - Recuperação
	if (Vol == 243)
	{
		if (item->sIndex == 3203)
		{
			int flagSkillOff = FALSE;

			for (int k = 0; k < MAX_AFFECT; k++)
			{
				int skillAffectType = pMob[a_iConn].Affect[k].Type;
				if (skillAffectType == 1 || skillAffectType == 3 || skillAffectType == 5 || skillAffectType == 7 || skillAffectType == 10 || skillAffectType == 12 || skillAffectType == 20 || skillAffectType == 32)
				{
					pMob[a_iConn].Affect[k].Type = 0;
					flagSkillOff = TRUE;
				}
			}

			if (flagSkillOff == TRUE)
			{
				pMob[a_iConn].GetCurrentScore(a_iConn);
				SendScore(a_iConn);
			}
		}

		if (item->sIndex == 415)
		{
			int flagSkillOff = FALSE;

			for (int k = 0; k < MAX_AFFECT; k++)
			{
				int skillAffectType = pMob[a_iConn].Affect[k].Type;
				if (skillAffectType == 20 || skillAffectType == 1)
				{
					pMob[a_iConn].Affect[k].Type = 0;
					flagSkillOff = TRUE;
				}
			}

			if (flagSkillOff == TRUE)
			{
				pMob[a_iConn].GetCurrentScore(a_iConn);
				SendScore(a_iConn);
			}
		}

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		sprintf(temp, "useitem,joia_pvp joia:%d", item->sIndex);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);
		return;
	}
#pragma endregion
#pragma endregion

#pragma region >> Itens Click Direito
	if (Vol == 210)
	{
		switch (item->sIndex)
		{
		case KEY_ARIMA:
		case KEY_BARNEL:
		case KEY_CAMPUS:
		case KEY_GOBI:
		case KEY_ICECROW:
		case KEY_ICELAND:
			KeyTerritory(m, item, a_iConn);
			break;
		case 3210:
		case 3211:
		case 3212:
			boxEvent(m, item, a_iConn);
			break;
		case 3213:
			bagWarrior(m, item, a_iConn);
			break;
		case 3790://Contrato Sem Sela N
		case 3791://Contrato Sem Sela B
		case 3792://Contrato Macro eternal 7d
			itemContract(m, item, a_iConn);
			break;
		case 3793:
		case 3794:
			itemJoiasEvent(m, item, a_iConn);
			break;
		default:
			break;
		}
		
	}
#pragma endregion
#pragma region Contratos do reino
	if (Vol >= 41 && Vol < 50)
	{
		int Evock = Vol - 41;

		if (pMob[a_iConn].MOB.Clan != 7 && pMob[a_iConn].MOB.Clan != 8)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Only_same_kingdom]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (Evock < 5 && pMob[a_iConn].MOB.Clan == 8)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Only_same_kingdom]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (Evock >= 5 && pMob[a_iConn].MOB.Clan == 7)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Only_same_kingdom]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

			GenerateSummon(a_iConn, Evock + 40, 0, 1);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		sprintf(temp, "useitem,contrato_de_reino evock:%d", Evock + 28);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);
		return;
	}

#pragma endregion

#pragma region >> Itens Entrada Quests
	if (Vol == 184)
	{
		if (item->sIndex >= VELA && item->sIndex <= EMBLEMA_GUARDA)
			itemEnterQuest(m, item, a_iConn);
	}
#pragma endregion

#pragma region >> Itens de quests
	if (Vol == 191)
	{
		if (pMob[a_iConn].Extra.ClassMaster != MORTAL)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Level_Limit2]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}
		int thisQuest = item->sIndex - 4117;

		int minlevel = pMob[a_iConn].Extra.ClassMaster == MORTAL ? CReadFiles::QuestLevel[thisQuest][0] : CReadFiles::QuestLevel[thisQuest][2];
		int maxlevel = pMob[a_iConn].Extra.ClassMaster == MORTAL ? CReadFiles::QuestLevel[thisQuest][1] : CReadFiles::QuestLevel[thisQuest][3];

		if (pMob[a_iConn].MOB.CurrentScore.Level < minlevel || pMob[a_iConn].MOB.CurrentScore.Level >= maxlevel)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Level_limit]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		struct tm when;
		time_t now;
		time(&now);
		when = *localtime(&now);

		int QuestExp = pMob[a_iConn].Extra.ClassMaster == MORTAL ? CReadFiles::QuestExp[thisQuest][0] : CReadFiles::QuestExp[thisQuest][1];
		int QuestExpParty = QuestExp / 10;

		pMob[a_iConn].MOB.Coin += CReadFiles::QuestCoin[thisQuest];
		pMob[a_iConn].MOB.Exp += QuestExp;

#pragma region Log de Experiência diário
		if (when.tm_yday != pMob[a_iConn].Extra.DayLog.YearDay)
			pMob[a_iConn].Extra.DayLog.Exp = 0;

		pMob[a_iConn].Extra.DayLog.YearDay = when.tm_yday;
		pMob[a_iConn].Extra.DayLog.Exp += QuestExp;
#pragma endregion

		if (pMob[a_iConn].MOB.Coin > 2000000000)
			pMob[a_iConn].MOB.Coin = 2000000000;

		sprintf(temp, g_pMessageStringTable[_NS_GETEXP], pMob[a_iConn].Extra.ClassMaster == MORTAL ? CReadFiles::QuestExp[thisQuest][0] : CReadFiles::QuestExp[thisQuest][1]);
		SendMsgExp(a_iConn, temp, TNColor::Default, false);

		SendEmotion(a_iConn, 14, 3);

		if (pMob[a_iConn].CheckGetLevel() == 4)
		{
			int PKPoint = GetPKPoint(a_iConn) + 5;
			SetPKPoint(a_iConn, PKPoint);

			SetCircletSubGod(a_iConn);
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Level_Up]);
			SendScore(a_iConn);
			TitleNotification(a_iConn, pMob[a_iConn].MOB.CurrentScore.Level);

			if (pMob[a_iConn].Extra.ClassMaster == MORTAL)
				DoItemLevel(a_iConn);
		}

		SendEtc(a_iConn);
		SendScore(a_iConn);

		int partyleader = pMob[a_iConn].Leader;

		if (partyleader <= 0)
			partyleader = a_iConn;

		if (partyleader >= MAX_USER)
			partyleader = a_iConn;

		if (partyleader != a_iConn && (pMob[partyleader].Extra.ClassMaster == MORTAL)
			&& pMob[partyleader].MOB.CurrentScore.Level < 370)
		{
			pMob[partyleader].MOB.Exp += QuestExpParty;

			sprintf(temp, g_pMessageStringTable[_NS_GETEXP], QuestExpParty);
			SendMsgExp(partyleader, temp, TNColor::Default, false);


#pragma region Log de Experiência diário
			if (when.tm_yday != pMob[partyleader].Extra.DayLog.YearDay)
				pMob[partyleader].Extra.DayLog.Exp = 0;

			pMob[partyleader].Extra.DayLog.YearDay = when.tm_yday;
			pMob[partyleader].Extra.DayLog.Exp += QuestExpParty;
#pragma endregion

			SendEmotion(partyleader, 14, 3);

			if (pMob[partyleader].CheckGetLevel() == 4)
			{
				int PKPoint = GetPKPoint(partyleader) + 5;
				SetPKPoint(partyleader, PKPoint);

				SetCircletSubGod(partyleader);
				SendClientMsg(partyleader, g_pMessageStringTable[_NN_Level_Up]);
				SendScore(partyleader);
				TitleNotification(partyleader, pMob[partyleader].MOB.CurrentScore.Level);

				if (pMob[partyleader].Extra.ClassMaster == MORTAL)
					DoItemLevel(partyleader);
			}

			SendEtc(partyleader);
			SendScore(partyleader);
		}

		for (int i = 0; i < MAX_PARTY; i++)
		{
			int partymember = pMob[partyleader].PartyList[i];

			if (partymember <= 0 || partymember >= MAX_USER)
				continue;

			if (pUser[partymember].Mode != USER_PLAY || partymember == a_iConn)
				continue;

			if (partymember != a_iConn && (pMob[partymember].Extra.ClassMaster == MORTAL)
				&& pMob[partymember].MOB.CurrentScore.Level < 370)
			{
				pMob[partymember].MOB.Exp += QuestExpParty;

#pragma region Log de Experiência diário
				if (when.tm_yday != pMob[partymember].Extra.DayLog.YearDay)
					pMob[partymember].Extra.DayLog.Exp = 0;

				pMob[partymember].Extra.DayLog.YearDay = when.tm_yday;
				pMob[partymember].Extra.DayLog.Exp += QuestExpParty;
#pragma endregion

				sprintf(temp, g_pMessageStringTable[_NS_GETEXP], QuestExpParty);
				SendMsgExp(partymember, temp, TNColor::Default, false);

				SendEmotion(partymember, 14, 3);

				if (pMob[partymember].CheckGetLevel() == 4)
				{
					int PKPoint = GetPKPoint(partymember) + 5;
					SetPKPoint(partymember, PKPoint);

					SetCircletSubGod(partymember);
					SendClientMsg(partymember, g_pMessageStringTable[_NN_Level_Up]);
					SendScore(partymember);
					TitleNotification(partymember, pMob[partymember].MOB.CurrentScore.Level);

					if (pMob[partymember].Extra.ClassMaster == MORTAL)
						DoItemLevel(partymember);
				}

				SendEtc(partymember);
				SendScore(partymember);

			}
		}
		sprintf(temp, "useitem,%s level:%d classmaster:%d", g_pItemList[item->sIndex].Name, pMob[a_iConn].MOB.BaseScore.Level, pMob[a_iConn].Extra.ClassMaster);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		SendItem(a_iConn, m->SourType, m->SourPos, item);
		return;
	}
#pragma endregion
#pragma region >> Molar do Gargula
	if (Vol == 194)
	{
		if (pMob[a_iConn].Extra.ClassMaster != MORTAL)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Level_Limit2]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].MOB.CurrentScore.Level < 200 || pMob[a_iConn].MOB.CurrentScore.Level >= 204)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Level_limit]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].Extra.QuestInfo.Mortal.MolarGargula)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Youve_Done_It_Already]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		for (int i = 1; i < 6; i++)
		{
			if (pMob[a_iConn].MOB.Equip[i].sIndex == 0)
				continue;

			int sanc = BASE_GetItemSanc(&pMob[a_iConn].MOB.Equip[i]);

			if (sanc < 6)
			{
				BASE_SetItemSanc(&pMob[a_iConn].MOB.Equip[i], 6, 0);
				SendItem(a_iConn, ITEM_PLACE_EQUIP, i, &pMob[a_iConn].MOB.Equip[i]);
			}
		}
		pMob[a_iConn].Extra.QuestInfo.Mortal.MolarGargula = 1;
		pMob[a_iConn].GetCurrentScore(a_iConn);

		sprintf(temp, g_pMessageStringTable[_DN_Play_Quest], "Molar do Gargula");
		SendClientMsg(a_iConn, temp);

		sprintf(temp, "useitem,itemquest molar %d", pMob[a_iConn].Extra.QuestInfo.Mortal.MolarGargula);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		return;
	}
#pragma endregion
#pragma region >> Cristal - Elime / Sylphed / Thelion / Noas
	if (Vol == 187)
	{
		if (pMob[a_iConn].Extra.ClassMaster != ARCH)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].MOB.CurrentScore.Level < 355)
		{
			sprintf(temp, g_pMessageStringTable[_DN_Level_Limit], 356);
			SendClientMsg(a_iConn, temp);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int quest = item->sIndex - 4106 + 1;

		if (pMob[a_iConn].Extra.QuestInfo.Arch.Cristal == quest)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Youve_Done_It_Already]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].Extra.QuestInfo.Arch.Cristal >= quest)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Youve_Done_It_Already]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].Extra.QuestInfo.Arch.Cristal != quest - 1)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Need_BeforeQuest]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		pMob[a_iConn].Extra.QuestInfo.Arch.Cristal = quest;

		if (quest == 1)
			pMob[a_iConn].MOB.BaseScore.MaxMp += 80;

		else if (quest == 2)
			pMob[a_iConn].MOB.BaseScore.Ac += 30;

		else if (quest == 3)
			pMob[a_iConn].MOB.BaseScore.MaxHp += 80;

		else
		{
			pMob[a_iConn].MOB.BaseScore.MaxHp += 60;
			pMob[a_iConn].MOB.BaseScore.MaxMp += 60;
			pMob[a_iConn].MOB.BaseScore.Ac += 30;
		}

		pMob[a_iConn].MOB.Exp -= 100000000;

		int newlevel = 0;

		for (int i = 0; i < MAX_LEVEL; i++)
		{
			if (pMob[a_iConn].MOB.Exp >= g_pNextLevel[i] && pMob[a_iConn].MOB.Exp <= g_pNextLevel[i + 1])
				newlevel = i;
		}

		pMob[a_iConn].MOB.BaseScore.Level = newlevel;
		int check = pMob[a_iConn].CheckGetLevel();

		if (check == 4)
			SetCircletSubGod(a_iConn);

		BASE_GetBonusScorePoint(&pMob[a_iConn].MOB, &pMob[a_iConn].Extra);

		pMob[a_iConn].GetCurrentScore(a_iConn);
		SendEtc(a_iConn);
		SendScore(a_iConn);

		SendEmotion(a_iConn, 14, 3);

		sprintf(temp, g_pMessageStringTable[_DN_Play_Quest], g_pItemList[item->sIndex].Name);
		SendClientMsg(a_iConn, temp);

		sprintf(temp, "useitem,archcristal complete etapa:%d", quest);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);
		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		return;
	}
#pragma endregion
#pragma region >> Barra de Prata
	if (Vol == 185)
	{
		int gold = 0;

		if (item->sIndex == 4010)
			gold = 100000000;

		else if (item->sIndex == 4011)
			gold = 1000000000;

		else if (item->sIndex == 4026)
			gold = 1000000;

		else if (item->sIndex == 4027)
			gold = 5000000;

		else if (item->sIndex == 4028)
			gold = 10000000;

		else if (item->sIndex == 4029)
			gold = 50000000;

		unsigned int fGold = pMob[a_iConn].MOB.Coin + gold;

		if (fGold > 2000000000)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_get_more_than_2G]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		pMob[a_iConn].MOB.Coin = fGold;
		SendEtc(a_iConn);
		SendEmotion(a_iConn, 14, 3);

		sprintf(temp, "useitem,silver coin used V:%d fV:%d", gold, fGold);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		return;
	}
#pragma endregion
#pragma region >> Bolsa do Andarilho
	if (item->sIndex == 3467)
	{
		if (pMob[a_iConn].MOB.Carry[60].sIndex == 3467 && pMob[a_iConn].MOB.Carry[61].sIndex == 3467)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_MAX_BAG]);
			return;
		}

		if (pMob[a_iConn].MOB.Carry[60].sIndex != 3467)
		{
			pMob[a_iConn].MOB.Carry[60].sIndex = 3467;
			BASE_SetItemDate(&pMob[a_iConn].MOB.Carry[60], 30);
			SendCarry(a_iConn);
		}
		else
		{
			pMob[a_iConn].MOB.Carry[61].sIndex = 3467;
			BASE_SetItemDate(&pMob[a_iConn].MOB.Carry[61], 30);
			SendCarry(a_iConn);
		}

		SendScore(a_iConn);
		SendEtc(a_iConn);

		pMob[a_iConn].MaxCarry = 30;

		if (pMob[a_iConn].MOB.Carry[60].sIndex == 3467)
			pMob[a_iConn].MaxCarry += 15;

		if (pMob[a_iConn].MOB.Carry[61].sIndex == 3467)
			pMob[a_iConn].MaxCarry += 15;

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		SendCarry(a_iConn);

		return;
	}
#pragma endregion
#pragma region >> Extração Elmo
	if (item->sIndex == 3021)
	{
		int Extra = BASE_GetItemAbility(item, EF_ITEMLEVEL);

		if (pMob[a_iConn].MOB.Equip[1].sIndex == 0)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			SendClientMsg(a_iConn, "Equipe um Elmo e tente novamente");
			return;
		}

		if (pMob[a_iConn].MOB.Equip[1].sIndex >= 3500 && pMob[a_iConn].MOB.Equip[1].sIndex <= 3507)
		{
			SendClientMsg(a_iConn, "Não é possivel utilizar em Cytheras.");
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (Extra <= 5)
		{
			int destExtra = BASE_GetItemAbility(&pMob[a_iConn].MOB.Equip[1], EF_ITEMLEVEL);
			int desttype = BASE_GetItemAbility(&pMob[a_iConn].MOB.Equip[1], EF_MOBTYPE);

			if (/*destExtra != 0 || */ destExtra != Extra || (desttype != 2 && desttype != 0 && desttype != 1))
			{
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				SendClientMsg(a_iConn, "Item equipado incompativel com a extração!!");
				return;
			}

			int sanc = BASE_GetItemSanc(&pMob[a_iConn].MOB.Equip[1]);

			if (Extra == 5 && sanc != REF_11)
			{
				sprintf(temp, g_pMessageStringTable[_DN_SANCREQ], 11);
				SendClientMsg(a_iConn, temp);
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				return;
			}
			else if (Extra <= 4 && sanc > 9)
			{
				sprintf(temp, g_pMessageStringTable[_DN_SANCREQ], 9);
				SendClientMsg(a_iConn, temp);
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				return;
			}

			pMob[a_iConn].MOB.Equip[1].stEffect[1].cEffect = item->stEffect[1].cEffect;
			pMob[a_iConn].MOB.Equip[1].stEffect[1].cValue = item->stEffect[1].cValue;

			pMob[a_iConn].MOB.Equip[1].stEffect[2].cEffect = item->stEffect[2].cEffect;
			pMob[a_iConn].MOB.Equip[1].stEffect[2].cValue = item->stEffect[2].cValue;

			SendItem(a_iConn, ITEM_PLACE_EQUIP, 1, &pMob[a_iConn].MOB.Equip[1]);

			sprintf(temp, "useitem,Extracao elmo: %d-%d:%d:%d:%d:%d:%d", item->sIndex, item->stEffect[0].cEffect, item->stEffect[0].cValue, item->stEffect[1].cEffect, item->stEffect[1].cValue, item->stEffect[2].cEffect, item->stEffect[2].cValue);
			MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);

			if (amount > 1)
				BASE_SetItemAmount(item, amount - 1);

			else
				memset(item, 0, sizeof(STRUCT_ITEM));

			SendEmotion(a_iConn, 14, 3);
			return;
		}
	}

#pragma endregion
#pragma region >> Extração Peito
	if (item->sIndex == 3022)
	{
		int Extra = BASE_GetItemAbility(item, EF_ITEMLEVEL);

		if (pMob[a_iConn].MOB.Equip[2].sIndex == 0)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			SendClientMsg(a_iConn, "Equipe um Peitoral e tente novamente");
			return;
		}

		if (Extra <= 5)
		{
			int destExtra = BASE_GetItemAbility(&pMob[a_iConn].MOB.Equip[2], EF_ITEMLEVEL);
			int desttype = BASE_GetItemAbility(&pMob[a_iConn].MOB.Equip[2], EF_MOBTYPE);

			if (/*destExtra != 0 ||*/ destExtra != Extra || (desttype != 2 && desttype != 0 && desttype != 1))
			{
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				SendClientMsg(a_iConn, "Item equipado incompativel com a extração!!");
				return;
			}

			int sanc = BASE_GetItemSanc(&pMob[a_iConn].MOB.Equip[2]);

			if (Extra == 5 && sanc != REF_11)
			{
				sprintf(temp, g_pMessageStringTable[_DN_SANCREQ], 11);
				SendClientMsg(a_iConn, temp);
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				return;
			}

			else if (Extra <= 4 && sanc > 9)
			{
				sprintf(temp, g_pMessageStringTable[_DN_SANCREQ], 9);
				SendClientMsg(a_iConn, temp);
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				return;
			}

			pMob[a_iConn].MOB.Equip[2].stEffect[1].cEffect = item->stEffect[1].cEffect;
			pMob[a_iConn].MOB.Equip[2].stEffect[1].cValue = item->stEffect[1].cValue;

			pMob[a_iConn].MOB.Equip[2].stEffect[2].cEffect = item->stEffect[2].cEffect;
			pMob[a_iConn].MOB.Equip[2].stEffect[2].cValue = item->stEffect[2].cValue;

			SendItem(a_iConn, ITEM_PLACE_EQUIP, 2, &pMob[a_iConn].MOB.Equip[2]);

			sprintf(temp, "useitem,Extracao peito: %d-%d:%d:%d:%d:%d:%d", item->sIndex, item->stEffect[0].cEffect, item->stEffect[0].cValue, item->stEffect[1].cEffect, item->stEffect[1].cValue, item->stEffect[2].cEffect, item->stEffect[2].cValue);
			MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);

			if (amount > 1)
				BASE_SetItemAmount(item, amount - 1);

			else
				memset(item, 0, sizeof(STRUCT_ITEM));

			SendEmotion(a_iConn, 14, 3);
			return;
		}
	}
#pragma endregion
#pragma region >> Extração Calça
	if (item->sIndex == 3023)
	{
		int Extra = BASE_GetItemAbility(item, EF_ITEMLEVEL);

		if (pMob[a_iConn].MOB.Equip[3].sIndex == 0)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			SendClientMsg(a_iConn, "Equipe uma Calça e tente novamente");
			return;
		}
		if (Extra <= 5)
		{
			int destExtra = BASE_GetItemAbility(&pMob[a_iConn].MOB.Equip[3], EF_ITEMLEVEL);
			int desttype = BASE_GetItemAbility(&pMob[a_iConn].MOB.Equip[3], EF_MOBTYPE);

			if (/*destExtra != 0 || */ destExtra != Extra || (desttype != 2 && desttype != 0 && desttype != 1))
			{
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				SendClientMsg(a_iConn, "Item equipado incompativel com a extração!!");
				return;
			}

			int sanc = BASE_GetItemSanc(&pMob[a_iConn].MOB.Equip[3]);

			if (Extra == 5 && sanc != REF_11)
			{
				sprintf(temp, g_pMessageStringTable[_DN_SANCREQ], 11);
				SendClientMsg(a_iConn, temp);
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				return;
			}

			else if (Extra <= 4 && sanc > 9)
			{
				sprintf(temp, g_pMessageStringTable[_DN_SANCREQ], 9);
				SendClientMsg(a_iConn, temp);
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				return;
			}

			pMob[a_iConn].MOB.Equip[3].stEffect[1].cEffect = item->stEffect[1].cEffect;
			pMob[a_iConn].MOB.Equip[3].stEffect[1].cValue = item->stEffect[1].cValue;

			pMob[a_iConn].MOB.Equip[3].stEffect[2].cEffect = item->stEffect[2].cEffect;
			pMob[a_iConn].MOB.Equip[3].stEffect[2].cValue = item->stEffect[2].cValue;

			SendItem(a_iConn, ITEM_PLACE_EQUIP, 3, &pMob[a_iConn].MOB.Equip[3]);

			sprintf(temp, "useitem,Extracao calça: %d-%d:%d:%d:%d:%d:%d", item->sIndex, item->stEffect[0].cEffect, item->stEffect[0].cValue, item->stEffect[1].cEffect, item->stEffect[1].cValue, item->stEffect[2].cEffect, item->stEffect[2].cValue);
			MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);

			if (amount > 1)
				BASE_SetItemAmount(item, amount - 1);

			else
				memset(item, 0, sizeof(STRUCT_ITEM));

			SendEmotion(a_iConn, 14, 3);
			return;
		}
	}
#pragma endregion
#pragma region >> Extração Luva
	if (item->sIndex == 3024)
	{
		int Extra = BASE_GetItemAbility(item, EF_ITEMLEVEL);

		if (pMob[a_iConn].MOB.Equip[4].sIndex == 0)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			SendClientMsg(a_iConn, "Equipe uma Luva e tente novamente");
			return;
		}

		if (Extra <= 5)
		{
			int destExtra = BASE_GetItemAbility(&pMob[a_iConn].MOB.Equip[4], EF_ITEMLEVEL);
			int desttype = BASE_GetItemAbility(&pMob[a_iConn].MOB.Equip[4], EF_MOBTYPE);

			if (/*destExtra != 0 || */ destExtra != Extra || (desttype != 2 && desttype != 0 && desttype != 1))
			{
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				SendClientMsg(a_iConn, "Item equipado incompativel com a extração!!");
				return;
			}

			int sanc = BASE_GetItemSanc(&pMob[a_iConn].MOB.Equip[4]);

			if (Extra == 5 && sanc != REF_11)
			{
				sprintf(temp, g_pMessageStringTable[_DN_SANCREQ], 11);
				SendClientMsg(a_iConn, temp);
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				return;
			}

			else if (Extra <= 4 && sanc > 9)
			{
				sprintf(temp, g_pMessageStringTable[_DN_SANCREQ], 9);
				SendClientMsg(a_iConn, temp);
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				return;
			}

			pMob[a_iConn].MOB.Equip[4].stEffect[1].cEffect = item->stEffect[1].cEffect;
			pMob[a_iConn].MOB.Equip[4].stEffect[1].cValue = item->stEffect[1].cValue;

			pMob[a_iConn].MOB.Equip[4].stEffect[2].cEffect = item->stEffect[2].cEffect;
			pMob[a_iConn].MOB.Equip[4].stEffect[2].cValue = item->stEffect[2].cValue;

			SendItem(a_iConn, ITEM_PLACE_EQUIP, 4, &pMob[a_iConn].MOB.Equip[4]);

			sprintf(temp, "useitem,Extracao luva: %d-%d:%d:%d:%d:%d:%d", item->sIndex, item->stEffect[0].cEffect, item->stEffect[0].cValue, item->stEffect[1].cEffect, item->stEffect[1].cValue, item->stEffect[2].cEffect, item->stEffect[2].cValue);
			MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);

			if (amount > 1)
				BASE_SetItemAmount(item, amount - 1);

			else
				memset(item, 0, sizeof(STRUCT_ITEM));

			SendEmotion(a_iConn, 14, 3);
			return;
		}
	}
#pragma endregion
#pragma region >> Extração Bota
	if (item->sIndex == 3025)
	{
		int Extra = BASE_GetItemAbility(item, EF_ITEMLEVEL);

		if (pMob[a_iConn].MOB.Equip[5].sIndex == 0)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			SendClientMsg(a_iConn, "Equipe uma Bota e tente novamente");
			return;
		}

		if (Extra <= 5)
		{
			int destExtra = BASE_GetItemAbility(&pMob[a_iConn].MOB.Equip[5], EF_ITEMLEVEL);
			int desttype = BASE_GetItemAbility(&pMob[a_iConn].MOB.Equip[5], EF_MOBTYPE);

			if (/*destExtra != 0 || */ destExtra != Extra || (desttype != 2 && desttype != 0 && desttype != 1))
			{
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				SendClientMsg(a_iConn, "Item equipado incompativel com a extração!!");
				return;
			}

			int sanc = BASE_GetItemSanc(&pMob[a_iConn].MOB.Equip[5]);

			if (Extra == 5 && sanc != REF_11)
			{
				sprintf(temp, g_pMessageStringTable[_DN_SANCREQ], 11);
				SendClientMsg(a_iConn, temp);
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				return;
			}

			else if (Extra <= 4 && sanc > 9)
			{
				sprintf(temp, g_pMessageStringTable[_DN_SANCREQ], 9);
				SendClientMsg(a_iConn, temp);
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				return;
			}

			pMob[a_iConn].MOB.Equip[5].stEffect[1].cEffect = item->stEffect[1].cEffect;
			pMob[a_iConn].MOB.Equip[5].stEffect[1].cValue = item->stEffect[1].cValue;

			pMob[a_iConn].MOB.Equip[5].stEffect[2].cEffect = item->stEffect[2].cEffect;
			pMob[a_iConn].MOB.Equip[5].stEffect[2].cValue = item->stEffect[2].cValue;

			if (pMob[a_iConn].MOB.Equip[5].stEffect[1].cEffect == EF_DAMAGE && BASE_GetStaticItemAbility(&pMob[a_iConn].MOB.Equip[5], EF_DAMAGE) != 0)
				pMob[a_iConn].MOB.Equip[5].stEffect[1].cValue -= BASE_GetStaticItemAbility(&pMob[a_iConn].MOB.Equip[5], EF_DAMAGE);

			if (pMob[a_iConn].MOB.Equip[5].stEffect[2].cEffect == EF_DAMAGE && BASE_GetStaticItemAbility(&pMob[a_iConn].MOB.Equip[5], EF_DAMAGE) != 0)
				pMob[a_iConn].MOB.Equip[5].stEffect[2].cValue -= BASE_GetStaticItemAbility(&pMob[a_iConn].MOB.Equip[5], EF_DAMAGE);

			SendItem(a_iConn, ITEM_PLACE_EQUIP, 5, &pMob[a_iConn].MOB.Equip[5]);

			sprintf(temp, "useitem,Extracao bota: %d-%d:%d:%d:%d:%d:%d", item->sIndex, item->stEffect[0].cEffect, item->stEffect[0].cValue, item->stEffect[1].cEffect, item->stEffect[1].cValue, item->stEffect[2].cEffect, item->stEffect[2].cValue);
			MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);

			if (amount > 1)
				BASE_SetItemAmount(item, amount - 1);

			else
				memset(item, 0, sizeof(STRUCT_ITEM));

			SendEmotion(a_iConn, 14, 3);
			return;
		}
	}
#pragma endregion

#pragma region Extração Arma
	if (item->sIndex == 3026)
	{
		int Extra = BASE_GetItemAbility(item, EF_ITEMLEVEL);

		if (pMob[a_iConn].MOB.Equip[6].sIndex == 0)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			SendClientMsg(a_iConn, "Equipe uma arma e tente novamente");
			return;
		}

		if (Extra <= 6)
		{
			int destextra = BASE_GetItemAbility(&pMob[a_iConn].MOB.Equip[6], EF_ITEMLEVEL);
			int desttype = BASE_GetItemAbility(&pMob[a_iConn].MOB.Equip[6], EF_MOBTYPE);

			if (destextra == 0 || destextra != Extra || (desttype != 0 && desttype != 1))
			{
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				SendClientMsg(a_iConn, "Item equipado incompativel com a extração!!");
				return;
			}

			int sanc = BASE_GetItemSanc(&pMob[a_iConn].MOB.Equip[6]);

			if (Extra == 6 && sanc != REF_11)
			{
				sprintf(temp, g_pMessageStringTable[_DN_SANCREQ], 11);
				SendClientMsg(a_iConn, temp);
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				return;
			}

			else if (Extra <= 4 && sanc > 9)
			{
				sprintf(temp, g_pMessageStringTable[_DN_SANCREQ], 9);
				SendClientMsg(a_iConn, temp);
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				return;
			}

			pMob[a_iConn].MOB.Equip[6].stEffect[1].cEffect = item->stEffect[1].cEffect;
			pMob[a_iConn].MOB.Equip[6].stEffect[1].cValue = item->stEffect[1].cValue;

			pMob[a_iConn].MOB.Equip[6].stEffect[2].cEffect = item->stEffect[2].cEffect;
			pMob[a_iConn].MOB.Equip[6].stEffect[2].cValue = item->stEffect[2].cValue;

			SendItem(a_iConn, ITEM_PLACE_EQUIP, 6, &pMob[a_iConn].MOB.Equip[6]);

			sprintf(temp, "useitem,Extracao arma: %d-%d:%d:%d:%d:%d:%d", item->sIndex, item->stEffect[0].cEffect, item->stEffect[0].cValue, item->stEffect[1].cEffect, item->stEffect[1].cValue, item->stEffect[2].cEffect, item->stEffect[2].cValue);
			MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);

			if (amount > 1)
				BASE_SetItemAmount(item, amount - 1);

			else
				memset(item, 0, sizeof(STRUCT_ITEM));

			SendEmotion(a_iConn, 14, 3);
			return;
		}
		
		return;
	}
#pragma region >> Barra Mytril (Dano)
	if (Vol == 235)
	{
		STRUCT_ITEM *dest = GetItemPointer(&pMob[a_iConn].MOB, pUser[a_iConn].Cargo, m->DestType, m->DestPos);

		if (dest == NULL)
			return;

		if (m->DestType || m->DestPos >= 8 && m->DestPos < 16 || m->DestType == ITEM_PLACE_EQUIP && m->DestPos == 0 || m->DestType == ITEM_PLACE_EQUIP && m->DestPos == 1)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Only_To_Equips]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int sanc = BASE_GetItemSanc(dest);
		int ItemId = dest->sIndex;

		if (sanc < REF_11 || BASE_GetItemAbility(dest, EF_MOBTYPE) != 1)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		for (int a = 0; a < 3; a++)
		{
			if (dest->stEffect[a].cEffect == EF_DAMAGE || dest->stEffect[a].cEffect == EF_DAMAGE2)
			{
				dest->stEffect[a].cEffect = EF_DAMAGE;
				if (dest->stEffect[a].cValue < (m->DestPos != 6 && m->DestPos != 7 ? 12 : 45))
				{
					SendClientMsg(a_iConn, "Não é possível aprimorar este item.");
					SendItem(a_iConn, m->SourType, m->SourPos, item);
					return;
				}
			}
		}

		for (int b = 0; b < 3; b++)
		{
			if (dest->stEffect[b].cEffect == EF_DAMAGE || dest->stEffect[b].cEffect == EF_DAMAGE2)
			{
				dest->stEffect[b].cEffect = EF_DAMAGE;
				if (dest->stEffect[b].cValue == (m->DestPos != 6 && m->DestPos != 7 ? 42 : 81))
				{
					SendClientMsg(a_iConn, "Não é possível aprimorar este item.");
					SendItem(a_iConn, m->SourType, m->SourPos, item);
					return;
				}
			}
		}


		int RateSucess = 30;
		int _rand = rand() % 115;
		if (_rand > 100)
			_rand -= 15;

		if (_rand <= RateSucess && RateSucess)
		{
			for (int i = 0; i < 3; i++)
			{
				if (dest->stEffect[i].cEffect == EF_DAMAGE || dest->stEffect[i].cEffect == EF_DAMAGE2)
				{
					dest->stEffect[i].cEffect = EF_DAMAGE;
					dest->stEffect[i].cValue += m->DestPos != 6 && m->DestPos != 7 ? 6 : 9;

					if (dest->stEffect[i].cValue >(m->DestPos != 6 && m->DestPos != 7 ? 42 : 81))
						dest->stEffect[i].cValue = (m->DestPos != 6 && m->DestPos != 7 ? 42 : 81);

					break;
				}
			}

			pMob[a_iConn].GetCurrentScore(a_iConn);
			SendScore(a_iConn);
			SendClientMsg(a_iConn, "Upgrade +");

			sprintf(temp, "useitem,upgrade success %d+%d - (%d,%d,%d)", dest->sIndex, sanc, item->stEffect[0].cEffect, item->stEffect[1].cEffect, item->stEffect[2].cEffect);

			if (amount > 1)
				BASE_SetItemAmount(item, amount - 1);

			else
				memset(item, 0, sizeof(STRUCT_ITEM));

			SendItem(a_iConn, m->DestType, m->DestPos, dest);
			SendEmotion(a_iConn, 14, 3);
		}

		else
		{
			if ((rand() % 7) == 0)
			{
				for (int i = 0; i < 3; i++)
				{
					if (dest->stEffect[i].cEffect == EF_DAMAGE || dest->stEffect[i].cEffect == EF_DAMAGE2)
					{
						dest->stEffect[i].cEffect = EF_DAMAGE;

						if (dest->stEffect[i].cValue >= (m->DestPos != 6 && m->DestPos != 7 ? 6 : 9))
							dest->stEffect[i].cValue -= m->DestPos != 6 && m->DestPos != 7 ? 6 : 9;

						break;
					}
				}

				sprintf(temp, "useitem,upgrade fail-- %d+%d - (%d,%d,%d)", dest->sIndex, sanc, item->stEffect[0].cEffect, item->stEffect[1].cEffect, item->stEffect[2].cEffect);

				SendClientMsg(a_iConn, "Upgrade -");
				SendItem(a_iConn, m->DestType, m->DestPos, dest);
				SendEmotion(a_iConn, 14, 3);
			}
			else
			{
				sprintf(temp, "useitem,upgrade fail %d+%d - (%d,%d,%d)", dest->sIndex, sanc, item->stEffect[0].cEffect, item->stEffect[1].cEffect, item->stEffect[2].cEffect);
				SendClientMsg(a_iConn, "O upgrade do item falhou.");

				int sFace = pMob[a_iConn].MOB.Equip[0].sIndex / 10;

				if (sFace)
					SendEmotion(a_iConn, 15, 0);

				else
					SendEmotion(a_iConn, 20, 0);
			}

			MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);

			if (amount > 1)
				BASE_SetItemAmount(item, amount - 1);

			else
				memset(item, 0, sizeof(STRUCT_ITEM));
		}

		return;
	}
#pragma endregion
#pragma region >> Barra Mytril (Magia)
	if (Vol == 236)
	{
		STRUCT_ITEM *dest = GetItemPointer(&pMob[a_iConn].MOB, pUser[a_iConn].Cargo, m->DestType, m->DestPos);

		if (dest == NULL)
			return;


		if (m->DestType || m->DestPos >= 8 && m->DestPos < 16 || m->DestType == ITEM_PLACE_EQUIP && m->DestPos == 0 || m->DestType == ITEM_PLACE_EQUIP && m->DestPos == 1)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Only_To_Equips]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int sanc = BASE_GetItemSanc(dest);
		int ItemId = dest->sIndex;

		if (sanc < REF_11 || BASE_GetItemAbility(dest, EF_MOBTYPE) != 1)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		for (int a = 0; a < 3; a++)
		{
			if (dest->stEffect[a].cEffect == EF_MAGIC || dest->stEffect[a].cEffect == EF_MAGICADD)
			{
				dest->stEffect[a].cEffect = EF_MAGIC;
				if (dest->stEffect[a].cValue < (m->DestPos != 6 && m->DestPos != 7 ? 6 : 20))
				{
					SendClientMsg(a_iConn, "Não é possível aprimorar este item.");
					SendItem(a_iConn, m->SourType, m->SourPos, item);
					return;
				}
			}
		}


		for (int b = 0; b < 3; b++)
		{
			if (dest->stEffect[b].cEffect == EF_MAGIC || dest->stEffect[b].cEffect == EF_MAGICADD)
			{
				dest->stEffect[b].cEffect = EF_MAGIC;
				if (dest->stEffect[b].cValue == (m->DestPos != 6 && m->DestPos != 7 ? 14 : 36))
				{
					SendClientMsg(a_iConn, "Não é possível aprimorar este item.");
					SendItem(a_iConn, m->SourType, m->SourPos, item);
					return;
				}
			}
		}


		int RateSucess = 30;
		int _rand = rand() % 115;
		if (_rand > 100)
			_rand -= 15;

		if (_rand <= RateSucess && RateSucess)
		{
			for (int i = 0; i < 3; i++)
			{
				if (dest->stEffect[i].cEffect == EF_MAGIC || dest->stEffect[i].cEffect == EF_MAGICADD)
				{
					dest->stEffect[i].cEffect = EF_MAGIC;
					dest->stEffect[i].cValue += m->DestPos != 6 && m->DestPos != 7 ? 2 : 4;

					if (dest->stEffect[i].cValue >(m->DestPos != 6 && m->DestPos != 7 ? 14 : 36))
						dest->stEffect[i].cValue = (m->DestPos != 6 && m->DestPos != 7 ? 14 : 36);

					break;
				}
			}

			pMob[a_iConn].GetCurrentScore(a_iConn);
			SendClientMsg(a_iConn, "Upgrade +");
			SendScore(a_iConn);

			sprintf(temp, "useitem,upgrade success %d+%d - (%d,%d,%d)", dest->sIndex, sanc, item->stEffect[0].cEffect, item->stEffect[1].cEffect, item->stEffect[2].cEffect);

			if (amount > 1)
				BASE_SetItemAmount(item, amount - 1);

			else
				memset(item, 0, sizeof(STRUCT_ITEM));

			SendItem(a_iConn, m->DestType, m->DestPos, dest);
			SendEmotion(a_iConn, 14, 3);
		}

		else
		{
			if ((rand() % 7) == 0)
			{
				for (int i = 0; i < 3; i++)
				{
					if (dest->stEffect[i].cEffect == EF_MAGIC || dest->stEffect[i].cEffect == EF_MAGICADD)
					{
						dest->stEffect[i].cEffect = EF_MAGIC;

						if (dest->stEffect[i].cValue >(m->DestPos != 6 && m->DestPos != 7 ? 2 : 4))
							dest->stEffect[i].cValue -= m->DestPos != 6 && m->DestPos != 7 ? 2 : 4;

						break;
					}
				}
				sprintf(temp, "useitem,upgrade fail-- %d+%d - (%d,%d,%d)", dest->sIndex, sanc, item->stEffect[0].cEffect, item->stEffect[1].cEffect, item->stEffect[2].cEffect);

				SendClientMsg(a_iConn, "Upgrade -");
				SendItem(a_iConn, m->DestType, m->DestPos, dest);
				SendEmotion(a_iConn, 14, 3);
			}
			else
			{
				sprintf(temp, "useitem,upgrade fail %d+%d - (%d,%d,%d)", dest->sIndex, sanc, item->stEffect[0].cEffect, item->stEffect[1].cEffect, item->stEffect[2].cEffect);

				SendClientMsg(a_iConn, "O upgrade do item falhou.");
				int sFace = pMob[a_iConn].MOB.Equip[0].sIndex / 10;

				if (sFace)
					SendEmotion(a_iConn, 15, 0);

				else
					SendEmotion(a_iConn, 20, 0);
			}

			MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);

			if (amount > 1)
				BASE_SetItemAmount(item, amount - 1);

			else
				memset(item, 0, sizeof(STRUCT_ITEM));
		}

		return;
	}
#pragma endregion
#pragma region >> Barra Mytril (Defesa)
	if (Vol == 237)
	{
		STRUCT_ITEM *dest = GetItemPointer(&pMob[a_iConn].MOB, pUser[a_iConn].Cargo, m->DestType, m->DestPos);

		if (dest == NULL)
			return;


		if (m->DestType || m->DestPos >= 6 && m->DestPos < 16 || m->DestType == ITEM_PLACE_EQUIP && m->DestPos == 0 || m->DestType == ITEM_PLACE_EQUIP && m->DestPos == 1)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Only_To_Equips]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (dest->sIndex >= 3500 && dest->sIndex <= 3507)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int sanc = BASE_GetItemSanc(dest);
		int ItemId = dest->sIndex;

		if (sanc < REF_11 || BASE_GetItemAbility(dest, EF_MOBTYPE) != 1)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int dam = 0;
		int effect = 0;

		for (int i = 0; i < 3; i++)
		{
			if (dest->stEffect[i].cEffect == EF_AC || dest->stEffect[i].cEffect == EF_ACADD2)
			{
				dam = dest->stEffect[i].cValue;
				effect = dest->stEffect[i].cEffect;

				break;
			}
		}

		int max_add = (effect == EF_AC ? 40 : 70);
		int min_add = (effect == EF_AC ? 15 : 15);

		if (dam < min_add)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			SendClientMsg(a_iConn, "Não é possível aprimorar este item.");
			return;
		}

		if (dam >= max_add)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			SendClientMsg(a_iConn, "Não é possível aprimorar este item.");
			return;
		}

		int RateSucess = 60;
		int _rand = rand() % 115;
		if (_rand > 100)
			_rand -= 15;

		if (_rand <= RateSucess && RateSucess)
		{
			for (int i = 0; i < 3; i++)
			{
				if (dest->stEffect[i].cEffect == EF_AC || dest->stEffect[i].cEffect == EF_ACADD2)
				{
					dest->stEffect[i].cValue += (dest->stEffect[i].cEffect == EF_AC ? 5 : 10);

					if (dest->stEffect[i].cValue >(dest->stEffect[i].cEffect == EF_AC ? 40 : 70))
						dest->stEffect[i].cValue = (dest->stEffect[i].cEffect == EF_AC ? 40 : 70);

					break;
				}
			}

			pMob[a_iConn].GetCurrentScore(a_iConn);
			SendClientMsg(a_iConn, "Upgrade +");
			SendScore(a_iConn);
			sprintf(temp, "useitem,upgrade success %d+%d - (%d,%d,%d)", dest->sIndex, sanc, item->stEffect[0].cEffect, item->stEffect[1].cEffect, item->stEffect[2].cEffect);

			if (amount > 1)
				BASE_SetItemAmount(item, amount - 1);

			else
				memset(item, 0, sizeof(STRUCT_ITEM));

			SendItem(a_iConn, m->DestType, m->DestPos, dest);
			SendEmotion(a_iConn, 14, 3);
		}

		else
		{
			if ((rand() % 7) == 0)
			{
				for (int i = 0; i < 3; i++)
				{
					if (dest->stEffect[i].cEffect == EF_AC || dest->stEffect[i].cEffect == EF_ACADD2)
					{
						if (dest->stEffect[i].cEffect == EF_AC && dest->stEffect[i].cValue > 5 || dest->stEffect[i].cEffect == EF_ACADD2 && dest->stEffect[i].cValue > 10)
							dest->stEffect[i].cValue -= (dest->stEffect[i].cEffect == EF_AC ? 5 : 10);

						break;
					}
				}
				sprintf(temp, "useitem,upgrade fail-- %d+%d - (%d,%d,%d)", dest->sIndex, sanc, item->stEffect[0].cEffect, item->stEffect[1].cEffect, item->stEffect[2].cEffect);
				SendClientMsg(a_iConn, "Upgrade -");
				SendItem(a_iConn, m->DestType, m->DestPos, dest);
				SendEmotion(a_iConn, 14, 3);
			}
			else
			{
				sprintf(temp, "useitem,upgrade fail %d+%d - (%d,%d,%d)", dest->sIndex, sanc, item->stEffect[0].cEffect, item->stEffect[1].cEffect, item->stEffect[2].cEffect);

				SendClientMsg(a_iConn, "O upgrade do item falhou.");

				int sFace = pMob[a_iConn].MOB.Equip[0].sIndex / 10;

				if (sFace)
					SendEmotion(a_iConn, 15, 0);

				else
					SendEmotion(a_iConn, 20, 0);
			}

			MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);

			if (amount > 1)
				BASE_SetItemAmount(item, amount - 1);

			else
				memset(item, 0, sizeof(STRUCT_ITEM));
		}

		return;
	}
#pragma endregion
#pragma region >> Barra Mytril (Crítico)
	if (Vol == 238)
	{
		STRUCT_ITEM *dest = GetItemPointer(&pMob[a_iConn].MOB, pUser[a_iConn].Cargo, m->DestType, m->DestPos);

		if (dest == NULL)
			return;


		if (m->DestType || m->DestPos >= 8 && m->DestPos < 16 || m->DestType == ITEM_PLACE_EQUIP && m->DestPos == 0 || m->DestType == ITEM_PLACE_EQUIP && m->DestPos == 1)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Only_To_Equips]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int sanc = BASE_GetItemSanc(dest);
		int ItemId = dest->sIndex;

		if (sanc < REF_10 || BASE_GetItemAbility(dest, EF_MOBTYPE) != 1)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		//int dam = BASE_GetItemAbilityNosanc(dest, EF_CRITICAL2);
		int dam = 0;
		int effect = 0;

		for (int i = 0; i < 3; i++)
		{
			if (dest->stEffect[i].cEffect == EF_CRITICAL || dest->stEffect[i].cEffect == EF_CRITICAL2)
			{
				effect = dest->stEffect[i].cEffect;

				if (effect == EF_CRITICAL2)
				{
					dest->stEffect[i].cEffect = EF_CRITICAL;
					dest->stEffect[i].cValue -= 45;
				}

				dam = dest->stEffect[i].cValue;
				

				break;
			}
		}

		int max_add = m->DestPos != 6 && m->DestPos != 7 ? 50 : 0;
		int min_add = m->DestPos != 6 && m->DestPos != 7 ? 5 : 0;
		
		if (m->DestPos == 6)
		{
			 max_add = 50;
			 min_add = 3;
		}

		if (dam < min_add)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			SendClientMsg(a_iConn, "Não é possível aprimorar este item.");
			return;
		}

		if (dam >= max_add)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			SendClientMsg(a_iConn, "Não é possível aprimorar este item.");
			return;
		}


		int RateSucess = 30;
		int _rand = rand() % 115;

		if (_rand > 100)
			_rand -= 15;

		if (_rand <= RateSucess && RateSucess)
		{
			for (int i = 0; i < 3; i++)
			{
				if (dest->stEffect[i].cEffect == EF_CRITICAL || dest->stEffect[i].cEffect == EF_CRITICAL2)
				{
					dest->stEffect[i].cEffect = EF_CRITICAL;
					//dest->stEffect[i].cValue += m->DestPos != 6 && m->DestPos != 7 ? 10 : 1;
					dest->stEffect[i].cValue += 10;

					//if (dest->stEffect[i].cValue >(m->DestPos != 6 && m->DestPos != 7 && m->DestPos != 4 ? 50 : 0))
						//dest->stEffect[i].cValue = (m->DestPos != 6 && m->DestPos != 7 && m->DestPos != 4 ? 50 : 0);

					if (dest->stEffect[i].cValue > 50)
						dest->stEffect[i].cValue = 50;

					break;
				}
			}



			pMob[a_iConn].GetCurrentScore(a_iConn);
			SendClientMsg(a_iConn, "Upgrade +");
			SendScore(a_iConn);
			sprintf(temp, "useitem,upgrade success %d+%d - (%d,%d,%d)", dest->sIndex, sanc, item->stEffect[0].cEffect, item->stEffect[1].cEffect, item->stEffect[2].cEffect);

			if (amount > 1)
				BASE_SetItemAmount(item, amount - 1);

			else
				memset(item, 0, sizeof(STRUCT_ITEM));

			SendItem(a_iConn, m->DestType, m->DestPos, dest);
			SendEmotion(a_iConn, 14, 3);
		}

		else
		{
			if ((rand() % 7) == 0)
			{
				for (int i = 0; i < 3; i++)
				{
					if (dest->stEffect[i].cEffect == EF_CRITICAL || dest->stEffect[i].cEffect == EF_CRITICAL2)
					{
						dest->stEffect[i].cEffect = EF_CRITICAL;
						//if (dest->stEffect[i].cValue >(m->DestPos != 6 && m->DestPos != 7 ? 10 : 10))
							//dest->stEffect[i].cValue -= m->DestPos != 6 && m->DestPos != 7 ? 10 : 10;

						if (dest->stEffect[i].cValue > 10)
							dest->stEffect[i].cValue -= 10;

						break;
					}
				}
				sprintf(temp, "useitem,upgrade fail-- %d+%d - (%d,%d,%d)", dest->sIndex, sanc, item->stEffect[0].cEffect, item->stEffect[1].cEffect, item->stEffect[2].cEffect);

				SendItem(a_iConn, m->DestType, m->DestPos, dest);
				SendEmotion(a_iConn, 14, 3);
				SendClientMsg(a_iConn, "Upgrade -");
			}
			else
			{
				sprintf(temp, "useitem,upgrade fail %d+%d - (%d,%d,%d)", dest->sIndex, sanc, item->stEffect[0].cEffect, item->stEffect[1].cEffect, item->stEffect[2].cEffect);

				SendClientMsg(a_iConn, "O upgrade do item falhou.");
				int sFace = pMob[a_iConn].MOB.Equip[0].sIndex / 10;

				if (sFace)
					SendEmotion(a_iConn, 15, 0);

				else
					SendEmotion(a_iConn, 20, 0);
			}

			MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);

			if (amount > 1)
				BASE_SetItemAmount(item, amount - 1);

			else
				memset(item, 0, sizeof(STRUCT_ITEM));
		}

		return;
	}
#pragma endregion
#pragma region >> Replation Normal
	if (item->sIndex >= 4016 && item->sIndex <= 4020)
	{
		STRUCT_ITEM *dest = GetItemPointer(&pMob[a_iConn].MOB, pUser[a_iConn].Cargo, m->DestType, m->DestPos);
		int nPos = g_pItemList[dest->sIndex].nPos;

		if (dest == NULL)
			return;

		if (!m->DestType || m->DestPos >= 60)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Only_To_Equips]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (dest->sIndex >= 3500 && dest->sIndex <= 3507)
		{
			SendClientMsg(a_iConn, "Não é possível utilizar em cytheras.");
			SendItem(a_iConn, ITEM_PLACE_CARRY, m->SourPos, item);
			return;
		}

		if (nPos == 64 || nPos == 192 || nPos == 42)
		{
			SendClientMsg(a_iConn, "Possível somente para equipamentos de defesa.");
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int sanc = BASE_GetItemSanc(dest);
		int ItemId = dest->sIndex;

		if (sanc > 6 || BASE_GetItemAbility(dest, EF_MOBTYPE) != 0 && BASE_GetItemAbility(dest, EF_MOBTYPE) != 2)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int replation = item->sIndex >= 4016 && item->sIndex <= 4020 ? item->sIndex - 4015 : item->sIndex - 4020;

		if (BASE_GetItemAbility(dest, EF_ITEMLEVEL) != replation)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		SetItemBonus2(dest);
		SendItem(a_iConn, m->DestType, m->DestPos, dest);
		SendEmotion(a_iConn, 14, 3);

		sprintf(temp, "useitem,replation normal: effect %d+%d - (%d,%d,%d)", dest->sIndex, sanc, dest->stEffect[0].cEffect, dest->stEffect[1].cEffect, dest->stEffect[2].cEffect);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		return;
	}
#pragma endregion
#pragma region >> Replation Premium
	if (item->sIndex >= 4021 && item->sIndex <= 4025)
	{
		STRUCT_ITEM *dest = GetItemPointer(&pMob[a_iConn].MOB, pUser[a_iConn].Cargo, m->DestType, m->DestPos);
		int nPos = g_pItemList[dest->sIndex].nPos;

		if (dest == NULL)
			return;

		if (!m->DestType || m->DestPos >= 60)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Only_To_Equips]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (dest->sIndex >= 3500 && dest->sIndex <= 3507)
		{
			SendClientMsg(a_iConn, "Não é possível utilizar em cytheras.");
			SendItem(a_iConn, ITEM_PLACE_CARRY, m->SourPos, item);
			return;
		}

		if (nPos == 64 || nPos == 192 || nPos == 42)
		{
			SendClientMsg(a_iConn, "Possível somente para equipamentos de defesa.");
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int sanc = BASE_GetItemSanc(dest);
		int ItemId = dest->sIndex;

		if (sanc > 9 || BASE_GetItemAbility(dest, EF_MOBTYPE) != 0 && BASE_GetItemAbility(dest, EF_MOBTYPE) != 2)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int replation = item->sIndex >= 4021 && item->sIndex <= 4025 ? item->sIndex - 4020 : item->sIndex - 4025;

		if (BASE_GetItemAbility(dest, EF_ITEMLEVEL) != replation)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		SetItemBonus2(dest);
		SendItem(a_iConn, m->DestType, m->DestPos, dest);
		SendEmotion(a_iConn, 14, 3);

		sprintf(temp, "useitem,replation normal: effect %d+%d - (%d,%d,%d)", dest->sIndex, sanc, dest->stEffect[0].cEffect, dest->stEffect[1].cEffect, dest->stEffect[2].cEffect);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		return;
	}
#pragma endregion
#pragma region >> Flash Prateado
	if (item->sIndex == 3451)
	{
		if (pMob[a_iConn].MOB.Equip[13].sIndex == NULL)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].MOB.Equip[13].sIndex == 3902 || pMob[a_iConn].MOB.Equip[13].sIndex == 3905 || pMob[a_iConn].MOB.Equip[13].sIndex == 3908)
		{
			pMob[a_iConn].MOB.Equip[13].sIndex = 3914;
			pMob[a_iConn].MOB.Equip[13].stEffect[0].cValue = pMob[a_iConn].MOB.Equip[13].stEffect[0].cValue;
			pMob[a_iConn].MOB.Equip[13].stEffect[1].cValue = pMob[a_iConn].MOB.Equip[13].stEffect[1].cValue;
			pMob[a_iConn].MOB.Equip[13].stEffect[2].cValue = pMob[a_iConn].MOB.Equip[13].stEffect[2].cValue;

			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Refine_Success]);
			SendEmotion(a_iConn, 14, 3);

			SendItem(a_iConn, ITEM_PLACE_EQUIP, 13, &pMob[a_iConn].MOB.Equip[13]);
			return;
		}

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));
		return;
	}
#pragma endregion
#pragma region >> Flash Dourado
	if (item->sIndex == 3452)
	{
		if (pMob[a_iConn].MOB.Equip[13].sIndex == NULL)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].MOB.Equip[13].sIndex == 3902 || pMob[a_iConn].MOB.Equip[13].sIndex == 3905 || pMob[a_iConn].MOB.Equip[13].sIndex == 3908)
		{
			pMob[a_iConn].MOB.Equip[13].sIndex = 3915;
			pMob[a_iConn].MOB.Equip[13].stEffect[0].cValue = pMob[a_iConn].MOB.Equip[13].stEffect[0].cValue;
			pMob[a_iConn].MOB.Equip[13].stEffect[1].cValue = pMob[a_iConn].MOB.Equip[13].stEffect[1].cValue;
			pMob[a_iConn].MOB.Equip[13].stEffect[2].cValue = pMob[a_iConn].MOB.Equip[13].stEffect[2].cValue;

			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Refine_Success]);
			SendEmotion(a_iConn, 14, 3);
			SendItem(a_iConn, ITEM_PLACE_EQUIP, 13, &pMob[a_iConn].MOB.Equip[13]);
			return;
		}

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));
		return;
	}
#pragma endregion
#pragma region >> Pedra Ideal
	if (Vol == 211)
	{
		if (pMob[a_iConn].Extra.ClassMaster != ARCH && pMob[a_iConn].Extra.ClassMaster != CELESTIAL)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].Extra.ClassMaster == ARCH && pMob[a_iConn].MOB.CurrentScore.Level < 355)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].Extra.ClassMaster == ARCH && (pMob[a_iConn].MOB.Equip[1].sIndex != 0 || pMob[a_iConn].Extra.QuestInfo.Arch.MortalLevel < 99))
		{
			if (pMob[a_iConn].MOB.Equip[1].sIndex)
				SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_with_armor]);

			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].Extra.ClassMaster == CELESTIAL && (pMob[a_iConn].MOB.Equip[11].sIndex < 1760 || pMob[a_iConn].MOB.Equip[11].sIndex > 1763))
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].Extra.ClassMaster == CELESTIAL && pMob[a_iConn].MOB.CurrentScore.Level < 120)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].Extra.ClassMaster == CELESTIAL)
		{
			pMob[a_iConn].Extra.ClassMaster = CELESTIALCS;

			pMob[a_iConn].Extra.SaveCelestial[1].Class = pMob[a_iConn].MOB.Equip[11].sIndex - 1760;

			pMob[a_iConn].Extra.SaveCelestial[1].BaseScore = pMob[a_iConn].MOB.BaseScore;

			pMob[a_iConn].Extra.SaveCelestial[1].LearnedSkill = pMob[a_iConn].MOB.LearnedSkill;

			pMob[a_iConn].Extra.SaveCelestial[1].BaseScore.Level = 0;

			pMob[a_iConn].Extra.SaveCelestial[1].BaseScore.Str = BaseSIDCHM[pMob[a_iConn].MOB.Class][0];
			pMob[a_iConn].Extra.SaveCelestial[1].BaseScore.Int = BaseSIDCHM[pMob[a_iConn].MOB.Class][1];
			pMob[a_iConn].Extra.SaveCelestial[1].BaseScore.Dex = BaseSIDCHM[pMob[a_iConn].MOB.Class][2];
			pMob[a_iConn].Extra.SaveCelestial[1].BaseScore.Con = BaseSIDCHM[pMob[a_iConn].MOB.Class][3];

			pMob[a_iConn].Extra.SaveCelestial[1].BaseScore.Special[0] = 0;
			pMob[a_iConn].Extra.SaveCelestial[1].BaseScore.Special[1] = 0;
			pMob[a_iConn].Extra.SaveCelestial[1].BaseScore.Special[2] = 0;
			pMob[a_iConn].Extra.SaveCelestial[1].BaseScore.Special[3] = 0;

			pMob[a_iConn].Extra.SaveCelestial[1].BaseScore.Ac = 230;
			pMob[a_iConn].Extra.SaveCelestial[1].BaseScore.Damage = 0;
			pMob[a_iConn].Extra.SaveCelestial[1].BaseScore.Hp = BaseSIDCHM[pMob[a_iConn].MOB.Equip[11].sIndex - 1760][4];
			pMob[a_iConn].Extra.SaveCelestial[1].BaseScore.MaxHp = BaseSIDCHM[pMob[a_iConn].MOB.Equip[11].sIndex - 1760][4];
			pMob[a_iConn].Extra.SaveCelestial[1].BaseScore.Mp = BaseSIDCHM[pMob[a_iConn].MOB.Equip[11].sIndex - 1760][5];
			pMob[a_iConn].Extra.SaveCelestial[1].BaseScore.MaxMp = BaseSIDCHM[pMob[a_iConn].MOB.Equip[11].sIndex - 1760][5];

			pMob[a_iConn].Extra.SaveCelestial[1].SpecialBonus = 855;

			pMob[a_iConn].Extra.SaveCelestial[1].LearnedSkill &= 0xFF000000;

			pMob[a_iConn].Extra.SaveCelestial[1].Exp = 0;

			pMob[a_iConn].Extra.SaveCelestial[1].Soul = pMob[a_iConn].Extra.Soul;
		
			memset(&pMob[a_iConn].MOB.Equip[11], 0, sizeof(STRUCT_ITEM));

			//limpa barra de skill
			memset(&pMob[a_iConn].MOB.SkillBar, 0, 4);

			SendItem(a_iConn, ITEM_PLACE_EQUIP, 11, &pMob[a_iConn].MOB.Equip[11]);

			if (amount > 1)
				BASE_SetItemAmount(item, amount - 1);

			else
				memset(item, 0, sizeof(STRUCT_ITEM));

			sprintf(temp, "useitem,ideal stone used to make god2");
			MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);

			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_My_King_Bless1]);
			return;
		}

#pragma region Celestial
		
		if (pMob[a_iConn].Extra.ClassMaster == ARCH)
		{
			int ptlevel = 0;
			int retconfig = nConfig::ReadExtra(PATH_SETTINGS, "extra.json", CELESTIAL);

			if (pMob[a_iConn].MOB.CurrentScore.Level < 370)
				ptlevel = 1;

			else if (pMob[a_iConn].MOB.CurrentScore.Level < 380)
				ptlevel = 2;

			else if (pMob[a_iConn].MOB.CurrentScore.Level < 398)
				ptlevel = 3;

			else if (pMob[a_iConn].MOB.CurrentScore.Level == 398)
				ptlevel = 4;
			else
				ptlevel = 5;

			memset(&pMob[a_iConn].MOB.Equip[1], 0, sizeof(STRUCT_ITEM));

			if (pMob[a_iConn].MOB.CurrentScore.Level < 380)
				pMob[a_iConn].MOB.Equip[1].sIndex = 3500;

			else if (pMob[a_iConn].MOB.CurrentScore.Level < 399)
				pMob[a_iConn].MOB.Equip[1].sIndex = 3501;

			else if (pMob[a_iConn].MOB.CurrentScore.Level < 400)
				pMob[a_iConn].MOB.Equip[1].sIndex = 3502;

			pMob[a_iConn].Extra.QuestInfo.Celestial.ArchLevel = ptlevel;
			pMob[a_iConn].Extra.ClassMaster = CELESTIAL;

			pMob[a_iConn].MOB.BaseScore.Level = 0;

			pMob[a_iConn].MOB.BaseScore.Str = BaseSIDCHM[pMob[a_iConn].MOB.Class][0];
			pMob[a_iConn].MOB.BaseScore.Int = BaseSIDCHM[pMob[a_iConn].MOB.Class][1];
			pMob[a_iConn].MOB.BaseScore.Dex = BaseSIDCHM[pMob[a_iConn].MOB.Class][2];
			pMob[a_iConn].MOB.BaseScore.Con = BaseSIDCHM[pMob[a_iConn].MOB.Class][3];

			pMob[a_iConn].MOB.BaseScore.Special[0] = 0;
			pMob[a_iConn].MOB.BaseScore.Special[1] = 0;
			pMob[a_iConn].MOB.BaseScore.Special[2] = 0;
			pMob[a_iConn].MOB.BaseScore.Special[3] = 0;

			pMob[a_iConn].MOB.BaseScore.Ac = 1004;
			pMob[a_iConn].MOB.BaseScore.Damage = 400;
			pMob[a_iConn].MOB.BaseScore.Hp = BaseSIDCHM[pMob[a_iConn].MOB.Class][4];
			pMob[a_iConn].MOB.BaseScore.MaxHp = BaseSIDCHM[pMob[a_iConn].MOB.Class][4];
			pMob[a_iConn].MOB.BaseScore.Mp = BaseSIDCHM[pMob[a_iConn].MOB.Class][5];
			pMob[a_iConn].MOB.BaseScore.MaxMp = BaseSIDCHM[pMob[a_iConn].MOB.Class][5];

			pMob[a_iConn].MOB.SpecialBonus = 855;

			pMob[a_iConn].MOB.LearnedSkill = 1073741824;

			pMob[a_iConn].MOB.Exp = 0;

			memset(&pMob[a_iConn].MOB.Equip[15], 0, sizeof(STRUCT_ITEM));

			if (pMob[a_iConn].MOB.Clan == 7)
				pMob[a_iConn].MOB.Equip[15].sIndex = 3197;

			else if (pMob[a_iConn].MOB.Clan == 8)
				pMob[a_iConn].MOB.Equip[15].sIndex = 3198;

			else
				pMob[a_iConn].MOB.Equip[15].sIndex = 3199;

			pMob[a_iConn].MOB.Equip[0].stEffect[1].cEffect = 98;
			pMob[a_iConn].MOB.Equip[0].stEffect[1].cValue = 3;
			pMob[a_iConn].MOB.Equip[0].stEffect[2].cEffect = 106;
			pMob[a_iConn].MOB.Equip[0].stEffect[2].cValue = (unsigned char)pMob[a_iConn].MOB.Equip[0].sIndex;
			
			//limpa barra de skill
			memset(&pMob[a_iConn].MOB.SkillBar, 0, 4);

			sprintf(temp, "Parabens!!![  %s  ] por ser o [ %dº ] jogador a criar Celestial no EternalWYD", pMob[a_iConn].MOB.MobName, CharaCreate[CELESTIAL]);
			SendNotice(temp);
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_My_King_Bless1]);

			if (retconfig)
				retconfig = nConfig::WriteExtra(PATH_SETTINGS, "extra.json", CELESTIAL);
		}
#pragma endregion

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		sprintf(temp, "useitem,ideal stone used to make god %d %d", pMob[a_iConn].Extra.QuestInfo.Celestial.ArchLevel, pMob[a_iConn].Extra.QuestInfo.Arch.Cristal);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);

		CharLogOut(a_iConn);

		SendClientSignalParm(a_iConn, ESCENE_FIELD, _MSG_SendArchEffect, pUser[a_iConn].Slot);
		return;

	}

#pragma endregion
#pragma region >> Pedra Misteriosa
	if (item->sIndex == 4148)
	{
		if (pMob[a_iConn].Extra.ClassMaster != CELESTIALCS && pMob[a_iConn].Extra.ClassMaster != SCELESTIAL)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int Village = BASE_GetVillage(pMob[a_iConn].TargetX, pMob[a_iConn].TargetY);

		if (Village < 0 || Village >= 5)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_OnlyVillage]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int cl = pMob[a_iConn].Extra.ClassMaster == CELESTIALCS ? 0 : 1;
		int ncl = pMob[a_iConn].Extra.ClassMaster == CELESTIALCS ? 1 : 0;

		if (pMob[a_iConn].Extra.ClassMaster == CELESTIALCS)
		{
			pMob[a_iConn].Extra.ClassMaster = SCELESTIAL;
			pMob[a_iConn].Extra.QuestInfo.Celestial.CelestialLevel = pMob[a_iConn].MOB.BaseScore.Level;
			SendClientMsg(a_iConn, "Você é Sub Celestial!");

		}
		else
		{
			pMob[a_iConn].Extra.ClassMaster = CELESTIALCS;
			pMob[a_iConn].Extra.QuestInfo.Celestial.SubCelestialLevel = pMob[a_iConn].MOB.BaseScore.Level;
			SendClientMsg(a_iConn, "Você é Celestial!");
		}
		pMob[a_iConn].Extra.SaveCelestial[cl].BaseScore = pMob[a_iConn].MOB.BaseScore;
		pMob[a_iConn].Extra.SaveCelestial[cl].Class = pMob[a_iConn].MOB.Class;
		pMob[a_iConn].Extra.SaveCelestial[cl].Exp = pMob[a_iConn].MOB.Exp;
		pMob[a_iConn].Extra.SaveCelestial[cl].LearnedSkill = pMob[a_iConn].MOB.LearnedSkill;
		pMob[a_iConn].Extra.SaveCelestial[cl].ScoreBonus = pMob[a_iConn].MOB.ScoreBonus;
		pMob[a_iConn].Extra.SaveCelestial[cl].SkillBonus = pMob[a_iConn].MOB.SkillBonus;
		pMob[a_iConn].Extra.SaveCelestial[cl].SpecialBonus = pMob[a_iConn].MOB.SpecialBonus;
		pMob[a_iConn].Extra.SaveCelestial[cl].SPX = pMob[a_iConn].MOB.SPX;
		pMob[a_iConn].Extra.SaveCelestial[cl].SPY = pMob[a_iConn].MOB.SPY;

		pMob[a_iConn].Extra.SaveCelestial[cl].Soul = pMob[a_iConn].Extra.Soul;

		memcpy(pMob[a_iConn].Extra.SaveCelestial[cl].SkillBar1, pMob[a_iConn].MOB.SkillBar, 4);
		memcpy(pMob[a_iConn].Extra.SaveCelestial[cl].SkillBar2, pUser[a_iConn].CharShortSkill, 16);

		pMob[a_iConn].MOB.BaseScore = pMob[a_iConn].Extra.SaveCelestial[ncl].BaseScore;
		pMob[a_iConn].MOB.Class = pMob[a_iConn].Extra.SaveCelestial[ncl].Class;
		pMob[a_iConn].MOB.Exp = pMob[a_iConn].Extra.SaveCelestial[ncl].Exp;
		pMob[a_iConn].MOB.LearnedSkill = pMob[a_iConn].Extra.SaveCelestial[ncl].LearnedSkill;
		pMob[a_iConn].MOB.ScoreBonus = pMob[a_iConn].Extra.SaveCelestial[ncl].ScoreBonus;
		pMob[a_iConn].MOB.SkillBonus = pMob[a_iConn].Extra.SaveCelestial[ncl].SkillBonus;
		pMob[a_iConn].MOB.SpecialBonus = pMob[a_iConn].Extra.SaveCelestial[ncl].SpecialBonus;
		pMob[a_iConn].MOB.SPX = pMob[a_iConn].Extra.SaveCelestial[ncl].SPX;
		pMob[a_iConn].MOB.SPY = pMob[a_iConn].Extra.SaveCelestial[ncl].SPY;
		pMob[a_iConn].Extra.Soul = pMob[a_iConn].Extra.SaveCelestial[ncl].Soul;

		memcpy(pMob[a_iConn].MOB.SkillBar, pMob[a_iConn].Extra.SaveCelestial[ncl].SkillBar1, 4);
		memcpy(pUser[a_iConn].CharShortSkill, pMob[a_iConn].Extra.SaveCelestial[ncl].SkillBar2, 16);

		for (int i = 0; i < MAX_AFFECT; i++)
		{
			if (pMob[a_iConn].Affect[i].Type == 4 || pMob[a_iConn].Affect[i].Type == 8 || pMob[a_iConn].Affect[i].Type == 29 || pMob[a_iConn].Affect[i].Type == 30 || pMob[a_iConn].Affect[i].Type == 34 || pMob[a_iConn].Affect[i].Type == 35 || pMob[a_iConn].Affect[i].Type == 39)
				continue;

			memset(&pMob[a_iConn].Affect[i], 0, sizeof(STRUCT_AFFECT));
		}

		pMob[a_iConn].MOB.Equip[0].sIndex = pMob[a_iConn].Extra.MortalFace + 5 + pMob[a_iConn].MOB.Class;
		SendItem(a_iConn, ITEM_PLACE_EQUIP, 0, &pMob[a_iConn].MOB.Equip[0]);

		MSG_SetShortSkill sm_sss;
		memset(&sm_sss, 0, sizeof(MSG_SetShortSkill));

		sm_sss.Size = sizeof(MSG_SetShortSkill);
		sm_sss.ID = ESCENE_FIELD;
		sm_sss.Type = _MSG_SetShortSkill;

		memcpy(sm_sss.Skill1, pMob[a_iConn].Extra.SaveCelestial[ncl].SkillBar1, 4);
		memcpy(sm_sss.Skill2, pMob[a_iConn].Extra.SaveCelestial[ncl].SkillBar2, 16);

		pUser[a_iConn].cSock.AddMessage((char*)&sm_sss, sizeof(MSG_SetShortSkill));

		BASE_GetBonusSkillPoint(&pMob[a_iConn].MOB, &pMob[a_iConn].Extra);
		BASE_GetBonusScorePoint(&pMob[a_iConn].MOB, &pMob[a_iConn].Extra);

		BASE_GetHpMp(&pMob[a_iConn].MOB, &pMob[a_iConn].Extra);

		pMob[a_iConn].GetCurrentScore(a_iConn);

		GetGuild(a_iConn);

		SendScore(a_iConn);
		SendEtc(a_iConn);

		sprintf(temp, "useitem,mistery stone change god2god");
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		return;
	}
#pragma endregion
#pragma region >> Escritura do Pesadelo
	if (Vol == 212)
	{
		time_t mtime;

		time(&mtime);

		if (mtime < (pMob[a_iConn].Extra.LastNT + 72000))
		{
			int rtime = (int)((72000 - (mtime - pMob[a_iConn].Extra.LastNT)) / 60 / 60);
			int rmin = (int)((72000 - (mtime - pMob[a_iConn].Extra.LastNT)) / 60 - (rtime * 60));

			sprintf(temp, g_pMessageStringTable[_DD_NightmareTime], rtime, rmin);
			SendClientMsg(a_iConn, temp);

			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		pMob[a_iConn].Extra.LastNT = mtime;
		pMob[a_iConn].Extra.NT += 13;

		sprintf(temp, "useitem,nightmare entrance ticket %d", pMob[a_iConn].Extra.NT);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		return;
	}
#pragma endregion
#pragma region Livros Nonas/Decimas
#pragma region >> Linhagem Transknight

	/* Proteção Divina */
	if (item->sIndex == 5500)
	{
		if (pMob[a_iConn].MOB.BaseScore.Level <= 199)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Need_More_Level_To_Learn]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].Extra.ClassMaster == MORTAL || pMob[a_iConn].Extra.ClassMaster == ARCH)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_GOD2CHARONLY_]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int ItemID = item->sIndex;

		if (pMob[a_iConn].MOB.Class == 0)
		{
			if ((1 << 4) & pMob[a_iConn].Extra.SecLearnedSkill)
			{
				SendClientMsg(a_iConn, "Apenas uma 9ª Skill por personagem.");
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				return;
			}

			if ((1 << 8) & pMob[a_iConn].Extra.SecLearnedSkill)
			{
				SendClientMsg(a_iConn, "Apenas uma 9ª Skill por personagem.");
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				return;
			}

			if ((1 << 7) & pMob[a_iConn].MOB.LearnedSkill)
			{
				if ((1 << 0) & pMob[a_iConn].Extra.SecLearnedSkill)
				{
					SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Already_Learned_It]);
					SendItem(a_iConn, m->SourType, m->SourPos, item);
					return;
				}
				else
				{
					pMob[a_iConn].Extra.SecLearnedSkill |= 0x1;
					sprintf(temp, g_pMessageStringTable[_SN_Learn_Skill], g_pItemList[ItemID].Name);

					SendClientMsg(a_iConn, temp);
					SendEtc(a_iConn);

					if (amount > 1)
						BASE_SetItemAmount(item, amount - 1);

					else
						memset(item, 0, sizeof(STRUCT_ITEM));

					return;
				}
			}
			else
			{
				SendClientMsg(a_iConn, "É necessário ter aprendido a 8ª Skill.");
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				return;
			}

		}
		else
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Learn_Other_Class_Skill]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}
	}

	/* Mãos Sangrentas */
	if (item->sIndex == 5504) 
	{
		if (pMob[a_iConn].MOB.BaseScore.Level <= 199)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Need_More_Level_To_Learn]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].Extra.ClassMaster == MORTAL || pMob[a_iConn].Extra.ClassMaster == ARCH)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_GOD2CHARONLY_]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int ItemID = item->sIndex;

		if (pMob[a_iConn].MOB.Class == 0)
		{
			if ((1 << 0) & pMob[a_iConn].Extra.SecLearnedSkill)
			{
				SendClientMsg(a_iConn, "Apenas uma 9ª Skill por personagem.");
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				return;
			}

			if ((1 << 8) & pMob[a_iConn].Extra.SecLearnedSkill)
			{
				SendClientMsg(a_iConn, "Apenas uma 9ª Skill por personagem.");
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				return;
			}

			if ((1 << 15) & pMob[a_iConn].MOB.LearnedSkill)
			{
				if ((1 << 4) & pMob[a_iConn].Extra.SecLearnedSkill)
				{
					SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Already_Learned_It]);
					SendItem(a_iConn, m->SourType, m->SourPos, item);
					return;
				}
				else
				{
					pMob[a_iConn].Extra.SecLearnedSkill |= 0x10; 
					sprintf(temp, g_pMessageStringTable[_SN_Learn_Skill], g_pItemList[ItemID].Name);

					SendClientMsg(a_iConn, temp);
					SendEtc(a_iConn);

					if (amount > 1)
						BASE_SetItemAmount(item, amount - 1);

					else
						memset(item, 0, sizeof(STRUCT_ITEM));

					return;
				}
			}
			else
			{
				SendClientMsg(a_iConn, "É necessário ter aprendido a 8ª Skill.");
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				return;
			}
		}
		else
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Learn_Other_Class_Skill]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}
	}

	/* Espelho Mágico */
	if (item->sIndex == 5508)
	{
		if (pMob[a_iConn].MOB.BaseScore.Level <= 199)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Need_More_Level_To_Learn]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].Extra.ClassMaster == MORTAL || pMob[a_iConn].Extra.ClassMaster == ARCH)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_GOD2CHARONLY_]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int ItemID = item->sIndex;

		if (pMob[a_iConn].MOB.Class == 0)
		{
			if ((1 << 0) & pMob[a_iConn].Extra.SecLearnedSkill)
			{
				SendClientMsg(a_iConn, "Apenas uma 9ª Skill por personagem.");
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				return;
			}

			if ((1 << 4) & pMob[a_iConn].Extra.SecLearnedSkill)
			{
				SendClientMsg(a_iConn, "Apenas uma 9ª Skill por personagem.");
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				return;
			}

			if ((1 << 23) & pMob[a_iConn].MOB.LearnedSkill)
			{
				if ((1 << 8) & pMob[a_iConn].Extra.SecLearnedSkill)
				{
					SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Already_Learned_It]);
					SendItem(a_iConn, m->SourType, m->SourPos, item);
					return;
				}
				else
				{
					pMob[a_iConn].Extra.SecLearnedSkill |= 0x100;
					sprintf(temp, g_pMessageStringTable[_SN_Learn_Skill], g_pItemList[ItemID].Name);

					SendClientMsg(a_iConn, temp);
					SendEtc(a_iConn);

					if (amount > 1)
						BASE_SetItemAmount(item, amount - 1);

					else
						memset(item, 0, sizeof(STRUCT_ITEM));

					return;
				}
			}
			else
			{
				SendClientMsg(a_iConn, "É necessário ter aprendido a 8ª Skill.");
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				return;
			}
		}
		else
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Learn_Other_Class_Skill]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}
	}
#pragma endregion
#pragma endregion
#pragma region >> Livros Sephira
	if (Vol >= 31 && Vol <= 38)
	{
		int ItemID = item->sIndex;

		if (ItemID <= 0 || ItemID > MAX_ITEMLIST)
		{
			MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, "err, wrong skill book index", 0, pUser[a_iConn].IP);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int SkillLearn = 1 << (Vol - 7);

		if ((pMob[a_iConn].MOB.LearnedSkill & SkillLearn) != 0)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Already_Learned_It]);
			return;
		}

		pMob[a_iConn].MOB.LearnedSkill = pMob[a_iConn].MOB.LearnedSkill | SkillLearn;

		sprintf(temp, g_pMessageStringTable[_SN_Learn_Sephera], g_pItemList[ItemID].Name);

		SendClientMsg(a_iConn, temp);
		SendEtc(a_iConn);

		SetAffect(a_iConn, 44, 20, 20);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		sprintf(temp, "useitem,skillbook index:%d", ItemID);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);
		return;
	}
#pragma endregion
#pragma region >> Selo do Guerreiro
	if (item->sIndex == 4146)
	{
		pUser[a_iConn].UseItemTime = GetTickCount();

		if (pMob[a_iConn].Extra.Fame >= 2000000000)
			pMob[a_iConn].Extra.Fame = 2000000000;

		pMob[a_iConn].Extra.Fame += 10;

		SendEmotion(a_iConn, 14, 3);

		if (pMob[a_iConn].Extra.ClassMaster == MORTAL && pMob[a_iConn].MOB.CurrentScore.Level >= 354 && pMob[a_iConn].MOB.Equip[15].sIndex != 3191 && pMob[a_iConn].MOB.Equip[15].sIndex != 3192 && pMob[a_iConn].MOB.Equip[15].sIndex != 3193 && pMob[a_iConn].MOB.Equip[15].sIndex != 3194 && pMob[a_iConn].MOB.Equip[15].sIndex != 3195 && pMob[a_iConn].MOB.Equip[15].sIndex != 3196)
		{
			memset(&pMob[a_iConn].MOB.Equip[15], 0, sizeof(STRUCT_ITEM));

			if (pMob[a_iConn].MOB.Clan == 7)
				pMob[a_iConn].MOB.Equip[15].sIndex = 3191;

			else if (pMob[a_iConn].MOB.Clan == 8)
				pMob[a_iConn].MOB.Equip[15].sIndex = 3192;

			else
				pMob[a_iConn].MOB.Equip[15].sIndex = 3193;

			SendItem(a_iConn, ITEM_PLACE_EQUIP, 15, &pMob[a_iConn].MOB.Equip[15]);
		}

		sprintf(temp, "useitem,sealofwarrior %d", pMob[a_iConn].Extra.Fame);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		return;
	}
#pragma endregion
#pragma region >> Pedra da Furia
	if (item->sIndex == 3020)
	{
		if ((pMob[a_iConn].Extra.ClassMaster == CELESTIAL || pMob[a_iConn].Extra.ClassMaster == CELESTIALCS || pMob[a_iConn].Extra.ClassMaster == SCELESTIAL) && pMob[a_iConn].MOB.CurrentScore.Level >= 199)
		{
			if (pMob[a_iConn].Extra.Fame < 500)
			{
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				return;
			}

			if (pMob[a_iConn].Extra.QuestInfo.Circle == 0)
			{
				int sAgua = 0;
				int sTerra = 0;
				int sSol = 0;
				int sVento = 0;

				for (int i = 0; i < pMob[a_iConn].MaxCarry; i++)
				{
					if (pMob[a_iConn].MOB.Carry[i].sIndex == 5334)
						sAgua = 1;

					if (pMob[a_iConn].MOB.Carry[i].sIndex == 5335)
						sTerra = 1;

					if (pMob[a_iConn].MOB.Carry[i].sIndex == 5336)
						sSol = 1;

					if (pMob[a_iConn].MOB.Carry[i].sIndex == 5337)
						sVento = 1;
				}

				if (sAgua == 1 && sTerra == 1 && sSol == 1 && sVento == 1)
				{
					for (int i = 0; i < pMob[a_iConn].MaxCarry; i++)
					{
						if (pMob[a_iConn].MOB.Carry[i].sIndex == 5334 && sAgua == 1)
						{
							memset(&pMob[a_iConn].MOB.Carry[i], 0, sizeof(STRUCT_ITEM));
							SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);
							sAgua = 0;
						}

						if (pMob[a_iConn].MOB.Carry[i].sIndex == 5335 && sTerra == 1)
						{
							memset(&pMob[a_iConn].MOB.Carry[i], 0, sizeof(STRUCT_ITEM));
							SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);
							sTerra = 0;
						}

						if (pMob[a_iConn].MOB.Carry[i].sIndex == 5336 && sSol == 1)
						{
							memset(&pMob[a_iConn].MOB.Carry[i], 0, sizeof(STRUCT_ITEM));
							SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);
							sSol = 0;
						}

						if (pMob[a_iConn].MOB.Carry[i].sIndex == 5337 && sVento == 1)
						{
							memset(&pMob[a_iConn].MOB.Carry[i], 0, sizeof(STRUCT_ITEM));
							SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);
							sVento = 0;
						}
					}

					pMob[a_iConn].Extra.Fame -= 500;

					int _rand = rand() % 115;

					if (_rand > 100)
						_rand -= 15;

					if (_rand < 30)
					{
						if (!pMob[a_iConn].MOB.Equip[1].sIndex)
							memset(&pMob[a_iConn].MOB.Equip[1], 0, sizeof(STRUCT_ITEM));

						pMob[a_iConn].MOB.Equip[1].sIndex = 3507;

						SendItem(a_iConn, ITEM_PLACE_EQUIP, 1, &pMob[a_iConn].MOB.Equip[1]);

						sprintf(temp, g_pMessageStringTable[_DN_Play_Quest], "Cythera Arcana");
						SendClientMsg(a_iConn, temp);

						SendEmotion(a_iConn, 14, 3);
						pMob[a_iConn].Extra.QuestInfo.Circle = 1;

						sprintf(temp, "useitem,furystone quest arcan complete.");
						MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);
					}

					else
					{
						SendClientMsg(a_iConn, g_pMessageStringTable[_NN_FAILURE]);

						sprintf(temp, "useitem,furystone quest arcan fail.");
						MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);
					}
					if (amount > 1)
						BASE_SetItemAmount(item, amount - 1);

					else
						memset(item, 0, sizeof(STRUCT_ITEM));

					return;
				}
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				return;
			}

			else if (pMob[a_iConn].Extra.QuestInfo.Circle && pMob[a_iConn].Extra.QuestInfo.Celestial.Reset < 3)
			{
				pMob[a_iConn].Extra.QuestInfo.Celestial.Reset++;
				pMob[a_iConn].Extra.Fame -= 500;

				pMob[a_iConn].MOB.Exp -= 20000000;

				int newlevel = pMob[a_iConn].MOB.CurrentScore.Level;

				for (int i = 0; i < MAX_CLEVEL; i++)
				{
					if (pMob[a_iConn].MOB.Exp >= g_pNextLevel_2[i] && pMob[a_iConn].MOB.Exp <= g_pNextLevel_2[i + 1])
						newlevel = i;

				}

				pMob[a_iConn].MOB.BaseScore.Level = newlevel;
				int check = pMob[a_iConn].CheckGetLevel();

				if (check == 4)
					SetCircletSubGod(a_iConn);

				BASE_GetBonusScorePoint(&pMob[a_iConn].MOB, &pMob[a_iConn].Extra);

				pMob[a_iConn].GetCurrentScore(a_iConn);
				SendEtc(a_iConn);
				SendScore(a_iConn);

				SendEmotion(a_iConn, 14, 3);

				sprintf(temp, g_pMessageStringTable[_DN_Play_Quest], "Reset Celestial");
				SendClientMsg(a_iConn, temp);

				sprintf(temp, "useitem,furystone quest reset %d", pMob[a_iConn].Extra.QuestInfo.Celestial.Reset);
				MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);

				if (amount > 1)
					BASE_SetItemAmount(item, amount - 1);

				else
					memset(item, 0, sizeof(STRUCT_ITEM));

				return;
			}
		}
		if (pMob[a_iConn].Extra.ClassMaster != CELESTIAL)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].MOB.CurrentScore.Level < 89)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Level_Limit2]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].Extra.QuestInfo.Celestial.Lv90 == 1)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Youve_Done_It_Already]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].Extra.Fame < 500)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int _rand = rand() % 115;

		if (_rand > 100)
			_rand -= 15;

		pMob[a_iConn].Extra.Fame -= 500;

		if (_rand < 60)
		{
			pMob[a_iConn].Extra.QuestInfo.Celestial.Lv90 = 1;

			SendEmotion(a_iConn, 14, 3);

			sprintf(temp, g_pMessageStringTable[_DN_Play_Quest], "Lv90");
			SendClientMsg(a_iConn, temp);

			if (amount > 1)
				BASE_SetItemAmount(item, amount - 1);

			else
				memset(item, 0, sizeof(STRUCT_ITEM));

			STRUCT_ITEM Prize;
			memset(&Prize, 0, sizeof(STRUCT_ITEM));

			Prize.sIndex = 3502;

			PutItem(a_iConn, &Prize);

			sprintf(temp, "useitem,furystone quest90 sucess");
			MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);
		}
		else
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_FAILURE]);

			if (amount > 1)
				BASE_SetItemAmount(item, amount - 1);

			else
				memset(item, 0, sizeof(STRUCT_ITEM));

			sprintf(temp, "useitem,furystone quest90 fail");
			MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);
		}

		return;
	}
#pragma endregion
#pragma region >> Feijões mágicos - Removedor
	if (Vol == 186)
	{
		STRUCT_ITEM *dest = GetItemPointer(&pMob[a_iConn].MOB, pUser[a_iConn].Cargo, m->DestType, m->DestPos);

		if (dest == NULL)
			return;

		if (m->DestType || m->DestPos >= 6 && m->DestPos < 16 || m->DestType == ITEM_PLACE_EQUIP && m->DestPos == 0)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Only_To_Equips]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int sanc = BASE_GetItemSanc(dest);

		if (sanc < 1)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int color = item->sIndex - 3407;

		//Removedor
		if (color == 10)
		{
			if ((dest->stEffect[0].cEffect && dest->stEffect[0].cEffect < 116 || dest->stEffect[0].cEffect && dest->stEffect[0].cEffect > 125))
			{
				if ((dest->stEffect[1].cEffect && dest->stEffect[1].cEffect < 116 || dest->stEffect[1].cEffect && dest->stEffect[1].cEffect > 125))
				{
					if ((dest->stEffect[2].cEffect && dest->stEffect[2].cEffect < 116 || dest->stEffect[2].cEffect && dest->stEffect[2].cEffect > 125))
					{
						SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Refine_More]);
						SendItem(a_iConn, m->SourType, m->SourPos, item);
						return;
					}
					dest->stEffect[2].cEffect = 43;
				}
				else
					dest->stEffect[1].cEffect = 43;
			}
			else
				dest->stEffect[0].cEffect = 43;
		}
		else
		{
			if (dest->stEffect[0].cEffect && dest->stEffect[0].cEffect != 43 && (dest->stEffect[0].cEffect && dest->stEffect[0].cEffect < 116 || dest->stEffect[0].cEffect && dest->stEffect[0].cEffect > 125))
			{
				if (dest->stEffect[1].cEffect && dest->stEffect[1].cEffect != 43 && (dest->stEffect[1].cEffect && dest->stEffect[1].cEffect < 116 || dest->stEffect[1].cEffect && dest->stEffect[1].cEffect > 125))
				{
					if (dest->stEffect[2].cEffect && dest->stEffect[2].cEffect != 43 && (dest->stEffect[2].cEffect && dest->stEffect[2].cEffect < 116 || dest->stEffect[2].cEffect && dest->stEffect[2].cEffect > 125))
					{
						SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Refine_More]);
						SendItem(a_iConn, m->SourType, m->SourPos, item);
						return;
					}
					dest->stEffect[2].cEffect = 116 + color;
				}
				else
					dest->stEffect[1].cEffect = 116 + color;
			}
			else
				dest->stEffect[0].cEffect = 116 + color;
		}

		sprintf(temp, "%s", g_pMessageStringTable[_NN_Refine_Success]);
		SendClientMsg(a_iConn, temp);

		pMob[a_iConn].GetCurrentScore(a_iConn);

		SendScore(a_iConn);
		sprintf(temp, "useitem,paint success %d+%d - (%d,%d,%d)", dest->sIndex, sanc, item->stEffect[0].cEffect, item->stEffect[1].cEffect, item->stEffect[2].cEffect);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		SendEquip(a_iConn, 0);
		SendItem(a_iConn, m->DestType, m->DestPos, dest);
		SendEmotion(a_iConn, 14, 3);

		return;
	}
#pragma endregion
#pragma region >> DBRecord
	if (Vol == 14)
	{
		MSG_MessageDBRecord sm_dbrec;
		memset(&sm_dbrec, 0, sizeof(MSG_MessageDBRecord));

		sm_dbrec.Type = _MSG_MessageDBRecord;
		sm_dbrec.ID = 0;
		sm_dbrec.Size = sizeof(MSG_MessageDBRecord);

		sprintf(sm_dbrec.Record, "TCK %d %s %d %d %d %d", ServerIndex, pUser[a_iConn].AccountName, item->stEffect[0].cEffect, item->stEffect[1].cEffect, item->stEffect[2].cEffect, item->sIndex);

		DBServerSocket.SendOneMessage((char*)&sm_dbrec, sizeof(MSG_MessageDBRecord));

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		return;
	}
#pragma endregion
#pragma region >> GUILDBOARD
	if (Vol == 17)
	{
		int Guild = BASE_GetGuild(item);

		if (Guild > 0)
		{
			MSG_STANDARDPARM2 sm_gbo;
			memset(&sm_gbo, 0, sizeof(MSG_STANDARDPARM2));

			sm_gbo.Type = _MSG_GuildBoard;
			sm_gbo.ID = ESCENE_FIELD;
			sm_gbo.Parm1 = Guild;
			sm_gbo.Parm2 = GUILDBOARD;
			sm_gbo.Size = sizeof(MSG_STANDARDPARM2);

			pUser[a_iConn].cSock.AddMessage((char*)&sm_gbo, sizeof(MSG_STANDARDPARM2));
		}

		return;
	}
#pragma endregion
#pragma region >> Pergaminho do Perdão
	if (Vol == 203)
	{
		SetPKPoint(a_iConn, 150);

		MSG_CreateMob sm_pp;
		memset(&sm_pp, 0, sizeof(MSG_CreateMob));
		GetCreateMob(a_iConn, &sm_pp);

		GridMulticast(pMob[a_iConn].TargetX, pMob[a_iConn].TargetY, (MSG_STANDARD*)&sm_pp, 0);

		SendEmotion(a_iConn, 14, 3);

		sprintf(temp, "useitem,perdao new cp %d", 75);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));
		return;
	}
#pragma endregion
#pragma region >> Fogos de Artificio
	if (Vol == 19)
	{
		SendEmotion(a_iConn, 100, rand() % 5);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));
		return;
	}
#pragma endregion
#pragma region Evoluir
	if (item->sIndex == 3222)
	{
		if (pMob[a_iConn].Extra.ClassMaster == MORTAL)
		{
			if (pMob[a_iConn].MOB.BaseScore.Level >= 399)
			{
				SendClientMsg(a_iConn, "Você atingiu o nível máximo.");
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				return;
			}

			else
			{
				pMob[a_iConn].MOB.BaseScore.Level = 399;
				pMob[a_iConn].MOB.BaseScore.Ac += 399;
				pMob[a_iConn].MOB.SpecialBonus = 798;
				pMob[a_iConn].MOB.Exp = 4100000000;
				pMob[a_iConn].GetCurrentScore(a_iConn);
				SendScore(a_iConn);
				SendEtc(a_iConn);

				if (amount > 1)
					BASE_SetItemAmount(item, amount - 1);

				else
					memset(item, 0, sizeof(STRUCT_ITEM));

				CharLogOut(a_iConn);

			}

		}
		if (pMob[a_iConn].Extra.ClassMaster == ARCH)
		{
			if (pMob[a_iConn].MOB.BaseScore.Level >= 399)
			{
				SendClientMsg(a_iConn, "Você atingiu o nível máximo.");
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				return;
			}

			else
			{
				pMob[a_iConn].MOB.BaseScore.Level = 399; // Seta o Nível
				pMob[a_iConn].MOB.Exp = 4000000000;      // Seta o Exp
				pMob[a_iConn].MOB.BaseScore.Ac += 399;   // Seta a Defesa Correta
				pMob[a_iConn].MOB.SpecialBonus = 798;    // Seta os Pontos de Skills Corretos
				pMob[a_iConn].MOB.LearnedSkill = 0;      // Zera as Skills
				pMob[a_iConn].Extra.Fame += 96000;       // Entrega para o player 96k de FAME
				pMob[a_iConn].MOB.Equip[15].sIndex = 3193;  // Entrega Capa para o ARCH do Destrave 370
				pMob[a_iConn].GetCurrentScore(a_iConn);     // Atualiza o Nível, Status
				SendScore(a_iConn);                      // Atualiza o Scores, Pontos
				SendEtc(a_iConn);                        // Indefined

				CharLogOut(a_iConn);                     // Retorna para os Personagens

				if (amount > 1)
					BASE_SetItemAmount(item, amount - 1);

				else
					memset(item, 0, sizeof(STRUCT_ITEM));

			}

		}

		if (pMob[a_iConn].Extra.ClassMaster >= CELESTIAL)
		{
			SendClientMsg(a_iConn, "Impossível utilizar em Celestiais e SubCelestiais.");
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));


		return;
	}
#pragma endregion
#pragma region >> Composto de Chance
	if (item->sIndex == 4124)
	{
		if (pMob[a_iConn].MOB.CurrentScore.Level < 69 || pMob[a_iConn].MOB.CurrentScore.Level >= 74)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Level_limit]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int specialreset = 50;

		int special = pMob[a_iConn].MOB.SpecialBonus;

		for (int i = 0; i < 4; i++)
		{
			if (pMob[a_iConn].MOB.BaseScore.Special[i] <= specialreset)
			{
				special += pMob[a_iConn].MOB.BaseScore.Special[i];
				pMob[a_iConn].MOB.BaseScore.Special[i] = 0;
			}
			else
			{
				special += specialreset;
				pMob[a_iConn].MOB.BaseScore.Special[i] -= specialreset;
			}
		}

		pMob[a_iConn].MOB.SpecialBonus = special;

		pMob[a_iConn].MOB.LearnedSkill &= 0xFFFFFF00;
		pMob[a_iConn].MOB.LearnedSkill &= 0xFFFF00FF;
		pMob[a_iConn].MOB.LearnedSkill &= 0xFF00FFFF;

		BASE_GetBonusSkillPoint(&pMob[a_iConn].MOB, &pMob[a_iConn].Extra);

		SendEtc(a_iConn);
		SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Initialize_Skill]);
		SetAffect(a_iConn, 44, 20, 20);
		SendScore(a_iConn);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		return;
	}

#pragma endregion
#pragma region >> Composto de Equilíbrio
	if (item->sIndex == 4126)
	{
		if (pMob[a_iConn].MOB.CurrentScore.Level < 119 || pMob[a_iConn].MOB.CurrentScore.Level >= 124)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Level_limit]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int specialreset = 100;

		int special = pMob[a_iConn].MOB.SpecialBonus;

		for (int i = 0; i < 4; i++)
		{
			if (pMob[a_iConn].MOB.BaseScore.Special[i] <= specialreset)
			{
				special += pMob[a_iConn].MOB.BaseScore.Special[i];
				pMob[a_iConn].MOB.BaseScore.Special[i] = 0;
			}
			else
			{
				special += specialreset;
				pMob[a_iConn].MOB.BaseScore.Special[i] -= specialreset;
			}
		}

		pMob[a_iConn].MOB.SpecialBonus = special;

		pMob[a_iConn].MOB.LearnedSkill &= 0xFFFFFF00;
		pMob[a_iConn].MOB.LearnedSkill &= 0xFFFF00FF;
		pMob[a_iConn].MOB.LearnedSkill &= 0xFF00FFFF;

		BASE_GetBonusSkillPoint(&pMob[a_iConn].MOB, &pMob[a_iConn].Extra);

		SendEtc(a_iConn);
		SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Initialize_Skill]);
		SetAffect(a_iConn, 44, 20, 20);
		SendScore(a_iConn);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		return;
	}

#pragma endregion
#pragma region >> Carta de Duelo N.M.A
	if (Vol == 20)
	{
		int TargetX = pMob[a_iConn].TargetX;
		int TargetY = pMob[a_iConn].TargetY;


		if ((TargetX / 4) != 261 || (TargetY / 4) != 422)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Only_at_tor_alter]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].Leader != -1 && pMob[a_iConn].Leader)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Party_Leader_Only]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		char UserName[128];

		int UserArea = GetUserInArea(774, 3593, 892, 3702, UserName);

		if (UserArea >= 1)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Someone_is_on_quest]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);

			return;
		}

		CartaTime = 60;
		CartaSala = 1;

		DoTeleport(a_iConn, CartaPos[0][0], CartaPos[0][1]);
		SendClientSignalParm(a_iConn, ESCENE_FIELD, _MSG_StartTime, CartaTime * 2);

		for (int i = 0; i < MAX_PARTY; i++)
		{
			int partyconn = pMob[a_iConn].PartyList[i];

			if (partyconn > 0 && partyconn < MAX_USER && partyconn != a_iConn && pUser[partyconn].Mode == USER_PLAY)
			{
				DoTeleport(partyconn, CartaPos[0][0], CartaPos[0][1]);
				SendClientSignalParm(partyconn, ESCENE_FIELD, _MSG_StartTime, CartaTime * 2);
			}
		}

		for (int xx = 767; xx < 897; xx++)
		{
			for (int yy = 3582; yy < 3712; yy++)
			{
				int tmob = pMobGrid[yy][xx];

				if (tmob < MAX_USER)
					continue;

				DeleteMob(tmob, 3);
			}
		}

		int cartaindex = item->sIndex - 3171;

		if (cartaindex == 1)
		{//Carta N
			for (int i = SECRET_ROOM_N_INITIAL; i <= SECRET_ROOM_N_END; i++)
			{
				GenerateMob(i, 0, 0);
				GenerateMob(i, 0, 0);
			}

			GenerateMob(SECRET_ROOM_N_BOSS_INITIAL + rand() % 1, 0, 0);
		}

		else if (cartaindex == 0)
		{//Carta M
			for (int i = SECRET_ROOM_M_INITIAL; i <= SECRET_ROOM_M_END; i++)
			{
				GenerateMob(i, 0, 0);
				GenerateMob(i, 0, 0);
			}

			GenerateMob(SECRET_ROOM_M_BOSS_INITIAL + rand() % 1, 0, 0);
		}
		else
		{//Carta A
			for (int i = SECRET_ROOM_A_INITIAL; i <= SECRET_ROOM_A_END; i++)
			{
				GenerateMob(i, 0, 0);
				GenerateMob(i, 0, 0);
			}

			GenerateMob(SECRET_ROOM_A_BOSS_INITIAL + rand() % 1, 0, 0);
		}

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));
		return;
	}
#pragma endregion
#pragma region >> Poeira de Fada
	if (Vol == 7)//Poeira de Fada
	{
		int Level = pMob[a_iConn].MOB.BaseScore.Level;
		int maxlevel = pMob[a_iConn].Extra.ClassMaster == MORTAL || pMob[a_iConn].Extra.ClassMaster == ARCH ? MAX_LEVEL : MAX_CLEVEL;

			pMob[a_iConn].MOB.Exp = pMob[a_iConn].Extra.ClassMaster == MORTAL || pMob[a_iConn].Extra.ClassMaster == ARCH ? g_pNextLevel[Level + 1] : g_pNextLevel_2[Level + 1];

			if (pMob[a_iConn].CheckGetLevel())
			{
				SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Level_Up]);
				SendEmotion(a_iConn, 14, 3);
				SendScore(a_iConn);
				SendEtc(a_iConn);
				SetCircletSubGod(a_iConn);
				TitleNotification(a_iConn, pMob[a_iConn].MOB.CurrentScore.Level);

				if (pMob[a_iConn].Extra.ClassMaster == MORTAL)
					DoItemLevel(a_iConn);

			}

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));


		return;
	}
#pragma endregion
#pragma region >> Escritura de Oriharucon / Lactolerium
	if (item->sIndex >= 3445 && item->sIndex <= 3446)
	{
		int Ori = 0;
		int Lac = 0;

		for (int i = 0; i < pMob[a_iConn].MaxCarry; i++)
		{
			if (pMob[a_iConn].MOB.Carry[i].sIndex == 412)
				Ori += pMob[a_iConn].MOB.Carry[i].stEffect[0].cEffect == 61 ? pMob[a_iConn].MOB.Carry[i].stEffect[0].cValue : 1;

			if (pMob[a_iConn].MOB.Carry[i].sIndex == 413)
				Lac += pMob[a_iConn].MOB.Carry[i].stEffect[0].cEffect == 61 ? pMob[a_iConn].MOB.Carry[i].stEffect[0].cValue : 1;
		}

		STRUCT_ITEM Poeira;
		memset(&Poeira, 0, sizeof(STRUCT_ITEM));

		bool Flag = false;

		if (item->sIndex == 3445)
		{
			if (RemoveItem(a_iConn, 412, 10) == TRUE)
			{
				Poeira.sIndex = 3447;
				Poeira.stEffect[0].cEffect = EF_AMOUNT;
				Poeira.stEffect[0].cValue = 10;
				PutItem(a_iConn, &Poeira);

				Flag = true;
			}
		}

		else if (item->sIndex == 3446)
		{
			if (RemoveItem(a_iConn, 413, 10) == TRUE)
			{
				Poeira.sIndex = 3448;
				Poeira.stEffect[0].cEffect = EF_AMOUNT;
				Poeira.stEffect[0].cValue = 10;
				PutItem(a_iConn, &Poeira);

				Flag = true;
			}
		}

		if (Flag)
		{
			SetAffect(a_iConn, 44, 20, 20);
			SendScore(a_iConn);
			SendCarry(a_iConn);
			SendEtc(a_iConn);

			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Processing_Complete]);
		}
		else
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Need_10_Particle]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		SendItem(a_iConn, m->SourType, m->SourPos, item);

		return;
	}
#pragma endregion
#pragma region >> Pacote Oriharucon / Lactolerium
	if (item->sIndex >= 3447 && item->sIndex <= 3448)
	{
		if (item->sIndex == 3447)
		{
			STRUCT_ITEM Item;
			memset(&Item, 0, sizeof(STRUCT_ITEM));

			Item.sIndex = 412;
			Item.stEffect[0].cEffect = EF_AMOUNT;
			Item.stEffect[0].cValue = 10;

			PutItem(a_iConn, &Item);

			memset(item, 0, sizeof STRUCT_ITEM);

			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		else if (item->sIndex == 3448)
		{
			STRUCT_ITEM Item;
			memset(&Item, 0, sizeof(STRUCT_ITEM));

			Item.sIndex = 413;
			Item.stEffect[0].cEffect = EF_AMOUNT;
			Item.stEffect[0].cValue = 10;

			PutItem(a_iConn, &Item);

			memset(item, 0, sizeof STRUCT_ITEM);

			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		memset(item, 0, sizeof STRUCT_ITEM);

		SendItem(a_iConn, m->SourType, m->SourPos, item);
		return;
	}
#pragma endregion
#pragma region >> Pergaminho de Reforma
	if (item->sIndex == 3335)
	{
		int sAffect = GetEmptyAffect(a_iConn, 33);

		if ((pMob[a_iConn].MOB.Equip[0].sIndex == 316 || pMob[a_iConn].MOB.Equip[0].sIndex == 317
			|| pMob[a_iConn].MOB.Equip[0].sIndex == 297 || pMob[a_iConn].MOB.Equip[0].sIndex == 202
			|| pMob[a_iConn].MOB.Equip[0].sIndex == 209 || pMob[a_iConn].MOB.Equip[0].sIndex == 212
			|| pMob[a_iConn].MOB.Equip[0].sIndex == 230 || pMob[a_iConn].MOB.Equip[0].sIndex == 228))
		{
			pMob[a_iConn].MOB.Equip[0].sIndex = pMob[a_iConn].Extra.ClassMaster == MORTAL ?
				pMob[a_iConn].Extra.MortalFace : pMob[a_iConn].Extra.MortalFace + 5 + pMob[a_iConn].MOB.Class;
		}

		pMob[a_iConn].Affect[sAffect].Type = 0;
		pMob[a_iConn].Affect[sAffect].Level = 0;
		pMob[a_iConn].Affect[sAffect].Value = 0;
		pMob[a_iConn].Affect[sAffect].Time = 0;
		SendItem(a_iConn, ITEM_PLACE_EQUIP, 0, &pMob[a_iConn].MOB.Equip[0]);
		SendScore(a_iConn);
		SendEmotion(a_iConn, 14, 3);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		return;
	}
#pragma endregion
#pragma region >> Transformação Javali 
	if (item->sIndex == 3418)
	{
		int sAffect = GetEmptyAffect(a_iConn, 33);

		if (sAffect == -1 || pMob[a_iConn].Affect[sAffect].Type == 33)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_CantEatMore]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		pMob[a_iConn].Affect[sAffect].Type = 33;
		pMob[a_iConn].Affect[sAffect].Level = 1;
		pMob[a_iConn].Affect[sAffect].Value = 1;
		pMob[a_iConn].Affect[sAffect].Time = AFFECT_1H;

		pMob[a_iConn].GetCurrentScore(a_iConn);
		SendItem(a_iConn, ITEM_PLACE_EQUIP, 0, &pMob[a_iConn].MOB.Equip[0]);
		SendScore(a_iConn);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		return;
	}
#pragma endregion
#pragma region >> Transformação Lobo
	if (item->sIndex == 3419)
	{
		int sAffect = GetEmptyAffect(a_iConn, 33);

		if (sAffect == -1 || pMob[a_iConn].Affect[sAffect].Type == 33)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_CantEatMore]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		pMob[a_iConn].Affect[sAffect].Type = 33;
		pMob[a_iConn].Affect[sAffect].Level = 1;
		pMob[a_iConn].Affect[sAffect].Value = 2;
		pMob[a_iConn].Affect[sAffect].Time = AFFECT_1H;

		pMob[a_iConn].GetCurrentScore(a_iConn);
		SendItem(a_iConn, ITEM_PLACE_EQUIP, 0, &pMob[a_iConn].MOB.Equip[0]);
		SendScore(a_iConn);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		return;
	}
#pragma endregion
#pragma region >> Transformação Golem
	if (item->sIndex == 3420)
	{
		int sAffect = GetEmptyAffect(a_iConn, 33);

		if (sAffect == -1 || pMob[a_iConn].Affect[sAffect].Type == 33)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_CantEatMore]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		pMob[a_iConn].Affect[sAffect].Type = 33;
		pMob[a_iConn].Affect[sAffect].Level = 1;
		pMob[a_iConn].Affect[sAffect].Value = 3;
		pMob[a_iConn].Affect[sAffect].Time = AFFECT_1H;

		pMob[a_iConn].GetCurrentScore(a_iConn);
		SendItem(a_iConn, ITEM_PLACE_EQUIP, 0, &pMob[a_iConn].MOB.Equip[0]);
		SendScore(a_iConn);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		return;
	}
#pragma endregion
#pragma region >> Transformação Gremlim
	if (item->sIndex == 3421)
	{
		int sAffect = GetEmptyAffect(a_iConn, 33);

		if (sAffect == -1 || pMob[a_iConn].Affect[sAffect].Type == 33)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_CantEatMore]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		pMob[a_iConn].Affect[sAffect].Type = 33;
		pMob[a_iConn].Affect[sAffect].Level = 1;
		pMob[a_iConn].Affect[sAffect].Value = 4;
		pMob[a_iConn].Affect[sAffect].Time = AFFECT_1H;

		pMob[a_iConn].GetCurrentScore(a_iConn);
		SendItem(a_iConn, ITEM_PLACE_EQUIP, 0, &pMob[a_iConn].MOB.Equip[0]);
		SendScore(a_iConn);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		return;
	}
#pragma endregion
#pragma region >> Transformação Orc
	if (item->sIndex == 3422)
	{
		int sAffect = GetEmptyAffect(a_iConn, 33);

		if (sAffect == -1 || pMob[a_iConn].Affect[sAffect].Type == 33)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_CantEatMore]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		pMob[a_iConn].Affect[sAffect].Type = 33;
		pMob[a_iConn].Affect[sAffect].Level = 1;
		pMob[a_iConn].Affect[sAffect].Value = 5;
		pMob[a_iConn].Affect[sAffect].Time = AFFECT_1H;

		pMob[a_iConn].GetCurrentScore(a_iConn);
		SendItem(a_iConn, ITEM_PLACE_EQUIP, 0, &pMob[a_iConn].MOB.Equip[0]);
		SendScore(a_iConn);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		return;
	}
#pragma endregion
#pragma region >> Transformação Troll
	if (item->sIndex == 3423)
	{
		int sAffect = GetEmptyAffect(a_iConn, 33);

		if (sAffect == -1 || pMob[a_iConn].Affect[sAffect].Type == 33)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_CantEatMore]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		pMob[a_iConn].Affect[sAffect].Type = 33;
		pMob[a_iConn].Affect[sAffect].Level = 1;
		pMob[a_iConn].Affect[sAffect].Value = 6;
		pMob[a_iConn].Affect[sAffect].Time = AFFECT_1H;

		pMob[a_iConn].GetCurrentScore(a_iConn);
		SendItem(a_iConn, ITEM_PLACE_EQUIP, 0, &pMob[a_iConn].MOB.Equip[0]);
		SendScore(a_iConn);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		return;
	}
#pragma endregion
#pragma region >> Transformação Carbunbkle
	if (item->sIndex == 3424)
	{
		int sAffect = GetEmptyAffect(a_iConn, 33);

		if (sAffect == -1 || pMob[a_iConn].Affect[sAffect].Type == 33)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_CantEatMore]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		pMob[a_iConn].Affect[sAffect].Type = 33;
		pMob[a_iConn].Affect[sAffect].Level = 1;
		pMob[a_iConn].Affect[sAffect].Value = 7;
		pMob[a_iConn].Affect[sAffect].Time = AFFECT_1H;

		pMob[a_iConn].GetCurrentScore(a_iConn);
		SendItem(a_iConn, ITEM_PLACE_EQUIP, 0, &pMob[a_iConn].MOB.Equip[0]);
		SendScore(a_iConn);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		return;
	}
#pragma endregion
#pragma region >> Transformação Zumbi
	if (item->sIndex == 3425)
	{
		int sAffect = GetEmptyAffect(a_iConn, 33);

		if (sAffect == -1 || pMob[a_iConn].Affect[sAffect].Type == 33)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_CantEatMore]);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		pMob[a_iConn].Affect[sAffect].Type = 33;
		pMob[a_iConn].Affect[sAffect].Level = 1;
		pMob[a_iConn].Affect[sAffect].Value = 8;
		pMob[a_iConn].Affect[sAffect].Time = 4;

		pMob[a_iConn].GetCurrentScore(a_iConn);
		SendItem(a_iConn, ITEM_PLACE_EQUIP, 0, &pMob[a_iConn].MOB.Equip[0]);
		SendScore(a_iConn);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		return;
	}
#pragma endregion
#pragma region >> Baú do Calabouço
	if (item->sIndex == 5550)
	{
		int rand_ = rand() % 100;
		STRUCT_ITEM Item;
		memset(&Item, 0, sizeof(STRUCT_ITEM));

		if (rand_ <= 10)
			Item.sIndex = 5551;	

		else if (rand_ <= 20)
		{
			Item.sIndex = 4028;
			Item.stEffect[0].cEffect = EF_AMOUNT;
			Item.stEffect[0].cValue = 2;
		}

		else if (rand_ <= 30)
		{
			Item.sIndex = 413;
			Item.stEffect[0].cEffect = EF_AMOUNT;
			Item.stEffect[0].cValue = 2;
		}

		else if (rand_ <= 60)
		{
			Item.sIndex = 412;
			Item.stEffect[0].cEffect = EF_AMOUNT;
			Item.stEffect[0].cValue = 5;
		}

		else
			Item.sIndex = 578;
			
		PutItem(a_iConn, &Item);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));
		return;
	}
#pragma endregion
#pragma region >> Purificador Arcano Nv0
	if (item->sIndex == 5565)
	{
		if (pMob[a_iConn].MOB.Equip[9].sIndex == 0)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].MOB.Equip[9].sIndex >= 5553 && pMob[a_iConn].MOB.Equip[9].sIndex <= 5557 ||
			pMob[a_iConn].MOB.Equip[9].sIndex >= 5560 && pMob[a_iConn].MOB.Equip[9].sIndex <= 5564 ||
			g_pItemList[pMob[a_iConn].MOB.Equip[9].sIndex].nPos == 256 ||
			g_pItemList[pMob[a_iConn].MOB.Equip[9].sIndex].nPos == 512 ||
			g_pItemList[pMob[a_iConn].MOB.Equip[9].sIndex].nPos == 3840 ||
			g_pItemList[pMob[a_iConn].MOB.Equip[9].sIndex].nPos == 2048)
		{
			SendClientMsg(a_iConn, "Não é possivel utilizar nesses itens.");
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

			int sanc = BASE_GetItemSanc(&pMob[a_iConn].MOB.Equip[9]);

			if (sanc < 8)
			{
				sprintf(temp, g_pMessageStringTable[_DN_SANCREQ], 8);
				SendClientMsg(a_iConn, temp);
				SendItem(a_iConn, m->SourType, m->SourPos, item);
				return;
			}

			int RateSucess = 80;
			int _rand = rand() % 115;
			if (_rand > 100)
				_rand -= 15;

			if (_rand <= RateSucess && RateSucess)
			{
				if (pMob[a_iConn].MOB.Equip[9].sIndex == 5552)
				{
					pMob[a_iConn].MOB.Equip[9].sIndex = 5553;
					pMob[a_iConn].MOB.Equip[9].stEffect[0].cEffect = 0;
					pMob[a_iConn].MOB.Equip[9].stEffect[0].cValue = 0;
					pMob[a_iConn].MOB.Equip[9].stEffect[1].cEffect = 0;
					pMob[a_iConn].MOB.Equip[9].stEffect[1].cValue = 0;
					pMob[a_iConn].MOB.Equip[9].stEffect[2].cEffect = 0;
					pMob[a_iConn].MOB.Equip[9].stEffect[2].cValue = 0;
				}

				else if (pMob[a_iConn].MOB.Equip[9].sIndex == 5559)
				{
					pMob[a_iConn].MOB.Equip[9].sIndex = 5560;
					pMob[a_iConn].MOB.Equip[9].stEffect[0].cEffect = 0;
					pMob[a_iConn].MOB.Equip[9].stEffect[0].cValue = 0;
					pMob[a_iConn].MOB.Equip[9].stEffect[1].cEffect = 0;
					pMob[a_iConn].MOB.Equip[9].stEffect[1].cValue = 0;
					pMob[a_iConn].MOB.Equip[9].stEffect[2].cEffect = 0;
					pMob[a_iConn].MOB.Equip[9].stEffect[2].cValue = 0;
				}
			}
			else
			{
				SendClientMsg(a_iConn, "O upgrade do item falhou.");

				int sFace = pMob[a_iConn].MOB.Equip[0].sIndex / 10;

				if (sFace)
					SendEmotion(a_iConn, 15, 0);

				else
					SendEmotion(a_iConn, 20, 0);
			}

			SendItem(a_iConn, ITEM_PLACE_EQUIP, 9, &pMob[a_iConn].MOB.Equip[9]);
			pMob[a_iConn].GetCurrentScore(a_iConn);
			SendScore(a_iConn);

			sprintf(temp, "useitem,purificador nv 0: %d-%d:%d:%d:%d:%d:%d", item->sIndex, item->stEffect[0].cEffect, item->stEffect[0].cValue, item->stEffect[1].cEffect, item->stEffect[1].cValue, item->stEffect[2].cEffect, item->stEffect[2].cValue);
			MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);

			if (amount > 1)
				BASE_SetItemAmount(item, amount - 1);

			else
				memset(item, 0, sizeof(STRUCT_ITEM));

			SendEmotion(a_iConn, 14, 3);
			return;
		}
#pragma endregion
#pragma region >> Purificador Arcano Nv1
	if (item->sIndex == 5566)
	{
		if (pMob[a_iConn].MOB.Equip[9].sIndex == 0)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].MOB.Equip[9].sIndex == 5552 || pMob[a_iConn].MOB.Equip[9].sIndex == 5559 || 
			pMob[a_iConn].MOB.Equip[9].sIndex >= 5554 && pMob[a_iConn].MOB.Equip[9].sIndex <= 5557 ||
			pMob[a_iConn].MOB.Equip[9].sIndex >= 5561 && pMob[a_iConn].MOB.Equip[9].sIndex <= 5564 ||
			g_pItemList[pMob[a_iConn].MOB.Equip[9].sIndex].nPos == 256 ||
			g_pItemList[pMob[a_iConn].MOB.Equip[9].sIndex].nPos == 512 ||
			g_pItemList[pMob[a_iConn].MOB.Equip[9].sIndex].nPos == 3840 ||
			g_pItemList[pMob[a_iConn].MOB.Equip[9].sIndex].nPos == 2048)
		{
			SendClientMsg(a_iConn, "Não é possivel utilizar nesses itens.");
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int sanc = BASE_GetItemSanc(&pMob[a_iConn].MOB.Equip[9]);

		if (sanc < 8)
		{
			sprintf(temp, g_pMessageStringTable[_DN_SANCREQ], 8);
			SendClientMsg(a_iConn, temp);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int RateSucess = 80;
		int _rand = rand() % 115;
		if (_rand > 100)
			_rand -= 15;

		if (_rand <= RateSucess && RateSucess)
		{
			if (pMob[a_iConn].MOB.Equip[9].sIndex == 5553)
			{
				pMob[a_iConn].MOB.Equip[9].sIndex = 5554;
				pMob[a_iConn].MOB.Equip[9].stEffect[0].cEffect = 0;
				pMob[a_iConn].MOB.Equip[9].stEffect[0].cValue = 0;
				pMob[a_iConn].MOB.Equip[9].stEffect[1].cEffect = 0;
				pMob[a_iConn].MOB.Equip[9].stEffect[1].cValue = 0;
				pMob[a_iConn].MOB.Equip[9].stEffect[2].cEffect = 0;
				pMob[a_iConn].MOB.Equip[9].stEffect[2].cValue = 0;
			}

			else if (pMob[a_iConn].MOB.Equip[9].sIndex == 5560)
			{
				pMob[a_iConn].MOB.Equip[9].sIndex = 5561;
				pMob[a_iConn].MOB.Equip[9].stEffect[0].cEffect = 0;
				pMob[a_iConn].MOB.Equip[9].stEffect[0].cValue = 0;
				pMob[a_iConn].MOB.Equip[9].stEffect[1].cEffect = 0;
				pMob[a_iConn].MOB.Equip[9].stEffect[1].cValue = 0;
				pMob[a_iConn].MOB.Equip[9].stEffect[2].cEffect = 0;
				pMob[a_iConn].MOB.Equip[9].stEffect[2].cValue = 0;
			}
		}
		else
		{
			SendClientMsg(a_iConn, "O upgrade do item falhou.");

			int sFace = pMob[a_iConn].MOB.Equip[0].sIndex / 10;

			if (sFace)
				SendEmotion(a_iConn, 15, 0);

			else
				SendEmotion(a_iConn, 20, 0);
		}

		SendItem(a_iConn, ITEM_PLACE_EQUIP, 9, &pMob[a_iConn].MOB.Equip[9]);
		pMob[a_iConn].GetCurrentScore(a_iConn);
		SendScore(a_iConn);

		sprintf(temp, "useitem,purificador nv 1: %d-%d:%d:%d:%d:%d:%d", item->sIndex, item->stEffect[0].cEffect, item->stEffect[0].cValue, item->stEffect[1].cEffect, item->stEffect[1].cValue, item->stEffect[2].cEffect, item->stEffect[2].cValue);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		SendEmotion(a_iConn, 14, 3);
		return;
	}
#pragma endregion
#pragma region >> Purificador Arcano Nv2
	if (item->sIndex == 5567)
	{
		if (pMob[a_iConn].MOB.Equip[9].sIndex == 0)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].MOB.Equip[9].sIndex >= 5552 && pMob[a_iConn].MOB.Equip[9].sIndex <= 5553 ||
			pMob[a_iConn].MOB.Equip[9].sIndex >= 5559 && pMob[a_iConn].MOB.Equip[9].sIndex <= 5560 ||
			pMob[a_iConn].MOB.Equip[9].sIndex >= 5555 && pMob[a_iConn].MOB.Equip[9].sIndex <= 5557 ||
			pMob[a_iConn].MOB.Equip[9].sIndex >= 5562 && pMob[a_iConn].MOB.Equip[9].sIndex <= 5564 ||
			g_pItemList[pMob[a_iConn].MOB.Equip[9].sIndex].nPos == 256 ||
			g_pItemList[pMob[a_iConn].MOB.Equip[9].sIndex].nPos == 512 ||
			g_pItemList[pMob[a_iConn].MOB.Equip[9].sIndex].nPos == 3840 ||
			g_pItemList[pMob[a_iConn].MOB.Equip[9].sIndex].nPos == 2048)
		{
			SendClientMsg(a_iConn, "Não é possivel utilizar nesses itens.");
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int sanc = BASE_GetItemSanc(&pMob[a_iConn].MOB.Equip[9]);

		if (sanc < 8)
		{
			sprintf(temp, g_pMessageStringTable[_DN_SANCREQ], 8);
			SendClientMsg(a_iConn, temp);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int RateSucess = 80;
		int _rand = rand() % 115;
		if (_rand > 100)
			_rand -= 15;

		if (_rand <= RateSucess && RateSucess)
		{
			if (pMob[a_iConn].MOB.Equip[9].sIndex == 5554)
			{
				pMob[a_iConn].MOB.Equip[9].sIndex = 5555;
				pMob[a_iConn].MOB.Equip[9].stEffect[0].cEffect = 0;
				pMob[a_iConn].MOB.Equip[9].stEffect[0].cValue = 0;
				pMob[a_iConn].MOB.Equip[9].stEffect[1].cEffect = 0;
				pMob[a_iConn].MOB.Equip[9].stEffect[1].cValue = 0;
				pMob[a_iConn].MOB.Equip[9].stEffect[2].cEffect = 0;
				pMob[a_iConn].MOB.Equip[9].stEffect[2].cValue = 0;
			}

			else if (pMob[a_iConn].MOB.Equip[9].sIndex == 5561)
			{
				pMob[a_iConn].MOB.Equip[9].sIndex = 5562;
				pMob[a_iConn].MOB.Equip[9].stEffect[0].cEffect = 0;
				pMob[a_iConn].MOB.Equip[9].stEffect[0].cValue = 0;
				pMob[a_iConn].MOB.Equip[9].stEffect[1].cEffect = 0;
				pMob[a_iConn].MOB.Equip[9].stEffect[1].cValue = 0;
				pMob[a_iConn].MOB.Equip[9].stEffect[2].cEffect = 0;
				pMob[a_iConn].MOB.Equip[9].stEffect[2].cValue = 0;
			}
		}
		else
		{
			SendClientMsg(a_iConn, "O upgrade do item falhou.");

			int sFace = pMob[a_iConn].MOB.Equip[0].sIndex / 10;

			if (sFace)
				SendEmotion(a_iConn, 15, 0);

			else
				SendEmotion(a_iConn, 20, 0);
		}

		SendItem(a_iConn, ITEM_PLACE_EQUIP, 9, &pMob[a_iConn].MOB.Equip[9]);
		pMob[a_iConn].GetCurrentScore(a_iConn);
		SendScore(a_iConn);

		sprintf(temp, "useitem,purificador nv 2: %d-%d:%d:%d:%d:%d:%d", item->sIndex, item->stEffect[0].cEffect, item->stEffect[0].cValue, item->stEffect[1].cEffect, item->stEffect[1].cValue, item->stEffect[2].cEffect, item->stEffect[2].cValue);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		SendEmotion(a_iConn, 14, 3);
		return;
	}
#pragma endregion
#pragma region >> Purificador Arcano Nv3
	if (item->sIndex == 5568)
	{
		if (pMob[a_iConn].MOB.Equip[9].sIndex == 0)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].MOB.Equip[9].sIndex >= 5552 && pMob[a_iConn].MOB.Equip[9].sIndex <= 5554 ||
			pMob[a_iConn].MOB.Equip[9].sIndex >= 5559 && pMob[a_iConn].MOB.Equip[9].sIndex <= 5561 ||
			pMob[a_iConn].MOB.Equip[9].sIndex >= 5556 && pMob[a_iConn].MOB.Equip[9].sIndex <= 5557 ||
			pMob[a_iConn].MOB.Equip[9].sIndex >= 5563 && pMob[a_iConn].MOB.Equip[9].sIndex <= 5564 ||
			g_pItemList[pMob[a_iConn].MOB.Equip[9].sIndex].nPos == 256 ||
			g_pItemList[pMob[a_iConn].MOB.Equip[9].sIndex].nPos == 512 ||
			g_pItemList[pMob[a_iConn].MOB.Equip[9].sIndex].nPos == 3840 ||
			g_pItemList[pMob[a_iConn].MOB.Equip[9].sIndex].nPos == 2048)
		{
			SendClientMsg(a_iConn, "Não é possivel utilizar nesses itens.");
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int sanc = BASE_GetItemSanc(&pMob[a_iConn].MOB.Equip[9]);

		if (sanc < 8)
		{
			sprintf(temp, g_pMessageStringTable[_DN_SANCREQ], 8);
			SendClientMsg(a_iConn, temp);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int RateSucess = 80;
		int _rand = rand() % 115;
		if (_rand > 100)
			_rand -= 15;

		if (_rand <= RateSucess && RateSucess)
		{
			if (pMob[a_iConn].MOB.Equip[9].sIndex == 5555)
			{
				pMob[a_iConn].MOB.Equip[9].sIndex = 5556;
				pMob[a_iConn].MOB.Equip[9].stEffect[0].cEffect = 0;
				pMob[a_iConn].MOB.Equip[9].stEffect[0].cValue = 0;
				pMob[a_iConn].MOB.Equip[9].stEffect[1].cEffect = 0;
				pMob[a_iConn].MOB.Equip[9].stEffect[1].cValue = 0;
				pMob[a_iConn].MOB.Equip[9].stEffect[2].cEffect = 0;
				pMob[a_iConn].MOB.Equip[9].stEffect[2].cValue = 0;
			}

			else if (pMob[a_iConn].MOB.Equip[9].sIndex == 5562)
			{
				pMob[a_iConn].MOB.Equip[9].sIndex = 5563;
				pMob[a_iConn].MOB.Equip[9].stEffect[0].cEffect = 0;
				pMob[a_iConn].MOB.Equip[9].stEffect[0].cValue = 0;
				pMob[a_iConn].MOB.Equip[9].stEffect[1].cEffect = 0;
				pMob[a_iConn].MOB.Equip[9].stEffect[1].cValue = 0;
				pMob[a_iConn].MOB.Equip[9].stEffect[2].cEffect = 0;
				pMob[a_iConn].MOB.Equip[9].stEffect[2].cValue = 0;
			}
		}
		else
		{
			SendClientMsg(a_iConn, "O upgrade do item falhou.");

			int sFace = pMob[a_iConn].MOB.Equip[0].sIndex / 10;

			if (sFace)
				SendEmotion(a_iConn, 15, 0);

			else
				SendEmotion(a_iConn, 20, 0);
		}

		SendItem(a_iConn, ITEM_PLACE_EQUIP, 9, &pMob[a_iConn].MOB.Equip[9]);
		pMob[a_iConn].GetCurrentScore(a_iConn);
		SendScore(a_iConn);

		sprintf(temp, "useitem,purificador nv 3: %d-%d:%d:%d:%d:%d:%d", item->sIndex, item->stEffect[0].cEffect, item->stEffect[0].cValue, item->stEffect[1].cEffect, item->stEffect[1].cValue, item->stEffect[2].cEffect, item->stEffect[2].cValue);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		SendEmotion(a_iConn, 14, 3);
		return;
	}
#pragma endregion
#pragma region >> Purificador Arcano Nv4
	if (item->sIndex == 5569)
	{
		if (pMob[a_iConn].MOB.Equip[9].sIndex == 0)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].MOB.Equip[9].sIndex >= 5552 && pMob[a_iConn].MOB.Equip[9].sIndex <= 5555 ||
			pMob[a_iConn].MOB.Equip[9].sIndex >= 5559 && pMob[a_iConn].MOB.Equip[9].sIndex <= 5562 ||
			pMob[a_iConn].MOB.Equip[9].sIndex == 5557 ||
			pMob[a_iConn].MOB.Equip[9].sIndex == 5564 ||
			g_pItemList[pMob[a_iConn].MOB.Equip[9].sIndex].nPos == 256 ||
			g_pItemList[pMob[a_iConn].MOB.Equip[9].sIndex].nPos == 512 ||
			g_pItemList[pMob[a_iConn].MOB.Equip[9].sIndex].nPos == 3840 ||
			g_pItemList[pMob[a_iConn].MOB.Equip[9].sIndex].nPos == 2048)
		{
			SendClientMsg(a_iConn, "Não é possivel utilizar nesses itens.");
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int sanc = BASE_GetItemSanc(&pMob[a_iConn].MOB.Equip[9]);

		if (sanc < 8)
		{
			sprintf(temp, g_pMessageStringTable[_DN_SANCREQ], 8);
			SendClientMsg(a_iConn, temp);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int RateSucess = 80;
		int _rand = rand() % 115;
		if (_rand > 100)
			_rand -= 15;

		if (_rand <= RateSucess && RateSucess)
		{
			if (pMob[a_iConn].MOB.Equip[9].sIndex == 5556)
			{
				pMob[a_iConn].MOB.Equip[9].sIndex = 5557;
				pMob[a_iConn].MOB.Equip[9].stEffect[0].cEffect = 0;
				pMob[a_iConn].MOB.Equip[9].stEffect[0].cValue = 0;
				pMob[a_iConn].MOB.Equip[9].stEffect[1].cEffect = 0;
				pMob[a_iConn].MOB.Equip[9].stEffect[1].cValue = 0;
				pMob[a_iConn].MOB.Equip[9].stEffect[2].cEffect = 0;
				pMob[a_iConn].MOB.Equip[9].stEffect[2].cValue = 0;
			}

			else if (pMob[a_iConn].MOB.Equip[9].sIndex == 5563)
			{
				pMob[a_iConn].MOB.Equip[9].sIndex = 5564;
				pMob[a_iConn].MOB.Equip[9].stEffect[0].cEffect = 0;
				pMob[a_iConn].MOB.Equip[9].stEffect[0].cValue = 0;
				pMob[a_iConn].MOB.Equip[9].stEffect[1].cEffect = 0;
				pMob[a_iConn].MOB.Equip[9].stEffect[1].cValue = 0;
				pMob[a_iConn].MOB.Equip[9].stEffect[2].cEffect = 0;
				pMob[a_iConn].MOB.Equip[9].stEffect[2].cValue = 0;
			}
		}
		else
		{
			SendClientMsg(a_iConn, "O upgrade do item falhou.");

			int sFace = pMob[a_iConn].MOB.Equip[0].sIndex / 10;

			if (sFace)
				SendEmotion(a_iConn, 15, 0);

			else
				SendEmotion(a_iConn, 20, 0);
		}

		SendItem(a_iConn, ITEM_PLACE_EQUIP, 9, &pMob[a_iConn].MOB.Equip[9]);
		pMob[a_iConn].GetCurrentScore(a_iConn);
		SendScore(a_iConn);

		sprintf(temp, "useitem,purificador nivel 4: %d-%d:%d:%d:%d:%d:%d", item->sIndex, item->stEffect[0].cEffect, item->stEffect[0].cValue, item->stEffect[1].cEffect, item->stEffect[1].cValue, item->stEffect[2].cEffect, item->stEffect[2].cValue);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		SendEmotion(a_iConn, 14, 3);
		return;
	}
#pragma endregion
#pragma region >> Purificador Arcano Nv5
	if (item->sIndex == 5570)
	{
		if (pMob[a_iConn].MOB.Equip[9].sIndex == 0)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].MOB.Equip[9].sIndex >= 5552 && pMob[a_iConn].MOB.Equip[9].sIndex <= 5556 ||
			pMob[a_iConn].MOB.Equip[9].sIndex >= 5559 && pMob[a_iConn].MOB.Equip[9].sIndex <= 5563 ||
			g_pItemList[pMob[a_iConn].MOB.Equip[9].sIndex].nPos == 256 ||
			g_pItemList[pMob[a_iConn].MOB.Equip[9].sIndex].nPos == 512 ||
			g_pItemList[pMob[a_iConn].MOB.Equip[9].sIndex].nPos == 3840 ||
			g_pItemList[pMob[a_iConn].MOB.Equip[9].sIndex].nPos == 2048)
		{
			SendClientMsg(a_iConn, "Não é possivel utilizar nesses itens.");
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int sanc = BASE_GetItemSanc(&pMob[a_iConn].MOB.Equip[9]);

		if (sanc < 8)
		{
			sprintf(temp, g_pMessageStringTable[_DN_SANCREQ], 8);
			SendClientMsg(a_iConn, temp);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int RateSucess = 80;
		int _rand = rand() % 115;
		if (_rand > 100)
			_rand -= 15;

		if (_rand <= RateSucess && RateSucess)
		{
			if (pMob[a_iConn].MOB.Equip[9].sIndex == 5557)
			{
				pMob[a_iConn].MOB.Equip[9].stEffect[0].cEffect = EF_MPADD;
				pMob[a_iConn].MOB.Equip[9].stEffect[0].cValue += 10;
				
			}

			else if (pMob[a_iConn].MOB.Equip[9].sIndex == 5564)
			{
				pMob[a_iConn].MOB.Equip[9].stEffect[0].cEffect = EF_HPADD;
				pMob[a_iConn].MOB.Equip[9].stEffect[0].cValue += 10;
			}
		}
		else
		{
			SendClientMsg(a_iConn, "O upgrade do item falhou.");

			int sFace = pMob[a_iConn].MOB.Equip[0].sIndex / 10;

			if (sFace)
				SendEmotion(a_iConn, 15, 0);

			else
				SendEmotion(a_iConn, 20, 0);
		}

		SendItem(a_iConn, ITEM_PLACE_EQUIP, 9, &pMob[a_iConn].MOB.Equip[9]);
		pMob[a_iConn].GetCurrentScore(a_iConn);
		SendScore(a_iConn);

		sprintf(temp, "useitem,purificador nv 5: %d-%d:%d:%d:%d:%d:%d", item->sIndex, item->stEffect[0].cEffect, item->stEffect[0].cValue, item->stEffect[1].cEffect, item->stEffect[1].cValue, item->stEffect[2].cEffect, item->stEffect[2].cValue);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		SendEmotion(a_iConn, 14, 3);
		return;
	}
#pragma endregion
#pragma region >> Extração Arcana
	if (item->sIndex == 5571)
	{
		if (pMob[a_iConn].MOB.Equip[9].sIndex == 0)
		{
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].MOB.Equip[9].sIndex >= 5552 && pMob[a_iConn].MOB.Equip[9].sIndex <= 5556 ||
			pMob[a_iConn].MOB.Equip[9].sIndex >= 5559 && pMob[a_iConn].MOB.Equip[9].sIndex <= 5563 ||
			g_pItemList[pMob[a_iConn].MOB.Equip[9].sIndex].nPos == 256 ||
			g_pItemList[pMob[a_iConn].MOB.Equip[9].sIndex].nPos == 512 ||
			g_pItemList[pMob[a_iConn].MOB.Equip[9].sIndex].nPos == 3840 ||
			g_pItemList[pMob[a_iConn].MOB.Equip[9].sIndex].nPos == 2048)
		{
			SendClientMsg(a_iConn, "Não é possivel utilizar nesses itens.");
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int sanc = BASE_GetItemSanc(&pMob[a_iConn].MOB.Equip[9]);

		if (sanc < 8)
		{
			sprintf(temp, g_pMessageStringTable[_DN_SANCREQ], 8);
			SendClientMsg(a_iConn, temp);
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		pMob[a_iConn].MOB.Equip[9].stEffect[1].cEffect = item->stEffect[1].cEffect;
		pMob[a_iConn].MOB.Equip[9].stEffect[1].cValue = item->stEffect[1].cValue;

		pMob[a_iConn].MOB.Equip[9].stEffect[2].cEffect = item->stEffect[2].cEffect;
		pMob[a_iConn].MOB.Equip[9].stEffect[2].cValue = item->stEffect[2].cValue;


		SendItem(a_iConn, ITEM_PLACE_EQUIP, 9, &pMob[a_iConn].MOB.Equip[9]);
		pMob[a_iConn].GetCurrentScore(a_iConn);
		SendScore(a_iConn);

		sprintf(temp, "useitem,Extracao lendario: %d-%d:%d:%d:%d:%d:%d", item->sIndex, item->stEffect[0].cEffect, item->stEffect[0].cValue, item->stEffect[1].cEffect, item->stEffect[1].cValue, item->stEffect[2].cEffect, item->stEffect[2].cValue);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		SendEmotion(a_iConn, 14, 3);
		return;
	}
#pragma endregion
#pragma region >> Elixir de Kersef
	if (item->sIndex == 5573)
	{	
		//Coveiro
		if (pMob[a_iConn].TargetX > 2379 && pMob[a_iConn].TargetY > 2076 && pMob[a_iConn].TargetX < 2426 && pMob[a_iConn].TargetY < 2133)
		{
			SendClientMsg(a_iConn, "Não pode usar aqui.");
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}	
		//Jardin
		if (pMob[a_iConn].TargetX > 2228 && pMob[a_iConn].TargetY > 1700 && pMob[a_iConn].TargetX < 2257 && pMob[a_iConn].TargetY < 1728)
		{
			SendClientMsg(a_iConn, "Não pode usar aqui.");
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}
		//Kaizen
		if (pMob[a_iConn].TargetX > 459 && pMob[a_iConn].TargetY > 3887 && pMob[a_iConn].TargetX < 497 && pMob[a_iConn].TargetY < 3916)
		{
			SendClientMsg(a_iConn, "Não pode usar aqui.");
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}
		//Hidra
		if (pMob[a_iConn].TargetX > 658 && pMob[a_iConn].TargetY > 3728 && pMob[a_iConn].TargetX < 703 && pMob[a_iConn].TargetY < 3762)
		{
			SendClientMsg(a_iConn, "Não pode usar aqui.");
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}
		//Elfos
		if (pMob[a_iConn].TargetX > 1312 && pMob[a_iConn].TargetY > 4027 && pMob[a_iConn].TargetX < 1348 && pMob[a_iConn].TargetY < 4055)
		{
			SendClientMsg(a_iConn, "Não pode usar aqui.");
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		if (pMob[a_iConn].Extra.CheckTimeKersef >= 900)
		{
			SendClientMsg(a_iConn, "Não pode comer mais.");
			SendItem(a_iConn, m->SourType, m->SourPos, item);
			return;
		}

		int i = 0;
		pMob[a_iConn].Extra.CheckTimeKersef += 300;

		if (pMob[a_iConn].Extra.CheckTimeKersef == 300)
			i = 5;

		else if (pMob[a_iConn].Extra.CheckTimeKersef == 600)
			i = 10;

		else if (pMob[a_iConn].Extra.CheckTimeKersef == 900)
			i = 15;

		sprintf(temp, "Seu tempo em quests aumentou (%d) / (+5) minutos", i);
		SendClientMsg(a_iConn, temp);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);

		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		return;
	}
#pragma endregion
}