
#include "StdAfx.h"

void Msg_CW_Br(){
	MessageBoxA(NULL,"W-Close\n\nO processo não pode ser fechado! Saindo do Jogo!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);	
ExitProcess(0);
}

void Msg_CW_En(){
	MessageBoxA(NULL,"W-Close\n\nProcess can't be closed! Exiting Game!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);	
ExitProcess(0);
} 

void Msg_CW_Page(){
	Sleep (2000);
    ShellExecute(NULL, "open", carrega.HackSplash_WebSite, NULL, NULL, SW_SHOWNORMAL);
	}


void Close_W_fail(){
	if (carrega.Message_Warning_En == 1 || carrega.Message_Warning_En == 4){
    CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_CW_En),NULL,0,0);
	Sleep(3000); 
	ExitProcess(0);	
}
    if (carrega.Message_Warning_En == 2){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_CW_Br),NULL,0,0);
	Sleep(3000); 
	ExitProcess(0);	
	}
	if (carrega.Message_Warning_En == 3){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_CW_Page),NULL,0,0);
	Sleep(3000); 
	ExitProcess(0);	
	}
	if (carrega.Message_Warning_En == 0){
	ExitProcess(0);
	}
	else
	ExitProcess(0);
}

bool CloseWin(LPCSTR WindowTitle){
HWND WinTitle = FindWindowA(NULL,WindowTitle);
if( WinTitle > 0){
SendMessage(WinTitle, WM_CLOSE,0,0); 
if (carrega.Log_Txt_Hack == 1){	
ofstream out("GameGuard/Log.txt", ios::app);
out << "\nW-Close:     ", out <<   WindowTitle;
out.close();
}
	 if (carrega.Hack_Log_Upload == 1){
 time_t rawtime;
 struct tm * timeinfo;
 time (&rawtime);
 timeinfo = localtime (&rawtime);
     ofstream out("Log", ios::app);
	 out <<"\nLocal Time: ", out << asctime(timeinfo);
       out <<"W-Close:    ", out << WindowTitle;
	 out << "\n= = = = = = = = = = = = = = = = = = =";
	 out.close();
 SetFileAttributes("Log", FILE_ATTRIBUTE_HIDDEN); // Set file as a HIDDEN file
}
Sleep (2000);
HWND WinTitle = FindWindowA(NULL,WindowTitle);
if( WinTitle > 0){
if (carrega.Log_Txt_Hack == 1){	
ofstream out("GameGuard/Log.txt", ios::app);
out << "\n W-Close:    " <<WindowTitle<<" can't be closed, exiting game!";
out.close();
}
	 if (carrega.Hack_Log_Upload == 1){
 time_t rawtime;
 struct tm * timeinfo;
 time (&rawtime);
 timeinfo = localtime (&rawtime);
     ofstream out("Log", ios::app);
	 out <<"\nLocal Time: ", out << asctime(timeinfo);
       out <<"W-Close:    " <<WindowTitle<<" can't be closed, exiting game!";
	 out << "\n= = = = = = = = = = = = = = = = = = =";
	 out.close();
 SetFileAttributes("Log", FILE_ATTRIBUTE_HIDDEN); // Set file as a HIDDEN file
 Close_W_fail();
}
	 else
	 {
	 Close_W_fail();
}
	return false;
	}
}
	return true;
}



////////////////////////////////////////////////////////////////////////////////////////////////
//Window close scan - W-Close 
//Are Case-sensitive - Find it just looking window name or using [Handler 1.5 by Oliver Bock] 
//TitleWindow("xxxx");
////////////////////////////////////////////////////////////////////////////////////////////////
void Close_Winx(){
CloseWin("Cheat Engine 5.0");
}

void CloseWin_(){
	if (carrega.Anti_Kill_Scans == 1)
	{
again:
	CloseWin(); // Antikill
    Close_Winx();
    Sleep(carrega.DWindow_occours);
    goto again;
}
	else
	{
	again2:
    Close_Winx();
    Sleep(carrega.DWindow_occours);
    goto again2;
	}
}

void Close_Window(){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(CloseWin_),NULL,0,0);
}

