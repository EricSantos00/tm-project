
#include "StdAfx.h"
#include "LimitSingleInstance.h"
   

// The one and only CLimitSingleInstance object.
CLimitSingleInstance g_SingleInstanceObj(TEXT("Global\\{G4ATBCE5-7348-450a-B2YC-CVL5XBF12X3D}"));  //PERSONALIZE THIS LINE FOR MORE SECURITY
int LoadSingleInstance2 (int argc, char* argv[])
{
 if (g_SingleInstanceObj.IsAnotherInstanceRunning()){
   if (carrega.Message_Warning_En == 1){
    MessageBoxA(NULL,"SI-Scan\n\nAnti-kill active! just one Game instance allowed!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
    ExitProcess(0);	
    }
    if (carrega.Message_Warning_En == 2){
	MessageBoxA(NULL,"SI-Scan\n\nO Sistema Anti-kill permite apenas uma instancia de jogo aberta!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
	ExitProcess(0);	
	}	
	else
	{
	MessageBoxA(NULL,"SI-Scan\n\nAnti-kill active! just one Game instance allowed!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
 	ExitProcess(0);	
}
}
return(0);
}


void LoadSingleInstance(){
	LoadSingleInstance2(0,0);
}