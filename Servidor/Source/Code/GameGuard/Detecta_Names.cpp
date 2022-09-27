
#include "StdAfx.h"

// CHECK IF MAIN.EXE VALUES ARE CORRECT ///////////////////////////////
void CheckConfigFile(){
{
HWND WinTitle = FindWindowA(NULL, carrega.MainWindowName);
if( WinTitle != 0){
	MessageBoxA(NULL,"WARNING! [START.cpp > Test_Main_Win_Class_PID = Turned ON]\n\nMain Window found!\n\nClick Ok to search Main Window Class.","CONFIGURATION MESSAGE", MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}
else
{
	MessageBoxA(NULL,"WARNING! [START.cpp > Test_Main_Win_Class_PID = Turned ON]\n\n Main Window NOT FOUND!\n\nCheck [START.cpp > carrega.MainWindowName] configuration!","CONFIGURATION MESSAGE", MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
    ExitProcess(0);
}
/////////////////////////////////
HWND WinClasse = FindWindowExA(NULL,NULL,carrega.MainClassName,NULL);
if( WinClasse != 0){
	MessageBoxA(NULL,"WARNING! [START.cpp > Test_Main_Win_Class_PID = Turned ON]\n\n Main Class Window found!\n\nClick Ok to search Main PID.","CONFIGURATION MESSAGE", MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}
else
{
	MessageBoxA(NULL,"WARNING! [START.cpp > Test_Main_Win_Class_PID = Turned ON]\n\n Main Class Window NOT FOUND!\n\nCheck [START.cpp > carrega.MainClassName] configuration!","CONFIGURATION MESSAGE", MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
	ExitProcess(0);
}
/////////////////////////////////
    PROCESSENTRY32 pe32;
    HANDLE hSnapshot = NULL;
	pe32.dwSize = sizeof( PROCESSENTRY32 );
    hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
    if( Process32First( hSnapshot, &pe32 )){
        do{
            if( strcmp( pe32.szExeFile, carrega.Nome_do_Main ) == 0 )
            {
	MessageBoxA(NULL,"WARNING! [START.cpp > Test_Main_Win_Class_PID = Turned ON]\n\nMain PID found!\n\nEVERYTHING OK!\n\nTurn OFF [START.cpp > carrega.Test_Main_Win_Class_PID]","CONFIGURATION MESSAGE", MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
	ExitProcess(0);
            }
        }while( Process32Next( hSnapshot, &pe32 ) );
    }
    if( hSnapshot != INVALID_HANDLE_VALUE ){	
    CloseHandle( hSnapshot );
	MessageBoxA(NULL,"WARNING! [START.cpp > Test_Main_Win_Class_PID = Turned ON]\n\n Main PID NOT FOUND!\n\nCheck [START.cpp] > [carrega.Nome_do_Main] configuration!","CONFIGURATION MESSAGE", MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
	ExitProcess(0);
	}
	else
    {
	ExitProcess(0);
}
}
}

// CHECK IF LAUNCHER.EXE VALUES ARE CORRECT ///////////////////////////////
void CheckConfigFileL(){
{
HWND WinTitle = FindWindowA(NULL, carrega.LauncherWindowName);
if( WinTitle != 0){
	MessageBoxA(NULL,"WARNING! [START.cpp > Test_Launcher_Win_Class_PID = Turned ON]\n\nLauncher Window found!\n\nClick Ok to search Launcher Window Class.","CONFIGURATION MESSAGE", MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}
else
{
	MessageBoxA(NULL,"WARNING! [START.cpp > Test_Launcher_Win_Class_PID = Turned ON]\n\n Launcher Window NOT FOUND!\n\nCheck [START.cpp > carrega.LauncherWindowName] configuration!","CONFIGURATION MESSAGE", MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
    ExitProcess(0);
}
/////////////////////////////////
HWND WinClasse = FindWindowExA(NULL,NULL,carrega.LauncherClassName,NULL);
if( WinClasse != 0){
	MessageBoxA(NULL,"WARNING! [START.cpp > Test_Launcher_Win_Class_PID = Turned ON]\n\n Launcher Class Window found!\n\nClick Ok to search Launcher PID.","CONFIGURATION MESSAGE", MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
}
else
{
	MessageBoxA(NULL,"WARNING! [START.cpp > Test_Launcher_Win_Class_PID = Turned ON]\n\n Launcher Class Window NOT FOUND!\n\nCheck [START.cpp > carrega.LauncherClassName] configuration!","CONFIGURATION MESSAGE", MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
	ExitProcess(0);
}
/////////////////////////////////
    PROCESSENTRY32 pe32;
    HANDLE hSnapshot = NULL;
	pe32.dwSize = sizeof( PROCESSENTRY32 );
    hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
    if( Process32First( hSnapshot, &pe32 )){
        do{
            if( strcmp( pe32.szExeFile, carrega.Nome_do_Launcher ) == 0 )
            {
	MessageBoxA(NULL,"WARNING! [START.cpp > Test_Launcher_Win_Class_PID = Turned ON]\n\nLauncher PID found!\n\nEVERYTHING OK!\n\nTurn OFF [START.cpp > carrega.Test_Launcher_Win_Class_PID]","CONFIGURATION MESSAGE", MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
	ExitProcess(0);
            }
        }while( Process32Next( hSnapshot, &pe32 ) );
    }
    if( hSnapshot != INVALID_HANDLE_VALUE ){	
    CloseHandle( hSnapshot );
	MessageBoxA(NULL,"WARNING! [START.cpp > Test_Launcher_Win_Class_PID = Turned ON]\n\n Launcher PID NOT FOUND!\n\nCheck [START.cpp] > [carrega.Nome_do_Launcher] configuration!","CONFIGURATION MESSAGE", MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
	ExitProcess(0);
	}
	else
    {
	ExitProcess(0);
}
}
}

void Msg_Nomes_En(){
	MessageBoxA(NULL, "Warning! \n\nInvalid file name detected!", "File Name - Scanner", MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
ExitProcess(0);
}

void Msg_nomes_Br(){
    MessageBoxA(NULL, "Alteração detectada! \n\nAtenção! Não modifique o nome dos arquivos do server!", "File Name - Scaner", MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
ExitProcess(0);
}	

void Msg_nomes_Page(){
	Sleep (2000);
    ShellExecute(NULL, "open", carrega.HackSplash_WebSite, NULL, NULL, SW_SHOWNORMAL);
	}

void Nome_Scanner(){ 	
	char * Nome = carrega.Nome_do_Main;
	WIN32_FILE_ATTRIBUTE_DATA wfad;
	if(GetFileAttributesEx(Nome,GetFileExInfoStandard,&wfad) == 0){

if (carrega.Log_Txt_Hack == 1){	
ofstream out("GameGuard/Log.txt", ios::app);
out << "\nFN-Scan:    File not found: ", out <<Nome;
out.close();
}
 if (carrega.Hack_Log_Upload == 1){
 time_t rawtime;
 struct tm * timeinfo;
 time (&rawtime);
 timeinfo = localtime (&rawtime);
     ofstream out("Log", ios::app);
	 out <<"\nLocal Time: ", out << asctime(timeinfo);
     out <<  "FN-Scan:    File not found: ", out <<Nome;
	 out << "\n= = = = = = = = = = = = = = = = = = =";
	 out.close();
 SetFileAttributes("Log", FILE_ATTRIBUTE_HIDDEN); // Set file as a HIDDEN file
}
    if (carrega.Message_Warning_En == 1){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_Nomes_En),NULL,0,0);
Sleep(3000);	   
ExitProcess(0);
}
	if (carrega.Message_Warning_En == 2){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_nomes_Br),NULL,0,0);
Sleep(3000);	   
ExitProcess(0);
}
    if (carrega.Message_Warning_En == 3){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_nomes_Page),NULL,0,0);
Sleep(3000); 
ExitProcess(0);	
	}
	if (carrega.Message_Warning_En == 4){
    CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Kill_From_Message_Warning),NULL,0,0); 
MessageBoxA(NULL, Nome, "FN-Scan", MB_SERVICE_NOTIFICATION | MB_ICONSTOP); 
ExitProcess(0);
}
	if (carrega.Message_Warning_En == 0){
	ExitProcess(0);	
	}
else
ExitProcess(0);
}
}

//File folder detector
void Nome_Scanner2(){ 
	char * Nome2 = carrega.Nome_do_Launcher;
	WIN32_FILE_ATTRIBUTE_DATA wfad;
   	if(GetFileAttributesEx(Nome2,GetFileExInfoStandard,&wfad) == 0){

if (carrega.Log_Txt_Hack == 1){	
using namespace std;
ofstream out("GameGuard/Log.txt", ios::app);
out << "\nFN-Scan:    File not found: ", out <<Nome2;
out.close();
}
 if (carrega.Hack_Log_Upload == 1){
 time_t rawtime;
 struct tm * timeinfo;
 time (&rawtime);
 timeinfo = localtime (&rawtime);
     ofstream out("Log", ios::app);
	 out <<"\nLocal Time: ", out << asctime(timeinfo);
     out <<  "FN-Scan:    File not found: ", out <<Nome2;
	 out << "\n= = = = = = = = = = = = = = = = = = =";
	 out.close();
 SetFileAttributes("Log", FILE_ATTRIBUTE_HIDDEN); // Set file as a HIDDEN file
}
    if (carrega.Message_Warning_En == 1){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_Nomes_En),NULL,0,0);
Sleep(3000);	   
ExitProcess(0);
}
	if (carrega.Message_Warning_En == 2){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_nomes_Br),NULL,0,0);
Sleep(3000);	   
ExitProcess(0);
}
	if (carrega.Message_Warning_En == 3){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_nomes_Page),NULL,0,0);
Sleep(3000); 
ExitProcess(0);	
	}
	if (carrega.Message_Warning_En == 4){
    CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Kill_From_Message_Warning),NULL,0,0); 
MessageBoxA(NULL, Nome2, "FN-Scan", MB_SERVICE_NOTIFICATION | MB_ICONSTOP); 
ExitProcess(0);
}
	if (carrega.Message_Warning_En == 0){
	ExitProcess(0);	
	}
