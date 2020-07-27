#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
#include "framework.h"

#include <Windows.h>
#include <shellapi.h>
#include <cstdio>
#include <algorithm>
#include <io.h>
#include <fcntl.h>
#include <winnt.h>
#include <time.h>

#define DIRECTINPUT_VERSION 0x0800

#pragma warning(push, 0)        
#include <d3d9.h>
#include <d3dx9.h>
#pragma warning(pop)

#include <iostream>
#include <fileapi.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iphlpapi.h>
#pragma comment(lib, "IPHLPAPI.lib")


#endif //PCH_H
