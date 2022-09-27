
#ifndef __CREAD_FILES_H__
#define __CREAD_FILES_H__

#include <stdio.h>
#include "..\Basedef.h"

class CReadFiles
{
private:
	static const char* const IMPORT_ITEM_PATH;
	static const char* const UPDATE_CONNECTION_PATH;
	static const char* const UPDATE_CONNECTION_DATA_PATH;
	static const char* const IMPORT_ITEM2_PATH;
	static const char* const IMPORT_ITEM_ERROR_PATH;
	static const char* const IMPORT_USER_PATH;
	static const char* const IMPORT_USER2_PATH;
	static const char* const GUILD_INFO_PATH;
	static const char* const IMPORT_DONATE_PATH;
	static const char* const IMPORT_DONATE2_PATH;
	static const char* const IMPORT_DONATE_ERROR_PATH;
	static const char* const UPDATE_USER_PATH;
	static const char* const UPDATE_USER2_PATH;
	static const char* const RANKING_PATH;

public:
	static void UpdateConnection();
	static void UpdateConnectionData();
	static void ImportItem();
	static void ImportUser();
	static void ReadGuildInfo();
	static void WriteGuildInfo();
	static void ImportDonate();
	static void UpdateUser();
	static void WriteRanking();
};

#endif // __CREAD_FILES_H__