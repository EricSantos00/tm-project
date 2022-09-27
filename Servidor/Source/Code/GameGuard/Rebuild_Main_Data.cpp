
#include "StdAfx.h"

void RebuildData()
{   
	DWORD* Data = (DWORD*)(0x00693FF1); // Get Addres with HxD (virtual Memory)
	memset(&Data[0],0x00,6);            // Digits amount = ,x);
	memcpy(&Data[0],"Player",6);        // Digits amount = ,x);

	//For extra memsets:
/*  DWORD* Data1 = (DWORD*)(0x006903A8); 
	memset(&Data1[0],0x00,4);           
	memcpy(&Data1[0],"Data",4); */

/*	DWORD* Data2 = (DWORD*)(0x007DBE6AC); 
	memset(&Data2[0],0x00,4);           
	memcpy(&Data2[0],"Data",4);  */

/*	DWORD* Data3 = (DWORD*)(0x007DBE6AC); 
	memset(&Data3[0],0x00,4);           
	memcpy(&Data3[0],"Data",4);  */

/*	DWORD* Data4 = (DWORD*)(0x007DBE6AC); 
	memset(&Data4[0],0x00,4);           
	memcpy(&Data4[0],"Data",4);  */

/*	DWORD* Data5 = (DWORD*)(0x007DBE6AC); 
	memset(&Data5[0],0x00,4);           
	memcpy(&Data5[0],"Data",4);   */
  }


/*
// OUTRO TESTE de menset em bytes específicos da memória (Tudo testado e funcionando Ok!, descomente e use)      
#define serial_offset           0x00692174  // (TESTE NO SERIAL) Offset serial = UK4l3 = 55 4B 34 6C 33
	*(BYTE*)(serial_offset)		= 0x55;
	*(BYTE*)(serial_offset+1)	= 0x4B;
	*(BYTE*)(serial_offset+2)	= 0x34;
	*(BYTE*)(serial_offset+3)	= 0x6C;
	*(BYTE*)(serial_offset+4)	= 0x33;
*/
