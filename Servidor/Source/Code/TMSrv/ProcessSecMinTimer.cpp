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
#include "MacroPerga.h"
#include <thread>
#include "WarOfNoatum.h"
#include "WarOfCity.h"
#include "WarOfKingdom.h"
#include "AltarOfKing.h"
#include "AutoEvent.h"
#include "SombraNegra.h"
#include "BossCamp.h"
#include "AutoBan.h"
#include "GuildHall.h"
#include "InvadeArmia.h"

void ProcessSecTimer()
{
	if (ServerDown == 120) // two minutes untill the server closes
	{
		if (BILLING != 0)
		{
			_AUTH_GAME Unk;

			memset(&Unk, 0, 196);

			SendBilling2(&Unk, 4);

			BILLING = 0;
		}

		while (TRUE)
		{
			if (UserCount >= MAX_USER)
			{
				Log("sys,server down complete", "-system", 0);

				if (hFont != 0)
				{
					DeleteObject(hFont);

					hFont = NULL;
				}

				PostQuitMessage(NULL);

				return;
			}

			if (pUser[UserCount].Mode == USER_EMPTY)
			{
				UserCount++;

				continue;
			}

			break;
		}

		pUser[UserCount].AccountName[ACCOUNTNAME_LENGTH - 1] = 0;
		pUser[UserCount].AccountName[ACCOUNTNAME_LENGTH - 2] = 0;

		sprintf(temp, "sys,save %d - %d - %s", UserCount, pUser[UserCount].Mode, pUser[UserCount].AccountName);
		Log(temp, "-system", 0);

		CloseUser(UserCount);

		UserCount++;

		return;
	}

	if (ServerDown > -1000)
	{
		if (ServerDown <= 0)
		{
			ServerDown++;

			goto lbl_PST1;
		}

		if (ServerDown % 20 == 1)
		{
			int messageId = ServerDown / 20;
			SendNotice(g_pMessageStringTable[messageId + 17]);
		}

		ServerDown++;

		if (ServerDown == 120)
		{
			SetTimer(hWndMain, TIMER_SEC, 200, 0);

			return;
		}
	}

lbl_PST1:

	SecCounter++;

	CurrentTime = timeGetTime();

	if (SecCounter % 120)
		CReadFiles::ReadMacblock();

	if (BILLING != 0 && BillCounter > 0 && BillServerSocket.Sock == 0)
	{
		BillCounter--;

		if (BillCounter <= 0)
		{
			CurrentTime = timeGetTime();

			sprintf(temp, "err,start reconnect BILL %d", CurrentTime);
			Log(temp, "-system", 0);

			int *pip = (int*)LocalIP;

			int ret = BillServerSocket.ConnectBillServer(BillServerAddress, BillServerPort, *pip, WSA_READBILL);

			CurrentTime = timeGetTime();

			sprintf(temp, "err,start reconnect BILL %d", CurrentTime);
			Log(temp, "-system", 0);

			if (ret == 0)
			{
				Log("err,Reconnect BILL Server(x2) fail.", "-system", 0);

				BILLING = 0;
			}
			else
			{
				_AUTH_GAME Unk;

				memset(&Unk, 0, 196);

				SendBilling2(&Unk, 4);
			}
		}
	}
	else
		BillCounter = 0;

	if (SecCounter % 8 == 0)
	{
		for (int i = 0; i < MAX_USER; i++)
		{
			if (SaveCount >= MAX_USER)
				SaveCount = 1;

			if (pUser[SaveCount].Mode == USER_PLAY && pMob[SaveCount].Mode != MOB_EMPTY)
			{
				if (BILLING == 2 && pUser[SaveCount].Unk_2728 == 1 && pMob[SaveCount].MOB.CurrentScore.Level >= FREEEXP && (g_Hour <= 12 || g_Hour >= 19))
				{
					SendClientMsg(SaveCount, g_pMessageStringTable[_NN_Child_Pay]);
					CharLogOut(SaveCount);

					SaveCount++;

					break;
				}
				else
				{
					SaveUser(SaveCount, 0);

					SaveCount++;

					break;
				}
			}

			SaveCount++;
			
			
					
		}
	}

	if (SecCounter % 10 == 0)
	{
		try
		{

			CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)InitMacro, NULL, 0, 0);
			
		}
		catch (const std::exception&)
		{
			sprintf(temp, "err,start thread macro %d", CurrentTime);
			Log(temp, "-system macro perga", 0);
		}
		
		
	}

	for (int bb = 1; bb < MAX_USER; bb++)
	{
		if (pUser[bb].Mode)
		{
			if (pUser[bb].cSock.nSendPosition)
			{
				BOOL bSend = pUser[bb].cSock.SendMessageA();
				if (!bSend)
				{
					sprintf(temp, "err,send fail close %d/%d %d/%d",
						bb, pUser[bb].cSock.Sock, pUser[bb].cSock.nSendPosition, pUser[bb].cSock.nSentPosition);

					pUser[bb].AccountName[ACCOUNTNAME_LENGTH - 1] = 0;
					pUser[bb].AccountName[ACCOUNTNAME_LENGTH - 2] = 0;

					Log(temp, pUser[bb].AccountName, pUser[bb].IP);

					CloseUser(bb);
				}
			}
		}

		if (pUser[bb].Mode == USER_PLAY)
			pMob[bb].ProcessorSecTimer();

		//Celestial Lv181 dentro da zona do pesadelo
		if ((pMob[bb].TargetX / 128) == 9 && (pMob[bb].TargetY / 128) == 1 || (pMob[bb].TargetX / 128) == 8 && (pMob[bb].TargetY / 128) == 2 || (pMob[bb].TargetX / 128) == 10 && (pMob[bb].TargetY / 128) == 2)
		{
			if (pMob[bb].Extra.ClassMaster >= CELESTIAL && pMob[bb].MOB.CurrentScore.Level >= 180)
				DoRecall(bb);
		}

        //Vale Perdido
		if (((pMob[bb].TargetX) / 128) == 17 && ((pMob[bb].TargetY) / 128) == 28)
		{
			if (pMob[bb].MOB.Equip[13].sIndex != 3916)
				DoRecall(bb);
		}
#pragma region >> Pista de Runas Balrog Portais
		int xv = (pMob[bb].TargetX) & 0xFFFC;
		int yv = (pMob[bb].TargetY) & 0xFFFC;

		for (int x = 0; x < 3; x++)
		{
			if (pUser[bb].Mode != USER_PLAY || pMob[bb].MOB.CurrentScore.Hp <= 0 || Pista[5].Party[x].LeaderID == 0 || Pista[5].Party[x].LeaderID != bb || strcmp(Pista[5].Party[x].LeaderName, pMob[bb].MOB.MobName))
				continue;

			if (pMob[Pista[5].Party[x].LeaderID].Leader != -1 && pMob[Pista[5].Party[x].LeaderID].Leader)
				continue;

			//srand(time(NULL));
			int _rd = rand() % 3;

			int tx = 2100;
			int ty = 2100;

			//Sala 1 Portal 1
			if (xv == PistaBalrogPortalPos[0][0][0] && yv == PistaBalrogPortalPos[0][0][1])
			{
				if (_rd <= 1)
				{
					tx = PistaBalrogPos[1][0];
					ty = PistaBalrogPos[1][1];
				}

				else
				{
					tx = PistaBalrogPos[0][0];
					ty = PistaBalrogPos[0][1];
				}
			}

			//Sala 2 Portal 1
			else if (xv == PistaBalrogPortalPos[1][0][0] && yv == PistaBalrogPortalPos[1][0][1])
			{
				if (_rd <= 1)
				{
					tx = PistaBalrogPos[1][0];
					ty = PistaBalrogPos[1][1];
				}
				else if (_rd == 2)
				{
					tx = PistaBalrogPos[2][0];
					ty = PistaBalrogPos[2][1];
				}

				else
				{
					tx = PistaBalrogPos[0][0];
					ty = PistaBalrogPos[0][1];
				}
			}

			//Sala 2 Portal 2
			else if (xv == PistaBalrogPortalPos[1][1][0] && yv == PistaBalrogPortalPos[1][1][1])
			{
				if (_rd >= 2)
				{
					tx = PistaBalrogPos[1][0];
					ty = PistaBalrogPos[1][1];
				}
				else if (_rd == 0)
				{
					tx = PistaBalrogPos[2][0];
					ty = PistaBalrogPos[2][1];
				}

				else
				{
					tx = PistaBalrogPos[0][0];
					ty = PistaBalrogPos[0][1];
				}
			}

			//Sala 3 Portal 1
			else if (xv == PistaBalrogPortalPos[2][0][0] && yv == PistaBalrogPortalPos[2][0][1])
			{
				if (_rd <= 1)
				{
					tx = PistaBalrogPos[2][0];
					ty = PistaBalrogPos[2][1];
				}
				else if (_rd == 2)
				{
					tx = PistaBalrogPos[3][0];
					ty = PistaBalrogPos[3][1];
				}

				else
				{
					tx = PistaBalrogPos[1][0];
					ty = PistaBalrogPos[1][1];
				}
			}

			//Sala 3 Portal 2
			else if (xv == PistaBalrogPortalPos[2][1][0] && yv == PistaBalrogPortalPos[2][1][1])
			{
				if (_rd >= 2)
				{
					tx = PistaBalrogPos[2][0];
					ty = PistaBalrogPos[2][1];
				}
				else if (_rd == 0)
				{
					tx = PistaBalrogPos[3][0];
					ty = PistaBalrogPos[3][1];
				}

				else
				{
					tx = PistaBalrogPos[1][0];
					ty = PistaBalrogPos[1][1];
				}
			}

			//Sala 3 Portal 3
			else if (xv == PistaBalrogPortalPos[2][2][0] && yv == PistaBalrogPortalPos[2][2][1])
			{
				if (_rd <= 1)
				{
					tx = PistaBalrogPos[2][0];
					ty = PistaBalrogPos[2][1];
				}
				else if (_rd == 2)
				{
					tx = PistaBalrogPos[3][0];
					ty = PistaBalrogPos[3][1];
				}

				else
				{
					tx = PistaBalrogPos[1][0];
					ty = PistaBalrogPos[1][1];
				}
			}

			//Sala 4 Portal 1
			else if (xv == PistaBalrogPortalPos[3][0][0] && yv == PistaBalrogPortalPos[3][0][1])
			{
				if (_rd <= 1)
				{
					tx = PistaBalrogPos[3][0];
					ty = PistaBalrogPos[3][1];
				}
				else if (_rd == 2)
				{
					tx = PistaBalrogPos[4][0];
					ty = PistaBalrogPos[4][1];

					if (Pista[5].Party[0].MobCount == 0)
						GenerateMob(RUNEQUEST_LV5_MOB_BOSS, 0, 0);
				}

				else
				{
					tx = PistaBalrogPos[2][0];
					ty = PistaBalrogPos[2][1];
				}
			}

			//Sala 4 Portal 2
			else if (xv == PistaBalrogPortalPos[3][1][0] && yv == PistaBalrogPortalPos[3][1][1])
			{
				if (_rd >= 2)
				{
					tx = PistaBalrogPos[3][0];
					ty = PistaBalrogPos[3][1];
				}
				else if (_rd == 0)
				{
					tx = PistaBalrogPos[4][0];
					ty = PistaBalrogPos[4][1];

					if (Pista[5].Party[0].MobCount == 0)
						GenerateMob(RUNEQUEST_LV5_MOB_BOSS, 0, 0);
				}

				else
				{
					tx = PistaBalrogPos[2][0];
					ty = PistaBalrogPos[2][1];
				}
			}

			//Sala 4 Portal 3
			else if (xv == PistaBalrogPortalPos[3][2][0] && yv == PistaBalrogPortalPos[3][2][1])
			{
				if (_rd <= 1)
				{
					tx = PistaBalrogPos[3][0];
					ty = PistaBalrogPos[3][1];
				}
				else if (_rd == 2)
				{
					tx = PistaBalrogPos[4][0];
					ty = PistaBalrogPos[4][1];

					if (Pista[5].Party[0].MobCount == 0)
						GenerateMob(RUNEQUEST_LV5_MOB_BOSS, 0, 0);
				}

				else
				{
					tx = PistaBalrogPos[2][0];
					ty = PistaBalrogPos[2][1];
				}
			}

			//Sala 4 Portal 4
			else if (xv == PistaBalrogPortalPos[3][3][0] && yv == PistaBalrogPortalPos[3][3][1])
			{
				if (_rd <= 1)
				{
					tx = PistaBalrogPos[3][0];
					ty = PistaBalrogPos[3][1];
				}
				else if (_rd == 2)
				{
					tx = PistaBalrogPos[4][0];
					ty = PistaBalrogPos[4][1];

					if (Pista[5].Party[0].MobCount == 0)
						GenerateMob(RUNEQUEST_LV5_MOB_BOSS, 0, 0);
				}

				else
				{
					tx = PistaBalrogPos[2][0];
					ty = PistaBalrogPos[2][1];
				}
			}
			else
				continue;

			int inv = 0;
			for (inv = 0; inv < pMob[bb].MaxCarry && inv < MAX_CARRY; inv++)
			{
				if (pMob[bb].MOB.Carry[inv].sIndex == 4032)
				{
					BASE_ClearItem(&pMob[bb].MOB.Carry[inv]);
					SendItem(bb, ITEM_PLACE_CARRY, inv, &pMob[bb].MOB.Carry[inv]);
					break;
				}
			}

			if (inv == pMob[bb].MaxCarry)
				continue;

			DoTeleport(Pista[5].Party[x].LeaderID, tx, ty);

			for (int c = 0; c < MAX_PARTY; c++)
			{
				int partyconn = pMob[Pista[5].Party[x].LeaderID].PartyList[c];

				if (partyconn > 0 && partyconn < MAX_USER && partyconn != Pista[5].Party[x].LeaderID && pUser[partyconn].Mode == USER_PLAY)
					DoTeleport(partyconn, tx, ty);
			}
		}
#pragma endregion
	}


