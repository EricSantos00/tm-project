#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <stdio.h> 
#include <fcntl.h>
#include <io.h>
#include <string.h>        
#include <time.h>
#include <mbstring.h>
#include "../Basedef.h"
#ifndef ANT_CH
#define ANT_CH

bool ReadConfig(const char* FileName);

void WINAPI AntiHack();

void CloseGame();
void BackupWinsockData();
unsigned long __stdcall AntiWPEPro(void* pVoid);
void I_loop();
void I_Scan();
void Injetado();
void Msg_I_Br();
void Dll_Inject();
void DetectID();
//void AntiInject();
//BOOLEAN BlockAPI(HANDLE hProcess, CHAR* libName, CHAR* apiName);

// checa se tem algum aplicativo aberto
void TitleCheckWindow();
void Msg_W_Br();
bool TitleWindow(LPCSTR WindowTitle);
void W_Scan();
void YProtectionMain();
DWORD __forceinline IsInsideVPC_exceptionFilter(LPEXCEPTION_POINTERS ep);
bool IsInsideVPC();
bool IsInsideVMWare();
bool isInsideVBox();
bool isVBoxBios();
void AllToUpper(char* str, unsigned long len);
unsigned char* ScanDataForString(unsigned char* data, unsigned long data_length, unsigned char* string2);






// Mais Proteções
bool GetFileName(char* text);

#endif // !ANT_CH
