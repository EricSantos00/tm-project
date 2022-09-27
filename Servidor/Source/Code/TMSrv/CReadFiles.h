
#ifndef __CREAD_FILES_H__
#define __CREAD_FILES_H__

#include <stdio.h>
#include "..\Basedef.h"

class CReadFiles
{
public:
	CReadFiles();

	static void ReadSancRate();
	static void ReadQuestsRate();
	static void ReadCompRate();
	static void ReadMobMerc();
	static void ReadAdmin();
	static void ReadMacblock();
	static void ReadChallanger();
	static void WriteChallanger();
	static void ReadGuild();
	static void WriteGuild();
	static void WriteCountPlayer();

public:
	static int QuestExp[5][2];
	static int QuestCoin[5];
	static int QuestLevel[5][4];

private:
	static const char* const SANC_RATE_PATH;
	static const char* const QUESTS_RATE_PATH;
	static const char* const COMP_RATE_PATH;
	static const char* const MOB_MERC_PATH;
	static const char* const ADMIN_PATH;
	static const char* const MAC_BLOCK_PATH;
	static const char* const CHALL_PATH;
	static const char* const GUILD_PATH;
	static const char* const GUILDCHAMP_PATH;
};

#endif // __CREAD_FILES_H__