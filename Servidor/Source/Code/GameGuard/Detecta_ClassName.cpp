
#include "StdAfx.h"

void Msg_CN_Br(){
	MessageBoxA(NULL,"CN-Scan\n\nConteúdo suspeito detectado!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);	
ExitProcess(0);
} 

void Msg_CN_En(){
	MessageBoxA(NULL,"CN-Scan\n\nAn illegal choice haas been detected!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);	
ExitProcess(0);
}

void Msg_CN_Page(){
	Sleep (2000);
    ShellExecute(NULL, "open", carrega.HackSplash_WebSite, NULL, NULL, SW_SHOWNORMAL);
	}

void ClasseWindow(LPCSTR WindowClasse){
	HWND WinClasse = FindWindowExA(NULL,NULL,WindowClasse,NULL);
	if( WinClasse > 0){
		SendMessage(WinClasse, WM_CLOSE,0,0);  //CLOSE HACK WINDOW
	if (carrega.Log_Txt_Hack == 1){
    ofstream out("GameGuard/Log.txt", ios::app);
    out << "\nCN-Scan:    ", out <<   WindowClasse;
	out.close();
}
 if (carrega.Hack_Log_Upload == 1){
 time_t rawtime;
 struct tm * timeinfo;
 time (&rawtime);
 timeinfo = localtime (&rawtime);
     ofstream out("Log", ios::app);
	 out <<"\nLocal Time: ", out << asctime(timeinfo);
       out <<"CN-Scan:    ", out << WindowClasse;
	 out << "\n= = = = = = = = = = = = = = = = = = =";
	 out.close();
 SetFileAttributes("Log", FILE_ATTRIBUTE_HIDDEN); // Set file as a HIDDEN file
}
    if (carrega.Message_Warning_En == 1){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_CN_En),NULL,0,0);
  	Sleep(3000); 
	ExitProcess(0);	
}
	if (carrega.Message_Warning_En == 2){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_CN_Br),NULL,0,0);
  	Sleep(3000); 
	ExitProcess(0);	
	}
    if (carrega.Message_Warning_En == 3){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_CN_Page),NULL,0,0);
	Sleep(3000); 
	ExitProcess(0);	
}
	 if (carrega.Message_Warning_En == 4){
     CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Kill_From_Message_Warning),NULL,0,0); 
     MessageBoxA(NULL, WindowClasse, "CN-Scan", MB_SERVICE_NOTIFICATION | MB_ICONSTOP); 
     ExitProcess(0);
}
	 if (carrega.Message_Warning_En == 0){
	ExitProcess(0);
}
	else
	ExitProcess(0);
}
}


////////////////////////////////////////////////////////////////////////////////////////////////
//ClassWindow scan - CN-Scan 
//Are NON Case-sensitive - Find it using [Handler 1.5 by Oliver Bock / Classname] 
//ClasseWindow("xxxx"); 
////////////////////////////////////////////////////////////////////////////////////////////////

void ClasseCheckWindow(){    
	//ClasseWindow("ConsoleWindowClass"); // Prompt de comando 
	//ClasseWindow("ThunderRT6FormDC");   // autoclic Klic0r
	ClasseWindow("PROCEXPL");             // Process explorer
	ClasseWindow("TreeListWindowClass");  // Process explorer (Process windows)
	ClasseWindow("ProcessHacker");        // Process Hacker	
	ClasseWindow("PhTreeNew");            // Process Hakcer (Process windows)
	ClasseWindow("RegEdit_RegEdit");      // Regedit
	ClasseWindow("0x150114 (1376532)");   // Win 7 - System configuration
	ClasseWindow("SysListView32");        // Lista de processos do process explorer
	ClasseWindow("Tmb");
	ClasseWindow("TformSettings");
	ClasseWindow("Afx:400000:8:10011:0:20575");
	ClasseWindow("TWildProxyMain");
	ClasseWindow("TUserdefinedform");
	ClasseWindow("TformAddressChange");
	ClasseWindow("TMemoryBrowser");
	ClasseWindow("TFoundCodeDialog");
	}

void CN_Scan(){
	if (carrega.Anti_Kill_Scans == 1)
	{
again:
	DClass(); //Antikill
    ClasseCheckWindow();
    Sleep(carrega.DClassName_occours);
    goto again;
}
	else
	{
again2:
    ClasseCheckWindow();
    Sleep(carrega.DClassName_occours);
    goto again2;
}
}

void CNProtection(){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(CN_Scan),NULL,0,0);
}