#pragma region >> Contador Laranja

	if(SecCounter % 12 == 0)
	{
		//Carta Sala 1
		int Sala1 = mNPCGen.pList[SECRET_ROOM_N_SALA1_MOB_1].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_N_SALA1_MOB_2].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_M_SALA1_MOB_1].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_M_SALA1_MOB_2].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_A_SALA1_MOB_1].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_A_SALA1_MOB_2].CurrentNumMob;
		int Sala2 = mNPCGen.pList[SECRET_ROOM_N_SALA2_MOB_1].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_N_SALA2_MOB_2].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_M_SALA2_MOB_1].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_M_SALA2_MOB_2].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_A_SALA2_MOB_1].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_A_SALA2_MOB_2].CurrentNumMob;
		int Sala3 = mNPCGen.pList[SECRET_ROOM_N_SALA3_MOB_1].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_N_SALA3_MOB_2].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_M_SALA3_MOB_1].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_M_SALA3_MOB_2].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_A_SALA3_MOB_1].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_A_SALA3_MOB_2].CurrentNumMob;
		int Sala4 = mNPCGen.pList[SECRET_ROOM_N_SALA4_MOB_1].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_N_SALA4_MOB_2].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_N_SALA4_MOB_3].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_N_SALA4_MOB_4].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_M_SALA4_MOB_1].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_M_SALA4_MOB_2].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_M_SALA4_MOB_3].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_M_SALA4_MOB_4].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_A_SALA4_MOB_1].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_A_SALA4_MOB_2].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_A_SALA4_MOB_3].CurrentNumMob + mNPCGen.pList[SECRET_ROOM_A_SALA4_MOB_4].CurrentNumMob;

		SendSignalParmArea(778, 3651, 832, 3699, ESCENE_FIELD, _MSG_MobLeft, Sala1);
		//Carta Sala 2
		SendSignalParmArea(836, 3651, 890, 3699, ESCENE_FIELD, _MSG_MobLeft, Sala2);
		//Carta Sala 3
		SendSignalParmArea(832, 3594, 890, 3644, ESCENE_FIELD, _MSG_MobLeft, Sala3);
		//Carta Sala 4
		SendSignalParmArea(780, 3594, 832, 3645, ESCENE_FIELD, _MSG_MobLeft, Sala4);

		//Pista de runas +6 - Coelho
		SendShortSignalParm2Area(3330, 1475, 3448, 1525, ESCENE_FIELD, _MSG_MobCount, Pista[6].MobsLeft, 100);
		

	}
#pragma endregion
#pragma region >> Verifica se o usuário está com várias contas abertas

	/* Lan House (A) */
	GetUserInAreaMac(0, 3860, 3602, 3946, 3690);

	/* Lan House (M) */
	GetUserInAreaMac(0, 3734, 3476, 3818, 3561);

	/* Lan House (N) */
	GetUserInAreaMac(0, 3604, 3601, 3690, 3690);

	/* Área de evento */
	GetUserInAreaMac(0, 2560, 2560, 2687, 2687);
	
	/*Loja Aberta*/
	//GetUserLojaMac();

	//GetUserInAreaMac2(0, 20, 20);

#pragma endregion
#pragma endregion
#pragma region >> Reset Areas
	if (SecCounter % 1200 == 0)
	{
		ClearArea(2232, 1564, 2263, 1592);// Capa Verde
		ClearArea(2640, 1966, 2670, 2004);//Reset habilidades
		ClearArea(1950, 1586, 1988, 1614);//Reset habilidades
		ClearArea(793, 4046, 827, 4080);//Quest Gargula
		ClearArea(3604, 3601, 3690, 3690);//Lanhouse N  

		for (int x = 1; x < MAX_USER; x++)
		{
			if (pMob[x].QuestFlag && pUser[x].Mode == USER_PLAY)
				pMob[x].QuestFlag = 0;
		}
	}
	if (SecCounter % 1800 == 0)
	{
		ClearMapa(20, 20);
	}
#pragma endregion
#pragma region >> Contador Fadas/Trajes/Esferas
	if(SecCounter % 120 == 0)
	{
		for(int user = 0; user < MAX_USER; user++)
		{
			
			if(pUser[user].Mode != USER_PLAY)
				continue;

			SendClientPac(user);

			if (pMob[user].MOB.Equip[14].sIndex >= 3980 && pMob[user].MOB.Equip[14].sIndex <= 3989 && BASE_CheckItemDate(&pMob[user].MOB.Equip[14]))
			{
				sprintf(temp, "etc,premium item end %d", pMob[user].MOB.Equip[14].sIndex);
				Log(temp, "-system", 0);

				BASE_ClearItem(&pMob[user].MOB.Equip[14]);
				SendItem(user, ITEM_PLACE_EQUIP, 14, &pMob[user].MOB.Equip[14]);
			}

			if (pMob[user].MOB.Equip[12].sIndex >= 4150 && pMob[user].MOB.Equip[12].sIndex <= 4188 && BASE_CheckItemDate(&pMob[user].MOB.Equip[12]))
			{
				sprintf(temp, "etc,premium item end %d", pMob[user].MOB.Equip[12].sIndex);
				Log(temp, "-system", 0);

				BASE_ClearItem(&pMob[user].MOB.Equip[12]);
				SendItem(user, ITEM_PLACE_EQUIP, 12, &pMob[user].MOB.Equip[12]);
			}

			if((pMob[user].MOB.Equip[13].sIndex >= 3900 && pMob[user].MOB.Equip[13].sIndex <= 3916) ||
				(pMob[user].MOB.Equip[13].sIndex > 3788 && pMob[user].MOB.Equip[13].sIndex < 3792))
			{
				BASE_CheckFairyDate(&pMob[user].MOB.Equip[13]);
				SendItem(user, ITEM_PLACE_EQUIP, 13, &pMob[user].MOB.Equip[13]);
				pMob[user].GetCurrentScore(user);
			}

			if (pMob[user].MOB.Carry[60].sIndex == 3467 && BASE_CheckItemDate(&pMob[user].MOB.Carry[60]))
			{
				BASE_ClearItem(&pMob[user].MOB.Carry[60]);
				SendItem(user, ITEM_PLACE_CARRY, 60, &pMob[user].MOB.Carry[60]);

				pMob[user].MaxCarry = 30;

				if (pMob[user].MOB.Carry[60].sIndex == 3467)
					pMob[user].MaxCarry += 15;

				if (pMob[user].MOB.Carry[61].sIndex == 3467)
					pMob[user].MaxCarry += 15;
			}

			if (pMob[user].MOB.Carry[61].sIndex == 3467 && BASE_CheckItemDate(&pMob[user].MOB.Carry[61]))
			{
				BASE_ClearItem(&pMob[user].MOB.Carry[61]);
				SendItem(user, ITEM_PLACE_CARRY, 61, &pMob[user].MOB.Carry[61]);

				pMob[user].MaxCarry = 30;

				if (pMob[user].MOB.Carry[60].sIndex == 3467)
					pMob[user].MaxCarry += 15;

				if (pMob[user].MOB.Carry[61].sIndex == 3467)
					pMob[user].MaxCarry += 15;
			}
		}
	}
#pragma endregion

	int Sec32 = SecCounter % 32;

	if (SecCounter % (120 * 60) == 0)
	{
		GuildZoneReport();
	}

	if (SecCounter % 2 == 0)
	{
		for (int i = 1; i < MAX_USER; i++)
		{
			if (pUser[i].Mode == USER_PLAY)
			{
				if (i % 32 == Sec32)
				{
					//CreateExportInspectTable(i);
				}

				if (pMob[i].MOB.CurrentScore.Hp > 0)
				{
					bool Flag = false;

					if (SecCounter % 20 == 0)
					{
						pUser[i].HP += pMob[i].MOB.BaseScore.Level + 30;
						pUser[i].MP += pMob[i].MOB.BaseScore.Level + 30;

						if (pMob[i].Extra.ClassMaster >= CELESTIAL)
						{
							pUser[i].HP += pMob[i].MOB.RegenHP;
							pUser[i].MP += pMob[i].MOB.RegenMP;
						}

						Flag = true;
					}

					int WaitHP = pUser[i].HP;

					if (WaitHP > 0)
					{
						int MaxHP = pMob[i].MOB.CurrentScore.MaxHp;
						int CurHP = pMob[i].MOB.CurrentScore.Hp;

						int HP = WaitHP - CurHP;

						if (HP >= _Max_Potion_HPCasting_) { HP = _Max_Potion_HPCasting_; }
						else
						{
							HP = abs(WaitHP);
						}

						pUser[i].HP -= HP;

						if (pUser[i].HP < 0) { pUser[i].HP = 0; }

						CurHP += HP;

						if (CurHP >= MaxHP) { CurHP = MaxHP; }

						pMob[i].MOB.CurrentScore.Hp = CurHP;

						Flag = true;
					}

					int WaitMP = pUser[i].MP;

					if (WaitMP < 0) { pUser[i].MP = 0; }

					if (WaitMP > 0)
					{
						int MaxMP = pMob[i].MOB.CurrentScore.MaxMp;
						int CurMP = pMob[i].MOB.CurrentScore.Mp;

						int MP = WaitMP - (MaxMP - CurMP);

						if (MP >= _Max_Potion_MPCasting_) { MP = _Max_Potion_MPCasting_; }
						else
						{
							MP = abs(WaitMP);

							if (MP < 0) MP = 0;
						}

						pUser[i].MP -= MP;

						if (pUser[i].MP < 0) { pUser[i].MP = 0; }

						CurMP += MP;

						if (CurMP >= MaxMP) { CurMP = MaxMP; }

						pMob[i].MOB.CurrentScore.Mp = CurMP;

						Flag = true;
					}

					if (Flag)
					{
						pMob[i].GetCurrentScore(i);
						SendHpMp(i);
					}

				}
			}

			//if (pUser[i].Mode != USER_EMPTY)
			//{

			//}
		}

		invadArmiaTime--;
	}

	if (SecCounter % 60 == 0)
	{
		InvadeArmiaTimeNotice();
	}

	if (SecCounter % 2 == 0)
	{
		struct tm when;
		time_t now;
		time(&now);
		when = *localtime(&now);

		if (StartAltarKing && altarKing.nTimer > 0)
			altarKing.nTimer--;
		if (StartAltarKing && altarKing.nTimer <= 0)
		{
			sprintf(temp, "Ninguem dominou o Altar do Rei, Evento encerrado!!!");
			SendNotice(temp);
			//Sleep(2000);
			noWinner();
		}

		for (size_t i = 0; i < MAX_USER; i++)
		{
			if (pUser[i].Mode != USER_PLAY)
				continue;
			//Altar Thor
			if (CastleServer == 1 
				&& (pMob[i].TargetX >= 1042 && pMob[i].TargetX <= 1162)
				&&(pMob[i].TargetY >= 1679 && pMob[i].TargetY <= 1771))
				MasterCastle(i);

			
			if (StartAltarKing && (pMob[i].TargetX >= altarKing.spotMSG.StartX && pMob[i].TargetX <= altarKing.spotMSG.DestX)
				&& (pMob[i].TargetY >= altarKing.spotMSG.StartY && pMob[i].TargetY <= altarKing.spotMSG.DestY))
				dominatorKing(i);

			CheckPlayGuildHall(i);

			//if (pMob[i].TargetX /128 == 20 && pMob[i].TargetY /128 == 15)
			//{
			//	SendClientSignalParm(i, ESCENE_FIELD, _MSG_StartTime, pUser[i].AltarStatus++);
			//}
	
		}

		//Novas Funcoes
		WarOfKingdom();
		startKing();
		fAutoNotice();
		fAutoDouble();
		ReadAutoBan();

		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)initBoss, NULL, 0, 0);
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)initBossCamp,(void*)Freak, 0, 0);
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)initBossCamp, (void*)Talos, 0, 0);
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)initBossCamp, (void*)Noah, 0, 0);
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)initBossCamp, (void*)Kirei, 0, 0);
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)StartInvadeArmia, NULL, 0, 0);
		NTask_StartEventTrade();

		if ((when.tm_wday == 2 && when.tm_hour == 12 && when.tm_min == 0) && when.tm_sec >= 0 && when.tm_sec <= 2 && KefraLive)
		{
			KefraLive = 0;

			//Kefra
			GenerateMob(KEFRA_BOSS, 0, 0);

			for(int xx = KEFRA_MOB_INITIAL; xx <= KEFRA_MOB_END; xx++)
				GenerateMob(xx, 0, 0);
		}
		
