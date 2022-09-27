#include <Windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>
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
#include "ProcessDBMessage.h"
#include "CCastleZakum.h"
#include "FadaDourada.h"
#include "KefraDrop.h"
#include "SombraNegra.h"
#include "BossCamp.h"
#include "GuildHall.h"
#include "InvadeArmia.h"

void MobKilled(int target, int a_iConn, int PosX, int PosY)
{
	try
	{
		if (a_iConn <= 0 || a_iConn >= MAX_MOB || target <= 0 || target >= MAX_MOB || pMob[target].Mode == USER_EMPTY)
			return;

		STRUCT_ITEM* FairySlot = &pMob[target].MOB.Equip[13];
		MSG_CreateMob sCreateMob;

		if (pMob[target].MOB.CurrentScore.Level >= 1000)
		{
			pMob[target].MOB.CurrentScore.Hp = pMob[target].MOB.CurrentScore.MaxHp;

			if (target < MAX_USER)
				SetReqHp(target);

			GetCreateMob(target, &sCreateMob);
			GridMulticast(pMob[target].TargetX, pMob[target].TargetY, (MSG_STANDARD*)&sCreateMob, 0);
			SendScore(a_iConn);
			return;
		}

#pragma region Nyerds
		if (pMob[target].MOB.Equip[13].sIndex == 769 && g_pRvrWar.Status == 0 && GTorreState == 0 && CastleState == 0)
		{
			int sanc = BASE_GetItemSanc(FairySlot);

			if (sanc > 0)
			{
				sanc--;

				if (FairySlot->stEffect[0].cEffect == 43)
					FairySlot->stEffect[0].cValue = sanc;

				else if (FairySlot->stEffect[1].cEffect == 43)
					FairySlot->stEffect[1].cValue = sanc;

				else if (FairySlot->stEffect[2].cEffect == 43)
					FairySlot->stEffect[2].cValue = sanc;
			}
			else
				BASE_ClearItem(FairySlot);

			if (target > 0 && target <= MAX_USER)
			{
				SendItem(target, ITEM_PLACE_EQUIP, 13, &pMob[target].MOB.Equip[13]);
				SendEmotion(target, 14, 2);
			}

			SendEquip(target, 0);

			pMob[target].MOB.CurrentScore.Hp = pMob[target].MOB.CurrentScore.MaxHp;

			if (target < MAX_USER)
				SetReqHp(target);

			GetCreateMob(target, &sCreateMob);
			GridMulticast(pMob[target].TargetX, pMob[target].TargetY, (MSG_STANDARD*)&sCreateMob, 0);
			SendScore(a_iConn);
			return;
		}
#pragma endregion
#pragma region Morte nas quests
		//Coveiro
		if (pMob[a_iConn].TargetX > 2379 && pMob[a_iConn].TargetY > 2076 && pMob[a_iConn].TargetX < 2426 && pMob[a_iConn].TargetY < 2133)
			pMob[a_iConn].Extra.CheckTimeKersef = 0;

		//Jardin
		if (pMob[a_iConn].TargetX > 2228 && pMob[a_iConn].TargetY > 1700 && pMob[a_iConn].TargetX < 2257 && pMob[a_iConn].TargetY < 1728)
			pMob[a_iConn].Extra.CheckTimeKersef = 0;

		//Kaizen
		if (pMob[a_iConn].TargetX > 459 && pMob[a_iConn].TargetY > 3887 && pMob[a_iConn].TargetX < 497 && pMob[a_iConn].TargetY < 3916)
			pMob[a_iConn].Extra.CheckTimeKersef = 0;

		//Hidra
		if (pMob[a_iConn].TargetX > 658 && pMob[a_iConn].TargetY > 3728 && pMob[a_iConn].TargetX < 703 && pMob[a_iConn].TargetY < 3762)
			pMob[a_iConn].Extra.CheckTimeKersef = 0;

		//Elfos
		if (pMob[a_iConn].TargetX > 1312 && pMob[a_iConn].TargetY > 4027 && pMob[a_iConn].TargetX < 1348 && pMob[a_iConn].TargetY < 4055)
			pMob[a_iConn].Extra.CheckTimeKersef = 0;
#pragma endregion
#pragma region Pergaminho da Ressurreição
		for (int i = 0; i < pMob[target].MaxCarry; i++)
		{
			if (pMob[target].MOB.Carry[i].sIndex == 3463)
			{
				int amount = BASE_GetItemAmount(&pMob[target].MOB.Carry[i]);

				if (amount > 1)
					BASE_SetItemAmount(&pMob[target].MOB.Carry[i], amount - 1);
				else
					BASE_ClearItem(&pMob[target].MOB.Carry[i]);

				SendItem(target, ITEM_PLACE_CARRY, i, &pMob[target].MOB.Carry[i]);

				pMob[target].MOB.CurrentScore.Hp = pMob[target].MOB.CurrentScore.MaxHp;
				pMob[target].MOB.CurrentScore.Mp = pMob[target].MOB.CurrentScore.MaxMp;

				pMob[target].GetCurrentScore(target);
				SetReqHp(target);
				SendScore(target);
				SendCreateMob(target, target, 1);
				return;
			}
		}
#pragma endregion
#pragma region Morte na Guerra de Noatum
		if (CastleState > 1 && pMob[target].TargetX == 1046 && pMob[target].TargetY == 1690 && target > 0 && target < MAX_USER)
		{
			DoTeleport(target, 1066, 1717);
			return;
		}
#pragma endregion
#pragma region Morte na Guerra RvR
		if (pMob[target].GenerateIndex == TORRE_RVR_BLUE || pMob[target].GenerateIndex == TORRE_RVR_RED)
		{
			if (a_iConn == 29999)
			{
				DeleteMob(target, 1);
				return;
			}

			int connId = a_iConn;
			if (connId > MAX_USER)
			{
				int summonerId = pMob[connId].Summoner;

				if (summonerId > 0 && summonerId < MAX_USER)
					connId = summonerId;
				else
					connId = 0;
			}

			if (connId <= MAX_USER && pUser[connId].Mode != USER_PLAY)
				connId = 0;

			// Ressuscita a torre
			pMob[target].MOB.CurrentScore.Hp = pMob[target].MOB.CurrentScore.MaxHp;

			MSG_CreateMob packet;
			GetCreateMob(target, &packet);

			GridMulticast(pMob[target].TargetX, pMob[target].TargetY, (MSG_STANDARD*)&packet, 0);

			int towerId = 0;

			if (pMob[target].GenerateIndex == TORRE_RVR_BLUE)
				towerId = 1;
			else
				towerId = 0;

			const char* tDeath = towerId == 1 ? "Blue" : "Red";

			g_pRvrWar.Points[towerId] += 25;

			for (INT32 i = 1; i < MAX_USER; i++)
			{
				if (pUser[i].Mode != USER_PLAY)
					continue;

				if (pMob[i].TargetX >= AREA_RVR_MINX && pMob[i].TargetX <= AREA_RVR_MAXX && pMob[i].TargetY >= AREA_RVR_MINY && pMob[i].TargetY <= AREA_RVR_MAXY)
				{
					sprintf(temp, "A Torre do Reino [%s] foi Destruida!!", tDeath);
					SendClientMsg(i, temp);// se quiser pode fala qual da seguinte forma:  , (pMob[i].GenerateIndex == TORRE_RVR_BLUE) ? "Blue" : "Red", (towerId == 0) ? "Blue" : "Red");

				}
				// RVR
				if (pMob[i].TargetX >= AREA_RVR_MINX && pMob[i].TargetX <= AREA_RVR_MAXX &&
					pMob[i].TargetY >= AREA_RVR_MINY && pMob[i].TargetY <= AREA_RVR_MAXY && g_pRvrWar.Status == 1)
				{
					int cape = pMob[i].MOB.Clan;

					INT32 posX = 0;
					INT32 posY = 0;

					//srand(time(NULL));
					// Adicionar 
					if (cape == 7)
					{
						posX = 1754 + rand() % 4;
						posY = 1982 + rand() % 4;
					}
					else if (cape == 8)
					{
						posX = 1694 + rand() % 4;
						posY = 1980 + rand() % 4;
					}

					if (posX != 0 && posY != 0)
						DoTeleport(i, posX, posY);
				}
			}

			for (int i = 1; i < MAX_USER; i++)
			{
				if (pMob[i].TargetX >= AREA_RVR_MINX && pMob[i].TargetX <= AREA_RVR_MAXX &&
					pMob[i].TargetY >= AREA_RVR_MINY && pMob[i].TargetY <= AREA_RVR_MAXY)
				{
					if (pUser[i].Mode != USER_PLAY)
						continue;

					// Atualiza o placar de kill
					SendCounterMob(i, g_pRvrWar.Points[1], g_pRvrWar.Points[0]);
				}
			}

			return;
		}

#pragma endregion
#pragma region Crias EXP
		if (a_iConn >= MAX_USER && pMob[a_iConn].MOB.Clan == 4 && pMob[a_iConn].MOB.Equip[0].sIndex >= 315 && pMob[a_iConn].MOB.Equip[0].sIndex <= 345 && target > MAX_USER && pMob[target].MOB.Clan != 4)
		{
			int summoner = pMob[a_iConn].Summoner;

			if (summoner > 0 && summoner < MAX_USER && pUser[summoner].Mode && pMob[summoner].Mode)
			{
				STRUCT_ITEM* Mount = &pMob[summoner].MOB.Equip[14];

				if (pMob[summoner].MOB.Equip[14].sIndex >= 2330 && pMob[summoner].MOB.Equip[14].sIndex < 2359)
				{
					unsigned char XP = Mount->stEffect[1].cEffect;
					unsigned char Crescimento = Mount->stEffect[2].cValue;

					unsigned char exp = XP + 100;

					if (Mount->sIndex == 2330)
						exp = XP + 25;

					else if (Mount->sIndex == 2331)
						exp = XP + 35;

					else if (Mount->sIndex == 2332)
						exp = XP + 45;

					else if (Mount->sIndex == 2333)
						exp = XP + 55;

					else if (Mount->sIndex == 2334)
						exp = XP + 65;

					else if (Mount->sIndex == 2335)
						exp = XP + 75;

					if (XP < pMob[target].MOB.CurrentScore.Level && XP < 100)
					{
						Crescimento = Crescimento + 1;

						if (Crescimento < exp)
						{
							Mount->stEffect[2].cValue = Crescimento;
							SendItem(summoner, ITEM_PLACE_EQUIP, 14, &pMob[summoner].MOB.Equip[14]);
						}
						else
						{
							Crescimento = 1;
							XP = XP + 1;
							Mount->stEffect[2].cValue = 1;
							Mount->stEffect[1].cEffect = XP;
							SendClientMsg(summoner, g_pMessageStringTable[_NN_Mount_Level]);
							SendItem(summoner, ITEM_PLACE_EQUIP, 14, &pMob[summoner].MOB.Equip[14]);
							MountProcess(summoner, 0);
						}
					}
				}
			}
		}
#pragma endregion
#pragma region Invocações

		MSG_CNFMobKill sm;
		memset(&sm, 0, sizeof(MSG_CNFMobKill));

		sm.Type = _MSG_CNFMobKill;
		sm.Size = sizeof(MSG_CNFMobKill);
		sm.ID = ESCENE_FIELD;

		sm.KilledMob = target;
		sm.Killer = a_iConn;

		pMob[target].MOB.CurrentScore.Hp = 0;

		int Leader = pMob[a_iConn].Leader;

		if (Leader == 0)
			Leader = a_iConn;

		if (a_iConn >= MAX_USER && pMob[a_iConn].MOB.Clan == 4)
		{
			int Summoner = pMob[a_iConn].Summoner;

			if (Summoner <= 0 || Summoner >= MAX_USER || pUser[Summoner].Mode != USER_PLAY)
			{
				GridMulticast(pMob[target].TargetX, pMob[target].TargetY, (MSG_STANDARD*)&sm, 0);

				if (target > MAX_USER)
					DeleteMob(target, 1);

				return;
			}

			a_iConn = Summoner;
		}
#pragma endregion
#pragma region PLACAR RVR
		if (target < MAX_USER && a_iConn < MAX_USER)
		{
			if (pMob[target].TargetX >= AREA_RVR_MINX && pMob[target].TargetX <= AREA_RVR_MAXX &&
				pMob[target].TargetY >= AREA_RVR_MINY && pMob[target].TargetY <= AREA_RVR_MAXY && g_pRvrWar.Status == 1)
			{
				int capeKiller = pMob[a_iConn].MOB.Clan;
				int capeDead = pMob[target].MOB.Clan;

				if ((capeKiller == 8 || capeKiller == 7) &&
					(capeDead == 8 || capeDead == 7))
				{
					if (capeDead != capeKiller)
					{
						int capeId = capeKiller - 7;

						g_pRvrWar.Points[capeId]++;

						for (INT32 i = 1; i < MAX_USER; i++)
						{
							if (pUser[i].Mode != USER_PLAY)
								continue;

							if (pMob[i].TargetX >= AREA_RVR_MINX && pMob[i].TargetX <= AREA_RVR_MAXX &&
								pMob[i].TargetY >= AREA_RVR_MINY && pMob[i].TargetY <= AREA_RVR_MINY)
							{
								char tmp[128];
								sprintf(tmp, "%s matou %s e pontuou para o reino %s", pMob[a_iConn].MOB.MobName, pMob[target].MOB.MobName, (capeId == 0) ? "Blue" : "Red");
								SendClientMsg(i, tmp);

								// Atualiza o placar de kill
								SendCounterMob(i, g_pRvrWar.Points[1], g_pRvrWar.Points[0]);
							}
						}

					}
				}
			}
		}
#pragma endregion
#pragma region PvE
		if (target >= MAX_USER || pMob[target].MOB.BaseScore.Level > MAX_LEVEL + 5)
		{
			if (target >= MAX_USER || pMob[target].MOB.BaseScore.Level <= MAX_LEVEL)
			{
				if (a_iConn < MAX_USER && pMob[target].MOB.Clan != 4)
				{
#pragma region Distribuição da EXP
					int MobExp = GetExpApply(pMob[a_iConn].Extra, (int)pMob[target].MOB.Exp, pMob[a_iConn].MOB.CurrentScore.Level, pMob[target].MOB.CurrentScore.Level);
					int FinalExp = 0;

					int UNK_1 = 30;
					int UNK_2 = 0;
					int UNK_3 = pMob[a_iConn].Extra.ClassMaster;

					int tx = pMob[a_iConn].TargetX;
					int ty = pMob[a_iConn].TargetY;

					int party = 0;

					if (UNK_3 > 0 && UNK_3 <= MAX_PARTY)
					{
						int NumMob = g_EmptyMob + UNK_3;

						if (UNK_3 > 1)
							NumMob = NumMob + PARTYBONUS - 100;

						int eMob = MobExp;
						int isExp = NumMob * MobExp / 100;

						struct tm when;
						time_t now;
						time(&now);
						when = *localtime(&now);

						for (int i = 0; i < MAX_PARTY + 1; ++i)
						{
							party = 0;

							if (Leader && i < MAX_PARTY)
								party = pMob[Leader].PartyList[i];
							else
								party = Leader;

#pragma region Pesadelo Arcano
							if (party > 0 && party < MAX_USER && pMob[party].MOB.CurrentScore.Hp > 0 && (tx / 128) == 9 && (pMob[party].TargetX / 128) == 9
								&& (ty / 128) == 1 && (pMob[party].TargetY / 128) == 1)
							{
								isExp = GetExpApply(pMob[party].Extra, (int)pMob[target].MOB.Exp, pMob[party].MOB.CurrentScore.Level, pMob[target].MOB.CurrentScore.Level);

								int myLevel = pMob[party].MOB.CurrentScore.Level;

								//if (pMob[party].Extra.ClassMaster != MORTAL && pMob[party].Extra.ClassMaster != ARCH)
								//	myLevel += MAX_LEVEL + 1;

								int exp = (UNK_1 + myLevel) * isExp / (UNK_1 + myLevel);
								if (exp > 0 && exp <= 10000000)
								{
									if (pMob[party].Extra.ClassMaster == MORTAL)
									{
										if (myLevel <= 200) // 150k
											exp /= 1;

										else if (myLevel <= 300) // 120k
											exp /= 0.84f;

										else if (myLevel <= 356) // 80k
											exp /= 1.05f;

										else if (myLevel <= 370) // 50k
											exp /= 1.63f;

										else if (myLevel <= 380) // 40k
											exp /= 1.95f;

										else if (myLevel <= 390) // 30k
											exp /= 2.55f;

										else if (myLevel <= 399) // 20k
											exp /= 3.70f;
									}

									if (pMob[party].Extra.ClassMaster == ARCH)
									{
										if (myLevel <= 200) // Exp Média 90k
											exp /= 0.72f;

										else if (myLevel <= 300)// Exp Média 70k
											exp /= 0.84f;

										else if (myLevel <= 356)// Exp Média 30k
											exp /= 1.40f;

										else if (myLevel <= 360)// Exp Média 8k
											exp /= 2.75f;

										else if (myLevel <= 370)// Exp Média 6k
											exp /= 3.60f;

										else if (myLevel <= 380) // Exp Média 2.5k
											exp /= 8;

										else if (myLevel <= 390)  // Exp Média 1.8k
											exp /= 15;

										else if (myLevel <= 400) // Exp Média 1k
											exp /= 25;
									}

									if (pMob[party].Extra.ClassMaster != MORTAL && pMob[party].Extra.ClassMaster != ARCH)
									{
										if (myLevel < 20)
											exp /= 10;

										else if (myLevel < 50)
											exp /= 20;

										else if (myLevel < 70)
											exp /= 40;

										else if (myLevel < 120)
											exp /= 50;

										else if (myLevel < 195)
											exp /= 70;

										else
											exp /= 100;
									}

									//if (pMob[party].Extra.ClassMaster != ARCH && pMob[party].Extra.ClassMaster != MORTAL)
										//exp /= 50;

									exp = 6 * exp / 10;

									//if (exp > eMob)
									//	exp = eMob;

									if (pMob[a_iConn].ExpBonus > 0 && pMob[a_iConn].ExpBonus < 500)
										exp += exp * pMob[a_iConn].ExpBonus / 100;

									if (NewbieEventServer && pMob[party].MOB.CurrentScore.Level < 100 && pMob[party].Extra.ClassMaster != CELESTIAL && pMob[party].Extra.ClassMaster != CELESTIALCS && pMob[party].Extra.ClassMaster != SCELESTIAL)
										exp += exp / 4;

									//if (DOUBLEMODE)
									exp *= DOUBLEMODE;

									if (KefraLive == 0)
										exp /= 2;

									if (NewbieEventServer)
										exp += (exp * 15) / 100;
									else
										exp -= (exp * 15) / 100;

									//Log de Experiência diário
									if (when.tm_yday != pMob[party].Extra.DayLog.YearDay)
										pMob[party].Extra.DayLog.Exp = 0;

									pMob[party].Extra.DayLog.YearDay = when.tm_yday;
									pMob[party].Extra.DayLog.Exp += exp;

									if (pMob[party].Extra.Hold > 0 && (unsigned int)exp >= pMob[party].Extra.Hold)
									{
										int nhold = pMob[party].Extra.Hold - exp;

										if (nhold < 0)
											nhold = 0;

										exp -= pMob[party].Extra.Hold;
										pMob[party].Extra.Hold = nhold;
									}

									else if (pMob[party].Extra.Hold > 0 && (unsigned int)exp < pMob[party].Extra.Hold)
									{
										pMob[party].Extra.Hold -= exp;
										continue;
									}

									if (pMob[party].MOB.Exp + exp > g_pNextLevel[MAX_LEVEL + 1])
									{
										pMob[party].MOB.Exp = g_pNextLevel[MAX_LEVEL + 1];
									}
									else
									{
										pMob[party].MOB.Exp += exp;
									}

									//RankingUpdateExp
									STRUCT_RANKING rankInfo = STRUCT_RANKING(pMob[party].MOB.MobName, pMob[party].MOB.Exp, pMob[party].Extra.ClassMaster, pMob[party].MOB.CurrentScore.Level, pMob[party].MOB.Class, pMob[party].MOB.Guild, pMob[party].MOB.Clan);

									MSG_UpdateExpRanking expRankingPacket = MSG_UpdateExpRanking(party, rankInfo);
									DBServerSocket.SendOneMessage((char*)&expRankingPacket, sizeof(expRankingPacket));
								}
							}
#pragma endregion
#pragma region Pesadelo Mistico
							else if (party > 0 && party < MAX_USER && pMob[party].MOB.CurrentScore.Hp > 0 && (tx / 128) == 8 && (pMob[party].TargetX / 128) == 8
								&& (ty / 128) == 2 && (pMob[party].TargetY / 128) == 2)
							{
								isExp = GetExpApply(pMob[party].Extra, (int)pMob[target].MOB.Exp, pMob[party].MOB.CurrentScore.Level, pMob[target].MOB.CurrentScore.Level);

								int myLevel = pMob[party].MOB.CurrentScore.Level;

								//if (pMob[party].Extra.ClassMaster != MORTAL && pMob[party].Extra.ClassMaster != ARCH)
									//myLevel += MAX_LEVEL + 1;

								int exp = (UNK_1 + myLevel) * isExp / (UNK_1 + myLevel);
								if (exp > 0 && exp <= 10000000)
								{
									if (pMob[party].Extra.ClassMaster == MORTAL)
									{
										if (myLevel <= 200) // 110k
											exp /= 1;

										else if (myLevel <= 300) // 70k
											exp /= 1.03f;

										else if (myLevel <= 356) // 40k
											exp /= 1.50f;

										else if (myLevel <= 370) // 27k
											exp /= 2.15f;

										else if (myLevel <= 380) // 20k
											exp /= 2.78f;

										else if (myLevel <= 390) // 15k
											exp /= 3.70f;

										else if (myLevel <= 399) // 10k
											exp /= 5.20f;
									}


									if (pMob[party].Extra.ClassMaster == ARCH)
									{
										if (myLevel <= 200) // Exp Média 90k
											exp /= 0.72f;

										else if (myLevel <= 300)// Exp Média 70k
											exp /= 0.84f;

										else if (myLevel <= 356)// Exp Média 30k
											exp /= 1.40f;

										else if (myLevel <= 360)// Exp Média 8k
											exp /= 2.75f;

										else if (myLevel <= 370)// Exp Média 6k
											exp /= 3.60f;

										else if (myLevel <= 380) // Exp Média 2.5k
											exp /= 8;

										else if (myLevel <= 390)  // Exp Média 1.8k
											exp /= 15;

										else if (myLevel <= 400) // Exp Média 1k
											exp /= 25;
									}

									if (pMob[party].Extra.ClassMaster != MORTAL && pMob[party].Extra.ClassMaster != ARCH)
									{
										if (myLevel < 20)
											exp /= 10;

										else if (myLevel < 50)
											exp /= 20;

										else if (myLevel < 70)
											exp /= 40;

										else if (myLevel < 120)
											exp /= 50;

										else if (myLevel < 195)
											exp /= 70;

										else
											exp /= 100;
									}

									//if (pMob[party].Extra.ClassMaster != ARCH && pMob[party].Extra.ClassMaster != MORTAL)
										//exp /= 50;

									exp = 6 * exp / 10;

									if (pMob[a_iConn].ExpBonus > 0 && pMob[a_iConn].ExpBonus < 500)
										exp += exp * pMob[a_iConn].ExpBonus / 100;

									if (NewbieEventServer && pMob[party].MOB.CurrentScore.Level < 100 && pMob[party].Extra.ClassMaster != CELESTIAL && pMob[party].Extra.ClassMaster != CELESTIALCS && pMob[party].Extra.ClassMaster != SCELESTIAL)
										exp += exp / 4;

									//if (DOUBLEMODE)
									exp *= DOUBLEMODE;

									if (KefraLive == 0)
										exp /= 2;

									if (NewbieEventServer)
										exp += (exp * 15) / 100;
									else
										exp -= (exp * 15) / 100;

									//Log de Experiência diário
									if (when.tm_yday != pMob[party].Extra.DayLog.YearDay)
										pMob[party].Extra.DayLog.Exp = 0;

									pMob[party].Extra.DayLog.YearDay = when.tm_yday;
									pMob[party].Extra.DayLog.Exp += exp;

									if (pMob[party].Extra.Hold > 0 && (unsigned int)exp >= pMob[party].Extra.Hold)
									{
										int nhold = pMob[party].Extra.Hold - exp;

										if (nhold < 0)
											nhold = 0;

										exp -= pMob[party].Extra.Hold;
										pMob[party].Extra.Hold = nhold;
									}

									else if (pMob[party].Extra.Hold > 0 && (unsigned int)exp < pMob[party].Extra.Hold)
									{
										pMob[party].Extra.Hold -= exp;
										continue;
									}

									if (pMob[party].MOB.Exp + exp > g_pNextLevel[MAX_LEVEL + 1])
									{
										pMob[party].MOB.Exp = g_pNextLevel[MAX_LEVEL + 1];
									}
									else
									{
										pMob[party].MOB.Exp += exp;
									}

									// RankingUpdateExp
									STRUCT_RANKING rankInfo = STRUCT_RANKING(pMob[party].MOB.MobName, pMob[party].MOB.Exp, pMob[party].Extra.ClassMaster, pMob[party].MOB.CurrentScore.Level, pMob[party].MOB.Class, pMob[party].MOB.Guild, pMob[party].MOB.Clan);

									MSG_UpdateExpRanking expRankingPacket = MSG_UpdateExpRanking(party, rankInfo);
									DBServerSocket.SendOneMessage((char*)&expRankingPacket, sizeof(expRankingPacket));
								}
							}
#pragma endregion
#pragma region Pesadelo Normal
							else if (party > 0 && party < MAX_USER && pMob[party].MOB.CurrentScore.Hp > 0 && (tx / 128) == 10 && (pMob[party].TargetX / 128) == 10
								&& (ty / 128) == 2 && (pMob[party].TargetY / 128) == 2)
							{
								isExp = GetExpApply(pMob[party].Extra, (int)pMob[target].MOB.Exp, pMob[party].MOB.CurrentScore.Level, pMob[target].MOB.CurrentScore.Level);

								int myLevel = pMob[party].MOB.CurrentScore.Level;

								//if (pMob[party].Extra.ClassMaster != MORTAL && pMob[party].Extra.ClassMaster != ARCH)
								//	myLevel += MAX_LEVEL + 1;

								int exp = (UNK_1 + myLevel) * isExp / (UNK_1 + myLevel);
								if (exp > 0 && exp <= 10000000)
								{
									if (pMob[party].Extra.ClassMaster != MORTAL && pMob[party].Extra.ClassMaster != ARCH)
									{
										if (myLevel < 120)
											exp /= 10;

										else if (myLevel < 150)
											exp /= 20;

										else if (myLevel < 170)
											exp /= 40;

										else if (myLevel < 180)
											exp /= 80;

										else if (myLevel < 190)
											exp /= 160;

										else
											exp /= 320;
									}

									if (pMob[party].Extra.ClassMaster != MORTAL && pMob[party].Extra.ClassMaster != ARCH)
									{
										if (myLevel < 20)
											exp /= 10;

										else if (myLevel < 50)
											exp /= 20;

										else if (myLevel < 70)
											exp /= 40;

										else if (myLevel < 120)
											exp /= 50;

										else if (myLevel < 195)
											exp /= 70;

										else
											exp /= 100;
									}

									exp = 6 * exp / 10;

									if (pMob[a_iConn].ExpBonus > 0 && pMob[a_iConn].ExpBonus < 500)
										exp += exp * pMob[a_iConn].ExpBonus / 100;

									if (NewbieEventServer && pMob[party].MOB.CurrentScore.Level < 100 && pMob[party].Extra.ClassMaster != CELESTIAL && pMob[party].Extra.ClassMaster != CELESTIALCS && pMob[party].Extra.ClassMaster != SCELESTIAL)
										exp += exp / 4;

									//if (DOUBLEMODE)
									exp *= DOUBLEMODE;

									if (KefraLive == 0)
										exp /= 2;

									//if (pMob[party].Extra.ClassMaster != ARCH && pMob[party].Extra.ClassMaster != MORTAL)
										//exp /= 50;

									if (NewbieEventServer)
										exp += (exp * 15) / 100;
									else
										exp -= (exp * 15) / 100;

									// Log de Experiência diário
									if (when.tm_yday != pMob[party].Extra.DayLog.YearDay)
										pMob[party].Extra.DayLog.Exp = 0;

									pMob[party].Extra.DayLog.YearDay = when.tm_yday;
									pMob[party].Extra.DayLog.Exp += exp;

									if (pMob[party].Extra.Hold > 0 && (unsigned int)exp >= pMob[party].Extra.Hold)
									{
										int nhold = pMob[party].Extra.Hold - exp;

										if (nhold < 0)
											nhold = 0;

										exp -= pMob[party].Extra.Hold;
										pMob[party].Extra.Hold = nhold;
									}

									else if (pMob[party].Extra.Hold > 0 && (unsigned int)exp < pMob[party].Extra.Hold)
									{
										pMob[party].Extra.Hold -= exp;
										continue;
									}

									if (pMob[party].MOB.Exp + exp > g_pNextLevel[MAX_LEVEL + 1])
									{
										pMob[party].MOB.Exp = g_pNextLevel[MAX_LEVEL + 1];
									}
									else
									{
										pMob[party].MOB.Exp += exp;
									}
									// RankingUpdateExp
									STRUCT_RANKING rankInfo = STRUCT_RANKING(pMob[party].MOB.MobName, pMob[party].MOB.Exp, pMob[party].Extra.ClassMaster, pMob[party].MOB.CurrentScore.Level, pMob[party].MOB.Class, pMob[party].MOB.Guild, pMob[party].MOB.Clan);

									MSG_UpdateExpRanking expRankingPacket = MSG_UpdateExpRanking(party, rankInfo);
									DBServerSocket.SendOneMessage((char*)&expRankingPacket, sizeof(expRankingPacket));
								}
							}
#pragma endregion
#pragma region Pergaminho da Água Arcano
							else if (party > 0 && party < MAX_USER && pMob[party].MOB.CurrentScore.Hp > 0 && (tx / 128) == 10 && (pMob[party].TargetX / 128) == 10
								&& (ty / 128) == 27 && (pMob[party].TargetY / 128) == 27)
							{
								isExp = GetExpApply(pMob[party].Extra, (int)pMob[target].MOB.Exp, pMob[party].MOB.CurrentScore.Level, pMob[target].MOB.CurrentScore.Level);

								int myLevel = pMob[party].MOB.CurrentScore.Level;

								//if (pMob[party].Extra.ClassMaster != MORTAL && pMob[party].Extra.ClassMaster != ARCH)
									//myLevel += MAX_LEVEL + 1;

								int exp = 450 * isExp / (UNK_1 + myLevel);

								if (exp > 0 && exp <= 10000000)
								{

									if (pMob[party].Extra.ClassMaster == MORTAL)
									{
										if (myLevel <= 200) // Exp Média 90k
											exp /= 0.72f;

										else if (myLevel <= 300)// Exp Média 70k
											exp /= 0.84f;

										else if (myLevel <= 356)// Exp Média 30k
											exp /= 1.40f;

										else if (myLevel <= 360)// Exp Média 8k
											exp /= 2.75f;

										else if (myLevel <= 370)// Exp Média 6k
											exp /= 3.60f;

										else if (myLevel <= 380) // Exp Média 2.5k
											exp /= 8;

										else if (myLevel <= 390)  // Exp Média 1.8k
											exp /= 15;

										else if (myLevel <= 400) // Exp Média 1k
											exp /= 25;
									}

									if (pMob[party].Extra.ClassMaster == ARCH)
									{
										if (myLevel <= 200) // Exp Média 70k
											exp /= 1;

										else if (myLevel <= 300)// Exp Média 50k
											exp /= 0.05f;

										else if (myLevel <= 356)// Exp Média 30k
											exp /= 0.85f;

										else if (myLevel <= 360)// Exp Média 6k
											exp /= 4.0f;

										else if (myLevel <= 370)// Exp Média 3k
											exp /= 6.60f;

										else if (myLevel <= 380) // Exp Média 2k
											exp /= 9;

										else if (myLevel <= 390)  // Exp Média 1.5k
											exp /= 15;

										else if (myLevel <= 400) // Exp Média 900
											exp /= 22;
									}

									if (pMob[party].Extra.ClassMaster != MORTAL && pMob[party].Extra.ClassMaster != ARCH)
									{
										if (myLevel < 20)
											exp /= 10;

										else if (myLevel < 50)
											exp /= 20;

										else if (myLevel < 70)
											exp /= 40;

										else if (myLevel < 120)
											exp /= 50;

										else if (myLevel < 195)
											exp /= 70;

										else
											exp /= 100;
									}

									exp = 6 * exp / 10;

									if (exp > eMob)
										exp = eMob;

									if (pMob[a_iConn].ExpBonus > 0 && pMob[a_iConn].ExpBonus < 500)
										exp += exp * (pMob[a_iConn].ExpBonus + pMob[a_iConn].g_pFairyContent[0]) / 100;

									if (NewbieEventServer && pMob[party].MOB.CurrentScore.Level < 100 && pMob[party].Extra.ClassMaster != CELESTIAL && pMob[party].Extra.ClassMaster != CELESTIALCS && pMob[party].Extra.ClassMaster != SCELESTIAL)
										exp += exp / 4;

									//if (DOUBLEMODE)
									exp *= DOUBLEMODE;

									if (KefraLive == 0)
										exp /= 2;

									//if (pMob[party].Extra.ClassMaster != ARCH && pMob[party].Extra.ClassMaster != MORTAL)
										//exp /= 50;

									if (NewbieEventServer)
										exp += (exp * 15) / 100;
									else
										exp -= (exp * 15) / 100;

									//Log de Experiência diário
									if (when.tm_yday != pMob[party].Extra.DayLog.YearDay)
										pMob[party].Extra.DayLog.Exp = 0;

									pMob[party].Extra.DayLog.YearDay = when.tm_yday;
									pMob[party].Extra.DayLog.Exp += exp;

									if (pMob[party].Extra.Hold > 0 && (unsigned int)exp >= pMob[party].Extra.Hold)
									{
										int nhold = pMob[party].Extra.Hold - exp;

										if (nhold < 0)
											nhold = 0;

										exp -= pMob[party].Extra.Hold;
										pMob[party].Extra.Hold = nhold;
									}

									else if (pMob[party].Extra.Hold > 0 && (unsigned int)exp < pMob[party].Extra.Hold)
									{
										pMob[party].Extra.Hold -= exp;
										continue;
									}

									if (pMob[party].MOB.Exp + exp > g_pNextLevel[MAX_LEVEL + 1])
									{
										pMob[party].MOB.Exp = g_pNextLevel[MAX_LEVEL + 1];
									}
									else
									{
										pMob[party].MOB.Exp += exp;
									}

									//RankingUpdateExp
									STRUCT_RANKING rankInfo = STRUCT_RANKING(pMob[party].MOB.MobName, pMob[party].MOB.Exp, pMob[party].Extra.ClassMaster, pMob[party].MOB.CurrentScore.Level, pMob[party].MOB.Class, pMob[party].MOB.Guild, pMob[party].MOB.Clan);

									MSG_UpdateExpRanking expRankingPacket = MSG_UpdateExpRanking(party, rankInfo);
									DBServerSocket.SendOneMessage((char*)&expRankingPacket, sizeof(expRankingPacket));
								}
							}
#pragma endregion
#pragma region Pergaminho da Água Mistico
							else if (party > 0 && party < MAX_USER && pMob[party].MOB.CurrentScore.Hp > 0 && (tx / 128) == 9 && (pMob[party].TargetX / 128) == 9
								&& (ty / 128) == 28 && (pMob[party].TargetY / 128) == 28)
							{
								isExp = GetExpApply(pMob[party].Extra, (int)pMob[target].MOB.Exp, pMob[party].MOB.CurrentScore.Level, pMob[target].MOB.CurrentScore.Level);

								int myLevel = pMob[party].MOB.CurrentScore.Level;

								//if (pMob[party].Extra.ClassMaster != MORTAL && pMob[party].Extra.ClassMaster != ARCH)
								//	myLevel += MAX_LEVEL + 1;

								int exp = 450 * isExp / (UNK_1 + myLevel);

								if (exp > 0 && exp <= 10000000)
								{
									if (pMob[party].Extra.ClassMaster == MORTAL)
									{
										if (myLevel <= 200) // 100k
											exp /= 1;

										else if (myLevel <= 300) // 50k
											exp /= 1.08f;

										else if (myLevel <= 356) // 30k
											exp /= 1.30f;

										else if (myLevel <= 370) // 20k
											exp /= 1.80f;

										else if (myLevel <= 380) // 15k
											exp /= 2.20f;

										else if (myLevel <= 390) // 12k
											exp /= 2.60f;

										else if (myLevel <= 399) // 6k
											exp /= 4.70f;
									}


									if (pMob[party].Extra.ClassMaster == ARCH)
									{
										if (myLevel <= 200) // Exp Média 90k
											exp /= 0.72f;

										else if (myLevel <= 300)// Exp Média 70k
											exp /= 0.84f;

										else if (myLevel <= 356)// Exp Média 30k
											exp /= 1.40f;

										else if (myLevel <= 360)// Exp Média 8k
											exp /= 2.75f;

										else if (myLevel <= 370)// Exp Média 6k
											exp /= 3.60f;

										else if (myLevel <= 380) // Exp Média 2.5k
											exp /= 8;

										else if (myLevel <= 390)  // Exp Média 1.8k
											exp /= 15;

										else if (myLevel <= 400) // Exp Média 1k
											exp /= 25;
									}

									if (pMob[party].Extra.ClassMaster != MORTAL && pMob[party].Extra.ClassMaster != ARCH)
									{
										if (myLevel < 20)
											exp /= 10;

										else if (myLevel < 50)
											exp /= 20;

										else if (myLevel < 70)
											exp /= 40;

										else if (myLevel < 120)
											exp /= 50;

										else if (myLevel < 195)
											exp /= 70;

										else
											exp /= 100;
									}

									exp = 6 * exp / 10;

									if (exp > eMob)
										exp = eMob;

									if (pMob[a_iConn].ExpBonus > 0 && pMob[a_iConn].ExpBonus < 500)
										exp += exp * (pMob[a_iConn].ExpBonus + pMob[a_iConn].g_pFairyContent[0]) / 100;

									if (NewbieEventServer && pMob[party].MOB.CurrentScore.Level < 100 && pMob[party].Extra.ClassMaster != CELESTIAL && pMob[party].Extra.ClassMaster != CELESTIALCS && pMob[party].Extra.ClassMaster != SCELESTIAL)
										exp += exp / 4;

									//if (DOUBLEMODE)
									exp *= DOUBLEMODE;

									if (KefraLive == 0)
										exp /= 2;

									//if (pMob[party].Extra.ClassMaster != ARCH && pMob[party].Extra.ClassMaster != MORTAL)
									//	exp /= 50;

									if (NewbieEventServer)
										exp += (exp * 15) / 100;
									else
										exp -= (exp * 15) / 100;

									//Log de Experiência diário
									if (when.tm_yday != pMob[party].Extra.DayLog.YearDay)
										pMob[party].Extra.DayLog.Exp = 0;

									pMob[party].Extra.DayLog.YearDay = when.tm_yday;
									pMob[party].Extra.DayLog.Exp += exp;

									if (pMob[party].Extra.Hold > 0 && (unsigned int)exp >= pMob[party].Extra.Hold)
									{
										int nhold = pMob[party].Extra.Hold - exp;

										if (nhold < 0)
											nhold = 0;

										exp -= pMob[party].Extra.Hold;
										pMob[party].Extra.Hold = nhold;
									}

									else if (pMob[party].Extra.Hold > 0 && (unsigned int)exp < pMob[party].Extra.Hold)
									{
										pMob[party].Extra.Hold -= exp;
										continue;
									}

									if (pMob[party].MOB.Exp + exp > g_pNextLevel[MAX_LEVEL + 1])
									{
										pMob[party].MOB.Exp = g_pNextLevel[MAX_LEVEL + 1];
									}
									else
									{
										pMob[party].MOB.Exp += exp;
									}

									//RankingUpdateExp
									STRUCT_RANKING rankInfo = STRUCT_RANKING(pMob[party].MOB.MobName, pMob[party].MOB.Exp, pMob[party].Extra.ClassMaster, pMob[party].MOB.CurrentScore.Level, pMob[party].MOB.Class, pMob[party].MOB.Guild, pMob[party].MOB.Clan);

									MSG_UpdateExpRanking expRankingPacket = MSG_UpdateExpRanking(party, rankInfo);
									DBServerSocket.SendOneMessage((char*)&expRankingPacket, sizeof(expRankingPacket));
								}
							}
#pragma endregion
#pragma region Pergaminho da Água Normal
							else if (party > 0 && party < MAX_USER && pMob[party].MOB.CurrentScore.Hp > 0 && (tx / 128) == 8 && (pMob[party].TargetX / 128) == 8
								&& (ty / 128) == 27 && (pMob[party].TargetY / 128) == 27)
							{
								isExp = GetExpApply(pMob[party].Extra, (int)pMob[target].MOB.Exp, pMob[party].MOB.CurrentScore.Level, pMob[target].MOB.CurrentScore.Level);

								int myLevel = pMob[party].MOB.CurrentScore.Level;

								//if (pMob[party].Extra.ClassMaster != MORTAL && pMob[party].Extra.ClassMaster != ARCH)
								//	myLevel += MAX_LEVEL + 1;

								int exp = 450 * isExp / (UNK_1 + myLevel);

								if (exp > 0 && exp <= 10000000)
								{
									if (pMob[party].Extra.ClassMaster == MORTAL)
									{
										if (myLevel <= 200) // 70k
											exp /= 1.28;

										else if (myLevel <= 300) // 40k
											exp /= 1.03f;

										else if (myLevel <= 356) // 20k
											exp /= 1.45f;

										else if (myLevel <= 370) // 15k
											exp /= 1.80f;

										else if (myLevel <= 380) // 10k
											exp /= 2.45f;

										else if (myLevel <= 390) // 6k
											exp /= 3.70f;

										else if (myLevel <= 399) // 3k
											exp /= 6.80f;
									}

									if (pMob[party].Extra.ClassMaster == ARCH)
									{
										if (myLevel <= 200) // Exp Média 90k
											exp /= 0.72f;

										else if (myLevel <= 300)// Exp Média 70k
											exp /= 0.84f;

										else if (myLevel <= 356)// Exp Média 30k
											exp /= 1.40f;

										else if (myLevel <= 360)// Exp Média 8k
											exp /= 2.75f;

										else if (myLevel <= 370)// Exp Média 6k
											exp /= 3.60f;

										else if (myLevel <= 380) // Exp Média 2.5k
											exp /= 8;

										else if (myLevel <= 390)  // Exp Média 1.8k
											exp /= 15;

										else if (myLevel <= 400) // Exp Média 1k
											exp /= 25;
									}

									if (pMob[party].Extra.ClassMaster != MORTAL && pMob[party].Extra.ClassMaster != ARCH)
									{
										if (myLevel < 20)
											exp /= 10;

										else if (myLevel < 50)
											exp /= 20;

										else if (myLevel < 70)
											exp /= 40;

										else if (myLevel < 120)
											exp /= 50;

										else if (myLevel < 195)
											exp /= 70;

										else
											exp /= 100;
									}

									exp = 6 * exp / 10;

									if (exp > eMob)
										exp = eMob;

									if (pMob[a_iConn].ExpBonus > 0 && pMob[a_iConn].ExpBonus < 500)
										exp += exp * (pMob[a_iConn].ExpBonus + pMob[a_iConn].g_pFairyContent[0]) / 100;

									if (NewbieEventServer && pMob[party].MOB.CurrentScore.Level < 100 && pMob[party].Extra.ClassMaster != CELESTIAL && pMob[party].Extra.ClassMaster != CELESTIALCS && pMob[party].Extra.ClassMaster != SCELESTIAL)
										exp += exp / 4;

									//if (DOUBLEMODE)
									exp *= DOUBLEMODE;

									if (KefraLive == 0)
										exp /= 2;

									//if (pMob[party].Extra.ClassMaster != ARCH && pMob[party].Extra.ClassMaster != MORTAL)
									//	exp /= 50;

									if (NewbieEventServer)
										exp += (exp * 15) / 100;
									else
										exp -= (exp * 15) / 100;

									//Log de Experiência diário
									if (when.tm_yday != pMob[party].Extra.DayLog.YearDay)
										pMob[party].Extra.DayLog.Exp = 0;

									pMob[party].Extra.DayLog.YearDay = when.tm_yday;
									pMob[party].Extra.DayLog.Exp += exp;

									if (pMob[party].Extra.Hold > 0 && (unsigned int)exp >= pMob[party].Extra.Hold)
									{
										int nhold = pMob[party].Extra.Hold - exp;

										if (nhold < 0)
											nhold = 0;

										exp -= pMob[party].Extra.Hold;
										pMob[party].Extra.Hold = nhold;
									}

									else if (pMob[party].Extra.Hold > 0 && (unsigned int)exp < pMob[party].Extra.Hold)
									{
										pMob[party].Extra.Hold -= exp;
										continue;
									}

									if (pMob[party].MOB.Exp + exp > g_pNextLevel[MAX_LEVEL + 1])
									{
										pMob[party].MOB.Exp = g_pNextLevel[MAX_LEVEL + 1];
									}
									else
									{
										pMob[party].MOB.Exp += exp;
									}

									//RankingUpdateExp
									STRUCT_RANKING rankInfo = STRUCT_RANKING(pMob[party].MOB.MobName, pMob[party].MOB.Exp, pMob[party].Extra.ClassMaster, pMob[party].MOB.CurrentScore.Level, pMob[party].MOB.Class, pMob[party].MOB.Guild, pMob[party].MOB.Clan);

									MSG_UpdateExpRanking expRankingPacket = MSG_UpdateExpRanking(party, rankInfo);
									DBServerSocket.SendOneMessage((char*)&expRankingPacket, sizeof(expRankingPacket));
								}
							}
#pragma endregion

							else if (party > 0 && party < MAX_USER && pMob[party].MOB.CurrentScore.Hp > 0 && tx >= pMob[party].TargetX - HALFGRIDX
								&& tx <= pMob[party].TargetX + HALFGRIDX && ty >= pMob[party].TargetY - HALFGRIDY && ty <= pMob[party].TargetY + HALFGRIDY)
							{

								isExp = GetExpApply(pMob[party].Extra, (int)pMob[target].MOB.Exp, pMob[party].MOB.CurrentScore.Level, pMob[target].MOB.CurrentScore.Level);

								int myLevel = pMob[party].MOB.CurrentScore.Level;

								//if (pMob[party].Extra.ClassMaster != MORTAL && pMob[party].Extra.ClassMaster != ARCH)
								//	myLevel += MAX_LEVEL + 1;

								int exp = 450 * isExp / (UNK_1 + myLevel);

								if (exp > 0 && exp <= 10000000)
								{
									if (pMob[party].Extra.ClassMaster == MORTAL)
									{
										if (myLevel <= 200) //50k
											exp /= 1;

										else if (myLevel <= 300) //25k
											exp /= 1.07f;

										else if (myLevel <= 356) //15k
											exp /= 1.25f;

										else if (myLevel <= 370) //10k
											exp /= 1.70;

										else if (myLevel <= 380) //8k
											exp /= 2.10f;

										else if (myLevel <= 390) //6k
											exp /= 2.60;

										else if (myLevel <= 399) //3k
											exp /= 4;
									}


									if (pMob[party].Extra.ClassMaster == ARCH)
									{
										if (myLevel <= 200) // Exp Média 90k
											exp /= 0.72f;

										else if (myLevel <= 300)// Exp Média 70k
											exp /= 0.84f;

										else if (myLevel <= 356)// Exp Média 30k
											exp /= 1.40f;

										else if (myLevel <= 360)// Exp Média 8k
											exp /= 2.75f;

										else if (myLevel <= 370)// Exp Média 6k
											exp /= 3.60f;

										else if (myLevel <= 380) // Exp Média 2.5k
											exp /= 8;

										else if (myLevel <= 390)  // Exp Média 1.8k
											exp /= 15;

										else if (myLevel <= 400) // Exp Média 1k
											exp /= 25;
									}

									//if (pMob[party].Extra.ClassMaster != ARCH && pMob[party].Extra.ClassMaster != MORTAL)
										//exp /= 50;

									if (pMob[party].Extra.ClassMaster != MORTAL && pMob[party].Extra.ClassMaster != ARCH)
									{
										if (myLevel < 20)
											exp /= 10;

										else if (myLevel < 50)
											exp /= 20;

										else if (myLevel < 70)
											exp /= 40;

										else if (myLevel < 120)
											exp /= 50;

										else if (myLevel < 195)
											exp /= 70;

										else
											exp /= 100;
									}

									exp = 6 * exp / 10;

									if (exp > eMob)
										exp = eMob;

									if (pMob[a_iConn].ExpBonus > 0 && pMob[a_iConn].ExpBonus < 500)
										exp += exp * (pMob[a_iConn].ExpBonus + pMob[a_iConn].g_pFairyContent[0]) / 100;

									if (g_pRvrWar.Bonus != 0)
									{
										if (g_pRvrWar.Bonus == pMob[party].MOB.Clan)
											exp += (exp * 5) / 100;
									}

									if (NewbieEventServer && pMob[party].MOB.CurrentScore.Level < 100 && pMob[party].Extra.ClassMaster != CELESTIAL && pMob[party].Extra.ClassMaster != CELESTIALCS && pMob[party].Extra.ClassMaster != SCELESTIAL)
										exp += exp / 4;

									//if (DOUBLEMODE)
									exp *= DOUBLEMODE;

									if (KefraLive == 0)
										exp /= 2;


									if (NewbieEventServer)
										exp += (exp * 15) / 100;
									else
										exp -= (exp * 15) / 100;

									//Log de Experiência diário
									if (when.tm_yday != pMob[party].Extra.DayLog.YearDay)
										pMob[party].Extra.DayLog.Exp = 0;

									pMob[party].Extra.DayLog.YearDay = when.tm_yday;
									pMob[party].Extra.DayLog.Exp += exp;

									if (pMob[party].Extra.Hold > 0 && (unsigned int)exp >= pMob[party].Extra.Hold)
									{
										int nhold = pMob[party].Extra.Hold - exp;

										if (nhold < 0)
											nhold = 0;

										exp -= pMob[party].Extra.Hold;
										pMob[party].Extra.Hold = nhold;
									}

									else if (pMob[party].Extra.Hold > 0 && (unsigned int)exp < pMob[party].Extra.Hold)
									{
										pMob[party].Extra.Hold -= exp;
										continue;
									}

									if (pMob[party].MOB.Exp + exp > g_pNextLevel[MAX_LEVEL + 1])
									{
										pMob[party].MOB.Exp = g_pNextLevel[MAX_LEVEL + 1];
									}
									else
									{
										pMob[party].MOB.Exp += exp;
									}

									//RankingUpdateExp
									STRUCT_RANKING rankInfo = STRUCT_RANKING(pMob[party].MOB.MobName, pMob[party].MOB.Exp, pMob[party].Extra.ClassMaster, pMob[party].MOB.CurrentScore.Level, pMob[party].MOB.Class, pMob[party].MOB.Guild, pMob[party].MOB.Clan);

									MSG_UpdateExpRanking expRankingPacket = MSG_UpdateExpRanking(party, rankInfo);
									DBServerSocket.SendOneMessage((char*)&expRankingPacket, sizeof(expRankingPacket));
								}
							}
						}
#pragma endregion
#pragma region Targets Monstros
						int GenerateIndex = pMob[target].GenerateIndex;
						//srand(time(NULL));
						int DieSay = rand() % 4;

						if (GenerateIndex >= 0 && mNPCGen.pList[GenerateIndex].DieAction[DieSay][0] && pMob[target].Leader == 0)
							SendChat(target, mNPCGen.pList[GenerateIndex].DieAction[DieSay]);

						GridMulticast(pMob[target].TargetX, pMob[target].TargetY, (MSG_STANDARD*)&sm, 0);

						if (pMob[a_iConn].MOB.Clan && pMob[a_iConn].MOB.Clan != 4 && pMob[a_iConn].MOB.Clan != 7 && pMob[a_iConn].MOB.Clan != 8)
							DeleteMob(target, 1);

						else
						{
							int AlvoX = PosX;
							if (!PosX)
								AlvoX = pMob[target].TargetX;

							int AlvoY = PosY;
							if (!PosY)
								AlvoY = pMob[target].TargetY;

#pragma region Kefra
							if (pMob[target].GenerateIndex == KEFRA_BOSS)
							{
								if (pMob[a_iConn].MOB.Guild)
								{
									int Group = ServerGroup;
									int Server = pMob[a_iConn].MOB.Guild / MAX_GUILD;
									int usGuild = pMob[a_iConn].MOB.Guild;

									char guildname[256];

									BASE_GetGuildName(Group, usGuild, guildname);

									KefraLive = usGuild;

									MSG_GuildInfo sm_gi;
									memset(&sm_gi, 0, sizeof(MSG_GuildInfo));

									sm_gi.Type = _MSG_GuildInfo;
									sm_gi.Size = sizeof(MSG_GuildInfo);
									sm_gi.ID = a_iConn;

									sm_gi.Guild = usGuild;
									GuildInfo[usGuild].Fame += 300;

									sm_gi.GuildInfo = GuildInfo[usGuild];

									DBServerSocket.SendOneMessage((char*)&sm_gi, sizeof(MSG_GuildInfo));

									sprintf(temp, g_pMessageStringTable[_SN_End_Khepra], guildname);
									SendNotice(temp);

									DrawConfig(TRUE);
								}

								else
								{
									KefraLive = 1;
									sprintf(temp, g_pMessageStringTable[_SN_End_Khepra], "Eternal");
									SendNotice(temp);

									DrawConfig(TRUE);
								}
								//srand(time(NULL));
								int itemrand = rand() % 60;

								STRUCT_ITEM* KefraItem = &pMob[target].MOB.Carry[itemrand];
								//drop jogador que matou kefra
								PutItem(a_iConn, KefraItem);
								//drop guild que matou o kefra apenas 10 membros
								KefraDrop(a_iConn);
								sprintf(temp, "etc,kefra killed");
								Log(temp, pMob[a_iConn].MOB.MobName, 0);
							}
#pragma endregion
#pragma region Portões de Noatum
							if (1 > 0)
							{
								int GenerateID = pMob[target].GenerateIndex;
								if (pMob[target].MOB.Equip[0].sIndex == 220 && CastleState)
								{
									if (pMob[target].TargetX < 0 || pMob[target].TargetX >= MAX_GRIDX || pMob[target].TargetY < 0 || pMob[target].TargetY >= MAX_GRIDY)
									{
										Log("err,no castle gate to open pos", "-system", 0);
										return;
									}

									int ItemID = pItemGrid[pMob[target].TargetY][pMob[target].TargetX];
									if (ItemID >= 0 && ItemID < MAX_ITEM && pItem[ItemID].Mode)
									{
										int heigth = 0;
										int isUpdate = UpdateItem(ItemID, 1, &heigth);
										if (isUpdate)
										{
											MSG_UpdateItem UpdateIt;

											UpdateIt.ID = ESCENE_FIELD;
											UpdateIt.Type = _MSG_UpdateItem;

											UpdateIt.ItemID = ItemID + 10000;

											UpdateIt.Size = sizeof(MSG_UpdateItem);

											//UpdateIt.Height = heigth;

											UpdateIt.State = pItem[ItemID].State;

											GridMulticast(pItem[ItemID].PosX, pItem[ItemID].PosY, (MSG_STANDARD*)&UpdateIt, 0);

											pItem[ItemID].Delay = 0;
										}
									}

									else
										Log("err,no castle gato to open", "-system", 0);
								}
								else
								{
#pragma endregion
#pragma region Pergaminho da Água (M)
									if (GenerateID >= WATER_M_INITIAL && GenerateID <= WATER_M_INITIAL + 7)
									{
										int CurrentNumMob = mNPCGen.pList[GenerateID].CurrentNumMob;

										if (CurrentNumMob == 1)
										{
											int Sala = GenerateID - WATER_M_INITIAL;

											if (WaterClear1[1][Sala] > 15)
												WaterClear1[1][Sala] = 15;

											int partyleader = pMob[a_iConn].Leader;

											if (partyleader <= 0)
												partyleader = a_iConn;

											int slot_free = -1;

											STRUCT_ITEM Perga;
											memset(&Perga, 0, sizeof(STRUCT_ITEM));

											Perga.sIndex = 778 + Sala;

											if (partyleader > 0 && partyleader < MAX_USER)
												PutItem(partyleader, &Perga);

											SendClientSignalParm(partyleader, ESCENE_FIELD, _MSG_StartTime, WaterClear1[1][Sala] * 2);

											for (int i = 0; i < MAX_PARTY; i++)
											{
												int partymember = pMob[partyleader].PartyList[i];

												if (partymember >= MAX_USER)
													continue;

												if (pUser[partymember].Mode != USER_PLAY)
													continue;

												SendClientSignalParm(partymember, ESCENE_FIELD, _MSG_StartTime, WaterClear1[1][Sala] * 2);


											}
									/*		pMob[partyleader].MOB.SalaClear = TRUE;
											pMob[partyleader].MOB.macroOn = FALSE;*/
										}

									}


									else if (GenerateID >= WATER_M_INITIAL + 8 && GenerateID <= WATER_M_INITIAL + 11)
									{
										int CurrentNumMob = mNPCGen.pList[GenerateID].CurrentNumMob;

										if (CurrentNumMob == 1)
										{
											int Sala = 9;

											if (WaterClear1[1][Sala] > 5)
												WaterClear1[1][Sala] = 5;

											int partyleader = pMob[a_iConn].Leader;

											if (partyleader <= 0)
												partyleader = a_iConn;

											SendClientSignalParm(partyleader, ESCENE_FIELD, _MSG_StartTime, WaterClear1[1][Sala] * 2);

											for (int i = 0; i < MAX_PARTY; i++)
											{
												int partymember = pMob[partyleader].PartyList[i];

												if (partymember >= MAX_USER)
													continue;

												if (pUser[partymember].Mode != USER_PLAY)
													continue;

												SendClientSignalParm(partymember, ESCENE_FIELD, _MSG_StartTime, WaterClear1[1][Sala] * 2);

											}
								/*			pMob[partyleader].MOB.SalaClear = TRUE;
											pMob[partyleader].MOB.macroOn = FALSE;*/
										}
									}
#pragma endregion
#pragma region Pergaminho da Água (N)
									else if (GenerateID >= WATER_N_INITIAL && GenerateID <= WATER_N_INITIAL + 7)
									{
										int CurrentNumMob = mNPCGen.pList[GenerateID].CurrentNumMob;

										if (CurrentNumMob == 1)
										{
											int Sala = GenerateID - WATER_N_INITIAL;

											if (WaterClear1[0][Sala] > 15)
												WaterClear1[0][Sala] = 15;

											int partyleader = pMob[a_iConn].Leader;

											if (partyleader <= 0)
												partyleader = a_iConn;

											int slot_free = -1;

											STRUCT_ITEM Perga;
											memset(&Perga, 0, sizeof(STRUCT_ITEM));

											Perga.sIndex = 3174 + Sala;

											if (partyleader > 0 && partyleader < MAX_USER)
												PutItem(partyleader, &Perga);

											SendClientSignalParm(partyleader, ESCENE_FIELD, _MSG_StartTime, WaterClear1[0][Sala] * 2);

											for (int i = 0; i < MAX_PARTY; i++)
											{
												int partymember = pMob[partyleader].PartyList[i];

												if (partymember >= MAX_USER)
													continue;

												if (pUser[partymember].Mode != USER_PLAY)
													continue;

												SendClientSignalParm(partymember, ESCENE_FIELD, _MSG_StartTime, WaterClear1[0][Sala] * 2);
											}
				/*							pMob[partyleader].MOB.SalaClear = TRUE;
											pMob[partyleader].MOB.macroOn = FALSE;*/
										}
									}

									else if (GenerateID >= WATER_N_INITIAL + 8 && GenerateID <= WATER_N_INITIAL + 11)
									{
										int CurrentNumMob = mNPCGen.pList[GenerateID].CurrentNumMob;

										if (CurrentNumMob == 1)
										{
											int Sala = 9;

											if (WaterClear1[0][Sala] > 5)
												WaterClear1[0][Sala] = 5;

											int partyleader = pMob[a_iConn].Leader;

											if (partyleader <= 0)
												partyleader = a_iConn;

											SendClientSignalParm(partyleader, ESCENE_FIELD, _MSG_StartTime, WaterClear1[0][Sala] * 2);

											for (int i = 0; i < MAX_PARTY; i++)
											{
												int partymember = pMob[partyleader].PartyList[i];

												if (partymember >= MAX_USER)
													continue;

												if (pUser[partymember].Mode != USER_PLAY)
													continue;

												SendClientSignalParm(partymember, ESCENE_FIELD, _MSG_StartTime, WaterClear1[0][Sala] * 2);
											}
											//pMob[partyleader].MOB.SalaClear = TRUE;
											//pMob[partyleader].MOB.macroOn = FALSE;
										}
									}
#pragma endregion
#pragma region Pergaminho da Água (A)
									else if (GenerateID >= WATER_A_INITIAL && GenerateID <= WATER_A_INITIAL + 7)
									{
										int CurrentNumMob = mNPCGen.pList[GenerateID].CurrentNumMob;

										if (CurrentNumMob == 1)
										{
											int Sala = GenerateID - WATER_A_INITIAL;

											if (WaterClear1[2][Sala] > 15)
												WaterClear1[2][Sala] = 15;

											int partyleader = pMob[a_iConn].Leader;

											if (partyleader <= 0)
												partyleader = a_iConn;

											int slot_free = -1;

											STRUCT_ITEM Perga;
											memset(&Perga, 0, sizeof(STRUCT_ITEM));

											Perga.sIndex = 3183 + Sala;

											if (partyleader > 0 && partyleader < MAX_USER)
												PutItem(partyleader, &Perga);

											SendClientSignalParm(partyleader, ESCENE_FIELD, _MSG_StartTime, WaterClear1[2][Sala] * 2);

											for (int i = 0; i < MAX_PARTY; i++)
											{
												int partymember = pMob[partyleader].PartyList[i];

												if (partymember >= MAX_USER)
													continue;

												if (pUser[partymember].Mode != USER_PLAY)
													continue;

												SendClientSignalParm(partymember, ESCENE_FIELD, _MSG_StartTime, WaterClear1[2][Sala] * 2);
											}
										/*	pMob[partyleader].MOB.SalaClear = TRUE;
											pMob[partyleader].MOB.macroOn = FALSE;*/
										}
									}

									else if (GenerateID >= WATER_A_INITIAL + 8 && GenerateID <= WATER_A_INITIAL + 11)
									{
										int CurrentNumMob = mNPCGen.pList[GenerateID].CurrentNumMob;

										if (CurrentNumMob == 1)
										{
											int Sala = 9;

											if (WaterClear1[2][Sala] > 5)
												WaterClear1[2][Sala] = 5;

											int partyleader = pMob[a_iConn].Leader;

											if (partyleader <= 0)
												partyleader = a_iConn;

											SendClientSignalParm(partyleader, ESCENE_FIELD, _MSG_StartTime, WaterClear1[2][Sala] * 2);

											for (int i = 0; i < MAX_PARTY; i++)
											{
												int partymember = pMob[partyleader].PartyList[i];

												if (partymember >= MAX_USER)
													continue;

												if (pUser[partymember].Mode != USER_PLAY)
													continue;

												SendClientSignalParm(partymember, ESCENE_FIELD, _MSG_StartTime, WaterClear1[2][Sala] * 2);
											}
										/*	pMob[partyleader].MOB.SalaClear = TRUE;
											pMob[partyleader].MOB.macroOn = FALSE;*/
										}
									}
#pragma endregion
#pragma region Pesadelos
									else if (GenerateIndex >= NIGHTMARE_M_INITIAL && GenerateIndex <= NIGHTMARE_M_END)
										GenerateMob(GenerateIndex, 0, 0);//Pesa M

									else if (GenerateIndex >= NIGHTMARE_N_INITIAL && GenerateIndex <= NIGHTMARE_N_END)
										GenerateMob(GenerateIndex, 0, 0);//Pesa N

									else if (GenerateIndex >= NIGHTMARE_A_INITIAL && GenerateIndex <= NIGHTMARE_A_END)
										GenerateMob(GenerateIndex, 0, 0);//Pesa A
#pragma endregion

#pragma region Sombra Negra
									//Boss
									else if (GenerateID == bSombraNegra.Boss.ID)
									{
										sombraNegraKilled(a_iConn);
									}
									//Guardiao
									else if (GenerateID == bSombraNegra.Guardian.ID)
									{
										guardianKilled();
									}
#pragma endregion

#pragma region Boss Camp
									for (size_t i = 0; i < MAX_BOSS_CAMP; i++)
									{
										//Boss
										if (GenerateID == bossCamp[i].Boss.ID)
										{
											BossCampKilled(a_iConn, i);
										}
										//Guardiao
										else if (GenerateID == bossCamp[i].Guardian.ID)
										{
											guardianBossCampKilled(i);
										}

									}

#pragma endregion

#pragma region Carta de Duelo (M)							
									if (GenerateID >= SECRET_ROOM_M_SALA1_MOB_1 && GenerateID <= SECRET_ROOM_M_SALA1_MOB_2)
									{
										int CurrentNumMob = mNPCGen.pList[SECRET_ROOM_M_SALA1_MOB_1].CurrentNumMob;
										CurrentNumMob += mNPCGen.pList[SECRET_ROOM_M_SALA1_MOB_2].CurrentNumMob;

										if (CurrentNumMob == 1)
										{
											CartaTime = 60;

											ClearAreaTeleport(778, 3652, 832, 3698, CartaPos[1][0], CartaPos[1][1]);

											CartaSala++;

											MSG_STANDARDPARM sm;

											sm.Type = _MSG_StartTime;
											sm.ID = ESCENE_FIELD;
											sm.Size = sizeof(MSG_STANDARDPARM);
											sm.Parm = CartaTime * 2;

											MapaMulticast(6, 28, (MSG_STANDARD*)&sm, 0);
										}
									}

									else if (GenerateID >= SECRET_ROOM_M_SALA2_MOB_1 && GenerateID <= SECRET_ROOM_M_SALA2_MOB_2)
									{
										int CurrentNumMob = mNPCGen.pList[SECRET_ROOM_M_SALA2_MOB_1].CurrentNumMob;
										CurrentNumMob += mNPCGen.pList[SECRET_ROOM_M_SALA2_MOB_2].CurrentNumMob;

										if (CurrentNumMob == 1)
										{
											CartaTime = 60;

											ClearAreaTeleport(836, 3652, 890, 3698, CartaPos[2][0], CartaPos[2][1]);

											CartaSala++;

											MSG_STANDARDPARM sm;

											sm.Type = _MSG_StartTime;
											sm.ID = ESCENE_FIELD;
											sm.Size = sizeof(MSG_STANDARDPARM);
											sm.Parm = CartaTime * 2;

											MapaMulticast(6, 28, (MSG_STANDARD*)&sm, 0);
										}
									}

									else if (GenerateID >= SECRET_ROOM_M_SALA3_MOB_1 && GenerateID <= SECRET_ROOM_M_SALA3_MOB_2)
									{
										int CurrentNumMob = mNPCGen.pList[SECRET_ROOM_M_SALA3_MOB_1].CurrentNumMob;
										CurrentNumMob += mNPCGen.pList[SECRET_ROOM_M_SALA3_MOB_2].CurrentNumMob;

										if (CurrentNumMob == 1)
										{
											CartaTime = 60;

											ClearAreaTeleport(834, 3595, 889, 3645, CartaPos[3][0], CartaPos[3][1]);

											CartaSala++;

											MSG_STANDARDPARM sm;

											sm.Type = _MSG_StartTime;
											sm.ID = ESCENE_FIELD;
											sm.Size = sizeof(MSG_STANDARDPARM);
											sm.Parm = CartaTime * 2;

											MapaMulticast(6, 28, (MSG_STANDARD*)&sm, 0);
										}
									}

									else if (GenerateID >= SECRET_ROOM_M_SALA4_MOB_1 && GenerateID <= SECRET_ROOM_M_SALA4_MOB_4)
									{
										int CurrentNumMob = mNPCGen.pList[SECRET_ROOM_M_SALA4_MOB_1].CurrentNumMob;
										CurrentNumMob += mNPCGen.pList[SECRET_ROOM_M_SALA4_MOB_2].CurrentNumMob;
										CurrentNumMob += mNPCGen.pList[SECRET_ROOM_M_SALA4_MOB_3].CurrentNumMob;
										CurrentNumMob += mNPCGen.pList[SECRET_ROOM_M_SALA4_MOB_4].CurrentNumMob;

										if (CurrentNumMob == 1)
										{
											//ClearArea(776, 3595, 834, 3648);
											CartaTime = 3;
											CartaSala = 4;
										}
									}
#pragma endregion
#pragma region Carta de Duelo (N)
									else if (GenerateID >= SECRET_ROOM_N_SALA1_MOB_1 && GenerateID <= SECRET_ROOM_N_SALA1_MOB_2)
									{
										int CurrentNumMob = mNPCGen.pList[SECRET_ROOM_N_SALA1_MOB_1].CurrentNumMob;
										CurrentNumMob += mNPCGen.pList[SECRET_ROOM_N_SALA1_MOB_2].CurrentNumMob;

										if (CurrentNumMob == 1)
										{
											CartaTime = 60;

											ClearAreaTeleport(778, 3652, 832, 3698, CartaPos[1][0], CartaPos[1][1]);

											CartaSala++;

											MSG_STANDARDPARM sm;

											sm.Type = _MSG_StartTime;
											sm.ID = ESCENE_FIELD;
											sm.Size = sizeof(MSG_STANDARDPARM);
											sm.Parm = CartaTime * 2;

											MapaMulticast(6, 28, (MSG_STANDARD*)&sm, 0);
										}
									}

									else if (GenerateID >= SECRET_ROOM_N_SALA2_MOB_1 && GenerateID <= SECRET_ROOM_N_SALA2_MOB_2)
									{
										int CurrentNumMob = mNPCGen.pList[SECRET_ROOM_N_SALA2_MOB_1].CurrentNumMob;
										CurrentNumMob += mNPCGen.pList[SECRET_ROOM_N_SALA2_MOB_2].CurrentNumMob;

										if (CurrentNumMob == 1)
										{
											CartaTime = 60;

											ClearAreaTeleport(836, 3652, 890, 3698, CartaPos[2][0], CartaPos[2][1]);

											CartaSala++;

											MSG_STANDARDPARM sm;

											sm.Type = _MSG_StartTime;
											sm.ID = ESCENE_FIELD;
											sm.Size = sizeof(MSG_STANDARDPARM);
											sm.Parm = CartaTime * 2;

											MapaMulticast(6, 28, (MSG_STANDARD*)&sm, 0);
										}
									}

									else if (GenerateID >= SECRET_ROOM_N_SALA3_MOB_1 && GenerateID <= SECRET_ROOM_N_SALA3_MOB_2)
									{
										int CurrentNumMob = mNPCGen.pList[SECRET_ROOM_N_SALA3_MOB_1].CurrentNumMob;
										CurrentNumMob += mNPCGen.pList[SECRET_ROOM_N_SALA3_MOB_2].CurrentNumMob;

										if (CurrentNumMob == 1)
										{
											CartaTime = 60;

											ClearAreaTeleport(834, 3595, 889, 3645, CartaPos[3][0], CartaPos[3][1]);

											CartaSala++;

											MSG_STANDARDPARM sm;

											sm.Type = _MSG_StartTime;
											sm.ID = ESCENE_FIELD;
											sm.Size = sizeof(MSG_STANDARDPARM);
											sm.Parm = CartaTime * 2;

											MapaMulticast(6, 28, (MSG_STANDARD*)&sm, 0);
										}
									}

									else if (GenerateID >= SECRET_ROOM_N_SALA4_MOB_1 && GenerateID <= SECRET_ROOM_N_SALA4_MOB_4)
									{
										int CurrentNumMob = mNPCGen.pList[SECRET_ROOM_N_SALA4_MOB_1].CurrentNumMob;
										CurrentNumMob += mNPCGen.pList[SECRET_ROOM_N_SALA4_MOB_2].CurrentNumMob;
										CurrentNumMob += mNPCGen.pList[SECRET_ROOM_N_SALA4_MOB_3].CurrentNumMob;
										CurrentNumMob += mNPCGen.pList[SECRET_ROOM_N_SALA4_MOB_4].CurrentNumMob;

										if (CurrentNumMob == 1)
										{
											//ClearArea(776, 3595, 834, 3648);
											CartaTime = 3;
											CartaSala = 4;
										}
									}
#pragma endregion
#pragma region Carta de Duelo (A)
									else if (GenerateID >= SECRET_ROOM_A_SALA1_MOB_1 && GenerateID <= SECRET_ROOM_A_SALA1_MOB_2)
									{
										int CurrentNumMob = mNPCGen.pList[SECRET_ROOM_A_SALA1_MOB_1].CurrentNumMob;
										CurrentNumMob += mNPCGen.pList[SECRET_ROOM_A_SALA1_MOB_2].CurrentNumMob;

										if (CurrentNumMob == 1)
										{
											CartaTime = 60;

											ClearAreaTeleport(778, 3652, 832, 3698, CartaPos[1][0], CartaPos[1][1]);

											CartaSala++;

											MSG_STANDARDPARM sm;

											sm.Type = _MSG_StartTime;
											sm.ID = ESCENE_FIELD;
											sm.Size = sizeof(MSG_STANDARDPARM);
											sm.Parm = CartaTime * 2;

											MapaMulticast(6, 28, (MSG_STANDARD*)&sm, 0);
										}
									}

									else if (GenerateID >= SECRET_ROOM_A_SALA2_MOB_1 && GenerateID <= SECRET_ROOM_A_SALA2_MOB_2)
									{
										int CurrentNumMob = mNPCGen.pList[SECRET_ROOM_A_SALA2_MOB_1].CurrentNumMob;
										CurrentNumMob += mNPCGen.pList[SECRET_ROOM_A_SALA2_MOB_2].CurrentNumMob;

										if (CurrentNumMob == 1)
										{
											CartaTime = 60;

											ClearAreaTeleport(836, 3652, 890, 3698, CartaPos[2][0], CartaPos[2][1]);

											CartaSala++;

											MSG_STANDARDPARM sm;

											sm.Type = _MSG_StartTime;
											sm.ID = ESCENE_FIELD;
											sm.Size = sizeof(MSG_STANDARDPARM);
											sm.Parm = CartaTime * 2;

											MapaMulticast(6, 28, (MSG_STANDARD*)&sm, 0);
										}
									}

									else if (GenerateID >= SECRET_ROOM_A_SALA3_MOB_1 && GenerateID <= SECRET_ROOM_A_SALA3_MOB_2)
									{
										int CurrentNumMob = mNPCGen.pList[SECRET_ROOM_A_SALA3_MOB_1].CurrentNumMob;
										CurrentNumMob += mNPCGen.pList[SECRET_ROOM_A_SALA3_MOB_2].CurrentNumMob;

										if (CurrentNumMob == 1)
										{
											CartaTime = 60;

											ClearAreaTeleport(834, 3595, 889, 3645, CartaPos[3][0], CartaPos[3][1]);

											CartaSala++;

											MSG_STANDARDPARM sm;

											sm.Type = _MSG_StartTime;
											sm.ID = ESCENE_FIELD;
											sm.Size = sizeof(MSG_STANDARDPARM);
											sm.Parm = CartaTime * 2;

											MapaMulticast(6, 28, (MSG_STANDARD*)&sm, 0);
										}
									}

									else if (GenerateID >= SECRET_ROOM_A_SALA4_MOB_1 && GenerateID <= SECRET_ROOM_A_SALA4_MOB_4)
									{
										int CurrentNumMob = mNPCGen.pList[SECRET_ROOM_A_SALA4_MOB_1].CurrentNumMob;
										CurrentNumMob += mNPCGen.pList[SECRET_ROOM_A_SALA4_MOB_2].CurrentNumMob;
										CurrentNumMob += mNPCGen.pList[SECRET_ROOM_A_SALA4_MOB_3].CurrentNumMob;
										CurrentNumMob += mNPCGen.pList[SECRET_ROOM_A_SALA4_MOB_4].CurrentNumMob;

										if (CurrentNumMob == 1)
										{
											//ClearArea(776, 3595, 834, 3648);
											CartaTime = 3;
											CartaSala = 4;
										}
									}
#pragma endregion
#pragma region Pista de Runas
#pragma region Pista +0 Lich_Crunt
									else if (GenerateID == RUNEQUEST_LV0_LICH1 || GenerateID == RUNEQUEST_LV0_LICH2)
									{
										//srand(time(NULL));
										int _rand = rand() % 100;

										if (_rand < 20)
										{
											for (int c = MAX_USER; c < MAX_MOB; c++)
											{
												if (pMob[c].Mode == USER_EMPTY)
													continue;

												if (pMob[c].GenerateIndex != RUNEQUEST_LV0_LICH1 && pMob[c].GenerateIndex != RUNEQUEST_LV0_LICH2)
													continue;

												DeleteMob(c, 3);
											}

											int partyleader = pMob[a_iConn].Leader;

											if (partyleader <= 0)
												partyleader = a_iConn;

											STRUCT_ITEM Runa;
											memset(&Runa, 0, sizeof(STRUCT_ITEM));

											//srand(time(NULL));
											Runa.sIndex = PistaRune[0][rand() % 4];

											if (partyleader > 0 && partyleader < MAX_USER)
												PutItem(partyleader, &Runa);

											for (int i = 0; i < MAX_PARTY; i++)
											{
												int partymember = pMob[partyleader].PartyList[i];

												if (partymember >= MAX_USER)
													continue;

												if (pUser[partymember].Mode != USER_PLAY)
													continue;

												Runa.sIndex = PistaRune[0][rand() % 4];
												PutItem(partymember, &Runa);
											}

											STRUCT_ITEM NextPista;
											memset(&NextPista, 0, sizeof(STRUCT_ITEM));

											NextPista.sIndex = 5134;
											NextPista.stEffect[0].cEffect = 43;
											NextPista.stEffect[0].cValue = 1;

											PutItem(partyleader, &NextPista);

											sprintf(temp, "etc,questRune +0 complete leader:%s", pMob[partyleader].MOB.MobName);
											Log(temp, "-system", 0);
										}
										else
										{
											for (int c = MAX_USER; c < MAX_MOB; c++)
											{
												if (pMob[c].Mode == USER_EMPTY)
													continue;

												if (pMob[c].GenerateIndex != RUNEQUEST_LV0_LICH1 && pMob[c].GenerateIndex != RUNEQUEST_LV0_LICH2)
													continue;

												DeleteMob(c, 3);
											}

											GenerateMob(RUNEQUEST_LV0_LICH1, 0, 0);
											GenerateMob(RUNEQUEST_LV0_LICH1, 0, 0);

											GenerateMob(RUNEQUEST_LV0_LICH2, 0, 0);
											GenerateMob(RUNEQUEST_LV0_LICH2, 0, 0);
										}
									}
#pragma endregion
#pragma region Pista +1 Torre
									else if (GenerateID == RUNEQUEST_LV1_TORRE1 || GenerateID == RUNEQUEST_LV1_TORRE2 || GenerateID == RUNEQUEST_LV1_TORRE3)
									{
										int party = GenerateID - RUNEQUEST_LV1_TORRE1;

										Pista[1].Party[party].MobCount = 0;
									}

									else if (GenerateID >= RUNEQUEST_LV1_MOB_INITIAL && GenerateID <= RUNEQUEST_LV1_MOB_END)
									{
										int partyleader = pMob[a_iConn].Leader;

										if (partyleader <= 0)
											partyleader = a_iConn;

										if (mNPCGen.pList[RUNEQUEST_LV1_TORRE1].CurrentNumMob >= 1 && Pista[1].Party[0].LeaderID == partyleader)
											Pista[1].Party[0].MobCount++;

										else if (mNPCGen.pList[RUNEQUEST_LV1_TORRE2].CurrentNumMob >= 1 && Pista[1].Party[1].LeaderID == partyleader)
											Pista[1].Party[1].MobCount++;

										else if (mNPCGen.pList[RUNEQUEST_LV1_TORRE3].CurrentNumMob >= 1 && Pista[1].Party[2].LeaderID == partyleader)
											Pista[1].Party[2].MobCount++;

										//if ((Pista[1].Party[0].MobCount || Pista[1].Party[1].MobCount || Pista[1].Party[2].MobCount) <= 0)
									}
#pragma endregion
#pragma region Pista +2 Amon
									else if (GenerateID == RUNEQUEST_LV2_MOB_BOSS)
									{
										int partyleader = pMob[a_iConn].Leader;

										if (partyleader <= 0)
											partyleader = a_iConn;

										STRUCT_ITEM Runa;
										memset(&Runa, 0, sizeof(STRUCT_ITEM));

										//srand(time(NULL));
										Runa.sIndex = PistaRune[2][rand() % 5];

										if (partyleader > 0 && partyleader < MAX_USER)
											PutItem(partyleader, &Runa);

										for (int i = 0; i < MAX_PARTY; i++)
										{
											int partymember = pMob[partyleader].PartyList[i];

											if (partymember >= MAX_USER)
												continue;

											if (pUser[partymember].Mode != USER_PLAY)
												continue;

											Runa.sIndex = PistaRune[2][rand() % 5];
											PutItem(partymember, &Runa);

										}

										STRUCT_ITEM NextPista;
										memset(&NextPista, 0, sizeof(STRUCT_ITEM));

										NextPista.sIndex = 5134;
										NextPista.stEffect[0].cEffect = 43;
										NextPista.stEffect[0].cValue = 3;

										PutItem(partyleader, &NextPista);

										sprintf(temp, "etc,questRune +2 complete leader:%s", pMob[partyleader].MOB.MobName);
										Log(temp, "-system", 0);
									}
#pragma endregion
#pragma region Pista +3 Sulrang
									else if (GenerateID >= RUNEQUEST_LV3_MOB_SULRANG_INITIAL && GenerateID <= RUNEQUEST_LV3_MOB_SULRANG_END && Pista[3].Party[0].LeaderID != 0 && Pista[3].Party[0].MobCount == 0)
									{
										Pista[3].Party[0].MobCount = 1;
										//srand(time(NULL));
										GenerateMob(RUNEQUEST_LV3_MOB_BOSS_INITIAL + rand() % 7, 0, 0);
									}
#pragma endregion
#pragma region Pista +4 Labirinto
									else if (GenerateID >= RUNEQUEST_LV4_MOB_INITIAL && GenerateID <= RUNEQUEST_LV4_MOB_END && mNPCGen.pList[GenerateID].CurrentNumMob == 1)
									{
										int leader = pMob[a_iConn].Leader;

										int partyleader = pMob[a_iConn].Leader;

										if (partyleader <= 0)
											partyleader = a_iConn;

										if (partyleader == Pista[4].Party[0].LeaderID && Pista[4].Party[1].MobCount >= 1 && Pista[4].Party[2].MobCount >= 1)
										{
											Pista[4].Party[0].MobCount--;

											if (Pista[4].Party[0].MobCount == 0)
											{
												DoTeleport(partyleader, 3351, 1334);

												for (int i = 0; i < MAX_PARTY; i++)
												{
													int partya_iConn = pMob[partyleader].PartyList[i];

													if (partya_iConn > 0 && partya_iConn < MAX_USER && partya_iConn != partyleader && pUser[partya_iConn].Mode == USER_PLAY)
														DoTeleport(partya_iConn, 3352, 1334);
												}

												GenerateMob(RUNEQUEST_LV4_MOB_BOSS, 0, 0);
											}
										}
										else if (partyleader == Pista[4].Party[1].LeaderID && Pista[4].Party[0].MobCount >= 1 && Pista[4].Party[2].MobCount >= 1)
										{
											Pista[4].Party[1].MobCount--;

											if (Pista[4].Party[1].MobCount == 0)
											{
												DoTeleport(partyleader, 3351, 1334);

												for (int i = 0; i < MAX_PARTY; i++)
												{
													int partya_iConn = pMob[partyleader].PartyList[i];

													if (partya_iConn > 0 && partya_iConn < MAX_USER && partya_iConn != partyleader && pUser[partya_iConn].Mode == USER_PLAY)
														DoTeleport(partya_iConn, 3351, 1334);
												}

												GenerateMob(RUNEQUEST_LV4_MOB_BOSS, 0, 0);
											}
										}
										else if (partyleader == Pista[4].Party[2].LeaderID && Pista[4].Party[1].MobCount >= 1 && Pista[4].Party[0].MobCount >= 1)
										{
											Pista[4].Party[2].MobCount--;

											if (Pista[4].Party[2].MobCount == 0)
											{
												DoTeleport(partyleader, 3351, 1334);

												for (int i = 0; i < MAX_PARTY; i++)
												{
													int partya_iConn = pMob[partyleader].PartyList[i];

													if (partya_iConn > 0 && partya_iConn < MAX_USER && partya_iConn != partyleader && pUser[partya_iConn].Mode == USER_PLAY)
														DoTeleport(partya_iConn, 3351, 1334);
												}

												GenerateMob(RUNEQUEST_LV4_MOB_BOSS, 0, 0);
											}
										}
									}

									else if (GenerateID == RUNEQUEST_LV4_MOB_BOSS)
									{
										int partyleader = pMob[a_iConn].Leader;

										if (partyleader <= 0)
											partyleader = a_iConn;

										STRUCT_ITEM Runa;
										memset(&Runa, 0, sizeof(STRUCT_ITEM));
										//srand(time(NULL));
										Runa.sIndex = PistaRune[4][rand() % 3];

										if (partyleader > 0 && partyleader < MAX_USER)
											PutItem(partyleader, &Runa);


										for (int i = 0; i < MAX_PARTY; i++)
										{
											int partymember = pMob[partyleader].PartyList[i];

											if (partymember >= MAX_USER)
												continue;

											if (pUser[partymember].Mode != USER_PLAY)
												continue;

											Runa.sIndex = PistaRune[4][rand() % 3];
											PutItem(partymember, &Runa);
										}


										STRUCT_ITEM NextPista;
										memset(&NextPista, 0, sizeof(STRUCT_ITEM));

										NextPista.sIndex = 5134;
										NextPista.stEffect[0].cEffect = 43;
										NextPista.stEffect[0].cValue = 5;

										PutItem(partyleader, &NextPista);

										sprintf(temp, "etc,questRune +4 complete leader:%s", pMob[partyleader].MOB.MobName);
										Log(temp, "-system", 0);
									}
#pragma endregion
#pragma region Pista +5 Balrog
									else if (GenerateID == RUNEQUEST_LV5_MOB_BOSS)
									{
										Pista[5].Party[0].MobCount = 1;

										int partyleader = pMob[a_iConn].Leader;

										if (partyleader <= 0)
											partyleader = a_iConn;

										STRUCT_ITEM Runa;
										memset(&Runa, 0, sizeof(STRUCT_ITEM));
										//srand(time(NULL));
										Runa.sIndex = PistaRune[5][rand() % 6];

										if (partyleader > 0 && partyleader < MAX_USER)
											PutItem(partyleader, &Runa);

										for (int i = 0; i < MAX_PARTY; i++)
										{
											int partymember = pMob[partyleader].PartyList[i];

											if (partymember >= MAX_USER)
												continue;

											if (pUser[partymember].Mode != USER_PLAY)
												continue;

											Runa.sIndex = PistaRune[5][rand() % 6];
											PutItem(partymember, &Runa);
										}


										STRUCT_ITEM NextPista;
										memset(&NextPista, 0, sizeof(STRUCT_ITEM));

										NextPista.sIndex = 5134;
										NextPista.stEffect[0].cEffect = 43;
										NextPista.stEffect[0].cValue = 6;

										PutItem(partyleader, &NextPista);

										sprintf(temp, "etc,questRune +5 complete leader:%s", pMob[partyleader].MOB.MobName);
										Log(temp, "-system", 0);
									}
#pragma endregion
#pragma region Pista +6 Coelho
									else if (GenerateID >= RUNEQUEST_LV6_MOB_INITIAL && GenerateID <= RUNEQUEST_LV6_MOB_END)
									{
										if (Pista[6].MobsLeft >= 100) return;

										Pista[6].MobsLeft++;

										if (Pista[6].MobsLeft == 100)
											GenerateMob(RUNEQUEST_LV6_MOB_BOSS, 0, 0);

									}

									else if (GenerateID == RUNEQUEST_LV6_MOB_BOSS)
									{
										int partyleader = pMob[a_iConn].Leader;

										if (partyleader <= 0)
											partyleader = a_iConn;

										STRUCT_ITEM Runa;
										memset(&Runa, 0, sizeof(STRUCT_ITEM));
										//srand(time(NULL));
										Runa.sIndex = PistaRune[6][rand() % 8];

										if (partyleader > 0 && partyleader < MAX_USER)
											PutItem(partyleader, &Runa);


										for (int i = 0; i < MAX_PARTY; i++)
										{
											int partymember = pMob[partyleader].PartyList[i];

											if (partymember >= MAX_USER)
												continue;

											if (pUser[partymember].Mode != USER_PLAY)
												continue;

											Runa.sIndex = PistaRune[6][rand() % 8];
											PutItem(partymember, &Runa);
										}

										sprintf(temp, "etc,questRune +6 complete leader:%s", pMob[partyleader].MOB.MobName);
										Log(temp, "-system", 0);
									}
#pragma endregion

#pragma region Pista +1 - Lugefer_Inf
									else if (GenerateID >= RUNEQUEST_LV1_MOB_INITIAL && GenerateID <= RUNEQUEST_LV1_MOB_END)
										GenerateMob(GenerateID, 0, 0);
#pragma endregion
#pragma region Pista +2 - Amon_Inf
									else if (GenerateID >= RUNEQUEST_LV2_MOB_INITIAL && GenerateID <= RUNEQUEST_LV2_MOB_END)
										GenerateMob(GenerateID, 0, 0);
#pragma endregion
#pragma region Pista +3 - Kalintz_Mago
									else if (GenerateID >= RUNEQUEST_LV3_MOB_BOSS_INITIAL && GenerateID <= RUNEQUEST_LV3_MOB_BOSS_END && Pista[3].Party[0].LeaderID != 0 && Pista[3].Party[0].MobCount != 0)
									{
										//srand(time(NULL));
										GenerateMob(RUNEQUEST_LV3_MOB_BOSS_INITIAL + rand() % 7, 0, 0);

										int leader = pMob[a_iConn].Leader;

										int partyleader = pMob[a_iConn].Leader;

										if (partyleader <= 0)
											partyleader = a_iConn;

										if (partyleader == Pista[3].Party[0].LeaderID)
											Pista[3].Party[0].MobCount++;

										else if (partyleader == Pista[3].Party[1].LeaderID)
											Pista[3].Party[1].MobCount++;

										else if (partyleader == Pista[3].Party[2].LeaderID)
											Pista[3].Party[2].MobCount++;
									}
#pragma endregion
#pragma region Kefra - Mago_Negro
									else if (GenerateIndex >= KEFRA_MOB_INITIAL && GenerateIndex <= KEFRA_MOB_END && KefraLive == 0)
										GenerateMob(GenerateIndex, 0, 0);
#pragma endregion

#pragma region Invasão Armia
										for (size_t i = 0; i < INVADE_ARMIA.ID.size(); i++)
										{
											if (GenerateIndex == INVADE_ARMIA.ID[i])
											{
												InvadeArmiaMobCount++;
												InvadeArmiaDropMob(a_iConn);

												if (InvadeArmiaMobCount >= INVADE_ARMIA.Group)
												{
													InvadeArmiaWaveKilled(GenerateIndex);
													InvadeArmiaMobCount = 0;
												}

												break;
											}

										
										}

										if (GenerateIndex == INVADE_ARMIA.IDBoss)
											InvadeArmiaBossKilled(GenerateIndex);
#pragma endregion

#pragma region FamPoint Count
										FamePointBoss(a_iConn, GenerateIndex);
										FamePointMob(a_iConn, GenerateIndex);
#pragma endregion

#pragma endregion
#pragma region Coliseu (N)
									if (GenerateID >= 4623 && GenerateID <= 4634)
									{
										STRUCT_ITEM item;
										memset(&item, 0, sizeof(STRUCT_ITEM));

										//srand(time(NULL));
										int _rand = rand() % 14;

										if (_rand == 0)
											item.sIndex = 419;

										else if (_rand == 1)
											item.sIndex = 420;

										else if (_rand == 2)
											item.sIndex = 4026;

										if (item.sIndex)
										{
											SetItemBonus(&item, 0, 0, 0);

											PutItem(a_iConn, &item);
										}
									}
#pragma endregion

									else if (GenerateID == 5 || GenerateID == 6 || GenerateID == 7)
									{
										STRUCT_ITEM item;
										memset(&item, 0, sizeof(STRUCT_ITEM));
										//srand(time(NULL));
										int _rand = rand() % 14;

										if (_rand == 0)
											item.sIndex = 421 + (rand() % 7);

										else if (_rand == 1)
											item.sIndex = 419;

										if (item.sIndex)
										{
											SetItemBonus(&item, 0, 0, 0);

											if (pHeightGrid[AlvoY][AlvoX] > -40 && pHeightGrid[AlvoY][AlvoX] < 36)
												PutItem(a_iConn, &item);
											//CreateItem(AlvoX, AlvoY, &item, rand() % 4, 1);
										}
									}
#pragma region Calabouço Zumbi
									else if (GenerateID >= 4566 && GenerateID <= 4618)
									{
										g_calabouco.Left--;

										for (int i = 0; i < MAX_USER; i++)
										{
											if ((pMob[i].TargetX / 128) == 13 || (pMob[i].TargetY / 128) == 16)
												SendCounterMob(i, g_calabouco.Left, 52);
										}

										if (g_calabouco.Left == NULL)
										{
											GenerateMob(4619, 0, 0);

											for (int i = 0; i < MAX_USER; i++)
											{
												if ((pMob[i].TargetX / 128) == 13 || (pMob[i].TargetY / 128) == 16)
													SendClientMsg(i, "Troll Zumbi acaba de nascer no centro do calabouço.");
											}
										}
									}

									else if (GenerateID == 4619)
									{
										STRUCT_ITEM item;
										memset(&item, 0, sizeof(STRUCT_ITEM));

										for (int i = 0; i < MAX_USER; i++)
										{
											if (pUser[i].Mode != USER_PLAY)
												continue;

											if ((pMob[i].TargetX / 128) == 13 || (pMob[i].TargetY / 128) == 16)
											{
												item.sIndex = 5550;
												PutItem(i, &item);
												DoRecall(i);
											}
										}
									}
#pragma endregion
#pragma region Lan House N - Boss

									if ((!strcmp(pMob[target].MOB.MobName, "AranhaAmald")) || (!strcmp(pMob[target].MOB.MobName, "GargulaAmald"))
										|| (!strcmp(pMob[target].MOB.MobName, "HorizonAmald")) || (!strcmp(pMob[target].MOB.MobName, "MorlockAmald")))
									{
										if (g_quests.HouseNLeft >= 4001) return;


										SendCounterMob(a_iConn, g_quests.HouseNLeft, 4000);

										g_quests.HouseNLeft++;

										if (g_quests.HouseNLeft == 4001)
										{
											if (g_quests.HouseNStatus == false)
											{
												CreateMob("Solitario", 3684, 3684, "npc", 0);
												SendNoticeArea("O BOSS [Solitário] foi summonado no primeiro andar.", 3604, 3601, 3690, 3690);
												g_quests.HouseNStatus = true;
											}

											g_quests.HouseNLeft = 0;
										}
									}

									if (!strcmp(pMob[target].MOB.MobName, "Solitario"))
									{
										//srand(time(NULL));
										int rand_ = rand() % 100;
										STRUCT_ITEM Item;
										memset(&Item, 0, sizeof(STRUCT_ITEM));

										if (rand_ <= 10)
											Item.sIndex = 4028;

										else if (rand_ <= 30)
										{
											Item.sIndex = 413;
											Item.stEffect[0].cEffect = EF_AMOUNT;
											Item.stEffect[0].cValue = 1;
										}

										else if (rand_ <= 60)
										{
											Item.sIndex = 412;
											Item.stEffect[0].cEffect = EF_AMOUNT;
											Item.stEffect[0].cValue = 2;
										}
										else
										{
											Item.sIndex = 4019;
											Item.stEffect[0].cEffect = EF_AMOUNT;
											Item.stEffect[0].cValue = 5;
										}

										g_quests.HouseNStatus = false;

										PutItem(a_iConn, &Item);
									}
#pragma endregion

									CCastleZakum::MobKilled(target, a_iConn, PosX, PosY);
									// CEncampment::MobKilled(target, a_iConn, PosX, PosY);

									if (GenerateID == ORC_GUERREIRO)
										DoRecall(a_iConn);

									else if (GenerateID >= TORRE_NOATUM1 && GenerateID <= TORRE_NOATUM3)
										LiveTower[GenerateID - TORRE_NOATUM1] = 0;

									else if (GenerateID == REI_HARABARD)
									{
										Kingdom1Clear = 1;
										SendNoticeArea(g_pMessageStringTable[_NN_King1_Killed], 1676, 1556, 1776, 1636);
									}
									else if (GenerateID == REI_GLANTUAR)
									{
										Kingdom2Clear = 1;
										SendNoticeArea(g_pMessageStringTable[_NN_King2_Killed], 1676, 1816, 1776, 1892);
									}

#pragma region Quest Diaria 
									if (pUser[a_iConn].QuestAtiva != 0)
									{
										char msg[126];

										STRUCT_QUESTDIARIA packet;
										memset(&packet, 0, sizeof(STRUCT_QUESTDIARIA));
										packet.Type = 0xD01;
										packet.ID = a_iConn;
										packet.Size = sizeof(STRUCT_QUESTDIARIA);

										if (pMob[target].MOB.Equip[0].sIndex == QuestDiaria[pUser[a_iConn].QuestAtiva].IdMob1 && pUser[a_iConn].CountMob1 < QuestDiaria[pUser[a_iConn].QuestAtiva].QtdMob1)
										{
											pUser[a_iConn].CountMob1++;

											packet.IndexQuest = pUser[a_iConn].QuestAtiva;
											packet.Count1 = pUser[a_iConn].CountMob1;
											packet.Count2 = pUser[a_iConn].CountMob2;
											packet.Count3 = pUser[a_iConn].CountMob3;

											packet.CountMax1 = QuestDiaria[packet.IndexQuest].QtdMob1;
											packet.CountMax2 = QuestDiaria[packet.IndexQuest].QtdMob2;
											packet.CountMax3 = QuestDiaria[packet.IndexQuest].QtdMob3;

											SendCounterMob(a_iConn, pUser[a_iConn].CountMob1, QuestDiaria[pUser[a_iConn].QuestAtiva].QtdMob1);

											pUser[a_iConn].cSock.SendOneMessage((char*)&packet, sizeof(STRUCT_QUESTDIARIA));
										}

										if (pMob[target].MOB.Equip[0].sIndex == QuestDiaria[pUser[a_iConn].QuestAtiva].IdMob2 && pUser[a_iConn].CountMob2 < QuestDiaria[pUser[a_iConn].QuestAtiva].QtdMob2)
										{
											pUser[a_iConn].CountMob2++;

											packet.IndexQuest = pUser[a_iConn].QuestAtiva;
											packet.Count1 = pUser[a_iConn].CountMob1;
											packet.Count2 = pUser[a_iConn].CountMob2;
											packet.Count3 = pUser[a_iConn].CountMob3;

											packet.CountMax1 = QuestDiaria[packet.IndexQuest].QtdMob1;
											packet.CountMax2 = QuestDiaria[packet.IndexQuest].QtdMob2;
											packet.CountMax3 = QuestDiaria[packet.IndexQuest].QtdMob3;

											SendCounterMob(a_iConn, pUser[a_iConn].CountMob2, QuestDiaria[pUser[a_iConn].QuestAtiva].QtdMob2);

											pUser[a_iConn].cSock.SendOneMessage((char*)&packet, sizeof(STRUCT_QUESTDIARIA));
										}


										if (pMob[target].MOB.Equip[0].sIndex == QuestDiaria[pUser[a_iConn].QuestAtiva].IdMob3 && pUser[a_iConn].CountMob3 < QuestDiaria[pUser[a_iConn].QuestAtiva].QtdMob3)
										{
											pUser[a_iConn].CountMob3++;

											packet.IndexQuest = pUser[a_iConn].QuestAtiva;
											packet.Count1 = pUser[a_iConn].CountMob1;
											packet.Count2 = pUser[a_iConn].CountMob2;
											packet.Count3 = pUser[a_iConn].CountMob3;

											packet.CountMax1 = QuestDiaria[packet.IndexQuest].QtdMob1;
											packet.CountMax2 = QuestDiaria[packet.IndexQuest].QtdMob2;
											packet.CountMax3 = QuestDiaria[packet.IndexQuest].QtdMob3;

											SendCounterMob(a_iConn, pUser[a_iConn].CountMob3, QuestDiaria[pUser[a_iConn].QuestAtiva].QtdMob3);

											pUser[a_iConn].cSock.SendOneMessage((char*)&packet, sizeof(STRUCT_QUESTDIARIA));
										}

										if (pUser[a_iConn].CountMob1 == QuestDiaria[pUser[a_iConn].QuestAtiva].QtdMob1)
										{
											if (pUser[a_iConn].CountMob2 == QuestDiaria[pUser[a_iConn].QuestAtiva].QtdMob2) // Adicionar o 3 mob aqui
											{
												if (pUser[a_iConn].CountMob3 == QuestDiaria[pUser[a_iConn].QuestAtiva].QtdMob3)
												{
													STRUCT_ITEM item;
													memset(&item, 0, sizeof(STRUCT_ITEM));
													long long expGain = QuestDiaria[pUser[a_iConn].QuestAtiva].ExpReward;
													int coinGain = QuestDiaria[pUser[a_iConn].QuestAtiva].GoldReward;
													coinGain += pMob[a_iConn].MOB.Coin;
													expGain += pMob[a_iConn].MOB.Exp;

													if (coinGain >= MAX_COIN)
														coinGain = MAX_COIN - pMob[a_iConn].MOB.Coin;

													if (expGain >= MAX_EXP)
														expGain = MAX_EXP - pMob[a_iConn].MOB.Exp;

													pMob[a_iConn].MOB.Exp += expGain;
													pMob[a_iConn].MOB.Coin += coinGain;

													sprintf(temp, "Adquiriu %d de exp", QuestDiaria[pUser[a_iConn].QuestAtiva].ExpReward);
													SendMsgExp(a_iConn, temp, TNColor::Default, false);

													sprintf(temp, "Adquiriu %d de gold", QuestDiaria[pUser[a_iConn].QuestAtiva].GoldReward);
													SendMsgExp(a_iConn, temp, TNColor::Yellow, false);

													item.sIndex = QuestDiaria[pUser[a_iConn].QuestAtiva].Item->sIndex;
													item.stEffect[0].cEffect = QuestDiaria[pUser[a_iConn].QuestAtiva].Item->stEffect[0].cEffect;
													item.stEffect[0].cValue = QuestDiaria[pUser[a_iConn].QuestAtiva].Item->stEffect[0].cValue;
													item.stEffect[1].cEffect = QuestDiaria[pUser[a_iConn].QuestAtiva].Item->stEffect[1].cEffect;
													item.stEffect[1].cValue = QuestDiaria[pUser[a_iConn].QuestAtiva].Item->stEffect[1].cValue;
													item.stEffect[2].cEffect = QuestDiaria[pUser[a_iConn].QuestAtiva].Item->stEffect[2].cEffect;
													item.stEffect[2].cValue = QuestDiaria[pUser[a_iConn].QuestAtiva].Item->stEffect[2].cValue;

													PutItem(a_iConn, &item);

													sprintf(msg, "!Você recebeu [%s (qnt. %d)] por concluir a missão diária.", g_pItemList[item.sIndex].Name, item.stEffect[0].cValue);
													SendClientMsg(a_iConn, msg);

													pUser[a_iConn].QuestAtiva = 0;

													packet.IndexQuest = pUser[a_iConn].QuestAtiva;

													pUser[a_iConn].cSock.SendOneMessage((char*)&packet, sizeof(STRUCT_QUESTDIARIA));
												}
											}
										}
									}
#pragma endregion

								}

#pragma endregion
#pragma region Drop Gold
								int MobCoin = pMob[target].MOB.Coin;
								int UNKGOLD = 18;

								if (pMob[target].MOB.BaseScore.Level < 10)
									UNKGOLD = 2;
								else if (pMob[target].MOB.BaseScore.Level < 20)
									UNKGOLD = 4;
								else if (pMob[target].MOB.BaseScore.Level < 30)
									UNKGOLD = 6;
								else if (pMob[target].MOB.BaseScore.Level < 50)
									UNKGOLD = 9;

								//srand(time(NULL));
								UNKGOLD = rand() % (UNKGOLD + 1);

								if (MobCoin && UNKGOLD == 0)
								{
									MobCoin = 4 * (rand() % (((MobCoin + 1) / 4) + 1) + (MobCoin + 1) / 4 + MobCoin);

									if (MobCoin > 2000)
										MobCoin = 2000;

									if (MobCoin + pMob[a_iConn].MOB.Coin > 2000000000)
										SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_get_more_than_2G]);
									else
									{
										pMob[a_iConn].MOB.Coin += MobCoin;
										SendEtc(a_iConn);

										sprintf(temp, "Adquiriu %d de gold", MobCoin);
										SendMsgExp(a_iConn, temp, TNColor::Yellow, false);
									}
								}
#pragma endregion
#pragma region Drop Evento em todos os mobs
								//srand(time(NULL));
								if (evOn && evStartIndex && evEndIndex && evItem && evRate && evCurrentIndex < evEndIndex && rand() % evRate == 0)
								{
									STRUCT_ITEM item;
									memset(&item, 0, sizeof(STRUCT_ITEM));

									item.sIndex = evItem;

									if (evIndex)
									{
										item.stEffect[0].cEffect = 62;
										item.stEffect[0].cValue = evCurrentIndex / 256;
										item.stEffect[1].cEffect = 63;
										item.stEffect[1].cValue = evCurrentIndex;
										item.stEffect[2].cEffect = 59;
										item.stEffect[2].cValue = rand();

										sprintf(temp, " [%s] Dropou [%s] de [%d].", pMob[a_iConn].MOB.MobName, g_pItemList[evItem].Name, evCurrentIndex);
									}
									else
										sprintf(temp, "[%s] Dropou [%s]", pMob[a_iConn].MOB.MobName, g_pItemList[evItem].Name);

									if (evNotice)
										SendMsgExp(a_iConn, temp, TNColor::Default, true);

									evCurrentIndex++;

									SetItemBonus(&item, pMob[target].MOB.CurrentScore.Level, 0, 0);
									PutItem(a_iConn, &item);
									DrawConfig(1);
								}

#pragma endregion
#pragma region Drop comum
								int target_level = pMob[target].MOB.CurrentScore.Level;

								for (int i = 0; i < MAX_CARRY; i++)
								{
									if (pMob[target].MOB.Carry[i].sIndex == 0)
										continue;

									int droprate = g_pDropRate[i];
									int dropbonus = g_pDropBonus[i] + pMob[a_iConn].DropBonus;

									if (dropbonus != 100)
									{
										dropbonus = 10000 / (dropbonus + 1);
										droprate = dropbonus * droprate / 100;
									}

									int pos = i / 8;

									if (i < 60)
									{
										if (pos == 0 || pos == 1 || pos == 2)
										{
											if (target_level < 10)
												droprate = 4 * droprate / 100;

											else if (target_level < 20)
												droprate = 5 * droprate / 100;

											else if (target_level < 30)
												droprate = 6 * droprate / 100;

											else if (target_level < 40)
												droprate = 7 * droprate / 100;

											else if (target_level < 60)
												droprate = 8 * droprate / 100;

											else
												droprate = 99 * droprate / 100;
										}
									}

									else
									{
										if (target_level < 170)
											droprate = 90 * droprate / 100;

										else if (target_level < 200)
											droprate = 60 * droprate / 100;

										else if (target_level < 230)
											droprate = 50 * droprate / 100;

										else if (target_level < 255)
											droprate = 43 * droprate / 100;

										else if (target_level < 320)
											droprate = 38 * droprate / 100;

										else
											droprate = 50 * droprate / 100;
									}

									/* Zona Lan House N */
									if ((pMob[a_iConn].TargetX / 128) == 28 || (pMob[a_iConn].TargetY / 128) == 28)
										droprate = 30 * droprate / 100;

									/* Zona Nipplehein */
									if ((pMob[a_iConn].TargetX / 128) == 28 || (pMob[a_iConn].TargetY / 128) == 23)
										droprate = 30 * droprate / 100;

									else if ((pMob[a_iConn].TargetX / 128) == 27 || (pMob[a_iConn].TargetY / 128) == 23)
										droprate = 30 * droprate / 100;

									else if ((pMob[a_iConn].TargetX / 128) == 29 || (pMob[a_iConn].TargetY / 128) == 23)
										droprate = 30 * droprate / 100;

									else if ((pMob[a_iConn].TargetX / 128) == 28 || (pMob[a_iConn].TargetY / 128) == 22)
										droprate = 30 * droprate / 100;

									if (TESTSERVER)
										droprate /= 2;

									if (LOCALSERVER)
										droprate /= 100;

									if (pMob[a_iConn].MOB.Rsv & 4)
									{
										int special2 = pMob[a_iConn].MOB.CurrentScore.Special[2];
										special2 = special2 / 10 + 10;
										special2 = 100 - special2;
										droprate = special2 * droprate / 100;
									}

									if (i == 8 || i == 9 || i == 10)
										droprate = 4;

									if (i == 11)
										droprate = 1;

									//srand(time(NULL));

									if (droprate >= 32000)
										droprate = 32000;

									if (droprate <= 0)
										droprate = 0;
									else
										droprate = rand() % droprate;

									if (droprate == 0 || i == 11)
									{
										STRUCT_ITEM* item = &pMob[target].MOB.Carry[i];

										if (item->sIndex <= 390 || item->sIndex >= MAX_ITEMLIST)
											continue;

										if (item->sIndex == 454)
											continue;

										int reqlv = g_pItemList[item->sIndex].ReqLvl;

										if (reqlv < 140 || (droprate % 2) != 1)
										{
											int bonus = 0;

											if (a_iConn > 0 && a_iConn < MAX_USER)
												bonus = pMob[a_iConn].DropBonus + pMob[a_iConn].g_pFairyContent[1];

											if (g_pRvrWar.Bonus != 0)
											{
												if (g_pRvrWar.Bonus == pMob[a_iConn].MOB.Clan)
													bonus += (bonus * 5) / 100;
											}

											SetItemBonus(item, pMob[target].MOB.CurrentScore.Level, 0, bonus);

											if (CCastleZakum::KeyDrop(target, a_iConn, PosX, PosY, item) == TRUE) {
												bool isFlag = false;

												if (pMob[a_iConn].g_pFairyContent[3] == 1)
												{
													for (int j = 0; j < MAX_FAIRY_BONUS; j++)
													{
														if (pMob[a_iConn].g_pFairyAmounts[j] == item->sIndex)
														{
															for (int k = 0; k < pMob[a_iConn].MaxCarry; k++)
															{
																if (pMob[a_iConn].MOB.Carry[k].sIndex == item->sIndex)
																{
																	int result = BASE_GetItemAmount(&pMob[a_iConn].MOB.Carry[k]);

																	if (result == 0) { result = 1; }

																	int Count = BASE_GetItemAmount(item);

																	if (Count == 0) Count = 1;

																	result += Count;

																	if (result > 120) continue;

																	BASE_SetItemAmount(&pMob[a_iConn].MOB.Carry[k], result);

																	SendItem(a_iConn, ITEM_PLACE_CARRY, k, &pMob[a_iConn].MOB.Carry[k]);

																	isFlag = true;
																	break;
																}
															}
															break;
														}
													}
												}

												if (pMob[a_iConn].CheckDrop == 1)
												{
													if (pMob[a_iConn].CheckItemDrop == 0)
														continue;

													if (pMob[a_iConn].CheckItemDrop == item->sIndex)
														isFlag = false;
													else
													{
														sprintf(temp, "Item [%s] foi deletado pelo autodrop.", g_pItemList[item->sIndex].Name);
														SendMsgExp(a_iConn, temp, TNColor::GreenYellow, false);
														return;
													}
												}

												if (isFlag == false)
												{
													int isFadaAmmount = FALSE;
													for (size_t i = 0; i < sizeof(fadaAmmount); i++)
													{
														if (item->sIndex == fadaAmmount[i])
														{
															isFadaAmmount = TRUE;
															break;
														}
													}

													if (pMob[a_iConn].MOB.Equip[13].sIndex == 3915 && isFadaAmmount)
													{
														if (!AutoAmmount(a_iConn, item))
															PutItem(a_iConn, item);
													}
													else
														PutItem(a_iConn, item);
												}
											}

											sprintf(temp, "MobName:%s dropou o item: %s:%d %d.%d.%d.%d.%d.%d do mob:%s", pMob[a_iConn].MOB.MobName, g_pItemList[item->sIndex].Name, item->sIndex, item->stEffect[0].cEffect, item->stEffect[0].cValue, item->stEffect[1].cEffect, item->stEffect[1].cValue, item->stEffect[2].cEffect, item->stEffect[2].cValue, pMob[target].MOB.MobName);

											if (a_iConn > 0 && a_iConn < MAX_USER)
												Log(temp, pUser[a_iConn].AccountName, pUser[a_iConn].IP);

											if (pMob[a_iConn].MOB.Carry > 0)
											{
												if (BASE_GetItemSanc(item) > 0)
												{
													sprintf(temp, "Adquiriu [%s +%d]", g_pItemList[item->sIndex].Name, BASE_GetItemSanc(item));
													SendMsgExp(a_iConn, temp, TNColor::GoldenEscuro, false);
												}
												else
												{
													sprintf(temp, "Adquiriu [%s]", g_pItemList[item->sIndex].Name);
													SendMsgExp(a_iConn, temp, TNColor::GoldenClaro, false);
												}
											}
											MSG_STANDARDPARM updateItemDayLog;
											memset(&updateItemDayLog, 0, sizeof(MSG_STANDARDPARM));

											updateItemDayLog.Size = sizeof(MSG_STANDARDPARM);
											updateItemDayLog.Type = _MSG_DBItemDayLog;
											updateItemDayLog.ID = 0;
											updateItemDayLog.Parm = item->sIndex;

											DBServerSocket.SendOneMessage((char*)&updateItemDayLog, sizeof(MSG_STANDARDPARM));

											if (LOCALSERVER)
											{
												int item_index = item->sIndex;

												int reqlv = g_pItemList[item_index].ReqLvl;
												int itempos = g_pItemList[item_index].nPos;

												if (itempos & 0xFE && itempos != 128 && a_iConn < MAX_USER)
												{
													sprintf(temp, "%-12s - %s(%d:%d) %d(%d:%d)",
														pMob[target].MOB.MobName, g_pItemList[item_index].Name,
														pMob[target].MOB.CurrentScore.Level, reqlv, g_dLevel, g_dLevel1,
														g_dLevel2);

													SendSay(a_iConn, temp);
												}
											}

											if (i == 8 || i == 9 || i == 10)
												i = 11;
										}
									}
								}
#pragma endregion
#pragma region Quest Amuleto mistico
								//srand(time(NULL));
								if (a_iConn < MAX_USER && (pMob[target].MOB.Equip[0].sIndex == 239 || pMob[target].MOB.Equip[0].sIndex == 241) && !(rand() % 20))
								{
									if (pMob[a_iConn].Extra.QuestInfo.Mortal.TerraMistica == 1)
									{
										SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Watching_Town_Success]);
										pMob[a_iConn].Extra.QuestInfo.Mortal.TerraMistica = 2;
									}
								}
#pragma endregion
								DeleteMob(target, 1);

								WarOfTower::KilledTower(target, a_iConn, 0, 0);
							}
							else
								DeleteMob(target, 1);
						}
					}

					else
					{
						GridMulticast(pMob[target].TargetX, pMob[target].TargetY, (MSG_STANDARD*)&sm, 0);
						DeleteMob(target, 1);
					}
				}

				else
				{
					GridMulticast(pMob[target].TargetX, pMob[target].TargetY, (MSG_STANDARD*)&sm, 0);
					DeleteMob(target, 1);
				}
			}
			else
			{
				//pUser[target].ReqHp = pMob[target].MOB.CurrentScore.MaxHp;
				SetReqHp(target);

				pMob[target].MOB.CurrentScore.Hp = pMob[target].MOB.CurrentScore.MaxHp;
				SendScore(target);
			}
		}
