#include "ProcessClientMessage.h"
#include "SombraNegra.h"
#include "BossCamp.h"
#include "TitleSystem.h"
#include "IlegalCMD.h"

void Exec_MSG_Attack(int a_iConn, char* pMsg)
{
	MSG_Attack* m = (MSG_Attack*)pMsg;

	m->ID = ESCENE_FIELD;


	short TargetKilled[MAX_TARGET] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	unsigned int ClientTick = m->ClientTick;

	unsigned int LastAttackTick = 0;

	if (pUser[a_iConn].TradeMode)
	{
		SendClientMsg(a_iConn, g_pMessageStringTable[_NN_CantWhenAutoTrade]);
		return;
	}

	if (pUser[a_iConn].Mode != USER_PLAY)
	{
		SendHpMode(a_iConn);
		return;
	}

	if (pMob[a_iConn].LastX / 128 == RvrMapX && pMob[a_iConn].LastY / 128 == RvrMapY && !pMob[a_iConn].MOB.Clan)
	{
		SendClientMsg(a_iConn, "Você não pode atacar nessa área.");
		return;
	}


	if (pMob[a_iConn].MOB.CurrentScore.Hp == 0 && m->SkillIndex != 99)
	{
		SendHpMode(a_iConn);
		AddCrackError(a_iConn, 1, 8);
		return;
	}

	if (ClientTick != SKIPCHECKTICK && pUser[a_iConn].LastAttackTick != SKIPCHECKTICK && m->ClientTick < (unsigned int)pUser[a_iConn].LastAttackTick + 800)
	{
		sprintf(temp, "err,attack %d %d 800ms limit", m->ClientTick, pUser[a_iConn].LastAttackTick);

		Log(temp, pUser[a_iConn].AccountName, pUser[a_iConn].IP);
		AddCrackError(a_iConn, 1, 107);
		SendBanAccount(a_iConn, Banned::Analise);
		SaveInfoDetect(a_iConn, temp);

		return;
	}

	if (ClientTick != SKIPCHECKTICK && pUser[a_iConn].LastAttackTick != SKIPCHECKTICK)
	{
		if (ClientTick < (unsigned int)pUser[a_iConn].LastAttackTick - 100)
			AddCrackError(a_iConn, 4, 7);

		LastAttackTick = pUser[a_iConn].LastAttackTick;

		pUser[a_iConn].LastAttackTick = ClientTick;
		pUser[a_iConn].LastAttack = m->SkillIndex;
	}

	if (ClientTick != SKIPCHECKTICK)
	{
		int ClientTick15sec = 0;

		if (CurrentTime <= 0x1D4C0)
			ClientTick15sec = 0;
		else
			ClientTick15sec = CurrentTime - 120000;

		if (ClientTick > CurrentTime + 15000 || ClientTick < (unsigned int)ClientTick15sec)
		{
			Log("etc,clienttime faster than 15 sec - MSG_ATTACK", pUser[a_iConn].AccountName, pUser[a_iConn].IP);
			AddCrackError(a_iConn, 1, 107);
			SendBanAccount(a_iConn, Banned::Tempo3horas);
			SaveInfoDetect(a_iConn, "clienttime faster than 15 sec - MSG_ATTACK");
			return;
		}

		pUser[a_iConn].LastAttackTick = ClientTick;
	}

	int skillnum = m->SkillIndex;

	int tx = m->TargetX;
	int ty = m->TargetY;

	if (ClientTick != SKIPCHECKTICK && skillnum != 42 && (tx != m->TargetX || ty != m->TargetY))
	{
		sprintf(temp, "err,hitposition %d,%d - %d,%d - %d,%d", m->PosX, m->PosY, m->TargetX, m->TargetY, tx, ty);
		MyLog(LogType::Attack, pUser[a_iConn].AccountName, temp, 0, pUser[a_iConn].IP);
		AddCrackError(a_iConn, 2, 9);
		SendBanAccount(a_iConn, Banned::Tempo3horas);
		SaveInfoDetect(a_iConn, temp);
		return;
	}


	if (skillnum >= 0 && skillnum < MAX_SKILLINDEX && ClientTick != SKIPCHECKTICK)
	{
		if (skillnum < -1 || skillnum > MAX_SKILLINDEX)
		{
			MyLog(LogType::Attack, pUser[a_iConn].AccountName, "MSG_Attack, skillnum out of range", 0, pUser[a_iConn].IP);
			return;
		}

		if (g_pSpell[skillnum].Passive == 1)
			return;

		/* Proteção Absoluta */
		if (pMob[a_iConn].MOB.Class == 1) 
		{
			for (int i = 0; i < MAX_AFFECT; i++)
			{
				if (pMob[a_iConn].Affect[i].Type != 6)
					continue;

				pMob[a_iConn].Affect[i].Type = 0;
				pMob[a_iConn].Affect[i].Value = 0;
				pMob[a_iConn].Affect[i].Level = 0;
				pMob[a_iConn].Affect[i].Time = 0;

				pMob[a_iConn].GetCurrentScore(a_iConn);
				SendScore(a_iConn);

				break;
			}
		}
		if (LastAttackTick != -1 && ClientTick != SKIPCHECKTICK)
		{
			int isTime = ClientTick - LastAttackTick;

			int skilldelay = g_pSpell[skillnum].Delay;

			if ((pMob[a_iConn].MOB.Rsv & RSV_CAST) != 0 && skilldelay >= 2)
				skilldelay--;

			
			for (int i = 0; i < MAX_AFFECT; i++)
			{
				if (pMob[a_iConn].Affect[i].Type == 8)
				{
					int master = pMob[a_iConn].Affect[i].Level;
					if (master & (1 << 0))//bonus sagacidade
						skilldelay--;
				}
			}

			skilldelay = skilldelay * 1000;

			if (isTime < 700)
			{
				AddCrackError(a_iConn, 10, 30);
				sprintf(temp, "skill delay skillnum: %d-%d", ClientTick, isTime);
				MyLog(LogType::Attack, pUser[a_iConn].AccountName, temp, 0, pUser[a_iConn].IP);

				return;
			}
		}

		pUser[a_iConn].LastAttackTick = m->ClientTick;

		if ((skillnum / 24) != pMob[a_iConn].MOB.Class && (skillnum / 24) <= 3)
		{
			MyLog(LogType::Attack, pUser[a_iConn].AccountName, "MSG_Attack, Request other class skill", 0, pUser[a_iConn].IP);
			return;
		}
	}

	int Level = 0;
	int Delay = 100;
	int Special = 0;

	if (skillnum >= 0 && skillnum < 96)
	{
		int getSkillMaster = ((skillnum % 24) / 8) + 1;

		if (ClientTick != SKIPCHECKTICK)
		{
			int learn = skillnum % 24;
			int learnedSkill = 1 << learn;

			if (m->ClientTick != SKIPCHECKTICK && (pMob[a_iConn].MOB.LearnedSkill & learnedSkill) == FALSE && AddCrackError(a_iConn, 8, 10) != FALSE)
				return;

			if (getSkillMaster <= 0 || getSkillMaster > 3)
			{
				MyLog(LogType::Attack, pUser[a_iConn].AccountName, "Skill kind out of bound - MSG_ATTACK", pUser[a_iConn].AccountName, pUser[a_iConn].IP);
				return;
			}
		}

		Level = pMob[a_iConn].MOB.CurrentScore.Special[getSkillMaster];
		Delay = Delay + Level;
		Special = Level;
	}
	else
	{
		if (skillnum >= 96 && skillnum <= 100)
		{
			if (skillnum == 97)
			{
				if (m->PosX > 0 && m->PosX < 4096 && m->PosY > 0 && m->PosY < 4096)
				{
					int itemId = pItemGrid[m->PosX][m->PosY];
					if (itemId > 0 && itemId < MAX_ITEMLIST && pItem[itemId].ITEM.sIndex == 746)
						m->Motion = 1;
					else
					{
						MyLog(LogType::Attack, pUser[a_iConn].AccountName, "err, mortar invalid", pUser[a_iConn].AccountName, pUser[a_iConn].IP);
						return;
					}
				}
				else
				{
					MyLog(LogType::Attack, pUser[a_iConn].AccountName, "err, mortar invalid", pUser[a_iConn].AccountName, pUser[a_iConn].IP);
					return;
				}
			}
			else
			{
				int learn = skillnum - 72;
				int learnedSkill = 1 << learn;
				if (m->ClientTick != SKIPCHECKTICK && (pMob[a_iConn].MOB.LearnedSkill & learnedSkill) == FALSE && AddCrackError(a_iConn, 208, 1) != FALSE)
					return;
			}

			Level = pMob[a_iConn].MOB.CurrentScore.Level;
			Delay = Delay + Level;
			Special = Level;
		}
	}
#pragma region Escudo dourado
	if (skillnum == 85)
	{
		int coin = 100 * Level;

		if (pMob[a_iConn].MOB.Coin < coin)
			return;

		pMob[a_iConn].MOB.Coin -= coin;
		SendEtc(a_iConn);
	}
#pragma endregion
#pragma region Consumo de mana
	int Mp = pMob[a_iConn].MOB.CurrentScore.Mp;
	//int ReqMp = pUser[a_iConn].ReqMp;

	if (skillnum >= 0 && skillnum < MAX_SKILLINDEX)
	{
		int ManaSpent = BASE_GetManaSpent(skillnum, pMob[a_iConn].MOB.SaveMana, Special);

		if ((pMob[a_iConn].MOB.CurrentScore.Mp - ManaSpent) < 0)
		{
			SendSetHpMp(a_iConn);
			return;
		}

		pMob[a_iConn].MOB.CurrentScore.Mp = pMob[a_iConn].MOB.CurrentScore.Mp - ManaSpent;
		//pUser[a_iConn].ReqMp = pUser[a_iConn].ReqMp - ManaSpent;
		SetReqMp(a_iConn);

		/* Espelho Mágico */
		if (pMob[a_iConn].MOB.Class == 0 && (pMob[a_iConn].Extra.SecLearnedSkill & 0x100)) 
		{
			pMob[a_iConn].MOB.CurrentScore.Mp = pMob[a_iConn].MOB.CurrentScore.Mp - ManaSpent / 2;
			SetReqMp(a_iConn);
		}
	}

	m->CurrentMp = pMob[a_iConn].MOB.CurrentScore.Mp;
	//m->ReqMp = pUser[a_iConn].ReqMp;
#pragma endregion

	int master = 0;

	if (!pMob[a_iConn].MOB.Class && pMob[a_iConn].MOB.LearnedSkill & 0x4000)
	{
		master = pMob[a_iConn].MOB.CurrentScore.Special[2] / 20;

		if (master < 0)
			master = 0;

		if (master > 15)
			master = 15;
	}

	if (pMob[a_iConn].MOB.Class == 3)
		DoRemoveHide(a_iConn);

	DoRemoveSamaritano(a_iConn);

	int Exp = 0;
	int mylevel = pMob[a_iConn].MOB.CurrentScore.Level;

	unsigned char map_att = GetAttribute(pMob[a_iConn].TargetX, pMob[a_iConn].TargetY) & 0x40;

	int hp = pMob[a_iConn].MOB.CurrentScore.Hp;

	int UNK2 = 0;
	unsigned char DoubleCritical = 0;

	if (skillnum == 79)
	{
		m->ClientTick = 0xE0A1ACA;
		m->Motion = 254;

		m->TargetX = pMob[a_iConn].TargetX;
		m->TargetY = pMob[a_iConn].TargetY;

		m->AttackerID = a_iConn;
		m->SkillIndex = 79;

		for (int x = 1; x < 6; x++)
		{
			m->Dam[x].Damage = m->Dam[0].Damage;
			m->Dam[x].TargetID = m->Dam[0].TargetID;
		}
	}

#pragma region Loop Target
	for (int i = 0; i < MAX_TARGET; i++)
	{
		if (i >= MAX_TARGET && m->Size <= sizeof(MSG_Attack))
			break;

		else if (i >= 1 && m->Size <= sizeof(MSG_AttackOne))
			break;

		else if (i >= 2 && m->Size <= sizeof(MSG_AttackTwo))
			break;


		int idx = m->Dam[i].TargetID;

		if (idx <= 0 || idx >= MAX_MOB)
			continue;

		if (pMob[idx].MOB.Class == 3)
			DoRemoveHide(idx);

		if (pMob[idx].Mode == MOB_EMPTY)
		{
			SendRemoveMob(a_iConn, idx, 1, 0);
			continue;
		}

		if (idx >= MAX_USER && (pMob[idx].MOB.Equip[0].sIndex == 219 || pMob[idx].MOB.Equip[0].sIndex == 220) && ((pMob[idx].TargetX / 128) == 26 && (pMob[idx].TargetY / 128) == 12))
		{
			m->Dam[i].TargetID = 0;
			m->Dam[i].Damage = 0;

			continue;
		}

		if (pMob[idx].MOB.CurrentScore.Hp <= 0 && m->SkillIndex != 31 && m->SkillIndex != 99)
		{
			m->Dam[i].TargetID = 0;
			m->Dam[i].Damage = 0;

			// SendRemoveMob(a_iConn, idx, 1, 0);
			continue;
		}

		if (pMob[idx].MOB.Merchant == 4 || pMob[idx].MOB.Merchant == 43 || pMob[idx].MOB.Merchant == 1 || pMob[idx].MOB.Merchant == 100)
		{
			m->Dam[i].TargetID = 0;
			m->Dam[i].Damage = 0;
			continue;
		}

		if (skillnum != 42 && (pMob[a_iConn].TargetX < pMob[idx].TargetX - VIEWGRIDX || pMob[a_iConn].TargetX > pMob[idx].TargetX + VIEWGRIDX || pMob[a_iConn].TargetY < pMob[idx].TargetY - VIEWGRIDY || pMob[a_iConn].TargetY > pMob[idx].TargetY + VIEWGRIDY))
		{
			SendRemoveMob(a_iConn, idx, 1, 0);
			continue;
		}

		long long dam = m->Dam[i].Damage;

		if (dam != -2 && dam != -1 && dam)
		{
			m->Dam[i].Damage = 0;
			AddCrackError(a_iConn, 10, 77);

			continue;
		}


		if (strcmp(pMob[idx].MOB.MobName, "Espelho RainhaG") == 0 && idx >= MAX_USER)
		{
			pMob[idx].CurrentTradeSecTimer = 1200;
		}

		

		
		int leader = pMob[a_iConn].Leader;

		if (leader == 0)
			leader = a_iConn;

		int mobleader = pMob[idx].Leader;

		if (mobleader == 0)
			mobleader = idx;

		int Guild = pMob[a_iConn].MOB.Guild;

		if (pMob[a_iConn].GuildDisable)
			Guild = 0;

		int MobGuild = pMob[idx].MOB.Guild;

		if (pMob[idx].GuildDisable)
			MobGuild = 0;

		if (Guild == 0 && MobGuild == 0)
			Guild = -1;

		if (BrState && BRItem > 0 && pMob[a_iConn].TargetX >= 2604 && pMob[a_iConn].TargetY >= 1708 && pMob[a_iConn].TargetX <= 2648 && pMob[a_iConn].TargetY <= 1744)
			Guild = -1;

		int Clan = pMob[a_iConn].MOB.Clan;
		int MobClan = pMob[idx].MOB.Clan;

		int isFrag = 0;

		if (Clan == 7 && MobClan == 7 || Clan == 8 && MobClan == 8)
			isFrag = 1;

		if (WarOfTower::AttackTower(a_iConn, idx) == FALSE)
		{
			m->Dam[i].TargetID = 0;
			m->Dam[i].Damage = 0;
			continue;
		}

		/*if (a_iConn != idx && a_iConn > 0 && a_iConn < MAX_USER && idx > 0 && idx < MAX_USER && CastleState == 0 && GTorreState == 0 && NewbieEventServer == 0)
		{
			int AttackerPK = pUser[a_iConn].PKMode;
			int TargetPK = pUser[idx].PKMode;
			int TargetGuilty = GetGuilty(idx);

			unsigned char attributemap = GetAttribute(pMob[a_iConn].TargetX, pMob[a_iConn].TargetY) & 64;

			if (dam == -2 && !TargetPK && !TargetGuilty && attributemap || dam == -1 && skillnum >= 0 && skillnum <= MAX_SKILLINDEX && g_pSpell[skillnum].Aggressive && attributemap && !TargetPK && !TargetGuilty)
			{
				m->Dam[i].TargetID = 0;
				m->Dam[i].Damage = 0;
				continue;
			}
		}*/

#pragma region Ataque físico
		if (dam == -2)
		{
			int dis = BASE_GetDistance(m->PosX, m->PosY, m->TargetX, m->TargetY);

			if (dis > pUser[a_iConn].Range || dis > 23)
				return;

			dam = 0;

			if (i > 0 && m->Size < sizeof(MSG_AttackTwo) && pMob[a_iConn].MOB.Class != 3 && (pMob[a_iConn].MOB.LearnedSkill & 0x40) == 0)
			{
				AddCrackError(a_iConn, 10, 24);
				continue;
			}

			int CriticalDouble = 0;

			if (i == 0)
				CriticalDouble = BASE_GetDoubleCritical(&pMob[a_iConn].MOB, &pUser[a_iConn].cProgress, &m->Progress, &DoubleCritical);

			dam = pMob[a_iConn].MOB.CurrentScore.Damage;

			if ((DoubleCritical & 2) != 0)
			{
				//srand(time(NULL));
				if (idx < MAX_USER)
					dam = (((rand() % 2) + 13) * dam) / 10;
				else
					dam = (((rand() % 2) + 15) * dam) / 10;


				/*Mãos Sangrentas */
				if (pMob[a_iConn].MOB.Class == 0 && (pMob[a_iConn].Extra.SecLearnedSkill & 0x10))
				{
					int Equip6 = pMob[a_iConn].MOB.Equip[6].sIndex;
					int Equip7 = pMob[a_iConn].MOB.Equip[7].sIndex;

					if (Equip6 > 0 && Equip6 < MAX_ITEMLIST || Equip7 > 0 && Equip7 < MAX_ITEMLIST)
					{
						int Type6 = g_pItemList[Equip6].nPos;
						int Type7 = g_pItemList[Equip7].nPos;

						if (Type6 == 192 && Type7 == 192)
						{
							//srand(time(NULL));
							int sSpecial = pMob[a_iConn].MOB.CurrentScore.Special[2];
							int Calculo = (sSpecial * 10) / 2 + (rand() % 15);
							int Damage = 0;

							if ((rand() % 100) < 20)
							{
								Damage = Calculo;

								pMob[a_iConn].MOB.CurrentScore.Hp = pMob[a_iConn].MOB.CurrentScore.Hp + Damage;

								if (a_iConn > 0 && a_iConn < MAX_USER)
									SetReqHp(a_iConn);

								MSG_SetHpDam dam;

								dam.Type = _MSG_SetHpDam;
								dam.Size = sizeof(MSG_SetHpDam);
								dam.ID = a_iConn;

								dam.Hp = pMob[a_iConn].MOB.CurrentScore.Hp;
								dam.Dam = Damage;

								SendScore(a_iConn);

								GridMulticast(pMob[a_iConn].TargetX, pMob[a_iConn].TargetY, (MSG_STANDARD*)&dam, 0);
							}
						}
					}
				}
			}
			

			int Ac = pMob[idx].MOB.CurrentScore.Ac;

			if (idx < MAX_USER)
				Ac *= 3;

			dam = BASE_GetDamage((int)dam, Ac, master);
			//srand(time(NULL));
			if (i == 0 && m->Size >= sizeof(MSG_AttackTwo) && pMob[a_iConn].MOB.Class == 3 && (pMob[a_iConn].MOB.LearnedSkill & 0x200000) && (rand() % 4) == 0)
			{
				int skilldam = (pMob[a_iConn].MOB.CurrentScore.Special[3] + pMob[a_iConn].MOB.CurrentScore.Str);

				int acc = pMob[idx].MOB.CurrentScore.Ac;

				skilldam = BASE_GetDamage(skilldam, acc, master);

				if (skilldam > 0)
					skilldam /= 2;

				if (skilldam < 60)
					skilldam = rand() % 60 + 10;

				m->Dam[1].TargetID = MOB_EMPTY;
				m->Dam[1].Damage = skilldam;

				DoubleCritical |= 4;
				dam += skilldam;
			}

			if ((DoubleCritical & 1) != FALSE)
				dam *= 2;

			m->DoubleCritical = DoubleCritical;
		}
#pragma endregion
#pragma region Ataque Mágico
		else if (dam == -1 && skillnum >= 0 && skillnum <= MAX_SKILLINDEX)
		{
			dam = 0;

			int maxtarget = g_pSpell[skillnum].MaxTarget;

			if (ClientTick != SKIPCHECKTICK && i > maxtarget)
			{
				AddCrackError(a_iConn, 10, 28);

				sprintf(temp, "skill target max num %d", ClientTick);
				MyLog(LogType::Attack, pUser[a_iConn].AccountName, temp, 0, pUser[a_iConn].IP);

				continue;
			}

			if (g_pSpell[skillnum].bParty != 0 && leader != mobleader && Guild != MobGuild)
			{
				AddCrackError(a_iConn, 10, 27);

				sprintf(temp, "party skill - skill:%d leader:%d tleader:%d", ClientTick, leader, mobleader);
				MyLog(LogType::Attack, pUser[a_iConn].AccountName, temp, 0, pUser[a_iConn].IP);

				continue;
			}

			int unk2 = 0;
			int InstanceType = g_pSpell[skillnum].InstanceType;

#pragma region Ataques com elementos
			if (InstanceType >= 1 && InstanceType <= 5)
			{
				int Weather = CurrentWeather;
				int ApplyWeather = 0;

				if ((pMob[a_iConn].TargetX / 128) < 12 && (pMob[a_iConn].TargetY / 128) > 25)
					ApplyWeather = 1;

				else
					ApplyWeather = 0;

				if (ApplyWeather != 0)
					Weather = 0;
#pragma region Ataque de Fada
				if (ClientTick == SKIPCHECKTICK && m->Motion == 254 && (m->SkillIndex == 32 || m->SkillIndex == 34 || m->SkillIndex == 36))
				{
					int Level = pMob[a_iConn].MOB.CurrentScore.Level;
					int familiarsanc = BASE_GetItemSanc(&pMob[a_iConn].MOB.Equip[13]);

					switch (m->SkillIndex)
					{
					case 32:
						dam = ((__int64)familiarsanc * 200) + ((__int64)Level * 8);
						break;
					case 34:
						dam = ((__int64)familiarsanc * 300) + ((__int64)Level * 8);
						break;
					case 36:
						dam = ((__int64)familiarsanc * 350) + ((__int64)Level * 8);
						break;
					}

					if (dam > 1000)
						dam = 1000;
				}
#pragma endregion
				else
					dam = BASE_GetSkillDamage(skillnum, &pMob[a_iConn].MOB, Weather, pMob[a_iConn].WeaponDamage);

				int def = pMob[idx].MOB.CurrentScore.Ac;

				if (idx < MAX_USER)
					def *= 2;

				if (pMob[idx].MOB.Class == 1)
					def = (def * 3) / 2;

				dam = BASE_GetSkillDamage(dam, def, master);

				if (InstanceType == 1)
				{
					int ResistPoint = 0;

					if (idx < MAX_USER)
					{
						ResistPoint = 10;

						if (pMob[idx].MOB.CurrentScore.Level > 354)
						{
							if (pMob[idx].Extra.ClassMaster >= CELESTIAL)
							{
								ResistPoint += 32;
							}
							else if (pMob[idx].Extra.ClassMaster == ARCH)
							{
								ResistPoint += 16;
							}
							else
							{
								ResistPoint += 15;
							}
						}
					}
					else
					{
						ResistPoint = pMob[idx].MOB.LearnedSkill / 1000;
					}

					dam = ((100 - ResistPoint) * dam) / 100;
				}
				else if (InstanceType >= 2 && InstanceType <= 5 && skillnum != 97)
				{
					int skind = InstanceType - 2;

					int MobResist = pMob[idx].MOB.Resist[skind];

					if (idx < MAX_USER)
						MobResist /= 2;

					dam = dam * (200 - MobResist) / 100;
				}

			}
#pragma endregion
#pragma region All Skills
#pragma region Tempestade de Raios
			if (skillnum == 79)
			{
				dam = BASE_GetSkillDamage(skillnum, &pMob[a_iConn].MOB, CurrentWeather, pMob[a_iConn].WeaponDamage);

				int Ac = pMob[idx].MOB.CurrentScore.Ac;

				 if (idx < MAX_USER)
					Ac *= 2;
			
				 dam = pMob[idx].MOB.CurrentScore.Damage;

				SendSetHpMp(idx);
			}
#pragma endregion
#pragma region Bênção Divina
			if (skillnum == 201) // Bênção Divina
			{
				if (pMob[a_iConn].Extra.SecLearnedSkill & 0x2)
				{
					int Hp = pMob[a_iConn].MOB.CurrentScore.Hp;
					int MaxHp = pMob[a_iConn].MOB.CurrentScore.MaxHp;
					int HpTax = MaxHp - Hp;

					pMob[a_iConn].DivineBlessing = TRUE;
					pMob[a_iConn].RateRegen = HpTax;

					MSG_Attack sm;

					memset(&sm, 0, sizeof(MSG_AttackOne));

					sm.Type = _MSG_AttackOne;
					sm.ID = a_iConn;
					sm.Size = sizeof(MSG_AttackOne);

					sm.ClientTick = 0xE0A1ACA;
					sm.Motion = 255;

					sm.TargetX = pMob[a_iConn].TargetX;
					sm.TargetY = pMob[a_iConn].TargetY;

					sm.CurrentMp = -2;

					sm.AttackerID = a_iConn;
					sm.SkillIndex = 29;

					sm.Dam[0].TargetID = a_iConn;
					sm.Dam[0].Damage = -1;

					if (a_iConn < MAX_USER)
						ProcessClientMessage(a_iConn, (char*)&sm, TRUE);
				}
			}
			else if (InstanceType == 6 && pMob[a_iConn].DivineBlessing == TRUE)
			{
				if (pMob[idx].MOB.Clan == 4)
					continue;

				unsigned char getAttribute = GetAttribute(pMob[idx].TargetX, pMob[idx].TargetY) & 0x40;

				if (map_att == 0 && getAttribute)
				{
					m->Dam[i].TargetID = MOB_EMPTY;
					m->Dam[i].Damage = 0;

					continue;
				}

				if (skillnum == 27)
					dam = 0;
				else
					dam = pMob[a_iConn].RateRegen;

				dam = -dam;

				if (dam < 0 && dam > -6)
					dam = -6;

				int MobHP = pMob[idx].MOB.CurrentScore.Hp;

				if (pMob[idx].MOB.Equip[13].sIndex == 786)
				{
					int sanc = pMob[idx].MOB.Equip[13].stEffect[0].cValue;
					if (sanc < 2)
						sanc = 2;

					pMob[idx].MOB.CurrentScore.Hp = pMob[idx].MOB.CurrentScore.Hp - dam / sanc;

				}
				else  if (pMob[idx].MOB.Equip[13].sIndex == 1936)
				{
					int sanc = pMob[idx].MOB.Equip[13].stEffect[0].cValue;
					if (sanc < 2)
						sanc = 2;

					sanc *= 10;

					pMob[idx].MOB.CurrentScore.Hp = pMob[idx].MOB.CurrentScore.Hp - dam / sanc;

				}

				else  if (pMob[idx].MOB.Equip[13].sIndex == 1937)
				{
					int sanc = pMob[idx].MOB.Equip[13].stEffect[0].cValue;
					if (sanc < 2)
						sanc = 2;

					sanc *= 1000;

					pMob[idx].MOB.CurrentScore.Hp = pMob[idx].MOB.CurrentScore.Hp - dam / sanc;

				}

				else
					pMob[idx].MOB.CurrentScore.Hp = pMob[idx].MOB.CurrentScore.Hp - dam;


				if (pMob[idx].MOB.CurrentScore.Hp > pMob[idx].MOB.CurrentScore.MaxHp)
					pMob[idx].MOB.CurrentScore.Hp = pMob[idx].MOB.CurrentScore.MaxHp;


				if (idx > 0 && idx < MAX_USER)
					SetReqHp(idx);


				int calc_exp = pMob[idx].MOB.CurrentScore.Hp - MobHP >> 3;

				if (calc_exp > 120)
					calc_exp = 120;

				if (calc_exp < 0)
					calc_exp = 0;


				if (calc_exp > 0 && a_iConn != idx && a_iConn > 0 && a_iConn < MAX_USER)
				{
					int village = BASE_GetVillage(pMob[idx].TargetX, pMob[idx].TargetY);

					if (village < 0 || village >= 5)
					{
						if (UNK2 < calc_exp)
							UNK2 = calc_exp;
					}
				}
				pMob[a_iConn].DivineBlessing = FALSE;
				pMob[a_iConn].RateRegen = 0;
			}
#pragma endregion
#pragma region Cura / Recuperação
			else if (InstanceType == 6)
			{
				if (pMob[idx].MOB.Clan == 4)
					continue;

				unsigned char getAttribute = GetAttribute(pMob[idx].TargetX, pMob[idx].TargetY) & 0x40;

				if (map_att == 0 && getAttribute || pMob[idx].MOB.CurrentScore.Hp <= 0)
				{
					m->Dam[i].TargetID = MOB_EMPTY;
					m->Dam[i].Damage = 0;

					continue;
				}

				if (skillnum == 27)
					dam = (Special * 2) + g_pSpell[skillnum].InstanceValue;
				else
					dam = (Special * 3) + g_pSpell[skillnum].InstanceValue;


				if (pMob[a_iConn].Extra.ClassMaster != MORTAL && pMob[a_iConn].Extra.ClassMaster != ARCH)
					dam *= 2;

				if (pMob[a_iConn].Extra.ClassMaster != MORTAL && pMob[a_iConn].Extra.ClassMaster != ARCH)
				{
					if (dam >= 1090)
						dam = 1100;
				}
				else
				{
					if (dam >= 638)
						dam = 638;
				}

				dam = -dam;

				if (dam < 0 && dam > -6)
					dam = -6;

				int MobHP = pMob[idx].MOB.CurrentScore.Hp;

				if (pMob[idx].MOB.Equip[13].sIndex == 786)
				{
					int sanc = pMob[idx].MOB.Equip[13].stEffect[0].cValue;
					if (sanc < 2)
						sanc = 2;

					pMob[idx].MOB.CurrentScore.Hp = pMob[idx].MOB.CurrentScore.Hp - ((int)dam / sanc);

				}
				else  if (pMob[idx].MOB.Equip[13].sIndex == 1936)
				{
					int sanc = pMob[idx].MOB.Equip[13].stEffect[0].cValue;
					if (sanc < 2)
						sanc = 2;

					sanc *= 10;

					pMob[idx].MOB.CurrentScore.Hp = pMob[idx].MOB.CurrentScore.Hp - ((int)dam / (sanc * 10));

				}

				else  if (pMob[idx].MOB.Equip[13].sIndex == 1937)
				{
					int sanc = pMob[idx].MOB.Equip[13].stEffect[0].cValue;
					if (sanc < 2)
						sanc = 2;

					sanc *= 1000;

					pMob[idx].MOB.CurrentScore.Hp = pMob[idx].MOB.CurrentScore.Hp - ((int)dam / (sanc * 20));

				}

				else
					pMob[idx].MOB.CurrentScore.Hp = pMob[idx].MOB.CurrentScore.Hp - (int)dam;


				if (pMob[idx].MOB.CurrentScore.Hp > pMob[idx].MOB.CurrentScore.MaxHp)
					pMob[idx].MOB.CurrentScore.Hp = pMob[idx].MOB.CurrentScore.MaxHp;

				if (idx > 0 && idx < MAX_USER)
					SendHpMp(idx);

				int calc_exp = (pMob[idx].MOB.CurrentScore.Hp - MobHP) >> 3;

				if (calc_exp > 120)
					calc_exp = 120;

				if (calc_exp < 0)
					calc_exp = 0;


				if (calc_exp > 0 && a_iConn != idx && a_iConn > 0 && a_iConn < MAX_USER)
				{
					int village = BASE_GetVillage(pMob[idx].TargetX, pMob[idx].TargetY);

					if (village < 0 || village >= 5)
					{
						if (UNK2 < calc_exp)
							UNK2 = calc_exp;
					}
				}
			}
#pragma endregion
#pragma region Flash
			else if (InstanceType == 7)
			{
				pMob[idx].Mode = MOB_PEACE;
				pMob[idx].CurrentTarget = MOB_EMPTY;

				for (int j = 0; j < MAX_ENEMY; j++)
					pMob[idx].EnemyList[j] = MOB_EMPTY;
			}
#pragma endregion
#pragma region Desintoxicar
			else if (InstanceType == 8)
			{
				int NeedUpdate = 0;

				for (int k = 0; k < MAX_AFFECT; k++)
				{
					int Type = pMob[idx].Affect[k].Type;

					if (Type == 1 || Type == 3 || Type == 5 || Type == 7 || Type == 10 || Type == 12 || Type == 20 || (Type == 32 && (1 << 7) & pMob[a_iConn].MOB.LearnedSkill))
					{
						pMob[idx].Affect[k].Type = 0;
						NeedUpdate = 1;
					}
				}

				if (NeedUpdate)
				{
					pMob[idx].GetCurrentScore(idx);
					SendScore(idx);
				}
			}
#pragma endregion
#pragma region Teleporte
			else if (InstanceType == 9)
			{
				if (pMob[idx].MOB.CurrentScore.Hp <= 0)
				{
					SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Summon_Dead_Person]);
					break;
				}

				unsigned char getAtt = GetAttribute(pMob[a_iConn].TargetX, pMob[a_iConn].TargetY);

				if (getAtt & 0x4 && pMob[a_iConn].MOB.CurrentScore.Level < 1000)
				{
					SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Summon_Not_Allowed_Here]);
					continue;
				}

				/*if (pMob[idx].MOB.CurrentScore.Hp > pMob[a_iConn].MOB.CurrentScore.Hp + Special + 30)
				{
					SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Too_High_Level_To_Summon]);
					continue;
				}*/

				if (pMob[a_iConn].LastX /128 == 13 && pMob[a_iConn].LastY / 128 == 15)
				{
					SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Summon_Not_Allowed_Here]);
					continue;
				}

				if (pMob[idx].MOB.CurrentScore.Level > pMob[a_iConn].MOB.CurrentScore.Level)
				{
					SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Too_High_Level_To_Summon]);
					continue;
				}

				if ((pMob[idx].TargetX & 0xFF00) == 0 && (pMob[idx].TargetY & 0xFF00) == 0)
				{
					SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Use_That_Here]);
					return;
				}

				/* Zone Kefra*/
				if (pMob[idx].TargetX >= 2335 && pMob[idx].TargetY >= 3896 && pMob[idx].TargetX <= 2395 && pMob[idx].TargetY <= 3955)
				{
					SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Use_That_Here]);
					return;
				}

				/* Zone RvR*/
				if (pMob[idx].TargetX >= 1710 && pMob[idx].TargetY >= 1968 && pMob[idx].TargetX <= 1755 && pMob[idx].TargetY <= 1995)
				{
					SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Use_That_Here]);
					return;
				}

				/* Zone Calabouço Zumbi */
				if ((pMob[idx].TargetX / 128) == 13 || (pMob[idx].TargetY / 128) == 16)
				{
					SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Use_That_Here]);
					return;
				}

				/* Zone Coliseu N */
				if ((pMob[idx].TargetX / 128) == 27 || (pMob[idx].TargetY / 128) == 11)
				{
					SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Use_That_Here]);
					return;
				}

				if (idx < MAX_USER && pUser[idx].Mode == USER_PLAY)
				{
					DoSummon(idx, pMob[a_iConn].TargetX, pMob[a_iConn].TargetY);

					sprintf(temp, g_pMessageStringTable[_SN_Summoned_By_S], pMob[a_iConn].MOB.MobName);
					SendClientMsg(idx, temp);
				}
			}
