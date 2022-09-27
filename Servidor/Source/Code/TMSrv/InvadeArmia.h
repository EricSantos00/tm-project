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

extern BOOL invadArmiaStart;
extern BOOL invadArmiaEnd;
extern BOOL invadArmiaNotice;
extern short unsigned int waveStart;
extern unsigned int InvadeArmiaMobCount;
extern int invadArmiaTime;

void WINAPI StartInvadeArmia();
void InvadeArmiaStartWave(int nWave);
void InvadeArmiaWaveKilled(int nMob);
void InvadeArmiaStartBoss();
void InvadeArmiaBossKilled(int nMob);
void InvadeArmiaDropMob(int conn);
void InvadeArmiaDropBoss(int conn, unsigned int cooX, unsigned int cooY);
void InvadeArmiaTimeNotice();
