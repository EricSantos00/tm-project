
#ifndef __GETFUNC__
#define __GETFUNC__

#include "..\Basedef.h"
#include <Windows.h>

int GetRecycleBin(int a_iConn, STRUCT_ITEM* kItem, int a_iPrice);

int	 GetMatchCombine		(STRUCT_ITEM *item);
int  GetMatchCombineEhre	(STRUCT_ITEM *Item);
int  GetMatchCombineLoki    (STRUCT_ITEM *Item);
int  GetMatchCombineTiny	(STRUCT_ITEM *Item);
int  GetMatchCombineShany	(STRUCT_ITEM *Item);
int  GetMatchCombineAilyn	(STRUCT_ITEM *Item);
int  GetMatchCombineAgatha	(STRUCT_ITEM *Item);
int  GetMatchCombineOdin	(STRUCT_ITEM *Item);
int  GetMatchCombineDedekinto(STRUCT_ITEM *Item);
int  GetMatchCombineAlquimia(STRUCT_ITEM *Item);
int GetParryRate(STRUCT_MOB *mob, int add, int attackerdex, int attackrsv);
int	 GetEmptyAffect(int mob, int type);  // return value -1 if it's full.
int	 GetHide				(int mob);
int	 GetInView				(int a, int b);
int  GetInHalf				(int a, int b);
int	 GetTeleportPosition	(int conn, int *x, int * y); // returns the cost of the teleport
int	 GetExpApply			(STRUCT_MOBExtra Extra, int exp, int attacker, int target);
int	 GetCreateMob			(int mob, MSG_CreateMob *sm);
int	 GetCreateMobTrade		(int mob, MSG_CreateMobTrade* sm);
void GetAffect              (unsigned short *out, STRUCT_AFFECT *affect);
void GetCreateItem			(int idx, MSG_CreateItem* sm);
void GetAction			    (int mob, int targetx, int targety, MSG_Action* sm);
unsigned char GetAttribute	(int x, int y);
void GetAttack             (int mob, int target, MSG_AttackOne *sm);
void GetAttackArea			(int mob, MSG_Attack *sm);
void GetGuild				(int conn);
int  GetGuild				(STRUCT_ITEM *item);
int  GetEmptyItemGrid		(int *gridx, int *gridy);
int	 GetEmptyMobGrid        (int conn, int  *tx, int *ty);
int  GetCurKill				(int conn);
int	 GetTotKill				(int conn);
void SetCurKill				(int conn, int value);
void SetTotKill				(int conn, int value);
int  GetPKPoint				(int conn);
int	 GetGuilty				(int conn);
void SetGuilty				(int conn, int value);
void SetPKPoint				(int conn, int value);
BOOL GetEmptyMobGridGreat	(int mob, int *tx, int *ty);
std::string GetFormatDecimal(int value);


int GetAttackMiss(int a_iConn, int a_iTarget);
#endif