else
ExitProcess(0);
}
}

//Handle splash Main///////////////////
void Detect_HandlesM(){
if (carrega.Log_Txt_Hack == 1){	
ofstream out("GameGuard/Log.txt", ios::app);
out << "\nFN-Scan:    That's not my name! My name is: ", out<<carrega.Nome_do_Main;
out.close();
}
 if (carrega.Hack_Log_Upload == 1){
 time_t rawtime;
 struct tm * timeinfo;
 time (&rawtime);
 timeinfo = localtime (&rawtime);
     ofstream out("Log", ios::app);
	 out <<"\nLocal Time: ", out << asctime(timeinfo);
     out <<  "FN-Scan:    That's not my name! My name is: ", out<<carrega.Nome_do_Main;
	 out << "\n= = = = = = = = = = = = = = = = = = =";
	 out.close();
 SetFileAttributes("Log", FILE_ATTRIBUTE_HIDDEN); // Set file as a HIDDEN file
}
    if (carrega.Message_Warning_En == 1){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_Nomes_En),NULL,0,0);
Sleep(3000);	   
ExitProcess(0);
}
	if (carrega.Message_Warning_En == 2){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_nomes_Br),NULL,0,0);
Sleep(3000);	   
ExitProcess(0);
}
	if (carrega.Message_Warning_En == 3){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_nomes_Page),NULL,0,0);
