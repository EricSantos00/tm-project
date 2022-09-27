#include "ProcessClientMessage.h"
#include <iostream>
#include <windows.h>
#include <windowsx.h>
#include <string>
#include <sstream>

#define MaxMobKilled 1000
#define FameMob 1
#define FameBase 10

//void BuyTerritory();//feito no _MSG_Buy
void GuildLevelUp();
void KeyTerritory(MSG_UseItem* m, STRUCT_ITEM* Item, int a_iConn);
void FamePointMob(unsigned int conn, unsigned int target);
void FamePointBoss(unsigned int conn, unsigned int boss);
void GuardianTerritory(int conn, int nTerritory, int NPC);
void TerritoryMob(int conn, int nTerritory, int nMob);
void WINAPI TerritoryStart();
void CheckPlayTerritory(int nTerritory, unsigned int conn);
void CheckPlayGuildHall(unsigned int conn);