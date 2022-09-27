#include "ConfigIni.h"
#include <iostream>
#include <windows.h>
#include <windowsx.h>
#include <string>
#include <sstream>
#include <iomanip>
#include "Basedef.h"
#include "jsonlib/json.hpp"
#include "DBSrv/CFileDB.h"

using namespace std;
using ConfigIni::nConfig;
using json = nlohmann::json;
int AtivaTitleSystem = FALSE;
STRUCT_STAFF_ETERNAL StaffEternal;
STRUCT_MOB g_MobBase[];
STRUCT_TREASURE ng_pTreasure[];
STRUCT_EVENTS eEvents;
STRUCT_QUIZ eQuiz[];
STRUCT_ITEM premioLojaAfk;
int jsonSancRate[3][12];
STRUCT_ITEM dropKefra[];
STRUCT_WARS warsTimer[];
STRUCT_ITEM BoxEvent[][5];
STRUCT_ITEM sbagWarrior[];
STRUCT_aDOUBLE autoDouble;
STRUCT_aNOTICE autoNotice;
STRUCT_SOMBRA_NEGRA bSombraNegra;
STRUCT_STATUS_BOSS statusSombraNegra;
STRUCT_BOSS_CAMP bossCamp[];
STRUCT_STATUS_BOSS statusBossCamp[4];
int locationBossCamp[MAX_BOSS_CAMP][4][2];
STRUCT_EVENT_TRADE EventTrade;
STRUCT_COLISEU nColiseu[];
STRUCT_AUTOBAN autoBan;
STRUCT_FILTER FilterName;
STRUCT_TITLE_SYSTEM TitleLevel[tMaxTitle];
STRUCT_TITLE_SYSTEM TitleStatus[tMaxTitle];
STRUCT_TITLE_SYSTEM TitleUnic[tMaxTitle];
STRUCT_TITLE_PLAYER TitlePlayer;
STRUCT_EVENT_INVADE INVADE_ARMIA;
StatusServer EternalServer[];
unsigned int AccountSaveBuff[];
// Items que pode ser ganhado aleatoriamente por 1 hora de online
/*{ 412, 413, 4027 }*/
int g_pRewardBonus[];

/*GAME CONFIG-----------*/

//Config for Event
//////////////////////////////////////
int evNotice = 1;
int evStartIndex = 0;
int evEndIndex = 0;
int evCurrentIndex = 0;
int evRate = 0;
int evItem = 0;
int evIndex = 0;
int evOn = 0;
int evDelete = 0;
////////////////////////////////////

int DOUBLEMODE = 0;
int DUNGEONEVENT = 1;
int DEADPOINT = 1;
int StatSapphire = 30;
int BRItem = 413;
int BRHour = 19;

int BILLING = 3;
int CHARSELBILL = 0;
int POTIONCOUNT = 10;
int PARTYBONUS = 100;
int GUILDBOARD = 0;

int GTorreHour = 21;
int isDropItem = 0;
int maxNightmare = 3;
int PotionDelay = 500;

int KefraLive = 0;

int FREEEXP = 35;
int PARTY_DIF = 200;
/*-----------GAME CONFIG*/
int NPCBlock[];
int TOTAL_QUIZ;
int goldQuiz;
long int expQuiz;
int QuizOn;
int SortQuiz;
int groupItens[];
int fadaAmmount[];
STRUCT_ALTAR_KING altarKing;
BOOL StartAltarKing = FALSE;
STRUCT_MOB exportNPCJson;
unsigned int ipAdmin[];
unsigned int CharaCreate[];
 DWORD MAX_BOX_N = 0;
 DWORD MAX_BOX_M = 0;
 DWORD MAX_BOX_A = 0;
//Maximo de config 100 maximo de subconfig 50
short gameConfig[maxGameConfig][MaxSubConfig];
unsigned int GuildLevel[MAX_GUILD_LEVEL];
STRUCT_GUILD_HALL GuildHall[MAX_GUILD];
STRUCT_TERRITORY Territory[MAX_TERRITORY];
//PATH Folders, difinir extern no basedef.h
const string PATH_COMMON = "../../Common/";
const string PATH_DB = "../../DBSrv/";
const string PATH_DBSqlite = "DB/";
const string PATH_DBEternal = PATH_DBSqlite + "Eternal.db";
const string PATH_TM = "../../TMSrv/";
const string PATH_CONFIG = "Config/";
const string PATH_SETTINGS = PATH_COMMON + "Settings/";
const string PATH_EVENTS = PATH_COMMON + "Events/";
const string PATH_EVENT_VemProEternal = PATH_EVENTS + "VemProEternal/";
const string PATH_EVENT_LojaAfk = PATH_EVENTS + "LojaAfk/";
const string PATH_EVENT_Lottery = PATH_EVENTS + "Lottery/";
const string PATH_EVENT_AltarOfKing = PATH_EVENTS + "AltarOfKing/";
const string PATH_EVENT_Box = PATH_EVENTS + "Box/";
const string PATH_EVENT_Trade = PATH_EVENTS + "NPCTrade/";
const string PATH_NewNPC = "NewNPC/";
const string PATH_NewBoss = "NewBoss/";
const string PATH_SOMBRA_NEGRA = PATH_NewBoss + "SombraNegra/";
const string PATH_BOSS_CAMP = PATH_NewBoss + "Camp/";
const string PATH_BAN = "Ban/";
const string PATH_AUTO_BAN = PATH_BAN + "AutoBan/";
const string PATH_FILTER_NAME = "FilterName/";
const string PATH_ADM = "Staff/";
const string PATH_SITE = "C:/xampp/htdocs/wyd/Eternal_Site/";
const string PATH_SAVEBUFF = "SaveBuff/";
const string PATH_TITLE_SYSTEM = "TitleSystem/";
const string PATH_GUILD_HALL = PATH_COMMON + "GuildHall/";
const string PATH_TERRITORY = PATH_GUILD_HALL + "Territory/";
const string PATH_INVADE = PATH_EVENTS + "Invade/";
//Files Json, definir extern no basedef.h
const string ConfigJson = "config.json";
const string GameConfig = "gameConfig.json";
const string Serv00 = PATH_SITE + "serv00.htm";

enum  keyName : char
{
	CONFIG,
	SERVERLIST,
	ADMIN
};
/*
enum eGameConfig 
{
	DROP_ITEM_EVENT,
	ETC_EVENT,
	BILLING,
	ITEM_DROP_BONUS,
	TREASURE,
	ETC
};*/

void nConfig::findAndReplaceAll(std::string& data, std::string& match, const std::string& replace)
{
	// pega a primeira ocorrência
	size_t pos = data.find(match);

	// Repete até o fim
	while (pos != std::string::npos)
	{
		data.replace(pos, match.size(), replace);

		// pega a próxima ocorrência da posição atual
		pos = data.find(match, pos + replace.size());
	}
}

int nConfig::ReadEventsEternal(string path, string file, int key)
{
	string fullpath = path + file;
	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	if (fp == NULL) {

		// não encontrado, será criado um novo(default) no diretorio
		int creat = WriteEventsEternal(PATH_EVENT_VemProEternal, file, key, 0);

		if (!creat)
			return creat;
	}

	try
	{
		ifstream spath(fullpath);
		json nJson;
		spath >> nJson;

		switch (key)
		{
		case VemProEternal:
			//eEvents.name = (char*)file.c_str();
			nJson["EVENTSETERNAL"]["VemProEternal"].get_to(eEvents.eventValue);
			break;
		default:
			break;
		}

		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}

}

int nConfig::WriteEventsEternal(string path, string file, int key, int nValue)
{

	string fullpath = path + file;

#pragma region Txt New playerEvent.json
	auto nJson = R"(
{
"EVENTSETERNAL": {
					"VemProEternal": 0

				 }
	
})"_json;

