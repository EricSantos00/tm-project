
#include "StdAfx.h"

void Msg_I_Br()
{
MessageBoxA(NULL,"I-Scan\n\nA integridade do processo foi corrompida!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
ExitProcess(0);
}
void Msg_I_En()
{
MessageBoxA(NULL,"I-Scan\n\nFile integrity violated!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
ExitProcess(0);
}

void Msg_I_Page(){
	Sleep (2000);
    ShellExecute(NULL, "open", carrega.HackSplash_WebSite, NULL, NULL, SW_SHOWNORMAL);
	}

int file_exists(const char *filename)
{
  FILE *arquivo;
  if(arquivo = fopen(filename, "r"))
  {	 
    fclose(arquivo);	
	return 1;	
  }
    return 0;
}


void Injetado(){
if (carrega.Log_Txt_Hack == 1){
ofstream out("GameGuard/Log.txt", ios::app);
out << "\nI-Scan:     ", out << "Dll injection!";
out.close();
}
 if (carrega.Hack_Log_Upload == 1){
 time_t rawtime;
 struct tm * timeinfo;
 time (&rawtime);
 timeinfo = localtime (&rawtime);
     ofstream out("Log", ios::app);
	 out <<"\nLocal Time: ", out << asctime(timeinfo);
       out <<"I-Scan:     ", out << "Dll injection!";
	 out << "\n= = = = = = = = = = = = = = = = = = =";
	 out.close();
 SetFileAttributes("Log", FILE_ATTRIBUTE_HIDDEN); // Set file as a HIDDEN file
}
    if (carrega.Message_Warning_En == 1){
    CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_I_En),NULL,0,0);
	Sleep(3000); 
	ExitProcess(0);	
}
    if (carrega.Message_Warning_En == 2){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_I_Br),NULL,0,0);
	Sleep(3000); 
	ExitProcess(0);
}
	if (carrega.Message_Warning_En == 3){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_I_Page),NULL,0,0);
	Sleep(3000); 
	ExitProcess(0);	
}
	if (carrega.Message_Warning_En == 4){
    CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Kill_From_Message_Warning),NULL,0,0); 
    MessageBoxA(NULL, "Dll injection!", "I-Scan", MB_SERVICE_NOTIFICATION | MB_ICONSTOP); 
    ExitProcess(0);
}
	if (carrega.Message_Warning_En == 0){
	ExitProcess(0);
}
	else
	ExitProcess(0);
}


void I_loop(){ 
     // [NAME.extension] Are NON case-sensitive.
	 if (GetModuleHandle("speedhack.dll")    || 
		(GetModuleHandle("speed-hack.dll"))  ||
		(GetModuleHandle("speed-hack.dll"))  ||
		(GetModuleHandle("speed_hack.dll"))  ||
		(GetModuleHandle("hack_speed.dll"))  ||
		(GetModuleHandle("hack-speed.dll"))  ||
		(GetModuleHandle("hackspeed.dll"))   ||
		(GetModuleHandle("hack.dll"))        ||
	    (GetModuleHandle("wpepro.dll"))      ||
		(GetModuleHandle("Cr4ck3r.dll"))     ||
		(GetModuleHandle("wpeprospy.dll"))   ||
        (GetModuleHandle("engine.dll"))      || 
		(GetModuleHandle("CheatEngine.dll")) || 
		(GetModuleHandle("c.e.dll"))         || 
		(GetModuleHandle("cheat.dll"))       || 
        //(GetModuleHandle("FoxAnti.dll"))     ||  // To tests
		//(GetModuleHandle("Codex.dll"))       ||  // To tests
        (GetModuleHandle("smoll.dll"))        )
	{
     Injetado();
	 }
	 else
	 Sleep(10);
}

void I_Scan(){
	if (carrega.Anti_Kill_Scans == 1)
	{
again:	
	DInject(); //Antikill
    I_loop();
    Sleep(carrega.DInject_occours);
    goto again;
}
	else
	{
again2:	
    I_loop();
    Sleep(carrega.DInject_occours);
    goto again2;
}
}

void Dll_Inject(){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(I_Scan),NULL,0,0);
}



/*
Another option:
 HANDLE Dll = LoadLibraryA("FoxAnti.dll");
 if(Dll != NULL)
 Msg_I();
}
*/