//#pragma region >> Espelho RainhaG
//		bool IsDead = true;
//		int Verid = 0;
//
//		for (int j = MAX_USER; j < MAX_MOB; j++)
//		{
//			if (strcmp(pMob[j].MOB.MobName, "Espelho RainhaG") == 0)
//			{
//				if (pMob[j].MOB.CurrentScore.Hp > 0)
//				{
//					IsDead = false;
//					Verid = j;
//
//					pMob[j].CurrentTradeSecTimer--;
//				}
//
//				if (pMob[j].CurrentTradeSecTimer == 0)
//				{
//					DeleteMob(j, 3);
//
//				}
//			}
//		}
//
//		if (SecCounter % 7200 == 0)
//		{
//			if (IsDead && Verid == 0)
//			{
//				int rand_ = rand() % 100;
//
//				if (rand_ <= 10)
//				CreateMob("Espelho_RainhaG", 3494, 2979, "npc", 0);	
//		
//				else if (rand_ <= 20)
//					CreateMob("Espelho_RainhaG", 3747, 2981, "npc", 0);
//
//				else if (rand_ <= 50)
//					CreateMob("Espelho_RainhaG", 3540, 2982, "npc", 0);
//
//				else if (rand_ <= 70)
//					CreateMob("Espelho_RainhaG", 3616, 2788, "npc", 0);
//
//				else if (rand_ <= 80)
//					CreateMob("Espelho_RainhaG", 3685, 3011, "npc", 0);
//				
//			}
//		}
//
//
//#pragma endregion
#pragma region Sorteio
				if (SecCounter % 7400 == 0)
				{
					int byResult = 0;
		
					int ClientId[MAX_USER] = { 0, };
		
					for (int i = 1; i < MAX_USER; i++)
					{
						if (pUser[i].Mode != USER_PLAY) continue;
		
						ClientId[byResult] = i; byResult++;
					}
		
					if (byResult != 0)
					{
						//srand(time(NULL));
						int nUser = ClientId[rand() % byResult];
		
						if (pUser[nUser].Mode == USER_PLAY)
						{
							int id = g_pRewardBonus[rand() % MAX_ITEM_REWARD_PER_HOUR];
		
							if (id != 0)
							{
								int i = 0;
									for (; i < MAX_CARGO - 8; i++)
									{
										if (pUser[nUser].Cargo[i].sIndex == 0)
										{
											pUser[nUser].Cargo[i].sIndex = id;
		
										SendItem(nUser, ITEM_PLACE_CARGO, i, &pUser[nUser].Cargo[i]);
		
										sprintf(temp, "Personagem [%s] foi sorteado e ganhou [%s].", pMob[nUser].MOB.MobName, g_pItemList[id].Name);
										SendSpkMsg(nUser, temp, TNColor::White, true);
										break;
									}
								}
							}
						}
					}
				}
		#pragma endregion
#pragma region >> Lojinha Offline
				if (SecCounter % 2 == 0)
				{
					for (int i = 0; i < MAX_USER; i++)
					{
						if (pUser[i].Mode != USER_PLAY)
							continue;

						if (pUser[i].ISTradTimer == 0 || pUser[i].TradeMode == 0)
							continue;

						int IsConn = -1;

						pUser[i].LojinhaTimer++;

						int TimeOne = pUser[i].ISTradTimer;
						bool Flag = false;

						for (int j = 0; j < MAX_USER; j++)
						{
							if (i == j) continue;

							if (pUser[j].Mode != USER_PLAY) continue;

							if (pUser[j].ISTradTimer == 0 || pUser[j].TradeMode == 0) continue;

							if (pUser[i].Mac[0] == pUser[j].Mac[0] && pUser[i].Mac[1] == pUser[j].Mac[1] && pUser[i].Mac[2] == pUser[j].Mac[2] && pUser[i].Mac[3] == pUser[j].Mac[3])
							{
								int TimeTwo = pUser[j].ISTradTimer;

								if (TimeOne <= TimeTwo) { IsConn = i; }
								else if (TimeTwo <= TimeOne) { IsConn = j; }
								continue;
							}
						}

						if (IsConn == -1) { IsConn = i; }

						if (pUser[i].LojinhaTimer >= 900) //  900 = 15 min porque passa de 2 em 2 ms
						{
							//verifica se é a conta principal
							if (!pUser[i].OnlyTrade)
							{
								/*STRUCT_ITEM Item;
								memset(&Item, 0, sizeof(STRUCT_ITEM));

								Item.sIndex = 475;*/

								PutItem(IsConn, &premioLojaAfk);

								sprintf(temp, "!Parabéns, você ganhou o item [%s] por tempo de comércio.", g_pItemList[premioLojaAfk.sIndex].Name);
								SendClientMsg(IsConn, temp);

								pUser[i].LojinhaTimer = 0;
							}
						}
					}
				}
#pragma endregion
#pragma region >> Reset Quests

				if (SecCounter % 2 == 0)
				{
					for (int i = 0; i < MAX_USER; i++)
					{
						if (pUser[i].Mode != USER_PLAY)
							continue;

						if (pMob[i].CheckQuest > 0) 
						pMob[i].CheckQuest--;

						SendClientSignalParmCoord(i, ESCENE_FIELD, _MSG_StartTime, pMob[i].CheckQuest, 2379, 2076, 2426, 2133);
						SendClientSignalParmCoord(i, ESCENE_FIELD, _MSG_StartTime, pMob[i].CheckQuest, 2228, 1700, 2257, 1728);
						SendClientSignalParmCoord(i, ESCENE_FIELD, _MSG_StartTime, pMob[i].CheckQuest, 459, 3887, 497, 3916);
						SendClientSignalParmCoord(i, ESCENE_FIELD, _MSG_StartTime, pMob[i].CheckQuest, 658, 3728, 703, 3762);
						SendClientSignalParmCoord(i, ESCENE_FIELD, _MSG_StartTime, pMob[i].CheckQuest, 1312, 4027, 1348, 4055);

						if (pMob[i].CheckQuest <= 0) // 15 min porque passa de 2 em 2 ms
						{
							ClearAreaQuest(i, 2379, 2076, 2426, 2133);// Coveiro
							ClearAreaQuest(i, 2228, 1700, 2257, 1728);//Carbuncle
							ClearAreaQuest(i, 459, 3887, 497, 3916);//Kaizen
							ClearAreaQuest(i, 658, 3728, 703, 3762);//Hidras
							ClearAreaQuest(i, 1312, 4027, 1348, 4055);//Elfos


							if (pMob[i].QuestFlag && pUser[i].Mode == USER_PLAY)
								pMob[i].QuestFlag = 0;

							pMob[i].CheckQuest = 0;
						}
					}
				}

#pragma endregion
#pragma region >> Pesadelo Start
				if (GetUserInArea(1152, 128, 1280, 256, temp) && (when.tm_min == 14 && when.tm_sec == 0 || when.tm_min == 34 && when.tm_sec == 0 || when.tm_min == 54 && when.tm_sec == 0))
				{
					MSG_STANDARDPARM sm;
					memset(&sm, 0, sizeof(MSG_STANDARDPARM));

					sm.Type = _MSG_StartTime;
					sm.ID = ESCENE_FIELD;
					sm.Size = sizeof(MSG_STANDARDPARM);
					sm.Parm = 900;

					MapaMulticast(9, 1, (MSG_STANDARD*)&sm, 0);
					//Pesa A
					for (int i = NIGHTMARE_A_INITIAL; i <= NIGHTMARE_A_END; i++)
						GenerateMob(i, 0, 0);

					sprintf(temp, "etc,nigthmare_arcan started");
					Log(temp, "-system", 0);
				}

				if (GetUserInArea(1024, 256, 1152, 384, temp) > 0 && (when.tm_min == 9 && when.tm_sec == 0 || when.tm_min == 29 && when.tm_sec == 0 || when.tm_min == 49 && when.tm_sec == 0))
				{
					MSG_STANDARDPARM sm;
					memset(&sm, 0, sizeof(MSG_STANDARDPARM));

					sm.Type = _MSG_StartTime;
					sm.ID = ESCENE_FIELD;
					sm.Size = sizeof(MSG_STANDARDPARM);
					sm.Parm = 900;

					MapaMulticast(8, 2, (MSG_STANDARD*)&sm, 0);//Pesa M

					for (int i = NIGHTMARE_M_INITIAL; i <= NIGHTMARE_M_END; i++)
						GenerateMob(i, 0, 0);

					sprintf(temp, "etc,nigthmare_mistycal started");
					Log(temp, "-system", 0);
				}

				if (GetUserInArea(1280, 256, 1408, 384, temp) > 0 && (when.tm_min == 24 && when.tm_sec == 0 || when.tm_min == 44 && when.tm_sec == 0 || when.tm_min == 4 && when.tm_sec == 0))
				{
					MSG_STANDARDPARM sm;
					memset(&sm, 0, sizeof(MSG_STANDARDPARM));

					sm.Type = _MSG_StartTime;
					sm.ID = ESCENE_FIELD;
					sm.Size = sizeof(MSG_STANDARDPARM);
					sm.Parm = 900;

					MapaMulticast(10, 2, (MSG_STANDARD*)&sm, 0);

					//Pesa N
					for (int i = NIGHTMARE_N_INITIAL; i <= NIGHTMARE_N_END; i++)
						GenerateMob(i, 0, 0);

					sprintf(temp, "etc,nigthmare_normal started");
					Log(temp, "-system", 0);
				}
#pragma endregion
#pragma region >> Pesadelo Reset
		if ((when.tm_min == 9 || when.tm_min == 29 || when.tm_min == 49) && when.tm_sec == 0)
		{
			DeleteMobMapa(9, 1);
			ClearMapa(9, 1);//Pesa A
			PartyPesa[2] = 0;

			sprintf(temp, "etc,nightmare_arcan clear -%d:%d", when.tm_hour, when.tm_min);
			Log(temp, "-system", 0);
		}
		if ((when.tm_min == 4 || when.tm_min == 24 || when.tm_min == 44) && when.tm_sec == 0)
		{
			DeleteMobMapa(8, 2);
			ClearMapa(8, 2);//Pesa M
			PartyPesa[1] = 0;

			sprintf(temp, "etc,nightmare_mystic clear -%d:%d", when.tm_hour, when.tm_min);
			Log(temp, "-system", 0);
		}

		if ((when.tm_min == 19 || when.tm_min == 39 || when.tm_min == 59) && when.tm_sec == 0)
		{
			DeleteMobMapa(10, 2);
			ClearMapa(10, 2);//Pesa N
			PartyPesa[0] = 0;

			sprintf(temp, "etc,nightmare_normal clear -%d:%d", when.tm_hour, when.tm_min);
			Log(temp, "-system", 0);
		}
#pragma endregion
#pragma region >> Calabouço start / reset
		if ((when.tm_min == 00 ) && when.tm_sec == 0)
		{
			for (int t = 0; t < 3; t++)
			{
				if (g_calabouco.Party[t].LeaderID == 0 || strcmp(pMob[g_calabouco.Party[t].LeaderID].MOB.MobName, g_calabouco.Party[t].LeaderName) != 0)
					continue;

				if (pMob[g_calabouco.Party[t].LeaderID].Leader != -1 && pMob[g_calabouco.Party[t].LeaderID].Leader)
					continue;
				//srand(time(NULL));
				DoTeleport(g_calabouco.Party[t].LeaderID, 1712 - rand() % 4, 2080 + rand() % 10);
				SendClientMsg(g_calabouco.Party[t].LeaderID, "Você entrou no [ Calabouço Zumbi ].");

				for (int i = 0; i < MAX_PARTY; i++)
				{
					int partyconn = pMob[g_calabouco.Party[t].LeaderID].PartyList[i];

					if (partyconn < 6)
						continue;

					//srand(time(NULL));
					if (partyconn > 0 && partyconn < MAX_USER && partyconn != g_calabouco.Party[t].LeaderID && pUser[partyconn].Mode == USER_PLAY)
						DoTeleport(partyconn, 1712 - rand() % 4, 2080 + rand() % 10);

					SendClientMsg(partyconn, "Você entrou no [ Calabouço Zumbi ].");

				}
			}

			MSG_STANDARDPARM sm;
			memset(&sm, 0, sizeof(MSG_STANDARDPARM));

			sm.Type = _MSG_StartTime;
			sm.ID = ESCENE_FIELD;
			sm.Size = sizeof(MSG_STANDARDPARM);
			sm.Parm = 1800;

			MapaMulticast(13, 16, (MSG_STANDARD*)&sm, 0);

			for (int i = 4566; i <= 4618; i++)
			{
				GenerateMob(i, 0, 0);
				g_calabouco.Left++;
			}
				
		}

		if ((when.tm_min == 29) && when.tm_sec == 59) // Reset
		{
			ClearMapa(13, 16);
			DeleteMobMapa(13, 16);

			for (int z = 0; z < 3; z++)
			{
				g_calabouco.Party[z].LeaderID = 0;
				strncpy(g_calabouco.Party[z].LeaderName, " ", NAME_LENGTH);
			}
		}