#pragma endregion
#pragma region Invisibilidade
			else if (InstanceType == 10 && idx < MAX_USER)
			{
				for (int l = MAX_USER; l < MAX_MOB; l++)
				{
					if (pMob[l].Mode == MOB_COMBAT && pMob[l].CurrentTarget == idx)
					{
						for (int m = 0; m < MAX_ENEMY; m++)
						{
							if (pMob[l].EnemyList[m] == idx)
								pMob[l].EnemyList[m] = a_iConn;
						}

						pMob[l].CurrentTarget = a_iConn;
					}
				}
			}
#pragma endregion
#pragma region Evocação
			else if (InstanceType == 11)
			{

				int instancevalue = g_pSpell[skillnum].InstanceValue;

				if (instancevalue > 0 && instancevalue < 51)
				{
					int summons = 0;

					if (instancevalue == 1 || instancevalue == 2)
						summons = pMob[a_iConn].MOB.CurrentScore.Special[2] / 30;

					else if (instancevalue == 3 || instancevalue == 4 || instancevalue == 5)
						summons = pMob[a_iConn].MOB.CurrentScore.Special[2] / 40;

					else if (instancevalue == 6 || instancevalue == 7)
						summons = pMob[a_iConn].MOB.CurrentScore.Special[2] / 80;

					else if (instancevalue == 8)
						summons = 1;

					if (GenerateSummon(a_iConn, instancevalue - 1, 0, summons) == 0)
					{
						pMob[a_iConn].MOB.CurrentScore.Mp = Mp;
						//pUser[a_iConn].ReqMp = ReqMp;
					}
				}
				dam = 0;
			}
