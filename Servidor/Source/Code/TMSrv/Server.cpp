//#include "DialogConfigExtra.h"
#include <Windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>
#include <io.h>
#include <errno.h>
#include <inttypes.h>

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
#include "CReadFiles.h"
#include "WarOfTower.h"
#include "../ConfigIni.h"
#include "WarOfNoatum.h"
#include "CNPCGene.h"
#include "SombraNegra.h"
#include "WarOfKingdom.h"
#include "BossCamp.h"
#include "AccountBuff.h"
//#include "../../../../../../../Program Files (x86)/Windows Kits/10/Include/10.0.17763.0/um/timeapi.h"
#include "resource.h"



#pragma region Defines

int TowerCount = 0;
int TowerStage = 0;
int notWarNoatum = FALSE;
int playerAltar;
int countAltarDec = 0;
int GuildTower = 0;
int GuildScore[MAX_GUILD];
int LoadTerritory = FALSE;
BOOL StartImpost = FALSE;
short RandTorreRed[4][2]{ 
						  {1684, 2014},
						  {1712, 2014},
						  {1712, 1948},
						  {1684, 1949} 
						};
short RandTorreBlue[4][2]{
						  {1739, 2011},
						  {1768, 2011},
						  {1763, 1948},
						  {1744, 1949}
						 };
using ConfigIni::nConfig;

int ServerDown = -1000;

int g_EmptyMob = MAX_USER;

int ServerIndex = -1;
//int Sapphire = 8; transferido para o basedef
int ServerGroup = -1;
int GuildCounter = 1;

STRUCT_GUARD g_pGuard[MAX_NPC_GUARD_COUT];

std::string TerritoryName[MAX_TERRITORY]
{
	"Arima",
	"Barnel",
	"Campus",
	"Gobi",
	"IceCrow"
};

STRUCT_QUEST QuestDiaria[36];
int BigCubo = 1;

void CreateExportInspectTable(int conn)
{
	if (conn <= 0 || conn >= MAX_USER || pUser[conn].Mode != USER_PLAY) return;

	try
	{
		const char* dir = "../../MaskTable/Inspect/%s";
		/*testing*/
		auto mob = pMob[conn].MOB;
		auto extra = pMob[conn].Extra;
		auto sk = pUser[conn].CharShortSkill;
		

		FILE *fp = NULL;

		char cast[256];

		sprintf(cast, dir, mob.MobName);

		fp = fopen(cast, "wt");

		if (fp == NULL) return;

		int guild = mob.Guild;

		char guildname[256];

		if (guild > 0)
		{
			int Group = ServerGroup;
			int Server = guild / MAX_GUILD;
			BASE_GetGuildName(Group, guild, guildname);
		}

		fprintf(fp, "%s,%d,%d,%d,%d,%d,%d\n", mob.MobName, 0, mob.CurrentScore.MaxHp, mob.CurrentScore.MaxMp, mob.Critical, 0, mob.CurrentScore.AttackRun & 15);
		fprintf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n", mob.Equip[0].sIndex, mob.Equip[1].sIndex, mob.Equip[2].sIndex, mob.Equip[3].sIndex, mob.Equip[4].sIndex, mob.Equip[5].sIndex, mob.Equip[6].sIndex, mob.Equip[7].sIndex, mob.Equip[8].sIndex, mob.Equip[9].sIndex, mob.Equip[10].sIndex, mob.Equip[11].sIndex, mob.Equip[12].sIndex, mob.Equip[13].sIndex, mob.Equip[14].sIndex, mob.Equip[15].sIndex);
		fprintf(fp, "%d,%d,%d,%d,%d,%s,%d\n", GetCurKill(conn), extra.Fame, mob.CurrentScore.Level, mob.Class, extra.ClassMaster, guild <= 0 ? "*" : guildname, mob.GuildLevel);
		fprintf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", mob.SkillBar[0], mob.SkillBar[1], mob.SkillBar[2], mob.SkillBar[3], sk[0], sk[1], sk[2], sk[3], sk[4], sk[5], sk[6], sk[7], sk[8], sk[9], sk[10], sk[11], sk[12], sk[13], sk[14], sk[15]);

		fclose(fp);
	}
	catch (...)
	{

	}
}

void BASE_ReadQuestDiaria()
{
	FILE* fp = fopen("QuestDiaria.txt", "rb");

	if (fp == NULL)
	{
		MessageBoxA(NULL, "Não foi possível carregar o arquivo 'QuestDiaria.txt'", "TMSRV", MB_OK);

		return;
	}

	int count = 0;

	while (fscanf(fp, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
		&QuestDiaria[count].IndexQuest,
		&QuestDiaria[count].Nivel,
		&QuestDiaria[count].IdMob1, &QuestDiaria[count].QtdMob1,
		&QuestDiaria[count].IdMob2, &QuestDiaria[count].QtdMob2,
		&QuestDiaria[count].IdMob3, &QuestDiaria[count].QtdMob3,
		&QuestDiaria[count].ExpReward,
		&QuestDiaria[count].GoldReward,
		&QuestDiaria[count].Item->sIndex,
		&QuestDiaria[count].Item->stEffect[0].cEffect,
		&QuestDiaria[count].Item->stEffect[0].cValue,
		&QuestDiaria[count].Item->stEffect[1].cEffect,
		&QuestDiaria[count].Item->stEffect[1].cValue,
		&QuestDiaria[count].Item->stEffect[2].cEffect,
		&QuestDiaria[count].Item->stEffect[2].cValue) != EOF && count < 7)
		count++;

	fclose(fp);
}

void BASE_ReadGuardFile()
{
	FILE* fp = fopen("Guard.txt", "rb");

	if (fp == NULL)
	{
		MessageBoxA(NULL, "Não foi possível carregar o arquivo 'Guard.txt'", "TMSRV", MB_OK);

		return;
	}

	try
	{
		char Buffer[1024];

		while (TRUE)
		{
			char *ptr = fgets((char*)Buffer, 1024, fp);

			if (ptr == NULL) break;

			bool FlagTemp = false;

			for (int o = 0; o < 1024; o++)
			{
				if (ptr[o] == ',') { ptr[o] = ' '; }
				if (ptr[o] == '[') { break; }
			}

			if (ptr[0] == '#') continue;

			/* Guard Index */
			int i = -1;

			/* Sub Category (Can't Modify) */

			int j = -1;

			/* Ratting */

			int AR = -1;
			int BR = -1;
			int CR = -1;
			int DR = -1;
			int ER = -1;
			int FR = -1;

			/* Required */

			int y = -1;

			/* ----------------------------------------------------- */

			int A = 0, A1 = 0, AV1 = 0, A2 = 0, AV2 = 0, A3 = 0, AV3 = 0;
			int B = 0, B1 = 0, BV1 = 0, B2 = 0, BV2 = 0, B3 = 0, BV3 = 0;
			int C = 0, C1 = 0, CV1 = 0, C2 = 0, CV2 = 0, C3 = 0, CV3 = 0;
			int D = 0, D1 = 0, DV1 = 0, D2 = 0, DV2 = 0, D3 = 0, DV3 = 0;
			int E = 0, E1 = 0, EV1 = 0, E2 = 0, EV2 = 0, E3 = 0, EV3 = 0;

			int Parm1, Parm2, Parm3, Parm4;

			sscanf(Buffer, "%d %d %d %d %d %d[%d,%d,%d,%d,%d,%d,%d,%d][%d,%d,%d,%d,%d,%d,%d,%d][%d,%d,%d,%d,%d,%d,%d,%d][%d,%d,%d,%d,%d,%d,%d,%d][%d,%d,%d,%d,%d,%d,%d,%d]",

				&i, &y, &Parm1, &Parm2, &Parm3, &Parm4,

				&A,

				&A1, &AV1,
				&A2, &AV2,
				&A3, &AV3,

				&AR,

				&B,

				&B1, &BV1,
				&B2, &BV2,
				&B3, &BV3,

				&BR,

				&C,

				&C1, &CV1,
				&C2, &CV2,
				&C3, &CV3,

				&CR,

				&D,

				&D1, &DV1,
				&D2, &DV2,
				&D3, &DV3,

				&DR,

				&E,

				&E1, &EV1,
				&E2, &EV2,
				&E3, &EV3,

				&ER

				);

			if (i < FALSE || i >= MAX_NPC_GUARD_COUT)	continue;

			//if (j < FALSE || j >= MAX_NPC_GUARD_ITEM)	continue;

			if (y < -1 || y >= MAX_ITEMLIST)				continue;

			g_pGuard[i].Req.Parm0 = y;

			g_pGuard[i].Req.Parm1 = Parm1;
			g_pGuard[i].Req.Parm2 = Parm2;
			g_pGuard[i].Req.Parm3 = Parm3;
			g_pGuard[i].Req.Parm4 = Parm4;

			g_pGuard[i].Sub.Item[0].sIndex = A;

			g_pGuard[i].Sub.Item[0].stEffect[0].cEffect = A1;
			g_pGuard[i].Sub.Item[0].stEffect[0].cValue = AV1;

			g_pGuard[i].Sub.Item[0].stEffect[1].cEffect = A2;
			g_pGuard[i].Sub.Item[0].stEffect[1].cValue = AV2;

			g_pGuard[i].Sub.Item[0].stEffect[2].cEffect = A3;
			g_pGuard[i].Sub.Item[0].stEffect[2].cValue = AV3;

			g_pGuard[i].Sub.Ratting[0] = AR /*<= FALSE ? FALSE : AR*/;

			g_pGuard[i].Sub.Item[1].sIndex = B;

			g_pGuard[i].Sub.Item[1].stEffect[0].cEffect = B1;
			g_pGuard[i].Sub.Item[1].stEffect[0].cValue = BV1;

			g_pGuard[i].Sub.Item[1].stEffect[1].cEffect = B2;
			g_pGuard[i].Sub.Item[1].stEffect[1].cValue = BV2;

			g_pGuard[i].Sub.Item[1].stEffect[2].cEffect = B3;
			g_pGuard[i].Sub.Item[1].stEffect[2].cValue = BV3;

			g_pGuard[i].Sub.Ratting[1] = BR/* <= FALSE ? FALSE : BR*/;

			g_pGuard[i].Sub.Item[2].sIndex = C;

			g_pGuard[i].Sub.Item[2].stEffect[0].cEffect = C1;
			g_pGuard[i].Sub.Item[2].stEffect[0].cValue = CV1;

			g_pGuard[i].Sub.Item[2].stEffect[1].cEffect = C2;
			g_pGuard[i].Sub.Item[2].stEffect[1].cValue = CV2;

			g_pGuard[i].Sub.Item[2].stEffect[2].cEffect = C3;
			g_pGuard[i].Sub.Item[2].stEffect[2].cValue = CV3;

			g_pGuard[i].Sub.Ratting[2] = CR /*<= FALSE ? FALSE : CR*/;

			g_pGuard[i].Sub.Item[3].sIndex = D;

			g_pGuard[i].Sub.Item[3].stEffect[0].cEffect = D1;
			g_pGuard[i].Sub.Item[3].stEffect[0].cValue = DV1;

			g_pGuard[i].Sub.Item[3].stEffect[1].cEffect = D2;
			g_pGuard[i].Sub.Item[3].stEffect[1].cValue = DV2;

			g_pGuard[i].Sub.Item[3].stEffect[2].cEffect = D3;
			g_pGuard[i].Sub.Item[3].stEffect[2].cValue = DV3;

			g_pGuard[i].Sub.Ratting[3] = DR/* <= FALSE ? FALSE : DR*/;

			g_pGuard[i].Sub.Item[4].sIndex = E;

			g_pGuard[i].Sub.Item[4].stEffect[0].cEffect = E1;
			g_pGuard[i].Sub.Item[4].stEffect[0].cValue = EV1;

			g_pGuard[i].Sub.Item[4].stEffect[1].cEffect = E2;
			g_pGuard[i].Sub.Item[4].stEffect[1].cValue = EV2;

			g_pGuard[i].Sub.Item[4].stEffect[2].cEffect = E3;
			g_pGuard[i].Sub.Item[4].stEffect[2].cValue = EV3;

			g_pGuard[i].Sub.Ratting[4] = ER/* <= FALSE ? FALSE : ER*/;
		}
	}
	catch (...)
	{

	}

	fclose(fp);
}

int ValidGuild = MAX_GUILDZONE;
int WaterScrollPosition[3][10][2] = 
{
	{//N
		{ 1121, 3554 },//LV1
		{ 1085, 3554 },//2
		{ 1049, 3554 },//3
		{ 1049, 3518 },//4
		{ 1049, 3482 },//5
		{ 1085, 3482 },//6
		{ 1121, 3482 },//7
		{ 1121, 3518 },//8
		{ 1085, 3518 },
		{ 1085, 3518 }
	},
	{//M
		{ 1250, 3682 },//LV1
		{ 1214, 3682 },//2
		{ 1178, 3682 },//3
		{ 1178, 3646 },//4
		{ 1178, 3610 },//5
		{ 1214, 3610 },//6
		{ 1250, 3610 },//7
		{ 1250, 3646 },//8
		{ 1214, 3646 },
		{ 1214, 3646 }
	},
	{//A
		{ 1379, 3554 },//LV1
		{ 1340, 3554 },//2
		{ 1305, 3554 },//3
		{ 1305, 3518 },//4
		{ 1305, 3482 },//5
		{ 1341, 3482 },//6
		{ 1377, 3482 },//7
		{ 1377, 3518 },//8
		{ 1343, 3518 },
		{ 1343, 3518 }
	}
};
int PesaNPosStandard[13][2] = 
{
	{ 1304, 335 },
	{ 1304, 335 },
	{ 1304, 335 },
	{ 1304, 335 },
	{ 1304, 335 },
	{ 1304, 335 },
	{ 1304, 335 },
	{ 1304, 335 },
	{ 1304, 335 },
	{ 1304, 335 },
	{ 1304, 335 },
	{ 1304, 335 },
	{ 1304, 335 }
};

int PesaMPosStandard[13][2] =
{
	{ 1083, 308 },
	{ 1083, 308 },
	{ 1083, 308 },
	{ 1083, 308 },
	{ 1083, 308 },
	{ 1083, 308 },
	{ 1083, 308 },
	{ 1083, 308 },
	{ 1083, 308 },
	{ 1083, 308 },
	{ 1083, 308 },
	{ 1083, 308 },
	{ 1083, 308 }
};

int PesaAPosStandard[13][2] =
{
	{ 1204, 152 },
	{ 1217, 155 },
	{ 1195, 175 },
	{ 1182, 174 },
	{ 1171, 190 },
	{ 1189, 196 },
	{ 1209, 182 },
	{ 1226, 190 },
	{ 1230, 174 },
	{ 1247, 184 },
	{ 1224, 190 },
	{ 1211, 165 },
	{ 1209, 174 }
};

int CartaPos[4][2] = 
{
	{ 786, 3688 },
	{ 843, 3688 },
	{ 843, 3632 },
	{ 786, 3640 }
};

int PistaPos[7][3][2] = 
{
	{//Sala 1 Lich
		{ 3350, 1622 }, //Grupo 1
		{ 3431, 1634 }, //Grupo 2
		{ 0, 0 }  //Grupo 3
	},
	{//Sala 2 Torre
		{ 3362, 1574 }, //Grupo 1
		{ 3385, 1555 }, //Grupo 2
		{ 3414, 1575 }  //Grupo 3
	},
	{//Sala 3 Amon
		{ 3410, 1453 }, //Grupo 1
		{ 3419, 1426 }, //Grupo 2
		{ 3358, 1436 }  //Grupo 3
	},
	{//Sala 4 Sulrang
		{ 3376, 1096 }, //Grupo 1
		{ 3400, 1089 }, //Grupo 2
		{ 3392, 1073 }  //Grupo 3
	},
	{//Sala 5 Labirinto
		{ 3342, 1394 }, //Grupo 1
		{ 3444, 1394 }, //Grupo 2
		{ 3442, 1293 }  //Grupo 3
	},
	{//Sala 6 Balrog
		{ 3421, 1217 }, //Grupo 1
		{ 3426, 1211 }, //Grupo 2
		{ 3424, 1226 }  //Grupo 3
	},
	{//Sala 7 Coelho
		{ 3404, 1517 }, //Grupo 1
		{ 3392, 1479 }, //Grupo 2
		{ 3383, 1501 }  //Grupo 3
	}
};

int PistaBalrogPos[5][2] = 
{
	{3421, 1217}, //Sala1
	{3428, 1180}, //Sala2
	{3357, 1186}, //Sala3
	{3393, 1255}, //Sala4
	{3385, 1204} //Sala Boss
};

int PistaBalrogPortalPos[5][5][2] = 
{
	//Sala1
	{
		{3428, 1196},
		{0, 0},
		{0, 0},
		{0, 0}
	},

	//Sala2
	{
		{3380, 1176},
		{3380, 1164},
		{0, 0},
		{0, 0}
	},

	//Sala3
	{
		{3360, 1224},
		{3352, 1224},
		{3340, 1224},
		{0, 0}
	},

	//Sala4
	{
		{3400, 1236},
		{3392, 1236},
		{3384, 1236},
		{3376, 1236}
	},

	//Sala5
	{
		{0, 0},
		{0, 0},
		{0, 0},
		{0, 0}
	}
};

int CartaTime = 0;
int CartaSala = 0;

short weapon[32][9];

CPSock BillServerSocket;
char   BillServerAddress[32] = { 0, };
int	   BillServerPort = 0;

HWND  hWndMain;
HMENU hMainMenu;
HFONT hFont = NULL;

FILE *FLogSystem = NULL;
FILE *FLogQuests = NULL;
FILE *FLogDebugs = NULL;
FILE *FLogEvents = NULL;
FILE *FLogCombine = NULL;
FILE *FLogItens = NULL;
FILE *FLogCommand = NULL;
FILE *FLogAttack = NULL;
FILE* FBanned = NULL;

int LastLogSystem = -1;
int LastLogQuests = -1;
int LastLogDebugs = -1;
int LastLogEvents = -1;
int LastLogCombine = -1;
int LastLogItens = -1;
int LastLogCommand = -1;
int LastLogAttack = -1;
int LastLogBanned= -1;

FILE *fLogFile = NULL;

CPSock DBServerSocket;
AccountBanned BannedUser[MAX_USER];
novatoEternal NovatoEternal;

unsigned int pAdminIP[MAX_ADMIN] = {0,};

CNPCGenerator mNPCGen;
CNPCSummon mSummon;
CUser pUser[MAX_USER];
CMob pMob[MAX_MOB];
STRUCT_BLOCKMAC pMac[MAX_MAC];

STRUCT_TREASURE g_pTreasure[8];

STRUCT_ITEM LevelItem[4][4][400];

char temp[4096];
char msgTemp[10000];

CItem pItem[MAX_ITEM];

unsigned int CurrentTime = 0;
unsigned int LastSendTime = 0;


int BillCounter = 0;

int	g_Week = 0;
int	g_Hour = 0;

int LastLogDay = 0;
int ConfigReady = 0;

///////////////////////////////////////

int NewbieEventServer = 0;
int CastleServer = 0;


int UserCount = 1;
int SaveCount = 1;
int ItemCount = 100;

int ForceWeather = -1;

int WeekMode = 4;
int ForceWeekMode = -1;
int GuildDay = 0;
int GuildHour = 20;

int NumGuildBattle = 26;
int PotionReady = 0;

int Citizen = 80;
int QuestIceTime = 0;

int GTorreState = 0;
int GTorreGuild = 0;

int NewbieHour = 20;
int ColoState = 0;

int NumServerInGroup = 0;

int LiveTower[3];

int pChallangerMoney[6];

unsigned short g_pGuildWar[65536];
unsigned short g_pGuildAlly[65536];
STRUCT_GUILDINFO GuildInfo[65536];

unsigned short pMobGrid[MAX_GRIDY][MAX_GRIDX];
unsigned short pItemGrid[MAX_GRIDY][MAX_GRIDX];
char pHeightGrid[MAX_GRIDY][MAX_GRIDX];

unsigned char LocalIP[4] = { 0, };

char FailAccount[16][16];

CPSock ListenSocket;

char DBServerAddress[32] = { 0, };
int DBServerPort = 0;

int CurrentWeather = 0;
int TESTSERVER = 0;
int LOCALSERVER = 0;

int TransperCharacter = 0;

unsigned int SecCounter = 0;
unsigned int MinCounter = 0;

int GuildImpostoID[MAX_GUILDZONE];

int BrState = 0;
int BrMod = 0;
int BrGrid = 0;
int CastleState = 0;
int AltarState = 1;

int Colo150Limit = 0;
char KefraKiller[32] = "LOCALSERVER";

int g_dLevel = 0;
int g_dLevel1 = 0;
int g_dLevel2 = 0;

int Kingdom1Clear = 0;
int Kingdom2Clear = 0;

int GuildNameInitialized = 0;

///////////////////////////////////////
//Config for Duel: 1:1 5:5 10:10 All:All
//////////////////////////////////////
char nRanking1[32] = { "unnamed" };
char nRanking2[32] = { "unnamed" };
char nTitle1[32] = { "unnamed" };
char nTitle2[32] = { "unnamed" };

int RankingProgress = 0;
int Ranking1 = 0;
int Ranking2 = 0;
int lTitle1 = 0;
int lTitle2 = 0;
int RankingTime = 0;

int Ranking1X = 147;
int Ranking1Y = 4044;
int Ranking2X = 189;
int Ranking2Y = 4044;

int cRanking1X = 2564;
int cRanking1Y = 1688;
int cRanking2X = 2579;
int cRanking2Y = 1714;

int kRanking1X = 142;
int kRanking1Y = 4007;
int kRanking2X = 195;
int kRanking2Y = 4082;

int TaxChanged[MAX_GUILDZONE] = { 0, 0, 0, 0, 0 };

HDC hDC;

//////////////////////////////////////

int WaterClear1[3][10] = { 0, 0, 0, 0, 0, };
int PartyPesa[3] = { 0, 0, 0 };


STRUCT_PISTA Pista[7] = { 0, 0, 0, 0, 0, };
STRUCT_CALABOUCO g_calabouco;
STRUCT_QUESTS g_quests;

STRUCT_MERC pMobMerc[MAX_MOB_MERC];

int PistaRune[7][10] = 
{
	// Lich
	{
		5110, 5112, 5115, 5113, 5111, 0, 0, 0, 0, 0
	},

	// Torre
	{
		5114, 5113, 5117, 5111, 5115, 5112, 0, 0, 0, 0
	},

	// Amon
	{
		5118, 5121, 5122, 5116, 5130, 5119, 0, 0, 0, 0
	},

	// Sulrang
	{
		5122, 5126, 5121, 5116, 5119, 0, 0, 0, 0, 0
	},

	// Labirinto
	{
		5125, 5126, 5124, 5127, 0, 0, 0, 0, 0, 0
	},

	// Balrog
	{
		5120, 5131, 5118, 5119, 5123, 5132, 5121, 0, 0, 0
	},

	//Coelho
	{
		5130, 5131, 5119, 5133, 5120, 5123, 5132, 5129, 5128, 0
	}
};

//////////////////////////////////////
extern STRUCT_GUILDZONE g_pGuildZone[MAX_GUILDZONE];

#pragma endregion

void ClearCrown(int conn)
{
	if (pUser[conn].Mode != USER_PLAY)
		return;

	int GLevel = pMob[conn].MOB.GuildLevel;
	int Guild = pMob[conn].MOB.Guild;

	int IsCrownGuild = FALSE;

	int i = 0;

	for (i = 0; i < MAX_SERVER; i++)
	{
		int CrownGuild = ChargedGuildList[i][4];

		if ((Guild != 0) && (CrownGuild != 0) && (CrownGuild == Guild && GLevel == 9))
		{
			IsCrownGuild = TRUE;

			break;
		}
	}

	if (IsCrownGuild == 1)
	{
		int HaveCrow = 0;
		int HaveDrag = 0;

		for (i = 0; i < MAX_EQUIP; i++)
		{
			if(pMob[conn].MOB.Equip[i].sIndex == 747)
				HaveCrow = 1;

			if (pMob[conn].MOB.Equip[i].sIndex != 3993 && pMob[conn].MOB.Equip[i].sIndex != 3994) // 747 = Crown on itemlist
				continue;

			HaveDrag = 1;

			if(pMob[conn].MOB.Equip[i].sIndex == 3993 && pMob[conn].MOB.Clan == 7)
			{
				sprintf(temp, "etc,crown guild:%d level:%d charge:%d name:%s", Guild, GLevel, ChargedGuildList[ServerIndex][4], pMob[conn].MOB.MobName);
				Log(temp, pUser[conn].AccountName, pUser[conn].IP);

				pMob[conn].MOB.Equip[i].sIndex = 3994;

				SendItem(conn, ITEM_PLACE_EQUIP, i, &pMob[conn].MOB.Equip[i]);
			}
			else if(pMob[conn].MOB.Equip[i].sIndex == 3994 && pMob[conn].MOB.Clan == 8)
			{
				sprintf(temp, "etc,crown guild:%d level:%d charge:%d name:%s", Guild, GLevel, ChargedGuildList[ServerIndex][4], pMob[conn].MOB.MobName);
				Log(temp, pUser[conn].AccountName, pUser[conn].IP);

				pMob[conn].MOB.Equip[i].sIndex = 3993;

				SendItem(conn, ITEM_PLACE_EQUIP, i, &pMob[conn].MOB.Equip[i]);
			}
		}

		for (i = 0; i < MAX_CARRY; i++)
		{
			if (pMob[conn].MOB.Carry[i].sIndex == 747)
				HaveCrow = 1;

			if (pMob[conn].MOB.Carry[i].sIndex != 3993 && pMob[conn].MOB.Carry[i].sIndex != 3994) // 747 = Crown on itemlist
				continue;

			HaveDrag = 1;

			if(pMob[conn].MOB.Carry[i].sIndex == 3993 && pMob[conn].MOB.Clan == 7)
			{
				sprintf(temp, "etc,crown guild:%d level:%d charge:%d name:%s", Guild, GLevel, ChargedGuildList[ServerIndex][4], pMob[conn].MOB.MobName);
				Log(temp, pUser[conn].AccountName, pUser[conn].IP);

				pMob[conn].MOB.Carry[i].sIndex = 3994;

				SendItem(conn, ITEM_PLACE_CARRY, i, &pMob[conn].MOB.Carry[i]);
			}

			if(pMob[conn].MOB.Carry[i].sIndex == 3994 && pMob[conn].MOB.Clan == 8)
			{
				sprintf(temp, "etc,crown guild:%d level:%d charge:%d name:%s", Guild, GLevel, ChargedGuildList[ServerIndex][4], pMob[conn].MOB.MobName);
				Log(temp, pUser[conn].AccountName, pUser[conn].IP);

				pMob[conn].MOB.Carry[i].sIndex = 3993;

				SendItem(conn, ITEM_PLACE_CARRY, i, &pMob[conn].MOB.Carry[i]);
			}
		}

		for (i = 0; i < MAX_CARGO; i++)
		{
			if (pUser[conn].Cargo[i].sIndex == 747)
				HaveCrow = 1;

			if (pUser[conn].Cargo[i].sIndex != 3993 && pUser[conn].Cargo[i].sIndex != 3994) // 747 = Crown on itemlist
				continue;

			HaveDrag = 1;

			if(pUser[conn].Cargo[i].sIndex == 3993 && pMob[conn].MOB.Clan == 7)
			{
				sprintf(temp, "etc,crown guild:%d level:%d charge:%d name:%s", Guild, GLevel, ChargedGuildList[ServerIndex][4], pMob[conn].MOB.MobName);
				Log(temp, pUser[conn].AccountName, pUser[conn].IP);

				pUser[conn].Cargo[i].sIndex = 3994;

				SendItem(conn, ITEM_PLACE_CARGO, i, &pUser[conn].Cargo[i]);
			}
			else if(pUser[conn].Cargo[i].sIndex == 3994 && pMob[conn].MOB.Clan == 8)
			{
				sprintf(temp, "etc,crown guild:%d level:%d charge:%d name:%s", Guild, GLevel, ChargedGuildList[ServerIndex][4], pMob[conn].MOB.MobName);
				Log(temp, pUser[conn].AccountName, pUser[conn].IP);

				pUser[conn].Cargo[i].sIndex = 3993;

				SendItem(conn, ITEM_PLACE_CARGO, i, &pUser[conn].Cargo[i]);
			}
		}

		if(HaveCrow == 0)
		{
			STRUCT_ITEM Item;
			memset(&Item, 0, sizeof(STRUCT_ITEM));

			Item.sIndex = 747;
			Item.stEffect[0].cEffect = 43;
			Item.stEffect[0].cValue = 9;

			PutItem(conn, &Item);
		}

		if(HaveDrag == 0)
		{
			STRUCT_ITEM Item;
			memset(&Item, 0, sizeof(STRUCT_ITEM));

			if(pMob[conn].MOB.Clan == 8)
				Item.sIndex = 3993;

			else if(pMob[conn].MOB.Clan == 7)
				Item.sIndex = 3994;


			PutItem(conn, &Item);
		}

		return;
	}

	for (i = 0; i < MAX_EQUIP; i++)
	{
		if (pMob[conn].MOB.Equip[i].sIndex != 747 && pMob[conn].MOB.Equip[i].sIndex != 3993 && pMob[conn].MOB.Equip[i].sIndex != 3994) // 747 = Crown on itemlist
			continue;

		sprintf(temp, "etc,crown guild:%d level:%d charge:%d name:%s", Guild, GLevel, ChargedGuildList[ServerIndex][4], pMob[conn].MOB.MobName);
		Log(temp, pUser[conn].AccountName, pUser[conn].IP);

		memset(&pMob[conn].MOB.Equip[i], 0, sizeof(STRUCT_ITEM));

		SendItem(conn, ITEM_PLACE_EQUIP, i, &pMob[conn].MOB.Equip[i]);
	}

	for (i = 0; i < MAX_CARRY; i++)
	{
		if (pMob[conn].MOB.Carry[i].sIndex != 747 && pMob[conn].MOB.Carry[i].sIndex != 3993 && pMob[conn].MOB.Carry[i].sIndex != 3994) // 747 = Crown on itemlist
			continue;

		sprintf(temp, "etc,crown guild:%d level:%d charge:%d name:%s", Guild, GLevel, ChargedGuildList[ServerIndex][4], pMob[conn].MOB.MobName);
		Log(temp, pUser[conn].AccountName, pUser[conn].IP);

		memset(&pMob[conn].MOB.Carry[i], 0, sizeof(STRUCT_ITEM));

		SendItem(conn, ITEM_PLACE_CARRY, i, &pMob[conn].MOB.Carry[i]);
	}

	for (i = 0; i < MAX_CARGO; i++)
	{
		if (pUser[conn].Cargo[i].sIndex != 747 && pUser[conn].Cargo[i].sIndex != 3993 && pUser[conn].Cargo[i].sIndex != 3994) // 747 = Crown on itemlist
			continue;

		sprintf(temp, "etc,crown guild:%d level:%d charge:%d name:%s", Guild, GLevel, ChargedGuildList[ServerIndex][4], pMob[conn].MOB.MobName);
		Log(temp, pUser[conn].AccountName, pUser[conn].IP);

		memset(&pUser[conn].Cargo[i], 0, sizeof(STRUCT_ITEM));

		SendItem(conn, ITEM_PLACE_CARGO, i, &pUser[conn].Cargo[i]);
	}
}

BOOL AddCrackError(int conn, int val, int Type)
{
	if (Type != 3 && Type != 8 && Type != 15)
	{
		sprintf(temp, "cra point: %d  type: %d", val, Type);
		Log(temp, pUser[conn].AccountName, pUser[conn].IP);
	}

	pUser[conn].NumError = pUser[conn].NumError + val;

	if (pUser[conn].NumError >= 2000000000)
	{
		SendClientMsg(conn, g_pMessageStringTable[_NN_Bad_Network_Packets]);

		CharLogOut(conn);

		sprintf(temp, "cra char logout type: %d", Type);
		Log(temp, pUser[conn].AccountName, pUser[conn].IP);

		return TRUE;
	}

	return FALSE;
}

BOOL PutItemCargo(int conn, STRUCT_ITEM* item)
{
	if (conn <= 0 || conn >= MAX_USER)
		return FALSE;

	if (pUser[conn].Mode != USER_PLAY)
		return FALSE;

	int SlotId = -1;

	int i = 0;

	for (; i < MAX_CARGO - 8; i++)
	{
		if (pUser[conn].Cargo[i].sIndex == 0)

			SlotId = i;

		break;
	}

	if (SlotId == -1)
	{
		SendClientMsg(conn, g_pMessageStringTable[_NN_You_Have_No_Space_To_Trade]);

		return FALSE;
	}


	memcpy(&pUser[conn].Cargo[SlotId], item, sizeof(STRUCT_ITEM));

	SendItem(conn, ITEM_PLACE_CARGO, SlotId, &pUser[conn].Cargo[SlotId]);

	return TRUE;
}

BOOL PutItem(int conn, STRUCT_ITEM *item)
{
	if (conn <= 0 || conn >= MAX_USER)
		return FALSE;

	if (pUser[conn].Mode != USER_PLAY)
		return FALSE;

	int SlotId = -1;

	for (int i = 0; i < pMob[conn].MaxCarry; i++)
	{
		if (pMob[conn].MOB.Carry[i].sIndex == 0)
		{
			SlotId = i;

			break;
		}
	}

	if (SlotId == -1)
	{
		SendClientMsg(conn, g_pMessageStringTable[_NN_You_Have_No_Space_To_Trade]);

		return FALSE;
	}

	memcpy(&pMob[conn].MOB.Carry[SlotId], item, sizeof(STRUCT_ITEM));

	SendItem(conn, ITEM_PLACE_CARRY, SlotId, &pMob[conn].MOB.Carry[SlotId]);

	return TRUE;
}


void GuildZoneReport(void)
{
	MSG_GuildZoneReport sm;
	memset(&sm, 0, sizeof(MSG_GuildZoneReport));

	sm.Type = _MSG_GuildZoneReport;
	sm.Size = sizeof(sm);
	sm.ID = ServerIndex;

	for (int i = 0; i < MAX_GUILDZONE; i++)
	{
		sm.Guild[i] = g_pGuildZone[i].ChargeGuild;
	}

	DBServerSocket.SendOneMessage((char*)&sm, sizeof(sm));
}

HFONT__ *GetAFont()
{
	return 0;
}

void OpenConfigExtra()
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//DialogConfigExtra * nConfigExtra = new DialogConfigExtra();
	//nConfigExtra.Create(IDD_DIALOG_CONFIG_EXTRA, this);
	//nConfigExtra->DoModal();
}

void ReadInvadeArmia()
{
	int status = nConfig::ReadInvadeArmia(PATH_INVADE, "invadeArmia.json");

	if (!status)
		MessageBox(hWndMain, "Erro ao ler invadeArmia", "FILE ERROR", NULL);
}

void ReadRvrWinner()
{
	nConfig::ReadRvrWinner(PATH_SETTINGS, "rvrWinner.json");
}

void WriteRvrWinner()
{
	nConfig::WriteRvrWinner(PATH_SETTINGS, "rvrWinner.json");

}

void ReadTerritory()
{
	for (size_t i = 0; i < MAX_TERRITORY; i++)
	{
		int status = nConfig::ReadTerritory(PATH_TERRITORY, TerritoryName[i] + ".json", i);
		
		if (!status)
			continue;
	}	
}

void WriteTerritory(unsigned int Territory)
{
	nConfig::WriteTerritory(PATH_TERRITORY, TerritoryName[Territory] + ".json", Territory);
}

void WriteGuildHall(unsigned int conn)
{
	int Guild = pMob[conn].MOB.Guild;
	int Groups = ServerGroup;
	
	char name[256];

	if (Guild)
	{
		for (size_t i = 0; i < MAX_USER; i++)
		{
			if (pUser[i].Mode != USER_PLAY)
				continue;
			if (pMob[i].MOB.Guild != Guild)
				continue;

			if (pMob[i].MOB.GuildLevel == GUILD_LEADER)
			{
				GuildHall[Guild].Lider = pMob[i].MOB.MobName;
				break;
			}
		}

		BASE_GetGuildName(Groups, Guild, name);

		std::string guildName = name;

		int status = nConfig::WriteGuildHall(PATH_GUILD_HALL, guildName + ".json", Guild);

	}
}

int ReadGuildHall(unsigned int conn)
{

	int Guild = pMob[conn].MOB.Guild;
	int Groups = ServerGroup;
	char name[256];

	if (Guild)
	{
		BASE_GetGuildName(Groups, Guild, name);

		std::string guildName = name;

		int status = nConfig::ReadGuildHall(PATH_GUILD_HALL, guildName + ".json");
		
		return status;
	}

	return FALSE;

}

void ReadGuildLevel()
{

	int status = nConfig::ReadGuildLevel(PATH_SETTINGS, "guildLevel.json");
	if (!status)
		MessageBox(hWndMain, "Erro ao ler guildLevel", "FILE ERROR", NULL);

}

void ReadTitleSystem()
{

	int status = nConfig::ReadTitleLevel(PATH_SETTINGS, "titleLevel.json");
	if (!status)
		MessageBox(hWndMain, "Erro ao ler StatusServer", "FILE ERROR", NULL);

}

void WriteStatistic()
{
	unsigned int cCelestial = 0;
	unsigned int csCelestial = 0;
	unsigned int cArch = 0;
	unsigned int cMortal = 0;
	unsigned int cStaff = 0;
	unsigned int cTotal = 0;
	unsigned int cTK = 0;
	unsigned int cFM = 0;
	unsigned int cBM = 0;
	unsigned int cHT = 0;
	unsigned int cRed = 0;
	unsigned int cBlue = 0;
	unsigned int cNoReino = 0;

	for (size_t i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;

		switch (pMob[i].Extra.ClassMaster)
		{
			case MORTAL:
				cMortal++;
				break;
			case ARCH:
				cArch++;
				break;
			case CELESTIAL:
				cCelestial++;
				break;
			case SCELESTIAL:
				csCelestial++;
				break;
			case CELESTIALCS:
				cCelestial++;
				break;
			default:
				break;
		}

		switch (pMob[i].MOB.Class)
		{
			case TK:
				cTK++;
				break;
			case FM:
				cFM++;
				break;
			case BM:
				cBM++;
				break;
			case HT:
				cHT++;
				break;
			default:
				break;
		}

		switch (pMob[i].MOB.Clan)
		{
		case REINO_BLUE:
			cBlue++;
			break;
		case REINO_RED:
			cRed++;
			break;
		default:
			cNoReino++;
			break;
		}

	}

	int status = nConfig::WriteStatistic(PATH_SETTINGS, "statistic.json", cMortal, cArch,
		cCelestial, csCelestial, cTK, cFM, cBM, cHT,cRed,cBlue,cNoReino);
	if (!status)
	{
		sprintf(temp, "error ao carregar statistic ");
		MyLog(LogType::System, "statistic.json", temp, 0, 0);
	}
}

void ReadAccountBuff(unsigned int conn)
{
	std::string accountName = pUser[conn].AccountName;

	int status = nConfig::ReadAccoutSaveBuff(PATH_SAVEBUFF, accountName +".json");
	if (!status)
	{
		sprintf(temp, "error ao carregar buffs salvos em: [%s] ", pUser[conn].AccountName);
		MyLog(LogType::Itens, pUser[conn].AccountName, temp, 0, pUser[conn].IP);
	}
	else
	{
		LoadBuff(conn);
		sprintf(temp, "carregou com sucesso buffs salvos em: [%s] ", pUser[conn].AccountName);
		MyLog(LogType::Itens, pUser[conn].AccountName, temp, 0, pUser[conn].IP);
	}
	
}

void WriteAccountBuff(unsigned int conn)
{
	std::string accountName = pUser[conn].AccountName;

	SaveBuff(conn);
	int status = nConfig::WriteAccountSaveBuff(PATH_SAVEBUFF, accountName + ".json");
	if (!status)
	{
		sprintf(temp, "error ao gravar buffs em: [%s] ", pUser[conn].AccountName);
		MyLog(LogType::Itens, pUser[conn].AccountName, temp, 0, pUser[conn].IP);
	}
	else
	{
		sprintf(temp, "gravou com sucesso buffs em: [%s] ", pUser[conn].AccountName);
		MyLog(LogType::Itens, pUser[conn].AccountName, temp, 0, pUser[conn].IP);
	}

}

void ReadStatusServer()
{
	int status = nConfig::ReadStatusServer(PATH_SETTINGS, "StatusServer.json");
	if (!status)
		MessageBox(hWndMain, "Erro ao ler StatusServer", "FILE ERROR", NULL);
}

void ReadBossCamp()
{
	int status = nConfig::ReadBossCamp(PATH_BOSS_CAMP, Freak);
	if (!status)
		MessageBox(hWndMain, "Erro ao ler Boss Freak", "FILE ERROR", NULL);


	status = nConfig::ReadStatusBossCamp(PATH_BOSS_CAMP, Freak);
	if (!status)
		MessageBox(hWndMain, "Erro ao ler Status Boss Freak", "FILE ERROR", NULL);

	status = nConfig::ReadBossCamp(PATH_BOSS_CAMP, Talos);
	if (!status)
		MessageBox(hWndMain, "Erro ao ler Boss Talos", "FILE ERROR", NULL);


	status = nConfig::ReadStatusBossCamp(PATH_BOSS_CAMP, Talos);
	if (!status)
		MessageBox(hWndMain, "Erro ao ler Status Boss Talos", "FILE ERROR", NULL);

	status = nConfig::ReadBossCamp(PATH_BOSS_CAMP, Noah);
	if (!status)
		MessageBox(hWndMain, "Erro ao ler Boss Noah", "FILE ERROR", NULL);


	status = nConfig::ReadStatusBossCamp(PATH_BOSS_CAMP, Noah);
	if (!status)
		MessageBox(hWndMain, "Erro ao ler Status Boss Noah", "FILE ERROR", NULL);

	status = nConfig::ReadBossCamp(PATH_BOSS_CAMP, Kirei);
	if (!status)
		MessageBox(hWndMain, "Erro ao ler Boss Kirei", "FILE ERROR", NULL);


	status = nConfig::ReadStatusBossCamp(PATH_BOSS_CAMP, Kirei);
	if (!status)
		MessageBox(hWndMain, "Erro ao ler Status Boss Kirei", "FILE ERROR", NULL);
}

void WriteBossCamp(unsigned char boss)
{
	int status = nConfig::WriteStatusBossCamp(PATH_BOSS_CAMP, boss);

	if (!status)
		MessageBox(hWndMain, "Erro ao gravar status.json Boss Camp", "FILE ERROR", NULL);
}

void ReadStaff()
{
	int status = nConfig::ReadStaff(PATH_ADM, "staffList.json");

	if (!status)
		MessageBox(hWndMain, "Erro ao ler staffList", "FILE ERROR", NULL);
}

void ReadColiseu()
{
	int status = nConfig::ReadColiseu(PATH_SETTINGS, "coliseu.json");

	if (!status)
		MessageBox(hWndMain, "Erro ao ler coliseu", "FILE ERROR", NULL);
}

void ReadEventTrade()
{
	int status = nConfig::ReadEventTrade(PATH_EVENT_Trade, "tradeEvent.json");

	if (!status)
		MessageBox(hWndMain, "Erro ao ler tradeEvent", "FILE ERROR", NULL);
}

void WriteSombraNegra()
{
	int status = nConfig::WriteStatusSombraNegra(PATH_SOMBRA_NEGRA, "status.json");

	if (!status)
		MessageBox(hWndMain, "Erro ao gravar status.json Sombra Negra", "FILE ERROR", NULL);
}

void ReadSombraNegra()
{
	int status = nConfig::ReadSombraNegra(PATH_SOMBRA_NEGRA, "sombraNegra.json");

	if (!status)
		MessageBox(hWndMain, "Erro ao ler sombraNegra.json", "FILE ERROR", NULL);

	status = nConfig::ReadStatusSombraNegra(PATH_SOMBRA_NEGRA, "status.json");

	if (!status)
		MessageBox(hWndMain, "Erro ao ler status.json Sombra Negra", "FILE ERROR", NULL);
}

void ReadAutoEvent()
{
	int status = nConfig::ReadAutoEvent(PATH_SETTINGS, "eventAuto.json");

	if (!status)
		MessageBox(hWndMain, "Erro ao ler eventAuto", "FILE ERROR", NULL);
}

void ReadBagWarrior(void)
{
	int status = nConfig::ReadBagWarrior(PATH_SETTINGS, "bagWarrior.json");

	if (!status)
		MessageBox(hWndMain, "Erro ao ler bagWarrior", "FILE ERROR", NULL);
}

void ReadAltarOfKing(void)
{
	StartAltarKing = FALSE;
	altarKing.HourFinish = FALSE;
	int status = nConfig::ReadAltarOfKing(PATH_EVENT_AltarOfKing, "AltarOfKing.json");

	if (!status)
		MessageBox(hWndMain, "Erro ao ler AltarOfKing", "FILE ERROR", NULL);
}

void ReadBoxEvent(void)
{
	int status = nConfig::ReadBoxEvent(PATH_EVENT_Box, "boxEventClick.json");

	if (!status)
		MessageBox(hWndMain, "Erro ao ler boxEventClick", "FILE ERROR", NULL);

}

void ConvertNPC(void)
{
	
	for (size_t i = 0; i < MAX_NPCGENERATOR; i++)
	{
		memset(&exportNPCJson, 0, sizeof(STRUCT_MOB));
		memcpy(&exportNPCJson, &mNPCGen.pList[i].Leader, sizeof(STRUCT_MOB));
		std::string file = exportNPCJson.MobName;

		if (exportNPCJson.MobName == nullptr)
			continue;

		nConfig::ConvertNPC(PATH_NewNPC, file);

	}
	
}

void ReadWarsTimer(void)
{
	int status = nConfig::ReadWarsTimer(PATH_SETTINGS, "warsTimer.json");

	if (!status)
		MessageBox(hWndMain, "Erro ao ler warsTime", "FILE ERROR", NULL);

	DrawConfig(TRUE);

	g_pRvrWar.Annoucement = warsTimer[eRvR].Notice;
	TowerStage = warsTimer[eTower].Notice;
	notWarNoatum = warsTimer[eNoatum].Notice;
}

void ReadDropKefra(void)
{
	int status = nConfig::ReadDropKefra(PATH_SETTINGS, "dropKefra.json");

	if (!status)
		MessageBox(hWndMain, "Erro ao ler dropKefra", "FILE ERROR", NULL);
}

void ReadLottery(void)
{
	int status = nConfig::ReadLottery(PATH_EVENT_Lottery, "lottery");

	if (!status)
		MessageBox(hWndMain, "Erro ao ler lottery", "FILE ERROR", NULL);
}

void ReadNPCBlock(void)
{
	int status = nConfig::ReadNPCBlock(PATH_SETTINGS, "npcBlock.json");

	if (!status)
		MessageBox(hWndMain, "Erro ao ler npcBlock", "FILE ERROR", NULL);
}

void ReadPremioLojaAfk(void)
{
	int status = nConfig::ReadPremioLojaAfk(PATH_EVENT_LojaAfk, "premio");

	if (!status)
		MessageBox(hWndMain, "Erro ao ler premio loja Afk", "FILE ERROR", NULL);
}

void ReadFadaAmmount()
{

	int Status = nConfig::ReadFadaAmmount(PATH_SETTINGS, "fadaAmmount.json");

	if (!Status)
		MessageBox(hWndMain, "Erro ao ler fadaAmmount.json", "FILE ERROR", NULL);
}

void ReadGroupItens()
{

	int Status = nConfig::ReadGroupItens(PATH_SETTINGS, "groupItens.json");

	if (!Status)
		MessageBox(hWndMain, "Erro ao ler groupItens.json", "FILE ERROR", NULL);
}

void ReadQuiz(void)
{
	QuizOn = nConfig::ReadQuiz(PATH_SETTINGS, "quiz.json");

	if (!QuizOn)
		MessageBox(hWndMain, "Erro ao ler quiz.json", "FILE ERROR", NULL);
}

void ReadConfig(void)
{

	int status = nConfig::ReadGameConfig(PATH_CONFIG, "gameConfig.json");

	if (!status)
		MessageBox(hWndMain, "Erro ao ler  gameConfig", "FILE ERROR", NULL);
	else
	{
		evIndex = gameConfig[0][0];
		evDelete = gameConfig[0][1];
		evOn = gameConfig[0][2];
		evItem = gameConfig[0][3];
		evRate = gameConfig[0][4];
		evStartIndex = gameConfig[0][5];
		evCurrentIndex = gameConfig[0][6];
		evEndIndex = gameConfig[0][7];
		evNotice = gameConfig[0][8];

		DOUBLEMODE = gameConfig[1][0];
		DUNGEONEVENT = gameConfig[1][1];
		DEADPOINT = gameConfig[1][2];
		StatSapphire = gameConfig[1][3];
		BRItem = gameConfig[1][4];

		BILLING = gameConfig[2][0];
		FREEEXP = gameConfig[2][1];
		CHARSELBILL = gameConfig[2][2];
		POTIONCOUNT = gameConfig[2][3];
		PARTYBONUS = gameConfig[2][4];
		GUILDBOARD = gameConfig[2][5];

		if (PARTYBONUS < 50 || PARTYBONUS > 200)
			PARTYBONUS = 100;

		for (size_t i = 0; i < 64; i++)
		{
			g_pDropBonus[i] = gameConfig[3][i];
		}

		memmove(&g_pTreasure, &ng_pTreasure, sizeof(STRUCT_TREASURE));

		PARTY_DIF = gameConfig[5][0];
		KefraLive = gameConfig[5][1];
		GTorreHour = gameConfig[5][2];
		isDropItem = gameConfig[5][3];
		BRHour = gameConfig[5][4];
		maxNightmare = gameConfig[5][5];
		PotionDelay = gameConfig[5][6];

		ConfigReady = 1;
		DrawConfig(TRUE);
	}

}

//Desativado, usando novo configGame acima
/*
void ReadConfig(void) // TODO : EVERYTHING
{
	FILE *fp = NULL;
	fp = fopen("gameconfig.txt", "rt");

	if (fp == NULL)
	{
		MessageBox(hWndMain, "no gameconfig.txt, server will generate default setting.", "Error", MB_OK | MB_SYSTEMMODAL);

		ConfigReady = 1;

		DrawConfig(TRUE);

		return;
	}

	
	char tmp[512];
	char parm[16][32];
	int  value[26];

	fgets(tmp, 511, fp);

	if (strcmp(tmp, "Drop Item Event Settings:\n"))
	{
		MessageBox(hWndMain, "not game-server generated gameconfig.txt - Line1", "Error", MB_OK | MB_SYSTEMMODAL);

		fclose(fp);

		return;
	}

	for (int i = 0; i < 16; i++)
	{
		value[i] = -1;

		memset(parm[i], 0, 32);
	}

	fgets(tmp, 511, fp);

	sscanf(tmp, "%s %d %s %d %s %d %s %d %s %d %s %d %d %d %d", parm[0], &value[0], parm[1], &value[1], parm[2], &value[2], parm[3], &value[3], parm[4], &value[4], parm[5], &value[5], &value[6], &value[7], &value[8]);

	if (strcmp(parm[0], "evindex") || strcmp(parm[1], "evdelete") || strcmp(parm[2], "evon") || strcmp(parm[3], "evitem") || strcmp(parm[4], "evrate") || strcmp(parm[5], "evstart"))
	{
		MessageBox(hWndMain, "not game-server generated gameconfig.txt - Line2", "Error", MB_OK | MB_SYSTEMMODAL);

		fclose(fp);

		return;
	}

	if (value[0] == -1 || value[1] == -1 || value[2] == -1 || value[3] == -1 || value[4] == -1 || value[5] == -1 || value[6] == -1 || value[7] == -1)
	{
		MessageBox(hWndMain, "not game-server generated gameconfig.txt - Line2", "Error", MB_OK | MB_SYSTEMMODAL);

		fclose(fp);

		return;
	}

	
	evIndex = value[0];
	evDelete = value[1];
	evOn = value[2];
	evItem = value[3];
	evRate = value[4];
	evStartIndex = value[5];
	evCurrentIndex = value[6];
	evEndIndex = value[7];
	evNotice = value[8];  


	fgets(tmp, 511, fp);

	if (strcmp(tmp, "Etc Event Settings:\n"))
	{
		MessageBox(hWndMain, "not game server generated gameconfig.txt - Line3", "Error", MB_OK | MB_SYSTEMMODAL);

		fclose(fp);

		return;
	}

	for (int i = 0; i < 16; i++)
	{
		value[i] = -1;

		memset(parm[i], 0, 32);
	}

	fgets(tmp, 511, fp);

	sscanf(tmp, "%s %d %s %d %s %d %s %d %s %d", parm[0], &value[0], parm[1], &value[1], parm[2], &value[2], parm[3], &value[3], parm[4], &value[4]);

	if (strcmp(parm[0], "double") || strcmp(parm[1], "deadpoint") || strcmp(parm[2], "dungeonevent") || strcmp(parm[3], "statsapphire"))
	{
		MessageBox(hWndMain, "not game-server generated gameconfig.txt - Line4", "Error", MB_OK | MB_SYSTEMMODAL);

		fclose(fp);

		return;
	}

	if (value[0] == -1 || value[1] == -1 || value[2] == -1 || value[3] == -1)
	{
		MessageBox(hWndMain, "not game-server generated gameconfig.txt - Line4", "Error", MB_OK | MB_SYSTEMMODAL);

		fclose(fp);

		return;
	}

	DOUBLEMODE = value[0];
	DUNGEONEVENT = value[1];
	DEADPOINT = value[2];
	StatSapphire = value[3];
	BRItem = value[4];

	fgets(tmp, 511, fp);

	if (strcmp(tmp, "Billing Settings:\n"))
	{
		MessageBox(hWndMain, "not game server generated gameconfig.txt - Line5", "Error", MB_OK | MB_SYSTEMMODAL);

		fclose(fp);

		return;
	}

	for (int i = 0; i < 16; i++)
	{
		value[i] = -1;

		memset(parm[i], 0, 32);
	}

	fgets(tmp, 511, fp);

	sscanf(tmp, "%s %d %s %d %s %d %s %d %s %d %s %d", parm[0], &value[0], parm[1], &value[1], parm[2], &value[2], parm[3], &value[3], parm[4], &value[4], parm[5], &value[5]);

	if (strcmp(parm[0], "billmode") || strcmp(parm[1], "freeexp"))
	{
		MessageBox(hWndMain, "not game-server generated gameconfig.txt - Line6", "Error", MB_OK | MB_SYSTEMMODAL);

		fclose(fp);

		return;
	}

	if (value[0] == -1 || value[1] == -1)
	{
		MessageBox(hWndMain, "not game-server generated gameconfig.txt - Line6", "Error", MB_OK | MB_SYSTEMMODAL);

		fclose(fp);

		return;
	}

	BILLING = value[0];
	FREEEXP = value[1];
	CHARSELBILL = value[2];
	POTIONCOUNT = value[3];
	PARTYBONUS = value[4];
	GUILDBOARD = value[5];

	if (PARTYBONUS < 50 || PARTYBONUS > 200)
		PARTYBONUS = 100;

	fgets(tmp, 511, fp);

	if (strcmp(tmp, "Item Drop Bonus Settings:\n"))
	{
		MessageBox(hWndMain, "not game server generated gameconfig.txt - Line7", "Error", MB_OK | MB_SYSTEMMODAL);

		return;
	}

	fgets(tmp, 511, fp);

	sscanf(tmp, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &value[0], &value[1], &value[2], &value[3], &value[4], &value[5], &value[6], &value[7], &value[8], &value[9], &value[10], &value[11], &value[12], &value[13], &value[14], &value[15]);

	for (int k = 0; k < 16; k++)
	{
		if (value[k] < 0 || value[k] > 9999)
		{
			MessageBox(hWndMain, "not game-server generated gameconfig.txt - Line8", "Error", MB_OK | MB_SYSTEMMODAL);

			fclose(fp);

			return;
		}

		g_pDropBonus[k] = value[k];
		value[k] = -1;
	}

	fgets(tmp, 511, fp);

	sscanf(tmp, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &value[0], &value[1], &value[2], &value[3], &value[4], &value[5], &value[6], &value[7], &value[8], &value[9], &value[10], &value[11], &value[12], &value[13], &value[14], &value[15]);

	for (int k = 0; k < 16; k++)
	{
		if (value[k] < 0 || value[k] > 9999)
		{
			MessageBox(hWndMain, "not game-server generated gameconfig.txt - Line9", "Error", MB_OK | MB_SYSTEMMODAL);

			fclose(fp);

			return;

		}

		g_pDropBonus[k + 16] = value[k];

		value[k] = -1;
	}

	fgets(tmp, 511, fp);

	sscanf(tmp, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &value[0], &value[1], &value[2], &value[3], &value[4], &value[5], &value[6], &value[7], &value[8], &value[9], &value[10], &value[11], &value[12], &value[13], &value[14], &value[15]);

	for (int k = 0; k < 16; k++)
	{
		if (value[k] < 0 || value[k] > 9999)
		{
			MessageBox(hWndMain, "not game-server generated gameconfig.txt - Line10", "Error", MB_OK | MB_SYSTEMMODAL);

			fclose(fp);

			return;
		}

		g_pDropBonus[k + 32] = value[k];

		value[k] = -1;
	}

	fgets(tmp, 511, fp);

	sscanf(tmp, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &value[0], &value[1], &value[2], &value[3], &value[4], &value[5], &value[6], &value[7], &value[8], &value[9], &value[10], &value[11], &value[12], &value[13], &value[14], &value[15]);

	for (int k = 0; k < 16; k++)
	{
		if (value[k] < 0 || value[k] > 9999)
		{
			MessageBox(hWndMain, "not game-server generated gameconfig.txt - Line11", "Error", MB_OK | MB_SYSTEMMODAL);

			fclose(fp);

			return;
		}

		g_pDropBonus[k + 48] = value[k];

		value[k] = -1;
	}

	fgets(tmp, 511, fp);

	if (strcmp(tmp, "Treasure Settings:\n"))
	{
		MessageBox(hWndMain, "not game server generated gameconfig.txt - Line12", "Error", MB_OK | MB_SYSTEMMODAL);

		fclose(fp);

		return;
	}

	for (int k = 0; k < 8; k++)
	{
		STRUCT_TREASURE *t = &g_pTreasure[k];

		memset(t, 0, sizeof(*t));

		for (int i = 0; i < 26; i++)
			value[i] = -1;

		fgets(tmp, 511, fp);

		sscanf(tmp, "%d  %d %d %d %d %d  %d %d %d %d %d  %d %d %d %d %d  %d %d %d %d %d  %d %d %d %d %d",
			&value[0], &value[1], &value[2], &value[3], &value[4], &value[5], &value[6], &value[7], &value[8], &value[9],
			&value[10], &value[11], &value[12], &value[13], &value[14], &value[15], &value[16], &value[17], &value[18], &value[19],
			&value[20], &value[21], &value[22], &value[23], &value[24], &value[25]);

		t->Source = value[0];

		for (int i = 0; i < 5; i++)
		{
			STRUCT_ITEM *it = &t->Target[i];

			it->sIndex = value[1 + i * 5];
			it->stEffect[0].cEffect = value[2 + i * 5];
			it->stEffect[0].cValue = value[3 + i * 5];
			it->stEffect[1].cEffect = value[4 + i * 5];
			it->stEffect[1].cValue = value[5 + i * 5];

		}

		fgets(tmp, 511, fp);

		sscanf(tmp, "%d %d %d %d %d", &value[0], &value[1], &value[2], &value[3], &value[4]);

		for (int i = 0; i < 5; i++)
			t->Rate[i] = value[i];
	}

	fgets(tmp, 511, fp);

	if (strcmp(tmp, "Etc Settings:\n"))
	{
		MessageBox(hWndMain, "not game server generated gameconfig.txt - Line13", "Error", MB_OK | MB_SYSTEMMODAL);

		fclose(fp);

		return;
	}

	for (int i = 0; i < 16; i++)
	{
		value[i] = -1;

		memset(parm[i], 0, 32);
	}

	fgets(tmp, 511, fp);

	sscanf(tmp, "%s %3d %s %3d %s %3d %s %3d %s %3d %s %3d %s %3d %s %3d", parm[0], &value[0], parm[1], &value[1], parm[2], &value[2], parm[3], &value[3], parm[4], &value[4], parm[5], &value[5], parm[6], &value[6], parm[7], &value[7]);

	if (strcmp(parm[0], "partydif") || strcmp(parm[1], "kefrastatus") || strcmp(parm[2], "GTorreHour") || strcmp(parm[4], "DropItem") || strcmp(parm[5], "BRHour") || strcmp(parm[6], "maxNightmare") || strcmp(parm[7], "PotionDelay"))
	{
		MessageBox(hWndMain, "not game-server generated gameconfig.txt - Line13", "Error", MB_OK | MB_SYSTEMMODAL);

		fclose(fp);

		return;
	}

	if (value[0] == -1 || value[1] == -1 || value[2] == -1 || value[3] == -1 || value[4] == -1 || value[5] == -1 || value[6] == -1 || value[7] == -1)
	{
		MessageBox(hWndMain, "not game-server generated gameconfig.txt - Line13", "Error", MB_OK | MB_SYSTEMMODAL);

		fclose(fp);

		return;
	}

	PARTY_DIF = value[0];
	KefraLive = value[1];
	GTorreHour = value[2];
	isDropItem = value[4];
	BRHour = value[5];
	maxNightmare = value[6];
	PotionDelay = value[7];

	fclose(fp);

	ExportConfig();
}

*/

//Função inutil, desativado
/*
void ExportConfig()
{
	char dir[256];

	sprintf(dir, "../../Common/ServerStatus.txt");

	FILE *fp = NULL;

	fp = fopen(dir, "wt");

	if (fp == NULL)
	{
		Log("err, exportconfig canull", "-system", 0);

		return;
	}

	char msg[256];

	fprintf(fp, "expr,%d", DOUBLEMODE);
	fprintf(fp, "\n");
	fprintf(fp, "drop,%d", 0);
	fprintf(fp, "\n");
	fprintf(fp, "rvr,%d", 20);
	fprintf(fp, "\n");
	fprintf(fp, "geg,%d", 19);
	fprintf(fp, "\n");
	fprintf(fp, "twr,%d", GTorreHour);
	fprintf(fp, "\n");
	fprintf(fp, "kefra,%d", KefraLive);
	fclose(fp);
}
*/

void DrawConfig(int wb)
{
	if (ConfigReady == 0)
		return;

	int x = 0;
	int y = 0;
	HFONT h = 0;
	
	int color = 255;
	int backcolor = 0;

	char String[4096];
	char separator1[4096] = "_____________________________________________________________________________________________________________";
	char separator2[4096] = "-----------------------------------------------------------------------------------------------------------";
	int len = 0;

	hDC = GetDC(hWndMain);

	if (hDC == NULL)
		return;

	if (hFont == 0)
		return;

	if (SelectObject(hDC, hFont) != 0)
		h = (HFONT)SelectObject(hDC, hFont);

	FILE *fp = NULL;

	/*
	if (wb) {
		fp = fopen("gameconfig.txt", "w+");
		ExportConfig();
	}*/

	SetTextColor(hDC, color);

	sprintf(String, "Drop Item Event Settings:");
	len = strlen(String);

	TextOutA(hDC, x, y, String, len);

	y += 16;

	//if (wb)
		//fprintf(fp, "%s\n", String);

	SetTextColor(hDC, backcolor);

	sprintf(String,"   evindex: %d |  evdelete: %d |  evon %d |  evitem: %d |  evrate: %d |  evstart: %d %d %d %d",
		evIndex, evDelete, evOn, evItem, evRate, evStartIndex, evCurrentIndex, evEndIndex, evNotice);
	
	len = strlen(String);

	TextOutA(hDC, x, y, String, len);

	y += 16;

	sprintf(String, separator1);
	len = strlen(String);

	TextOutA(hDC, x, y, String, len);

	y += 16;

	//if (wb)
	//	fprintf(fp, "%s\n", String);

	SetTextColor(hDC, color);

	sprintf(String, "Etc Event Settings:");

	len = strlen(String);
	TextOutA(hDC, x, y, String, len);

	y += 16;

	//if (wb)
		//fprintf(fp, "%s\n", String);

	SetTextColor(hDC, backcolor);
	sprintf(String, "   Mult.EXP: %d  | deadpoint: %d  | dungeonevent: %d  | statsapphire: %d  |  battleroyal: %d",
		DOUBLEMODE, DEADPOINT, DUNGEONEVENT, StatSapphire, BRItem);
	
	len = strlen(String);
	
	TextOutA(hDC, x, y, String, len);

	y += 16;

	sprintf(String, separator1);
	len = strlen(String);

	TextOutA(hDC, x, y, String, len);

	y += 16;

	//if (wb)
	//	fprintf(fp, "%s\n", String);

	SetTextColor(hDC, color);

	sprintf(String, "Billing Settings:");

	len = strlen(String);
	TextOutA(hDC, x, y, String, len);

	y += 16;

	//if (wb)
		//fprintf(fp, "%s\n", String);

	SetTextColor(hDC, backcolor);

	sprintf(String, "   billmode: %d  | Lv.Treiner: %d   charselbill: %d  |  potioncount: %d |  partybonus: %d |  guildboard: %d",
		BILLING, FREEEXP, CHARSELBILL, POTIONCOUNT, PARTYBONUS, GUILDBOARD);
	
	len = strlen(String);
	TextOutA(hDC, x, y, String, len);

	y += 16;

	sprintf(String, separator1);
	len = strlen(String);

	TextOutA(hDC, x, y, String, len);

	y += 16;

	//if (wb)
	//	fprintf(fp, "%s\n", String);

	SetTextColor(hDC, color);

	sprintf(String, "Item Drop Bonus Settings:");

	len = strlen(String);
	TextOutA(hDC, x, y, String, len);
	
	y += 16;

	//if (wb)
	//	fprintf(fp, "%s\n", String);

	SetTextColor(hDC, backcolor);

	for (int i = 0; i < 4; i++)
	{
		int pos = 16 * i;
		sprintf(String, "   %3d %3d %3d %3d %3d %3d %3d %3d   %3d %3d %3d %3d %3d %3d %3d %3d",
			g_pDropBonus[0 + pos], g_pDropBonus[1 + pos], g_pDropBonus[2 + pos], g_pDropBonus[3 + pos],
			g_pDropBonus[4 + pos], g_pDropBonus[5 + pos], g_pDropBonus[6 + pos], g_pDropBonus[7 + pos],
			g_pDropBonus[8 + pos], g_pDropBonus[9 + pos], g_pDropBonus[10 + pos], g_pDropBonus[11 + pos],
			g_pDropBonus[12 + pos], g_pDropBonus[13 + pos], g_pDropBonus[14 + pos], g_pDropBonus[15 + pos]);

		len = strlen(String);
		TextOutA(hDC, x, y, String, len);

		y += 16;
		if (i < 3)
		{
			sprintf(String, separator2);
			len = strlen(String);

			TextOutA(hDC, x, y, String, len);

			y += 16;
		}
		
	}

	sprintf(String, separator1);
	len = strlen(String);

	TextOutA(hDC, x, y, String, len);

	y += 16;

	//SetTextColor(hDC, color);
	//desativado sistema de Treasure antigo
	/*sprintf(String, "Treasure Settings:");
	len = strlen(String);
	
	TextOutA(hDC, x, y, String, len);
	y += 16;

	//if (wb)
	//	fprintf(fp, "%s\n", String);

	SetTextColor(hDC, backcolor);
	sprintf(String, "src   Item1   Add(Max2)    Item2   Add(Max2)    Item3   Add(Max2)    Item4   Add(Max2)    Item5   Add(Max2)");
	len = strlen(String);

	TextOutA(hDC, x, y, String, len);

	y += 16;
	short nRate[5];
	for (int j = 0; j < 8; j++)
	{
		STRUCT_TREASURE *tr = &g_pTreasure[j];

		sprintf(String, "%-4d ", g_pTreasure[j].Source);

		for (int k = 0; k < 5; ++k)
		{
			STRUCT_ITEM *item = &tr->Target[k];
			
			sprintf(String, "%s  %-4d %2d %2d %2d %2d   ",
				String, item->sIndex, item->stEffect[0].cEffect, item->stEffect[0].cValue, item->stEffect[1].cEffect, item->stEffect[1].cValue);
		}

		//if (j < 5)
		//{
		//	nRate[j] = tr->Rate[0];
		//}
		len = strlen(String);
		TextOutA(hDC, x, y, String, len);
		y += 16;

		//if (wb)
		//	fprintf(fp, "%s\n", String);

		sprintf(String, " Rate: %-5d          Rate: %-5d          Rate: %-5d          Rate: %-5d          Rate: %-5d",
			tr->Rate[0], tr->Rate[1], tr->Rate[2], tr->Rate[3], tr->Rate[4]);

		len = strlen(String);
		TextOutA(hDC, x, y, String, len);
		y += 16;
		if (j < 7)
		{
			SetTextColor(hDC, backcolor);
			sprintf(String, separator2);
			len = strlen(String);

			TextOutA(hDC, x, y, String, len);

			y += 16;
		}
		
	}
	sprintf(String, separator1);
	len = strlen(String);

	TextOutA(hDC, x, y, String, len);

	y += 16;*/
	
	//if (wb)
	//	fprintf(fp, "%s\n", String);

	SetTextColor(hDC, color);

	sprintf(String, "Etc Settings:");

	len = strlen(String);
	TextOutA(hDC, x, y, String, len);

	y += 16;

	//if (wb)
	//	fprintf(fp, "%s\n", String);

	SetTextColor(hDC, backcolor);
	sprintf(String, " partydif: %d | kefrastatus: %d  | DropItem: %d",
		PARTY_DIF, KefraLive, isDropItem);

	len = strlen(String);

	TextOutA(hDC, x, y, String, len);

	y += 16;

	sprintf(String, separator2);
	len = strlen(String);

	TextOutA(hDC, x, y, String, len);

	y += 16;

	sprintf(String, " BRHour: %d | maxNightmare: %d | PotionDelay: %d",
		BRHour, maxNightmare, PotionDelay);

	len = strlen(String);

	TextOutA(hDC, x, y, String, len);

	y += 16;

	sprintf(String, separator1);
	len = strlen(String);

	TextOutA(hDC, x, y, String, len);

	y += 16;

	SetTextColor(hDC, color);

	sprintf(String, "Guerras Status:");

	len = strlen(String);
	TextOutA(hDC, x, y, String, len);

	y += 16;

	/*------GUERRA DE TORRE Visual TM*/
	char* gambiZero1 = warsTimer[eTower].Minute < 10 ? "0" : "";
	SetTextColor(hDC, backcolor);
	sprintf(String, " Guerra de Torre: Horario: %d : %s%d",
		warsTimer[eTower].Hour, gambiZero1,warsTimer[eTower].Minute);

	len = strlen(String);

	TextOutA(hDC, x, y, String, len);

	y += 16;
	char* torreSunday = warsTimer[eTower].Days[Sunday] ? "X" : " ";
	char* torreMonday = warsTimer[eTower].Days[Monday] ? "X" : " ";
	char* torreTuesday = warsTimer[eTower].Days[Tuesday] ? "X" : " ";
	char* torreWednesday = warsTimer[eTower].Days[Wednesday] ? "X" : " ";
	char* torreThursday = warsTimer[eTower].Days[Thursday] ? "X" : " ";
	char* torreFriday = warsTimer[eTower].Days[Friday] ? "X" : " ";
	char* torreSaturday = warsTimer[eTower].Days[Saturday] ? "X" : " ";
	
	SetTextColor(hDC, backcolor);
	sprintf(String, " Dias da Semana : Domingo(%s)| Segunda(%s)| Terça(%s)| Quarta(%s)| Quinta(%s)| Sexta(%s)| Sábado(%s)",
		torreSunday, torreMonday, torreTuesday, torreWednesday, torreThursday, torreFriday, torreSaturday);

	len = strlen(String);

	TextOutA(hDC, x, y, String, len);

	y += 16;

	sprintf(String, separator2);
	len = strlen(String);

	TextOutA(hDC, x, y, String, len);


	y += 16;

	/*------GUERRA DE NOATUM Visual TM*/
	char* gambiZero2 = warsTimer[eNoatum].Minute < 10 ? "0":"";
	
	SetTextColor(hDC, backcolor);
	sprintf(String, " Guerra de Noatum: Horario: %d : %s%d",
		warsTimer[eNoatum].Hour, gambiZero2, warsTimer[eNoatum].Minute);

	len = strlen(String);

	TextOutA(hDC, x, y, String, len);

	y += 16;
	char* noatumSunday = warsTimer[eNoatum].Days[Sunday] ? "X" : " ";
	char* noatumMonday = warsTimer[eNoatum].Days[Monday] ? "X" : " ";
	char* noatumTuesday = warsTimer[eNoatum].Days[Tuesday] ? "X" : " ";
	char* noatumWednesday = warsTimer[eNoatum].Days[Wednesday] ? "X" : " ";
	char* noatumThursday = warsTimer[eNoatum].Days[Thursday] ? "X" : " ";
	char* noatumFriday = warsTimer[eNoatum].Days[Friday] ? "X" : " ";
	char* noatumSaturday = warsTimer[eNoatum].Days[Saturday] ? "X" : " ";


	SetTextColor(hDC, backcolor);
	sprintf(String, " Dias da Semana : Domingo(%s)| Segunda(%s)| Terça(%s)| Quarta(%s)| Quinta(%s)| Sexta(%s)| Sábado(%s)",
		noatumSunday, noatumMonday, noatumTuesday, noatumWednesday, noatumThursday, noatumFriday, noatumSaturday);

	len = strlen(String);

	TextOutA(hDC, x, y, String, len);

	y += 16;

	sprintf(String, separator2);
	len = strlen(String);

	TextOutA(hDC, x, y, String, len);


	y += 16;

	/*------GUERRA RvR Visual TM*/
	char* gambiZero3 = warsTimer[eRvR].Minute < 10 ? "0" : "";

	SetTextColor(hDC, backcolor);
	sprintf(String, " Guerra RvR: Horario: %d : %s%d",
		warsTimer[eRvR].Hour, gambiZero3, warsTimer[eRvR].Minute);

	len = strlen(String);

	TextOutA(hDC, x, y, String, len);

	y += 16;
	char* rvrSunday = warsTimer[eRvR].Days[Sunday] ? "X" : " ";
	char* rvrMonday = warsTimer[eRvR].Days[Monday] ? "X" : " ";
	char* rvrTuesday = warsTimer[eRvR].Days[Tuesday] ? "X" : " ";
	char* rvrWednesday = warsTimer[eRvR].Days[Wednesday] ? "X" : " ";
	char* rvrThursday = warsTimer[eRvR].Days[Thursday] ? "X" : " ";
	char* rvrFriday = warsTimer[eRvR].Days[Friday] ? "X" : " ";
	char* rvrSaturday = warsTimer[eRvR].Days[Saturday] ? "X" : " ";


	SetTextColor(hDC, backcolor);
	sprintf(String, " Dias da Semana : Domingo(%s)| Segunda(%s)| Terça(%s)| Quarta(%s)| Quinta(%s)| Sexta(%s)| Sábado(%s)",
		rvrSunday, rvrMonday, rvrTuesday, rvrWednesday, rvrThursday, rvrFriday, rvrSaturday);

	len = strlen(String);

	TextOutA(hDC, x, y, String, len);

	y += 16;

	sprintf(String, separator2);
	len = strlen(String);

	TextOutA(hDC, x, y, String, len);


	y += 16;

	/*------GUERRA Cidades Visual TM*/
	char* gambiZero4 = warsTimer[eCity].Minute < 10 ? "0" : "";

	SetTextColor(hDC, backcolor);
	sprintf(String, " Guerra de Cidades: Horario: %d : %s%d",
		warsTimer[eCity].Hour, gambiZero4, warsTimer[eCity].Minute);

	len = strlen(String);

	TextOutA(hDC, x, y, String, len);

	y += 16;
	char* citySunday = warsTimer[eCity].Days[Sunday] ? "X" : " ";
	char* cityMonday = warsTimer[eCity].Days[Monday] ? "X" : " ";
	char* cityTuesday = warsTimer[eCity].Days[Tuesday] ? "X" : " ";
	char* cityWednesday = warsTimer[eCity].Days[Wednesday] ? "X" : " ";
	char* cityThursday = warsTimer[eCity].Days[Thursday] ? "X" : " ";
	char* cityFriday = warsTimer[eCity].Days[Friday] ? "X" : " ";
	char* citySaturday = warsTimer[eCity].Days[Saturday] ? "X" : " ";


	SetTextColor(hDC, backcolor);
	sprintf(String, " Dias da Semana : Domingo(%s)| Segunda(%s)| Terça(%s)| Quarta(%s)| Quinta(%s)| Sexta(%s)| Sábado(%s)",
		citySunday, cityMonday, cityTuesday, cityWednesday, cityThursday, cityFriday, citySaturday);

	len = strlen(String);

	TextOutA(hDC, x, y, String, len);

	y += 16;

	sprintf(String, separator2);
	len = strlen(String);

	TextOutA(hDC, x, y, String, len);

	y += 16;

	sprintf(String, separator1);
	len = strlen(String);

	SetTextColor(hDC, color);

	sprintf(String, "Evento Altar do Rei:");

	len = strlen(String);
	TextOutA(hDC, x, y, String, len);

	y += 16;

	char* aMin0 = altarKing.Min[0] < 10 ? "0" : "";
	char* aMin1 = altarKing.Min[1] < 10 ? "0" : "";
	char* aMin2 = altarKing.Min[2] < 10 ? "0" : "";

	char* rSunday = altarKing.Days[Sunday] ? "X" : " ";
	char* rMonday = altarKing.Days[Monday] ? "X" : " ";
	char* rTuesday = altarKing.Days[Tuesday] ? "X" : " ";
	char* rWednesday = altarKing.Days[Wednesday] ? "X" : " ";
	char* rThursday = altarKing.Days[Thursday] ? "X" : " ";
	char* rFriday = altarKing.Days[Friday] ? "X" : " ";
	char* rSaturday = altarKing.Days[Saturday] ? "X" : " ";


	SetTextColor(hDC, backcolor);
	sprintf(String, " Dias da Semana : Domingo(%s)| Segunda(%s)| Terça(%s)| Quarta(%s)| Quinta(%s)| Sexta(%s)| Sábado(%s)",
		rSunday, rMonday, rTuesday, rWednesday, rThursday, rFriday, rSaturday);

	len = strlen(String);

	TextOutA(hDC, x, y, String, len);

	y += 16;

	SetTextColor(hDC, backcolor);
	sprintf(String, " Horarios: %d : %s%d | %d : %s%d | %d : %s%d",
		altarKing.Hour[0], aMin0, altarKing.Min[0], altarKing.Hour[1], aMin1, altarKing.Min[1],
		altarKing.Hour[2], aMin2, altarKing.Min[2]);

	len = strlen(String);

	TextOutA(hDC, x, y, String, len);

	y += 16;

	if (hFont && h)
		h = (HFONT)SelectObject(hDC, h);
	
	ReleaseDC(hWndMain, hDC);

	//if (wb)
	//	fclose(fp);
}

void AddFailAccount(char *Account)
{
	for (int i = 0; i < 16; i++)
	{
		if (FailAccount[i][0] == 0)
		{
			strcpy(FailAccount[i], Account);

			return;
		}
	}
}

int  CheckFailAccount(char *Account)
{
	int Num = 0;

	for (int i = 0; i < 16; i++)
	{
		if (FailAccount[i][0] != 0)
		{
			if (strcmp(FailAccount[i], Account) == 0)
				Num++;
		}
	}

	return Num;
}

int  IsFree(STRUCT_SELCHAR *sel)
{
	if (FREEEXP <= 0)
		return 1;

	for (int i = 0; i < MOB_PER_ACCOUNT; i++)
	{
		if (sel->MobName[i][0] != 0 && sel->Score[i].Level >= FREEEXP && sel->Score[i].Level < 999)
			return 1;
	}

	return 0;
}

int  SendBilling(int a1, char *a2, int a3, int a4)
{
	return TRUE;
}

int  SendBilling2(_AUTH_GAME *m, int hostlong)
{
	*(u_long*)&m->Unk = htonl(hostlong);

	sprintf(m->Unk, "%d", ServerIndex + 10 * ServerGroup);

	BillServerSocket.SendBillMessage((char*)m);

	return 0;
}

void SetItemBonus(STRUCT_ITEM *Dest, int Level, int a3, int DropBonus)
{
	int addDropBonus = DropBonus / 8;
	
	if (DropBonus / 8 < 0)
		addDropBonus = 0;

	if (addDropBonus > 2)
		addDropBonus = 2;

	int add1 = -1;
	int add2 = -1;

	if (Dest->stEffect[0].cEffect >= EF_GRADE0 && Dest->stEffect[0].cEffect <= EF_GRADE5)
	{
		add1 = Dest->stEffect[0].cEffect - EF_GRADE0;
		add2 = Dest->stEffect[0].cValue;
   
		Dest->stEffect[0].cEffect = 0;
		Dest->stEffect[0].cValue = 0;
	}

	g_dLevel1 = 0;
	g_dLevel2 = 0;

	if(!a3 && Level >= 210)
		Level -= 47;

	int ItemId = Dest->sIndex;
	int nUnique = g_pItemList[ItemId].nUnique;
	int nReqLv = g_pItemList[ItemId].ReqLvl;
	int nPos = g_pItemList[ItemId].nPos;

	int lvdif = (Level - nReqLv + 1) / 25;

	if(add1 != -1)
		lvdif = add1;

	g_dLevel = lvdif;

	int pForc = 0;

	if ( lvdif >= 4 )
		pForc = 1;

	if ( lvdif < 0 )
		lvdif = 0;

	if ( lvdif > 3 )
		lvdif = 3;

	if ( a3 && lvdif >= 3 )
		lvdif = 2;

	if (nPos & 0xFE && !LOBYTE(Dest->stEffect[0].sValue) && nPos != 128 )
	{
    
	int v38 = 59;
    int v37 = 0;
    int v36 = 0;
	//srand(time(NULL));
    int v35 = rand() % 101;
    int v34 = 100;

    if ( a3 )
    {
      v34 = v35 % 3;
    }
    else
    {
      if ( lvdif )
      {
        if ( lvdif == 1 )
        {
          v34 = v35 % (6 - addDropBonus);
        }
        else
        {
          if ( lvdif == 2 )
          {
            v34 = v35 % (6 - addDropBonus);
          }
          else
          {
            if ( lvdif >= 3 )
              v34 = v35 % 4;
          }
        }
      }
      else
      {
        v34 = v35 % (8 - addDropBonus);
      }
    }
    switch ( nPos )
    {
      case 2:
        if ( v34 )
        {
          if ( v34 == 1 )
          {
            v38 = 60;
            v36 = 2;
          }
        }
        else
        {
          v38 = 26;
          v36 = 3;
        }
        break;
      case 4:
        v38 = 71;
        v36 = 10;
        v37 = 1;
        break;
      case 8:
        v38 = 71;
        v36 = 10;
        v37 = 1;
        break;
      case 16:
        v38 = 72;
        v36 = 5;
        break;
      case 32:
        v38 = 73;
        v36 = 6;
        v37 = -1;
        break;
      case 64:
      case 192:
        if ( nUnique != 44 && nUnique != 47 )
        {
          if ( v34 )
          {
            if ( v34 == 1 )
            {
              v38 = 2;
              v36 = 9;
              v37 = -1;
            }
            else
            {
              if ( v34 == 2 )
              {
                v38 = 74;
                v36 = 3;
              }
            }
          }
          else
          {
            v38 = 26;
            v36 = 3;
            v37 = 1;
          }
        }
        else
        {
          if ( v34 )
          {
            if ( v34 == 1 )
            {
              v38 = 74;
              v36 = 3;
              v37 = 1;
            }
          }
          else
          {
            v38 = 60;
            v36 = 4;
            v37 = -1;
          }
        }
        break;
    }
	//srand(time(NULL));
    int v33 = rand() % 100;
    if ( a3 )
      v33 = 2 * v33 / 3;
    int v32 = 100;
    if ( a3 )
    {
      v32 = v33 % 4;
    }
    else
    {
      if ( lvdif )
      {
        if ( lvdif == 1 )
        {
          v32 = v33 % 6;
        }
        else
        {
          if ( lvdif == 2 )
          {
            v32 = v33 % 6;
          }
          else
          {
            if ( lvdif >= 3 )
              v32 = v33 % 4;
          }
        }
      }
      else
      {
        v32 = v33 % 8;
      }
    }
    int v31 = 59;
    int v30 = 0;
    int v29 = 0;
    switch ( nPos )
    {
      case 2:
        if ( v32 )
        {
          if ( v32 == 1 )
          {
            v31 = 3;
            v30 = 5;
            v29 = -1;
          }
        }
        else
        {
          v31 = 4;
          v30 = 10;
        }
        break;
      case 4:
        if ( v32 )
        {
          if ( v32 == 1 )
          {
            v31 = 2;
            v30 = 6;
            v29 = -1;
          }
          else
          {
            if ( v32 == 2 )
            {
              v31 = 3;
              v30 = 5;
              v29 = -1;
            }
          }
        }
        else
        {
          v31 = 60;
          v30 = 2;
          v29 = -1;
        }
        break;
      case 8:
        if ( v32 )
        {
          if ( v32 == 1 )
          {
            v31 = 2;
            v30 = 6;
            v29 = -1;
          }
          else
          {
            if ( v32 == 2 )
            {
              v31 = 3;
              v30 = 5;
              v29 = -1;
            }
          }
        }
        else
        {
          v31 = 60;
          v30 = 2;
          v29 = -1;
        }
        break;
      case 16:
        if ( v32 )
        {
          switch ( v32 )
          {
            case 1:
              v31 = 2;
              v30 = 6;
              v29 = -1;
              break;
            case 2:
              v31 = 74;
              v30 = 3;
              break;
            case 3:
              v31 = 54;
              v30 = 3;
              break;
          }
        }
        else
        {
          v31 = 60;
          v30 = 2;
          v29 = -1;
        }
        break;
      case 32:
        if ( v32 )
        {
          if ( v32 == 1 )
          {
            v31 = 74;
            v30 = 3;
          }
        }
        else
        {
          v31 = 60;
          v30 = 2;
          v29 = -1;
        }
        break;
      case 64:
      case 128:
      case 192:
        if ( nUnique != 44 && nUnique != 47 )
        {
          if ( v32 )
          {
            if ( v32 == 1 )
            {
              v31 = 2;
              v30 = 9;
              v29 = -1;
            }
            else
            {
              if ( v32 == 2 )
              {
                v31 = 74;
                v30 = 3;
                v29 = 1;
              }
            }
          }
          else
          {
            v31 = 26;
            v30 = 3;
            v29 = 1;
          }
        }
        else
        {
          if ( v32 )
          {
            if ( v32 == 1 )
            {
              v31 = 74;
              v30 = 3;
              v29 = 1;
            }
          }
          else
          {
            v31 = 60;
            v30 = 4;
            v29 = -1;
          }
        }
        break;
    }
    int v28 = 0;
	//srand(time(NULL));
    v35 = rand() % 100;
    if ( lvdif )
    {
      switch ( lvdif )
      {
        case 1:
          if ( v35 >= 1 )
          {
            if ( v35 >= 5 )
            {
              if ( v35 >= 24 )
              {
                if ( v35 >= 65 )
                  v28 = 1;
                else
                  v28 = 2;
              }
              else
              {
                v28 = 3;
              }
            }
            else
            {
              v28 = 4;
            }
          }
          else
          {
            v28 = 5;
          }
          break;
        case 2:
          if ( v35 >= 2 )
          {
            if ( v35 >= 16 )
            {
              if ( v35 >= 60 )
                v28 = 2;
              else
                v28 = 3;
            }
            else
            {
              v28 = 4;
            }
          }
          else
          {
            v28 = 5;
          }
          break;
        case 3:
          if ( v35 >= 2 )
          {
            if ( v35 >= 9 )
            {
              if ( v35 >= 45 )
              {
                if ( v35 >= 75 )
                  v28 = 2;
                else
                  v28 = 3;
              }
              else
              {
                v28 = 4;
              }
            }
            else
            {
              v28 = 5;
            }
          }
          else
          {
            v28 = 6;
          }
          break;
        default:
          if ( lvdif >= 4 )
          {
            if ( v35 >= 2 )
            {
              if ( v35 >= 10 )
              {
                if ( v35 >= 30 )
                {
                  if ( v35 >= 75 )
                    v28 = 3;
                  else
                    v28 = 4;
                }
                else
                {
                  v28 = 5;
                }
              }
              else
              {
                v28 = 6;
              }
            }
            else
            {
              v28 = 7;
            }
          }
          break;
      }
    }
    else
    {
      if ( v35 >= 2 )
      {
        if ( v35 >= 6 )
        {
          if ( v35 >= 24 )
            v28 = v35 < 55;
          else
            v28 = 2;
        }
        else
        {
          v28 = 3;
        }
      }
      else
      {
        v28 = 4;
      }
    }
    if ( pForc && v28 < 4 )
      v28 = 4;
    v28 += v37;
    if ( a3 && !v28 )
      v28 = 1;
    if ( LOBYTE(Dest->stEffect[1].sValue) || v28 <= 0 )
    {
      if ( LOBYTE(Dest->stEffect[1].sValue) || v28 > 0 || nPos != 32 )
      {
        if ( !LOBYTE(Dest->stEffect[1].sValue) )
        {
			Dest->stEffect[1].cEffect = 59;
			//srand(time(NULL));
          int v4 = rand() & 0x8000007F;
          if ( v4 < 0 )
            v4 = ((unsigned __int8)(v4 - 1) | 0x80) + 1;
		  Dest->stEffect[1].cValue = v4;
        }
      }
      else
      {
		  Dest->stEffect[1].cEffect = v38;
		  Dest->stEffect[1].cValue = 0;
      }
    }
    else
    {
		Dest->stEffect[1].cEffect = v38;
		Dest->stEffect[1].cValue = v36 * v28;
    }
    g_dLevel1 = v28;
    int v27 = 0;
	//srand(time(NULL));
    v33 = rand() % 100;
    if ( lvdif )
    {
      switch ( lvdif )
      {
        case 1:
          if ( v33 >= 1 )
          {
            if ( v33 >= 5 )
            {
              if ( v33 >= 24 )
              {
                if ( v33 >= 65 )
                  v27 = 1;
                else
                  v27 = 2;
              }
              else
              {
                v27 = 3;
              }
            }
            else
            {
              v27 = 4;
            }
          }
          else
          {
            v27 = 5;
          }
          break;
        case 2:
          if ( v33 >= 2 )
          {
            if ( v33 >= 16 )
            {
              if ( v33 >= 60 )
                v27 = 2;
              else
                v27 = 3;
            }
            else
            {
              v27 = 4;
            }
          }
          else
          {
            v27 = 5;
          }
          break;
        case 3:
          if ( v33 >= 2 )
          {
            if ( v33 >= 9 )
            {
              if ( v33 >= 45 )
              {
                if ( v33 >= 75 )
                  v27 = 2;
                else
                  v27 = 3;
              }
              else
              {
                v27 = 4;
              }
            }
            else
            {
              v27 = 5;
            }
          }
          else
          {
            v27 = 6;
          }
          break;
        default:
          if ( lvdif >= 4 )
          {
            if ( v33 >= 2 )
            {
              if ( v33 >= 10 )
              {
                if ( v33 >= 30 )
                {
                  if ( v33 >= 75 )
                    v27 = 3;
                  else
                    v27 = 4;
                }
                else
                {
                  v27 = 5;
                }
              }
              else
              {
                v27 = 6;
              }
            }
            else
            {
              v27 = 7;
            }
          }
          break;
      }
    }
    else
    {
      if ( v35 >= 2 )
      {
        if ( v33 >= 6 )
        {
          if ( v33 >= 24 )
            v27 = v33 < 55;
          else
            v27 = 2;
        }
        else
        {
          v27 = 3;
        }
      }
      else
      {
        v28 = 4;
      }
    }
    if ( pForc && v27 < 3 )
      v27 = 3;
    if ( a3 && v27 >= 5 )
      v27 = 4;
    v27 += v29;
    if ( addDropBonus && !v27 )
      v27 = addDropBonus;
    if ( a3 && !v27 )
      v27 = 1;
    if ( v27 <= 0 || LOBYTE(Dest->stEffect[2].sValue) )
    {
      if ( !LOBYTE(Dest->stEffect[2].sValue) )
      {
        Dest->stEffect[2].cEffect = 59;
		//srand(time(NULL));
        int v5 = rand() & 0x8000007F;
        if ( v5 < 0 )
          v5 = ((unsigned __int8)(v5 - 1) | 0x80) + 1;
		Dest->stEffect[2].cValue = v5;
      }
    }
    else
    {
		Dest->stEffect[2].cEffect = v31;
		Dest->stEffect[2].cValue = v30 * v27;
    }
    g_dLevel2 = v27;

    if ( !LOBYTE(Dest->stEffect[0].sValue) )
    {
		//srand(time(NULL));
      int v26 = rand() % 100;
      if ( a3 )
        v26 /= 2;
      int v25 = 1;
      int v24 = 12;
      int v23 = 45;
      int v22 = 70;
      if ( lvdif >= 3 )
      {
        v25 = 6;
        v24 = 35;
        v23 = 85;
        v22 = 100;
      }
      if ( lvdif == 2 )
      {
        v25 = 6;
        v24 = 35;
        v23 = 85;
        v22 = 100;
      }
      if ( lvdif == 1 )
      {
        v25 = 6;
        v24 = 22;
        v23 = 75;
        v22 = 90;
      }
      if ( !lvdif )
      {
        v25 = 6;
        v24 = 22;
        v23 = 75;
        v22 = 90;
      }
      if ( v26 >= v25 )
      {
        if ( v26 >= v24 )
        {
          if ( v26 >= v23 )
          {
            if ( v26 >= v22 )
            {
				Dest->stEffect[0].cEffect = 59;
				//srand(time(NULL));
              int v6 = rand() & 0x8000007F;
              if ( v6 < 0 )
                v6 = ((unsigned __int8)(v6 - 1) | 0x80) + 1;
			  Dest->stEffect[0].cValue = v6;
            }
            else
            {
				//srand(time(NULL));
              int v20 = rand() % 10;
              int v19 = g_pBonusType[v20];
              int v18 = lvdif;
              int v17 = g_pBonusValue[v20][lvdif][0];
              int v16 = g_pBonusValue[v20][lvdif][1];
              int v15 = v16 + 1 - v17;
              int v14 = rand() % v15 + v17;
              Dest->stEffect[0].cEffect = v19;
              Dest->stEffect[0].cValue = v14;
            }
          }
          else
          {
            Dest->stEffect[0].cEffect = 43;
            Dest->stEffect[0].cValue = 0;
          }
        }
        else
        {
          Dest->stEffect[0].cEffect = 43;
          Dest->stEffect[0].cValue = 1;
        }
      }
      else
      {
        Dest->stEffect[0].cEffect = 43;
        Dest->stEffect[0].cValue = 2;
        if ( add2 > 2 )
        {
			//srand(time(NULL));
          int v21 = rand() % 100;
          switch ( add2 )
          {
            case 3:
              if ( v21 < 30 )
                Dest->stEffect[0].cValue = 3;
              break;
            case 4:
              if ( v21 >= 10 )
              {
                if ( v21 < 40 )
                  Dest->stEffect[0].cValue = 3;
              }
              else
              {
                Dest->stEffect[0].cValue = 4;
              }
              break;
            case 5:
              if ( v21 >= 10 )
              {
                if ( v21 >= 30 )
                {
                  if ( v21 < 60 )
                    Dest->stEffect[0].cValue = 3;
                }
                else
                {
                  Dest->stEffect[0].cValue = 4;
                }
              }
              else
              {
                Dest->stEffect[0].cValue = 5;
              }
              break;
            case 6:
              if ( v21 >= 10 )
              {
                if ( v21 >= 20 )
                {
                  if ( v21 >= 40 )
                  {
                    if ( v21 < 60 )
                      Dest->stEffect[0].cValue = 3;
                  }
                  else
                  {
                    Dest->stEffect[0].cValue = 4;
                  }
                }
                else
                {
                  Dest->stEffect[0].cValue = 5;
                }
              }
              else
              {
                Dest->stEffect[0].cValue = 6;
              }
              break;
            case 7:
              if ( v21 >= 4 )
              {
                if ( v21 >= 10 )
                {
                  if ( v21 >= 20 )
                  {
                    if ( v21 >= 35 )
                    {
                      if ( v21 < 60 )
                        Dest->stEffect[0].cValue = 3;
                    }
                    else
                    {
                      Dest->stEffect[0].cValue = 4;
                    }
                  }
                  else
                  {
                    Dest->stEffect[0].cValue = 5;
                  }
                }
                else
                {
                  Dest->stEffect[0].cValue = 6;
                }
              }
              else
              {
                Dest->stEffect[0].cValue = 7;
              }
              break;
          }
        }
      }
    }
  }

  for (int i = 0; i < 12; ++i )
  {
    int v12 = g_pItemList[ItemId].ReqLvl;
    switch ( g_pItemList[ItemId].stEffect[i].sEffect )
    {
      case 0x2B:
        Dest->stEffect[0].cEffect = 43;
		Dest->stEffect[0].cValue = (unsigned char)g_pItemList[ItemId].stEffect[i].sValue;
        break;
      case 0x3D:
        Dest->stEffect[0].cEffect = 61;
        Dest->stEffect[0].cValue = LOBYTE(g_pItemList[ItemId].stEffect[i].sValue);
        break;
      case 0x4E:
        Dest->stEffect[0].cEffect = 78;
		//srand(time(NULL));
        int v11 = rand() % 4 + g_pItemList[ItemId].stEffect[i].sValue;
        if ( v11 > 9 )
          v11 = 9;
        Dest->stEffect[0].cValue = v11;
        break;
    }
  }
  if ( Dest->sIndex == 412 || Dest->sIndex == 413 || Dest->sIndex == 419 || Dest->sIndex == 420 || Dest->sIndex == 753 )
  {
	  //srand(time(NULL));
    if ( !Dest->stEffect[0].cEffect )
    {
      Dest->stEffect[0].cEffect = 59;
	  
      Dest->stEffect[0].cValue = rand();
    }
    if ( !Dest->stEffect[1].cEffect)
    {
      Dest->stEffect[1].cEffect = 59;
      Dest->stEffect[01].cValue = rand();
    }
    if ( !Dest->stEffect[2].cEffect)
    {
      Dest->stEffect[2].cEffect = 59;
      Dest->stEffect[2].cValue = rand();
    }
  }
  if ( Dest->sIndex >= 447 && Dest->sIndex <= 450
    || Dest->sIndex >= 692 && Dest->sIndex <= 695)
  {
    if ( !Dest->stEffect[0].cEffect )
    {
      Dest->stEffect[0].cEffect = 59;
      Dest->stEffect[0].cValue = rand();
    }
    if ( !Dest->stEffect[1].cEffect)
    {
      Dest->stEffect[1].cEffect = 59;
      Dest->stEffect[01].cValue = rand();
    }
    if ( !Dest->stEffect[2].cEffect)
    {
      Dest->stEffect[2].cEffect = 59;
      Dest->stEffect[2].cValue = rand()%256;
    }
  }
}

void SetItemBonus2(STRUCT_ITEM *Dest)
{
	//srand(time(NULL));
	int nPos = g_pItemList[Dest->sIndex].nPos;

	if(nPos == 2)//Elmo
	{
		int _rand = rand()%50;

		if(Dest->stEffect[0].cEffect == EF_SANC)
		{
			int sanc = BASE_GetItemSanc(Dest);

			if (sanc < 6)
			{
				sanc += rand() % 2;

				if (sanc >= 6)
					sanc = 6;

				BASE_SetItemSanc(Dest, sanc, 0);
			}
		}
		else 
		{
			Dest->stEffect[0].cEffect = EF_SANC;
			Dest->stEffect[0].cValue = rand()%2;
		}
		Dest->stEffect[1].cEffect = g_pBonusValue3[_rand][0];
		Dest->stEffect[1].cValue = g_pBonusValue3[_rand][1];

		Dest->stEffect[2].cEffect = g_pBonusValue3[_rand][2];
		Dest->stEffect[2].cValue = g_pBonusValue3[_rand][3];
	}
	//Peito calça
	if(nPos == 4 || nPos == 8)
	{
		int _rand = rand() % 108;

		if(Dest->stEffect[0].cEffect == EF_SANC)
		{
			int sanc = BASE_GetItemSanc(Dest);

			if (sanc < 6)
			{
				sanc += rand() % 2;

				if (sanc >= 6)
					sanc = 6;

				BASE_SetItemSanc(Dest, sanc, 0);
			}
		}
		else 
		{
			Dest->stEffect[0].cEffect = EF_SANC;
			Dest->stEffect[0].cValue = rand()%2;
		}

		Dest->stEffect[1].cEffect = g_pBonusValue2[_rand][0];
		Dest->stEffect[1].cValue = g_pBonusValue2[_rand][1];

		Dest->stEffect[2].cEffect = g_pBonusValue2[_rand][2];
		Dest->stEffect[2].cValue = g_pBonusValue2[_rand][3];
	}

	//Luva
	if(nPos == 16)
	{
		int _rand = rand()%60;

		if(Dest->stEffect[0].cEffect == EF_SANC)
		{
			int sanc = BASE_GetItemSanc(Dest);

			if (sanc < 6)
			{
				sanc += rand() % 2;

				if (sanc >= 6)
					sanc = 6;

				BASE_SetItemSanc(Dest, sanc, 0);
			}
		}
		else 
		{
			Dest->stEffect[0].cEffect = EF_SANC;
			Dest->stEffect[0].cValue = rand()%2;
		}

		Dest->stEffect[1].cEffect = g_pBonusValue4[_rand][0];
		Dest->stEffect[1].cValue = g_pBonusValue4[_rand][1];

		Dest->stEffect[2].cEffect = g_pBonusValue4[_rand][2];
		Dest->stEffect[2].cValue = g_pBonusValue4[_rand][3];
	}

	//Bota
	if(nPos == 32)
	{
		int _rand = rand()%32;

		if(Dest->stEffect[0].cEffect == EF_SANC)
		{
			int sanc = BASE_GetItemSanc(Dest);

			if (sanc < 6)
			{
				sanc += rand() % 2;

				if (sanc >= 6)
					sanc = 6;

				BASE_SetItemSanc(Dest, sanc, 0);
			}
		}
		else 
		{
			Dest->stEffect[0].cEffect = EF_SANC;
			Dest->stEffect[0].cValue = rand()%2;
		}

		Dest->stEffect[1].cEffect = g_pBonusValue5[_rand][0];
		Dest->stEffect[1].cValue = g_pBonusValue5[_rand][1];

		Dest->stEffect[2].cEffect = g_pBonusValue5[_rand][2];
		Dest->stEffect[2].cValue = g_pBonusValue5[_rand][3];
	
	}
}

int Challange(int conn, int mob, int coin)
{
	if (mob < MAX_USER || mob >= MAX_MOB)
		return 0;

	int ZoneChall = pMob[mob].MOB.BaseScore.Level;
	int Guild = pMob[conn].MOB.Guild;

	if (ZoneChall < 0 || ZoneChall >= ValidGuild)
		return 0;

	if (ZoneChall == 4)
		return 0;


	if (pMob[conn].MOB.GuildLevel != 9)
	{
		SendSay(mob, g_pMessageStringTable[_NN_Only_Guild_Master_can]);

		return 0;
	}

	if (g_pGuildZone[ZoneChall].ChargeGuild == Guild)
	{
		SendSay(mob, g_pMessageStringTable[_NN_Champions_Cant_Challange]);

		return 0;
	}
	if (pMob[conn].Extra.Citizen != (ServerIndex + 1))
	{
		SendSay(mob, g_pMessageStringTable[_DN_ANOTHER_TOWNSPEOPLE]);
		return 0;
	}

	int Group = ServerGroup;
	int Server = Guild / MAX_GUILD;
	int usGuild = Guild & MAX_GUILD - 1;

	int GuildName = 1;

	if (Group >= 0 && Group < MAX_SERVERGROUP && Server >= 0 && Server < 16 && usGuild >= 0 && usGuild < MAX_GUILD && g_pGuildName[Group][Server][usGuild][0] == 0)
		GuildName = 0;


	if (GuildName == 0)
	{
		SendSay(mob, g_pMessageStringTable[_NN_Only_Named_Guild]);

		return 0;
	}

	if (GuildInfo[Guild].Fame < 100)
	{
		sprintf(temp, g_pMessageStringTable[_DN_Need_1000000_For_Challange], 100);
		SendSay(mob, temp);

		return 0;
	}

	MSG_GuildInfo sm;
	memset(&sm, 0, sizeof(MSG_GuildInfo));

	sm.Type = _MSG_GuildInfo;
	sm.Size = sizeof(MSG_GuildInfo);
	sm.ID = conn;

	sm.Guild = Guild;

	coin = GuildInfo[Guild].Fame;

	GuildInfo[Guild].Fame -= 100;

	sm.GuildInfo = GuildInfo[Guild];

	DBServerSocket.SendOneMessage((char*)&sm, sizeof(MSG_GuildInfo));

	SendClientMsg(conn, g_pMessageStringTable[_NN_Challanged]);

	sprintf(temp, "etc,challange guild:%d fame:%d zone:%d", Guild, coin, ZoneChall);
	Log(temp, pMob[conn].MOB.MobName, 0);

	if (pChallangerMoney[ZoneChall] < coin)
	{
		g_pGuildZone[ZoneChall].ChallangeGuild = Guild;
		pChallangerMoney[ZoneChall] = coin;

		CReadFiles::WriteChallanger();
		CReadFiles::WriteGuild();
	}

	return 1;
}

int GenerateSummon(int conn, int SummonID, STRUCT_ITEM *sItem, int Num)
{
	int Leader = pMob[conn].Leader;

	if (Leader <= 0)
		Leader = conn;

	int MobEmpty = GetEmptyNPCMob();

	if (MobEmpty == 0)
	{
		SendClientMsg(conn, g_pMessageStringTable[_NN_Cant_Create_More_Summons]);

		return 0;
	}

	if (SummonID < 0 || SummonID >= MAX_SUMMONLIST)
		return 0;

	int sFace = mSummon.Mob[SummonID].Equip[0].sIndex;
	int Unk = 0;
	int SummonNum = 0;

	int IsSummonOther = 0;

	for (int i = 0; i < MAX_PARTY; i++)
	{
		int partyconn = pMob[Leader].PartyList[i];

		if (partyconn == 0)
			continue;

		if (partyconn <= 0 || partyconn >= MAX_MOB)
			continue;

		for (int k = 0; k < 8; k++)
		{
			if (pMob[partyconn].MOB.Equip[0].sIndex == mSummon.Mob[k].Equip[0].sIndex && mSummon.Mob[k].Equip[0].sIndex != sFace)
			{
				return 0;
			}
		}

		if (pMob[partyconn].MOB.Equip[0].sIndex != sFace || SummonID >= MAX_SUMMONLIST)
			continue;

		int posX = pMob[conn].TargetX;
		int posY = pMob[conn].TargetY;

		SummonNum++;


		if (GetEmptyMobGrid(partyconn, &posX, &posY) != 0 && GetInView(conn, partyconn) == FALSE)
		{
			MSG_Action sm;
			memset(&sm, 0, sizeof(MSG_Action));

			GetAction(partyconn, posX, posY, &sm);

			sm.Effect = 8;
			sm.Speed = 6;

			GridMulticast(partyconn, posX, posY, (MSG_STANDARD*)&sm);

			if (SummonNum >= Num)
				return 0;
			else
				continue;
		}
		else if (SummonNum >= Num)
			return 0;
	}
	for (int i = SummonNum; i < Num; i++)
	{
		MobEmpty = GetEmptyNPCMob();

		if (MobEmpty == 0)
		{
			SendClientMsg(conn, g_pMessageStringTable[_NN_Cant_Create_More_Summons]);

			return 0;
		}
		int j = 0;

		for (j = 0; j < MAX_PARTY; j++)
		{
			if (pMob[Leader].PartyList[j])
				continue;

			else
				break;
		}

		if (j >= MAX_PARTY)
		{
			SendClientMsg(conn, g_pMessageStringTable[_NN_Party_Full_Cant_Summon]);

			return 0;
		}

		memset(pMob[MobEmpty].PartyList, 0, sizeof(pMob[MobEmpty].PartyList));
		memcpy(&pMob[MobEmpty], &mSummon.Mob[SummonID], sizeof(mSummon.Mob[SummonID]));

		pMob[MobEmpty].MOB.BaseScore.Level = pMob[conn].MOB.BaseScore.Level <= MAX_LEVEL ? pMob[conn].MOB.BaseScore.Level : MAX_LEVEL;

		strcat(pMob[MobEmpty].MOB.MobName, "^");

		for (int k = 0; k < NAME_LENGTH; k++)
		{
			if (pMob[MobEmpty].MOB.MobName[k] == '_')
				pMob[MobEmpty].MOB.MobName[k] = ' ';
		}

		memset(pMob[MobEmpty].Affect, 0, sizeof(pMob[MobEmpty].Affect));

		int Int = pMob[conn].MOB.CurrentScore.Int;
		int Evocacao = pMob[conn].MOB.CurrentScore.Special[2];

		int sBase = Int * pSummonBonus[SummonID].Unk / 100;
		int sMax = Evocacao * pSummonBonus[SummonID].Unk2 / 100;

		pMob[MobEmpty].MOB.BaseScore.Damage += sMax + sBase;

		sBase = Int * pSummonBonus[SummonID].Unk3 / 100;
		sMax = Evocacao * pSummonBonus[SummonID].Unk4 / 100;

		pMob[MobEmpty].MOB.BaseScore.Ac += sMax + sBase;

		sBase = Int * pSummonBonus[SummonID].Unk5 / 100;
		sMax = Evocacao * pSummonBonus[SummonID].Unk6 / 100;

		pMob[MobEmpty].MOB.BaseScore.MaxHp += sMax + sBase;

		pMob[MobEmpty].MOB.CurrentScore.MaxHp = pMob[MobEmpty].MOB.BaseScore.MaxHp;

		pMob[MobEmpty].GenerateIndex = -1;

		pMob[MobEmpty].Formation = 5;

		pMob[MobEmpty].RouteType = 5;
		pMob[MobEmpty].Mode = MOB_PEACE;

		//	*(int*)&pMob[MobEmpty].Unk6[64] = 0;
		//	*(int*)&pMob[MobEmpty].Unk6[60] = 0;

		pMob[MobEmpty].SegmentProgress = 0;
		pMob[MobEmpty].SegmentDirection = 0;

		memset(&pMob[MobEmpty].SegmentX, 0, sizeof(pMob[MobEmpty].SegmentX));
		memset(&pMob[MobEmpty].SegmentY, 0, sizeof(pMob[MobEmpty].SegmentY));

		//	memset(pMob[MobEmpty].Unk6, 0, 20);
		//	memset(&pMob[MobEmpty].Unk6[20], 0, 20);

		pMob[MobEmpty].Leader = Leader;
		pMob[MobEmpty].LastTime = CurrentTime;

		if (sItem != 0)
		{
			int mountsanc = BASE_GetItemAbility(sItem, EF_MOUNTSANC);

			if (mountsanc >= 100)
				mountsanc = 100;

			int face = pMob[MobEmpty].MOB.Equip[0].sIndex;
			int con = 0;

			if (face >= 315 && face < 345)
			{
				int mcon = /*0x4C7974[face]*/0; // Voltar e identificar essa var
				int mUnk = mcon / 2 - 1000;
				int mUnk2 = mcon - mUnk;

				con = mountsanc * (mcon - mUnk) / 100 + mcon / 2 - 1000;
			}

			pMob[MobEmpty].MOB.BaseScore.Con = con;
			pMob[MobEmpty].MOB.CurrentScore.Con = con;

			pMob[MobEmpty].MOB.BaseScore.Damage += 6 * BASE_GetItemAbility(sItem, EF_MOUNTSANC);
			pMob[MobEmpty].MOB.CurrentScore.Damage = pMob[MobEmpty].MOB.BaseScore.Damage;
		}

		if (pMob[conn].GuildDisable == 0)
		{
			pMob[MobEmpty].MOB.Guild = pMob[conn].MOB.Guild;
			pMob[MobEmpty].MOB.GuildLevel = 0;
		}

		GetGuild(MobEmpty);


		pMob[MobEmpty].MOB.CurrentScore.Hp = pMob[MobEmpty].MOB.CurrentScore.MaxHp;

		if (pMob[conn].MOB.Equip[15].sIndex == 543 || pMob[conn].MOB.Equip[15].sIndex == 545)
		{
			memset(&pMob[MobEmpty].MOB.Equip[15], 0, sizeof(STRUCT_ITEM));
			pMob[MobEmpty].MOB.Equip[15].sIndex = 734;
		}

		if (pMob[conn].MOB.Equip[15].sIndex == 544 || pMob[conn].MOB.Equip[15].sIndex == 546)
		{
			memset(&pMob[MobEmpty].MOB.Equip[15], 0, sizeof(STRUCT_ITEM));
			pMob[MobEmpty].MOB.Equip[15].sIndex = 735;
		}

		if (pMob[conn].MOB.Equip[15].sIndex == 548 || pMob[conn].MOB.Equip[15].sIndex == 549)
		{
			memset(&pMob[MobEmpty].MOB.Equip[15], 0, sizeof(STRUCT_ITEM));
			pMob[MobEmpty].MOB.Equip[15].sIndex = 550;
		}

		pMob[MobEmpty].MOB.Clan = 4;

		pMob[MobEmpty].GetCurrentScore(MAX_USER);

		memset(pMob[MobEmpty].EnemyList, 0, sizeof(pMob[MobEmpty].EnemyList));

		int posX = pMob[conn].TargetX;
		int posY = pMob[conn].TargetY;

		int tmob = GetEmptyMobGrid(MobEmpty, &posX, &posY);

		if (tmob == 0)
		{
			pMob[MobEmpty].Mode = MOB_EMPTY;

			return 0;
		}

		pMob[MobEmpty].TargetX = posX;
		pMob[MobEmpty].LastX = posX;
		pMob[MobEmpty].TargetY = posY;
		pMob[MobEmpty].LastY = posY;

		if (sItem == 0)
		{
			pMob[MobEmpty].Affect[0].Type = 24;
			pMob[MobEmpty].Affect[0].Value = 0;
			pMob[MobEmpty].Affect[0].Level = 0;
			pMob[MobEmpty].Affect[0].Time = 20;

			if (SummonID >= 28 && SummonID <= 37)
				pMob[MobEmpty].Affect[0].Time = 2000000000;
		}

		if (sItem != 0)
		{
			if (sItem->stEffect[0].sValue > pMob[MobEmpty].MOB.CurrentScore.MaxHp)
				sItem->stEffect[0].sValue = pMob[MobEmpty].MOB.CurrentScore.MaxHp;

			pMob[MobEmpty].MOB.BaseScore.Hp = sItem->stEffect[0].sValue;
			pMob[MobEmpty].MOB.CurrentScore.Hp = pMob[MobEmpty].MOB.BaseScore.Hp;
		}
		MSG_CreateMob sm;
		memset(&sm, 0, sizeof(MSG_CreateMob));

		GetCreateMob(MobEmpty, &sm);

		sm.CreateType |= 3u;
		pMobGrid[posY][posX] = MobEmpty;

		GridMulticast(posX, posY, (MSG_STANDARD*)&sm, 0);

		pMob[Leader].PartyList[j] = MobEmpty;
		pMob[MobEmpty].Leader = Leader;

		if (SummonNum == 0)
			SendAddParty(Leader, Leader, 0);

		SendAddParty(MobEmpty, Leader, 0);

		if (SummonNum == 0)
			SendAddParty(MobEmpty, MobEmpty, j + 1);

		SendAddParty(Leader, MobEmpty, j + 1);

		for (int l = 0; l < MAX_PARTY; l++)
		{
			if (pMob[Leader].PartyList[l] == 0)
				continue;

			if (pMob[Leader].PartyList[l] != MobEmpty)
				SendAddParty(pMob[Leader].PartyList[l], MobEmpty, l + 1);

			SendAddParty(MobEmpty, pMob[Leader].PartyList[l], l + 1);
		}

		pMob[MobEmpty].Summoner = conn;
	}
	return 1;
}

int CreateMob(char *MobName, int PosX, int PosY, char *folder, int Type)
{
	int tmob = GetEmptyNPCMob();

	if (tmob == 0)
	{
		sprintf(temp, "err,no emptymob create %s", MobName);
		Log(temp, "-system", 0);

		return -1;
	}

	strncpy(pMob[tmob].MOB.MobName, MobName, NAME_LENGTH);

	memset(&pMob[tmob].PartyList, 0, sizeof(pMob[tmob].PartyList));
	
	int read = ReadMob(&pMob[tmob].MOB, folder);

	if(read == 0)
		return 0;

	pMob[tmob].MOB.MobName[NAME_LENGTH - 1] = 0;
	pMob[tmob].MOB.BaseScore.Merchant = 0;


	for (int i = 0; i < NAME_LENGTH; i++)
	{
		if (pMob[tmob].MOB.MobName[i] == 95)
			pMob[tmob].MOB.MobName[i] = 32;

		if (pMob[tmob].MOB.MobName[i] == '@')
			pMob[tmob].MOB.MobName[i] = 0;
	}
	memset(pMob[tmob].Affect, 0, sizeof(pMob[tmob].Affect));


	for (int i = 0; i < MAX_SEGMENT; i++)
	{
		//srand(time(NULL));
		if(pMob[tmob].MOB.Equip[0].sIndex != 220 && pMob[tmob].MOB.Equip[0].sIndex != 219 && pMob[tmob].MOB.Equip[0].sIndex != 358)
		{
			pMob[tmob].SegmentListX[i] = PosX + rand()%5 - 2;
			pMob[tmob].SegmentListY[i] = PosY + rand()%5 - 2;
		}

		else 
		{
			pMob[tmob].SegmentListX[i] = PosX;
			pMob[tmob].SegmentListY[i] = PosY;
		}
	}


	if (pMob[tmob].MOB.Equip[0].sIndex == 220 || pMob[tmob].MOB.Equip[0].sIndex == 219)
	{
		if (pMob[tmob].MOB.Equip[0].sIndex == 219)
		{
			pMob[tmob].MOB.Guild = g_pGuildZone[4].ChargeGuild;
			pMob[tmob].MOB.GuildLevel = 0;
		}
	}

	if (strcmp(MobName, "Espelho RainhaG") == 0)
	{
		pMob[tmob].CurrentTradeSecTimer = 1200;
	}

	pMob[tmob].GenerateIndex = -1;

	pMob[tmob].Formation = 0;

	pMob[tmob].RouteType = Type;
	pMob[tmob].Mode = MOB_PEACE;

	pMob[tmob].SegmentDirection = 0;

	pMob[tmob].Leader = 0;
	pMob[tmob].WaitSec = Type == 0 ? 10 : 40;
	pMob[tmob].LastTime = CurrentTime;

	pMob[tmob].GetCurrentScore(MAX_USER);
	pMob[tmob].MOB.CurrentScore.Hp = pMob[tmob].MOB.CurrentScore.MaxHp;

	if (NewbieEventServer && pMob[tmob].MOB.CurrentScore.Level < 120)
		pMob[tmob].MOB.CurrentScore.Hp = 3 * pMob[tmob].MOB.CurrentScore.Hp / 4;

	pMob[tmob].SegmentProgress = Type == 0 ? 0 : 4;

	memset(pMob[tmob].EnemyList, 0, sizeof(pMob[tmob].EnemyList));

	int px = pMob[tmob].SegmentListX[0];
	int py = pMob[tmob].SegmentListY[0];

	int mobslot = GetEmptyMobGrid(tmob, &px, &py);

	if (mobslot == 0)
	{
		pMob[tmob].Mode = 0;

		pMob[tmob].MOB.MobName[0] = 0;
		pMob[tmob].GenerateIndex = -1;

		return -2;
	}

	pMob[tmob].SegmentX = px;
	pMob[tmob].TargetX = px;
	pMob[tmob].LastX = px;
	pMob[tmob].SegmentY = py;
	pMob[tmob].TargetY = py;
	pMob[tmob].LastY = py;

	int skillnum = pMob[tmob].MOB.BaseScore.MaxMp;

	if (skillnum)
	{
		SetAffect(tmob, skillnum, 30000, 200);
		SetTick(tmob, skillnum, 30000, 200);
	}

	MSG_CreateMob sm;
	memset(&sm, 0, sizeof(MSG_CreateMob));

	GetCreateMob(tmob, &sm);

	sm.CreateType |= 2;

	pMobGrid[py][px] = tmob;

	GridMulticast(px, py, (MSG_STANDARD*)&sm, 0);

	return TRUE;
}

int RemoveItem(int a_iMob, int a_iObject, int a_iCount)
{
	if (a_iCount < TRUE) a_iCount = TRUE;

	int FindCount = 0;

	int ProcSlot = -1;

	for (int i = 0; i < pMob[a_iMob].MaxCarry; i++)
	{
		if (pMob[a_iMob].MOB.Carry[i].sIndex == 0)
		{
			ProcSlot = i;

			break;
		}
	}

	if (ProcSlot == -1)
	{
		SendClientMsg(a_iMob, g_pMessageStringTable[_NN_You_Have_No_Space_To_Trade]);

		return FALSE;
	}

	for (int i = 0; i < pMob[a_iMob].MaxCarry; i++)
	{
		if (pMob[a_iMob].MOB.Carry[i].sIndex != a_iObject) continue;

		int byCount = BASE_GetItemAmount(&pMob[a_iMob].MOB.Carry[i]);

		if (byCount == FALSE) byCount = TRUE;

		FindCount += byCount;
	}

	if (FindCount < a_iCount) return FALSE; int RemoveCount = a_iCount;

	for (int i = 0; i < pMob[a_iMob].MaxCarry && RemoveCount > FALSE; i++)
	{
		if (pMob[a_iMob].MOB.Carry[i].sIndex != a_iObject) continue;

		int byCount = BASE_GetItemAmount(&pMob[a_iMob].MOB.Carry[i]);

		if (byCount == FALSE) byCount = TRUE;

		if (byCount > RemoveCount)
		{
			byCount -= RemoveCount;

			BASE_SetItemAmount(&pMob[a_iMob].MOB.Carry[i], byCount); SendItem(a_iMob, ITEM_PLACE_CARRY, i, &pMob[a_iMob].MOB.Carry[i]);

			return TRUE;
		}

		RemoveCount -= byCount;

		memset(&pMob[a_iMob].MOB.Carry[i], 0, sizeof(STRUCT_ITEM)); SendItem(a_iMob, ITEM_PLACE_CARRY, i, &pMob[a_iMob].MOB.Carry[i]);
	}

	return TRUE;
}

void GenerateMob(int index, int PosX, int PosY)
{
	int GenerateMin = mNPCGen.pList[index].MinuteGenerate;

	int nindex = index;

	if (index == bSombraNegra.Boss.ID)
		genSombraNegra(index);

	/*for (size_t i = 0; i < INVADE_ARMIA.ID.size(); i++)
	{
		if (index == INVADE_ARMIA.ID[i])
		{
			mNPCGen.pList[index].Leader.SPX = INVADE_ARMIA.StartX;
			mNPCGen.pList[index].Leader.SPY = INVADE_ARMIA.StartY;
			mNPCGen.pList[index].SegmentListX[0] = INVADE_ARMIA.EndX;
			mNPCGen.pList[index].SegmentListY[0] = INVADE_ARMIA.EndY;
			break;
		}
	}*/
	

	if (index == bSombraNegra.Guardian.ID)
		genGuardianSombraNegra(index);

		//generator dos boss/guardians de camp
		for (size_t i = 0; i < MAX_BOSS_CAMP; i++)
		{
			if (index == bossCamp[i].Boss.ID)
			{
				genBossCamp(index, i);
				break;
			}

			else if (index == bossCamp[i].Guardian.ID)
			{
				genGuardianBossCamp(index, i);
				break;
			}
		}

	if (index == TORRE_RVR_RED || index == TORRE_RVR_BLUE)
		WarRandTower(index);

	if (index == altarKing.BossStatus.ID)
	{
		//strcpy(&mNPCGen.pList[index].Leader.MobName[16], altarKing.BossStatus.NAME.c_str());
		//strcpy(&mNPCGen.pList[index].Follower.MobName[16], altarKing.BossStatus.NAME.c_str());
		mNPCGen.pList[index].Leader.CurrentScore.Ac = altarKing.BossStatus.AC;
		mNPCGen.pList[index].Leader.Equip[0] = altarKing.BossStatus.FACE;
		mNPCGen.pList[index].Leader.CurrentScore.Damage = altarKing.BossStatus.DAN;
		mNPCGen.pList[index].Leader.CurrentScore.MaxHp = altarKing.BossStatus.HP;
		mNPCGen.pList[index].Leader.CurrentScore.Con = altarKing.BossStatus.CON;
		mNPCGen.pList[index].Leader.CurrentScore.Hp = altarKing.BossStatus.HP;
		mNPCGen.pList[index].Leader.CurrentScore.Level = altarKing.BossStatus.LEVEL;
		mNPCGen.pList[index].Leader.Magic = altarKing.BossStatus.MAGI;
		mNPCGen.pList[index].Leader.CurrentScore.MaxMp = altarKing.BossStatus.MP;
		mNPCGen.pList[index].Leader.CurrentScore.Mp = altarKing.BossStatus.MP;
		strcpy(&mNPCGen.pList[index].SegmentAction[0][80], altarKing.BossStatus.MSG1.c_str());
		strcpy(&mNPCGen.pList[index].SegmentAction[1][80], altarKing.BossStatus.MSG2.c_str());
		strcpy(&mNPCGen.pList[index].SegmentAction[2][80], altarKing.BossStatus.MSG3.c_str());
		
	}

	for (int i = 0; i < MAX_MOB_MERC; i++)
	{
		if (index != pMobMerc[i].GenerateIndex || index == 0)
			continue;

		memcpy(mNPCGen.pList[index].Leader.Carry, pMobMerc[i].Carry, sizeof(mNPCGen.pList[index].Leader.Carry));
		break;
	}

	if (GenerateMin >= 500)
	{
		int segx = mNPCGen.pList[index].SegmentListX[0];
		int segy = mNPCGen.pList[index].SegmentListY[0];

		int res = segx - segy;

		if ((segx - segy) <= 0)
		{
			Log("err,end index < start index", "-system", 0);
			return;
		}

		//srand(time(NULL));
		int reloc = rand() % segx + segy;
		if (reloc < 0 || reloc >= mNPCGen.NumList)
			Log("err,wrong index relocation", "-system", 0);

		index = reloc;
	}

	int Formation = mNPCGen.pList[nindex].Formation;
	int MinGroup = mNPCGen.pList[nindex].MinGroup;

	int qmob = mNPCGen.pList[nindex].MaxGroup - mNPCGen.pList[nindex].MinGroup + 1;

	if (qmob <= 0)
	{
		sprintf(temp, "err,zero divide : %d", index);
		Log(temp, "-system", 0);
		qmob = 1;
	}

	//srand(time(NULL));
	MinGroup += rand() % qmob;

	if (mNPCGen.pList[nindex].CurrentNumMob >= mNPCGen.pList[nindex].MaxNumMob)
		return;

	if (mNPCGen.pList[nindex].CurrentNumMob + MinGroup > mNPCGen.pList[nindex].MaxNumMob)
		MinGroup = mNPCGen.pList[nindex].MaxNumMob - mNPCGen.pList[nindex].CurrentNumMob;

	int tmob = GetEmptyNPCMob();

	if (tmob == 0)
	{
		sprintf(temp, "err,no emptymob leader: %d", index);
		//Log(temp, "-system", 0);

		return;
	}

	if(mNPCGen.pList[index].Leader.Equip[0].sIndex != 219 && mNPCGen.pList[index].SegmentListX[0] >= 2440 && mNPCGen.pList[index].SegmentListX[0] <= 2545 && mNPCGen.pList[index].SegmentListY[0] >= 1845 && mNPCGen.pList[index].SegmentListY[0] <= 1921)
	{
		mNPCGen.pList[index].MinuteGenerate = -1;
		return;
	}

	int tmob2 = tmob;

	memset(&pMob[tmob].PartyList, 0, sizeof(pMob[tmob].PartyList));
	memcpy(&pMob[tmob].MOB, &mNPCGen.pList[nindex].Leader, sizeof(STRUCT_MOB));

	pMob[tmob].MOB.MobName[NAME_LENGTH - 1] = 0;
	pMob[tmob].MOB.BaseScore.Merchant = 0;

	strncpy(pMob[tmob].MOB.MobName, mNPCGen.pList[nindex].Leader.MobName, NAME_LENGTH);

	if(strcmp(pMob[tmob].MOB.MobName, mNPCGen.pList[nindex].Leader.MobName) != 0)
		memcpy(pMob[tmob].MOB.MobName, mNPCGen.pList[nindex].Leader.MobName, NAME_LENGTH);

	for (int i = 0; i < NAME_LENGTH; i++)
	{
		if (pMob[tmob].MOB.MobName[i] == 95)
			pMob[tmob].MOB.MobName[i] = 32;

		if (pMob[tmob].MOB.MobName[i] == 64)
			pMob[tmob].MOB.MobName[i] = 32;
	}

	memset(pMob[tmob].Affect, 0, sizeof(pMob[tmob].Affect));

	for (int i = 0; i < MAX_SEGMENT; i++)
	{
		if (mNPCGen.pList[index].SegmentListX[i])
		{
			if (mNPCGen.pList[index].SegmentRange[i])
			{
				//srand(time(NULL));
				pMob[tmob].SegmentListX[i] = mNPCGen.pList[index].SegmentListX[i]
					- mNPCGen.pList[index].SegmentRange[i] + (rand() % (mNPCGen.pList[index].SegmentRange[i] + 1));

				pMob[tmob].SegmentListY[i] = mNPCGen.pList[index].SegmentListY[i]
					- mNPCGen.pList[index].SegmentRange[i] + (rand() % (mNPCGen.pList[index].SegmentRange[i] + 1));
			}
			else
			{
				pMob[tmob].SegmentListX[i] = mNPCGen.pList[index].SegmentListX[i];
				pMob[tmob].SegmentListY[i] = mNPCGen.pList[index].SegmentListY[i];
			}
			pMob[tmob].SegmentWait[i] = mNPCGen.pList[index].SegmentWait[i];
		}
		else
		{
			pMob[tmob].SegmentListX[i] = 0;
			pMob[tmob].SegmentListY[i] = 0;
		}
	}

	if (PosX && PosY)
	{
		for (int i = 0; i < MAX_SEGMENT; i++)
		{
			pMob[tmob].SegmentListX[i] = PosX;
			pMob[tmob].SegmentListY[i] = PosY;
		}
	}

	if (pMob[tmob].MOB.Equip[0].sIndex == 220 || pMob[tmob].MOB.Equip[0].sIndex == 219)
	{
		int br = BrState;
		if (BrState > 0 && br < MAX_USER)
		{
			if (pUser[br].Mode == USER_PLAY  && GTorreState == 0)
			{
				*(int*)&pMob[tmob].MOB.Equip[15] = *(int*)&pMob[br].MOB.Equip[15];
				*(int*)(&pMob[tmob].MOB.Equip[15] + 4) = *(int*)(&pMob[br].MOB.Equip[15] + 4);

				if (pMob[tmob].MOB.Equip[0].sIndex == 219)
				{
					pMob[tmob].MOB.Guild = pMob[br].MOB.Guild;

					GetGuild(tmob);

					if (pMob[br].MOB.GuildLevel == 9)
						pMob[tmob].MOB.GuildLevel = 0;
				}
			}
		}
	}

	WarOfTower::CreateTower(index, tmob);

	pMob[tmob].GenerateIndex = index;

	pMob[tmob].Formation = mNPCGen.pList[nindex].Formation;

	pMob[tmob].RouteType = mNPCGen.pList[nindex].RouteType;
	pMob[tmob].Mode = MOB_PEACE;

	pMob[tmob].SegmentDirection = 0;

	pMob[tmob].Leader = 0;
	pMob[tmob].WaitSec = pMob[tmob].SegmentWait[0];
	pMob[tmob].LastTime = CurrentTime;

	pMob[tmob].GetCurrentScore(MAX_USER);
	pMob[tmob].MOB.CurrentScore.Hp = pMob[tmob].MOB.CurrentScore.MaxHp;

	if (NewbieEventServer && pMob[tmob].MOB.CurrentScore.Level < 120)
		pMob[tmob].MOB.CurrentScore.Hp = 3 * pMob[tmob].MOB.CurrentScore.Hp / 4;

	pMob[tmob].SegmentProgress = 0;

	memset(pMob[tmob].EnemyList, 0, sizeof(pMob[tmob].EnemyList));

	//srand(time(NULL));
	if (pMob[tmob].MOB.Clan == 1 && rand() % 10 == 1)
		pMob[tmob].MOB.Clan = 2;

	int mobslot = GetEmptyMobGrid(tmob, &pMob[tmob].SegmentListX[0], &pMob[tmob].SegmentListY[0]);

	if (mobslot == 0)
	{
		pMob[tmob].Mode = 0;

		pMob[tmob].MOB.MobName[0] = 0;
		pMob[tmob].GenerateIndex = -1;

		return;
	}

	//Imposto
	if(pMob[tmob].MOB.Merchant == 6 && tmob >= MAX_USER)
	{
		int level = pMob[tmob].MOB.CurrentScore.Level;

		GuildImpostoID[level] = tmob;
		pMob[tmob].MOB.Guild = g_pGuildZone[level].ChargeGuild;
	}


	pMob[tmob].SegmentX = pMob[tmob].SegmentListX[0];
	pMob[tmob].TargetX = pMob[tmob].SegmentListX[0];
	pMob[tmob].LastX = pMob[tmob].SegmentListX[0];
	pMob[tmob].SegmentY = pMob[tmob].SegmentListY[0];
	pMob[tmob].TargetY = pMob[tmob].SegmentListY[0];
	pMob[tmob].LastY = pMob[tmob].SegmentListY[0];

	if (mNPCGen.pList[nindex].CurrentNumMob < 0)
		mNPCGen.pList[nindex].CurrentNumMob = 0;

	mNPCGen.pList[nindex].CurrentNumMob++;

	int skillnum = mNPCGen.pList[nindex].Leader.BaseScore.MaxMp;

	if (skillnum)
	{
		SetAffect(tmob, skillnum, 30000, 200);
		SetTick(tmob, skillnum, 30000, 200);
	}

	MSG_CreateMob sm;
	memset(&sm, 0, sizeof(MSG_CreateMob));
	GetCreateMob(tmob, &sm);

	sm.CreateType |= 2;

	pMobGrid[pMob[tmob].SegmentListY[0]][pMob[tmob].SegmentListX[0]] = tmob;

	GridMulticast(pMob[tmob].SegmentListX[0], pMob[tmob].SegmentListY[0], (MSG_STANDARD*)&sm, 0);

	for (int i = 0; i < MinGroup && i < MAX_PARTY; i++)
	{
		int tempmob = GetEmptyNPCMob();

		if (tempmob == 0)
		{
			pMob[tmob2].PartyList[i] = 0;

			sprintf(temp, "err,no empty mob: %d", index);

			Log(temp, "-system", 0);
			continue;
		}

		memset(&pMob[tempmob].PartyList, 0, sizeof(pMob[tempmob].PartyList));

		pMob[tmob2].PartyList[i] = tempmob;

		memcpy(&pMob[tempmob], &mNPCGen.pList[nindex].Follower, sizeof(STRUCT_MOB));

		pMob[tempmob].MOB.BaseScore.Merchant = 0;

		strncpy(pMob[tempmob].MOB.MobName, mNPCGen.pList[nindex].Follower.MobName, NAME_LENGTH);

		for (int j = 0; j < NAME_LENGTH; ++j)
		{
			if (pMob[tempmob].MOB.MobName[j] == 95)
				pMob[tempmob].MOB.MobName[j] = 32;

			if (pMob[tempmob].MOB.MobName[j] == '@')
				pMob[tempmob].MOB.MobName[j] = 0;
		}
		memset(pMob[tempmob].Affect, 0, sizeof(pMob[tempmob].Affect));

		for (int j = 0; j < MAX_SEGMENT; j++)
		{
			if (mNPCGen.pList[index].SegmentRange[j])
			{
				pMob[tempmob].SegmentListX[j] = g_pFormation[i][j][Formation] + pMob[tmob].SegmentListX[j];

				pMob[tempmob].SegmentListY[j] = g_pFormation[i][j][Formation] + pMob[tmob].SegmentListY[j];


				pMob[tempmob].SegmentWait[j] = mNPCGen.pList[index].SegmentWait[j];
			}
			else
			{
				pMob[tempmob].SegmentListX[j] = mNPCGen.pList[index].SegmentListX[j];
				pMob[tempmob].SegmentListY[j] = mNPCGen.pList[index].SegmentListY[j];
			}
		}
		if (PosX && PosY)
		{
			for (int k = 0; k < MAX_SEGMENT; k++)
			{
				//srand(time(NULL));
				pMob[tempmob].SegmentListX[k] = PosX + rand() % 5 - 2;
				pMob[tempmob].SegmentListY[k] = PosY + rand() % 5 - 2;
			}
		}

		pMob[tempmob].GenerateIndex = index;

		pMob[tempmob].Formation = mNPCGen.pList[nindex].Formation;

		pMob[tempmob].RouteType = mNPCGen.pList[nindex].RouteType;
		pMob[tempmob].Mode = MOB_PEACE;

		pMob[tempmob].SegmentProgress = 0;

		pMob[tempmob].Leader = tmob2;
		pMob[tempmob].LastTime = CurrentTime;

		pMob[tempmob].GetCurrentScore(MAX_USER);
		pMob[tempmob].MOB.CurrentScore.Hp = pMob[tempmob].MOB.CurrentScore.MaxHp;

		if (NewbieEventServer && pMob[tempmob].MOB.CurrentScore.Level < 120)
			pMob[tempmob].MOB.CurrentScore.Hp = 3 * pMob[tempmob].MOB.CurrentScore.Hp / 4;

		pMob[tempmob].WaitSec = pMob[tempmob].SegmentWait[0];
		pMob[tempmob].SegmentDirection = 0;

		memset(pMob[tempmob].EnemyList, 0, sizeof(pMob[tempmob].EnemyList));

		//srand(time(NULL));
		if (pMob[tempmob].MOB.Clan == 1 && rand() % 10 == 1)
			pMob[tempmob].MOB.Clan = 2;

		int mslot = GetEmptyMobGrid(tempmob, &pMob[tempmob].SegmentListX[0], &pMob[tempmob].SegmentListY[0]);

		if (mslot == 0)
		{
			sprintf(temp, "err,No empty mobgrid: %d %d %d", index, pMob[tempmob].SegmentListX[0], pMob[tempmob].SegmentListY[0]);
			Log(temp, "-system", 0);

			pMob[tempmob].Mode = 0;
			pMob[tempmob].MOB.MobName[0] = 0;
			pMob[tempmob].GenerateIndex = -1;
			pMob[tmob2].PartyList[i] = 0;

			return;
		}


		pMob[tempmob].SegmentX = pMob[tempmob].SegmentListX[0];
		pMob[tempmob].TargetX = pMob[tempmob].SegmentListX[0];
		pMob[tempmob].LastX = pMob[tempmob].SegmentListX[0];
		pMob[tempmob].SegmentY = pMob[tempmob].SegmentListY[0];
		pMob[tempmob].TargetY = pMob[tempmob].SegmentListY[0];
		pMob[tempmob].LastY = pMob[tempmob].SegmentListY[0];

		skillnum = mNPCGen.pList[nindex].Leader.BaseScore.MaxMp;

		if (skillnum)
		{
			SetAffect(tempmob, skillnum, 30000, 200);
			SetTick(tempmob, skillnum, 30000, 200);
		}

		MSG_CreateMob sm2;
		memset(&sm2, 0, sizeof(MSG_CreateMob));
		GetCreateMob(tempmob, &sm2);

		sm2.CreateType |= 2;

		pMobGrid[pMob[tempmob].SegmentListY[0]][pMob[tempmob].SegmentListX[0]] = tempmob;

		GridMulticast(pMob[tempmob].SegmentListX[0], pMob[tempmob].SegmentListY[0], (MSG_STANDARD*)&sm2, 0);

		if (mNPCGen.pList[nindex].CurrentNumMob < 0)
			mNPCGen.pList[nindex].CurrentNumMob = 0;

		mNPCGen.pList[nindex].CurrentNumMob++;
	}
}

void RebuildGenerator()
{
	for (int i = 0; i < mNPCGen.NumList; i++)
		mNPCGen.NumOld[i] = 0;

	for (int i = MAX_USER; i < MAX_MOB; i++)
	{
		if (pMob[i].Mode == 0)
			continue;

		int GenerateIndex = pMob[i].GenerateIndex;

		if (GenerateIndex >= 0 && GenerateIndex < mNPCGen.NumList)
			mNPCGen.NumOld[GenerateIndex]++;
	}

	for (int i = MAX_USER; i < mNPCGen.NumList; i++)
	{
		if (mNPCGen.pList[i].CurrentNumMob == mNPCGen.NumOld[i])
			continue;

		sprintf(temp, "Idx:%d Name:%s Old:%d New:%d", i, mNPCGen.pList[i].Leader.MobName, mNPCGen.pList[i].CurrentNumMob, mNPCGen.NumOld[i]);

		Log(temp, "-system", 0);

		mNPCGen.pList[i].CurrentNumMob = mNPCGen.NumOld[i];
	}
}

BOOL InitApplication(HANDLE hInstance)
{
	WNDCLASS  wc;

	wc.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;

	wc.lpfnWndProc = (WNDPROC)MainWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = (HICON)LoadIcon((HINSTANCE)hInstance, "MAINICON");
	wc.hInstance = (HINSTANCE)hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "MainClass";

	if (!RegisterClass(&wc))
		return RegisterClass(&wc);

	return TRUE;
}

BOOL InitInstance(HANDLE hInstance, int nCmdShow)
{
	hMainMenu = CreateMenu();
	hWndMain = CreateWindow("MainClass", "Game Server",
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,    // Window style. 
		CW_USEDEFAULT, CW_USEDEFAULT, 900, 850,            // W,H[MenuÇÕÄ¡¸é 480]
		NULL, hMainMenu, (HINSTANCE)hInstance, NULL);

	if (!hWndMain)
		return (FALSE);

	ShowWindow(hWndMain, nCmdShow);
	UpdateWindow(hWndMain);

	return TRUE;
}

FILE*  WriteHeader(char *fileName)
{
	FILE *fp = NULL;

	fp = fopen(fileName, "wt");

	fprintf(fp, "<script>\n");
	fprintf(fp, "function f_show(idx) \n");
	fprintf(fp, "{\n");
	fprintf(fp, "opener.document.frmRegist.item_code.value=idx;\n");
	fprintf(fp, "self.close();\n");
	fprintf(fp, "}\n");
	fprintf(fp, "</script>\n");
	fprintf(fp, "<style><!--\n");
	fprintf(fp, "A:link {color:#111111;font-size:9pt;text-decoration:none}\n");
	fprintf(fp, "A:visited {color:#333333;font-size:9pt;text-decoration:none}\n");
	fprintf(fp, "A:active {color:red;font-size:9pt}\n");
	fprintf(fp, "A:hover {text-color:red;text-decoration:underline}\n");
	fprintf(fp, "BODY,TD,TH {font-size: 9pt}\n");
	fprintf(fp, "--></style>\n");

	return fp;
}

void  WriteArmor(FILE *fp)
{
}

BOOL WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;


	UNREFERENCED_PARAMETER(lpCmdLine);
	
	if (!hPrevInstance)
	if (!InitApplication(hInstance))
		return FALSE;
	
	if (!InitInstance(hInstance, nCmdShow))
		return FALSE;

	hFont = CreateFont(12, 0, 0, 0, FW_LIGHT, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEVICE_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Fixedsys"); // |FF_DECORATIVE

	BASE_InitModuleDir();
	BASE_InitializeHitRate();

	StartLog();
	memset(&g_pTreasure, 0, sizeof(g_pTreasure));

	BASE_ReadQuestDiaria();
	BASE_ReadGuardFile();
	ReadConfig();
	CReadFiles::ReadSancRate();
	ReadQuiz();
	ReadPremioLojaAfk();
	ReadGroupItens();
	ReadFadaAmmount();
	ReadNPCBlock();
	ReadLottery();
	ReadDropKefra();
	ReadWarsTimer();
	ReadBoxEvent();
	ReadAltarOfKing();
	ReadBagWarrior();
	ReadAutoEvent();
	ReadSombraNegra();
	ReadEventTrade();
	ReadColiseu();
	ReadStaff();
	ReadBossCamp();
	ReadStatusServer();
	ReadLevelItemConfig();
	ReadTitleSystem();
	ReadGuildLevel();
	ConfigReady = 1;

	DrawConfig(0);

	memset(GuildHall, 0, sizeof(GuildHall));
	memset(Territory, 0, MAX_TERRITORY);
	memset(g_pGuildWar, 0, sizeof(g_pGuildWar));
	memset(g_pGuildAlly, 0, sizeof(g_pGuildAlly));
	memset(GuildInfo, 0, sizeof(GuildInfo));
	memset(pMac, 0, sizeof(pMac));
	memset(pMobMerc, 0, sizeof(pMobMerc));
	memset(&g_pRvrWar, 0, sizeof g_pRvrWar);

	int ret = ListenSocket.WSAInitialize();

	if (!ret)
	{
		Log("erro,não foi possivel iniciar a seguinte função : WSAInitialize", "-system", 0);

		return FALSE;
	}

	Reboot();
	ReadTerritory();
	ReadRvrWinner();
	ReadInvadeArmia();
	SetCastleDoor(1);

	char name[255];

	FILE* fp = fopen("localip.txt", "rt");

	if (fp)
	{
		fscanf(fp, "%s", name);

		fclose(fp);
	}
	else
		MessageBox(hWndMain, "Não foi possivel encontrar o arquivo LocalIP.txt", "Erro ao iniciar", NULL);

	int r1 = 0, r2 = 0, r3 = 0, r4 = 0;

	sscanf(name, "%d.%d.%d.%d", &r1, &r2, &r3, &r4);

	LocalIP[0] = r1;
	LocalIP[1] = r2;
	LocalIP[2] = r3;
	LocalIP[3] = r4;
	DBServerAddress[0] = 0;

	for (int i = 0; i < MAX_SERVERGROUP; i++)
	{
		for (int j = 1; j < MAX_SERVERNUMBER; j++)
		{
			if (!strcmp(g_pServerList[i][j], name))
			{
				strcpy(DBServerAddress, g_pServerList[i][0]);

				ServerGroup = i;
				ServerIndex = j - 1;

				break;
			}
		}

		if (DBServerAddress[0] == 0)
			continue;
	}

	if (DBServerAddress[0] == 0)
	{
		MessageBox(hWndMain, "Não foi possivel pegar o ServerGroup. LocalIP.txt / ServerList.txt", "Erro ao iniciar", MB_OK | MB_SYSTEMMODAL);

		return TRUE;
	}

	DBServerPort = 7514;

	int *pip = (int*)LocalIP;

	ret = DBServerSocket.ConnectServer(DBServerAddress, 7514, *pip, WSA_READDB);

	if (ret == NULL)
	{
		Log("erro, Não foi possivel se conectar a DBServer", "-system", 0);
		MessageBox(hWndMain, "Não foi possivel se conectar a DBServer", "Erro ao iniciar", NULL);

		return FALSE;
	}

	for (int i = 1; i < MAX_SERVERNUMBER; i++)
	{
		if (g_pServerList[ServerGroup][i][0] != 0)
			NumServerInGroup++;
	}

	if (NumServerInGroup <= 0)
		NumServerInGroup = 1;

	if (NumServerInGroup > 10)
		NumServerInGroup = 10;
	
	if (!strcmp(DBServerAddress, "192.168.0.153"))
		TESTSERVER = 1;

	if (!strcmp(DBServerAddress, "192.168.0.50"))
		LOCALSERVER = 1;

	fp = fopen("biserver.txt", "rt");

	if (fp)
	{
		fscanf(fp, "%s %d", BillServerAddress, &BillServerPort);

		fclose(fp);
	}

	if (BILLING > 0)
	{
		int *pip2 = (int*)LocalIP;

		ret = BillServerSocket.ConnectBillServer(BillServerAddress, BillServerPort, *pip2, WSA_READBILL);

		if (ret == NULL)
		{
			Log("erro, Não foi possivel se conectar na BIServer", "-system", 0);
			BILLING = 0;
		}
		else
		{
			_AUTH_GAME sm;
			
			memset(&sm, 0, sizeof(sm));

			SendBilling2(&sm, 4); // MSG_BillLogin ?
		}
	}

	SetColoseumDoor(1);
	SetColoseumDoor2(3);

	memset(FailAccount, 0, sizeof(FailAccount));

	CurrentTime = timeGetTime();

	CReadFiles::CReadFiles();
	// CEncampment::ReadCamp();
	CCastleZakum::ReadCastleQuest();

	SetTimer(hWndMain, TIMER_SEC, 500, NULL);
	SetTimer(hWndMain, TIMER_MIN, 12000, NULL);

	ListenSocket.StartListen(hWndMain, *pip, GAME_PORT, WSA_ACCEPT);

	GuildZoneReport();

	if (KefraLive == 0)
	{
		for (int k = KEFRA_MOB_INITIAL; k < KEFRA_MOB_END; k++)
			GenerateMob(k, 0, 0);

		GenerateMob(KEFRA_BOSS, 0, 0);
	}

	//mNPCGen.ReadRegion();
	//mNPCGen.DropList();
   // mNPCGen.LevelList();

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return	msg.wParam;
}

void WriteWeapon(FILE *fp)
{
	fprintf(fp, "<body leftmargin=0 topmargin=0 marginwidth=0 marginheight=0><table>\n");

	for (int i = 0; i < 32; i++)
	{
		fprintf(fp, "<tr  height=10>");

		for (int j = 0; j < 9; j++)
		{
			char dest[256];

			int item = weapon[i][j];

			if (j == 0)
				strcpy(dest, "#F6EED9");
			if (j == 1)
				strcpy(dest, "#DFDFDF");
			if (j == 2)
				strcpy(dest, "#D9EAF6");
			if (j == 3)
				strcpy(dest, "#DFE9D0");
			if (j == 4)
				strcpy(dest, "#F6D9E0");
			if (j == 5)
				strcpy(dest, "#F6EED9");
			if (j == 6)
				strcpy(dest, "#DFDFDF");
			if (j == 7)
				strcpy(dest, "#D9EAF6");
			if (j == 8)
				strcpy(dest, "#DFE9D0");

			int reqlv = g_pItemList[item].ReqLvl;
			int reqstatus = g_pItemList[item].ReqCon + g_pItemList[item].ReqDex + g_pItemList[item].ReqInt + g_pItemList[item].ReqStr;

			if (reqlv || reqstatus <= 75)
			{
				if (reqlv || reqstatus <= 20)
					strcpy(temp, "#000000");
				else
					strcpy(temp, "#00BF00");
			}
			else
				strcpy(temp, "#FF00FF");

			fprintf(fp, "<td width=140 height=16 bgcolor='%s'><a href=\"javascript:f_show(%d); title='%d'><font color='%s'>%16.16s</font></a></td>",
				&dest, item, item, &temp, &g_pItemList[item].Name);
		}
		fprintf(fp, "</tr>\n");
	}
	fprintf(fp, "</table></body>\n");
}

void BuildList()
{

}

LONG APIENTRY MainWndProc(HWND hWnd, UINT message, UINT wParam, LONG lParam)
{
	switch (message)
	{

	case WM_TIMER:
	{
		if (wParam == TIMER_SEC)
			ProcessSecTimer();
		else if (wParam == TIMER_MIN)
			ProcessMinTimer();
	} break;

	case WSA_READBILL:
	{
		if (WSAGETSELECTEVENT(lParam) != FD_READ)
		{
			Log("err Billing connection lost.", "-system", 0);

			BillServerSocket.CloseSocket();
			BillCounter = 360;

			Log("err,billing disconnected.", "-system", 0);

			return TRUE;
		}

		int ret = BillServerSocket.Receive();

		if (ret != TRUE)
		{
			Log("err bill receive fail", "-system", 0);

			BillServerSocket.CloseSocket();
			BillCounter = 360;

			return TRUE;
		}

		if (ret == FALSE)
		{
			ret = WSAGetLastError();

			sprintf(temp, "err,socket %d %d-%d-%d", ret, BillServerSocket.nRecvPosition, BillServerSocket.nProcPosition, BillServerSocket.nSendPosition);

			ret = BillServerSocket.Receive();

			if (ret != TRUE)
			{
				Log("err,bill receive retry_recv fail", "-system", 0);

				BillServerSocket.CloseSocket();
				BillCounter = 360;

				break;
			}
		}
		else if (ret == -1)
		{
			sprintf(temp, "clo,bill receive %d-%d-%d", BillServerSocket.nRecvPosition, BillServerSocket.nProcPosition, BillServerSocket.nSendPosition);
			Log(temp, "-system", 0);

			ret = recv(BillServerSocket.Sock, BillServerSocket.pRecvBuffer, RECV_BUFFER_SIZE, NULL);

			BillServerSocket.CloseSocket();
			BillCounter = 360;

			break;
		}

		int Error = 0;
		int ErrorCode = 0;

		while (1)
		{
			char *Msg = BillServerSocket.ReadBillMessage(&Error, &ErrorCode);

			if (Msg == NULL)
				break;

			if (Error == 1 || Error == 2)
			{
				sprintf(temp, "err readbill (%d),%d", Error, ErrorCode);
				Log(temp, "-system", 0);

				break;
			}

			ProcessBILLMessage(Msg);

		};

	}  break;

	case WSA_READDB:
	{
		int t = WSAGETSELECTEVENT(lParam);
		if (WSAGETSELECTEVENT(lParam) != FD_READ)
		{
			Log("err wsareaddb fail", "-system", 0);

			DBServerSocket.CloseSocket();

			int ret = 0;

			for (int i = 0; i < 2; i++)
			{
				int *pip = (int*)LocalIP;

				ret = DBServerSocket.ConnectServer(DBServerAddress, DBServerPort, *pip, WSA_READDB);

				if (ret != NULL)
					break;

				Sleep(200);
			}

			if (ret == 0)
			{
				Log("reconnect DB fail.", "-system", 0);

				PostQuitMessage(NULL);

				return TRUE;

			}

			Sleep(200);
			PostQuitMessage(NULL);
			return TRUE;
		}

		if (DBServerSocket.Receive() == FALSE)
		{
			Log("err wsareaddb fail", "-system", 0);

			DBServerSocket.CloseSocket();

			int ret = 0;

			for (int i = 0; i < 2; i++)
			{
				int *pip = (int*)LocalIP;

				ret = DBServerSocket.ConnectServer(DBServerAddress, DBServerPort, *pip, WSA_READDB);

				if (ret != NULL)
					break;

				Sleep(200);
			}

			if (ret == 0)
			{
				Log("reconnect DB fail.", "-system", 0);

				PostQuitMessage(NULL);

				return TRUE;

			}
			PostQuitMessage(NULL);
			return TRUE;

		}

		int Error = 0;
		int ErrorCode = 0;

		while (1)
		{
			char *Msg = DBServerSocket.ReadMessage(&Error, &ErrorCode);

			if (Msg == NULL)
				break;


#ifdef  _PACKET_DEBUG
			MSG_STANDARD *debug = (MSG_STANDARD*)Msg;

			if (BASE_CheckPacket(debug))
			{
				sprintf(temp, "**PACKET_DEBUG** Type:%d Size:%d", debug->Type, debug->Size);
				Log(temp, "-system", 0);

				break;
			}
#endif

			if (Error == 1 || Error == 2)
			{
				sprintf(temp, "err readdb (%d),%d", Error, ErrorCode);
				Log(temp, "-system", 0);
				break;
			}

			ProcessDBMessage(Msg);
		};

	} break;

	case  WSA_READ:
	{
		int User = GetUserFromSocket(wParam);
		if (User == 0)
		{
			closesocket(wParam);

			break;
		}

		if (WSAGETSELECTEVENT(lParam) != FD_READ)
		{
			sprintf(temp, "clo,fd %d-%d", pUser[User].Mode, pMob[User].Mode);
			Log(temp, pUser[User].AccountName, pUser[User].IP);

			CloseUser(User);
			break;
		}

		int ret = pUser[User].cSock.Receive();

		if (ret == FALSE)
		{
			ret = WSAGetLastError();

			sprintf(temp, "err,socket %d %d-%d-%d %d-%d", ret, pUser[User].cSock.nRecvPosition, pUser[User].cSock.nProcPosition, pUser[User].cSock.nSendPosition, pUser[User].Mode, pMob[User].Mode);

			ret = pUser[User].cSock.Receive();

			if (ret == FALSE)
			{
				Log("err,retry_recv fail", pUser[User].AccountName, pUser[User].IP);

				CloseUser(User);

				break;
			}
		}
		else if (ret == -1)
		{
			sprintf(temp, "clo,receive %d-%d-%d %d-%d", pUser[User].cSock.nRecvPosition, pUser[User].cSock.nProcPosition, pUser[User].cSock.nSendPosition, pUser[User].Mode, pMob[User].Mode);

			Log("clo,receive %d-%d-%d", pUser[User].AccountName, pUser[User].IP);

			ret = recv(pUser[User].cSock.Sock, pUser[User].cSock.pRecvBuffer, RECV_BUFFER_SIZE, NULL);

			CloseUser(User);

			break;
		}

		int Error = 0;
		int ErrorCode = 0;

		while (1)
		{
			char *Msg = pUser[User].cSock.ReadMessage(&Error, &ErrorCode);

			if (Msg == NULL)
				break;

#ifdef  _PACKET_DEBUG
			MSG_STANDARD *debug = (MSG_STANDARD*)Msg;

			if (Msg != NULL && BASE_CheckPacket(debug))
			{
				sprintf(temp, "**PACKET_DEBUG** Type:%d Size:%d", debug->Type, debug->Size);
				Log(temp, "-system", 0);
			}
#endif

			if (Error == 1 || Error == 2)
			{
				pUser[User].AccountName[ACCOUNTNAME_LENGTH - 1] = 0;
				pUser[User].AccountName[ACCOUNTNAME_LENGTH - 2] = 0;

				sprintf(temp, "err,read (%d),%d", Error, ErrorCode);
				Log(temp, pUser[User].AccountName, pUser[User].IP);

				break;
			}

			ProcessClientMessage(User, Msg, FALSE);
		};

	} break;

	case WSA_ACCEPT:
	{
		if (WSAGETSELECTERROR(lParam) == 0)
		{

			int User = GetEmptyUser();

			if (User == 0)
			{
				Log("err,accept fail - no empty", "-system", 0);

				break;
			}

			int ret = pUser[User].AcceptUser(ListenSocket.Sock);

			if (User >= MAX_USER - ADMIN_RESERV)
			{
				SendClientMsg(User, g_pMessageStringTable[_NN_Reconnect]);
				pUser[User].cSock.SendMessageA();

				CloseUser(User);

				return TRUE;
			}

			if (ServerDown != -1000)
			{
				SendClientMsg(User, g_pMessageStringTable[_NN_ServerReboot_Cant_Connect]);

				CloseUser(User);

				return TRUE;
			}

		}
		else
			Log("err,- accept - wsagetselecterror", "-system", 0);

	} break;

	case WM_PAINT:
		PAINTSTRUCT ps;
		BeginPaint(hWnd, &ps);
		DrawConfig(0);

		EndPaint(hWnd, &ps);
		break;

	case WM_CREATE:
	{
		HMENU hMenu, hSubMenu;
		// HICON hIcon, hIconSm;

		hMenu = CreateMenu();

		hSubMenu = CreatePopupMenu();
		AppendMenu(hSubMenu, MF_STRING, IDC_EXIT, "&Exit");
		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&File");

		hSubMenu = CreatePopupMenu();
		AppendMenu(hSubMenu, MF_STRING, IDC_MOBRELOAD, "&Load Mob");
		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Mob");

		hSubMenu = CreatePopupMenu();
		AppendMenu(hSubMenu, MF_STRING, IDC_REBOOT, "&Desligar");
		AppendMenu(hSubMenu, MF_STRING, IDC_SAVEALL, "&SaveAll");
		AppendMenu(hSubMenu, MF_STRING, IDC_READGUILD, "&Load Guild");
		AppendMenu(hSubMenu, MF_STRING, IDC_READGUILDNAME, "&Load Guild Name");
		AppendMenu(hSubMenu, MF_STRING, IDC_READGAMECONFIG, "&Load Game Config");
		AppendMenu(hSubMenu, MF_STRING, IDC_READSKILLDATA, "&Load Skill Data");
		AppendMenu(hSubMenu, MF_STRING, IDC_READ_START_LOG, "&Load Start Log");
		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Sistema");

		hSubMenu = CreatePopupMenu();
		AppendMenu(hSubMenu, MF_STRING, IDC_READQUIZ, "&Load Quiz");
		AppendMenu(hSubMenu, MF_STRING, IDC_READ_PREMIO_LOJAAFK, "&Load Premio Loja Afk");
		AppendMenu(hSubMenu, MF_STRING, IDC_READ_LOTTERY, "&Load Lottery");
		AppendMenu(hSubMenu, MF_STRING, IDC_READ_BOX_EVENT, "&Load Box Event");
		AppendMenu(hSubMenu, MF_STRING, IDC_READ_ALTAR_OF_KING, "&Load Altar Of King");
		AppendMenu(hSubMenu, MF_STRING, IDC_READ_AUTO_EVENT, "&Load Auto Event");
		AppendMenu(hSubMenu, MF_STRING, IDC_READ_EVENT_TRADE, "&Load Event Trade");
		AppendMenu(hSubMenu, MF_STRING, IDC_READ_COLISEU, "&Load Event Coliseu");
		AppendMenu(hSubMenu, MF_STRING, IDC_READ_RVR_WINNER, "&Load Rvr Winner");
		AppendMenu(hSubMenu, MF_STRING, IDC_READ_INVADE_ARMIA, "&Load Invade Armia");
		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Events");

		hSubMenu = CreatePopupMenu();
		AppendMenu(hSubMenu, MF_STRING, IDC_READSANCRATE, "&Load Sanc");
		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Rates");

		hSubMenu = CreatePopupMenu();
		AppendMenu(hSubMenu, MF_STRING, IDC_READ_NPC_BLOCK, "&Load NPC Block");
		AppendMenu(hSubMenu, MF_STRING, IDC_READ_FADA_GROUP, "&Load Fada Dourada");
		AppendMenu(hSubMenu, MF_STRING, IDC_READ_GROUP_ITENS, "&Load Agrupar Itens");
		AppendMenu(hSubMenu, MF_STRING, IDC_READ_DROP_KEFRA, "&Load Drop Kefra");
		AppendMenu(hSubMenu, MF_STRING, IDC_READ_WARS_TIMER, "&Load Wars Timer");
		AppendMenu(hSubMenu, MF_STRING, IDC_READ_BAG_WARRIOR, "&Load Bag Warrior");
		AppendMenu(hSubMenu, MF_STRING, IDC_READ_SOMBRA_NEGRA, "&Load Sombra Negra");
		AppendMenu(hSubMenu, MF_STRING, IDC_READ_BOSS_CAMP, "&Load Boss Camp");
		AppendMenu(hSubMenu, MF_STRING, IDC_READ_STAFF, "&Load Staff List");
		AppendMenu(hSubMenu, MF_STRING, IDC_READ_STATUS_SERVER, "&Load Status Server");
		AppendMenu(hSubMenu, MF_STRING, IDC_READ_TITLE_SYSTEM, "&Load Title System");
		AppendMenu(hSubMenu, MF_STRING, IDC_READ_GUILD_LEVEL, "&Load Guild Level");
		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Config Extra");

		hSubMenu = CreatePopupMenu();
		AppendMenu(hSubMenu, MF_STRING, IDC_CONVERT_NPC, "&Convert NPC to Json");
		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Tools");

		SetMenu(hWnd, hMenu);
	} break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_EXIT:
			PostMessage(hWnd, WM_CLOSE, 0, 0);
			break;

		case IDC_MOBRELOAD:
			mNPCGen.ReadNPCGenerator();
			break;

		case IDC_REBOOT:
			ServerDown = 1;
			break;

		case IDC_SAVEALL:
			SaveAll();
			break;

		case IDC_READGUILD:
			CReadFiles::ReadGuild();
			break;

		case IDC_READGUILDNAME:
			BASE_InitializeGuildName();
			break;

		case IDC_READSKILLDATA:
			BASE_InitializeSkill();
			break;

		case IDC_READQUIZ:
			ReadQuiz();
			break;

		case IDC_READ_PREMIO_LOJAAFK:
			ReadPremioLojaAfk();
			break;

		case IDC_READSANCRATE:
			CReadFiles::ReadSancRate();
			break;

		case IDC_READ_GROUP_ITENS:
			ReadGroupItens();
			break;

		case IDC_READ_FADA_GROUP:
			ReadFadaAmmount();
			break;

		case IDC_READ_NPC_BLOCK:
			ReadNPCBlock();
			break;

		case IDC_READ_LOTTERY:
			ReadLottery();
			break;

		case IDC_READ_DROP_KEFRA:
			ReadDropKefra();
			break;

		case IDC_READ_WARS_TIMER:
			ReadWarsTimer();
			break;

		case IDC_CONVERT_NPC:
			//ConvertNPC();
			OpenConfigExtra();
			break;
			
		case IDC_READ_BOX_EVENT:
			ReadBoxEvent();
			break;

		case IDC_READ_ALTAR_OF_KING:
			ReadAltarOfKing();
			break;

		case IDC_READ_BAG_WARRIOR:
			ReadBagWarrior();
			break;

		case IDC_READ_AUTO_EVENT:
			ReadAutoEvent();
				break;

		case IDC_READ_SOMBRA_NEGRA:
			ReadSombraNegra();
			break;

		case IDC_READ_EVENT_TRADE:
			ReadEventTrade();
			break;

		case IDC_READ_COLISEU:
			ReadColiseu();
			break;

		case IDC_READ_STAFF:
			ReadStaff();
			break;

		case IDC_READ_BOSS_CAMP:
			ReadBossCamp();
			break;

		case IDC_READ_STATUS_SERVER:
			ReadStatusServer();
			break;

		case IDC_READ_START_LOG:
			StartLog();
			break;

		case IDC_READ_TITLE_SYSTEM:
			ReadTitleSystem();
			break;

		case IDC_READ_GUILD_LEVEL:
			ReadGuildLevel();
			break;

		case IDC_READ_RVR_WINNER:
			ReadRvrWinner();
			break;

		case IDC_READ_INVADE_ARMIA:
			ReadInvadeArmia();
			break;

		case IDC_READGAMECONFIG:
		{
			ReadConfig();
			DrawConfig(0);
		} break;
		}
	} break;
	case WM_CLOSE:
	{
		if (MessageBox(hWndMain, "Você realmente deseja desligar o server?", "Aviso!!!", MB_ICONQUESTION | MB_YESNO) == IDNO)
			break;

		if (BILLING != 0)
		{
			_AUTH_GAME sm;
			memset(&sm, 0, sizeof(sm));
			SendBilling2(&sm, 4);

			BILLING = 0;
		}

		CReadFiles::WriteGuild();

		nConfig::WriteGameConfig(PATH_CONFIG, "gameConfig.json");
		WriteSombraNegra();

		if (fLogFile)
			fclose(fLogFile);

		if (FLogSystem)
			fclose(FLogSystem);
		if (FLogQuests)
			fclose(FLogQuests);
		if (FLogDebugs)
			fclose(FLogDebugs);
		if (FLogEvents)
			fclose(FLogEvents);
		if (FLogCombine)
			fclose(FLogCombine);
		if (FLogItens)
			fclose(FLogItens);

		if (hFont)
		{
			DeleteObject(hFont);
			hFont = NULL;
		}

		DefWindowProc(hWnd, message, wParam, lParam);

	} break;

	case WM_DESTROY:
		WSACleanup();
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

int  GetUserInArea(int x1, int y1, int x2, int y2, char *MobName)
{
	int userCount = 0;

	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;

		if (pMob[i].Mode == 0)
			continue;

		if (pMob[i].TargetX >= x1 && pMob[i].TargetX <= x2 && pMob[i].TargetY >= y1 && pMob[i].TargetY <= y2)
		{
			strncpy(MobName, pMob[i].MOB.MobName, NAME_LENGTH);
			userCount++;
		}
	}
	return userCount;
}

void MountProcess(int conn, STRUCT_ITEM *Mount)
{
	STRUCT_ITEM *MItem = &pMob[conn].MOB.Equip[14];

	int IsEqual = 1;

	if (Mount != NULL)
		IsEqual = memcmp(Mount, MItem, sizeof(STRUCT_ITEM));

	if (IsEqual != 0)
		return;

	int leaderid = pMob[conn].Leader;

	if (leaderid == 0)
		leaderid = conn;

	
	for (int i = 0; i < MAX_PARTY; i++)
	{
		int partyconn = pMob[leaderid].PartyList[i];

		if (partyconn <= 0 || partyconn > MAX_MOB)
			continue;

		int face = pMob[partyconn].MOB.Equip[0].sIndex;

		if (pMob[partyconn].Summoner == conn)
		{
			if (face >= 315 && face < 345)
				DeleteMob(partyconn, 3);
		}
	}

	int MBabyId = MItem->sIndex - 2320;


	if (MBabyId >= 10 && MBabyId < 40)
	{
		int MHp = BASE_GetItemAbility(MItem, EF_MOUNTHP);

		if (MHp > 0)
			GenerateSummon(conn, MBabyId, MItem, 1);
	}
}

void LinkMountHp(int mobconn)
{
	if (mobconn < MAX_USER || mobconn >= MAX_MOB)
		return;

	if (pMob[mobconn].MOB.Clan != 4)
		return;

	int face = pMob[mobconn].MOB.Equip[0].sIndex;

	if (face < 315 || face >= 345)
		return;

	int Summoner = pMob[mobconn].Summoner;

	if (Summoner <= 0 || Summoner >= MAX_USER)
		return;

	if (pMob[Summoner].Mode == USER_EMPTY)
		return;

	if (pUser[Summoner].Mode != USER_PLAY)
		return;



	int mountId = pMob[Summoner].MOB.Equip[14].sIndex - 2330;
	int mountFace = face - 315;

	if ((face - 315) != mountId)
		return;

	int mountHpItem = pMob[Summoner].MOB.Equip[14].stEffect[0].sValue;
	int mountHp = pMob[mobconn].MOB.CurrentScore.Hp;

	if (mountHpItem == mountHp)
		return;


	pMob[Summoner].MOB.Equip[14].stEffect[0].sValue = mountHp;
	SendItem(Summoner, ITEM_PLACE_EQUIP, 14, &pMob[Summoner].MOB.Equip[14]);
}

void ProcessAdultMount(int conn, int HpLost)
{
	STRUCT_ITEM *MItem = &pMob[conn].MOB.Equip[14];

	if (MItem->sIndex < 2360 || MItem->sIndex >= 2390)
		return;

	int midx = MItem->sIndex - 2360;
	int MMaxHp = mSummon.Mob[midx + 10].CurrentScore.MaxHp;
	int MFeed = MItem->stEffect[2].cEffect;

	for (int i = 0; i < MAX_AFFECT; i++)
	{
		if (pMob[conn].Affect[i].Type == 51)
			return;
	}

	if (MFeed <= 0 && MItem->stEffect[0].sValue > 0)
	{
		MItem->stEffect[0].sValue = 0;
		MFeed = 0;
	}

	int MHp = MItem->stEffect[0].sValue;
	int MHp2 = MItem->stEffect[0].sValue - HpLost;

	if (MHp2 >= MMaxHp)
		MHp2 = MMaxHp;

	int NMHp = MHp2;

	MItem->stEffect[0].sValue = NMHp;

	if (MHp2 <= 0)
		MItem->stEffect[2].cEffect = 0;

	if ((MHp <= 0 && MHp2 > 0) || (MHp2 <= 0 && MHp > 0))
		SendEquip(conn, 0);

	if (MHp != MHp2 && conn < MAX_USER)
		SendItem(conn, ITEM_PLACE_EQUIP, 14, &pMob[conn].MOB.Equip[14]);
}

void ProcessBILLMessage(char *pMsg)
{
}

void CheckIdle(int conn)
{
	int ser = SecCounter;
	int lst = pUser[conn].LastReceiveTime;

	if (lst > ser)
		pUser[conn].LastReceiveTime = SecCounter;

	if (lst < ser - 1440)
		pUser[conn].LastReceiveTime = SecCounter;

	if (lst < ser - 720)
	{
		sprintf(temp, "sys,disconnect last:%d server:%d mode:%d conn:%d", pUser[conn].LastReceiveTime, SecCounter, pUser[conn].Mode, conn);
		Log(temp, pUser[conn].AccountName, 0);

		CloseUser(conn);
	}
}

/*
void FinishCastleWar()
{
	SetCastleDoor(1);

	ClearAreaGuild(1036, 1672, 1144, 1764, g_pGuildZone[4].ChargeGuild);

	CastleState = 0;

	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;

		SendClientSignal(i, _MSG_SendCastleState, CastleState);
	}

	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;

		SendClientSignalParm(i, ESCENE_FIELD, _MSG_SendCastleState, CastleState);
	}

	for (int i = MAX_USER; i < MAX_MOB; i++)
	{
		if (pMob[i].Mode == MOB_EMPTY)
			continue;

		if (pMob[i].MOB.Equip[0].sIndex != 219)
			continue;

		DeleteMob(i, 2);
	}

	ClearArea(1036, 1672, 1144, 1764);
}*/

void RegenMob(int conn)
{
	if (conn > 0 && conn < MAX_USER)
	{
		
		int Guild = pMob[conn].MOB.Guild;
		/*if (CastleState <= 1 || pMob[conn].TargetX != 1046 || pMob[conn].TargetY != 1690 || Guild <= 0 || pMob[conn].MOB.GuildLevel < 6 || Guild == g_pGuildZone[4].ChargeGuild)
			pUser[conn].CastleStatus = 0;
		
		else
		{
			int Citys = 0;

			for (int i = 0; i < ValidGuild; i++)
			{
				if (g_pGuildZone[i].ChargeGuild == pMob[conn].MOB.Guild && i != 4)
					Citys++;
			}

			if (Citys != 0)
			{
				if (pUser[conn].CastleStatus == 0)
				{
					sprintf(temp, g_pMessageStringTable[_SN_S_is_charging_castle], pMob[conn].MOB.MobName);
					SendNotice(temp);
				}
				MSG_STANDARDPARM sm;
				memset(&sm, 0, sizeof(MSG_STANDARDPARM));

				sm.Type = _MSG_SendCastleState2;
				sm.Size = sizeof(MSG_STANDARDPARM);
				sm.ID = conn;
				sm.Parm = 1;

				GridMulticast(pMob[conn].TargetX, pMob[conn].TargetY, (MSG_STANDARD*)&sm, 0);

				//Contador Altar de Thor
				pUser[conn].CastleStatus++;
				SendClientSignalParmCoord(conn, ESCENE_FIELD, _MSG_StartTime, pUser[conn].CastleStatus++, 1046, 1690, 1046, 1690);

				if (pUser[conn].CastleStatus > 22)//Dominou o Altar
				{
					sprintf(temp, g_pMessageStringTable[_SN_S_charge_castle], pMob[conn].MOB.MobName);
					SendNotice(temp);

					g_pGuildZone[4].ChargeGuild = Guild;
					g_pGuildZone[4].Clan = pMob[conn].MOB.Clan;

					FinishCastleWar();

					for (int i = 0; i < MAX_USER; i++)
						ClearCrown(i);
				}
			}
		}*/

		pUser[conn].Unk_2736++;

		//if (!(pUser[conn].Unk_2736 % 10))pra test
		if (!(pUser[conn].Unk_2736 % 450))
		{
			int PKP = GetPKPoint(conn);
			if (PKP < 75)
			{
				PKP++;
				SetPKPoint(conn, PKP);
				sprintf(temp, g_pMessageStringTable[_DD_PKPointPlus], PKP - 75, 1);
				SendClientMsg(conn, temp);
			}

			STRUCT_ITEM *Mount = &pMob[conn].MOB.Equip[14];
			if (pMob[conn].MOB.Equip[14].sIndex >= 2300 && Mount->sIndex < 2330)
			{
				int Incubacao = BASE_GetBonusItemAbility(Mount, EF_INCUDELAY);
				if (Incubacao > 0)
				{
					Incubacao--;
					Mount->stEffect[2].cValue = Incubacao;
					SendItem(conn, ITEM_PLACE_EQUIP, 14, &pMob[conn].MOB.Equip[14]);
					SendClientMsg(conn, g_pMessageStringTable[_NN_Incu_Proceed]);
				}
			}
			if (Mount->sIndex >= 2330 && Mount->sIndex < 2390 && Mount->stEffect[0].sValue > 0 && !GetMountProtect(conn))
			{
				int Feed = Mount->stEffect[2].cEffect;
				int MountDiv = Mount->sIndex - 2330 % 30;

				if (MountDiv > 15)
					Feed -= 4;
				else
					Feed -= 2;

				if (Feed > 1)
					Mount->stEffect[2].cEffect = Feed;

				else
				{
					Mount->stEffect[0].sValue = 0;
					Mount->stEffect[2].cEffect = 4;

					SendClientMsg(conn, g_pMessageStringTable[_NN_Mount_died]);

					memcpy(&pMob[conn].MOB.Equip[14], Mount, sizeof(STRUCT_ITEM));

					Mount->stEffect[2].cEffect = 0;

					if (Mount->sIndex >= 2360 && Mount->sIndex < 2390)
						ProcessAdultMount(conn, 0);

					if (Mount->sIndex >= 2360)
						pMob[conn].GetCurrentScore(conn);

					else
						MountProcess(conn, Mount);
				}
				SendItem(conn, ITEM_PLACE_EQUIP, 14, &pMob[conn].MOB.Equip[14]);
			}
		}
		int Guilty = GetGuilty(conn);

		if (Guilty > 0)
		{
			Guilty--;
			SetGuilty(conn, Guilty);

			if (!Guilty)
			{
				MSG_CreateMob CreateMob;
				GetCreateMob(conn, &CreateMob);
				GridMulticast(pMob[conn].TargetX, pMob[conn].TargetY, (MSG_STANDARD*)&CreateMob, 0);
				
				for (int j = MAX_USER; j < MAX_MOB; j++)
				{
					if (pMob[j].Mode == 5 && pMob[j].MOB.Clan == 4)
					{
						if (pMob[j].CurrentTarget == conn)
						{
							pMob[j].CurrentTarget = 0;
							pMob[j].Mode = 4;
						}
						for (int k = 0; k < MAX_ENEMY; k++)
						{
							if (pMob[j].EnemyList[k] == conn)
							{
								pMob[j].EnemyList[k] = 0;
								pMob[j].Mode = MOB_PEACE;
							}
						}
					}
				}
			}
		}
	}	
}

int  ProcessAffect(int idx)
{
	int FadaIndex = FadaIndex = pMob[idx].MOB.Equip[13].sIndex;
	int currentTarget = pMob[idx].CurrentTarget;

	if (idx >= MAX_USER || FadaIndex != 753 && FadaIndex != 769 && FadaIndex != 1726 || currentTarget == 0)
		goto LABEL_59;

	if (currentTarget == idx)
		pMob[idx].CurrentTarget = 0;

#pragma region Fada attack
	else
	{
		if (currentTarget > 0 && currentTarget < MAX_MOB)
		{
			if (pMob[currentTarget].Mode)
			{
				unsigned char map_att = GetAttribute(pMob[idx].TargetX, pMob[idx].TargetY);

				if (map_att & 0x40 || currentTarget >= MAX_USER && pMob[currentTarget].MOB.Clan != 4)
				{
					if (pUser[idx].PKMode || currentTarget >= MAX_USER)
					{
						int leader = pMob[idx].Leader;
						if (!leader)
							leader = idx;

						int targetleader = pMob[currentTarget].Leader;
						if (!targetleader)
							targetleader = currentTarget;

						int guild = pMob[idx].MOB.Guild;
						if (pMob[idx].GuildDisable)
							guild = 0;

						int mobguild = pMob[currentTarget].MOB.Guild;
						if (pMob[currentTarget].GuildDisable)
							mobguild = 0;

						if (!guild && !mobguild)
							guild = -1;

						if (leader != targetleader && guild != mobguild)
						{
							if (currentTarget < MAX_USER)
							{
								unsigned char map_att2 = GetAttribute(pMob[currentTarget].TargetX, pMob[currentTarget].TargetY);

								if (!(map_att & 0x40))
								{
									pMob[idx].CurrentTarget = 0;
									goto LABEL_59;
								}
								if (pMob[currentTarget].MOB.Rsv & 0x10)
								{
									pMob[idx].CurrentTarget = 0;
									goto LABEL_59;
								}
								if (pMob[currentTarget].MOB.BaseScore.Level >= MAX_LEVEL && pMob[currentTarget].MOB.Merchant & 1)
								{
									pMob[idx].CurrentTarget = 0;
									goto LABEL_59;
								}
							}
							int sameclan = 0;
							int clan = pMob[idx].MOB.Clan;
							int mobclan = pMob[currentTarget].MOB.Clan;

							if (clan == 7 && mobclan == 7 || clan == 8 && mobclan == 8)
								sameclan = 1;

							if ((sameclan != 1 || pUser[idx].PKMode) && (sameclan != 1 || currentTarget < MAX_USER))
							{
								if (pMob[currentTarget].TargetX >= pMob[idx].TargetX - HALFGRIDX
									&& pMob[currentTarget].TargetX <= pMob[idx].TargetX + HALFGRIDX
									&& (pMob[currentTarget].TargetY >= pMob[idx].TargetY - HALFGRIDY || pMob[currentTarget].TargetY <= pMob[idx].TargetY + HALFGRIDY))
								{
									MSG_Attack sm;

									memset(&sm, 0, sizeof(MSG_AttackOne));

									sm.Type = _MSG_AttackOne;
									sm.ID = idx;
									sm.Size = sizeof(MSG_AttackOne);

									//check
									sm.ClientTick = 0xE0A1ACA;
									sm.Motion = 254;

									sm.TargetX = pMob[idx].TargetX;
									sm.TargetY = pMob[idx].TargetY;

									//check
									sm.CurrentMp = -2;
									//check
									sm.AttackerID = idx;

									//check
									sm.SkillIndex = 32;

									if (FadaIndex == 769)
										sm.SkillIndex = 34;
									if (FadaIndex == 1726)
										sm.SkillIndex = 36;

									sm.Dam[0].TargetID = currentTarget;
									sm.Dam[0].Damage = -1;

									ProcessClientMessage(idx, (char*)&sm, TRUE);
								}
								else
									pMob[idx].CurrentTarget = 0;
							}
							goto LABEL_59;
						}
						pMob[idx].CurrentTarget = 0;
					}
					else
						pMob[idx].CurrentTarget = 0;
				}
				else
					pMob[idx].CurrentTarget = 0;
			}
			else
				pMob[idx].CurrentTarget = 0;
		}
		else
			pMob[idx].CurrentTarget = 0;
	}
#pragma endregion
	LABEL_59:

			int regen = 0;
			int upScore = 0;
			int FaceChange = 0;
			int Damage = 0;

			for (int i = 0; i < MAX_AFFECT; i++)
			{
				int Type = pMob[idx].Affect[i].Type;

				if (Type <= 0)
					continue;


				int MaxHp = pMob[idx].MOB.CurrentScore.MaxHp;
				int Hp = pMob[idx].MOB.CurrentScore.Hp;
				int AffectValue = pMob[idx].Affect[i].Value;
				int AffectLevel = pMob[idx].Affect[i].Level;
				int Level = pMob[idx].MOB.CurrentScore.Level;

				if (pMob[idx].Extra.ClassMaster != MORTAL && pMob[idx].Extra.ClassMaster != ARCH)
					Level += MAX_LEVEL;

#pragma region Regen de HP Aura da Vida
				if (Type == 17)
				{
					Hp += AffectLevel / 2 + AffectValue;

					if (Hp < 1)
						Hp = 1;

					if (Hp > MaxHp)
						Hp = MaxHp;

					if (pMob[idx].MOB.CurrentScore.Hp != Hp)
						upScore = 1;

					Damage = Hp - pMob[idx].MOB.CurrentScore.Hp;

					pMob[idx].MOB.CurrentScore.Hp = Hp;
					regen = 1;
					goto LessAffect;
				}
#pragma endregion
#pragma region Veneno - Drenagem de HP
				if (Type == 20) //??? Possivelmente Veneno's
				{
					AffectValue = 100;

					if (idx >= MAX_USER)
						AffectValue -= pMob[idx].MOB.LearnedSkill / MAX_USER;

					AffectValue /= 10;

					int HpLose = (int)((100 - AffectValue) / 100.0);
					int Perda = 500; //1000

					if (idx >= MAX_USER)
						Perda = 10 * (100 - pMob[idx].MOB.LearnedSkill / MAX_USER);

					int Perdamax = Hp - Perda;

					Hp = (int)((double)Hp * HpLose);

					if (Hp < (signed int)Perdamax)
						Hp = Perdamax;

					if (Hp < 1)
						Hp = 1;

					if (Hp > MaxHp)
						Hp = MaxHp;

					if (pMob[idx].MOB.CurrentScore.Hp != Hp)
						upScore = 1;

					Damage = Hp - pMob[idx].MOB.CurrentScore.Hp;

					pMob[idx].MOB.CurrentScore.Hp = Hp;

					if (idx > 0 && idx < MAX_USER)
						pUser[idx].HP += Damage;

					regen = 1;

					if (idx > MAX_USER && pMob[idx].MOB.Clan == 4)
						LinkMountHp(idx);

					goto LessAffect;
				}
#pragma endregion
#pragma region RegenHP Type21
				/*		if (Type == 21)//Regen de HT
						{
							Hp += AffectValue * MaxHp / 100;

							if (Hp < 1)
								Hp = 1;

							if (Hp > MaxHp)
								Hp = MaxHp;

							if (pMob[idx].MOB.CurrentScore.Hp != Hp)
								upScore = 1;

							Damage = Hp - pMob[idx].MOB.CurrentScore.Hp;

							pMob[idx].MOB.CurrentScore.Hp = Hp;
							regen = 1;

							goto LessAffect;
						}*/
#pragma endregion
#pragma region Trovão
				if (Type == 22)
				{
					int alvo1 = 0;
					int alvo2 = 0;
					int alvo3 = 0;
					int alvo4 = 0;
					int alvo6 = 0;
					int alvo7 = 0;

					unsigned char map_att = GetAttribute(pMob[idx].TargetX, pMob[idx].TargetY);

					int Clan = pMob[idx].MOB.Clan;

					if (map_att & 1)
						goto LessAffect;

					int yv = pMob[idx].TargetY - 1;
					int xv = pMob[idx].TargetX - 1;
					int leader = pMob[idx].Leader;

					if (leader <= 0)
						leader = idx;

					for (int yy = yv; yy <= (yv + 1); yy++)
					{
						for (int xx = xv; xx <= (xv + 1); xx++)
						{
							if (xx < 0 || xx >= MAX_GRIDX || yy < 0 || yy >= MAX_GRIDY || pMobGrid[yy][xx] <= 0 || pMobGrid[yy][xx] >= MAX_MOB || !pMob[pMobGrid[yy][xx]].Mode || pMob[pMobGrid[yy][xx]].MOB.CurrentScore.Hp <= 0 || leader == pMob[pMobGrid[yy][xx]].Leader)
								continue;

							int tmob = pMobGrid[yy][xx];

							int tclan = pMob[tmob].MOB.Clan;
							int SameClan = 0;

							if (Clan == 7 && tclan == 7 || Clan == 8 && tclan == 8)
								SameClan = 1;

							if (pMob[tmob].MOB.Merchant & 1)
								continue;

							if (pMob[tmob].MOB.Merchant == 1) continue;

							unsigned char map_attack = GetAttribute(xx, yy);

							if (map_attack & 1)
								continue;

							if (idx >= MAX_USER)
								break;

							if ((pUser[idx].PKMode || tmob >= MAX_USER && tclan != 4 && SameClan != 1) && (map_att & 0x40 || tmob >= 100 && tclan != 4 && SameClan != 1) && !(pMob[tmob].MOB.Rsv & 0x10))
							{
								if (SameClan == 1 && tmob >= MAX_USER || tclan == 6 || tmob == idx)
									continue;

								int idxleader = pMob[idx].Leader;

								if (!idxleader)
									idxleader = idx;

								int mobleader = pMob[tmob].Leader;
								if (!mobleader)
									mobleader = tmob;

								int Guild = pMob[idx].MOB.Guild;

								if (pMob[idx].GuildDisable)
									Guild = 0;

								int MobGuild = pMob[tmob].MOB.Guild;

								if (pMob[tmob].GuildDisable)
									MobGuild = 0;

								int Ally = g_pGuildAlly[Guild];

								if (!Ally)
									Ally = -2;

								if (!Guild && !MobGuild)
									Guild = -1;

								if (idxleader == mobleader || Guild == MobGuild || Ally == MobGuild)
									continue;

								if (!alvo1)
								{
									alvo1 = tmob;
									continue;
								}

								if (alvo1 == tmob)
									continue;

								if (!alvo2)
								{
									alvo2 = tmob;
									continue;
								}
								if (alvo2 == tmob)
									continue;

								if (!alvo3)
								{
									alvo3 = tmob;
									continue;
								}
								if (alvo3 == tmob)
									continue;

								if (!alvo4)
								{
									alvo4 = tmob;
									continue;
								}
								if (alvo4 == tmob)
									continue;

								if (!alvo6)
								{
									alvo6 = tmob;
									continue;
								}

								if (alvo6 == tmob || alvo7)
									continue;

								alvo7 = tmob;
							}
						}
					}

					yv = pMob[idx].TargetY - 4;
					xv = pMob[idx].TargetX - 4;

					for (int yy = yv; yy <= (yv + 4); yy++)
					{
						for (int xx = xv; xx <= (xv + 4); xx++)
						{
							if (xx < 0 || xx >= MAX_GRIDX || yy < 0 || yy >= MAX_GRIDY || pMobGrid[yy][xx] <= 0 || pMobGrid[yy][xx] >= MAX_MOB || !pMob[pMobGrid[yy][xx]].Mode || pMob[pMobGrid[yy][xx]].MOB.CurrentScore.Hp <= 0 || leader == pMob[pMobGrid[yy][xx]].Leader)
								continue;

							int tmob = pMobGrid[yy][xx];

							int tclan = pMob[tmob].MOB.Clan;
							int SameClan = 0;

							if (Clan == 7 && tclan == 7 || Clan == 8 && tclan == 8)
								SameClan = 1;

							if (pMob[tmob].MOB.Merchant & 1)
								continue;

							unsigned char map_attack = GetAttribute(xx, yy);

							if (map_attack & 1)
								continue;

							if (idx >= MAX_USER)
								break;

							if ((pUser[idx].PKMode || tmob >= MAX_USER && tclan != 4 && SameClan != 1) && (map_att & 0x40 || tmob >= MAX_USER && tclan != 4 && SameClan != 1) && !(pMob[tmob].MOB.Rsv & 0x10))
							{
								if (SameClan == 1 && tmob >= MAX_USER || tclan == 6 || tmob == idx)
									continue;

								int idxleader = pMob[idx].Leader;

								if (!idxleader)
									idxleader = idx;

								int mobleader = pMob[tmob].Leader;
								if (!mobleader)
									mobleader = tmob;

								int Guild = pMob[idx].MOB.Guild;

								if (pMob[idx].GuildDisable)
									Guild = 0;

								int MobGuild = pMob[tmob].MOB.Guild;

								if (pMob[tmob].GuildDisable)
									MobGuild = 0;

								int Ally = g_pGuildAlly[Guild];

								if (!Ally)
									Ally = -2;

								if (!Guild && !MobGuild)
									Guild = -1;

								if (idxleader == mobleader || Guild == MobGuild || Ally == MobGuild)
									continue;

								if (!alvo1)
								{
									alvo1 = tmob;
									continue;
								}

								if (alvo1 == tmob)
									continue;

								if (!alvo2)
								{
									alvo2 = tmob;
									continue;
								}
								if (alvo2 == tmob)
									continue;

								if (!alvo3)
								{
									alvo3 = tmob;
									continue;
								}
								if (alvo3 == tmob)
									continue;

								if (!alvo4)
								{
									alvo4 = tmob;
									continue;
								}
								if (alvo4 == tmob)
									continue;

								if (!alvo6)
								{
									alvo6 = tmob;
									continue;
								}

								if (alvo6 == tmob || alvo7)
									continue;

								alvo7 = tmob;
							}
						}
					}

					if (alvo1)
					{
						MSG_Attack sm;

						memset(&sm, 0, sizeof(MSG_Attack));

						sm.Type = _MSG_Attack;
						sm.ID = idx;
						sm.Size = sizeof(MSG_Attack);

						sm.ClientTick = 0xE0A1ACA;
						sm.Motion = 254;

						sm.TargetX = pMob[idx].TargetX;
						sm.TargetY = pMob[idx].TargetY;

						sm.CurrentMp = -2;

						if (pMob[idx].MOB.Equip[0].sIndex == 219)
							sm.CurrentMp = -4;

						sm.AttackerID = idx;
						sm.SkillIndex = 33;

						//srand(time(NULL));
						int calc = 500 + rand() % 100 + (pMob[idx].Extra.ClassMaster == MORTAL || pMob[idx].Extra.ClassMaster == MORTAL ? Level : Level + MAX_CLEVEL) + AffectLevel;

						sm.Dam[0].TargetID = alvo1;
						sm.Dam[0].Damage = -1;

						if (calc > 300)
						{
							sm.Dam[1].TargetID = alvo2;
							sm.Dam[1].Damage = -1;
						}

						if (calc > 350)
						{
							sm.Dam[2].TargetID = alvo3;
							sm.Dam[2].Damage = -1;
						}

						if (calc > 400)
						{
							sm.Dam[3].TargetID = alvo4;
							sm.Dam[3].Damage = -1;
						}

						if (calc > 450)
						{
							sm.Dam[4].TargetID = alvo6;
							sm.Dam[4].Damage = -1;
						}

						if (calc > 500)
						{
							sm.Dam[5].TargetID = alvo7;
							sm.Dam[5].Damage = -1;
						}

						if (idx < MAX_USER)
							ProcessClientMessage(idx, (char*)&sm, TRUE);
					}
				}
#pragma endregion
#pragma region Aura Bestial
				if (Type == 23)
				{
					int alvo1 = 0;
					int alvo2 = 0;
					int alvo3 = 0;
					int alvo4 = 0;
					int alvo6 = 0;
					int alvo7 = 0;

					unsigned char map_att = GetAttribute(pMob[idx].TargetX, pMob[idx].TargetY);

					int Clan = pMob[idx].MOB.Clan;

					if (map_att & 1)
						goto LessAffect;

					int yv = pMob[idx].TargetY - 1;
					int xv = pMob[idx].TargetX - 1;
					int leader = pMob[idx].Leader;

					if (leader <= 0)
						leader = idx;

					for (int yy = yv; yy <= (yv + 1); yy++)
					{
						for (int xx = xv; xx <= (xv + 1); xx++)
						{
							if (xx < 0 || xx >= MAX_GRIDX || yy < 0 || yy >= MAX_GRIDY || pMobGrid[yy][xx] <= 0 || pMobGrid[yy][xx] >= MAX_MOB || !pMob[pMobGrid[yy][xx]].Mode || pMob[pMobGrid[yy][xx]].MOB.CurrentScore.Hp <= 0 || leader == pMob[pMobGrid[yy][xx]].Leader)
								continue;

							int tmob = pMobGrid[yy][xx];

							int tclan = pMob[tmob].MOB.Clan;
							int SameClan = 0;

							if (Clan == 7 && tclan == 7 || Clan == 8 && tclan == 8)
								SameClan = 1;

							if (pMob[tmob].MOB.Merchant & 1)
								continue;

							if (pMob[tmob].MOB.Merchant == 1) continue;

							unsigned char map_attack = GetAttribute(xx, yy);

							if (map_attack & 1)
								continue;

							if (idx >= MAX_USER)
								break;

							if ((pUser[idx].PKMode || tmob >= MAX_USER && tclan != 4 && SameClan != 1) && (map_att & 0x40 || tmob >= 100 && tclan != 4 && SameClan != 1) && !(pMob[tmob].MOB.Rsv & 0x10))
							{
								if (SameClan == 1 && tmob >= MAX_USER || tclan == 6 || tmob == idx)
									continue;

								int idxleader = pMob[idx].Leader;

								if (!idxleader)
									idxleader = idx;

								int mobleader = pMob[tmob].Leader;
								if (!mobleader)
									mobleader = tmob;

								int Guild = pMob[idx].MOB.Guild;

								if (pMob[idx].GuildDisable)
									Guild = 0;

								int MobGuild = pMob[tmob].MOB.Guild;

								if (pMob[tmob].GuildDisable)
									MobGuild = 0;

								int Ally = g_pGuildAlly[Guild];

								if (!Ally)
									Ally = -2;

								if (!Guild && !MobGuild)
									Guild = -1;

								if (idxleader == mobleader || Guild == MobGuild || Ally == MobGuild)
									continue;

								if (!alvo1)
								{
									alvo1 = tmob;
									continue;
								}

								if (alvo1 == tmob)
									continue;

								if (!alvo2)
								{
									alvo2 = tmob;
									continue;
								}
								if (alvo2 == tmob)
									continue;

								if (!alvo3)
								{
									alvo3 = tmob;
									continue;
								}
								if (alvo3 == tmob)
									continue;

								if (!alvo4)
								{
									alvo4 = tmob;
									continue;
								}
								if (alvo4 == tmob)
									continue;

								if (!alvo6)
								{
									alvo6 = tmob;
									continue;
								}

								if (alvo6 == tmob || alvo7)
									continue;

								alvo7 = tmob;
							}
						}
					}

					yv = pMob[idx].TargetY - 4;
					xv = pMob[idx].TargetX - 4;

					for (int yy = yv; yy <= (yv + 4); yy++)
					{
						for (int xx = xv; xx <= (xv + 4); xx++)
						{
							if (xx < 0 || xx >= MAX_GRIDX || yy < 0 || yy >= MAX_GRIDY || pMobGrid[yy][xx] <= 0 || pMobGrid[yy][xx] >= MAX_MOB || !pMob[pMobGrid[yy][xx]].Mode || pMob[pMobGrid[yy][xx]].MOB.CurrentScore.Hp <= 0 || leader == pMob[pMobGrid[yy][xx]].Leader)
								continue;

							int tmob = pMobGrid[yy][xx];

							int tclan = pMob[tmob].MOB.Clan;
							int SameClan = 0;

							if (Clan == 7 && tclan == 7 || Clan == 8 && tclan == 8)
								SameClan = 1;

							if (pMob[tmob].MOB.Merchant & 1)
								continue;

							unsigned char map_attack = GetAttribute(xx, yy);

							if (map_attack & 1)
								continue;

							if (idx >= MAX_USER)
								break;

							if ((pUser[idx].PKMode || tmob >= MAX_USER && tclan != 4 && SameClan != 1) && (map_att & 0x40 || tmob >= MAX_USER && tclan != 4 && SameClan != 1) && !(pMob[tmob].MOB.Rsv & 0x10))
							{
								if (SameClan == 1 && tmob >= MAX_USER || tclan == 6 || tmob == idx)
									continue;

								int idxleader = pMob[idx].Leader;

								if (!idxleader)
									idxleader = idx;

								int mobleader = pMob[tmob].Leader;
								if (!mobleader)
									mobleader = tmob;

								int Guild = pMob[idx].MOB.Guild;

								if (pMob[idx].GuildDisable)
									Guild = 0;

								int MobGuild = pMob[tmob].MOB.Guild;

								if (pMob[tmob].GuildDisable)
									MobGuild = 0;

								int Ally = g_pGuildAlly[Guild];

								if (!Ally)
									Ally = -2;

								if (!Guild && !MobGuild)
									Guild = -1;

								if (idxleader == mobleader || Guild == MobGuild || Ally == MobGuild)
									continue;

								if (!alvo1)
								{
									alvo1 = tmob;
									continue;
								}

								if (alvo1 == tmob)
									continue;

								if (!alvo2)
								{
									alvo2 = tmob;
									continue;
								}
								if (alvo2 == tmob)
									continue;

								if (!alvo3)
								{
									alvo3 = tmob;
									continue;
								}
								if (alvo3 == tmob)
									continue;

								if (!alvo4)
								{
									alvo4 = tmob;
									continue;
								}
								if (alvo4 == tmob)
									continue;

								if (!alvo6)
								{
									alvo6 = tmob;
									continue;
								}

								if (alvo6 == tmob || alvo7)
									continue;

								alvo7 = tmob;
							}
						}
					}

					if (alvo1)
					{
						MSG_Attack sm;

						memset(&sm, 0, sizeof(MSG_Attack));

						sm.Type = _MSG_Attack;
						sm.ID = idx;
						sm.Size = sizeof(MSG_Attack);

						sm.ClientTick = 0xE0A1ACA;
						sm.Motion = 254;

						sm.TargetX = pMob[idx].TargetX;
						sm.TargetY = pMob[idx].TargetY;

						sm.CurrentMp = -2;

						if (pMob[idx].MOB.Equip[0].sIndex == 219)
							sm.CurrentMp = -4;

						sm.AttackerID = idx;
						sm.SkillIndex = 52;

						//srand(time(NULL));
						int calc = 5000 + rand() % 100 + (pMob[idx].Extra.ClassMaster == MORTAL || pMob[idx].Extra.ClassMaster == MORTAL ? Level : Level + MAX_CLEVEL) + AffectLevel;

						sm.Dam[0].TargetID = alvo1;
						sm.Dam[0].Damage = -1;

						if (calc > 300)
						{
							sm.Dam[1].TargetID = alvo2;
							sm.Dam[1].Damage = -1;
						}

						if (calc > 350)
						{
							sm.Dam[2].TargetID = alvo3;
							sm.Dam[2].Damage = -1;
						}

						if (calc > 400)
						{
							sm.Dam[3].TargetID = alvo4;
							sm.Dam[3].Damage = -1;
						}

						if (calc > 450)
						{
							sm.Dam[4].TargetID = alvo6;
							sm.Dam[4].Damage = -1;
						}

						if (calc > 500)
						{
							sm.Dam[5].TargetID = alvo7;
							sm.Dam[5].Damage = -1;
						}

						if (idx < MAX_USER)
							ProcessClientMessage(idx, (char*)&sm, TRUE);
					}
				}
#pragma endregion
#pragma region Affects less time
				LessAffect :
						   if (pMob[idx].Affect[i].Time < 32400000)
							   pMob[idx].Affect[i].Time--;

						   if (pMob[idx].Affect[i].Time <= 0)
						   {
							   if (pMob[idx].Affect[i].Type == 16)
								   FaceChange = 1;

							   if (pMob[idx].Affect[i].Type == 33)
								   FaceChange = 1;

							   int summonEnd = 0;

							   if (pMob[idx].Affect[i].Type == 24 && idx >= MAX_USER)
								   DeleteMob(idx, 3);

							   pMob[idx].Affect[i].Type = 0;
							   pMob[idx].Affect[i].Time = 0;
							   pMob[idx].Affect[i].Value = 0;
							   pMob[idx].Affect[i].Level = 0;
							   upScore = 1;
						   }

#pragma endregion
			}

			if (regen)
			{
				if (idx > 0 && idx < MAX_USER)
				{
					SetReqHp(idx);
					SetReqMp(idx);
				}

				MSG_SetHpDam dam;

				dam.Type = _MSG_SetHpDam;
				dam.Size = sizeof(MSG_SetHpDam);
				dam.ID = idx;

				dam.Hp = pMob[idx].MOB.CurrentScore.Hp;
				dam.Dam = Damage;

				GridMulticast(pMob[idx].TargetX, pMob[idx].TargetY, (MSG_STANDARD*)&dam, 0);
			}

			if (upScore)
			{
				pMob[idx].GetCurrentScore(idx);
				SendScore(idx);

				if (FaceChange)
					SendEquip(idx, 0);

				return TRUE;
			}
			else
				return 0;

			return 0;
}

void SendUpdateWoteBattle()
{
	/*MSG_BATTLEWOTE sm;
	memset(&sm, 0, sizeof(MSG_BATTLEWOTE));

	sm.Type = _MSG_BATTLEWOTE;
	sm.Size = sizeof(MSG_BATTLEWOTE);
	sm.ID = -1;
	sm.Call = Task;

	for (int  i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY) continue;

		pUser[i].cSock.SendOneMessage((char*)&sm, sizeof(sm));
	}*/
}

void SendSpkMsg(int conn, char* Msg, TNColor Color32, bool ToAll = false)
{
	if (conn <= 0 || conn >= MAX_USER) return;

	MSG_ChatColor sm_mt;
	memset(&sm_mt, 0, sizeof(MSG_STANDARDPARM));

	sm_mt.Size = sizeof(MSG_ChatColor);
	sm_mt.ID = 0;
	sm_mt.Type = _MSG_MagicTrumpet;
	strcpy(sm_mt.Message, Msg);
	sm_mt.Color = Color32;

	if (ToAll)
	{
		for (int i = 0; i < MAX_USER; i++)
		{
			if (pUser[i].Mode != USER_PLAY) continue;

			pUser[i].cSock.SendOneMessage((char*)&sm_mt, sizeof(sm_mt));
		}
	}
	else
	{
		pUser[conn].cSock.SendOneMessage((char*)&sm_mt, sizeof(sm_mt));
	}


}

void SendMsgExp(int conn, char* Msg, TNColor Color32, bool ToAll = false)
{
	if (conn <= 0 || conn >= MAX_USER) return;

	MSG_Exp_Msg_Panel_ sm;
	memset(&sm, 0, sizeof(MSG_Exp_Msg_Panel_));

	sm.Type = _MSG_Exp_Msg_Panel_;
	sm.Size = sizeof(MSG_Exp_Msg_Panel_);
	sm.ID = conn;

	strcpy(sm.Msg, Msg);

	sm.Color32 = Color32;

	if (ToAll)
	{
		for (int i = 0; i < MAX_USER; i++)
		{
			if (pUser[i].Mode != USER_PLAY) continue;

			pUser[i].cSock.SendOneMessage((char*)&sm, sizeof(sm));
		}
	}
	else
	{
		pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(sm));
	}
}

void SendDamage(int x1, int y1, int x2, int y2)
{
	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;

		if (pMob[i].MOB.CurrentScore.Hp <= 0)
			continue;

		if (pMob[i].TargetX < x1 || pMob[i].TargetX > x2 || pMob[i].TargetY < y1 || pMob[i].TargetY > y2)
			continue;

		int UNK = 1048576000;

		int dam_base = 2000;

		int hp = pMob[i].MOB.CurrentScore.Hp;

		if(hp < dam_base)
			dam_base = hp - 1;

		int dam = hp - dam_base;


		if (hp < dam_base)
			dam = hp;

		if (hp < 1)
			dam = 1;

		int req_hp = dam - pMob[i].MOB.CurrentScore.Hp;

		pMob[i].MOB.CurrentScore.Hp = dam;

		//pUser[i].ReqHp = dam;

		SetReqHp(i);
		SetReqMp(i);

		MSG_SetHpDam sm;
		memset(&sm, 0, sizeof(MSG_SetHpDam));

		sm.Type = _MSG_SetHpDam;
		sm.Size = sizeof(MSG_SetHpDam);
		sm.ID = i;

		sm.Hp = dam;
		sm.Dam = req_hp;

		GridMulticast(pMob[i].TargetX, pMob[i].TargetY, (MSG_STANDARD*)&sm, 0);
	}
}

void SendDamageKingdom(int x1, int y1, int x2, int y2, int Clan)
{
	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;

		if (pMob[i].MOB.CurrentScore.Hp <= 0)
			continue;

		if (pMob[i].TargetX < x1 || pMob[i].TargetX > x2 || pMob[i].TargetY < y1 || pMob[i].TargetY > y2)
			continue;

		if(pMob[i].MOB.Clan == Clan)
			continue;

		int UNK = 1048576000;

		int dam_base = pMob[i].MOB.CurrentScore.MaxHp / 10;

		int hp = pMob[i].MOB.CurrentScore.Hp;

		if(hp < dam_base)
			dam_base = hp - 1;

		int dam = hp - dam_base;


		if (hp < dam_base)
			dam = hp;

		if (hp < 1)
			dam = 1;

		int req_hp = dam - pMob[i].MOB.CurrentScore.Hp;

		pMob[i].MOB.CurrentScore.Hp = dam;

		//pUser[i].ReqHp = dam;

		SetReqHp(i);
		SetReqMp(i);

		MSG_SetHpDam sm;
		memset(&sm, 0, sizeof(MSG_SetHpDam));

		sm.Type = _MSG_SetHpDam;
		sm.Size = sizeof(MSG_SetHpDam);
		sm.ID = i;

		sm.Hp = dam;
		sm.Dam = req_hp;

		GridMulticast(pMob[i].TargetX, pMob[i].TargetY, (MSG_STANDARD*)&sm, 0);
	}
}

void SendDamageLeader(int x1, int y1, int x2, int y2)
{
	int HaveUser = 0;
	
	for(int x = x1; x < x2; x++)
	{
		for(int y = y1; y < y2; y++)
		{
			if(x < 0 || x >= MAX_GRIDX || y < 0 || y >= MAX_GRIDY)
				continue;

			if(pMobGrid[y][x] == 0)
				continue;

			if(pMobGrid[y][x] >= MAX_USER)
				continue;

			int tmob = pMobGrid[y][x];

			if(tmob == Pista[4].Party[0].LeaderID)
			{
				HaveUser++;
				continue;
			}

			if(tmob == Pista[4].Party[1].LeaderID)
			{
				HaveUser++;
				continue;
			}
			if(tmob == Pista[4].Party[1].LeaderID)
			{
				HaveUser++;
				continue;
			}
		}
	}

	if(HaveUser)
		return;
	
	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;

		if (pMob[i].MOB.CurrentScore.Hp <= 0)
			continue;

		if (pMob[i].TargetX < x1 || pMob[i].TargetX > x2 || pMob[i].TargetY < y1 || pMob[i].TargetY > y2)
			continue;

		int UNK = 1048576000;

		int dam_base = 2000;

		int hp = pMob[i].MOB.CurrentScore.Hp;

		if(hp < dam_base)
			dam_base = hp - 1;

		int dam = hp - dam_base;


		if (hp < dam_base)
			dam = hp;

		if (hp < 1)
			dam = 1;

		int req_hp = dam - pMob[i].MOB.CurrentScore.Hp;

		pMob[i].MOB.CurrentScore.Hp = dam;

		//pUser[i].HP = dam;

		SetReqHp(i);
		SetReqMp(i);

		MSG_SetHpDam sm;
		memset(&sm, 0, sizeof(MSG_SetHpDam));

		sm.Type = _MSG_SetHpDam;
		sm.Size = sizeof(MSG_SetHpDam);
		sm.ID = i;

		sm.Hp = dam;
		sm.Dam = req_hp;

		GridMulticast(pMob[i].TargetX, pMob[i].TargetY, (MSG_STANDARD*)&sm, 0);
	}
}

void SummonGuild2(int Guild, int tx, int ty, int maxsummon, int village)
{
	if (Guild <= 0)
		return;

	int summons = 0;

	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY || pMob[i].Mode == USER_EMPTY)
			continue;

		if (pMob[i].MOB.Guild != Guild)
			continue;

		if (village < 1 || village > 3 || BASE_GetVillage(pMob[i].TargetX, pMob[i].TargetY) == village)
		{
			DoTeleport(i, tx, ty);

			summons++;

			if (summons == 30)
			{
				tx++;
				ty++;
			}

			if (summons == 45)
			{
				tx = tx - 2;
				ty = ty - 2;
			}

			if (summons >= maxsummon)
				break;
		}
	}
}

void SummonGuild(int Guild, int tx, int ty, int maxsummon, int village)
{
	if (Guild <= 0) return;

	int summons = 0;

	if (village >= 4) return;

	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;

		if (pMob[i].MOB.Guild != Guild)
			continue;

		int Master = pMob[i].Extra.ClassMaster;

		if (village == 2 && Master != MORTAL) continue;
		if (village == 3 && Master != ARCH) continue;

		if (BASE_GetVillage(pMob[i].TargetX, pMob[i].TargetY) == village)
		{
			summons++;

			DoTeleport(i, tx, ty);
		}
		else
		{
			SendClientMsg(i, g_pMessageStringTable[_NN_3rd_village_limit]);
		}

		if (summons >= maxsummon) break;

	}
}

void ClearAreaQuest(int conn, int x1, int y1, int x2, int y2)
{
	for (int i = 0; i < MAX_USER; i++)
	{

		if (pUser[conn].Mode != USER_PLAY)
			continue;

		if (pMob[conn].Mode == USER_EMPTY)
			continue;

		if (pMob[conn].TargetX < x1 || pMob[conn].TargetX > x2 || pMob[conn].TargetY < y1 || pMob[conn].TargetY > y2)
			continue;

		if (pMob[conn].MOB.CurrentScore.Hp <= 0)
		{
			pMob[conn].MOB.CurrentScore.Hp = 2;
			SendScore(conn);
		}

		pMob[conn].QuestFlag = 0;
		pMob[conn].Extra.CheckTimeKersef = 0;
		DoRecall(conn);
	}
}

void ClearArea(int x1, int y1, int x2, int y2)
{
	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;

		if (pMob[i].Mode == USER_EMPTY)
			continue;

		if (pMob[i].TargetX < x1 || pMob[i].TargetX > x2 || pMob[i].TargetY < y1 || pMob[i].TargetY > y2)
			continue;

		if (pMob[i].MOB.CurrentScore.Hp <= 0)
		{
			pMob[i].MOB.CurrentScore.Hp = 2;
			SendScore(i);
		}

		DoRecall(i);
	}
}

void ClearMap(int x, int y)
{
	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;

		if (pMob[i].Mode == USER_EMPTY)
			continue;

		
		if (pMob[i].MOB.CurrentScore.Hp <= 0)
		{
			pMob[i].MOB.CurrentScore.Hp = 2;
			SendScore(i);
		}

		if (pMob[i].LastX / 128 == x && pMob[i].LastY / 128 == y)
			DoRecall(i);
	}
}

void ClearAreaLevel(int x1, int y1, int x2, int y2, int minLv, int maxLv)
{
	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;

		if (pMob[i].Mode == USER_EMPTY)
			continue;

		if (pMob[i].TargetX < x1 || pMob[i].TargetX > x2 || pMob[i].TargetY < y1 || pMob[i].TargetY > y2)
			continue;

		if (pMob[i].MOB.CurrentScore.Level < minLv)
			continue;

		if (pMob[i].MOB.CurrentScore.Level > maxLv)
			continue;

		if (pMob[i].MOB.CurrentScore.Hp <= 0)
		{
			pMob[i].MOB.CurrentScore.Hp = 2;
			SendScore(i);
		}

		DoRecall(i);
	}
}

int BASE_GetOnScreen(int a_iMob, int a_iTarget)
{
	/* TRUE		= O alvo esta no campo de visao */
	/* FALSE	= O alvo esta fora do campo de visao */

	/* Credits By: NakiuS */

	if (a_iMob <= 0 || a_iTarget <= 0 || a_iMob >= MAX_MOB || a_iTarget >= MAX_MOB) return FALSE;

	int X = pMob[a_iMob].TargetX;
	int Y = pMob[a_iMob].TargetY;

	int Z = pMob[a_iTarget].TargetX;
	int F = pMob[a_iTarget].TargetY;

	int Q = 16;

	if (X < Z - Q || Y < F - Q || X > Z + Q || Y > F + Q) return FALSE;

	return TRUE;
}

void ClearAreaGuild(int x1, int y1, int x2, int y2, int Guild)
{
	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;

		if (pMob[i].Mode == USER_EMPTY)
			continue;

		if (pMob[i].TargetX < x1 || pMob[i].TargetX > x2 || pMob[i].TargetY < y1 || pMob[i].TargetY > y2)
			continue;

		if (pMob[i].MOB.Guild == Guild)
			continue;

		if (pMob[i].MOB.CurrentScore.Hp <= 0)
		{
			pMob[i].MOB.CurrentScore.Hp = 2;
			SendScore(i);
		}

		DoRecall(i);
	}
}

void ClearAreaTeleport(int x1, int y1, int x2, int y2, int tx, int ty)
{
	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;

		if (pMob[i].Mode == USER_EMPTY)
			continue;

		if (pMob[i].TargetX < x1 || pMob[i].TargetX > x2 || pMob[i].TargetY < y1 || pMob[i].TargetY > y2)
			continue;

		if (pMob[i].MOB.CurrentScore.Hp <= 0)
		{
			pMob[i].MOB.CurrentScore.Hp = 1;

			SendScore(i);
		}
		/*
		if(rand()%1 == 0)
			tx -= rand()%3;
		else
			tx += rand()%3;

		if(rand()%1 == 0)
			ty -= rand()%3;
		else
			ty += rand()%3;
*/
		DoTeleport(i, tx, ty);
	}
}
/*
void ClearGuildPKZone()
{
	int x1 = 128;
	int y1 = 128;

	int x2 = 256;
	int y2 = 256;

	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;

		if (pMob[i].Mode == 0)
			continue;

		if (pMob[i].TargetX >= x1 && pMob[i].TargetX <= x2 && pMob[i].TargetY >= y1 && pMob[i].TargetY <= y2)
			DoRecall(i);
	}
}*/

void SetColoseumDoor(int state)
{
	int gate = 0;

	int height = 0;

	for (int i = 1; i < 3; i++)
	{
		gate = i + 12;

		if (pItem[i + 12].ITEM.sIndex <= 0 || pItem[gate].ITEM.sIndex >= MAX_ITEMLIST)
			continue;

		//if (pItem[gate].State == state)
		//	continue;

		UpdateItem(gate, state, &height);

		/*if (state == STATE_OPEN)
		{
			MSG_UpdateItem sm;
			memset(&sm, 0, sizeof(MSG_UpdateItem));

			sm.ID = ESCENE_FIELD;
			sm.Type = _MSG_UpdateItem;

			sm.ItemID = gate + 10000;

			sm.Size = sizeof(MSG_UpdateItem);

			//		sm.Height = height;
			sm.State = pItem[gate].State;

			GridMulticast(pItem[gate].PosX, pItem[gate].PosY, (MSG_STANDARD*)&sm, 0);
		}
		else
		{*/
			MSG_CreateItem sm;
			memset(&sm, 0, sizeof(MSG_CreateItem));

			GetCreateItem(gate, &sm);

			GridMulticast(pItem[gate].PosX, pItem[gate].PosY, (MSG_STANDARD*)&sm, 0);
		//}
		pItem[gate].Delay = 0;
	}
}

void SetColoseumDoor2(int state)
{
	int gate = 0;

	int height = 0;

	for (int i = 0; i < 5; i++)
	{
		gate = i + 15;

		if (pItem[i + 15].ITEM.sIndex <= 0 || pItem[gate].ITEM.sIndex >= MAX_ITEMLIST)
			continue;

		//if (pItem[gate].State == state)
		//	continue;

		UpdateItem(gate, state, &height);

		/*if (state == STATE_OPEN)
		{
			MSG_UpdateItem sm;
			memset(&sm, 0, sizeof(MSG_UpdateItem));

			sm.ID = ESCENE_FIELD;
			sm.Type = _MSG_UpdateItem;

			sm.ItemID = gate + 10000;

			sm.Size = sizeof(MSG_UpdateItem);

			//		sm.Height = height;
			sm.State = pItem[gate].State;

			GridMulticast(pItem[gate].PosX, pItem[gate].PosY, (MSG_STANDARD*)&sm, 0);
		}
		else
		{*/
			MSG_CreateItem sm;
			memset(&sm, 0, sizeof(MSG_CreateItem));

			GetCreateItem(gate, &sm);

			GridMulticast(pItem[gate].PosX, pItem[gate].PosY, (MSG_STANDARD*)&sm, 0);
		//}
		pItem[gate].Delay = 0;
	}
}

void GenerateColoseum(int InitID)
{
	//srand(time(NULL));
	int MaxSpawn = 4 + rand() % 4;

	for (int i = 0; i < MaxSpawn; i++)
		GenerateMob(InitID, 0, 0);
}

void DeleteColoseum()
{
	for (int i = MAX_USER; i < MAX_MOB; i++)
	{
		if (!pMob[i].Mode)
			continue;

		if (pMob[i].MOB.CurrentScore.Hp <= 0)
			continue;

		if (!pMob[i].GenerateIndex || pMob[i].GenerateIndex == 1 || pMob[i].GenerateIndex == 2)
			DeleteMob(i, 2);

		if (pMob[i].GenerateIndex == 5 || pMob[i].GenerateIndex == 6 || pMob[i].GenerateIndex == 7)
			DeleteMob(i, 2);
	}
}
/*
void SetArenaDoor(int state)
{
	for (int i = 0; i < ValidGuild; i++)
	{
		if (i == 4)
			continue;

		for (int j = 0; j < 3; j++)
		{
			int gate = 3 * i + j + 1;
			int height = 0;

			if (pItem[gate].ITEM.sIndex <= 0 || pItem[gate].ITEM.sIndex >= MAX_ITEMLIST)
				continue;

			if (pItem[gate].State == state)
				continue;

			UpdateItem(gate, state, &height);

			if (state == STATE_OPEN)
			{
				MSG_UpdateItem sm;
				memset(&sm, 0, sizeof(MSG_UpdateItem));

				sm.ID = ESCENE_FIELD;
				sm.Type = _MSG_UpdateItem;

				sm.ItemID = gate + 10000;

				sm.Size = sizeof(MSG_UpdateItem);

				//sm.Height = height;
				sm.State = pItem[gate].State;

				GridMulticast(pItem[gate].PosX, pItem[gate].PosY, (MSG_STANDARD*)&sm, 0);
			}
			else
			{
				MSG_CreateItem sm;
				memset(&sm, 0, sizeof(MSG_CreateItem));

				GetCreateItem(gate, &sm);

				GridMulticast(pItem[gate].PosX, pItem[gate].PosY, (MSG_STANDARD*)&sm, 0);
			}
			pItem[gate].Delay = 0;
		}
	}
}
*/
/*
void SetCastleDoor(int state)
{
	for (int i = 0; i < 4; i++)
	{
		int DoorId = i + 36;

		if (pItem[DoorId].ITEM.sIndex <= 0 || pItem[DoorId].ITEM.sIndex >= MAX_ITEMLIST)
			continue;

		if (pItem[DoorId].State == state)
			continue;

		int height = 0;

		UpdateItem(DoorId, state, &height);

		if (state == STATE_OPEN)
		{
			MSG_UpdateItem sm;
			memset(&sm, 0, sizeof(MSG_UpdateItem));

			sm.ID = ESCENE_FIELD;
			sm.Type = _MSG_UpdateItem;
			sm.ItemID = DoorId + 10000;
			sm.Size = sizeof(MSG_UpdateItem);
			//		sm.Height = height;
			sm.State = pItem[DoorId].State;

			GridMulticast(pItem[DoorId].PosX, pItem[DoorId].PosY, (MSG_STANDARD*)&sm, 0);
		}
		else
		{
			int keyid = BASE_GetItemAbility(&pItem[DoorId].ITEM, EF_KEYID);

			if (keyid == 15)
				CreateMob("GATE", pItem[DoorId].PosX, pItem[DoorId].PosY, "npc", 0);

			MSG_CreateItem sm;
			memset(&sm, 0, sizeof(MSG_CreateItem));

			GetCreateItem(DoorId, &sm);

			GridMulticast(pItem[DoorId].PosX, pItem[DoorId].PosY, (MSG_STANDARD*)&sm, 0);
		}
		pItem[DoorId].Delay = 0;
	}
}*/

/*
void DecideWinner()
{
	for (int i = 0; i < ValidGuild; i++)
	{
		if (i == 3 || i == 4)
			continue;

		int ChargeSurvivor = 0;
		int ChallangeSurvivor = 0;

		int ChargeGuild = g_pGuildZone[i].ChargeGuild;
		int ChallangeGuild = g_pGuildZone[i].ChallangeGuild;

		if (ChallangeGuild == 0)
			continue;

		char GuildChargeName[256];
		char GuildChallangeName[256];

		BASE_GetGuildName(ServerGroup, g_pGuildZone[i].ChargeGuild, GuildChargeName);
		BASE_GetGuildName(ServerGroup, ChallangeGuild, GuildChallangeName);

		for (int j = g_pGuildZone[i].WarAreaY1; j <= g_pGuildZone[i].WarAreaY2; j++)
		{
			for (int k = g_pGuildZone[i].WarAreaX1; k <= g_pGuildZone[i].WarAreaX2; k++)
			{
				if(j < 0 || j >= MAX_GRIDY || k < 0 || k >= MAX_GRIDX)
					continue;

				int tmob = pMobGrid[j][k];

				if (tmob <= 0 || tmob >= MAX_USER)
					continue;

				if (pUser[tmob].Mode != USER_PLAY)
					continue;

				if (pMob[tmob].Mode == MOB_EMPTY)
					continue;

				if (pMob[tmob].MOB.CurrentScore.Hp <= 0)
					continue;

				int Guild = pMob[tmob].MOB.Guild;
				int Level = pMob[tmob].Extra.ClassMaster != MORTAL && pMob[tmob].Extra.ClassMaster != MORTAL ? pMob[tmob].MOB.CurrentScore.Level + MAX_LEVEL : pMob[tmob].MOB.CurrentScore.Level;

				if (Guild == 0)
					continue;

				if (Guild == ChargeGuild || Guild == ChallangeGuild)
				{
					sprintf(temp, "sys,guild war survive %s(%d-%d)", pMob[tmob].MOB.MobName, Guild, Level);
					Log(temp, "-system", 0);

					if (Guild == ChargeGuild)
						ChargeSurvivor += Level;

					else if (Guild == ChallangeGuild)
						ChallangeSurvivor += Level;

					else
						Log("err, more than 3 guild, at same guild zone", "-system", 0);
				}
			}
		}

		sprintf(temp, "sys,guild war %d result %d(%d) %d(%d)", i, ChargeGuild, ChargeSurvivor, ChallangeGuild, ChallangeSurvivor);
		Log(temp, "-system", 0);

		if (ChargeSurvivor < ChallangeSurvivor)
		{
			sprintf(temp, g_pMessageStringTable[_SSNN_GuildWarResult], GuildChallangeName, GuildChargeName, ChallangeSurvivor, ChargeSurvivor);
			SendGuildNotice(ChargeGuild, temp);
			SendGuildNotice(ChallangeGuild, temp);

			g_pGuildZone[i].ChargeGuild = ChallangeGuild;
			g_pGuildZone[i].Victory = 0;
		}
		else
		{
			sprintf(temp, g_pMessageStringTable[_SSNN_GuildWarResult], GuildChargeName, GuildChallangeName, ChargeSurvivor, ChallangeSurvivor);
			SendGuildNotice(ChargeGuild, temp);
			SendGuildNotice(ChallangeGuild, temp);

			if(g_pGuildZone[i].Victory < 4)
				g_pGuildZone[i].Victory++;
		}

		g_pGuildZone[i].ChallangeGuild = 0;
	}

	if(g_pGuildZone[1].ChargeGuild == g_pGuildZone[0].ChargeGuild && g_pGuildZone[2].ChargeGuild == g_pGuildZone[0].ChargeGuild && g_pGuildZone[3].ChargeGuild == g_pGuildZone[0].ChargeGuild)
		g_pGuildZone[4].ChargeGuild = g_pGuildZone[0].ChargeGuild;
}
*/
void GuildProcess()
{
	time_t rawtime;
	tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	if (timeinfo->tm_hour == 3 && GuildNameInitialized == 0)
	{
		BASE_InitializeGuildName();

		Log("sys,GuildName initialized", "-system", 0);

		GuildNameInitialized = 1;
	}

	if (timeinfo->tm_hour > 3 && GuildNameInitialized == 1)
		GuildNameInitialized = 0;

	//WarNotum Movido para um arquivo separado
	/*
#pragma region Guerra de Noatum
	if (CastleServer == 1 && (timeinfo->tm_hour == 21))
	{
		if (CastleState || timeinfo->tm_min >= 5)
		{
			if (CastleState != 1 || timeinfo->tm_min <= 5 || timeinfo->tm_min >= 10)
			{
				if (CastleState != 2 || timeinfo->tm_min <= 50)
				{
					if (CastleState == 3 && timeinfo->tm_min > 55)
					{
						sprintf(temp, g_pMessageStringTable[_DN_Castle_closed], timeinfo->tm_hour - 17);
						SendNotice(temp);
						FinishCastleWar();
					}
				}
				else
				{
					sprintf(temp, g_pMessageStringTable[_DN_Castle_will_be_closed], timeinfo->tm_hour - 17);
					SendNotice(temp);
					CastleState = 3;
				}
			}
			else
			{
				ClearAreaGuild(1036, 1672, 1144, 1764, g_pGuildZone[4].ChargeGuild);

				ClearAreaTeleport(1129, 1705, 1129, 1709, 1057, 1742);
				ClearAreaTeleport(1116, 1705, 1116, 1709, 1057, 1742);
				ClearAreaTeleport(1094, 1688, 1094, 1692, 1057, 1742);
				ClearAreaTeleport(1087, 1609, 1087, 1713, 1057, 1742);
				ClearAreaTeleport(1050, 1690, 1050, 1690, 1057, 1742);
				ClearAreaTeleport(1046, 1690, 1047, 1691, 1057, 1742);
				ClearAreaTeleport(1124, 1708, 1124, 1708, 1057, 1742);

				SetCastleDoor(3);

				for (int i = 0; i < 3; ++i)
				{
					GenerateMob(i + TORRE_NOATUM1, 0, 0);
					LiveTower[i] = 1;
				}

				sprintf(temp, g_pMessageStringTable[_DN_Castle_opened], timeinfo->tm_hour - 17);
				SendNotice(temp);
				CastleState = 2;
			}
		}
		else
		{
			sprintf(temp, g_pMessageStringTable[_DN_Castle_will_be_open], timeinfo->tm_hour - 17);
			SendNotice(temp);
			CastleState = 1;

			for (int j = 0; j < MAX_USER; j++)
			{
				if (pUser[j].Mode == USER_PLAY)
					SendClientSignalParm(j, ESCENE_FIELD, 940, CastleState);
			}
		}
	}
#pragma endregion
*/

	int NewbieServerID = (timeinfo->tm_mday - 1) % NumServerInGroup;

	if ((TESTSERVER || LOCALSERVER || ServerIndex == NewbieServerID) && BRItem > 0)
	{
		int tmmin2 = timeinfo->tm_min / 20;
		int tmmin = timeinfo->tm_min % 20;
		BrMod = timeinfo->tm_min % 20;
		BrGrid = timeinfo->tm_min / 20;

		if (timeinfo->tm_hour != BRHour || BrState || tmmin)
		{
			if (timeinfo->tm_hour != BRHour || BrState != 1 || tmmin != 5)
			{
				if (timeinfo->tm_hour == BRHour && BrState == 2 && tmmin == 13)
				{
					if (BRItem > 0 && BRItem < MAX_ITEMLIST)
					{
						STRUCT_ITEM item;

						BASE_ClearItem(&item);
						item.sIndex = BRItem;

						//srand(time(NULL));
						int create = CreateItem(2621, 1726, &item, rand() % 4, 1);
						sprintf(temp, "etc,britem created %d/%d", BRItem, create);
						Log(temp, "-system", 0);
					}
					BrState = 3;
					SendNoticeArea(g_pMessageStringTable[_NN_BR_Rewarded], 2580, 1688, 2665, 1765);
				}
			}
			else
			{
				SetColoseumDoor(3);
				BrState = 2;

				if (tmmin2)
				{
					if (tmmin2 == 1)
					{
						SendNoticeArea(g_pMessageStringTable[_NN_BR_Start2], 2580, 1688, 2665, 1765);
						ClearAreaLevel(2604, 1708, 2648, 1744, 200, 400);
					}
					else
						SendNoticeArea(g_pMessageStringTable[_NN_BR_Start3], 2580, 1688, 2665, 1765);
				}
				else
				{
					SendNoticeArea(g_pMessageStringTable[_NN_BR_Start1], 2580, 1688, 2665, 1765);
					ClearAreaLevel(2604, 1708, 2648, 1744, 100, 400);
				}
				SetColoseumDoor(3);

				for (int k = 0; k < MAX_USER; k++)
				{
					if (pUser[k].Mode == USER_PLAY && pMob[k].TargetX >= 2604 && pMob[k].TargetX <= 2648 && pMob[k].TargetY >= 1708 && pMob[k].TargetY <= 1744)
					{
						SendGridMob(k);

						if (pMob[k].Leader)
							RemoveParty(k);
					}
				}
			}
		}
		else
		{
			BrState = 1;
			if (tmmin2)
			{
				if (tmmin2 == 1)
				{
					SendNoticeArea(g_pMessageStringTable[_NN_BR_Ready2], 2580, 1708, 2665, 1765);
					ClearAreaLevel(2604, 1708, 2648, 1744, 200, 400);
				}
				else
					SendNoticeArea(g_pMessageStringTable[_NN_BR_Ready3], 2580, 1708, 2665, 1765);

			}
			else
			{
				SendNoticeArea(g_pMessageStringTable[_NN_BR_Ready1], 2580, 1708, 2665, 1765);
				ClearAreaLevel(2604, 1708, 2648, 1744, 100, 400);
			}
			for (int k = 0; k < MAX_USER; k++)
			{
				if (pUser[k].Mode == USER_PLAY && pMob[k].TargetX >= 2604 && pMob[k].TargetX <= 2648 && pMob[k].TargetY >= 1708 && pMob[k].TargetY <= 1744)
				{
					SendGridMob(k);

					if (pMob[k].Leader)
						RemoveParty(k);
				}
			}
		}

		if (timeinfo->tm_hour == BRHour && BrState == 3 && tmmin >= 14)
		{
			SetColoseumDoor(1);
			BrState = 0;
		}
	}

	//#ifdef Coliseu //indefinido
#pragma region Coliseu
	if (nColiseu[0].Days[timeinfo->tm_wday])
	{


		if (timeinfo->tm_hour == nColiseu[0].Hour[0] || timeinfo->tm_hour == nColiseu[0].Hour[1])
		{
			if (ColoState == 0 && timeinfo->tm_min <= 5)
			{
				sprintf(temp, "Os portões do Coliseu será fechado em %d minutos.", timeinfo->tm_min);
				SendNotice(temp);
				ColoState = 1;
			}

			if (ColoState == 1 && timeinfo->tm_min > 5)
			{
				SetColoseumDoor(3);
				ColoState = 2;
				Colo150Limit = 1;
				ClearAreaLevel(2604, 1708, 2648, 1744, 150, 400);
			
			}

			if (ColoState == 2 && timeinfo->tm_min >= 6)
			{
				if (timeinfo->tm_hour == nColiseu[0].Hour[0])
					GenerateColoseum(0);
				else if (timeinfo->tm_hour == nColiseu[0].Hour[1])
					GenerateColoseum(5);

				ColoState = 3;
			}

			if (ColoState == 3 && timeinfo->tm_min >= 7)
			{
				SetColoseumDoor2(1);
				ColoState = 4;
			}

			if (ColoState == 4 && timeinfo->tm_min >= 8)
			{
				if (timeinfo->tm_hour == nColiseu[0].Hour[0])
					GenerateColoseum(1);

				else if (timeinfo->tm_hour == nColiseu[0].Hour[1])
					GenerateColoseum(6);

				ColoState = 5;
			}

			if (ColoState == 5 && timeinfo->tm_min >= 9)
			{
				if (timeinfo->tm_hour == nColiseu[0].Hour[0])
				{
					GenerateColoseum(0);
					GenerateColoseum(1);
				}
				else if (timeinfo->tm_hour == nColiseu[0].Hour[1])
				{
					GenerateColoseum(5);
					GenerateColoseum(6);
				}
				ColoState = 6;
			}

			if (ColoState == 6 && timeinfo->tm_min >= 11)
			{
				if (timeinfo->tm_hour == nColiseu[0].Hour[0])
				{
					GenerateColoseum(1);
					GenerateColoseum(2);
				}
				else if (timeinfo->tm_hour == nColiseu[0].Hour[1])
				{
					GenerateColoseum(6);
					GenerateColoseum(7);
				}
				ColoState = 7;
			}

			if (ColoState == 7 && timeinfo->tm_min >= 13)
			{
				if (timeinfo->tm_hour == nColiseu[0].Hour[0])
				{
					GenerateColoseum(1);
					GenerateColoseum(2);
				}
				else if (timeinfo->tm_hour == nColiseu[0].Hour[1])
				{
					GenerateColoseum(6);
					GenerateColoseum(7);
				}
				ColoState = 8;
			}

			if (ColoState == 8 && timeinfo->tm_min >= 15)
			{
				SetColoseumDoor(1);
				SetColoseumDoor2(2);
				DeleteColoseum();
				ColoState = 9;
				Colo150Limit = 0;
				ClearArea(2604, 1708, 2648, 1744);
			}

		}
	}

#pragma endregion
//#endif
	if (timeinfo->tm_hour == NewbieHour && timeinfo->tm_min == 54)
		PotionReady = 0;

	if (timeinfo->tm_hour == NewbieHour && timeinfo->tm_min == 55 && PotionReady == 0)
	{
		GenerateMob(22, 0, 0);
		PotionReady = 1;
	}
//Movido para WarOfCity
/*
#pragma region Guerra de Cidades
	int day = GuildDay - 1;

	if (day < 0)
		day += 7;
	
	int fweek = timeinfo->tm_wday;

	if (ForceWeekMode != -1)
		fweek = -1;

	if (WeekMode || ((fweek != GuildDay) || timeinfo->tm_hour < GuildHour) && ForceWeekMode != 1)
	{
		if (WeekMode != 1 || (fweek != GuildDay || (timeinfo->tm_hour < GuildHour) || timeinfo->tm_min <= 2) && ForceWeekMode != 2)
		{
			if (WeekMode != 2 || ((fweek != GuildDay) || timeinfo->tm_hour < GuildHour || timeinfo->tm_min <= 5) && ForceWeekMode != 3)
			{
				if (WeekMode != 3
					|| (fweek != GuildDay || (timeinfo->tm_hour < GuildHour) || timeinfo->tm_min <= 20) && ForceWeekMode != 4)
				{
					if (WeekMode != 4 || fweek != day && ForceWeekMode != 5)
					{
						if (WeekMode == 5 && (fweek == GuildDay || !ForceWeekMode))
						{
							SendNotice(g_pMessageStringTable[_NN_Guild_Battle_Notice6]);
							WeekMode = 0;

							for(int i = 0; i < MAX_GUILDZONE; i++)
							{
								if(i == 4)
									continue;

								if(g_pGuildZone[i].ChallangeGuild == 0 && g_pGuildZone[i].Victory < 4)
									g_pGuildZone[i].Victory++; 
							}

						}
					}
					else
					{
						SendNotice(g_pMessageStringTable[_NN_Guild_Battle_Notice5]);
						WeekMode = 5;
					}
				}
				else
				{
					SendNotice(g_pMessageStringTable[_NN_Guild_Battle_Notice4]);
					DecideWinner();
					ClearGuildPKZone();
					ClearChallanger();
					CReadFiles::WriteChallanger();
					SetArenaDoor(STATE_LOCKED);
					WeekMode = 4;

					GuildZoneReport();
				}
			}
			else
			{
				SendNotice(g_pMessageStringTable[_NN_Guild_Battle_Notice3]);
				WeekMode = 3;
				SetArenaDoor(STATE_OPEN);
			}
		}
		else
		{
			SendNotice(g_pMessageStringTable[_NN_Guild_Battle_Notice2]);
			ClearGuildPKZone();
			WeekMode = 2;
			SetArenaDoor(STATE_LOCKED);

			for (int n = 0; n < ValidGuild; n++)
			{
				if (n != 4)
				{
					if (g_pGuildZone[n].ChallangeGuild)
					{
						if (g_pGuildZone[n].ChargeGuild)
							SummonGuild(g_pGuildZone[n].ChargeGuild, g_pGuildZone[n].ChargeWarSpawnX, g_pGuildZone[n].ChargeWarSpawnY, NumGuildBattle, n);
					}
				}
			}

			for (int n = 0; n < ValidGuild; n++)
			{
				if (n != 4)
				{
					if (g_pGuildZone[n].ChallangeGuild)
						SummonGuild(g_pGuildZone[n].ChallangeGuild,	g_pGuildZone[n].ChallangeWarSpawnX, g_pGuildZone[n].ChallangeWarSpawnY, NumGuildBattle, n);
				}
			}
		}
	}
	else
	{
		SendNotice(g_pMessageStringTable[_NN_Guild_Battle_Notice1]);
		WeekMode = 1;
	}
#pragma endregion

	*/
	WarOfTower::StandByProcess();
  }

void StartLog()
{
	struct tm when;
	time_t now;
	time(&now);
	when = *localtime(&now);

	if (FLogSystem != NULL)
		fclose(FLogSystem);

	sprintf(temp, ".\\Log\\System\\System_%02d_%02d_%04d_%02d_%02d_%02d.txt", when.tm_mday, when.tm_mon + 1, when.tm_year + 1900, when.tm_hour, when.tm_min, when.tm_sec);

	FLogSystem = fopen(temp, "wt");

	LastLogSystem = when.tm_mday;


	if (FLogDebugs != NULL)
		fclose(FLogDebugs);

	sprintf(temp, ".\\Log\\Debugs\\Debugs_%02d_%02d_%04d_%02d_%02d_%02d.txt", when.tm_mday, when.tm_mon + 1, when.tm_year + 1900, when.tm_hour, when.tm_min, when.tm_sec);

	FLogDebugs = fopen(temp, "wt");

	LastLogDebugs = when.tm_mday;


	if (FLogQuests != NULL)
		fclose(FLogQuests);

	sprintf(temp, ".\\Log\\Quests\\Quests_%02d_%02d_%04d_%02d_%02d_%02d.txt", when.tm_mday, when.tm_mon + 1, when.tm_year + 1900, when.tm_hour, when.tm_min, when.tm_sec);

	FLogQuests = fopen(temp, "wt");

	LastLogQuests = when.tm_mday;


	if (FLogEvents != NULL)
		fclose(FLogEvents);

	sprintf(temp, ".\\Log\\Events\\Events_%02d_%02d_%04d_%02d_%02d_%02d.txt", when.tm_mday, when.tm_mon + 1, when.tm_year + 1900, when.tm_hour, when.tm_min, when.tm_sec);

	FLogEvents = fopen(temp, "wt");

	LastLogEvents = when.tm_mday;


	if (FLogCombine != NULL)
		fclose(FLogCombine);

	sprintf(temp, ".\\Log\\Combine\\Combine_%02d_%02d_%04d_%02d_%02d_%02d.txt", when.tm_mday, when.tm_mon + 1, when.tm_year + 1900, when.tm_hour, when.tm_min, when.tm_sec);

	FLogCombine = fopen(temp, "wt");

	LastLogCombine = when.tm_mday;

	if (FLogItens != NULL)
		fclose(FLogItens);

	sprintf(temp, ".\\Log\\Itens\\Itens_%02d_%02d_%04d_%02d_%02d_%02d.txt", when.tm_mday, when.tm_mon + 1, when.tm_year + 1900, when.tm_hour, when.tm_min, when.tm_sec);

	FLogItens = fopen(temp, "wt");

	LastLogItens = when.tm_mday;

	if (FLogCommand != NULL)
		fclose(FLogCommand);

	sprintf(temp, ".\\Log\\Command\\Command_%02d_%02d_%04d_%02d_%02d_%02d.txt", when.tm_mday, when.tm_mon + 1, when.tm_year + 1900, when.tm_hour, when.tm_min, when.tm_sec);

	FLogCommand = fopen(temp, "wt");

	LastLogCommand = when.tm_mday;

	if (FLogAttack != NULL)
		fclose(FLogAttack);

	sprintf(temp, ".\\Log\\Attack\\Attack_%02d_%02d_%04d_%02d_%02d_%02d.txt", when.tm_mday, when.tm_mon + 1, when.tm_year + 1900, when.tm_hour, when.tm_min, when.tm_sec);

	FLogAttack = fopen(temp, "wt");

	LastLogAttack = when.tm_mday;

	if (FBanned != NULL)
		fclose(FBanned);

	sprintf(temp, ".\\Log\\Banned\\Banned_%02d_%02d_%04d_%02d_%02d_%02d.txt", when.tm_mday, when.tm_mon + 1, when.tm_year + 1900, when.tm_hour, when.tm_min, when.tm_sec);

	FBanned = fopen(temp, "wt");

	LastLogBanned = when.tm_mday;

	if (fLogFile != NULL)
		fclose(fLogFile);

	sprintf(temp, ".\\Log\\TM_%02d_%02d_%04d_%02d_%02d_%02d.txt", when.tm_mday, when.tm_mon + 1, when.tm_year + 1900, when.tm_hour, when.tm_min, when.tm_sec);

	fLogFile = fopen(temp, "wt");

	LastLogDay = when.tm_mday;

}

void CrackLog(int conn, char *str)
{
	char AccountName[16];

	if (conn <= 0 || conn >= MAX_USER)
	{
		if (conn < 0 || conn >= MAX_MOB)
			sprintf(temp, "index:%d", conn);

		else
			sprintf(temp, "mob:%d name:%s", conn, pMob[conn].MOB.MobName);
	}

	else
	{
		memcpy(AccountName, pUser[conn].AccountName, sizeof(pUser[conn].AccountName));

		pUser[conn].AccountName[15] = 0;
		pUser[conn].AccountName[14] = 0;

		sprintf(temp, "conn:%d mode:%d name:%s", conn, pUser[conn].Mode, AccountName);
	}

	strcat(temp, str);

	Log(temp, "-system", 0);

	SetWindowTextA(hWndMain, temp);
}

void Log(char *str1, char *str2, unsigned int ip)
{
	struct tm when;
	time_t now;
	time(&now);
	when = *localtime(&now);

	char LogTemp[1024];

	unsigned char *cIP = (unsigned char*)&ip;

	//sprintf(LogTemp, "%2.2d%2.2d%2.2d,%2.2d%2.2d%2.2d,%8.8x", when.tm_year - 100, when.tm_mon + 1, when.tm_mday, when.tm_hour, when.tm_min, when.tm_sec, ip);
	//sprintf(LogTemp, "%s,%s,%s \n", LogTemp, str2, str1);

	if (ip != 0)
		sprintf(LogTemp, "[%02d/%02d/%04d][%02d:%02d:%02d] IP: %d.%d.%d.%d", when.tm_mday, when.tm_mon + 1, when.tm_year + 1900, when.tm_hour, when.tm_min, when.tm_sec, cIP[0], cIP[1], cIP[2], cIP[3]);
	else
		sprintf(LogTemp, "[%02d/%02d/%04d][%02d:%02d:%02d] ", when.tm_mday, when.tm_mon + 1, when.tm_year + 1900, when.tm_hour, when.tm_min, when.tm_sec);
	
	sprintf(LogTemp, "%s %s %s \n", LogTemp, str2, str1);

	if (fLogFile)
		fprintf(fLogFile, LogTemp);

	SetWindowText(hWndMain, LogTemp);

	
}

void MyLog(LogType logType, char* str1, char* str2, char* str3, unsigned int ip)
{
	struct tm when;
	time_t now;
	time(&now);
	when = *localtime(&now);

	char LogTemp[1024];
	unsigned char *cIP = (unsigned char*)&ip;


	if (ip != 0)
		sprintf(LogTemp, "[%02d/%02d/%04d][%02d:%02d:%02d] IP: %d.%d.%d.%d", when.tm_mday, when.tm_mon + 1, when.tm_year + 1900, when.tm_hour, when.tm_min, when.tm_sec, cIP[0], cIP[1], cIP[2], cIP[3]);
	else
		sprintf(LogTemp, "[%02d/%02d/%04d][%02d:%02d:%02d] ", when.tm_mday, when.tm_mon + 1, when.tm_year + 1900, when.tm_hour, when.tm_min, when.tm_sec);


	sprintf(LogTemp, "%s %s %s %s \n", LogTemp, str1, str2, str3);

	switch (logType)
	{
		case LogType::System:
		{
			if (FLogSystem) {
				fprintf(FLogSystem, LogTemp);
			}

			break;
		}

		case LogType::Quests:
		{
			if (FLogQuests) {
				fprintf(FLogQuests, LogTemp);
			}

			break;
		}

		case LogType::Debugs:
		{
			if (FLogDebugs) {
				fprintf(FLogDebugs, LogTemp);
			}

			break;
		}

		case LogType::Events:
		{
			if (FLogEvents) {
				fprintf(FLogEvents, LogTemp);
			}

			break;
		}

		case LogType::Combines:
		{
			if (FLogCombine) {
				fprintf(FLogCombine, LogTemp);
			}

			break;
		}

		case LogType::Itens:
		{
			if (FLogItens) {
				fprintf(FLogItens, LogTemp);
			 }

		   break;
		}

		case LogType::Command:
		{
			if (FLogCommand) {
				fprintf(FLogCommand, LogTemp);
			}

			break;
		}

		case LogType::Attack:
		{
			if (FLogAttack) {
				fprintf(FLogAttack, LogTemp);
			}

			break;
		}

		case LogType::Banned:
		{
			if (FBanned) {
				fprintf(FBanned, LogTemp);
			}

			break;
		}
	}


	SetWindowText(hWndMain, LogTemp);

}

int  GetUserFromSocket(int Sock)
{
	if (Sock == 0)
		return 0;

	for (int i = 1; i < MAX_USER; i++)
	{
		if (pUser[i].cSock.Sock == (unsigned)Sock)
			return i;
	}

	return 0;
}

int  GetEmptyUser(void)
{
	for (int i = 1; i < MAX_USER; i++)
	{
		if (pUser[i].Mode == USER_EMPTY)
			return i;
	}

	return 0;
}

int  GetEmptyItem()
{
	for (int i = 1; i < MAX_ITEM; i++)
	{
		if (pItem[i].Mode == 0)
			return i;
	}

	return 0;
}

int  GetEmptyNPCMob()
{
	int ReadCount = MAX_MOB - (MAX_USER * 3);

	if (g_EmptyMob >= ReadCount) { g_EmptyMob = MAX_USER; }

	int EmptyMob = g_EmptyMob;

	for (int i = 0; i < MAX_MOB; i++, EmptyMob++)
	{
		if (EmptyMob >= ReadCount)
		{
			EmptyMob = MAX_USER;

			continue;
		}

		if (pMob[EmptyMob].Mode == MOB_EMPTY)
		{
			g_EmptyMob = EmptyMob + TRUE;

			return EmptyMob;
		}
	}

	return 0;
}


int  GetUserByName(char *name)
{
	if (name[0] == '+')
	{
		char *tname = name + 1;

		_strupr(tname);

		for (int i = 1; i < MAX_USER; i++)
		{
			if (pMob[i].Mode == MOB_EMPTY)
				continue;

			if (pUser[i].Mode != USER_PLAY)
				continue;

			if (!strcmp(tname, pUser[i].AccountName))
				return i;
		}
		return 0;
	}

	for (int i = 1; i < MAX_USER; i++)
	{
		if (pMob[i].Mode == MOB_EMPTY)
			continue;

		if (pUser[i].Mode != USER_PLAY)
			continue;

		if (!strcmp(name, pMob[i].MOB.MobName))
			return i;
	}
	return 0;
}

int  IsImple(int user)
{
	return 0;
}

void CloseUser(int conn)
{
	int unk = 0;
	int unk2 = 0;

	if (pUser[conn].Mode == USER_PLAY && pMob[conn].TargetX >= 0 && pMob[conn].TargetX < 4096
		&& pMob[conn].TargetY >= 0 && pMob[conn].TargetY < 4096)
		pMobGrid[pMob[conn].TargetY][pMob[conn].TargetX] = 0;

	pUser[conn].Admin = 0;
	pMob[conn].Extra.CheckTimeKersef = 0;

	if (pUser[conn].IsBillConnect) 
		SendBilling(conn, pUser[conn].AccountName, 2, 0);

	pUser[conn].cSock.CloseSocket();

	int Mode = pUser[conn].Mode;

	if (Mode && Mode != USER_ACCEPT)
	{
		if (Mode != USER_PLAY && Mode != USER_SAVING4QUIT)
		{
			MSG_STANDARD sm;
			memset(&sm, 0, sizeof(MSG_STANDARD));

			sm.Type = _MSG_DBNoNeedSave;
			sm.ID = conn;

			DBServerSocket.SendOneMessage((char*)&sm, sizeof(MSG_STANDARD));

			pMob[conn].Mode = USER_EMPTY;

			pUser[conn].CloseUser();
		}

		else
		{
			MSG_STANDARD sm2;
			memset(&sm2, 0, sizeof(MSG_STANDARD));

			sm2.Type = 0x123;
			sm2.ID = conn;
			sm2.Size = sizeof(MSG_STANDARD);

			pUser[conn].cSock.SendOneMessage((char*)&sm2, sizeof(MSG_STANDARD));

			RemoveParty(conn);

			int tradeOpponentID = pUser[conn].Trade.OpponentID;

			if (tradeOpponentID > 0 && tradeOpponentID < MAX_USER && pUser[tradeOpponentID].Mode == USER_PLAY && pUser[tradeOpponentID].Trade.OpponentID == conn)
				RemoveTrade(tradeOpponentID);

			pUser[conn].Trade.OpponentID = 0;

			MSG_SavingQuit sm;
			memset(&sm, 0, sizeof(MSG_SavingQuit));

			sm.Type = _MSG_SavingQuit;

			if (conn < 0 || conn > MAX_MOB)
			{
				CrackLog(conn, " SaveAndQuitMobidx");
				return;
			}

			int Slot = pUser[conn].Slot;

			if (Slot < 0 || Slot >= MAX_CLASS)
			{
				CrackLog(conn, " SaveAndQuitWrongSlot");
				return;
			}

			memcpy(&sm.MOB, &pMob[conn], sizeof(STRUCT_MOB));
			memcpy(sm.Cargo, &pUser[conn].Cargo, sizeof(pUser[conn].Cargo));
			memcpy(sm.ShortSkill, &pUser[conn].CharShortSkill, 16);

			strcpy(sm.BlockPass, pUser[conn].BlockPass);
			sm.IsBlocked = pUser[conn].IsBlocked;

			memcpy(sm.affect, pMob[conn].Affect, sizeof(sm.affect));
			sm.Extra = pMob[conn].Extra;

			strncpy((char*)&sm.AccountName, pUser[conn].AccountName, ACCOUNTNAME_LENGTH);

			sm.Coin = pUser[conn].Coin;
			sm.Donate = pUser[conn].Donate;
			sm.VemProEternal = pUser[conn].VemProEternal;

			sm.Slot = pUser[conn].Slot;
			sm.IsNewbieRe = pUser[conn].IsNewBieRe;

			sm.QuestDiaria.IndexQuest = pUser[conn].QuestAtiva;
			sm.QuestDiaria.MobCount1 = pUser[conn].CountMob1;
			sm.QuestDiaria.MobCount2 = pUser[conn].CountMob2;
			sm.QuestDiaria.MobCount3 = pUser[conn].CountMob3;

			sm.ID = conn;

			WriteAccountBuff(conn);
			DBServerSocket.SendOneMessage((char*)&sm, sizeof(MSG_SavingQuit));

			pUser[conn].Mode = USER_SAVING4QUIT;

			DeleteMob(conn, 2);

			WriteStatistic();
		}

	}

	else
		pUser[conn].CloseUser();
}

CMob *GetMobFromIndex(unsigned int index)
{
	if (index < 0 || index >= MAX_MOB)
		return NULL;

	return &pMob[index];
}

int  GetAngle(int x, int y)
{
	if (x == 0 || y == 0)
		return 0;

	double tangle = atan2((FLOAT)y, (FLOAT)x);

	int angle = (int)((tangle * 3600) / 6.283184);

	if (angle < 0)
		angle += 3600;

	if (angle > 3600)
		angle -= 3600;

	return angle;
}

int  GetLength(int x, int y)
{
	FLOAT valx = (FLOAT)(x * x);
	FLOAT valy = (FLOAT)(y * y);

	FLOAT valxy = valx + valy;

	if (valxy > 100)
		return 100;

	if (valxy <= 0)
		return 0;

	double fout = sqrt(valxy);

	int out = (int)fout;

	return out;
}

int  ReadMob(STRUCT_MOB *mob, char *dir)
{
	sprintf(temp, "./%s/%s", dir, mob->MobName);

	int Handle = _open(temp, O_RDONLY | O_BINARY);

	if (Handle == -1)
	{
		if (errno == EINVAL)
			sprintf(temp, "err,ReadMob EEXIST %s", mob->MobName);

		else if (errno == EMFILE)
			sprintf(temp, "err,ReadMob EMFILE %s", mob->MobName);

		else if (errno == ENOENT)
			sprintf(temp, "err,ReadMob ENOENTN %s", mob->MobName);

		else
			sprintf(temp, "err,ReadMob UNKNOW %s", mob->MobName);

		Log(temp, "-system", 0);
		return FALSE;
	}

	strncpy(temp, mob->MobName, NAME_LENGTH);

	int ret = _read(Handle, mob, sizeof(STRUCT_MOB));

	if (ret == -1)
	{
		_close(Handle);

		return FALSE;
	}

	_close(Handle);

	strncpy(mob->MobName, temp, NAME_LENGTH);

	BASE_GetEnglish(mob->MobName);

	mob->BaseScore = mob->CurrentScore;

	return TRUE;
}

void DeleteMob(int conn, int Type)
{
	MSG_RemoveMob sm;
	memset(&sm, 0, sizeof(MSG_RemoveMob));

	sm.Type = _MSG_RemoveMob;
	sm.Size = sizeof(MSG_RemoveMob);
	sm.ID = conn;
	sm.RemoveType = Type;

	GridMulticast(pMob[conn].TargetX, pMob[conn].TargetY, (MSG_STANDARD*)&sm, conn < MAX_USER ? conn : 0);

	if (Type != 0)
	{
		int X = pMob[conn].TargetX;
		int Y = pMob[conn].TargetY;

		int geneidx = pMob[conn].GenerateIndex;

		if (conn != pMobGrid[Y][X])
		{
			bool Flag = false;

			for (int y = 0; y < MAX_GRIDY; y++)
			{
				for (int x = 0; x < MAX_GRIDX; x++)
				{
					if (pMobGrid[y][x] == conn)
					{
						Flag = true;

						GridMulticast(x, y, (MSG_STANDARD*)&sm, 0);

						pMobGrid[y][x] = 0;

						break;
					}
				}

				if (Flag) break;
			}
		}
		else
		{
			pMobGrid[Y][X] = 0;
		}



		pMob[conn].MOB.CurrentScore.Hp = 0;  //4

		pMob[conn].Mode = MOB_EMPTY;

		RemoveParty(conn);

		if (conn >= MAX_USER)
		{
			if (geneidx >= 0 && geneidx < MAX_NPCGENERATOR)
			{
				mNPCGen.pList[geneidx].CurrentNumMob--;

				if (mNPCGen.pList[geneidx].CurrentNumMob < 0) mNPCGen.pList[geneidx].CurrentNumMob = 0;
			}
		}
	}
	

}

void SaveUser(int conn, int Export)
{
	MSG_DBSaveMob sm;
	memset(&sm, 0, sizeof(MSG_DBSaveMob));

	sm.Type = _MSG_DBSaveMob;

	memcpy(&sm.MOB, &pMob[conn].MOB, sizeof(STRUCT_MOB));

	memcpy(&sm.Cargo, pUser[conn].Cargo, sizeof(STRUCT_ITEM) * MAX_CARGO);

	sm.Coin = pUser[conn].Coin;

	sm.ID = conn;
	sm.Export = Export;

	sm.Slot = pUser[conn].Slot;
	sm.Donate = pUser[conn].Donate;
	sm.VemProEternal = pUser[conn].VemProEternal;

	memcpy(&sm.PartyPassword, &pUser[conn].PartyPassword, sizeof(sm.PartyPassword));

	sm.QuestDiaria.IndexQuest = pUser[conn].QuestAtiva;
	sm.QuestDiaria.LastTimeQuest = pUser[conn].LastQuestDay;
	sm.QuestDiaria.MobCount1 = pUser[conn].CountMob1;
	sm.QuestDiaria.MobCount1 = pUser[conn].CountMob2;
	sm.QuestDiaria.MobCount1 = pUser[conn].CountMob3;

	strncpy(sm.AccountName, pUser[conn].AccountName, ACCOUNTNAME_LENGTH);

	memcpy(sm.ShortSkill, pUser[conn].CharShortSkill, 16);

	memcpy(sm.affect, pMob[conn].Affect, sizeof(sm.affect));
	sm.Extra = pMob[conn].Extra;

	DBServerSocket.SendOneMessage((char*)&sm, sizeof(MSG_DBSaveMob));
}

void CharLogOut(int conn)
{
	if(conn < 0 || conn >= MAX_USER)
	{
		Log("err,char logout - not conn valid", "-system", 0);
		return;
	}
	if (pUser[conn].Mode != USER_PLAY)
	{
		Log("err,char logout - not user_play", pUser[conn].AccountName, pUser[conn].IP);

		SendClientSignal(conn, conn, _MSG_CNFCharacterLogout);

		return;
	}

	MSG_STANDARD sm2;
	memset(&sm2, 0, sizeof(MSG_STANDARD));

	sm2.Type = 0x123;
	sm2.ID = conn;
	sm2.Size = sizeof(MSG_STANDARD);

	pUser[conn].cSock.SendOneMessage((char*)&sm2, sizeof(MSG_STANDARD));

	pMob[conn].Extra.CheckTimeKersef = 0;

	//CreateExportInspectTable(conn);

	if (pUser[conn].IsBillConnect && CHARSELBILL == 0)
		SendBilling(conn, pUser[conn].AccountName, 2, 0);

	int trade = pUser[conn].Trade.OpponentID;

	if (trade > 0 && trade < MAX_USER)
	{
		if (pUser[trade].Mode == USER_PLAY && pUser[trade].Trade.OpponentID == conn)
			RemoveTrade(trade);
	}

	pUser[conn].SelChar.Score[pUser[conn].Slot].Level = pMob[conn].MOB.BaseScore.Level;

	pMob[conn].MacroPerga = FALSE;
	//pMob[conn].MOB.macroOn = FALSE;
	//pMob[conn].MOB.MacroInside= FALSE;
	//pMob[conn].MOB.SalaClear = FALSE;

	SaveUser(conn, 1);
	DeleteMob(conn, 2);

	pMob[conn].TargetX = pMob[conn].MOB.SPX;
	pMob[conn].TargetY = pMob[conn].MOB.SPY;

	pUser[conn].Mode = USER_SELCHAR;

	pMob[conn].Mode = 0;

	WriteAccountBuff(conn);
	WriteStatistic();

	SendClientSignal(conn, conn, _MSG_CNFCharacterLogout);

}

void Reboot()
{
	for (int y = 0; y < MAX_GRIDY; y++)
	{
		for (int x = 0; x < MAX_GRIDX; x++)
		{
			pMobGrid[y][x] = 0;
			pItemGrid[y][x] = 0;
			pHeightGrid[y][x] = 0;
		}
	}

	for (int i = 0; i < 3; i++)
		LiveTower[i] = 0;

	BASE_InitializeMobname("MobName.txt", 0);

	mNPCGen.ReadNPCGenerator();

	int Handle = _open("./heightmap.dat", _O_RDONLY | _O_BINARY, NULL);

	if (Handle == -1)
	{
		Log("err Load height grid fail", "-system", 0);

		return;
	}

	_read(Handle, (void*)pHeightGrid, sizeof(pHeightGrid));
	_close(Handle);

	BASE_InitializeBaseDef();
	BASE_ApplyAttribute((char*)pHeightGrid, MAX_GRIDX);
	BASE_InitializeMessage("Language.txt");

	mSummon.Initialize();

	Log("sys,start server", "-system", 0);

	for (int i = 0; i < g_dwInitItem; i++)
	{
		STRUCT_ITEM Item;
		memset(&Item, 0, sizeof(STRUCT_ITEM));

		Item.sIndex = g_pInitItem[i].ItemIndex;

		int ID = CreateItem(g_pInitItem[i].PosX, g_pInitItem[i].PosY, &Item, g_pInitItem[i].Rotate, 1);

		if (ID >= MAX_ITEM || ID <= 0)
			continue;

		int ret = BASE_GetItemAbility(&Item, EF_KEYID);

		if (ret != 0 && ret < 15)
		{
			int Height;

			UpdateItem(ID, STATE_LOCKED, &Height);
		}
	}

	WeekMode = 4;

	struct tm when;
	time_t now;
	time(&now);
	when = *localtime(&now);

	int GDay = GuildDay - 1;

	if (GDay < 0)
		GDay += 7;

	if (when.tm_wday == GDay)
		WeekMode = 5;

	if (when.tm_wday == GuildDay && when.tm_hour < GuildHour)
		WeekMode = 0;

	SetColoseumDoor(1);
}

/*
void ClearChallanger()
{
	for (int i = 0; i < ValidGuild; i++)
	{
		g_pGuildZone[i].ChallangeGuild = 0;
		pChallangerMoney[i] = 0;
	}
}

*/
void SetBattle(int mob, int target)
{
	if (mob <= 0 || target <= 0 || mob >= MAX_MOB || target >= MAX_MOB)
		return;

	if (pMob[mob].Mode == MOB_EMPTY)
		return;

	if (pMob[target].Mode == MOB_EMPTY)
		return;

	if(mob == target)
		return;

	if (mob >= MAX_USER && (target >= MAX_USER ||pUser[target].Mode == USER_PLAY) )
	{
		if (pMob[mob].TargetX >= pMob[target].TargetX - 23 && pMob[mob].TargetX <= pMob[target].TargetX + 23 && pMob[mob].TargetY >= pMob[target].TargetY - 23 && pMob[mob].TargetY <= pMob[target].TargetY + 23)
		{
			pMob[mob].Mode = MOB_COMBAT;

			pMob[mob].AddEnemyList(target);

			

			int generateindex = pMob[mob].GenerateIndex;
			//srand(time(NULL));
			int say = rand() % 4;

			if (generateindex < 0 || generateindex >= MAX_NPCGENERATOR)
				return;

			if (mNPCGen.pList[generateindex].FightAction[say][0] && !pMob[mob].Leader)
				SendChat(mob, mNPCGen.pList[generateindex].FightAction[say]);
		}
	}
}

int  CreateItem(int x, int y, STRUCT_ITEM *item, int rotate, int Create)
{
	if (item->sIndex <= 0 || item->sIndex >= MAX_ITEMLIST)
		return FALSE;

	GetEmptyItemGrid(&x, &y);

//	if (pHeightGrid[y][x] >= -15 || pHeightGrid[y][x] >= 90)
//		return FALSE;

	if (pItemGrid[y][x])
		return FALSE;

	int empty = GetEmptyItem();

	if (empty == 0)
		return FALSE;

	pItem[empty].Mode = 1;

	pItem[empty].PosX = x;
	pItem[empty].PosY = y;

	memcpy(&pItem[empty].ITEM, item, sizeof(STRUCT_ITEM));

	pItem[empty].Rotate = rotate;
	pItem[empty].State = STATE_OPEN;

	pItem[empty].Delay = 90;
	pItem[empty].Decay = 0;

	pItem[empty].GridCharge = BASE_GetItemAbility(item, EF_GROUND);

	pItemGrid[y][x] = empty;

	pItem[empty].Height = pHeightGrid[y][x];

	MSG_CreateItem sm;
	memset(&sm, 0, sizeof(MSG_CreateItem));

	sm.Type = _MSG_CreateItem;
	sm.Size = sizeof(MSG_CreateItem);
	sm.ID = ESCENE_FIELD;

	sm.ItemID = empty + 10000;

	memcpy(&sm.Item, &pItem[empty].ITEM, sizeof(STRUCT_ITEM));

	sm.GridX = x;
	sm.GridY = y;

	sm.Rotate = rotate;
	sm.State = pItem[empty].State;
//	sm.Create = Create;

//	sm.Height = pItem[empty].Height;

	if (Create == 2)//Bau
		sm.Height = -204;

	GridMulticast(x, y, (MSG_STANDARD*)&sm, 0);

	return TRUE;
}

void RemoveTrade(int conn)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	memset(&pUser[conn].Trade, 0, sizeof(MSG_Trade));

	for (int i = 0; i < MAX_TRADE; i++)
		pUser[conn].Trade.InvenPos[i] = -1;

	memset(&pUser[conn].AutoTrade, 0, sizeof(MSG_SendAutoTrade));

	for (int i = 0; i < MAX_AUTOTRADE; i++)
		pUser[conn].AutoTrade.CarryPos[i] = -1;

	if (pUser[conn].Mode != USER_PLAY)
		return;

	SendClientSignal(conn, conn, 900);

	if (pUser[conn].TradeMode)
	{
		int posX = pMob[conn].TargetX;
		int posY = pMob[conn].TargetY;

		MSG_CreateMob sm;
		memset(&sm, 0, sizeof(MSG_CreateMob));

		GetCreateMob(conn, &sm);
		GridMulticast(posX, posY, (MSG_STANDARD*)&sm, 0);

		pUser[conn].TradeMode = 0;
	}
}

void RemoveParty(int conn)
{
	int leader = pMob[conn].Leader;

	if (leader < 0 || leader >= MAX_MOB)
	{
		Log("err,RemoveParty but worng leader", pUser[conn].AccountName, pUser[conn].IP);
		return;
	}

	if (leader && leader < MAX_USER && pUser[leader].Mode != USER_PLAY)
	{
		Log("err,removeparty - conn mode", pUser[conn].AccountName, pUser[conn].IP);
		Log("err,removeparty - leader mode", pUser[conn].AccountName, pUser[conn].IP);

		pMob[conn].Leader = 0;
	}
	else
	{
		if (conn > 0 && conn < MAX_USER)
			SendRemoveParty(conn, 0);

		if (leader)
		{
			SendRemoveParty(leader, conn);
			pMob[conn].Leader = 0;

			for (int i = 0; i < MAX_PARTY; i++)
			{
				int partyconn = pMob[leader].PartyList[i];

				if (partyconn)
				{
					if (partyconn == conn)
						pMob[leader].PartyList[i] = 0;

					if(pMob[partyconn].Summoner && pMob[partyconn].Summoner == conn)
						DeleteMob(partyconn, 3);

					if(!pMob[partyconn].Summoner && partyconn >= MAX_USER && leader < MAX_USER)
						DeleteMob(partyconn, 3);

					if (partyconn > 0 && partyconn <= MAX_USER && pUser[partyconn].Mode == USER_PLAY)
						SendRemoveParty(partyconn, conn);
				}
			}
		}

		else
		{
			int novolider = 0;

			for (int i = 0; i < MAX_PARTY; i++)
			{
				int partyconn = pMob[conn].PartyList[i];

				if(partyconn != 0 && partyconn < MAX_USER)
				{
					novolider = partyconn;

					for(int s = 0; s < 7; s++)
					{
						for(int t = 0; t < 3; t++)
						{
							if(Pista[s].Party[t].LeaderID == conn && strcmp(Pista[s].Party[t].LeaderName, pMob[conn].MOB.MobName) == 0)
							{
								strncpy(Pista[s].Party[t].LeaderName, pMob[novolider].MOB.MobName, NAME_LENGTH);
								Pista[s].Party[t].LeaderID = novolider;
							}
						}
					}

					break;
				}
			}

			for (int i = 0; i < MAX_PARTY; i++)
			{
				int partyconn = pMob[conn].PartyList[i];

				if (partyconn > 0 && partyconn <= MAX_MOB)
				{
					pMob[conn].PartyList[i] = 0;
					pMob[partyconn].Leader = 0;

					if (partyconn > 0 && partyconn < MAX_USER && pUser[partyconn].Mode == USER_PLAY)
						SendRemoveParty(partyconn, 0);

					if (partyconn > MAX_USER)
					{
						if (conn < MAX_USER && pMob[partyconn].Summoner && pMob[partyconn].Summoner == conn)
							DeleteMob(partyconn, 3);

						pMob[partyconn].Summoner = 0;
					}
					if(novolider != 0 && novolider != partyconn && partyconn < MAX_USER && novolider < MAX_USER)
					{
						MSG_AcceptParty sm;
						memset(&sm, 0, sizeof(MSG_AcceptParty));

						sm.Size = sizeof(MSG_AcceptParty);
						sm.Type = _MSG_AcceptParty;
						sm.ID = 0;

						sm.LeaderID = novolider;

						strncpy(sm.MobName, pMob[novolider].MOB.MobName, NAME_LENGTH);

						pMob[partyconn].LastReqParty = novolider;

						ProcessClientMessage(partyconn, (char*)&sm, TRUE);
					}
				}
			}
		}
	}
}

void TransferGroup(int conn, int trans)
{
	int leader = pMob[conn].Leader;

	if (leader < 0 || leader >= MAX_MOB)
	{
		Log("err,RemoveParty but worng leader", pUser[conn].AccountName, pUser[conn].IP);
		return;
	}

	if (leader && leader < MAX_USER && pUser[leader].Mode != USER_PLAY)
	{
		Log("err,removeparty - conn mode", pUser[conn].AccountName, pUser[conn].IP);
		Log("err,removeparty - leader mode", pUser[conn].AccountName, pUser[conn].IP);

		pMob[conn].Leader = 0;
	}
	else
	{
		if (conn > 0 && conn < MAX_USER)
			SendRemoveParty(conn, 0);

		if (leader)
		{
			SendRemoveParty(leader, conn);
			pMob[conn].Leader = 0;

			for (int i = 0; i < MAX_PARTY; i++)
			{
				int partyconn = pMob[leader].PartyList[i];

				if (partyconn)
				{
					if (partyconn == conn)
						pMob[leader].PartyList[i] = 0;

					if (pMob[partyconn].Summoner && pMob[partyconn].Summoner == conn)
						DeleteMob(partyconn, 3);

					if (!pMob[partyconn].Summoner && partyconn >= MAX_USER && leader < MAX_USER)
						DeleteMob(partyconn, 3);

					if (partyconn > 0 && partyconn <= MAX_USER && pUser[partyconn].Mode == USER_PLAY)
						SendRemoveParty(partyconn, conn);
				}
			}
		}

		else
		{
			int novolider = 0;

			if (trans)
			{
				novolider = trans;
				int first;
				int connFirst;
				int newLider;
				for (size_t nn = 0; nn < MAX_PARTY; nn++)
				{
					int partyconn = pMob[conn].PartyList[nn];

					if (partyconn > 0 && partyconn <= MAX_MOB)
					{

						if (nn == 0)
						{
							first = nn;
							connFirst = partyconn;
						}
					
						if (partyconn == novolider)
							newLider = nn;
					
					}
				}

				pMob[conn].PartyList[first] = novolider;
				pMob[conn].PartyList[newLider] = connFirst;
			}

			for (int i = 0; i < MAX_PARTY; i++)
			{
				int partyconn = pMob[conn].PartyList[i];

				if (partyconn != 0 && partyconn < MAX_USER)
				{
					//novolider = partyconn;

					for (int s = 0; s < 7; s++)
					{
						for (int t = 0; t < 3; t++)
						{
							if (Pista[s].Party[t].LeaderID == conn && strcmp(Pista[s].Party[t].LeaderName, pMob[conn].MOB.MobName) == 0)
							{
								strncpy(Pista[s].Party[t].LeaderName, pMob[novolider].MOB.MobName, NAME_LENGTH);
								Pista[s].Party[t].LeaderID = novolider;
							}
						}
					}

					break;
				}
			}

			for (int i = 0; i < MAX_PARTY; i++)
			{
				int partyconn = pMob[conn].PartyList[i];

				if (partyconn > 0 && partyconn <= MAX_MOB)
				{
					pMob[conn].PartyList[i] = 0;
					pMob[partyconn].Leader = 0;

					if (partyconn > 0 && partyconn < MAX_USER && pUser[partyconn].Mode == USER_PLAY)
						SendRemoveParty(partyconn, 0);

					if (partyconn > MAX_USER)
					{
						if (conn < MAX_USER && pMob[partyconn].Summoner && pMob[partyconn].Summoner == conn)
							DeleteMob(partyconn, 3);

						pMob[partyconn].Summoner = 0;
					}

					if (novolider != 0 && novolider != partyconn && partyconn < MAX_USER && novolider < MAX_USER)
					{
						MSG_AcceptParty sm;
						memset(&sm, 0, sizeof(MSG_AcceptParty));

						sm.Size = sizeof(MSG_AcceptParty);
						sm.Type = _MSG_AcceptParty;
						sm.ID = 0;

						sm.LeaderID = novolider;

						strncpy(sm.MobName, pMob[novolider].MOB.MobName, NAME_LENGTH);

						pMob[partyconn].LastReqParty = novolider;

						ProcessClientMessage(partyconn, (char*)&sm, TRUE);
					}
				}
			}

			if (trans)
			{
				MSG_AcceptParty sm;
				memset(&sm, 0, sizeof(MSG_AcceptParty));

				sm.Size = sizeof(MSG_AcceptParty);
				sm.Type = _MSG_AcceptParty;
				sm.ID = 0;

				sm.LeaderID = novolider;

				strncpy(sm.MobName, pMob[novolider].MOB.MobName, NAME_LENGTH);

				pMob[conn].LastReqParty = novolider;

				ProcessClientMessage(conn, (char*)&sm, TRUE);
			}
		}


	}
}

int UpdateItem(int Gate, int state, int *height)
{
	int rotate = pItem[Gate].Rotate;

	int update = BASE_UpdateItem(pItem[Gate].GridCharge, pItem[Gate].State, state, pItem[Gate].PosX, pItem[Gate].PosY, (char*)&pHeightGrid, rotate, height);

	if (update == 0)
		return FALSE;

	pItem[Gate].State = state;
	pItem[Gate].Height = *height;

	int GridCharge = pItem[Gate].GridCharge;
	int itemstate = pItem[Gate].State;

	pItem[Gate].Delay = 0;

	if (GridCharge >= 6 || GridCharge < 0)
	{
		Log("err,updateItem maskidx illegal", "-system", 0);
		return TRUE;
	}

	if (itemstate == state)
	{
		int keyid = BASE_GetItemAbility(&pItem[Gate].ITEM, EF_KEYID);

		if (keyid == 15 && itemstate == 1 && state == 3)
			CreateMob("GATE", pItem[Gate].PosX, pItem[Gate].PosY, "npc", 0);

		pItem[Gate].State = state;

		return TRUE;
	}

	int posX = pItem[Gate].PosX;
	int posY = pItem[Gate].PosY;

	for (int i = 0; i <= MAX_GROUNDMASK - 2; i++)
	{
		for (int j = 0; j <= MAX_GROUNDMASK - 2; j++)
		{
			int val = g_pGroundMask[GridCharge][rotate][i][j];

			int iX = posX + j - 2;
			int jY = posY + i - 2;

			if (iX >= 1 && jY >= 1 && iX <= 4094 && jY <= 4094 && val)
			{
				int tmob = pMobGrid[jY][iX];

				if (tmob != 0)
				{
					if (pMob[tmob].MOB.Equip[0].sIndex == 220)
						DeleteMob(tmob, 3);

					else
					{
						int mobgrid = GetEmptyMobGrid(tmob, &iX, &jY);

						if (mobgrid != 0)
						{
							pMob[tmob].Route[0] = 0;

							MSG_Action sm;
							memset(&sm, 0, sizeof(MSG_Action));

							GetAction(tmob, iX, jY, &sm);

							int unk = 20;
							int unk2 = 0;

							GridMulticast(iX, jY, (MSG_STANDARD*)&sm, 0);

							if (tmob < MAX_USER)
								pUser[tmob].cSock.SendOneMessage((char*)&sm, sizeof(sm));
						}
					}
				}
			}
		}
	}

	return TRUE;
}

void DoRecall(int conn)
{
	int x = pMob[conn].MOB.SPX;
	int y = pMob[conn].MOB.SPY;
	int CityID = (pMob[conn].MOB.Merchant & 0xC0) >> 6;

	//srand(time(NULL));
	x = rand() % 15 + g_pGuildZone[CityID].CitySpawnX;
	y = rand() % 15 + g_pGuildZone[CityID].CitySpawnY;

	int Guild = pMob[conn].MOB.Guild;

	if (Guild > 0)
	{
		for (int i = 0; i < MAX_GUILDZONE; i++)
		{
			if (Guild == g_pGuildZone[i].ChargeGuild)
			{
				x = g_pGuildZone[i].GuildSpawnX;
				y = g_pGuildZone[i].GuildSpawnY;

				break;
			}
		}
	}

	// RVR
	//srand(time(NULL));
	if (pMob[conn].TargetX >= 1710 && pMob[conn].TargetX <= 1755 &&
		pMob[conn].TargetY >= 1968 && pMob[conn].TargetY <= 1995 && g_pRvrWar.Status == 1)
	{
		int cape = pMob[conn].MOB.Clan;
		if (cape == 7)
		{
			x = 1754 + rand() % 4;
			y = 1971 + rand() % 20;
		}
		else if (cape == 8)
		{
			x = 1711 + rand() % 4;
			y = 1971 + rand() % 20;
		}
	}

	if (pMob[conn].Extra.ClassMaster == MORTAL && pMob[conn].MOB.CurrentScore.Level < FREEEXP)
	{
		x = 2112 + rand()%5 - 3;
		y = 2042 + rand()%5 - 3;
	}

	int tret = GetEmptyMobGrid(conn, &x, &y);

	MSG_Action sm;
	memset(&sm, 0, sizeof(MSG_Action));

	GetAction(conn, x, y, &sm);

	sm.Effect = 1;

	if (conn < MAX_USER)
		pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(sm));

	GridMulticast(conn, x, y, (MSG_STANDARD*)&sm);
}

void DoWar(int myguild, int target)
{
	int max_guild = 65536;

	if (myguild <= 0 || target < 0 || myguild >= max_guild || target >= max_guild)
	{
		sprintf(temp, "err,dowar my: %d ta:%d", myguild, target);
		Log(temp, "-system", 0);
		return;
	}

	char myGuildName[16];
	char targetGuildName[16];

	BASE_GetGuildName(ServerGroup, myguild, myGuildName);
	BASE_GetGuildName(ServerGroup, target, targetGuildName);

	int myGuildWar = g_pGuildWar[myguild];

	if (myGuildWar < 0 || myGuildWar >= max_guild)
		myGuildWar = 0;

	int targetGuildWar = g_pGuildWar[target];

	if (target)
	{
		if (myGuildWar || !target || targetGuildWar == myguild)
		{
			if (myGuildWar || !target || targetGuildWar != myguild)
			{
				sprintf(temp, "err,dowar my:%d ta:%d ct:%d et:%d", myguild, target, myGuildWar, targetGuildWar);
				Log(temp, "-system", 0);
			}
			else
			{
				sprintf(temp, g_pMessageStringTable[_SS_War_Started], myGuildName, targetGuildName);
				SendNotice(temp);

				g_pGuildWar[myguild] = target;

				for (int i = 0; i < MAX_USER; i++)
				{
					if (pUser[i].Mode == USER_PLAY && (pMob[i].MOB.Guild == myguild || pMob[i].MOB.Guild == target))
						SendWarInfo(i, g_pGuildZone[4].Clan);

				}
			}
		}

		else
		{
			sprintf(temp, g_pMessageStringTable[_SS_War_Declared], myGuildName, targetGuildName);

			SendGuildNotice(myguild, temp);
			SendGuildNotice(target, temp);

			g_pGuildWar[myguild] = target;
		}
	}
	else
	{
		if (myGuildWar <= 0 || myGuildWar >= max_guild)
			return;

		targetGuildWar = g_pGuildWar[myGuildWar];

		BASE_GetGuildName(ServerGroup, myGuildWar, targetGuildName);

		if (targetGuildWar == myguild)
		{
			sprintf(temp, g_pMessageStringTable[_SS_War_Canceled], myGuildName, targetGuildName);

			g_pGuildWar[myGuildWar] = 0;
			g_pGuildWar[myguild] = 0;

			for (int j = 0; j < MAX_USER; j++)
			{
				if (pUser[j].Mode == USER_PLAY && (pMob[j].MOB.Guild == myguild || pMob[j].MOB.Guild == myGuildWar))
					SendWarInfo(j, g_pGuildZone[4].Clan);
			}
		}

		else
		{
			sprintf(temp, g_pMessageStringTable[_SS_War_declare_canceled], myGuildName, targetGuildName);
			g_pGuildWar[myguild] = 0;
		}

		SendGuildNotice(myguild, temp);
		SendGuildNotice(myGuildWar, temp);
	}
}

void DoAlly(int myguild, int target)
{
	int max_guild = 65536;

	if (myguild <= 0 || target < 0 || myguild >= max_guild || target >= max_guild)
	{
		sprintf(temp, "err,doally my: %d ta:%d", myguild, target);
		Log(temp, "-system", 0);
		return;
	}

	char myGuildName[16];
	char targetGuildName[16];

	BASE_GetGuildName(ServerGroup, myguild, myGuildName);
	BASE_GetGuildName(ServerGroup, target, targetGuildName);

	int myGuildAlly = g_pGuildAlly[myguild];

	if (myGuildAlly < 0 || myGuildAlly >= max_guild)
		myGuildAlly = 0;

	int targetGuildAlly = g_pGuildAlly[target];

	if (!myGuildAlly)
	{
		if (!myGuildAlly && target)
		{
			sprintf(temp, g_pMessageStringTable[_SS_Ally_Declared], myGuildName, targetGuildName);

			SendNotice(temp);

			g_pGuildAlly[myguild] = target;
		}
	}
	else
	{
		myGuildAlly = g_pGuildAlly[myguild];

		if (myGuildAlly > 0 && myGuildAlly < max_guild)
		{
			BASE_GetGuildName(ServerGroup, myGuildAlly, targetGuildName);

			sprintf(temp, g_pMessageStringTable[_SS_Ally_Canceled], myGuildName, targetGuildName);

			SendNotice(temp);

			g_pGuildAlly[myguild] = 0;
		}
	}

	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode == USER_PLAY && pMob[i].MOB.Guild == myguild)
			SendWarInfo(i, g_pGuildZone[4].Clan);
	}
}

void DoDeprivate(int conn, int target)
{
	if (conn <= 0 || conn > MAX_USER)
	{
		Log("err,dodeprivate - conn", "-system", 0);

		return;
	}

	int Guild = pMob[conn].MOB.Guild;
	int GuildLevel = pMob[conn].MOB.GuildLevel;


	if (target <= 0 || target > MAX_USER || pUser[target].Mode != USER_PLAY)
	{
		SendClientMsg(conn, g_pMessageStringTable[_NN_Not_Connected]);

		return;
	}

	if (GuildLevel <= pMob[target].MOB.GuildLevel)
	{
		SendClientMsg(conn, g_pMessageStringTable[_NN_Only_Guild_Master_Can]);
		return;
	}

	int sub = pMob[conn].MOB.GuildLevel;
	int Disqualified = FALSE;
	int gGuild = pMob[target].MOB.Guild;

	if (Guild != gGuild)
		return;

	if (sub >= 6 && sub <= 8 && pMob[target].MOB.GuildLevel < 6 || sub == 9)
	{
		Disqualified = TRUE;

		if(pMob[target].MOB.GuildLevel >= 6 && pMob[target].MOB.GuildLevel <= 8)
		{
			if(GuildInfo[gGuild].Sub1 != 0)
				GuildInfo[gGuild].Sub1 = 0;

			else if(GuildInfo[gGuild].Sub2 != 0)
				GuildInfo[gGuild].Sub2 = 0;
		
			else if(GuildInfo[gGuild].Sub3 != 0)
				GuildInfo[gGuild].Sub3 = 0;
		

			sprintf(temp, "etc,subdelete subname:%s guild:%d ", pMob[target].MOB.MobName, Guild);
			Log(temp, pUser[conn].AccountName, pUser[conn].IP);

			MSG_GuildInfo sm_gi;
			memset(&sm_gi, 0, sizeof(MSG_GuildInfo));

			sm_gi.Type = _MSG_GuildInfo;
			sm_gi.Size = sizeof(MSG_GuildInfo);
			sm_gi.ID = conn;

			sm_gi.Guild = Guild;
			sm_gi.GuildInfo = GuildInfo[Guild];

			DBServerSocket.SendOneMessage((char*)&sm_gi, sizeof(MSG_GuildInfo));
		}

		time_t mtime;
		time(&mtime);

		//----------Sistema de GuildHall
		unsigned int GuildIndex = pMob[conn].MOB.Guild;

		ReadGuildHall(conn);

		GuildHall[GuildIndex].TotalMember--;

		WriteGuildHall(conn);

		//-----------------------------------

		pMob[target].Extra.LastPenalty = mtime;

		pMob[target].MOB.Guild = 0;
		pMob[target].MOB.GuildLevel = 0;

		MSG_CreateMob sm;
		memset(&sm, 0, sizeof(MSG_CreateMob));

		GetCreateMob(target, &sm);

		GridMulticast(pMob[target].TargetX, pMob[target].TargetY, (MSG_STANDARD*)&sm, 0);
	}


	if (Disqualified == FALSE)
	{
		SendClientMsg(conn, g_pMessageStringTable[_NN_Deprivate]);

		return;
	}

	SendScore(target);

	SendClientMsg(target, g_pMessageStringTable[_NN_Disqualified_By_Guild_Master]);
	SendClientMsg(conn, g_pMessageStringTable[_NN_Disqualify]);
}

void ProcessRanking()
{
	if (RankingTime <= 0)
		return;

	RankingTime--;

	if (RankingTime % 5 == 0)
	{
		int Rank1 = 0;
		int Rank2 = 0;

		for (int i = 1; i < MAX_USER; i++)
		{
			if (pUser[i].Mode != USER_PLAY)
				continue;

			if (pMob[i].MOB.CurrentScore.Hp <= 0)
				continue;

			int posX = pMob[i].TargetX;
			int posY = pMob[i].TargetY;

			if (posX >= kRanking1X && posX <= kRanking2X && posY >= kRanking1Y && posY <= kRanking2Y)
			{
				if (RankingProgress == 1)
				{
					if (i == Ranking1)
						Rank1++;

					if (i == Ranking2)
						Rank2++;
				}

				else
				{
					if (pMob[i].MOB.Guild == Ranking1)
						Rank1++;

					if (pMob[i].MOB.Guild == Ranking2)
						Rank2++;
				}
			}
		}

		if (Rank1 == 0 || Rank2 == 0)
			RankingTime = 0;
	}

	if (RankingTime >= 60)
	{
		if (RankingTime >= 120)
		{
			if (RankingTime < 180)
			{
				SendDamage(142, 4007, 195, 4019);
				SendDamage(142, 4070, 195, 4082);

				SendEnvEffect(142, 4007, 168, 4018, 32, 0);
				SendEnvEffect(142, 4071, 168, 4082, 32, 0);
				SendEnvEffect(169, 4007, 195, 4018, 32, 0);
				SendEnvEffect(169, 4071, 195, 4082, 32, 0);
			}
		}
		else
		{
			SendDamage(142, 4007, 195, 4034);
			SendDamage(142, 4055, 195, 4082);

			SendEnvEffect(142, 4007, 168, 4018, 32, 0);
			SendEnvEffect(142, 4071, 168, 4082, 32, 0);
			SendEnvEffect(142, 4019, 168, 4030, 32, 0);
			SendEnvEffect(142, 4059, 168, 4070, 32, 0);
			SendEnvEffect(168, 4007, 195, 4018, 32, 0);
			SendEnvEffect(168, 4071, 195, 4082, 32, 0);
			SendEnvEffect(168, 4019, 195, 4030, 32, 0);
			SendEnvEffect(168, 4059, 195, 4070, 32, 0);
		}
	}
	else
	{
		SendDamage(142, 4007, 195, 4042);
		SendDamage(142, 4046, 195, 4082);
		SendEnvEffect(142, 4007, 168, 4018, 32, 0);
		SendEnvEffect(142, 4071, 168, 4082, 32, 0);
		SendEnvEffect(142, 4019, 168, 4030, 32, 0);
		SendEnvEffect(142, 4059, 168, 4070, 32, 0);
		SendEnvEffect(142, 4031, 168, 4042, 32, 0);
		SendEnvEffect(142, 4047, 168, 4058, 32, 0);
		SendEnvEffect(168, 4007, 195, 4018, 32, 0);
		SendEnvEffect(168, 4071, 195, 4082, 32, 0);
		SendEnvEffect(168, 4019, 195, 4030, 32, 0);
		SendEnvEffect(168, 4059, 195, 4070, 32, 0);
		SendEnvEffect(168, 4031, 195, 4042, 32, 0);
		SendEnvEffect(168, 4047, 195, 4058, 32, 0);
	}

	if (RankingTime <= 0)
	{
		int Rank1 = 0;
		int Rank2 = 0;

		for (int i = 1; i < MAX_USER; i++)
		{
			if (pUser[i].Mode != USER_PLAY)
				continue;

			if (pMob[i].MOB.CurrentScore.Hp <= 0)
				continue;

			int posX = pMob[i].TargetX;
			int posY = pMob[i].TargetY;

			if (posX >= kRanking1X && posX <= kRanking2X && posY >= kRanking1Y && posY <= kRanking2Y)
			{
				if (RankingProgress == 1)
				{
					if (i == Ranking1)
						Rank1++;

					if (i == Ranking2)
						Rank2++;
				}

				else
				{
					if (pMob[i].MOB.Guild == Ranking1)
						Rank1++;

					if (pMob[i].MOB.Guild == Ranking2)
						Rank2++;
				}
			}
		}

		nRanking1[15] = 0;
		nRanking1[16] = 0;
		nRanking2[15] = 0;
		nRanking2[16] = 0;

		nTitle1[15] = 0;
		nTitle1[16] = 0;
		nTitle2[15] = 0;
		nTitle2[16] = 0;


		if (Rank1 == Rank2)
		{
			sprintf(temp, g_pMessageStringTable[_SS_S_S_Draw], nRanking1, nRanking2);

			SendNoticeArea(temp, cRanking1X, cRanking1Y, cRanking2X, cRanking2Y);
			SendNoticeArea(temp, kRanking1X, kRanking1Y, kRanking2X, kRanking2Y);
		}

		else
		{
			if (Rank1 <= Rank2)
				sprintf(temp, g_pMessageStringTable[_SS_S_WinBy_S], nRanking2, nRanking1);
			else
				sprintf(temp, g_pMessageStringTable[_SS_S_WinBy_S], nRanking1, nRanking2);

			SendNoticeArea(temp, cRanking1X, cRanking1Y, cRanking2X, cRanking2Y);
			SendNoticeArea(temp, kRanking1X, kRanking1Y, kRanking2X, kRanking2Y);

			MSG_MessageDBRecord sm;
			memset(&sm, 0, sizeof(MSG_MessageDBRecord));

			sm.Type = _MSG_MessageDBRecord;
			sm.ID = 0;
			sm.Size = sizeof(MSG_MessageDBRecord);

			if (RankingProgress != 1 || Ranking1 <= 0 || Ranking1 >= MAX_USER || Ranking2 <= 0 || Ranking2 >= MAX_USER)
			{
				if (Rank1 <= Rank2)
					sprintf(temp, "RNK %d %d %s %d %d %s %d %d", ServerIndex, RankingProgress, nRanking2, lTitle2, Ranking2, nRanking1, lTitle1, Ranking1);
				else
					sprintf(temp, "RNK %d %d %s %d %d %s %d %d", ServerIndex, RankingProgress, nRanking1, lTitle1, Ranking1, nRanking2, lTitle2, Ranking2);
			}

			else
			{
				int GuildR1 = pMob[Ranking1].MOB.Guild;
				int GuildR2 = pMob[Ranking2].MOB.Guild;

				if (Rank1 <= Rank2)
					sprintf(temp, "RNK %d %d %s %d %d %s %d %d", ServerIndex, RankingProgress, nRanking2, lTitle2, GuildR2, nRanking1, lTitle1, GuildR1);
				else
					sprintf(temp, "RNK %d %d %s %d %d %s %d %d", ServerIndex, RankingProgress, nRanking1, lTitle1, GuildR1, nRanking2, lTitle2, GuildR2);
			}

			DBServerSocket.SendOneMessage((char*)&sm, sm.Size);
		}

		RankingProgress = 0;
		RankingTime = 0;
		Ranking1 = 0;
		Ranking2 = 0;

		nRanking1[0] = 0;
		nRanking2[0] = 0;

		ClearAreaTeleport(kRanking1X, kRanking1Y, kRanking2X, kRanking2Y, 2572, 1752);
	}
}

void DoRanking(int tDuel, int conn, int enemy)
{
	if (tDuel == 0)
	{
		int duelTime = 121;

		if (conn < 0 || conn >= MAX_USER || enemy < 0 || enemy >= MAX_USER)
			return;

		strncpy(nRanking1, pMob[conn].MOB.MobName, NAME_LENGTH);
		strncpy(nRanking2, pMob[enemy].MOB.MobName, NAME_LENGTH);

		lTitle1 = pMob[conn].MOB.CurrentScore.Level;
		lTitle2 = pMob[enemy].MOB.CurrentScore.Level;

		DoTeleport(conn, Ranking2X, Ranking2Y);
		DoTeleport(enemy, Ranking1X, Ranking1Y);

		sprintf(temp, g_pMessageStringTable[_NN_Battle_Started], pMob[conn].MOB.MobName, pMob[enemy].MOB.MobName);

		SendClientMsg(conn, temp);
		SendClientMsg(enemy, temp);

		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_StartTime, 2 * duelTime - 2);
		SendClientSignalParm(enemy, ESCENE_FIELD, _MSG_StartTime, 2 * duelTime - 2);

		RankingProgress = 1;
		Ranking1 = conn;
		Ranking2 = enemy;
		RankingTime = duelTime;

		return;
	}

	int duelTime = 301;

	int GuildR1 = pMob[conn].MOB.Guild;
	int GuildR2 = pMob[enemy].MOB.Guild;

	if (GuildR1 <= 0 || GuildR2 <= 0)
		return;

	if(GuildR1 == GuildR2)
		return;

	RankingProgress = tDuel + 1;
	Ranking1 = GuildR1;
	Ranking2 = GuildR2;
	RankingTime = duelTime;

	BASE_GetGuildName(ServerGroup, Ranking1, nRanking1);
	BASE_GetGuildName(ServerGroup, Ranking2, nRanking2);

	strncpy(nTitle1, pMob[conn].MOB.MobName, NAME_LENGTH);

	lTitle1 = pMob[conn].MOB.CurrentScore.Level;

	strncpy(nTitle2, pMob[enemy].MOB.MobName, NAME_LENGTH);

	lTitle2 = pMob[enemy].MOB.CurrentScore.Level;

	int jRank1 = 5;
	int jRank2 = 5;

	if (tDuel == 2)
	{
		jRank1 = 10;
		jRank2 = 10;
	}

	else if (tDuel == 3)
	{
		jRank1 = 100;
		jRank2 = 100;

		SummonGuild(Ranking1, Ranking1X, Ranking1Y, 100, 3);
		SummonGuild(Ranking2, Ranking1X, Ranking1Y, 100, 3);
	}

	else
	{
		for (int i = cRanking1Y; i <= cRanking2Y; i++)
		{
			for (int j = cRanking1X; j <= cRanking2X; j++)
			{
				int tmob = pMobGrid[i][j];

				if (tmob <= 0 || tmob >= MAX_USER)
					continue;

				if (jRank1 > 0 && pMob[tmob].MOB.Guild == Ranking1)
				{
					jRank1--;

					DoTeleport(tmob, Ranking1X, Ranking1Y);

					SendClientMsg(tmob, g_pMessageStringTable[194]);
					SendClientSignalParm(tmob, ESCENE_FIELD, _MSG_StartTime, 2 * duelTime - 2);
				}

				if (jRank2 > 0 && pMob[tmob].MOB.Guild == Ranking2)
				{
					jRank2--;

					DoTeleport(tmob, Ranking2X, Ranking2Y);

					SendClientMsg(tmob, g_pMessageStringTable[194]);
					SendClientSignalParm(tmob, ESCENE_FIELD, _MSG_StartTime, 2 * duelTime - 2);
				}
				if (jRank1 <= 0 || jRank2 <= 0)
					break;
			}
		}
	}
}

void DoRemoveHide(int conn)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	for (int i = 0; i < MAX_AFFECT; i++)
	{
		if (pMob[conn].Affect[i].Type != 28)
			continue;

		pMob[conn].Affect[i].Type = 0;
		pMob[conn].Affect[i].Value = 0;
		pMob[conn].Affect[i].Level = 0;
		pMob[conn].Affect[i].Time = 0;

		pMob[conn].GetCurrentScore(conn);
		SendScore(conn);

		break;
	}
}

void DoRemoveSamaritano(int conn)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	for (int i = 0; i < MAX_AFFECT; i++)
	{
		if (pMob[conn].Affect[i].Type != 24)
			continue;

		pMob[conn].Affect[i].Type = 0;
		pMob[conn].Affect[i].Value = 0;
		pMob[conn].Affect[i].Level = 0;
		pMob[conn].Affect[i].Time = 0;

		pMob[conn].GetCurrentScore(conn);
		SendScore(conn);

		break;
	}
}

void DoTeleport(int mob, int x, int y)
{
	MSG_Action sm;
	memset(&sm, 0, sizeof(MSG_Action));

	int ret = GetEmptyMobGrid(mob, &x, &y);

	if (ret)
	{
		GetAction(mob, x, y, &sm);

		sm.Effect = 1; // teleport effect

		if (mob < MAX_USER)
			pUser[mob].cSock.AddMessage((char*)&sm, sizeof(MSG_Action));

		GridMulticast(mob, x, y, (MSG_STANDARD*)&sm);
	}
}

void DoSummon(int target, int x, int y)
{
	MSG_Action sm;

	memset(&sm, 0, sizeof(MSG_Action));

	int tret = GetEmptyMobGrid(target, &x, &y);

	GetAction(target, x, y, &sm);

	sm.Effect = 1; // teleport effect

	if (target < MAX_USER)
		pUser[target].cSock.SendOneMessage((char*)&sm, sizeof(sm));

	GridMulticast(target, x, y, (MSG_STANDARD*)&sm);
}

void DoGreatTeleport(int mob, int x, int y)
{
	MSG_Action sm;
	memset(&sm, 0, sizeof(MSG_Action));

	int ret = GetEmptyMobGridGreat(mob, &x, &y);

	if (ret)
	{
		GetAction(mob, x, y, &sm);

		sm.Effect = 1; // teleport effect

		if (mob < MAX_USER)
			pUser[mob].cSock.SendOneMessage((char*)&sm, sizeof(sm));

		GridMulticast(mob, x, y, (MSG_STANDARD*)&sm);
	}
}

BOOL SetAffect(int conn, int skillnum, int time, int Level)
{
	if (pMob[conn].MOB.Merchant == 1 || conn > MAX_USER)
		return FALSE;

	int sAffectType = g_pSpell[skillnum].AffectType;
	int sAggressive = g_pSpell[skillnum].Aggressive;

	if (pMob[conn].MOB.Rsv & RSV_BLOCK && sAggressive)
		return FALSE;

	int EmptyAffect = GetEmptyAffect(conn, sAffectType);

	if (sAffectType <= 0 || EmptyAffect  < 0 || EmptyAffect >= MAX_AFFECT)
		return FALSE;

	int sType = pMob[conn].Affect[EmptyAffect].Type;

	pMob[conn].Affect[EmptyAffect].Type = sAffectType;
	pMob[conn].Affect[EmptyAffect].Value = g_pSpell[skillnum].AffectValue;

	int sTime = (g_pSpell[skillnum].AffectTime + 1) * time / 100;

	if(sType == 1 || sType == 3 || sType == 10)
		sTime = 4;

	
	if (sType == sAffectType && (unsigned int)sTime > pMob[conn].Affect[EmptyAffect].Time)
		pMob[conn].Affect[EmptyAffect].Time = sTime;

	else
		pMob[conn].Affect[EmptyAffect].Time = sTime;

	//correção Timer Soul
	//if (sType == 29)
	//{
		//if (pMob[conn].MOB.CurrentScore.Level <= 40)
		//	sTime = 5;
		//else
		//	sTime = 50;

		//pMob[conn].Affect[EmptyAffect].Time = sTime;
	//}

	if (sType == sAffectType && Level > pMob[conn].Affect[EmptyAffect].Level)
		pMob[conn].Affect[EmptyAffect].Level = Level;

	else
		pMob[conn].Affect[EmptyAffect].Level = Level;

	if (time >= 2139062143)
		pMob[conn].Affect[EmptyAffect].Time = 2139062143;

	pMob[conn].GetCurrentScore(conn);

	if (sType == CANCEL_SPEEL_INDEX) { pMob[conn].Affect[EmptyAffect].Time = 2; }

	return TRUE;
}

BOOL SetTick(int mob, int skillnum, int Delay, int Level)
{
	if (pMob[mob].MOB.Merchant == 1 && mob > MAX_USER)
		return FALSE;

	int sTickType = g_pSpell[skillnum].TickType;
	int sAggressive = g_pSpell[skillnum].Aggressive;

	if ((pMob[mob].MOB.Rsv & RSV_BLOCK) && (sAggressive != 0))
		return 0;

	int EmptyAffect = GetEmptyAffect(mob, sTickType);

	if (sTickType > 0 && EmptyAffect >= 0 && EmptyAffect < MAX_AFFECT)
	{
		pMob[mob].Affect[EmptyAffect].Type = sTickType;
		pMob[mob].Affect[EmptyAffect].Value = g_pSpell[skillnum].TickValue;
		pMob[mob].Affect[EmptyAffect].Time = (Delay * (g_pSpell[skillnum].AffectTime + 1)) / 100;

		if (Delay >= 500000000)
			pMob[mob].Affect[EmptyAffect].Time = 500000000;

		if(pMob[mob].Affect[EmptyAffect].Time >= 3 && (sTickType == 1 || sTickType == 3 || sTickType == 10))
			pMob[mob].Affect[EmptyAffect].Time = 2;

		pMob[mob].Affect[EmptyAffect].Level = Level;


		if (sTickType == CANCEL_SPEEL_INDEX) { pMob[mob].Affect[EmptyAffect].Time = 2; }

		pMob[mob].GetCurrentScore(mob);

		
		return TRUE;
	}

	return FALSE;
}

void ProcessDecayItem()
{
	for (int i = 0; i < ItemCount; i++)
	{
		ItemCount++;

		if (ItemCount >= 5000)
			ItemCount = g_dwInitItem + 1;

		if (pItem[ItemCount].ITEM.sIndex == 1727)
			continue;

		if (pItem[ItemCount].Mode == 0 || pItem[ItemCount].Mode == 2)
			continue;

		if (pItem[ItemCount].Delay >= 1)
		{
			pItem[ItemCount].Delay--;
			continue;
		}

		if (pItem[ItemCount].Decay != -1)
		{
			int itemPosX = pItem[ItemCount].PosX;
			int itemPosY = pItem[ItemCount].PosY;

			BASE_ClearItem(&pItem[ItemCount].ITEM);

			pItemGrid[itemPosX][itemPosY] = 0;
			pItem[ItemCount].Mode = 0;

			MSG_DecayItem sm;
			memset(&sm, 0, sizeof(MSG_DecayItem));

			sm.Type = _MSG_DecayItem;
			sm.Size = sizeof(MSG_DecayItem);
			sm.ID = ESCENE_FIELD;

			sm.ItemID = ItemCount + 10000;

			GridMulticast(itemPosX, itemPosY, (MSG_STANDARD*)&sm, 0);
		}
	}
}

int  CombineTreasureMap(int conn)
{
	for (int i = 0; i < MAX_CARRY; i++)
	{
		if (pMob[conn].MOB.Carry[i].sIndex != 788)
			continue;

		if (i + 1 >= MAX_CARRY)
			continue;

		if (pMob[conn].MOB.Carry[i + 1].sIndex != 789)
			continue;

		if (i + 9 >= MAX_CARRY)
			continue;

		if (pMob[conn].MOB.Carry[i + 9].sIndex != 790)
			continue;

		if (i + 10 >= MAX_CARRY)
			continue;

		if (pMob[conn].MOB.Carry[i + 10].sIndex != 791)
			continue;

		if (i + 18 >= MAX_CARRY)
			continue;

		if (pMob[conn].MOB.Carry[i + 18].sIndex != 792)
			continue;

		if (i + 19 >= MAX_CARRY)
			continue;

		if (pMob[conn].MOB.Carry[i + 19].sIndex != 793)
			continue;

		MSG_MessageDBRecord sm;
		memset(&sm, 0, sizeof(MSG_MessageDBRecord));

		sm.Type = _MSG_MessageDBRecord;
		sm.ID = 0;

		sm.Size = sizeof(MSG_MessageDBRecord);

		sprintf(sm.Record, "ETC treasure_map %d %s %s", ServerIndex, pUser[conn].AccountName, pMob[conn].MOB.MobName);

		DBServerSocket.SendOneMessage((char*)&sm, sizeof(MSG_MessageDBRecord));

		if (i >= MAX_CARRY)
			continue;

		pMob[conn].MOB.Carry[i].sIndex = 0;
		SendItem(conn, ITEM_PLACE_CARRY, i, &pMob[conn].MOB.Carry[i]);

		if (i + 1 >= MAX_CARRY)
			continue;

		pMob[conn].MOB.Carry[i + 1].sIndex = 0;
		SendItem(conn, ITEM_PLACE_CARRY, i + 1, &pMob[conn].MOB.Carry[i + 1]);

		if (i + 9 >= MAX_CARRY)
			continue;

		pMob[conn].MOB.Carry[i + 9].sIndex = 0;
		SendItem(conn, ITEM_PLACE_CARRY, i + 9, &pMob[conn].MOB.Carry[i + 9]);

		if (i + 10 >= MAX_CARRY)
			continue;

		pMob[conn].MOB.Carry[i + 10].sIndex = 0;
		SendItem(conn, ITEM_PLACE_CARRY, i + 10, &pMob[conn].MOB.Carry[i + 10]);

		if (i + 18 >= MAX_CARRY)
			continue;

		pMob[conn].MOB.Carry[i + 18].sIndex = 0;
		SendItem(conn, ITEM_PLACE_CARRY, i + 18, &pMob[conn].MOB.Carry[i + 18]);

		if (i + 19 >= MAX_CARRY)
			continue;

		pMob[conn].MOB.Carry[i + 19].sIndex = 0;
		SendItem(conn, ITEM_PLACE_CARRY, i + 19, &pMob[conn].MOB.Carry[i + 19]);

		SendClientMsg(conn, g_pMessageStringTable[_NN_Treasure_Map]);

		return TRUE;
	}

	int itemCount = 0;

	for (int i = 0; i < MAX_CARRY; i++)
	{
		if (pMob[conn].MOB.Carry[i].sIndex >= 788 && pMob[conn].MOB.Carry[i].sIndex <= 793)
		{
			pMob[conn].MOB.Carry[i].sIndex = 485;

			SendItem(conn, ITEM_PLACE_CARRY, i, &pMob[conn].MOB.Carry[i]);

			itemCount++;
		}
	}

	if (itemCount <= 0)
		return 0;

	SendClientMsg(conn, g_pMessageStringTable[_NN_Congratulations]);
	return TRUE;
}

void Combine(int conn, int item, int PrizeItem)
{
	int founditem = 0;

	if (conn < 0 || conn >= MAX_USER)
		return;

	for (int i = 0; i < MAX_CARRY; i++)
	{
		int index = pMob[conn].MOB.Carry[i].sIndex;

		if (index == item)
			founditem += pMob[conn].MOB.Carry[i].stEffect[0].cEffect == 61 ? pMob[conn].MOB.Carry[i].stEffect[0].cValue : 1;

		if (founditem >= 10)
			break;
	}

	if (founditem < 10)
		return;

	int clearitem = 0;

	for (int i = 0; i < MAX_CARRY; i++)
	{
		int index = pMob[conn].MOB.Carry[i].sIndex;

		if (index != item)
			continue;

		if (clearitem >= founditem)
			break;

		clearitem += pMob[conn].MOB.Carry[i].stEffect[0].cEffect == 61 ? pMob[conn].MOB.Carry[i].stEffect[0].cValue : 1;

		if (pMob[conn].MOB.Carry[i].stEffect[0].cEffect == 61 && pMob[conn].MOB.Carry[i].stEffect[0].cValue > 10)
			pMob[conn].MOB.Carry[i].stEffect[0].cValue -= 10;

		else
			BASE_ClearItem(&pMob[conn].MOB.Carry[i]);


		if (clearitem < 10)
			continue;
	}

	STRUCT_ITEM Prize;

	Prize.sIndex = PrizeItem;
	//srand(time(NULL));
	Prize.stEffect[0].cEffect = 59;
	Prize.stEffect[0].cValue = rand() % 100;
	//srand(time(NULL));
	Prize.stEffect[1].cEffect = 59;
	Prize.stEffect[1].cValue = rand() % 100;
	//srand(time(NULL));
	Prize.stEffect[2].cEffect = 59;
	Prize.stEffect[2].cValue = rand() % 50 + 50;

	int i = 0;

	for (i = 0; i < MAX_CARRY; i++)
	{
		int error = -1;

		//if (BASE_CanCarry(&Prize, pMob[conn].MOB.Carry, i % 9, i / 9, &error) == 1)
		//	break;

		if (pMob[conn].MOB.Carry[i].sIndex == 0)
			break;
	}
	//srand(time(NULL));
	if (i >= 0 && i < MAX_CARRY)
	{
		*(int*)&pMob[conn].MOB.Carry[i] = *(int*)&Prize;
		*(int*)((int)&pMob[conn].MOB.Carry[i] + 4) = *(int*)((int)&Prize + 4);
	}

	else
		CreateItem(pMob[conn].TargetX, pMob[conn].TargetY, &Prize, rand() % 4, 1);
}

int ApplyHp(int conn)
{
	int retnValue = FALSE;

	//if(pUser[conn].ReqHp > pMob[conn].MOB.CurrentScore.MaxHp)
	//	pUser[conn].ReqHp = pMob[conn].MOB.CurrentScore.MaxHp;

	//int hp = pMob[conn].MOB.CurrentScore.Hp;
	//int reqhp = pUser[conn].ReqHp;

	//if(reqhp > hp)
	//{
	//	int hpdif = reqhp - hp;
	//	if (reqhp - hp > 2000)
	//		hpdif = 2000;

	//	hp += hpdif;

	//	if (hp > 2000000000)
	//		hp = 2000000000;

	//	pMob[conn].MOB.CurrentScore.Hp = hp;

	//	if(pMob[conn].MOB.CurrentScore.Hp > reqhp)
	//		pMob[conn].MOB.CurrentScore.Hp = reqhp;

	//	retnValue = TRUE;
	//}
	//else
	//	retnValue = FALSE;

	return retnValue;
}

int ApplyMp(int conn)
{
	int retnValue = FALSE;

	//if (pUser[conn].ReqMp > pMob[conn].MOB.CurrentScore.MaxMp)
	//	pUser[conn].ReqMp = pMob[conn].MOB.CurrentScore.MaxMp;

	//int mp = pMob[conn].MOB.CurrentScore.Mp;
	//int reqmp = pUser[conn].ReqMp;

	//if (reqmp > mp)
	//{
	//	int mpdif = reqmp - mp;
	//	if (reqmp - mp > 2000)
	//		mpdif = 2000;

	//	mp += mpdif;

	//	if (mp > 2000000000)
	//		mp = 2000000000;

	//	pMob[conn].MOB.CurrentScore.Mp = mp;

	//	if (pMob[conn].MOB.CurrentScore.Mp > reqmp)
	//		pMob[conn].MOB.CurrentScore.Mp = reqmp;

	//	retnValue = TRUE;
	//}
	//else
	//	retnValue = FALSE;

	return retnValue;
}

void SetReqHp(int conn)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	//if (pUser[conn].ReqHp < 0)
	//	pUser[conn].ReqHp = 0;

	if (pMob[conn].MOB.CurrentScore.Hp > pMob[conn].MOB.CurrentScore.MaxHp)
		pMob[conn].MOB.CurrentScore.Hp = pMob[conn].MOB.CurrentScore.MaxHp;

	//if (pUser[conn].ReqHp < pMob[conn].MOB.CurrentScore.Hp)
	//	pUser[conn].ReqHp = pMob[conn].MOB.CurrentScore.Hp;
}

void SetReqMp(int conn)
{
	if (conn <= 0 || conn >= MAX_USER)
		return;

	//if (pUser[conn].ReqMp < 0)
	//	pUser[conn].ReqMp = 0;

	if (pMob[conn].MOB.CurrentScore.Mp > pMob[conn].MOB.CurrentScore.MaxMp)
		pMob[conn].MOB.CurrentScore.Mp = pMob[conn].MOB.CurrentScore.MaxMp;

	//if (pUser[conn].ReqMp < pMob[conn].MOB.CurrentScore.Mp)
	//	pUser[conn].ReqMp = pMob[conn].MOB.CurrentScore.Mp;
}

void ClearMapa(int x, int y)
{
	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;

		if (pMob[i].Mode == MOB_EMPTY)
			continue;

		if ((pMob[i].TargetX /128) != x || (pMob[i].TargetY / 128) != y)
			continue;

		if(pMob[i].MOB.CurrentScore.Hp == 0)
		{
			pMob[i].MOB.CurrentScore.Hp = 2;

			pUser[i].NumError = 0;

			SendScore(i);
			SendSetHpMp(i);
		}

		DoRecall(i);
	}
}

void DeleteMobMapa(int x, int y)
{
	for (int i = MAX_USER; i < MAX_MOB; i++)
	{
		if (pMob[i].Mode == USER_EMPTY)
			continue;

		if ((pMob[i].TargetX / 128) != x || (pMob[i].TargetY / 128) != y)
			continue;

		DeleteMob(i, 1);
	}
}

void ReadLevelItemConfig(void)
{
	FILE *fp = NULL;

	fp = fopen("LevelItem.txt", "rt");

	if (fp == NULL)
	{
		MessageBox(hWndMain, "no LevelItem.txt", "Error", MB_OK | MB_SYSTEMMODAL);

		return;
	}

	memset(&LevelItem, 0, sizeof(LevelItem));

	while (1)
	{
		char tmp[256];
		char *ret = fgets(tmp, 256, fp);

		if (ret == NULL)
			break;

		int cls = 0;
		int type = 0;
		int level = 0;
		STRUCT_ITEM Item;
		memset(&Item, 0, sizeof(STRUCT_ITEM));

		int ival1 = 0, ival2 = 0, ival3 = 0;
		int ival4 = 0, ival5 = 0, ival6 = 0, ival7 = 0;

		sscanf(tmp, "%d %d %d %d %d %d %d %d %d %d", &cls, &type, &level, &ival1, &ival2, &ival3, &ival4, &ival5, &ival6, &ival7);

		Item.sIndex = ival1;
		Item.stEffect[0].cEffect = ival2;
		Item.stEffect[0].cValue = ival3;
		Item.stEffect[1].cEffect = ival4;
		Item.stEffect[1].cValue = ival5;
		Item.stEffect[2].cEffect = ival6;
		Item.stEffect[2].cValue = ival7;

		if (cls == 4 && type != 4)//Item para todas as classes mais não para todas build
		{
			LevelItem[0][type][level] = Item;
			LevelItem[1][type][level] = Item;
			LevelItem[2][type][level] = Item;
			LevelItem[3][type][level] = Item;
		}

		else if (cls == 4 && type == 4)//Item para todas as classes e todas as build
		{
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 4; k++)
					LevelItem[j][k][level] = Item;
			}

		}

		else if (type == 0)//Item para todas as build
		{
			LevelItem[cls][0][level] = Item;
			LevelItem[cls][1][level] = Item;
			LevelItem[cls][2][level] = Item;
			LevelItem[cls][3][level] = Item;
		}

		else
			LevelItem[cls][type][level] = Item;
	}

	fclose(fp);
}

void DoItemLevel(int conn)
{
	int type = 0;

	if ((pMob[conn].MOB.BaseScore.Str > pMob[conn].MOB.BaseScore.Int) && (pMob[conn].MOB.BaseScore.Str > pMob[conn].MOB.BaseScore.Dex))
		type = 1;

	else if ((pMob[conn].MOB.BaseScore.Int > pMob[conn].MOB.BaseScore.Str) && (pMob[conn].MOB.BaseScore.Int > pMob[conn].MOB.BaseScore.Dex))
		type = 2;

	else if ((pMob[conn].MOB.BaseScore.Dex > pMob[conn].MOB.BaseScore.Str) && (pMob[conn].MOB.BaseScore.Dex > pMob[conn].MOB.BaseScore.Int))
		type = 3;


	if (LevelItem[pMob[conn].MOB.Class][type][pMob[conn].MOB.BaseScore.Level].sIndex != 0)
	{
		for (int i = 0; i < MAX_CARGO - 2; i++)
		{
			int retsour = pUser[conn].Cargo[i].sIndex;

			if (retsour != 0)
				continue;
			// nunca se usa [i]
			// se vc quer copiar algum ptr, ou struct, vc tem q usar o memcpy
			memcpy(&pUser[conn].Cargo[i], &LevelItem[pMob[conn].MOB.Class][type][pMob[conn].MOB.BaseScore.Level], sizeof(STRUCT_ITEM));
			//pUser[conn].Cargo[i] = LevelItem[pMob[conn].MOB.Class][type][pMob[conn].MOB.BaseScore.Level];

			SendItem(conn, ITEM_PLACE_CARGO, i, &pUser[conn].Cargo[i]);

			char cMsg[128];

			sprintf(cMsg, "%s [%s]", g_pMessageStringTable[_NN_Item_Arrived], g_pItemList[LevelItem[pMob[conn].MOB.Class][type][pMob[conn].MOB.BaseScore.Level].sIndex].Name);

			SendClientMsg(conn, cMsg);

			char ItemCode[256];

			sprintf(temp, "tra,%s %d", pUser[conn].AccountName, i);
			BASE_GetItemCode(&LevelItem[pMob[conn].MOB.Class][type][pMob[conn].MOB.BaseScore.Level], ItemCode);
			strcat(temp, ItemCode);
			Log(temp, "_lvlreward_", pUser[conn].IP);

			if (pUser[conn].Mode == USER_SELCHAR)
				SaveUser(conn, 0);

			return;
		}
	}
}
	
void SetCircletSubGod(int conn)
{
	if (pMob[conn].Extra.ClassMaster == SCELESTIAL && pMob[conn].MOB.BaseScore.Level == 120 && pMob[conn].Extra.QuestInfo.Celestial.Add120 == 0)
	{
		pMob[conn].Extra.QuestInfo.Celestial.Add120 = 1;

		if(pMob[conn].MOB.Equip[1].sIndex != 0)
		{
			pMob[conn].MOB.Equip[1].stEffect[1].cEffect = EF_AC;
			pMob[conn].MOB.Equip[1].stEffect[1].cValue = 30;
			pMob[conn].MOB.Equip[1].stEffect[2].cEffect = EF_HP;
			pMob[conn].MOB.Equip[1].stEffect[2].cValue = 40;
			SendItem(conn, ITEM_PLACE_EQUIP, 1, &pMob[conn].MOB.Equip[1]);
		}
	}

	if (pMob[conn].Extra.ClassMaster == SCELESTIAL && pMob[conn].MOB.BaseScore.Level == 150 && pMob[conn].Extra.QuestInfo.Celestial.Add150 == 0)
	{
		pMob[conn].Extra.QuestInfo.Celestial.Add150 = 1;

		if(pMob[conn].MOB.Equip[1].sIndex != 0)
		{
			pMob[conn].MOB.Equip[1].stEffect[1].cEffect = EF_AC;
			pMob[conn].MOB.Equip[1].stEffect[1].cValue = 35;
			pMob[conn].MOB.Equip[1].stEffect[2].cEffect = EF_HP;
			pMob[conn].MOB.Equip[1].stEffect[2].cValue = 50;
			SendItem(conn, ITEM_PLACE_EQUIP, 1, &pMob[conn].MOB.Equip[1]);
		}
	}

	if (pMob[conn].Extra.ClassMaster == SCELESTIAL && pMob[conn].MOB.BaseScore.Level == 180 && pMob[conn].Extra.QuestInfo.Celestial.Add180 == 0)
	{
		pMob[conn].Extra.QuestInfo.Celestial.Add180 = 1;

		if(pMob[conn].MOB.Equip[1].sIndex != 0)
		{
			pMob[conn].MOB.Equip[1].stEffect[1].cEffect = EF_AC;
			pMob[conn].MOB.Equip[1].stEffect[1].cValue = 45;
			pMob[conn].MOB.Equip[1].stEffect[2].cEffect = EF_HP;
			pMob[conn].MOB.Equip[1].stEffect[2].cValue = 60;
			SendItem(conn, ITEM_PLACE_EQUIP, 1, &pMob[conn].MOB.Equip[1]);
		}
	}

	if (pMob[conn].Extra.ClassMaster == SCELESTIAL && pMob[conn].MOB.BaseScore.Level == 199 && pMob[conn].Extra.QuestInfo.Celestial.Add200 == 0)
	{
		pMob[conn].Extra.QuestInfo.Celestial.Add200 = 1;

		if(pMob[conn].MOB.Equip[1].sIndex != 0)
		{
			pMob[conn].MOB.Equip[1].stEffect[1].cEffect = EF_AC;
			pMob[conn].MOB.Equip[1].stEffect[1].cValue = 50;
			pMob[conn].MOB.Equip[1].stEffect[2].cEffect = EF_HP;
			pMob[conn].MOB.Equip[1].stEffect[2].cValue = 70;
			SendItem(conn, ITEM_PLACE_EQUIP, 1, &pMob[conn].MOB.Equip[1]);
		}
	}
}

void SummonServer(int tx, int ty)
{
	int summons = 0;

	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY || pMob[i].Mode == USER_EMPTY)
			continue;

		DoGreatTeleport(i, tx, ty);
	}
}

void SummonPlayer(int x, int y, int conn)
{
	
	if (pUser[conn].Mode != USER_PLAY)
		return;

	DoGreatTeleport(conn, x, y);
}

void MobAttack(int attacker, MSG_Attack sm)
{
	//srand(time(NULL));
	int _rd = rand() % 100;

	if(sm.SkillIndex == 109)
	{
		if(_rd < 40)
			sm.SkillIndex = 110;

		else if(_rd < 80)
			sm.SkillIndex = 111;
	}

	for(int i = 0; i < MAX_TARGET; i++)
	{
		int skillbase = sm.SkillIndex;
		int Target = sm.Dam[i].TargetID;

		if (Target <= 0 || Target >= MAX_MOB)
			continue;

		if (pMob[Target].MOB.CurrentScore.Hp <= 0)
			continue;

		sm.FlagLocal = 0;

		Target = sm.Dam[i].TargetID;

		//srand(time(NULL));
		if(skillbase != 109)
			sm.Dam[i].Damage = 500 + rand()%200;

		sm.SkillIndex = skillbase;

		int skill = sm.SkillIndex;

		if (skill >= 0 && skill < MAX_SKILLINDEX && sm.SkillParm == 0)
		{
			if (skill == 33)
				sm.Motion = 253;

			int kind = ((skill % MAX_SKILL / 8) + 1);

			if (kind >= 1 && kind <= 3)
			{
				int special = pMob[attacker].MOB.CurrentScore.Special[kind];
						
				int NeedUpdate = 0;
						
				if (SetAffect(Target, skill, 100, special) != FALSE)
					NeedUpdate = 1;

				if (SetTick(Target, skill, 100, special) != FALSE)
					NeedUpdate = 1;

				if (NeedUpdate)
					SendScore(Target);
			}
		}

		if (Target < MAX_USER && sm.Dam[i].Damage > 0)
		{
			int attackdex = pMob[attacker].MOB.CurrentScore.Dex / 5;

			if (pMob[attacker].MOB.LearnedSkill & 0x1000000)
				attackdex += 100;

			if (pMob[attacker].MOB.Rsv & 0x40)
				attackdex += 500;

			int parryretn = GetParryRate(&pMob[Target].MOB, pMob[Target].Parry, attackdex, pMob[attacker].MOB.Rsv);

			if (sm.SkillIndex == 79 || sm.SkillIndex == 22)
				parryretn = 30 * parryretn / 100;

			//srand(time(NULL));
			int rd = rand() % 1000 + 1;

			if (rd < parryretn)
			{
				sm.Dam[i].Damage = -3;

				if ((pMob[Target].MOB.Rsv & 0x200) != 0 && rd < 100)
					sm.Dam[i].Damage = -4;
			}

			else if (pMob[attacker].MOB.Clan == 4)
				sm.Dam[i].Damage = (2 * sm.Dam[i].Damage) / 5;
		}

		int TargetLeader = pMob[Target].CurrentTarget;
		
		if (sm.Dam[i].Damage > 0)
		{
			if (TargetLeader <= MOB_EMPTY)
				TargetLeader = Target;

			SetBattle(TargetLeader, attacker);

			if (pMob[attacker].MOB.Clan != 4)
				SetBattle(attacker, TargetLeader);

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

					pMob[TargetLeader].PartyList[attacker] = MOB_EMPTY;
					continue;
				}

				SetBattle(partyconn, attacker);
				SetBattle(attacker, partyconn);
			}

			int Summoner = pMob[attacker].Summoner;

			if (pMob[attacker].MOB.Clan == 4 && Target >= MAX_USER && Summoner > 0 && Summoner < MAX_USER && pUser[Summoner].Mode == USER_PLAY)
			{
				int posX = pMob[Summoner].TargetX;
				int posY = pMob[Summoner].TargetY;
				int num = 46;
				int dam = 0;
				int exp = 0;
				int setDam = 0;

				if (pMob[attacker].TargetX > posX - num && pMob[attacker].TargetX < posX + num && pMob[attacker].TargetY > posY - num && pMob[attacker].TargetY < posY + num)
				{
					if (pMob[Target].MOB.CurrentScore.Hp < sm.Dam[i].Damage)
						setDam = pMob[Target].MOB.CurrentScore.Hp;
					else
						setDam = sm.Dam[i].Damage;

					dam = setDam;
					exp = (int)(pMob[Target].MOB.Exp * dam / pMob[Target].MOB.CurrentScore.MaxHp);

					if (pMob[Summoner].MOB.CurrentScore.Level == pMob[attacker].MOB.CurrentScore.Level)
					{
						exp = GetExpApply(pMob[attacker].Extra, exp, pMob[attacker].MOB.CurrentScore.Level, pMob[Target].MOB.CurrentScore.Level);

						if (exp > 12000)
							exp = 12000;

						if (pMob[Target].MOB.Clan == 4)
							exp = 0;

						pMob[Summoner].MOB.Exp = pMob[Summoner].MOB.Exp + exp;
					}
				}
			}
		}

		if (sm.Dam[i].Damage > 0 || sm.Dam[i].Damage <= -5)
		{
			int DamageNow = sm.Dam[i].Damage;
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
		
			for (int c = 0; c < MAX_AFFECT; c++)
			{
				if (pMob[Target].Affect[c].Type == 18)
				{
					if (pMob[Target].MOB.CurrentScore.Mp >((pMob[Target].MOB.CurrentScore.MaxMp / 100) * 10))
					{
						int mana = pMob[Target].MOB.CurrentScore.Mp - (DamageNow >> 1);

						if (mana < 0)
						{
							DamageNow -= mana;
							mana = 0;
						}

						pMob[Target].MOB.CurrentScore.Mp = mana;

						//pUser[Target].ReqMp = pUser[Target].ReqMp - (DamageNow >> 1);
						SetReqMp(Target);

						DamageNow = ((DamageNow >> 1) + (DamageNow << 4)) / 80;
						sm.Dam[i].Damage = DamageNow;
					}
				}
			}

			if (pMob[Target].MOB.Equip[13].sIndex == 786)
			{
				int sanc = pMob[Target].MOB.Equip[13].stEffect[0].cValue;
				
				if (sanc < 2)
					sanc = 2;

				pMob[Target].MOB.CurrentScore.Hp = pMob[Target].MOB.CurrentScore.Hp - ((sm.Dam[i].Damage) / sanc);
			}
			else if (pMob[Target].MOB.Equip[13].sIndex == 1936)
			{
				int sanc = pMob[Target].MOB.Equip[13].stEffect[0].cValue;
				
				if (sanc < 2)
					sanc = 2;

				sanc *= 10;

				pMob[Target].MOB.CurrentScore.Hp = pMob[Target].MOB.CurrentScore.Hp - ((sm.Dam[i].Damage) / sanc);
			}
			else if (pMob[Target].MOB.Equip[13].sIndex == 1937)
			{
				int sanc = pMob[Target].MOB.Equip[13].stEffect[0].cValue;
				
				if (sanc < 2)
					sanc = 2;

				sanc *= 1000;

				pMob[Target].MOB.CurrentScore.Hp = pMob[Target].MOB.CurrentScore.Hp - ((sm.Dam[i].Damage) / sanc);
			}
			else
			{

				if (pMob[Target].MOB.CurrentScore.Hp < sm.Dam[i].Damage)
					pMob[Target].MOB.CurrentScore.Hp = 0;

				else
					pMob[Target].MOB.CurrentScore.Hp = pMob[Target].MOB.CurrentScore.Hp - sm.Dam[i].Damage;

			}

			if(Target > MAX_USER)
				SendScore(Target);

			if (Target > MAX_USER && pMob[Target].MOB.Clan == 4)
				LinkMountHp(Target);

			if (damage > 0)
				ProcessAdultMount(Target, damage);
		}

		GridMulticast(pMob[Target].TargetX, pMob[Target].TargetY, (MSG_STANDARD*)&sm, 0);

		if (Target > 0 && Target < MAX_USER)
		{
			//if (pUser[Target].HP < sm.Dam[i].Damage)
			//	pUser[Target].HP = 0;

			//else
			//	pUser[Target].HP = pUser[Target].HP - sm.Dam[i].Damage;

			if(sm.SkillIndex == 109)
			{
				pMob[Target].MOB.CurrentScore.Hp = 0;
//				pUser[Target].HP = 0;
			}

			SetReqHp(Target);
			SendSetHpMp(Target);
		}

		if (pMob[Target].MOB.CurrentScore.Hp <= 0)
		{
			pMob[Target].MOB.CurrentScore.Hp = 0;
					
			MobKilled(Target, attacker, 0, 0);
		}
	}
}

int  ParseMobMercString(int Num, char *str)
{
	char str1[128];
	str1[0] = 0;

	char str2[128];
	str2[0] = 0;

	char str3[128];
	str3[0] = 0;

	int  value = 0;
	int secondvalue = 0;

	sscanf(str, "%s %s %s", str1, str2, str3);

	if (str[0] == 47)
		return FALSE;

	if (str[0] == 0)
		return FALSE;

	STRUCT_ITEM Item;
	memset(&Item, 0, sizeof(STRUCT_ITEM));

	char item_str1[256];
	char item_str2[256];
	char item_str3[256];
	char item_str4[256];
	char item_str5[256];
	char item_str6[256];
	char item_str7[256];
	char item_str8[256];

	int item_value[8] = { 0, 0, 0, 0, 0, 0, 0 , 0};

	sscanf(str2, "%s %s %s %s %s %s %s - %s", item_str1, item_str2, item_str3, item_str4, item_str5, item_str6, item_str7, item_str8);
	item_value[0] = atoi(item_str1);
	item_value[1] = atoi(item_str2);
	item_value[2] = atoi(item_str3);
	item_value[3] = atoi(item_str4);
	item_value[4] = atoi(item_str5);
	item_value[5] = atoi(item_str6);
	item_value[6] = atoi(item_str7);
	item_value[7] = atoi(item_str8);

	value = atoi(str2);
	secondvalue = atoi(str3);

	if (strlen(str2) > 80)
		return FALSE;

	_strupr(str1);

	if (!strcmp(str1, "MOBNAME:"))
		strncpy(pMobMerc[Num].MobName, str2, NAME_LENGTH);

	else if (!strcmp(str1, "GENERATEINDEX:"))
		pMobMerc[Num].GenerateIndex = value;

	else if (!strcmp(str1, "RENEWTIME:"))
		pMobMerc[Num].RenewTime = value * 2;

	else if (!strcmp(str1, "REBORNTIME:"))
		pMobMerc[Num].RebornTime = value * 2;

	else
	{
		for (int i = 0; i < MAX_CARRY; i++)
		{
			sprintf(temp, "ITEM_%d:", i);

			if (!strcmp(str1, temp))
			{
				pMobMerc[Num].Carry[i].sIndex = item_value[0];
				pMobMerc[Num].Carry[i].stEffect[0].cEffect = item_value[1];
				pMobMerc[Num].Carry[i].stEffect[0].cValue = item_value[2];
				pMobMerc[Num].Carry[i].stEffect[1].cEffect = item_value[3];
				pMobMerc[Num].Carry[i].stEffect[1].cValue = item_value[4];
				pMobMerc[Num].Carry[i].stEffect[2].cEffect = item_value[5];
				pMobMerc[Num].Carry[i].stEffect[2].cValue = item_value[6];

				pMobMerc[Num].MaxStock[i] = item_value[7];
				pMobMerc[Num].Stock[i] = item_value[7];

				return TRUE;
			}
		}
	}
	return TRUE;
}

void DeleteGenerateMob(int generate)
{
	for (int i = MAX_USER; i < MAX_MOB; i++)
	{
		if (pMob[i].Mode == MOB_EMPTY)
			continue;

		if (pMob[i].GenerateIndex != generate)
			continue;

		DeleteMob(i, 3);
	}
}

int  CreateTreasureBox(int x, int y, STRUCT_ITEM *item, int rotate, int State)
{
	if (item->sIndex <= 0 || item->sIndex >= MAX_ITEMLIST)
		return FALSE;

	GetEmptyItemGrid(&x, &y);


	if (pItemGrid[y][x])
		return FALSE;

	int empty = GetEmptyItem();

	if (empty == 0)
		return FALSE;

	pItem[empty].Mode = 2;

	pItem[empty].PosX = x;
	pItem[empty].PosY = y;

	memcpy(&pItem[empty].ITEM, item, sizeof(STRUCT_ITEM));

	pItem[empty].Rotate = rotate;
	pItem[empty].State = State;

	pItem[empty].Delay = 0;
	pItem[empty].Decay = 0;

	pItem[empty].GridCharge = BASE_GetItemAbility(item, EF_GROUND);

	pItemGrid[y][x] = empty;

	pItem[empty].Height = pHeightGrid[y][x];

	MSG_CreateItem sm;
	memset(&sm, 0, sizeof(MSG_CreateItem));

	sm.Type = _MSG_CreateItem;
	sm.Size = sizeof(MSG_CreateItem);
	sm.ID = ESCENE_FIELD;

	sm.ItemID = empty + 10000;

	memcpy(&sm.Item, &pItem[empty].ITEM, sizeof(STRUCT_ITEM));

	sm.GridX = x;
	sm.GridY = y;

	sm.Rotate = rotate;
	sm.State = pItem[empty].State;

	sm.Height = -204;

	GridMulticast(x, y, (MSG_STANDARD*)&sm, 0);

	return TRUE;
}

int GetUserLojaMac(int conn)
{
	int userCount = 0;
	
		if (pUser[conn].Mode != USER_PLAY)
			return FALSE;

		if (pMob[conn].Mode == 0)
			return FALSE;

		for (int i = 1; i < MAX_USER; i++)
		{
			if (pUser[i].Mode != USER_PLAY)
				continue;

			if (i == conn) continue;

			if (pMob[i].Mode == 0)
				continue;
		
					if (pUser[conn].Mac[0] == pUser[i].Mac[0])
					{
						if (pUser[conn].Mac[1] == pUser[i].Mac[1])
						{
							if (pUser[conn].Mac[2] == pUser[i].Mac[2])
							{
								if (pUser[conn].Mac[3] == pUser[i].Mac[3])
								{
									if (pUser[conn].TradeMode && pUser[i].TradeMode)
									{
										RemoveTrade(conn);
										SendClientMsg(conn, "Somente 1 conta por computador.");
										userCount++;
										continue;
									}

								}
							}
						}

					}
			
		}
	
	return userCount;
}

int GetUserInAreaMac(int notUsage, int x1, int y1, int x2, int y2)
{
	int userCount = 0;

	for (int conn = 1; conn < MAX_USER; conn++)
	{
		if (pUser[conn].Mode != USER_PLAY)
			continue;

		if (pMob[conn].Mode == 0)
			continue;

		for (int i = 1; i < MAX_USER; i++)
		{
			if (pUser[i].Mode != USER_PLAY)
				continue;

			if (i == conn) continue;

			if (pMob[i].Mode == 0)
				continue;

			if (pMob[conn].TargetX >= x1 && pMob[conn].TargetX <= x2 && pMob[conn].TargetY >= y1 && pMob[conn].TargetY <= y2)
			{
				if (pMob[i].TargetX >= x1 && pMob[i].TargetX <= x2 && pMob[i].TargetY >= y1 && pMob[i].TargetY <= y2)
				{
					if (pUser[conn].Mac[0] == pUser[i].Mac[0])
					{
						if (pUser[conn].Mac[1] == pUser[i].Mac[1])
						{
							if (pUser[conn].Mac[2] == pUser[i].Mac[2])
							{
								if (pUser[conn].Mac[3] == pUser[i].Mac[3])
								{
									DoRecall(i);

									SendClientMsg(i, "Somente 1 conta por computador.");
									userCount++;
									continue;
								}
							}
						}

					}

				}
			}
		}
	}
	return userCount;
}
int GetUserInAreaMac2(int notUsage, int x1, int y1)
{
	int userCount = 0;

	for (int conn = 1; conn < MAX_USER; conn++)
	{
		if (pUser[conn].Mode != USER_PLAY)
			continue;

		if (pMob[conn].Mode == 0)
			continue;

		for (int i = 1; i < MAX_USER; i++)
		{
			if (pUser[i].Mode != USER_PLAY)
				continue;

			if (i == conn) continue;

			if (pMob[i].Mode == 0)
				continue;

			if ((pMob[conn].TargetX / 128) == x1 || (pMob[conn].TargetY / 128) == y1)
			{
				if ((pMob[i].TargetX / 128) == x1 || (pMob[i].TargetY / 128) == y1)
				{
					if (pUser[conn].Mac[0] == pUser[i].Mac[0])
					{
						if (pUser[conn].Mac[1] == pUser[i].Mac[1])
						{
							if (pUser[conn].Mac[2] == pUser[i].Mac[2])
							{
								if (pUser[conn].Mac[3] == pUser[i].Mac[3])
								{
									DoRecall(i);

									SendClientMsg(i, "Somente 1 conta por computador.");
									userCount++;
									continue;
								}
							}
						}

					}

				}
			}
		}
	}
	return userCount;
}


void SaveAll()
{
	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode == USER_PLAY)
		{
			CharLogOut(i);
			Log("saveall", pUser[i].AccountName, pUser[i].IP);
		}
	}
}

void SetBigCuboDoor(int state)
{
	int gate = 0;

	int height = 0;

	for (int i = 0; i < 10; i++)
	{
		gate = i + 49;

		if (pItem[i + 49].ITEM.sIndex <= 0 || pItem[gate].ITEM.sIndex >= MAX_ITEMLIST)
			continue;

		if (pItem[gate].State == state)
			continue;

		UpdateItem(gate, state, &height);

		if (state == 1)
		{
			MSG_UpdateItem sm;
			memset(&sm, 0, sizeof(MSG_UpdateItem));

			sm.ID = ESCENE_FIELD;
			sm.Type = _MSG_UpdateItem;

			sm.ItemID = gate + 10000;

			sm.Size = sizeof(MSG_UpdateItem);

			//		sm.Height = height;
			sm.State = pItem[gate].State;

			GridMulticast(pItem[gate].PosX, pItem[gate].PosY, (MSG_STANDARD*)&sm, 0);
		}
		else
		{
			MSG_CreateItem sm;
			memset(&sm, 0, sizeof(MSG_CreateItem));

			GetCreateItem(gate, &sm);

			GridMulticast(pItem[gate].PosX, pItem[gate].PosY, (MSG_STANDARD*)&sm, 0);
		}

		pItem[gate].Delay = 0;
	}
}

int GetFirstSlotBag(int Conn)
{
	int SlotId = -1;

	for (int i = 0; i < pMob[Conn].MaxCarry; i++)
	{
		if (pMob[Conn].MOB.Carry[i].sIndex == 0)
		{
			SlotId = i;

			return TRUE;
		}
	}

	if (SlotId == -1)
		return FALSE;
	
}

int GetSlotsVagoBag(int Conn)
{

	int SlotCount = 0;

	for (int i = 0; i < pMob[Conn].MaxCarry; i++)
	{
		if (pMob[Conn].MOB.Carry[i].sIndex == 0)
			SlotCount++;
	}
		return SlotCount;
}

STRUCT_ITEM *GetFirstItemBag(int Conn, int idItem)
{
	STRUCT_ITEM *Item;
	//memset(Item, 0, sizeof(STRUCT_ITEM));
	for (int i = 0; i < pMob[Conn].MaxCarry; i++)
	{
		if (pMob[Conn].MOB.Carry[i].sIndex == idItem)
		{
			Item = &pMob[Conn].MOB.Carry[i];

			return Item;

			break;
		}
	}

	return nullptr;
}

int GetMountProtect(int conn)
{
	int sAffect = GetEmptyAffect(conn, MOUNT_PROTECT_TYPE);

	if (pMob[conn].Affect[sAffect].Type == MOUNT_PROTECT_TYPE)
		return TRUE;
	
	return FALSE;

}