#pragma endregion
#pragma region >> Pista de runas start
		if ((when.tm_min == 20 || when.tm_min == 40 || when.tm_min == 00) && when.tm_sec == 0)
		{//Pista de Runas entrada

			Pista[4].Party[0].MobCount = 1;
			Pista[4].Party[1].MobCount = 1;
			Pista[4].Party[2].MobCount = 1;

			Pista[6].Party[0].MobCount = 100;

			for(int s = 0; s < 7; s++)
			{
				for(int t = 0; t < 3; t++)
				{
					if(Pista[s].Party[t].LeaderID == 0 || strcmp(pMob[Pista[s].Party[t].LeaderID].MOB.MobName, Pista[s].Party[t].LeaderName) != 0)
						continue;

					if((pMob[Pista[s].Party[t].LeaderID].TargetX/128) != 25 || (pMob[Pista[s].Party[t].LeaderID].TargetY/128) != 13)
						continue;

					if (pMob[Pista[s].Party[t].LeaderID].Leader != -1 && pMob[Pista[s].Party[t].LeaderID].Leader)
						continue;

					DoTeleport(Pista[s].Party[t].LeaderID, PistaPos[Pista[s].Party[t].Sala][t][0], PistaPos[Pista[s].Party[t].Sala][t][1]);

					for (int i = 0; i < MAX_PARTY; i++)
					{
						int partyconn = pMob[Pista[s].Party[t].LeaderID].PartyList[i];

						if (partyconn > 0 && partyconn < MAX_USER && partyconn != Pista[s].Party[t].LeaderID && pUser[partyconn].Mode == USER_PLAY)
							if((pMob[partyconn].TargetX/128) == 25 && (pMob[partyconn].TargetY/128) == 13)
								DoTeleport(partyconn, PistaPos[Pista[s].Party[t].Sala][t][0], PistaPos[Pista[s].Party[t].Sala][t][1]);		
					}

					//Pista+0 Lich
					if(s == 0 && t == 0) GenerateMob(RUNEQUEST_LV0_LICH2, 0, 0);

					if(s == 0 && t == 1) GenerateMob(RUNEQUEST_LV0_LICH1, 0, 0);

					//Pista +1 Torre
					if(s == 1)
					{
						GenerateMob(RUNEQUEST_LV1_TORRE1, 3358, 1582);
						GenerateMob(RUNEQUEST_LV1_TORRE2, 3386, 1548);
						GenerateMob(RUNEQUEST_LV1_TORRE3, 3418, 1582);

						for(int generateindex = RUNEQUEST_LV1_MOB_INITIAL; generateindex <= RUNEQUEST_LV1_MOB_END; generateindex++)
							GenerateMob(generateindex, 0, 0);
					}
				

					if(s == 2)
						GenerateMob(RUNEQUEST_LV2_MOB_BOSS, 0, 0);

					//srand(time(NULL));

					if(s == 4)
						Pista[s].Party[t].MobCount = 8 + rand() % 8;

					if(s == 4 && t == 0)
					{
						for(int generateindex = RUNEQUEST_LV4_MOB_INITIAL; generateindex <= RUNEQUEST_LV4_MOB_END; generateindex++)
							GenerateMob(generateindex, 0, 0);
					}
				}
			}
		}
#pragma endregion
#pragma region >> Pista de runas reset
		if ((when.tm_min == 15 || when.tm_min == 35 || when.tm_min == 55) && when.tm_sec == 0)
		{//Pista de Runas saida

			for (int c = MAX_USER; c < MAX_MOB; c++)
			{
				if (pMob[c].Mode == USER_EMPTY)
					continue;

				if ((pMob[c].TargetX / 128) != 27 || (pMob[c].TargetY / 128) != 11)
					continue;

				if (pMob[c].TargetX < 3310 || pMob[c].TargetX > 3588 || pMob[c].TargetY < 1005 || pMob[c].TargetY > 1663)
					continue;

				DeleteMob(c, 3);
			}

			for (int x = 0; x < MAX_USER; x++)
			{
				if (pUser[x].Mode != USER_PLAY)
					continue;

				if (pMob[x].Mode == USER_EMPTY)
					continue;

				if (pMob[x].TargetX < 3310 || pMob[x].TargetX > 3588 || pMob[x].TargetY < 1005 || pMob[x].TargetY > 1663)
					continue;

				if (pMob[x].MOB.CurrentScore.Hp <= 0)
				{
					pMob[x].MOB.CurrentScore.Hp = 1;

					SendScore(x);
				}

				//srand(time(NULL));
				DoTeleport(x, 3294, rand() % 1 == 0 ? 1701 : 1686);
			}

			//Pista +1 - Torre

			//Grupo 1 ganhou
			if (Pista[1].Party[0].MobCount > Pista[1].Party[1].MobCount && Pista[1].Party[0].MobCount > Pista[1].Party[2].MobCount)
			{
				if (Pista[1].Party[0].LeaderID != 0 && strcmp(pMob[Pista[1].Party[0].LeaderID].MOB.MobName, Pista[1].Party[0].LeaderName) == 0)
				{			
						STRUCT_ITEM Runa;
						memset(&Runa, 0, sizeof(STRUCT_ITEM));

						//srand(time(NULL));

							Runa.sIndex = PistaRune[1][rand() % 5];

							if (Pista[1].Party[0].LeaderID > 0 && Pista[1].Party[0].LeaderID < MAX_USER)
								PutItem(Pista[1].Party[0].LeaderID, &Runa);
						
						for (int i = 0; i < MAX_PARTY; i++)
						{
							int partymember = pMob[Pista[1].Party[0].LeaderID].PartyList[i];

							if (partymember >= MAX_USER)
								continue;

								if (pUser[partymember].Mode != USER_PLAY)
									continue;

								//srand(time(NULL));
								Runa.sIndex = PistaRune[1][rand() % 5];
								PutItem(partymember, &Runa);
							}
						
						STRUCT_ITEM Prize;
						memset(&Prize, 0, sizeof(STRUCT_ITEM));

						Prize.sIndex = 5134;
						Prize.stEffect[0].cEffect = 43;
						Prize.stEffect[0].cValue = 2;

						PutItem(Pista[1].Party[0].LeaderID, &Prize);

						sprintf(temp, "etc,questRune complete +1 party1");
						Log(temp, "-system", 0);
					}
				}

			//Grupo 2 ganhou
			else if(Pista[1].Party[1].MobCount > Pista[1].Party[0].MobCount && Pista[1].Party[1].MobCount > Pista[1].Party[2].MobCount)
			{
				if(Pista[1].Party[1].LeaderID != 0 && strcmp(pMob[Pista[1].Party[1].LeaderID].MOB.MobName, Pista[1].Party[1].LeaderName) == 0)
				{
					STRUCT_ITEM Runa;
					memset(&Runa, 0, sizeof(STRUCT_ITEM));

						//srand(time(NULL));
						Runa.sIndex = PistaRune[1][rand() % 5];

						if (Pista[1].Party[1].LeaderID > 0 && Pista[1].Party[1].LeaderID < MAX_USER)
							PutItem(Pista[1].Party[1].LeaderID, &Runa);
					
						for (int i = 0; i < MAX_PARTY; i++)
						{
							int partymember = pMob[Pista[1].Party[1].LeaderID].PartyList[i];

							if (partymember >= MAX_USER)
								continue;

							if (pUser[partymember].Mode != USER_PLAY)
								continue;

							//srand(time(NULL));
							Runa.sIndex = PistaRune[1][rand() % 5];
							PutItem(partymember, &Runa);
						}
					

					STRUCT_ITEM Prize;
					memset(&Prize, 0, sizeof(STRUCT_ITEM));

					Prize.sIndex = 5134;
					Prize.stEffect[0].cEffect = 43;
					Prize.stEffect[0].cValue = 2;

					PutItem(Pista[1].Party[1].LeaderID, &Prize);

					sprintf(temp, "etc,questRune complete +1 party2");
					Log(temp, "-system", 0);
				}
			}

			//Grupo 3 ganhou
			else if(Pista[1].Party[2].MobCount > Pista[1].Party[0].MobCount && Pista[1].Party[2].MobCount > Pista[1].Party[1].MobCount)
			{
				if(Pista[1].Party[2].LeaderID != 0 && strcmp(pMob[Pista[1].Party[2].LeaderID].MOB.MobName, Pista[1].Party[2].LeaderName) == 0)
				{
					STRUCT_ITEM Runa;
					memset(&Runa, 0, sizeof(STRUCT_ITEM));

						//srand(time(NULL));
						Runa.sIndex = PistaRune[1][rand() % 5];

						if (Pista[1].Party[2].LeaderID > 0 && Pista[1].Party[2].LeaderID < MAX_USER)
							PutItem(Pista[1].Party[0].LeaderID, &Runa);
					

					for (int i = 0; i < MAX_PARTY; i++)
					{
						int partymember = pMob[Pista[1].Party[2].LeaderID].PartyList[i];

						if (partymember >= MAX_USER)
							continue;

						
							if (pUser[partymember].Mode != USER_PLAY)
								continue;

							//srand(time(NULL));
							Runa.sIndex = PistaRune[1][rand() % 5];
							PutItem(partymember, &Runa);
						}
					

					STRUCT_ITEM Prize;
					memset(&Prize, 0, sizeof(STRUCT_ITEM));

					Prize.sIndex = 5134;
					Prize.stEffect[0].cEffect = 43;
					Prize.stEffect[0].cValue = 2;

					PutItem(Pista[1].Party[2].LeaderID, &Prize);

					sprintf(temp, "etc,questRune complete +1 party3");
					Log(temp, "-system", 0);
				}
			}

			//Pista +3 - Sulrang

			//Grupo 1 ganhou
			if(Pista[3].Party[0].MobCount > Pista[3].Party[1].MobCount && Pista[3].Party[0].MobCount > Pista[3].Party[2].MobCount)
			{
				if(Pista[3].Party[0].LeaderID != 0 && strcmp(pMob[Pista[3].Party[0].LeaderID].MOB.MobName, Pista[3].Party[0].LeaderName) == 0)
				{
					STRUCT_ITEM Runa;
					memset(&Runa, 0, sizeof(STRUCT_ITEM));

						//srand(time(NULL));
						Runa.sIndex = PistaRune[3][rand() % 5];

						if (Pista[3].Party[0].LeaderID > 0 && Pista[3].Party[0].LeaderID < MAX_USER)
							PutItem(Pista[3].Party[0].LeaderID, &Runa);
					

					for (int i = 0; i < MAX_PARTY; i++)
					{
						int partymember = pMob[Pista[3].Party[0].LeaderID].PartyList[i];

						if (partymember >= MAX_USER)
							continue;

							if (pUser[partymember].Mode != USER_PLAY)
								continue;

							//srand(time(NULL));
							Runa.sIndex = PistaRune[3][rand() % 5];
							PutItem(partymember, &Runa);
						}
					

					STRUCT_ITEM Prize;
					memset(&Prize, 0, sizeof(STRUCT_ITEM));

					Prize.sIndex = 5134;
					Prize.stEffect[0].cEffect = 43;
					Prize.stEffect[0].cValue = 4;

					PutItem(Pista[3].Party[0].LeaderID, &Prize);

					sprintf(temp, "etc,questRune complete +3 party1");
					Log(temp, "-system", 0);
				}
			}

			//Grupo 2 ganhou
			else if(Pista[3].Party[1].MobCount > Pista[3].Party[0].MobCount && Pista[3].Party[1].MobCount > Pista[3].Party[2].MobCount)
			{
				if(Pista[3].Party[1].LeaderID != 0 && strcmp(pMob[Pista[3].Party[1].LeaderID].MOB.MobName, Pista[3].Party[1].LeaderName) == 0)
				{
					STRUCT_ITEM Runa;
					memset(&Runa, 0, sizeof(STRUCT_ITEM));

						//srand(time(NULL));
						Runa.sIndex = PistaRune[3][rand() % 5];

						if (Pista[3].Party[1].LeaderID > 0 && Pista[3].Party[1].LeaderID < MAX_USER)
					
					for (int i = 0; i < MAX_PARTY; i++)
					{
						int partymember = pMob[Pista[3].Party[1].LeaderID].PartyList[i];

						if (partymember >= MAX_USER)
							continue;

							if (pUser[partymember].Mode != USER_PLAY)
								continue;

							//srand(time(NULL));
							Runa.sIndex = PistaRune[3][rand() % 5];
							PutItem(partymember, &Runa);
						}
					
					STRUCT_ITEM Prize;
					memset(&Prize, 0, sizeof(STRUCT_ITEM));

					Prize.sIndex = 5134;
					Prize.stEffect[0].cEffect = 43;
					Prize.stEffect[0].cValue = 4;

					PutItem(Pista[3].Party[3].LeaderID, &Prize);

					sprintf(temp, "etc,questRune complete +3 party2");
					Log(temp, "-system", 0);
				}
			}

			//Grupo 3 ganhou
			else if(Pista[3].Party[2].MobCount > Pista[3].Party[0].MobCount && Pista[3].Party[2].MobCount > Pista[3].Party[1].MobCount)
			{
				if(Pista[3].Party[2].LeaderID != 0 && strcmp(pMob[Pista[3].Party[2].LeaderID].MOB.MobName, Pista[3].Party[2].LeaderName) == 0)
				{
					STRUCT_ITEM Runa;
					memset(&Runa, 0, sizeof(STRUCT_ITEM));
					
						//srand(time(NULL));
						Runa.sIndex = PistaRune[3][rand() % 5];

						if (Pista[3].Party[2].LeaderID > 0 && Pista[3].Party[2].LeaderID < MAX_USER)
							PutItem(Pista[3].Party[2].LeaderID, &Runa);
					
					for (int i = 0; i < MAX_PARTY; i++)
					{
						int partymember = pMob[Pista[3].Party[2].LeaderID].PartyList[i];

						if (partymember >= MAX_USER)
							continue;

							if (pUser[partymember].Mode != USER_PLAY)
								continue;

							//srand(time(NULL));
							Runa.sIndex = PistaRune[3][rand() % 5];
							PutItem(partymember, &Runa);
						}
					
					STRUCT_ITEM Prize;
					memset(&Prize, 0, sizeof(STRUCT_ITEM));

					Prize.sIndex = 5134;
					Prize.stEffect[0].cEffect = 43;
					Prize.stEffect[0].cValue = 4;

					PutItem(Pista[3].Party[2].LeaderID, &Prize);

					sprintf(temp, "etc,questRune complete +3 party3");
					Log(temp, "-system", 0);
				}
			}

			for(int x = 0;x < 7; x++)
			{
				for(int z = 0; z < 3;z ++)
				{
					Pista[x].Party[z].LeaderID = 0;
					strncpy(Pista[x].Party[z].LeaderName, " ", 16);
					Pista[x].Party[z].MobCount = 0;
					Pista[x].Party[z].Sala = 0;
				}
			}

		}