#pragma endregion
#pragma region Chamas Etéreas
			else if (InstanceType == 12)
			{
				int Leader = pMob[a_iConn].Leader, slot = 0, targetlevel = pMob[idx].MOB.CurrentScore.Level, level = pMob[a_iConn].MOB.CurrentScore.Level, chance, _rand;

				if (Leader <= 0)
					Leader = a_iConn;

				// Montros
				if (idx > MAX_USER && pMob[idx].MOB.Merchant == 0)
				{
				
					if (pMob[idx].TargetX >= 3725 && pMob[idx].TargetY >= 2833 && pMob[idx].TargetX <= 3833 && pMob[idx].TargetY <= 2908)
						continue;

					if (pMob[idx].TargetX >= 3837 && pMob[idx].TargetY >= 2873 && pMob[idx].TargetX <= 3942 && pMob[idx].TargetY <= 2894)
						continue;

					if (pMob[idx].TargetX >= 1676 && pMob[idx].TargetY >= 1556 && pMob[idx].TargetX <= 1776 && pMob[idx].TargetY <= 1636)
						continue;
					
					if (pMob[idx].TargetX >= 1676 && pMob[idx].TargetY >= 1816 && pMob[idx].TargetX <= 1776 && pMob[idx].TargetY <= 1892)
						continue;

					if (pMob[idx].TargetX >= 2445 && pMob[idx].TargetY >= 1850 && pMob[idx].TargetX <= 2546 && pMob[idx].TargetY <= 1920)
						continue;

					if (!strcmp(pMob[idx].MOB.MobName, "Cav. Lugefer"))
						continue;

					if (!strcmp(pMob[idx].MOB.MobName, "FrenzyDemonLord"))
						continue;

					if (!strcmp(pMob[idx].MOB.MobName, "Lich Crunt"))
						continue;

					if (!strcmp(pMob[idx].MOB.MobName, "Dragao Lich"))
						continue;

					if (!strcmp(pMob[idx].MOB.MobName, "Hezling"))
						continue;

					if (!strcmp(pMob[idx].MOB.MobName, "Golem Anciao"))
						continue;

					if (!strcmp(pMob[idx].MOB.MobName, "LichCrunt"))
						continue;

					if (!strcmp(pMob[idx].MOB.MobName, "Lich Batama"))
						continue;

					if (!strcmp(pMob[idx].MOB.MobName, "Espelho RainhaG"))
						continue;

					if (!strcmp(pMob[idx].MOB.MobName, "VeridRainhaG"))
						continue;

					if (!strcmp(pMob[idx].MOB.MobName, "Verid"))
						continue;

					if (!strcmp(pMob[idx].MOB.MobName, "Sombra Negra"))
						continue;

					if (!strcmp(pMob[idx].MOB.MobName, "LichVatama"))
						continue;

					if (!strcmp(pMob[idx].MOB.MobName, "Torre Guardia"))
						continue;

					if (!strcmp(pMob[idx].MOB.MobName, "Torre Guardia "))
						continue;

					if (!strcmp(pMob[idx].MOB.MobName, "Lich Infernal"))
						continue;

					if (!strcmp(pMob[idx].MOB.MobName, "Lugefer"))
						continue;

					if (!strcmp(pMob[idx].MOB.MobName, "Torre"))
						continue;

					if (!strcmp(pMob[idx].MOB.MobName, "Shama Amald"))
						continue;

					if (!strcmp(pMob[idx].MOB.MobName, "Ranger Amald"))
						continue;

					if (!strcmp(pMob[idx].MOB.MobName, "Mago Amald"))
						continue;

					if (!strcmp(pMob[idx].MOB.MobName, "Templario Amald"))
						continue;

					if (!strcmp(pMob[idx].MOB.MobName, "Ent Anciao"))
						continue;

					if (!strcmp(pMob[idx].MOB.MobName, "Guerreiro Amon"))
						continue;

					if (!strcmp(pMob[idx].MOB.MobName, "Simio Anciao"))
						continue;

					int targetLevel = pMob[idx].MOB.CurrentScore.Level; //378
					int level = pMob[a_iConn].MOB.CurrentScore.Level; //37c

					int calcLevel = 100; //380
					if (targetLevel + 10 > level)
					{
						int getCalcLevel = (targetLevel + 10) - level; //384
						calcLevel = (getCalcLevel << 2) - calcLevel;
					}

					//00432E8F
					//srand(time(NULL));
					int Rand = rand() % 100; //388
					if (Rand > calcLevel || idx < MAX_USER || pMob[idx].MOB.CurrentScore.Hp < pMob[idx].MOB.CurrentScore.MaxHp || pMob[idx].MOB.Clan == 6)
						continue;

					int j = 0;

					for (j = 0; j < MAX_PARTY; j++)
					{
						if (pMob[Leader].PartyList[j])
						{
							slot++;
							continue;
						}

						else
							break;
					}

					if (j >= MAX_PARTY)
					{
						SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Party_Full_Cant_Summon]);
						return;
					}

					RemoveParty(idx);

					memset(pMob[idx].PartyList, 0, sizeof(pMob[idx].PartyList));
					pMob[idx].MOB.BaseScore.Level = pMob[a_iConn].MOB.BaseScore.Level <= MAX_LEVEL ? pMob[a_iConn].MOB.BaseScore.Level : MAX_LEVEL;

					strcat(pMob[idx].MOB.MobName, "^");

					for (int k = 0; k < NAME_LENGTH; k++)
					{
						if (pMob[idx].MOB.MobName[k] == '_')
							pMob[idx].MOB.MobName[k] = ' ';
					}

					memset(pMob[idx].Affect, 0, sizeof(pMob[idx].Affect));

					pMob[idx].Formation = 5;

					pMob[idx].RouteType = 5;
					pMob[idx].Mode = MOB_PEACE;

					memset(&pMob[idx].SegmentX, 0, sizeof(pMob[idx].SegmentX));
					memset(&pMob[idx].SegmentY, 0, sizeof(pMob[idx].SegmentY));

					pMob[idx].Leader = Leader;

					pMob[idx].MOB.CurrentScore.Hp = pMob[idx].MOB.CurrentScore.MaxHp;
					pMob[idx].MOB.Clan = 4;

					pMob[idx].GetCurrentScore(MAX_USER);

					memset(pMob[idx].EnemyList, 0, sizeof(pMob[idx].EnemyList));

					MSG_CreateMob sm_tb;
					memset(&sm_tb, 0, sizeof(MSG_CreateMob));
					GetCreateMob(idx, &sm_tb);

					pMobGrid[pMob[idx].TargetY][pMob[idx].TargetX] = idx;

					GridMulticast(pMob[idx].TargetX, pMob[idx].TargetY, (MSG_STANDARD*)&sm_tb, 0);

					pMob[Leader].PartyList[j] = idx;
					pMob[idx].Leader = Leader;

					if (slot == 0)
						SendAddParty(Leader, Leader, 0);

					SendAddParty(idx, Leader, 0);

					if (slot == 0)
						SendAddParty(idx, idx, j + 1);

					SendAddParty(Leader, idx, j + 1);

					for (int l = 0; l < MAX_PARTY; l++)
					{
						if (pMob[Leader].PartyList[l] == 0)
							continue;

						if (pMob[Leader].PartyList[l] != idx)
							SendAddParty(pMob[Leader].PartyList[l], idx, l + 1);

						SendAddParty(idx, pMob[Leader].PartyList[l], l + 1);
					}

					pMob[idx].Summoner = a_iConn;
				}


				// Personagem
				else if (idx < MAX_USER)
				{
					//srand(time(NULL));
					int chance = (pMob[a_iConn].MOB.BaseScore.Special[1] + 1) / 7;
					int Rand = rand() % 100;

					if (Rand > chance)
					{
						int burnmp = ((pMob[idx].MOB.CurrentScore.Mp + 1) / 100) * (10 + rand() % 10);

						if (burnmp > pMob[idx].MOB.CurrentScore.Mp)
							pMob[idx].MOB.CurrentScore.Mp = 0;

						else
							pMob[idx].MOB.CurrentScore.Mp -= burnmp;

						SendSetHpMp(idx);
						SendScore(idx);
						continue;
					}

					for (int k = 0; k < MAX_AFFECT; k++)
					{
						int Type = pMob[idx].Affect[k].Type;

						if (Type == 18 || Type == 16 || Type == 14 || Type == 19 || Type == 32)
						{
							pMob[idx].Affect[k].Type = 0;
							pMob[idx].Affect[k].Value = 0;
							pMob[idx].Affect[k].Level = 0;
							pMob[idx].Affect[k].Time = 0;

							pMob[idx].GetCurrentScore(idx);
							SendScore(idx);
						}
					}

					SendEquip(idx, 0);
					pMob[idx].GetCurrentScore(idx);
					SendScore(idx);

					continue;
				}
			}

