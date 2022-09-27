#include "AntCheat.h"
#include "BaseCli.h"
#include "main.h"

bool ReadConfig(const char* FileName)
{
	FILE* pFile = NULL;


	pFile = fopen(FileName, "r");


	if (pFile != NULL)
	{
		return true;
	}
	// isso é o anti hacker, que vai pro cliente dentro da DLL ta lgd ?
	return false;
}

unsigned static long dwRecvCall; // Addr do início da func Recv
unsigned static long dwSendCall; // Addr do início da func Send
unsigned static char bAddr_r[6], bAddr_s[6]; // Bytes iniciais das funções send/recv

void BackupWinsockData() {
	LoadLibrary("ws2_32.dll"); // Hook na dll da winsock2
	dwRecvCall = (unsigned long)GetProcAddress(GetModuleHandle("ws2_32.dll"), "recv"); // Seta o valor de dwRecvCall com o addrbase da func Recv
	dwSendCall = (unsigned long)GetProcAddress(GetModuleHandle("ws2_32.dll"), "send"); // Seta o valor de dwSendCall com o addrbase da func Send
	ReadProcessMemory(GetCurrentProcess(), (LPVOID)dwRecvCall, bAddr_r, 6, 0); // Move os bytes iniciais originais da func recv para o buffer
	ReadProcessMemory(GetCurrentProcess(), (LPVOID)dwSendCall, bAddr_s, 6, 0); // Move os bytes iniciais originais da func send para o buffer
}
void CloseGame() {
	DWORD exitCode;
	GetExitCodeProcess(GetCurrentProcess(), &exitCode);
	ExitProcess(exitCode);
}
void WINAPI AntiHack() {
	while (true) {
		if (memcmp((LPVOID)dwRecvCall, bAddr_r, 6) != 0) CloseGame(); // Verifica se os bytes iniciais da func Recv estão diferentes do original
		if (memcmp((LPVOID)dwSendCall, bAddr_s, 6) != 0) CloseGame(); // Verifica se os bytes iniciais da func Send estão diferentes do original
		Sleep(1000); // Delay para não dar lag
	}
}
unsigned long __stdcall AntiWPEPro(void* pVoid)
{
	bool bHooked = false;
	unsigned char szBuffer[8];

	// First 6 bytes of of Send/Recv
	unsigned char bOriginal[] = "\x55"         // PUSH EBP
		"\x8B\xEC\x83"   // MOV EBP, ESP
		"\xEC\x10";   // SUB ESP, 10

	int i;

	unsigned long dwRecvCall = (unsigned long)GetProcAddress(GetModuleHandle("WS2_32.dll"), "recv");
	unsigned long dwSendCall = (unsigned long)GetProcAddress(GetModuleHandle("WS2_32.dll"), "send");

	while (true)
	{
		ReadProcessMemory(GetCurrentProcess(), (void*)dwRecvCall, szBuffer, 6, 0);

		for (i = 0; i < 6; i++)
		{
			// If we find one part missing, write the original bytes back and break the loop
			if (bOriginal[i] != szBuffer[i])
			{
				WriteProcessMemory(GetCurrentProcess(), (void*)dwRecvCall, bOriginal, 6, 0);
				break;
			}
		}

		ReadProcessMemory(GetCurrentProcess(), (void*)dwSendCall, szBuffer, 6, 0);

		for (i = 0; i < 6; i++)
		{
			// Send + Recvs first 6 bytes are the same, we can use the same buffer
			if (bOriginal[i] != szBuffer[i])
			{
				WriteProcessMemory(GetCurrentProcess(), (void*)dwSendCall, bOriginal, 6, 0);
				break;
			}
		}

		Sleep(500);
	}

	return 0;
};