#pragma endregion
#pragma region Coliseu N - No PvP
		if (nColiseu[0].Days[when.tm_wday])
		{


			if ((when.tm_hour == nColiseu[0].Hour[0] - 1 || when.tm_hour == nColiseu[0].Hour[1] - 1) && when.tm_min >= 55 && !g_quests.Annoucement)
			{
				SendNotice("!O Coliseu {N} iniciará em 5 minutos. Acesse pelo NPC Xamã.");

				g_quests.Annoucement = 1;
			}

			if ((when.tm_min == 10) && when.tm_sec == 0) // Reset Coliseu N
			{
				ClearMapa(27, 11);
			}
		}
#pragma endregion

	}

	if((SecCounter % 2) == 0)
		ProcessDecayItem();

	int UsersDie = 0;

	int Sec4 = SecCounter % 4;

	if (SecCounter % 4 == 0)
	{
		ProcessRanking();

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (WaterClear1[i][j] > 1)
					WaterClear1[i][j]--;

				else if (WaterClear1[i][j] == 1 && j <= 7)
				{
					ClearAreaTeleport(WaterScrollPosition[i][j][0] - 8, WaterScrollPosition[i][j][1] - 8, WaterScrollPosition[i][j][0] + 8, WaterScrollPosition[i][j][1] + 8, 1965, 1769);
					WaterClear1[i][j] = 0;
				}
				else if (WaterClear1[i][j] == 1 && j > 7)
				{
					ClearAreaTeleport(WaterScrollPosition[i][j][0] - 12, WaterScrollPosition[i][j][1] - 12, WaterScrollPosition[i][j][0] + 12, WaterScrollPosition[i][j][1] + 12, 1965, 1769);
					WaterClear1[i][j] = 0;
				}
			}
		}

#pragma region >> Limpa a zona da Carta de Duelo
		if (CartaTime > 1) CartaTime--;

		if (CartaTime == 1)
		{
			CartaTime = 60;

			if (CartaSala == 1)
				ClearAreaTeleport(778, 3652, 832, 3698, CartaPos[1][0], CartaPos[1][1]);

			else if (CartaSala == 2)
				ClearAreaTeleport(836, 3652, 890, 3698, CartaPos[2][0], CartaPos[2][1]);

			else if (CartaSala == 3)
				ClearAreaTeleport(834, 3595, 889, 3645, CartaPos[3][0], CartaPos[3][1]);


			if (CartaSala == 4)
			{
				ClearArea(776, 3595, 834, 3648);
				CartaTime = 0;
				CartaSala = 0;

				sprintf(temp, "etc,clear secretroom");
				Log(temp, "-system", 0);
			}

			else
				CartaSala++;

			MSG_STANDARDPARM sm;

			sm.Type = _MSG_StartTime;
			sm.ID = ESCENE_FIELD;
			sm.Size = sizeof(MSG_STANDARDPARM);
			sm.Parm = CartaTime * 2;

			MapaMulticast(6, 28, (MSG_STANDARD*)&sm, 0);
		}
#pragma endregion

	}

#pragma region >> Quest Castle Zakum
	CCastleZakum::ProcessSecTimer();
#pragma endregion


	int Sec16 = SecCounter % 16;


	int i = 0;
	
	for (i = 1; i < MAX_USER; i++)
	{
		if (i % 32 == Sec32 && pUser[i].Mode && pUser[i].Mode != USER_SAVING4QUIT)
			CheckIdle(i);

#pragma region >> Regeneração de HP e MP (poções)
		if (pUser[i].Mode == USER_PLAY && pMob[i].MOB.CurrentScore.Hp > 0)
		{
			pUser[i].Unk_2688 = 0;

			int retHp = ApplyHp(i);
			int retMp = ApplyMp(i);

			if (retHp != 0)
				SendScore(i);

			else if (retMp != 0)
				SendSetHpMp(i);
		}
#pragma endregion

		if (SecCounter % 2 == 0 && pMob[i].MOB.CurrentScore.Hp <= 0 && pMob[i].TargetX == 1046 && pMob[i].TargetY == 1690)
		{
			pMob[i].DetectDeadOnCastle++;
		//	SendClientSignalParmCoord(i, ESCENE_FIELD, _MSG_StartTime, pMob[i].DetectDeadOnCastle, 1046, 1690, 1046, 1690);
			if (pMob[i].DetectDeadOnCastle > 10)
			{
				DoRecall(i);
			}
		}
		else
			pMob[i].DetectDeadOnCastle = 0;
	

		if (i % 16 == Sec16 &&  pUser[i].Mode == USER_PLAY)
		{

			if (pMob[i].TargetX != 1046 && pMob[i].TargetY != 1690)
			{
				pMob[i].DetectDeadOnCastle = 0;
			}

			if (pMob[i].MOB.CurrentScore.Hp > 0)
			{
				RegenMob(i);
				ProcessAffect(i);
				UsersDie++;
			}
			else
			{
				if (pMob[i].TargetX == 1046 && pMob[i].TargetY == 1690)
				{
					if (pMob[i].MOB.CurrentScore.Hp <= 0)
					{
						pMob[i].DetectDeadOnCastle++;

						//SendClientSignalParmCoord(i, ESCENE_FIELD, _MSG_StartTime, pMob[i].DetectDeadOnCastle, 1046, 1690, 1046, 1690);

						if (pMob[i].DetectDeadOnCastle > 1)
						{
							DoRecall(i);
						}
					}
					else
					{
						pMob[i].DetectDeadOnCastle = 0;
					}
				}
			}
		}

#pragma region >> Verifica o estado de Quest do jogador
		//Coveiro
		if (pMob[i].QuestFlag != 1 && pMob[i].TargetX > 2379 && pMob[i].TargetY > 2076 && pMob[i].TargetX < 2426 && pMob[i].TargetY < 2133 && pMob[i].MOB.BaseScore.Level < 1000)
			DoRecall(i);

		//Jardin
		if (pMob[i].QuestFlag != 2 && pMob[i].TargetX > 2228 && pMob[i].TargetY > 1700 && pMob[i].TargetX < 2257 && pMob[i].TargetY < 1728 && pMob[i].MOB.BaseScore.Level < 1000)
			DoRecall(i);

		//Kaizen
		if (pMob[i].QuestFlag != 3 && pMob[i].TargetX > 459 && pMob[i].TargetY > 3887 && pMob[i].TargetX < 497 && pMob[i].TargetY < 3916 && pMob[i].MOB.BaseScore.Level < 1000)
			DoRecall(i);

		//Hidra
		if (pMob[i].QuestFlag != 4 && pMob[i].TargetX > 658 && pMob[i].TargetY > 3728 && pMob[i].TargetX < 703 && pMob[i].TargetY < 3762 && pMob[i].MOB.BaseScore.Level < 1000)
			DoRecall(i);

		//Elfos
		if (pMob[i].QuestFlag != 5 && pMob[i].TargetX > 1312 && pMob[i].TargetY > 4027 && pMob[i].TargetX < 1348 && pMob[i].TargetY < 4055 && pMob[i].MOB.BaseScore.Level < 1000)
			DoRecall(i);
#pragma endregion

	}

	if (BrState == 2 && i % 8 == Sec16 && BRItem > 0)
	{
		if (BrMod < 9)
		{
			if (BrMod >= 7)
			{
				SendDamage(2608, 1708, 2622, 1711);
				SendDamage(2608, 1739, 2622, 1743);
				SendEnvEffect(2608, 1708, 2622, 1711, 32, 0);
				SendEnvEffect(2608, 1739, 2622, 1743, 32, 0);
			}
		}
		else
		{
			SendDamage(2608, 1708, 2622, 1718);
			SendDamage(2608, 1733, 2622, 1743);
			SendEnvEffect(2608, 1708, 2622, 1718, 32, 0);
			SendEnvEffect(2608, 1733, 2622, 1743, 32, 0);
		}
	}


	if(SecCounter % 6 == 0)
	{
		SendEnvEffectKingdom(1050, 2108, 1070, 2146, 32, 0, REINO_BLUE);
		SendEnvEffectKingdom(1066, 2133, 1098, 2146, 32, 0, REINO_BLUE);
		SendDamageKingdom(1050, 2108, 1070, 2146, REINO_BLUE);
		SendDamageKingdom(1066, 2133, 1098, 2146, REINO_BLUE);

		SendEnvEffectKingdom(1230, 1947, 1245, 1988, 32, 0, REINO_RED);
		SendEnvEffectKingdom(1204, 1948, 1231, 1962, 32, 0, REINO_RED);
		SendDamageKingdom(1230, 1947, 1245, 1988, REINO_RED);
		SendDamageKingdom(1204, 1948, 1231, 1962, REINO_RED);
	}

	if(SecCounter % 5 == 0)
	{
		SendEnvEffectLeader(3436, 1285, 3450, 1299, 32, 0);
		SendDamageLeader(3436, 1285, 3450, 1299);
		SendEnvEffectLeader(3368, 1285, 3382, 1299, 32, 0);
		SendDamageLeader(3368, 1285, 3382, 1299);
		SendEnvEffectLeader(3384, 1302, 3398, 1316, 32, 0);
		SendDamageLeader(3384, 1302, 3398, 1316);
		SendEnvEffectLeader(3438, 1320, 3452, 1334, 32, 0);
		SendDamageLeader(3438, 1320, 3452, 1334);
		SendEnvEffectLeader(3369, 1320, 3383, 1334, 32, 0);
		SendDamageLeader(3369, 1320, 3383, 1334);
		SendEnvEffectLeader(3385, 1336, 3399, 1350, 32, 0);
		SendDamageLeader(3385, 1336, 3399, 1350);
		SendEnvEffectLeader(3402, 1353, 3416, 1367, 32, 0);
		SendDamageLeader(3402, 1353, 3416, 1367);
		SendEnvEffectLeader(3436, 1371, 3450, 1385, 32, 0);
		SendDamageLeader(3436, 1371, 3450, 1385);
		SendEnvEffectLeader(3368, 1371, 3382, 1385, 32, 0);
		SendDamageLeader(3368, 1371, 3382, 1385);
		SendEnvEffectLeader(3402, 1387, 3416, 1401, 32, 0);
		SendDamageLeader(3402, 1387, 3416, 1401);
		SendEnvEffectLeader(3420, 1286, 3434, 1300, 32, 0);
		SendDamageLeader(3420, 1286, 3434, 1300);
		SendEnvEffectLeader(3351, 1286, 3365, 1300, 32, 0);
		SendDamageLeader(3351, 1286, 3365, 1300);
		SendEnvEffectLeader(3402, 1302, 3416, 1316, 32, 0);
		SendDamageLeader(3402, 1302, 3416, 1316);
		SendEnvEffectLeader(3420, 1320, 3434, 1334, 32, 0);
		SendDamageLeader(3420, 1320, 3434, 1334);
		SendEnvEffectLeader(3371, 1337, 3385, 1351, 32, 0);
		SendDamageLeader(3371, 1337, 3385, 1351);
		SendEnvEffectLeader(3436, 1337, 3450, 1351, 32, 0);
		SendDamageLeader(3436, 1337, 3450, 1351);
		SendEnvEffectLeader(3385, 1353, 3399, 1367, 32, 0);
		SendDamageLeader(3385, 1353, 3399, 1367);
		SendEnvEffectLeader(3352, 1370, 3366, 1384, 32, 0);
		SendDamageLeader(3352, 1370, 3366, 1384);
		SendEnvEffectLeader(3419, 1370, 3433, 1384, 32, 0);
		SendDamageLeader(3419, 1370, 3433, 1384);
		SendEnvEffectLeader(3385, 1387, 3399, 1401, 32, 0);
		SendDamageLeader(3385, 1387, 3399, 1401);
		SendEnvEffectLeader(3402, 1286, 3416, 1300, 32, 0);
		SendDamageLeader(3402, 1286, 3416, 1300);
		SendEnvEffectLeader(3352, 1302, 3366, 1316, 32, 0);
		SendDamageLeader(3352, 1302, 3366, 1316);
		SendEnvEffectLeader(3420, 1302, 3434, 1316, 32, 0);
		SendDamageLeader(3420, 1302, 3434, 1316);
		SendEnvEffectLeader(3401, 1320, 3415, 1334, 32, 0);
		SendDamageLeader(3401, 1320, 3415, 1334);
		SendEnvEffectLeader(3420, 1336, 3434, 1350, 32, 0);
		SendDamageLeader(3420, 1336, 3434, 1350);
		SendEnvEffectLeader(3436, 1353, 3450, 1367, 32, 0);
		SendDamageLeader(3436, 1353, 3450, 1367);
		SendEnvEffectLeader(3368, 1353, 3382, 1367, 32, 0);
		SendDamageLeader(3368, 1353, 3382, 1367);
		SendEnvEffectLeader(3401, 1370, 3415, 1384, 32, 0);
		SendDamageLeader(3401, 1370, 3415, 1384);
		SendEnvEffectLeader(3435, 1387, 3449, 1401, 32, 0);
		SendDamageLeader(3435, 1387, 3449, 1401);
		SendEnvEffectLeader(3369, 1387, 3383, 1401, 32, 0);
		SendDamageLeader(3369, 1387, 3383, 1401);
		SendEnvEffectLeader(3387, 1285, 3401, 1299, 32, 0);
		SendDamageLeader(3387, 1285, 3401, 1299);
		SendEnvEffectLeader(3368, 1302, 3382, 1316, 32, 0);
		SendDamageLeader(3368, 1302, 3382, 1316);
		SendEnvEffectLeader(3436, 1302, 3450, 1316, 32, 0);
		SendDamageLeader(3436, 1302, 3450, 1316);
		SendEnvEffectLeader(3384, 1319, 3398, 1333, 32, 0);
		SendDamageLeader(3384, 1319, 3398, 1333);
		SendEnvEffectLeader(3402, 1335, 3416, 1349, 32, 0);
		SendDamageLeader(3402, 1335, 3416, 1349);
		SendEnvEffectLeader(3419, 1353, 3433, 1367, 32, 0);
		SendDamageLeader(3419, 1353, 3433, 1367);
		SendEnvEffectLeader(3352, 1353, 3366, 1367, 32, 0);
		SendDamageLeader(3352, 1353, 3366, 1367);
		SendEnvEffectLeader(3385, 1370, 3399, 1384, 32, 0);
		SendDamageLeader(3385, 1370, 3399, 1384);
		SendEnvEffectLeader(3419, 1387, 3433, 1401, 32, 0);
		SendDamageLeader(3419, 1387, 3433, 1401);
		SendEnvEffectLeader(3352, 1387, 3366, 1401, 32, 0);
		SendDamageLeader(3352, 1387, 3366, 1401);
		SendEnvEffectLeader(3335, 1286, 3349, 1300, 32, 0);
		SendDamageLeader(3335, 1286, 3349, 1300);
		SendEnvEffectLeader(3335, 1302, 3349, 1316, 32, 0);
		SendDamageLeader(3335, 1302, 3349, 1316);
		SendEnvEffectLeader(3335, 1354, 3349, 1368, 32, 0);
		SendDamageLeader(3335, 1354, 3349, 1368);
		SendEnvEffectLeader(3335, 1371, 3349, 1385, 32, 0);
		SendDamageLeader(3335, 1371, 3349, 1385);
	}

	for (int k = 0; k < MAX_MOB_MERC; k++)
	{
		if (pMobMerc[k].RenewTime == 0 || pMobMerc[k].RebornTime == 0 || pMobMerc[k].GenerateIndex == 0)
			continue;

		if (SecCounter % pMobMerc[k].RenewTime == 0)
			memcpy(pMobMerc[k].Stock, pMobMerc[k].MaxStock, sizeof(pMobMerc[k].Stock));

		if (SecCounter % pMobMerc[k].RebornTime == 0)
			GenerateMob(pMobMerc[k].GenerateIndex, 0, 0);
	}

	// CEncampment::ProcessSecTimer();

	int Sec6 = SecCounter % 6;