#pragma endregion
#pragma region Furia Divina
			if (skillnum == 6)
			{
				if (idx >= MAX_USER && pMob[idx].MOB.Merchant != 0)
					break;

				if (pMob[idx].MOB.Equip[0].sIndex == 219 || pMob[idx].MOB.Equip[0].sIndex == 220 || pMob[idx].MOB.Equip[0].sIndex == 362)
					break;

				if (pMob[idx].GenerateIndex == 8 || pMob[idx].GenerateIndex == 9)
					break;

				if (pMob[idx].MOB.Clan == 6)
					break;

				dam = 1;

				pMob[idx].Route[0] = 0;

				int PosX = pMob[a_iConn].TargetX;

				if (PosX < pMob[idx].TargetX)
					PosX++;

				if (PosX > pMob[idx].TargetX)
					PosX--;

				int PosY = pMob[a_iConn].TargetY;

				if (PosY < pMob[idx].TargetY)
					PosY++;

				if (PosY > pMob[idx].TargetY)
					PosY--;

				if (GetEmptyMobGrid(idx, &PosX, &PosY) == FALSE)
					break;

				int kind2 = pMob[a_iConn].MOB.CurrentScore.Special[1];

				int kindvalue = (kind2 / 10) + 20;

				if (idx > MAX_USER)
					kindvalue = (kind2 / 5) + 40;

				int leveldif = pMob[a_iConn].Extra.ClassMaster != MORTAL && pMob[a_iConn].Extra.ClassMaster != ARCH ? pMob[a_iConn].MOB.CurrentScore.Level : pMob[a_iConn].MOB.CurrentScore.Level + MAX_LEVEL - (pMob[idx].Extra.ClassMaster != MORTAL && pMob[idx].Extra.ClassMaster != ARCH ? pMob[idx].MOB.CurrentScore.Level + MAX_LEVEL : pMob[idx].MOB.CurrentScore.Level);

				leveldif = leveldif >> 2;

				int _chance = kindvalue + leveldif;

				if (_chance > 50)
					_chance = 50;

				//srand(time(NULL));
				if (rand() % 100 < _chance)
				{
					MSG_Action sm_act;
					memset(&sm_act, 0, sizeof(MSG_Action));

					GetAction(idx, PosX, PosY, &sm_act);

					sm_act.Effect = 2;
					sm_act.Speed = 6;

					GridMulticast(idx, PosX, PosY, (MSG_STANDARD*)&sm_act);

					if (idx < MAX_USER)
					{
						memset(&sm_act, 0, sizeof(MSG_Action));
						GetAction(idx, PosX, PosY, &sm_act);

						sm_act.Effect = 2;
						sm_act.Speed = 6;
						pUser[idx].cSock.AddMessage((char*)&sm_act, sizeof(MSG_Action));
					}

					if (idx >= MAX_USER)
						SetBattle(idx, a_iConn);
				}
			}
