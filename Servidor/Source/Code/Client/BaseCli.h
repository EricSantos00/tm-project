#include <cstdint>
#include <basetsd.h>
#ifndef BASE_CLI
#define BASE_CLI

extern INT16 cCheck;
extern uint16_t LastPacketId;
class ConfigR
{
public:
	char* Nome_do_Executavel;
	char* Nome_do_Launcher;
	char* Nome_da_DLL;
	char* Launcher_Window;
	char* MsgBox_Title;
	char* Nome;
	char* Nome2;
	char* Serial;
	char* Versao;
	char* IP;
	char* Jump_asm;

	int ATIVA_TESTE;
	int Minimum_thread;
	int Dont_kill_yet;
	int Config_serial_versao;
	int Entrypoint_Memset;
	int Verifica_Nome;
	int Splash_Screen;
	int ChecarClient;
	int CheckSun_Geral;
	int CRC_Player;
	int CheckSum_LDexedll;
	int CheckSum_LDexe01dll;
	int CRC_Launcher;
	int Detecta_Inject;
	int GlowDLL;
	int MinimizerDLL;
	int Detecta_Dump;
	int Launcher_Ativo;
	int Detecta_Kill;
	int EnableLogFile;
	int SendClientMsg;
	int Detecta_Hide;
	int Detecta_Speed;
	int Detecta_PID;
	int Detecta_Window;
	int Detecta_Heuristica;
	int Detecta_ClassName;

	long CheckSum_Launcher;
	long CheckSum_LDexe;
	long CheckSum_LDdll;
	long CheckSum_LD01;
	long CheckSum_Core;
	long CheckSum_GameGuard;
	long CRC_Terrain3;
	long CRC_Terrain4;
	long CRC_Terrain5;
	long CRC_Terrain6;
	long CRC_Terrain7;
};
bool initialize();
void cleanup();
extern ConfigR Config;
extern char LoadFileName[24];

#endif // !BASE_CLI
