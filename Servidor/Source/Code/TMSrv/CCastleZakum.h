
#pragma once

#include <stdio.h>
#include "..\Basedef.h"


class CCastleZakum
{
private:
	static const char* const CASTLE_QUEST_PATH;

public:
	static BOOL OpenCastleGate(int conn, int gateid, MSG_UpdateItem *m);
	static void MobKilled(int target, int conn, int PosX, int PosY);
	static BOOL KeyDrop(int target, int conn, int PosX, int PosY, STRUCT_ITEM *Key);

	static void ProcessSecTimer();
	static void ProcessMinTimer();

	static void CheckMove(int conn, int targetx, int targety);

	static void ReadCastleQuest();
	static int  ParseCastleString(int Num, char *str);
};