#pragma endregion
#pragma region Exterminar
			else if (skillnum == 22)
			{
				int CurrentMp = pMob[a_iConn].MOB.CurrentScore.Mp;

				pMob[a_iConn].MOB.CurrentScore.Mp = 0;
				//pUser[a_iConn].ReqMp = 0;

				m->CurrentMp = 0;

				int kind4 = pMob[a_iConn].MOB.CurrentScore.Special[3];

				int _INT = pMob[a_iConn].MOB.CurrentScore.Int;
				dam = (dam + CurrentMp) + (_INT / 2);

				int PosX = pMob[idx].TargetX;
				int PosY = pMob[idx].TargetY;

				if (GetEmptyMobGrid(a_iConn, &PosX, &PosY) != 0 && pMob[idx].MOB.Equip[0].sIndex != 219 && pMob[idx].MOB.Equip[0].sIndex != 220)
				{
					MSG_Action sm_act;
					memset(&sm_act, 0, sizeof(MSG_Action));

					GetAction(a_iConn, PosX, PosY, &sm_act);

					sm_act.Type = 2;
					sm_act.Speed = 2;

					GridMulticast(a_iConn, PosX, PosY, (MSG_STANDARD*)&sm_act);
					pUser[a_iConn].cSock.AddMessage((char*)&sm_act, sizeof(MSG_Action));
				}
			}
#pragma endregion
#pragma region Julgamento Divino
			else if (skillnum == 30)
			{
				dam = dam + hp;

				pMob[a_iConn].MOB.CurrentScore.Hp = ((pMob[a_iConn].MOB.CurrentScore.Hp) / 6) + 1;
				//pUser[a_iConn].ReqHp = pMob[a_iConn].MOB.CurrentScore.Hp;
			}
#pragma endregion
#pragma region Renascimento 
			else if (skillnum == 31)
			{
			//srand(time(NULL));
				int hp = (rand() % 10 + 10) * ((pMob[a_iConn].MOB.CurrentScore.MaxHp + 1) / 100);

				pMob[a_iConn].MOB.CurrentScore.Mp = 0;
				//pUser[a_iConn].ReqMp = 0;

				m->CurrentMp = 0;

				SendSetHpMp(a_iConn);

				//srand(time(NULL));
				if ((rand() % 100) < 70)
				{
					pMob[idx].MOB.CurrentScore.Hp = hp;
					pUser[idx].NumError = 0;
					SendScore(idx);
					SendSetHpMp(idx);
					SendEtc(idx);

					int sAffect = GetEmptyAffect(idx, 55);

					if (sAffect == -1 || pMob[idx].Affect[sAffect].Type == 55)
						continue;

					pMob[idx].Affect[sAffect].Type = 55;
					pMob[idx].Affect[sAffect].Value = 0;
					pMob[idx].Affect[sAffect].Level = 0;
					pMob[idx].Affect[sAffect].Time = 2;

					pMob[idx].GetCurrentScore(idx);
					SendScore(idx);

					MSG_CreateMob CreateMob;
					GetCreateMob(idx, &CreateMob);
					GridMulticast(pMob[idx].TargetX, pMob[idx].TargetY, (MSG_STANDARD*)&CreateMob, 0);
				}
			}
