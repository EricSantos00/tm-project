
#pragma comment(lib, "Urlmon.lib")  //download da internet
#include <urlmon.h>                 //download da internet
#include <iterator>                 // for copy and past
#include <windows.h>
#include <tlhelp32.h>
#include <process.h>
#include <fstream>
#include "winsock.h"
#include <string>
#include "windowsx.h"
#include <iostream>   // coat << <<
#include <tchar.h>    //to php POST
#include <map>        //compare words ban txt
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib, "iphlpapi")    //to get mac address
#include <iphlpapi.h>               //to get mac address
#include <assert.h>                 //to get mac address 

#include <wininet.h>                //to ftp server / php
#pragma comment(lib, "Wininet")     //to ftp server
#pragma comment(lib,"wininet.lib")  //to php POST

#include "START.h"
#include "Classe.h"
#include "CRC.h"

#define WIN_32_LEAN_AND_MEAN

 #pragma warning (disable: 4996 4091 4101 4018 4309)

 using namespace std;

extern  "C"  __declspec(dllexport) void __cdecl GasMask_5(); //API (init da dll)