void I_loop()
{
	// [NAME.extension] Are NON case-sensitive.
	if (GetModuleHandle("speedhack.dll") ||
		(GetModuleHandle("speed-hack.dll")) ||
		(GetModuleHandle("speed-hack.dll")) ||
		(GetModuleHandle("speed_hack.dll")) ||
		(GetModuleHandle("hack_speed.dll")) ||
		(GetModuleHandle("hack-speed.dll")) ||
		(GetModuleHandle("hackspeed.dll")) ||
		(GetModuleHandle("hack.dll")) ||
		(GetModuleHandle("wpepro.dll")) ||
		(GetModuleHandle("Cr4ck3r.dll")) ||
		(GetModuleHandle("wpeprospy.dll")) ||
		(GetModuleHandle("engine.dll")) ||
		(GetModuleHandle("CheatEngine.dll")) ||
		(GetModuleHandle("c.e.dll")) ||
		(GetModuleHandle("cheat.dll")) ||
		(GetModuleHandle("mukilin.dll")) ||
		(GetModuleHandle("Whook.dll")) ||
		(GetModuleHandle("whook7556.dll")) ||
		(GetModuleHandle("hook.dll")) ||
		(GetModuleHandle("wHook.dll")) ||
		(GetModuleHandle("Hook756.dll")) ||
		(GetModuleHandle("WHOOK.dll")) ||
		(GetModuleHandle("whook756.dll")) ||
		(GetModuleHandle("w1.dll")) ||
		(GetModuleHandle("w2.dll")) ||
		(GetModuleHandle("w3.dll")) ||
		(GetModuleHandle("w4.dll")) ||
		(GetModuleHandle("w5.dll")) ||
		(GetModuleHandle("w6.dll")) ||
		(GetModuleHandle("w7.dll")) ||
		(GetModuleHandle("w8.dll")) ||
		(GetModuleHandle("w9.dll")) ||
		(GetModuleHandle("w10.dll")) ||
		(GetModuleHandle("whook.dll"))
		)
	{
		Injetado();
	}
	else
		Sleep(100);
}

void Msg_I_Br()
{
	MessageBoxA(NULL, "GameGuard\n\nA integridade do processo foi corrompida!", Config.MsgBox_Title, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}

void Injetado()
{

	if (Config.EnableLogFile == 1)
	{
		using namespace std;
		ofstream out("WYD.log", ios::app);
		out << "\n AntiHacker:  ", out << "File integrity violated!";
	}
	if (Config.SendClientMsg == 2)
	{
		CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_I_Br), NULL, 0, 0);
		Sleep(5000);
		ExitProcess(0);
	}
	if (Config.SendClientMsg == 0)
	{
		ExitProcess(0);
	}
	else
		ExitProcess(0);
}

void I_Scan()
{
again:
	I_loop();
	DetectID();
	Sleep(10000);
	goto again;
}

void Dll_Inject()
{
	CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(I_Scan), NULL, 0, 0);
}

void Msg_W_Br()
{
	MessageBoxA(NULL, "GameGuard\n\nConteúdo suspeito detectado!", Config.MsgBox_Title, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}


bool TitleWindow(LPCSTR WindowTitle)
{
	HWND WinTitle = FindWindowA(NULL, WindowTitle);
	if (WinTitle > 0)
	{

		if (Config.EnableLogFile == 1)
		{
			using namespace std;
			ofstream out("WYD.log", ios::app);
			out << "\n AntiHacker:  ", out << WindowTitle;
		}
		if (Config.SendClientMsg == 2)
		{
			Sleep(5000);
			ExitProcess(0);
			CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Msg_W_Br), NULL, 0, 0);
		}
		if (Config.SendClientMsg == 0)
		{
			ExitProcess(0);
		}
		else
			ExitProcess(0);
		return false;
	}
	return true;
}


void TitleCheckWindow()
{
	TitleWindow("Cheat Engine 5.0");
	TitleWindow("Cheat Engine 5.1");
	TitleWindow("Cheat Engine 5.1.1");
	TitleWindow("Cheat Engine 5.2");
	TitleWindow("Cheat Engine 5.3");
	TitleWindow("Cheat Engine 5.4");
	TitleWindow("Cheat Engine 5.5");
	TitleWindow("Cheat Engine 5.6");
	TitleWindow("Cheat Engine 5.6.1");
	TitleWindow("Cheat Engine 6.0");
	TitleWindow("Cheat Engine 6.1");
	TitleWindow("Cheat Engine 6.2");
	TitleWindow("Cheat Engine 6.3");
	TitleWindow("Cheat Engine 6.4");
	TitleWindow("Cheat Engine 6.5");
	TitleWindow("Cheat Engine 7.1");
	TitleWindow("Cheat Engine");
	TitleWindow("WPE PRO");
	TitleWindow("WPePro 0.9a");
	TitleWindow("WPePro 1.3");
}

