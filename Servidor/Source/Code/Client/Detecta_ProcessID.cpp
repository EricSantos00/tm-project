#include "AntCheat.h"
#include <TlHelp32.h>
#include "BaseCli.h"

void Kill_From_Message_Warning() {
	Sleep(3000);
	ExitProcess(0);
}

	void GetProcId(char* ProcName){
    PROCESSENTRY32 pe32;
    HANDLE hSnapshot = NULL;

	pe32.dwSize = sizeof( PROCESSENTRY32 );
    hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );

    if( Process32First( hSnapshot, &pe32 )){
        do{
            if( strcmp( pe32.szExeFile, ProcName ) == 0 )
            {
			HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);  // Close detected process
			TerminateProcess(hProcess,NULL);                                               // Close detected process

	ExitProcess(0);
	Msg_W_Br();
		
	

            }
        }while( Process32Next( hSnapshot, &pe32 ) );
    }
    if( hSnapshot != INVALID_HANDLE_VALUE )
        CloseHandle( hSnapshot );   
}

////////////////////////////////////////////////////////////////////////////////////////////////
//Process ID - PID-Scan 
//Are Case-sensitive - Find it using: Windows Task Manger/table processes (ctrl + alt + del)
//GetProcId("xxxx.exe");
//GetProcId("XXXX.EXE"); 
////////////////////////////////////////////////////////////////////////////////////////////////

void ClasseCheckPross(){ 
	// PID Detector are Case-sensitive!
	GetProcId("ollydbg.exe*32");
	GetProcId("ollydbg.exe");
	GetProcId("bvkhex.exe");
    GetProcId("cheatengine-x86_64.exe");
	GetProcId("HxD.exe");
	GetProcId("procexp2.exe");
	GetProcId("Hide Toolz3.3.3.exe");
	GetProcId("SbieSvc.exe");    // < sandbox 
	GetProcId("SbieSvc*32.exe"); // < sandbox 
	GetProcId("SbieSvc*32.exe"); // < sandbox 
	GetProcId("SbieCtrl.exe");   // < sandbox 
	GetProcId("Start.exe");      // < sandbox 
	GetProcId("WPE PRO.exe");
}

void PC_Scan(){
	/*if (carrega.Anti_Kill_Scans == 1)
	{
again:
	DProcID(); //Antikill
    ClasseCheckPross();
    Sleep(carrega.DPID_occours);
    goto again;
}
	else
	{*/
//again2:
    ClasseCheckPross();
  //  Sleep(58000);
   // goto again2;
//}
}

void DetectID(){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(PC_Scan),NULL,0,0);
	}

