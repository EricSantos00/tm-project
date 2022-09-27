#include "ProcessClientMessage.h"
#include <iostream>
#include <windows.h>
#include <windowsx.h>
#include <string>
#include <sstream>

void WINAPI initBossCamp(unsigned char boss);
void startBossCamp(unsigned char boss);
void checkBossCamp(unsigned char boss);
void genBossCamp(int index, unsigned char boss);
void genGuardianBossCamp(int index, unsigned char boss);
void checkHPBossCamp(int idx, unsigned char boss);
void guardianBossCampKilled(unsigned char boss);
void BossCampKilled(int a_iConn, unsigned char boss);
void randDropBossCamp();

