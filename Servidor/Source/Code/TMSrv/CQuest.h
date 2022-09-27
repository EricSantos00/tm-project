#pragma once

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
#include "CMob.h"
#include "CUser.h"
#include "CNPCGene.h"
#include "CReadFiles.h"
#include "CCastleZakum.h"


void NTask_TrainingI(int a_iConn, int a_iTarget);
void NTask_TrainingII(int a_iConn, int a_iTarget);
void NTask_TrainingIII(int a_iConn, int a_iTarget);
void NTask_TrainingChief(int a_iConn, int a_iTarget);

void NTask_QuestCoveiro(int a_iConn, int a_iTarget);
void NTask_QuestJardineiro(int a_iConn, int a_iTarget);
void NTask_QuestKaizen(int a_iConn, int a_iTarget);
void NTask_QuestHidra(int a_iConn, int a_iTarget);
void NTask_QuestElfos(int a_iConn, int a_iTarget);
void NTask_QuestMolarGargula(int a_iConn, int a_iTarget);
void NTask_QuestCapaVerde(int a_iConn, int a_iTarget);
void NTask_QuestLeakyZakum(int a_iConn, int a_iTarget);
void NTask_QuestGuardaEventos(int a_iConn, int a_iTarget);
void NTask_QuestChefeTreina(int a_iConn, int a_iTarget);
void NTask_SacerdoteKruno(int a_iConn, int a_iTarget);
void NTask_SacerdoteAmelia(int a_iConn, int a_iTarget);
void NTask_QuestGuardaReal(int a_iConn, int a_iTarget);
void NTask_SacerdoteJester(int a_iConn, int a_iTarget);
void NTask_Sobrevivente(int a_iConn, int a_iTarget);
void NTask_GuardaHelgardh(int a_iConn, int a_iTarget);


void NTask_MestreHaby(int a_iConn, int a_iTarget, int confirm);
void NTask_Kibita(int a_iConn, int a_iTarget);
void NTask_Skills(int a_iConn, int a_iTarget, int confirm);
void NTask_Perzens(int a_iConn, int a_iTarget);
void NTask_Juli(int a_iConn, int a_iTarget);

void NTask_DragãoArmia(int a_iConn, int a_iTarget);
void NTask_DragãoArzan(int a_iConn, int a_iTarget);
void NTask_CarbuncleWind(int a_iConn, int a_iTarget);

void NTask_CapMercenario(int a_iConn, int a_iTarget, int confirm);
void NTask_CapExpor(int a_iConn, int a_iTarget);
void NTask_Jeffi(int a_iConn, int a_iTarget);
void NTask_Shama(int a_iConn, int a_iTarget);
void NTask_BlackOracle(int a_iConn, int a_iTarget);
void NTask_M_Montaria(int a_iConn, int a_iTarget, int confirm);
void NTask_King(int a_iConn, int a_iTarget, int confirm);
void NTask_KingdonBroker(int a_iConn, int a_iTarget, int confirm, int ClientTick);
void NTask_GodGovernment(int a_iConn, int a_iTarget);
void NTask_LiderAprendiz(int a_iConn, int a_iTarget);
void NTask_Urnammu(int a_iConn, int a_iTarget);


void NTask_Uxmal(int a_iConn, int a_iTarget);
void NTask_Forseti(int a_iConn, int a_iTarget, int confirm);
void NTask_Xamã(int a_iConn, int a_iTarget, int confirm);

//Event Trade
void NTask_EventTrade(int a_iConn, int a_iTarget, int NpcGrade);
void NTask_StartEventTrade();
































