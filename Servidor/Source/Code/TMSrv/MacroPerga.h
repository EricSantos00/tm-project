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
#include "ProcessDBMessage.h"

#define PergaAguaN 3173
#define PergaAguaM 777
#define PergaAguaA 3182
int AtiveMacroPerga(int conn);
int UseItem(int slotItem, int conn);
void WINAPI InitMacro();
void MacroOnline(int ClientID);