#pragma endregion
#pragma region PvP
		else
		{
			int tlevel = pMob[target].MOB.BaseScore.Level;

			if (tlevel < 0 || tlevel > MAX_LEVEL)
				return;

#pragma region Lose EXP
			unsigned int curexp = (unsigned int)(pMob[target].Extra.ClassMaster == MORTAL || pMob[target].Extra.ClassMaster == ARCH ? g_pNextLevel[tlevel] : g_pNextLevel_2[tlevel]);
			unsigned int nextexp = (unsigned int)(pMob[target].Extra.ClassMaster == MORTAL || pMob[target].Extra.ClassMaster == ARCH ? g_pNextLevel[tlevel + 1] : g_pNextLevel_2[tlevel + 1]);
			unsigned int alphaexp = (nextexp - curexp);
			unsigned int deltaexp = (nextexp - curexp) / 20;

			if (tlevel >= 30)
				deltaexp = alphaexp / 22;

			if (tlevel >= 40)
				deltaexp = alphaexp / 25;

			if (tlevel >= 50)
				deltaexp = alphaexp / 30;

			if (tlevel >= 60)
				deltaexp = alphaexp / 35;

			if (tlevel >= 70)
				deltaexp = alphaexp / 40;

			if (tlevel >= 80)
				deltaexp = alphaexp / 45;

			if (tlevel >= 90)
				deltaexp = alphaexp / 50;

			if (tlevel >= 100)
				deltaexp = alphaexp / 55;

			if (tlevel >= 150)
				deltaexp = alphaexp / 70;

			if (tlevel >= 200)
				deltaexp = alphaexp / 85;

			if (tlevel >= 250)
				deltaexp = alphaexp / 100;

			if (deltaexp < 0)
				deltaexp = 0;
			if (deltaexp > 150000)
				deltaexp = 150000;
#pragma endregion

			WarOfTower::KilledTower(target, a_iConn, 0, 0);

			int killer_curkill = GetCurKill(a_iConn);
			int killer_totkill = GetTotKill(a_iConn);
			int killer_pkpoint = GetPKPoint(a_iConn);
			int killed_pkpoint = GetPKPoint(target);
			int killed_guilty = GetGuilty(target);
			int killed_curkill = GetCurKill(target);
			int killed_clan = pMob[target].MOB.Clan;
			int killer_clan = pMob[a_iConn].MOB.Clan;
			int SameClan = 0;
			int AtWar = 0;

			if (killed_pkpoint > 10 && killed_pkpoint <= 25)
				deltaexp *= 3;
			else
				deltaexp *= 5;

			int killed_x = pMob[target].TargetX / 128;
			int killed_y = pMob[target].TargetY / 128;

#pragma region Perca de CP em War
			if (a_iConn < MAX_USER)
			{
				if (TESTSERVER)
					deltaexp /= 3;

				else
					deltaexp /= 6;

				//desativado verificação de reino pra perca de cp
				//if (killed_clan == 7 && killer_clan == 8 || killed_clan == 8 && killer_clan == 7)
				//	SameClan = 1;

				int killed_guild = pMob[target].MOB.Guild;
				int killer_guild = pMob[a_iConn].MOB.Guild;
				int max_guild = 65536;

				if (killed_guild > 0 && killed_guild < max_guild && killer_guild > 0 && killer_guild < max_guild
					&& g_pGuildWar[killed_guild] == killer_guild && g_pGuildWar[killer_guild] == killed_guild)
					AtWar = 1;

				if (CastleState && killed_x == 8 && killed_y == 13)
					AtWar = 1;

				if (g_pRvrWar.Status != 0)
					AtWar = 1;

				if (TowerStage != 0)
					AtWar = 1;

				if (StartAltarKing)
					AtWar = 1;
			}
#pragma endregion

			GridMulticast(pMob[target].TargetX, pMob[target].TargetY, (MSG_STANDARD*)&sm, 0);

			int arena = BASE_GetArena(pMob[target].TargetX, pMob[target].TargetY);
			int village = BASE_GetVillage(pMob[target].TargetX, pMob[target].TargetY);
			int ZoneUnk = 0;

			if (killed_x == 1 && killed_y == 31 /*|| killed_x == 19 && killed_y == 30*/)
				ZoneUnk = 1;

			if (arena != 5 || village != 5 || ZoneUnk)
			{
				SendClientMsg(target, g_pMessageStringTable[_NN_In_Arena_No_Exp_Loss]);

				if (arena >= 0 && arena < MAX_GUILDZONE)
				{
					STRUCT_ITEM item;
					memset(&item, 0, sizeof(STRUCT_ITEM));

					item.sIndex = 431;
					SetItemBonus(&item, 0, 0, 0);
					//srand(time(NULL));
					CreateItem(pMob[target].TargetX, pMob[target].TargetY, &item, rand() % 4, 1);
				}
			}

			else
			{
				if (TESTSERVER)
					deltaexp /= 4;

				if (SameClan)
					deltaexp += killed_curkill * deltaexp / 4;

				if (deltaexp > 30000)
					deltaexp = 30000;

				if (deltaexp < 0)
					deltaexp = 0;


				if ((tlevel >= 35 || pMob[target].Extra.ClassMaster != MORTAL) && NewbieEventServer == 0)
				{
					if (a_iConn >= MAX_USER)
					{
						if (DEADPOINT)
							pMob[target].Extra.Hold += (unsigned int)(pMob[target].MOB.Exp > deltaexp ? deltaexp : pMob[target].MOB.Exp);
					}
					else
						pMob[target].Extra.Hold += (unsigned int)(pMob[target].MOB.Exp > deltaexp ? deltaexp : pMob[target].MOB.Exp);

					if (DEADPOINT || a_iConn < MAX_USER)
					{
						sprintf(temp, g_pMessageStringTable[_DN_lose_D_exp], deltaexp);
						SendClientMsg(target, temp);
						SendEtc(target);
					}
				}
				else if (pMob[target].MOB.CurrentScore.Level < FREEEXP && pMob[target].Extra.ClassMaster == MORTAL && NewbieEventServer == 0)
					SendClientMsg(target, g_pMessageStringTable[_NN_Below_lv20_No_Exp_Loss]);

				if (SameClan)
				{
					SendEtc(a_iConn);

					++killer_curkill;
					SetCurKill(a_iConn, killer_curkill);

					++killer_totkill;
					SetTotKill(a_iConn, killer_totkill);

					if (AtWar == 0 && killed_guilty == 0)
					{
						int Lostpk = 3 * killed_pkpoint / -20;
						if (Lostpk < -3)
							Lostpk = -3;

						if (Lostpk > 0)
							Lostpk = 0;

						if (killed_guilty > 0)
							Lostpk = 0;

						killer_pkpoint += Lostpk;
						SetPKPoint(a_iConn, killer_pkpoint);
						sprintf(temp, g_pMessageStringTable[_DD_PKPointMinus], killer_pkpoint - 75, Lostpk);
						SendClientMsg(a_iConn, temp);
					}

				}
#pragma region Perca de CP
				else
				{
					int ZoneUnk = 0;

					if (killed_x == 1 && killed_y == 31 || killed_x == 19 && killed_y == 30)
						ZoneUnk = 1;

					if (AtWar == 0 && !ZoneUnk)
					{
						int LostPk = 3 * killed_pkpoint / -25;

						if (LostPk < -3)
							LostPk = -3;

						if (LostPk > 0)
							LostPk = 0;

						if (killed_guilty > 0)
							LostPk = 0;

						if (pMob[target].MOB.Equip[15].sIndex == 548 || pMob[target].MOB.Equip[15].sIndex == 549 || pMob[a_iConn].MOB.Equip[15].sIndex == 548 || pMob[a_iConn].MOB.Equip[15].sIndex == 549)
							LostPk *= 3;

						killer_pkpoint += LostPk;

						SetPKPoint(a_iConn, killer_pkpoint);

						if (LostPk)
						{
							sprintf(temp, g_pMessageStringTable[_DD_PKPointMinus], killer_pkpoint - 75, -LostPk);
							SendClientMsg(a_iConn, temp);
						}

#pragma region  Perca de itens, cp negativo
						if (killed_pkpoint <= 60)
						{
							int killed_loseitem = (75 - killed_pkpoint) / 10;
							int killed_numitem = 0;

							for (int i = 0; i < MAX_CARRY - 1; i++)
							{
								//srand(time(NULL));
								if (rand() % 5)
									continue;

								STRUCT_ITEM* ItemLose = &pMob[target].MOB.Carry[i];

								if (pMob[target].MOB.Carry[i].sIndex <= 0)
									continue;

								if (ItemLose->sIndex > MAX_ITEMLIST || ItemLose->sIndex == 508 || ItemLose->sIndex == 509 || ItemLose->sIndex == 522 || ItemLose->sIndex >= 526 && ItemLose->sIndex <= 531)
									continue;

								if (ItemLose->sIndex == 446)
									continue;

								//srand(time(NULL));
								int create = CreateItem(pMob[target].TargetX, pMob[target].TargetY, ItemLose, 0, rand() % 4);

								if (create >= MAX_ITEM || create <= 0)
									continue;

								if (BASE_NeedLog(ItemLose, 0))
								{
									char logitem[256];

									BASE_GetItemCode(ItemLose, logitem);

									sprintf(temp, "cho %s", logitem);

									Log(temp, pUser[target].AccountName, pUser[target].IP);
								}

								memset(ItemLose, 0, sizeof(STRUCT_ITEM));

								MSG_CNFDropItem cnfDrop;

								cnfDrop.Type = _MSG_CNFDropItem;
								cnfDrop.Size = sizeof(MSG_CNFDropItem);

								cnfDrop.SourType = ITEM_PLACE_CARRY;
								cnfDrop.SourPos = i;

								cnfDrop.GridX = pMob[target].TargetX;
								cnfDrop.GridY = pMob[target].TargetY;

								pUser[target].cSock.SendOneMessage((char*)&cnfDrop, sizeof(MSG_CNFDropItem));

								killed_numitem++;
								//srand(time(NULL));
								if (rand() % 2 && killed_numitem < killed_loseitem)
									continue;
							}
						}
						if (killed_pkpoint <= 35)
						{
							int killed_loseitem = (killed_pkpoint + 10) / 10;

							if (killed_loseitem <= 0)
								killed_loseitem = 1;

							//srand(time(NULL));
							int drop = rand() % killed_loseitem;

							while (!drop)
							{
								//srand(time(NULL));
								int slot = rand() % 14 + 1;
								if (slot != 12)
								{
									STRUCT_ITEM* ItemLose = &pMob[target].MOB.Equip[slot];
									if (pMob[target].MOB.Equip[slot].sIndex > 0 && ItemLose->sIndex <= MAX_ITEMLIST && ItemLose->sIndex != 508 && ItemLose->sIndex != 509 && ItemLose->sIndex != 522 && (ItemLose->sIndex < 526 || ItemLose->sIndex > 531))
									{
										if (ItemLose->sIndex != 446)
										{
											int create = CreateItem(pMob[target].TargetX, pMob[target].TargetY, ItemLose, 0, rand() % 4);
											if (create > 0 && create < 5000)
											{
												if (BASE_NeedLog(ItemLose, 0))
												{
													char itemname[256];

													BASE_GetItemCode(ItemLose, itemname);
													sprintf(temp, "cho %s", itemname);

													Log(temp, pUser[target].AccountName, pUser[target].IP);
												}
												SendItem(target, ITEM_PLACE_EQUIP, slot, &pMob[target].MOB.Equip[slot]);
												memset(ItemLose, 0, sizeof(STRUCT_ITEM));

												MSG_CNFDropItem cnfDrop;

												cnfDrop.Type = _MSG_CNFDropItem;
												cnfDrop.Size = sizeof(MSG_CNFDropItem);

												cnfDrop.SourType = ITEM_PLACE_CARRY;
												cnfDrop.SourPos = slot;

												cnfDrop.GridX = pMob[target].TargetX;
												cnfDrop.GridY = pMob[target].TargetY;

												pUser[target].cSock.SendOneMessage((char*)&cnfDrop, sizeof(MSG_CNFDropItem));
											}
										}
									}
									break;
								}
							}
						}
#pragma endregion
					}
				}
#pragma endregion
				GetCreateMob(a_iConn, &sCreateMob);
				GridMulticast(pMob[a_iConn].TargetX, pMob[a_iConn].TargetY, (MSG_STANDARD*)&sCreateMob, 0);

				if (SameClan)
					SetCurKill(target, 0);

				if (killed_pkpoint < 75 && !AtWar && a_iConn < MAX_USER)
				{
					killed_pkpoint++;
					SetPKPoint(target, killed_pkpoint);
					sprintf(temp, g_pMessageStringTable[_DD_PKPointPlus], killed_pkpoint - 75, 1);
					SendClientMsg(target, temp);
				}
				GetCreateMob(target, &sCreateMob);
				GridMulticast(pMob[target].TargetX, pMob[target].TargetY, (MSG_STANDARD*)&sCreateMob, 0);

				sprintf(temp, "etc PK killer:%s(%d,%d) killed:%s(%d,%d) kingdom:%d war:%d",
					pMob[a_iConn].MOB.MobName, pMob[a_iConn].MOB.CurrentScore.Level, killer_pkpoint, pMob[target].MOB.MobName,
					pMob[target].MOB.CurrentScore.Level, killed_pkpoint, SameClan, AtWar);

				Log(temp, "-system", 0);
			}

#pragma region  HP Monstros
			if (pMob[target].MOB.Equip[13].sIndex == 753 || pMob[target].MOB.Equip[13].sIndex == 1726)//10X HP MOB  - 20X HP MOB
			{
				int sanc = BASE_GetItemSanc(&pMob[target].MOB.Equip[13]);
				if (sanc > 0)
				{
					sanc--;

					if (pMob[target].MOB.Equip[13].stEffect[0].cEffect == 43)
						pMob[target].MOB.Equip[13].stEffect[0].cValue = sanc;

					else if (pMob[target].MOB.Equip[13].stEffect[1].cEffect == 43)
						pMob[target].MOB.Equip[13].stEffect[1].cValue = sanc;

					else if (pMob[target].MOB.Equip[13].stEffect[2].cEffect == 43)
						pMob[target].MOB.Equip[13].stEffect[2].cValue = sanc;
				}
				else
					BASE_ClearItem(&pMob[target].MOB.Equip[13]);

				SendItem(target, ITEM_PLACE_EQUIP, 13, &pMob[target].MOB.Equip[13]);
			}
#pragma endregion
#pragma region  Limpar invocações
			if (pMob[target].MOB.Class == 2)
			{
				int IsLeader = pMob[target].Leader;

				if (IsLeader == 0) { IsLeader = target; }

				for (int i = 0; i < MAX_PARTY + 1; i++)
				{
					int vConn = 0;

					if (i == 0) { vConn = IsLeader; }
					else
					{
						vConn = pMob[IsLeader].PartyList[i - 1];
					}

					if (vConn < MAX_USER || vConn >= MAX_MOB) continue;

					int Summoner = pMob[vConn].Summoner;

					if (Summoner && Summoner == target)
					{
						DeleteMob(vConn, 3);
					}
				}
			}
#pragma endregion
		}
#pragma endregion
	}
	catch (const std::exception& e)
	{
		sprintf(temp, "error mobKilled: [%s]",e.what());
		MyLog(LogType::System, pUser[a_iConn].AccountName, temp, 0, pUser[a_iConn].IP);
	}
	
}
