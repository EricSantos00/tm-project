 #pragma once
/*
Este header, ira compartilhar as structs entre servidor e client a medida que o mesmo for sendo atualizado
outros headers também poder´ser criado como de constantes por exemplo.
*/

#ifndef _SHAREDSTRUCTS_ // Last updated 27/01/2013

#define _SHAREDSTRUCTS_

#define _MSG      	short		  Size;			\
					char		  KeyWord;		\
					char		  CheckSum;		\
					short		  Type;			\
					short		  ID;			\
					unsigned int  ClientTick;

 

#define _PCKHEADER MSG_HSTANDARD Header

#ifdef _WYDCLIENT
 
#endif // _WYDCLIENT
 
#pragma pack(push, 1)

#pragma pack(pop)

#endif