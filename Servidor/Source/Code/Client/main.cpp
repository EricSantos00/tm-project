#include "main.h"
#include "AntCheat.h"
#include "BaseCli.h"

STRUCT_QUESTDIARIA QuestDay;
STRUCT_CLIENTPAC g_pSendClientPac;

int __stdcall DllMain(HINSTANCE hInstDLL, DWORD catchReason, LPVOID lpResrv)
{
	__try
	{
		switch (catchReason)
		{
		case DLL_PROCESS_ATTACH:
		{
			DWORD dwOldProtectFlag_text;
			VirtualProtect((int*)0x0401000, 0x5F0FFF - 0x0401000, 0x40, &dwOldProtectFlag_text);

			HookNaked::Start();

			/* Tira os check-sum para manipulação de ponteiros */
			/* Remove - Client Is Bad Ptr */
			JMP_NEAR(0x005D33FD, (INT32*)0x005D3418);

			/* Remove - Client Is Write Ptr */
			JMP_NEAR(0x005D3419, (INT32*)0x005D3434);

			/* Remove - Client Is Bad Code Ptr */
			JMP_NEAR(0x005D3435, (INT32*)0x005D344C);

			BASE_EffectMagic(true);
			AffectIconLimit();

			VirtualProtect((int*)0x0401000, 0x5F0FFF - 0x0401000, dwOldProtectFlag_text, &dwOldProtectFlag_text);
			//break;

			BackupWinsockData();
			CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)AntiHack, NULL, 0, 0);
			Dll_Inject();
			TitleCheckWindow();
			YProtectionMain();
			//initialize();
			DisableThreadLibraryCalls(hInstDLL);

			if (lpResrv == nullptr) // Dynamic Load
			{
				return initialize() ? TRUE : []() {
					MessageBox(0, "Não foi possível carregar a Library", "Erro: Library Eternal", MB_OK);
					return FALSE;
				}();
			}
		}

		case DLL_PROCESS_DETACH:
		{
			cleanup();
			FreeLibrary(hInstDLL);
			break;
		}

		}
	}
	__except (GetExceptionCode())
	{

	}

	return TRUE;
}