#pragma region Movimento / fala dos NPCS 
	int initial = Sec6 + MAX_USER;
	for (int index = initial; index < MAX_MOB; index += 6)
	{
		int Mode = pMob[index].Mode;
		int Clan = pMob[index].MOB.Clan;

		if (Mode)
		{
			if (Mode == MOB_IDLE)
			{
				if (pMob[index].MOB.CurrentScore.Hp <= 0)
				{
					Log("err,standingby processer delete hp zero mob", "-system", 0);
					DeleteMob(index, 1);
					continue;
				}

				ProcessAffect(index);

				int nX = pMob[index].TargetX;
				int nY = pMob[index].TargetY;
			}

			if (Mode == MOB_PEACE)
			{
				int chp = pMob[index].MOB.CurrentScore.Hp;
				if (chp <= 0)
				{
					Log("err,standingby processer delete hp zero mob", "-system", 0);
					DeleteMob(index, 1);
					continue;
				}

				ProcessAffect(index);

				if(pMob[index].GenerateIndex != RUNEQUEST_LV6_MOB_BOSS && pMob[index].TargetX >= 3423 && pMob[index].TargetX <= 3442 && pMob[index].TargetY >= 1492 && pMob[index].TargetY <= 1511)
				{
					if(pMob[index].GenerateIndex >= RUNEQUEST_LV6_MOB_INITIAL2 && pMob[index].GenerateIndex <= RUNEQUEST_LV6_MOB_END2)
					{
						if(Pista[6].Party[0].MobCount < 100 && Pista[6].Party[0].MobCount != 0)
							Pista[6].Party[0].MobCount++;
					}

					DeleteMob(index, 3);
					continue;
				}
				int Progress = pMob[index].SegmentProgress;

				if (Progress < 0 || Progress > MAX_SEGMENT)
				{
					pMob[index].SegmentProgress = 0;
					Progress = 0;
				}
				int Processor = pMob[index].StandingByProcessor();

				if (Processor & 0x10000000)
				{		
					int Target = Processor & 0xFFFFFFF;

					SetBattle(index, Processor & 0xFFFFFFF);

					int Leader = pMob[index].Leader;
					if (Leader <= 0)
						Leader = index;

					for (int l = 0; l < MAX_PARTY; ++l)
					{
						int party = pMob[Leader].PartyList[l];

						if (party > MAX_USER)
						{
							if (pMob[party].Mode && pMob[party].MOB.CurrentScore.Hp > 0)
								SetBattle(party, Target);

							else
							{
								if (pMob[party].Mode)
									DeleteMob(party, 1);

								pMob[Leader].PartyList[l] = 0;
							}
						}
					}

					if (Target < MAX_USER)
					{
						int leader = pMob[Target].Leader;

						if (leader <= 0)
							leader = Target;

						for (int n = 0; n < MAX_PARTY; n++)
						{
							int party = pMob[leader].PartyList[n];
							if (party > MAX_USER)
							{
								if (pMob[party].Mode && pMob[party].MOB.CurrentScore.Hp > 0)
									SetBattle(party, index);

								else
								{
									if (pMob[party].Mode)
										DeleteMob(party, 1);

									pMob[leader].PartyList[n] = 0;
								}
							}
						}
					}
				}
				else
				{
					if (Processor & 1)
					{
						MSG_Action sm;

						if (GetEmptyMobGrid(index, &pMob[index].NextX, &pMob[index].NextY) == FALSE)
							continue;

						GetAction(index, pMob[index].NextX, pMob[index].NextY, (MSG_Action*)&sm);

						if (pMob[index].NextX == pMob[index].TargetX && pMob[index].NextY == pMob[index].TargetY)
							continue;

						sm.Speed = BASE_GetSpeed(&pMob[index].MOB.CurrentScore);
						sm.Effect = 0;

						GridMulticast(index, pMob[index].NextX, pMob[index].NextY, (MSG_STANDARD*)&sm);

						int progres = pMob[index].SegmentProgress;

						if (Progress != progres)
						{
							if (progres >= 0 && progres < MAX_SEGMENT && pMob[index].GenerateIndex >= 0 && pMob[index].GenerateIndex < MAX_NPCGENERATOR && mNPCGen.pList[pMob[index].GenerateIndex].SegmentAction[Progress][0])
								SendSay(index, mNPCGen.pList[pMob[index].GenerateIndex].SegmentAction[Progress]);
						}

						if (pMob[index].GenerateIndex >= RUNEQUEST_LV2_MOB_INITIAL && pMob[index].GenerateIndex <= RUNEQUEST_LV2_MOB_END)
						{
							if (pMob[index].TargetX >= 3373 && pMob[index].TargetX <= 3407 && pMob[index].TargetY >= 1420 && pMob[index].TargetY <= 1453)
								DeleteMob(index, 3);
						}
					}
					if (Processor & 0x10)
					{
						int progres = pMob[index].SegmentProgress;

						if (Progress != progres)
						{
							if (progres >= 0 && progres < MAX_SEGMENT && pMob[index].GenerateIndex >= 0 && pMob[index].GenerateIndex < MAX_NPCGENERATOR && mNPCGen.pList[pMob[index].GenerateIndex].FleeAction[Progress][0])
								SendSay(index, mNPCGen.pList[pMob[index].GenerateIndex].FleeAction[Progress]);
						}
					}
					else
					{
						if (Processor & 0x100)
						{
							DeleteMob(index, 3);
							continue;
						}
						if (Processor & 0x1000)
						{
							pMob[index].GetRandomPos();

							if (pMob[index].NextX == pMob[index].TargetX && pMob[index].NextY == pMob[index].TargetY)
								continue;

							MSG_Action sm;

							if (GetEmptyMobGrid(index, &pMob[index].NextX, &pMob[index].NextY) == FALSE)
								continue;


							GetAction(index, pMob[index].NextX, pMob[index].NextY, (MSG_Action*)&sm);

							sm.Speed = BASE_GetSpeed(&pMob[index].MOB.CurrentScore);
							sm.Effect = 0;

							GridMulticast(index, pMob[index].NextX, pMob[index].NextY, (MSG_STANDARD*)&sm);
						}
						if (Processor & 2)
							DoTeleport(index, pMob[index].NextX, pMob[index].NextY);

						if (Processor & 0x10000)
						{
							if(pMob[index].GenerateIndex >= RUNEQUEST_LV6_MOB_INITIAL && pMob[index].GenerateIndex <= RUNEQUEST_LV6_MOB_END)
							{
								if(Pista[6].Party[0].MobCount < 100 && Pista[6].Party[0].MobCount != 0)
									Pista[6].Party[0].MobCount++;
							}

							DeleteMob(index, 3);
							continue;
						}
					}
				}
			}
		}
	}
