
#include "StdAfx.h"


void Msg_CLASS_Br(){	
	MessageBoxA(NULL,"HC-Scan\n\nConteúdo suspeito detectado!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
	ExitProcess(0);
}
void Msg_CLASS_En(){	
	MessageBoxA(NULL,"HC-Scan\n\nAn illegal choice haas been detected!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
	ExitProcess(0);
}

void Msg_CLASS_Page(){
	Sleep (2000);
    ShellExecute(NULL, "open", carrega.HackSplash_WebSite, NULL, NULL, SW_SHOWNORMAL);
	}

BOOL CALLBACK heurclass(HWND hwnd, LPARAM lParam){
    static TCHAR y[60];
    GetClassName(hwnd, y, 60);

////////////////////////////////////////////////////////////////////////////////////////////////
//Heuristic ClassWindow - HC-Scan 
//Are NON Case-sensitive - Find it using [Handler 1.5 by Oliver Bock / Classname] 
//_tcsstr(y,"xxxx")  Just one word, without empty space
////////////////////////////////////////////////////////////////////////////////////////////////

if (_tcsstr(y,"ProcessHacker")          || 
	_tcsstr(y,"PROCEXP")                || //ProcessExplorer
	_tcsstr(y,"TFormMain.UnicodeClass") || //HxD
	_tcsstr(y,"WindowsForms10")         || 	 
	_tcsstr(y,"obj_Form")){                //Hidetoolz

if (carrega.Log_Txt_Hack == 1){
ofstream out("GameGuard/Log.txt", ios::app);
out << "\nHC-Scan:    ", out <<   y;    // printf ("Found Hack = %s " , windowName);
out.close();
}
 if (carrega.Hack_Log_Upload == 1){
 time_t rawtime;
 struct tm * timeinfo;
 time (&rawtime);
 timeinfo = localtime (&rawtime);
     ofstream out("Log", ios::app);
	 out <<"\nLocal Time: ", out << asctime(timeinfo);
       out <<"HC-Scan:    ", out << y;
	 out << "\n= = = = = = = = = = = = = = = = = = =";
	 out.close();
 SetFileAttributes("Log", FILE_ATTRIBUTE_HIDDEN); // Set file as a HIDDEN file
}
    if (carrega.Message_Warning_En == 1){
    CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_CLASS_En),NULL,0,0);
	Sleep(3000); 
	ExitProcess(0);	
}
    if (carrega.Message_Warning_En == 2){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_CLASS_Br),NULL,0,0);
	Sleep(500); 
	ExitProcess(0);
	}
	if (carrega.Message_Warning_En == 3){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_CLASS_Page),NULL,0,0);
	Sleep(3000); 
	ExitProcess(0);	
	}
	if (carrega.Message_Warning_En == 4){
    CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Kill_From_Message_Warning),NULL,0,0); 
    MessageBoxA(NULL, y, "HC-Scan", MB_SERVICE_NOTIFICATION | MB_ICONSTOP); 
    ExitProcess(0);
	}
	if (carrega.Message_Warning_En == 0){
	ExitProcess(0);	
	}
	else
	ExitProcess(0);				
    return FALSE;
    }
	//cout <<"true";
	return TRUE;
}


void heuristiclass(){
	EnumWindows(heurclass, NULL);
}

void heuri11(){
if (carrega.Anti_Kill_Scans == 1)
	{
again:
    DHeuriClass(); //Antikill
    heuristiclass();
    Sleep (carrega.DHeuristica_Class_occours);
    goto again;
}
else
{
	again2:
    heuristiclass();
    Sleep (carrega.DHeuristica_Class_occours);
	goto again2;
}
}

void Heuristicclass(){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(heuri11),NULL,0,0);
}