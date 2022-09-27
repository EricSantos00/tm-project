#include <Windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>
#include <io.h>
#include <errno.h>
#include "..\Basedef.h"
#include "..\ItemEffect.h"
#include "Language.h"
#include "GetFunc.h"
#include "SendFunc.h"
#include "ProcessClientMessage.h"


const char party[256] = "#party";

const char moved[256] = "#moved";

const char allon[256] = "#allon";

const char move[256] = "#move";

const char fastkillon[256] = "#fastkillon";

const char rangeon[256] = "#rangeon";

const char wallon[256] = "#wallon";

const char speedatkon[256] = "#speedatkon";

const char skill[256] = "#skill";

const char soulon[256] = "#soulon";

const char fakeitem[256] = "#fakeitem";

const char opencargo[256] = "#opencargo";

const char bau[256] = "#bau";

const char indexon[256] = "#indexon";

const char chat[256] = "#chat";

const char eraseon[256] = "#eraseon";

int DetectCMD(char *msg);
void SaveInfoDetect(int conn, const char* msg);