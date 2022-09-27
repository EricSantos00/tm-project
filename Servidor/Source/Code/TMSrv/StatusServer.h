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

int GetStatusServer(int conn, char* AccountName);