#pragma endregion
#pragma region Teleporte
			else if (skillnum == 41)
			{
				int skill_target = (Special / 25) + 2;

				if (skill_target >= MAX_TARGET)
					skill_target = MAX_TARGET;

				if (skill_target <= 1)
					skill_target = 2;

				for (int q = 0; q < skill_target && ((q < MAX_TARGET && m->Size >= sizeof(MSG_Attack)) || (q < 1 && m->Size >= sizeof(MSG_AttackOne)) || (q < 2 && m->Size >= sizeof (MSG_AttackTwo))); q++)
				{
					int targetidx = m->Dam[q].TargetID;

					if (targetidx <= MOB_EMPTY || targetidx >= MAX_USER)
						continue;

					if (pUser[targetidx].Mode != USER_PLAY)
						continue;

					if (SetAffect(targetidx, skillnum, Delay, Level) == 0)
						continue;

					SendScore(targetidx);
				}

				break;
			}
#pragma endregion
#pragma region Arma Mágica
			else if (skillnum == 44)
			{
				int skill_target = (Special / 25) + 2;

				if (skill_target >= MAX_TARGET)
					skill_target = MAX_TARGET;

				if (skill_target <= 1)
					skill_target = 2;

				for (int q = 0; q < skill_target && ((q < MAX_TARGET && m->Size >= sizeof(MSG_Attack)) || (q < 1 && m->Size >= sizeof(MSG_AttackOne)) || (q < 2 && m->Size >= sizeof (MSG_AttackTwo))); q++)
				{
					int targetidx = m->Dam[q].TargetID;
					if (targetidx <= MOB_EMPTY || targetidx >= MAX_USER)
						continue;

					if (pUser[targetidx].Mode != USER_PLAY)
						continue;

					if (SetAffect(targetidx, skillnum, Delay, Level) == 0)
						continue;

					SendScore(targetidx);
				}

				break;
			}
#pragma endregion
#pragma region Cancelamento
			else if (skillnum == 47)
			{
				int CancelContinue = 0;

				for (int k = 0; k < MAX_AFFECT; k++)
				{
					int Type = pMob[idx].Affect[k].Type;

					if (Type == 19)
					{
						pMob[idx].Affect[k].Type = 0;
						pMob[idx].Affect[k].Value = 0;
						pMob[idx].Affect[k].Level = 0;
						pMob[idx].Affect[k].Time = 0;

						pMob[idx].GetCurrentScore(idx);
						SendScore(idx);
						CancelContinue = 1;
						break;
					}
				}

				if (CancelContinue == 1)
					break;
			}
#pragma endregion
#pragma region Book Vinha
			else if (skillnum == 98)
			{
				if (m->TargetX < 0 || m->TargetX >= MAX_GRIDX || m->TargetY < 0 || m->TargetY >= MAX_GRIDY)
					break;

				unsigned char getAttribute = GetAttribute(m->TargetX, m->TargetY);
				getAttribute = getAttribute & 0x40;

				if (map_att == 0 && getAttribute == 1)
					continue;

				CreateMob("Vinha", m->TargetX, m->TargetY, "npc", 3);
				break;
			}
#pragma endregion
#pragma region Book Ressureição
			if (pMob[a_iConn].MOB.CurrentScore.Hp == 0 && skillnum == 99)
			{
				//srand(time(NULL));
				int rev = rand() % 115;

				if (rev > 100)
					rev -= 15;

				if (rev >= 40)
				{
					pMob[a_iConn].MOB.CurrentScore.Hp = 2;
					pUser[a_iConn].NumError = 0;
					SendScore(a_iConn);
					SendSetHpMp(a_iConn);
					DoRecall(a_iConn);
					SendEtc(a_iConn);
				}

				//srand(time(NULL));
				int hp = (rand() % 50 + 1) * ((pMob[a_iConn].MOB.CurrentScore.MaxHp + 1) / 100);

				pMob[a_iConn].MOB.CurrentScore.Hp = hp;
				pUser[a_iConn].NumError = 0;
				SendScore(a_iConn);
				SendSetHpMp(a_iConn);
				SendEtc(a_iConn);

				MSG_CreateMob CreateMob;
				GetCreateMob(a_iConn, &CreateMob);
				GridMulticast(pMob[a_iConn].TargetX, pMob[a_iConn].TargetY, (MSG_STANDARD*)&CreateMob, 0);
			}
#pragma endregion
#pragma region Buffs Time
			int Aggressive = g_pSpell[skillnum].Aggressive;

			int SameLeaderGuild = 1;

			if (Aggressive != 0)
			{
				if (leader == mobleader || Guild == MobGuild)
					SameLeaderGuild = 0;

				int affectresist = g_pSpell[skillnum].AffectResist;

				int idxlevel = pMob[idx].Extra.ClassMaster == MORTAL || pMob[idx].Extra.ClassMaster == ARCH ? pMob[idx].MOB.CurrentScore.Level : pMob[idx].MOB.CurrentScore.Level + MAX_LEVEL;
				int a_iConnlevel = pMob[a_iConn].Extra.ClassMaster == MORTAL || pMob[idx].Extra.ClassMaster == ARCH ? pMob[a_iConn].MOB.CurrentScore.Level : pMob[a_iConn].MOB.CurrentScore.Level + MAX_LEVEL;

				int difLevel = (idxlevel - a_iConnlevel) / 2;

				difLevel = -difLevel;

				if (affectresist >= 1 && affectresist <= 4)
				{
					//srand(time(NULL));
					int random = rand() % 100;

					if (random > pMob[idx].MOB.RegenMP + affectresist + difLevel)
						SameLeaderGuild = 0;
				}

				if ((pMob[idx].MOB.Rsv & 0x80) != FALSE)
					SameLeaderGuild = 0;

				if (a_iConn < MAX_USER && pMob[idx].MOB.Clan == 6)
					SameLeaderGuild = 0;
			}



#pragma region Time
			if (SameLeaderGuild)
			{
				if (skillnum == 102)
				{
					if (pMob[a_iConn].Extra.ClassMaster == MORTAL)
						Delay = 200;

					else if (pMob[a_iConn].Extra.ClassMaster != MORTAL && pMob[a_iConn].Extra.ClassMaster != ARCH)
					{
						Delay = 200;

						if (pMob[a_iConn].MOB.CurrentScore.Level < 39)
							Delay -= (39 - (pMob[a_iConn].MOB.CurrentScore.Level)) * 4;

						else if (pMob[a_iConn].MOB.CurrentScore.Level >= 199)
							Delay = 400;

						else
							Delay = 200;
					}
				}

				if (SetAffect(idx, skillnum, Delay, Special) != 0)
					UNK2 = TRUE;

				if (SetTick(idx, skillnum, Delay, Special) != 0)
					UNK2 = TRUE;

				if (UNK2 != FALSE)
				{
					pMob[idx].GetCurrentScore(idx);
					SendScore(idx);
				}
			}

#pragma endregion
#pragma endregion
#pragma region Transformações
			if (skillnum == 64 || skillnum == 66 || skillnum == 68 || skillnum == 70 || skillnum == 71)
			{
				pMob[a_iConn].GetCurrentScore(a_iConn);
				SendScore(a_iConn);
				SendEquip(a_iConn, 0);
			}
#pragma endregion
#pragma endregion

		}
#pragma endregion

		else
		{
			MyLog(LogType::Attack, pUser[a_iConn].AccountName, "err,dam not -2 -1 MSG_ATTACK", 0, pUser[a_iConn].IP);
			return;
		}

		m->Dam[i].Damage = (int)dam;

		if (dam <= 0)
			continue;

#pragma region Perfuração		   
		if (idx < MAX_USER || pMob[idx].MOB.Clan == 4)
		{
			if ((m->DoubleCritical & 4) != 0)
				dam = m->Dam[1].Damage + (dam >> 2);

			else
				dam = dam >> 2;
		}

		if (pMob[a_iConn].ForceDamage != 0)
		{
			if (dam <= 1)
				dam = pMob[a_iConn].ForceDamage;

			else if (dam > 0)
				dam = dam + pMob[a_iConn].ForceDamage;

			m->Dam[i].Damage = (int)dam;
		}
#pragma endregion
#pragma region Ataque PvP
		if (pMob[a_iConn].PvPDamage != 0 && idx < MAX_USER)
		{
			if (dam <= 1)
				dam += (dam * pMob[a_iConn].PvPDamage / 100);

			else if (dam > 0)
				dam += (dam / 100 * pMob[a_iConn].PvPDamage);

			m->Dam[i].Damage = (int)dam;
		}