#pragma endregion

	Sec4 = SecCounter % 4;

#pragma region Ataque / fala em ação dos mobs
	for (int index = Sec4 + MAX_USER; index < MAX_MOB; index += 4)
	{
		if (pMob[index].Mode != MOB_COMBAT)
			continue;

		int flag = 0;

		if (pMob[index].MOB.Clan == 4)
			flag = FALSE;

		if (pMob[index].MOB.CurrentScore.Hp <= 0)
		{
			pMob[index].MOB.CurrentScore.Hp = 0;
			
			sprintf(temp, "err, battleprocessor delete hp 0 idx:%d leader:%d fol0:%d fol1:%d", index, pMob[index].Leader, pMob[index].PartyList[0], pMob[index].PartyList[1]);
			Log(temp, "-system", NULL);
			
			DeleteMob(index, 1);
			continue;
		}

		if (index % 16 == Sec16)
			ProcessAffect(index);

		if(pMob[index].GenerateIndex != RUNEQUEST_LV6_MOB_BOSS && pMob[index].TargetX >= 3423 && pMob[index].TargetX <= 3442 && pMob[index].TargetY >= 1492 && pMob[index].TargetY <= 1511)
		{
			if(pMob[index].GenerateIndex >= RUNEQUEST_LV6_MOB_INITIAL2 && pMob[index].GenerateIndex <= RUNEQUEST_LV6_MOB_END2)
			{
				if(Pista[6].Party[0].MobCount < 100 && Pista[6].Party[0].MobCount != 0)
					Pista[6].Party[0].MobCount++;
			}

			DeleteMob(index, 3);
			continue;
		}

		int Target = pMob[index].CurrentTarget;

		if (Target > 0 && Target < MAX_MOB)
		{
			int leader = pMob[index].Leader;
			if (leader == MOB_EMPTY)
				leader = index;

			int targetLeader = pMob[Target].Leader;
			
			if (targetLeader == MOB_EMPTY)
				targetLeader = Target;

			int indexguild = pMob[index].MOB.Guild;
			if (pMob[index].GuildDisable)
				indexguild = 0;

			int targetguild = pMob[Target].MOB.Guild;
			if (pMob[Target].GuildDisable)
				targetguild = 0;

			if (indexguild == 0 && targetguild == 0)
				indexguild = -1;

			if (leader == targetLeader || indexguild == targetguild)
				pMob[index].RemoveEnemyList(Target);
		}
		
		int BattleMode = pMob[index].BattleProcessor();
		
		if (BattleMode & 0x20)
		{
			DeleteMob(index, 3);
			continue;
		}

		if (BattleMode & 0x1000)
		{
			if (Target <= MOB_EMPTY || Target >= MAX_MOB)
				continue;

			
			if (pMob[Target].MOB.CurrentScore.Hp <= 0)
				continue;

			MSG_AttackOne sm;

			int village = BASE_GetVillage(pMob[Target].TargetX, pMob[Target].TargetY);

			unsigned char mapatt = GetAttribute(pMob[Target].TargetX, pMob[Target].TargetY);

			
			GetAttack(index, Target, &sm);

			sm.FlagLocal = 0;

			int targetbackup = Target;

			Target = sm.Dam[0].TargetID;

			if (GetInHalf(Target, index) == 0)
			{
				continue;
			}

			int skill = sm.SkillIndex;

			//109 : Raio Vermelho
			//110 : Empurrão
			//111 : Chão de espinhos
			if(skill == 109 || skill == 110 || skill == 111)
				goto KefraAttackLabel;
			
			if (skill >= 0 && skill < MAX_SKILLINDEX && sm.SkillParm == 0)
			{
				if (skill == 33)
					sm.Motion = 253;

				int kind = ((skill % MAX_SKILL / 8) + 1);
				
				if (kind >= 1 && kind <= 3)
				{
					int special = pMob[index].MOB.CurrentScore.Special[kind];
					BOOL NeedUpdate = FALSE;
					
					if (SetAffect(Target, skill, 100, special))
						NeedUpdate = TRUE;

					if (SetTick(Target, skill, 100, special))
						NeedUpdate = TRUE;

					if (NeedUpdate == TRUE)
						SendScore(Target);
				}
			}

			if (Target < MAX_USER && sm.Dam[0].Damage > 0)
			{
				//srand(time(NULL));
				int Pop = rand() % 100 + 1;

				if (pMob[index].MOB.Clan == 4)
					sm.Dam[0].Damage = (2 * sm.Dam[0].Damage) / 5;

				if (Pop < GetAttackMiss(index, Target))
				{
					sm.Dam[0].Damage = -3;
				}
			}

			int TargetLeader = pMob[Target].Leader;
			
			if (sm.Dam[0].Damage > 0)
			{
				if (TargetLeader <= MOB_EMPTY)
					TargetLeader = Target;

				SetBattle(TargetLeader, index);

				if (pMob[index].MOB.Clan != 4)
					SetBattle(index, TargetLeader);

				for (int z = 0; z < MAX_PARTY; z++)
				{
					int partyconn = pMob[TargetLeader].PartyList[z];
					if (partyconn <= MAX_USER)
						continue;

					if (pMob[partyconn].Mode == MOB_EMPTY || pMob[partyconn].MOB.CurrentScore.Hp <= 0)
					{
						if (pMob[partyconn].Mode != MOB_EMPTY)
						{
							pMob[partyconn].MOB.CurrentScore.Hp = 0;
							DeleteMob(partyconn, 1);
						}

						pMob[TargetLeader].PartyList[z] = MOB_EMPTY;
						continue;
					}

					SetBattle(partyconn, index);
					SetBattle(index, partyconn);
				}

				int Summoner = pMob[index].Summoner;
				
				if (pMob[index].MOB.Clan == 4 && Target >= MAX_USER && Summoner > 0 && Summoner < MAX_USER && pUser[Summoner].Mode == USER_PLAY)
				{
					int posX = pMob[Summoner].TargetX;
					int posY = pMob[Summoner].TargetY;
					int num = 46;
					int dam = 0;
					int exp = 0;
					int summdam = 0;

					if (pMob[index].TargetX > posX - num && pMob[index].TargetX < posX + num && pMob[index].TargetY > posY - num && pMob[index].TargetY < posY + num)
					{
						if (pMob[Target].MOB.CurrentScore.Hp < sm.Dam[0].Damage)
							summdam = pMob[Target].MOB.CurrentScore.Hp;
						
						else
							summdam = sm.Dam[0].Damage;
					}
				}
			}

			if (sm.Dam[0].Damage > 0 || sm.Dam[0].Damage <= -5)
			{
				int DamageNow = sm.Dam[0].Damage;
				int damage = 0;
				int mountindex = pMob[Target].MOB.Equip[14].sIndex;

				if (Target < MAX_USER && mountindex >= 2360 && mountindex < 2390 && pMob[Target].MOB.Equip[14].stEffect[0].sValue > 0)
				{
					DamageNow = (3 * sm.Dam[0].Damage) / 4;
					damage = sm.Dam[0].Damage - DamageNow;

					if (DamageNow <= 0)
						DamageNow = 1;

					sm.Dam[0].Damage = DamageNow;
				}

				for (int c = 0; c < MAX_AFFECT && Target < MAX_USER; c++)
				{
					if (pMob[Target].Affect[c].Type == 18)
					{
						if (pMob[Target].MOB.CurrentScore.Mp > ((pMob[Target].MOB.CurrentScore.MaxMp / 100) * 10))
						{
							int mana = pMob[Target].MOB.CurrentScore.Mp - (DamageNow >> 1);

							if (mana < 0)
							{
								DamageNow -= mana;
								mana = 0;
							}

							pMob[Target].MOB.CurrentScore.Mp = mana;

							SetReqMp(Target);

							SendSetHpMp(Target);

							DamageNow = ((DamageNow >> 1) + (DamageNow << 4)) / 80;
							sm.Dam[0].Damage = DamageNow;
						}
					}
				}


				if (pMob[Target].MOB.Equip[13].sIndex == 786)
				{
					int sanc = pMob[Target].MOB.Equip[13].stEffect[0].cValue;
					
					if (sanc < 2)
						sanc = 2;

					sanc *= 2;

					pMob[Target].MOB.CurrentScore.Hp = pMob[Target].MOB.CurrentScore.Hp - (sm.Dam[0].Damage / sanc);
				}
				else if (pMob[Target].MOB.Equip[13].sIndex == 1936)
				{
					int sanc = pMob[Target].MOB.Equip[13].stEffect[0].cValue;
					
					if (sanc < 2)
						sanc = 2;

					sanc *= 10;

					pMob[Target].MOB.CurrentScore.Hp = pMob[Target].MOB.CurrentScore.Hp - (sm.Dam[0].Damage / sanc);
				}
				else if (pMob[Target].MOB.Equip[13].sIndex == 1937)
				{
					int sanc = pMob[Target].MOB.Equip[13].stEffect[0].cValue;
					
					if (sanc < 2)
						sanc = 2;

					sanc *= 1000;

					pMob[Target].MOB.CurrentScore.Hp = pMob[Target].MOB.CurrentScore.Hp - (sm.Dam[0].Damage / sanc);
				}
				else
				{
					if (pMob[Target].MOB.CurrentScore.Hp < sm.Dam[0].Damage)
						pMob[Target].MOB.CurrentScore.Hp = 0;

					else
						pMob[Target].MOB.CurrentScore.Hp = pMob[Target].MOB.CurrentScore.Hp - sm.Dam[0].Damage;
				}

				if (Target > MAX_USER && pMob[Target].MOB.Clan == 4)
					LinkMountHp(Target);

				if (damage > 0 && !GetMountProtect(Target))//dano na montaria
					ProcessAdultMount(Target, damage);
			}

			GridMulticast(pMob[Target].TargetX, pMob[Target].TargetY, (MSG_STANDARD*)&sm, 0);

			if (Target > 0 && Target < MAX_USER)
			{
				if (pUser[Target].HP < sm.Dam[0].Damage)
					pUser[Target].HP = 0;

				else
					pUser[Target].HP = pUser[Target].HP - sm.Dam[0].Damage;

				SetReqHp(Target);
				SendSetHpMp(Target);
			}
			else
				SendScore(Target);

			if (pMob[Target].MOB.CurrentScore.Hp <= 0)
			{
				pMob[Target].MOB.CurrentScore.Hp = 0;
				
				MobKilled(Target, index, 0, 0);
			}
		}

		//Kefra
		if (0 == 1)
		{
KefraAttackLabel:
			MSG_Attack sm;
			memset(&sm, 0, sizeof(MSG_Attack));

			GetAttackArea(index, &sm);
			MobAttack(index, sm);
		}

		if (BattleMode & 0x100)
		{
			int TargetID = pMob[index].CurrentTarget;
			pMob[index].GetTargetPosDistance(TargetID);

			if (pMob[index].NextX == pMob[index].TargetX && pMob[index].NextY == pMob[index].TargetY)
				continue;

			MSG_Action sm;
			if (GetEmptyMobGrid(index, &pMob[index].NextX, &pMob[index].NextY) == FALSE)
				continue;

			GetAction(index, pMob[index].NextX, pMob[index].NextY, (MSG_Action*)&sm);

			sm.Speed = BASE_GetSpeed(&pMob[index].MOB.CurrentScore);
			sm.Effect = 0;

			GridMulticast(index, pMob[index].NextX, pMob[index].NextY, (MSG_STANDARD*)&sm);
		}

		if (BattleMode & 1)
		{
			Target = pMob[index].CurrentTarget;
			pMob[index].GetTargetPos(Target);

			if (pMob[index].NextX == pMob[index].TargetX && pMob[index].NextY == pMob[index].TargetY)
				continue;

			MSG_Action sm;
			if (GetEmptyMobGrid(index, &pMob[index].NextX, &pMob[index].NextY) == FALSE)
				continue;

			GetAction(index, pMob[index].NextX, pMob[index].NextY, (MSG_Action*)&sm);

			sm.Speed = BASE_GetSpeed(&pMob[index].MOB.CurrentScore);
			sm.Effect = 0;

			GridMulticast(index, pMob[index].NextX, pMob[index].NextY, (MSG_STANDARD*)&sm);
		}

		if (BattleMode & 2)
			DoTeleport(index, pMob[index].NextX, pMob[index].NextY);

		if (BattleMode & 0x10)
		{
			MSG_Action sm;
			
			if (GetEmptyMobGrid(index, &pMob[index].NextX, &pMob[index].NextY) == FALSE)
				continue;

			GetAction(index, pMob[index].NextX, pMob[index].NextY, (MSG_Action*)&sm);

			if (pMob[index].NextX == pMob[index].TargetX && pMob[index].NextY == pMob[index].TargetY)
				continue;

			sm.Speed = BASE_GetSpeed(&pMob[index].MOB.CurrentScore);
			sm.Effect = 0;

			GridMulticast(index, pMob[index].NextX, pMob[index].NextY, (MSG_STANDARD*)&sm);
		}
	}
