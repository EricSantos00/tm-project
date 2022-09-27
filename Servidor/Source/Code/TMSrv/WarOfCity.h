#include <Windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>
#include <io.h>
#include <errno.h>
#include <inttypes.h>

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
#include "CReadFiles.h"
#include "WarOfTower.h"
#include "../ConfigIni.h"


void WarCity();
void ClearGuildPKZone();
void DecideWinner();
void ClearChallanger();
void SetArenaDoor(int state);