void W_Scan()
{
again:
	TitleCheckWindow();
	//dectMaqVirtual();
	Sleep(1000);
	goto again;
}

void YProtectionMain()
{
	CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(W_Scan), NULL, 0, 0);
}

DWORD __forceinline IsInsideVPC_exceptionFilter(LPEXCEPTION_POINTERS ep)
{
	PCONTEXT ctx = ep->ContextRecord;

	ctx->Ebx = -1;
	ctx->Eip += 4;
	return EXCEPTION_CONTINUE_EXECUTION;
}

bool IsInsideVPC()
{
	bool rc = false;

	__try
	{
		_asm push ebx
		_asm mov  ebx, 0
		_asm mov  eax, 1


		_asm __emit 0Fh
		_asm __emit 3Fh
		_asm __emit 07h
		_asm __emit 0Bh

		_asm test ebx, ebx
		_asm setz[rc]
			_asm pop ebx
	}

	__except (IsInsideVPC_exceptionFilter(GetExceptionInformation()))
	{
	}

	return rc;
}

void AllToUpper(char* str, unsigned long len)
{
	for (unsigned long c = 0; c < len; c++)
	{
		if (str[c] >= 'a' && str[c] <= 'z')
		{
			str[c] -= 32;
		}
	}
}

unsigned char* ScanDataForString(unsigned char* data, unsigned long data_length, unsigned char* string2)
{
	unsigned long string_length = strlen((char*)string2);
	for (unsigned long i = 0; i <= (data_length - string_length); i++)
	{
		if (strncmp((char*)(&data[i]), (char*)string2, string_length) == 0) return &data[i];
	}
	return 0;
}

bool isVBoxBios()
{
	HKEY hk = 0;
	int ret = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Services\\mssmbios\\data", 0, KEY_ALL_ACCESS, &hk);
	if (ret == ERROR_SUCCESS)
	{
		unsigned long type = 0;
		unsigned long length = 0;
		ret = RegQueryValueEx(hk, "SMBiosData", 0, &type, 0, &length);
		if (ret == ERROR_SUCCESS)
		{
			if (length)
			{
				char* p = (char*)LocalAlloc(LMEM_ZEROINIT, length);
				if (p)
				{
					ret = RegQueryValueEx(hk, "SMBiosData", 0, &type, (unsigned char*)p, &length);
					if (ret == ERROR_SUCCESS)
					{
						AllToUpper(p, length);
						unsigned char* x1 = ScanDataForString((unsigned char*)p, length, (unsigned char*)"INNOTEK GMBH");
						unsigned char* x2 = ScanDataForString((unsigned char*)p, length, (unsigned char*)"VIRTUALBOX");
						unsigned char* x3 = ScanDataForString((unsigned char*)p, length, (unsigned char*)"SUN MICROSYSTEMS");
						unsigned char* x4 = ScanDataForString((unsigned char*)p, length, (unsigned char*)"VIRTUAL MACHINE");
						unsigned char* x5 = ScanDataForString((unsigned char*)p, length, (unsigned char*)"VBOXVER");
						if (x1 || x2 || x3 || x4 || x5)
						{
							return true;
						}
					}
					LocalFree(p);
				}
			}
		}
		RegCloseKey(hk);
	}
	return false;
}

bool isInsideVBox()
{
	bool rc = false;
	HKEY HK = 0;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\ACPI\\DSDT\\VBOX__", 0, KEY_READ, &HK) == ERROR_SUCCESS)
	{
	//	MessageBox(0, "VirtualBox detected", "waliedassar", 0);
		rc = true;
	}



	return rc;
}

bool IsInsideVMWare()
{
	bool rc = true;

	__try
	{
		__asm
		{
			push   edx
			push   ecx
			push   ebx

			mov    eax, 'VMXh'
			mov    ebx, 0
			mov    ecx, 10
			mov    edx, 'VX'

			in     eax, dx

			cmp    ebx, 'VMXh'
			setz[rc]

			pop    ebx
			pop    ecx
			pop    edx
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		rc = false;
	}

	return rc;
}