#pragma endregion

#pragma region >> Limpa as propriedades do mob caso não foram removidas pelo método padrão

	if (SecCounter % 20 == 0)
	{
		for (int nY = 0; nY < MAX_GRIDY; nY++)
		{
			for (int nX = 0; nX < MAX_GRIDX; nX++)
			{
				int Target = pMobGrid[nY][nX];

				if (Target < MAX_USER) continue;

				if (pMob[Target].Mode == MOB_EMPTY || pMob[Target].MOB.CurrentScore.Hp <= FALSE)
				{
					if (pMob[Target].TargetX != 0 && pMob[Target].TargetY != 0)
					{
						MSG_RemoveMob sm;
						memset(&sm, 0, sizeof(MSG_RemoveMob));
						sm.Size = sizeof(MSG_RemoveMob);

						sm.Type = _MSG_RemoveMob;
						sm.ID = Target;
						sm.RemoveType = 0;

						GridMulticast(pMob[Target].TargetX, pMob[Target].TargetY, (MSG_STANDARD*)&sm, Target < MAX_USER ? Target : 0);
					}

					pMob[Target].Clear();

					pMobGrid[nY][nX] = 0;
				}
			}
		}
	}

	if (SecCounter % 120 == 0)//2 minutos
	{
		if (!StartImpost)//necessário para contabilizar o impost das cidades sem dono
		{
			StartImpost = TRUE;

			for (int i = MAX_USER; i < MAX_MOB; i++)
			{
				if (pMob[i].Mode == MOB_EMPTY)
					continue;

				if (pMob[i].MOB.Equip[0].sIndex == 219 ||
					strncmp(pMob[i].MOB.MobName, "Balmus", NAME_LENGTH) == 0 ||
					strncmp(pMob[i].MOB.MobName, "Bruce", NAME_LENGTH) == 0 ||
					strncmp(pMob[i].MOB.MobName, "Empis", NAME_LENGTH) == 0 ||
					strncmp(pMob[i].MOB.MobName, "Kara", NAME_LENGTH) == 0)
				{
					pMob[i].MOB.CurrentScore.Hp = 0;
					MobKilled(i, i, 0, 0);
				}
			}

		}
	}
#pragma endregion
}

void ProcessMinTimer()
{
	time_t rawtime;
	tm *timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	if (timeinfo->tm_mday != LastLogDay && LastLogSystem && LastLogQuests && LastLogDebugs && LastLogEvents && LastLogCombine && LastLogItens)
		StartLog();

	if ((MinCounter % 2) == 0)
	{
		int NewbieServerID = (timeinfo->tm_mday - 1) % NumServerInGroup;

		if (LOCALSERVER != 0 || ServerIndex == NewbieServerID)
			NewbieEventServer = 1;

		else if (NewbieEventServer == 1 && ServerIndex != NewbieServerID)
		{
			// CEncampment::ChangeNewBieChannel();

			for (int i = 1; i < MAX_USER; i++)
			{
				if (pUser[i].Mode == USER_EMPTY || pUser[i].cSock.Sock == 0)
					continue;

				if (pUser[i].TradeMode == 1)
					RemoveTrade(i);
			}

			NewbieEventServer = 0;
		}


		//if (timeinfo->tm_wday == 0)
		if (warsTimer[eNoatum].Days[timeinfo->tm_wday])
		{
			CastleServer = 1;
		}
		else
			CastleServer = 0;
		

		if (1 != 0) // Likely to be a debug flag of sorts.. TODO: Check and decide if it stays
		{
			int wNum = BASE_GetWeekNumber();
			int wMod = wNum % 7;
			int wDay = wNum / 7;

			//if (wMod == 0 && ((wDay % 2) == (ServerIndex % 2)))
			//	CastleServer = 1;
			//else
			//	CastleServer = 0;

		}

	}

	
	
	for(int i = 0; i < MAX_GUILDZONE; i++)
	{
		if(GuildImpostoID[i] == 0)
			continue;

		if(pMob[GuildImpostoID[i]].MOB.CurrentScore.Hp <= 0)
			continue;

		strcpy(temp, "./npc/");

		char name[NAME_LENGTH];

		sprintf(name, "%s", pMob[GuildImpostoID[i]].MOB.MobName);

		for(int j = 0; j < NAME_LENGTH; j++)
		{
			if(name[j] == ' ')
				name[j] = '_';
		}

		strcat(temp, name);

		int handle = _open(temp, _O_CREAT | _O_RDWR | _O_BINARY, _S_IREAD | _S_IWRITE);
		if (handle == -1)
		{
			Log("-system", "fail - save npc imposto file", 0);
			return;
		}
		_write(handle, (void*)&pMob[GuildImpostoID[i]].MOB, sizeof(pMob[GuildImpostoID[i]].MOB));
		_close(handle);
	}


	if (ForceWeekMode != -1)
		timeinfo->tm_wday = -1;

	CCastleZakum::ProcessMinTimer();

#pragma region Clear Area
	if (Kingdom1Clear == 1)
	{
		Kingdom1Clear = 2;
	}
	else if (Kingdom1Clear == 2)
	{
		Kingdom1Clear = 0;

		ClearArea(1676, 1556, 1776, 1636);
	}

	if (Kingdom2Clear == 1)
	{
		Kingdom2Clear = 2;
	}
	else if (Kingdom2Clear == 2)
	{
		Kingdom2Clear = 0;

		ClearArea(1676, 1816, 1776, 1892);
	}
#pragma endregion

	if ((MinCounter % 10) == 0)
		memset(FailAccount, 0, sizeof(FailAccount));

	CurrentTime = timeGetTime();


#pragma region Close Gates
	if (BigCubo == 1) // Apenas adicionei, falta criar os comandos pra iniciar e terminar o resto, mas a func ta ai
	{
		for (int i = 17; i < g_dwInitItem - 10; i++)
		{
			int ipx = g_pInitItem[i].PosX; // Item Pos X
			int ipy = g_pInitItem[i].PosY; // Item Pos Y
			int ipg = pItemGrid[ipy][ipx]; // Item Pos Grid

			if (pItem[ipg].ITEM.sIndex <= 0 || pItem[ipg].ITEM.sIndex >= MAX_ITEMLIST)
				continue;

			CItem *tItem = &pItem[ipg];

			int iKey = BASE_GetItemAbility(&pItem[ipg].ITEM, 39);

			if (iKey != 0)
			{
				if (pItem[ipg].State == STATE_OPEN && iKey < 15)
				{
					if (pItem[ipg].Delay == 0)
					{
						pItem[ipg].Delay = 1;

						continue;
					}

					UpdateItem(ipg, 3, &pItem[ipg].Height);

					pItem[ipg].Delay = 0;

					MSG_CreateItem sm;

					sm.Type = _MSG_CreateItem;
					sm.Size = sizeof(MSG_CreateItem);
					sm.ID = ESCENE_FIELD;

					sm.ItemID = ipg + 10000;

					memcpy(&sm.Item, &pItem[ipg].ITEM, sizeof(STRUCT_ITEM));

					sm.GridX = ipx;
					sm.GridY = ipy;

					sm.Rotate = pItem[ipg].Rotate;
					sm.State = pItem[ipg].State;

					GridMulticast(ipx, ipy, (MSG_STANDARD*)&sm, 0);
				}
			}
		}
	}
	else
	{
		for (int i = 17; i < g_dwInitItem; i++)
		{
			int ipx = g_pInitItem[i].PosX; // Item Pos X
			int ipy = g_pInitItem[i].PosY; // Item Pos Y
			int ipg = pItemGrid[ipy][ipx]; // Item Pos Grid

			if (pItem[ipg].ITEM.sIndex <= 0 || pItem[ipg].ITEM.sIndex >= MAX_ITEMLIST)
				continue;

			CItem *tItem = &pItem[ipg];

			int iKey = BASE_GetItemAbility(&pItem[ipg].ITEM, 39);

			if (iKey != 0)
			{
				if (pItem[ipg].State == STATE_OPEN && iKey < 15)
				{
					if (pItem[ipg].Delay == 0)
					{
						pItem[ipg].Delay = 1;

						continue;
					}

					UpdateItem(ipg, 3, &pItem[ipg].Height);
					/*
					MSG_UpdateItem sm;

					sm.ID = ESCENE_FIELD;
					sm.Type = _MSG_UpdateItem;

					sm.ItemID = ipg + 10000;

					sm.Size = sizeof(MSG_UpdateItem);

					//sm.Height = pItem[ipg].Height;
					*/
					pItem[ipg].State = STATE_LOCKED;
					/*
					sm.State = pItem[ipg].State;

					GridMulticast(ipx, ipy, (MSG_STANDARD*)&sm, 0);
					*/
					pItem[ipg].Delay = 0;

					MSG_CreateItem sm;

					sm.Type = _MSG_CreateItem;
					sm.Size = sizeof(MSG_CreateItem);
					sm.ID = ESCENE_FIELD;

					sm.ItemID = ipg + 10000;

					memcpy(&sm.Item, &pItem[ipg].ITEM, sizeof(STRUCT_ITEM));

					sm.GridX = ipx;
					sm.GridY = ipy;

					sm.Rotate = pItem[ipg].Rotate;
					sm.State = pItem[ipg].State;
					//sm.Create = Create;

					//sm.Height = pItem[empty].Height;

					GridMulticast(ipx, ipy, (MSG_STANDARD*)&sm, 0);
				}
			}
		}
	}
#pragma endregion
#pragma region GenerateMobs
	for (int i = 0; i < mNPCGen.NumList; i++)
	{
		int MinuteGenerate = mNPCGen.pList[i].MinuteGenerate;

		if (i != 0 && i != 1 && i != 2 && i != 5 && i != 6 && i != 7 && i != -1)
		{
			if (MinuteGenerate <= 0)
				continue;
			

			int mod = i % MinuteGenerate;

			if (MinCounter % MinuteGenerate == mod)
			{
				GenerateMob(i, 0, 0);
				
				//if(!LoadTerritory)
					//ReadTerritory(); // essa leitura esta bugando os arquivos json
				
				if (MinuteGenerate >= 500 && MinuteGenerate < 1000)
				{
					//srand(time(NULL));
					mNPCGen.pList[i].MinuteGenerate = rand() % 500 + 500;

					continue;
				}

				if (MinuteGenerate >= 1000 && MinuteGenerate < 2000)
				{
					//srand(time(NULL));
					mNPCGen.pList[i].MinuteGenerate = rand() % 1000 + 1000;

					continue;
				}

				if (MinuteGenerate >= 2000 && MinuteGenerate < 3800)
				{
					//srand(time(NULL));
					mNPCGen.pList[i].MinuteGenerate = rand() % 1800 + 2000;

					continue;
				}

				if (MinuteGenerate >= 3800)
				{
					mNPCGen.pList[i].MinuteGenerate = rand() % 1000 + 3800;

					if (DUNGEONEVENT)
					{
						//srand(time(NULL));
						int RndPos = rand() % 30;
						int dpX = DungeonPos[RndPos][0];
						int dpY = DungeonPos[RndPos][1];

						int RndL = rand() % 5 + 5;

						for (int j = 0; j < RndL; j++)
						{
							STRUCT_ITEM PrizeItem;

							memset(&PrizeItem, 0, sizeof(STRUCT_ITEM));

							//srand(time(NULL));
							PrizeItem.sIndex = DungeonItem[rand() % 10];

							SetItemBonus(&PrizeItem, 0, 0, 0);

							int rnd = rand() % 4;

							CreateItem(dpX, dpY, &PrizeItem, rnd, 1);
						}
					}
				}
				
			}
		}
		
	}
#pragma endregion
	MinCounter++;

	//srand(time(NULL));
	int rndWeather = rand() % 1200;

	if (ForceWeather == -1)
	{
		if (rndWeather >= 0 && rndWeather < 260 && CurrentWeather != 0)
		{
			CurrentWeather = 0;
			SendWeather();
		}
		else if (rndWeather >= 30 && rndWeather < 50 && CurrentWeather != 1)
		{
			CurrentWeather = 1;
			SendWeather();
		}
		else if (rndWeather >= 55 && rndWeather < 60 && CurrentWeather != 2)
		{
			CurrentWeather = 2;
			SendWeather();
		}
	}
	else
	{
		if (ForceWeather != CurrentWeather)
		{
			CurrentWeather = ForceWeather;
			SendWeather();
		}
	}
 
	GuildProcess();
	WarCity();
	WarNoatum();
}