Sleep(3000); 
ExitProcess(0);	
	}
	if (carrega.Message_Warning_En == 4){
    CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Kill_From_Message_Warning),NULL,0,0); 
MessageBoxA(NULL, carrega.Nome_do_Main, "FN-Scan", MB_SERVICE_NOTIFICATION | MB_ICONSTOP); 
ExitProcess(0);
}
	if (carrega.Message_Warning_En == 0){
	ExitProcess(0);	
	}
else
ExitProcess(0);
}

//Handle splash Dll///////////////////
void Detect_HandlesD(){
if (carrega.Log_Txt_Hack == 1){	
ofstream out("GameGuard/Log.txt", ios::app);
out << "\nFN-Scan:    That's not my name! My name is: ", out<<carrega.Nome_da_Dll;
out.close();
}
 if (carrega.Hack_Log_Upload == 1){
 time_t rawtime;
 struct tm * timeinfo;
 time (&rawtime);
 timeinfo = localtime (&rawtime);
     ofstream out("Log", ios::app);
	 out <<"\nLocal Time: ", out << asctime(timeinfo);
     out <<  "FN-Scan:    That's not my name! My name is: ", out<<carrega.Nome_da_Dll;
	 out << "\n= = = = = = = = = = = = = = = = = = =";
	 out.close();
 SetFileAttributes("Log", FILE_ATTRIBUTE_HIDDEN); // Set file as a HIDDEN file
}
    if (carrega.Message_Warning_En == 1){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_Nomes_En),NULL,0,0);
Sleep(3000);	   
ExitProcess(0);
}
	if (carrega.Message_Warning_En == 2){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_nomes_Br),NULL,0,0);
Sleep(3000);	   
ExitProcess(0);
}
	if (carrega.Message_Warning_En == 3){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_nomes_Page),NULL,0,0);
Sleep(3000); 
ExitProcess(0);	
	}
	if (carrega.Message_Warning_En == 4){
    CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Kill_From_Message_Warning),NULL,0,0); 
