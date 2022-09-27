
#include "StdAfx.h"

void Serial_e_Etc()
{
	DWORD* Serial = (DWORD*)(0x007DBE6AC); // Serial Offset, in this case, mxmain Version 1.01E are = 692174 
	memset(&Serial[0],0x00,16);           // Max digits (16)
	memcpy(&Serial[0],carrega.Serial,16); 

	DWORD* Versao = (DWORD*)(0x0069216C); // Version Offset, in this case, mxmain Version 1.01E are = 69216C
	memset(&Versao[0],0x00,5);            // Max digits (5)
	memcpy(&Versao[0],carrega.Versao,5);  

    DWORD* Ip = (DWORD*)(0x007DBE6C0);     // IP Offset 
	memset(&Ip[0],0x00,15);               // Max digits (15)
    memcpy(&Ip[0],carrega.IP,15); 
}


