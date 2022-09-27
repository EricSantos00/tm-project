
#include "BaseCli.h"
#include "main.h"
#include "AntCheat.h"

ConfigR Config;
char LoadFileName[24];
INT16 cCheck;

uint16_t LastPacketId;

bool initialize()
{
	
	if (IsInsideVPC())
	{
		MessageBoxA(0, "Detectado Maquina Virtual", "Info", MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
		return false;
	}
	if (IsInsideVMWare())
	{
		MessageBoxA(0, "Detectado Maquina Virtual", "Info", MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
		return false;

	}

	if (isInsideVBox())
	{
		MessageBoxA(0, "Detectado Maquina Virtual", "Info", MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
		return false;
	}

	if (isVBoxBios())
	{
		MessageBoxA(0, "Detectado Maquina Virtual", "Info", MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
		return false;
	}

	return true;
}
void cleanup()
{


}


void Startprogress(string Filename)
{
	ShellExecute(NULL, "open", Filename.c_str(), NULL, NULL, SW_SHOWMINIMIZED);
}