#pragma endregion

	
	switch (key)
		{
		case VemProEternal:
			nJson["EVENTSETERNAL"]["VemProEternal"] = nValue;
			break;
		case 99:
			break;
		default:
			break;
		}

	try
	{
		ofstream bjson(fullpath);
		bjson << setw(4) << nJson << std::endl;
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::ReadQuiz(string path, string file)
{
	string fullpath = path + file;
	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	if (fp == NULL) {

		// não encontrado, será criado um novo(default) no diretorio
		int creat = WriteQuiz(PATH_SETTINGS, file);

		if (!creat)
			return creat;
	}

	try
	{
		ifstream spath(fullpath);
		json nJson;
		spath >> nJson;

		nJson["CONFIG"]["ToTalQuiz"].get_to(TOTAL_QUIZ);
		nJson["CONFIG"]["GOLD"].get_to(goldQuiz);
		nJson["CONFIG"]["EXP"].get_to(expQuiz);

		for (auto& x : nJson["QUESTIONS"].items())
		{
			string Title = x.value().find("Title").value();
			int tLength = Title.size();
			int Correct = x.value().find("Correct").value();
			string Answer0 = x.value().find("Answer0").value();
			int tA0 = Answer0.size();
			string Answer1 = x.value().find("Answer1").value();
			int tA1 = Answer1.size();
			string Answer2 = x.value().find("Answer2").value();
			int tA2 = Answer2.size();
			string Answer3 = x.value().find("Answer3").value();
			int tA3 = Answer3.size();

			char* cTitle = new char[tLength + 1];
			copy(Title.begin(), Title.end(), cTitle);
			cTitle[tLength] = '\0';
			eQuiz[stoi(x.key())].Title = cTitle;

			eQuiz[stoi(x.key())].Correct = Correct;

			char* cA0 = new char[tA0 + 1];
			copy(Answer0.begin(), Answer0.end(), cA0);
			cA0[tA0] = '\0';
			eQuiz[stoi(x.key())].Answer0 = cA0;

			char* cA1 = new char[tA1 + 1];
			copy(Answer1.begin(), Answer1.end(), cA1);
			cA1[tA1] = '\0';
			eQuiz[stoi(x.key())].Answer1 = cA1;

			char* cA2 = new char[tA2 + 1];
			copy(Answer2.begin(), Answer2.end(), cA2);
			cA2[tA2] = '\0';
			eQuiz[stoi(x.key())].Answer2 = cA2;

			char* cA3 = new char[tA3 + 1];
			copy(Answer3.begin(), Answer3.end(), cA3);
			cA3[tA3] = '\0';
			eQuiz[stoi(x.key())].Answer3 = cA3;

		};
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
	
}

int ConfigIni::nConfig::WriteQuiz(string path, string file)
{
	string fullpath = path + file;

#pragma region Txt New quiz.json
	auto nJson = R"(
{
"CONFIG": {
			"GOLD": 10000,
			"EXP": 100000,
			"ToTalQuiz": 3
		  },
"QUESTIONS": [
				{
					"Title": "Qual classe evoca monstros?",
					"Correct": 1,
					"Answer0": "Foema",
					"Answer1": "BeastMaster",
					"Answer2": "Transknight",
					"Answer3": "Huntress"
				},
				{
					"Title": "Em qual cidade fica a Zona Elemental da Agua?",
					"Correct": 0,
					"Answer0": "Arzam",
					"Answer1": "Armia",
					"Answer2": "Erion",
					"Answer3": "Noatum"
				},
				{
					"Title": "Qual o nome do Servidor?",
					"Correct": 3,
					"Answer0": "Eternity",
					"Answer1": "7DY",
					"Answer2": "WYD",
					"Answer3": "ETERNAL"
				}
			]
	
	
})"_json;

#pragma endregion

	try
	{
		ofstream bjson(fullpath);
		bjson << setw(4) << nJson << std::endl;
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::ReadSancRate(string path, string file)
{
	string fullpath = path + file;
	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	if (fp == NULL) {

		// não encontrado, será criado um novo(default) no diretorio
		int creat = WriteSancRate(PATH_SETTINGS, file);

		if (!creat)
			return creat;
	}

	try
	{
		ifstream spath(fullpath);
		json nJson;
		spath >> nJson;

		for (auto& x : nJson["SANC"]["ORI"].items())
		{
			x.value().get_to(jsonSancRate[0][stoi(x.key())]);
		}

		for (auto& x : nJson["SANC"]["LAC"].items())
		{
			x.value().get_to(jsonSancRate[1][stoi(x.key())]);
		}

		for (auto& x : nJson["SANC"]["AMAGO"].items())
		{
			x.value().get_to(jsonSancRate[2][stoi(x.key())]);
		}

		memmove(g_pSancRate, jsonSancRate, sizeof(g_pSancRate));

		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::WriteSancRate(string path, string file)
{
	string fullpath = path + file;

#pragma region Txt New sancRate.json
	auto nJson = R"(
{
"SANC": {
		"ORI": {
				"0":100,
				"1":100,
				"2":100,
				"3":85,
				"4":70,
				"5":50,
				"6":00,
				"7":00,
				"8":00,
				"9":00,
				"10":00,
				"11":00
				},
		"LAC": {
				"0":100,
				"1":100,
				"2":100,
				"3":100,
				"4":100,
				"5":100,
				"6":70,
				"7":60,
				"8":30,
				"9":10,
				"10":00,
				"11":00
				},
				
		"AMAGO": {
				"0":100,
				"1":100,
				"2":100,
				"3":100,
				"4":100,
				"5":100,
				"6":70,
				"7":60,
				"8":30,
				"9":10,
				"10":10,
				"11":05
				}

		}

})"_json;

#pragma endregion

	try
	{
		ofstream bjson(fullpath);
		bjson << setw(4) << nJson << std::endl;
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::ReadPremioLojaAfk(string path, string file)
{
	string fullpath = path + file;
	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	memset(&premioLojaAfk, 0, sizeof(STRUCT_ITEM));

	if (fp == NULL) {
		
		premioLojaAfk.sIndex = 475;
		return FALSE;
	}

	try
	{
		ifstream spath(fullpath);
		json nJson;
		spath >> nJson;
		vector<short> itemPremio;
		nJson["SHOP"]["Item"].get_to(itemPremio);

		premioLojaAfk.sIndex = itemPremio[0];
		premioLojaAfk.stEffect->sValue = itemPremio[1];
		premioLojaAfk.stEffect[0].cEffect = itemPremio[2];
		premioLojaAfk.stEffect[0].cValue = itemPremio[3];
		premioLojaAfk.stEffect[1].cEffect = itemPremio[4];
		premioLojaAfk.stEffect[1].cValue = itemPremio[5];
		premioLojaAfk.stEffect[2].cEffect = itemPremio[6];
		premioLojaAfk.stEffect[2].cValue = itemPremio[7];

		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::ReadGroupItens(string path, string file)
{
	string fullpath = path + file;
	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	if (fp == NULL) {

		// não encontrado, será criado um novo(default) no diretorio
		int creat = WriteGrupItens(PATH_SETTINGS, file);

		if (!creat)
			return creat;
	}

	try
	{
		ifstream spath(fullpath);
		json nJson;
		spath >> nJson;
		memset(&groupItens, 0, sizeof(groupItens));
		for (auto& x : nJson["GROUP"].items())
		{
			x.value().get_to(groupItens[stoi(x.key())]);
		}
		
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::WriteGrupItens(string path, string file)
{
	string fullpath = path + file;

#pragma region Txt New groupItens.json
	auto nJson = R"(
{
"GROUP":{
	
			"0": 412,
			"1": 413,
			"2": 419,
			"3": 420,
			"4": 2390,
			"5": 2391,
			"6": 2392,
			"7": 2393,
			"8": 2394,
			"9": 2395,
			"10": 2396,
			"11": 2397,
			"12": 2398,
			"13": 2399,
			"14": 2400,
			"15": 2401,
			"16": 2402,
			"17": 2403,
			"18": 2404,
			"19": 2405,
			"20": 2406,
			"21": 2407,
			"22": 2408,
			"23": 2409,
			"24": 2410,
			"25": 2411,
			"26": 2412,
			"27": 2413,
			"28": 2414,
			"29": 2415,
			"30": 2416,
			"31": 2417,
			"32": 2418,
			"33": 2419,
			"34": 4016,
			"35": 4017,
			"36": 4018,
			"37": 4019,
			"38": 4020,
			"39": 4021,
			"40": 4022,
			"41": 4023,
			"42": 4024,
			"43": 4025,
			"44": 4038,
			"45": 4039,
			"46": 4040,
			"47": 4041,
			"48": 4042
				
        }


})"_json;

#pragma endregion

	try
	{
		ofstream bjson(fullpath);
		bjson << setw(4) << nJson << std::endl;
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::ReadFadaAmmount(string path, string file)
{
	string fullpath = path + file;
	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	if (fp == NULL) {

		// não encontrado, será criado um novo(default) no diretorio
		int creat = WriteFadaAmmount(PATH_SETTINGS, file);

		if (!creat)
			return creat;
	}

	try
	{
		ifstream spath(fullpath);
		json nJson;
		spath >> nJson;
		memset(&fadaAmmount, 0, sizeof(fadaAmmount));
		for (auto& x : nJson["GROUP"].items())
		{
			x.value().get_to(fadaAmmount[stoi(x.key())]);
		}

		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::WriteFadaAmmount(string path, string file)
{
	string fullpath = path + file;

#pragma region Txt New fadaAmmount.json
	auto nJson = R"(
{
"GROUP":{
	
			"0": 412,
			"1": 413
				
        }


})"_json;

#pragma endregion

	try
	{
		ofstream bjson(fullpath);
		bjson << setw(4) << nJson << std::endl;
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::ReadNPCBlock(string path, string file)
{
	string fullpath = path + file;
	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	if (fp == NULL) {

		// não encontrado, será criado um novo(default) no diretorio
		int creat = WriteNPCBlock(PATH_SETTINGS, file);

		if (!creat)
			return creat;
	}

	try
	{
		ifstream spath(fullpath);
		json nJson;
		spath >> nJson;
		memset(&NPCBlock, 0, sizeof(eNPCBlock));

		nJson["NPC"]["Uxmall"].get_to(NPCBlock[Uxmall]);
		nJson["NPC"]["Odin"].get_to(NPCBlock[Odin]);
		nJson["NPC"]["BlackOrackle"].get_to(NPCBlock[BlackOrackle]);
		nJson["NPC"]["Xama"].get_to(NPCBlock[Xama]);
		nJson["NPC"]["Shama"].get_to(NPCBlock[Shama]);
		nJson["NPC"]["Jeffi"].get_to(NPCBlock[Jeffi]);
		nJson["NPC"]["Perzens"].get_to(NPCBlock[Perzens]);
		nJson["NPC"]["MestreHaby"].get_to(NPCBlock[MestreHaby]);
		nJson["NPC"]["Kibita"].get_to(NPCBlock[Kibita]);
		nJson["NPC"]["Urnammu"].get_to(NPCBlock[Urnammu]);

		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::WriteNPCBlock(string path, string file)
{
	string fullpath = path + file;

#pragma region Txt New groupItens.json
	auto nJson = R"(
{
"NPC":{
		"Uxmall": 0,
		"Odin": 1,
		"BlackOrackle": 1,
		"Xamã": 1,
		"Shama": 1,
		"Jeffi": 1,
		"Perzens": 1,
		"MestreHaby": 1,
		"Kibita": 1,
		"Urnammu": 0
		
	  }

})"_json;

#pragma endregion

	try
	{
		ofstream bjson(fullpath);
		bjson << setw(4) << nJson << std::endl;
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::ReadLottery(string path, string file)
{
	string fullpath = path + file;
	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	if (fp == NULL) {

		// não encontrado, será criado um novo(default) no diretorio
		int creat = WriteLottery(PATH_EVENT_Lottery, file);

		if (!creat)
			return creat;
	}

	try
	{
		ifstream spath(fullpath);
		json nJson;
		spath >> nJson;
		memset(&g_pRewardBonus, 0, sizeof(g_pRewardBonus));
		for (auto& x : nJson["REWARD"].items())
		{
			x.value().get_to(g_pRewardBonus[stoi(x.key())]);
		}

		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::WriteLottery(string path, string file)
{
	string fullpath = path + file;

#pragma region Txt New lottery.json
	auto nJson = R"(
{
"REWARD":{
	
			"0": 412,
			"1": 413,
			"2": 418,
			"3": 419,
			"4": 418,
			"5": 419,
			"6": 4026,
			"7": 4026,
			"8": 4026,
			"9": 4027
				
        }


})"_json;

#pragma endregion

	try
	{
		ofstream bjson(fullpath);
		bjson << setw(4) << nJson << std::endl;
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::ReadDropKefra(string path, string file)
{
	string fullpath = path + file;
	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	if (fp == NULL) {

		// não encontrado, será criado um novo(default) no diretorio
		int creat = WriteDropKefra(PATH_SETTINGS, file);

		if (!creat)
			return creat;
	}

	try
	{
		ifstream spath(fullpath);
		json nJson;
		spath >> nJson;

		memset(dropKefra, 0, sizeof(STRUCT_ITEM));

		for (auto& x : nJson["DROP"]["Itens"].items())
		{

			vector<short> nDropKefra = x.value();
			dropKefra[stoi(x.key())].sIndex = nDropKefra[0];
			dropKefra[stoi(x.key())].stEffect->sValue = nDropKefra[1];
			dropKefra[stoi(x.key())].stEffect[0].cEffect = nDropKefra[2];
			dropKefra[stoi(x.key())].stEffect[0].cValue = nDropKefra[3];
			dropKefra[stoi(x.key())].stEffect[1].cEffect = nDropKefra[4];
			dropKefra[stoi(x.key())].stEffect[1].cValue = nDropKefra[5];
			dropKefra[stoi(x.key())].stEffect[2].cEffect = nDropKefra[6];
			dropKefra[stoi(x.key())].stEffect[2].cValue = nDropKefra[7];

		};

		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
	
}

int ConfigIni::nConfig::WriteDropKefra(string path, string file)
{
	string fullpath = path + file;

#pragma region Txt New dropKefra.json
	auto nJson = R"(
{
"DROP": {
		"Itens": {
				"0": [0,0,0,0,0,0,0,0],
				"1": [0,0,0,0,0,0,0,0],
				"2": [0,0,0,0,0,0,0,0],
				"3": [0,0,0,0,0,0,0,0],
				"4": [0,0,0,0,0,0,0,0],
				"5": [0,0,0,0,0,0,0,0],
				"6": [0,0,0,0,0,0,0,0],
				"7": [0,0,0,0,0,0,0,0],
				"8": [0,0,0,0,0,0,0,0],
				"9": [0,0,0,0,0,0,0,0]
				
				}
		}
})"_json;

#pragma endregion

	try
	{
		ofstream bjson(fullpath);
		bjson << setw(4) << nJson << std::endl;
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::ReadWarsTimer(string path, string file)
{
	string fullpath = path + file;
	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	if (fp == NULL) {

		// não encontrado, será criado um novo(default) no diretorio
		int creat = WriteWarsTimer(PATH_SETTINGS, file);

		if (!creat)
			return creat;
	}

	try
	{
		ifstream spath(fullpath);
		json nJson;
		spath >> nJson;

		memset(warsTimer, 0, sizeof(STRUCT_WARS));
		//Tower
		nJson["WAR"]["Tower"].find("Days").value().get_to(warsTimer[eTower].Days);
		nJson["WAR"]["Tower"].find("Hour").value().get_to(warsTimer[eTower].Hour);
		nJson["WAR"]["Tower"].find("Minute").value().get_to(warsTimer[eTower].Minute);
		nJson["WAR"]["Tower"].find("Notice").value().get_to(warsTimer[eTower].Notice);
		//Noatum
		nJson["WAR"]["Noatum"].find("Days").value().get_to(warsTimer[eNoatum].Days);
		nJson["WAR"]["Noatum"].find("Hour").value().get_to(warsTimer[eNoatum].Hour);
		nJson["WAR"]["Noatum"].find("Minute").value().get_to(warsTimer[eNoatum].Minute);
		nJson["WAR"]["Tower"].find("Notice").value().get_to(warsTimer[eNoatum].Notice);
		//City
		nJson["WAR"]["City"].find("Days").value().get_to(warsTimer[eCity].Days);
		nJson["WAR"]["City"].find("Hour").value().get_to(warsTimer[eCity].Hour);
		nJson["WAR"]["City"].find("Minute").value().get_to(warsTimer[eCity].Minute);
		nJson["WAR"]["Tower"].find("Notice").value().get_to(warsTimer[eCity].Notice);
		//RvR
		nJson["WAR"]["RvR"].find("Days").value().get_to(warsTimer[eRvR].Days);
		nJson["WAR"]["RvR"].find("Hour").value().get_to(warsTimer[eRvR].Hour);
		nJson["WAR"]["RvR"].find("Minute").value().get_to(warsTimer[eRvR].Minute);
		nJson["WAR"]["Tower"].find("Notice").value().get_to(warsTimer[eRvR].Notice);

		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::WriteWarsTimer(string path, string file)
{
	string fullpath = path + file;

#pragma region Txt New warsTimer.json
	auto nJson = R"(
{

"WAR": {
		"Tower": {
				"Days": [0,1,1,1,1,0,0],
				"Hour": 19,
				"Minute": 0
		
				},
		"Noatum": {
				"Days": [1,0,0,0,0,0,0],
				"Hour": 19,
				"Minute": 0
		
				},
				
		"City": {
				"Days": [0,0,0,0,0,0,1],
				"Hour": 21,
				"Minute": 0
				},
				
		"RvR": {
				"Days": [0,0,0,0,0,1,0],
				"Hour": 21,
				"Minute": 0
				}

	   }
	
})"_json;

#pragma endregion

	try
	{
		ofstream bjson(fullpath);
		bjson << setw(4) << nJson << std::endl;
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::ReadBoxEvent(string path, string file)
{
	string fullpath = path + file;
	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	if (fp == NULL) {

		// não encontrado, será criado um novo(default) no diretorio
		int creat = WriteBoxEvent(PATH_EVENT_Box, file);

		if (!creat)
			return creat;
	}

	try
	{
		ifstream spath(fullpath);
		json nJson;
		spath >> nJson;

		memset(BoxEvent, 0, sizeof(STRUCT_ITEM));

		nJson["EVENTS"]["MAX_N"].get_to(MAX_BOX_N);
		nJson["EVENTS"]["MAX_M"].get_to(MAX_BOX_M);
		nJson["EVENTS"]["MAX_A"].get_to(MAX_BOX_A);

		for (auto& x : nJson["EVENTS"]["N"].items())
		{
			vector<short> nBoxEvent = x.value();
			BoxEvent[0][stoi(x.key())].sIndex = nBoxEvent[0];
			BoxEvent[0][stoi(x.key())].stEffect->sValue = nBoxEvent[1];
			BoxEvent[0][stoi(x.key())].stEffect[0].cEffect = nBoxEvent[2];
			BoxEvent[0][stoi(x.key())].stEffect[0].cValue = nBoxEvent[3];
			BoxEvent[0][stoi(x.key())].stEffect[1].cEffect = nBoxEvent[4];
			BoxEvent[0][stoi(x.key())].stEffect[1].cValue = nBoxEvent[5];
			BoxEvent[0][stoi(x.key())].stEffect[2].cEffect = nBoxEvent[6];
			BoxEvent[0][stoi(x.key())].stEffect[2].cValue = nBoxEvent[7];
		};

		for (auto& x : nJson["EVENTS"]["M"].items())
		{
			vector<short> nBoxEvent = x.value();
			BoxEvent[1][stoi(x.key())].sIndex = nBoxEvent[0];
			BoxEvent[1][stoi(x.key())].stEffect->sValue = nBoxEvent[1];
			BoxEvent[1][stoi(x.key())].stEffect[0].cEffect = nBoxEvent[2];
			BoxEvent[1][stoi(x.key())].stEffect[0].cValue = nBoxEvent[3];
			BoxEvent[1][stoi(x.key())].stEffect[1].cEffect = nBoxEvent[4];
			BoxEvent[1][stoi(x.key())].stEffect[1].cValue = nBoxEvent[5];
			BoxEvent[1][stoi(x.key())].stEffect[2].cEffect = nBoxEvent[6];
			BoxEvent[1][stoi(x.key())].stEffect[2].cValue = nBoxEvent[7];
		};

		for (auto& x : nJson["EVENTS"]["A"].items())
		{
			vector<short> nBoxEvent = x.value();
			BoxEvent[2][stoi(x.key())].sIndex = nBoxEvent[0];
			BoxEvent[2][stoi(x.key())].stEffect->sValue = nBoxEvent[1];
			BoxEvent[2][stoi(x.key())].stEffect[0].cEffect = nBoxEvent[2];
			BoxEvent[2][stoi(x.key())].stEffect[0].cValue = nBoxEvent[3];
			BoxEvent[2][stoi(x.key())].stEffect[1].cEffect = nBoxEvent[4];
			BoxEvent[2][stoi(x.key())].stEffect[1].cValue = nBoxEvent[5];
			BoxEvent[2][stoi(x.key())].stEffect[2].cEffect = nBoxEvent[6];
			BoxEvent[2][stoi(x.key())].stEffect[2].cValue = nBoxEvent[7];
		};

		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::WriteBoxEvent(string path, string file)
{
	string fullpath = path + file;

#pragma region Txt New boxEvent.json
	auto nJson = R"(
{
"EVENTS": {
		"MAX_N": 4,
		"MAX_M": 4,
		"MAX_A": 3,
		"N": {
			  "0": [2396,0,61,5,0,0,0,0],
			  "1": [2397,0,61,5,0,0,0,0],
			  "2": [2401,0,61,5,0,0,0,0],
			  "3": [2402,0,61,5,0,0,0,0]
			 },
		"M": {
			  "0": [2399,0,61,5,0,0,0,0],
			  "1": [2400,0,61,5,0,0,0,0],
			  "2": [2404,0,61,5,0,0,0,0],
			  "3": [2405,0,61,5,0,0,0,0]
			 },
		"A": {
			  "0": [2411,0,61,3,0,0,0,0],
			  "1": [2412,0,61,3,0,0,0,0],
			  "2": [2413,0,61,3,0,0,0,0]
			 }

		  }

})"_json;

#pragma endregion

	try
	{
		ofstream bjson(fullpath);
		bjson << setw(4) << nJson << std::endl;
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::ReadAltarOfKing(string path, string file)
{
	string fullpath = path + file;
	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	if (fp == NULL) {

		// não encontrado, será criado um novo(default) no diretorio
		int creat = WriteAltarOfKing(PATH_EVENT_AltarOfKing, file);

		if (!creat)
			return creat;
	}
	try
	{
		ifstream spath(fullpath);
		json nJson;
		spath >> nJson;

		memset(&altarKing.BossStatus.FACE, 0, sizeof(STRUCT_ITEM));
		nJson["INDEX"]["Timer"].find("Days").value().get_to(altarKing.Days);
		nJson["INDEX"]["Timer"].find("Hour").value().get_to(altarKing.Hour);
		nJson["INDEX"]["Timer"].find("Minute").value().get_to(altarKing.Min);
		nJson["INDEX"]["Timer"].find("Notice").value().get_to(altarKing.Notice);

		for (auto& x : nJson["INDEX"]["Reward"].items())
		{
			vector<short> nReward = x.value();
			altarKing.Rewards[stoi(x.key())].sIndex = nReward[0];
			altarKing.Rewards[stoi(x.key())].stEffect->sValue = nReward[1];
			altarKing.Rewards[stoi(x.key())].stEffect[0].cEffect = nReward[2];
			altarKing.Rewards[stoi(x.key())].stEffect[0].cValue = nReward[3];
			altarKing.Rewards[stoi(x.key())].stEffect[1].cEffect = nReward[4];
			altarKing.Rewards[stoi(x.key())].stEffect[1].cValue = nReward[5];
			altarKing.Rewards[stoi(x.key())].stEffect[2].cEffect = nReward[6];
			altarKing.Rewards[stoi(x.key())].stEffect[2].cValue = nReward[7];
		};

		nJson["INDEX"]["Boss"].find("ID").value().get_to(altarKing.BossStatus.ID);
		//string nName;
		nJson["INDEX"]["Boss"].find("NAME").value().get_to(altarKing.BossStatus.NAME);
		//altarKing.BossStatus.NAME = nName.c_str();
		vector<short> nface;
		nJson["INDEX"]["Boss"].find("FACE").value().get_to(nface);
		altarKing.BossStatus.FACE.sIndex = nface[0];
		altarKing.BossStatus.FACE.stEffect->sValue = nface[1];
		altarKing.BossStatus.FACE.stEffect[0].cEffect = nface[2];
		altarKing.BossStatus.FACE.stEffect[0].cValue = nface[3];
		altarKing.BossStatus.FACE.stEffect[1].cEffect = nface[4];
		altarKing.BossStatus.FACE.stEffect[1].cValue = nface[5];
		altarKing.BossStatus.FACE.stEffect[2].cEffect = nface[6];
		altarKing.BossStatus.FACE.stEffect[2].cValue = nface[7];

		nJson["INDEX"]["Boss"].find("LEVEL").value().get_to(altarKing.BossStatus.LEVEL);
		nJson["INDEX"]["Boss"].find("HP").value().get_to(altarKing.BossStatus.HP);
		nJson["INDEX"]["Boss"].find("CON").value().get_to(altarKing.BossStatus.CON);
		nJson["INDEX"]["Boss"].find("MP").value().get_to(altarKing.BossStatus.MP);
		nJson["INDEX"]["Boss"].find("AC").value().get_to(altarKing.BossStatus.AC);
		nJson["INDEX"]["Boss"].find("DAN").value().get_to(altarKing.BossStatus.DAN);
		nJson["INDEX"]["Boss"].find("MAGIC").value().get_to(altarKing.BossStatus.MAGI);
		nJson["INDEX"]["Boss"].find("MSG1").value().get_to(altarKing.BossStatus.MSG1);
		nJson["INDEX"]["Boss"].find("MSG2").value().get_to(altarKing.BossStatus.MSG2);
		nJson["INDEX"]["Boss"].find("MSG3").value().get_to(altarKing.BossStatus.MSG3);

		nJson["INDEX"]["Counter"].find("StartX").value().get_to(altarKing.spotMSG.StartX);
		nJson["INDEX"]["Counter"].find("StartY").value().get_to(altarKing.spotMSG.StartY);
		nJson["INDEX"]["Counter"].find("DestX").value().get_to(altarKing.spotMSG.DestX);
		nJson["INDEX"]["Counter"].find("DestY").value().get_to(altarKing.spotMSG.DestY);

		nJson["INDEX"]["TimerAltar"].get_to(altarKing.TimerAltar);
		nJson["INDEX"]["Duration"].get_to(altarKing.Duration);


		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
	

	
}

int ConfigIni::nConfig::WriteAltarOfKing(string path, string file)
{
	string fullpath = path + file;

#pragma region Txt New AltarOfKing.json
	auto nJson = R"(
{
"INDEX": {
	     "Timer": {
						"Days": [1,1,1,1,1,1,1],
						"Hour": [12,16,3],
						"Minute": [30,16,5],
						"Notice": 0

		           },
						
		"Reward": {
		
					"0": [413,0,61,5,0,0,0,0],
					"1": [4028,0,0,0,0,0,0,0],
					"2": [4140,0,0,0,0,0,0,0],
					"3": [3314,0,0,0,0,0,0,0],
					"4": [777,0,61,5,0,0,0,0]
		
				  },
				  
		"Boss":{
				"ID": 4630,
				"NAME": "Altar Guardian",
				"FACE": [174,0,0,0,0,0,0,0],
				"LEVEL": 100,
				"HP": 10000,
				"CON": 5000,
				"MP": 10000,
				"AC": 5000,
				"DAN": 1000,
				"MAGIC": 1000,
				"MSG1": "Haa.haaa.Saiam do Altar humanos....",
				"MSG2": "Haa.haaa.Sou o guardiao do altar....",
				"MSG3": "graaaa.Vou matar todos voces...."
			   },
			   
		"Counter": {
					"StartX": 1065,
					"StartY": 1714,
					"DestX": 1128,
					"DestY": 1742
		
				   },
		"TimerAltar": 60,
		"Duration": 1800
		 
		  }
})"_json;

#pragma endregion

	try
	{
		ofstream bjson(fullpath);
		bjson << setw(4) << nJson << std::endl;
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::ReadBagWarrior(string path, string file)
{
	string fullpath = path + file;
	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	if (fp == NULL) {

		// não encontrado, será criado um novo(default) no diretorio
		int creat = WriteBagWarrior(PATH_SETTINGS, file);

		if (!creat)
			return creat;
	}

	try
	{
		ifstream spath(fullpath);
		json nJson;
		spath >> nJson;

		memset(sbagWarrior, 0, sizeof(STRUCT_ITEM));

		for (auto& x : nJson["ITENS"]["Reward"].items())
		{

			vector<short> nbagWarrior = x.value();
			sbagWarrior[stoi(x.key())].sIndex = nbagWarrior[0];
			sbagWarrior[stoi(x.key())].stEffect->sValue = nbagWarrior[1];
			sbagWarrior[stoi(x.key())].stEffect[0].cEffect = nbagWarrior[2];
			sbagWarrior[stoi(x.key())].stEffect[0].cValue = nbagWarrior[3];
			sbagWarrior[stoi(x.key())].stEffect[1].cEffect = nbagWarrior[4];
			sbagWarrior[stoi(x.key())].stEffect[1].cValue = nbagWarrior[5];
			sbagWarrior[stoi(x.key())].stEffect[2].cEffect = nbagWarrior[6];
			sbagWarrior[stoi(x.key())].stEffect[2].cValue = nbagWarrior[7];

		};
		//int vect = sizeof(sbagWarrior) / sizeof(sbagWarrior[0]);
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::WriteBagWarrior(string path, string file)
{
	string fullpath = path + file;

#pragma region Txt New bagWarrior.json
	auto nJson = R"(
{
"ITENS": {
		"Reward": {
					"0": [3381,0,0,0,0,0,0,0],
					"1": [3363,0,0,0,0,0,0,0],
					"2": [3467,0,0,0,0,0,0,0],
					"3": [3378,0,0,0,0,0,0,0],
					"4": [3366,0,0,0,0,0,0,0],
					"5": [3467,0,0,0,0,0,0,0]
				  }
		 }
})"_json;

#pragma endregion

	try
	{
		ofstream bjson(fullpath);
		bjson << setw(4) << nJson << std::endl;
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::ReadAutoEvent(string path, string file)
{
	string fullpath = path + file;
	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	if (fp == NULL) {

		// não encontrado, será criado um novo(default) no diretorio
		int creat = WriteAltarOfKing(PATH_EVENT_AltarOfKing, file);

		if (!creat)
			return creat;
	}
	try
	{
		ifstream spath(fullpath);
		json nJson;
		spath >> nJson;

		memset(&autoDouble, 0, sizeof(STRUCT_aDOUBLE));
		memset(&autoNotice, 0, sizeof(STRUCT_aNOTICE));
		nJson["EVENT"]["DOUBLE"].find("DayStart").value().get_to(autoDouble.DayStart);
		nJson["EVENT"]["DOUBLE"].find("HourStart").value().get_to(autoDouble.HourStart);
		nJson["EVENT"]["DOUBLE"].find("MinStart").value().get_to(autoDouble.MinStart);
		nJson["EVENT"]["DOUBLE"].find("MSGStart").value().get_to(autoDouble.MSGStart);
		nJson["EVENT"]["DOUBLE"].find("DayEnd").value().get_to(autoDouble.DayEnd);
		nJson["EVENT"]["DOUBLE"].find("HourEnd").value().get_to(autoDouble.HourEnd);
		nJson["EVENT"]["DOUBLE"].find("MinEnd").value().get_to(autoDouble.MinEnd);
		nJson["EVENT"]["DOUBLE"].find("MultEXP").value().get_to(autoDouble.MultEXP);
		nJson["EVENT"]["DOUBLE"].find("MSGEnd").value().get_to(autoDouble.MSGEnd);
		
		nJson["EVENT"]["NOTICE"].find("MaxNotice").value().get_to(autoNotice.MaxNotice);
	
		nJson["EVENT"]["NOTICE"].find("Days").value().get_to(autoNotice.Days);
		nJson["EVENT"]["NOTICE"].find("Hours").value().get_to(autoNotice.Hours);
		vector<string> nNotice;
		nJson["EVENT"]["NOTICE"].find("Notice").value().get_to(nNotice);

		for (size_t i = 0; i < autoNotice.MaxNotice; i++)
		{
			autoNotice.Notice[i] = nNotice[i];
		}

		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}


}

int ConfigIni::nConfig::WriteAutoEvent(string path, string file)
{
	string fullpath = path + file;

#pragma region Txt New eventAuto.json
	auto nJson = R"(
{
"EVENT": {
		"DOUBLE": {
				"DayStart": 6,
				"HourStart": 0,
				"MinStart": 0,
				"MSGStart" : "O Evento Double Exp foi ativado!!!",
				"DayEnd": 1,
				"HourEnd": 0,
				"MinEnd": 0,
				"MultEXP": 2,
				"MSGEnd": "O Evento Double Exp foi desativado!!!"
			   },
		"NOTICE": {
				"MaxNotice": 10,
				"Days": [1,1,1,1,1,1,1],
				"Hours": [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
				"Notice": [
							"Bem vindo ao Eternal WYD!!!",
							"Visite nossa pagina www.eternalwyd.com.br",
							"Participe de nossas redes sociais e concorra a premios",
							"Reporte bugs e ou erros e seja recompensado por isso",
							"Reporte conduta inadequada de outros jogadores e seja recompensado",
							"Dê sua opniao sobre novos eventos em nossa pagina, e concorra a premios",
							"Nao forneca sua senha para ninguem, voce e total responsavel pela sua account",
							"Utilizacao de programas auxiliares sere passivo de ban permanente",
							"Esta gostando do Eternal WYD? divulgue-nos em suas redes sociais!!",
							"Novo por aqui? use o comando /VemProEternal e receba bonus para novatos"
						  ]
			  }
	    }
})"_json;

#pragma endregion

	try
	{
		ofstream bjson(fullpath);
		bjson << setw(4) << nJson << std::endl;
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::ReadEventTrade(string path, string file)
{
	string fullpath = path + file;
	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	if (fp == NULL) {

		// não encontrado, será criado um novo(default) no diretorio
		int creat = WriteEventTrade(PATH_EVENT_Trade, file);

		if (!creat)
			return creat;
	}

	try
	{
		ifstream spath(fullpath);
		json nJson;
		spath >> nJson;

		nJson["STATUS"]["Days"].get_to(EventTrade.Days);
		nJson["STATUS"]["HourStart"].get_to(EventTrade.HourStart);
		nJson["STATUS"]["MinStart"].get_to(EventTrade.MinStart);
		nJson["STATUS"]["HourEnd"].get_to(EventTrade.HourEnd);
		nJson["STATUS"]["MinEnd"].get_to(EventTrade.MinEnd);
		nJson["STATUS"]["MSGStart"].get_to(EventTrade.MSGStart);
		nJson["STATUS"]["MSGEnd"].get_to(EventTrade.MSGEnd);
		nJson["STATUS"]["MSG"].get_to(EventTrade.MSG);
		nJson["STATUS"]["MsgErr"].get_to(EventTrade.MsgErr);
		nJson["STATUS"]["MsgBag"].get_to(EventTrade.MsgBag);
		nJson["STATUS"]["MsgLimit"].get_to(EventTrade.MsgLimit);

		//NPC1
		nJson["NPC1"]["TradeLimit"].get_to(EventTrade.NPC1.TradeLimit);
		vector<short> nReceiv1;
		nJson["NPC1"]["ItemReceive"].get_to(nReceiv1);
		EventTrade.NPC1.ItemReceive.sIndex = nReceiv1[0];
		EventTrade.NPC1.ItemReceive.stEffect->sValue = nReceiv1[1];
		EventTrade.NPC1.ItemReceive.stEffect[0].cEffect = nReceiv1[2];
		EventTrade.NPC1.ItemReceive.stEffect[0].cValue = nReceiv1[3];
		EventTrade.NPC1.ItemReceive.stEffect[1].cEffect = nReceiv1[4];
		EventTrade.NPC1.ItemReceive.stEffect[1].cValue = nReceiv1[5];
		EventTrade.NPC1.ItemReceive.stEffect[2].cEffect = nReceiv1[6];
		EventTrade.NPC1.ItemReceive.stEffect[2].cValue = nReceiv1[7];

		nJson["NPC1"]["BaseRand"].get_to(EventTrade.NPC1.BaseRand);
		nJson["NPC1"]["Rates"].get_to(EventTrade.NPC1.Rates);

		for (auto& x : nJson["NPC1"]["Reward"].items())
		{

			vector<short> nReward1 = x.value();
			EventTrade.NPC1.Reward[stoi(x.key())].sIndex = nReward1[0];
			EventTrade.NPC1.Reward[stoi(x.key())].stEffect->sValue = nReward1[1];
			EventTrade.NPC1.Reward[stoi(x.key())].stEffect[0].cEffect = nReward1[2];
			EventTrade.NPC1.Reward[stoi(x.key())].stEffect[0].cValue = nReward1[3];
			EventTrade.NPC1.Reward[stoi(x.key())].stEffect[1].cEffect = nReward1[4];
			EventTrade.NPC1.Reward[stoi(x.key())].stEffect[1].cValue = nReward1[5];
			EventTrade.NPC1.Reward[stoi(x.key())].stEffect[2].cEffect = nReward1[6];
			EventTrade.NPC1.Reward[stoi(x.key())].stEffect[2].cValue = nReward1[7];

		};

		//NPC2
		nJson["NPC2"]["TradeLimit"].get_to(EventTrade.NPC2.TradeLimit);
		vector<short> nReceiv2;
		nJson["NPC2"]["ItemReceive"].get_to(nReceiv2);
		EventTrade.NPC2.ItemReceive.sIndex = nReceiv2[0];
		EventTrade.NPC2.ItemReceive.stEffect->sValue = nReceiv2[1];
		EventTrade.NPC2.ItemReceive.stEffect[0].cEffect = nReceiv2[2];
		EventTrade.NPC2.ItemReceive.stEffect[0].cValue = nReceiv2[3];
		EventTrade.NPC2.ItemReceive.stEffect[1].cEffect = nReceiv2[4];
		EventTrade.NPC2.ItemReceive.stEffect[1].cValue = nReceiv2[5];
		EventTrade.NPC2.ItemReceive.stEffect[2].cEffect = nReceiv2[6];
		EventTrade.NPC2.ItemReceive.stEffect[2].cValue = nReceiv2[7];

		nJson["NPC2"]["BaseRand"].get_to(EventTrade.NPC2.BaseRand);
		nJson["NPC2"]["Rates"].get_to(EventTrade.NPC2.Rates);

		for (auto& x : nJson["NPC2"]["Reward"].items())
		{

			vector<short> nReward2 = x.value();
			EventTrade.NPC2.Reward[stoi(x.key())].sIndex = nReward2[0];
			EventTrade.NPC2.Reward[stoi(x.key())].stEffect->sValue = nReward2[1];
			EventTrade.NPC2.Reward[stoi(x.key())].stEffect[0].cEffect = nReward2[2];
			EventTrade.NPC2.Reward[stoi(x.key())].stEffect[0].cValue = nReward2[3];
			EventTrade.NPC2.Reward[stoi(x.key())].stEffect[1].cEffect = nReward2[4];
			EventTrade.NPC2.Reward[stoi(x.key())].stEffect[1].cValue = nReward2[5];
			EventTrade.NPC2.Reward[stoi(x.key())].stEffect[2].cEffect = nReward2[6];
			EventTrade.NPC2.Reward[stoi(x.key())].stEffect[2].cValue = nReward2[7];

		};

		//NPC3
		nJson["NPC3"]["TradeLimit"].get_to(EventTrade.NPC3.TradeLimit);
		vector<short> nReceiv3;
		nJson["NPC3"]["ItemReceive"].get_to(nReceiv3);
		EventTrade.NPC3.ItemReceive.sIndex = nReceiv3[0];
		EventTrade.NPC3.ItemReceive.stEffect->sValue = nReceiv3[1];
		EventTrade.NPC3.ItemReceive.stEffect[0].cEffect = nReceiv3[2];
		EventTrade.NPC3.ItemReceive.stEffect[0].cValue = nReceiv3[3];
		EventTrade.NPC3.ItemReceive.stEffect[1].cEffect = nReceiv3[4];
		EventTrade.NPC3.ItemReceive.stEffect[1].cValue = nReceiv3[5];
		EventTrade.NPC3.ItemReceive.stEffect[2].cEffect = nReceiv3[6];
		EventTrade.NPC3.ItemReceive.stEffect[2].cValue = nReceiv3[7];

		nJson["NPC3"]["BaseRand"].get_to(EventTrade.NPC3.BaseRand);
		nJson["NPC3"]["Rates"].get_to(EventTrade.NPC3.Rates);

		for (auto& x : nJson["NPC3"]["Reward"].items())
		{

			vector<short> nReward3 = x.value();
			EventTrade.NPC3.Reward[stoi(x.key())].sIndex = nReward3[0];
			EventTrade.NPC3.Reward[stoi(x.key())].stEffect->sValue = nReward3[1];
			EventTrade.NPC3.Reward[stoi(x.key())].stEffect[0].cEffect = nReward3[2];
			EventTrade.NPC3.Reward[stoi(x.key())].stEffect[0].cValue = nReward3[3];
			EventTrade.NPC3.Reward[stoi(x.key())].stEffect[1].cEffect = nReward3[4];
			EventTrade.NPC3.Reward[stoi(x.key())].stEffect[1].cValue = nReward3[5];
			EventTrade.NPC3.Reward[stoi(x.key())].stEffect[2].cEffect = nReward3[6];
			EventTrade.NPC3.Reward[stoi(x.key())].stEffect[2].cValue = nReward3[7];

		};

		//NPC4
		nJson["NPC4"]["TradeLimit"].get_to(EventTrade.NPC4.TradeLimit);
		vector<short> nReceiv4;
		nJson["NPC4"]["ItemReceive"].get_to(nReceiv4);
		EventTrade.NPC4.ItemReceive.sIndex = nReceiv4[0];
		EventTrade.NPC4.ItemReceive.stEffect->sValue = nReceiv4[1];
		EventTrade.NPC4.ItemReceive.stEffect[0].cEffect = nReceiv4[2];
		EventTrade.NPC4.ItemReceive.stEffect[0].cValue = nReceiv4[3];
		EventTrade.NPC4.ItemReceive.stEffect[1].cEffect = nReceiv4[4];
		EventTrade.NPC4.ItemReceive.stEffect[1].cValue = nReceiv4[5];
		EventTrade.NPC4.ItemReceive.stEffect[2].cEffect = nReceiv4[6];
		EventTrade.NPC4.ItemReceive.stEffect[2].cValue = nReceiv4[7];

		nJson["NPC4"]["BaseRand"].get_to(EventTrade.NPC4.BaseRand);
		nJson["NPC4"]["Rates"].get_to(EventTrade.NPC4.Rates);

		for (auto& x : nJson["NPC4"]["Reward"].items())
		{

			vector<short> nReward4 = x.value();
			EventTrade.NPC4.Reward[stoi(x.key())].sIndex = nReward4[0];
			EventTrade.NPC4.Reward[stoi(x.key())].stEffect->sValue = nReward4[1];
			EventTrade.NPC4.Reward[stoi(x.key())].stEffect[0].cEffect = nReward4[2];
			EventTrade.NPC4.Reward[stoi(x.key())].stEffect[0].cValue = nReward4[3];
			EventTrade.NPC4.Reward[stoi(x.key())].stEffect[1].cEffect = nReward4[4];
			EventTrade.NPC4.Reward[stoi(x.key())].stEffect[1].cValue = nReward4[5];
			EventTrade.NPC4.Reward[stoi(x.key())].stEffect[2].cEffect = nReward4[6];
			EventTrade.NPC4.Reward[stoi(x.key())].stEffect[2].cValue = nReward4[7];

		};

		//NPC5
		nJson["NPC5"]["TradeLimit"].get_to(EventTrade.NPC5.TradeLimit);
		vector<short> nReceiv5;
		nJson["NPC5"]["ItemReceive"].get_to(nReceiv5);
		EventTrade.NPC5.ItemReceive.sIndex = nReceiv5[0];
		EventTrade.NPC5.ItemReceive.stEffect->sValue = nReceiv5[1];
		EventTrade.NPC5.ItemReceive.stEffect[0].cEffect = nReceiv5[2];
		EventTrade.NPC5.ItemReceive.stEffect[0].cValue = nReceiv5[3];
		EventTrade.NPC5.ItemReceive.stEffect[1].cEffect = nReceiv5[4];
		EventTrade.NPC5.ItemReceive.stEffect[1].cValue = nReceiv5[5];
		EventTrade.NPC5.ItemReceive.stEffect[2].cEffect = nReceiv5[6];
		EventTrade.NPC5.ItemReceive.stEffect[2].cValue = nReceiv5[7];

		nJson["NPC5"]["BaseRand"].get_to(EventTrade.NPC5.BaseRand);
		nJson["NPC5"]["Rates"].get_to(EventTrade.NPC5.Rates);

		for (auto& x : nJson["NPC5"]["Reward"].items())
		{

			vector<short> nReward5 = x.value();
			EventTrade.NPC5.Reward[stoi(x.key())].sIndex = nReward5[0];
			EventTrade.NPC5.Reward[stoi(x.key())].stEffect->sValue = nReward5[1];
			EventTrade.NPC5.Reward[stoi(x.key())].stEffect[0].cEffect = nReward5[2];
			EventTrade.NPC5.Reward[stoi(x.key())].stEffect[0].cValue = nReward5[3];
			EventTrade.NPC5.Reward[stoi(x.key())].stEffect[1].cEffect = nReward5[4];
			EventTrade.NPC5.Reward[stoi(x.key())].stEffect[1].cValue = nReward5[5];
			EventTrade.NPC5.Reward[stoi(x.key())].stEffect[2].cEffect = nReward5[6];
			EventTrade.NPC5.Reward[stoi(x.key())].stEffect[2].cValue = nReward5[7];

		};
		
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::WriteEventTrade(string path, string file)
{
	string fullpath = path + file;

#pragma region Txt New tradeEvent.json
	auto nJson = R"(
{
"STATUS": {
			"Days": [1,1,1,1,1,1,1],
			"HourStart": 0,
			"MinStart": 0,
			"HourEnd": 23,
			"MinEnd": 0,
			"MSGStart": "Evento de Troca Eternal foi iniciado!!",
			"MSGEnd": "Evento de troca Eternal foi finalizado!!!",
			"MSG": "Traga o item [%s]",
			"MsgErr": "Preciso do item [%s]",
			"MsgBag": "Voce precisa de espaco na mochila",
			"MsgLimit": "Voce atingiu o limite de troca de hoje."
			
		  },
"NPC1": {
			"TradeLimit": 0,
			"ItemReceive": [4900,0,0,0,0,0,0,0],
			"BaseRand": 100,
			"Rates": [50,20,20,7,2],
			"Reward": {
						"0": [419,0,0,0,0,0,0,0],
						"1": [420,0,0,0,0,0,0,0],
						"2": [412,0,0,0,0,0,0,0],
						"3": [413,0,0,0,0,0,0,0],
						"4": [4901,0,0,0,0,0,0,0]
					  }
		},
"NPC2": {
			"TradeLimit": 0,
			"ItemReceive": [4901,0,0,0,0,0,0,0],
			"BaseRand": 100,
			"Rates": [50,20,20,7,2],
			"Reward": {
						"0": [3346,0,0,0,0,0,0,0],
						"1": [3345,0,0,0,0,0,0,0],
						"2": [3344,0,0,0,0,0,0,0],
						"3": [3361,0,0,0,0,0,0,0],
						"4": [4902,0,0,0,0,0,0,0]
					  }
		},
"NPC3": {
			"TradeLimit": 0,
			"ItemReceive": [4902,0,0,0,0,0,0,0],
			"BaseRand": 100,
			"Rates": [50,20,20,7,2],
			"Reward": {
						"0": [3389,0,0,0,0,0,0,0],
						"1": [3388,0,0,0,0,0,0,0],
						"2": [3387,0,0,0,0,0,0,0],
						"3": [3386,0,0,0,0,0,0,0],
						"4": [4903,0,0,0,0,0,0,0]
					  }
		},
"NPC4": {
			"TradeLimit": 0,
			"ItemReceive": [4903,0,0,0,0,0,0,0],
			"BaseRand": 100,
			"Rates": [50,20,20,7,2],
			"Reward": {
						"0": [3439,0,0,0,0,0,0,0],
						"1": [3438,0,0,0,0,0,0,0],
						"2": [3454,0,0,0,0,0,0,0],
						"3": [3467,0,0,0,0,0,0,0],
						"4": [4904,0,0,0,0,0,0,0]
					  }
		},
"NPC5": {
			"TradeLimit": 0,
			"ItemReceive": [4904,0,0,0,0,0,0,0],
			"BaseRand": 100,
			"Rates": [50,20,20,7,2],
			"Reward": {
						"0": [4901,0,0,0,0,0,0,0],
						"1": [4026,0,0,0,0,0,0,0],
						"2": [4027,0,0,0,0,0,0,0],
						"3": [4028,0,0,0,0,0,0,0],
						"4": [4029,0,0,0,0,0,0,0]
					  }
		}

})"_json;

#pragma endregion

	try
	{
		ofstream bjson(fullpath);
		bjson << setw(4) << nJson << std::endl;
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::ReadColiseu(string path, string file)
{
	string fullpath = path + file;
	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	if (fp == NULL) {

		// não encontrado, será criado um novo(default) no diretorio
		int creat = WriteColiseu(PATH_SETTINGS, file);

		if (!creat)
			return creat;
	}
	try
	{
		ifstream spath(fullpath);
		json nJson;
		spath >> nJson;

		memset(&nColiseu, 0, sizeof(STRUCT_COLISEU));

		nJson["N"]["Days"].get_to(nColiseu[0].Days);
		nJson["N"]["Hour"].get_to(nColiseu[0].Hour);
		nJson["N"]["Min"].get_to(nColiseu[0].Min);
		nJson["N"]["Item"].get_to(nColiseu[0].Item);

		nJson["M"]["Days"].get_to(nColiseu[1].Days);
		nJson["M"]["Hour"].get_to(nColiseu[1].Hour);
		nJson["M"]["Min"].get_to(nColiseu[1].Min);
		nJson["M"]["Item"].get_to(nColiseu[1].Item);

		nJson["A"]["Days"].get_to(nColiseu[2].Days);
		nJson["A"]["Hour"].get_to(nColiseu[2].Hour);
		nJson["A"]["Min"].get_to(nColiseu[2].Min);
		nJson["A"]["Item"].get_to(nColiseu[2].Item);
		

		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}

}

int ConfigIni::nConfig::WriteColiseu(string path, string file)
{
	string fullpath = path + file;

#pragma region Txt New coliseu.json
	auto nJson = R"(
{
"N": {
		"Days": [1,1,1,1,1,1,1],
		"Hour": [12,20],
		"Min": [0,0],
		"Item": 3170
	 },
"M": {
		"Days": [0,0,0,0,0,0,0],
		"Hour": [12,20],
		"Min": [0,0],
		"Item": 0
	 },
"A": {
		"Days": [0,0,0,0,0,0,0],
		"Hour": [12,20],
		"Min": [0,0],
		"Item": 0
	 }
})"_json;

#pragma endregion

	try
	{
		ofstream bjson(fullpath);
		bjson << setw(4) << nJson << std::endl;
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::ReadStatusServer(string path, string file)
{
	string fullpath = path + file;
	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	if (fp == NULL) {

		// não encontrado, será criado um novo(default) no diretorio
		int creat = WriteStatusServer(PATH_SETTINGS, file);

		if (!creat)
			return creat;
	}

	try
	{
		ifstream spath(fullpath);
		json nJson;
		spath >> nJson;

		memset(EternalServer, 0, MAX_STATUS_SERVER);

		nJson["STATUS"]["String"].get_to(EternalServer[sOff].MSG);

		nJson["STATUS"]["Off"].get_to(EternalServer[sOff].Status);
		nJson["STATUS"]["MSGOff"].get_to(EternalServer[sOff].MSG);

		nJson["STATUS"]["Free"].get_to(EternalServer[sFree].Status);
		nJson["STATUS"]["MSGFree"].get_to(EternalServer[sFree].MSG);

		nJson["STATUS"]["Maintenance"].get_to(EternalServer[sMaintenance].Status);
		nJson["STATUS"]["MSGMaintenance"].get_to(EternalServer[sMaintenance].MSG);

		nJson["STATUS"]["Staff"].get_to(EternalServer[sStaff].Status);
		nJson["STATUS"]["MSGStaff"].get_to(EternalServer[sStaff].MSG);

		nJson["STATUS"]["Premium"].get_to(EternalServer[sPremium].Status);
		nJson["STATUS"]["MSGPremium"].get_to(EternalServer[sPremium].MSG);
		
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::WriteStatusServer(string path, string file)
{
	string fullpath = path + file;

#pragma region Txt New StatusServer.json
	auto nJson = R"(
{
"STATUS": {
			"Off": 0,
			"MSGOff": "Servidor no momento se encontra offiline",
			"Free": 0,
			"MSGFree": "Servidor Disponivel para todos, bom jogo!!",
			"Maintenance": 1,
			"MSGMaintenance": "Servidor em manutenção, volte mais tarde.",
			"Staff": 0,
			"MSGStaff": "Servidor disponivel apenas para Staff Eternal.",
			"Premium": 0,
			"MSGPremium": "Servidor disponivel apenas para jogadores premium."
			
		 }
})"_json;

#pragma endregion

	try
	{
		ofstream bjson(fullpath);
		bjson << setw(4) << nJson << std::endl;
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::WriteStatistic(string path, string file, 
	int tMortal, int tArch, int tCelestial, int tSubCelestial,
	int tTK, int tFM, int tBM, int tHT, int tRed, int tBlue, int tNoReino)
{
	std::string fullpath = path + file;

#pragma region Txt New Statistic.json
	auto nJson = R"(
{
"PLAYER": {
			"Mortal": 0,
			"Arch": 0,
			"Celestial": 0,
			"SubCelestial": 0,
			"ReinoRed": 0,
			"ReinoBlue": 0,
			"SemReino": 0	
		  },
"CLASS": {
			"TK": 0,
			"FM": 0,
			"BM": 0,
			"HT": 0	
		  },
"GERAL": {
			"TOTAL": 0
		 }

})"_json;

#pragma endregion

	try
	{
		int cTotal = 0;
		cTotal = tMortal + tArch + tCelestial + tSubCelestial;
		nJson["PLAYER"]["Mortal"] = tMortal;
		nJson["PLAYER"]["Arch"] = tArch;
		nJson["PLAYER"]["Celestial"] = tCelestial;
		nJson["PLAYER"]["SubCelestial"] = tSubCelestial;
		nJson["PLAYER"]["ReinoRed"] = tRed;
		nJson["PLAYER"]["ReinoBlue"] = tBlue;
		nJson["PLAYER"]["SemReino"] = tNoReino;

		nJson["CLASS"]["TK"] = tTK;
		nJson["CLASS"]["FM"] = tFM;
		nJson["CLASS"]["BM"] = tBM;
		nJson["CLASS"]["HT"] = tHT;

		nJson["GERAL"]["TOTAL"] = cTotal;
		ofstream bjson(fullpath);
		bjson << setw(4) << nJson << std::endl;
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::ReadTitleLevel(string path, string file)
{
	string fullpath = path + file;
	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	if (fp == NULL) {

		// não encontrado, será criado um novo(default) no diretorio
		int creat = WriteTitleLevel(PATH_SETTINGS, file);

		if (!creat)
			return creat;
	}

	try
	{
		ifstream spath(fullpath);
		json nJson;
		spath >> nJson;
		memset(&TitleLevel, 0, sizeof(STRUCT_TITLE_SYSTEM));
		for (size_t i = 0; i < tMaxTitle; i++)
		{
			string titleName = "";
			switch (i)
			{
			case tNOVATO:
				titleName = "NOVATO";
				break;
			case tEXPLORADOR:
				titleName = "EXPLORADOR";
				break;
			case tPERITO:
				titleName = "PERITO";
				break;
			case tVETERANO:
				titleName = "VETERANO";
				break;
			case tMORTAL:
				titleName = "MORTAL";
				break;
			case tMISTICO:
				titleName = "MISTICO";
				break;
			case tARCANO:
				titleName = "ARCANO";
				break;
			case tPESADELO:
				titleName = "PESADELO";
				break;
			case tARCH:
				titleName = "ARCH";
				break;
			case tSUPREMO:
				titleName = "SUPREMO";
				break;
			default:
				break;
			}
			TitleLevel[i].Name = "qwertyuiopasdfghjklzxcvbnm";
			TitleLevel[i].Name = titleName;
			TitleLevel[i].ExpBase = (i + 2) /2;
			TitleLevel[i].DropBase = (i + 1) / 2;
			nJson["CONQUISTA"][titleName].find("Level").value().get_to(TitleLevel[i].Level);
			nJson["CONQUISTA"][titleName].find("ClassMaster").value().get_to(TitleLevel[i].ClassMaster);
			nJson["CONQUISTA"][titleName].find("Classe").value().get_to(TitleLevel[i].Classe);
			nJson["CONQUISTA"][titleName].find("Str").value().get_to(TitleLevel[i].Str);
			nJson["CONQUISTA"][titleName].find("Int").value().get_to(TitleLevel[i].Int);
			nJson["CONQUISTA"][titleName].find("Dex").value().get_to(TitleLevel[i].Dex);
			nJson["CONQUISTA"][titleName].find("Con").value().get_to(TitleLevel[i].Con);
			nJson["CONQUISTA"][titleName].find("LevelMontaria").value().get_to(TitleLevel[i].LevelMontaria);
			nJson["CONQUISTA"][titleName].find("ConjutoRefino").value().get_to(TitleLevel[i].ConjutoRefino);
			nJson["CONQUISTA"][titleName].find("Coin").value().get_to(TitleLevel[i].Coin);
			nJson["CONQUISTA"][titleName].find("Defesa").value().get_to(TitleLevel[i].Defesa);

		}

		
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::WriteTitleLevel(string path, string file)
{
	std::string fullpath = path + file;

#pragma region Txt New titleLevel.json
	auto nJson = R"(
{
"CONQUISTA": {

				"NOVATO":{
							"Level": 10,
							"ClassMaster": 2,
							"Classe": 0,
							"Str":0,
							"Int":0,
							"Dex":0,
							"Con":0,
							"LevelMontaria":0,
							"ConjutoRefino":0,
							"Coin": 0,
							"Defesa":0
							
						 },
				"EXPLORADOR":{
							"Level": 100,
							"ClassMaster": 2,
							"Classe": 0,
							"Str":0,
							"Int":0,
							"Dex":0,
							"Con":0,
							"LevelMontaria":0,
							"ConjutoRefino":0,
							"Coin": 0,
							"Defesa":0
							
						 },
						 
				"PERITO":{
							"Level": 256,
							"ClassMaster": 2,
							"Classe": 0,
							"Str":0,
							"Int":0,
							"Dex":0,
							"Con":0,
							"LevelMontaria":0,
							"ConjutoRefino":0,
							"Coin": 0,
							"Defesa":0
							
						 },
				 "VETERANO":{
							"Level": 356,
							"ClassMaster": 2,
							"Classe": 0,
							"Str":0,
							"Int":0,
							"Dex":0,
							"Con":0,
							"LevelMontaria":0,
							"ConjutoRefino":0,
							"Coin": 0,
							"Defesa":0
							
						 },
				"MORTAL":{
							"Level": 400,
							"ClassMaster": 2,
							"Classe": 0,
							"Str":0,
							"Int":0,
							"Dex":0,
							"Con":0,
							"LevelMontaria":0,
							"ConjutoRefino":0,
							"Coin": 0,
							"Defesa":0
							
						 },
						 
				"MISTICO":{
							"Level": 1,
							"ClassMaster": 1,
							"Classe": 0,
							"Str":0,
							"Int":0,
							"Dex":0,
							"Con":0,
							"LevelMontaria":0,
							"ConjutoRefino":0,
							"Coin": 0,
							"Defesa":0
							
						 },
				"ARCANO":{
							"Level": 256,
							"ClassMaster": 1,
							"Classe": 0,
							"Str":0,
							"Int":0,
							"Dex":0,
							"Con":0,
							"LevelMontaria":0,
							"ConjutoRefino":0,
							"Coin": 0,
							"Defesa":0
							
						 },
				"PESADELO":{
							"Level": 356,
							"ClassMaster": 1,
							"Classe": 0,
							"Str":0,
							"Int":0,
							"Dex":0,
							"Con":0,
							"LevelMontaria":0,
							"ConjutoRefino":0,
							"Coin": 0,
							"Defesa":0
							
						 },
				"ARCH":{
							"Level": 400,
							"ClassMaster": 1,
							"Classe": 0,
							"Str":0,
							"Int":0,
							"Dex":0,
							"Con":0,
							"LevelMontaria":0,
							"ConjutoRefino":0,
							"Coin": 0,
							"Defesa":0
							
						 },
				"SUPREMO":{
							"Level": 1,
							"ClassMaster": 3,
							"Classe": 0,
							"Str":0,
							"Int":0,
							"Dex":0,
							"Con":0,
							"LevelMontaria":0,
							"ConjutoRefino":0,
							"Coin": 0,
							"Defesa":0
							
						 }
	}

})"_json;

#pragma endregion

	
	try
	{
		ofstream bjson(fullpath);
		bjson << setw(4) << nJson << std::endl;
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::ReadGuildLevel(string path, string file)
{
	string fullpath = path + file;
	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	if (fp == NULL) {

		// não encontrado, será criado um novo(default) no diretorio
		int creat = WriteGuildLevel(PATH_SETTINGS, file);

		if (!creat)
			return creat;
	}

	try
	{
		ifstream spath(fullpath);
		json nJson;
		spath >> nJson;
		memset(&GuildLevel, 0, MAX_GUILD_LEVEL);

		for (auto& x : nJson["LEVEL"].items())
			GuildLevel[stoi(x.key())] = x.value();

		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::WriteGuildLevel(string path, string file)
{
	std::string fullpath = path + file;

#pragma region Txt New GuildLevel.json
	auto nJson = R"(
{
"LEVEL": {
		 "0": 0,
		 "1": 1200,
		 "2": 3400,
		 "3": 7100,
		 "4": 12000,
		 "5": 22000,
		 "6": 34000,
		 "7": 48000,
		 "8": 75000,
		 "9": 100000
		  }

})"_json;

#pragma endregion


	try
	{
		ofstream bjson(fullpath);
		bjson << setw(4) << nJson << std::endl;
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::ReadGuildHall(string path, string file)
{
	string fullpath = path + file;
	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	if (fp == NULL) 
			return FALSE;

	try
	{
		ifstream spath(fullpath);
		json nJson;
		spath >> nJson;

	
		int nGuildIndex = -1;

		nJson["SYSTEM"]["GuildIndex"].get_to(nGuildIndex);
		nJson["SYSTEM"]["FamePoint"].get_to(GuildHall[nGuildIndex].FamePoint);
		nJson["SYSTEM"]["Level"].get_to(GuildHall[nGuildIndex].Level);
		nJson["SYSTEM"]["Lider"].get_to(GuildHall[nGuildIndex].Lider);
		nJson["SYSTEM"]["TotalMember"].get_to(GuildHall[nGuildIndex].TotalMember);
		nJson["SYSTEM"]["Territory"].get_to(GuildHall[nGuildIndex].Territory);
	
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::WriteGuildHall(string path, string file, unsigned int guildIndex)
{
	std::string fullpath = path + file;
	json nJson;

	try
	{
		nJson["SYSTEM"]["GuildIndex"] = guildIndex;
		nJson["SYSTEM"]["FamePoint"] = GuildHall[guildIndex].FamePoint;
		nJson["SYSTEM"]["Level"] = GuildHall[guildIndex].Level;
		nJson["SYSTEM"]["Lider"] = GuildHall[guildIndex].Lider;
		nJson["SYSTEM"]["TotalMember"] = GuildHall[guildIndex].TotalMember;
		nJson["SYSTEM"]["Territory"] = GuildHall[guildIndex].Territory;
		ofstream bjson(fullpath);
		bjson << setw(4) << nJson << std::endl;
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::ReadTerritory(string path, string file, unsigned int nTerritory)
{
	string fullpath = path + file;
	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	if (fp == NULL)
		return FALSE;

	try
	{
		ifstream spath(fullpath);
		json nJson;
		spath >> nJson;

		nJson["CONFIG"]["Key"].get_to(Territory[nTerritory].Name);
		nJson["CONFIG"]["Name"].get_to(Territory[nTerritory].Name);
		nJson["CONFIG"]["GuildIndex"].get_to(Territory[nTerritory].GuildIndex);
		nJson["CONFIG"]["Level"].get_to(Territory[nTerritory].Level);
		nJson["CONFIG"]["MaxMob"].get_to(Territory[nTerritory].MaxMob);
		nJson["CONFIG"]["Mob"].get_to(Territory[nTerritory].Mob);
		nJson["CONFIG"]["Challenger"].get_to(Territory[nTerritory].Challenger);
		nJson["CONFIG"]["DayWar"].get_to(Territory[nTerritory].DayWar);
		nJson["CONFIG"]["X1"].get_to(Territory[nTerritory].X1);
		nJson["CONFIG"]["X2"].get_to(Territory[nTerritory].X2);
		nJson["CONFIG"]["Y1"].get_to(Territory[nTerritory].Y1);
		nJson["CONFIG"]["Y2"].get_to(Territory[nTerritory].Y2);
		nJson["CONFIG"]["InputX"].get_to(Territory[nTerritory].InputX);
		nJson["CONFIG"]["InputY"].get_to(Territory[nTerritory].InputY);
		nJson["CONFIG"]["Day"].get_to(Territory[nTerritory].Day);
		nJson["CONFIG"]["Year"].get_to(Territory[nTerritory].Year);
		nJson["CONFIG"]["Start"].get_to(Territory[nTerritory].Start);
		nJson["CONFIG"]["CooReset"].get_to(Territory[nTerritory].CooReset);

		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::WriteTerritory(string path, string file, unsigned int nTerritory)
{
	std::string fullpath = path + file;
	json nJson;

	try
	{
		nJson["CONFIG"]["Key"] = "qwertyuiopasdfghjklzxcvbnm";
		nJson["CONFIG"]["Name"] = Territory[nTerritory].Name;
		nJson["CONFIG"]["GuildIndex"] = Territory[nTerritory].GuildIndex;
		nJson["CONFIG"]["Level"] = Territory[nTerritory].Level;
		nJson["CONFIG"]["MaxMob"] = Territory[nTerritory].MaxMob;
		nJson["CONFIG"]["Mob"] = Territory[nTerritory].Mob;
		nJson["CONFIG"]["Challenger"] = Territory[nTerritory].Challenger;
		nJson["CONFIG"]["DayWar"] = Territory[nTerritory].DayWar;
		nJson["CONFIG"]["X1"] = Territory[nTerritory].X1;
		nJson["CONFIG"]["X2"] = Territory[nTerritory].X2;
		nJson["CONFIG"]["Y1"] = Territory[nTerritory].Y1;
		nJson["CONFIG"]["Y2"] = Territory[nTerritory].Y2;
		nJson["CONFIG"]["InputX"] = Territory[nTerritory].InputX;
		nJson["CONFIG"]["InputY"] = Territory[nTerritory].InputY;
		nJson["CONFIG"]["Day"] = Territory[nTerritory].Day;
		nJson["CONFIG"]["Year"] = Territory[nTerritory].Year;
		nJson["CONFIG"]["Start"] = Territory[nTerritory].Start;
		nJson["CONFIG"]["CooReset"] = Territory[nTerritory].CooReset;
	
		ofstream bjson(fullpath);
		bjson << setw(4) << nJson << std::endl;
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::ReadRvrWinner(string path, string file)
{
	time_t rawnow = time(NULL);
	struct tm* now = localtime(&rawnow);
	string fullpath = path + file;
	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	if (fp == NULL)
		return FALSE;

	try
	{
		ifstream spath(fullpath);
		json nJson;
		spath >> nJson;

		nJson["CONFIG"]["Winner"].get_to(g_pRvrWar.Bonus);
		nJson["CONFIG"]["Day"].get_to(now->tm_yday);
		nJson["CONFIG"]["Year"].get_to(now->tm_year);

		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::WriteRvrWinner(string path, string file)
{
	time_t rawnow = time(NULL);
	struct tm* now = localtime(&rawnow);
	std::string fullpath = path + file;
	json nJson;

	try
	{

		nJson["CONFIG"]["Winner"] = g_pRvrWar.Bonus;
		nJson["CONFIG"]["Day"] = now->tm_yday;
		nJson["CONFIG"]["Year"] = now->tm_year;
		
		ofstream bjson(fullpath);
		bjson << setw(4) << nJson << std::endl;
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::ReadInvadeArmia(string path, string file)
{
	string fullpath = path + file;
	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	if (fp == NULL) {

		// não encontrado, será criado um novo(default) no diretorio
		int creat = WriteInvadeArmia(PATH_INVADE, file);

		if (!creat)
			return creat;
	}

	try
	{
		ifstream spath(fullpath);
		json nJson;
		spath >> nJson;
		memset(&INVADE_ARMIA, 0, sizeof(STRUCT_EVENT_INVADE));

		nJson["ARMIA"]["nDay"].get_to(INVADE_ARMIA.nDay);
		nJson["ARMIA"]["nHour"].get_to(INVADE_ARMIA.nHour);
		nJson["ARMIA"]["nMin"].get_to(INVADE_ARMIA.nMin);
		nJson["ARMIA"]["ID"].get_to(INVADE_ARMIA.ID);
		nJson["ARMIA"]["Group"].get_to(INVADE_ARMIA.Group);
		nJson["ARMIA"]["StartX"].get_to(INVADE_ARMIA.StartX);
		nJson["ARMIA"]["StartY"].get_to(INVADE_ARMIA.StartY);
		nJson["ARMIA"]["EndX"].get_to(INVADE_ARMIA.EndX);
		nJson["ARMIA"]["EndY"].get_to(INVADE_ARMIA.EndY);
		nJson["ARMIA"]["Rate"].get_to(INVADE_ARMIA.Rate);
		nJson["ARMIA"]["Drop"].get_to(INVADE_ARMIA.Drop);
		nJson["ARMIA"]["IDBoss"].get_to(INVADE_ARMIA.IDBoss);
		nJson["ARMIA"]["RateBoss"].get_to(INVADE_ARMIA.RateBoss);

		for (auto& x : nJson["ARMIA"]["DropBoss"].items())
		{

			vector<short> nDropBoss = x.value();
			INVADE_ARMIA.DropBoss[stoi(x.key())].sIndex = nDropBoss[0];
			INVADE_ARMIA.DropBoss[stoi(x.key())].stEffect->sValue = nDropBoss[1];
			INVADE_ARMIA.DropBoss[stoi(x.key())].stEffect[0].cEffect = nDropBoss[2];
			INVADE_ARMIA.DropBoss[stoi(x.key())].stEffect[0].cValue = nDropBoss[3];
			INVADE_ARMIA.DropBoss[stoi(x.key())].stEffect[1].cEffect = nDropBoss[4];
			INVADE_ARMIA.DropBoss[stoi(x.key())].stEffect[1].cValue = nDropBoss[5];
			INVADE_ARMIA.DropBoss[stoi(x.key())].stEffect[2].cEffect = nDropBoss[6];
			INVADE_ARMIA.DropBoss[stoi(x.key())].stEffect[2].cValue = nDropBoss[7];

		};

		nJson["ARMIA"]["Time"].get_to(INVADE_ARMIA.Time);

		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::WriteInvadeArmia(string path, string file)
{
	std::string fullpath = path + file;
#pragma region Txt New GuildLevel.json
	auto nJson = R"(
{
"ARMIA": {
			"nDay": 6,
			"nHour": 20,
			"nMin": 0,
			"ID": [4121,4121,4121,4121,4121,4121,4121],
			"Group": 300,
			"StartX": 2248,
			"StartY": 2115,
			"EndX": 2177,
			"EndY": 2103,
			"Rate": [30,61,75,86],
			"Drop": [419,420,412,413],	
			"IDBoss": 4125,
			"RateBoss": [30,61,82,99],
			"DropBoss": {
							"0": [3173,0,61,30,0,0,0,0],
							"1": [777,0,61,20,0,0,0,0],
							"2": [1774,0,0,0,0,0,0,0],
							"3": [4029,0,0,0,0,0,0,0]
						},
			"Time": 1800
		 }
})"_json;

#pragma endregion

	try
	{
		ofstream bjson(fullpath);
		bjson << setw(4) << nJson << std::endl;
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::ReadSombraNegra(string path, string file)
{
	string fullpath = path + file;
	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	if (fp == NULL) {

		// não encontrado, será criado um novo(default) no diretorio
		int creat = WriteSombraNegra(PATH_SOMBRA_NEGRA, file);

		if (!creat)
			return creat;
	}
	try
	{
		ifstream spath(fullpath);
		json nJson;
		spath >> nJson;

		memset(&bSombraNegra, 0, sizeof(STRUCT_SOMBRA_NEGRA));
		//memset(&bSombraNegra.Boss, 0, sizeof(STRUCT_BOSS));
		//(&bSombraNegra.Guardian, 0, sizeof(STRUCT_BOSS));

		nJson["STATUS"]["Days"].get_to(bSombraNegra.Days);
		nJson["STATUS"]["StartHour"].get_to(bSombraNegra.StartHour);
		nJson["STATUS"]["EndHour"].get_to(bSombraNegra.EndHour);
		nJson["STATUS"]["Follow"].get_to(bSombraNegra.follow);
		nJson["STATUS"]["String"].get_to(bSombraNegra.NoticeStart);
		nJson["STATUS"]["NoticeStart"].get_to(bSombraNegra.NoticeStart);
		nJson["STATUS"]["NoticeEnd1"].get_to(bSombraNegra.NoticeEnd1);
		nJson["STATUS"]["NoticeEnd2"].get_to(bSombraNegra.NoticeEnd2);
#pragma region  Boss	
		nJson["BOSS"]["ID"].get_to(bSombraNegra.Boss.ID);
		string nName;
		nJson["BOSS"]["NAME"].get_to(nName);
		bSombraNegra.Boss.NAME = nName.c_str();
		vector<short> nFace;
		nJson["BOSS"]["FACE"].get_to(nFace);
		bSombraNegra.Boss.FACE.sIndex = nFace[0];
		bSombraNegra.Boss.FACE.stEffect->sValue = nFace[1];
		bSombraNegra.Boss.FACE.stEffect[0].cEffect = nFace[2];
		bSombraNegra.Boss.FACE.stEffect[0].cValue = nFace[3];
		bSombraNegra.Boss.FACE.stEffect[1].cEffect = nFace[4];
		bSombraNegra.Boss.FACE.stEffect[1].cValue = nFace[5];
		bSombraNegra.Boss.FACE.stEffect[2].cEffect = nFace[6];
		bSombraNegra.Boss.FACE.stEffect[2].cValue = nFace[7];

		vector<short> nHelm;
		nJson["BOSS"]["HELM"].get_to(nHelm);
		bSombraNegra.Boss.HELM.sIndex = nHelm[0];
		bSombraNegra.Boss.HELM.stEffect->sValue = nHelm[1];
		bSombraNegra.Boss.HELM.stEffect[0].cEffect = nHelm[2];
		bSombraNegra.Boss.HELM.stEffect[0].cValue = nHelm[3];
		bSombraNegra.Boss.HELM.stEffect[1].cEffect = nHelm[4];
		bSombraNegra.Boss.HELM.stEffect[1].cValue = nHelm[5];
		bSombraNegra.Boss.HELM.stEffect[2].cEffect = nHelm[6];
		bSombraNegra.Boss.HELM.stEffect[2].cValue = nHelm[7];

		vector<short> nBody;
		nJson["BOSS"]["BODY"].get_to(nBody);
		bSombraNegra.Boss.BODY.sIndex = nBody[0];
		bSombraNegra.Boss.BODY.stEffect->sValue = nBody[1];
		bSombraNegra.Boss.BODY.stEffect[0].cEffect = nBody[2];
		bSombraNegra.Boss.BODY.stEffect[0].cValue = nBody[3];
		bSombraNegra.Boss.BODY.stEffect[1].cEffect = nBody[4];
		bSombraNegra.Boss.BODY.stEffect[1].cValue = nBody[5];
		bSombraNegra.Boss.BODY.stEffect[2].cEffect = nBody[6];
		bSombraNegra.Boss.BODY.stEffect[2].cValue = nBody[7];

		vector<short> nLeg;
		nJson["BOSS"]["LEG"].get_to(nLeg);
		bSombraNegra.Boss.LEG.sIndex = nLeg[0];
		bSombraNegra.Boss.LEG.stEffect->sValue = nLeg[1];
		bSombraNegra.Boss.LEG.stEffect[0].cEffect = nLeg[2];
		bSombraNegra.Boss.LEG.stEffect[0].cValue = nLeg[3];
		bSombraNegra.Boss.LEG.stEffect[1].cEffect = nLeg[4];
		bSombraNegra.Boss.LEG.stEffect[1].cValue = nLeg[5];
		bSombraNegra.Boss.LEG.stEffect[2].cEffect = nLeg[6];
		bSombraNegra.Boss.LEG.stEffect[2].cValue = nLeg[7];

		vector<short> nGlove;
		nJson["BOSS"]["GLOVE"].get_to(nGlove);
		bSombraNegra.Boss.GLOVE.sIndex = nGlove[0];
		bSombraNegra.Boss.GLOVE.stEffect->sValue = nGlove[1];
		bSombraNegra.Boss.GLOVE.stEffect[0].cEffect = nGlove[2];
		bSombraNegra.Boss.GLOVE.stEffect[0].cValue = nGlove[3];
		bSombraNegra.Boss.GLOVE.stEffect[1].cEffect = nGlove[4];
		bSombraNegra.Boss.GLOVE.stEffect[1].cValue = nGlove[5];
		bSombraNegra.Boss.GLOVE.stEffect[2].cEffect = nGlove[6];
		bSombraNegra.Boss.GLOVE.stEffect[2].cValue = nGlove[7];

		vector<short> nBoot;
		nJson["BOSS"]["BOOT"].get_to(nBoot);
		bSombraNegra.Boss.BOOT.sIndex = nBoot[0];
		bSombraNegra.Boss.BOOT.stEffect->sValue = nBoot[1];
		bSombraNegra.Boss.BOOT.stEffect[0].cEffect = nBoot[2];
		bSombraNegra.Boss.BOOT.stEffect[0].cValue = nBoot[3];
		bSombraNegra.Boss.BOOT.stEffect[1].cEffect = nBoot[4];
		bSombraNegra.Boss.BOOT.stEffect[1].cValue = nBoot[5];
		bSombraNegra.Boss.BOOT.stEffect[2].cEffect = nBoot[6];
		bSombraNegra.Boss.BOOT.stEffect[2].cValue = nBoot[7];

		vector<short> nWeapon;
		nJson["BOSS"]["WEAPON"].get_to(nWeapon);
		bSombraNegra.Boss.WEAPON.sIndex = nWeapon[0];
		bSombraNegra.Boss.WEAPON.stEffect->sValue = nWeapon[1];
		bSombraNegra.Boss.WEAPON.stEffect[0].cEffect = nWeapon[2];
		bSombraNegra.Boss.WEAPON.stEffect[0].cValue = nWeapon[3];
		bSombraNegra.Boss.WEAPON.stEffect[1].cEffect = nWeapon[4];
		bSombraNegra.Boss.WEAPON.stEffect[1].cValue = nWeapon[5];
		bSombraNegra.Boss.WEAPON.stEffect[2].cEffect = nWeapon[6];
		bSombraNegra.Boss.WEAPON.stEffect[2].cValue = nWeapon[7];

		vector<short> nShield;
		nJson["BOSS"]["SHIELD"].get_to(nShield);
		bSombraNegra.Boss.SHIELD.sIndex = nShield[0];
		bSombraNegra.Boss.SHIELD.stEffect->sValue = nShield[1];
		bSombraNegra.Boss.SHIELD.stEffect[0].cEffect = nShield[2];
		bSombraNegra.Boss.SHIELD.stEffect[0].cValue = nShield[3];
		bSombraNegra.Boss.SHIELD.stEffect[1].cEffect = nShield[4];
		bSombraNegra.Boss.SHIELD.stEffect[1].cValue = nShield[5];
		bSombraNegra.Boss.SHIELD.stEffect[2].cEffect = nShield[6];
		bSombraNegra.Boss.SHIELD.stEffect[2].cValue = nShield[7];

		vector<short> nPixie;
		nJson["BOSS"]["PIXIE"].get_to(nPixie);
		bSombraNegra.Boss.PIXIE.sIndex = nPixie[0];
		bSombraNegra.Boss.PIXIE.stEffect->sValue = nPixie[1];
		bSombraNegra.Boss.PIXIE.stEffect[0].cEffect = nPixie[2];
		bSombraNegra.Boss.PIXIE.stEffect[0].cValue = nPixie[3];
		bSombraNegra.Boss.PIXIE.stEffect[1].cEffect = nPixie[4];
		bSombraNegra.Boss.PIXIE.stEffect[1].cValue = nPixie[5];
		bSombraNegra.Boss.PIXIE.stEffect[2].cEffect = nPixie[6];
		bSombraNegra.Boss.PIXIE.stEffect[2].cValue = nPixie[7];
		
		nJson["BOSS"]["StartX"].get_to(bSombraNegra.Boss.StartX);
		nJson["BOSS"]["StartY"].get_to(bSombraNegra.Boss.StartY);
		nJson["BOSS"]["DestX"].get_to(bSombraNegra.Boss.DestX);
		nJson["BOSS"]["DestY"].get_to(bSombraNegra.Boss.DestY);
		nJson["BOSS"]["REGEN"].get_to(bSombraNegra.Boss.REGEN);
		nJson["BOSS"]["LEVEL"].get_to(bSombraNegra.Boss.LEVEL);
		nJson["BOSS"]["HP"].get_to(bSombraNegra.Boss.HP);
		nJson["BOSS"]["MP"].get_to(bSombraNegra.Boss.MP);
		nJson["BOSS"]["AC"].get_to(bSombraNegra.Boss.AC);
		nJson["BOSS"]["DAN"].get_to(bSombraNegra.Boss.DAN);
		nJson["BOSS"]["MAGIC"].get_to(bSombraNegra.Boss.MAGI);
		nJson["BOSS"]["STR"].get_to(bSombraNegra.Boss.STR);
		nJson["BOSS"]["INT"].get_to(bSombraNegra.Boss.INT);
		nJson["BOSS"]["DEX"].get_to(bSombraNegra.Boss.DEX);
		nJson["BOSS"]["CON"].get_to(bSombraNegra.Boss.CON);
		nJson["BOSS"]["MSG1"].get_to(bSombraNegra.Boss.MSG1);
		nJson["BOSS"]["MSG2"].get_to(bSombraNegra.Boss.MSG2);
		nJson["BOSS"]["MSG3"].get_to(bSombraNegra.Boss.MSG3);

#pragma endregion

#pragma region Guardian
		nJson["GUARDIAN"]["ID"].get_to(bSombraNegra.Guardian.ID);
		//string gName;
		nJson["GUARDIAN"]["NAME"].get_to(bSombraNegra.Guardian.NAME);
		//bSombraNegra.Guardian.NAME = gName.c_str();
		memset(&nFace, 0, 8);
		nJson["GUARDIAN"]["FACE"].get_to(nFace);
		bSombraNegra.Guardian.FACE.sIndex = nFace[0];
		bSombraNegra.Guardian.FACE.stEffect->sValue = nFace[1];
		bSombraNegra.Guardian.FACE.stEffect[0].cEffect = nFace[2];
		bSombraNegra.Guardian.FACE.stEffect[0].cValue = nFace[3];
		bSombraNegra.Guardian.FACE.stEffect[1].cEffect = nFace[4];
		bSombraNegra.Guardian.FACE.stEffect[1].cValue = nFace[5];
		bSombraNegra.Guardian.FACE.stEffect[2].cEffect = nFace[6];
		bSombraNegra.Guardian.FACE.stEffect[2].cValue = nFace[7];

		memset(&nHelm, 0, 8);
		nJson["GUARDIAN"]["HELM"].get_to(nHelm);
		bSombraNegra.Guardian.HELM.sIndex = nHelm[0];
		bSombraNegra.Guardian.HELM.stEffect->sValue = nHelm[1];
		bSombraNegra.Guardian.HELM.stEffect[0].cEffect = nHelm[2];
		bSombraNegra.Guardian.HELM.stEffect[0].cValue = nHelm[3];
		bSombraNegra.Guardian.HELM.stEffect[1].cEffect = nHelm[4];
		bSombraNegra.Guardian.HELM.stEffect[1].cValue = nHelm[5];
		bSombraNegra.Guardian.HELM.stEffect[2].cEffect = nHelm[6];
		bSombraNegra.Guardian.HELM.stEffect[2].cValue = nHelm[7];

		memset(&nBody, 0, 8);
		nJson["GUARDIAN"]["BODY"].get_to(nBody);
		bSombraNegra.Guardian.BODY.sIndex = nBody[0];
		bSombraNegra.Guardian.BODY.stEffect->sValue = nBody[1];
		bSombraNegra.Guardian.BODY.stEffect[0].cEffect = nBody[2];
		bSombraNegra.Guardian.BODY.stEffect[0].cValue = nBody[3];
		bSombraNegra.Guardian.BODY.stEffect[1].cEffect = nBody[4];
		bSombraNegra.Guardian.BODY.stEffect[1].cValue = nBody[5];
		bSombraNegra.Guardian.BODY.stEffect[2].cEffect = nBody[6];
		bSombraNegra.Guardian.BODY.stEffect[2].cValue = nBody[7];

		memset(&nLeg, 0, 8);
		nJson["GUARDIAN"]["LEG"].get_to(nLeg);
		bSombraNegra.Guardian.LEG.sIndex = nLeg[0];
		bSombraNegra.Guardian.LEG.stEffect->sValue = nLeg[1];
		bSombraNegra.Guardian.LEG.stEffect[0].cEffect = nLeg[2];
		bSombraNegra.Guardian.LEG.stEffect[0].cValue = nLeg[3];
		bSombraNegra.Guardian.LEG.stEffect[1].cEffect = nLeg[4];
		bSombraNegra.Guardian.LEG.stEffect[1].cValue = nLeg[5];
		bSombraNegra.Guardian.LEG.stEffect[2].cEffect = nLeg[6];
		bSombraNegra.Guardian.LEG.stEffect[2].cValue = nLeg[7];

		memset(&nGlove, 0, 8);
		nJson["GUARDIAN"]["GLOVE"].get_to(nGlove);
		bSombraNegra.Guardian.GLOVE.sIndex = nGlove[0];
		bSombraNegra.Guardian.GLOVE.stEffect->sValue = nGlove[1];
		bSombraNegra.Guardian.GLOVE.stEffect[0].cEffect = nGlove[2];
		bSombraNegra.Guardian.GLOVE.stEffect[0].cValue = nGlove[3];
		bSombraNegra.Guardian.GLOVE.stEffect[1].cEffect = nGlove[4];
		bSombraNegra.Guardian.GLOVE.stEffect[1].cValue = nGlove[5];
		bSombraNegra.Guardian.GLOVE.stEffect[2].cEffect = nGlove[6];
		bSombraNegra.Guardian.GLOVE.stEffect[2].cValue = nGlove[7];

		memset(&nBoot, 0, 8);
		nJson["GUARDIAN"]["BOOT"].get_to(nBoot);
		bSombraNegra.Guardian.BOOT.sIndex = nBoot[0];
		bSombraNegra.Guardian.BOOT.stEffect->sValue = nBoot[1];
		bSombraNegra.Guardian.BOOT.stEffect[0].cEffect = nBoot[2];
		bSombraNegra.Guardian.BOOT.stEffect[0].cValue = nBoot[3];
		bSombraNegra.Guardian.BOOT.stEffect[1].cEffect = nBoot[4];
		bSombraNegra.Guardian.BOOT.stEffect[1].cValue = nBoot[5];
		bSombraNegra.Guardian.BOOT.stEffect[2].cEffect = nBoot[6];
		bSombraNegra.Guardian.BOOT.stEffect[2].cValue = nBoot[7];

		memset(&nWeapon, 0, 8);
		nJson["GUARDIAN"]["WEAPON"].get_to(nWeapon);
		bSombraNegra.Guardian.WEAPON.sIndex = nWeapon[0];
		bSombraNegra.Guardian.WEAPON.stEffect->sValue = nWeapon[1];
		bSombraNegra.Guardian.WEAPON.stEffect[0].cEffect = nWeapon[2];
		bSombraNegra.Guardian.WEAPON.stEffect[0].cValue = nWeapon[3];
		bSombraNegra.Guardian.WEAPON.stEffect[1].cEffect = nWeapon[4];
		bSombraNegra.Guardian.WEAPON.stEffect[1].cValue = nWeapon[5];
		bSombraNegra.Guardian.WEAPON.stEffect[2].cEffect = nWeapon[6];
		bSombraNegra.Guardian.WEAPON.stEffect[2].cValue = nWeapon[7];

		memset(&nShield, 0, 8);
		nJson["GUARDIAN"]["SHIELD"].get_to(nShield);
		bSombraNegra.Guardian.SHIELD.sIndex = nShield[0];
		bSombraNegra.Guardian.SHIELD.stEffect->sValue = nShield[1];
		bSombraNegra.Guardian.SHIELD.stEffect[0].cEffect = nShield[2];
		bSombraNegra.Guardian.SHIELD.stEffect[0].cValue = nShield[3];
		bSombraNegra.Guardian.SHIELD.stEffect[1].cEffect = nShield[4];
		bSombraNegra.Guardian.SHIELD.stEffect[1].cValue = nShield[5];
		bSombraNegra.Guardian.SHIELD.stEffect[2].cEffect = nShield[6];
		bSombraNegra.Guardian.SHIELD.stEffect[2].cValue = nShield[7];

		memset(&nPixie, 0, 8);
		nJson["BOSS"]["PIXIE"].get_to(nPixie);
		bSombraNegra.Guardian.PIXIE.sIndex = nPixie[0];
		bSombraNegra.Guardian.PIXIE.stEffect->sValue = nPixie[1];
		bSombraNegra.Guardian.PIXIE.stEffect[0].cEffect = nPixie[2];
		bSombraNegra.Guardian.PIXIE.stEffect[0].cValue = nPixie[3];
		bSombraNegra.Guardian.PIXIE.stEffect[1].cEffect = nPixie[4];
		bSombraNegra.Guardian.PIXIE.stEffect[1].cValue = nPixie[5];
		bSombraNegra.Guardian.PIXIE.stEffect[2].cEffect = nPixie[6];
		bSombraNegra.Guardian.PIXIE.stEffect[2].cValue = nPixie[7];

		nJson["GUARDIAN"]["StartX"].get_to(bSombraNegra.Guardian.StartX);
		nJson["GUARDIAN"]["StartY"].get_to(bSombraNegra.Guardian.StartY);
		nJson["GUARDIAN"]["DestX"].get_to(bSombraNegra.Guardian.DestX);
		nJson["GUARDIAN"]["DestY"].get_to(bSombraNegra.Guardian.DestY);
		nJson["GUARDIAN"]["REGEN"].get_to(bSombraNegra.Guardian.REGEN);
		nJson["GUARDIAN"]["LEVEL"].get_to(bSombraNegra.Guardian.LEVEL);
		nJson["GUARDIAN"]["HP"].get_to(bSombraNegra.Guardian.HP);
		nJson["GUARDIAN"]["MP"].get_to(bSombraNegra.Guardian.MP);
		nJson["GUARDIAN"]["AC"].get_to(bSombraNegra.Guardian.AC);
		nJson["GUARDIAN"]["DAN"].get_to(bSombraNegra.Guardian.DAN);
		nJson["GUARDIAN"]["MAGIC"].get_to(bSombraNegra.Guardian.MAGI);
		nJson["GUARDIAN"]["STR"].get_to(bSombraNegra.Guardian.STR);
		nJson["GUARDIAN"]["INT"].get_to(bSombraNegra.Guardian.INT);
		nJson["GUARDIAN"]["DEX"].get_to(bSombraNegra.Guardian.DEX);
		nJson["GUARDIAN"]["CON"].get_to(bSombraNegra.Guardian.CON);
		nJson["GUARDIAN"]["MSG1"].get_to(bSombraNegra.Guardian.MSG1);
		nJson["GUARDIAN"]["MSG2"].get_to(bSombraNegra.Guardian.MSG2);
		nJson["GUARDIAN"]["MSG3"].get_to(bSombraNegra.Guardian.MSG3);
#pragma endregion

		for (auto& x : nJson["DROP"].items())
		{

			vector<short> nDrop = x.value();
			bSombraNegra.Drop[stoi(x.key())].sIndex = nDrop[0];
			bSombraNegra.Drop[stoi(x.key())].stEffect->sValue = nDrop[1];
			bSombraNegra.Drop[stoi(x.key())].stEffect[0].cEffect = nDrop[2];
			bSombraNegra.Drop[stoi(x.key())].stEffect[0].cValue = nDrop[3];
			bSombraNegra.Drop[stoi(x.key())].stEffect[1].cEffect = nDrop[4];
			bSombraNegra.Drop[stoi(x.key())].stEffect[1].cValue = nDrop[5];
			bSombraNegra.Drop[stoi(x.key())].stEffect[2].cEffect = nDrop[6];
			bSombraNegra.Drop[stoi(x.key())].stEffect[2].cValue = nDrop[7];

		};

		for (auto& x : nJson["DROPPARTY"].items())
		{

			vector<short> nDropParty = x.value();
			bSombraNegra.DropParty[stoi(x.key())].sIndex = nDropParty[0];
			bSombraNegra.DropParty[stoi(x.key())].stEffect->sValue = nDropParty[1];
			bSombraNegra.DropParty[stoi(x.key())].stEffect[0].cEffect = nDropParty[2];
			bSombraNegra.DropParty[stoi(x.key())].stEffect[0].cValue = nDropParty[3];
			bSombraNegra.DropParty[stoi(x.key())].stEffect[1].cEffect = nDropParty[4];
			bSombraNegra.DropParty[stoi(x.key())].stEffect[1].cValue = nDropParty[5];
			bSombraNegra.DropParty[stoi(x.key())].stEffect[2].cEffect = nDropParty[6];
			bSombraNegra.DropParty[stoi(x.key())].stEffect[2].cValue = nDropParty[7];

		};

		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::WriteSombraNegra(string path, string file)
{
	string fullpath = path + file;

#pragma region Txt New SombraNegra.json
	auto nJson = R"(
{
"STATUS": {

			"Days": [1,1,1,1,1,1,1],
			"StartHour": 10,
			"EndHour": 23,
			"Follow": 4,
			"String": "qwertyuiopasdfghjklçzxcvbnm",
			"NoticeStart": "Sombra Negra acaba de aparecer no Castelo de Gelo!!!",
			"NoticeEnd1": "O Grupo de [%s] dorrotou Sombra Negra!!!",
			"NoticeEnd2": "Sombra Negra desapareceu do Castelo de Gelo!!"
		  },
"BOSS": {
				"ID": 4103,
				"NAME": "Sombra Negra",
				"FACE": [174,0,0,0,0,0,0,0],
				"HELM": [1225,0,43,0,26,50,0,0],
				"BODY": [1226,0,43,0,0,0,0,0],
				"LEG": [1227,0,43,0,0,0,0,0],
				"GLOVE": [1228,0,43,0,0,0,0,0],
				"BOOT": [1229,0,43,0,0,0,0,0],
				"WEAPON": [3591,0,43,0,26,100,0,0],
				"SHIELD": [0,0,0,0,0,0,0,0],
				"PIXIE": [1936,43,5,0,0,0,0,0],
				"StartX": 3818,
				"StartY": 2880,
				"DestX": 3820,
				"DestY": 2890,
				"REGEN": 209,
				"LEVEL": 399,
				"HP": 15000,
				"MP": 5000,
				"AC": 7000,
				"DAN": 6000,
				"MAGIC": 1000,
				"STR": 5,
				"INT": 1000,
				"DEX": 8000,
				"CON": 8000,
				"MSG1": "Haa.haaa.Irei aniquilar todos....",
				"MSG2": "Haa.haaa.Saiam do meu territorio....",
				"MSG3": "graaaa.A morte te aguarda...."

		},
		
"GUARDIAN": {
				"ID": 4631,
				"NAME": "Guardian Shadow",
				"FACE": [174,0,0,0,0,0,0,0],
				"HELM": [1225,0,43,0,26,50,0,0],
				"BODY": [1226,0,43,0,0,0,0,0],
				"LEG": [1227,0,43,0,0,0,0,0],
				"GLOVE": [1228,0,43,0,0,0,0,0],
				"BOOT": [1229,0,43,0,0,0,0,0],
				"WEAPON": [3591,0,43,0,26,100,0,0],
				"SHIELD": [0,0,0,0,0,0,0,0],
				"PIXIE": [1936,43,5,0,0,0,0,0],
				"StartX": 3818,
				"StartY": 2880,
				"DestX": 3820,
				"DestY": 2890,
				"REGEN": 209,
				"LEVEL": 200,
				"HP": 34000,
				"MP": 5000,
				"AC": 5000,
				"DAN": 1000,
				"MAGIC": 1000,
				"STR": 5,
				"INT": 1000,
				"DEX": 8000,
				"CON": 12000,
				"MSG1": "Haa.haaa.Terao que nos derrotar antes de chegar em nosso Mestre....",
				"MSG2": "Haa.haaa.Saiam do nosso castelo....",
				"MSG3": "graaaa.Nao permitiremos que incomodem o Mestre...."
			},
		
"DROP": {
			"0": [412,0,61,5,0,0,0,0],
			"1": [413,0,61,5,0,0,0,0],
			"2": [4029,0,0,0,0,0,0,0],
			"3": [670,0,61,5,0,0,0,0],
			"4": [671,0,61,5,0,0,0,0],
			"5": [1741,0,61,5,0,0,0,0]
		},	

"DROPPARTY": {
				"0": [412,0,61,5,0,0,0,0],
				"1": [413,0,61,5,0,0,0,0],
				"2": [4029,0,0,0,0,0,0,0],
				"3": [670,0,61,5,0,0,0,0],
				"4": [671,0,61,5,0,0,0,0],
				"5": [412,0,61,10,0,0,0,0]
		     }			

})"_json;

#pragma endregion

	try
	{

		ofstream bjson(fullpath);
		bjson << setw(4) << nJson << std::endl;
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::ReadStatusSombraNegra(string path, string file)
{
	string fullpath = path + file;
	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	if (fp == NULL) {

		// não encontrado, será criado um novo(default) no diretorio
		int creat = WriteSombraNegra(PATH_SOMBRA_NEGRA, file);

		if (!creat)
			return creat;
	}
	try
	{
		ifstream spath(fullpath);
		json nJson;
		spath >> nJson;

		memset(&statusSombraNegra, 0, sizeof(STRUCT_STATUS_BOSS));
		string pName;
		nJson["STATUS"]["aLive"].get_to(statusSombraNegra.aLive);
		nJson["STATUS"]["PlayerKiled"].get_to(pName);
		int tLength = pName.size();
		char* nName = new char[tLength + 1];
		copy(pName.begin(), pName.end(), nName);
		nName[tLength] = '\0';
		statusSombraNegra.PlayerKiled = nName;
		nJson["STATUS"]["DayKiled"].get_to(statusSombraNegra.DayKiled);
		nJson["STATUS"]["HourKiled"].get_to(statusSombraNegra.HourKiled);
		nJson["STATUS"]["MinKiled"].get_to(statusSombraNegra.MinKiled);
	
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::WriteStatusSombraNegra(string path, string file)
{
	std::string fullpath = path + file;

	json nJson;
	try
	{
		const char* pName = statusSombraNegra.PlayerKiled ? statusSombraNegra.PlayerKiled : "NINGUEM";
		
		nJson["STATUS"]["aLive"] = statusSombraNegra.aLive;
		nJson["STATUS"]["PlayerKiled"] = pName;
		nJson["STATUS"]["DayKiled"] = statusSombraNegra.DayKiled;
		nJson["STATUS"]["HourKiled"] = statusSombraNegra.HourKiled;
		nJson["STATUS"]["MinKiled"] = statusSombraNegra.MinKiled;

		ofstream bjson(fullpath);
		bjson << setw(4) << nJson << std::endl;
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::ReadAutoBan(string path, string file)
{
	string fullpath = path + file;
	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	if (fp == NULL) 
		return FALSE;
	
	try
	{
		ifstream spath(fullpath);
		json nJson;
		spath >> nJson;

		//memset(&autoBan, 0, sizeof(STRUCT_AUTOBAN));
		nJson["BAN"]["BanType"].get_to(autoBan.BanType);
		nJson["BAN"]["Status"].get_to(autoBan.Status);

		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::WriteAutoBan(string path, string file)
{
	std::string fullpath = path + file;

	json nJson;
	try
	{
		
		nJson["BAN"]["BanType"] = autoBan.BanType;
		nJson["BAN"]["Status"] = autoBan.Status;
		ofstream bjson(fullpath);
		bjson << setw(4) << nJson << std::endl;
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::ReadStaff(string path, string file)
{
	string fullpath = path + file;
	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	if (fp == NULL) {

		// não encontrado, será criado um novo(default) no diretorio
		int creat = WriteStaff(PATH_ADM, file);

		if (!creat)
			return creat;
	}
	try
	{
		ifstream spath(fullpath);
		json nJson;
		spath >> nJson;

		memset(&StaffEternal, 0, sizeof(STRUCT_STAFF_ETERNAL));

		nJson["STAFF"]["DEV"].get_to(StaffEternal.DEV);
		nJson["STAFF"]["ADM"].get_to(StaffEternal.ADM);
		nJson["STAFF"]["GM"].get_to(StaffEternal.GM);
		
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::WriteStaff(string path, string file)
{
	std::string fullpath = path + file;

#pragma region Txt New staffList.json
	auto nJson = R"(
{
"STAFF": {
		"DEV": ["DEV-NEWS","DEV-NUNES"],
		"ADM": ["ADM-SKY","ADM-NUNES","ADM-NEWS"],
		"GM": ["","",""]
		}
})"_json;

#pragma endregion

	try
	{

		nJson["STAFF"]["DEV"] = StaffEternal.DEV;
		nJson["STAFF"]["ADM"] = StaffEternal.ADM;
		nJson["STAFF"]["GM"] = StaffEternal.GM;
		ofstream bjson(fullpath);
		bjson << setw(4) << nJson << std::endl;
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::ReadBossCamp(string path, int boss)
{
	string file;
	switch (boss)
	{
	case Freak:
		file = "freak.json";
		break;
	case Talos:
		file = "talos.json";
		break;
	case Noah:
		file = "noah.json";
		break;
	case Kirei:
		file = "kirei.json";
		break;
	default:
		break;
	}

	string fullpath = path + file;
	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	if (fp == NULL) {

		// não encontrado, será criado um novo(default) no diretorio
		int creat = WriteBossCamp(PATH_BOSS_CAMP, boss);

		if (!creat)
			return creat;
	}
	try
	{
		ifstream spath(fullpath);
		json nJson;
		spath >> nJson;

		memset(&bossCamp[boss], 0, sizeof(STRUCT_BOSS_CAMP));
		memset(&locationBossCamp[boss], 0, 4);
		
		nJson["STATUS"]["Days"].get_to(bossCamp[boss].Days);
		nJson["STATUS"]["StartHour"].get_to(bossCamp[boss].StartHour);
		nJson["STATUS"]["Follow"].get_to(bossCamp[boss].follow);
		nJson["STATUS"]["NoticeStart"].get_to(bossCamp[boss].NoticeStart);
		nJson["STATUS"]["NoticeEnd"].get_to(bossCamp[boss].NoticeEnd);
		for (auto& x : nJson["LOCATION"].items())
		{
			vector<short> nLocation = x.value();
			locationBossCamp[boss][stoi(x.key())][0] = nLocation[0];
			locationBossCamp[boss][stoi(x.key())][1] = nLocation[1];
		}
		
#pragma region  Boss	
		nJson["BOSS"]["ID"].get_to(bossCamp[boss].Boss.ID);
		//string nName;
		nJson["BOSS"]["STRING"].get_to(bossCamp[boss].Boss.NAME);
		nJson["BOSS"]["NAME"].get_to(bossCamp[boss].Boss.NAME);
		//bossCamp[boss].Boss.NAME = nName.c_str();
		vector<short> nFace;
		nJson["BOSS"]["FACE"].get_to(nFace);
		bossCamp[boss].Boss.FACE.sIndex = nFace[0];
		bossCamp[boss].Boss.FACE.stEffect->sValue = nFace[1];
		bossCamp[boss].Boss.FACE.stEffect[0].cEffect = nFace[2];
		bossCamp[boss].Boss.FACE.stEffect[0].cValue = nFace[3];
		bossCamp[boss].Boss.FACE.stEffect[1].cEffect = nFace[4];
		bossCamp[boss].Boss.FACE.stEffect[1].cValue = nFace[5];
		bossCamp[boss].Boss.FACE.stEffect[2].cEffect = nFace[6];
		bossCamp[boss].Boss.FACE.stEffect[2].cValue = nFace[7];

		vector<short> nHelm;
		nJson["BOSS"]["HELM"].get_to(nHelm);
		bossCamp[boss].Boss.HELM.sIndex = nHelm[0];
		bossCamp[boss].Boss.HELM.stEffect->sValue = nHelm[1];
		bossCamp[boss].Boss.HELM.stEffect[0].cEffect = nHelm[2];
		bossCamp[boss].Boss.HELM.stEffect[0].cValue = nHelm[3];
		bossCamp[boss].Boss.HELM.stEffect[1].cEffect = nHelm[4];
		bossCamp[boss].Boss.HELM.stEffect[1].cValue = nHelm[5];
		bossCamp[boss].Boss.HELM.stEffect[2].cEffect = nHelm[6];
		bossCamp[boss].Boss.HELM.stEffect[2].cValue = nHelm[7];

		vector<short> nBody;
		nJson["BOSS"]["BODY"].get_to(nBody);
		bossCamp[boss].Boss.BODY.sIndex = nBody[0];
		bossCamp[boss].Boss.BODY.stEffect->sValue = nBody[1];
		bossCamp[boss].Boss.BODY.stEffect[0].cEffect = nBody[2];
		bossCamp[boss].Boss.BODY.stEffect[0].cValue = nBody[3];
		bossCamp[boss].Boss.BODY.stEffect[1].cEffect = nBody[4];
		bossCamp[boss].Boss.BODY.stEffect[1].cValue = nBody[5];
		bossCamp[boss].Boss.BODY.stEffect[2].cEffect = nBody[6];
		bossCamp[boss].Boss.BODY.stEffect[2].cValue = nBody[7];

		vector<short> nLeg;
		nJson["BOSS"]["LEG"].get_to(nLeg);
		bossCamp[boss].Boss.LEG.sIndex = nLeg[0];
		bossCamp[boss].Boss.LEG.stEffect->sValue = nLeg[1];
		bossCamp[boss].Boss.LEG.stEffect[0].cEffect = nLeg[2];
		bossCamp[boss].Boss.LEG.stEffect[0].cValue = nLeg[3];
		bossCamp[boss].Boss.LEG.stEffect[1].cEffect = nLeg[4];
		bossCamp[boss].Boss.LEG.stEffect[1].cValue = nLeg[5];
		bossCamp[boss].Boss.LEG.stEffect[2].cEffect = nLeg[6];
		bossCamp[boss].Boss.LEG.stEffect[2].cValue = nLeg[7];

		vector<short> nGlove;
		nJson["BOSS"]["GLOVE"].get_to(nGlove);
		bossCamp[boss].Boss.GLOVE.sIndex = nGlove[0];
		bossCamp[boss].Boss.GLOVE.stEffect->sValue = nGlove[1];
		bossCamp[boss].Boss.GLOVE.stEffect[0].cEffect = nGlove[2];
		bossCamp[boss].Boss.GLOVE.stEffect[0].cValue = nGlove[3];
		bossCamp[boss].Boss.GLOVE.stEffect[1].cEffect = nGlove[4];
		bossCamp[boss].Boss.GLOVE.stEffect[1].cValue = nGlove[5];
		bossCamp[boss].Boss.GLOVE.stEffect[2].cEffect = nGlove[6];
		bossCamp[boss].Boss.GLOVE.stEffect[2].cValue = nGlove[7];

		vector<short> nBoot;
		nJson["BOSS"]["BOOT"].get_to(nBoot);
		bossCamp[boss].Boss.BOOT.sIndex = nBoot[0];
		bossCamp[boss].Boss.BOOT.stEffect->sValue = nBoot[1];
		bossCamp[boss].Boss.BOOT.stEffect[0].cEffect = nBoot[2];
		bossCamp[boss].Boss.BOOT.stEffect[0].cValue = nBoot[3];
		bossCamp[boss].Boss.BOOT.stEffect[1].cEffect = nBoot[4];
		bossCamp[boss].Boss.BOOT.stEffect[1].cValue = nBoot[5];
		bossCamp[boss].Boss.BOOT.stEffect[2].cEffect = nBoot[6];
		bossCamp[boss].Boss.BOOT.stEffect[2].cValue = nBoot[7];

		vector<short> nWeapon;
		nJson["BOSS"]["WEAPON"].get_to(nWeapon);
		bossCamp[boss].Boss.WEAPON.sIndex = nWeapon[0];
		bossCamp[boss].Boss.WEAPON.stEffect->sValue = nWeapon[1];
		bossCamp[boss].Boss.WEAPON.stEffect[0].cEffect = nWeapon[2];
		bossCamp[boss].Boss.WEAPON.stEffect[0].cValue = nWeapon[3];
		bossCamp[boss].Boss.WEAPON.stEffect[1].cEffect = nWeapon[4];
		bossCamp[boss].Boss.WEAPON.stEffect[1].cValue = nWeapon[5];
		bossCamp[boss].Boss.WEAPON.stEffect[2].cEffect = nWeapon[6];
		bossCamp[boss].Boss.WEAPON.stEffect[2].cValue = nWeapon[7];

		vector<short> nShield;
		nJson["BOSS"]["SHIELD"].get_to(nShield);
		bossCamp[boss].Boss.SHIELD.sIndex = nShield[0];
		bossCamp[boss].Boss.SHIELD.stEffect->sValue = nShield[1];
		bossCamp[boss].Boss.SHIELD.stEffect[0].cEffect = nShield[2];
		bossCamp[boss].Boss.SHIELD.stEffect[0].cValue = nShield[3];
		bossCamp[boss].Boss.SHIELD.stEffect[1].cEffect = nShield[4];
		bossCamp[boss].Boss.SHIELD.stEffect[1].cValue = nShield[5];
		bossCamp[boss].Boss.SHIELD.stEffect[2].cEffect = nShield[6];
		bossCamp[boss].Boss.SHIELD.stEffect[2].cValue = nShield[7];

		vector<short> nPixie;
		nJson["BOSS"]["PIXIE"].get_to(nPixie);
		bossCamp[boss].Boss.PIXIE.sIndex = nPixie[0];
		bossCamp[boss].Boss.PIXIE.stEffect->sValue = nPixie[1];
		bossCamp[boss].Boss.PIXIE.stEffect[0].cEffect = nPixie[2];
		bossCamp[boss].Boss.PIXIE.stEffect[0].cValue = nPixie[3];
		bossCamp[boss].Boss.PIXIE.stEffect[1].cEffect = nPixie[4];
		bossCamp[boss].Boss.PIXIE.stEffect[1].cValue = nPixie[5];
		bossCamp[boss].Boss.PIXIE.stEffect[2].cEffect = nPixie[6];
		bossCamp[boss].Boss.PIXIE.stEffect[2].cValue = nPixie[7];

		nJson["BOSS"]["StartX"].get_to(bossCamp[boss].Boss.StartX);
		nJson["BOSS"]["StartY"].get_to(bossCamp[boss].Boss.StartY);
		nJson["BOSS"]["DestX"].get_to(bossCamp[boss].Boss.DestX);
		nJson["BOSS"]["DestY"].get_to(bossCamp[boss].Boss.DestY);
		nJson["BOSS"]["REGEN"].get_to(bossCamp[boss].Boss.REGEN);
		nJson["BOSS"]["LEVEL"].get_to(bossCamp[boss].Boss.LEVEL);
		nJson["BOSS"]["HP"].get_to(bossCamp[boss].Boss.HP);
		nJson["BOSS"]["MP"].get_to(bossCamp[boss].Boss.MP);
		nJson["BOSS"]["AC"].get_to(bossCamp[boss].Boss.AC);
		nJson["BOSS"]["DAN"].get_to(bossCamp[boss].Boss.DAN);
		nJson["BOSS"]["MAGIC"].get_to(bossCamp[boss].Boss.MAGI);
		nJson["BOSS"]["STR"].get_to(bossCamp[boss].Boss.STR);
		nJson["BOSS"]["INT"].get_to(bossCamp[boss].Boss.INT);
		nJson["BOSS"]["DEX"].get_to(bossCamp[boss].Boss.DEX);
		nJson["BOSS"]["CON"].get_to(bossCamp[boss].Boss.CON);
		nJson["BOSS"]["MSG1"].get_to(bossCamp[boss].Boss.MSG1);
		nJson["BOSS"]["MSG2"].get_to(bossCamp[boss].Boss.MSG2);
		nJson["BOSS"]["MSG3"].get_to(bossCamp[boss].Boss.MSG3);

#pragma endregion

#pragma region Guardian
		nJson["GUARDIAN"]["ID"].get_to(bossCamp[boss].Guardian.ID);
		//string gName;
		nJson["GUARDIAN"]["NAME"].get_to(bossCamp[boss].Guardian.NAME);
		//bossCamp[boss].Guardian.NAME = gName.c_str();
		memset(&nFace, 0, 8);
		nJson["GUARDIAN"]["FACE"].get_to(nFace);
		bossCamp[boss].Guardian.FACE.sIndex = nFace[0];
		bossCamp[boss].Guardian.FACE.stEffect->sValue = nFace[1];
		bossCamp[boss].Guardian.FACE.stEffect[0].cEffect = nFace[2];
		bossCamp[boss].Guardian.FACE.stEffect[0].cValue = nFace[3];
		bossCamp[boss].Guardian.FACE.stEffect[1].cEffect = nFace[4];
		bossCamp[boss].Guardian.FACE.stEffect[1].cValue = nFace[5];
		bossCamp[boss].Guardian.FACE.stEffect[2].cEffect = nFace[6];
		bossCamp[boss].Guardian.FACE.stEffect[2].cValue = nFace[7];

		memset(&nHelm, 0, 8);
		nJson["GUARDIAN"]["HELM"].get_to(nHelm);
		bossCamp[boss].Guardian.HELM.sIndex = nHelm[0];
		bossCamp[boss].Guardian.HELM.stEffect->sValue = nHelm[1];
		bossCamp[boss].Guardian.HELM.stEffect[0].cEffect = nHelm[2];
		bossCamp[boss].Guardian.HELM.stEffect[0].cValue = nHelm[3];
		bossCamp[boss].Guardian.HELM.stEffect[1].cEffect = nHelm[4];
		bossCamp[boss].Guardian.HELM.stEffect[1].cValue = nHelm[5];
		bossCamp[boss].Guardian.HELM.stEffect[2].cEffect = nHelm[6];
		bossCamp[boss].Guardian.HELM.stEffect[2].cValue = nHelm[7];

		memset(&nBody, 0, 8);
		nJson["GUARDIAN"]["BODY"].get_to(nBody);
		bossCamp[boss].Guardian.BODY.sIndex = nBody[0];
		bossCamp[boss].Guardian.BODY.stEffect->sValue = nBody[1];
		bossCamp[boss].Guardian.BODY.stEffect[0].cEffect = nBody[2];
		bossCamp[boss].Guardian.BODY.stEffect[0].cValue = nBody[3];
		bossCamp[boss].Guardian.BODY.stEffect[1].cEffect = nBody[4];
		bossCamp[boss].Guardian.BODY.stEffect[1].cValue = nBody[5];
		bossCamp[boss].Guardian.BODY.stEffect[2].cEffect = nBody[6];
		bossCamp[boss].Guardian.BODY.stEffect[2].cValue = nBody[7];

		memset(&nLeg, 0, 8);
		nJson["GUARDIAN"]["LEG"].get_to(nLeg);
		bossCamp[boss].Guardian.LEG.sIndex = nLeg[0];
		bossCamp[boss].Guardian.LEG.stEffect->sValue = nLeg[1];
		bossCamp[boss].Guardian.LEG.stEffect[0].cEffect = nLeg[2];
		bossCamp[boss].Guardian.LEG.stEffect[0].cValue = nLeg[3];
		bossCamp[boss].Guardian.LEG.stEffect[1].cEffect = nLeg[4];
		bossCamp[boss].Guardian.LEG.stEffect[1].cValue = nLeg[5];
		bossCamp[boss].Guardian.LEG.stEffect[2].cEffect = nLeg[6];
		bossCamp[boss].Guardian.LEG.stEffect[2].cValue = nLeg[7];

		memset(&nGlove, 0, 8);
		nJson["GUARDIAN"]["GLOVE"].get_to(nGlove);
		bossCamp[boss].Guardian.GLOVE.sIndex = nGlove[0];
		bossCamp[boss].Guardian.GLOVE.stEffect->sValue = nGlove[1];
		bossCamp[boss].Guardian.GLOVE.stEffect[0].cEffect = nGlove[2];
		bossCamp[boss].Guardian.GLOVE.stEffect[0].cValue = nGlove[3];
		bossCamp[boss].Guardian.GLOVE.stEffect[1].cEffect = nGlove[4];
		bossCamp[boss].Guardian.GLOVE.stEffect[1].cValue = nGlove[5];
		bossCamp[boss].Guardian.GLOVE.stEffect[2].cEffect = nGlove[6];
		bossCamp[boss].Guardian.GLOVE.stEffect[2].cValue = nGlove[7];

		memset(&nBoot, 0, 8);
		nJson["GUARDIAN"]["BOOT"].get_to(nBoot);
		bossCamp[boss].Guardian.BOOT.sIndex = nBoot[0];
		bossCamp[boss].Guardian.BOOT.stEffect->sValue = nBoot[1];
		bossCamp[boss].Guardian.BOOT.stEffect[0].cEffect = nBoot[2];
		bossCamp[boss].Guardian.BOOT.stEffect[0].cValue = nBoot[3];
		bossCamp[boss].Guardian.BOOT.stEffect[1].cEffect = nBoot[4];
		bossCamp[boss].Guardian.BOOT.stEffect[1].cValue = nBoot[5];
		bossCamp[boss].Guardian.BOOT.stEffect[2].cEffect = nBoot[6];
		bossCamp[boss].Guardian.BOOT.stEffect[2].cValue = nBoot[7];

		memset(&nWeapon, 0, 8);
		nJson["GUARDIAN"]["WEAPON"].get_to(nWeapon);
		bossCamp[boss].Guardian.WEAPON.sIndex = nWeapon[0];
		bossCamp[boss].Guardian.WEAPON.stEffect->sValue = nWeapon[1];
		bossCamp[boss].Guardian.WEAPON.stEffect[0].cEffect = nWeapon[2];
		bossCamp[boss].Guardian.WEAPON.stEffect[0].cValue = nWeapon[3];
		bossCamp[boss].Guardian.WEAPON.stEffect[1].cEffect = nWeapon[4];
		bossCamp[boss].Guardian.WEAPON.stEffect[1].cValue = nWeapon[5];
		bossCamp[boss].Guardian.WEAPON.stEffect[2].cEffect = nWeapon[6];
		bossCamp[boss].Guardian.WEAPON.stEffect[2].cValue = nWeapon[7];

		memset(&nShield, 0, 8);
		nJson["GUARDIAN"]["SHIELD"].get_to(nShield);
		bossCamp[boss].Guardian.SHIELD.sIndex = nShield[0];
		bossCamp[boss].Guardian.SHIELD.stEffect->sValue = nShield[1];
		bossCamp[boss].Guardian.SHIELD.stEffect[0].cEffect = nShield[2];
		bossCamp[boss].Guardian.SHIELD.stEffect[0].cValue = nShield[3];
		bossCamp[boss].Guardian.SHIELD.stEffect[1].cEffect = nShield[4];
		bossCamp[boss].Guardian.SHIELD.stEffect[1].cValue = nShield[5];
		bossCamp[boss].Guardian.SHIELD.stEffect[2].cEffect = nShield[6];
		bossCamp[boss].Guardian.SHIELD.stEffect[2].cValue = nShield[7];

		memset(&nPixie, 0, 8);
		nJson["BOSS"]["PIXIE"].get_to(nPixie);
		bossCamp[boss].Guardian.PIXIE.sIndex = nPixie[0];
		bossCamp[boss].Guardian.PIXIE.stEffect->sValue = nPixie[1];
		bossCamp[boss].Guardian.PIXIE.stEffect[0].cEffect = nPixie[2];
		bossCamp[boss].Guardian.PIXIE.stEffect[0].cValue = nPixie[3];
		bossCamp[boss].Guardian.PIXIE.stEffect[1].cEffect = nPixie[4];
		bossCamp[boss].Guardian.PIXIE.stEffect[1].cValue = nPixie[5];
		bossCamp[boss].Guardian.PIXIE.stEffect[2].cEffect = nPixie[6];
		bossCamp[boss].Guardian.PIXIE.stEffect[2].cValue = nPixie[7];

		nJson["GUARDIAN"]["StartX"].get_to(bossCamp[boss].Guardian.StartX);
		nJson["GUARDIAN"]["StartY"].get_to(bossCamp[boss].Guardian.StartY);
		nJson["GUARDIAN"]["DestX"].get_to(bossCamp[boss].Guardian.DestX);
		nJson["GUARDIAN"]["DestY"].get_to(bossCamp[boss].Guardian.DestY);
		nJson["GUARDIAN"]["REGEN"].get_to(bossCamp[boss].Guardian.REGEN);
		nJson["GUARDIAN"]["LEVEL"].get_to(bossCamp[boss].Guardian.LEVEL);
		nJson["GUARDIAN"]["HP"].get_to(bossCamp[boss].Guardian.HP);
		nJson["GUARDIAN"]["MP"].get_to(bossCamp[boss].Guardian.MP);
		nJson["GUARDIAN"]["AC"].get_to(bossCamp[boss].Guardian.AC);
		nJson["GUARDIAN"]["DAN"].get_to(bossCamp[boss].Guardian.DAN);
		nJson["GUARDIAN"]["MAGIC"].get_to(bossCamp[boss].Guardian.MAGI);
		nJson["GUARDIAN"]["STR"].get_to(bossCamp[boss].Guardian.STR);
		nJson["GUARDIAN"]["INT"].get_to(bossCamp[boss].Guardian.INT);
		nJson["GUARDIAN"]["DEX"].get_to(bossCamp[boss].Guardian.DEX);
		nJson["GUARDIAN"]["CON"].get_to(bossCamp[boss].Guardian.CON);
		nJson["GUARDIAN"]["MSG1"].get_to(bossCamp[boss].Guardian.MSG1);
		nJson["GUARDIAN"]["MSG2"].get_to(bossCamp[boss].Guardian.MSG2);
		nJson["GUARDIAN"]["MSG3"].get_to(bossCamp[boss].Guardian.MSG3);
#pragma endregion

		for (auto& x : nJson["DROP"].items())
		{

			vector<short> nDrop = x.value();
			bossCamp[boss].Drop[stoi(x.key())].sIndex = nDrop[0];
			bossCamp[boss].Drop[stoi(x.key())].stEffect->sValue = nDrop[1];
			bossCamp[boss].Drop[stoi(x.key())].stEffect[0].cEffect = nDrop[2];
			bossCamp[boss].Drop[stoi(x.key())].stEffect[0].cValue = nDrop[3];
			bossCamp[boss].Drop[stoi(x.key())].stEffect[1].cEffect = nDrop[4];
			bossCamp[boss].Drop[stoi(x.key())].stEffect[1].cValue = nDrop[5];
			bossCamp[boss].Drop[stoi(x.key())].stEffect[2].cEffect = nDrop[6];
			bossCamp[boss].Drop[stoi(x.key())].stEffect[2].cValue = nDrop[7];

		};

		for (auto& x : nJson["DROPPARTY"].items())
		{

			vector<short> nDropParty = x.value();
			bossCamp[boss].DropParty[stoi(x.key())].sIndex = nDropParty[0];
			bossCamp[boss].DropParty[stoi(x.key())].stEffect->sValue = nDropParty[1];
			bossCamp[boss].DropParty[stoi(x.key())].stEffect[0].cEffect = nDropParty[2];
			bossCamp[boss].DropParty[stoi(x.key())].stEffect[0].cValue = nDropParty[3];
			bossCamp[boss].DropParty[stoi(x.key())].stEffect[1].cEffect = nDropParty[4];
			bossCamp[boss].DropParty[stoi(x.key())].stEffect[1].cValue = nDropParty[5];
			bossCamp[boss].DropParty[stoi(x.key())].stEffect[2].cEffect = nDropParty[6];
			bossCamp[boss].DropParty[stoi(x.key())].stEffect[2].cValue = nDropParty[7];

		};

		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::WriteBossCamp(string path, int boss)
{
	string file;
	switch (boss)
	{
		case Freak:
			file = "freak.json";
			break;
		case Talos:
			file = "talos.json";
			break;
		case Noah:
			file = "noah.json";
			break;
		case Kirei:
			file = "kirei.json";
			break;
		default:
			break;
	}
	string fullpath = path + file;

#pragma region Txt New BossCamp
	auto nJson = R"(
{
"STATUS": {

			"Days": [1,1,1,1,1,1,1],
			"StartHour": [0,5,10,15,20],
			"Follow": 4,
			"NoticeStart": "BossCamp apareceu.",
			"NoticeEnd": "O Grupo de [%s] dorrotou BossCamp!!!"
		  },
"LOCATION": {
			"0": [2503,1937],
			"1": [2609,2035],
			"2": [2453,2118],
			"3": [2277,2088]
		},
"BOSS": {
				"ID": 4638,
				"STRING": "qwertyuiopasdfghjklçzxcvbnm",
				"NAME": "BossCamp",
				"FACE": [346,0,43,9,0,0,0,0],
				"HELM": [0,0,0,0,0,0,0,0],
				"BODY": [0,0,0,0,0,0,0,0],
				"LEG": [0,0,0,0,0,0,0,0],
				"GLOVE": [0,0,0,0,0,0,0,0],
				"BOOT": [0,0,0,0,0,0,0,0],
				"WEAPON": [0,0,0,0,0,0,0,0],
				"SHIELD": [0,0,0,0,0,0,0,0],
				"PIXIE": [1936,0,5,0,0,0,0,0],
				"StartX": 0,
				"StartY": 0,
				"DestX": 0,
				"DestY": 0,
				"REGEN": 209,
				"LEVEL": 200,
				"HP": 5000,
				"MP": 200,
				"AC": 3000,
				"DAN": 3000,
				"MAGIC": 500,
				"STR": 1000,
				"INT": 1000,
				"DEX": 2000,
				"CON": 8000,
				"MSG1": "Haa.haaa.Sinto cheiro de virgemmmmm....",
				"MSG2": "Haa.haaa.Ser abominavel saia daqui....",
				"MSG3": "graaaa.Insetos malditos...."

		},
		
"GUARDIAN": {
				"ID": 4638,
				"NAME": "BossCamp_",
				"FACE": [346,0,0,0,0,0,0,0],
				"HELM": [0,0,0,0,0,0,0,0],
				"BODY": [0,0,0,0,0,0,0,0],
				"LEG": [0,0,0,0,0,0,0,0],
				"GLOVE": [0,0,0,0,0,0,0,0],
				"BOOT": [0,0,0,0,0,0,0,0],
				"WEAPON": [0,0,0,0,0,0,0,0],
				"SHIELD": [0,0,0,0,0,0,0,0],
				"PIXIE": [1936,43,1,0,0,0,0,0],
				"StartX": 0,
				"StartY": 0,
				"DestX": 0,
				"DestY": 0,
				"REGEN": 209,
				"LEVEL": 150,
				"HP": 2000,
				"MP": 100,
				"AC": 500,
				"DAN": 500,
				"MAGIC": 20,
				"STR": 50,
				"INT": 60,
				"DEX": 800,
				"CON": 3000,
				"MSG1": "Haa.haaa.Terao que nos derrotar antes de chegar em nosso Mestre....",
				"MSG2": "Haa.haaa.Saiam daqui....",
				"MSG3": "graaaa.Nao permitiremos que incomodem o Mestre...."
			},
		
"DROP": {
			"0": [412,0,61,5,0,0,0,0],
			"1": [413,0,61,5,0,0,0,0],
			"2": [4029,0,0,0,0,0,0,0],
			"3": [670,0,61,5,0,0,0,0],
			"4": [671,0,61,5,0,0,0,0],
			"5": [1741,0,61,5,0,0,0,0]
		},	

"DROPPARTY": {
				"0": [412,0,61,5,0,0,0,0],
				"1": [413,0,61,5,0,0,0,0],
				"2": [4029,0,0,0,0,0,0,0],
				"3": [670,0,61,5,0,0,0,0],
				"4": [671,0,61,5,0,0,0,0],
				"5": [412,0,61,10,0,0,0,0]
		     }			

})"_json;

#pragma endregion

	try
	{

		ofstream bjson(fullpath);
		bjson << setw(4) << nJson << std::endl;
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::ReadStatusBossCamp(string path, int boss)
{
	string file;
	switch (boss)
	{
	case Freak:
		file = "statusFreak.json";
		break;
	case Talos:
		file = "statusTalos.json";
		break;
	case Noah:
		file = "statusNoah.json";
		break;
	case Kirei:
		file = "statusKirei.json";
		break;
	default:
		break;
	}

	string fullpath = path + file;
	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	if (fp == NULL) {

		// não encontrado, será criado um novo(default) no diretorio
		int creat = WriteStatusBossCamp(PATH_BOSS_CAMP, boss);

		if (!creat)
			return creat;
	}
	try
	{
		ifstream spath(fullpath);
		json nJson;
		spath >> nJson;

		memset(&statusBossCamp[boss], 0, sizeof(STRUCT_STATUS_BOSS));
		string pName;
		nJson["STATUS"]["aLive"].get_to(statusBossCamp[boss].aLive);
		nJson["STATUS"]["PlayerKiled"].get_to(pName);
		int tLength = pName.size();
		char* nName = new char[tLength + 1];
		copy(pName.begin(), pName.end(), nName);
		nName[tLength] = '\0';
		statusBossCamp[boss].PlayerKiled = nName;
		nJson["STATUS"]["DayKiled"].get_to(statusBossCamp[boss].DayKiled);
		nJson["STATUS"]["HourKiled"].get_to(statusBossCamp[boss].HourKiled);
		nJson["STATUS"]["MinKiled"].get_to(statusBossCamp[boss].MinKiled);

		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::WriteStatusBossCamp(string path, int boss)
{
	string file;
	switch (boss)
	{
	case Freak:
		file = "statusFreak.json";
		break;
	case Talos:
		file = "statusTalos.json";
		break;
	case Noah:
		file = "statusNoah.json";
		break;
	case Kirei:
		file = "statusKirei.json";
		break;
	default:
		break;
	}

	std::string fullpath = path + file;

	json nJson;
	try
	{
		const char* pName = statusBossCamp[boss].PlayerKiled ? statusBossCamp[boss].PlayerKiled : "NINGUEM";

		nJson["STATUS"]["aLive"] = statusBossCamp[boss].aLive;
		nJson["STATUS"]["PlayerKiled"] = pName;
		nJson["STATUS"]["DayKiled"] = statusBossCamp[boss].DayKiled;
		nJson["STATUS"]["HourKiled"] = statusBossCamp[boss].HourKiled;
		nJson["STATUS"]["MinKiled"] = statusBossCamp[boss].MinKiled;

		ofstream bjson(fullpath);
		bjson << setw(4) << nJson << std::endl;
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::ReadAccoutSaveBuff(string path, string file)
{
	string fullpath = path + file;
	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	if (fp == NULL) {

		// não encontrado, será criado um novo(default) no diretorio
		int creat = WriteAccountSaveBuff(PATH_SAVEBUFF, file);

		if (!creat)
			return creat;
	}
	try
	{
		ifstream spath(fullpath);
		json nJson;
		spath >> nJson;

		memset(&AccountSaveBuff, 0, MAX_SAVE_BUFF);

		nJson["BUFF"]["SAUDE"].get_to(AccountSaveBuff[0]);
		nJson["BUFF"]["SEPHIRA"].get_to(AccountSaveBuff[1]);
		nJson["BUFF"]["BOXEXP"].get_to(AccountSaveBuff[2]);
		nJson["BUFF"]["PVM"].get_to(AccountSaveBuff[3]);
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::WriteAccountSaveBuff(string path, string file)
{
	std::string fullpath = path + file;

#pragma region Txt New AccountBuff.json
	auto nJson = R"(
{
"BUFF": {
		"SAUDE": 0,
		"SEPHIRA": 0,
		"BOXEXP": 0,
		"PVM": 0
		}
})"_json;

#pragma endregion

	try
	{
		nJson["BUFF"]["SAUDE"] = AccountSaveBuff[0];
		nJson["BUFF"]["SEPHIRA"] = AccountSaveBuff[1];
		nJson["BUFF"]["BOXEXP"] = AccountSaveBuff[2];
		nJson["BUFF"]["PVM"] = AccountSaveBuff[3];
		ofstream bjson(fullpath);
		bjson << setw(4) << nJson << std::endl;
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::ReadTitleSystem(string path, string file)
{
	string fullpath = path + file;
	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	if (fp == NULL) {

		// não encontrado, será criado um novo(default) no diretorio
		int creat = WriteTitSystem(PATH_TITLE_SYSTEM, file,"NONE",FALSE);

		if (!creat)
			return creat;
	}
	try
	{
		ifstream spath(fullpath);
		json nJson;
		spath >> nJson;

		memset(&TitlePlayer, 0, sizeof(STRUCT_TITLE_PLAYER));

	
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::WriteTitSystem(string path, string file, string Name, unsigned int ativa)
{
	std::string fullpath = path + file;

#pragma region Txt New TitleSystem.json
	auto nJson = R"(
{
		"LEVEL": {
				 "NOVATO": {
							"Status": 0,
							"Conquest": 0
						   },
				"EXPLORADOR": {
							"Status": 0,
							"Conquest": 0
						   },
				"PERITO": {
							"Status": 0,
							"Conquest": 0
						   },
				"VETERANO": {
							"Status": 0,
							"Conquest": 0
						   },
				"MORTAL": {
							"Status": 0,
							"Conquest": 0
						   },

				 "MISTICO": {
							"Status": 0,
							"Conquest": 0
						   },
				"ARCANO": {
							"Status": 0,
							"Conquest": 0
						   },
				"PESADELO": {
							"Status": 0,
							"Conquest": 0
						   },
				"ARCH": {
							"Status": 0,
							"Conquest": 0
						   },
				"SUPREMO": {
							"Status": 0,
							"Conquest": 0
						   }
				
				}
		
})"_json;

#pragma endregion

	try
	{
		for (size_t i = 0; i < tMaxTitle; i++)
		{
			string titleName = "";
			switch (i)
			{
			case tNOVATO:
				titleName = "NOVATO";
				break;
			case tEXPLORADOR:
				titleName = "EXPLORADOR";
				break;
			case tPERITO:
				titleName = "PERITO";
				break;
			case tVETERANO:
				titleName = "VETERANO";
				break;
			case tMORTAL:
				titleName = "MORTAL";
				break;
			case tMISTICO:
				titleName = "MISTICO";
				break;
			case tARCANO:
				titleName = "ARCANO";
				break;
			case tPESADELO:
				titleName = "PESADELO";
				break;
			case tARCH:
				titleName = "ARCH";
				break;
			case tSUPREMO:
				titleName = "SUPREMO";
				break;
			default:
				break;
			}
			
			if (!strcmp(titleName.c_str(), Name.c_str()))
			{
				nJson["LEVEL"][titleName].find("Status").value() = ativa;
			}
			
			

		}
		ofstream bjson(fullpath);
		bjson << setw(4) << nJson << std::endl;
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int nConfig::ReadGameConfig(string path, string file)
{
	string fullpath = path + file;
	short itemDropBonus[64];
	STRUCT_TREASURE treasure[8];
	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	if (fp == NULL) {

		//gameConfig.json não encontrado, será criado um novo(default) no diretorio config/
		int creat = WriteGameConfig(PATH_CONFIG, "gameConfig.json");

		if (!creat)
			return creat;
	}

	try
	{
		ifstream spath(fullpath);
		json nJson;
		spath >> nJson;

		memset(gameConfig, 0, sizeof(gameConfig));

		//case DROP_ITEM_EVENT:
		nJson["DROP_ITEM_EVENT"]["evIndex"].get_to(gameConfig[DROP_ITEM_EVENT][0]);
		nJson["DROP_ITEM_EVENT"]["evDelete"].get_to(gameConfig[DROP_ITEM_EVENT][1]);
		nJson["DROP_ITEM_EVENT"]["evOn"].get_to(gameConfig[DROP_ITEM_EVENT][2]);
		nJson["DROP_ITEM_EVENT"]["evItem"].get_to(gameConfig[DROP_ITEM_EVENT][3]);
		nJson["DROP_ITEM_EVENT"]["evRate"].get_to(gameConfig[DROP_ITEM_EVENT][4]);
		nJson["DROP_ITEM_EVENT"]["evStartIndex"].get_to(gameConfig[DROP_ITEM_EVENT][5]);
		nJson["DROP_ITEM_EVENT"]["evCurrentIndex"].get_to(gameConfig[DROP_ITEM_EVENT][6]);
		nJson["DROP_ITEM_EVENT"]["evEndIndex"].get_to(gameConfig[DROP_ITEM_EVENT][7]);
		nJson["DROP_ITEM_EVENT"]["evNotice"].get_to(gameConfig[DROP_ITEM_EVENT][8]);

		//case ETC_EVENT:
		nJson["ETC_EVENT"]["DOUBLEMODE"].get_to(gameConfig[ETC_EVENT][0]);
		nJson["ETC_EVENT"]["DEADPOINT"].get_to(gameConfig[ETC_EVENT][1]);
		nJson["ETC_EVENT"]["DUNGEONEVENT"].get_to(gameConfig[ETC_EVENT][2]);
		nJson["ETC_EVENT"]["StatSpapphire"].get_to(gameConfig[ETC_EVENT][3]);
		nJson["ETC_EVENT"]["BatleRoyalItem"].get_to(gameConfig[ETC_EVENT][4]);

		//case nBILLING:
		nJson["BILLING"]["BILLING"].get_to(gameConfig[nBILLING][0]);
		nJson["BILLING"]["FREEEXP"].get_to(gameConfig[nBILLING][1]);
		nJson["BILLING"]["CHARSELBILL"].get_to(gameConfig[nBILLING][2]);
		nJson["BILLING"]["POTIONCOUNT"].get_to(gameConfig[nBILLING][3]);
		nJson["BILLING"]["PARTYBONUS"].get_to(gameConfig[nBILLING][4]);
		nJson["BILLING"]["GUILDBOARD"].get_to(gameConfig[nBILLING][5]);

		//case ITEM_DROP_BONUS:
		nJson["ITEM_DROP_BONUS"].get_to(itemDropBonus);
		memmove(&gameConfig[ITEM_DROP_BONUS], &itemDropBonus, sizeof(itemDropBonus));

		//case TREASURE:
		for (auto& x : nJson["TREASURE"].items())
		{
			for (auto& e : x.value().items())
			{
				vector<short> ntreasure = e.value();

				treasure->Source = stoi(x.key());
				treasure->Rate[stoi(e.key())] = ntreasure[5];
				treasure->Target[stoi(e.key())].sIndex = ntreasure[0];
				treasure->Target[stoi(e.key())].stEffect[0].cEffect = ntreasure[1];
				treasure->Target[stoi(e.key())].stEffect[0].cValue = ntreasure[2];
				treasure->Target[stoi(e.key())].stEffect[1].cEffect = ntreasure[3];
				treasure->Target[stoi(e.key())].stEffect[1].cValue = ntreasure[4];
				//	memmove(&treasure[stoi(x.key())][stoi(e.key())], &ntreasure, sizeof(ntreasure));
			}

			memmove(&ng_pTreasure[stoi(x.key())], &treasure, sizeof(STRUCT_TREASURE));

		};

		//case OTHER:
		nJson["OTHER"]["PARTY_DIF"].get_to(gameConfig[OTHER][0]);
		nJson["OTHER"]["KefraLive"].get_to(gameConfig[OTHER][1]);
		nJson["OTHER"]["GTorreHour"].get_to(gameConfig[OTHER][2]);
		nJson["OTHER"]["isDropItem"].get_to(gameConfig[OTHER][3]);
		nJson["OTHER"]["BableRoyalRHour"].get_to(gameConfig[OTHER][4]);
		nJson["OTHER"]["maxNightmare"].get_to(gameConfig[OTHER][5]);
		nJson["OTHER"]["PotionDelay"].get_to(gameConfig[OTHER][6]);


		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int nConfig::WriteGameConfig(string path, string file)
{

	std::string fullpath = path + file;

#pragma region Txt New gameConfig.json
	auto nJson = R"(
{
"DROP_ITEM_EVENT": {
					"evIndex": 1,
					"evDelete": 0,
					"evOn": 0,
					"evItem": 4026,
					"evRate": 40,
					"evStartIndex": 1,
					"evCurrentIndex": 0,
					"evEndIndex": 30000,
					"evNotice": 1
				   },
"ETC_EVENT": {
				"DOUBLEMODE": 1,
				"DEADPOINT": 1,
				"DUNGEONEVENT": 0,
				"StatSpapphire": 30,
				"BatleRoyalItem": 0
			},
"BILLING": {
			"BILLING": 0,
			"FREEEXP": 35,
			"CHARSELBILL": 0,
			"POTIONCOUNT": 100,
			"PARTYBONUS": 82,
			"GUILDBOARD": 0
		   },
"ITEM_DROP_BONUS": [
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100,
					100
				  ],
"TREASURE": {
				"0": [
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0]
					],
				"1": [
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0]
					],
				"2": [
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0]
					],
				"3": [
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0]
					],
				"4": [
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0]
					],
				"5": [
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0]
					],
				"6": [
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0]
					],
				"7": [
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0],
						[0,0,0,0,0,0]
					 ]
			},
"OTHER": {
		"PARTY_DIF": 200,
		"KefraLive": 0,
		"GTorreHour": 21,
		"isDropItem": 0,
		"BableRoyalRHour": 19,
		"maxNightmare": 3,
		"PotionDelay": 500
	  }

})"_json;

#pragma endregion

	//case nBILLING:
	nJson["BILLING"]["BILLING"] = BILLING;
	nJson["BILLING"]["CHARSELBILL"] = CHARSELBILL;
	nJson["BILLING"]["FREEEXP"] = FREEEXP;
	nJson["BILLING"]["GUILDBOARD"] = GUILDBOARD;
	nJson["BILLING"]["PARTYBONUS"] = PARTYBONUS;
	nJson["BILLING"]["POTIONCOUNT"] = POTIONCOUNT;
	
	//case DROP_ITEM_EVENT:
	nJson["DROP_ITEM_EVENT"]["evCurrentIndex"] = evCurrentIndex;
	nJson["DROP_ITEM_EVENT"]["evDelete"] = evDelete;
	nJson["DROP_ITEM_EVENT"]["evEndIndex"] = evEndIndex;
	nJson["DROP_ITEM_EVENT"]["evIndex"] = evIndex;
	nJson["DROP_ITEM_EVENT"]["evItem"] = evItem;
	nJson["DROP_ITEM_EVENT"]["evNotice"] = evNotice;
	nJson["DROP_ITEM_EVENT"]["evOn"] = evOn;
	nJson["DROP_ITEM_EVENT"]["evRate"] = evRate;
	nJson["DROP_ITEM_EVENT"]["evStartIndex"] = evStartIndex;
	
	//case ETC_EVENT:
	nJson["ETC_EVENT"]["BatleRoyalItem"] = BRItem;
	nJson["ETC_EVENT"]["DEADPOINT"] = DEADPOINT;
	nJson["ETC_EVENT"]["DOUBLEMODE"] = DOUBLEMODE;
	nJson["ETC_EVENT"]["DUNGEONEVENT"] = DUNGEONEVENT;
	nJson["ETC_EVENT"]["StatSpapphire"] = StatSapphire;	
	
	//case ITEM_DROP_BONUS:
	nJson["ITEM_DROP_BONUS"] = g_pDropBonus;
	
	//case OTHER:
	nJson["OTHER"]["BableRoyalRHour"] = BRHour;
	nJson["OTHER"]["GTorreHour"] = GTorreHour;
	nJson["OTHER"]["KefraLive"] = KefraLive;
	nJson["OTHER"]["PARTY_DIF"] = PARTY_DIF;
	nJson["OTHER"]["PotionDelay"] = PotionDelay;
	nJson["OTHER"]["isDropItem"] = isDropItem;
	nJson["OTHER"]["maxNightmare"] = maxNightmare;
	

	try
	{
		ofstream bjson(fullpath);
		bjson << setw(4) << nJson << std::endl;
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}


}

int nConfig::ConvertNPC(string path, string file)
{
	string fullpath = path + file;

#pragma region Txt New npc.json
	auto nJson = R"(
{
"MOB": {

				"MobName": 0,
				"Clan": 0,
				"Merchant": 0,
				"Guild": 0,
				"Class": 0,
				"Rsv": 0,
				"Quest": 0,
				"Coin": 0,
				"Exp": 0,
				"SPX": 0,
				"SPY": 0,
				"BaseScpre": {
				
							"Level": 0,
							"Ac": 0,
							"Damage": 0,
							"Merchant": 0,
							"AttackRun": 0,
							"Direction": 0,
							"ChaosRate": 0,
							"MaxHp": 0,
							"MaxMp": 0,
							"Hp": 0,
							"Mp": 0,
							"Str": 0,
							"Int": 0,
							"Dex": 0,
							"Con": 0,
							"Special1": 0,
							"Special2": 0,
							"Special3": 0,
							"Special4": 0		
				
							 },
				"CurrentScore": {
				
							"Level": 0,
							"Ac": 0,
							"Damage": 0,
							"Merchant": 0,
							"AttackRun": 0,
							"Direction": 0,
							"ChaosRate": 0,
							"MaxHp": 0,
							"MaxMp": 0,
							"Hp": 0,
							"Mp": 0,
							"Str": 0,
							"Int": 0,
							"Dex": 0,
							"Con": 0,
							"Special1": 0,
							"Special2": 0,
							"Special3": 0,
							"Special4": 0		
				
							 },
							 
							 
				"Equip": {
						"Face": [0,0,0,0,0,0,0,0],
						"Helmet": [0,0,0,0,0,0,0,0],
						"Armor": [0,0,0,0,0,0,0,0],
						"Pant": [0,0,0,0,0,0,0,0],
						"Glove": [0,0,0,0,0,0,0,0],
						"Boot": [0,0,0,0,0,0,0,0],
						"Weapon": [0,0,0,0,0,0,0,0],
						"Shield": [0,0,0,0,0,0,0,0],
						"Ring": [0,0,0,0,0,0,0,0],
						"Amulet": [0,0,0,0,0,0,0,0],
						"Orb": [0,0,0,0,0,0,0,0],
						"Stone": [0,0,0,0,0,0,0,0],
						"Guild": [0,0,0,0,0,0,0,0],
						"Pixie": [0,0,0,0,0,0,0,0],
						"Mount": [0,0,0,0,0,0,0,0],
						"Mantle": [0,0,0,0,0,0,0,0]
					    },
			"Bag": {
					 "0": [0,0,0,0,0,0,0,0]
				
				   },
			"LearnedSkill": 0,
			"Magic": 0,
			"ScoreBonus": 0,
			"SpecialBonus": 0,
			"SkillBonus": 0,
			"Critical": 0,
			"SaveMana": 0,
			"GuildLevel": 0,
			"RegenHP": 0,
			"RegenMP": 0,
			"SkillBar": [0,0,0,0],
			"Resist": [0,0,0,0],
			"MacroOn": 0,
			"MacroInside": 0,
			"SalaClear": 0
				
	
		}


})"_json;

#pragma endregion

				nJson["MOB"]["MobName"].get_to(exportNPCJson.Merchant);
				nJson["MOB"]["Clan"].get_to(exportNPCJson.Merchant);
				nJson["MOB"]["Merchant"].get_to(exportNPCJson.Merchant);
				nJson["MOB"]["Guild"].get_to(exportNPCJson.Guild);
				nJson["MOB"]["Class"].get_to(exportNPCJson.Class);
				nJson["MOB"]["Coin"].get_to(exportNPCJson.Coin);
				nJson["MOB"]["Exp"].get_to(exportNPCJson.Exp);
				nJson["MOB"]["SPX"].get_to(exportNPCJson.SPX);
				nJson["MOB"]["SPY"].get_to(exportNPCJson.SPY);
				//BaseScore
				nJson["MOB"]["BaseScore"].find("Level").value().get_to(exportNPCJson.BaseScore.Level);
				nJson["MOB"]["BaseScore"].find("Ac").value().get_to(exportNPCJson.BaseScore.Ac);
				nJson["MOB"]["BaseScore"].find("Damage").value().get_to(exportNPCJson.BaseScore.Damage);
				nJson["MOB"]["BaseScore"].find("Merchant").value().get_to(exportNPCJson.BaseScore.Merchant);
				nJson["MOB"]["BaseScore"].find("AttackRun").value().get_to(exportNPCJson.BaseScore.AttackRun);
				//nJson["MOB"]["BaseScore"].find("Direction").value().get_to(exportNPCJson.BaseScore.Direction);
				//nJson["MOB"]["BaseScore"].find("ChaosRate").value().get_to(exportNPCJson.BaseScore.ChaosRate);
				nJson["MOB"]["BaseScore"].find("MaxHp").value().get_to(exportNPCJson.BaseScore.MaxHp);
				nJson["MOB"]["BaseScore"].find("MaxMp").value().get_to(exportNPCJson.BaseScore.MaxMp);
				nJson["MOB"]["BaseScore"].find("Hp").value().get_to(exportNPCJson.BaseScore.Hp);
				nJson["MOB"]["BaseScore"].find("Mp").value().get_to(exportNPCJson.BaseScore.Mp);
				nJson["MOB"]["BaseScore"].find("Str").value().get_to(exportNPCJson.BaseScore.Str);
				nJson["MOB"]["BaseScore"].find("Int").value().get_to(exportNPCJson.BaseScore.Int);
				nJson["MOB"]["BaseScore"].find("Dex").value().get_to(exportNPCJson.BaseScore.Dex);
				nJson["MOB"]["BaseScore"].find("Con").value().get_to(exportNPCJson.BaseScore.Con);
				nJson["MOB"]["BaseScore"].find("Special1").value().get_to(exportNPCJson.BaseScore.Special[0]);
				nJson["MOB"]["BaseScore"].find("Special2").value().get_to(exportNPCJson.BaseScore.Special[1]);
				nJson["MOB"]["BaseScore"].find("Special3").value().get_to(exportNPCJson.BaseScore.Special[2]);
				nJson["MOB"]["BaseScore"].find("Special4").value().get_to(exportNPCJson.BaseScore.Special[3]);
				//passar o baseScore para CurrentScore
				for (size_t i = 0; i < 16; i++)
				{
					STRUCT_ITEM* nItem = &exportNPCJson.Equip[i];
					vector<short> arrayItem;
					memcpy(&arrayItem, nItem, sizeof(STRUCT_ITEM));
					switch (i)
					{
					case 0:
						nJson["MOB"]["Equip"].find("Face").value().get_to(arrayItem);
						break;
					case 1:
						nJson["MOB"]["Equip"].find("Helmet").value().get_to(arrayItem);
						break;
					case 2:
						nJson["MOB"]["Equip"].find("Armor").value().get_to(arrayItem);
						break;
					case 3:
						nJson["MOB"]["Equip"].find("Pant").value().get_to(arrayItem);
						break;
					case 4:
						nJson["MOB"]["Equip"].find("Glove").value().get_to(arrayItem);
						break;
					case 5:
						nJson["MOB"]["Equip"].find("Boot").value().get_to(arrayItem);
						break;
					case 6:
						nJson["MOB"]["Equip"].find("Weapon").value().get_to(arrayItem);
						break;
					case 7:
						nJson["MOB"]["Equip"].find("Shield").value().get_to(arrayItem);
						break;
					case 8:
						nJson["MOB"]["Equip"].find("Ring").value().get_to(arrayItem);
						break;
					case 9:
						nJson["MOB"]["Equip"].find("Amulet").value().get_to(arrayItem);
						break;
					case 10:
						nJson["MOB"]["Equip"].find("Orb").value().get_to(arrayItem);
						break;
					case 11:
						nJson["MOB"]["Equip"].find("Stone").value().get_to(arrayItem);
						break;
					case 12:
						nJson["MOB"]["Equip"].find("Guild").value().get_to(arrayItem);
						break;
					case 13:
						nJson["MOB"]["Equip"].find("Pixie").value().get_to(arrayItem);
						break;
					case 14:
						nJson["MOB"]["Equip"].find("Mount").value().get_to(arrayItem);
						break;
					case 15:
						nJson["MOB"]["Equip"].find("Mantle").value().get_to(arrayItem);
						break;
					default:
						break;
					}
				}
				//Equip
				/*nJson["MOB"]["Equip"].find("Face").value().get_to(exportNPCJson.Equip[0].sIndex);
				nJson["MOB"]["Equip"].find("Helmet").value().get_to(exportNPCJson.Equip[1].sIndex);
				nJson["MOB"]["Equip"].find("Armor").value().get_to(exportNPCJson.Equip[2].sIndex);
				nJson["MOB"]["Equip"].find("Pant").value().get_to(exportNPCJson.Equip[3].sIndex);
				nJson["MOB"]["Equip"].find("Glove").value().get_to(exportNPCJson.Equip[4].sIndex);
				nJson["MOB"]["Equip"].find("Boot").value().get_to(exportNPCJson.Equip[5].sIndex);
				nJson["MOB"]["Equip"].find("Weapon").value().get_to(exportNPCJson.Equip[6].sIndex);
				nJson["MOB"]["Equip"].find("Shield").value().get_to(exportNPCJson.Equip[7].sIndex);
				nJson["MOB"]["Equip"].find("Ring").value().get_to(exportNPCJson.Equip[8].sIndex);
				nJson["MOB"]["Equip"].find("Amulet").value().get_to(exportNPCJson.Equip[9].sIndex);
				nJson["MOB"]["Equip"].find("Orb").value().get_to(exportNPCJson.Equip[10].sIndex);
				nJson["MOB"]["Equip"].find("Stone").value().get_to(exportNPCJson.Equip[11].sIndex);
				nJson["MOB"]["Equip"].find("Guild").value().get_to(exportNPCJson.Equip[12].sIndex);
				nJson["MOB"]["Equip"].find("Pixie").value().get_to(exportNPCJson.Equip[13].sIndex);
				nJson["MOB"]["Equip"].find("Mount").value().get_to(exportNPCJson.Equip[14].sIndex);
				nJson["MOB"]["Equip"].find("Mantle").value().get_to(exportNPCJson.Equip[15]);*/
				//for passando em todos os itens/slot e pegando os dados do array
			/*	for (size_t i = 0; i < 16; i++)
				{
					g_MobBase[key].Equip[i].sIndex = equipSlot[i][0];
					g_MobBase[key].Equip[i].stEffect->sValue = equipSlot[i][1];
					g_MobBase[key].Equip[i].stEffect[0].cEffect = equipSlot[i][2];
					g_MobBase[key].Equip[i].stEffect[0].cValue = equipSlot[i][3];
					g_MobBase[key].Equip[i].stEffect[1].cEffect = equipSlot[i][4];
					g_MobBase[key].Equip[i].stEffect[1].cValue = equipSlot[i][5];
					g_MobBase[key].Equip[i].stEffect[2].cEffect = equipSlot[i][6];
					g_MobBase[key].Equip[i].stEffect[2].cValue = equipSlot[i][7];
				};*/
				//for para pegar os itens inciais da mochila
				/*/for (auto& x : nJson[className]["Bag"].items())
				{

					vector<short> equipBag = x.value();
					g_MobBase[key].Carry[stoi(x.key())].sIndex = equipBag[0];
					g_MobBase[key].Carry[stoi(x.key())].stEffect->sValue = equipBag[1];
					g_MobBase[key].Carry[stoi(x.key())].stEffect[0].cEffect = equipBag[2];
					g_MobBase[key].Carry[stoi(x.key())].stEffect[0].cValue = equipBag[3];
					g_MobBase[key].Carry[stoi(x.key())].stEffect[1].cEffect = equipBag[4];
					g_MobBase[key].Carry[stoi(x.key())].stEffect[1].cValue = equipBag[5];
					g_MobBase[key].Carry[stoi(x.key())].stEffect[2].cEffect = equipBag[6];
					g_MobBase[key].Carry[stoi(x.key())].stEffect[2].cValue = equipBag[7];

				};

				nJson[className]["LearnedSkill"].get_to(g_MobBase[key].LearnedSkill);
				nJson[className]["Magic"].get_to(g_MobBase[key].Magic);
				nJson[className]["ScoreBonus"].get_to(g_MobBase[key].ScoreBonus);
				nJson[className]["SpecialBonus"].get_to(g_MobBase[key].SpecialBonus);
				nJson[className]["SkillBonus"].get_to(g_MobBase[key].SkillBonus);
				nJson[className]["Critical"].get_to(g_MobBase[key].Critical);
				nJson[className]["SaveMana"].get_to(g_MobBase[key].SaveMana);
				nJson[className]["GuildLevel"].get_to(g_MobBase[key].GuildLevel);
				nJson[className]["RegenHP"].get_to(g_MobBase[key].RegenHP);
				nJson[className]["RegenMP"].get_to(g_MobBase[key].RegenMP);

				vector<short> skill;
				nJson[className]["SkillBar"].get_to(skill);
				for (size_t i = 0; i < 4; i++)
				{
					g_MobBase[key].SkillBar[i] = skill[i];
				}

				vector<short> resist;
				nJson[className]["Resist"].get_to(skill);
				for (size_t i = 0; i < 4; i++)
				{
					g_MobBase[key].Resist[i] = skill[i];
				}*/

	try
	{
		ofstream bjson(fullpath);
		bjson << setw(4) << nJson << std::endl;
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int nConfig::ReadExtra(string path, string file, int key)
{
	string fullpath = path + file;

	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	if (fp == NULL) {

		//config.json não encontrado, será criado um novo(default) no diretorio config/
		int creat = WriteExtra(PATH_SETTINGS, "extra.json", 0);

		if (!creat)
			return creat;
	}

	try
	{
		ifstream spath(fullpath);
		json nJson;
		spath >> nJson;

		switch (key)
		{
		case MORTAL:
			nJson["CHARACTER_CREATE"]["MORTAL"].get_to(CharaCreate[MORTAL]);
			break;

		case ARCH:
			nJson["CHARACTER_CREATE"]["ARCH"].get_to(CharaCreate[ARCH]);
			break;

		case CELESTIAL:
			nJson["CHARACTER_CREATE"]["CELESTIAL"].get_to(CharaCreate[CELESTIAL]);
			break;

		case CELESTIALCS:
			nJson["CHARACTER_CREATE"]["CELESTIALCS"].get_to(CharaCreate[CELESTIALCS]);
			break;

		case SCELESTIAL:
			nJson["CHARACTER_CREATE"]["SCELESTIAL"].get_to(CharaCreate[SCELESTIAL]);
			break;

		default:
			break;
		}

		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int nConfig::WriteExtra(string path, string file, int key)
{
	std::string fullpath = path + file;
	FILE* fp = fopen(fullpath.c_str(), "rt");

#pragma region Txt New Extra
	auto text = R"({
"CHARACTER_CREATE": {
			"MORTAL": 1,
			"ARCH": 1,
			"CELESTIAL": 1,
			"CELESTIALCS": 1,
			"SCELESTIAL": 1
		},
"CLASS_CREATE": {
			"TK": 1,
			"FM": 1,
			"BM": 1,
			"HT": 1
		}

}
    )";
#pragma endregion

	if (fp == NULL)
	{
		fprintf(fp, text, 0);
		fclose(fp);

		return TRUE;
	};

	ifstream spath(fullpath);
	json nJson;
	spath >> nJson;
	int nvalor = CharaCreate[key] + 1;
	switch (key)
	{
	case MORTAL:
		nJson["CHARACTER_CREATE"]["MORTAL"] = nvalor;
		break;

	case ARCH:
		nJson["CHARACTER_CREATE"]["ARCH"] = nvalor;
		break;

	case CELESTIAL:
		nJson["CHARACTER_CREATE"]["CELESTIAL"] = nvalor;
		break;

	case CELESTIALCS:
		nJson["CHARACTER_CREATE"]["CELESTIALCS"] = nvalor;
		break;

	case SCELESTIAL:
		nJson["CHARACTER_CREATE"]["SCELESTIAL"] = nvalor;
		break;

	default:
		break;
	}

	ofstream bjson(fullpath);
	bjson << setw(4) << nJson << std::endl;
	return TRUE;

}

#pragma region Config Json
int nConfig::ReadConfigNews(string path, string file, int key)
{
	string fullpath = path + file;

	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	if (fp == NULL) {

		//config.json não encontrado, será criado um novo(default) no diretorio config/
		//int creat = WriteConfigNews(PATH_SETTINGS, ConfigJson, 0);
		
		//if (!creat)
			return FALSE;
	}
	
	try
	{
		ifstream spath(fullpath);
		json nJson;
		spath >> nJson;
		GroupServer Server0;
		GroupServer Server1;
		GroupServer Server2;
	
		switch (key)
		{
		case CONFIG:
			nJson["CONFIG"]["Sapphire"].get_to(Sapphire);
			nJson["CONFIG"]["LastCapsule"].get_to(LastCapsule);
			nJson["CONFIG"]["TitleSystem"].get_to(AtivaTitleSystem);
			break;
		case SERVERLIST:
			nJson["SERVERLIST"]["MaxServer"].get_to(MaxServer);
			nJson["SERVERLIST"]["MaxServerGroup"].get_to(MaxServerGroup);
			nJson["SERVERLIST"]["MaxServerNumber"].get_to(MaxServerNumber);
			nJson["CONFIG"]["TitleSystem"].get_to(AtivaTitleSystem);//não remover devido a releitura do arquivo na TM

			for (auto& x : nJson["SERVERLIST"]["IPLIST"].items())
			{
				int group = x.value().find("ServerGroup").value();
				int number = x.value().find("ServerNumber").value();
				string address = x.value().find("Address").value();

				strcpy(g_pServerList[group][number], address.c_str());
			};
			
			break;
		case ADMIN:
			int a, b, c, d;
			a = b = c = d = 0;
			for (auto& x : nJson["ADMIN"].items())
			{
				string remov = ".";
				string inc = " ";
				string ip = x.value();

				findAndReplaceAll(ip, remov, inc);
		
				sscanf(ip.c_str(), "%d %d %d %d", &a, &b, &c, &d);

				unsigned int ip_decimal = (d << 24) + (c << 16) + (b << 8) + a;

			ipAdmin[stoi(x.key())] = ip_decimal;
			
			};

			break;
		default:
			break;
		}
		

		return TRUE;

	}
	catch (json::parse_error& e)
	{
		// output exception information
		std::cout << "message: " << e.what() << '\n'
			<< "exception id: " << e.id << '\n'
			<< "byte position of error: " << e.byte << std::endl;
		return FALSE;
	}
}

int nConfig::WriteConfigNews(std::string path, std::string file, int key)
{
	string fullpath = path + file;
	
#pragma region Txt New config
	auto nJson = R"({
	"CONFIG": {
		"Sapphire": 8,
		"LastCapsule": 0,
		"TitleSystem": 1
	},
	"SERVERLIST": {
		"MaxServer": 10,
		"MaxServerGroup": 10,
		"MaxServerNumber": 11,
		"IPLIST": [
					{
						"ServerGroup": 0,
						"ServerNumber": 0,
						"Address": "192.168.0.102"
					},
					{
						"ServerGroup": 0,
						"ServerNumber": 1,
						"Address": "192.168.0.102"
					},
					{
						"ServerGroup": 0,
						"ServerNumber": 2,
						"Address": "192.168.0.102"
					}
				]
			
			},
	"ADMIN": {
				
				"0": "192.168.0.102"
			 }
		}
    )";
#pragma endregion
	try
	{
		ofstream bjson(fullpath);
		bjson << setw(4) << nJson << std::endl;
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}

	
}

#pragma endregion

#pragma region DB
int nConfig::ReadbaseMob(string path, string file, int key)
{
	char Class[4][2] = {
		{'T','K'},
		{'F','M'},
		{'B','M'},
		{'H','T'}
	};

	string className;
	short equipSlot[16][8];
	string fullpath = path + file;

	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	if (fp == NULL) {

		//baseMob.json não encontrado
		return FALSE;
	}

	try
	{
		ifstream spath(fullpath);
		json nJson;
		spath >> nJson;

		for (int i = 0; i < 2; i++)
		{
			g_MobBase[0].MobName[i] = Class[key][i];
		}

		switch (key)
		{
		case TK:
			className = "TK";
			break;
		case FM:
			className = "FM";
			break;
		case BM:
			className = "BM";
			break;
		case HT:
			className = "HT";
			break;
		default:
			break;
		}

		//Base
		nJson[className]["Merchant"].get_to(g_MobBase[key].Merchant);
		nJson[className]["Guild"].get_to(g_MobBase[key].Guild);
		nJson[className]["Class"].get_to(g_MobBase[key].Class);
		nJson[className]["Coin"].get_to(g_MobBase[key].Coin);
		nJson[className]["Exp"].get_to(g_MobBase[key].Exp);
		nJson[className]["SPX"].get_to(g_MobBase[key].SPX);
		nJson[className]["SPY"].get_to(g_MobBase[key].SPY);
		//BaseScore
		nJson[className]["BaseScore"].find("Level").value().get_to(g_MobBase[key].BaseScore.Level);
		nJson[className]["BaseScore"].find("Ac").value().get_to(g_MobBase[key].BaseScore.Ac);
		nJson[className]["BaseScore"].find("Damage").value().get_to(g_MobBase[key].BaseScore.Damage);
		nJson[className]["BaseScore"].find("Merchant").value().get_to(g_MobBase[key].BaseScore.Merchant);
		nJson[className]["BaseScore"].find("AttackRun").value().get_to(g_MobBase[key].BaseScore.AttackRun);
		//nJson[className]["BaseScore"].find("Direction").value().get_to(g_MobBase[key].BaseScore.Direction);
		//nJson[className]["BaseScore"].find("ChaosRate").value().get_to(g_MobBase[key].BaseScore.ChaosRate);
		nJson[className]["BaseScore"].find("MaxHp").value().get_to(g_MobBase[key].BaseScore.MaxHp);
		nJson[className]["BaseScore"].find("MaxMp").value().get_to(g_MobBase[key].BaseScore.MaxMp);
		nJson[className]["BaseScore"].find("Hp").value().get_to(g_MobBase[key].BaseScore.Hp);
		nJson[className]["BaseScore"].find("Mp").value().get_to(g_MobBase[key].BaseScore.Mp);
		nJson[className]["BaseScore"].find("Str").value().get_to(g_MobBase[key].BaseScore.Str);
		nJson[className]["BaseScore"].find("Int").value().get_to(g_MobBase[key].BaseScore.Int);
		nJson[className]["BaseScore"].find("Dex").value().get_to(g_MobBase[key].BaseScore.Dex);
		nJson[className]["BaseScore"].find("Con").value().get_to(g_MobBase[key].BaseScore.Con);
		nJson[className]["BaseScore"].find("Special1").value().get_to(g_MobBase[key].BaseScore.Special[0]);
		nJson[className]["BaseScore"].find("Special2").value().get_to(g_MobBase[key].BaseScore.Special[1]);
		nJson[className]["BaseScore"].find("Special3").value().get_to(g_MobBase[key].BaseScore.Special[2]);
		nJson[className]["BaseScore"].find("Special4").value().get_to(g_MobBase[key].BaseScore.Special[3]);
		//passar o baseScore para CurrentScore
		memmove(&g_MobBase[key].CurrentScore, &g_MobBase[key].BaseScore, sizeof(STRUCT_SCORE));
		//Equip
		nJson[className]["Equip"].find("Face").value().get_to(equipSlot[0]);
		nJson[className]["Equip"].find("Helmet").value().get_to(equipSlot[1]);
		nJson[className]["Equip"].find("Armor").value().get_to(equipSlot[2]);
		nJson[className]["Equip"].find("Pant").value().get_to(equipSlot[3]);
		nJson[className]["Equip"].find("Glove").value().get_to(equipSlot[4]);
		nJson[className]["Equip"].find("Boot").value().get_to(equipSlot[5]);
		nJson[className]["Equip"].find("Weapon").value().get_to(equipSlot[6]);
		nJson[className]["Equip"].find("Shield").value().get_to(equipSlot[7]);
		nJson[className]["Equip"].find("Ring").value().get_to(equipSlot[8]);
		nJson[className]["Equip"].find("Amulet").value().get_to(equipSlot[9]);
		nJson[className]["Equip"].find("Orb").value().get_to(equipSlot[10]);
		nJson[className]["Equip"].find("Stone").value().get_to(equipSlot[11]);
		nJson[className]["Equip"].find("Guild").value().get_to(equipSlot[12]);
		nJson[className]["Equip"].find("Pixie").value().get_to(equipSlot[13]);
		nJson[className]["Equip"].find("Mount").value().get_to(equipSlot[14]);
		nJson[className]["Equip"].find("Mantle").value().get_to(equipSlot[15]);
		//for passando em todos os itens/slot e pegando os dados do array
		for (size_t i = 0; i < 16; i++)
		{
			g_MobBase[key].Equip[i].sIndex = equipSlot[i][0];
			g_MobBase[key].Equip[i].stEffect->sValue = equipSlot[i][1];
			g_MobBase[key].Equip[i].stEffect[0].cEffect = equipSlot[i][2];
			g_MobBase[key].Equip[i].stEffect[0].cValue = equipSlot[i][3];
			g_MobBase[key].Equip[i].stEffect[1].cEffect = equipSlot[i][4];
			g_MobBase[key].Equip[i].stEffect[1].cValue = equipSlot[i][5];
			g_MobBase[key].Equip[i].stEffect[2].cEffect = equipSlot[i][6];
			g_MobBase[key].Equip[i].stEffect[2].cValue = equipSlot[i][7];
		};
		//for para pegar os itens inciais da mochila
		for (auto& x : nJson[className]["Bag"].items())
		{

			vector<short> equipBag = x.value();
			g_MobBase[key].Carry[stoi(x.key())].sIndex = equipBag[0];
			g_MobBase[key].Carry[stoi(x.key())].stEffect->sValue = equipBag[1];
			g_MobBase[key].Carry[stoi(x.key())].stEffect[0].cEffect = equipBag[2];
			g_MobBase[key].Carry[stoi(x.key())].stEffect[0].cValue = equipBag[3];
			g_MobBase[key].Carry[stoi(x.key())].stEffect[1].cEffect = equipBag[4];
			g_MobBase[key].Carry[stoi(x.key())].stEffect[1].cValue = equipBag[5];
			g_MobBase[key].Carry[stoi(x.key())].stEffect[2].cEffect = equipBag[6];
			g_MobBase[key].Carry[stoi(x.key())].stEffect[2].cValue = equipBag[7];

		};

		nJson[className]["LearnedSkill"].get_to(g_MobBase[key].LearnedSkill);
		nJson[className]["Magic"].get_to(g_MobBase[key].Magic);
		nJson[className]["ScoreBonus"].get_to(g_MobBase[key].ScoreBonus);
		nJson[className]["SpecialBonus"].get_to(g_MobBase[key].SpecialBonus);
		nJson[className]["SkillBonus"].get_to(g_MobBase[key].SkillBonus);
		nJson[className]["Critical"].get_to(g_MobBase[key].Critical);
		nJson[className]["SaveMana"].get_to(g_MobBase[key].SaveMana);
		nJson[className]["GuildLevel"].get_to(g_MobBase[key].GuildLevel);
		nJson[className]["RegenHP"].get_to(g_MobBase[key].RegenHP);
		nJson[className]["RegenMP"].get_to(g_MobBase[key].RegenMP);

		vector<short> skill;
		nJson[className]["SkillBar"].get_to(skill);
		for (size_t i = 0; i < 4; i++)
		{
			g_MobBase[key].SkillBar[i] = skill[i];
		}

		vector<short> resist;
		nJson[className]["Resist"].get_to(skill);
		for (size_t i = 0; i < 4; i++)
		{
			g_MobBase[key].Resist[i] = skill[i];
		}

		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::ReadFilterName(string path, string file)
{
	string fullpath = path + file;
	FILE* fp = NULL;
	fp = fopen(fullpath.c_str(), "rt");

	if (fp == NULL) {

		// não encontrado, será criado um novo(default) no diretorio
		int creat = WriteFilterName(PATH_FILTER_NAME, file);

		if (!creat)
			return creat;
	}

	try
	{
		ifstream spath(fullpath);
		json nJson;
		spath >> nJson;

		nJson["FILTER"]["ATIVO"].get_to(FilterName.ATIVO);
		nJson["FILTER"]["TOTAL"].get_to(FilterName.TOTAL);
		vector<string> nArray;
		nJson["FILTER"]["NAME"].get_to(nArray);

		for (size_t i = 0; i < FilterName.TOTAL; i++)
		{
			FilterName.NAME[i] = nArray[i];
		}
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

int ConfigIni::nConfig::WriteFilterName(string path, string file)
{
	string fullpath = path + file;

#pragma region Txt New block.json
	auto nJson = R"(
{
"FILTER": {
		  "ATIVO": 0,
		  "TOTAL": 20,
		  "NAME":[
					"ADM",
					"GM",
					"DEV",
					"NEWSGAMES",
					"ETERNAL",
					"ADMIN",
					"MOD",
					"MODERADOR",
					"GAMEMASTER",
					"PROGRA",
					"ANUS",
					"ÂNUS",
					"BUNDA",
					"BUCETA",
					"ANAL",
					"PERERECA",
					"PÊNIS",
					"PENIS",
					"PIRU",
					"VAGINA"
				 ]
		  }
})"_json;

#pragma endregion

	try
	{
		ofstream bjson(fullpath);
		bjson << setw(4) << nJson << std::endl;
		return TRUE;
	}
	catch (const std::exception&)
	{
		return FALSE;
	}
}

#pragma endregion


