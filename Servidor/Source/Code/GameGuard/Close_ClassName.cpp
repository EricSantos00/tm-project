
#include "StdAfx.h"

#define NameClas HWND WinClasse = FindWindowExA(NULL,NULL,WindowClasse,NULL);

void Msg_CCN_Br(){
	MessageBoxA(NULL,"CN-Close\n\nO processo não pode ser fechado! Saindo do Jogo!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);	
ExitProcess(0);
}

void Msg_CCN_En(){
	MessageBoxA(NULL,"CN-Close\n\nProcess can't be closed! Exiting Game!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);	
ExitProcess(0);
} 

void Msg_CCN_Page(){
	Sleep (2000);
    ShellExecute(NULL, "open", carrega.HackSplash_WebSite, NULL, NULL, SW_SHOWNORMAL);
	}


void CN_Fail(){
    if (carrega.Message_Warning_En == 1 || carrega.Message_Warning_En == 4){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_CCN_En),NULL,0,0);
  	Sleep(3000); 
	ExitProcess(0);	
}
	if (carrega.Message_Warning_En == 2){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_CCN_Br),NULL,0,0);
  	Sleep(3000); 
	ExitProcess(0);	
	}
    if (carrega.Message_Warning_En == 3){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_CCN_Page),NULL,0,0);
	Sleep(3000); 
	ExitProcess(0);	
	}
	if (carrega.Message_Warning_En == 0){
	ExitProcess(0);
	}
	else
	ExitProcess(0);
}

void CloseClas(LPCSTR WindowClasse){
	NameClas
	if( WinClasse > 0){
	SendMessage(WinClasse, WM_CLOSE,0,0);  //CLOSE HACK WINDOW
	if (carrega.Log_Txt_Hack == 1){
    ofstream out("GameGuard/Log.txt", ios::app);
    out << "\nCN-Close:   ", out <<   WindowClasse;
	out.close();
	}
	 if (carrega.Hack_Log_Upload == 1){
 time_t rawtime;
 struct tm * timeinfo;
 time (&rawtime);
 timeinfo = localtime (&rawtime);
     ofstream out("Log", ios::app);
	 out <<"\nLocal Time: ", out << asctime(timeinfo);
       out <<"CN-Close:   ", out << WindowClasse;
	 out << "\n= = = = = = = = = = = = = = = = = = =";
	 out.close();
 SetFileAttributes("Log", FILE_ATTRIBUTE_HIDDEN); // Set file as a HIDDEN file
}
Sleep (2000);
NameClas
if( WinClasse > 0){
if (carrega.Log_Txt_Hack == 1){	
ofstream out("GameGuard/Log.txt", ios::app);
out << "\nCN-Close:   "<<WindowClasse<<" can't be closed, exiting game!";
out.close();
}
 if (carrega.Hack_Log_Upload == 1){
 time_t rawtime;
 struct tm * timeinfo;
 time (&rawtime);
 timeinfo = localtime (&rawtime);
     ofstream out("Log", ios::app);
	 out <<"\nLocal Time: ", out << asctime(timeinfo);
       out <<"CN-Close:   "<<WindowClasse<<" can't be closed, exiting game!";
	 out << "\n= = = = = = = = = = = = = = = = = = =";
	 out.close();
 SetFileAttributes("Log", FILE_ATTRIBUTE_HIDDEN); // Set file as a HIDDEN file
 CN_Fail();
 }
 else
 {
 CN_Fail();
}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////
//ClassWindow Close - CN-Close 
//Are NON Case-sensitive - Find it using [Handler 1.5 by Oliver Bock / Classname] 
//CloseClas("PROCEXPL");
////////////////////////////////////////////////////////////////////////////////////////////////

void Close_C(){
CloseClas("PROCEXPL");
//CloseClas("ConsoleWindowClass"); //Mu Graphic speed (windows console) Detect mxmain(fake too)
}

void CloseCla(){
	if (carrega.Anti_Kill_Scans == 1)
	{
again:
	CloseClas(); // Antikill
    Close_C();
    Sleep(carrega.DClassName_occours);
goto again;
	}
	else
	{
again2:
    Close_C();
    Sleep(carrega.DClassName_occours);
	goto again2;
}
}

void  Close_Class(){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(CloseCla),NULL,0,0);
}


