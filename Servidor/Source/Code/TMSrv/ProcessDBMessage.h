
#pragma once

#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <stdio.h> 
#include <fcntl.h>
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/timeb.h>
#include <string.h>        
#include <time.h>

#include "..\Basedef.h"
#include "..\CPSock.h"

#include "CItem.h"
#include "CMob.h"
#include "CUser.h"
#include "CNPCGene.h"


void  ProcessDBMessage(int conn, char *pMsg);