#pragma endregion
#pragma region PK
		if (leader == mobleader || Guild == MobGuild)
			dam = 0;

		if (idx >= MAX_USER && isFrag != FALSE)
			dam = 0;

		int Summoner = idx;

		if (idx >= MAX_USER && pMob[idx].MOB.Clan == 4 && pMob[idx].Summoner > 0 && pMob[idx].Summoner < MAX_USER && pUser[pMob[idx].Summoner].Mode == USER_PLAY)
			Summoner = pMob[idx].Summoner;

		if (Summoner < MAX_USER)
		{
			int pointPK = GetPKPoint(a_iConn);
			int SummonerPointPK = GetPKPoint(Summoner);

			int arena = BASE_GetArena(pMob[a_iConn].TargetX, pMob[a_iConn].TargetY);
			int village = BASE_GetVillage(pMob[a_iConn].TargetX, pMob[a_iConn].TargetY);

			int mapX = pMob[a_iConn].TargetX >> 7;
			int mapY = pMob[a_iConn].TargetY >> 7;

			int MapPK = 0;
			int isWar = 0;

			int a_iConnGuild = pMob[a_iConn].MOB.Guild;
			int SummonerGuild = pMob[Summoner].MOB.Guild;
			int maxguild = 65536;

			if (a_iConnGuild > 0 && a_iConnGuild < maxguild && SummonerGuild > 0 && SummonerGuild < maxguild && g_pGuildWar[a_iConnGuild] == SummonerGuild && g_pGuildWar[SummonerGuild] == a_iConnGuild)
				isWar = 1;

			if (CastleState != 0 && mapX == 8 && mapY == 13)
				isWar = 1;

			if (mapX == 1 && mapY == 31 || mapX == 19 && mapY == 30)//define o mapa que o jogador vai ficar pk
				MapPK = 1;


			if (arena == MAX_GUILDZONE && village == MAX_GUILDZONE && MapPK == FALSE && isWar == FALSE)
			{
				if (pointPK <= 10 && SummonerPointPK > 10)
				{
					sprintf(temp, g_pMessageStringTable[_DN_CantKillUser], pointPK);
					SendClientMsg(a_iConn, temp);
					dam = 0;
				}
				else if (SummonerPointPK > 10 && dam > 0 || skillnum == 6)
				{
					int Guilty = GetGuilty(a_iConn);
					SetGuilty(a_iConn, 8);

					if (Guilty == 0)
					{
						MSG_CreateMob mob;
						GetCreateMob(a_iConn, &mob);
						GridMulticast(pMob[a_iConn].TargetX, pMob[a_iConn].TargetY, (MSG_STANDARD*)&mob, 0);
					}
				}
			}
#pragma endregion
#pragma region Miss
			if (idx != a_iConn)
			{
				//srand(time(NULL));
				int Pop = rand() % 100;
				int parryretn = GetAttackMiss(a_iConn, idx);

				if (Pop < GetAttackMiss(a_iConn, idx))
				{
					dam = -3;
				}

				/* Espelho Mágico */
				if (pMob[a_iConn].Extra.SecLearnedSkill & 0x100)
				{
					int Special = (pMob[a_iConn].MOB.CurrentScore.Special[3] / 2);

					parryretn -= Special;
				}

#pragma region Not Usage
				//int attackdex = pMob[a_iConn].MOB.CurrentScore.Dex / 5;

				//if (pMob[a_iConn].MOB.LearnedSkill & 0x1000000)
				//	attackdex += 100;

				//if (pMob[a_iConn].MOB.Rsv & 0x40)
				//	attackdex += 500;

				//int parryretn = GetParryRate(&pMob[idx].MOB, pMob[idx].Parry, attackdex, pMob[a_iConn].MOB.Rsv);

				//if (skillnum == 79 || skillnum == 22)
				//	parryretn = 30 * parryretn / 100;

				//int rd = rand() % 1000 + 1;

				//if (rd < parryretn)
				//{
				//	dam = -3;

				//	if ((pMob[idx].MOB.Rsv & 0x200) != 0 && rd < 100)
				//		dam = -4;
				//}  
#pragma endregion

			}
#pragma endregion
		}

		/* Proteção Divina */
		if (pMob[idx].MOB.Class == 0) 
		{
			for (int i = 0; i < MAX_AFFECT; i++)
			{
				if (pMob[idx].Affect[i].Type == 6 && dam > 0)
					dam = 0;
			}
		}

		/* Proteção Absoluta */
		if (pMob[idx].MOB.Class == 1) 
		{
			for (int i = 0; i < MAX_AFFECT; i++)
			{
				if (pMob[idx].Affect[i].Type == 6 && dam > 0)
					dam = 0;
			}
		}
		if (pMob[idx].MOB.Clan == 6 && Level < MAX_LEVEL)
			dam = 0;

		if (idx > MAX_USER && dam >= 1)
			dam += pMob[a_iConn].ForceMobDamage;

		if (dam >= MAX_DAMAGE)
			dam = MAX_DAMAGE;

		m->Dam[i].Damage = (int)dam;

		if (dam <= 0)
			continue;

		if ((pMob[a_iConn].MOB.Rsv & RSV_FROST) != 0)
		{
			//srand(time(NULL));
			if (rand() % 2 == 0)
			{
				int skind2 = pMob[a_iConn].MOB.CurrentScore.Special[1];

				if (SetAffect(idx, 36, skind2 + 150, skind2) != 0)
					SendScore(idx);

				if (SetTick(idx, 36, skind2 + 150, skind2) != 0)
					SendScore(idx);
			}
		}

		if ((pMob[a_iConn].MOB.Rsv & RSV_DRAIN) != 0)
		{
			//srand(time(NULL));
			if (rand() % 2 == 0)
			{
				int skind2 = pMob[a_iConn].MOB.CurrentScore.Special[1];

				if (SetAffect(idx, 40, skind2 + 150, skind2) != 0)
					SendScore(idx);

				if (SetTick(idx, 40, skind2 + 150, skind2) != 0)
					SendScore(idx);
			}
		}

		if (idx > 0 && idx < MAX_USER && dam > 0)
		{
			if (pMob[idx].ReflectDamage > 0)
				dam = dam - pMob[idx].ReflectDamage;

			if (dam <= 0)
				dam = 1;

			for (size_t buff = 0; buff < MAX_AFFECT; buff++)
			{
				if (pMob[a_iConn].Affect[buff].Type == 8)
				{
					int master = pMob[a_iConn].Affect[buff].Level;
					if (master & (1 << 6))//bonus precisão
						pMob[idx].Parry -= 30;
				}
			}


			if (pMob[idx].ReflectPvP > 0)
				dam = dam - (dam / 100 * pMob[idx].ReflectPvP);

			if (dam <= 0)
				dam = 1;

			m->Dam[i].Damage = (int)dam;
		}

		if (pMob[a_iConn].TargetX >= 1017 && pMob[a_iConn].TargetX <= 1290 && pMob[a_iConn].TargetY >= 1911 && pMob[a_iConn].TargetY <= 2183 && dam > 0 && pMob[a_iConn].MOB.Clan == pMob[idx].MOB.Clan)
		{
			m->Dam[i].Damage = 0;
			m->Dam[i].TargetID = 0;

			continue;
		}

		if (idx < MAX_USER && a_iConn < MAX_USER)
		{
			if (pMob[idx].TargetX >= AREA_RVR_MINX && pMob[idx].TargetX <= AREA_RVR_MAXX &&
				pMob[idx].TargetY >= AREA_RVR_MINY && pMob[idx].TargetY <= AREA_RVR_MAXY && g_pRvrWar.Status == 1)
			{
				if (pMob[idx].MOB.Clan == pMob[a_iConn].MOB.Clan)
				{
					dam = 0;
					m->Dam[i].TargetID = 0;
					m->Dam[i].Damage = 0;
				}
			}
		}

		int _pDamage = (int)dam;
		int _calcDamage = 0;
		int pTargetMountId = pMob[idx].MOB.Equip[14].sIndex;

		if (idx < MAX_USER && pTargetMountId >= 2360 && pTargetMountId < 2390 && pMob[idx].MOB.Equip[14].stEffect[0].sValue > 0)
		{

			_pDamage = (int)((dam * 3) >> 2);
			_calcDamage = (int)(dam - _pDamage);
			if (_pDamage <= 0)
				_pDamage = 1;

			m->Dam[i].Damage = _pDamage;
		}

#pragma region Controle de Mana
		int tDamage = _pDamage;

		for (int c = 0; c < MAX_AFFECT; c++)
		{
			if (pMob[idx].Affect[c].Type == 18)
			{
				if (pMob[idx].MOB.CurrentScore.Mp >((pMob[idx].MOB.CurrentScore.MaxMp / 100) * 20))
				{
					int mana = pMob[idx].MOB.CurrentScore.Mp - tDamage;

					if (mana < 0)
					{
						tDamage -= mana;
						mana = 0;
					}

					pMob[idx].MOB.CurrentScore.Mp = mana;

					SendSetHpMp(idx);
					 
					int abs = (1 << 23) & pMob[a_iConn].MOB.LearnedSkill ? 55 : 60;

					tDamage = ((tDamage >> 1) + (tDamage << 4)) / abs;
					m->Dam[i].Damage = tDamage;

					if ((DoubleCritical & 4) != FALSE)
						m->Dam[1].Damage = tDamage;
					break;
				}
			}
		}