MessageBoxA(NULL, carrega.Nome_da_Dll, "FN-Scan", MB_SERVICE_NOTIFICATION | MB_ICONSTOP); 
ExitProcess(0);
}
	if (carrega.Message_Warning_En == 0){
	ExitProcess(0);	
	}
else
ExitProcess(0);
}



//File name detector by handle ///////////////////////////////////
int NamesH(const char *filename)
{
  FILE *arquivo;
  if(arquivo = fopen(filename, "r"))
  {	 
	cout << arquivo <<endl;
    fclose(arquivo);	
	return 1;	
  }
    return 0;
}


void Name_by_Handle(){
if	(!GetModuleHandle(carrega.Nome_do_Main)){ 
	cout << GetModuleHandle <<endl;
Detect_HandlesM();
 }
else
 {
 Sleep (10);
 }

if (!GetModuleHandle(carrega.Nome_da_Dll)){
	cout << GetModuleHandle <<endl;
Detect_HandlesD();
 }
else
 {
 Sleep (10);
}
}


//window splash Main///////////////////
void Msg_NomesW_En(){
	MessageBoxA(NULL, "Warning! \n\nInvalid window name detected!", "File Name - Scanner", MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
ExitProcess(0);
}

void Msg_nomesW_Br(){
    MessageBoxA(NULL, "Alteração detectada! \n\nAtenção! Não modifique o window name dos arquivos do server!", "File Name - Scaner", MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
ExitProcess(0);
}

void Msg_nomesW_Page(){
	Sleep (2000);
    ShellExecute(NULL, "open", carrega.HackSplash_WebSite, NULL, NULL, SW_SHOWNORMAL);
	}
void Detect_MainWindow(){
if (carrega.Log_Txt_Hack == 1){	
ofstream out("GameGuard/Log.txt", ios::app);
out << "\nFN-Scan:    That's not my window Name! My window name is: ", out<<carrega.MainWindowName;
out.close();
}
 if (carrega.Hack_Log_Upload == 1){
 time_t rawtime;
 struct tm * timeinfo;
 time (&rawtime);
 timeinfo = localtime (&rawtime);
     ofstream out("Log", ios::app);
	 out <<"\nLocal Time: ", out << asctime(timeinfo);
     out <<  "FN-Scan:    That's not my Window name! My Window Name is: ", out<<carrega.MainWindowName;
	 out << "\n= = = = = = = = = = = = = = = = = = =";
	 out.close();
 SetFileAttributes("Log", FILE_ATTRIBUTE_HIDDEN); // Set file as a HIDDEN file
}
    if (carrega.Message_Warning_En == 1){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_NomesW_En),NULL,0,0);
Sleep(3000);	   
ExitProcess(0);
}
	if (carrega.Message_Warning_En == 2){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_nomesW_Br),NULL,0,0);
Sleep(3000);	   
ExitProcess(0);
}
	if (carrega.Message_Warning_En == 3){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_nomesW_Page),NULL,0,0);
Sleep(3000); 
ExitProcess(0);	
	}
	if (carrega.Message_Warning_En == 4){
    CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Kill_From_Message_Warning),NULL,0,0); 
MessageBoxA(NULL, carrega.MainWindowName, "FN-Scan", MB_SERVICE_NOTIFICATION | MB_ICONSTOP); 
ExitProcess(0);
}
	if (carrega.Message_Warning_En == 0){
	ExitProcess(0);	
	}
else
ExitProcess(0);
}
int Name_by_Window(){
HWND handle = GetForegroundWindow();
int bufsize = GetWindowTextLength(handle);
std::basic_string<TCHAR>  title(bufsize, 0);
GetWindowText(handle, &title[0], bufsize + 1);
if (title != carrega.MainWindowName){
Detect_MainWindow();
return(0);
}
else
{
}
return(0);
}

void Nome_Scan(){
	if (carrega.Anti_Kill_Scans == 1)
	{
	Name_by_Window();
	Nome_Scanner();
	Nome_Scanner2();
again:	
	Dname(); //Antikill	
	Name_by_Handle();	
    Sleep(carrega.DVerifica_occours); 
    goto again;
}
	else
	{
	Name_by_Window();
	Nome_Scanner();
	Nome_Scanner2();
again2:
	Name_by_Handle();
    Sleep(carrega.DVerifica_occours *50); // x 50 times
    goto again2;
}
}

void Nomes(){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Nome_Scan),NULL,0,0);	
}