#pragma endregion

		if (!strcmp(pMob[idx].MOB.MobName, "Zard"))
		{
			pMob[a_iConn].MOB.Equip[12].EF1 = 51;
			pMob[a_iConn].MOB.Equip[12].EFV1 += 1;

			SendClientSignalParm(a_iConn, ESCENE_FIELD, _MSG_MobLeft, pMob[a_iConn].MOB.Equip[12].EFV1);

			if (pMob[a_iConn].MOB.Equip[12].EFV1 == 80)
			{
				STRUCT_ITEM Runa;
				memset(&Runa, 0, sizeof(STRUCT_ITEM));

				Runa.sIndex = 475;
				PutItem(a_iConn, &Runa);
				pMob[a_iConn].MOB.Equip[12].EFV1 = 0;
			}

			dam = 0;
		}

		if (pMob[a_iConn].MOB.Class == 1 || pMob[a_iConn].MOB.Class == 3)
		{
			bool isFlag = false;
			 bool ativaFlag = false;//desativar flag ranger quests

			//Coveiro
			if (pMob[a_iConn].TargetX >= 2379 && pMob[a_iConn].TargetY >= 2076 && pMob[a_iConn].TargetX <= 2426 && pMob[a_iConn].TargetY <= 2133)
				isFlag = true;

			//Jardin
			if (pMob[a_iConn].TargetX > 2228 && pMob[a_iConn].TargetY > 1700 && pMob[a_iConn].TargetX < 2257 && pMob[a_iConn].TargetY < 1728)
				isFlag = true;

			//Kaizen
			if (pMob[a_iConn].TargetX > 459 && pMob[a_iConn].TargetY > 3887 && pMob[a_iConn].TargetX < 497 && pMob[a_iConn].TargetY < 3916)
				isFlag = true;

			//Hidra
			if (pMob[a_iConn].TargetX > 658 && pMob[a_iConn].TargetY > 3728 && pMob[a_iConn].TargetX < 703 && pMob[a_iConn].TargetY < 3762)
				isFlag = true;

			//Elfos
			if (pMob[a_iConn].TargetX > 1312 && pMob[a_iConn].TargetY > 4027 && pMob[a_iConn].TargetX < 1348 && pMob[a_iConn].TargetY < 4055)
				isFlag = true;

			if(isFlag == true && ativaFlag == true)
			{
			if (g_pItemList[pMob[a_iConn].MOB.Equip[6].sIndex].nUnique == 42)
				{
					for (i = 0; i < pMob[a_iConn].MaxCarry; i++)
					{
						if (pMob[a_iConn].MOB.Carry[i].sIndex == 5572)
							break;
					}

					if (i != pMob[a_iConn].MaxCarry)
					{
						int amount = BASE_GetItemAmount(&pMob[a_iConn].MOB.Carry[i]);

						if (amount > 1)
							BASE_SetItemAmount(&pMob[a_iConn].MOB.Carry[i], amount - 1);
						else
							BASE_ClearItem(&pMob[a_iConn].MOB.Carry[i]);

						SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);
					}

					else
					{
						SendClientMsg(a_iConn, "Não possui flexas suficientes.");
						return;
					}
				}
			}
		}
				

		if (pMob[idx].MOB.Equip[13].sIndex == 786)
		{

			int itemSanc = pMob[idx].MOB.Equip[13].stEffect[0].cValue;
			if (itemSanc < 2)
				itemSanc = 2;


			tDamage = _pDamage / itemSanc;
			if (tDamage > pMob[idx].MOB.CurrentScore.Hp)
				tDamage = pMob[idx].MOB.CurrentScore.Hp;

			pMob[idx].MOB.CurrentScore.Hp = pMob[idx].MOB.CurrentScore.Hp - tDamage;
		}

		else if (pMob[idx].MOB.Equip[13].sIndex == 1936)//10X HP MONSTRO
		{

			int itemSanc = pMob[idx].MOB.Equip[13].stEffect[0].cValue;
			if (itemSanc < 2)
				itemSanc = 2;

			itemSanc *= 10;

			tDamage = _pDamage / itemSanc;

			if (tDamage > pMob[idx].MOB.CurrentScore.Hp)
				tDamage = pMob[idx].MOB.CurrentScore.Hp;

			pMob[idx].MOB.CurrentScore.Hp = pMob[idx].MOB.CurrentScore.Hp - tDamage;
		}

		else if (pMob[idx].MOB.Equip[13].sIndex == 1937)//20X HP MONSTRO
		{
			int itemSanc = pMob[idx].MOB.Equip[13].stEffect[0].cValue;
			if (itemSanc < 2)
				itemSanc = 2;

			itemSanc *= 1000;

			tDamage = _pDamage / itemSanc;

			if (tDamage > pMob[idx].MOB.CurrentScore.Hp)
				tDamage = pMob[idx].MOB.CurrentScore.Hp;

			pMob[idx].MOB.CurrentScore.Hp = pMob[idx].MOB.CurrentScore.Hp - tDamage;
		}

		else
		{
			if (tDamage > pMob[idx].MOB.CurrentScore.Hp)
				tDamage = pMob[idx].MOB.CurrentScore.Hp;


			pMob[idx].MOB.CurrentScore.Hp = pMob[idx].MOB.CurrentScore.Hp - tDamage;
		}


		if (_calcDamage > 0)
			ProcessAdultMount(idx, _calcDamage / 2);

		if (LOCALSERVER != 0)
		{
			sprintf(temp, "%s: %d(%d) - %d", pMob[idx].MOB.MobName, _pDamage, tDamage, pMob[idx].MOB.CurrentScore.Hp);
			SendSay(idx, temp);
		}


		if (idx > 0 && idx < MAX_USER)
		{
			//pUser[idx].ReqHp = pUser[idx].ReqHp - tDamage;

			SetReqHp(idx);
		}
		sprintf(temp, "etc,msg_attack attacker:%d name:%s target:%d name:%s dam:%d x:%d y:%d", a_iConn, pMob[a_iConn].MOB.MobName, idx, pMob[idx].MOB.MobName, m->Dam[i].Damage, pMob[idx].TargetX, pMob[idx].TargetY);
		MyLog(LogType::Attack, pUser[a_iConn].AccountName, temp, 0, pUser[a_iConn].IP);

		if (idx > MAX_USER && pMob[idx].MOB.Clan == 4)
			LinkMountHp(idx);

#pragma region Joia Abs
		if (dam >= 1)
		{
			for (size_t buff = 0; buff < MAX_AFFECT; buff++)
			{
				if (pMob[a_iConn].Affect[buff].Type == 8)
				{
					int master = pMob[a_iConn].Affect[buff].Level;
					if (master & (1 << 3))//bonus Abs
					{
						int hpAtual = pMob[a_iConn].MOB.CurrentScore.Hp;
						int maxHpAtual = pMob[a_iConn].MOB.CurrentScore.MaxHp;
						int RecHP = (int)((dam * 2) / 100);

						if (RecHP > 350)
							RecHP = 350;

						if (hpAtual >= maxHpAtual)
							RecHP = 0;

						int newHP = pMob[a_iConn].MOB.CurrentScore.Hp + RecHP;

						if (newHP > maxHpAtual)	
						{
							newHP -= maxHpAtual;
							RecHP = newHP;
						}

						pMob[a_iConn].MOB.CurrentScore.Hp += RecHP;

			
					}
				}
			}
			
		}
#pragma endregion

		if (skillnum == 79)
		{
			SendSetHpMp(idx);
		}

		if (pMob[idx].MOB.CurrentScore.Hp <= 0)
		{
			pMob[idx].MOB.CurrentScore.Hp = 0;
			TargetKilled[i] = idx;
			continue;
		}

		if (pMob[idx].Mode != MOB_EMPTY && pMob[idx].MOB.CurrentScore.Hp > 0)
		{
			SetBattle(idx, a_iConn);

			pMob[a_iConn].CurrentTarget = idx;

			int mleader = pMob[a_iConn].Leader;
			if (mleader <= MOB_EMPTY)
				mleader = a_iConn;

			int r = 0;
			for (r = MOB_EMPTY; r < MAX_PARTY; r++)
			{
				int partyMemberId = pMob[mleader].PartyList[r];
				if (partyMemberId <= MAX_USER)
					continue;

				if (pMob[partyMemberId].Mode == MOB_EMPTY || pMob[partyMemberId].MOB.CurrentScore.Hp <= 0)
				{
					if (pMob[partyMemberId].Mode != MOB_EMPTY)
						DeleteMob(partyMemberId, 1);

					pMob[mleader].PartyList[r] = MOB_EMPTY;
				}
				else
					SetBattle(partyMemberId, idx);
			}
#pragma region Boss Sombra Negra
			if (!strcmp(pMob[idx].MOB.MobName, "Sombra Negra "))
			{
				checkHPBoss(idx);
			}
#pragma endregion

#pragma region Boss Camp
			for (size_t i = 0; i < MAX_BOSS_CAMP; i++)
			{
				if (!strcmp(pMob[idx].MOB.MobName, bossCamp[i].Boss.NAME.c_str()))
					checkHPBossCamp(idx, i);
			}
#pragma endregion

			mleader = pMob[idx].Leader;
			if (mleader <= 0)
				mleader = idx;

			for (r = 0; r < MAX_PARTY; r++)
			{
				int ptMemberId = pMob[mleader].PartyList[r];
				if (ptMemberId <= MAX_USER)
					continue;

				if (pMob[ptMemberId].Mode == MOB_EMPTY || pMob[ptMemberId].MOB.CurrentScore.Hp <= 0)
				{
					if (pMob[ptMemberId].Mode != MOB_EMPTY)
						DeleteMob(ptMemberId, 1);

					pMob[mleader].PartyList[r] = MOB_EMPTY;
				}
				else
					SetBattle(ptMemberId, a_iConn);
			}
		}

	}
#pragma endregion

	if (UNK2 > 0)
		Exp = UNK2;

	//if (DOUBLEMODE)
		Exp = Exp * DOUBLEMODE;

	if (Exp <= 0)
		Exp = 0;

	if (Exp > 200)
		Exp = 200;

	//Espectral
	if ((pMob[a_iConn].MOB.LearnedSkill & (1 << 29)) != 0)
		m->DoubleCritical = m->DoubleCritical | 8;

	m->CurrentExp = pMob[a_iConn].MOB.Exp;
	m->CurrentHp = pMob[a_iConn].MOB.CurrentScore.Hp;
	m->CurrentMp = pMob[a_iConn].MOB.CurrentScore.Mp;
	m->ReqMp = m->CurrentMp;

	if (ClientTick == SKIPCHECKTICK)
		m->ClientTick = CurrentTime;

	if (skillnum != 102)
		GridMulticast(pMob[a_iConn].TargetX, pMob[a_iConn].TargetY, (MSG_STANDARD*)m, 0);

	if (skillnum == 30)
		SendSetHpMp(a_iConn);


#pragma region MobKilled Check
	for (int i = 0; i < MAX_TARGET; i++)
	{
		if (TargetKilled[i] > 0 && TargetKilled[i] < MAX_MOB && pMob[TargetKilled[i]].Mode != MOB_EMPTY)
			MobKilled(TargetKilled[i], a_iConn, 0, 0);
	}
#pragma endregion
#pragma region Level Check

	int Segment = pMob[a_iConn].CheckGetLevel();

	if (Segment >= 1 && Segment <= 4)
	{
		if (Segment == 4)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Level_Up]);
			SetCircletSubGod(a_iConn);
			TitleNotification(a_iConn, pMob[a_iConn].MOB.CurrentScore.Level);

			if (pMob[a_iConn].Extra.ClassMaster == MORTAL)
				DoItemLevel(a_iConn);
		}

		if (Segment == 3)
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_3_Quarters_Bonus]);

		if (Segment == 2)
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_2_Quarters_Bonus]);

		if (Segment == 1)
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_1_Quarters_Bonus]);

		SendScore(a_iConn);
		SendEmotion(a_iConn, 14, 3);

		if (Segment == 4)
		{
			SendEtc(a_iConn);

			int PKPoint = GetPKPoint(a_iConn) + 5;
			SetPKPoint(a_iConn, PKPoint);

			MSG_CreateMob sm_lup;
			memset(&sm_lup, 0, sizeof(MSG_CreateMob));
			GetCreateMob(a_iConn, &sm_lup);

			GridMulticast(pMob[a_iConn].TargetX, pMob[a_iConn].TargetY, (MSG_STANDARD*)&sm_lup, 0);

			sprintf(temp, "lvl %s level up to %d", pMob[a_iConn].MOB.MobName, pMob[a_iConn].MOB.BaseScore.Level);
			MyLog(LogType::Attack, pUser[a_iConn].AccountName, temp, 0, pUser[a_iConn].IP);

		}
	}
#pragma endregion

}
